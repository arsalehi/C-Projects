#ifndef __HATTER_H__
#define __HATTER_H__
#endif

#ifndef NIL
#define NIL (void *)0
#endif

typedef struct HatterSpeak {
  char *oldspeak;
  char *hatterspeak;
} HatterSpeak;

//
// Creates the HatterSpeak struct
//
// oldspeak: word in oldsepak
// hatterspeak: translation from oldspeak to hatterspeak
//
HatterSpeak *hatter_create(char *oldspeak, char *hatterspeak);

//
// Destructor for HatterSpeak object
// May not be directly used
//
void hatter_delete(HatterSpeak *gs);
