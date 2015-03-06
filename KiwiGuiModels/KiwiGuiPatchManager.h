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

#ifndef __DEF_KIWI_GUI_CONTEXT__
#define __DEF_KIWI_GUI_CONTEXT__

#include "KiwiGuiPatcher.h"

namespace Kiwi
{
    //! The gui context
    /**
     The gui context
     */
	class GuiPatchManager : public inheritable_enable_shared_from_this<GuiPatchManager>
    {
	private:
		const wGuiDeviceManager m_device;
		vector<sGuiPatcher>           m_pages;
		mutable mutex           m_mutex;
		
    public:
		
		//! The constructor.
		/** The function initialize and empty context.
		 @param device The gui device manager.
		 */
		GuiPatchManager(sGuiDeviceManager device) noexcept;
		
		//! The destructor.
		/** Stop the digital signal processing if needed and free the chains.
		 */
		virtual ~GuiPatchManager();
		
		//! Retrieve the gui device manager of the context.
		/** This function retrieves the gui device manager.
		 @return The gui device manager.
		 */
		inline sGuiDeviceManager getDeviceManager() const noexcept
		{
			return m_device.lock();
		}
		
		//! Retrieve the number of page.
		/** The function retrieves the number of page.
		 @return The number of page.
		 */
		inline ulong getNumberOfGuiPatcher() const noexcept
		{
			lock_guard<mutex> guard(m_mutex);
			return (ulong)m_pages.size();
		}
		
		//! Add a page to the gui context.
		/** The function adds a page to the gui context.
		 @param page The page to remove.
		 */
		void add(sGuiPatcher page);
		
		//! Remove a page from the gui context.
		/** The function removes a page from the gui context.
		 @param page The page to remove.
		 */
		void remove(sGuiPatcher page);
    };
}

#endif


