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

#include "KiwiGuiWindow.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI CONTEXT                                     //
    // ================================================================================ //
    
    class GuiContext
    {
    private:
        const wGuiDeviceManager m_device;
        set<sGuiWindow>         m_windows;
        mutex                   m_mutex;
        
    public:
        //! The constructor.
        /** The function initialize and empty context.
         @param device The device manager.
         */
        GuiContext(sGuiDeviceManager device) noexcept;
        
        //! The destructor.
        /** Close all the windows.
         */
        ~GuiContext() noexcept;
        
        //! Retrieves the device manager.
        /** The function retrieves the device manager of the context.
         @return The device manager.
         */
        inline sGuiDeviceManager getDeviceManager() const noexcept
        {
            return m_device.lock();
        }
        
        //! Create a window.
        /** The function creates a window.
         @return The window.
         */
        sGuiWindow createWindow() noexcept;
    };
}

#endif


