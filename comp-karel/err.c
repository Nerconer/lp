/*
 * A n t l r  S e t s / E r r o r  F i l e  H e a d e r
 *
 * Generated from: karel.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-2001
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 */

#define ANTLR_VERSION	13333
#include "pcctscfg.h"
#include "pccts_stdio.h"

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
using namespace std;

// struct to store information about tokens
typedef struct {
  string kind;
  string text;
} Attrib;

typedef std::tuple<int,int,int> i3tuple;

// function to fill token information (predeclaration)
void zzcr_attr(Attrib *attr, int type, char *text);

// fields for AST nodes
#define AST_FIELDS string kind; string text;
#include "ast.h"

// macro to create a new AST node (and function predeclaration)
#define zzcr_ast(as,attr,ttype,textt) as=createASTnode(attr,ttype,textt)
AST* createASTnode(Attrib* attr,int ttype, char *textt);
#define zzSET_SIZE 8
#include "antlr.h"
#include "ast.h"
#include "tokens.h"
#include "dlgdef.h"
#include "err.h"

ANTLRChar *zztokens[37]={
	/* 00 */	"Invalid",
	/* 01 */	"@",
	/* 02 */	"SPACE",
	/* 03 */	"NUM",
	/* 04 */	"LPAREN",
	/* 05 */	"RPAREN",
	/* 06 */	"LBRA",
	/* 07 */	"RBRA",
	/* 08 */	"LKEY",
	/* 09 */	"RKEY",
	/* 10 */	"WORLD",
	/* 11 */	"ROBOT",
	/* 12 */	"WALLS",
	/* 13 */	"BEEPERS",
	/* 14 */	"LEFT",
	/* 15 */	"RIGHT",
	/* 16 */	"UP",
	/* 17 */	"DOWN",
	/* 18 */	"COMMA",
	/* 19 */	"SEMICOLON",
	/* 20 */	"DEFINE",
	/* 21 */	"TURNOFF",
	/* 22 */	"IF",
	/* 23 */	"AND",
	/* 24 */	"OR",
	/* 25 */	"NOT",
	/* 26 */	"MOVE",
	/* 27 */	"TURNLEFT",
	/* 28 */	"PUTBEEPER",
	/* 29 */	"PICKBEEPER",
	/* 30 */	"ISCLEAR",
	/* 31 */	"FOUNDBEEPER",
	/* 32 */	"ANYBEEPERSINBAG",
	/* 33 */	"ITERATE",
	/* 34 */	"BEGIN",
	/* 35 */	"END",
	/* 36 */	"ID"
};
SetWordType zzerr1[8] = {0x0,0xc0,0x3,0x0, 0x0,0x0,0x0,0x0};
SetWordType zzerr2[8] = {0x0,0x0,0x0,0xc0, 0x1,0x0,0x0,0x0};
SetWordType zzerr3[8] = {0x0,0x0,0x80,0x3, 0x0,0x0,0x0,0x0};
SetWordType zzerr4[8] = {0x0,0x0,0x0,0xc0, 0x1,0x0,0x0,0x0};
SetWordType zzerr5[8] = {0x0,0x0,0x0,0x3c, 0x10,0x0,0x0,0x0};
SetWordType setwd1[37] = {0x0,0x1,0x0,0x0,0x0,0x0,0x0,
	0x8,0x40,0x90,0x0,0x2,0xc,0xc,0x0,
	0x0,0x0,0x0,0x8,0x0,0xc,0x0,0x90,
	0x20,0x20,0x20,0x90,0x90,0x90,0x90,0x0,
	0x0,0x0,0x0,0xc,0x0,0x90};
SetWordType zzerr6[8] = {0x0,0x30,0x0,0x0, 0x0,0x0,0x0,0x0};
SetWordType setwd2[37] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x4,0x0,0x0,0xc8,0xc8,0x0,
	0x0,0x0,0x0,0x0,0x0,0xc8,0x10,0x1,
	0x0,0x0,0x0,0x3,0x3,0x3,0x3,0x0,
	0x0,0x0,0x0,0x48,0x20,0x13};
SetWordType setwd3[37] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
	0x0,0x0,0x0,0x2,0x0,0x0};
