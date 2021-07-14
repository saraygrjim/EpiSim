/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
     ELSE = 275,
     STATE = 276,
     STRING = 277,
     TICKS = 278,
     TRUE = 279,
     AND = 280,
     OR = 281,
     EQ = 282,
     NEQ = 283,
     LE = 284,
     GE = 285,
     NORTH = 286,
     SOUTH = 287,
     WEST = 288,
     EAST = 289,
     NORTHEAST = 290,
     NORTHWEST = 291,
     SOUTHEAST = 292,
     SOUTHWEST = 293,
     NORTHP = 294,
     SOUTHP = 295,
     WESTP = 296,
     EASTP = 297,
     STRAIN = 298,
     NUM_STRAINS = 299,
     SIGNO_UNARIO = 300
   };
#endif
/* Tokens.  */
#define BOOL 258
#define CELLS 259
#define CONDITION 260
#define DOUBLE 261
#define EXTENDED 262
#define EFFECT 263
#define FALSE 264
#define GLOB 265
#define IDENTIF 266
#define INT 267
#define MOORE 268
#define NEUMANN 269
#define NGH 270
#define NUMBER 271
#define PROP 272
#define RANDOM 273
#define IF 274
#define ELSE 275
#define STATE 276
#define STRING 277
#define TICKS 278
#define TRUE 279
#define AND 280
#define OR 281
#define EQ 282
#define NEQ 283
#define LE 284
#define GE 285
#define NORTH 286
#define SOUTH 287
#define WEST 288
#define EAST 289
#define NORTHEAST 290
#define NORTHWEST 291
#define SOUTHEAST 292
#define SOUTHWEST 293
#define NORTHP 294
#define SOUTHP 295
#define WESTP 296
#define EASTP 297
#define STRAIN 298
#define NUM_STRAINS 299
#define SIGNO_UNARIO 300




/* Copy the first part of user declarations.  */
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

char beginEvaluation [] = "void evaluation(vector<vector<Cell>> &cells, int currentDay){ \n  \n ";   
char beginStrain [] = "for (int i = 0; i < N; i++){ \n         for (int j = 0; j < N; j++){    \n  \n             int** c_neighbours; \n             c_neighbours = (int**)malloc(MAX_NEIGH*sizeof(int *)); \n             for (int i = 0; i<MAX_NEIGH; i++){ \n                 c_neighbours[i] = (int *)malloc(2*sizeof(int)); \n             } \n             for (int i = 0; i<MAX_NEIGH; i++){ \n                 for (int j = 0; j<2; j++){ \n                     c_neighbours[i][j] = -1; \n                 } \n             } \n             searchNeighbours(c_neighbours, N, i, j, neighType); \n  \n ";
char searchFunction [] = "bool search(int** neighbours, int state, vector<vector<Cell>> &cells){ \n int i = 0; \n int x = neighbours[i][0]; \n int y = neighbours[i][1]; \n bool found = false; \n while (found == false && i < MAX_NEIGH){  \n if (x != -1){ \n     if(cells[x][y].state == state && (duration - cells[x][y].duration) >= daysToInfect){ \n         found = true; \n     } \n } \n x = neighbours[i][0]; \n y = neighbours[i][1]; \n i++; \n } \n return found; \n }\n";
char sumQuarantinedFunction [] = "int sum_quarantined(int** neighbours, vector<vector<Cell>> &cells){ \n int i = 0; \n int x = neighbours[i][0]; \n int y = neighbours[i][1]; \n int sum = 0; \n while (i < MAX_NEIGH){  \n     if(x != -1 && cells[x][y].quarantined){ \n         sum++; \n     } \n \n     x = neighbours[i][0]; \n     y = neighbours[i][1]; \n     i++; \n } \n return sum; \n }\n";
char includes [] = "#include <GL/gl.h> \n #include <GL/glut.h> \n #include <stdio.h> \n #include <cstdlib> \n #include <stdlib.h> \n #include <time.h> \n #include <string.h> \n #include <iostream> \n #include \"sim.h\" \n #include \"grid.h\" \n #include <vector> \n  \n using namespace std; \n using std::vector; \n  \n #define MAX_NEIGH  12 \n";
#define FF fflush(stdout);    // para forzar la impresion inmediata

