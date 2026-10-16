#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/Record_800B15FC.h"
#include "game/fn_800F06F4.h"
#include "game/fn_801C1F94.h"
#include "game/cu_80136B1C.h"

struct State_802A2020 {
    char mUnknown0[4];
    unsigned char mUnknown4;
};

struct State_802A1F90 {
    char mUnknown0[4];
    Object_80039F5C *mpUnknown4;
    Object_80039F5C *mpUnknown8;
    unsigned char mUnknown12;
};

struct Record_8014F104 {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
    char mUnknown12[40];
    char mUnknown52[4];
};

struct Block_8014F104 {
    char mUnknown0[0x24];
    unsigned char mUnknown24;
    char mUnknown25[15];
    Record_8014F104 *mpUnknown34;
    unsigned int mUnknown38;
    Object_80039F5C *mpUnknown3C;
};

extern "C" {
extern Object_80039F5C *lbl_803EB2E0;
extern int lbl_803EB2DC;
extern int lbl_803EB2D8;

Block_8014F104 *fn_8014F104(Class_80148A58 *p);
Object_80039F5C *fn_8003AC84(int id);
void fn_800A042C(void *p);
void fn_800A050C(void *p, float dt);
void fn_8003AB08(Object_80039F5C *p, int a);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
void fn_8017D844(const char *pText);
void fn_801477F0(Block_80170E64 *p);
void fn_800F0490(int a, State_80039F5C *pQueue, int id);
void fn_800F0278(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p,
                 unsigned char position);
void fn_80120618(void);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_800D6F08(void);
void fn_800B14E4(void);
int fn_801787A0(void);
int fn_80178508(void *pPos, float *pOut, int a);
void fn_801783D0(int bit, int on);
void fn_80178370(void);
void fn_80171824(Object_80039F5C *p);
void fn_8014D210(Object_80039F5C *p, int a, int b);
int fn_8009D990(int index);
void fn_80177C44(int value);
void fn_8014D948(void *p);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
void fn_8014F4D8(Class_80148A58 *p, Object_80039F5C *pPlayer, int kind, int value);
void fn_8009D8CC(int index);
int fn_801783AC(int bit);
unsigned int fn_802372EC(int a, int b);
float fn_8022785C(Vector_80039F5C *pPos, Vector_80039F5C *pOther);
void fn_800655B8(void);
int fn_8005BE5C(int value);
void fn_800B9654(void *p, float dt);
void fn_800B9998(void *p);
void fn_801488D4(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_8003A450(void);
void fn_8014D67C(void);
void fn_8005BF5C(void);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
int fn_8005BFD4(void);
void fn_800AD910(int a, float b);
void fn_80173B8C(void);

void fn_8014E534(State_802A2020 *p)
{
    p->mUnknown4 = 0;
    fn_800A042C(p);
    Object_80039F5C *pPlayer = fn_80039F5C(1, 0);
    fn_8003AB08(pPlayer, 0);
    if (fn_800F06F4(0, pPlayer->mpState, 1, 0xFFFF) == 0xFFFF) {
        Message_800F01CC message;
        if (fn_8014F104(fn_80148A58())->mUnknown24) {
            fn_801C1F94(&message, 0, 4);
            message.mId = 51;
            message.mUnknown1[0] = 16;
            fn_800F053C(0, pPlayer->mpState, &message, pPlayer);
            fn_801C1F94(&message, 0, 4);
            message.mId = 1;
            fn_800F01CC(0, pPlayer->mpState, &message, pPlayer);
        } else {
            fn_801C1F94(&message, 0, 4);
            message.mId = 1;
            fn_800F03D8(0, pPlayer->mpState, &message, pPlayer);
        }
    }
    char text[64];
    fn_801C2D88(text, 64, "Catch %s %s", pPlayer->mUnknown2927, pPlayer->mUnknown2927 + 21);
    fn_8017D844(text);
    fn_801477F0(pPlayer->mpUnknown4);
    for (unsigned char i = 0; i <= 4; i++) {
        Object_80039F5C *pOther = fn_80039F5C(0, i);
        int position = fn_800F06F4(0, pOther->mpState, 97, 0xFFFF);
        fn_8003AB08(pOther, 0);
        fn_800F0490(0, pOther->mpState, 51);
        fn_800F0490(0, pOther->mpState, 2);
        fn_800F0490(0, pOther->mpState, 97);
        Message_800F01CC message;
        fn_801C1F94(&message, 0, 4);
        message.mId = 51;
        if (fn_8014F104(fn_80148A58())->mUnknown24) {
            message.mUnknown1[0] = 48;
        } else {
            message.mUnknown1[0] = 32;
        }
        if (position == 0xFFFF) {
            fn_800F03D8(0, pOther->mpState, &message, pOther);
            fn_801C1F94(&message, 0, 4);
            message.mId = 97;
            fn_800F03D8(0, pOther->mpState, &message, pOther);
        } else {
            fn_800F0278(0, pOther->mpState, &message, pOther, position);
            fn_801C1F94(&message, 0, 4);
            message.mId = 97;
            fn_800F0278(0, pOther->mpState, &message, pOther, position + 1);
        }
    }
    fn_80120618();
}

void fn_8014E7D4(State_802A2020 *p, float dt)
{
    Vector_80039F5C pos;
    Object_80039F5C *pCarrier = fn_80137B40();
    if (pCarrier) {
        if (!p->mUnknown4) {
            p->mUnknown4 = 1;
            fn_80137D58(fn_801374BC(), &pos);
            Record_800B15FC *pRecord = fn_800B15FC();
            pRecord->mUnknown14 = 3;
            pRecord->mUnknownC = pos.mX;
            pRecord->mUnknown10 = pos.mY;
            pRecord->mUnknown4 = 1;
            fn_800B1508();
            pRecord = fn_800B15FC();
            pRecord->mUnknownC = pos.mX;
            pRecord->mUnknown10 = pos.mY;
            fn_8009BD2C(pCarrier, &pRecord->mUnknown0);
            pRecord->mUnknown14 = 4;
            fn_800B1508();
        }
    } else if (p->mUnknown4) {
        p->mUnknown4 = 0;
        fn_800D6F08();
    }
    fn_800A050C(p, dt);
    fn_800B14E4();
    if (fn_801787A0() == 0) {
        fn_80137D58(fn_801374BC(), &pos);
        if (pCarrier) {
            if (fn_80178508(&pCarrier->mMotion, 0, 0) > 2) {
                fn_801783D0(3, 1);
                fn_80178370();
                fn_800D6F08();
            } else if ((pCarrier->mFlags & 0x800) &&
                       (pCarrier->mpState->mId == 10 || pCarrier->mpState->mId == 16 ||
                        pCarrier->mpState->mId == 25)) {
                fn_80171824(pCarrier);
            } else {
                fn_8014D210(pCarrier, 130, 10);
            }
        } else if (fn_80178508(&pos, 0, 0) > 2) {
            fn_801783D0(3, 1);
            fn_80178370();
        }
        if (!fn_8009D990(1)) {
            fn_80177C44(1);
            fn_80178370();
            fn_800D6F08();
        }
    }
    fn_80148A58()->vfn_15();
    fn_8014D948(p);
    if (fn_8013BA58(fn_801374BC(), 0) == 1 && !lbl_803EB2E0) {
        int time = fn_8009D990(1);
        lbl_803EB2E0 = fn_80137B40();
        lbl_803EB2DC = time;
    } else if (fn_8013BA58(fn_801374BC(), 0) != 1 && lbl_803EB2E0) {
        unsigned int time = lbl_803EB2DC - fn_8009D990(1);
        Object_80039F5C *pPlayer = lbl_803EB2E0;
        fn_8014F4D8(fn_80148A58(), pPlayer, 8, time);
        fn_8014F4D8(fn_80148A58(), pPlayer, 7, 1);
        if (time > fn_8014F104(fn_80148A58())->mUnknown38) {
            fn_8014F104(fn_80148A58())->mUnknown38 = time;
            fn_8014F104(fn_80148A58())->mpUnknown3C = pPlayer;
        }
        lbl_803EB2DC = 0;
        lbl_803EB2E0 = 0;
    }
}

void fn_8014EA90(State_802A1F90 *p, float dt)
{
    Object_80039F5C *pPlayer = fn_80039F5C(1, 0);
    p->mpUnknown4 = fn_80137B40();
    p->mUnknown12 = 0;
    fn_8009D8CC(1);
    if (fn_8009D990(1)) {
        if (fn_801783AC(3)) {
            unsigned int best = 0xFFFFFFFF;
            p->mUnknown12 = 1;
            for (unsigned short i = 0; i <= 5; i++) {
                Object_80039F5C *pOther = fn_8003AC84(fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown0);
                unsigned int value = fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown4;
                if (pOther != pPlayer && (value < best || (value == best && fn_802372EC(0, 100) > 50))) {
                    p->mpUnknown4 = pOther;
                    best = value;
                }
            }
        } else if (!p->mpUnknown4 || pPlayer == p->mpUnknown4) {
            p->mUnknown12 = 1;
            p->mpUnknown4 = p->mpUnknown8;
            if (!p->mpUnknown8) {
                Vector_80039F5C pos;
                fn_80137D58(fn_801374BC(), &pos);
                float best = 3.4028235e38f;
                for (unsigned short i = 0; i <= 4; i++) {
                    Object_80039F5C *pOther = fn_80039F5C(0, i);
                    float distance = fn_8022785C(&pOther->mMotion.mPos, &pos);
                    if (distance < best) {
                        p->mpUnknown4 = pOther;
                        best = distance;
                    }
                }
            }
        } else if (fn_801783AC(3)) {
            p->mUnknown12 = 1;
        }
        if (!fn_8009D990(1)) {
            p->mUnknown12 = 0;
        }
        if (p->mUnknown12) {
            fn_800655B8();
            fn_8005BE5C(2);
        }
    }
    fn_800B9654(p, dt);
}

void fn_8014EC74(State_802A1F90 *p)
{
    fn_800B9998(p);
    if (fn_8009D990(1)) {
        fn_801488D4(fn_80039F5C(1, 0), p->mpUnknown4);
        if (p->mUnknown12) {
            fn_8003A450();
            fn_8014D67C();
            fn_8005BF5C();
        }
    } else {
        fn_8003A450();
        for (unsigned int team = 0; team <= 1; team++) {
            for (unsigned int i = 0; i <= 6; i++) {
                Object_80039F5C *pPlayer = fn_80039F5C((unsigned char)team, i);
                fn_800EFE60(0, pPlayer->mpState, pPlayer);
            }
        }
    }
    p->mpUnknown8 = 0;
}

int fn_8014ED30(State_802A1F90 *p)
{
    if (!p->mUnknown12 || fn_8005BFD4() == 1) {
        return 1;
    }
    return 0;
}

void fn_8014ED70(void *p, float dt)
{
    if (fn_8009D990(1)) {
        fn_800AD910(2, dt);
    } else {
        fn_80173B8C();
    }
}

int fn_8014EDBC(void)
{
    return lbl_803EB2D8;
}
}
