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

#include "Size.h"

namespace Kiwi
{
    namespace Gui
    {
        
        // ================================================================================ //
        //                                      POINT                                       //
        // ================================================================================ //
        
        Size::Size() noexcept :
        m_width(0.), m_height(0.)
        {
            ;
        }
        
        Size::Size(const double width, const double height, const double ratio, const double min_width, const double min_height) noexcept
        {
            m_ratio         = max(ratio, 0.);
            m_min_width     = max(min_width, 0.);
            m_min_height    = max(min_height, 0.);
            m_width         = max(width, m_min_width);
            m_height        = max(height, m_min_height);
            if(m_ratio)
            {
                m_height = m_width * m_ratio;
            }
        }
        
        Size::Size(Size const& size) noexcept :
        m_width(size.m_width),
        m_height(size.m_height),
        m_ratio(size.m_ratio),
        m_min_width(size.m_min_width),
        m_min_height(size.m_min_height)
        {
            ;
        }
        
        Size::Size(Point const& pt) noexcept :
        m_width(max(pt.x(), 0.)),
        m_height(max(pt.y(), 0.)),
        m_ratio(0.),
        m_min_width(0.),
        m_min_height(0.)
        {
            ;
        }
        
        Size::~Size()
        {
            ;
        }
    }
}