#pragma once

#include <string>
#include <functional>


namespace JKYJ
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

#define BIT(x) (1 << x)
	// Used to filter events to get a type of event not the specic type
	// ex) want to get any type of mouse events, but not specific type of mouse event like scrolling
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0), // 1
		EventCategoryInput = BIT(1), // 10
		EventCategoryKeyboard = BIT(2), // 100
		EventCategoryMouse = BIT(3), // 1000
		EventCategoryMouseButton = BIT(4), // 10000
	};

	class Event
	{
		friend class EventDispatcher;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlag() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsCategory(EventCategory category) const
		{
			return GetCategoryFlag() & category;
		}

	protected:
		bool m_handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		// using is alternative to typedef
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStatcType())
			{
				m_Event.m_handled = func(*(T*) &m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
}