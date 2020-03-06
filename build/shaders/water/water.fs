//Copyright (c) 2020 by Stan Fortoński
//Based on https://www.youtube.com/watch?v=HusvGeEDU_U&list=PLRIWtICgwaX23jiqVByUs0bqhnalNTNZh
#version 410 core

layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 brightColor;

out vec4 fragColor;
in vec4 clipSpace;
in vec3 fragPos;
in vec2 texCoords;

const int SHINENESS = 256;
const float WATER_DEPTH_FACTOR = 2.0;
const vec4 WATER_COLOR = vec4(0.0, 0.15, 0.6, 1.0);
const float NORMAL_FACTOR = 2.5;
const vec3 BRIGHT_FACTOR = vec3(0.2126, 0.7152, 0.0722);
const int AMOUNT_OF_POINT_LIGHTS = 1;
const vec3 NORMAL = vec3(0.0, 1.0, 0.0);
const float WAVE_STR = 0.01;

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

uniform sampler2D reflectionTex;
uniform sampler2D refractionTex;
uniform sampler2D dudvMap;
uniform sampler2D depthMap;
uniform sampler2D normalMap;
uniform vec3 viewPos;
uniform float waterOffset;
uniform float farPlane;
uniform float nearPlane;
uniform int lightsAmount;
uniform PointLight lights[AMOUNT_OF_POINT_LIGHTS];

vec3 calcPointLight(PointLight light, vec3 material, vec3 viewDir, vec3 normal, float dimming);
vec3 calcFog(vec3 result);
float calcDistance(float depth);

void main()
{
  vec3 viewDir = normalize(viewPos - fragPos);
  vec4 material = vec4(0.0);

  vec2 NDC = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
  vec2 reflectCoords = vec2(NDC.x, -NDC.y);
  vec2 refractCoords = vec2(NDC.x, NDC.y);

  float distance1 = calcDistance(texture(depthMap, refractCoords).r);
  float distance2 = calcDistance(gl_FragCoord.z);
  float waterDepth = distance1 - distance2;
  float waterAlpha = clamp(waterDepth/WATER_DEPTH_FACTOR, 0.0, 1.0);
  float waterAlphaDistort = clamp(waterDepth/(WATER_DEPTH_FACTOR*2), 0.0, 1.0);

  vec2 distortTexCoords1 = vec2(texCoords.x + waterOffset/2, texCoords.y);
  vec2 distortTexCoords2 = vec2(-texCoords.x + waterOffset/2, texCoords.y + waterOffset);
  vec2 distort1 = (texture(dudvMap, distortTexCoords1).rg * 2.0 - 1.0) * WAVE_STR * waterAlphaDistort;
  vec2 distort2 = (texture(dudvMap, distortTexCoords2).rg * 2.0 - 1.0) * WAVE_STR * waterAlphaDistort;

  vec2 distorting = distort1 + distort2;
  reflectCoords += distorting;
  refractCoords += distorting;

  reflectCoords.x = clamp(reflectCoords.x, 0.001, 0.999);
  reflectCoords.y = clamp(reflectCoords.y, -0.999, -0.001);
  refractCoords = clamp(refractCoords, 0.001, 0.999);
  vec4 reflectColor = texture(reflectionTex, reflectCoords);
  vec4 refractColor = texture(refractionTex, refractCoords);

  vec4 normalColor1 = texture(normalMap, distortTexCoords1);
  vec4 normalColor2 = texture(normalMap, distortTexCoords2);
  vec4 normalMixColor = normalColor1 + normalColor2;
  vec3 normal = vec3(normalMixColor.r * 2.0 - 1.0, normalMixColor.b * NORMAL_FACTOR, normalMixColor.g * 2.0 - 1.0);
  normal = normalize(normal);

  float fresnel = dot(viewDir, normal);
  material = mix(reflectColor, refractColor, fresnel);
  material = mix(material, WATER_COLOR, 0.5);

  vec3 result = vec3(0.0, 0.0, 0.0);
  for (int i = 0; i < lightsAmount; ++i)
    result += calcPointLight(lights[i], material.rgb, viewDir, normal, waterAlpha);

  float brightness = dot(result.xyz, BRIGHT_FACTOR);
  if (brightness > 1.0)
    brightColor = vec4(result.xyz, 1.0);
  else brightColor = vec4(0.0, 0.0, 0.0, 1.0);
  fragColor = vec4(calcFog(result), waterAlpha);
}

vec3 calcPointLight(PointLight light, vec3 material, vec3 viewDir, vec3 normal, float dimming)
{
  vec3 fragToLightDir = -light.position;
  float distances = length(fragToLightDir);
  fragToLightDir = normalize(fragToLightDir);
  float weakening = 1.0 / (light.constant + light.linear * distances + light.quadratic * pow(distances, 2));


  float diff = max(dot(fragToLightDir, normal), 0.0);
  vec3 halfwayDir = normalize(fragToLightDir + viewDir);
  float specAngle = max(dot(halfwayDir, normal), 0.0);
  float spec = pow(specAngle, SHINENESS);

  vec3 ambient = light.ambient * material * weakening;
  vec3 diffuse = light.diffuse * diff * material * weakening;
  vec3 specular = light.specular * spec * weakening * dimming;
  return ambient + diffuse + specular;
}

vec3 calcFog(vec3 result)
{
  const vec3 fogColor = vec3(0.6, 0.7, 0.8);
  const float fogStart = 120;
  const float fogEnd = 200;
  float dist = length(viewPos - fragPos);
  float fogFactor = clamp(((fogEnd - dist)/(fogEnd - fogStart)), 0.125, 1.0);
  return mix(fogColor, result, fogFactor);
}

float calcDistance(float depth)
{
  return 2.0 * nearPlane * farPlane / (farPlane + nearPlane - (2.0 * depth - 1.0) * (farPlane - nearPlane));
}
