#version 450

layout(binding = 0) uniform sampler2D Texture;
layout(binding = 1) uniform sampler2D Normal_map;
layout(binding = 2) uniform sampler2D Spec_map;

in vec3 frag_norm;
in vec2 frag_texcoord;
in vec3 frag_pos;
in vec3 frag_tan;
in vec3 frag_bitan;

uniform ivec3 Mode;
uniform float Degree;
uniform mat4 Projection;
uniform mat4 ModelView;

out vec4 outColor;

void main(){
	float Pi = 3.14159265358979323846f;

	float ambient_coefficient = 0.1, diffuse_coefficient = 1, specular_coefficient = 0.5;
	
	vec4 ambient_color = vec4(0.7,0.7,0.7,1.0);
	vec4 diffuse_color = vec4(0.35,0.3,0.15,1.0);
	vec4 specular_color=vec4(1.0,1.0,1.0,1.0);
	
	vec3 light_pos=vec3(ModelView*vec4(-3*sin((Degree+180)/180*Pi*9/10),-3*cos((Degree+180)/180*Pi*9/10),0.0,1.0));
	vec3 view_pos =vec3(ModelView*vec4(-3*sin((Degree+180)/180*Pi),-3*cos((Degree+180)/180*Pi),0.0,1.0));
	
	if(Mode[0]==1)
		diffuse_color = texture2D(Texture,frag_texcoord);

	//ambient
	vec4 ambient = ambient_coefficient * ambient_color;

	//diffuse
	vec3 norm = frag_norm;
	if(Mode[1]==1){
		norm = normalize(2*(texture2D(Normal_map,frag_texcoord).x - 0.5)*frag_tan + 2*(texture2D(Normal_map,frag_texcoord).y - 0.5)*frag_bitan + 2*(texture2D(Normal_map,frag_texcoord).z - 0.5)*frag_norm);
	}
	vec3 lightDir = normalize(light_pos - frag_pos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * diffuse_color;

	//specular
	vec3 viewDir = normalize(view_pos - frag_pos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec4 specular = specular_coefficient*spec*specular_color;
	if(Mode[2]==1)
		specular = specular * texture2D(Spec_map,frag_texcoord);

	outColor= (specular+diffuse+ambient);
}