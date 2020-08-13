#include "pch.h"

#include "Texture.h"
#include "Renderer2D.h"
#include <d3d11.h>
#include "OpenGL/OpenGLTexture.h"
#include "DX11/DX11Texture.h"

namespace Engine {



	Engine::Texture* Texture::Create(const std::string& path)
	{
		if (Renderer2D::GetApi() == Renderer2D::API::NONE)
			std::cout << "None rendering API is set\n";
		else if (Renderer2D::GetApi() == Renderer2D::API::OPENGL)
			return new OpenGLTexture(path);
		else if (Renderer2D::GetApi() == Renderer2D::API::DX11)
			return new DX11Texture(path);
	}

}