#include "engine/cu_801C2EB4.h"
#include "game/Class_80297AB8.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_8022781C.h"

struct Entry_8015005C {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknown10;
    unsigned char mUnknown12;
    char mUnknown13;
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    char mUnknown18[2];
};

struct Table_8015005C {
    Entry_8015005C mEntries[4];
    Vector_80039F5C mUnknown80;
    Point_8017886C mUnknown92[3];
    char mUnknown116;
    unsigned char mUnknown117;
    unsigned char mCount;
    char mUnknown119[6];
    unsigned char mUnknown125;
};

class Class_802A1D20 : public Class_80297AB8 {
public:
    unsigned char mUnknown4;
    char mUnknown5[3];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

extern "C" {
Table_8015005C *fn_801530FC(void);
Object_80039F5C *fn_8003AC84(int id);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
void fn_8017E17C(int slot, const char *pText0, const char *pText1, const char *pText2, int key);
extern const char lbl_802A0DDC[];
extern const char lbl_802A05C8[];
void fn_801780A8(Point_8017886C point);
void fn_8013A910(Object_80137ABC *pBall, int *pAngles);
void fn_8013AD9C(Object_80137ABC *pBall, int value);
void fn_80138590(Object_80137ABC *pBall);
void fn_8014FFC4(Point_8017886C *pPoint);
extern const float lbl_802A134C;
extern const float lbl_802A1350;
extern const float lbl_802A1360;
extern const float lbl_802A1364;
extern const float lbl_802A1368;

void fn_80150DFC(Class_802A1D20 *p)
{
    p->Class_80297AB8::vfn_05();
}

// Reset the balls and keep the three random field positions at least four units apart.
void ResetBallsAndFieldPositions(void)
{
    unsigned int count = fn_801383C8();
    Table_8015005C *pTable = fn_801530FC();
    Vector_80039F5C position;
    int angles[3];
    Point_8017886C origin;
    origin.mX = lbl_802A134C;
    origin.mY = lbl_802A1350;
    fn_801780A8(origin);
    Object_80137ABC *pCurrent = fn_801374BC();
    for (unsigned char i = 0; i < count; i++) {
        Object_80137ABC *pBall = fn_80137ABC(i);
        if (fn_80137AD0(pBall)) {
            fn_8013791C(pBall, 5, 0);
        }
        if (pBall == pCurrent) {
            fn_8013791C(pBall, 6, 0);
        }
        position.mX = origin.mX + i * lbl_802A1360;
        position.mY = origin.mY;
        position.mZ = lbl_802A1364;
        fn_80137D74(pBall, &position);
        angles[0] = 0;
        angles[1] = 0xFFC00000;
        angles[2] = 0xFFC00000;
        fn_8013A910(pBall, angles);
        fn_8013AD9C(pBall, 0);
        fn_80138590(pBall);
    }
    for (unsigned char i = 0; i <= 2; i++) {
        fn_8014FFC4(&pTable->mUnknown92[i]);
        unsigned int j = 0;
        while (j < i) {
            if (fn_8022781C(&pTable->mUnknown92[i], &pTable->mUnknown92[j]) < lbl_802A1368) {
                fn_8014FFC4(&pTable->mUnknown92[i]);
                j = 0;
            } else {
                j++;
            }
        }
    }
}

// Clear eliminated players' rows; show each remaining player's current round total.
void RefreshFourPlayerScoreRows(Class_802A1D20 *p)
{
    for (unsigned char i = 0; i <= 3; i++) {
        if (fn_801530FC()->mEntries[i].mUnknown13 == 0) {
            char score[16];
            char name[20];
            fn_801C2EF0(name, fn_8003AC84(fn_801530FC()->mEntries[i].mUnknown0)->mUnknown2927 + 21, sizeof(name));
            Entry_8015005C *pEntries = fn_801530FC()->mEntries;
            fn_801C2D88(score, sizeof(score), lbl_802A0DDC,
                        pEntries[i].mUnknown10 + pEntries[i].mUnknown8 * 2);
            fn_8017E17C(i + 1, name, score, lbl_802A05C8, fn_801530FC()->mEntries[i].mUnknown12);
        } else {
            fn_8017E17C(i + 1, lbl_802A05C8, lbl_802A05C8, lbl_802A05C8, 255);
        }
    }
}
}
