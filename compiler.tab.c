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
#line 1 "src/compiler_files/compiler.y"
                          // SECCION 1 Declaraciones de C-Yacc

#include <stdio.h>
#include <ctype.h>            // declaraciones para tolower
#include <string.h>           // declaraciones para cadenas
#include <stdlib.h>           // declaraciones para exit ()
#include <pthread.h>
#include "src/compiler_files/lista.h"            // linked list

// Types of neighborhood
#define MOORE_T         0
#define NEUMANN_T       1
#define EXTENDED_T      2

// Types of sections
#define GLOBAL_T        0
#define CELL_T          1
#define STATE_T         2
#define INIT_T          3
#define STRAIN_T        4

// Type of variables
#define NO_TYPE           0
#define BOOLEAN_T         1
#define INTEGER_T         2
#define DOUBLE_T          3

int  memoria [26];         	// Se define una zona de memoria para las variables 
char identif[2048];
char define[2048];
char drawCell[2048];
char construct[2048];
char foundFunction[2048];
int typeExpression[100];
int i = 0;
int hasState = 0;
int numStrains = 1;

int  counter = 1;
nodeList *List;              // Lista enlazada para almacenar variables
int neighborhoodType = NEUMANN_T;
int section = GLOBAL_T;

char beginEvaluation [] = "void evaluation(vector<vector<Cell>> &cells, int currentTick){ \n int results[nStates]; \n for (int i=0; i<nStates; i++){ \n     results[i] = 0; \n } \n";   
char beginStrain [] = "for (int i = 0; i < N; i++){ \n\tfor (int j = 0; j < N; j++){\n  \n\t\tint** c_neighbours; \n\t\tc_neighbours = (int**)malloc(MAX_NEIGH*sizeof(int *)); \n\t\tfor (int i = 0; i<MAX_NEIGH; i++){ \n\t\t\tc_neighbours[i] = (int *)malloc(2*sizeof(int)); \n\t\t} \n\t\tfor (int i = 0; i<MAX_NEIGH; i++){ \n \t\t\tfor (int j = 0; j<2; j++){ \n\t\t\t\tc_neighbours[i][j] = -1; \n\t\t\t} \n \t\t} \n\t\tsearchNeighbours(c_neighbours, N, i, j, neighType); \n  \n";
char countFunction [] = "int count(int** neighbours, string variable, string value, vector<vector<Cell>> &cells){ \n     int i = 0; \n     int x = neighbours[i][0]; \n     int y = neighbours[i][1]; \n     int found = 0; \n     while (found == false && i < MAX_NEIGH){  \n         if (x != -1){ \n             if(foundVariable(cells[x][y], variable).compare(value) == 0){ \n                 found ++; \n             } \n         } \n         x = neighbours[i][0]; \n         y = neighbours[i][1]; \n         i++; \n     } \n     return found; \n } \n";
char includes [] = "#include <GL/gl.h> \n #include <GL/glut.h> \n #include <stdio.h> \n #include <cstdlib> \n #include <stdlib.h> \n #include <time.h> \n #include <string.h> \n #include <iostream> \n #include <fstream> \n #include \"sim.h\" \n #include \"grid.h\" \n #include <vector> \n  \n using namespace std; \n using std::vector; \n  \n #define MAX_NEIGH  12 \n #define NO_CHANGE 0\n";
char infectFunction [] = "void Cell::infect(){ \n\tinfected = true; \n \n";

#define FF fflush(stdout);    // para forzar la impresion inmediata

int  yylex();
int  yyerror();
int  yywarning();
int  yyparse();
char *generateString();
char * toUpper(char aux[]);
void generateCellClass();
void generateFoundFunction();
char * generateFirstLine();
int foundType(int type);
void clean();


#line 135 "compiler.tab.c"

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
    COUNT = 260,
    CURRENTTICK = 261,
    CONTINUE = 262,
    DOUBLE = 263,
    EXTENDED = 264,
    FALSE = 265,
    GLOB = 266,
    IDENTIF = 267,
    INT = 268,
    MOORE = 269,
    NEUMANN = 270,
    NGH = 271,
    NUMBER = 272,
    PROP = 273,
    RANDOM = 274,
    IF = 275,
    INIT = 276,
    ELSE = 277,
    CELL = 278,
    STRING = 279,
    TICKS = 280,
    TRUE = 281,
    AND = 282,
    OR = 283,
    EQ = 284,
    NEQ = 285,
    LE = 286,
    GE = 287,
    NORTH = 288,
    SOUTH = 289,
    WEST = 290,
    EAST = 291,
    NORTHEAST = 292,
    NORTHWEST = 293,
    SOUTHEAST = 294,
    SOUTHWEST = 295,
    NORTHP = 296,
    SOUTHP = 297,
    WESTP = 298,
    EASTP = 299,
    STRAIN = 300,
    NUM_STRAINS = 301,
    SIGNO_UNARIO = 302
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 66 "src/compiler_files/compiler.y"
                      // El tipo de la pila tiene caracter dual
      int valor ;             // - valor numerico de un NUMBER
      char *cadena ;          // - para pasar los nombres de IDENTIFES

#line 237 "compiler.tab.c"

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
#define YYLAST   266

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  204

#define YYUNDEFTOK  2
#define YYMAXUTOK   302


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
      54,    55,    50,    48,    58,    49,    62,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    53,
      60,    47,    61,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    56,     2,    57,     2,     2,     2,     2,
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
      45,    46,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   157,   157,   157,   190,   199,   207,   215,   223,   231,
     240,   247,   255,   262,   271,   278,   288,   294,   304,   305,
     304,   311,   312,   320,   339,   346,   374,   382,   407,   426,
     445,   462,   480,   497,   517,   526,   535,   544,   556,   563,
     572,   581,   589,   597,   609,   611,   618,   624,   628,   628,
     646,   648,   656,   656,   693,   694,   701,   708,   714,   720,
     726,   732,   738,   744,   750,   756,   762,   768,   774,   780,
     789,   804,   841,   845,   853,   861,   871,   883,   911,   919,
     926,   934,   940,   948,   955,   961,   967,   977,   978,   979,
     980,   981,   988,   995,  1002,  1009,  1016,  1023,  1030
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "CELLS", "COUNT", "CURRENTTICK",
  "CONTINUE", "DOUBLE", "EXTENDED", "FALSE", "GLOB", "IDENTIF", "INT",
  "MOORE", "NEUMANN", "NGH", "NUMBER", "PROP", "RANDOM", "IF", "INIT",
  "ELSE", "CELL", "STRING", "TICKS", "TRUE", "AND", "OR", "EQ", "NEQ",
  "LE", "GE", "NORTH", "SOUTH", "WEST", "EAST", "NORTHEAST", "NORTHWEST",
  "SOUTHEAST", "SOUTHWEST", "NORTHP", "SOUTHP", "WESTP", "EASTP", "STRAIN",
  "NUM_STRAINS", "'='", "'+'", "'-'", "'*'", "'/'", "SIGNO_UNARIO", "';'",
  "'('", "')'", "'{'", "'}'", "','", "'%'", "'<'", "'>'", "'.'", "$accept",
  "program", "$@1", "general", "header", "neighbourhood", "nCells",
  "nStrains", "time", "properties", "cell", "$@2", "$@3", "cellProperties",
  "states", "state", "color", "codeColor", "declaration", "strains",
  "rules", "beginIf", "bodyIf", "codeIf", "init", "$@4",
  "initialAssigments", "assignment", "$@5", "expression", "termino",
  "operand", "boolValue", "intValue", "doubleValue", "position", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,    61,    43,    45,
      42,    47,   302,    59,    40,    41,   123,   125,    44,    37,
      60,    62,    46
};
# endif

