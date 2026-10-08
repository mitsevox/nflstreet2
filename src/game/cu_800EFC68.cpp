#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802372EC.h"
#include <math.h>
#include "game/cu_80067C10.h"
#include "game/fn_80238174.h"
#include "game/fn_802270D4.h"
#include <string.h>
#include "game/fn_801D2B7C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_8022781C.h"
#include "game/fn_80227638.h"

/* Record whose address fn_8011F4E0 returns. Only the accessed fields are
   declared; the size is unknown. */
struct Record_8011F4E0 {
    char mUnknown0[2];
    unsigned short mUnknown2;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    char mUnknown7[1];
    unsigned char mUnknown8[4];
    unsigned char mUnknown12[4];
    unsigned char mUnknown16[7];
    char mUnknown23[1];
    unsigned char mUnknown24[8];
    unsigned char mUnknown32[7];
    char mUnknown39[1];
    unsigned char mUnknown40[8];
};

/* Views of the block at player +336. Only the accessed fields
   are declared. */
struct Block_800FBAA8 {
    char mUnknown0[36];
    int mUnknown36;
};

struct Block_800FCC24 {
    int mUnknown0;
    char mUnknown4[16];
    int mUnknown20;
    char mUnknown24[9];
    unsigned char mUnknown33;
    char mUnknown34[3];
    unsigned char mUnknown37;
};

struct Block_800FD650 {
    float mUnknown0;
    float mUnknown4;
    char mUnknown8[8];
    unsigned int mUnknown16;
};

struct State_80111F80 {
    char mUnknown0[20];
    unsigned char mUnknown20;
};

struct State_80112E10 {
    int mUnknown0;
    int mUnknown4;
    float mUnknown8;
    unsigned char mUnknown12;
    unsigned char mUnknown13;
};

struct State_80113478 {
    int mUnknown0;
    int mUnknown4;
};

struct State_80113AAC {
    int mRef;
    char mUnknown4[10];
    unsigned char mUnknown14;
    unsigned char mUnknown15;
    char mUnknown16[5];
    unsigned char mUnknown21;
};

struct State_801147D4 {
    char mUnknown0[31];
    unsigned char mUnknown31;
};

struct State_80114DF4 {
    int mRef;
    char mUnknown4[52];
    unsigned char mUnknown56;
};

struct Record_801170A0 {
    char mUnknown0[1];
    unsigned char mUnknown1;
};

struct Record_80118894 {
    char mUnknown0[64];
    float mUnknown64;
    char mUnknown68[8];
    float mUnknown76;
};

struct Pair_8011BAE0 {
    float mUnknown0;
    float mUnknown4;
};

struct Entry_8011AFCC {
    char mUnknown0[60];
    int mUnknown60;
    char mUnknown64[4];
    float mUnknown68;
    char mUnknown72[8];
};

struct Record_8011F518;

/* Bytes at +336 of the player object as fn_8010BA00, fn_8010B5B0 and
   fn_8010BC48 access them. Partial layout. */
struct State_8010BA00 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
};

/* Record that fn_8010B738 reads through each table entry. Partial layout. */
struct Record_8010B738 {
    char mUnknown0[4];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
};

struct Entry_8010B738 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Record_8010B738 *mpRecord;
};

/* Counted table of 8-byte entries starting at +4. */
struct Table_8010B738 {
    unsigned short mCount;
    char mUnknown2[2];
    Entry_8010B738 mEntries[1];
};

/* Output of fn_801076F0. */
struct Result_801076F0 {
    Point_8017886C mUnknown0;
    Point_8017886C mUnknown8;
    int mUnknown16;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    float mUnknown32;
    float mUnknown36;
    float mUnknown40;
};

/* Input of fn_801076F0. Partial layout. */
struct Input_801076F0 {
    char mUnknown0[4];
    Point_8017886C mUnknown4;
    char mUnknown12[4];
    Point_8017886C mUnknown16;
};



extern float lbl_803EAEF4;
extern int lbl_803EAF10;
extern unsigned char lbl_802DAB60[];
extern unsigned char lbl_802DABBC[];

/* 24-byte entry of a queue's handler table, indexed by a queued message id. */
struct Handlers_800EFC68 {
    int (*mpUnknown0)(Object_80039F5C *p);
    int (*mpUnknown4)(Object_80039F5C *p);
    int (*mpUnknown8)(Object_80039F5C *p);
    int (*mpUnknown12)(Object_80039F5C *p);
    int (*mpUnknown16)(Object_80039F5C *p, int value);
    void (*mpUnknown20)(Message_800F01CC *pMessage);
};

/* Descriptor registered per queue kind through fn_800EFE0C. */
struct Queue_800EFE0C {
    unsigned short mUnknown0;
    unsigned short mCount;
    Handlers_800EFC68 *mpHandlers;
};

/* 196-byte record returned by fn_800B8694. */
struct Record_800B8694 {
    float mUnknown0[8];
    float mUnknown32;
    float mUnknown36;
    float mUnknown40;
    float mUnknown44;
    int mUnknown48;
    float mUnknown52[22];
    float mUnknown140;
    float mUnknown144;
    float mUnknown148;
    float mUnknown152;
    float mUnknown156;
    float mUnknown160;
    float mUnknown164;
    float mUnknown168;
    float mUnknown172;
    float mUnknown176;
    float mUnknown180;
    float mUnknown184;
    char mUnknown188[8];
};

/* 116-byte entry of the array that Record_803EAE18 points to. */
struct Entry_800F0EFC {
    unsigned int *mpUnknown0;
    int *mpUnknown4;
    Input_800B6D34 mBlock;
    unsigned char mUnknown112;
    char mUnknown113[3];
};

/* 8-byte record registered through fn_80238174 by fn_800F164C. */
struct Record_803EAE18 {
    unsigned char mCount;
    char mUnknown1[3];
    Entry_800F0EFC *mpEntries;
};

/* Block at +336 of the player object used by fn_800F0C6C and fn_800F0CCC,
   the handlers in entry 52 of the handler table at 0x802DB280. */
struct Block_800F0C6C {
    char mUnknown0[4];
    int mUnknown4;
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

/* 88-byte block at +336 of the player object, cleared by fn_800F4A74. */
struct Block_800F4A74 {
    char mUnknown0[20];
    int mUnknown20;
    int mUnknown24;
    float mUnknown28;
    float mUnknown32;
    int mUnknown36;
    int mUnknown40;
    float mUnknown44;
    unsigned char mUnknown48;
    unsigned char mUnknown49;
    unsigned char mUnknown50;
    unsigned char mUnknown51;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
    unsigned char mUnknown54;
    unsigned char mUnknown55;
    unsigned char mUnknown56;
    unsigned char mUnknown57;
    short mUnknown58;
    unsigned char mUnknown60;
    unsigned char mUnknown61;
    unsigned char mUnknown62;
    unsigned char mUnknown63;
    char mUnknown64[24];
};

struct Info_800F3A6C {
    Point_8017886C mUnknown0;
    Point_8017886C mUnknown8;
    int mUnknown16;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    float mUnknown32;
    float mUnknown36;
    float mUnknown40;
};

/* Ball pointer and two positions passed to fn_800F2EC8, fn_800F30AC and
   fn_800F3A6C. Only the accessed prefix is declared; the size is unknown. */
struct Points_800F3A6C {
    Object_80137ABC *mpUnknown0;
    Vector_80039F5C mUnknown4;
    Vector_80039F5C mUnknown16;
    Vector_80039F5C mUnknown28;
    Point_8017886C mUnknown40;
    float mUnknown48;
};

/* View of another player's +336 block read by fn_800F3344 while that player
   is in state 28. Only the accessed prefix is declared; the size is unknown. */
struct Block_800F3344 {
    unsigned short mUnknown0;
    char mUnknown2[2];
    Vector_80039F5C mUnknown4;
    unsigned int mUnknown16;
};

/* Block at +336 of the player object used by fn_800F23EC, fn_800F24D8 and
   fn_800F268C. Only the accessed prefix is declared; the size is unknown. */
struct Block_800F23EC {
    float mUnknown0;
    short mUnknown4;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
};

/* Byte at +336 of the player object set by fn_800F2AA0. */
struct Block_800F2AA0 {
    unsigned char mUnknown0;
};

/* Four bytes matched against the Info_80089904 records by fn_800F2CB4. */
struct Key_800F2CB4 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
};

/* Record passed by the caller at 0x800F6548/0x800F6594 to fn_800F4E88 and
   fn_800F4F08. Only the accessed members are declared; the size is unknown. */
struct Record_800F4E88 {
    Point_8017886C mUnknown0;
    float mUnknown8;
    float mUnknown12;
    char mUnknown16[4];
    int mUnknown20;
};

struct Object_800F4E14 {
    char mUnknown0[20];
    int mUnknown20;
};

extern "C" {
void fn_8003AB28(Object_80039F5C *p, Message_800F01CC *pMessage, int value);
int fn_800B65A0(int unknown);
void fn_800B6714(Object_80039F5C *p, int port);
void fn_800D0BF4(Object_80039F5C *p, int a, int b);
void fn_800E9528(Object_80039F5C *p);
int fn_800E96EC(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
void fn_8010D508(Object_80039F5C *p);
int fn_801101DC(Object_80039F5C *p);
int fn_801102A4(Object_80039F5C *p);
void fn_8011E240(Object_80039F5C *p);
void fn_8011E3EC(Object_80039F5C *p, int a);
Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, int a, unsigned char count, float *pOut, int b);
float fn_801250B8(Object_80039F5C *p, int a, int b);
int fn_80178308(void);
int fn_80178320(void);
int fn_801BE648(void *p);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
extern float lbl_803EAF58;
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_8009F7A4(Object_80039F5C *p, Object_80039F5C **ppOut);
int fn_8009FE24(Object_80039F5C *p);
int fn_800F5AD4(Object_80039F5C *p);
void fn_800F6AD8(float *p);
Point_8017886C fn_800F97A8(Object_80039F5C *p);
void fn_800FBB70(void);
unsigned char fn_800FC014(Object_80039F5C *p, Object_80039F5C *pOther);
unsigned char fn_800FC0C4(Object_80039F5C *p);
int fn_800FC4A8(Object_80039F5C *p, Block_800FCC24 *pBlock, int a);
int fn_800FC7A0(Object_80039F5C *p, Block_800FCC24 *pBlock);
void fn_800FD724(Object_80039F5C *p);
int fn_8011F1CC(void);
Record_8011F4E0 *fn_8011F4E0(void);
void fn_8016DF34(Object_80039F5C *p);
int fn_801783AC(int bit);
void fn_8009A8D4(void *p);
int fn_8009EAB0(Object_80039F5C *p, unsigned char a);
int fn_8009EF6C(void *p);
int fn_80099AD0(Object_80039F5C *p, Object_80137ABC *pBall, int a, int b, int c, int d, int e);
int fn_80099C80(Object_80039F5C *p, Object_80137ABC *pBall, int a, int *pOut, int *pOut2);
int fn_80099F04(Object_80039F5C *p, int a, unsigned char index);
int fn_8009A1A8(Object_80039F5C *p, int a, int b, int c, unsigned char index);
int fn_800C1180(Object_80039F5C *p);
float fn_800CA9B4(int kind, Object_80039F5C *p);
void fn_800CE674(Object_800CE674 *p);
void fn_800CE684(Object_800CE674 *p);
void fn_800D6EDC(void);
void fn_800D7A0C(Object_80039F5C *p, int a);
int fn_800E815C(Object_80039F5C *p, int a, int b);
int fn_800E98A4(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_800F2C1C(Object_80039F5C *p, int a);
int fn_8010A2DC(Object_80039F5C *p, int a, int b);
int fn_80113088(Object_80039F5C *p);
int fn_80113604(Object_80039F5C *p);
Object_80039F5C *fn_80114E7C(Object_80039F5C *p);
int fn_80118B4C(Object_80039F5C *p, Pair_8011BAE0 *pPair);
void fn_8011BAE0(Pair_8011BAE0 *pOut);
void fn_8011DBC0(Object_80039F5C *p);
void fn_8011DBC4(Object_80039F5C *p);
int fn_8011DC68(unsigned int id);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pOther, int a, int b);
int fn_8011E3F4(Object_80039F5C *p);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
void fn_80143EBC(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_801486A0(void);
int fn_801520C4(Object_80039F5C *p, unsigned char *pIndex);
void fn_8017D9B0(int a, int b);
void *fn_8023816C(void *pHandle);
extern float lbl_803ECB08;
extern unsigned char *lbl_803EC9F0;
void fn_8003AB08(Object_80039F5C *p, int a);
void fn_8009D1AC(Object_80039F5C *p);
int fn_800A2178(void);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
void fn_800D6914(int a, Object_80039F5C *p);
void fn_80104B3C(Object_80039F5C *p, Vector_80039F5C *pOut);
Object_80039F5C *fn_80105384(Object_80039F5C *p, int a, int b);
int fn_80105E90(Object_80039F5C *p, Object_80039F5C *pTarget, int kind);
int fn_80106618(Object_80039F5C *p);
void fn_80106678(Record_8011F518 *pRecord, Object_80039F5C *p, int a, int b);
void fn_8010CEB8(Object_80039F5C *p, int kind);
Record_8011F518 *fn_8011F518(void);
float fn_8012506C(Object_80039F5C *p, int kind);
int fn_801485D4(void);
int fn_80156704(void);
unsigned char fn_80156D14(void);
int fn_80178348(void);
int fn_80178360(void);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_8022765C(void *pOut, void *pA, void *pB);
unsigned char fn_8010B87C(Object_80039F5C *p, Object_80039F5C *pOther);
extern Queue_800EFE0C **lbl_803EAE14;
extern int lbl_803EC9EC;
extern Record_803EAE18 *lbl_803EAE18;
extern float lbl_803EAE1C;
extern Input_800B6D34 lbl_802DAAD0;
extern unsigned int *lbl_802EE928[];
extern int *lbl_802EE938[];
void fn_800A5A8C(int a, Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800D6C70(Object_80039F5C *p);
int fn_800DD648(Object_80039F5C *p);
void fn_800EFC68(int a, State_80039F5C *pQueue);
void fn_800EFCD0(int a, State_80039F5C *pQueue, Object_80039F5C *p);
void fn_800F0490(int a, State_80039F5C *pQueue, int id);
void fn_800F0960(Object_80039F5C *p, Block_800F0C6C *pBlock);
int fn_800F0B84(Object_80039F5C *p);
void fn_800F0FD0(Input_800B6D34 *pBlock, int index);
int fn_800F1FDC(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_800F21E0(Object_80039F5C *p, Object_80039F5C *pOther, float distance);
int fn_800F2920(Object_80039F5C *p);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, int a, unsigned char count, int angle, float *pOut, int b);
unsigned int fn_80178D18(int team);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
int fn_80238278(const void *p, int size, int seed);
void fn_8009BD60(Object_80039F5C *p);
int fn_8011F1A4(void);
unsigned int fn_8011F4C8(void);
int fn_800B6644(int index);
Record_800B8694 *fn_800B8694(int index);
int fn_801D34D0(void *pDest, int size, int value, int width);
void fn_800A8954(int event, int team, Object_80039F5C *p);
int fn_800B83F4(Object_80039F5C *p);
int fn_800CA5CC(Object_80039F5C *p, int a, int b);
int fn_800D0B90(Object_80039F5C *p);
void fn_800D0C0C(Object_80039F5C *p, int a);
int fn_801BA568(void *pA, void *pB, int id);
int fn_801BA5A8(void *pA, void *pB, unsigned short id, int index);
int fn_801BA6B0(Entry_800EAC9C *pEntry);
void fn_801BA6BC(Entry_800EAC9C *pEntry, int flag);
void fn_801BD81C(void *p, float value);
float fn_801CFFA0(float value);
int fn_800B83A0(Object_80039F5C *p);
void fn_80067E3C(int type, Vector_80039F5C *pPos, int id, int a, int b, int c);
extern float lbl_803EA2C4;
float fn_80178A08(void);
int fn_8011E9B4(Object_80039F5C *p);
void fn_8022732C(void *pPoint, void *pVelocity, float scale);
int fn_800C4B6C(Object_80039F5C *p);
void fn_800D52F8(Object_80039F5C *p);
int fn_800CE4A8(Query_800CE770 *pQuery);
float fn_800C49A4(Object_80039F5C *p, float value);
void fn_8011E33C(Object_80039F5C *p, Object_80039F5C *pOther, int a);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, void *p, float e);
void fn_801BA2A8(void *a, void *b, unsigned short c, unsigned short d, unsigned short e, void *p, float f);
Object_80039F5C *fn_8015286C(void *pSet, int index);
int fn_8015310C(void *pSet);
extern unsigned char lbl_803EAE20[8];
extern const float lbl_803ED6CC;
int fn_800AC3FC(Object_80039F5C *p, int value);
void fn_800C89F0(Object_80039F5C *p, int angle, int a, int b, float scale);
void fn_8013AA00(Object_80137ABC *pBall, float *pOut, Point_8017886C *pPoint, float scale);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
void fn_801528E0(void *pSet, Point_8017886C *pOut);
int fn_800AC3A0(Object_80039F5C *p);
void fn_802271A4(Point_8017886C *pOut, Point_8017886C *pIn);
float fn_801CFB94(int angle);
float fn_80178A44(void);
float fn_8011F4D4(void);
float fn_802276E8(Point_8017886C *pA, Point_8017886C *pB);
int fn_8009A6EC(Object_80039F5C *p);
int fn_800997F4(Object_80039F5C *p, Object_80137ABC *pBall, float range, void *pBlock, int a, int b, int c, int *pOutA,
                int *pOutB);
int fn_80099734(Object_80039F5C *p, Object_80137ABC *pBall, int a, int mode, void *pBlock, int b, int c, int d, int e,
                float range);
extern char lbl_8031BDD4[];
}

extern "C" void fn_800EFC68(int a, State_80039F5C *pQueue) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    memmove(pEntries, pEntries + 1, (lbl_803EAE14[a]->mCount - 1) * 4);
    pEntries[lbl_803EAE14[a]->mCount - 1].mId = 0;
}

extern "C" void fn_800EFCD0(int a, State_80039F5C *pQueue, Object_80039F5C *p) {
    p->mUnknown3088 = 0;
    if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown0(p) == 1 && p->mUnknown3088 == 0) {
        fn_800EFC68(a, pQueue);
        fn_800EFCD0(a, pQueue, p);
    }
    p->mUnknown3088 = 1;
    fn_800D6C70(p);
}

