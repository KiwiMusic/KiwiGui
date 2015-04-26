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
    
    void GuiTextEditor::Caret::draw(scGuiView view, Sketch& sketch) const
    {
        if(m_status)
        {
            sketch.setColor(m_color);
            sketch.drawLine(0., 0., 0., getSize().height(), 2.);
        }
    }
    
    void GuiTextEditor::Caret::viewCreated(sGuiView view) noexcept
    {
        if(!m_active)
        {
            m_active = true;
            m_status = true;
            redraw();
            delay(500.);
        }
    }
    
    void GuiTextEditor::Caret::viewRemoved(sGuiView view) noexcept
    {
        m_active = false;
    }
    
    void GuiTextEditor::Caret::tick()
    {
        if(m_active)
        {
            m_status = !m_status;
            redraw();
            delay(500.);
        }
    }
    
    
    // ================================================================================ //
    //                                     TEXT EDITOR                                  //
    // ================================================================================ //
    
    GuiTextEditor::GuiTextEditor(sGuiContext context) noexcept :
    GuiSketcher(context),
    m_caret(make_shared<Caret>(context))
    {
        m_notify_return = UsedAsCharacter;
        m_notify_tab    = UsedAsCharacter;
        m_formated      = false;
        m_line_space    = 1.;
        m_justification = Font::Justification::TopLeft;
        m_begin         = 0;
        m_caret->setPosition(Point(0., 0.));
        m_caret->setSize(Size(2., m_font.getSize()));
    }
    
    GuiTextEditor::~GuiTextEditor() noexcept
    {
        m_lines.clear();
        lock_guard<mutex> guard(m_lists_mutex);
        m_lists.clear();
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
        if(justification & Font::Justification::Left && !(m_justification & Font::Justification::Left))
        {
            m_justification = Font::Justification::TopLeft;
            redraw();
        }
        else if(justification & Font::Justification::Right && !(m_justification & Font::Justification::Right))
        {
            m_justification = Font::Justification::TopRight;
            redraw();
        }
        else if(justification & Font::Justification::HorizontallyCentered && !(m_justification & Font::Justification::HorizontallyCentered))
        {
            m_justification = Font::Justification::CentredTop;
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
    
    void GuiTextEditor::setReturnKeyBehavior(const bool notify) noexcept
    {
        m_notify_return = notify;
    }
    
    void GuiTextEditor::setTabKeyBehavior(const bool notify) noexcept
    {
        m_notify_tab    = notify;
    }
    
    void GuiTextEditor::setColor(Color const& color) noexcept
    {
        if(m_color != color)
        {
            m_color = color;
            redraw();
        }
    }
    
    void GuiTextEditor::draw(scGuiView view, Sketch& sketch) const
    {
        const Size size = getSize();
        sketch.setColor(m_color);
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
        if(event.isCharacter())
        {
            switch(event.getCharacter())
            {
                case KeyboardEvent::Key::Escape:
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
                    break;
                case KeyboardEvent::Key::Return:
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
                    break;
                case KeyboardEvent::Key::Tab:
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
                    break;
                case KeyboardEvent::Key::Backspace:
                    eraseSelection(event.hasAlt());
                    break;
                case KeyboardEvent::Key::Delete:
                    cout << "delete" << endl;
                    break;
                    
                default:
                    addCharacter(event.getCharacter());
                    break;
            }
        }
        else
        {
            moveCaret(event.getKeyCode(), event.hasAlt(), event.hasShift());
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
            return Size(0., m_font.getSize());
        }
    }
    
    void GuiTextEditor::clearText() noexcept
    {
        m_formated = false;
        m_text.clear();
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
    
    void GuiTextEditor::eraseSelection(const bool forward) noexcept
    {
        if(!m_text.empty())
        {
            if(forward && m_text.size() > m_begin)
            {
                m_formated = false;
                m_text.erase(m_begin, 1ul);
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
                if(format()){redraw();}
            }
            else if(!forward && m_begin)
            {
                m_formated = false;
                m_text.erase(m_begin-1, 1ul);
                m_begin--;
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
                if(format()){redraw();}
            }
        }
        
    }
    
    void GuiTextEditor::addCharacter(wchar_t character) noexcept
    {
        m_formated = false;
        m_text.insert(m_begin, 1ul, character);
        m_begin++;
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
        if(format())
        {
            redraw();
        }
    }
    
    void GuiTextEditor::getLineWidths() noexcept
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            wstring line;
            m_widths.clear();
            wistringstream stream(m_text);
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
    
    bool GuiTextEditor::format() noexcept
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
            computeCaretPosition();
            m_formated = true;
            return true;
        }
        return false;
    }
    
    bool GuiTextEditor::receive(scGuiView view, KeyboardFocus const event)
    {
        if(event == KeyboardFocusIn)
        {
            addChild(m_caret);
        }
        else
        {
            removeChild(m_caret);
        }
        return true;
    }
    
    bool GuiTextEditor::notify(sAttr attr)
    {
        if(attr->getName() == Tags::size)
        {
            m_formated = false;
            format();
        }
        return true;
    }
    
    void GuiTextEditor::computeCaretPosition() noexcept
    {
        wstring::size_type size = 0;
        for(vector<wstring>::size_type i = 0; i < m_lines.size(); i++)
        {
            if(m_begin <= size + m_lines[i].size())
            {
                sGuiContext ctxt = getContext();
                if(ctxt)
                {
                    const double w = ctxt->getTextWidth(m_font, wstring(m_lines[i].c_str(), max(m_begin - size, 0ul)));
                    m_caret->setPosition(Point(w, double(i) * m_line_space * m_font.getSize()));
                    cout << max(m_begin - size, 0ul) << endl;
                    return;
                    
                }
            }
            else
            {
                size += (m_lines[i].size() + 1);
            }
        }
        m_caret->setPosition(Point(0., 0.));
    }
    
    void GuiTextEditor::moveCaret(int const direction, const bool alt, const bool shift) noexcept
    {
        if(!alt && !shift)
        {
            if(direction == KeyboardEvent::Key::Left)
            {
                if(m_begin > 0ul)--m_begin;
                computeCaretPosition();
            }
            else if(direction == KeyboardEvent::Key::Right)
            {
                if(m_begin < m_text.size() - 1ul) ++m_begin;
                computeCaretPosition();
            }
            else if(direction == KeyboardEvent::Key::Up)
            {
                ;
            }
            else if(direction == KeyboardEvent::Key::Down)
            {
                if(m_begin < m_text.size() - 1ul) ++m_begin;
                computeCaretPosition();
            }
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



