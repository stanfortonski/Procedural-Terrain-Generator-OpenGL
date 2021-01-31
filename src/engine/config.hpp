/* Copyright (c) 2020 - 2021 by Stan Fortoński */

#ifndef CONFIG_HPP
#define CONFIG_HPP 1
#define DEBUG_ENGINE 0
#include "support/Singleton.hpp"
#include "json.hpp"
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using json = nlohmann::json;

namespace Engine
{
  class Config: public Singleton<Config>
  {
    friend class Singleton<Config>;

    std::string title = "Terrain Generator";
    unsigned majorVersion = 4;
    unsigned minorVersion = 1;
    unsigned windowWidth = 1920;
    unsigned windowHeight = 1080;
    unsigned shadowSize = 2048;
    unsigned samples = 8;
    float cameraPitch = 0;
    float cameraYaw = -90;
    float cameraSpeed = 7;
    float cameraSensitivity = 0.1;
    float cameraFov = 45;
    float cameraFar = 1000;
    float cameraNear = 0.05;
    float shadowFar = 500;
    float anisotropy = 8;
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 gravity = glm::vec3(0.0f, -9.81f, 0.0f);

    Config(){
        std::ifstream i("config.json");
        json json;
        i >> json;
        i.close();

        windowWidth = json["windowWidth"];
        windowHeight = json["windowHeight"];
        shadowSize = json["shadowSize"];
        samples = json["samples"];
        cameraPitch = json["cameraPitch"];
        cameraYaw = json["cameraYaw"];
        cameraSpeed =json["cameraSpeed"];
        cameraSensitivity = json["cameraSensitivity"];
        cameraFov = json["cameraFov"];
        cameraFar = json["cameraFar"];
        cameraNear = json["cameraNear"];
        shadowFar = json["shadowFar"];
        anisotropy = json["anisotropy"];
    }

  public:
    std::string getTitle() const{return title;}
    unsigned getWindowWidth() const{return windowWidth;}
    unsigned getWindowHeight() const{return windowHeight;}
    unsigned getMajorVersion() const{return majorVersion;}
    unsigned getMinorVersion() const{return minorVersion;}
    unsigned getShadowSize() const{return shadowSize;}
    unsigned getSamples() const{return samples;}
    float getCameraPitch() const{return cameraPitch;}
    float getCameraYaw() const{return cameraYaw;}
    float getCameraSpeed() const{return cameraSpeed;}
    float getCameraSensitivity() const{return cameraSensitivity;}
    float getCameraFov() const{return cameraFov;}
    float getCameraFar() const{return cameraFar;}
    float getCameraNear() const{return cameraNear;}
    glm::vec3 getCameraPosition() const{return cameraPosition;}
    glm::vec3 getCameraDirection() const{return cameraDirection;}
    float getShadowFar() const{return shadowFar;}
    float getAnisotropy() const{return anisotropy;}
    glm::vec3 getGravity() const{return gravity;}
  };
}
#endif
