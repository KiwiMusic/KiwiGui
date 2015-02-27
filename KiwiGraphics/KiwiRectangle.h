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

#ifndef __DEF_KIWI_GUI_RECTANGLE__
#define __DEF_KIWI_GUI_RECTANGLE__

#include "KiwiPoint.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      RECTANGLE                                   //
    // ================================================================================ //
    
    //! The rectangle holds four double values.
    /**
     The rectangle is used to represent a rectangle in a space and allows several modification.
     */
    class Rectangle
    {
    private:
        Point m_position;
        Point m_size;
        
        enum Positioning
        {
            Inside      = 0,
            Left        = 1,
            Right       = 2,
            Bottom      = 4,
            BottomLeft  = 5,
            BottomRight = 6,
            Top         = 8,
            TopLeft     = 9,
            TopRight    = 10
        };
        
        Positioning positioning(Point const& pt) const noexcept;
    public:
        
        //! Constructor.
        /** The function initializes a rectangle.
         */
        Rectangle() noexcept;
        
        //! Constructor.
        /** The function initializes a rectangle with four double values.
         @param x The abscissa of the top-left corner.
         @param y The ordinate of the top-left corner.
         @param width The width of the rectangle.
         @param height The height of the rectangle.
         */
        Rectangle(const double x, const double y, const double width, const double height) noexcept;
        
        //! Constructor.
        /** The function initializes a rectangle with two points.
         @param position The poisition of the top-left corner.
         @param size The size of the rectangle.
         */
        Rectangle(Point const& position, Point const& size) noexcept;
        
        //! Constructor.
        /** The function initializes another rectangle.
         @param rect The other rectangle.
         */
        Rectangle(Rectangle const& rect) noexcept;
        
        //! Destructor.
        /** The function deletes the rectangle.
         */
        ~Rectangle() noexcept;
        
        //! Return a rectangle with the positions of two opposite corners.
        /** The function returns a rectangle with the positions of two opposite corners.
         @param corner1 The position of the first corner.
         @param corner1 The position of the second corner.
         @return The new rectangle.
         */
        static Rectangle withCorners(Point const& corner1, Point const& corner2) noexcept;
        
        //! Return a rectangle with the center positions and the size.
        /** The function returns a rectangle with the center positions and the size.
         @param centre The position of centre.
         @param size The size.
         @return The new rectangle.
         */
        static Rectangle withCentre(Point const& centre, Point const& size);
        
        //! Return the same rectangle with a different position.
        /** The function returns the same rectangle with a different position.
         @param newpos The new position of the rectangle.
         @return The new rectangle.
         */
        Rectangle withPosition(Point const& newpos) const noexcept
        {
            return Rectangle(newpos.x(), newpos.y(), m_size.x(), m_size.y());
        }
        
        //! Return the same rectangle with a position at zero origin.
        /** The function returns the same rectangle with a position at zero origin.
         @return The new rectangle.
         */
        Rectangle withZeroOrigin() const noexcept
        {
            return Rectangle(0., 0., m_size.x(), m_size.y());
        }
        //! Retrieve the abscissa.
        /** The function retrieves the abscissa.
         @return The abscissa.
         */
        inline double x() const noexcept
        {
            return m_position.x();
        }
        
        //! Retrieve the ordinate.
        /** The function retrieves the ordinate.
         @return The ordinate.
         */
        inline double y() const noexcept
        {
            return m_position.y();
        }
        
        //! Retrieve the width.
        /** The function retrieves the width.
         @return The width.
         */
        inline double width() const noexcept
        {
            return m_size.x();
        }
        
        //! Retrieve the height.
        /** The function retrieves the height.
         @return The height.
         */
        inline double height() const noexcept
        {
            return m_size.y();
        }
        
        //! Retrieve the position.
        /** The function retrieves the position.
         @return The position.
         */
        inline Point position() const noexcept
        {
            return m_position;
        }
        
        //! Retrieve the size.
        /** The function retrieves the size.
         @return The size.
         */
        inline Point size() const noexcept
        {
            return m_size;
        }
        
        //! Retrieve the ordinate of the bottom.
        /** The function retrieves the ordinate of the bottom.
         @return The ordinate of the bottom.
         */
        double bottom() noexcept
        {
            return y() + height();
        }
        
        //! Retrieve the abscissa of the right.
        /** The function retrieves the abscissa of the right.
         @return The abscissa of the right.
         */
        double right() noexcept
        {
            return x() + width();
        }
        
        //! Retrieves the centre of the rectangle.
        /** The function retrieves the centre of the rectangle.
         @return The centre of the rectangle.
         */
        inline Point centre() noexcept
        {
            return Point(x() + width() * 0.5, y() + height() * 0.5);
        }
        
        //! Set the abscissa.
        /** The function sets the abscissa.
         @param x The abscissa.
         */
        inline void x(double x) noexcept
        {
            m_position.x(x);
        }
        
        //! Set the ordinate.
        /** The function sets the ordinate.
         @param y The ordinate.
         */
        inline void y(double y) noexcept
        {
            m_position.y(y);
        }
        
        //! Set the width.
        /** The function sets the width.
         @param width The width.
         */
        inline void width(double width) noexcept
        {
            m_size.x(max(width, 0.));
        }
        
        //! Set the height.
        /** The function sets the height.
         @param height The height.
         */
        inline void height(double height) noexcept
        {
            m_size.y(max(height, 0.));
        }
        
        //! Set the position.
        /** The function sets the position.
         @param position The position.
         */
        inline void position(Point const& position) noexcept
        {
            m_position = position;
        }
        
        //! Set the size.
        /** The function sets the size.
         @param size The size.
         */
        inline void size(Point const& size) noexcept
        {
            m_size.x(max(size.x(), 0.));
            m_size.y(max(size.y(), 0.));
        }
        
        //! Move the abscissa position of the rectangle.
        /** The function moves the abscissa position of the rectangle.
         @param left The abscissa position.
         */
        void left(double const left) noexcept
        {
            width(max(right() - left, 0.));
            x(left);
        }
        
        //! Move the ordinate position of the rectangle.
        /** The function moves the ordinate position of the rectangle.
         @param top The ordinate position.
         */
        void top(double const top) noexcept
        {
            height(max(bottom() - top, 0.));
            y(top);
        }
        
        //! Move the right position of the rectangle.
        /** The function moves the right position of the rectangle and expands or retracts it.
         @param top The right position.
         */
        void right(double right) noexcept
        {
            x(min(x(), right));
            width(right - x());
        }
        
        //! Move the bottom position of the rectangle.
        /** The function moves the bttom position of the rectangle and expands or retracts it.
         @param bottom The bottom position.
         */
        void bottom(double bottom) noexcept
        {
            y(min(y(), bottom));
            height(bottom - y());
        }
        
        //! Set the position and the size with another rectangle.
        /** The function sets the position and the size with another rectangle.
         @param rect The other rectangle.
         @return The rectangle.
         */
        inline Rectangle& operator=(Rectangle const& rect) noexcept
        {
            m_position = rect.position();
            m_size = rect.size();
            return *this;
        }
        
        //! Shift the rectangle with a point.
        /** The function shifts the rectangle with a point.
         @param pt The point.
         @return The rectangle.
         */
        inline Rectangle& operator+=(Point const& pt) noexcept
        {
            m_position += pt;
            return *this;
        }
        
        //! Shift the rectangle with a value.
        /** The function shifts the rectangle with a value.
         @param value The value.
         @return The rectangle.
         */
        inline Rectangle& operator+=(double const value) noexcept
        {
            m_position += value;
            return *this;
        }
        
        //! Shift inversed the rectangle with a point.
        /** The function shifts inversed the rectangle with a point.
         @param pt The point.
         @return The rectangle.
         */
        inline Rectangle& operator-=(Point const& pt) noexcept
        {
            m_position -= pt;
            return *this;
        }
        
        //! Shift inversed the rectangle with a value.
        /** The function shifts inversed the rectangle with a value.
         @param value The value.
         @return The rectangle.
         */
        inline Rectangle& operator-=(double const value) noexcept
        {
            m_position -= value;
            return *this;
        }
        
        //! Expand the rectangle with a point.
        /** The function expands the rectangle with a point.
         @param point The point.
         @return The rectangle.
         */
        inline Rectangle& operator*=(Point const& pt) noexcept
        {
            m_size *= pt;
            return *this;
        }
        
        //! Expand the rectangle with a value.
        /** The function expands the rectangle with a value.
         @param value The value.
         @return The rectangle.
         */
        inline Rectangle& operator*=(double const value) noexcept
        {
            m_size  *= value;
            return *this;
        }
        
        //! Retract the rectangle with a point.
        /** The function retracts the rectangle with a point.
         @param point The point.
         @return The rectangle.
         */
        inline Rectangle& operator/=(Point const& pt) noexcept
        {
            m_size /= pt;
            return *this;
        }
        
        //! Retract the rectangle with a value.
        /** The function retracts the rectangle with a value.
         @param value The value.
         @return The rectangle.
         */
        inline Rectangle& operator/=(double const value) noexcept
        {
            m_size /= value;
            return *this;
        }
        
        //! Retrieve the rectangle shifted with a point.
        /** The function the rectangle shifted with a point.
         @param pt The point.
         @return The rectangle.
         */
        inline Rectangle operator+(Point const& pt) noexcept
        {
            return Rectangle(x() + pt.x(), y() + pt.y(), width(), height());
        }
        
        //! Retrieve the rectangle shifted with a value.
        /** The function the rectangle shifted with a value.
         @param value The value.
         @return The rectangle.
         */
        inline Rectangle operator+(double const value) noexcept
        {
            return Rectangle(x() + value, y() + value, width(), height());
        }
        
        //! Retrieve the rectangle inverse shifted with a point.
        /** The function the rectangle inverse shifted with a point.
         @param pt The point.
         @return The rectangle.
         */
        inline Rectangle operator-(Point const& pt) noexcept
        {
            return Rectangle(x() - pt.x(), y() - pt.y(), width(), height());
        }
        
        //! Retrieve the rectangle inverse shifted with a value.
        /** The function the rectangle inverse shifted with a value.
         @param value The value.
         @return The rectangle.
         */
        inline Rectangle operator-(double const value) noexcept
        {
            return Rectangle(x() - value, y() - value, width(), height());
        }
        
        //! Retrieve the rectangle expanded with a point.
        /** The function the rectangle expanded with a point.
         @param pt The point.
         @return The rectangle.
         */
        inline Rectangle operator*(Point const& pt) noexcept
        {
            return Rectangle(x() * pt.x(), y() * pt.y(), width(), height());
        }
        
        //! Retrieve the rectangle expanded with a value.
        /** The function the rectangle expanded with a value.
         @param value The value.
         @return The rectangle.
         */
        inline Rectangle operator*(double const value) noexcept
        {
            return Rectangle(x() * value, y() * value, width(), height());
        }
        
        //! Retrieve the rectangle retracted with a point.
        /** The function the rectangle retracted with a point.
         @param pt The point.
         @return The rectangle.
         */
        inline Rectangle operator/(Point const& pt) noexcept
        {
            return Rectangle(x() / pt.x(), y() / pt.y(), width(), height());
        }
        
        //! Retrieve the rectangle retracted with a value.
        /** The function the rectangle retracted with a value.
         @param value The value.
         @return The rectangle.
         */
        inline Rectangle operator/(double const value) noexcept
        {
            return Rectangle(x() / value, y() / value, width(), height());
        }
        
        //! Get the equality two rectangle.
        /** The function retrieves the equality two rectangle.
         @param rect The other rectangle.
         @return true if the two retrieves are equal, otherwise false.
         */
        inline bool operator==(Rectangle const rect) const noexcept
        {
            return m_position == rect.position() && m_size == rect.size();
        }
        
        //! Get the equality two rectangle.
        /** The function retrieves the equality two rectangle.
         @param rect The other rectangle.
         @return true if the two retrieves are not equal, otherwise false.
         */
        inline bool operator!=(Rectangle const rect) const noexcept
        {
            return m_position != rect.position() || m_size != rect.size();
        }
        
        //! Get if the rectangle contains a point.
        /** The function retrieves if the rectangle contains a point.
         @param pt The point.
         @return true if the rectangle contains the point, otherwise false.
         */
        inline bool contains(Point const& pt) const noexcept
        {
            return positioning(pt) == Inside;
        }
        
        //! Get if the rectangle overlaps another rectangle.
        /** The function retrieves if the rectangle overlaps another rectangle.
         @param other The other rectangle.
         @return true if the rectangle overlaps the other rectangle, otherwise false.
         */
        inline bool overlaps(Rectangle const& other) const noexcept
        {
            return x() + width() > other.x() && y() + height() > other.y() && x() < other.x() + other.width() && y() < other.y() + other.height();
        }
        
        //! Expand the rectangle.
        /** The function expands the rectangle.
         @param pt The amount of expansion.
         */
        inline void expand(Point const& pt) noexcept
        {
            position(m_position - pt);
            width(max(0., width() + pt.x() * 2.));
            height(max(0., height() + pt.y() * 2.));
        }
        
        //! Expand the rectangle.
        /** The function expands the rectangle.
         @param value The amount of expansion.
         */
        inline void expand(double const value) noexcept
        {
            expand(Point(value, value));
        }
        
        //! Return an the expanded rectangle.
        /** The function returns an expanded rectangle.
         @param pt The amount of expansion.
         @return The new rectangle.
        */
        inline Rectangle expanded(Point const& pt) const noexcept
        {
            return Rectangle(m_position.x() - pt.x(), m_position.y() - pt.y(), max(0., width() + pt.x() * 2.), max(0., height() + pt.y() * 2.));
        }
        
        //! Return an the expanded rectangle.
        /** The function returns an expanded rectangle.
         @param value The amount of expansion.
         @return The new rectangle.
         */
        inline Rectangle expanded(const double value) const noexcept
        {
            return expanded(Point(value, value));
        }
        
        //! Reduce the rectangle.
        /** The function reduces the rectangle.
         @param pt The amount of reduction.
         */
        inline void reduce(Point const& pt) noexcept
        {
            expand(-pt);
        }
        
        //! Reduce the rectangle.
        /** The function reduces the rectangle.
         @param delta The amount of reduction.
         */
        inline void reduce(double const value) noexcept
        {
            expand(Point(-value, -value));
        }
        
        //! Return an the reduced rectangle.
        /** The function returns an reduced rectangle.
         @param pt The amount of reduction.
         @return The new rectangle.
         */
        inline Rectangle reduced(Point const& pt) const noexcept
        {
            return expanded(-pt);
        }
        
        //! Return an the reduced rectangle.
        /** The function returns an reduced rectangle.
         @param value The amount of reduction.
         @return The new rectangle.
         */
        inline Rectangle reduced(const double value) const noexcept
        {
            return reduced(Point(value, value));
        }
        
        //! Get if the rectangle overlaps a line.
        /** The function gets if the rectangle overlaps a line.
         @param begin The first point of the line.
         @param end   The end point of the line.
         @return true if the rectangle overlaps a line, otherwise false.
         */
        bool overlaps(Point const& begin, Point const& end) const noexcept;
        
        //! Get if the rectangle overlaps a quadratic bezier line.
        /** The function gets if the rectangle overlaps a quadratic bezier line.
         @param begin The first point of the line.
         @param ctrl  The control point of the line.
         @param end   The end point of the line.
         @return true if the rectangle overlaps a line, otherwise false.
         */
        bool overlaps(Point const& begin, Point const& ctrl, Point const& end) const noexcept;
        
        //! Get if the rectangle overlaps a cubic bezier line.
        /** The function gets if the rectangle overlaps a cubic bezier line.
         @param begin The first point of the line.
         @param ctrl1 The first control point of the line.
         @param ctrl2 The second control point of the line.
         @param end   The end point of the line.
         @return true if the rectangle overlaps a line, otherwise false.
         */
        bool overlaps(Point const& begin, Point const& ctrl1, Point const& ctrl2, Point const& end) const noexcept;
    };
    
}

#endif