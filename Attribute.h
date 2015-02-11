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

#ifndef __DEF_KIWI_GUI_ATTRIBUTE__
#define __DEF_KIWI_GUI_ATTRIBUTE__

#include "Doodle.h"

namespace Kiwi
{
    namespace Gui
    {
        template <class T> class AttrTyped;
        
        class Attr;
        typedef shared_ptr<Attr>       sAttr;
        typedef weak_ptr<Attr>         wAttr;
        typedef shared_ptr<const Attr> scAttr;
        typedef weak_ptr<const Attr>   wcAttr;
        
        // ================================================================================ //
        //                                      ATTRIBUTE                                   //
        // ================================================================================ //
        
        //! The attribute is an abstract class that holds a set of values of differents kinds and differents sizes.
        /** The attribute manages a set of values that should be displayed in an inspector. The setter and getter must be override.
         */
        class Attr : public enable_shared_from_this<Attr>
        {
        public:
            class Manager;
            typedef shared_ptr<Manager>         sManager;
            typedef weak_ptr<Manager>           wManager;
            typedef shared_ptr<const Manager>   scManager;
            typedef weak_ptr<const Manager>     swManager;
            
            class Listener;
            typedef shared_ptr<Listener>        sListener;
            typedef weak_ptr<Listener>          wListener;
            typedef shared_ptr<const Listener>  scListener;
            typedef weak_ptr<const Listener>    wcListener;
    
            /** Flags describing the behavior of the attribute.
             @see setInvisible, setDisabled, setSaveable, setNotifyChanges
             */
            enum Behavior
            {
                Invisible			= 1<<0,///< Indicates that the attribute is invisible.
                Disabled			= 1<<1,///< Indicates that the attribute can't be changed.
                Unsaved             = 1<<2,///< Indicates that the attribute is not saved.
                Notifier            = 1<<3,///< Indicates that the attribute should not notify its changes.
                All                 = Invisible | Disabled | Unsaved | Notifier
            };
            
        protected:
            const string    m_name;				///< The name of the attribute.
            const string    m_label;			///< The label of the attribute.
            const string    m_category;			///< The category of the attribute.
            const ulong		m_order;			///< The order of the attribute.
            ulong           m_behavior;			///< The behavior of the attribute.
            bool            m_frozen;           ///< The frozen state of the attribute.
            wManager        m_manager;          ///< The manager of the attribute.
        private:
            set<wListener,
            owner_less<wListener>> m_lists;
            mutex                  m_lists_mutex;
            
        protected:
            
            //! Notify the manager and the listener that the attribute has changed.
            /** The function notifies the manager and the listener that the attribute has changed.
             */
            void notify() noexcept;
            
        public:
            
            //! Constructor.
            /** Allocate and initialize the member values.
             @param name			The name of the attribute (usually only letters and undescore characters).
             @param label			A short description of the attribute in a human readable style.
             @param category		A named category that the attribute fits into.
             @param order			The attribute order.
             @param behavior		A combination of the flags which define the attribute's behavior.
             */
            Attr(string const& name, string const& label, string const& category, const ulong behavior = 0, const ulong order = 0) noexcept;
            
            //! Destructor.
            /** Clear the attribute.
             */
            virtual ~Attr() noexcept;
            
            //! Constructor.
            /** Allocate and initialize the member values.
             @param name			The name of the attribute (usually only letters and undescore characters).
             @param label			A short description of the attribute in a human readable style.
             @param category		A named category that the attribute fits into.
             @param order			The attribute order.
             @param behavior		A combination of the flags which define the attribute's behavior.
             */
            template<class T> inline static shared_ptr<AttrTyped<T>> create(string const& name, string const& label, string const& category, T const& value, const ulong behavior = 0, const ulong order = 0)
            {
                return make_shared<AttrTyped<T>>(name, label, category, value, behavior, order);
            }
            
