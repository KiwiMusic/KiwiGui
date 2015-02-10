//
//  main.cpp
//  example
//
//  Created by Guillot Pierre on 30/01/2015.
//  Copyright (c) 2015 Kiwi. All rights reserved.
//

#include <iostream>

#include "../../Gui.h"
using namespace Kiwi::Gui;

int main(int argc, const char * argv[])
{
    Mouser::Event mevent(Mouser::Event::Down, Kiwi::Gui::Point(0., 0.), 0);
    shared_ptr<Bang> bang = Sketcher::create<Bang>();
    bang->initialize();
    
    sAttr attr;
    vector<sAttr> attrs;
    bang->getAttributes(attrs);
    for(vector<sAttr>::size_type i = 0; i < attrs.size(); i++)
    {
        if(attrs[i]->getName() == "circlecolor")
        {
            attr = attrs[i];
        }
        cout << attrs[i]->getTypeName() << endl;
    }
    if(!attr)
    {
        return 1;
    }

    if(attr->isType<Color>())
    {
        sAttrColor cattr = dynamic_pointer_cast<Attr<Color>>(attr);
        if(cattr)
        {
            cout << "Color : " << endl;
            Color color;
            cattr->getValue(color);
            cout << color.red() << " " << color.green() << " " << color.blue() << endl;
            cattr->setValue(Color(0.1, 0.2, 0.3, 0.4));
            cattr->getValue(color);
            cout << color.red() << " " << color.green() << " " << color.blue() << endl;
        }
    }
    
    for(vector<sAttr>::size_type i = 0; i < attrs.size(); i++)
    {
        if(attrs[i]->getName() == "size")
        {
            attr = attrs[i];
        }
    }
    if(!attr)
    {
        return 1;
    }
    if(attr->isType<Kiwi::Gui::Size>())
    {
        sAttrSize cattr = dynamic_pointer_cast<Attr<Kiwi::Gui::Size>>(attr);
        if(cattr)
        {
            cout << "Size : " << endl;
            Kiwi::Gui::Size size;
            cattr->getValue(size);
            cout << size.width() << " " << size.height() << endl;
            cattr->setValue(Kiwi::Gui::Point(0.1, 0.2));
            cattr->getValue(size);
           cout << size.width() << " " << size.height() << endl;
        }
    }
    
    bang->receive(mevent);
    return 0;
}
