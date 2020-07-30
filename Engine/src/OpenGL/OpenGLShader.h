#include <string>
#include <GL/glew.h>
#include <unordered_map>
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer/Shader.h"


namespace Engine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);
		~OpenGLShader();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual std::string fromFile(const std::string& path) override;

		virtual int GetUniform(const std::string& name) override
			;
		virtual void SetUniform1i(const std::string& name, int value) override;
		virtual void SetUniformIntArray(const std::string& name, int size, int* value) override;

		virtual void SetUniform1f(const std::string& name, float value) override;
		virtual void SetUniform2f(const std::string& name, float x, float y) override;
		virtual void SetUniform3f(const std::string& name, const glm::vec3& value) override;

		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& value) override;
	private:
		unsigned int m_Id;
		std::unordered_map<std::string, int> m_LocationCache;
	};
}