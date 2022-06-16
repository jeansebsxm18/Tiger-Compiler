/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{
  /// IfExp.
  class IfExp : public Exp
  {
  public:
    IfExp(const Location& location,
          Exp* test,
          Exp* thenclause,
          Exp* elseclause);
    IfExp(const Location& location, Exp* test, Exp* thenclause);
    IfExp(const IfExp&) = delete;
    IfExp& operator=(const IntExp&) = delete;

    ~IfExp() override;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const Exp& get_test() const;
    Exp& get_test();
    const Exp& get_thenclause() const;
    Exp& get_thenclause();
    const Exp& get_elseclause() const;
    Exp& get_elseclause();

    // FIXME: Some code was deleted here.
  protected:
    Exp* test_;
    Exp* thenclause_;
    Exp* elseclause_;
  };
} // namespace ast
#include <ast/if-exp.hxx>
