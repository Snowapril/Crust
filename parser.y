%{
	#include <stdio.h> 
       #include <vector>
       #include "ast/node.hpp"
       #include "ast/stmt.hpp"
       #include "ast/symtab.hpp"
	int yyerror(const char* msg), yylex(); 
       int lineno = 1;
       SymbolTable globalSymTab;
%}	
%code requires { #include "ast/node.hpp" }
%code requires { #include "ast/stmt.hpp" }
%code requires { #include "ast/symtab.hpp" }
%union {
	Node* node;
       Block* block;
       Statement* stmt; 
       FuncStmt* funcStmt;
       std::vector<Statement*>* stmts; 
       std::vector<Node*>* nodes; 
	int iVal; 
	char* sVal;  
}

%token <iVal> _NUMBER
%token <sVal> _ID _LITERAL
%type <nodes> Args Params
%type <block> Block
%type <node> Type Factor Exp Term Value Param Id
%type <stmt> StmtIf StmtVarDec StmtAssign StmtFor StmtLoop Stmt
%type <stmts> Stmts 

%token _IF _ELSE _WHILE _RETURN _FUNC _FOR _LOOP _BREAK _IN _LET
%token _OPAREN _CPAREN _OCURLY _CCURLY _OBRACK _CBRACK 
%token _SEMI _COLONS _COMMA _ASS _RIGHTARROW _COLON
%token _AND _OR 
%token _PLUS _MINUS _TIMES _MOD _DIV 
%token _GT _LT _GE _LE _EQ _NEQ 
%token _INT _BOOL _CHAR _VOID _FLOAT
%token _TRUE _FALSE

%start Prog

%%
Prog   : Funcs {printf("program\n");}
       ;

Funcs  : Func Funcs {printf("Funcs empl\n"); }
       |            {printf("Funcs new\n");  }
       ;

Func   : _FUNC _ID _OPAREN Params _CPAREN Block {printf("Func\n"); 
              globalSymTab.addFunction($2, new FuncStmt($2, $4, $6));}
       | _FUNC _ID _OPAREN Params _CPAREN _RIGHTARROW Type Block {printf("Func2\n"); 
              globalSymTab.addFunction($2, new FuncStmt($2, $4, $7, $8));}
       ;

Params : Params _COMMA Param {printf("Params1\n"); $$->emplace_back($3);}
       | Param               {printf("Params2\n"); $$ = new std::vector<Node*>(); $$->emplace_back($1);}
       |                     {printf("Params3\n"); $$ = new std::vector<Node*>();}
       ;

Param  : Type _ID {printf("Param\n"); $$ = new ParamNode($1, $2); }
       ;

Block  : _OCURLY Stmts _CCURLY     {printf("Block\n"); $$ = new Block($2);}
       | _OCURLY _CCURLY           {printf("Block\n"); $$ = new Block();}
       ;

Stmts  : Stmt Stmts { printf("Stmts\n");   $2->emplace_back($1); $$ = $2;}
       |            { printf("asdfasf\n"); $$ = new std::vector<Statement*>(); }
       ;

Stmt   : StmtIf            {printf("Stmt\n"); $$ = $1;}
       | StmtVarDec _SEMI  {printf("Stmt\n"); $$ = $1;}
       | StmtAssign _SEMI  {printf("Stmt\n"); $$ = $1;}
       | _BREAK _SEMI      {printf("Stmt\n"); $$ = new BreakStmt();}
       | StmtFor           {printf("Stmt\n"); $$ = $1;}
       | StmtLoop          {printf("Stmt\n"); $$ = $1;}
       | _RETURN Exp _SEMI {printf("Stmt\n"); $$ = new ReturnStmt($2);}
       | _SEMI             {printf("Stmt\n");}
       ;

Args   : Args _COMMA Id {printf("Args\n"); $$->emplace_back($3);}
       | Id             {printf("Args\n"); $$ = new std::vector<Node*>(); $$->emplace_back($1);}
       |                { $$ = new std::vector<Node*>(); }
       ;

Type   : _INT        { printf("Type\n"); $$ = new TypeNode(VarType::INT);   }
       | _FLOAT      { printf("Type\n"); $$ = new TypeNode(VarType::FLOAT); }
       | _BOOL       { printf("Type\n"); $$ = new TypeNode(VarType::BOOL);  }
       | _CHAR       { printf("Type\n"); $$ = new TypeNode(VarType::CHAR);  }
       | _VOID       { printf("Type\n"); $$ = new TypeNode(VarType::VOID);  }
       ;

StmtIf : _IF Exp Block {printf("StmtIf\n"); $$ = new IfStmt($2, $3);}
       | _IF Exp Block _ELSE Block {printf("StmtIf\n"); $$ = new IfStmt($2, $3, $5);}
       ;

StmtVarDec  : _LET _ID _ASS Exp             {printf("StmtVarDec\n"); $$ = new VarDecStmt($2, $4);}
            | _LET _ID _COLON Type _ASS Exp {printf("StmtVarDec\n"); $$ = new VarDecStmt($2, $4, $6);}
            ;

StmtAssign  : Id _ASS Exp {printf("StmtAssign\n"); $$ = new AssignStmt($1, $3);}
            ;
            
StmtFor     : _FOR Id _IN Exp Block {printf("StmtFor\n"); $$ = new ForStmt($2, $4, $5);}
            ;
            
StmtLoop    : _LOOP Block {printf("StmtLoop\n"); $$ = new LoopStmt($2);}
            ; 

Exp : Exp _PLUS Exp {printf("Exp\n");  $$ = new OpNode(OpType::ADD); $$->addChild($1); $$->addChild($3); }
    | Exp _MINUS Exp {printf("Exp\n"); $$ = new OpNode(OpType::SUB); $$->addChild($1); $$->addChild($3); }
    | Term { printf("Exp\n"); $$ = $1; }
    ;

Term : Term _TIMES Exp {printf("Term\n"); $$ = new OpNode(OpType::MUL); $$->addChild($1); $$->addChild($3); }
     | Term _DIV Exp {printf("Term\n");   $$ = new OpNode(OpType::DIV); $$->addChild($1); $$->addChild($3); }
     | Term _MOD Exp {printf("Term\n");   $$ = new OpNode(OpType::MOD); $$->addChild($1); $$->addChild($3); }
     | Factor {printf("Term\n"); $$ = $1; }
     ;

Factor : Value {printf("Factor\n"); $$ = $1; }
       | _PLUS Value {printf("Factor\n"); $$ = new OpNode(OpType::POS); $$->addChild($2); }
       | _MINUS Value {printf("Factor\n"); $$ = new OpNode(OpType::NEG); $$->addChild($2); }
       ;

Value  : Id                            {printf("Value\n"); $$ = $1; }
       | _LITERAL                      {printf("Value\n"); $$ = new LiteralNode(VarType::CHAR, $1); }
       | _NUMBER                       {printf("Value\n"); $$ = new LiteralNode(VarType::INT, $1);}
       | _TRUE                         {printf("Value\n"); $$ = new LiteralNode(VarType::BOOL, true);}
       | _FALSE                        {printf("Value\n"); $$ = new LiteralNode(VarType::BOOL, false);}
       | _OPAREN Exp _CPAREN           {printf("Value\n"); $$ = $2; }
       | Id _OPAREN Args _CPAREN _SEMI {printf("Value\n"); $$ = new FuncCallNode($1, $3);}
       ;

Id     : _ID {printf("Id\n"); $$ = new VarNode($1);}
       ;

%%

int yyerror(const char* msg) { 
       fputs(msg, stderr); 
       return 0; 
}