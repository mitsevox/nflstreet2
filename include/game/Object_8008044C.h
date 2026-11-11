#ifndef GAME_OBJECT_8008044C_H
#define GAME_OBJECT_8008044C_H

extern "C" {
int fn_801FA228(int handle, int a, int b, void *pRecord);
}

struct Object_8008044C {
    Object_8008044C() : mUnknown0(0), mUnknown4(0), mUnknown8(-1), mUnknown12(-1), mUnknown16(-1) {}
    ~Object_8008044C() {}
    int Read(void *pRecord) { return fn_801FA228(mUnknown0, 0, 0, pRecord); }

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    char mUnknown20[24];
};

/* Optional second argument of fn_8008044C and fn_8008040C: four words, read
   only when the pointer is non-null. */
struct Desc_8008044C {
    Desc_8008044C() : mUnknown0(0), mUnknown4(0), mUnknown8(0), mUnknown12(0) {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
};

/* Row filled by fn_800817CC: bytes +0x00 to +0x0D and the 14 words at +0x10.
   PlayerLook_t (include/game/PlayerLookRecord.h) holds one at +0x20. */
struct Info_80307908 {
    unsigned char mUnknown00;
    unsigned char mUnknown01;
    unsigned char mUnknown02;
    unsigned char mUnknown03;
    unsigned char mUnknown04;
    unsigned char mUnknown05;
    char mUnknown06[2];
    unsigned char mUnknown08;
    unsigned char mUnknown09;
    unsigned char mUnknown0A;
    unsigned char mUnknown0B;
    unsigned char mUnknown0C;
    unsigned char mUnknown0D;
    char mUnknown0E[2];
    unsigned int mValues[14];
};

extern "C" {
void fn_8008040C(Object_8008044C *pObject, Desc_8008044C *pDesc);
void fn_8008044C(Object_8008044C *pObject, Desc_8008044C *pDesc, int tag);
void fn_8008056C(Object_8008044C *pObject);
int PlayerDbGetTeamId(Object_8008044C *pObject);
int PlayerDbSeekId(Object_8008044C *pObject, int a, int *pResult);
void PlayerDbGetLastName(Object_8008044C *pObject, char *pBuffer, int size);
int PlayerDbGetNameKey(Object_8008044C *pObject, char *pBuffer, int size);
int PlayerDbGetPybt(Object_8008044C *pObject);
int PlayerDbGetHeight(Object_8008044C *pObject);
int PlayerDbGetPbpo(Object_8008044C *pObject);
void PlayerGetGearRatings(Object_8008044C *pObject, int *pValues);
void fn_800817CC(Object_8008044C *pObject, Info_80307908 *pInfo);
void fn_80081F50(Object_8008044C *pObject, unsigned char side, int a);
}

#endif
