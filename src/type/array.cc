/**
 ** \file type/array.cc
 ** \brief Implementation for type/array.hh.
 */

#include <type/array.hh>
#include <type/visitor.hh>

namespace type
{
  Array::Array(const Type& type)
    : type_(type)
  {}

  void Array::accept(ConstVisitor& v) const { v(*this); }
  void Array::accept(Visitor& v) { v(*this); }
} // namespace type