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

#ifndef __DEF_KIWI_GUI_GEOMETRY__
#define __DEF_KIWI_GUI_GEOMETRY__

#include "Attribute.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      POSITION                                    //
    // ================================================================================ //
    
    class PointAttr : public Point, public Attr::Value
    {
    public:
        using Point::Point;
        
        PointAttr()
        {
            ;
        }
        
        PointAttr(Point const& point) noexcept : Point(point)
        {
            ;
        }
        
        //! Set the attribute value with a string.
        /** The function sets the attribute value with a string.
         @param text The value in the string format.
         */
        void setValue(string const& text) noexcept override;
        
        //! Retrieve the attribute value as a string.
        /** The function retrieves the attribute value as a string.
         @param text The value in the string format.
         */
        void getValue(string& text) const noexcept override;
    };
    
    // ================================================================================ //
    //                                      SIZE                                        //
    // ================================================================================ //
    
    //! The size holds is an unsigned point with a ratio.
    /**
     The size holds is an unsigned point with a ratio that defines
     */
    class SizeAttr : public Attr::Value
    {
        double m_ratio;
        Point  m_min;
        Point  m_point;
    public:
        
        //! Constructor.
        /** The function initializes a size null.
         */
        SizeAttr() noexcept;
        
        //! Constructor.
        /** The function initializes a point with two double values.
         @param width The width.
         @param height The height.
         @param ratio The ratio between the width and the height.
         */
        SizeAttr(const double width, const double height, const double ratio = 0., const double min_width = 0., const double min_height = 0.) noexcept;
        
        //! Constructor.
        /** The function initializes another size.
         */
        SizeAttr(SizeAttr const& size) noexcept;
        
        //! Constructor.
        /** The function initializes another point.
         */
        SizeAttr(Point const& pt) noexcept;
        
        //! Destructor.
        /** The function deletes the point.
         */
        ~SizeAttr();
        
        //! Set the attribute value with a string.
        /** The function sets the attribute value with a string.
         @param text The value in the string format.
         */
        void setValue(string const& text) noexcept override;
        
        //! Retrieve the attribute value as a string.
        /** The function retrieves the attribute value as a string.
         @param text The value in the string format.
         */
        void getValue(string& text) const noexcept override;
        
        //! Set the width.
        /** The function sets the width.
         @param w The width.
         */
        inline void width(const double w) noexcept
        {
            m_point.x(max(w, m_min.x()));
            if(m_ratio)
            {
                m_point.y(m_point.x() * m_ratio);
            }
        }
        
        //! Set the height.
        /** The function sets the height.
         @param h The height.
         */
        inline void height(const double h) noexcept
        {
            if(!m_ratio)
            {
                m_point.y(max(h, m_min.y()));
            }
        }
        
        //! Set the ratio.
        /** The function sets the ratio.
         @param r The ratio.
         */
        inline void ratio(const double r) noexcept
        {
            m_ratio = max(r, 0.);
            if(m_ratio)
            {
                m_point.y(m_point.x() * m_ratio);
            }
        }
        
        //! Retrieve the width.
        /** The function retrieves the width.
         @return The width.
         */
        inline double width() const noexcept
        {
            return m_point.x();
        }
        
        //! Retrieve the height.
        /** The function retrieves the height.
         @return The height.
         */
        inline double height() const noexcept
        {
            return m_point.y();
        }
        
        //! Retrieve the ratio.
        /** The function retrieves the ratio.
         @return The ratio.
         */
        inline double ratio() const noexcept
        {
            return m_ratio;
        }
        
        //! Retrieve the minimum.
        /** The function retrieves the minimum.
         @return The minimum.
         */
        inline Point min() const noexcept
        {
            return m_min;
        }
        
        //! Retrieve the minimum width.
        /** The function retrieves the minimum width.
         @return The minimum width.
         */
        inline double minWidth() const noexcept
        {
            return m_min.x();
        }
        
        //! Retrieve the minimum height.
        /** The function retrieves the minimum height.
         @return The minimum height.
         */
        inline double minHeight() const noexcept
        {
            return m_min.y();
        }
        
        //! ...
        /** ...
         @return ...
         */
        inline SizeAttr& operator=(SizeAttr const& size) noexcept
        {
            m_ratio = size.ratio();
            m_min = size.m_min;
            m_point = size.m_point;
            return *this;
        }
        
        //! ...
        /** ...
         @return ...
         */
        inline SizeAttr& operator=(Point const& pt) noexcept
        {
            width(pt.x());
            height(pt.y());
            return *this;
        }
        
        //! ...
        /** ...
         @return ...
         */
        inline bool operator!=(SizeAttr const& size) noexcept
        {
            return width() != size.width() || height() != size.height();
        }
        
        //! ...
        /** ...
         @return ...
         */
        inline bool operator!=(Point const& pt) noexcept
        {
            return width() != pt.x() || height() != pt.y();
        }
        
        //! ...
        /** ...
         @return ...
         */
        inline operator Point() noexcept
        {
            return Point(width(), height());
        }
    };
    
    // ================================================================================ //
    //                                      COLOR                                       //
    // ================================================================================ //
    
    struct ColorAttr : public Color, public Attr::Value
    {
    public:
        using Color::Color;
        
        ColorAttr()
        {
            ;
        }
        
        ColorAttr(Color const& color) noexcept : Color(color)
        {
            ;
        }
        
        //! Set the attribute value with a string.
        /** The function sets the attribute value with a string.
         @param text The value in the string format.
         */
        void setValue(string const& text) noexcept override;
        
        //! Retrieve the attribute value as a string.
        /** The function retrieves the attribute value as a string.
         @param text The value in the string format.
         */
        void getValue(string& text) const noexcept override;
    };
}

#endif