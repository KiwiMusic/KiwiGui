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

#ifndef __DEF_KIWI_VIEW_BOX__
#define __DEF_KIWI_VIEW_BOX__

#include "KiwiLinkView.h"

namespace Kiwi
{
    
    // ================================================================================ //
    //                                      BOX                                         //
    // ================================================================================ //
    
    //! The object view.
    /**
     The object view...
     */
	class ObjectView :	public enable_shared_from_this<ObjectView>,
						public Attr::Listener,
						public Sketcher::Listener,
						public Writer::View,
						public PatcherView::Listener
    {
    private:
        const wGuiObject	m_object;
        const wPatcherView	m_patcher_view;
        bool				m_selected;
        
    public:
        
        //! Constructor.
        /** You should never call this method except if you really know what you're doing.
         */
        ObjectView(sGuiObject object, sPatcherView patcherview) noexcept;
        
        //! The destructor.
        /** You should never call this method except if you really know what you're doing.
         */
        virtual ~ObjectView();
        
        //! The object view maker.
        /** The function creates a bow view with arguments.
         @param object The object.
         @param patcherview The patcher view.
         @param args The arguments.
         @return The object view.
         */
        template<class Class, class ...Args> static shared_ptr<Class> create(sGuiObject object, sPatcherView patcherview, Args&& ...args)
        {
            if(object && patcherview)
            {
                shared_ptr<Class> objectview = make_shared<Class>(object, patcherview, forward<Args>(args)...);
                if(objectview)
                {
                    object->addListener(objectview);
					
					vector<sAttr> attrs;
					object->getAttrs(attrs, {"position", "presentation_position", "size", "presentation_size", "presentation"});
					for (auto attr : attrs)
					{
						attr->addListener(objectview);
					}
					
					patcherview->addListener(objectview);
					
					Kiwi::sWriter writer = dynamic_pointer_cast<Kiwi::Writer>(object);
					if (writer)
					{
						Kiwi::Writer::sTextField textfield = writer->getTextField();
						if(textfield)
						{
							textfield->setWriter(writer);
						}
						
						writer->addView(objectview);
					}
					
					objectview->init();
					
                    return objectview;
                }
            }
            return nullptr;
        }
		
		//! Receive the notification that an attribute changed.
		/** The function receive notification when an attribute or when its value changed.
		 @param attr		The attribute that has been modified.
		 */
		void notify(sAttr attr);
		
        //! Retrieve the object.
        /** The funtion retrieves the object.
         @return The object.
         */
        inline sGuiObject getObject() const noexcept
        {
            return m_object.lock();
        }
        
        //! Retrieve the patcher view.
        /** The funtion retrieves the patcher view.
         @return The patcher view.
         */
        inline sPatcherView getPatcherView() const noexcept
        {
            return m_patcher_view.lock();
        }
        
        //! Retrieve if the patcher is locked/unlocked.
        /** The function retrieves if the patcher is locked/unlocked.
         @param true if the patcher is locked, false if unlocked.
         */
        bool getPatcherLockStatus() const noexcept;
        
        //! Retrieve if the patcher is in presentation mode.
        /** The function retrieves if the patcher is in presentation mode.
         @param true if the patcher is in presentation mode, otherwise false.
         */
        bool getPatcherPresentationStatus() const noexcept;
        
        //! Retrieve the text of the object.
        /** The funtion retrieves the text of the object.
         @return The text of the object.
         */
        string getText() const noexcept;
        
        //! Retrieve the bounds of the object.
        /** The function retrieves the bounds of the object.
         @return The position of the object.
         */
        Rectangle getBounds() const noexcept;
        
        //! Retrieve the display bounds of the object view.
        /** The function retrieves the display bounds of the object view.
         @return The bounds of the object view.
         */
        virtual Rectangle getDisplayBounds() const noexcept;
        
        //! Retrieve the position of the object.
        /** The function retrieves the position of the object.
         @return The position of the object.
         */
        Point getPosition() const noexcept;
        
        //! Retrieve the display position of the object view.
        /** The function retrieves the display position of the object view.
         @return The position of the object view.
         */
        virtual Point getDisplayPosition() const noexcept;
        
        //! Retrieve the size of the object.
        /** The function retrieves the size of the object.
         @return The size of the object.
         */
        inline Point getSize() const noexcept;
        
        //! Retrieve the display size of the object view.
        /** The function retrieves the display size of the object view.
         @return The size of the object view.
         */
        virtual Point getDisplaySize() const noexcept;
		
        //! Retrieves if the object should be hidden when the patcher is locked.
        /** The function retrieves if the object should be hidden when the patcher is locked.
         @return True if the object should be hidden when the patcher is locked, false otherwise.
         */
        inline bool isHiddenOnLock() const noexcept;
        
        //! Retrieve if the object should be displayed in presentation.
        /** The function retrieves if the object should be displayed in presentation.
         @return True if the object should be displayed in presentation, otherwise false.
         */
        bool isIncludeInPresentation() const noexcept;
        
        //! Retrieve if the object is selected.
        /** The function retrieves if the object is selected.
         @param true if the object is selected, otherwise false.
         */
        bool isSelected() const noexcept;
        
        //! Retrieve if the object is visible.
        /** The function retrieves if the object is visible.
         @param true if the object is visible, otherwise false.
         */
        bool isVisible() const noexcept;
        
        //! Retrieve the number of inlets of the object.
        /** The functions retrieves the number of inlets of the object.
         @return The number of inlets.
         */
        ulong getNumberOfInlets() const noexcept;
        
        //! Retrieve the number of outlets of the object.
        /** The functions retrieves the number of outlets of the object.
         @return The number of outlets.
         */
        ulong getNumberOfOutlets() const noexcept;
        
        //! Retrieve the display size of an inlet/outlet.
        /** The function retrieves the display size of an inlet/outlet.
         @return The display size of an inlet/outlet.
         */
        virtual Point getIOSize() const noexcept;
        
        //! Retrieve the position of an inlet.
        /** The function retrieves the position of an inlet.
         @param index The index of the inlet.
         @return the position of the inlet as a point.
         */
        virtual Point getInletPosition(const ulong index) const noexcept;
        
        //! Retrieve the position of an outlet.
        /** The function retrieves the position of an outlet.
         @param index The index of the outlet.
         @return The position of the outlet as a point.
         */
        virtual Point getOutletPosition(const ulong index) const noexcept;
        
        //! Retrieve the bounds of an inlet.
        /** The function retrieves the bounds of an inlet.
         @param index The index of the inlet.
         @return The bounds of the inlet as a Rectangle.
         */
        virtual Kiwi::Rectangle getInletBounds(const ulong index) const noexcept;
        
        //! Retrieve the bounds of an outlet.
        /** The function retrieves the bounds of an outlet.
         @param index The index of the outlet.
         @return The bounds of the outlet as a rectangle.
         */
        virtual Kiwi::Rectangle getOutletBounds(const ulong index) const noexcept;
		
        //! Retrieve if the object is touched by a point.
		/** The function retrieves if the object is touch by a point and fill the knock with the knock informations (depending on the current presentation status mode).
         @param point The point.
         @param knock The knock.
         @return true if the object is touched by the point, otherwise false.
         */
        virtual bool contains(Point const& point, Knock& knock) const noexcept;
		
		//! Tests if a point is inside an object resizer zone.
		/** The function tests if a point is inside an object resizer zone. The point is relative to the patcher top-left's coordinates
		 @param point The point to test.
		 @return A flag describing the resizer zone as defined in the Knock::Border enum.
		 */
		virtual ulong resizerKnock(Point const& point) const noexcept;
		
        //! Tests if the object overlaps the rectangle.
        /** The function tests if the object overlaps the rectangle (depending on the current presentation status mode).
         @param rect The Rectangle.
         @return True if the object overlaps the rectangle, otherwise false.
         */
        virtual bool overlaps(Kiwi::Rectangle const& rect) const noexcept;
        
        //! Notify that the object is selected.
        /** The function notifies that the object is selected to redraw the object.
         @param status true if the object is selected, otherwise false.
         */
        void setSelectedStatus(bool status);
		
		/** This function is called just after the objectview has been created.
		 */
		virtual void init() = 0;
		
		//! Receive the notification that the view is currently being edited.
		/** The function is called if the view is currently being edited.
		 */
		virtual void textFieldEditorShown() = 0;
		
		//! Receives the notification that the textfield's text changed.
		/** The function receives the notification that the textfield's text changed
		 */
		virtual void textfieldTextChanged() = 0;
		
        //! The position notification function that should be override.
        /** The function is called by the object when its position changed.
         */
        virtual void positionChanged() = 0;
        
        //! The size notification function that should be override.
        /** The function is called by the object when its size changed.
         */
        virtual void sizeChanged() = 0;
        
        //! The size notification function that should be override.
        /** The function is called by the object when its size changed.
         */
        virtual void patcherViewLockStatusChanged() = 0;
        
        //! The patcher presentation notification function.
        /** The function is called by the object when patcher presentation mode changed.
         */
        virtual void patcherViewPresentationStatusChanged() = 0;
        
        //! Called by the object when the object selection status changed.
        /** The function is called by the object selection status changed.
         */
        virtual void patcherViewSelectionStatusChanged() = 0;
		
		//! The patcher presentation notification function.
		/** The function is called by the object when patcher presentation mode changed.
		 */
		virtual void presentationStatusChanged() = 0;
        
        //! The redraw function that should be override.
        /** The function is called by the object when it should be repainted.
         */
        virtual void redraw() = 0;
        
        //! The grab focus function that should be override.
        /** The function is called by the object when it want to grab keyboard focus.
         */
        virtual void grabKeyboardFocus() = 0;
    };
}


#endif


