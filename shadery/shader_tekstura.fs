#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
   color = vec4(texture(ourTexture1, TexCoord), 1.0f);
}
