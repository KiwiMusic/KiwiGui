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

#include "KiwiSketcher.h"

namespace Kiwi
{
	// ================================================================================ //
	//                                      SKETCHER                                    //
	// ================================================================================ //
	
	Sketcher::Sketcher() noexcept :
	m_position(Attr::create("position", "Position", "Appearance", PointValue(0., 0.))),
	m_size(Attr::create(    "size",     "Size",     "Appearance", SizeValue(10., 10.)))
	{
		addAttr(m_position);
		addAttr(m_size);
	}
	
	Sketcher::~Sketcher()
	{
		;
	}
	
	void Sketcher::addListener(sListener listener)
	{
		if(listener)
		{
			lock_guard<mutex> guard(m_lists_mutex);
			m_lists.insert(listener);
		}
	}
	
	void Sketcher::removeListener(sListener listener)
	{
		if(listener)
		{
			lock_guard<mutex> guard(m_lists_mutex);
			m_lists.erase(listener);
		}
	}
	
	void Sketcher::redraw() noexcept
	{
		lock_guard<mutex> guard(m_lists_mutex);
		auto it = m_lists.begin();
		while(it != m_lists.end())
		{
			if((*it).expired())
			{
				it = m_lists.erase(it);
			}
			else
			{
				sListener listener = (*it).lock();
				listener->redraw();
				++it;
			}
		}
	}
	
	void Doodle::drawText(string const& text, Rectangle const& rect, Font::Justification j, bool wrap)
	{
		drawText(text, rect.x(), rect.y(), rect.width(), rect.height(), j, wrap);
	}
}