#ifndef __LL_H__
#define __LL_H__

#ifndef NIL
#define NIL (void *)0
#endif

#include "hatter.h"
#include <inttypes.h>
#include <stdbool.h>

extern bool move_to_front;

typedef struct ListNode ListNode;

//
// Struct definition of a ListNode.
//
// gs:  HatterSpeak struct containing oldspeak and its hatterspeak translation.
//
struct ListNode {
  HatterSpeak *gs;
  ListNode *next;
};

//
// Constructor for a ListNode.
//
// gs:  HatterSpeak struct containing oldspeak and its hatterspeak translation.
//
ListNode *ll_node_create(HatterSpeak *gs);

//
// Destructor fro a ListNode.
//
// n:   The ListNode to free.
//
void ll_node_delete(ListNode *n);

//
// Destructor for a linked list of ListNodes.
//
// head:    The head of the linked list.
//
void ll_delete(ListNode *head);

//
// Creates and inserts a ListNode into a linked list
//
// head:    The head of the linked list to insert in
// gs:      HatterSpeak struct.
//
ListNode *ll_insert(ListNode **head, HatterSpeak *gs);

//
// Searches for a specific key in a linked list
// Returns the ListNode if found and Null otherwise
//
// head:    The head of the linked list to search in
// key:     The key to search for
ListNode *ll_lookup(ListNode **head, char *key);

//
// Returns length of Linked List -- number of nodes
//
// *head:   head of linked list
//
uint32_t ll_length(ListNode *head);

// Prints Linked List
//
void ll_print(ListNode *head);

int get_seeks();

int get_traversed();

#endif
