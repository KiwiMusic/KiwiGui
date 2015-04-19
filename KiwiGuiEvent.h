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

#ifndef __DEF_KIWI_GUI_KEYBOARDER__
#define __DEF_KIWI_GUI_KEYBOARDER__

#include "KiwiGraphics/KiwiGraphics.h"

namespace Kiwi
{
    class GuiSketcher;
    typedef shared_ptr<GuiSketcher>            sGuiSketcher;
    typedef weak_ptr<GuiSketcher>              wGuiSketcher;
    typedef shared_ptr<const GuiSketcher>      scGuiSketcher;
    typedef weak_ptr<const GuiSketcher>        wcGuiSketcher;
    
    class GuiKeyboarder;
    typedef shared_ptr<GuiKeyboarder>          sGuiKeyboarder;
    typedef weak_ptr<GuiKeyboarder>            wGuiKeyboarder;
    typedef shared_ptr<const GuiKeyboarder>    scGuiKeyboarder;
    typedef weak_ptr<const GuiKeyboarder>      wcGuiKeyboarder;
    
    class GuiMouser;
    typedef shared_ptr<GuiMouser>               sGuiMouser;
    typedef weak_ptr<GuiMouser>                 wGuiMouser;
    typedef shared_ptr<const GuiMouser>         scGuiMouser;
    typedef weak_ptr<const GuiMouser>			wcGuiMouser;
    
    class GuiActionManager;
    typedef shared_ptr<GuiActionManager>        sGuiActionManager;
    typedef weak_ptr<GuiActionManager>          wGuiActionManager;
    typedef shared_ptr<const GuiActionManager>  scGuiActionManager;
    typedef weak_ptr<const GuiActionManager>	wcGuiActionManager;
    
    class GuiController;
    typedef shared_ptr<GuiController>           sGuiController;
    typedef weak_ptr<GuiController>             wGuiController;
    typedef shared_ptr<const GuiController>     scGuiController;
    typedef weak_ptr<const GuiController>       wcGuiController;
    
    class GuiView;
    typedef shared_ptr<GuiView>                 sGuiView;
    typedef weak_ptr<GuiView>                   wGuiView;
    typedef shared_ptr<const GuiView>           scGuiView;
    typedef weak_ptr<const GuiView>             wcGuiView;
    
    class GuiButton;
    typedef shared_ptr<GuiButton>               sGuiButton;
    typedef weak_ptr<GuiButton>                 wGuiButton;
    typedef shared_ptr<const GuiButton>         scGuiButton;
    typedef weak_ptr<const GuiButton>           wcGuiButton;
    
    class GuiContainer;
    typedef shared_ptr<GuiContainer>            sGuiContainer;
    typedef weak_ptr<GuiContainer>              wGuiContainer;
    typedef shared_ptr<const GuiContainer>      scGuiContainer;
    typedef weak_ptr<const GuiContainer>        wcGuiContainer;
    
    class GuiWindow;
    typedef shared_ptr<GuiWindow>               sGuiWindow;
    typedef weak_ptr<GuiWindow>                 wGuiWindow;
    typedef shared_ptr<const GuiWindow>         scGuiWindow;
    typedef weak_ptr<const GuiWindow>           wcGuiWindow;
    
    class GuiContext;
    typedef shared_ptr<GuiContext>              sGuiContext;
    typedef weak_ptr<GuiContext>                wGuiContext;
    typedef shared_ptr<const GuiContext>        scGuiContext;
    typedef weak_ptr<const GuiContext>          wcGuiContext;
    
    class GuiDeviceManager;
    typedef shared_ptr<GuiDeviceManager>        sGuiDeviceManager;
    typedef weak_ptr<GuiDeviceManager>          wGuiDeviceManager;
    typedef shared_ptr<const GuiDeviceManager>  scGuiDeviceManager;
    typedef weak_ptr<const GuiDeviceManager>    wcGuiDeviceManager;
    
    class GuiTextEditor;
    typedef shared_ptr<GuiTextEditor>            sGuiTextEditor;
    typedef weak_ptr<GuiTextEditor>              wGuiTextEditor;
    typedef shared_ptr<const GuiTextEditor>      scGuiTextEditor;
    typedef weak_ptr<const GuiTextEditor>        wcGuiTextEditor;
    
    // ================================================================================ //
    //                                      SKETCH                                      //
    // ================================================================================ //
    