extern "C" void fn_800EFD70(int count) {
    if (lbl_803EAE14 == 0) {
        lbl_803EC9EC = count;
        lbl_803EAE14 = (Queue_800EFE0C **)fn_801D2B7C(count * 4, 0, 0);
        for (int i = 0; i < count; i++) {
            lbl_803EAE14[i] = 0;
        }
    }
}

extern "C" void fn_800EFDD8() {
    if (lbl_803EAE14 != 0) {
        fn_801D2BD0(lbl_803EAE14);
        lbl_803EAE14 = 0;
    }
}

extern "C" void fn_800EFE0C(int a, Queue_800EFE0C *pQueue) {
    lbl_803EAE14[a] = pQueue;
}

extern "C" void fn_800EFE1C(int a, State_80039F5C *pQueue) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    for (int i = 0; i < lbl_803EAE14[a]->mCount; i++) {
        pEntries[i].mId = 0;
    }
}

extern "C" void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p);
    for (int i = 0; i < lbl_803EAE14[a]->mCount; i++) {
        pEntries[i].mId = 0;
    }
}

extern "C" void fn_800EFEF8(int a, State_80039F5C *pQueue, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p) == 1) {
        pEntries[0].mId = 0;
    }
    for (int i = 1; i < lbl_803EAE14[a]->mCount; i++) {
        pEntries[i].mId = 0;
    }
}

extern "C" void fn_800EFFA0(int a, State_80039F5C *pQueue, Object_80039F5C *p, int flag) {
    int id = pQueue->mId;
    int done = 0;

    if (flag != 0) {
        p->mUnknown3088 = 0;
        if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown12(p) == 1) {
            if (p->mUnknown3088 == 0) {
                fn_800EFC68(a, pQueue);
                done = 1;
                fn_800EFCD0(a, pQueue, p);
            } else {
                fn_800F0490(a, pQueue, id);
            }
        }
    }
    if (done == 0) {
        p->mUnknown3088 = 0;
        if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown8(p) == 1) {
            if (p->mUnknown3088 == 0) {
                fn_800EFC68(a, pQueue);
                fn_800EFCD0(a, pQueue, p);
            } else {
                fn_800F0490(a, pQueue, id);
            }
        }
    }
}

extern "C" void fn_800F00D4(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p) == 1) {
        int i;
        int last = lbl_803EAE14[a]->mCount - 2;

        for (i = 0; i < last && pEntries[i].mId != 0; i++) {
        }
        memmove(pEntries + 1, pEntries, (i + 1) * 4);
        pEntries[0] = *pMessage;
        fn_800EFCD0(a, pQueue, p);
    } else {
        fn_800F01CC(a, pQueue, pMessage, p);
        pEntries[2].mId = 0;
    }
}

extern "C" void fn_800F01CC(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    if (pEntries[0].mId != 0) {
        int i;
        int last = lbl_803EAE14[a]->mCount - 2;

        for (i = 1; i < last && pEntries[i].mId != 0; i++) {
        }
        memmove(pEntries + 2, pEntries + 1, i * 4);
        pEntries[1] = *pMessage;
    } else {
        fn_800F053C(a, pQueue, pMessage, p);
    }
}

extern "C" void fn_800F0278(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p, int position) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;
    Queue_800EFE0C *pInfo = lbl_803EAE14[a];

    if (pEntries[pInfo->mCount - 1].mId == 0) {
        if (pEntries[0].mId != 0) {
            int i;

            if (position == 0 && pInfo->mpHandlers[pEntries[0].mId].mpUnknown4(p) != 1) {
                position = 1;
            }
            for (i = 0; i < lbl_803EAE14[a]->mCount && pEntries[i].mId != 0 && i != position; i++) {
            }
            if (i != lbl_803EAE14[a]->mCount) {
                memmove(pEntries + (i + 1), pEntries + i, (lbl_803EAE14[a]->mCount - i - 1) * 4);
                pEntries[i] = *pMessage;
                if (i == 0) {
                    fn_800EFCD0(a, pQueue, p);
                }
            }
        } else {
            fn_800F053C(a, pQueue, pMessage, p);
        }
    }
}

extern "C" void fn_800F03D8(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    if (pEntries[0].mId != 0) {
        int i;

        for (i = 1; i < lbl_803EAE14[a]->mCount && pEntries[i].mId != 0; i++) {
        }
        if (i != lbl_803EAE14[a]->mCount) {
            pEntries[i++] = *pMessage;
            if (i != lbl_803EAE14[a]->mCount) {
                pEntries[i].mId = 0;
            }
        }
    } else {
        fn_800F053C(a, pQueue, pMessage, p);
    }
}

extern "C" void fn_800F0490(int a, State_80039F5C *pQueue, int id) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;
    int count = lbl_803EAE14[a]->mCount;

    for (int i = 0; i < count; i++) {
        if (pEntries[i].mId == id) {
            memmove(&pEntries[i], &pEntries[i + 1], (count - i - 1) * 4);
            pEntries[lbl_803EAE14[a]->mCount - 1].mId = 0;
            break;
        }
    }
}

extern "C" void fn_800F053C(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p) == 1) {
        pEntries[0] = *pMessage;
        pEntries[1].mId = 0;
        fn_800EFCD0(a, pQueue, p);
    } else {
        fn_800F01CC(a, pQueue, pMessage, p);
        pEntries[2].mId = 0;
    }
}

extern "C" void fn_800F05E4(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p) == 1) {
        pEntries[0] = *pMessage;
        fn_800EFCD0(a, pQueue, p);
    } else {
        fn_800F01CC(a, pQueue, pMessage, p);
    }
}

extern "C" void fn_800F067C(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p);
    pEntries[0] = *pMessage;
    fn_800EFCD0(a, pQueue, p);
}

extern "C" int fn_800F06F4(int a, void *pRecord, int id, int value) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pRecord;
    int result = 0xFFFF;
    unsigned int i;

    if (value == 0xFFFF) {
        i = 0;
    } else {
        i = value;
    }
    if ((pEntries[i].mId & 0x7F) == 0) {
        return 0xFFFF;
    }
    for (; i < lbl_803EAE14[a]->mCount && (pEntries[i].mId & ~0x80) != 0; i++) {
        if ((pEntries[i].mId & ~0x80) == id) {
            result = i;
            break;
        }
    }
    return result;
}

extern "C" int fn_800F0770(int a, State_80039F5C *pQueue, int which, int value, Object_80039F5C *p) {
    int result = 0;

    switch (which) {
    case 0:
        result = lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown0(p);
        break;
    case 1:
        result = lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown4(p);
        break;
    case 2:
        result = lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown8(p);
        break;
    case 3:
        result = lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown12(p);
        break;
    case 4:
        if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown16 != 0) {
            result = lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown16(p, value);
        }
        break;
    }
    if (result == 1) {
        fn_800EFC68(a, pQueue);
        fn_800EFCD0(a, pQueue, p);
    }
    return result;
}

extern "C" int fn_800F08F8() {
    return 0;
}

extern "C" int fn_800F0900() {
    return 1;
}

extern "C" int fn_800F0908() {
    return 0;
}

extern "C" void fn_800F0910(int a, Message_800F01CC *pMessage) {
    void (*pHandler)(Message_800F01CC *) = lbl_803EAE14[a]->mpHandlers[pMessage->mId].mpUnknown20;

    if (pHandler != 0) {
        pHandler(pMessage);
    }
}

extern "C" void fn_800F0960(Object_80039F5C *p, Block_800F0C6C *pBlock) {
    int kind;
    int mode;

    if (fn_801BE648(p->mpUnknown792) == 47 || fn_801BE648(p->mpUnknown792) == 32) {
        return;
    }
    mode = 32;
    fn_8009BD60(p);
    kind = p->mpState->mUnknown1;
    switch (kind) {
    case 0:
        p->mUnknown1008.mUnknown0 = 1;
        break;
    case 3:
        p->mUnknown1008.mUnknown0 = 4;
        break;
    case 2:
        p->mUnknown1008.mUnknown0 = 3;
        break;
    case 1:
        p->mUnknown1008.mUnknown0 = 2;
        break;
    case 4:
        p->mUnknown1008.mUnknown0 = 7;
        break;
    case 5:
        p->mUnknown1008.mUnknown0 = 5;
        break;
    case 6:
        p->mUnknown1008.mUnknown0 = 6;
        break;
    case 7:
        p->mUnknown1008.mUnknown0 = 10;
        break;
    case 8:
        p->mUnknown1008.mUnknown0 = 11;
        break;
    case 9:
        p->mUnknown1008.mUnknown0 = 12;
        break;
    default:
        p->mUnknown1008.mUnknown0 = 2;
        break;
    }
    switch (kind) {
    case 0:
    case 2:
    case 3:
        if (fn_8011F1A4() != 0 && (fn_8011F4C8() & 1)) {
            p->mUnknown1008.mUnknown1 = 3;
        } else {
            p->mUnknown1008.mUnknown1 = 6;
        }
        break;
    case 5:
        if (p->mMotion.mPos.mX < fn_80177FE0().mX) {
            p->mUnknown1008.mUnknown1 = 3;
        } else {
            p->mUnknown1008.mUnknown1 = 6;
        }
        break;
    case 1:
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
        p->mUnknown512.mUnknown14 = 6;
        mode = 47;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = 1.0f;
        break;
    }
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, mode, p, 1.0f);
    p->mUnknown512.mUnknown14 = 0;
}

extern "C" int fn_800F0B84(Object_80039F5C *p) {
    int result = 0;

    if (fn_801BE648(p->mpUnknown792) == 47 || fn_801BE648(p->mpUnknown792) == 32
        || p->mMotion.mUnknown28 < lbl_803ECB08 * 0.14f) {
        result = 1;
    }
    return result;
}

extern "C" void fn_800F0BF8(Object_80039F5C *p, int a, int angle) {
    if (fn_800F0B84(p) != 0) {
        Message_800F01CC message;

        memset(&message, 0, 4);
        message.mId = 52;
        message.mUnknown1[0] = a;
        message.mUnknown1[1] = angle >> 17 & 0x7F;
        fn_800F00D4(0, p->mpState, &message, p);
    }
}

extern "C" int fn_800F0C6C(Object_80039F5C *p) {
    Block_800F0C6C *pBlock = (Block_800F0C6C *)&p->mUnknown336;

    pBlock->mUnknown4 = (p->mpState->mUnknown2 & 0x7F) << 17;
    pBlock->mUnknown8 = 0;
    if (fn_800F0B84(p) != 0) {
        pBlock->mUnknown9 = 0;
    } else {
        pBlock->mUnknown9 = 1;
    }
    return 0;
}

