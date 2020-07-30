#include "pch.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "OpenGL/OpenGLIndexBuffer.h"
#include "DX11/DX11IndexBuffer.h"

namespace Engine {

	
	Engine::IndexBuffer* IndexBuffer::Create(unsigned int* data, unsigned int size)
	{
		if (Renderer::GetApi() == Renderer::API::NONE)
			std::cout << "None rendering API is set\n";
		else if (Renderer::GetApi() == Renderer::API::OPENGL)
			return new OpenGLIndexBuffer(data, size);
		else if (Renderer::GetApi() == Renderer::API::DX11)
			return new DX11IndexBuffer(data, size);
	}

}