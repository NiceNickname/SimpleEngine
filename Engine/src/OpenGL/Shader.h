#include <string>
#include <GL/glew.h>
#include <unordered_map>
#include "glm/gtc/matrix_transform.hpp"


namespace Engine
{
	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();
		void Bind();
		void Unbind();
		std::string fromFile(const std::string& path);

		int GetUniform(const std::string& name);

		void SetUniform1i(const std::string& name, int value);
		void SetUniformIntArray(const std::string& name, int size, int* value);


		void SetUniform1f(const std::string& name, float value);
		void SetUniform2f(const std::string& name, float x, float y);
		void SetUniform3f(const std::string& name, const glm::vec3& value);


		void SetUniformMat4f(const std::string& name, const glm::mat4& value);
	private:
		unsigned int m_Id;
		std::unordered_map<std::string, int> m_LocationCache;
	};
}