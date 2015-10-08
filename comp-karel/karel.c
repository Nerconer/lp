/*
 * A n t l r  T r a n s l a t i o n  H e a d e r
 *
 * Terence Parr, Will Cohen, and Hank Dietz: 1989-2001
 * Purdue University Electrical Engineering
 * With AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 *
 *   antlr -gt karel.g
 *
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
#define GENAST

#include "ast.h"

#define zzSET_SIZE 8
#include "antlr.h"
#include "tokens.h"
#include "dlgdef.h"
#include "mode.h"

/* MR23 In order to remove calls to PURIFY use the antlr -nopurify option */

#ifndef PCCTS_PURIFY
#define PCCTS_PURIFY(r,s) memset((char *) &(r),'\0',(s));
#endif

#include "ast.c"
zzASTgvars

ANTLR_INFO

#include <cstdlib>
#include <cmath>

//global structures: AST, and domini
AST *root;
enum torient {DLEFT,DRIGHT,DUP,DDOWN};
struct {
  int gx,gy;                                    // dimensions del mon
  int posx,posy;                                 // posicio actual robot
  torient orient;                               // orientacio actual robot
  int nsens;                                    // nombre de sensors que te el robot
  vector<i3tuple>  walls, beepers;   
}domini;

// function to fill token information
void zzcr_attr(Attrib *attr, int type, char *text) {
  if (type == ID) {
    attr->kind = "id";
    attr->text = text;
  }
  else if (type == WORLD) {
    attr->kind = "world";
  }
  else if (type == ROBOT) {
    attr->kind = "robot";
  }
  else if (type == WALLS) {
    attr->kind = "walls";
  }
  else if (type == BEEPERS) {
    attr->kind = "beepers";
  }
  else if (type == DEFINE) {
    attr->kind = "define";
  }
  else {
    attr->kind = text;
    attr->text = "";
  }
}

// function to create a new AST node
AST* createASTnode(Attrib* attr, int type, char* text) {
  AST* as = new AST;
  as->kind = attr->kind; 
  as->text = attr->text;
  as->right = NULL; 
  as->down = NULL;
  return as;
}


/// create a new "list" AST node with one element
AST* createASTlist(AST *child) {
  AST *as=new AST;
  as->kind="list";
  as->right=NULL;
  as->down=child;
  return as;
}

AST *findDefinition(string id) {
  AST *n = root->down->right->right->down;
  while (n != NULL and (n->down->text != id)) n = n->right;
  if (n == NULL) {cout << "NOT FOUND: " << id << " " << endl;}
  return n->down->right;
}

/// get nth child of a tree. Count starts at 0.
/// if no such child, returns NULL
AST* child(AST *a,int n) {
  AST *c=a->down;
  for (int i=0; c!=NULL && i<n; i++) c=c->right;
  return c;
}



/// print AST, recursively, with indentation
void ASTPrintIndent(AST *a,string s)
{
  if (a==NULL) return;
  
  if (a->kind == "id") {
    if(a->text == "left" or a->text == "right" or a->text == "up" or a->text == "down") {
      cout << a->text;
    }
    else {
      cout << a->kind;
      if (a->text!="") cout<<"("<<a->text<<")";
    }
  }
  else {
    cout<<a->kind;
    if (a->text!="") cout<<"("<<a->text<<")";
  }
  cout<<endl;
  
  AST *i = a->down;
  while (i!=NULL && i->right!=NULL) {
    cout<<s+"  \\__";
    ASTPrintIndent(i,s+"  |"+string(i->kind.size()+i->text.size(),' '));
    i=i->right;
  }
  
  if (i!=NULL) {
    cout<<s+"  \\__";
    ASTPrintIndent(i,s+"   "+string(i->kind.size()+i->text.size(),' '));
    i=i->right;
  }
}

/// print AST 
void ASTPrint(AST *a)
{
  while (a!=NULL) {
    cout<<" ";
    ASTPrintIndent(a,"");
    a=a->right;
  }
}



bool avaluaCondicio(AST *a) {
  if (a->kind == "not") return not(avaluaCondicio(child(a,0)));
  else if (a->kind == "and") return avaluaCondicio(child(a,0)) and avaluaCondicio(child(a,1));
  else if (a->kind == "or") return avaluaCondicio(child(a,0)) or avaluaCondicio(child(a,1));
  // ompliu el codi que falta aqui
  
}

bool dinsDominis(int x, int y) {
  return (x < domini.gx and y < domini.gy and x >= 0 and y >= 0);
}

