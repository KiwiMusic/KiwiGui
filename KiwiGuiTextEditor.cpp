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
    GuiSketcher(context),
    m_caret(make_shared<Caret>(context))
    {
        m_notify_return = true;
        m_notify_tab    = true;
        m_formated      = false;
        m_line_space    = 1.5;
        m_justification = Font::Justification::CentredLeft;
        m_caret->setPosition(Point(0., 0.));
        m_caret->setSize(Size(2., m_font.getSize()));
        m_caret->start();
        add(m_caret);
    }
    
    GuiTextEditor::~GuiTextEditor() noexcept
    {
        m_lines.clear();
    }
    
    void GuiTextEditor::setFont(Font const& font) noexcept
    {
        if(font != m_font)
        {
            m_formated = false;
            m_font = font;
            m_caret->setSize(Size(1., m_font.getSize()));
            getLineWidths();
            format();
            redraw();
        }
    }
    
    void GuiTextEditor::setJustification(const Font::Justification justification) noexcept
    {
        if(justification != m_justification)
        {
            m_justification = justification;
            redraw();
        }
    }
    
    void GuiTextEditor::setLineSpacing(const double factor) noexcept
    {
        if(factor != m_line_space)
        {
            m_line_space = factor;
            redraw();
        }
    }
    
    void GuiTextEditor::setDisplayMode(const DisplayMode mode) noexcept
    {
        if(mode != m_mode)
        {
            m_mode = mode;
            format();
            redraw();
        }
    }
    
    void GuiTextEditor::showCaret(const bool state) noexcept
    {
        if(state && !m_caret->state())
        {
            add(m_caret);
            m_caret->start();
        }
        else if(!state && m_caret->state())
        {
            m_caret->stop();
            remove(m_caret);
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
        sketch.setColor(Colors::black);
        sketch.setFont(m_font);
        const double height = m_font.getSize() * m_line_space;
        for(vector<wstring>::size_type i = 0; i < m_lines.size(); i++)
        {
            sketch.drawText(m_lines[i], 0., i * height, size.width(), height, m_justification);
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
            m_formated = false;
            m_text.pop_back();
            getLineWidths();
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
            format();
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
        m_text = text;
    }
    
    Size GuiTextEditor::getTextSize() const noexcept
    {
        if(!m_widths.empty())
        {
            return Size(*max_element(m_widths.begin(), m_widths.end()), (m_widths.size() - 1) * m_line_space * m_font.getSize() + m_font.getSize());
        }
        else
        {
            return Size();
        }
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
        m_formated = false;
        m_text += character;
        getLineWidths();
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
        format();
        redraw();
    }
    
    void GuiTextEditor::getLineWidths() noexcept
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            m_widths.clear();
            wistringstream stream(m_text);
            wstring line;
            while(bool(getline(stream, line)))
            {
                m_widths.push_back(ctxt->getTextWidth(m_font, line));
            }
            if(m_text[m_text.size() - 1] == L'\n')
            {
                m_widths.push_back(0.);
            }
        }
    }
    
    void GuiTextEditor::format() noexcept
    {
        if(!m_formated)
        {
            m_lines.clear();
            wistringstream stream(m_text);
            wstring line;
            while(bool(getline(stream, line)))
            {
                m_lines.push_back(line);
            }
            if(m_text[m_text.size() - 1] == L'\n')
            {
                m_lines.push_back(wstring());
            }
            sGuiContext ctxt = getContext();
            if(ctxt && !m_lines.empty())
            {
                const ulong nlines = ulong(m_lines.size()) - 1ul;
                m_caret->setPosition(Point(ctxt->getTextWidth(m_font, m_lines[nlines]), nlines * m_line_space * m_font.getSize()));
            }
            m_formated = true;
        }
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



