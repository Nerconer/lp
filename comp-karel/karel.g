#header
<<
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
>>

<<
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
	if(x == x1 && y == y1)
	  return true;
	--y1;
      }
    }
    else if( ori == 1 ) {	// DRIGHT
      for(int j = 0; dinsDominis(x1,y1); j++) {
	if(x == x1 && y == y1)
	  return true;
	++y1;
      }
    }
    else if( ori == 2 ) {	// DUP
      for(int j = 0; dinsDominis(x1,y1); j++) {
	if(x == x1 && y == y1)
	  return true;
	--x1;
      }
    }
    else {	// DDOWN
      for(int j = 0; dinsDominis(x1,y1); j++) {
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
>>

#lexclass START
#token SPACE "[\ \n]" << zzskip();>>

#token NUM "[0-9]+"
#token LPAREN "\("
#token RPAREN "\)"
#token LBRA "\["
#token RBRA "\]"
#token LKEY "\{"
#token RKEY "\}"
#token WORLD "world"
#token ROBOT "robot"
#token WALLS "walls"
#token BEEPERS "beepers"
#token LEFT "left"
#token RIGHT "right"
#token UP "up"
#token DOWN "down"
#token COMMA "\,"
#token SEMICOLON "\;"

#token DEFINE "define"
#token TURNOFF "turnoff"


#token IF "if"
#token AND "and"
#token OR "or"
#token NOT "not"

#token MOVE "move"
#token TURNLEFT "turnleft"
#token PUTBEEPER "putbeeper"
#token PICKBEEPER "pickbeeper"

#token ISCLEAR "isClear"
#token FOUNDBEEPER "foundBeeper"
#token ANYBEEPERSINBAG "anyBeepersInBag"

#token ITERATE "iterate"

#token BEGIN "begin"
#token END "end"


#token ID "([A-Z]|[a-z])(([A-Z]|[a-z])*[0-9]*)"



//karel: dworld drobot definitions  <<#0=createASTlist(_sibling);>>;

karel: dworld drobot definitions BEGIN! iter1 END! <<#0=createASTlist(_sibling);>>;




dworld: WORLD^ NUM NUM;

drobot: ROBOT^ NUM NUM NUM dir;

dir: LEFT | RIGHT | UP | DOWN;

rIf: IF^ cond LKEY! instr RKEY!;

cond: ((NOT^)* (ISCLEAR | FOUNDBEEPER | ANYBEEPERSINBAG)) ((AND^ | OR^ | NOT^) (ISCLEAR | FOUNDBEEPER | ANYBEEPERSINBAG))*;

rinst: (TURNLEFT | MOVE | PUTBEEPER | PICKBEEPER |ID) SEMICOLON!;

instr: (rIf | rinst)* <<#0=createASTlist(_sibling);>>;

functions: DEFINE^ ID LKEY! instr RKEY!;


iter2: ITERATE^ NUM LKEY! instr RKEY!;

iter1: iter2 (ID SEMICOLON!)* TURNOFF SEMICOLON! <<#0=createASTlist(_sibling);>>;


defsWallsBeepers: WALLS^ LBRA! NUM NUM dir (COMMA! NUM NUM dir)* RBRA! | BEEPERS^ NUM NUM NUM;

definitions: (defsWallsBeepers | functions)* <<#0=createASTlist(_sibling);>>;



linstr: ;









