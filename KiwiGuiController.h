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

#ifndef __DEF_KIWI_GUI_CONTROLLER__
#define __DEF_KIWI_GUI_CONTROLLER__

#include "KiwiGuiModel.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI CONTROLLER                                  //
    // ================================================================================ //
    
    class GuiController : public Attr::Listener, public enable_shared_from_this<GuiController>
    {
    private:
        friend class GuiView;
        
        const sGuiSketcher      m_sketcher;
        const sGuiMouser        m_mouser;
        const sGuiKeyboarder    m_keyboarder;
        const bool              m_want_mouse;
        const bool              m_want_keyboard;
    public:
        
        //! The controller constructor.
        /** The function does nothing.
         @param sketcher The sketcher to control.
         */
        GuiController(sGuiSketcher sketcher) noexcept;
        
        //! The controller destructor.
        /** The function does nothing.
         */
        virtual ~GuiController() noexcept;
        
        //! Retrieves the sketcher of the controller.
        /** The function retrieves the sketcher of the controller.
         @return The sketcher.
         */
        sGuiSketcher getSketcher() const noexcept
        {
            return m_sketcher;
        }
        
        //! Receives if the controller wants the mouse.
        /** This function retrieves if the controller wants the mouse.
         @return true if the controller wants the mouse, othrewise false.
         */
        virtual inline bool wantMouse() const noexcept
        {
            return m_want_mouse;
        }
        
        //! Receives if the controller wants the keyboard.
        /** This function retrieves if the controller wants the keyboard.
         @return true if the controller wants the keyboard, othrewise false.
         */
        virtual inline bool wantKeyboard() const noexcept
        {
            return m_want_keyboard;
        }
        
        //! Retrieve the position of the sketcher.
        /** The function retrieves the position of the sketcher.
         @return The position of the sketcher.
         */
        virtual Point getPosition() const noexcept = 0;
        
        //! Retrieve the size of the sketcher.
        /** The function retrieves the size of the sketcher.
         @return The size of the sketcher.
         */
        virtual Size getSize() const noexcept = 0;
        
        //! Retrieve the bounds of the object.
        /** The function retrieves the bounds of the object.
         @return The bounds of the object.
         */
        inline Rectangle getBounds() const noexcept
        {
            return Rectangle(getPosition(), getSize());
        }
        
        //! Receive the notification that an attribute has changed.
        /** The function must be implement to receive notifications when an attribute is added or removed, or when its value, appearance or behavior changes.
         @param attr		The attribute that has been modified.
         */
        virtual void notify(sAttr attr) override = 0;
        
        //! The paint method that can be override.
        /** The function shoulds draw some stuff in the sketch.
         @param sketch  A sketch to draw.
         */
        virtual void draw(Sketch& sketch);
        
    protected:
        
        //! The mouse receive method.
        /** The function pass the mouse event to the sketcher if it inherits from mouser.
         @param event    A mouser event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(MouseEvent const& event);
        
        //! The keyboard receive method.
        /** The function pass the keyboard event to the sketcher if it inherits from keyboarder.
         @param event    A keyboard event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(KeyboardEvent const& event);
        
        //! The keyboard focus receive method.
        /** The function pass the keyboard event to the sketcher if it inherits from keyboarder.
         @param event    A focus event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(KeyboardFocus const event);
        
        //! Retrieve the shared pointer of the controller.
        /** The function retrieves the shared pointer of controller.
         @return The shared pointer of the controller.
         */
        sGuiController getShared() noexcept
        {
            return shared_from_this();
        }
        
        //! Retrieve the shared pointer of the controller.
        /** The function retrieves the shared pointer of controller.
         @return The shared pointer of the controller.
         */
        scGuiController getShared() const noexcept
        {
            return shared_from_this();
        }
        
    };
}

#endif


