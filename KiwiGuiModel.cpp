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
	//                                      MODEL                                       //
	// ================================================================================ //
	
    GuiModel::GuiModel(sGuiContext context) noexcept :
    m_context(context)
    {
        ;
    }
    
	GuiModel::~GuiModel() noexcept
	{
        lock_guard<mutex> guard1(m_views_mutex);
        m_views.clear();
        lock_guard<mutex> guard2(m_childs_mutex);
        m_childs.clear();
	}
    
    sGuiDeviceManager GuiModel::getDeviceManager() const noexcept
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            return ctxt->getDeviceManager();
        }
        return sGuiDeviceManager();
    }
    
    Point GuiModel::getMousePosition() const noexcept
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            return ctxt->getMousePosition();
        }
        return Point();
    }
    
    sGuiView GuiModel::createView() noexcept
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
                        vector<sGuiModel> childs(getChilds());
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
    
    void GuiModel::removeView(sGuiView view) noexcept
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
    
    vector<sGuiView> GuiModel::getViews() const noexcept
    {
        lock_guard<mutex> guard(m_views_mutex);
        return vector<sGuiView>(m_views.begin(), m_views.end());
    }
    
    sGuiView GuiModel::getFirstView() const noexcept
    {
        lock_guard<mutex> guard(m_views_mutex);
        if(!m_views.empty())
        {
            return *m_views.begin();
        }
        return sGuiView();
    }
    
    bool GuiModel::hasView(sGuiView view) const noexcept
    {
        lock_guard<mutex> guard(m_views_mutex);
        return m_views.find(view) != m_views.end();
    }
    
    void GuiModel::redraw(sGuiView view) noexcept
    {
        if(view && hasView(view))
        {
            view->redraw();
        }
        else
        {
            const vector<sGuiView> views(getViews());
            for(auto it : views)
            {
                it->redraw();
            }
        }
    }
    
    void GuiModel::grabFocus(sGuiView view) noexcept
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
    
    vector<sGuiModel> GuiModel::getChilds() const noexcept
    {
        lock_guard<mutex> guard(m_childs_mutex);
        return vector<sGuiModel>(m_childs.begin(), m_childs.end());
    }
    
    void GuiModel::addChild(sGuiModel child) noexcept
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
                const vector<sGuiView> views(getViews());
                for(auto it : views)
                {
                    it->addChild(child->createView());
                }
            }
        }
    }
    
    void GuiModel::removeChild(sGuiModel child) noexcept
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
                const vector<sGuiView> childviews = child->getViews();
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
}