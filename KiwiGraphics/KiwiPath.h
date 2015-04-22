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

#ifndef __DEF_KIWI_GUI_PATH__
#define __DEF_KIWI_GUI_PATH__

#include "KiwiRectangle.h"

// Have to finish (later)
namespace Kiwi
{
    // ================================================================================ //
    //                                      PATH                                        //
    // ================================================================================ //
    
    //! The path holds a set of points.
    /**
     The point is used to represent a set a segment in a space and allows several modification.
     */
    class Path
    {
    public:
        enum Mode
        {
            Move        = 0,
            Linear      = 1,
            Quadratic   = 2,
            Cubic       = 3
        };
        
    private:
        //! Node.
        /** A node repesent a point in a pth.
         */
        struct Node
        {
            Point point;
            Mode  mode;
            inline Node(Point const& pt, Mode const m = Linear) noexcept : point(pt), mode(m) {};
            inline Node(Node const& other) noexcept : point(other.point), mode(other.mode) {};
            inline Node(Point&& pt, Mode const m = Linear) noexcept : mode(m) {swap(point, pt);};
            inline Node(Node&& other) noexcept : mode(other.mode) {swap(point, other.point);};
            inline ~Node() noexcept {};
            inline Node& operator=(Node const& other) noexcept {point = other.point; mode = other.mode; return *this;}
            inline Node& operator=(Point const& pt) noexcept {point = pt; return *this;}
            inline Node& operator=(Node&& other) noexcept {swap(point, other.point); mode = other.mode; return *this;}
            inline Node& operator=(Point&& pt) noexcept {swap(point, pt); return *this;}
            inline operator Point() const noexcept {return point;}
            inline operator Mode() const noexcept{return mode;}
        };
        
    
        vector<Node> m_points;
    public:
        
        //! Constructor.
        /** The function initialize an empty path.
         */
        inline Path() noexcept {};
        
        //! Constructor.
        /** The function initialize a path with another.
         @param path The other path.
         */
        inline Path(Path const& path) noexcept :
        m_points(path.m_points) {}
        
        //! Constructor.
        /** The function initialize a path with another.
         @param path The other path.
         */
        inline Path(Path&& path) noexcept
        {m_points.swap(path.m_points);}
        
        //! Constructor with a list of points.
        /** The function allocates the path with a list of points.
         @param The
         */
        Path(initializer_list<Point> il) noexcept;
        
        //! Constructor with a list of points.
        /** The function allocates the path with a list of points.
         @param The 
         */
        Path(const Mode mode, initializer_list<Point> il) noexcept;
        
        //! Destructor.
        /** The function deletes the path.
         */
        inline ~Path() noexcept {clear();}
        
        //! Retrieve the number of nodes of the path.
        /** The function retrieves the number of nodes of the path.
         @return The number of nodes of the path.
         */
        ulong size() const noexcept {return (ulong)m_points.size(); }
        
        //! Retrieve if the path is empty.
        /** The function retrieves if the path is empty.
         @return True if the path is empty, otherwise false.
         */
        bool empty() const noexcept {return m_points.empty();}
        
        //! Clear the path.
        /** The function clears a point to the path.
         */
        inline void clear() noexcept {m_points.clear();};
        
        //! Add a node to the path that won't be linked to the previous point.
        /** The function adds a node to the path that won't be linked to the previous node.
         @param point The point to add.
         */
        void moveTo(Point const& point) noexcept;
        
        //! Add a node to the path that will be linked to the previous point linearly.
        /** The function adds a node to the path that will be linked to the previous node linearly.
         @param point The point to add.
         */
        void lineTo(Point const& point) noexcept;
        
        //! Add a node to the path that will be linked to the previous node with a quadratic bezier curve.
        /** The function adds a node to the path that will be linked to the previous node with a quadratic bezier curve.
         @param control The control point.
         @param end     The end point.
         */
        void quadraticTo(Point const& control, Point const& end);
        
        //! Add a node to the path that will be linked to the previous node with a cubic bezier curve.
        /** The function adds a node to the path that will be linked to the previous node with a cubic bezier curve.
         @param control1 The first control point.
         @param control2 The seconf control point.
         @param end     The end point.
         */
        void cubicTo(Point const& control1, Point const& control2, Point const& end);
        
        //! Add a node to close the path.
        /** The function adds a node to close the path.
         */
        void close() noexcept;
        
        //! Retrieve the bounds of the path.
        /** The function retrieves the bounds of the path. The bounds rectangle is the smallest rectangle that contains all the points.
         @return The bounds of the path.
         */
        Rectangle bounds() const noexcept;
        
        //! Retrieve the smallest distance point with a point.
        /** The function retrieves the smallest distance point with a point.
         @param pt The point to compute.
         @return The distance with the point.
         */
        double distance(Point const& pt) const noexcept;
        
        //! Retrieve if a point is near the path.
        /** The function retrieves if a point is near the path.
         @param pt The point to compute.
         @param distance The distance of neighborhood (0 means over the line).
         @return true if the point is near, otherwise false.
         */
        bool near(Point const& pt, double const distance) const noexcept;
        
        bool overlaps(Rectangle const& rect) const noexcept;
        
        //! Set the position and the size with another rectangle.
        /** The function sets the position and the size with another rectangle.
         @param rect The other rectangle.
         @return The rectangle.
         *
        inline Path& operator=(Rectangle const& rect) noexcept
        {
            m_position = rect.position();
            m_size = rect.size();
            return *this;
        }
        
        //! Shift the rectangle with a point.
        ** The function shifts the rectangle with a point.
         @param pt The point.
         @return The rectangle.
         *
        inline Path& operator+=(Point const& pt) noexcept
        {
            m_position += pt;
            return *this;
        }*/
    };
}

#endif