    //! The sketch is almost a full pure virtual class that should be override depending on the graphical implementation.
    /**
     The sketch...
     */
    class Sketch
    {
    public:
        //! Constructor.
        /** The function does nothing.
         */
        constexpr inline Sketch() noexcept
        {
            ;
        }
        
        //! Destrcutor.
        /** The function does nothing.
         */
        inline virtual ~Sketch() noexcept
        {
            ;
        }
        
        //! Retrieve the position.
        /** The function retrieves the position.
         @return The position.
         */
        virtual inline Point getPosition() const noexcept = 0;
        
        //! Retrieve the size.
        /** The function retrieves the size.
         @return The size.
         */
        virtual inline Size getSize() const noexcept = 0;
        
        //! Retrieve the bounds.
        /** The function retrieves the bounds.
         @return The bounds.
         */
        virtual inline Rectangle getBounds() const noexcept = 0;
        
        //! Set the color.
        /** The function sets the color that now will be used by the sketch.
         @param color The color.
         */
        virtual void setColor(Color const& color) = 0;
        
        //! Set the font.
        /** The sets the font that now will be used by the sketch.
         @param font The font.
         */
        virtual void setFont(Font const& font) = 0;
        
        //! Fill the sketch with the current color.
        /** The function fills the entire sketch with the current color.
         */
        virtual void fillAll() const = 0;
        
        //! Fill the sketch with a color.
        /** The function fills the entire sketch with a color.
         */
        inline virtual void fillAll(Color const& color)
        {
            setColor(color);
            fillAll();
        }
        
        //! Draw a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param rect The rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        inline virtual void drawText(wstring const& text, Rectangle const& rect, Font::Justification j, bool truncated = false) const
        {
            wstring_convert<codecvt_utf8<wchar_t>> cv;
            drawText(string(cv.to_bytes(text)), rect.x(), rect.y(), rect.width(), rect.height(), j, truncated);
        }
        
        //! Draws a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param x The abscissa of the rectangle.
         @param y The ordinate of the rectangle.
         @param w The width of the rectangle.
         @param h The height of the rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        inline virtual void drawText(wstring const& text, double x, double y, double w, double h, Font::Justification j, bool truncated = false) const
        {
            wstring_convert<codecvt_utf8<wchar_t>> cv;
            drawText(cv.to_bytes(text), x, y, w, h, j, truncated);
        }
        
        //! Draw a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param rect The rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        inline virtual void drawText(string const& text, Rectangle const& rect, Font::Justification j, bool truncated = false) const
        {
            drawText(text, rect.x(), rect.y(), rect.width(), rect.height(), j, truncated);
        }
        
        //! Draws a line of text within a rectangle.
        /** The function draws a line of text within a rectangle.
         @param text The text.
         @param x The abscissa of the rectangle.
         @param y The ordinate of the rectangle.
         @param w The width of the rectangle.
         @param h The height of the rectangle.
         @param j The justification.
         @param truncated If the text should be truncated if it goes out the boundaries.
         */
        virtual void drawText(string const& text, double x, double y, double w, double h, Font::Justification j, bool truncated = false) const = 0;
        
        //! Fill a path.
        /** The function fills a path.
         @param path The path.
         */
        virtual void fillPath(Path const& path) const = 0;
        
        //! Draw a path.
        /** The function draws a patcher.
         @param path The path.
         @param thickness The thickness of the parth.
         */
        virtual void drawPath(const Path& path, double const thickness) const = 0;
        
        virtual void drawLine(double x1, double y1, double x2, double y2, double thickness) const = 0;
        
        virtual void drawRectangle(double x, double y, double w, double h, double thickness, double rounded = 0.) const = 0;
        
        virtual void drawRectangle(Rectangle const& rect, double thickness, double rounded = 0.)
        {
            drawRectangle(rect.x(), rect.y(), rect.width(), rect.height(), thickness, rounded);
        }
        
        virtual void fillRectangle(double x, double y, double w, double h, double rounded = 0.) const = 0;
        
        virtual void fillRectangle(Rectangle const& rect, double rounded = 0.)
        {
            drawRectangle(rect.x(), rect.y(), rect.width(), rect.height(), rounded);
        }
        
        virtual void drawEllipse(double x, double y, double width, double height, double thickness = 0.) const = 0;
        
        virtual void drawEllipse(Rectangle const& rect, double thickness = 0.) const
        {
            drawEllipse(rect.x(), rect.y(), rect.width(), rect.height(), thickness);
        }
        
