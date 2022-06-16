/**
 ** \file ast/let-exp.hh
 ** \brief Declaration of ast::LetExp.
 */

#pragma once

#include <ast/chunk-list.hh>
#include <ast/exp.hh>
#include <misc/contract.hh>

namespace ast
{
  /// LetExp.
  class LetExp : public Exp
  {
  public:
    LetExp(const Location& location, ChunkList* chunklist, Exp* exp);
    LetExp(const LetExp&) = delete;
    LetExp& operator=(const LetExp&) = delete;

    ~LetExp() override;

    void accept(ConstVisitor& v) const override;

    void accept(Visitor& v) override;

    const ChunkList& chunklist_get() const;

    ChunkList& chunklist_get();

    const Exp& exp_get() const;

    Exp& exp_get();

  protected:
    ChunkList* chunklist_;

    Exp* exp_;
  };
} // namespace ast
#include <ast/let-exp.hxx>
