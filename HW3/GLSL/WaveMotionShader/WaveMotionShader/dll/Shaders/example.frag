#version 450

in float height;

out vec4 outColor;

void main(){
	//Use fragment shader to change color
	if (height > 0.3){
		outColor = vec4(0.0, 0.0, 1.0, 1.0);
	}
	else if (height > -0.6){
		outColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
	else{
		outColor = vec4(0.0, 1.0, 0.0, 1.0);
	}
}