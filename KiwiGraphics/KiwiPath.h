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
    //protected:
    public:
        //! @internal
        enum Mode
        {
            Move        = 0,
            Linear      = 1,
            Quadratic   = 2,
            Cubic       = 3
        };
        
        //! @internal
        class Node
        {
        private:
            double data[2];
            Mode   m;
        public:
            constexpr inline Node() noexcept : data{0., 0.}, m(Linear) {};
            constexpr inline Node(Point const& pt, Mode const _m = Linear) noexcept : data{pt.m_data[0], pt.m_data[1]}, m(_m) {};
            constexpr inline Node(Node const& other) noexcept : data{other.data[0], other.data[1]}, m(other.m) {};
            inline Node(Point&& pt, Mode const _m = Linear) noexcept : m(_m) {swap(data, pt.m_data);};
            inline Node(Node&& other) noexcept : m(other.m) {swap(data, other.data);};
            inline ~Node() noexcept {};
            inline Node& operator=(Point const& pt) noexcept {memcpy(data, pt.m_data, sizeof(double)*2); return *this;}
            inline Node& operator=(Node const& other) noexcept {memcpy(data, other.data, sizeof(double)*2); m = other.m; return *this;}
            inline Node& operator=(Point&& pt) noexcept {swap(data, pt.m_data); return *this;}
            inline Node& operator=(Node&& other) noexcept {swap(data, other.data); m = other.m; return *this;}
            inline Point point() const noexcept {return Point(data[0], data[1]);}
            inline Mode mode() const noexcept{return m;}
        };
        
    private:
        vector<Node> m_nodes;
        Rectangle    m_bounds;
    public:
        
        Node getNode(ulong index) const noexcept
        {
            if(m_nodes.size() > index)
            {
                return m_nodes[index];
            }
            return Node();
        }
        
        //! Constructor.
        /** The function initializes an empty path.
         */
        inline Path() noexcept {};
        
        //! Constructor.
        /** The function initializes a path with another.
         @param path The other path.
         */
        inline Path(Path const& path) noexcept :
        m_nodes(path.m_nodes), m_bounds(path.m_bounds) {}
        
        //! Constructor.
        /** The function initializes a path with another.
         @param path The other path.
         */
        inline Path(Path&& path) noexcept
        {m_nodes.swap(path.m_nodes); swap(m_bounds, path.m_bounds);}
        
        //! Constructor.
        /** The function initializes a path with a first point.
         @param path The other path.
         */
        inline Path(Point const& pt) noexcept {addNode(Node(pt, Move));}
        
        //! Constructor.
        /** The function initializes a path with a first point.
         @param path The other path.
         */
        inline Path(Point&& pt) noexcept {addNode(Node(forward<Point>(pt), Move));}
        
        //! Linear constructor.
        /** The function initializes a path with a line.
         @param start The first point of the line.
         @param end   The end point of the line.
         */
        inline static Path linear(Point const& start, Point const& end)
        {
            Path path(start);
            path.addNode(Node(end, Linear));
            return path;
        }
        
        //! Linear constructor.
        /** The function initializes a path with a line.
         @param start The first point of the line.
         @param end   The end point of the line.
         */
        inline static Path linear(Point&& start, Point&& end)
        {
            Path path(forward<Point>(start));
            path.addNode(Node(forward<Point>(end), Linear));
            return path;
        }
        
        //! Linear constructor.
        /** The function initializes a path with a set of lines. The number of points must be superior or equal to 2.
         @param il The set of points.
         */
        inline static Path linear(initializer_list<Point> il)
        {
            assert(il.size() < 2 && "The number of points must be superior or equal to 2 to create lines.");
            auto it = il.begin();
            Path path(*it++);
            path.addNodes(il.size() - 1, it, il.end(), Linear);
            return path;
        }
        
        //! Quadratic constructor.
        /** The function initializes a path with a quadratic bezier curve.
         @param start The first point of the curve.
         @param control The control point curve.
         @param end   The end point of the curve.
         */
        inline static Path quadratic(Point const& start, Point const& control, Point const& end)
        {
            Path path(start);
            path.addNode(Node(control, Quadratic));
            path.addNode(Node(end, Quadratic));
            return path;
        }
        
        //! Quadratic constructor.
        /** The function initializes a path with a quadratic bezier curve.
         @param start The first point of the curve.
         @param control The control point curve.
         @param end   The end point of the curve.
         */
        inline static Path quadratic(Point&& start, Point&& control, Point&& end)
        {
            Path path(forward<Point>(start));
            path.addNode(Node(forward<Point>(control), Quadratic));
            path.addNode(Node(forward<Point>(end), Quadratic));
            return path;
        }
        
        //! Quadratic constructor.
        /** The function initializes a path with a set of quadratic bezier curves. The number of points must be odd and superior or equal to 3.
         @param il The set of points.
         */
        inline static Path quadratic(initializer_list<Point> il)
        {
            assert(il.size() < 3 && "The number of points must be superior or equal to 3 to create quadratic bezier curves.");
            assert((il.size() % 3) != 1 && "The number of points must be odd to create quadratic bezier curves.");
            auto it = il.begin();
            Path path(*it++);
            path.addNodes(il.size() - 1, it, il.end(), Quadratic);
            return path;
        }
        
        //! Cubic constructor.
        /** The function initializes a path with a cubic bezier curve.
         @param start The first point of the curve.
         @param control1 The first control point curve.
         @param control2 The second control point curve.
         @param end   The end point of the curve.
         */
        inline static Path cubic(Point const& start, Point const& control1, Point const& control2, Point const& end)
        {
            Path path(start);
            path.addNode(Node(control1, Cubic));
            path.addNode(Node(control2, Cubic));
            path.addNode(Node(end, Cubic));
            return path;
        }
        
        //! Cubic constructor.
        /** The function initializes a path with a cubic bezier curve.
         @param start The first point of the curve.
         @param control1 The first control point curve.
         @param control2 The second control point curve.
         @param end   The end point of the curve.
         */
        inline static Path cubic(Point&& start, Point&& control1, Point&& control2, Point&& end)
        {
            Path path(forward<Point>(start));
            path.addNode(Node(forward<Point>(control1), Cubic));
            path.addNode(Node(forward<Point>(control2), Cubic));
            path.addNode(Node(forward<Point>(end), Cubic));
            return path;
        }
        
        //! Cubic constructor.
        /** The function initializes a path with a set of cubic bezier curves. The number of points must be a multiple of 3 + 1 and superior or equal to 4.
         @param il The set of points.
         */
        inline static Path cubic(initializer_list<Point> il)
        {
            assert(il.size() < 3 && "The number of points must be superior or equal to 4 to create cubic bezier curves.");
            assert(!((il.size() - 1) % 3) && "The number of points must be a multiple of 3 + 1 to create cubic bezier curves.");
            auto it = il.begin();
            Path path(*it++);
            path.addNodes(il.size() - 1, it, il.end(), Cubic);
            return path;
        }
        
        //! Sets the path with another path.
        /** The function the path with another path.
         @param other The other path.
         @return The path.
         */
        inline Path& operator=(Path const& other) noexcept
        {
            m_nodes = other.m_nodes;
            m_bounds = other.m_bounds;
            return *this;
        }
        
        //! Sets the path with another path.
        /** The function the path with another path.
         @param other The other path.
         @return The path.
         */
        inline Path& operator=(Path&& other) noexcept
        {
            swap(m_nodes, other.m_nodes);
            swap(m_bounds, other.m_bounds);
            return *this;
        }
        
        //! Destructor.
        /** The function deletes the path.
         */
        inline ~Path() noexcept {clear();}
        
        //! Retrieves the number of nodes of the path.
        /** The function retrieves the number of nodes of the path.
         @return The number of nodes of the path.
         */
        inline ulong size() const noexcept {return (ulong)m_nodes.size(); }
        
        //! Retrieves if the path is empty.
        /** The function retrieves if the path is empty.
         @return True if the path is empty, otherwise false.
         */
        inline bool empty() const noexcept {return m_nodes.empty();}
        
        //! Clears the path.
        /** The function clears a point to the path.
         */
        inline void clear() noexcept {m_nodes.clear();};
        
        //! Retrieves the bounds of the path.
        /** The function retrieves the bounds of the path. The bounds rectangle is the smallest rectangle that contains all the points.
         @return The bounds of the path.
         */
        inline Rectangle bounds() const noexcept {return m_bounds;};
        
        //! Adds a new point to the path not linked with the previous one.
        /** The function adds a new point to the path that won't be linked to the previous node.
         @param point The point to add.
         */
        inline void addMove(Point const& point) noexcept
        {
            addNode(Node(point, Move));
        }
        
        //! Adds a new point to the path not linked with the previous one.
        /** The function adds a new point to the path that won't be linked to the previous node.
         @param point The point to add.
         */
        inline void addMove(Point&& point) noexcept
        {
            addNode(Node(forward<Point>(point), Move));
        }
        
        //! Adds a the point that will be linked to the previous point linearly.
        /** The function adds a point to the path that will be linked to the previous node linearly.
         @param point The point to add.
         */
        inline void addLinear(Point const& point) noexcept
        {
            addNode(Node(point, Linear));
        }
        
        //! Adds a point that will be linked to the previous point linearly.
        /** The function adds a point to the path that will be linked to the previous node linearly.
         @param point The point to add.
         */
        inline void addLinear(Point&& point) noexcept
        {
            addNode(Node(forward<Point>(point), Linear));
        }
        
        //! Add a set of points to that will be linked linearly.
        /** The function adds a set of points to that will be linked linearly.
         @param il The set of points.
         */
        inline void addLinear(initializer_list<Point> il) noexcept
        {
            addNodes(il, Linear);
        }
        
        //! Adds a quadratic bezier curve to the path.
        /** The function adds a quadratic bezier curve to the path.
         @param control The control point.
         @param end     The end point.
         */
        inline void addQuadratic(Point const& control, Point const& end) noexcept
        {
            addNode(Node(control, Quadratic));
            addNode(Node(end, Quadratic));
        }
        
        //! Adds a quadratic bezier curve to the path.
        /** The function adds a quadratic bezier curve to the path.
         @param control The control point.
         @param end     The end point.
         */
        inline void addQuadratic(Point&& control, Point&& end) noexcept
        {
            addNode(Node(forward<Point>(control), Quadratic));
            addNode(Node(forward<Point>(end), Quadratic));
        }
        
        //! Add a set of quadratic bezier curves to the path.
        /** The function adds a set of quadratic bezier curves to the path. The number of point must be even, the first point of each pair defines the control point and the second point of each pair defines the end point.
         @param il The set of points that represent the quadratic bezier curves.
         */
        inline void addQuadratic(initializer_list<Point> il) noexcept
        {
            assert(!(il.size() % 2) && "Quadractic bezier curve must have an even number of points.");
            addNodes(il, Quadratic);
        }
        
        //! Adds a cubic bezier curve to the path.
        /** The function adds a cubic bezier curve to the path.
         @param control1 The first control point.
         @param control2 The seconf control point.
         @param end     The end point.
         */
        inline void addCubic(Point const& control1, Point const& control2, Point const& end) noexcept
        {
            addNode(Node(control1, Cubic));
            addNode(Node(control2, Cubic));
            addNode(Node(end, Cubic));
        }
        
        //! Adds a cubic bezier curve to the path.
        /** The function adds a cubic bezier curve to the path.
         @param control1 The first control point.
         @param control2 The seconf control point.
         @param end     The end point.
         */
        inline void addCubic(Point&& control1, Point&& control2, Point&& end) noexcept
        {
            addNode(Node(forward<Point>(control1), Cubic));
            addNode(Node(forward<Point>(control2), Cubic));
            addNode(Node(forward<Point>(end), Cubic));
        }
        
        //! Add a set of quadratic bezier curves to the path.
        /** The function adds a set of quadratic bezier curves to the path. The number of point must be a multiple of 3, the first point of each set defines the first control point, the second point defines the second control point and the third point defines the end point.
         @param il The set of points that represent the quadratic bezier curves.
         */
        inline void addCubic(initializer_list<Point> il) noexcept
        {
            assert(!(il.size() % 3) && "Cubic bezier curve must have a number of points multiple of 3.");
            addNodes(il, Cubic);
        }
        
        //! Add rectangle to the path.
        /** The function adds rectangle to the path.
         @param rect The rectangle.
         */
        inline void addRectangle(Rectangle const& rect) noexcept
        {
            addNode(Node(rect.position(), Move));
            addNode(Node(Point(rect.right(), rect.y()), Linear));
            addNode(Node(Point(rect.right(), rect.bottom()), Linear));
            addNode(Node(Point(rect.x(), rect.bottom()), Linear));
            addNode(Node(rect.position(), Linear));
        }
        
        //! Add a node to close the path.
        /** The function adds a node to close the path.
         */
        inline void close() noexcept
        {
            assert(empty() && "The path must not be empty to be closed.");
            addNode(Node(m_nodes[0].point(), Linear));
        }
        
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
        
    private:
        
        //@internal
        inline void rebound(Node const& newnode) noexcept
        {
            if(m_nodes.size() > 1)
            {
                const Point pt = newnode.point();
                if(pt.x() < m_bounds.x()) m_bounds.left(pt.x());
                else if(pt.x() > m_bounds.right()) m_bounds.right(pt.x());
                if(pt.y() < m_bounds.y()) m_bounds.top(pt.y());
                else if(pt.y() > m_bounds.bottom()) m_bounds.bottom(pt.y());
            }
            else
            {
                m_bounds.position(m_nodes[0].point());
            }
        }
        
        //@internal
        inline void resize(const vector<Node>::size_type size) noexcept
        {
            m_nodes.resize(size);
        }
        
        //@internal
        inline void addNodes(initializer_list<Point> il, Mode mode) noexcept
        {
            vector<Node>::size_type size = m_nodes.size();
            resize(size + il.size());
            for(auto it = il.begin(); it != il.end(); ++it){
                addNode(size++, Node((*it), mode));
            }
        }
        
        //@internal
        inline void addNodes(const vector<Node>::size_type s, const Point* begin, const Point* end, Mode mode) noexcept
        {
            vector<Node>::size_type size = m_nodes.size();
            resize(size + s);
            for(auto it = begin; it != end; ++it){
                addNode(size++, Node((*it), mode));
            }
        }
        
        //@internal
        inline void addNode(Node const& node) noexcept
        {
            m_nodes.push_back(node);
            rebound(node);
        }
        
        //@internal
        inline void addNode(Node&& node) noexcept
        {
            m_nodes.push_back(forward<Node>(node));
            rebound(m_nodes[m_nodes.size() - 1]);
        }
        
        //@internal
        inline void addNode(const vector<Node>::size_type pos, Node const& node) noexcept
        {
            m_nodes[pos] = node;
            rebound(node);
        }
        
        //@internal
        inline void addNode(const vector<Node>::size_type pos, Node&& node) noexcept
        {
            m_nodes[pos] = forward<Node>(node);
            rebound(m_nodes[pos]);
        }
    };
}

#endif