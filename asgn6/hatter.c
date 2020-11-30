#include "hatter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

HatterSpeak *hatter_create(char *oldspeak, char *hatter){

    HatterSpeak *hs = (HatterSpeak *)malloc(sizeof(HatterSpeak));
    if(!hs){
        return (HatterSpeak *)NIL;
    }

    hs->oldspeak = (char *)malloc((strlen(oldspeak)+1) * sizeof(char));
    if(!hs->oldspeak){
        free(hs);
        return (HatterSpeak *)NIL;
    }

    if(hatter == NULL){
        hs->hatterspeak = NULL;
        strcpy(hs->oldspeak, oldspeak);
        return hs;
    } else {
        hs->hatterspeak = (char *)malloc((strlen(hatter)+1) * sizeof(char)); 
        if(!hs->hatterspeak){ 
            free(hs->oldspeak);
            free(hs);
            return (HatterSpeak *)NIL;
    }
    
    strcpy(hs->oldspeak, oldspeak);
    strcpy(hs->hatterspeak, hatter);
    //printf("oldspeak: %s, hs->oldspeak: %s\n", oldspeak, hs->oldspeak);
    //printf("hatter: %s, hs->hatterspeak: %s\n", hatter, hs->hatterspeak);
    return hs;
    }
}

void hatter_delete(HatterSpeak *gs){
    if(gs->hatterspeak){
        free(gs->hatterspeak);
    }
    free(gs->oldspeak);
    free(gs);
}
