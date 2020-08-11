#include "pch.h"

#include "Renderer.h"
#include "BatchRenderer.h"
#include "DX11/DX11BatchRenderer.h"
#include "OpenGL/OpenGLBatchRenderer.h"

namespace Engine {



	Engine::BatchRenderer* BatchRenderer::Create()
	{
		if (Renderer::GetApi() == Renderer::API::OPENGL)
			return new OpenGLBatchRenderer();
		else if (Renderer::GetApi() == Renderer::API::DX11)
			return new DX11BatchRenderer();
	}

}