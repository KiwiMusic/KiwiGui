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

#ifndef __DEF_KIWI_GUI_SCROLLBAR__
#define __DEF_KIWI_GUI_SCROLLBAR__

#include "KiwiGuiButton.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI SCROOLBAR                                   //
    // ================================================================================ //
    
    //! The scrool bar
    /** The...
     */
    class GuiScrollBar : public GuiSketcher
    {
    public:
        enum Direction
        {
            Vertical    = false,
            Horizontal  = true
        };
    private:
        class Controller;
        
        const Direction m_direction;
        double          m_thumb_time;
        Color           m_thumb_color;
        Color           m_background_color;
        
    public:
        
        //! The button constructor.
        /** The function does nothing.
         @param context     The context.
         @param direction   The direction of the scroll bar.
         @param time        The time in ms that the thumb will be displayed.
         @param tbcolor     The thumb color.
         @param bgcolor     The background color.
         */
        GuiScrollBar(sGuiContext context,
                     const Direction direction,
                     const double time = 150.,
                     Color const& tbcolor = Colors::black,
                     Color const& bgcolor = Colors::transparent) noexcept;
        
        //! The button destructor.
        /** The function does nothing.
         */
        inline virtual ~GuiScrollBar() noexcept {}
        
        //! Gets the direction of the scroll bar.
        /** The function retrieves tthe direction of the scroll bar.
         @return The direction.
         */
        inline Direction getDirection() const noexcept {return m_direction;};
        
        //! Gets the time is ms that the thumb will be displayed after an action.
        /** The function retrieves the time in ms that the thumb will be displayed after an action. If the time is negative, that means that the thumb is always displayed.
         @return The time of display.
         */
        inline double getThumbDisplayTime() const noexcept {return m_thumb_time;};
        
        //! Retreives the background color of the scroll bar.
        /** The function retreives the background color of the scroll bar.
         @return The background color.
         */
        inline Color getBackgroundColor() const noexcept {return m_background_color;}
        
        //! Gets the color of the thumb.
        /** The function retreives the color of the thumb.
         @return The color of the thumb.
         */
        inline Color getThumbColor() const noexcept {return m_thumb_color;}
        
        //! Sets the time in ms that the thumb will be displayed after an action.
        /** The function sets the time in ms that the thumb will be displayed after an action. If the time is negative, the thumb will always be visible.
         @param time The time of display.
         */
        void setThumbDisplayTime(const double time) noexcept;
        
        //! Sets the background color of the scroll bar.
        /** The function sets the background color of the scroll bar.
         @param color The background color.
         */
        void setBackgroundColor(Color const& color) noexcept;
        
        //! Sets the color of the thumb.
        /** The function sets the color of the thumb.
         @param color The color of the thumb.
         */
        void setThumbColor(Color const& color) noexcept;
        
        //! The draw method that should be override.
        /** The function shoulds draw some stuff in the sketch.
         @param ctrl    The controller that ask the draw.
         @param sketch  A sketch to draw.
         */
        void draw(scGuiView view, Sketch& sketch) const override {};
        
    private:
        
        //! Create the controller.
        /** The function creates a controller depending on the inheritance.
         @return The controller.
         */
        sGuiController createController() override;
    };
    
    // ================================================================================ //
    //                              GUI SCROOLBAR CONTROLLER                            //
    // ================================================================================ //
    
    class GuiScrollBar::Controller : public GuiController, public Clock
    {
    public:
        class Listener
        {
        public:
            virtual ~Listener() noexcept {};
            
            //! Receives the notification that a scroll bar has moved.
            /** The function receivesthe notification that a scroll bar has moved.
             @param scrollbar The scroll bar.
             */
            virtual void scrollBarMoved(sGuiScrollBar scrollbar) = 0;
        };
        typedef shared_ptr<Listener>    sListener;
        typedef weak_ptr<Listener>      wListener;
        
    private:
        const sGuiScrollBar     m_scrollbar;
        array<double, 2>        m_limits;
        array<double, 2>        m_range;
        atomic_bool             m_visible;
        
        set<wListener,
        owner_less<wListener>> m_lists;
        mutex                  m_lists_mutex;
    public:
        //! The controller constructor.
        /** The function does nothing.
         */
        Controller(sGuiScrollBar scrollbar) noexcept;
        
        //! The controller destructor.
        /** The function does nothing.
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
        inline bool wantKeyboard() const noexcept override {return false;}
        
        //! Receives if the controller wants actions.
        /** This function retrieves if the controller wants the actions.
         @return true if the controller wants the actions, othrewise false.
         */
        virtual inline bool wantActions() const noexcept override {return false;}
        
        //! Gets the maximum and minimum limits of the thumb.
        /** The function retreives the maximum and minimum limits of the thumb.
         @return The maximum and minimum limits of the thumb.
         */
        inline array<double, 2> getRangeLimits() const noexcept {return m_limits;}
        
        //! Gets the current range of the thumb.
        /** The function retreives the current range of the thumb.
         @return The current range of the thumb.
         */
        inline array<double, 2> getCurrentRange() noexcept {return m_range;};
        
        //! The paint method that can be override.
        /** The function shoulds draw some stuff in the sketch.
         @param view    The view that ask to draw.
         @param sketch  A sketch to draw.
         */
        void draw(sGuiView view, Sketch& sketch) override;
        
        //! The mouse receive method.
        /** The function pass the mouse event to the sketcher if it inherits from mouser.
         @param event    A mouser event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(sGuiView view, MouseEvent const& event) override;
        
        //! Sets the maximum and minimum limits of the thumb.
        /** The function sets the maximum and minimum limits of the thumb.
         @param limits The limits.
         */
        void setRangeLimits(array<double, 2> const& limits) noexcept;
        
        //! Sets the current range of the thumb.
        /** The function sets the current range of the thumb.
         @param range The range.
         */
        void setCurrentRange(array<double, 2> const& range) noexcept;
        
        //! Scrolls the thumb to the start.
        /** The function scrolls the thumb to the start.
         */
        void scrollToStart() noexcept;
        
        //! Scrolls the thumb to the end.
        /** The function scrolls the thumb to the end.
         */
        void scrollToEnd() noexcept;
        
        //! Scrolls the center of the thumb to a position.
        /** The function scrolls the thumb to a position. The position defines the center of the thumb.
         @param position The position of the thumb.
         */
        void scrollTo(const double position) noexcept;
        
        //! The tick function that must be override.
        /** The tick function is called by a clock after a delay.
         */
        void tick() override;
        
        //! Add an instance listener in the binding list of the controller.
        /** The function adds an instance listener in the binding list of the controller.
         @param listener  The listener.
         */
        void addListener(sListener listener);
        
        //! Remove an instance listener from the binding list of the controller.
        /** The function removes an instance listener from the binding list of the controller.
         @param listener  The listener.
         */
        void removeListener(sListener listener);
    };
}

#endif


