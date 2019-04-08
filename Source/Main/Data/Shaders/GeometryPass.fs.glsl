#version 440 core
layout (location = 0) out vec4 gAlbedo;
layout (location = 1) out vec3 gPosition;
layout (location = 2) out vec3 gNormal;

in vec2 TextureCoordinates_FS_in;
in vec3 WorldPosition_FS_in;
in vec3 Normal_FS_in;

void main()
{    
    gPosition = WorldPosition_FS_in;
    gNormal = normalize(Normal_FS_in);
    gAlbedo.rgb = vec3(1.0, 0.0, 1.0);
    gAlbedo.a = 1.0;
} 
