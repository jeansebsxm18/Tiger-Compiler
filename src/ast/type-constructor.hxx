/**
 ** \file ast/type-constructor.hxx
 ** \brief Inline methods of ast::TypeConstructor.
 */

#pragma once

#include <ast/type-constructor.hh>
#include <type/types.hh>

namespace ast
{
  inline void TypeConstructor::create_type_set(const type::Type* type)
  {
    type_ = type;
  }

  inline const type::Type* TypeConstructor::created_type_get() const
  {
    return type_;
  }
} // namespace ast
