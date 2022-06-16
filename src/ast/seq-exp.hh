/**
 ** \file ast/seq-exp.hh
 ** \brief Declaration of ast::SeqExp.
 */

#pragma once

#include <ast/exp.hh>

namespace ast
{
  /// SeqExp.
  class SeqExp : public Exp
  {
  public:
    SeqExp(const Location& location, ast::exps_type* exps);
    SeqExp(const SeqExp&) = delete;
    SeqExp& operator=(const SeqExp) = delete;

    ~SeqExp() override;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const exps_type& exps_get() const;
    exps_type& exps_get();

  protected:
    exps_type* exps_;
  };
} // namespace ast
#include <ast/seq-exp.hxx>
