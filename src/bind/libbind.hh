/**
 ** \file bind/libbind.hh
 ** \brief Interface of the bind module.
 */

#include <ast/fwd.hh>
#include <misc/error.hh>

namespace bind
{
  misc::error bind_compute(ast::Ast& tree);
  void name_compute(ast::Ast& tree);
} // namespace bind
