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

#include "KiwiGuiViewport.h"
#include "KiwiGuiDevice.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI VIEWPORT                                    //
    // ================================================================================ //
    
    GuiViewport::GuiViewport(sGuiContext context) noexcept : GuiModel(context),
    m_scrollbar_h(make_shared<GuiScrollBar>(context, GuiScrollBar::Direction::Horizontal)),
    m_scrollbar_v(make_shared<GuiScrollBar>(context, GuiScrollBar::Direction::Vertical)),
    m_scrollbar_thickness(10)
    {
        addChild(m_scrollbar_h);
        addChild(m_scrollbar_v);
    }
    
    GuiViewport::~GuiViewport() noexcept
    {
        ;
    }
    
    void GuiViewport::setContent(sGuiModel model) noexcept
    {
        if(m_content != model)
        {
            if(m_content)
            {
                removeChild(m_content);
            }
            
            if(model)
            {
                m_content = model;
                addChild(model);
            }
        }
    }
    
    void GuiViewport::setScrollBarThickness(double thickness) noexcept
    {
        if(thickness < 0.) thickness = 0.;
        if(thickness != m_scrollbar_thickness)
        {
            m_scrollbar_thickness = thickness;
        }
    }
    
    sGuiController GuiViewport::createController()
    {
        return make_shared<Controller>(static_pointer_cast<GuiViewport>(shared_from_this()));
    }
    
    // ================================================================================ //
    //                                VIEWPORT CONTROLLER                               //
    // ================================================================================ //
    
    GuiViewport::Controller::Controller(sGuiViewport viewport) noexcept : GuiController(viewport),
    m_viewport(viewport)
    {
        shouldReceiveMouse(true, false);
    }
    
    void GuiViewport::Controller::resized() noexcept
    {
        const Rectangle bounds = getLocalBounds();
        
        if(m_content)
        {
            //m_content->setBounds(bounds.reduced(10));
            m_content->setBounds(bounds);
        }
        
        if(m_scrollbar_v || m_scrollbar_h)
        {
            sGuiViewport vp = getViewport();
            if(vp)
            {
                double thickness = vp->getScrollBarThickness();
                if(m_scrollbar_v)
                {
                    m_scrollbar_v->setBounds(bounds.withLeft(bounds.right() - thickness).withBottom(bounds.bottom() - thickness));
                }
                if(m_scrollbar_h)
                {
                    m_scrollbar_h->setBounds(bounds.withTop(bounds.bottom() - thickness).withRight(bounds.right() - thickness));
                }
            }
        }
    }
    
    void GuiViewport::Controller::childCreated(sGuiController child) noexcept
    {
        sGuiViewport vp = getViewport();
        if(vp && child)
        {
            sGuiModel childM = child->getModel();
            if(childM)
            {
                if(childM == vp->getContent())
                {
                    m_content = child;
                    resized();
                }
                else if(childM == vp->getVerticalScrollBar())
                {
                    m_scrollbar_v = static_pointer_cast<GuiScrollBar::Controller>(child);
                    resized();
                }
                else if(childM == vp->getHorizontalScrollBar())
                {
                    m_scrollbar_h = static_pointer_cast<GuiScrollBar::Controller>(child);
                    resized();
                }
            }
        }
    }
    
    void GuiViewport::Controller::childRemoved(sGuiController child) noexcept
    {
        sGuiViewport vp = getViewport();
        if(vp && child)
        {
            sGuiModel childM = child->getModel();
            if(childM)
            {
                if(childM == vp->getContent())
                {
                    m_content.reset();
                    resized();
                }
                else if(childM == vp->getVerticalScrollBar())
                {
                    m_scrollbar_v.reset();
                }
                else if(childM == vp->getHorizontalScrollBar())
                {
                    m_scrollbar_h.reset();
                }
            }
        }
    }
    
    bool GuiViewport::Controller::receive(sGuiView view, MouseEvent const& event)
    {
        if(event.isWheel())
        {
            cout << "vp wheel" << endl;
        }
        return false;
    }
    
    void GuiViewport::Controller::scrollBarMoved(GuiScrollBar::sController scrollbar)
    {
        
    }

}