#define YYPACT_NINF (-118)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-53)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -118,    12,    14,  -118,    50,    -4,    64,    65,  -118,    26,
      38,     7,  -118,    59,    61,    32,    76,  -118,    77,    79,
      80,    40,  -118,  -118,  -118,    83,    55,    48,    51,  -118,
      85,    72,    73,    74,    64,  -118,    97,  -118,  -118,   -13,
      69,    -5,   -10,    -6,  -118,  -118,     7,    78,    68,    82,
    -118,  -118,  -118,    90,   117,  -118,  -118,   118,  -118,  -118,
      86,    87,   124,   103,   121,    98,  -118,   149,     7,   124,
     108,   106,   124,   152,  -118,   148,   154,   114,  -118,   116,
      28,    38,  -118,   125,   152,   171,  -118,   130,  -118,    38,
     153,  -118,   159,    90,  -118,    28,    36,    28,    67,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,   168,   -10,   194,
    -118,   196,   202,   167,   157,   167,    81,    28,    28,    28,
      28,    28,    28,    28,    28,    28,    28,   158,    28,    28,
      28,    28,   165,  -118,   204,  -118,   166,  -118,  -118,  -118,
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,   170,
     212,  -118,   161,   161,   161,   161,   161,   161,   167,   167,
     173,   173,     2,   161,   161,   161,   119,   -10,   130,    53,
     169,  -118,   177,     2,  -118,   190,     2,  -118,   191,   194,
     231,   195,   239,  -118,  -118,   230,  -118,   -10,  -118,    98,
    -118,  -118,    -7,   198,   200,     2,  -118,    28,   199,   126,
    -118,   201,     2,  -118
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,    10,     1,     0,     0,     0,     6,    11,     0,
       0,     0,     4,     0,    14,     0,     0,    48,     0,     0,
       0,     0,     9,     8,     7,     0,    12,     0,     0,     3,
       0,    29,    33,    31,    16,    15,     0,     5,    18,     0,
       0,     0,     0,     0,    17,    13,     0,     0,     0,     0,
      80,    79,    28,    84,     0,    32,    81,     0,    30,    19,
       0,     0,     0,     0,     0,    85,    82,     0,    21,     0,
       0,     0,    38,    50,    83,     0,     0,     0,    22,     0,
       0,    36,    39,     0,    50,     0,    86,     0,    20,    34,
       0,    71,     0,    81,    72,     0,     0,     0,     0,    54,
      70,    75,    73,    74,    37,    49,    51,     0,     0,    24,
      35,     0,     0,    69,    81,    68,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    27,     0,    23,     0,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,     0,
       0,    78,    60,    61,    63,    62,    65,    67,    55,    56,
      57,    58,    44,    59,    64,    66,     0,     0,     0,     0,
       0,    83,     0,    44,    40,     0,    44,    53,     0,    24,
       0,     0,     0,    47,    46,    41,    45,     0,    25,    82,
      76,    77,     0,     0,     0,    44,    26,     0,     0,     0,
      43,     0,    44,    42
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,  -118,   221,
    -118,  -118,  -118,   192,  -118,    84,    91,  -116,   247,   -73,
      -8,   -12,    60,  -117,  -118,  -118,   180,   -67,  -118,   -94,
      92,  -118,   224,   223,   -42,  -118
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,     6,    14,     7,    37,    26,    12,
      10,    46,    67,    59,    77,   135,   109,   132,    60,    17,
      71,   173,   174,   175,    29,    30,    83,   176,    85,    98,
      99,   100,   101,   102,   103,   149
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      55,   113,   115,   116,    47,    50,    84,    53,   104,   172,
      18,    56,     3,   194,   -52,    19,   110,    84,     4,     9,
      20,    51,    70,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,    90,   163,   164,   165,   166,    50,    54,
      91,    90,    48,    57,    92,    93,    50,    94,    91,   195,
      72,   178,    92,   114,    51,    94,   184,    72,    90,   186,
      72,    79,    51,    50,    82,    91,   133,     8,    22,    92,
      93,   193,    94,    23,    24,    11,    95,    96,   198,    51,
      15,    13,    97,    16,    95,    96,    25,    27,    28,    31,
      97,    32,    33,    34,   117,   118,   119,   120,   121,   122,
      35,    36,   180,   199,    38,    39,    40,    97,   117,   118,
     119,   120,   121,   122,    45,   123,   124,   125,   126,    41,
      42,    43,   127,    49,    62,   133,   128,   129,   130,   123,
     124,   125,   126,    61,    65,    66,   151,    63,    74,    68,
     128,   129,   130,    69,    70,   133,   117,   118,   119,   120,
     121,   122,    64,   117,   118,   119,   120,   121,   122,    73,
      75,    76,    80,    81,   -52,    86,    87,   123,   124,   125,
     126,    88,   177,    89,   123,   124,   125,   126,   128,   129,
     130,   201,   105,   107,   108,   128,   129,   130,   117,   118,
     119,   120,   121,   122,   117,   118,   119,   120,   121,   122,
     117,   118,   119,   120,   121,   122,   134,   111,   136,   123,
     124,   125,   126,   112,   162,   131,   168,   125,   126,   150,
     128,   129,   130,   167,   169,   170,   128,   129,   130,   171,
     183,   182,   128,   129,   130,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   185,   189,   187,
     190,   191,   192,   196,   197,    44,   200,   202,    21,   179,
      78,   181,   203,   188,   106,    52,    58
};

static const yytype_uint8 yycheck[] =
{
      42,    95,    96,    97,    17,    10,    73,    17,    81,     7,
       3,    17,     0,    20,    12,     8,    89,    84,     4,    23,
      13,    26,    20,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,     5,   128,   129,   130,   131,    10,    49,
      12,     5,    55,    49,    16,    17,    10,    19,    12,    56,
      62,   167,    16,    17,    26,    19,   173,    69,     5,   176,
      72,    69,    26,    10,    72,    12,   108,    17,     9,    16,
      17,   187,    19,    14,    15,    11,    48,    49,   195,    26,
      54,    16,    54,    45,    48,    49,    25,    55,    12,    12,
      54,    12,    12,    53,    27,    28,    29,    30,    31,    32,
      17,    46,    49,   197,    56,    54,    21,    54,    27,    28,
      29,    30,    31,    32,    17,    48,    49,    50,    51,    47,
      47,    47,    55,    54,    56,   167,    59,    60,    61,    48,
      49,    50,    51,    55,    17,    17,    55,    55,    17,    53,
      59,    60,    61,    56,    20,   187,    27,    28,    29,    30,
      31,    32,    62,    27,    28,    29,    30,    31,    32,    56,
      62,    12,    54,    57,    12,    17,    12,    48,    49,    50,
      51,    57,    53,    57,    48,    49,    50,    51,    59,    60,
      61,    55,    57,    12,    54,    59,    60,    61,    27,    28,
      29,    30,    31,    32,    27,    28,    29,    30,    31,    32,
      27,    28,    29,    30,    31,    32,    12,    54,    12,    48,
      49,    50,    51,    54,    56,    47,    12,    50,    51,    62,
      59,    60,    61,    58,    58,    55,    59,    60,    61,    17,
      53,    62,    59,    60,    61,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    57,    17,    58,
      55,    12,    22,    55,    54,    34,    57,    56,    11,   168,
      68,   169,   202,   179,    84,    41,    43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    64,    65,     0,     4,    66,    67,    69,    17,    23,
      73,    11,    72,    16,    68,    54,    45,    82,     3,     8,
      13,    81,     9,    14,    15,    25,    71,    55,    12,    87,
      88,    12,    12,    12,    53,    17,    46,    70,    56,    54,
      21,    47,    47,    47,    72,    17,    74,    17,    55,    54,
      10,    26,    95,    17,    49,    97,    17,    49,    96,    76,
      81,    55,    56,    55,    62,    17,    17,    75,    53,    56,
      20,    83,    84,    56,    17,    62,    12,    77,    76,    83,
      54,    57,    83,    89,    90,    91,    17,    12,    57,    57,
       5,    12,    16,    17,    19,    48,    49,    54,    92,    93,
      94,    95,    96,    97,    82,    57,    89,    12,    54,    79,
      82,    54,    54,    92,    17,    92,    92,    27,    28,    29,
      30,    31,    32,    48,    49,    50,    51,    55,    59,    60,
      61,    47,    80,    97,    12,    78,    12,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    98,
      62,    55,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    56,    92,    92,    92,    92,    58,    12,    58,
      55,    17,     7,    84,    85,    86,    90,    53,    80,    79,
      49,    93,    62,    53,    86,    57,    86,    58,    78,    17,
      55,    12,    22,    80,    20,    56,    55,    54,    86,    92,
      57,    55,    56,    85
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    65,    64,    66,    67,    68,    68,    68,    68,
      69,    69,    70,    70,    71,    71,    72,    72,    74,    75,
      73,    76,    76,    77,    78,    78,    79,    80,    81,    81,
      81,    81,    81,    81,    82,    82,    82,    82,    83,    83,
      84,    85,    85,    85,    86,    86,    86,    86,    88,    87,
      89,    89,    91,    90,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      93,    94,    94,    94,    94,    94,    94,    94,    94,    95,
      95,    96,    96,    97,    97,    97,    97,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     5,     2,     4,     0,     2,     2,     2,
       0,     2,     0,     2,     0,     2,     3,     4,     0,     0,
       9,     2,     3,     4,     0,     4,     7,     1,     4,     2,
       4,     2,     4,     2,     8,     9,     7,     8,     1,     2,
       6,     2,     9,     6,     0,     2,     2,     2,     0,     7,
       0,     2,     0,     5,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       1,     1,     1,     1,     1,     1,     6,     6,     3,     1,
       1,     1,     2,     3,     1,     2,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
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
#line 157 "src/compiler_files/compiler.y"
                                            { Add("state", "int", CELL_T, "0", "0");
                                              Add("alive", "bool", CELL_T, "true", "true");
                                              Add("infected", "bool", CELL_T, "false", "false");
                                              Add("no_change", "none", STATE_T, " ", " "); 
                                            }
#line 1571 "compiler.tab.c"
    break;

  case 3:
#line 162 "src/compiler_files/compiler.y"
                                            { size_t needed = snprintf(NULL, 0, "%s", (yyvsp[-3].cadena)) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "%s", (yyvsp[-3].cadena));
                                              generateCellClass();
                                              generateFoundFunction();
                                              char aux[2048];
                                              sprintf(aux, "\n");

                                              nodeList *p = List; //Pointer
                                              while(p->next != NULL){
                                                  if(STRAIN_T == p->section){
                                                      char file[100];
                                                      sprintf(file, "ofstream %s(\"Data/DataStrain_%s.csv\");\n", p->name, p->name); 
                                                      strcat(aux, file);
                                                  }
                                                  p = p->next;
                                              }

                                              printf ("%s\n%s\n%s\nint nStates = %d;\n%s\n%s\n%s\n%s\n ", includes, define, aux, (counter+1), buffer, construct, foundFunction, countFunction); 
                                              
                                              printf("%s\n %s \n%s } \n %s", beginEvaluation, generateFirstLine(), (yyvsp[-1].cadena), drawCell);
                                              
                                              free(buffer);
                                            }
