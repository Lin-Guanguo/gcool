// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 35 "Parser.y"

    #include "gcool/AST/AST.h"
    #include "gcool/AST/Expr.h"
    using namespace gcool::ast;

#line 47 "Parser.cpp"


#include "Parser.h"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "Parser.y"
namespace gcool {
#line 126 "Parser.cpp"

  /// Build a parser object.
  Parser::Parser (yyscan_t scannner_yyarg, gcool::ast::ASTContext* context_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scannner (scannner_yyarg),
      context (context_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
    {
      case symbol_kind::S_class: // class
      case symbol_kind::S_features: // features
        value.copy< NoneInitHolder<gcool::ast::Class> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.copy< NoneInitHolder<gcool::ast::Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.copy< NoneInitHolder<gcool::ast::FormalDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_inherits: // inherits
      case symbol_kind::S_symbol: // symbol
        value.copy< NoneInitHolder<gcool::ast::Symbol> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_is_final: // is_final
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_ERROR: // ERROR
        value.copy< const char* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.copy< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_branchs: // case_branchs
        value.copy< gcool::ast::CaseBranchList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class_seq: // class_seq
        value.copy< gcool::ast::ClassList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_args_: // args_
      case symbol_kind::S_block_exprs: // block_exprs
        value.copy< gcool::ast::ExprList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_params_: // params_
        value.copy< gcool::ast::FormalList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_let_init_exprs: // let_init_exprs
        value.copy< gcool::ast::LetInitList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_optional_assign: // optional_assign
        value.copy< gcool::ast::OptionalExpr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STR: // STR
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_class: // class
      case symbol_kind::S_features: // features
        value.move< NoneInitHolder<gcool::ast::Class> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< NoneInitHolder<gcool::ast::Expr> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_formal: // formal
        value.move< NoneInitHolder<gcool::ast::FormalDecl> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_inherits: // inherits
      case symbol_kind::S_symbol: // symbol
        value.move< NoneInitHolder<gcool::ast::Symbol> > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_is_final: // is_final
        value.move< bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_ERROR: // ERROR
        value.move< const char* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.move< double > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_case_branchs: // case_branchs
        value.move< gcool::ast::CaseBranchList > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_class_seq: // class_seq
        value.move< gcool::ast::ClassList > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_args_: // args_
      case symbol_kind::S_block_exprs: // block_exprs
        value.move< gcool::ast::ExprList > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_params_: // params_
        value.move< gcool::ast::FormalList > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_let_init_exprs: // let_init_exprs
        value.move< gcool::ast::LetInitList > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_optional_assign: // optional_assign
        value.move< gcool::ast::OptionalExpr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_STR: // STR
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_class: // class
      case symbol_kind::S_features: // features
        value.YY_MOVE_OR_COPY< NoneInitHolder<gcool::ast::Class> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.YY_MOVE_OR_COPY< NoneInitHolder<gcool::ast::Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.YY_MOVE_OR_COPY< NoneInitHolder<gcool::ast::FormalDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_inherits: // inherits
      case symbol_kind::S_symbol: // symbol
        value.YY_MOVE_OR_COPY< NoneInitHolder<gcool::ast::Symbol> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_is_final: // is_final
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_ERROR: // ERROR
        value.YY_MOVE_OR_COPY< const char* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_branchs: // case_branchs
        value.YY_MOVE_OR_COPY< gcool::ast::CaseBranchList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class_seq: // class_seq
        value.YY_MOVE_OR_COPY< gcool::ast::ClassList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_args_: // args_
      case symbol_kind::S_block_exprs: // block_exprs
        value.YY_MOVE_OR_COPY< gcool::ast::ExprList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_params_: // params_
        value.YY_MOVE_OR_COPY< gcool::ast::FormalList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_let_init_exprs: // let_init_exprs
        value.YY_MOVE_OR_COPY< gcool::ast::LetInitList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_optional_assign: // optional_assign
        value.YY_MOVE_OR_COPY< gcool::ast::OptionalExpr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STR: // STR
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_class: // class
      case symbol_kind::S_features: // features
        value.move< NoneInitHolder<gcool::ast::Class> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< NoneInitHolder<gcool::ast::Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.move< NoneInitHolder<gcool::ast::FormalDecl> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_inherits: // inherits
      case symbol_kind::S_symbol: // symbol
        value.move< NoneInitHolder<gcool::ast::Symbol> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_is_final: // is_final
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_ERROR: // ERROR
        value.move< const char* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_case_branchs: // case_branchs
        value.move< gcool::ast::CaseBranchList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_class_seq: // class_seq
        value.move< gcool::ast::ClassList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_args_: // args_
      case symbol_kind::S_block_exprs: // block_exprs
        value.move< gcool::ast::ExprList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_params_: // params_
        value.move< gcool::ast::FormalList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_let_init_exprs: // let_init_exprs
        value.move< gcool::ast::LetInitList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_optional_assign: // optional_assign
        value.move< gcool::ast::OptionalExpr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STR: // STR
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_class: // class
      case symbol_kind::S_features: // features
        value.copy< NoneInitHolder<gcool::ast::Class> > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.copy< NoneInitHolder<gcool::ast::Expr> > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.copy< NoneInitHolder<gcool::ast::FormalDecl> > (that.value);
        break;

      case symbol_kind::S_inherits: // inherits
      case symbol_kind::S_symbol: // symbol
        value.copy< NoneInitHolder<gcool::ast::Symbol> > (that.value);
        break;

      case symbol_kind::S_is_final: // is_final
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_ERROR: // ERROR
        value.copy< const char* > (that.value);
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_case_branchs: // case_branchs
        value.copy< gcool::ast::CaseBranchList > (that.value);
        break;

      case symbol_kind::S_class_seq: // class_seq
        value.copy< gcool::ast::ClassList > (that.value);
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_args_: // args_
      case symbol_kind::S_block_exprs: // block_exprs
        value.copy< gcool::ast::ExprList > (that.value);
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_params_: // params_
        value.copy< gcool::ast::FormalList > (that.value);
        break;

      case symbol_kind::S_let_init_exprs: // let_init_exprs
        value.copy< gcool::ast::LetInitList > (that.value);
        break;

      case symbol_kind::S_optional_assign: // optional_assign
        value.copy< gcool::ast::OptionalExpr > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_STR: // STR
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_class: // class
      case symbol_kind::S_features: // features
        value.move< NoneInitHolder<gcool::ast::Class> > (that.value);
        break;

      case symbol_kind::S_expr: // expr
        value.move< NoneInitHolder<gcool::ast::Expr> > (that.value);
        break;

      case symbol_kind::S_formal: // formal
        value.move< NoneInitHolder<gcool::ast::FormalDecl> > (that.value);
        break;

      case symbol_kind::S_inherits: // inherits
      case symbol_kind::S_symbol: // symbol
        value.move< NoneInitHolder<gcool::ast::Symbol> > (that.value);
        break;

      case symbol_kind::S_is_final: // is_final
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_ERROR: // ERROR
        value.move< const char* > (that.value);
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.move< double > (that.value);
        break;

      case symbol_kind::S_case_branchs: // case_branchs
        value.move< gcool::ast::CaseBranchList > (that.value);
        break;

      case symbol_kind::S_class_seq: // class_seq
        value.move< gcool::ast::ClassList > (that.value);
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_args_: // args_
      case symbol_kind::S_block_exprs: // block_exprs
        value.move< gcool::ast::ExprList > (that.value);
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_params_: // params_
        value.move< gcool::ast::FormalList > (that.value);
        break;

      case symbol_kind::S_let_init_exprs: // let_init_exprs
        value.move< gcool::ast::LetInitList > (that.value);
        break;

      case symbol_kind::S_optional_assign: // optional_assign
        value.move< gcool::ast::OptionalExpr > (that.value);
        break;

      case symbol_kind::S_INT: // INT
        value.move< int > (that.value);
        break;

      case symbol_kind::S_STR: // STR
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, scannner));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_class: // class
      case symbol_kind::S_features: // features
        yylhs.value.emplace< NoneInitHolder<gcool::ast::Class> > ();
        break;

      case symbol_kind::S_expr: // expr
        yylhs.value.emplace< NoneInitHolder<gcool::ast::Expr> > ();
        break;

      case symbol_kind::S_formal: // formal
        yylhs.value.emplace< NoneInitHolder<gcool::ast::FormalDecl> > ();
        break;

      case symbol_kind::S_inherits: // inherits
      case symbol_kind::S_symbol: // symbol
        yylhs.value.emplace< NoneInitHolder<gcool::ast::Symbol> > ();
        break;

      case symbol_kind::S_is_final: // is_final
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_ERROR: // ERROR
        yylhs.value.emplace< const char* > ();
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_case_branchs: // case_branchs
        yylhs.value.emplace< gcool::ast::CaseBranchList > ();
        break;

      case symbol_kind::S_class_seq: // class_seq
        yylhs.value.emplace< gcool::ast::ClassList > ();
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_args_: // args_
      case symbol_kind::S_block_exprs: // block_exprs
        yylhs.value.emplace< gcool::ast::ExprList > ();
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_params_: // params_
        yylhs.value.emplace< gcool::ast::FormalList > ();
        break;

      case symbol_kind::S_let_init_exprs: // let_init_exprs
        yylhs.value.emplace< gcool::ast::LetInitList > ();
        break;

      case symbol_kind::S_optional_assign: // optional_assign
        yylhs.value.emplace< gcool::ast::OptionalExpr > ();
        break;

      case symbol_kind::S_INT: // INT
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_STR: // STR
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: class_seq
#line 72 "Parser.y"
                                    { }
#line 1064 "Parser.cpp"
    break;

  case 3: // class_seq: %empty
#line 75 "Parser.y"
                                    { }
#line 1070 "Parser.cpp"
    break;

  case 4: // class_seq: class_seq class SEMICOLON
#line 76 "Parser.y"
                                    { context->Classes.push_back(std::move(yystack_[1].value.as < NoneInitHolder<gcool::ast::Class> > ())); }
#line 1076 "Parser.cpp"
    break;

  case 5: // class: is_final CLASS symbol inherits LB features RB
#line 79 "Parser.y"
                                                     { yylhs.value.as < NoneInitHolder<gcool::ast::Class> > () = std::move(yystack_[1].value.as < NoneInitHolder<gcool::ast::Class> > ()); yylhs.value.as < NoneInitHolder<gcool::ast::Class> > ()->Inheirt = yystack_[3].value.as < NoneInitHolder<gcool::ast::Symbol> > (); yylhs.value.as < NoneInitHolder<gcool::ast::Class> > ()->Name = yystack_[4].value.as < NoneInitHolder<gcool::ast::Symbol> > (); yylhs.value.as < NoneInitHolder<gcool::ast::Class> > ()->IsFinal = yystack_[6].value.as < bool > (); }
#line 1082 "Parser.cpp"
    break;

  case 6: // is_final: %empty
#line 82 "Parser.y"
            { yylhs.value.as < bool > () = false; }
#line 1088 "Parser.cpp"
    break;

  case 7: // is_final: FINAL
#line 83 "Parser.y"
            { yylhs.value.as < bool > () = true; }
#line 1094 "Parser.cpp"
    break;

  case 8: // inherits: %empty
#line 86 "Parser.y"
                        { yylhs.value.as < NoneInitHolder<gcool::ast::Symbol> > () = context->Symtbl.getObject(); }
#line 1100 "Parser.cpp"
    break;

  case 9: // inherits: INHERITS symbol
#line 87 "Parser.y"
                        { yylhs.value.as < NoneInitHolder<gcool::ast::Symbol> > () = yystack_[0].value.as < NoneInitHolder<gcool::ast::Symbol> > (); }
#line 1106 "Parser.cpp"
    break;

  case 10: // symbol: SYMBOL
#line 90 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Symbol> > () = context->Symtbl.get(yystack_[0].value.as < const char* > ()); }
#line 1112 "Parser.cpp"
    break;

  case 11: // formal: symbol COLON symbol
#line 93 "Parser.y"
                            { yylhs.value.as < NoneInitHolder<gcool::ast::FormalDecl> > () = FormalDecl{yystack_[2].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Symbol> > ()}; }
#line 1118 "Parser.cpp"
    break;

  case 12: // features: %empty
#line 96 "Parser.y"
            { yylhs.value.as < NoneInitHolder<gcool::ast::Class> > () = Class{ Symbol::EmptySymbol, Symbol::EmptySymbol }; }
#line 1124 "Parser.cpp"
    break;

  case 13: // features: features formal optional_assign SEMICOLON
#line 97 "Parser.y"
                                                 { yylhs.value.as < NoneInitHolder<gcool::ast::Class> > () = std::move(yystack_[3].value.as < NoneInitHolder<gcool::ast::Class> > ()); yylhs.value.as < NoneInitHolder<gcool::ast::Class> > ()->Attrs.push_back(AttrFeature{yystack_[2].value.as < NoneInitHolder<gcool::ast::FormalDecl> > (), yystack_[1].value.as < gcool::ast::OptionalExpr > ()}); }
#line 1130 "Parser.cpp"
    break;

  case 14: // features: features symbol LP params RP COLON symbol LB expr RB SEMICOLON
#line 98 "Parser.y"
                                                                        { yylhs.value.as < NoneInitHolder<gcool::ast::Class> > () = std::move(yystack_[10].value.as < NoneInitHolder<gcool::ast::Class> > ()); yylhs.value.as < NoneInitHolder<gcool::ast::Class> > ()->Methods.push_back(MethodFeature{yystack_[9].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[4].value.as < NoneInitHolder<gcool::ast::Symbol> > (), std::move(yystack_[7].value.as < gcool::ast::FormalList > ()), yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > ()}); }
#line 1136 "Parser.cpp"
    break;

  case 15: // optional_assign: %empty
#line 101 "Parser.y"
                   { yylhs.value.as < gcool::ast::OptionalExpr > () = OptionalExpr{}; }
#line 1142 "Parser.cpp"
    break;

  case 16: // optional_assign: ASSIGN expr
#line 102 "Parser.y"
                   { yylhs.value.as < gcool::ast::OptionalExpr > () = yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (); }
#line 1148 "Parser.cpp"
    break;

  case 17: // params: %empty
#line 105 "Parser.y"
                { yylhs.value.as < gcool::ast::FormalList > () = FormalList{}; }
#line 1154 "Parser.cpp"
    break;

  case 18: // params: params_
#line 106 "Parser.y"
                { yylhs.value.as < gcool::ast::FormalList > () = std::move(yystack_[0].value.as < gcool::ast::FormalList > ()); }
#line 1160 "Parser.cpp"
    break;

  case 19: // params_: formal
#line 109 "Parser.y"
                            { yylhs.value.as < gcool::ast::FormalList > () = FormalList{}; yylhs.value.as < gcool::ast::FormalList > ().push_back(yystack_[0].value.as < NoneInitHolder<gcool::ast::FormalDecl> > ()); }
#line 1166 "Parser.cpp"
    break;

  case 20: // params_: params_ COMMA formal
#line 110 "Parser.y"
                            { yylhs.value.as < gcool::ast::FormalList > () = std::move(yystack_[2].value.as < gcool::ast::FormalList > ()); yylhs.value.as < gcool::ast::FormalList > ().push_back(yystack_[0].value.as < NoneInitHolder<gcool::ast::FormalDecl> > ()); }
#line 1172 "Parser.cpp"
    break;

  case 21: // expr: symbol
#line 113 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprSymbol(yystack_[0].value.as < NoneInitHolder<gcool::ast::Symbol> > ())); }
#line 1178 "Parser.cpp"
    break;

  case 22: // expr: TRUE
#line 114 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprBool(true)); }
#line 1184 "Parser.cpp"
    break;

  case 23: // expr: FALSE
#line 115 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprBool(false)); }
#line 1190 "Parser.cpp"
    break;

  case 24: // expr: INT
#line 116 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprInt(yystack_[0].value.as < int > ())); }
#line 1196 "Parser.cpp"
    break;

  case 25: // expr: FLOAT
#line 117 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprFloat(yystack_[0].value.as < double > ())); }
#line 1202 "Parser.cpp"
    break;

  case 26: // expr: STR
#line 118 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprString(yystack_[0].value.as < std::string > ())); }
#line 1208 "Parser.cpp"
    break;

  case 27: // expr: symbol ASSIGN expr
#line 119 "Parser.y"
                                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprAssign(yystack_[2].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > ())); }
