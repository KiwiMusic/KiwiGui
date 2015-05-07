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
        lock_guard<mutex> guard1(m_views_mutex);
        m_views.clear();
        lock_guard<mutex> guard2(m_childs_mutex);
        m_childs.clear();
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
            sGuiController ctrl;
            try
            {
                ctrl = createController();
            }
            catch(exception& e)
            {
                return sGuiView();
            }
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
                    bool status = false;
                    {
                        lock_guard<mutex> guard(m_views_mutex);
                        status = m_views.insert(view).second;
                    }
                    if(status)
                    {
                        ctrl->setView(view);
                        vector<sGuiSketcher> childs(getChilds());
                        for(auto it : childs)
                        {
                            sGuiView childview = it->createView();
                            if(childview)
                            {
                                view->addChild(childview);
                            }
                        }
                        viewCreated(view);
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
            bool status = false;
            {
                lock_guard<mutex> guard(m_views_mutex);
                status = bool(m_views.erase(view));
            }
            if(status)
            {
                viewRemoved(view);
            }
        }
    }
    
    vector<sGuiView> GuiSketcher::getViews() noexcept
    {
        vector<sGuiView> views;
        lock_guard<mutex> guard(m_views_mutex);
        auto it = m_views.begin();
        while(it != m_views.end())
        {
            sGuiView view = (*it).lock();
            if(view)
            {
                views.push_back(view);
                ++it;
            }
            else
            {
                it = m_views.erase(it);
            }
        }
        return views;
    }
    
    vector<sGuiView> GuiSketcher::getViews() const noexcept
    {
        vector<sGuiView> views;
        lock_guard<mutex> guard(m_views_mutex);
        auto it = m_views.begin();
        while(it != m_views.end())
        {
            sGuiView view = (*it).lock();
            if(view)
            {
                views.push_back(view);
                ++it;
            }
        }
        return views;
    }
    
    sGuiView GuiSketcher::getFirstView() const noexcept
    {
        lock_guard<mutex> guard(m_views_mutex);
        auto it = m_views.begin();
        while(it != m_views.end())
        {
            sGuiView view = (*it).lock();
            if(view)
            {
                return view;
            }
        }
        return sGuiView();
    }
    
    bool GuiSketcher::hasView(sGuiView view) const noexcept
    {
        lock_guard<mutex> guard(m_views_mutex);
        return m_views.find(view) != m_views.end();
    }
    
    void GuiSketcher::redraw(sGuiView view) noexcept
    {
        if(view && hasView(view))
        {
            view->redraw();
        }
        else
        {
            vector<sGuiView> views(getViews());
            for(auto it : views)
            {
                it->redraw();
            }
        }
    }
    
    void GuiSketcher::grabFocus(sGuiView view) noexcept
    {
        if(view && hasView(view))
        {
            view->grabFocus();
        }
        else
        {
            view = getFirstView();
            if(view)
            {
                view->grabFocus();
            }
        }
    }
    
    vector<sGuiSketcher> GuiSketcher::getChilds() noexcept
    {
        vector<sGuiSketcher> childs;
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
                childs.push_back(child);
                ++it;
            }
        }
        return childs;
    }
    
    vector<sGuiSketcher> GuiSketcher::getChilds() const noexcept
    {
        vector<sGuiSketcher> childs;
        lock_guard<mutex> guard(m_childs_mutex);
        auto it = m_childs.begin();
        while(it != m_childs.end())
        {
            sGuiSketcher child = (*it).lock();
            if(child)
            {
                childs.push_back(child);
                ++it;
            }
        }
        return childs;
    }
    
    void GuiSketcher::addChild(sGuiSketcher child) noexcept
    {
        if(child)
        {
            bool status = false;
            {
                lock_guard<mutex> guard(m_childs_mutex);
                status  = m_childs.insert(child).second;
            }
            if(status)
            {
                vector<sGuiView> views(getViews());
                for(auto it : views)
                {
                    it->addChild(child->createView());
                }
            }
        }
    }
    
    void GuiSketcher::removeChild(sGuiSketcher child) noexcept
    {
        if(child)
        {
            bool status = false;
            {
                lock_guard<mutex> guard(m_childs_mutex);
                status = bool(m_childs.erase(child));
            }
            if(status)
            {
                vector<sGuiView> childviews = child->getViews();
                for(auto it : childviews)
                {
                    sGuiView view = it->getParent();
                    if(view && hasView(it->getParent()))
                    {
                        view->removeChild(it);
                    }
                }
            }
        }
    }
    
    sGuiController GuiSketcher::createController()
    {
        return make_shared<GuiController>(static_pointer_cast<GuiSketcher>(shared_from_this()));
    }
}