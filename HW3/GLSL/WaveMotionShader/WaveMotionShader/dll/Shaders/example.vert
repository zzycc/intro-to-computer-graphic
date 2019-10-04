#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in float index;

uniform mat4 Projection;
uniform mat4 ModelView;
uniform int Time;

void main() {
	//Use vertex shader to compute position
	float pi = 3.14159265359;
	vec3 wave_pos = pos;
	wave_pos.y = 5 * sin(2 * pi * (Time + index * 5) / 100);
	gl_Position = Projection * ModelView * vec4(wave_pos, 1.0);
}