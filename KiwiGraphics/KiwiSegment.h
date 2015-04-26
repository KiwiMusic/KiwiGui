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

#ifndef __DEF_KIWI_GUI_SEGMENT__
#define __DEF_KIWI_GUI_SEGMENT__

#include "KiwiSize.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                     SEGMENT                                      //
    // ================================================================================ //
    
    //! The segment holds two segment.
    /**
     The segment is used to represent a finite line in a space and allows several modification.
     */
    class Segment
    {
    private:
        Point m_start, m_end;
        
    public:
        
        //! Constructor.
        /** The function initializes a segment, using (0, 0) as its start and end points.
         */
        inline Segment() noexcept : m_start(), m_end(){}
        
        //! Constructor.
        /** The function initializes a segment with two point.
         @param start The start point.
         @param end   The end point.
         */
        inline Segment(const Point& start, const Point& end) noexcept : m_start(start), m_end(end){}
        
        //! Constructor.
        /** The function initializes a segment with another segment.
         @param pt The other segment.
         */
        inline Segment(Segment const& segment) noexcept : m_start(segment.start()), m_end(segment.end()){}
        
        //! Constructor.
        /** The function initializes a segment with two points.
         @param start The start point.
         @param end   The end point.
         */
        inline Segment(Point&& start, Point&& end) noexcept
        {
            swap(m_start, start);
            swap(m_end, end);
        }
        
        //! Destructor.
        /** The function deletes the segment.
         */
        inline ~Segment() noexcept {}
        
        //! Retrieves the start point.
        /** The function retrieves the start point.
         @return The start point.
         */
        inline Point start() const noexcept
        {
            return m_start;
        }
        
        //! Retrieves the end point.
        /** The function retrieves the end point.
         @return The end point.
         */
        inline Point end() const noexcept
        {
            return m_end;
        }
        
        //! Set a new start point.
        /** The function sets a new start point.
         @param start The new start point.
         */
        inline void start(Point const& newStart) noexcept
        {
            m_start = newStart;
        }
        
        //! Set a new end point.
        /** The function sets a new end point.
         @param start The new end point.
         */
        inline void end(Point const& newEnd) noexcept
        {
            m_end = newEnd;
        }
        
        //! Retrieves the abscissa of the start point.
        /** The function retrieves the abscissa of the start point.
         @return The abscissa of the start point.
         */
        inline double startX() const noexcept
        {
            return m_start.x();
        }
        
        //! Retrieves the abscissa of the end point.
        /** The function retrieves the abscissa of the end point.
         @return The abscissa of the end point.
         */
        inline double endX() const noexcept
        {
            return m_end.x();
        }
        
        //! Retrieves the ordinate of the start point.
        /** The function retrieves the ordinate of the start point.
         @return The ordinate of the start point.
         */
        inline double startY() const noexcept
        {
            return m_start.y();
        }
        
        //! Retrieves the ordinate of the end point.
        /** The function retrieves the ordinate of the end point.
         @return The ordinate of the end point.
         */
        inline double endY() const noexcept
        {
            return m_end.y();
        }
        
        //! Sets the abscissa of the start point.
        /** The function sets the abscissa of the start point.
         @param x The abscissa of the start point.
         */
        inline void startX(const double x) noexcept
        {
            m_start.x(x);
        }
        
        //! Sets the abscissa of the end point.
        /** The function sets the abscissa of the end point.
         @param x The abscissa of the end point.
         */
        inline void endX(const double x) noexcept
        {
            m_end.x(x);
        }
        
        //! Sets the ordinate of the start point.
        /** The function sets the ordinate of the start point.
         @param y The ordinate of the start point.
         */
        inline void startY(const double y) noexcept
        {
            m_start.y(y);
        }
        
        //! Sets the ordinate of the end point.
        /** The function sets the ordinate of the end point.
         @param y The ordinate of the end point.
         */
        inline void endY(const double y) noexcept
        {
            m_end.y(y);
        }
        
        //! Retrieve the segment as a vector of atoms.
        /** The function retrieves the segment as a vector of atoms.
         @return The vector of atoms.
         */
        inline Vector get() const noexcept
        {
            return Vector({m_start.x(), m_start.y(), m_end.x(), m_end.y()});
        }
        
        //! Set the attribute value with a vector of atoms.
        /** The function sets the attribute value with a vector of atoms.
         @param vector The vector of atoms.
         */
        void set(Vector const& vector) noexcept
        {
            if(vector.size() > 3 && vector[0].isNumber() && vector[1].isNumber() && vector[2].isNumber() && vector[3].isNumber())
            {
                m_start = Point(double(vector[0]), double(vector[1]));
                m_end   = Point(double(vector[2]), double(vector[3]));
            }
        }
        
        //! Sets the segment with another one.
        /** The function sets the segment with another one.
         @param segment another segment.
         @return The segment.
         */
        inline Segment& operator=(Segment const& segment) noexcept
        {
            m_start = segment.start();
            m_end   = segment.end();
            return *this;
        }
        
        //! Sets the segment with another one.
        /** The function sets the segment with another one.
         @param segment another segment.
         @return The segment.
         */
        inline Segment& operator=(Segment&& segment) noexcept
        {
            swap(m_start, segment.m_start);
            swap(m_end, segment.m_end);
            return *this;
        }
        
        //! Shift the segment by a point.
        /** The function shifts the segment by a point.
         @param pt The point.
         @return The segment.
         */
        inline Segment& operator+=(Point const& pt) noexcept
        {
            m_start += pt;
            m_end   += pt;
            return *this;
        }
        
        //! Shift the segment by a point.
        /** The function shifts the segment by a point.
         @param value The value.
         @return The segment.
         */
        inline Segment& operator+=(double const value) noexcept
        {
            m_start += value;
            m_end   += value;
            return *this;
        }
        
        //! Shift the segment by a point.
        /** The function shifts the segment by a point.
         @param pt The point.
         @return The segment.
         */
        inline Segment& operator-=(Point const& pt) noexcept
        {
            m_start -= pt;
            m_end   -= pt;
            return *this;
        }
        
        //! Shift the segment by a point.
        /** The function shifts the segment by a point.
         @param pt The point.
         @return The segment.
         */
        inline Segment& operator-=(double const value) noexcept
        {
            m_start -= value;
            m_end   -= value;
            return *this;
        }
        
        //! Retrieves a new segment shifted by a point.
        /** The function retrieves a new segment shifted by a point.
         @param pt The point to add.
         @return The new segment.
         */
        inline Segment operator+(Point const& pt) const noexcept
        {
            return Segment(m_start + pt, m_end + pt);
        }
        
        //! Retrieves a new segment shifted by a value.
        /** The function retrieves a new segment shifted by a value.
         @param value The value to add.
         @return The new segment.
         */
        inline Segment operator+(double const value) const noexcept
        {
            return Segment(m_start + value, m_end + value);
        }
        
        //! Retrieves a new segment shifted by a point.
        /** The function retrieves a new segment shifted by a point.
         @param pt The point to add.
         @return The new segment.
         */
        inline Segment operator-(Point const& pt) const noexcept
        {
            return Segment(m_start - pt, m_end - pt);
        }
        
        //! Retrieves a new segment shifted by a value.
        /** The function retrieves a new segment shifted by a value.
         @param value The value to add.
         @return The new segment.
         */
        inline Segment operator-(double const value) const noexcept
        {
            return Segment(m_start - value, m_end - value);
        }
        
        //! Get the equality of the segment with another.
        /** The function retrieves the equality of the segment with another.
         @param segment The other segment.
         @return true if the two segments are equal, otherwise false.
         */
        inline bool operator==(Segment const& segment) const noexcept
        {
            return m_start == segment.start() && m_end == segment.end();
        }
        
        //! Get the equality of the segment with another.
        /** The function retrieves the equality of the segment with another.
         @param segment The other segment.
         @return true if the two segments are not equal, otherwise false.
         */
        inline bool operator!=(Segment const& segment) const noexcept
        {
            return m_start != segment.start() && m_end != segment.end();
        }
        
        //! Retrieve a copy and apply a rotation from the origin.
        /** The function retrieves a copy and applies a rotation from the origin.
         @param The angle
         @return The copy with the rotation.
         */
        Segment rotated(double const angle) const noexcept
        {
            return Segment(m_start.rotated(angle), m_end.rotated(angle));
        }
        
        //! Retrieve a copy and apply a rotation from another point.
        /** The function retrieves a copy and applies a rotation from another point.
         @param origin The origin point.
         @param angle  The angle
         @return The copy with the rotation.
         */
        inline Segment rotated(Point const& origin, double const angle) const noexcept
        {
            return Segment(m_start.rotated(origin, angle), m_end.rotated(origin, angle));
        }
        
        //! Apply a rotation from the origin.
        /** The function Applies a rotation from the origin.
         @param angle  The angle
         */
        void rotate(double const angle) noexcept
        {
            m_start.rotate(angle);
            m_end.rotate(angle);
        }
        
        //! Apply a rotation from the origin from another point.
        /** The function Applies a rotation from another point.
         @param origin The origin point.
         @param angle  The angle
         */
        void rotate(Point const& origin, double const angle) noexcept
        {
            *this = rotated(origin, angle);
        }
        
        //! Returns a reversed segment version.
        /** The function returns a segment that is the same as this one, but with the start and end reversed.
         */
        const Segment reversed() const noexcept
        {
            return Segment(m_end, m_start);
        }
        
        //! Reverse start and end points.
        /** The function reverses start and end points.
         */
        const void reverse() noexcept
        {
            swap(m_start, m_end);
        }
        
        //! Retrieve the angle of the segment.
        /** This value is the number of radians clockwise from the 3 o'clock direction,
         where the segment's start point is considered to be at the centre.
         @return The angle of the segment.
         */
        inline double angle() const noexcept
        {
            return m_start.angle(m_end);
        }
        
        //! Retrieve the length of the segment.
        /** The function retrieves the length from the origin.
         @return The length.
         */
        inline double length() const noexcept
        {
            return abs(m_start.distance(m_end));
        }
        
        //! Retrieve the smallest distance from a point.
        /** The function retrieves the smallest distance from a point.
         @param pt The point.
         @return The distance from the point.
         */
        double distance(Point const& pt) const noexcept
        {
            const Point delta(m_end - m_start);
            const double length = delta.x() * delta.x() + delta.y() * delta.y();
            
            if (length > 0)
            {
                const double prop = ((pt.x() - m_start.x()) * delta.x() + (pt.y() - m_start.y()) * delta.y()) / length;
                
                if (prop >= 0 && prop <= 1.0)
                {
                    return pt.distance(m_start + delta * (prop));
                }
            }
            
            const double fromStart = pt.distance(m_start);
            const double fromEnd = pt.distance(m_end);
            
            return (fromStart < fromEnd) ? fromStart : fromEnd;
        }
        
        //! Retrieve the smallest distance from a point.
        /** So if the point is close to the line, this will return the perpendicular
         distance from the line; if the point is a long way beyond one of the line's
         end-point's, it'll return the straight-line distance to the nearest end-point.
         @param pt The point.
         @param onSegment receives the position of the point that is found.
         @return The distance from the point.
         */
        double distance(Point const& pt, Point& onSegment) const noexcept
        {
            const Point delta(m_end - m_start);
            const double length = delta.x() * delta.x() + delta.y() * delta.y();
            
            if (length > 0)
            {
                const double prop = ((pt.x() - m_start.x()) * delta.x() + (pt.y() - m_start.y()) * delta.y()) / length;
                
                if (prop >= 0 && prop <= 1.0)
                {
                    onSegment = m_start + delta * (prop);
                    return pt.distance(onSegment);
                }
            }
            
            const double fromStart = pt.distance(m_start);
            const double fromEnd = pt.distance(m_end);
            
            if (fromStart < fromEnd)
            {
                onSegment = m_start;
                return fromStart;
            }
            else
            {
                onSegment = m_end;
                return fromEnd;
            }
        }
        
        //! Returns true if this segment intersects another.
        /** The function returns true if this segment intersects another.
         @param segment The other segment.
         @return True if this segment intersects another.
         */
        bool intersects(Segment const& segment) const noexcept;
        
        //! Returns true if this segment intersects another.
        /** The function returns true if this segment intersects another, and find the intersection point.
         @param segment The other segment.
         @param intersection The position of the point where the segments meet (or where they would meet if they were infinitely long)
         @return True if this segment intersects another.
         */
        bool intersects(Segment const& segment, Point& intersection) const noexcept;
        
        //! Returns true if this segment intersects another.
        /** The function returns true if this segment intersects another.
         @param segment The other segment.
         @return True if this segment intersects another.
         */
        static bool intersects(Segment const& s1, Segment const& s2) noexcept;
        
        //! Returns true if this segment intersects another.
        /** The function returns true if this segment intersects another, and find the intersection point.
         @param segment The other segment.
         @param intersection The position of the point where the segments meet (or where they would meet if they were infinitely long)
         @return True if this segment intersects another.
         */
        static bool intersects(Segment const& s1, Segment const& s2, Point& intersection) noexcept;

    };
}

#endif