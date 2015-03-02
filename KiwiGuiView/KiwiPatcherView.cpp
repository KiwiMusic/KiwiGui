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

#include "KiwiPatcherView.h"
#include "KiwiObjectView.h"
#include "KiwiLinkView.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  PAGE VIEW                                       //
    // ================================================================================ //
    
    PatcherView::PatcherView(const sGuiPatcher patcher) noexcept :
    m_patcher(patcher),
	m_zoom(100),
	m_locked(false),
	m_presentation(false),
	m_display_grid(true),
	m_snap_to_grid(false)
    {
        
    }
    
    PatcherView::~PatcherView()
    {
		m_objects_selected.clear();
		m_links_selected.clear();
		
        m_objects.clear();
		m_links.clear();
    }
	
	void PatcherView::addListener(sListener listener)
	{
		if(listener)
		{
			lock_guard<mutex> guard(m_listeners_mutex);
			m_listeners.insert(listener);
		}
	}
	
	void PatcherView::removeListener(sListener listener)
	{
		if(listener)
		{
			lock_guard<mutex> guard(m_listeners_mutex);
			m_listeners.erase(listener);
		}
	}
	
	void PatcherView::setZoom(long zoom)
	{
		m_zoom = clip(zoom, (long)1, (long)1000);
	}
	
	void PatcherView::setLockStatus(bool locked)
	{
		if(m_locked != locked)
		{
			m_locked = locked;
			
			m_listeners_mutex.lock();
			auto it = m_listeners.begin();
			while(it != m_listeners.end())
			{
				if((*it).expired())
				{
					it = m_listeners.erase(it);
				}
				else
				{
					sListener listener = (*it).lock();
					listener->patcherViewLockStatusChanged();
					++it;
				}
			}
			m_listeners_mutex.unlock();
			
			unselectAll();
			lockStatusChanged();
		}
	}
	
	void PatcherView::setPresentationStatus(bool presentation)
	{
		if(m_presentation != presentation)
		{
			m_presentation = presentation;
			
			m_listeners_mutex.lock();
			auto it = m_listeners.begin();
			while(it != m_listeners.end())
			{
				if((*it).expired())
				{
					it = m_listeners.erase(it);
				}
				else
				{
					sListener listener = (*it).lock();
					listener->patcherViewPresentationStatusChanged();
					++it;
				}
			}
			m_listeners_mutex.unlock();
			
			presentationStatusChanged();
		}
	}
	
	void PatcherView::setGridDisplayedStatus(bool display)
	{
		m_display_grid = display;
	}
	
	void PatcherView::setSnapToGridStatus(bool snap)
	{
		m_snap_to_grid = snap;
	}
	
	void PatcherView::setObjectsPresentationStatus(const vector<sObjectView>& objects, const bool add)
	{
		for(vector<sObjectView>::size_type i = 0; i < objects.size(); i++)
		{
			if(const sGuiObject object = objects[i]->getObject())
			{
				if (object->isIncludeInPresentation() != add)
				{
					sAttrBool attrpres = object->getAttrTyped<BoolValue>("presentation");
					if (attrpres)
					{
						attrpres->setValue(add);
						
						if (add)
						{
							const Rectangle bounds = object->getPresentationBounds();
							
							sAttrPoint attrpres_pos = object->getAttrTyped<PointValue>("presentation_position");
							sAttrSize attrpres_size = object->getAttrTyped<SizeValue>("presentation_size");
							
							if (attrpres_pos && attrpres_size)
							{
								attrpres_pos->setValue(bounds.position());
								SizeValue size(attrpres_size->getValue());
								size = bounds.size();
								attrpres_size->setValue(size);
							}
						}
					}
				}
			}
		}
	}
	
	void PatcherView::addObjectView(sObjectView object)
	{
		m_objects.push_back(object);
	}
	
	void PatcherView::removeObjectView(sObjectView object)
	{
        auto it = find(m_objects.begin(), m_objects.end(), object);
        if(it != m_objects.end())
        {
            m_objects.erase(it);
        }
	}
	
	sObjectView PatcherView::getObjectView(sGuiObject object) const noexcept
	{
		if(object)
		{
			lock_guard<mutex> guard(m_mutex);
			for(vector<sObjectView>::size_type i = 0; i < m_objects.size(); i++)
			{
				if(object == m_objects[i]->getObject())
				{
					return m_objects[i];
				}
			}
		}
		
		return sObjectView();
	}
	
	void PatcherView::addLinkView(sLinkView link)
	{
		m_links.push_back(link);
	}
	
	void PatcherView::removeLinkView(sLinkView link)
	{
		for(vector<sLinkView>::size_type i = 0; i < m_links.size(); i++)
		{
			if(link == m_links[i])
			{
				m_links.erase(m_links.begin()+i);
			}
		}
	}
	
	sLinkView PatcherView::getLinkView(sGuiLink link) const noexcept
	{
		if(link)
		{
			lock_guard<mutex> guard(m_mutex);
			for(vector<sLinkView>::size_type i = 0; i < m_links.size(); i++)
			{
				if(link == m_links[i]->getLink())
				{
					return m_links[i];
				}
			}
		}
		
		return sLinkView();
	}
	
	void PatcherView::getSelection(vector<sObjectView>& objects) const noexcept
	{
		objects.clear();
		for(auto it = m_objects_selected.begin(); it != m_objects_selected.end(); ++it)
		{
			if (sObjectView object = (*it).lock())
			{
				objects.push_back(object);
			}
		}
	}
	
	void PatcherView::getSelection(vector<sLinkView>& links) const noexcept
	{
		links.clear();
		for(auto it = m_links_selected.begin(); it != m_links_selected.end(); ++it)
		{
			if (sLinkView link = (*it).lock())
			{
				links.push_back(link);
			}
		}
	}
    
    void PatcherView::getSelection(set<wObjectView, owner_less<wObjectView>>& objects) const noexcept
	{
		objects = m_objects_selected;
	}
	
	void PatcherView::getSelection(set<wLinkView, owner_less<wLinkView>>& links) const noexcept
	{
		links = m_links_selected;
	}
	
	void PatcherView::unselectAll(const bool notify)
	{
		if(isAnythingSelected())
		{
			unselectAllObjects(false);
			unselectAllLinks(false);
			
			if(notify)
            {
				selectionChanged();
            }
		}
	}
	
	void PatcherView::deleteSelection()
	{
		bool sendChange = false;
		for(auto it = m_objects_selected.begin(); it != m_objects_selected.end(); ++it)
		{
			sObjectView object = (*it).lock();
			if(object)
			{
				getPatcher()->remove(object->getObject());
				sendChange = true;
			}
		}
		m_objects_selected.clear();
		
		for(auto it = m_links_selected.begin(); it != m_links_selected.end(); ++it)
		{
			sLinkView link = (*it).lock();
			if(link)
			{
				getPatcher()->remove(link->getLink());
				sendChange = true;
			}
		}
		m_links_selected.clear();
		
		if(sendChange)
        {
			selectionChanged();
        }
	}
	
	bool PatcherView::selectAllLinks()
	{
		if(m_links_selected.size() != m_links.size())
		{
			for(vector<sLinkView>::size_type i = 0; i < m_links.size(); i++)
			{
				if(m_links_selected.insert(m_links[i]).second)
				{
					m_links[i]->setSelectedStatus(true);
				}
			}
			selectionChanged();
			return true;
		}
		return false;
	}
	
	
	bool PatcherView::selectAllObjects()
	{
		if(m_objects_selected.size() != m_objects.size())
		{
			for(vector<sObjectView>::size_type i = 0; i < m_objects.size(); i++)
			{
				if(m_objects_selected.insert(m_objects[i]).second)
				{
					m_objects[i]->setSelectedStatus(true);
				}
			}
			selectionChanged();
			return true;
		}
		return false;
	}
	
	bool PatcherView::unselectAllObjects(const bool notify)
	{
		bool sendChange = false;
		if(!m_objects_selected.empty())
		{
			for(auto it = m_objects_selected.begin(); it != m_objects_selected.end(); ++it)
			{
				sObjectView object = (*it).lock();
				if(object)
				{
					object->setSelectedStatus(false);
					sendChange = true;
				}
			}
			m_objects_selected.clear();
			
			if(notify && sendChange)
            {
				selectionChanged();
            }
			
			return true;
		}
		return false;
	}
	
	bool PatcherView::unselectAllLinks(const bool notify)
	{
		bool sendChange = false;
		if(!m_links_selected.empty())
		{
			for(auto it = m_links_selected.begin(); it != m_links_selected.end(); ++it)
			{
				sLinkView link = (*it).lock();
				if(link)
				{
					link->setSelectedStatus(false);
					sendChange = true;
				}
			}
			m_links_selected.clear();
			
			if(notify && sendChange)
            {
				selectionChanged();
            }
			
			return true;
		}
		return false;
	}
	
	bool PatcherView::isSelected(sObjectView object)
	{
		return object && (m_objects_selected.find(object) != m_objects_selected.end());
	}
	
	bool PatcherView::isSelected(sLinkView link)
	{
		return link && (m_links_selected.find(link) != m_links_selected.end());
	}
	
	void PatcherView::select(vector<sObjectView>& objects)
	{
		bool notify = false;
		if(!objects.empty())
		{
			for(auto it = objects.begin(); it != objects.end(); ++it)
			{
				if(select(*it, false))
				{
					notify = true;
				}
			}
			
			if(notify)
            {
				selectionChanged();
            }
		}
	}
	
	void PatcherView::select(vector<sLinkView>& links)
	{
		bool notify = false;
		if(!links.empty())
		{
			for(auto it = links.begin(); it != links.end(); ++it)
			{
				if(select(*it, false))
				{
					notify = true;
				}
			}
			
			if(notify)
            {
				selectionChanged();
            }
		}
	}
	
	bool PatcherView::select(sObjectView object, const bool notify)
	{
		if(object && m_objects_selected.insert(object).second)
		{
			object->setSelectedStatus(true);
			if(notify)
            {
				selectionChanged();
            }
			return true;
		}
		return false;
	}
	
	bool PatcherView::select(sLinkView link, const bool notify)
	{
		if(link && m_links_selected.insert(link).second)
		{
			link->setSelectedStatus(true);
			if(notify)
            {
				selectionChanged();
            }
			return true;
		}
		return false;
	}
	
	bool PatcherView::selectOnly(sObjectView object)
	{
		unselectAllLinks();
		if (object)
		{
			if(!m_objects_selected.empty())
			{
				for(auto it = m_objects_selected.begin(); it != m_objects_selected.end(); ++it)
				{
					sObjectView object2 = (*it).lock();
					if(object2)
					{
						object2->setSelectedStatus(false);
					}
				}
				m_objects_selected.clear();
			}
			
			if(m_objects_selected.insert(object).second)
			{
				object->setSelectedStatus(true);
				selectionChanged();
				return true;
			}
		}
		
		return false;
	}
	
	bool PatcherView::selectOnly(sLinkView link)
	{
		unselectAllObjects();
		if(link)
		{
			if(!m_links_selected.empty())
			{
				for(auto it = m_links_selected.begin(); it != m_links_selected.end(); ++it)
				{
					sLinkView link2 = (*it).lock();
					if(link2)
					{
						link2->setSelectedStatus(false);
					}
				}
				m_links_selected.clear();
			}
			
			if(m_links_selected.insert(link).second)
			{
				link->setSelectedStatus(true);
				return true;
			}
			
			selectionChanged();
		}
		
		return false;
	}
	
	void PatcherView::unselect(vector<sObjectView>& objects)
	{
		bool notify = false;
		if(isAnythingSelected() && !objects.empty())
		{
			for(auto it = objects.begin(); it != objects.end(); ++it)
			{
				if(unselect(*it, false))
				{
					notify = true;
				}
			}
			
			if(notify)
            {
				selectionChanged();
            }
		}
	}
	
	void PatcherView::unselect(vector<sLinkView>& links)
	{
		bool notify = false;
		if(isAnythingSelected() && !links.empty())
		{
			for(auto it = links.begin(); it != links.end(); ++it)
			{
				if(unselect(*it, false))
				{
					notify = true;
				}
			}
			
			if(notify)
            {
				selectionChanged();
            }
		}
	}
	
	bool PatcherView::unselect(sObjectView object, const bool notify)
	{
		if(object && m_objects_selected.erase(object))
		{
			object->setSelectedStatus(false);
			if(notify)
            {
				selectionChanged();
            }
			return true;
		}
		return false;
	}
	
	bool PatcherView::unselect(sLinkView link, const bool notify)
	{
		if(link && m_links_selected.erase(link))
		{
			link->setSelectedStatus(false);
			if(notify)
            {
				selectionChanged();
            }
			return true;
		}
		return false;
	}
	
	Rectangle PatcherView::getSelectionBounds()
	{
		// to do !
        return Rectangle();
	}
	
	void PatcherView::startMoveOrResizeObjects()
	{
		m_last_bounds.clear();
		for(auto it = m_objects_selected.begin(); it != m_objects_selected.end(); ++it)
		{
			if(sObjectView objectctrl = (*it).lock())
			{
				if(sGuiObject object = objectctrl->getObject())
				{
					if(!getPresentationStatus())
					{
						m_last_bounds[objectctrl] = object->getBounds();
					}
					else
					{
						m_last_bounds[objectctrl] = object->getPresentationBounds();
					}
				}
			}
		}
	}
	
	void PatcherView::endMoveOrResizeObjects()
	{
		// Todo : add undo / redo here
		m_last_bounds.clear();
	}
	
	void PatcherView::resizeSelectedObjects(Point const& d, const long flags, const bool preserveRatio)
	{
		for(auto it = m_last_bounds.begin(); it != m_last_bounds.end(); ++it)
		{
			if(sObjectView objectview = (*it).first.lock())
			{
				sGuiObject object = objectview->getObject();
				if(object)
				{
					const bool presentation = getPresentationStatus();
					const string attrname_pos = presentation ? "presentation_position" : "position";
					const string attrname_size = presentation ? "presentation_size" : "size";
					sAttrPoint attrpos = object->getAttrTyped<PointValue>(attrname_pos);
					sAttrSize attrsize = object->getAttrTyped<SizeValue>(attrname_size);
					
					const double fixedRatio = attrsize->getValue().ratio();
					
					Rectangle original = it->second;
					Rectangle newrect = original;
					
					Point minLimit = Point(attrsize->getValue().minWidth(), attrsize->getValue().minHeight());
						
                    if (flags & Knock::Left)
						newrect.left(min(newrect.right() - minLimit.x(), newrect.x() + d.x()));
					
					if (flags & Knock::Right)
						newrect.width(max(minLimit.x(), newrect.width() + d.x()));
					
					if (flags & Knock::Top)
						newrect.top(min(newrect.bottom() - minLimit.y(), newrect.y() + d.y()));
					
					if (flags & Knock::Bottom)
						newrect.height(max(minLimit.y(), newrect.height() + d.y()));
					
					// constrain the aspect ratio if one has been specified..
					if (preserveRatio || (fixedRatio > 0.))
					{
						bool adjustWidth;
						double ratio = 1.;
						if(fixedRatio > 0.)
						{
							ratio = fixedRatio;
						}
						else if (original.height() > 0)
						{
							ratio = original.width() / original.height();
						}
						
						if ((flags & Knock::Top || flags & Knock::Bottom) && !(flags & Knock::Left || flags & Knock::Right))
						{
							adjustWidth = true;
						}
						else if ((flags & Knock::Left || flags & Knock::Right) && ! (flags & Knock::Top || flags & Knock::Bottom))
						{
							adjustWidth = false;
						}
						else
						{
							const double oldRatio = (original.height() > 0) ? abs(original.width() / (double) original.height()) : 0.0;
							const double newRatio = abs(newrect.width() / (double) newrect.height());
							
							adjustWidth = (oldRatio > newRatio);
						}
						
						if (adjustWidth)
						{
							newrect.width((newrect.height() * ratio));
							
							if (newrect.width() < minLimit.x())
							{
								newrect.width(minLimit.x());
								newrect.height(newrect.width() / ratio);
							}
						}
						else
						{
							newrect.height(newrect.width() / ratio);
							
							if (newrect.height() < minLimit.y())
							{
								newrect.height(minLimit.y());
								newrect.width(newrect.height() * ratio);
							}
						}
						
						if((flags & Knock::Top || flags & Knock::Bottom) && !(flags & Knock::Left || flags & Knock::Right))
						{
							newrect.x(original.x() + (original.width() - newrect.width()) / 2);
						}
						else if((flags & Knock::Left || flags & Knock::Right) && ! (flags & Knock::Top || flags & Knock::Bottom))
						{
							newrect.y(original.y() + (original.height() - newrect.height()) / 2);
						}
						else
						{
							if (flags & Knock::Left)
								newrect.x(original.right() - newrect.width());
							
							if (flags & Knock::Top)
								newrect.y(original.bottom() - newrect.height());
						}
					}
					
					if(attrpos)
					{
						attrpos->setValue(newrect.position());
					}
					
					if(attrsize)
					{
						SizeValue size(attrsize->getValue());
						size = newrect.size();
						attrsize->setValue(size);
					}
				}
			}
		}
	}
	
    void PatcherView::moveSelectedObjects(Point const& delta)
	{
		if (isAnyObjectSelected())
		{
			const bool presentation = getPresentationStatus();
			const string attrname_pos = presentation ? "presentation_position" : "position";
			
			for(auto it = m_objects_selected.begin(); it != m_objects_selected.end(); ++it)
			{
				if(sObjectView objectctrl = (*it).lock())
				{
                    if(sGuiObject object = objectctrl->getObject())
                    {
						sAttrPoint attrpos = object->getAttrTyped<PointValue>(attrname_pos);
						if(!presentation)
						{
							attrpos->setValue(object->getPosition() + delta);
						}
						else
						{
							attrpos->setValue(object->getPresentationPosition() + delta);
						}
                    }
				}
			}
		}
	}
	
	Dico PatcherView::getSelectedObjectsDico()
	{
        Dico dico;
        string text;
        
        /*
        if (isAnyObjectSelected())
        {
            vector<Atom> elements;
            vector<sGuiObject> objects;
            for(auto it = m_objects_selected.begin(); it != m_objects_selected.end(); ++it)
            {
                sObjectView objview = (*it).lock();
                if(objview)
                {
                    sGuiObject object = objview->getObject();
                    if (object)
                    {
                        Dico objectdico;
                        Dico subobject;
                        
                        object->write(subobject);
                        objectdico->set(Tag::List::object, subobject);
                        elements.push_back(objectdico);
                        objects.push_back(object);
                    }
                }
            }
            dico->set(Tag::List::objects, elements);
            
            elements.clear();
            
            for(vector<sGuiLink>::size_type i = 0; i < m_links.size(); i++)
            {
                Dico linkdico;
                Dico sublinkdico;
                sGuiLink link = m_links[i]->getLink();
                if (link)
                {
                    sGuiObject objectFrom = link->getObjectFrom();
                    sGuiObject objectTo = link->getObjectTo();
                    if (find(objects.begin(), objects.end(), objectFrom) != objects.end() &&
                        find(objects.begin(), objects.end(), objectTo) != objects.end())
                    {
                        link->write(sublinkdico);
                        linkdico->set(Tag::List::link, sublinkdico);
                        elements.push_back(linkdico);
                    }
                }
            }
            dico->set(Tag::List::links, elements);
            objects.clear();
        }
        */
        
		return dico;
	}
	
	bool PatcherView::addObjectsFromDico(Dico const& dico, Point const& shift)
	{
		bool TODO;
		return 0;
	}
	
	void PatcherView::objectCreated(sGuiObject object)
	{
		sObjectView objectview = createObjectView(object);
		if (objectview)
		{
			addObjectView(objectview);
			objectViewCreated(objectview);
		}
	}
	
	void PatcherView::objectRemoved(sGuiObject object)
	{
		sObjectView objectview = getObjectView(object);
		if (objectview)
		{
			objectViewWillBeRemoved(objectview);
			removeObjectView(objectview);
		}
	}
	
	void PatcherView::linkCreated(sGuiLink link)
	{
		sLinkView linkview = createLinkView(link);
		if (linkview)
		{
			addLinkView(linkview);
			linkViewCreated(linkview);
		}
	}
	
	void PatcherView::linkRemoved(sGuiLink link)
	{
		sLinkView linkview = getLinkView(link);
		if (linkview)
		{
			linkViewWillBeRemoved(linkview);
			removeLinkView(linkview);
		}
	}
    
    // ================================================================================ //
    //                                      KNOCK                                       //
    // ================================================================================ //
    
    Knock PatcherView::knockAll( Point const& point) const  noexcept
    {
        Knock knock;
        lock_guard<mutex> guard(m_mutex);
		
		for (auto rit = m_objects.rbegin(); rit != m_objects.rend(); ++rit)
		{
			if((*rit)->contains(point, knock))
			{
				return knock;
			}
		}
        if(!getPresentationStatus())
        {
			for (auto rit = m_links.rbegin(); rit != m_links.rend(); ++rit)
			{
				if((*rit)->contains(point, knock))
				{
					return knock;
				}
			}
        }
		knock.target = Knock::Patcher;
        knock.patcher = const_pointer_cast<PatcherView>(shared_from_this());
        knock.part = Knock::Inside;
        return knock;
    }
    
    Knock PatcherView::knockObjects(Point const& point) const noexcept
    {
        Knock knock;
        lock_guard<mutex> guard(m_mutex);
		for (auto rit = m_objects.rbegin(); rit != m_objects.rend(); ++rit)
		{
			if((*rit)->contains(point, knock))
			{
				return knock;
			}
		}
        knock.patcher = const_pointer_cast<PatcherView>(shared_from_this());
        knock.part = Knock::Inside;
        return knock;
    }
    
    Knock PatcherView::knockLinks(Point const& point) const noexcept
    {
        Knock knock;
		if(!getPresentationStatus())
		{
			lock_guard<mutex> guard(m_mutex);
			for (auto rit = m_links.rbegin(); rit != m_links.rend(); ++rit)
			{
				if((*rit)->contains(point, knock))
				{
					return knock;
				}
			}
		}
        knock.patcher = const_pointer_cast<PatcherView>(shared_from_this());
        knock.part = Knock::Inside;
        return knock;
    }
    
    
    void PatcherView::knockAll(Rectangle const& rect, vector<sObjectView>& objects, vector<sLinkView>& links) const  noexcept
    {
        knockObjects(rect, objects);
        knockLinks(rect, links);
    }
    
    void PatcherView::knockObjects(Rectangle const& rect, vector<sObjectView>& objects) const  noexcept
    {
        lock_guard<mutex> guard(m_mutex);
		for (auto rit = m_objects.rbegin(); rit != m_objects.rend(); ++rit)
		{
			if((*rit)->overlaps(rect))
			{
				objects.push_back(*rit);
			}
		}
    }
	
    void PatcherView::knockLinks(Rectangle const& rect, vector<sLinkView>& links) const  noexcept
    {
		if(!getPresentationStatus())
		{
			lock_guard<mutex> guard(m_mutex);
			for (auto rit = m_links.rbegin(); rit != m_links.rend(); ++rit)
			{
				if((*rit)->overlaps(rect))
				{
					links.push_back(*rit);
				}
			}
		}
    }
    
    // ================================================================================ //
    //										IOLET MAGNET                                //
    // ================================================================================ //
    
    PatcherView::Magnet PatcherView::magnetFindInlet(sObjectView object, Point const& point, double distance) const
    {
        Magnet magnet;
        lock_guard<mutex> guard(m_mutex);
        for(vector<sObjectView>::size_type i = m_objects.size(); i; i--)
        {
            if(m_objects[i] != object)
            {
                for(ulong j = 0; j <  m_objects[i]->getNumberOfInlets(); j++)
                {
                    const double cdistance = point.distance(m_objects[i]->getInletPosition(j));
                    if(cdistance < distance)
                    {
                        magnet.object   = m_objects[i];
                        magnet.index = j;
                        distance = cdistance;
                    }
                }
            }
        }
        return magnet;
    }
    
    PatcherView::Magnet PatcherView::magnetFindOutlet(sObjectView object, Point const& point, double distance) const
    {
        Magnet magnet;
        lock_guard<mutex> guard(m_mutex);
        for(vector<sObjectView>::size_type i = m_objects.size(); i; i--)
        {
            if(m_objects[i] != object)
            {
                for(ulong j = 0; j <  m_objects[i]->getNumberOfOutlets(); j++)
                {
                    const double cdistance = point.distance(m_objects[i]->getOutletPosition(j));
                    if(cdistance < distance)
                    {
                        magnet.object   = m_objects[i];
                        magnet.index = j;
                        distance = cdistance;
                    }
                }
            }
        }
        return magnet;
    }
    
    // ================================================================================ //
    //										LASSO                                       //
    // ================================================================================ //
    
    void PatcherView::lassoBegin(Lasso* lasso, Point const& point, const bool preserve)
    {
        if(lasso->dragging)
        {
            lasso->objects.clear();
            lasso->links.clear();
        }
        
        if(!preserve)
        {
            unselectAll();
        }
        else
        {
            lock_guard<mutex> guard(m_mutex);
            for(auto it = m_objects_selected.begin(); it != m_objects_selected.end(); ++it)
            {
                sObjectView object = (*it).lock();
                if(object)
                {
                    lasso->objects.insert(object);
                }
            }
            
            for(auto it = m_links_selected.begin(); it != m_links_selected.end(); ++it)
            {
                sLinkView link = (*it).lock();
                if(link)
                {
                    lasso->links.insert(link);
                }
            }
        }
        
        lasso->origin = point;
        lasso->bounds = Rectangle(lasso->origin, Point(0., 0));
        lasso->dragging = true;
    }
    
    void PatcherView::lassoPerform(Lasso* lasso, Point const& pos, bool objects, bool links, const bool preserve)
    {
		lasso->bounds = Rectangle::withCorners(lasso->origin, pos);

        bool selectionHasChanged = false;
        if(preserve)
        {
            if(objects)
            {
                vector<sObjectView> lassoObjects;
                knockObjects(lasso->bounds, lassoObjects);
                
                lock_guard<mutex> guard(m_mutex);
                for(vector<sObjectView>::size_type i = 0; i < m_objects.size(); i++)
                {
                    const bool isSelected = m_objects[i]->isSelected();
                    const bool wasSelected = lasso->objects.find(m_objects[i]) != lasso->objects.end();
                    const bool inLasso = find(lassoObjects.begin(), lassoObjects.end(), m_objects[i]) != lassoObjects.end();
                    
                    if(!isSelected && (wasSelected != inLasso))
                    {
                        select(m_objects[i], false);
                        selectionHasChanged = true;
                    }
                    else if(isSelected && (wasSelected == inLasso))
                    {
                        unselect(m_objects[i], false);
                        selectionHasChanged = true;
                    }
                }
            }
            if(links)
            {
                vector<sLinkView> lassoLinks;
                knockLinks(lasso->bounds, lassoLinks);
                
                lock_guard<mutex> guard(m_mutex);
                for(vector<sLinkView>::size_type i = 0; i < m_links.size(); i++)
                {
                    const bool isSelected = m_links[i]->isSelected();
                    const bool wasSelected = lasso->links.find(m_links[i]) != lasso->links.end();
                    const bool inLasso = find(lassoLinks.begin(), lassoLinks.end(), m_links[i]) != lassoLinks.end();
                    
                    if(!isSelected && (wasSelected != inLasso))
                    {
                        select(m_links[i], false);
                        selectionHasChanged = true;
                    }
                    else if(isSelected && (wasSelected == inLasso))
                    {
                        unselect(m_links[i], false);
                        selectionHasChanged = true;
                    }
                }
            }
            
            if(selectionHasChanged)
            {
                selectionChanged();
            }
        }
        else
        {
            unselectAll(false);
            if(objects)
            {
                vector<sObjectView> nObjects;
                knockObjects(lasso->bounds, nObjects);
                select(nObjects);
            }
            if(links)
            {
                vector<sLinkView> nLinks;
                knockLinks(lasso->bounds, nLinks);
                select(nLinks);
            }
        }
    }
    
    void PatcherView::lassoEnd(Lasso* lasso) const
    {
        lasso->dragging = false;
        lasso->objects.clear();
        lasso->links.clear();
    }
}




