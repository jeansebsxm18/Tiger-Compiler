/**
 ** \file ast/object-exp.hh
 ** \brief Declaration of ast::ObjectExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// ObjectExp.
  class ObjectExp : public Exp
  {
  public:
    ObjectExp(const Location& location, NameTy* type_name);
    ObjectExp(const ObjectExp&) = delete;
    ObjectExp& operator=(const ObjectExp&) = delete;

    ~ObjectExp() override;

    void accept(ConstVisitor& v) const override;

    void accept(Visitor& v);

    const NameTy& type_name_get() const;
    NameTy& type_name_get();

    const TypeDec* def_get() const;
    void def_set(TypeDec* def);

  protected:
    NameTy* type_name_;
    TypeDec* def_ = nullptr;
  };
} // namespace ast
#include <ast/object-exp.hxx>
