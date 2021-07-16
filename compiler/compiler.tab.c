/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "compiler.y"
                          // SECCION 1 Declaraciones de C-Yacc

#include <stdio.h>
#include <ctype.h>            // declaraciones para tolower
#include <string.h>           // declaraciones para cadenas
#include <stdlib.h>           // declaraciones para exit ()
#include <pthread.h>
#include "lista.h"            // linked list

// Types of neighborhood
#define MOORE_T         0
#define NEUMANN_T       1
#define EXTENDED_T      2

// Types of variables
#define GLOBAL_T        0
#define CELL_T          1
#define STATE_T         2
#define INIT_T          3
 
int  memoria [26];         	// Se define una zona de memoria para las variables 
char temp [2048];
char identif[2048];
char define[2048];
char drawCell[2048];
char construct[2048];
int  counter = 0;
nodeList *List;              // Lista enlazada para almacenar variables
int neighborhoodType = NEUMANN_T;
int section = GLOBAL_T;

char beginEvaluation [] = "void evaluation(vector<vector<Cell>> &cells, int currentTick){ \n  \n";   
char beginStrain [] = "for (int i = 0; i < N; i++){ \n\tfor (int j = 0; j < N; j++){\n  \n\t\tint** c_neighbours; \n\t\tc_neighbours = (int**)malloc(MAX_NEIGH*sizeof(int *)); \n\t\tfor (int i = 0; i<MAX_NEIGH; i++){ \n\t\t\tc_neighbours[i] = (int *)malloc(2*sizeof(int)); \n\t\t} \n\t\tfor (int i = 0; i<MAX_NEIGH; i++){ \n \t\t\tfor (int j = 0; j<2; j++){ \n\t\t\t\tc_neighbours[i][j] = -1; \n\t\t\t} \n \t\t} \n\t\tsearchNeighbours(c_neighbours, N, i, j, neighType); \n  \n";
char searchFunction [] = "bool search(int** neighbours, int state, vector<vector<Cell>> &cells){ \n int i = 0; \n int x = neighbours[i][0]; \n int y = neighbours[i][1]; \n bool found = false; \n while (found == false && i < MAX_NEIGH){  \n if (x != -1){ \n     if (cells[x][y].state == state){ \n         found = true; \n     } \n } \n x = neighbours[i][0]; \n y = neighbours[i][1]; \n i++; \n } \n return found; \n }\n";
char sumQuarantinedFunction [] = "int sum_quarantined(int** neighbours, vector<vector<Cell>> &cells){ \n int i = 0; \n int x = neighbours[i][0]; \n int y = neighbours[i][1]; \n int sum = 0; \n while (i < MAX_NEIGH){  \n     if(x != -1 && cells[x][y].quarantined){ \n         sum++; \n     } \n \n     x = neighbours[i][0]; \n     y = neighbours[i][1]; \n     i++; \n } \n return sum; \n }\n";
char includes [] = "#include <GL/gl.h> \n #include <GL/glut.h> \n #include <stdio.h> \n #include <cstdlib> \n #include <stdlib.h> \n #include <time.h> \n #include <string.h> \n #include <iostream> \n #include \"sim.h\" \n #include \"grid.h\" \n #include <vector> \n  \n using namespace std; \n using std::vector; \n  \n #define MAX_NEIGH  12 \n";
char infectFunction [] = "void Cell::infect(){ \n\tinfected = true; \n\tstate = 1;\n";
#define FF fflush(stdout);    // para forzar la impresion inmediata

int  yylex();
int  yyerror();
int  yyparse();
char *generateString();
char * toUpper(char aux[]);
void generateCellClass();


#line 118 "compiler.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOL = 258,
    CELLS = 259,
    CONDITION = 260,
    DOUBLE = 261,
    EXTENDED = 262,
    EFFECT = 263,
    FALSE = 264,
    GLOB = 265,
    IDENTIF = 266,
    INT = 267,
    MOORE = 268,
    NEUMANN = 269,
    NGH = 270,
    NUMBER = 271,
    PROP = 272,
    RANDOM = 273,
    IF = 274,
    INIT = 275,
    ELSE = 276,
    CELL = 277,
    STRING = 278,
    TICKS = 279,
    TRUE = 280,
    AND = 281,
    OR = 282,
    EQ = 283,
    NEQ = 284,
    LE = 285,
    GE = 286,
    NORTH = 287,
    SOUTH = 288,
    WEST = 289,
    EAST = 290,
    NORTHEAST = 291,
    NORTHWEST = 292,
    SOUTHEAST = 293,
    SOUTHWEST = 294,
    NORTHP = 295,
    SOUTHP = 296,
    WESTP = 297,
    EASTP = 298,
    STRAIN = 299,
    NUM_STRAINS = 300,
    SIGNO_UNARIO = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 49 "compiler.y"
                      // El tipo de la pila tiene caracter dual
      int valor ;             // - valor numerico de un NUMBER
      char *cadena ;          // - para pasar los nombres de IDENTIFES

#line 219 "compiler.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);





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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYLAST   232

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  180

#define YYUNDEFTOK  2
#define YYMAXUTOK   301


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    59,     2,     2,
      52,    53,    49,    47,    56,    48,    57,    50,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    58,
      60,    46,    61,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    54,     2,    55,     2,     2,     2,     2,
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
      45,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   139,   139,   139,   153,   159,   163,   168,   175,   182,
     190,   196,   203,   207,   212,   217,   225,   228,   235,   236,
     235,   242,   243,   251,   268,   272,   289,   293,   300,   306,
     316,   325,   336,   338,   340,   342,   347,   350,   355,   360,
     364,   368,   373,   376,   379,   384,   384,   389,   392,   397,
     421,   422,   425,   428,   431,   434,   437,   440,   443,   446,
     449,   452,   455,   458,   464,   473,   492,   495,   498,   501,
     506,   523,   528,   531,   534,   538,   541,   545,   548,   551,
     557,   559,   561,   563,   565,   574,   583,   592,   601,   610,
     619,   628
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "CELLS", "CONDITION", "DOUBLE",
  "EXTENDED", "EFFECT", "FALSE", "GLOB", "IDENTIF", "INT", "MOORE",
  "NEUMANN", "NGH", "NUMBER", "PROP", "RANDOM", "IF", "INIT", "ELSE",
  "CELL", "STRING", "TICKS", "TRUE", "AND", "OR", "EQ", "NEQ", "LE", "GE",
  "NORTH", "SOUTH", "WEST", "EAST", "NORTHEAST", "NORTHWEST", "SOUTHEAST",
  "SOUTHWEST", "NORTHP", "SOUTHP", "WESTP", "EASTP", "STRAIN",
  "NUM_STRAINS", "'='", "'+'", "'-'", "'*'", "'/'", "SIGNO_UNARIO", "'('",
  "')'", "'{'", "'}'", "','", "'.'", "';'", "'%'", "'<'", "'>'", "$accept",
  "program", "$@1", "general", "header", "neighbourhood", "nCells",
  "nStrains", "time", "properties", "cell", "$@2", "$@3", "cellProperties",
  "states", "state", "color", "code", "declaration", "strains", "rules",
  "beginIf", "bodyIf", "codeIf", "init", "$@4", "initialAssigments",
  "assignment", "expression", "termino", "operand", "boolValue",
  "intValue", "doubleValue", "position", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,    61,    43,    45,    42,
      47,   301,    40,    41,   123,   125,    44,    46,    59,    37,
      60,    62
};
# endif

