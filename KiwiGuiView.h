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
    
    class GuiView : public Attr::Listener, public enable_shared_from_this<GuiView>
    {
    private:
        const wGuiContext       m_context;
        const sGuiController    m_controller;
        wGuiView                m_parent_view;
        vector<sGuiView>        m_childs;
        mutex                   m_childs_mutex;
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
        inline sGuiContext getContext() const noexcept
        {
            return m_context.lock();
        }
        
        //! Retrieves the controller of the view.
        /** The function retrieves the controller of the view.
         @return The controller.
         */
        inline sGuiController getController() const noexcept
        {
            return m_controller;
        }
        
        //! Retrieves the sketcher of the controller.
        /** The function retrieves the sketcher of the controller.
         @return The sketcher.
         */
        inline sGuiSketcher getSketcher() const noexcept
        {
            return m_controller->getSketcher();
        }
        
        //! Retrieves the parent view of the view.
        /** The function retrieves the parent view of the view.
         @return The parent view.
         */
        inline sGuiView getParent() const noexcept
        {
            return m_parent_view.lock();
        }
        
        //! Retrieve the position of the view.
        /** The function retrieves the position of the view.
         @return The position of the view.
         */
        inline Point getPosition() const noexcept
        {
            return m_controller->getPosition();
        }
        
        //! Retrieve the size of the view.
        /** The function retrieves the size of the view.
         @return The size of the view.
         */
        inline Size getSize() const noexcept
        {
            return m_controller->getSize();
        }
        
        //! Retrieve the bounds of the view.
        /** The function retrieves the bounds of the view.
         @return The bounds of the view.
         */
        inline Rectangle getBounds() const noexcept
        {
            return m_controller->getBounds();
        }
        
        //! Retrieve the global position of the view.
        /** The function retrieves tthe global position of the view.
         @return The global position of the view.
         */
        Point getGlobalPosition() const noexcept;
        
        //! Retrieve the position of the parent view.
        /** The function retrieves the position of the parent view or the screen area if it is a top level view.
         @return The position of the parent view.
         */
        Point getParentPosition() const noexcept;
        
        //! Retrieve the size of the view.
        /** The function retrieves the size of the view if it is a top level view.
         @return The size of the view.
         */
        Size getParentSize() const noexcept;
        
        //! Retrieve the bounds of the view.
        /** The function retrieves the bounds of the view if it is a top level view.
         @return The bounds of the view.
         */
        Rectangle getParentBounds() const noexcept;
        
        //! Receives the notification that the sketcher needs to be redrawn.
        /** This function is called by the sketcher whenever it needs to be redrawn.
         */
        virtual void redraw() = 0;
        
        //! Receives the notification that the sketcher needs to be moved.
        /** This function is called by the sketcher whenever it needs to be moved.
         */
        virtual void move() = 0;
        
        //! Receives the notification that the sketcher needs to be resized.
        /** This function is called by the sketcher whenever it needs to be resized.
         */
        virtual void resize() = 0;
        
        //! Receives the notification that the sketcher needs the keyboard focus.
        /** This function is called by the sketcher whenever it needs the keyboard focus.
         */
        virtual void grabFocus() = 0;
        
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
        
        //! Adds a child view to the view.
        /** The function adds a child view that will be displayed inside the view.
         @param child The child.
         */
        void add(sGuiView child) noexcept;
        
        //! Remove a child view from the view.
        /** The function removes a child view and make it invisible.
         @param child The child.
         */
        void remove(sGuiView child) noexcept;
        
        //! Receive the notification that an attribute has changed.
        /** The function must be implement to receive notifications when an attribute is added or removed, or when its value, appearance or behavior changes.
         @param manager     The attribute manager.
         @param attr		The attribute that has been modified.
         */
        void attrChanged(Attr::sManager manager, sAttr attr) override;
        
        //! The mouse receive method.
        /** The function pass the mouse event to the sketcher if it inherits from mouser.
         @param event    A mouser event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(MouseEvent const& event);
        
        //! The keyboard receive method.
        /** The function pass the keyboard event to the sketcher if it inherits from keyboarder.
         @param event    A keyboard event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(KeyboardEvent const& event);
        
        //! The keyboard focus receive method.
        /** The function pass the keyboard event to the sketcher if it inherits from keyboarder.
         @param event    A focus event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(KeyboardFocus event);
        
        //! Retrieves the action codes.
        /** The function retreives the action codes from the the manager.
         @return The action codes.
         */
        vector<Action::Code> getActionCodes();
        
        //! Retrieves an action from the manager.
        /** The function retreives an action from the the manager.
         @param code The code of the action.
         @return The action.
         */
        Action getAction(const ulong code);
        
        //! Performs an action.
        /** The function performs an action.
         @param code The code of the action.
         @return true if the action has been performed, otherwise false.
         */
        bool performAction(const ulong code);
        
    private:
        
        //! Adds a child view to the view.
        /** The function adds a child view that will be displayed inside the view.
         @param child The child.
         */
        virtual void addChild(sGuiView child) = 0;
        
        //! Remove a child view from the view.
        /** The function removes a child view and make it invisible.
         @param child The child.
         */
        virtual void removeChild(sGuiView child) = 0;
        
        //@internal
        void setParent(sGuiView child);
    };
}

#endif


