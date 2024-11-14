/**
 * toylang_lexer.c
 * Copyright (C) 2024 Paul Passeron
 * TOYLANG_LEXER source file
 * Paul Passeron <paul.passeron2@gmail.com>
 */

#include "../include/toylang_lexer.h"

void dump_token(token_t token) {
  print_location_t(stdout, token.location);
  printf("\'" SF "\' %s", SA(token.lexeme), human_token_kind(token.kind));
}

lexer_t new_toylang_lexer() {
  lexer_t l = {0};
  l.rules = new_rules();
  add_rule_to_lexer(&l, SV("let"), KEY_LET);
  add_bad_rule_to_lexer(&l, SV("/\\*"), SV("Unmatched multi-line comment."));
  add_rule_to_lexer(&l, SV("\\*"), MULT);
  add_rule_to_lexer(&l, SV("+"), PLUS);
  add_rule_to_lexer(&l, SV(";"), SEMICOLON);
  add_rule_to_lexer(&l, SV("="), EQ);
  add_rule_to_lexer(&l, SV("\\("), OPEN_PAR);
  add_rule_to_lexer(&l, SV("\\)"), CLOSE_PAR);
  add_rule_to_lexer(&l, SV("[0-9]([0-9])"), INTLIT);
  add_rule_to_lexer(&l, SV("[a-zA-Z_-_]([a-zA-Z_-_0-9])"), IDENTIFIER);
  add_skip_rule_to_lexer(&l, SV(" "));
  add_skip_rule_to_lexer(&l, SV("\n"));
  add_skip_rule_to_lexer(&l, SV("\t"));
  add_skip_rule_to_lexer(&l, SV("\b"));
  add_skip_rule_to_lexer(&l, SV("/\\**\\*/"));
  add_bad_rule_to_lexer(&l, SV("*"), SV("No rule."));
  return l;
}

const char *human_token_kind(int kind) {
  switch (kind) {

  case KEY_LET:
    return "KEY_LET";
  case IDENTIFIER:
    return "IDENTIFIER";
  case INTLIT:
    return "INTLIT";
  case EQ:
    return "EQ";
  case PLUS:
    return "PLUS";
  case MULT:
    return "MULT";
  case SEMICOLON:
    return "SEMICOLON";
  case OPEN_PAR:
    return "OPEN_PAR";
  case CLOSE_PAR:
    return "CLOSE_PAR";
  default:
    return "ERROR";
  }
}
