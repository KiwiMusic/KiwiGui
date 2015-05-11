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
    
    void GuiController::shouldReceiveMouse(const bool accept) noexcept
    {
        if(m_want_mouse != accept)
        {
            m_want_mouse = accept;
            sGuiView view = getView();
            if(view)
            {
                view->behaviorChanged();
            }
        }
    }
    
    void GuiController::shouldReceiveKeyboard(const bool accept) noexcept
    {
        if(m_want_keyboard != accept)
        {
            m_want_keyboard = accept;
            sGuiView view = getView();
            if(view)
            {
                view->behaviorChanged();
            }
        }
    }
    
    void GuiController::shouldReceiveActions(const bool accept) noexcept
    {
        if(m_want_action != accept)
        {
            m_want_action = accept;
            sGuiView view = getView();
            if(view)
            {
                view->behaviorChanged();
            }
        }
    }
    
    void GuiController::setBounds(Rectangle const& bounds) noexcept
    {
        m_bounds = bounds;
        sGuiView view = getView();
        if(view)
        {
            view->boundsChanged();
            this->boundsChanged();
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
    
    void GuiController::setBounds(Rectangle&& bounds) noexcept
    {
        m_bounds = forward<Rectangle>(bounds);
        sGuiView view = getView();
        if(view)
        {
            view->boundsChanged();
            this->boundsChanged();
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
        m_bounds.position(position);
        sGuiView view = getView();
        if(view)
        {
            view->positionChanged();
            this->boundsChanged();
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
    
    void GuiController::setPosition(Point&& position) noexcept
    {
        m_bounds.position(forward<Point>(position));
        sGuiView view = getView();
        if(view)
        {
            view->positionChanged();
            this->boundsChanged();
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
    
    void GuiController::setSize(Size const& size) noexcept
    {
        m_bounds.size(size);
        sGuiView view = getView();
        if(view)
        {
            view->sizeChanged();
            this->boundsChanged();
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
    
    void GuiController::setSize(Size&& size) noexcept
    {
        m_bounds.size(forward<Size>(size));
        sGuiView view = getView();
        if(view)
        {
            view->sizeChanged();
            this->boundsChanged();
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
    
    bool GuiController::contains(Point const& pt)
    {
        return m_bounds.contains(pt);
    }
    
    bool GuiController::overlaps(Rectangle const& rect)
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
}
















