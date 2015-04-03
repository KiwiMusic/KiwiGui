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

#ifndef __DEF_KIWI_GUI_OBJECT__
#define __DEF_KIWI_GUI_OBJECT__

#include "../KiwiGuiEvents/KiwiGuiEvents.h"

namespace Kiwi
{
    class GuiLink;
    typedef shared_ptr<GuiLink>                 sGuiLink;
    typedef weak_ptr<GuiLink>					wGuiLink;
    typedef shared_ptr<const GuiLink>           scGuiLink;
    typedef weak_ptr<const GuiLink>				wcGuiLink;
    
    class GuiObject;
    typedef shared_ptr<GuiObject>               sGuiObject;
    typedef weak_ptr<GuiObject>                 wGuiObject;
    typedef shared_ptr<const GuiObject>         scGuiObject;
    typedef weak_ptr<const GuiObject>           wcGuiObject;
    
    class GuiPatcher;
    typedef shared_ptr<GuiPatcher>				sGuiPatcher;
    typedef weak_ptr<GuiPatcher>                wGuiPatcher;
    typedef shared_ptr<const GuiPatcher>        scGuiPatcher;
    typedef weak_ptr<const GuiPatcher>			wcGuiPatcher;
    
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
    
    //! The gui box...
    /**
     The gui box
     */
	class GuiObject : virtual public Sketcher
    {
	private:
		const wGuiPatcher       m_patcher;
        
    protected:
        const sAttrLong         m_number_of_inlets;
        const sAttrLong         m_number_of_outlets;
        const sAttrString       m_text;
        
        const sAttrPoint        m_presentation_position;
        const sAttrSize         m_presentation_size;
        const sAttrBool         m_hidden;
        const sAttrBool         m_presentation;
        const sAttrBool         m_ignoreclick;
        
    public:
		//! The constructor.
		/** The constructor.
		 @param page The gui page.
		 */
		GuiObject(sGuiPatcher page) noexcept;
		
		//! The destructor.
		/** The destructor.
		 */
		virtual ~GuiObject();
		
		//! Retrieve the gui patcher.
		/** This function retrieves the gui patcher.
		 @return The gui patcher.
		 */
		inline sGuiPatcher getPatcher() const noexcept
		{
			return m_patcher.lock();
		}
        
        //! Retrieve the text attribute value of the object.
        /** The function retrieves the text attribute value of the object.
         @return The text attribute value of the object.
         */
        inline string getText() const noexcept
        {
            return m_text->getValue();
        }
        
        //! Retrieve the number of inlet of the object.
        /** The function retrieves the number of inlet of the object.
         @return The number of inlet of the object.
         */
        inline ulong getNumberOfInlets() const noexcept
        {
            return m_number_of_inlets->getValue();
        }
        
        //! Retrieve the number of outlet of the object.
        /** The function retrieves the number of outlet of the object.
         @return The number of outlet of the object.
         */
        inline ulong getNumberOfOutlets() const noexcept
        {
            return m_number_of_outlets->getValue();
        }
        
        //! Retrieves if the object should be hidden when the patcher is locked.
        /** The function retrieves if the object should be hidden when the patcher is locked.
         @return True if the object should be hidden when the patcher is locked, false otherwise.
         */
        inline bool isHiddenOnLock() const noexcept
        {
            return m_hidden->getValue();
        }
        
        //! Retrieve if the object should be displayed in presentation.
        /** The function retrieves if the object should be displayed in presentation.
         @return True if the object should be displayed in presentation, otherwise false.
         */
        inline bool isIncludeInPresentation() const noexcept
        {
            return m_presentation->getValue();
        }
        
        //! Retrieve the "ignoreclick" attribute value of the object.
        /** The function retrieves the "ignoreclick" attribute value of the object.
         @return The "ignoreclick" attribute value of the object.
         */
        inline bool getIgnoreClick() const noexcept
        {
            return m_ignoreclick->getValue();
        }
        
        //! Retrieve the position of the object when the patcherview is in presentation mode.
        /** The function retrieves the position of the object when the patcherview is in presentation mode.
         @return The position of the object when the patcherview is in presentation mode.
         */
        inline Point getPresentationPosition() const noexcept
        {
            return m_presentation_position->getValue();
        }
        
        //! Retrieve the size of the object when the patcherview is in presentation mode.
        /** The function retrieves the size of the object when the patcherview is in presentation mode.
         @return The size of the object when the patcherview is in presentation mode.
         */
        inline Size getPresentationSize() const noexcept
        {
            return m_presentation_size->getValue();
        }
        
        //! Retrieve the bounds of the object when the patcherview is in presentation mode.
        /** The function retrieves the bounds of the object when the patcherview is in presentation mode.
         @return The bounds of the object when the patcherview is in presentation mode.
         */
        inline Rectangle getPresentationBounds() const noexcept
        {
            return Rectangle(m_presentation_position->getValue(), m_presentation_size->getValue());
        }
    };
}

#endif


