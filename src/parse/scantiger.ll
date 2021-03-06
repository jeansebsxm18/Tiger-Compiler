                                                            /* -*- C++ -*- */
%option c++
%option nounput
%option debug
%option batch

%{

#include <cerrno>
#include <climits>
#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>

#include <misc/contract.hh>
  // Using misc::escape is very useful to quote non printable characters.
  // For instance
  //
  //    std::cerr << misc::escape('\n') << '\n';
  //
  // reports about `\n' instead of an actual new-line character.
#include <misc/escape.hh>
#include <misc/symbol.hh>
#include <parse/parsetiger.hh>
#include <parse/tiger-parser.hh>
  /* FIXME: Some code was deleted here. */

#define YY_USER_ACTION tp.location_.columns(yyleng);

/* Convenient shortcuts. */
#define TOKEN_VAL(Type, Value)                  \
  parser::make_ ## Type(Value, tp.location_)

#define TOKEN(Type)                             \
  parser::make_ ## Type(tp.location_)


// Flex uses `0' for end of file.  0 is not a token_type.
#define yyterminate() return TOKEN(EOF)

# define CHECK_EXTENSION()                              \
  do {                                                  \
    if (!tp.enable_extensions_p_)                       \
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(yytext) << "'\n";       \
  } while (false)

YY_FLEX_NAMESPACE_BEGIN
%}

%x SC_COMMENT SC_STRING

/* Abbreviations.  */
int             [0-9]+
num             \\[0-3][0-7][0-7]
xnum            \\x[0-9a-fA-F]{2}
character       [a-zA-Z]
white           [ \t]
eol             "\n\r"|"\r\n"|"\r"|"\n"
identifier      [a-zA-Z]{1}[a-zA-Z0-9_]*|"_main"
escape          "\\a"|"\\b"|"\\t"|"\\n"|"\\v"|"\\f"|"\\r"
escape-error    \\.
%%
%{
  // FIXME: Some code was deleted here (Local variables).
std::string grown_string;
int comments = 0;

  // Each time yylex is called.
  tp.location_.step();
%}

 /* The rules.  */

{int}         {
                long val = 0;
                val = strtol(yytext, 0, 10);
                if (val > INT_MAX)
                {
                    tp.error_ << misc::error::error_type::scan
                            << tp.location_ << ": Too high int value " << val
                            << "\n";
                }
                return TOKEN_VAL(INT, val);
              }

 /* Metavar tokens. */

"_chunks" {
    return TOKEN(CHUNKS);
}

"_exp" {
    return TOKEN(EXP);
}

"_lvalue" {
    return TOKEN(LVALUE);
}

"_namety" {
    return TOKEN(NAMETY);
}

 /* Keyword tokens. */

"array" {
    return TOKEN(ARRAY);
}
"if" {
    return TOKEN(IF);
}
"then" {
    return TOKEN(THEN);
}
"else" {
    return TOKEN(ELSE);
}
"while" {
    return TOKEN(WHILE);
}
"for" {
    return TOKEN(FOR);
}
"to" {
    return TOKEN(TO);
}
"do" {
    return TOKEN(DO);
}
"let" {
    return TOKEN(LET);
}
"in" {
    return TOKEN(IN);
}
"end" {
    return TOKEN(END);
}
"of" {
    return TOKEN(OF);
}
"break" {
    return TOKEN(BREAK);
}
"nil" {
    return TOKEN(NIL);
}
"function" {
    return TOKEN(FUNCTION);
}
"var" {
    return TOKEN(VAR);
}
"type" {
    return TOKEN(TYPE);
}

"import" {
    return TOKEN(IMPORT);
}

"primitive" {
    return TOKEN(PRIMITIVE);
}

 /* Object related tokens. */

"class" {
    return TOKEN(CLASS);
}

"extends" {
    return TOKEN(EXTENDS);
}

"method" {
    return TOKEN(METHOD);
}

