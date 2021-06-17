#include "io.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BLOCK 4096

uint64_t total_syms;
uint64_t total_bits;

static uint8_t sym_buf[BLOCK];
static int sym_index = 0;

static uint8_t bit_buf[BLOCK];
static int bit_index = 0;

// static uint8_t byte_index = 0;

// total_syms -- used for statistics
// total_bits -- used for statistics

int read_bytes(int infile, uint8_t *buf, int to_read) {
  int rb = 0;
  int total = 0;

  do {
    rb = read(infile, buf + total, to_read - total);
    total += rb;
  } while (rb > 0 && total != to_read);

  return total;
}

int write_bytes(int outfile, uint8_t *buf, int to_write) {
  int written = 0;
  int total = 0;

  do {
    written = write(outfile, buf + total, to_write - total);
    total += written;
  } while (written > 0 && total != to_write);

  return total;
}

void read_header(int infile, FileHeader *header) {
  uint64_t head_count = 0;
  head_count = read_bytes(infile, (uint8_t *)header, sizeof(FileHeader));
  total_bits += (head_count * 8);
  return;
}

void write_header(int outfile, FileHeader *header) {
  uint64_t head_count = 0;
  head_count = write_bytes(outfile, (uint8_t *)header, sizeof(FileHeader));
  total_bits += (head_count * 8);
  // printf("PROTECTION: %d\n", header->protection);
  return;
}

// sym_buf[BLOCK]
// sym_index
bool read_sym(int infile, uint8_t *sym) {
  static int end = 0;

  // If first time running read_sym
  if (sym_index == 0) {
    end = read_bytes(infile, sym_buf, BLOCK);
  }
  *sym = sym_buf[sym_index++];
  total_syms++;

  // If reached end of buffer, reset and overwrite
  if (sym_index == BLOCK) {
    sym_index = 0;
  }

  if (end == BLOCK) {
    return true;
  } else {

    if (sym_index == end + 1) {
      return false;
    } else {
      return true;
    }
  }
}

// bit_buf[BLOCK]
// bit_index && byte_index

void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {
  // printf("bits: %d\n", bit_index);
  total_bits += (8 + bitlen);

  // BUFFER CODE
  for (uint8_t i = 0; i < bitlen; i++) {

    if (code & 1) {
      bit_buf[bit_index / 8] |= (1 << (bit_index % 8));
    } else {
      bit_buf[bit_index / 8] &= ~(1 << (bit_index % 8));
    }
    bit_index++;
    code >>= 1;

    // Check to see if buffer is full: write to outfile
    if (bit_index / 8 == BLOCK) {
      // printf("Wrote bytes in code\n");
      write_bytes(outfile, bit_buf, BLOCK);
      bit_index = 0;
    }
  }

  // BUFFER SYM

  for (uint8_t i = 0; i < 8; i++) {

    // Set bit in buffer to corresponding bit in symbol
    if (/*sym & (i << (i % 8))*/ sym & 1) { // sym & 1
      bit_buf[bit_index / 8] |= (1 << (bit_index % 8));
    } else {
      bit_buf[bit_index / 8] &= ~(1 << (bit_index % 8));
    }
    bit_index++;
    sym >>= 1;

    // Check to see if buffer is full: write to outfile
    if (bit_index / 8 == BLOCK) {
      // printf("Wrote bytes in sym\n");
      write_bytes(outfile, bit_buf, BLOCK);
      bit_index = 0;
    }
  }

  return;
}

void flush_pairs(int outfile) {

  // Check if there are things to be flushed
  if (bit_index != 0) {
    int bytes;
    if (bit_index % 8 == 0) {
      bytes = bit_index / 8;
    } else {
      bytes = bit_index / 8 + 1;
    }
    // printf("wrote out in flush pairs\n");
    write_bytes(outfile, bit_buf, bytes); // Be careful for static problems
  }

  return;
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {

  // READ CODE
  total_bits += (8 + bitlen);
  *code = 0;

  for (uint8_t i = 0; i < bitlen; i++) {

    // READ TO BUFFER IF FIRST CALL
    if (bit_index == 0) {
      // printf("Read bytes in read_pair\n");
      read_bytes(infile, bit_buf, BLOCK);
    }

    if (bit_buf[bit_index / 8] & (1 << (bit_index % 8))) {
      *code |= (1 << (i % 16));
    } else {
      *code &= ~(1 << (i % 16));
    }
    bit_index++;

    // RESET bit_index IF NEEDED (END OF BUFFER)
    if (bit_index / 8 == BLOCK) {
      bit_index = 0;
    }
  }

  // printf("RP code: %d\n", *code);
  // READ SYM
  *sym = 0;

  for (uint8_t i = 0; i < 8; i++) {

    // READ TO BUFFER IF FIRST CALL
    if (bit_index == 0) {
      read_bytes(infile, bit_buf, BLOCK);
    }

    if (bit_buf[bit_index / 8] & (1 << (bit_index % 8))) {
      *sym |= (1 << (i % 8));
    } else {
      *sym &= ~(1 << (i % 8));
    }
    bit_index++;

    // RESET bit_index IF NEEDED (END OF BUFFER)
    if (bit_index / 8 == BLOCK) {
      bit_index = 0;
    }
  }

  return *code != STOP_CODE;
}

void buffer_word(int outfile, Word *w) {
  if (!w) {
    return;
  }
  total_syms += w->len;
  // printf("in buffer word\n");

  for (uint64_t i = 0; i < w->len; i++) {
    // printf("adding sym");
    sym_buf[sym_index++] = w->syms[i];

    if (sym_index == BLOCK) {
      // printf("Writing out in buf_word\n");
      write_bytes(outfile, sym_buf, BLOCK);
      sym_index = 0;
    }
  }

  return;
}

void flush_words(int outfile) {
  // printf("sym index in flush_words: %d", sym_index);
  if (sym_index != 0) {
    write_bytes(outfile, sym_buf, sym_index);
    // printf("Writing out in flush_words");
  }

  return;
}
