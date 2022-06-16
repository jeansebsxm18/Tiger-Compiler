/**
 ** \file ast/assign-exp.hh
 ** \brief Declaration of ast::AssignExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/var.hh>

namespace ast
{
  /// AssignExp.
  class AssignExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    AssignExp(const Location& location, Var* var, Exp* exp);
    AssignExp(const AssignExp&) = delete;
    AssignExp& operator=(const AssignExp&) = delete;

    ~AssignExp() override;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    const Var& var_get() const;

    Var& var_get();

    const Exp& exp_get() const;

    Exp& exp_get();
    /** \} */
  protected:
    Var* var_;
    Exp* exp_;
  };
} // namespace ast
#include <ast/assign-exp.hxx>
