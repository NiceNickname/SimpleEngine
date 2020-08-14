#pragma once

#include <functional>
#include "Events/Event.h"

namespace Engine {


	class Window
	{

	public:

		enum class Type { WIN32WINDOW = 0, GLFW };

		virtual ~Window() = default;
		static Window* Create(const std::string& name, int width, int height, Type type);

		virtual void Update() = 0;
		virtual bool ShouldClose() = 0;
		virtual void GetFrameBufferSize(int* width, int* height) = 0;
		inline void SetEventCallback(const std::function<void(Event&)>& callback) { m_Callback = callback; }

		const std::string& GetName() const { return m_Name; }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }
		
		inline void SetWidth(unsigned int width) { m_Width = width; }
		inline void SetHeight(unsigned int height) { m_Height = height; }
		inline std::function<void(Event&)>& GetCallback() { return m_Callback; }

	protected:
		std::string m_Name;
		int m_Width;
		int m_Height;

		std::function<void(Event&)> m_Callback;
	};

}