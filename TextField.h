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

#ifndef __DEF_KIWI_GUI_TEXTFIELD__
#define __DEF_KIWI_GUI_TEXTFIELD__

#include "Defs.h"

namespace Kiwi
{
    namespace Gui
    {
        // ================================================================================ //
        //                                     TEXTFIELD                                    //
        // ================================================================================ //
        
        class TextField
        {
			typedef shared_ptr<TextField>	sTextField;
		public:
			class Owner;
			typedef shared_ptr<Owner>	sOwner;
			typedef weak_ptr<Owner>		wOwner;
			
			// ================================================================================ //
			//                                 TEXTFIELD OWNER                                  //
			// ================================================================================ //
			
            class Owner
            {
            public:
				//! Retrieve the number of nodes of the path.
				/** The function retrieves the number of nodes of the path.
				 @return The number of nodes of the path.
				 */
				Owner() {};
				virtual ~Owner() {}
				
				/** This function is called whenever text is entered into the editor.
				 An implementation of this class should check the input string,
				 and return an edited version of it that should be used.
				 @param newtext The new entered text
				 @return true if you want to pass the key
				 */
				virtual bool textEntered(wstring& newtext) { return true; };
				
				virtual void textChanged(sTextField textfield) {};
				
                void setText();
                void setTextBounds();
				virtual void returnPressed() {};
				virtual void escapePressed() {};
				virtual void getText(wstring const& text) {};
            };
            
            void setText(wstring const& text)
            {
                m_owner->setText();
            }
            
            void setTextBounds(Rectangle const& rect)
            {
                m_owner->setTextBounds();
            }
            
        private:
            sOwner m_owner;
            void setOwner(sOwner owner)
            {
                m_owner = owner;
            }
        };
		
		typedef shared_ptr<TextField>	sTextField;
    }
}

#endif