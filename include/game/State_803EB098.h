#ifndef GAME_STATE_803EB098_H
#define GAME_STATE_803EB098_H

#include "game/Record_8011F518.h"

/* Record at State_803EB098 +8, whose address fn_8011F4E0 returns. The
   48-byte span is the one fn_8011EFD4 compares as a unit (li r5,48 at
   0x8011F008); inside it only the accessed fields are declared. */
struct Record_8011F4E0 {
    char mUnknown0[2];
    unsigned short mUnknown2;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    char mUnknown7[1];
    unsigned char mUnknown8[4];
    unsigned char mUnknown12[4];
    unsigned char mUnknown16[7];
    char mUnknown23[1];
    unsigned char mUnknown24[8];
    unsigned char mUnknown32[7];
    char mUnknown39[1];
    unsigned char mUnknown40[8];
};

/* 32-byte record of the trailing State_803EB098 array (fn_8011F4F8). */
struct Record_8011F4F8 {
    char mUnknown0[11];
    unsigned char mUnknownB;
    char mUnknownC[20];
};

/* State allocated through fn_80238174 under the id 'pinf' (fn_8011F0D8):
   576 bytes followed by mUnknown572 records of 32 bytes. */
struct State_803EB098 {
    float mUnknown0;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6[2];
    Record_8011F4E0 mUnknown8;
    char mUnknown56[456];
    Record_8011F518 mUnknown512;
    char mUnknown528[44];
    unsigned char mUnknown572;
    char mUnknown573[3];
    Record_8011F4F8 mUnknown576[1];
};

#endif
