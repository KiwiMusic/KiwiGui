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

#ifndef __DEF_KIWI_GUI_DEFINES__
#define __DEF_KIWI_GUI_DEFINES__

#include "../KiwiCore/KiwiCore.h"

namespace Kiwi
{
    class GuiModel;
    typedef shared_ptr<GuiModel>            sGuiModel;
    typedef weak_ptr<GuiModel>              wGuiModel;
    typedef shared_ptr<const GuiModel>      scGuiModel;
    typedef weak_ptr<const GuiModel>        wcGuiModel;
    
    class GuiKeyboarder;
    typedef shared_ptr<GuiKeyboarder>          sGuiKeyboarder;
    typedef weak_ptr<GuiKeyboarder>            wGuiKeyboarder;
    typedef shared_ptr<const GuiKeyboarder>    scGuiKeyboarder;
    typedef weak_ptr<const GuiKeyboarder>      wcGuiKeyboarder;
    
    class GuiMouser;
    typedef shared_ptr<GuiMouser>               sGuiMouser;
    typedef weak_ptr<GuiMouser>                 wGuiMouser;
    typedef shared_ptr<const GuiMouser>         scGuiMouser;
    typedef weak_ptr<const GuiMouser>			wcGuiMouser;
    
    class GuiActionManager;
    typedef shared_ptr<GuiActionManager>        sGuiActionManager;
    typedef weak_ptr<GuiActionManager>          wGuiActionManager;
    typedef shared_ptr<const GuiActionManager>  scGuiActionManager;
    typedef weak_ptr<const GuiActionManager>	wcGuiActionManager;
    
    class GuiController;
    typedef shared_ptr<GuiController>           sGuiController;
    typedef weak_ptr<GuiController>             wGuiController;
    typedef shared_ptr<const GuiController>     scGuiController;
    typedef weak_ptr<const GuiController>       wcGuiController;
    
    class GuiView;
    typedef shared_ptr<GuiView>                 sGuiView;
    typedef weak_ptr<GuiView>                   wGuiView;
    typedef shared_ptr<const GuiView>           scGuiView;
    typedef weak_ptr<const GuiView>             wcGuiView;
    
    class GuiContext;
    typedef shared_ptr<GuiContext>              sGuiContext;
    typedef weak_ptr<GuiContext>                wGuiContext;
    typedef shared_ptr<const GuiContext>        scGuiContext;
    typedef weak_ptr<const GuiContext>          wcGuiContext;
    
    class GuiDeviceManager;
    typedef shared_ptr<GuiDeviceManager>        sGuiDeviceManager;
    typedef weak_ptr<GuiDeviceManager>          wGuiDeviceManager;
    typedef shared_ptr<const GuiDeviceManager>  scGuiDeviceManager;
    typedef weak_ptr<const GuiDeviceManager>    wcGuiDeviceManager;
    
    class GuiTextEditor;
    typedef shared_ptr<GuiTextEditor>            sGuiTextEditor;
    typedef weak_ptr<GuiTextEditor>              wGuiTextEditor;
    typedef shared_ptr<const GuiTextEditor>      scGuiTextEditor;
    typedef weak_ptr<const GuiTextEditor>        wcGuiTextEditor;
}

#endif