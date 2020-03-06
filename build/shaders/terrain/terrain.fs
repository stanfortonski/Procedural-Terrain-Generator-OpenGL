//Copyright (c) 2020 by Stan Fortoński
#version 410 core

layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 brightColor;

in vec2 texCoords;
in vec3 fragPos;

const int SHINENESS = 32;
const vec3 BRIGHT_FACTOR = vec3(0.2126, 0.7152, 0.0722);
const int AMOUNT_OF_POINT_LIGHTS = 1;
const int DISCS_PCF_AMOUNT = 20;
const vec3 DISCS_PCF[DISCS_PCF_AMOUNT] = vec3[](
   vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1),
   vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
   vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1),
   vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1)
);

struct PointLight
{
  vec3 position;
  float constant;
  float linear;
  float quadratic;
  vec3 diffuse;
  vec3 ambient;
  vec3 specular;
};

uniform sampler2D grassTex;
uniform sampler2D stoneTex;
uniform sampler2D normalMap;
uniform sampler2D heightMap;
uniform vec3 viewPos;
uniform float farPlane;
uniform int lightsAmount;
uniform PointLight lights[AMOUNT_OF_POINT_LIGHTS];
uniform samplerCube shadowMaps[AMOUNT_OF_POINT_LIGHTS];
uniform int allowShadows;

float shadowCalculation(samplerCube shadowMap, vec3 lightPos);
vec3 calcPointLight(PointLight light, vec3 material, vec3 viewDir, vec3 normal, float shadow);
vec3 blendColor(vec3 rgbA, vec3 rgbB, vec3 rgbC, float alpha);
vec3 calcFog(vec3 material);

void main()
{
  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 normalColor = texture(normalMap, texCoords).rgb;
  vec3 normal = vec3(normalColor.r * 2.0 - 1.0, normalColor.b, normalColor.g * 2.0 - 1.0);
  normal = normalize(normal);

  vec3 height = texture(heightMap, texCoords).rgb;

  vec3 grass1 = texture(grassTex, texCoords * 10 + 5).rgb;
  vec3 grass2 = texture(grassTex, texCoords * 15 + 20).rgb;
  vec3 grass3 = texture(grassTex, texCoords * 20 + 30).rgb;
  vec3 grass = blendColor(grass1, grass2, grass3, 0.33);

  vec3 stone1 = texture(stoneTex, texCoords * 10 + 5).rgb;
  vec3 stone2 = texture(stoneTex, texCoords * 15 + 20).rgb;
  vec3 stone3 = texture(stoneTex, texCoords * 20 + 30).rgb;
  vec3 stone = blendColor(stone1, stone2, stone3, 0.33) * vec3(2.0, 2.0, 2.0);

  vec3 material = mix(stone, grass, pow(normal.y, 5));
  material = mix(grass, material, min(fragPos.y / 0.7, 1));

  vec3 result = vec3(0.0, 0.0, 0.0);
  for (int i = 0; i < lightsAmount; ++i)
  {
    float pointShadow = 0.0;
    if (allowShadows == 1)
      pointShadow = shadowCalculation(shadowMaps[i], lights[i].position);
    result += calcPointLight(lights[i], material, viewDir, normal, pointShadow);
  }

  float brightness = dot(result, BRIGHT_FACTOR);
  if (brightness > 1.0)
    brightColor = vec4(result, 1.0);
  else brightColor = vec4(0.0, 0.0, 0.0, 1.0);

  result = calcFog(result);
  fragColor = vec4(result, 1.0);
}

float shadowCalculation(samplerCube shadowMap, vec3 lightPos)
{
  const float bias = 0.25;

  vec3 LightToFragDir = fragPos - lightPos;
  float currentDepth = length(LightToFragDir) - bias;
  float viewDistance = length(viewPos - fragPos);
  float diskRadius = clamp(viewDistance / farPlane, 0.005, 0.02);

  float shadow = 0.0;
  for (int i = 0; i < DISCS_PCF_AMOUNT; ++i)
  {
    float closestDepth = texture(shadowMap, LightToFragDir + DISCS_PCF[i] * diskRadius).r;
    closestDepth *= farPlane;
    if (currentDepth > closestDepth)
      shadow += 1.0;
  }
  shadow /= float(DISCS_PCF_AMOUNT);
  return shadow;
}

vec3 calcPointLight(PointLight light, vec3 material, vec3 viewDir, vec3 normal, float shadow)
{
  vec3 fragToLightDir = fragPos - light.position;
  float distances = length(fragToLightDir);
  fragToLightDir = normalize(fragToLightDir);
  float weakening = 1.0 / (light.constant + light.linear * distances + light.quadratic * pow(distances, 2));

  float diff = max(dot(fragToLightDir, normal), 0.0);
  vec3 halfwayDir = normalize(fragToLightDir + viewDir);
  float specAngle = max(dot(halfwayDir, normal), 0.0);
  float spec = pow(specAngle, SHINENESS);

  vec3 ambient = light.ambient * material * weakening;
  vec3 diffuse = light.diffuse * diff * weakening;
  vec3 specular = light.specular * spec * weakening;
  return (ambient + (1.0 - shadow) * (diffuse + specular)) * (material);
}

vec3 blendColor(vec3 rgbA, vec3 rgbB, vec3 rgbC, float alpha)
{
	return (rgbA * alpha) + (rgbB * alpha) + (rgbC * alpha);
}

vec3 calcFog(vec3 material)
{
  const vec3 fogColor = vec3(0.6, 0.7, 0.8);
  const float fogStart = 120;
  const float fogEnd = 200;
  float dist = length(viewPos - fragPos);
  float fogFactor = clamp(((fogEnd - dist)/(fogEnd - fogStart)), 0.125, 1.0);
  return mix(fogColor, material, fogFactor);
}
