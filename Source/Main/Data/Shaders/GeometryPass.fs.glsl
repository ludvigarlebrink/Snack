#version 440 core

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedo;

in vec2 TextureCoordinates_FS_in;
in vec3 WorldPosition_FS_in;
in vec3 Normal_FS_in;

void main()
{    
    gPosition = vec4(WorldPosition_FS_in, 1.0);
    gNormal = vec4(normalize(Normal_FS_in), 1.0);
    gAlbedo = vec4(1.0, 0.0, 0.0, 1.0);
} 
