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

#ifndef __DEF_KIWI_GUI_KEYBOARD_EVENT__
#define __DEF_KIWI_GUI_KEYBOARD_EVENT__

#include "KiwiGuiMouseEvent.h"

namespace Kiwi
{   
    // ================================================================================ //
    //                                  KEYBOARD EVENT                                  //
    // ================================================================================ //
    
    typedef bool KeyboardFocus;
    static const bool KeyboardFocusIn  = 1;
    static const bool KeyboardFocusOut = 0;
    
	class KeyboardEvent
	{
	public:
		
		enum Modifier : ulong
		{
			Nothing     = 0,
			Shift       = 1,
			Ctrl        = 2,
			Alt         = 4,
			Left        = 16,
			Right       = 32,
			Middle      = 64,
#ifdef __APPLE__
			Cmd          = 8,
			Popup        = Right | Ctrl,
#else
			Cmd          = Ctrl,
			Popup        = Right
#endif
		};
		
		class Key
		{
		public:
			enum Code
			{
#ifdef __APPLE__
				Space = ' ',
				Escape  = 0x1b,
				Return  = 0x0d,
				Tab     = 9,
				Delete  = 0xF728,
				Backspace= 0x7f,
				Insert  = -1,
				Up      = 0xF700,
				Down    = 0xF701,
				Left    = 0xF702,
				Right   = 0xF703
#else
				Space = ' ',
				Escape  = 0x1b,
				Return  = 0x0d,
				Tab     = 9,
				Delete  = 0xF728,
				Backspace= 0x7f,
				Insert  = -1,
				Up      = 0xF700,
				Down    = 0xF701,
				Left    = 0xF702,
				Right   = 0xF703
#endif
			};
		};
		
	private:
		const int		m_keycode;
		const long      m_modifiers;
		const wchar_t   m_character;
	public:
		
        inline explicit KeyboardEvent(const long modifiers, const wchar_t character) noexcept
        : m_keycode(0), m_modifiers(modifiers), m_character(character)
        {
            ;
        }
        
		inline explicit KeyboardEvent(const int keycode, const long modifiers, const wchar_t character) noexcept
		: m_keycode(keycode), m_modifiers(modifiers), m_character(character)
		{
			;
		}
		
		inline explicit KeyboardEvent(const int keycode) noexcept
		: m_keycode(keycode), m_modifiers(Nothing), m_character(0)
		{
			;
		}
		
		inline explicit KeyboardEvent(const int keycode, const long modifiers) noexcept
		: m_keycode(keycode), m_modifiers(modifiers), m_character(0)
		{
			;
		}
		
		//! Creates a copy of another Keyboard.
		KeyboardEvent(const KeyboardEvent& other) noexcept
		: m_keycode(other.getKeyCode()), m_modifiers(other.getModifiers()),
		m_character(other.getCharacter())
		{
			;
		}
		
		~KeyboardEvent() noexcept
		{
			;
		}
		
		//! Compares two Keyboard objects.
		bool operator==(const KeyboardEvent& other) const noexcept
		{
			return m_modifiers == other.getModifiers()
			&& (m_character == other.getCharacter()
				|| m_character == 0
				|| other.getCharacter() == 0)
			&& (m_keycode == other.getKeyCode()
				|| (m_keycode < 256
					&& other.getKeyCode() < 256
					&& towlower(getKeyCode()) == towlower(other.getKeyCode())));
		}
		
		//! Compares two Keyboard objects.
		bool operator!= (const KeyboardEvent& other) const noexcept
		{
			return ! operator== (other);
		}
		
		inline bool isCharacter() const noexcept
		{
			return m_character != 0;
		}
		
		inline wchar_t getCharacter() const noexcept
		{
			return m_character;
		}
		
		inline int getKeyCode() const noexcept
		{
			return m_keycode;
		}
		
		inline bool isAlphabetic() const noexcept
		{
			return iswalpha(m_character);
		}
		
		inline bool isAlphanumeric() const noexcept
		{
			return iswalnum(m_character);
		}
		
		inline bool isNumber() const noexcept
		{
			return iswdigit(m_character);
		}
		
		inline bool isSpace() const noexcept
		{
			return m_character == Key::Code::Space;
		}
		
		inline bool isEscape() const noexcept
		{
			return m_keycode == Key::Escape;
		}
		
		inline bool isReturn() const noexcept
		{
			return m_character == Key::Return;
		}
		
		inline bool isTab() const noexcept
		{
			return m_character == Key::Tab;
		}
		
		inline bool isDelete() const noexcept
		{
			return m_character == Key::Delete;
		}
		
		inline bool isBackspace() const noexcept
		{
			return m_character == Key::Backspace;
		}
		
		inline bool isInsert() const noexcept
		{
			return m_character == Key::Insert;
		}
		
		inline bool hasArrowKey() const noexcept
		{
			return isUp() || isDown() || isLeft() || isRight();
		}
		
		inline bool isUp() const noexcept
		{
			return m_character == Key::Up;
		}
		
		inline bool isDown() const noexcept
		{
			return m_character == Key::Down;
		}
		
		inline bool isLeft() const noexcept
		{
			return m_character == Key::Left;
		}
		
		inline bool isRight() const noexcept
		{
			return m_character == Key::Right;
		}
		
		inline long getModifiers() const noexcept
		{
			return m_modifiers;
		}
		
		inline bool hasNoModifier() const noexcept
		{
			return m_modifiers == Nothing;
		}
		
		inline bool hasShift() const noexcept
		{
			return m_modifiers & Shift;
		}
		
		inline bool hasCtrl() const noexcept
		{
			return m_modifiers & Ctrl;
		}
		
		inline bool hasAlt() const noexcept
		{
			return m_modifiers & Alt;
		}
		
		inline bool hasLeft() const noexcept
		{
			return m_modifiers & Left;
		}
		
		inline bool hasRight() const noexcept
		{
			return m_modifiers & Right;
		}
		
		inline bool hasMiddle() const noexcept
		{
			return m_modifiers & Middle;
		}
		
		inline bool hasCmd() const noexcept
		{
            return m_modifiers & Cmd;
		}
		
		inline bool hasPopup() const noexcept
		{
			return m_modifiers & Popup;
		}
	};
    
    // ================================================================================ //
    //                                     KEYBOARDER                                   //
    // ================================================================================ //
    
    //! The GuiKeyboarder is an abstract class that receive keyboard events.
    /**
     The GuiKeyboarder is an abstract class with a receive method that must be overriden to receive keyboard events.
     */
    class GuiKeyboarder
    {
    public:
        //! Constructor.
        /** The function does nothing.
         */
        constexpr inline GuiKeyboarder() noexcept {};
        
        //! Destructor.
        /** The function does nothing.
         */
        virtual inline ~GuiKeyboarder() noexcept {};
        
        //! The receive method that should be overriden.
        /** The function shoulds perform some stuff.
         @param event    A keyboard event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(scGuiView view, KeyboardEvent const& event) = 0;
        
        //! The receive method that should be overriden.
        /** The function shoulds perform some stuff.
         @param event    A focus event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(scGuiView view, KeyboardFocus const event)
        {
            return false;
        }
    };
}

#endif