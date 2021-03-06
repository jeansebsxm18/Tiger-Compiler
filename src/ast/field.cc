/**
 ** \file ast/field.cc
 ** \brief Implementation of ast::Field.
 */

#include <ast/field.hh>
#include <ast/visitor.hh>

namespace ast
{
  Field::Field(const Location& location, misc::symbol name, NameTy* type_name)
    : Ast(location)
    , name_(name)
    , type_name_(type_name)
  {}

  Field::~Field() { delete type_name_; }

  void Field::accept(ConstVisitor& v) const { v(*this); }

  void Field::accept(Visitor& v) { v(*this); }
} // namespace ast
