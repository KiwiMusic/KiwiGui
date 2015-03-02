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

#ifndef __DEF_KIWI_GUI_DEVICE__
#define __DEF_KIWI_GUI_DEVICE__

#include "KiwiGuiPatcherManager.h"

namespace Kiwi
{
    //! The gui device manager owns the informations....
    /**
     The gui device manager
     */
    class GuiDeviceManager
    {
	private:
		vector<sGuiPatcherManager>	m_managers;
		mutable mutex			m_mutex;
		
	public:
		
		//! The constructor.
		/** The function does nothing.
		 */
		GuiDeviceManager() noexcept;
		
		//! The destructor.
		virtual ~GuiDeviceManager() noexcept;
		
		//! Add a page manager to the device manager.
		/** The function adds a page manager to the device manager.
		 @param page manager The page manager to add.
		 */
		void add(sGuiPatcherManager manager);
		
		//! Remove a page manager from the device manager.
		/** The function removes a page manager from the device manager.
		 @param page manager The page manager to remove.
		 */
		void remove(sGuiPatcherManager manager);
		
		//! Retrieve the number of page managers.
		/** The function retrieves the number of page managers.
		 @return The number of page managers.
		 */
		inline ulong getNumberOfGuiPatcherManager() const noexcept
		{
			lock_guard<mutex> guard(m_mutex);
			return (ulong)m_managers.size();
		}
    };
}

#endif


