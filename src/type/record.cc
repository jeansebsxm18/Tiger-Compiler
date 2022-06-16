/**
 ** \file type/record.cc
 ** \brief Implementation for type/record.hh.
 */

#include <ostream>

#include <type/builtin-types.hh>
#include <type/nil.hh>
#include <type/record.hh>
#include <type/visitor.hh>

namespace type
{
  void Record::accept(ConstVisitor& v) const { v(*this); }

  void Record::accept(Visitor& v) { v(*this); }

  const Type* Record::field_type(misc::symbol key) const
  {
    for (auto& v : fields_)
    {
      if (v.name_get() == key)
        return &v.type_get();
    }
    return nullptr;
  }

  int Record::field_index(misc::symbol key) const
  {
    int count = 0;
    for (auto v : fields_)
    {
      if (v.name_get() == key)
        return count; 
      count++;
    }
  }

  bool Record::compatible_with(const Type& other) const
  {
    auto fields_vec = this->fields_get();

    for (auto &f : fields_vec)
    {
      if (f.type_get() != other.actual())
        return false;
    }
    return true;
  }

} // namespace type
