/**
 ** \file ast/record-ty.hxx
 ** \brief Inline methods of ast::RecordTy.
 */

#pragma once

#include <ast/record-ty.hh>

namespace ast
{
  inline const fields_type& RecordTy::field_get() const { return *field_; }
  inline fields_type& RecordTy::field_get() { return *field_; }
} // namespace ast
