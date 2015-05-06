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

#ifndef __DEF_KIWI_GUI_SKETCHER__
#define __DEF_KIWI_GUI_SKETCHER__

#include "KiwiGuiEvent.h"

namespace Kiwi
{    
	// ================================================================================ //
	//                                      SKETCHER                                    //
	// ================================================================================ //
	
	//! The sketcher...
	/** The sketcher...
	 */
    class GuiSketcher : public Attr::Manager
	{
	private:
        const wGuiContext           m_context;
		set<wGuiView,
		owner_less<wGuiView>>       m_views;
		mutable mutex               m_views_mutex;
        set<wGuiSketcher,
        owner_less<wGuiSketcher>>   m_childs;
        mutable mutex               m_childs_mutex;
	public:
		
		//! Constructor.
		/** The function does nothing.
         @param context The context.
		 */
        GuiSketcher(sGuiContext context) noexcept;
		
		//! Destructor.
		/** The function does nothing.
		 */
		virtual ~GuiSketcher() noexcept;
        
        //! Retrieves the context.
        /** The function retrieves the context of the sketcher.
         @return The context.
         */
        inline sGuiContext getContext() const noexcept
        {
            return m_context.lock();
        }
        
        //! Retrieves the device manager.
        /** The function retrieves the device manager of the sketcher.
         @return The device manager.
         */
        sGuiDeviceManager getDeviceManager() const noexcept;
        
        //! Retrieves the position of the sketcher.
        /** The function retrieves the position of the sketcher.
         @return The position of the sketcher.
         */
        inline Point getPosition() const noexcept
        {
            return Attr::Manager::getAttrValue<Point>(Tags::position);
        }
        
        //! Retrieves the size of the sketcher.
        /** The function retrieves the size of the sketcher.
         @return The size of the sketcher.
         */
        inline Size getSize() const noexcept
        {
            return Attr::Manager::getAttrValue<Size>(Tags::size);
        }
        
        //! Retrieves the bounds of the sketcher.
        /** The function retrieves the bounds of the sketcher.
         @return The bounds of the sketcher.
         */
        inline Rectangle getBounds() const noexcept
        {
            return Rectangle(getPosition(), getSize());
        }
		
		//! The draw method that should be override.
		/** The function shoulds draw some stuff in the sketch.
         @param ctrl    The controller that ask the draw.
		 @param sketch  A sketch to draw.
		 */
		virtual void draw(scGuiView view, Sketch& sketch) const = 0;
        
        //! Retrieves the absolute mouse position.
        /** The function retrieves the absolute mouse position.
         @return The position.
         */
        Point getMousePosition() const noexcept;
        
        //! Retrieves the views.
        /** The function retrieves the views. The methods also cleans the view list if some of them are not valid anymore.
         @return The views.
         */
        vector<sGuiView> getViews() noexcept;
        
        //! Retrieves the views.
        /** The function retrieves the views.
         @return The views.
         */
        vector<sGuiView> getViews() const noexcept;
        
        //! Retrieves the first available view.
        /** The function retrieves the first available view.
         @return The view.
         */
        sGuiView getFirstView() const noexcept;
        
        //! Retrieves if the sketcher has a view.
        /** The function retrieves if the sketcher has a view.
         @param view The view.
         @return true if the sketcher has the view, otherwise false.
         */
        bool hasView(sGuiView view) const noexcept;
		
        //! Sets the bounds of the sketcher.
        /** The function sets the bounds of the sketcher.
         @param bounds The bounds of the sketcher.
         */
        void setBounds(Rectangle const& bounds) noexcept;
        
        //! Sets the position of the sketcher.
        /** The function sets the position of the sketcher.
         @param position The position of the sketcher.
         */
        void setPosition(Point const& position) noexcept;
        
        //! Sets the size of the sketcher.
        /** The function sets the size of the sketcher.
         @param size The size of the sketcher.
         */
        void setSize(Size const& size) noexcept;
        
    protected:
        
        //! Creates a view.
        /** The function creates a view depending on the inheritance and the implemetation.
         @return The view.
         */
        sGuiView createView() noexcept;
        
        //! Removes a view.
        /** The function removes a view.
         @param view The view.
         */
        void removeView(sGuiView view) noexcept;
        
        //! Receives the notification that a view has been created.
        /** The function notfies the sketcher that a view has been created.
         @param view The view.
         */
        virtual void viewCreated(sGuiView view) noexcept {};
        
