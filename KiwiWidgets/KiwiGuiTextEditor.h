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

#include "../KiwiGuiDevice.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                     TEXT EDITOR                                  //
    // ================================================================================ //
    
    //! The virtual text editor
    /**
     The text editor...
     */
    class GuiTextEditor
    {
    public:
        
        class Listener;
        typedef shared_ptr<Listener>    sListener;
        typedef weak_ptr<Listener>      wListener;

    public:
        
        //! Constructor.
        /** The function initializes the text editor.
         @param context The context.
         */
        GuiTextEditor() noexcept {}
        
        //! Destructor.
        /** The function frees the text editor.
         */
        virtual ~GuiTextEditor() noexcept {}
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
}

#endif