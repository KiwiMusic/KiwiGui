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
            Regular             = 0,    ///< Regular version of the font
            Bold                = 1,    ///< Bold version the font.
            Italic              = 2,    ///< Italic version of the font.
            BoldItalic          = 3,    ///< Bold/Italic version the font.
            Underlined          = 4,    ///< Underlined version the font.
            BoldUnderlined      = 5,    ///< Bold/Underlined version the font.
            ItalicUnderlined    = 6,    ///< Italic/Underlined version of the font.
            BoldItalicUnderlined= 7     ///< Bold/Italic/Underlined version the font.
        };
        
        /** The internal font
         */
        class Intern
        {
        private:
            const string    m_name;
            double          m_height;
            unsigned        m_style;
        public:
            
            //! Font constructor.
            /** Initializes a intern font with a name, size and style.
             @param name    The name of the font.
             @param height  The height of the font.
             @param style   The style of the font.
             */
            inline Intern(string const& name, double height, Style style) noexcept : m_name(name), m_height(height), m_style(style) {}
            
            //! Destructor.
            /** The function does nothing.
             */
            virtual inline ~Intern() noexcept {};
            
            //! Retrieves if the font is available in the system.
            /** The function retrieves if the font is available in the system.
             @return true if the font is available otherwise false.
             */
            virtual inline bool isValid() const noexcept
            {
                return false;
            }
            
            //! Retrieves the font name.
            /** The function retrieves the name of the font.
             @return The name of the font.
             */
            virtual inline shared_ptr<Intern> getNewReference() const noexcept
            {
                return make_shared<Intern>(getName(), getHeight(), getStyle());
            }
            
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
                return m_height;
            }
            
            //! Retrieves the font style.
            /** The function retrieves the style of the font.
             @return true if the font is valid, otherwise false.
             */
            inline unsigned getStyle() const noexcept
            {
                return m_style;
            }
            
            //! Sets the font height.
            /** The function sets the height of the font.
             @param size The height of the font.
             */
            virtual inline void setHeight(const double size)
            {
                m_height = clip(size, 0.1, 10000.);
            }
            
            //! Sets the font style.
            /** The function sets the style of the font.
             @param style The style of the font as a set flags.
             */
            virtual inline void setStyle(const Style style)
            {
                m_style = style;
            }
            
            //! Retrieves the width of a character.
            /** The function retreives the width of a character for the font.
             @param c The character.
             @return The width of the character.
             */
            virtual double getCharacterWidth(char const& c) const noexcept;
            
            //! Retrieves the width of a character.
            /** The function retreives the width of a character for the font.
             @param c The character.
             @return The width of the character.
             */
            virtual double getCharacterWidth(wchar_t const& c) const noexcept;
            
            //! Retrieves the width of a line.
            /** The function retreives the width of a line for the font.
             @param line The line.
             @return The width of the line.
             */
            virtual double getLineWidth(string const& line) const noexcept;
            
            //! Retrieves the width of a line.
            /** The function retreives the width of a line for the font.
             @param line The line.
             @return The width of the line.
             */
            virtual double getLineWidth(wstring const& line) const noexcept;
            
            //! Retrieves the size of a text.
            /** The function the size of a text depending for the font.
             @param text The text.
             @param width The width limit of the text, zero means no limits.
             @return The width of the text.
             */
            virtual Size getTextSize(string const& text, const double width = 0.) const noexcept;
            
            //! Retrieves the size of a text.
            /** The function the width of a text depending for the font.
             @param text The text.
             @param width The width limit of the text, zero means no limits.
             @return The width of the text.
             */
            virtual Size getTextSize(wstring const& text, const double width = 0.) const noexcept;
            
        };
        typedef shared_ptr<Intern>  sIntern;
        typedef weak_ptr<Intern>    wIntern;
        
    private:
        friend class GuiDeviceManager;
        static vector<Font> m_fonts;
        
        sIntern         m_intern;
        
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
        static vector<string> getAvailableFamilies() noexcept;
        
    public:
        
        //! Font constructor.
        /** Initializes a default Arial font with a normal plain style and a font size of 12.
         */
        inline Font() noexcept {}
        
        //! Font constructor.
        /** Initializes a font with a name, size and style.
         @param name The name of the font.
         @param size The size of the font.
         @param face The face of the font.
		 */
        inline Font(string const& name, double height = 12., Style style = Regular) noexcept {}
        
        //! Font constructor.
        /** Initializes a with another font.
         @param font The other font.
         */
        inline Font(Font const& font) {}
        
        //! Font constructor.
        /** Initializes a with another font.
         @param font The other font.
         */
        inline Font(Font&& font) : m_intern(move(font.m_intern)) {font.m_intern = sIntern();}
        
        //! Font equal oeprator.
        /** Initializes the font with another font.
         @param other The other font.
         */
        inline Font& operator=(Font const& other) noexcept
        {
            m_intern = other.m_intern->getNewReference();
            return *this;
        }
        
        //! Font equal oeprator.
        /** Initializes the font with another font.
         @param other The other font.
         */
        inline Font& operator=(Font&& other) noexcept
        {
            m_intern = move(other.m_intern);
            other.m_intern = sIntern();
            return *this;
        }
        
        //! Destructor.
        /** The function does nothing.
         */
        inline ~Font() noexcept {}
        
        //! Retrieves if the font is available.
        /** The function retrieves if the font is available.
         @return true if the font is available, otherwise false.
         */
        inline bool isValid() const noexcept
        {
            return m_intern->isValid();
        }
        
        //! Retrieves the font name.
        /** The function retrieves the name of the font.
         @return The name of the font.
         */
        inline string getName() const noexcept
        {
            return m_intern->getName();
        }
        
        //! Retrieves the font height.
        /** The function retrieves the height of the font.
         @return The height of the font.
         */
        inline double getHeight() const noexcept
        {
            return m_intern->getHeight();
        }
        
        //! Retrieves the font style.
        /** The function retrieves the style of the font.
         @return The style of the font.
         */
        inline unsigned getStyle() const noexcept
        {
            return m_intern->getStyle();
        }
        
        //! Retrieves a font name as a string.
        /** The function retrieves a font name as a string.
         @return A font name as a string.
         */
        inline string getStyleName() const noexcept
        {
            switch(getStyle())
            {
                case Regular:
                    return string("Regular");
                    break;
                case Bold:
                    return string("Bold");
                    break;
                case Italic:
                    return string("Italic");
                    break;
                case Underlined:
                    return string("Underlined");
                    break;
                case BoldItalic:
                    return string("Bold Italic");
                    break;
                case BoldUnderlined:
                    return string("Bold Underlined");
                    break;
                case ItalicUnderlined:
                    return string("Italic Underlined");
                    break;
                default:
                    return string("Bold Italic Underlined");
                    break;
            }
        }
        
        //! Retrieve if the font is boldened.
        /** The function retrieves if a font is boldened.
         @return True if boldened, false otherwise.
         */
        bool isBold() const noexcept
        {
            return getStyle() & Bold;
        }
        
        //! Retrieve if the font is italicised.
        /** The function retrieves if a font is italicised.
         @return True if italicised, false otherwise.
         */
        bool isItalic() const noexcept
        {
            return getStyle() & Italic;
        }
        
        //! Retrieve if the font is underlined.
        /** The function retrieves if a font is underlined.
         @return True if underlined, false otherwise.
         */
        bool isUnderlined() const noexcept
        {
            return getStyle() & Underlined;
        }
        
        //! Sets the font name.
        /** The function sets the name of the font.
         @param size The size of the name.
         */
        inline void setName(const string& name)
        {
            ;
        }
		
        //! Sets the font height.
        /** The function sets the height of the font.
         @param height The height of the font.
         */
        inline void setHeight(const double height)
        {
            if(height != getHeight())
            {
                m_intern->setHeight(height);
            }
        }
        
        //! Sets the font style.
        /** The function sets the style of the font.
         @param style The style of the font as a set flags.
         */
        inline void setStyle(const Style style)
        {
            if(style != getStyle())
            {
                m_intern->setStyle(style);
            }
        }
        
        //! Sets the font style.
        /** The function sets the style of the font.
         @param styleFlags The style of the font as a set flags.
         */
        inline void setStyle(string const& style)
        {
            if(style == string("Regular"))
            {
                setStyle(Regular);
            }
            else if(style == string("Bold"))
            {
                setStyle(Bold);
            }
            else if(style == string("Italic"))
            {
                setStyle(Italic);
            }
            else if(style == string("Underlined"))
            {
                setStyle(Underlined);
            }
            else if(style == string("Bold Italic"))
            {
                setStyle(BoldItalic);
            }
            else if(style == string("Bold Underlined"))
            {
                setStyle(BoldUnderlined);
            }
            else if(style == string("Italic Underlined"))
            {
                setStyle(ItalicUnderlined);
            }
            else if(style == string("Bold Italic Underlined"))
            {
                setStyle(BoldItalicUnderlined);
            }
        }
        
        //! Make the font bold or non-bold
        /** The function makes the font bold or non-bold
         @param shouldBeBold True if bold, false otherwise.
         */
        inline void setBold(const bool shouldBeBold) noexcept
        {
            unsigned style = getStyle();
            shouldBeBold ? style |= Font::Bold : style &= Font::Bold;
            setStyle(Style(style));
        }
        
        //! Make the font italic or non-italic
        /** The function makes the font italic or non-italic
         @param shouldBeItalic True if italic, false otherwise.
         */
        inline void setItalic(const bool shouldBeItalic) noexcept
        {
            unsigned style = getStyle();
            shouldBeItalic ? style |= Font::Italic : style &= Font::Italic;
            setStyle(Style(style));
        }
        
        //! Make the font undelined or non-undelined
        /** The function makes the font undelined or non-undelined
         @param shouldBeUnderlined True if undelined, false otherwise.
         */
        inline void setUnderline(const bool shouldBeUnderlined) noexcept
        {
            unsigned style = getStyle();
            shouldBeUnderlined ? style |= Font::Underlined : style &= Font::Underlined;
            setStyle(Style(style));
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
            return Vector({getName(), getHeight(), getStyleName()});
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
}

#endif
