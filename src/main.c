#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "ast.h"

extern FILE* yyin;

int main(int argc, char* argv[])
{
    if (argc != 2)
	{
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");

    if (!yyin) {
        perror("fopen");
        return 1;
    }

    if (yyparse() == 0) {
        printf("Parsing succeeded.\n");
        print_ast(root, 0);
        free_ast(root);
    }
	else
	{
        fprintf(stderr, "Parsing failed.\n");
    }

    fclose(yyin);
    return 0;
}
