#version 450

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

uniform mat4 Projection;
uniform mat4 ModelView;

out float height;

void main()
{
	//Use geometry to make a plane
	gl_Position = gl_in[0].gl_Position;
	float width = 0.01;
	vec3 mid = gl_in[0].gl_Position.xyz / gl_in[0].gl_Position.w;
	vec3 up = width * (Projection * ModelView * vec4(0.0, 1.0, 0.0, 0.0)).xyz;
	vec3 right = width * (Projection * ModelView * vec4(1.0, 0.0, 0.0, 0.0)).xyz;
	height = mid.y;
	gl_Position = vec4(mid - right - up, 1.0); EmitVertex();
	gl_Position = vec4(mid + right - up, 1.0); EmitVertex();
	gl_Position = vec4(mid - right + up, 1.0); EmitVertex();
	gl_Position = vec4(mid + right + up, 1.0); EmitVertex();
	EndPrimitive();
}