/**
 ** \file bind/renamer.hxx
 ** \brief Template methods of bind::Renamer.
 */

#pragma once

#include <bind/renamer.hh>

namespace bind
{
  template <class E, class Def> void Renamer::visit(E& e, const Def* def)
  {
    if (def)
      {
        auto name = new_name(def);
        e.name_set(name);
      }
    super_type::operator()(e);
  }
  /*
  template <>
  inline misc::symbol Renamer::new_name_compute<ast::FunctionDec>(const ast::FunctionDec& e)
  {
    auto name = e.name_get();
    std::cout << "FUNC NEW NAME" << std::endl;
    if (name != "_main" && e.body_get())
    {
      auto new_name = misc::symbol::fresh(name);
      new_names_.insert( {&e, new_name} );
      return new_name;
    }
    return name;
  }
*/
  template <typename Def> misc::symbol Renamer::new_name_compute(const Def& e)
  {
    auto name = e.name_get();

    auto new_name = misc::symbol::fresh(name);
    new_names_.insert({&e, new_name});
    return new_name;
  }

  template <typename Def> misc::symbol Renamer::new_name(const Def& e)
  {
    auto it = new_names_.find(e);
    if (it == new_names_.end())
      return new_name_compute(*e);
    return (*it).second;
  }
} // namespace bind
