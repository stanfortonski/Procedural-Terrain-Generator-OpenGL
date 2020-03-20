//Copyright (c) 2020 by Stan Fortoński
#version 410 core
#define FACES 6

layout (triangles) in;
layout(triangle_strip, max_vertices = 18) out;

out vec4 fragPos;

uniform mat4 shadowMatrices[FACES];

void main()
{
  for (gl_Layer = 0; gl_Layer < FACES; ++gl_Layer)
  {
    for (int i = 0; i < 3; ++i)
    {
      fragPos = gl_in[i].gl_Position;
      gl_Position = shadowMatrices[gl_Layer] * fragPos;
      EmitVertex();
    }
    EndPrimitive();
  }
}
