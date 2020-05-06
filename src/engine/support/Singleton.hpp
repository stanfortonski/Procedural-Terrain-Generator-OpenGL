/* Copyright (c) 2020 by Stan Fortoński */

#ifndef SINGLETON_HPP
#define SINGLETON_HPP 1
#include <iostream>

namespace Engine
{
  template <typename T>
  class Singleton
  {
  protected:
    Singleton(){}
    virtual ~Singleton(){;}

  public:
    Singleton(const Singleton &) = delete;
    Singleton & operator=(const Singleton &) = delete;
    Singleton(Singleton &&) = delete;
    Singleton & operator=(Singleton &&) = delete;

    static T & get()
    {
      static T instance;
      return instance;
    };
  };
}
#endif
