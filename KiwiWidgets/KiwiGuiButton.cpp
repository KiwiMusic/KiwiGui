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
	
    GuiButton::GuiButton(sGuiContext context, Color const& color) noexcept : GuiModel(context),
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
    
    void GuiButton::draw(sController ctrl, Sketch& sketch) const
    {
        const Rectangle bounds = ctrl->getBounds().withZeroOrigin();
        sketch.setColor(m_background_color.darker(0.1));
        sketch.setLineWidth(1.);
        sketch.drawRectangle(bounds);
        sketch.setColor(m_background_color);
        sketch.fillRectangle(bounds.reduced(0.5));
    }
    
    bool GuiButton::receive(sController ctrl, MouseEvent const& event)
    {
        return event.isUp() && ctrl->contains(event.getPosition() + ctrl->getPosition());
    }
    
    sGuiController GuiButton::createController()
    {
        return make_shared<Controller>(static_pointer_cast<GuiButton>(shared_from_this()));
    }
    
    // ================================================================================ //
    //                              GUI BUTTON CONTROLLER                               //
    // ================================================================================ //
    
    GuiButton::Controller::Controller(sGuiButton button) noexcept :
    GuiController(button),
    m_button(button)
    {
        setBounds(Rectangle(0.,0., 20., 20.));
        shouldReceiveMouse(true);
        shouldReceiveKeyboard(false);
        shouldReceiveActions(false);
    }
    
    bool GuiButton::Controller::receive(sGuiView view, MouseEvent const& event)
    {
        sGuiButton button(getButton());
        if(button)
        {
            if(button->receive(static_pointer_cast<Controller>(shared_from_this()), event))
            {
                vector<sListener> listeners(getListeners());
                for(auto it : listeners)
                {
                    it->buttonPressed(button);
                }
                return true;
            }
        }
        return false;
    }
    
    void GuiButton::Controller::draw(sGuiView view, Sketch& sketch)
    {
        sGuiButton button(getButton());
        if(button)
        {
            button->draw(static_pointer_cast<Controller>(shared_from_this()), sketch);
        }
    }
}
















