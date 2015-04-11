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

#include "KiwiGuiContext.h"
#include "KiwiGuiDevice.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI CONTEXT                                     //
    // ================================================================================ //
	
    GuiContext::GuiContext(sGuiDeviceManager device) noexcept :
    m_device(device)
    {
        ;
    }
    
    GuiContext::~GuiContext() noexcept
    {
        lock_guard<mutex> guard(m_mutex);
        m_windows.clear();
    }
    
    sGuiWindow GuiContext::createWindow() noexcept
    {
        sGuiDeviceManager device = getDeviceManager();
        if(device)
        {
            sGuiWindow window = device->createWindow();
            if(window)
            {
                lock_guard<mutex> guard(m_mutex);
                m_windows.insert(window);
            }
            return window;
        }
        return sGuiWindow();
    }
}
















