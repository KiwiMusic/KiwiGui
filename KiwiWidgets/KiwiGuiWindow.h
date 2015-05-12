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
        const sGuiResizer   m_resizer;
        sHeader             m_header;
        sGuiModel           m_content;
        Color               m_color;
    public:
        
        //! The window constructor.
        /** The function does nothing.
         @param context The context.
         @param title   The title of the window.
         @param zones   The title of the window.
         @param color   The background color of the window.
         @param buttons The buttons available at the top of the window.
         @param show    If the window should be popup.
         */
        GuiWindow(sGuiContext context, const ulong zones = GuiResizer::All, Color const& color = Colors::grey) noexcept;
        
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
        
        //! Sets the header of the window.
        /** The function sets the header of the window.
         @param header The header.
         */
        void setHeader(sHeader header) noexcept;
        
        //! Gets the header of the window.
        /** The function retrieves the header of the window.
         @return The header.
         */
        inline sHeader getHeader() const noexcept {return m_header;}
        
        //! Gets if the window has an header.
        /** The function retrieves if the window has an header.
         @return true if the window has an header, otherwise false.
         */
        inline bool hasHeader() const noexcept {return bool(m_header);}
        
        //! Sets the content of the window.
        /** The function sets the content of the window.
         @param content The content.
         */
        void setContent(sGuiModel content) noexcept;
        
        //! Gets the content of the window.
        /** The function retrieves the content of the window.
         @return The content.
         */
        inline sGuiModel getContent() const noexcept {return m_content;}
        
        //! Gets if the window has a content.
        /** The function retrieves if the window has a content.
         @return true if the window has a content, otherwise false.
         */
        inline bool hasContent() const noexcept {return bool(m_content);}
        
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
        const wGuiWindow    m_window;
        sGuiController      m_resizer;
        sGuiController      m_header;
        sGuiController      m_content;
        
        Rectangle        m_last_bounds;
        
    public:
        //! The window controller constructor.
        /** The function initialize the window controller.
         @param window  The window to control.
         */
        Controller(sGuiWindow window) noexcept;
        
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
        
        //! Receives the notification that a child has been created.
        /** The function notifies the controller that a child has been created.
         @param child The child controller.
         */
        void childCreated(sGuiController child) noexcept override;
        
        //! Receives the notification that a child has been removed.
        /** The function notifies the controller that a child has been removed.
         @param child The child controller.
         */
        void childRemoved(sGuiController child) noexcept override;
        
        //! Receives the notification that the bounds of the parent controller changed.
        /** The function notifies that the bounds of the parent controller changed.
         */
        void boundsChanged() noexcept override;
    };
    
    // ================================================================================ //
    //                              GUI WINDOW HEADER                                   //
    // ================================================================================ //
    
    class GuiWindow::Header : public GuiModel
    {
    private:
        class Controller;
        typedef shared_ptr<Controller>  sController;
        typedef weak_ptr<Controller>    wController;
        
        const sGuiButton m_button_close;
        const sGuiButton m_button_minimize;
        const sGuiButton m_button_maximize;
        string          m_title;
        ulong           m_buttons;
        Color           m_bg_color;
        Color           m_txt_color;
        
    public:
        
        /** The direction of the scroll bar.
         */
        enum TitleButtons
        {
            noButton        = 0,///< No button
            minimiseButton  = 1,///< Minimize button
            maximiseButton  = 2,///< Maximize button
            closeButton     = 4,///< Close button
            allButtons      = 7 ///< All buttons
        };
        
        //! The container constructor.
        /** The function does nothing.
         @param context     The context.
         @param title       The title to display.
         @param buttons     The buttons to display.
         @param bgcolor     The background color.
         @param txtcolor    The text color.
         */
        Header(sGuiContext context,
               string const& title  = "untitled",
               ulong const buttons  = allButtons,
               Color const& bgcolor = Colors::grey,
               Color const& txtcolor= Colors::black) noexcept;
        
        //! The container destructor.
        /** The function does nothing.
         */
        virtual ~Header() noexcept;
        
        //! Retreives the title of the header.
        /** The function retreives the title of the header.
         @return The title.
         */
        inline string getTitle() const noexcept {return m_title;}
        
        //! Retreives the button of the header.
        /** The function retreives the buttons of the header.
         @return The buttons.
         */
        inline ulong getButtons() const noexcept {return m_buttons;}
        
        //! Retreives the background color of the header.
        /** The function retreives the background color of the header.
         @return The background color.
         */
        inline Color getBackgroundColor() const noexcept {return m_bg_color;}
        
        //! Retreives the text color of the header.
        /** The function retreives the text color of the header.
         @return The text color.
         */
        inline Color getTextColor() const noexcept{return m_txt_color;}
        
        //! Retreives the close button of the header.
        /** The function retreives the close button of the header.
         @return The close button.
         */
        inline sGuiButton getCloseButton() const noexcept{return m_button_close;}
        
        //! Retreives the minimize button of the header.
        /** The function retreives the minimize button of the header.
         @return The minimize button.
         */
        inline sGuiButton getMinimizeButton() const noexcept{return m_button_minimize;}
        
        //! Retreives the maximize button of the header.
        /** The function retreives the maximize button of the header.
         @return The maximize button.
         */
        inline sGuiButton getMaximizeButton() const noexcept{return m_button_maximize;}
        
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
        
        //! Sets the text color of the header.
        /** The function sets the text color of the header.
         @param color The text color.
         */
        void setTextColor(Color const& color) noexcept;
        
        //! The draw method that should be override.
        /** The function shoulds draw some stuff.
         @param ctrl    The controller.
         @param sketch  The sketch to draw.
         */
        virtual void draw(sController ctrl, Sketch& sketch) const;
        
        //! The receive method that should be override.
        /** The function shoulds perform some stuff.
         @param ctrl     The controller gives the event.
         @param event    A mouser event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(sController ctrl, MouseEvent const& event) ;
        
        //! Create the controller.
        /** The function creates a controller for the header's window.
         @return The controller.
         */
        sGuiController createController() override;
    };
    
    // ================================================================================ //
    //                          GUI WINDOW HEADER CONTROLLER                            //
    // ================================================================================ //
    
    class GuiWindow::Header::Controller : public GuiController, public GuiButton::Listener
    {
    private:
        const wHeader   m_header;
        Point           m_last_pos;
    public:
        
        //! The window header controller constructor.
        /** The function initialize the window header  controller.
         @param header  The window header to control.
         */
        Controller(sHeader header) noexcept;
        
        //! The controller destructor.
        /** The function does nothing.
         */
        inline ~Controller() noexcept {};
        
        //! Retreives the window header of the controller.
        /** The function retreives the window header of the controller.
         @return The window header.
         */
        inline sHeader getHeader() const noexcept {return m_header.lock();}
        
        //! Retreives the window's controller.
        /** The function retreives the window's controller.
         @return The window's controller.
         */
        inline GuiWindow::sController getWindowController() const noexcept
        {
            sGuiController pctrl(getParent());
            if(pctrl) {
                return static_pointer_cast<GuiWindow::Controller>(pctrl);
            }
            return GuiWindow::sController();
        }
        
        //! The draw method that should be override.
        /** The function shoulds draw some stuff.
         @param view    The view that owns the controller.
         @param sketch  The sketch to draw.
         */
        void draw(sGuiView view, Sketch& sketch) override;
        
        //! The mouse receive method that can be override.
        /** The function shoulds perform some stuff.
         @param view    The view that owns the controller.
         @param event   The mouser event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(sGuiView view, MouseEvent const& event) override;
        
        //! Receives the notification that a button is pressed.
        /** The function receives the notification that a button is pressed.
         @param button The button.
         */
        void buttonPressed(sGuiButton button) override;
        
        //! Receives the notification that a child has been created.
        /** The function notfies the model that a child has been created.
         @param child The child controller.
         */
        void childCreated(sGuiController child) noexcept override;
        
        //! Receives the notification that a child has been removed.
        /** The function notfies the model that a child has been removed.
         @param child The child controller.
         */
        void childRemoved(sGuiController child) noexcept override;
        
        //! Receives the notification that the parent controller changed.
        /** The function notifies that the parent controller changed or has been setted.
         */
        void parentChanged() noexcept override;
        
        //! Receives the notification that the bounds of the parent controller changed.
        /** The function notifies that the bounds of the parent controller changed.
         */
        void parentBoundsChanged() noexcept override;
    };

}

#endif


