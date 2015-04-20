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

#ifndef __DEF_KIWI_GUI_DEVICE__
#define __DEF_KIWI_GUI_DEVICE__

#include "KiwiGuiContext.h"

namespace Kiwi
{
    //! The gui device manager owns the informations....
    /**
     The gui device manager
     */
    class GuiDeviceManager
    {
	public:
		
		//! The constructor.
		/** The function does nothing.
		 */
        constexpr inline GuiDeviceManager() noexcept {}
		
		//! The destructor.
        /** The function does nothing.
         */
        inline virtual ~GuiDeviceManager() noexcept {}
        
        void initialize() const noexcept
        {
            Font::setAvailableFonts(getSystemFonts());
        }
        
        //! Create a view.
        /** The function creates a view for a controller.
         @param ctrl The controller linked with the view.
         @return The view.
         */
        virtual sGuiView createView(sGuiController ctrl) noexcept = 0;
        
        //! Retrieves the mouse absolute position.
        /** The function retrieves the mouse absolute position.
         @return The mouse absolute position.
         */
        virtual Point getMousePosition() const noexcept = 0;
        
        //! Retrieves the screen bounds.
        /** The function retrieves the screen bounds for a point. Since there can be several screens, the point determines wichs screen to select.
         @param pt The point.
         @return The screen bounds.
         */
        virtual Rectangle getScreenBounds(Point const& pt) const noexcept = 0;
        
        //! Retrieves the size of a text.
        /** The function the size of a text depending on a font.
         @param font The font.
         @param text The text.
         @return The size of the text.
         */
        virtual Size getTextSize(Font const& font, string const& text) const noexcept
        {
            wstring_convert<codecvt_utf8_utf16<wchar_t>,wchar_t> cv;
            return getTextSize(font, cv.from_bytes(text));
        }
        
        //! Retrieves the size of a text.
        /** The function the size of a text depending on a font.
         @param font The font.
         @param text The text.
         @return The size of the text.
         */
        virtual Size getTextSize(Font const& font, wstring const& text) const noexcept = 0;
        
    private:
        
        //! Retrieves all the fonts from the system.
        /** The function retrieves all the fonts from the system.
         @return A vector of fonts.
         */
        virtual vector<Font> getSystemFonts() const noexcept = 0;
        
    };
}

#endif


