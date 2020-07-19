//Copyright (c) 2020 by Stan Fortoński
//Based on: https://learnopengl.com/Advanced-Lighting/Bloom
#version 410 core

out vec4 fragColor;
in vec2 texCoords;

uniform sampler2D screenTexture0;
uniform sampler2D screenTexture1;

void main()
{
  const float gamma = 1.5;
  const float exposure = 0.6;

  vec3 sceneTex = texture(screenTexture0, texCoords).rgb;
  vec3 lightSceneTex = texture(screenTexture1, texCoords).rgb;
  vec3 hdrColor = sceneTex + lightSceneTex;

  vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
  result = pow(result, vec3(1.0 / gamma));

  fragColor = vec4(result, 1.0);
}
