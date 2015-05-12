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
    
    //! The controller is a class that manages the drawing and the interactions requested by a view.
    /** The controller is instantiate by a model to serve as a bridge between the its interface and a view.
     */
    class GuiController : public inheritable_enable_shared_from_this<GuiController>
    {
    private:
        friend class GuiContext;
        
        const wGuiContext   m_context;
        const wGuiModel     m_model;
        Rectangle           m_bounds;
        bool                m_want_mouse;
        bool                m_want_keyboard;
        bool                m_want_action;
        wGuiView            m_view;

    public:
        
        //! The controller constructor.
        /** The function initializes the defaults values of the controller.
         @param model The model to control.
         */
        GuiController(sGuiModel model) noexcept;
        
        //! The controller destructor.
        /** The function does nothing.
         */
        virtual inline ~GuiController() noexcept {};
        
        //! Retrieves the view of the controller.
        /** The function retrieves the view of the controller.
         @return The view.
         */
        inline sGuiView getView() const noexcept {return m_view.lock();}
        
        //! Retrieves the model of the controller.
        /** The function retrieves the model of the controller.
         @return The model.
         */
        inline sGuiModel getModel() const noexcept{return m_model.lock();}
        
        //! Retrieves the context of the controller.
        /** The function retrieves the context of the controller.
         @return The context.
         */
        inline sGuiContext getContext() const noexcept{return m_context.lock();}

        //! Receives the notification that the bounds of the parent controller changed.
        /** The function notifies that the bounds of the parent controller changed.
         */
        virtual void boundsChanged() noexcept {};
        
        //! Retrieves the parent controller.
        /** The function retrieves parent controller.
         @return The parent controller.
         */
        sGuiController getParent() const noexcept;
        
        //! Receives the notification that the parent controller changed.
        /** The function notifies that the parent controller changed or has been setted.
         */
        virtual void parentChanged() noexcept {};
        
        //! Receives the notification that the bounds of the parent controller changed.
        /** The function notifies that the bounds of the parent controller changed.
         */
        virtual void parentBoundsChanged() noexcept {};
        
        //! Retrieves the childs controller.
        /** The function retrieves childs controller.
         @return The childs controller.
         */
        vector<sGuiController> getChilds() const noexcept;
        
        //! Receives the notification that a child has been created.
        /** The function notifies the controller that a child has been created.
         @param child The child controller.
         */
        virtual void childCreated(sGuiController child) noexcept {};
        
        //! Receives the notification that a child has been removed.
        /** The function notifies the controller that a child has been removed.
         @param child The child controller.
         */
        virtual void childRemoved(sGuiController child) noexcept {};
        
        //! Receives the notification that the bounds of a child changed.
        /** The function notifies the controller that the bounds of a child changed.
         @param child The child controller.
         */
        virtual void childBoundsChanged(sGuiController child) noexcept {};
        
        //! Receives if the controller wants the mouse.
        /** This function retrieves if the controller wants the mouse.
         @return true if the controller wants the mouse, othrewise false.
         */
        inline bool wantMouse() const noexcept {return m_want_mouse;}
        
        //! Receives if the controller wants the keyboard.
        /** This function retrieves if the controller wants the keyboard.
         @return true if the controller wants the keyboard, othrewise false.
         */
        inline bool wantKeyboard() const noexcept {return m_want_keyboard;}
        
        //! Receives if the controller wants actions.
        /** This function retrieves if the controller wants the actions.
         @return true if the controller wants the actions, othrewise false.
         */
        inline bool wantActions() const noexcept  {return m_want_action;}
        
        //! Retrieve the position of the controller.
        /** The function retrieves the position of the controller.
         @return The position of the controller.
         */
        inline Point getPosition() const noexcept {return m_bounds.position();}
        
        //! Retrieve the size of the controller.
        /** The function retrieves the size of the controller.
         @return The size of the controller.
         */
        inline Size getSize() const noexcept {return m_bounds.size();}
        
        //! Retrieve the bounds of the controller.
        /** The function retrieves the bounds of the controller.
         @return The bounds of the controller.
         */
        inline Rectangle getBounds() const noexcept {return m_bounds;}
        
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
        
        //! The draw method that should be override.
        /** The function shoulds draw some stuff.
         @param view    The view that owns the controller.
         @param sketch  The sketch to draw.
         */
        virtual void draw(sGuiView view, Sketch& sketch) = 0;
        
        //! The mouse receive method that can be override.
        /** The function shoulds perform some stuff.
         @param view    The view that owns the controller.
         @param event   The mouser event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(sGuiView view, MouseEvent const& event) {return false;}
        
        //! The keyboard receive method that can be override.
        /** The function shoulds perform some stuff.
         @param view    The view that owns the controller.
         @param event   The keyboard event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(sGuiView view, KeyboardEvent const& event) {return false;}
        
        //! The focus receive method that can be override.
        /** The function shoulds perform some stuff.
         @param view    The view that owns the controller.
         @param event   The focus event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(sGuiView view, KeyboardFocus const event) {return false;}
        
        //! Retrieves the action codes.
        /** The function retreives the action codes from the the manager.
         @return The action codes.
         */
        virtual vector<Action::Code> getActionCodes() {return vector<Action::Code>();}
        
        //! Retrieves an action from the manager.
        /** The function retreives an action from the the manager.
         @param code The code of the action.
         @return The action.
         */
        virtual Action getAction(const ulong code) {return Action();}
        
        //! Performs an action.
        /** The function performs an action.
         @param code The code of the action.
         @return true if the action has been performed, otherwise false.
         */
        virtual bool performAction(const ulong code) {return false;}
        
        //! Test if the point lies into the controler.
        /** The funtion tests if the point lies into the controler.
         @param pt The point.
         @return true if the point lies into the controler, otherwise false.
         */
        virtual bool contains(Point const& pt);
        
        //! Test if the rectangle overlaps the controler.
        /** The funtion tests if the rectangle overlaps the controler.
         @param rect The rectangle.
         @return true if the rectangle overlaps of the controler, otherwise false.
         */
        virtual bool overlaps(Rectangle const& rect);
        
        //! Sets if the controller should receive mouse events.
        /** The function sets if the controller should receive mouse events.
         @param accept true if the controller shoulds receive the mouse events, otherwise false.
         */
        void shouldReceiveMouse(const bool accept) noexcept;
        
        //! Sets if the controller should receive keyboard events.
        /** The function sets if the controller should keyboard mouse events.
         @param accept true if the controller shoulds keyboard the mouse events, otherwise false.
         */
        void shouldReceiveKeyboard(const bool accept) noexcept;
        
        //! Sets if the controller should receive actions.
        /** The function sets if the controller should receive actions.
         @param accept true if the controller shoulds actions, otherwise false.
         */
        void shouldReceiveActions(const bool accept) noexcept;
        
        //! Sets the bounds of the controller.
        /** The function sets the bounds of the controller.
         @param bounds The bounds of the controller.
         */
        void setBounds(Rectangle const& bounds) noexcept;
        
        //! Sets the bounds of the controller.
        /** The function sets the bounds of the controller.
         @param bounds The bounds of the controller.
         */
        void setBounds(Rectangle&& bounds) noexcept;
        
        //! Sets the position of the controller.
        /** The function sets the position of the controller.
         @param position The position of the controller.
         */
        void setPosition(Point const& position) noexcept;
        
        //! Sets the position of the controller.
        /** The function sets the position of the controller.
         @param position The position of the controller.
         */
        void setPosition(Point&& position) noexcept;
        
        //! Sets the size of the controller.
        /** The function sets the size of the controller.
         @param size The size of the controller.
         */
        void setSize(Size const& size) noexcept;
        
        //! Sets the size of the controller.
        /** The function sets the size of the controller.
         @param size The size of the controller.
         */
        void setSize(Size&& size) noexcept;
        
        //! Send a notification to the view that the controller needs to be redrawn.
        /** The function sends a notification to the view that the controller should be redrawn.
         */
        void redraw() noexcept;
        
        //! Send a notification to the view that the controller wants the keyboard focus.
        /** The function sends a notification to the view that the controller wants the keyboard focus.
         */
        void grabFocus() noexcept;
        
        //! Sends the notification to the view that the controller needs to go behind the other controllers.
        /** This function sends a notification to the view that the controller needs to go behind the other controllers.
         */
        void toBack() noexcept;
        
        //! Sends the notification to the view that the controller needs to go in front of the other controllers.
        /** This function sends a notification to the view that the controller needs to in front of the other controllers.
         */
        void toFront() noexcept;
        
        //! Sends the notification to the view that the controller needs another mouse cursor.
        /** This function sends the notification to the view that the controller needs another mouse cursor.
         */
        void setMouseCursor(MouseCursor const& cursor) noexcept;
    };
}

#endif