extern "C" int fn_800F0CCC(Object_80039F5C *p) {
    Block_800F0C6C *pBlock = (Block_800F0C6C *)&p->mUnknown336;
    Object_800B26B0 *pMotion = &p->mMotion;

    if (pBlock->mUnknown9 != 0) {
        return 1;
    }
    if (pBlock->mUnknown8 == 0) {
        fn_800F0960(p, pBlock);
        p->mUnknown512.mUnknown14 = 0;
        p->mFlags &= ~4;
        pBlock->mUnknown8 = 1;
    }
    if (fn_8013BA58(fn_801374BC(), 0) == 4 && p == fn_80137B88(fn_801374BC())) {
        Message_800F01CC message;

        memset(&message, 0, 4);
        message.mId = 23;
        message.mUnknown1[0] = fn_801374E0(fn_801374BC());
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (p->mFlags & 1) {
        p->mFlags &= ~1;
        fn_800A5A8C(9, p, p);
    }
    if (p->mFlags & 4) {
        p->mFlags &= ~4;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = pMotion->mFacing;
        p->mUnknown512.mUnknown4 = pMotion->mFacing;
        p->mUnknown512.mUnknown0 = pMotion->mUnknown28 / lbl_803ECB08;
        return 1;
    }
    return 0;
}

extern "C" void fn_800F0E10(Message_800F01CC *pMessage) {
    pMessage->mUnknown1[1] = (0x800000 - (pMessage->mUnknown1[1] << 17)) >> 17 & 0x7F;
}

extern "C" int fn_800F0E2C(void *p, void *q) {
    Record_803EAE18 *pRecord = (Record_803EAE18 *)p;
    Record_803EAE18 *pOther = (Record_803EAE18 *)q;
    int result;

    if (pOther != 0) {
        result = 0;
        result |= pRecord->mCount != pOther->mCount;
        result |= fn_80238258(pRecord->mpEntries, pOther->mpEntries, pRecord->mCount * 116);
    } else {
        result = fn_80238278(pRecord, 8, 0);
        result = fn_80238278(pRecord->mpEntries, pRecord->mCount * 116, result);
    }
    return result;
}

extern "C" int fn_800F0EC0(void *p, int value) {
    Record_803EAE18 *pRecord = (Record_803EAE18 *)p;

    fn_801D2BD0(pRecord->mpEntries);
    pRecord->mpEntries = 0;
    return 0;
}

extern "C" int fn_800F0EFC(void *p, int value) {
    Record_803EAE18 *pRecord = (Record_803EAE18 *)p;

    pRecord->mpEntries = (Entry_800F0EFC *)fn_801D2B7C(pRecord->mCount * 116, 0, 0);
    memset(pRecord->mpEntries, 0, pRecord->mCount * 116);
    for (int i = 0; i < pRecord->mCount; i++) {
        pRecord->mpEntries[i].mpUnknown0 = lbl_802EE928[0];
        pRecord->mpEntries[i].mpUnknown4 = lbl_802EE938[0];
    }
    return 0;
}

extern "C" int fn_800F0FA0(Input_800B6D34 *pBlock, unsigned int *pMasks, int index) {
    int result = 0;

    if (pMasks != 0 && (pBlock->mUnknown0 & pMasks[index]) == pMasks[index]) {
        result = 1;
    }
    return result;
}

extern "C" void fn_800F0FD0(Input_800B6D34 *pBlock, int index) {
    Record_800B8694 *pInput;
    unsigned int i;

    fn_801D34D0(pBlock, 104, 0, 4);
    if (fn_800B6644(index) == 255) {
        return;
    }
    pInput = fn_800B8694(index);
    pBlock->mUnknown20 = pInput->mUnknown48;
    pBlock->mUnknown4 = pInput->mUnknown32;
    pBlock->mUnknown8 = pInput->mUnknown36;
    pBlock->mUnknown12 = pInput->mUnknown40;
    pBlock->mUnknown16 = pInput->mUnknown44;
    pBlock->mUnknown24[0] = pInput->mUnknown140;
    pBlock->mUnknown24[1] = pInput->mUnknown144;
    pBlock->mUnknown24[2] = pInput->mUnknown148;
    pBlock->mUnknown24[3] = pInput->mUnknown152;
    pBlock->mUnknown24[4] = pInput->mUnknown156;
    pBlock->mUnknown24[5] = pInput->mUnknown160;
    pBlock->mUnknown24[6] = pInput->mUnknown168;
    pBlock->mUnknown24[7] = pInput->mUnknown164;
    pBlock->mUnknown24[8] = pInput->mUnknown172;
    pBlock->mUnknown24[9] = pInput->mUnknown176;
    pBlock->mUnknown24[10] = pInput->mUnknown180;
    pBlock->mUnknown24[11] = pInput->mUnknown184;
    if (pInput->mUnknown0[0] != 0.0f || pBlock->mUnknown24[2] != 0.0f) {
        pBlock->mUnknown0 |= 0x1;
    }
    if (pInput->mUnknown0[1] != 0.0f || pBlock->mUnknown24[3] != 0.0f) {
        pBlock->mUnknown0 |= 0x2;
    }
    if (pInput->mUnknown0[2] != 0.0f || pBlock->mUnknown24[1] != 0.0f) {
        pBlock->mUnknown0 |= 0x4;
    }
    if (pInput->mUnknown0[3] != 0.0f || pBlock->mUnknown24[0] != 0.0f) {
        pBlock->mUnknown0 |= 0x8;
    }
    if (pInput->mUnknown0[4] != 0.0f) {
        pBlock->mUnknown0 |= 0x10;
    }
    if (pInput->mUnknown0[5] != 0.0f) {
        pBlock->mUnknown0 |= 0x20;
    }
    if (pInput->mUnknown0[6] != 0.0f) {
        pBlock->mUnknown0 |= 0x40;
    }
    if (pInput->mUnknown0[7] != 0.0f) {
        pBlock->mUnknown0 |= 0x80;
    }
    if (pInput->mUnknown52[0] != 0.0f) {
        pBlock->mUnknown0 |= 0x100;
    }
    if (pInput->mUnknown52[1] != 0.0f) {
        pBlock->mUnknown0 |= 0x200;
    }
    if (pInput->mUnknown52[2] != 0.0f) {
        pBlock->mUnknown0 |= 0x400;
    }
    if (pInput->mUnknown52[3] != 0.0f) {
        pBlock->mUnknown0 |= 0x800;
    }
    if (pInput->mUnknown52[4] != 0.0f) {
        pBlock->mUnknown0 |= 0x1000;
    }
    if (pInput->mUnknown52[5] != 0.0f) {
        pBlock->mUnknown0 |= 0x2000;
    }
    if (pInput->mUnknown52[6] != 0.0f) {
        pBlock->mUnknown0 |= 0x4000;
    }
    if (pInput->mUnknown52[7] != 0.0f) {
        pBlock->mUnknown0 |= 0x8000;
    }
    if (pInput->mUnknown52[8] != 0.0f) {
        pBlock->mUnknown0 |= 0x10000;
    }
    if (pInput->mUnknown52[9] != 0.0f) {
        pBlock->mUnknown0 |= 0x20000;
    }
    if (pInput->mUnknown52[10] != 0.0f) {
        pBlock->mUnknown0 |= 0x40000;
    }
    if (pInput->mUnknown52[11] != 0.0f || pBlock->mUnknown24[6] != 0.0f) {
        pBlock->mUnknown0 |= 0x80000;
    }
    if (pInput->mUnknown52[12] != 0.0f || pBlock->mUnknown24[7] != 0.0f) {
        pBlock->mUnknown0 |= 0x100000;
    }
    if (pInput->mUnknown52[13] != 0.0f || pBlock->mUnknown24[5] != 0.0f) {
        pBlock->mUnknown0 |= 0x200000;
    }
    if (pInput->mUnknown52[14] != 0.0f || pBlock->mUnknown24[4] != 0.0f) {
        pBlock->mUnknown0 |= 0x400000;
    }
    if (pInput->mUnknown52[15] != 0.0f || pBlock->mUnknown24[8] != 0.0f) {
        pBlock->mUnknown0 |= 0x800000;
    }
    if (pInput->mUnknown52[16] != 0.0f || pBlock->mUnknown24[9] != 0.0f) {
        pBlock->mUnknown0 |= 0x1000000;
    }
    if (pInput->mUnknown52[17] != 0.0f || pBlock->mUnknown24[10] != 0.0f) {
        pBlock->mUnknown0 |= 0x2000000;
    }
    if (pInput->mUnknown52[18] != 0.0f || pBlock->mUnknown24[11] != 0.0f) {
        pBlock->mUnknown0 |= 0x4000000;
    }
    if (pInput->mUnknown52[19] != 0.0f) {
        pBlock->mUnknown0 |= 0x8000000;
    }
    if (pInput->mUnknown52[20] != 0.0f) {
        pBlock->mUnknown0 |= 0x10000000;
    }
    if (pInput->mUnknown52[21] != 0.0f) {
        pBlock->mUnknown0 |= 0x20000000;
    }
    if (pBlock->mUnknown12 != 0.0f || pBlock->mUnknown16 != 0.0f) {
        Point_8017886C stick;
        float length;
        int angle;

        stick.mX = pBlock->mUnknown12;
        stick.mY = pBlock->mUnknown16;
        length = fn_802270A4(&stick) > 1.0f ? 1.0f : fn_802270A4(&stick);
        angle = fn_801CFE40(stick.mY, stick.mX) & 0xFFFFFF;
        if (length > 0.8f) {
            if (angle <= 0x400000 || angle >= 0xC00000) {
                pBlock->mUnknown0 |= 0x8000;
            } else {
                pBlock->mUnknown0 |= 0x4000;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        pBlock->mUnknown72[i] = pBlock->mUnknown24[lbl_803EAE18->mpEntries[index].mpUnknown4[i]];
    }
    for (i = 0; i < 68; i++) {
        if (fn_800F0FA0(pBlock, lbl_803EAE18->mpEntries[index].mpUnknown0, i) != 0) {
            pBlock->mUnknown92[i / 8] |= 1 << (i % 8);
        }
    }
}

extern "C" int fn_800F15B0(void *p, void *pBuffer) {
    Record_803EAE18 *pRecord = (Record_803EAE18 *)p;

    memcpy(pBuffer, pRecord, 8);
    memcpy((char *)pBuffer + 8, pRecord->mpEntries, pRecord->mCount * 116);
    return 1;
}

extern "C" int fn_800F1604(void *p, void *pBuffer) {
    Record_803EAE18 *pRecord = (Record_803EAE18 *)p;

    memcpy(pRecord->mpEntries, (char *)pBuffer + 8, pRecord->mCount * 116);
    return 1;
}

extern "C" int fn_800F1638(void *p) {
    return lbl_803EAE18->mCount * 116 + 8;
}

extern "C" void fn_800F164C(int count) {
    void *pHandle = fn_80238174(0, (void **)&lbl_803EAE18, 8, 0, 0x6173736A);
    Record_803EAE18 *pRecord;

    fn_80238234(pHandle, fn_800F0EFC, fn_800F0EC0, 0, fn_800F0E2C);
    fn_80238248(pHandle, fn_800F15B0, fn_800F1638, fn_800F1604);
    pRecord = (Record_803EAE18 *)fn_8023816C(pHandle);
    pRecord->mCount = count;
    pRecord->mpEntries = 0;
    fn_802381E0(pHandle);
}

extern "C" void fn_800F16F4() {
    lbl_803EAE18 = 0;
}

extern "C" void fn_800F1700() {
    for (unsigned char i = 0; i < lbl_803EAE18->mCount; i++) {
        fn_800F0FD0(&lbl_803EAE18->mpEntries[i].mBlock, i);
        lbl_803EAE18->mpEntries[i].mUnknown112 = 0;
    }
}

extern "C" void fn_800F177C(int index, Input_800B6D34 *pOut) {
    Input_800B6D34 *pSource;

    if (lbl_803EAE18->mpEntries[index].mUnknown112 == 0) {
        pSource = &lbl_803EAE18->mpEntries[index].mBlock;
    } else {
        pSource = &lbl_802DAAD0;
    }
    *pOut = *pSource;
}

extern "C" void fn_800F1800(int index) {
    lbl_803EAE18->mpEntries[index].mUnknown112 = 1;
}

extern "C" void fn_800F181C(int index, int which) {
    lbl_803EAE18->mpEntries[index].mpUnknown0 = lbl_802EE928[which];
    lbl_803EAE18->mpEntries[index].mpUnknown4 = lbl_802EE938[which];
}

extern "C" void fn_800F1858(Object_80039F5C *p) {
    short *pRatings = p->mRatings;
    Block_800F0C6C *pBlock = (Block_800F0C6C *)&p->mUnknown336;
    int index = 0xFFFF;
    int side;
    int found;
    float a;
    float b;

    fn_800A8954(1, p->mIdBytes[2], p);
    fn_8009BD60(p);
    side = 6;
    a = 0.4f;
    b = 0.05f;
    switch (p->mpState->mUnknown2) {
    case 0:
        side = 6;
        break;
    case 1:
        side = 6;
        break;
    case 2:
        side = 3;
        break;
    }
    if (p->mUnknown776 == 1) {
        if (side == 6) {
            side = 3;
        } else {
            side = 6;
        }
    }
    pBlock->mUnknown8 = side;
    p->mUnknown1008.mUnknown1 = side;
    p->mUnknown1008.mUnknown0 = 3;
    found = fn_800D0B90(p);
    if (fn_800B83F4(p) != 0) {
        fn_800D0C0C(p, 0);
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 240, p, 1.0f);
    } else if (found != 0) {
        if (fn_802372EC(0, 100) < 50) {
            p->mUnknown1008.mUnknown2 = 1;
        } else {
            p->mUnknown1008.mUnknown2 = 2;
        }
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 179, p, 1.0f);
        switch (p->mUnknown1008.mUnknown2) {
        case 1:
            if (side == 3) {
                fn_800D0C0C(p, 2);
            } else {
                fn_800D0C0C(p, 1);
            }
            break;
        case 2:
            if (side == 3) {
                fn_800D0C0C(p, 4);
            } else {
                fn_800D0C0C(p, 3);
            }
            break;
        }
    } else {
        fn_800D0C0C(p, 0);
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 22, p, 1.0f);
    }
    if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 22) != 0 || fn_801BA568(p->mpUnknown796, p->mpUnknown800, 179) != 0) {
        Entry_800EAC9C *pEntries = p->mpUnknown800;
        Entry_800EAC9C *pEntry;
        float speed;

        if (fn_801BA568(p->mpUnknown796, pEntries, 179) != 0) {
            index = fn_801BA5A8(p->mpUnknown796, pEntries, 179, 0);
        } else if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 22) != 0) {
            index = fn_801BA5A8(p->mpUnknown796, pEntries, 22, 0);
        }
        if (p->mUnknown776 == 1) {
            fn_801BA6BC(&pEntries[index], fn_801BA6B0(&pEntries[index]) == 0);
        }
        speed = 1.0f;
        if (fn_800CA5CC(p, 1, 1) != 0) {
            a *= fn_800CA9B4(1, p);
            b *= fn_800CA9B4(0, p);
        }
        if (pRatings[4] > 85) {
            short excess = pRatings[4] - 85;

            speed += excess / 170.0f * a;
        }
        pEntry = &pEntries[index];
        fn_801BD81C(&pEntry->mpUnknown76, fn_801CFFA0(speed));
        speed = 1.0f;
        if (pRatings[0] > 85) {
            short excess = pRatings[0] - 85;

            speed += excess / 170.0f * b;
        }
        pEntry->mUnknown44 = speed;
    } else if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 240) != 0) {
        Entry_800EAC9C *pEntries = p->mpUnknown800;

        index = fn_801BA5A8(p->mpUnknown796, pEntries, 240, 0);
        if (p->mUnknown776 == 1) {
            fn_801BA6BC(&pEntries[index], fn_801BA6B0(&pEntries[index]) == 0);
        }
    }
}

extern "C" void fn_800F1C68(Object_80039F5C *p) {
    Block_800F0C6C *pBlock = (Block_800F0C6C *)&p->mUnknown336;
    Command_800CEE74 command;
    int value;
    int unused;
    int flag;
    int index;

    if (fn_800B83A0(p) != 0) {
        p->mUnknown1008.mUnknown0 = 8;
    } else {
        p->mUnknown1008.mUnknown0 = 2;
    }
    flag = p->mUnknown776 == 1;
    fn_800CEE74(&command, p, 0, 0, 0, 229, flag);
    index = fn_800C3BEC(p, &command, &value, &unused);
    if (index != -1) {
        if (p->mMotion.mPos.mX > 0.0f) {
            pBlock->mUnknown8 = 3;
        } else {
            pBlock->mUnknown8 = 6;
        }
        fn_800C39E0(p, 229, index, value, flag);
        if (fn_801BA568(p->mpUnknown796, p->mpUnknown800, 229) != 0) {
            Entry_800EAC9C *pEntries = p->mpUnknown800;
            Entry_800EAC9C *pEntry;
            int entry = fn_801BA5A8(p->mpUnknown796, pEntries, 229, 0);
            short *pRatings = p->mRatings;
            float a = 0.4f;
            float b = 0.05f;
            float speed = 1.0f;

            if (fn_800CA5CC(p, 1, 1) != 0) {
                a = fn_800CA9B4(1, p) * a;
                b = fn_800CA9B4(0, p) * b;
            }
            if (pRatings[4] > 85) {
                short excess = pRatings[4] - 85;

                speed += excess / 170.0f * a;
            }
            pEntry = &pEntries[entry];
            fn_801BD81C(&pEntry->mpUnknown76, fn_801CFFA0(speed));
            speed = 1.0f;
            if (pRatings[0] > 85) {
                short excess = pRatings[0] - 85;

                speed += excess / 170.0f * b;
            }
            pEntry->mUnknown44 = speed;
            fn_800D0C0C(p, 0);
        }
        fn_80067E3C(48, &p->mMotion.mPos, p->mId, 0, 0, 0);
        p->mFlags |= 8;
    } else {
        fn_800D0BF4(p, 1, 34);
        fn_800F1858(p);
    }
}

extern "C" int fn_800F1EE0(Object_80039F5C *p) {
    int result = 0;
    int mode = fn_800AD9B4();

    if (fn_80137C48(p) == 0) {
        return 0;
    }
    if (mode == 3) {
        switch (p->mpState->mId) {
        case 5:
        case 10:
        case 11:
        case 12:
        case 15:
        case 16:
        case 25:
        case 26:
        case 27:
        case 35:
            result = 0;
            break;
        default:
            result = 1;
            break;
        }
        if (!(p->mFlags & 0x4000) && fn_801CFFD0(p->mMotion.mUnknown32, 0x400000) > 0x38E38E) {
            result = 0;
        }
        if ((p->mUnknown528.mUnknown15 >= 4 && p->mUnknown528.mUnknown15 <= 19) || p->mUnknown528.mUnknown15 > 21) {
            result = 0;
        }
    }
    return result;
}

extern "C" int fn_800F1FDC(Object_80039F5C *p, Object_80039F5C *pOther) {
    Object_800B26B0 *pMotion = &p->mMotion;
    float margin = fn_80178A08() - fabsf(pMotion->mPos.mX);
    int result;

    if (pOther != 0 && margin > 4.5f) {
        Point_8017886C ahead;
        float distance;

        ahead.mX = pOther->mMotion.mPos.mX;
        ahead.mY = pOther->mMotion.mPos.mY;
        fn_8022732C(&ahead, &pOther->mMotion.mUnknown40, 15.0f / lbl_803EA2C4);
        fn_80227690(&ahead, &ahead, &pMotion->mPos);
        distance = fn_802270A4(&ahead);
        if (!(pOther->mFlags & 0x800) && fn_8011E9B4(pOther) == 0) {
            if (distance < pOther->mMotion.mUnknown28 * (45.0f / lbl_803EA2C4)) {
                Point_8017886C delta;
                int heading = fn_801CFE40(pOther->mMotion.mUnknown44, pOther->mMotion.mUnknown40);

                fn_80227690(&delta, &pMotion->mPos, &pOther->mMotion.mPos);
                if (((heading - fn_801CFE40(delta.mY, delta.mX)) & 0xFFFFFF) > 0x800000) {
                    result = 1;
                } else {
                    result = 2;
                }
            } else if (pMotion->mUnknown32 < 0x400000 || pMotion->mUnknown32 > 0xC00000) {
                result = 2;
            } else {
                result = 1;
            }
        } else {
            fn_80227690(&ahead, &pOther->mMotion.mPos, &p->mMotion.mPos);
            if (((pMotion->mUnknown32 - fn_801CFE40(ahead.mY, ahead.mX)) & 0xFFFFFF) > 0x800000) {
                result = 1;
            } else {
                result = 2;
            }
        }
    } else if (margin < 4.5f) {
        if (pMotion->mPos.mX > 0.0f) {
            if (pMotion->mUnknown32 <= 0x7FFFFF) {
                result = 2;
            } else {
                result = 1;
            }
        } else if (pMotion->mUnknown32 <= 0x7FFFFF) {
            result = 1;
        } else {
            result = 2;
        }
    } else if (pMotion->mUnknown32 < 0x400000 || pMotion->mUnknown32 > 0xC00000) {
        result = 2;
    } else {
        result = 1;
    }
    return result;
}

extern "C" int fn_800F21E0(Object_80039F5C *p, Object_80039F5C *pOther, float distance) {
    Object_800B26B0 *pMotion = &p->mMotion;
    int result;

    fn_80178A08();
    if (pOther != 0) {
        Point_8017886C ahead;
        float time = 15.0f / lbl_803EA2C4;

        ahead.mX = pOther->mMotion.mPos.mX + pOther->mMotion.mUnknown40 * time;
        ahead.mY = pOther->mMotion.mPos.mY + pOther->mMotion.mUnknown44 * time;
        fn_80227690(&ahead, &ahead, &pMotion->mPos);
        fn_801CFE40(ahead.mY, ahead.mX);
        if (distance < 1.5f) {
            result = 2;
        } else {
            result = fn_802372EC(0, 2) + 2;
        }
    } else if (pMotion->mUnknown28 > lbl_803ECB08 * 0.72f) {
        result = 2;
    } else if (fn_802372EC(0, 100) < 50) {
        result = 3;
    } else {
        result = 4;
    }
    return result;
}

