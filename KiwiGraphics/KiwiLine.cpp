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

#include "KiwiLine.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      SEGMENT                                     //
    // ================================================================================ //
    
    Point Segment::getNearestPoint(Point const& pt) const noexcept
    {
        const Point delta(m_end - m_start);
        const double length = delta.length();
        if(length > 0.)
        {
            const double ratio = (pt - m_start).dot(delta) / length;
            if(ratio < 0.)
            {
                return m_start;
            }
            else if(ratio > 1.)
            {
                return m_end;
            }
            else
            {
                return m_start + (ratio * delta);
            }
        }
        else
        {
            return (distance(m_start) < distance(m_end)) ? m_start : m_end;
        }
    }
    
    bool Segment::intersects(Segment const& s) const noexcept
    {
        if(start() == s.start() || start() == s.end() || end() == s.end() || end() == s.start())
        {
            return true;
        }
        
        const Point d1(end() - start());
        const Point d2(s.end() - s.start());
        const double divisor = d1.x() * d2.y() - d2.x() * d1.y();
        
        if(divisor == 0)
        {
            if(!(d1 == Point() || d2 == Point()))
            {
                if (d1.y() == 0 && d2.y() != 0)
                {
                    const double along = (startY() - s.startY()) / d2.y();
                    return along >= 0. && along <= 1.;
                }
                else if (d2.y() == 0 && d1.y() != 0)
                {
                    const double along = (s.startY() - startY()) / d1.y();
                    return along >= 0. && along <= 1.;
                }
                else if (d1.x() == 0. && d2.x() != 0)
                {
                    const double along = (startX() - s.startX()) / d2.x();
                    return along >= 0. && along <= 1.;
                }
                else if (d2.x() == 0 && d1.x() != 0)
                {
                    const double along = (s.startX() - startX()) / d1.x();
                    return along >= 0. && along <= 1.;
                }
            }
            
            return false;
        }
        
        const double along1 = ((startY() - s.startY()) * d2.x() - (startX() - s.startX()) * d2.y()) / divisor;
        
        if (along1 < 0. || along1 > 1.)
            return false;
        
        const double along2 = ((startY() - s.startY()) * d1.x() - (startX() - s.startX()) * d1.y()) / divisor;
        return along2 >= 0. && along2 <= 1.;
    }
    
    bool Segment::intersects(Segment const& s, Point& intersection) const noexcept
    {
        if(start() == s.start() || start() == s.end())
        {
            intersection = start();
            return true;
        }
        else if(end() == s.end() || end() == s.start())
        {
            intersection = end();
            return true;
        }
        
        const Point d1(end() - start());
        const Point d2(s.end() - s.start());
        const double divisor = d1.x() * d2.y() - d2.x() * d1.y();
        
        if(divisor == 0)
        {
            if(!(d1 == Point() || d2 == Point()))
            {
                if (d1.y() == 0 && d2.y() != 0)
                {
                    const double along = (startY() - s.startY()) / d2.y();
                    intersection = Point(s.startX() + along * d2.x(), startY());
                    return along >= 0. && along <= 1.;
                }
                else if (d2.y() == 0 && d1.y() != 0)
                {
                    const double along = (s.startY() - startY()) / d1.y();
                    intersection = Point(startX() + along * d1.x(), s.startY());
                    return along >= 0. && along <= 1.;
                }
                else if (d1.x() == 0. && d2.x() != 0)
                {
                    const double along = (startX() - s.startX()) / d2.x();
                    intersection = Point(startX(), s.startY() + along * d2.y());
                    return along >= 0. && along <= 1.;
                }
                else if (d2.x() == 0 && d1.x() != 0)
                {
                    const double along = (s.startX() - startX()) / d1.x();
                    intersection = Point(s.startX(), startY() + along * d1.y());
                    return along >= 0. && along <= 1.;
                }
            }
            
            intersection = (end() + s.start()) / 2.;
            return false;
        }
        
        const double along1 = ((startY() - s.startY()) * d2.x() - (startX() - s.startX()) * d2.y()) / divisor;
        intersection = start() + d1 * along1;
        
        if (along1 < 0 || along1 > 1.)
            return false;
        
        const double along2 = ((startY() - s.startY()) * d1.x() - (startX() - s.startX()) * d1.y()) / divisor;
        return along2 >= 0 && along2 <= 1.;
    }
    
    bool Segment::intersects(BezierQuad const& curve) const noexcept
    {
        return curve.intersects(*this);
    }
    
    bool Segment::intersects(BezierCubic const& curve) const noexcept
    {
        return curve.intersects(*this);
    }
    
    // ================================================================================ //
    //                                    BEZIER QUAD                                   //
    // ================================================================================ //
    
    Point BezierQuad::getNearestPoint(Point const& pt) const noexcept
    {
        int todo;
        return Point(0., 0.);
    }
    
    Point BezierQuad::getPointAt(const double t) const noexcept
    {
        const double t2 = t * t;
        const double mt = 1.-t;
        const double mt2 = mt * mt;
        return m_start * mt2 + m_ctrl * 2 * mt * t + m_end * t2;
    }
    
    bool BezierQuad::intersects(Segment const& segment) const noexcept
    {
        const ulong steps = 100;
        
        const double factor = 1./(double)steps;
        Point last = m_start;
        
        for(double t = 0.; t < 1.; t+=factor)
        {
            const Point next = getPointAt(t);
            if(Segment(last, next).intersects(segment))
            {
                return true;
            }
            
            last = next;
        }
        
        if(Segment(last, m_end).intersects(segment))
        {
            return true;
        }
        
        return false;
    }
    
    bool BezierQuad::intersects(BezierQuad const& curve) const noexcept
    {
        const vector<Point> points = curve.discretized(100);
        
        for(ulong i = 0; i < points.size(); i+=2)
        {
            if(intersects(Segment(points[i], points[i+1])))
            {
                return true;
            }
        }
        
        return false;
    }
    
    bool BezierQuad::intersects(BezierCubic const& curve) const noexcept
    {
        const vector<Point> points = discretized(100);
        
        for(ulong i = 0; i < points.size(); i+=2)
        {
            if(curve.intersects(Segment(points[i], points[i+1])))
            {
                return true;
            }
        }
        
        return false;
    }
    
    // ================================================================================ //
    //                                    BEZIER CUBIC                                  //
    // ================================================================================ //
    
    Point BezierCubic::getNearestPoint(Point const& pt) const noexcept
    {
        int todo;
        return Point(0., 0.);
    }
    
    Point BezierCubic::getPointAt(const double t) const noexcept
    {
        const double t2 = t * t;
        const double t3 = t2 * t;
        const double mt = 1-t;
        const double mt2 = mt * mt;
        const double mt3 = mt2 * mt;
        return m_start * mt3 + 3* m_ctrl1 * mt2 * t + 3 * m_ctrl2 * mt * t2 + m_end * t3;
    }
    
    bool BezierCubic::intersects(Segment const& segment) const noexcept
    {
        const ulong steps = 100;
        
        const double factor = 1./(double)steps;
        Point last = m_start;
        
        for(double t = 0.; t < 1.; t+=factor)
        {
            const Point next = getPointAt(t);
            if(Segment(last, next).intersects(segment))
            {
                return true;
            }
            
            last = next;
        }
        
        if(Segment(last, m_end).intersects(segment))
        {
            return true;
        }
        
        return false;
    }
    
    bool BezierCubic::intersects(BezierQuad const& curve) const noexcept
    {
        const vector<Point> points = curve.discretized(100);
        
        for(ulong i = 0; i < points.size(); i+=2)
        {
            if(intersects(Segment(points[i], points[i+1])))
            {
                return true;
            }
        }
        
        return false;
    }
    
    bool BezierCubic::intersects(BezierCubic const& curve) const noexcept
    {
        const vector<Point> points = discretized(100);
        
        for(ulong i = 0; i < points.size(); i+=2)
        {
            if(curve.intersects(Segment(points[i], points[i+1])))
            {
                return true;
            }
        }
        
        return false;
    }
}
