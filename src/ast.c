/**
 * ast.c
 * Copyright (C) 2024 Paul Passeron
 * AST source file
 * Paul Passeron <paul.passeron2@gmail.com>
 */

#include "../include/ast.h"
#include <stdlib.h>

// Function to create a new identifier node
ast_t *new_identifier(token_t tok) {
  ast_t *node = malloc(sizeof(ast_t));
  if (!node) {
    return NULL; // Handle memory allocation failure
  }
  node->kind = AST_IDENTIFIER;
  node->as.identifier.tok = tok;
  return node;
}

// Function to free an identifier node
void free_identifier(ast_t *iden) {
  free(iden); // Only free the identifier node itself
}

// Function to create a new identifier node
ast_t *new_intlit(token_t tok) {
  ast_t *node = malloc(sizeof(ast_t));
  if (!node) {
    return NULL; // Handle memory allocation failure
  }
  node->kind = AST_IDENTIFIER;
  node->as.identifier.tok = tok;
  return node;
}

// Function to free an identifier node
void free_intlit(ast_t *intlit) {
  free(intlit); // Only free the identifier node itself
}

// Function to create a new binary operation node
ast_t *new_binop(token_t tok, ast_t *lhs, ast_t *rhs) {
  ast_t *node = malloc(sizeof(ast_t));
  if (!node) {
    return NULL; // Handle memory allocation failure
  }
  node->kind = AST_BINOP;
  node->as.binop.op = tok;
  node->as.binop.lhs = lhs;
  node->as.binop.rhs = rhs;
  return node;
}

// Function to free a binary operation node
void free_binop(ast_t *binop) {
  if (binop) {
    // Free the left-hand side and right-hand side recursively
    free(binop->as.binop.lhs);
    free(binop->as.binop.rhs);
    free(binop); // Free the binary operation node itself
  }
}

// Function to create a new let node
ast_t *new_let(token_t name, ast_t *value) {
  ast_t *node = malloc(sizeof(ast_t));
  if (!node) {
    return NULL; // Handle memory allocation failure
  }
  node->kind = AST_LET;
  node->as.let.name = name;
  node->as.let.value = value;
  return node;
}

// Function to free a let node
void free_let(ast_t *let) {
  if (let) {
    free(let->as.let.value); // Free the value associated with the let
    free(let);               // Free the let node itself
  }
}

ast_t *new_program(ast_t **stmts, size_t stmts_len) {
  ast_t *program = malloc(sizeof(ast_t));
  program->as.prog = (ast_program_t){stmts, stmts_len};
  program->kind = AST_PROG;
  return program;
}
void free_program(ast_t *program) {
  for (size_t i = 0; i < program->as.prog.stmts_len; i++) {
    free(program->as.prog.stmts[i]);
    // TODO: improve and be recursive etc
  }
  free(program);
}

void pad(int n) {
  for (int i = 0; i < n; i++) {
    printf("  ");
  }
}

void dump_ast(ast_t *node, int depth) {
  if (!node) {
    return;
  }
  pad(depth);
  switch (node->kind) {
  case AST_IDENTIFIER: {
    printf("Identifier: " SF "\n",
           SA(node->as.identifier.tok
                  .lexeme)); // Assuming token_t has a lexeme field
  } break;
  case AST_BINOP: {
    printf("Binary Operation: " SF "\n",
           SA(node->as.binop.op.lexeme)); // Assuming token_t has a lexeme field
    pad(depth + 1);
    printf("Left Operand:\n");
    dump_ast(node->as.binop.lhs, depth + 2);
    pad(depth + 1);
    printf("Right Operand:\n");
    dump_ast(node->as.binop.rhs, depth + 2);
  } break;

  case AST_LET: {
    printf("Let Statement: " SF "\n",
           SA(node->as.let.name.lexeme)); // Assuming token_t has a lexeme field

    pad(depth + 1);
    printf("Value:\n");
    dump_ast(node->as.let.value, depth + 2);
  } break;
  case AST_PROG: {
    printf("Program:\n");
    for (size_t i = 0; i < node->as.prog.stmts_len; i++) {
      dump_ast(node->as.prog.stmts[i], depth + 1);
    }
  } break;
  default: {
    printf("Unknown AST Node\n");
  } break;
  }
}