extern "C" int fn_800F22D8(Object_80039F5C *p, int a, int b, int c) {
    int result = 0;

    if (fn_800F1EE0(p) != 0) {
        Message_800F01CC message;

        if (b == 0 || a == 1) {
            float distance;
            int team = fn_80178320();
            Object_80039F5C *pOther = fn_801245DC(p, team, 0, fn_80178D18(fn_80178320()), 0x2E38E3, &distance, 0);

            if (b == 0) {
                b = fn_800F1FDC(p, pOther);
            }
            if (a == 1) {
                a = fn_800F21E0(p, pOther, distance);
            }
        }
        fn_800D0BF4(p, c, 34);
        result = 1;
        memset(&message, 0, 4);
        message.mId = 34;
        message.mUnknown1[0] = a;
        message.mUnknown1[1] = b;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int fn_800F23EC(Object_80039F5C *p) {
    Block_800F23EC *pBlock = (Block_800F23EC *)&p->mUnknown336;
    int kind = p->mpState->mUnknown1;

    if (kind == 0) {
        Input_800B6D34 input;
        int index;

        fn_800B6D34(p, &input);
        pBlock->mUnknown6 = kind;
        pBlock->mUnknown0 = 0.0f;
        switch (p->mpState->mUnknown2) {
        case 1:
            index = 1;
            break;
        case 2:
            index = 2;
            break;
        default:
            index = 1;
            break;
        }
        pBlock->mUnknown7 = input.mUnknown72[index] != 0.0f;
        if (pBlock->mUnknown7) {
            pBlock->mUnknown4 = 5;
        } else {
            pBlock->mUnknown4 = 10;
        }
    } else {
        pBlock->mUnknown6 = 1;
        pBlock->mUnknown4 = -1;
    }
    p->mFlags &= ~4;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = p->mUnknown512.mUnknown4;
    return 0;
}

extern "C" int fn_800F24D8(Object_80039F5C *p) {
    int result = 0;
    Block_800F23EC *pBlock = (Block_800F23EC *)&p->mUnknown336;
    Object_800B26B0 *pMotion = &p->mMotion;

    switch (pBlock->mUnknown6) {
    case 0:
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mUnknown512.mUnknown4;
        break;
    case 1:
        if (fn_800D0B90(p) == 4) {
            fn_800F1C68(p);
        } else {
            fn_800F1858(p);
        }
        p->mUnknown512.mUnknown14 = 0;
        pBlock->mUnknown6 = 2;
        fn_80067E3C(97, &pMotion->mPos, p->mId, p->mpState->mId, 0, 0);
        break;
    case 2:
        if (p->mFlags & 1) {
            p->mFlags &= ~1;
            if (fn_800C4B6C(p) == 0) {
                fn_800A5A8C(4, p, p);
            } else {
                result = 1;
            }
        }
        if (p->mFlags & 0x40000000) {
            fn_800D52F8(p);
            p->mFlags &= ~0x40000000;
        }
        if (!(p->mFlags & 4)) {
            if (p->mUnknown9[0] != 1) {
                Message_800F01CC message;

                p->mFlags &= ~0x80000;
                fn_801C1F94(&message, 0, 4);
                message.mId = 11;
                message.mUnknown1[0] = p->mUnknown9[0];
                fn_800F05E4(0, p->mpState, &message, p);
                return 1;
            }
        } else {
            p->mFlags &= ~4;
            p->mUnknown512.mUnknown14 = 1;
            result = 1;
            p->mUnknown512.mUnknown8 = pMotion->mFacing;
            p->mUnknown512.mUnknown4 = pMotion->mFacing;
            p->mUnknown512.mUnknown0 = 0.72f;
        }
        break;
    }
    return result;
}

extern "C" int fn_800F268C(Object_80039F5C *p) {
    Block_800F23EC *pBlock = (Block_800F23EC *)&p->mUnknown336;

    if (pBlock->mUnknown6 == 0) {
        Input_800B6D34 input;
        int bit;
        int index;

        pBlock->mUnknown4--;
        pBlock->mUnknown4 = pBlock->mUnknown4 < 0 ? 0 : pBlock->mUnknown4;
        fn_800B6D34(p, &input);
        switch (p->mpState->mUnknown2) {
        case 1:
            bit = 7;
            index = 1;
            break;
        case 2:
            bit = 6;
            index = 2;
            break;
        default:
            bit = 5;
            index = 1;
            break;
        }
        if (pBlock->mUnknown7 != 0) {
            float value = input.mUnknown72[index] <= 1.0f ? input.mUnknown72[index] : 1.0f;

            if (value != 1.0f) {
                if (value < pBlock->mUnknown0 || pBlock->mUnknown4 == 0) {
                    p->mpState->mUnknown1 = 3;
                    pBlock->mUnknown6 = 1;
                } else {
                    pBlock->mUnknown0 = value;
                }
            } else {
                p->mpState->mUnknown1 = 4;
                pBlock->mUnknown6 = 1;
            }
        } else {
            float time = pBlock->mUnknown4 * 0.1f;

            if (time < 0.5f) {
                p->mpState->mUnknown1 = 4;
                pBlock->mUnknown6 = 1;
            } else if ((input.mUnknown92[(unsigned int)bit >> 3] & (1 << bit)) != (1 << bit)) {
                if (time >= 0.5f) {
                    p->mpState->mUnknown1 = 3;
                }
                pBlock->mUnknown6 = 1;
            }
        }
    }
    return 0;
}

extern "C" int fn_800F2828(Object_80039F5C *a, int b) {
    return fn_801250B8(a, b, 6) < lbl_803EAE1C;
}

extern "C" int fn_800F285C(Object_80039F5C *p) {
    if (fn_800AD9B4() != 3) {
        return 0;
    }
    switch (p->mpState->mId) {
        case 5:
        case 10:
        case 11:
        case 15:
        case 16:
        case 17:
        case 25:
        case 26:
        case 27:
        case 32:
        case 34:
        case 35:
        case 36:
        case 43:
        case 51:
        case 91:
        return 0;
    }
    return 1;
}

extern "C" int fn_800F2920(Object_80039F5C *p) {
    int id = p->mId;

    if ((id & 0xFF) == 1 && ((id >> 8) & 0xFF) == fn_80178320() && p->mUnknown1032 == 4) {
        Object_80039F5C *pTarget = fn_8009BCE8(&p->mUnknown1036);

        if (pTarget != 0) {
            Query_800CE770 query;

            fn_800CE770(&query);
            query.mUnknown36 = 0xE38E3;
            query.mUnknown52 = 66;
            query.mUnknown44 = 0.4f;
            query.mpUnknown0 = pTarget;
            query.mpUnknown4 = p;
            if (fn_800CE4A8(&query) != 0) {
                float skill;

                fn_8011E1BC(pTarget, p, 0, 5);
                fn_8011E33C(p, pTarget, 5);
                skill = p->mRatings[0] / 255.0f;
                p->mUnknown772 = fn_800C49A4(p, skill * 0.5f + 0.5f);
                return 1;
            }
        }
    }
    return 0;
}

extern "C" int fn_800F2A40(Object_80039F5C *p) {
    Object_80039F5C *pOther = fn_80137B40();

    if (pOther != 0) {
        Point_8017886C delta;

        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mFacing);
    }
    return 1;
}

extern "C" int fn_800F2AA0(Object_80039F5C *p) {
    Block_800F2AA0 *pBlock = (Block_800F2AA0 *)&p->mUnknown336;
    float skill;

    if (p->mFlags & 0x4000) {
        pBlock->mUnknown0 = 1;
    } else {
        pBlock->mUnknown0 = 0;
    }
    fn_8009BD60(p);
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 68, p, 1.0f);
    p->mFlags &= ~4;
    skill = p->mRatings[0] / 255.0f;
    skill = skill <= 1.0f ? skill : 1.0f;
    p->mUnknown772 = fn_800C49A4(p, skill * 0.7f + 0.3f);
    p->mUnknown9[0] = 1;
    p->mUnknown512.mUnknown14 = 0;
    return 0;
}

extern "C" int fn_800F2B8C(Object_80039F5C *p) {
    if (fn_801BE648(p->mpUnknown792) != 68 || (p->mFlags & 4)) {
        p->mFlags &= ~4;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.4f;
        p->mUnknown772 = 1.0f;
        return 1;
    }
    return 0;
}

extern "C" int fn_800F2C14() {
    return 0;
}

extern "C" int fn_800F2C1C(Object_80039F5C *p, int a) {
    if (fn_800F285C(p) != 0) {
        if ((p->mId & 0xFF) == 1 && p->mUnknown1032 == 4) {
            return fn_800F2920(p);
        } else {
            Message_800F01CC message;

            memset(&message, 0, 4);
            message.mId = 5;
            message.mUnknown1[0] = a;
            fn_800F00D4(0, p->mpState, &message, p);
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_800F2CB4(Table_80089904 *pTable, unsigned short event, void *a, void *b, Object_80039F5C *p, int skip) {
    int found = 0;

    if (skip == 0) {
        int best = -1;
        int bestScore = 0;
        int kind = p->mpState->mUnknown1;
        Key_800F2CB4 key;
        Vector_80039F5C delta;
        int i;

        if (p->mMotion.mUnknown28 > lbl_803ECB08 * 0.4f) {
            key.mUnknown0 = 2;
        } else {
            key.mUnknown0 = 1;
        }
        key.mUnknown2 = fn_800F2A40(p);
        fn_80137D58(fn_801374BC(), &delta);
        fn_80227690(&delta, &delta, &p->mMotion.mPos);
        key.mUnknown1 = lbl_803EAE20[((fn_801CFE40(delta.mY, delta.mX) - p->mMotion.mFacing) >> 21) & 7];
        for (i = 0; i < pTable->mCount; i++) {
            Info_80089904 *pInfo = pTable->mEntries[i].mpInfo;
            int score;

            if (key.mUnknown0 != pInfo->mValue) {
                continue;
            }
            score = 1;
            if (key.mUnknown1 == pInfo->mType) {
                score = 3;
            } else if (pInfo->mType == 1) {
                score = 2;
            }
            if (key.mUnknown2 != pInfo->mUnknown6) {
                score = 0;
            }
            if (kind != 0) {
                if (pInfo->mUnknown7 == 1) {
                    score = 0;
                }
            } else if (pInfo->mUnknown7 == 2) {
                score = 0;
            }
            if (score < bestScore) {
                continue;
            }
            if (score > bestScore) {
                bestScore = score;
                found = pInfo->mUnknown7 == 2;
                best = i;
            } else if (fn_802372EC(0, 100) < 50) {
                best = i;
            }
        }
        if (bestScore == 0) {
            best = 0;
        }
        if (found) {
            p->mpState->mUnknown2 = 1;
        } else {
            p->mpState->mUnknown2 = 0;
        }
        fn_801BA2A8(a, b, pTable->mEntries[best].mUnknown0, pTable->mEntries[best].mUnknown2, event, p, 1.0f);
    }
    return 0;
}

extern "C" Object_80039F5C *fn_800F2EC8(Object_80039F5C *pExclude, Points_800F3A6C *pInfo) {
    Object_80039F5C *pBest = 0;
    unsigned char index = 0;
    unsigned int i;

    for (i = 0; i < 4; i++) {
        Object_80039F5C *p = fn_8015286C(lbl_8031BDD4, i);

        if (p == pExclude || fn_801520C4(p, &index) == 0 || pInfo->mpUnknown0 != fn_80137ABC(index)) {
            continue;
        }
        if (pBest == 0) {
            pBest = p;
        } else {
            float distance = fn_8022781C(&pInfo->mUnknown4, &p->mMotion.mPos);
            float bestDistance = fn_8022781C(&pInfo->mUnknown4, &pBest->mMotion.mPos);

            if (distance <= 8.0f && bestDistance <= 8.0f) {
                if (p->mMotion.mPos.mY < pBest->mMotion.mPos.mY) {
                    pBest = p;
                }
            } else if (distance < bestDistance) {
                pBest = p;
            }
        }
    }
    return pBest;
}

extern "C" int fn_800F2FB8(Object_80039F5C *p, unsigned char *pIndex) {
    int result = 0;

    *pIndex = 0;
    if (fn_8015310C(lbl_8031BDD4) != 0) {
        result = fn_801520C4(p, pIndex);
        if (result != 0) {
            Vector_80039F5C ball;

            fn_80137D58(fn_80137ABC(*pIndex), &ball);
            if ((ball.mX > fn_80178A08() + 3.0f && p->mMotion.mPos.mX > fn_80178A08() - 2.0f)
                || (ball.mX < -fn_80178A08() - 3.0f && p->mMotion.mPos.mX < 2.0f - fn_80178A08())) {
                result = 0;
            }
        }
    }
    return result;
}

extern "C" void fn_800F30AC(Object_80039F5C *p, Object_80039F5C *pOther, Points_800F3A6C *pInfo) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;
    Vector_80039F5C target = pInfo->mUnknown16;
    Vector_80039F5C origin = pInfo->mUnknown4;
    Vector_80039F5C delta;
    int heading;
    int angle;
    int turn;
    int result;

    fn_80227690(&delta, &origin, &target);
    heading = fn_801CFE40(delta.mY, delta.mX);
    if (pOther != 0) {
        fn_80227690(&delta, &origin, &pOther->mMotion.mPos);
        if (fn_802270A4(&delta) > 2.0f) {
            angle = fn_801CFE40(delta.mY, delta.mX);
            turn = fn_801CFFD0(heading, angle);
            if (turn <= 0x1FFFFF) {
                result = 0;
            } else if (turn > 0x600000) {
                result = 1;
            } else if (((heading - angle) & 0xFFFFFF) <= 0x7FFFFF) {
                result = 2;
            } else {
                result = 3;
            }
        } else {
            result = 4;
        }
    } else {
        result = 1;
    }
    pBlock->mUnknown24 = result;
    fn_80227690(&delta, &origin, &p->mMotion.mPos);
    if (fn_802270A4(&delta) > 2.0f) {
        angle = fn_801CFE40(delta.mY, delta.mX);
        turn = fn_801CFFD0(heading, angle);
        if (turn <= 0x1FFFFF) {
            result = 0;
        } else if (turn > 0x600000) {
            result = 1;
        } else if (((heading - angle) & 0xFFFFFF) <= 0x7FFFFF) {
            result = 2;
        } else {
            result = 3;
        }
    } else {
        result = 4;
    }
    pBlock->mUnknown20 = result;
}

extern "C" void fn_800F3284(Object_80039F5C *p, Block_800F4A74 *pBlock, Points_800F3A6C *pInfo) {
    Object_80039F5C *pOther = fn_800F2EC8(p, pInfo);

    if (pOther == 0) {
        pBlock->mUnknown49 = 0;
        pBlock->mUnknown51 = 0;
    } else {
        pBlock->mUnknown49 = 1;
        pBlock->mUnknown51 = 1;
    }
    pBlock->mUnknown58 = 0;
    pBlock->mUnknown50 = 2;
    pBlock->mUnknown44 = 0.0f;
    pBlock->mUnknown56 = fn_802372EC(0, 100);
    pBlock->mUnknown52 = 0;
    pBlock->mUnknown53 = 0;
    pBlock->mUnknown54 = 0;
    pBlock->mUnknown48 = 0;
    pBlock->mUnknown57 = 0;
    pBlock->mUnknown61 = 0;
    pBlock->mUnknown55 = 0;
    pBlock->mUnknown60 = 1;
    fn_8009A8D4(pBlock);
    fn_800F30AC(p, pOther, pInfo);
}

extern "C" void fn_800F3344(Object_80039F5C *p, Object_80039F5C *pOther, Block_800F4A74 *pBlock) {
    Object_80137ABC *pBall = fn_80137ABC(pBlock->mUnknown62);
    int result = pBlock->mUnknown49;

    if (pOther != 0 && fn_800AC3FC(p, pBlock->mUnknown56) == 0) {
        Vector_80039F5C start;
        Vector_80039F5C target;
        Vector_80039F5C velocity;
        Point_8017886C delta;
        Point_8017886C apart;
        Point_8017886C ahead;
        float ballTime;
        float otherTime;
        float time;
        float distance;

        fn_80138064(pBall, &start);
        fn_80137D58(pBall, &target);
        fn_80137EC4(pBall, &velocity);
        fn_80227690(&delta, &start, &target);
        ballTime = fn_802270A4(&delta) / fn_802270A4(&velocity);
        fn_80227690(&delta, &start, &pOther->mMotion.mPos);
        otherTime = fn_802270A4(&delta)
            / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (pOther->mRatings[4] / 255.0f) + lbl_803ED6CC));
        fn_80227690(&delta, &start, &p->mMotion.mPos);
        time = fn_802270A4(&delta) / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        distance = fn_802270A4(&delta);
        fn_80227690(&apart, &p->mMotion.mPos, &pOther->mMotion.mPos);
        fn_80227690(&ahead, &target, &pOther->mMotion.mPos);
        if (pOther->mpState->mId == 28 && fn_80137C48(pOther) == pBall) {
            Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;

            if (pPass->mUnknown0 < pPass->mUnknown16) {
                otherTime = pPass->mUnknown16 - pPass->mUnknown0;
                fn_80227690(&delta, &pPass->mUnknown4, &target);
                ballTime = fn_802270A4(&delta) / fn_802270A4(&velocity);
                fn_80227690(&delta, &pPass->mUnknown4, &p->mMotion.mPos);
                time = fn_802270A4(&delta)
                    / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
            }
        }
        switch (pBlock->mUnknown20) {
        case 0:
            if (ballTime <= time - 5.0f) {
                result = 1;
            } else {
                switch (pBlock->mUnknown24) {
                case 0:
                    result = p->mMotion.mPos.mY <= pOther->mMotion.mPos.mY;
                    break;
                case 1:
                    result = 0;
                    break;
                case 2:
                case 3:
                    result = 0;
                    break;
                case 4:
                    result = 0;
                    break;
                }
            }
            break;
        case 1:
            switch (pBlock->mUnknown24) {
            case 1:
                result = 1;
                if (time < otherTime && pBlock->mUnknown54 == 0) {
                    result = 0;
                }
                break;
            case 0:
                result = 0;
                break;
            case 2:
            case 3:
                result = 0;
                break;
            case 4:
                result = 1;
                break;
            }
            break;
        case 4:
            switch (pBlock->mUnknown24) {
            case 4:
                result = p->mMotion.mPos.mY < pOther->mMotion.mPos.mY;
                break;
            case 0:
                result = 0;
                break;
            case 1:
                result = 0;
                break;
            case 2:
            case 3:
                result = 0;
                break;
            }
            break;
        case 2:
        case 3:
            switch (pBlock->mUnknown24) {
            case 0:
                {
                    int angle = fn_801CFE40(velocity.mY, velocity.mX);

                    if ((fn_801CFFD0(angle, pOther->mMotion.mUnknown32) <= 0x3FFFFF
                         && fn_801CFFD0(angle, p->mMotion.mUnknown32) > 0x400000 && distance > 2.0f)
                        || (pBlock->mUnknown49 == 0 && velocity.mZ < 0.0f)) {
                        result = pOther->mMotion.mPos.mY >= p->mMotion.mPos.mY;
                    } else {
                        result = 1;
                    }
                }
                break;
            case 2:
            case 3:
                result = time < otherTime;
                break;
            case 4:
                result = 1;
                break;
            case 1:
                result = time >= otherTime;
                break;
            }
            break;
        }
    } else {
        result = 0;
    }
    if (result != pBlock->mUnknown49) {
        pBlock->mUnknown50 = pBlock->mUnknown49;
        pBlock->mUnknown49 = result;
    }
}

extern "C" void fn_800F3838(Object_80039F5C *p, Object_80039F5C *pOther, Points_800F3A6C *pInfo) {
    Object_800B26B0 *pMotion;
    Point_8017886C delta;
    int angle;
    float distance;
    float strength;

    if (pOther == 0) {
        return;
    }
    pMotion = &p->mMotion;
    fn_80227690(&delta, &pOther->mMotion.mPos, &pMotion->mPos);
    angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    distance = fn_802270A4(&delta);
    if (fn_801CFFD0(angle, pMotion->mFacing) > 0x555554 && distance >= 3.5f) {
        return;
    }
    strength = 0.0f;
    if (pMotion->mPos.mY > pOther->mMotion.mPos.mY) {
        if (distance < 8.0f) {
            distance -= 1.0f;
            if (distance < 0.0f) {
                distance = 0.0f;
            }
            strength = distance / 8.0f;
            strength = 1.0f - strength;
        }
        if (fn_801CFFD0(pMotion->mFacing, 0x400000) <= 0x1FFFFF && fn_8013BA58(pInfo->mpUnknown0, 0) == 4) {
            fn_80227690(&delta, &pInfo->mUnknown16, &pMotion->mPos);
            angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        }
    } else if (distance < 2.5f) {
        distance -= 1.0f;
        if (distance < 0.0f) {
            distance = 0.0f;
        }
        strength = distance / 2.5f;
        strength = 1.0f - strength;
    }
    if (strength != 0.0f) {
        fn_800C89F0(p, angle, 2, 0, strength);
    }
}

extern "C" void fn_800F39FC(Points_800F3A6C *pInfo, int index) {
    pInfo->mpUnknown0 = fn_80137ABC(index);
    fn_80138064(pInfo->mpUnknown0, &pInfo->mUnknown4);
    fn_8013AA00(pInfo->mpUnknown0, &pInfo->mUnknown48, &pInfo->mUnknown40, 1.5f);
    fn_80137EC4(pInfo->mpUnknown0, &pInfo->mUnknown28);
    fn_80137D58(pInfo->mpUnknown0, &pInfo->mUnknown16);
}

extern "C" void fn_800F3A6C(Object_80039F5C *pA, Object_80039F5C *pB, Info_800F3A6C *pInfo, Points_800F3A6C *pPoints) {
    Point_8017886C delta;

    fn_80227690(&pInfo->mUnknown0, &pPoints->mUnknown16, &pB->mMotion.mPos);
    pInfo->mUnknown16 = fn_801CFE40(pInfo->mUnknown0.mY, pInfo->mUnknown0.mX);
    fn_80227690(&pInfo->mUnknown8, &pA->mMotion.mPos, &pB->mMotion.mPos);
    pInfo->mUnknown20 = fn_801CFE40(pInfo->mUnknown8.mY, pInfo->mUnknown8.mX);
    pInfo->mUnknown32 = fn_802270A4(&pInfo->mUnknown8);
    fn_80227690(&delta, &pPoints->mUnknown4, &pB->mMotion.mPos);
    pInfo->mUnknown24 = fn_801CFE40(delta.mY, delta.mX);
    pInfo->mUnknown36 = fn_802270A4(&delta);
    fn_80227690(&delta, &pPoints->mUnknown4, &pA->mMotion.mPos);
    pInfo->mUnknown28 = fn_801CFE40(delta.mY, delta.mX);
    pInfo->mUnknown40 = fn_802270A4(&delta);
}

