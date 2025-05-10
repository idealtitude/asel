%{
#include "parser.h"
#include "ast.h"
#include <string.h>

void yyerror(const char *s);
%}

%option noyywrap

digit       [0-9]
id          [a-zA-Z_][a-zA-Z0-9_]*
strlit      \"([^\"\\]|\\.)*\"
ws          [ \t]+

%%

"if"        { return IF; }
"elif"      { return ELIF; }
"else"      { return ELSE; }
"int"       { return INT; }
"float"     { return FLOAT; }
"bool"      { return BOOL; }
"str"       { return STR; }
"true"      { yylval.boolean = 1; return BOOL_LITERAL; }
"false"     { yylval.boolean = 0; return BOOL_LITERAL; }
"return"    { return RETURN; }

{strlit}    { yylval.str = strdup(yytext); return STRING; }
{digit}+    { yylval.integer = atoi(yytext); return INTEGER; }
{id}        { yylval.str = strdup(yytext); return IDENT; }

"="         { return '='; }
"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }
":"         { return ':'; }
";"         { return ';'; }
"\n"        { return '\n'; }

{ws}        ;

";;"([^;]|;[^;])*";;" { /* multi-line comment */ }

.           { return yytext[0]; }

%%
