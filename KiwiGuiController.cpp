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
    
    void GuiController::redraw() noexcept
    {
        sGuiView view = getView();
        if(view)
        {
            view->redraw();
        }
    }
    
    void GuiController::setBounds(Rectangle const& bounds) noexcept
    {
        m_bounds = bounds;
        sGuiView view = getView();
        if(view)
        {
            view->boundsChanged();
        }
    }
    
    void GuiController::setBounds(Rectangle&& bounds) noexcept
    {
        m_bounds = forward<Rectangle>(bounds);
        sGuiView view = getView();
        if(view)
        {
            view->boundsChanged();
        }
    }
    
    void GuiController::setPosition(Point const& position) noexcept
    {
        m_bounds.position(position);
        sGuiView view = getView();
        if(view)
        {
            view->positionChanged();
        }
    }
    
    void GuiController::setPosition(Point&& position) noexcept
    {
        m_bounds.position(forward<Point>(position));
        sGuiView view = getView();
        if(view)
        {
            view->positionChanged();
        }
    }
    
    void GuiController::setSize(Size const& size) noexcept
    {
        m_bounds.size(size);
        sGuiView view = getView();
        if(view)
        {
            view->sizeChanged();
        }
    }
    
    void GuiController::setSize(Size&& size) noexcept
    {
        m_bounds.size(forward<Size>(size));
        sGuiView view = getView();
        if(view)
        {
            view->sizeChanged();
        }
    }
    
    void GuiController::draw(sGuiView view, Sketch& sketch)
    {
        getSketcher()->draw(view, sketch);
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
}
















