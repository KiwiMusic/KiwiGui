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

#ifndef __DEF_KIWI_GUI_DOODLE__
#define __DEF_KIWI_GUI_DOODLE__

#include "Font.h"

namespace Kiwi
{
    namespace Gui
    {
        // ================================================================================ //
        //                                      DOODLE                                      //
        // ================================================================================ //
        
        //! The doodle is almost a full pure virtual class that should be override depending on the graphical implementation.
        /**
         The doodle...
         */
        class Doodle
        {
        public:
            
            //! Constructor.
            /** The function does nothing.
             */
            Doodle()
            {
                ;
            }
            
            //! Destrcutor.
            /** The function does nothing.
             */
            virtual ~Doodle()
            {
                ;
            }
            
            //! Retrieve the abscissa.
            /** The function retrieves the abscissa.
             @return The abscissa.
             */
            virtual inline double getX() = 0;
            
            //! Retrieve the ordinate.
            /** The function retrieves the ordinate.
             @return The ordinate.
             */
            virtual inline double getY() = 0;
            
            //! Retrieve the width.
            /** The function retrieves the width.
             @return The width.
             */
            virtual inline double getWidth() = 0;
            
            //! Retrieve the height.
            /** The function retrieves the height.
             @return The height.
             */
            virtual inline double getHeight() = 0;
            
            //! Retrieve the position.
            /** The function retrieves the position.
             @return The position.
             */
            virtual inline Point getPosition() = 0;
            
            //! Retrieve the size.
            /** The function retrieves the size.
             @return The size.
             */
            virtual inline Point getSize() = 0;
            
            //! Retrieve the bounds.
            /** The function retrieves the bounds.
             @return The bounds.
             */
            virtual inline Rectangle getBounds() = 0;
            
            //! Set the color.
            /** The function sets the color that now will be used by the doodle.
             @param color The color.
             */
            virtual void setColor(Color const& color) = 0;
			
            //! Set the font.
            /** The sets the font that now will be used by the doodle.
             @param font The font.
             */
            virtual void setFont(Font const& font) = 0;
            
            //! Fill the doodle with the current color.
            /** The function fills the entire doodle with the current color.
             */
            virtual void fillAll() = 0;
			
			//! Fill the doodle with a color.
			/** The function fills the entire doodle with a color.
			 */
			virtual void fillAll(Color const& color)
			{
				setColor(color);
				fillAll();
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
            virtual void drawText(string const& text, double x, double y, double w, double h, Kiwi::Gui::Font::Justification j, bool truncated = false) = 0;
            
            //! Draw a line of text within a rectangle.
            /** The function draws a line of text within a rectangle.
             @param text The text.
             @param rect The rectangle.
             @param j The justification.
             @param truncated If the text should be truncated if it goes out the boundaries.
             */
            virtual void drawText(string const& text, Rectangle const& rect, Font::Justification j, bool wrap = false);
			
			//! Tries to draw a text string inside a given rectangle.
			/** The function tries to draw a text string inside a given space.
			 If the text is too big, it'll be squashed horizontally or broken over multiple lines
			 if the maximumLinesToUse value allows this. If the text just won't fit into the space,
			 it'll cram as much as possible in there, and put some ellipsis at the end to show that
			 it's been truncated.
			 A Justification parameter lets you specify how the text is laid out within the rectangle,
			 both horizontally and vertically.
			 minimumHorizontalScale parameter specifies how much the text can be squashed horizontally
			 to try to squeeze it into the space. If you don't want any horizontal scaling to occur, you
			 can set this value to 1.0f.
			 @see drawText
			 */
			virtual void drawFittedText(string const& text, const double x, const double y, const double w, const double h, Font::Justification j, const long maximumNumberOfLines, const double minimumHorizontalScale) = 0;
			
			//! Tries to draw a text string inside a given rectangle.
			/** The function tries to draw a text string inside a given space.
			 @see drawFittedText
			 */
			virtual void drawFittedText(string const& text, Rectangle const& rect, Font::Justification j, const long maximumNumberOfLines, const double minimumHorizontalScale)
			{
				drawFittedText(text, rect.x(), rect.y(), rect.width(), rect.height(), j, maximumNumberOfLines, minimumHorizontalScale);
			}
			
			virtual void drawMultiLineText(wstring const& text, const long startX, const long baselineY, const long maximumLineWidth) const = 0;
            
            //! Fill a path.
            /** The function fills a path.
             @param path The path.
             */
            virtual void fillPath(Path const& path) = 0;
            
            //! Draw a path.
            /** The function draws a patcher.
             @param path The path.
             @param thickness The thickness of the parth.
             */
            virtual void drawPath(const Path& path, double const thickness) = 0;
            
            virtual inline void drawLine(double x1, double y1, double x2, double y2, double thickness) = 0;
            
            virtual inline void drawRectangle(double x, double y, double w, double h, double thickness, double rounded = 0.) = 0;
            
            virtual inline void drawRectangle(Rectangle const& rect, double thickness, double rounded = 0.)
            {
                drawRectangle(rect.x(), rect.y(), rect.width(), rect.height(), thickness, rounded);
            }
            
            virtual inline void fillRectangle(double x, double y, double w, double h, double rounded = 0.) = 0;
            
            virtual inline void fillRectangle(Rectangle const& rect, double rounded = 0.)
            {
                drawRectangle(rect.x(), rect.y(), rect.width(), rect.height(), rounded);
            }
            
            virtual inline void drawEllipse(double x, double y, double width, double height, double thickness = 0.) = 0;
            
            virtual inline void drawEllipse(Rectangle const& rect, double thickness = 0.)
            {
                drawEllipse(rect.x(), rect.y(), rect.width(), rect.height(), thickness);
            }
            
            virtual inline void fillEllipse(double x, double y, double width, double height) = 0;
            
            virtual inline void fillEllipse(Rectangle const& rect)
            {
                fillEllipse(rect.x(), rect.y(), rect.width(), rect.height());
            }
        };        
    }
}

#endif