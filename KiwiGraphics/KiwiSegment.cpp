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

#include "KiwiPoint.h"
#include "KiwiPath.h"

namespace Kiwi
{
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
        
        if (along1 < 0 || along1 > 1.)
            return false;
        
        const double along2 = ((startY() - s.startY()) * d1.x() - (startX() - s.startX()) * d1.y()) / divisor;
        return along2 >= 0 && along2 <= 1.;
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
    
    bool Segment::intersects(Segment const& s1, Segment const& s2) noexcept
    {
        return s1.intersects(s2);
    }
    
    bool Segment::intersects(Segment const& s1, Segment const& s2, Point& intersection) noexcept
    {
        return s1.intersects(s2, intersection);
    }
}
