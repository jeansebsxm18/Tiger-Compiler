/**
 ** \file bind/tasks.hh
 ** \brief Bind module related tasks.
 */

#pragma once

#include <task/libtask.hh>

namespace bind::tasks
{
  TASK_GROUP("3. Bind");

  DISJUNCTIVE_TASK_DECLARE("bound",
                           "default the computation of bindings to Tiger"
                           "(without objects nor overloading)",
                           "bindings-compute");

  //OBJECT AFTER biding-compute in DISJONCTIVE TASK

  TASK_DECLARE("b|bindings-compute",
               "bind the identifiers ",
               bind_compute,
               "parse");

  TASK_DECLARE("B|bindings-display",
               "enable bindings display in the AST",
               bind_display,
               "parse");

  TASK_DECLARE("rename",
               "rename identifiers to unique names",
               name_compute,
               "bound");
} // namespace bind::tasks
