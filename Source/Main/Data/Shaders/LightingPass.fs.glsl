#version 440 core

out vec4 FragColor;
  
in vec2 TexCoords_FS_in;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

//struct DirectonalLight 
//{
//	vec3 position;
//	vec3 direction;
//	vec3 color;
//	float intensity;
//};
//
//uniform int lightCount = 0;
//uniform DirectonalLight directionalLights[16];

void main()
{             
	// float ambientStrength = 0.1;
	// vec3 ambient = vec3(0.0, 0.0, 0.0);
	// vec3 diffuse = vec3(0.0, 0.0, 0.0);
    // retrieve data from G-buffer
    vec4 WorldPosition = texture(gPosition, TexCoords_FS_in);
    vec4 Normal = texture(gNormal, TexCoords_FS_in);
    vec4 Albedo = texture(gAlbedo, TexCoords_FS_in);
	//for (int i = 0; i < lightCount; ++i) 
	//{
	//	ambient += directionalLights[i].color * ambientStrength;		
	//	float diff = max(dot(Normal, directionalLights[i].direction), 0.0);
	//	diffuse += diff * directionalLights[i].color;
	//}
	//if (lightCount > 0) 
	//{
	//	ambient /= lightCount;
	//	diffuse /= lightCount;
	//}
    //vec3 result = (ambient + diffuse) * Albedo.xyz;
    FragColor = vec4(abs(Normal.rgb), 1.0);
}  