#line 1214 "Parser.cpp"
    break;

  case 28: // expr: expr DOT symbol LP args RP
#line 120 "Parser.y"
                                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprDispatch(yystack_[5].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[3].value.as < NoneInitHolder<gcool::ast::Symbol> > (), std::move(yystack_[1].value.as < gcool::ast::ExprList > ()))); }
#line 1220 "Parser.cpp"
    break;

  case 29: // expr: expr AT symbol DOT symbol LP args RP
#line 121 "Parser.y"
                                            { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprStaticDispatch(yystack_[7].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[5].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[3].value.as < NoneInitHolder<gcool::ast::Symbol> > (), std::move(yystack_[1].value.as < gcool::ast::ExprList > ()))); }
#line 1226 "Parser.cpp"
    break;

  case 30: // expr: symbol LP args RP
#line 122 "Parser.y"
                                            { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprDispatch(context->ExprAlloc.allocExpr(ExprSelf()), yystack_[3].value.as < NoneInitHolder<gcool::ast::Symbol> > (), std::move(yystack_[1].value.as < gcool::ast::ExprList > ()))); }
#line 1232 "Parser.cpp"
    break;

  case 31: // expr: IF expr THEN expr ELSE expr FI
#line 123 "Parser.y"
                                            { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprCond(yystack_[5].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[3].value.as < NoneInitHolder<gcool::ast::Expr> > (), std::move(yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > ()))); }
