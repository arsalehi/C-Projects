#include "trie.h"
#include <inttypes.h>

#define NIL (void *)0

TrieNode *trie_node_create(uint16_t code){
    TrieNode *t = (TrieNode *)malloc(sizeof(TrieNode));

    if(!t){
        return (TrieNode *)NIL;
    }
    
    t->code = code;

    for (int i = 0; i < 256; i++){
        t->children[i] = NULL;
    }
    
    return t;
}



void trie_node_delete(TrieNode *n){
    if(!n){
    	return;
    }

    free(n);
}

TrieNode *trie_create(void){
    TrieNode *t = trie_node_create(EMPTY_CODE);
    return t;
}


void trie_reset(TrieNode *root){
    if(!root){
        return;
    }
    
    for(int i = 0; i < 256; i++){
        if(root->children[i] != NULL){
            // Recursive call -> deletes child and all children
            trie_delete(root->children[i]);
            root->children[i] = NULL;
        }
    }
    return;
}

void trie_delete(TrieNode *n){
    if(!n){
        return;
    }

    for(int i = 0; i < 256; i++){
        if(n->children[i] != NULL){
            trie_delete(n->children[i]);
            n->children[i] = NULL;
        }
    }
    trie_node_delete(n);
    return;
}

TrieNode *trie_step(TrieNode *n, uint8_t sym){
    return n->children[sym];
}

void tn_print(TrieNode *n){
    if(!n){
        return;
    }

    for(int i = 0; i < 256; i++){
        if(n->children[i] != NULL){
            printf("%c--", i);
        }
    }
    printf("\n");
}
