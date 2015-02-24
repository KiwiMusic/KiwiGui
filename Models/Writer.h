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

#ifndef __DEF_KIWI_GUI_TEXTFIELD__
#define __DEF_KIWI_GUI_TEXTFIELD__

#include "Keyboarder.h"

namespace Kiwi
{
		// ================================================================================ //
		//										WRITER										//
		// ================================================================================ //
		
		class Writer : virtual public Kiwi::Sketcher, public Kiwi::Keyboarder, protected Kiwi::Mouser
		{
			typedef shared_ptr<Writer>			sWriter;
			typedef weak_ptr<Writer>			wWriter;
			
		public:
			class TextField;
			typedef shared_ptr<TextField>			sTextField;
			typedef weak_ptr<TextField>				wTextField;
			typedef shared_ptr<const TextField> 	scTextField;
			typedef weak_ptr<const TextField>		wcTextField;
			
		public:
			
			// ================================================================================ //
			//									  WRITER VIEW									//
			// ================================================================================ //
			
			class View // => ObjectView
			{
			public:
				virtual ~View() {};

				//! Receive the notification that the view is currently being edited.
				/** The function is called if the view is currently being edited.
				 */
				virtual void textFieldEditorShown() = 0;
				
				//! Receives the notification that the textfield's text changed.
				/** The function receives the notification that the textfield's text changed
				 */
				virtual void textfieldTextChanged() = 0;
			};
			
			typedef shared_ptr<View>		sView;
			typedef weak_ptr<View>			wView;
			
		private:
			sTextField						m_textfield;
			
			set<wView, owner_less<wView>>   m_views;
			mutable mutex                   m_views_mutex;
			
			// writer attributes
			Font	m_font;
			Color	m_textcolor;
			
		public:
			Writer();
			
			virtual ~Writer();
			
			//! Adds a view to the writer.
			/** The function adds a view to the writer. 
			 The view will then be notified whenever the writer needs to add or remove textfields.
			 @param view The view to add.
			 */
			void addView(sView view);
			
			//! Removes a view from the writer.
			/** The function removes a view from the writer.
			 If the view wasn't a writer's view, the function does nothing.
			 @param view The view to remove.
			 */
			void removeView(sView view);
			
			
			bool receive(Mouser::Event const& event) override
			{
				int TODO;
				return false;
			}
		
			bool receive(Keyboarder::Event const& event) override
			{
				int TODO;
				return false;
			}
	
			bool receive(Keyboarder::Focus event) override
			{
				int TODO;
				return false;
			}

			//! Retrieves the textfield.
			/** This function retrievs the textfield.
			 @return The textfield.
			 */
			sTextField getTextField() const noexcept;
			
			//! Retrieves the textfield.
			/** This function retrieves the textfield.
			 @return The textfield.
			 */
			void setText(wstring const& newText) noexcept;
			
			//! Retrieves the textfield's text.
			/** This function retrieves the textfield's text.
			 @return The textfield's text.
			 */
			wstring getText(const bool textedited = false) const noexcept;
			
			//! This function is called whenever text is entered into the editor.
			/** An implementation of this class should check the input string,
			 and return an edited version of it that should be used.
			 @param newtext The new entered text.
			 @return False if you don't want to pass the key to the textfield, otherwise true.
			 */
			virtual bool textFilter(wstring& newtext);
			
			//! This function is called when the text of the textfield changed.
			/** An implementation of this class should check the new text and do something with it.
			 @param textfield The textfield that changed.
			 */
			virtual void textChanged();
		};
		
		typedef shared_ptr<Writer>			sWriter;
		typedef weak_ptr<Writer>			wWriter;
		typedef shared_ptr<const Writer> 	scWriter;
		typedef weak_ptr<const Writer>		wcWriter;
		
		// ================================================================================ //
		//                                     TEXTFIELD                                    //
		// ================================================================================ //
		
