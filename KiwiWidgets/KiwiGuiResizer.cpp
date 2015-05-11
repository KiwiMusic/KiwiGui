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

#include "KiwiGuiResizer.h"
#include "KiwiGuiDevice.h"

namespace Kiwi
{
    GuiResizer::Zone GuiResizer::getZone(Rectangle const& rect, Point const& pt) const noexcept
    {
        const bool left     = pt.x() < m_size;
        const bool right    = pt.x() > rect.width() - m_size;
        const bool top      = pt.y() < m_size;
        const bool bottom   = pt.y() > rect.height() - m_size;
        if(m_zones & CornerTopLeft && left && top)
        {
            return CornerTopLeft;
        }
        else if(m_zones & CornerBottomLeft && left && bottom)
        {
            return CornerBottomLeft;
        }
        else if(m_zones & CornerTopRight && right && top)
        {
            return CornerTopRight;
        }
        else if(m_zones & CornerBottomRight && right && bottom)
        {
            return CornerBottomRight;
        }
        else if(m_zones & BorderLeft && left)
        {
            return BorderLeft;
        }
        else if(m_zones & BorderRight && right)
        {
            return BorderRight;
        }
        else if(m_zones & BorderTop && top)
        {
            return BorderTop;
        }
        else if(m_zones & BorderBottom && bottom)
        {
            return BorderBottom;
        }
        return Zone::Nothing;
    }
    
    sGuiController GuiResizer::createController()
    {
        return make_shared<Controller>(static_pointer_cast<GuiResizer>(shared_from_this()));
    }
    
    GuiResizer::Controller::Controller(sGuiResizer resizer) noexcept : GuiController(resizer),
    m_resizer(resizer)
    {
        shouldReceiveMouse(true);
        shouldReceiveKeyboard(false);
        shouldReceiveActions(false);
    }
    
    bool GuiResizer::Controller::contains(Point const& pt)
    {
        sGuiResizer resizer(getResizer());
        if(resizer)
        {
            return resizer->getZone(getBounds(), pt) != Zone::Nothing;
        }
        else
        {
            return false;
        }
    }
    
    bool GuiResizer::Controller::receive(sGuiView view, MouseEvent const& event)
    {
        if(event.isMove())
        {
            sGuiResizer resizer(getResizer());
            if(resizer)
            {
                m_zone = resizer->getZone(getBounds(), event.getPosition());
            }
            return true;
        }
        if(event.isDown())
        {
            sGuiResizer resizer(getResizer());
            sGuiController parent(getParent());
            if(parent && resizer)
            {
                m_last_bounds = parent->getBounds();
                m_zone        = resizer->getZone(getBounds(), event.getPosition());
            }
            return true;
        }
        else if(event.isDrag())
        {
            sGuiController parent(getParent());
            if(parent)
            {
                switch(m_zone)
                {
                    case CornerTopLeft:
                        ;
                        break;
                    case CornerBottomLeft:
                        ;
                        break;
                    case CornerTopRight:
                        ;
                        break;
                    case CornerBottomRight:
                        ;
                        break;
                    case BorderLeft:
                    {
                        const double left = m_last_bounds.left() + event.getPosition().x() - event.getDownPosition().x();
                        parent->setBounds(Rectangle(left, m_last_bounds.y(), m_last_bounds.right() - left, m_last_bounds.height()));
                    }
                        break;
                    case BorderRight:
                    {
                        const double width = m_last_bounds.width() + event.getPosition().x() - event.getDownPosition().x();
                        parent->setBounds(Rectangle(m_last_bounds.position(), Size(width, m_last_bounds.height())));
                    }
                        break;
                    case BorderBottom:
                    {
                        const double height = m_last_bounds.height() + event.getPosition().y() - event.getDownPosition().y();
                        parent->setBounds(Rectangle(m_last_bounds.position(), Size(m_last_bounds.width(), height)));
                    }
                        break;
                    case BorderTop:
                    {
                        const double top = m_last_bounds.top() + event.getPosition().y() - event.getDownPosition().y();
                        parent->setBounds(Rectangle(m_last_bounds.x(), top, m_last_bounds.width(), m_last_bounds.bottom() - top));
                    }
                        break;
                        
                    default:
                        break;
                }
            }
            return true;
        }
        else
        {
            m_zone = Zone::Nothing;
        }
        return false;
    }
    
    void GuiResizer::Controller::parentChanged() noexcept
    {
        sGuiController parent(getParent());
        if(parent)
        {
            setBounds(parent->getBounds().withZeroOrigin());
            toFront();
        }
    }
    
    void GuiResizer::Controller::parentBoundsChanged() noexcept
    {
        sGuiController parent(getParent());
        if(parent)
        {
            setBounds(parent->getBounds().withZeroOrigin());
        }
    }
}
















