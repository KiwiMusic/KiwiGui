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
        enum Style
        {
            Plain       = 0,    ///< indicates a plain, non-bold, non-italic version of the font
            Bold        = 1,    ///< boldens the font.
            Italic      = 2,    ///< An italic version of the font.
            Underlined  = 4     ///< underlines the font.
        };
        
    private:
        friend class GuiDeviceManager;
        static vector<Font> m_fonts;
        
        string          m_name;
        double			m_size;
        ulong           m_style;
        
        inline static void setAvailableFonts(vector<Font> const& fonts) noexcept
        {
             m_fonts = fonts;
        }
        
        inline static void setAvailableFonts(vector<Font>&& fonts) noexcept
        {
            m_fonts.swap(fonts);
        }
        
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
        inline Font(string const& name, double size = 12, ulong face = Plain) noexcept : m_name(name), m_size(clip(size, 0.1, 10000.)), m_style(face) {}
        
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
        inline Font withName(const string& name) const noexcept
        {
            return Font(name, m_size, m_style);
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
            ulong flags = (m_style & Font::Underlined) ? Underlined : Plain;
			if(isBold())
            {
                flags |= Bold;
            }
            if(isItalic())
            {
                flags |= Italic;
            }
            return flags;
        }
        
        //! Retrieves a font name as a string.
        /** The function retrieves a font name as a string.
         @return A font name as a string.
         */
        inline string getStyleName() const noexcept
        {
            return getStyleName(m_style);
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
        
        //! Make the font bold or non-bold
        /** The function makes the font bold or non-bold
         @param shouldBeBold True if bold, false otherwise.
         */
        void setBold(const bool shouldBeBold)
        {
            const ulong flags = getStyle();
            setStyle(shouldBeBold ? (flags | Bold) : (flags & ~Bold));
        }
        
        //! Make the font italic or non-italic
        /** The function makes the font italic or non-italic
         @param shouldBeItalic True if italic, false otherwise.
         */
        void setItalic(const bool shouldBeItalic)
        {
            const ulong flags = getStyle();
            setStyle(shouldBeItalic ? (flags | Italic) : (flags & ~Italic));
        }
        
        //! Make the font undelined or non-undelined
        /** The function makes the font undelined or non-undelined
         @param shouldBeUnderlined True if undelined, false otherwise.
         */
        void setUnderline(const bool shouldBeUnderlined)
        {
            const ulong flags = getStyle();
            setStyle(shouldBeUnderlined ? (flags | Underlined) : (flags & ~Underlined));
        }
        
        //! Retrieves a font name as a string.
        /** The function retrieves a font name as a string.
         @return A font name as a string.
         */
        inline static string getStyleName(const ulong styleFlags) noexcept
        {
            const bool bold = (styleFlags & Font::Bold);
            const bool italic = (styleFlags & Font::Italic);
            
            if (bold && italic) return "Bold Italic";
            else if (bold)      return "Bold";
            else if (italic)    return "Italic";
            else return "Regular";
        }
        
        //! Compare the font with another.
        /** The function compare the font with another.
         @param other The other font.
         @return true is the fonts are not similar, otherwise false.
         */
        inline bool operator!=(Font const& other) const noexcept
        {
            return getName() != other.getName() || getStyle() != other.getStyle() ||  getSize() != other.getSize();
        }
        
        //! Compare the font with another.
        /** The function compare the font with another.
         @param other The other font.
         @return true is the fonts are similar, otherwise false.
         */
        inline bool operator==(Font const& other) const noexcept
        {
            return getName() == other.getName() && getStyle() == other.getStyle() && getSize() == other.getSize();
        }
        
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
                    setSize(double(vector[1]));
                }
                if(vector.size() > 2 && vector[2].isTag())
                {
                    int todo;
                }
            }
        }
    };
}

#endif
