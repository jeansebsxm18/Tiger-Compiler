/**
 ** \file ast/if-exp.cc
 ** \brief Implementation of ast::IfExp.
 */

#include <ast/if-exp.hh>
#include <ast/visitor.hh>

namespace ast
{
  IfExp::IfExp(const Location& location,
               Exp* test,
               Exp* thenclause,
               Exp* elseclause)
    : Exp(location)
    , test_(test)
    , thenclause_(thenclause)
    , elseclause_(elseclause)
  {}
  IfExp::IfExp(const Location& location, Exp* test, Exp* thenclause)
    : Exp(location)
    , test_(test)
    , thenclause_(thenclause)
    , elseclause_(nullptr)
  {}
  IfExp::~IfExp()
  {
    delete test_;
    delete thenclause_;
    if (elseclause_ != nullptr)
      delete elseclause_;
  }

  void IfExp::accept(ConstVisitor& v) const { v(*this); }
  void IfExp::accept(Visitor& v) { v(*this); }

} // namespace ast
