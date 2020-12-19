#version 430

in vec2 tc;

out vec4 color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
layout (binding=0) uniform sampler2D samp;

void main(void)
{
	color = texture(samp, tc);
}
