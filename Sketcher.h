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

#include "Doodle.h"
#include "Event.h"

namespace Kiwi
{
    namespace Gui
    {
        // ================================================================================ //
        //                                      SKETCHER                                    //
        // ================================================================================ //
        
        class Sketcher
        {
            
        public:
            class View
            {
            protected:
                virtual void redraw() = 0;
                
            public:
                View() noexcept
                {
                    ;
                }
                
                virtual ~View()
                {
                    ;
                }
            };
            typedef shared_ptr<View>    sView;
            typedef weak_ptr<View>      wView;
            
        private:
            
            set<wView, owner_less<wView>>   m_views;
            mutable mutex                   m_views_mutex;
        public:
            Sketcher()
            {
                ;
            }
            
            virtual ~Sketcher()
            {
                ;
            }
            
            //! The paint method that should be override.
            /** The function shoulds draw some stuff in the doodle. Return false if you don't want to draw then the box manager will draw the text of the box, othersize return true.
             @param doodle    A doodle to draw.
             */
            virtual void draw(Doodle& doodle) const = 0;
            
        protected:
            
            //! Send a notification to the view that the box should be redraw.
            /** The function sends a notification to the view that the box should be redraw.
             */
            void redraw() const noexcept
            {
                
            }
        };
		
		typedef shared_ptr<Sketcher>          sSketcher;
		typedef weak_ptr<Sketcher>            wSketcher;
		typedef shared_ptr<const Sketcher>    scSketcher;
		typedef weak_ptr<const Sketcher>      wcSketcher;
		
        class Mouser
        {
        public:
            Mouser() noexcept
            {
                ;
            }
            
            virtual ~Mouser()
            {
                ;
            }
            
            //! The receive method that should be override.
            /** The function shoulds perform some stuff.
             @param event    A mouse event.
             */
            virtual bool receive(Event::Mouse const& event) = 0;
        };
        
        typedef shared_ptr<Mouser>          sMouser;
        typedef weak_ptr<Mouser>            wMouser;
        typedef shared_ptr<const Mouser>    scMouser;
        typedef weak_ptr<const Mouser>      wcMouser;
        
        class Keyboarder
        {
        public:
            Keyboarder() noexcept
            {
                ;
            }
            
            virtual ~Keyboarder()
            {
                ;
            }
            //! The receive method that should be override.
            /** The function shoulds perform some stuff.
             @param event    A keyboard event.
             */
            virtual bool receive(Event::Keyboard const& event) = 0;
            
            //! The receive method that should be override.
            /** The function shoulds perform some stuff.
             @param event    A focus event.
             */
            virtual bool receive(Event::Focus event)
            {
                return false;
            }
            
        protected:
            
            //! Send a notification to the controler that the box should be redraw.
            /** The function sends a notification to the controler that the box should be redraw.
             */
            void grabKeyboardFocus() const noexcept
            {
                ;
            }
        };
        
        typedef shared_ptr<Keyboarder>          sKeyboarder;
        typedef weak_ptr<Keyboarder>            wKeyboarder;
        typedef shared_ptr<const Keyboarder>    scKeyboarder;
        typedef weak_ptr<const Keyboarder>      wcKeyboarder;
    }
}

#endif