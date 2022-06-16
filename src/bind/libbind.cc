/**
 ** \file bind/libbind.cc
 ** \brief Define exported bind functions.
 */

#include <bind/binder.hh>
#include <bind/renamer.hh>

namespace bind
{
  misc::error bind_compute(ast::Ast& tree)
  {
    Binder bind_compute;
    bind_compute(tree);
    return bind_compute.error_get();
  }

  void name_compute(ast::Ast& tree)
  {
    Renamer name_compute;
    name_compute(tree);
  }
} // namespace bind