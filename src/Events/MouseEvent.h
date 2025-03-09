#pragma once

#include "Event.h"

#include <iostream>

namespace JKYJ
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) { }

		inline float GetX() const { return m_MouseX; };
		inline float GetY() const { return m_MouseY; };

		std::string ToString() const override
		{
			return "MouseMovedEvent: (" + std::to_string(m_MouseX) + ", " +  std::to_string(m_MouseY) + ")\n";
		}

		virtual int GetCategoryFlag() const override { return EventCategoryMouse | EventCategoryInput; } // 1010

		static EventType GetStaticType() { return EventType::MouseMoved; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseMoved"; }
	
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {
		}

		inline float GetXOffset() const { return m_XOffset; };
		inline float GetYOffset() const { return m_YOffset; };

		std::string ToString() const override
		{
			return "MouseScrolledEvent: (" + std::to_string(m_XOffset) + ", " + std::to_string(m_YOffset) + ")\n";
		}

		virtual int GetCategoryFlag() const override { return EventCategoryMouse | EventCategoryInput; } // 1010

		static EventType GetStaticType() { return EventType::MouseScrolled; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseScrolled"; }

	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }
		virtual int GetCategoryFlag() const override { return EventCategoryMouse | EventCategoryInput; }

	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {
		}

		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button, int repeatCount)
			: MouseButtonEvent(button) { }

		std::string ToString() const override
		{
			return "MouseButtonPressedEvent: " + std::to_string(m_Button) + "\n";
		}

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseButtonPressed"; }
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {
		}


		std::string ToString() const override
		{
			return "MouseButtonReleasedEvent: " + std::to_string(m_Button) + "\n";
		}

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseButtonReleased"; }
	};
}