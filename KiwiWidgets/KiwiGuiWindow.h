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

#include "KiwiGuiTextEditor.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI WINDOW                                      //
    // ================================================================================ //
    
    class GuiWindow : public GuiModel
    {
    public:
        class Header;
        typedef shared_ptr<Header>          sHeader;
        typedef weak_ptr<Header>            wHeader;
        typedef shared_ptr<const Header>    scHeader;
        typedef weak_ptr<const Header>      wcHeader;
        
    protected:
        class Controller;
        typedef shared_ptr<Controller>  sController;
        typedef weak_ptr<Controller>    wController;
        
    private:
        sHeader         m_header;
        Color           m_color;
    public:
        
        //! The window constructor.
        /** The function does nothing.
         @param context The context.
         @param title   The title of the window.
         @param color   The background color of the window.
         @param buttons The buttons available at the top of the window.
         @param show    If the window should be popup.
         */
        GuiWindow(sGuiContext context, Color const& color = Colors::white) noexcept;
        
        //! The window destructor.
        /** The function does nothing.
         */
        virtual ~GuiWindow() noexcept;
        
        //! Sets the background color of the window.
        /** The function sets the background color of the window.
         @param color The background color.
         */
        void setBackgroundColor(Color const& color) noexcept;
        
        //! Retreives the background color of the window.
        /** The function retreives the background color of the window.
         @return The background color.
         */
        inline Color getBackgroundColor() const noexcept {return m_color;}
        
        //! Add a new view of the window to the desktop
        /** The function adds new view of the window to the desktop
         */
        void addToDesktop() noexcept;
        
        //! Remove the view of the window to the desktop
        /** The function removes the view of the window from the desktop
         */
        void removeFromDesktop() noexcept;
        
        //! Create the controller.
        /** The function creates a controller for the window.
         @return The controller.
         */
        sGuiController createController() override;
    };
    
    // ================================================================================ //
    //                              GUI WINDOW CONTROLLER                               //
    // ================================================================================ //
    
    //! The window controller.
    /** The window controller manage a view of a window.
     */
    class GuiWindow::Controller : public GuiController
    {
    private:
        const wGuiWindow m_window;
    public:
        //! The window controller constructor.
        /** The function initialize the window controller.
         @param context The context.
         @param window  The window to control.
         */
        Controller(sGuiContext context, sGuiWindow window) noexcept;
        
        //! The controller destructor.
        /** The function does nothing.
         */
        inline ~Controller() noexcept {};
        
        //! Retreives the window of the controller.
        /** The function retreives the window of the controller.
         @return The window.
         */
        inline sGuiWindow getWindow() const noexcept {return m_window.lock();}
        
        //! Closes the window's view.
        /** This function removes the window's view from the desktop.
         */
        void close();
        
        //! Minimize the window's view.
        /** This function minimize the window's view.
         */
        void minimize();
        
        //! Maximize the window's view.
        /** This function maximize the window's view.
         */
        void maximize();
        
        //! The draw method that can be override.
        /** The function shoulds draw some stuff.
         @param view    The view that owns the controller.
         @param sketch  The sketch to draw.
         */
        void draw(sGuiView view, Sketch& sketch) override;
    };
    
    // ================================================================================ //
    //                              GUI WINDOW HEADER                                   //
    // ================================================================================ //
    
    class GuiWindow::Header : public GuiModel, public GuiMouser, public GuiButton::Listener
    {
    private:
        const wGuiWindow m_window;
        const sGuiButton m_button_close;
        const sGuiButton m_button_minimize;
        const sGuiButton m_button_maximize;
        string          m_title;
        long            m_buttons;
        Color           m_bg_color;
        Color           m_bd_color;
        Color           m_txt_color;
        Point           m_last_pos;
        Rectangle       m_last_bounds;
        
    public:
        
        enum TitleButtons
        {
            noButton        = 0,
            minimiseButton  = 1,
            maximiseButton  = 2,
            closeButton     = 4,
            allButtons      = 7
        };
        
        //! The container constructor.
        /** The function does nothing.
         @param window      The window.
         @param title       The title to display.
         @param bgcolor     The background color.
         @param bdcolor     The border color.
         @param txtcolor    The text color.
         */
        Header(sGuiWindow window,
               string const& title = "untitled",
               Color const& bgcolor = Color(0.88, 0.89, 0.88, 1.),
               Color const& bdcolor = Color(0.6, 0.6, 0.6, 1.),
               Color const& txtcolor = Color(0., 0., 0., 1.)) noexcept;
        
        //! The container destructor.
        /** The function does nothing.
         */
        virtual ~Header() noexcept;
        
        //! The creation method.
        /** The function create the header and bind it to the buttons if need.
         @param window      The window.
         @param title       The title to display.
         @param buttons     The buttons available.
         @param bgcolor     The background color.
         @param bdcolor     The border color.
         @param txtcolor    The text color.
         @return The header.
         */
        static inline sHeader create(sGuiWindow window, string const& title = "untitled", const ulong buttons = allButtons, Color const& bgcolor = Color(0.88, 0.89, 0.88, 1.), Color const& bdcolor = Color(0.6, 0.6, 0.6, 1.), Color const& txtcolor = Color(0., 0., 0., 1.)) noexcept
        {
            sHeader header = make_shared<Header>(window, title, bgcolor, bdcolor, txtcolor);
            if(header)
            {
                header->setButtons(buttons);
            }
            return header;
        }
        
        //! Retreives the shared pointer.
        /** The function retreives the shared pointer.
         @return The shared pointer.
         */
        inline scHeader getShared() const noexcept
        {
            return static_pointer_cast<const Header>(shared_from_this());
        }
        
        //! Retreives the shared pointer.
        /** The function retreives the shared pointer.
         @return The shared pointer.
         */
        inline sHeader getShared() noexcept
        {
            return static_pointer_cast<Header>(shared_from_this());
        }
        
        //! Retreives the window of the header.
        /** The function retreives the window of the header.
         @return The window.
         */
        inline sGuiWindow getWindow() const noexcept
        {
            return m_window.lock();
        }
        
        //! Retreives the title of the header.
        /** The function retreives the title of the header.
         @return The title.
         */
        inline string getTitle() const noexcept
        {
            return m_title;
        }
        
        //! Retreives the button of the header.
        /** The function retreives the buttons of the header.
         @return The buttons.
         */
        inline ulong getButtons() const noexcept
        {
            return m_buttons;
        }
        
        //! Retreives the background color of the header.
        /** The function retreives the background color of the header.
         @return The background color.
         */
        inline Color getBackgroundColor() const noexcept
        {
            return m_bg_color;
        }
        
        //! Retreives the border color of the header.
        /** The function retreives the border color of the header.
         @return The border color.
         */
        inline Color getBorderColor() const noexcept
        {
            return m_bd_color;
        }
        
        //! Retreives the text color of the header.
        /** The function retreives the text color of the header.
         @return The text color.
         */
        inline Color getTextColor() const noexcept
        {
            return m_txt_color;
        }
        
        //! Sets the title of the header.
        /** The function sets the title of the header.
         @param title The title.
         */
        void setTitle(string const& title) noexcept;
        
        //! Sets the top left buttons of the header.
        /** The function sets the top left buttons of the header.
         @param buttons The top left buttons.
         */
        void setButtons(const ulong buttons) noexcept;
        
        //! Sets the background color of the header.
        /** The function sets the background color of the header.
         @param color The background color.
         */
        void setBackgroundColor(Color const& color) noexcept;
        
        //! Sets the border color of the header.
        /** The function sets the border color of the header.
         @param color The border color.
         */
        void setBorderColor(Color const& color) noexcept;
        
        //! Sets the text color of the header.
        /** The function sets the text color of the header.
         @param color The text color.
         */
        void setTextColor(Color const& color) noexcept;
        
        //! The paint method that should be override.
        /** The function shoulds draw some stuff in the sketch.
         @param ctrl    The controller that ask the draw.
         @param sketch  A sketch to draw.
         */
        void draw(scGuiView view, Sketch& sketch) const;
        
        //! The receive method that should be override.
        /** The function shoulds perform some stuff.
         @param event    A mouser event.
         @param ctrl     The controller gives the event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(scGuiView view, MouseEvent const& event)  override;
        
        //! Receives the notfivation that a button has been pressed.
        /** The function receives the notfivation that a button has been pressed.
         @param The button.
         */
        void buttonPressed(sGuiButton button) override;
        
        sGuiController createController() override
        {
            return nullptr;
        }
    };

}

#endif


