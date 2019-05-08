#version 440 core

layout (location = 0) in vec3 Position_VS_in;
layout (location = 1) in vec3 Normal_VS_in;
layout (location = 2) in vec3 Tangent_VS_in;
layout (location = 3) in vec2 TextureCoordinates_VS_in;

out vec2 TextureCoordinates_FS_in;
out vec3 Normal_FS_in;
out vec3 WorldPos_FS_in;

uniform mat4 Model = mat4(1.0);
uniform mat4 ViewProjection = mat4(1.0);

void main()
{
    TextureCoordinates_FS_in = TextureCoordinates_VS_in;
    WorldPos_FS_in = (Model * vec4(Position_VS_in, 1.0)).xyz;
	Normal_FS_in = normalize(mat3(transpose(inverse(Model))) * Normal_VS_in);
    gl_Position = ViewProjection * vec4(WorldPos_FS_in, 1.0);
}
