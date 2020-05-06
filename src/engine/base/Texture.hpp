/* Copyright (c) 2020 by Stan Fortoński */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP 1
#include "../support/TextureLoader.hpp"

namespace Engine
{
  class Texture
  {
    unsigned id = 0;
    unsigned * amount;

    void init();
    void swap(const Texture & tex);
    void clear();

  public:
    Texture();
    Texture(const std::string & path, GLenum type);
    Texture(const std::vector<std::string> & paths);
    Texture(const Texture & tex);
    Texture & operator=(const Texture & tex);
    virtual ~Texture();

    void create();
    void remove();

    void bind(GLenum type) const;

    void load(const std::string & path, GLenum type);
    void load(const std::vector<std::string> & paths);

    unsigned getId() const{return id;}

    static void active(const unsigned & n = 0){glActiveTexture(GL_TEXTURE0 + n);}
    static void unbind(GLenum type){glBindTexture(type, 0);}

    bool isNotCreated() const{return id == 0;}
    bool isCreated() const{return id != 0;}
  };
}
#endif