#line 1238 "Parser.cpp"
    break;

  case 32: // expr: WHILE expr LOOP expr POOL
#line 124 "Parser.y"
                                        { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprLoop(yystack_[3].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > ())); }
#line 1244 "Parser.cpp"
    break;

  case 33: // expr: LB block_exprs RB
#line 125 "Parser.y"
                                        { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprBlock(std::move(yystack_[1].value.as < gcool::ast::ExprList > ()))); }
#line 1250 "Parser.cpp"
    break;

  case 34: // expr: LET let_init_exprs IN expr
#line 126 "Parser.y"
                                        { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprLet(std::move(yystack_[2].value.as < gcool::ast::LetInitList > ()), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > ())); }
#line 1256 "Parser.cpp"
    break;

  case 35: // expr: CASE expr OF case_branchs ESAC
#line 127 "Parser.y"
                                        { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprCase(yystack_[3].value.as < NoneInitHolder<gcool::ast::Expr> > (), std::move(yystack_[1].value.as < gcool::ast::CaseBranchList > ()))); }
#line 1262 "Parser.cpp"
    break;

  case 36: // expr: NEW symbol
#line 128 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprNew(yystack_[0].value.as < NoneInitHolder<gcool::ast::Symbol> > ())); }
#line 1268 "Parser.cpp"
    break;

  case 37: // expr: ISVOID expr
