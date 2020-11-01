#include "stack.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OPTIONS "rsn:"

void recursive_solution(int disks, char orig, char dest, char other);
void stack_solution(int disks, Stack *a, Stack *b, Stack *c);
void print_state_r(int disk, char peg1, char peg2);
void print_state_s(int disk, char peg1, char peg2);
void init_pegs(int disks, Stack *a);

// Stack*l refers to the last peg that gained a disk
Stack *move_smallest(Stack *l, Stack *a, Stack *b, Stack *c);
Stack *move_disk1(Stack *l, Stack *a, Stack *b, Stack *c);

int recurse_counter = 0;
int stack_counter = 0;

int disks = 5;

int main(int argc, char **argv) {

  int opt = 0;
  bool want_stack = false;
  bool want_recursion = false;

  while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
    switch (opt) {
    case 'r':
      want_recursion = true;
      break;
    case 's':
      want_stack = true;
      break;
    case 'n':
      disks = atoi(optarg);
      break;
    }
  }

  Stack *A = stack_create(disks, 'A');
  Stack *B = stack_create(disks, 'B');
  Stack *C = stack_create(disks, 'C');

  if (want_stack) {
    printf("================================\n");
    printf("----------   STACKS   ----------\n");
    printf("================================\n");
    stack_solution(disks, A, B, C);
    stack_delete(A);
    stack_delete(B);
    stack_delete(C);
    printf("\n");
    printf("Number of moves: %d\n", stack_counter);
    printf("\n");
  }
  if (want_recursion) {
    printf("================================\n");
    printf("--------   RECURSION  ----------\n");
    printf("================================\n");
    recursive_solution(disks, 'A', 'B', 'C');
    printf("\n");
    printf("Number of moves: %d\n", recurse_counter);
    printf("\n");
  }

  return 0;
}

void recursive_solution(int disks, char orig, char dest, char other) {
  if (disks == 1) {
    printf("Move disk %d from peg %c to peg %c\n", disks, orig, dest);
    recurse_counter++;
    return;
  }
  recursive_solution(disks - 1, orig, other, dest);
  print_state_r(disks, orig, dest);
  recursive_solution(disks - 1, other, dest, orig);
}

void stack_solution(int disks, Stack *a, Stack *b, Stack *c) {

  init_pegs(disks, a);

  int disk_val = stack_pop(a);
  Stack *l = a;
  if (disks % 2 == 0) {
    stack_push(c, disk_val);
    l = c;
    print_state_s(c->items[stack_peek(c) - 1], a->name, c->name);
  } else {
    stack_push(b, disk_val);
    l = b;
    print_state_s(b->items[stack_peek(b) - 1], a->name, b->name);
  }

  while (!(stack_empty(a)) || !(stack_empty(c))) {

    l = move_smallest(l, a, b, c);

    l = move_disk1(l, a, b, c);
  }

  return;
}

Stack *move_smallest(Stack *l, Stack *a, Stack *b, Stack *c) {
  Stack *potential1;
  Stack *potential2;
  int temp = 0;

  switch (l->name) {
  case 'A':
    potential1 = b;
    potential2 = c;
    break;
  case 'B':
    potential1 = a;
    potential2 = c;
    break;
  default:
    potential1 = a;
    potential2 = b;
    break;
  }

  if (stack_empty(potential1)) {
    // Move disk from potential2 to potential 1
    temp = stack_pop(potential2);
    stack_push(potential1, temp);
    print_state_s(potential1->items[stack_peek(potential1) - 1],
                  potential2->name, potential1->name);
    return potential1;
  } else if (stack_empty(potential2)) {
    // Move disk from potential1 to potential2
    temp = stack_pop(potential1);
    stack_push(potential2, temp);
    print_state_s(potential2->items[stack_peek(potential2) - 1],
                  potential1->name, potential2->name);
    return potential2;
  } else if (potential1->items[stack_peek(potential1) - 1] <
             potential2->items[stack_peek(potential2) - 1]) {
    // Move disk from potential1 to potential2
    temp = stack_pop(potential1);
    stack_push(potential2, temp);
    print_state_s(potential2->items[stack_peek(potential2) - 1],
                  potential1->name, potential2->name);
    return potential2;
  } else {
    // Move disk from potential2 to potential 1
    temp = stack_pop(potential2);
    stack_push(potential1, temp);
    print_state_s(potential1->items[stack_peek(potential1) - 1],
                  potential2->name, potential1->name);
    return potential1;
  }
}

Stack *move_disk1(Stack *l, Stack *a, Stack *b, Stack *c) {
  Stack *peg1;
  Stack *not_last;
  int temp = 0;

  // Determine which peg has the smallest disk on top, and which disk was not
  // just added to
  if (a->items[stack_peek(a) - 1] == 1) {
    peg1 = a;
    if (l->name == b->name) {
      not_last = c;
    } else {
      not_last = b;
    }
  } else if (b->items[stack_peek(b) - 1] == 1) {
    peg1 = b;
    if (l->name == a->name) {
      not_last = c;
    } else {
      not_last = a;
    }
  } else {
    peg1 = c;
    if (l->name == a->name) {
      not_last = b;
    } else {
      not_last = a;
    }
  }

  // Move smallest based on whether last disk moved was even or odd
  switch (l->items[stack_peek(l) - 1] % 2) {
  case 0:
    // Move smallest disk to peg that was last added to
    temp = stack_pop(peg1);
    stack_push(l, temp);
    print_state_s(l->items[stack_peek(l) - 1], peg1->name, l->name);
    return l;
    break;
  default:
    // Move smallest disk to peg NOT last added to
    temp = stack_pop(peg1);
    stack_push(not_last, temp);
    print_state_s(not_last->items[stack_peek(not_last) - 1], peg1->name,
                  not_last->name);
    return not_last;
    break;
  }

  return l;
}

void init_pegs(int disks, Stack *a) {

  for (int i = disks; i > 0; --i) {
    stack_push(a, i);
  }
  return;
}

void print_state_r(int disk, char peg1, char peg2) {
  printf("Move disk %d from peg %c to peg %c\n", disk, peg1, peg2);
  recurse_counter++;
  return;
}

void print_state_s(int disk, char peg1, char peg2) {
  printf("Move disk %d from peg %c to peg %c\n", disk, peg1, peg2);
  stack_counter++;
  return;
}
