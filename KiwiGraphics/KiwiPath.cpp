/*
 ==============================================================================
 
 This file is part of the KIWI library.
 Copyright (c) 2014 Pierre Guillot & Eliott Paris.
 
 Permission is granted to use this software under the terms of either:
 a) the GPL v2 (or any later version)
 b) the Affero GPL v3
 
 Details of these licenses can be found at: www.gnu.org/licenses
 
 KIWI is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 To release a closed-source product which uses KIWI, contact : guillotpierre6@gmail.com
 
 ==============================================================================
 */

#include "KiwiPath.h"

namespace Kiwi
{
    Path::Node::Node(Point const& pt, Mode const mode) noexcept :
    point(pt), mode(mode)
    {
        
    }
    
    Path::Node::Node(Point const& pt) noexcept :
    point(pt), mode(Linear)
    {
        
    }
    
    Path::Node::Node(Node const& other) noexcept :
    point(other.point), mode(other.mode)
    {
        
    }
    
    Path::Node::~Node() noexcept
    {
        ;
    }
    
    Path::Path() noexcept
    {
        ;
    }
    
    Path::Path(Path const& path) noexcept
    {
        m_points = path.m_points;
    }
    
    Path::Path(Point const& pt) noexcept
    {
        m_points.push_back({pt, Move});
    }
    
    Path::Path(Rectangle const& rect) noexcept
    {
        m_points.push_back({rect.position(), Move});
        m_points.push_back({Point(rect.x() + rect.width(), rect.y()), Linear});
        m_points.push_back({Point(rect.x() + rect.width(), rect.y() + rect.height()), Linear});
        m_points.push_back({Point(rect.x(), rect.y() + rect.height()), Linear});
        close();
    }
    
    Path::Path(Point const& start, Point const& end) noexcept
    {
        m_points.push_back({start, Move});
        m_points.push_back({end, Linear});
    }
    
    Path::Path(Point const& start, Point const& ctrl, Point const& end) noexcept
    {
        m_points.push_back({start, Move});
        m_points.push_back({ctrl, Quadratic});
        m_points.push_back({end, Linear});
    }
    

    Path::Path(Point const& start, Point const& ctrl1, Point const& ctrl2, Point const& end) noexcept
    {
        m_points.push_back({start, Move});
        m_points.push_back({ctrl1, Cubic});
        m_points.push_back({ctrl2, Cubic});
        m_points.push_back({end, Linear});
    }
    
    Path::~Path() noexcept
    {
        m_points.clear();
    }
    
    void Path::move(const Point &pt) noexcept
    {
        m_points.push_back({pt, Move});
    }
    
    void Path::line(const Point &pt) noexcept
    {
        m_points.push_back({pt, Linear});
    }
    
    void Path::quadratic(Point const& control, Point const& end)
    {
        m_points.push_back({control, Quadratic});
        m_points.push_back({end, Linear});
    }
    
    void Path::cubic(Point const& control1, Point const& control2, Point const& end)
    {
        m_points.push_back({control1, Cubic});
        m_points.push_back({control2, Cubic});
        m_points.push_back({end, Linear});
    }
    
    void Path::close() noexcept
    {
        if(!m_points.empty())
        {
            m_points.push_back({m_points[0].point, Linear});
        }
    }
    
    void Path::clear() noexcept
    {
        m_points.clear();
    }
    
    Rectangle Path::bounds() const noexcept
    {
        Point position(0., 0.);
        Point size(0., 0.);
        if(!m_points.empty())
        {
            position = m_points[0].point;
            size = m_points[0].point;
            for(vector<Point>::size_type i = 1; i < m_points.size(); i++)
            {
                if(m_points[i].point.x() < position.x())
                {
                    position.x(m_points[i].point.x());
                }
                else if(m_points[i].point.x() > size.x())
                {
                    size.x(m_points[i].point.x());
                }
                
                if(m_points[i].point.y() < position.y())
                {
                    position.y(m_points[i].point.y());
                }
                else if(m_points[i].point.y() > size.y())
                {
                    size.y(m_points[i].point.y());
                }
            }
        }
        return Rectangle(position, size - position);
        
    }
    
