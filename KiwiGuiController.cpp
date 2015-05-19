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

#include "KiwiGuiController.h"
#include "KiwiGuiDevice.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      GUI CONTROLLER                              //
    // ================================================================================ //
    
    GuiController::GuiController(sGuiModel model) noexcept :
    m_context(model->getContext()), m_model(model),
    m_bounds(), m_want_mouse(false), m_want_keyboard(false), m_want_action(false)
    {
        
    }
    
    sGuiController GuiController::getParent() const noexcept
    {
        sGuiView view = getView();
        if(view)
        {
            view = view->getParent();
            if(view)
            {
                return view->getController();
            }
        }
        return sGuiController();
    }
    
    vector<sGuiController> GuiController::getChilds() const noexcept
    {
        vector<sGuiController> childs;
        sGuiView view = getView();
        if(view)
        {
            for(auto it : view->getChilds())
            {
                childs.push_back(it->getController());
            }
        }
        return childs;
    }
    
    void GuiController::shouldReceiveMouse(const bool accept, const bool acceptOnChildren) noexcept
    {
        if(m_want_mouse != accept)
        {
            m_want_mouse = accept;
        }
        if(m_want_mouse_on_children != acceptOnChildren)
        {
            m_want_mouse_on_children = acceptOnChildren;
        }
    }
    
    void GuiController::shouldReceiveKeyboard(const bool wanted) noexcept
    {
        if(m_want_keyboard != wanted)
        {
            m_want_keyboard = wanted;
            sGuiView view = getView();
            if(view)
            {
                view->setWantKeyboard(wanted);
            }
        }
    }
    
    void GuiController::shouldReceiveActions(const bool wanted) noexcept
    {
        if(m_want_action != wanted)
        {
            m_want_action = wanted;
            sGuiView view = getView();
            if(view)
            {
                view->setWantActions(wanted);
            }
        }
    }
    
    void GuiController::setBounds(Rectangle const& newBounds) noexcept
    {
        setBounds(Rectangle(newBounds));
    }
    
    void GuiController::setBounds(Rectangle&& bounds) noexcept
    {
        Rectangle newBounds = forward<Rectangle>(bounds);
        const Rectangle oldBounds = getBounds();
        
        if(m_bounds_checker)
        {
            m_bounds_checker->check(newBounds, oldBounds);
        }
        
        const bool moved = newBounds.position() != oldBounds.position();
        const bool resized = newBounds.size() != oldBounds.size();
        
        if(moved || resized)
        {
            m_bounds = newBounds;
            
            sGuiView view = getView();
            if(view)
            {
                if(!resized)
                {
                    this->moved();
                    view->positionChanged();
                }
                else if(!moved)
                {
                    this->resized();
                    view->sizeChanged();
                }
                else
                {
                    this->moved();
                    this->resized();
                    view->boundsChanged();
                }
            }
            
            sGuiController parent(getParent());
            if(parent)
            {
                parent->childBoundsChanged(shared_from_this());
            }
            for(auto it : getChilds())
            {
                it->parentBoundsChanged();
            }
        }
    }
    
    void GuiController::setPosition(Point const& position) noexcept
    {
        setBounds(m_bounds.withPosition(position));
    }
    
    void GuiController::setPosition(Point&& position) noexcept
    {
        setBounds(m_bounds.withPosition(forward<Point>(position)));
    }
    
    void GuiController::setSize(Size const& size) noexcept
    {
        setBounds(m_bounds.withSize(size));
    }
    
    void GuiController::setSize(Size&& size) noexcept
    {
        setBounds(m_bounds.withSize(forward<Size>(size)));
    }
    
    void GuiController::setBoundsChecker(sBoundsChecker boundsChecker) noexcept
    {
        m_bounds_checker = boundsChecker;
    }
    
    bool GuiController::hitTest(Point const& pt) const noexcept
    {
        if (m_want_mouse)
        {
            return true;
        }
        
        if(m_want_mouse_on_children)
        {
            for(auto c : getChilds())
            {
                if(c)
                {
                    const Rectangle cBounds = c->getBounds();
                    const Point localpt = pt - cBounds.position();
                    if(localpt >= cBounds.position() &&
                       localpt <= Point(cBounds.right(), cBounds.bottom()) &&
                       c->hitTest(localpt))
                    {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
    
    bool GuiController::contains(Point const& pt) const noexcept
    {
        return m_bounds.contains(pt);
    }
    
    bool GuiController::overlaps(Rectangle const& rect) const noexcept
    {
        return m_bounds.overlaps(rect);
    }
    
    Point GuiController::getMousePosition() const noexcept
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            return ctxt->getMousePosition();
        }
        else
        {
            return Point();
        }
    }
    
    Point GuiController::getMouseRelativePosition() const noexcept
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            Point pt = ctxt->getMousePosition() - getPosition();
            sGuiView view = getView();
            if(view)
            {
                while((view = view->getParent()))
                {
                    sGuiController ctrl = view->getController();
                    if(ctrl)
                    {
                        pt -= ctrl->getPosition();
                    }
                }
            }
            return pt;
        }
        else
        {
            return Point();
        }
    }
    
    void GuiController::redraw() noexcept
    {
        sGuiView view = getView();
        if(view)
        {
            view->redraw();
        }
    }
    
    void GuiController::grabFocus() noexcept
    {
        sGuiView view = getView();
        if(view)
        {
            view->grabFocus();
        }
    }
    
    void GuiController::toBack() noexcept
    {
        sGuiView view = getView();
        if(view)
        {
            view->toBack();
        }
    }
    
    void GuiController::toFront() noexcept
    {
        sGuiView view = getView();
        if(view)
        {
            view->toFront();
        }
    }
    
    void GuiController::alwaysOnTop(const bool onTop) noexcept
    {
        sGuiView view = getView();
        if(view)
        {
            view->alwaysOnTop(onTop);
        }
    }
    
    void GuiController::setMouseCursor(MouseCursor const& cursor) noexcept
    {
        sGuiView view = getView();
        if(view)
        {
            view->setMouseCursor(cursor);
        }
    }
}

