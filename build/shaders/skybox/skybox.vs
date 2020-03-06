//Copyright (c) 2020 by Stan Fortoński
#version 410 core

layout (location = 0) in vec3 aPos;

out vec3 texCoords;

uniform mat4 viewProject;

void main()
{
  texCoords = aPos;
  vec4 pos =  viewProject * vec4(aPos, 1.0);
  gl_Position = pos.xyww;
}