#line 129 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprArithU(yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithU::OP_ISVOID)); }
#line 1274 "Parser.cpp"
    break;

  case 38: // expr: NOT expr
#line 130 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprArithU(yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithU::OP_NOT)); }
#line 1280 "Parser.cpp"
    break;

  case 39: // expr: expr ADD expr
#line 131 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_ADD)); }
#line 1286 "Parser.cpp"
    break;

  case 40: // expr: expr SUB expr
#line 132 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_SUB)); }
#line 1292 "Parser.cpp"
    break;

  case 41: // expr: expr MUL expr
#line 133 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_MUL)); }
#line 1298 "Parser.cpp"
    break;

  case 42: // expr: expr DIV expr
#line 134 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_DIV)); }
#line 1304 "Parser.cpp"
    break;

  case 43: // expr: expr EQ expr
#line 135 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_EQ)); }
#line 1310 "Parser.cpp"
    break;

  case 44: // expr: expr LE expr
#line 136 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_LE)); }
#line 1316 "Parser.cpp"
    break;

  case 45: // expr: expr LT expr
#line 137 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_LT)); }
#line 1322 "Parser.cpp"
    break;

  case 46: // expr: expr GE expr
#line 138 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_GE)); }
#line 1328 "Parser.cpp"
    break;

  case 47: // expr: expr GT expr
