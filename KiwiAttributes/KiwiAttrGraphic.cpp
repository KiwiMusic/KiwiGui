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

#include "KiwiAttrGraphic.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      POSITION                                    //
    // ================================================================================ //
    
    void PointValue::setValue(string const& text) noexcept
    {
        string::size_type pos = text.find_first_of("-0123456789.");
        if(pos != string::npos)
        {
            x(stod(text.c_str()+pos));
            pos = text.find(' ', pos);
            pos = text.find_first_of("-0123456789.", pos);
            if(pos != string::npos)
            {
                y(stod(text.c_str()+pos));
            }
        }
    }
    
    void PointValue::getValue(string& text) const noexcept
    {
        text = "[" + toString(x()) + ", " + toString(y()) + "]";
    }
    
    // ================================================================================ //
    //                                      SIZE                                        //
    // ================================================================================ //
    
    SizeValue::SizeValue() noexcept :
    m_ratio(0.),
    m_min(0., 0.),
    m_point(0., 0.)
    {
        ;
    }
    
    SizeValue::SizeValue(const double width, const double height, const double min_width, const double min_height, const double ratio) noexcept :
    m_ratio(max(ratio, 0.)),
    m_min(max(min_width, 0.), max(min_height, 0.)),
    m_point(max(width, m_min.x()), max(height, m_min.y()))
    {
        if(m_ratio)
        {
            m_point.y(m_point.x() * m_ratio);
        }
    }
    
    SizeValue::SizeValue(SizeValue const& size) noexcept :
    m_ratio(size.m_ratio),
    m_min(size.m_min),
    m_point(size.m_point)
    {
        ;
    }
    
    SizeValue::~SizeValue()
    {
        ;
    }
    
    void SizeValue::setValue(string const& text) noexcept
    {
        string::size_type pos = text.find_first_of("-0123456789.");
        if(pos != string::npos)
        {
            width(stod(text.c_str()+pos));
            pos = text.find(' ', pos);
            pos = text.find_first_of("-0123456789.", pos);
            if(pos != string::npos)
            {
                height(stod(text.c_str()+pos));
            }
        }
    }
    
    void SizeValue::getValue(string& text) const noexcept
    {
        text = "[" + toString(width()) + ", " + toString(height()) + "]";
    }
    
    // ================================================================================ //
    //                                      COLOR                                       //
    // ================================================================================ //
    
    void ColorValue::setValue(string const& text) noexcept
    {
        double point[4] = {0., 0., 0., 0.};
        string::size_type pos;
        for(ulong i = 0; i < 4; i++)
        {
            pos = text.find_first_of("-0123456789.");
            if(pos != string::npos)
            {
                point[i] = stod(text.c_str()+pos);
                pos = text.find(' ', pos);
            }
        }
        red(point[0]);
        green(point[1]);
        blue(point[2]);
        alpha(point[3]);
    }
    
    void ColorValue::getValue(string& text) const noexcept
    {
        text = "[" + toString(red()) + ", " + toString(green()) + ", " + toString(blue()) + ", " + toString(alpha()) + "]";
    }
    
    // ================================================================================ //
    //                                    RECTANGLE										//
    // ================================================================================ //
    
    void RectangleValue::setValue(string const& text) noexcept
    {
        double point[4] = {0., 0., 0., 0.};
        string::size_type pos;
        for(ulong i = 0; i < 4; i++)
        {
            pos = text.find_first_of("-0123456789.");
            if(pos != string::npos)
            {
                point[i] = stod(text.c_str()+pos);
                pos = text.find(' ', pos);
            }
        }
        x(point[0]);
        y(point[1]);
        width(point[2]);
        height(point[3]);
    }
    
    void RectangleValue::getValue(string& text) const noexcept
    {
        text = "[" + toString(x()) + ", " + toString(y()) + ", " + toString(width()) + ", " + toString(height()) + "]";
    }
	
	// ================================================================================ //
	//                                      FONT										//
	// ================================================================================ //
	
	//! Set the attribute value with a string.
	/** The function sets the attribute value with a string.
	 @param text The value in the string format.
	 */
	void FontValue::setValue(string const& text) noexcept
	{
		;
	}
	
	//! Retrieve the attribute value as a string.
	/** The function retrieves the attribute value as a string.
	 @param text The value in the string format.
	 */
	void FontValue::getValue(string& text) const noexcept
	{
		text = "[\"" + getName() + "\", " + toString(getSize()) + ", \"" + getStyleName(getStyle()) + "\"]";
	}
}

