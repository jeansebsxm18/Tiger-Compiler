/**
 ** \file type/named.cc
 ** \brief Implementation for type/named.hh.
 */

#include <set>

#include <type/named.hh>
#include <type/visitor.hh>

namespace type
{
  Named::Named(misc::symbol name)
    : name_(name)
    , type_(nullptr)
  {}

  Named::Named(misc::symbol name, const Type* type)
    : name_(name)
    , type_(type)
  {}

  void Named::accept(ConstVisitor& v) const { v(*this); }

  void Named::accept(Visitor& v) { v(*this); }

  // FIXME: Some code was deleted here (Sound).
  bool Named::sound() const 
  {
    //TODO
    return true; 
  }

  bool Named::compatible_with(const Type& other) const
  {
    if (*this->type_get() == other.actual())
      return true;
    return false;
  }

} // namespace type