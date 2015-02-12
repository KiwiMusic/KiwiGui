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

#include "Graphic.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      POSITION                                    //
    // ================================================================================ //
    
    void PointAttr::setValue(string const& text) noexcept
    {
        double point[2] = {0., 0.};
        string::size_type pos;
        for(ulong i = 0; i < 2; i++)
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
    }
    
    void PointAttr::getValue(string& text) const noexcept
    {
        text = "[" + toString(x()) + ", " + toString(y()) + "]";
    }
    
    // ================================================================================ //
    //                                      SIZE                                        //
    // ================================================================================ //
    
    SizeAttr::SizeAttr() noexcept :
    m_ratio(0.),
    m_min(0., 0.),
    m_point(0., 0.)
    {
        ;
    }
    
    SizeAttr::SizeAttr(const double width, const double height, const double ratio, const double min_width, const double min_height) noexcept :
    m_ratio(max(ratio, 0.)),
    m_min(max(min_width, 0.), max(min_height, 0.)),
    m_point(max(width, m_min.x()), m_ratio ? m_min.x() * m_ratio : max(height, m_min.y()))
    {
        
    }
    
    SizeAttr::SizeAttr(SizeAttr const& size) noexcept :
    m_ratio(size.m_ratio),
    m_min(size.m_min),
    m_point(size.m_point)
    {
        ;
    }
    
    SizeAttr::SizeAttr(Point const& pt) noexcept :
    m_ratio(0.),
    m_min(0., 0.),
    m_point(pt)
    {
        ;
    }
    
    SizeAttr::~SizeAttr()
    {
        ;
    }
    
    void SizeAttr::setValue(string const& text) noexcept
    {
        double point[2] = {0., 0.};
        string::size_type pos;
        for(ulong i = 0; i < 2; i++)
        {
            pos = text.find_first_of("-0123456789.");
            if(pos != string::npos)
            {
                point[i] = stod(text.c_str()+pos);
                pos = text.find(' ', pos);
            }
        }
        width(point[0]);
        height(point[1]);
    }
    
    void SizeAttr::getValue(string& text) const noexcept
    {
        text = "[" + toString(width()) + ", " + toString(height()) + "]";
    }
    
    // ================================================================================ //
    //                                      COLOR                                       //
    // ================================================================================ //
    
    void ColorAttr::setValue(string const& text) noexcept
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
    
    void ColorAttr::getValue(string& text) const noexcept
    {
        text = "[" + toString(red()) + ", " + toString(green()) + ", " + toString(blue()) + ", " + toString(alpha()) + "]";
    }
}

