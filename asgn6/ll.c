#include "ll.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int seeks;
int traverses;

ListNode *ll_node_create(HatterSpeak *gs) {
  ListNode *n = (ListNode *)malloc(sizeof(ListNode));
  if (!n) {
    if (gs) {
      hatter_delete(gs);
    }
    return (ListNode *)NIL;
  }

  if (!gs) {
    printf("Needs valid HatterSpeak struct\n");
    free(n);
    return (ListNode *)NIL;
  }

  n->gs = gs;
  n->next = NULL;

  return n;
}

void ll_node_delete(ListNode *n) {

  // printf("-- deleted node --\n");
  hatter_delete(n->gs);
  free(n);
  return;
}

void ll_delete(ListNode *head) {

  ListNode *temp = head;
  ListNode *next = temp->next;

  if (temp && !next) {
    ll_node_delete(temp);
    return;
  }

  while (temp != NULL) {
    // printf("Made it here\n");
    next = temp->next;
    ll_node_delete(temp);
    temp = next;
  }
  return;
}

ListNode *ll_insert(ListNode **head, HatterSpeak *gs) {

  if (ll_lookup(head, gs->oldspeak)) {
    hatter_delete(gs);
    // printf("deleted duplicate hatterspeak\n");
    return *head;
  }

  ListNode *new = ll_node_create(gs);
  if (!new) {
    return (ListNode *)NIL;
  }
  // printf("new node oldspeak: %s\n", gs->oldspeak);
  new->next = *head;
  *head = new; // may be done by hashtable??
  return new;
}

ListNode *ll_lookup(ListNode **head, char *key) {

  seeks++;

  ListNode *temp = *head;

  if (temp == NULL) {
    return (ListNode *)NIL;
    // printf("temp is not NULL\n");
  }

  if (!move_to_front) {
    traverses++;
  }

  ListNode *next = temp->next;

  // printf("Passed taking in ll values\n");

  if (temp == NULL) {
    return (ListNode *)NIL;
    // printf("temp is not NULL\n");
  }

  // If first element is desired element
  if (strcmp(temp->gs->oldspeak, key) == 0) {
    // traverses++;
    return temp;
  }

  // printf("Made it after string compare\n");

  while (next) {
    traverses++;
    if (strcmp(next->gs->oldspeak, key) == 0) {
      if (move_to_front) {
        // printf("mtf true\n");
        temp->next = next->next;
        next->next = *head;
        *head = next;
      }
      return next;
    }
    temp = next;
    next = next->next;
  }
  // printf("Made it to final return statement\n");
  return (ListNode *)NIL;
}

uint32_t ll_length(ListNode *head) {
  uint32_t counter = 0;
  ListNode *temp = head;
  while (temp) {
    counter++;
    temp = temp->next;
  }
  return counter;
}

void ll_print(ListNode *head) {

  if (!head) {
    printf("LL is EMPTY\n");
    return;
  }

  while (head->next) {
    printf("%s -- ", head->gs->oldspeak);
    head = head->next;
  }
  printf("%s\n", head->gs->oldspeak);
  return;
}

int get_seeks() { return seeks; }

int get_traversed() { return traverses; }
