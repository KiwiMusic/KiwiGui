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

#include "KiwiAttr.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      ONOFF                                       //
    // ================================================================================ //
    
    class BoolValue : public Attr::Value
    {
    private:
        bool m_state;
        
    public:
        
        BoolValue() noexcept : m_state(false)
        {
            ;
        }
        
        BoolValue(const bool state) noexcept : m_state(state)
        {
            ;
        }
        
        BoolValue(BoolValue const& other) noexcept : m_state(other.m_state)
        {
            ;
        }
        
        ~BoolValue() noexcept
        {
            ;
        }
        
        //! Retrieve the attribute value as a vector of atoms.
        /** The function retrieves the attribute value as a vector of atoms.
         @return The vector of atoms.
         */
        Vector get() const noexcept override;
        
        //! Set the attribute value with a vector of atoms.
        /** The function sets the attribute value with a vector of atoms.
         @param vector The vector of atoms.
         */
        void set(Vector const& vector) override;
        
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
        
        inline BoolValue& operator=(BoolValue const& other) noexcept
        {
            m_state = other.m_state;
            return *this;
        }
        
        inline BoolValue& operator=(const bool state) noexcept
        {
            m_state = state;
            return *this;
        }
        
        inline operator bool() const noexcept
        {
            return m_state;
        }
        
        inline bool operator!=(BoolValue const& other) const noexcept
        {
            return m_state != other.m_state;
        }
        
        inline bool operator==(BoolValue const& other) const noexcept
        {
            return m_state == other.m_state;
        }
    };
    
    // ================================================================================ //
    //                                      LONG                                        //
    // ================================================================================ //
    
    class LongValue : public Attr::Value
    {
    private:
        long m_value;
        
    public:
        
        LongValue() noexcept : m_value(0)
        {
            ;
        }
        
        LongValue(const long value) noexcept : m_value(value)
        {
            ;
        }
        
        LongValue(LongValue const& other) noexcept : m_value(other.m_value)
        {
            ;
        }
        
        ~LongValue() noexcept
        {
            ;
        }
        
        //! Retrieve the attribute value as a vector of atoms.
        /** The function retrieves the attribute value as a vector of atoms.
         @return The vector of atoms.
         */
        Vector get() const noexcept override;
        
        //! Set the attribute value with a vector of atoms.
        /** The function sets the attribute value with a vector of atoms.
         @param vector The vector of atoms.
         */
        void set(Vector const& vector) override;
        
        inline long value() const noexcept
        {
            return m_value;
        }
        
        inline void value(const long value) noexcept
        {
            m_value = value;
        }
        
        inline LongValue& operator=(LongValue const& other) noexcept
        {
            m_value = other.m_value;
            return *this;
        }
        
        inline LongValue& operator=(const long value) noexcept
        {
            m_value = value;
            return *this;
        }
        
        inline operator long() const noexcept
        {
            return m_value;
        }
        
        inline bool operator!=(LongValue const& other) const noexcept
        {
            return m_value != other.m_value;
        }
        
        inline bool operator==(LongValue const& other) const noexcept
        {
            return m_value == other.m_value;
        }
    };
    
    // ================================================================================ //
    //                                      DOUBLE                                      //
    // ================================================================================ //
    
    class DoubleValue : public Attr::Value
    {
    private:
        double m_value;
        
    public:
        
        DoubleValue() noexcept : m_value(0)
        {
            ;
        }
        
        DoubleValue(const long value) noexcept : m_value(value)
        {
            ;
        }
        
        DoubleValue(DoubleValue const& other) noexcept : m_value(other.m_value)
        {
            ;
        }
        
        ~DoubleValue() noexcept
        {
            ;
        }
        
        //! Retrieve the attribute value as a vector of atoms.
        /** The function retrieves the attribute value as a vector of atoms.
         @return The vector of atoms.
         */
        Vector get() const noexcept override;
        
        //! Set the attribute value with a vector of atoms.
        /** The function sets the attribute value with a vector of atoms.
         @param vector The vector of atoms.
         */
        void set(Vector const& vector) override;
        
        inline double value() const noexcept
        {
            return m_value;
        }
        
        inline void value(const double value) noexcept
        {
            m_value = value;
        }
        
        inline DoubleValue& operator=(DoubleValue const& other) noexcept
        {
            m_value = other.m_value;
            return *this;
        }
        
        inline DoubleValue& operator=(const double value) noexcept
        {
            m_value = value;
            return *this;
        }
        
        inline operator double() const noexcept
        {
            return m_value;
        }
        
        inline bool operator!=(DoubleValue const& other) const noexcept
        {
            return m_value != other.m_value;
        }
        
        inline bool operator==(DoubleValue const& other) const noexcept
        {
            return m_value == other.m_value;
        }
    };
	
	// ================================================================================ //
	//                                      STRING										//
	// ================================================================================ //
	
	class StringValue : public Attr::Value
	{
	private:
		string m_value;
	public:
		
		StringValue() noexcept
		{
			;
		}
		
		StringValue(string const& str) noexcept : m_value(str)
		{
			;
		}
		
		StringValue(StringValue const& other) noexcept : m_value(other.m_value)
		{
			;
		}
		
		~StringValue() noexcept
		{
			;
		}
		
        //! Retrieve the attribute value as a vector of atoms.
        /** The function retrieves the attribute value as a vector of atoms.
         @return The vector of atoms.
         */
        Vector get() const noexcept override;
        
        //! Set the attribute value with a vector of atoms.
        /** The function sets the attribute value with a vector of atoms.
         @param vector The vector of atoms.
         */
        void set(Vector const& vector) override;
		
		inline string value() const noexcept
		{
			return m_value;
		}
		
		inline void value(string const& value) noexcept
		{
			m_value = value;
		}
		
		inline StringValue& operator=(StringValue const& other) noexcept
		{
			m_value = other.m_value;
			return *this;
		}
		
		inline StringValue& operator=(string const& value) noexcept
		{
			m_value = value;
			return *this;
		}
		
		inline StringValue& operator=(char const& value) noexcept
		{
			m_value = value;
			return *this;
		}
		
		inline operator string() const noexcept
		{
			return m_value;
		}
		
		inline bool operator!=(StringValue const& other) const noexcept
		{
			return m_value != other.m_value;
		}
		
		inline bool operator!=(string const& other) const noexcept
		{
			return m_value != other;
		}
		
		inline bool operator==(StringValue const& other) const noexcept
		{
			return m_value == other.m_value;
		}
		
		inline bool operator==(string const& other) const noexcept
		{
			return m_value == other;
		}
	};
}

#endif