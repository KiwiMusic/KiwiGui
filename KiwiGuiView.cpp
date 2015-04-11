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

namespace Kiwi
{
    // ================================================================================ //
    //                                      GUI VIEW                                    //
    // ================================================================================ //
	
    GuiView::GuiView(sGuiController ctrl) noexcept :
    m_controller(ctrl)
    {
        ;
    }
    
    GuiView::~GuiView() noexcept
    {
        lock_guard<mutex> guard(m_childs_mutex);
        m_childs.clear();
    }

    void GuiView::add(sGuiView child) noexcept
    {
        if(child)
        {
            lock_guard<mutex> guard(m_childs_mutex);
            if(find(m_childs.begin(), m_childs.end(), child) == m_childs.end())
            {
                m_childs.push_back(child);
                try
                {
                    addChild(child);
                }
                catch(exception& e)
                {
                    
                }
            }
        }
    }
    
    void GuiView::remove(sGuiView child) noexcept
    {
        if(child)
        {
            lock_guard<mutex> guard(m_childs_mutex);
            auto it = find(m_childs.begin(), m_childs.end(), child);
            if(it != m_childs.end())
            {
                m_childs.erase(it);
                try
                {
                    removeChild(child);
                }
                catch(exception& e)
                {
                    
                }
            }
        }
    }
    
    bool GuiView::receive(MouseEvent const& event)
    {
        if(m_controller->wantMouse())
        {
            return m_controller->receive(event);
        }
        else
        {
            return false;
        }
    }
    
    bool GuiView::receive(KeyboardEvent const& event)
    {
        if(m_controller->wantKeyboard())
        {
            return m_controller->receive(event);
        }
        else
        {
            return false;
        }
    }
    
    bool GuiView::receive(KeyboardFocus event)
    {
        if(m_controller->wantKeyboard())
        {
            return m_controller->receive(event);
        }
        else
        {
            return false;
        }
    }
}
















