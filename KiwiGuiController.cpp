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

#include "KiwiGuiController.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      GUI CONTROLLER                              //
    // ================================================================================ //
	
    GuiController::GuiController(sGuiSketcher sketcher) noexcept :
    m_sketcher(sketcher),
    m_mouser(dynamic_pointer_cast<GuiMouser>(sketcher)),
    m_keyboarder(dynamic_pointer_cast<GuiKeyboarder>(sketcher)),
    m_want_mouse(bool(m_mouser)),
    m_want_keyboard(bool(m_keyboarder))
    {
        ;
    }
    
    GuiController::~GuiController() noexcept
    {
        ;
    }
    
    void GuiController::draw(Sketch& sketch)
    {
        m_sketcher->draw(shared_from_this(), sketch);
    }
    
    bool GuiController::receive(MouseEvent const& event)
    {
        if(m_mouser)
        {
            return m_mouser->receive(shared_from_this(), event);
        }
        return true;
    }
    
    bool GuiController::receive(KeyboardEvent const& event)
    {
        
    }
    
    bool GuiController::receive(KeyboardFocus const event)
    {
        
    }
    
     void redraw()
    {
        
    }
}
















