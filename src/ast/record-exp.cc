/**
 ** \file ast/record-exp.cc
 ** \brief Implementation of ast::RecordExp.
 */

#include <ast/record-exp.hh>
#include <ast/visitor.hh>
#include <misc/algorithm.hh>

namespace ast
{
  RecordExp::RecordExp(const Location& location,
                       ast::NameTy* type_name,
                       ast::fieldinits_type* fields)
    : Exp(location)
    , type_name_(type_name)
    , fields_(fields)
  {}
  RecordExp::~RecordExp()
  {
    delete type_name_;
    delete fields_;
  }

  void RecordExp::accept(ConstVisitor& v) const { v(*this); };
  void RecordExp::accept(Visitor& v) { v(*this); }

} // namespace ast
