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
        
        struct Node
        {
            Point point;
            Mode  mode;
            
            Node(Point const& pt, Mode const mode) noexcept;
            Node(Point const& pt) noexcept;
            Node(Node const& other) noexcept;
            ~Node() noexcept;
            
            inline operator Point() const noexcept
            {
                return point;
            }
            
            inline operator Mode() const noexcept
            {
                return mode;
            }
            
        };
        
    private:
        vector<Node> m_points;
        
    public:
        
        //! Constructor.
        /** The function initialize an empty path.
         */
        Path() noexcept;
        
        //! Constructor.
        /** The function initialize a path with another.
         @param path The other path.
         */
        Path(Path const& path) noexcept;
        
        //! Constructor.
        /** The function initialize a path with a point.
         @param pt The first point of the path.
         */
        Path(Point const& pt) noexcept;
        
        //! Constructor.
        /** The function initialize a path with a rectangle.
         @param rect The rectangle.
         */
        Path(Rectangle const& rect) noexcept;
        
        //! Constructor.
        /** The function initialize a path with a line.
         @param start The starting position of the line.
         @param end The ending position of the line.
         */
        Path(Point const& start, Point const& end) noexcept;
        
        //! Constructor.
        /** The function initialize a path with a quadratic bezier line.
         @param start The starting position of the line.
         @param control The control point.
         @param end     The end point.
         */
        Path(Point const& start, Point const& ctrl, Point const& end) noexcept;
        
        //! Constructor.
        /** The function initialize a path with a cubic bezier line.
         @param start The starting position of the line.
         @param control1 The first control point.
         @param control2 The seconf control point.
         @param end     The end point.
         */
        Path(Point const& start, Point const& ctrl1, Point const& ctrl2, Point const& end) noexcept;
        
        //! Destructor.
        /** The function deletes the path.
         */
        ~Path() noexcept;
        
        //! Retrieve the number of nodes of the path.
        /** The function retrieves the number of nodes of the path.
         @return The number of nodes of the path.
         */
        ulong size() const noexcept
        {
            return (ulong)m_points.size();
        }
        
        //! Retrieve if the path is empty.
        /** The function retrieves if the path is empty.
         @return True if the path is empty, otherwise false.
         */
        bool empty() const noexcept
        {
            return m_points.empty();
        }
        
        //! Clear the path.
        /** The function clears a point to the path.
         */
        void clear() noexcept;
        
        //! Retrieve the node at a specific index.
        /** The function retrieves the node at a specific index.
         @param index The adress of the node.
         @return The node.
         */
        inline Node& operator[](ulong index)
        {
            return m_points[vector<Node>::size_type(index)];
        }
        
        //! Retrieve the node at a specific index.
        /** The function retrieves the node at a specific index.
         @param index The adress of the node.
         @return The node.
         */
        inline Node const& operator[](ulong index) const
        {
            return m_points[vector<Node>::size_type(index)];
        }
        
        //! Add a node to the path that won't be linked to the previous point.
        /** The function adds a node to the path that won't be linked to the previous node.
         @param point The point to add.
         */
        void move(Point const& point) noexcept;
        
        //! Add a node to the path that will be linked to the previous point linearly.
        /** The function adds a node to the path that will be linked to the previous node linearly.
         @param point The point to add.
         */
        void line(Point const& point) noexcept;
        
        //! Add a node to the path that will be linked to the previous node with a quadratic bezier curve.
        /** The function adds a node to the path that will be linked to the previous node with a quadratic bezier curve.
         @param control The control point.
         @param end     The end point.
         */
        void quadratic(Point const& control, Point const& end);
        
        //! Add a node to the path that will be linked to the previous node with a cubic bezier curve.
        /** The function adds a node to the path that will be linked to the previous node with a cubic bezier curve.
         @param control1 The first control point.
         @param control2 The seconf control point.
         @param end     The end point.
         */
        void cubic(Point const& control1, Point const& control2, Point const& end);
        
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