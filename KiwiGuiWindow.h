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

#ifndef __DEF_KIWI_GUI_WINDOW__
#define __DEF_KIWI_GUI_WINDOW__

#include "KiwiGuiView.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI WINDOW                                      //
    // ================================================================================ //
    
    class GuiWindow
    {
    public:
        class Manager;
    private:
        set<sGuiView>   m_views;
        mutex           m_mutex;
    public:
        
        enum TitleButtons
        {
            minimiseButton  = 1,
            maximiseButton  = 2,
            closeButton     = 4,
            allButtons      = 7
        };
        
        //! The window constructor.
        /** The function does nothing.
         */
        GuiWindow(string const& title = "untitled",
                  Color const& color = Color(0., 0., 0., 1.),
                  const long buttons = allButtons,
                  const bool show = true) noexcept;
        
        //! The window destructor.
        /** The function does nothing.
         */
        virtual ~GuiWindow() noexcept;
        
        //! Adds a sketcher to the window.
        /** The function adds a sketcher to the window.
         @param sketcher The sketcher.
         */
        void add(sGuiSketcher sketcher);
        
        //! Sets the title of the window
        /** The function sets the title of the window.
         @param title The title.
         */
        virtual void setTitle(string const& title) = 0;
        
    private:
        
        //! Display a view .
        /** The function should display the view in the window.
         @param view The view.
         */
        virtual void display(sGuiView view) = 0;
        
    };
    
    // ================================================================================ //
    //                                  GUI WINDOW MANAGER                              //
    // ================================================================================ //
    
    class GuiWindow::Manager
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
        Manager(sGuiDeviceManager device) noexcept;
        
        //! The destructor.
        /** Close all the windows.
         */
        ~Manager() noexcept;
        
        //! Retrieves the device manager.
        /** The function retrieves the device manager of the context.
         @return The device manager.
         */
        inline sGuiDeviceManager getDeviceManager() const noexcept
        {
            return m_device.lock();
        }
        
        //! Creates a window.
        /** The function creates a window and shows it.
         @return The window.
         */
        sGuiWindow createWindow() noexcept;
        
        //! Shows a window.
        /** The function shows a window.
         @param The window.
         */
        void showWindow(sGuiWindow window) noexcept;
        
        //! Minimize a window.
        /** The function minimizes a window.
         @param The window.
         */
        void minimizeWindow(sGuiWindow window) noexcept;
        
        //! Maximize a window.
        /** The function maximize a window.
         @param The window.
         */
        void maximizeWindow(sGuiWindow window) noexcept;
        
        //! Close a window.
        /** The function closes a window.
         @param The window.
         */
        void closeWindow(sGuiWindow window) noexcept;
    };
}

#endif


