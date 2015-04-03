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

#ifndef __DEF_KIWI_GUI_PAGEVIEW__
#define __DEF_KIWI_GUI_PAGEVIEW__

#include "../KiwiGuiModels/KiwiGuiModels.h"

namespace Kiwi
{
    struct Knock;
    
    class PatcherView;
    typedef shared_ptr<PatcherView>         sPatcherView;
    typedef weak_ptr<PatcherView>           wPatcherView;
    typedef shared_ptr<const PatcherView>   scPatcherView;
    typedef weak_ptr<const PatcherView>     wcPatcherView;
    
    class LinkView;
    typedef shared_ptr<LinkView>         sLinkView;
    typedef weak_ptr<LinkView>           wLinkView;
    typedef shared_ptr<const LinkView>   scLinkView;
    typedef weak_ptr<const LinkView>     wcLinkView;
    
    class ObjectView;
    typedef shared_ptr<ObjectView>         sObjectView;
    typedef weak_ptr<ObjectView>           wObjectView;
    typedef shared_ptr<const ObjectView>   scObjectView;
    typedef weak_ptr<const ObjectView>     wcObjectView;
    
    // ================================================================================ //
    //                                  PAGE VIEW                                       //
    // ================================================================================ //
    
    //! The patcher view is an abstract class that facilitates the control of a patcher in an application.
    /**
     The patcher view...
     @see Patcher, Patcher::Listener, ObjectView
     */
    class PatcherView : public GuiPatcher::View, public enable_shared_from_this<PatcherView>
    {
	public:
		class Listener;
		typedef shared_ptr<Listener>        sListener;
		typedef weak_ptr<Listener>          wListener;
		typedef shared_ptr<const Listener>  scListener;
		typedef weak_ptr<const Listener>    wcListener;
		
    private:
        const sGuiPatcher       m_patcher;
        vector<sObjectView>		m_objects;
        vector<sLinkView>		m_links;
        mutable mutex           m_mutex;
        
        set<wObjectView,
        owner_less<wObjectView>>	m_objects_selected;
        set<wLinkView,
        owner_less<wLinkView>>		m_links_selected;
        
        map<wObjectView,
        Rectangle,
        owner_less<wObjectView>>	m_last_bounds;
		
		set<wListener,
		owner_less<wListener>>      m_listeners;
		mutable mutex           	m_listeners_mutex;
        
        long m_zoom;
        bool m_locked;
        bool m_presentation;
        bool m_display_grid;
        bool m_snap_to_grid;
        
        void addObjectView(sObjectView object);
        void removeObjectView(sObjectView object);
        
        sObjectView getObjectView(sGuiObject object) const noexcept;
        
        void addLinkView(sLinkView link);
        void removeLinkView(sLinkView link);
        
        sLinkView getLinkView(sGuiLink link) const noexcept;
        
    public:
        
        //! Constructor.
        /** You should never call this method except if you really know what you're doing.
         Please use the create method instead.
         @param patcher The patcher to control.
         */
        PatcherView(const sGuiPatcher patcher) noexcept;
        
        //! The destructor.
        /** The destructor.
         */
        virtual ~PatcherView() noexcept;
		
		//! Adds a patcher view listener.
		/** The function adds a patcher view listener
		 @param listener The listener to add.
		 */
		void addListener(sListener listener);
		
		//! Removes a patcher view listener.
		/** The function removes a patcher view listener.
		 @param listener The listener to remove.
		 */
		void removeListener(sListener listener);
		
        //! Retrieve the patcher.
        /** The funtion retrieves the patcher.
         @return The patcher.
         */
        inline sGuiPatcher getPatcher() const noexcept
        {
            return m_patcher;
        }
        
        //! Get object views.
        /** The function retrieves the object controllers of the patcher.
         @param objects   A vector of object controllers.
         */
        void getObjects(vector<sObjectView>& objects) const
        {
            lock_guard<mutex> guard(m_mutex);
            objects = m_objects;
        }
		
        //! Get link controllers.
        /** The function retrieves the link controllers of the patcher.
         @param objects   A vector of link controllers.
         */
        void getLinks(vector<sLinkView>& links) const
        {
            lock_guard<mutex> guard(m_mutex);
            links = m_links;
        }
        
