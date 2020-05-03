#include "Shader.h"
#include <fstream>
#include <vector>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	// Read our shaders into the appropriate buffers
	std::string vertexSource = fromFile(vertexPath);
	std::string fragmentSource = fromFile(fragmentPath);

		// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = (const GLchar*)vertexSource.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.
		std::cout << vertexPath << " compile error" << std::endl;
		for (GLchar ch : infoLog)
			std::cout << ch;
		std::cout << std::endl;


		// In this simple program, we'll just leave
		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = (const GLchar*)fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		// Use the infoLog as you see fit.
		std::cout << fragmentPath << " compile error" << std::endl;
		for (GLchar ch : infoLog)
			std::cout << ch;
		std::cout << std::endl;

		// In this simple program, we'll just leave
		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	m_Id= glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(m_Id, vertexShader);
	glAttachShader(m_Id, fragmentShader);

	// Link our program
	glLinkProgram(m_Id);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_Id, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_Id, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_Id);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Use the infoLog as you see fit.

		std::cout << vertexPath << " " << fragmentPath << " link error" << std::endl;
		for (GLchar ch : infoLog)
			std::cout << ch;
		std::cout << std::endl;

		// In this simple program, we'll just leave
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(m_Id, vertexShader);
	glDetachShader(m_Id, fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_Id);
}

void Shader::Bind()
{
	glUseProgram(m_Id);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

std::string Shader::fromFile(const std::string& path)
{
	std::ifstream fin(path);
	std::string line;
	std::string result = "";
	while (getline(fin, line))
	{
		result += line + '\n';
	}
	fin.close();
	return result;
}

int Shader::GetUniform(const std::string& name)
{
	if (m_LocationCache.find(name) != m_LocationCache.end())
		return m_LocationCache[name];

	int result = glGetUniformLocation(m_Id, name.c_str());
	if (result == -1)
		return result;
	else
	{
		m_LocationCache.insert(std::make_pair(name, result));
		return result;
	}
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniform(name), value);
}
