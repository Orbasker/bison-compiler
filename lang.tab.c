/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "lang.y"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include "lang.tab.h"

using namespace std;

typedef struct symrec {
    char *name;
    int type;
    struct symrec *next;
} symrec;

symrec *sym_table = NULL;

symrec *putsym(const char *, int);
symrec *getsym(const char *);

void yyerror(const char *s) {
    extern int yylineno;
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}

FILE *outfile;
FILE *debugfile;
char* declarations;
char* statementsL;


extern FILE *yyin;
extern int yylex();
extern int yylineno;
extern int yydebug;

int isSetOrCollection(const char* var);
#define DEBUG_PRINT(msg, ...) fprintf(debugfile, "DEBUG: " msg "\n", ##__VA_ARGS__)

#line 113 "lang.tab.c"

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

#include "lang.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_STRING_LITERAL = 4,             /* STRING_LITERAL  */
  YYSYMBOL_IDENTIFIER = 5,                 /* IDENTIFIER  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_STR = 7,                        /* STR  */
  YYSYMBOL_SET = 8,                        /* SET  */
  YYSYMBOL_COLLECTION = 9,                 /* COLLECTION  */
  YYSYMBOL_INPUT = 10,                     /* INPUT  */
  YYSYMBOL_OUTPUT = 11,                    /* OUTPUT  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_FOR = 15,                       /* FOR  */
  YYSYMBOL_EQ = 16,                        /* EQ  */
  YYSYMBOL_NEQ = 17,                       /* NEQ  */
  YYSYMBOL_LE = 18,                        /* LE  */
  YYSYMBOL_GE = 19,                        /* GE  */
  YYSYMBOL_LT = 20,                        /* LT  */
  YYSYMBOL_GT = 21,                        /* GT  */
  YYSYMBOL_ASSIGN = 22,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 23,                      /* PLUS  */
  YYSYMBOL_MINUS = 24,                     /* MINUS  */
  YYSYMBOL_MUL = 25,                       /* MUL  */
  YYSYMBOL_DIV = 26,                       /* DIV  */
  YYSYMBOL_INTERSECT = 27,                 /* INTERSECT  */
  YYSYMBOL_UNION = 28,                     /* UNION  */
  YYSYMBOL_LPAREN = 29,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 30,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 31,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 32,                    /* RBRACE  */
  YYSYMBOL_SEMICOLON = 33,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 34,                     /* COMMA  */
  YYSYMBOL_COLON = 35,                     /* COLON  */
  YYSYMBOL_LBRACKET = 36,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 37,                  /* RBRACKET  */
  YYSYMBOL_LOWER_THAN_ELSE = 38,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_program = 40,                   /* program  */
  YYSYMBOL_declaration = 41,               /* declaration  */
  YYSYMBOL_identifiers = 42,               /* identifiers  */
  YYSYMBOL_identifier = 43,                /* identifier  */
  YYSYMBOL_statements = 44,                /* statements  */
  YYSYMBOL_statement = 45,                 /* statement  */
  YYSYMBOL_expression = 46,                /* expression  */
  YYSYMBOL_condition = 47,                 /* condition  */
  YYSYMBOL_set_literal = 48,               /* set_literal  */
  YYSYMBOL_number_list = 49,               /* number_list  */
  YYSYMBOL_col_literal = 50,               /* col_literal  */
  YYSYMBOL_string_list = 51                /* string_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
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


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   348

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    73,    73,    77,    88,    97,   106,   120,   127,   137,
     149,   150,   172,   178,   182,   186,   191,   196,   212,   237,
     243,   249,   256,   276,   283,   290,   295,   312,   328,   344,
     391,   392,   393,   394,   395,   404,   422,   436,   444,   452,
     460,   468,   476,   486,   492,   500,   507,   514,   521,   528,
     538,   545,   546,   552,   556,   560,   564,   568
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER",
  "STRING_LITERAL", "IDENTIFIER", "INT", "STR", "SET", "COLLECTION",
  "INPUT", "OUTPUT", "IF", "ELSE", "WHILE", "FOR", "EQ", "NEQ", "LE", "GE",
  "LT", "GT", "ASSIGN", "PLUS", "MINUS", "MUL", "DIV", "INTERSECT",
  "UNION", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "SEMICOLON", "COMMA",
  "COLON", "LBRACKET", "RBRACKET", "LOWER_THAN_ELSE", "$accept", "program",
  "declaration", "identifiers", "identifier", "statements", "statement",
  "expression", "condition", "set_literal", "number_list", "col_literal",
  "string_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-90)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-44)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -90,    55,   219,   -90,   -90,   -90,   -90,    59,    59,    59,
      59,    82,    20,    60,    90,    68,    90,     5,   100,   -90,
      89,   -90,   293,   -90,   -90,     0,   -90,    74,    84,    91,
      59,   253,    87,    90,     5,   -20,   287,   107,    69,   129,
      -7,   -90,   -90,    73,    41,   -90,    19,    90,    90,    90,
      90,    90,    90,    90,   -90,   -90,    59,   -90,   -90,   -90,
     122,   -90,   304,   -90,    -8,    85,    90,    90,    90,    90,
      90,    90,    90,   -90,   127,   128,   -90,   -90,   -90,   156,
     161,   -90,   315,    17,    17,   131,   131,   -90,   -90,   -90,
     -90,   -90,   219,   232,    35,    35,    35,    35,    35,    35,
      35,   125,    93,    59,   -90,   -90,   -90,   -90,     5,   152,
     -90,   136,   141,   142,   138,   219,   219,   137,   219,   160,
     -90,   -90,   -90,   -90,   266,   172,     5,   -90,   -90,   185,
     -90
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      10,     0,     2,     1,    30,    31,     9,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    10,    53,    13,
      34,    11,     0,    32,    33,     0,     7,     0,     0,     0,
       0,     0,     0,     0,     0,    34,     0,     0,     0,    34,
       0,    56,    55,     0,     0,    51,     0,     0,     0,     0,
       0,     0,     0,     0,    14,     3,     0,     4,     5,     6,
       0,    16,     0,    17,    34,     0,     0,     0,     0,     0,
       0,     0,     0,    10,     0,     0,    42,    12,    54,     0,
       0,    50,     0,    36,    37,    38,    39,    40,    41,     8,
      15,    18,     0,     0,    35,    44,    45,    47,    49,    46,
      48,     0,     0,     0,    57,    52,    29,    19,    10,    20,
      25,     0,     0,     0,     0,     0,     0,     0,     0,    12,
      21,    27,    10,    26,     0,     0,    10,    24,    28,     0,
      12
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -90,   -90,   -90,    30,    -2,   -16,   -89,    -1,   165,   -90,
     -90,   -90,   -90
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    19,    25,    39,     2,    21,    22,    37,    23,
      46,    24,    44
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      20,    43,    66,   107,   109,    26,    26,    26,    26,    41,
      32,   -43,    35,    36,    66,    40,    48,    49,    50,    51,
      52,    53,    92,    76,    31,     6,   120,   121,    60,   123,
      62,    64,    36,    55,    56,   127,    75,    42,    27,    28,
      29,    20,    50,    51,    52,    53,    82,    83,    84,    85,
      86,    87,    88,    80,    89,     3,    81,   101,    48,    49,
      50,    51,    52,    53,     6,    94,    95,    96,    97,    98,
      99,   100,    74,    78,     6,    79,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    30,    14,    15,    33,
      20,    20,   114,     4,     5,     6,   111,    38,     6,    20,
     112,   113,    16,    45,    17,    77,   125,    57,    56,    18,
     129,    47,    20,    20,    20,    93,    20,    58,    56,    16,
      63,    34,    20,    20,    59,    56,    18,    20,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    73,    14,
      15,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    66,    14,    15,    16,    90,    17,   110,    52,    53,
     104,    18,   102,   103,   105,   115,   116,    16,   122,    17,
     119,   117,   118,   124,    18,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,    14,    15,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    65,    14,
      15,    16,     0,    17,   128,     0,     0,     0,    18,     0,
       0,     0,     0,     0,    16,     0,    17,   130,     0,     0,
       0,    18,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,     0,    14,    15,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,    14,    15,    16,     0,
      17,     0,     0,     0,     0,    18,     4,     5,     6,     0,
       0,    16,     0,   108,     0,     0,     0,     0,    18,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
      14,    15,    16,     0,    34,     0,    61,     0,     0,    18,
       0,     0,     0,     0,     0,    16,     0,   126,     0,     0,
       0,     0,    18,    67,    68,    69,    70,    71,    72,     0,
      48,    49,    50,    51,    52,    53,    48,    49,    50,    51,
      52,    53,     0,     0,     0,     0,    54,    48,    49,    50,
      51,    52,    53,     0,     0,     0,     0,    91,    48,    49,
      50,    51,    52,    53,     0,     0,     0,     0,   106
};

static const yytype_int16 yycheck[] =
{
       2,    17,    22,    92,    93,     7,     8,     9,    10,     4,
      12,    31,    14,    14,    22,    16,    23,    24,    25,    26,
      27,    28,    30,    30,     4,     5,   115,   116,    30,   118,
      31,    33,    33,    33,    34,   124,    38,    32,     8,     9,
      10,    43,    25,    26,    27,    28,    47,    48,    49,    50,
      51,    52,    53,    34,    56,     0,    37,    73,    23,    24,
      25,    26,    27,    28,     5,    66,    67,    68,    69,    70,
      71,    72,     3,    32,     5,    34,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,     4,    14,    15,    29,
      92,    93,   108,     3,     4,     5,     3,    29,     5,   101,
     102,   103,    29,     3,    31,    32,   122,    33,    34,    36,
     126,    22,   114,   115,   116,    30,   118,    33,    34,    29,
      33,    31,   124,   125,    33,    34,    36,   129,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    31,    14,
      15,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    22,    14,    15,    29,    33,    31,    32,    27,    28,
       4,    36,    35,    35,     3,    13,    30,    29,    31,    31,
      32,    30,    30,    13,    36,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    14,    15,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    33,    14,
      15,    29,    -1,    31,    32,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    31,    32,    -1,    -1,
      -1,    36,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    -1,    14,    15,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    -1,    14,    15,    29,    -1,
      31,    -1,    -1,    -1,    -1,    36,     3,     4,     5,    -1,
      -1,    29,    -1,    31,    -1,    -1,    -1,    -1,    36,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    -1,
      14,    15,    29,    -1,    31,    -1,    33,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    -1,
      -1,    -1,    36,    16,    17,    18,    19,    20,    21,    -1,
      23,    24,    25,    26,    27,    28,    23,    24,    25,    26,
      27,    28,    -1,    -1,    -1,    -1,    33,    23,    24,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    33,    23,    24,
      25,    26,    27,    28,    -1,    -1,    -1,    -1,    33
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    40,    44,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    14,    15,    29,    31,    36,    41,
      43,    45,    46,    48,    50,    42,    43,    42,    42,    42,
       4,     4,    43,    29,    31,    43,    46,    47,    29,    43,
      46,     4,    32,    44,    51,     3,    49,    22,    23,    24,
      25,    26,    27,    28,    33,    33,    34,    33,    33,    33,
      43,    33,    46,    33,    43,    47,    22,    16,    17,    18,
      19,    20,    21,    31,     3,    43,    30,    32,    32,    34,
      34,    37,    46,    46,    46,    46,    46,    46,    46,    43,
      33,    33,    30,    30,    46,    46,    46,    46,    46,    46,
      46,    44,    35,    35,     4,     3,    33,    45,    31,    45,
      32,     3,    43,    43,    44,    13,    30,    30,    30,    32,
      45,    45,    31,    45,    13,    44,    31,    45,    32,    44,
      32
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    41,    41,    42,    42,    43,
      44,    44,    45,    45,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    47,    47,    47,    47,    47,    47,    47,
      48,    49,    49,    49,    50,    50,    51,    51
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     3,     3,     3,     1,     3,     1,
       0,     2,     3,     1,     2,     4,     3,     3,     4,     5,
       5,     7,     7,    11,     9,     5,     7,     7,     9,     4,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     0,     3,     2,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* declaration: INT identifiers SEMICOLON  */
