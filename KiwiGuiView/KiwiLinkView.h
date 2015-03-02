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

#ifndef __DEF_KIWI_VIEW_LINK__
#define __DEF_KIWI_VIEW_LINK__

#include "KiwiPatcherView.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  LINK VIEW                                       //
    // ================================================================================ //
    
    //! The link controller .
    /**
     The link controller...
     */
    class LinkView
    {
    private:
        sGuiLink        m_link;
        Kiwi::Path		m_path;
        bool			m_selected;
        
    public:
        
        //! Constructor.
        /** You should never call this method except if you really know what you're doing.
         */
        LinkView(sGuiLink link) noexcept;
        
        //! The destructor.
        /** You should never call this method except if you really know what you're doing.
         */
        virtual ~LinkView();
        
        //! The link view maker.
        /** The function creates an controller with arguments.
         @param link The link.
         @param args The arguments.
         @return The link view.
         */
        template<class Class, class ...Args> static shared_ptr<Class> create(sGuiLink link)
        {
            return make_shared<Class>(link);
        }
        
        //! The link view maker.
        /** The function creates an controller with arguments.
         @param link The link.
         @param args The arguments.
         @return The link view.
         */
        template<class Class, class ...Args> static shared_ptr<Class> create(sGuiLink link, Args&& ...args)
        {
            return make_shared<Class>(link, forward<Args>(args)...);
        }
        
        //! Get the link of the view.
        /** The function retrieves the link of the view.
         @return The link.
         */
        inline sGuiLink getLink() const noexcept
        {
            return m_link;
        }
        
        //! Retrieve the bounds of the link.
        /** The function retrieves  the bounds of the link.
         @return The bounds of the link.
         */
        inline Kiwi::Rectangle getBounds() const noexcept
        {
            int todo;
            return Kiwi::Rectangle(0., 0., 100., 100.);
        }
        
        //! Notify that the link is selected.
        /** The function notifies that the link is selected and needs to be redrawn.
         @param status true if the link is selected, otherwise false.
         */
        void setSelectedStatus(bool status);
        
        //! Retrieve if the link is selected.
        /** The function retrieves if the link is selected.
         @param True if the link is selected, otherwise false.
         */
        inline bool isSelected() const noexcept
        {
            return m_selected;
        }
        
        //! Retrieve if the link is touch by a point.
        /** The function retrieves if the link is touch by a point and fill the knock with the knock informations.
         @param point The point.
         @param knock The knock.
         @return true if the link is touch by the point, otherwise false.
         */
        virtual bool contains(Kiwi::Point const& point, Knock& knock) const noexcept;
        
        //! Retrieve if the link is overlaps the rectangle.
        /** The function retrieves if the link is overlaps the rectangle.
         @param rect The Rectangle.
         @return true if the link overlaps the rectangle, otherwise false.
         */
        virtual bool overlaps(Kiwi::Rectangle const& rect) const noexcept;
        
        //! The bounds notification function that should be override.
        /** The function is called by the link when its bounds changed.
         */
        virtual void boundsChanged() = 0;
        
        //! The redraw function that should be override.
        /** The function is called by the link when it should be repainted.
         */
        virtual void redraw() = 0;
        
        //! The default paint method.
        /** The default function paint a default link.
         @param link        The link to draw.
         @param d           The doodle to draw in.
         @param selected    If the link is selected
         */
        static void paint(sGuiLink link, Kiwi::Doodle& d, bool selected = false);
    };
    
    // ================================================================================ //
    //                                  LINK CREATOR                                    //
    // ================================================================================ //
    
    class LinkCreator
    {
    private:
        wGuiObject		m_object_from;
        wGuiObject		m_object_to;
        ulong           m_index_outlet;
        ulong           m_index_intlet;
        Kiwi::Path      m_path;
        
    public:
        
        //! The constructor.
        /** You should never use this method.
         */
        LinkCreator(const sGuiObject from, const unsigned outlet, const sGuiObject to, const unsigned inlet) noexcept;
        
        //! The destructor.
        /** You should never use this method.
         */
        ~LinkCreator();
        
        //! The creator creation method with sockets.
        /** The function allocates a creator.
         @param from    The object that send.
         @param outlet  The index of the outlet.
         @param to      The object that receive.
         @param inlet   The index of the inlet.
         @return The creator.
         */
        static shared_ptr<LinkCreator> create(const sGuiObject from, const unsigned outlet, const sGuiObject to, const unsigned inlet);
        
        //! Retrieve if the creator owns the objects.
        /** The function retrieves if the creator owns the two objects.
         @return true if the creator owns the two objects, otherwise false.
         */
        inline bool hasObjectes() const noexcept
        {
            return !LinkCreator::m_object_from.expired() && LinkCreator::m_object_to.expired();
        }
        
        //! Retrieve if the creator owns the output object.
        /** The function retrieves if the creator owns the output object.
         @return true if the creator owns the output object, otherwise false.
         */
        inline bool hasObjectFrom() const noexcept
        {
            return !LinkCreator::m_object_from.expired();
        }
        
        //! Retrieve if the creator owns the input object.
        /** The function retrieves if the creator owns the input object.
         @return true if the creator owns the input object, otherwise false.
         */
        inline bool hasObjectTo() const noexcept
        {
            return !LinkCreator::m_object_to.expired();
        }
        
        //! Retrieve the index of the outlet of the creator.
        /** The function retrieves the index of the outlet of the creator.
         @return The index of the outlet of the creator.
         */
        inline ulong getOutletIndex() const noexcept
        {
            return LinkCreator::m_index_outlet;
        }
        
        //! Retrieve the index of the inlet of the creator.
        /** The function retrieves the index of the inlet of the creator.
         @return The index of the inlet of the creator.
         */
        inline ulong getInletIndex() const noexcept
        {
            return LinkCreator::m_index_intlet;
        }
        
        //! Retrieve the output object.
        /** The function retrieves the output object of the creator.
         @return The output object.
         */
        inline sGuiObject getObjectFrom() const noexcept
        {
            return m_object_from.lock();
        }
        
        //! Retrieve the input object.
        /** The function retrieves the input object of the creator.
         @return The input object.
         */
        inline sGuiObject getObjectTo() const noexcept
        {
            return m_object_to.lock();
        }
        
        /** Call this in your mouseDrag event, to update the link's position.
         This must be repeatedly calling when the mouse is dragged, after you've
         first initialised the link with beginLink().
         */
        void drag(Kiwi::Point const& point)
        {
            /*
            if(m_path.size() == 1)
            {
                m_path.lineTo(point);
            }
            else
            {
                m_path.setPoint(m_path.size() - 1, point);
            }
            */
        }
    };
    
    
}


#endif


