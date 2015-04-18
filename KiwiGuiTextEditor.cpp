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

#include "KiwiGuiTextEditor.h"
#include "KiwiGuiDevice.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                     TEXT EDITOR                                  //
    // ================================================================================ //
    
    GuiTextEditor::GuiTextEditor(sGuiContext context) noexcept :
    GuiSketcher(context)
    {
        m_multi_line = false;
        m_wrap_word  = false;
        m_notify_return = true;
        m_notify_tab    = true;
    }
    
    GuiTextEditor::~GuiTextEditor() noexcept
    {
        
    }
    
    void GuiTextEditor::setDisplay(const bool shouldBeMultiLine, const bool shouldWordWrap)
    {
        if(m_multi_line != shouldBeMultiLine || m_wrap_word != (shouldWordWrap && shouldBeMultiLine))
        {
            m_multi_line   = shouldBeMultiLine;
            m_wrap_word    = shouldWordWrap && shouldBeMultiLine;
            /*
            viewport->setScrollBarsShown(scrollbarVisible && multiline, scrollbarVisible && multiline);
            viewport->setViewPosition(0, 0);
            resized();
            scrollToMakeSureCursorIsVisible();
             */
        }
    }
    
    void GuiTextEditor::setKeyNotification(const bool returnNotifies, const bool tabNotifies) noexcept
    {
        m_notify_return = returnNotifies;
        m_notify_tab    = tabNotifies;
    }
}



