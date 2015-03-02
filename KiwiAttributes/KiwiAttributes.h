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

#include "KiwiAttrDefault.h"
#include "KiwiAttrGraphic.h"

namespace Kiwi
{
    typedef shared_ptr<Attr::Typed<BoolValue>>		sAttrBool;
    typedef shared_ptr<Attr::Typed<LongValue>>		sAttrLong;
	typedef shared_ptr<Attr::Typed<DoubleValue>>	sAttrDouble;
	typedef shared_ptr<Attr::Typed<StringValue>>	sAttrString;
    
    typedef shared_ptr<Attr::Typed<PointValue>>		sAttrPoint;
    typedef shared_ptr<Attr::Typed<SizeValue>>		sAttrSize;
    typedef shared_ptr<Attr::Typed<ColorValue>>  	sAttrColor;
    typedef SizeValue Size;
}

#endif