bool isWall(int x, int y) {
  cout << "posicio a mirar: (" << x << ", "<< y << ")" << endl;
  for (const auto&i : domini.walls) {
    int x1, y1, ori;
    x1 = get<0>(i); y1 = get<1>(i); ori = get<2>(i);
    if( ori == 0 ) {	// DLEFT
      for(int j = 0; dinsDominis(x1,y1); j++) {
        cout << " DLEFT x1: " << x1 << " " << "y1: "<<y1 << endl;
        if(x == x1 && y == y1)
        return true;
        --y1;
      }
    }
    else if( ori == 1 ) {	// DRIGHT
      for(int j = 0; dinsDominis(x1,y1); j++) {
        cout << " DRIGHT x1: " << x1 << " " << "y1: "<<y1 << endl;
        if(x == x1 && y == y1)
        return true;
        ++y1;
      }
    }
    else if( ori == 2 ) {	// DUP
      for(int j = 0; dinsDominis(x1,y1); j++) {
        cout << " DUP x1: " << x1 << " " << "y1: "<<y1 << endl;
        if(x == x1 && y == y1)
        return true;
        --x1;
      }
    }
    else {	// DDOWN
      for(int j = 0; dinsDominis(x1,y1); j++) {
        cout << " DOWN x1: " << x1 << " " << "y1: "<<y1 << endl;
        if(x == x1 && y == y1)
        return true;
        ++x1;
      }
    }
  }
  return false;
}

bool isClear(int x, int y, int orient) {
  // ompliu el codi que falta aqui
  if ( orient == DLEFT ) {
    if (dinsDominis(x,y-1) && !isWall(x,y-1))
    return true;
  }
  else if( orient == DRIGHT ) {
    if (dinsDominis(x,y+1) && !isWall(x,y+1))
    return true;
  }
  else if( orient == DUP ) {
    if (dinsDominis(x-1,y) && !isWall(x-1,y))
    return true;
  }
  else {	// DDOWN
    if (dinsDominis(x+1,y) && !isWall(x+1,y))
    return true;
  }
  return false;
}

void obtenirDir() {
  string dir;
  dir = root->down->right->down->right->right->right->kind.c_str();
  if ( dir == "left" )
  domini.orient = DLEFT;
  if ( dir == "right" )
  domini.orient = DRIGHT;
  if ( dir == "up" ) 
  domini.orient = DUP;
  if ( dir == "down" )
  domini.orient = DDOWN;   
}

int mirarDir(AST *a) {
  if( a->kind == "left" )
  return 0;
  else if( a->kind == "right" )
  return 1;
  else if( a->kind == "up" )
  return 2;
  else // down
  return 3;
}

void detectaWallsBeepers() {
  AST *llista = root->down->right->right->down;
  while ( llista != NULL ) {
    if(llista->kind == "walls") {
      AST *walls = llista->down;
      while( walls != NULL) {
        int dir = mirarDir(walls->right->right);
        // afageix un nou mur i avanca al seguent
        domini.walls.push_back(i3tuple(atoi(walls->kind.c_str()),atoi(walls->right->kind.c_str()), dir));
        walls = walls->right->right->right;
      }
    }
    if(llista->kind == "beepers") {
      AST *beepers = llista->down;
      domini.beepers.push_back(i3tuple(atoi(beepers->kind.c_str()), atoi(beepers->right->kind.c_str()), atoi(beepers->right->right->kind.c_str())));
    }
    llista = llista->right;
  }
}

void omplirDomini() { 
  domini.gx = atoi(root->down->down->kind.c_str());
  domini.gy = atoi(root->down->down->right->kind.c_str());
  domini.posx = atoi(root->down->right->down->kind.c_str());
  domini.posy = atoi(root->down->right->down->right->kind.c_str()); 
  // ompliu el codi que falta aqui  
  domini.nsens = atoi(root->down->right->down->right->right->kind.c_str());
  obtenirDir();
}

void testWalls() {
  int x,y,ori;
  x = 0;
  y = 0;
  ori = 3;
  cout << "isClear("<< x <<", "<< y <<", "<< ori << ") "<< isClear(x,y,ori) << endl;
}

void novaPosicio () {
  omplirDomini();
  // ompliu el codi que falta aqui
  detectaWallsBeepers();
  

}

void printWallsBeepers(vector<i3tuple> v) {
  for (const auto&i : v) {
    cout << "[" << get<0>(i)  << " " << get<1>(i) << " " << get<2>(i) << "]" <<endl;
  }
}

