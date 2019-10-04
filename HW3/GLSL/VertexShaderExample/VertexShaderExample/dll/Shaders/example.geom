#version 450

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;
 
in vec4 geom_color[3];
out vec4 frag_color;

void main()
{
	for(int i = 0; i < gl_in.length(); i++)
	{
		gl_Position = gl_in[i].gl_Position;
		frag_color = geom_color[i];
		EmitVertex();
	}
	EndPrimitive();
}