//Copyright (c) 2020 by Stan Fortoński
#version 410 core

out vec4 fragColor;
in vec3 texCoords;

uniform samplerCube skybox;

void main()
{
  fragColor = texture(skybox, texCoords);
}
