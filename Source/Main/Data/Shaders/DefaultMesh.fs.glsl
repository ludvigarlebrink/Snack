#version 450 core

layout (location = 0) out vec4 FragColor;

in vec2 TextureCoordinates_FS_in;

void main()
{
    FragColor = vec4(1.0, 0.2, 0.2, 1.0);
}
