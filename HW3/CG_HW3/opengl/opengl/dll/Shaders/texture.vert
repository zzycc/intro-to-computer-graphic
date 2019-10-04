#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 nor;
layout(location = 2) in vec2 tex;

uniform mat4 Projection;
uniform mat4 ModelView;
uniform float Degree;
uniform ivec3 Mode;

out vec3 normal;
out vec3 position;
out vec2 texcoord;

void main() {
	//Use vertex shader to compute position
	gl_Position = Projection * ModelView * vec4(pos, 1.0);
	normal= (Projection * ModelView * vec4(nor,0.0)).xyz;
	texcoord=tex;
	position= vec3(ModelView * vec4(pos, 1.0));
}