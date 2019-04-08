
#version 440 core
out vec4 FragColor;
  
in vec2 TexCoords_FS_in;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

void main()
{             
    // retrieve data from G-buffer
    vec3 FragPos = texture(gPosition, TexCoords_FS_in).rgb;
    vec3 Normal = texture(gNormal, TexCoords_FS_in).rgb;
    vec4 Albedo = texture(gAlbedo, TexCoords_FS_in).rgba;
    
    FragColor = Albedo;
}  
