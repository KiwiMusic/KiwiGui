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

#ifndef __DEF_KIWI_GUI_BUTTON__
#define __DEF_KIWI_GUI_BUTTON__

#include "../KiwiGuiDevice.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI BUTTON                                      //
    // ================================================================================ //
    
    //! The button is a simple graphical button.
    /** The button is a simple graphical button that the user can press.
     */
    class GuiButton : public GuiModel
    {
    public:
        class Listener;
        typedef shared_ptr<Listener>    sListener;
        typedef weak_ptr<Listener>      wListener;
        
    protected:
        class Controller;
        typedef shared_ptr<Controller>  sController;
        typedef weak_ptr<Controller>    wController;
        
    private:
        Color m_background_color;
    public:
        
        //! The button constructor.
        /** The function initializes the button and defaults values.
         @param context The context.
         @param bgcolor The button background color.
         */
        GuiButton(sGuiContext context, Color const& bgcolor = Colors::white) noexcept;
        
        //! The button destructor.
        /** The function frees the memory.
         */
        inline virtual ~GuiButton() noexcept {};
        
        //! Retreives the background color of the button.
        /** The function retreives background the color of the button.
         @return The background color.
         */
        inline Color getBackgroundColor() const noexcept {return m_background_color;}
        
        //! Sets the background color of the button.
        /** The function sets the background color of the button and notifies all the views that they should be redrawn.
         @param color The color.
         */
        void setBackgroundColor(Color const& color) noexcept;
        
        //! The draw method that can be override.
        /** The function shoulds draw some stuff in the sketch. The default implementation draws a simple square with the background color and a darker border. Another implementation can draw more differents or complex shapes.
         @param ctrl    The controller that ask to be redraw.
         @param sketch  A sketch to draw.
         */
        virtual void draw(sController ctrl, Sketch& sketch) const;
        
        //! The mouse receive method that can be override.
        /** The function should return true if the button has been well pressed, otherwise it should return false. The default implementation returns true whenever the mouse event is down. Another implementation cans valid another kind of mouse event or/and defines an area where the press action is valid.
         @param ctrl    The controller that ask to be redraw.
         @param event   The mouser event.
         @return true if the button has been well pressed, otherwise false.
         */
        virtual bool receive(sController ctrl, MouseEvent const& event);
        
        //! Add an instance listener in the binding list of the manager.
        /** The function adds an instance listener in the binding list of the manager.
         @param listener  The listener.
         */
        void addListener(sListener listener)
        {
            if(listener)
            {
                ;
            }
        }
        
        //! Remove an instance listener from the binding list of the manager.
        /** The function removes an instance listener from the binding list of the manager.
         @param listener  The listener.
         */
        void removeListener(sListener listener)
        {
            if(listener)
            {
                ;
            }
        }
        
    private:
        
        //! Create the controller.
        /** The function creates a controller depending on the inheritance.
         @return The controller.
         */
        sGuiController createController() override;
    };
    
    // ================================================================================ //
    //                              GUI BUTTON CONTROLLER                               //
    // ================================================================================ //
    
    //! The button controller.
    /** The button controller manage a view of a button.
     */
    class GuiButton::Controller : public GuiController, public Broadcaster<Listener>
    {
    private:
        const wGuiButton m_button;
    public:
        //! The button controller constructor.
        /** The function initialize the button controller.
         @param context The context.
         @param button  The button to control.
         */
        Controller(sGuiContext context, sGuiButton button) noexcept;
        
        //! The controller destructor.
        /** The function does nothing.
         */
        inline ~Controller() noexcept {};
        
        //! Gets the button.
        /** The function retrieves the button.
         @return The button.
         */
        inline sGuiButton getButton() const noexcept {return m_button.lock();}
        
        //! The draw method that can be override.
        /** The function shoulds draw some stuff.
         @param view    The view that owns the controller.
         @param sketch  The sketch to draw.
         */
        void draw(sGuiView view, Sketch& sketch) override;
        
        //! The mouse receive method that can be override.
        /** The function pass the mouse event to the model if it inherits from mouser.
         @param view    The view that owns the controller.
         @param event   The mouser event.
         @return true if the class has done something with the event, otherwise false.true if the button has been well pressed
         */
        bool receive(sGuiView view, MouseEvent const& event);
    };
    
    // ================================================================================ //
    //                                  GUI BUTTON LISTENER                             //
    // ================================================================================ //
    
    //! The button listener.
    /** The button listener is notified when a button is pressed.
     */
    class GuiButton::Listener
    {
    public:
        //! The listener destructor.
        /** The function frees the memory.
         */
        virtual ~Listener() noexcept {};
        
        //! Receives the notification that a button is pressed.
        /** The function receives the notification that a button is pressed.
         @param button The button.
         */
        virtual void buttonPressed(sGuiButton button) = 0;
    };
}

#endif