		//! The textfield manages a text and a set of view for the textfield.
		/** The textfield manages a text and a set of view for the textfield.
		 */
		class Writer::TextField : public Attr::Manager
		{
		public:
			class View;
			typedef shared_ptr<View>		sView;
			typedef weak_ptr<View>			wView;
			typedef shared_ptr<const View>	scView;
			typedef weak_ptr<const View>	wcView;
			
		private:
			wWriter						m_writer;
			
			wstring						m_text;
			wstring						m_text_edited;
			bool						m_editing;
			
			set<wView,
			owner_less<wView>>			m_textviews;
			mutable mutex				m_textviews_mutex;
			
			// textfield attributes
			const sAttrString	m_fontname;
			const sAttrDouble	m_fontsize;
			const sAttrString	m_fontface;
			const sAttrString	m_textjusification;
			const sAttrColor	m_textcolor;
			const sAttrLong		m_margin_left;
			const sAttrLong		m_margin_top;
			const sAttrLong		m_margin_right;
			const sAttrLong		m_margin_bottom;
			const sAttrBool		m_multiline;
			const sAttrBool		m_autofixwidth;
			const sAttrBool		m_editonclick;
			const sAttrBool		m_selectallonedit;
			const sAttrBool		m_readonly;
			const sAttrBool		m_wordwrap;
			const sAttrBool		m_useellipsis;
			const sAttrBool		m_autoscroll;
			const sAttrBool		m_wantsreturn;
			const sAttrBool		m_wantstab;
			
		public:
			
			//! Constructor.
			TextField() noexcept;
			
			//! Destructor.
			~TextField();
			
			//! Notify the manager that the values of an attribute has changed.
			/** The function notifies the manager that the values of an attribute has changed.
			 @param attr An attribute.
			 @return pass true to notify changes to listeners, false if you don't want them to be notified
			 */
			bool notify(sAttr attr) override;
			
			//! Sets the writer.
			void setWriter(sWriter writer);
			
			//! Retrieves the writer.
			sWriter getWriter();
			
			//! Adds a textview to be managed by the textfield.
			/** The function adds a textfield to be managed by the textfield.
			 @param view The textfield view to add.
			 */
			void addView(sView view);
			
			//! Removes a textview thas was managed by the textfield.
			/** The function removes a textfield thas was managed by the textfield.
			 If the textfield wasn't managed by the the textfield, the function does nothing.
			 @param view The textfield view to remove.
			 */
			void removeView(sView view);
			
			//! Indicates textfield that a view is currently entered in editing mode.
			/** The function indicates textfield that a view is currently entered in editing mode.
			 Every startEditing call needs to be followed by an endEditing call to indicate that the view is no more in editing mode.
			 */
			void startEditing();
			
			//! Indicates textfield that a view is no more editing mode.
			/** The function indicates textfield that a view is no more in editing mode.
			 You need to call startEditing before every endEditing call.
			 */
			void endEditing();
			
			//! Get if the textfield is currently being edited by a view.
			/** The function get if the textfield is currently being edited.
			 @return True if the textfield is currently being edited by a view, false otherwise.
			 */
			bool isEditing();
			
			//! Sets the text of the textfield.
			/** The function sets the textfield's text and update all views.
			 @param newtext The new textfield's text.
			 */
			void setText(wstring const& newtext);
			
			//! Retrieves the textfield's text.
			/** The function retrieves the textfield's text.
			 @return The textfield's text.
			 */
			wstring getText() const noexcept;
			
			//! Sets the edited text of the textfield.
			/** The function sets the textfield's edited text and update all views with this text.
			 @param newtext The new textfield's edited text.
			 */
			void setEditedText(wstring const& newtext);
			
			//! Retrieves the textfield's edited text.
			/** The function retrieves the textfield's edited text.
			 @return The textfield's text.
			 */
			wstring getEditedText() const noexcept;
			
			//! Updates all textfield's views.
			/** The function updates all textfield's views.
			 Effectivelly, it calls setText to all views.
			 */
			void updateViews(const bool editing);
			
			//! Set the textfield's font.
			/** The function sets the textfield's font.
			 @param font The new font to use.
			 */
			void setFont(Font const& font)
			{
				setFontName(font.getName());
			}
			
