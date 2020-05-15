#pragma once

#include <sstream>

#include "Event.h"

namespace FEE {

	class FEE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : m_MousePosX(x), m_MousePosY(y) {}

		inline float GetX() const { return m_MousePosX; }
		inline float GetY() const { return m_MousePosY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << GetX() << ", " << GetY();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse	| EventCategoryInput )

	private:
		float m_MousePosX;
		float m_MousePosY;

	};

	class FEE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset) 
			: m_xOffset(xOffset), m_yOffset(yOffset) {}

		inline float GetOffsetX() const { return m_xOffset; }
		inline float GetOffsetY() const { return m_yOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetOffsetX() << ", " << GetOffsetY();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY( EventCategoryMouse | EventCategoryInput )

	private:
		float m_xOffset, m_yOffset;
	};

	class FEE_API MouseButtonEvent : public Event
	{
	public:

		inline int GetMouseButton() const { return m_button; }
		
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int button)
			: m_button(button) {}

		int m_button;
	};

	class FEE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)

	};

	class FEE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

	};


}