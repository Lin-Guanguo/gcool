// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file Parser.h
 ** Define the gcool::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
// "%code requires" blocks.
#line 11 "Parser.y"

    #include <string>
    #include <optional>
    #include "gcool/AST/AST.h"
    #include "gcool/AST/Expr.h"
    typedef void* yyscan_t;

    template<typename T>
    class NoneInitHolder : public std::optional<T>{
    public:
        using std::optional<T>::optional;
        using std::optional<T>::operator =;
        operator T() {
            return this->value();
        }
    };

#line 67 "Parser.h"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif



#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

#line 5 "Parser.y"
namespace gcool {
#line 203 "Parser.h"




  /// A Bison parser.
  class Parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // class
      // features
      char dummy1[sizeof (NoneInitHolder<gcool::ast::Class>)];

      // expr
      char dummy2[sizeof (NoneInitHolder<gcool::ast::Expr>)];

      // formal
      char dummy3[sizeof (NoneInitHolder<gcool::ast::FormalDecl>)];

      // inherits
      // symbol
      char dummy4[sizeof (NoneInitHolder<gcool::ast::Symbol>)];

      // is_final
      char dummy5[sizeof (bool)];

      // SYMBOL
      // ERROR
      char dummy6[sizeof (const char*)];

      // FLOAT
      char dummy7[sizeof (double)];

      // case_branchs
      char dummy8[sizeof (gcool::ast::CaseBranchList)];

      // class_seq
      char dummy9[sizeof (gcool::ast::ClassList)];

      // args
      // args_
      // block_exprs
      char dummy10[sizeof (gcool::ast::ExprList)];

      // params
      // params_
      char dummy11[sizeof (gcool::ast::FormalList)];

      // let_init_exprs
      char dummy12[sizeof (gcool::ast::LetInitList)];

      // optional_assign
      char dummy13[sizeof (gcool::ast::OptionalExpr)];

      // INT
      char dummy14[sizeof (int)];