#define YYPACT_NINF (-111)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -111,     4,     3,  -111,    15,    13,    37,    48,  -111,    12,
      33,    55,  -111,    71,    41,    26,    75,  -111,    83,    90,
      91,    37,  -111,  -111,  -111,    64,    58,    50,    53,  -111,
      86,    61,    67,    68,  -111,  -111,    92,  -111,  -111,   -15,
      72,    17,   104,   109,  -111,    55,    73,    96,    84,  -111,
    -111,  -111,    94,  -111,  -111,  -111,  -111,    55,   102,   138,
     113,   147,   157,  -111,   138,   117,   115,   138,   163,  -111,
     164,   121,   137,    21,    33,  -111,   149,   139,   163,   141,
    -111,    33,  -111,   144,    94,  -111,    21,    22,  -111,  -111,
    -111,  -111,  -111,  -111,    21,  -111,  -111,   181,   187,  -111,
     148,    62,    21,    21,    21,    21,    21,    21,    21,    21,
      21,    21,   145,    21,    21,    21,    69,   143,   146,   190,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,   150,  -111,   112,   112,   112,   112,   112,
     112,   -16,   -16,   118,   118,    57,   112,   112,   112,  -111,
     188,   181,   141,   151,    57,  -111,   152,    57,  -111,   153,
     187,   194,  -111,   185,  -111,   181,  -111,  -111,   -14,   158,
     160,    57,  -111,    21,   155,   105,  -111,   159,    57,  -111
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,    10,     1,     0,     0,     0,     6,    11,     0,
       0,     0,     4,     0,    14,     0,     0,    45,     0,     0,
       0,    16,     9,     8,     7,     0,    12,     0,     0,     3,
       0,     0,     0,     0,    17,    15,     0,     5,    18,     0,
       0,    72,    77,    75,    13,     0,     0,     0,     0,    74,
      73,    29,    79,    31,    76,    30,    19,    21,     0,     0,
       0,     0,     0,    22,     0,     0,     0,    36,    47,    78,
       0,     0,     0,    72,    34,    37,     0,     0,    47,     0,
      20,    32,    65,     0,    76,    66,    72,     0,    50,    64,
      69,    67,    68,    35,    72,    46,    48,     0,    24,    33,
       0,     0,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,     0,    72,    72,    72,     0,    28,     0,     0,
      23,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,     0,    71,    56,    57,    59,    58,    61,
      63,    51,    52,    53,    54,    42,    55,    60,    62,    49,
       0,     0,     0,     0,    42,    38,     0,    42,    27,     0,
      24,     0,    44,    39,    43,     0,    25,    70,     0,     0,
       0,    42,    26,    72,     0,     0,    41,     0,    42,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,   193,
    -111,  -111,  -111,   161,  -111,    56,    63,  -110,   206,   -72,
     -61,    -5,    42,   -97,  -111,  -111,   154,   -12,   -86,  -111,
    -111,   178,   179,   182,  -111
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,     6,    14,     7,    37,    26,    12,
      10,    45,    62,    56,    71,   120,    98,   118,    57,    17,
      66,   154,   155,   156,    29,    30,    77,   157,    87,    88,
      89,    90,    91,    92,   133
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     101,    46,    93,    72,     3,   170,    75,     4,   116,    99,
     102,   103,   104,   105,   106,   107,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,    49,   146,   147,   148,
      49,     8,    82,   110,   111,     9,    83,    84,    47,    85,
     171,   159,    50,   113,   114,   115,    50,    11,   102,   103,
     104,   105,   106,   107,    67,   169,    78,   162,    18,    67,
     164,    19,    67,    13,    15,    25,    78,    20,    76,   108,
     109,   110,   111,    86,   174,   112,    65,    16,    22,    27,
      35,   113,   114,   115,    23,    24,    28,   175,   102,   103,
     104,   105,   106,   107,    31,   102,   103,   104,   105,   106,
     107,    32,    33,    36,    38,    39,    40,    41,    44,   108,
     109,   110,   111,    42,    43,   134,   108,   109,   110,   111,
      52,   113,   114,   115,    48,    54,    58,   149,   113,   114,
     115,   102,   103,   104,   105,   106,   107,    60,   102,   103,
     104,   105,   106,   107,   102,   103,   104,   105,   106,   107,
      59,    61,   108,   109,   110,   111,    64,    65,   177,   108,
     109,   110,   111,    69,   113,   114,   115,    68,    70,    73,
      74,   113,   114,   115,    76,    79,    80,   113,   114,   115,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,    81,    97,    95,    94,   100,   117,   119,   145,
     150,   152,   151,   153,   158,   167,   168,   163,   161,   165,
     176,   172,   173,   178,    34,   160,   166,    21,    63,    51,
     179,     0,    55,     0,    53,     0,     0,     0,     0,     0,
       0,     0,    96
};

