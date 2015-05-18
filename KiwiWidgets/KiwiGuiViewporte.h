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

#ifndef __DEF_KIWI_GUI_VIEWPORT__
#define __DEF_KIWI_GUI_VIEWPORT__

#include "KiwiGuiContainer.h"

namespace Kiwi
{    
    // ================================================================================ //
    //                                  GUI VIEW PORT                                   //
    // ================================================================================ //
    
    //! The view port is a model that ...
    /** The view port
     */
    class GuiViewport : public GuiModel
    {
    private:
        class Controller;
        const sGuiScrollBar m_scrollbar_h;
        const sGuiScrollBar m_scrollbar_v;
        sGuiModel           m_content;
        double              m_scrollbar_thickness;
    public:
        
        //! The view port constructor.
        /** The function intialize the model and allocates a container.
         @param context The context.
         */
        GuiViewport(sGuiContext context) noexcept;
        
        //! The view port destructor.
        /** The function frees the memory.
         */
        ~GuiViewport() noexcept;
        
        //! Sets the content model of the view port.
        /** The function sets the content model of the view port.
         @param model The content model.
         */
        void setContent(sGuiModel model) noexcept;
        
        //! Gets the content model of the view port.
        /** The function retrieves the content model of the view port.
         @return The content model.
         */
        inline sGuiModel getContent() const noexcept {return m_content;}
        
        //! Gets the horizontal scrollbar model of the viewport.
        /** The function retrieves the horizontal scrollbar model of the viewport.
         @return The horizontal scrollbar model.
         */
        inline sGuiScrollBar getHorizontalScrollBar() const noexcept {return m_scrollbar_h;}
        
        //! Gets the vertical scrollbar model of the viewport.
        /** The function retrieves the vertical scrollbar model of the viewport.
         @return The vertical scrollbar model.
         */
        inline sGuiScrollBar getVerticalScrollBar() const noexcept {return m_scrollbar_v;}
        
        //! Sets the scrollbars' thickness.
        /** The function sets the scrollbars' thickness.
         @param thickness The thickness.
         */
        void setScrollBarThickness(double thickness) noexcept;
        
        //! Get the scrollbars' thickness.
        /** The function retrieves the scrollbars' thickness.
         @return The scrollbars' thickness.
         */
        inline double getScrollBarThickness() const noexcept {return m_scrollbar_thickness;}
        
        //! Create the controller.
        /** The function creates a controller depending on the inheritance.
         @return The controller.
         */
        sGuiController createController() override;
    };
    
    // ================================================================================ //
    //                              GUI VIEW PORT CONTROLLER                            //
    // ================================================================================ //
    
    class GuiViewport::Controller : public GuiController, public GuiScrollBar::Listener
    {
    private:
        const wGuiViewport          m_viewport;
        sGuiController              m_content;
        GuiScrollBar::sController   m_scrollbar_v;
        GuiScrollBar::sController   m_scrollbar_h;
        
    public:
        
        //! The view port controller constructor.
        /** The function initialize the view port controller.
         @param view port  The view port to control.
         */
        Controller(sGuiViewport viewport) noexcept;
        
        //! The controller destructor.
        /** The function does nothing.
         */
        inline ~Controller() noexcept {;}
        
        //! Gets the view port.
        /** The function retrieves the view port.
         @return The view port.
         */
        inline sGuiViewport getViewport() const noexcept {return m_viewport.lock();}
        
        //! Receives the notification that the bounds of the parent controller changed.
        /** The function notifies that the bounds of the parent controller changed.
         */
        virtual void resized() noexcept override;
        
        //! The mouse receive method that can be override.
        /** The function shoulds perform some stuff.
         @param view    The view that owns the controller.
         @param event   The mouser event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(sGuiView view, MouseEvent const& event) override;
        
        //! The draw method that can be override.
        /** The function shoulds draw some stuff.
         @param view    The view that owns the controller.
         @param sketch  The sketch to draw.
         */
        void draw(sGuiView view, Sketch& sketch) override
        {
            sketch.fillAll(Colors::blue.withAlpha(0.2));
        }
        
        //! Receives the notification that a child has been created.
        /** The function notfies the model that a child has been created.
         @param child The child controller.
         */
        void childCreated(sGuiController child) noexcept override;
        
        //! Receives the notification that a child has been removed.
        /** The function notfies the model that a child has been removed.
         @param child The child controller.
         */
        void childRemoved(sGuiController child) noexcept override;
        
        //! Receives the notification that a scroll bar moved.
        /** The function receivesthe notification that a scroll bar moved.
         @param scrollbar The scroll bar.
         */
        void scrollBarMoved(GuiScrollBar::sController scrollbar) override;
    };
}

#endif


