//Copyright (c) 2020 by Stan Fortoński
//Based on: https://learnopengl.com/Advanced-Lighting/Bloom
#version 410 core
#define WEIGHT_AMOUNT 5

out vec4 fragColor;
in vec2 texCoords;

uniform sampler2D image;

uniform bool isHorizontal;
uniform float weight[WEIGHT_AMOUNT] = float[](0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{
  vec2 texOffset = 1.0 / textureSize(image, 0);
  vec3 result = texture(image, texCoords).rgb * weight[0];
  if (isHorizontal)
  {
    for (int i = 1; i < WEIGHT_AMOUNT; ++i)
    {
      result += texture(image, texCoords + vec2(texOffset.x * i, 0.0)).rgb * weight[i];
      result += texture(image, texCoords - vec2(texOffset.x * i, 0.0)).rgb * weight[i];
    }
  }
  else
  {
    for (int i = 1; i < WEIGHT_AMOUNT; ++i)
    {
      result += texture(image, texCoords + vec2(0.0, texOffset.y * i)).rgb * weight[i];
      result += texture(image, texCoords - vec2(0.0, texOffset.y * i)).rgb * weight[i];
    }
  }
  fragColor = vec4(result, 1.0);
}
