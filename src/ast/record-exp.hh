/**
 ** \file ast/record-exp.hh
 ** \brief Declaration of ast::RecordExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/field-init.hh>
#include <ast/name-ty.hh>

namespace ast
{
  /// RecordExp.
  class RecordExp : public Exp
  {
  public:
    RecordExp(const Location& location,
              ast::NameTy* type_name,
              ast::fieldinits_type* fields);
    RecordExp(const RecordExp&) = delete;
    RecordExp& operator=(const RecordExp&) = delete;

    ~RecordExp() override;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const ast::NameTy& get_type_name() const;
    ast::NameTy& get_type_name();
    const ast::fieldinits_type& get_fields() const;
    ast::fieldinits_type& get_fields();
    void def_set(TypeDec* def);
    const TypeDec* def_get() const;

  protected:
    ast::NameTy* type_name_;
    ast::fieldinits_type* fields_;
    TypeDec* def_;
  };
} // namespace ast
#include <ast/record-exp.hxx>
