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

#include "KiwiGuiResizer.h"

namespace Kiwi
{
    class GuiContainer;
    typedef shared_ptr<GuiContainer>            sGuiContainer;
    typedef weak_ptr<GuiContainer>              wGuiContainer;
    typedef shared_ptr<const GuiContainer>      scGuiContainer;
    typedef weak_ptr<const GuiContainer>        wcGuiContainer;
    
    // ================================================================================ //
    //                                  GUI CONTAINER                                   //
    // ================================================================================ //
    
    //! The container is a simple model that allows to add childs models.
    /** The container allows to adds childs models from other models.
     */
    class GuiContainer : public GuiModel
    {
    public:
        // ================================================================================ //
        //                              GUI CONTAINER CONTROLLER                            //
        // ================================================================================ //
        
        //! The container controller.
        /** The container controller manage a view of a container.
         */
        class Controller : public GuiController
        {
        private:
            const wGuiContainer m_container;
        public:
            //! The container controller constructor.
            /** The function initialize the container controller.
             @param container  The container to control.
             */
            Controller(sGuiContainer container) noexcept : GuiController(container), m_container(container) {};
            
            //! The controller destructor.
            /** The function does nothing.
             */
            inline ~Controller() noexcept {};
            
            //! Gets the container.
            /** The function retrieves the container.
             @return The container.
             */
            inline sGuiContainer getContainer() const noexcept {return m_container.lock();}
            
            //! The draw method that can be override.
            /** The function shoulds draw some stuff.
             @param view    The view that owns the controller.
             @param sketch  The sketch to draw.
             */
            void draw(sGuiView view, Sketch& sketch) override {};
        };
        
        //! The window constructor.
        /** The function does nothing.
         @param context The context.
         */
        GuiContainer(sGuiContext context) noexcept : GuiModel(context) {}
        
        //! The window destructor.
        /** The function does nothing.
         */
        virtual inline ~GuiContainer() noexcept {}
        
        //! Adds a model to the window.
        /** The function adds model to the window that will be displayed inside the window container.
         @param model The model.
         */
        void addContent(sGuiModel model) noexcept {addChild(model);}
        
        //! Remove a model from the window.
        /** The function removes a model from the window container.
         @param model The model.
         */
        void removeContent(sGuiModel model) noexcept {removeChild(model);};
        
        //! Create the controller.
        /** The function creates a controller depending on the inheritance.
         @return The controller.
         */
        sGuiController createController() noexcept override
        {
            return make_shared<Controller>(static_pointer_cast<GuiContainer>(shared_from_this()));
        }
    };
}

#endif


