/**
 ** \file ast/escapable.hh
 ** \brief Declaration of ast::Escapable.
 */

#pragma once

#include <ast/fwd.hh>

namespace ast
{
  /// Escapable.
  class Escapable
  {
  public:
    bool escapable_get() const;
    void escapable_set(bool escapable);

  protected:
    bool escapable_ = true;
  };
} // namespace ast
#include <ast/escapable.hxx>
