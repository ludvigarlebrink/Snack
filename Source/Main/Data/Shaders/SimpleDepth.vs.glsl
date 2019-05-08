#version 440 core

layout (location = 0) in vec3 Position_VS_in;

uniform mat4 LightSpaceMatrix;
uniform mat4 Model;

void main()
{
    gl_Position = LightSpaceMatrix * Model * vec4(/*Position_VS_in, */1.0);
}  
