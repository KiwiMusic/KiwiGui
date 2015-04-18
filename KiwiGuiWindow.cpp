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
	
    GuiWindow::GuiWindow(sGuiContext context, Color const& color) noexcept : GuiSketcher(context),
    m_container(make_shared<GuiContainer>(context))
    {
        setPosition(Point(0., 0.));
        setSize(Size(800., 600.));
        setBackgroundColor(Color(1., 1., 1., 0.));
        add(m_container);
        m_container->setSize(getSize());
    }
    
    GuiWindow::~GuiWindow() noexcept
    {
        ;
    }
    void GuiWindow::setBackgroundColor(Color const& color) noexcept
    {
        if(m_color != color)
        {
            m_color = color;
            redraw();
        }
    }

    void GuiWindow:: draw(scGuiView ctrl, Sketch& sketch) const
    {
        sketch.setColor(m_color);
        sketch.fillRectangle(sketch.getBounds(), 4.);
    }
    
    void GuiWindow::addContent(sGuiSketcher sketcher) noexcept
    {
        m_container->addContent(sketcher);
    }
    
    void GuiWindow::removeContent(sGuiSketcher sketcher) noexcept
    {
        m_container->removeContent(sketcher);
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
    
    void GuiWindow::close()
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            vector<sGuiView> views = getViews();
            for(vector<sGuiView>::size_type i = 0; i < views.size(); i++)
            {
                views[i]->removeFromDesktop();
                ctxt->removeWindow(views[i]);
            }
        }
    }
    
    void GuiWindow::minimize()
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            vector<sGuiView> views = getViews();
            for(vector<sGuiView>::size_type i = 0; i < views.size(); i++)
            {
                views[i]->setMinimize(true);
            }
        }
    }
    
    // ================================================================================ //
    //                              GUI WINDOW HEADER                                   //
    // ================================================================================ //
    
    GuiWindow::Header::Header(sGuiWindow window,
                              string const& title,
                              Color const& bgcolor,
                              Color const& bdcolor,
                              Color const& txtcolor) noexcept :
    GuiSketcher(window->getContext()),
    m_window(window),
    m_button_close(make_shared<GuiButton>(getContext(), Colors::red.brighter(0.4))),
    m_button_minimize(make_shared<GuiButton>(getContext(), Colors::yellow.brighter(0.4))),
    m_button_maximize(make_shared<GuiButton>(getContext(), Colors::green.brighter(0.4))),
    m_title(title),
    m_bg_color(bgcolor),
    m_bd_color(bdcolor),
    m_txt_color(txtcolor)
    {
        setPosition(Point(0., 0.));
        setSize(Size(window->getSize().width(), 24.));
        m_button_close->setBounds(Rectangle(6., 6., 12., 12.));
        m_button_minimize->setBounds(Rectangle(24, 6., 12., 12.));
        m_button_maximize->setBounds(Rectangle(42, 6., 12., 12.));
    }
    
    GuiWindow::Header::~Header() noexcept
    {
        ;
    }
    
    void GuiWindow::Header::setTitle(string const& title) noexcept
    {
        if(title != m_title)
        {
            m_title = title;
            redraw();
        }
    }
    
    void GuiWindow::Header::setButtons(const ulong buttons) noexcept
    {
        if(buttons != m_buttons)
        {
            if((buttons & closeButton) && !(m_buttons & closeButton))
            {
                add(m_button_close);
                m_button_close->addListener(getShared());
            }
            else if(!(buttons & closeButton) && (m_buttons & closeButton))
            {
                remove(m_button_close);
                m_button_close->removeListener(getShared());
            }
            if((buttons & minimiseButton) && !(m_buttons & minimiseButton))
            {
                add(m_button_minimize);
                m_button_minimize->addListener(getShared());
            }
            else if(!(buttons & minimiseButton) && (m_buttons & minimiseButton))
            {
                remove(m_button_minimize);
                m_button_minimize->removeListener(getShared());
            }
            if((buttons & maximiseButton) && !(m_buttons & maximiseButton))
            {
                add(m_button_maximize);
                m_button_maximize->addListener(getShared());
            }
            else if(!(buttons & maximiseButton) && (m_buttons & maximiseButton))
            {
                remove(m_button_maximize);
                m_button_maximize->removeListener(getShared());
            }
            m_buttons = buttons;
        }
    }
    
    void GuiWindow::Header::setBackgroundColor(Color const& color) noexcept
    {
        if(color != m_bg_color)
        {
            m_bg_color = color;
            redraw();
        }
    }
    
    void GuiWindow::Header::setBorderColor(Color const& color) noexcept
    {
        if(color != m_bd_color)
        {
            m_bd_color = color;
            redraw();
        }
    }
    
    void GuiWindow::Header::setTextColor(Color const& color) noexcept
    {
        if(color != m_txt_color)
        {
            m_txt_color = color;
            redraw();
        }
    }
    
    void GuiWindow::Header::draw(scGuiView view, Sketch& sketch) const
    {
        sketch.fillAll(m_bg_color);
        sketch.setColor(m_bd_color);
        sketch.drawRectangle(sketch.getBounds().withZeroOrigin(), 1.);
        sketch.setColor(m_txt_color);
        sketch.drawText(m_title, 60., 0., sketch.getBounds().width() - 120., sketch.getBounds().height(), Font::Centred);
    }
    
    bool GuiWindow::Header::receive(scGuiView view, MouseEvent const& event)
    {
        if(event.isDown())
        {
            m_last_pos = getMousePosition();
        }
        else if(event.isDrag())
        {
            const Point position = getMousePosition();
            sGuiWindow window = getWindow();
            if(window)
            {
                window->setPosition(window->getPosition() + position - m_last_pos);
            }
            m_last_pos = position;
        }
        else if(event.isDoubleClick())
        {
            sGuiWindow window = getWindow();
            if(window)
            {
                sGuiContext ctxt = getContext();
                if(ctxt)
                {
                    const Rectangle bounds = window->getBounds();
                    const Rectangle screen = ctxt->getScreenBounds(bounds.centre());
                    if(screen == bounds)
                    {
                        window->setBounds(m_last_bounds);
                    }
                    else
                    {
                        m_last_bounds = bounds;
                        window->setBounds(screen);
                    }
                }
            }
        }
        return true;
    }
    
    void GuiWindow::Header::buttonPressed(sGuiButton button)
    {
        if(button == m_button_close)
        {
            sGuiWindow window = getWindow();
            if(window)
            {
                window->close();
            }
        }
        else if(button == m_button_minimize)
        {
            sGuiWindow window = getWindow();
            if(window)
            {
                window->minimize();
            }
        }
        else if(button == m_button_maximize)
        {
            sGuiWindow window = getWindow();
            if(window)
            {
                
            }
        }
    }
}
















