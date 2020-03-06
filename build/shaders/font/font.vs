//Copyright (c) 2020 by Stan Fortoński
#version 410 core

layout (location = 0) in vec4 vertex;

out vec2 texCoords;

uniform mat4 projection;

void main()
{
  gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
  texCoords = vertex.zw;
}
