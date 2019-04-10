#version 440 core

layout (location = 0) in vec2 Position_VS_in;

uniform mat4 Model = mat4(1.0);
uniform mat4 ViewProjection = mat4(1.0);

void main()
{
    vec4 worldPosition = Model * vec4(Position_VS_in.x, 0.0f, Position_VS_in.y, 1.0);
    gl_Position = ViewProjection * worldPosition;
}
