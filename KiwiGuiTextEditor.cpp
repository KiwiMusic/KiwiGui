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

#include "KiwiGuiModel.h"
#include "KiwiGuiDevice.h"

namespace Kiwi
{
	// ================================================================================ //
	//                                      SKETCHER                                    //
	// ================================================================================ //
	
    GuiSketcher::GuiSketcher(sGuiContext context) noexcept :
    m_context(context)
	{
        ;
	}
	
	GuiSketcher::~GuiSketcher() noexcept
	{
        {
            lock_guard<mutex> guard(m_views_mutex);
            m_views.clear();
        }
        {
            lock_guard<mutex> guard(m_childs_mutex);
            m_childs.clear();
        }
	}
    
    sGuiDeviceManager GuiSketcher::getDeviceManager() const noexcept
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            return ctxt->getDeviceManager();
        }
        return sGuiDeviceManager();
    }
    
    sGuiView GuiSketcher::createView() noexcept
    {
        sGuiDeviceManager device = getDeviceManager();
        if(device)
        {
            sGuiController ctrl = createController();
            if(ctrl)
            {
                sGuiView view;
                try
                {
                    view = device->createView(ctrl);
                }
                catch(exception& e)
                {
                    return sGuiView();
                }
                if(view)
                {
                    lock_guard<mutex> guard(m_views_mutex);
                    m_views.insert(view);
                }
                return view;
            }
        }
        return sGuiView();
    }
    
    void GuiSketcher::removeView(sGuiView view) noexcept
    {
        if(view)
        {
            m_views.erase(view);
        }
    }
    
    void GuiSketcher::redraw() noexcept
    {
        lock_guard<mutex> guard(m_views_mutex);
        auto it = m_views.begin();
        while(it != m_views.end())
        {
            if((*it).expired())
            {
                it = m_views.erase(it);
            }
            else
            {
                sGuiView view = (*it).lock();
                view->redraw();
                ++it;
            }
        }
    }
    
    void GuiSketcher::add(sGuiSketcher child) noexcept
    {
        if(child)
        {
            lock_guard<mutex> guard(m_childs_mutex);
            if(m_childs.insert(child).second)
            {
                lock_guard<mutex> guard_view(m_views_mutex);
                auto it = m_views.begin();
                while(it != m_views.end())
                {
                    if((*it).expired())
                    {
                        it = m_views.erase(it);
                    }
                    else
                    {
                        sGuiView view = (*it).lock();
                        sGuiView childview = child->createView();
                        if(childview)
                        {
                            try
                            {
                                view->add(childview);
                            }
                            catch(exception& e)
                            {
                                ;
                            }
                        }
                        ++it;
                    }
                }
            }
        }
    }
    
    void GuiSketcher::remove(sGuiSketcher child) noexcept
    {
        if(child)
        {
            lock_guard<mutex> guard(m_childs_mutex);
            if(m_childs.erase(child))
            {
                lock_guard<mutex> guard_view(m_views_mutex);
                auto it = m_views.begin();
                while(it != m_views.end())
                {
                    if((*it).expired())
                    {
                        it = m_views.erase(it);
                    }
                    else
                    {
                        sGuiView view = (*it).lock();
                        int todo;
                        ++it;
                    }
                }
            }
        }
    }
    
    // ================================================================================ //
    //                                      MOUSER                                      //
    // ================================================================================ //
    
    GuiMouser::GuiMouser() noexcept
    {
        ;
    }
    
    GuiMouser::~GuiMouser() noexcept
    {
        ;
    }
    
    // ================================================================================ //
    //                                      KEYBOARDER                                  //
    // ================================================================================ //
    
    GuiKeyboarder::GuiKeyboarder() noexcept
    {
        ;
    }
    
    GuiKeyboarder::~GuiKeyboarder() noexcept
    {
        ;
    }
}