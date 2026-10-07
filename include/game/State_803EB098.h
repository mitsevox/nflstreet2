#ifndef GAME_STATE_803EB098_H
#define GAME_STATE_803EB098_H

/* Record at State_803EB098 +512; its extent past +4 is not established and
   is declared up to the next separately accessed offset. */
struct Record_8011F518 {
    char mUnknown0[4];
    unsigned char mUnknown4;
    char mUnknown5[11];
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
    char mUnknown8[48];
    char mUnknown56[456];
    Record_8011F518 mUnknown512;
    char mUnknown528[44];
    unsigned char mUnknown572;
    char mUnknown573[3];
    Record_8011F4F8 mUnknown576[1];
};

#endif
