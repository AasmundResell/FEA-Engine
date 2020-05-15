#pragma once

#include "FEA_Engine/Core.h"

#include <string>
#include <functional>


namespace FEE {

	// Events in the engine is currently blocked, that means that when an event happens
	// it needs to be dealt with then and there

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	//this enum is used if you only want one category of events
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput		    = BIT(1),
		EventCategoryKeyboard	    = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMousebutton    = BIT(4)

	};

	//need to check what type of event and category that is handled
	
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::type; }\
								   virtual EventType GetEventType() const override { return GetStaticType(); }\
								   virtual const char* GetName() {return #type;	}	

	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category; }
	
	class FEE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const { return 0; }
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		//used to check if an event is in the given category 
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;	
			
		}
		//Need to check if an event has been handled or not
		bool m_Handled = false;
	};

	
	//this class is used to check that the event type matches the template argument
	class EventDispatcher
	{
	
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event): m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				//If match will call the event function with the event(?)
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;	
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
	

}