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

#ifndef __DEF_KIWI_GUI_CLASSIC__
#define __DEF_KIWI_GUI_CLASSIC__

#include "../Models/Models.h"

namespace Kiwi
{
    namespace Gui
    {
		// ================================================================================ //
		//                                     DEFAULT                                      //
		// ================================================================================ //
		
		class Default : public Gui::Writer
		{
		protected:
			sAttrColor    m_color_background;
			sAttrColor    m_color_border;
			
			virtual void doubleClick() {};
			
		public:
			Default() noexcept;
			virtual ~Default();
			
			bool textFilter(wstring& newtext) override;
			void textChanged() override;
			void draw(Doodle& doodle) const override;
			bool notify(sAttr attr) override;
		};
		
		
		// ================================================================================ //
		//                                      BUTTON                                      //
		// ================================================================================ //
		
		
        class Button : virtual public Sketcher, virtual public Mouser
        {
        protected:
            const sAttrColor    m_color_background;
            const sAttrColor    m_color_border;
            const sAttrColor    m_color_circle;
            const sAttrColor    m_color_led;
            atomic_bool         m_led;
        public:
            Button() noexcept;
            virtual ~Button();
            bool receive(Mouser::Event const& event) override;
            void draw(Doodle& doodle) const override;
            bool notify(sAttr attr) override;
            virtual void bang() {};
        };
    }
}

#endif


