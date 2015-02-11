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

#include "Attribute.h"

namespace Kiwi
{
    namespace Gui
    {
        // ================================================================================ //
        //                                      SKETCHER                                    //
        // ================================================================================ //
        
        //! The sketcher...
        /** The sketcher...
         */
        class Sketcher : virtual public Attr::Manager
        {
		public:
            class Listener;
            typedef shared_ptr<Listener>        sListener;
            typedef weak_ptr<Listener>          wListener;
            typedef shared_ptr<const Listener>  scListener;
            typedef weak_ptr<const Listener>    wcListener;
			
        protected:
            const sAttrPoint  m_position;
            const sAttrSize   m_size;
        private:
            set<wListener,
            owner_less<wListener>> m_lists;
            mutable mutex          m_lists_mutex;
			
        public:
            
            //! Constructor.
            /** The function does nothing.
             */
            Sketcher() noexcept;
            
            //! Destructor.
            /** The function does nothing.
             */
            virtual ~Sketcher();
            
            template<class T, class ...Args> static shared_ptr<T> create(Args&& ...args)
            {
                shared_ptr<T> sketcher = make_shared<T>(forward<Args>(args)...);
                if(sketcher)
                {
                    sketcher->Sketcher::initialize();
                    sketcher->initialize();
                }
                return sketcher;
            }
			
			//! Adds a listener to the sketcher.
			/** The function adds a listener to the sketcher.
			 @param listener The listener to add.
			 */
            void addListener(sListener listener);
			
			//! Removes a listener from the sketcher.
			/** The function removes a listener from the sketcher. 
             @param listener The listener to remove.
			 */
            void removeListener(sListener listener);
			
            //! The paint method that should be override.
            /** The function shoulds draw some stuff in the doodle.
             @param doodle A doodle to draw.
             */
            virtual void draw(Doodle& doodle) const = 0;
            
            //! Retrieve the position of the object.
            /** The function retrieves the position of the object.
             @return The position of the object.
             */
            inline Point getPosition() const noexcept
            {
                return m_position->getValue();
            }
            
            //! Retrieve the size of the object.
            /** The function retrieves the size of the object.
             @return The size of the object.
             */
            inline Size getSize() const noexcept
            {
                return m_size->getValue();
            }
            
            //! Retrieve the bounds of the object.
            /** The function retrieves the bounds of the object.
             @return The bounds of the object.
             */
            inline Rectangle getBounds() const noexcept
            {
                 return Rectangle(m_position->getValue(), m_size->getValue());
            }
            
        protected:
            
            //! Send a notification to each listeners that the object needs to be redrawn.
            /** The function sends a notification to each listeners that the object should be redrawn.
             */
            void redraw() noexcept;
        };
        
        //! The sketcher listener...
        /** The sketcher listener...
         */
        class Sketcher::Listener
        {
        public:
            
            Listener() noexcept
            {
                ;
            }
            
            virtual ~Listener()
            {
                ;
            }
            
            //! Receives the notification that the sketcher needs to be redrawn.
            /** This function is called by the sketcher whenever it needs to be redrawn.
             The listener sublasses must implement this method to draw the sketcher.
             */
            virtual void redraw() = 0;
        };
    }
}

#endif