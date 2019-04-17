#version 440 core

out vec4 FragColor;
  
in vec2 TexCoords_FS_in;

uniform sampler2D GPosition;
uniform sampler2D GNormal;
uniform sampler2D GAlbedo;
uniform sampler2D GMRA;

struct DirectonalLight 
{
	vec3 direction;
	vec3 color;
	float intensity;
};

struct PointLight 
{
	vec3 position;
	vec3 color;
	float intensity;
};

uniform int DirectionalLightCount = 0;
uniform DirectonalLight DirectionalLights[16];
uniform int PointLightCount = 0;
uniform PointLight PointLights[16];
uniform vec3 ViewPosition = vec3(0.0, 0.0, 0.0);

#define PI 3.14159265359

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

void main()
{             
	vec4 WorldPosition = texture(GPosition, TexCoords_FS_in);
	vec4 Normal = texture(GNormal, TexCoords_FS_in);
	vec4 Albedo = texture(GAlbedo, TexCoords_FS_in);
	vec3 viewDir = normalize(ViewPosition - WorldPosition.xyz);

	vec4 MRA = texture(GMRA, TexCoords_FS_in);
	float metallic = MRA.x;
	float roughness = MRA.y;
	float ao = MRA.z;

	vec3 Lo = vec3(0.0);

	vec3 F0 = vec3(0.04); 
	F0 = mix(F0, Albedo.xyz, metallic);

	for (int i = 0; i < PointLightCount; ++i) 
	{
		// Light radiance
		vec3 L = normalize(PointLights[i].position - WorldPosition.xyz);
		vec3 H = normalize(viewDir + L);  
		float distance    = length(PointLights[i].position - WorldPosition.xyz);
		float attenuation = 1.0 / (distance * distance);
		vec3 radiance     = PointLights[i].intensity * PointLights[i].color * attenuation;

		// BRDF
		float NDF = DistributionGGX(Normal.xyz, H, roughness);       
		float G   = GeometrySmith(Normal.xyz, viewDir, L, roughness);
		vec3 F  = fresnelSchlick(max(dot(H, viewDir), 0.0), F0);

		vec3 numerator    = NDF * G * F;
		float denominator = 4.0 * max(dot(Normal.xyz, viewDir), 0.0) * max(dot(Normal.xyz, L), 0.0);
		vec3 specular     = numerator / max(denominator, 0.001); 
				
		vec3 kD = vec3(1.0) - F;
		kD *= 1.0 - metallic;
	
		// Outgoing radiance
		float NdotL = max(dot(Normal.xyz, L), 0.0);        
		Lo += (kD * Albedo.xyz / PI + specular) * radiance * NdotL;
	}

	vec3 ambient = vec3(0.03) * Albedo.xyz * ao;
	vec3 color   = ambient + Lo;

	// Gamma correction
	color = color / (color + vec3(1.0));
	color = pow(color, vec3(1.0/2.2)); 

	FragColor = vec4(color, 1.0);
}  
