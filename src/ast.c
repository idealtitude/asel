#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

//ASTNode* root = NULL;

ASTNode* new_int_node(int val)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_INT;
    node->data.int_val = val;
    return node;
}

ASTNode* new_bool_node(int val)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_BOOL;
    node->data.bool_val = val;
    return node;
}

ASTNode* new_string_node(const char* str)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_STRING;
    node->data.str_val = str ? strdup(str) : NULL;

    return node;
}

ASTNode* new_ident_node(const char* str)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_IDENT;
    node->data.str_val = str ? strdup(str) : NULL;

    return node;
}

ASTNode* new_decl_node(const char* name, ASTNode* expr)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_DECL;
    node->data.decl.name = name ? strdup(name) : name;
    node->data.decl.value = expr;
    return node;
}

ASTNode* new_return_node(ASTNode* expr)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_RETURN;
    node->data.return_expr = expr;
    return node;
}

ASTNode* new_if_node(ASTNode* cond, ASTNode* body)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_IF;
    node->data.if_stmt.cond = cond;
    node->data.if_stmt.body = body;
    return node;
}

ASTNode* new_stmt_list_node(ASTNode* stmt, ASTNode* next)
{
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_STMT_LIST;
    node->data.stmt_list.stmt = stmt;
    node->data.stmt_list.next = next;
    return node;
}

void print_ast(ASTNode* node, int indent)
{
    if (!node) return;

    for (int i = 0; i < indent; ++i)
	{
		printf("  ");
	}

    switch (node->type) {
        case AST_INT:
            printf("INT: %d\n", node->data.int_val);
            break;
        case AST_BOOL:
            printf("BOOL: %s\n", node->data.bool_val ? "true" : "false");
            break;
        case AST_STRING:
            printf("STRING: \"%s\"\n", node->data.str_val);
            break;
        case AST_IDENT:
            printf("IDENT: %s\n", node->data.str_val);
            break;
        case AST_DECL:
            printf("DECL: %s =\n", node->data.decl.name);
            print_ast(node->data.decl.value, indent + 1);
            break;
        case AST_RETURN:
            printf("RETURN\n");
            print_ast(node->data.return_expr, indent + 1);
            break;
        case AST_IF:
            printf("IF condition:\n");
            print_ast(node->data.if_stmt.cond, indent + 1);
            printf("IF body:\n");
            print_ast(node->data.if_stmt.body, indent + 1);
            break;
        case AST_STMT_LIST:
            print_ast(node->data.stmt_list.stmt, indent);
            print_ast(node->data.stmt_list.next, indent);
            break;
    }
}

void free_ast(ASTNode* node)
{
    if (!node) return;

    switch (node->type)
	{
        case AST_STRING:
        case AST_IDENT:
            free(node->data.str_val);
            break;
        case AST_DECL:
            free(node->data.decl.name);
            free_ast(node->data.decl.value);
            break;
        case AST_RETURN:
            free_ast(node->data.return_expr);
            break;
        case AST_IF:
            free_ast(node->data.if_stmt.cond);
            free_ast(node->data.if_stmt.body);
            break;
        case AST_STMT_LIST:
            free_ast(node->data.stmt_list.stmt);
            free_ast(node->data.stmt_list.next);
            break;
        default:
            break;
    }

    free(node);
}
