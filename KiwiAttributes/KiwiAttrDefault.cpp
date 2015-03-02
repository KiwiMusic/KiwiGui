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

#include "KiwiAttrDefault.h"

namespace Kiwi
{
    void BoolValue::setValue(string const& text) noexcept
    {
        string::size_type pos;
        pos = text.find("true");
        if(pos != string::npos)
        {
            m_state = true;
            return;
        }
        pos = text.find("false");
        if(pos != string::npos)
        {
            m_state = false;
            return;
        }
        pos = text.find_first_of("0123456789");
        if(pos != string::npos)
        {
            m_state = (bool)stod(text.c_str()+pos);
            return;
        }
    }
    
    void BoolValue::getValue(string& text) const noexcept
    {
        text = toString(m_state);
    }
    
    void LongValue::setValue(string const& text) noexcept
    {
        const string::size_type pos = text.find_first_of("-0123456789");
        if(pos != string::npos)
        {
            m_value = stol(text.c_str()+pos);
        }
    }
    
    void LongValue::getValue(string& text) const noexcept
    {
        text = toString(m_value);
    }
    
    void DoubleValue::setValue(string const& text) noexcept
    {
        const string::size_type pos = text.find_first_of("-0123456789.");
        if(pos != string::npos)
        {
            m_value = stod(text.c_str()+pos);
        }
    }
    
    void DoubleValue::getValue(string& text) const noexcept
    {
        text = toString(m_value);
    }
}