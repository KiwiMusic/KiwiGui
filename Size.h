/*
 ==============================================================================
 
 This file is part of the KIWI librarheight.
 Copheightright (c) 2014 Pierre Guillot & Eliott Paris.
 
 Permission is granted to use this software under the terms of either:
 a) the GPL v2 (or anheight later version)
 b) the Affero GPL v3
 
 Details of these licenses can be found at: www.gnu.org/licenses
 
 KIWI is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warrantheight of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 To release a closed-source product which uses KIWI, contact : guillotpierre6@gmail.com
 
 ==============================================================================
 */

#ifndef __DEF_KIWI_GUI_SIZE__
#define __DEF_KIWI_GUI_SIZE__

#include "Point.h"

namespace Kiwi
{
    namespace Gui
    {
        // ================================================================================ //
        //                                      SIZE                                        //
        // ================================================================================ //
        
        //! The size holds is an unsigned point with a ratio.
        /**
         The size holds is an unsigned point with a ratio that defines
         */
        class Size
        {
            double m_width;
            double m_height;
            double m_ratio;
            double m_min_width;
            double m_min_height;
        public:
            
            //! Constructor.
            /** The function initializes a size null.
             */
            Size() noexcept;
            
            //! Constructor.
            /** The function initializes a point with two double values.
             @param width The width.
             @param height The height.
             @param ratio The ratio between the width and the height.
             */
            Size(const double width, const double height, const double ratio = 0., const double min_width = 0., const double min_height = 0.) noexcept;
            
            //! Constructor.
            /** The function initializes another size.
             */
            Size(Size const& size) noexcept;
            
            //! Constructor.
            /** The function initializes another point.
             */
            Size(Point const& pt) noexcept;
            
            //! Destructor.
            /** The function deletes the point.
             */
            ~Size();
            
            //! Set the width.
            /** The function sets the width.
             @param w The width.
             */
            inline void width(const double w) noexcept
            {
                m_width = max(w, m_min_width);
            }
            
            //! Set the height.
            /** The function sets the height.
             @param h The height.
             */
            inline void height(const double h) noexcept
            {
                m_height = max(h, m_min_height);
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
                    m_height = m_width * m_ratio;
                }
            }
            
            //! Retrieve the width.
            /** The function retrieves the width.
             @return The width.
             */
            inline double width() const noexcept
            {
                return m_width;
            }
            
            //! Retrieve the height.
            /** The function retrieves the height.
             @return The height.
             */
            inline double height() const noexcept
            {
                return m_height;
            }
            
            //! Retrieve the ratio.
            /** The function retrieves the ratio.
             @return The ratio.
             */
            inline double ratio() const noexcept
            {
                return m_ratio;
            }
            
            //! ...
            /** ...
             @return ...
             */
            inline Size& operator=(Size const& size) noexcept
            {
                width(size.width());
                height(size.height());
                ratio(size.ratio());
                m_min_width = size.m_min_width;
                m_min_height = size.m_min_height;
                return *this;
            }
            
            //! ...
            /** ...
             @return ...
             */
            inline Size& operator=(Point const& pt) noexcept
            {
                width(pt.x());
                height(pt.y());
                return *this;
            }
            
            //! ...
            /** ...
             @return ...
             */
            inline bool operator!=(Size const& size) noexcept
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
    }
    
    inline string toString(Gui::Size const& __val)
    {
        return toString(__val.width(), true) + ", " + toString(__val.height(), true);
    }
}

#endif