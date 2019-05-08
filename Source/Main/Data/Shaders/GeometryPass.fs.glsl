#version 440 core

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedo;
layout (location = 3) out vec4 gMRA;

in vec2 TextureCoordinates_FS_in;
in vec3 WorldPosition_FS_in;
in vec3 Normal_FS_in;

uniform sampler2D AlbedoMap;
uniform sampler2D NormalMap;
uniform sampler2D MetallicMap;
uniform sampler2D RoughnessMap;
uniform sampler2D AOMap;

uniform vec4 AlbedoColor;
uniform vec4 NormalColor;
uniform vec4 MetallicColor;
uniform vec4 RoughnessColor;
uniform vec4 AOColor; 

void main()
{    
	float metallic = vec4(texture(MetallicMap, TextureCoordinates_FS_in) * MetallicColor).r;
	float roughness = vec4(texture(RoughnessMap, TextureCoordinates_FS_in) * RoughnessColor).r;
	float ao = vec4(texture(AOMap, TextureCoordinates_FS_in) * AOColor).r;
	vec3 albedo = pow(texture(AlbedoMap, TextureCoordinates_FS_in).rbg, vec3(2.2));
	gPosition = vec4(WorldPosition_FS_in, 1.0);
	gNormal = vec4(normalize(Normal_FS_in), 1.0);
    //gNormal = vec4(texture(NormalMap, TextureCoordinates_FS_in).xyz * NormalColor.rgb, 1.0);
    gAlbedo = vec4(albedo * AlbedoColor.rgb, 1.0);
	gMRA = vec4(metallic, roughness, ao, 1.0);
} 
