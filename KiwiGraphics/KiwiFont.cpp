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

#include "KiwiFont.h"

namespace Kiwi
{
    vector<Font> Font::m_fonts;
    
    double Font::Intern::getCharacterWidth(char const& c) const noexcept
    {
        return 0.;
    }
    
    double Font::Intern::getCharacterWidth(wchar_t const& c) const noexcept
    {
        return 0.;
    }
    
    double Font::Intern::getLineWidth(string const& line) const noexcept
    {
        return 0.;
    }
    
    double Font::Intern::getLineWidth(wstring const& line) const noexcept
    {
        return 0.;
    }
    
    Size Font::Intern::getTextSize(string const& text, const double width) const noexcept
    {
        return Size(0., 0.);
    }
    
    Size Font::Intern::getTextSize(wstring const& text, const double width) const noexcept
    {
        return Size(0., 0.);
    }
}