#line 139 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_GT)); }
#line 1334 "Parser.cpp"
    break;

  case 48: // expr: LP expr RP
#line 140 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > (); }
#line 1340 "Parser.cpp"
    break;

  case 49: // expr: SELF
#line 141 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprSelf()); }
#line 1346 "Parser.cpp"
    break;

  case 50: // expr: NULL
#line 142 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(ExprNull()); }
#line 1352 "Parser.cpp"
    break;

  case 51: // args: %empty
#line 145 "Parser.y"
                { yylhs.value.as < gcool::ast::ExprList > () = ExprList{}; }
#line 1358 "Parser.cpp"
    break;

  case 52: // args: args_
#line 146 "Parser.y"
                { yylhs.value.as < gcool::ast::ExprList > () = std::move(yystack_[0].value.as < gcool::ast::ExprList > ()); }
#line 1364 "Parser.cpp"
    break;

  case 53: // args_: expr
#line 149 "Parser.y"
                        { yylhs.value.as < gcool::ast::ExprList > () = ExprList{}; yylhs.value.as < gcool::ast::ExprList > ().push_back(yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > ()); }
#line 1370 "Parser.cpp"
    break;

  case 54: // args_: args_ COMMA expr
#line 150 "Parser.y"
                        { yylhs.value.as < gcool::ast::ExprList > () = std::move(yystack_[2].value.as < gcool::ast::ExprList > ()); yylhs.value.as < gcool::ast::ExprList > ().push_back(yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > ()); }
#line 1376 "Parser.cpp"
    break;

  case 55: // block_exprs: expr SEMICOLON
#line 153 "Parser.y"
                                    { yylhs.value.as < gcool::ast::ExprList > () = ExprList{}; yylhs.value.as < gcool::ast::ExprList > ().push_back(yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > ()); }
#line 1382 "Parser.cpp"
    break;

  case 56: // block_exprs: block_exprs expr SEMICOLON
