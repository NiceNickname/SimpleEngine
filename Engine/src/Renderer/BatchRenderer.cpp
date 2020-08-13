#include "pch.h"

#include "Renderer2D.h"
#include "BatchRenderer.h"
#include "DX11/DX11BatchRenderer.h"
#include "OpenGL/OpenGLBatchRenderer.h"

namespace Engine {



	Engine::BatchRenderer* BatchRenderer::Create()
	{
		if (Renderer2D::GetApi() == Renderer2D::API::OPENGL)
			return new OpenGLBatchRenderer();
		else if (Renderer2D::GetApi() == Renderer2D::API::DX11)
			return new DX11BatchRenderer();
	}

}