#line 1600 "compiler.tab.c"
    break;

  case 4:
#line 190 "src/compiler_files/compiler.y"
                                            { size_t needed = snprintf(NULL, 0, "%s \n %s \n", (yyvsp[-1].cadena), (yyvsp[0].cadena)) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "%s \n %s \n", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                              (yyval.cadena) = generateString(buffer);
                                              free(buffer);
                                            }
#line 1611 "compiler.tab.c"
    break;

  case 5:
#line 199 "src/compiler_files/compiler.y"
                                                    {  size_t needed = snprintf(NULL, 0, "%s %s %s", (yyvsp[-2].cadena), (yyvsp[-1].cadena), (yyvsp[0].cadena)) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf(buffer, "%s %s %s", (yyvsp[-2].cadena), (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(buffer); 
                                                        free(buffer);
                                                    }
#line 1622 "compiler.tab.c"
    break;

  case 6:
#line 207 "src/compiler_files/compiler.y"
                                            {   size_t needed = snprintf(NULL, 0, "int neighType  = NEUMANN;\n") + 1;
                                                char  *buffer = malloc(needed);
                                                sprintf(buffer, "int neighType  = NEUMANN;\n");
                                                (yyval.cadena) = generateString(buffer);
                                                free(buffer);

                                            }
#line 1634 "compiler.tab.c"
    break;

  case 7:
#line 215 "src/compiler_files/compiler.y"
                                            { neighborhoodType = NEUMANN_T; 
                                              size_t needed = snprintf(NULL, 0, "int neighType = %s;\n", toUpper((yyvsp[0].cadena))) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int neighType = %s;\n", toUpper((yyvsp[0].cadena)));
                                              (yyval.cadena) = generateString(buffer);
                                              free(buffer);
                                            }
#line 1646 "compiler.tab.c"
    break;

  case 8:
#line 223 "src/compiler_files/compiler.y"
                                            { neighborhoodType = MOORE_T; 
                                              size_t needed = snprintf(NULL, 0, "int neighType = %s;\n", toUpper((yyvsp[0].cadena))) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int neighType = %s;\n", toUpper((yyvsp[0].cadena)));
                                              (yyval.cadena) = generateString(buffer);
                                              free(buffer);
                                            }
#line 1658 "compiler.tab.c"
    break;

  case 9:
#line 231 "src/compiler_files/compiler.y"
                                            { neighborhoodType = EXTENDED_T; 
                                              size_t needed = snprintf(NULL, 0, "int neighType = %s;\n", toUpper((yyvsp[0].cadena))) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int neighType = %s;\n", toUpper((yyvsp[0].cadena)));
                                              (yyval.cadena) = generateString(buffer);
                                              free(buffer);
                                            }
#line 1670 "compiler.tab.c"
    break;

  case 10:
#line 240 "src/compiler_files/compiler.y"
                                            { size_t needed = snprintf(NULL, 0,  "#define N 100\n") + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer,  "#define N 100\n");
                                              strcat ( define, buffer); 
                                              free(buffer);
                                            }
#line 1681 "compiler.tab.c"
    break;

  case 11:
#line 247 "src/compiler_files/compiler.y"
                                            { size_t needed = snprintf(NULL, 0,  "#define N %d\n", (yyvsp[0].valor)) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer,  "#define N %d\n", (yyvsp[0].valor));
                                              strcat ( define, buffer); 
                                              free(buffer);
                                            }
#line 1692 "compiler.tab.c"
    break;

  case 12:
#line 255 "src/compiler_files/compiler.y"
                                            { size_t needed = snprintf(NULL, 0, "int nStrain  = 1;\n") + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int nStrain  = 1;\n");
                                              (yyval.cadena) = generateString(buffer);
                                              free(buffer);
                                            }
#line 1703 "compiler.tab.c"
    break;

  case 13:
#line 262 "src/compiler_files/compiler.y"
                                            { numStrains = (yyvsp[0].valor);
                                              size_t needed = snprintf(NULL, 0, "int nStrain  = %d;\n", (yyvsp[0].valor)) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int nStrain  = %d;\n", (yyvsp[0].valor));
                                              (yyval.cadena) = generateString(buffer);
                                              free(buffer);
                                            }
#line 1715 "compiler.tab.c"
    break;

  case 14:
#line 271 "src/compiler_files/compiler.y"
                                            { size_t needed = snprintf(NULL, 0, "int days = 500;\n") + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int days = 500;\n");
                                              (yyval.cadena) = generateString(buffer);
                                              free(buffer);
                                            }
#line 1726 "compiler.tab.c"
    break;

  case 15:
#line 278 "src/compiler_files/compiler.y"
                                            { size_t needed = snprintf(NULL, 0, "int days = %d;\n", (yyvsp[0].valor)) + 1;
                                              char  *buffer = malloc(needed);
                                              sprintf(buffer, "int days = %d;\n", (yyvsp[0].valor));
                                              (yyval.cadena) = generateString(buffer);
                                              free(buffer);
                                            }
#line 1737 "compiler.tab.c"
    break;

  case 16:
#line 288 "src/compiler_files/compiler.y"
                                                     {  size_t needed = snprintf(NULL, 0, "%s", (yyvsp[-1].cadena)) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf(buffer, "%s", (yyvsp[-1].cadena));
                                                        (yyval.cadena) = generateString(buffer);
                                                        free(buffer);
                                                      }
#line 1748 "compiler.tab.c"
    break;

  case 17:
