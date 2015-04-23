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
    double Path::distance(Point const& pt) const noexcept
    {
        if(m_nodes.size() == 1)
        {
            return pt.distance(m_nodes[0].point());
        }
        else if(m_nodes.size() > 1)
        {
            double dist = numeric_limits<double>::max();
            Point previous;
            for(vector<Node>::size_type i = 0; i < m_nodes.size(); i++)
            {
                Point current = m_nodes[i].point();
                switch(m_nodes[i].mode())
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
                        if(i < m_nodes.size())
                        {
                            const Point ctrl = current;
                            current = m_nodes[i].point();
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
                        if(i < m_nodes.size())
                        {
                            const Point ctrl1 = current;
                            const Point ctrl2 = m_nodes[i-1].point();
                            current = m_nodes[i].point();
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
        if(m_nodes.size() == 1)
        {
            return pt.near(m_nodes[0].point(), distance);
        }
        else if(m_nodes.size() > 1)
        {
            for(vector<Node>::size_type i = 1; i < m_nodes.size(); i++)
            {
                switch(m_nodes[i].mode())
                {
                    case Move:
                        if(pt.near(m_nodes[i].point(), distance))
                        {
                            return true;
                        }
                        break;
                    case Linear:
                        if(pt.near(m_nodes[i-1].point(), m_nodes[i].point(), distance))
                        {
                            return true;
                        }
                        break;
                    case Quadratic:
                        i++;
                        if(i < m_nodes.size())
                        {
                            if(pt.near(m_nodes[i-2].point(), m_nodes[i-1].point(), m_nodes[i].point(), distance))
                            {
                                return true;
                            }
                        }
                        break;
                    case Cubic:
                        i += 2;
                        if(i < m_nodes.size())
                        {
                            if(pt.near(m_nodes[i-3].point(), m_nodes[i-2].point(), m_nodes[i-1].point(), m_nodes[i].point(), distance))
                            {
                                return true;
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        return false;
    }
    
    
    bool Path::overlaps(Rectangle const& rect) const noexcept
    {
        if(m_nodes.size() == 1)
        {
            return rect.contains(m_nodes[0].point());
        }
        else if(m_nodes.size() > 1)
        {
            Point previous;
            for(vector<Node>::size_type i = 0; i < m_nodes.size(); i++)
            {
                Point current = m_nodes[i].point();
                switch(m_nodes[i].mode())
                {
                    case Move:
                        if(rect.contains(current))
                        {
                            return true;
                        }
                        break;
                    case Linear:
                        if(rect.overlaps(Segment(previous, current)))
                        {
                            return true;
                        }
                        break;
                    case Quadratic:
                        i++;
                        if(i < m_nodes.size())
                        {
                            const Point ctrl = current;
                            current = m_nodes[i].point();
                            if(rect.overlaps(previous, ctrl, current))
                            {
                                return true;
                            }
                            
                        }
                        break;
                    case Cubic:
                        i += 2;
                        if(i < m_nodes.size())
                        {
                            const Point ctrl1 = current;
                            const Point ctrl2 = m_nodes[i-1].point();
                            current = m_nodes[i].point();
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