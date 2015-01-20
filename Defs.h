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

#ifndef __DEF_KIWI_GUI_DEFS__
#define __DEF_KIWI_GUI_DEFS__

#include <stdio.h>
#include <stdarg.h>
#include <cwchar>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <memory>
#include <cmath>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>
#include <set>
#include <unordered_set>
#include <deque>
#include <thread>

#ifdef __APPLE__
#include <Accelerate/Accelerate.h>
#endif

using namespace std;

#define _USE_MATH_DEFINES

#ifndef M_PI
#define M_E         2.71828182845904523536028747135266250   /* e              */
#define M_LOG2E     1.44269504088896340735992468100189214   /* log2(e)        */
#define M_LOG10E    0.434294481903251827651128918916605082  /* log10(e)       */
#define M_LN2       0.693147180559945309417232121458176568  /* loge(2)        */
#define M_LN10      2.30258509299404568401799145468436421   /* loge(10)       */
#define M_PI        3.14159265358979323846264338327950288   /* pi             */
#define M_PI_2      1.57079632679489661923132169163975144   /* pi/2           */
#define M_PI_4      0.785398163397448309615660845819875721  /* pi/4           */
#define M_1_PI      0.318309886183790671537767526745028724  /* 1/pi           */
#define M_2_PI      0.636619772367581343075535053490057448  /* 2/pi           */
#define M_2_SQRTPI  1.12837916709551257389615890312154517   /* 2/sqrt(pi)     */
#define M_SQRT2     1.41421356237309504880168872420969808   /* sqrt(2)        */
#define M_SQRT1_2   0.707106781186547524400844362104849039  /* 1/sqrt(2)      */
#endif

namespace Kiwi
{    
#ifndef ulong
    typedef unsigned long ulong;
#endif
    namespace Gui
    {
        template <typename Type> Type clip(const Type& n, const Type& lower, const Type& upper)
        {
            return max(lower, min(n, upper));
        }
        
        // Solve a 3rd degree equation, return the number of solution and the solution are in solution1, solution2 and solution3.
        template <typename Type> ulong solve(Type a, Type b, Type c, Type const d, Type &solution1, Type &solution2,  Type &solution3)
        {
            if(abs(a) > 0.)
            {
                Type z = a;
                a = b / z;
                b = c / z;
                c = d / z;
                
                Type p = b - a * a / 3.;
                Type q = a * (2. * a * a - 9. * b) / 27. + c;
                Type p3 = p * p * p;
                Type D = q * q + 4. * p3 / 27.;
                Type offset = -a / 3.;
                if(D == 0.)
                {
                    Type u;
                    if(q < 0.)
                    {
                        u = pow( -q / 2., 1. / 3.);
                    }
                    else
                    {
                        u = -pow( q / 2., 1. / 3.);
                    }
                    solution1 = 2. * u + offset;
                    solution2 = -u + offset;
                    return 2;
                }
                else if(D > 0.)
                {
                    z = sqrt(D);
                    Type u = ( -q + z) / 2.;
                    Type v = ( -q - z) / 2.;
                    u = (u >= 0.) ? pow(u, 1. / 3.) : - pow( -u, 1. / 3.);
                    v = (v >= 0.) ? pow(v, 1. / 3.) : - pow( -v, 1. / 3.);
                    solution1 = u + v + offset;
                    return 1;
                }
                else
                {
                    Type u = 2. * sqrt( -p / 3.);
                    Type v = acos(-sqrt( -27. / p3) * q / 2.) / 3.;
                    solution1 = u * cos(v) + offset;
                    solution2 = u * cos(v + 2. * M_PI / 3.) + offset;
                    solution3 = u * cos(v + 4. * M_PI / 3.) + offset;
                    return 3;
                }
            }
            else
            {
                a = b;
                b = c;
                c = d;
                if(abs(a) <= 0.)
                {
                    if(abs(b) <= 0.)
                    {
                        return 0;
                    }
                    else
                    {
                        solution1 = -c / b;
                        return 1;
                    }
                }
                
                Type D = b*b - 4.*a*c;
                if(D == 0)
                {
                    solution1 = -b / (2. * a);
                    return 1;
                }
                if(D > 0.)
                {
                    D = sqrt(D);
                    solution1 = ( -b - D) / (2. * a);
                    solution2 = ( -b + D) / (2. * a);
                    return 2;
                }
                else
                {
                    return 0;
                }
            }
        }
        
        inline string toString(int __val)
        {
            return to_string(__val);
        }
        
        inline string toString(unsigned __val)
        {
            return to_string(__val);
        }
        
        inline string toString(long __val)
        {
            return to_string(__val);
        }
        
        inline string toString(ulong __val)
        {
            return to_string(__val);
        }
        
        inline string toString(long long __val)
        {
            return to_string(__val);
        }
        
        inline string toString(ulong long __val)
        {
            return to_string(__val);
        }
        
        inline string toString(float __val)
        {
            return to_string(__val);
        }
        
        inline string toString(double __val, bool removeTrailingPoint = false)
        {
            size_t len = snprintf(0, 0, "%.10f", __val);
            string s(len+1, 0);
            // technically non-portable, see below
            snprintf(&s[0], len+1, "%.10f", __val);
            // remove nul terminator
            s.pop_back();
            // remove trailing zeros
            s.erase(s.find_last_not_of('0') + 1, string::npos);
            
            // remove trailing point
            if(removeTrailingPoint && s.back() == '.')
                s.pop_back();
            
            return s;
        }
        
        inline string toString(long double __val)
        {
            return to_string(__val);
        }
    }
};

#endif


