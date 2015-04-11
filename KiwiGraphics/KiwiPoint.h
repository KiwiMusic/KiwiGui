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

#ifndef __DEF_KIWI_GUI_POINT__
#define __DEF_KIWI_GUI_POINT__

#include "../../KiwiCore/KiwiCore.h"

namespace Kiwi
{
    class Path;
    // ================================================================================ //
    //                                      POINT                                       //
    // ================================================================================ //
    
    //! The point holds two double values.
    /**
     The point is used to represent a point in a space and allows several modification.
     */
    class Point
    {
    private:
        double m_x;
        double m_y;
        
        static ulong solve(double a, double b, double c, double const d, double &solution1, double &solution2, double &solution3);
        static ulong solve(array<Point, 6>& W, double *t, const ulong depth);
    public:
        
        //! Constructor.
        /** The function initializes a point at zero origin.
         */
        Point() noexcept;
        
        //! Constructor.
        /** The function initializes a point with two double values.
         @param x The abscissa.
         @param y The ordinate.
         */
        Point(const double x, const double y) noexcept;
        
        //! Constructor.
        /** The function initializes a point with another point.
         @param pt The other point.
         */
        Point(Point const& pt) noexcept;
        
        //! Constructor.
        /** The function initializes a point from a position over a path.
         @param path The path.
         @param position The position on the path (first point is 0 and and end point is 1).
         */
        Point(Path const& path, const double position) noexcept;
        
        //! Destructor.
        /** The function deletes the point.
         */
        ~Point() noexcept;
        
        //! Retrieve the point over a line.
        /** The function retrieves the point over a line.
         @param begin The first point of the line.
         @param end   The end point of the line.
         @param delta The position of the point over the line (first point is 0 and and end point is 1).
         @return The point.
         */
        static Point fromLine(Point const& begin, Point const& end, const double delta) noexcept;
        
        //! Retrieve the point over a quadratic bezier line.
        /** The function retrieves the point over a quadratic bezier line.
         @param begin The first point of the line.
         @param ctrl  The control point of the line.
         @param end   The end point of the line.
         @param delta The position of the point over the line (first point is 0 and and end point is 1).
         @return The point.
         */
        static Point fromLine(Point const& begin, Point const& ctrl, Point const& end, const double delta) noexcept;
        
        //! Retrieve the point over a cubic bezier line.
        /** The function retrieves the point over a cubic bezier line.
         @param begin The first point of the line.
         @param ctrl1 The first control point of the line.
         @param ctrl2 The second control point of the line.
         @param end The end point of the line.
         @param delta The position of the point over the line (first point is 0 and and end point is 1).
         @return The point.
         */
        static Point fromLine(Point const& begin, Point const& ctrl1, Point const& ctrl2, Point const& end, const double delta) noexcept;
        
        //! Set the abscissa.
        /** The function sets the abscissa.
         @param x The abscissa.
         */
        inline void x(const double x) noexcept
        {
            m_x = x;
        }
        
        //! Set the ordinate.
        /** The function sets the ordinate.
         @param y The ordinate.
         */
        inline void y(const double y) noexcept
        {
            m_y = y;
        }
        
        //! Retrieve the abscissa.
        /** The function retrieves the abscissa.
         @return The abscissa.
         */
        inline double x() const noexcept
        {
            return m_x;
        }
        
        //! Retrieve the ordinate.
        /** The function retrieves the ordinate.
         @return The ordinate.
         */
        inline double y() const noexcept
        {
            return m_y;
        }
        
        //! Set the abscissa and the ordinate with another point.
        /** The function sets the abscissa and the ordinate with another point.
         @param pt Another point.
         @return The point.
         */
        inline Point& operator=(Point const& pt) noexcept
        {
            m_x = pt.m_x;
            m_y = pt.m_y;
            return *this;
        }
        
        //! Set the abscissa and the ordinate with a value.
        /** The function sets the abscissa and the ordinate with a value.
         @param value The value.
         @return The point.
         */
        inline Point& operator=(double const& value) noexcept
        {
            m_x = value;
            m_y = value;
            return *this;
        }
        
        //! Increment the abscissa and the ordinate with another point.
        /** The function increments the abscissa and the ordinate with another point.
         @param pt Another point.
         @return The point.
         */
        inline Point& operator+=(Point const& pt) noexcept
        {
            m_x += pt.m_x;
            m_y += pt.m_y;
            return *this;
        }
        
        //! Increment the abscissa and the ordinate with a value.
        /** The function increments the abscissa and the ordinate with a value.
         @param value The value.
         @return The point.
         */
        inline Point& operator+=(double const value) noexcept
        {
            m_x += value;
            m_y += value;
            return *this;
        }
        
        //! Decrement the abscissa and the ordinate with another point.
        /** The function decrements the abscissa and the ordinate with another point.
         @param value The value.
         @return The point.
         */
        inline Point& operator-=(Point const& pt) noexcept
        {
            m_x -= pt.m_x;
            m_y -= pt.m_y;
            return *this;
        }
        
