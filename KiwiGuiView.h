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

#ifndef __DEF_KIWI_GUI_VIEW__
#define __DEF_KIWI_GUI_VIEW__

#include "KiwiGuiController.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      GUI VIEW                                    //
    // ================================================================================ //
    
    class GuiView : public enable_shared_from_this<GuiView>
    {
    private:
        const wGuiContext       m_context;
        const sGuiController    m_controller;
        wGuiView                m_parent_view;
        vector<sGuiView>        m_childs;
        mutable mutex           m_childs_mutex;
    public:
        
        //! The view constructor.
        /** The function does nothing.
         @param ctrl The controlller.
         */
        GuiView(sGuiController ctrl) noexcept;
        
        //! The view destructor.
        /** The function does nothing.
         */
        virtual ~GuiView() noexcept;
        
        //! Retrieves the context of the view.
        /** The function retrieves the context of the view.
         @return The context.
         */
        inline sGuiContext getContext() const noexcept {return m_context.lock();}
        
        //! Retrieves the controller of the view.
        /** The function retrieves the controller of the view.
         @return The controller.
         */
        inline sGuiController getController() const noexcept {return m_controller;}
        
        //! Retrieves the parent view of the view.
        /** The function retrieves the parent view of the view.
         @return The parent view.
         */
        inline sGuiView getParent() const noexcept {return m_parent_view.lock();}
        
        //! Retrieves the childs views of the view.
        /** The function retrieves the childs views of the view.
         @return The childs views.
         */
        inline vector<sGuiView> getChilds() const noexcept
        {
            lock_guard<mutex> guard(m_childs_mutex);
            return m_childs;
        }
        
        //! Retrieve the position of the view.
        /** The function retrieves the position of the view.
         @return The position of the view.
         */
        inline Point getPosition() const noexcept {return m_controller->getPosition();}
        
        //! Retrieve the size of the view.
        /** The function retrieves the size of the view.
         @return The size of the view.
         */
        inline Size getSize() const noexcept {return m_controller->getSize();}
        
        //! Retrieve the bounds of the view.
        /** The function retrieves the bounds of the view.
         @return The bounds of the view.
         */
        inline Rectangle getBounds() const noexcept {return m_controller->getBounds();}
        
        //! Test if the point lies into the view.
        /** The funtion tests if the point lies into the view (the point to test is inside the view bounds).
         @param pt The point.
         @return true if the point lies into the view, otherwise false.
         */
        inline bool hitTest(Point const& pt) const noexcept {return m_controller->hitTest(pt);}
        
        //! Test if the point lies into the view.
        /** The funtion tests if the point lies into the view.
         @param pt The point.
         @return true if the point lies into the view, otherwise false.
         */
        inline bool contains(Point const& pt) const noexcept {return m_controller->contains(pt);}
        
        //! Receives if the view wants the mouse.
        /** This function retrieves if the view wants the mouse.
         @return true if the view wants the mouse, otherwise false.
         */
        inline bool wantMouse() const noexcept {return m_controller->wantMouse();}
        
        //! Receives if the view wants the mouse on children.
        /** This function retrieves if the view wants the mouse on children.
         @return true if the view wants the mouse on children, otherwise false.
         */
        inline bool wantMouseOnChildren() const noexcept {return m_controller->wantMouse();}
        
        //! Receives if the view wants the keyboard.
        /** This function retrieves if the view wants the keyboard.
         @return true if the view wants the keyboard, otherwise false.
         */
        inline bool wantKeyboard() const noexcept {return m_controller->wantKeyboard();}
        
        //! Receives if the view wants actions.
        /** This function retrieves if the view wants the actions.
         @return true if the view wants the actions, otherwise false.
         */
        inline bool wantActions() const noexcept  {return m_controller->wantActions();}
        
        //! Retrieve the global position of the view.
        /** The function retrieves tthe global position of the view.
         @return The global position of the view.
         */
        Point getGlobalPosition() const noexcept;
        
        //! Retrieve the position of the parent view.
        /** The function retrieves the position of the parent view, or the screen area if it's a top-level view.
         @return The position of the parent view.
         */
        Point getParentPosition() const noexcept;
        
        //! Retrieve the size of the view.
        /** The function retrieves the size of the parent view. 
         If the view is a top-level view, it will return the screen size.
         @return The size of the view.
         */
        Size getParentSize() const noexcept;
        
        //! Retrieve the bounds of the view.
        /** The function retrieves the bounds of the parent view.
         If the view is a top-level view, it will return the screen bounds.
         @return The bounds of the view.
         */
        Rectangle getParentBounds() const noexcept;
        
        //! Adds a child view to the view.
        /** The function adds a child view that will be displayed inside the view.
         @param child The child.
         */
        void addChild(sGuiView child) noexcept;
        
        //! Remove a child view from the view.
        /** The function removes a child view and make it invisible.
         @param child The child.
         */
        void removeChild(sGuiView child) noexcept;
        
        //! The draw method.
        /** The function pass tells the controller to draw.
         @param sketch  A sketch to draw.
         */
        inline void draw(Sketch& sketch) {m_controller->draw(shared_from_this(), sketch);}
        
        //! The draw method.
        /** The function pass tells the controller to draw.
         @param sketch  A sketch to draw.
         */
        inline void drawOver(Sketch& sketch) {m_controller->drawOver(shared_from_this(), sketch);}
        
        //! The mouse receive method.
        /** The function pass the mouse event to the model if it inherits from mouser.
         @param event    A mouser event.
         @return true if the class has done something with the event otherwise false
         */
        inline bool receive(MouseEvent const& event) {return m_controller->receive(shared_from_this(), event);}
        
        //! The keyboard receive method.
        /** The function pass the keyboard event to the model if it inherits from keyboarder.
         @param event    A keyboard event.
         @return true if the class has done something with the event otherwise false
         */
        inline bool receive(KeyboardEvent const& event) {return m_controller->receive(shared_from_this(), event);}
        
        //! The keyboard focus receive method.
        /** The function pass the keyboard event to the model if it inherits from keyboarder.
         @param event    A focus event.
         @return true if the class has done something with the event otherwise false
         */
        inline bool receive(KeyboardFocus event) {return m_controller->receive(shared_from_this(), event);}
        
        //! Retrieves the action codes.
        /** The function retreives the action codes from the the manager.
         @return The action codes.
         */
        inline vector<Action::Code> getActionCodes() {return m_controller->getActionCodes();}
        
        //! Retrieves an action from the manager.
        /** The function retreives an action from the the manager.
         @param code The code of the action.
         @return The action.
         */
        inline Action getAction(const ulong code) {return m_controller->getAction(code);}
        
        //! Performs an action.
        /** The function performs an action.
         @param code The code of the action.
         @return true if the action has been performed, otherwise false.
         */
        inline bool performAction(const ulong code) {return m_controller->performAction(code);}
        
        //! Receives the notification that the controller needs to be redrawn.
        /** This function is called by the controller whenever it needs to be redrawn.
         */
        virtual void redraw() = 0;
        
        //! Receives the notification that the bounds of the controller changed.
        /** This function is called by the controller whenever its bounds changed.
         */
        virtual void boundsChanged() = 0;
        
        //! Receives the notification that the position of the controller changed.
        /** This function is called by the controller whenever it needs to be moved.
         */
        virtual void positionChanged() = 0;
        
        //! Receives the notification that the size of the controller changed.
        /** This function is called by the controller whenever it needs to be resized.
         */
        virtual void sizeChanged() = 0;
        
        //! Receives the notification that the controller's behavior changed.
        /** This function is called by the controller whenever its behavio changed.
         */
        virtual void behaviorChanged() = 0;
        
        //! Receives the notification that the view needs its cursor to be changed.
        /** This function is called whenever its mouse cursor needs to be changed.
         */
        virtual void setMouseCursor(Kiwi::MouseCursor const& cursor) = 0;
        
        //! Receives the notification that the model needs the keyboard focus.
        /** This function is called by the model whenever it needs the keyboard focus.
         */
        virtual void grabFocus() = 0;
        
        //! Receives the notification that the model needs to go behind the other viewes.
        /** This function is called by the model whenever it needs to go behind the other viewes.
         */
        virtual void toBack() = 0;
        
        //! Receives the notification that the model needs to go in front of the other viewes.
        /** This function is called by the model whenever it needs to go in front of the other viewes.
         */
        virtual void toFront() = 0;
        
        //! Receives the notification that the view will always need to be in front of its siblings.
        /** This function is called to indicate that this view will always need to be in front of its siblings.
         */
        virtual void alwaysOnTop(const bool alwaysOnTop) = 0;
        
        //! Adds the view to the desktop.
        /** This function adds the view to the desktop as a top level window.
         */
        virtual void addToDesktop() = 0;
        
        //! Removes the view from the desktop.
        /** This function removes the view from the desktop.
         */
        virtual void removeFromDesktop() = 0;
        
        //! Minimize the view.
        /** This function minimizes the view.
         */
        virtual void setMinimize(const bool state) = 0;
        
    private:
        
        //! Adds a child view to the view.
        /** The function adds a child view that will be displayed inside the view.
         @param child The child.
         */
        virtual void addChildView(sGuiView child) = 0;
        
        //! Remove a child view from the view.
        /** The function removes a child view and make it invisible.
         @param child The child.
         */
        virtual void removeChildView(sGuiView child) = 0;
        
        //@internal
        void setParent(sGuiView child);
    };
}

#endif


