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

#include "KiwiGuiObject.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      GUI DEVICE                                  //
    // ================================================================================ //
    GuiObject::GuiObject(sGuiPatcher patcher) noexcept :
    m_number_of_inlets(Attr::create("object_inlets","Number of Inlets", "Object", LongValue(0), Attr::Invisible)),
    m_number_of_outlets(Attr::create("object_outlets","Number of Outlets", "Object", LongValue(0), Attr::Invisible)),
    m_text(Attr::create("object_text","Object text", "Object", StringValue(""), Attr::Invisible)),
    m_presentation_position(Attr::create("presentation_position","Presentation Position", "Appearance", PointValue(0., 0.))),
    m_presentation_size(Attr::create("presentation_size",        "Presentation Size",     "Appearance", SizeValue(10., 10.))),
    m_hidden(Attr::create("hidden",                              "Hide on Lock",          "Appearance", BoolValue(false))),
    m_presentation(Attr::create("presentation",                  "Include in presentation","Appearance", BoolValue(false))),
    m_ignoreclick(Attr::create("ignoreclick",                    "Ignore Click",           "Behavior",   BoolValue(false)))
    {
        addAttr(m_presentation_position);
        addAttr(m_presentation_size);
        addAttr(m_hidden);
        addAttr(m_presentation);
        addAttr(m_ignoreclick);
    }
    
    GuiObject::~GuiObject()
    {
        ;
    }
}
















