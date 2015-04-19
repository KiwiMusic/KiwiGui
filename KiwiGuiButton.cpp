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

#include "KiwiGuiButton.h"
#include "KiwiGuiDevice.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI BUTTON                                      //
    // ================================================================================ //
	
    GuiButton::GuiButton(sGuiContext context, Color const& color) noexcept : GuiSketcher(context),
    m_color(color)
    {
        ;
    }
    

    GuiButton::~GuiButton() noexcept
    {
        ;
    }
    
    void GuiButton::setColor(Color const& color) noexcept
    {
        if(color != m_color)
        {
            m_color = color;
            redraw();
        }
    }
    
    void GuiButton::draw(scGuiView view, Sketch& sketch) const
    {
        const Rectangle bounds = getBounds().withZeroOrigin();
        sketch.setColor(getColor().darker(0.1));
        sketch.fillEllipse(bounds);
        sketch.setColor(getColor());
        sketch.fillEllipse(bounds.reduced(0.5));
    }
    
    bool GuiButton::receive(scGuiView view, MouseEvent const& event)
    {
        if(event.isDown())
        {
            lock_guard<mutex> guard(m_lists_mutex);
            auto it = m_lists.begin();
            while(it != m_lists.end())
            {
                sListener listener = (*it).lock();
                if(listener)
                {
                    listener->buttonPressed(static_pointer_cast<GuiButton>(shared_from_this()));
                    ++it;
                }
                else
                {
                    it = m_lists.erase(it);
                }
            }
        }
        return true;
    }
    
    void GuiButton::addListener(sListener listener)
    {
        if(listener)
        {
            lock_guard<mutex> guard(m_lists_mutex);
            m_lists.insert(listener);
        }
    }
    
    void GuiButton::removeListener(sListener listener)
    {
        if(listener)
        {
            lock_guard<mutex> guard(m_lists_mutex);
            m_lists.erase(listener);
        }
    }

}
















