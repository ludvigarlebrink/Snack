#version 440 core

layout (location = 0) out vec4 FragColor;

in vec3 Normal_FS_in;
in vec2 TextureCoordinates_FS_in;

uniform struct DirectionalLight
{
	vec3 direction;
	vec3 color;
	float intensity;
} DirectionalLights[4];

uniform int DirectionalLightCount;

void main()
{
	vec3 finalColor = DirectionalLights[0].color * dot(normalize(Normal_FS_in), DirectionalLights[0].direction);
    FragColor = vec4(clamp(finalColor, vec3(0.0), vec3(1.0)), 1.0);
}
