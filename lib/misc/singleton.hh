/**
 ** \file misc/singleton.hh
 ** \brief Generic singleton
 */

#pragma once

namespace misc
{
  template <typename T> class Singleton
  {
  protected:
    Singleton(){};
    ~Singleton(){};

  public:
    Singleton(Singleton& other) = delete;
    void operator=(const Singleton&) = delete;
    static T& instance()
    {
      static T instance;
      return instance;
    }
  };

} // namespace misc
