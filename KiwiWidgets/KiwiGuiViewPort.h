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
    class GuiViewPort : public GuiModel
    {
    private:
        class Controller;
        
        
        const sGuiScrollBar m_scrollbar_h;
        const sGuiScrollBar m_scrollbar_v;
        sGuiModel           m_content;
    public:
        
        //! The view port constructor.
        /** The function intialize the model and allocates a container.
         @param context The context.
         */
        GuiViewPort(sGuiContext context) noexcept;
        
        //! The view port destructor.
        /** The function frees the memory.
         */
        ~GuiViewPort() noexcept;
        
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
        
        //! Create the controller.
        /** The function creates a controller depending on the inheritance.
         @return The controller.
         */
        sGuiController createController() override;
    };
    
    // ================================================================================ //
    //                              GUI VIEW PORT CONTROLLER                            //
    // ================================================================================ //
    
    class GuiViewPort::Controller : public GuiController, public GuiScrollBar::Listener
    {
    private:
        const wGuiViewPort m_view_port;
    public:
        
        //! The view port controller constructor.
        /** The function initialize the view port controller.
         @param view port  The view port to control.
         */
        Controller(sGuiViewPort viewport) noexcept;
        
        //! The controller destructor.
        /** The function does nothing.
         */
        inline ~Controller() noexcept {};
        
        //! Gets the view port.
        /** The function retrieves the view port.
         @return The view port.
         */
        inline sGuiViewPort getViewPort() const noexcept {return m_view_port.lock();}
        
        //! The draw method that can be override.
        /** The function shoulds draw some stuff.
         @param view    The view that owns the controller.
         @param sketch  The sketch to draw.
         */
        void draw(sGuiView view, Sketch& sketch) override {};
        
        //! Receives the notification that a scroll bar moved.
        /** The function receivesthe notification that a scroll bar moved.
         @param scrollbar The scroll bar.
         */
        void scrollBarMoved(GuiScrollBar::sController scrollbar) override;
    };
}

#endif


