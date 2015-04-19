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
        }
    }
    
    void GuiTextEditor::setKeyNotification(const bool returnNotifies, const bool tabNotifies) noexcept
    {
        m_notify_return = returnNotifies;
        m_notify_tab    = tabNotifies;
    }
    
    void GuiTextEditor::draw(scGuiView view, Sketch& sketch) const
    {
        const Size size = getSize();
        sketch.fillAll(Colors::white);
        if(!m_multi_line)
        {
            sketch.setColor(Colors::black);
            sketch.drawText(m_text, 0., 0., size.width(), size.height(), Font::CentredLeft);
        }
        else
        {
            sketch.setColor(Colors::black);
            sketch.drawText(m_text, 0., 0., size.width(), size.height(), Font::CentredLeft);
        }        
    }
    
    bool GuiTextEditor::receive(scGuiView view, MouseEvent const& event)
    {
        return true;
    }
    
    bool GuiTextEditor::receive(scGuiView view, KeyboardEvent const& event)
    {
        if(event.isBackspace())
        {
            m_text.pop_back();
            lock_guard<mutex> guard(m_lists_mutex);
            auto it = m_lists.begin();
            while(it != m_lists.end())
            {
                sListener listener = (*it).lock();
                if(listener)
                {
                    listener->textChanged(static_pointer_cast<GuiTextEditor>(shared_from_this()));
                    ++it;
                }
                else
                {
                    it = m_lists.erase(it);
                }
            }
            redraw();
        }
        else if(event.isReturn())
        {
            if(m_notify_return)
            {
                lock_guard<mutex> guard(m_lists_mutex);
                auto it = m_lists.begin();
                while(it != m_lists.end())
                {
                    sListener listener = (*it).lock();
                    if(listener)
                    {
                        listener->returnKeyPressed(static_pointer_cast<GuiTextEditor>(shared_from_this()));
                        ++it;
                    }
                    else
                    {
                        it = m_lists.erase(it);
                    }
                }
            }
            else
            {
                addCharacter(L'\n');
            }
        }
        else if(event.isTab())
        {
            if(m_notify_tab)
            {
                lock_guard<mutex> guard(m_lists_mutex);
                auto it = m_lists.begin();
                while(it != m_lists.end())
                {
                    sListener listener = (*it).lock();
                    if(listener)
                    {
                        listener->tabKeyPressed(static_pointer_cast<GuiTextEditor>(shared_from_this()));
                        ++it;
                    }
                    else
                    {
                        it = m_lists.erase(it);
                    }
                }
            }
            else
            {
                addCharacter(L'\t');
            }
        }
        else if(event.isEscape())
        {
            lock_guard<mutex> guard(m_lists_mutex);
            auto it = m_lists.begin();
            while(it != m_lists.end())
            {
                sListener listener = (*it).lock();
                if(listener)
                {
                    listener->escapeKeyPressed(static_pointer_cast<GuiTextEditor>(shared_from_this()));
                    ++it;
                }
                else
                {
                    it = m_lists.erase(it);
                }
            }
        }
        else if(event.isCharacter())
        {
            addCharacter(event.getCharacter());
        }
        return true;
    }
    
    void GuiTextEditor::setText(wstring const& text) noexcept
    {
        
    }
    
    void GuiTextEditor::clearText() noexcept
    {
        
    }
    
    ulong GuiTextEditor::getCaretPosition() const noexcept
    {
        return 0ul;
    }
    
    void GuiTextEditor::setCaretPosition(ulong pos) noexcept
    {
        
    }
    
    void GuiTextEditor::addCharacter(wchar_t character) noexcept
    {
        m_text += character;
        lock_guard<mutex> guard(m_lists_mutex);
        auto it = m_lists.begin();
        while(it != m_lists.end())
        {
            sListener listener = (*it).lock();
            if(listener)
            {
                listener->textChanged(static_pointer_cast<GuiTextEditor>(shared_from_this()));
                ++it;
            }
            else
            {
                it = m_lists.erase(it);
            }
        }
        redraw();
    }
    
    void GuiTextEditor::addListener(sListener listener)
    {
        if(listener)
        {
            lock_guard<mutex> guard(m_lists_mutex);
            m_lists.insert(listener);
        }
    }
    
    void GuiTextEditor::removeListener(sListener listener)
    {
        if(listener)
        {
            lock_guard<mutex> guard(m_lists_mutex);
            m_lists.erase(listener);
        }
    }
}