      // STR
      char dummy15[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;


    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        TK_YYEMPTY = -2,
    TK_YYEOF = 0,                  // "end of file"
    TK_YYerror = 256,              // error
    TK_YYUNDEF = 257,              // "invalid token"
    TK_CLASS = 258,                // CLASS
    TK_IF = 259,                   // IF
    TK_THEN = 260,                 // THEN
    TK_ELSE = 261,                 // ELSE
    TK_FI = 262,                   // FI
    TK_TRUE = 263,                 // TRUE
    TK_FALSE = 264,                // FALSE
    TK_WHILE = 265,                // WHILE
    TK_LOOP = 266,                 // LOOP
    TK_POOL = 267,                 // POOL
    TK_IN = 268,                   // IN
    TK_INHERITS = 269,             // INHERITS
    TK_ISVOID = 270,               // ISVOID
    TK_LET = 271,                  // LET
    TK_CASE = 272,                 // CASE
    TK_ESAC = 273,                 // ESAC
    TK_NEW = 274,                  // NEW
    TK_OF = 275,                   // OF
    TK_NOT = 276,                  // NOT
    TK_DOT = 277,                  // DOT
    TK_AT = 278,                   // AT
    TK_ASSIGN = 279,               // ASSIGN
    TK_ARROW = 280,                // ARROW
    TK_ADD = 281,                  // ADD
    TK_SUB = 282,                  // SUB
    TK_MUL = 283,                  // MUL
    TK_DIV = 284,                  // DIV
    TK_LP = 285,                   // LP
    TK_RP = 286,                   // RP
    TK_LB = 287,                   // LB
    TK_RB = 288,                   // RB
    TK_EQ = 289,                   // EQ
    TK_LE = 290,                   // LE
    TK_GE = 291,                   // GE
    TK_LT = 292,                   // LT
    TK_GT = 293,                   // GT
    TK_SEMICOLON = 294,            // SEMICOLON
    TK_COMMA = 295,                // COMMA
    TK_COLON = 296,                // COLON
    TK_SELF = 297,                 // SELF
    TK_FINAL = 298,                // FINAL
    TK_NULL = 299,                 // NULL
    TK_SYMBOL = 300,               // SYMBOL
    TK_ERROR = 301,                // ERROR
    TK_STR = 302,                  // STR
    TK_INT = 303,                  // INT
    TK_FLOAT = 304                 // FLOAT
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 50, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_CLASS = 3,                             // CLASS
        S_IF = 4,                                // IF
        S_THEN = 5,                              // THEN
        S_ELSE = 6,                              // ELSE
        S_FI = 7,                                // FI
        S_TRUE = 8,                              // TRUE
        S_FALSE = 9,                             // FALSE
        S_WHILE = 10,                            // WHILE
        S_LOOP = 11,                             // LOOP
        S_POOL = 12,                             // POOL
        S_IN = 13,                               // IN
        S_INHERITS = 14,                         // INHERITS
        S_ISVOID = 15,                           // ISVOID
        S_LET = 16,                              // LET
        S_CASE = 17,                             // CASE
        S_ESAC = 18,                             // ESAC
        S_NEW = 19,                              // NEW
        S_OF = 20,                               // OF
        S_NOT = 21,                              // NOT
        S_DOT = 22,                              // DOT
        S_AT = 23,                               // AT
        S_ASSIGN = 24,                           // ASSIGN
        S_ARROW = 25,                            // ARROW
        S_ADD = 26,                              // ADD
        S_SUB = 27,                              // SUB
        S_MUL = 28,                              // MUL
        S_DIV = 29,                              // DIV
        S_LP = 30,                               // LP
        S_RP = 31,                               // RP
        S_LB = 32,                               // LB
        S_RB = 33,                               // RB
        S_EQ = 34,                               // EQ
        S_LE = 35,                               // LE
        S_GE = 36,                               // GE
        S_LT = 37,                               // LT
        S_GT = 38,                               // GT
        S_SEMICOLON = 39,                        // SEMICOLON
        S_COMMA = 40,                            // COMMA
        S_COLON = 41,                            // COLON
        S_SELF = 42,                             // SELF
        S_FINAL = 43,                            // FINAL
        S_NULL = 44,                             // NULL
        S_SYMBOL = 45,                           // SYMBOL
        S_ERROR = 46,                            // ERROR
        S_STR = 47,                              // STR
        S_INT = 48,                              // INT
        S_FLOAT = 49,                            // FLOAT
        S_YYACCEPT = 50,                         // $accept
        S_program = 51,                          // program
        S_class_seq = 52,                        // class_seq
        S_class = 53,                            // class
        S_is_final = 54,                         // is_final
        S_inherits = 55,                         // inherits
        S_symbol = 56,                           // symbol
        S_formal = 57,                           // formal
        S_features = 58,                         // features
        S_optional_assign = 59,                  // optional_assign
        S_params = 60,                           // params
        S_params_ = 61,                          // params_
        S_expr = 62,                             // expr
        S_args = 63,                             // args
        S_args_ = 64,                            // args_
        S_block_exprs = 65,                      // block_exprs
        S_let_init_exprs = 66,                   // let_init_exprs
        S_case_branchs = 67                      // case_branchs
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
      {
        switch (this->kind ())
    {
      case symbol_kind::S_class: // class
      case symbol_kind::S_features: // features
        value.move< NoneInitHolder<gcool::ast::Class> > (std::move (that.value));
        break;

      case symbol_kind::S_expr: // expr
        value.move< NoneInitHolder<gcool::ast::Expr> > (std::move (that.value));
        break;

      case symbol_kind::S_formal: // formal
        value.move< NoneInitHolder<gcool::ast::FormalDecl> > (std::move (that.value));
        break;

      case symbol_kind::S_inherits: // inherits
      case symbol_kind::S_symbol: // symbol
        value.move< NoneInitHolder<gcool::ast::Symbol> > (std::move (that.value));
        break;

      case symbol_kind::S_is_final: // is_final
        value.move< bool > (std::move (that.value));
        break;

      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_ERROR: // ERROR
        value.move< const char* > (std::move (that.value));
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.move< double > (std::move (that.value));
        break;

      case symbol_kind::S_case_branchs: // case_branchs
        value.move< gcool::ast::CaseBranchList > (std::move (that.value));
        break;

      case symbol_kind::S_class_seq: // class_seq
        value.move< gcool::ast::ClassList > (std::move (that.value));
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_args_: // args_
      case symbol_kind::S_block_exprs: // block_exprs
        value.move< gcool::ast::ExprList > (std::move (that.value));
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_params_: // params_
        value.move< gcool::ast::FormalList > (std::move (that.value));
        break;

      case symbol_kind::S_let_init_exprs: // let_init_exprs
        value.move< gcool::ast::LetInitList > (std::move (that.value));
        break;

      case symbol_kind::S_optional_assign: // optional_assign
        value.move< gcool::ast::OptionalExpr > (std::move (that.value));
        break;

      case symbol_kind::S_INT: // INT
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_STR: // STR
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#else
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, NoneInitHolder<gcool::ast::Class>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const NoneInitHolder<gcool::ast::Class>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, NoneInitHolder<gcool::ast::Expr>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const NoneInitHolder<gcool::ast::Expr>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, NoneInitHolder<gcool::ast::FormalDecl>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const NoneInitHolder<gcool::ast::FormalDecl>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, NoneInitHolder<gcool::ast::Symbol>&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const NoneInitHolder<gcool::ast::Symbol>& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, bool&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const bool& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, const char*&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const const char*& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, double&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const double& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gcool::ast::CaseBranchList&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gcool::ast::CaseBranchList& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gcool::ast::ClassList&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gcool::ast::ClassList& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gcool::ast::ExprList&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gcool::ast::ExprList& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gcool::ast::FormalList&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gcool::ast::FormalList& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gcool::ast::LetInitList&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gcool::ast::LetInitList& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, gcool::ast::OptionalExpr&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const gcool::ast::OptionalExpr& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v)
        : Base (t)
        , value (v)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_class: // class
      case symbol_kind::S_features: // features
        value.template destroy< NoneInitHolder<gcool::ast::Class> > ();
        break;

      case symbol_kind::S_expr: // expr
        value.template destroy< NoneInitHolder<gcool::ast::Expr> > ();
        break;

      case symbol_kind::S_formal: // formal
        value.template destroy< NoneInitHolder<gcool::ast::FormalDecl> > ();
        break;

      case symbol_kind::S_inherits: // inherits
      case symbol_kind::S_symbol: // symbol
        value.template destroy< NoneInitHolder<gcool::ast::Symbol> > ();
        break;

      case symbol_kind::S_is_final: // is_final
        value.template destroy< bool > ();
        break;

      case symbol_kind::S_SYMBOL: // SYMBOL
      case symbol_kind::S_ERROR: // ERROR
        value.template destroy< const char* > ();
        break;

      case symbol_kind::S_FLOAT: // FLOAT
        value.template destroy< double > ();
        break;

      case symbol_kind::S_case_branchs: // case_branchs
        value.template destroy< gcool::ast::CaseBranchList > ();
        break;

      case symbol_kind::S_class_seq: // class_seq
        value.template destroy< gcool::ast::ClassList > ();
        break;

      case symbol_kind::S_args: // args
      case symbol_kind::S_args_: // args_
      case symbol_kind::S_block_exprs: // block_exprs
        value.template destroy< gcool::ast::ExprList > ();
        break;

      case symbol_kind::S_params: // params
      case symbol_kind::S_params_: // params_
        value.template destroy< gcool::ast::FormalList > ();
        break;

      case symbol_kind::S_let_init_exprs: // let_init_exprs
        value.template destroy< gcool::ast::LetInitList > ();
        break;

      case symbol_kind::S_optional_assign: // optional_assign
        value.template destroy< gcool::ast::OptionalExpr > ();
        break;

      case symbol_kind::S_INT: // INT
        value.template destroy< int > ();
        break;

      case symbol_kind::S_STR: // STR
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

#if YYDEBUG || 0
      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return Parser::symbol_name (this->kind ());
      }
#endif // #if YYDEBUG || 0


      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#else
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, const char* v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const const char*& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const double& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const int& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const std::string& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
    };

