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
        m_empty_width   = m_font.getCharacterWidth(L' ');
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
            m_font        = font;
            m_empty_width = m_font.getCharacterWidth(L' ');
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
            m_redraw = false;
        }
        else if(justification & Font::Justification::Right && !(m_justification & Font::Justification::Right))
        {
            m_justification = Font::Justification::TopRight;
            redraw();
            m_redraw = false;
        }
        else if(justification & Font::Justification::HorizontallyCentered && !(m_justification & Font::Justification::HorizontallyCentered))
        {
            m_justification = Font::Justification::CentredTop;
            redraw();
            m_redraw = false;
        }
    }
    
    void GuiTextEditor::setLineSpacing(const double factor) noexcept
    {
        if(factor != m_line_space)
        {
            m_line_space = factor;
            redraw();
            m_redraw = false;
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
            m_redraw = false;
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
                sketch.drawText(m_text, view->getBounds().withZeroOrigin(), m_justification, false);
            }
            else
            {
                sketch.drawText(m_text, view->getBounds().withZeroOrigin(), m_justification, true);
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
        lock_guard<mutex> guard(m_text_mutex);
        return m_font.getTextSize(m_text, limit);
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
            caret->setColor(m_color);
            m_carets.insert(caret);
            addChild(caret);
        }
    }
    
    void GuiTextEditor::removeCaret(sCaret caret)
    {
        if(caret)
        {
            lock_guard<mutex> guard(m_carets_mutex);
            m_carets.erase(caret);
            removeChild(caret);
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
    //                                  TEXT EDITOR CARET                               //
    // ================================================================================ //
    
    void GuiTextEditor::setCaretPosition(const sCaret caret, const double limit) const noexcept
    {
        lock_guard<mutex> guard(m_text_mutex);
        if(m_wrapped)
        {
            const size_type linebreak = m_text.find_last_of(L'\n', caret->caret);
            if(linebreak == npos)
            {
                Size offset;
                size_type pos = 0;
                wstring line(1ul, m_text[pos]);
                offset.width(m_font.getLineWidth(line));
                while(pos <= caret->caret)
                {
                    if(offset.width() > limit)
                    {
                        offset.height(offset.height() + m_font.getHeight());
                        line.clear();
                        line += m_text[pos];
                    }
                    line += m_text[++pos];
                    offset.width(m_font.getLineWidth(line));
                }
                //caret->setPosition(Point(offset.width(), offset.height()));
            }
            else
            {
                Size offset = m_font.getTextSize(wstring(m_text, 0ul, linebreak), limit);
                size_type pos = linebreak+1;
                wstring line(1ul, m_text[pos]);
                offset.width(m_font.getLineWidth(line));
                while(pos <= caret->caret)
                {
                    if(offset.width() > limit)
                    {
                        offset.height(offset.height() + m_font.getHeight());
                        line.clear();
                        line += m_text[pos];
                    }
                    line += m_text[++pos];
                    offset.width(m_font.getLineWidth(line));
                }
                //caret->setPosition(Point(offset.width(), offset.height()));
            }
        }
        else
        {
            if(caret->caret == 0ul)
            {
                //caret->setPosition(Point());
            }
            else
            {
                size_type linebreak = m_text.find_last_of(L'\n', caret->caret - ulong(m_text[caret->caret] == L'\n'));
                if(linebreak == npos) {
                    //caret->setPosition(Point(m_font.getLineWidth(wstring(m_text, 0ul, caret->caret)), 0.));
                }
                else {
                    Point pos(m_font.getLineWidth(wstring(m_text, linebreak + 1ul, caret->caret - linebreak - 1ul)), m_font.getHeight());
                    if(linebreak != 0ul) {
                        linebreak = m_text.find_last_of(L'\n', linebreak - 1ul);
                        while(linebreak != npos)
                        {
                            pos.y(pos.y() + m_font.getHeight());
                            if(linebreak == 0ul) {
                                linebreak = npos;
                            }
                            else {
                                linebreak = m_text.find_last_of(L'\n', max(linebreak, 1ul) - 1ul);
                            }
                        }
                    }
                    //caret->setPosition(pos);
                }
            }
            
        }
    }
                
    void GuiTextEditor::eraseAtCaret(const sCaret caret)
    {
        if(!caret->empty())
        {
            m_redraw = true;
            {
                lock_guard<mutex> guard(m_text_mutex);
                m_text.erase(caret->first(), caret->second());
                caret->start = caret->caret = caret->first();
                caret->dist  = npos;
            }
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
    
    void GuiTextEditor::insertAtCaret(const sCaret caret, wstring const& text) noexcept
    {
        if(!text.empty())
        {
            m_redraw = true;
            {
                lock_guard<mutex> guard(m_text_mutex);
                if(!caret->empty())
                {
                    m_text.erase(caret->first(), caret->second() - caret->first());
                    caret->start = caret->caret = caret->first();
                    caret->dist  = npos;
                }
                m_text.insert(caret->caret, text);
            }
            caret->start = caret->caret = min(caret->caret + text.size(), m_text.size());
            
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
        
        cout << "next"<< endl;
        if(caret->empty())
        {
            wcout << m_text[caret->caret - 1ul] << endl;
        }
        else
        {
            cout << caret->second() - caret->first()<< endl;
            wcout << wstring(m_text, caret->first(), caret->second() - caret->first()) << endl;
        }
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
    
    void GuiTextEditor::Controller::draw(sGuiView view, Sketch& sketch)
    {
        const Size viewSize = getView()->getSize();
        m_editor->setCaretPosition(m_caret, viewSize.width());
        m_editor->draw(getView(), sketch);
    }
        
    bool GuiTextEditor::Controller::receive(sGuiView view, MouseEvent const& event)
    {
        return true;
    }
    
    bool GuiTextEditor::Controller::receive(sGuiView view, KeyboardEvent const& event)
    {
        if(m_editor->receive(m_caret, event))
        {
            const Size viewSize = getView()->getSize();
            m_editor->setCaretPosition(m_caret, viewSize.width());
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool GuiTextEditor::Controller::receive(sGuiView view, KeyboardFocus const event)
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
            sketch.setColor(m_color);
            sketch.setLineWidth(2.);
            //sketch.drawLine(0., 0., 0., getSize().height());
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