extern "C" void fn_800F3B54(Object_80039F5C *p, Object_80039F5C *pOther, Block_800F4A74 *pBlock, Info_800F3A6C *pInfo,
                            Points_800F3A6C *pPoints) {
    float progress = 0.0f;
    int passing = 0;

    if (pOther->mpState->mId == 28) {
        Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;

        passing = 1;
        progress = (float)pPass->mUnknown0 / (float)pPass->mUnknown16;
    }
    if ((pInfo->mUnknown32 < 2.5f || (passing && progress > 0.6f)) && pPoints->mUnknown28.mZ < 0.0f
        && (pPoints->mUnknown16.mZ < 5.0f || pInfo->mUnknown40 > pInfo->mUnknown36
            || fabsf(p->mMotion.mPos.mX) > fabsf(pOther->mMotion.mPos.mX))) {
        Point_8017886C delta;
        Point_8017886C toTarget;
        int heading;
        int turn;

        fn_80227690(&delta, &pPoints->mUnknown40, &p->mMotion.mPos);
        fn_802270A4(&delta);
        heading = (pInfo->mUnknown20 + 0x800000) & 0xFFFFFF;
        fn_80227690(&toTarget, &pPoints->mUnknown16, &p->mMotion.mPos);
        turn = fn_801CFFD0(heading, fn_801CFE40(toTarget.mY, toTarget.mX));
        if (turn <= 0x18E38D
            || (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.0f && passing && progress > 0.5f && turn <= 0x1FFFFF)) {
            pBlock->mUnknown54 = 1;
        }
    }
}

extern "C" void fn_800F3D38(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Point_8017886C *pAim,
                            Info_800F3A6C *pInfo, Points_800F3A6C *pPoints, float *pValue) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;
    Object_80137ABC *pBall = fn_80137ABC(pBlock->mUnknown62);
    Point_8017886C delta;
    Point_8017886C lead;

    pTarget->mX = pPoints->mUnknown40.mX;
    delta.mY = 0.0f;
    pTarget->mY = pPoints->mUnknown40.mY;
    delta.mX = 0.0f;
    pAim->mX = pTarget->mX;
    pAim->mY = pTarget->mY;
    if (fn_801CFFD0(pOther->mMotion.mUnknown32, 0) != 0) {
        fn_80227690(&delta, &pOther->mMotion.mPos, &pBall->mState.mPos);
    }
    if (pOther->mpState->mId == 28 && fn_80137C48(pOther) == pBall) {
        Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;

        fn_80227538(&lead, fn_801CFE40(delta.mY, delta.mX), 0.5f);
        if (pPass->mUnknown0 < pPass->mUnknown16) {
            pAim->mX = pPass->mUnknown4.mX;
            pAim->mY = pPass->mUnknown4.mY;
            fn_80227690(pAim, pAim, &lead);
        }
    } else {
        Point_8017886C back;

        pBlock->mUnknown55 = 1;
        pBlock->mUnknown58 = 0;
        fn_80227538(&lead, fn_801CFE40(delta.mY, delta.mX), 1.5f);
        fn_80227690(pAim, pTarget, &lead);
        fn_80227690(&back, pAim, &p->mMotion.mPos);
        if (fn_801CFFD0(fn_801CFE40(back.mY, back.mX), p->mMotion.mUnknown32) > 0x471C72) {
            int turn = fn_801CFFD0(pOther->mMotion.mUnknown32, p->mMotion.mUnknown32);

            if ((float)fn_801CFFD0(pOther->mMotion.mUnknown32, 0x400000) > 35.0f && pOther->mMotion.mUnknown28 > 0.0f) {
                if (turn <= 0x155554) {
                    fn_80227538(&back, pOther->mMotion.mUnknown32, 0.5f);
                    fn_80227638(pAim, &p->mMotion.mPos, &back);
                }
            } else {
                pAim->mX = pPoints->mUnknown40.mX;
                pAim->mY = pPoints->mUnknown40.mY;
                pBlock->mUnknown55 = 0;
            }
        }
    }
}

extern "C" void fn_800F3F90(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Point_8017886C *pAim,
                            Points_800F3A6C *pPoints) {
    if (p != 0 && pOther != 0 && pTarget != 0 && pAim != 0 && pPoints != 0) {
        if (pOther->mpState->mId == 28) {
            Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;

            if (pPass != 0) {
                pTarget->mX = pPass->mUnknown4.mX;
                pTarget->mY = pPass->mUnknown4.mY;
            }
        } else {
            pTarget->mX = pPoints->mUnknown40.mX;
            pTarget->mY = pPoints->mUnknown40.mY;
            pTarget->mY -= 1.0f;
        }
        pAim->mX = pTarget->mX;
        pAim->mY = pTarget->mY;
    } else if (pPoints != 0 && pAim != 0) {
        pAim->mX = pPoints->mUnknown40.mX;
        pAim->mY = pPoints->mUnknown40.mY;
    }
}

extern "C" void fn_800F4038(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Point_8017886C *pAim,
                            Points_800F3A6C *pPoints, Info_800F3A6C *pInfo, float value) {
    Point_8017886C toAim;
    Point_8017886C toBall;
    Point_8017886C toOther = {0.0f, 0.0f};
    Point_8017886C apart;
    Point_8017886C passDelta;
    Point_8017886C ballDir;
    Point_8017886C otherDir;
    Point_8017886C sum;
    Block_800F4A74 *pBlock;
    float otherTime = 0.0f;
    float ballTime;
    float time;
    float scale;
    float needed;
    int cut = 0;

    fn_80227690(&toAim, pAim, &p->mMotion.mPos);
    pBlock = (Block_800F4A74 *)&p->mUnknown336;
    fn_80227690(&toBall, pTarget, &pPoints->mUnknown16);
    ballTime = fn_802270A4(&toBall) / fn_802270A4(&pPoints->mUnknown28);
    time = fn_802270A4(&toAim)
         / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
    if (pOther != 0) {
        fn_80227690(&toOther, pTarget, &pOther->mMotion.mPos);
        fn_80227690(&apart, &pOther->mMotion.mPos, &p->mMotion.mPos);
        otherTime = fn_802270A4(&toOther)
                  / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (pOther->mRatings[4] / 255.0f) + lbl_803ED6CC));
    } else {
        toOther.mY = 0.0f;
        toOther.mX = 0.0f;
        apart.mY = 0.0f;
        apart.mX = 0.0f;
    }
    if (pOther != 0 && pOther->mpState->mId == 28) {
        Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;

        ballTime = pPass->mUnknown16 - pPass->mUnknown0;
        fn_80227690(&passDelta, &pPass->mUnknown4, &p->mMotion.mPos);
        time = fn_802270A4(&passDelta)
             / (lbl_803ECB08 * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
    }
    if (pBlock->mUnknown49 == 1) {
        if (time < otherTime && fn_802270A4(&apart) < 2.0f && fn_802270A4(&toAim) < fn_802270A4(&toOther)) {
            scale = time / 1.5f;
        } else {
            scale = ballTime;
            if (pBlock->mUnknown55 != 0) {
                scale = time;
            }
        }
        scale *= value;
    } else {
        scale = ballTime;
    }
    pBlock->mUnknown28 = pAim->mX;
    pBlock->mUnknown32 = pAim->mY;
    needed = scale > 0.0f ? fn_802270A4(&toAim) / scale : 0.0f;
    if (needed > p->mMotion.mUnknown36) {
        scale = 1.0f;
    } else if (p->mMotion.mUnknown36 != 0.0f) {
        scale = needed / p->mMotion.mUnknown36;
    } else {
        scale = 0.0f;
    }
    pBlock->mUnknown36 = fn_801CFE40(toAim.mY, toAim.mX) & 0xFFFFFF;
    if (pOther != 0) {
        if (otherTime < ballTime - 2.5f || (otherTime < 12.0f && ballTime < 12.0f)
            || p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.5f) {
            if (fn_802270A4(&toAim) < 7.0f) {
                cut = 1;
            }
        }
        if (fn_801CFFD0(p->mMotion.mUnknown32, 0x400000) <= 0x1C71C6 && scale > 0.9f && fn_802270A4(&apart) < 5.0f
            && p->mMotion.mPos.mY < pOther->mMotion.mPos.mY + 5.0f
            && fn_801CFFD0(pBlock->mUnknown40, 0x400000) <= 0x1C71C6) {
            cut = 0;
        }
        if (cut != 0 && fn_801CFFD0(p->mMotion.mUnknown32, 0x400000) <= 0x1C71C6) {
            if (fn_802270A4(&apart) > 10.0f
                || fn_801CFFD0(pOther->mMotion.mUnknown32, fn_801CFE40(toOther.mY, toOther.mX)) > 0x155555) {
                cut = 0;
            }
        }
    }
    if (pOther != 0 && cut != 0) {
        fn_80227690(&ballDir, &pPoints->mUnknown16, &p->mMotion.mPos);
        fn_80227690(&otherDir, &pOther->mMotion.mPos, &p->mMotion.mPos);
        fn_802271A4(&ballDir, &ballDir);
        fn_802271A4(&otherDir, &otherDir);
        if (fn_801CFFD0(p->mMotion.mFacing, 0x400000) <= 0x18E38D && pBlock->mUnknown49 != 0) {
            ballDir.mX *= 0.35f;
            ballDir.mY = 0.0f;
            otherDir.mX *= 0.65f;
            otherDir.mY *= 0.65f;
        } else {
            switch (pBlock->mUnknown49) {
            case 0:
            case 1:
                otherDir.mX = 0.0f;
                otherDir.mY = 0.0f;
                break;
            }
        }
        fn_80227638(&sum, &ballDir, &otherDir);
        pBlock->mUnknown40 = fn_801CFE40(sum.mY, sum.mX);
    } else {
        int turn;

        pBlock->mUnknown40 = pBlock->mUnknown36;
        turn = fn_801CFFD0(pBlock->mUnknown40, p->mMotion.mFacing);
        if (turn > 0x400000) {
            scale = fn_801CFB94(turn / 2) * 0.72f;
            pBlock->mUnknown60 = 0;
        }
    }
    if (scale < 1e-07f) {
        scale = 0.0f;
    }
    pBlock->mUnknown44 = scale;
}

extern "C" void fn_800F4690(Object_80039F5C *p, Object_80039F5C *pOther, Points_800F3A6C *pPoints) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;

    if (pBlock->mUnknown44 != 0.0f) {
        if (pBlock->mUnknown52 == 1 && pBlock->mUnknown36 == pBlock->mUnknown40) {
            pBlock->mUnknown48 = 12;
        }
        if (pBlock->mUnknown60 == 1 && pBlock->mUnknown44 >= 0.72f && pBlock->mUnknown36 == pBlock->mUnknown40
            && fn_801CFFD0(p->mMotion.mFacing, pBlock->mUnknown36) <= 0xE38E2
            && fn_801CFFD0(p->mMotion.mUnknown32, pBlock->mUnknown36) <= 0xE38E2) {
            pBlock->mUnknown48 = 1;
        }
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown36;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown40;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown44;
    }
    p->mUnknown512.mUnknown15 = pBlock->mUnknown48;
    if (pBlock->mUnknown40 == pBlock->mUnknown36 && p->mMotion.mUnknown28 > lbl_803ECB08 * 0.05f
        && fn_801CFFD0(p->mMotion.mUnknown32, pBlock->mUnknown40) > 0x2E38E3
        && fn_801CFFD0(p->mMotion.mFacing, 0xC00000) <= 0x2AAAA9) {
        pBlock->mUnknown44 = 0.0f;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown36;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown40;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown44;
        pBlock->mUnknown58 = 2;
    }
    if (pBlock->mUnknown53 == 1) {
        fn_800F3838(p, pOther, pPoints);
    }
}

extern "C" void fn_800F4838(Object_80039F5C *p) {
    Point_8017886C target = {0.0f, 0.0f};
    Point_8017886C delta;
    Block_800F4A74 *pBlock;

    fn_801528E0(lbl_8031BDD4, &target);
    fn_80227690(&delta, &target, &p->mMotion.mPos);
    pBlock = (Block_800F4A74 *)&p->mUnknown336;
    pBlock->mUnknown36 = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    if (fn_8022781C(&p->mMotion.mPos, &target) < 15.0f) {
        pBlock->mUnknown40 = 0xC00000;
        pBlock->mUnknown44 = 0.0f;
    } else {
        pBlock->mUnknown40 = pBlock->mUnknown36;
        pBlock->mUnknown44 = 1.0f;
    }
    p->mUnknown512.mUnknown14 = 3;
    p->mUnknown512.mUnknown4 = pBlock->mUnknown36;
    p->mUnknown512.mUnknown8 = pBlock->mUnknown40;
    p->mUnknown512.mUnknown0 = pBlock->mUnknown44;
}

extern "C" void fn_800F4918(Object_80039F5C *p, Object_80039F5C *pOther, Points_800F3A6C *pPoints, int value) {
    int choice = 0x1FFFFFFF;
    int a = 0;
    int b = 0;
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;
    int mode;
    float range;
    float height;

    if ((p->mFlags & 0x4000) == 0) {
        mode = 3;
    } else {
        mode = 1;
    }
    if (p->mUnknown8 == 255) {
        range = 120.0f;
    } else {
        range = 17.0f;
    }
    fn_801380AC(fn_80137ABC(pBlock->mUnknown62), &height);
    if (fn_8009A6EC(p) != 0) {
        choice = fn_800997F4(p, fn_80137ABC(pBlock->mUnknown62), range, pBlock, 3, 0, 0, &a, &b);
    }
    if (choice == 0x1FFFFFFF) {
        choice = fn_80099734(p, fn_80137ABC(pBlock->mUnknown62), 0, mode, pBlock, 1, 0, 0, 0, range);
        if (choice == 0x1FFFFFFF) {
            return;
        }
    }
    if (((choice >> 29) & 3) == 1) {
        fn_8009A1A8(p, choice, a, b, pBlock->mUnknown62);
    } else {
        fn_80099F04(p, choice, pBlock->mUnknown62);
    }
}

extern "C" int fn_800F4A74(Object_80039F5C *p) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;

    memset(pBlock, 0, 88);
    pBlock->mUnknown62 = fn_801374E0(fn_801374BC());
    pBlock->mUnknown63 = 0;
    pBlock->mUnknown36 = 0;
    pBlock->mUnknown40 = 0xC00000;
    return 0;
}

extern "C" int fn_800F4AD4(Object_80039F5C *p) {
    if (p->mUnknown8 == 255) {
        Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;
        Points_800F3A6C points;
        Info_800F3A6C info;
        Point_8017886C target;
        Point_8017886C aim;
        float value;
        Object_80039F5C *pOther;

        if (pBlock->mUnknown63 != 0) {
            fn_800F39FC(&points, pBlock->mUnknown62);
            if (fn_8013BA58(points.mpUnknown0, 0) != 4) {
                pBlock->mUnknown63 = 0;
            }
        }
        if (pBlock->mUnknown63 == 0) {
            pBlock->mUnknown63 = fn_800F2FB8(p, &pBlock->mUnknown62);
            if (pBlock->mUnknown63 != 0) {
                fn_800F39FC(&points, pBlock->mUnknown62);
                fn_800F3284(p, pBlock, &points);
            }
        }
        if (pBlock->mUnknown63 != 0) {
            pOther = fn_800F2EC8(p, &points);
            if (--pBlock->mUnknown58 < 0) {
                int rating;
                int spread;
                int delay;

                value = 1.0f;
                target.mY = 0.0f;
                target.mX = 0.0f;
                aim.mY = 0.0f;
                aim.mX = 0.0f;
                rating = p->mRatings[3];
                if (p->mRatings[8] > rating) {
                    rating = p->mRatings[8];
                }
                spread = 255 - rating;
                if (spread < 0) {
                    spread = 0;
                }
                delay = fn_802372EC(0, spread >> 5) + fn_800AC3A0(p);
                pBlock->mUnknown48 = 0;
                pBlock->mUnknown52 = 0;
                pBlock->mUnknown53 = 0;
                pBlock->mUnknown54 = 0;
                pBlock->mUnknown55 = 0;
                pBlock->mUnknown61 = 0;
                pBlock->mUnknown58 = delay;
                pBlock->mUnknown60 = 1;
                if (fn_801783AC(11) == 0) {
                    fn_801783AC(12);
                }
                if (pOther != 0) {
                    fn_800F3A6C(p, pOther, &info, &points);
                    fn_800F3B54(p, pOther, pBlock, &info, &points);
                }
                fn_800F3344(p, pOther, pBlock);
                switch (pBlock->mUnknown49) {
                case 0:
                    fn_800F3F90(p, pOther, &target, &aim, &points);
                    pBlock->mUnknown60 = 1;
                    break;
                case 1:
                    fn_800F3D38(p, pOther, &target, &aim, &info, &points, &value);
                    pBlock->mUnknown60 = 1;
                    break;
                }
                aim.mX = aim.mX < 1.0f - fn_80178A08() ? 1.0f - fn_80178A08()
                       : (aim.mX > fn_80178A08() - 1.0f ? fn_80178A08() - 1.0f : aim.mX);
                aim.mY = aim.mY < 1.0f - fn_80178A44() ? 1.0f - fn_80178A44()
                       : (aim.mY <= fn_80178A44() - 1.0f ? aim.mY : fn_80178A44() - 1.0f);
                fn_800F4038(p, pOther, &target, &aim, &points, &info, value);
            }
            fn_800F4690(p, pOther, &points);
            fn_800F4918(p, pOther, &points, 0);
        } else {
            fn_800F4838(p);
        }
    }
    return 0;
}

extern "C" int fn_800F4E14(Object_80039F5C *p, Object_800F4E14 *pInfo) {
    int result = 0;

    if (fn_801BE648(p->mpUnknown792) == 86) {
        fn_800F0BF8(p, 4, pInfo->mUnknown20);
        result = 1;
    } else if (fn_801BE648(p->mpUnknown792) == 85) {
        fn_800DD648(p);
    }
    return result;
}

