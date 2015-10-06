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
#define COMMA 14
#define SEMICOLON 15
#define DEFINE 16
#define TURNOFF 17
#define IF 18
#define AND 19
#define OR 20
#define NOT 21
#define MOVE 22
#define TURNLEFT 23
#define PUTBEEPER 24
#define PICKBEEPER 25
#define ISCLEAR 26
#define FOUNDBEEPER 27
#define ANYBEEPERSINBAG 28
#define ITERATE 29
#define BEGIN 30
#define END 31
#define ID 32

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
extern SetWordType setwd1[];
extern SetWordType zzerr5[];
extern SetWordType setwd2[];
extern SetWordType setwd3[];
