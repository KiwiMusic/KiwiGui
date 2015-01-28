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

#include "Point.h"

namespace Kiwi
{
    namespace Gui
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
            
        public:
            
            //! Constructor.
            /** The function initializes a rectangle.
             */
            Rectangle() noexcept;
            
            //! Constructor.
            /** The function initializes a rectangle with four double values.
             */
            Rectangle(const double x, const double y, const double width, const double height) noexcept;
            
            //! Constructor.
            /** The function initializes a rectangle with two points.
             */
            Rectangle(Point const& position, Point const& size) noexcept;
            
            //! Destructor.
            /** The function deletes the rectangle.
             */
            ~Rectangle();
            
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
			
			//! Returns a Rectangle from the positions of two opposite corners.
			inline static Rectangle fromOppositeCorners(Point const& corner1, Point const& corner2) noexcept
			{
				const double x = min(corner1.x(), corner2.x());
				const double y = min(corner1.y(), corner2.y());
				double w = corner1.x() - corner2.x();
				double h = corner1.y() - corner2.y();
				
				if (w < 0) w = -w;
				if (h < 0) h = -h;
				
				return Rectangle(x, y, w, h);
			}
			
			//! Retrieves the rectangle centre.
			/** The function retrieves the rectangle centre.
			 @return The rectangle centre as a point.
			 */
			inline Point centre() noexcept
			{
				return Point(x() + width() * 0.5, y() + height() * 0.5);
			}
			
			/** Returns a rectangle with a centre position. */
            inline static Rectangle withCentre(Point const& centre, Point const& size)
            {
                return Rectangle(centre, Point()).expanded(size * 0.5);
            }
			
			/** Returns a rectangle whose size is the same as this one, but with a new top-left position */
			inline Rectangle withPosition(Point const& newpos) const noexcept
			{
				return Rectangle(newpos.x(), newpos.y(), m_size.x(), m_size.y());
			}
			
			/** Returns a rectangle whose size is the same as this one, but whose top-left position is (0, 0). */
			inline Rectangle withZeroOrigin() const noexcept
			{
				return Rectangle(0., 0., m_size.x(), m_size.y());
			}
			
            /** Moves the x position, adjusting the width so that the right-hand edge remains in the same place.
             If the x is moved to be on the right of the current right-hand edge, the width will be set to zero.
             */
            void left(double newLeft) noexcept
            {
                width(max(right() - newLeft, 0.));
                x(newLeft);
            }
            
            /** Moves the y position, adjusting the height so that the bottom edge remains in the same place.
             If the y is moved to be below the current bottom edge, the height will be set to zero.
             */
            void top(double newTop) noexcept
            {
                height(max(bottom() - newTop, 0.));
                y(newTop);
            }
            
            /** Adjusts the width so that the right-hand edge of the rectangle has this new value.
             If the new right is below the current X value, the X will be pushed down to match it.
             */
            void right(double newRight) noexcept
            {
                x(min(x(), newRight));
                width(newRight - x());
            }
            
            //! Retrieves the right-hand edge position of the rectangle.
            /** Retrieves the right-hand edge position of the rectangle.
             */
            double right() noexcept
            {
                return x() + width();
            }
            
            /** Adjusts the height so that the bottom edge of the rectangle has this new value.
             If the new bottom is lower than the current Y value, the Y will be pushed down to match it.
             */
            void bottom(double newBottom) noexcept
            {
                y(min(y(), newBottom));
                height(newBottom - y());
            }
            
