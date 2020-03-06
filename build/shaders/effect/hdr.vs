//Copyright (c) 2020 by Stan Fortoński
#version 410 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 texCoords;

uniform mat4 model;

void main()
{
  gl_Position = model * vec4(aPos, 0.0, 1.0);
  texCoords = aTexCoords;
}
