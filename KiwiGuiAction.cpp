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

#include "KiwiGuiAction.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      ACTION                                      //
    // ================================================================================ //
    
    Action::Action(KeyboardEvent const& _event, string const& _name, string const& _description, string const& _category) noexcept :
    event(_event), name(_name), description(_description), category(_category)
    {
        ;
    }
    
    Action::Action(Action const& other) noexcept :
    event(other.event), name(other.name), description(other.description), category(other.category)
    {
        
    }
    
    Action::Action() noexcept :
    event(KeyboardEvent(' '))
    {
        
    }
    
    Action::~Action() noexcept
    {
        ;
    }
}