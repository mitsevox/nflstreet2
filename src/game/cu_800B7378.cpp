#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Input_800B6D34.h"
#include "game/cu_80136B1C.h"
#include "game/fn_801FCE10.h"
#include "game/fn_8022781C.h"
#include "game/Class_80297BF8.h"
#include "game/Class_80297C60.h"
#include "game/Step_800C4460.h"
#include "game/cu_8002B8F8.h"
#include "game/cu_8003108C.h"
#include "game/cu_80064864.h"
#include "game/cu_80067C10.h"
#include "game/InGame.h"
#include <string.h>

/* Local views matching the definitions in cu_8008E978.cpp. */
struct Entry_800B5224 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2[2];
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9[3];
};

struct Block_800B62D8 {
    Entry_800B5224 *mpEntries;
    unsigned char mCount;
    unsigned char mUnknown5;
    unsigned char mUnknown6[2];
    unsigned char mUnknown8[10];
    unsigned char mUnknown12[10];
};

struct Sequence_800C4460 {
    Step_800C4460 mSteps[8];
    unsigned char mUnknown100;
    unsigned char mUnknown101;
    unsigned char mUnknown102[2];
};

struct Block_800B95B4 {
    Sequence_800C4460 mSequence;
    Object_8017886C mUnknown104;
    Object_8017886C mUnknown124;
    unsigned int mUnknown144;
    unsigned char mUnknown148;
    unsigned char mUnknown149[3];
    int mUnknown14C;
    unsigned char mUnknown150;
    unsigned char mUnknown151;
    unsigned char mUnknown152[2];
    int mUnknown154;
    unsigned char mUnknown158;
    unsigned char mUnknown159[3];
    int mUnknown15C;
    unsigned char mUnknown160;
    unsigned char mUnknown161[3];
    int mUnknown164;
};

struct Desc_802345C4 {
    int mUnknown0;
    int mUnknown4;
};

