#include "pch.h"


#include "Renderer2D.h"
#include "OpenGL/OpenGLIndexBuffer.h"
#include "DX11/DX11IndexBuffer.h"

namespace Engine {

	
	Engine::IndexBuffer* IndexBuffer::Create(void* data, unsigned int size)
	{
		if (Renderer2D::GetApi() == Renderer2D::API::NONE)
			std::cout << "None rendering API is set\n";
		else if (Renderer2D::GetApi() == Renderer2D::API::OPENGL)
			return new OpenGLIndexBuffer(data, size);
		else if (Renderer2D::GetApi() == Renderer2D::API::DX11)
			return new DX11IndexBuffer(data, size);
	}

}