#line 294 "src/compiler_files/compiler.y"
                                                        { size_t needed = snprintf(NULL, 0, "%s %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                          char  *buffer = malloc(needed);
                                                          sprintf(buffer, "%s %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                          (yyval.cadena) = generateString(buffer);
                                                          free(buffer);
                                                        }
#line 1759 "compiler.tab.c"
    break;

  case 18:
#line 304 "src/compiler_files/compiler.y"
                                         { section = CELL_T; }
#line 1765 "compiler.tab.c"
    break;

  case 19:
#line 305 "src/compiler_files/compiler.y"
                                        { section = STATE_T; }
#line 1771 "compiler.tab.c"
    break;

  case 20:
#line 306 "src/compiler_files/compiler.y"
                                        {  }
#line 1777 "compiler.tab.c"
    break;

  case 21:
#line 311 "src/compiler_files/compiler.y"
                                                           { }
#line 1783 "compiler.tab.c"
    break;

  case 22:
#line 312 "src/compiler_files/compiler.y"
                                                           { }
#line 1789 "compiler.tab.c"
    break;

  case 23:
#line 320 "src/compiler_files/compiler.y"
                                              { if(strcmp((yyvsp[-3].cadena), "state") != 0) {
                                                  yyerror();
                                                }
                                                if(Get((yyvsp[-2].cadena)) == NULL) { 
                                                  Add((yyvsp[-2].cadena), "none", section, " ", " "); 
                                                  size_t needed = snprintf(NULL, 0, "%s", (yyvsp[-2].cadena)) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf(buffer, "%s", (yyvsp[-2].cadena));
                                                  char aux[1024];
                                                  sprintf(aux, "#define %s %d\n", toUpper(buffer), counter);
                                                  strcat(define, aux);
                                                  // printf ("%s", define);
                                                  sprintf(drawCell, "void drawCell(vector<vector<Cell>> &cells){ \n for (int i = 0; i < N; i++){ \n for (int j = 0; j < N; j++){ \n switch (cells[i][j].state){ \n case NO_CHANGE: \n glColor3f(1.000000, 1.000000, 1.000000); \n break; \n case %s:\n glColor3f%s; \n break;\n %s } \n glRectd(i, j, i+1, j+1); \n }\n }\n  }\n ", toUpper(buffer), (yyvsp[-1].cadena), (yyvsp[0].cadena)); 
                                                  free(buffer);
                                                }
                                                else { yyerror("ERROR: Duplicate state"); exit(1);}
                                              }
#line 1811 "compiler.tab.c"
    break;

  case 24:
#line 339 "src/compiler_files/compiler.y"
                                                        { 
                                                          char  *buffer = malloc(2);
                                                          sprintf(buffer, " "); 
                                                          (yyval.cadena) = generateString(buffer); 
                                                          free(buffer);
                                                        }
#line 1822 "compiler.tab.c"
    break;

  case 25:
#line 346 "src/compiler_files/compiler.y"
                                                        { if(strcmp((yyvsp[-3].cadena), "state") != 0) {
                                                              yyerror();
                                                          }
                                                          if(Get((yyvsp[-2].cadena)) == NULL) { 
                                                            Add((yyvsp[-2].cadena), "int", section, "0", "0"); 

                                                            size_t needed = snprintf(NULL, 0, "%s", (yyvsp[-2].cadena)) + 1;
                                                            char  *aux1 = malloc(needed);
                                                            sprintf(aux1, "%s", (yyvsp[-2].cadena));
                                                            
                                                            needed = snprintf(NULL, 0, "#define %s %d\n", toUpper(aux1), counter) + 1;
                                                            char  *aux2 = malloc(needed);
                                                            sprintf(aux2, "#define %s %d\n", toUpper(aux1), counter);
                                                            strcat(define, aux2);
                                                            counter++;

                                                            needed = snprintf(NULL, 0, "case %s:\n glColor3f%s; \n break;\n %s",toUpper(aux1), (yyvsp[-1].cadena), (yyvsp[0].cadena)) + 1;
                                                            char  *buffer = malloc(needed);
                                                            sprintf(buffer, "case %s:\n glColor3f%s; \n break;\n %s",toUpper(aux1), (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                            (yyval.cadena) = generateString(buffer);
                                                            free(buffer);
                                                            free(aux1);
                                                            free(aux2);
                                                          }
                                                          else { yyerror("ERROR: duplicate variable"); exit(1);}
                                                       }
#line 1853 "compiler.tab.c"
    break;

  case 26:
#line 374 "src/compiler_files/compiler.y"
                                                                       { size_t needed = snprintf(NULL, 0, "(%s,%s,%s)", (yyvsp[-5].cadena), (yyvsp[-3].cadena), (yyvsp[-1].cadena)) + 1;
                                                                          char  *buffer = malloc(needed);
                                                                          sprintf(buffer, "(%s,%s,%s)", (yyvsp[-5].cadena), (yyvsp[-3].cadena), (yyvsp[-1].cadena));
                                                                          (yyval.cadena) = generateString(buffer);
                                                                          free(buffer);
                                                                        }
#line 1864 "compiler.tab.c"
    break;

  case 27:
#line 382 "src/compiler_files/compiler.y"
                                                      { char *eptr;
                                                          size_t needed = snprintf(NULL, 0, "%s", (yyvsp[0].cadena)) + 1;
                                                          char  *aux = malloc(needed);
                                                          sprintf(aux, " %s", (yyvsp[0].cadena));
                                                          double number = strtod(aux, &eptr);
                                                          free(aux);
                                                          needed = snprintf(NULL, 0, "%f", number) + 1;
                                                          char  *buffer = malloc(needed);
                                                          sprintf(buffer, "%f", number); 
                                                          if (number > 1.0) { 
                                                            yywarning("WARNING: rgb color component must be between 0 and 1. By default the value will be 1.0");
                                                            sprintf(buffer, "1.0");
                                                            (yyval.cadena) = generateString(buffer); 
                                                          }
                                                          else if (number < 0.0) { 
                                                            yywarning("WARNING: rgb color component must be between 0 and 1. By default the value will be 0.0");
                                                            sprintf(buffer, "0.0");
                                                            (yyval.cadena) = generateString(buffer); 
                                                          }
                                                          (yyval.cadena) = generateString(buffer); 
                                                          free(buffer);
                                                        }
#line 1891 "compiler.tab.c"
    break;

  case 28:
#line 407 "src/compiler_files/compiler.y"
                                                      { if(Get((yyvsp[-2].cadena)) == NULL) { //No existe una variable llamda con el valo que lleva IDENTIF
                                                          //Se añade la variable a la lista de variables identificando si es global o atributo de célula
                                                          Add((yyvsp[-2].cadena), "bool", section, (yyvsp[0].cadena), (yyvsp[0].cadena));
                                                          size_t needed = snprintf(NULL, 0,  "%s %s = %s;\n", (yyvsp[-3].cadena), (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                          char  *buffer = malloc(needed);
                                                          sprintf (buffer, "%s %s = %s;\n", (yyvsp[-3].cadena), (yyvsp[-2].cadena), (yyvsp[0].cadena)); //Traducción a C: bool identif = valor;
                                                          (yyval.cadena) = generateString(buffer);
                                                          free(buffer);
                                                          clean();
                                                        }
                                                        else { //Existe una variable on ese nombre
                                                          if(strcmp((yyvsp[-3].cadena), "state") == 0 || strcmp((yyvsp[-3].cadena), "alive") == 0 || strcmp((yyvsp[-3].cadena), "infected") == 0){
                                                            yyerror("ERROR: %s is a reserved variable", (yyvsp[-3].cadena)); exit(1);
                                                          } else {
                                                            yyerror("ERROR: duplicate variable"); exit(1);
                                                          }
                                                        }
                                                        
                                                      }
#line 1915 "compiler.tab.c"
    break;

  case 29:
#line 426 "src/compiler_files/compiler.y"
                                                     { if(Get((yyvsp[0].cadena)) == NULL) { 
                                                        Add((yyvsp[0].cadena), "bool", section, "false", "false"); 
                                                        size_t needed = snprintf(NULL, 0,  "%s %s = false;\n", (yyvsp[-1].cadena), (yyvsp[0].cadena)) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer, "%s %s = false;\n", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(buffer);
                                                        free(buffer);
                                                        clean();
                                                      }
                                                      else { 
                                                        if(strcmp((yyvsp[-1].cadena), "state") == 0 || strcmp((yyvsp[-1].cadena), "alive") == 0 || strcmp((yyvsp[-1].cadena), "infected") == 0){
                                                          yyerror("ERROR: %s is a reserved variable", (yyvsp[-1].cadena)); exit(1);
                                                        } else {
                                                          yyerror("ERROR: duplicate variable"); exit(1);
                                                        }
                                                      }
                                                      
                                                    }
#line 1938 "compiler.tab.c"
    break;

  case 30:
#line 445 "src/compiler_files/compiler.y"
                                                    { if(Get((yyvsp[-2].cadena)) == NULL) { 
                                                        Add((yyvsp[-2].cadena), "int", section, (yyvsp[0].cadena), (yyvsp[0].cadena)); 
                                                        size_t needed = snprintf(NULL, 0,   "%s %s = %s;\n", (yyvsp[-3].cadena), (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer,  "%s %s = %s;\n", (yyvsp[-3].cadena), (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(buffer);
                                                        free(buffer);
                                                        clean();
                                                      }
                                                      else { 
                                                        if(strcmp((yyvsp[-3].cadena), "state") == 0 || strcmp((yyvsp[-3].cadena), "alive") == 0 || strcmp((yyvsp[-3].cadena), "infected") == 0){
                                                          yyerror("ERROR: %s is a reserved variable", (yyvsp[-3].cadena)); exit(1);
                                                        } else {
                                                          yyerror("ERROR:%s is a duplicate variable", (yyvsp[-3].cadena)); exit(1);
                                                        }
                                                      }
                                                    }
#line 1960 "compiler.tab.c"
    break;

  case 31:
#line 462 "src/compiler_files/compiler.y"
                                                    { if(Get((yyvsp[0].cadena)) == NULL) { 
                                                        Add((yyvsp[0].cadena), "int", section, "0", "0"); 
                                                        size_t needed = snprintf(NULL, 0,   "%s %s = 0;\n", (yyvsp[-1].cadena), (yyvsp[0].cadena)) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer,  "%s %s = 0;\n", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(buffer);
                                                        free(buffer);
                                                        clean();
                                                      }
                                                      else { 
                                                        if(strcmp((yyvsp[-1].cadena), "state") == 0 || strcmp((yyvsp[-1].cadena), "alive") == 0 || strcmp((yyvsp[-1].cadena), "infected") == 0){
                                                          yyerror("ERROR: %s is a reserved variable", (yyvsp[-1].cadena)); exit(1);
                                                        } else {
                                                          yyerror("ERROR:%s is a duplicate variable", (yyvsp[-1].cadena)); exit(1);
                                                        }
                                                      }
                                                    }
#line 1982 "compiler.tab.c"
    break;

  case 32:
#line 480 "src/compiler_files/compiler.y"
                                                    { if(Get((yyvsp[-2].cadena)) == NULL) { 
                                                        Add((yyvsp[-2].cadena), "double", section, (yyvsp[0].cadena), (yyvsp[0].cadena)); 
                                                        size_t needed = snprintf(NULL, 0,   "%s %s = %s;\n", (yyvsp[-3].cadena), (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer,  "%s %s = %s;\n", (yyvsp[-3].cadena), (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(buffer);
                                                        free(buffer);
                                                        clean();
                                                      }
                                                      else { 
                                                        if(strcmp((yyvsp[-3].cadena), "state") == 0 || strcmp((yyvsp[-3].cadena), "alive") == 0 || strcmp((yyvsp[-3].cadena), "infected") == 0){
                                                          yyerror("ERROR: %s is a reserved variable", (yyvsp[-3].cadena)); exit(1);
                                                        } else {
                                                          yyerror("ERROR:%s is a duplicate variable", (yyvsp[-3].cadena)); exit(1);
                                                        }
                                                      }
                                                    }
#line 2004 "compiler.tab.c"
    break;

  case 33:
#line 497 "src/compiler_files/compiler.y"
                                                    { if(Get((yyvsp[0].cadena)) == NULL) { 
                                                        Add((yyvsp[0].cadena), "double", section, "0.0", "0.0"); 
                                                        size_t needed = snprintf(NULL, 0,   "%s %s = 0.0;\n", (yyvsp[-1].cadena), (yyvsp[0].cadena)) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer,  "%s %s = 0.0;\n", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(buffer);
                                                        free(buffer);
                                                        clean();
                                                      }
                                                      else { 
                                                        if(strcmp((yyvsp[-1].cadena), "state") == 0 || strcmp((yyvsp[-1].cadena), "alive") == 0 || strcmp((yyvsp[-1].cadena), "infected") == 0){
                                                          yyerror("ERROR: %s is a reserved variable", (yyvsp[-1].cadena)); exit(1);
                                                        } else {
                                                          yyerror("ERROR:%s is a duplicate variable", (yyvsp[-1].cadena)); exit(1);
                                                        }
                                                      }
                                                    }
#line 2026 "compiler.tab.c"
    break;

  case 34:
#line 517 "src/compiler_files/compiler.y"
                                                                           {  size_t needed = snprintf(NULL, 0, "if(currentTick >= %d) {\n %s %s \n } \n for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n } \n ", (yyvsp[-4].valor), beginStrain, (yyvsp[-1].cadena), (yyvsp[-6].cadena), (yyvsp[-6].cadena), (yyvsp[-6].cadena)) + 1;
                                                                              char  *buffer = malloc(needed);
                                                                              sprintf (buffer,  "if(currentTick >= %d) {\n %s %s \n } \n for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n } \n ", (yyvsp[-4].valor), beginStrain, (yyvsp[-1].cadena), (yyvsp[-6].cadena), (yyvsp[-6].cadena), (yyvsp[-6].cadena));
                                                                              (yyval.cadena) = generateString(buffer);
                                                                              free(buffer);
                                                                              if(Get((yyvsp[-6].cadena)) == NULL) { 
                                                                                Add((yyvsp[-6].cadena), "null", STRAIN_T, " ", " "); 
                                                                              }
                                                                            }
#line 2040 "compiler.tab.c"
    break;

  case 35:
#line 526 "src/compiler_files/compiler.y"
                                                                           {  size_t needed = snprintf(NULL, 0, "if(currentTick >= %d) {\n %s %s \n } \n for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n } \n %s ", (yyvsp[-5].valor), beginStrain, (yyvsp[-2].cadena), (yyvsp[-7].cadena), (yyvsp[-7].cadena), (yyvsp[-7].cadena), (yyvsp[0].cadena)) + 1;
                                                                              char  *buffer = malloc(needed);
                                                                              sprintf (buffer,  "if(currentTick >= %d) {\n %s %s \n } \n for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n  } \n %s ", (yyvsp[-5].valor), beginStrain, (yyvsp[-2].cadena), (yyvsp[-7].cadena), (yyvsp[-7].cadena), (yyvsp[-7].cadena), (yyvsp[0].cadena));
                                                                              (yyval.cadena) = generateString(buffer);
                                                                              free(buffer);
                                                                              if(Get((yyvsp[-7].cadena)) == NULL) { 
                                                                                Add((yyvsp[-7].cadena), "null", STRAIN_T, " ", " "); 
                                                                              }
                                                                            }
#line 2054 "compiler.tab.c"
    break;

  case 36:
#line 535 "src/compiler_files/compiler.y"
                                                                           {  size_t needed = snprintf(NULL, 0, "if(currentTick >= 0) {\n %s %s \n } \n for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n } \n ", beginStrain, (yyvsp[-1].cadena), (yyvsp[-5].cadena), (yyvsp[-5].cadena), (yyvsp[-5].cadena)) + 1;
                                                                              char  *buffer = malloc(needed);
                                                                              sprintf (buffer,  "if(currentTick >= 0) {\n %s %s \n } \n for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n } \n ", beginStrain, (yyvsp[-1].cadena), (yyvsp[-5].cadena), (yyvsp[-5].cadena), (yyvsp[-5].cadena));
                                                                              (yyval.cadena) = generateString(buffer);
                                                                              free(buffer);
                                                                              if(Get((yyvsp[-5].cadena)) == NULL) { 
                                                                                Add((yyvsp[-5].cadena), "null", STRAIN_T, " ", " "); 
                                                                              } 
                                                                            }
#line 2068 "compiler.tab.c"
    break;

  case 37:
#line 544 "src/compiler_files/compiler.y"
                                                                           {  size_t needed = snprintf(NULL, 0, "if(currentTick >= 0) {\n %s %s \n } for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n \n } \n %s ", beginStrain, (yyvsp[-2].cadena), (yyvsp[-6].cadena), (yyvsp[-6].cadena), (yyvsp[-6].cadena), (yyvsp[0].cadena)) + 1;
                                                                              char  *buffer = malloc(needed);
                                                                              sprintf (buffer,  "if(currentTick >= 0) {\n %s %s \n } for(int i=0; i<N; i++){\n    for(int j=0; j<N; j++){\n        results[cells[i][j].state]++;\n    }\n}\n%s << currentTick ;\nfor(int i=0; i<nStates;i++){\n    %s <<  \",\" << results[i];\n}\n%s << \"\\n\";\n \n } \n %s ", beginStrain, (yyvsp[-2].cadena), (yyvsp[-6].cadena), (yyvsp[-6].cadena), (yyvsp[-6].cadena), (yyvsp[0].cadena));
                                                                              (yyval.cadena) = generateString(buffer);
                                                                              free(buffer);
                                                                              if(Get((yyvsp[-6].cadena)) == NULL) { 
                                                                                Add((yyvsp[-6].cadena), "null", STRAIN_T, " ", " "); 
                                                                              }
                                                                            }
#line 2082 "compiler.tab.c"
    break;

  case 38:
#line 556 "src/compiler_files/compiler.y"
                                                { size_t needed = snprintf(NULL, 0, "%s \n }", (yyvsp[0].cadena)) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer,  "%s \n }", (yyvsp[0].cadena));
                                                  (yyval.cadena) = generateString(buffer);
                                                  free(buffer);
                                                }
#line 2093 "compiler.tab.c"
    break;

  case 39:
#line 563 "src/compiler_files/compiler.y"
                                                { size_t needed = snprintf(NULL, 0, "%s \n %s", (yyvsp[-1].cadena), (yyvsp[0].cadena)) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer,  "%s \n %s", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                  (yyval.cadena) = generateString(buffer);
                                                  free(buffer);
                                                  }
#line 2104 "compiler.tab.c"
    break;

  case 40:
#line 572 "src/compiler_files/compiler.y"
                                                                  { size_t needed = snprintf(NULL, 0, "if( %s ) {\n %s ", (yyvsp[-3].cadena), (yyvsp[0].cadena)) + 1;
                                                                    char  *buffer = malloc(needed);
                                                                    sprintf (buffer,  "if( %s ) {\n %s ", (yyvsp[-3].cadena), (yyvsp[0].cadena));
                                                                    (yyval.cadena) = generateString(buffer);
                                                                    free(buffer);
                                                                    clean();
                                                                  }
#line 2116 "compiler.tab.c"
    break;

  case 41:
#line 581 "src/compiler_files/compiler.y"
                                                                    { size_t needed = snprintf(NULL, 0, "%s \n}\n",(yyvsp[-1].cadena)) + 1;
                                                                      char  *buffer = malloc(needed);
                                                                      sprintf (buffer,  "%s \n}\n",(yyvsp[-1].cadena));
                                                                      (yyval.cadena) = generateString(buffer);
                                                                      free(buffer);
                                                                      clean();
                                                                    }
#line 2128 "compiler.tab.c"
    break;

  case 42:
#line 589 "src/compiler_files/compiler.y"
                                                                     {  size_t needed = snprintf(NULL, 0, "%s \n} else if ( %s ) {\n %s", (yyvsp[-8].cadena), (yyvsp[-3].cadena), (yyvsp[0].cadena)) + 1;
                                                                        char  *buffer = malloc(needed);
                                                                        sprintf (buffer,  "%s \n} else if ( %s ) {\n %s", (yyvsp[-8].cadena), (yyvsp[-3].cadena), (yyvsp[0].cadena));
                                                                        (yyval.cadena) = generateString(buffer);
                                                                        free(buffer);
                                                                        clean();
                                                                      }
#line 2140 "compiler.tab.c"
    break;

  case 43:
#line 597 "src/compiler_files/compiler.y"
                                                                      { size_t needed = snprintf(NULL, 0, "%s \n} else {\n %s \n}", (yyvsp[-5].cadena), (yyvsp[-1].cadena)) + 1;
                                                                        char  *buffer = malloc(needed);
                                                                        sprintf (buffer,  "%s \n} else {\n %s \n}", (yyvsp[-5].cadena), (yyvsp[-1].cadena));
                                                                        (yyval.cadena) = generateString(buffer);
                                                                        free(buffer);
                                                                        clean();
                                                                      }
#line 2152 "compiler.tab.c"
    break;

  case 44:
#line 609 "src/compiler_files/compiler.y"
                                                      {  (yyval.cadena) = generateString(" "); }
#line 2158 "compiler.tab.c"
    break;

  case 45:
#line 611 "src/compiler_files/compiler.y"
                                                      { size_t needed = snprintf(NULL, 0, "%s \n %s", (yyvsp[-1].cadena), (yyvsp[0].cadena)) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer, "%s \n %s", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(buffer);
                                                        free(buffer);
                                                      }
#line 2169 "compiler.tab.c"
    break;

  case 46:
#line 618 "src/compiler_files/compiler.y"
                                                      { size_t needed = snprintf(NULL, 0, "%s \n %s", (yyvsp[-1].cadena), (yyvsp[0].cadena)) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer, "%s \n %s", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(buffer);
                                                        free(buffer);
                                                      }
#line 2180 "compiler.tab.c"
    break;

  case 47:
#line 624 "src/compiler_files/compiler.y"
                                                      { (yyval.cadena) = generateString("continue;"); }
#line 2186 "compiler.tab.c"
    break;

  case 48:
#line 628 "src/compiler_files/compiler.y"
                                                      { section = INIT_T; 
                                                        hasState = 0;
                                                        clean();
                                                     }
#line 2195 "compiler.tab.c"
    break;

  case 49:
#line 632 "src/compiler_files/compiler.y"
                                                      { if (hasState == 0) {
                                                          yyerror("ERROR: Init funcion doesn't have an assigment to the variable \"state\"");
                                                          exit(1);
                                                        } else {
                                                          size_t needed = snprintf(NULL, 0, "%s }", (yyvsp[-1].cadena)) + 1;
                                                          char  *buffer = malloc(needed);
                                                          sprintf (buffer, "%s }", (yyvsp[-1].cadena));
                                                          strcat(infectFunction, buffer);
                                                          free(buffer);
                                                        }
                                                      }
#line 2211 "compiler.tab.c"
    break;

  case 50:
#line 646 "src/compiler_files/compiler.y"
                                                      { (yyval.cadena) = generateString(" "); }
#line 2217 "compiler.tab.c"
    break;

  case 51:
#line 648 "src/compiler_files/compiler.y"
                                                      { size_t needed = snprintf(NULL, 0, "%s \n %s \n", (yyvsp[-1].cadena), (yyvsp[0].cadena)) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer, "%s \n %s \n", (yyvsp[-1].cadena), (yyvsp[0].cadena));
                                                        (yyval.cadena) = generateString(buffer);
                                                        free(buffer);
                                                      }
#line 2228 "compiler.tab.c"
    break;

  case 52:
#line 656 "src/compiler_files/compiler.y"
                                                             { clean(); }
#line 2234 "compiler.tab.c"
    break;

  case 53:
#line 657 "src/compiler_files/compiler.y"
                                                             { nodeList *p = Get((yyvsp[-3].cadena));
                                                              if(p == NULL) { 
                                                                yyerror("ERROR: Variable \"%s\" doesn't exist", (yyvsp[-3].cadena));
                                                                exit(1);
                                                              } else {
                                                                if(strcmp((yyvsp[-3].cadena), "state")==0) { 
                                                                  hasState = 1; 
                                                                }
                                                                if (strcmp(p->type,"int") == 0 && foundType(INTEGER_T) == 1){
                                                                  yywarning("WARNING: Maybe you're assigning a wrong type to variable \"%s\"", (yyvsp[-3].cadena));
                                                                } else if (strcmp(p->type,"bool") == 0 && foundType(BOOLEAN_T == 1)){
                                                                  yywarning("WARNING: Maybe you're assigning a wrong type to variable \"%s\"", (yyvsp[-3].cadena));
                                                                } else if (strcmp(p->type,"double") && foundType(DOUBLE_T == 1)) {
                                                                  yywarning("WARNING: Maybe you're assigning a wrong type to variable \"%s\"", (yyvsp[-3].cadena));
                                                                } 
                                                                clean();
                                                                size_t needed = snprintf(NULL, 0, "cells[i][j].%s = %s; ", (yyvsp[-3].cadena), (yyvsp[-1].cadena)) + 1;
                                                                char  *buffer = malloc(needed);
                                                                if(p->section == CELL_T){
                                                                  if (section != INIT_T ) {
                                                                    sprintf(buffer, "cells[i][j].%s = %s; ", (yyvsp[-3].cadena), (yyvsp[-1].cadena));
                                                                  } else {
                                                                    sprintf(buffer, "%s = %s; ", (yyvsp[-3].cadena), (yyvsp[-1].cadena));
                                                                  }
                                                                  (yyval.cadena) = generateString(buffer); 
                                                                } else if(p->section == GLOBAL_T) {
                                                                  // strcpy(p->actualValue, $4);
                                                                  sprintf(buffer, "%s = %s; ", (yyvsp[-3].cadena), (yyvsp[-1].cadena));
                                                                  (yyval.cadena) = generateString(buffer); 
                                                                }
                                                                free(buffer);
                                                              }
                                                            }
#line 2272 "compiler.tab.c"
    break;

  case 54:
#line 693 "src/compiler_files/compiler.y"
                                                  {  }
#line 2278 "compiler.tab.c"
    break;

  case 55:
#line 694 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s + %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s + %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer);
                                                  }
#line 2289 "compiler.tab.c"
    break;

  case 56:
#line 701 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s - %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s - %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer);
                                                  }
#line 2300 "compiler.tab.c"
    break;

  case 57:
#line 708 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s * %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s * %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer); }
#line 2310 "compiler.tab.c"
    break;

  case 58:
#line 714 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s / %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s / %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer); }
#line 2320 "compiler.tab.c"
    break;

  case 59:
#line 720 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s %% %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s %% %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer); }
#line 2330 "compiler.tab.c"
    break;

  case 60:
#line 726 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s && %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s && %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer); }
#line 2340 "compiler.tab.c"
    break;

  case 61:
#line 732 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s || %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s || %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer); }
#line 2350 "compiler.tab.c"
    break;

  case 62:
#line 738 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s != %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s != %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer); }
#line 2360 "compiler.tab.c"
    break;

  case 63:
#line 744 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s == %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s == %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer); }
#line 2370 "compiler.tab.c"
    break;

  case 64:
#line 750 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s < %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s < %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer); }
#line 2380 "compiler.tab.c"
    break;

  case 65:
#line 756 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s <= %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s <= %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer); }
#line 2390 "compiler.tab.c"
    break;

  case 66:
#line 762 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s > %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s > %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer); }
#line 2400 "compiler.tab.c"
    break;

  case 67:
#line 768 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s >= %s", (yyvsp[-2].cadena), (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s >= %s", (yyvsp[-2].cadena), (yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer); }
#line 2410 "compiler.tab.c"
    break;

  case 68:
#line 774 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "- %s", (yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "- %s",(yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer); }
#line 2420 "compiler.tab.c"
    break;

  case 69:
#line 780 "src/compiler_files/compiler.y"
                                                  { size_t needed = snprintf(NULL, 0, "%s",(yyvsp[0].cadena)) + 1;
                                                    char  *buffer = malloc(needed);
                                                    sprintf (buffer, "%s",(yyvsp[0].cadena));
                                                    (yyval.cadena) = generateString(buffer);
                                                    free(buffer); }
#line 2430 "compiler.tab.c"
    break;

  case 70:
#line 789 "src/compiler_files/compiler.y"
                                                    {  }
#line 2436 "compiler.tab.c"
    break;

  case 71:
#line 804 "src/compiler_files/compiler.y"
                                                    { nodeList *p = Get((yyvsp[0].cadena));
                                                      if(p == NULL) { 
                                                        if (strcmp((yyvsp[0].cadena), "currenttick") == 0) {
                                                          typeExpression[i] = INTEGER_T;
                                                          i++;
                                                          (yyval.cadena) = generateString("currentTick");
                                                        } else {
                                                          yyerror("ERROR: Variable \"%s\" doesn't exist", (yyvsp[0].cadena));
                                                          exit(1);
                                                        }
                                                      } else {
                                                        
                                                        if (strcmp(p->type, "int") == 0) {
                                                          typeExpression[i] = INTEGER_T;
                                                          i++;
                                                        } else if (strcmp(p->type, "bool") == 0) {
                                                          
                                                          typeExpression[i] = BOOLEAN_T;
                                                          i++;
                                                        } else if (strcmp(p->type, "double") == 0) {
                                                          typeExpression[i] = DOUBLE_T;
                                                          i++;
                                                        }
                                                        size_t needed = snprintf(NULL, 0, "cells[i][j].%s", (yyvsp[0].cadena)) + 1;
                                                        char  *buffer = malloc(needed);
                                                        if(p->section == CELL_T){
                                                          sprintf(buffer, "cells[i][j].%s", (yyvsp[0].cadena));
                                                        } else if (p->section == GLOBAL_T){
                                                          sprintf(buffer, "%s", (yyvsp[0].cadena));
                                                        } else if (p->section == STATE_T){
                                                          sprintf(buffer, "%s", toUpper((yyvsp[0].cadena)));
                                                        }
                                                        (yyval.cadena) = generateString(buffer);
                                                        free(buffer); 
                                                      }
                                                    }
#line 2477 "compiler.tab.c"
    break;

  case 72:
#line 841 "src/compiler_files/compiler.y"
                                                    { typeExpression[i] = DOUBLE_T;
                                                      i++;
                                                      (yyval.cadena) = generateString("((rand() % (1001))/1000.0)"); }
#line 2485 "compiler.tab.c"
    break;

  case 73:
#line 845 "src/compiler_files/compiler.y"
                                                    { typeExpression[i] = INTEGER_T;
                                                      i++;
                                                      size_t needed = snprintf(NULL, 0, "%s", (yyvsp[0].cadena)) + 1;
                                                      char  *buffer = malloc(needed);
                                                      sprintf (buffer, "%s", (yyvsp[0].cadena));
                                                      (yyval.cadena) = generateString(buffer);
                                                      free(buffer); }
#line 2497 "compiler.tab.c"
    break;

  case 74:
#line 853 "src/compiler_files/compiler.y"
                                                    { typeExpression[i] = DOUBLE_T;
                                                      i++;
                                                      size_t needed = snprintf(NULL, 0, "%s", (yyvsp[0].cadena)) + 1;
                                                      char  *buffer = malloc(needed);
                                                      sprintf (buffer, "%s", (yyvsp[0].cadena));
                                                      (yyval.cadena) = generateString(buffer);
                                                      free(buffer);  }
#line 2509 "compiler.tab.c"
    break;

  case 75:
#line 861 "src/compiler_files/compiler.y"
                                                    { typeExpression[i] = BOOLEAN_T;
                                                      i++;
                                                      size_t needed = snprintf(NULL, 0, "%s", (yyvsp[0].cadena)) + 1;
                                                      char  *buffer = malloc(needed);
                                                      sprintf (buffer, "%s", (yyvsp[0].cadena));
                                                      (yyval.cadena) = generateString(buffer);
                                                      free(buffer);  }
#line 2521 "compiler.tab.c"
    break;

  case 76:
#line 871 "src/compiler_files/compiler.y"
                                                        { if( Get((yyvsp[-3].cadena))->section == CELL_T ) {
                                                            size_t needed = snprintf(NULL, 0, "count(c_neighbours, string(\"%s\"), std::to_string(%s), cells)", (yyvsp[-3].cadena), (yyvsp[-1].cadena)) + 1;
                                                            char  *buffer = malloc(needed);
                                                            sprintf (buffer, "count(c_neighbours, string(\"%s\"), std::to_string(%s), cells)", (yyvsp[-3].cadena), (yyvsp[-1].cadena));
                                                            (yyval.cadena) = generateString(buffer);
                                                            free(buffer);  
                                                          } else {
                                                            yyerror("ERROR: Variable \"%s\" isn't an atribute of a cell type", (yyvsp[-3].cadena));
                                                            exit(1);
                                                          }
                                                        }
#line 2537 "compiler.tab.c"
    break;

  case 77:
#line 883 "src/compiler_files/compiler.y"
                                                    { nodeList *p = Get((yyvsp[0].cadena));
                                                      if(p == NULL) { 
                                                        yyerror( "ERROR: Variable \"%s\" doesn't exist", (yyvsp[0].cadena));
                                                        exit(1);
                                                      } else {
                                                        if(p->section == CELL_T){
                                                          if (strcmp(p->type, "int") == 0) {
                                                            typeExpression[i] = INTEGER_T;
                                                            i++;
                                                          } else if (strcmp(p->type, "bool") == 0) {
                                                            typeExpression[i] = BOOLEAN_T;
                                                            i++;
                                                          } else if (strcmp(p->type, "double") == 0) {
                                                            typeExpression[i] = DOUBLE_T;
                                                            i++;
                                                          }
                                                          size_t needed = snprintf(NULL, 0, "cells%s.%s", (yyvsp[-3].cadena), (yyvsp[0].cadena)) + 1;
                                                          char  *buffer = malloc(needed);
                                                          sprintf (buffer, "cells%s.%s", (yyvsp[-3].cadena), (yyvsp[0].cadena));
                                                          (yyval.cadena) = generateString(buffer);
                                                          free(buffer);  
                                                        } else {
                                                          yyerror("ERROR: \"%s\" not a cell variable", (yyvsp[0].cadena));
                                                          exit(1);
                                                        }
                                                      } 
                                                    }
#line 2569 "compiler.tab.c"
    break;

  case 78:
#line 911 "src/compiler_files/compiler.y"
                                                     {  size_t needed = snprintf(NULL, 0, "( %s )", (yyvsp[-1].cadena)) + 1;
                                                        char  *buffer = malloc(needed);
                                                        sprintf (buffer, "( %s )", (yyvsp[-1].cadena));
                                                        (yyval.cadena) = generateString(buffer);
                                                        free(buffer); }
#line 2579 "compiler.tab.c"
    break;

  case 79:
#line 919 "src/compiler_files/compiler.y"
                                                { size_t needed = snprintf(NULL, 0, "%s", (yyvsp[0].cadena)) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "%s", (yyvsp[0].cadena));
                                                  (yyval.cadena) = generateString(buffer);
                                                  free(buffer); 
                                                }
#line 2590 "compiler.tab.c"
    break;

  case 80:
#line 926 "src/compiler_files/compiler.y"
                                                { size_t needed = snprintf(NULL, 0, "%s", (yyvsp[0].cadena)) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "%s", (yyvsp[0].cadena));
                                                  (yyval.cadena) = generateString(buffer);
                                                  free(buffer); 
                                                }
#line 2601 "compiler.tab.c"
    break;

  case 81:
#line 934 "src/compiler_files/compiler.y"
                                                { size_t needed = snprintf(NULL, 0, "%d", (yyvsp[0].valor)) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "%d", (yyvsp[0].valor));
                                                  (yyval.cadena) = generateString(buffer);
                                                  free(buffer); 
                                                }
#line 2612 "compiler.tab.c"
    break;

  case 82:
#line 940 "src/compiler_files/compiler.y"
                                                { size_t needed = snprintf(NULL, 0, "-%d", (yyvsp[0].valor)) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "-%d", (yyvsp[0].valor));
                                                  (yyval.cadena) = generateString(buffer);
                                                  free(buffer); 
                                                }
#line 2623 "compiler.tab.c"
    break;

  case 83:
#line 948 "src/compiler_files/compiler.y"
                                              { size_t needed = snprintf(NULL, 0, "%d.%d", (yyvsp[-2].valor), (yyvsp[0].valor)) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "%d.%d", (yyvsp[-2].valor), (yyvsp[0].valor));
                                                  (yyval.cadena) = generateString(buffer);
                                                  free(buffer);  
                                                }
#line 2634 "compiler.tab.c"
    break;

  case 84:
#line 955 "src/compiler_files/compiler.y"
                                                { size_t needed = snprintf(NULL, 0, "%d.0", (yyvsp[0].valor)) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "%d.0", (yyvsp[0].valor));
                                                  (yyval.cadena) = generateString(buffer);
                                                  free(buffer);
                                                }
#line 2645 "compiler.tab.c"
    break;

  case 85:
#line 961 "src/compiler_files/compiler.y"
                                              { size_t needed = snprintf(NULL, 0, "-%d.0", (yyvsp[0].valor)) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "-%d.0", (yyvsp[0].valor));
                                                  (yyval.cadena) = generateString(buffer);
                                                  free(buffer); 
                                                }
#line 2656 "compiler.tab.c"
    break;

  case 86:
#line 967 "src/compiler_files/compiler.y"
                                                { size_t needed = snprintf(NULL, 0, "-%d.%d", (yyvsp[-2].valor), (yyvsp[0].valor)) + 1;
                                                  char  *buffer = malloc(needed);
                                                  sprintf (buffer, "-%d.%d", (yyvsp[-2].valor), (yyvsp[0].valor));
                                                  (yyval.cadena) = generateString(buffer);
                                                  free(buffer);  
                                                }
#line 2667 "compiler.tab.c"
    break;

  case 87:
#line 977 "src/compiler_files/compiler.y"
                                                    { (yyval.cadena) = generateString("[c_neighbours[1][0]][c_neighbours[1][1]]");}
#line 2673 "compiler.tab.c"
    break;

  case 88:
#line 978 "src/compiler_files/compiler.y"
                                                    { (yyval.cadena) = generateString("[c_neighbours[5][0]][c_neighbours[5][1]]");}
#line 2679 "compiler.tab.c"
    break;

  case 89:
#line 979 "src/compiler_files/compiler.y"
                                                    { (yyval.cadena) = generateString("[c_neighbours[7][0]][c_neighbours[7][1]]");}
#line 2685 "compiler.tab.c"
    break;

  case 90:
#line 980 "src/compiler_files/compiler.y"
                                                    { (yyval.cadena) = generateString("[c_neighbours[3][0]][c_neighbours[3][1]]");}
#line 2691 "compiler.tab.c"
    break;

  case 91:
#line 981 "src/compiler_files/compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T) {
                                                        (yyval.cadena) = generateString("[c_neighbours[2][0]][c_neighbours[2][1]]");
                                                      } else {
                                                          yyerror("ERROR: \"%s\" not allow in this type of neighborhood", (yyvsp[0].cadena));
                                                          exit(1);
                                                      }
                                                    }
