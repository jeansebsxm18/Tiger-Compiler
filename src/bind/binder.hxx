/**
 ** \file bind/binder.hxx
 ** \brief Inline methods of bind::Binder.
 **/

#pragma once

#include <bind/binder.hh>

namespace bind
{
  /*-----------------.
  | Error handling.  |
  `-----------------*/

  inline void Binder::error(const ast::Ast& loc, const std::string& msg)
  {
    error_ << misc::error::error_type::bind << loc.location_get() << ": " << msg
           << '\n';
  }

  inline void Binder::error(const std::string& msg)
  {
    error_ << misc::error::error_type::bind << msg
           << '\n';
  }

  template <typename T>
  void Binder::undeclared(const std::string& k, const T& e)
  {
    error(e, k);
  }

  template <typename T> void Binder::redefinition(const T& e1, const T& e2)
  {
    error(*e2, "redefinition: " + e2->name_get().get());
    error(*e1, "first definition");
  }

  template <typename T> void Binder::loop(const T& e)
  {
    error(e, "\'break\' outside any loop");
  }

  /*----------------------------.
  | Visiting /ChunkInterface/.  |
  `----------------------------*/

  template <class D> void Binder::chunk_visit(ast::Chunk<D>& e)
  {
    // Shorthand.
    using chunk_type = ast::Chunk<D>;
    for (const auto& dec : e)
      dec->accept(*this);
    // FIXME make for loop for body.
  }

  /* These specializations are in bind/binder.hxx, so that derived
     visitors can use them (otherwise, they wouldn't see them).  */

  // FIXME: Some code was deleted here.

} // namespace bind
