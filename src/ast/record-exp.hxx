/**
 ** \file ast/record-exp.hxx
 ** \brief Inline methods of ast::RecordExp.
 */

#pragma once

#include <ast/record-exp.hh>

namespace ast
{
  inline const ast::NameTy& RecordExp::get_type_name() const
  {
    return *type_name_;
  }
  inline ast::NameTy& RecordExp::get_type_name() { return *type_name_; }
  inline const ast::fieldinits_type& RecordExp::get_fields() const
  {
    return *fields_;
  }
  inline ast::fieldinits_type& RecordExp::get_fields() { return *fields_; }

  inline const ast::TypeDec* RecordExp::def_get() const { return def_; }

  inline void RecordExp::def_set(TypeDec* def) { def_ = def; }
} // namespace ast
