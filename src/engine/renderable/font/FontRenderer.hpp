/* Copyright (c) 2020 by Stan Fortoński */

#ifndef FONT_RENDERER_HPP
#define FONT_RENDERER_HPP 1
#include "../shape/Shape.hpp"
#include "../../support/Font.hpp"
#include "../../window/Window.hpp"

namespace Engine
{
  class FontRenderer: public Shape
  {
    Window & window;
    Font font;
    glm::vec3 color = glm::vec3(0.0f);
    float posX = 0;
    float posY = 0;
    float scale = 1;
    std::string text;

    glm::mat4 getProjectionMatrix() const{return glm::ortho(0.0f, (float)window.getWidth(), 0.0f, (float)window.getHeight());}

  public:
    FontRenderer(Window & win, const Font & f);

    virtual void render(Program & program);

    void setColor(const glm::vec3 & c){color = c;}
    glm::vec3 getColor() const{return color;}

    void setPosition(const float & x, const float & y){posX = x; posY = y;}
    glm::vec2 getPosition() const{return glm::vec2(posX, posY);}

    void setScale(const float & s){scale = s;}
    float getScale() const{return scale;}

    void setText(const std::string & textLine){text = textLine;}
    std::string getText() const{return text;}
  };
}
#endif
