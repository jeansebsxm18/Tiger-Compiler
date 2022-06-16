/**
 ** \file type/class.cc
 ** \brief Implementation for type/class.hh.
 */

#include <ostream>

#include <range/v3/algorithm/find.hpp>
#include <type/class.hh>
#include <type/visitor.hh>

namespace type
{
  Class::Class(const Class* super)
    : Type()
    , id_(fresh_id())
    , super_(super)
    , subclasses_()
  {}

  void Class::accept(ConstVisitor& v) const { v(*this); }

  void Class::accept(Visitor& v) { v(*this); }

  const Type* Class::attr_type(misc::symbol key) const
  {
    for (const Attribute& elt : attrs_get())
    {
      if (elt.name_get() == key)
        return &elt.type_get();
    }
    return nullptr;
  }

  const Type* Class::meth_type(misc::symbol key) const
  {
    for (const auto& meth : meths_get())
    {
      if (meth->name_get() == key)
        return &meth->type_get();
    }
    return nullptr;
  }

  const Class* Class::common_root(const Class& other) const
  {
    if (super_->id_get() == other.super_get()->id_get())
      return super_;
    return nullptr;
  }

  bool Class::sound() const
  {
    for (const auto& elt : subclasses_get())
    {
      if (elt->id_get() == id_)
        return false;
    }
    return true;
  }
  bool Class::compatible_with(const Type& other) const
  {
    return this->actual() == other;
  }

  const Class& Class::object_instance()
  {
    static Class instance;
    return instance;
  }

  unsigned Class::fresh_id()
  {
    static unsigned counter_ = 0;
    return counter_++;
  }

} // namespace type
