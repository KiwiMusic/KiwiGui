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

#ifndef __DEF_KIWI_GUI_PATCHER__
#define __DEF_KIWI_GUI_PATCHER__

#include "KiwiGuiLink.h"

namespace Kiwi
{
    class PatcherView;

    //! The gui patcher...
    /**
     The gui patcher
     */
    class GuiPatcher : virtual public Attr::Manager
    {
	public:
		class View;
        typedef shared_ptr<PatcherView>         sPatcherView;
        typedef weak_ptr<PatcherView>           wPatcherView;
        typedef shared_ptr<const PatcherView>   scPatcherView;
        typedef weak_ptr<const PatcherView>     wcPatcherView;
		
	private:
		wGuiContext         m_manager;
		vector<sGuiObject>  m_objects;
		vector<sGuiLink>    m_links;
		mutable mutex       m_mutex;
        
        set<wPatcherView,
        owner_less<wPatcherView>>   m_views;
        mutable mutex               m_views_mutex;
        
        const sAttrColor    m_color_unlocked_background;
        const sAttrColor    m_color_locked_background;
        const sAttrLong     m_gridsize;
        
        //! @internal flags describing the type of the notification
        enum Notification
        {
            Added        = false,
            Removed      = true
        };
		
        //! @internal Trigger notification to controlers.
        void send(sGuiObject object, Notification type);
        void send(sGuiLink link, Notification type);
        
    public:
		//! The constructor.
		/** The constructor.
		 @param instance The manager.
		 */
		GuiPatcher(sGuiContext manager) noexcept;
		
		//! The destructor.
		/** Free memory.
		 */
		virtual ~GuiPatcher();
		
		//! Retrieve the context of the chain.
		/** This function retrieves the context of the chain.
		 @return The context of the chain.
		 */
		inline sGuiContext getContext() const noexcept
		{
			return m_manager.lock();
		}
		
		//! Retrieve the device manager of the context.
		/** This function retrieves the device manager of the context.
		 @return The device manager of the context.
		 */
		sGuiDeviceManager getDeviceManager() const noexcept;
        
        //! Create a new view
        /** The function creates a new patcher.
         @return The view.
         */
        sPatcherView createView();
		
		//! Retrieve the objects of the patcher.
		/** The function retrieves the objects of the patcher.
		 @return The objects of the patcher.
		 */
		inline vector<sGuiObject> getObjects() const noexcept
		{
			return m_objects;
		}
		
		//! Retrieve the links of the patcher.
		/** The function retrieves the links of the patcher.
		 @return The links of the patcher.
		 */
		inline vector<sGuiLink> getLinks() const noexcept
		{
			return m_links;
		}
		
		//! Add an object to the page.
		/** The function adds an object to the page.
		 @param object The object to add.
		 */
		void add(sGuiObject box);
		
		//! Add a link to the patcher.
		/** The function adds a link to the patcher.
		 @param link The link to add.
		 */
		void add(sGuiLink link);
		
		//! Remove an object from the page.
		/** The function removes an object from the patcher.
		 @param object The box to remove.
		 */
		void remove(sGuiObject box);
		
		//! Remove a link from the patcher.
		/** The function removes a link from the patcher
		 @param link The link to remove.
		 */
		void remove(sGuiLink link);
        
        //! Bring a object to the front of the patcher.
        /** The function brings a object to the front of the patcher. The object will be setted as if it was the last object created and will be the last object of the vector of objects.
         @param object        The pointer to the object.
         */
        void toFront(sGuiObject object);
        
        //! Bring a object to the back of the patcher.
        /** The function brings a object to the back of the patcher. The object will be setted as if it was the first object created and will be the first object of the vector of objects.
         @param object        The pointer to the object.
         */
        void toBack(sGuiObject object);
        
        //! Retrieve the "gridsize" attribute value of the patcher.
        /** The function retrieves the "gridsize" attribute value of the patcher.
         @return The "gridsize" attribute value of the patcher.
         */
        inline long getGridSize() const noexcept
        {
            return m_gridsize->getValue();
        }
        
        //! Retrieve the "locked_bgcolor" attribute value of the patcher.
        /** The function retrieves the "locked_bgcolor" attribute value of the patcher.
         @return The "locked_bgcolor" attribute value of the patcher.
         */
        inline Color getLockedBackgroundColor() const noexcept
        {
            return m_color_locked_background->getValue();
        }
        
        //! Retrieve the "locked_bgcolor" attribute value of the patcher.
        /** The function retrieves the "locked_bgcolor" attribute value of the patcher.
         @return The "locked_bgcolor" attribute value of the patcher.
         */
        inline Color getUnlockedBackgroundColor() const noexcept
        {
            return m_color_unlocked_background->getValue();
        }
    };
	
	// ================================================================================ //
	//									 GUI PAGE VIEW                                  //
	// ================================================================================ //
	
    //! The gui patcher view is an abstract class that facilitates the control of a patcher in an application.
    /** The gui patcher view is an abstract class that facilitates the control of a patcher in an application.
     @see GuiPatcher, Patcher
     */
	class GuiPatcher::View
	{
	public:
		virtual ~View() {}
		
		//! Receive the notification that an object has been created.
		/** The function is called by the page when an object has been created.
		 @param object The box.
		 */
		virtual void objectCreated(sGuiObject box) = 0;
		
		//! Receive the notification that an object has been removed.
		/** The function is called by the page when an object has been removed.
		 @param object The box.
		 */
		virtual void objectRemoved(sGuiObject box) = 0;
		
		//! Receive the notification that a link has been created.
		/** The function is called by the patcher when a link has been created.
		 @param link   The link.
		 */
		virtual void linkCreated(sGuiLink link) = 0;
		
		//! Receive the notification that a link has been removed.
		/** The function is called by the patcher when a link has been removed.
		 @param link   The link.
		 */
		virtual void linkRemoved(sGuiLink link) = 0;
	};
}

#endif


