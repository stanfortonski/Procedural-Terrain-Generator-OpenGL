//Copyright (c) 2020 by Stan Fortoński
#version 410 core

in vec4 fragPos;

uniform vec3 lightPos;
uniform float farPlane;

void main()
{
  float lightDistance = length(fragPos.xyz - lightPos);
  lightDistance /= farPlane;
  gl_FragDepth = lightDistance;
}
