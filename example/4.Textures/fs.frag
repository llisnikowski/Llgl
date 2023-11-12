#version 450 core

in vec2 vertTexCoords;

out vec4 Color;
layout (binding = 0) uniform sampler2D tex;

void main()
{
    //Color = vec4(vertColor, 1.f);
    Color = vec4(texture(tex, vertTexCoords).rgb, 1.f);
}