#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 widok;
uniform mat4 rzutowanie;

void main()
{
   gl_Position = rzutowanie * widok * model * vec4(position, 1.0f);
}