            //! Retrieve the manager of the attribute.
            /** The function retrieves themanager of the attribute.
             @return The manager of the attribute.
             */
            inline sManager getManager() const noexcept
            {
                return m_manager.lock();
            }
            
            //! Retrieve the type index of the attribute.
            /** The function retrieves the type index of the attribute.
             @return The type index of the attribute.
             */
            virtual type_index getTypeIndex() const noexcept = 0;
            
            //! Retrieve the attribute value as a string.
            /** The function retrieves the attribute value as a string.
             @return The attribute value as a string.
             */
            virtual string getValueAsString() const noexcept = 0;
            
            //! Set the attribute value as a string.
            /** The function sets the attribute value as a string.
             @param value The attribute value as a string.
             */
            virtual void setValueWithString(string const& value) = 0;
            
            //! Retrieve if the attribute is from a specific template.
            /** The function retrieves if the attribute is from a specific template.
             @return true if the attribute is from a specific template.
             */
            template<class T> inline bool isType() const noexcept
            {
                return (type_index)typeid(T) == getTypeIndex();
            }
            
            //! Retrieve if the attribute is from a specific template.
            /** The function retrieves if the attribute is from a specific template.
             @return true if the attribute is from a specific template.
             */
            template<class T> inline shared_ptr<AttrTyped<T>> getShared() noexcept
            {
                return dynamic_pointer_cast<AttrTyped<T>>(shared_from_this());
            }
            
            //! Retrieve the name of the attribute.
            /** The function retrieves the name of the attribute.
             @return The name of the attribute.
             */
            inline string getName() const noexcept
            {
                return m_name;
            }
            
            //! Retrieve the attribute label.
            /** The function retrieves the attribute label.
             @return The attribute label.
             */
            inline string getLabel() const noexcept
            {
                return m_label;
            }
            
            //! Retrieve the attribute category.
            /** The function retrieves the attribute category.
             @return The attribute category.
             */
            inline string getCategory() const noexcept
            {
                return m_category;
            }
            
            //! Retrieve the attribute order.
            /** The function retrieves the attribute order.
             @return The attribute order.
             */
            inline ulong getOrder() const noexcept
            {
                return m_order;
            }
            
            //! Retrieves the whole behavior flags field of the attribute.
            /** The function retrieves the whole behavior flags field of the attribute.
             @return behavior	A combination of the flags which define the attribute's behaviors.
             */
            inline ulong getBehavior() const noexcept
            {
                return m_behavior;
            }
            
            //! Retrieve if the attribute is invisible.
            /** The function retrieves if the attribute is invisible.
             @return True if the attribute is invisible otherwise false.
             */
            inline bool isInvisible() const noexcept
            {
                return m_behavior & Invisible;
            }
            
            //! Retrieve if the attribute is disable.
            /** The function retrieves if the attribute is disable.
             @return True if the attribute is disabled otherwise false.
             */
            inline bool isDisabled() const noexcept
            {
                return m_behavior & Disabled;
            }
            
            //! Retrieve if the attribute is saved.
            /** The function retrieves if the attribute is saved.
             @return True if the attribute is saveable otherwise false.
             */
            inline bool isSaved() const noexcept
            {
                return !(m_behavior & Unsaved);
            }
            
            //! Retrieve if the attribute should notify changes.
            /** The function retrieves if the attribute should notify changes.
             @return True if the attribute should notify changes otherwise false.
             */
            inline bool isNotifier() const noexcept
            {
                return !(m_behavior & Notifier);
            }
            
            //! Retrieve if the attribute is frozen.
            /** The function retrieves if the attribute is frozen.
             @return True if the attribute is frozen, false otherwise.
             */
            inline bool isFrozen() const noexcept
            {
                return m_frozen;
            }
            
            //! Set the whole behavior flags field of the attribute.
            /** The function sets the whole behavior flags field of the attribute.
             @param behavior	A combination of the flags which define the attribute's behaviors.
             */
            void setBehavior(const ulong behavior) noexcept;
            
