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

#ifndef __DEF_KIWI_GUI_CONTAINER__
#define __DEF_KIWI_GUI_CONTAINER__

#include "KiwiGuiButton.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI CONTAINER                                   //
    // ================================================================================ //
    
    //! The container is a sketcher that facilitates the positioning of sub sketchers.
    /** The container allows to creates...
     */
    class GuiContainer : public GuiSketcher
    {
    public:
        struct Cell
        {
            ulong row;
            ulong column;
        };
        
    private:
        map<Cell, ulong> m_disposition;
        
    public:
        
        //! The window constructor.
        /** The function does nothing.
         @param context The context.
         */
        GuiContainer(sGuiContext context) noexcept;
        
        //! The window destructor.
        /** The function does nothing.
         */
        virtual ~GuiContainer() noexcept;
        
        //! The draw method that should be override.
        /** The function shoulds draw some stuff in the sketch.
         @param ctrl    The controller that ask the draw.
         @param sketch  A sketch to draw.
         */
        void draw(scGuiView view, Sketch& sketch) const override {};
        
        //! Adds a sketcher to the window.
        /** The function adds sketcher to the window that will be displayed inside the window container.
         @param sketcher The sketcher.
         */
        void addContent(sGuiSketcher sketcher) noexcept;
        
        //! Remove a sketcher from the window.
        /** The function removes a sketcher from the window container.
         @param sketcher The sketcher.
         */
        void removeContent(sGuiSketcher sketcher) noexcept;
    };
    
    // ================================================================================ //
    //                                  GUI VIEW PORT                                   //
    // ================================================================================ //
    
    //! The view port is a sketcher that ...
    /** The view port
     */
    class GuiViewPort : public GuiSketcher
    {
    private:
        const sGuiContainer m_container;
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
}

#endif


