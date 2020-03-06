//Copyright (c) 2020 by Stan Fortoński
//Based on: OpenGL 4 ShadingLanguage Cookbook Second Edition David Wolff
#version 410 core

layout (vertices = 4) out;

in vec2 tc[];
out vec2 tc_out[];

uniform int maxTessLevel;
uniform mat4 viewProject;
uniform mat4 model;

float calcTessLevel()
{
  const int minLevel = 4;
  const float minDepth = 0.001;
  const float maxDepth = 30.0;

  vec4 p = viewProject * model * gl_in[gl_InvocationID].gl_Position;

  float depth = clamp((abs(p.z) - minDepth)/(maxDepth - minDepth), 0.0, 1.0);
  float tl = mix(maxTessLevel, minLevel, depth);
  return tl;
}

void main()
{
  float tessLevel = calcTessLevel();
  gl_TessLevelOuter[0] = tessLevel;
  gl_TessLevelOuter[1] = tessLevel;
  gl_TessLevelOuter[2] = tessLevel;
  gl_TessLevelOuter[3] = tessLevel;
  gl_TessLevelInner[0] = tessLevel;
  gl_TessLevelInner[1] = tessLevel;
  tc_out[gl_InvocationID] = tc[gl_InvocationID];
  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
  gl_out[gl_InvocationID].gl_ClipDistance[0] = gl_in[gl_InvocationID].gl_ClipDistance[0];
}
