#version 440 core

layout(triangles, equal_spacing, ccw) in;

uniform mat4 ViewProjection = mat4(1.0);

in vec3 WorldPos_TES_in[];

vec3 Interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
   	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main()
{
   	gl_Position = ViewProjection * vec4(Interpolate3D(WorldPos_TES_in[0], WorldPos_TES_in[1], WorldPos_TES_in[2]), 1.0);
}