#line 77 "lang.y"
                              { 
        DEBUG_PRINT("Outputting int declaration");
        DEBUG_PRINT("Identifiers from assign: %s", (yyvsp[-1].sval));
        asprintf(&(yyval.sval), "int %s", (yyvsp[-1].sval)); 
        char* temp = strtok((yyvsp[-1].sval), ",");
        while (temp != NULL) {
            putsym(temp, INT);  // Add to symbol table
            temp = strtok(NULL, ",");
        }
        free((yyvsp[-1].sval)); 
    }
#line 1282 "lang.tab.c"
    break;

  case 4: /* declaration: STR identifiers SEMICOLON  */
#line 88 "lang.y"
                                { 
        asprintf(&(yyval.sval), "std::string %s;\n", (yyvsp[-1].sval)); 
        char* temp = strtok((yyvsp[-1].sval), ",");
        while (temp != NULL) {
            putsym(temp, STR);  // Add to symbol table
            temp = strtok(NULL, ",");
        }
        free((yyvsp[-1].sval)); 
    }
#line 1296 "lang.tab.c"
    break;

  case 5: /* declaration: SET identifiers SEMICOLON  */
#line 97 "lang.y"
                                { 
        asprintf(&(yyval.sval), "std::set<int> %s;\n", (yyvsp[-1].sval)); 
        char* temp = strtok((yyvsp[-1].sval), ",");
        while (temp != NULL) {
            putsym(temp, SET);  // Add to symbol table
            temp = strtok(NULL, ",");
        }
        free((yyvsp[-1].sval)); 
    }