        //! Decrement the abscissa and the ordinate with a value.
        /** The function decrements the abscissa and the ordinate with a value.
         @param pt Another point.
         @return The point.
         */
        inline Point& operator-=(double const value) noexcept
        {
            m_x -= value;
            m_y -= value;
            return *this;
        }
        
        //! Multiply the abscissa and the ordinate with another point.
        /** The function multiplies the abscissa and the ordinate with another point.
         @param value The value.
         @return The point.
         */
        inline Point& operator*=(Point const& pt) noexcept
        {
            m_x *= pt.m_x;
            m_y *= pt.m_y;
            return *this;
        }
        
        //! Multiply the abscissa and the ordinate with a value.
        /** The function multiplies the abscissa and the ordinate with a value.
         @param pt Another point.
         @return The point.
         */
        inline Point& operator*=(double const value) noexcept
        {
            m_x *= value;
            m_y *= value;
            return *this;
        }
        
        //! Divide the abscissa and the ordinate with another point.
        /** The function divides the abscissa and the ordinate with another point.
         @param value The value.
         @return The point.
         */
        inline Point& operator/=(Point const& pt) noexcept
        {
            m_x /= pt.m_x;
            m_y /= pt.m_y;
            return *this;
        }
        
        //! Divide the abscissa and the ordinate with a value.
        /** The function divides the abscissa and the ordinate with a value.
         @param pt Another point.
         @return The point.
         */
        inline Point& operator/=(double const value) noexcept
        {
            m_x /= value;
            m_y /= value;
            return *this;
        }
        
        //! Add a value to the point.
        /** The function adds a value to the point.
         @param value The value to add.
         @return The new point.
         */
        inline Point operator+(double const value) noexcept
        {
            return Point(m_x + value, m_y + value);
        }
        
        //! Add a a point to the point.
        /** The function adds a value to the point.
         @param pt The point to add.
         @return The new point.
         */
        inline Point operator+(Point const& pt) noexcept
        {
            return Point(m_x + pt.x(), m_y + pt.y());
        }
        
        //! Subtract a a value to the point.
        /** The function subtracts a value to the point.
         @param value The value to subtract.
         @return The new point.
         */
        inline Point operator-(double const value) const noexcept
        {
            return Point(m_x - value, m_y - value);
        }
        
        //! Subtract a a point to the point.
        /** The function subtract to the point.
         @param pt The point to subtract.
         @return The new point.
         */
        inline Point operator-(Point const pt) const noexcept
        {
            return Point(m_x - pt.x(), m_y - pt.y());
        }
        
        //! Multiply a point with the point.
        /** The function multiplies a point with the point.
         @param pt The point to multiply with.
         @return The new point.
         */
        inline Point operator*(Point const pt) const noexcept
        {
            return Point(m_x * pt.x(), m_y * pt.y());
        }
        
        //! Divide a value with the point.
        /** The function divides a value with the point.
         @param value The value to divide with.
         @return The new point.
         */
        inline Point operator/(const double value) const noexcept
        {
            return Point(m_x / value, m_y / value);
        }
        
        //! Divide a point with the point.
        /** The function divides a point with the point.
         @param pt The point to divide with.
         @return The new point.
         */
        inline Point operator/(Point const pt) const noexcept
        {
            return Point(m_x * pt.x(), m_y * pt.y());
        }
        
        //! Returns the inverse of the point.
        /** The function return the inverse of the point.
         @return The new point.
         */
        inline Point operator-() const noexcept
        {
            return Point(-m_x, -m_y);
        }
        
        //! Get the equality of the point with another.
        /** The function retrieves the equality of the point with another.
         @param pt The other point.
         @return true if the two points are equal, otherwise false.
         */
        inline bool operator==(Point const& pt) const noexcept
        {
            return m_x == pt.x() && m_y == pt.y();
        }
        
        //! Get the equality of the point with another.
        /** The function retrieves the equality of the point with another.
         @param pt The other point.
         @return true if the two points are not equal, otherwise false.
         */
        inline bool operator!=(Point const& pt) const noexcept
        {
            return m_x != pt.x() || m_y != pt.y();
        }
        
        //! Retrieve a copy and apply a rotation from the origin.
        /** The function retrieves a copy and applies a rotation from the origin.
         @param The angle
         @return The copy with the rotation.
         */
        Point rotate(double const angle) const noexcept
        {
            return Point(m_x * cos(angle) - m_y * sin(angle), m_x * sin(angle) + m_y * cos(angle));
        }
        
        //! Retrieve a copy and apply a rotation from another point.
        /** The function retrieves a copy and applies a rotation from another point.
         @pram pt The other point.
         @param The angle
         @return The copy with the rotation.
         */
        inline Point rotate(Point const& pt, double const angle) const noexcept
        {
            const Point newpt = *this - pt;
            return Point(newpt.x() * cos (angle) - newpt.y() * sin (angle) + pt.x(), newpt.x() * sin (angle) + newpt.y() * cos (angle) + pt.y());
        }
        
