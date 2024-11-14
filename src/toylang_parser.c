#include "../include/toylang_parser.h"
token_t *parse_token_lexeme(lexer_t *l, int *worked, string_view_t lexeme) {
  token_t tok = next(l);
  *worked = 0;
  if (is_error_tok(tok)) {
    return NULL;
  }
  if (sv_eq(tok.lexeme, lexeme)) {
    token_t *res = malloc(sizeof(token_t));
    *res = tok;
    *worked = 1;
    return res;
  }
  return NULL;
}

token_t *parse_token_kind(lexer_t *l, int *worked, int kind) {
  token_t tok = next(l);
  *worked = 0;
  if (is_error_tok(tok)) {
    return NULL;
  }
  if (tok.kind == kind) {
    token_t *res = malloc(sizeof(token_t));
    *res = tok;
    *worked = 1;
    return res;
  }
  return NULL;
}

// RULE let
void *parse_let_c0(lexer_t *l, int *worked);

// RULE stmt
void *parse_stmt_c0(lexer_t *l, int *worked);

// RULE leaf
void *parse_leaf_c0(lexer_t *l, int *worked);

void *parse_leaf_c1(lexer_t *l, int *worked);

// RULE expr
void *parse_expr_c0(lexer_t *l, int *worked);

void *parse_expr_c1(lexer_t *l, int *worked);

void *parse_expr_c2(lexer_t *l, int *worked);

// RULE program
void *parse_program_c0(lexer_t *l, int *worked);

// RULE let
void *parse_let(lexer_t *l, int *worked) {
  *worked = 0;
  int rule_worked = 0;
  void *rule_res = NULL;
  lexer_t rule_cpy = *l;
  rule_res = parse_let_c0(&rule_cpy, &rule_worked);
  if (rule_worked) {
    *worked = 1;
    *l = rule_cpy;
    return rule_res;
  }
  return NULL;
}

// RULE stmt
void *parse_stmt(lexer_t *l, int *worked) {
  *worked = 0;
  int rule_worked = 0;
  void *rule_res = NULL;
  lexer_t rule_cpy = *l;
  rule_res = parse_stmt_c0(&rule_cpy, &rule_worked);
  if (rule_worked) {
    *worked = 1;
    *l = rule_cpy;
    return rule_res;
  }
  return NULL;
}

// RULE leaf
void *parse_leaf(lexer_t *l, int *worked) {
  *worked = 0;
  int rule_worked = 0;
  void *rule_res = NULL;
  lexer_t rule_cpy = *l;
  rule_res = parse_leaf_c0(&rule_cpy, &rule_worked);
  if (rule_worked) {
    *worked = 1;
    *l = rule_cpy;
    return rule_res;
  }
  rule_cpy = *l;
  rule_res = parse_leaf_c1(&rule_cpy, &rule_worked);
  if (rule_worked) {
    *worked = 1;
    *l = rule_cpy;
    return rule_res;
  }
  return NULL;
}

// RULE expr
void *parse_expr(lexer_t *l, int *worked) {
  *worked = 0;
  int rule_worked = 0;
  void *rule_res = NULL;
  lexer_t rule_cpy = *l;
  rule_res = parse_expr_c0(&rule_cpy, &rule_worked);
  if (rule_worked) {
    *worked = 1;
    *l = rule_cpy;
    return rule_res;
  }
  rule_cpy = *l;
  rule_res = parse_expr_c1(&rule_cpy, &rule_worked);
  if (rule_worked) {
    *worked = 1;
    *l = rule_cpy;
    return rule_res;
  }
  rule_cpy = *l;
  rule_res = parse_expr_c2(&rule_cpy, &rule_worked);
  if (rule_worked) {
    *worked = 1;
    *l = rule_cpy;
    return rule_res;
  }
  return NULL;
}

// RULE program
void *parse_program(lexer_t *l, int *worked) {
  *worked = 0;
  int rule_worked = 0;
  void *rule_res = NULL;
  lexer_t rule_cpy = *l;
  rule_res = parse_program_c0(&rule_cpy, &rule_worked);
  if (rule_worked) {
    *worked = 1;
    *l = rule_cpy;
    return rule_res;
  }
  return NULL;
}

