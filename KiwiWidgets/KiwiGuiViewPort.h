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
    
    //! The view port is a sketcher that ...
    /** The view port
     */
    class GuiViewPort : public GuiSketcher
    {
    private:
        class Controller;
        
        const sGuiContainer m_container;
        const sGuiScrollBar m_scrollbar_h;
        const sGuiScrollBar m_scrollbar_v;
        sGuiSketcher        m_content;
    public:
        
        //! The view port constructor.
        /** The function intialize the sketcher and allocates a container.
         @param context The context.
         */
        GuiViewPort(sGuiContext context) noexcept;
        
        //! The view port destructor.
        /** The function frees the memory.
         */
        ~GuiViewPort() noexcept;
        
        //! Sets the content sketcher of the view port.
        /** The function sets the content sketcher of the view port.
         @param sketcher The content sketcher.
         */
        void setContent(sGuiSketcher sketcher) noexcept;
        
        //! Gets the content sketcher of the view port.
        /** The function retrieves the content sketcher of the view port.
         @return The content sketcher.
         */
        inline sGuiSketcher getContent() const noexcept
        {
            return m_content;
        }
        
        //! Sets the content sketcher position.
        /** The function sets the content sketcher position.
         @param position The position of the content.
         */
        void setContentPosition(Point const& position);
        
        //! Gets the content sketcher position.
        /** The function retrieves the content sketcher position.
         @return The position of the content.
         */
        inline Point getContentPosition() const noexcept
        {
            return m_container->getPosition();
        }
        
        //! The draw method that should be override.
        /** The function shoulds draw some stuff in the sketch.
         @param ctrl    The controller that ask the draw.
         @param sketch  A sketch to draw.
         */
        void draw(scGuiView view, Sketch& sketch) const override {sketch.fillAll(Colors::white);}
        
        //! Notify the manager that the values of an attribute has changed.
        /** The function notifies the manager that the values of an attribute has changed.
         @param attr An attribute.
         @return pass true to notify changes to listeners, false if you don't want them to be notified
         */
        bool notify(sAttr attr) override;
    };
    
    class GuiViewPort::Controller : public GuiController
    {
        
    };
}

#endif


