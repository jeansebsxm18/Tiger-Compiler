/**
 ** \file ast/pretty-printer.hh
 ** \brief Declaration of ast::PrettyPrinter.
 */

#pragma once

#include <ast/default-visitor.hh>
#include <ast/object-visitor.hh>

namespace ast
{
  /// Visit an Ast and print the content of each node.
  class PrettyPrinter
    : virtual public DefaultConstVisitor
    , virtual public ObjectConstVisitor
  {
  public:
    using super_type = DefaultConstVisitor;
    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build to print on \a ostr.
    PrettyPrinter(std::ostream& ostr);

    /// Visit methods.
    /// \{
    //Var
    void operator()(const FieldInit& e) override;
    void operator()(const Field& e) override;
    void operator()(const SimpleVar& e) override;    //OK
    void operator()(const FieldVar& e) override;     //OK
    void operator()(const SubscriptVar& e) override; //OK
    //Exp
    void operator()(const CastExp& e) override; //OK

    void operator()(const ArrayExp& e) override;  //OK
    void operator()(const AssignExp& e) override; //OK
    void operator()(const CallExp& e) override;   //OK
    void operator()(const ForExp& e) override;    //OK
    void operator()(const IfExp& e) override;     //OK
    void operator()(const IntExp& e) override;    //OK
    void operator()(const LetExp& e) override;    //OK
    void operator()(const NilExp& e) override;    //No get
    void operator()(const ObjectExp& e) override; //OK
    void operator()(const OpExp& e) override;     //No complete
    void operator()(const RecordExp& e) override; //OK
    void operator()(const SeqExp& e) override;
    void operator()(const StringExp& e) override; //OK
    void operator()(const WhileExp& e) override;  //OK
    void operator()(const BreakExp& e) override;
    void operator()(const MethodCallExp& e) override;

    // Ty
    void operator()(const ArrayTy& e) override;  //OK
    void operator()(const ClassTy& e) override;  //OK
    void operator()(const NameTy& e) override;   //OK
    void operator()(const RecordTy& e) override; //OK

    //Dec
    void operator()(const FunctionDec& e) override; //OK
    void operator()(const TypeDec& e) override;     //OK
    void operator()(const VarDec& e) override;      //OK
    void operator()(const MethodDec& e) override;   //OK
    // FIXME: Some code was deleted here.
    /// \}

  private:
    // Factor pretty-printing of RecordExp and RecordTy.
    template <typename RecordClass> void print_record(const RecordClass& e);

    // Whether we are in a ast::ClassTy.
    bool within_classty_p_ = false;

  protected:
    /// The stream to print on.
    std::ostream& ostr_;
  };

} // namespace ast
