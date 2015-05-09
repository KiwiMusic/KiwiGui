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

#include "KiwiGuiScrollBar.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                  GUI CONTAINER                                   //
    // ================================================================================ //
    
    //! The container is a simple model that allows to add childs models.
    /** The container allows to adds childs models from other models.
     */
    class GuiContainer : public GuiModel
    {
    private:
        class Controller;
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
        
        //! Adds a model to the window.
        /** The function adds model to the window that will be displayed inside the window container.
         @param model The model.
         */
        void addContent(sGuiModel model) noexcept;
        
        //! Remove a model from the window.
        /** The function removes a model from the window container.
         @param model The model.
         */
        void removeContent(sGuiModel model) noexcept;
        
        sGuiController createController() noexcept override
        {
            return nullptr;
        }
    };
}

#endif


