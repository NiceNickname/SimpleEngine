#pragma once
#include <functional>

namespace Engine {

	class Event
	{
	public:
		enum class Type {WINDOWRESIZED = 0, WINDOWCLOSED, MOUSEMOVED, MOUSEBUTTONPRESSED, 
			MOUSEBUTTONRELEASED, MOUSESCROLLED, KEYPRESSED, KEYRELEASED, KEYTYPED};
		enum class Category { APPLICATION = 0, MOUSE, KEYBOARD};

		Type m_Type;
		Category m_Category;

	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		void Dispatch(std::function<void(T&)> DispatchFunc)
		{
			if (m_Event.m_Type == T::GetType())
				DispatchFunc((T&)m_Event);
		}

	private:
		Event& m_Event;
	};
}
