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

#include "KiwiColor.h"

namespace Kiwi
{
    class GuiDeviceManager;
    
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
        enum Style : unsigned
        {
            Plain               = 0,    ///< Plain version of the font
            Bold                = 1,    ///< Bold version the font.
            Italic              = 2,    ///< Italic version of the font.
            BoldItalic          = 3,    ///< Bold/Italic version the font.
            Underlined          = 4,    ///< Underlined version the font.
            BoldUnderlined      = 5,    ///< Bold/Underlined version the font.
            ItalicUnderlined    = 6,    ///< Italic/Underlined version of the font.
            BoldItalicUnderlined= 7     ///< Bold/Italic/Underlined version the font.
        };
        
    private:
        friend class GuiDeviceManager;
        class Intern;
        
        static vector<Font> m_fonts;
        
        string          m_name;
        double			m_size;
        unsigned        m_style;
        
        inline static void setAvailableFonts(vector<Font> const& fonts) noexcept
        {
             m_fonts = fonts;
        }
        
        inline static void setAvailableFonts(vector<Font>&& fonts) noexcept
        {
            m_fonts.swap(fonts);
        }
        
    public:
        
        //! Retrieves the available font names in the system.
        /** The function the available font names in the system.
         @return The available font names .
         */
        static vector<string> getAvailableNames() noexcept;
        
        //! Retrieves the available font families in the system.
        /** The function the available font families in the system.
         @return The available font families.
         */
        static vector<string> getAvailableFamilies() noexcept;
        
    public:
        
        //! Font constructor.
        /** Initializes a default Arial font with a normal plain style and a font size of 12.
         */
        inline Font() noexcept : m_name("Helvetica"), m_size(12.), m_style(Plain) {}
        
        //! Font constructor.
        /** Initializes a font with a name, size and style.
         @param name The name of the font.
         @param size The size of the font.
         @param face The face of the font.
		 */
        inline Font(string const& name, double size = 12, Style face = Plain) noexcept : m_name(name), m_size(clip(size, 0.1, 10000.)), m_style(face) {}
        
        //! Font constructor.
        /** Initializes a with another font.
         @param font The other font.
         */
        inline Font(Font const& font) : m_name(font.m_name), m_size(font.m_size), m_style(font.m_style) {}
        
        //! Font constructor.
        /** Initializes a with another font.
         @param font The other font.
         */
        inline Font(Font&& font) : m_name(), m_size(font.m_size), m_style(font.m_style)
        {
            swap(m_name, font.m_name);
        }
        
        //! Font equal oeprator.
        /** Initializes the font with another font.
         @param font The other font.
         */
        inline Font& operator=(Font const& font) noexcept
        {
            m_name  = font.m_name;
            m_size  = font.m_size;
            m_style = font.m_style;
            return *this;
        }
        
        //! Font equal oeprator.
        /** Initializes the font with another font.
         @param font The other font.
         */
        inline Font& operator=(Font&& font) noexcept
        {
            swap(m_name, font.m_name);
            m_size  = font.m_size;
            m_style = font.m_style;
            return *this;
        }
        
        //! Destructor.
        /** The function does nothing.
         */
        inline ~Font() {}
        
        //! Retrieves the font name.
        /** The function retrieves the name of the font.
         @return The name of the font.
         */
        inline string getName() const noexcept
        {
            return m_name;
        }
        
        //! Retrieves the font height.
        /** The function retrieves the height of the font.
         @return The height of the font.
         */
        inline double getHeight() const noexcept
        {
            return m_size;
        }
        
        //! Retrieves the font style.
        /** The function retrieves the style of the font.
         @return The style of the font.
         */
        inline unsigned getStyle() const noexcept
        {
            return m_style;
        }
        
        //! Retrieves a font name as a string.
        /** The function retrieves a font name as a string.
         @return A font name as a string.
         */
        inline string getStyleName() const noexcept
        {
            int todo;
            return "Regular";
        }
        
        //! Retrieve if the font is boldened.
        /** The function retrieves if a font is boldened.
         @return True if boldened, false otherwise.
         */
        bool isBold() const noexcept
        {
            return m_style & Bold;
        }
        
        //! Retrieve if the font is italicised.
        /** The function retrieves if a font is italicised.
         @return True if italicised, false otherwise.
         */
        bool isItalic() const noexcept
        {
            return m_style & Italic;
        }
        
        //! Retrieve if the font is underlined.
        /** The function retrieves if a font is underlined.
         @return True if underlined, false otherwise.
         */
        bool isUnderlined() const noexcept
        {
            return m_style & Underlined;
        }
        
        //! Sets the font name.
        /** The function sets the name of the font.
         @param size The size of the name.
         */
        inline void setName(const string& name)
        {
            m_name = name;
        }
		
