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

#ifndef __DEF_KIWI_GUI_SKETCH__
#define __DEF_KIWI_GUI_SKETCH__

#include "KiwiGraphics/KiwiGraphics.h"

namespace Kiwi
{
    
    // ================================================================================ //
    //                                      SKETCH                                      //
    // ================================================================================ //
    
    //! The sketch is an abstract class that must be overriden depending on the graphical implementation.
    /**
     The sketch...
     */
    class Sketch
    {
    private:
        const Rectangle m_bounds;
        Color           m_color;
        double          m_line_width;
        Font            m_font;
        Path::Joint     m_joint;
        Path::LineCap   m_linecap;
        AffineMatrix    m_matrix;
        bool            m_identity;
        
    public:
        //! Constructor.
        /** The function initializes a sketch.
         */
        Sketch(Rectangle const& bounds) noexcept : m_bounds(bounds), m_line_width(1.), m_joint(Path::Joint::Mitered), m_linecap(Path::LineCap::Butt), m_identity(true) {}
        
        //! Destrcutor.
        /** The function does nothing.
         */
        virtual ~Sketch() noexcept {}
        
    protected:
        typedef Path::Node Node;
        typedef enum Path::Mode Mode;
        
        //! Retrieve a constant reference of the nodes of a path.
        /** The function a constant reference of the nodes of a path.
         @param path The path.
         @return The vector of nodes.
         */
        inline vector<Node> const& getNodes(Path const& path) const noexcept
        {
            return path.m_nodes;
        }
        
        //! Draws a top-left justified text within a rectangle.
        /** The function draws a top-left justified text within a rectangle.
         @param text The text.
         @param x The abscissa of the rectangle.
         @param y The ordinate of the rectangle.
         @param w The width of the rectangle.
         @param h The height of the rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        virtual void internalDrawText(string const& text, double x, double y, double w, double h, Font const& font,
                                      Font::Justification j, bool truncated) const noexcept = 0;
        
        virtual void internalDrawText(wstring const& text, double x, double y, double w, double h, Font const& font,
                                      Font::Justification j, bool truncated) const noexcept
        {
            wstring_convert<codecvt_utf8<wchar_t>> cv;
            internalDrawText(cv.to_bytes(text), x, y, w, h, m_font, j, truncated);
        }
        
        //! Draws a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param x The abscissa of the rectangle.
         @param y The ordinate of the rectangle.
         @param w The width of the rectangle.
         @param h The height of the rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        virtual void internalDrawTextLine(string const& text, double x, double y, double w, double h, Font const& font,
                                          Font::Justification j, bool ellipses = false) const noexcept = 0;
        
        virtual void internalDrawTextLine(wstring const& text, double x, double y, double w, double h, Font const& font,
                                          Font::Justification j, bool ellipses = false) const noexcept
        {
            wstring_convert<codecvt_utf8<wchar_t>> cv;
            internalDrawTextLine(cv.to_bytes(text), x, y, w, h, m_font, j, ellipses);
        }
        
        //! Fill a path.
        /** The function fills a path.
         @param path The path.
         */
        virtual void internalFillPath(Path const& path, Color const& color) const noexcept = 0;
        
        //! Draw a path.
        /** The function draws a path.
         @param path        The path to draw.
         @param thickness   The line thickness of the path.
         @param joint       How must be drawn the joint between lines.
         @param linecap     How must be drawn the ends of lines.
         */
        virtual void internalDrawPath(Path const& path,
                                      double const thickness,
                                      const Path::Joint joint,
                                      const Path::LineCap linecap,
                                      Color const& color) const noexcept = 0;
        
    public:
        //! Set the transformation matrix.
        /** The function sets the transformation matrix.
         @param matrix The transformation matrix.
         */
        inline void setMatrix(AffineMatrix const& matrix) noexcept {m_matrix = matrix; m_identity = m_matrix.isIdentity();}
        
        //! Retrieve the transformation matrix.
        /** The function retrieves the transformation matrix.
         @param matrix The transformation matrix.
         */
        inline AffineMatrix getMatrix() const noexcept {return m_matrix;}
        
        //! Retrieve the position.
        /** The function retrieves the position.
         @return The position.
         */
        inline Point getPosition() const noexcept {return m_bounds.position();}
        
        //! Retrieve the size.
        /** The function retrieves the size.
         @return The size.
         */
        inline Size getSize() const noexcept {return m_bounds.size();}
        
        //! Retrieve the bounds.
        /** The function retrieves the bounds.
         @return The bounds.
         */
        inline Rectangle getBounds() const noexcept {return m_bounds;}
        
