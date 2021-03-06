#version 430

layout (location=0) in vec3 pos;
layout(location=1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 objColor;

void main(void) {
     gl_Position = projection * view * model * vec4(pos, 1.0);
}