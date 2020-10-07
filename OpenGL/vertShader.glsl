#version 430

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
//uniform mat4 mv_matrix;
uniform mat4 projection;
//uniform vec3 objColor;


out vec4 varyingColor;
out vec3 Normal;

void main(void) {
     float ambientStrength = 0.5;
     vec3 ambient = ambientStrength * vec3(1.0, 1.0, 0.5);
     vec3 result = ambient * position;
     gl_Position = projection * view * model * vec4(position, 1.0);
     //gl_Position = projection * mv_matrix * vec4(position, 1.0);
     varyingColor = vec4(result, 1.0);
     Normal = normal;
}