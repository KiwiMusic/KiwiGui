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
    Rectangle::Rectangle() noexcept :
    m_position(0., 0.), m_size(0., 0.)
    {
        ;
    }
    
    Rectangle::Rectangle(const double x, const double y, const double width, const double height) noexcept :
    m_position(x, y), m_size(max(width, 0.), max(height, 0.))
    {
        ;
    }
    
    Rectangle::Rectangle(Point const& position, Point const& size) noexcept :
    m_position(position), m_size(max(size.x(), 0.), max(size.y(), 0.))
    {
        ;
    }
    
    Rectangle::Rectangle(Rectangle const& rect) noexcept :
    m_position(rect.m_position), m_size(rect.m_size)
    {
        
    }
    
    Rectangle::~Rectangle()
    {
        ;
    }
    
    Rectangle Rectangle::withCorners(Point const& corner1, Point const& corner2) noexcept
    {
        const double x = min(corner1.x(), corner2.x());
        const double y = min(corner1.y(), corner2.y());
        double w = corner1.x() - corner2.x();
        double h = corner1.y() - corner2.y();
        
        if(w < 0.)
        {
            w = -w;
        }
        if(h < 0.)
        {
             h = -h;
        }
        return Rectangle(x, y, w, h);
    }
    
    Rectangle Rectangle::withCentre(Point const& centre, Point const& size)
    {
        return Rectangle(centre, Point()).expanded(size * 0.5);
    }
    
    bool Rectangle::overlaps(Point const& begin, Point const& end) const noexcept
    {
        int zaza;
        if(contains(begin) || contains(end))
        {
            return true;
        }
        return false;
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