#line 2703 "compiler.tab.c"
    break;

  case 92:
#line 988 "src/compiler_files/compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T) {
                                                        (yyval.cadena) = generateString("[c_neighbours[0][0]][c_neighbours[0][1]]");
                                                      } else {
                                                          yyerror("ERROR: \"%s\" not allow in this type of neighborhood", (yyvsp[0].cadena));
                                                          exit(1);
                                                      }
                                                    }
#line 2715 "compiler.tab.c"
    break;

  case 93:
#line 995 "src/compiler_files/compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T) {
                                                        (yyval.cadena) = generateString("[c_neighbours[4][0]][c_neighbours[4][1]]");
                                                      } else {
                                                          yyerror("ERROR: \"%s\" not allow in this type of neighborhood", (yyvsp[0].cadena));
                                                          exit(1);
                                                      }
                                                    }
#line 2727 "compiler.tab.c"
    break;

  case 94:
#line 1002 "src/compiler_files/compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T) {
                                                        (yyval.cadena) = generateString("[c_neighbours[6][0]][c_neighbours[6][1]]");
                                                      } else {
                                                          yyerror("ERROR: \"%s\" not allow in this type of neighborhood", (yyvsp[0].cadena));
                                                          exit(1);
                                                      }
                                                    }
#line 2739 "compiler.tab.c"
    break;

  case 95:
