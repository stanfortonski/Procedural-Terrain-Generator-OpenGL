//Copyright (c) 2020 by Stan Fortoński
#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec4 clipSpace;
out vec3 fragPos;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 viewProject;

const float TILING = 2.0;

void main()
{
  vec4 pos = vec4(aPos, 1.0);
  fragPos = vec3(model * pos);
  clipSpace = viewProject * model * pos;
  texCoords = vec2(aTexCoords.x/2.0 + 0.5, aTexCoords.y/2.0 + 0.5) * TILING;
  gl_Position = clipSpace;
}
