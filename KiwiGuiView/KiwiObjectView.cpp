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

#include "KiwiObjectView.h"
#include "KiwiPatcherView.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  BOX VIEW                                        //
    // ================================================================================ //
    
    ObjectView::ObjectView(sGuiObject object, sPatcherView patcherview)  noexcept :
    m_object(object),
    m_patcher_view(patcherview),
    m_selected(false)
    {
        ;
    }
    
    ObjectView::~ObjectView()
    {
        ;
    }
    
    string ObjectView::getText() const noexcept
    {
        sGuiObject object = getObject();
        if(object)
        {
            return object->getText();
        }
        
        return string();
    }
    
    Rectangle ObjectView::getBounds() const noexcept
    {
        sGuiObject object = getObject();
        if(object)
        {
            if(!getPatcherPresentationStatus())
            {
                return object->getBounds();
            }
            else
            {
                return object->getPresentationBounds();
            }
        }
        
        return Rectangle();
    }
    
    Rectangle ObjectView::getDisplayBounds() const noexcept
    {
        return getBounds();
    }
    
    Point ObjectView::getPosition() const noexcept
    {
        sGuiObject object = getObject();
        if(object)
        {
            if(!getPatcherPresentationStatus())
            {
                return object->getPosition();
            }
            else
            {
                return object->getPresentationPosition();
            }
        }
        
        return Point();
    }
    
    Point ObjectView::getDisplayPosition() const noexcept
    {
        return getPosition();
    }
    
    Point ObjectView::getSize() const noexcept
    {
        sGuiObject object = getObject();
        if(object)
        {
            if(!getPatcherPresentationStatus())
            {
                return object->getSize();
            }
            else
            {
                return object->getPresentationSize();
            }
        }
        
        return Point();
    }
    
    Point ObjectView::getDisplaySize() const noexcept
    {
        return getSize();
    }
    
    ulong ObjectView::getNumberOfInlets() const noexcept
    {
        sGuiObject object = getObject();
        if(object)
        {
            return object->getNumberOfInlets();
        }
        
        return 0;
    }
    
    ulong ObjectView::getNumberOfOutlets() const noexcept
    {
        sGuiObject object = getObject();
        if(object)
        {
            return object->getNumberOfOutlets();
        }
        
        return 0;
    }
    
    Point ObjectView::getIOSize() const noexcept
    {
        return Point(5, 3);
    }
    
    bool ObjectView::isHiddenOnLock() const noexcept
    {
        sGuiObject object = getObject();
        if(object)
        {
            return object->isHiddenOnLock();
        }
        
        return false;
    }
    
    bool ObjectView::isIncludeInPresentation() const noexcept
    {
        sGuiObject object = getObject();
        if(object)
        {
            return object->isIncludeInPresentation();
        }
        
        return false;
    }
    
    bool ObjectView::isSelected() const noexcept
    {
        return m_selected;
    }
    
    bool ObjectView::isVisible() const noexcept
    {
        return !(getPatcherLockStatus() && isHiddenOnLock()) || (getPatcherPresentationStatus() && !isIncludeInPresentation());
    }
    
    bool ObjectView::getPatcherLockStatus() const noexcept
    {
        sPatcherView patcherview = getPatcherView();
        if(patcherview)
        {
            return patcherview->getLockStatus();
        }
        return false;
    }
    
    bool ObjectView::getPatcherPresentationStatus() const noexcept
    {
        sPatcherView patcherview = getPatcherView();
        if(patcherview)
        {
            return patcherview->getPresentationStatus();
        }
        return false;
    }
    
    void ObjectView::setSelectedStatus(bool status)
    {
        if(isSelected() != status)
        {
            m_selected = status;
            patcherViewSelectionStatusChanged();
        }
    }
	
	void ObjectView::notify(sAttr attr)
	{
		const string attrName = attr->getName();
		
		if((attrName == "position" && !getPatcherPresentationStatus()) ||
		   (attrName == "presentation_position" && getPatcherPresentationStatus()))
		{
			positionChanged();
		}
		else if((attrName == "size" && !getPatcherPresentationStatus()) ||
				(attrName == "presentation_size" && getPatcherPresentationStatus()))
		{
			sizeChanged();
		}
		else if(attrName == "presentation")
		{
			presentationStatusChanged();
		}
	}
	
    Kiwi::Point ObjectView::getInletPosition(const ulong index) const noexcept
    {
		return getInletBounds(index).centre();
    }
    
    Kiwi::Point ObjectView::getOutletPosition(const ulong index) const noexcept
    {
		return getOutletBounds(index).centre();
    }
	
	Kiwi::Rectangle ObjectView::getInletBounds(const ulong index) const noexcept
	{
		const ulong ninlets = getNumberOfInlets();
		const Kiwi::Point ioSize = getIOSize();
		const Kiwi::Rectangle objectBounds = ObjectView::getBounds();
		
		if(ninlets >= index)
		{
			if(index == 1)
			{
				return Kiwi::Rectangle(objectBounds.x(), objectBounds.y(), ioSize.x(), ioSize.y());
			}
			else
			{
				const double offset = ((objectBounds.width() - ioSize.x()) / (double)(ninlets - 1)) * (index - 1);
				return Kiwi::Rectangle(objectBounds.x() + offset, objectBounds.y(), ioSize.x(), ioSize.y());
			}
		}
		
		return Kiwi::Rectangle();
	}
	
	Kiwi::Rectangle ObjectView::getOutletBounds(const ulong index) const noexcept
	{
		const ulong noutlets = getNumberOfOutlets();
		const Kiwi::Point ioSize = getIOSize();
		const Kiwi::Rectangle objectBounds = ObjectView::getBounds();
		
		if(noutlets >= index)
		{
			if(index == 1)
			{
				return Kiwi::Rectangle(objectBounds.x(), objectBounds.y() + objectBounds.height() - ioSize.y(), ioSize.x(), ioSize.y());
			}
			else
			{
				const double offset = ((objectBounds.width() - ioSize.x()) / (double)(noutlets - 1)) * (index - 1);
				return Kiwi::Rectangle(objectBounds.x() + offset, objectBounds.y() + objectBounds.height() - ioSize.y(), ioSize.x(), ioSize.y());
			}
		}
		
		return Kiwi::Rectangle();
	}
	
	ulong ObjectView::resizerKnock(Kiwi::Point const& pt) const noexcept
	{
		ulong borderFlag = Knock::BorderZone::None;
		if(isSelected())
		{
			const Kiwi::Point localPoint = pt - getDisplayPosition();
			if(localPoint.y() <= 2)
			{
				borderFlag |= Knock::BorderZone::Top;
			}
			if(localPoint.x() >= getDisplaySize().x() - 2)
			{
				borderFlag |= Knock::BorderZone::Right;
			}
			if(localPoint.y() >= getDisplaySize().y() - 2)
			{
				borderFlag |= Knock::BorderZone::Bottom;
			}
			if(localPoint.x() <= 2)
			{
				borderFlag |= Knock::BorderZone::Left;
			}
		}
		
		return borderFlag;
	}

    bool ObjectView::contains(Kiwi::Point const& pt, Knock& knock) const noexcept
    {
        if(isVisible() && getDisplayBounds().contains(pt))
        {
			ulong borderFlag = resizerKnock(pt);
			if(borderFlag != Knock::BorderZone::None)
            {
				knock.border  = borderFlag;
                knock.border &= ~Knock::None;
				knock.part	  = Knock::Border;
                knock.object     = const_pointer_cast<ObjectView>(shared_from_this());
                knock.target  = Knock::Object;
                return true;
            }
            else if(getBounds().contains(pt))
            {
				knock.target  = Knock::Object;
                knock.object     = const_pointer_cast<ObjectView>(shared_from_this());
                knock.part    = Knock::Inside;
                knock.index   = 0;
				
                if(!isSelected() && !getPatcherPresentationStatus() && !getPatcherLockStatus())
                {
					const ulong ninlets = getNumberOfInlets();
					const ulong noutlets= getNumberOfOutlets();
					const Kiwi::Point ioSize = getIOSize();
					
                    if(pt.y() < getPosition().y() + ioSize.y())
                    {
						for(ulong i = 1; i <= ninlets; i++)
						{
							if(getInletBounds(i).contains(pt))
							{
								knock.part    = Knock::Inlet;
								knock.index   = i;
							}
						}
                    }
                    else if(pt.y() > getPosition().y() + getSize().y() - ioSize.y())
                    {
						for(ulong i = 1; i <= noutlets; i++)
						{
							if(getOutletBounds(i).contains(pt))
							{
								knock.part    = Knock::Outlet;
								knock.index   = i;
							}
						}
                    }
					if(knock.part == Knock::Inlet || knock.part == Knock::Outlet)
					{
						knock.object     = const_pointer_cast<ObjectView>(shared_from_this());
						knock.target  = Knock::Object;
						return true;
					}
                }
                return true;
            }
        }
        return false;
    }
	
    bool ObjectView::overlaps(Kiwi::Rectangle const& rect) const noexcept
    {
        return getBounds().overlaps(rect);
    }
}

