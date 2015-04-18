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
    
    class GuiWindow : public GuiSketcher, public enable_shared_from_this<GuiWindow>
    {
    private:
        class Container;
        typedef shared_ptr<Container>           sContainer;
        typedef weak_ptr<Container>             wContainer;
        typedef shared_ptr<const Container>     scContainer;
        typedef weak_ptr<const Container>       wcContainer;
        
    public:
        class Controller;
        class Header;
        
        enum TitleButtons
        {
            noButton        = 0,
            minimiseButton  = 1,
            maximiseButton  = 2,
            closeButton     = 4,
            allButtons      = 7
        };
        
    private:
        
        string m_title;
        Color  m_color;
        ulong  m_buttons;
        bool   m_has_title_bar;
    public:
        
        //! The window constructor.
        /** The function does nothing.
         @param context The context.
         @param title   The title of the window.
         @param color   The background color of the window.
         @param buttons The buttons available at the top of the window.
         @param show    If the window should be popup.
         */
        GuiWindow(sGuiContext context,
                  string const& title = "untitled",
                  Color const& color = Color(0., 0., 0., 1.),
                  const ulong buttons = allButtons,
                  const bool show = true) noexcept;
        
        //! The window destructor.
        /** The function does nothing.
         */
        virtual ~GuiWindow() noexcept;
        
        //! Retreives the title of the window
        /** The function retreives the title of the window.
         @return The title.
         */
        inline string getTitle() const noexcept
        {
            return m_title;
        }
        
        //! Retreives the background color of the window
        /** The function retreives the background color of the window.
         @return The background color.
         */
        inline Color getBackgroundColor() const noexcept
        {
            return m_color;
        }
        
        //! Retreives the background color of the window
        /** The function retreives the background color of the window.
         @return The background color.
         */
        Color getButtons() const noexcept;
        
        //! Sets the title of the window
        /** The function sets the title of the window.
         @param title The title.
         */
        void setTitle(string const& title) noexcept;
        
        //! Sets the background color of the window
        /** The function sets the background color of the window.
         @param color The background color.
         */
        void setBackgroundColor(Color const& color) noexcept;
        
        //! Sets the top left buttons of the window
        /** The function sets the top left buttons of the window.
         @param buttons The top left buttons.
         */
        void setButtons(const ulong buttons) noexcept;
        
        //! The paint method that should be override.
        /** The function shoulds draw some stuff in the sketch.
         @param ctrl    The controller that ask the draw.
         @param sketch  A sketch to draw.
         */
        void draw(scGuiController ctrl, Sketch& sketch) const override;
        
        //! Displays the windows.
        /** This function diwplays in the desktop.
         */
        void display();
        
    private:
        
        //! Create the controller.
        /** The function creates a controller depending on the inheritance.
         @return The controller.
         */
        sGuiController createController() override;
        
    };
    
    // ================================================================================ //
    //                              GUI WINDOW CONTROLLER                               //
    // ================================================================================ //
    
    class GuiWindow::Controller : public GuiController
    {
    private:
        const sGuiWindow m_window;
        Point            m_last_position;
    public:
        
        //! The window controller constructor.
        /** The function does nothing.
         @param window The window.
         */
        Controller(sGuiWindow window) noexcept;
        
        //! The window controller destructor.
        /** The function does nothing.
         */
        ~Controller() noexcept;
        
        //! Retrieves the sketcher of the controller.
        /** The function retrieves the sketcher of the controller.
         @return The sketcher.
         */
        inline sGuiSketcher getSketcher() const noexcept override
        {
            return m_window;
        }
        
        //! Receives if the controller wants the mouse.
        /** This function retrieves if the controller wants the mouse.
         @return true if the controller wants the mouse, othrewise false.
         */
        inline bool wantMouse() const noexcept override
        {
            return true;
        }
        
        //! The mouse receive method.
        /** The function pass the mouse event to the sketcher if it inherits from mouser.
         @param event    A mouser event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(MouseEvent const& event) override;
        
    };
    
    class GuiWindow::Container : public GuiSketcher, public enable_shared_from_this<Container>
    {
    private:
        const wGuiWindow m_window;
        
    public:
        //! The container constructor.
        /** The function does nothing.
         @param window The window.
         */
        Container(sGuiWindow window) noexcept;
        
        //! The container destructor.
        /** The function does nothing.
         */
        virtual ~Container() noexcept;
        
    private:
        
        //! Create the controller.
        /** The function creates a controller depending on the inheritance.
         @return The controller.
         */
        sGuiController createController() override;
    };
    
    
    class GuiWindow::Header : public GuiSketcher, public enable_shared_from_this<Header>
    {
    private:
        const wGuiWindow m_window;
        
    public:
        //! The container constructor.
        /** The function does nothing.
         @param window The window.
         */
        Header(sGuiWindow window) noexcept;
        
        //! The container destructor.
        /** The function does nothing.
         */
        virtual ~Header() noexcept;
        
    private:
        
        //! Create the controller.
        /** The function creates a controller depending on the inheritance.
         @return The controller.
         */
        sGuiController createController() override;
    };

}

#endif


