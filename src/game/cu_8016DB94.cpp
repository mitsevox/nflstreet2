#include <math.h>
#include "game/Class_80297CE8.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_800785C0.h"
#include "game/Object_8017886C.h"
#include "game/Pair_8017055C.h"
#include "game/Record_8011F4F8.h"
#include "game/Record_8011F518.h"
#include "game/Record_800B15FC.h"
#include "game/cu_8003108C.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802372EC.h"
#include "game/cu_80164568.h"
#include "game/fn_80163E94.h"

/* Block returned by fn_801787D0, as declared in src/game/cu_80176F18.cpp. */
struct Info_ScrmState {
    float mUnknown00;
    float mUnknown04;
    float mUnknown08;
    int mUnknown0C;
    int mUnknown10;
    short mUnknown14;
    float mUnknown18;
    int mUnknown1C;
};

/* Player block at +336 as written after fn_800EEE3C: the point and facing it
   returned and two flag bytes. */
struct State_8016DDDC {
    char mUnknown0[8];
    Point_8017886C mPoint;
    int mFacing;
    char mUnknown20[28];
    unsigned char mUnknown48;
    char mUnknown49[1];
    unsigned char mUnknown50;
};

/* Player block at +336 as read for the states checked by fn_8016EC40. */
struct State_8016EC40 {
    char mUnknown0[8];
    int mUnknown8;
    char mUnknown12[7];
    unsigned char mUnknown19;
};

/* First word of the player block at +1160. */
struct Block_8016F7F8 {
    float mUnknown0;
};

