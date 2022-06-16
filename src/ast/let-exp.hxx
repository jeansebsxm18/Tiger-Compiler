/**
 ** \file ast/let-exp.hxx
 ** \brief Inline methods of ast::LetExp.
 */

#pragma once

#include <ast/let-exp.hh>

namespace ast
{
  inline const ChunkList& LetExp::chunklist_get() const { return *chunklist_; }

  inline ChunkList& LetExp::chunklist_get() { return *chunklist_; }

  inline const Exp& LetExp::exp_get() const { return *exp_; }

  inline Exp& LetExp::exp_get() { return *exp_; }
} // namespace ast
