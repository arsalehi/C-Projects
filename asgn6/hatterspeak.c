#include "bf.h"
#include "bv.h"
#include "ll.h"
#include "hash.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#define OPTIONS "sh:f:mb"
#define REGEX "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]+('|-)*)*"

bool move_to_front;
extern int seeks;
extern int traverses;

// Converts a word to lowercase 
//
void lower(char str[]);


int main(int argc, char **argv){
    
    int op = 0; 

    int bf_size = 1048576;
    int hash_size = 10000;
    bool m = false;
    bool b = false;
    bool show_stats = false;

    while ((op = getopt(argc, argv, OPTIONS)) != -1) {
        switch(op){
            case 's':
                show_stats = true;
                break;
            case 'h':
                hash_size = atoi(optarg);
                break;
            case 'f':
                bf_size = atoi(optarg);
                break;
            case 'm':
                move_to_front = true;
                m = true;
                break;
            case 'b':
                move_to_front = false;
                b = true;
                break;
            default:
                printf("Please re-run and enter a valid argument\n");
                return 0;
        }
    }

    if (m && b){
        printf("Invalid combination of arguments. \nRe-run with m or b only");
        return 0;
    }

    //Put more if statements later

//***************************************************************

    HashTable *ht =  ht_create(hash_size);
    BloomFilter *bf = bf_create(bf_size);
    BloomFilter *vals = bf_create(bf_size);

    FILE *old_speak = fopen("oldspeak.txt", "r");
    if(!old_speak){
        printf("Error with .txt file\n");
        return 0;
    }

    //Process oldspeak.txt words and allocate to ht and bf
    char os_buffer[0xFF];
    while(fscanf(old_speak, "%s\n", os_buffer) != EOF){
        lower(os_buffer);
        bf_insert(bf, os_buffer);
        HatterSpeak *os = hatter_create(os_buffer, NULL);
        ht_insert(ht, os);
    }
    fclose(old_speak);

    FILE *hatter_speak = fopen("hatterspeak.txt", "r");
    if(!hatter_speak){
        printf("Error with .txt file\n");
        return 0;
    }

    char hs_old[0xFF];
    char hs_hat[0xFF];
    while(fscanf(hatter_speak, "%s %s\n", hs_old, hs_hat) != EOF){
        lower(hs_old);
        lower(hs_hat);
        HatterSpeak *hs = hatter_create(hs_old, hs_hat);
        bf_insert(bf, hs_old);
        bf_insert(vals, hs_hat);
        ht_insert(ht, hs);
    }
    fclose(hatter_speak);

//***************************************
    regex_t regex;
    if(regcomp(&regex, REGEX, REG_EXTENDED) != 0){
        printf("Regex not compiling\n");
        return 0;
    }

    char *word;

    HatterSpeak *hat_f = hatter_create("~", "~");
    HatterSpeak *hat_t = hatter_create("~", "~");

    ListNode *forbidden = ll_node_create(hat_f);
    bool contains_forbidden = false;
    ListNode *translatable = ll_node_create(hat_t);
    bool contains_translatable = false;

    ListNode *head_f = forbidden;
    ListNode *head_t = translatable;

    while((word = next_word(stdin, &regex))){

        if(bf_probe(bf, word)){
            ListNode *node = ht_lookup(ht, word);

            if(node){
                if(!node){
                    printf("Not in hashtable\n");
                    continue;
                }
                if(node->gs->hatterspeak){
                    //printf("HAS HATTERSPEAK %s\n", node->gs->hatterspeak);
                    HatterSpeak *hatspeak = hatter_create(word, node->gs->hatterspeak);
                    ll_insert(&head_t, hatspeak);
                    contains_translatable = true;
                } else {

                    if(bf_probe(vals, word)){
                        printf("%s should not be a dungeon word\n", word);
                        continue;
                    }

                    //printf("NO HATTERSPEAK %s\n", node->gs->oldspeak);
                    HatterSpeak *hatspeak = hatter_create(word, NULL);
                    ll_insert(&head_f, hatspeak);
                    contains_forbidden = true;
                }
            }
        }
    }

//*************************************************************

    if(show_stats){
        printf("Seeks: %d\n", get_seeks());
        double temp_seeks = get_seeks();
        double avg_seek = traverses/ temp_seeks;
        printf("Average seek Length: %f\n", avg_seek);
        double sum_ll = 0;
        for(uint32_t i = 0; i < ht->length; i++){
            if(ht->heads[i]){
                int len = ll_length(ht->heads[i]);
                sum_ll += len;
            }
        }
        double avg_length = (sum_ll / (ht->length));
        printf("Average Linked List Length: %lf\n", avg_length);
        double num_heads = 0;
        for(uint32_t i = 0; i < ht->length; i++){
            if(ht->heads[i] != NULL){
                num_heads++;
            }
        }
        double hash_load = num_heads/ht->length;
        printf("Hash table load: %f%%\n", hash_load * 100);
        double bloom_load = 0;
        for(uint32_t i = 0; i < bf->filter->length; i++){
            if(bv_get_bit(bf->filter, i)){
                bloom_load++;
            }
        }
        printf("Bloom filter load: %f%%\n", (bloom_load/bf->filter->length) * 100);
        return 0;
    }

    if(contains_forbidden && contains_translatable){
        printf("\nDear Comrade,\n\n");
        printf("You have chosen to use words that the queen has decreed oldspeak.\n");
        printf("Due to your infraction you will be sent to the dungeon where you will\n");
        printf("\tbe taught hatterspeak\n\n");

        printf("Your errors:\n\n");
        ListNode *temp_f = head_f;
        while(temp_f){
            if(strcmp(temp_f->gs->oldspeak, "~") == 0){
                temp_f = temp_f->next;
                continue;
            }
            printf("%s\n", temp_f->gs->oldspeak);
            temp_f = temp_f->next;
        }

        printf("\nAppropriate hatterspeak translations.\n\n");
        ListNode *temp_t = head_t;
        while(temp_t){
            if(strcmp(temp_t->gs->oldspeak, "~") == 0){
                temp_t = temp_t->next;
                continue;
            }
            printf("%s -> %s\n", temp_t->gs->oldspeak, temp_t->gs->hatterspeak);
            temp_t = temp_t->next;
        }

    } else if (contains_translatable) {

        printf("Dear Wonderlander,\n\n");
        printf("The decree for hatterspeak finds your message lacking. Some of the\n");
        printf("\twords that you have used are not hatterspeak.\n");
        printf("The list shows how to turn the oldspeak words into hatterspeak\n\n");

        printf("Appropriate hatterspeak translations.\n\n");
        //ll_print(head_t);
        ListNode *temp_t = head_t;
        while(temp_t){
            if(strcmp(temp_t->gs->oldspeak, "~") == 0){
                temp_t = temp_t->next;
                continue;
            }
            printf("%s -> %s\n", temp_t->gs->oldspeak, temp_t->gs->hatterspeak);
            temp_t = temp_t->next;
        }
    } else if (contains_forbidden){

        printf("Dear Wonderlander,\n\n");
        printf("You have chosen to use words that the queen has decreed oldspeak.\n");
        printf("Due to your infraction you will be sent to the dungeon where you will\n");
        printf("\tbe taught hatterspeak.\n\n");

        printf("Your errors:\n\n");
        ListNode *temp_f = head_f;
        while(temp_f){
            if(strcmp(temp_f->gs->oldspeak, "~") == 0){
                temp_f = temp_f->next;
                continue;
            }
            printf("%s\n", temp_f->gs->oldspeak);
            temp_f = temp_f->next;
        }
    } else {
        printf("All words are safe\n");
    }

    printf("\n\nNo seg faults in Print sequence\n");

    //ht_print(ht);
    //printf("Current head of head_t: %s\n", head_t->gs->oldspeak);
    ll_delete(head_f);
    ll_delete(head_t);

    printf("No seg faults deleting linked lists\n");

    clear_words();
    regfree(&regex);
    bf_delete(bf);
    bf_delete(vals);
    ht_delete(ht);

    printf("No seg faults deleting rest of contents\n");
    
    return 0;
}

void lower(char str[]){
    for(int i =0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
    return;
}

