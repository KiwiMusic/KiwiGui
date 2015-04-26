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
        createAttr(Tags::position,  "Position", "Appearance", Point(0., 0.));
        createAttr(Tags::size,      "Size",     "Appearance", Size(10., 10.));
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
                    {
                        lock_guard<mutex> guard(m_views_mutex);
                        m_views.insert(view);
                        addListener(view, {Tags::position, Tags::size});
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
                    viewCreated(view);
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
            lock_guard<mutex> guard(m_views_mutex);
            m_views.erase(view);
            removeListener(view, {Tags::position, Tags::size});
            viewRemoved(view);
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
    
    sGuiView GuiSketcher::getFirstView() noexcept
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
            else
            {
                it = m_views.erase(it);
            }
        }
        return sGuiView();
    }
    
    bool GuiSketcher::hasView(sGuiView view) noexcept
    {
        lock_guard<mutex> guard(m_views_mutex);
        return m_views.find(view) != m_views.end();
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
    
    void GuiSketcher::setBounds(Rectangle const& bounds) noexcept
    {
        setPosition(bounds.position());
        setSize(bounds.size());
    }
    
    void GuiSketcher::setPosition(Point const& position) noexcept
    {
        setAttrValue(Tags::position, position);
    }
    
    void GuiSketcher::setSize(Size const& size) noexcept
    {
        setAttrValue(Tags::size, size);
    }
    
    void GuiSketcher::addChild(sGuiSketcher child) noexcept
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
    
    void GuiSketcher::removeChild(sGuiSketcher child) noexcept
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
        return make_shared<GuiController>(static_pointer_cast<GuiSketcher>(shared_from_this()));
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