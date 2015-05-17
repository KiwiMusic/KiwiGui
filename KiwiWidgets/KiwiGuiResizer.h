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

#ifndef __DEF_KIWI_GUI_RESIZER__
#define __DEF_KIWI_GUI_RESIZER__

#include "KiwiguiScrollBar.h"

namespace Kiwi
{
    class GuiResizer;
    typedef shared_ptr<GuiResizer>      sGuiResizer;
    typedef weak_ptr<GuiResizer>        wGuiResizer;
    typedef shared_ptr<const GuiResizer>scGuiResizer;
    typedef weak_ptr<const GuiResizer>  wcGuiResizer;
    
    // ================================================================================ //
    //                                      GUI RESIZER                                 //
    // ================================================================================ //
    
    //! The resizer is a model that resize its parent.
    /** The resizer is a model that resize...
     */
    class GuiResizer : public GuiModel
    {
    public:
        class Controller;
        typedef shared_ptr<Controller>  sController;
        typedef weak_ptr<Controller>    wController;
        
        enum Zone
        {
            Nothing             = 1<<0,
            BorderLeft          = 1<<1,
            BorderTop           = 1<<2,
            BorderRight         = 1<<3,
            BorderBottom        = 1<<4,
            AllBorders          = BorderLeft | BorderTop | BorderRight | BorderBottom,
            CornerTopLeft       = 1<<5,
            CornerTopRight      = 1<<6,
            CornerBottomLeft    = 1<<7,
            CornerBottomRight   = 1<<8,
            AllCorners          = CornerTopLeft | CornerTopRight | CornerBottomLeft | CornerBottomRight,
            All                 = AllBorders | AllCorners
        };
        
    private:
        ulong   m_zones;
        double  m_size;
    public:
        
        //! The resizer constructor.
        /** The function does nothing.
         @param context The context.
         @param zones   The resizables zones.
         @param size    The border size.
         */
        GuiResizer(sGuiContext context, ulong zones, const double size = 5.) noexcept : GuiModel(context), m_zones(zones), m_size(max(0., size)) {}
        
        //! The resizer destructor.
        /** The function does nothing.
         */
        inline ~GuiResizer() noexcept {}
        
        //! Gets the border thickness of the resizer.
        /** The function retrieves the border thickness of the resizer.
         @return The border size.
         */
        inline double getThickness() const noexcept {return m_size;}
        
        //! Sets the border thickness of the resizer.
        /** The function sets the border thickness of the resizer.
         @param size The border thickness.
         */
        void setThickness(const double thickness) noexcept {m_size = max(0., thickness);}
        
        //! Gets the zones that are resizables.
        /** The function retrieves the zones that are resizables.
         @return The zones.
         */
        inline ulong getZones() const noexcept {return m_zones;}
        
        //! Sets the zones that are resizables.
        /** The function sets the zones that are resizables.
         @param zones The zones.
         */
        void setZones(const ulong zones) noexcept {m_zones = zones;}
        
        //! Get the zone touch by a point in a given rectangle.
        /** The function retrieves the zone touch by a point in a given rectangle.
         @param rect The rectangle.
         @param pt   The point.
         @return The zone.
         */
        Zone getZone(Rectangle const& rect, Point const& pt) const noexcept;
        
    private:
        
        //! Create the controller.
        /** The function creates a controller depending on the inheritance.
         @return The controller.
         */
        sGuiController createController() override;
    };
    
    // ================================================================================ //
    //                              GUI RESIZER CONTROLLER                              //
    // ================================================================================ //
    
    //! The resizer controller.
    /** The resizer controller manage a view of a resizer.
     */
    class GuiResizer::Controller : public GuiController
    {
    private:
        const wGuiResizer   m_resizer;
        Rectangle           m_last_bounds;
        Zone                m_zone;
        
        MouseCursor getCursorForZone() const noexcept;
        ulong getRectangleBorders() const noexcept;
    public:
        //! The resizer controller constructor.
        /** The function initialize the resizer controller.
         @param resizer   The resizer to control.
         */
        Controller(sGuiResizer resizer) noexcept;
        
        //! The controller destructor.
        /** The function does nothing.
         */
        inline ~Controller() noexcept {};
        
        //! Gets the resizer.
        /** The function retrieves the resizer.
         @return The resizer.
         */
        inline sGuiResizer getResizer() const noexcept {return m_resizer.lock();}
        
        //! The paint method that can be override.
        /** The function shoulds draw some stuff in the sketch.
         @param view    The view that ask to draw.
         @param sketch  A sketch to draw.
         */
        void draw(sGuiView view, Sketch& sketch) override {};
        
        //! Test if the point lies into the controler.
        /** The funtion tests if the point lies into the controler.
         @param pt The point.
         @return true if the point lies into the controler, otherwise false.
         */
        bool hitTest(Point const& pt) const noexcept override;
    
        //! Test if the point lies into the controler.
        /** The funtion tests if the point lies into the controler.
         @param pt The point.
         @return true if the point lies into the controler, otherwise false.
         */
        bool contains(Point const& pt) const noexcept override;
        
        //! The mouse receive method.
        /** The function pass the mouse event to the model if it inherits from mouser.
         @param event    A mouser event.
         @return true if the class has done something with the event otherwise false
         */
        bool receive(sGuiView view, MouseEvent const& event) override;
        
        //! Receives the notification that the parent controller changed.
        /** The function notifies that the parent controller changed or has been setted.
         */
        void parentChanged() noexcept override;
        
        //! Receives the notification that the bounds of the parent controller changed.
        /** The function notifies that the bounds of the parent controller changed.
         */
        void parentBoundsChanged() noexcept override;
    };
}

#endif


