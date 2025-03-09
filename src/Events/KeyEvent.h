#pragma once

#include "Event.h"

#include <iostream>

namespace JKYJ
{
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		virtual int GetCategoryFlag() const override { return EventCategoryKeyboard | EventCategoryInput; } // 100 | 10 = 110

	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) { }
		
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode)
			: KeyEvent(keycode) { }


		std::string ToString() const override
		{
			return "KeyPressedEvent: " + std::to_string(m_KeyCode) + "\n";
		}

		static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyPressed"; }

	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		
		std::string ToString() const override
		{
			return "KeyReleasedEvent: " + std::to_string(m_KeyCode) + "\n";
		}

		static EventType GetStaticType() { return EventType::KeyReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyReleased"; }
	};
}