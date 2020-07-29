#include "pch.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "OpenGL/OpenGLIndexBuffer.h"

namespace Engine {

	
	Engine::IndexBuffer* IndexBuffer::Create(unsigned int* data, unsigned int size)
	{
		if (Renderer::GetApi() == Renderer::API::NONE)
			std::cout << "None rendering API is set\n";
		else if (Renderer::GetApi() == Renderer::API::OPENGL)
			return new OpenGLIndexBuffer(data, size);
		else if (Renderer::GetApi() == Renderer::API::DX11)
			std::cout << "DX11 currently is not supported\n";
	}

}