int  yylex();
int  yyerror();
int  yyparse();
char *generateString();
char * toUpper(char aux[]);
void generateCellClass();



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 47 "compiler.y"
{                      // El tipo de la pila tiene caracter dual
      int valor ;             // - valor numerico de un NUMBER
      char *cadena ;          // - para pasar los nombres de IDENTIFES
}
/* Line 193 of yacc.c.  */
#line 237 "compiler.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 250 "compiler.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   210

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNRULES -- Number of states.  */
#define YYNSTATES  165

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    58,     2,     2,
      51,    53,    48,    46,    52,    47,    54,    49,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    57,
      59,    45,    60,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,     2,    56,     2,     2,     2,     2,
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
      50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    10,    15,    16,    19,    22,    25,
      26,    29,    30,    33,    34,    37,    40,    44,    45,    46,
      51,    54,    58,    63,    64,    69,    77,    81,    83,    88,
      93,    98,   107,   117,   125,   134,   136,   139,   146,   149,
     159,   166,   167,   170,   173,   178,   180,   184,   188,   192,
     196,   200,   204,   208,   212,   216,   220,   224,   228,   232,
     234,   236,   238,   240,   242,   244,   251,   255,   256,   258,
     260,   261,   263,   264,   268,   270,   272,   274,   276,   278,
     280,   282,   284,   286,   288,   290,   292
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      62,     0,    -1,    63,    70,    79,    -1,    64,    69,    -1,
      66,    65,    68,    67,    -1,    -1,    15,    14,    -1,    15,
      13,    -1,    15,     7,    -1,    -1,     4,    16,    -1,    -1,
      44,    16,    -1,    -1,    23,    16,    -1,    10,    78,    -1,
      10,    78,    69,    -1,    -1,    -1,    71,    73,    72,    74,
      -1,    17,    78,    -1,    17,    78,    73,    -1,    21,    11,
      76,    75,    -1,    -1,    21,    11,    76,    75,    -1,    51,
      77,    52,    77,    52,    77,    53,    -1,    16,    54,    16,
      -1,    16,    -1,     3,    11,    45,    88,    -1,    12,    11,
      45,    89,    -1,     6,    11,    45,    90,    -1,    43,    11,
      51,    16,    53,    55,    80,    56,    -1,    43,    11,    51,
      16,    53,    55,    80,    56,    79,    -1,    43,    11,    51,
      53,    55,    80,    56,    -1,    43,    11,    51,    53,    55,
      80,    56,    79,    -1,    81,    -1,    81,    80,    -1,    19,
      51,    85,    53,    55,    82,    -1,    83,    56,    -1,    83,
      56,    20,    19,    51,    85,    53,    55,    82,    -1,    83,
      56,    20,    55,    83,    56,    -1,    -1,    84,    83,    -1,
      81,    83,    -1,    11,    45,    85,    57,    -1,    86,    -1,
      85,    46,    85,    -1,    85,    47,    85,    -1,    85,    48,
      85,    -1,    85,    49,    85,    -1,    85,    58,    85,    -1,
      85,    25,    85,    -1,    85,    26,    85,    -1,    85,    28,
      85,    -1,    85,    27,    85,    -1,    85,    59,    85,    -1,
      85,    29,    85,    -1,    85,    60,    85,    -1,    85,    30,
      85,    -1,    87,    -1,    11,    -1,    18,    -1,    89,    -1,
      90,    -1,    88,    -1,    15,    51,    91,    53,    54,    11,
      -1,    51,    85,    53,    -1,    -1,    24,    -1,     9,    -1,
      -1,    16,    -1,    -1,    16,    54,    16,    -1,    16,    -1,
      31,    -1,    32,    -1,    33,    -1,    34,    -1,    35,    -1,
      36,    -1,    37,    -1,    38,    -1,    39,    -1,    40,    -1,
      41,    -1,    42,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   134,   134,   144,   150,   154,   159,   166,   173,   181,
     187,   194,   198,   203,   208,   216,   219,   226,   227,   226,
     233,   234,   240,   254,   258,   272,   276,   283,   289,   299,
     308,   319,   321,   323,   325,   330,   333,   338,   343,   347,
     351,   356,   359,   362,   367,   387,   388,   391,   394,   397,
     400,   403,   406,   409,   412,   415,   418,   421,   424,   430,
     439,   458,   461,   464,   467,   472,   489,   494,   497,   500,
     504,   507,   511,   514,   517,   523,   525,   527,   529,   531,
     540,   549,   558,   567,   576,   585,   594
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "CELLS", "CONDITION", "DOUBLE",
  "EXTENDED", "EFFECT", "FALSE", "GLOB", "IDENTIF", "INT", "MOORE",
  "NEUMANN", "NGH", "NUMBER", "PROP", "RANDOM", "IF", "ELSE", "STATE",
  "STRING", "TICKS", "TRUE", "AND", "OR", "EQ", "NEQ", "LE", "GE", "NORTH",
  "SOUTH", "WEST", "EAST", "NORTHEAST", "NORTHWEST", "SOUTHEAST",
  "SOUTHWEST", "NORTHP", "SOUTHP", "WESTP", "EASTP", "STRAIN",
  "NUM_STRAINS", "'='", "'+'", "'-'", "'*'", "'/'", "SIGNO_UNARIO", "'('",
  "','", "')'", "'.'", "'{'", "'}'", "';'", "'%'", "'<'", "'>'", "$accept",
  "program", "general", "header", "neighbourhood", "nCells", "nStrains",
  "time", "properties", "cell", "@1", "@2", "cellProperties", "states",
  "state", "color", "code", "declaration", "strains", "rules", "beginIf",
  "bodyIf", "codeIf", "assignment", "expression", "termino", "operand",
  "boolValue", "intValue", "doubleValue", "position", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,    61,    43,    45,    42,    47,
     300,    40,    44,    41,    46,   123,   125,    59,    37,    60,
      62
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    63,    64,    65,    65,    65,    65,    66,
      66,    67,    67,    68,    68,    69,    69,    71,    72,    70,
      73,    73,    74,    75,    75,    76,    77,    77,    78,    78,
      78,    79,    79,    79,    79,    80,    80,    81,    82,    82,
      82,    83,    83,    83,    84,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    86,
      87,    87,    87,    87,    87,    87,    87,    88,    88,    88,
      89,    89,    90,    90,    90,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     4,     0,     2,     2,     2,     0,
       2,     0,     2,     0,     2,     2,     3,     0,     0,     4,
       2,     3,     4,     0,     4,     7,     3,     1,     4,     4,
       4,     8,     9,     7,     8,     1,     2,     6,     2,     9,
       6,     0,     2,     2,     4,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     6,     3,     0,     1,     1,
       0,     1,     0,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       9,     0,     0,    17,     0,     5,    10,     1,     0,     0,
       0,     3,     0,    13,     0,     2,     0,    18,     0,     0,
       0,    15,     8,     7,     6,     0,    11,     0,    20,     0,
       0,     0,     0,    16,    14,     0,     4,     0,    21,     0,
      19,    67,    72,    70,    12,     0,     0,     0,    69,    68,
      28,    74,    30,    71,    29,     0,     0,     0,    23,     0,
       0,     0,     0,    35,    27,     0,     0,    22,    73,     0,
      67,    33,    36,     0,     0,     0,    31,    60,     0,    71,
      61,    67,     0,    45,    59,    64,    62,    63,    34,    26,
       0,    23,    32,     0,     0,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,     0,    67,    67,    67,     0,
      24,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,     0,    66,    51,    52,    54,    53,    56,
      58,    46,    47,    48,    49,    41,    50,    55,    57,     0,
       0,     0,    41,    37,     0,    41,    25,     0,    67,    43,
      38,    42,    65,     0,     0,    44,     0,    41,    67,     0,
       0,    40,     0,    41,    39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    13,     5,    36,    26,    11,     8,
       9,    29,    17,    40,    67,    58,    65,    21,    15,    62,
     142,   143,   144,   145,    82,    83,    84,    85,    86,    87,
     123
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -114
static const yytype_int16 yypact[] =
{
       0,   -10,    24,  -114,    23,    21,  -114,  -114,     2,    30,
      63,  -114,   157,    41,    45,  -114,    63,  -114,    54,    57,
      65,    23,  -114,  -114,  -114,    71,    44,    39,    30,    68,
      55,    62,    74,  -114,  -114,    92,  -114,   -15,  -114,   109,
    -114,    22,   105,   122,  -114,    86,    85,    90,  -114,  -114,
    -114,    97,  -114,  -114,  -114,   110,   147,   158,   152,   159,
     147,   126,   127,   147,   128,   124,   173,  -114,  -114,   130,
      19,     2,  -114,   171,   158,    90,     2,  -114,   138,    97,
    -114,    19,    25,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
     139,   152,  -114,   121,    33,    19,    19,    19,    19,    19,
      19,    19,    19,    19,    19,   135,    19,    19,    19,   158,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,   140,  -114,    76,    76,    76,    76,    76,
      76,   120,   120,   -18,   -18,    38,    76,    76,    76,   141,
     142,   150,    38,  -114,   136,    38,  -114,   186,    19,  -114,
     178,  -114,  -114,    69,   -16,  -114,   148,    38,    19,   144,
      84,  -114,   146,    38,  -114
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,   181,  -114,
    -114,  -114,   175,  -114,   113,   131,   -61,   189,    96,   -58,
     125,    46,  -113,  -114,   -81,  -114,  -114,   166,   165,   168,
    -114
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      94,    45,    69,   156,     1,    72,     6,    95,    96,    97,
      98,    99,   100,    90,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,     7,   136,   137,   138,    48,   149,
      77,    48,   151,    10,    78,    79,    12,    80,    46,   157,
     106,   107,   108,    49,   159,    14,    49,    16,   139,   141,
      95,    96,    97,    98,    99,   100,    27,    61,    95,    96,
      97,    98,    99,   100,    25,    30,    18,   153,    31,    19,
      81,   101,   102,   103,   104,    20,    32,   160,   105,   101,
     102,   103,   104,   106,   107,   108,   124,    34,    35,    39,
      37,   106,   107,   108,    95,    96,    97,    98,    99,   100,
      41,    95,    96,    97,    98,    99,   100,    42,    44,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,    43,
      47,    51,   101,   102,   103,   104,   155,   106,   107,   108,
     101,   102,   103,   104,   106,   107,   108,   162,    53,    55,
      56,    57,   106,   107,   108,    95,    96,    97,    98,    99,
     100,    59,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,    22,    60,    61,    88,   103,   104,
      23,    24,    92,    66,    64,    68,    74,    70,   106,   107,
     108,    63,    73,    71,    75,    63,    76,    89,    63,    93,
     135,   109,   150,   140,   146,   148,   147,   152,   154,   158,
     161,   163,    33,    38,   110,    28,    91,    50,    54,   164,
      52
};

