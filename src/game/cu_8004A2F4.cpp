#include "game/Object_8008044C.h"
#include "game/fn_80233CBC.h"
#include "game/Desc_800408E4.h"
#include "game/Record_8031B6F8.h"
#include "game/cu_801A8620.h"
#include "game/Object_80235588.h"
#include "game/fn_801EBC18.h"
#include <math.h>
#include <string.h>

#include "game/Node_80041904.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_80040818.h"
#include "game/InGame.h"
#include "game/bitstream.h"
#include "game/cu_80041210.h"
#include "game/cu_80067C10.h"
#include "game/cu_8008E978.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_801BA2A8.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802372EC.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"

/* Record whose four key bytes at +4 fn_8004A6EC and fn_8004A7A8 score. */
struct Variant_8004A6EC {
    char mUnknown0[4];
    unsigned char mKey[4];
};

/* Entry of a variant table: the two halfwords handed to fn_801BA2A8 and the
   scored record. */
struct VariantEntry_8004A6EC {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Variant_8004A6EC *mpVariant;
};

struct VariantTable_8004A6EC {
    unsigned short mCount;
    char mUnknown2[2];
    VariantEntry_8004A6EC mEntries[1];
};

/* Name and id pair of the tables fn_8004B020 searches; an id of -1 ends
   the table. */
struct NameId_8004B020 {
    char mName[64];
    int mId;
};

/* 0x24-byte name table entry of fn_8004C368, fn_8004C3D4 and fn_8004C440. */
struct ShortNameId_8004C368 {
    char mName[32];
    int mId;
};

/* 0x44-byte sound name table entry of fn_8004C4AC. */
struct SoundNameId_8004C4AC {
    char mName[64];
    unsigned short mId;
    char mUnknown66[2];
};

/* 0x84-byte name/state table entry of fn_8004C270. */
struct StateNameId_8004C270 {
    char mName[64];
    char mState[64];
    int mId;
};

/* Record of fn_801C02CC; its halfwords +42 and +14 are passed to fn_801BBE5C. */
struct Frame_801C02CC {
    char mUnknown0[14];
    unsigned short mUnknown14;
    char mUnknown16[26];
    unsigned short mUnknown42;
};

typedef int (*Handler_803084C4)(VariantTable_8004A6EC *pTable, unsigned short c, void *a, void *b,
                                Object_80041904 *pObject, int skip);

/* Handler set registered with fn_801BE030: a count and the handler array. */
struct Table_803EA4D0 {
    unsigned short mCount;
    Handler_803084C4 *mpHandlers;
};

