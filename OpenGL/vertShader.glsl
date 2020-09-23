#version 430

layout (location=0) in vec3 position;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

out vec4 varyingColor;

void main(void) {
     float ambientStrength = 0.5;
     vec3 ambient = ambientStrength * vec3(1.0, 1.0, 0.5);
     vec3 result = ambient * position;
     gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);
     // varyingColor = vec4(0.5, 0.5, 0.5, 1.0);
     //varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
     varyingColor = vec4(result, 1.0);
}