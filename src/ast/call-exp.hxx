/**
 ** \file ast/call-exp.hxx
 ** \brief Inline methods of ast::CallExp.
 */

#pragma once

#include <ast/call-exp.hh>

namespace ast
{
  inline const misc::symbol CallExp::name_get() const { return name_; }

  inline misc::symbol CallExp::name_get() { return name_; }

  inline const exps_type& CallExp::args_get() const { return *args_; }

  inline exps_type& CallExp::args_get() { return *args_; }

  inline const FunctionDec* CallExp::def_get() const { return def_; }

  inline void CallExp::def_set(FunctionDec* def) { def_ = def; }

  inline void CallExp::name_set(misc::symbol name) { name_ = name; }

  inline FunctionDec* CallExp::def_get() { return def_; }

} // namespace ast
