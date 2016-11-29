#version 330 core

layout (location = 0) in vec3 position;

out vec3 TexCoords;

uniform mat4 widok;
uniform mat4 rzutowanie;

void main()
{
	vec4 pos = rzutowanie * widok * vec4(position, 1.0f);
	gl_Position = pos.xyww;
	TexCoords = position;
}
