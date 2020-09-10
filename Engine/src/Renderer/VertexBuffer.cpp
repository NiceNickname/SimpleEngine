#include "pch.h"
#include "VertexBuffer.h"
#include "Renderer2D.h"
#include "OpenGL/OpenGLVertexBuffer.h"
#include "DX11/DX11VertexBuffer.h"

namespace Engine {

	VertexBuffer* VertexBuffer::Create(void* data, unsigned int size)
	{
		if (Renderer2D::GetApi() == Renderer2D::API::NONE)
			std::cout << "None API is set\n";
		else if (Renderer2D::GetApi() == Renderer2D::API::OPENGL)
			return new OpenGLVertexBuffer(data, size);
		else if (Renderer2D::GetApi() == Renderer2D::API::DX11)
			return new DX11VertexBuffer(data, size);
	}

}