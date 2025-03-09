#pragma once

#include "Event.h"

#include <iostream>

namespace JKYJ
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:m_Width(width), m_Height(height) { }

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			return "WindowResizeEvent: (" + std::to_string(m_Width) + ", " + std::to_string(m_Height) + ")\n";
		}

		virtual int GetCategoryFlag() const override { return EventCategoryApplication; }
		static EventType GetStaticType() { return EventType::WindowResize; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowResize"; }

	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		virtual int GetCategoryFlag() const override { return EventCategoryApplication; }
		static EventType GetStaticType() { return EventType::WindowClose; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowClose"; }
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		virtual int GetCategoryFlag() const override { return EventCategoryApplication; }
		static EventType GetStaticType() { return EventType::AppTick; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "AppTick"; }
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		virtual int GetCategoryFlag() const override { return EventCategoryApplication; }
		static EventType GetStaticType() { return EventType::AppUpdate; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "AppUpdate"; }
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		virtual int GetCategoryFlag() const override { return EventCategoryApplication; }
		static EventType GetStaticType() { return EventType::AppRender; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "AppRender"; }
	};
}