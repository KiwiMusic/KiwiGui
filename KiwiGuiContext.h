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
        set<sGuiView>           m_windows;
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
        
        //! Adds a top level window to the context.
        /** The function adds a the view of a top level window to the context.
         @param window The view of the top level window.
         */
        void addWindow(sGuiView window) noexcept;
        
        //! Removes a top level window from the context.
        /** The function removes a the view of a top level window from the context.
         @param window The view of the top level window.
         */
        void removeWindow(sGuiView window) noexcept;
        
        //! Retrieves the width of a line.
        /** The function retreives the width of a line depending on a font.
         @param font The font.
         @param line The line.
         @return The width of the line.
         */
        double getLineWidth(Font const& font, string const& line) const noexcept;
        
        //! Retrieves the width of a line.
        /** The function retreives the width of a line depending on a font.
         @param font The font.
         @param line The line.
         @return The width of the line.
         */
        double getLineWidth(Font const& font, wstring const& line) const noexcept;
        
        //! Retrieves the size of a text.
        /** The function the size of a text depending on a font.
         @param font The font.
         @param text The text.
         @param width The width limit of the text, zero means no limits.
         @return The width of the text.
         */
        Size getTextSize(Font const& font, string const& text, const double width = 0.) const noexcept;
        
        //! Retrieves the size of a text.
        /** The function the width of a text depending on a font.
         @param font The font.
         @param text The text.
         @param width The width limit of the text, zero means no limits.
         @return The width of the text.
         */
        Size getTextSize(Font const& font, wstring const& text, const double width_limit = 0.) const noexcept;
    };
}

#endif