        //! Retrieve the zoom of the patcher.
        /** The function retrieves the zoom of the patcher.
         @return the zoom of the patcher in percent.
         @see setZoom
         */
        inline long getZoom() const noexcept
        {
            return m_zoom;
        }
        
        //! Set the zoom of the patcher.
        /** The function sets the zoom of the patcher.
         @param zoom The zoom of the patcher in percent.
         @see getZoom
         */
        void setZoom(long zoom);
        
        //! Retrieve if the patcher is locked or unlocked.
        /** The function retrieves if the patcher is locked or unlocked.
         @return True if the patcher is locked, false if it is unlocked.
         @see setLockStatus
         */
        inline bool getLockStatus() const noexcept
        {
            return m_locked;
        }
        
        //! Lock/Unlock the patcher.
        /** The function locks or unlocks the patcher.
         @param locked True to lock the patcher, false to unlock it.
         @see getLockStatus
         */
        void setLockStatus(bool locked);
        
        //! Retrieve if the presentation mode of the patcher is active.
        /** The function retrieves if the presentation mode of the patcher is active.
         @return True if the presentation mode of the patcher is active otherwise false.
         */
        inline bool getPresentationStatus() const noexcept
        {
            return m_presentation;
        }
        
        //! Active the presentation mode of the patcher.
        /** The function actives the presentation mode of the patcher.
         @param presentation True to active the presentation mode, otherwise false.
         */
        void setPresentationStatus(bool presentation);
        
        //! Retrieve if the patcher is displays the grid.
        /** The function retrieves if the patcher is displays the grid.
         @return True if the patcher is displays the grid is locked otherwise false.
         */
        inline bool getGridDisplayedStatus() const noexcept
        {
            return m_display_grid;
        }
        
        //! Shows/Hides the grid of the patcher.
        /** The function shows or hides the grid of the patcher.
         @param display True to show the grid, false to hide it.
         */
        void setGridDisplayedStatus(bool display);
        
        //! Retrieve if the snap to grid mode of the patcher is active.
        /** The function retrieves if the snap to grid mode of the patcher is active.
         @return True if the snap to grid mode of the patcher is active, otherwise false.
         */
        inline bool getSnapToGridStatus() const noexcept
        {
            return m_snap_to_grid;
        }
        
        //! Active the snap to grid in the patcher.
        /** The function actives the snap to grid in the patcher.
         @param snap True to active the snap to grid, otherwise false.
         */
        void setSnapToGridStatus(bool snap);
        
        //! Adds or removes objects from presentation.
        /** The function Adds or removes objects from presentation.
         @param objects The objects to add or remove from presentation.
         @param add True to add objects to presentation, false to remove them.
         */
        void setObjectsPresentationStatus(const vector<sObjectView>& objects, const bool add);
        
        // ================================================================================ //
        //										SELECTION									//
        // ================================================================================ //
        
        //! Retrieves if some objects or links are currently selected.
        /** The function retrieves if some objects or links are currently selected.
         @return True if some objects or links are currently selected, false if nothing is selected.
         */
        inline bool isAnythingSelected() const noexcept
        {
            return isAnyObjectSelected() || isAnyLinksSelected();
        }
        
        //! Retrieves if some objects are currently selected.
        /** The function retrieves if some objects are currently selected.
         @return True if some objects are currently selected, false if no object is selected.
         */
        inline bool isAnyObjectSelected() const noexcept
        {
            lock_guard<mutex> guard(m_mutex);
            return !m_objects_selected.empty();
        }
		
		//! Retrieves the number of objects currently selected.
		/** The function retrieves the number of objects currently selected.
		 @return The number of objects currently selected.
		 */
		inline long getNumberOfSelectedObjects() const noexcept
		{
			lock_guard<mutex> guard(m_mutex);
			return !m_objects_selected.size();
		}
		
        //! Retrieves if some links are currently selected.
        /** The function retrieves if some links are currently selected.
         @return True if some links are currently selected, false if no object is selected.
         */
        inline bool isAnyLinksSelected() const noexcept
        {
            lock_guard<mutex> guard(m_mutex);
            return !m_links_selected.empty();
        }
        
        //! Retrieves the selected objects.
        /** The function retrieves the selected objects.
         */
        void getSelection(vector<sObjectView>& objects) const noexcept;
        
