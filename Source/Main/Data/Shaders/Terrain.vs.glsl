#version 440 core

layout (location = 0) in vec2 Position_VS_in;

uniform mat4 Model = mat4(1.0);
uniform mat4 ViewProjection = mat4(1.0);

out vec3 WorldPos_TCS_in;

void main()
{
    vec4 worldPosition = Model * vec4(Position_VS_in.x, 0.0f, Position_VS_in.y, 1.0);
    WorldPos_TCS_in = worldPosition.xyz;
    gl_Position = worldPosition;
}