            //! Set if the attribute is visible or not.
            /** The function sets if the attribute is visible or not.
             @param invisible If true, the attribute will be invisible, if false it will be visible.
             */
            void setInvisible(const bool invisible) noexcept;
            
            //! Set if the attribute is disabled or not.
            /** The function sets if the attribute is disabled or not.
             @param disable If true, the attribute will be disabled, if false it will be enabled.
             */
            void setDisabled(const bool disable) noexcept;
            
            //! Set if the attribute is saved or not.
            /** The function sets if the attribute is saved or not.
             @param disable If true, the attribute will be saved, if false it won't be saved.
             */
            void setSaved(const bool saved) noexcept;
            
            //! Set if the attribute is notifier or not.
            /** The function sets if the attribute is notifier or not.
             @param disable If true, the attribute will be notify changes, if false it won't notify changes.
             */
            void setNotifier(const bool notifier) noexcept;
            
            //! Add an instance listener in the binding list of the attribute.
            /** The function adds an instance listener in the binding list of the attribute.
             @param listener  The listener.
             */
            void addListener(sListener listener);
            
            //! Remove an instance listener from the binding list of the attribute.
            /** The function removes an instance listener from the binding list of the attribute.
             @param listener  The listener.
             */
            void removeListener(sListener listener);
        };
        
        // ================================================================================ //
        //                                  ATTRIBUTE TYPED                                 //
        // ================================================================================ //
        
        template <class T> class AttrTyped : public Attr
        {
        private:
            friend AttrTyped::Manager;
            T       m_value;
            T       m_default;
            T       m_freezed;
            
        public:
            
            //! Constructor.
            /** You should never have to use the function.
             */
            AttrTyped(string const& name, string const& label, string const& category, T const& value, const ulong behavior = 0, const ulong order = 0) : Attr(name, label, category, behavior, order), m_value(value), m_default(value)
            {
                ;
            }
            
            //! Destructor.
            /** You should never have to use the function.
             */
            ~AttrTyped()
            {
                ;
            }
            
            //! Retrieve the type index of the attribute.
            /** The function retrieves the type index of the attribute.
             @return The type index of the attribute.
             */
            inline type_index getTypeIndex() const noexcept override
            {
                return typeid(T);
            }
            
            //! Retrieve the attribute value as a string.
            /** The function retrieves the attribute value as a string.
             @return The attribute value as a string.
             */
            inline string getValueAsString() const noexcept override
            {
                return toString(m_value);
            }
            
            //! Set the attribute value as a string.
            /** The function sets the attribute value as a string.
             @param value The attribute value as a string.
             */
            inline void setValueWithString(string const& value) override
            {
                int todo;
            }
            
            //! Retrieves the values.
            /** The current values.
             @param value The value that to set.
             */
            inline void getValue(T& value) const
            {
                value = m_value;
            }
            
            //! Retrieves the values.
            /** The current values.
             @param value The value that to set.
             */
            inline T getValue() const
            {
                return m_value;
            }
            
            //! Retrieves the default value.
            /** Retrieve the default value.
             @param value The value that to set.
             */
            inline void getDefaultValue(T& value) const
            {
                value = m_default;
            }
            
            //! Retrieve the frozen value.
            /** Retrieve the frozen value.
             @param value The value that to set
             */
            inline void getFrozenValue(T& value) const
            {
                value = m_freezed;
            }
            
            //! Sets the values.
            /** The function sets the current value.
             @param elements The vector of elements.
             @see get
             */
            inline void setValue(T const& value)
            {
                if(m_value != value)
                {
                    m_value = value;
                    notify();
                }
            }
            
            //! Freezes or unfreezes the current value.
            /** Freezes or unfreezes the current value.
             @param frozen If true the attribute will be frozen, if false it will be unfrozen.
             */
            inline void freeze(const bool frozen)
            {
                if(frozen != m_frozen)
                {
                    m_frozen = frozen;
                    m_freezed = m_value;
                }
                notify();
            }
            
            //! Resets the value to its default state.
            /** Resets the value to its default state.
             */
            void resetDefaultValue()
            {
                setValue(m_default);
            }
            
            //! Resets the attribute values to frozen values.
            /** Resets the attribute values to its frozen values.
             */
            void resetFrozenValue()
            {
                setValue(m_freezed);
            }
        };
        
