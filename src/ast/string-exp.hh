/**
 ** \file ast/string-exp.hh
 ** \brief Declaration of ast::StringExp.
 */

#pragma once

#include <string>
#include <ast/exp.hh>

namespace ast
{
  /// StringExp.
  class StringExp : public Exp
  {
  public:
    StringExp(const Location& location, std::string string);
    StringExp(const StringExp&) = delete;
    StringExp& operator=(const StringExp&) = delete;

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    std::string string_get() const;

  protected:
    std::string string_;
  };
} // namespace ast
#include <ast/string-exp.hxx>
