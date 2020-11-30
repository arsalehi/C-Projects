//#include "bv.h"
#include "bf.h"
#include "bv.h"
#include "ll.h"
#include "hash.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

// Print BloomFilter for testing
//
void print_bf(BloomFilter *bf);

// Series of tests for BloomFilter
//
void test_bf(BloomFilter *bf);

// Print LinkedList starting at the head
//
void print_ll(ListNode *head);

// Test LinkedList 
//
void test_ll(void);

// Print Content of Hatterspeak "Object"
//
void print_hatter(HatterSpeak *gs);

// Tests on HashTable ADT
//
void test_hash();

// Used to print Hash Table 
//
void print_hash(HashTable *ht);


int main(void){

    //BloomFilter *bf = bf_create(2000);
    //test_bf(bf);
   // bf_delete(bf);
    test_hash();
    return 0;
}

void print_bf(BloomFilter *bf){
    printf("BitVector/BloomFilter State:\n");
    for(uint32_t i = 0; i <= bv_get_len(bf->filter); ++i){
        printf("loc: %d -- %d\n", i, bv_get_bit(bf->filter, i));
    }
    printf("\n");
    return;
}

void test_bf(BloomFilter *bf){
    char *words[] = {
        "word",
        "another",
        "quick",
        "verylong",
        "wow",
        "rocket",
        "league",
        "is",
        "addicting",
        "xd",
        "sadge",
        "monkaW",
        "monkaS",
        "pepelaugh",
        "pepemeltdown",
        "hasmods",
        "widepeepo",
        "pog",
        "pogchamp",
        "laksdajsdlkf",
        "eleven",
        "number",
        "hahahah",
        "fourteen",
        "ting",
        "real",
        "quentin",
        "juliana",
        "sammy",
        "daddy"
    };

    char *keys[] = {
        "word",
        "another",
        "quick",
        "verylong",
        "wow",
        "rocket",
        "league",
        "is",
        "addicting",
        "laksdajsdlkf",
        "eleven",
        "number",
        "hahahah",
        "fourteen",
        "ting",
        "real",
        "quentin",
        "juliana",
        "sammy",
        "daddy"
    };
    int key_size = 20;
    int word_size = 30;

    for(int i = 0; i < key_size; ++i){
        bf_insert(bf, keys[i]);
        
    }

    for(int i = word_size-1; i >= 0; --i){
        if(bf_probe(bf, words[i])){
            printf("%15s in Filter\n", words[i]);
        } else {
            printf("%15s NOT in Filter\n", words[i]);
        }
    }

    return;
}

void test_ll(void){

    HatterSpeak *hat1 = hatter_create("old1", "hatter1");
    HatterSpeak *hat2 = hatter_create("old2", "hatter2");
    HatterSpeak *hat3 = hatter_create("old3", "hatter3");
    HatterSpeak *hat4 = hatter_create("old4", "hatter4");
    HatterSpeak *hat5 = hatter_create("old5", "hatter5");

    ListNode *head = ll_node_create(hat1);
    ll_insert(&head, hat2);
    ll_insert(&head, hat3);
    ll_insert(&head, hat4);
    ll_insert(&head, hat5);

    print_ll(head);
    printf("Length: %d\n", ll_length(head));

    ll_delete(head);

    return;
}

void print_ll(ListNode *head){

    if(!head){
        printf("LL is EMPTY\n");
        return;
    }

    while(head->next){
        printf("%s -- ", head->gs->oldspeak);
        head = head->next;
    }
    printf("%s\n", head->gs->oldspeak);
    return;
}

void test_hash(){
    HashTable *ht = ht_create(50);

    HatterSpeak *hat1 = hatter_create("old1", "hatter1");
    HatterSpeak *hat2 = hatter_create("old2", "hatter2");
    HatterSpeak *hat3 = hatter_create("old3", "hatter3");
    HatterSpeak *hat4 = hatter_create("old4", "hatter4");
    HatterSpeak *hat5 = hatter_create("old5", "hatter5");
    HatterSpeak *hat6 = hatter_create("old6", "hatter6");
    HatterSpeak *hat7 = hatter_create("old7", "hatter7");
    HatterSpeak *hat8 = hatter_create("old8", "hatter8");
    HatterSpeak *hat9 = hatter_create("old9", "hatter9");
    HatterSpeak *hat10 = hatter_create("old10", "hatter10");

    printf("\n\n\n");

    ht_insert(ht, hat1);
    ht_insert(ht, hat2);
    ht_insert(ht, hat3);
    ht_insert(ht, hat4);
    ht_insert(ht, hat5);
    ht_insert(ht, hat6);
    ht_insert(ht, hat7);
    ht_insert(ht, hat8);
    ht_insert(ht, hat9);
    ht_insert(ht, hat10);

    /*
    ListNode *lookup = ht_lookup(ht, "hatter7");
    if(lookup != NULL){
        printf("Key old7 is matched with node->oldspeak %s\n", lookup->gs->oldspeak);
    } else {
        printf("Node does not exist\n");
    }
    */

    printf("HT COUNT: %d\n", ht_count(ht));
    

    print_hash(ht);
    ht_delete(ht);
    return;
}

void print_hash(HashTable *ht){
    for(uint32_t i = 0; i < ht_get_len(ht); i++){
        //printf("Made it here");
        if(ht->heads[i] != NULL){
            printf("%d: ", i);
            print_ll(ht->heads[i]);
        }
    }
    return;
}

