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

#include "Font.h"
#include "TargetConditionals.h"

#if TARGET_OS_MAC
#import <Cocoa/Cocoa.h>

namespace Kiwi
{
    namespace Gui
    {
        Point Font::getStringSize(Font const& font, string const& text) noexcept
        {
            NSString *message = [NSString stringWithCString:text.c_str() encoding:[NSString defaultCStringEncoding]];
            NSString *fontname = [NSString stringWithCString:font.getName().c_str() encoding:[NSString defaultCStringEncoding]];
            NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:[NSFont fontWithName:fontname size:font.getSize()], NSFontAttributeName, nil];
            NSAttributedString *text2 = [[NSAttributedString alloc] initWithString:message attributes: attributes];
            NSSize textSize = [text2 size];
            
            return Point(textSize.width, textSize.height);
        }
        
        Point Font::getStringSize(Font const& font, wstring const& wtext) noexcept
        {
            string text(wtext.begin(), wtext.end());
            NSString *message = [NSString stringWithCString:text.c_str() encoding:[NSString defaultCStringEncoding]];
            NSString *fontname = [NSString stringWithCString:font.getName().c_str() encoding:[NSString defaultCStringEncoding]];
            NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:[NSFont fontWithName:fontname size:font.getSize()], NSFontAttributeName, nil];
            NSAttributedString *text2 = [[NSAttributedString alloc] initWithString:message attributes: attributes];
            NSSize textSize = [text2 size];
            
            return Point(textSize.width, textSize.height);
        }
		
		double Font::getStringHeight(Font const& font, string const text, const float textWidth) noexcept
		{
			NSString *message = [NSString stringWithCString:text.c_str() encoding:[NSString defaultCStringEncoding]];

			//NSString *fontFamily = @"Helvetica";
			NSString *fontFamily = [NSString stringWithCString:font.getName().c_str() encoding:[NSString defaultCStringEncoding]];
			NSFontTraitMask fontTrait;
			
			if(font.isBold()) fontTrait |= NSBoldFontMask;
			if(font.isItalic()) fontTrait |= NSItalicFontMask;
			
			NSFontManager *fontManager = [NSFontManager sharedFontManager];
			NSFont *nsFont = [fontManager fontWithFamily:fontFamily traits:fontTrait weight:0 size:font.getSize()];
			
			NSTextStorage *textStorage = [[[NSTextStorage alloc] initWithString:message] autorelease];
			NSTextContainer *textContainer = [[[NSTextContainer alloc] initWithContainerSize: NSMakeSize(textWidth, FLT_MAX)] autorelease];
			NSLayoutManager *layoutManager = [[[NSLayoutManager alloc] init] autorelease];
			
			[layoutManager addTextContainer:textContainer];
			[textStorage addLayoutManager:layoutManager];
			
			[textStorage addAttribute:NSFontAttributeName value:nsFont range:NSMakeRange(0, [textStorage length])];
			[textContainer setLineFragmentPadding:0.0];
			
			(void) [layoutManager glyphRangeForTextContainer:textContainer];
			return [layoutManager usedRectForTextContainer:textContainer].size.height;
		}
    }
}

#elif TARGET_OS_IPHONE
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>
#import <MobileCoreServices/MobileCoreServices.h>
#include <sys/fcntl.h>
#endif