#line 1009 "src/compiler_files/compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        (yyval.cadena) = generateString("[c_neighbours[8][0]][c_neighbours[8][1]]");
                                                      } else {
                                                          yyerror("ERROR: \"%s\" not allow in this type of neighborhood", (yyvsp[0].cadena));
                                                          exit(1);
                                                      }
                                                    }
#line 2751 "compiler.tab.c"
    break;

  case 96:
#line 1016 "src/compiler_files/compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        (yyval.cadena) = generateString("[c_neighbours[10][0]][c_neighbours[10][1]]");
                                                      } else {
                                                          yyerror("ERROR: \"%s\" not allow in this type of neighborhood", (yyvsp[0].cadena));
                                                          exit(1);
                                                      }
                                                    }
#line 2763 "compiler.tab.c"
    break;

  case 97:
#line 1023 "src/compiler_files/compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        (yyval.cadena) = generateString("[c_neighbours[11][0]][c_neighbours[11][1]]");
                                                      } else {
                                                          yyerror("ERROR: \"%s\" not allow in this type of neighborhood", (yyvsp[0].cadena));
                                                          exit(1);
                                                      }
                                                    }
#line 2775 "compiler.tab.c"
    break;

  case 98:
#line 1030 "src/compiler_files/compiler.y"
                                                    { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        (yyval.cadena) = generateString("[c_neighbours[9][0]][c_neighbours[9][1]]");
                                                      } else {
                                                          yyerror("ERROR: \"%s\" not allow in this type of neighborhood", (yyvsp[0].cadena));
                                                          exit(1);
                                                      }
                                                    }
