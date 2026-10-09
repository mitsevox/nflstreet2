#include "game/Class_8018FD64Inline.h"
#include "game/Object_80039F5C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801BE60C.h"
#include "game/fn_800B65A0.h"

struct Object_80053674;

struct Node_80053674 {
    unsigned char mUnknown00[128];
    void *mpUnknown80;
    Node_80053674 *mpNext;
};

struct Container_80053258 {
    unsigned char mUnknown00[152];
    Object_80053674 *mpUnknown98;
    unsigned char mUnknown9C[156];
    Node_80053674 *mpUnknown138;
};

struct Model_80053258 {
    unsigned char mUnknown00[324];
    void *mpUnknown144;
    unsigned char mUnknown148[4];
    unsigned char mUnknown14C[1];
};

struct ModelRef_80053258 {
    Model_80053258 *mpModel;
};

struct Object_80053674 {
    unsigned char mUnknown00[232];
    unsigned int mUnknownE8;
    unsigned char mUnknownEC[64];
    ModelRef_80053258 *mpUnknown12C;
    unsigned char mUnknown130[8];
    Node_80053674 *mpUnknown138;
    unsigned char mUnknown13C[44];
    Vector_80039F5C mUnknown168;
    unsigned char mUnknown174[4];
    union {
        int mUnknown178;
        unsigned char mUnknown178Bytes[4];
    };
    unsigned char mUnknown17C;
    unsigned char mUnknown17D[91];
    Container_80053258 *mpUnknown1D8;
};

struct Args_80052F54 {
    Object_80053674 *mpObject;
    union {
        int mRef;
        unsigned char mRefBytes[4];
    };
    unsigned int mKind;
    Node_80053674 *mpNode;
};

struct State_80309CEC {
    Object_80053674 *mpObject;
    int mValue;
};

struct Record_800530E8 {
    unsigned short mUnknown00;
    unsigned short mUnknown02;
    unsigned char mUnknown04[6];
    unsigned short mUnknown0A;
    void *mpUnknown0C;
    unsigned char mUnknown10[2];
    unsigned short mUnknown12;
    char *mpUnknown14;
};

struct Text_80309CB4 {
    unsigned short mUnknown00;
    unsigned short mUnknown02;
    unsigned short mUnknown04;
    unsigned short mUnknown06;
    int mUnknown08;
    void *mpUnknown0C;
    unsigned short mUnknown10;
    unsigned short mUnknown12;
    int mUnknown14;
    char *mpUnknown18;
};

