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

#include "KiwiGuiPatcher.h"
#include "KiwiGuiDevice.h"
#include "../KiwiGuiView/KiwiPatcherView.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                     GUI PATCHER                                  //
    // ================================================================================ //
	
	GuiPatcher::GuiPatcher(sGuiContext manager) noexcept :
    m_manager(manager),
    m_color_unlocked_background(Attr::create("unlocked_bgcolor","Unlocked Background Color", "Appearance", ColorValue(0.88, 0.89, 0.88, 1.))),
    m_color_locked_background(Attr::create("locked_bgcolor", "Locked Background Color", "Appearance", ColorValue(0.88, 0.89, 0.88, 1.))),
    m_gridsize(Attr::create("gridsize", "Grid Size", "Editing", LongValue(20)))
    {
        addAttr(m_color_unlocked_background);
        addAttr(m_color_locked_background);
        addAttr(m_gridsize);
    }
	
	GuiPatcher::~GuiPatcher()
	{
		lock_guard<mutex> guard(m_mutex);
		m_objects.clear();
		m_links.clear();
        m_views.clear();
	}
	
	sGuiDeviceManager GuiPatcher::getDeviceManager() const noexcept
	{
		sGuiContext manager = getContext();
		if(manager)
		{
			return manager->getDeviceManager();
		}
		
		return nullptr;
	}
    
    GuiPatcher::sPatcherView GuiPatcher::createView()
    {
        sGuiContext manager = getContext();
        if(manager)
        {
            return nullptr;//manager->createView();
        }
        
        return sPatcherView();
    }
	
	void GuiPatcher::add(sGuiObject object)
	{
		if(object)
		{
			lock_guard<mutex> guard(m_mutex);
			if(find(m_objects.begin(), m_objects.end(), object) == m_objects.end())
			{
				m_objects.push_back(object);
                send(object, Notification::Added);
			}
		}
	}
	
	void GuiPatcher::add(sGuiLink link)
	{
		if(link)
		{
			lock_guard<mutex> guard(m_mutex);
			if(find(m_links.begin(), m_links.end(), link) == m_links.end())
			{
				m_links.push_back(link);
                send(link, Notification::Added);
			}
		}
	}
	
	void GuiPatcher::remove(sGuiObject object)
	{
		if(object)
		{
			lock_guard<mutex> guard(m_mutex);
			auto it = find(m_objects.begin(), m_objects.end(), object);
			if(it != m_objects.end())
			{
				m_objects.erase(it);
                send(object, Notification::Removed);
			}
		}
	}
	
	void GuiPatcher::remove(sGuiLink link)
	{
		if(link)
		{
			lock_guard<mutex> guard(m_mutex);
			auto it = find(m_links.begin(), m_links.end(), link);
			if(it != m_links.end())
			{
				m_links.erase(it);
                send(link, Notification::Removed);
			}
		}
	}
    
    void GuiPatcher::toFront(sGuiObject object)
    {
        if(object)
        {
            lock_guard<mutex> guard(m_mutex);
            auto it = find(m_objects.begin(), m_objects.end(), object);
            if(it != m_objects.end())
            {
                m_objects.erase(it);
                m_objects.push_back(object);
            }
        }
    }
    
    void GuiPatcher::toBack(sGuiObject object)
    {
        if(object)
        {
            lock_guard<mutex> guard(m_mutex);
            auto it = find(m_objects.begin(), m_objects.end(), object);
            if(it != m_objects.end())
            {
                m_objects.erase(it);
                m_objects.insert(m_objects.begin(), object);
            }
        }
    }
    
    void GuiPatcher::send(sGuiObject object, GuiPatcher::Notification type)
    {
        if(object)
        {
            lock_guard<mutex> guard(m_views_mutex);
            for(auto it = m_views.begin(); it != m_views.end(); )
            {
                sPatcherView view = (*it).lock();
                if(view)
                {
                    if(type == Notification::Added)
                    {
                        view->objectCreated(object);
                    }
                    else
                    {
                        view->objectRemoved(object);
                    }
                    
                    ++it;
                }
                else
                {
                    it = m_views.erase(it);
                }
            }
        }
    }
    
    void GuiPatcher::send(sGuiLink link, GuiPatcher::Notification type)
    {
        if(link)
        {
            lock_guard<mutex> guard(m_views_mutex);
            for(auto it = m_views.begin(); it != m_views.end(); )
            {
                sPatcherView view = (*it).lock();
                if(view)
                {
                    if(type == Notification::Added)
                    {
                        view->linkCreated(link);
                    }
                    else
                    {
                        view->linkRemoved(link);
                    }
                    
                    ++it;
                }
                else
                {
                    it = m_views.erase(it);
                }
            }
        }
    }
}
