extern "C" {
extern float lbl_803EA2C4;
extern Table_803EA4D0 lbl_803EA4D0;
extern unsigned char lbl_803EA4DC[8];
extern Object_80041904 *lbl_803EA4E4;
extern NameId_8004B020 lbl_802D47DC[];
extern NameId_8004B020 lbl_802D48A8[];
extern NameId_8004B020 lbl_802CFE34[85];
extern ShortNameId_8004C368 lbl_802CFBCC[8];
extern ShortNameId_8004C368 lbl_802CFD2C[3];
extern ShortNameId_8004C368 lbl_802CFDA4[4];
extern NameId_8004B020 lbl_802D14C8[32];
extern StateNameId_8004C270 lbl_802D1D48[63];
extern SoundNameId_8004C4AC lbl_802D3DC4[38];
/* Hitter passed to fn_8004C844: an id word, a sound channel byte (0xFF for
   none) and the two floats whose product is the hit strength. */
struct Hitter_8004C844 {
    int mId;
    char mUnknown4[4];
    unsigned char mChannel;
    char mUnknown9[443];
    float mUnknown452;
    char mUnknown456[52];
    float mUnknown508;
};

typedef void (*Loader_8004C684)(int handle, Object_80041904 *pObject);

extern Callback_80041904 lbl_802CFCEC[8];
extern Loader_8004C684 lbl_802CFD0C[8];
extern void (*lbl_802CFD98[3])(Object_80040818 *pOwner);
extern int lbl_8030865C[8];
extern unsigned char lbl_803EA4D8;
extern unsigned char lbl_803EA4D9;
extern unsigned short lbl_803EA4DA;
extern int lbl_8030867C[8];
extern float lbl_803EA4E8;
extern float lbl_803EA4EC;
extern float lbl_803EA4F0;

void fn_800301C4(void *pStream, float *pValues, int bits, float scale);
void fn_80030554(void *pStream, float *pValues, int bits, float scale);
void fn_800411C8(Object_80040818 *pObject);
void fn_800411EC(Object_80040818 *pObject);
int fn_8004C204(const char *pName);
int fn_8004C270(const char *pName, const char *pState);
int fn_8004C2FC(const char *pName);
unsigned short fn_8004C4AC(const char *pName);
int fn_8004C5E0(int index);
void fn_8004D498(int handle);
int fn_8004D4B0(int handle, const char *pKey);
int fn_8004D508(int handle, const char *pKey);
unsigned char fn_8005164C(int type);
int fn_80051680(int type);
void fn_80194C5C(int a, int b, int c);
int fn_8004D560(int handle);
int fn_8004D5B8(int handle, const char *pKey, char *pText, int size);
int fn_8004D5F0(int handle, const char *pKey);
float fn_8004D624(int handle, const char *pKey);
unsigned char fn_8004D6F4(int handle, const char *pKey, float *pValues, int count);
int fn_8004D728(int handle, const char *pKey, float *pValues);
int fn_8004D84C(int handle);
void fn_8004D860(int handle, int position);
int fn_800C47C4(void);
void fn_80145100(int type, int index);
char *fn_801C2EB4(char *pDst, const char *pSrc);
int fn_801F0A8C(int set, const char *pName);
void fn_8004CBEC(void *pData, float t, Object_80041904 *pObject, Object_80040818 *pOwner);
int fn_801BE068(void *pA, void *pB, void *pC, unsigned short key, float value, void *p);
unsigned short fn_801BE648(void *p);
void fn_8004CE6C(Object_80040818 *pOwner);
void fn_8004E090(Object_80040818 *pOwner, int a, int b);
void fn_800516B4(int id, float *pA, float *pB);
void fn_800516E4(int id);
void fn_80051724(Object_80040818 *pOwner, float *p);
void fn_80051810(Object_80040818 *pOwner, float value);
void fn_80051880(Object_80040818 *pOwner, float value);
void fn_80051B3C(Object_80040818 *pOwner, float *pPos);
void fn_8005415C(int a, int b);
int fn_800A3444(void);
int fn_801784C4(void);
float fn_80178A08(void);
float fn_80178A44(void);
void fn_8019EC88(Pose_80041930 *pOut, Pose_80041930 *pA, Pose_80041930 *pB, Pose_80041930 *pC, float t,
                 unsigned char a);
void fn_801A9F98(Extra_8004149C *pExtra, Object_80040818 *pItem, int a, int b);
void fn_801AA124(Object_80040818 *pItem, void *a, int b, void *c);
short *fn_801AA220(int count);
void fn_801B9EDC(void *p, int a, int b, int c);
void fn_801B9FEC(void *p, void *q);
int fn_801BB638(int id, int a);
int fn_801BBE5C(int a, int b);
void fn_801BE030(int type, Table_803EA4D0 *pTable);
void fn_801BE040(void *p);
Frame_801C02CC *fn_801C02CC(Actor_801C009C *pActor, int index);
int fn_801C2FE4(const char *pA, const char *pB);
int fn_801CFE40(float y, float x);
void fn_80227248(void *pOut, void *p, float scale);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80237260(int stream);

Handler_803084C4 lbl_803084C4[102];

void fn_8004A2F4(Pose_80041930 *pPose, BitStream_t *pStream, unsigned int count)
{
    short *pValue = pPose->mUnknown48;
    unsigned int groups = count * 3 / 5;
    unsigned int rest = count * 3 % 5;
    unsigned int i;
    long long bits;

    for (i = 0; i < groups; i++) {
        bits = ReadBitStream(pStream, 60);
        pValue[0] = (bits << 4 >> 48) & ~15;
        pValue[1] = (bits << 16 >> 48) & ~15;
        pValue[2] = (bits << 28 >> 48) & ~15;
        pValue[3] = (bits << 40 >> 48) & ~15;
        pValue[4] = (bits << 52 >> 48) & ~15;
        pValue += 5;
    }
    bits = ReadBitStream(pStream, rest * 12);
    for (i = 0; i < rest; i++) {
        pValue[i] = (bits << (64 - (rest - i) * 12) >> 48) & ~15;
    }
    fn_800301C4(pStream, pPose->mUnknown8, 16, 512.0f);
    pPose->mUnknown32 = (int)ReadBitStream(pStream, 16) << 8;
}

int fn_8004A6EC(VariantTable_8004A6EC *pTable, unsigned char *pKey);
int fn_8004A7A8(VariantTable_8004A6EC *pTable, unsigned char *pKey);

int fn_8004A474(VariantTable_8004A6EC *pTable, void *a, void *b, Object_80041904 *pObject, unsigned short c)
{
    int index = fn_8004A6EC(pTable, &pObject->mUnknown428->mUnknown1704);

    if (index >= 0) {
        fn_801BA2A8(a, b, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, c, pObject, 1.0f);
    }
    return 0;
}

int fn_8004A4F0(VariantTable_8004A6EC *pTable, void *a, void *b, Object_80041904 *pObject, unsigned short c)
{
    int index = fn_8004A7A8(pTable, &pObject->mUnknown428->mUnknown1704);

    if (index >= 0) {
        fn_801BA2A8(a, b, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2, c, pObject, 1.0f);
    }
    return 0;
}

int fn_8004A56C(VariantTable_8004A6EC *pTable, unsigned short c, void *a, void *b, Object_80041904 *pObject, int skip)
{
    if (!skip) {
        fn_8004A474(pTable, a, b, pObject, c);
    }
    return 0;
}

int fn_8004A5AC(VariantTable_8004A6EC *pTable, unsigned short c, void *a, void *b, Object_80041904 *pObject, int skip)
{
    if (!skip) {
        fn_8004A4F0(pTable, a, b, pObject, c);
    }
    return 0;
}

int fn_8004A5EC(VariantTable_8004A6EC *pTable, unsigned short c, void *a, void *b, Object_80041904 *pObject, int skip)
{
    if (!skip) {
        Extra_8004149C *pExtra = pObject->mUnknown428;
        unsigned char b0 = pExtra->mUnknown1704;
        unsigned char b1 = pExtra->mUnknown1705;
        unsigned char b2 = pExtra->mUnknown1706;
        unsigned char b3 = pExtra->mUnknown1707;
        Frame_801C02CC *pFrame = fn_801C02CC(fn_80093BAC(b0, b1), b2);

        fn_801BA2A8(a, b, fn_801BBE5C(pFrame->mUnknown42 | 0x4000, pFrame->mUnknown14), b3, c, pObject, 1.0f);
    }
    return 0;
}

void fn_8004A680(Pose_80041930 *pPose, Skeleton_80041930 *pSkeleton)
{
    unsigned int i;

    for (i = 0; i < pSkeleton->mUnknown6; i++) {
        pPose->mUnknown48[i * 3 + 0] = pSkeleton->mUnknown1040[i][0] << 4;
        pPose->mUnknown48[i * 3 + 1] = pSkeleton->mUnknown1040[i][1] << 4;
        pPose->mUnknown48[i * 3 + 2] = pSkeleton->mUnknown1040[i][2] << 4;
    }
}

int fn_8004A6EC(VariantTable_8004A6EC *pTable, unsigned char *pKey)
{
    int best = -1;
    signed char bestIndex = -1;
    int i;

    for (i = 0; i < pTable->mCount; i++) {
        Variant_8004A6EC *pVariant = pTable->mEntries[i].mpVariant;
        int score = fn_802372EC(1, 10);
        int j;

        for (j = 0; j < 4; j++) {
            if (pKey[j] == pVariant->mKey[j]) {
                score += (10 - j) * 10;
            }
        }
        if (score > best) {
            best = score;
            bestIndex = i;
        }
    }
    return bestIndex;
}

int fn_8004A7A8(VariantTable_8004A6EC *pTable, unsigned char *pKey)
{
    int best = -1;
    signed char bestIndex = -1;
    int i;

    for (i = 0; i < pTable->mCount; i++) {
        Variant_8004A6EC *pVariant = pTable->mEntries[i].mpVariant;
        int score = fn_802372EC(0, 10);
        int j;

        for (j = 0; j < 4; j++) {
            if (pKey[j] == pVariant->mKey[j]) {
                score += (10 - j) * 10;
            } else if (j == 0) {
                score = 0;
                break;
            }
        }
        if (score > best) {
            best = score;
            bestIndex = i;
        }
    }
    return bestIndex;
}

void fn_8004A870(Handler_803084C4 *pHandlers, unsigned int count)
{
    unsigned int i;

    for (i = 0; i < count; i++) {
        pHandlers[i] = fn_8004A56C;
    }
    pHandlers[6] = fn_8004A5AC;
    pHandlers[23] = fn_8004A5AC;
    pHandlers[24] = fn_8004A5AC;
    pHandlers[7] = fn_8004A5AC;
    pHandlers[101] = fn_8004A5EC;
}

void fn_8004A8C4(Extra_8004149C *pExtra, Object_80040818 *pItem, int a) { fn_801A9F98(pExtra, pItem, a, 0); }

void fn_8004A8E8(Object_80040818 *pItem, void *a, int b, void *c) { fn_801AA124(pItem, a, b, c); }

void fn_8004A908(Object_80041904 *pObject, int index)
{
    Skeleton_80041930 *pSkeleton = fn_800410B8(index);

    if (pSkeleton) {
        Object_80040818 *pPlaced = fn_80040F18(index);
        unsigned short count = pSkeleton->mUnknown6;
        int size = count * 64;

        pPlaced->mUnknown228 = fn_801D2B7C(size, 0, 0);
        fn_801C1F94(pPlaced->mUnknown228, 0, size);
        if (pPlaced) {
            pPlaced->mUnknown172.mUnknown4 = count + 1;
            pPlaced->mUnknown172.mUnknown0 = 0x100;
            pPlaced->mUnknown172.mUnknown2 = 0x202;
            pPlaced->mUnknown172.mUnknown48 = fn_801AA220(count);
            pPlaced->mUnknown172.mUnknown52 = (float (*)[4][4])pPlaced->mUnknown228;
            fn_8004A680(&pPlaced->mUnknown172, pSkeleton);
        }
        fn_801B9EDC(pObject->mUnknown428->mUnknown48, 0, 10, 10);
        fn_801B9FEC(pObject->mUnknown428->mUnknown48, pObject->mUnknown428->mUnknown60);
        fn_801BE040(pObject->mUnknown428->mUnknown1300);
        pObject->mUnknown428->mUnknown1708 = 0;
    }
}

void fn_8004A9FC(void)
{
    fn_8004A870(lbl_803084C4, 102);
    fn_801BE030(10, &lbl_803EA4D0);
}

void fn_8004AA34(Pose_80041930 *pPose, BitStream_t *pStream, unsigned int count)
{
    unsigned short *pValue = (unsigned short *)pPose->mUnknown48;
    unsigned int groups = count * 3 / 5;
    unsigned int rest = count * 3 % 5;
    unsigned int i;
    unsigned long long bits;

    for (i = 0; i < groups; i++) {
        bits = (unsigned long long)(pValue[0] >> 4) << 48;
        bits |= (unsigned long long)(pValue[1] >> 4) << 36;
        bits |= (unsigned long long)(pValue[2] >> 4) << 24;
        bits |= (unsigned long long)(pValue[3] >> 4) << 12;
        bits |= (unsigned long long)(pValue[4] >> 4);
        fn_80191068(pStream, bits, 60);
        pValue += 5;
    }
    bits = 0;
    for (i = 0; i < rest; i++) {
        bits |= (unsigned long long)(pValue[i] >> 4) << (rest - (i + 1)) * 12;
    }
    fn_80191068(pStream, bits, rest * 12);
    fn_80030554(pStream, pPose->mUnknown8, 16, 512.0f);
    fn_80191068(pStream, pPose->mUnknown32 >> 8, 16);
}

void fn_8004ABF4(Object_80040818 *pObject, Object_80041904 *pLinked, BitStream_t *pStream0, BitStream_t *pStream1,
                 BitStream_t *pStream2, BitStream_t *pStream3, float t)
{
    short values1[192];
    short values2[192];
    short values3[192];
    Pose_80041930 pose1;
    Pose_80041930 pose3;
    Pose_80041930 pose2;
    unsigned int count = pObject->mUnknown172.mUnknown4 - 1;

    pose1.mUnknown48 = values1;
    pose3.mUnknown48 = values3;
    pose2.mUnknown48 = values2;
    fn_8004A2F4(&pose1, pStream1, count);
    fn_8004A2F4(&pObject->mUnknown172, pStream0, count);
    if (pStream2) {
        fn_8004A2F4(&pose2, pStream2, count);
    }
    if (pStream3) {
        fn_8004A2F4(&pose3, pStream3, count);
    }
    if (!pStream2) {
        if (!pStream3) {
            fn_8019EC88(&pObject->mUnknown172, &pose1, 0, 0, t, 0);
        } else {
            fn_8019EC88(&pObject->mUnknown172, &pose1, 0, &pose3, t, 0);
        }
    } else if (!pStream3) {
        fn_8019EC88(&pObject->mUnknown172, &pose1, &pose2, 0, t, 0);
    } else {
        fn_8019EC88(&pObject->mUnknown172, &pose1, &pose2, &pose3, t, 0);
    }
}

void fn_8004AD3C(int a)
{
    switch (fn_800A3444()) {
    case 4:
        fn_801BB638(0x66, a);
        fn_801BB638(0x67, a);
        fn_801BB638(0x68, a);
        break;
    case 0:
        fn_801BB638(0x69, a);
        fn_801BB638(0x6A, a);
        fn_801BB638(0x6B, a);
        break;
    case 3:
        fn_801BB638(0x6C, a);
        fn_801BB638(0x6D, a);
        fn_801BB638(0x6E, a);
        break;
    case 5:
        fn_801BB638(0x6F, a);
        fn_801BB638(0x70, a);
        fn_801BB638(0x71, a);
        break;
    case 7:
        fn_801BB638(0x72, a);
        fn_801BB638(0x73, a);
        break;
    case 10:
        fn_801BB638(0x74, a);
        fn_801BB638(0x75, a);
        fn_801BB638(0x76, a);
        break;
    case 6:
        fn_801BB638(0x7A, a);
        fn_801BB638(0x7B, a);
        fn_801BB638(0x7C, a);
        break;
    case 2:
        fn_801BB638(0x77, a);
        fn_801BB638(0x78, a);
        fn_801BB638(0x79, a);
        break;
    case 1:
        fn_801BB638(0x7D, a);
        fn_801BB638(0x7E, a);
        fn_801BB638(0x7F, a);
        break;
    case 8:
        fn_801BB638(0x80, a);
        fn_801BB638(0x81, a);
        fn_801BB638(0x82, a);
        break;
    case 11:
        fn_801BB638(0x74, a);
        fn_801BB638(0x75, a);
        fn_801BB638(0x76, a);
        break;
    }
}

void fn_8004AF84(Extra_8004149C *pExtra) { pExtra->mUnknown1708 &= ~0x78; }

/* Clears flag bits 0x78 of the Extra block and restarts its fn_801BE068 entry. */
static inline void Restart_801BE068(Object_80041904 *pObject, unsigned short key, float value)
{
    fn_8004AF84(pObject->mUnknown428);
    fn_801BE068(pObject->mUnknown428->mUnknown1300, pObject->mUnknown428->mUnknown48, pObject->mUnknown428->mUnknown60,
                key, value, pObject);
}

void fn_8004AF94(Object_80041904 *pObject, unsigned char b1, unsigned char b0, unsigned char b3,
                 unsigned char b2)
{
    pObject->mUnknown428->mUnknown50 = 10;
    pObject->mUnknown428->mUnknown1704 = b0;
    pObject->mUnknown428->mUnknown1705 = b1;
    pObject->mUnknown428->mUnknown1706 = b2;
    pObject->mUnknown428->mUnknown1707 = b3;
    Restart_801BE068(pObject, 0x65, 1.0f);
}

int fn_8004B020(const char *pName, NameId_8004B020 *pTable)
{
    int i;

    for (i = 0; pTable[i].mId != -1; i++) {
        if (fn_801C2FE4(pName, pTable[i].mName) == 0) {
            return pTable[i].mId;
        }
    }
    return -1;
}

void fn_8004B088(Object_80040818 *pObject)
{
    Flags_800411C8 *pFlags;
    Node_80041904 *pNode;

    pObject->mUnknown472->mUnknown8 = pObject->mUnknown472->mUnknown112;
    pObject->mUnknown472->mUnknown12 = pObject->mUnknown472->mUnknown116;
    pObject->mUnknown472->mUnknown16 = pObject->mUnknown472->mUnknown120;
    pObject->mUnknown472->mUnknown96 = pObject->mUnknown472->mUnknown124;
    pObject->mUnknown472->mUnknown100 = pObject->mUnknown472->mUnknown128;
    pObject->mUnknown472->mUnknown104 = pObject->mUnknown472->mUnknown132;
    pObject->mUnknown472->mUnknown108 = pObject->mUnknown472->mUnknown136;
    pObject->mUnknown472->mUnknown32 = pObject->mUnknown472->mUnknown140;
    if (pObject->mUnknown472->mUnknown428) {
        pObject->mUnknown472->mUnknown428->mUnknown56 = pObject->mUnknown472->mUnknown140;
    }
    fn_800411EC(pObject);
    pFlags = pObject->mUnknown476;
    if (pFlags && pFlags->mUnknown20 != -1) {
        fn_800516B4(pFlags->mUnknown20, &pObject->mUnknown472->mUnknown112, &pObject->mUnknown472->mUnknown124);
        fn_800516E4(pFlags->mUnknown20);
    }
    for (pNode = pObject->mUnknown472->mUnknown312; pNode; pNode = pNode->mpNext) {
        if (pNode->mUnknown104 != -1 && pNode->mUnknown108 != -1) {
            fn_8004E090(pObject, pNode->mUnknown104, 0);
        }
    }
}

void fn_8004B1A0(Object_80040818 *pObject)
{
    float y = fabsf(pObject->mUnknown472->mUnknown12);
    int outY = y > fn_80178A44() + lbl_803EA4E8;
    float x = fabsf(pObject->mUnknown472->mUnknown8);
    int outX = x > fn_80178A08() + lbl_803EA4E8;

    if (outX || outY) {
        Vector_80039F5C pos;

        pos.mX = pObject->mUnknown472->mUnknown8;
        pos.mY = pObject->mUnknown472->mUnknown12;
        pos.mZ = pObject->mUnknown472->mUnknown16;
        if (outX) {
            float margin = lbl_803EA4F0 * fn_80237260(0);

            pos.mX = pObject->mUnknown472->mUnknown8 < 0.0f ? lbl_803EA4EC - fn_80178A08() + margin
                                                                 : fn_80178A08() - (lbl_803EA4EC + margin);
        }
        if (outY) {
            float margin = lbl_803EA4F0 * fn_80237260(0);

            pos.mY = pObject->mUnknown472->mUnknown12 < 0.0f ? lbl_803EA4EC - fn_80178A44() + margin
                                                                 : fn_80178A44() - (lbl_803EA4EC + margin);
        }
        pObject->mUnknown472->mUnknown8 = pos.mX;
        pObject->mUnknown472->mUnknown12 = pos.mY;
        pObject->mUnknown472->mUnknown16 = pos.mZ;
        fn_800411EC(pObject);
        if (pObject->mUnknown476 && pObject->mUnknown476->mUnknown20 != -1) {
            fn_800516B4(pObject->mUnknown476->mUnknown20, &pos.mX, &pObject->mUnknown472->mUnknown96);
        }
    }
}

int fn_8004B354(Object_80041904 *pObject, Object_80040818 *pOwner, int mode)
{
    Extra_8004149C *pExtra = pObject->mUnknown428;

    if (mode == 0) {
        if (pObject->mUnknown196 != -1) {
            pExtra->mUnknown1704 = 1;
            Restart_801BE068(pObject, pObject->mUnknown196, 1.0f);
        }
        pObject->mUnknown200.mStep = 0;
        pObject->mUnknown200.mPhase = 0;
        pObject->mUnknown200.mTime = 0.0f;
        if (pOwner->mUnknown476 && pOwner->mUnknown476->mUnknown20 != -1) {
            fn_800516E4(pOwner->mUnknown476->mUnknown20);
        }
    } else if (mode == 2) {
        if (pObject->mUnknown192) {
            pObject->mUnknown192(pOwner);
        }
        if (pOwner->mUnknown476 && pOwner->mUnknown476->mUnknown20 != -1) {
            Vector_80039F5C from;
            Vector_80039F5C to;
            Point_8017886C center;
            Point_8017886C offset;

            from.mX = pObject->mUnknown8;
            from.mY = pObject->mUnknown12;
            from.mZ = pObject->mUnknown16;
            to.mX = pObject->mUnknown8;
            to.mY = pObject->mUnknown12;
            to.mZ = pObject->mUnknown16;
            if (fn_801784C4()) {
                from.mX = -from.mX;
                from.mY = -from.mY;
            }
            center = fn_80177FE0();
            fn_80227690(&offset, &from, &center);
            {
                float length = fn_802270A4(&offset);

                if (length < 6.0f) {
                    if (length <= 0.001f) {
                        offset.mY = 6.0f;
                        offset.mX = 0.0f;
                    } else {
                        fn_80227248(&offset, &offset, 6.0f / length);
                    }
                    fn_80227638(&to, &center, &offset);
                    if (fn_801784C4()) {
                        to.mX = -to.mX;
                        to.mY = -to.mY;
                    }
                    pObject->mUnknown8 = to.mX;
                    pObject->mUnknown12 = to.mY;
                    pObject->mUnknown16 = to.mZ;
                    fn_80051B3C(pOwner, &pObject->mUnknown8);
                }
            }
        }
    } else {
        fn_8004CE6C(pOwner);
        if (pObject->mUnknown408 != 0.0f) {
            fn_80051810(pOwner, pObject->mUnknown408);
        }
        if (pObject->mUnknown412 != 0.0f) {
            fn_80051880(pOwner, pObject->mUnknown412);
        }
        if (pExtra && (pExtra->mUnknown1708 & 1)) {
            if (pObject->mUnknown196 != -1) {
                pExtra->mUnknown1704 = pObject->mUnknown424;
                Restart_801BE068(pObject, pObject->mUnknown196, 1.0f);
            }
            pExtra->mUnknown1708 &= ~1;
        }
        if (pObject->mUnknown380) {
            Vector_80039F5C pos;
            float t;
            Node_80041904 *pNode;

            pObject->mUnknown380 = 0;
            pos.mX = pObject->mUnknown360.mX;
            pos.mY = pObject->mUnknown360.mY;
            pos.mZ = pObject->mUnknown360.mZ;
            t = pObject->mUnknown372;
            if (fn_801784C4()) {
                pos.mX = -pos.mX;
                pos.mY = -pos.mY;
            }
            if (pObject->mUnknown382) {
                fn_80051724(pOwner, &pObject->mUnknown348);
            }
            for (pNode = pObject->mUnknown312; pNode; pNode = pNode->mpNext) {
                unsigned int count;

                if (fn_801C2FE4(pNode->mName, pObject->mUnknown316) != 0) {
                    continue;
                }
                if (!pObject->mUnknown381) {
                    if (pNode->mId != -1 && fn_801BE648(pObject->mUnknown428->mUnknown1300) == pObject->mUnknown196) {
                        pExtra->mUnknown1704 = pObject->mUnknown424;
                        pExtra->mUnknown1705 = lbl_803EA4DC[(((fn_801CFE40(pObject->mUnknown352, pObject->mUnknown348) -
                                                               (pObject->mUnknown32 + 0x400000)) &
                                                              0xFFFFFF) +
                                                             0x100000) >>
                                                                21 &
                                                            7];
                        Restart_801BE068(pObject, pNode->mId, 1.0f);
                    }
                    if (pNode->mUnknown104 != -1 && pNode->mUnknown108 != -1 && t > pNode->mUnknown112) {
                        if (pNode->mUnknown116) {
                            pNode->mUnknown120 = pNode->mUnknown116;
                        } else {
                            fn_8004E090(pOwner, pNode->mUnknown104, pNode->mUnknown108);
                        }
                        if (pNode->mUnknown124) {
                            fn_800411C8(pOwner);
                        }
                    }
                    if (pNode->mUnknown100 != 15) {
                        fn_8005415C(pNode->mUnknown96, pNode->mUnknown100);
                        pNode->mUnknown100 = 15;
                    }
                    if (pNode->mUnknown68) {
                        pNode->mUnknown68 = 0;
                        pObject->mUnknown200.mActive = 1;
                        pObject->mUnknown200.mPhase = 3;
                        pObject->mUnknown200.mUnknown8 = pNode->mUnknown76;
                        pObject->mUnknown200.mUnknown4 = pNode->mUnknown72;
                        pObject->mUnknown200.mTime = 0.0f;
                        pObject->mUnknown200.mStep = 0;
                    }
                    fn_8004CBEC(pNode->mUnknown128, t, pObject, pOwner);
                    count = (unsigned int)pNode->mUnknown112;
                } else {
                    Object_80137ABC *pBall = fn_801374BC();

                    if (pBall) {
                        count = pBall->mState.mIndex;
                    } else {
                        count = (unsigned int)pNode->mUnknown112;
                    }
                }
                if (pNode->mUnknown92) {
                    fn_80067E3C(pNode->mUnknown92, &pos, pObject->mUnknown376, (unsigned int)t, pObject->mUnknown381,
                                count);
                }
                break;
            }
        } else {
            Vector_80039F5C pos;

            pos.mX = pObject->mUnknown8;
            pos.mY = pObject->mUnknown12;
            pos.mZ = pObject->mUnknown16;
            if (fn_801784C4()) {
                pos.mX = -pos.mX;
                pos.mY = -pos.mY;
            }
            if (pObject->mUnknown200.mActive) {
                Cycle_80041904 *pCycle = &pObject->mUnknown200;

                pCycle->mTime += lbl_803EA2C4 * (1.0f / 60.0f);
                switch (pCycle->mPhase) {
                case 0:
                    if (pCycle->mTime >= pCycle->mUnknown4) {
                        pCycle->mPhase = 2;
                        pCycle->mTime = 0.0f;
                    }
                    break;
                case 1:
                    if (pCycle->mTime >= pCycle->mUnknown4) {
                        pCycle->mPhase = 3;
                        pCycle->mTime = 0.0f;
                    }
                    break;
                case 2:
                    if (pCycle->mTime >= pCycle->mUnknown8) {
                        pCycle->mStep++;
                        pCycle->mPhase = 0;
                        pCycle->mTime = 0.0f;
                        pCycle->mStep %= pOwner->mUnknown248;
                    }
                    break;
                case 3:
                    if (pCycle->mTime >= pCycle->mUnknown8) {
                        pCycle->mStep++;
                        if (pCycle->mStep == pOwner->mUnknown248 - 1) {
                            pCycle->mPhase = 4;
                            pCycle->mActive = 0;
                        } else {
                            pCycle->mPhase = 1;
                            pCycle->mTime = 0.0f;
                        }
                    }
                    break;
                case 4:
                    break;
                }
            }
            if (pObject->mUnknown308) {
                fn_80067D4C(pObject->mUnknown308, &pos);
            }
        }
    }
    return 1;
}

void fn_8004BA44(int handle, Object_80041904 *pObject)
{
    char text[64];
    char state[64];
    int position = fn_8004D84C(handle);

    fn_8004D508(handle, "anim");
    if (fn_8004D5B8(handle, "emotion2State", state, 64)) {
        pObject->mUnknown196 = fn_8004C2FC(state);
    } else {
        pObject->mUnknown196 = -1;
    }
    fn_8004D5B8(handle, "emotion2State", state, 64);
    fn_8004D860(handle, position);
    if (fn_8004D508(handle, "animPal")) {
        pObject->mUnknown200.mActive = 1;
        pObject->mUnknown200.mUnknown8 = fn_8004D624(handle, "delay");
        pObject->mUnknown200.mUnknown4 = fn_8004D624(handle, "rate");
    }
    fn_8004D860(handle, position);
    if (fn_8004D508(handle, "animUV")) {
        pObject->mUnknown224 = 1;
        pObject->mUnknown288 = 0;
        pObject->mUnknown268 = fn_8004D624(handle, "delay");
        pObject->mUnknown272 = (unsigned int)fn_8004D624(handle, "row");
        pObject->mUnknown276 = (unsigned int)fn_8004D624(handle, "column");
        pObject->mUnknown292 = pObject->mUnknown272 * pObject->mUnknown276;
        fn_8004D6F4(handle, "rate", pObject->mUnknown228, pObject->mUnknown292);
        fn_8004D5B8(handle, "travelDim", text, 64);
        pObject->mUnknown300 = fn_8004B020(text, lbl_802D47DC);
        fn_8004D5B8(handle, "stepType", text, 64);
        pObject->mUnknown304 = fn_8004B020(text, lbl_802D48A8);
        pObject->mUnknown296 = 0.0f;
        pObject->mUnknown280 = 0;
        pObject->mUnknown284 = 0;
    } else {
        pObject->mUnknown224 = 0;
    }
    fn_8004D860(handle, position);
    if (fn_8004D508(handle, "sound")) {
        unsigned short sound;

        fn_8004D5B8(handle, "name", text, 64);
        sound = fn_8004C4AC(text);
        pObject->mUnknown308 = sound;
        if ((unsigned short)(sound - 79) <= 8) {
            pObject->mUnknown310 = sound - 79;
        }
    } else {
        pObject->mUnknown308 = 0;
    }
    fn_8004D860(handle, position);
}

void fn_8004BD20(int handle, Object_80041904 *pObject)
{
    char text[64];
    char state[64];
    int position = fn_8004D84C(handle);
    Node_80041904 *pNode = (Node_80041904 *)fn_801D2B7C(sizeof(Node_80041904), 0, 0);

    fn_801C1F94(pNode, 0, sizeof(Node_80041904));
    pNode->mpNext = pObject->mUnknown312;
    pNode->mUnknown108 = -1;
    pNode->mUnknown112 = 0.0f;
    pNode->mUnknown124 = 0;
    pNode->mUnknown128 = 0;
    pNode->mId = -1;
    pNode->mUnknown104 = -1;
    pNode->mUnknown116 = 0;
    pNode->mUnknown120 = 0;
    strcpy(pNode->mName, "");
    pObject->mUnknown312 = pNode;
    if (fn_8004D5B8(handle, "name", text, 64)) {
        fn_801C2EB4(pNode->mName, text);
    }
    if (fn_8004D508(handle, "anim") && fn_8004D5B8(handle, "emotion2State", text, 64)) {
        pNode->mId = fn_8004C2FC(text);
    }
    fn_8004D860(handle, position);
    if (fn_8004D508(handle, "swapPart")) {
        pNode->mUnknown112 = fn_8004D624(handle, "force");
        if (fn_8004D5B8(handle, "id", text, 64)) {
            pNode->mUnknown104 = fn_8004C204(text);
        }
        if (fn_8004D5B8(handle, "swapState", state, 64)) {
            pNode->mUnknown108 = fn_8004C270(text, state);
        }
        {
            float rate = lbl_803EA2C4;

            pNode->mUnknown116 = (unsigned int)(60.0f / rate * fn_8004D624(handle, "delay"));
        }
        pNode->mUnknown124 = fn_8004D5F0(handle, "bDisableCollisions");
    }
    fn_8004D860(handle, position);
    if (fn_8004D508(handle, "particle")) {
        do {
            Emitter_8004BD20 *pEmitter = (Emitter_8004BD20 *)fn_801D2B7C(sizeof(Emitter_8004BD20), 0, 0);

            fn_801C1F94(pEmitter, 0, sizeof(Emitter_8004BD20));
            pEmitter->mpNext = pNode->mUnknown128;
            pNode->mUnknown128 = pEmitter;
            pEmitter->mUnknown4 = -1;
            pEmitter->mUnknown8 = 0;
            pEmitter->mUnknown0 = -1;
            pEmitter->mUnknown40 = 0;
            pEmitter->mUnknown36 = 0.0f;
            if (fn_8004D5B8(handle, "emitPoint", text, 64) && fn_801C2FE4(text, "IMPACT") == 0) {
                pEmitter->mUnknown40 = 1;
            }
            if (fn_8004D5B8(handle, "psf", text, 64)) {
                int index = fn_801F0A8C(fn_800C47C4(), text);

                if (index == -1) {
                    pEmitter->mUnknown0 = 21;
                } else {
                    pEmitter->mUnknown0 = fn_8004C5E0(index);
                    if (pEmitter->mUnknown0 != 21) {
                        fn_80145100(pEmitter->mUnknown0, index);
                    }
                }
            }
            pEmitter->mUnknown36 = fn_8004D624(handle, "force");
            if (!pEmitter->mUnknown40) {
                float swap;

                fn_8004D728(handle, "emitTranslate", pEmitter->mUnknown12);
                swap = pEmitter->mUnknown12[1];
                pEmitter->mUnknown12[1] = pEmitter->mUnknown12[2];
                pEmitter->mUnknown12[2] = swap;
                fn_8004D728(handle, "emitRotate", pEmitter->mUnknown24);
                swap = pEmitter->mUnknown24[1];
                pEmitter->mUnknown24[1] = pEmitter->mUnknown24[2];
                pEmitter->mUnknown24[2] = swap;
            }
            pEmitter->mUnknown4 = fn_8004D5F0(handle, "occurances");
        } while (fn_8004D560(handle));
    }
    fn_8004D860(handle, position);
    if (fn_8004D508(handle, "animPal")) {
        pNode->mUnknown68 = 1;
        pNode->mUnknown88 = 4;
        pNode->mUnknown76 = fn_8004D624(handle, "delay");
        pNode->mUnknown72 = fn_8004D624(handle, "rate");
        lbl_803EA4E4 = pObject;
    } else {
        pNode->mUnknown68 = 0;
    }
    fn_8004D860(handle, position);
    if (fn_8004D508(handle, "surface")) {
        pNode->mUnknown100 = fn_8004D5F0(handle, "surfType");
        pNode->mUnknown96 = fn_8004D5F0(handle, "polyGroupId");
    } else {
        pNode->mUnknown100 = 15;
        pNode->mUnknown96 = -1;
    }
    fn_8004D860(handle, position);
    if (fn_8004D508(handle, "sound")) {
        fn_8004D5B8(handle, "name", text, 64);
        pNode->mUnknown92 = fn_8004C4AC(text);
    } else {
        pNode->mUnknown92 = 0;
    }
    fn_8004D860(handle, position);
}

int fn_8004C204(const char *pName)
{
    int i;

    for (i = 0; i < sizeof(lbl_802D14C8) / sizeof(lbl_802D14C8[0]); i++) {
        if (fn_801C2FE4(pName, lbl_802D14C8[i].mName) == 0) {
            return lbl_802D14C8[i].mId;
        }
    }
    return -1;
}

int fn_8004C270(const char *pName, const char *pState)
{
    int i;

    for (i = 0; i < sizeof(lbl_802D1D48) / sizeof(lbl_802D1D48[0]); i++) {
        if (fn_801C2FE4(pName, lbl_802D1D48[i].mName) == 0 &&
            fn_801C2FE4(pState, lbl_802D1D48[i].mState) == 0) {
            return lbl_802D1D48[i].mId;
        }
    }
    return -1;
}

int fn_8004C2FC(const char *pName)
{
    int i;

    for (i = 0; i < sizeof(lbl_802CFE34) / sizeof(lbl_802CFE34[0]); i++) {
        if (fn_801C2FE4(pName, lbl_802CFE34[i].mName) == 0) {
            return lbl_802CFE34[i].mId;
        }
    }
    return -1;
}

int fn_8004C368(const char *pName)
{
    int i;

    for (i = 0; i < sizeof(lbl_802CFBCC) / sizeof(lbl_802CFBCC[0]); i++) {
        if (fn_801C2FE4(pName, lbl_802CFBCC[i].mName) == 0) {
            return lbl_802CFBCC[i].mId;
        }
    }
    return 0;
}

int fn_8004C3D4(const char *pName)
{
    int i;

    for (i = 0; i < sizeof(lbl_802CFD2C) / sizeof(lbl_802CFD2C[0]); i++) {
        if (fn_801C2FE4(pName, lbl_802CFD2C[i].mName) == 0) {
            return lbl_802CFD2C[i].mId;
        }
    }
    return 0;
}

int fn_8004C440(const char *pName)
{
    int i;

    for (i = 0; i < sizeof(lbl_802CFDA4) / sizeof(lbl_802CFDA4[0]); i++) {
        if (fn_801C2FE4(pName, lbl_802CFDA4[i].mName) == 0) {
            return lbl_802CFDA4[i].mId;
        }
    }
    return 0;
}

unsigned short fn_8004C4AC(const char *pName)
{
    int i;

    for (i = 0; i < sizeof(lbl_802D3DC4) / sizeof(lbl_802D3DC4[0]); i++) {
        if (fn_801C2FE4(pName, lbl_802D3DC4[i].mName) == 0) {
            return lbl_802D3DC4[i].mId;
        }
    }
    return 0;
}

void fn_8004C518(int handle, Object_80041904 *pObject)
{
    char text[32];

    fn_8004D508(handle, "event");
    while (fn_8004D5B8(handle, "type", text, 32)) {
        switch (fn_8004C440(text)) {
        case 1:
            fn_8004BA44(handle, pObject);
            break;
        case 2:
            fn_8004BD20(handle, pObject);
            break;
        case 3:
            fn_8004BD20(handle, pObject);
            break;
        }
        fn_8004D560(handle);
    }
}

int fn_8004C5E0(int type)
{
    int i;
    unsigned int slot = 8;
    int result = 21;

    for (i = 0; i < 8; i++) {
        if (type == lbl_8030865C[i]) {
            lbl_8030867C[i]++;
            return i + 12;
        }
        if (lbl_8030865C[i] == -1 && slot == 8) {
            slot = i;
        }
    }
    if (result == 21 && slot < 8) {
        lbl_8030865C[slot] = type;
        lbl_8030867C[slot] = 1;
        result = slot + 12;
    }
    return result;
}

void fn_8004C684(int handle, Object_80041904 *pObject)
{
    char type[32];
    char reset[32];
    int hasType;
    int hasReset;

    fn_8004D498(handle);
    fn_8004D4B0(handle, "behavior");
    hasType = fn_8004D5B8(handle, "type", type, 32);
    hasReset = fn_8004D5B8(handle, "reset", reset, 32);
    pObject->mUnknown188 = 0;
    pObject->mUnknown184 = lbl_802CFCEC[pObject->mUnknown188];
    pObject->mUnknown196 = -1;
    pObject->mUnknown424 = 1;
    pObject->mUnknown312 = 0;
    pObject->mUnknown420 = 0;
    lbl_803EA4E4 = 0;
    if (hasType) {
        pObject->mUnknown188 = fn_8004C368(type);
        pObject->mUnknown184 = lbl_802CFCEC[pObject->mUnknown188];
        if (lbl_802CFD0C[pObject->mUnknown188]) {
            lbl_802CFD0C[pObject->mUnknown188](handle, pObject);
        }
        fn_8004C518(handle, pObject);
    }
    pObject->mUnknown192 = 0;
    if (hasReset) {
        pObject->mUnknown192 = lbl_802CFD98[fn_8004C3D4(reset)];
    }
    pObject->mUnknown380 = 0;
}

void fn_8004C7B8(Object_80041904 *pObject)
{
    Node_80041904 *pNode = pObject->mUnknown312;

    while (pNode) {
        Emitter_8004BD20 *pEmitter = pNode->mUnknown128;
        Node_80041904 *pFreeNode;

        while (pEmitter) {
            Emitter_8004BD20 *pFree = pEmitter;

            pEmitter = pEmitter->mpNext;
            fn_801D2BD0(pFree);
        }
        pNode->mUnknown128 = 0;
        pFreeNode = pNode;
        pNode = pNode->mpNext;
        fn_801D2BD0(pFreeNode);
    }
    pObject->mUnknown312 = 0;
    if (pObject->mUnknown420) {
        fn_801D2BD0(pObject->mUnknown420);
        pObject->mUnknown420 = 0;
    }
}

void fn_8004C844(Object_80040818 *pItem, float *pPos, float *pDir, const char *pName, int type,
                 Hitter_8004C844 *pHitter)
{
    int fire = 1;
    unsigned int time = fn_800289A8();
    Object_80041904 *pObject = pItem->mUnknown472;
    unsigned char i;

    for (i = 0; i < 3; i++) {
        if (pObject->mUnknown384[i].mType == type) {
            break;
        }
    }
    if (i == 3) {
        for (i = 0; i < 2; i++) {
            pObject->mUnknown384[i + 1].mType = pObject->mUnknown384[i].mType;
            pObject->mUnknown384[i + 1].mTime = pObject->mUnknown384[i].mTime;
        }
        pObject->mUnknown384[0].mTime = time;
        pObject->mUnknown384[0].mType = type;
    } else {
        if (time - pObject->mUnknown384[i].mTime < 30) {
            fire = 0;
        }
        pObject->mUnknown384[i].mTime = time;
    }
    if (!fire) {
        return;
    }
    pObject->mUnknown380 = 1;
    pObject->mUnknown381 = fn_8005164C(type);
    fn_801C2EB4(pObject->mUnknown316, pName);
    pObject->mUnknown360.mX = pPos[0];
    pObject->mUnknown360.mY = pPos[1];
    pObject->mUnknown360.mZ = pPos[2];
    pObject->mUnknown348 = pDir[0];
    pObject->mUnknown352 = pDir[1];
    pObject->mUnknown356 = pDir[2];
    if (pObject->mUnknown381) {
        pObject->mUnknown372 = fn_802270D4((char *)fn_801374BC() + 0x54);
    } else if (fn_80051680(type)) {
        if (pHitter) {
            pObject->mUnknown372 = pHitter->mUnknown508 * pHitter->mUnknown452;
        }
    } else {
        pObject->mUnknown372 = fn_802270D4(pDir);
    }
    if (pHitter) {
        float scale;

        pObject->mUnknown376 = pHitter->mId;
        scale = pObject->mUnknown372 * (1.0f / 70.0f);
        if (pHitter->mChannel != 0xFF) {
            int hi = lbl_803EA4D8;
            int lo = lbl_803EA4D9;
            float volume = (hi - lo) * scale + lo;

            if (volume > hi) {
                volume = hi;
            }
            fn_80194C5C(pHitter->mChannel, (unsigned char)(int)volume, lbl_803EA4DA);
        }
    } else {
        pObject->mUnknown376 = 0;
    }
}

void fn_8004CAA8(Object_80040818 *pItem, float *pPos, float *pDir, const char *pName, int type,
                 Hitter_8004C844 *pHitter)
{
    Object_80041904 *pObject = pItem->mUnknown472;
    Object_80040818 **ppLinked = pObject->mUnknown152;
    float strength = 0.0f;
    unsigned int i;

    if (pHitter) {
        strength = pHitter->mUnknown508 * pHitter->mUnknown452;
    }
    pObject->mUnknown372 = strength;
    fn_8004C844(pItem, pPos, pDir, pName, type, pHitter);
    for (i = 0; i < 8 && ppLinked[i]; i++) {
        if (pHitter) {
            ppLinked[i]->mUnknown472->mUnknown372 = strength;
        }
        fn_8004C844(ppLinked[i], pPos, pDir, pName, type, pHitter);
    }
}

int fn_8004CB98(int type)
{
    return lbl_8030867C[type - 12];
}

void fn_8004CBB0(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        lbl_8030867C[i] = 0;
        lbl_8030865C[i] = -1;
    }
}