        //! Retrieves the selected links.
        /** The function retrieves the selected links.
         */
        void getSelection(vector<sLinkView>& links) const noexcept;
        
        //! Retrieves the selected objects.
        /** The function retrieves the selected objects.
         */
        void getSelection(set<wObjectView, owner_less<wObjectView>>& objects) const noexcept;
        
        //! Retrieves the selected links.
        /** The function retrieves the selected links.
         */
        void getSelection(set<wLinkView, owner_less<wLinkView>>& links) const noexcept;
        
        //! Deletes all selected links and objects.
        /** The function deletes all selected links and objects.
         */
        void deleteSelection();
        
        //! Retrieves if an object is selected.
        /** The function retrieve if an object is selected.
         */
        bool isSelected(sObjectView object);
        
        //! Retrieves if a link is selected.
        /** The function retrieve if a link is selected.
         */
        bool isSelected(sLinkView link);
        
        //! Adds all objects to selection.
        /** The function adds all objects to selection.
         */
        bool selectAllObjects();
        
        //! Adds all links to selection.
        /** The function adds all links to selection.
         */
        bool selectAllLinks();
        
        //! Selects a set of objects.
        /** The function selects a set of objects.
         */
        void select(vector<sObjectView>& objects);
        
        //! Selects a set of links.
        /** The function selects a set of links.
         */
        void select(vector<sLinkView>& links);
        
        //! Adds an object to the selection.
        /** The function adds an object to the selection.
         */
        bool select(sObjectView object, const bool notify = true);
        
        //! Adds a link to the selection.
        /** The function adds a link to the selection.
         */
        bool select(sLinkView link, const bool notify = true);
        
        //! Clears the selection then the selects an object.
        /** The function clears the selection then the selects an object.
         */
        bool selectOnly(sObjectView object);
        
        //! Clears the selection then the selects an object.
        /** The function clears the selection then the selects an object.
         */
        bool selectOnly(sLinkView link);
        
        //! Unselects all objects and links.
        /** The function unselects all objects and links.
         */
        void unselectAll(const bool notify = true);
        
        //! Unselects all objects.
        /** The function unselects all objects.
         */
        bool unselectAllObjects(const bool notify = true);
        
        //! Unselects all links.
        /** The function unselects all links.
         */
        bool unselectAllLinks(const bool notify = true);
        
        //! Unselects a set of objects.
        /** The function unselects a set of objects.
         */
        void unselect(vector<sObjectView>& objects);
        
        //! Unselects a set of links.
        /** The function unselects a set of links.
         */
        void unselect(vector<sLinkView>& links);
        
        //! Removes an object from the selection.
        /** The function unselects object.
         */
        bool unselect(sObjectView object, const bool notify = true);
        
        //! Removes a link from the selection.
        /** The function unselects link.
         */
        bool unselect(sLinkView link, const bool notify = true);
        
        //! Called when the selection has changed.
        /** The function is called when the selection has changed.
         */
        virtual void selectionChanged() {};
        
        //! Retrieves the selected objects bounds.
        /** The function retrieves the selected objects bounds.
         @return The selected objects bounds as a rectangle.
         */
        Rectangle getSelectionBounds();
        
        //! Moves the objects that are currently selected by given value.
        /** The function moves the objects that are currently selected by given value.
         @param delta A shift amount delta.
         */
        void moveSelectedObjects(Point const& delta);
        
        //! Start resizing objects.
        /** Call this function before to call resizeSelectedObjects.
         */
        void startMoveOrResizeObjects();
        
        //! Resizes the objects that are currently selected by given value.
        /** The function moves the objects that are currently selected by given value.
         @param delta A shift amount delta.
         */
        void resizeSelectedObjects(Point const& delta, const long borderFlags, const bool preserveRatio = false);
        
        //! end resizing objects.
        /** Call this function after resizeSelectedObjects.
         */
        void endMoveOrResizeObjects();
        
        //! Retrieve the selected objects (including links) as a dico
        /** The function retrieve the selected objects (including links) as a dico.
         You may use it to copy selection to clipboard.
         @return The dico.
         */
        Dico getSelectedObjectsDico();
        
