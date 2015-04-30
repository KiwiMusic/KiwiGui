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
    //                                      TEXT                                        //
    // ================================================================================ //
    
    GuiText::GuiText(sGuiContext ctxt) noexcept : GuiSketcher(ctxt),
    m_font(),
    m_justification(Font::Justification::TopLeft),
    m_line_space(1.),
    m_display_mode(Wrapped),
    m_text()
    {
        if(ctxt)
        {
            m_empty_width = ctxt->getTextWidth(m_font, wstring(L" "));
            m_trail_width = ctxt->getTextWidth(m_font, wstring(L"..."));
        }
        else
        {
            m_empty_width = m_font.getSize() * 0.5;
            m_trail_width = m_empty_width * 3.;
        }
        computeLinesWidth();
    }
    
    GuiText::~GuiText() noexcept
    {
        m_text.clear();
    }
    
    void GuiText::setFont(Font const& font) noexcept
    {
        if(font != m_font)
        {
            m_font      = font;
            sGuiContext ctxt = getContext();
            if(ctxt)
            {
                m_empty_width = ctxt->getTextWidth(m_font, wstring(L" "));
                m_trail_width = ctxt->getTextWidth(m_font, wstring(L"..."));
            }
            computeLinesWidth();
            redraw();
            m_redraw = false;
        }
    }
    
    void GuiText::setJustification(const Font::Justification justification) noexcept
    {
        if(m_justification != justification)
        {
            m_justification = justification;
            redraw();
        }
    }
    
    void GuiText::setLineSpacing(const double factor) noexcept
    {
        if(factor != m_line_space)
        {
            m_line_space = factor;
            computeLinesWidth();
            redraw();
        }
    }
    
    void GuiText::setDisplayMode(const DisplayMode mode) noexcept
    {
        if(mode != m_display_mode)
        {
            m_display_mode = mode;
            redraw();
        }
    }
    
    void GuiText::setColor(Color const& color) noexcept
    {
        if(m_color != color)
        {
            m_color = color;
            redraw();
        }
    }
    
    void GuiText::setString(wstring const& text) noexcept
    {
        m_text = text;
    }
    
    void GuiText::setString(wstring&& text) noexcept
    {
        swap(m_text, text);
    }
    
    void GuiText::clearString() noexcept
    {
        m_text.clear();
    }
    
    void GuiText::computeLinesWidth() noexcept
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            m_widths.clear();
            size_type last = 0ul;
            size_type pos = m_text.find(L'\n', 0ul);
            while(pos != npos)
            {
                m_widths.push_back(ctxt->getTextWidth(m_font, wstring(m_text, last, pos - last)) + m_empty_width);
                last = pos+1ul;
                pos = m_text.find(L'\n', last);
            }
            m_widths.push_back(ctxt->getTextWidth(m_font, wstring(m_text, last, npos)) + m_empty_width);
        }
    }
    
    void GuiText::drawTruncated(scGuiView view, Sketch& sketch) const
    {
        ulong i = 0ul;
        size_type last = 0ul, pos = m_text.find(L'\n', 0ul);
        const Rectangle bounds = sketch.getBounds();
        const double height = m_font.getSize() * m_line_space;
        while(pos != npos)
        {
            const double h = i++ * height;
            if(h > bounds.y())
            {
                sketch.drawText(wstring(m_text, last, pos - last), 0., h, bounds.width(), height, m_justification);
            }
            last = pos+1ul;
            pos = m_text.find(L'\n', last);
        }
        const double h = i++ * height;
        if(h > bounds.y())
        {
            sketch.drawText(wstring(m_text, last, npos), 0., h, bounds.width(), height, m_justification);
        }
    }
    
    void GuiText::drawTrailPoint(scGuiView view, Sketch& sketch) const
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            const Size size = getSize();
            ulong i = 0ul;
            size_type last = 0ul, pos = m_text.find(L'\n', 0ul);
            const Rectangle bounds = sketch.getBounds();
            const double height = m_font.getSize() * m_line_space;
            while(pos != npos)
            {
                if(m_widths[i] <= size.width())
                {
                    sketch.drawText(wstring(m_text, last, pos - last), 0., i++ * height, size.width(), height, m_justification);
                }
                else
                {
                    wstring line(m_text, last, pos - last - 1ul);
                    line.append(3ul, L'.');
                    while(ctxt->getTextWidth(m_font, line) > size.width() && line.size() > 3ul)
                    {
                        line.erase(line.size() - 4ul, 1ul);
                    }
                    sketch.drawText(line, 0., i++ * height, size.width(), height, m_justification);
                }
                
                last = pos+1ul;
                pos = m_text.find(L'\n', last);
            }
            if(m_widths[i] <= size.width())
            {
                sketch.drawText(wstring(m_text,  last, npos), 0., i * height, size.width(), height, m_justification);
            }
            else
            {
                wstring line(m_text, last, m_text.size() - 1ul);
                line.append(3ul, L'.');
                while(ctxt->getTextWidth(m_font, line) > size.width() && line.size() > 3ul)
                {
                    line.erase(line.size() - 4ul, 1ul);
                }
                sketch.drawText(line, 0., i * height, size.width(), height, m_justification);
            }
        }
    }
    
    void GuiText::drawWrapped(scGuiView view, Sketch& sketch) const
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            const Size size = getSize();
            ulong i = 0ul, lindex = 0ul;
            size_type last = 0ul, pos = m_text.find(L'\n', 0ul);
            const Rectangle bounds = sketch.getBounds();
            const double height = m_font.getSize() * m_line_space;
            while(pos != npos)
            {
                if(m_widths[lindex] <= size.width())
                {
                    sketch.drawText(wstring(m_text, last, pos - last), 0., i++ * height, size.width(), height, m_justification);
                }
                else
                {
                    wstring next, line(m_text, last, pos - last);
                    size_type width = m_widths[lindex];
                    while(width > size.width() && line.size())
                    {
                        next.insert(0ul, 1ul, line[line.size() - 1ul]);
                        line.pop_back();
                        width = ctxt->getTextWidth(m_font, line);
                        if(width <= size.width())
                        {
                            sketch.drawText(line, 0., i++ * height, size.width(), height, m_justification);
                            line.clear();
                            swap(line, next);
                            width = ctxt->getTextWidth(m_font, line);
                        }
                    }
                    sketch.drawText(line, 0., i++ * height, size.width(), height, m_justification);
                }
                lindex++;
                last = pos+1ul;
                pos = m_text.find(L'\n', last);
            }
            if(m_widths[lindex] <= size.width())
            {
                sketch.drawText(wstring(m_text, last, pos - last), 0., i * height, size.width(), height, m_justification);
            }
            else
            {
                wstring next, line(m_text, last, npos);
                size_type width = m_widths[lindex];
                while(width > size.width() && line.size())
                {
                    next.insert(0ul, 1ul, line[line.size() - 1ul]);
                    line.pop_back();
                    width = ctxt->getTextWidth(m_font, line);
                    if(width <= size.width())
                    {
                        sketch.drawText(line, 0., i++ * height, size.width(), height, m_justification);
                        line.clear();
                        swap(line, next);
                        width = ctxt->getTextWidth(m_font, line);
                    }
                }
                sketch.drawText(line, 0., i * height, size.width(), height, m_justification);
                
            }
        }
    }
    
    void GuiText::draw(scGuiView view, Sketch& sketch) const
    {
        if(!m_text.empty())
        {
            const Size size = getSize();
            sketch.setColor(m_color);
            sketch.setFont(m_font);
            if(m_display_mode == Truncated)
            {
                drawTruncated(view, sketch);
            }
            else if(m_display_mode == TrailPoint)
            {
                drawTrailPoint(view, sketch);
            }
            else
            {
                drawWrapped(view, sketch);
            }
        }
    }
    
    // ================================================================================ //
    //                                     TEXT EDITOR                                  //
    // ================================================================================ //
    
    GuiTextEditor::GuiTextEditor(sGuiContext context) noexcept :
    GuiSketcher(context)
    {
        m_notify_return = UsedAsCharacter;
        m_notify_tab    = UsedAsCharacter;
        m_redraw        = false;
        m_line_space    = 1.;
        m_justification = Font::Justification::TopLeft;
        if(context)
        {
            m_empty_width = context->getTextWidth(m_font, wstring(L" "));
        }
        else
        {
            m_empty_width = 0.5 * m_font.getSize();
        }
    }
    
    GuiTextEditor::~GuiTextEditor() noexcept
    {
        {lock_guard<mutex> guard(m_text_mutex);
            m_text.clear();}
        {lock_guard<mutex> guard(m_lists_mutex);
            m_lists.clear();}
        {lock_guard<mutex> guard(m_carets_mutex);
            m_carets.clear();}
    }
    
    void GuiTextEditor::setFont(Font const& font) noexcept
    {
        if(font != m_font)
        {
            m_font      = font;
            sGuiContext ctxt = getContext();
            if(ctxt)
            {
                m_empty_width = ctxt->getTextWidth(m_font, wstring(L" "));
            }
            redraw();
            m_redraw = false;
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
    
    void GuiTextEditor::setWrapped(const bool wrap) noexcept
    {
        if(wrap != m_wrapped)
        {
            m_wrapped = wrap;
            redraw();
            m_redraw = false;
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
        lock_guard<mutex> guard(m_text_mutex);
        if(!m_text.empty())
        {
            sketch.setColor(m_color);
            sketch.setFont(m_font);
            if(!m_wrapped)
            {
                const Rectangle bounds  = sketch.getBounds();
                const double lineheight = getLineHeight();
                double text_y = 0.;
                size_type last = 0ul, pos = m_text.find(L'\n', 0ul);
                while(pos != npos)
                {
                    sketch.drawText(wstring(m_text, last, pos - last), 0., text_y, bounds.width(), lineheight, m_justification);
                    last = ++pos;
                    pos = m_text.find(L'\n', last);
                    text_y += lineheight;
                }
                sketch.drawText(wstring(m_text, last, npos), 0., text_y, bounds.width(), lineheight, m_justification);
            }
            else
            {
                sGuiContext ctxt = getContext();
                if(ctxt)
                {
                    const Rectangle bounds  = sketch.getBounds();
                    const double lineheight = getLineHeight();
                    double text_y = 0.;
                    size_type last = 0ul, pos = m_text.find(L'\n', 0ul);
                    while(pos != npos)
                    {
                        wstring line(m_text, last, pos - last);
                        double width = ctxt->getTextWidth(m_font, line);
                        if(width <= bounds.width() - m_empty_width)
                        {
                            sketch.drawText(line, 0., text_y, bounds.width() - m_empty_width, lineheight, m_justification);
                            text_y += lineheight;
                        }
                        else
                        {
                            wstring next;
                            while(width > bounds.width() - m_empty_width && line.size())
                            {
                                next.insert(0ul, 1ul, line[line.size() - 1ul]);
                                line.pop_back();
                                width = ctxt->getTextWidth(m_font, line);
                                if(width <= bounds.width() - m_empty_width)
                                {
                                    sketch.drawText(line, 0., text_y, bounds.width() - m_empty_width, lineheight, m_justification);
                                    text_y += lineheight;
                                    line.clear();
                                    swap(line, next);
                                    width = ctxt->getTextWidth(m_font, line);
                                }
                            }
                            sketch.drawText(line, 0., text_y, bounds.width() - m_empty_width, lineheight, m_justification);
                            text_y += lineheight;
                        }
                        last = ++pos;
                        pos = m_text.find(L'\n', last);
                    }
                    wstring line(m_text, last, npos);
                    double width = ctxt->getTextWidth(m_font, line);
                    if(width <= bounds.width() - m_empty_width)
                    {
                        sketch.drawText(line, 0., text_y, bounds.width() - m_empty_width, lineheight, m_justification);
                    }
                    else
                    {
                        wstring next;
                        while(width > bounds.width() - m_empty_width && line.size())
                        {
                            next.insert(0ul, 1ul, line[line.size() - 1ul]);
                            line.pop_back();
                            width = ctxt->getTextWidth(m_font, line);
                            if(width <= bounds.width() - m_empty_width)
                            {
                                sketch.drawText(line, 0., text_y, bounds.width() - m_empty_width, lineheight, m_justification);
                                text_y += lineheight;
                                line.clear();
                                swap(line, next);
                                width = ctxt->getTextWidth(m_font, line);
                            }
                        }
                        sketch.drawText(line, 0., text_y, bounds.width() - m_empty_width, lineheight, m_justification);
                    }
                }
            }
        }
    }
    
    bool GuiTextEditor::receive(const sCaret caret, KeyboardEvent const& event)
    {
        const int code = event.getKeyCode();
        if(code == KeyboardEvent::Key::Escape)
        {
            vector<sListener> listeners(getListeners());
            for(auto it : listeners)
            {
                it->escapeKeyPressed(static_pointer_cast<GuiTextEditor>(shared_from_this()));
            }
            return true;
        }
        else if(code == KeyboardEvent::Key::Return && m_notify_return)
        {
            vector<sListener> listeners(getListeners());
            for(auto it : listeners)
            {
                it->returnKeyPressed(static_pointer_cast<GuiTextEditor>(shared_from_this()));
            }
            return true;
        }
        else if(code == KeyboardEvent::Key::Tab && m_notify_tab)
        {
            vector<sListener> listeners(getListeners());
            for(auto it : listeners)
            {
                it->tabKeyPressed(static_pointer_cast<GuiTextEditor>(shared_from_this()));
            }
            return true;
        }
        else if(event.getKeyCode() == KeyboardEvent::Key::Delete)
        {
            if(caret->empty())
            {
                if(event.hasAlt())
                {
                    moveCaretToNextWord(caret, true);
                }
                if(event.hasCmd())
                {
                    moveCaretToEndLine(caret, true);
                }
                else
                {
                    moveCaretToNextCharacter(caret, true);
                }
            }
            eraseAtCaret(caret);
            return true;
        }
        else if(event.getKeyCode() == KeyboardEvent::Key::Backspace)
        {
            if(caret->empty())
            {
                if(event.hasAlt())
                {
                    moveCaretToPreviousWord(caret, true);
                }
                else if(event.hasCmd())
                {
                    moveCaretToStartLine(caret, true);
                }
                else
                {
                    moveCaretToPreviousCharacter(caret, true);
                }
            }
            eraseAtCaret(caret);
            return true;
        }
        else if(event.getKeyCode() == KeyboardEvent::Key::Return)
        {
            insertAtCaret(caret, wstring(1ul, L'\n'));
            return true;
        }
        else if(event.getKeyCode() == KeyboardEvent::Key::Tab)
        {
            insertAtCaret(caret, wstring(1ul, L'\t'));
            return true;
        }
        else if(event.isCharacter())
        {
            insertAtCaret(caret, wstring(1ul, event.getCharacter()));
            return true;
        }
        else
        {
            const int direction = event.getKeyCode();
            if(direction == KeyboardEvent::Key::Left)
            {
                if(event.hasNoModifier())
                {
                    moveCaretToPreviousCharacter(caret, event.hasShift());
                    return true;
                }
                else if(event.hasAlt())
                {
                    moveCaretToPreviousWord(caret, event.hasShift());
                    return true;
                }
                else if(event.hasCmd())
                {
                    moveCaretToStartLine(caret, event.hasShift());
                    return true;
                }
            }
            else if(direction == KeyboardEvent::Key::Right)
            {
                if(event.hasNoModifier())
                {
                    moveCaretToNextCharacter(caret, event.hasShift());
                    return true;
                }
                else if(event.hasAlt())
                {
                    moveCaretToNextWord(caret, event.hasShift());
                    return true;
                }
                else if(event.hasCmd())
                {
                    moveCaretToEndLine(caret, event.hasShift());
                    return true;
                }
            }
            else if(direction == KeyboardEvent::Key::Up)
            {
                if(event.hasNoModifier())
                {
                    moveCaretToTopCharacter(caret, event.hasShift());
                    return true;
                }
                else if(event.hasAlt())
                {
                    moveCaretToStartLine(caret, event.hasShift());
                    return true;
                }
                else if(event.hasCmd())
                {
                    moveCaretToStart(caret, event.hasShift());
                    return true;
                }
            }
            else if(direction == KeyboardEvent::Key::Down)
            {
                if(event.hasNoModifier())
                {
                    moveCaretToBottomCharacter(caret, event.hasShift());
                    return true;
                }
                else if(event.hasAlt())
                {
                    moveCaretToEndLine(caret, event.hasShift());
                    return true;
                }
                else if(event.hasCmd())
                {
                    moveCaretToEnd(caret, event.hasShift());
                    return true;
                }
            }
        }
        return false;
    }
    
    void GuiTextEditor::setText(wstring const& text) noexcept
    {
        m_text = text;
    }
    
    Size GuiTextEditor::getTextSize(const double limit) const noexcept
    {
        sGuiContext ctxt = getContext();
        lock_guard<mutex> guard(m_text_mutex);
        if(ctxt && !m_text.empty())
        {
            if(limit > m_empty_width)
            {
                const double lineheight = getLineHeight();
                Size size(limit - m_empty_width, 0.);
                size_type last = 0ul, pos = m_text.find(L'\n', 0ul);
                while(pos != npos)
                {
                    wstring line(m_text, last, pos - last);
                    double width = ctxt->getTextWidth(m_font, line);
                    if(width <= size.width())
                    {
                        size.height(size.height() + lineheight);
                    }
                    else
                    {
                        wstring next;
                        while(width > size.width() && line.size())
                        {
                            next.insert(0ul, 1ul, line[line.size() - 1ul]);
                            line.pop_back();
                            width = ctxt->getTextWidth(m_font, line);
                            if(width <= size.width())
                            {
                                size.height(size.height() + lineheight);
                                line.clear();
                                swap(line, next);
                                width = ctxt->getTextWidth(m_font, line);
                            }
                        }
                        if(!line.empty())
                        {
                            size.height(size.height() + lineheight);
                        }
                        
                    }
                    last = ++pos;
                    pos = m_text.find(L'\n', last);
                }
                wstring line(m_text, last, npos);
                double width = ctxt->getTextWidth(m_font, line);
                if(width <= size.width())
                {
                    size.height(size.height() + lineheight);
                }
                else
                {
                    wstring next;
                    while(width > size.width() && line.size())
                    {
                        next.insert(0ul, 1ul, line[line.size() - 1ul]);
                        line.pop_back();
                        width = ctxt->getTextWidth(m_font, line);
                        if(width <= size.width())
                        {
                            size.height(size.height() + lineheight);
                            line.clear();
                            swap(line, next);
                            width = ctxt->getTextWidth(m_font, line);
                        }
                    }
                    if(!line.empty())
                    {
                        wcout << line << endl;
                        size.height(size.height() + lineheight);
                    }
                        }
                return size;
            }
            else
            {
                Size size;
                const double lineheight = getLineHeight();
                size_type last = 0ul, pos = m_text.find(L'\n', 0ul);
                while(pos != npos)
                {
                    size.width(max(ctxt->getTextWidth(m_font, wstring(m_text, last, pos - last)) + m_empty_width, size.width()));
                    size.height(size.height() + lineheight);
                    last = ++pos;
                    pos = m_text.find(L'\n', last);
                }
                size.width(max(ctxt->getTextWidth(m_font, wstring(m_text, last, npos)) + m_empty_width + m_empty_width, size.width()));
                size.height(size.height() + m_font.getSize());
                return size;
            }
        }
        else
        {
            return Size(m_empty_width, m_font.getSize());
        }
    }
    
    void GuiTextEditor::clearText() noexcept
    {
        m_redraw = true;
        m_text.clear();
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
        if(m_redraw)
        {
            redraw();
        }
    }
    
    void GuiTextEditor::addCaret(sCaret caret)
    {
        if(caret)
        {
            lock_guard<mutex> guard(m_carets_mutex);
            m_carets.insert(caret);
            //addChild(caret);
        }
    }
    
    void GuiTextEditor::removeCaret(sCaret caret)
    {
        if(caret)
        {
            lock_guard<mutex> guard(m_carets_mutex);
            m_carets.erase(caret);
            //removeChild(caret);
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
    
    sGuiController GuiTextEditor::GuiTextEditor::createController()
    {
        return make_shared<Controller>(static_pointer_cast<GuiTextEditor>(shared_from_this()));
    }
                
    void GuiTextEditor::eraseAtCaret(sCaret caret)
    {
        if(!caret->empty())
        {
            m_redraw = true;
            {
                lock_guard<mutex> guard(m_text_mutex);
                m_text.erase(caret->first(), caret->second());
            }
            moveCaretToPreviousCharacter(caret, false);
            vector<sListener> listeners(getListeners());
            for(auto it : listeners)
            {
                it->textChanged(static_pointer_cast<GuiTextEditor>(shared_from_this()));
            }
            vector<sCaret> carets(getCarets());
            for(auto it : carets)
            {
                //it->textChanged(static_pointer_cast<GuiTextEditor>(shared_from_this()));
            }
            if(m_redraw)
            {
                redraw();
            }
        }
    }
    
    void GuiTextEditor::insertAtCaret(sCaret caret, wstring const& text) noexcept
    {
        if(!text.empty())
        {
            m_redraw = true;
            {
                lock_guard<mutex> guard(m_text_mutex);
                if(!caret->empty())
                {
                    m_text.erase(caret->first(), caret->second());
                    if(!select) {
                        caret->empty() ? caret->start = caret->caret = max(caret->caret, 1ul) - 1ul : caret->start = caret->caret = min(caret->caret, caret->start);
                    }
                    else if(caret->caret != 0) {
                        --caret->caret;
                    }
                    caret->dist  = npos;
                }
                m_text.insert(caret->caret, text);
            }
            moveCaretToNextCharacter(caret, false);
            vector<sListener> listeners(getListeners());
            for(auto it : listeners)
            {
                it->textChanged(static_pointer_cast<GuiTextEditor>(shared_from_this()));
            }
            vector<sCaret> carets(getCarets());
            for(auto it : carets)
            {
                //it->textChanged(static_pointer_cast<GuiTextEditor>(shared_from_this()));
            }
            if(m_redraw)
            {
                redraw();
            }
        }
    }
    
    void GuiTextEditor::moveCaretToStart(const sCaret caret, const bool select) noexcept
    {
        caret->caret = 0ul;
        if(!select) {
            caret->start = caret->caret;
        }
        caret->dist = npos;
    }
    
    void GuiTextEditor::moveCaretToEnd(const sCaret caret, const bool select) noexcept
    {
        lock_guard<mutex> guard(m_text_mutex);
        caret->caret = m_text.size();
        if(select) {
            caret->start = caret->caret;
        }
        caret->dist = npos;
    }
    
    void GuiTextEditor::moveCaretToNextCharacter(const sCaret caret, const bool select) noexcept
    {
        lock_guard<mutex> guard(m_text_mutex);
        if(!select) {
            caret->empty() ? (caret->start = caret->caret = min(caret->caret+1, m_text.size())) : caret->start = caret->caret = max(caret->caret, caret->start);
        }
        else if(caret->caret != m_text.size()) {
            ++caret->caret;
        }
        caret->dist = npos;
    }
    
    void GuiTextEditor::moveCaretToPreviousCharacter(const sCaret caret, const bool select) noexcept
    {
        lock_guard<mutex> guard(m_text_mutex);
        if(!select) {
            caret->empty() ? caret->start = caret->caret = max(caret->caret, 1ul) - 1ul : caret->start = caret->caret = min(caret->caret, caret->start);
        }
        else if(caret->caret != 0) {
            --caret->caret;
        }
        caret->dist  = npos;
    }
    
    void GuiTextEditor::moveCaretToStartLine(const sCaret caret, const bool select) noexcept
    {
        int tosee;
        lock_guard<mutex> guard(m_text_mutex);
        const size_type line = (caret->caret != 0ul) ? m_text.find_last_of(L'\n', caret->caret - 1ul) : 0ul;
        caret->caret = (line == npos) ? 0ul : min(line + 1ul, m_text.size());
        if(!select) {
            caret->start = caret->caret;
        }
        caret->dist  = npos;
    }
    
    void GuiTextEditor::moveCaretToEndLine(const sCaret caret, const bool select) noexcept
    {
        lock_guard<mutex> guard(m_text_mutex);
        const size_type line = m_text.find_first_of(L'\n', caret->caret);
        caret->caret = (line == npos) ? m_text.size() : line;
        if(!select) {
            caret->start = caret->caret;
        }
        caret->dist  = npos;
    }
    
    void GuiTextEditor::moveCaretToTopCharacter(const sCaret caret, const bool select) noexcept
    {
        lock_guard<mutex> guard(m_text_mutex);
        const size_type current = select ? caret->caret : caret->first();
        size_type line = (current > 0ul) ? m_text.find_last_of(L'\n', current -  1ul) + 1 : 0ul;
        if(line == npos) {
            line = 0ul;
        }
        if(caret->dist == npos) {
            caret->dist = current - (line);
        }
        if(line == 0ul) {
            caret->caret = 0ul;
        }
        else{
            const size_type pline = (line > 2ul) ? m_text.find_last_of(L'\n', max(line -  2ul, 0ul)) + 1 : 0ul;
            caret->caret = min(pline + caret->dist, m_text.find_first_of(L'\n', pline));
        }
        if(!select) {
            caret->start = caret->caret;
        }
    }
    
    void GuiTextEditor::moveCaretToBottomCharacter(const sCaret caret, const bool select) noexcept
    {
        lock_guard<mutex> guard(m_text_mutex);
        int todo;
    }
    
    void GuiTextEditor::moveCaretToNextWord(const sCaret caret, const bool select) noexcept
    {
        lock_guard<mutex> guard(m_text_mutex);
        if(select) {
            caret->caret = caret->second();
        }
        if(m_text[caret->caret] == L' ' || m_text[caret->caret] == L'\n' || m_text[caret->caret] == L'\t') {
            caret->caret = m_text.find_first_not_of(L" \n\t", caret->caret);
        }
        if(caret->caret == npos) {
            caret->caret = m_text.size();
        }
        else {
            caret->caret = m_text.find_first_of(L" \n\t", caret->caret);
            if(caret->caret == npos) {
                caret->caret = m_text.size();
            }
        }
        if(!select) {
            caret->start = caret->caret;
        }
        caret->dist  = npos;
    }
    
    void GuiTextEditor::moveCaretToPreviousWord(const sCaret caret, const bool select) noexcept
    {
        lock_guard<mutex> guard(m_text_mutex);
        if(select) {
            caret->caret = caret->second();
        }
        if(m_text[caret->caret] == L' ' || m_text[caret->caret] == L'\n' || m_text[caret->caret] == L'\t') {
            caret->caret = m_text.find_last_not_of(L" \n\t", caret->caret);
        }
        else if(caret->caret){
            caret->caret = m_text.find_last_not_of(L" \n\t", caret->caret - 1ul);
        }
        if(caret->caret == npos) {
            caret->caret = 0ul;
        }
        else {
            caret->caret = m_text.find_last_of(L" \n\t", caret->caret);
            caret->caret = (caret->caret == npos) ? 0ul : caret->caret + 1ul;
        }
        if(!select) {
            caret->start = caret->caret;
        }
        caret->dist  = npos;
    }

    // ================================================================================ //
    //                              TEXT EDITOR CONTROLLER                              //
    // ================================================================================ //
    
    GuiTextEditor::Controller::Controller(sGuiTextEditor editor) noexcept : GuiController(editor), m_editor(editor),
        m_caret(make_shared<GuiTextEditor::Caret>(editor))
    {
        m_editor->addCaret(m_caret);
    }
        
    GuiTextEditor::Controller::~Controller() noexcept
    {
        m_editor->removeCaret(m_caret);
    }
        
    bool GuiTextEditor::Controller::receive(MouseEvent const& event)
    {
        return true;
    }
    
    bool GuiTextEditor::Controller::receive(KeyboardEvent const& event)
    {
        return m_editor->receive(m_caret, event);
    }
    
    bool GuiTextEditor::Controller::receive(KeyboardFocus const event)
    {
        int decomment_later; // And remove from constructor and destructor
        /*
        if(event == KeyboardFocusIn)
        {
            m_editor->addChild(m_caret);
        }
        else
        {
            m_editor->removeChild(m_caret);
        }
         */
        return true;
    }
        
    // ================================================================================ //
    //                                  TEXT EDITOR CARET                               //
    // ================================================================================ //
    
    void GuiTextEditor::Caret::draw(scGuiView view, Sketch& sketch) const
    {
        if(!empty())
        {
            
        }
        if(m_status)
        {
            /*
            sketch.setColor(m_color);
            sketch.drawLine(0., 0., 0., getSize().height(), 2.);
             */
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
}