            //! Retrieves the bottom edge position of the rectangle.
            /** Retrieves the bottom edge position of the rectangle.
             */
            double bottom() noexcept
            {
                return y() + height();
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
                m_size      *= value;
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
            
            inline Rectangle operator+(Point const& pt) const noexcept
            {
                return Rectangle(*this) += pt;
            }
            
            inline Rectangle operator+(double const value) const noexcept
            {
                return Rectangle(*this) += value;
            }
            
            inline Rectangle operator-(Point const& pt) const noexcept
            {
                return Rectangle(*this) -= pt;
            }
            
            inline Rectangle operator-(double const value) const noexcept
            {
                return Rectangle(*this) -= value;
            }
            
            inline Rectangle operator*(Point const& pt) const noexcept
            {
                return Rectangle(*this) *= pt;
            }
            
            inline Rectangle operator*(double const value) const noexcept
            {
                return Rectangle(*this) *= value;
            }
            
            inline Rectangle operator/(Point const& pt) const noexcept
            {
                return Rectangle(*this) /= pt;
            }
            
            inline Rectangle operator/(double const value) const noexcept
            {
                return Rectangle(*this) /= value;
            }
            
            inline bool operator==(Rectangle const rect) const noexcept
            {
                return m_position == rect.position() && m_size == rect.size();
            }
            
            inline bool operator==(Point const& pt) const noexcept
            {
                return m_position == pt && m_size == pt;
            }
            
            inline bool operator==(double const value) const noexcept
            {
                return m_position == value && m_size == value;
            }
            
            inline bool operator!=(Rectangle const rect) const noexcept
            {
                return m_position != rect.position() || m_size != rect.size();
            }

            inline bool operator!=(Point const& pt) const noexcept
            {
                return m_position != pt || m_size != pt;
            }
            
            inline bool operator!=(double const value) const noexcept
            {
                return m_position != value && m_size != value;
            }
            
            inline bool contains(Point const& pt) const noexcept
            {
                return pt.x() >= m_position.x() && pt.y() >= m_position.y() && pt.x() < m_position.x() + m_size.x() && pt.y() < m_position.y() + m_size.y();
            }
            
            inline bool overlaps(Rectangle const& other) const noexcept
            {
                return x() + width() > other.x() && y() + height() > other.y() && x() < other.x() + other.width() && y() < other.y() + other.height();
            }
			
			//! Expands the rectangle by a given amount.
			/** Effectively, its new size is (x - pt.x, y - pt.y, width + pt.x * 2, height + pt.y * 2).
			 @see expanded, reduce, reduced
			 */
			inline void expand(Point const& pt) noexcept
			{
				position(m_position - pt);
				width(max(0., width() + pt.x() * 2));
				height(max(0., height() + pt.y() * 2));
			}
			
			//! Expands the rectangle by a given amount.
			/** Effectively, its new size is (x - delta, y - delta, width + delta * 2, height + delta * 2).
			 @see expanded, reduce, reduced
			 */
            inline void expand(double const delta) noexcept
            {
				expand(Point(delta, delta));
            }
			
			//! Returns a rectangle that is larger than this one by a given amount.
			/** Effectively, the rectangle returned is (x - pt.x, y - pt.y, width + pt.x * 2, height + pt.y * 2).
			 @see expand, reduce, reduced
			 */
			Rectangle expanded(Point const& pt) const noexcept
			{
				const double w = max(0., width() + pt.x() * 2);
				const double h = max(0., height() + pt.y() * 2);
				return Rectangle(m_position.x() - pt.x(), m_position.y() - pt.y(), w, h);
			}
			
			//! Returns a rectangle that is larger than this one by a given amount.
			/** Effectively, its new size is (x - delta, y - delta, width + delta * 2, height + delta * 2).
			 @see expanded, reduce, reduced
			 */
			Rectangle expanded(const double delta) const noexcept
			{
				return expanded(Point(delta, delta));
			}
			
			//! Shrinks the rectangle by a given amount.
			/** Effectively, its new size is (x + pt.x, y + pt.y, width - pt.x * 2, height - pt.y * 2).
			 @see reduced, expand, expanded
			 */
            inline void reduce(Point const& pt) noexcept
            {
                expand(-pt);
            }
			
			//! Shrinks the rectangle by a given amount.
			/** Effectively, its new size is (x + delta, y + delta, width - delta * 2, height - delta * 2).
			 @see reduced, expand, expanded
			 */
			inline void reduce(double const delta) noexcept
			{
				expand(Point(-delta, -delta));
			}
			
			//! Returns a rectangle that is smaller than this one by a given amount.
			/** Effectively, the rectangle returned is (x + pt.x, y + pt.y, width - pt.x * 2, height - pt.y * 2).
			 @see reduce, expand, expanded
			 */
            Rectangle reduced(Point const& pt) const noexcept
            {
				return expanded(-pt);
            }
			
			//! Returns a rectangle that is smaller than this one by a given amount.
			/** Effectively, the rectangle returned is (x + delta, y + delta, width - delta * 2, height - delta * 2).
			 @see reduce, expand, expanded
			 */
            Rectangle reduced(const double delta) const noexcept
            {
                return reduced(Point(delta, delta));
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
}

#endif