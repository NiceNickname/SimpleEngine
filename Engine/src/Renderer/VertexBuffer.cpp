#include "pch.h"
#include "VertexBuffer.h"
#include "Renderer.h"
#include "OpenGL/OpenGLVertexBuffer.h"

namespace Engine {

	VertexBuffer* VertexBuffer::Create(float* data, unsigned int size)
	{
		if (Renderer::GetApi() == Renderer::API::NONE)
			std::cout << "None API is set\n";
		else if (Renderer::GetApi() == Renderer::API::OPENGL)
			return new OpenGLVertexBuffer(data, size);
		else if (Renderer::GetApi() == Renderer::API::DX11)
			std::cout << "DX11 currently is not supported\n";
	}

}