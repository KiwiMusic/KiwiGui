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

#include "KiwiGuiWindow.h"
#include "KiwiGuiDevice.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI WINDOW                                      //
    // ================================================================================ //
	
    GuiWindow::GuiWindow(sGuiContext context, string const& name, Color const& color, const ulong buttons, const bool show) noexcept : GuiSketcher(context)
    {
        setPosition(Point(0., 0.));
        setSize(Size(800., 600.));
        setBackgroundColor(Color(1., 1., 1., 0.));
    }
    
    GuiWindow::~GuiWindow() noexcept
    {
        ;
    }
    
    void GuiWindow::setTitle(string const& title) noexcept
    {
        
    }
    
    void GuiWindow::setBackgroundColor(Color const& color) noexcept
    {
        m_color = color;
        redraw();
    }
    
    void GuiWindow::setButtons(const ulong buttons) noexcept
    {
        
    }
    

    void GuiWindow::draw(scGuiController ctrl, Sketch& sketch) const
    {
        sketch.setColor(m_color);
        sketch.fillRectangle(sketch.getBounds(), 4.);
    }
    
    void GuiWindow::display()
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            sGuiView view = createView();
            if(view)
            {
                view->addToDesktop();
                ctxt->addWindow(view);
            }
        }
    }
    
    sGuiController GuiWindow::createController()
    {
        return make_shared<GuiWindow::Controller>(shared_from_this());
    }
    
    // ================================================================================ //
    //                              GUI WINDOW CONTROLLER                               //
    // ================================================================================ //
    
    GuiWindow::Controller::Controller(sGuiWindow window) noexcept :
    GuiController(window),
    m_window(window)
    {
        ;
    }

    GuiWindow::Controller::~Controller() noexcept
    {
        ;
    }
    
    bool GuiWindow::Controller::receive(MouseEvent const& event)
    {
        if(event.isDown())
        {
            m_last_position = getMousePosition();
        }
        else if(event.isDrag())
        {
            m_window->setPosition(m_window->getPosition() + getMousePosition() - m_last_position);
            m_last_position = getMousePosition();
        }
        return true;
    }
    
    // ================================================================================ //
    //                              GUI WINDOW CONTAINER                                //
    // ================================================================================ //
    
    GuiWindow::Container::Container(sGuiWindow window) noexcept :
    GuiSketcher(window->getContext()),
    m_window(window)
    {
        
    }
    
    GuiWindow::Container::~Container() noexcept
    {
        
    }
    
    sGuiController GuiWindow::Container::createController()
    {
        return make_shared<GuiController>(shared_from_this());
    }
}
















