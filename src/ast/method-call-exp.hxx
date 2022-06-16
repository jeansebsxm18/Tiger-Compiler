/**
 ** \file ast/method-call-exp.hxx
 ** \brief Inline methods of ast::MethodCallExp.
 */

#pragma once

#include <ast/method-call-exp.hh>

namespace ast
{
  inline const ast::Var& MethodCallExp::get_object() const { return *object_; }
  inline ast::Var& MethodCallExp::get_object() { return *object_; }

} // namespace ast
