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
    m_background_color(color)
    {
        ;
    }
    
    void GuiButton::setBackgroundColor(Color const& color) noexcept
    {
        if(color != m_background_color)
        {
            m_background_color = color;
            redraw();
        }
    }
    
    void GuiButton::draw(scGuiView view, Sketch& sketch) const
    {
        const Rectangle bounds = view->getBounds().withZeroOrigin();
        sketch.setColor(m_background_color.darker(0.1));
        sketch.setLineWidth(1.);
        sketch.drawRectangle(bounds);
        sketch.setColor(m_background_color);
        sketch.fillEllipse(bounds.reduced(0.5));
    }
    
    bool GuiButton::valid(scGuiView view, MouseEvent const& event)
    {
        return event.isDown();
    }
    
    // ================================================================================ //
    //                              GUI BUTTON CONTROLLER                               //
    // ================================================================================ //
    
    GuiButton::Controller::Controller(sGuiButton button) noexcept :
    GuiController(button->getContext()),
    m_button(button)
    {
        shouldReceiveMouse(true);
        shouldReceiveKeyboard(false);
        shouldReceiveActions(false);
    }
    
    bool GuiButton::Controller::receive(sGuiView view, MouseEvent const& event)
    {
        if(m_button->valid(view, event))
        {
            vector<sListener> listeners(getListeners());
            for(auto it : listeners)
            {
                it->buttonPressed(m_button);
            }
            return true;
        }
        return false;
    }
}
















