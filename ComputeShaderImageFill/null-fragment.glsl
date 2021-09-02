#version 430 core

uniform sampler2D tex;

uniform float numSamples;

in vec2 texcoord;

out vec4 color;

void main(){
	color = texture(tex, texcoord) / numSamples;
}