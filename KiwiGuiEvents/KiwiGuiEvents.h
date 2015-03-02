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

#ifndef __DEF_KIWI_GUI_EVENTS__
#define __DEF_KIWI_GUI_EVENTS__

#include "KiwiWriter.h"

namespace Kiwi
{
    class Keyboarder;
    typedef shared_ptr<Keyboarder>          sKeyboarder;
    typedef weak_ptr<Keyboarder>            wKeyboarder;
    typedef shared_ptr<const Keyboarder>    scKeyboarder;
    typedef weak_ptr<const Keyboarder>      wcKeyboarder;
    
    class Mouser;
    typedef shared_ptr<Mouser>              sMouser;
    typedef weak_ptr<Mouser>				wMouser;
    typedef shared_ptr<const Mouser>        scMouser;
    typedef weak_ptr<const Mouser>			wcMouser;
    
    class Writer;
    typedef shared_ptr<Writer>              sWriter;
    typedef weak_ptr<Writer>				wWriter;
    typedef shared_ptr<const Writer>        scWriter;
    typedef weak_ptr<const Writer>			wcWriter;
}

#endif