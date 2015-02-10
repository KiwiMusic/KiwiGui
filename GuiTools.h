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

#ifndef __DEF_KIWI_GUI_TOOLS__
#define __DEF_KIWI_GUI_TOOLS__

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
#include <list>
#include <set>
#include <deque>
#include <thread>
#include <typeinfo>
#include <typeindex>

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
    
    inline string trimDecimal(string& text)
    {
        string::size_type pos = text.find('.');
        if(pos != string::npos)
        {
            string::size_type size = text.size();
            while(size > pos && text[size - 1] == '0')
            {
                text.pop_back();
                size--;
            }
            if(text[size - 1] == '.')
            {
                text.pop_back();
            }
        }
        return text;
    }
    
    inline string toString(bool __val)
    {
        if(__val)
        {
            return "true";
        }
        else
        {
            return "false";
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
    
    inline string toString(unsigned long long __val)
    {
        return to_string(__val);
    }
    
    inline string toString(float __val, bool trim = false)
    {
        if(trim)
        {
            string text = to_string(__val);
            return trimDecimal(text);
        }
        else
        {
            return to_string(__val);
        }
    }
    
    inline string toString(double __val, bool trim = false)
    {
        if(trim)
        {
            string text = to_string(__val);
            return trimDecimal(text);
        }
        else
        {
            return to_string(__val);
        }
    }
    
    inline string toString(long double __val, bool trim = false)
    {
        if(trim)
        {
            string text = to_string(__val);
            return trimDecimal(text);
        }
        else
        {
            return to_string(__val);
        }
    }
    
    namespace Gui
    {
        class Sketcher;
        typedef shared_ptr<Sketcher>          sSketcher;
        typedef weak_ptr<Sketcher>            wSketcher;
        typedef shared_ptr<const Sketcher>    scSketcher;
        typedef weak_ptr<const Sketcher>      wcSketcher;
        
        class Mouser;
        typedef shared_ptr<Mouser>          sMouser;
        typedef weak_ptr<Mouser>            wMouser;
        typedef shared_ptr<const Mouser>    scMouser;
        typedef weak_ptr<const Mouser>      wcMouser;
        
        class Keyboarder;
        typedef shared_ptr<Keyboarder>          sKeyboarder;
        typedef weak_ptr<Keyboarder>            wKeyboarder;
        typedef shared_ptr<const Keyboarder>    scKeyboarder;
        typedef weak_ptr<const Keyboarder>      wcKeyboarder;
        
        template <typename Type> Type clip(const Type& n, const Type& lower, const Type& upper)
        {
            return max(lower, min(n, upper));
        }
    }
    
};

#endif