        typedef shared_ptr<AttrTyped<bool>>  sAttrBool;
        typedef shared_ptr<AttrTyped<long>>  sAttrLong;
        typedef shared_ptr<AttrTyped<double>>sAttrDouble;
        typedef shared_ptr<AttrTyped<Point>> sAttrPoint;
        typedef shared_ptr<AttrTyped<Size>>  sAttrSize;
        typedef shared_ptr<AttrTyped<Color>> sAttrColor;
        
        
        // ================================================================================ //
        //                                  ATTRIBUTE MANAGER                               //
        // ================================================================================ //
        
        //! The attribute manager manages a set of attributes.
        /** The attribute manager manages a set of attributes, it allows the setting and the getting of their values and to retrieve them by name or by category.
         @see AttrTyped
         */
        class Attr::Manager : public enable_shared_from_this<Manager>
        {
            map<string, sAttr> m_attrs;
        public:
            
            //! Constructor.
            /** Creates a new attribute manager.
             */
            Manager() noexcept;
            
            //! Destructor.
            /** Free the attributes.
             */
            virtual ~Manager();
            
            //! Initialize the attribute manager.
            /** The function add the pointer of the manager to the attributes.
             */
            void initialize() noexcept;
            
            //! Notify the manager that the values of an attribute has changed.
            /** The function notifies the manager that the values of an attribute has changed.
             @param attr An attribute.
             @return pass true to notify changes to listeners, false if you don't want them to be notified
             */
            virtual bool notify(sAttr attr) = 0;
            
            //! Retrieve all the attributes.
            /** The function retrieves the attributes.
             @param attrs the attributes.
             */
            void getAttrs(vector<sAttr>& attrs) const noexcept;
            
            //! Retrieve a set of attributes.
            /** The function retrieves the attributes.
             @param attrs the attributes.
             @param names the names of the attributes.
             */
            void getAttrs(vector<sAttr>& attrs, vector<string> const& names) const noexcept;
            
            //! Retrieve an attribute.
            /** The function retrieves an attribute.
             @param name the name of the attribute.
             @return the attributes.
             */
            sAttr getAttr(string const& name) const noexcept;
			
			//! Retrieve an attribute.
			/** The function retrieves an attribute.
			 @param name the name of the attribute.
			 @return the attributes.
			 */
			template<class T> inline shared_ptr<AttrTyped<T>> getAttrTyped(string const& name) const noexcept
			{
				sAttr attr = getAttr(name);
				if(attr)
				{
					return attr->getShared<T>();
				}
				else
				{
					return nullptr;
				}
			}

        protected:
            //! ...
            /** ...
             */
            void addAttr(sAttr attr);
            
        };
        
        // ================================================================================ //
        //                                  ATTRIBUTE LISTENER                              //
        // ================================================================================ //
        
        //! The attribute manager listener is a virtual class that can be binded to an attribute manager to be notified of various changes.
        /** The attribute manager listener is a very light class that allows to be notified of the attributes modification.
         */
        class Attr::Listener
        {
        public:
            virtual ~Listener() {}
            
            //! Receive the notification that an attribute has changed.
            /** The function must be implement to receive notifications when an attribute is added or removed, or when its value, appearance or behavior changes.
             @param attr		The attribute that has been modified.
             @param type		The type of notification.
             */
            virtual void notify(sAttr attr) = 0;
        };
    }
}


#endif


