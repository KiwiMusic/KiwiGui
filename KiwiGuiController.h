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
    
    class GuiController : public enable_shared_from_this<GuiController>
    {
        friend GuiSketcher;
    private:
        const sGuiSketcher  m_sketcher;
        wGuiView            m_view;
        
        //! Sets the view of the controller.
        /** The function sets the view of the controller.
         @param The view.
         */
        inline void setView(sGuiView view) noexcept
        {
            m_view = view;
        }
    public:
        
        //! The controller constructor.
        /** The function does nothing.
         */
        inline GuiController(sGuiSketcher sketcher) noexcept : m_sketcher(sketcher)
        {
            assert(m_sketcher);
        }
        
        //! The controller destructor.
        /** The function does nothing.
         */
        virtual inline ~GuiController() noexcept {};
        
    protected:
        
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
        
        //! Send a notification to the view that the sketcher needs to be redrawn.
        /** The function sends a notification to the each that the sketcher should be redrawn.
         */
        void redraw() noexcept;
        
    public:
        //! Retrieves the view of the controller.
        /** The function retrieves the view of the controller.
         @return The view.
         */
        inline sGuiView getView() const noexcept
        {
            return m_view.lock();
        }
        
        //! Retrieves the context of the controller.
        /** The function retrieves the context of the controller.
         @return The context.
         */
        inline sGuiContext getContext() const noexcept
        {
            return m_sketcher->getContext();
        }
        
        //! Retrieve the sketcher of the controller.
        /** The function retrieves the sketcher of the controller.
         @return The sketcher.
         */
        inline sGuiSketcher getSketcher() const noexcept
        {
            return m_sketcher;
        }
        
        //! Retrieve if the controller wants the mouse.
        /** This function retrieves if the controller wants the mouse.
         @return true if the controller wants the mouse, othrewise false.
         */
        virtual inline bool wantMouse() const noexcept
        {
            sGuiMouser mouser = dynamic_pointer_cast<GuiMouser>(getSketcher());
            if(mouser)
            {
                return true;
            }
            return false;
        }
        
        //! Retrieve if the controller wants the keyboard.
        /** This function retrieves if the controller wants the keyboard.
         @return true if the controller wants the keyboard, othrewise false.
         */
        virtual inline bool wantKeyboard() const noexcept
        {
            sGuiKeyboarder keyboarder = dynamic_pointer_cast<GuiKeyboarder>(getSketcher());
            if(keyboarder)
            {
                return true;
            }
            return false;
        }
        
        //! Retrieve if the controller wants actions.
        /** This function retrieves if the controller wants the actions.
         @return true if the controller wants the actions, othrewise false.
         */
        virtual inline bool wantActions() const noexcept
        {
            sGuiActionManager actionmanager = dynamic_pointer_cast<GuiActionManager>(getSketcher());
            if(actionmanager)
            {
                return true;
            }
            return false;
        }
        
        //! Retrieve the position of the sketcher.
        /** The function retrieves the position of the sketcher.
         @return The position of the sketcher.
         */
        virtual Point getPosition() const noexcept;
        
        //! Retrieve the size of the sketcher.
        /** The function retrieves the size of the sketcher.
         @return The size of the sketcher.
         */
        virtual Size getSize() const noexcept;
        
        //! Retrieve the bounds of the object.
        /** The function retrieves the bounds of the object.
         @return The bounds of the object.
         */
        inline Rectangle getBounds() const noexcept
        {
            return Rectangle(getPosition(), getSize());
        }
        
        //! Make the sketcher's view visible or invisible.
        /** This function make the sketcher's view visible or invisible.
         @param visible True to make it visible, otherwise false.
         */
        virtual void setVisible(const bool visible);
        
        //! Retrieve if the sketcher is visible.
        /** The function retrieves if the sketcher is visible.
         @param true if the sketcher is visible, otherwise false.
         */
        virtual bool isVisible() const noexcept
        {
            return false;
        }
        
        //! The paint method that can be override.
        /** The function shoulds draw some stuff in the sketch.
         @param sketch  A sketch to draw.
         */
        virtual void draw(Sketch& sketch);
        
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
        
        //! Retrieves the action codes.
        /** The function retreives the action codes from the the manager.
         @return The action codes.
         */
        virtual vector<Action::Code> getActionCodes();
        
        //! Retrieves an action from the manager.
        /** The function retreives an action from the the manager.
         @param code The code of the action.
         @return The action.
         */
        virtual Action getAction(const ulong code);
        
        //! Performs an action.
        /** The function performs an action.
         @param code The code of the action.
         @return true if the action has been performed, otherwise false.
         */
        virtual bool performAction(const ulong code);
        
        //! Test if the point lies into the sketcher of the controler.
        /** The tests if the point lies into the sketcher of the controler.
         @param pt The point.
         @return true if the point ies into the sketcher of the controler, otherwise false.
         */
        virtual bool contains(Point const& pt);
        
        //! Test if the rectangle overlaps the sketcher of the controler.
        /** The tests if the rectangle overlaps the sketcher of the controler.
         @param rect The rectangle.
         @return true if the rectangle overlaps the sketcher of the controler, otherwise false.
         */
        virtual bool overlaps(Rectangle const& rect);
        
        //! Retrieves the absolute mouse position.
        /** The function retrieves the absolute mouse position.
         @return The position.
         */
        Point getMousePosition() const noexcept;
        
        //! Retrieves the relative mouse position.
        /** The function retrieves the relative mouse position.
         @return The position.
         */
        Point getMouseRelativePosition() const noexcept;
    };
}

#endif


