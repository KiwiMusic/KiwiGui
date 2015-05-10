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
    GuiScrollBar::GuiScrollBar(sGuiContext context,
                               const Direction direction,
                               const double time,
                               Color const& tbcolor,
                               Color const& bgcolor) noexcept :
    GuiModel(context),
    m_direction(direction),
    m_thumb_time(time),
    m_thumb_color(tbcolor),
    m_background_color(bgcolor)
    {
        ;
    }
    
    void GuiScrollBar::setThumbDisplayTime(const double time) noexcept
    {
        if(m_thumb_time != time)
        {
            m_thumb_time = time;
            redraw();
        }
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
            redraw();
        }
    }
    
    void GuiScrollBar::draw(sController ctrl, Sketch& sketch) const
    {
        sketch.fillAll(m_background_color);
        if(ctrl->isThumbVisible())
        {
            const array<double, 2> limits = ctrl->getRangeLimits(), range = ctrl->getCurrentRange();
            const Size size = ctrl->getSize();
            sketch.setColor(m_thumb_color);
            if(m_direction == Horizontal)
            {
                const double ratio = size.width() / (limits[1] - limits[0]);
                sketch.fillRectangle((range[0] + limits[0]) * ratio, 0., (range[1] + limits[0]) * ratio, size.height());
            }
            else
            {
                const double ratio = size.height() / (limits[1] - limits[0]);
                sketch.fillRectangle(0., (range[0] + limits[0]) * ratio, size.width(), (range[1] + limits[0]) * ratio);
            }
        }
    }
    
    bool GuiScrollBar::receive(sController ctrl, MouseEvent const& event)
    {
        if(event.isWheel())
        {
            const array<double, 2> range = ctrl->getCurrentRange();
            if(m_direction == Horizontal)
            {
                ctrl->scrollTo(event.getWheelOffsetX() + (range[1] - range[0]) * 0.5);
            }
            else
            {
                ctrl->scrollTo(event.getWheelOffsetY() + (range[1] - range[0]) * 0.5);
            }
            return true;
        }
        else if(event.isDown() || event.isDrag())
        {
            if(ctrl->isThumbVisible() || m_thumb_time < 0.)
            {
                if(m_direction == Horizontal)
                {
                    ctrl-> scrollTo(event.getX());
                }
                else
                {
                    ctrl-> scrollTo(event.getY());
                }
            }
            return true;
        }
        return false;
    }
    
    sGuiController GuiScrollBar::createController()
    {
        return make_shared<Controller>(static_pointer_cast<GuiScrollBar>(shared_from_this()));
    }

    // ================================================================================ //
    //                              GUI SCROOLBAR CONTROLLER                            //
    // ================================================================================ //
    
    GuiScrollBar::Controller::Controller(sGuiScrollBar scrollbar) noexcept :
    GuiController(scrollbar),
    m_scrollbar(scrollbar)
    {
        m_limits    = {0., 1.};
        m_range     = {0., 0.};
        m_visible   = scrollbar->getThumbDisplayTime() < 0.;
        shouldReceiveMouse(true);
        shouldReceiveKeyboard(false);
        shouldReceiveActions(false);
    }
    
    void GuiScrollBar::Controller::tick()
    {
        m_visible = false;
        redraw();
    }
    
    void GuiScrollBar::Controller::draw(sGuiView view, Sketch& sketch)
    {
        sGuiScrollBar scrollbar(getScrollBar());
        if(scrollbar)
        {
            scrollbar->draw(static_pointer_cast<Controller>(GuiController::shared_from_this()), sketch);
        }
    }
    
    bool GuiScrollBar::Controller::receive(sGuiView view, MouseEvent const& event)
    {
        sGuiScrollBar scrollbar(getScrollBar());
        if(scrollbar)
        {
            if(scrollbar->receive(static_pointer_cast<Controller>(GuiController::shared_from_this()), event))
            {
                return true;
            }
            else
            {
                if(m_visible && scrollbar->getThumbDisplayTime() > 1.)
                {
                    delay(scrollbar->getThumbDisplayTime());
                }
                else if(m_visible && scrollbar->getThumbDisplayTime() > 0.)
                {
                    m_visible = false;
                    view->redraw();
                }
                return false;
            }
        }
        return false;
    }
    
    void GuiScrollBar::Controller::setRangeLimits(array<double, 2> const& limits) noexcept
    {
        double lmin = min(limits[0], limits[1]), lmax = max(limits[0], limits[1]);
        if(m_limits[0] != lmin && m_limits[1] != lmax)
        {
            m_limits[0] = lmin;
            m_limits[1] = lmax;
            if(m_visible)
            {
                getView()->redraw();
            }
        }
    }
    
    void GuiScrollBar::Controller::setCurrentRange(array<double, 2> const& range) noexcept
    {
        double rmin = clip(min(range[0], range[1]), m_limits[0], m_limits[1]), rmax = clip(max(range[0], range[1]), m_limits[0], m_limits[1]);
        if(m_range[0] != rmin && m_range[1] != rmax)
        {
            m_range[0] = rmin;
            m_range[1] = rmax;
            redraw();
        }
    }
    
    void GuiScrollBar::Controller::scrollToStart() noexcept
    {
        if(m_range[0] != m_limits[0])
        {
            const double offset = m_range[0] - m_limits[0];
            m_range[0] -= offset;
            m_range[1] -= offset;
            redraw();
        }
    }
    
    void GuiScrollBar::Controller::scrollToEnd() noexcept
    {
        if(m_range[1] != m_limits[1])
        {
            const double offset = m_limits[1] - m_range[1];
            m_range[0] += offset;
            m_range[1] += offset;
            if(m_visible)
            {
                redraw();
            }
        }
    }
    
    void GuiScrollBar::Controller::scrollTo(const double position) noexcept
    {
        double const start = max(position - (m_range[1] - m_range[0]), m_limits[0]);
        if(start != m_range[0])
        {
            m_range[1] += start - m_range[0];
            m_range[0] = start;
            if(m_visible)
            {
                redraw();
            }
        }
    }    
}
















