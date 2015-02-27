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

#ifndef __DEF_KIWI_GUI_COLOR__
#define __DEF_KIWI_GUI_COLOR__

#include "KiwiPath.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      COLOR                                       //
    // ================================================================================ //
    
    //! The color holds four double values for red, green, blue and alpha colors values.
    /**
     The rectangle is used to represent a color in the rgba format then, you should use the hsla methods with parsimony.
     */
    class Color
    {
    private:
        double m_red;
        double m_green;
        double m_blue;
        double m_alpha;
        static const string m_hex_digits;
        static double hueToRGB(double const v1, double const v2, double vH);
    public:
        
        //! Constructor.
        /** The function initialize a default black color.
         */
        Color() noexcept;
        
        //! Constructor.
        /** The function initialize a color with rgba values.
         @param red The red value.
         @param green The green value.
         @param blue The blue value.
         @param alpha The alpha value.
         */
        Color(const double red, const double green, const double blue, const double alpha = 1.) noexcept;
        
        //! Constructor.
        /** The function initialize a color with another.
         @param other The other color.
         */
        Color(Color const& other) noexcept;
        
        //! Destructor.
        /** The function deletes the color.
         */
        ~Color() noexcept;
        
        //! Retrieve a color with hsla values.
        /** The function retrieves the a color with hsla values.
         @param hue The hue value.
         @param saturation The saturation value.
         @param lightness The lightness value.
         @param alpha The alpha value.
         @return The color.
         */
        static Color withHSLA(const double hue, const double saturation, const double lightness, const double alpha = 0.) noexcept;
        
        //! Retrieve a color with hexadecimal.
        /** The function retrieves the a color with hexadecimal.
         @param color The color in hexadecimal.
         @return The color.
         */
        static Color withHexa(string const& color) noexcept;
        
        //! Retrieve a brighter color.
        /** The function retrieves a the brighter color.
         @param value The amount of brightness.
         @return The new color.
         */
        inline Color brighter(const double value) const noexcept
        {
            return Color(red() + value, green() + value, blue() + value, alpha());
        }
        
        //! Retrieve a darker color.
        /** The function retrieves a the darker color.
         @param value The amount of darkness.
         @return The new color.
         */
        inline Color darker(const double value) const noexcept
        {
            return Color(red() - value, green() - value, blue() - value, alpha());
        }
        
        //! Retrieve the same color with a different alpha.
        /** The function retrieves the same color with a different alpha.
         @param alpha The alpha.
         @return The new color.
         */
        inline Color withAlpha(const double value) const noexcept
        {
            return Color(red(), green(), blue(), clip(value, 0., 1.));
        }
        
        //! Retrieve a different color with the same alpha.
        /** The function retrieves a different color with the same alpha.
         @param red The red value.
         @param green The green value.
         @param blue The blue value.
         @return The new color.
         */
        inline Color withRGB(const double red, const double green, const double blue) const noexcept
        {
            return Color(red, green, blue, alpha());
        }
        
        //! Retrieve the red value.
        /** The function retrieves the red value.
         @return The red value.
         */
        inline double red() const noexcept
        {
            return m_red;
        }
        
        //! Retrieve the green value.
        /** The function retrieves the green value.
         @return The green value.
         */
        inline double green() const noexcept
        {
            return m_green;
        }
        
        //! Retrieve the blue value.
        /** The function retrieves the blue value.
         @return The blue value.
         */
        inline double blue() const noexcept
        {
            return m_blue;
        }
        
        //! Retrieve the alpha value.
        /** The function retrieves the alpha value.
         @return The alpha value.
         */
        inline double alpha() const noexcept
        {
            return m_alpha;
        }
        
        //! Retrieve the hue value.
        /** The function retrieves the hue value. Please use this method with parsimony.
         @return The hue value.
         */
        double hue() const noexcept;
        
        //! Retrieve the saturation value.
        /** The function retrieves the saturation value. Please use this method with parsimony.
         @return The saturation value.
         */
        double saturation() const noexcept;
        
        //! Retrieve the lightness value.
        /** The function retrieves the lightness value. Please use this method with parsimony.
         @return The lightness value.
         */
        double lightness() const noexcept;
        
        //! Retrieve the hexadecimal value.
        /** The function retrieves the hexadecimal value.
         @return The hexadecimal value.
         */
        string hexa() const noexcept;
        
        //! Set the red value.
        /** The function set the red value.
         @param value The red value.
         */
        inline void red(const double value) noexcept
        {
            m_red = clip(value, 0., 1.);
        }
        
        //! Set the green value.
        /** The function set the green value.
         @param value The green value.
         */
        inline void green(const double value) noexcept
        {
            m_green = clip(value, 0., 1.);
        }
        
        //! Set the blue value.
        /** The function set the blue value.
         @param value The blue value.
         */
        inline void blue(const double value) noexcept
        {
            m_blue = clip(value, 0., 1.);
        }
        
        //! Set the alpha value.
        /** The function set the alpha value.
         @param value The alpha value.
         */
        inline void alpha(const double value) noexcept
        {
            m_alpha = clip(value, 0., 1.);
        }
        
        //! Set the hue value.
        /** The function set the hue value. Please use this method with parsimony.
         @param value The hue value.
         */
        inline void hue(const double value) noexcept
        {
            *this = withHSLA(value, saturation(), lightness(), m_alpha);
        }
    
        //! Set the saturation value.
        /** The function set the saturation value. Please use this method with parsimony.
         @param value The saturation value.
         */
        inline void saturation(const double value) noexcept
        {
           *this = withHSLA(hue(), value, lightness(), m_alpha);
        }
        
        //! Set the lightness value.
        /** The function set the lightness value. Please use this method with parsimony.
         @param value The lightness value.
         */
        inline void lightness(const double value) noexcept
        {
            *this = withHSLA(hue(), saturation(), value, m_alpha);
        }
        
        //! Set the color with another.
        /** The function sets the color with another.
         @param other The other color.
         */
        inline Color& operator=(Color const& other) noexcept
        {
            m_red = other.m_red;
            m_green = other.m_green;
            m_blue = other.m_blue;
            m_alpha = other.m_alpha;
            return *this;
        }
        
        //! Compare the color with another.
        /** The function compare the color with another.
         @param other The other color.
         @return true is the colors are not equals, otherwise false.
         */
        inline bool operator!=(Color const& other) noexcept
        {
            return m_red != other.m_red || m_green != other.m_green ||  m_blue != other.m_blue ||  m_alpha != other.m_alpha;
        }
        
        //! Compare the color with another.
        /** The function compare the color with another.
         @param other The other color.
         @return true is the colors are equals, otherwise false.
         */
        inline bool operator==(Color const& other) noexcept
        {
            return m_red == other.m_red && m_green == other.m_green && m_blue == other.m_blue && m_alpha == other.m_alpha;
        }
    };
}

#endif