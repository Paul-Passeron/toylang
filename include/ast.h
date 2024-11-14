/**
 * ast.h
 * Copyright (C) 2024 Paul Passeron
 * AST header file
 * Paul Passeron <paul.passeron2@gmail.com>
 */

#ifndef AST_H
#define AST_H

#include "lexer.h"

typedef struct ast_t ast_t;

typedef enum ast_kind_t {
  AST_IDENTIFIER,
  AST_BINOP,
  AST_LET,
  AST_INTLIT,
  AST_PROG,
} ast_kind_t;

typedef struct ast_identifier_t {
  token_t tok;
} ast_identifier_t;

typedef struct ast_program_t {
  ast_t **stmts;
  size_t stmts_len;
} ast_program_t;

typedef struct ast_binop_t {
  token_t op;
  ast_t *lhs;
  ast_t *rhs;
} ast_binop_t;

typedef struct ast_let_t {
  token_t name;
  ast_t *value;
} ast_let_t;

typedef struct ast_intlit_t {
  token_t tok;
} ast_intlit_t;

ast_t *new_identifier(token_t tok);
void free_identifier(ast_t *iden);

ast_t *new_binop(token_t tok, ast_t *lhs, ast_t *rhs);
void free_binop(ast_t *binop);

ast_t *new_let(token_t name, ast_t *value);
void free_let(ast_t *let);

ast_t *new_intlit(token_t tok);
void free_intlit(ast_t *intlit);

ast_t *new_program(ast_t **stmts, size_t stmts_len);
void free_program(ast_t *program);

void dump_ast(ast_t *node, int depth);

typedef union ast_as_t {
  ast_identifier_t identifier;
  ast_binop_t binop;
  ast_let_t let;
  ast_intlit_t intlit;
  ast_program_t prog;
} ast_as_t;

struct ast_t {
  ast_kind_t kind;
  ast_as_t as;
};

#endif // AST_H
