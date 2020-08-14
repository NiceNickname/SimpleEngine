#pragma once
#include "Event.h"

namespace Engine {


	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height)
		{
			m_Category = Event::Category::APPLICATION;
			m_Type = Event::Type::WINDOWRESIZED;
		}

		static Event::Type GetType() { return Event::Type::WINDOWRESIZED; }

		unsigned int m_Width, m_Height;

	};

	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent()
		{
			m_Category = Event::Category::APPLICATION;
			m_Type = Event::Type::WINDOWCLOSED;
		}

		static Event::Type GetType() { return Event::Type::WINDOWCLOSED; }
	};

}