extern "C" {
extern float lbl_803ECB08;

int fn_800254E8(Object_800785C0 *pRecord, int a, int b);
int fn_80025708(void);
int fn_8002C9A8(Type_803EA368 *p, int msg, int value);
void fn_80039AA8(void);
Object_80039F5C *fn_80039FE8(int team, int a, unsigned char n);
Object_80039F5C *fn_8003A130(Vector_80039F5C *pPos, float *pOut, int team);
void fn_8003A4DC(void);
void fn_80044264(void);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_8009D888(int index, int value);
unsigned int fn_8009D990(int index);
int fn_8009D9D8(int index);
void fn_8009E0EC(void);
void fn_800A0230(void);
int fn_800A7FD8(void);
void fn_800A8F08(void);
int fn_800A937C(void);
int fn_800A9680(void);
void fn_800AD910(int a, float b);
void fn_800AEEDC(int team);
int fn_800B1200(void);
void fn_800B14E4(void);
void fn_800B2630(void);
unsigned char fn_800B65A0(int team);
void fn_800B6C98(void);
void fn_800B82AC(int team);
int fn_800BA6F8(void);
void fn_800C9FC0(void);
void fn_800CA3C4(void);
void fn_800D0B08(void);
void fn_800DC578(void);
void fn_800EEE3C(Point_8017886C *pOut, int *pFacing, Object_80039F5C *p, int value);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_800FAD2C(void);
void fn_800FAECC(int a);
void fn_800FF6D8(Object_80039F5C *p);
void fn_8010BEA4(void);
void fn_8011875C(void);
void fn_8011DF90(void);
void fn_8011E068(void);
void fn_8011F3A8(void);
void fn_8011F574(void);
void fn_80120618(void);
void fn_80138590(Object_80137ABC *pBall);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_8013F9F8(void);
Camera_8013F738 *fn_8013FA04(int index);
void fn_8013FA8C(int a);
int fn_801486A0(void);
void fn_80162780(int a, int b);
void fn_80164C4C(Object_800670B4 *pObject, Record_80067338 *pRecord, int team, int a);
int fn_801650BC(Record_80067338 *pRecord);
Object_800670B4 *fn_80168708(int team);
void fn_8016B0B0(void);
void fn_80173614(void);
void fn_80173E24(void);
void fn_80176630(void);
int fn_80177F70(void);
int fn_80178308(void);
int fn_80178320(void);
int fn_80178508(void *pPos, float *pOut, int a);
Info_ScrmState *fn_801787D0(void);
int fn_801787DC(int team);
float fn_80178A08(void);
float fn_80178A2C(void);
void fn_8017CFB4(int index);
void fn_8017DA9C(int team);
void fn_801C3E54(Camera_8013F738 *pCamera);
void fn_80067E3C(int type, Vector_80039F5C *pPos, int id, int a, int b, int c);
int fn_800A8408(int team);
int fn_800A8444(int team);
int fn_800A8F84(int team);
void fn_800B1698(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_800D0B90(Object_80039F5C *p);
int fn_800D42CC(void);
void fn_800D45F0(Object_80039F5C *p, float a);
void fn_8011DF90(void);
int fn_8011F1CC(void);
int fn_8011F2C4(void);
void fn_80148154(void);
void fn_801483C8(void);
void fn_80171450(Object_80039F5C *p);
void fn_801726F8(Object_80039F5C *p);
int fn_801729F8(Object_80137ABC *pBall, Pair_8017055C *pPos);
void fn_80177C50(int a);
void fn_80178370(void);
int fn_801783AC(int bit);
void fn_801783D0(int bit, int on);
void fn_80178718(Object_80039F5C *p);
Object_80039F5C *fn_8017876C(void);
int fn_801788D8(unsigned int *pValue);
void fn_8017C858(unsigned short team, int value);
void fn_8017C8B0(unsigned short team, int value);
void fn_8017C8DC(unsigned short team, int value);
void fn_8017C934(unsigned short team, int value);
void fn_8017C960(unsigned short team, int value);
void fn_8016FB10(Object_80039F5C *p, Object_80137ABC *pBall, Pair_8017055C *pOut, int a);
int fn_8016EB50(Object_80039F5C *p, Vector_80039F5C *pPos);
float fn_8016FAB4(void);
int fn_801CFFD0(int a, int b);

void fn_8016DBE4(Object_80039F5C *p);
void fn_8016DF34(Object_80039F5C *p);
void fn_8016E008(int team);
void fn_8016E064(void);
int fn_8016E154(Object_80039F5C *p);
void fn_8016E15C(void);
int fn_8016E928(void);
void fn_8016F6A4(void);
void fn_8016F99C(void);
}

extern "C" void fn_8016DB94(int team)
{
    fn_801647A4(fn_80168708(team), team, lbl_803EB3B0);
    fn_8016E008(team);
    fn_80162780(1, 1);
}

extern "C" void fn_8016DBE4(Object_80039F5C *p)
{
    Message_800F01CC message;
    Message_800F01CC ballMessage;

    fn_801C1F94(&message, 0, 4);
    fn_801C1F94(&ballMessage, 0, 4);
    message.mId = p->mIdBytes[2] == fn_80178308() ? 13 : 14;
    p->mFlags &= ~0x40000;
    ballMessage.mId = 49;
    if (fn_80137C48(p) != 0) {
        if (fn_80137B40() == p) {
            fn_800F053C(0, p->mpState, &ballMessage, p);
            fn_800F03D8(0, p->mpState, &message, p);
        } else {
            fn_8013791C(fn_80137C48(p), 5, 0);
        }
    } else {
        fn_800F053C(0, p->mpState, &message, p);
    }
}

extern "C" void fn_8016DCD4(int team)
{
    unsigned char i;
    unsigned int count;

    if (fn_80177F70() != 0 || fn_800BA6F8() != 0) {
        count = fn_80178D70(team);
        for (i = 0; i < count; i++) {
            Object_80039F5C *p = fn_80039F5C(team, i);
            fn_8016DBE4(p);
            p->mFlags |= 0x10;
        }
    }
    fn_8011DF90();
}

extern "C" int fn_8016DD60(void)
{
    int result = 1;

    if (fn_80177F70() != 0) {
        int team = fn_80178308();
        unsigned char i;
        unsigned int count = fn_80178D70(team);

        for (i = 0; i < count; i++) {
            if ((fn_80039F5C(team, i)->mFlags & 0x40000) == 0) {
                result = 0;
                break;
            }
        }
    }
    return result;
}

extern "C" void fn_8016DDDC(int team)
{
    unsigned char i;
    unsigned int count = fn_80178D70(team);

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
        Point_8017886C point;
        int facing;
        State_8016DDDC *pState;

        switch (p->mpState->mId) {
        case 13:
        case 14:
            fn_800EEE3C(&point, &facing, p, 1);
            pState = (State_8016DDDC *)&p->mUnknown336;
            pState->mPoint.mX = point.mX;
            pState->mPoint.mY = point.mY;
            pState->mFacing = facing;
            pState->mUnknown48 = 0;
            pState->mUnknown50 = 1;
            fn_800FF6D8(p);
            break;
        default:
            if (fn_80137C48(p) != 0 && fn_80137B40() == p) {
                fn_8013791C(fn_80137C48(p), 5, 0);
            }
            fn_800EFE60(0, p->mpState, p);
            fn_8016DBE4(p);
            fn_800EEE3C(&point, &facing, p, 1);
            pState = (State_8016DDDC *)&p->mUnknown336;
            pState->mPoint.mX = point.mX;
            pState->mPoint.mY = point.mY;
            pState->mFacing = facing;
            pState->mUnknown48 = 0;
            pState->mUnknown50 = 1;
            fn_800FF6D8(p);
            break;
        }
        p->mFlags |= 0x40000;
    }
}

