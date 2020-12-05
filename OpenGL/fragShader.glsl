#version 430

in vec4 varyingColor;

out vec4 color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{ color = varyingColor;

}