#line 1310 "lang.tab.c"
    break;

  case 6: /* declaration: COLLECTION identifiers SEMICOLON  */
#line 106 "lang.y"
                                       { 
        DEBUG_PRINT("Outputting collection declaration for the following identifiers: %s", (yyvsp[-1].sval));
        asprintf(&(yyval.sval), "std::set<std::string> %s;\n", (yyvsp[-1].sval)); 
        char* temp = strtok((yyvsp[-1].sval), ",");
        while (temp != NULL) {
            putsym(temp, COLLECTION);  // Add to symbol table
            temp = strtok(NULL, ",");
        }
        free((yyvsp[-1].sval)); 
    }
#line 1325 "lang.tab.c"
    break;

  case 7: /* identifiers: identifier  */
#line 120 "lang.y"
               { 
        char* temp;
        asprintf(&temp, "%s", (yyvsp[0].sval));
        free((yyvsp[0].sval));
        (yyval.sval) = temp;

     }
#line 1337 "lang.tab.c"
    break;

  case 8: /* identifiers: identifiers COMMA identifier  */
#line 127 "lang.y"
                                   { 
        char* temp; 
        asprintf(&temp, "%s,%s", (yyvsp[-2].sval), (yyvsp[0].sval)); 
        free((yyvsp[-2].sval)); 
        free((yyvsp[0].sval)); 
        (yyval.sval) = temp; 
    }
#line 1349 "lang.tab.c"
    break;

  case 9: /* identifier: IDENTIFIER  */
#line 137 "lang.y"
               { 
        DEBUG_PRINT("identifier from identifier: %s", (yyvsp[0].sval));
        char* temp;
        asprintf(&temp, "CPP_%s", (yyvsp[0].sval));
        free((yyvsp[0].sval));
        (yyval.sval) = temp;
        DEBUG_PRINT("identifier from identifier: %s", (yyval.sval));
        DEBUG_PRINT("current statement in identifier: %s", statementsL);
     }
#line 1363 "lang.tab.c"
    break;

  case 10: /* statements: %empty  */
#line 149 "lang.y"
                { (yyval.sval) = strdup(""); }
#line 1369 "lang.tab.c"
    break;

  case 11: /* statements: statements statement  */
#line 150 "lang.y"
                           {
        DEBUG_PRINT("Before concatenation: %s", statementsL);
        
        // Accumulate the statements
        char* temp;
        asprintf(&temp, "%s%s", statementsL, (yyvsp[0].sval));
        
        DEBUG_PRINT("After concatenation: %s", temp);
        
        // Update statementsL to accumulate the generated code
        free(statementsL);
        statementsL = temp;
        
        // Pass along the accumulated statements
        (yyval.sval) = strdup(statementsL);
        
        free((yyvsp[0].sval));  // Free the current statement since it's already added to statementsL
    }
#line 1392 "lang.tab.c"
    break;

  case 12: /* statement: LBRACE statements RBRACE  */
#line 172 "lang.y"
                             {  
        char* temp;
        asprintf(&temp, "%s", (yyvsp[-1].sval));
        free((yyvsp[-1].sval));
        (yyval.sval) = temp;
    }
#line 1403 "lang.tab.c"
    break;

  case 13: /* statement: declaration  */
#line 178 "lang.y"
                  { 
        asprintf(&(yyval.sval), "%s;\n", (yyvsp[0].sval)); 
        free((yyvsp[0].sval));
    }
