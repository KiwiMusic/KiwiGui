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

#ifndef __DEF_KIWI_GUI_AFFINEMATRIX__
#define __DEF_KIWI_GUI_AFFINEMATRIX__

#include "../../KiwiCore/KiwiCore.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  AFFINE MATRIX                                   //
    // ================================================================================ //
    
    //! The color holds matrix values
    /**
     Represent an affine matrix suitable to do 2D graphical transformations such as translating, scaling, rotating, shearing or reflecting.
     */
    class AffineMatrix
    {
    private:
        double m_xx, m_xy, m_x0;
        double m_yx, m_yy, m_y0;
        
    public:
        //! Constructor.
        /** The function initializes an identity matrix.
         */
        constexpr inline AffineMatrix() noexcept :
            m_xx(1.), m_xy(0.), m_x0(0.),
            m_yx(0.), m_yy(1.), m_y0(0.) {}
        
        //! Constructor.
        /** The function initializes an affine matrix with another.
         */
        constexpr inline AffineMatrix(AffineMatrix const& other) noexcept :
            m_xx(other.m_xx), m_xy(other.m_xy), m_x0(other.m_x0),
            m_yx(other.m_yx), m_yy(other.m_yy), m_y0(other.m_y0) {}
        
        //! Constructor.
        /** The function initializes an affine matrix.
         @param xx The xx component of the affine transformation [0][0].
         @param xy The xy component of the affine transformation [0][1].
         @param x0 The X translation component of the affine transformation [0][2].
         @param yx The yx component of the affine transformation [1][0].
         @param yy The yy component of the affine transformation [1][1].
         @param y0 The Y translation component of the affine transformation [1][2].
         */
        constexpr inline AffineMatrix(const double xx, const double xy, const double x0,
                                      const double yx, const double yy, const double y0) noexcept :
            m_xx(xx), m_xy(xy), m_x0(x0),
            m_yx(yx), m_yy(yy), m_y0(y0) {}
        
        //! Reset the affine matrix to an identity matrix.
        /** The function reset the affine matrix to an identity matrix.
         */
        void reset() noexcept
        {
            *this = AffineMatrix();
        }
        
        bool isIdentity() const noexcept
        {
            return (m_xx == 1. && m_xy == 0. && m_x0 == 0 &&
                    m_yx == 0. && m_yy == 1. && m_y0 == 0.);
        }
        
        //! Apply this affine transformation matrix to a point.
        /** The function applies this affine transformation matrix to a point.
         */
        void applyTo(double& x, double& y) const noexcept
        {
            const double old_x = x;
            x = m_xx * old_x + m_xy * y + m_x0;
            y = m_yx * old_x + m_yy * y + m_y0;
        }
        
        //! Apply this affine transformation matrix to a point.
        /** The function applies this affine transformation matrix to a point.
         */
        template <typename PointType> void applyTo(PointType& pt) const noexcept
        {
            const double old_x = pt.x();
            pt.x(m_xx * old_x + m_xy * pt.y() + m_x0);
            pt.y(m_yx * old_x + m_yy * pt.y() + m_y0);
        }
        
        //! Apply this affine transformation matrix to a vector of points.
        /** The function applies this affine transformation matrix to a vector of points.
         */
        template <typename PointType> void applyTo(vector<PointType> const& points) const noexcept
        {
            for(auto pt : points)
            {
                const double old_x = pt.x();
                pt.x(m_xx * old_x + m_xy * pt.y() + m_x0);
                pt.y(m_yx * old_x + m_yy * pt.y() + m_y0);
            }
        }
        
        //! Sets the matrix with another.
        /** The function sets the matrix with another.
         @param other The other matrix.
         @return The affine matrix.
         */
        inline AffineMatrix& operator=(AffineMatrix const& other) noexcept
        {
            m_xx = other.m_xx; m_xy = other.m_xy; m_x0 = other.m_x0;
            m_yx = other.m_yx; m_yy = other.m_yy; m_y0 = other.m_y0;
            return *this;
        }
        
        //! Return true if this affine matrix is equal to another.
        /** The function returns true if this affine matrix is equal to another.
         @param other The other matrix.
         @return True if this affine matrix is equal to another, otherwise false.
         */
        bool operator==(AffineMatrix const& other) const noexcept
        {
            return (m_xx == other.m_xx && m_xy == other.m_xy && m_x0 == other.m_x0 &&
                    m_yx == other.m_yx && m_yy == other.m_yy && m_y0 == other.m_y0);
        }
        
        //! Return true if this affine matrix is not equal to another.
        /** The function returns true if this affine matrix is not equal to another.
         @param other The other matrix.
         @return True if this affine matrix is not equal to another, otherwise false.
         */
        bool operator!=(AffineMatrix const& other) const noexcept
        {
            return ! operator== (other);
        }
        
        //! Return an affine matrix that represent a translation.
        /** The function returns an affine matrix that represent a translation.
         @param x The abscissa translation value.
         @param y The ordinate translation value.
         @return An affine matrix.
         */
        static inline AffineMatrix translation(const double x, const double y) noexcept
        {
            return AffineMatrix(1., 0., x,
                                0., 1., y);
        }
        
        //! Return a new affine matrix that is a translated version of this one.
        /** The function returns a new affine matrix that is a translated version of this one.
         @param x The abscissa delta translation value.
         @param y The ordinate delta translation value.
         @return An affine matrix.
         */
        inline AffineMatrix translated(const double x, const double y) const noexcept
        {
            return AffineMatrix(m_xx, m_xy, m_x0 + x,
                                m_yx, m_yy, m_y0 + y);
        }
        
        //! Return a new affine matrix that is the same as this one but with new translation values.
        /** The function returns a new affine matrix that is the same as this one but with new translation values.
         @param x The new abscissa translation value.
         @param y The new ordinate translation value.
         @return An affine matrix.
         */
        inline AffineMatrix withTranslation(const double x, const double y) const noexcept
        {
            return AffineMatrix(m_xx, m_xy, x,
                                m_yx, m_yy, y);
        }
        
        //! Return an affine matrix that represent a scale transformation.
        /** The function returns an affine matrix that represent a scale transformation.
         @param x The abscissa scale value.
         @param y The ordinate scale value.
         @return An affine matrix.
         */
        static inline AffineMatrix scale(const double x, const double y) noexcept
        {
            return AffineMatrix(x, 0., 0.,
                                0., y, 0.);
        }
        
        //! Return a new affine matrix that is a re-scaled version of this one.
        /** The function returns a new affine matrix that is a re-scaled version of this one.
         @param x The abscissa scale value.
         @param y The ordinate scale value.
         @return An affine matrix.
         */
        inline AffineMatrix scaled(const double x, const double y) const noexcept
        {
            return AffineMatrix(m_xx * x, m_xy, m_x0,
                                m_yx, m_yy * y, m_y0);
        }
        
        //! Return an affine matrix that represent a rotation transformation.
        /** The function returns an affine matrix that represent an anti-clockwise rotation transformation, centred about the origin.
         @param radian The angle of the rotation in radian
         @return An affine matrix.
         */
        static inline AffineMatrix rotation(const double radian) noexcept
        {
            const double cosRad = cos(radian);
            const double sinRad = sin(radian);
            
            return AffineMatrix(cosRad,  sinRad, 0.,
                                -sinRad, cosRad, 0.);
        }
        
        //! Return a new affine matrix that is a rotated version of this one.
        /** The function returns a new affine matrix that is a rotated version of this one.
         @param radian The angle of the anti-clockwise rotation in radian
         @return An affine matrix.
         */
        inline AffineMatrix rotated(const double radian) const noexcept
        {
            const double cosRad = cos(radian);
            const double sinRad = sin(radian);
            
            return AffineMatrix(m_xx * cosRad - m_yx * sinRad, m_xy * cosRad - m_yy * sinRad, m_x0 * cosRad - m_y0 * sinRad,
                                m_xx * sinRad + m_yx * cosRad, m_xy * sinRad + m_yy * cosRad, m_x0 * sinRad + m_y0 * cosRad);
        }
        
        //! Return an affine matrix that represent a shear transformation.
        /** The function returns an affine matrix that represent a shear transformation.
         @param x The abscissa direction shear value.
         @param y The ordinate direction shear value.
         @return An affine matrix.
         */
        static inline AffineMatrix shear(const double x, const double y) noexcept
        {
            return AffineMatrix(1., x, 0.,
                                y , 1., 0.);
        }
        
        //! Return a new affine matrix that is a re-sheared version of this one.
        /** The function returns a new affine matrix that is a re-sheared version of this one.
         @param x The abscissa direction shear value.
         @param y The ordinate direction shear value.
         @return An affine matrix.
         */
        inline AffineMatrix sheared(const double x, const double y) const noexcept
        {
            return AffineMatrix(m_xx + x * m_yx, m_xy + x * m_yy, m_x0 + x * m_y0,
                                m_yx + y * m_xx, m_yy + y * m_xy, m_y0 + y * m_x0);
        }
        
        //! Return an affine matrix that represent a pixel to cartesian coordinate system transformation.
        /** The function returns an affine matrix that represent a pixel to cartesian coordinate system transformation.
         The resulting matrix can be used to tranform points from a top-left (0,0) origin system with a downward y direction
         to a centered cartesian system with upward y direction.
         @param width The width value.
         @param height The height value.
         @return An affine matrix.
         */
        static inline AffineMatrix pixelToCartesian(const double width, const double height) noexcept
        {
            return AffineMatrix(1., 0.,  width * 0.5,
                                0., -1., height * 0.5);
        }
        
        //! Return an affine matrix that represent a cartesian to pixel coordinate system transformation.
        /** The function returns an affine matrix that represent a cartesian to pixel coordinate system transformation.
         The resulting matrix can be used to tranform points from a centered origin cartesian coordinate system with upward y direction
         to a top-left origin system with a downward y direction.
         @param width The width value.
         @param height The height value.
         @return An affine matrix.
         */
        static inline AffineMatrix cartesianToPixel(const double width, const double height) noexcept
        {
            return AffineMatrix();
        }
    };
}

#endif