        //! Set the current color.
        /** The function sets the color that now will be used by the sketch.
         @param color The color.
         */
        inline void setColor(Color const& color) noexcept {m_color = color;}
        
        //! Retrieve the current color.
        /** The function retrieves the color that is currently be used by the sketch.
         @return The color.
         */
        inline Color getColor() const noexcept {return m_color;}
        
        //! Set the current font.
        /** The sets the font that now will be used by the sketch.
         @param font The font.
         */
        inline void setFont(Font const& font) noexcept {m_font = font;}
        
        //! Retrieve the current font.
        /** The function retrieves the font that is currently be used by the sketch.
         @return The font.
         */
        inline Font getFont() const noexcept {return m_font;}
        
        //! Set the current line width.
        /** The sets the line width that now will be used by the sketch.
         @param linewidth The line width.
         */
        inline void setLineWidth(const double linewidth) noexcept {m_line_width = linewidth;}
        
        //! Retrieve the current line width.
        /** The function retrieves the line width that is currently be used by the sketch.
         @return The line width.
         */
        inline double getLineWidth() const noexcept {return m_line_width;}
        
        //! Set the current line joint.
        /** The function sets the type of line joint that now will be used by the sketch.
         @param joint       How must be drawn the joint between lines.
         */
        inline void setLineJoint(Path::Joint const& linejoint) noexcept {m_joint = linejoint;}
        
        //! Retrieve the current line joint.
        /** The function retrieves type of line joint that is currently be used by the sketch.
         @return The line joint.
         */
        inline Path::Joint getLineJoint() const noexcept {return m_joint;}
        
        //! Set the current line cap.
        /** The sets the type of line cap that now will be used by the sketch.
         @param linecap     How must be drawn the ends of lines.
         */
        inline void setLineCap(Path::LineCap const& linecap) noexcept {m_linecap = linecap;}
        
        //! Retrieve the current line cap.
        /** The function retrieves type of line cap that is currently be used by the sketch.
         @return The line cap.
         */
        inline Path::LineCap getLineCap() const noexcept {return m_linecap;}
        
        //! Fill a path.
        /** The function fills a path.
         @param path The path.
         */
        void fillPath(Path const& path) const noexcept
        {
            internalFillPath(m_identity ? path : path.transformed(m_matrix), m_color);
        }
        
        //! Fill a path.
        /** The function fills a path.
         @param path The path.
         @param color The fill color.
         */
        void fillPath(Path const& path, Color const& color) const noexcept
        {
            internalFillPath(m_identity ? path : path.transformed(m_matrix), color);
        }
        
        //! Fill a path transformed by a matrix.
        /** The function fills a path with a transformed by a matrix.
         @param path The path.
         @param matrix The affine matrix.
         */
        void fillPath(Path const& path, AffineMatrix const& matrix) const noexcept
        {
            if (m_identity && matrix.isIdentity())
            {
                internalFillPath(path, m_color);
            }
            else if(matrix.isIdentity())
            {
                internalFillPath(path.transformed(m_matrix), m_color);
            }
            else
            {
                internalFillPath(path.transformed(m_matrix.composedWith(matrix)), m_color);
            }
        }
        
        //! Draw a path with the current sketch color, line width and style.
        /** The function draws a path with the current sketch color, line width and style
         @param path        The path to draw.
         */
        virtual void drawPath(Path const& path) const noexcept
        {
            internalDrawPath(m_identity ? path : path.transformed(m_matrix), m_line_width, m_joint, m_linecap, m_color);
        }
        
        //! Draw a path with a given line width.
        /** The function draws a path with a given line width.
         @param path        The path to draw.
         @param thickness   The line thickness of the path.
         */
        virtual void drawPath(Path const& path, double const thickness) const noexcept
        {
            internalDrawPath(m_identity ? path : path.transformed(m_matrix), thickness, m_joint, m_linecap, m_color);
        }
        
        //! Draw a path with a given color.
        /** The function draws a path with a given color.
         @param path        The path to draw.
         @param color       The color of the path.
         */
        virtual void drawPath(Path const& path, Color const& color) const noexcept
        {
            internalDrawPath(m_identity ? path : path.transformed(m_matrix), m_line_width, m_joint, m_linecap, color);
        }
        
        //! Draw a path transformed by a matrix.
        /** The function draws a path.
         @param path        The path to draw.
         @param matrix      The affine matrix to apply to path to transform it.
         */
        virtual void drawPath(Path const& path, AffineMatrix const& matrix) const noexcept
        {
            if (m_identity && matrix.isIdentity())
            {
                internalDrawPath(path, m_line_width, m_joint, m_linecap, m_color);
            }
            else if(matrix.isIdentity())
            {
                internalDrawPath(path.transformed(m_matrix), m_line_width, m_joint, m_linecap, m_color);
            }
            else
            {
                internalDrawPath(path.transformed(m_matrix.composedWith(matrix)), m_line_width, m_joint, m_linecap, m_color);
            }
        }
        
