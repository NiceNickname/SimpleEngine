#pragma once
#include "Event.h"

namespace Engine {

	class KeyboardEvent : public Event
	{
	public:
		int m_KeyCode;
	};


	class KeyPressedEvent : public KeyboardEvent
	{
	public:
		KeyPressedEvent(int keycode, bool repeat)
			: m_Repeat(repeat)
		{
			m_KeyCode = keycode;
			m_Category = Event::Category::KEYBOARD;
			m_Type = Event::Type::KEYPRESSED;
		}

		static Event::Type GetType() { return Event::Type::KEYPRESSED; }

		bool m_Repeat;
	};


	class KeyReleasedEvent : public KeyboardEvent
	{
	public:
		KeyReleasedEvent(int keycode)
		{
			m_KeyCode = keycode;
			m_Category = Event::Category::KEYBOARD;
			m_Type = Event::Type::KEYRELEASED;
		}

		static Event::Type GetType() { return Event::Type::KEYRELEASED; }
	};

	class KeyTypedEvent : public KeyboardEvent
	{
	public:
		KeyTypedEvent(int keycode)
		{
			m_KeyCode = keycode;
			m_Category = Event::Category::KEYBOARD;
			m_Type = Event::Type::KEYTYPED;
		}
	
		static Event::Type GetType() { return Event::Type::KEYTYPED; }

	};

}