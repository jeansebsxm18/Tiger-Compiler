/**
 ** \file ast/record-ty.hh
 ** \brief Declaration of ast::RecordTy.
 */

#pragma once

#include <ast/field.hh>
#include <ast/ty.hh>

namespace ast
{
  /// RecordTy.
  class RecordTy : public Ty
  {
  public:
    RecordTy(const Location& location, fields_type* field);
    RecordTy(const RecordTy&) = delete;
    RecordTy& operator=(const RecordTy&) = delete;

    ~RecordTy() override;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const fields_type& field_get() const;
    fields_type& field_get();

  protected:
    fields_type* field_;
  };
} // namespace ast
#include <ast/record-ty.hxx>
