%{
	#include "y.tab.h"
	extern int lineno; 
%}

digit		[0-9] 
alpha		[a-zA-Z]
space 		[ \t]
id 			[a-zA-Z_][a-zA-Z_0-9]*
literal 	\"([^\\\"]|\\.)*\"

%%
{digit}+	{ 
	yylval.iVal = atoi(yytext);
	printf("digit(%d)\n", yylval.iVal);
	return _NUMBER;
}

"int" 		{ return _INT; 		}
"float" 	{ return _FLOAT; 	}
"bool"		{ return _BOOL; 	}
"char"		{ return _CHAR; 	}
"void"		{ return _VOID; 	}
"true"		{ return _TRUE; 	}
"false"		{ return _FALSE; 	}
"if"		{ return _IF; 		}
"else"		{ return _ELSE; 	}
"for"		{ return _FOR; 		}
"in"		{ return _IN; 	}
"loop"		{ return _LOOP; 	}
"break"		{ return _BREAK; 	}
"fn" 		{ return _FUNC; 	}
"return" 	{ return _RETURN; 	}
"let"		{ return _LET;}

{id}		{ 
	yylval.sVal = (char*)malloc(yyleng); 
	sprintf(yylval.sVal, "%s", yytext);
	printf("id(%s)\n", yylval.sVal);
	return _ID;
}
{literal}	{ 
	yylval.sVal = (char*)malloc(yyleng); 
	sprintf(yylval.sVal, "%s", yytext);
	printf("literal(%s)\n", yylval.sVal);
	return _LITERAL;
}
{space}	{ }

","			{ return _COMMA; 	}
"="			{ return _ASS; 		}
";"			{ return _SEMI; 	} 
":"			{ return _COLON; 	} 
"("			{ return _OPAREN; 	}
")" 		{ return _CPAREN; 	}
"{"			{ return _OCURLY; 	}
"}" 		{ return _CCURLY; 	}
"["			{ return _OBRACK; 	}
"]"			{ return _CBRACK; 	}
"->"		{ return _RIGHTARROW; }

"+" 		{ return _PLUS; 	}
"-"			{ return _MINUS; 	}
"*" 		{ return _TIMES; 	}
"%" 		{ return _MOD; 		}
"/" 		{ return _DIV;		}

"&&"		{ return _AND; 		}
"||"		{ return _OR; 		}

">"			{ return _GT; 		}
"<"			{ return _LT; 		}
">=" 		{ return _GE; 		}
"<="		{ return _LE; 		}
"=="		{ return _EQ; 		}
"!="		{ return _NEQ; 		}

"\n"		{ lineno++; 		}


%%

int yywrap(){ 
	return 1; 
} 