#line 154 "Parser.y"
                                    { yylhs.value.as < gcool::ast::ExprList > () = std::move(yystack_[2].value.as < gcool::ast::ExprList > ()); yylhs.value.as < gcool::ast::ExprList > ().push_back(yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > ()); }
#line 1388 "Parser.cpp"
    break;

  case 57: // let_init_exprs: formal optional_assign
#line 157 "Parser.y"
                                                   { yylhs.value.as < gcool::ast::LetInitList > () = LetInitList{}; yylhs.value.as < gcool::ast::LetInitList > ().push_back({yystack_[1].value.as < NoneInitHolder<gcool::ast::FormalDecl> > (), yystack_[0].value.as < gcool::ast::OptionalExpr > ()}); }
#line 1394 "Parser.cpp"
    break;

  case 58: // let_init_exprs: let_init_exprs COMMA formal optional_assign
#line 158 "Parser.y"
                                                   { yylhs.value.as < gcool::ast::LetInitList > () = std::move(yystack_[3].value.as < gcool::ast::LetInitList > ()); yylhs.value.as < gcool::ast::LetInitList > ().push_back({yystack_[1].value.as < NoneInitHolder<gcool::ast::FormalDecl> > (), yystack_[0].value.as < gcool::ast::OptionalExpr > ()}); }
#line 1400 "Parser.cpp"
    break;

  case 59: // case_branchs: symbol COLON symbol ARROW expr SEMICOLON
#line 161 "Parser.y"
                                                                { yylhs.value.as < gcool::ast::CaseBranchList > () = CaseBranchList{}; yylhs.value.as < gcool::ast::CaseBranchList > ().push_back({FormalDecl{yystack_[5].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[3].value.as < NoneInitHolder<gcool::ast::Symbol> > ()}, yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > ()}); }
#line 1406 "Parser.cpp"
    break;

  case 60: // case_branchs: case_branchs symbol COLON symbol ARROW expr SEMICOLON
#line 162 "Parser.y"
                                                                { yylhs.value.as < gcool::ast::CaseBranchList > () = std::move(yystack_[6].value.as < gcool::ast::CaseBranchList > ()); yylhs.value.as < gcool::ast::CaseBranchList > ().push_back({FormalDecl{yystack_[5].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[3].value.as < NoneInitHolder<gcool::ast::Symbol> > ()}, yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > ()}); }
#line 1412 "Parser.cpp"
    break;


