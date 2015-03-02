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

#include "KiwiWriter.h"

namespace Kiwi
{
	// ================================================================================ //
	//										WRITER										//
	// ================================================================================ //
	
	Writer::Writer()
	{
		m_textfield = make_shared<TextField>();
	}
	
	Writer::~Writer()
	{
		
	}
	
	void Writer::addView(sView view)
	{
		if(view)
		{
			lock_guard<mutex> guard(m_views_mutex);
			m_views.insert(view);
		}
	}
	
	void Writer::removeView(sView view)
	{
		if(view)
		{
			lock_guard<mutex> guard(m_views_mutex);
			m_views.erase(view);
		}
	}
	
	Writer::sTextField Writer::getTextField() const noexcept
	{
		return m_textfield;
	}
	
	void Writer::setText(wstring const& newText) noexcept
	{
		if(m_textfield)
		{
			m_textfield->setText(newText);
		}
	}
	
	wstring Writer::getText(const bool textedited) const noexcept
	{
		if(m_textfield)
		{
			if(textedited)
			{
				return m_textfield->getEditedText();
			}
			else
			{
				return m_textfield->getText();
			}
		}
		
		return wstring();
	}
	
	bool Writer::textFilter(wstring& newtext)
	{
		return true;
	}
	
	void Writer::textChanged()
	{
		;
	}
	
	
	// ================================================================================ //
	//									  TEXTFIELD										//
	// ================================================================================ //
	
	
	Writer::TextField::TextField() noexcept :
	m_fontname(Attr::create("fontname", "Font Name", "Font", StringValue("Menelo"))),
	m_fontsize(Attr::create("fontsize", "Font Size", "Font", DoubleValue(12.))),
	m_fontface(Attr::create("fonface", "Font Face", "Font", StringValue("Plain"))),
	m_textjusification(Attr::create("textjustification", "Text Justification", "Font", StringValue("Left"))),
	m_textcolor(Attr::create("textcolor", "Text Color", "Color", ColorValue(0., 0., 0., 1.))),
	m_margin_left(Attr::create("margin_left", "Margin Left", "Appearance", LongValue(0))),
	m_margin_top(Attr::create("margin_top", "Margin Top", "Appearance", LongValue(0))),
	m_margin_right(Attr::create("margin_right", "Margin Right", "Appearance", LongValue(0))),
	m_margin_bottom(Attr::create("margin_bottom", "Margin Bottom", "Appearance", LongValue(0))),
	m_multiline(Attr::create("multiline", "Multiline", "Behavior", BoolValue(false))),
	m_autofixwidth(Attr::create("autofixwidth", "Auto Fixed Width", "Behavior", BoolValue(true))),
	m_editonclick(Attr::create("editonclick", "Edit On Click", "Behavior", BoolValue(true))),
	m_selectallonedit(Attr::create("selectallonedit", "Select All On Edit", "Behavior", BoolValue(true))),
	m_readonly(Attr::create("readonly", "Read Only", "Behavior", BoolValue(false))),
	m_wordwrap(Attr::create("wordwrap", "Word Wrap", "Behavior", BoolValue(true))),
	m_useellipsis(Attr::create("useellipsis", "Use Ellipsis", "Behavior", BoolValue(false))),
	m_autoscroll(Attr::create("autoscroll", "Auto Scroll", "Behavior", BoolValue(true))),
	m_wantsreturn(Attr::create("wantsreturn", "Wants Return", "Behavior", BoolValue(false))),
	m_wantstab(Attr::create("wantstab", "Wants Tab", "Behavior", BoolValue(false)))
	{
		;
	}
	
	Writer::TextField::~TextField()
	{
		m_textviews.clear();
	}
	
	void Writer::TextField::setWriter(sWriter writer)
	{
		m_writer = writer;
	}
	
	bool Writer::TextField::notify(sAttr attr)
	{
		return true;
	}
	
	sWriter Writer::TextField::getWriter()
	{
		return m_writer.lock();
	}
	
	void Writer::TextField::addView(sView view)
	{
		if(view)
		{
			lock_guard<mutex> guard(m_textviews_mutex);
			m_textviews.insert(view);
		}
	}
	
	void Writer::TextField::removeView(sView view)
	{
		if(view)
		{
			lock_guard<mutex> guard(m_textviews_mutex);
			m_textviews.erase(view);
		}
	}
	
	void Writer::TextField::startEditing()
	{
		if (!m_editing)
		{
			m_text_edited = m_text;
			m_editing = true;
		}
	}
	
	void Writer::TextField::endEditing()
	{
		if (m_editing)
		{
			m_editing = false;
			
			if (m_text != m_text_edited)
			{
				m_text = m_text_edited;
				updateViews(false);
			}
		}
	}
	
	bool Writer::TextField::isEditing()
	{
		return m_editing;
	}
	
	void Writer::TextField::setText(wstring const& newtext)
	{
		if (newtext != m_text)
		{
			m_text = newtext;
			updateViews(false);
		}
	}
	
	wstring Writer::TextField::getText() const noexcept
	{
		return m_text;
	}
	
	void Writer::TextField::setEditedText(wstring const& newtext)
	{
		if (newtext != m_text_edited)
		{
			m_text_edited = newtext;
			updateViews(true);
		}
	}
	
	wstring Writer::TextField::getEditedText() const noexcept
	{
		return m_text_edited;
	}
	
	void Writer::TextField::updateViews(const bool editing)
	{
		lock_guard<mutex> guard(m_textviews_mutex);
		auto it = m_textviews.begin();
		while(it != m_textviews.end())
		{
			if((*it).expired())
			{
				it = m_textviews.erase(it);
			}
			else
			{
				sView textview = (*it).lock();
				if (editing)
				{
					textview->textfieldTextEdited();
				}
				else
				{
					textview->textfieldTextChanged();
				}
				++it;
			}
		}
	}
	
	// ================================================================================ //
	//									TEXTFIELD VIEW									//
	// ================================================================================ //
	
	Writer::TextField::View::View(sTextField textfield) : m_textfield(textfield)
	{
		;
	}
	
	Writer::TextField::View::~View()
	{
		;
	}
	
	Writer::sTextField Writer::TextField::View::getTextField() const noexcept
	{
		return m_textfield.lock();
	}
	
	sWriter Writer::TextField::View::getWriter() const noexcept
	{
		sTextField tf = getTextField();
		if(tf)
		{
			return tf->getWriter();
		}
		return sWriter();
	}
}