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
        return (segment.intersects(Segment(topLeft(),    topRight()))    ||
                segment.intersects(Segment(topRight(),   bottomRight())) ||
                segment.intersects(Segment(bottomLeft(), bottomRight())) ||
                segment.intersects(Segment(topLeft(),    bottomLeft())));
    }
    
    bool Rectangle::overlaps(Segment const& segment) const noexcept
    {
        return (contains(segment.start()) || contains(segment.end()) || intersects(segment));
    }
    
    bool Rectangle::overlaps(BezierQuad const& curve) const noexcept
    {
        if(contains(curve.start()) || contains(curve.end()))
        {
            return true;
        }
        else
        {
            const vector<Point> points = curve.discretized(100);
            
            for(ulong i = 0; i < points.size(); i+=2)
            {
                if(intersects(Segment(points[i], points[i+1])))
                {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    bool Rectangle::overlaps(BezierCubic const& curve) const noexcept
    {
        if(contains(curve.start()) || contains(curve.end()))
        {
            return true;
        }
        else
        {
            const vector<Point> points = curve.discretized(100);
            
            for(ulong i = 0; i < points.size(); i+=2)
            {
                if(intersects(Segment(points[i], points[i+1])))
                {
                    return true;
                }
            }
        }
        
        return false;
    }
}