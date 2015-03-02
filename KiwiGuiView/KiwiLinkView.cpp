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

#include "KiwiLinkView.h"
#include "KiwiPatcherView.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  LINK CONTROLER                                  //
    // ================================================================================ //
	
    LinkView::LinkView(sGuiLink link) noexcept :
    m_link(link)
    {
        ;
    }
    
    LinkView::~LinkView()
    {
        ;
    }
    
	void LinkView::setSelectedStatus(bool status)
	{
		if(m_selected != status)
		{
			m_selected = status;
			redraw();
		}
	}
    
    void LinkView::paint(sGuiLink link, Kiwi::Doodle& d, bool selected)
    {
        /*
        if(m_path.size() > 1)
        {
            const Kiwi::Point origin = link->getPosition() - 10.;
            Kiwi::Point current = m_path.getPoint(0) - origin;
            Kiwi::Path drawnpath(current);
            for(ulong i = 1; i < path.size(); i++)
            {
                const Kiwi::Point next = path.getPoint(i) - origin;
                const Kiwi::Point middle = Kiwi::Point::fromLine(current, next, 0.5);
                if(current.y() < next.y())
                {
                    const double height = (middle.y() - current.y()) * 0.5 + 5.;
                    drawnpath.quadraticTo(Kiwi::Point(current.x(), current.y() + height), middle);
                    drawnpath.quadraticTo(Kiwi::Point(next.x(), next.y() - height), next);
                }
                else if(current.y() - 20. < next.y())
                {
                    const double height = (current.y() - next.y()) * 0.5;
                    const double absi = (middle.x() - current.x()) * height * 0.05;
                    drawnpath.quadraticTo(Kiwi::Point(current.x() + absi, current.y() + height + 5.), middle);
                    drawnpath.quadraticTo(Kiwi::Point(next.x() - absi, next.y() - height - 5.), next);
                }
                else
                {
                    const double absi = (middle.x() - current.x()) * 0.5;
                    drawnpath.quadraticTo(Kiwi::Point(current.x() + absi, current.y() + 15.), middle);
                    drawnpath.quadraticTo(Kiwi::Point(next.x() - absi, next.y() - 15.), next);
                }
                
                current = next;
            }
            
            Kiwi::Color color;
            if(selected)
            {
                color = Kiwi::Color(0., 0.5, 0.75, 0.4);
            }
            else
            {
                color = link->getMessageColor();
            }
            
            d.setColor(color.darker(0.2));
            d.drawPath(drawnpath, 2.);
            d.setColor(color.brighter(0.15));
            d.drawPath(drawnpath, 1.);
        }
         */
    }

    bool LinkView::contains(Kiwi::Point const& point, Knock& knock) const noexcept
    {
        /*
        if(m_path.size() > 1)
        {
            Kiwi::Point current = path.getPoint(0);
            Kiwi::Path drawnpath(current);
            for(ulong i = 1; i < path.size(); i++)
            {
                const Kiwi::Point next = path.getPoint(i);
                const Kiwi::Point middle = Kiwi::Point::fromLine(current, next, 0.5);
                if(current.y() < next.y())
                {
                    const double height = (middle.y() - current.y()) * 0.5 + 5.;
                    drawnpath.quadraticTo(Kiwi::Point(current.x(), current.y() + height), middle);
                    drawnpath.quadraticTo(Kiwi::Point(next.x(), next.y() - height), next);
                }
                else if(current.y() - 20. < next.y())
                {
                    const double height = (current.y() - next.y()) * 0.5;
                    const double absi = (middle.x() - current.x()) * height * 0.05;
                    drawnpath.quadraticTo(Kiwi::Point(current.x() + absi, current.y() + height + 5.), middle);
                    drawnpath.quadraticTo(Kiwi::Point(next.x() - absi, next.y() - height - 5.), next);
                }
                else
                {
                    const double absi = (middle.x() - current.x()) * 0.5;
                    drawnpath.quadraticTo(Kiwi::Point(current.x() + absi, current.y() + 15.), middle);
                    drawnpath.quadraticTo(Kiwi::Point(next.x() - absi, next.y() - 15.), next);
                }
                
                current = next;
            }
            
            if(getBounds().expanded(10.).contains(point) && drawnpath.near(point, 2.5))
            {
                knock.link = getLink();
                knock.part = Knock::Inside;
                return true;
            }
		}
		*/
        knock.link.reset();
        knock.part = Knock::Outside;
        return false;
    }
    
    bool LinkView::overlaps(Kiwi::Rectangle const& rect) const noexcept
    {
        /*
        if(m_path.size() > 1)
        {
            Kiwi::Point current = path.getPoint(0);
            Kiwi::Path drawnpath(current);
            for(ulong i = 1; i < path.size(); i++)
            {
                const Kiwi::Point next = path.getPoint(i);
                const Kiwi::Point middle = Kiwi::Point::fromLine(current, next, 0.5);
                if(current.y() < next.y())
                {
                    const double height = (middle.y() - current.y()) * 0.5 + 5.;
                    drawnpath.quadraticTo(Kiwi::Point(current.x(), current.y() + height), middle);
                    drawnpath.quadraticTo(Kiwi::Point(next.x(), next.y() - height), next);
                }
                else if(current.y() - 20. < next.y())
                {
                    const double height = (current.y() - next.y()) * 0.5;
                    const double absi = (middle.x() - current.x()) * height * 0.05;
                    drawnpath.quadraticTo(Kiwi::Point(current.x() + absi, current.y() + height + 5.), middle);
                    drawnpath.quadraticTo(Kiwi::Point(next.x() - absi, next.y() - height - 5.), next);
                }
                else
                {
                    const double absi = (middle.x() - current.x()) * 0.5;
                    drawnpath.quadraticTo(Kiwi::Point(current.x() + absi, current.y() + 15.), middle);
                    drawnpath.quadraticTo(Kiwi::Point(next.x() - absi, next.y() - 15.), next);
                }
                
                current = next;
            }
            
            if(getBounds().expanded(10.).overlaps(rect) && drawnpath.overlaps(rect))
            {
                return true;
            }
		}*/
        return false;
    }
    
    LinkCreator::LinkCreator(const sGuiObject from, const unsigned outlet, const sGuiObject to, const unsigned inlet) noexcept :
    m_object_from(from), m_object_to(to), m_index_outlet(outlet), m_index_intlet(inlet)
    {
        /*
        if(from && outlet < from->getNumberOfOutlets() && to && inlet < to->getNumberOfInlets())
        {
            Object::sController from_ctrl   = from->getController();
            Object::sController to_ctrl     = to->getController();
            if(from_ctrl && to_ctrl)
            {
                m_path.moveTo(from_ctrl->getOutletPosition(outlet));
                m_path.lineTo(to_ctrl->getInletPosition(inlet));
            }
        }
        else if(from && outlet < from->getNumberOfOutlets())
        {
            Object::sController from_ctrl   = from->getController();
            if(from_ctrl)
            {
                m_path.moveTo(from_ctrl->getOutletPosition(outlet));
            }
        }
        else if(to && inlet < to->getNumberOfInlets())
        {
            Object::sController to_ctrl   = to->getController();
            if(to_ctrl)
            {
                m_path.moveTo(to_ctrl->getInletPosition(inlet));
            }
        }
         */
    }
    
    shared_ptr<LinkCreator> LinkCreator::create(const sGuiObject from, const unsigned outlet, const sGuiObject to, const unsigned inlet)
    {
        if((from && outlet < from->getNumberOfOutlets()) || (to && inlet < to->getNumberOfInlets()))
        {
            return make_shared<LinkCreator>(from, outlet, to, inlet);
        }
        else
        {
            return nullptr;
        }
    }
    
    LinkCreator::~LinkCreator()
    {
        
    }
}
















