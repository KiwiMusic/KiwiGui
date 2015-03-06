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

namespace Kiwi
{
    // ================================================================================ //
    //                                     GUI PATCHER                                  //
    // ================================================================================ //
	
	GuiPatcher::GuiPatcher(sGuiPatchManager manager) noexcept :
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
		m_boxes.clear();
		m_links.clear();
	}
	
	sGuiDeviceManager GuiPatcher::getDeviceManager() const noexcept
	{
		sGuiPatchManager instance = getGuiPatchManager();
		if(instance)
		{
			return instance->getDeviceManager();
		}
		
		return nullptr;
	}
	
	void GuiPatcher::add(sGuiObject box)
	{
		if(box)
		{
			lock_guard<mutex> guard(m_mutex);
			if(find(m_boxes.begin(), m_boxes.end(), box) == m_boxes.end())
			{
				m_boxes.push_back(box);
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
			}
		}
	}
	
	void GuiPatcher::remove(sGuiObject box)
	{
		if(box)
		{
			lock_guard<mutex> guard(m_mutex);
			auto it = find(m_boxes.begin(), m_boxes.end(), box);
			if(it != m_boxes.end())
			{
				m_boxes.erase(it);
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
			}
		}
	}
}
