#line 1412 "lang.tab.c"
    break;

  case 14: /* statement: expression SEMICOLON  */
#line 182 "lang.y"
                           { 
        asprintf(&(yyval.sval), "%s;\n", (yyvsp[-1].sval)); 
        free((yyvsp[-1].sval)); 
    }
#line 1421 "lang.tab.c"
    break;

  case 15: /* statement: INPUT STRING_LITERAL identifier SEMICOLON  */
#line 186 "lang.y"
                                                { 
        asprintf(&(yyval.sval), "std::cout << %s;\nstd::cin >> %s;\n", (yyvsp[-2].sval), (yyvsp[-1].sval)); 
        free((yyvsp[-2].sval)); 
        free((yyvsp[-1].sval)); 
    }
#line 1431 "lang.tab.c"
    break;

  case 16: /* statement: OUTPUT STRING_LITERAL SEMICOLON  */
#line 191 "lang.y"
                                      { 
        DEBUG_PRINT("Output string literal: %s", (yyvsp[-1].sval));
        asprintf(&(yyval.sval), "std::cout << %s << std::endl;\n", (yyvsp[-1].sval)); 
        free((yyvsp[-1].sval)); 
    }
#line 1441 "lang.tab.c"
    break;

  case 17: /* statement: OUTPUT identifier SEMICOLON  */
#line 196 "lang.y"
                                  {
        DEBUG_PRINT("Output identifier: %s", (yyvsp[-1].sval));
        int res = isSetOrCollection((yyvsp[-1].sval));
        DEBUG_PRINT("isSetOrCollection: %d", res);
        if (res) {
            DEBUG_PRINT("Outputting set or collection");
            asprintf(&(yyval.sval), "for (const auto& element : %s) {\n"
                        "    std::cout << \" \" << element;\n"
                        "}\n"
                        "std::cout << std::endl;\n", (yyvsp[-1].sval));
        } else {
            DEBUG_PRINT("Outputting simple identifier");
            asprintf(&(yyval.sval), "std::cout << %s << std::endl;\n", (yyvsp[-1].sval));
        }
        free((yyvsp[-1].sval));
    }
#line 1462 "lang.tab.c"
    break;

  case 18: /* statement: OUTPUT STRING_LITERAL expression SEMICOLON  */
#line 212 "lang.y"
                                                 { 
        if (isSetOrCollection((yyvsp[-1].sval))) {
            asprintf(&(yyval.sval), "std::cout << %s;\n"
                         "for (const auto& element : %s) {\n"
                         "    std::cout << \" \" << element;\n"
                         "}\n"
                         "std::cout << std::endl;\n", (yyvsp[-2].sval), (yyvsp[-1].sval));
        }
        else if (strchr((yyvsp[-1].sval),MINUS) != NULL)
        {
            char* leftSide = strtok((yyvsp[-1].sval), "-");
            char* rightSide = strtok(NULL, "-");
            asprintf(&(yyval.sval), "std::cout << %s << (%s - intersection(%s, %s)) << std::endl;\n", (yyvsp[-2].sval), leftSide, rightSide, rightSide);
        }
        else if (strstr((yyvsp[-1].sval), "+") != NULL) {
            // Generate code to compute the union of sets using union_sets function
            asprintf(&(yyval.sval), "std::cout << %s << union_sets%s, %s << std::endl;\n", (yyvsp[-2].sval), strtok((yyvsp[-1].sval), "+"), strtok(NULL, "+"));
        }
        else {
            asprintf(&(yyval.sval), "std::cout << %s << %s << std::endl;\n", (yyvsp[-2].sval), (yyvsp[-1].sval));
        }
        DEBUG_PRINT("Output string_lteral,expression: %s %s", (yyvsp[-2].sval), (yyvsp[-1].sval));
        free((yyvsp[-2].sval)); 
        free((yyvsp[-1].sval)); 
    }
#line 1492 "lang.tab.c"
    break;

  case 19: /* statement: IF LPAREN identifier RPAREN statement  */
#line 237 "lang.y"
                                                                  {
        DEBUG_PRINT("Outputting if statement with single statement");
        asprintf(&(yyval.sval), "if (&%s) {\n%s}\n", (yyvsp[-2].sval), (yyvsp[0].sval));
        free((yyvsp[-2].sval));
        free((yyvsp[0].sval));
    }
#line 1503 "lang.tab.c"
    break;

  case 20: /* statement: IF LPAREN condition RPAREN statement  */
#line 243 "lang.y"
                                                                 {
        DEBUG_PRINT("Outputting if statement with single statement");
        asprintf(&(yyval.sval), "if (%s) {\n%s}\n", (yyvsp[-2].sval), (yyvsp[0].sval));
        free((yyvsp[-2].sval));
        free((yyvsp[0].sval));
    }
#line 1514 "lang.tab.c"
    break;

  case 21: /* statement: IF LPAREN condition RPAREN statement ELSE statement  */
#line 249 "lang.y"
                                                          {
        DEBUG_PRINT("Outputting if statement with else statement");
        asprintf(&(yyval.sval), "if (%s) {\n%s} else {\n%s}\n", (yyvsp[-4].sval), (yyvsp[-2].sval), (yyvsp[0].sval));
        free((yyvsp[-4].sval));
        free((yyvsp[-2].sval));
        free((yyvsp[0].sval));
    }
#line 1526 "lang.tab.c"
    break;

  case 22: /* statement: IF LPAREN condition RPAREN LBRACE statements RBRACE  */