#line 2787 "compiler.tab.c"
    break;


#line 2791 "compiler.tab.c"

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
#line 1039 "src/compiler_files/compiler.y"
    
                                // SECCION 4    Codigo en C
int n_line = 1 ;

int yyerror (message)
char *message ;
{ 
 
    fprintf (stderr, "\033[1;31m %s in line %d\033[0m\n", message, n_line) ;
    printf ( "\n") ;	// bye
    exit(1);
}

int yywarning (message)
char *message ;
{ 
 
    fprintf (stderr, "\033[1;33m %s in line %d\n\033[0m\n", message, n_line) ;
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
    "count",        COUNT,
    "currentTick",  CURRENTTICK,
    "continue",     CONTINUE,
    "double",       DOUBLE,
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


int yylex (){
  int i ;
  unsigned char c ;
  unsigned char cc ;
  char ops_expandibles [] = "!<=>|%&+-/*" ;
  char cadena [256] ;
  tStop *symbol ;

  do {
    c = getchar () ;
  
    if (c == '/') {	// If the line contain / could be a comment 
      cc = getchar () ;
      if (cc != '/') {   // If the next char is / is a comment 
        ungetc (cc, stdin) ;
      } else { // ==> Comment, ignore the line
        c = getchar () ;	// ...
        while (c != '\n') {
            c = getchar () ;
        }
      }
    }
    
    if (c == '\n')
    n_line++ ;
  
  } while (c == ' ' || c == '\n' || c == 10 || c == 13 || c == '\t') ;

  if ((c >= '0' && c <= '9')) {
        ungetc (c, stdin) ;
        scanf ("%d", &yylval.valor) ;
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
      return (IDENTIF) ;
    } else {
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

  if (c == EOF || c == 255 || c == 26) {
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



void generateCellClass(){
  char assignment[2048];
  sprintf(construct, "class Cell{ \n public: \n");
  sprintf(assignment, "Cell::Cell (){\n \n");

  nodeList *p = List; //Pointer
  while(p != NULL){
    if(p->section == CELL_T){
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
}

void generateFoundFunction() {
    char aux[1024];
    strcat(foundFunction, "string foundVariable(Cell c, string variable) { \n     char aux[100]; \n     string ret = \"\"; \n");
    
    nodeList *p = List; //Pointer
    while(p != NULL){ 
      if(p->section == CELL_T){
        if (strcmp(p->type, "int") == 0 || strcmp(p->type, "bool") == 0) {
          sprintf(aux, " if (variable.compare(\"%s\")==0) { \nsprintf(aux, \"%%d\", c.%s);\n}", p->name, p->name );
        } else if (strcmp(p->type, "double") == 0) {
          sprintf(aux, " if (variable.compare(\"%s\")==0) { \nsprintf(aux, \"%%f\", c.%s);\n}", p->name, p->name );
        }
        strcat(foundFunction, aux);
      }
      p = p->next;
    } 

    strcat(foundFunction, "\nret = aux; \nreturn ret; \n}");
  
}
// fprintf (stderr, "BBBBBB %s\n", Get("state")->name);

int foundType(int type){
  // int ret = 0;
  for(int j=0; j<100; j++){
    if ( type == INTEGER_T && typeExpression[j] == DOUBLE_T) {
      fprintf (stderr, "AAAAA %d\n", typeExpression[j]);
      return 1;
    } else if ( type == BOOLEAN_T && (typeExpression[j] == DOUBLE_T || typeExpression[j] == INTEGER_T)) {
      return 1;
    } else if ( (type == DOUBLE_T || type == INTEGER_T) && typeExpression[j] == BOOLEAN_T ) {
      return 1;
    }
  }
  return 0;
}

void clean(){
  for(int j=0; j<100; j++){
    typeExpression[j] = 0;
  }
  i = 0;
}


// To write the first line of the output files
char * generateFirstLine(){
  char  *line = malloc(2048);
  sprintf (line, " ");

  char  *aux = malloc(2048);
  sprintf (aux, " ");

  // char line[2048];
  sprintf(aux, " ");
  sprintf(line, " ");
  nodeList *p = List; //Pointer
  while(p->next != NULL){
        if( STATE_T == p->section){
          sprintf(aux, "%s", line);
          sprintf(line, ",%s", toUpper(p->name));
          strcat(line, aux);
        }
        p = p->next;
  }
  sprintf(aux, "%s\\n", line);
  sprintf(line, "currentTick");
  strcat(line, aux);

  size_t needed = snprintf(NULL, 0, "if (currentTick == 0){ \n MyFile << \"%s\";\n}\n", line) + 1;
  char  *writeFirstLine = malloc(needed*numStrains);
  sprintf(writeFirstLine, "if (currentTick == 0){ \n");
  p = List; //Pointer
  while(p->next != NULL){
        if( STRAIN_T == p->section){
          strcat(writeFirstLine, p->name);
          strcat(writeFirstLine, " << \"");
          strcat(writeFirstLine, line);
          strcat(writeFirstLine, "\";\n");
        }
        p = p->next;
  }
  strcat(writeFirstLine, "}\n");


  return writeFirstLine;
}

/*-----------Fuctions for the Linked List----------*/
// Add new nodes to the list
int Add(char *name, char *type, int section, char *defValue, char *actualValue)
{
    nodeList *p = List;    //Pointer

    //We chek if this node exists
    while(p != NULL){
        if(strcmp(name, p->name)==0 && strcmp(type, p->type)==0 && section == p->section){
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
    newNode->section = section;
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
int Destroy(char *name, char *type, int section) {

    if(List == NULL) return -1;    //The list is empty

    if(strcmp(List->type, type) == 0 && List->section == section && strcmp(List->name, name) == 0){   //If the first node is the node we are looking for, deleted
        nodeList *aux = List;
        List = List->next;
        aux->next = NULL;
        free(aux);
        return 1;
    }

    nodeList *p = List; //Pointer

    
    while(p->next != NULL){
        if(strcmp(name, p->name)==0 && strcmp(type, p->type)==0 && section == p->section){
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

