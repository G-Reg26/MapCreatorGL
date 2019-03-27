#version 330

in vec2 texCoord0;

uniform sampler2D diffuse;

void main(){
	gl_FragColor = texture(diffuse, texCoord0);
}