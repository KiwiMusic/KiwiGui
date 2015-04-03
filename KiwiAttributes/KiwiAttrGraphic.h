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

#include "KiwiAttr.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      POSITION                                    //
    // ================================================================================ //
    
    class PointValue : public Point, public Attr::Value
    {
    public:
        using Point::Point;
        
        PointValue()
        {
            ;
        }
        
        PointValue(Point const& point) noexcept : Point(point)
        {
            ;
        }
        
        //! Retrieve the attribute value as a vector of atoms.
        /** The function retrieves the attribute value as a vector of atoms.
         @return The vector of atoms.
         */
        Vector get() const noexcept override;
        
        //! Set the attribute value with a vector of atoms.
        /** The function sets the attribute value with a vector of atoms.
         @param vector The vector of atoms.
         */
        void set(Vector const& vector) override;
    };
    
    // ================================================================================ //
    //                                      SIZE                                        //
    // ================================================================================ //
    
    //! The size holds is an unsigned point with a ratio.
    /**
     The size holds is an unsigned point with a ratio that defines
     */
    class SizeValue : public Attr::Value
    {
        double m_ratio;
        Point  m_min;
        Point  m_point;
    public:
        
        //! Constructor.
        /** The function initializes a size null.
         */
        SizeValue() noexcept;
        
        //! Constructor.
        /** The function initializes a point with two double values.
         @param width The width.
         @param height The height.
         @param ratio The ratio between the width and the height.
         */
        SizeValue(const double width, const double height, const double min_width = 0., const double min_height = 0., const double ratio = 0.) noexcept;
        
        //! Constructor.
        /** The function initializes another size.
         */
        SizeValue(SizeValue const& size) noexcept;
        
        //! Destructor.
        /** The function deletes the point.
         */
        ~SizeValue();
        
        //! Retrieve the attribute value as a vector of atoms.
        /** The function retrieves the attribute value as a vector of atoms.
         @return The vector of atoms.
         */
        Vector get() const noexcept override;
        
        //! Set the attribute value with a vector of atoms.
        /** The function sets the attribute value with a vector of atoms.
         @param vector The vector of atoms.
         */
        void set(Vector const& vector) override;
        
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
        inline SizeValue& operator=(SizeValue const& size) noexcept
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
        inline SizeValue& operator=(Point const& pt) noexcept
        {
            width(pt.x());
            height(pt.y());
            return *this;
        }
        
        //! ...
        /** ...
         @return ...
         */
        inline bool operator!=(SizeValue const& size) noexcept
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
    
    struct ColorValue : public Color, public Attr::Value
    {
    public:
        using Color::Color;
        
        ColorValue()
        {
            ;
        }
        
        ColorValue(Color const& color) noexcept : Color(color)
        {
            ;
        }
        
        //! Retrieve the attribute value as a vector of atoms.
        /** The function retrieves the attribute value as a vector of atoms.
         @return The vector of atoms.
         */
        Vector get() const noexcept override;
        
        //! Set the attribute value with a vector of atoms.
        /** The function sets the attribute value with a vector of atoms.
         @param vector The vector of atoms.
         */
        void set(Vector const& vector) override;
    };
    
    // ================================================================================ //
    //                                      RECTANGLE                                   //
    // ================================================================================ //
    
    struct RectangleValue : public Rectangle, public Attr::Value
    {
    public:
        using Rectangle::Rectangle;
        
        RectangleValue()
        {
            ;
        }
        
        RectangleValue(Rectangle const& rectangle) noexcept : Rectangle(rectangle)
        {
            ;
        }
        
        //! Retrieve the attribute value as a vector of atoms.
        /** The function retrieves the attribute value as a vector of atoms.
         @return The vector of atoms.
         */
        Vector get() const noexcept override;
        
        //! Set the attribute value with a vector of atoms.
        /** The function sets the attribute value with a vector of atoms.
         @param vector The vector of atoms.
         */
        void set(Vector const& vector) override;
    };
	
	// ================================================================================ //
	//                                      RECTANGLE                                   //
	// ================================================================================ //
	
	struct FontValue : public Font, public Attr::Value
	{
	public:
		using Font::Font;
		
        //! Retrieve the attribute value as a vector of atoms.
        /** The function retrieves the attribute value as a vector of atoms.
         @return The vector of atoms.
         */
        Vector get() const noexcept override;
        
        //! Set the attribute value with a vector of atoms.
        /** The function sets the attribute value with a vector of atoms.
         @param vector The vector of atoms.
         */
        void set(Vector const& vector) override;
	};
}

#endif