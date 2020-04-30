#include <string>
#include <GL/glew.h>
class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();
	void Bind();
	void Unbind();
	std::string fromFile(const std::string& path);
private:
	unsigned int m_Id;
};