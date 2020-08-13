#include "pch.h"

#include "RenderingAPI.h"
#include "Renderer2D.h"
#include "OpenGL/OpenGLRenderingApi.h"
#include "DX11/DX11RenderingApi.h"

namespace Engine {



	RenderingAPI* RenderingAPI::Create(const std::unique_ptr<Window>& window)
	{
		if (Renderer2D::GetApi() == Renderer2D::API::OPENGL)
			return new OpenGLRenderingApi(window);
		else if (Renderer2D::GetApi() == Renderer2D::API::DX11)
			return new DX11RenderingApi(window);
	}

}