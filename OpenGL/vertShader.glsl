#version 430

layout (location=0) in vec3 pos;
layout (location=1) in vec3 aNormal;
layout (location=2) in vec2 texCoord;

out vec2 tc;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (binding=0) uniform sampler2D samp;

void main(void)
{
  gl_Position = projection * view * model * vec4(pos, 1.0);
  tc = texCoord;
}