        virtual void fillEllipse(double x, double y, double width, double height) const = 0;
        
        virtual void fillEllipse(Rectangle const& rect) const
        {
            fillEllipse(rect.x(), rect.y(), rect.width(), rect.height());
        }
    };
    
    // ================================================================================ //
    //                                      MOUSE EVENT                                 //
    // ================================================================================ //
    
    //! The mouse event.
    /**
     The mouse event.
     */
    class MouseEvent
    {
    public:
        //! The mouse event type.
        /**
         The mouse event type.
         */
        enum Type : unsigned int
        {
            Unknown     = 0,
            Enter       = 1,
            Leave       = 2,
            Move        = 3,
            Drag        = 4,
            Down        = 5,
            Up          = 6,
            DoubleClick = 7,
            Wheel       = 8
        };
        
        //! The mouse event modifiers.
        /**
         The mouse event modifiers.
         */
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
        
    private:
        
        const Type      m_type;
        const Point     m_position;
        const Point		m_position_down;
        const Point     m_wheel_offset;
        const ulong     m_modifiers;
        const bool		m_was_clicked;
        const ulong     m_nclicks;
        
    public:
        //! Constructor.
        /** The function initializes a mouse event.
         @param type    The type of mouse event.
         @param x       The abscissa of mouse event.
         @param y       The ordinate of mouse event.
         @param mod     The modifiers of the mouse event.
         */
        MouseEvent(const Type type, const int x, const int y, const ulong mod) noexcept;
        
        //! Constructor.
        /** The function initializes a mouse event.
         @param type    The type of mouse event.
         @param position The position of mouse event.
         @param mod     The modifiers of the mouse event.
         */
        MouseEvent(const Type type, Point const& position, const ulong mod) noexcept;
        
        //! Constructor.
        /** The function initializes a mouse event.
         @param type    The type of mouse event.
         @param x       The abscissa of mouse event.
         @param y       The ordinate of mouse event.
         @param mod     The modifiers of the mouse event.
         @param wheel_x The wheel abscissa of mouse event.
         @param wheel_y The wheel ordinate of mouse event.
         @param clicked If the mouse event was already clicked.
         @param down_x  The last down abscissa of mouse event.
         @param down_y  The last down ordinate of mouse event.
         @param nclicks the number of multiclicks.
         */
        MouseEvent(const Type type, const int x, const int y, const ulong mod, const double wheel_x, const double wheel_y, const bool clicked, const int down_x, const int down_y, const ulong nclicks) noexcept;
        
        //! Constructor.
        /** The function initializes a mouse event.
         @param type    The type of mouse event.
         @param position The position of mouse event.
         @param mod     The modifiers of the mouse event.
         @param wheel   The wheel offset of mouse event.
         @param clicked If the mouse event was already clicked.
         @param down_position The last down position of mouse event.
         @param nclicks the number of multiclicks.
         */
        MouseEvent(const Type type, Point const& position, const ulong mod, Point const& wheel, const bool clicked, Point const& down_position, const ulong nclicks) noexcept;
        
        //! Destructor.
        /** The function does nothing.
         */
        virtual ~MouseEvent() noexcept;
        
        //! Retrieve the type of the mouse event.
        /** The function retrieves the type of the mouse event.
         @return The type of mouse event.
         */
        inline Type getType() const noexcept
        {
            return m_type;
        }
        
        //! Retrieve if the type of the mouse event is unknown.
        /** The function retrieves if the type of the mouse event is unknown.
         @return true if the type of the mouse event is unknown, otherwise false.
         */
        inline bool isUnknown() const noexcept
        {
            return m_type == Unknown;
        }
        
        //! Retrieve if the type of the mouse event is enter.
        /** The function retrieves if the type of the mouse event is enter.
         @return true if the type of the mouse event is enter, otherwise false.
         */
        inline bool isEnter() const noexcept
        {
            return m_type == Enter;
        }
        
        //! Retrieve if the type of the mouse event is leave.
        /** The function retrieves if the type of the mouse event is leave.
         @return true if the type of the mouse event is leave, otherwise false.
         */
        inline bool isLeave() const noexcept
        {
            return m_type == Leave;
        }
        
        //! Retrieve if the type of the mouse event is move.
        /** The function retrieves if the type of the mouse event is move.
         @return true if the type of the mouse event is move, otherwise false.
         */
        inline bool isMove() const noexcept
        {
            return m_type == Move;
        }
        