        //! Retrieve the length from the origin.
        /** The function retrieves the length from the origin.
         @return The length.
         */
        inline double length() const noexcept
        {
            return m_x * m_x + m_y * m_y;
        }
        
        //! Retrieve the distance from the origin.
        /** The function retrieves the distance from the origin.
         @return The distance.
         */
        inline double distance() const noexcept
        {
            return sqrt(m_x * m_x + m_y * m_y);
        }
        
        //! Retrieve the distance from another point.
        /** The function retrieves the distance from another point.
         @param pt The other point.
         @return The distance.
         */
        inline double distance(Point const& pt) const noexcept
        {
            return sqrt((m_x - pt.x()) * (m_x - pt.x()) + (m_y - pt.y()) * (m_y - pt.y()));
        }
        
        //! Retrieve the angle from the origin.
        /** The function retrieves the angle from origin.
         @return The angle.
         */
        inline double angle() const noexcept
        {
            return atan2(m_y, m_x);
        }
        
        //! Retrieve the angle from another point.
        /** The function retrieves the angle from another point.
         @param pt The other point.
         @return The angle.
         */
        inline double angle(Point const& pt) const noexcept
        {
            return atan2(m_y - pt.y(), m_x - pt.x());
        }
        
        //! Retrieve the dot product with another point.
        /** The function retrieves the dot product with another point.
         @param pt The other point.
         @return The dot product.
         */
        inline double dot(Point const& pt) const noexcept
        {
            return m_x * pt.x() + m_y * pt.y();
        }
        
        //! Retrieve the distance from a line.
        /** The function retrieves the distance a line.
         @param begin The first point of the line.
         @param end   The end point of the line.
         @return The distance.
         */
        double distance(Point const& begin, Point const& end) const noexcept;
        
        //! Retrieve the distance from a quadratic bezier line.
        /** The function retrieves the distance a quadratic bezier line.
         @param begin The first point of the line.
         @param ctrl  The control point of the line.
         @param end   The end point of the line.
         @return The distance.
         */
        double distance(Point const& begin, Point const& ctrl, Point const& end) const noexcept;
        
        //! Retrieve the distance from a cubic bezier line.
        /** The function retrieves the distance a cubic bezier line.
         @param begin The first point of the line.
         @param ctrl1 The first control point of the line.
         @param ctrl2 The second control point of the line.
         @param end   The end point of the line.
         @return The distance.
         */
        double distance(Point const& begin, Point const& ctrl1, Point const& ctrl2, Point const& end) const noexcept;
        
        //! Get if the point is near to another point.
        /** The function gets if the point is near to another point.
         @param pt The other point.
         @param distance The distance of neighborhood.
         @return true if the two points are near, otherwise false.
         */
        bool near(Point const& pt, double const distance) const noexcept;
        
        //! Get if the point is near or over a line.
        /** The function gets if the point is near or over a line.
         @param begin The first point of the line.
         @param end   The end point of the line.
         @param distance The distance of neighborhood (0 means over the line).
         @return true if the point is near to the line, otherwise false.
         */
        bool near(Point const& begin, Point const& end, double const distance) const noexcept;
        
        //! Get if the point is near or over a quadratic bezier line.
        /** The function gets if the point is near or over a quadratic bezier line.
         @param begin The first point of the line.
         @param ctrl  The control point of the line.
         @param end   The end point of the line.
         @param distance The distance of neighborhood (0 means over the line).
         @return true if the point is near to the line, otherwise false.
         */
        bool near(Point const& begin, Point const& ctrl, Point const& end, double const distance) const noexcept;
        
        //! Get if the point is near or over a cubic bezier line.
        /** The function gets if the point is near or over a cubic bezier line.
         @param begin The first point of the line.
         @param ctrl1 The first control point of the line.
         @param ctrl2 The second control point of the line.
         @param end   The end point of the line.
         @param distance The distance of neighborhood (0 means over the line).
         @return true if the point is near to the line, otherwise false.
         */
        bool near(Point const& begin, Point const& ctrl1, Point const& ctrl2, Point const& end, double const distance) const noexcept;
    };
    
    //! Multiply a value with a point.
    /** The function multiplies a value a the point.
     @param pt The point to multiply.
     @param value The value to multiply with.
     @return The new point.
     */
    static inline Point operator*(Point const& pt, double const value) noexcept
    {
        return Point(pt.x() * value, pt.y() * value);
    }
    
    //! Multiply a value with a point.
    /** The function multiplies a value a the point.
     @param pt The point to multiply.
     @param value The value to multiply with.
     @return The new point.
     */
    static inline Point operator*(const double value, Point const& pt) noexcept
    {
        return Point(pt.x() * value, pt.y() * value);
    }
    
    // ================================================================================ //
    //                                      ATTR                                        //
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
    
    typedef shared_ptr<Attr::Typed<PointValue>>		sAttrPoint;
    typedef shared_ptr<Attr::Typed<SizeValue>>		sAttrSize;
    typedef SizeValue Size;
}

#endif