void *parse_let_c0(lexer_t *l, int *worked) {
  *worked = 0;
  free(parse_token_lexeme(l, worked, SV("let")));
  if (!*worked) {
    return NULL;
  }
  void *elem_1 = parse_token_kind(l, worked, IDENTIFIER);
  if (!*worked) {
    return NULL;
  }
  free(parse_token_lexeme(l, worked, SV("=")));
  if (!*worked) {
    return NULL;
  }
  void *elem_3 = parse_expr(l, worked);
  if (!*worked) {
    return NULL;
  }
  free(parse_token_lexeme(l, worked, SV(";")));
  if (!*worked) {
    return NULL;
  }

  token_t *name_ptr = elem_1;
  token_t name = *name_ptr;
  free(name_ptr);
  ast_t *expr_ptr = elem_3;
  return new_let(name, expr_ptr);
}
void *parse_stmt_c0(lexer_t *l, int *worked) {
  *worked = 0;
  void *elem_0 = parse_let(l, worked);
  if (!*worked) {
    return NULL;
  }
  return elem_0;
}
void *parse_leaf_c0(lexer_t *l, int *worked) {
  *worked = 0;
  void *elem_0 = parse_token_kind(l, worked, INTLIT);
  if (!*worked) {
    return NULL;
  }

  token_t *lit_ptr = elem_0;
  token_t lit = *lit_ptr;
  free(lit_ptr);
  return new_intlit(lit);
}
void *parse_leaf_c1(lexer_t *l, int *worked) {
  *worked = 0;
  void *elem_0 = parse_token_kind(l, worked, IDENTIFIER);
  if (!*worked) {
    return NULL;
  }

  token_t *lit_ptr = elem_0;
  token_t lit = *lit_ptr;
  free(lit_ptr);
  return new_identifier(lit);
}
void *parse_expr_c0(lexer_t *l, int *worked) {
  *worked = 0;
  void *elem_0 = parse_leaf(l, worked);
  if (!*worked) {
    return NULL;
  }
  void *elem_1 = parse_token_lexeme(l, worked, SV("+"));
  if (!*worked) {
    return NULL;
  }
  void *elem_2 = parse_leaf(l, worked);
  if (!*worked) {
    return NULL;
  }

  ast_t *lh = elem_0;
  ast_t *rh = elem_2;
  token_t *op_ptr = elem_1;
  token_t op = *op_ptr;
  free(op_ptr);
  return new_binop(op, lh, rh);
}
void *parse_expr_c1(lexer_t *l, int *worked) {
  *worked = 0;
  void *elem_0 = parse_leaf(l, worked);
  if (!*worked) {
    return NULL;
  }
  void *elem_1 = parse_token_lexeme(l, worked, SV("*"));
  if (!*worked) {
    return NULL;
  }
  void *elem_2 = parse_leaf(l, worked);
  if (!*worked) {
    return NULL;
  }

  ast_t *lh = elem_0;
  ast_t *rh = elem_2;
  token_t *op_ptr = elem_1;
  token_t op = *op_ptr;
  free(op_ptr);
  return new_binop(op, lh, rh);
}
void *parse_expr_c2(lexer_t *l, int *worked) {
  *worked = 0;
  void *elem_0 = parse_leaf(l, worked);
  if (!*worked) {
    return NULL;
  }

  return elem_0;
}
void *parse_program_c0(lexer_t *l, int *worked) {
  *worked = 0;

  size_t prog_cap = 16;
  size_t prog_count = 0;
  ast_t **res = malloc(sizeof(ast_t *) * prog_cap);
  lexer_t cpy = *l;
  while (!is_done(l)) {
    int w = false;
    ast_t *stmt = parse_stmt(&cpy, &w);
    if (!w)
      break;
    *l = cpy;
    if (prog_count >= prog_cap) {
      prog_cap *= 2;
      res = realloc(res, sizeof(ast_t *) * prog_cap);
    }
    res[prog_count++] = stmt;
  }
  *worked = 1;
  res = realloc(res, sizeof(ast_t *) * (prog_count + 1));
  res[prog_count] = NULL;
  return new_program(res, prog_count);
}