#line 256 "lang.y"
                                                          {
        DEBUG_PRINT("Outputting if statement with multiple statements");
        DEBUG_PRINT("Condition: %s", (yyvsp[-4].sval));
        // DEBUG_PRINT("Statements: %s", $$);
        DEBUG_PRINT("Statements from statment: %s", (yyvsp[-1].sval));

        char* if_block;
        asprintf(&if_block, "if (%s) {\n%s}\n", (yyvsp[-4].sval), (yyvsp[-1].sval));

        // Check if_block content
        DEBUG_PRINT("Generated if block: %s", if_block);

        (yyval.sval) = if_block;

        free((yyvsp[-4].sval));
        // free($6);
    }
#line 1548 "lang.tab.c"
    break;

  case 23: /* statement: IF LPAREN condition RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE  */
#line 276 "lang.y"
                                                                                        {
        DEBUG_PRINT("Outputting if statement with else block");
        asprintf(&(yyval.sval), "if (%s) {\n%s} else {\n%s}\n", (yyvsp[-8].sval), (yyvsp[-5].sval), (yyvsp[-1].sval));
        free((yyvsp[-8].sval));
        free((yyvsp[-5].sval));
        free((yyvsp[-1].sval));
    }
#line 1560 "lang.tab.c"
    break;

  case 24: /* statement: IF LPAREN condition RPAREN LBRACE statements RBRACE ELSE statement  */
#line 283 "lang.y"
                                                                         {
        DEBUG_PRINT("Outputting if statement with else statement");
        asprintf(&(yyval.sval), "if (%s) {\n%s} else {\n%s}\n", (yyvsp[-6].sval), (yyvsp[-3].sval), (yyvsp[0].sval));
        free((yyvsp[-6].sval));
        free((yyvsp[-3].sval));
        free((yyvsp[0].sval));
    }
#line 1572 "lang.tab.c"
    break;

  case 25: /* statement: WHILE condition LBRACE statements RBRACE  */
#line 290 "lang.y"
                                               { 
        asprintf(&(yyval.sval), "while (%s) {\n%s}\n", (yyvsp[-3].sval), (yyvsp[-1].sval)); 
        free((yyvsp[-3].sval)); 
        free((yyvsp[-1].sval)); 
    }
#line 1582 "lang.tab.c"
    break;

  case 26: /* statement: FOR LPAREN identifier COLON identifier RPAREN statement  */
#line 295 "lang.y"
                                                              {
        DEBUG_PRINT("Parsing for loop");
        DEBUG_PRINT("Iterator: %s", (yyvsp[-4].sval));
        DEBUG_PRINT("Set/Collection: %s", (yyvsp[-2].sval));
        DEBUG_PRINT("Body: %s", (yyvsp[0].sval));
        
        char* for_block;
        asprintf(&for_block, "for (const auto& %s : %s) {\n%s}\n", (yyvsp[-4].sval), (yyvsp[-2].sval), (yyvsp[0].sval));
        
        DEBUG_PRINT("Generated for block: %s", for_block);
        
        (yyval.sval) = for_block;
        
        free((yyvsp[-4].sval));
        free((yyvsp[-2].sval));
        free((yyvsp[0].sval));
    }
#line 1604 "lang.tab.c"
    break;

  case 27: /* statement: FOR LPAREN NUMBER COLON NUMBER RPAREN statement  */
#line 312 "lang.y"
                                                      {
        DEBUG_PRINT("Parsing for loop with number range");
        DEBUG_PRINT("Start: %d", (yyvsp[-4].ival));
        DEBUG_PRINT("End: %d", (yyvsp[-2].ival));
        DEBUG_PRINT("Body: %s", (yyvsp[0].sval));
        
        char* for_block;
        asprintf(&for_block, "for (int CPP_i = %d; CPP_i <= %d; CPP_i++) {\n%s}\n", (yyvsp[-4].ival), (yyvsp[-2].ival), (yyvsp[0].sval));
        
        DEBUG_PRINT("Generated for block: %s", for_block);
        
        (yyval.sval) = for_block;
        
        // Only free the statement, not the integer values
        free((yyvsp[0].sval));
    }
#line 1625 "lang.tab.c"
    break;

  case 28: /* statement: FOR LPAREN NUMBER COLON identifier RPAREN LBRACE statements RBRACE  */
#line 328 "lang.y"
                                                                         {
        DEBUG_PRINT("Parsing for loop with number range and identifier");
        DEBUG_PRINT("Start: %d", (yyvsp[-6].ival));
        DEBUG_PRINT("End: %s", (yyvsp[-4].sval));
        DEBUG_PRINT("Body: %s", (yyvsp[-1].sval));
        
        char* for_block;
        asprintf(&for_block, "for (int CPP_i = %d; CPP_i <= %s; CPP_i++) {\n%s}\n", (yyvsp[-6].ival), (yyvsp[-4].sval), (yyvsp[-1].sval));
        
        DEBUG_PRINT("Generated for block: %s", for_block);
        
        (yyval.sval) = for_block;
        
        free((yyvsp[-4].sval));
        free((yyvsp[-1].sval));
    }
#line 1646 "lang.tab.c"
    break;

  case 29: /* statement: identifier ASSIGN expression SEMICOLON  */