        //! Adds objects to the patcher from a dico
        /** The function adds objects to the patcher from a dico
         The dico must be formated with getSelectedObjectsDico
         @param dico The dico.
         @param shift Shift the position of the objects.
         @return True if the patcher has been modified, false otherwise
         */
        bool addObjectsFromDico(Dico const& dico, Point const& shift = Point());
		
        //! Create an object controller.
        /** Patcher controller's subclasses must implement this method to create custom object controller.
         @param object     The object.
         @return The newly created object controller.
         */
        virtual sObjectView createObjectView(sGuiObject object) = 0;
        
        //! Receive the notification that an object controller has been created.
        /** The function is called by the patcher when an object controller has been created.
         @param objectctrl The object controller.
         */
        virtual void objectViewCreated(sObjectView objectctrl) {};
        
        //! Receive the notification that an object controller before an object has been removed.
        /** The function is called by the patcher controller before an object has been removed.
         @param objectctrl The object controller.
         */
        virtual void objectViewWillBeRemoved(sObjectView objectctrl) {};
        
        //! Receive the notification that an object has been replaced.
        /** The function is called by the patcher when an object has been replaced.
         @param oldobject  The old object.
         @param newobject	The new object.
         */
        virtual void objectHasBeenReplaced(sGuiObject oldobject, sGuiObject newobject) {};
        
        //! Receive the notification that a box has been created.
        /** The function is called by the page when a box has been created.
         @param object The box.
         */
        void objectCreated(sGuiObject object) override;
        
        //! Receive the notification that a box has been removed.
        /** The function is called by the page when a box has been removed.
         @param object The box.
         */
        void objectRemoved(sGuiObject object) override;
        
        //! Receive the notification that a link has been created.
        /** The function is called by the patcher when a link has been created.
         @param link   The link.
         */
        void linkCreated(sGuiLink link) override;
        
        //! Receive the notification that a link has been removed.
        /** The function is called by the patcher when a link has been removed.
         @param link   The link.
         */
        void linkRemoved(sGuiLink link) override;
        
		//! Receive the notification that the values of an attribute has changed.
		/** The function notifies the manager that the values of an attribute has changed.
		 @param attr An attribute.
		 @return pass true to notify changes to listeners, false if you don't want them to be notified
		 */
		virtual bool notify(sAttr attr) = 0;
		
        //! Create a link controller.
        /** Patcher controller's subclasses must implement this method to create custom link controller.
         @param link     The link.
         @return The newly created link controller.
         */
        virtual sLinkView createLinkView(sGuiLink link) = 0;
        
        //! Receive the notification that a link controller has been created.
        /** The function is called by the patcher when a link controller has been created.
         @param linkctrl The link controller.
         */
        virtual void linkViewCreated(sLinkView linkctrl) {};
        
        //! Receive the notification that a link controller before an object has been removed.
        /** The function is called by the patcher controller before a link has been removed.
         @param linkctrl The link controller.
         */
        virtual void linkViewWillBeRemoved(sLinkView linkctrl) {};
        
        // ================================================================================ //
        //                                      KNOCK                                       //
        // ================================================================================ //
        
        //! Test a point.
        /** The function try to find an object or then link under the point otherwise it will consider that the patcher has been touched.
         @param point The point.
         */
        Knock knockAll(Point const& point) const  noexcept;
        
        //! Test a point.
        /** The function try to find an object under the point.
         @param patcher The patcher to test.
         @param point The point.
         */
        Knock knockObjects(Point const& point) const  noexcept;
        
        //! Test a point.
        /** The function try to find an object.
         @param point The point.
         */
        Knock knockLinks(Point const& point) const  noexcept;
        
        //! Test a rectangle.
        /** The function try to find the objects and the links that overlaps the rectangle.
         @param rect The rectangle.
         @param objects The vector of objects that will be filled.
         @param links The vector of links that will be filled.
         */
        void knockAll(Rectangle const& rect, vector<sObjectView>& objects, vector<sLinkView>& links) const  noexcept;
        
        //! Test a rectangle.
        /** The function try to find the objects that overlaps the rectangle.
         @param rect The rectangle.
         @param objects The vector of objects that will be filled.
         */
        void knockObjects(Rectangle const& rect, vector<sObjectView>& objects) const  noexcept;
        
