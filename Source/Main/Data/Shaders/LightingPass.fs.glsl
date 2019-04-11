#version 440 core

out vec4 FragColor;
  
in vec2 TexCoords_FS_in;

uniform sampler2D GPosition;
uniform sampler2D GNormal;
uniform sampler2D GAlbedo;

struct DirectonalLight 
{
	vec3 position;
	vec3 direction;
	vec3 color;
	float intensity;
};

uniform int LightCount = 0;
uniform DirectonalLight DirectionalLights[16];
uniform vec3 ViewPosition = vec3(0.0, 0.0, 0.0);

void main()
{             
	float ambientStrength = 0.1;
	vec3 ambient = vec3(0.0, 0.0, 0.0);
	vec3 diffuse = vec3(0.0, 0.0, 0.0);
	float specularStrength = 0.9;
	vec3 specular = vec3(0.0, 0.0, 0.0);
	int shininess = 256;
	// retrieve data from G-buffer
	vec4 WorldPosition = texture(GPosition, TexCoords_FS_in);
	vec4 Normal = texture(GNormal, TexCoords_FS_in);
	vec4 Albedo = texture(GAlbedo, TexCoords_FS_in);
	vec3 viewDir = normalize(ViewPosition - WorldPosition.xyz);
	int specCount = 0;
	for (int i = 0; i < LightCount; ++i) 
	{
		ambient += DirectionalLights[i].color * ambientStrength;		
		float diff = max(dot(Normal.xyz, DirectionalLights[i].direction), 0.0);
		diffuse += diff * DirectionalLights[i].color;

		
		vec3 reflectDir = reflect(-DirectionalLights[i].direction, Normal.xyz); 
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
		if (spec > 0) {
			++specCount;
		}
		specular += specularStrength * spec * DirectionalLights[i].color;
		
	}
	if (LightCount > 0) 
	{
		ambient /= LightCount;
		diffuse /= LightCount;
	}
	if (specCount > 0) 
	{
		specular /= specCount;
	}
	vec3 result = (ambient + diffuse + specular) * Albedo.xyz;
	FragColor = vec4(result, 1.0);
}  
