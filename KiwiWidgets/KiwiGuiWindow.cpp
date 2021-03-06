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
	
    GuiWindow::GuiWindow(sGuiContext context, const ulong zones, Color const& color) noexcept : GuiModel(context),
    m_resizer(make_shared<GuiResizer>(context, zones)),
    m_color(Colors::white),
    m_roundness(4.)
    {
        setBackgroundColor(color);
        addChild(m_resizer);
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
    
    void GuiWindow::setRoundness(double roundness) noexcept
    {
        if(roundness < 0.) roundness = 0.;
        if(roundness != m_roundness)
        {
            m_roundness = roundness;
            redraw();
        }
    }
    
    void GuiWindow::setHeader(sHeader header) noexcept
    {
        if(m_header)
        {
            removeChild(header);
            m_header = sHeader();
        }
        if(header)
        {
            addChild(header);
            m_header = header;
        }
    }
    
    void GuiWindow::setContent(sGuiModel content) noexcept
    {
        if(m_content)
        {
            removeChild(m_content);
            m_content = sGuiModel();
        }
        if(content)
        {
            m_content = content;
            addChild(content);
        }
    }
    
    void GuiWindow::addToDesktop() noexcept
    {
        removeFromDesktop();
        sGuiView view = createView();
        if(view)
        {
            sGuiContext ctxt = getContext();
            if(ctxt)
            {
                view->addToDesktop();
                ctxt->addTopLevelModel(shared_from_this());
            }
            else
            {
                removeView(view);
            }
        }
    }
    
    void GuiWindow::removeFromDesktop() noexcept
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            for(auto it : getViews())
            {
                it->removeFromDesktop();
                removeView(it);
            }
            
            ctxt->removeTopLevelModel(shared_from_this());
        }
    }
    
    sGuiController GuiWindow::createController()
    {
        return make_shared<Controller>(static_pointer_cast<GuiWindow>(shared_from_this()));
    }
    
    // ================================================================================ //
    //                              GUI WINDOW CONTROLLER                               //
    // ================================================================================ //
    
    GuiWindow::Controller::Controller(sGuiWindow window) noexcept : GuiController(window),
    m_window(window)
    {
        setBoundsChecker(make_shared<ScreenBoundsChecker>(window->getContext()));
        shouldReceiveMouse(false);
        shouldReceiveKeyboard(false);
        shouldReceiveActions(false);
        setBounds(Rectangle(30., 30., 1000., 600.));
    }

    void GuiWindow::Controller::close()
    {
        sGuiWindow window(getWindow());
        if(window)
        {
            window->removeFromDesktop();
        }
    }
    
    void GuiWindow::Controller::minimize()
    {
        sGuiView view = getView();
        if(view)
        {
            view->setMinimize(true);
        }
    }
    
    void GuiWindow::Controller::maximize()
    {
        sGuiContext ctxt(getContext());
        if(ctxt)
        {
            const Rectangle bounds = getBounds();
            const Rectangle screen = ctxt->getScreenBounds(bounds.centre());
            if(screen == bounds)
            {
                setBounds(m_last_bounds);
            }
            else
            {
                m_last_bounds = bounds;
                setBounds(screen);
            }
        }
    }
    
    void GuiWindow::Controller::draw(sGuiView view, Sketch& sketch)
    {
        sGuiWindow window(getWindow());
        if(window)
        {
            sketch.setColor(window->getBackgroundColor());
            sketch.fillRectangle(getBounds().withZeroOrigin(), window->getRoundness());
        }
    }
    
    void GuiWindow::Controller::drawOver(sGuiView view, Sketch& sketch)
    {
        sGuiWindow window = getWindow();
        if(window)
        {
            sketch.setColor(window->getBackgroundColor().contrasted(0.8));
            sketch.setLineWidth(3.);
            sketch.drawRectangle(getBounds().withZeroOrigin().reduced(1.5), window->getRoundness());
        }
    }
    
    void GuiWindow::Controller::childCreated(sGuiController child) noexcept
    {
        sGuiWindow window(getWindow());
        if(child && window)
        {
            sGuiModel model(child->getModel());
            if(model == window->m_resizer)
            {
                m_resizer = child;
                m_resizer->setBounds(getBounds());
                m_resizer->alwaysOnTop(true);
            }
            else if(model == window->getHeader())
            {
                m_header = child;
                const Rectangle bounds(getBounds().withZeroOrigin().reduced(2.));
                m_header->setBounds(bounds.withHeight(m_header->getSize().height()));
                
                if(m_content)
                {
                    m_content->setBounds(m_header ? bounds.withTop(m_header->getBounds().bottom()) : bounds);
                }
            }
            else if(model == window->getContent())
            {
                m_content = child;
                const Rectangle bounds(getBounds().withZeroOrigin().reduced(2.));
                m_content->setBounds(m_header ? bounds.withTop(m_header->getBounds().bottom()) : bounds);
            }
        }
    }
    
    void GuiWindow::Controller::childRemoved(sGuiController child) noexcept
    {
        if(child)
        {
            if(child == m_resizer)
            {
                m_resizer = sGuiController();
            }
            else if(child == m_header)
            {
                m_header = sGuiController();
                if(m_content)
                {
                    m_content->setBounds(getBounds().withZeroOrigin().reduced(2.));
                }
            }
            else if(child == m_content)
            {
                m_content = sGuiController();
            }
        }
    }
    
    void GuiWindow::Controller::resized() noexcept
    {
        const Rectangle bounds(getLocalBounds().reduced(2.));
        if(m_resizer)
        {
            m_resizer->setBounds(bounds);
        }
        if(m_header)
        {
            m_header->setBounds(bounds.withHeight(m_header->getSize().height()));
        }
        if(m_content)
        {
            m_content->setBounds(m_header ? bounds.withTop(m_header->getBounds().bottom()) : bounds);
        }
    }
    
    // ================================================================================ //
    //                              GUI WINDOW HEADER                                   //
    // ================================================================================ //
    
    GuiWindow::Header::Header(sGuiContext context,
                              string const& title,
                              ulong const buttons,
                              Color const& bgcolor,
                              Color const& txtcolor) noexcept :
    GuiModel(context),
    m_button_close(make_shared<GuiButton>(getContext(), Colors::red.brighter(0.4))),
    m_button_minimize(make_shared<GuiButton>(getContext(), Colors::yellow.brighter(0.4))),
    m_button_maximize(make_shared<GuiButton>(getContext(), Colors::green.brighter(0.4))),
    m_title(title),
    m_buttons(noButton),
    m_bg_color(bgcolor),
    m_txt_color(txtcolor)
    {
        setButtons(buttons);
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
                addChild(m_button_close);
            }
            else if(!(buttons & closeButton) && (m_buttons & closeButton))
            {
                removeChild(m_button_close);
            }
            if((buttons & minimiseButton) && !(m_buttons & minimiseButton))
            {
                addChild(m_button_minimize);
            }
            else if(!(buttons & minimiseButton) && (m_buttons & minimiseButton))
            {
                removeChild(m_button_minimize);
            }
            if((buttons & maximiseButton) && !(m_buttons & maximiseButton))
            {
                addChild(m_button_maximize);
            }
            else if(!(buttons & maximiseButton) && (m_buttons & maximiseButton))
            {
                removeChild(m_button_maximize);
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
    
    void GuiWindow::Header::setTextColor(Color const& color) noexcept
    {
        if(color != m_txt_color)
        {
            m_txt_color = color;
            redraw();
        }
    }
    
    void GuiWindow::Header::draw(sController ctrl, Sketch& sketch) const
    {
        const Rectangle bounds = ctrl->getBounds().withZeroOrigin();
        sketch.fillAll(m_bg_color.contrasted(0.8));
        sketch.setColor(m_bg_color.contrasted(0.4));
        //sketch.setColor(m_txt_color);
        Font font;
        font.setHeight(bounds.height() * 0.6);
        font.setStyle(Font::Bold);
        sketch.setFont(font);
        if(font.getLineWidth(m_title) < bounds.width() - 120)
        {
            sketch.drawTextLine(m_title, bounds, Font::Centred, false);
        }
        else
        {
            sketch.drawTextLine(m_title, 60., 0., bounds.width() - 64., bounds.height(), Font::Left, true);
        }
    }
    
    bool GuiWindow::Header::receive(sController ctrl, MouseEvent const& event)
    {
        return true;
    }
    
    sGuiController GuiWindow::Header::createController()
    {
        return make_shared<Header::Controller>(static_pointer_cast<Header>(shared_from_this()));
    }
    
    // ================================================================================ //
    //                          GUI WINDOW HEADER CONTROLLER                            //
    // ================================================================================ //
        
    GuiWindow::Header::Controller::Controller(sHeader header) noexcept : GuiController(header),
    m_header(header)
    {
        setBounds(Rectangle(0., 0., 800., 24.));
        shouldReceiveMouse(true);
        shouldReceiveKeyboard(false);
        shouldReceiveActions(false);
    }
    
    void GuiWindow::Header::Controller::draw(sGuiView view, Sketch& sketch)
    {
        sHeader header(getHeader());
        if(header)
        {
            header->draw(static_pointer_cast<Controller>(shared_from_this()), sketch);
        }
    }
    
    bool GuiWindow::Header::Controller::receive(sGuiView view, MouseEvent const& event)
    {
        if(event.isDown())
        {
            sGuiController pctrl(getParent());
            if(pctrl)
            {
                m_last_window_pos = pctrl->getPosition();
            }
            m_last_down_pos = getMousePosition();
            return true;
        }
        else if(event.isDrag())
        {
            sGuiController pctrl(getParent());
            if(pctrl)
            {
                pctrl->setPosition(m_last_window_pos + getMousePosition() - m_last_down_pos);
                return true;
            }
        }
        else if(event.isDoubleClick())
        {
            GuiWindow::sController pctrl(getWindowController());
            if(pctrl)
            {
                pctrl->maximize();
                return true;
            }
        }
        return false;
    }
    
    void GuiWindow::Header::Controller::buttonPressed(sGuiButton button)
    {
        sHeader header(getHeader());
        if(header && button)
        {
            GuiWindow::sController pctrl(getWindowController());
            if(pctrl)
            {
                if(button == header->getCloseButton())
                {
                    pctrl->close();
                }
                else if(button == header->getMinimizeButton())
                {
                    pctrl->minimize();
                }
                else if(button == header->getMaximizeButton())
                {
                    pctrl->maximize();
                }
            }
        }
    }
    
    void GuiWindow::Header::Controller::childCreated(sGuiController child) noexcept
    {
        sHeader header(getHeader());
        if(header && child)
        {
            const ulong buttons = header->getButtons();
            sGuiModel childm(child->getModel());
            if(childm == header->getCloseButton())
            {
                GuiButton::sController bctrl = static_pointer_cast<GuiButton::Controller>(child);
                bctrl->setBounds(Rectangle(6., 6., 12., 12.));
                bctrl->addListener(static_pointer_cast<Controller>(shared_from_this()));
            }
            else if(childm == header->getMinimizeButton())
            {
                GuiButton::sController bctrl = static_pointer_cast<GuiButton::Controller>(child);
                bctrl->setBounds(Rectangle(6. + (buttons && closeButton) * 18., 6., 12., 12.));
                bctrl->addListener(static_pointer_cast<Controller>(shared_from_this()));
            }
            else if(childm == header->getMaximizeButton())
            {
                GuiButton::sController bctrl = static_pointer_cast<GuiButton::Controller>(child);
                bctrl->setBounds(Rectangle(6. + (buttons && closeButton) * 18. + (buttons && minimiseButton) * 18., 6., 12., 12.));
                bctrl->addListener(static_pointer_cast<Controller>(shared_from_this()));
            }
        }
    }
    
    void GuiWindow::Header::Controller::childRemoved(sGuiController child) noexcept
    {
        sHeader header(getHeader());
        if(header && child)
        {
            const ulong buttons = header->getButtons();
            sGuiModel childm(child->getModel());
            if(childm == header->getCloseButton() || childm == header->getMinimizeButton() || childm == header->getMaximizeButton())
            {
                static_pointer_cast<GuiButton::Controller>(child)->removeListener(static_pointer_cast<Controller>(shared_from_this()));
                vector<sGuiController> childs(getChilds());
                for(auto it : getChilds())
                {
                    if(it->getModel() == header->getCloseButton())
                    {
                        GuiButton::sController bctrl = static_pointer_cast<GuiButton::Controller>(it);
                        bctrl->setBounds(Rectangle(6., 6., 12., 12.));
                        bctrl->addListener(static_pointer_cast<Controller>(shared_from_this()));
                    }
                    else if(it->getModel() == header->getMinimizeButton())
                    {
                        GuiButton::sController bctrl = static_pointer_cast<GuiButton::Controller>(it);
                        bctrl->setBounds(Rectangle(6. + (buttons && closeButton) * 18., 6., 12., 12.));
                        bctrl->addListener(static_pointer_cast<Controller>(shared_from_this()));
                    }
                    else if(it->getModel() == header->getMaximizeButton())
                    {
                        GuiButton::sController bctrl = static_pointer_cast<GuiButton::Controller>(it);
                        bctrl->setBounds(Rectangle(6. + (buttons && closeButton) * 18. + (buttons && minimiseButton) * 18., 6., 12., 12.));
                        bctrl->addListener(static_pointer_cast<Controller>(shared_from_this()));
                    }
                }
            }
        }
    }
    
    void GuiWindow::Header::Controller::parentChanged() noexcept
    {
        sGuiController parent(getParent());
        if(parent)
        {
            //setSize(Size(parent->getSize().width(), 24.));
            //toBack();
        }
    }
    
    void GuiWindow::Header::Controller::parentBoundsChanged() noexcept
    {
        sGuiController parent(getParent());
        if(parent)
        {
            //setSize(Size(parent->getSize().width(), 24.));
        }
    }
}

