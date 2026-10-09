#include "game/fn_8022781C.h"
#include <string.h>

#include "game/bitstream.h"
#include "game/Level_80054130.h"
#include "game/Object_80040818.h"
#include "game/cu_80041210.h"
#include "game/cu_80136B1C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_80054138.h"
#include "game/fn_801EBC18.h"

/* Placement record that fn_800408E4 turns into an object. */
struct Desc_800408E4 {
    int mUnknown0;
    char mName[128];
    Desc_8004149C mUnknown132;
    void *mUnknown160;
    void *mUnknown164;
    int mUnknown168;
    int mUnknown172;
    int mUnknown176;
    unsigned short mUnknown180;
};

extern "C" {
void fn_800301C4(void *pStream, float *pValues, int bits, float scale);
void fn_80030304(void *pStream, float *pValues, int bits, float scale);
void fn_80030554(void *pStream, float *pValues, int bits, float scale);
void fn_8003065C(void *pStream, float *pValues, int bits, float scale);
void fn_80030ACC(void (*pSave)(BitStream_t *pStream),
                 void (*pLoad)(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2,
                               BitStream_t *pStream3, float t),
                 int size, const char *pName);
void fn_800400BC(Block_80170E64 *pBlock, Object_80041904 *pLinked);
void fn_8004AA34(Pose_80041930 *pPose, void *pStream, int count);
void fn_8004ABF4(Object_80040818 *pObject, Object_80041904 *pLinked, void *pStream0, void *pStream1, void *pStream2,
                 void *pStream3, float t);
void fn_8004AF84(Extra_8004149C *pExtra);
void fn_8004CBE8(void);
void fn_8004D0F4(int handle);
void fn_8004D118(int handle);
void fn_8004D144(Desc_800408E4 *pDesc, int handle, int first);
int fn_8004D3A8(void *pData, char *pName);
void fn_8004D798(void);
void fn_8004D818(void);
void fn_8004DC88(void *pData, int model, Object_80040818 *pObject);
void fn_8004DF68(Object_80040818 *pObject);
void fn_8004DFDC(void);
void fn_8004E018(void);
void fn_8004E0CC(Object_80040818 *pObject, int a, int b);
void fn_8004E320(void);
void fn_8004E358(void);
void fn_8004F754(int model, Object_80040818 *pObject, int index);
void fn_800504EC(void);
void fn_80051308(void);
void fn_80053A1C(void);
void fn_800B2A14(float *pPos, unsigned char *pAngles);
char *fn_801C310C(char *pText, const char *pPattern);
int fn_801C9DC8(int value);
int fn_801DCF0C(int type, int size, int count, void (*pInit)(Object_80040818 *, Desc_800408E4 *),
                void (*pRelease)(Object_80040818 *));
void fn_801DCF8C(int type);
void fn_801DD0C8(int handle, int type, int a, int (*pCallback)(Object_80040818 *));
Object_80040818 *fn_801DD268(int handle, int type, int a, Desc_800408E4 *pDesc);
void fn_801DD320(int handle, Object_80040818 *pObject);
void fn_801DD3AC(int handle, Object_80040818 *pObject, int a);
void fn_801EBEF8(Quat_801EB488 *pOut, int a, int b, int c);
void fn_801EC048(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB, float t);
int fn_801F1520(int value);
int fn_801F7C88(void);
int fn_80227594(float *pA, float *pB, float tolerance);
float fn_8022785C(Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_80227930(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB, float t);
void fn_80228D58(Object_80040818 *pObject);
void fn_80228DD4(void);
void fn_80228E18(void);

int fn_800400CC(Object_80040818 *pObject);
void fn_800400D4(Object_80040818 *pObject, unsigned int count);
void fn_80040788(int handle, int count);
void fn_800407F0(void);
void fn_80040818(Object_80040818 *pObject, Desc_800408E4 *pDesc);
void fn_80040884(Object_80040818 *pObject);
int fn_800408A4(Object_80040818 *pObject);
}

static Object_80040818 **lbl_803EA480 = 0;
static unsigned char lbl_803EA484 = 1;
static unsigned short lbl_803EC784;
static unsigned short lbl_803EC786;
static unsigned short lbl_803EC788;
static void *lbl_803EC78C;

extern "C" {
#if defined(DECOMP_COMPARE)
int fn_800400CC(Object_80040818 *pObject)
{
    return 0;
}

/* Links the newest object to up to eight earlier objects that share its
   group id, and points each of them back at it. */
void fn_800400D4(Object_80040818 *pObject, unsigned int count)
{
    Object_80041904 *pLinked = pObject->mUnknown472;
    unsigned int n = 0;
    unsigned int i;

    for (i = 0; i < count; i++) {
        if (lbl_803EA480[i]->mUnknown472->mUnknown144 == pLinked->mUnknown144) {
            if (n < 8) {
                pLinked->mUnknown152[n++] = lbl_803EA480[i];
                lbl_803EA480[i]->mUnknown472->mUnknown152[0] = pObject;
            } else {
                break;
            }
        }
    }
}
#endif

void fn_80040154(BitStream_t *pStream)
{
    unsigned int i;

    for (i = 0; i < lbl_803EC784; i++) {
        Object_80040818 *pObject = lbl_803EA480[i];

        if (pObject->mUnknown300 != 0) {
            if (fn_800410E0(pObject) != 0) {
                fn_8004AA34(&pObject->mUnknown172, pStream, pObject->mUnknown172.mUnknown4 - 1);
            }
            fn_80191068(pStream, pObject->mUnknown232_31, 1);
            fn_80191068(pStream, pObject->mUnknown300->mUnknown40, 8);
            fn_80030554(pStream, &pObject->mPos.mX, 17, 256.0f);
            fn_8003065C(pStream, &pObject->mRot.mX, 12, 1024.0f);
        }
    }
}

/* Load callback: reads each object back from two saved streams and blends
   position and rotation by t; the last two streams are read and skipped. */
void fn_8004023C(BitStream_t *pStream0, BitStream_t *pStream1, BitStream_t *pStream2, BitStream_t *pStream3, float t)
{
    unsigned int i;

    for (i = 0; i < lbl_803EC784; i++) {
        Object_80040818 *pObject = lbl_803EA480[i];

        if (pObject->mUnknown300 != 0) {
            Vector_80039F5C pos0;
            Vector_80039F5C pos1;
            Quat_801EB488 rot0;
            Quat_801EB488 rot1;
            unsigned char bit;
            unsigned char value;

            if (fn_800410E0(pObject) != 0) {
                fn_8004AF84(pObject->mUnknown472->mUnknown428);
                fn_8004ABF4(pObject, fn_80041904(i), pStream0, pStream1, pStream2, pStream3, t);
            }
            bit = ReadBitStream(pStream1, 1);
            ReadBitStream(pStream0, 1);
            if (bit) {
                pObject->mUnknown232_29 = 1;
            } else {
                pObject->mUnknown232_29 = 0;
            }
            value = ReadBitStream(pStream1, 8);
            ReadBitStream(pStream0, 8);
            fn_8004E0CC(pObject, 0, value);
            fn_800301C4(pStream1, &pos1.mX, 17, 256.0f);
            fn_800301C4(pStream0, &pos0.mX, 17, 256.0f);
            if (fn_8022785C(&pos0, &pos1) > 15.0f) {
                pObject->mPos.mX = pos0.mX;
                pObject->mPos.mY = pos0.mY;
                pObject->mPos.mZ = pos0.mZ;
            } else {
                fn_80227930(&pObject->mPos, &pos0, &pos1, t);
            }
            fn_80030304(pStream1, &rot1.mX, 12, 1024.0f);
            fn_80030304(pStream0, &rot0.mX, 12, 1024.0f);
            fn_801EC048(&pObject->mRot, &rot0, &rot1, t);
            if (pStream2 != 0) {
                ReadBitStream(pStream2, 1);
                ReadBitStream(pStream2, 8);
                fn_800301C4(pStream2, &pos1.mX, 17, 256.0f);
                fn_80030304(pStream2, &rot1.mX, 12, 1024.0f);
            }
            if (pStream3 != 0) {
                ReadBitStream(pStream3, 1);
                ReadBitStream(pStream3, 8);
                fn_800301C4(pStream3, &pos1.mX, 17, 256.0f);
                fn_80030304(pStream3, &rot1.mX, 12, 1024.0f);
            }
        }
    }
}

int fn_800404C8(void)
{
    int size = 0;
    unsigned int i;

    for (i = 0; i < lbl_803EC784; i++) {
        Object_80040818 *pObject = lbl_803EA480[i];

        if (pObject->mUnknown300 != 0) {
            Skeleton_80041930 *pSkeleton = fn_800410E0(pObject);

            if (pSkeleton != 0) {
                size += pSkeleton->mUnknown6 * 36;
                size += 64;
            }
            size += 108;
        }
    }
    return size;
}

void fn_80040558(int count, int handle)
{
    fn_80040788(handle, count);
    lbl_803EA480 = (Object_80040818 **)fn_801D2B7C(count * 4, 0, 0);
    memset(lbl_803EA480, 0, count * 4);
    fn_801F7C88();
    lbl_803EC786 = count;
    lbl_803EC784 = 0;
    lbl_803EC78C = fn_801EEB44("objmodel.dat", 44);
    fn_8004DFDC();
    fn_8004E320();
    fn_800504EC();
    fn_8004D0F4(handle);
}

void fn_800405F0(int handle)
{
    unsigned int i;

    if (lbl_803EA480 != 0) {
        for (i = 0; i < lbl_803EC784; i++) {
            Object_80041904 *pLinked = lbl_803EA480[i]->mUnknown472;

            if (pLinked->mUnknown184 != 0) {
                pLinked->mUnknown184(pLinked, lbl_803EA480[i], 3);
            }
            fn_801DD320(handle, lbl_803EA480[i]);
            fn_80228D58(lbl_803EA480[i]);
        }
        fn_80228DD4();
        fn_801D2BD0(lbl_803EA480);
        lbl_803EA480 = 0;
    }
    fn_800407F0();
    fn_8004E018();
    fn_8004E358();
    fn_80051308();
    fn_8004D118(handle);
    fn_801EEFAC(lbl_803EC78C);
}

void fn_800406C0(unsigned int flags)
{
    int all = (flags >> 8) & 1;
    unsigned int i;

    if (lbl_803EA480 != 0) {
        for (i = 0; i < lbl_803EC784; i++) {
            Object_80040818 *pObject = lbl_803EA480[i];

            if (all || ((1 << pObject->mUnknown472->mUnknown188) & flags)) {
                Object_80041904 *pLinked = pObject->mUnknown472;

                if (pLinked->mUnknown184 != 0) {
                    pLinked->mUnknown184(pLinked, pObject, 4);
                }
            }
        }
    }
    if (all || (flags & 0xC0)) {
        fn_80053A1C();
    }
}

void fn_80040788(int handle, int count)
{
    fn_801DCF0C(28, sizeof(Object_80040818), count, fn_80040818, fn_80040884);
    if (handle != 0) {
        fn_801DD0C8(handle, 28, 0, fn_800408A4);
    }
}

void fn_800407F0(void)
{
    fn_80228E18();
    fn_801DCF8C(28);
}

void fn_80040818(Object_80040818 *pObject, Desc_800408E4 *pDesc)
{
    pObject->mUnknown328 = pDesc->mUnknown0;
    strcpy(pObject->mName, pDesc->mName);
    pObject->mUnknown20 = fn_800400CC;
    pObject->mUnknown304 = 0;
    pObject->mUnknown336 = -100000.0f;
    pObject->mUnknown340 = -100000.0f;
    pObject->mUnknown332 = 0;
    pObject->mUnknown476 = 0;
    pObject->mUnknown480 = 0;
}

void fn_80040884(Object_80040818 *pObject)
{
    fn_8004DF68(pObject);
}

int fn_800408A4(Object_80040818 *pObject)
{
    int result = 0;

    if (lbl_803EA484) {
        result = pObject->mUnknown20(pObject);
    }
    return result;
}

void fn_800408E4(Desc_800408E4 *pDesc, int handle)
{
    Object_80041904 *pLinked;

    pDesc->mUnknown168 = fn_8004D3A8(pDesc->mUnknown160, pDesc->mName);
    if (pDesc->mUnknown168 == -1) {
        return;
    }
    lbl_803EA480[lbl_803EC784] = fn_801DD268(handle, 28, 0, pDesc);
    fn_801DD3AC(handle, lbl_803EA480[lbl_803EC784], 6);
    fn_8004DC88(pDesc->mUnknown164, pDesc->mUnknown168, lbl_803EA480[lbl_803EC784]);
    if (fn_801C310C(pDesc->mName, "CROWD") != 0) {
        lbl_803EA480[lbl_803EC784]->mUnknown232_27 = 1;
    }
    lbl_803EA480[lbl_803EC784]->mUnknown472 = fn_8004149C((void *)pDesc->mUnknown168, &pDesc->mUnknown132);
    lbl_803EA480[lbl_803EC784]->mUnknown472->mUnknown4 = lbl_803EC784;
    fn_8004F754(pDesc->mUnknown168, lbl_803EA480[lbl_803EC784], lbl_803EC784);
    lbl_803EA480[lbl_803EC784]->mUnknown472->mUnknown144 = pDesc->mUnknown172;
    lbl_803EA480[lbl_803EC784]->mUnknown472->mUnknown148 = pDesc->mUnknown180;
    memset(lbl_803EA480[lbl_803EC784]->mUnknown472->mUnknown152, 0, 32);
    lbl_803EA480[lbl_803EC784]->mUnknown308 = pDesc->mUnknown176;
    lbl_803EA480[lbl_803EC784]->mUnknown332 = fn_80054138(&pDesc->mUnknown132.mUnknown4);
    lbl_803EC784++;
}

void fn_80040A70(Object_80041904 *pLinked, int index)
{
    Object_80040818 *pObject = lbl_803EA480[index];

    if (pLinked->mUnknown428 != 0 && (pLinked->mUnknown428->mUnknown32 != 0 || pLinked->mUnknown428->mUnknown33 != 0)) {
        fn_800B2A14(&pLinked->mUnknown8, &pLinked->mUnknown428->mUnknown32);
        Angles_801EBC18 angles;
        fn_801EBC18(&angles, &pLinked->mUnknown96);
        angles.mUnknown8 = pLinked->mUnknown32 + 0x400000;
        fn_801EBEF8(&pObject->mRot, angles.mUnknown8, angles.mUnknown4, angles.mUnknown0);
    } else {
        pObject->mRot.mX = pLinked->mUnknown96;
        pObject->mRot.mY = pLinked->mUnknown100;
        pObject->mRot.mZ = pLinked->mUnknown104;
        pObject->mRot.mW = pLinked->mUnknown108;
    }
    pObject->mPos.mX = pLinked->mUnknown8;
    pObject->mPos.mY = pLinked->mUnknown12;
    pObject->mPos.mZ = pLinked->mUnknown16;
    if (pLinked->mUnknown428 != 0) {
        pLinked->mUnknown428->mUnknown56 = pLinked->mUnknown32;
    }
    if (fn_80227594(&pObject->mUnknown336, &pLinked->mUnknown8, 0.05f) == 0) {
        pObject->mUnknown332 = fn_80054138(&pLinked->mUnknown8);
        pObject->mUnknown336 = pLinked->mUnknown8;
        pObject->mUnknown340 = pLinked->mUnknown12;
    }
}

void fn_80040B88(int handle)
{
    Desc_800408E4 desc;
    unsigned short index;

    {
        int saved0 = fn_801F1520(4);
        int saved1 = fn_801C9DC8(4);

        desc.mUnknown160 = fn_801EEB44("objdefs.dat", 44);
        fn_801F1520(saved0);
        fn_801C9DC8(saved1);
    }
    desc.mUnknown164 = lbl_803EC78C;
    fn_8004D798();
    strcpy(desc.mName, "OBJDEF_ANIMBALL");
    desc.mUnknown132.mUnknown12 = 0.0f;
    desc.mUnknown132.mUnknown8 = 0.0f;
    desc.mUnknown132.mUnknown4 = 0.0f;
    desc.mUnknown132.mUnknown24 = 0.0f;
    desc.mUnknown132.mUnknown20 = 0.0f;
    desc.mUnknown132.mUnknown16 = 0.0f;
    desc.mUnknown172 = 0;
    desc.mUnknown176 = 0;
    desc.mUnknown180 = 0;
    index = lbl_803EC784;
    fn_800408E4(&desc, handle);
    fn_800400BC(fn_8013825C(fn_801374BC()), fn_80040F18(index)->mUnknown472);
    fn_8004D818();
    fn_801EEFAC(desc.mUnknown160);
}

void fn_80040C90(int handle)
{
    Desc_800408E4 desc;
    Level_80054130 *pLevel;
    Entry_80054130 *pEntry;
    unsigned int i;
    unsigned short first;

    {
        int saved0 = fn_801F1520(4);
        int saved1 = fn_801C9DC8(4);

        desc.mUnknown160 = fn_801EEB44("objdefs.dat", 44);
        fn_801F1520(saved0);
        fn_801C9DC8(saved1);
    }
    desc.mUnknown164 = lbl_803EC78C;
    fn_8004D798();
    pLevel = fn_80054130();
    for (i = 0; i < pLevel->mUnknown88; i++) {
        pEntry = &pLevel->mUnknown92[i];

        strcpy(desc.mName, &pLevel->mUnknown44[pEntry->mUnknown24 * 24]);
        desc.mUnknown132.mUnknown4 = pEntry->mUnknown0[0];
        desc.mUnknown132.mUnknown8 = pEntry->mUnknown0[1];
        desc.mUnknown132.mUnknown12 = pEntry->mUnknown0[2];
        desc.mUnknown132.mUnknown16 = pEntry->mUnknown0[3];
        desc.mUnknown132.mUnknown20 = pEntry->mUnknown0[4];
        desc.mUnknown132.mUnknown24 = pEntry->mUnknown0[5];
        desc.mUnknown172 = pEntry->mUnknown28;
        desc.mUnknown176 = pEntry->mUnknown32;
        desc.mUnknown180 = pEntry->mUnknown24;
        fn_800408E4(&desc, handle);
    }
    first = lbl_803EC784;
    lbl_803EC788 = first;
    for (i = 0; i < pLevel->mUnknown104; i++) {
        Entry_80054130 *pLinked = &pLevel->mUnknown108[i];
        unsigned short count;

        strcpy(desc.mName, &pLevel->mUnknown60[pLinked->mUnknown24 * 24]);
        desc.mUnknown132.mUnknown4 = pLinked->mUnknown0[0];
        desc.mUnknown132.mUnknown8 = pLinked->mUnknown0[1];
        desc.mUnknown132.mUnknown12 = pLinked->mUnknown0[2];
        desc.mUnknown132.mUnknown16 = pLinked->mUnknown0[3];
        desc.mUnknown132.mUnknown20 = pLinked->mUnknown0[4];
        desc.mUnknown132.mUnknown24 = pLinked->mUnknown0[5];
        desc.mUnknown172 = pLinked->mUnknown28;
        desc.mUnknown180 = pLinked->mUnknown24;
        desc.mUnknown176 = pLinked->mUnknown32;
        count = lbl_803EC784;
        fn_800408E4(&desc, handle);
        if (count != lbl_803EC784) {
            fn_800400D4(lbl_803EA480[lbl_803EC784 - 1], first);
        }
    }
    for (i = 0; i < pLevel->mUnknown112; i++) {
        pEntry = &pLevel->mUnknown116[i];

        strcpy(desc.mName, &pLevel->mUnknown68[pEntry->mUnknown24 * 24]);
        desc.mUnknown132.mUnknown4 = pEntry->mUnknown0[0];
        desc.mUnknown132.mUnknown8 = pEntry->mUnknown0[1];
        desc.mUnknown132.mUnknown12 = pEntry->mUnknown0[2];
        desc.mUnknown132.mUnknown16 = pEntry->mUnknown0[3];
        desc.mUnknown132.mUnknown20 = pEntry->mUnknown0[4];
        desc.mUnknown132.mUnknown24 = pEntry->mUnknown0[5];
        desc.mUnknown176 = pEntry->mUnknown32;
        fn_8004D144(&desc, handle, first);
    }
    fn_8004D818();
    fn_801EEFAC(desc.mUnknown160);
    fn_8004CBE8();
}

unsigned short fn_80040F10(void)
{
    return lbl_803EC784;
}

Object_80040818 *fn_80040F18(int index)
{
    return lbl_803EA480[index];
}

Object_80040818 *fn_80040F28(Vector_80039F5C *pPos, float *pDist)
{
    float best = 10000.0f;
    Object_80040818 *pBest = 0;
    unsigned int i;

    if (lbl_803EA480 != 0) {
        for (i = 0; i < lbl_803EC784; i++) {
            Object_80040818 *pObject = lbl_803EA480[i];
            float dist = fn_8022781C(&pObject->mPos, pPos);

            if (dist < best) {
                pBest = pObject;
                best = dist;
            }
        }
    }
    if (pDist != 0) {
        *pDist = best;
    }
    return pBest;
}

Object_80040818 *fn_80040FD4(Vector_80039F5C *pPos, int type, float *pDist)
{
    float best = 10000.0f;
    Object_80040818 *pBest = 0;
    unsigned int i;

    if (lbl_803EA480 != 0) {
        for (i = 0; i < lbl_803EC784; i++) {
            Object_80040818 *pObject = lbl_803EA480[i];

            if (pObject->mUnknown472->mUnknown188 == type) {
                float dist = fn_8022781C(&pObject->mPos, pPos);

                if (dist < best) {
                    pBest = pObject;
                    best = dist;
                }
            }
        }
    }
    if (pDist != 0) {
        *pDist = best;
    }
    return pBest;
}

int fn_80041094(int index)
{
    if (lbl_803EA480[index]->mUnknown304 != 0) {
        return 1;
    }
    return 0;
}

Skeleton_80041930 *fn_800410B8(int index)
{
    Object_80040818 *pObject = lbl_803EA480[index];

    if (pObject->mUnknown304 != 0) {
        return *pObject->mUnknown304;
    }
    return 0;
}

Skeleton_80041930 *fn_800410E0(Object_80040818 *pObject)
{
    if (pObject->mUnknown304 != 0) {
        return *pObject->mUnknown304;
    }
    return 0;
}

void fn_800410FC(void)
{
    fn_80030ACC(fn_80040154, fn_8004023C, fn_800404C8(), "Animated Big Objects");
}

Object_80040818 *fn_8004113C(int key, unsigned int count)
{
    unsigned short i;

    for (i = 0; i < count; i++) {
        Object_80040818 *pObject = lbl_803EA480[i];

        if (pObject->mUnknown308 == key) {
            return pObject;
        }
    }
    return 0;
}

Object_80040818 *fn_8004117C(int key)
{
    unsigned short i;

    for (i = lbl_803EC788; i < lbl_803EC784; i++) {
        Object_80040818 *pObject = lbl_803EA480[i];

        if (pObject->mUnknown472->mUnknown144 == key) {
            return pObject;
        }
    }
    return 0;
}

void fn_800411C8(Object_80040818 *pObject)
{
    if (pObject == 0) {
        return;
    }
    if (pObject->mUnknown476 == 0) {
        return;
    }
    pObject->mUnknown476->mUnknown2 &= ~1;
}

void fn_800411EC(Object_80040818 *pObject)
{
    if (pObject == 0) {
        return;
    }
    if (pObject->mUnknown476 == 0) {
        return;
    }
    pObject->mUnknown476->mUnknown2 |= 1;
}
}