extern "C" void fn_8016DF34(Object_80039F5C *p)
{
    if (fn_801486A0() != 0 && fn_801486A0() != 1) {
        if (fn_80178308() == (p->mId >> 8 & 0xFF)) {
            Message_800F01CC message;

            if ((p->mId >> 16 & 0xFF) == 0) {
                fn_801C1F94(&message, 0, 4);
                message.mId = 70;
            } else {
                fn_801C1F94(&message, 0, 4);
                message.mId = 69;
            }
            fn_800F03D8(0, p->mpState, &message, p);
        } else {
            Message_800F01CC message;

            fn_801C1F94(&message, 0, 4);
            message.mId = 42;
            fn_800F03D8(0, p->mpState, &message, p);
        }
    }
}

extern "C" void fn_8016E008(int team)
{
    unsigned char i;
    unsigned int count = fn_80178D70(team);

    for (i = 0; i < count; i++) {
        fn_8016DF34(fn_80039F5C(team, i));
    }
}

extern "C" void fn_8016E064(void)
{
    int team = fn_80178308();
    Point_8017886C pos;
    Record_800B15FC *pRecord;
    Object_80039F5C *p;

    pos = fn_80177FE0();
    pRecord = fn_800B15FC();
    pRecord->mUnknown14 = 3;
    pRecord->mUnknownC = pos.mX;
    pRecord->mUnknown10 = pos.mY;
    pRecord->mUnknown4 = team;
    if (fn_80177F70() != 0) {
        fn_8009BD2C(fn_80039FE8(team, 7, 0), &pRecord->mUnknown0);
        if (pRecord->mUnknown0 == 0) {
            fn_8009BD2C(fn_80039FE8(team, 24, 0), &pRecord->mUnknown0);
        }
    }
    p = fn_8009BCE8(&pRecord->mUnknown0);
    if (p != 0) {
        fn_80067DB8(27, &p->mMotion.mPos, p->mpState->mUnknown2 == 8, 0, 0);
    }
    fn_800B1508();
}

extern "C" int fn_8016E154(Object_80039F5C *p)
{
    return 1;
}

extern "C" void fn_8016E15C(void)
{
    Point_8017886C pos;

    pos = fn_80177FE0();
    if (fn_80177F70() != 0) {
        Message_800F01CC message;
        Object_80137ABC *pBall = fn_801374BC();
        Vector_80039F5C ballPos;
        Object_80039F5C *pCarrier;
        Object_80039F5C *pPasser;
        int offense;
        unsigned char team;

        fn_80137D58(pBall, &ballPos);
        pCarrier = fn_8003A130(&ballPos, 0, fn_80178308());
        fn_80137A04(pBall, pCarrier);
        pPasser = fn_8016444C(fn_80168708(fn_80178308()));
        if (pCarrier->mMotion.mPos.mY - pPasser->mMotion.mPos.mY < 2.5f) {
            fn_801C1F94(&message, 0, 4);
            message.mId = 26;
            message.mUnknown1[0] = pPasser->mIdBytes[1];
            message.mUnknown1[1] = 14;
            message.mUnknown1[2] = 0;
            fn_800F00D4(0, pCarrier->mpState, &message, pCarrier);
        } else {
            fn_801C1F94(&message, 0, 4);
            message.mId = 25;
            message.mUnknown1[0] = pPasser->mIdBytes[1];
            message.mUnknown1[1] = 8;
            fn_800F00D4(0, pCarrier->mpState, &message, pCarrier);
        }
        fn_801C1F94(&message, 0, 4);
        message.mId = 56;
        message.mUnknown1[0] = fn_8016E154(pCarrier);
        fn_800F00D4(0, pPasser->mpState, &message, pPasser);

        offense = fn_80178320();
        for (team = 0; team < 2; team++) {
            unsigned char i;
            unsigned int count = fn_80178D70(team);

            for (i = 0; i < count; i++) {
                Object_80039F5C *p = fn_80039F5C(team, i);

                if (p != pCarrier && p != pPasser && p->mMotion.mUnknown28 < lbl_803ECB08 * 0.1f &&
                    (p->mIdBytes[2] == offense || fabsf(pos.mY - p->mMotion.mPos.mY) < 2.0f ||
                     fabsf(pos.mX - p->mMotion.mPos.mX) > 6.0f)) {
                    float delay = 0.025098039f;

                    delay += fn_802372EC(0, 8) * 0.01f;
                    if (p->mIdBytes[2] == offense) {
                        delay += 0.075f;
                    } else {
                        delay += 0.025f;
                    }
                    fn_801C1F94(&message, 0, 4);
                    message.mId = 51;
                    message.mUnknown1[0] = (int)(delay * 32.0f);
                    fn_800F00D4(0, p->mpState, &message, p);
                }
            }
        }
    }
}

