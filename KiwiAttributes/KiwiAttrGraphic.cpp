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
    
    void PointValue::set(Vector const& vector)
    {
        if(vector.size() > 1 && vector[0].isNumber() && vector[1].isNumber())
        {
            x((double)vector[0]);
            y((double)vector[1]);
        }
    }
    
    Vector PointValue::get() const noexcept
    {
        return {x(), y()};
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
    
    void SizeValue::set(Vector const& vector)
    {
        if(vector.size() > 1 && vector[0].isNumber() && vector[1].isNumber())
        {
            width((double)vector[0]);
            height((double)vector[1]);
        }
    }
    
    Vector SizeValue::get() const noexcept
    {
        return {width(), height()};
    }
    
    // ================================================================================ //
    //                                      COLOR                                       //
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
    
    // ================================================================================ //
    //                                    RECTANGLE										//
    // ================================================================================ //
    
    void RectangleValue::set(Vector const& vector)
    {
        if(vector.size() > 3 && vector[0].isNumber() && vector[1].isNumber() && vector[2].isNumber() && vector[3].isNumber())
        {
            x((double)vector[0]);
            y((double)vector[1]);
            width((double)vector[2]);
            height((double)vector[3]);
        }
    }
    
    Vector RectangleValue::get() const noexcept
    {
        return {x(), y(), width(), height()};
    }
	
	// ================================================================================ //
	//                                      FONT										//
	// ================================================================================ //
	
	void FontValue::set(Vector const& vector)
	{
        int todo;
	}
	
	//! Retrieve the attribute value as a string.
    Vector FontValue::get() const noexcept
    {
        int todo;
        return {};
    }
}

