#version 440 core
layout (location = 0) in vec3 Position_VS_in;

out vec2 TexCoords_FS_in;

void main()
{
    TexCoords_FS_in = vec2(Position_VS_in.x * 0.5 + 0.5, Position_VS_in.y * 0.5 + 0.5);
    gl_Position = vec4(Position_VS_in, 1.0);
}
