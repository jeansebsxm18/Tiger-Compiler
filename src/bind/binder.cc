/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <ast/all.hh>
#include <bind/binder.hh>

#include <misc/contract.hh>

namespace bind
{
  /*-----------------.
  | Error handling.  |
  `-----------------*/

  /// The error handler.
  const misc::error& Binder::error_get() const { return error_; }

  void Binder::check_main(const ast::FunctionDec& e)
  {
    if (scope_fun_.nb_scope == 1)
    {
      if (e.name_get().get() == "_main")
        main = true;
    }
    else if (main && e.name_get().get() == "_main")
    {
      error(e, "Bad _main deefinition");
    }
  }
  
  /*----------------.
  | Symbol tables.  |
  `----------------*/

  void Binder::scope_begin()
  {
    scope_fun_.scope_begin();
    scope_type_.scope_begin();
    scope_var_.scope_begin();
  }

  void Binder::scope_end()
  {
    scope_fun_.scope_end();
    scope_type_.scope_end();
    scope_var_.scope_end();
  }

  /*---------.
  | Visits.  |
  `---------*/

  void Binder::operator()(ast::FunctionDec& e)
  {
    check_main(e);
    scope_fun_.put(e.name_get(), &e);
    scope_begin();
    misc::scoped_map<misc::symbol, ast::VarDec*> scope_var;
    for (auto& x : e.formals_get())
      {
        auto name = scope_var.get(x->name_get());
        if (name == nullptr)
          {
            x->accept(*this);
            scope_var.put(x->name_get(), x);
          }
        else
          Binder::redefinition(name, x);
      }
    if (e.result_get())
      {
        auto type = scope_type_.get(e.result_get()->name_get());
        if (type == nullptr && e.result_get()->name_get() != "int"
            && e.result_get()->name_get() != "string")
          {
            Binder::undeclared(
              "undeclared type: " + e.result_get()->name_get().get(), e);
          }
        else
          {
            e.result_get()->def_set(type);
            if (e.result_get()->def_get() != 0)
              e.result_get()->def_get()->accept(*this);
          }
      }
    if (e.body_get())
      e.body_get()->accept(*this);
    scope_end();
  }

  void Binder::operator()(ast::CallExp& e)
  {
    auto name = scope_fun_.get(e.name_get());
    if (name != nullptr)
      e.def_set(name);
    else
      Binder::undeclared("undeclared function: " + e.name_get().get(), e);
    auto exps = e.args_get();
    for (auto exp : exps)
      exp->accept(*this);
  }

  void Binder::operator()(ast::TypeDec& e)
  {
    scope_type_.put(e.name_get(), &e);
    e.ty_get().accept(*this);
  }

  void Binder::operator()(ast::RecordTy& e)
  {
    auto fields = e.field_get();
    for (auto& field : fields)
      {
        auto name = scope_type_.get(field->type_name_get().name_get());
        if (name == nullptr && field->type_name_get().name_get() != "int"
            && field->type_name_get().name_get() != "string")
          Binder::undeclared("undeclared type: "
                               + field->type_name_get().name_get().get(),
                             *field);
        else
          field->accept(*this);
      }
  }

  void Binder::operator()(ast::VarDec& e)
  {
    if (e.type_name_get())
      {
        auto type = scope_type_.get(e.type_name_get()->name_get());
        if (type == nullptr && e.type_name_get()->name_get() != "int"
            && e.type_name_get()->name_get() != "string")
          {
            Binder::undeclared(
              "undeclared type: " + e.type_name_get()->name_get().get(), e);
          }
        else
          {
            e.type_name_get()->def_set(type);
            this->accept(e.type_name_get());
            this->accept(e.init_get());
          }
      }
    else
      {
        this->accept(e.init_get());
      }
    scope_var_.put(e.name_get(), &e);
  }

  void Binder::operator()(ast::LetExp& e)
  {
    scope_begin();
    super_type::operator()(e);
    scope_end();
  }

  void Binder::operator()(ast::WhileExp& e)
  {
    e.test_get().accept(*this);
    scope_begin();
    scope_loop_.push_back(&e);
    e.body_get().accept(*this);
    scope_end();
    scope_loop_.pop_back();
  }
  void Binder::operator()(ast::ForExp& e)
  {
    e.hi_get().accept(*this);
    e.vardec_get().accept(*this);
    scope_begin();
    scope_loop_.push_back(&e);
    e.body_get().accept(*this);
    scope_end();
    scope_loop_.pop_back();
  }