extern "C" {
int fn_8002C9A8(Type_803EA368 *p, int msg, int value);
int fn_8002CA74(Type_803EA368 *p, int msg, int value);
unsigned char fn_8002D060(Type_803EA368 *p);
int fn_8002D0AC(Type_803EA368 *p);
int fn_8002D228(Type_803EA368 *p);
void fn_8002D2C8(Type_803EA368 *p, unsigned char value);
int fn_80065864(void);
void fn_80076160(void);
void fn_80094DF0(void);
int fn_8009A6EC(Object_80039F5C *p);
void fn_8009B924(void);
int fn_8009B9A8(int a);
int fn_8009B9BC(void);
void fn_8009BA10(int value);
void fn_8009FF94(unsigned int value);
void fn_8009FFB4(unsigned int value);
void fn_800A1FEC(Object_8017886C *result, Object_8017886C *value);
void fn_800AE9A4(void);
void fn_800AE9EC(void);
void fn_800AFDD4(void (*pCallback)(int, unsigned int, float));
int fn_800B51D0(Object_80039F5C *p);
void fn_800B6474(int index, unsigned char value);
void fn_800B64C4(void);
int fn_800B6644(int index);
void fn_800B6988(int index);
void fn_800B6E68(Object_80039F5C *p, Input_800B6D34 *pInput);
int fn_800B7248(Input_800B6D34 *pInput, Object_80137ABC *pBall, Object_80039F5C *p, Object_80039F5C *pTarget);
int fn_800B7370(Object_80039F5C *p, Input_800B6D34 *pInput);
void fn_800B86A4(int index);
void *fn_800B9A44(Class_80297C60 *p);
void fn_800B9A6C(Class_80297C60 *p, void *q);
int fn_800B9B18(void *p);
void fn_800B24C8(void);
int fn_800BA6F8(void);
void fn_800BAAC4(void);
void fn_800BD184(Class_80297BF8 *p, int value);
void fn_800C4438(Sequence_800C4460 *p);
void fn_800C4460(Sequence_800C4460 *p);
int fn_800C8704(int *pA, int *pB);
void fn_800C9FC0(void);
int fn_800CA5CC(Object_80039F5C *p, int kind, int value);
void fn_800D42D4(void);
void fn_800D45A0(void);
void fn_800D4858(void);
void fn_800D4888(int flag);
void fn_800D490C(void);
void fn_800D49A4(void);
void fn_800D49FC(void);
void fn_800D4A40(void);
int fn_800E1350(Object_80039F5C *p);
int fn_800E815C(Object_80039F5C *p, int a, int b);
void fn_800F181C(int index, int value);
int fn_800F2C1C(Object_80039F5C *p, int a);
int fn_801133FC(Object_80039F5C *p, int a, int b);
int fn_8011F1CC(void);
int fn_80125510(Object_80039F5C *p, int a);
int fn_8013BA58(Object_80137ABC *p, int *pOut);
void fn_8013F3FC(void);
unsigned char fn_801478F0(unsigned char a);
void fn_80148154(void);
void fn_801483C8(void);
int fn_801486A0(void);
int fn_801520C4(Object_80039F5C *p, unsigned char *pIndex);
void fn_8016DA98(Object_80039F5C *p);
void fn_80173D10(void);
unsigned int fn_801735C8(unsigned int mask);
int fn_80177C38(void);
int fn_80177F70(void);
int fn_801783AC(int bit);
void fn_801783D0(int bit, int on);
void fn_801789F8(void);
int fn_80179138(void);
void fn_8017CFB4(int index);
int fn_8017D064(int a);
void fn_8017D7C4(const char *pText);
void fn_8017F2A4(void);
unsigned char fn_8017F2DC(unsigned char value);
unsigned char fn_8017F324(unsigned char value);
unsigned char fn_8017F394(void);
unsigned char fn_8017F48C(void);
int fn_801BE648(void *p);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
float fn_8022710C(void *pV);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_8022E558(void);
void fn_802345C4(Desc_802345C4 *pDesc, int count);

extern unsigned char lbl_803EAB64;
extern unsigned char lbl_803EAB65;
extern short lbl_803EAB66;
extern short lbl_803EAB68;
extern short lbl_803EAB6A;
extern short lbl_803EAB6C;
extern Block_800B62D8 *lbl_803EAB60;
extern Block_800B95B4 *lbl_803EAB78;
extern unsigned char lbl_803EAB7C;
extern unsigned char lbl_803EAB7D;
extern unsigned char lbl_803EAB7E;
extern int lbl_803EAB80;
extern float lbl_803ECB08;
}

extern "C" int fn_800B7378(Object_80039F5C *p)
{
    int result = 0;
    int minAngle = (int)(lbl_803EAB64 * 46603.379f);
    int maxAngle = (int)(lbl_803EAB65 * 46603.379f);
    Object_80039F5C *pCarrier = fn_80137B40();
    int angleSlack;
    int rangeSlack;
    Vector_80039F5C delta;
    int angle;
    float distance;

    if (p != 0 && pCarrier != 0 && pCarrier->mMotion.mUnknown28 / lbl_803ECB08 > 0.14f) {
        if ((unsigned int)(p->mUnknown528.mUnknown15 - 4) <= 1) {
            angleSlack = (int)(lbl_803EAB6A * 46603.379f);
        } else {
            angleSlack = 0;
        }
        rangeSlack = (unsigned int)(p->mUnknown528.mUnknown15 - 4) <= 1 ? lbl_803EAB6C : 0;
        if (pCarrier != 0 && fn_801BE648(pCarrier->mpUnknown792) != 0x54
            && fn_801BE648(pCarrier->mpUnknown792) != 0x45 && fn_801BE648(pCarrier->mpUnknown792) != 0xB2
            && fn_801BE648(pCarrier->mpUnknown792) != 0x4D && (unsigned int)pCarrier->mMotion.mFacing <= 0x800000) {
            fn_80227690(&delta, &p->mMotion, &pCarrier->mMotion);
            angle = fn_801CFE40(delta.mY, delta.mX);
            if (fn_801CFFD0(pCarrier->mMotion.mFacing, 0) <= 0x3FFFFF) {
                minAngle = (int)(minAngle - fn_801CFB94(pCarrier->mMotion.mFacing) * 699050.0f);
                maxAngle = (int)(maxAngle - fn_801CFB94(pCarrier->mMotion.mFacing) * 1398101.0f);
            } else {
                minAngle = (int)(minAngle - fn_801CFB94(pCarrier->mMotion.mFacing) * 1398101.0f);
                maxAngle = (int)(maxAngle - fn_801CFB94(pCarrier->mMotion.mFacing) * 699050.0f);
            }
            distance = fn_8022710C(&delta);
            if (angle >= minAngle - angleSlack && angle <= maxAngle + angleSlack
                && distance >= lbl_803EAB66 - rangeSlack && distance <= lbl_803EAB68 + rangeSlack) {
                result = 1;
            }
        }
    }
    return result;
}

