#include "pch.h"
#include "Window/GlfwWindow.h"
#include "Renderer2D.h"

#include "DX11/DX11RenderingApi.h"
#include "OpenGL/OpenGLIndexBuffer.h"
#include "OpenGL/OpenGLVertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/OpenGLRenderingApi.h"
#include "DX11/DX11Shader.h"


namespace Engine {

	std::unique_ptr<RenderingAPI> Renderer2D::m_Api;
	std::unique_ptr<BatchRenderer> Renderer2D::m_BatchRenderer;
	Renderer2D::API Renderer2D::m_ApiName = Renderer2D::API::NONE;

	void Renderer2D::Init()
	{
	}

	void Renderer2D::ShutDown()
	{
		if (m_Api.get() != nullptr)
			m_Api.reset();
	}

	void Renderer2D::SwapBuffers()
	{
		m_Api->SwapBuffers();
	}

	void Renderer2D::ClearBuffer()
	{
		m_Api->ClearBuffer();
	}

	void Renderer2D::Begin()
	{
		m_BatchRenderer->Begin();
	}

	void Renderer2D::End()
	{
		m_BatchRenderer->End();
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		m_BatchRenderer->DrawQuad(position, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture)
	{
		m_BatchRenderer->DrawQuad(position, size, texture);
	}

	void Renderer2D::Draw()
	{
		m_BatchRenderer->Draw();
	}



	void Renderer2D::SetApi(API api, std::unique_ptr<Window>& window)
	{
		m_ApiName = api;
		if (api == API::NONE)
			std::cout << "Cannot set API to NONE\n";
		else if (api == API::OPENGL)
		{
			if (m_Api.get() != nullptr)
				m_Api.reset();
			window.reset(Window::Create("Engine", 1280, 720, Window::Type::GLFW));
			m_Api.reset(RenderingAPI::Create(window));
			m_BatchRenderer.reset(BatchRenderer::Create());
		}
		else if (api == API::DX11)
		{
			if (m_Api.get() != nullptr)
				m_Api.reset();
			window.reset(Window::Create("Engine", 1280, 720, Window::Type::WIN32WINDOW));
			m_Api.reset(RenderingAPI::Create(window));
			m_BatchRenderer.reset(BatchRenderer::Create());
		}
	}


	void Renderer2D::Prepare()
	{
		m_Api->Prepare();
	}


}