        //! Test a rectangle.
        /** The function try to find the links that overlaps the rectangle.
         @param rect The rectangle.
         @param links The vector of links that will be filled.
         */
        void knockLinks(Rectangle const& rect, vector<sLinkView>& links) const  noexcept;
    
        // ================================================================================ //
        //										MAGNET                                      //
        // ================================================================================ //
    
        struct Magnet
        {
            wObjectView    object;
            ulong       index;
            
            //! Retrieve the object view of the magnet.
            /** The function retrieves the object view of the magnet.
             @return The object view.
             */
            inline sObjectView getObject() const noexcept
            {
                return object.lock();
            }
            
            //! Retrieve the index of the iolet.
            /** The function retrieves the index of the iolet.
             @return The index of the iolet.
             */
            inline ulong getIndex() const noexcept
            {
                return index;
            }
        };
        //! Find the closest inlet to an object.
        /** The function finds the closest inlet in the patcher .
         @param objectview  The object view that won't be check (the object that owns the outlet).
         @param point    The point to compute.
         @param distance The maximum distance to look for an inlet.
         @return A magnet with the object view and the inlet index if an inlet has been found.
         */
        Magnet magnetFindInlet(sObjectView object, Point const& point, double distance = 50.) const;
    
        //! Find the closest outlet to an object.
        /** The function finds the closest outlet in the patcher.
         @param point The point to compute.
         @param object  The object that won't be check (the object that owns the link).
         @param distance The maximum distance to look for an outlet.
         @return A magnet with the object view and the outlet index if an outlet has been found.
         */
        Magnet magnetFindOutlet(sObjectView object, Point const& point, double distance = 50.) const;
    
        // ================================================================================ //
        //										LASSO                                       //
        // ================================================================================ //
    
        struct Lasso
        {
            Rectangle              bounds;
            Point                  origin;
            bool						dragging;
            set<wObjectView,
            owner_less<wObjectView>>       objects;
            set<wLinkView,
            owner_less<wLinkView>>      links;
            
            virtual ~Lasso()
            {
                objects.clear();
                links.clear();
            }
        };
        
        //! Initialize the selection of the links and the objects.
        /** The function initialize the selection of the links and the objects.
         @param point The starting point.
         @param preserve The lasso should preserve the last selection.
         */
        void lassoBegin(Lasso* lasso, Point const& point, const bool preserve);
        
        //! Perform the selection of the links and the objects.
        /** The function performs the selection of the links and the objects.
         @param point The draging point.
         @param objects The lasso should add objects to the selection.
         @param links The lasso should add links to the selection.
         @param preserve The lasso should preserve the last selection.
         */
        void lassoPerform(Lasso* lasso, Point const& point, bool objects, bool links, const bool preserve);
        
        //! Finish the selection of the links and the objects.
        /** The function finishes the selection of the links and the objects.
         @param preserve The lasso should preserve the last selection.
         */
        void lassoEnd(Lasso* lasso) const;
    
    protected:
    
        //! The redraw function that must be overriden to be notified when the patcher needs to be redrawn.
        /** The function is called by the patcher when it needs to be repainted.
         */
        virtual void redraw() {};
    
        //! Called when the patcher has been locked/unlocked.
        /** The function is called when the patcher has been locked/unlocked.
         */
        virtual void lockStatusChanged() {};
    
        //! Called when the patcher presentation mode has been activated/deactivated.
        /** The function is called when the patcher presentation mode has been activated/deactivated.
         */
        virtual void presentationStatusChanged() {};
    };
	
	// ================================================================================ //
	//								  PAGEVIEW LISTENER                                 //
	// ================================================================================ //
	
	//! The patcher view listener .
	/**
	 The patcher view listener...
	 */
	class PatcherView::Listener
	{
	public:
		virtual ~Listener() {}
		
		//! Called by the patcherView when its lock status changed.
		/** The function is called by the patcherView when its lock status changed.
		 */
		virtual void patcherViewLockStatusChanged() = 0;
		
		//! Called by the patcherView when presentation status changed.
		/** The function is called by the patcherView when presentation status changed.
		 */
		virtual void patcherViewPresentationStatusChanged() = 0;
		
		//! Called by the patcherView when selection status changed.
		/** The function is called by the patcherView when selection status changed.
		 */
		virtual void patcherViewSelectionStatusChanged() = 0;
	};

