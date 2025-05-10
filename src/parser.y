%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
void yyerror(const char *s);
ASTNode* root;
%}

%union {
    int integer;
    int boolean;
    char* str;
    struct ASTNode* ast;
}

%token <integer> INTEGER
%token <boolean> BOOL_LITERAL
%token <str> IDENT STRING

%token INT FLOAT BOOL STR
%token IF ELIF ELSE RETURN

%type <ast> program stmt stmt_list expr
%type type  // <-- temporairement sans type explicite, évite les warnings

%%

program:
    stmt_list               { root = $1; }
    | stmt_list '\n'        { root = $1; }
    ;

stmt_list:
    stmt '\n'               { $$ = new_stmt_list_node($1, NULL); }
    | stmt_list stmt '\n'   { $$ = new_stmt_list_node($2, $1); }
    ;

stmt:
    type IDENT '=' expr     { $$ = new_decl_node($2, $4); }
    | RETURN expr           { $$ = new_return_node($2); }
    | IF '(' expr ')' ':' stmt { $$ = new_if_node($3, $6); }
    ;

expr:
    INTEGER               { $$ = new_int_node($1); }
    | BOOL_LITERAL        { $$ = new_bool_node($1); }
    | STRING              { $$ = new_string_node($1); }
    | IDENT               { $$ = new_ident_node($1); }
    ;

type:
    INT
    | FLOAT
    | BOOL
    | STR
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}
