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

#ifndef __DEF_KIWI_GUI_BUTTON__
#define __DEF_KIWI_GUI_BUTTON__

#include "KiwiGuiView.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI BUTTON                                      //
    // ================================================================================ //
    
    //! The button is a simple graphical button.
    /** The button is a simple graphical button.
     */
    class GuiButton : public GuiSketcher, public GuiMouser
    {
    public:
        
        class Listener
        {
        public:
            virtual ~Listener() noexcept {};
            
            //! Receives the notfivation that a button has been pressed.
            /** The function receives the notfivation that a button has been pressed.
             @param The button.
             */
            virtual void buttonPressed(sGuiButton button) = 0;
        };
        
        typedef shared_ptr<Listener>    sListener;
        typedef weak_ptr<Listener>      wListener;
        
    private:
        set<wListener,
        owner_less<wListener>> m_lists;
        mutex                  m_lists_mutex;
        Color                  m_color;
    public:
        
        //! The button constructor.
        /** The function does nothing.
         @param context The context.
         */
        GuiButton(sGuiContext context, Color const& color = Colors::white) noexcept;
        
        //! The button destructor.
        /** The function does nothing.
         */
        virtual ~GuiButton() noexcept;
        
        //! Retreives the color of the button.
        /** The function retreives the color of the button.
         @return The color.
         */
        inline Color getColor() const noexcept
        {
            return m_color;
        }
        
        //! Sets the color of the button.
        /** The function sets the color of the button.
         @param color The color.
         */
        void setColor(Color const& color) noexcept;
        
        //! The draw method that should be override.
        /** The function shoulds draw some stuff in the sketch.
         @param ctrl    The controller that ask the draw.
         @param sketch  A sketch to draw.
         */
        virtual void draw(scGuiView view, Sketch& sketch) const override;
        
        //! The receive method that should be override.
        /** The function shoulds perform some stuff.
         @param event    A mouser event.
         @param ctrl     The controller gives the event.
         @return true if the class has done something with the event otherwise false
         */
        virtual bool receive(scGuiView view, MouseEvent const& event) override;
        
        //! Add an instance listener in the binding list of the attribute.
        /** The function adds an instance listener in the binding list of the attribute.
         @param listener  The listener.
         */
        void addListener(sListener listener);
        
        //! Remove an instance listener from the binding list of the attribute.
        /** The function removes an instance listener from the binding list of the attribute.
         @param listener  The listener.
         */
        void removeListener(sListener listener);
    };
}

#endif