void fn_8004CBE8(void)
{
}
}

struct Parser_8004D3A8 {
    char mName[256];
    void *mpData;
    void *mpCursor;
    int mId;
};

struct Cache_8004DA0C {
    int mHandle;
    char mName[256];
    char mUnknown260[48];
    int mReferences;
    void *mpArchive;
    int mId;
};

struct Instance_8004DA0C {
    Cache_8004DA0C *mpCache;
    Object_80235588 mRender;
};

extern "C" {
extern Child_801A9430 **lbl_803EA4F4;
extern Parser_8004D3A8 *lbl_803EA4F8;
extern unsigned short lbl_803EC7D0;
extern unsigned short lbl_803EC7D2;
extern int lbl_803EC7D4;
extern void *lbl_803EC7D8;
extern char *lbl_803EC7DC;
extern unsigned short lbl_803EA4FC;
extern Cache_8004DA0C *lbl_8030869C[];
extern void *lbl_803EA368;
void fn_801EBEF8(Quat_801EB488 *, int, int, int);
void fn_801EBFA0(Quat_801EB488 *, int, int, int);
void fn_801EB660(Quat_801EB488 *, Quat_801EB488 *, void *);
void fn_801D0508(void); void fn_801D0544(void);
void fn_801D0860(void *); void fn_801D0C58(void *);
void fn_801D0470(int); void fn_801D04C4(void); void fn_801D08FC(int);
void fn_80227C2C(void *, void *);
void fn_8022765C(void *, void *, void *);
void fn_802276B4(void *, void *, void *);
void fn_80227490(void *, void *, int, int, int);
int fn_801CFFD0(int, int);
int fn_801DCF0C(int, int, int, void *, void *);
void fn_801DCF8C(int);
void fn_801DD0C8(int, int, int, int (*)(Child_801A9430 *));
Child_801A9430 *fn_801DD268(int, int, int, Desc_800408E4 *);
void fn_801DD320(int, Child_801A9430 *);
void fn_80228D58(Child_801A9430 *); void fn_80228DD4(void); void fn_80228E18(void);
int fn_801F7C88(void);
Object_80040818 *fn_8004113C(int, unsigned int);
void fn_801A980C(Child_801A9430 *);
void *fn_801EF7BC(void *, int, char *);
int fn_801F0C50(void *, int);
void *fn_80216860(void *, const char *);
void *fn_80216BFC(void *, const char *);
void *fn_80216E34(void *);
int fn_80216F3C(void *, const char *, char *, int, const char *);
int fn_80217070(void *, const char *, int);
float fn_802171DC(void *, const char *, float);
int fn_8021743C(void *, const char *, float *, int);
int fn_8002D060(void *);
int fn_801C657C(void);
void fn_801A8548(Object_801A8620 *, int);
int fn_80228668(void);
void fn_80235C90(void *, int, float, float, float, float);
void fn_80235740(void *, int); void fn_80235764(void *, int);
int fn_801EF390(void *, int, int);
void fn_80235DB8(int); void fn_80234DCC(int, void *, const char *, int);
void fn_80235588(void *, int); void fn_802355E4(void *);
void fn_80235630(void *, int); void fn_80235C24(void *, void *);
void fn_80235D74(void *, int); void fn_802353D8(void *, int); void fn_802353F8(void *, int);
void fn_80234EA0(void *, int); void fn_801F010C(void *, int);
void fn_8004E16C(void *, int, Object_80040818 *);
void fn_801A8D9C(void *, int, Object_801A8620 *);
void fn_801A92D0(void *, Object_801A8620 *);
unsigned int fn_80236398(int);
void fn_801A5050(int, Vector_80039F5C *, float, float *);
int fn_8004D2F8(Child_801A9430 *);
void fn_8004D068(int);
int fn_8004D994(const char *);
void fn_8004DA0C(void *, int, Object_80040818 *);

void fn_8004CBEC(void *pData, float time, Object_80041904 *pObject, Object_80040818 *pOwner)
{
    Emitter_8004BD20 *p = (Emitter_8004BD20 *)pData;
    while (p) {
        if (!(time <= p->mUnknown36) && p->mUnknown0 != 21 &&
            (p->mUnknown4 == 0 || p->mUnknown8 < p->mUnknown4)) {
            p->mUnknown8++;
            Quat_801EB488 rotation;
            Vector_80039F5C position;
            if (p->mUnknown40) {
                Vector_80039F5C direction;
                direction.mX = -pObject->mUnknown348;
                direction.mY = -pObject->mUnknown352;
                direction.mZ = -pObject->mUnknown356;
                int angle = fn_801CFE40(direction.mZ, direction.mX);
                int heading = fn_801CFE40(direction.mY, direction.mX);
                fn_801EBFA0(&rotation, angle, heading, 0);
                position = pObject->mUnknown360;
            } else {
                fn_801EBEF8(&rotation, (int)(p->mUnknown24[2] * 46603.3789f),
                            (int)(p->mUnknown24[1] * 46603.3789f), (int)(p->mUnknown24[0] * 46603.3789f));
                fn_801EB660(&rotation, &rotation, &pObject->mUnknown96);
                fn_801D0508();
                fn_801D0860(&rotation);
                Vector_80039F5C offset;
                fn_80227C2C(&offset, p->mUnknown12);
                fn_801D0544();
                position.mX = pObject->mUnknown8;
                position.mY = pObject->mUnknown12;
                position.mZ = pObject->mUnknown16;
                fn_8022765C(&position, &position, &offset);
            }
            fn_80145EFC(p->mUnknown0, &position.mX, &rotation.mX, (Source_80144CE0 *)pOwner->mUnknown332);
            Record_8031B6F8 record;
            record.mId = p->mUnknown0;
            record.mPos[0] = position.mX;
            record.mPos[1] = position.mY;
            record.mPos[2] = position.mZ;
            record.mRot[0] = rotation.mX;
            record.mRot[1] = rotation.mY;
            record.mRot[2] = rotation.mZ;
            record.mRot[3] = rotation.mW;
            record.mpSource = (Source_80144CE0 *)pOwner->mUnknown332;
            fn_8014516C(record);
        }
        p = p->mpNext;
    }
}

void fn_8004CE6C(Object_80040818 *pOwner)
{
    Node_80041904 *p = pOwner->mUnknown472->mUnknown312;
    while (p) {
        if (p->mUnknown116 && p->mUnknown120 && --p->mUnknown120 == 0)
            fn_8004E090(pOwner, p->mUnknown104, p->mUnknown108);
        p = p->mpNext;
    }
}

void fn_8004CEE8(Child_801A9430 *p)
{
    Object_80041904 *pObject = p->mpObject54;
    Extra_8004149C *pExtra = pObject->mUnknown428;
    if (pExtra) {
        if (pExtra->mUnknown32) {
            p->mAngle4C = (p->mAngle4C + pExtra->mWord36) & 0xFFFFFF;
            Angles_801EBC18 angles;
            fn_801EBC18(&angles, &p->mRotation3C.mX);
            angles.mUnknown8 = p->mAngle4C + 0x400000;
            fn_801EBEF8(&p->mRotation3C, angles.mUnknown8, angles.mUnknown4, angles.mUnknown0);
        }
        int angle = fn_801CFFD0(p->mAngle4C, pObject->mUnknown32);
        if (pExtra->mUnknown33) {
            Vector_80039F5C delta;
            fn_802276B4(&delta, &pObject->mUnknown8, pObject->mUnknown20);
            fn_80227490(&delta, &delta, angle, 0, 0);
            fn_8022765C(&p->mUnknown30, &p->mUnknown30, &delta);
        }
    }
}

void fn_8004CFCC(int handle, int count)
{
    fn_801DCF0C(31, 112, count, 0, 0);
    if (handle) fn_801DD0C8(handle, 31, 0, fn_8004D2F8);
    lbl_803EA4F4 = (Child_801A9430 **)fn_801D2B7C(count * 4, 0, 0);
    fn_801C1F94(lbl_803EA4F4, 0, count * 4);
    fn_801F7C88();
    lbl_803EC7D0 = 0;
    lbl_803EC7D2 = count;
}

void fn_8004D068(int handle)
{
    if (lbl_803EA4F4) {
        for (unsigned short i = 0; i < lbl_803EC7D0; i++) {
            fn_801DD320(handle, lbl_803EA4F4[i]);
            fn_80228D58(lbl_803EA4F4[i]);
        }
        fn_80228DD4();
        fn_801D2BD0(lbl_803EA4F4);
        lbl_803EA4F4 = 0;
    }
}

void fn_8004D0F4(int handle) { fn_8004CFCC(handle, 64); }
void fn_8004D118(int handle) { fn_8004D068(handle); fn_80228E18(); fn_801DCF8C(31); }

void fn_8004D144(Desc_800408E4 *pDesc, int handle, int first)
{
    Child_801A9430 *p = fn_801DD268(handle, 31, 0, pDesc);
    lbl_803EA4F4[lbl_803EC7D0] = p;
    fn_801442FC(&p->mTracker60);
    p->mWord68 = 0;
    p->mUnknown14.mX = pDesc->mUnknown132.mUnknown4;
    p->mUnknown14.mY = pDesc->mUnknown132.mUnknown8;
    p->mUnknown14.mZ = pDesc->mUnknown132.mUnknown12;
    p->mUnknown30 = p->mUnknown14;
    fn_801EBFA0(&p->mRotation3C, (int)(pDesc->mUnknown132.mUnknown20 * 46603.3789f),
                (int)(pDesc->mUnknown132.mUnknown24 * 46603.3789f),
                (int)(pDesc->mUnknown132.mUnknown16 * 46603.3789f));
    p->mUnknown20 = p->mRotation3C;
    p->mpOwner50 = 0;
    p->mAngle4C = (int)((pDesc->mUnknown132.mUnknown24 - 90.0f) * 46603.3789f);
    p->mpOwner50 = fn_8004113C(pDesc->mUnknown176, first);
    if (!p->mpOwner50) {
        p->mpObject54 = 0;
    } else {
        p->mpObject54 = p->mpOwner50->mUnknown472;
        Child_801A9430 *pLast = (Child_801A9430 *)p->mpOwner50->mUnknown480;
        if (!pLast) p->mpOwner50->mUnknown480 = (int)p;
        else {
            while (pLast->mpUnknown5C) pLast = pLast->mpUnknown5C;
            pLast->mpUnknown5C = p;
        }
    }
    p->mpUnknown58 = fn_80054138(&pDesc->mUnknown132.mUnknown4);
    lbl_803EC7D0++;
    p->mUnknown6C = 0;
    fn_801A980C(p);
}

int fn_8004D2F8(Child_801A9430 *p) { if (p->mpOwner50) fn_8004CEE8(p); return 0; }

int fn_8004D334(const char *pName)
{
    for (int i = 0; i < lbl_803EC7D4; i++)
        if (fn_801C2FE4(pName, lbl_803EA4F8[i].mName) == 0) return i;
    return -1;
}

int fn_8004D3A8(void *pData, char *pName)
{
    int id = fn_801F0A8C((int)pData, pName);
    if (id == -1) return -1;
    int index = fn_8004D334(pName);
    if (index == -1) {
        fn_801C2EB4(lbl_803EA4F8[lbl_803EC7D4].mName, pName);
        void *p = fn_801EF7BC(pData, id, lbl_803EC7DC);
        lbl_803EA4F8[lbl_803EC7D4].mpCursor = p;
        lbl_803EA4F8[lbl_803EC7D4].mpData = p;
        lbl_803EC7DC += fn_801F0C50(pData, id) + 4;
        lbl_803EA4F8[lbl_803EC7D4].mId = id;
        index = lbl_803EC7D4++;
    } else lbl_803EA4F8[index].mpCursor = lbl_803EA4F8[index].mpData;
    return index;
}

void fn_8004D498(int handle) { lbl_803EA4F8[handle].mpCursor = lbl_803EA4F8[handle].mpData; }
int fn_8004D4B0(int handle, const char *pKey) {
    void *p = fn_80216860(lbl_803EA4F8[handle].mpCursor, pKey);
    lbl_803EA4F8[handle].mpCursor = p; return p != 0;
}
int fn_8004D508(int handle, const char *pKey) {
    void *p = fn_80216BFC(lbl_803EA4F8[handle].mpCursor, pKey);
    lbl_803EA4F8[handle].mpCursor = p; return p != 0;
}
int fn_8004D560(int handle) {
    void *p = fn_80216E34(lbl_803EA4F8[handle].mpCursor);
    lbl_803EA4F8[handle].mpCursor = p; return p != 0;
}
int fn_8004D5B8(int handle, const char *pKey, char *pText, int size) {
    return fn_80216F3C(lbl_803EA4F8[handle].mpCursor, pKey, pText, size, "");
}
int fn_8004D5F0(int handle, const char *pKey) { return fn_80217070(lbl_803EA4F8[handle].mpCursor, pKey, 0); }
float fn_8004D624(int handle, const char *pKey) { return fn_802171DC(lbl_803EA4F8[handle].mpCursor, pKey, 0.0f); }
int fn_8004D65C(int handle, const char *pKey, float *pValues) {
    float values[9];
    if (!fn_8021743C(lbl_803EA4F8[handle].mpCursor, pKey, values, 9)) return 0;
    for (int i = 0; i < 9; i++) pValues[i + i / 3] = values[i];
    return 1;
}
unsigned char fn_8004D6F4(int handle, const char *pKey, float *pValues, int count) {
    return fn_8021743C(lbl_803EA4F8[handle].mpCursor, pKey, pValues, count);
}
int fn_8004D728(int handle, const char *pKey, float *pValues) {
    float values[3];
    if (!fn_8021743C(lbl_803EA4F8[handle].mpCursor, pKey, values, 3)) return 0;
    pValues[0] = values[0]; pValues[2] = values[2]; pValues[1] = values[1]; return 1;
}
void fn_8004D798(void) {
    lbl_803EC7D4 = 0;
    lbl_803EA4F8 = (Parser_8004D3A8 *)fn_801D2B7C(0x4B60, 4, 0);
    fn_801C1F94(lbl_803EA4F8, 0, 0x4B60);
    lbl_803EC7D8 = fn_801D2B7C(0x18000, 4, 0);
    fn_801C1F94(lbl_803EC7D8, 0, 0x18000);
    lbl_803EC7DC = (char *)lbl_803EC7D8;
    fn_8004CBB0();
}
void fn_8004D818(void) { fn_801D2BD0(lbl_803EA4F8); lbl_803EA4F8 = 0; fn_801D2BD0(lbl_803EC7D8); }
int fn_8004D84C(int handle) { return (int)lbl_803EA4F8[handle].mpCursor; }
void fn_8004D860(int handle, int position) { lbl_803EA4F8[handle].mpCursor = (void *)position; }

int fn_8004D874(Object_801A8620 *p, int mode)
{
    Instance_8004DA0C *pInstance = p->mpRender12C;
    unsigned char flag;
    if (fn_8002D060(lbl_803EA368)) flag = p->mUnknownE8.mBytes[3] & 4;
    else flag = p->mUnknownE8.mBytes[3] & 1;
    if (flag) {
        int context = fn_801C657C();
        Object_80041904 *pPose = (Object_80041904 *)p->mpUnknown1D8;
        if (p->mFlagF0) fn_801A9368(p, (int)pPose->mUnknown200.mStep);
        if (pPose->mUnknown224 == 1) fn_801A93C0(p, &pPose->mUnknown224);
        int index = fn_80228668();
        Object_80235588 *pRender = &pInstance->mRender;
        fn_801D0470(index); fn_801D04C4();
        fn_801D0C58(&p->mUnknown4); fn_801D0860(&p->mUnknown18); fn_801D08FC(0x400000);
        fn_80235C90(pRender, context, 0.5f, 0.5f, 0.5f, 0.51f);
        fn_80235740(pRender, context); fn_801D0544(); fn_80235764(pRender, context);
    }
    if (p->mUnknownE8.mWord & 2) fn_801A8548(p, mode);
    return 0;
}

int fn_8004D994(const char *pName)
{
    for (int i = 0; i < lbl_803EA4FC; i++)
        if (fn_801C2FE4(pName, lbl_8030869C[i]->mName) == 0) return i;
    return -1;
}

void fn_8004DA0C(void *pData, int handle, Object_80040818 *pObject)
{
    Object_801A8620 *p = (Object_801A8620 *)pObject;
    char name[256];
    fn_8004D5B8(handle, "tideRef", name, 256);
    int index = fn_8004D994(name);
    p->mpRender12C = (Instance_8004DA0C *)fn_801D2B7C(196, 0, 0);
    fn_801C1F94(p->mpRender12C, 0, 196);
    Instance_8004DA0C *pInstance = p->mpRender12C;
    if (index == -1) {
        lbl_8030869C[lbl_803EA4FC] = (Cache_8004DA0C *)fn_801D2B7C(320, 0, 0);
        fn_801C1F94(lbl_8030869C[lbl_803EA4FC], 0, 320);
        pInstance->mpCache = lbl_8030869C[lbl_803EA4FC++];
        pInstance->mpCache->mReferences = 1;
        fn_801C2EB4(pInstance->mpCache->mName, name);
        pInstance->mpCache->mpArchive = pData;
        pInstance->mpCache->mId = fn_801F0A8C((int)pData, name);
        pInstance->mpCache->mHandle = fn_801EF390(pData, pInstance->mpCache->mId, 1);
        fn_80235DB8(pInstance->mpCache->mHandle);
        fn_80234DCC(pInstance->mpCache->mHandle, pInstance->mpCache->mUnknown260, "Objects", 3);
    } else {
        pInstance->mpCache = lbl_8030869C[index];
        pInstance->mpCache->mReferences++;
    }
    Object_80235588 *pRender = &pInstance->mRender;
    fn_80235588(pRender, 6);
    fn_80235630(pRender, pInstance->mpCache->mHandle);
    fn_80235C24(pRender, pInstance->mpCache->mUnknown260);
    fn_80235D74(pRender, 8); fn_802353D8(pRender, 3); fn_802353F8(pRender, 0);
    p->mUnknownE8.mWord = 1;
    if (fn_8004D5B8(handle, "tideEnvMapRef", name, 256)) p->mUnknownE8.mWord = 2;
    p->mUnknown14 = fn_8004D874;
}

void fn_8004DC08(Object_80040818 *pObject)
{
    Object_801A8620 *p = (Object_801A8620 *)pObject;
    Instance_8004DA0C *pInstance = p->mpRender12C;
    fn_802355E4(&pInstance->mRender);
    pInstance->mpCache->mReferences--;
    if (pInstance->mpCache->mReferences <= 0) {
        fn_80234EA0(pInstance->mpCache->mUnknown260, 3);
        fn_801F010C(pInstance->mpCache->mpArchive, pInstance->mpCache->mId);
    }
    fn_801D2BD0(p->mpRender12C);
    p->mpRender12C = 0;
}

void fn_8004DC88(void *pData, int handle, Object_80040818 *pObject)
{
    Object_801A8620 *p = (Object_801A8620 *)pObject;
    char type[32]; char name[128];
    p->mpUnknownA8 = pData;
    fn_8004D498(handle);
    if (!fn_8004D4B0(handle, "render")) return;
    fn_8004D5B8(handle, "type", type, 32);
    if (fn_801C2FE4(type, "NO_RENDER") == 0) {
        p->mTypeEC = 0;
        fn_8004E16C(pData, handle, pObject);
        return;
    }
    if (fn_801C2FE4(type, "STATIC_RENDER") == 0) {
        p->mTypeEC = 1;
        fn_8004DA0C(pData, handle, pObject);
    } else if (fn_801C2FE4(type, "DYNAMIC_RENDER") == 0) {
        p->mTypeEC = 2;
        fn_8004E16C(pData, handle, pObject);
        fn_8004D498(handle); fn_8004D4B0(handle, "render");
        fn_801A8D9C(pData, handle, p);
        fn_8004D498(handle); fn_8004D4B0(handle, "render");
    }
    if (fn_8004D5F0(handle, "bFadeable")) p->mUnknown140 = 1;
    else p->mUnknown140 = 0;
    p->mScale144 = 1.0f;
    if (fn_8004D508(handle, "shadow")) {
        float size = fn_8004D624(handle, "fShadowSize");
        unsigned int packed = fn_80236398(0);
        float color[4];
        color[0] = (packed & 0xFF) * 0.0078125f;
        color[1] = ((packed >> 8) & 0xFF) * 0.0078125f;
        color[2] = ((packed >> 16) & 0xFF) * 0.0078125f;
        color[3] = (packed >> 24) * 0.0078125f;
        if (size == 0.0f) size = 2.0f;
        fn_801A5050(0, &p->mUnknown4, size, color);
    }
    fn_8004D498(handle);
    if (fn_8004D4B0(handle, "animPal")) {
        p->mFlagF0 = 1;
        fn_8004D5B8(handle, "tideRef", name, 128);
        p->mUnknownF4 = fn_801F0A8C((int)pData, name);
        fn_801A92D0(pData, p);
    } else { p->mFlagF0 = 0; p->mUnknownF8 = 0; }
}
}