	// ================================================================================ //
	//										KNOCK										//
	// ================================================================================ //
	
    struct Knock
    {
    public:
        enum Target
        {
            Nothing = 0,
            Patcher	= 1,
            Object	= 2,
            Link	= 3
        };
		
        enum Part
        {
            Outside     = 1<<0,
            Inside      = 1<<1,
            Inlet       = 1<<2,
            Outlet      = 1<<3,
            Border      = 1<<4
        };
        
        enum BorderZone
        {
            None	= 1<<0,
            Left	= 1<<1,
            Right	= 1<<2,
            Top		= 1<<3,
            Bottom	= 1<<4,
        };
        
        wPatcherView       patcher;
        wObjectView        object;
        wLinkView       link;
        Target          target	= Nothing;
        ulong			part	= Outside;
        ulong			border	= None;
        ulong           index   = 0;
        
        
        //! Retrieve the last target touched.
        /** The function retrieves the last target touched by a point.
         @return The target.
         */
        inline Target getTarget() const noexcept
        {
            return target;
        }
        
        //! Retrieve if the last target was nothing.
        /** The function retrieves if the last target was nothing.
         @return true if the last target was nothing, otherwise false.
         */
        inline bool hasHitNothing() const noexcept
        {
            return target == Nothing;
        }
        
        //! Retrieve if the last target was an object.
        /** The function retrieves if the last target was an object.
         @return true if the last target was an object, otherwise false.
         */
        inline bool hasHitObject() const noexcept
        {
            return target == Object;
        }
        
        //! Retrieve if the last target was a link.
        /** The function retrieves if the last target was a link.
         @return true if the last target was a link, otherwise false.
         */
        inline bool hasHitLink() const noexcept
        {
            return target == Link;
        }
        
        //! Retrieve if the last target was a patcher.
        /** The function retrieves if the last target was a patcher.
         @return true if the last target was a patcher, otherwise false.
         */
        inline bool hasHitPatcher() const noexcept
        {
            return target == Patcher;
        }
        
        //! Retrieve the object that has been touched.
        /** The function retrieves the object that has been touched.
         @return The object that has been touched if the last target was an object.
         */
        inline sObjectView getObject() const noexcept
        {
            if(target == Object)
            {
                return object.lock();
            }
            return nullptr;
        }
        
        //! Retrieve the link that has been touched.
        /** The function retrieves the link that has been touched.
         @return The link that has been touched if the last target was a link.
         */
        inline sLinkView getLink() const noexcept
        {
            if(target == Link)
            {
                return link.lock();
            }
            return nullptr;
        }
        
        //! Retrieve the patcher that has been touched.
        /** The function retrieves the patcher that has been touched.
         @return The patcher that has been touched if the last target was a patcher.
         */
        inline sPatcherView getPatcher() const noexcept
        {
            if(target == Patcher)
            {
                return patcher.lock();
            }
            return nullptr;
        }
        
        //! Retrieve the part of the target that has been touched.
        /** The function retrieves the part of the target that has been touched. If an object has been touched, it can be one of all the parts. If a link has been touched, it can only be the four first parts. If a patcher has been touched, it can be inside or outside. It nothing has been touched yet, it will be outside.
         @return The part of the target that has been touched.
         */
        inline ulong getPart() const noexcept
        {
            if(target == Object)
            {
                return part;
            }
            else if(target == Link)
            {
                return clip(part, (ulong)Outside, (ulong)Outlet);
            }
            else if(target == Patcher)
            {
                return clip(part, (ulong)Outside, (ulong)Inside);
            }
            return Outside;
        }
        
        //! Retrieve the type of border if a border of an object has been touched.
        /** The function retrieves the type of border if a border of an object has been touched.
         @return The type of border if a border of an object has been touched.
         */
        inline ulong getBorder() const noexcept
        {
            if(target == Object)
            {
                return border;
            }
            return None;
        }
        
        //! Retrieve the index of the part of the object.
        /** The function retrieves the index of the part of the object. If the part is an inlet or an outlet, it will be their index. If the part is a border or a corner it will be their position.
         @return The index of the part of the object.
         */
        inline ulong getIndex() const noexcept
        {
            if(target == Object)
            {
                return index;
            }
            return 0;
        }
    };
}


#endif


