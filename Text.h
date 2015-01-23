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

#ifndef __DEF_KIWI_TEXT__
#define __DEF_KIWI_TEXT__

#include "Doodle.h"
#include "Event.h"

namespace Kiwi
{
    namespace Gui
    {
        // ================================================================================ //
        //									  TEXTEDITOR                                    //
        // ================================================================================ //
        
        class TextEditor
        {
        private:
            wstring             m_text;
            wstring::size_type  m_marker_start;
            wstring::size_type  m_marker_end;
			
			/*
			string             m_text;
			string::size_type  m_marker_start;
			string::size_type  m_marker_end;
			*/
			
			bool				m_multiline;
			bool				m_word_wrap;
			bool				m_return_key_starts_new_line;
			bool				m_tab_key_used;
			bool				m_select_all_when_focused;
            
            Font                m_font;
            Font::Justification m_justification;
            Color               m_text_color;
            vector<string>      m_displayed_text;
            
            Rectangle           m_bounds;
            double              m_padding_top;
            double              m_padding_left;
            double              m_padding_bottom;
            double              m_padding_right;
            
            double              m_displayed_width;
            double              m_displayed_height;
            double              m_line_spacing;
            
            Point               m_text_size;
            Point               m_text_displayed_size;
			
            void updateBoundaries();
            void truncate();
            void wrap();
			
			wstring string_to_wstring(const string& str) const;
			string wstring_to_string(const wstring& wstr) const;
			
			class Listener;
			typedef shared_ptr<Listener>    sListener;
			typedef weak_ptr<Listener>      wListener;
        public:
            
            //! Constructor.
            /** The function initialize a texteditor with an empty text.
             */
            TextEditor();
            
            //! Constructor.
            /** The function initialize a texteditor with a string.
             */
            TextEditor(string const& text);
            
            //! Destructor.
            /** The function initialize a text with a string.
             */
            virtual ~TextEditor();
			
			//! Puts the editor into either multi- or single-line mode.
			/** This function puts the editor into either multi- or single-line mode.
			 By default, the editor will be in single-line mode, so use this if you need a multi-line editor.
			 See also the setReturnKeyStartsNewLine() method, which will also need to be turned
			 on if you want a multi-line editor with line-breaks.
			 @see isMultiLine, setReturnKeyStartsNewLine
			 */
			void setMultiLine(const bool shouldBeMultiLine, const bool shouldWordWrap = true);
			
			//! Returns true if the editor is in multi-line mode.
			/** This Function returns true if the editor is in multi-line mode.
			 */
			bool isMultiLine() const noexcept;

			//! Selects all the text when texteditor is focused on.
			/** If set to true (false by default), focusing on the editor will highlight all its text.
			 This is useful for boxes where you expect the user to re-enter all the
			 text when they focus on, rather than editing what's already there.
			 */
			void setSelectAllWhenFocused(const bool b);
			
			//! Changes the behaviour of the return key.
			/** The function changes the behaviour of the return key.
			 If set to true, the return key will insert a new-line into the text; if false
			 it will trigger a call to the TextEditor::Listener::textEditorReturnKeyPressed()
			 method. By default this is set to false, and when true it will only insert
			 new-lines when in multi-line mode (see setMultiLine()). 
			 */
			void setReturnKeyStartsNewLine(const bool shouldStartNewLine);
			
			//! Indicates whether the tab key accepted as character or not (default is not).
			/** Indicates whether the tab key should be accepted and used to input a tab character, or whether it gets ignored.
			 */
			void setTabKeyUsedAsCharacter(const bool shouldTabKeyBeUsed);
			
			//! Sets the font to be used by the text editor.
			/** The function sets the font to be used by the text editor.
			 @param font The font.
			 */
			void setFont(Font const& font) noexcept;
			
			//! Sets the justification of the text editor.
			/** The function sets the justification of the text editor.
			 @param justification The justification.
			 */
			void setJustification(Font::Justification const& justification) noexcept;
			
			//! Sets the color of the text.
			/** The function sets the color of the text.
			 @param color The color to use to draw the text.
			 */
			void setTextColor(Color const& color) noexcept;

			//! Sets the bounds of the text editor relative to its parent origin.
			/** The function sets the bounds of the text editor relative to its parent origin.
			 @param bounds The bounds of the text editor relative to its parent origin.
			 */
			void setBounds(Rectangle const& bounds) noexcept;
			
			void setPadding(double const top, double const right, double const bottom, double const left) noexcept;
			void setPaddingTop(double const top) noexcept;
			void setPaddingLeft(double const left) noexcept;
			void setPaddingBottom(double const bottom) noexcept;
			void setPaddingRight(double const right) noexcept;
			
			void setLineSpacing(double const lineSpacing) noexcept;
			
			bool receive(Event::Mouse const& event);
			bool receive(Event::Keyboard const& event);
			bool receive(Event::Focus::Type event);
			bool draw(Doodle& doodle) const;
			
			//! Get is the text is empty.
			/** The function retrieves is the text is empty.
			 @return true if the text is empty, otherwise false.
			 */
			bool isEmpty() const noexcept;
			
            //! Get the number of lines.
            /** The function retrieves the number of lines.
             @return The number of lines in the text.
             */
            ulong getNumberOfLines() const noexcept;
            
            //! Retrieves the text size.
            /** The function retrieves the text size.
             @return The text size.
             */
            inline wstring::size_type size() const noexcept
            {
                return m_text.size();
            }
			
            void setText(string const& text);
            
            static string getStringSelection(Font const& font, string const& text, double const x1, double const x2) noexcept;
            
            static Point getStringPosition(Font const& font, string const& text, double const x1, double const x2) noexcept;
            
            bool isSelectionEmpty() const noexcept;
            
            void selectAll() noexcept;
            void addPreviousCharacterToSelection() noexcept;
            void addNextCharacterToSelection() noexcept;
            void addPreviousWordToSelection() noexcept;
            void addNextWordToSelection() noexcept;
            
            void eraseSelection();
            void insertCharacter(const wchar_t c);
			//void insertCharacter(const char c);
        };
    }
    
	
	
}

#endif