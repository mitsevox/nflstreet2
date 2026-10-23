#include "game/Object_8017886C.h"
#include "game/fn_800670B4.h"
#include "game/Object_80039F5C.h"
#include "game/cu_80136B1C.h"
#include "game/cu_8002B8F8.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"

/* Four-byte entry of the stream read by fn_800B9F50. */
struct Event_800B9F50 {
    unsigned char mType;
    unsigned char mIndex;
    unsigned short mTime;
};

/* Block allocated by fn_800BA3F0 through fn_80238174 under the id 'prac'
   (392 bytes); only the accessed fields are declared. */
struct Block_800BA3F0 {
    Object_800670B4 *mpUnknown0;
    Object_800670B4 *mpUnknown4;
    Record_80067338 *mpUnknown8;
    Record_80067338 *mpUnknownC;
    int mUnknown10;
    unsigned char mUnknown14;
    unsigned char mUnknown15[3];
    Point_8017886C mUnknown18;
    int mUnknown20;
    unsigned char mUnknown24[0x9C];
    int mUnknownC0;
    unsigned char mUnknownC4[0x1C];
    unsigned char mUnknownE0;
    unsigned char mUnknownE1[3];
    int mUnknownE4[37];
    Event_800B9F50 *mpUnknown178;
    int mUnknown17C;
    unsigned char mUnknown180;
    unsigned char mUnknown181[1];
    unsigned char mUnknown182;
    unsigned char mUnknown183;
    unsigned char mUnknown184;
    unsigned char mUnknown185;
    unsigned char mUnknown186[2];
};


struct Record_800B49EC;

extern "C" {
int fn_800BA870(void);
void fn_800AD910(int a, float b);
int fn_8002C9A8(Type_803EA368 *p, int msg, int value);
void fn_800A6F04(int team);
void fn_800B4798(short *pRatings, int team, int index, float *pOut);
void fn_800B49EC(Record_800B49EC *pDst, const Record_800B49EC *pSrc);
int fn_800BAAB8(void);
void fn_8011DF90(void);
void fn_80138590(Object_80137ABC *pBall);
void fn_8013A910(Object_80137ABC *pBall, int *pAngles);
void fn_8013AD9C(Object_80137ABC *pBall, int a);
void fn_8013F97C(int a);
void fn_8013FA58(int a, int b);
void fn_8013FA8C(int a);
void fn_80164430(Object_800670B4 *pObject, unsigned char index, unsigned char *pA, unsigned char *pB);
Object_800670B4 *fn_80168708(int team);
void fn_80168A14(int team);
void fn_80173D10(void);
void fn_80176C90(void);
int fn_80177C38(void);
void fn_80177C44(int value);
void fn_80177C50(int a);
void fn_801780A8(Point_8017886C pos);

extern Block_800BA3F0 *lbl_803EAB88;
}

extern "C" Point_8017886C fn_800BA7A0(void)
{
    if (lbl_803EAB88->mUnknown20 == 0) {
        lbl_803EAB88->mUnknown18.mX = 0.0f;
        lbl_803EAB88->mUnknown18.mY = -20.0f;
    }
    return lbl_803EAB88->mUnknown18;
}

extern "C" void fn_800BA804(int value)
{
    if (fn_800BA870() != 0) {
        lbl_803EAB88->mUnknown183 = value;
        if (value != 0) {
            fn_800AD910(8, 0.0f);
        }
    } else {
        lbl_803EAB88->mUnknown183 = 0;
    }
}

extern "C" void fn_800BAAE4(void)
{
    Vector_80039F5C pos;
    int angles[3];
    Point_8017886C point;
    Object_80137ABC *pBall;

    if (fn_80177C38() == 1 || fn_80177C38() == 3) {
        fn_80177C50(1);
        fn_80177C44(0);
    }
    fn_8002C9A8(lbl_803EA368, 3, 0);
    if (fn_80137B40() != 0) {
        fn_8013791C(fn_801374BC(), 5, 0);
    }
    fn_801780A8(fn_800BA7A0());
    if (fn_800BAAB8() != 0) {
        pBall = fn_801374BC();
        fn_8013791C(pBall, 6, 0);
        point = fn_80177FE0();
        pos.mX = point.mX;
        pos.mY = point.mY;
        pos.mZ = 0.3f;
        fn_80137D74(pBall, &pos);
        angles[0] = 0;
        angles[1] = 0xFFC00000;
        angles[2] = 0xFFC00000;
        fn_8013A910(pBall, angles);
        fn_8013AD9C(pBall, 0);
        fn_80138590(pBall);
        fn_8013FA8C(1);
    }
    fn_8013F97C(0);
    fn_8013FA58(1, fn_801374D4());
    fn_8011DF90();
    fn_80176C90();
    fn_80173D10();
    fn_80168A14(0);
    fn_80168A14(1);
    for (int team = 0; team <= 1; team++) {
        Object_800670B4 *pTeam = fn_80168708((unsigned char)team);
        int count = fn_80178D18((unsigned char)team);

        for (int i = 0; i < count; i++) {
            Object_80039F5C *p = fn_80039F5C((unsigned char)team, (unsigned short)i);
            unsigned char a;
            unsigned char b;

            fn_80164430(pTeam, (unsigned char)i, &a, &b);
            p->mUnknown2914 = a;
            fn_800B49EC((Record_800B49EC *)p->mRatings, (const Record_800B49EC *)p->mUnknown3020);
            fn_800B4798(p->mRatings, (unsigned char)team, (unsigned char)i, &p->mUnknown2900);
        }
        fn_800A6F04((unsigned char)team);
    }
}