void printValors() {
  cout << endl;
  cout << "domini X: " << domini.gx << endl;
  cout << "domini Y: " << domini.gy << endl;
  
  cout << endl;
  cout << "pos actual robot (x,y): (" << domini.posx << ", " << domini.posy << ")" << endl;
  
  cout << "num sensors (total): " << domini.nsens << endl;
  cout << "orientacio: " << domini.orient << " (0->left, 1->right, 2->up, 3->down)" << endl;
  
  cout << endl;
  cout << "num walls: " << domini.walls.size() << endl;
  printWallsBeepers(domini.walls);
  
  cout << endl;
  cout << "num beepers: " << domini.beepers.size() << endl;
  printWallsBeepers(domini.beepers);
}

int main() {
  root = NULL;
  ANTLR(karel(&root), stdin);
  ASTPrint(root);
  novaPosicio();
  printValors();
  testWalls();	// TREURE
}

void
#ifdef __USE_PROTOS
karel(AST**_root)
#else
karel(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  dworld(zzSTR); zzlink(_root, &_sibling, &_tail);
  drobot(zzSTR); zzlink(_root, &_sibling, &_tail);
  definitions(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzmatch(BEGIN);  zzCONSUME;
  iter1(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzmatch(END); 
  (*_root)=createASTlist(_sibling);
 zzCONSUME;

  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x1);
  }
}

void
#ifdef __USE_PROTOS
dworld(AST**_root)
#else
dworld(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(WORLD); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x2);
  }
}

void
#ifdef __USE_PROTOS
drobot(AST**_root)
#else
drobot(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(ROBOT); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  dir(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x4);
  }
}

void
#ifdef __USE_PROTOS
dir(AST**_root)
#else
dir(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  if ( (LA(1)==LEFT) ) {
    zzmatch(LEFT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  }
  else {
    if ( (LA(1)==RIGHT) ) {
      zzmatch(RIGHT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
    }
    else {
      if ( (LA(1)==UP) ) {
        zzmatch(UP); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      }
      else {
        if ( (LA(1)==DOWN) ) {
          zzmatch(DOWN); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
        }
        else {zzFAIL(1,zzerr1,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
      }
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x8);
  }
}

void
#ifdef __USE_PROTOS
rIf(AST**_root)
#else
rIf(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(IF); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  cond(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzmatch(LKEY);  zzCONSUME;
  instr(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzmatch(RKEY);  zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x10);
  }
}

void
#ifdef __USE_PROTOS
cond(AST**_root)
#else
cond(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    {
      zzBLOCK(zztasp3);
      zzMake0;
      {
      while ( (LA(1)==NOT) ) {
        zzmatch(NOT); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
        zzLOOP(zztasp3);
      }
      zzEXIT(zztasp3);
      }
    }
    {
      zzBLOCK(zztasp3);
      zzMake0;
      {
      if ( (LA(1)==ISCLEAR) ) {
        zzmatch(ISCLEAR); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      }
      else {
        if ( (LA(1)==FOUNDBEEPER) ) {
          zzmatch(FOUNDBEEPER); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
        }
        else {
          if ( (LA(1)==ANYBEEPERSINBAG) ) {
            zzmatch(ANYBEEPERSINBAG); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
          }
          else {zzFAIL(1,zzerr2,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
        }
      }
      zzEXIT(zztasp3);
      }
    }
    zzEXIT(zztasp2);
    }
  }
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (setwd1[LA(1)]&0x20) ) {
      {
        zzBLOCK(zztasp3);
        zzMake0;
        {
        if ( (LA(1)==AND) ) {
          zzmatch(AND); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
        }
        else {
          if ( (LA(1)==OR) ) {
            zzmatch(OR); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
          }
          else {
            if ( (LA(1)==NOT) ) {
              zzmatch(NOT); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
            }
            else {zzFAIL(1,zzerr3,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
        }
        zzEXIT(zztasp3);
        }
      }
      {
        zzBLOCK(zztasp3);
        zzMake0;
        {
        if ( (LA(1)==ISCLEAR) ) {
          zzmatch(ISCLEAR); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
        }
        else {
          if ( (LA(1)==FOUNDBEEPER) ) {
            zzmatch(FOUNDBEEPER); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
          }
          else {
            if ( (LA(1)==ANYBEEPERSINBAG) ) {
              zzmatch(ANYBEEPERSINBAG); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
            }
            else {zzFAIL(1,zzerr4,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
        }
        zzEXIT(zztasp3);
        }
      }
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x40);
  }
}

void
#ifdef __USE_PROTOS
rinst(AST**_root)
#else
rinst(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    if ( (LA(1)==TURNLEFT) ) {
      zzmatch(TURNLEFT); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
    }
    else {
      if ( (LA(1)==MOVE) ) {
        zzmatch(MOVE); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      }
      else {
        if ( (LA(1)==PUTBEEPER) ) {
          zzmatch(PUTBEEPER); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
        }
        else {
          if ( (LA(1)==PICKBEEPER) ) {
            zzmatch(PICKBEEPER); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
          }
          else {
            if ( (LA(1)==ID) ) {
              zzmatch(ID); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
            }
            else {zzFAIL(1,zzerr5,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
          }
        }
      }
    }
    zzEXIT(zztasp2);
    }
  }
  zzmatch(SEMICOLON);  zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd1, 0x80);
  }
}

void
#ifdef __USE_PROTOS
instr(AST**_root)
#else
instr(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    for (;;) {
      if ( !((setwd2[LA(1)]&0x1))) break;
      if ( (LA(1)==IF) ) {
        rIf(zzSTR); zzlink(_root, &_sibling, &_tail);
      }
      else {
        if ( (setwd2[LA(1)]&0x2) ) {
          rinst(zzSTR); zzlink(_root, &_sibling, &_tail);
        }
        else break; /* MR6 code for exiting loop "for sure" */
      }
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  (*_root)=createASTlist(_sibling);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x4);
  }
}

void
#ifdef __USE_PROTOS
functions(AST**_root)
#else
functions(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(DEFINE); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(ID); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(LKEY);  zzCONSUME;
  instr(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzmatch(RKEY);  zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x8);
  }
}

void
#ifdef __USE_PROTOS
iter2(AST**_root)
#else
iter2(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzmatch(ITERATE); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(LKEY);  zzCONSUME;
  instr(zzSTR); zzlink(_root, &_sibling, &_tail);
  zzmatch(RKEY);  zzCONSUME;
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x10);
  }
}

void
#ifdef __USE_PROTOS
iter1(AST**_root)
#else
iter1(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  iter2(zzSTR); zzlink(_root, &_sibling, &_tail);
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    while ( (LA(1)==ID) ) {
      zzmatch(ID); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      zzmatch(SEMICOLON);  zzCONSUME;
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  zzmatch(TURNOFF); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
  zzmatch(SEMICOLON); 
  (*_root)=createASTlist(_sibling);
 zzCONSUME;

  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x20);
  }
}

void
#ifdef __USE_PROTOS
defsWallsBeepers(AST**_root)
#else
defsWallsBeepers(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  if ( (LA(1)==WALLS) ) {
    zzmatch(WALLS); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
    zzmatch(LBRA);  zzCONSUME;
    zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
    zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
    dir(zzSTR); zzlink(_root, &_sibling, &_tail);
    {
      zzBLOCK(zztasp2);
      zzMake0;
      {
      while ( (LA(1)==COMMA) ) {
        zzmatch(COMMA);  zzCONSUME;
        zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
        zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
        dir(zzSTR); zzlink(_root, &_sibling, &_tail);
        zzLOOP(zztasp2);
      }
      zzEXIT(zztasp2);
      }
    }
    zzmatch(RBRA);  zzCONSUME;
  }
  else {
    if ( (LA(1)==BEEPERS) ) {
      zzmatch(BEEPERS); zzsubroot(_root, &_sibling, &_tail); zzCONSUME;
      zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
      zzmatch(NUM); zzsubchild(_root, &_sibling, &_tail); zzCONSUME;
    }
    else {zzFAIL(1,zzerr6,&zzMissSet,&zzMissText,&zzBadTok,&zzBadText,&zzErrk); goto fail;}
  }
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd2, 0x40);
  }
}