extern "C" void fn_8016E498(void)
{
    int team = fn_80178308();
    unsigned short i = 0;
    int other = fn_80178320();
    Vector_80039F5C ballPos;
    unsigned int count;
    int side;

    fn_8011F574();
    fn_800D0B08();
    fn_80137D58(fn_801374BC(), &ballPos);
    fn_8003A4DC();
    fn_8017CFB4(1);
    fn_8017CFB4(2);
    fn_8017CFB4(0);
    fn_8017DA9C(fn_80178308());
    fn_8017DA9C(fn_80178320());
    fn_800B14E4();
    fn_80044264();
    fn_80067CCC();
    fn_800AD910(3, 0.0f);
    fn_8011F3A8();
    fn_80137C10(0);
    fn_8009E0EC();
    fn_8011875C();
    fn_800FAD2C();
    fn_8016B0B0();
    fn_800FAECC(1);
    fn_80164C4C(fn_80168708(team), fn_8016871C(team), team, 0);
    fn_80164C4C(fn_80168708(other), fn_8016871C(other), other, 0);

    count = fn_80178D70(team);
    for (i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
        unsigned char j;

        for (j = 0; j < 10; j++) {
            if (p->mQueue[j].mId == 18) {
                p->mFlags |= 0x10000000;
                break;
            }
        }
    }

    fn_800AEEDC(0);
    fn_800AEEDC(1);
    fn_800B6C98();
    fn_80173614();
    fn_8016E15C();
    fn_8011E068();
    fn_80039AA8();
    fn_8002C9A8(lbl_803EA368, 1, 0);
    if (fn_800A937C() == 0 && fn_800A9680() == 0) {
        fn_8002C9A8(lbl_803EA368, 2, 0);
        fn_800310C0(lbl_803EA368, 2, 0, &ballPos, 0);
    }
    fn_8016E064();
    fn_80120618();
    fn_800C9FC0();
    fn_800CA3C4();
    if (fn_80025708() != 0 && fn_800785C0()->mUnknown1A4 != 0 && fn_8009D9D8(4) == 0) {
        fn_8009D888(4, 0);
    }
    fn_800B2630();
    fn_80176630();
    fn_80173E24();

    side = fn_80178308();
    fn_80138590(fn_801374BC());
    fn_8010BEA4();
    fn_800DC578();
    if (fn_800B65A0(side) != 0xFF && fn_80177F70() != 0) {
        Camera_8013F738 *pCamera = fn_8013FA04(fn_8013F9F8());
        Record_80067338 *pRecord = fn_8016871C(side);

        if (fn_801650BC(pRecord) == 0 && pRecord->mUnknown14 != 4 && pRecord->mUnknown14 != 2) {
            fn_8013FA8C(2);
            fn_801C3E54(pCamera);
        }
    }
    fn_800B82AC(fn_80178320());
    fn_800A8F08();
    fn_800A0230();
}

extern "C" int fn_8016E764(void)
{
    bool allowed = true;
    int mode = fn_801486A0();
    int result;

    if (mode <= 3) {
        allowed = mode == 2;
    }
    result = 0;
    if (fn_800B65A0(fn_80178308()) != 0xFF) {
        if (fn_8017886C()->mUnknown1D == -2 || fn_8013BA58(fn_801374BC(), 0) == 6 || !allowed) {
            if (fn_8016E928() != 0) {
                result = 1;
            }
        }
    } else if (fn_8017886C()->mUnknown1D == -2 || fn_8013BA58(fn_801374BC(), 0) == 6 || !allowed) {
        Object_800785C0 *pRecord = fn_800785C0();

        if (fn_80025708() != 0 && pRecord->mUnknown1A4 != 0 && fn_800254E8(pRecord, 55, 0) != 0 &&
            fn_801787DC(0) < fn_801787DC(1)) {
            result = 1;
        }
        if (result == 0 && (short)fn_8009D990(0) <= lbl_803EABA4->fn_800C02E0() && fn_800B1200() != 0 &&
            fn_8016E928() != 0) {
            result = 1;
        }
    }
    if (lbl_803EABA4->fn_800C0414() == 1 && fn_8009D990(0) > fn_8009D990(1) &&
        fn_801787DC(fn_80178308()) > fn_801787DC(fn_80178320())) {
        result = 0;
    }
    if (fn_800A7FD8() == 1 || fn_800A937C() != 0) {
        result = 0;
    }
    return result;
}

