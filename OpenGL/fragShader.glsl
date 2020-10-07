#version 430

in vec4 varyingColor;
in vec3 Normal;

out vec4 color;
//uniform mat4 model;
//uniform mat4 view;
uniform mat4 mv_matrix;
uniform mat4 projection;
//uniform vec3 objColor;

void main(void) {
     color = varyingColor;
}