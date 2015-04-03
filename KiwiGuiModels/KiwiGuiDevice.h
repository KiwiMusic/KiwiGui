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

#include "KiwiGuiContext.h"

namespace Kiwi
{
    //! The gui device manager owns the informations....
    /**
     The gui device manager
     */
    class GuiDeviceManager
    {
	private:
		vector<sGuiContext> m_managers;
		mutex               m_mutex;
		
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
		void add(sGuiContext manager);
		
		//! Remove a page manager from the device manager.
		/** The function removes a page manager from the device manager.
		 @param page manager The page manager to remove.
		 */
		void remove(sGuiContext manager);
        
        //! Retrieve the patcher managers.
        /** The function retrieves  the patcher managers.
         @return The patcher managers.
         */
        inline vector<sGuiContext> getPatcherManagers() const noexcept
        {
            return m_managers;
        }
        
        //! Create the view of a patcher depending on the implementation.
        /** The function retrieves the view of a patcher depending on the implementation.
         @param patcher The patcher.
         @return The patcher view.
         */
        virtual GuiPatcher::sView createView(sGuiPatcher patcher)
        {
            return nullptr;
        }
    };
}

#endif