        //! Retrieve if the type of the mouse event is drag.
        /** The function retrieves if the type of the mouse event is drag.
         @return true if the type of the mouse event is drag, otherwise false.
         */
        inline bool isDrag() const noexcept
        {
            return m_type == Drag;
        }
        
        //! Retrieve if the type of the mouse event is down.
        /** The function retrieves if the type of the mouse event is down.
         @return true if the type of the mouse event is down, otherwise false.
         */
        inline bool isDown() const noexcept
        {
            return m_type == Down;
        }
        
        //! Retrieve if the type of the mouse event is up.
        /** The function retrieves if the type of the mouse event is up.
         @return true if the type of the mouse event is up, otherwise false.
         */
        inline bool isUp() const noexcept
        {
            return m_type == Up;
        }
        
        //! Retrieve if the type of the mouse event is double click.
        /** The function retrieves if the type of the mouse event is double click.
         @return true if the type of the mouse event is double click, otherwise false.
         */
        inline bool isDoubleClick() const noexcept
        {
            return m_type == DoubleClick;
        }
        
        //! Retrieve if the type of the mouse event is wheel.
        /** The function retrieves if the type of the mouse event is wheel.
         @return true if the type of the mouse event is wheel, otherwise false.
         */
        inline bool isWheel() const noexcept
        {
            return m_type == Wheel;
        }
        
        //! Retrieve if the abscissa of the mouse event.
        /** The function retrieves the abscissa of the mouse event.
         @return The abscissa of the mouse event.
         */
        inline double getX() const noexcept
        {
            return m_position.x();
        }
        
        //! Retrieve if the ordinate of the mouse event.
        /** The function retrieves the ordinate of the mouse event.
         @return The ordinate of the mouse event.
         */
        inline double getY() const noexcept
        {
            return m_position.y();
        }
        
        //! Retrieve if the position of the mouse event.
        /** The function retrieves the position of the mouse event.
         @return The position of the mouse event.
         */
        inline Point getPosition() const noexcept
        {
            return m_position;
        }
        
        //! Retrieve if the lastest abscissa of the mouse event.
        /** The function retrieves the lastest down abscissa of the mouse event.
         @return The lastest down abscissa of the mouse event.
         */
        inline double getDownX() const noexcept
        {
            return m_position_down.x();
        }
        
        //! Retrieve if the lastest ordinate of the mouse event.
        /** The function retrieves the lastest down ordinate of the mouse event.
         @return The lastest down ordinate of the mouse event.
         */
        inline double getDownY() const noexcept
        {
            return m_position_down.y();
        }
        
        //! Retrieve if the lastest position of the mouse event.
        /** The function retrieves the lastest down position of the mouse event.
         @return The lastest down position of the mouse event.
         */
        inline Point getDownPosition() const noexcept
        {
            return m_position_down;
        }
        
        //! Retrieve if the abscissa wheel offset of the mouse event.
        /** The function retrieves the abscissa wheel offset of the mouse event.
         @return The abscissa wheel offset of the mouse event.
         */
        inline double getWheelOffsetX() const noexcept
        {
            return m_wheel_offset.x();
        }
        
        //! Retrieve if the ordinate wheel offset of the mouse event.
        /** The function retrieves the ordinate wheel offset of the mouse event.
         @return The ordinate wheel offset of the mouse event.
         */
        inline double getWheelOffsetY() const noexcept
        {
            return m_wheel_offset.y();
        }
        
        //! Retrieve if the wheel offset of the mouse event.
        /** The function retrieves the wheel offset of the mouse event.
         @return The wheel offset of the mouse event.
         */
        inline Point getWheelOffset() const noexcept
        {
            return m_wheel_offset;
        }
        
        //! Retrieve the modifiers pressed during the mouse event.
        /** The function retrieves the modifiers pressed during the mouse event.
         @return The modifiers pressed during the mouse event.
         */
        inline ulong getModifiers() const noexcept
        {
            return m_modifiers;
        }
        
        //! Retrieve if no modifiers has been pressed during the mouse event.
        /** The function retrieves if no modifiers has been pressed during the mouse event.
         @return True if no modifiers has been pressed during the mouse event, otherwise false.
         */
        inline bool hasNoModifier() const noexcept
        {
            return m_modifiers == Nothing;
        }
        
        //! Retrieve if the shift modifier has been pressed during the mouse event.
        /** The function retrieves if the shift modifier has been pressed during the mouse event.
         @return True if the shift modifier has been pressed during the mouse event, otherwise false.
         */
        inline bool hasShift() const noexcept
        {
            return m_modifiers & Shift;
        }
        
