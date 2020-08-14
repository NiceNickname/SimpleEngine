#pragma once

#include "Event.h"


namespace Engine {


	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float posX, float posY)
			: m_PosX(posX), m_PosY(posY)
		{
			m_Category = Event::Category::MOUSE;
			m_Type = Event::Type::MOUSEMOVED;
		}

		static Event::Type GetType() { return Event::Type::MOUSEMOVED; }

		float m_PosX, m_PosY;
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(int button)
			: m_Button(button)
		{
			m_Category = Event::Category::MOUSE;
			m_Type = Event::Type::MOUSEBUTTONPRESSED;
		}

		static Event::Type GetType() { return Event::Type::MOUSEBUTTONPRESSED; }

		int m_Button;
	};

	class MouseButtonReleasedEvent : public Event 
	{
	public:
		MouseButtonReleasedEvent(int button)
			: m_Button(button)
		{
			m_Category = Event::Category::MOUSE;
			m_Type = Event::Type::MOUSEBUTTONRELEASED;
		}

		static Event::Type GetType() { return Event::Type::MOUSEBUTTONRELEASED; }

		int m_Button;
	};

	class MouseScrolledEvent : public Event
	{
	public:

		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset)
		{
			m_Category = Event::Category::MOUSE;
			m_Type = Event::Type::MOUSESCROLLED;
		}

		static Event::Type GetType() { return Event::Type::MOUSESCROLLED; }

		float m_XOffset;
		float m_YOffset;
	};

}