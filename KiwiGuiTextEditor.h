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

#ifndef __DEF_KIWI_GUI_TEXT_EDITOR__
#define __DEF_KIWI_GUI_TEXT_EDITOR__

#include "KiwiGuiView.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                     TEXT EDITOR                                  //
    // ================================================================================ //
    
    //! The text editor...
    /**
     The text editor...
     */
    class GuiTextEditor : public GuiSketcher, public GuiMouser, public GuiKeyboarder
    {
    public:
        class Caret;
        typedef shared_ptr<Caret>       sCaret;
        typedef weak_ptr<Caret>         wCaret;
        
        class Listener;
        typedef shared_ptr<Listener>    sListener;
        typedef weak_ptr<Listener>      wListener;
        
        enum DisplayMode
        {
            Trunc   = 0,
            Trail   = 1,
            Wrap    = 2
        };
        
        enum BehaviorMode //: bool
        {
            UsedAsCharacter = false,
            Notify          = true
        };
        
    private:
        const sCaret            m_caret;
        Font                    m_font;
        Font::Justification     m_justification;
        double                  m_line_space;
        DisplayMode             m_mode;
        Color                   m_color;
        
        wstring                 m_text;
        vector<wstring>         m_lines;
        vector<double>          m_widths;
        double                  m_empty_charw;
        
        bool                    m_notify_return;
        bool                    m_notify_tab;
        bool                    m_formated;

        set<wListener,
        owner_less<wListener>> m_lists;
        mutex                  m_lists_mutex;
        
        //@internal

        void addCharacter(wchar_t character) noexcept;
        void erase(const bool forward, const bool word) noexcept;
        void getLineWidths() noexcept;
        bool format() noexcept;
        void computeCaretPosition() noexcept;
        
        void moveCaret(KeyboardEvent const& event) noexcept;
        
    public:
        //! Constructor.
        /** The function does nothing.
         @param context The context.
         */
        GuiTextEditor(sGuiContext context) noexcept;
        
        //! Destructor.
        /** The function does nothing.
         */
        virtual ~GuiTextEditor() noexcept;
        
        //! Sets the font of the editor.
        /** The function sets the font of the editor. The size of the text can changed so you should retrieve the it and resize the text editor if needed.
         @param font The new font.
         */
        void setFont(Font const& font) noexcept;
        
        //! Sets the justification of the editor.
        /** The function sets the justification of the editor. The text will always be top justified, only the horizontal position can be changed.
         @param justification The new justification.
         */
        void setJustification(const Font::Justification justification) noexcept;
        
        //! Sets the line spacing of the editor.
        /** The function sets the line spacing of the editor. The line spacing is a factor that multiplies the font height and defines the space between lines. The size of the text can changed so you should retrieve the it and resize the text editor if needed.
         @param factor The line space.
         */
        void setLineSpacing(const double factor) noexcept;
        
        //! Sets the display mode.
        /** The function sets the display mode of the editor. The display mode defines if when the text width exceeds the width of the editor the text should be truncated, the end of the lines should be replaced with trailling points or if the text should be wrapped to a new line. The size of the text can changed so you should retrieve the it and resize the text editor if needed.
         @param mode The display mode.
         */
        void setDisplayMode(const DisplayMode mode) noexcept;
        
        //! Sets the behavior of the return and tab keys of the editor.
        /** The function sets if the return key or the tab key notify the listeners or if the keys should be consider as new characters.
         @param returnNotifies  True if the return key should notify the listeners.
         @param tabNotifies     True if the return tab should notify the listeners.
         */
        inline void setKeyBehavior(const bool returnNotifies, const bool tabNotifies) noexcept
        {
            setReturnKeyBehavior(returnNotifies);
            setTabKeyBehavior(tabNotifies);
        }
        
        //! Sets the behavior of the return key of the editor.
        /** The function sets if the return key notifies the listeners or if the key should be consider as new characters.
         @param notify  True if the return key should notify the listeners.
         */
        void setReturnKeyBehavior(const bool notify) noexcept;
        
        //! Sets the behavior of the tab key of the editor.
        /** The function sets if the tab key notifies the listeners or if the key should be consider as new characters.
         @param notify  True if the tab key should notify the listeners.
         */
        void setTabKeyBehavior(const bool notify) noexcept;
        
        //! Sets the color of the text.
        /** The function sets the color of the text.
         @param color The new color.
         */
        void setColor(Color const& color) noexcept;
        
        //! Sets the text of the editor.
        /** The function sets the text of the editor.
         @param text The text.
         */
        void setText(wstring const& text) noexcept;
        
        //! Clears the text of the editor.
        /** The function clears the text of the editor.
         */
        void clearText() noexcept;
        
        //! Retrieves the font of the editor.
        /** The function retrieves the font of the editor. 
         @return The font.
         */
        inline Font getFont() const noexcept
        {
            return m_font;
        }
        
        //! Retrieves the justification of the editor.
        /** The function retrieves the justification of the editor.
         @return The justification.
         */
        inline Font::Justification getJustification() const noexcept
        {
            return m_justification;
        }
        
        //! Retrieves the line spacing of the editor.
        /** The function retrieves the line spacing of the editor.
         @return The line spacing.
         */
        inline double getLineSpacing() const noexcept
        {
            return m_line_space;
        }
        
        //! Retrieves the display mode of the editor.
        /** The function retrieves the ldisplay mode of the editor.
         @return The display mode.
         */
        inline DisplayMode getDisplayMode() const noexcept
        {
            return m_mode;
        }
        
        //! Retrieves if the return key is used as a character or if it notifies the listeners.
        /** The function retrieves if the return key is used as a character or if it notifies the listeners.
         @return true if the return key is used as a character, otherwise false if it notifies the listeners.
         */
        inline bool getReturnKeyBehavior() const noexcept
        {
            return !m_notify_return;
        }
        
        //! Retrieves if the tab key is used as a character or if it notifies the listeners.
        /** The function retrieves if the tab key is used as a character or if it notifies the listeners.
         @return true if the tab key is used as a character, otherwise false if it notifies the listeners.
         */
        inline bool getTabKeyBehavior() const noexcept
        {
            return !m_notify_tab;
        }
        
        //! Retrieves the text of the editor.
        /** The function retrieves the text of the editor.
         @return The text.
         */
        inline wstring getText() const noexcept
        {
            return m_text;
        }
        
        //! Retrieves the size of the text.
        /** The function retrieves the size of the text.
         @return The size of the text.
         */
        Size getTextSize() const noexcept;

        //! The draw method that should be override.
        /** The function shoulds draw some stuff in the sketch.
         @param ctrl    The controller that ask the draw.
         @param sketch  A sketch to draw.
         */
        void draw(scGuiView view, Sketch& sketch) const override;
        
        //! The receive method that should be override.
        /** The function shoulds perform some stuff.
         @param event    A mouser event.
         @param ctrl     The controller gives the event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(scGuiView view, MouseEvent const& event) override;
        
        //! The receive method that should be override.
        /** The function shoulds perform some stuff.
         @param event    A keyboard event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(scGuiView view, KeyboardEvent const& event) override;
        
        //! The receive method that should be override.
        /** The function shoulds perform some stuff.
         @param event    A focus event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(scGuiView view, KeyboardFocus const event) override;
        
        //! Notify the text editor that it should grab the keayboard focus.
        /** The function notifies the text editor that it should grab the keayboard focus.
         */
        inline void grabFocus() {GuiSketcher::grabFocus();}
        
        //! Notify the manager that the values of an attribute has changed.
        /** The function notifies the manager that the values of an attribute has changed.
         @param attr An attribute.
         @return pass true to notify changes to listeners, false if you don't want them to be notified
         */
        bool notify(sAttr attr) override;
        
        //! Add an instance listener in the binding list of the text editor.
        /** The function adds an instance listener in the binding list of the text editor.
         @param listener  The listener.
         */
        void addListener(sListener listener);
        
        //! Remove an instance listener from the binding list of the text editor.
        /** The function removes an instance listener from the binding list of the text editor.
         @param listener  The listener.
         */
        void removeListener(sListener listener);
    };
    
    //! The listener of the text editor.
    /**
     The listener...
     */
    class GuiTextEditor::Listener
    {
    public:
        //! Destructor.
        /** The function does nothing.
         */
        inline virtual ~Listener() {}
        
        //! Receives the notification that the text changed.
        /** The function notifies the listener that the text changed.
         @param editor The text editor that notifies.
         */
        virtual void textChanged(sGuiTextEditor editor) {}
        
        //! Receives the notification that the return key has been pressed.
        /** The function notifies the listener that the return key has been pressed.
         @param editor The text editor that notifies.
         */
        virtual void returnKeyPressed(sGuiTextEditor editor) {}
        
        //! Receives the notification that the tab key has been pressed.
        /** The function notifies the listener that the tab key has been pressed.
         @param editor The text editor that notifies.
         */
        virtual void tabKeyPressed(sGuiTextEditor editor) {}
        
        //! Receives the notification that the escape key has been pressed.
        /** The function notifies the listener that the escape key has been pressed.
         @param editor The text editor that notifies.
         */
        virtual void escapeKeyPressed(sGuiTextEditor editor) {}
        
        //! Receives the notification that the text editor lose the focus.
        /** The function notifies the listener that the text editor lose the focus.
         @param editor The text editor that notifies.
         */
        virtual void focusLost(sGuiTextEditor editor) {}
    };
    
    //! The caret of the text editor.
    /**
     The caret...
     */
    class GuiTextEditor::Caret : public GuiSketcher, public Attr::Listener, public Clock
    {
    public:
        typedef wstring::size_type size_type;
        static const size_type npos = -1;
    private:
        atomic_bool m_status;
        atomic_bool m_active;
        Color       m_color;
        Font        m_font;
        
        size_type   m_caret;
        size_type   m_start;
        size_type   m_dist;
        
        void computeRendering(wstring const& text) noexcept;
    public:
        
        //! Constructor.
        /** The function does nothing.
         @param context The context.
         */
        inline Caret(sGuiContext context) noexcept : GuiSketcher(context),
        m_status(false),
        m_active(false),
        m_color(Colors::black),
        m_caret(0ul),
        m_start(0ul),
        m_dist(0ul) {}
        
        //! Destructor.
        /** The function does nothing.
         */
        inline  ~Caret() noexcept {}
        
        //! Sets the color of the caret.
        /** The function sets the color of the caret.
         @param color   The new color.
         */
        inline void setColor(Color const& color) noexcept {m_color = color;}
        
        //! Retrievs the color of the caret.
        /** The function retrieves the color of the caret.
         @return The color.
         */
        inline Color getColor() const noexcept {return m_color;}
        
        //! Retrieves if the selection is empty.
        /** The function retrieves if the selection is empty.
         @return true if the selection is empty, otherwise false.
         */
        inline bool empty() const noexcept {return m_caret == m_start;}
        
        //! Retrieves the size of the selection.
        /** The function retrieves the size of the selection.
         @return The size of the selection.
         */
        inline size_type size() const noexcept {return m_caret > m_start ? m_caret - m_start : m_start - m_caret;}
        
        //! Retrieves the first position of the selection.
        /** The function retrieves the first position of the selection.
         @return The first position of the selection.
         */
        inline size_type first() const noexcept {return m_caret > m_start ? m_start : m_caret;}
        
        //! Retrieves the second position of the selection.
        /** The function retrieves the second position of the selection.
         @return The second position of the selection.
         */
        inline size_type second() const noexcept {return m_caret > m_start ? m_caret : m_start;}
        
        //! Retrieves the caret position.
        /** The function retrieves the caret position.
         @return The caret position.
         */
        inline size_type caret() const noexcept {return m_caret;}
        
        //! Retrieves the start position of the selection.
        /** The function retrieves the start position of the selection.
         @return The start position.
         */
        inline size_type start() const noexcept {return m_start;}
        
        //! Selects all the text.
        /** The function selects all the text.
         @param text The text.
         */
        void selectAll(wstring const& text) noexcept;
        
        //! Moves to the begining of the text.
        /** The function moves to the begining of the text (cmd + top).
         @param select true if only the caret move (shift).
         */
        void moveToStart(const bool select) noexcept;
        
        //! Moves to the end of the text.
        /** The function moves to the end of the text (cmd + bottom).
         @param text The text.
         @param select true if only the caret move (shift).
         */
        void moveToEnd(wstring const& text, const bool select) noexcept;
        
        //! Moves to the next character.
        /** The function moves to the next character (right).
         @param text The text.
         @param select true if only the caret move (shift).
         */
        void moveToNextCharacter(wstring const& text, const bool select) noexcept;
        
        //! Moves to the previous character.
        /** The function moves to the previous character (left).
         @param text The text.
         @param select true if only the caret move (shift).
         */
        void moveToPreviousCharacter(wstring const& text, const bool select) noexcept;
        
        //! Moves to the start of the line.
        /** The function moves to the start of the line (cmd + left).
         @param text The text.
         @param select true if only the caret move (shift).
         */
        void moveToStartLine(wstring const& text, const bool select) noexcept;
        
        //! Moves to the start of the line.
        /** The function moves to the start of the line (cmd + right).
         @param text The text.
         @param select true if only the caret move (shift).
         */
        void moveToEndLine(wstring const& text, const bool select) noexcept;
        
        //! Moves to the top character.
        /** The function moves to the top character (up).
         @param text The text.
         @param select true if only the caret move (shift).
         */
        void moveToTopCharacter(wstring const& text, const bool select) noexcept;
        
        //! Moves to the bottom character.
        /** The function moves to the bottom character (down).
         @param text The text.
         @param select true if only the caret move (shift).
         */
        void moveToBottomCharacter(wstring const& text, const bool select) noexcept;
        
        //! Moves to the next word.
        /** The function moves to the next word (alt + right).
         @param text The text.
         @param select true if only the caret move (shift).
         */
        void moveToNextWord(wstring const& text, const bool select) noexcept;
        
        //! Moves to the previous word.
        /** The function moves to the previous word (alt + left).
         @param text The text.
         @param select true if only the caret move (shift).
         */
        void moveToPreviousWord(wstring const& text, const bool select) noexcept;
        
        //! The draw method that should be override.
        /** The function shoulds draw some stuff in the sketch.
         @param ctrl    The controller that ask the draw.
         @param sketch  A sketch to draw.
         */
        void draw(scGuiView view, Sketch& sketch) const override;
        
        //! Receives the notification that a view has been created.
        /** The function notfies the sketcher that a view has been created.
         @param view The view.
         */
        void viewCreated(sGuiView view) noexcept override;
        
        //! Receives the notification that a view has been removed.
        /** The function notfies the sketcher that a view has been removed.
         @param view The view.
         */
        void viewRemoved(sGuiView view) noexcept override;
        
        //! The tick function that must be override.
        /** The tick function is called by a clock after a delay.
         */
        void tick() override;
        
        //! Notify the manager that the values of an attribute has changed.
        /** The function notifies the manager that the values of an attribute has changed.
         @param attr An attribute.
         @return pass true to notify changes to listeners, false if you don't want them to be notified
         */
        bool notify(sAttr attr) {m_status = true; return true;};
        
        //! Receive the notification that an attribute has changed.
        /** The function must be implement to receive notifications when an attribute is added or removed, or when its value, appearance or behavior changes.
         @param manager     The attribute manager.
         @param attr		The attribute that has been modified.
         */
        void attrChanged(Attr::sManager manager, sAttr attr) override;
    };
}

#endif