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

#include "KiwiGuiContainer.h"
#include "KiwiGuiDevice.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI CONTAINER                                   //
    // ================================================================================ //
	
    GuiContainer::GuiContainer(sGuiContext context) noexcept : GuiSketcher(context)
    {
        ;
    }
    
    GuiContainer::~GuiContainer() noexcept
    {
        ;
    }

    void GuiContainer::addContent(sGuiSketcher sketcher) noexcept
    {
        addChild(sketcher);
    }
    
    void GuiContainer::removeContent(sGuiSketcher sketcher) noexcept
    {
        removeChild(sketcher);
    }
    
    // ================================================================================ //
    //                                  GUI VIEW PORT                                   //
    // ================================================================================ //
    
    GuiViewPort::GuiViewPort(sGuiContext context) noexcept : GuiSketcher(context),
    m_container(make_shared<GuiContainer>(context))
    {
        m_container->setBounds(getBounds());
        addChild(m_container);
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
















