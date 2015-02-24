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

#include "Classic.h"

namespace Kiwi
{
	// ================================================================================ //
	//                                     DEFAULT                                      //
	// ================================================================================ //
	Default::Default() noexcept :
	m_color_background( Attr::create("bgcolor",     "Background Color", "Color", ColorValue(1., 1., 1., 1.))),
	m_color_border(     Attr::create("bdcolor",     "Border Color",     "Color", ColorValue(0.4, 0.4, 0.4, 1.)))
	{
		m_size->setValue(Size(80., 20.));
		addAttr(m_color_background);
		addAttr(m_color_border);
	}
	
	Default::~Default()
	{
		;
	}
	
	void Default::draw(Kiwi::Doodle& d) const
	{
		const double borderSize = 2;
		d.fillAll(m_color_background->getValue());
		d.setColor(m_color_border->getValue());
		d.drawRectangle(d.getBounds().reduced(borderSize*0.5), borderSize);
	}
	
	bool Default::textFilter(wstring& newtext)
	{
		string text = string(newtext.begin(), newtext.end());
		cout << "newbox textenter: " << text << endl;
		return true;
	}
	
	void Default::textChanged()
	{
		;
	}
	
	bool Default::notify(sAttr attr)
	{
		if(attr == m_color_background || attr == m_color_border)
		{
			redraw();
		}
		
		if (attr->getName() == "size")
		{
			cout << "size changed" << endl;
		}
		
		return true;
	}
	
	/*
		sObject NewBox::create(Initializer const& initiliazer) const
		{
	 sObject obj = make_shared<NewBox>(initiliazer);
	 
	 Kiwi::sWriter writer = dynamic_pointer_cast<Kiwi::Writer>(obj);
	 if(writer)
	 {
	 Kiwi::Writer::sTextField textfield = writer->getTextField();
	 if(textfield)
	 {
	 textfield->setWriter(writer);
	 }
	 }
	 
	 return obj;
		}
		*/
	
	// ================================================================================ //
	//                                      BUTTON                                      //
	// ================================================================================ //
	
	Button::Button() noexcept :
	m_color_background( Attr::create("bgcolor",     "Background Color", "Color", ColorValue(1., 1., 1., 1.))),
	m_color_border(     Attr::create("bdcolor",     "Border Color",     "Color", ColorValue(0.4, 0.4, 0.4, 1.))),
	m_color_circle(     Attr::create("circlecolor", "Circle Color",     "Color", ColorValue(0.4, 0.4, 0.4, 1.))),
	m_color_led(        Attr::create("ledcolor",    "Led Color",        "Color", ColorValue(0.4, 0.4, 0.4, 1.))),
	m_led(false)
	{
		m_size->setValue(Size(20., 20., 10., 10., 1.));
		addAttr(m_color_background);
		addAttr(m_color_border);
		addAttr(m_color_circle);
		addAttr(m_color_led);
	}
	
	Button::~Button()
	{
		;
	}
	
	bool Button::receive(Mouser::Event const& event)
	{
		if(event.isDown())
		{
			this->bang();
			m_led = true;
			redraw();
			return true;
		}
		else if(event.isUp())
		{
			m_led = false;
			redraw();
			return true;
		}
		return false;
	}
	
	void Button::draw(Kiwi::Doodle& d) const
	{
		const double borderSize = d.getWidth() * 0.1;
		const Rectangle ledRect = d.getBounds().reduced(d.getWidth() * 0.2);
		d.fillAll(m_color_background->getValue());
		
		d.setColor(m_color_border->getValue());
		d.drawRectangle(d.getBounds().reduced(borderSize*0.5), borderSize, 0);
		d.setColor(m_color_circle->getValue());
		d.drawEllipse(ledRect, borderSize);
		
		if(m_led)
		{
			d.setColor(m_color_led->getValue());
			d.fillEllipse(ledRect);
		}
	}
	
	bool Button::notify(sAttr attr)
	{
		if(attr == m_color_circle || attr == m_color_background || attr == m_color_border)
		{
			cout << "attr changed : "<< attr->getName() << endl;
			redraw();
		}
		return true;
	}
}

