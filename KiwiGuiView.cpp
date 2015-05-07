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

#include "KiwiGuiView.h"
#include "KiwiGuiContext.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      GUI VIEW                                    //
    // ================================================================================ //
	
    GuiView::GuiView(sGuiController ctrl) noexcept :
    m_context(ctrl->getContext()),
    m_controller(ctrl)
    {
        ;
    }
    
    GuiView::~GuiView() noexcept
    {
        lock_guard<mutex> guard(m_childs_mutex);
        m_childs.clear();
    }
    
    Point GuiView::getGlobalPosition() const noexcept
    {
        Point pos = getPosition() + getParentPosition();
        sGuiView parent = getParent();
        while((parent = parent->getParent()))
        {
            pos += parent->getParentPosition();
        }
        return pos;
    }
    
    Point GuiView::getParentPosition() const noexcept
    {
        sGuiView parent = getParent();
        if(parent)
        {
            return parent->getPosition();
        }
        else
        {
            sGuiContext ctxt = getContext();
            if(ctxt)
            {
                return ctxt->getScreenBounds(getBounds().centre()).position();
            }
        }
        return Point();
    }
    
    Size GuiView::getParentSize() const noexcept
    {
        sGuiView parent = getParent();
        if(parent)
        {
            return parent->getParentSize();
        }
        else
        {
            sGuiContext ctxt = getContext();
            if(ctxt)
            {
                return ctxt->getScreenBounds(getBounds().centre()).size();
            }
        }
        return Size();
    }
    
    Rectangle GuiView::getParentBounds() const noexcept
    {
        sGuiView parent = getParent();
        if(parent)
        {
            return parent->getParentBounds();
        }
        else
        {
            sGuiContext ctxt = getContext();
            if(ctxt)
            {
                return ctxt->getScreenBounds(getBounds().centre());
            }
        }
        return Rectangle();
    }

    void GuiView::addChild(sGuiView child) noexcept
    {
        if(child)
        {
            lock_guard<mutex> guard(m_childs_mutex);
            if(find(m_childs.begin(), m_childs.end(), child) == m_childs.end())
            {
                m_childs.push_back(child);
                child->m_parent_view = shared_from_this();
                try
                {
                    addChildView(child);
                }
                catch(exception& e)
                {
                    
                }
            }
        }
    }
    
    void GuiView::removeChild(sGuiView child) noexcept
    {
        if(child)
        {
            lock_guard<mutex> guard(m_childs_mutex);
            auto it = find(m_childs.begin(), m_childs.end(), child);
            if(it != m_childs.end())
            {
                m_childs.erase(it);
                child->m_parent_view = sGuiView();
                try
                {
                    removeChildView(child);
                }
                catch(exception& e)
                {
                    
                }
            }
        }
    }
}
















