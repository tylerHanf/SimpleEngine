#version 430

in vec4 lineColor;
out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 projection;

void main(void) {
     color = lineColor;
}