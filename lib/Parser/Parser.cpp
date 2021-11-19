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
#line 71 "Parser.y"
                                    { context->Classes = std::move(yystack_[0].value.as < gcool::ast::ClassList > ()); }
#line 1036 "Parser.cpp"
    break;

  case 3: // class_seq: %empty
#line 74 "Parser.y"
                                    { yylhs.value.as < gcool::ast::ClassList > () = ClassList{}; }
#line 1042 "Parser.cpp"
    break;

  case 4: // class_seq: class_seq class SEMICOLON
#line 75 "Parser.y"
                                    { yylhs.value.as < gcool::ast::ClassList > () = std::move(yystack_[2].value.as < gcool::ast::ClassList > ()); yylhs.value.as < gcool::ast::ClassList > ().push_back(std::move(yystack_[1].value.as < NoneInitHolder<gcool::ast::Class> > ())); }
#line 1048 "Parser.cpp"
    break;

  case 5: // class: CLASS symbol inherits LB features RB
#line 78 "Parser.y"
                                            { yylhs.value.as < NoneInitHolder<gcool::ast::Class> > () = std::move(yystack_[1].value.as < NoneInitHolder<gcool::ast::Class> > ()); yylhs.value.as < NoneInitHolder<gcool::ast::Class> > ()->Inheirt = yystack_[3].value.as < NoneInitHolder<gcool::ast::Symbol> > (); yylhs.value.as < NoneInitHolder<gcool::ast::Class> > ()->Name = yystack_[4].value.as < NoneInitHolder<gcool::ast::Symbol> > (); }
#line 1054 "Parser.cpp"
    break;

  case 6: // inherits: %empty
#line 81 "Parser.y"
                        { yylhs.value.as < NoneInitHolder<gcool::ast::Symbol> > () = context->Symtbl.getObject(); }
#line 1060 "Parser.cpp"
    break;

  case 7: // inherits: INHERITS symbol
#line 82 "Parser.y"
                        { yylhs.value.as < NoneInitHolder<gcool::ast::Symbol> > () = yystack_[0].value.as < NoneInitHolder<gcool::ast::Symbol> > (); }
#line 1066 "Parser.cpp"
    break;

  case 8: // symbol: SYMBOL
#line 85 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Symbol> > () = context->Symtbl.get(yystack_[0].value.as < const char* > ()); }
#line 1072 "Parser.cpp"
    break;

  case 9: // formal: symbol COLON symbol
#line 88 "Parser.y"
                            { yylhs.value.as < NoneInitHolder<gcool::ast::FormalDecl> > () = FormalDecl{yystack_[2].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Symbol> > ()}; }
#line 1078 "Parser.cpp"
    break;

  case 10: // features: %empty
#line 91 "Parser.y"
            { yylhs.value.as < NoneInitHolder<gcool::ast::Class> > () = Class{ Symbol::EmptySymbol, Symbol::EmptySymbol }; }
#line 1084 "Parser.cpp"
    break;

  case 11: // features: features formal optional_assign SEMICOLON
#line 92 "Parser.y"
                                                 { yylhs.value.as < NoneInitHolder<gcool::ast::Class> > () = std::move(yystack_[3].value.as < NoneInitHolder<gcool::ast::Class> > ()); yylhs.value.as < NoneInitHolder<gcool::ast::Class> > ()->Attrs.push_back(AttrFeature{yystack_[2].value.as < NoneInitHolder<gcool::ast::FormalDecl> > (), yystack_[1].value.as < gcool::ast::OptionalExpr > ()}); }
#line 1090 "Parser.cpp"
    break;

  case 12: // features: features symbol LP params RP COLON symbol LB expr RB SEMICOLON
#line 93 "Parser.y"
                                                                        { yylhs.value.as < NoneInitHolder<gcool::ast::Class> > () = std::move(yystack_[10].value.as < NoneInitHolder<gcool::ast::Class> > ()); yylhs.value.as < NoneInitHolder<gcool::ast::Class> > ()->Methods.push_back(MethodFeature{yystack_[9].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[4].value.as < NoneInitHolder<gcool::ast::Symbol> > (), std::move(yystack_[7].value.as < gcool::ast::FormalList > ()), yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > ()}); }
#line 1096 "Parser.cpp"
    break;

  case 13: // optional_assign: %empty
#line 96 "Parser.y"
                   { yylhs.value.as < gcool::ast::OptionalExpr > () = OptionalExpr{}; }