struct Cache_8004E16C {
    int mHandle;
    char mName[256];
    int mReferences;
    int mId;
    void *mpArchive;
};

struct Metadata_8004ED44 {
    unsigned char mKind;
    unsigned char mCount;
    unsigned short mUnknown2;
    char **mNames;
    Object_80040818 *mpObject;
    Block_80170E64 *mpBlock;
    unsigned short mUnknown16;
    unsigned short mType;
    unsigned short mUnknown20;
    short mUnknown22;
};

class Shape_801E2CB4 {
public:
    virtual ~Shape_801E2CB4();
    virtual void vfn_02(void *pBounds);
    virtual float vfn_03(Vector_80039F5C *pPoint, const float matrix[4][4],
                       Vector_80039F5C *pDelta, Vector_80039F5C *pNormal,
                       Vector_80039F5C *pOut, float *pDistance, float length);
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
};
struct Collection_801E7034;
struct Body_801E9538 {
    char mUnknown0[68];
    float mUnknown68;
    char mUnknown72[4];
    float mUnknown76;
    char mUnknown80[20];
    Vector_80039F5C mUnknown100;
    char mUnknown112[24];
    float mTransform[4][4];
    char mUnknown200[112];
    int mKind;
    Collection_801E7034 *mpShapes;
    char mUnknown320[4];
    Metadata_8004ED44 *mpMetadata;
};

