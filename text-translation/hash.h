#ifndef __HASH_H__
#define __HASH_H__

#ifndef NIL
#define NIL (void *)0
#endif

#include "ll.h"
#include <inttypes.h>
#include <stdlib.h>

//
// STruct definition for a HastTable
//
// salt:    The salt of the HastTable (used for hashing)
// length:  The maximum number of entries in the HashTable
// heads:   An array of linked list heads.
//
typedef struct HashTable {
  uint64_t salt[2];
  uint32_t length;
  ListNode **heads;
} HashTable;

//
// Constructor for a HashTable
//
// length:  Length of the HashTable
// salt:    Salt for the HastTable
//
HashTable *ht_create(uint32_t length);

//
// Destructor for a HashTable
//
// ht:  The HashTable
//
void ht_delete(HashTable *ht);

//
// Returns number of entries in hash table
//
// ht:   The Hashtable
//
uint32_t ht_count(HashTable *ht);

//
// Searches a HashTable for a key
// Returns the ListNode if found and returns NULL otherwise
// This should call the ll_lookup() function
//
// ht:  The HashTable
// key: The key to search for
//
ListNode *ht_lookup(HashTable *ht, char *key);

//
// First creates a new ListNode from HatterSpeak
// The created ListNode is then inserted into a HashTable
// This should call the ll_insert() function
//
// ht:  The HashTable
// gs:  The HatterSpeak to add to the HashTable
//
void ht_insert(HashTable *ht, HatterSpeak *gs);

// Gets length of array AKA ht->length
//
uint32_t ht_get_len(HashTable *ht);

// Prints Hashtable
//
void ht_print(HashTable *ht);

#endif