        //! Draw a path transformed by a matrix.
        /** The function draws a path.
         @param path        The path to draw.
         @param thickness   The line thickness of the path.
         @param color       The color of the path.
         @param matrix      The affine matrix to apply to the path to transform it.
         */
        virtual void drawPath(Path const& path, double const thickness, Color const& color, AffineMatrix const& matrix) const noexcept
        {
            if (m_identity && matrix.isIdentity())
            {
                internalDrawPath(path, thickness, m_joint, m_linecap, color);
            }
            else if(matrix.isIdentity())
            {
                internalDrawPath(path.transformed(m_matrix), thickness, m_joint, m_linecap, color);
            }
            else
            {
                internalDrawPath(path.transformed(m_matrix.composedWith(matrix)), thickness, m_joint, m_linecap, color);
            }
        }
        
        //! Fill the entire the sketch with the current color.
        /** The function fills the entire sketch with the current color.
         */
        inline void fillAll() noexcept
        {
            fillAll(m_color);
        }
        
        //! Fill the sketch with a color.
        /** The function fills the entire sketch with a color.
         */
        inline void fillAll(Color const& color) noexcept
        {
            Path p;
            p.addRectangle(getBounds());
            internalFillPath(p, color);
        }
        
        //! Draws a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param x The abscissa of the rectangle.
         @param y The ordinate of the rectangle.
         @param w The width of the rectangle.
         @param h The height of the rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        inline void drawText(string const& text, double x, double y, double w, double h, Font::Justification j, bool truncated = false) const noexcept
        {
            internalDrawText(text, x, y, w, h, m_font, j, truncated);
        }
        
        //! Draws a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param x The abscissa of the rectangle.
         @param y The ordinate of the rectangle.
         @param w The width of the rectangle.
         @param h The height of the rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        inline void drawText(string const& text, double x, double y, double w, double h, Font const& font, Font::Justification j, bool truncated = false) const noexcept
        {
            internalDrawText(text, x, y, w, h, font, j, truncated);
        }
        
        //! Draw a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param rect The rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        inline void drawText(wstring const& text, Rectangle const& rect, Font::Justification j, bool truncated = false) const
        {
            internalDrawText(text, rect.x(), rect.y(), rect.width(), rect.height(), m_font, j, truncated);
        }
        
        //! Draws a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param x The abscissa of the rectangle.
         @param y The ordinate of the rectangle.
         @param w The width of the rectangle.
         @param h The height of the rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        inline void drawText(wstring const& text, double x, double y, double w, double h, Font::Justification j, bool truncated = false) const
        {
            internalDrawText(text, x, y, w, h, m_font, j, truncated);
        }
        
        //! Draw a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param rect The rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        void drawText(string const& text, Rectangle const& rect, Font::Justification j, bool truncated = false) const noexcept
        {
            internalDrawText(text, rect.x(), rect.y(), rect.width(), rect.height(), m_font, j, truncated);
        }
        
        //! Draws a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param x The abscissa of the rectangle.
         @param y The ordinate of the rectangle.
         @param w The width of the rectangle.
         @param h The height of the rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        void drawTextLine(string const& text, double x, double y, double w, double h, Font::Justification j, bool ellipses = false) const noexcept
        {
            internalDrawTextLine(text, x, y, w, h, m_font, j, ellipses);
        }
        
        //! Draw a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param rect The rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        void drawTextLine(string const& text, Rectangle const& rect, Font::Justification j, bool ellipses = false) const noexcept
        {
            internalDrawTextLine(text, rect.x(), rect.y(), rect.width(), rect.height(), m_font, j, ellipses);
        }
        
        //! Draws a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param x The abscissa of the rectangle.
         @param y The ordinate of the rectangle.
         @param w The width of the rectangle.
         @param h The height of the rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        void drawTextLine(wstring const& text, double x, double y, double w, double h, Font::Justification j, bool ellipses = false) const noexcept
        {
            internalDrawTextLine(text, x, y, w, h, m_font, j, ellipses);
        }
        
        //! Draw a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param rect The rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        void drawTextLine(wstring const& text, Rectangle const& rect, Font::Justification j, bool ellipses = false) const noexcept
        {
            internalDrawTextLine(text, rect.x(), rect.y(), rect.width(), rect.height(), m_font, j, ellipses);
        }
        