#line 1102 "Parser.cpp"
    break;

  case 14: // optional_assign: ASSIGN expr
#line 97 "Parser.y"
                   { yylhs.value.as < gcool::ast::OptionalExpr > () = yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (); }
#line 1108 "Parser.cpp"
    break;

  case 15: // params: %empty
#line 100 "Parser.y"
                { yylhs.value.as < gcool::ast::FormalList > () = FormalList{}; }
#line 1114 "Parser.cpp"
    break;

  case 16: // params: params_
#line 101 "Parser.y"
                { yylhs.value.as < gcool::ast::FormalList > () = std::move(yystack_[0].value.as < gcool::ast::FormalList > ()); }
#line 1120 "Parser.cpp"
    break;

  case 17: // params_: formal
#line 104 "Parser.y"
                            { yylhs.value.as < gcool::ast::FormalList > () = FormalList{}; yylhs.value.as < gcool::ast::FormalList > ().push_back(yystack_[0].value.as < NoneInitHolder<gcool::ast::FormalDecl> > ()); }
#line 1126 "Parser.cpp"
    break;

  case 18: // params_: params_ COMMA formal
#line 105 "Parser.y"
                            { yylhs.value.as < gcool::ast::FormalList > () = std::move(yystack_[2].value.as < gcool::ast::FormalList > ()); yylhs.value.as < gcool::ast::FormalList > ().push_back(yystack_[0].value.as < NoneInitHolder<gcool::ast::FormalDecl> > ()); }
#line 1132 "Parser.cpp"
    break;

  case 19: // expr: symbol
#line 108 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprSymbol(yystack_[0].value.as < NoneInitHolder<gcool::ast::Symbol> > ())); }
#line 1138 "Parser.cpp"
    break;

  case 20: // expr: TRUE
#line 109 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprBool(true)); }
#line 1144 "Parser.cpp"
    break;

  case 21: // expr: FALSE
#line 110 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprBool(false)); }
#line 1150 "Parser.cpp"
    break;

  case 22: // expr: INT
#line 111 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprInt(yystack_[0].value.as < int > ())); }
#line 1156 "Parser.cpp"
    break;

  case 23: // expr: FLOAT
#line 112 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprFloat(yystack_[0].value.as < double > ())); }
#line 1162 "Parser.cpp"
    break;

  case 24: // expr: STR
#line 113 "Parser.y"
                { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprString(yystack_[0].value.as < std::string > ())); }
#line 1168 "Parser.cpp"
    break;

  case 25: // expr: symbol ASSIGN expr
#line 114 "Parser.y"
                                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprAssign(yystack_[2].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > ())); }
#line 1174 "Parser.cpp"
    break;

  case 26: // expr: expr DOT symbol LP args RP
#line 115 "Parser.y"
                                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprDispatch(yystack_[5].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[3].value.as < NoneInitHolder<gcool::ast::Symbol> > (), std::move(yystack_[1].value.as < gcool::ast::ExprList > ()))); }
#line 1180 "Parser.cpp"
    break;

  case 27: // expr: expr AT symbol DOT symbol LP args RP
#line 116 "Parser.y"
                                            { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprStaticDispatch(yystack_[7].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[5].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[3].value.as < NoneInitHolder<gcool::ast::Symbol> > (), std::move(yystack_[1].value.as < gcool::ast::ExprList > ()))); }
#line 1186 "Parser.cpp"
    break;

  case 28: // expr: symbol LP args RP
#line 117 "Parser.y"
                                            { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprDispatch(context->ExprAlloc.allocExpr(new ExprSelf()), yystack_[3].value.as < NoneInitHolder<gcool::ast::Symbol> > (), std::move(yystack_[1].value.as < gcool::ast::ExprList > ()))); }
#line 1192 "Parser.cpp"
    break;

  case 29: // expr: IF expr THEN expr ELSE expr FI
#line 118 "Parser.y"
                                            { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprCond(yystack_[5].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[3].value.as < NoneInitHolder<gcool::ast::Expr> > (), std::move(yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > ()))); }
#line 1198 "Parser.cpp"
    break;

  case 30: // expr: WHILE expr LOOP expr POOL
#line 119 "Parser.y"
                                        { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprLoop(yystack_[3].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > ())); }
#line 1204 "Parser.cpp"
    break;

  case 31: // expr: LB block_exprs RB
