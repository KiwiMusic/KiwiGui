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
        m_notify_return = UsedAsCharacter;
        m_notify_tab    = UsedAsCharacter;
        m_redraw        = false;
        m_line_space    = 1.;
        m_justification = Font::Justification::TopLeft;
        if(context)
        {
            m_empty_charw = context->getTextWidth(m_font, wstring(L" "));
            m_trail_width = context->getTextWidth(m_font, wstring(L"..."));
        }
        else
        {
            m_empty_charw = 0.5 * m_font.getSize();
            m_trail_width = m_empty_charw * 3.;
        }
    }
    
    GuiTextEditor::~GuiTextEditor() noexcept
    {
        m_text.clear();
        lock_guard<mutex> guard(m_lists_mutex);
        m_lists.clear();
    }
    
    void GuiTextEditor::setFont(Font const& font) noexcept
    {
        if(font != m_font)
        {
            m_font      = font;
            sGuiContext ctxt = getContext();
            if(ctxt)
            {
                m_empty_charw = ctxt->getTextWidth(m_font, wstring(L" "));
                m_trail_width = ctxt->getTextWidth(m_font, wstring(L"..."));
            }
            computeLinesWidth();
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
    
    void GuiTextEditor::setDisplayMode(const DisplayMode mode) noexcept
    {
        if(mode != m_mode)
        {
            m_mode = mode;
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
        if(!m_text.empty())
        {
            const Size size = getSize();
            sketch.setColor(m_color);
            sketch.setFont(m_font);
            const double height = m_font.getSize() * m_line_space;
            
            size_type last = 0ul;
            size_type pos = m_text.find(L'\n', 0ul);
            if(m_mode == Trunc)
            {
                ulong i = 0ul;
                while(pos != npos)
                {
                    sketch.drawText(wstring(m_text, last, pos - last), 0., i++ * height, size.width(), height, m_justification);
                    last = pos+1ul;
                    pos = m_text.find(L'\n', last);
                }
                sketch.drawText(wstring(m_text, last, npos), 0., i * height, size.width(), height, m_justification);
            }
            else if(m_mode == Trail)
            {
                sGuiContext ctxt = getContext();
                if(ctxt)
                {
                    ulong i = 0ul;
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
            else
            {
                sGuiContext ctxt = getContext();
                if(ctxt)
                {
                    ulong i = 0ul, lindex = 0ul;
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
        }
    }
    
    bool GuiTextEditor::receive(scGuiView view, KeyboardEvent const& event)
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
        return false;
    }
    
    void GuiTextEditor::setText(wstring const& text) noexcept
    {
        m_text = text;
    }
    
    Size GuiTextEditor::getTextSize(const double limit) const noexcept
    {
        if(!m_widths.empty())
        {
            if(limit > 0.)
            {
                double height = 0;
                for(vector<double>::size_type i = 0; i < m_widths.size(); i++)
                {
                    height += ceil(m_widths[i] / limit) * m_line_space * m_font.getSize();
                }
                return Size(limit, height - m_line_space * m_font.getSize() + m_font.getSize());
            }
            else
            {
                return Size(*max_element(m_widths.begin(), m_widths.end()), (m_widths.size() - 1) * m_line_space * m_font.getSize() + m_font.getSize());
            }
        }
        else
        {
            return Size(0., m_font.getSize());
        }
    }
    
    void GuiTextEditor::clearText() noexcept
    {
        m_redraw = true;
        m_text.clear();
        computeLinesWidth();
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
    
    void GuiTextEditor::erase(sCaret caret)
    {
        if(!caret->empty())
        {
            m_redraw = true;
            m_text.erase(caret->first(), caret->second());
            caret->moveToNextCharacter(m_text, false);
            computeLinesWidth();
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
    }
    
    void GuiTextEditor::addCharacter(sCaret caret, wchar_t character) noexcept
    {
        m_redraw = true;
        if(!caret->empty())
        {
            m_text.erase(caret->first(), caret->second());
        }
        m_text.insert(caret->caret(), 1ul, character);
        caret->moveToNextCharacter(m_text, false);
        computeLinesWidth();
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
    
    void GuiTextEditor::computeLinesWidth() noexcept
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
        {
            m_widths.clear();
            size_type last = 0ul;
            size_type pos = m_text.find(L'\n', 0ul);
            while(pos != npos)
            {
                m_widths.push_back(ctxt->getTextWidth(m_font, wstring(m_text, last, pos - last)) + m_empty_charw);
                last = pos+1ul;
                pos = m_text.find(L'\n', last);
            }
            m_widths.push_back(ctxt->getTextWidth(m_font, wstring(m_text, last, npos)) + m_empty_charw);
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

    // ================================================================================ //
    //                              TEXT EDITOR CONTROLLER                              //
    // ================================================================================ //
    
    GuiTextEditor::Controller::Controller(sGuiTextEditor editor) noexcept : GuiController(editor), m_editor(editor),
        m_caret(make_shared<GuiTextEditor::Caret>(editor))
    {
        m_editor->addListener(m_caret);
        m_editor->addChild(m_caret);
    }
        
    GuiTextEditor::Controller::~Controller() noexcept
    {
        m_editor->removeListener(m_caret);
        m_editor->removeChild(m_caret);
    }
        
    bool GuiTextEditor::Controller::receive(MouseEvent const& event)
    {
        return true;
    }
    
    bool GuiTextEditor::Controller::receive(KeyboardEvent const& event)
    {
        if(!m_editor->receive(getView(), event));
        {
            if(event.getKeyCode() == KeyboardEvent::Key::Delete)
            {
                if(m_caret->empty())
                {
                    if(event.hasAlt())
                    {
                        m_caret->moveToNextWord(m_editor->getText(), true);
                    }
                    if(event.hasCmd())
                    {
                        m_caret->moveToEndLine(m_editor->getText(), true);
                    }
                    else
                    {
                        m_caret->moveToNextCharacter(m_editor->getText(), true);
                    }
                }
                m_editor->erase(m_caret);
                return true;
            }
            else if(event.getKeyCode() == KeyboardEvent::Key::Backspace)
            {
                if(m_caret->empty())
                {
                    if(event.hasAlt())
                    {
                        m_caret->moveToPreviousWord(m_editor->getText(), true);
                    }
                    else if(event.hasCmd())
                    {
                        m_caret->moveToStartLine(m_editor->getText(), true);
                    }
                    else
                    {
                        m_caret->moveToPreviousCharacter(m_editor->getText(), true);
                    }
                }
                m_editor->erase(m_caret);
                return true;
            }
            else if(event.getKeyCode() == KeyboardEvent::Key::Return)
            {
                m_editor->addCharacter(m_caret, L'\n');
                return true;
            }
            else if(event.getKeyCode() == KeyboardEvent::Key::Tab)
            {
                m_editor->addCharacter(m_caret, L'\t');
                return true;
            }
            else if(event.isCharacter())
            {
                m_editor->addCharacter(m_caret, event.getCharacter());
                return true;
            }
            else
            {
                const int direction = event.getKeyCode();
                if(direction == KeyboardEvent::Key::Left)
                {
                    if(event.hasNoModifier())
                    {
                        m_caret->moveToPreviousCharacter(m_editor->getText(), event.hasShift());
                        return true;
                    }
                    else if(event.hasAlt())
                    {
                        m_caret->moveToPreviousWord(m_editor->getText(), event.hasShift());
                        return true;
                    }
                    else if(event.hasCmd())
                    {
                        m_caret->moveToStartLine(m_editor->getText(), event.hasShift());
                        return true;
                    }
                }
                else if(direction == KeyboardEvent::Key::Right)
                {
                    if(event.hasNoModifier())
                    {
                        m_caret->moveToNextCharacter(m_editor->getText(), event.hasShift());
                        return true;
                    }
                    else if(event.hasAlt())
                    {
                        m_caret->moveToNextWord(m_editor->getText(), event.hasShift());
                        return true;
                    }
                    else if(event.hasCmd())
                    {
                        m_caret->moveToEndLine(m_editor->getText(), event.hasShift());
                        return true;
                    }
                }
                else if(direction == KeyboardEvent::Key::Up)
                {
                    if(event.hasNoModifier())
                    {
                        m_caret->moveToTopCharacter(m_editor->getText(), event.hasShift());
                        return true;
                    }
                    else if(event.hasAlt())
                    {
                        m_caret->moveToStartLine(m_editor->getText(), event.hasShift());
                        return true;
                    }
                    else if(event.hasCmd())
                    {
                        m_caret->moveToStart(event.hasShift());
                        return true;
                    }
                }
                else if(direction == KeyboardEvent::Key::Down)
                {
                    if(event.hasNoModifier())
                    {
                        m_caret->moveToBottomCharacter(m_editor->getText(), event.hasShift());
                        return true;
                    }
                    else if(event.hasAlt())
                    {
                        m_caret->moveToEndLine(m_editor->getText(), event.hasShift());
                        return true;
                    }
                    else if(event.hasCmd())
                    {
                        m_caret->moveToEnd(m_editor->getText(), event.hasShift());
                        return true;
                    }
                }
            }
            return false;
        }
        return true;
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
    
    void GuiTextEditor::Caret::computeRendering(wstring const& text) noexcept
    {
        sGuiTextEditor editor = getEditor();
        sGuiContext ctxt = getContext();
        if(ctxt && editor)
        {
            const size_type f = first();
            ulong nlines    = 0;
            size_type start = 0;
            size_type index = 0;
            while(index <= f)
            {
                if(text[index] == L'\n'){
                    nlines++;
                    start = index;
                }
                index++;
            }
            if(!empty())
            {
                const size_type s = second();
                ulong snlines    = 0;
                size_type sstart = 0;
                while(index <= s)
                {
                    if(text[index] == L'\n'){
                        snlines++;
                        sstart = index;
                    }
                    index++;
                }
                setPosition(Point(0., 0.));
                setSize(Size(2., 2));
            }
            else
            {
                setPosition(Point(0., 0.));
                setSize(Size(2., editor->m_font.getSize()));
            }
            redraw();
            
        }
    }
    
    void GuiTextEditor::Caret::selectAll(wstring const& text) noexcept
    {
        m_start = 0ul;
        m_caret = text.size();
        m_dist  = npos;
    }
    
    void GuiTextEditor::Caret::moveToStart(const bool select) noexcept
    {
        select ? m_caret = 0ul : m_start = m_caret = 0ul;
        m_dist  = npos;
    }
    
    void GuiTextEditor::Caret::moveToEnd(wstring const& text, const bool select) noexcept
    {
        select ? m_caret = text.size() : m_start = m_caret = text.size();
        m_dist  = npos;
    }
    
    void GuiTextEditor::Caret::moveToNextCharacter(wstring const& text, const bool select) noexcept
    {
        if(!select) {
            empty() ? (m_start = m_caret = min(m_caret+1, text.size())) : m_start = m_caret = max(m_caret, m_start);
        }
        else if(m_caret != text.size()) {
            ++m_caret;
        }
        m_dist  = npos;
    }
    
    void GuiTextEditor::Caret::moveToPreviousCharacter(wstring const& text, const bool select) noexcept
    {
        if(!select) {
            empty() ? m_start = m_caret = max(m_caret, 1ul) - 1ul : m_start = m_caret = min(m_caret, m_start);
        }
        else if(m_caret != 0) {
            --m_caret;
        }
        m_dist  = npos;
    }
    
    void GuiTextEditor::Caret::moveToStartLine(wstring const& text, const bool select) noexcept
    {
        int tosee;
        const size_type line = (m_caret != 0ul) ? text.find_last_of(L'\n', m_caret-1) : 0ul;
        m_caret = (line == npos) ? 0ul : min(line + 1ul, text.size());
        if(!select) {
            m_start = m_caret;
        }
        m_dist  = npos;
    }
    
    void GuiTextEditor::Caret::moveToEndLine(wstring const& text, const bool select) noexcept
    {
        const size_type line = text.find_first_of(L'\n', m_caret);
        m_caret = (line == npos) ? text.size() : line;
        if(!select) {
            m_start = m_caret;
        }
        m_dist  = npos;
    }
    
    void GuiTextEditor::Caret::moveToTopCharacter(wstring const& text, const bool select) noexcept
    {
        const size_type current = select ? m_caret : first();
        size_type line = (current > 0ul) ? text.find_last_of(L'\n', current -  1ul) + 1 : 0ul;
        if(line == npos) {
            line = 0ul;
        }
        if(m_dist == npos) {
            m_dist = current - (line);
        }
        if(line == 0ul) {
            m_caret = 0ul;
        }
        else{
            const size_type pline = (line > 2ul) ? text.find_last_of(L'\n', max(line -  2ul, 0ul)) + 1 : 0ul;
            m_caret = min(pline + m_dist, text.find_first_of(L'\n', pline));
        }
        if(!select) {
            m_start = m_caret;
        }
    }
    
    void GuiTextEditor::Caret::moveToNextWord(wstring const& text, const bool select) noexcept
    {
        if(select) {
            m_caret = second();
        }
        if(text[m_caret] == L' ' || text[m_caret] == L'\n' || text[m_caret] == L'\t') {
            m_caret = text.find_first_not_of(L" \n\t", m_caret);
        }
        if(m_caret == npos) {
            m_caret = text.size();
        }
        else {
            m_caret = text.find_first_of(L" \n\t", m_caret);
            if(m_caret == npos) {
                m_caret = text.size();
            }
        }
        if(!select) {
            m_start = m_caret;
        }
        m_dist  = npos;
    }
    
    void GuiTextEditor::Caret::moveToPreviousWord(wstring const& text, const bool select) noexcept
    {
        if(select) {
            m_caret = second();
        }
        if(text[m_caret] == L' ' || text[m_caret] == L'\n' || text[m_caret] == L'\t') {
            m_caret = text.find_last_not_of(L" \n\t", m_caret);
        }
        else if(m_caret){
            m_caret = text.find_last_not_of(L" \n\t", m_caret - 1);
        }
        if(m_caret == npos) {
            m_caret = 0ul;
        }
        else {
            m_caret = text.find_last_of(L" \n\t", m_caret);
            m_caret = (m_caret == npos) ? 0ul : m_caret + 1ul;
        }
        if(!select) {
            m_start = m_caret;
        }
        m_dist  = npos;
    }
    
    void GuiTextEditor::Caret::moveToBottomCharacter(wstring const& text, const bool select) noexcept
    {
        //cout << "not available" << endl;
        /*
         const size_type current = select ? m_caret : second();
         size_type line = (current > 0ul) ? text.find_last_of(L'\n', current -  1ul) + 1 : 0ul;
         if(line == npos) {
         line = 0ul;
         }
         if(m_dist == npos) {
         m_dist = current - (line);
         }
         const size_type nline = text.find_first_of(L'\n', current);
         if(nline == npos) {
         m_caret = text.size();
         }
         else {
         const size_type nlineend = text.find_first_of(L'\n', nline + 1ul);
         if(nlineend < nline + 1ul + m_dist){
         cout << "line end" << endl;
         m_caret = nlineend;
         }
         else{
         cout << "line + dist" << endl;
         m_caret = nline + m_dist;
         }
         }
         if(!select) {
         m_start = m_caret;
         }
         */
    }
    
    void GuiTextEditor::Caret::draw(scGuiView view, Sketch& sketch) const
    {
        if(m_status)
        {
            sketch.setColor(m_color);
            sketch.setLineWidth(2.);
            sketch.drawLine(0., 0., 0., getSize().height());
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
    
    void GuiTextEditor::Caret::attrChanged(Attr::sManager manager, sAttr attr)
    {
        if(attr->getName() == Tags::Font)
        {
            ;
        }
    }
    
    void GuiTextEditor::Caret::textChanged(sGuiTextEditor editor)
    {
        ;
    }

}



