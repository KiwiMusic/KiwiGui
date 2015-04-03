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
    void BoolValue::set(Vector const& vector)
    {
        if(!vector.empty() && vector[0].isNumber())
        {
            m_state = (bool)vector[0];
        }
    }
    
    Vector BoolValue::get() const noexcept
    {
        return {m_state};
    }
    
    void LongValue::set(Vector const& vector)
    {
        if(!vector.empty() && vector[0].isNumber())
        {
            m_value = (long)vector[0];
        }
    }
    
    Vector LongValue::get() const noexcept
    {
        return {m_value};
    }
    
    void DoubleValue::set(Vector const& vector)
    {
        if(!vector.empty() && vector[0].isNumber())
        {
            m_value = (double)vector[0];
        }
    }
    
    Vector DoubleValue::get() const noexcept
    {
        return {m_value};
    }
    
    void StringValue::set(Vector const& vector)
    {
        if(!vector.empty() && vector[0].isTag())
        {
            m_value = sTag(vector[0])->getName();
        }
    }
    
    Vector StringValue::get() const noexcept
    {
        return {m_value};
    }
    
    
}