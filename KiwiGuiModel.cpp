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
    
    Point GuiSketcher::getMousePosition() const noexcept
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            return ctxt->getMousePosition();
        }
        return Point();
    }
    
    sGuiView GuiSketcher::createView() noexcept
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            sGuiController ctrl = createController();
            if(ctrl)
            {
                sGuiView view;
                try
                {
                    view = ctxt->createView(ctrl);
                }
                catch(exception& e)
                {
                    return sGuiView();
                }
                if(view)
                {
                    {
                        lock_guard<mutex> guard(m_views_mutex);
                        m_views.insert(view);
                        ctrl->setView(view);
                    }
                    {
                        lock_guard<mutex> guard(m_childs_mutex);
                        auto it = m_childs.begin();
                        while(it != m_childs.end())
                        {
                            sGuiSketcher child = (*it).lock();
                            if(!child)
                            {
                                it = m_childs.erase(it);
                            }
                            else
                            {
                                sGuiView childview = child->createView();
                                if(childview)
                                {
                                    view->add(childview);
                                }
                                ++it;
                            }
                        }
                    }
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
    
    vector<sGuiView> GuiSketcher::getViews() noexcept
    {
        lock_guard<mutex> guard(m_views_mutex);
        return vector<sGuiView>(m_views.begin(), m_views.end());
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
    
    void GuiSketcher::setBounds(Rectangle const& bounds) noexcept
    {
        setPosition(bounds.position());
        setSize(bounds.size());
    }
    
    void GuiSketcher::setPosition(Point const& position) noexcept
    {
        m_position = position;
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
                view->move();
                ++it;
            }
        }
    }
    
    void GuiSketcher::setSize(Size const& size) noexcept
    {
        m_size = size;
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
                view->resize();
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
                vector<sGuiView> childviews = child->getViews();
                lock_guard<mutex> guard_view(m_views_mutex);
                for(vector<sGuiView>::size_type i = 0; i < childviews.size(); i++)
                {
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
                            if(view == childviews[i]->getParent())
                            {
                                view->remove(childviews[i]);
                            }
                            ++it;
                        }
                    }
                }
            }
        }
    }
    
    sGuiController GuiSketcher::createController()
    {
        return make_shared<GuiController>(shared_from_this());
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
    
    // ================================================================================ //
    //                                     ACTION MANAGER                               //
    // ================================================================================ //
    
    GuiActionManager::GuiActionManager() noexcept
    {
        ;
    }
    
    GuiActionManager::~GuiActionManager() noexcept
    {
        ;
    }
}