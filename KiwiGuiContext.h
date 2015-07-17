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

#include "KiwiGuiView.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI CONTEXT                                     //
    // ================================================================================ //
    
    class GuiContext
    {
    private:
        const wGuiDeviceManager m_device;
        
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
        
        //! Create a view.
        /** The function creates a view for a controller.
         @param ctrl The controller linked with the view.
         @return The view.
         */
        sGuiView createView(sGuiController ctrl) const noexcept;
        
        //! Retrieves the mouse absolute position.
        /** The function retrieves the mouse absolute position.
         @return The mouse absolute position.
         */
        Point getMousePosition() const noexcept;
        
        //! Retrieves the screen bounds.
        /** The function retrieves the screen bounds for a point. Since there can be several screens, the point determines wichs screen to select.
         @param pt The point.
         @return The screen bounds.
         */
        Rectangle getScreenBounds(Point const& pt) const noexcept;
    };
}

#endif


