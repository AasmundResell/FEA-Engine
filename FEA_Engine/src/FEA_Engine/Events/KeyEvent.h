#pragma once

#include "Event.h"

namespace FEE {


	//this is an abstract class
	class FEE_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:

		//this is the actual value of the key that is being pushed
		KeyEvent(int keyCode) : m_keyCode(keyCode) {}
		
		int m_keyCode;	
	};

	class FEE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_keyRepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_keyRepeatCount; }

		std::string ToString() const override
		{
			//needs to check number of key values regarding the time intervall of the push
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode << " (" << m_keyRepeatCount << " repeats)";
			return ss.str();
		}

		//use this macro to be simplify the use of common Event functions
		EVENT_CLASS_TYPE(KeyPressed)
	protected:
		int m_keyRepeatCount;
	};

	class FEE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode): KeyEvent(keyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keyCode;
			return ss.str();

		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class FEE_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keyCode)
			: KeyEvent(keyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_keyCode;
			return ss.str();
		}

		//use this macro to be simplify the use of common Event functions
		EVENT_CLASS_TYPE(KeyTyped)
	};


}

