#include <math.h>
#include <string.h>

#include "game/Object_8003DEC4.h"
#include "game/Object_80039F5C.h"
#include "game/bitstream.h"
#include "game/cu_80041210.h"
#include "game/cu_80067C10.h"
#include "game/cu_8008E978.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_801BA2A8.h"
#include "game/fn_801BE60C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802372EC.h"
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

/* Emitter record allocated per "particle" block and linked through
   mpNext at +128 of its node. */
struct Emitter_8004BD20 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12[3];
    float mUnknown24[3];
    float mUnknown36;
    unsigned char mUnknown40;
    char mUnknown41[3];
    Emitter_8004BD20 *mpNext;
};

/* Element of the list at +312 of Object_80041904, linked through
   mpNext. */
struct Node_80041904 {
    char mName[64];
    int mId;
    unsigned char mUnknown68;
    char mUnknown69[3];
    float mUnknown72;
    float mUnknown76;
    char mUnknown80[8];
    int mUnknown88;
    unsigned short mUnknown92;
    char mUnknown94[2];
    int mUnknown96;
    int mUnknown100;
    int mUnknown104;
    int mUnknown108;
    float mUnknown112;
    int mUnknown116;
    int mUnknown120;
    unsigned char mUnknown124;
    char mUnknown125[3];
    Emitter_8004BD20 *mUnknown128;
    Node_80041904 *mpNext;
};

struct Flags_800411C8 {
    char mUnknown0[20];
    short mUnknown20;
};

/* View of the 548-byte placed object of src/game/cu_800400CC.cpp. */
struct Object_80040818 {
    char mUnknown0[172];
    Pose_80041930 mUnknown172;
    void *mUnknown228;
    char mUnknown232[16];
    unsigned int mUnknown248;
    char mUnknown252[220];
    Object_80041904 *mUnknown472;
    Flags_800411C8 *mUnknown476;
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
extern int lbl_8030865C[8];
extern int lbl_8030867C[8];
extern float lbl_803EA4E8;
extern float lbl_803EA4EC;
extern float lbl_803EA4F0;

void fn_800301C4(void *pStream, float *pValues, int bits, float scale);
void fn_80030554(void *pStream, float *pValues, int bits, float scale);
Object_80040818 *fn_80040F18(int index);
Skeleton_80041930 *fn_800410B8(int index);
void fn_800411C8(Object_80040818 *pObject);
void fn_800411EC(Object_80040818 *pObject);
int fn_8004C204(const char *pName);
int fn_8004C270(const char *pName, const char *pState);
int fn_8004C2FC(const char *pName);
unsigned short fn_8004C4AC(const char *pName);
int fn_8004C5E0(int index);
int fn_8004D508(int handle, const char *pKey);
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
void fn_8004CBEC(void *pData, Object_80041904 *pObject, Object_80040818 *pOwner, float t);
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
void fn_801A9F98(Extra_8004149C *pExtra, int entry, int a, int b);
void fn_801AA124(int entry, void *a, int b, void *c);
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
float fn_802270A4(void *pV);
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

void fn_8004A8C4(Extra_8004149C *pExtra, int entry, int a) { fn_801A9F98(pExtra, entry, a, 0); }

void fn_8004A8E8(int entry, void *a, int b, void *c) { fn_801AA124(entry, a, b, c); }

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

/* Clears flag bits 0x78 of the Extra block and restarts its 0x801BE068 entry. */
static inline void Restart_801BE068(Object_80041904 *pObject, unsigned short key, float value)
{
    fn_8004AF84(pObject->mUnknown428);
    fn_801BE068(pObject->mUnknown428->mUnknown1300, pObject->mUnknown428->mUnknown48, pObject->mUnknown428->mUnknown60,
                key, pObject, value);
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
                pExtra->mUnknown1704 = pObject->mUnknown427;
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
                        pExtra->mUnknown1704 = pObject->mUnknown427;
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
                    fn_8004CBEC(pNode->mUnknown128, pObject, pOwner, t);
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
}
