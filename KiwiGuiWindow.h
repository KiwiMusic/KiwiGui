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

#include "KiwiGuiContainer.h"
#include "KiwiGuiTextEditor.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI WINDOW                                      //
    // ================================================================================ //
    
    class GuiWindow : public GuiSketcher
    {
    public:
        class Header;
        typedef shared_ptr<Header>          sHeader;
        typedef weak_ptr<Header>            wHeader;
        typedef shared_ptr<const Header>    scHeader;
        typedef weak_ptr<const Header>      wcHeader;
        
    private:
        const sGuiContainer m_container;
        Color  m_color;
    public:
        
        //! The window constructor.
        /** The function does nothing.
         @param context The context.
         @param title   The title of the window.
         @param color   The background color of the window.
         @param buttons The buttons available at the top of the window.
         @param show    If the window should be popup.
         */
        GuiWindow(sGuiContext context, Color const& color = Color(0., 0., 0., 1.)) noexcept;
        
        //! The window destructor.
        /** The function does nothing.
         */
        virtual ~GuiWindow() noexcept;
        
        //! Sets the background color of the window
        /** The function sets the background color of the window.
         @param color The background color.
         */
        void setBackgroundColor(Color const& color) noexcept;
        
        //! Retreives the background color of the window
        /** The function retreives the background color of the window.
         @return The background color.
         */
        inline Color getBackgroundColor() const noexcept
        {
            return m_color;
        }
        
        //! The paint method that should be override.
        /** The function shoulds draw some stuff in the sketch.
         @param ctrl    The controller that ask the draw.
         @param sketch  A sketch to draw.
         */
        void draw(scGuiView view, Sketch& sketch) const override;
        
        //! Adds a sketcher to the window.
        /** The function adds sketcher to the window that will be displayed inside the window container.
         @param sketcher The sketcher.
         */
        void addContent(sGuiSketcher sketcher) noexcept;
        
        //! Remove a sketcher from the window.
        /** The function removes a sketcher from the window container.
         @param sketcher The sketcher.
         */
        void removeContent(sGuiSketcher sketcher) noexcept;
        
        //! Displays the windows.
        /** This function displays the window in the desktop.
         */
        void display();
        
        //! Closes the windows.
        /** This function removes the window from the desktop.
         */
        void close();

        //! Closes the windows.
        /** This function removes the window from the desktop.
         */
        void minimize();

    };
    
    // ================================================================================ //
    //                              GUI WINDOW HEADER                                   //
    // ================================================================================ //
    
    class GuiWindow::Header : public GuiSketcher, public GuiMouser, public GuiButton::Listener
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
        void draw(scGuiView view, Sketch& sketch) const override;
        
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
    };

}

#endif


