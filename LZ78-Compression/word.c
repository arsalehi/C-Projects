#include "word.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define NIL (void *)0

Word *word_create(uint8_t *syms, uint64_t len) {
  Word *w = (Word *)malloc(sizeof(Word));
  if (!w) {
    return (Word *)NIL;
  }
  // printf("len is %lu\n", len);
  bool len0 = false;
  if (len == 0) {
    len0 = true;
  }
  if (!syms && !len0) {
    free(w);
    return (Word *)NIL;
  }
  w->syms = (uint8_t *)malloc(sizeof(uint8_t) * len);
  if (!w->syms && !len0) {
    free(w);
    return (Word *)NIL;
  }
  w->len = len;

  for (uint64_t i = 0; i < w->len; i++) {
    w->syms[i] = syms[i];
  }
  return w;
}

Word *word_append_sym(Word *w, uint8_t sym) {
  // printf("in word append sym\n");
  if (!w) {
    // printf("failed first condition wps\n");
    return (Word *)NIL;
  }

  Word *new = (Word *)malloc(sizeof(Word));
  if (!new) {
    // printf("failed malloc wps\n");
    return (Word *)NIL;
  }
  new->len = w->len + 1;

  new->syms = (uint8_t *)malloc(sizeof(uint8_t) * new->len);
  if (!new->syms) {
    // printf("failed syms condition wps\n");
    free(new);
    return (Word *)NIL;
  }
  // printf("created word in append\n");
  memcpy(new->syms, w->syms, w->len);

  // make sure memcpy did not fail
  if (!new->syms) {
    return (Word *)NIL;
  }
  // printf("memcpy successful\n");
  new->syms[new->len - 1] = sym;
  // printf("function successful\n");

  return new;
}

void word_delete(Word *w) {
  if (!w) {
    return;
  }
  free(w->syms);
  free(w);
}

WordTable *wt_create(void) {
  WordTable *wt = (WordTable *)calloc(MAX_CODE, sizeof(Word));
  if (!wt) {
    return (WordTable *)NIL;
  }
  wt[EMPTY_CODE] = word_create(NULL, 0);
  return wt;
}

void wt_reset(WordTable *wt) {
  for (int i = START_CODE; i < MAX_CODE;
       i++) { // CONSIDER IF YOU NEED TO ACCESS MAX CODE
    if (wt[i] != NULL) {
      word_delete(wt[i]);
      wt[i] = NULL;
    }
  }
}

void wt_delete(WordTable *wt) {
  for (int i = 0; i < MAX_CODE; i++) {
    if (wt[i] != NULL) {
      word_delete(wt[i]);
      wt[i] = NULL;
    }
  }
  free(wt);
}
