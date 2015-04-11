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
	public:
		
		//! The constructor.
		/** The function does nothing.
		 */
		GuiDeviceManager() noexcept;
		
		//! The destructor.
		virtual ~GuiDeviceManager() noexcept;
        
        //! Create a view.
        /** The function creates a view for a controller.
         @param ctrl The controller linked with the view.
         @return The view.
         */
        virtual sGuiView createView(sGuiController ctrl) const noexcept
        {
            return sGuiView();
        }
        
        //! Create a window.
        /** The function creates a window.
         @return The window.
         */
        virtual sGuiWindow createWindow() const noexcept
        {
            return sGuiWindow();
        }
        
    };
}

#endif


