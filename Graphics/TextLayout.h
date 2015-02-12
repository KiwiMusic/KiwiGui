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

#ifndef __DEF_KIWI_GUI_TEXTLAYOUT__
#define __DEF_KIWI_GUI_TEXTLAYOUT__

#include "Font.h"

namespace Kiwi
{
    namespace Gui
    {
        // ================================================================================ //
        //									  TEXTLAYOUT                                    //
        // ================================================================================ //
        
        //! The textlayout is almost a pure virtual class that should be overridden depending on the graphical implementation.
        /**
         The textlayout...
         */
        class TextLayout
        {
        public:
            
            //! Constructor.
            /** The function does nothing.
             */
            TextLayout()
            {
                ;
            }
            
            //! Destrcutor.
            /** The function does nothing.
             */
            virtual ~TextLayout()
            {
                ;
            }
			
			//! Set the text and attributes.
			/**	This function sets the text and attributes of the textfield.
			 @param	text			The text to render.
			 @param	font			The font with which to render the text.
			 @param	bounds			The text is placed within the specified rect.
			 @param	justification	How to justify the text within the rect.
			 @param	wordwrap		enable/disable word wrapping.
			 @param	ellipsis		show/don't show ... if a line doesn't fit bounds (implies enabled word wrapping).
			 */
			virtual void set(wstring const& text,
							 Font const& font,
							 Rectangle const& bounds,
							 Font::Justification justification,
							 const bool wordwrap = false,
							 const bool ellipsis = false) = 0;
			
			//! Set the text color.
			/**	This function sets the text color.
			 @param	textcolor	The color for the text.
			 */
			virtual void setTextColor(Color const& textcolor) = 0;
			
			//! Return a measurement of how much space will be required to draw the text.
			/**	This function return a measurement of how much space will be required to draw the text.
			 @param	startindex			You can measure a subset of the characters, this defines the character from which to start.
			 @param	numchars			Pass -1 for all characters from startindex to end.
			 @param	includewhitespace	Define whether to measure with or without whitespace truncated from edges.
			 @param	width				Returns the width of text not including any margins.
			 @param	height				Returns the height of text not including any margins.
			 @param	numlines			Returns the number of lines of text.
			 */
			virtual void measure(long startindex, long numchars, const bool includewhitespace, double *width, double *height, long *numlines) = 0;
			
			//! Retrieve a count of the number of characters.
			/** This function retrieves a count of the number of characters.
			 @return		The number of characters.
			 */
			virtual long getNumberOfCharacters() const noexcept = 0;
			
			//! Retrieve the rectangle containing a character at a given index.
			/**	This function retrieves the rectangle containing a character at a given index.
			 @param	index	The index from which to fetch the character.
			 @param	rect	The address of a valid #t_rect which will be filled in upon return.
			 @return		A Kiwi error code.
			*/
			virtual void getCharRect(long index, Rectangle* rect) = 0;

			//!	Retrieve the character at a given index.
			/**	This function retrieves the character at a given index.
			 @param	index	The index from which to fetch the unicode character.
			 @param	pch		The address of a variable to hold the unicode character value upon return.
			 @return		A Kiwi error code.
			 */
			virtual void getCharAtIndex(long index, long *pch) = 0;
        };        
    }
}

#endif