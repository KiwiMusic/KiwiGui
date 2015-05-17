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
        if(rect.contains(pt))
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
    
    MouseCursor GuiResizer::Controller::getCursorForZone() const noexcept
    {
        MouseCursor mc;
        switch(m_zone)
        {
            case CornerTopLeft:         mc = MouseCursor::ResizingTopLeft; break;
            case CornerBottomLeft:      mc = MouseCursor::ResizingBottomLeft; break;
            case CornerTopRight:        mc = MouseCursor::ResizingTopRight; break;
            case CornerBottomRight:     mc = MouseCursor::ResizingBottomRight; break;
            case BorderLeft:            mc = MouseCursor::RezizingLeftRight; break;
            case BorderRight:           mc = MouseCursor::RezizingLeftRight; break;
            case BorderBottom:          mc = MouseCursor::RezizingUpDown; break;
            case BorderTop:             mc = MouseCursor::RezizingUpDown; break;
            default: break;
        }
        return mc;
    }
    
    ulong GuiResizer::Controller::getRectangleBorders() const noexcept
    {
        switch(m_zone)
        {
            case BorderLeft:            return (Rectangle::Left);
            case BorderRight:           return (Rectangle::Right);
            case BorderBottom:          return (Rectangle::Bottom);
            case BorderTop:             return (Rectangle::Top);
            case CornerTopLeft:         return (Rectangle::Top | Rectangle::Left);
            case CornerBottomLeft:      return (Rectangle::Bottom | Rectangle::Left);
            case CornerTopRight:        return (Rectangle::Top | Rectangle::Right);
            case CornerBottomRight:     return (Rectangle::Bottom | Rectangle::Right);
            default: break;
        }
        return 0;
    }
    
    bool GuiResizer::Controller::hitTest(Point const& pt) const noexcept
    {
        sGuiResizer resizer(getResizer());
        if(resizer)
        {
            return resizer->getZone(getLocalBounds(), pt) != Zone::Nothing;
        }
        return false;
    }
    
    bool GuiResizer::Controller::contains(Point const& pt) const noexcept
    {
        sGuiResizer resizer(getResizer());
        if(resizer)
        {
            return resizer->getZone(getBounds(), pt) != Zone::Nothing;
        }
        return false;
    }
    
    bool GuiResizer::Controller::receive(sGuiView view, MouseEvent const& event)
    {
        if(event.isMove())
        {
            sGuiResizer resizer(getResizer());
            if(resizer)
            {
                m_zone = resizer->getZone(getBounds(), event.getPosition());
                setMouseCursor(getCursorForZone());
            }
            return true;
        }
        if(event.isDown())
        {
            sGuiResizer resizer(getResizer());
            sGuiController parent(getParent());
            if(parent && resizer)
            {
                //Size size(parent->getSize().width(), parent->getSize().height(), 100., 100., 1.);
                m_last_bounds = parent->getBounds();
                m_zone        = resizer->getZone(getBounds(), event.getPosition());
                setMouseCursor(getCursorForZone());
            }
            return true;
        }
        else if(event.isDrag())
        {
            sGuiController parent(getParent());
            sGuiContext ctx = getContext();
            if(parent && ctx)
            {
                const Point delta = event.getPosition() - event.getDownPosition();
                
                const Rectangle newrect = m_last_bounds.resized(getRectangleBorders(),
                                                                delta, Point(100., 32.), Point(0., 0.),
                                                                event.hasShift(), event.hasAlt());
                
                const Rectangle sb = ctx->getScreenBounds(newrect.centre());
                parent->setBounds(newrect.withClippedEdges(sb.left(), sb.top(), sb.right(), sb.bottom()));
                setMouseCursor(getCursorForZone());
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
