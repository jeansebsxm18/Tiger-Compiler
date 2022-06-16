/**
 ** \file type/builtin-types.hh
 ** \brief The classes Int, String, Void.
 */
#pragma once

#include <misc/singleton.hh>
#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{
  class Int : public misc::Singleton<Int>, public Type
  {
    friend class misc::Singleton<Int>;
    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;
  };

  class String : public misc::Singleton<String>, public Type
  {
    friend class misc::Singleton<String>;
    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;
  };

  class Void : public misc::Singleton<Void>, public Type
  {
    friend class misc::Singleton<Void>;
    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;
  };
} // namespace type
