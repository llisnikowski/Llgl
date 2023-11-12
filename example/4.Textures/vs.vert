#version 450 core

layout (location = 0) in vec2 inPos;
layout (location = 1) in vec2 inTextureCoords;


out gl_PerVertex
{
    vec4 gl_Position;
};
out vec2 vertTexCoords;


void main()
{
    gl_Position = vec4(inPos, 0.f, 1.f);
    vertTexCoords = inTextureCoords;
}