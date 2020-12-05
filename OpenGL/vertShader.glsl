#version 430

layout (location=0) in vec3 pos;
layout (location=0) in vec3 aNormal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 varyingColor;

void main(void)
{ gl_Position = projection * view * model * vec4(pos, 1.0);
  varyingColor = vec4(pos, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}
