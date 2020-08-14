#pragma once

#include "Renderer/Renderer2D.h"
#include "Events/Event.h"
#include "Events/ApplicationEvents.h"
#include "Events/KeyboardEvents.h"
#include "Events/MouseEvents.h"

namespace Engine
{
	class App
	{
	public:
		App() { s_Instance = this; };
		virtual ~App() = default;

		void Run();
		const std::unique_ptr<Window>& GetWindow() { return m_Window; }
		static App* Get() { return s_Instance; }

	private:
		void ImGuiBegin();
		void ImGuiEnd();
		void ShutDown();
		void OnEvent(Event& e);

		void OnWindowClose(WindowClosedEvent& e);
		void OnWindowResize(WindowResizedEvent& e);


	protected:
		virtual void Start() {}
		virtual void Update() {}
		virtual void Render() {}
		virtual void ImGuiRender() {}
		virtual void ChooseApi() {}

		// keyboard event callbacks
		virtual void OnKeyPressed(KeyPressedEvent& e) {}
		virtual void OnKeyReleased(KeyReleasedEvent& e) {}
		virtual void OnKeyTyped(KeyTypedEvent& e) {}
		
		// mouse event callbacks
		virtual void OnMouseButtonPressed(MouseButtonPressedEvent& e) {}
		virtual void OnMouseButtonReleased(MouseButtonReleasedEvent& e) {}
		virtual void OnMouseMoved(MouseMovedEvent& e) {}
		virtual void OnMouseScrolled(MouseScrolledEvent& e) {}
		

	private:
		static App* s_Instance;
	protected:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		Renderer2D::API m_Api = Renderer2D::API::NONE;
	};
}