#line 344 "lang.y"
                                             { 
        DEBUG_PRINT("Outputting assignment statement with expression from statement");
        if (strstr((yyvsp[-1].sval), "+") != NULL && strstr((yyvsp[-1].sval), "{") != NULL) {
            // Case 1: Adding multiple elements to a collection
            char *plus = strchr((yyvsp[-1].sval), '+');
            *plus = '\0';
            char *rightSide = plus + 1;
            while (*rightSide == ' ') rightSide++; // Skip spaces
            asprintf(&(yyval.sval), "%s.insert(%s);\n", (yyvsp[-3].sval), rightSide);
        } else if (strstr((yyvsp[-1].sval), "+") != NULL && strchr((yyvsp[-1].sval), '"') != NULL) {
            // Case 2: Adding a single string element to a collection
            char *plus = strchr((yyvsp[-1].sval), '+');
            *plus = '\0';
            char *rightSide = plus + 1;
            while (*rightSide == ' ') rightSide++; // Skip spaces
            asprintf(&(yyval.sval), "%s.insert(%s;\n", (yyvsp[-3].sval), rightSide);
        } else if (strchr((yyvsp[-1].sval), '{') != NULL) {
            // Case 3: Direct assignment of a set/collection
            asprintf(&(yyval.sval), "%s.insert(%s);\n", (yyvsp[-3].sval), (yyvsp[-1].sval));
        } else {
            if (isSetOrCollection((yyvsp[-3].sval))) {
                DEBUG_PRINT("Outputting set or collection range insertion");
// Case 5: Inserting a range of elements from one set/collection to another
                DEBUG_PRINT("Assign identifier: %s", (yyvsp[-3].sval));
                DEBUG_PRINT("Expression: %s", (yyvsp[-1].sval));
                
                 // Generate the nested insertion statement
                asprintf(&(yyval.sval), "%s.insert(%s.begin(), %s.end());\n",
                        (yyvsp[-3].sval), (yyvsp[-3].sval), (yyvsp[-3].sval), (yyvsp[-1].sval));

                DEBUG_PRINT("Generated nested insertion: %s", (yyval.sval));

            } else {
                DEBUG_PRINT("Outputting simple assignment");
                // Case 4: Simple assignment
                asprintf(&(yyval.sval), "%s = %s;\n", (yyvsp[-3].sval), (yyvsp[-1].sval)); 
            }
            // Case 4: Simple assignment
        }
        free((yyvsp[-3].sval));
        free((yyvsp[-1].sval));
    }
#line 1693 "lang.tab.c"
    break;

  case 30: /* expression: NUMBER  */
#line 391 "lang.y"
           { asprintf(&(yyval.sval), "%d", (yyvsp[0].ival)); }
#line 1699 "lang.tab.c"
    break;

  case 31: /* expression: STRING_LITERAL  */
#line 392 "lang.y"
                     { (yyval.sval) = strdup((yyvsp[0].sval)); }
#line 1705 "lang.tab.c"
    break;

  case 32: /* expression: set_literal  */
#line 393 "lang.y"
                  { (yyval.sval) = (yyvsp[0].sval); }
#line 1711 "lang.tab.c"
    break;

  case 33: /* expression: col_literal  */
#line 394 "lang.y"
                  { (yyval.sval) = (yyvsp[0].sval); }
#line 1717 "lang.tab.c"
    break;

  case 34: /* expression: identifier  */
#line 395 "lang.y"
                 { 
        DEBUG_PRINT("identifier from expression: %s", (yyvsp[0].sval));
        DEBUG_PRINT("statement from expression at the moment: %s", statementsL);
        char* temp;
        asprintf(&temp, "%s", (yyvsp[0].sval));
        free((yyvsp[0].sval));
        (yyval.sval) = temp; 
        DEBUG_PRINT("statement from expression at the moment: %s", statementsL);
        }
#line 1731 "lang.tab.c"
    break;

  case 35: /* expression: identifier ASSIGN expression  */
#line 404 "lang.y"
                                   { 
        DEBUG_PRINT("Outputting assignment statement with expression from expression");
        if (strstr((yyvsp[0].sval), "+") != NULL && strstr((yyvsp[0].sval), "{") != NULL) {
            char *leftSide = strdup((yyvsp[0].sval));
            char *plus = strchr(leftSide, '+');
            *plus = '\0';
            char *rightSide = plus + 1;
            while (*rightSide == ' ') rightSide++; // Skip spaces
            asprintf(&(yyval.sval), "%s.insert(%s.begin(), %s.end())", (yyvsp[-2].sval), rightSide, rightSide);
            free(leftSide);
        } else if (strstr((yyvsp[0].sval), "{") != NULL) {
            asprintf(&(yyval.sval), "%s.insert(%s.begin(), %s.end())", (yyvsp[-2].sval), (yyvsp[0].sval), (yyvsp[0].sval));
        } else {
            asprintf(&(yyval.sval), "%s = %s", (yyvsp[-2].sval), (yyvsp[0].sval)); 
        }
        free((yyvsp[-2].sval)); 
        free((yyvsp[0].sval)); 
    }
#line 1754 "lang.tab.c"
    break;

  case 36: /* expression: expression PLUS expression  */
#line 422 "lang.y"
                                 {
        DEBUG_PRINT("Outputting addition expression");
        if (strstr((yyvsp[-2].sval), "{") != NULL || strstr((yyvsp[0].sval), "{") != NULL) {
            asprintf(&(yyval.sval), "%s + %s", (yyvsp[-2].sval), (yyvsp[0].sval));
        } 
        else if (isSetOrCollection((yyvsp[-2].sval)) && isSetOrCollection((yyvsp[0].sval))) {
            asprintf(&(yyval.sval), "union_sets(%s, %s)", (yyvsp[-2].sval), (yyvsp[0].sval));
        }
        else {
            asprintf(&(yyval.sval), "(%s + %s)", (yyvsp[-2].sval), (yyvsp[0].sval));
        }
        free((yyvsp[-2].sval));
        free((yyvsp[0].sval));
    }
#line 1773 "lang.tab.c"
    break;

  case 37: /* expression: expression MINUS expression  */
#line 436 "lang.y"
                                  { 
        DEBUG_PRINT("Outputting subtraction expression");
         char* temp; 
        asprintf(&temp, "intersection(%s, %s)", (yyvsp[-2].sval), (yyvsp[0].sval)); 
        free((yyvsp[-2].sval)); 
        free((yyvsp[0].sval)); 
        (yyval.sval) = temp; 
    }
#line 1786 "lang.tab.c"
    break;

  case 38: /* expression: expression MUL expression  */
