#version 430

layout (location=0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 lineColor;

void main(void) {
     gl_Position = projection * view * model * vec4(position, 1.0);
     lineColor = vec4(1.0, 0.0, 0.0, 1.0);
}