static const yytype_int16 yycheck[] =
{
      86,    16,    74,    64,     0,    19,    67,     4,    94,    81,
      26,    27,    28,    29,    30,    31,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,     9,   113,   114,   115,
       9,    16,    11,    49,    50,    22,    15,    16,    53,    18,
      54,   151,    25,    59,    60,    61,    25,    10,    26,    27,
      28,    29,    30,    31,    59,   165,    68,   154,     3,    64,
     157,     6,    67,    15,    52,    24,    78,    12,    11,    47,
      48,    49,    50,    52,   171,    53,    19,    44,     7,    53,
      16,    59,    60,    61,    13,    14,    11,   173,    26,    27,
      28,    29,    30,    31,    11,    26,    27,    28,    29,    30,
      31,    11,    11,    45,    54,    52,    20,    46,    16,    47,
      48,    49,    50,    46,    46,    53,    47,    48,    49,    50,
      16,    59,    60,    61,    52,    16,    53,    58,    59,    60,
      61,    26,    27,    28,    29,    30,    31,    53,    26,    27,
      28,    29,    30,    31,    26,    27,    28,    29,    30,    31,
      54,    57,    47,    48,    49,    50,    54,    19,    53,    47,
      48,    49,    50,    16,    59,    60,    61,    54,    11,    52,
      55,    59,    60,    61,    11,    11,    55,    59,    60,    61,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    55,    52,    55,    46,    52,    16,    11,    54,
      57,    11,    56,    53,    16,    11,    21,    55,    57,    56,
      55,    53,    52,    54,    21,   152,   160,    11,    57,    41,
     178,    -1,    43,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    63,    64,     0,     4,    65,    66,    68,    16,    22,
      72,    10,    71,    15,    67,    52,    44,    81,     3,     6,
      12,    80,     7,    13,    14,    24,    70,    53,    11,    86,
      87,    11,    11,    11,    71,    16,    45,    69,    54,    52,
      20,    46,    46,    46,    16,    73,    16,    53,    52,     9,
      25,    93,    16,    95,    16,    94,    75,    80,    53,    54,
      53,    57,    74,    75,    54,    19,    82,    83,    54,    16,
      11,    76,    82,    52,    55,    82,    11,    88,    89,    11,
      55,    55,    11,    15,    16,    18,    52,    90,    91,    92,
      93,    94,    95,    81,    46,    55,    88,    52,    78,    81,
      52,    90,    26,    27,    28,    29,    30,    31,    47,    48,
      49,    50,    53,    59,    60,    61,    90,    16,    79,    11,
      77,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    96,    53,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    54,    90,    90,    90,    58,
      57,    56,    11,    53,    83,    84,    85,    89,    16,    79,
      78,    57,    85,    55,    85,    56,    77,    11,    21,    79,
      19,    54,    53,    52,    85,    90,    55,    53,    54,    84
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    64,    63,    65,    66,    67,    67,    67,    67,
      68,    68,    69,    69,    70,    70,    71,    71,    73,    74,
      72,    75,    75,    76,    77,    77,    78,    79,    79,    80,
      80,    80,    81,    81,    81,    81,    82,    82,    83,    84,
      84,    84,    85,    85,    85,    87,    86,    88,    88,    89,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    91,    92,    92,    92,    92,    92,
      92,    92,    93,    93,    93,    94,    94,    95,    95,    95,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     5,     2,     4,     0,     2,     2,     2,
       0,     2,     0,     2,     0,     2,     2,     3,     0,     0,
       9,     1,     2,     4,     0,     4,     7,     3,     1,     4,
       4,     4,     8,     9,     7,     8,     1,     2,     6,     2,
       9,     6,     0,     2,     2,     0,     7,     0,     2,     4,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       6,     3,     0,     1,     1,     0,     1,     0,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 139 "compiler.y"
                                             { Add("state", "int", CELL_T, "0", "0");
                                              Add("alive", "bool", CELL_T, "true", "true");
                                              Add("infected", "bool", CELL_T, "false", "false");
                                            }
#line 1537 "compiler.tab.c"
    break;

  case 3:
#line 143 "compiler.y"
                                            { sprintf(temp, "%s", (yyvsp[-3].cadena));
                                              generateCellClass();
                                              printf ("%s\n %s\n %s\n %s\n %s\n %s\n  ", includes, define, temp, construct, searchFunction, sumQuarantinedFunction); 
                                              sprintf(temp, "%s", (yyvsp[-1].cadena));
                                              printf("%s\n %s } \n %s", beginEvaluation, temp, drawCell);
                                            }
#line 1548 "compiler.tab.c"
    break;

  case 4:
#line 153 "compiler.y"
                                            { sprintf(temp, "%s \n %s \n", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                              (yyval.cadena) = generateString(temp);
                                            }
#line 1556 "compiler.tab.c"
    break;

  case 5:
#line 159 "compiler.y"
                                                    {  sprintf(temp, "%s \n %s \n %s", (yyvsp[-2].cadena), (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(temp); }
#line 1563 "compiler.tab.c"
    break;

  case 6:
#line 163 "compiler.y"
                                            {   sprintf (temp, "int neighType  = NEUMANN;\n");
                                                //printf ("%s", temp); 
                                                (yyval.cadena) = generateString(temp);
                                            }
#line 1572 "compiler.tab.c"
    break;

  case 7:
#line 168 "compiler.y"
                                            { sprintf(temp, "%s", (yyvsp[0].cadena));
                                              sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                              (yyval.cadena) = generateString(temp);
                                              // printf ("%s", temp); 
                                              neighborhoodType = NEUMANN_T; 
                                            }
#line 1583 "compiler.tab.c"
    break;

  case 8:
#line 175 "compiler.y"
                                            { sprintf(temp, "%s", (yyvsp[0].cadena));
                                              sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                              (yyval.cadena) = generateString(temp);
                                              // printf ("%s", temp); 
                                              neighborhoodType = MOORE_T; 
                                            }
#line 1594 "compiler.tab.c"
    break;

  case 9:
#line 182 "compiler.y"
                                            { sprintf(temp, "%s", (yyvsp[0].cadena));
                                              sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                              (yyval.cadena) = generateString(temp);
                                              // printf ("%s", temp); 
                                              neighborhoodType = EXTENDED_T; 
                                            }
#line 1605 "compiler.tab.c"
    break;

  case 10:
#line 190 "compiler.y"
                                            { sprintf (temp, "#define N 100\n");
                                              strcat ( define, temp); 
                                              // sprintf (temp, "");
                                              // $$ = generateString(temp);
                                            }
#line 1615 "compiler.tab.c"
    break;

  case 11:
#line 196 "compiler.y"
                                            { sprintf (temp, "#define N %d\n", (yyvsp[0].valor));
                                              strcat ( define, temp); 
                                              // sprintf (temp, "");
                                              // $$ = generateString(temp);
                                            }
#line 1625 "compiler.tab.c"
    break;

  case 12:
#line 203 "compiler.y"
                                            { sprintf (temp, "int nStrain  = 1;\n");
                                              (yyval.cadena) = generateString(temp);
                                            }
#line 1633 "compiler.tab.c"
    break;

  case 13:
#line 207 "compiler.y"
                                            { sprintf (temp, "int nStrain  = %d;\n", (yyvsp[0].valor));
                                              (yyval.cadena) = generateString(temp);
                                            }
#line 1641 "compiler.tab.c"
    break;

  case 14:
#line 212 "compiler.y"
                                            { sprintf (temp, "int days = 500;\n");
                                              // printf ("%s", temp); 
                                              (yyval.cadena) = generateString(temp);
                                            }
#line 1650 "compiler.tab.c"
    break;

  case 15:
#line 217 "compiler.y"
                                            { sprintf (temp, "int days = %d;\n", (yyvsp[0].valor));
                                              // printf ("%s", temp);
                                              (yyval.cadena) = generateString(temp);
                                            }
#line 1659 "compiler.tab.c"
    break;

  case 16:
#line 225 "compiler.y"
                                                     {  sprintf (temp, "%s", (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(temp);
                                                      }
#line 1667 "compiler.tab.c"
    break;

  case 17:
#line 228 "compiler.y"
                                                     {  sprintf (temp, "%s %s", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(temp);
                                                      }
#line 1675 "compiler.tab.c"
    break;

  case 18:
#line 235 "compiler.y"
                                         { section = CELL_T; }
#line 1681 "compiler.tab.c"
    break;

  case 19:
#line 236 "compiler.y"
                                        { section = STATE_T; }
#line 1687 "compiler.tab.c"
    break;

  case 20:
#line 237 "compiler.y"
                                        {  }
#line 1693 "compiler.tab.c"
    break;

  case 21:
#line 242 "compiler.y"
                                                        { }
#line 1699 "compiler.tab.c"
    break;

  case 22:
#line 243 "compiler.y"
                                                        { }
#line 1705 "compiler.tab.c"
    break;

  case 23:
#line 251 "compiler.y"
                                              { if(strcmp((yyvsp[-3].cadena), "state") != 0) {
                                                  yyerror();
                                                }
                                                if(Get((yyvsp[-2].cadena)) == NULL) { 
                                                  Add((yyvsp[-2].cadena), "none", section, " ", " "); 
                                                  sprintf(temp, "%s", (yyvsp[-2].cadena));
                                                  char aux[1024];
                                                  sprintf(aux, "#define %s %d\n", toUpper(temp), counter);
                                                  strcat(define, aux);
                                                  // printf ("%s", define);
                                                  sprintf(drawCell, "void drawCell(vector<vector<Cell>> &cells){ \n for (int i = 0; i < N; i++){ \n for (int j = 0; j < N; j++){ \n switch (cells[i][j].state){ \n case %s:\n glColor3f%s; \n break;\n %s } \n glRectd(i, j, i+1, j+1); \n }\n }\n  }\n ", toUpper(temp), (yyvsp[-1].cadena), (yyvsp[0].cadena)); 
                                                  
                                                }
                                                else { yyerror("ERROR: Nombre de estado duplicado"); exit(1);}
                                              }
#line 1725 "compiler.tab.c"
    break;

  case 24:
#line 268 "compiler.y"
                                                        { //sprintf(define, "\n"); 
                                                          sprintf(temp, " "); 
                                                          (yyval.cadena) = generateString(temp); }
#line 1733 "compiler.tab.c"
    break;

  case 25:
#line 272 "compiler.y"
                                                        { if(strcmp((yyvsp[-3].cadena), "state") != 0) {
                                                              yyerror();
                                                          }
                                                          if(Get((yyvsp[-2].cadena)) == NULL) { 
                                                            Add((yyvsp[-2].cadena), "none", section, "", ""); 
                                                            sprintf(temp, "%s", (yyvsp[-2].cadena));
                                                            char aux[1024];
                                                            sprintf(aux, "#define %s %d\n", toUpper(temp), counter);
                                                            strcat(define, aux);
                                                            counter++;
                                                            sprintf (temp, "case %s:\n glColor3f%s; \n break;\n %s",toUpper(temp), (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                            (yyval.cadena) = generateString(temp); 
                                                          }
                                                          else { yyerror("ERROR: Variable duplicada"); exit(1);}
                                                       }
#line 1753 "compiler.tab.c"
    break;

  case 26:
#line 289 "compiler.y"
                                                        { sprintf(temp, "(%s,%s,%s)", (yyvsp[-5].cadena), (yyvsp[-3].cadena), (yyvsp[-1].cadena));
                                                          (yyval.cadena) = generateString(temp); }
#line 1760 "compiler.tab.c"
    break;

  case 27:
#line 293 "compiler.y"
                                                        { char *eptr;
                                                          sprintf(temp, " %d.%d", (yyvsp[-2].valor), (yyvsp[0].valor));
                                                          double number = strtod(temp, &eptr);
                                                          if (number > 255.0) { sprintf(temp, "255");}
                                                          else { sprintf(temp, "%f", number); }
                                                          (yyval.cadena) = generateString(temp); }
#line 1771 "compiler.tab.c"
    break;

  case 28:
#line 300 "compiler.y"
                                                        { if((yyvsp[0].valor) > 255) { sprintf(temp, "255"); } 
                                                          else { sprintf(temp, "%d", (yyvsp[0].valor)); }
                                                          (yyval.cadena) = generateString(temp); }
#line 1779 "compiler.tab.c"
    break;

  case 29:
#line 306 "compiler.y"
                                                    { if(Get((yyvsp[-2].cadena)) == NULL) { 
                                                        Add((yyvsp[-2].cadena), "bool", section, (yyvsp[0].cadena), (yyvsp[0].cadena)); 
                                                        sprintf (temp, "%s %s = %s;\n", (yyvsp[-3].cadena), (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                        // printf ("%s", temp); 
                                                        (yyval.cadena) = generateString(temp);
                                                      }
                                                      else { yyerror("ERROR: Variable duplicada"); exit(1);}
                                                      
                                                    }
#line 1793 "compiler.tab.c"
    break;

  case 30:
#line 316 "compiler.y"
                                                    { if(Get((yyvsp[-2].cadena)) == NULL) { 
                                                        Add((yyvsp[-2].cadena), "bool", section, (yyvsp[0].cadena), (yyvsp[0].cadena)); 
                                                        sprintf (temp, "%s %s = %s;\n", (yyvsp[-3].cadena), (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                        // printf ("%s", temp); 
                                                        (yyval.cadena) = generateString(temp);
                                                      }
                                                      else { yyerror("ERROR: Variable duplicada"); exit(1); }
                                                    }
#line 1806 "compiler.tab.c"
    break;

  case 31:
#line 325 "compiler.y"
                                                    { if(Get((yyvsp[-2].cadena)) == NULL) { 
                                                        Add((yyvsp[-2].cadena), "bool", section, (yyvsp[0].cadena), (yyvsp[0].cadena)); 
                                                        sprintf (temp, "%s %s = %s;\n", (yyvsp[-3].cadena), (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                        // printf ("%s", temp); 
                                                        (yyval.cadena) = generateString(temp);
                                                      }
                                                      else { yyerror("ERROR: Variable duplicada"); exit(1); }
                                                    }
#line 1819 "compiler.tab.c"
    break;

  case 32:
#line 336 "compiler.y"
                                                                           { sprintf(temp, " if(currentTick >= %d) {\n %s %s \n } \n } \n ", (yyvsp[-4].valor), beginStrain, (yyvsp[-1].cadena));
                                                                                     (yyval.cadena) = generateString(temp); }
#line 1826 "compiler.tab.c"
    break;

  case 33:
#line 338 "compiler.y"
                                                                           { sprintf(temp, " if(currentTick >= %d) {\n %s %s \n } \n } \n %s ", (yyvsp[-5].valor), beginStrain, (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                                                     (yyval.cadena) = generateString(temp); }
#line 1833 "compiler.tab.c"
    break;

  case 34:
#line 340 "compiler.y"
                                                                           { sprintf(temp, " if(currentTick >= 0) {\n %s %s \n } \n } \n ", beginStrain, (yyvsp[-1].cadena));
                                                                                     (yyval.cadena) = generateString(temp); }
#line 1840 "compiler.tab.c"
    break;

  case 35:
#line 342 "compiler.y"
                                                                           { sprintf(temp, " if(currentTick >= 0) {\n %s %s \n } \n } \n %s ", beginStrain, (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                                                     (yyval.cadena) = generateString(temp); }
#line 1847 "compiler.tab.c"
    break;

  case 36:
#line 347 "compiler.y"
                                                { sprintf(temp, "%s \n }", (yyvsp[0].cadena));
                                                  (yyval.cadena) = generateString(temp); }
#line 1854 "compiler.tab.c"
    break;

  case 37:
#line 350 "compiler.y"
                                                { sprintf(temp, "%s \n %s", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                  (yyval.cadena) = generateString(temp); }
#line 1861 "compiler.tab.c"
    break;

  case 38:
#line 355 "compiler.y"
                                                                  { sprintf (temp, "if( %s ) {\n %s ", (yyvsp[-3].cadena), (yyvsp[0].cadena));
                                                                    (yyval.cadena) = generateString(temp);
                                                                  }
#line 1869 "compiler.tab.c"
    break;

  case 39:
#line 360 "compiler.y"
                                                                    { sprintf(temp, "%s \n}\n",(yyvsp[-1].cadena));
                                                                    (yyval.cadena) = generateString(temp);
                                                                  }
#line 1877 "compiler.tab.c"
    break;

  case 40:
#line 364 "compiler.y"
                                                                     { sprintf(temp, "%s \n} else if ( %s ) {\n %s", (yyvsp[-8].cadena), (yyvsp[-3].cadena), (yyvsp[0].cadena));
                                                                    (yyval.cadena) = generateString(temp);
                                                                  }
#line 1885 "compiler.tab.c"
    break;

  case 41:
#line 368 "compiler.y"
                                                                      { sprintf(temp, "%s \n} else {\n %s \n}", (yyvsp[-5].cadena), (yyvsp[-1].cadena));
                                                                    (yyval.cadena) = generateString(temp);
                                                                  }
#line 1893 "compiler.tab.c"
    break;

  case 42:
#line 373 "compiler.y"
                                                      {   sprintf(temp, " ");
                                                        (yyval.cadena) = generateString(temp);
                                                      }
#line 1901 "compiler.tab.c"
    break;

  case 43:
#line 376 "compiler.y"
                                                      {   sprintf(temp, "%s \n %s", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(temp);}
#line 1908 "compiler.tab.c"
    break;

  case 44:
#line 379 "compiler.y"
                                                      {  sprintf(temp, "%s \n %s", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(temp);}
#line 1915 "compiler.tab.c"
    break;

  case 45:
#line 384 "compiler.y"
                                                      { section = INIT_T; }
#line 1921 "compiler.tab.c"
    break;

  case 46:
#line 385 "compiler.y"
                                                      { sprintf(temp, "%s }", (yyvsp[-1].cadena)); 
                                                        strcat(infectFunction, temp);
                                                      }
#line 1929 "compiler.tab.c"
    break;

  case 47:
#line 389 "compiler.y"
                                                      { sprintf(temp, " ");
                                                        (yyval.cadena) = generateString(temp);
                                                      }
#line 1937 "compiler.tab.c"
    break;

  case 48:
#line 392 "compiler.y"
                                                      { sprintf(temp, "%s \n %s \n", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(temp);
                                                      }
#line 1945 "compiler.tab.c"
    break;

  case 49:
#line 397 "compiler.y"
                                                            { nodeList *p = Get((yyvsp[-3].cadena));
                                                              if(p == NULL) { 
                                                                sprintf(temp, "ERROR: Variable %s doesn't exist", (yyvsp[-3].cadena));          
                                                                yyerror(temp);
                                                                exit(1);
                                                              } else {
                                                                if(p->type2 == CELL_T){
                                                                  // strcpy(p->actualValue, $3);
                                                                  if (section != INIT_T ) {
                                                                    sprintf(temp, "cells[i][j].%s = %s; ", (yyvsp[-3].cadena), (yyvsp[-1].cadena));
                                                                  } else {
                                                                    sprintf(temp, "%s = %s; ", (yyvsp[-3].cadena), (yyvsp[-1].cadena));
                                                                  }
                                                                  (yyval.cadena) = generateString(temp); 
                                                                } else if(p->type2 == GLOBAL_T) {
                                                                  // strcpy(p->actualValue, $3);
                                                                  sprintf(temp, "%s = %s; ", (yyvsp[-3].cadena), (yyvsp[-1].cadena));
                                                                  (yyval.cadena) = generateString(temp); 
                                                                } 
                                                              }
                                                            }
#line 1971 "compiler.tab.c"
    break;

  case 50:
#line 421 "compiler.y"
                                                  { }
#line 1977 "compiler.tab.c"
    break;

  case 51:
#line 422 "compiler.y"
                                                  { sprintf(temp, "%s + %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(temp); }
#line 1984 "compiler.tab.c"
    break;

  case 52:
#line 425 "compiler.y"
                                                  { sprintf(temp, "%s - %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(temp); }
#line 1991 "compiler.tab.c"
    break;

  case 53:
#line 428 "compiler.y"
                                                  { sprintf(temp, "%s * %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(temp); }
#line 1998 "compiler.tab.c"
    break;

  case 54:
#line 431 "compiler.y"
                                                  { sprintf(temp, "%s / %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(temp); }
#line 2005 "compiler.tab.c"
    break;

  case 55:
#line 434 "compiler.y"
                                                  { sprintf(temp, "%s %% %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(temp); }
#line 2012 "compiler.tab.c"
    break;

  case 56:
#line 437 "compiler.y"
                                                  { sprintf(temp, "%s && %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(temp); }
#line 2019 "compiler.tab.c"
    break;

  case 57:
#line 440 "compiler.y"
                                                  { sprintf(temp, "%s || %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(temp); }
#line 2026 "compiler.tab.c"
    break;

  case 58:
#line 443 "compiler.y"
                                                  { sprintf(temp, "%s != %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(temp); }
#line 2033 "compiler.tab.c"
    break;

  case 59:
#line 446 "compiler.y"
                                                  { sprintf(temp, "%s == %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(temp); }
#line 2040 "compiler.tab.c"
    break;

  case 60:
#line 449 "compiler.y"
                                                  { sprintf(temp, "%s < %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(temp); }
#line 2047 "compiler.tab.c"
    break;

  case 61:
#line 452 "compiler.y"
                                                  { sprintf(temp, "%s <= %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                  (yyval.cadena) = generateString(temp); }
#line 2054 "compiler.tab.c"
    break;

  case 62:
#line 455 "compiler.y"
                                                  { sprintf(temp, "%s > %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(temp); }
#line 2061 "compiler.tab.c"
    break;

  case 63:
#line 458 "compiler.y"
                                                  { sprintf(temp, "%s >= %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(temp); }
#line 2068 "compiler.tab.c"
    break;

  case 64:
#line 464 "compiler.y"
                                                       { ; }
#line 2074 "compiler.tab.c"
    break;

  case 65:
#line 473 "compiler.y"
                                                    { nodeList *p = Get((yyvsp[0].cadena));
                                                      if(p == NULL) { 
                                                        sprintf(temp, "ERROR: Variable %s doesn't exist", (yyvsp[0].cadena));          
                                                        yyerror(temp);
                                                        exit(1);
                                                      } else {
                                                        if(p->type2 == CELL_T){
                                                          sprintf(temp, "cells[i][j].%s", (yyvsp[0].cadena));
                                                          (yyval.cadena) = generateString(temp); 
                                                        } else if (p->type2 == GLOBAL_T){
                                                          sprintf(temp, "%s", (yyvsp[0].cadena));
                                                          (yyval.cadena) = generateString(temp); 
                                                        } else if (p->type2 == STATE_T){
                                                          sprintf(temp, "%s", toUpper((yyvsp[0].cadena)));
                                                          (yyval.cadena) = generateString(temp);
                                                        }
                                                      }
                                                    }
#line 2097 "compiler.tab.c"
    break;

  case 66:
#line 492 "compiler.y"
                                                    { sprintf(temp, "((rand() %% (1001))/1000.0)");
                                                      (yyval.cadena) = generateString(temp); }
#line 2104 "compiler.tab.c"
    break;

  case 67:
#line 495 "compiler.y"
                                                    { sprintf(temp, "%s", (yyvsp[0].cadena));
                                                      (yyval.cadena) = generateString(temp); }
#line 2111 "compiler.tab.c"
    break;

  case 68:
#line 498 "compiler.y"
                                                    { sprintf(temp, "%s", (yyvsp[0].cadena));
                                                      (yyval.cadena) = generateString(temp); }
#line 2118 "compiler.tab.c"
    break;

  case 69:
#line 501 "compiler.y"
                                                    { sprintf(temp, "%s", (yyvsp[0].cadena));
                                                      (yyval.cadena) = generateString(temp); }
#line 2125 "compiler.tab.c"
    break;

  case 70:
#line 506 "compiler.y"
                                                    { nodeList *p = Get((yyvsp[-5].cadena));
                                                      if(p == NULL) { 
                                                        sprintf(temp, "ERROR: Variable %s doesn't exist", (yyvsp[-5].cadena));          
                                                        yyerror(temp);
                                                        exit(1);
                                                      } else {
                                                        if(p->type2 == CELL_T){
                                                          sprintf(temp, "cells%s.%s", (yyvsp[-3].cadena), (yyvsp[0].cadena));
                                                          (yyval.cadena) = generateString(temp); 
                                                        } else {
                                                          sprintf(temp, "ERROR: %s not a cell variable", (yyvsp[0].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                        }
                                                      } 
                                                    }
#line 2146 "compiler.tab.c"
    break;

  case 71:
#line 523 "compiler.y"
                                                     { sprintf(temp, "( %s )", (yyvsp[-1].cadena));
                                                      (yyval.cadena) = generateString(temp); }
#line 2153 "compiler.tab.c"
    break;

  case 72:
#line 528 "compiler.y"
                                                {  sprintf (temp, "false");
                                                   (yyval.cadena) = generateString(temp); }
#line 2160 "compiler.tab.c"
    break;

  case 73:
#line 531 "compiler.y"
                                                {  sprintf (temp, "%s", (yyvsp[0].cadena));
                                                   (yyval.cadena) = generateString(temp); }
#line 2167 "compiler.tab.c"
    break;

  case 74:
#line 534 "compiler.y"
                                                {  sprintf (temp, "%s", (yyvsp[0].cadena));
                                                   (yyval.cadena) = generateString(temp); }
#line 2174 "compiler.tab.c"
    break;

  case 75:
#line 538 "compiler.y"
                                                {  sprintf (temp, "-1");
                                                   (yyval.cadena) = generateString(temp); }
#line 2181 "compiler.tab.c"
    break;

  case 76:
#line 541 "compiler.y"
                                                {  sprintf (temp, "%d", (yyvsp[0].valor));
                                                   (yyval.cadena) = generateString(temp); }
#line 2188 "compiler.tab.c"
    break;

  case 77:
#line 545 "compiler.y"
                                                {  sprintf (temp, "0.0");
                                                   (yyval.cadena) = generateString(temp); }
#line 2195 "compiler.tab.c"
    break;

  case 78:
#line 548 "compiler.y"
                                                {  sprintf (temp, "%d.%d", (yyvsp[-2].valor), (yyvsp[0].valor));
                                                   (yyval.cadena) = generateString(temp); }
#line 2202 "compiler.tab.c"
    break;

  case 79:
#line 551 "compiler.y"
                                                {  sprintf (temp, "%d.0", (yyvsp[0].valor));
                                                   (yyval.cadena) = generateString(temp); }
#line 2209 "compiler.tab.c"
    break;

  case 80:
#line 557 "compiler.y"
                                                    { sprintf(temp,"[c_neighbours[1][0]][c_neighbours[1][1]]");
                                                      (yyval.cadena) = generateString(temp);}
#line 2216 "compiler.tab.c"
    break;

  case 81:
#line 559 "compiler.y"
                                                    { sprintf(temp,"[c_neighbours[5][0]][c_neighbours[5][1]]");
                                                      (yyval.cadena) = generateString(temp);}
#line 2223 "compiler.tab.c"
    break;

  case 82:
#line 561 "compiler.y"
                                                    { sprintf(temp,"[c_neighbours[7][0]][c_neighbours[7][1]]");
                                                      (yyval.cadena) = generateString(temp);}
#line 2230 "compiler.tab.c"
    break;

  case 83:
#line 563 "compiler.y"
                                                    { sprintf(temp,"[c_neighbours[3][0]][c_neighbours[3][1]]");
                                                      (yyval.cadena) = generateString(temp);}
#line 2237 "compiler.tab.c"
    break;

  case 84:
#line 565 "compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[2][0]][c_neighbours[2][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[0].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
#line 2251 "compiler.tab.c"
    break;

  case 85:
#line 574 "compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[0][0]][c_neighbours[0][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[0].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
#line 2265 "compiler.tab.c"
    break;

  case 86:
#line 583 "compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[4][0]][c_neighbours[4][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[0].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
#line 2279 "compiler.tab.c"
    break;

  case 87:
#line 592 "compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[6][0]][c_neighbours[6][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[0].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
#line 2293 "compiler.tab.c"
    break;

  case 88:
#line 601 "compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        sprintf(temp,"[c_neighbours[8][0]][c_neighbours[8][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[0].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
#line 2307 "compiler.tab.c"
    break;

  case 89:
#line 610 "compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        sprintf(temp,"[c_neighbours[10][0]][c_neighbours[10][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[0].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
#line 2321 "compiler.tab.c"
    break;

  case 90:
#line 619 "compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        sprintf(temp,"[c_neighbours[11][0]][c_neighbours[11][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[0].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
#line 2335 "compiler.tab.c"
    break;

  case 91:
#line 628 "compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        sprintf(temp,"[c_neighbours[9][0]][c_neighbours[9][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[0].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    }
#line 2349 "compiler.tab.c"
    break;


#line 2353 "compiler.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 639 "compiler.y"
    
                                // SECCION 4    Codigo en C
int n_line = 1 ;

int yyerror (message)
char *message ;
{ 
 
    fprintf (stderr, "\033[1;31m %s en la linea %d\n", message, n_line) ;
    printf ( "\n") ;	// bye
}

char *miMalloc (int nbytes)       // n bytes reserved in dynamic memory
{
    char *p ;
    static long int nb = 0;        // quantify memory
    static int nv = 0 ;            // total memory requested

    p = malloc (nbytes) ;
    if (p == NULL) {
         fprintf (stderr, "No queda memoria para %d bytes mas\n", nbytes) ;
         fprintf (stderr, "Reservados %ld bytes en %d llamadas\n", nb, nv) ;
         exit (0) ;
    }
    nb += (long) nbytes ;
    nv++ ;

    return p ;
}


/***************************************************************************/
/**************************** Stop Words Section ***************************/
/***************************************************************************/

typedef struct sStopWords { // for the stop words of C
    char *name ;
    int token ;
} tStop ;

tStop stopWords [] = { // Stop words
    "bool",         BOOL,
    "cells",        CELLS,
    "condition",    CONDITION,
    "double",       DOUBLE,
    "effect",       EFFECT,
    "extended",     EXTENDED,
    "false",        FALSE,
    "global",       GLOB,
    "int",          INT,
    "moore",        MOORE,
    "neumann",      NEUMANN,
    "ngh",          NGH,
    "prop",         PROP,
    "if",           IF,
    "init",         INIT,
    "else",         ELSE,
    "random",       RANDOM,
    "cell",         CELL,
    "strain",       STRAIN,
    "strains",      NUM_STRAINS,
    "ticks",        TICKS,
    "true",         TRUE,
    "&&",           AND,
    "||",           OR,
    "==",           EQ,
    "!=",           NEQ,
    "<=",           LE,
    ">=",           GE,
    "n",            NORTH,
    "s",            SOUTH,
    "w",            WEST,
    "e",            EAST,
    "ne",           NORTHEAST,
    "nw",           NORTHWEST,
    "se",           SOUTHEAST,
    "sw",           SOUTHWEST,
    "n+",           NORTHP,
    "s+",           SOUTHP,
    "w+",           WESTP,
    "e+",           EASTP,
     NULL,          0               // End of table
} ;

tStop *searchStopWord (char *symbol_name)
{                                  // Search in the stop word table
    int i ;
    tStop *sim ;

    i = 0 ;
    sim = stopWords ;
    while (sim [i].name != NULL) {
           if (strcmp (sim [i].name, symbol_name) == 0) {
                                         // strcmp(a, b) return == 0 if a==b
                 return &(sim [i]) ;
             }
           i++ ;
    }

    return NULL ;
}

 
/***************************************************************************/
/************************* Lexicographical Analizer ************************/
/***************************************************************************/

char *generateString (char *name)     // copy the argument in a string 
{                                      
      char *p ;
      int l ;

      l = strlen (name)+1 ;
      p = (char *) miMalloc (l) ;
      strcpy (p, name) ;

      return p ;
}


int yylex ()
{
    int i ;
    unsigned char c ;
    unsigned char cc ;
    char ops_expandibles [] = "!<=>|%&+-/*" ;
    char cadena [256] ;
    tStop *symbol ;

    do {
    	c = getchar () ;

		if (c == '#') {	// Ignore the lines begin in #  (#define, #include)
			do {		//	OJO que puede funcionar mal si una linea contiene #
			 c = getchar () ;	
			} while (c != '\n') ;
		}
		
		if (c == '/') {	// If the line contain / could be a comment 
			cc = getchar () ;
			if (cc != '/') {   // If the next char is / is a comment 
				ungetc (cc, stdin) ;
		 } else {
		     c = getchar () ;	// ...
		     if (c == '@') {	// If is the sequence //@  ==> we transcribe the line
		          do {		// Inline code (Codigo embebido en C)
		              c = getchar () ;
		              putchar (c) ;
		          } while (c != '\n') ;
		     } else {		// ==> Comment, ignore the line
		          while (c != '\n') {
		              c = getchar () ;
		          }
		     }
		 }
		}
		
		if (c == '\n')
		 n_line++ ;
		
    } while (c == ' ' || c == '\n' || c == 10 || c == 13 || c == '\t') ;

    if (c == '\"') {
         i = 0 ;
         do {
             c = getchar () ;
             cadena [i++] = c ;
         } while (c != '\"' && i < 255) ;
         if (i == 256) {
              printf ("AVISO: string con mas de 255 caracteres en linea %d\n", n_line) ;
         }		 	
         cadena [--i] = '\0' ;
         yylval.cadena = generateString (cadena) ;
         return (STRING) ;
    }

    if ((c >= '0' && c <= '9')) {
         ungetc (c, stdin) ;
         scanf ("%d", &yylval.valor) ;
//         printf ("\nDEV: NUMBER %d\n", yylval.valor) ;        // PARA DEPURAR
         return NUMBER ;
    }

    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
         i = 0 ;
         while (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
                 (c >= '0' && c <= '9') || c == '_') && i < 255) {
             cadena [i++] = tolower (c) ;
             c = getchar () ;
         }
         cadena [i] = '\0' ;
         ungetc (c, stdin) ;

         yylval.cadena = generateString (cadena) ;
         symbol = searchStopWord (yylval.cadena) ;
         if (symbol == NULL) {    // isn't an stop word -> identif 
//               printf ("\nDEV: IDENTIF %s\n", yylval.cadena) ;    // PARA DEPURAR
               return (IDENTIF) ;
         } else {
//               printf ("\nDEV: OTRO %s\n", yylval.cadena) ;       // PARA DEPURAR
               return (symbol->token) ;
         }
    }

    if (strchr (ops_expandibles, c) != NULL) { // busca c en ops_expandibles
         cc = getchar () ;
         sprintf (cadena, "%c%c", (char) c, (char) cc) ;
         symbol = searchStopWord (cadena) ;
         if (symbol == NULL) {
              ungetc (cc, stdin) ;
              yylval.cadena = NULL ;
              return (c) ;
         } else {
              yylval.cadena = generateString (cadena) ; // aunque no se use
              return (symbol->token) ;
         }
    }

//    printf ("\nDEV: LITERAL %d #%c#\n", (int) c, c) ;      // PARA DEPURAR
    if (c == EOF || c == 255 || c == 26) {
//         printf ("tEOF ") ;                                // PARA DEPURAR
         return (0) ;
    }

    return c ;
}

char * toUpper(char aux[]){
    char *word;
    word = generateString(aux);
    // counter for the loop
    int i = 0;

    // word to convert to uppercase
    char chr; 

    // Loop
    while (word[i]) { 
        chr = word[i];
        word[i] = toupper(chr); 
        i++; 
    } 
    return word;
}

/*-----------Fuctions for the Linked List----------*/
// Add new nodes to the list
int Add(char *name, char *type, int type2, char *defValue, char *actualValue)
{
    nodeList *p = List;    //Pointer

    //We chek if this node exists
    while(p != NULL){
        if(strcmp(name, p->name)==0 && strcmp(type, p->type)==0 && type2 == p->type2){
            return 0; //Node already exists
        }
        p = p->next;
    }

    // Insert one node at the beginning of the list
    nodeList *newNode = (nodeList *)malloc(sizeof(nodeList));
    strcpy(newNode->name, name);
    strcpy(newNode->type, type);
    strcpy(newNode->defValue, defValue);
    strcpy(newNode->actualValue, actualValue);
    newNode->type2 = type2;
    newNode->next = List;    
    List = newNode;
    return 1;  
}


// To check if one element is on the list
nodeList* Get(char *name)
{
    nodeList *p = List; //Pointer
    
    //Go throught the list searching the node
    while(p != NULL){
        if(strcmp(name, p->name)==0){
            return p;  
        }
        p = p->next;
    }
    return NULL;  // Node not found
}

// Delete one node with these atributes
int Destroy(char *name, char *type, int type2) {

    if(List == NULL) return -1;    //The list is empty

    if(strcmp(List->type, type) == 0 && List->type2 == type2 && strcmp(List->name, name) == 0){   //If the first node is the node we are looking for, deleted
        nodeList *aux = List;
        List = List->next;
        aux->next = NULL;
        free(aux);
        return 1;
    }

    nodeList *p = List; //Pointer

    
    while(p->next != NULL){
        if(strcmp(name, p->name)==0 && strcmp(type, p->type)==0 && type2 == p->type2){
            nodeList *aux=p->next;
            p->next=p->next->next;
            aux->next= NULL;
            free(aux);
            return 1;
        }
        p = p->next;
    }
    return -1;  //Node not found
}

int main ()
{
    yyparse () ;
}



void generateCellClass(){
  // char construct[2048];
  char assignment[2048];
  sprintf(construct, "class Cell{ \n public: \n int state;\n");
  sprintf(assignment, "Cell::Cell (){\n \n state  = 0;\n ");

  nodeList *p = List; //Pointer
  while(p->next != NULL){
    if(p->type2 == CELL_T){
        strcat(construct, p->type);
        strcat(construct, " ");
        strcat(construct, p->name);
        strcat(construct, ";\n");

        strcat(assignment, p->name);
        strcat(assignment, " = ");
        strcat(assignment, p->defValue);
        strcat(assignment, ";\n");
    }
    p = p->next;
  }

  strcat(construct, " Cell(); \n void infect(); \n }; \n");
  strcat(assignment, "}\n  \n  ");


  strcat(construct, assignment);
  strcat(construct, infectFunction);
  // return construct;
}