        //! Receives the notification that a view has been removed.
        /** The function notfies the sketcher that a view has been removed.
         @param view The view.
         */
        virtual void viewRemoved(sGuiView view) noexcept {};
        
        //! Adds a child sketcher to the sketcher.
        /** The function adds a child sketcher that will be displayed inside the sketcher.
         @param child The child.
         */
        void addChild(sGuiSketcher child) noexcept;
        
        //! Remove a child sketcher from the sketcher.
        /** The function removes a child sketcher and make it invisible.
         @param child The child.
         */
        void removeChild(sGuiSketcher child) noexcept;
        
        //! Retrives all the child sketchers from the sketcher.
        /** The function retrieves all the child sketchers from the sketcher. The methods also cleans the childs list if some of them are not valid anymore.
         @return The childs.
         */
        vector<sGuiSketcher> getChilds() noexcept;
        
        //! Retrives all the child sketchers from the sketcher.
        /** The function retrieves all the child sketchers from the sketcher.
         @return The childs.
         */
        vector<sGuiSketcher> getChilds() const noexcept;
    
		//! Send a notification to one or all views that the sketcher needs to be redrawn.
		/** The function sends a notification to one or all views that the sketcher should be redrawn.
         @param view The view that should be redrawn or nothing for all.
		 */
		void redraw(sGuiView view = sGuiView()) noexcept;
        
        //! Send a notification to a view that the sketcher needs the keyboard focus.
        /** The function sends a notification to a view that the sketcher wants the keyboard focus. If the view is empty, the notification will be sent to the first view.
         @param view The view that should retrieve the focus.
         */
        void grabFocus(sGuiView view = sGuiView()) noexcept;

    private:
        
        //! Create the controller.
        /** The function creates a controller depending on the inheritance.
         @return The controller.
         */
        virtual sGuiController createController();
	};
    
    // ================================================================================ //
    //                                      MOUSER                                      //
    // ================================================================================ //
    
    //! The mouser is the virutal class that receive mouse events.
    /**
     The mouser is a virtual class with a receive method that should be override to receveie a mouse event.
     */
    class GuiMouser
    {
    public:
        //! Constructor.
        /** The function does nothing.
         */
        constexpr inline GuiMouser() noexcept {};
        
        //! Destructor.
        /** The function does nothing.
         */
        virtual ~GuiMouser() noexcept {};
        
        //! The receive method that should be override.
        /** The function shoulds perform some stuff.
         @param event    A mouser event.
         @param ctrl     The controller gives the event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(scGuiView view, MouseEvent const& event) = 0;
    };
    
    // ================================================================================ //
    //                                     KEYBOARDER                                   //
    // ================================================================================ //
    
    //! The mouser is the virutal class that receive keyboard events.
    /**
     The mouser is a virtual class with a receive method that should be override to receveie a keyboard events.
     */
    class GuiKeyboarder
    {
    public:
        //! Constructor.
        /** The function does nothing.
         */
        constexpr inline GuiKeyboarder() noexcept {};
        
        //! Destructor.
        /** The function does nothing.
         */
        virtual inline ~GuiKeyboarder() noexcept {};
        
        //! The receive method that should be override.
        /** The function shoulds perform some stuff.
         @param event    A keyboard event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(scGuiView view, KeyboardEvent const& event) = 0;
        
        //! The receive method that should be override.
        /** The function shoulds perform some stuff.
         @param event    A focus event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(scGuiView view, KeyboardFocus const  event)
        {
            return false;
        }
    };
    
    // ================================================================================ //
    //                                     ACTION MANAGER                               //
    // ================================================================================ //
    
    //! The...
    /**
     The...
     */
    class GuiActionManager
    {
    public:
        
        //! Constructor.
        /** The function does nothing.
         */
        constexpr inline GuiActionManager() noexcept {};
        
        //! Destructor.
        /** The function does nothing.
         */
        virtual inline ~GuiActionManager() noexcept {};
        
        //! Retrieves the action codes.
        /** The function retreives the action codes from the the manager.
         @return The action codes.
         */
        virtual vector<Action::Code> getActionCodes() = 0;
        
        //! Retrieves an action from the manager.
        /** The function retreives an action from the the manager.
         @param code The code of the action.
         @return The action.
         */
        virtual Action getAction(const ulong code) = 0;
        
        //! Performs an action.
        /** The function performs an action.
         @param code The code of the action.
         @return true if the action has been performed, otherwise false.
         */
        virtual bool performAction(const ulong code) = 0;
    };
}

#endif