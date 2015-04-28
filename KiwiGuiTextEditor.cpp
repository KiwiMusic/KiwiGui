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
    //                                  TEXT EDITOR CARET                               //
    // ================================================================================ //
    
    void GuiTextEditor::Caret::computeRendering(wstring const& text) noexcept
    {
        sGuiContext ctxt = getContext();
        if(ctxt)
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
                setSize(Size(2., m_font.getSize()));
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
        cout << "not available" << endl;
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

    void GuiTextEditor::Caret::attrChanged(Attr::sManager manager, sAttr attr)
    {
        if(attr->getName() == Tags::Font)
        {
            ;
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
        m_caret->setPosition(Point(0., 0.));
        m_caret->setSize(Size(2., m_font.getSize()));
        if(context)
        {
            m_empty_charw = context->getTextWidth(m_font, wstring(L" "));
        }
        else
        {
            m_empty_charw = 0.5 * m_font.getSize();
        }
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
            sGuiContext ctxt = getContext();
            if(ctxt)
            {
                m_empty_charw = ctxt->getTextWidth(m_font, wstring(L" "));
            }
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
        //cout << "receive :" << endl;
        //cout  << event.getKeyCode() << " " << event.getModifiers() << endl;
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
            moveCaret(event);
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
    
    void GuiTextEditor::erase(const bool forward, const bool word) noexcept
    {
        if(!m_text.empty())
        {
            /*
            if(m_caret.isEmpty())            // No selection
            {
                if(!forward && !word)       // Backward/One character
                {
                    
                }
                else if(forward && !word)   // Forward/One character
                {
                    
                }
                else if(!forward && word)   // Backward/Word
                {
                    
                }
                else if(forward && word)    // Forward/Word
                {
                    
                }
            }
            */
        }
        /*
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
        */
    }
    
    void GuiTextEditor::addCharacter(wchar_t character) noexcept
    {
        
        m_formated = false;
        m_text.insert(m_caret->caret(), 1ul, character);
        m_caret->moveToNextCharacter(m_text, false);
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
                m_widths.push_back(ctxt->getTextWidth(m_font, line) + m_empty_charw);
            }
            if(m_text[m_text.size() - 1] == L'\n')
            {
                m_widths.push_back(m_empty_charw);
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
            if(m_caret->caret() <= size + m_lines[i].size())
            {
                sGuiContext ctxt = getContext();
                if(ctxt)
                {
                    const double w = ctxt->getTextWidth(m_font, wstring(m_lines[i].c_str(), max(m_caret->caret() - size, 0ul)));
                    m_caret->setPosition(Point(w, double(i) * m_line_space * m_font.getSize()));
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
    
    void GuiTextEditor::moveCaret(KeyboardEvent const& event) noexcept
    {
        const int direction = event.getKeyCode();
        if(direction == KeyboardEvent::Key::Left)
        {
            if(event.hasNoModifier())
            {
                m_caret->moveToPreviousCharacter(m_text, event.hasShift());
            }
            else if(event.hasAlt())
            {
                m_caret->moveToPreviousWord(m_text, event.hasShift());
            }
            else if(event.hasCmd())
            {
                m_caret->moveToStartLine(m_text, event.hasShift());
            }
            computeCaretPosition();
        }
        else if(direction == KeyboardEvent::Key::Right)
        {
            if(event.hasNoModifier())
            {
                m_caret->moveToNextCharacter(m_text, event.hasShift());
            }
            else if(event.hasAlt())
            {
                m_caret->moveToNextWord(m_text, event.hasShift());
            }
            else if(event.hasCmd())
            {
                m_caret->moveToEndLine(m_text, event.hasShift());
            }
            computeCaretPosition();
        }
        else if(direction == KeyboardEvent::Key::Up)
        {
            if(event.hasNoModifier())
            {
                m_caret->moveToTopCharacter(m_text, event.hasShift());
            }
            else if(event.hasAlt())
            {
                m_caret->moveToStartLine(m_text, event.hasShift());
            }
            else if(event.hasCmd())
            {
                m_caret->moveToStart(event.hasShift());
            }
            computeCaretPosition();
        }
        else if(direction == KeyboardEvent::Key::Down)
        {
            if(event.hasNoModifier())
            {
                m_caret->moveToBottomCharacter(m_text, event.hasShift());
            }
            else if(event.hasAlt())
            {
                m_caret->moveToEndLine(m_text, event.hasShift());
            }
            else if(event.hasCmd())
            {
                m_caret->moveToEnd(m_text, event.hasShift());
            }
            computeCaretPosition();
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



