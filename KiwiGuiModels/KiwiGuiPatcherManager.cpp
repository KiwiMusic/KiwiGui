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

#include "KiwiGuiPatcherManager.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                     GUI INSTANCE                                 //
    // ================================================================================ //
	
	GuiPatcherManager::GuiPatcherManager(sGuiDeviceManager device) noexcept :
	m_device(device)
	{
		;
	}
	
	GuiPatcherManager::~GuiPatcherManager()
	{
		m_pages.clear();
	}
	
	void GuiPatcherManager::add(sGuiPatcher page)
	{
		if(page)
		{
			lock_guard<mutex> guard(m_mutex);
			if(find(m_pages.begin(), m_pages.end(), page) == m_pages.end())
			{
				m_pages.push_back(page);
			}
		}
	}
	
	void GuiPatcherManager::remove(sGuiPatcher page)
	{
		bool success = false;
		if(page)
		{
			lock_guard<mutex> guard(m_mutex);
			auto it = find(m_pages.begin(), m_pages.end(), page);
			if(it != m_pages.end())
			{
				m_pages.erase(it);
				success = true;
			}
		}
		if(success)
		{
			//remove window ?
		}
	}
}
