			//! Retrieves the textfield's font.
			/** The function retrieves the textfield's font.
			 @return The textfield's font.
			 */
			Font getFont() const noexcept
			{
				return Font(getFontName(), getFontSize());
			}
			
			//! Set the textfield's font name.
			/** The function sets the textfield's font name.
			 @param fontname The new font name to use.
			 */
			void setFontName(string const& fontname)
			{
				setAttrValue("fontname", StringValue(fontname));
			}
			
			//! Retrieves the textfield's font name.
			/** The function retrieves the textfield's font name.
			 @return The textfield's font name.
			 */
			string getFontName() const noexcept
			{
				StringValue val;
				if(getAttrValue("fontname", &val))
				{
					return val;
				}
				return 0;
			}
			
			//! Set the textfield's font size.
			/** The function sets the textfield's font name.
			 @param fontname The new font name to use.
			 */
			void setFontSize(const double fontsize)
			{
				setAttrValue("fontsize", DoubleValue(fontsize));
			}
			
			//! Retrieves the textfield's font size.
			/** The function retrieves the textfield's font size.
			 @return The textfield's font size.
			 */
			double getFontSize() const noexcept
			{
				DoubleValue val;
				if(getAttrValue("fontsize", &val))
				{
					return val;
				}
				return 12.;
			}
			
			//! Set the textfield's font justification.
			/** The function sets the textfield's font justification.
			 @param justification The new font justification to use.
			 */
			void setJustification(const Font::Justification justification)
			{
				StringValue val("Left");
				if (justification == Font::Justification::Centred)
				{
					val = "Center";
				}
				else if (justification == Font::Justification::Right)
				{
					val = "Right";
				}
				
				setAttrValue("textjustification", val);
			}
			
			//! Retrieves the textfield's font justification.
			/** The function retrieves the textfield's font justification.
			 @return The textfield's font justification.
			 */
			Font::Justification getJustification() const noexcept
			{
				StringValue val;
				if(getAttrValue("textjustification", &val))
				{
					if(val == "Left")
						return Font::Justification::Left;
					else if(val == "Center")
						return Font::Justification::Centred;
					else if(val == "Right")
						return Font::Justification::Right;
				}
				
				return Font::Justification::Left;
			}
			
			//! Set the margins.
			/** The function sets the textfield's margins.
			 @param left	The left margin.
			 @param top		The top margin.
			 @param right	The right margin.
			 @param bottom	The bottom margin.
			 */
			void setMargins(const long left, const long top, const long right, const long bottom)
			{
				setAttrValue("margin_left", LongValue(max<long>(0, left)));
				setAttrValue("margin_left", LongValue(max<long>(0, top)));
				setAttrValue("margin_left", LongValue(max<long>(0, right)));
				setAttrValue("margin_left", LongValue(max<long>(0, bottom)));
			}
			
			//! Retrieves the left margin.
			/** The function retrieves the left margin.
			 @return The left margin.
			 */
			long getMarginLeft() const noexcept
			{
				LongValue val;
				if(getAttrValue("margin_left", &val))
				{
					return val;
				}
				return 0;
			}
			
			//! Retrieves the top margin.
			/** The function retrieves the top margin.
			 @return The top margin.
			 */
			long getMarginTop() const noexcept
			{
				LongValue val;
				if(getAttrValue("margin_top", &val))
				{
					return val;
				}
				return 0;
			}
			
			//! Retrieves the right margin.
			/** The function retrieves the right margin.
			 @return The right margin.
			 */
			long getMarginRight() const noexcept
			{
				LongValue val;
				if(getAttrValue("margin_right", &val))
				{
					return val;
				}
				return 0;
			}
			
			//! Retrieves the bottom margin.
			/** The function retrieves the bottom margin.
			 @return The bottom margin.
			 */
			long getMarginBottom() const noexcept
			{
				LongValue val;
				if(getAttrValue("margin_bottom", &val))
				{
					return val;
				}
				return 0;
			}
			