  void Binder::operator()(ast::MethodDec& e)
  {
    scope_method_.put(e.name_get(), &e);
    e.formals_get().accept(*this);
    if (e.result_get() && e.result_get()->def_get())
      {
        auto type = scope_type_.get(e.result_get()->name_get());
        if (type == nullptr && e.result_get()->name_get() != "int"
            && e.result_get()->name_get() != "string")
          {
            Binder::undeclared(
              "undeclared type: " + e.result_get()->name_get().get(), e);
          }
        else
          {
            e.result_get()->def_set(type);
            if (e.result_get()->def_get() != 0)
              e.result_get()->def_get()->accept(*this);
          }
      }
    if (e.body_get())
      e.body_get()->accept(*this);
  }

  void Binder::operator()(ast::MethodChunk& e)
  {
    misc::scoped_map<misc::symbol, ast::MethodDec*> method;
    for (auto& dec : e)
      {
        auto name = method.get(dec->name_get());
        if (name != nullptr)
          Binder::redefinition(name, dec);
        else
          {
            method.put(dec->name_get(), dec);
            dec->accept(*this);
          }
      }
  }

  void Binder::operator()(ast::SimpleVar& e)
  {
    auto name = scope_var_.get(e.name_get());
    if (name != nullptr)
      e.def_set(name);
    else
      Binder::undeclared("undeclared variable: " + e.name_get().get(), e);
  }

  void Binder::operator()(ast::BreakExp& e)
  {
    if (scope_loop_.size() == 0)
      Binder::loop(e);
    else
      {
        auto name = scope_loop_.back();
        e.def_set(name);
      }
  }

  void Binder::operator()(ast::RecordExp& e)
  {
    auto name = scope_type_.get(e.get_type_name().name_get());
    if (name != nullptr)
      e.def_set(name);
    else
      Binder::undeclared(
        "undeclared type: " + e.get_type_name().name_get().get(), e);
    e.get_type_name().accept(*this);
    auto fieldInit = e.get_fields();
    for (auto elt : fieldInit)
      elt->accept(*this);
  }

  void Binder::operator()(ast::ObjectExp& e)
  {
    auto name = scope_type_.get(e.type_name_get().name_get());
    if (name != nullptr)
      {
        e.def_set(name);
        e.type_name_get().accept(*this);
      }
    else
      Binder::undeclared(
        "undeclared type: " + e.type_name_get().name_get().get(), e);
  }

  void Binder::operator()(ast::IfExp& e)
  {
    e.get_test().accept(*this);
    scope_begin();
    e.get_thenclause().accept(*this);
    scope_end();
    scope_begin();
    if (&e.get_elseclause())
      {
        e.get_elseclause().accept(*this);
      }
    scope_end();
  }

  void Binder::operator()(ast::ClassTy& e)
  {
    if (&e.super_get())
      {
        auto type = scope_type_.get(e.super_get().name_get());
        if (type == nullptr)
          {
            Binder::undeclared(
              "undeclared type: " + e.super_get().name_get().get(), e);
          }
        else
          e.super_get().accept(*this);
      }

    for (auto ch : e.chunks_get())
      ch->accept(*this);
  }

  void Binder::operator()(ast::NameTy& e)
  {
    if (scope_type_.contains(e.name_get()))
      {
        auto def = scope_type_.get(e.name_get());
        if (def)
          e.def_set(def);
        else
          error(e, "definition type is null inside namety binder");
      }
    else
      {
        if (e.name_get() == "string" || e.name_get() == "int")
          return;
        Binder::undeclared("undeclared type: " + e.name_get().get(), e);
      }
  }

  /*-------------------.
  | Visiting VarChunk. |
  `-------------------*/

  void Binder::operator()(ast::VarChunk& e) { chunk_visit(e); }

  /*------------------------.
  | Visiting FunctionChunk. |
  `------------------------*/

  void Binder::operator()(ast::FunctionChunk& e)
  {
    for (auto& dec : e)
      {
        auto name = scope_fun_.get(dec->name_get());
        if (name != nullptr)
          Binder::redefinition(name, dec);
        else
          {
            scope_fun_.put(dec->name_get(), dec);
            dec->accept(*this);
          }
      }
  }

  /*--------------------.
  | Visiting TypeChunk. |
  `--------------------*/
  void Binder::operator()(ast::TypeChunk& e)
  {
    for (auto& dec : e)
      {
        auto name = scope_type_.get(dec->name_get());
        if (name != nullptr)
          Binder::redefinition(name, dec);
        else
          {
            scope_type_.put(dec->name_get(), dec);
            dec->accept(*this);
          }
      }
  }
} // namespace bind
