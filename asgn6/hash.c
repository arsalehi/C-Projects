#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "ll.h"
#include "speck.h"

int seeks;
int traverses;

HashTable *ht_create(uint32_t length){
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x85ae998311115ae3;
        ht->salt[1] = 0xb6fac2ae33a40089;
        ht->length = length;
        ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
        return ht;
    }

    return (HashTable *)NIL;
}

void ht_delete(HashTable *ht){

    for(uint32_t i = 0; i < ht->length; ++i){
        if(ht->heads[i] != NULL){
            ll_delete(ht->heads[i]);
        }
    }
    free(ht->heads);
    free(ht);
    return;
}

uint32_t ht_count(HashTable *ht){
    uint32_t counter = 0;
    for(uint32_t i = 0; i < ht->length; ++i){
        if(ht->heads[i] != NULL){
            counter += ll_length(ht->heads[i]);
        }
    }
    return counter;
}

ListNode *ht_lookup(HashTable *ht, char *key){
    if(!ht){
        return (ListNode *)NIL;
    }

    uint32_t index = hash(ht->salt, key) % ht->length;
    //printf("INDEX WILL BE: %d\n", index);

    //Extra Security
    if(ht->heads[index] == NULL){
        return (ListNode *)NIL;
    }
    return ll_lookup(&(ht->heads[index]), key);;
}

void ht_insert(HashTable *ht, HatterSpeak *gs){

    //printf("Made it to insert\n");
    uint32_t index = hash(ht->salt, gs->oldspeak) % ht->length;
    if(ht->heads[index] == NULL){
        ht->heads[index] = ll_node_create(gs); // Has to be freed somewhere though?
        seeks++;
        //traverses++;
    } else {
        ll_insert(&(ht->heads[index]), gs);
    }
    return;
}

uint32_t ht_get_len(HashTable *ht){
    return ht->length;
}

void ht_print(HashTable *ht){
    for(uint32_t i = 0; i < ht_get_len(ht); i++){
        //printf("Made it here");
        if(ht->heads[i] != NULL){
            printf("%d: ", i);
            ll_print(ht->heads[i]);
        }
    }
    return;
}