static const yytype_uint8 yycheck[] =
{
      81,    16,    60,    19,     4,    63,    16,    25,    26,    27,
      28,    29,    30,    74,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,     0,   106,   107,   108,     9,   142,
      11,     9,   145,    10,    15,    16,    15,    18,    53,    55,
      58,    59,    60,    24,   157,    43,    24,    17,   109,    11,
      25,    26,    27,    28,    29,    30,    11,    19,    25,    26,
      27,    28,    29,    30,    23,    11,     3,   148,    11,     6,
      51,    46,    47,    48,    49,    12,    11,   158,    53,    46,
      47,    48,    49,    58,    59,    60,    53,    16,    44,    21,
      51,    58,    59,    60,    25,    26,    27,    28,    29,    30,
      45,    25,    26,    27,    28,    29,    30,    45,    16,    25,
      26,    27,    28,    29,    30,    46,    47,    48,    49,    45,
      11,    16,    46,    47,    48,    49,    57,    58,    59,    60,
      46,    47,    48,    49,    58,    59,    60,    53,    16,    53,
      55,    51,    58,    59,    60,    25,    26,    27,    28,    29,
      30,    54,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,     7,    55,    19,    71,    48,    49,
      13,    14,    76,    21,    16,    16,    52,    51,    58,    59,
      60,    56,    54,    56,    11,    60,    56,    16,    63,    51,
      55,    52,    56,    53,    53,    45,    54,    11,    20,    51,
      56,    55,    21,    28,    91,    16,    75,    41,    43,   163,
      42
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    62,    63,    64,    66,    16,     0,    70,    71,
      10,    69,    15,    65,    43,    79,    17,    73,     3,     6,
      12,    78,     7,    13,    14,    23,    68,    11,    78,    72,
      11,    11,    11,    69,    16,    44,    67,    51,    73,    21,
      74,    45,    45,    45,    16,    16,    53,    11,     9,    24,
      88,    16,    90,    16,    89,    53,    55,    51,    76,    54,
      55,    19,    80,    81,    16,    77,    21,    75,    16,    80,
      51,    56,    80,    54,    52,    11,    56,    11,    15,    16,
      18,    51,    85,    86,    87,    88,    89,    90,    79,    16,
      77,    76,    79,    51,    85,    25,    26,    27,    28,    29,
      30,    46,    47,    48,    49,    53,    58,    59,    60,    52,
      75,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    91,    53,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    55,    85,    85,    85,    77,
      53,    11,    81,    82,    83,    84,    53,    54,    45,    83,
      56,    83,    11,    85,    20,    57,    19,    55,    51,    83,
      85,    56,    53,    55,    82
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

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
#line 134 "compiler.y"
    { sprintf(temp, "%s", (yyvsp[(1) - (3)].cadena));
                                    generateCellClass();
                                    printf ("%s\n %s\n %s\n %s\n %s\n %s\n  ", includes, define, temp, construct, searchFunction, sumQuarantinedFunction); 
                                    sprintf(temp, "%s", (yyvsp[(3) - (3)].cadena));
                                    printf("%s\n %s }", beginEvaluation, temp );
                                  ;}
    break;

  case 3:
#line 144 "compiler.y"
    { sprintf(temp, "%s \n %s \n", (yyvsp[(1) - (2)].cadena), (yyvsp[(2) - (2)].cadena));
                                              (yyval.cadena) = generateString(temp);
                                            ;}
    break;

  case 4:
#line 150 "compiler.y"
    {  sprintf(temp, "%s \n %s \n %s", (yyvsp[(2) - (4)].cadena), (yyvsp[(3) - (4)].cadena), (yyvsp[(4) - (4)].cadena));
                                                        (yyval.cadena) = generateString(temp) ;}
    break;

  case 5:
#line 154 "compiler.y"
    {   sprintf (temp, "int neighType  = NEUMANN;\n");
                                                //printf ("%s", temp); 
                                                (yyval.cadena) = generateString(temp);
                                            ;}
    break;

  case 6:
#line 159 "compiler.y"
    { sprintf(temp, "%s", (yyvsp[(2) - (2)].cadena));
                                              sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                              (yyval.cadena) = generateString(temp);
                                              // printf ("%s", temp); 
                                              neighborhoodType = NEUMANN_T; 
                                            ;}
    break;

  case 7:
#line 166 "compiler.y"
    { sprintf(temp, "%s", (yyvsp[(2) - (2)].cadena));
                                              sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                              (yyval.cadena) = generateString(temp);
                                              // printf ("%s", temp); 
                                              neighborhoodType = MOORE_T; 
                                            ;}
    break;

  case 8:
#line 173 "compiler.y"
    { sprintf(temp, "%s", (yyvsp[(2) - (2)].cadena));
                                              sprintf (temp, "int neighType = %s;\n", toUpper(temp));
                                              (yyval.cadena) = generateString(temp);
                                              // printf ("%s", temp); 
                                              neighborhoodType = EXTENDED_T; 
                                            ;}
    break;

  case 9:
#line 181 "compiler.y"
    { sprintf (temp, "#define N 100\n");
                                              strcat ( define, temp); 
                                              sprintf (temp, "");
                                              (yyval.cadena) = generateString(temp);
                                            ;}
    break;

  case 10:
#line 187 "compiler.y"
    { sprintf (temp, "#define N %d\n", (yyvsp[(2) - (2)].valor));
                                              strcat ( define, temp); 
                                              sprintf (temp, "");
                                              (yyval.cadena) = generateString(temp);
                                            ;}
    break;

  case 11:
#line 194 "compiler.y"
    { sprintf (temp, "int nStrain  = 1;\n");
                                              (yyval.cadena) = generateString(temp);
                                            ;}
    break;

  case 12:
#line 198 "compiler.y"
    { sprintf (temp, "int nStrain  = %d;\n", (yyvsp[(2) - (2)].valor));
                                              (yyval.cadena) = generateString(temp);
                                            ;}
    break;

  case 13:
#line 203 "compiler.y"
    { sprintf (temp, "int days = 500;\n");
                                              // printf ("%s", temp); 
                                              (yyval.cadena) = generateString(temp);
                                            ;}
    break;

  case 14:
#line 208 "compiler.y"
    { sprintf (temp, "int days = %d;\n", (yyvsp[(2) - (2)].valor));
                                              // printf ("%s", temp);
                                              (yyval.cadena) = generateString(temp);
                                            ;}
    break;

  case 15:
#line 216 "compiler.y"
    {  sprintf (temp, "%s", (yyvsp[(2) - (2)].cadena));
                                                        (yyval.cadena) = generateString(temp);
                                                      ;}
    break;

  case 16:
#line 219 "compiler.y"
    {  sprintf (temp, "%s %s", (yyvsp[(2) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                        (yyval.cadena) = generateString(temp);
                                                      ;}
    break;

  case 17:
#line 226 "compiler.y"
    { section = CELL_T; ;}
    break;

  case 18:
#line 227 "compiler.y"
    { section = STATE_T; ;}
    break;

  case 19:
#line 228 "compiler.y"
    {  ;}
    break;

  case 20:
#line 233 "compiler.y"
    { ;}
    break;

  case 21:
#line 234 "compiler.y"
    { ;}
    break;

  case 22:
#line 240 "compiler.y"
    { if(Get((yyvsp[(2) - (4)].cadena)) == NULL) { 
                                                            Add((yyvsp[(2) - (4)].cadena), "none", section, " ", " "); 
                                                            sprintf(temp, "%s", (yyvsp[(2) - (4)].cadena));
                                                            char aux[1024];
                                                            sprintf(aux, "#define %s %d\n", toUpper(temp), counter);
                                                            strcat(define, aux);
                                                            // printf ("%s", define);
                                                            sprintf(drawCell, "void drawCell(Cell cells[N][N]){ \n for (int i = 0; i < N; i++){ \n for (int j = 0; j < N; j++){ \n switch (cells[i][j].state){ \n case %s:\n glColor3f%s; \n break;\n %s } \n glRectd(i, j, i+1, j+1); \n }\n }\n  }\n ", toUpper(temp), (yyvsp[(3) - (4)].cadena), (yyvsp[(4) - (4)].cadena)); 
                                                            
                                                          }
                                                          else { yyerror("ERROR: Nombre de estado duplicado"); exit(1);}
                                                        ;}
    break;

  case 23:
#line 254 "compiler.y"
    { //sprintf(define, "\n"); 
                                                          sprintf(temp, " "); 
                                                          (yyval.cadena) = generateString(temp); ;}
    break;

  case 24:
#line 258 "compiler.y"
    { if(Get((yyvsp[(2) - (4)].cadena)) == NULL) { 
                                                            Add((yyvsp[(2) - (4)].cadena), "none", section, "", ""); 
                                                            sprintf(temp, "%s", (yyvsp[(2) - (4)].cadena));
                                                            char aux[1024];
                                                            sprintf(aux, "#define %s %d\n", toUpper(temp), counter);
                                                            strcat(define, aux);
                                                            counter++;
                                                            sprintf (temp, "case %s:\n glColor3f%s; \n break;\n %s",toUpper(temp), (yyvsp[(3) - (4)].cadena), (yyvsp[(4) - (4)].cadena));
                                                            (yyval.cadena) = generateString(temp); 
                                                          }
                                                          else { yyerror("ERROR: Variable duplicada"); exit(1);}
                                                       ;}
    break;

  case 25:
#line 272 "compiler.y"
    { sprintf(temp, "(%s,%s,%s)", (yyvsp[(2) - (7)].cadena), (yyvsp[(4) - (7)].cadena), (yyvsp[(6) - (7)].cadena));
                                                          (yyval.cadena) = generateString(temp); ;}
    break;

  case 26:
#line 276 "compiler.y"
    { char *eptr;
                                                          sprintf(temp, " %d.%d", (yyvsp[(1) - (3)].valor), (yyvsp[(3) - (3)].valor));
                                                          double number = strtod(temp, &eptr);
                                                          if (number > 255.0) { sprintf(temp, "255");}
                                                          else { sprintf(temp, "%f", number); }
                                                          (yyval.cadena) = generateString(temp); ;}
    break;

  case 27:
#line 283 "compiler.y"
    { if((yyvsp[(1) - (1)].valor) > 255) { sprintf(temp, "255"); } 
                                                          else { sprintf(temp, "%d", (yyvsp[(1) - (1)].valor)); }
                                                          (yyval.cadena) = generateString(temp); ;}
    break;

  case 28:
#line 289 "compiler.y"
    { if(Get((yyvsp[(2) - (4)].cadena)) == NULL) { 
                                                        Add((yyvsp[(2) - (4)].cadena), "bool", section, (yyvsp[(4) - (4)].cadena), (yyvsp[(4) - (4)].cadena)); 
                                                        sprintf (temp, "%s %s = %s;\n", (yyvsp[(1) - (4)].cadena), (yyvsp[(2) - (4)].cadena), (yyvsp[(4) - (4)].cadena));
                                                        // printf ("%s", temp); 
                                                        (yyval.cadena) = generateString(temp);
                                                      }
                                                      else { yyerror("ERROR: Variable duplicada"); exit(1);}
                                                      
                                                    ;}
    break;

  case 29:
#line 299 "compiler.y"
    { if(Get((yyvsp[(2) - (4)].cadena)) == NULL) { 
                                                        Add((yyvsp[(2) - (4)].cadena), "bool", section, (yyvsp[(4) - (4)].cadena), (yyvsp[(4) - (4)].cadena)); 
                                                        sprintf (temp, "%s %s = %s;\n", (yyvsp[(1) - (4)].cadena), (yyvsp[(2) - (4)].cadena), (yyvsp[(4) - (4)].cadena));
                                                        // printf ("%s", temp); 
                                                        (yyval.cadena) = generateString(temp);
                                                      }
                                                      else { yyerror("ERROR: Variable duplicada"); exit(1); }
                                                    ;}
    break;

  case 30:
#line 308 "compiler.y"
    { if(Get((yyvsp[(2) - (4)].cadena)) == NULL) { 
                                                        Add((yyvsp[(2) - (4)].cadena), "bool", section, (yyvsp[(4) - (4)].cadena), (yyvsp[(4) - (4)].cadena)); 
                                                        sprintf (temp, "%s %s = %s;\n", (yyvsp[(1) - (4)].cadena), (yyvsp[(2) - (4)].cadena), (yyvsp[(4) - (4)].cadena));
                                                        // printf ("%s", temp); 
                                                        (yyval.cadena) = generateString(temp);
                                                      }
                                                      else { yyerror("ERROR: Variable duplicada"); exit(1); }
                                                    ;}
    break;

  case 31:
#line 319 "compiler.y"
    { sprintf(temp, " if(currentDay >= %d) {\n %s %s \n } \n } \n ", (yyvsp[(4) - (8)].valor), beginStrain, (yyvsp[(7) - (8)].cadena));
                                                                                     (yyval.cadena) = generateString(temp); ;}
    break;

  case 32:
#line 321 "compiler.y"
    { sprintf(temp, " if(currentDay >= %d) {\n %s %s \n } \n } \n %s ", (yyvsp[(4) - (9)].valor), beginStrain, (yyvsp[(7) - (9)].cadena), (yyvsp[(9) - (9)].cadena));
                                                                                     (yyval.cadena) = generateString(temp); ;}
    break;

  case 33:
#line 323 "compiler.y"
    { sprintf(temp, " if(currentDay >= 0) {\n %s %s \n } \n } \n ", beginStrain, (yyvsp[(6) - (7)].cadena));
                                                                                     (yyval.cadena) = generateString(temp); ;}
    break;

  case 34:
#line 325 "compiler.y"
    { sprintf(temp, " if(currentDay >= 0) {\n %s %s \n } \n } \n %s ", beginStrain, (yyvsp[(6) - (8)].cadena), (yyvsp[(8) - (8)].cadena));
                                                                                     (yyval.cadena) = generateString(temp); ;}
    break;

  case 35:
#line 330 "compiler.y"
    { sprintf(temp, "%s \n }", (yyvsp[(1) - (1)].cadena));
                                                  (yyval.cadena) = generateString(temp); ;}
    break;

  case 36:
#line 333 "compiler.y"
    { sprintf(temp, "%s \n %s", (yyvsp[(1) - (2)].cadena), (yyvsp[(2) - (2)].cadena));
                                                  (yyval.cadena) = generateString(temp); ;}
    break;

  case 37:
#line 338 "compiler.y"
    { sprintf (temp, "if( %s ) {\n %s ", (yyvsp[(3) - (6)].cadena), (yyvsp[(6) - (6)].cadena));
                                                                    (yyval.cadena) = generateString(temp);
                                                                  ;}
    break;

  case 38:
#line 343 "compiler.y"
    { sprintf(temp, "%s \n}\n",(yyvsp[(1) - (2)].cadena));
                                                                    (yyval.cadena) = generateString(temp);
                                                                  ;}
    break;

  case 39:
#line 347 "compiler.y"
    { sprintf(temp, "%s \n} else if ( %s ) {\n %s", (yyvsp[(1) - (9)].cadena), (yyvsp[(6) - (9)].cadena), (yyvsp[(9) - (9)].cadena));
                                                                    (yyval.cadena) = generateString(temp);
                                                                  ;}
    break;

  case 40:
#line 351 "compiler.y"
    { sprintf(temp, "%s \n} else {\n %s \n}", (yyvsp[(1) - (6)].cadena), (yyvsp[(5) - (6)].cadena));
                                                                    (yyval.cadena) = generateString(temp);
                                                                  ;}
    break;

  case 41:
#line 356 "compiler.y"
    {   sprintf(temp, " ");
                                                        (yyval.cadena) = generateString(temp);
                                                      ;}
    break;

  case 42:
#line 359 "compiler.y"
    {   sprintf(temp, "%s \n %s", (yyvsp[(1) - (2)].cadena), (yyvsp[(2) - (2)].cadena));
                                                        (yyval.cadena) = generateString(temp);;}
    break;

  case 43:
#line 362 "compiler.y"
    {  sprintf(temp, "%s \n %s", (yyvsp[(1) - (2)].cadena), (yyvsp[(2) - (2)].cadena));
                                                        (yyval.cadena) = generateString(temp);;}
    break;

  case 44:
#line 367 "compiler.y"
    { nodeList *p = Get((yyvsp[(1) - (4)].cadena));
                                                              if(p == NULL) { 
                                                                sprintf(temp, "ERROR: Variable %s doesn't exist", (yyvsp[(1) - (4)].cadena));          
                                                                yyerror(temp);
                                                                exit(1);
                                                              } else {
                                                                if(p->type2 == CELL_T){
                                                                  // strcpy(p->actualValue, $3);
                                                                  sprintf(temp, "cells[i][j].%s = %s; ", (yyvsp[(1) - (4)].cadena), (yyvsp[(3) - (4)].cadena));
                                                                  (yyval.cadena) = generateString(temp); 
                                                                } else if(p->type2 == GLOBAL_T) {
                                                                  // strcpy(p->actualValue, $3);
                                                                  sprintf(temp, "%s = %s; ", (yyvsp[(1) - (4)].cadena), (yyvsp[(3) - (4)].cadena));
                                                                  (yyval.cadena) = generateString(temp); 
                                                                }
                                                              }
                                                            ;}
    break;

  case 45:
#line 387 "compiler.y"
    { ;}
    break;

  case 46:
#line 388 "compiler.y"
    { sprintf(temp, "%s + %s", (yyvsp[(1) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                    (yyval.cadena) = generateString(temp); ;}
    break;

  case 47:
#line 391 "compiler.y"
    { sprintf(temp, "%s - %s", (yyvsp[(1) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                    (yyval.cadena) = generateString(temp); ;}
    break;

  case 48:
#line 394 "compiler.y"
    { sprintf(temp, "%s * %s", (yyvsp[(1) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                    (yyval.cadena) = generateString(temp); ;}
    break;

  case 49:
#line 397 "compiler.y"
    { sprintf(temp, "%s / %s", (yyvsp[(1) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                    (yyval.cadena) = generateString(temp); ;}
    break;

  case 50:
#line 400 "compiler.y"
    { sprintf(temp, "%s %% %s", (yyvsp[(1) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                    (yyval.cadena) = generateString(temp); ;}
    break;

  case 51:
#line 403 "compiler.y"
    { sprintf(temp, "%s && %s", (yyvsp[(1) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                    (yyval.cadena) = generateString(temp); ;}
    break;

  case 52:
#line 406 "compiler.y"
    { sprintf(temp, "%s || %s", (yyvsp[(1) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                    (yyval.cadena) = generateString(temp); ;}
    break;

  case 53:
#line 409 "compiler.y"
    { sprintf(temp, "%s != %s", (yyvsp[(1) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                    (yyval.cadena) = generateString(temp); ;}
    break;

  case 54:
#line 412 "compiler.y"
    { sprintf(temp, "%s == %s", (yyvsp[(1) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                    (yyval.cadena) = generateString(temp); ;}
    break;

  case 55:
#line 415 "compiler.y"
    { sprintf(temp, "%s < %s", (yyvsp[(1) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                    (yyval.cadena) = generateString(temp); ;}
    break;

  case 56:
#line 418 "compiler.y"
    { sprintf(temp, "%s <= %s", (yyvsp[(1) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                  (yyval.cadena) = generateString(temp); ;}
    break;

  case 57:
#line 421 "compiler.y"
    { sprintf(temp, "%s > %s", (yyvsp[(1) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                    (yyval.cadena) = generateString(temp); ;}
    break;

  case 58:
#line 424 "compiler.y"
    { sprintf(temp, "%s >= %s", (yyvsp[(1) - (3)].cadena), (yyvsp[(3) - (3)].cadena));
                                                    (yyval.cadena) = generateString(temp); ;}
    break;

  case 59:
#line 430 "compiler.y"
    { ; ;}
    break;

  case 60:
#line 439 "compiler.y"
    { nodeList *p = Get((yyvsp[(1) - (1)].cadena));
                                                      if(p == NULL) { 
                                                        sprintf(temp, "ERROR: Variable %s doesn't exist", (yyvsp[(1) - (1)].cadena));          
                                                        yyerror(temp);
                                                        exit(1);
                                                      } else {
                                                        if(p->type2 == CELL_T){
                                                          sprintf(temp, "cells[i][j].%s", (yyvsp[(1) - (1)].cadena));
                                                          (yyval.cadena) = generateString(temp); 
                                                        } else if (p->type2 == GLOBAL_T){
                                                          sprintf(temp, "%s", (yyvsp[(1) - (1)].cadena));
                                                          (yyval.cadena) = generateString(temp); 
                                                        } else if (p->type2 == STATE_T){
                                                          sprintf(temp, "%s", toUpper((yyvsp[(1) - (1)].cadena)));
                                                          (yyval.cadena) = generateString(temp);
                                                        }
                                                      }
                                                    ;}
    break;

  case 61:
#line 458 "compiler.y"
    { sprintf(temp, "((rand() %% (1001))/1000.0)");
                                                      (yyval.cadena) = generateString(temp); ;}
    break;

  case 62:
#line 461 "compiler.y"
    { sprintf(temp, "%s", (yyvsp[(1) - (1)].cadena));
                                                      (yyval.cadena) = generateString(temp); ;}
    break;

  case 63:
#line 464 "compiler.y"
    { sprintf(temp, "%s", (yyvsp[(1) - (1)].cadena));
                                                      (yyval.cadena) = generateString(temp); ;}
    break;

  case 64:
#line 467 "compiler.y"
    { sprintf(temp, "%s", (yyvsp[(1) - (1)].cadena));
                                                      (yyval.cadena) = generateString(temp); ;}
    break;

  case 65:
#line 472 "compiler.y"
    { nodeList *p = Get((yyvsp[(1) - (6)].cadena));
                                                      if(p == NULL) { 
                                                        sprintf(temp, "ERROR: Variable %s doesn't exist", (yyvsp[(1) - (6)].cadena));          
                                                        yyerror(temp);
                                                        exit(1);
                                                      } else {
                                                        if(p->type2 == CELL_T){
                                                          sprintf(temp, "cells%s.%s", (yyvsp[(3) - (6)].cadena), (yyvsp[(6) - (6)].cadena));
                                                          (yyval.cadena) = generateString(temp); 
                                                        } else {
                                                          sprintf(temp, "ERROR: %s not a cell variable", (yyvsp[(6) - (6)].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                        }
                                                      } 
                                                    ;}
    break;

  case 66:
#line 489 "compiler.y"
    { sprintf(temp, "( %s )", (yyvsp[(2) - (3)].cadena));
                                                      (yyval.cadena) = generateString(temp); ;}
    break;

  case 67:
#line 494 "compiler.y"
    {  sprintf (temp, "false");
                                                   (yyval.cadena) = generateString(temp); ;}
    break;

  case 68:
#line 497 "compiler.y"
    {  sprintf (temp, "%s", (yyvsp[(1) - (1)].cadena));
                                                   (yyval.cadena) = generateString(temp); ;}
    break;

  case 69:
#line 500 "compiler.y"
    {  sprintf (temp, "%s", (yyvsp[(1) - (1)].cadena));
                                                   (yyval.cadena) = generateString(temp); ;}
    break;

  case 70:
#line 504 "compiler.y"
    {  sprintf (temp, "-1");
                                                   (yyval.cadena) = generateString(temp); ;}
    break;

  case 71:
#line 507 "compiler.y"
    {  sprintf (temp, "%d", (yyvsp[(1) - (1)].valor));
                                                   (yyval.cadena) = generateString(temp); ;}
    break;

  case 72:
#line 511 "compiler.y"
    {  sprintf (temp, "0.0");
                                                   (yyval.cadena) = generateString(temp); ;}
    break;

  case 73:
#line 514 "compiler.y"
    {  sprintf (temp, "%d.%d", (yyvsp[(1) - (3)].valor), (yyvsp[(3) - (3)].valor));
                                                   (yyval.cadena) = generateString(temp); ;}
    break;

  case 74:
#line 517 "compiler.y"
    {  sprintf (temp, "%d.0", (yyvsp[(1) - (1)].valor));
                                                   (yyval.cadena) = generateString(temp); ;}
    break;

  case 75:
#line 523 "compiler.y"
    { sprintf(temp,"[c_neighbours[1][0]][c_neighbours[1][1]]");
                                                      (yyval.cadena) = generateString(temp);;}
    break;

  case 76:
#line 525 "compiler.y"
    { sprintf(temp,"[c_neighbours[5][0]][c_neighbours[5][1]]");
                                                      (yyval.cadena) = generateString(temp);;}
    break;

  case 77:
#line 527 "compiler.y"
    { sprintf(temp,"[c_neighbours[7][0]][c_neighbours[7][1]]");
                                                      (yyval.cadena) = generateString(temp);;}
    break;

  case 78:
#line 529 "compiler.y"
    { sprintf(temp,"[c_neighbours[3][0]][c_neighbours[3][1]]");
                                                      (yyval.cadena) = generateString(temp);;}
    break;

  case 79:
#line 531 "compiler.y"
    { if(neighborhoodType != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[2][0]][c_neighbours[2][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[(1) - (1)].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    ;}
    break;

  case 80:
#line 540 "compiler.y"
    { if(neighborhoodType != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[0][0]][c_neighbours[0][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[(1) - (1)].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    ;}
    break;

  case 81:
#line 549 "compiler.y"
    { if(neighborhoodType != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[4][0]][c_neighbours[4][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[(1) - (1)].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    ;}
    break;

  case 82:
#line 558 "compiler.y"
    { if(neighborhoodType != NEUMANN_T) {
                                                        sprintf(temp,"[c_neighbours[6][0]][c_neighbours[6][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[(1) - (1)].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    ;}
    break;

  case 83:
#line 567 "compiler.y"
    { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        sprintf(temp,"[c_neighbours[8][0]][c_neighbours[8][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[(1) - (1)].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    ;}
    break;

  case 84:
#line 576 "compiler.y"
    { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        sprintf(temp,"[c_neighbours[10][0]][c_neighbours[10][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[(1) - (1)].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    ;}
    break;

  case 85:
#line 585 "compiler.y"
    { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        sprintf(temp,"[c_neighbours[11][0]][c_neighbours[11][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[(1) - (1)].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    ;}
    break;

  case 86:
#line 594 "compiler.y"
    { if(neighborhoodType != NEUMANN_T && neighborhoodType != MOORE) {
                                                        sprintf(temp,"[c_neighbours[9][0]][c_neighbours[9][1]]");
                                                        (yyval.cadena) = generateString(temp);
                                                      } else {
                                                          sprintf(temp, "ERROR: %s not allow in this type of neighborhood", (yyvsp[(1) - (1)].cadena));          
                                                          yyerror(temp);
                                                          exit(1);
                                                      }
                                                    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2295 "compiler.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 605 "compiler.y"
    
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
    "else",         ELSE,
    "random",       RANDOM,
    "state",        STATE,
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
  sprintf(construct, "class Cell{ \n public: \n bool alive; \n int state; \n bool infected;  \n ");
  sprintf(assignment, "Cell::Cell (){\n alive = true;\n state  = 0;\n infected = false;\n ");

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

  strcat(construct, " Cell(); \n void infect(int, int); \n }; \n");
  strcat(assignment, "}\n void Cell::infect(int incubation, int duration){ \n     infected   = true; \n     state      = 1; \n     incubation = incubation; \n     duration   = duration; \n } \n  ");


  strcat(construct, assignment);
  // return construct;
}