#line 444 "lang.y"
                                { 
        DEBUG_PRINT("Outputting multiplication expression");
        char* temp; 
        asprintf(&temp, "(%s * %s)", (yyvsp[-2].sval), (yyvsp[0].sval)); 
        free((yyvsp[-2].sval)); 
        free((yyvsp[0].sval)); 
        (yyval.sval) = temp; 
    }
#line 1799 "lang.tab.c"
    break;

  case 39: /* expression: expression DIV expression  */
#line 452 "lang.y"
                                { 
        DEBUG_PRINT("Outputting division expression");
        char* temp; 
        asprintf(&temp, "(%s / %s)", (yyvsp[-2].sval), (yyvsp[0].sval)); 
        free((yyvsp[-2].sval)); 
        free((yyvsp[0].sval)); 
        (yyval.sval) = temp; 
    }
#line 1812 "lang.tab.c"
    break;

  case 40: /* expression: expression INTERSECT expression  */
#line 460 "lang.y"
                                      { 
        DEBUG_PRINT("Outputting intersection expression");
        char* temp; 
        asprintf(&temp, "intersection(%s, %s)", (yyvsp[-2].sval), (yyvsp[0].sval)); 
        free((yyvsp[-2].sval)); 
        free((yyvsp[0].sval)); 
        (yyval.sval) = temp; 
    }
#line 1825 "lang.tab.c"
    break;

  case 41: /* expression: expression UNION expression  */
#line 468 "lang.y"
                                  { 
        DEBUG_PRINT("Outputting union expression");
        char* temp; 
        asprintf(&temp, "union_sets(%s, %s)", (yyvsp[-2].sval), (yyvsp[0].sval)); 
        free((yyvsp[-2].sval)); 
        free((yyvsp[0].sval)); 
        (yyval.sval) = temp; 
    }
#line 1838 "lang.tab.c"
    break;

  case 42: /* expression: LPAREN expression RPAREN  */
#line 476 "lang.y"
                               { 
        DEBUG_PRINT("Outputting expression in parentheses");
        char* temp; 
        asprintf(&temp, "(%s)", (yyvsp[-1].sval)); 
        free((yyvsp[-1].sval)); 
        (yyval.sval) = temp; 
    }
#line 1850 "lang.tab.c"
    break;

  case 43: /* condition: identifier  */
#line 486 "lang.y"
               {
        char* temp;
        asprintf(&temp, "&%s", (yyvsp[0].sval));
        free((yyvsp[0].sval));
        (yyval.sval) = temp;
    }
#line 1861 "lang.tab.c"
    break;

  case 44: /* condition: expression EQ expression  */
#line 492 "lang.y"
                               { 
        DEBUG_PRINT("Outputting equality condition");
        char* temp; 
        asprintf(&temp, "(%s == %s)", (yyvsp[-2].sval), (yyvsp[0].sval)); 
        free((yyvsp[-2].sval)); 
        free((yyvsp[0].sval)); 
        (yyval.sval) = temp; 
    }
#line 1874 "lang.tab.c"
    break;

  case 45: /* condition: expression NEQ expression  */
#line 500 "lang.y"
                                { 
        char* temp; 
        asprintf(&temp, "(%s != %s)", (yyvsp[-2].sval), (yyvsp[0].sval)); 
        free((yyvsp[-2].sval)); 
        free((yyvsp[0].sval)); 
        (yyval.sval) = temp; 
    }
#line 1886 "lang.tab.c"
    break;

  case 46: /* condition: expression LT expression  */
#line 507 "lang.y"
                               { 
        char* temp; 
        asprintf(&temp, "(%s < %s)", (yyvsp[-2].sval), (yyvsp[0].sval)); 
        free((yyvsp[-2].sval)); 
        free((yyvsp[0].sval)); 
        (yyval.sval) = temp; 
    }
#line 1898 "lang.tab.c"
    break;

  case 47: /* condition: expression LE expression  */
#line 514 "lang.y"
                               { 
        char* temp; 
        asprintf(&temp, "(%s <= %s)", (yyvsp[-2].sval), (yyvsp[0].sval)); 
        free((yyvsp[-2].sval)); 
        free((yyvsp[0].sval)); 
        (yyval.sval) = temp; 
    }
#line 1910 "lang.tab.c"
    break;

  case 48: /* condition: expression GT expression  */
#line 521 "lang.y"
                               { 
        char* temp; 
        asprintf(&temp, "(%s > %s)", (yyvsp[-2].sval), (yyvsp[0].sval)); 
        free((yyvsp[-2].sval)); 
        free((yyvsp[0].sval)); 
        (yyval.sval) = temp; 
    }
#line 1922 "lang.tab.c"
    break;

  case 49: /* condition: expression GE expression  */
#line 528 "lang.y"
                               { 
        char* temp; 
        asprintf(&temp, "(%s >= %s)", (yyvsp[-2].sval), (yyvsp[0].sval)); 
        free((yyvsp[-2].sval)); 
        free((yyvsp[0].sval)); 
        (yyval.sval) = temp; 
    }
#line 1934 "lang.tab.c"
    break;

  case 50: /* set_literal: LBRACKET number_list RBRACKET  */
#line 538 "lang.y"
                                  { 
        asprintf(&(yyval.sval), "{%s}", (yyvsp[-1].sval)); 
        free((yyvsp[-1].sval)); 
    }
#line 1943 "lang.tab.c"
    break;

  case 51: /* number_list: NUMBER  */
#line 545 "lang.y"
           { asprintf(&(yyval.sval), "%d", (yyvsp[0].ival)); }
#line 1949 "lang.tab.c"
    break;

  case 52: /* number_list: number_list COMMA NUMBER  */