    double Path::distance(Point const& pt) const noexcept
    {
        if(m_points.size() == 1)
        {
            return pt.distance(m_points[0].point);
        }
        else if(m_points.size() > 1)
        {
            double dist = numeric_limits<double>::max();
            Point previous;
            for(vector<Node>::size_type i = 0; i < m_points.size(); i++)
            {
                Point current = m_points[i].point;
                switch(m_points[i].mode)
                {
                    case Move:
                    {
                        const double newdist = pt.distance(current);
                        if(newdist < dist)
                        {
                            dist = newdist;
                        }
                        break;
                    }
                    case Linear:
                    {
                        const double newdist = pt.distance(previous, current);
                        if(newdist < dist)
                        {
                            dist = newdist;
                        }
                        break;
                    }
                    case Quadratic:
                    {
                        i++;
                        if(i < m_points.size())
                        {
                            const Point ctrl = current;
                            current = m_points[i].point;
                            const double newdist = pt.distance(previous, ctrl, current);
                            if(newdist < dist)
                            {
                                dist = newdist;
                            }
                        }
                        break;
                    }
                    case Cubic:
                    {
                        i += 2;
                        if(i < m_points.size())
                        {
                            const Point ctrl1 = current;
                            const Point ctrl2 = m_points[i-1].point;
                            current = m_points[i].point;
                            const double newdist = pt.distance(previous, ctrl1, ctrl2, current);
                            if(newdist < dist)
                            {
                                dist = newdist;
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
                previous = current;
            }
            return dist;
        }
        return 0.;
    }
    
    bool Path::near(Point const& pt, double const distance) const noexcept
    {
        if(m_points.size() == 1)
        {
            return pt.near(m_points[0].point, distance);
        }
        else if(m_points.size() > 1)
        {
            Point previous;
            for(vector<Node>::size_type i = 0; i < m_points.size(); i++)
            {
                Point current = m_points[i].point;
                switch(m_points[i].mode)
                {
                    case Move:
                        if(pt.near(current, distance))
                        {
                            return true;
                        }
                        break;
                    case Linear:
                        if(pt.near(previous, current, distance))
                        {
                            return true;
                        }
                        break;
                    case Quadratic:
                        i++;
                        if(i < m_points.size())
                        {
                            const Point ctrl = current;
                            current = m_points[i].point;
                            if(pt.near(previous, ctrl, current, distance))
                            {
                                return true;
                            }
                            
                        }
                        break;
                    case Cubic:
                        i += 2;
                        if(i < m_points.size())
                        {
                            const Point ctrl1 = current;
                            const Point ctrl2 = m_points[i-1].point;
                            current = m_points[i].point;
                            if(pt.near(previous, ctrl1, ctrl2, current, distance))
                            {
                                return true;
                            }
                            
                        }
                        break;
                        
                    default:
                        break;
                }
                previous = current;
            }
        }
        return false;
    }
    
    
    bool Path::overlaps(Rectangle const& rect) const noexcept
    {
        if(m_points.size() == 1)
        {
            return rect.contains(m_points[0].point);
        }
        else if(m_points.size() > 1)
        {
            Point previous;
            for(vector<Node>::size_type i = 0; i < m_points.size(); i++)
            {
                Point current = m_points[i].point;
                switch(m_points[i].mode)
                {
                    case Move:
                        if(rect.contains(current))
                        {
                            return true;
                        }
                        break;
                    case Linear:
                        if(rect.overlaps(previous, current))
                        {
                            return true;
                        }
                        break;
                    case Quadratic:
                        i++;
                        if(i < m_points.size())
                        {
                            const Point ctrl = current;
                            current = m_points[i].point;
                            if(rect.overlaps(previous, ctrl, current))
                            {
                                return true;
                            }
                            
                        }
                        break;
                    case Cubic:
                        i += 2;
                        if(i < m_points.size())
                        {
                            const Point ctrl1 = current;
                            const Point ctrl2 = m_points[i-1].point;
                            current = m_points[i].point;
                            if(rect.overlaps(previous, ctrl1, ctrl2, current))
                            {
                                return true;
                            }
                            
                        }
                        break;
                        
                    default:
                        break;
                }
                previous = current;
            }
        }
        return false;
    }
}