extern "C" int fn_800F4E88(Object_80039F5C *p, Record_800F4E88 *pRecord) {
    Point_8017886C delta;
    Point_8017886C direction;

    delta.mX = pRecord->mUnknown0.mX - p->mMotion.mPos.mX;
    delta.mY = pRecord->mUnknown0.mY - p->mMotion.mPos.mY;
    fn_80227538(&direction, pRecord->mUnknown20, pRecord->mUnknown8);
    return fn_802276E8(&delta, &direction) <= 0.0f;
}

extern "C" void fn_800F4F08(Object_80039F5C *p, Record_800F4E88 *pRecord) {
    Object_800B26B0 *pMotion = &p->mMotion;
    Point_8017886C goal;
    Object_80039F5C *pCarrier;

    goal = fn_80177FE0();
    pCarrier = fn_80137B40();

    if (pMotion->mPos.mY > goal.mY && fn_8011F1A4() != 0) {
        float x;

        if (pCarrier != 0 && fn_8011F4C8() > 3) {
            if (p->mMotion.mPos.mX > goal.mX) {
                x = pCarrier->mMotion.mPos.mX - 1.0f;
            } else {
                x = pCarrier->mMotion.mPos.mX + 1.0f;
            }
        } else if (fn_801783AC(0) != 0 && pCarrier != 0) {
            x = pCarrier->mMotion.mPos.mX;
        } else {
            x = fn_8011F4D4();
        }
        x = x < 2.0f - fn_80178A08() ? 2.0f - fn_80178A08() : (x <= fn_80178A08() - 2.0f ? x : fn_80178A08() - 2.0f);
        if (fabsf(pMotion->mPos.mX - x) > 1.0f) {
            goal.mX = x;
            goal.mY = pMotion->mPos.mY + 2.0f;
            fn_80227690(&goal, &goal, &pMotion->mPos);
            pRecord->mUnknown20 = fn_801CFE40(goal.mY, goal.mX);
        } else {
            pRecord->mUnknown20 = 0x400000;
        }
        pRecord->mUnknown12 = 1.0f;
    } else if (fn_8011F1A4() != 0) {
        Point_8017886C home;

        goal.mX = fn_8011F4D4();
        home = fn_80177FE0();
        if (fabsf(pMotion->mPos.mX) - fabsf(home.mX) < fabsf(goal.mX) - fabsf(home.mX)) {
            if (fn_8011F4C8() > 3) {
                if (goal.mX > fn_80177FE0().mX) {
                    goal.mX -= 0.5f;
                } else {
                    goal.mX += 0.5f;
                }
            }
            fn_80227690(&goal, &goal, &pMotion->mPos);
            pRecord->mUnknown20 = fn_801CFE40(goal.mY, goal.mX);
        } else {
            int turn = fn_801CFFD0(pMotion->mFacing, 0x400000);

            if (((0x400000 - pMotion->mFacing) & 0xFFFFFF) <= 0x7FFFFF) {
                pRecord->mUnknown20 = (pMotion->mFacing + turn / 2) & 0xFFFFFF;
            } else {
                pRecord->mUnknown20 = (pMotion->mFacing - turn / 2) & 0xFFFFFF;
            }
        }
        pRecord->mUnknown12 = 1.0f;
    } else {
        pRecord->mUnknown20 = 0x400000;
        pRecord->mUnknown12 = 0.0f;
    }
}

extern "C" int fn_800F62A4(Object_80039F5C *p) {
    Message_800F01CC message;

    if (fn_800F5AD4(p)) {
        fn_801C1F94(&message, 0, 4);
        if (fn_8011F1CC() && !fn_801783AC(0)) {
            message.mId = 31;
        } else {
            message.mId = 33;
        }
        fn_800F053C(0, p->mpState, &message, p);
        return 0;
    } else {
        fn_801C1F94(&message, 0, 4);
        message.mId = 47;
        message.mUnknown1[1] = p->mpState->mUnknown2;
        message.mUnknown1[0] = p->mpState->mUnknown1;
        message.mUnknown1[2] = p->mpState->mUnknown3[0];
        fn_800F053C(0, p->mpState, &message, p);
    }
    return 0;
}

extern "C" int fn_800F6790(Object_80039F5C *p) {
    fn_8011E3EC(p, 0);
    fn_8011E240(p);
    return 1;
}

extern "C" void fn_800F67CC(unsigned char *p) {
    p[2] = ((0x800000 - (p[2] << 17)) >> 17) & 0x7F;
}

extern "C" unsigned int fn_800F67E8(Object_80039F5C *pTarget) {
    unsigned int count = 0;

    if (pTarget) {
        unsigned int i = 0;
        unsigned int n = fn_80178D18(fn_80178320());
        for (; i < n; i++) {
            Object_80039F5C *p = fn_80039F5C(fn_80178320(), i);
            if (p->mpState->mId == 22) {
                Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown336);
                if (pOther && pOther == pTarget) {
                    count++;
                }
            }
        }
    }
    return count;
}

extern "C" void fn_800F722C(Object_80039F5C *p, Object_80039F5C *pOther, float *pX, float *pOut) {
    if (p && pOther && pOut) {
        Vector_80039F5C pos;
        int side;
        int flag;
        float distance;

        fn_80137D58(fn_801374BC(), &pos);
        side = (p->mpState->mUnknown2 ^ 1) & 1;
        if (*pX > pos.mX ? side == 0 : side != 0) {
            flag = 1;
        } else {
            flag = 0;
        }
        distance = fabsf(p->mMotion.mPos.mX - pOther->mMotion.mPos.mX);
        if (flag) {
            if (*pX > p->mMotion.mPos.mX) {
                *pOut = distance;
            } else {
                *pOut = -distance;
            }
        } else {
            if (*pX > p->mMotion.mPos.mX) {
                *pOut = distance;
            } else {
                *pOut = -distance;
            }
        }
        fn_800F6AD8(pOut);
    }
}

extern "C" int fn_800F8D24() {
    return 0;
}

extern "C" Object_80039F5C *fn_800F93D0(Object_80039F5C *p) {
    Object_80039F5C *pResult = 0;
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char i;

    for (i = 0; i < 7; i++) {
        if (pRecord->mUnknown16[i] == p->mIdBytes[1]) {
            pResult = fn_80039F5C(fn_80178320(), i);
            break;
        }
    }
    return pResult;
}

extern "C" void fn_800F9440(Object_80039F5C *p, Object_80039F5C *pOther) {
    fn_8011F4E0()->mUnknown16[p->mIdBytes[1]] = pOther->mIdBytes[1];
}

extern "C" Object_80039F5C *fn_800F9AF0(unsigned char slot) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char i = 0;
    unsigned char index = pRecord->mUnknown8[slot];
    Object_80039F5C *p = fn_80039F5C(fn_80178308(), index);

    do {
        if (pRecord->mUnknown32[i] == fn_800FC0C4(p)) {
            unsigned char j;
            for (j = 0; j < 8; j++) {
                if (pRecord->mUnknown24[j] == ((p->mId >> 16) & 0xFF) && pRecord->mUnknown40[j] == i) {
                    break;
                }
            }
            if (j == 8) {
                p = 0;
                break;
            }
        }
        i++;
    } while (i < 7);
    return p;
}

extern "C" Object_80039F5C *fn_800F9BD8(int forward, Object_80039F5C *p) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    Object_80039F5C *pResult = 0;
    unsigned char id = 0;
    int found = 0;
    unsigned char i;

    if (!p) {
        found = 1;
    } else {
        id = p->mIdBytes[1];
    }
    for (i = 0; i < 3; i++) {
        unsigned char slot = !forward ? 2 - i : i;
        if (found) {
            Object_80039F5C *pSlot = fn_800F9AF0(slot);
            if (pSlot) {
                pResult = pSlot;
                break;
            }
        } else if (fn_80039F5C(fn_80178308(), pRecord->mUnknown8[slot])->mIdBytes[1] == id) {
            found = 1;
        }
    }
    return pResult;
}

extern "C" int fn_800F9CAC() {
    return 1;
}

extern "C" void fn_800FA014(Object_80039F5C *p, int *pRef) {
    Object_80039F5C *pOther = 0;

    if (p->mUnknown2914 == 16) {
        Object_80039F5C *pCurrent = fn_8009BCE8(pRef);
        if (!pCurrent || fn_800FC0C4(pCurrent) != p->mpState->mUnknown1) {
            if (fn_8009F7A4(p, &pOther)) {
                fn_8009BD2C(pOther, pRef);
            }
        }
    }
}

extern "C" void fn_800FAD10(unsigned char *p) {
    unsigned char value = p[1];
    if (value != 0) {
        value = 6 - value;
    }
    p[1] = value;
}

extern "C" void fn_800FB768(void) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();

    if (!(pRecord->mUnknown2 & 0x8000)) {
        pRecord->mUnknown2--;
        if (pRecord->mUnknown2 & 0x8000) {

            int team = fn_80178308();
            int swapped;
            do {
                unsigned char i;
                swapped = 0;
                for (i = 0; i < 2; i++) {

                    Object_80039F5C *pA = fn_80039F5C(team, pRecord->mUnknown12[i]);
                    Object_80039F5C *pB = fn_80039F5C(team, pRecord->mUnknown12[i + 1]);
                    if (pA->mMotion.mPos.mX < pB->mMotion.mPos.mX) {
                        unsigned char t = pRecord->mUnknown12[i];
                        pRecord->mUnknown12[i] = pRecord->mUnknown12[i + 1];
                        pRecord->mUnknown12[i + 1] = t;
                        swapped = 1;
                    }
                }
            } while (swapped == 1);
        }
    }
}

extern "C" void fn_800FB824(Object_80039F5C *p, Object_80039F5C *pOther) {
    fn_800F9440(p, pOther);
}

extern "C" Object_80039F5C *fn_800FB844(Object_80039F5C *p) {
    Object_80039F5C *pResult = 0;
    Record_8011F4E0 *pRecord = fn_8011F4E0();

    if (fn_8009FE24(p)) {
        Point_8017886C pos;
        unsigned char ahead;
        unsigned char behind;
        signed char i;
        int n;

        if (pRecord->mUnknown5 == 0) {
            fn_800FBB70();
        }
        pos = fn_800F97A8(p);
        ahead = 1;
        behind = 1;
        n = fn_80178D18(fn_80178320());
        for (i = 0; i < n; i++) {
            Object_80039F5C *pOther = fn_80039F5C(fn_80178320(), i);
            if (pOther != p && fn_8009FE24(pOther)) {
                Point_8017886C otherPos = fn_800F97A8(pOther);
                if (otherPos.mX > pos.mX) {
                    ahead++;
                } else {
                    behind++;
                }
            }
        }
        if (ahead < behind) {
            for (i = 0; i < 8; i++) {
                if (pRecord->mUnknown24[i] != 255) {
                    ahead--;
                }
                if (ahead == 0) {
                    pResult = fn_80039F5C(fn_80178308(), pRecord->mUnknown24[i]);
                    break;
                }
            }
        } else {
            for (i = 7; i >= 0; i--) {
                if (pRecord->mUnknown24[i] != 255) {
                    behind--;
                }
                if (behind == 0) {
                    pResult = fn_80039F5C(fn_80178308(), pRecord->mUnknown24[i]);
                    break;
                }
            }
        }
    }
    return pResult;
}

extern "C" void fn_800FBAA8(void) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char i;
    unsigned int n;

    for (i = 0; i < 7; i++) {
        pRecord->mUnknown16[i] = 255;
    }
    for (i = 0; i < 7; i++) {
        pRecord->mUnknown32[i] = 255;
    }
    pRecord->mUnknown4 = 0;
    pRecord->mUnknown5 = 0;
    pRecord->mUnknown6 = 0;
    n = fn_80178D18(fn_80178320());
    for (i = 0; i < n; i++) {
        Object_80039F5C *p = fn_80039F5C(fn_80178320(), i);
        if (p->mpState->mId == 42) {
            Block_800FBAA8 *pBlock = (Block_800FBAA8 *)&p->mUnknown336;
            pBlock->mUnknown36 = 0;
        }
    }
}

extern "C" Object_80039F5C *fn_800FBF74(Object_80039F5C *pTarget, Object_80039F5C *pOther) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    Object_80039F5C *pResult = 0;
    unsigned short i;
    unsigned int n = fn_80178D18(fn_80178320());

    for (i = 0; i < n; i++) {
        Object_80039F5C *p = fn_80039F5C(fn_80178320(), i);
        unsigned short slot = fn_800FC014(p, pOther) - 1;
        if (slot <= 4 && fn_80039F5C(fn_80178308(), pRecord->mUnknown8[slot]) == pTarget) {
            pResult = p;
            break;
        }
    }
    return pResult;
}

extern "C" unsigned char fn_800FC014(Object_80039F5C *p, Object_80039F5C *pOther) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char value;

    if (pRecord->mUnknown4) {
        value = pRecord->mUnknown32[p->mIdBytes[1]];
        if (value == 255) {
            value = 253;
        }
    } else {
        value = pOther->mIdBytes[1];
    }
    return value;
}

extern "C" Object_80039F5C *fn_800FC070(Object_80039F5C *p, Object_80039F5C *pOther) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char slot = fn_800FC014(p, pOther);
    return fn_80039F5C(fn_80178308(), pRecord->mUnknown8[slot - 1]);
}

extern "C" unsigned char fn_800FC0C4(Object_80039F5C *p) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char id = p->mIdBytes[1];
    unsigned char i;

    for (i = 1; i < 4; i++) {
        if (pRecord->mUnknown8[i - 1] == id) {
            break;
        }
    }
    return i;
}

extern "C" unsigned char fn_800FC128(Object_80039F5C *p) {
    unsigned char count = 0;
    unsigned char i = 0;
    unsigned int n = fn_80178D18(fn_80178320());

    for (; i < n; i++) {
        Object_80039F5C *pOther = fn_80039F5C(fn_80178320(), i);
        if (fn_800F06F4(0, pOther->mpState, 22, 0xFFFF) != 0xFFFF && pOther != p
            && pOther->mMotion.mPos.mX > p->mMotion.mPos.mX) {
            count++;
        }
    }
    return count;
}

extern "C" unsigned char fn_800FC1DC(Object_80039F5C *p) {
    unsigned char count = 0;
    unsigned char i = 0;
    unsigned int n = fn_80178D18(fn_80178320());

    for (; i < n; i++) {
        Object_80039F5C *pOther = fn_80039F5C(fn_80178320(), i);
        if (fn_800F06F4(0, pOther->mpState, 22, 0xFFFF) != 0xFFFF && pOther != p
            && pOther->mMotion.mPos.mX < p->mMotion.mPos.mX) {
            count++;
        }
    }
    return count;
}

extern "C" int fn_800FCC24(Object_80039F5C *p) {
    int result = 0;
    Block_800FCC24 *pBlock = (Block_800FCC24 *)&p->mUnknown336;
    unsigned int flags = p->mFlags;
    unsigned int state = pBlock->mUnknown0;
    Message_800F01CC message;

    p->mFlags = flags & ~0x40000;
    switch (state) {
    case 0:
        if (flags & 4) {
            p->mFlags &= ~4;
            pBlock->mUnknown0 = pBlock->mUnknown37;
        }
        if (pBlock->mUnknown0 == 2) {
            fn_800FC7A0(p, pBlock);
        }
        break;
    case 1:
        if (fn_800FC4A8(p, pBlock, 0)) {
            pBlock->mUnknown0 = 0;
            pBlock->mUnknown37 = 2;
            p->mUnknown512.mUnknown14 = 0;
        } else {
            pBlock->mUnknown0 = 2;
        }
        break;
    case 2:
        if (fn_800FC4A8(p, pBlock, 1)) {
            pBlock->mUnknown0 = 0;
            pBlock->mUnknown37 = state;
            p->mUnknown512.mUnknown14 = 0;
        } else if (fn_800FC4A8(p, pBlock, 2)) {
            pBlock->mUnknown0 = 0;
            pBlock->mUnknown37 = 3;
            p->mUnknown512.mUnknown14 = 0;
        } else if (fn_800FC7A0(p, pBlock)) {
            if (fn_800FC4A8(p, pBlock, 3)) {
                pBlock->mUnknown0 = 0;
                pBlock->mUnknown37 = 3;
                p->mUnknown512.mUnknown14 = 0;
            } else {
                result = 1;
            }
        }
        break;
    case 3:
        result = 1;
        break;
    }
    if (result == 1) {
        if (fn_801CFFD0(p->mMotion.mFacing, pBlock->mUnknown20) > 0x200000) {
            fn_801C1F94(&message, 0, 4);
            message.mId = 6;
            message.mUnknown1[0] = pBlock->mUnknown20 >> 16;
            message.mUnknown1[1] = 1;
            fn_800F03D8(0, p->mpState, &message, p);
            fn_801C1F94(&message, 0, 4);
            message.mId = 9;
            message.mUnknown1[0] = pBlock->mUnknown33;
            message.mUnknown1[1] = 0;
            message.mUnknown1[2] = 255;
            fn_800F03D8(0, p->mpState, &message, p);
        } else {
            fn_801C1F94(&message, 0, 4);
            message.mId = 87;
            message.mUnknown1[0] = pBlock->mUnknown33;
            message.mUnknown1[1] = pBlock->mUnknown20 >> 16;
            fn_800F03D8(0, p->mpState, &message, p);
        }
        fn_8016DF34(p);
    }
    return result;
}

extern "C" int fn_800FD3F0(Object_80039F5C *p) {
    if (p) {
        fn_800FD724(p);
    }
    return 1;
}

extern "C" int fn_800FD650(Object_80039F5C *p, int mode) {
    Block_800FD650 *pBlock = (Block_800FD650 *)&p->mUnknown336;

    if (mode == 1) {
        pBlock->mUnknown0 = -pBlock->mUnknown0;
        pBlock->mUnknown4 = -pBlock->mUnknown4;
        pBlock->mUnknown16 = (pBlock->mUnknown16 + 0x800000) & 0xFFFFFF;
    }
    return 0;
}

extern "C" int fn_800FF860() {
    return 1;
}

extern "C" void fn_80104C3C(Object_80039F5C *p, Vector_80039F5C *pOut, float scale) {
    Vector_80039F5C v;

    fn_80104B3C(p, &v);
    fn_80227264(pOut, &v, scale);
    fn_8022765C(pOut, pOut, &p->mMotion.mPos);
}

