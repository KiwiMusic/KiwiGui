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

#ifndef __DEF_KIWI_GUI_DEFAULT__
#define __DEF_KIWI_GUI_DEFAULT__

#include "Attribute.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      ONOFF                                       //
    // ================================================================================ //
    
    class BoolAttr : public Attr::Value
    {
    private:
        bool m_state;
        
    public:
        
        BoolAttr() noexcept : m_state(false)
        {
            ;
        }
        
        BoolAttr(const bool state) noexcept : m_state(state)
        {
            ;
        }
        
        BoolAttr(BoolAttr const& other) noexcept : m_state(other.m_state)
        {
            ;
        }
        
        ~BoolAttr() noexcept
        {
            ;
        }
        
        //! Set the attribute value with a string.
        /** The function sets the attribute value with a string.
         @param text The value in the string format.
         */
        void setValue(string const& text) noexcept override;
        
        //! Retrieve the attribute value as a string.
        /** The function retrieves the attribute value as a string.
         @param text The value in the string format.
         */
        void getValue(string& text) const noexcept override;
        
        inline bool state() const noexcept
        {
            return m_state;
        }
        
        inline void state(const bool state) noexcept
        {
            m_state = state;
        }
        
        inline void toggle() noexcept
        {
            m_state = !m_state;
        }
        
        inline BoolAttr& operator=(BoolAttr const& other) noexcept
        {
            m_state = other.m_state;
            return *this;
        }
        
        inline BoolAttr& operator=(const bool state) noexcept
        {
            m_state = state;
            return *this;
        }
        
        inline operator bool() const noexcept
        {
            return m_state;
        }
        
        inline bool operator!=(BoolAttr const& other) const noexcept
        {
            return m_state != other.m_state;
        }
        
        inline bool operator==(BoolAttr const& other) const noexcept
        {
            return m_state == other.m_state;
        }
    };
    
    // ================================================================================ //
    //                                      INTEGER                                     //
    // ================================================================================ //
    
    class Integer : public Attr::Value
    {
    private:
        long m_value;
        
    public:
        
        Integer() noexcept : m_value(0)
        {
            ;
        }
        
        Integer(const long value) noexcept : m_value(value)
        {
            ;
        }
        
        Integer(Integer const& other) noexcept : m_value(other.m_value)
        {
            ;
        }
        
        ~Integer() noexcept
        {
            ;
        }
        
        //! Set the attribute value with a string.
        /** The function sets the attribute value with a string.
         @param text The value in the string format.
         */
        void setValue(string const& text) noexcept override;
        
        //! Retrieve the attribute value as a string.
        /** The function retrieves the attribute value as a string.
         @param text The value in the string format.
         */
        void getValue(string& text) const noexcept override;
        
        inline bool value() const noexcept
        {
            return m_value;
        }
        
        inline void value(const bool value) noexcept
        {
            m_value = value;
        }
        
        inline Integer& operator=(Integer const& other) noexcept
        {
            m_value = other.m_value;
            return *this;
        }
        
        inline Integer& operator=(const long value) noexcept
        {
            m_value = value;
            return *this;
        }
        
        inline operator long() const noexcept
        {
            return m_value;
        }
        
        inline bool operator!=(Integer const& other) const noexcept
        {
            return m_value != other.m_value;
        }
        
        inline bool operator==(Integer const& other) const noexcept
        {
            return m_value == other.m_value;
        }
    };
}

#endif