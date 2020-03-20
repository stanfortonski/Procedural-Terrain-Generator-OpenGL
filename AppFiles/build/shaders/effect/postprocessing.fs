//Copyright (c) 2020 by Stan Fortoński
#version 410 core

out vec4 fragColor;
in vec2 texCoords;

uniform sampler2D screenTexture0;

void main()
{
  fragColor = texture(screenTexture0, texCoords);
}
