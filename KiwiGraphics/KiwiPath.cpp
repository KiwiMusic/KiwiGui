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
    Path::Path(initializer_list<Point> il) noexcept
    {
        if(il.size())
        {
            auto it = il.begin();
            m_points.push_back(Node(*it, Move));
            while(++it != il.end())
            {
                m_points.push_back(Node(*it, Linear));
            }
        }
    }
    
    Path::Path(const Mode mode, initializer_list<Point> il) noexcept
    {
        if(il.size())
        {
            auto it = il.begin();
            m_points.push_back(Node(*it++, Move));
            if(mode == Linear)
            {
                while(it != il.end())
                {
                    m_points.push_back(Node(*it++, Linear));
                }
            }
            else if(mode == Quadratic)
            {
                while(it != il.end())
                {
                    auto it1 = it++;
                    if(it != il.end())
                    {
                        m_points.push_back(Node(*it1, Quadratic));
                        m_points.push_back(Node(*it++, Linear));
                    }
                }
            }
            else if(mode == Cubic)
            {
                while(it != il.end())
                {
                    auto it1 = it++;
                    auto it2 = it != il.end() ? it++ : il.end();
                    if(it != il.end())
                    {
                        m_points.push_back(Node(*it1, Cubic));
                        m_points.push_back(Node(*it2, Cubic));
                        m_points.push_back(Node(*it++, Linear));
                    }
                }
            }
        }
    }
    
    void Path::moveTo(const Point &pt) noexcept
    {
        m_points.push_back({pt, Move});
    }
    
    void Path::lineTo(const Point &pt) noexcept
    {
        m_points.push_back({pt, Linear});
    }
    
    void Path::quadraticTo(Point const& control, Point const& end)
    {
        m_points.push_back({control, Quadratic});
        m_points.push_back({end, Linear});
    }
    
    void Path::cubicTo(Point const& control1, Point const& control2, Point const& end)
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
        return Rectangle(position, Size(size.x() - position.x(), size.y() - position.y()));
        
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