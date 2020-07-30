#pragma once
#include <glm/glm.hpp>
namespace Engine {

	class Shader
	{
	public:
		static Shader* Create(const std::string& vertexPath, const std::string& fragmentPath);
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual std::string fromFile(const std::string& path) = 0;

		virtual int GetUniform(const std::string& name) { return -1; };
		
		virtual void SetUniform1i(const std::string& name, int value) {};
		virtual void SetUniformIntArray(const std::string& name, int size, int* value)  {};
		
		virtual void SetUniform1f(const std::string& name, float value) {};
		virtual void SetUniform2f(const std::string& name, float x, float y) {};
		virtual void SetUniform3f(const std::string& name, const glm::vec3& value) {};


		virtual void SetUniformMat4f(const std::string & name, const glm::mat4 & value) {};
	};

}