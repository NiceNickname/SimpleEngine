#include "pch.h"
#include <glm/glm.hpp>
#include "Shader.h"
#include "Renderer.h"
#include "OpenGL/OpenGLShader.h"

namespace Engine {



	Engine::Shader* Shader::Create(const std::string& vertexPath, const std::string& fragmentPath)
	{
		if (Renderer::GetApi() == Renderer::API::NONE)
			std::cout << "None rendering API is set\n";
		else if (Renderer::GetApi() == Renderer::API::OPENGL)
			return new OpenGLShader(vertexPath, fragmentPath);
		else if (Renderer::GetApi() == Renderer::API::DX11)
			std::cout << "DX11 currently is not supported\n";
	}

}