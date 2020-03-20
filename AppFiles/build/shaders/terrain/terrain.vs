//Copyright (c) 2020 by Stan Fortoński
#version 410 core

out vec2 tc;

void main()
{
  vec2 patchTexCoords[] = vec2[](vec2(0.0, 0.0), vec2(1.0, 0.0), vec2(0.0, 1.0), vec2(1.0, 1.0));

  int x = gl_InstanceID % 64;
  int y = gl_InstanceID / 64;
  tc = vec2((x + patchTexCoords[gl_VertexID].x) / 64.0, (64 - y + patchTexCoords[gl_VertexID].y) / 64.0);

  gl_ClipDistance[0] = 0;
  gl_Position = vec4(tc.x - 0.5, 0.0, (1.0 - tc.y) - 0.5, 1.0);
}
