#include "bv.h"
#include "sieve.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#define OPTIONS "spn:"

//Used for testing and debugging BitVector implemenation and results
void print_bv(BitVector *v);

//Produces prime results, printing all prime numbers and classifying special primes
void primes(BitVector *v);

//Produces palindrome results, printing palindromes of a given base
void palindromes(BitVector *v);

//Used to calculate number in desired base
char* base_change(uint32_t num, uint32_t base);

//Supplementary for base change and palindrome checking
void string_reverse(char *string);

//Returns true if string is a palindrome
bool is_palindrome(char *string);


int main(int argc, char **argv){
    int num_bits = 100;
    int opt = 0;
    bool want_specials = false;
    bool want_palindromes = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 's':
            want_specials = true;
            break;
        case 'p':
            want_palindromes = true;
            break;
        case 'n':
            num_bits = atoi(optarg);
            break;
        }
    }

    //Ensures valud BitVector creation
    if(num_bits < 2){
        printf("For desired output run again with a value > 1\n");
        return 0;
    } 

    BitVector *b = bv_create(num_bits);
    sieve(b);

    if(want_specials){
        primes(b);
    }
    if(want_palindromes){
        if(want_specials){
            printf("\n");
        }
        palindromes(b);
    }

    //Freeing BitVector
    bv_delete(b);

    return 0;
}


void primes(BitVector *v){

    //Used to calculate each fibonacci value
    uint32_t fib = 2;
    uint32_t fib1 = 1;
    uint32_t fib2 = 1;

    //Used to calculate each lucas value
    uint32_t lucas = 3;
    uint32_t lucas1 = 1; 
    uint32_t lucas2 = 2; 

    //Used to calculate each mersenne value
    uint32_t mers = 3;
    uint32_t n = 3;

    //Loop through entire bitvector and check for all forms of primes
    for(uint32_t i = 2; i <= bv_get_len(v); ++i){
        if(bv_get_bit(v, i)){
            printf("%d: prime", i);
        }
        if(mers == i){
            if(bv_get_bit(v, i)){
                printf(", mersenne"); 
            }
            mers = (1 << n) -1;
            ++n;
        }
        //Used so Lucas numbers begin as 3 and with the two prevous numbers as 2 and 1
        if(i == 2){
            printf(", lucas");
        }
        if(lucas == i){
            if(bv_get_bit(v, i)){
                printf(", lucas");
            }
            lucas2 = lucas1;
            lucas1 = lucas;
            lucas = lucas1 + lucas2;
        }
        if(fib == i){
            if(bv_get_bit(v, i)){
                printf(", fibonacci");
            }
            fib2 = fib1;
            fib1 = fib;
            fib = fib1 + fib2;
        }
        if(bv_get_bit(v,i)){
            printf("\n");
        }
    }
    return;
}

char* base_change(uint32_t num, uint32_t base){
    uint32_t rem = 0;
    char rem_char;
    int max_num = 0;
    int temp = num;
    int index = 0;

    //Allocate space for base change result (Max number of digits is log2(N))
    while(temp >>= 1){
        ++max_num;
    }
    char *changed = (char *)malloc((max_num + 1) * sizeof(char));
    //Ensure that malloc works
    if(!changed){
        return 0;
    }

    while(num > 0){
        rem = num % base;
        if(rem < 10){
            rem_char = rem + '0';
        } else {
            //Capital W is 10 positions behind lowercase a, so this accounts for rollover
            rem_char = rem + 'W';
        }
        changed[index++] = rem_char;
        num /= base;
    }
    //Terminates string
    changed[index] = '\0';

    //Orinal result is backwards, need to reverse for correct order
    string_reverse(changed);

    return changed;
}

//Supplementary function
void string_reverse(char* string){
    int length = strlen(string);
    for(int i = 0; i < length/2; i++){
        char temp = string[i];
        string[i] = string[length-i-1];
        string[length-i-1] = temp;
    }
}

//Returns true if palindrome, else false
bool is_palindrome(char *string){
    bool result = true;
    char reverse[strlen(string)];
    strcpy(reverse, string);
    string_reverse(reverse);
    for(unsigned long i = 0; i < strlen(string)/2; i++){
        if(string[i] != reverse[i]){
            result = false;
        }
    }
    return result;
}

//Produces desired output for "-p" argument
void palindromes(BitVector *v){
    uint32_t base = 2;
    printf("Base %d\n", base);
    printf("---- --\n");
    for(uint32_t i = 2; i <= bv_get_len(v); ++i){
        char *changed = base_change(i, base);
        if(bv_get_bit(v, i) && is_palindrome(changed)){
            printf("%d = %s\n",i, changed);
        }
        free(changed);
    }
    printf("\n");
    base = 9;
    printf("Base %d\n", base);
    printf("---- --\n");
    for(uint32_t i = 2; i <= bv_get_len(v); ++i){
        char *changed = base_change(i, base);
        if(bv_get_bit(v, i) && is_palindrome(changed)){
            printf("%d = %s\n",i, changed);
        }
        free(changed);
    }
    printf("\n");
    base = 10;
    printf("Base %d\n", base);
    printf("---- --\n");
    for(uint32_t i = 2; i <= bv_get_len(v); ++i){
        char *changed = base_change(i, base);
        if(bv_get_bit(v, i) && is_palindrome(changed)){
            printf("%d = %s\n",i, changed);
        }
        free(changed);
    }
    printf("\n");
    //10 + 'S' = 10 + 19 = 29
    base = 29;
    printf("Base %d\n", base);
    printf("---- --\n");
    for(uint32_t i = 2; i <= bv_get_len(v); ++i){
        char *changed = base_change(i, base);
        if(bv_get_bit(v, i) && is_palindrome(changed)){
            printf("%d = %s\n",i, changed);
        }
        free(changed);
    }
}