extern "C" int fn_800B78DC(Object_80039F5C *p)
{
    unsigned char index = 0;
    Object_80137ABC *pBall;
    Object_80039F5C *pCarrier;
    Input_800B6D34 input;
    int state;

    if (fn_801486A0() == 1 && fn_801520C4(p, &index) != 0) {
        pBall = fn_80137ABC(index);
    } else {
        index = fn_801374D4();
        pBall = fn_801374BC();
    }
    fn_800B6D34(p, &input);
    if (fn_800B7378(p) != 0) {
        p->mUnknown512.mUnknown15 = 4;
    }
    if (input.mUnknown95 & 8) {
        p->mFlags |= 0x4000;
        if (fn_800CA5CC(p, 0, 1) != 0) {
            p->mUnknown512.mUnknown15 = 1;
            fn_8016DA98(p);
        }
    }
    if (input.mUnknown92 & 1) {
        int loose = 0;
        int dive = 0;

        if ((fn_801783AC(11) != 0 || fn_801783AC(12) != 0) && fn_8013BA58(pBall, 0) == 4
            && fn_80137AD0(pBall) == 0) {
            loose = 1;
        }
        if ((input.mUnknown96 & 1) && p->mUnknown1032 != 4 && p->mUnknown1032 != 6) {
            dive = 1;
        }
        if (loose || !dive) {
            if (fn_8013BA58(pBall, 0) == 4 && fn_800B51D0(p) != 0 && fn_801133FC(p, 1, 1) != 0) {
                goto handled;
            }
            if (!dive ? fn_800E815C(p, 0, 0) : fn_800E1350(p)) {
                goto handled;
            }
        } else if (fn_800E1350(p) != 0) {
            goto handled;
        }
    }
    if (input.mUnknown92 & 4) {
        int pass = 0;

        state = fn_8013BA58(pBall, 0);
        switch (state) {
        case 1:
            pCarrier = fn_80137AD0(pBall);
            if (pCarrier->mpState->mId == 15) {
                pass = fn_8022781C(&pCarrier->mMotion, &p->mMotion) > 5.0f;
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            pass = state >= 3;
            break;
        }
        if (pass) {
            int mode = 1;

            if ((input.mUnknown96 & 1) ? fn_8009A6EC(p) : (input.mUnknown96 & 0x10)) {
                mode = 3;
            }
            if (fn_801133FC(p, mode, 0) != 0) {
                goto handled;
            }
        } else {
            if (fn_8011F1CC() != 0) {
                pCarrier = fn_80137AD0(pBall);
                if (pCarrier != 0 && (pCarrier->mpState->mId == 18 || pCarrier->mpState->mId == 15)) {
                    fn_8022781C(&pCarrier->mMotion, &p->mMotion);
                }
            }
            if (fn_800F2C1C(p, 0) != 0) {
                goto handled;
            }
        }
    }
    if (fn_800B7248(&input, pBall, p, p) != 0) {
        return 0;
    }
    if ((input.mUnknown93 & 0x20)
        && (fn_8013BA58(pBall, 0) == 5 || fn_801486A0() == 0 || fn_801486A0() == 1 || fn_801486A0() == 2)
        && fn_80125510(p, 0) != 0) {
    handled:
        p->mFlags |= 0x4000;
        return 0;
    }
    if (input.mUnknown93 & 0x10) {
        fn_800B6988(p->mUnknown8);
    } else {
        if (fn_800B7370(p, &input) != 0) {
            return 0;
        }
        fn_800B6E68(p, &input);
    }
    return 0;
}

extern "C" void fn_800B8028(void)
{
    QueryCursor cursor = { 0, 0, -1, 0 };
    int current;
    int i;

    for (i = 0; i < lbl_803EAB60->mCount; i++) {
        lbl_803EAB60->mpEntries[i].mUnknown0 = 0xFF;
        lbl_803EAB60->mpEntries[i].mUnknown1 = 0xFF;
        lbl_803EAB60->mpEntries[i].mUnknown4 = 0;
        lbl_803EAB60->mpEntries[i].mUnknown8 = 0;
    }
    lbl_803EAB60->mUnknown6[0] = 0xFF;
    lbl_803EAB60->mUnknown6[1] = 0xFF;
    current = fn_8022E558();
    if (fn_801FCE10(0, "declare \x8a cursor for select * from 'OCMT'\n", &cursor) == 0) {
        int id;
        int slot;
        int team;

        while (fn_801FCE10(0, "fetch from \x8a 'UNLS' into \x82 and 'digl' into \x82\n", &cursor, &id, &slot) == 0) {
            if (fn_801FCE10(0, "select 'DIGT' into \x82 from 'MTTS' where 'UNLS' = \x82\n", &team, id) != 0) {
                break;
            }
            fn_800B6474((unsigned char)slot, team != current);
            fn_800F181C((unsigned char)slot, 0);
        }
    }
    if (cursor.mUnknown0 != 0) {
        fn_801FCFA0(&cursor);
    }
    fn_800B64C4();
}

extern "C" void fn_800B8494(int value)
{
    int a;
    int b;
    int resultA;
    int resultB;

    fn_800C8704(&a, &b);
    fn_801FCE10(0, "select 'DIOT' into \x82 from 'MTTS' where 'DIGT' = \x82\n", &resultA, a);
    fn_801FCE10(0, "select 'DIOT' into \x82 from 'MTTS' where 'DIGT' = \x82\n", &resultB, b);
    if (resultA == resultB) {
        fn_800BD184(lbl_803EAB90, value);
        fn_8013F3FC();
    } else {
        fn_800BD184(lbl_803EAB90, value);
    }
}

extern "C" void fn_800B876C(int index, unsigned int event, float value)
{
    if (fn_801486A0() == 0) {
        return;
    }
    switch (event) {
    case 0:
    case 6:
    case 7:
    case 8:
    case 14:
    case 15:
        if (fn_8009B9A8(0) != 0 && value == 1.0f) {
            fn_800B86A4(index);
        }
        break;
    case 9:
        if (lbl_803EAB78->mUnknown151 != 0 && fn_8009B9BC() == 0 && fn_8002D060(lbl_803EA368) == 0
            && fn_8002892C() == 0 && fn_80028934() == 0 && fn_8017F48C() == 0 && fn_80065864() == 0
            && fn_800655F8() == 1 && (fn_800B6644(index) == 0 || fn_800B6644(index) == 1)) {
            fn_8002C9A8(lbl_803EA368, 3, 0);
            if (fn_8002D228(lbl_803EA368) != 0) {
                fn_8009BA10(0);
                fn_8009B924();
                fn_80094DF0();
                fn_8002D2C8(lbl_803EA368, 1);
                while (fn_8017D064(7) != 0) {
                    fn_8017CFB4(7);
                }
                if (fn_8017F394() != 0) {
                    fn_8017F2A4();
                    fn_8017F324(1);
                    fn_8017F2DC(2);
                }
                fn_8002CA74(lbl_803EA368, 10, index);
                fn_8002CA74(lbl_803EA368, 11, 0);
                fn_8002CA74(lbl_803EA368, 7, 0);
            }
        }
        break;
    }
}

extern "C" int fn_800B89C8(void *pData)
{
    Step_800C4460 *pStep;

    if (fn_800B9B18(lbl_803EAB84) != 0) {
        return 0;
    }
    pStep = *(Step_800C4460 **)pData;
    if (lbl_803EAB78->mUnknown150 != 0) {
        pStep->mUnknownC = pStep->mUnknownC <= 180.0f ? pStep->mUnknownC : 180.0f;
    }
    return 1;
}

extern "C" int fn_800B8E18(void *p, char *pText)
{
    char firstDown[] = "1st Down";
    char turnover[] = "Turnover On Downs";
    char safety[] = "Safety";
    char onePoint[] = "1 Pt. Conversion";
    char twoPoint[] = "2 Pt. Conversion";
    char defensive[] = "Defensive Conversion";
    char failed[] = "Conversion Failed";
    char touchdown[] = "Touchdown";
    char touchdown2[] = "Touchdown";
    char touchback[] = "Touchback";
    int changed = 0;
    int pending = fn_8017D064(3);
    int score = lbl_803EAB78->mUnknown104.mUnknown1D;
    int state = fn_80177F70();

    if (pending == 0 && fn_801735C8(0x200) == 0) {
        if (lbl_803EAB78->mUnknown104.mUnknown04 == 1) {
            if (state == 6) {
                if (score == 0) {
                    strcpy(pText, failed);
                    changed = 1;
                }
            } else {
                if (lbl_803EAB78->mUnknown104.mUnknown18 & 0x40) {
                    if (!(lbl_803EAB78->mUnknown104.mUnknown18 & 0x40000) && (fn_80177C38() & 1) == 0
                        && fn_801486A0() != 2) {
                        strcpy(pText, firstDown);
                        changed = 1;
                    }
                }
                if (lbl_803EAB78->mUnknown104.mUnknown18 & 0x800) {
                    strcpy(pText, turnover);
                    changed = 1;
                    fn_80173D10();
                }
            }
        } else if (lbl_803EAB78->mUnknown104.mUnknown18 & 0x20000) {
            changed = 1;
            strcpy(pText, "Out Of Bounds");
        } else if (lbl_803EAB78->mUnknown104.mUnknown04 == 4) {
            changed = 1;
            strcpy(pText, "4th Down");
        }
        if (lbl_803EAB78->mUnknown104.mUnknown18 & 0x100) {
            if (state == 6 && score == 0) {
                strcpy(pText, failed);
                changed = 1;
            } else {
                strcpy(pText, touchback);
                changed = 1;
            }
        }
    }
    if (score != 0) {
        if (score == -2) {
            strcpy(pText, safety);
            changed = 1;
        } else if (score == 6 || score == 9) {
            fn_800D42D4();
            if (fn_80177C38() == 1 && fn_801783AC(20)) {
                strcpy(pText, touchdown2);
                changed = 1;
            } else {
                strcpy(pText, touchdown);
                changed = 1;
            }
        } else if (score == 2) {
            if (fn_80177C38() == 1 || fn_80177C38() == 3) {
                strcpy(pText, defensive);
            } else if (fn_80179138() == 1) {
                strcpy(pText, onePoint);
            } else {
                strcpy(pText, twoPoint);
            }
            changed = 1;
        }
    } else if (lbl_803EAB78->mUnknown104.mUnknown18 & 0x4000) {
        changed = 1;
        strcpy(pText, "No Good");
    }
    return changed;
}

extern "C" void fn_800B925C(void *p, char *pText)
{
    char firstDown[] = "1st Down";
    char turnover[] = "Turnover On Downs";
    char safety[] = "Safety";
    char onePoint[] = "1 Pt. Conversion";
    char twoPoint[] = "2 Pt. Conversion";
    char defensive[] = "Defensive Conversion";
    char failed[] = "Conversion Failed";
    char touchdown[] = "Touchdown";
    char touchdown2[] = "Touchdown";
    char touchback[] = "Touchback";

    if (pText != 0) {
        fn_8017D7C4(pText);
        if (strcmp(pText, firstDown) == 0) {
            fn_800D490C();
            fn_800AE9A4();
        }
        if (strcmp(pText, turnover) == 0) {
            fn_800D4858();
        }
        if (strcmp(pText, onePoint) == 0 || strcmp(pText, twoPoint) == 0) {
            fn_800D49A4();
            fn_800AE9A4();
        }
        if (strcmp(pText, defensive) == 0) {
            fn_800D49FC();
            fn_800AE9A4();
        }
        if (strcmp(pText, failed) == 0) {
            fn_800D4A40();
        }
        if (strcmp(pText, safety) == 0) {
            fn_800D45A0();
        }
        if (strcmp(pText, touchback) == 0) {
            fn_800D4888(0);
        }
        if (strcmp(pText, touchdown) == 0 || strcmp(pText, touchdown2) == 0) {
            fn_800AE9A4();
        }
    }
}

extern "C" void fn_800B9654(Class_80297C60 *p, float dt)
{
    Vector_80039F5C pos;

    pos.mX = pos.mY = pos.mZ = 0.0f;
    fn_80076160();
    fn_800C9FC0();
    fn_800AE9EC();
    fn_801478F0(0);
    fn_801783D0(21, 0);
    fn_800C4438(&lbl_803EAB78->mSequence);
    if (fn_801486A0()) {
        p->vfn_08();
    }
    fn_800B24C8();
    if (fn_800BA6F8()) {
        fn_800BAAC4();
    }
    fn_800A1FEC(&lbl_803EAB78->mUnknown104, &lbl_803EAB78->mUnknown124);
    lbl_803EAB78->mUnknown151 = 0;
    p->vfn_06();
    fn_800C4460(&lbl_803EAB78->mSequence);
    if (fn_8002D060(lbl_803EA368) == 0) {
        fn_800AFDD4(fn_800B876C);
    }
    fn_80067D4C(123, 0);
    fn_80148154();
    fn_801483C8();
    if (fn_8002D0AC(lbl_803EA368)) {
        fn_800310C0(lbl_803EA368, 37, 0, &pos, 0);
    }
    lbl_803EAB78->mUnknown148 = 0;
    lbl_803EAB78->mUnknown14C = 0;
    lbl_803EAB78->mUnknown144 = 0;
    lbl_803EAB78->mUnknown150 = 0;
    lbl_803EAB78->mUnknown158 = 0;
    lbl_803EAB78->mUnknown159[0] = 0;
    lbl_803EAB78->mUnknown154 = 0;
    lbl_803EAB78->mUnknown160 = 1;
    lbl_803EAB78->mUnknown164 = 2;
    p->vfn_07();
    Desc_802345C4 desc = { 3, 14 };
    fn_802345C4(&desc, 2);
    fn_801789F8();
    lbl_803EAB80 = -1;
    lbl_803EAB7C = 0;
    lbl_803EAB7D = 0;
    lbl_803EAB7E = 0;
    fn_8009FF94(0);
    fn_8009FFB4(0);
}

extern "C" void fn_800B9A9C(void)
{
    Step_800C4460 *pStep;

    lbl_803EAB78->mUnknown151 = 1;
    pStep = (Step_800C4460 *)fn_800B9A44(lbl_803EAB84);
    pStep->mUnknownC = 120.0f;
    pStep->mpCallback4 = fn_800B89C8;
    if (fn_800BA6F8()) {
        pStep->mUnknownC = 10.0f;
    }
    pStep->mpUnknown10 = pStep;
    fn_800B9A6C(lbl_803EAB84, pStep);
}
