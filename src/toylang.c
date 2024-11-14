/**
 * toylang.c
 * Copyright (C) 2024 Paul Passeron
 * TOYLANG source file
 * Paul Passeron <paul.passeron2@gmail.com>
 */

#include "../include/toylang_parser.h"
#include <stdio.h>

int main() {

  lexer_t l = new_toylang_lexer();
  char file[] = "test.tl";
  l.current_loc = (location_t){.filename = file, .col = 1, .line = 1};
  FILE *f = fopen(file, "r");
  if (!f) {
    perror("Could not open file: ");
    exit(1);
  }
  string_view_t s = from_file(f);
  l.remaining = s;

  lexer_t cpy = l;
  while (1) {
    token_t t = next(&cpy);
    if (is_error_tok(t))
      break;
    dump_token(t);
    printf("\n");
    fflush(stdout);
  }

  int worked = false;
  ast_t *prog = parse_program(&l, &worked);
  dump_ast(prog, 0);
  free(s.contents);
  return 0;
}
