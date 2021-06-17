
#include "code.h"
#include "io.h"
#include "trie.h"
#include "word.h"
#include <math.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdlib.h>

uint8_t bitlen(uint16_t x);

int main(void) {

  FILE *in = fopen("in.txt", "r");
  int infile = fileno(in);
  FILE *out = fopen("out.txt", "w");
  int outfile = fileno(out);

  FILE *test = fopen("test.txt", "w");
  int testfile = fileno(test);
  FILE *test2 = fopen("test2.txt", "r");
  int test2file = fileno(test2);

  uint8_t buf[100];
  for (int i = 0; i < 100; i++) {
    buf[i] = 0;
  }
  read_bytes(test2file, buf, 100);
  write_bytes(testfile, buf, 100);
  printf("Performed write and read test\n");

  TrieNode *root = trie_create();
  TrieNode *curr_node = root;
  TrieNode *prev_node = NULL;

  uint8_t curr_sym = 0;
  uint8_t prev_sym = 0;
  uint16_t next_code = START_CODE;

  // printf("! is %d\n", '!');

  while (read_sym(infile, &curr_sym)) {
    printf("sym: %c\n", curr_sym);
    TrieNode *next_node = trie_step(curr_node, curr_sym);

    if (next_node) {

      prev_node = curr_node;
      curr_node = next_node;

    } else {

      buffer_pair(outfile, curr_node->code, curr_sym, bitlen(next_code));
      curr_node->children[curr_sym] = trie_node_create(next_code);
      curr_node = root;
      next_code = next_code + 1;
    }

    if (next_code == MAX_CODE) {
      trie_reset(root);
      curr_node = root;
      next_code = START_CODE;
    }

    prev_sym = curr_sym;
  }

  if (curr_node != root) {
    buffer_pair(outfile, prev_node->code, prev_sym, bitlen(next_code));
    next_code = (next_code + 1) % MAX_CODE;
  }

  buffer_pair(outfile, STOP_CODE, 0, bitlen(next_code));
  flush_pairs(outfile);

  tn_print(root);

  fclose(test2);
  fclose(test);
  fclose(in);
  fclose(out);
  return 0;
}

uint8_t bitlen(uint16_t x) {

  return log2(x) + 1;
  /*
  int len = 0;
  do {
      len += 1;
      x >>= 1;
  } while (x > 0);
  return len;
  */
}
