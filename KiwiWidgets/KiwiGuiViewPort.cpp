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

#include "KiwiGuiViewPort.h"
#include "KiwiGuiDevice.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI VIEW PORT                                   //
    // ================================================================================ //
    
    GuiViewPort::GuiViewPort(sGuiContext context) noexcept : GuiSketcher(context),
    m_container(make_shared<GuiContainer>(context)),
    m_scrollbar_h(make_shared<GuiScrollBar>(context, GuiScrollBar::Horizontal)),
    m_scrollbar_v(make_shared<GuiScrollBar>(context, GuiScrollBar::Vertical))
    {
        Rectangle bounds = getBounds();
        m_container->setBounds(bounds);
        m_scrollbar_h->setBounds(Rectangle(0., bounds.height() - 10., bounds.width(), 10.));
        m_scrollbar_v->setBounds(Rectangle(bounds.width() - 10., 0., 10., bounds.height()));

        addChild(m_container);
        addChild(m_scrollbar_h);
        addChild(m_scrollbar_v);
    }
    
    GuiViewPort::~GuiViewPort() noexcept
    {
        ;
    }
    
    void GuiViewPort::setContent(sGuiSketcher sketcher) noexcept
    {
        if(m_content)
        {
            m_container->removeContent(sketcher);
        }
        m_container->addContent(sketcher);
        m_container->setBounds(getBounds());
    }
    
    void GuiViewPort::setContentPosition(Point const& position)
    {
        m_container->setPosition(-position);
        //m_container->setSize(getSize() + Size(position.x(), position.y()));
    }
    
    bool GuiViewPort::notify(sAttr attr)
    {
        if(attr->getName() == Tags::size)
        {
            const Point pos = m_container->getPosition();
            m_container->setSize(getSize());
            //m_container->setSize(getSize() + Size(pos.x(), pos.y()));
        }
        return true;
    }

}
















