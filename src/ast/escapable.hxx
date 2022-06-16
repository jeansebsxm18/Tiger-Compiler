/**
 ** \file ast/escapable.hxx
 ** \brief Inline methods of ast::Escapable.
 */

#pragma once

#include <ast/escapable.hh>

namespace ast
{
  inline bool Escapable::escapable_get() const { return escapable_; }

  inline void Escapable::escapable_set(bool escapable)
  {
    escapable_ = escapable;
  }
} // namespace ast