"new" {
    return TOKEN(NEW);
}

 /* Symbol tokens. */

"," {
    return TOKEN(COMMA);
}

":" {
    return TOKEN(COLON);
}

";" {
    return TOKEN(SEMI);
}

"(" {
    return TOKEN(LPAREN);
}

")" {
    return TOKEN(RPAREN);
}

"[" {
    return TOKEN(LBRACK);
}

"]" {
    return TOKEN(RBRACK);
}

"{" {
    return TOKEN(LBRACE);
}

"}" {
    return TOKEN(RBRACE);
}

"." {
    return TOKEN(DOT);
}

"+" {
    return TOKEN(PLUS);
}

"-" {
    return TOKEN(MINUS);
}

"*" {
    return TOKEN(TIMES);
}

"/" {
    return TOKEN(DIVIDE);
}

"=" {
    return TOKEN(EQ);
}

"<>" {
    return TOKEN(NE);
}

"<" {
    return TOKEN(LT);
}

"<=" {
    return TOKEN(LE);
}

">" {
    return TOKEN(GT);
}

">=" {
    return TOKEN(GE);
}

"&" {
    return TOKEN(AND);
}

"|" {
    return TOKEN(OR);
}

":=" {
    return TOKEN(ASSIGN);
}

{eol} {
        tp.location_.lines(yyleng);
        tp.location_.step();
      }

{white} { ; }
 /* Begin of a string. */

"\"" {
  grown_string.clear();
  BEGIN SC_STRING;
}

  /* Begin of a comment. */

"/*" {
  BEGIN SC_COMMENT;
  comments++;
}

  /* String state. */

<SC_STRING>
{
  "\"" {
    BEGIN INITIAL;
    return TOKEN_VAL(STRING, grown_string);
  }
  {character} { grown_string += yytext; }
  {escape} { grown_string.append(yytext); }
  {num} { grown_string.append(yytext + 3); }
  {xnum} { grown_string.append(1, strtol(yytext + 2, 0, 16)); }
  {int} { grown_string += yytext; }
  "\\" { grown_string.append(yytext); }
  "\\\\" { grown_string.append(yytext); }
  "\\\"" { grown_string.append(yytext); }
  <<EOF>> { 
      tp.error_ << misc::error::error_type::scan
                << tp.location_ << ": Unexpected end of file. Expecting closing string"
                << "\n";
        BEGIN INITIAL;
  }

  {escape-error} { tp.error_ << misc::error::error_type::scan 
                                << tp.location_ << ": Unexpected escape character " << yytext << ".\n"; 
    }
   . { grown_string.append(yytext); }
   
}

  /* Comment state. */

<SC_COMMENT>
{
  "/*" {
    comments++;
  }
  "*/" {
    comments--;
    if (comments == 0) {
      BEGIN INITIAL;
    }
  }
  \\[abfnrtv] { }
  {eol} { }
  . { }
  <<EOF>> {
      tp.error_ << misc::error::error_type::scan
                    << tp.location_ << ": Unexpected end of file. Expecting closing comment" << "\n";
    BEGIN INITIAL;
  }
}

 /* Id. */

{identifier} { return TOKEN_VAL(ID, yytext); }

 /* Error. */
. { tp.error_ << misc::error::error_type::scan 
                << tp.location_ << ": Invalid character " << yytext << "\n"; }

%%

// Do not use %option noyywrap, because then flex generates the same
// definition of yywrap, but outside the namespaces, so it defines it
// for ::yyFlexLexer instead of ::parse::yyFlexLexer.
int yyFlexLexer::yywrap() { return 1; }

void
yyFlexLexer::scan_open_(std::istream& f)
{
  yypush_buffer_state(YY_CURRENT_BUFFER);
  yy_switch_to_buffer(yy_create_buffer(&f, YY_BUF_SIZE));
}

void
yyFlexLexer::scan_close_()
{
  yypop_buffer_state();
}

YY_FLEX_NAMESPACE_END