extern "C" {
extern Text_80309CB4 lbl_80309CB4[2];
extern State_80309CEC lbl_80309CEC[5];
extern Args_80052F54 lbl_80309D14[15];
int lbl_803EA540 = 0;
unsigned char lbl_803EA544 = 0;
int lbl_803EA548 = 0;

int fn_80052D08(Args_80052F54 *);
void fn_8004CBEC(void *, Container_80053258 *, Object_80053674 *, float);
void fn_8004E090(Object_80053674 *, int, int);
void fn_8005D2C8(int);
void fn_80067E3C(int, void *, int, int, int, int);
void fn_8007ECBC(int, int);
void fn_80083E1C(Object_8007A334 *, int);
void fn_8009BD2C(Object_80039F5C *, int *);
void fn_800D6D7C(Object_80039F5C *, unsigned int, int);
int fn_800A3444(void);
int fn_801485D4(void);
int fn_80156704(void);
void fn_80156C78(int, int);
int fn_801784C4(void);
void fn_8017CA3C(int, int);
void fn_8017D7C4(const char *);
void fn_80180BE4(int, int *, int *);
int fn_80186F7C(unsigned char);
int fn_80188DD0(int);
int fn_801C2FE4(Node_80053674 *, const char *);
void *fn_8021EA44(int);
char *fn_80220BFC(int, int);
void *fn_80221BAC(void *, int, int);
void fn_80211EDC(void *, void *, int, int);
void fn_80211EBC(void *, void *, int, void *, int, int);
int fn_8022F358(int);
int fn_8022F384(int);
int fn_8022F3D4(int);
int fn_8022F4BC(void);

void fn_80052F54(Args_80052F54 *pArgs)
{
    unsigned int index = fn_800A3444();
    int db = fn_80186F7C(pArgs->mRefBytes[2]);
    if (fn_801485D4() == 0 && fn_80156704() == 0 && db != -1 && index <= 9) {
        int handle = fn_8022F3D4(fn_8022F358(db));
        int bit = 1 << index;
        Class_8018FD64 cursor;
        cursor.fn_8018FDEC(0x464E4955, 0x44494755, 0, 0, handle);
        int value = cursor.Class_8018FD64::fn_8018FF9C(0x504C5555);
        if (!(value & bit)) {
            value |= bit;
            cursor.Class_8018FD64::fn_8019002C(0x504C5555, value);
            lbl_803EA544 = 1;
            lbl_803EA540 = bit;
            if (value == 0x3FF) {
                fn_8005D2C8(1);
                fn_8007ECBC(fn_8022F384(fn_8022F4BC()), 34);
            }
        }
    }
}

int fn_80053084(Args_80052F54 *pArgs)
{
    Object_80053674 *pObject = pArgs->mpObject;
    int *pRef = &pArgs->mRef;
    int i = 0;
    while (i <= 4 && lbl_80309CEC[i].mpObject != pObject) {
        i++;
    }
    if (lbl_80309CEC[i].mValue != ((unsigned char *)pRef)[2]) {
        return 1;
    }
    return 0;
}

void fn_800530E8(void)
{
    Object_8007A334 cursor;
    fn_80083E1C(&cursor, 0);
    for (int i = 0; i <= 1; i++) {
        int id, team;
        fn_80180BE4(i, &id, &team);
        char *pText = 0;
        fn_80084034(&cursor, i, 0);
        int value = fn_80084438(&cursor);
        Record_800530E8 *pRecord = (Record_800530E8 *)fn_80221BAC(fn_8021EA44(1), 4, id);
        if (value == 0) {
            pText = fn_80220BFC(5, fn_80188DD0(i != 0));
        }
        lbl_80309CB4[i].mUnknown00 = pRecord->mUnknown00;
        lbl_80309CB4[i].mUnknown02 = pRecord->mUnknown02;
        lbl_80309CB4[i].mUnknown04 = pRecord->mUnknown0A;
        lbl_80309CB4[i].mUnknown06 = 0;
        lbl_80309CB4[i].mUnknown08 = pRecord->mUnknown00 * pRecord->mUnknown02;
        lbl_80309CB4[i].mpUnknown0C = pRecord->mpUnknown0C;
        lbl_80309CB4[i].mUnknown10 = pRecord->mUnknown0A;
        lbl_80309CB4[i].mUnknown12 = pRecord->mUnknown12;
        lbl_80309CB4[i].mUnknown14 = 512;
        if (pText) {
            lbl_80309CB4[i].mpUnknown18 = pText;
        } else {
            lbl_80309CB4[i].mpUnknown18 = pRecord->mpUnknown14;
        }
    }
    fn_80083F68(&cursor);
}

void fn_80053258(Args_80052F54 *pArgs)
{
    Object_80053674 *pObject = pArgs->mpObject;
    int *pRef = &pArgs->mRef;
    int i = 0;
    int changed = 0;
    int count = 0;
    while (i <= 4 && lbl_80309CEC[i].mpObject != pObject) {
        i++;
    }
    if (lbl_80309CEC[i].mValue == ((unsigned char *)pRef)[2]) {
        return;
    }
    switch (pArgs->mKind) {
    case 1: fn_8017D7C4("Hotspot Tackle!"); break;
    case 2: fn_8017D7C4("Hotspot Broken Tackle!"); break;
    case 3: fn_8017D7C4("Hotspot Pass!"); break;
    case 7: fn_8017D7C4("Hotspot Dive!"); break;
    case 4: fn_8017D7C4("Hotspot Catch!"); break;
    case 5: fn_8017D7C4("Hotspot Juke!"); break;
    case 6: fn_8017D7C4("Hotspot Hurdle!"); break;
    default: fn_8017D7C4("Hotspot Hit!"); break;
    }
    if (lbl_80309CEC[i].mValue != 2) {
        changed = 1;
    }
    lbl_80309CEC[i].mValue = ((unsigned char *)pRef)[2];
    for (int j = 0; j < 5; j++) {
        if (lbl_80309CEC[j].mValue == ((unsigned char *)pRef)[2]) {
            count++;
        }
    }
    if (count == 1) {
        fn_80052F54(pArgs);
    }
    fn_800D6D7C(fn_8009BCE8(pRef), count, changed);
    fn_8017CA3C(*pRef, 1);
    Object_80053674 *pOther = pObject->mpUnknown1D8->mpUnknown98;
    if (pOther) {
        pOther->mUnknownE8 &= ~1;
    }
    if (lbl_80309CB4[0].mpUnknown0C == 0) {
        fn_800530E8();
        Model_80053258 *pModel = pObject->mpUnknown12C->mpModel;
        fn_80211EDC(pModel->mUnknown14C, &lbl_80309CB4[0].mUnknown10, 0, 0);
        pModel = pObject->mpUnknown12C->mpModel;
        fn_80211EBC(pModel->mpUnknown144, pModel->mUnknown14C, 0, &lbl_80309CB4[0], 0, 0);
        pModel = pObject->mpUnknown12C->mpModel;
        fn_80211EDC(pModel->mUnknown14C, &lbl_80309CB4[1].mUnknown10, 1, 0);
        pModel = pObject->mpUnknown12C->mpModel;
        fn_80211EBC(pModel->mpUnknown144, pModel->mUnknown14C, 1, &lbl_80309CB4[1], 1, 1);
    }
    if (lbl_80309CEC[i].mValue == 0) {
        fn_8004E090(pObject, 0, 0);
    } else {
        fn_8004E090(pObject, 0, 1);
    }
    pObject->mUnknownE8 |= 1;
    Object_80039F5C *pPlayer = fn_8009BCE8(pRef);
    if (pPlayer) {
        fn_80067E3C(53, &pPlayer->mMotion, *pRef, 0, 0, 0);
    }
}

void fn_80053554(Args_80052F54 *pArgs)
{
    if (lbl_803EA548 == 15) {
        lbl_803EA548 = 0;
    }
    lbl_80309D14[lbl_803EA548] = *pArgs;
    lbl_803EA548++;
}

void fn_800535A8(void)
{
    for (int i = 0; i <= 14; i++) {
        fn_801C1F94(&lbl_80309D14[i], 0, sizeof(Args_80052F54));
    }
    lbl_803EA548 = 0;
}

void fn_800535FC(void)
{
    for (int i = 0; i <= 14; i++) {
        fn_801C1F94(&lbl_80309D14[i], 0, sizeof(Args_80052F54));
    }
    lbl_803EA548 = 0;
}

int fn_80053650(void *, Object_80053674 *pObject, int event)
{
    if (event != 0 && event == 4) {
        pObject->mUnknownE8 |= 1;
    }
    return 1;
}

int fn_80053674(Object_80053674 *pContext, Object_80053674 *pObject, int event)
{
    if (event == 0) {
        for (int i = 0; i <= 4; i++) {
            if (lbl_80309CEC[i].mpObject == 0) {
                lbl_80309CEC[i].mValue = 2;
                lbl_80309CEC[i].mpObject = pObject;
                break;
            }
        }
        pObject->mUnknownE8 &= ~1;
        lbl_80309CB4[1].mpUnknown0C = 0;
        lbl_803EA540 = 0;
        lbl_80309CB4[0].mpUnknown0C = 0;
        lbl_803EA544 = 0;
        fn_800535A8();
        fn_8005D2C8(0);
    } else if (event == 3) {
        for (int i = 0; i <= 4; i++) {
            if (lbl_80309CEC[i].mpObject == pObject) {
                lbl_80309CEC[i].mpObject = 0;
                lbl_80309CEC[i].mValue = 2;
                break;
            }
        }
        lbl_80309CB4[1].mpUnknown0C = 0;
        lbl_80309CB4[0].mpUnknown0C = 0;
    } else if (event == 4) {
        pObject->mUnknownE8 &= ~1;
        lbl_80309CB4[1].mpUnknown0C = 0;
        lbl_80309CB4[0].mpUnknown0C = 0;
    } else if (pContext->mUnknown17C) {
        Vector_80039F5C position;
        position.mX = pContext->mUnknown168.mX;
        position.mY = pContext->mUnknown168.mY;
        position.mZ = pContext->mUnknown168.mZ;
        if (fn_801784C4()) {
            position.mX = -position.mX;
            position.mY = -position.mY;
        }
        Node_80053674 *pNode = pContext->mpUnknown138;
        pContext->mUnknown17C = 0;
        while (pNode) {
            if (fn_801C2FE4(pNode, (const char *)pContext->mUnknown13C) == 0 && pContext->mUnknown178 != 0) {
                Args_80052F54 args;
                args.mpObject = pObject;
                args.mRef = pContext->mUnknown178;
                args.mKind = 0;
                args.mpNode = pNode;
                if (fn_80052D08(&args) && fn_80053084(&args)) {
                    if (fn_800B65A0(pContext->mUnknown178Bytes[2]) != 255) {
                        Object_80039F5C *pPlayer = fn_8009BCE8(&pContext->mUnknown178);
                        if (fn_801BE648(pPlayer->mpUnknown792) == 228 || fn_801BE648(pPlayer->mpUnknown792) == 229) {
                            fn_80156C78(44, 1);
                        }
                    }
                    if ((unsigned int)(args.mKind - 3) > 1) {
                        fn_8004CBEC(pNode->mpUnknown80, pObject->mpUnknown1D8, pObject, 1.0f);
                        fn_80053258(&args);
                    }
                }
            }
            pNode = pNode->mpNext;
        }
    }
    return 1;
}

void fn_800538E0(Object_80053674 *pObject, Object_80039F5C *pPlayer)
{
    int ref;
    fn_8009BD2C(pPlayer, &ref);
    Node_80053674 *pNode = pObject->mpUnknown1D8->mpUnknown138;
    while (pNode && fn_801C2FE4(pNode, "Obj_Hotspot_Sponsor") != 0) {
        pNode = pNode->mpNext;
    }
    Args_80052F54 args;
    args.mpObject = pObject;
    args.mRef = ref;
    args.mKind = 0;
    args.mpNode = pNode;
    if (fn_80052D08(&args) && fn_80053084(&args)) {
        if (fn_800B65A0(((unsigned char *)&ref)[2]) != 255) {
            if (fn_801BE648(pPlayer->mpUnknown792) == 228 || fn_801BE648(pPlayer->mpUnknown792) == 229) {
                fn_80156C78(44, 1);
            }
        }
        fn_8004CBEC(pNode->mpUnknown80, pObject->mpUnknown1D8, pObject, 1.0f);
        if ((unsigned int)(args.mKind - 3) <= 1) {
            fn_80053554(&args);
        } else {
            fn_80053258(&args);
        }
    }
}

int fn_800539F8(void)
{
    if (lbl_803EA544 == 0) {
        return 0;
    } else {
        lbl_803EA544 = 0;
        return 1;
    }
}

void fn_80053A1C(void)
{
    for (int i = 4; i >= 0; i--) {
        lbl_80309CEC[i].mValue = 2;
    }
    lbl_803EA544 = 0;
    lbl_803EA540 = 0;
    fn_800535FC();
}

void fn_80053A70(Object_80039F5C *pPlayer)
{
    for (int i = 0; i < 15; i++) {
        Args_80052F54 *pArgs = &lbl_80309D14[i];
        if (pArgs->mpObject) {
            if (pArgs->mKind == 3) {
                if (pArgs->mRefBytes[2] == pPlayer->mIdBytes[2]) {
                    fn_80053258(pArgs);
                }
                fn_801C1F94(pArgs, 0, sizeof(*pArgs));
            }
            if (pArgs->mKind == 4 && fn_8009BCE8(&pArgs->mRef) == pPlayer) {
                fn_80053258(pArgs);
                fn_801C1F94(pArgs, 0, sizeof(*pArgs));
            }
        }
    }
}
}
