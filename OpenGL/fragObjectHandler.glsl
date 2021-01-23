#version 430

out vec4 FragColor;

layout (location=0) in vec3 pos;
layout(location=1) in vec3 aNormal;

uniform vec3 objColor;

void main(void) {
     FragColor = vec4(objColor, 1.0);
}