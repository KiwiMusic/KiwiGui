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

#include "KiwiGuiObject.h"

namespace Kiwi
{
    //! The gui patcher...
    /**
     The gui patcher
     */
    class GuiPatcher : virtual public Attr::Manager
    {
	public:
		class View;
		typedef shared_ptr<View>        sView;
		typedef weak_ptr<View>          wView;
		typedef shared_ptr<const View>  scView;
		typedef weak_ptr<const View>    wcView;
		
	private:
		wGuiPatchManager  m_manager;
		vector<sGuiObject>	m_boxes;
		vector<sGuiLink>    m_links;
		mutable mutex       m_mutex;
        
        const sAttrColor	m_color_unlocked_background;
        const sAttrColor	m_color_locked_background;
        const sAttrLong		m_gridsize;
		
		//wPatcherview  (patcher a vector<sPatcherView>)
		
    public:
		//! The constructor.
		/** The constructor.
		 @param instance The manager.
		 */
		GuiPatcher(sGuiPatchManager manager) noexcept;
		
		//! The destructor.
		/** Free memory.
		 */
		virtual ~GuiPatcher();
		
		//! Retrieve the context of the chain.
		/** This function retrieves the context of the chain.
		 @return The context of the chain.
		 */
		inline sGuiPatchManager getGuiPatchManager() const noexcept
		{
			return m_manager.lock();
		}
		
		//! Retrieve the device manager of the context.
		/** This function retrieves the device manager of the context.
		 @return The device manager of the context.
		 */
		sGuiDeviceManager getDeviceManager() const noexcept;
		
		//! Retrieve the number of gui objects.
		/** The function retrieves the number of gui objects.
		 @return The number of gui objects.
		 */
		inline ulong getNumberOfObjects() const noexcept
		{
			lock_guard<mutex> guard(m_mutex);
			return (ulong)m_boxes.size();
		}
		
		//! Retrieve the number of gui links.
		/** The function retrieves the number of gui links.
		 @return The number of gui links.
		 */
		inline ulong getNumberOfLinks() const noexcept
		{
			lock_guard<mutex> guard(m_mutex);
			return (ulong)m_links.size();
		}
		
		//! Add a box to the page.
		/** The function adds a box to the page.
		 @param object The object to add.
		 */
		void add(sGuiObject box);
		
		//! Add a link to the patcher.
		/** The function adds a link to the patcher.
		 @param link The link to add.
		 */
		void add(sGuiLink link);
		
		//! Remove a box from the page.
		/** The function removes a box from the patcher.
		 @param object The box to remove.
		 */
		void remove(sGuiObject box);
		
		//! Remove a link from the patcher.
		/** The function removes a link from the patcher
		 @param link The link to remove.
		 */
		void remove(sGuiLink link);
        
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
		
		//sView ?? createView() => instance create view
    };
	
	// ================================================================================ //
	//									 GUI PAGE VIEW                                  //
	// ================================================================================ //
	
	//! The patcher view listener .
	/**
	 The patcher view listener...
	 */
	class GuiPatcher::View
	{
	public:
		virtual ~View() {}
		
		//! Receive the notification that a box has been created.
		/** The function is called by the page when a box has been created.
		 @param object The box.
		 */
		virtual void objectCreated(sGuiObject box) = 0;
		
		//! Receive the notification that a box has been removed.
		/** The function is called by the page when a box has been removed.
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