void
#ifdef __USE_PROTOS
definitions(AST**_root)
#else
definitions(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  {
    zzBLOCK(zztasp2);
    zzMake0;
    {
    for (;;) {
      if ( !((setwd2[LA(1)]&0x80))) break;
      if ( (setwd3[LA(1)]&0x1) ) {
        defsWallsBeepers(zzSTR); zzlink(_root, &_sibling, &_tail);
      }
      else {
        if ( (LA(1)==DEFINE) ) {
          functions(zzSTR); zzlink(_root, &_sibling, &_tail);
        }
        else break; /* MR6 code for exiting loop "for sure" */
      }
      zzLOOP(zztasp2);
    }
    zzEXIT(zztasp2);
    }
  }
  (*_root)=createASTlist(_sibling);
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd3, 0x2);
  }
}

void
#ifdef __USE_PROTOS
linstr(AST**_root)
#else
linstr(_root)
AST **_root;
#endif
{
  zzRULE;
  zzBLOCK(zztasp1);
  zzMake0;
  {
  zzEXIT(zztasp1);
  return;
fail:
  zzEXIT(zztasp1);
  zzsyn(zzMissText, zzBadTok, (ANTLRChar *)"", zzMissSet, zzMissTok, zzErrk, zzBadText);
  zzresynch(setwd3, 0x4);
  }
}
