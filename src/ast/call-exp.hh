/**
 ** \file ast/call-exp.hh
 ** \brief Declaration of ast::CallExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/function-dec.hh>
#include <misc/symbol.hh>

namespace ast
{
  /// CallExp.
  class CallExp : public Exp
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    CallExp(const Location& location, misc::symbol name, exps_type* args);
    CallExp(const CallExp&) = delete;
    CallExp& operator=(const CallExp&) = delete;

    ~CallExp() override;
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
    const misc::symbol name_get() const;

    misc::symbol name_get();

    const exps_type& args_get() const;

    exps_type& args_get();
    /** \} */

    const FunctionDec* def_get() const;
    FunctionDec* def_get();
    void def_set(FunctionDec* def);

    void name_set(misc::symbol name);

  protected:
    misc::symbol name_;
    exps_type* args_;
    FunctionDec* def_ = nullptr;
  };
} // namespace ast
#include <ast/call-exp.hxx>
