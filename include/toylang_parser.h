#include "lexer.h"
#include <stdlib.h>
// PREAMBULE:

// Toylang parser, generated using PPARSER.
#include "ast.h"
#include "toylang_lexer.h"

token_t *parse_token_lexeme(lexer_t *l, int *worked, string_view_t lexeme);
token_t *parse_token_kind(lexer_t *l, int *worked, int kind);
// RULE let
void *parse_let(lexer_t *l, int *worked);

// RULE stmt
void *parse_stmt(lexer_t *l, int *worked);

// RULE leaf
void *parse_leaf(lexer_t *l, int *worked);

// RULE expr
void *parse_expr(lexer_t *l, int *worked);

// RULE program
void *parse_program(lexer_t *l, int *worked);
