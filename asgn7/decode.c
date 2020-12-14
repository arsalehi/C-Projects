#include "code.h"
#include "io.h"
#include "trie.h"
#include "word.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "vi:o:"

uint64_t total_bits;
uint64_t total_syms;

struct stat infstats;

uint8_t bitlen(uint16_t x);

int main(int argc, char **argv) {
  int op = 0;
  char *in_name;
  char *out_name;
  int infile = STDIN_FILENO;
  int outfile = STDOUT_FILENO;
  bool stats = false;
  bool in = false;
  bool out = false;

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
      // printf("CASE O\n");
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
    // printf("IN OUT IF\n");
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

  FileHeader *head = (FileHeader *)calloc(1, sizeof(FileHeader));
  fchmod(infile, infstats.st_mode);
  read_header(infile, head);

  if (head->magic != MAGIC) {
    printf("MAGIC DID NOT CORRELATE\n");
    return 0;
  }

  WordTable *table = wt_create();
  uint8_t curr_sym = 0;
  uint16_t curr_code = 0;
  uint16_t next_code = START_CODE;

  // Decode loop
  while (read_pair(infile, &curr_code, &curr_sym, bitlen(next_code))) {
    // printf("Cur code: %d\n", curr_code);
    table[next_code] = word_append_sym(table[curr_code], curr_sym);
    buffer_word(outfile, table[next_code]);
    // printf("Buffered words\n");
    next_code++;
    if (next_code == MAX_CODE) {
      wt_reset(table);
      next_code = START_CODE;
    }
  }
  flush_words(outfile);

  if (stats) {
    int64_t c_bytes =
        (total_bits % 8 < 4) ? total_bits / 8 : total_bits / 8 + 1;
    printf("Compressed file size: %ld bytes\n", c_bytes);
    int64_t u_bytes = (int64_t)total_syms;
    printf("Uncompressed file size: %ld bytes\n", u_bytes);
    double one = 1;
    double cmp_ratio = 100 * (one - ((double)c_bytes / u_bytes));
    printf("Compression ratio: %.2lf%%\n", cmp_ratio);
  }

  free(head);
  close(infile);
  close(outfile);
  wt_delete(table);

  printf("RAN SUCCESSFULLY\n");
  return 0;
}

uint8_t bitlen(uint16_t x) { return log2(x) + 1; }
