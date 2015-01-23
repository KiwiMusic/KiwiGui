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

#ifndef __DEF_KIWI_GUI_FONT__
#define __DEF_KIWI_GUI_FONT__

#include "Defs.h"
#include "Point.h"

namespace Kiwi
{
    namespace Gui
    {
        // ================================================================================ //
        //                                      FONT                                        //
        // ================================================================================ //
		
        class Font
        {
        public:
			/** Flags describing the type of font justification
			 @see Face
			 */
            enum Justification
            {
                Left                    = 1,
                Right                   = 2,
                HorizontallyCentered    = 4,
                Top                     = 8,
                TopLeft                 = 9,
                TopRight                = 10,
                CentredTop              = 12,
                Bottom                  = 16,
                BottomLeft              = 17,
                BottomRight             = 18,
                CentredBottom           = 20,
                VerticallyCentred       = 32,
                CentredLeft             = 33,
                CentredRight            = 34,
                Centred                 = 36,
                HorizontallyJustified   = 64,
            };
			
			/** Flags describing the style of font
			 @see Face
			 */
            enum Style
            {
				Plain       = 0,    ///< indicates a plain, non-bold, non-italic version of the font
				Bold        = 1,    ///< boldens the font.
				Italic      = 2,    ///< An italic version of the font.
				Underlined  = 4     ///< underlines the font.
            };
			
		private:
			string          m_name;
			double			m_size;
			ulong           m_style;
		
		public:
			//! Font constructor.
			/** Initializes a default Arial font with a \Normal facetype and a font size of 12.
			 */
            Font() noexcept :
            m_name("Arial"), m_size(12.), m_style(Plain)
            {
				;
            }
			
			//! Font constructor.
			/** Initializes a default Arial font with a \Normal facetype and a font size of 12.
			 */
            Font(string const& name, double size, ulong face = Plain) noexcept :
            m_name(name), m_style(face)
            {
				setSize(size);
            }
			
			//! Destructor.
			~Font()
			{
				;
			}
			
			//! Sets the font name.
			/** The function sets the name of the font.
			 @param size The size of the name.
			 */
			inline void setName(const string& name)
			{
				m_name = name;
			}
			
			//! Retrieves the font name.
			/** The function retrieves the name of the font.
			 @return The name of the font.
			 */
			inline string getName() const noexcept
			{
				return m_name;
			}
			
			//! Sets the font size.
			/** The function sets the size of the font.
			 @param size The size of the font.
			 */
			inline void setSize(const double size)
			{
				m_size = clip(size, 0.1, 10000.);
			}
			
			//! Retrieves the font size.
			/** The function retrieves the size of the font.
			 @return The size of the font.
			 */
			inline double getSize() const noexcept
			{
				return m_size;
			}
			
			//! Sets the font style.
			/** The function sets the style of the font.
			 @param styleFlags The style of the font as a set flags.
			 */
			inline void setStyle(ulong styleFlags)
			{
				m_style = styleFlags;
			}
			
			//! Retrieves the font style.
			/** The function retrieves the style of the font.
			 @return The style of the font.
			 */
			inline ulong getStyle() const noexcept
			{
				int flags = (m_style & Font::Underlined) ? Underlined : Plain;
				
				if (isBold())    flags |= bold;
				if (isItalic())  flags |= italic;
				
				return flags;
			}
			
			//! Retrieves a font name as a string.
			/** The function retrieves a font name as a string.
			 @return A font name as a string.
			 */
			static string getStyleName(ulong styleFlags) noexcept
			{
				const bool bold = (styleFlags & Font::Bold);
				const bool italic = (styleFlags & Font::Italic);
				
				if (bold && italic) return "Bold Italic";
				if (bold)           return "Bold";
				if (italic)         return "Italic";
				return "Regular";
			}
			
			//! Retrieves if the font is boldened.
			/** The function retrieves if a font is boldened.
			 @return True if boldened, false otherwise.
			 */
			bool isBold() const noexcept
			{
				return m_style & Bold;
			}
			
			//! Retrieves if the font is italicised.
			/** The function retrieves if a font is italicised.
			 @return True if italicised, false otherwise.
			 */
			bool isItalic() const noexcept
			{
				return m_style & Italic;
			}
			
			//! Retrieves if the font is underlined.
			/** The function retrieves if a font is underlined.
			 @return True if underlined, false otherwise.
			 */
			bool isUnderlined() const noexcept
			{
				return m_style & Underlined;
			}
			
			//! Make the font bold or non-bold
			/** The function make the font bold or non-bold
			 @param shouldBeBold True if bold, false otherwise.
			 */
			void setBold(const bool shouldBeBold)
			{
				const ulong flags = getStyle();
				setStyle(shouldBeBold ? (flags | Bold) : (flags & ~Bold));
			}
			
			//! Make the font italic or non-italic
			/** The function make the font italic or non-italic
			 @param shouldBeItalic True if italic, false otherwise.
			 */
			void setItalic(const bool shouldBeItalic)
			{
				const ulong flags = getStyle();
				setStyle(shouldBeItalic ? (flags | Italic) : (flags & ~Italic));
			}
			
			//! Make the font undelined or non-undelined
			/** The function make the font undelined or non-undelined
			 @param shouldBeUnderlined True if undelined, false otherwise.
			 */
			void setUnderline(const bool shouldBeUnderlined)
			{
				const ulong flags = getStyle();
				setStyle(shouldBeUnderlined ? (flags | Underlined) : (flags & ~Underlined));
			}
			
			//! Get the display size of a string.
			/** The function retrieves the display size of a string.
			 @return The display size of a string.
			 */
            static Point getStringSize(Font const& font, string const& text) noexcept;
			
			//! Get the display size of a string.
			/** The function retrieves the display size of a string.
			 @return The display size of a string.
			 */
            static Point getStringSize(Font const& font, wstring const& text) noexcept;
			
			//! Get the display height of a fixed width text.
			/** The function retrieves the display height of a fixed width text
			 @return The display height of a fixed width text.
			 */
			static double getStringHeight(Font const& font, string const text, const float textWidth) noexcept;
        };
    }
}

#endif
