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

#include "KiwiMouser.h"

namespace Kiwi
{
	// ================================================================================ //
	//                                      MOUSER                                      //
	// ================================================================================ //
	
	Mouser::Mouser() noexcept
	{
		;
	}
	
	Mouser::~Mouser() noexcept
	{
		;
	}
	
	// ================================================================================ //
	//                                      EVENT                                       //
	// ================================================================================ //
	
	Mouser::Event::Event(const Type type, const int x, const int y, const ulong mod) noexcept :
	m_type(type), m_position(x, y), m_position_down(0., 0), m_wheel_offset(0., 0.), m_modifiers(mod), m_was_clicked(false), m_nclicks(0)
	{
		;
	}
	
	Mouser::Event::Event(const Type type, Point const& position, const ulong mod) noexcept :
	m_type(type), m_position(position), m_position_down(0., 0), m_wheel_offset(0., 0.), m_modifiers(mod), m_was_clicked(false), m_nclicks(0)
	{
		
	}
	
	Mouser::Event::Event(const Type type, const int x, const int y, const ulong mod, const double wheel_x, const double wheel_y, const bool was_clicked, const int down_x, const int down_y, const ulong nclicks) noexcept
	: m_type(type), m_position(x, y), m_position_down(down_x, down_y), m_wheel_offset(wheel_x, wheel_y), m_modifiers(mod), m_was_clicked(was_clicked), m_nclicks(nclicks)
	{
		;
	}
	
	Mouser::Event::Event(const Type type, Point const& position, const ulong mod, Point const& wheel, const bool was_clicked, Point const&down_position, const ulong nclicks) noexcept
	: m_type(type), m_position(position), m_position_down(down_position), m_wheel_offset(wheel), m_modifiers(mod), m_was_clicked(was_clicked), m_nclicks(nclicks)
	{
		;
	}
	
	Mouser::Event::~Event() noexcept
	{
		;
	}
}