#line 1416 "Parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char Parser::yypact_ninf_ = -102;

  const signed char Parser::yytable_ninf_ = -7;

  const short
  Parser::yypact_[] =
  {
    -102,    18,     2,  -102,  -102,   -15,    16,  -102,   -13,  -102,
      21,   -13,     5,  -102,  -102,   -25,  -102,   -20,    12,   -13,
     -13,   158,     0,     8,  -102,    19,     3,  -102,   158,  -102,
    -102,   158,   158,   -13,   158,   -13,   158,   158,   158,  -102,
    -102,  -102,  -102,  -102,     4,   382,  -102,    11,   -13,    78,
     222,   382,    12,   -11,   259,  -102,   382,   348,   276,   116,
     158,   158,   -13,   -13,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   -13,  -102,   158,   158,  -102,   158,   -13,
     -13,  -102,  -102,  -102,   294,   382,   382,    20,    13,    27,
      36,    -6,    -6,    -9,    -9,    67,    67,    67,    67,    67,
      28,   186,   240,   382,    12,    22,   -12,  -102,  -102,   158,
     158,   -13,   158,   158,  -102,  -102,   -13,  -102,    23,   382,
      31,    29,   365,   203,    41,   -13,  -102,   158,    34,  -102,
     158,    42,    37,  -102,   312,   158,  -102,  -102,   330,  -102
  };

  const signed char
  Parser::yydefact_[] =
  {
       3,     0,     2,     1,     7,     0,     0,     4,     0,    10,
       8,     0,     0,     9,    12,     0,     5,     0,    15,    17,
       0,     0,     0,     0,    19,     0,    18,    11,     0,    22,
      23,     0,     0,     0,     0,     0,     0,     0,     0,    49,
      50,    26,    24,    25,    21,    16,    13,     0,     0,     0,
       0,    37,    15,     0,     0,    36,    38,     0,     0,     0,
       0,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,     0,     0,    57,     0,     0,
       0,    48,    55,    33,     0,    27,    53,     0,    52,     0,
       0,    39,    40,    41,    42,    43,    44,    46,    45,    47,
       0,     0,     0,    34,    15,     0,     0,    56,    30,     0,
      51,     0,     0,     0,    32,    58,     0,    35,     0,    54,
       0,     0,     0,     0,     0,     0,    28,    51,     0,    31,
       0,     0,     0,    14,     0,     0,    29,    59,     0,    60
  };

  const signed char
  Parser::yypgoto_[] =
  {
    -102,  -102,  -102,  -102,  -102,  -102,    -8,   -18,  -102,   -48,
    -102,  -102,    10,  -101,  -102,  -102,  -102,  -102
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     1,     2,     5,     6,    12,    44,    18,    15,    22,
      25,    26,    86,    87,    88,    59,    53,   106
  };

  const short
  Parser::yytable_[] =
  {
      10,    24,    78,    13,    77,    -6,   117,    17,    16,   120,
      19,    23,    27,    62,    63,    52,    62,    63,     3,     8,
       9,    20,    66,    67,     7,    23,   132,    55,    60,    79,
      74,    45,     9,     9,    61,    11,    21,    14,    49,    46,
      23,    50,    51,    48,    54,     4,    56,    57,    58,    20,
      47,   108,    73,   109,    89,    90,   115,   110,   111,   127,
     112,   104,   126,   116,   125,   100,   130,   135,   136,    84,
      85,    23,   105,   133,    91,    92,    93,    94,    95,    96,
      97,    98,    99,    75,     0,   101,   102,     0,   103,    62,
      63,     0,     0,    64,    65,    66,    67,     0,   118,     0,
      62,    63,     0,   121,    64,    65,    66,    67,   124,     0,
       0,     0,    68,    69,    70,    71,    72,   131,     0,   119,
      28,     0,   122,   123,    29,    30,    31,     0,     0,     0,
       0,    32,    33,    34,     0,    35,     0,    36,     0,     0,
     134,     0,     0,     0,     0,   138,    37,     0,    38,    83,
       0,     0,     0,     0,     0,     0,     0,     0,    39,     0,
      40,     9,    28,    41,    42,    43,    29,    30,    31,     0,
       0,     0,     0,    32,    33,    34,     0,    35,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,    37,     0,
      38,     0,   113,     0,     0,     0,     0,     0,     0,     0,
      39,     0,    40,     9,     0,    41,    42,    43,    62,    63,
     129,     0,    64,    65,    66,    67,     0,     0,     0,     0,
      68,    69,    70,    71,    72,    62,    63,     0,     0,    64,
      65,    66,    67,    76,     0,     0,     0,    68,    69,    70,
      71,    72,     0,     0,    62,    63,     0,     0,    64,    65,
      66,    67,   114,     0,     0,     0,    68,    69,    70,    71,
      72,     0,    62,    63,     0,     0,    64,    65,    66,    67,
       0,     0,     0,     0,    68,    69,    70,    71,    72,    80,
       0,    62,    63,     0,     0,    64,    65,    66,    67,     0,
       0,     0,     0,    68,    69,    70,    71,    72,    62,    63,
       0,     0,    64,    65,    66,    67,     0,     0,     0,     0,
      68,    69,    70,    71,    72,    82,    62,    63,     0,     0,
      64,    65,    66,    67,     0,     0,     0,     0,    68,    69,
      70,    71,    72,   107,    62,    63,     0,     0,    64,    65,
      66,    67,     0,     0,     0,     0,    68,    69,    70,    71,
      72,   137,    62,    63,     0,     0,    64,    65,    66,    67,
       0,     0,     0,     0,    68,    69,    70,    71,    72,   139,
      62,    63,     0,     0,    64,    65,    66,    67,     0,    81,
       0,     0,    68,    69,    70,    71,    72,    62,    63,     0,
       0,    64,    65,    66,    67,     0,     0,     0,   128,    68,
      69,    70,    71,    72,    62,    63,     0,     0,    64,    65,
      66,    67,     0,     0,     0,     0,    68,    69,    70,    71,
      72
  };

  const short
  Parser::yycheck_[] =
  {
       8,    19,    13,    11,    52,     3,    18,    15,    33,   110,
      30,    19,    20,    22,    23,    33,    22,    23,     0,     3,
      45,    41,    28,    29,    39,    33,   127,    35,    24,    40,
      48,    21,    45,    45,    30,    14,    24,    32,    28,    39,
      48,    31,    32,    40,    34,    43,    36,    37,    38,    41,
      31,    31,    41,    40,    62,    63,   104,    30,    22,    30,
      32,    79,    31,    41,    41,    73,    25,    25,    31,    59,
      60,    79,    80,    39,    64,    65,    66,    67,    68,    69,
      70,    71,    72,     5,    -1,    75,    76,    -1,    78,    22,
      23,    -1,    -1,    26,    27,    28,    29,    -1,   106,    -1,
      22,    23,    -1,   111,    26,    27,    28,    29,   116,    -1,
      -1,    -1,    34,    35,    36,    37,    38,   125,    -1,   109,
       4,    -1,   112,   113,     8,     9,    10,    -1,    -1,    -1,
      -1,    15,    16,    17,    -1,    19,    -1,    21,    -1,    -1,
     130,    -1,    -1,    -1,    -1,   135,    30,    -1,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    -1,
      44,    45,     4,    47,    48,    49,     8,     9,    10,    -1,
      -1,    -1,    -1,    15,    16,    17,    -1,    19,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      32,    -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      42,    -1,    44,    45,    -1,    47,    48,    49,    22,    23,
       7,    -1,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    22,    23,    -1,    -1,    26,
      27,    28,    29,    11,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    -1,    -1,    22,    23,    -1,    -1,    26,    27,
      28,    29,    12,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    -1,    22,    23,    -1,    -1,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    20,
      -1,    22,    23,    -1,    -1,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    22,    23,
      -1,    -1,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    22,    23,    -1,    -1,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    34,    35,
      36,    37,    38,    39,    22,    23,    -1,    -1,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    22,    23,    -1,    -1,    26,    27,    28,    29,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,    39,
      22,    23,    -1,    -1,    26,    27,    28,    29,    -1,    31,
      -1,    -1,    34,    35,    36,    37,    38,    22,    23,    -1,
      -1,    26,    27,    28,    29,    -1,    -1,    -1,    33,    34,
      35,    36,    37,    38,    22,    23,    -1,    -1,    26,    27,
      28,    29,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    51,    52,     0,    43,    53,    54,    39,     3,    45,
      56,    14,    55,    56,    32,    58,    33,    56,    57,    30,
      41,    24,    59,    56,    57,    60,    61,    56,     4,     8,
       9,    10,    15,    16,    17,    19,    21,    30,    32,    42,
      44,    47,    48,    49,    56,    62,    39,    31,    40,    62,
      62,    62,    57,    66,    62,    56,    62,    62,    62,    65,
      24,    30,    22,    23,    26,    27,    28,    29,    34,    35,
      36,    37,    38,    41,    57,     5,    11,    59,    13,    40,
      20,    31,    39,    33,    62,    62,    62,    63,    64,    56,
      56,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      56,    62,    62,    62,    57,    56,    67,    39,    31,    40,
      30,    22,    32,     6,    12,    59,    41,    18,    56,    62,
      63,    56,    62,    62,    56,    41,    31,    30,    33,     7,
      25,    56,    63,    39,    62,    25,    31,    39,    62,    39
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    50,    51,    52,    52,    53,    54,    54,    55,    55,
      56,    57,    58,    58,    58,    59,    59,    60,    60,    61,
      61,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    63,    63,    64,    64,    65,    65,    66,    66,    67,
      67
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     0,     3,     7,     0,     1,     0,     2,
       1,     3,     0,     4,    11,     0,     2,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     6,     8,
       4,     7,     5,     3,     4,     5,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     0,     1,     1,     3,     2,     3,     2,     4,     6,
       7
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "CLASS", "IF", "THEN",
  "ELSE", "FI", "TRUE", "FALSE", "WHILE", "LOOP", "POOL", "IN", "INHERITS",
  "ISVOID", "LET", "CASE", "ESAC", "NEW", "OF", "NOT", "DOT", "AT",
  "ASSIGN", "ARROW", "ADD", "SUB", "MUL", "DIV", "LP", "RP", "LB", "RB",
  "EQ", "LE", "GE", "LT", "GT", "SEMICOLON", "COMMA", "COLON", "SELF",
  "FINAL", "NULL", "SYMBOL", "ERROR", "STR", "INT", "FLOAT", "$accept",
  "program", "class_seq", "class", "is_final", "inherits", "symbol",
  "formal", "features", "optional_assign", "params", "params_", "expr",
  "args", "args_", "block_exprs", "let_init_exprs", "case_branchs", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,    72,    72,    75,    76,    79,    82,    83,    86,    87,
      90,    93,    96,    97,    98,   101,   102,   105,   106,   109,
     110,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   145,   146,   149,   150,   153,   154,   157,   158,   161,
     162
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
    };
    // Last valid token kind.
    const int code_max = 304;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "Parser.y"
} // gcool
#line 1914 "Parser.cpp"

#line 167 "Parser.y"


void gcool::Parser::error(const std::string& s) {
    printf("Parser error: %s\n", s.data());
    context->HasParserError = true;
}
