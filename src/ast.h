#ifndef AST_H
#define AST_H

typedef enum
{
    AST_INT,
    AST_BOOL,
    AST_STRING,
    AST_IDENT,
    AST_DECL,
    AST_RETURN,
    AST_IF,
    AST_STMT_LIST
} ASTNodeType;

typedef struct ASTNode
{
    ASTNodeType type;
    union
	{
        int int_val;
        int bool_val;
        char* str_val;
        struct
		{
            char* name;
            struct ASTNode* value;
        } decl;
        struct ASTNode* return_expr;
        struct
		{
            struct ASTNode* cond;
            struct ASTNode* body;
        } if_stmt;
        struct
		{
            struct ASTNode* stmt;
            struct ASTNode* next;
        } stmt_list;
    } data;
} ASTNode;

ASTNode* new_int_node(int val);
ASTNode* new_bool_node(int val);
ASTNode* new_string_node(const char* str);
ASTNode* new_ident_node(const char* str);
ASTNode* new_decl_node(const char* name, ASTNode* expr);
ASTNode* new_return_node(ASTNode* expr);
ASTNode* new_if_node(ASTNode* cond, ASTNode* body);
ASTNode* new_stmt_list_node(ASTNode* stmt, ASTNode* next);
void print_ast(ASTNode* node, int indent);
void free_ast(ASTNode* node);

extern ASTNode* root;

#endif // AST_H
