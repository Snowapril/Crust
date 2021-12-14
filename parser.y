%{
	#include <stdio.h> 
       using namespace std; 
	int yyerror(const char* msg), yylex(); 
       int lineno = 1;
%}	
%union {
	int iVal; 
	char* sVal;  
}

%token <iVal> _NUMBER
%token <sVal> _ID _LITERAL

%token _IF _ELSE _WHILE _RETURN _FUNC _FOR _LOOP _BREAK
%token _OPAREN _CPAREN _OCURLY _CCURLY _OBRACK _CBRACK 
%token _SEMI _COLONS _COMMA _ASS  
%token _AND _OR 
%token _PLUS _MINUS _TIMES _MOD _DIV 
%token _GT _LT _GE _LE _EQ _NEQ 
%token _INT _BOOL _CHAR _VOID 
%token _TRUE _FALSE

%start Prog

%%
Prog   : {}
       ;

%%

int yyerror(const char* msg) { 
       fputs(msg, stderr); 
       return 0; 
}