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

#include "KiwiGuiScrollBar.h"
#include "KiwiGuiDevice.h"

namespace Kiwi
{
    GuiScrollBar::GuiScrollBar(sGuiContext context, const double time, Color const& bgcolor, Color const& tbcolor) noexcept : GuiSketcher(context),
    m_limits({0., 1.}),
    m_range({0., 0.}),
    m_thumb_time(time),
    m_background_color(bgcolor),
    m_thumb_color(tbcolor)
    {
        ;
    }
    
    void GuiScrollBar::setThumbDisplayTime(const double time) noexcept
    {
        m_thumb_time = time;
    }
    
    void GuiScrollBar::setBackgroundColor(Color const& color) noexcept
    {
        if(color != m_background_color)
        {
            m_background_color = color;
            redraw();
        }
    }
    
    void GuiScrollBar::setThumbColor(Color const& color) noexcept
    {
        if(color != m_thumb_color)
        {
            m_thumb_color = color;
            if(m_thumb_time < 0.) {redraw();}
        }
    }
    
    void GuiScrollBar::setRangeLimits(array<double, 2> const& limits) noexcept
    {
        double lmin = min(limits[0], limits[1]), lmax = max(limits[0], limits[1]);
        if(m_limits[0] != lmin && m_limits[1] != lmax)
        {
            m_limits[0] = lmin;
            m_limits[1] = lmax;
            if(m_thumb_time < 0.) {redraw();}
        }
    }
    
    void GuiScrollBar::setCurrentRange(array<double, 2> const& range) noexcept
    {
        double rmin = clip(min(range[0], range[1]), m_limits[0], m_limits[1]), rmax = clip(max(range[0], range[1]), m_limits[0], m_limits[1]);
        if(m_range[0] != rmin && m_range[1] != rmax)
        {
            m_range[0] = rmin;
            m_range[1] = rmax;
            redraw();
        }
    }
    
    void GuiScrollBar::scrollToStart() noexcept
    {
        if(m_range[0] != m_limits[0])
        {
            const double offset = m_range[0] - m_limits[0];
            m_range[0] -= offset;
            m_range[1] -= offset;
            redraw();
        }
    }
    
    void GuiScrollBar::scrollToEnd() noexcept
    {
        if(m_range[1] != m_limits[1])
        {
            const double offset = m_limits[1] - m_range[1];
            m_range[0] += offset;
            m_range[1] += offset;
            redraw();
        }
    }

}
















