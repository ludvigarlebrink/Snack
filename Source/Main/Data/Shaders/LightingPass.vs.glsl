#version 440 core
layout (location = 0) in vec3 aPos;

out vec2 TexCoords_FS_in;

void main()
{
    TexCoords_FS_in = aPos.xy;
    gl_Position = vec4(aPos, 1.0);
}
