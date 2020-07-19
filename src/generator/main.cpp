/* Copyright (c) 2020 by Stan Fortoński */

#include <cstdlib>
#include <ctime>
#include "TerrainApp.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Window * window = nullptr;
TerrainApp * game = nullptr;

void loop();
void processInput(GLFWwindow *win);
void resizeEvent(GLFWwindow * frame, int w, int h);
void mouseEvent(GLFWwindow * frame, double posX, double posY);

int main()
{
  srand(time(0));
  try
  {
    window = new Window;
    window->create(true);
    window->setTitle("Terrain Generator by Stan Fortoński");
    game = new TerrainApp(*window);
    window->setRenderMethod(loop);
    window->setEventResize(resizeEvent);
    window->setEventInput(processInput);
    window->setEventMouseMove(mouseEvent);
    window->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    window->startRender();
    delete game;
    delete window;
  }
  catch (std::runtime_error & e)
  {
    std::cerr<<e.what()<<std::endl;
    std::cin.get();
  }
  return 0;
}

void loop()
{
  game->render();
}

void resizeEvent(GLFWwindow * win, int w, int h)
{
  game->resize(w, h);
}

void mouseEvent(GLFWwindow * win, double posX, double posY)
{
  game->mouseMove(posX, posY);
}

void processInput(GLFWwindow *win)
{
  game->keyboardInput(win);
}
