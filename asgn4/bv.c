#include "bv.h"
#include <stdio.h>
#include <stdlib.h>

BitVector *bv_create(uint32_t bit_len) {
  BitVector *v = (BitVector *)malloc(sizeof(BitVector));
  if (!v) {
    return 0;
  }
  // Likely unnecessary but used to ensure no larger problems
  if (bit_len < 1) {
    bit_len = 1;
  }
  v->length = bit_len;

  v->vector = (uint8_t *)calloc((bit_len / 8) + 1, sizeof(uint8_t));

  if (!v->vector) {
    return 0;
  }
  return v;
}

void bv_delete(BitVector *v) {
  free(v->vector);
  free(v);
}

uint32_t bv_get_len(BitVector *v) { return v->length; }

void bv_set_bit(BitVector *v, uint32_t i) {
  uint8_t one = 1;
  // Creates 00...1...00
  // uint8_t mask = one<<(7 - (i%8));
  uint8_t mask = one << (i % 8);
  v->vector[i / 8] |= mask;
}

void bv_clr_bit(BitVector *v, uint32_t i) {
  uint8_t one = 1;
  // Invert so 00...1...00 becomes 11...0...11
  uint8_t mask = ~(one << (i % 8));
  v->vector[i / 8] &= mask;
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  uint8_t one = 1;
  uint8_t pos = i % 8;
  return ((v->vector[i / 8] & (one << pos)) >> pos);
}

void bv_set_all_bits(BitVector *v) {
  for (uint8_t i = 0; i < v->length / 8 + 1; i++) {
    v->vector[i] = 0xFF;
  }
  return;
}
