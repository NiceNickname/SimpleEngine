#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in float texIndex;

uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;

void main()
{
	v_Color = color;
	v_TexCoord = texCoord;
	v_TexIndex = texIndex;
	gl_Position = view * model * vec4(position, 1.0);
}