extern "C" int fn_8010531C(Object_80039F5C *p) {
    switch (p->mpState->mId) {
    case 5:
    case 10:
    case 11:
    case 12:
    case 16:
    case 17:
    case 28:
    case 32:
    case 51:
        return 0;
    }
    return 1;
}

extern "C" int fn_801064A4(Object_80039F5C *p, int a) {
    int result = 0;
    Object_80039F5C *pTarget = fn_80105384(p, 1, 0);

    if (pTarget == 0) {
        if (fn_801486A0() == 0) {
            fn_8013791C(fn_801374BC(), 3, 1);
        }
    } else if (fn_80105E90(p, pTarget, 11)) {
        Message_800F01CC message;

        result = 1;
        fn_801C1F94(&message, 0, 4);
        message.mId = 25;
        fn_800D0BF4(p, a, 25);
        message.mUnknown1[0] = pTarget->mIdBytes[1];
        message.mUnknown1[1] = 11;
        fn_800F00D4(0, p->mpState, &message, p);
        fn_8010CEB8(pTarget, 11);
    }
    return result;
}

extern "C" int fn_80106580(Object_80039F5C *p, int a) {
    int result = 0;
    Object_80039F5C *pTarget = fn_80105384(p, a, 0);

    if (pTarget != 0 && fn_80105E90(p, pTarget, 11) && fn_80106618(p)) {
        result = 1;
        fn_80106678(fn_8011F518(), pTarget, 6, 11);
        fn_8010CEB8(pTarget, 11);
        fn_800D6914(0, p);
    }
    return result;
}

extern "C" int fn_80106618(Object_80039F5C *p) {
    int *pValue;

    switch (p->mUnknown776) {
    case 1:
        pValue = &p->mUnknown108;
        break;
    case 2:
        pValue = &p->mUnknown200;
        break;
    default:
        pValue = 0;
        break;
    }
    if (pValue != 0) {
        return *pValue != 0 && *pValue != 4;
    }
    return 0;
}

extern "C" int fn_80106794(Object_80039F5C *p) {
    if (fn_80137C48(p) == fn_801374BC()) {
        fn_80137C10(0);
    }
    return 1;
}

extern "C" int fn_801067D8(Object_80039F5C *p) {
    return fn_8012506C(p, 6) < lbl_803EAEF4;
}

extern "C" void fn_801076F0(Object_80039F5C *pA, Object_80039F5C *pB, Result_801076F0 *pOut, Input_801076F0 *pIn) {
    Point_8017886C delta;

    fn_80227690(&pOut->mUnknown0, &pIn->mUnknown16, &pB->mMotion.mPos);
    pOut->mUnknown16 = fn_801CFE40(pOut->mUnknown0.mY, pOut->mUnknown0.mX);
    fn_80227690(&pOut->mUnknown8, &pA->mMotion.mPos, &pB->mMotion.mPos);
    pOut->mUnknown20 = fn_801CFE40(pOut->mUnknown8.mY, pOut->mUnknown8.mX);
    pOut->mUnknown32 = fn_802270A4(&pOut->mUnknown8);
    fn_80227690(&delta, &pIn->mUnknown4, &pB->mMotion.mPos);
    pOut->mUnknown24 = fn_801CFE40(delta.mY, delta.mX);
    pOut->mUnknown36 = fn_802270A4(&delta);
    fn_80227690(&delta, &pIn->mUnknown4, &pA->mMotion.mPos);
    pOut->mUnknown28 = fn_801CFE40(delta.mY, delta.mX);
    pOut->mUnknown40 = fn_802270A4(&delta);
}

extern "C" int fn_8010A07C(Object_80039F5C *p) {
    int result = 0;

    switch ((p->mUnknown388 >> 25) & 0xF) {
    case 1:
    case 2:
        result = 1;
        break;
    }
    return result;
}

extern "C" void fn_8010A1C4(int team) {
    int i;
    int count = fn_80178D18(team);

    for (i = 0; i < count; i++) {
        fn_8003AB08(fn_80039F5C(team, i), 62);
    }
}

extern "C" void fn_8010A220(void) {
    fn_8010A1C4(fn_80178308());
    fn_8010A1C4(fn_80178320());
    lbl_803EAF10 = 0;
}

extern "C" int fn_8010A254(Object_80039F5C *p, int kind) {
    int result = 0;
    Message_800F01CC message;

    if (fn_80137C48(p) == 0 && (kind == 5 || kind == 9)) {
        result = 1;
        fn_801C1F94(&message, 0, 4);
        message.mId = 62;
        message.mUnknown1[0] = 9;
        message.mUnknown1[2] = kind;
        fn_8003AB28(p, &message, 1);
    }
    return result;
}

extern "C" int fn_8010AEA0(Object_80039F5C *p) {
    fn_8009D1AC(p);
    return 1;
}

extern "C" void fn_8010AEC4(int value) {
    lbl_803EAF10 = value;
}

extern "C" int fn_8010B1B4(Object_80039F5C *p) {
    int state = fn_800AD9B4();

    if (p->mUnknown342 != 0 && state == 2) {
        return 0;
    }
    return 1;
}

extern "C" void fn_8010B1FC(Object_80039F5C *p, int a, short b) {
    if (p->mpState->mId == 70 && (p->mFlags & 0x40000)) {
        p->mUnknown336 = a;
        p->mUnknown340 = b;
    }
}

extern "C" unsigned char fn_8010B3A0(Object_80039F5C *p, int kind) {
    unsigned char result = 0;
    unsigned char i;

    switch (kind) {
    case 5: {
        unsigned int count = fn_80178D18(0);
        for (i = 0; i < count; i++) {
            result |= fn_8010B87C(p, fn_80039F5C(0, i));
            if (result) {
                break;
            }
        }
        count = fn_80178D18(1);
        for (i = 0; i < count; i++) {
            result |= fn_8010B87C(p, fn_80039F5C(1, i));
            if (result) {
                break;
            }
        }
        break;
    }
    case 4: {
        Object_80039F5C *pOther = fn_80137B40();

        if (pOther != 0) {
            result = fn_8010B87C(p, pOther);
        }
        break;
    }
    case 3: {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        for (i = 0; i < count; i++) {
            Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2] ^ 1, i);

            if (pOther->mFlags & 0x800) {
                result = fn_8010B87C(p, pOther);
            }
            if (result) {
                break;
            }
        }
        break;
    }
    case 1: {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        for (i = 0; i < count; i++) {
            result = fn_8010B87C(p, fn_80039F5C(p->mIdBytes[2], i));
            if (result) {
                break;
            }
        }
        break;
    }
    case 2: {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        for (i = 0; i < count; i++) {
            result = fn_8010B87C(p, fn_80039F5C(p->mIdBytes[2] ^ 1, i));
            if (result) {
                break;
            }
        }
        break;
    }
    case 6:
        result = 1;
        break;
    default:
        result = 1;
        break;
    }
    return result;
}

extern "C" unsigned char fn_8010B5B0(Object_80039F5C *p, unsigned char *pOut) {
    int mode = fn_800A2178();
    State_8010BA00 *pState = (State_8010BA00 *)&p->mUnknown336;
    unsigned char count = 0;

    if (fn_80137B40() != p) {
        pOut[count++] = pState->mUnknown2;
        if ((p->mIdBytes[2] == fn_80178348() && mode == 0) ||
            (p->mIdBytes[2] == fn_80178360() && mode == 14)) {
            pOut[count++] = 5;
        }
        if (p->mIdBytes[2] == fn_80178360()) {
            switch (mode) {
            case 12:
                pOut[count++] = 6;
                pOut[count++] = 7;
                break;
            case 7:
            case 8:
                pOut[count++] = 7;
                break;
            }
        }
    } else if (!fn_80156704() || fn_801485D4()) {
        switch (mode) {
        case 0:
        case 1:
        case 14:
        case 15:
            pOut[count++] = 8;
            break;
        case 9:
            pOut[count++] = 8;
            break;
        default:
            pOut[count++] = 9;
            break;
        }
    } else if (fn_80156D14()) {
        pOut[count++] = 8;
    } else {
        pOut[count++] = 9;
    }
    return count;
}

extern "C" unsigned char fn_8010B738(Object_80039F5C *p, Table_8010B738 *pTable) {
    unsigned char choices[100];
    unsigned char kinds[8];
    unsigned char n = 0;
    unsigned char result = 255;
    unsigned char count = fn_8010B5B0(p, kinds);
    unsigned char i;

    for (i = 0; i < pTable->mCount; i++) {
        Record_8010B738 *pRecord = pTable->mEntries[i].mpRecord;
        int found = 0;
        unsigned char j;

        for (j = 0; j < count; j++) {
            if (pRecord->mUnknown4 == kinds[j] && fn_8010B3A0(p, pRecord->mUnknown5)) {
                if ((pRecord->mUnknown6 == 1 && p->mUnknown776 == 2) ||
                    (pRecord->mUnknown6 == 2 && p->mUnknown776 == 1) || fn_80137B40() != p) {
                    if (lbl_802DABBC[i] == 0) {
                        found = 1;
                    }
                }
            }
        }
        if (found) {
            choices[n++] = i;
        }
    }
    if (n != 0) {
        result = choices[fn_802372EC(0, n)];
    }
    return result;
}

extern "C" int fn_8010B924(Object_80039F5C *p) {
    int kind;

    if (!fn_80156704() || fn_801485D4()) {
        int mode = fn_800A2178();
        int team = p->mIdBytes[2];

        kind = lbl_802DAB60[mode];
        if (team == fn_80178360()) {
            switch (kind) {
            case 4:
                kind = 1;
                break;
            case 2:
                kind = 3;
                break;
            case 1:
                kind = 4;
                break;
            case 3:
                kind = 2;
                break;
            }
        }
    } else if (fn_80156D14()) {
        kind = 1;
        if (fn_800B65A0(p->mIdBytes[2]) != 255) {
            kind = 4;
        }
    } else {
        kind = 3;
        if (fn_800B65A0(p->mIdBytes[2]) != 255) {
            kind = 2;
        }
    }
    return kind;
}

extern "C" int fn_8010BA00(Object_80039F5C *p) {
    State_8010BA00 *pState = (State_8010BA00 *)&p->mUnknown336;

    pState->mUnknown0 = 0;
    pState->mUnknown2 = fn_8010B924(p);
    pState->mUnknown3 = 255;
    if (fn_801BE648(p->mpUnknown792) == 48) {
        pState->mUnknown1 = 0;
    } else {
        pState->mUnknown1 = fn_802372EC(0, 15);
    }
    if (pState->mUnknown2 == 0 && fn_80137B40() != p) {
        pState->mUnknown0 = 1;
    }
    return 0;
}

extern "C" int fn_8010BC48(Object_80039F5C *p) {
    State_8010BA00 *pState = (State_8010BA00 *)&p->mUnknown336;

    if (pState->mUnknown3 != 255) {
        lbl_802DABBC[pState->mUnknown3] = 0;
    }
    fn_800A3B58(p, 2, 0);
    return 1;
}

extern "C" void fn_8010BE54(Object_80039F5C *p)
{
    Message_800F01CC message;

    fn_801C1F94(&message, 0, 4);
    message.mId = 93;
    fn_8003AB28(p, &message, 0);
}

extern "C" void fn_8010BEA4(void)
{
    fn_801C1F94(lbl_802DABBC, 0, 100);
}

extern "C" int fn_8010C864(Object_80039F5C *p)
{
    int found = 0;
    unsigned char i;
    unsigned int count = fn_80178D18(fn_80178308());

    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(fn_80178308(), i);

        if (pOther != p && fn_800F06F4(0, pOther->mpState, 26, 0xFFFF) != 0xFFFF) {
            found = 1;
            break;
        }
    }
    return found;
}

extern "C" void fn_8010CFD4(Object_80039F5C *p)
{
    if (((p->mMotion.mUnknown32 - 0x400000) & 0xFFFFFF) > 0x800000) {
        p->mUnknown512.mUnknown15 = 15;
    } else {
        p->mUnknown512.mUnknown15 = 16;
    }
}

extern "C" int fn_8010D6D4(Object_80039F5C *p)
{
    int port;

    fn_8010D508(p);
    port = fn_800B65A0(p->mIdBytes[2]);
    if (port != 255 && p->mUnknown8 == 255) {
        fn_800B6714(p, port);
    }
    p->mUnknown512.mUnknown14 = 0;
    return 0;
}

extern "C" Object_80039F5C *fn_8010DA38(Object_80039F5C *p, Object_80039F5C *pExclude)
{
    unsigned char i;
    unsigned int count = fn_80178D18(p->mIdBytes[2]);

    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], i);

        if (pOther != pExclude && pOther->mpState->mId == 90) {
            return pOther;
        }
    }
    return 0;
}

extern "C" void fn_8010EF40(Object_80039F5C *p)
{
    int found = 0;
    Block_80170374 *pBlock = &p->mUnknown560;
    Object_80039F5C *pCarrier;
    Object_80039F5C *pOther;
    Point_8017886C delta;

    if (pBlock->mFlags.mBytes[0] == 1) {
        pCarrier = fn_80137B40();
        if (pCarrier != 0 && (pCarrier->mFlags & 0x10000)) {
            switch (pBlock->mUnknown54) {
            case 0:
            case 5:
            case 7:
                pOther = fn_8009BCE8(&pBlock->mUnknown44);
                if (pOther == pCarrier) {
                    found = 1;
                } else {
                    pOther = fn_8009BCE8(&pBlock->mUnknown40);
                    if (pOther != 0 && (pOther->mpState->mId == 17 || pOther == pCarrier)) {
                        found = 1;
                    }
                }
                if (found && fn_802372EC(0, 100) <= 74) {
                    fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
                    if (fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), pOther->mMotion.mUnknown32) <= 0x3FFFFF) {
                        fn_800E96EC(p, pOther);
                    }
                }
                break;
            }
        }
    }
}

extern "C" int fn_8010FB10(Object_80039F5C *p)
{
    fn_8011E3EC(p, 0);
    fn_8011E240(p);
    return 1;
}

extern "C" int fn_8010FD8C() {
    return 1;
}

extern "C" int fn_801100A0(Object_80039F5C *p)
{
    State_80039F5C *pState = p->mpState;

    if (pState->mUnknown2) {
        p->mFlags |= 1 << pState->mUnknown1;
    } else {
        p->mFlags &= ~(1 << pState->mUnknown1);
    }
    return 1;
}

extern "C" int fn_801105B0(Object_80039F5C *p)
{
    int angle;

    if (p->mUnknown776 == 1) {
        angle = (0x800000 - p->mMotion.mFacing) & 0xFFFFFF;
    } else {
        angle = p->mMotion.mFacing;
    }
    if (p->mUnknown1008.mUnknown1 == 6) {
        angle = (angle + 0xB1C71D) & 0xFFFFFF;
    } else {
        angle = (0x131C71D - angle) & 0xFFFFFF;
    }
    if (angle <= 0x5FFFFF) {
        if (angle <= 0x3FFFFF) {
            angle = 0x1000000;
        } else {
            angle = 0x600000;
        }
    }
    return angle;
}

extern "C" int fn_80110630(Key_80110630 *pA, Key_80110630 *pB)
{
    int result = pA->mUnknown0 == pB->mUnknown0;

    if (pA->mUnknown1 != pB->mUnknown1) {
        result = 0;
    }
    if (pA->mUnknown2 != pB->mUnknown2 && pA->mUnknown2 != 0) {
        result = 0;
    }
    return result;
}

