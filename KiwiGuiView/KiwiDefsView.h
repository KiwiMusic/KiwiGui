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

#ifndef __DEF_KIWI_VIEW_DEFS__
#define __DEF_KIWI_VIEW_DEFS__

#include "../KiwiGuiModels/KiwiGuiModels.h"

namespace Kiwi
{
    struct Knock;
    
    class PatcherView;
    typedef shared_ptr<PatcherView>         sPatcherView;
    typedef weak_ptr<PatcherView>           wPatcherView;
    typedef shared_ptr<const PatcherView>   scPatcherView;
    typedef weak_ptr<const PatcherView>     wcPatcherView;
    
    class LinkView;
    typedef shared_ptr<LinkView>         sLinkView;
    typedef weak_ptr<LinkView>           wLinkView;
    typedef shared_ptr<const LinkView>   scLinkView;
    typedef weak_ptr<const LinkView>     wcLinkView;
    
    class ObjectView;
    typedef shared_ptr<ObjectView>         sObjectView;
    typedef weak_ptr<ObjectView>           wObjectView;
    typedef shared_ptr<const ObjectView>   scObjectView;
    typedef weak_ptr<const ObjectView>     wcObjectView;
}

#endif


