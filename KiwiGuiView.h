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
    
    class GuiView //: public Attr::Listener
    {
    private:
        const sGuiController  m_controller;
        vector<sGuiView>      m_childs;
        mutex                 m_childs_mutex;
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
        
        //! Retrieves the controller of the view.
        /** The function retrieves the controller of the view.
         @return The controller.
         */
        sGuiController getController() const noexcept
        {
            return m_controller;
        }
        
        //! Retrieves the sketcher of the controller.
        /** The function retrieves the sketcher of the controller.
         @return The sketcher.
         */
        sGuiSketcher getSketcher() const noexcept
        {
            return m_controller->getSketcher();
        }
        
        //! Receives the notification that the sketcher needs to be redrawn.
        /** This function is called by the sketcher whenever it needs to be redrawn.
         The listener sublasses must implement this method to draw the sketcher.
         */
        virtual void redraw() = 0;
        
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
         @param attr		The attribute that has been modified.
         @param type		The type of notification.
         */
        //virtual void notify(sAttr attr) = 0;
        
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
    };
}

#endif


