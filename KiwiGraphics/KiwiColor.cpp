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

#include "KiwiColor.h"

namespace Kiwi
{
    const string Color::m_hex_digits = string("0123456789ABCDEF");
    
    Color::Color() noexcept :
    m_red(0.), m_green(0.), m_blue(0.), m_alpha(1.)
    {
        ;
    }
    
    Color::Color(const double red, const double green, const double blue, const double alpha) noexcept :
    m_red(clip(red, 0., 1.)), m_green(clip(green, 0., 1.)), m_blue(clip(blue, 0., 1.)), m_alpha(clip(alpha, 0., 1.))
    {
        ;
    }
    
    Color::Color(Color const& other) noexcept :
    m_red(other.m_red), m_green(other.m_green), m_blue(other.m_blue), m_alpha(other.m_alpha)
    {
        ;
    }
    
    Color::~Color() noexcept
    {
        ;
    }
    
    Color Color::withHSLA(const double hue, const double saturation, const double lightness, const double alpha) noexcept
    {
        if(saturation == 0.)
        {
            return Color(lightness, lightness, lightness, alpha);
        }
        else
        {
            double var2;
            if(lightness < 0.5)
            {
                var2 = lightness * (1. + saturation);
            }
            else
            {
                var2 = (lightness + saturation) - (saturation * lightness);
            }
            const double var1 = 2. * lightness - var2;
            return Color(hueToRGB(var1, var2, hue + (1. / 3.)), hueToRGB(var1, var2, hue), hueToRGB(var1, var2, hue - (1. / 3.)),alpha);
        }

    }
    
    Color Color::withHexa(string const& color) noexcept
    {
        if(color.size() > 1 && color[0] == '#')
        {
            int hexvalue = atoi(color.c_str()+1);
            return Color(((hexvalue >> 16) & 0xFF) / 255., ((hexvalue >> 8) & 0xFF) / 255., ((hexvalue) & 0xFF) / 255., 1.);
        }
        else
        {
            return Color();
        }
    }
    
    double Color::hue() const noexcept
    {
        const double _max = max(max(red(), green()),  blue());
        if(!_max)
        {
            return 0.;
        }
        else
        {
            const double _min = min(min(red(), green()),  blue());
            const double _delta = _max - _min;
            double hue;
            if(red() == _max)
            {
                const double deltag = (((_max - green()) / 6 ) + (_delta / 2)) / _delta;
                const double deltab = (((_max - blue()) / 6 ) + (_delta / 2)) / _delta;
                hue = deltab - deltag;
            }
            else if(green() == _max)
            {
                const double deltar = (((_max - red()) / 6 ) + (_delta / 2)) / _delta;
                const double deltab = (((_max - blue()) / 6 ) + (_delta / 2)) / _delta;
                hue = (1. / 3.) + deltar - deltab;
            }
            else if(blue() == _max)
            {
                const double deltag = (((_max - green()) / 6 ) + (_delta / 2)) / _delta;
                const double deltar = (((_max - red()) / 6 ) + (_delta / 2)) / _delta;
                hue = (2. / 3.) + deltag - deltar;
            }
            
            if(hue < 0.)
            {
                return hue + 1;
            }
            else if (hue > 1.)
            {
                return hue - 1;
            }
            else
            {
                return hue;
            }
        }
    }
    
    double Color::saturation() const noexcept
    {
        const double _max = max(max(red(), green()),  blue());
        if(!_max)
        {
            return 0.;
        }
        else
        {
            const double _min = min(min(red(), green()),  blue());
            const double _light = (_max + _min) * 0.5;
            if(_light < 0.5)
            {
                return (_max - _min) / (_max + _min);
            }
            else
            {
                return (_max - _min) / (2. - _max - _min);
            }
        }
    }
    
    double Color::lightness() const noexcept
    {
        const double _max = max(max(red(), green()),  blue());
        const double _min = min(min(red(), green()),  blue());
        return (_max + _min) * 0.5;
    }
    
    string Color::hexa() const noexcept
    {
        string color("#");
        int r = red() * 255;
        int g = green() * 255;
        int b = blue() * 255;
        color += m_hex_digits[(r >> 4) & 15];
        color += m_hex_digits[r & 15];
        color += m_hex_digits[(g >> 4) & 15];
        color += m_hex_digits[g & 15];
        color += m_hex_digits[(b >> 4) & 15];
        color += m_hex_digits[b & 15];
        return color;
    }
    
    double Color::hueToRGB(double const v1, double const v2, double vH)
    {
        if(vH < 0.)
            vH += 1.;
        if(vH > 1.)
            vH -= 1.;
        if((6. * vH) < 1.)
            return (v1 + (v2 - v1) * 6. * vH);
        if((2. * vH) < 1.)
            return v2;
        if(( 3 * vH) < 2.)
            return (v1 + (v2 - v1) * ((2. / 3.) - vH) * 6.);
        return v1;
    }
    
    // ================================================================================ //
    //                                      ATTR                                        //
    // ================================================================================ //
    
    void ColorValue::set(Vector const& vector)
    {
        if(vector.size() > 2 && vector[0].isNumber() && vector[1].isNumber() && vector[2].isNumber())
        {
            red((double)vector[0]);
            green((double)vector[1]);
            blue((double)vector[2]);
            if(vector.size() > 3 && vector[3].isNumber())
            {
                alpha((double)vector[3]);
            }
        }
    }
    
    Vector ColorValue::get() const noexcept
    {
        return {red(), green(), blue(), alpha()};
    }
}