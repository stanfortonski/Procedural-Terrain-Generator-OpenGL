/* Copyright (c) 2020 by Stan Fortoński */

#ifndef PARTICLES_HPP
#define PARTICLES_HPP 1
#include <algorithm>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Engine.hpp"
#include "../Window/window.hpp"
#include "../renderable/Transformationable.hpp"
#include "../camera/InterfaceCamera.hpp"

namespace Engine
{
  class StandardParticle
  {
  public:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec4 color = glm::vec4(1.0);
  };

  template <typename T, typename P>
  class ParticlesGenerator: public Transformationable
  {
    InterfaceCamera * camera;
    Program & particleProgram;
    std::vector<T> particles;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec4> colors;
    unsigned VBOparticlesPos;
    unsigned VBOparticlesColor;
    unsigned amount;
    P particleModel;

    void respawnParticles();
    void generateBuffers();
    void updateBuffers();

  protected:
    virtual void respawnParticle(T & particle) = 0;
    virtual bool updateParticle(T & particle, const float & deltaTime) = 0;

  public:
    ParticlesGenerator(InterfaceCamera * cam, Program & program, const unsigned & particlesAmount);
    virtual ~ParticlesGenerator(){;}

    void update();
    void render();
    virtual void render(Program & program);

    virtual unsigned getVAO() const{return particleModel.getVAO();}
  };

  template <typename T, typename P>
  ParticlesGenerator<T, P>::ParticlesGenerator(InterfaceCamera * cam, Program & program, const unsigned & particlesAmount): camera(cam), particleProgram(program)
  {
    colors.resize(particlesAmount);
    positions.resize(particlesAmount);
    particles.resize(particlesAmount);
    std::fill(particles.begin(), particles.end(), T());
    generateBuffers();
  }

  template <typename T, typename P>
  void ParticlesGenerator<T, P>::render()
  {
    glDisable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    particleProgram.use();
    particleProgram.setMat4("viewProject", camera->getViewProjectionMatrix());
    particleProgram.setMat4("model", getTransformMatrix());
    particleModel.render(particleProgram, amount);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
  }

  template <typename T, typename P>
  void ParticlesGenerator<T, P>::render(Program & program)
  {
    update();
    render();
    program.use();
  }

  template <typename T, typename P>
  void ParticlesGenerator<T, P>::update()
  {
    amount = 0;
    for (unsigned i = 0; i < particles.size(); ++i)
      respawnParticle(particles[i]);

    float dt = Engine::get().getDeltaTime();
    for (unsigned i = 0; i < particles.size(); ++i)
    {
      T & p = particles[i];
      if (updateParticle(p, dt))
      {
        positions[i] = p.position;
        colors[i] = p.color;
        ++amount;
      }
    }
    updateBuffers();
  }

  template <typename T, typename P>
  void ParticlesGenerator<T, P>::generateBuffers()
  {
    glBindVertexArray(getVAO());
    glGenBuffers(1, &VBOparticlesPos);
    glBindBuffer(GL_ARRAY_BUFFER, VBOparticlesPos);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(glm::vec3), 0, GL_STREAM_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &VBOparticlesColor);
    glBindBuffer(GL_ARRAY_BUFFER, VBOparticlesColor);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(glm::vec4), 0, GL_STREAM_DRAW);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glVertexAttribDivisor(0, 0);
    glVertexAttribDivisor(1, 0);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);

    glBindVertexArray(0);
  }

  template <typename T, typename P>
  void ParticlesGenerator<T, P>::updateBuffers()
  {
    glBindVertexArray(getVAO());
    glBindBuffer(GL_ARRAY_BUFFER, VBOparticlesPos);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(glm::vec3), 0, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, amount * sizeof(glm::vec3), &positions[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOparticlesColor);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(glm::vec4), 0, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, amount * sizeof(glm::vec4), &colors[0]);
    glBindVertexArray(0);
  }
}
#endif
