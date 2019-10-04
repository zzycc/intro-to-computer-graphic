#version 450

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

out vec4 geom_color;

uniform mat4 Projection;
uniform mat4 ModelView;

void main() {
	gl_Position = Projection * ModelView * vec4(pos, 1.0);
	geom_color = vec4(color, 1.0);
}