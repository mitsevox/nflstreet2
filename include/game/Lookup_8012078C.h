#ifndef GAME_LOOKUP_8012078C_H
#define GAME_LOOKUP_8012078C_H

/* Eight-byte entry of the third array: a distance and the player index it
   belongs to (fn_8011FBE0). */
struct Entry_8011FBE0 {
    float mUnknown0;
    unsigned char mUnknown4;
};

/* 24-byte state allocated through fn_80238174 under the id 'purs'
   (fn_8012055C) and returned by fn_8012078C. Its four arrays each hold
   mUnknown16 elements. */
struct Lookup_8012078C {
    unsigned char *mpUnknown0;
    unsigned char *mpUnknown4;
    Entry_8011FBE0 *mpUnknown8;
    int *mpUnknown12;
    short mUnknown16;
    unsigned char mUnknown18;
    unsigned char mUnknown19;
    unsigned char mUnknown20;
    char mUnknown21[3];
};

extern "C" Lookup_8012078C *fn_8012078C(void);

#endif