        //! Retrieve if the control modifier has been pressed during the mouse event.
        /** The function retrieves if the control modifier has been pressed during the mouse event.
         @return True if the control modifier has been pressed during the mouse event, otherwise false.
         */
        inline bool hasCtrl() const noexcept
        {
            return m_modifiers & Ctrl;
        }
        
        //! Retrieve if the alt modifier has been pressed during the mouse event.
        /** The function retrieves if the alt modifier has been pressed during the mouse event.
         @return True if the alt modifier has been pressed during the mouse event, otherwise false.
         */
        inline bool hasAlt() const noexcept
        {
            return m_modifiers & Alt;
        }
        
        //! Retrieve if the left button has been pressed during the mouse event.
        /** The function retrieves if the left button has been pressed during the mouse event.
         @return True if the left button has been pressed during the mouse event, otherwise false.
         */
        inline bool hasLeft() const noexcept
        {
            return m_modifiers & Left;
        }
        
        //! Retrieve if the right button has been pressed during the mouse event.
        /** The function retrieves if the right button has been pressed during the mouse event.
         @return True if the right button has been pressed during the mouse event, otherwise false.
         */
        inline bool hasRight() const noexcept
        {
            return m_modifiers & Right;
        }
        
        //! Retrieve if the middle button has been pressed during the mouse event.
        /** The function retrieves if the middle button has been pressed during the mouse event.
         @return True if the middle button has been pressed during the mouse event, otherwise false.
         */
        inline bool hasMiddle() const noexcept
        {
            return m_modifiers & Middle;
        }
        
        //! Retrieve if the command modifier has been pressed during the mouse event.
        /** The function retrieves if the command modifier has been pressed during the mouse event.
         @return True if the command modifier has been pressed during the mouse event, otherwise false.
         */
        inline bool hasCmd() const noexcept
        {
            return m_modifiers & Cmd;
        }
        
        //! Retrieve if the popup modifier has been pressed during the mouse event.
        /** The function retrieves if the popup modifier has been pressed during the mouse event.
         @return True if the popup modifier has been pressed during the mouse event, otherwise false.
         */
        inline bool hasPopup() const noexcept
        {
            return m_modifiers & Popup;
        }
        
        //! Retrieve if the popup modifier has been pressed during the mouse event.
        /** The function retrieves if the popup modifier has been pressed during the mouse event.
         @return True if the popup modifier has been pressed during the mouse event, otherwise false.
         */
        inline bool wasClicked() const noexcept
        {
            return m_was_clicked;
        }
        
        //! Retrieve the number of multiclicks.
        /** The function retrieves the number of multiclicks.
         @return The number of multiclicks.
         */
        inline ulong getNumberOfClicks() const noexcept
        {
            return m_nclicks;
        }
        
        //! Set that the mouse can be move or dragged without limits.
        /** The function sets that the mouse can be move or dragged without limits.
         @param isLimited true if the mouse can be dragged without limits, otherwise false.
         @param visibleUntilLimits true if the mouse should be visible until the limit of the screen are reached.
         */
        virtual void setMouseUnlimited(bool isLimited, bool visibleUntilLimits = false) const
        {
            ;
        }
    };
    
    // ================================================================================ //
    //                                  KEYBOARD EVENT                                  //
    // ================================================================================ //
    
    typedef bool KeyboardFocus;
    static const bool KeyboardFocusIn  = 0;
    static const bool KeyboardFocusOut = 1;
    
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
    //                                      ACTION                                      //
    // ================================================================================ //
    
    //! The action class...
    /**
     The action...
     */
    class Action
    {
    public:
        typedef ulong Code;
        const KeyboardEvent   event;
        const string          name;
        const string          description;
        const string          category;        
    public:
        //! Constructor.
        /** The function initializes the members values.
         @param event       The type of action.
         @param name        The name of the action.
         @param description The description of the action.
         @param category    The category of the action.
         */
        Action(KeyboardEvent const& event, string const& name, string const& description, string const& category) noexcept;
        
        //! Constructor.
        /** The copy constructor.
         */
        Action(Action const& other) noexcept;
        
        //! Constructor.
        /** The default constructor.
         */
        Action() noexcept;
        
        //! Destructor.
        /** The function does nothing.
         */
        ~Action() noexcept;
    };
    
}

#endif