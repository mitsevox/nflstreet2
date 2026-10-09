#ifndef GAME_CU_80163674_H
#define GAME_CU_80163674_H

#include "game/Object_80039F5C.h"

struct Desc_80163788 {
    short mUnknown00;
    short mUnknown02;
    Vector_80039F5C mUnknown04;
    Vector_80039F5C mUnknown10;
    Vector_80039F5C mUnknown1C;
    Vector_80039F5C mUnknown28;
};

struct State_80163AD8 {
    unsigned char mUnknown00[88];
    void *mpUnknown58;
};

struct Object_80163788 {
    unsigned char mUnknown00[4];
    float mUnknown04;
    float mUnknown08;
    float mUnknown0C;
    unsigned char mUnknown10[4];
    int mUnknown14;
    unsigned char mUnknown18[48];
    State_80163AD8 mUnknown48;
    unsigned char mUnknownA4[244];
    unsigned int mUnknown198;
    Vector_80039F5C mUnknown19C;
    int mUnknown1A8;
    int mUnknown1AC;
    int mUnknown1B0;
    Vector_80039F5C mUnknown1B4;
    Vector_80039F5C mUnknown1C0;
    short mUnknown1CC;
    short mUnknown1CE;
    float mUnknown1D0;
    unsigned char mUnknown1D4;
    unsigned char mUnknown1D5[3];
    short mUnknown1D8;
    short mUnknown1DA;
    short mUnknown1DC;
    unsigned short mUnknown1DE;
    unsigned char mUnknown1E0[4];
    int mUnknown1E4;
};

extern "C" {
void fn_80163674(Object_80163788 *pObject, Desc_80163788 *pDesc);
void fn_80163788(Object_80163788 *pObject, Desc_80163788 *pDesc);
void fn_801638F0(Object_80163788 *pObject);
int fn_80163954(Object_80163788 *pObject, int value);
void fn_80163AD8(Object_80163788 *pObject, void *pData, int index, int component);
void fn_80163B44(Object_80163788 *pObject, void *pData);
int fn_80163BCC(Object_80163788 *pObject);
int fn_80163C30(void *pHandle, int count);
void fn_80163CD0(void);
void fn_80163D08(Object_80163788 *pObject, int value);
void fn_80163D64(Object_80163788 *pObject, unsigned char value);
}

#endif
