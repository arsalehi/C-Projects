#include "bf.h"
#include "speck.h"
#include <stdlib.h>
#include <stdio.h>

BloomFilter *bf_create(uint32_t size){
    BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
    if(bf){
        bf->primary[0] = 0xfc28ca6885711cf7;
        bf->primary[1] = 0x2841af568222f773;
        bf->secondary[0] = 0x85ae998311115ae3;
        bf->secondary[1] = 0xb6fac2ae33a40089;
        bf->tertiary [0] = 0xd37b01df0ae8f8d0;
        bf->tertiary [1] = 0x911d454886ca7cf7;
        bf->filter = bv_create(size);
        return bf;
    }
    return (BloomFilter *)NIL;
}

void bf_delete(BloomFilter *bf){
    bv_delete(bf->filter);
    free(bf);
}

void bf_insert(BloomFilter *bf, char *key){
    uint32_t index1 = hash(bf->primary, key) % bv_get_len(bf->filter);
    uint32_t index2 = hash(bf->secondary, key) % bv_get_len(bf->filter);
    uint32_t index3 = hash(bf->tertiary, key) % bv_get_len(bf->filter);

    bv_set_bit(bf->filter, index1);
    bv_set_bit(bf->filter, index2);
    bv_set_bit(bf->filter, index3);

    //printf("Indices inserted into: %d, %d, %d\n", index1, index2, index3);

    return;
}

bool bf_probe(BloomFilter *bf, char *key){
    uint8_t bit1 = bv_get_bit(bf->filter, hash(bf->primary, key) % bv_get_len(bf->filter));
    uint8_t bit2 = bv_get_bit(bf->filter, hash(bf->secondary, key) % bv_get_len(bf->filter));
    uint8_t bit3 = bv_get_bit(bf->filter, hash(bf->tertiary, key) % bv_get_len(bf->filter));

    if(bit1 && bit2 && bit3){
        return true;
    }
    return false;
}
