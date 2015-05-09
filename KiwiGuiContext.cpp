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
        m_top_levels.clear();
    }
    
    sGuiView GuiContext::createView(sGuiController ctrl) const noexcept
    {
        sGuiView view;
        sGuiDeviceManager device = getDeviceManager();
        if(device)
        {
            view = device->createView(ctrl);
            if(view)
            {
                ctrl->m_view = view;
            }
            return view;
        }
        return sGuiView();
    }
    
    Point GuiContext::getMousePosition() const noexcept
    {
        sGuiDeviceManager device = getDeviceManager();
        if(device)
        {
            return device->getMousePosition();
        }
        else
        {
            return Point();
        }
    }
    
    Rectangle GuiContext::getScreenBounds(Point const& pt) const noexcept
    {
        sGuiDeviceManager device = getDeviceManager();
        if(device)
        {
            return device->getScreenBounds(pt);
        }
        else
        {
            return Rectangle();
        }
    }
    
    void GuiContext::addTopLevelModel(sGuiModel view) noexcept
    {
        if(view)
        {
            lock_guard<mutex> gard(m_mutex);
            m_top_levels.insert(view);
        }
    }
    
    void GuiContext::removeTopLevelModel(sGuiModel view) noexcept
    {
        if(view)
        {
            lock_guard<mutex> gard(m_mutex);
            m_top_levels.erase(view);
        }
    }
}
