extern "C" int fn_8016E928(void)
{
    int team = fn_80178308();
    int busy = 0;
    unsigned short moving = 0;
    int blocked = 0;
    unsigned short i;
    unsigned int count = fn_80178D70(team);

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);

        if (p->mFlags & 0x40000) {
            continue;
        }
        switch (p->mUnknown2914) {
        case 0:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 24:
            blocked = 1;
            break;
        default:
            moving++;
            if (p->mMotion.mUnknown44 > lbl_803ECB08 * 0.05f) {
                blocked = 1;
            }
            if (p->mpState->mId == 7) {
                busy = 1;
            }
            break;
        }
    }
    if (fn_800B65A0(0) == 0xFF && fn_800B65A0(1) == 0xFF && fn_8013F9F8() == 3) {
        blocked = 1;
    }
    if (moving > 1 || blocked || busy) {
        return 0;
    }
    return 1;
}

extern "C" int fn_8016EA68(void)
{
    int team = fn_80178308();
    unsigned short i;
    unsigned int count = fn_80178D70(team);

    for (i = 0; i < count; i++) {
        if ((fn_80039F5C(team, i)->mFlags & 0x40000) == 0) {
            return 0;
        }
    }
    return 1;
}

extern "C" int fn_8016EADC(void)
{
    int team = fn_80178308();
    unsigned short i;
    unsigned int count = fn_80178D70(team);

    for (i = 0; i < count; i++) {
        if (fn_80039F5C(team, i)->mFlags & 0x40000) {
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_8016EB50(Object_80039F5C *p, Vector_80039F5C *pPos)
{
    Object_80137ABC *pBall;

    if (fn_80178508(pPos, 0, 0) == 1) {
        return 1;
    }
    if (p->mFlags & 0x800000) {
        return 1;
    }
    pBall = fn_80137C48(p);
    if (pBall != 0) {
        Vector_80039F5C ballPos;

        fn_80137DC8(pBall, &ballPos);
        if (fn_80178508(&ballPos, 0, 0) == 1) {
            pPos->mY = ballPos.mY;
            return 1;
        }
        if (ballPos.mY > fn_80178A2C() && fabsf(pPos->mX) > fn_80178A08() &&
            fn_80178508(&p->mMotion.mPos, 0, 0) == 1) {
            return 1;
        }
    }
    return 0;
}

extern "C" void fn_8016EC40(Object_80039F5C *p)
{
    Object_80039F5C *pOwner = 0;
    float margin = 0.0f;
    unsigned int value = 0;
    int mode = fn_800AD9B4();
    Object_80137ABC *pBall = fn_801374BC();
    Vector_80039F5C ballPos;
    Point_8017886C pos;
    Record_800B15FC *pRecord;

    fn_80137D58(pBall, &ballPos);
    if (mode != 3) {
        return;
    }
    pos = fn_80177FE0();
    if (p != 0 && p->mIdBytes[3] == 1) {
        pOwner = p;
    }
    if (!fn_801783AC(0)) {
        int ref;

        if (fn_801486A0() != 3) {
            margin = 0.3f;
        }
        if (ballPos.mY > pos.mY + margin) {
            int crossed = 1;

            if (p != 0) {
                switch (p->mpState->mId) {
                case 26:
                    if (((State_8016EC40 *)&p->mUnknown336)->mUnknown8 == 14) {
                        crossed = 0;
                    }
                    break;
                case 25:
                    if (fn_8011F518()->mUnknown4 == 8) {
                        crossed = 0;
                    }
                    break;
                }
            }
            if (p != 0 && p->mpState->mId == 15 &&
                fn_8011F4F8(fn_801374E0(fn_801374BC()))->mUnknown1D != 4) {
                crossed = 0;
            }
            if (fn_801486A0() == 0) {
                crossed = 0;
            }
            if (crossed) {
                fn_801783D0(0, 1);
                margin = 4.0f;
                if (ballPos.mX > pos.mX + margin) {
                    fn_801783D0(5, 1);
                }
                if (ballPos.mX < pos.mX - margin) {
                    fn_801783D0(6, 1);
                }
                if (fn_801783AC(4)) {
                    fn_801783D0(4, 0);
                    fn_80177C50(0);
                    fn_8011DF90();
                }
                pRecord = fn_800B15FC();
                fn_8009BD2C(p, &pRecord->mUnknown0);
                pRecord->mUnknownC = ballPos.mX;
                pRecord->mUnknown10 = ballPos.mY;
                pRecord->mUnknown14 = 24;
                fn_800B1508();
                if (p != 0) {
                    fn_8013FA8C(1);
                } else {
                    fn_80148154();
                    fn_801483C8();
                }
            }
        }
        if (!fn_801783AC(7) && ballPos.mX > pos.mX + 4.0f) {
            fn_8009BD2C(p, &ref);
            fn_801783D0(7, 1);
            pRecord = fn_800B15FC();
            pRecord->mUnknown14 = 32;
            pRecord->mUnknown0 = ref;
            pRecord->mUnknownC = ballPos.mX;
            pRecord->mUnknown10 = ballPos.mY;
            pRecord->mUnknown4 = 7;
            fn_800B1508();
        }
        if (!fn_801783AC(8) && ballPos.mX < pos.mX - 4.0f) {
            fn_8009BD2C(p, &ref);
            fn_801783D0(8, 1);
            pRecord = fn_800B15FC();
            pRecord->mUnknown14 = 32;
            pRecord->mUnknown0 = ref;
            pRecord->mUnknownC = ballPos.mX;
            pRecord->mUnknown10 = ballPos.mY;
            pRecord->mUnknown4 = 8;
            fn_800B1508();
        }
    }

    if (p != 0 && fn_8016EB50(p, &ballPos) && fn_801383A0(pBall) == 0) {
        int conversion = 0;

        if (fn_800A8F84(0) == 2 || fn_800A8F84(1) == 2) {
            conversion = 1;
        }
        if ((fn_801486A0() == 4 || fn_801486A0() == 3) && fn_8011F1CC() != 0 && !fn_801783AC(13) &&
            !fn_801783AC(1) && !fn_801783AC(20) && !conversion) {
            return;
        }
        if (fn_80177F70() != 6) {
            unsigned char id = p->mpState->mId;

            if (id == 12) {
                int kind;

                fn_8017C858(p->mIdBytes[2], 1);
                kind = fn_800D0B90(p);
                if (kind != 0) {
                    fn_8017C8DC(p->mIdBytes[2], 1);
                    switch (kind) {
                    case 1:
                        fn_8017C934(p->mIdBytes[2], 1);
                        break;
                    case 4:
                        if (((State_8016EC40 *)&p->mUnknown336)->mUnknown19 != 0) {
                            fn_80067E3C(52, &p->mMotion.mPos, p->mId, 0, 0, 0);
                            fn_8017C960(p->mIdBytes[2], 1);
                        }
                        break;
                    }
                }
            } else if (id >= 34 && id <= 36) {
                if (fn_800D0B90(p) != 0) {
                    fn_8017C8DC(p->mIdBytes[2], 1);
                }
            }
            if (fn_800A8444(p->mIdBytes[2]) != 0 && fn_800A8408(p->mIdBytes[2]) == 0 &&
                fn_800A8F84(p->mIdBytes[2]) == 1) {
                fn_8017C8B0(p->mIdBytes[2], 1);
            }
        }
        fn_801783D0(9, 1);
        fn_80067E3C(95, &ballPos, p->mId, 0, 0, 0);
        switch (fn_801788D8(&value)) {
        case 0:
            if (fn_80177F70() != 6) {
                if (fn_801787DC(p->mIdBytes[2]) + 6 < value) {
                    fn_80067DB8(89, &ballPos, p->mIdBytes[2], 0, 0);
                } else if (!fn_80025708()) {
                    fn_80067DB8(94, &ballPos, p->mIdBytes[2], 0, 0);
                }
            } else {
                if (fn_801787DC(p->mIdBytes[2]) + 2 < value) {
                    fn_80067DB8(90, &ballPos, p->mIdBytes[2], 0, 0);
                } else if (!fn_80025708()) {
                    fn_80067DB8(94, &ballPos, p->mIdBytes[2], 0, 0);
                }
            }
            break;
        case 1:
            if (fn_80177F70() != 6) {
                if (fn_800D42CC() == 2) {
                    fn_80067DB8(89, &ballPos, p->mIdBytes[2], 0, 0);
                }
            } else {
                if (fn_800D42CC() == 2) {
                    fn_80067DB8(90, &ballPos, p->mIdBytes[2], 0, 0);
                }
            }
            break;
        case 2:
            if (fn_801486A0() == 2) {
                fn_80067DB8(89, &ballPos, p->mIdBytes[2], 0, 0);
            }
            break;
        }
        fn_800310C0(lbl_803EA368, 11, p, &p->mMotion.mPos, &p->mMotion.mFacing);
        pRecord = fn_800B15FC();
        fn_8009BD2C(p, &pRecord->mUnknown0);
        pRecord->mUnknownC = ballPos.mX < 0.5f - fn_80178A08()
                                 ? 0.5f - fn_80178A08()
                                 : (ballPos.mX > fn_80178A08() - 0.5f ? fn_80178A08() - 0.5f : ballPos.mX);
        pRecord->mUnknown14 = 22;
        pRecord->mUnknown10 = ballPos.mY;
        fn_8009BD2C(p, &pRecord->mUnknown4);
        fn_800B1508();
        fn_80178370();
    } else {
        Pair_8017055C target;

        fn_8016FB10(p, pBall, &target, 0);
        if (!fn_801729F8(pBall, &target) || p == 0) {
            return;
        }
        if (pOwner->mMotion.mPos.mZ > 0.0f) {
            return;
        }
        if ((pOwner->mFlags & 0x800) &&
            ((pOwner->mFlags & 0x10000) || p->mUnknown560.mUnknown52[1] != 0)) {
            float x;
            float line;

            if (fn_801383A0(pBall) != 0) {
                fn_801726F8(p);
            }
            if (fn_8017876C() == 0) {
                fn_80178718(fn_8009BCE8(&pOwner->mUnknown560.mUnknown48));
            }
            x = p->mMotion.mPos.mX;
            line = fn_8016FAB4();
            if (line > fn_80178A2C()) {
                Object_80039F5C *pOther;
                float clamped = x >= 0.5f - fn_80178A08()
                                    ? (x > fn_80178A08() - 0.5f ? fn_80178A08() - 0.5f : x)
                                    : 0.5f - fn_80178A08();

                fn_801783D0(9, 1);
                fn_80067E3C(95, &ballPos, p->mId, 0, 0, 0);
                switch (fn_801788D8(&value)) {
                case 0:
                    if (fn_80177F70() != 6) {
                        if (fn_801787DC(p->mIdBytes[2]) + 6 < value) {
                            fn_80067DB8(89, &ballPos, p->mIdBytes[2], 0, 0);
                        } else if (!fn_80025708()) {
                            fn_80067DB8(94, &ballPos, p->mIdBytes[2], 0, 0);
                        }
                    } else {
                        if (fn_801787DC(p->mIdBytes[2]) + 2 < value) {
                            fn_80067DB8(90, &ballPos, p->mIdBytes[2], 0, 0);
                        } else if (!fn_80025708()) {
                            fn_80067DB8(94, &ballPos, p->mIdBytes[2], 0, 0);
                        }
                    }
                    break;
                case 1:
                    if (fn_80177F70() != 6) {
                        if (fn_800D42CC() == 2) {
                            fn_80067DB8(89, &ballPos, p->mIdBytes[2], 0, 0);
                        }
                    } else {
                        if (fn_800D42CC() == 2) {
                            fn_80067DB8(90, &ballPos, p->mIdBytes[2], 0, 0);
                        }
                    }
                    break;
                }
                fn_800310C0(lbl_803EA368, 11, p, &p->mMotion.mPos, &p->mMotion.mFacing);
                pOther = fn_8017876C();
                fn_800B1698(p, pOther);
                if (pOther != 0) {
                    fn_800310C0(lbl_803EA368, 7, pOther, &pOther->mMotion.mPos, &pOther->mMotion.mFacing);
                    fn_800310C0(lbl_803EA368, 25, pOther, &pOther->mMotion.mPos, &pOther->mMotion.mFacing);
                }
                fn_800D45F0(p, line);
                fn_800310C0(lbl_803EA368, 6, p, &p->mMotion.mPos, &p->mMotion.mFacing);
                fn_80178370();
            }
            pOwner->mFlags &= ~0x10000;
            fn_80178718(0);
        }
        if (p->mUnknown2914 == 0 || (fn_8011F2C4() != 0 && (p->mUnknown2914 == 1 || p->mUnknown2914 == 3))) {
            if (!(p->mFlags & 0x8000)) {
                Point_8017886C los = pos;

                if (p->mMotion.mPos.mY > los.mY || fabsf(p->mMotion.mPos.mX - los.mX) > 3.0f) {
                    p->mFlags |= 0x8000;
                }
            }
        }
        if (fn_801383A0(pBall) == 4) {
            if (fn_80137F88(pBall) > 20) {
                fn_801726F8(p);
            } else {
                fn_80171450(p);
            }
        } else if (fn_801383A0(pBall) == 1) {
            fn_80171450(p);
        }
    }
}

extern "C" void fn_8016F6A4(void)
{
    Info_ScrmState *pState = fn_801787D0();

    pState->mUnknown00 = 400.0f;
    pState->mUnknown04 = 400.0f;
    pState->mUnknown08 = 400.0f;
    pState->mUnknown10 = 0;
    pState->mUnknown0C = 0;
    pState->mUnknown18 = 400.0f;
    pState->mUnknown14 = -100;
    pState->mUnknown1C = 0;
}

extern "C" void fn_8016F6F4(Object_80039F5C *p, int *pValue)
{
    Info_ScrmState *pState = fn_801787D0();
    Vector_80039F5C ballPos;

    fn_80137D58(fn_801374BC(), &ballPos);
    if (ballPos.mY >= pState->mUnknown00 || pState->mUnknown14 == -100) {
        pState->mUnknown0C = p->mMotion.mFacing;
    }
    pState->mUnknown14 = 0;
    if (pState->mUnknown1C == 0) {
        pState->mUnknown1C = *pValue;
        pState->mUnknown18 = ballPos.mY;
    }
}

extern "C" void fn_8016F780(void)
{
    int mode = fn_800AD9B4();
    Info_ScrmState *pState = fn_801787D0();

    if (mode == 3) {
        Object_80039F5C *p = fn_80137B40();

        if (p != 0 && p->mIdBytes[3] == 1 && p->mUnknown512.mUnknown14 != 0 &&
            fn_801CFFD0(p->mUnknown512.mUnknown4, 0x400000) > 0x400000) {
            fn_8016F99C();
        }
    }
}

extern "C" void fn_8016F7F8(void)
{
    int mode = fn_800AD9B4();
    Info_ScrmState *pState = fn_801787D0();
    Object_80137ABC *pBall = fn_801374BC();
    Vector_80039F5C ballPos;
    Object_80039F5C *p;

    fn_80137D58(pBall, &ballPos);
    p = fn_80137AD0(pBall);
    if (mode == 3) {
        if (p != 0) {
            if (p->mId == pState->mUnknown10) {
                if (pState->mUnknown14 != -100) {
                    pState->mUnknown14++;
                }
                pState->mUnknown04 = ballPos.mY;
                if (fabsf(ballPos.mX) > fn_80178A08() && ballPos.mY < fn_80178A2C()) {
                    if (pState->mUnknown08 == 400.0f) {
                        pState->mUnknown08 = ballPos.mY;
                    }
                    pState->mUnknown04 = pState->mUnknown04 > pState->mUnknown08 ? pState->mUnknown08
                                                                               : pState->mUnknown04;
                } else {
                    pState->mUnknown08 = 400.0f;
                }
                if (((Block_8016F7F8 *)&p->mUnknown1160)->mUnknown0 != 0.0f || (p->mFlags & 0x10000)) {
                    if (pState->mUnknown04 > pState->mUnknown00) {
                        fn_8016F99C();
                    }
                } else if (pState->mUnknown14 == -100 || pState->mUnknown14 > 5) {
                    fn_8016F99C();
                } else {
                    pState->mUnknown00 = pState->mUnknown04;
                }
            } else {
                fn_8016F6A4();
                pState->mUnknown10 = p->mId;
                pState->mUnknown00 = pState->mUnknown04 = ballPos.mY;
                pState->mUnknown1C = 0;
                pState->mUnknown18 = 400.0f;
            }
        } else if (pState->mUnknown10 != 0) {
            fn_8016F6A4();
        }
    }
}

extern "C" void fn_8016F99C(void)
{
    Info_ScrmState *pState = fn_801787D0();
    Object_80137ABC *pBall = fn_801374BC();
    Vector_80039F5C ballPos;
    Object_80039F5C *p;

    fn_80137D58(pBall, &ballPos);
    p = fn_80137AD0(pBall);
    if (fabsf(ballPos.mX) > fn_80178A08() && ballPos.mY > fn_80178A2C()) {
        pState->mUnknown00 = fn_80178A2C() - 0.33f;
        pState->mUnknown08 = 400.0f;
    } else {
        pState->mUnknown00 = ballPos.mY;
        if (fabsf(ballPos.mX) > fn_80178A08()) {
            if (pState->mUnknown08 == 400.0f) {
                pState->mUnknown08 = ballPos.mY;
            }
            pState->mUnknown00 = pState->mUnknown00 > pState->mUnknown08 ? pState->mUnknown08
                                                                       : pState->mUnknown00;
        } else {
            pState->mUnknown08 = 400.0f;
        }
    }
    pState->mUnknown0C = p->mMotion.mFacing;
    pState->mUnknown14 = -100;
}

extern "C" float fn_8016FAB4(void)
{
    return fn_801787D0()->mUnknown00;
}

extern "C" int fn_8016FAD8(float *pOut)
{
    Info_ScrmState *pState = fn_801787D0();

    *pOut = pState->mUnknown18;
    return pState->mUnknown1C;
}
