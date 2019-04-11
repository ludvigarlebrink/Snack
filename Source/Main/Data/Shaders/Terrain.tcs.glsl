#version 410 core

layout (vertices = 3) out;

in vec3 WorldPos_TCS_in[];

out vec3 WorldPos_TES_in[];

void main()
{
    WorldPos_TES_in[gl_InvocationID] = WorldPos_TCS_in[gl_InvocationID];

    gl_TessLevelOuter[0] = 4.0;
    gl_TessLevelOuter[1] = 4.0;
    gl_TessLevelOuter[2] = 4.0;
    gl_TessLevelInner[0] = 2.0;
}
