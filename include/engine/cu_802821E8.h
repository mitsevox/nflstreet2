#ifndef ENGINE_CU_802821E8_H
#define ENGINE_CU_802821E8_H

typedef struct Struct_803ED474
{
    unsigned char *mUnknown00;
    int mUnknown04;
    int mUnknown08;
    char mUnknown0C[12];
    unsigned char mUnknown18;
} Struct_803ED474;

typedef struct Code_802C2860
{
    unsigned short mUnknown00;
    short mUnknown02;
} Code_802C2860;

typedef struct Leaf_802C2860
{
    short mUnknown00;
    unsigned char mUnknown02;
} Leaf_802C2860;

typedef struct Desc_802C2860
{
    Code_802C2860 *mpCodes;
    Leaf_802C2860 *mpLeaves;
    short mCount;
} Desc_802C2860;

#endif
