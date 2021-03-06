#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);

void main()
{
	gl_Position = view * model * vec4(position, 1.0);
}