extern "C" int fn_80110824(Object_80039F5C *p, int a, int b, int c)
{
    int result = 0;
    Message_800F01CC message;

    if (fn_801101DC(p)) {
        if (b == 0) {
            b = fn_801102A4(p);
        }
        if (a == 1) {
            a = 2;
        }
        result = 1;
        fn_800D0BF4(p, c, 35);
        fn_801C1F94(&message, 0, 4);
        message.mId = 35;
        message.mUnknown1[0] = a;
        message.mUnknown1[1] = b;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int fn_80110EB0(Object_80039F5C *p, int a)
{
    return fn_801250B8(p, a, 6) < lbl_803EAF58;
}

extern "C" int fn_80110EE4(Object_80039F5C *p)
{
    int result;
    int team;
    int angle;
    Object_80039F5C *pTarget;
    float distance;
    Point_8017886C delta;

    switch (p->mpState->mUnknown1) {
    case 1:
        result = 6;
        break;
    case 2:
        result = 8;
        break;
    case 0:
    default:
        team = fn_80178320();
        result = 6;
        pTarget = fn_801244F0(p, team, 0, fn_80178D70(fn_80178320()), &distance, 1);
        if (pTarget != 0) {
            fn_80227690(&delta, &pTarget->mMotion.mPos, &p->mMotion.mPos);
            angle = fn_801CFE40(delta.mY, delta.mX);
            fn_801CFFD0(angle, p->mMotion.mFacing);
            if (((angle - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                p->mpState->mUnknown1 = 1;
            } else {
                p->mpState->mUnknown1 = 2;
                result = 8;
            }
        } else if (p->mUnknown776 == 2) {
            result = 8;
        }
        break;
    }
    return result;
}

extern "C" int fn_80110FE4(Object_80039F5C *p)
{
    int result = 0;

    if (fn_800AD9B4() == 3) {
        switch (p->mpState->mId) {
        case 5:
        case 10:
        case 11:
        case 12:
        case 15:
        case 16:
        case 17:
        case 25:
        case 26:
        case 27:
        case 34:
        case 35:
            result = 0;
            break;
        default:
            result = 1;
            break;
        }
        if (p != fn_80137B40()) {
            result = 0;
        }
    }
    return result;
}

extern "C" int fn_80111090(Object_80039F5C *p, int a)
{
    int result = 0;
    Message_800F01CC message;

    if (fn_80110FE4(p)) {
        result = 1;
        fn_801C1F94(&message, 0, 4);
        message.mId = 43;
        message.mUnknown1[0] = a;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" void fn_80111354(Object_80039F5C *p)
{
    switch (p->mpState->mId) {
    case 5:
    case 10:
    case 11:
    case 15:
    case 16:
    case 17:
    case 25:
    case 26:
    case 27:
    case 32:
    case 36:
    case 58:
        break;
    default:
        fn_800E9528(p);
        break;
    }
}

extern "C" int fn_80111580(Object_80039F5C *p)
{
    switch (fn_801BE648(p->mpUnknown792)) {
    case 196:
    case 210:
        return 0;
    }
    return 1;
}

extern "C" int fn_80111964(Object_80039F5C *p)
{
    p->mUnknown512.mUnknown15 = 0;
    return 1;
}

extern "C" int fn_80111F80(Object_80039F5C *p)
{
    State_80111F80 *state = (State_80111F80 *)&p->mUnknown336;

    fn_8009A8D4(state);
    state->mUnknown20 = 0;
    return 0;
}

extern "C" int fn_80112E10(Object_80039F5C *p)
{
    State_80112E10 *state = (State_80112E10 *)&p->mUnknown336;

    if (p->mUnknown776 == 2) {
        state->mUnknown4 = 1;
    } else {
        state->mUnknown4 = 2;
    }
    state->mUnknown0 = 15;
    if (p->mUnknown528.mUnknown15 == 1) {
        state->mUnknown12 = 23;
    } else {
        state->mUnknown12 = 22;
    }
    state->mUnknown8 = p->mUnknown528.mUnknown0;
    state->mUnknown13 = 0;
    p->mUnknown512.mUnknown15 = state->mUnknown12;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown0 = state->mUnknown8;
    return 0;
}

extern "C" int fn_80112E8C(Object_80039F5C *p)
{
    State_80112E10 *state = (State_80112E10 *)&p->mUnknown336;
    int result = 0;

    if (!(p->mFlags & 0x4000)) {
        p->mUnknown512.mUnknown15 = state->mUnknown12;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = state->mUnknown8;
    }
    if (--state->mUnknown0 <= 0) {
        switch (state->mUnknown13) {
        case 0:
            fn_800D7A0C(p, state->mUnknown4);
            if (state->mUnknown12 == 23) {
                state->mUnknown12 = 1;
            } else {
                state->mUnknown12 = 0;
            }
            state->mUnknown0 = 8;
            state->mUnknown13 = 1;
            break;
        case 1:
            p->mUnknown512.mUnknown14 = 1;
            result = 1;
            p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
            break;
        }
    } else if (state->mUnknown13 == 1) {
        fn_800D7A0C(p, state->mUnknown4);
    }
    return result;
}

extern "C" int fn_80113088(Object_80039F5C *p)
{
    int result = 0;
    int ballState = fn_8013BA58(fn_801374BC(), 0);
    int *pMode = &p->mUnknown1032;

    switch (p->mpState->mId) {
    case 5:
    case 10:
    case 11:
    case 15:
    case 16:
    case 17:
    case 25:
    case 26:
    case 27:
    case 28:
    case 32:
    case 34:
    case 35:
    case 36:
    case 43:
    case 51:
    case 88:
        result = 0;
        break;
    default:
        if (*pMode == 0 || *pMode == 8) {
            if (ballState == 3 || ballState == 4) {
                result = 1;
            } else {
                Object_80039F5C *pCarrier = fn_80137B40();
                if (pCarrier != 0 && pCarrier->mpState->mId == 15) {
                    result = 1;
                }
            }
            if (result == 0 && fn_801486A0() == 1) {
                unsigned int count = fn_801383C8();
                unsigned int i;
                for (i = 1; i < count; i++) {
                    Object_80137ABC *pBall = fn_80137ABC(i);
                    int state = fn_8013BA58(pBall, 0);
                    Object_80039F5C *pOther;
                    if (state == 3 || state == 4) {
                        result = 1;
                        break;
                    }
                    pOther = fn_80137AD0(pBall);
                    if (pOther != 0 && pOther->mpState->mId == 15) {
                        result = 1;
                        break;
                    }
                }
            }
        }
        break;
    }
    return result;
}

extern "C" int fn_80113208(Object_80039F5C *p, int a, int mode, int c)
{
    int result = 0;
    unsigned char index;
    int value = -1;
    int extra = 0;
    int flag = 0;
    Object_80137ABC *pBall;
    int target;

    index = 0;
    if (mode == 1 || mode == 3) {
        flag = 1;
    }
    if (fn_801486A0() == 1 && fn_801520C4(p, &index) != 0) {
        pBall = fn_80137ABC(index);
    } else {
        pBall = fn_801374BC();
        index = fn_801374E0(pBall);
    }
    if (p->mpState->mUnknown2 != 0) {
        target = fn_80099AD0(p, pBall, 3, 3, mode, a, c);
    } else if (mode == 3) {
        if (c != 0) {
            target = fn_80099C80(p, pBall, 0, &value, &extra);
        } else {
            target = fn_80099C80(p, pBall, a, &value, &extra);
        }
    } else {
        target = fn_80099AD0(p, pBall, 0, 2, mode, a, c);
    }
    if (target != 0x1FFFFFFF && (value != -1 || mode != 3)) {
        if (mode == 3) {
            if (fn_8009A1A8(p, target, value, extra, index) == 1) {
                result = 1;
            }
        } else if (fn_80099F04(p, target, index) == 1) {
            result = 1;
        }
    } else if (a != 0) {
        if (mode == 3) {
            result = fn_80113208(p, a, 1, c);
        } else if (p->mpState->mUnknown2 != 0) {
            fn_800E815C(p, 0, 0);
            result = 1;
        } else {
            fn_800F2C1C(p, flag);
            result = 1;
        }
    }
    return result;
}

extern "C" int fn_801133FC(Object_80039F5C *p, int a, int b)
{
    int result = 0;

    if (fn_80113088(p) != 0) {
        Message_800F01CC message;
        result = 1;
        fn_801C1F94(&message, 0, sizeof(message));
        message.mId = 88;
        message.mUnknown1[0] = a;
        message.mUnknown1[1] = b;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int fn_80113478(Object_80039F5C *p)
{
    State_80113478 *state = (State_80113478 *)&p->mUnknown336;

    state->mUnknown0 = 0;
    state->mUnknown4 = p->mpState->mUnknown1;
    return 0;
}

extern "C" int fn_801135E4(Object_80039F5C *p)
{
    return fn_80113604(p);
}

extern "C" int fn_80113604(Object_80039F5C *p)
{
    State_80039F5C *pState = p->mpState;
    Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], pState->mUnknown1);
    unsigned int bit = 1 << pState->mUnknown2;

    if ((pOther->mFlags & bit) == bit) {
        return 1;
    }
    if (pState->mUnknown3[0] != 0) {
        fn_8010A2DC(p, 0, -1);
    }
    return 0;
}

extern "C" int fn_80113AAC(Object_80039F5C *p)
{
    State_80113AAC *state = (State_80113AAC *)&p->mUnknown336;

    if (state->mUnknown21 != 0 || state->mUnknown15 != 0) {
        state->mUnknown15 = 0;
        p->mFlags &= ~0x8;
        fn_800CE674(&p->mUnknown1240);
        fn_800CE684(&p->mUnknown1240);
        p->mUnknown1218 = 0;
        return 1;
    }
    return 0;
}

extern "C" int fn_80113BCC(Object_80039F5C *p)
{
    int result = 0;

    if (p->mpState->mId == 17 && fn_80114E7C(p) != 0) {
        result = 1;
    }
    return result;
}

extern "C" int fn_80113C18() {
    return 0;
}

extern "C" int fn_801147D4(Object_80039F5C *p)
{
    State_801147D4 *state = (State_801147D4 *)&p->mUnknown336;

    if (state->mUnknown31 != 0) {
        p->mFlags &= ~0x2000;
        p->mFlags &= ~0x8;
        fn_800CE674(&p->mUnknown1240);
        fn_800CE684(&p->mUnknown1240);
        return 1;
    }
    return 0;
}

extern "C" int fn_80114D14(int a, unsigned int b, int c, unsigned int d)
{
    int result = a - c;

    if (b > d) {
        if ((int)(b - d) > 100) {
            result++;
        }
    } else if (d > b) {
        if ((int)(d - b) > 100) {
            result--;
        }
    }
    return result;
}

extern "C" void fn_80114D50(Object_80039F5C *p, Object_80039F5C *pOther)
{
    p->mUnknown392 = 4;
    ((State_80113AAC *)&pOther->mUnknown336)->mUnknown14 = 4;
    fn_800D6EDC();
    fn_80067DB8(101, &p->mMotion.mPos, p->mId, pOther->mId, 0);
    if (!(pOther->mFlags & 0x400) && fn_801486A0() != 0) {
        int port = fn_800B65A0(pOther->mIdBytes[2]);
        if (port != 255) {
            fn_800B6714(pOther, port);
        }
    }
}

extern "C" unsigned char fn_80114DD8(Object_80039F5C *p)
{
    return p->mUnknown402;
}

extern "C" int fn_80114DE0(Object_80039F5C *p)
{
    return p->mUnknown392 == 1;
}

extern "C" void fn_80114DF4(Object_80039F5C *p)
{
    State_80114DF4 *state = (State_80114DF4 *)&p->mUnknown336;
    unsigned char kind = state->mUnknown56;

    if (kind == 1) {
        Object_80039F5C *pOther = fn_8009BCE8(&state->mRef);
        ((State_80113AAC *)&pOther->mUnknown336)->mUnknown15 = kind;
        pOther->mpState->mUnknown3[0] = 255;
        fn_800E98A4(pOther, p);
        fn_80143EBC(p, pOther);
        fn_80067DB8(102, &p->mMotion.mPos, 0, 0, 0);
        fn_8017D9B0(p->mId, pOther->mId);
    }
}

extern "C" Object_80039F5C *fn_80114E7C(Object_80039F5C *p)
{
    Object_80039F5C *result = 0;
    unsigned char id = p->mpState->mId;

    if (id == 16) {
        State_80114DF4 *state = (State_80114DF4 *)&p->mUnknown336;
        if (state->mUnknown56 == 1 || state->mUnknown56 == 4) {
            result = fn_8009BCE8(&state->mRef);
        }
    } else if (id == 17) {
        State_80113AAC *state = (State_80113AAC *)&p->mUnknown336;
        if (state->mUnknown14 == 1 || state->mUnknown14 == 4) {
            result = fn_8009BCE8(&state->mRef);
        }
    }
    return result;
}

extern "C" int fn_801163B4(Object_80039F5C *p)
{
    Object_80039F5C *value = 0;
    int result = 0;

    switch (p->mUnknown2914) {
    case 17:
    case 18:
        if (fn_8009F7A4(p, &value) != 0) {
            result = 1;
        }
        break;
    }
    return result;
}

extern "C" int fn_801167C4(void *pTarget, Object_80039F5C *p)
{
    int found = 0;

    if (pTarget != 0) {
        unsigned int i = 0;
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        for (; i < count && found == 0; i++) {
            Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], i);
            if (pOther != p) {
                unsigned char id = pOther->mpState->mId;
                if (id == 40 || id == 92) {
                    fn_8009EAB0(pOther, fn_800C1180(pOther));
                    if (fn_8009EF6C(pTarget) != 0) {
                        found = 1;
                    }
                }
            }
        }
    }
    return found;
}

extern "C" void fn_80116880(Object_80039F5C *p, Object_80039F5C *pOther, float *pValue, float *pOut, float range)
{
    int pending = 1;

    if (p != 0 && pValue != 0 && pOut != 0 && pOther != 0) {
        if (fabsf(p->mMotion.mPos.mX - *pValue) < range) {
            int limit = 0x2AAAA9;
            fn_801CFFD0(pOther->mMotion.mUnknown32, p->mMotion.mUnknown32);
            if (fn_801CFFD0(pOther->mMotion.mUnknown32, 0) <= limit) {
                pending = 0;
                *pOut = *pValue + range;
            } else if (fn_801CFFD0(pOther->mMotion.mUnknown32, 0x800000) <= limit) {
                pending = 0;
                *pOut = *pValue - range;
            }
        }
        if (pending != 0) {
            if (p->mMotion.mPos.mX > *pValue) {
                *pOut = *pValue + range;
            } else {
                *pOut = *pValue - range;
            }
        }
    }
}

extern "C" int fn_80116AB8(Object_80039F5C *p)
{
    int result = 1;

    if (p != 0) {
        int eligible;
        switch (p->mpState->mUnknown1) {
        case 0:
        case 4:
            eligible = 1;
            break;
        case 1:
        case 2:
        case 3:
            eligible = 0;
            break;
        case 9:
            eligible = 0;
            break;
        default:
            eligible = 0;
            break;
        }
        if (eligible) {
            unsigned int i = 0;
            unsigned int count = fn_80178D18(p->mIdBytes[2]);
            for (; i < count && result != 0; i++) {
                Object_80039F5C *pOther = fn_80039F5C(p->mIdBytes[2], i);
                if (pOther != p && pOther->mpState->mId == 40) {
                    result = 0;
                }
            }
        } else {
            result = 0;
        }
    }
    return result;
}

extern "C" void fn_801170A0(Record_801170A0 *p)
{
    unsigned char value = p->mUnknown1;

    if (value >= 1 && value <= 2) {
        value = 3 - value;
    } else if (value >= 3 && value <= 5) {
        value = 8 - value;
    } else if (value >= 6 && value <= 9) {
        value = 15 - value;
    }
    p->mUnknown1 = value;
}

extern "C" void fn_80118704(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EC9F0, 4, 0, 0x7A736674);
    unsigned char *pData = (unsigned char *)fn_8023816C(pHandle);

    *pData = 0;
    fn_802381E0(pHandle);
}

extern "C" void fn_8011875C(void)
{
    *lbl_803EC9F0 = 0;
}

extern "C" void fn_8011876C(void)
{
    lbl_803EC9F0 = 0;
}

extern "C" void fn_80118778(Record_801170A0 *p)
{
    unsigned char value = p->mUnknown1 + 14;

    if (value >= 15 && value <= 16) {
        value = 31 - value;
    } else if (value >= 17 && value <= 19) {
        value = 36 - value;
    } else if (value >= 20 && value <= 23) {
        value = 43 - value;
    }
    p->mUnknown1 = value - 14;
}

extern "C" void fn_80118894(Record_80118894 *pA, Record_80118894 *pB, int a, int b, Object_80039F5C *pPlayerA, Object_80039F5C *pPlayerB)
{
    if (a != 0) {
        pA->mUnknown64 *= fn_800CA9B4(9, pPlayerA);
        pA->mUnknown76 *= fn_800CA9B4(9, pPlayerA);
    }
    if (b != 0) {
        pB->mUnknown64 *= fn_800CA9B4(9, pPlayerB);
        pB->mUnknown76 *= fn_800CA9B4(9, pPlayerB);
    }
}

extern "C" void fn_8011893C(void)
{
    int team = fn_80178308();
    unsigned char i = 0;
    unsigned int count = fn_80178D70(team);

    for (; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
        int *pRef = &p->mUnknown1036;
        Object_80039F5C *pOther;
        unsigned short value;
        int mode;
        int otherMode;

        if (p->mUnknown1032 == 7) {
            pRef = &p->mUnknown1040;
        }
        pOther = fn_8009BCE8(pRef);
        if (fn_8011E3F4(p) != 0) {
            value = 0;
            switch (p->mUnknown1032) {
            case 2:
            case 3:
            case 4:
                mode = 4;
                otherMode = 4;
                value = 20 - (p->mRatings[7] >> 4);
                fn_8011DBC4(p);
                break;
            default:
                mode = p->mUnknown1032;
                otherMode = pOther != 0 ? pOther->mUnknown1032 : 0;
                break;
            }
        } else {
            value = 0;
            fn_8011DBC0(p);
            switch (p->mUnknown1032) {
            case 4:
                fn_80143EBC(p, pOther);
                mode = 2;
                otherMode = 8;
                fn_80143EBC(pOther, p);
                break;
            case 3:
                if (pOther != 0) {
                    mode = 1;
                    if (fn_801CFFD0(p->mMotion.mFacing, pOther->mMotion.mFacing) > 0x471C71) {
                        mode = p->mUnknown1032;
                    }
                    otherMode = pOther->mUnknown1032;
                } else {
                    otherMode = 0;
                    mode = 3;
                }
                break;
            default:
                mode = p->mUnknown1032;
                otherMode = pOther != 0 ? pOther->mUnknown1032 : 0;
                break;
            }
        }
        if (p->mUnknown1032 != mode) {
            p->mUnknown1134 = value;
            p->mUnknown1032 = mode;
            p->mUnknown1136 = 0;
            p->mUnknown1137 = 0;
            switch (mode) {
            case 4:
                p->mUnknown1126 = 1;
                if (fn_8011DC68(fn_801BE648(p->mpUnknown792)) != 0) {
                    p->mUnknown1064 = fn_801BE648(p->mpUnknown792);
                } else {
                    p->mUnknown1064 = -1;
                }
                break;
            case 1:
                pOther = 0;
                fn_8011E240(p);
                fn_8011E1BC(p, 0, 0, 1);
                break;
            }
        }
        if (pOther != 0 && pOther->mUnknown1032 != otherMode) {
            pOther->mUnknown1032 = otherMode;
            pOther->mUnknown1137 = 0;
            pOther->mUnknown1134 = 0;
            pOther->mUnknown1136 = 0;
        }
    }
}

extern "C" void fn_80119478(void)
{
    int team = fn_80178308();
    unsigned char i = 0;
    Pair_8011BAE0 pair;
    unsigned int count;

    fn_8011BAE0(&pair);
    count = fn_80178D70(team);
    for (; i < count; i++) {
        fn_80118B4C(fn_80039F5C(team, i), &pair);
    }
}

extern "C" void fn_8011AFCC(Entry_8011AFCC *pEntries)
{
    int swapped;

    do {
        Entry_8011AFCC *pPrev = pEntries;
        Entry_8011AFCC *pEntry;

        swapped = 0;
        for (pEntry = pEntries + 1; pEntry->mUnknown60 != 0; pEntry++) {
            if (pEntry->mUnknown68 < pPrev->mUnknown68) {
                Entry_8011AFCC temp = *pEntry;
                *pEntry = *pPrev;
                *pPrev = temp;
                swapped = 1;
            }
            pPrev = pEntry;
        }
    } while (swapped);
}

extern "C" void fn_8011B138(Entry_8011AFCC *pEntries)
{
    int swapped;

    do {
        Entry_8011AFCC *pPrev = pEntries;
        Entry_8011AFCC *pEntry;

        swapped = 0;
        for (pEntry = pEntries + 1; pEntry->mUnknown60 != 0; pEntry++) {
            if (pEntry->mUnknown68 > pPrev->mUnknown68) {
                Entry_8011AFCC temp = *pEntry;
                *pEntry = *pPrev;
                *pPrev = temp;
                swapped = 1;
            }
            pPrev = pEntry;
        }
    } while (swapped);
}

extern "C" int fn_80125508() {
    return 0;
}