#line 120 "Parser.y"
                                        { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprBlock(std::move(yystack_[1].value.as < gcool::ast::ExprList > ()))); }
#line 1210 "Parser.cpp"
    break;

  case 32: // expr: LET let_init_exprs IN expr
#line 121 "Parser.y"
                                        { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprLet(std::move(yystack_[2].value.as < gcool::ast::LetInitList > ()), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > ())); }
#line 1216 "Parser.cpp"
    break;

  case 33: // expr: CASE expr OF case_branchs ESAC
#line 122 "Parser.y"
                                        { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprCase(yystack_[3].value.as < NoneInitHolder<gcool::ast::Expr> > (), std::move(yystack_[1].value.as < gcool::ast::CaseBranchList > ()))); }
#line 1222 "Parser.cpp"
    break;

  case 34: // expr: NEW symbol
#line 123 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprNew(yystack_[0].value.as < NoneInitHolder<gcool::ast::Symbol> > ())); }
#line 1228 "Parser.cpp"
    break;

  case 35: // expr: ISVOID expr
#line 124 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprArithU(yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithU::OP_ISVOID)); }
#line 1234 "Parser.cpp"
    break;

  case 36: // expr: NOT expr
#line 125 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprArithU(yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithU::OP_NOT)); }
#line 1240 "Parser.cpp"
    break;

  case 37: // expr: expr ADD expr
#line 126 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_ADD)); }
#line 1246 "Parser.cpp"
    break;

  case 38: // expr: expr SUB expr
#line 127 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_SUB)); }
#line 1252 "Parser.cpp"
    break;

  case 39: // expr: expr MUL expr
#line 128 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_MUL)); }
#line 1258 "Parser.cpp"
    break;

  case 40: // expr: expr DIV expr
#line 129 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_DIV)); }
#line 1264 "Parser.cpp"
    break;

  case 41: // expr: expr EQ expr
#line 130 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_EQ)); }
#line 1270 "Parser.cpp"
    break;

  case 42: // expr: expr LE expr
#line 131 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_LE)); }
#line 1276 "Parser.cpp"
    break;

  case 43: // expr: expr LT expr
#line 132 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_LT)); }
#line 1282 "Parser.cpp"
    break;

  case 44: // expr: expr GE expr
#line 133 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_GE)); }
#line 1288 "Parser.cpp"
    break;

  case 45: // expr: expr GT expr
#line 134 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprArithB(yystack_[2].value.as < NoneInitHolder<gcool::ast::Expr> > (), yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > (), ExprArithB::OP_GT)); }
#line 1294 "Parser.cpp"
    break;

  case 46: // expr: LP expr RP
#line 135 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > (); }
#line 1300 "Parser.cpp"
    break;

  case 47: // expr: SELF
#line 136 "Parser.y"
                    { yylhs.value.as < NoneInitHolder<gcool::ast::Expr> > () = context->ExprAlloc.allocExpr(new ExprSelf()); }
#line 1306 "Parser.cpp"
    break;

  case 48: // args: %empty
#line 139 "Parser.y"
                { yylhs.value.as < gcool::ast::ExprList > () = ExprList{}; }
#line 1312 "Parser.cpp"
    break;

  case 49: // args: args_
#line 140 "Parser.y"
                { yylhs.value.as < gcool::ast::ExprList > () = std::move(yystack_[0].value.as < gcool::ast::ExprList > ()); }
#line 1318 "Parser.cpp"
    break;

  case 50: // args_: expr
#line 143 "Parser.y"
                        { yylhs.value.as < gcool::ast::ExprList > () = ExprList{}; yylhs.value.as < gcool::ast::ExprList > ().push_back(yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > ()); }
#line 1324 "Parser.cpp"
    break;

  case 51: // args_: args_ COMMA expr
#line 144 "Parser.y"
                        { yylhs.value.as < gcool::ast::ExprList > () = std::move(yystack_[2].value.as < gcool::ast::ExprList > ()); yylhs.value.as < gcool::ast::ExprList > ().push_back(yystack_[0].value.as < NoneInitHolder<gcool::ast::Expr> > ()); }
#line 1330 "Parser.cpp"
    break;

  case 52: // block_exprs: expr SEMICOLON
#line 147 "Parser.y"
                                    { yylhs.value.as < gcool::ast::ExprList > () = ExprList{}; yylhs.value.as < gcool::ast::ExprList > ().push_back(yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > ()); }
