#ifndef tokens_h
#define tokens_h
/* tokens.h -- List of labelled tokens and stuff
 *
 * Generated from: karel.g
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * ANTLR Version 1.33MR33
 */
#define zzEOF_TOKEN 1
#define SPACE 2
#define NUM 3
#define LPAREN 4
#define RPAREN 5
#define LBRA 6
#define RBRA 7
#define LKEY 8
#define RKEY 9
#define WORLD 10
#define ROBOT 11
#define WALLS 12
#define BEEPERS 13
#define LEFT 14
#define RIGHT 15
#define UP 16
#define DOWN 17
#define COMMA 18
#define SEMICOLON 19
#define DEFINE 20
#define TURNOFF 21
#define IF 22
#define AND 23
#define OR 24
#define NOT 25
#define MOVE 26
#define TURNLEFT 27
#define PUTBEEPER 28
#define PICKBEEPER 29
#define ISCLEAR 30
#define FOUNDBEEPER 31
#define ANYBEEPERSINBAG 32
#define ITERATE 33
#define BEGIN 34
#define END 35
#define ID 36

#ifdef __USE_PROTOS
void karel(AST**_root);
#else
extern void karel();
#endif

#ifdef __USE_PROTOS
void dworld(AST**_root);
#else
extern void dworld();
#endif

#ifdef __USE_PROTOS
void drobot(AST**_root);
#else
extern void drobot();
#endif

#ifdef __USE_PROTOS
void dir(AST**_root);
#else
extern void dir();
#endif

#ifdef __USE_PROTOS
void rIf(AST**_root);
#else
extern void rIf();
#endif

#ifdef __USE_PROTOS
void cond(AST**_root);
#else
extern void cond();
#endif

#ifdef __USE_PROTOS
void rinst(AST**_root);
#else
extern void rinst();
#endif

#ifdef __USE_PROTOS
void instr(AST**_root);
#else
extern void instr();
#endif

#ifdef __USE_PROTOS
void functions(AST**_root);
#else
extern void functions();
#endif

#ifdef __USE_PROTOS
void iter2(AST**_root);
#else
extern void iter2();
#endif

#ifdef __USE_PROTOS
void iter1(AST**_root);
#else
extern void iter1();
#endif

#ifdef __USE_PROTOS
void defsWallsBeepers(AST**_root);
#else
extern void defsWallsBeepers();
#endif

#ifdef __USE_PROTOS
void definitions(AST**_root);
#else
extern void definitions();
#endif

#ifdef __USE_PROTOS
void linstr(AST**_root);
#else
extern void linstr();
#endif

#endif
extern SetWordType zzerr1[];
extern SetWordType zzerr2[];
extern SetWordType zzerr3[];
extern SetWordType zzerr4[];
extern SetWordType zzerr5[];
extern SetWordType setwd1[];
extern SetWordType zzerr6[];
extern SetWordType setwd2[];
extern SetWordType setwd3[];