        //! Draw a point.
        /** The function draws a point (a rectangle with a size of one)
         @param x    The abscissa of the point.
         @param y    The ordinate of the point.
         */
        inline void drawPoint(const double x, const double y) const noexcept
        {
            fillRectangle(x - 0.5, y - 0.5, 1, 1);
        }
        
        //! Draw a point.
        /** The function draws a point (a rectangle with a size of one)
         @param point    The position of the point.
         */
        inline void drawPoint(Point const& point) const noexcept
        {
            fillRectangle(Rectangle(point - 0.5, Size(1, 1)));
        }
        
        //! Draw a segment.
        /** The function draws a segment.
         @param segment The segment to draw.
         */
        inline void drawLine(Segment const& segment) const noexcept
        {
            drawPath(Path(segment));
        }
        
        //! Draw a segment.
        /** The function draws a segment.
         @param start The start point.
         @param end   The end point.
         */
        inline void drawLine(Point const& start, Point const& end) const noexcept
        {
            drawPath(Path::line(start, end));
        }
        
        //! Draw a segment.
        /** The function draws a segment.
         @param x1 The abscissa value of the start point.
         @param y1 The ordinate value of the start point.
         @param x2 The abscissa value of the end point.
         @param y2 The ordinate value of the end point.
         */
        inline void drawLine(double x1, double y1, double x2, double y2) const noexcept
        {
            drawPath(Path::line(Point(x1, y1), Point(x2, y2)));
        }
        
        //! Draw a rectangle, optionally rounded.
        /** The function draws a rectangle, optionally rounded.
         @param x The abscissa value of the rectangle's position point.
         @param y The ordinate value of the rectangle's position point.
         @param w The width of the rectangle.
         @param h The height of the rectangle.
         @param rounded The roundness of the corners.
         */
        void drawRectangle(double x, double y, double w, double h, double rounded = 0.) const noexcept
        {
            drawRectangle(Rectangle(x, y, w, h), rounded);
        }
        
        //! Draw a rectangle, optionally rounded.
        /** The function draws a rectangle, optionally rounded.
         @param rect    The rectangle to draw.
         @param rounded The roundness of the corners.
         */
        inline void drawRectangle(Rectangle const& rect, double rounded = 0.) const noexcept
        {
            Path p;
            if(rounded > 0.)
            {
                p.addRectangle(rect, rounded);
            }
            else
            {
                p.addRectangle(rect);
            }
            
            drawPath(p);
        }
        
        //! Fill a rectangle, optionally rounded.
        /** The function fills a rectangle, optionally rounded.
         @param x The abscissa value of the rectangle's position point.
         @param y The ordinate value of the rectangle's position point.
         @param w The width of the rectangle.
         @param h The height of the rectangle.
         @param rounded The roundness of the corners.
         */
        virtual void fillRectangle(double x, double y, double w, double h, double rounded = 0.) const noexcept
        {
            fillRectangle(Rectangle(x, y, w, h), rounded);
        }
        
        //! Fill a rectangle, optionally rounded.
        /** The function fills a rectangle, optionally rounded.
         @param rect    The rectangle to draw.
         @param rounded The roundness of the corners.
         */
        inline void fillRectangle(Rectangle const& rect, double rounded = 0.) const noexcept
        {
            Path p;
            if(rounded > 0.)
            {
                p.addRectangle(rect, rounded);
            }
            else
            {
                p.addRectangle(rect);
            }
            
            fillPath(p);
        }

        //! Draw an ellipse.
        /** The function draws an ellipse.
         @param center The ellipse's center point.
         @param rx The x radius.
         @param rx The y radius.
         */
        inline void drawEllipse(Point const& center, const double rx, const double ry) const noexcept
        {
            Path p;
            p.addEllipse(center, rx, ry);
            drawPath(p);
        }
        
        //! Draw an ellipse.
        /** The function draws an ellipse that fit in a rectangle.
         @param rect    The rectangle that must contains the ellipse.
         */
        inline void drawEllipse(Rectangle const& rect) const noexcept
        {
            Path p;
            p.addEllipse(rect);
            drawPath(p);
        }
        
        //! Fill an ellipse.
        /** The function fills an ellipse.
         @param center The ellipse's center point.
         @param rx The x radius.
         @param rx The y radius.
         */
        inline void fillEllipse(Point const& center, const double rx, const double ry) const noexcept
        {
            Path p;
            p.addEllipse(center, rx, ry);
            drawPath(p);
        }
        
        //! Fill an ellipse.
        /** The function fills an ellipse that fit in a rectangle.
         @param rect    The rectangle that must contains the ellipse.
         */
        void fillEllipse(Rectangle const& rect) const noexcept
        {
            Path p;
            p.addEllipse(rect);
            fillPath(p);
        }
    };
}

#endif