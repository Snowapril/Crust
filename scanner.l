%{
	#include "y.tab.h"
	extern int lineno; 
%}

digit		[0-9] 
alpha		[a-zA-Z]
space 		[ \t]
id 			[a-zA-Z_]+
literal 	\"([^\\\"]|\\.)*\"

%%
{digit}+	{ 
	yylval.iVal = atoi(yytext);
	return _NUMBER;
}
{id}		{ 
	yylval.sVal = (char*)malloc(yyleng); 
	sprintf(yylval.sVal, "%s", yytext);
	return _ID;
}
{literal}	{ 
	yylval.sVal = (char*)malloc(yyleng); 
	sprintf(yylval.sVal, "%s", yytext);
	return _LITERAL;
}
{space}	{ }

","			{ return _COMMA; 	}
"="			{ return _ASS; 		}
";"			{ return _SEMI; 	} 
"("			{ return _OPAREN; 	}
")" 		{ return _CPAREN; 	}
"{"			{ return _OCURLY; 	}
"}" 		{ return _CCURLY; 	}
"["			{ return _OBRACK; 	}
"]"			{ return _CBRACK; 	}

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

"int" 		{ return _INT; 		}
"float" 	{ return _INT; 		}
"bool"		{ return _BOOL; 	}
"char"		{ return _CHAR; 	}
"void"		{ return _VOID; 	}

"true"		{ return _TRUE; 	}
"false"		{ return _FALSE; 	}

"if"		{ return _IF; 		}
"else"		{ return _ELSE; 	}
"for"		{ return _FOR; 		}
"loop"		{ return _LOOP; 	}
"break"		{ return _BREAK; 	}
"fn" 		{ return _FUNC; 	}
"return" 	{ return _RETURN; 	}
%%

int yywrap(){ 
	return 1; 
} 
