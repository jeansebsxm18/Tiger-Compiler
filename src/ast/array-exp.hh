/**
 ** \file ast/array-exp.hh
 ** \brief Declaration of ast::ArrayExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ArrayExp.
  class ArrayExp : public Exp
  {
  public:
    /** \name Ctor & dtor.
     ** \{ */
    ArrayExp(const Location& location, NameTy* type_name, Exp* size, Exp* init);
    ArrayExp(const ArrayExp&) = delete;
    ArrayExp& operator=(const ArrayExp&) = delete;

    ~ArrayExp() override;
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
    const NameTy& type_name_get() const;

    NameTy& type_name_get();

    const Exp& size_get() const;

    Exp& size_get();

    const Exp& init_get() const;

    Exp& init_get();
    /** \} */

  protected:
    NameTy* type_name_;
    Exp* size_;
    Exp* init_;
  };
} // namespace ast
#include <ast/array-exp.hxx>
