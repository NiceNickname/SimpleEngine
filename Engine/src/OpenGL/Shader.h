#include <string>
#include <GL/glew.h>
#include <unordered_map>

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();
	void Bind();
	void Unbind();
	std::string fromFile(const std::string& path);
	int GetUniform(const std::string& name);
	void SetUniform1i(const std::string& name, int i);
private:
	unsigned int m_Id;
	std::unordered_map<std::string, int> m_LocationCache;
};