#line 1336 "Parser.cpp"
    break;

  case 53: // block_exprs: block_exprs expr SEMICOLON
#line 148 "Parser.y"
                                    { yylhs.value.as < gcool::ast::ExprList > () = std::move(yystack_[2].value.as < gcool::ast::ExprList > ()); yylhs.value.as < gcool::ast::ExprList > ().push_back(yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > ()); }
#line 1342 "Parser.cpp"
    break;

  case 54: // let_init_exprs: formal optional_assign
#line 151 "Parser.y"
                                                   { yylhs.value.as < gcool::ast::LetInitList > () = LetInitList{}; yylhs.value.as < gcool::ast::LetInitList > ().push_back({yystack_[1].value.as < NoneInitHolder<gcool::ast::FormalDecl> > (), yystack_[0].value.as < gcool::ast::OptionalExpr > ()}); }
#line 1348 "Parser.cpp"
    break;

  case 55: // let_init_exprs: let_init_exprs COMMA formal optional_assign
#line 152 "Parser.y"
                                                   { yylhs.value.as < gcool::ast::LetInitList > () = std::move(yystack_[3].value.as < gcool::ast::LetInitList > ()); yylhs.value.as < gcool::ast::LetInitList > ().push_back({yystack_[1].value.as < NoneInitHolder<gcool::ast::FormalDecl> > (), yystack_[0].value.as < gcool::ast::OptionalExpr > ()}); }
#line 1354 "Parser.cpp"
    break;

  case 56: // case_branchs: symbol COLON symbol ARROW expr SEMICOLON
#line 155 "Parser.y"
                                                                { yylhs.value.as < gcool::ast::CaseBranchList > () = CaseBranchList{}; yylhs.value.as < gcool::ast::CaseBranchList > ().push_back({yystack_[5].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[3].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > ()}); }
#line 1360 "Parser.cpp"
    break;

  case 57: // case_branchs: case_branchs symbol COLON symbol ARROW expr SEMICOLON
#line 156 "Parser.y"
                                                                { yylhs.value.as < gcool::ast::CaseBranchList > () = std::move(yystack_[6].value.as < gcool::ast::CaseBranchList > ()); yylhs.value.as < gcool::ast::CaseBranchList > ().push_back({yystack_[5].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[3].value.as < NoneInitHolder<gcool::ast::Symbol> > (), yystack_[1].value.as < NoneInitHolder<gcool::ast::Expr> > ()}); }
#line 1366 "Parser.cpp"
    break;


