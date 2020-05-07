#include <string>
#include <GL/glew.h>
#include <unordered_map>
#include "Math/Math.h"


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


		void SetUniform1f(const std::string& name, float value);
		void SetUniform2f(const std::string& name, float x, float y);
		void SetUniform3f(const std::string& name, const Vector3f& value);


		void SetUniformMat4f(const std::string& name, const Mat4f& value);
	private:
		unsigned int m_Id;
		std::unordered_map<std::string, int> m_LocationCache;
	};
}