struct Contact_8004ED44 {
    unsigned int mIndexA;
    unsigned int mIndexB;
    Vector_80039F5C mPos;
};

extern "C" {
extern unsigned short lbl_803EA4FE;
extern Cache_8004E16C *lbl_802D4974[];
extern Shape_801E2CB4 *lbl_8030883C[];
extern Shape_801E2CB4 *lbl_80308AD4[];
extern Vector_80039F5C *lbl_80308B0C[];
extern Body_801E9538 *lbl_80308D0C[];
extern Body_801E9538 *lbl_80308F0C[];
extern void *lbl_80308F44[];
extern Metadata_8004ED44 lbl_80308F64[];
extern void *lbl_803EA50C;
extern void *lbl_803EA514;
extern Shape_801E2CB4 *lbl_803EA51C;
extern int lbl_803EA520;
extern int lbl_803EA524;
extern int lbl_803EA528;
extern int lbl_803EA52C;
extern int lbl_803EA530;
extern Body_801E9538 *lbl_803EC7E0;
extern Body_801E9538 *lbl_803EC7E4;
void fn_801A9184(Object_801A8620 *);
void fn_801A9224(void); void fn_801A925C(void); void fn_801A932C(Object_801A8620 *);
int fn_801C20A0(const char *, ...);
void fn_801C4DEC(int);
int fn_801C4E98(Skeleton_80041930 *, const char *);
Object_80039F5C *fn_8003E0C8(Block_80170E64 *);
Shape_801E2CB4 *fn_801E71D0(Collection_801E7034 *, unsigned int);
void fn_801E9E18(Body_801E9538 *, Vector_80039F5C *, Vector_80039F5C *);
void fn_802273E8(void *, void *, int, int, int);
void fn_802271A4(void *, void *);
void fn_80227264(void *, void *, float);
int fn_800EA284(Object_80039F5C *, int, int);
void fn_80178718(Object_80039F5C *);
void fn_800E954C(Object_80039F5C *, int, int *, int, int *);
int fn_800EAC9C(Object_80039F5C *);
float fn_8016D9F4(Object_80039F5C *, float, float);
int fn_8013BA58(Object_80137ABC *, int *);
int fn_80178508(void *, int, int);
void fn_80139294(Object_80137ABC *, Vector_80039F5C *, Vector_80039F5C *);
void fn_801783D0(int, int);
void fn_801E9CC4(Body_801E9538 *);
void fn_801E9CF0(Body_801E9538 *, Vector_80039F5C *, Vector_80039F5C *);
void *fn_801D3BD0(unsigned int, int);
Shape_801E2CB4 *fn_801E3144(void *, Vector_80039F5C *, Vector_80039F5C *, float, float, float);
Shape_801E2CB4 *fn_801E4088(void *, Vector_80039F5C *, float, float, float, float, float);
Shape_801E2CB4 *fn_801E3DD8(void *, Vector_80039F5C *, float, float, float);
Collection_801E7034 *fn_801E7034(void *, int, int);
void fn_801E7120(Collection_801E7034 *, Shape_801E2CB4 *);
Body_801E9538 *fn_801E9538(void *, Vector_80039F5C *, Collection_801E7034 *, Metadata_8004ED44 *, float, float);
void fn_801E9C1C(Body_801E9538 *, Vector_80039F5C *);
void fn_801E9BDC(Body_801E9538 *, Vector_80039F5C *);
void fn_801E9C5C(Body_801E9538 *, Vector_80039F5C *);
void fn_801E99DC(Body_801E9538 *, Vector_80039F5C *);
void fn_801E9A44(Body_801E9538 *, void *);
void fn_801E9AF0(Body_801E9538 *, Vector_80039F5C *, Quat_801EB488 *);
void fn_801E9F0C(Body_801E9538 *, int);
void fn_801E2878(void *, Body_801E9538 *);
void *fn_801E8478(void *, Body_801E9538 *, Body_801E9538 *, Vector_80039F5C *, Vector_80039F5C *);
void fn_801E91E0(void *, void *);
int fn_801C3180(const char *);
char *fn_801C2EF0(char *, const char *, int);
void fn_8004E2B4(Object_80040818 *);

void fn_8004DF68(Object_80040818 *pObject)
{
    Object_801A8620 *p = (Object_801A8620 *)pObject;
    if (p->mTypeEC == 1) fn_8004DC08(pObject);
    else if (p->mTypeEC == 2) { fn_801A9184(p); fn_8004E2B4(pObject); }
    else fn_8004E2B4(pObject);
    if (p->mFlagF0) fn_801A932C(p);
}
void fn_8004DFDC(void)
{
    lbl_803EA4FC = 0;
    fn_801C1F94(lbl_8030869C, 0, 0x1A0);
    fn_801A9224();
}
void fn_8004E018(void)
{
    fn_801A925C();
    for (unsigned int i = 0; i < lbl_803EA4FC; i++) fn_801D2BD0(lbl_8030869C[i]);
    fn_801C1F94(lbl_8030869C, 0, 0x1A0);
    lbl_803EA4FC = 0;
}
void fn_8004E090(Object_80040818 *p, int index, int value)
{
    fn_80233CBC((char *)p->mUnknown300 + 32, index, value);
    p->mWord316 = value;
}
void fn_8004E0CC(Object_80040818 *p, int index, int value)
{
    fn_80233CBC((char *)p->mUnknown300 + 32, index, value);
}
int fn_8004E0F4(const char *pName)
{
    for (int i = 0; i < lbl_803EA4FE; i++)
        if (fn_801C2FE4(pName, lbl_802D4974[i]->mName) == 0) return i;
    return -1;
}
void fn_8004E16C(void *pData, int handle, Object_80040818 *pObject)
{
    Object_801A8620 *p = (Object_801A8620 *)pObject;
    char name[256];
    if (!fn_8004D508(handle, "skeleton") || !fn_8004D5B8(handle, "tideRef", name, 256)) {
        p->mpSkeleton130 = 0;
    } else {
        int index = fn_8004E0F4(name);
        if (index == -1) {
            lbl_802D4974[lbl_803EA4FE] = (Cache_8004E16C *)fn_801D2B7C(272, 0, 0);
            fn_801C1F94(lbl_802D4974[lbl_803EA4FE], 0, 272);
            Cache_8004E16C *pCache = lbl_802D4974[lbl_803EA4FE++];
            p->mpSkeleton130 = pCache;
            fn_801C2EB4(pCache->mName, name);
            pCache->mpArchive = pData;
            pCache->mReferences = 1;
            pCache->mId = fn_801F0A8C((int)pData, name);
            pCache->mHandle = fn_801EF390(pData, pCache->mId, 1);
            fn_801C20A0("Loading Object Skeleton\n");
            fn_801C4DEC(pCache->mHandle);
        } else {
            Cache_8004E16C *pCache = lbl_802D4974[index];
            pCache->mReferences++;
            p->mpSkeleton130 = pCache;
        }
    }
}
void fn_8004E2B4(Object_80040818 *pObject)
{
    Object_801A8620 *p = (Object_801A8620 *)pObject;
    Cache_8004E16C *pCache = p->mpSkeleton130;
    if (pCache) {
        pCache->mReferences--;
        if (pCache->mReferences <= 0) fn_801F010C(pCache->mpArchive, pCache->mId);
        fn_801D2BD0(pObject->mUnknown228);
        fn_801D2BD0(pObject->mpUnknown220);
    }
    p->mpSkeleton130 = 0;
}
void fn_8004E320(void)
{
    lbl_803EA4FE = 0;
    fn_801C1F94(lbl_802D4974, 0, 0x1A0);
}
void fn_8004E358(void)
{
    for (unsigned int i = 0; i < lbl_803EA4FE; i++) fn_801D2BD0(lbl_802D4974[i]);
    fn_801C1F94(lbl_802D4974, 0, 0x1A0);
    lbl_803EA4FE = 0;
}
void fn_8004E3CC(Object_80040818 *pObject, int *pAngles)
{
    Skeleton_80041930 *pSkeleton = fn_800410E0(pObject);
    if (pSkeleton) {
        int index = fn_801C4E98(pSkeleton, "main");
        if (index == -1) index = fn_801C4E98(pSkeleton, "Main");
        short *p = &pObject->mpUnknown220[index * 3];
        pAngles[0] = p[0] << 8;
        pAngles[1] = p[1] << 8;
        pAngles[2] = p[2] << 8;
    }
}
int fn_8004E468(void *unused, Body_801E9538 *pA, Body_801E9538 *pB)
{
    if (!(pA->mpMetadata->mUnknown2 & 1) || !(pB->mpMetadata->mUnknown2 & 1)) return 1;
    if (pA->mKind == 2 || pB->mKind == 2 || pA->mKind == 1 || pB->mKind == 1) return 0;
    return 1;
}

void fn_8004E4D0(Body_801E9538 *pBody, unsigned int index, Body_801E9538 *pOther,
                 unsigned int otherIndex, unsigned int count, Contact_8004ED44 *pContacts, float step)
{
    Object_80039F5C *p = fn_8003E0C8(pBody->mpMetadata->mpBlock);
    Shape_801E2CB4 *pShape = fn_801E71D0(pBody->mpShapes, index);
    for (unsigned int i = 0; i < count; i++) {
        Vector_80039F5C velocity, delta, normal, point, direction;
        float distance;
        fn_801E9E18(pBody, &pContacts[i].mPos, &velocity);
        float speed = fn_802270D4(&velocity);
        float length = (speed + speed) * step;
        if (!(length >= 0.002f)) length = 0.002f;
        fn_80227264(&delta, &velocity, -(length / speed));
        pShape->vfn_03(&pContacts[i].mPos, pBody->mTransform, &delta, &normal, &point, &distance, length);
        int code = fn_801BE648(p->mpUnknown792);
        if ((code == 0xB5 || code == 0xBA || code == 0xC5 || code == 0xC3 || code == 0xC4 ||
             code == 0xD2 || code == 0xE0 || code == 0xE5 || code == 0xE4 || code == 0xE6 ||
             code == 0xEB || code == 0xE1 || code == 0xED || code == 0xEC || p->mpState->mId == 0x32) &&
            (p->mFlags & 8)) return;
        if (!fn_801784C4()) {
            fn_802273E8(&direction, &normal, 0, 0, 0x800000);
            fn_802271A4(&direction, &direction);
        } else fn_802271A4(&direction, &normal);
        direction.mZ = 0.0f;
        if (normal.mZ > 0.8f || !(normal.mZ >= -0.8f)) {
            p->mMotion.mPos.mX -= p->mMotion.mUnknown40 + p->mMotion.mUnknown40;
            p->mMotion.mPos.mY -= p->mMotion.mUnknown44 + p->mMotion.mUnknown44;
            fn_802271A4(&direction, &p->mMotion.mUnknown40);
            direction.mX = -direction.mX;
            direction.mY = -direction.mY;
        } else {
            if (!(distance >= 0.0001f)) distance += 0.05555f;
            if (p->mMotion.mUnknown40 * direction.mX >= 0.0f ||
                fabsf(distance * direction.mX) >= fabsf(p->mMotion.mUnknown40))
                p->mMotion.mPos.mX += direction.mX * distance;
            else p->mMotion.mPos.mX = p->mMotion.mUnknown12.mX;
            if (p->mMotion.mUnknown44 * direction.mY >= 0.0f ||
                fabsf(distance * direction.mY) >= fabsf(p->mMotion.mUnknown44))
                p->mMotion.mPos.mY += direction.mY * distance;
            else p->mMotion.mPos.mY = p->mMotion.mUnknown12.mY;
        }
        int angle = fn_801CFE40(direction.mY, direction.mX);
        int facing = (angle + 0x800000) & 0xFFFFFF;
        if (code != 0xB5 && code != 0xBA && code != 0xC5 && code != 0xC3 && code != 0xC4 &&
            code != 0xD2 && code != 0xE0 && code != 0xE5 && code != 0xE4 && code != 0xE6 && code != 0xED) {
            switch (p->mpState->mId) {
            case 5: case 10: case 11: case 12: case 15: case 20:
            case 25: case 26: case 27: case 57: case 58: case 93:
                break;
            case 16: {
                Object_80039F5C *pPartner = fn_8009BCE8(&p->mUnknown336);
                if (!fn_800EA284(p, angle, facing)) return;
                fn_80178718(pPartner);
                p->mFlags = (p->mFlags | 0x10000) & ~0x80000;
                return;
            }
            case 17: {
                Object_80039F5C *pPartner = fn_8009BCE8(&p->mUnknown336);
                if (!fn_800EA284(p, angle, facing)) return;
                fn_80178718(p);
                pPartner->mFlags = (pPartner->mFlags | 0x10000) & ~0x80000;
                return;
            }
            case 32:
                fn_800EA284(p, angle, facing);
                return;
            case 36:
                fn_800E954C(p, 10, &facing, 1, &angle);
                break;
            default:
                if (!fn_800EAC9C(p) && !(p->mMotion.mUnknown28 < fn_8016D9F4(p, 0.5f, 1.0f)))
                    fn_800E954C(p, 58, &facing, 3, &angle);
                break;
            }
            if (!(fabsf(normal.mZ) >= 0.8f)) {
                if (fn_801CFFD0(p->mMotion.mUnknown32, facing) <= 0x200000) {
                    p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
                    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown0 = 0.0f;
                } else {
                    p->mUnknown512.mUnknown14 = 4;
                    p->mUnknown512.mUnknown4 = angle;
                    p->mUnknown512.mUnknown8 = angle;
                }
            }
        }
    }
}

void fn_8004EA80(Vector_80039F5C *pImpulse)
{
    Object_80137ABC *pBall = fn_801374BC();
    if (fn_8013BA58(pBall, 0) != 1) {
        Vector_80039F5C position, impulse, noise;
        fn_80137D58(pBall, &position);
        impulse = *pImpulse;
        if (fn_801784C4()) { impulse.mX = -impulse.mX; impulse.mY = -impulse.mY; }
        if (fn_8013BA58(pBall, 0) == 4) {
            float scale;
            if (!(fn_802270D4(&impulse) <= 30.0f)) scale = 4.15f;
            else scale = 5.0f;
            fn_80227264(&impulse, &impulse, scale);
        } else fn_80227264(&impulse, &impulse, 5.0f);
        float force = fn_802270D4(&impulse) * fn_80237260(0);
        noise.mX = force * (fn_80237260(0) - 0.5f);
        noise.mY = force * (fn_80237260(0) - 0.5f);
        noise.mZ = force * (fn_80237260(0) - 0.5f);
        if (!(fabsf(impulse.mX) >= 0.05f) && !(fabsf(impulse.mY) >= 0.05f) && !(impulse.mZ <= 0.0f)) {
            impulse.mX += pBall->mState.mUnknown54.mX;
            impulse.mY += pBall->mState.mUnknown54.mY;
            if (fn_80178508(&pBall->mState, 0, 1) > 2 && !lbl_803EA530) lbl_803EA530 = 1;
        }
        if (impulse.mX * pBall->mState.mUnknown54.mX >= 0.0f) impulse.mX = 0.0f;
        else position.mX = pBall->mState.mUnknown28.mX;
        if (impulse.mY * pBall->mState.mUnknown54.mY >= 0.0f) impulse.mY = 0.0f;
        else position.mY = pBall->mState.mUnknown28.mY;
        if (impulse.mZ * pBall->mState.mUnknown54.mZ >= 0.0f) impulse.mZ = 0.0f;
        else position.mZ = pBall->mState.mUnknown28.mZ;
        fn_8022765C(&impulse, &impulse, &noise);
        fn_80139294(pBall, &impulse, (Vector_80039F5C *)&pBall->mState);
        fn_80137D74(pBall, &position);
        fn_801783D0(24, 1);
    }
}

int fn_8004ED44(void *unused, Body_801E9538 *pA, Body_801E9538 *pB, unsigned int count,
                Contact_8004ED44 *pContacts, float step)
{
    unsigned char a = pA->mpMetadata->mKind;
    unsigned char b = pB->mpMetadata->mKind;
    if (a == 1 && b == 1) return 3;
    if (a != 6 && b != 6) {
        if (a == 1) {
            if (b == 2 || b == 4) fn_8004E4D0(pA, 0, pB, pContacts[0].mIndexB, count, pContacts, step);
            return 2;
        }
        if (b == 1) {
            if (a == 2 || a == 4) fn_8004E4D0(pB, 0, pA, pContacts[0].mIndexA, count, pContacts, step);
            return 1;
        }
    }
    return 0;
}

void fn_8004EE18(void *unused, Body_801E9538 *pA, int indexA, Body_801E9538 *pB, int indexB,
                 Vector_80039F5C *pPosA, Vector_80039F5C *pPosB, Vector_80039F5C *pNormal)
{
    Metadata_8004ED44 *a = pA->mpMetadata;
    Metadata_8004ED44 *b = pB->mpMetadata;
    Vector_80039F5C position, normal;
    if ((a->mKind == 3 || a->mKind == 5 || a->mKind == 4) &&
        (b->mKind == 1 || b->mKind == 6 || b->mKind == 0)) {
        position = *pPosA; normal = *pNormal;
        Hitter_8004C844 *pHitter = (Hitter_8004C844 *)fn_8003E0C8(b->mpBlock);
        if (a->mKind == 5) fn_8004CAA8(a->mpObject, &position.mX, &normal.mX, a->mNames[indexA], b->mType, pHitter);
        else fn_8004C844(a->mpObject, &position.mX, &normal.mX, a->mNames[indexA], b->mType, pHitter);
    } else if ((a->mKind == 1 || a->mKind == 6 || a->mKind == 0) &&
               (b->mKind == 3 || b->mKind == 5 || b->mKind == 4)) {
        position = *pPosB;
        normal.mX = -pNormal->mX; normal.mY = -pNormal->mY; normal.mZ = -pNormal->mZ;
        Hitter_8004C844 *pHitter = (Hitter_8004C844 *)fn_8003E0C8(a->mpBlock);
        if (b->mKind == 5) fn_8004CAA8(b->mpObject, &position.mX, &normal.mX, b->mNames[indexB], a->mType, pHitter);
        else fn_8004C844(b->mpObject, &position.mX, &normal.mX, b->mNames[indexB], a->mType, pHitter);
    } else if ((a->mKind == 3 || a->mKind == 5 || a->mKind == 4) &&
               (b->mKind == 3 || b->mKind == 5 || b->mKind == 4)) {
        position = *pPosA; normal = *pNormal;
        Hitter_8004C844 *pHitter = (Hitter_8004C844 *)fn_8003E0C8(b->mpBlock);
        if (a->mKind == 5) fn_8004CAA8(a->mpObject, &position.mX, &normal.mX, a->mNames[indexA], b->mType, pHitter);
        else fn_8004C844(a->mpObject, &position.mX, &normal.mX, a->mNames[indexA], b->mType, pHitter);
        normal.mX = -pNormal->mX; normal.mY = -pNormal->mY; normal.mZ = -pNormal->mZ;
        pHitter = (Hitter_8004C844 *)fn_8003E0C8(a->mpBlock);
        if (b->mKind == 5) fn_8004CAA8(b->mpObject, &position.mX, &normal.mX, b->mNames[indexB], a->mType, pHitter);
        else fn_8004C844(b->mpObject, &position.mX, &normal.mX, b->mNames[indexB], a->mType, pHitter);
    }
    if (a->mKind != 5 && b->mKind == 6) {
        Vector_80039F5C impulse;
        fn_80227264(&impulse, pNormal, -1.0f);
        fn_8004EA80(&impulse);
    } else if (a->mKind == 6 && b->mKind != 5) fn_8004EA80(pNormal);
}

void fn_8004F20C(void)
{
    for (unsigned int i = 0; i < (unsigned int)lbl_803EA520; i++) {
        Body_801E9538 *p = lbl_80308D0C[i];
        if (p->mKind == 2) {
            Vector_80039F5C force;
            force.mX = force.mY = 0.0f;
            force.mZ = -((1.0f / p->mUnknown68) * 10.73f);
            fn_801E9CC4(p);
            fn_801E9CF0(p, &force, &p->mUnknown100);
        }
    }
}

void fn_8004F2D0(int handle, Collection_801E7034 *pSet, Object_80041904 *pObject,
                 Vector_80039F5C *pA, Vector_80039F5C *pB, float friction, float bounce, float radius)
{
    float y = pA->mY; pA->mY = -pA->mZ; pA->mZ = y;
    y = pB->mY; pB->mY = -pB->mZ; pB->mZ = y;
    int index = lbl_803EA528;
    void *pMemory = fn_801D3BD0(44, 0);
    lbl_8030883C[index] = fn_801E3144(pMemory, pA, pB, friction, bounce, radius);
    index = lbl_803EA528++;
    fn_801E7120(pSet, lbl_8030883C[index]);
}
void fn_8004F3A4(int handle, Collection_801E7034 *pSet, Object_80041904 *pObject,
                 Vector_80039F5C *pA, Vector_80039F5C *pB, float friction, float bounce)
{
    float y = pA->mY; pA->mY = -pA->mZ; pA->mZ = y;
    y = pB->mY; pB->mY = -pB->mZ; pB->mZ = y;
    Vector_80039F5C center;
    fn_8022765C(&center, pA, pB);
    fn_80227264(&center, &center, 0.5f);
    int index = lbl_803EA528;
    void *pMemory = fn_801D3BD0(40, 0);
    lbl_8030883C[index] = fn_801E4088(pMemory, &center, friction, bounce,
                                     fabsf(pA->mX - center.mX), fabsf(pA->mY - center.mY), fabsf(pA->mZ - center.mZ));
    index = lbl_803EA528++;
    fn_801E7120(pSet, lbl_8030883C[index]);
}
void fn_8004F4B4(int handle, Collection_801E7034 *pSet, Object_80041904 *pObject,
                 Vector_80039F5C *pPoint, float friction, float bounce, float radius)
{
    float y = pPoint->mY; pPoint->mY = -pPoint->mZ; pPoint->mZ = y;
    int index = lbl_803EA528;
    void *pMemory = fn_801D3BD0(32, 0);
    lbl_8030883C[index] = fn_801E3DD8(pMemory, pPoint, friction, bounce, radius);
    index = lbl_803EA528++;
    fn_801E7120(pSet, lbl_8030883C[index]);
}
void fn_8004F56C(Metadata_8004ED44 *p, char (*pNames)[32], unsigned int count)
{
    p->mCount = count;
    if (!count) p->mNames = 0;
    else {
        unsigned char map[20];
        char *unique[20];
        unsigned char names = 1;
        unsigned char i = 1;
        map[0] = 0;
        int bytes = fn_801C3180(pNames[0]) + 1;
        for (; i < count; i++) {
            int found = 0;
            for (unsigned char j = 0; j < names; j++) {
                if (!fn_801C2FE4(pNames[j], pNames[i])) {
                    map[i] = j; found = 1; break;
                }
            }
            if (!found) {
                if (names != i) fn_801C2EF0(pNames[names], pNames[i], 32);
                bytes += fn_801C3180(pNames[names]) + 1;
                map[i] = names++;
            }
        }
        p->mNames = (char **)fn_801D2B7C(bytes + count * 4, 0, 0);
        char *pText = (char *)(p->mNames + count);
        for (i = 0; i < names; i++) {
            unique[i] = pText;
            fn_801C2EB4(pText, pNames[i]);
            pText += fn_801C3180(unique[i]) + 1;
        }
        for (i = 0; i < count; i++) p->mNames[i] = unique[map[i]];
    }
}
void fn_8004F710(Metadata_8004ED44 *p)
{
    if (p->mNames) {
        fn_801D2BD0(p->mNames);
        p->mCount = 0;
        p->mNames = 0;
    }
}
void fn_8004F754(int handle, Object_80040818 *pObject, int objectIndex)
{
    Object_80041904 *pState = pObject->mUnknown472;
    float mass = 0.0f;
    pState->mUnknown382 = 0;
    pState->mUnknown408 = 0.0f;
    pState->mUnknown412 = 0.0f;
    fn_8004D498(handle);
    if (fn_8004D4B0(handle, "physics")) mass = fn_8004D624(handle, "mass");
    fn_8004D498(handle);
    if (fn_8004D4B0(handle, "collision")) {
        Vector_80039F5C *pPos = (Vector_80039F5C *)&pState->mUnknown8;
        void *pRot = &pState->mUnknown96;
        lbl_80308B0C[lbl_803EA520] = pPos;
        pState->mUnknown408 = fn_8004D624(handle, "aeroConst");
        pState->mUnknown412 = fn_8004D624(handle, "spinDamp");
        pState->mUnknown382 = fn_8004D5F0(handle, "helpOffGround");
        int cursor = fn_8004D84C(handle);
        if (fn_8004D508(handle, "primitive")) {
            while (fn_8004D560(handle)) {}
        }
        fn_8004D860(handle, cursor);
        int kind;
        if (mass <= 0.0f) kind = 2;
        else kind = 0;
        Collection_801E7034 *pSet = fn_801E7034(fn_801D3BD0(76, 0), 20, kind);
        char names[20][32];
        char type[32];
        Vector_80039F5C a, b;
        if (fn_8004D508(handle, "primitive")) {
            unsigned char count = 0;
            do {
                fn_8004D5B8(handle, "name", names[count], 32);
                fn_8004D5B8(handle, "PRIM_TYPE", type, 32);
                if (!fn_801C2FE4(type, "CYLINDER")) {
                    fn_8004D728(handle, "PRIM_CYL_END1", &a.mX);
                    fn_8004D728(handle, "PRIM_CYL_END2", &b.mX);
                    float radius = fn_8004D624(handle, "PRIM_CYL_RADIUS");
                    float friction = fn_8004D624(handle, "friction");
                    float bounce = fn_8004D624(handle, "bounce");
                    fn_8004F2D0(handle, pSet, pState, &a, &b, friction, bounce, radius);
                } else if (!fn_801C2FE4(type, "BOX")) {
                    fn_8004D728(handle, "PRIM_BOX_MIN", &a.mX);
                    fn_8004D728(handle, "PRIM_BOX_MAX", &b.mX);
                    float friction = fn_8004D624(handle, "friction");
                    float bounce = fn_8004D624(handle, "bounce");
                    fn_8004F3A4(handle, pSet, pState, &a, &b, friction, bounce);
                } else if (!fn_801C2FE4(type, "SPHERE")) {
                    fn_8004D728(handle, "PRIM_SPH_POS", &a.mX);
                    float radius = fn_8004D624(handle, "PRIM_SPH_RADIUS");
                    float friction = fn_8004D624(handle, "friction");
                    float bounce = fn_8004D624(handle, "bounce");
                    fn_8004F4B4(handle, pSet, pState, &a, friction, bounce, radius);
                }
                count++;
            } while (fn_8004D560(handle));
            fn_8004F56C(&lbl_80308F64[lbl_803EA524], names, count);
        }
        fn_8004D498(handle);
        Vector_80039F5C inertia, velocity, acceleration;
        Body_801E9538 *pBody;
        Metadata_8004ED44 *pMetadata = &lbl_80308F64[lbl_803EA524];
        if (!fn_8004D4B0(handle, "physics")) {
            inertia.mX = inertia.mZ = 0.6640654802322388f;
            inertia.mY = 1.3281309604644775f;
            pMetadata->mKind = 5;
            pMetadata->mpObject = pObject;
            pMetadata->mUnknown2 = 1;
            pMetadata->mType = lbl_803EA524;
            pMetadata->mUnknown16 = objectIndex;
            pMetadata->mUnknown22 = -1;
            pMetadata->mUnknown20 = 0xFFFF;
            pBody = fn_801E9538(fn_801D3BD0(328, 0), &inertia, pSet, pMetadata, 0.0f, 2.0f);
            velocity.mX = velocity.mY = velocity.mZ = 0.0f;
            acceleration.mX = acceleration.mY = acceleration.mZ = 0.0f;
            fn_801E9C1C(pBody, &velocity); fn_801E9BDC(pBody, &acceleration);
            fn_801E99DC(pBody, pPos); fn_801E9A44(pBody, pRot);
        } else {
            float matrix[12];
            if (!fn_8004D65C(handle, "moi", matrix)) {
                inertia.mX = inertia.mZ = 0.6640654802322388f;
                inertia.mY = 1.3281309604644775f;
            } else {
                inertia.mX = matrix[0] * 3.0f;
                inertia.mY = matrix[10] * 3.0f;
                inertia.mZ = matrix[5] * 3.0f;
            }
            mass = fn_8004D624(handle, "mass");
            if (mass <= 0.0f) pMetadata->mKind = 4;
            else pMetadata->mKind = 3;
            pMetadata->mpObject = pObject;
            pMetadata->mUnknown2 = 1;
            pMetadata->mUnknown16 = objectIndex;
            pMetadata->mType = lbl_803EA524;
            pMetadata->mUnknown22 = -1;
            pMetadata->mUnknown20 = 0xFFFF;
            float threshold = fn_8004D624(handle, "dThres");
            pBody = fn_801E9538(fn_801D3BD0(328, 0), &inertia, pSet, pMetadata, mass, threshold);
            Vector_80039F5C initial;
            if (!fn_8004D728(handle, "iVel", &initial.mX)) {
                velocity.mX = velocity.mY = velocity.mZ = 0.0f;
                acceleration.mX = acceleration.mY = acceleration.mZ = 0.0f;
                fn_801E9C1C(pBody, &velocity); fn_801E9BDC(pBody, &acceleration);
            } else fn_801E9C5C(pBody, &initial);
            fn_801E99DC(pBody, pPos); fn_801E9A44(pBody, pRot);
            if (!(mass <= 0.0f)) {
                if (!fn_8004D5F0(handle, "enable")) fn_801E9F0C(pBody, 3);
                else fn_801E9F0C(pBody, 2);
            }
        }
        float damping = fn_8004D624(handle, "rollDamp");
        if (damping == 0.0f) damping = 4.0f;
        pBody->mUnknown76 = damping;
        fn_801E2878(lbl_803EA514, pBody);
        lbl_80308D0C[lbl_803EA520] = pBody;
        pObject->mUnknown476 = (Flags_800411C8 *)&lbl_80308F64[lbl_803EA524];
        lbl_80308F64[lbl_803EA524].mUnknown20 = lbl_803EA520;
        if (fn_8004D4B0(handle, "physics") && fn_8004D508(handle, "constraint")) {
            do {
                Vector_80039F5C local, world;
                fn_8004D728(handle, "location", &local.mX);
                float y = local.mY; local.mY = -local.mZ; local.mZ = y;
                fn_8022765C(&world, &local, pPos);
                int index = lbl_803EA52C;
                lbl_80308F44[index] = fn_801E8478(fn_801D3BD0(36, 0), pBody, lbl_803EC7E4, &local, &world);
                fn_801E91E0(lbl_803EA50C, lbl_80308F44[lbl_803EA52C]);
                lbl_803EA52C++;
            } while (fn_8004D560(handle));
        }
        lbl_803EA520++;
        lbl_803EA524++;
    }
}

void fn_8004FF8C(void)
{
    Vector_80039F5C position = {0.0f, 0.0f, 3.0f};
    Object_8008044C query;
    fn_8008040C(&query, 0);
    for (unsigned int team = 0; team < 2; team++) {
        for (unsigned int index = 0; index < 7; index++) {
            Object_80039F5C *pPlayer = fn_80039F5C(team, index);
            Block_80170E64 *pBlock = pPlayer->mpUnknown4;
            Object_8003DEC4 *pModel = (Object_8003DEC4 *)pBlock;
            fn_800809C4(&query, pModel->mUnknown4956, 0);
            float scale = fn_800811E0(&query) * 0.02631579f;
            int slot = team * 7 + index;
            Vector_80039F5C a = {0.0f, scale * 0.5f, 0.0f};
            Vector_80039F5C b = {0.0f, -a.mY, 0.0f};
            Vector_80039F5C inertia;
            inertia.mX = (scale * 150.0f) * scale * 0.083333336f + 7.59375f;
            inertia.mY = 15.1875f;
            inertia.mZ = inertia.mX;
            lbl_80308AD4[slot] = fn_801E3144(fn_801D3BD0(44, 0), &a, &b, 0.5f, 0.6f, 0.45f);
            Collection_801E7034 *pSet = fn_801E7034(fn_801D3BD0(76, 0), 1, 1);
            fn_801E7120(pSet, lbl_80308AD4[slot]);
            Metadata_8004ED44 *pMetadata = &lbl_80308F64[lbl_803EA524];
            pMetadata->mpBlock = pBlock;
            pMetadata->mKind = 1;
            pMetadata->mpObject = 0;
            pMetadata->mUnknown2 = 1;
            pMetadata->mUnknown20 = 0xFFFF;
            pMetadata->mType = lbl_803EA524;
            pMetadata->mUnknown22 = slot;
            Body_801E9538 *pBody = fn_801E9538(fn_801D3BD0(328, 0), &inertia, pSet, pMetadata, 150.0f, 0.4f);
            Vector_80039F5C velocity = {0.0f, 0.0f, 0.0f};
            Vector_80039F5C force = {0.0f, 0.0f, 0.0f};
            Quat_801EB488 rotation;
            fn_801EBEF8(&rotation, 0, 0, 0);
            fn_801E9AF0(pBody, &position, &rotation);
            position.mZ += 5.0f;
            fn_801E9F0C(pBody, 1);
            fn_801E9C1C(pBody, &velocity); fn_801E9BDC(pBody, &force);
            fn_801E2878(lbl_803EA514, pBody);
            lbl_80308F0C[slot] = pBody;
            lbl_803EA524++;
        }
    }
    fn_8008056C(&query);
}
void fn_800502C0(void)
{
    Vector_80039F5C position = {0.0f, 0.0f, 3.0f};
    fn_8013825C(fn_801374BC());
    Vector_80039F5C inertia;
    inertia.mX = 0.12f * 0.12f * 0.25f + 0.2f * 0.2f * 0.083333336f;
    inertia.mY = inertia.mX;
    inertia.mZ = 0.12f * 0.12f * 0.5f;
    Vector_80039F5C centers[2] = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};
    lbl_803EA51C = fn_801E3DD8(fn_801D3BD0(32, 0), &centers[0], 0.1f, 1.0f, 0.15f);
    Collection_801E7034 *pSet = fn_801E7034(fn_801D3BD0(76, 0), 1, 1);
    fn_801E7120(pSet, lbl_803EA51C);
    Metadata_8004ED44 *pMetadata = &lbl_80308F64[lbl_803EA524];
    pMetadata->mpBlock = 0;
    pMetadata->mpObject = 0;
    pMetadata->mKind = 6;
    pMetadata->mUnknown22 = -1;
    pMetadata->mUnknown2 = 1;
    pMetadata->mUnknown20 = 0xFFFF;
    pMetadata->mType = lbl_803EA524;
    Body_801E9538 *pBody = fn_801E9538(fn_801D3BD0(328, 0), &inertia, pSet, pMetadata, 1.0f, 0.4f);
    Vector_80039F5C velocity = {0.0f, 0.0f, 0.0f};
    Vector_80039F5C force = {0.0f, 0.0f, 0.0f};
    fn_801E99DC(pBody, &position);
    Quat_801EB488 rotation;
    fn_801EBEF8(&rotation, 0, 0, 0);
    fn_801E9A44(pBody, &rotation);
    fn_801E9F0C(pBody, 1);
    fn_801E9C1C(pBody, &velocity); fn_801E9BDC(pBody, &force);
    fn_801E2878(lbl_803EA514, pBody);
    lbl_803EC7E0 = pBody;
    lbl_803EA530 = 0;
    lbl_803EA524++;
}

}
