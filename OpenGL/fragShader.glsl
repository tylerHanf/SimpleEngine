#version 430

in vec4 varyingColor;
in vec3 Normal;

out vec4 color;
uniform mat4 mv_matrix;
uniform mat4 projection;

void main(void) {
     gl_FragColor = varyingColor;
}