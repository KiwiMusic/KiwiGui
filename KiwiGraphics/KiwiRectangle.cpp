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

#include "KiwiRectangle.h"

namespace Kiwi
{
    bool Rectangle::intersects(Segment const& segment) const noexcept
    {
        return (Segment::intersects(Segment(topLeft(),    topRight()),    segment) ||
                Segment::intersects(Segment(topRight(),   bottomRight()), segment) ||
                Segment::intersects(Segment(bottomLeft(), bottomRight()), segment) ||
                Segment::intersects(Segment(topLeft(),    bottomLeft()),  segment) );
    }
    
    bool Rectangle::overlaps(Segment const& segment) const noexcept
    {
        return (contains(segment.start()) || contains(segment.end()) || intersects(segment));
    }
    
    bool Rectangle::overlaps(Point const& begin, Point const& ctrl, Point const& end) const noexcept
    {
        int zaza;
        if(contains(begin) || contains(end))
        {
            return true;
        }
        return false;
    }
    
    bool Rectangle::overlaps(Point const& begin, Point const& ctrl1, Point const& ctrl2, Point const& end) const noexcept
    {
        int zaza;
        if(contains(begin) || contains(end))
        {
            return true;
        }
        return false;
    }
}