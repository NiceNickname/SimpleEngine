#include "pch.h"
#include <glm/glm.hpp>
#include "Shader.h"
#include "Renderer2D.h"
#include "OpenGL/OpenGLShader.h"
#include "DX11/DX11Shader.h"

namespace Engine {

	Engine::Shader* Shader::Create(const std::string& vertexPath, const std::string& fragmentPath)
	{
		if (Renderer2D::GetApi() == Renderer2D::API::NONE)
			std::cout << "None rendering API is set\n";
		else if (Renderer2D::GetApi() == Renderer2D::API::OPENGL)
			return new OpenGLShader(vertexPath, fragmentPath);
		else if (Renderer2D::GetApi() == Renderer2D::API::DX11)
			return new DX11Shader(vertexPath, fragmentPath);
	}

}