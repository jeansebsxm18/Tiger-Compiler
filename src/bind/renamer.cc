/**
 ** \file bind/renamer.cc
 ** \brief Implementation of bind::Renamer.
 */

#include <bind/renamer.hh>

namespace bind
{
  using namespace ast;

  Renamer::Renamer()
    : super_type()
    , new_names_()
  {}

  template <>
  misc::symbol
  Renamer::new_name_compute<ast::FunctionDec>(const ast::FunctionDec& e)
  {
    auto name = e.name_get();
    if (name != "_main" && e.body_get())
      {
        auto new_name = misc::symbol::fresh(name);
        new_names_.insert({&e, new_name});
        return new_name;
      }
    return name;
  }

  void Renamer::operator()(ast::NameTy& ty) { visit(ty, ty.def_get()); }

  void Renamer::operator()(ast::CallExp& ty) { visit(ty, ty.def_get()); }

  void Renamer::operator()(ast::SimpleVar& ty) { visit(ty, ty.def_get()); }

  void Renamer::operator()(ast::FunctionDec& ty) { visit(ty, &ty); }

  void Renamer::operator()(ast::VarDec& ty) { visit(ty, &ty); }

  void Renamer::operator()(ast::TypeDec& ty) { visit(ty, &ty); }

} // namespace bind
