/**
 ** \file escapes/escapes-visitor.cc
 ** \brief Implementation for escapes/escapes-visitor.hh.
 */

#include <ast/all.hh>
#include <escapes/escapes-visitor.hh>
#include <misc/contract.hh>

namespace escapes
{
  void EscapesVisitor::operator()(ast::LetExp& e)
  {
    scope++;
    escape.scope_begin();
    e.chunklist_get().accept(*this);
    e.exp_get().accept(*this);
    escape.scope_end();
    scope--;
  }
  void EscapesVisitor::operator()(ast::WhileExp& e)
  {
    scope++;
    escape.scope_begin();
    e.test_get().accept(*this);
    e.body_get().accept(*this);
    escape.scope_end();
    scope--;
  }
  void EscapesVisitor::operator()(ast::ForExp& e)
  {
    scope++;
    escape.scope_begin();
    e.vardec_get().accept(*this);
    e.hi_get().accept(*this);
    e.body_get().accept(*this);
    escape.scope_end();
    scope--;
  }
  void EscapesVisitor::operator()(ast::IfExp& e)
  {
    scope++;
    escape.scope_begin();
    e.get_test().accept(*this);
    e.get_thenclause().accept(*this);
    if (&e.get_elseclause())
      e.get_elseclause().accept(*this);
    escape.scope_end();
    scope--;
  }
  void EscapesVisitor::operator()(ast::FunctionDec& e)
  {
    scope++;
    escape.scope_begin();
    e.formals_get().accept(*this);
    if (e.result_get())
      e.result_get()->accept(*this);
    if (e.body_get())
      e.body_get()->accept(*this);
    escape.scope_end();
    scope--;
  }
  void EscapesVisitor::operator()(ast::VarDec& e)
  {
    escape.put(e.name_get(), std::pair<ast::VarDec*, int>(&e, scope));
    e.escapable_set(false);
    if (e.type_name_get())
      {
        this->accept(e.type_name_get());
        this->accept(e.init_get());
      }
    else
      this->accept(e.init_get());
  }

  void EscapesVisitor::operator()(ast::SimpleVar& e)
  {
    auto it = escape.get(e.name_get());
    if (it.second != scope)
      {
        it.first->escapable_set(true);
      }
  }

} // namespace escapes