#line 546 "lang.y"
                               {
        char* temp;
        asprintf(&temp, "%s, %d", (yyvsp[-2].sval), (yyvsp[0].ival));
        free((yyvsp[-2].sval));
        (yyval.sval) = temp;
    }
#line 1960 "lang.tab.c"
    break;

  case 53: /* number_list: %empty  */
#line 552 "lang.y"
                  { (yyval.sval) = strdup(""); }
#line 1966 "lang.tab.c"
    break;

  case 54: /* col_literal: LBRACE string_list RBRACE  */
#line 556 "lang.y"
                              { 
        asprintf(&(yyval.sval), "{%s}", (yyvsp[-1].sval)); 
        free((yyvsp[-1].sval)); 
    }
#line 1975 "lang.tab.c"
    break;

  case 55: /* col_literal: LBRACE RBRACE  */
#line 560 "lang.y"
                    { (yyval.sval) = strdup("{}"); }
#line 1981 "lang.tab.c"
    break;

  case 56: /* string_list: STRING_LITERAL  */
#line 564 "lang.y"
                   {
        asprintf(&(yyval.sval), "%s", (yyvsp[0].sval));
        free((yyvsp[0].sval));
    }
#line 1990 "lang.tab.c"
    break;

  case 57: /* string_list: string_list COMMA STRING_LITERAL  */
#line 568 "lang.y"
                                       {
        char* temp;
        asprintf(&temp, "%s, %s", (yyvsp[-2].sval), (yyvsp[0].sval));
        free((yyvsp[-2].sval));
        free((yyvsp[0].sval));
        (yyval.sval) = temp;
    }
#line 2002 "lang.tab.c"
    break;


#line 2006 "lang.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 577 "lang.y"


symrec *putsym(const char *sym_name, int sym_type) {
    symrec *ptr = (symrec *)malloc(sizeof(symrec));
    ptr->name = (char *)malloc(strlen(sym_name) + 1);
    strcpy(ptr->name, sym_name);
    ptr->type = sym_type;
    ptr->next = sym_table;
    sym_table = ptr;
    return ptr;
}

symrec *getsym(const char *sym_name) {
    symrec *ptr;
    for (ptr = sym_table; ptr != NULL; ptr = ptr->next)
        if (strcmp(ptr->name, sym_name) == 0)
            return ptr;
    return NULL;
}

std::set<int> intersection(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

std::set<int> union_sets(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> result = a;
    result.insert(b.begin(), b.end());
    return result;
}

std::set<std::string> intersection(const std::set<std::string>& a, const std::set<std::string>& b) {
    std::set<std::string> result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

std::set<std::string> union_sets(const std::set<std::string>& a, const std::set<std::string>& b) {
    std::set<std::string> result = a;
    result.insert(b.begin(), b.end());
    return result;
}

int isSetOrCollection(const char* var) {
    DEBUG_PRINT("Checking if %s is a set or collection", var);
    symrec* symbol = getsym(var);
    // DEBUG_PRINT("Symbol type: %d", symbol->type);
    if (symbol) {
        DEBUG_PRINT("Symbol type: %d", symbol->type);
        return (symbol->type == SET || symbol->type == COLLECTION);
    }
    return 0;
}

int main(int argc, char **argv) {
    yydebug = 1;  // Enable debug output
    declarations = strdup("");
    statementsL = strdup("");

    outfile = fopen("output.cpp", "w");
    if (!outfile) {
        fprintf(stderr, "Error opening output file\n");
        return 1;
    }

    debugfile = fopen("debug.log", "w");
    if (!debugfile) {
        fprintf(stderr, "Error opening debug file\n");
        return 1;
    }
    ++argv, --argc;
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;

    // Output the header for C++ file
    fprintf(outfile, "#include <iostream>\n#include <set>\n#include <string>\n#include <algorithm>\n\n");

     // Output the intersection and union functions
    fprintf(outfile, "std::set<int> intersection(const std::set<int>& a, const std::set<int>& b) {\n");
    fprintf(outfile, "    std::set<int> result;\n");
    fprintf(outfile, "    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));\n");
    fprintf(outfile, "    return result;\n");
    fprintf(outfile, "}\n\n");

    fprintf(outfile, "std::set<int> union_sets(const std::set<int>& a, const std::set<int>& b) {\n");
    fprintf(outfile, "    std::set<int> result = a;\n");
    fprintf(outfile, "    result.insert(b.begin(), b.end());\n");
    fprintf(outfile, "    return result;\n");
    fprintf(outfile, "}\n\n");

    fprintf(outfile, "std::set<std::string> intersection(const std::set<std::string>& a, const std::set<std::string>& b) {\n");
    fprintf(outfile, "    std::set<std::string> result;\n");
    fprintf(outfile, "    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));\n");
    fprintf(outfile, "    return result;\n");
    fprintf(outfile, "}\n\n");

    fprintf(outfile, "std::set<std::string> union_sets(const std::set<std::string>& a, const std::set<std::string>& b) {\n");
    fprintf(outfile, "    std::set<std::string> result = a;\n");
    fprintf(outfile, "    result.insert(b.begin(), b.end());\n");
    fprintf(outfile, "    return result;\n");
    fprintf(outfile, "}\n\n");

    fprintf(outfile, "std::ostream& operator<<(std::ostream& os, const std::set<std::string>& set) { os << \"{\"; for (auto it = set.begin(); it != set.end(); ++it) { if (it != set.begin()) os << \", \"; os << *it; } os << \"}\"; return os; }\n");

    // Output the main function header
    fprintf(outfile, "int main() {\n");

    yyparse();

    // Output the generated code to the output file
    fprintf(outfile, "%s", statementsL);

    // Output the closing brace for main function
    fprintf(outfile, "    return 0;\n}\n");

    fclose(outfile);
    fclose(debugfile);
    free(declarations);
    free(statementsL);
    return 0;
}