#line 1370 "Parser.cpp"

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









  const signed char Parser::yypact_ninf_ = -105;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
    -105,     7,    12,  -105,   -33,   -20,  -105,    10,  -105,   -33,
      -7,  -105,  -105,   -22,  -105,   -24,     2,   -33,   -33,   156,
     -11,    -6,  -105,     3,    -3,  -105,   156,  -105,  -105,   156,
     156,   -33,   156,   -33,   156,   156,   156,  -105,  -105,  -105,
    -105,   -12,   379,  -105,    -5,   -33,    79,   219,   379,     2,
      -9,   256,  -105,   379,   345,   273,   116,   156,   156,   -33,
     -33,   156,   156,   156,   156,   156,   156,   156,   156,   156,
     -33,  -105,   156,   156,  -105,   156,   -33,   -33,  -105,  -105,
    -105,   291,   379,   379,     9,    -2,    14,    24,    67,    67,
       0,     0,    36,    36,    36,    36,    36,    18,   183,   237,
     379,     2,    11,   -10,  -105,  -105,   156,   156,   -33,   156,
     156,  -105,  -105,   -33,  -105,    16,   379,    20,    30,   362,
     200,    29,   -33,  -105,   156,    28,  -105,   156,    43,    40,
    -105,   309,   156,  -105,  -105,   327,  -105
  };

  const signed char
  Parser::yydefact_[] =
  {
       3,     0,     2,     1,     0,     0,     8,     6,     4,     0,
       0,     7,    10,     0,     5,     0,    13,    15,     0,     0,
       0,     0,    17,     0,    16,     9,     0,    20,    21,     0,
       0,     0,     0,     0,     0,     0,     0,    47,    24,    22,
      23,    19,    14,    11,     0,     0,     0,     0,    35,    13,
       0,     0,    34,    36,     0,     0,     0,     0,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,     0,     0,    54,     0,     0,     0,    46,    52,
      31,     0,    25,    50,     0,    49,     0,     0,    37,    38,
      39,    40,    41,    42,    44,    43,    45,     0,     0,     0,
      32,    13,     0,     0,    53,    28,     0,    48,     0,     0,
       0,    30,    55,     0,    33,     0,    51,     0,     0,     0,
       0,     0,     0,    26,    48,     0,    29,     0,     0,     0,
      12,     0,     0,    27,    56,     0,    57
  };

  const signed char
  Parser::yypgoto_[] =
  {
    -105,  -105,  -105,  -105,  -105,    -4,   -15,  -105,   -48,  -105,
    -105,    13,  -104,  -105,  -105,  -105,  -105
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     1,     2,     5,    10,    41,    16,    13,    20,    23,
      24,    83,    84,    85,    56,    50,   103
  };

  const unsigned char
  Parser::yytable_[] =
  {
       7,    74,    22,   117,    75,    11,    17,     3,   114,    15,
       6,    14,    57,    21,    25,     4,    49,    18,    58,     8,
     129,     6,    59,    60,     9,    12,    19,    21,    43,    52,
      71,    76,    42,     6,    44,    18,    70,    45,   106,    46,
     105,    21,    47,    48,   107,    51,   108,    53,    54,    55,
     109,   123,   113,   112,   127,    86,    87,   122,    59,    60,
     124,   101,    61,    62,    63,    64,    97,   130,   132,    81,
      82,   133,    21,   102,    88,    89,    90,    91,    92,    93,
      94,    95,    96,     0,    72,    98,    99,     0,   100,    59,
      60,     0,     0,     0,     0,    63,    64,     0,     0,   115,
       0,    59,    60,     0,   118,    61,    62,    63,    64,   121,
       0,     0,     0,    65,    66,    67,    68,    69,   128,   116,
      26,     0,   119,   120,    27,    28,    29,     0,     0,     0,
       0,    30,    31,    32,     0,    33,     0,    34,     0,     0,
     131,     0,     0,     0,     0,   135,    35,     0,    36,    80,
       0,     0,     0,     0,     0,     0,     0,     0,    37,     6,
      26,    38,    39,    40,    27,    28,    29,     0,     0,     0,
       0,    30,    31,    32,     0,    33,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,    35,     0,    36,   110,
       0,     0,     0,     0,     0,     0,     0,     0,    37,     6,
       0,    38,    39,    40,     0,    59,    60,   126,     0,    61,
      62,    63,    64,     0,     0,     0,     0,    65,    66,    67,
      68,    69,    59,    60,     0,     0,    61,    62,    63,    64,
      73,     0,     0,     0,    65,    66,    67,    68,    69,     0,
       0,    59,    60,     0,     0,    61,    62,    63,    64,   111,
       0,     0,     0,    65,    66,    67,    68,    69,     0,    59,
      60,     0,     0,    61,    62,    63,    64,     0,     0,     0,
       0,    65,    66,    67,    68,    69,    77,     0,    59,    60,
       0,     0,    61,    62,    63,    64,     0,     0,     0,     0,
      65,    66,    67,    68,    69,    59,    60,     0,     0,    61,
      62,    63,    64,     0,     0,     0,     0,    65,    66,    67,
      68,    69,    79,    59,    60,     0,     0,    61,    62,    63,
      64,     0,     0,     0,     0,    65,    66,    67,    68,    69,
     104,    59,    60,     0,     0,    61,    62,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69,   134,    59,
      60,     0,     0,    61,    62,    63,    64,     0,     0,     0,
       0,    65,    66,    67,    68,    69,   136,    59,    60,     0,
       0,    61,    62,    63,    64,     0,    78,     0,     0,    65,
      66,    67,    68,    69,    59,    60,     0,     0,    61,    62,
      63,    64,     0,     0,     0,   125,    65,    66,    67,    68,
      69,    59,    60,     0,     0,    61,    62,    63,    64,     0,
       0,     0,     0,    65,    66,    67,    68,    69
  };

  const short
  Parser::yycheck_[] =
  {
       4,    49,    17,   107,    13,     9,    30,     0,    18,    13,
      43,    33,    24,    17,    18,     3,    31,    41,    30,    39,
     124,    43,    22,    23,    14,    32,    24,    31,    39,    33,
      45,    40,    19,    43,    31,    41,    41,    40,    40,    26,
      31,    45,    29,    30,    30,    32,    22,    34,    35,    36,
      32,    31,    41,   101,    25,    59,    60,    41,    22,    23,
      30,    76,    26,    27,    28,    29,    70,    39,    25,    56,
      57,    31,    76,    77,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    -1,     5,    72,    73,    -1,    75,    22,
      23,    -1,    -1,    -1,    -1,    28,    29,    -1,    -1,   103,
      -1,    22,    23,    -1,   108,    26,    27,    28,    29,   113,
      -1,    -1,    -1,    34,    35,    36,    37,    38,   122,   106,
       4,    -1,   109,   110,     8,     9,    10,    -1,    -1,    -1,
      -1,    15,    16,    17,    -1,    19,    -1,    21,    -1,    -1,
     127,    -1,    -1,    -1,    -1,   132,    30,    -1,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
       4,    45,    46,    47,     8,     9,    10,    -1,    -1,    -1,
      -1,    15,    16,    17,    -1,    19,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
      -1,    45,    46,    47,    -1,    22,    23,     7,    -1,    26,
      27,    28,    29,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    22,    23,    -1,    -1,    26,    27,    28,    29,
      11,    -1,    -1,    -1,    34,    35,    36,    37,    38,    -1,
      -1,    22,    23,    -1,    -1,    26,    27,    28,    29,    12,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    -1,    22,
      23,    -1,    -1,    26,    27,    28,    29,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    20,    -1,    22,    23,
      -1,    -1,    26,    27,    28,    29,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    22,    23,    -1,    -1,    26,
      27,    28,    29,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    39,    22,    23,    -1,    -1,    26,    27,    28,
      29,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    38,
      39,    22,    23,    -1,    -1,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38,    39,    22,
      23,    -1,    -1,    26,    27,    28,    29,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    22,    23,    -1,
      -1,    26,    27,    28,    29,    -1,    31,    -1,    -1,    34,
      35,    36,    37,    38,    22,    23,    -1,    -1,    26,    27,
      28,    29,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    22,    23,    -1,    -1,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    38
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    49,    50,     0,     3,    51,    43,    53,    39,    14,
      52,    53,    32,    55,    33,    53,    54,    30,    41,    24,
      56,    53,    54,    57,    58,    53,     4,     8,     9,    10,
      15,    16,    17,    19,    21,    30,    32,    42,    45,    46,
      47,    53,    59,    39,    31,    40,    59,    59,    59,    54,
      63,    59,    53,    59,    59,    59,    62,    24,    30,    22,
      23,    26,    27,    28,    29,    34,    35,    36,    37,    38,
      41,    54,     5,    11,    56,    13,    40,    20,    31,    39,
      33,    59,    59,    59,    60,    61,    53,    53,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    53,    59,    59,
      59,    54,    53,    64,    39,    31,    40,    30,    22,    32,
       6,    12,    56,    41,    18,    53,    59,    60,    53,    59,
      59,    53,    41,    31,    30,    33,     7,    25,    53,    60,
      39,    59,    25,    31,    39,    59,    39
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    48,    49,    50,    50,    51,    52,    52,    53,    54,
      55,    55,    55,    56,    56,    57,    57,    58,    58,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    60,    60,
      61,    61,    62,    62,    63,    63,    64,    64
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     0,     3,     6,     0,     2,     1,     3,
       0,     4,    11,     0,     2,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     6,     8,     4,     7,
       5,     3,     4,     5,     2,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     0,     1,
       1,     3,     2,     3,     2,     4,     6,     7
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
  "SYMBOL", "ERROR", "STR", "INT", "FLOAT", "$accept", "program",
  "class_seq", "class", "inherits", "symbol", "formal", "features",
  "optional_assign", "params", "params_", "expr", "args", "args_",
  "block_exprs", "let_init_exprs", "case_branchs", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,    71,    71,    74,    75,    78,    81,    82,    85,    88,
      91,    92,    93,    96,    97,   100,   101,   104,   105,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   139,   140,
     143,   144,   147,   148,   151,   152,   155,   156
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
      45,    46,    47
    };
    // Last valid token kind.
    const int code_max = 302;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "Parser.y"
} // gcool
#line 1863 "Parser.cpp"

#line 161 "Parser.y"


void gcool::Parser::error(const std::string& s) {
    printf("error: %s", s.data());
}
