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

#include "Keyboarder.h"

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
			typedef weak_ptr<TextField>		wTextField;
			
		public:
			class Owner;
			typedef shared_ptr<Owner>		sOwner;
			typedef weak_ptr<Owner>			wOwner;
			typedef shared_ptr<const Owner> scOwner;
			typedef weak_ptr<const Owner>   wcOwner;
			
		private:
			sOwner m_owner;
			void setOwner(sOwner owner)
			{
				m_owner = owner;
			}
			
		public:
			virtual ~TextField() {}
			
			virtual void setText(wstring const& newtext) = 0;
			
			void setTextBounds();
			
			void getText(wstring const& text) {};
			
			void setTextBounds(Rectangle const& rect)
			{
				//m_owner->setTextBounds();
			}
			
			// ================================================================================ //
			//                                 TEXTFIELD OWNER                                  //
			// ================================================================================ //
			
            class Owner // ex : object
            {
			private:
				wstring						m_text;
				set<wTextField,
				owner_less<wTextField>>		m_textfields;
				mutable mutex				m_textfields_mutex;
				
            public:
				Owner() {};
				virtual ~Owner() {}
				
				//! This function is called whenever text is entered into the editor.
				/** An implementation of this class should check the input string,
				 and return an edited version of it that should be used.
				 @param newtext The new entered text.
				 @return True if you want to pass the key to the textfield, false otherwise. 
				 */
				virtual bool textEntered(sTextField textfield, wstring& newtext) { return true; };
				
				//! This function is called when the text of the textfield changed.
				/** An implementation of this class should check the new text and do something with it.
				 @param textfield The textfield that changed.
				 */
				virtual void textChanged(sTextField textfield) {};
				
				//! This function is called when the user pressed the return key.
				/** This function is called when the user pressed the return key.
				 @param textfield The textfield in which the user pressed the return key.
				 */
				virtual void returnPressed() {};
				
				//! This function is called when the user pressed the escape key.
				/** This function is called when the user pressed the escape key.
				 @param textfield The textfield in which the user pressed the escape key.
				 */
				virtual void escapePressed() {};
				
				//! Adds a textfield to be managed by the textfield owner.
				/** The function adds a textfield to be managed by the textfield owner.
				 @param textfield The textfield to add.
				 */
				void addTextfield(sTextField textfield)
				{
					if(textfield)
					{
						lock_guard<mutex> guard(m_textfields_mutex);
						m_textfields.insert(textfield);
					}
				}
				
				//! Removes a textfield thas was managed by the textfield owner.
				/** The function removes a textfield thas was managed by the textfield owner.
				 If the textfield wasn't managed by the the textfield owner, the function does nothing.
				 @param textfield The textfield to remove.
				 */
				void removeTextField(sTextField textfield)
				{
					if(textfield)
					{
						lock_guard<mutex> guard(m_textfields_mutex);
						m_textfields.erase(textfield);
					}
				}
				
				//! Removes a view from the sketcher.
				/** The function removes a view from the sketcher. The view will no longer be notified when the sketcher needs to be redrawn.
				 If the view wasn't a sketcher's view, the function does nothing.
				 @param view The textfield to remove.
				 */
				void setText(wstring const& newtext)
				{
					m_textfields_mutex.lock();
					auto it = m_textfields.begin();
					while(it != m_textfields.end())
					{
						if((*it).expired())
						{
							it = m_textfields.erase(it);
						}
						else
						{
							sTextField textfield = (*it).lock();
							textfield->setText(newtext);
							++it;
						}
					}
					m_textfields_mutex.unlock();
				}
            };
        };
		
		typedef shared_ptr<TextField>		sTextField;
		typedef weak_ptr<TextField>         wTextField;
		typedef shared_ptr<const TextField> scTextField;
		typedef weak_ptr<const TextField>   wcTextField;
    }
}

#endif