			//! Set the text color.
			/** The function sets the text color.
			 @param textcolor The new text color.
			 */
			void setTextColor(Color const& textcolor)
			{
				setAttrValue("textcolor", ColorValue(textcolor));
			}
			
			//! Retrieves the text color.
			/** The function retrieves the text color.
			 @return The text color.
			 */
			Color getTextColor() const noexcept
			{
				ColorValue val;
				if(getAttrValue("textcolor", &val))
				{
					return val;
				}
				return val;
			}
			
			//! Puts the textfield into either multi- or single-line mode.
			/** By default, the textfield will be in single-line mode,
			 so use this if you need a multi-line textfield.
			 See also the setWantsReturn() method, which will also need to be turned
			 on if you want a multi-line textfield with line-breaks.
			 @see isMultiLine, setWantsReturn
			 */
			void setMultiLine(const bool isMultiline)
			{
				setAttrValue("multiline", BoolValue(isMultiline));
			}
			
			//! Retrieves if the textfield is in multi-line mode.
			/** The function retrieves if the textfield is in multi-line mode.
			 @return True if the textfield is in multi-line mode, false if it's in single-line mode
			 */
			bool isMultiLine() const noexcept
			{
				BoolValue val;
				if(getAttrValue("multiline", &val))
				{
					return val;
				}
				return false;
			}
			
			//! Set the wantsreturn attribute.
			/** This function sets the wantsreturn attribute.
			 @param wantsReturn True if you want the return key starts a new line, false if it shoulld be ignored.
			 */
			void setWantsReturn(const bool wantsReturn)
			{
				setAttrValue("wantsreturn", BoolValue(wantsReturn));
			}
			
			//! Retrieves the wantsreturn attribute.
			/** The function retrieves the wantsreturn attribute.
			 @return The wantsreturn attribute value.
			 */
			bool getWantsReturn() const noexcept
			{
				BoolValue val;
				if(getAttrValue("wantsreturn", &val))
				{
					return val;
				}
				return false;
			}
			
			//! Set the wantstab attribute.
			/** This function sets the wantstab attribute.
			 @param wantstab True if you want the tab key be used, otherwise false.
			 */
			void setWantsTab(const bool wantsTab)
			{
				setAttrValue("wantstab", BoolValue(wantsTab));
			}
			
			//! Retrieves the wantstab attribute.
			/** The function retrieves the wantstab attribute.
			 @return The wantstab attribute value.
			 */
			bool getWantsTab() const noexcept
			{
				BoolValue val;
				if(getAttrValue("wantstab", &val))
				{
					return val;
				}
				return false;
			}
			
			//! Set the readonly attribute.
			/** This function sets the readonly attribute.
			 @param readonly True if you don't want the textfield being edited, otherwise false.
			 */
			void setReadOnly(const bool readonly)
			{
				setAttrValue("readonly", BoolValue(readonly));
			}
			
			//! Retrieves the readonly attribute.
			/** The function retrieves the readonly attribute.
			 @return The readonly attribute value.
			 */
			bool getReadOnly() const noexcept
			{
				BoolValue val;
				if(getAttrValue("readonly", &val))
				{
					return val;
				}
				return false;
			}
			
			//! Set the editonclick attribute.
			/** This function sets the editonclick attribute.
			 @param editonclick True if you want the textfield being edited on click.
			 */
			void setEditOnClick(const bool editonclick)
			{
				setAttrValue("editonclick", BoolValue(editonclick));
			}
			
			//! Retrieves the editonclick attribute.
			/** The function retrieves the editonclick attribute.
			 @return The editonclick attribute value.
			 */
			bool getEditOnClick() const noexcept
			{
				BoolValue val;
				if(getAttrValue("editonclick", &val))
				{
					return val;
				}
				return false;
			}
			
			//! Set the selectallonedit attribute.
			/** This function sets the selectallonedit attribute.
			 @param selectallonedit True if you want to select all text when textfield enter in edit mode.
			 */
			void setSelectAllOnEdit(const bool selectallonedit)
			{
				setAttrValue("selectallonedit", BoolValue(selectallonedit));
			}
			