    /// Build a parser object.
    Parser (yyscan_t scannner_yyarg, gcool::ast::ASTContext* context_yyarg);
    virtual ~Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Parser (const Parser&) = delete;
    /// Non copyable.
    Parser& operator= (const Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

#if YYDEBUG || 0
    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);
#endif // #if YYDEBUG || 0


    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYEOF ()
      {
        return symbol_type (token::TK_YYEOF);
      }
#else
      static
      symbol_type
      make_YYEOF ()
      {
        return symbol_type (token::TK_YYEOF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::TK_YYerror);
      }
#else
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::TK_YYerror);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::TK_YYUNDEF);
      }
#else
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::TK_YYUNDEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLASS ()
      {
        return symbol_type (token::TK_CLASS);
      }
#else
      static
      symbol_type
      make_CLASS ()
      {
        return symbol_type (token::TK_CLASS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF ()
      {
        return symbol_type (token::TK_IF);
      }
#else
      static
      symbol_type
      make_IF ()
      {
        return symbol_type (token::TK_IF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THEN ()
      {
        return symbol_type (token::TK_THEN);
      }
#else
      static
      symbol_type
      make_THEN ()
      {
        return symbol_type (token::TK_THEN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE ()
      {
        return symbol_type (token::TK_ELSE);
      }
#else
      static
      symbol_type
      make_ELSE ()
      {
        return symbol_type (token::TK_ELSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FI ()
      {
        return symbol_type (token::TK_FI);
      }
#else
      static
      symbol_type
      make_FI ()
      {
        return symbol_type (token::TK_FI);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRUE ()
      {
        return symbol_type (token::TK_TRUE);
      }
#else
      static
      symbol_type
      make_TRUE ()
      {
        return symbol_type (token::TK_TRUE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FALSE ()
      {
        return symbol_type (token::TK_FALSE);
      }
#else
      static
      symbol_type
      make_FALSE ()
      {
        return symbol_type (token::TK_FALSE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE ()
      {
        return symbol_type (token::TK_WHILE);
      }
#else
      static
      symbol_type
      make_WHILE ()
      {
        return symbol_type (token::TK_WHILE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOOP ()
      {
        return symbol_type (token::TK_LOOP);
      }
#else
      static
      symbol_type
      make_LOOP ()
      {
        return symbol_type (token::TK_LOOP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POOL ()
      {
        return symbol_type (token::TK_POOL);
      }
#else
      static
      symbol_type
      make_POOL ()
      {
        return symbol_type (token::TK_POOL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IN ()
      {
        return symbol_type (token::TK_IN);
      }
#else
      static
      symbol_type
      make_IN ()
      {
        return symbol_type (token::TK_IN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INHERITS ()
      {
        return symbol_type (token::TK_INHERITS);
      }
#else
      static
      symbol_type
      make_INHERITS ()
      {
        return symbol_type (token::TK_INHERITS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ISVOID ()
      {
        return symbol_type (token::TK_ISVOID);
      }
#else
      static
      symbol_type
      make_ISVOID ()
      {
        return symbol_type (token::TK_ISVOID);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LET ()
      {
        return symbol_type (token::TK_LET);
      }
#else
      static
      symbol_type
      make_LET ()
      {
        return symbol_type (token::TK_LET);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CASE ()
      {
        return symbol_type (token::TK_CASE);
      }
#else
      static
      symbol_type
      make_CASE ()
      {
        return symbol_type (token::TK_CASE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ESAC ()
      {
        return symbol_type (token::TK_ESAC);
      }
#else
      static
      symbol_type
      make_ESAC ()
      {
        return symbol_type (token::TK_ESAC);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEW ()
      {
        return symbol_type (token::TK_NEW);
      }
#else
      static
      symbol_type
      make_NEW ()
      {
        return symbol_type (token::TK_NEW);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OF ()
      {
        return symbol_type (token::TK_OF);
      }
#else
      static
      symbol_type
      make_OF ()
      {
        return symbol_type (token::TK_OF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT ()
      {
        return symbol_type (token::TK_NOT);
      }
#else
      static
      symbol_type
      make_NOT ()
      {
        return symbol_type (token::TK_NOT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT ()
      {
        return symbol_type (token::TK_DOT);
      }
#else
      static
      symbol_type
      make_DOT ()
      {
        return symbol_type (token::TK_DOT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AT ()
      {
        return symbol_type (token::TK_AT);
      }
#else
      static
      symbol_type
      make_AT ()
      {
        return symbol_type (token::TK_AT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN ()
      {
        return symbol_type (token::TK_ASSIGN);
      }
#else
      static
      symbol_type
      make_ASSIGN ()
      {
        return symbol_type (token::TK_ASSIGN);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARROW ()
      {
        return symbol_type (token::TK_ARROW);
      }
#else
      static
      symbol_type
      make_ARROW ()
      {
        return symbol_type (token::TK_ARROW);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ADD ()
      {
        return symbol_type (token::TK_ADD);
      }
#else
      static
      symbol_type
      make_ADD ()
      {
        return symbol_type (token::TK_ADD);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB ()
      {
        return symbol_type (token::TK_SUB);
      }
#else
      static
      symbol_type
      make_SUB ()
      {
        return symbol_type (token::TK_SUB);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MUL ()
      {
        return symbol_type (token::TK_MUL);
      }
#else
      static
      symbol_type
      make_MUL ()
      {
        return symbol_type (token::TK_MUL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV ()
      {
        return symbol_type (token::TK_DIV);
      }
#else
      static
      symbol_type
      make_DIV ()
      {
        return symbol_type (token::TK_DIV);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LP ()
      {
        return symbol_type (token::TK_LP);
      }
#else
      static
      symbol_type
      make_LP ()
      {
        return symbol_type (token::TK_LP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RP ()
      {
        return symbol_type (token::TK_RP);
      }
#else
      static
      symbol_type
      make_RP ()
      {
        return symbol_type (token::TK_RP);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LB ()
      {
        return symbol_type (token::TK_LB);
      }
#else
      static
      symbol_type
      make_LB ()
      {
        return symbol_type (token::TK_LB);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RB ()
      {
        return symbol_type (token::TK_RB);
      }
#else
      static
      symbol_type
      make_RB ()
      {
        return symbol_type (token::TK_RB);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQ ()
      {
        return symbol_type (token::TK_EQ);
      }
#else
      static
      symbol_type
      make_EQ ()
      {
        return symbol_type (token::TK_EQ);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LE ()
      {
        return symbol_type (token::TK_LE);
      }
#else
      static
      symbol_type
      make_LE ()
      {
        return symbol_type (token::TK_LE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GE ()
      {
        return symbol_type (token::TK_GE);
      }
#else
      static
      symbol_type
      make_GE ()
      {
        return symbol_type (token::TK_GE);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LT ()
      {
        return symbol_type (token::TK_LT);
      }
#else
      static
      symbol_type
      make_LT ()
      {
        return symbol_type (token::TK_LT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GT ()
      {
        return symbol_type (token::TK_GT);
      }
#else
      static
      symbol_type
      make_GT ()
      {
        return symbol_type (token::TK_GT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOLON ()
      {
        return symbol_type (token::TK_SEMICOLON);
      }
#else
      static
      symbol_type
      make_SEMICOLON ()
      {
        return symbol_type (token::TK_SEMICOLON);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA ()
      {
        return symbol_type (token::TK_COMMA);
      }
#else
      static
      symbol_type
      make_COMMA ()
      {
        return symbol_type (token::TK_COMMA);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON ()
      {
        return symbol_type (token::TK_COLON);
      }
#else
      static
      symbol_type
      make_COLON ()
      {
        return symbol_type (token::TK_COLON);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SELF ()
      {
        return symbol_type (token::TK_SELF);
      }
#else
      static
      symbol_type
      make_SELF ()
      {
        return symbol_type (token::TK_SELF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FINAL ()
      {
        return symbol_type (token::TK_FINAL);
      }
#else
      static
      symbol_type
      make_FINAL ()
      {
        return symbol_type (token::TK_FINAL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NULL ()
      {
        return symbol_type (token::TK_NULL);
      }
#else
      static
      symbol_type
      make_NULL ()
      {
        return symbol_type (token::TK_NULL);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SYMBOL (const char* v)
      {
        return symbol_type (token::TK_SYMBOL, std::move (v));
      }
#else
      static
      symbol_type
      make_SYMBOL (const const char*& v)
      {
        return symbol_type (token::TK_SYMBOL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ERROR (const char* v)
      {
        return symbol_type (token::TK_ERROR, std::move (v));
      }
#else
      static
      symbol_type
      make_ERROR (const const char*& v)
      {
        return symbol_type (token::TK_ERROR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STR (std::string v)
      {
        return symbol_type (token::TK_STR, std::move (v));
      }
#else
      static
      symbol_type
      make_STR (const std::string& v)
      {
        return symbol_type (token::TK_STR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT (int v)
      {
        return symbol_type (token::TK_INT, std::move (v));
      }
#else
      static
      symbol_type
      make_INT (const int& v)
      {
        return symbol_type (token::TK_INT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT (double v)
      {
        return symbol_type (token::TK_FLOAT, std::move (v));
      }
#else
      static
      symbol_type
      make_FLOAT (const double& v)
      {
        return symbol_type (token::TK_FLOAT, v);
      }
#endif


  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Parser (const Parser&);
    /// Non copyable.
    Parser& operator= (const Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

#if YYDEBUG || 0
    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#endif // #if YYDEBUG || 0


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const unsigned char yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 420,     ///< Last index in yytable_.
      yynnts_ = 18,  ///< Number of nonterminal symbols.
      yyfinal_ = 3 ///< Termination state number.
    };


    // User arguments.
    yyscan_t scannner;
    gcool::ast::ASTContext* context;

  };


#line 5 "Parser.y"
} // gcool
#line 2263 "Parser.h"


// "%code provides" blocks.
#line 28 "Parser.y"

    int yylex(gcool::Parser::value_type* parserData, yyscan_t scannner);

#line 2271 "Parser.h"


#endif // !YY_YY_PARSER_H_INCLUDED
