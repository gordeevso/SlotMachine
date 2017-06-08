#version 330 core

// fragment shader for sprite rendering
in vec2 TexCoords;
out vec4 color;

uniform sampler2D sprite;

void main()
{
    color =  texture(sprite, TexCoords);
}