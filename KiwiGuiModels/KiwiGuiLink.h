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

#ifndef __DEF_KIWI_GUI_LINK__
#define __DEF_KIWI_GUI_LINK__

#include "../KiwiGuiEvents/KiwiGuiEvents.h"

namespace Kiwi
{
    class GuiLink;
	typedef shared_ptr<GuiLink>                 sGuiLink;
	typedef weak_ptr<GuiLink>					wGuiLink;
	typedef shared_ptr<const GuiLink>           scGuiLink;
	typedef weak_ptr<const GuiLink>				wcGuiLink;
	
	class GuiObject;
	typedef shared_ptr<GuiObject>                  sGuiObject;
    typedef weak_ptr<GuiObject>                    wGuiObject;
	typedef shared_ptr<const GuiObject>            scGuiObject;
	typedef weak_ptr<const GuiObject>              wcGuiObject;
	
	class GuiPatcher;
	typedef shared_ptr<GuiPatcher>					sGuiPatcher;
	typedef weak_ptr<GuiPatcher>                   wGuiPatcher;
	typedef shared_ptr<const GuiPatcher>           scGuiPatcher;
	typedef weak_ptr<const GuiPatcher>				wcGuiPatcher;
	
	class GuiPatcherManager;
	typedef shared_ptr<GuiPatcherManager>          sGuiPatcherManager;
	typedef weak_ptr<GuiPatcherManager>			wGuiPatcherManager;
	typedef shared_ptr<const GuiPatcherManager>	scGuiPatcherManager;
	typedef weak_ptr<const GuiPatcherManager>		wcGuiPatcherManager;
	
	class GuiDeviceManager;
	typedef shared_ptr<GuiDeviceManager>        sGuiDeviceManager;
	typedef weak_ptr<GuiDeviceManager>          wGuiDeviceManager;
	typedef shared_ptr<const GuiDeviceManager>  scGuiDeviceManager;
	typedef weak_ptr<const GuiDeviceManager>    wcGuiDeviceManager;
	
    //! The gui link....
    /**
     The gui link
     */
    class GuiLink : public inheritable_enable_shared_from_this<GuiLink>
    {
    public:
		
    };
}

#endif