			//! Retrieves the selectallonedit attribute.
			/** The function retrieves the selectallonedit attribute.
			 @return The selectallonedit attribute value.
			 */
			bool getSelectAllOnEdit() const noexcept
			{
				BoolValue val;
				if(getAttrValue("selectallonedit", &val))
				{
					return val;
				}
				return false;
			}
			
			//! Set the wordwrap attribute.
			/** This function sets the wordwrap attribute.
			 @param wordwrap True if you want to use word wrapping.
			 */
			void setWordWrap(const bool wordwrap)
			{
				setAttrValue("wordwrap", BoolValue(wordwrap));
			}
			
			//! Retrieves the wordwrap attribute.
			/** The function retrieves the wordwrap attribute.
			 @return The wordwrap attribute value.
			 */
			bool getWordWrap() const noexcept
			{
				BoolValue val;
				if(getAttrValue("wordwrap", &val))
				{
					return val;
				}
				return false;
			}
			
			//! Set the useellipsis attribute.
			/** This function sets the useellipsis attribute.
			 @param useellipsis True if you want to use ellipsis.
			 */
			void setUseEllipsis(const bool useEllipsis)
			{
				setAttrValue("useellipsis", BoolValue(useEllipsis));
			}
			
			//! Retrieves the useellipsis attribute.
			/** The function retrieves the useellipsis attribute.
			 @return The useellipsis attribute value.
			 */
			bool getUseEllipsis() const noexcept
			{
				BoolValue val;
				if(getAttrValue("useellipsis", &val))
				{
					return val;
				}
				return false;
			}
			
			//! Set the autoscroll attribute.
			/** This function sets the autoscroll attribute.
			 @param autoscroll True if you want to auto scroll when edit.
			 */
			void setAutoScroll(const bool autoscroll)
			{
				setAttrValue("autoscroll", BoolValue(autoscroll));
			}
			
			//! Retrieves the autoscroll attribute.
			/** The function retrieves the autoscroll attribute.
			 @return The autoscroll attribute value.
			 */
			bool getAutoScroll() const noexcept
			{
				BoolValue val;
				if(getAttrValue("autoscroll", &val))
				{
					return val;
				}
				return false;
			}
			
			//! Set the autofixwidth attribute.
			/** This function sets the autofixwidth attribute.
			 @param autofixwidth True if you want the width to be recalculate when edit.
			 */
			void setAutoFixWidth(const bool autofixwidth)
			{
				setAttrValue("autofixwidth", BoolValue(autofixwidth));
			}
			
			//! Retrieves the autofixwidth attribute.
			/** The function retrieves the autofixwidth attribute.
			 @return The autofixwidth attribute value.
			 */
			bool getAutoFixWidth() const noexcept
			{
				BoolValue val;
				if(getAttrValue("autofixwidth", &val))
				{
					return val;
				}
				return false;
			}
			
			// ================================================================================ //
			//									TEXTFIELD VIEW									//
			// ================================================================================ //
			
			class View // => jLabel
			{
				friend void TextField::updateViews(const bool);
				
				wTextField	m_textfield;
				
			public:
				View(sTextField textfield);
				
				virtual ~View();
				
				//! Retrieves the textfield.
				/** This function retrieves the textfield.
				 @return The textfield.
				 */
				sTextField getTextField() const noexcept;
				
				//! Retrieves the textfield writer.
				/** This function retrieves the textfield writer.
				 @return The writer.
				 */
				sWriter getWriter() const noexcept;
				
			protected:
				
				//! Receives the notification that the textfield's text changed.
				/** The function receives the notification that the textfield's text changed
				 */
				virtual void textfieldTextChanged() = 0;
				
				//! Receives the notification that the textfield's text has been edited.
				/** The function receives the notification that the textfield's text has been edited.
				 */
				virtual void textfieldTextEdited() = 0;
			};
		};
}

#endif