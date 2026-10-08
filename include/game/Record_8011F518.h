#ifndef GAME_RECORD_8011F518_H
#define GAME_RECORD_8011F518_H

/* Record whose address fn_8011F518 returns. Only the accessed fields are
   declared; the size is not established. */
struct Record_8011F518 {
    char mUnknown0[4];
    unsigned char mUnknown4;
    char mUnknown5[3];
    float mUnknown8;
    int mUnknown12;
};

extern "C" Record_8011F518 *fn_8011F518(void);

#endif
