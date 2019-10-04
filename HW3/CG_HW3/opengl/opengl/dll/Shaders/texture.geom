#version 450

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in vec3 normal[3];
in vec2 texcoord[3]; 
in vec3 position[3];

out vec3 frag_norm;
out vec2 frag_texcoord;
out vec3 frag_pos;
out vec3 frag_tan;
out vec3 frag_bitan;

void main()
{
	vec3 edge1 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 edge2 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec2 deltaUV1 = texcoord[1] - texcoord[0];
	vec2 deltaUV2 = texcoord[2] - texcoord[0];
	float coefficient = 1/(deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	for(int i=0;i<gl_in.length();i++){
		gl_Position = gl_in[i].gl_Position;
		frag_norm = normalize(normal[i]);
		frag_texcoord = texcoord[i];
		frag_pos = position[i]; 
		frag_tan.x = coefficient * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		frag_tan.y = coefficient * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		frag_tan.z = coefficient * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		frag_tan = normalize(frag_tan);
		frag_bitan.x = coefficient * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		frag_bitan.y = coefficient * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		frag_bitan.z = coefficient * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		frag_bitan = normalize(frag_bitan);
		EmitVertex();
	}
	EndPrimitive();
}