#include "code.h"
#include "io.h"
#include "trie.h"
#include "word.h"
#include <fcntl.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "vi:o:"

uint8_t bitlen(uint16_t x);

uint64_t total_bits;
uint64_t total_syms;

struct stat infstats;

int main(int argc, char **argv) {
  int op = 0;
  bool stats = false;
  bool in = false;
  bool out = false;
  char *in_name;
  char *out_name;
  int infile = STDIN_FILENO;
  int outfile = STDOUT_FILENO;

  while ((op = getopt(argc, argv, OPTIONS)) != -1) {
    switch (op) {
    case 'v':
      stats = true;
      break;
    case 'i':
      in_name = optarg;
      in = true;
      break;
    case 'o':
      out_name = optarg;
      out = true;
      break;
    default:
      printf("Invalid arguments\n");
      return 0;
    }
  }

  if (in) {
    infile = open(in_name, O_RDONLY);
    if (infile == -1) {
      close(infile);
      printf("INFILE READ FAILED\n");
      return 0;
    }
  }

  if (out) {
    outfile = open(out_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (outfile == -1) {
      close(outfile);
      printf("OUTFILE READ FAILED\n");
      if (in) {
        close(infile);
      }
      return 0;
    }
  }

  fstat(infile, &infstats);

  FileHeader *infhead;
  infhead = (FileHeader *)calloc(1, sizeof(FileHeader));
  if (infhead == NULL) {
    close(infile);
    close(outfile);
    return 0;
  }
  infhead->magic = MAGIC;
  infhead->protection = infstats.st_mode;

  write_header(outfile, infhead);

  free(infhead);

  TrieNode *root = trie_create();
  TrieNode *curr_node = root;
  if (!curr_node) {
    close(infile);
    close(outfile);
    return 0;
  }
  TrieNode *prev_node = NULL;

  uint8_t curr_sym = 0;
  uint8_t prev_sym = 0;
  uint16_t next_code = START_CODE;

  while (read_sym(infile, &curr_sym)) {
    // printf("sym: %c\n", curr_sym);
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

  if (stats) {
    int64_t c_bytes =
        (total_bits % 8 < 4) ? total_bits / 8 : total_bits / 8 + 1;
    printf("Compressed file size: %ld bytes\n", c_bytes);
    int64_t u_bytes = total_syms;
    printf("Uncompressed file size: %ld bytes\n", u_bytes);
    double one = 1;
    double cmp_ratio = 100 * (one - ((double)c_bytes / u_bytes));
    printf("Compression ratio: %.2lf%%\n", cmp_ratio);
  }

  trie_delete(root);
  close(infile);
  close(outfile);

  return 0;
}

uint8_t bitlen(uint16_t x) { return log2(x) + 1; }
