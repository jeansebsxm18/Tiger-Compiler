/**
 ** \file ast/if-exp.hxx
 ** \brief Inline methods of ast::IfExp.
 */

#pragma once

#include <ast/if-exp.hh>

namespace ast
{
  inline const Exp& IfExp::get_test() const { return *test_; }
  inline Exp& IfExp::get_test() { return *test_; }
  inline const Exp& IfExp::get_thenclause() const { return *thenclause_; }
  inline Exp& IfExp::get_thenclause() { return *thenclause_; }
  inline const Exp& IfExp::get_elseclause() const { return *elseclause_; }
  inline Exp& IfExp::get_elseclause() { return *elseclause_; }
} // namespace ast