        //! Sets the font height.
        /** The function sets the height of the font.
         @param size The height of the font.
         */
        inline void setHeight(const double size)
        {
            m_size = clip(size, 0.1, 10000.);
        }
        
        //! Sets the font style.
        /** The function sets the style of the font.
         @param style The style of the font as a set flags.
         */
        inline void setStyle(Style style)
        {
            m_style = style;
        }
        
        //! Sets the font style.
        /** The function sets the style of the font.
         @param styleFlags The style of the font as a set flags.
         */
        inline void setStyle(string const& style)
        {
            int todo;
        }
        
        //! Make the font bold or non-bold
        /** The function makes the font bold or non-bold
         @param shouldBeBold True if bold, false otherwise.
         */
        inline void setBold(const bool shouldBeBold) noexcept
        {
            if(shouldBeBold && !(m_style & Font::Bold))
                m_style |= Font::Bold;
            else if(!shouldBeBold && (m_style & Font::Bold))
                m_style &= Font::Bold;
        }
        
        //! Make the font italic or non-italic
        /** The function makes the font italic or non-italic
         @param shouldBeItalic True if italic, false otherwise.
         */
        inline void setItalic(const bool shouldBeItalic) noexcept
        {
            if(shouldBeItalic && !(m_style & Font::Italic))
                m_style |= Font::Italic;
            else if(!shouldBeItalic && (m_style & Font::Italic))
                m_style &= Font::Italic;
        }
        
        //! Make the font undelined or non-undelined
        /** The function makes the font undelined or non-undelined
         @param shouldBeUnderlined True if undelined, false otherwise.
         */
        inline void setUnderline(const bool shouldBeUnderlined) noexcept
        {
            if(shouldBeUnderlined && !(m_style & Font::Underlined))
                m_style |= Font::Underlined;
            else if(!shouldBeUnderlined && (m_style & Font::Underlined))
                m_style &= Font::Underlined;
        }
        
        //! Compare the font with another.
        /** The function compare the font with another.
         @param other The other font.
         @return true is the fonts are not similar, otherwise false.
         */
        inline bool operator!=(Font const& other) const noexcept
        {
            return getName() != other.getName() || getStyle() != other.getStyle() ||  getHeight() != other.getHeight();
        }
        
        //! Compare the font with another.
        /** The function compare the font with another.
         @param other The other font.
         @return true is the fonts are similar, otherwise false.
         */
        inline bool operator==(Font const& other) const noexcept
        {
            return getName() == other.getName() && getStyle() == other.getStyle() && getHeight() == other.getHeight();
        }
        
        //! Retrieves the width of a character.
        /** The function retreives the width of a character for the font.
         @param c The character.
         @return The width of the character.
         */
        double getCharacterWidth(char const& c) const noexcept;
        
        //! Retrieves the width of a character.
        /** The function retreives the width of a character for the font.
         @param c The character.
         @return The width of the character.
         */
        double getCharacterWidth(wchar_t const& c) const noexcept;
        
        //! Retrieves the width of a line.
        /** The function retreives the width of a line for the font.
         @param line The line.
         @return The width of the line.
         */
        double getLineWidth(string const& line) const noexcept;
        
        //! Retrieves the width of a line.
        /** The function retreives the width of a line for the font.
         @param line The line.
         @return The width of the line.
         */
        double getLineWidth(wstring const& line) const noexcept;
        
        //! Retrieves the size of a text.
        /** The function the size of a text depending for the font.
         @param text The text.
         @param width The width limit of the text, zero means no limits.
         @return The width of the text.
         */
        Size getTextSize(string const& text, const double width = 0.) const noexcept;
        
        //! Retrieves the size of a text.
        /** The function the width of a text depending for the font.
         @param text The text.
         @param width The width limit of the text, zero means no limits.
         @return The width of the text.
         */
        Size getTextSize(wstring const& text, const double width = 0.) const noexcept;
        
        //! Retrieve the font as a vector of atoms.
        /** The function retrieves the font as a vector of atoms.
         @return The vector of atoms.
         */
        inline Vector get() const noexcept
        {
            return Vector({m_name, m_size, getStyleName()});
        }
        
        //! Set the font with a vector of atoms.
        /** The function sets the font with a vector of atoms.
         @param vector The vector of atoms.
         */
        inline void set(Vector const& vector) noexcept
        {
            if(!vector.empty() && vector[0].isTag())
            {
                setName(sTag(vector[0])->getName());
                if(vector.size() > 1 && vector[1].isNumber())
                {
                    setHeight(double(vector[1]));
                }
                if(vector.size() > 2 && vector[2].isTag())
                {
                    setStyle(sTag(vector[2])->getName());
                }
            }
        }
    };
    
    class Font::Intern
    {
    private:
        
    public:
        
    };
}

#endif
