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
    //                                      TEXT                                        //
    // ================================================================================ //
    
    class GuiText : public GuiSketcher
    {
    public:
        enum DisplayMode
        {
            Truncated   = 0,
            TrailPoint  = 1,
            Wrapped     = 2
        };
        
        typedef wstring::size_type size_type;
        static const size_type npos = -1;
        
    private:
        Font                    m_font;
        Font::Justification     m_justification;
        double                  m_line_space;
        DisplayMode             m_display_mode;
        Color                   m_color;
        
        wstring                 m_text;
        vector<double>          m_widths;
        double                  m_empty_width;
        double                  m_trail_width;
        atomic_bool             m_redraw;
        
        //@internal
        void computeLinesWidth() noexcept;
        void drawTruncated(scGuiView view, Sketch& sketch) const;
        void drawTrailPoint(scGuiView view, Sketch& sketch) const;
        void drawWrapped(scGuiView view, Sketch& sketch) const;
    public:
        
        //! Constructor.
        /** The function initializes the text.
         @param context The context.
         */
        GuiText(sGuiContext context) noexcept;
        
        //! Destructor.
        /** The function frees the text.
         */
        virtual ~GuiText() noexcept;
        
        //! Sets the font of the text.
        /** The function sets the font of the text. The size of the text can changed so you should retrieve the it and resize the text if needed.
         @param font The new font.
         */
        void setFont(Font const& font) noexcept;
        
        //! Sets the justification of the text.
        /** The function sets the justification of the text.
         @param justification The new justification.
         */
        void setJustification(const Font::Justification justification) noexcept;
        
        //! Sets the line spacing of the text.
        /** The function sets the line spacing of the text. The line spacing is a factor that multiplies the font height and defines the space between lines. The height of the text can change so you should retrieve it and resize the text if needed.
         @param factor The line space.
         */
        void setLineSpacing(const double factor) noexcept;
        
        //! Sets the display mode.
        /** The function sets the display mode of the text. The display mode defines if the text should be truncated at the end of the lines or if it should be replaced with trailling points or if should be wrapped to a new line. The height of the text can change so you should retrieve the size and resize the text if needed.
         @param mode The display mode.
         */
        void setDisplayMode(const DisplayMode mode) noexcept;
        
        //! Sets the color of the text.
        /** The function sets the color of the text.
         @param color The new color.
         */
        void setColor(Color const& color) noexcept;
        
        //! Sets the string of the text.
        /** The function sets the string of the text.
         @param text The string.
         */
        void setString(wstring const& text) noexcept;
        
        //! Sets the string of the text.
        /** The function sets the string of the text.
         @param text The string.
         */
        void setString(wstring&& text) noexcept;
        
        //! Clears the string of the text.
        /** The function clears the string of the text.
         */
        void clearString() noexcept;
        
        //! Retrieves the font of the text.
        /** The function retrieves the font of the text.
         @return The font.
         */
        inline Font getFont() const noexcept
        {
            return m_font;
        }
        
        //! Retrieves the justification of the text.
        /** The function retrieves the justification of the text.
         @return The justification.
         */
        inline Font::Justification getJustification() const noexcept
        {
            return m_justification;
        }
        
        //! Retrieves the line spacing of the text.
        /** The function retrieves the line spacing of the text.
         @return The line spacing.
         */
        inline double getLineSpacing() const noexcept
        {
            return m_line_space;
        }
        
        //! Retrieves the display mode of the text.
        /** The function retrieves the display mode of the text.
         @return The display mode.
         */
        inline DisplayMode getDisplayMode() const noexcept
        {
            return m_display_mode;
        }
        
        //! Retrieves the color of the text.
        /** The function retrieves the color of the text.
         @return The color.
         */
        inline Color getColor() const noexcept
        {
            return m_color;
        }
        
        //! Retrieves the string of the text.
        /** The function retrieves the string of the text.
         @return The string.
         */
        inline wstring getString() const noexcept
        {
            return m_text;
        }
        
        //! The draw method that should be override.
        /** The function shoulds draw some stuff in the sketch.
         @param ctrl    The controller that ask the draw.
         @param sketch  A sketch to draw.
         */
        void draw(scGuiView view, Sketch& sketch) const override;
        
    };
    
    // ================================================================================ //
    //                                     TEXT EDITOR                                  //
    // ================================================================================ //
    
    //! The text editor...
    /**
     The text editor...
     */
    class GuiTextEditor : public GuiSketcher
    {
    public:
        
        class Listener;
        typedef shared_ptr<Listener>    sListener;
        typedef weak_ptr<Listener>      wListener;
        
        enum BehaviorMode //: bool
        {
            UsedAsCharacter = false,
            Notify          = true
        };
        
        typedef wstring::size_type size_type;
        static const size_type npos = -1;
        
    private:
        class Caret;
        typedef shared_ptr<Caret>       sCaret;
        typedef weak_ptr<Caret>         wCaret;
        
        class Controller;
        typedef shared_ptr<Controller>  sController;
        typedef weak_ptr<Controller>    wController;
        
        Font                    m_font;
        Font::Justification     m_justification;
        double                  m_line_space;
        bool                    m_wrapped;
        Color                   m_color;
        
        wstring                 m_text;
        mutable mutex           m_text_mutex;
        double                  m_empty_width;
        atomic_bool             m_redraw;
        
        bool                    m_notify_return;
        bool                    m_notify_tab;

        set<wListener,
        owner_less<wListener>>  m_lists;
        mutex                   m_lists_mutex;
        
        set<wCaret,
        owner_less<wCaret>>     m_carets;
        mutex                   m_carets_mutex;        
    public:
        
        //! Constructor.
        /** The function initializes the text editor.
         @param context The context.
         */
        GuiTextEditor(sGuiContext context) noexcept;
        
        //! Destructor.
        /** The function frees the text editor.
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
        
        //! Sets if the text should be wrapped.
        /** The function sets if the text should be wrapped.
         @param wrap True if the text should be wrapped, otherwise false.
         */
        void setWrapped(const bool wrap) noexcept;
        
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
        
        //! Retrieves the height of a line.
        /** The function retrieves the height of a line.
         @return The height.
         */
        inline double getLineHeight() const noexcept
        {
            return m_line_space * m_font.getSize();
        }
        
        //! Retrieves if the text is wrapped within the limits of the text editor.
        /** The function retrieves if the text is wrapped within the limits of the text editor.
         @return True if the text is wrapped, otherwise false.
         */
        inline bool isTextWrapped() const noexcept
        {
            return m_wrapped;
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
        /** The function retrieves the size of the text. If the width limit is superior to zero, the function computes the size of the text like if the lines were wrapped.
         @param limit The width limit.
         @return The size of the text.
         */
        Size getTextSize(const double limit = 0.) const noexcept;

        //! The draw method that should be override.
        /** The function shoulds draw some stuff in the sketch.
         @param ctrl    The controller that ask the draw.
         @param sketch  A sketch to draw.
         */
        void draw(scGuiView view, Sketch& sketch) const override;
        
        //! Notify the text editor that it should grab the keayboard focus.
        /** The function notifies the text editor that it should grab the keayboard focus.
         */
        inline void grabFocus() {GuiSketcher::grabFocus();}
        
        //! Adds a listener in the binding list of the text editor.
        /** The function adds a listener in the binding list of the text editor.
         @param listener  The listener.
         */
        void addListener(sListener listener);
        
        //! Removes a listener from the binding list of the text editor.
        /** The function removes a listener from the binding list of the text editor.
         @param listener  The listener.
         */
        void removeListener(sListener listener);
        
    private:
        
        //! Adds a caret in the binding list of the text editor.
        /** The function adds the caret in the binding list of the text editor.
         @param caret  The caret.
         */
        void addCaret(sCaret caret);
        
        //! Removes a caret from the binding list of the text editor.
        /** The function removes the caret from the binding list of the text editor.
         @param caret  The caret.
         */
        void removeCaret(sCaret caret);
        
        //! The text editor keybaord receive method.
        /** The function adds character on move the caret.
         @param caret The caret.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(const sCaret caret, KeyboardEvent const& event);
        
        //! Erases the text at the caret.
        /** The function erases the caret's selection and notifies the other carets.
         @param caret  The caret.
         */
        void eraseAtCaret(sCaret caret);
        
        //! Insert text at the caret.
        /** The function inserts text at the caret's selection and notifies the other carets.
         @param caret  The caret.
         @param text   The text.
         */
        void insertAtCaret(sCaret caret, wstring const& text) noexcept;
        
        //! Moves the caret to the begining of the text.
        /** The function moves the caret to the begining of the text (cmd + top).
         @param caret The caret.
         @param select true if only the caret move (shift).
         */
        void moveCaretToStart(const sCaret caret, const bool select) noexcept;
        
        //! Moves the caret the caret to the end of the text.
        /** The function moves the caret to the end of the text (cmd + bottom).
         @param caret The caret.
         @param select true if only the caret move (shift).
         */
        void moveCaretToEnd(const sCaret caret, const bool select) noexcept;
        
        //! Moves the caret to the next character.
        /** The function moves the caret to the next character (right).
         @param caret The caret.
         @param select true if only the caret move (shift).
         */
        void moveCaretToNextCharacter(const sCaret caret, const bool select) noexcept;
        
        //! Moves the caret to the previous character.
        /** The function moves the caret to the previous character (left).
         @param caret The caret.
         @param select true if only the caret move (shift).
         */
        void moveCaretToPreviousCharacter(const sCaret caret, const bool select) noexcept;
        
        //! Moves the caret to the start of the line.
        /** The function moves the caret to the start of the line (cmd + left).
         @param caret The caret.
         @param select true if only the caret move (shift).
         */
        void moveCaretToStartLine(const sCaret caret, const bool select) noexcept;
        
        //! Moves the caret to the start of the line.
        /** The function moves the caret to the start of the line (cmd + right).
         @param caret The caret.
         @param select true if only the caret move (shift).
         */
        void moveCaretToEndLine(const sCaret caret, const bool select) noexcept;
        
        //! Moves the caret to the top character.
        /** The function moves the caret to the top character (up).
         @param caret The caret.
         @param select true if only the caret move (shift).
         */
        void moveCaretToTopCharacter(const sCaret caret, const bool select) noexcept;
        
        //! Moves the caret to the bottom character.
        /** The function moves the caret to the bottom character (down).
         @param caret The caret.
         @param select true if only the caret move (shift).
         */
        void moveCaretToBottomCharacter(const sCaret caret, const bool select) noexcept;
        
        //! Moves the caret to the next word.
        /** The function moves the caret to the next word (alt + right).
         @param caret The caret.
         @param select true if only the caret move (shift).
         */
        void moveCaretToNextWord(const sCaret caret, const bool select) noexcept;
        
        //! Moves the caret to the previous word.
        /** The function moves the caret to the previous word (alt + left).
         @param caret The caret.
         @param select true if only the caret move (shift).
         */
        void moveCaretToPreviousWord(const sCaret caret, const bool select) noexcept;
        
        //! Create the controller.
        /** The function creates a controller depending on the inheritance.
         @return The controller.
         */
        sGuiController createController() override;
        
        //! Gets the listeners.
        /** The functions gets the liteners and removes the deprecated ones.
         @return The listeners.
         */
        inline vector<sListener> getListeners() noexcept
        {
            vector<sListener> lists;
            lock_guard<mutex> guard(m_lists_mutex);
            for(auto it = m_lists.begin(); it != m_lists.end();)
            {
                sListener l = (*it).lock();
                if(l)
                {
                    lists.push_back(l); ++it;
                }
                else
                {
                    it = m_lists.erase(it);
                }
            }
            return lists;
        }
        
        //! Gets the carets.
        /** The functions gets the carets removes the deprecated ones.
         @return The carets.
         */
        inline vector<sCaret> getCarets() noexcept
        {
            vector<sCaret> carets;
            lock_guard<mutex> guard(m_carets_mutex);
            for(auto it = m_carets.begin(); it != m_carets.end();)
            {
                sCaret l = (*it).lock();
                if(l)
                {
                    carets.push_back(l); ++it;
                }
                else
                {
                    it = m_carets.erase(it);
                }
            }
            return carets;
        }
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
    class GuiTextEditor::Caret : public GuiSketcher, public Clock
    {
    public:
        typedef wstring::size_type size_type;
        static const size_type npos = -1;
    private:
        friend class GuiTextEditor;
        
        atomic_bool             m_status;
        atomic_bool             m_active;
        Color                   m_color;
        
        size_type               caret;
        size_type               start;
        size_type               dist;
    public:
        
        //! Constructor.
        /** The function initialize a default caret for the text editor.
         @param context The context.
         */
        inline Caret(sGuiTextEditor editor) noexcept : GuiSketcher(editor->getContext()),
        m_status(false),
        m_active(false),
        m_color(Colors::black),
        caret(0ul),
        start(0ul),
        dist(0ul) {}
        
        //! Destructor.
        /** The function does nothing.
         */
        inline  ~Caret() noexcept {}
        
        //! Sets the color of the caret.
        /** The function sets the color of the caret.
         @param color   The new color.
         */
        inline void setColor(Color const& color) noexcept {m_color = color;}
        
        //! Retrieves the color of the caret.
        /** The function retrieves the color of the caret.
         @return The color.
         */
        inline Color getColor() const noexcept {return m_color;}
        
        //! Retrieves if the selection is empty.
        /** The function retrieves if the selection is empty.
         @return true if the selection is empty, otherwise false.
         */
        inline bool empty() const noexcept {return caret == start;}
        
        //! Retrieves the size of the selection.
        /** The function retrieves the size of the selection.
         @return The size of the selection.
         */
        inline size_type size() const noexcept {return caret > start ? caret - start : start - caret;}
        
        //! Retrieves the first position of the selection.
        /** The function retrieves the first position of the selection.
         @return The first position of the selection.
         */
        inline size_type first() const noexcept {return caret > start ? start : caret;}
        
        //! Retrieves the second position of the selection.
        /** The function retrieves the second position of the selection.
         @return The second position of the selection.
         */
        inline size_type second() const noexcept {return caret > start ? caret : start;}
        
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
    };
    
    
    // ================================================================================ //
    //                              TEXT EDITOR CONTROLLER                              //
    // ================================================================================ //
    
    //! The controller of the text editor.
    /**
     The controller...
     */
    class GuiTextEditor::Controller : public GuiController
    {
    private:
        const sGuiTextEditor        m_editor;
        const GuiTextEditor::sCaret m_caret;
    public:
        
        //! The controller constructor.
        /** The function initializes the controller of the text editor.
         @param editor The text editor.
         */
        Controller(sGuiTextEditor editor) noexcept;
        
        //! The controller destructor.
        /** The function deletes the text editor.
         */
        ~Controller() noexcept;
        
        //! Receives if the controller wants the mouse.
        /** This function retrieves if the controller wants the mouse.
         @return true if the controller wants the mouse, othrewise false.
         */
        inline bool wantMouse() const noexcept override {return true;}
        
        //! Receives if the controller wants the keyboard.
        /** This function retrieves if the controller wants the keyboard.
         @return true if the controller wants the keyboard, othrewise false.
         */
        inline bool wantKeyboard() const noexcept override {return true;}
        
        //! Receives if the controller wants actions.
        /** This function retrieves if the controller wants the actions.
         @return true if the controller wants the actions, othrewise false.
         */
        inline bool wantActions() const noexcept override {return false;}
        
        //! The mouse receive method.
        /** The function pass the mouse event to the sketcher if it inherits from mouser.
         @param event    A mouser event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(MouseEvent const& event) override;
        
        //! The keyboard receive method.
        /** The function pass the keyboard event to the sketcher if it inherits from keyboarder.
         @param event    A keyboard event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(KeyboardEvent const& event) override;
        
        //! The keyboard focus receive method.
        /** The function pass the keyboard event to the sketcher if it inherits from keyboarder.
         @param event    A focus event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(KeyboardFocus const event)  override;
        
        
    };
}

#endif