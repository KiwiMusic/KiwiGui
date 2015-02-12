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

#ifndef __DEF_KIWI_GUI_ATTRIBUTES__
#define __DEF_KIWI_GUI_ATTRIBUTES__

#include "Default.h"
#include "Graphic.h"

namespace Kiwi
{
    typedef shared_ptr<Attr::Typed<BoolAttr>>  sAttrBool;
    typedef shared_ptr<Attr::Typed<Integer>>  sAttrInteger;
    
    typedef shared_ptr<Attr::Typed<PointAttr>>  sAttrPoint;
    typedef shared_ptr<Attr::Typed<SizeAttr>>   sAttrSize;
    typedef shared_ptr<Attr::Typed<ColorAttr>>  sAttrColor;
    typedef SizeAttr Size;
}

#endif


