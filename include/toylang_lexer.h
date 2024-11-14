/**
 * toylang_lexer.h
 * Copyright (C) 2024 Paul Passeron
 * TOYLANG_LEXER header file
 * Paul Passeron <paul.passeron2@gmail.com>
 */

#ifndef TOYLANG_LEXER_H
#define TOYLANG_LEXER_H

#include "lexer.h"

typedef enum token_kind_t {
  KEY_LET,
  IDENTIFIER,
  INTLIT,
  EQ,
  PLUS,
  MULT,
  SEMICOLON,
  OPEN_PAR,
  CLOSE_PAR,
} token_kind_t;

lexer_t new_toylang_lexer();
const char *human_token_kind(int kind);
void dump_token(token_t token);

#endif // TOYLANG_LEXER_H
