#include "pch.h"
#include "Window/GlfwWindow.h"
#include "Renderer.h"

#include "DX11/DX11RenderingApi.h"
#include "OpenGL/OpenGLIndexBuffer.h"
#include "OpenGL/OpenGLVertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/OpenGLRenderingApi.h"
#include "DX11/DX11Shader.h"


namespace Engine {

	std::unique_ptr<RenderingAPI> Renderer::m_Api;
	std::unique_ptr<BatchRenderer> Renderer::m_BatchRenderer;
	Renderer::API Renderer::m_ApiName = Renderer::API::NONE;

	void Renderer::Init()
	{
	}

	void Renderer::ShutDown()
	{
		if (m_Api.get() != nullptr)
			m_Api.reset();
	}

	void Renderer::SwapBuffers()
	{
		m_Api->SwapBuffers();
	}

	void Renderer::ClearBuffer()
	{
		m_Api->ClearBuffer();
	}

	void Renderer::Begin()
	{
		m_BatchRenderer->Begin();
	}

	void Renderer::End()
	{
		m_BatchRenderer->End();
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		m_BatchRenderer->DrawQuad(position, size, color);
	}

	void Renderer::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture)
	{
		m_BatchRenderer->DrawQuad(position, size, texture);
	}

	void Renderer::Draw()
	{
		m_BatchRenderer->Draw();
	}

	void Renderer::Flush()
	{
		// TODO: drawcall
	}



	void Renderer::SetApi(API api, std::unique_ptr<Window>& window)
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


	void Renderer::Prepare()
	{
		m_Api->Prepare();
	}


}
