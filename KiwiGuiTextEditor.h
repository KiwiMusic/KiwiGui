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

#include "KiwiGuiModel.h"

namespace Kiwi
{
    class GuiTextEditor;
    typedef shared_ptr<GuiTextEditor>            sGuiTextEditor;
    typedef weak_ptr<GuiTextEditor>              wGuiTextEditor;
    typedef shared_ptr<const GuiTextEditor>      scGuiTextEditor;
    typedef weak_ptr<const GuiTextEditor>        wcGuiTextEditor;
    
    // ================================================================================ //
    //                                     TEXT EDITOR                                  //
    // ================================================================================ //
    
    //! The text editor...
    /**
     The mtext editor...
     */
    class GuiTextEditor : public GuiSketcher, public GuiMouser, public GuiKeyboarder
    {
    public:
        class Listener
        {
            virtual ~Listener()  {}
            
            virtual void textChanged(sGuiTextEditor editor) {}
            
            virtual void returnKeyPressed(sGuiTextEditor editor) {}
            
            virtual void escapeKeyPressed(sGuiTextEditor editor) {}
            
            virtual void focusLost(sGuiTextEditor editor) {}
        };
        
    private:
        Font    m_font;
        string  m_text;
        bool    m_multi_line;
        bool    m_wrap_word;
        bool    m_notify_return;
        bool    m_notify_tab;
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
        
        //! Sets the display mode of the editor.
        /** The function sets if the text should displayed with multi-lines or single line, if the words should be wrapped.
         @param shouldBeMultiLine If the text should displayed with multi-lines.
         @param shouldWordWrap    If the words should be wrapped
         */
        void setDisplay(const bool shouldBeMultiLine, const bool shouldWordWrap = true);
        
        //! Sets the key notifications of the editor.
        /** The function sets if the return key or the tab key notify the listeners or if the keys should be consider as new characters.
         @param returnNotifies  True if the return key should notify the listeners.
         @param tabNotifies     True if the return tab should notify the listeners.
         */
        void setKeyNotification(const bool returnNotifies, const bool tabNotifies) noexcept;
        
        //! Retrieves if the return key is used as a character.
        /** The function retrieves if the return key is used as a character.
         @return True if the return key is used as a character, otherwise false.
         */
        inline bool isReturnKeyUsedAsCharacter() const noexcept
        {
            return !m_notify_return;
        }
        
        //! Retrieves if the tab key is used as a character.
        /** The function retrieves if the tab key is used as a character.
         @return True if the tab key is used as a character, otherwise false.
         */
        inline bool isTabKeyUsedAsCharacter() const noexcept
        {
            return !m_notify_tab;
        }

        //! The draw method that should be override.
        /** The function shoulds draw some stuff in the sketch.
         @param ctrl    The controller that ask the draw.
         @param sketch  A sketch to draw.
         */
        virtual void draw(scGuiView view, Sketch& sketch) const = 0;
        
        //! The receive method that should be override.
        /** The function shoulds perform some stuff.
         @param event    A mouser event.
         @param ctrl     The controller gives the event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(scGuiView view, MouseEvent const& event) = 0;
        
        //! The receive method that should be override.
        /** The function shoulds perform some stuff.
         @param event    A keyboard event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(scGuiView view, KeyboardEvent const& event) = 0;
        
        //! The receive method that should be override.
        /** The function shoulds perform some stuff.
         @param event    A focus event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(scGuiView view, KeyboardFocus const  event)
        {
            return false;
        }
        
        //! Create the controller.
        /** The function creates a controller depending on the inheritance.
         @return The controller.
         */
        virtual sGuiController createController() = 0;
        
        //! Retrieves the text of the editor.
        /** The function retrieves the text of the editor.
         @return The text.
         */
        inline string getText() const noexcept
        {
            return m_text;
        }
        
        //! Sets the text of the editor.
        /** The function sets the text of the editor.
         @param text The text.
         */
        void setText(string const& text) noexcept;
        
        //! Clears the text of the editor.
        /** The function clears the text of the editor.
         */
        void clearText() noexcept;
        
        //! Retrieves the current position of the caret.
        /** The function retrieves the current position of the caret.
         @return The position of the caret.
         */
        ulong getCaretPosition() const noexcept;
        
        //! Sets the current position of the caret.
        /** The function sets the current position of the caret.
         @param pos The position of the caret.
         */
        void setCaretPosition(ulong pos) noexcept;
    };
}

#endif