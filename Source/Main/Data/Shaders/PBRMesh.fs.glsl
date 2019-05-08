#version 440 core

out vec4 FragColor;

in vec2 TextureCoordinates_FS_in;
in vec3 Normal_FS_in;
in vec3 WorldPos_FS_in;

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
  
vec3 FresnelSchlick(float cosTheta, vec3 F0)
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
	vec3 albedo = pow(texture(AlbedoMap, TextureCoordinates_FS_in).rgb, vec3(2.2)) * AlbedoColor;
    //vec3 normal = texture(NormalMap, TextureCoordinates_FS_in).xyz * NormalColor.rgb;
	vec3 normal = Normal_FS_in;
    float metallic = vec4(texture(MetallicMap, TextureCoordinates_FS_in) * MetallicColor).r;
    float roughness = vec4(texture(RoughnessMap, TextureCoordinates_FS_in) * RoughnessColor).r;
    float ao = vec4(texture(AOMap, TextureCoordinates_FS_in) * AOColor).r;

    vec3 N = normalize(normal);
    vec3 V = normalize(ViewPosition - WorldPos_FS_in);
	           
    vec3 Lo = vec3(0.0);
	vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

	for (int i = 0; i < PointLightCount; ++i)
	{
		// calculate per-light radiance
        vec3 L = normalize(PointLights[i].position - WorldPos_FS_in);
        vec3 H = normalize(V + L);
        float distance    = length(PointLights[i].position - WorldPos_FS_in);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = PointLights[i].color * attenuation;        
        
        // cook-torrance brdf
        float NDF = DistributionGGX(N, H, roughness);        
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = FresnelSchlick(max(dot(H, V), 0.0), F0);       
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;	  
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
        vec3 specular     = numerator / max(denominator, 0.001);  
            
        // add to outgoing radiance Lo
        float NdotL = max(dot(N, L), 0.0);                
        Lo += (kD * albedo / PI + specular) * radiance * NdotL; 
	}  
  
    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;
	
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  
   
    FragColor = vec4(color, 1.0);
}  
