/* Player assignment and per-state player logic (the "ASSIGN.C" unit at 0x800EFC68-0x80125F3C): the assignment
   queues and messages, formation and coverage assignments, and the handlers of many player states, compiled as
   one translation unit. Linked with holdouts: the functions that are not exact yet keep the original bytes and
   stay registered partials in comparisons.json. */
#include "engine/animchan.h"
#include "game/StyleTracker.h"
#include "game/fn_801248D4.h"
#include "game/Directions_8012430C.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/Block_803EB028.h"
#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/PlayBookTeam.h"
#include "game/State_803EB098.h"
#include "game/AudmonEvent.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
#include "engine/AnimStateAnimList.h"
#include "game/Ball.h"
#include "game/PlayBookDb.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/PlaySet.h"
#include "game/PlayBookGetPlay.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/Record_800DB60C.h"
#include "game/fn_801BE60C.h"
#include "game/AnimChanStartAnim.h"
#include "game/PreSnapPhase.h"
#include "game/Record_8011F4F8.h"
#include "game/Block_801BE60C.h"
#include "game/cu_8008E978.h"
#include "game/Class_80297B90.h"
#include "game/Move_8011AB38.h"
#include "game/Record_800CE608.h"
#include "game/Class_80148A58.h"

/* Views of the block at player +336. Only the accessed fields
   are declared. */
struct Block_800FBAA8 {
    char mUnknown0[36];
    int mUnknown36;
};

struct Block_800FCC24 {
    int mUnknown0;
    Point_8017886C mUnknown4[2];
    int mUnknown20;
    int mUnknown24;
    float mUnknown28;
    unsigned char mUnknown32;
    unsigned char mUnknown33;
    unsigned short mUnknown34;
    unsigned char mUnknown36;
    unsigned char mUnknown37;
    unsigned char mUnknown38;
    unsigned char mUnknown39;
};

struct Block_800FD650 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
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
    unsigned int mUnknown0;
    int mUnknown4;
};

struct State_80113AAC {
    int mRef;
    char mUnknown4[8];
    unsigned char mUnknown12;
    unsigned char mUnknown13;
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
    unsigned char mUnknown57;
    unsigned char mUnknown58;
    char mUnknown59[8];
    unsigned char mUnknown67;
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
    Object_80039F5C *mpUnknown60;
    char mUnknown64[4];
    float mUnknown68;
    char mUnknown72[8];
};

/* Bytes at +336 of the player object as fn_8010BA00, fn_8010B5B0 and
   fn_8010BC48 access them. Partial layout. */
struct State_8010BA00 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
};

/* Further views of the block at player +336. Only the accessed fields are
   declared. */
struct State_8010BED4 {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    int mUnknown12;
    float mUnknown16;
    char mUnknown20[28];
    short mUnknown48;
    char mUnknown50[2];
    int mUnknown52;
    short mUnknown56;
};

struct State_8010CAE8 {
    char mUnknown0[12];
    float mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    char mUnknown21[3];
    int mUnknown24;
    char mUnknown28[16];
    float mUnknown44;
    float mUnknown48;
};

struct State_8010D80C {
    Vector_80039F5C mUnknown0;
    char mUnknown12[4];
    float mUnknown16;
    char mUnknown20[6];
    unsigned char mUnknown26;
};

/* The word at +0 is also read back by its low byte. */
struct State_80111104 {
    union {
        int mUnknown0;
        unsigned char mUnknown0Bytes[4];
    };
    unsigned short mUnknown4;
    unsigned short mUnknown6;
};

/* View of the payload that fn_801BE60C returns, as fn_8011067C accesses it.
   Partial layout. */
struct Block_8011067C {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    float mUnknown12;
    float mUnknown16;
    float mUnknown20;
    int mUnknown24;
    int mUnknown28;
    int mUnknown32;
};

/* View of the player object from +1032. */
struct Block_8010FB4C {
    int mUnknown0;
    char mUnknown4[101];
    unsigned char mUnknown105;
};

struct State_80111794 {
    union {
        int mUnknown0;
        unsigned char mUnknown0Bytes[4];
    };
    int mUnknown4;
};

extern "C" {
void fn_800B6E68(Object_80039F5C *p, Input_800B6D34 *pInput);
}

extern "C" {
int fn_800B7FE8(Object_80039F5C *p);
}

extern "C" {
int fn_800CA5CC(Object_80039F5C *p, int a, int b);
}

extern "C" {
void fn_800B8344(Object_80039F5C *p);
}

extern "C" {
int fn_800B7E60(Object_80039F5C *p);
}

extern "C" {
int fn_800B7F34(Object_80039F5C *p);
}

extern "C" {
int PlayerMoveGetKind(Object_80039F5C *p);
}

extern "C" {
void PlayerMoveSetResult(Object_80039F5C *p, int a);
}

extern "C" {
extern float lbl_803EAF30;
}

extern "C" {
extern unsigned short lbl_803EAF5E;
}

/* Record that fn_8010B738 and fn_8011067C read through each table entry.
   Partial layout. */
struct Record_8010B738 {
    char mUnknown0[4];
    Key_80110630 mUnknown4;
    unsigned char mUnknown7;
    char mUnknown8[4];
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
    float mUnknown24;
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

/* Input of fn_801076F0 and fn_80108074. Partial layout. */
struct Input_801076F0 {
    char mUnknown0[4];
    Point_8017886C mUnknown4;
    char mUnknown12[4];
    Point_8017886C mUnknown16;
    char mUnknown24[16];
    Point_8017886C mUnknown40;
};

/* View of the player block at +336 that fn_80108074 reads. Partial layout. */
struct Block_80108074 {
    char mUnknown0[4];
    Point_8017886C mUnknown4;
};

/* Bytes +0 and +1 of the player block at +336 as fn_80105898 and
   fn_80105AF4 access them. Partial layout. */
struct State_80105898 {
    signed char mUnknown0;
    unsigned char mUnknown1;
};

extern float lbl_803EAEF4;

extern Object_80039F5C *lbl_803EAF10;

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

/* Object pointer, three positions, a pair and a float filled by fn_800F39FC
   and passed to fn_800F2EC8, fn_800F30AC, fn_800F3284, fn_800F3838,
   fn_800F3A6C, fn_800F3B54, fn_800F3D38, fn_800F3F90 and fn_800F4038. Only
   the accessed prefix is declared; the size is unknown. */
struct Points_800F3A6C {
    Ball_t *mpUnknown0;
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
    unsigned char mUnknown24;
};

struct Object_800F4E14 {
    char mUnknown0[20];
    int mUnknown20;
};

/* Entry reached through List_801018B4 items and read by fn_801018B4. */
struct Entry_801018B4 {
    char mUnknown0[4];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    char mUnknown7[1];
    int mUnknown8;
    int mUnknown12;
    unsigned short mUnknown16;
};

/* 8-byte item of List_801018B4: two halfwords for AnimChanStartAnim and the
   entry pointer. */
struct Item_801018B4 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Entry_801018B4 *mpEntry;
};

/* Halfword count followed by items from +4. */
struct List_801018B4 {
    unsigned short mCount;
    char mUnknown2[2];
    Item_801018B4 mItems[1];
};

/* View of the player +336 storage written by fn_80101B7C. */
struct State_80101B7C {
    char mUnknown0[8];
    int mUnknown8;
};

/* View of the player +336 storage read by fn_801045BC. */
struct State_801045BC {
    char mUnknown0[4];
    int mUnknown4;
};

extern "C" {
void PlyrSetPendingMsg(Object_80039F5C *p, Message_800F01CC *pMessage, int value);
}

extern "C" {
void fn_800B6714(Object_80039F5C *p, int port);
}

extern "C" {
void PlayerMoveBegin(Object_80039F5C *p, int a, int b);
}

extern "C" {
void fn_800E9528(Object_80039F5C *p);
}

extern "C" {
int fn_800E96EC(Object_80039F5C *p, Object_80039F5C *pOther);
}

extern "C" {
int fn_80178308(void);
}

extern "C" {
int fn_80178320(void);
}

extern "C" {
int fn_801CFE40(float y, float x);
}

extern "C" {
int MathAngleDiff(int a, int b);
}

extern "C" void fn_80227690(void *pOut, void *pA, void *pB);

extern "C" {
extern float lbl_803EAF58;
}

extern "C" {
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
}

extern "C" {
int fn_8009F7A4(Object_80039F5C *p, Object_80039F5C **ppOut);
}

extern "C" {
int fn_8009FE24(Object_80039F5C *p);
}

extern "C" {
void fn_8016DF34(Object_80039F5C *p);
}

extern "C" {
int fn_801783AC(int bit);
}

extern "C" {
void fn_8009A8D4(void *p);
}

extern "C" {
int fn_8009EAB0(Object_80039F5C *p, int a);
}

extern "C" {
int fn_8009EF6C(void *p);
}

extern "C" {
int fn_80099AD0(Object_80039F5C *p, Ball_t *pBall, int a, int b, int c, int d, int e);
}

extern "C" {
int fn_80099C80(Object_80039F5C *p, Ball_t *pBall, int a, int *pOut, int *pOut2);
}

extern "C" {
int fn_80099F04(Object_80039F5C *p, int a, unsigned char index);
}

extern "C" {
int fn_8009A1A8(Object_80039F5C *p, int a, int b, int c, int index);
}

extern "C" {
int fn_800C1180(Object_80039F5C *p);
}

extern "C" {
float fn_800CA9B4(int kind, Object_80039F5C *p);
}

extern "C" {
void fn_800CE674(Object_800CE674 *p);
}

extern "C" {
void fn_800CE684(Object_800CE674 *p);
}

extern "C" {
void fn_800D7A0C(Object_80039F5C *p, int a);
}

extern "C" {
int fn_800E815C(Object_80039F5C *p, int a, int b);
}

extern "C" {
int fn_800E98A4(Object_80039F5C *p, Object_80039F5C *pOther);
}

extern "C" {
void PlyrCollideRemoveExempt(Object_80039F5C *p, Object_80039F5C *pOther);
}

extern "C" {
int fn_801486A0(void);
}

extern "C" {
int fn_801520C4(Object_80039F5C *p, unsigned char *pIndex);
}

extern "C" {
void HudClearMashPlayers(int a, int b);
}

extern "C" {
void *fn_8023816C(void *pHandle);
}

extern "C" {
extern float gPlyrMoveFwdSpeed;
}

extern "C" {
void PlyrClearPendingMsg(Object_80039F5C *p, int a);
}

extern "C" {
void fn_8009D1AC(Object_80039F5C *p);
}

extern "C" {
int fn_800A2178(void);
}

extern "C" {
void fn_800A3B58(Object_80039F5C *p, int a, int b);
}

extern "C" {
int fn_801485D4(void);
}

extern "C" {
int TutorialIsActive(void);
}

extern "C" {
unsigned char TutorialIsStepDone(void);
}

extern "C" {
int fn_80178348(void);
}

extern "C" {
int fn_80178360(void);
}

extern "C" void fn_80227264(void *pOut, void *p, float scale);

extern "C" void fn_8022765C(void *pOut, void *pA, void *pB);

extern "C" {
float fn_80237260(int stream);
}

extern "C" {
extern unsigned char lbl_803EAEE8;
}

extern "C" {
extern Queue_800EFE0C **lbl_803EAE14;
}

extern "C" {
extern Record_803EAE18 *lbl_803EAE18;
}

extern "C" {
extern float lbl_803EAE1C;
}

extern "C" {
extern Input_800B6D34 lbl_802DAAD0;
}

extern "C" {
extern unsigned int *lbl_802EE928[];
}

extern "C" {
extern int *lbl_802EE938[];
}

extern "C" {
void fn_800A5A8C(int a, Object_80039F5C *p, Object_80039F5C *pOther);
}

extern "C" {
int fn_800DD648(Object_80039F5C *p);
}

extern "C" {
unsigned int fn_80178D18(int team);
}

extern "C" {
int fn_800B76E8(Object_80039F5C *p);
}

extern "C" {
int CarrierMoveStart(Object_80039F5C *p, int a);
}

extern "C" {
int fn_800AD0E4(int team);
}

extern "C" {
int fn_800C53D8(Object_80039F5C *p);
}

extern "C" {
void HudSetMashPlayers(int a, int b, unsigned char c);
}

extern "C" {
void fn_80178718(Object_80039F5C *p);
}

extern "C" {
int fn_801787A0(void);
}

extern "C" {
int fn_80238258(const void *pA, const void *pB, unsigned int size);
}

extern "C" {
int fn_80238278(const void *p, int size, int seed);
}

extern "C" {
int fn_800C8BAC(Object_80039F5C *p, int a);
}

extern "C" {
unsigned char *PlyrGetPendingMsg(Object_80039F5C *p);
}

extern "C" {
void CamGameSetModeAll(int a);
}

extern "C" {
extern float lbl_803EAED8;
}

extern "C" {
extern unsigned int lbl_803EAEDC;
}

extern "C" {
void fn_800A2190(int bit);
}

extern "C" {
void fn_800A60D8(Object_80039F5C *p, Object_80039F5C *pOther);
}

extern "C" {
void PassIconsShow(int mode);
}

extern "C" {
int PassIconsAreShown(void);
}

extern "C" {
PlayBookFormation_t *PlayBookGetFormation(int team);
}

extern "C" void fn_80227538(void *pOut, int angle, float length);

extern "C" float fn_802276E8(void *pA, void *pB);

extern "C" {
float fn_80178A08(void);
}

extern "C" {
float fn_80178A44(void);
}

extern "C" {
int fn_801784E8(void);
}

extern "C" {
int PlayerActionAnimIsPassReady(Object_80039F5C *p);
}

extern "C" {
void PlayerActionAnimSteerPassReady(Object_80039F5C *p, int angle, float value);
}

extern "C" float fn_8022710C(void *p);

extern "C" {
int fn_801BE068(void *a, void *b, void *c, unsigned short d, float e, void *pRecord);
}

extern "C" {
Point_8017886C fn_80177FFC(int team);
}

extern "C" {
unsigned char fn_8009F6B4(void);
}

extern "C" {
int fn_8009F778(Object_80039F5C *p);
}

extern "C" {
void *fn_800AEE20(Object_80039F5C *p);
}

extern "C" {
void fn_8009BD60(Object_80039F5C *p);
}

extern "C" {
int fn_800B6644(int index);
}

extern "C" {
Record_800B8694 *fn_800B8694(int index);
}

extern "C" {
int MemFill(void *pDest, int size, int value, int width);
}

extern "C" {
void fn_800A8954(int event, int team, Object_80039F5C *p);
}

extern "C" {
int fn_800B83F4(Object_80039F5C *p);
}

extern "C" {
int AnimChanIsMirrored(Entry_800EAC9C *pEntry);
}

extern "C" {
void AnimChanSetMirrored(Entry_800EAC9C *pEntry, int flag);
}

extern "C" {
void AnimSeqSetSpeed(void *p, float value);
}

extern "C" {
float MathInverse(float value);
}

extern "C" {
int fn_800B83A0(Object_80039F5C *p);
}

extern "C" {
void AudmonEventPostId(int type, Vector_80039F5C *pPos, int id, int a, int b, int c);
}

extern "C" {
extern float gFrameTimeScale;
}

extern "C" void fn_8022732C(void *pOut, void *p, float scale);

extern "C" {
int fn_800C4B6C(Object_80039F5C *p);
}

extern "C" {
int fn_800CE4A8(Query_800CE770 *pQuery);
}

extern "C" {
float fn_800C49A4(Object_80039F5C *p, float value);
}

extern "C" {
int fn_801BE068(void *a, void *b, void *c, unsigned short d, float e, void *p);
}

extern "C" {
Object_80039F5C *fn_8015286C(void *pSet, int index);
}

extern "C" {
int fn_8015310C(void *pSet);
}

extern "C" {
extern unsigned char lbl_803EAE20[8];
}

extern "C" {
int fn_800AC3FC(Object_80039F5C *p, int value);
}

extern "C" {
void fn_800C89F0(Object_80039F5C *p, int angle, int a, int b, float scale);
}

extern "C" {
void BallSolveFallToHeight(Ball_t *pBall, float height, float *pTime, Vector_80039F5C *pLanding);
}

extern "C" {
void fn_801528E0(void *pSet, Point_8017886C *pOut);
}

extern "C" {
int fn_800AC3A0(Object_80039F5C *p);
}

extern "C" void fn_802271A4(void *pOut, void *p);

extern "C" {
float fn_801CFB94(int angle);
}

extern "C" {
int fn_8009A6EC(Object_80039F5C *p);
}

extern "C" {
int fn_800997F4(Object_80039F5C *p, Ball_t *pBall, float range, void *pBlock, int a, int b, int c, int *pOutA,
                int *pOutB);
}

extern "C" {
extern char lbl_8031BDD4[];
}

/* One 12-byte entry of the receiver list built by fn_800FAECC. */
struct Entry_800FAECC {
    Object_80039F5C *mpPlayer;
    float mX;
    unsigned char mKind;
};

/* View of the player +336 storage used by fn_80102664. */
struct State_80102664 {
    unsigned char mUnknown0;
    char mUnknown1[2];
    unsigned char mUnknown3;
};

extern "C" int PlayBookGetReceiver(int team, int index, unsigned char *pOut);

extern "C" void TutorialSetMoveDone(int a, int b);

extern unsigned int lbl_802DAB54[];

extern "C" {
void PassIconsHide(void);
}

extern "C" {
void PassIconsClearReplayFlag(void);
}

extern "C" {
int PassIconsWereShown(void);
}

extern "C" {
int fn_800A61E0(void);
}

extern "C" {
void QbPassRestoreReceiverOptions(Object_80039F5C *p);
}

extern unsigned int lbl_802DAB48[];

extern "C" {
extern Block_803EB028 *lbl_803EB028;
}

extern "C" {
extern State_803EB098 *lbl_803EB098;
}

extern "C" {
extern Lookup_8012078C *lbl_803EB09C;
}

extern "C" {
extern float lbl_802DB004[];
}

extern "C" {
int fn_80165098(PlayBookPlay_t *pRecord);
}

extern "C" {
int fn_801650BC(PlayBookPlay_t *pRecord);
}

extern "C" {
int fn_801650DC(PlayBookPlay_t *pRecord);
}

extern "C" {
int fn_801650FC(PlayBookPlay_t *pRecord);
}

extern "C" {
void fn_800A5A88(void *p);
}

extern "C" {
void SortArray(int a, void *pBase, int count, int size, int (*pCompare)(void *, void *),
                 void (*pSwap)(void *, void *), int b, int c);
}

struct Entry_8011AFCC_800F0960 {
    char mUnknown0[60];
    int mUnknown60;
    char mUnknown64[4];
    float mUnknown68;
    char mUnknown72[8];
};

/* View of the payload that fn_801BE60C returns, as fn_8011067C accesses it.
   Partial layout. */
struct Block_8011067C_800F0960 {
    char mUnknown0[12];
    float mUnknown12;
    float mUnknown16;
    char mUnknown20[4];
    int mUnknown24;
};

/* 8-byte item of List_801018B4_800F0960; only the leading pointer is read. */
struct Item_801018B4_800F0960 {
    Entry_801018B4 *mpEntry;
    char mUnknown4[4];
};

/* Halfword count followed by items from +8. */
struct List_801018B4_800F0960 {
    unsigned short mCount;
    char mUnknown2[6];
    Item_801018B4_800F0960 mItems[1];
};

/* 92-byte state allocated through fn_80238174 under the id 'blck'
   (fn_8011DF3C). */
struct Block_803EB028_800F0960 {
    int mUnknown0;
    char mUnknown4[80];
    unsigned int mUnknown84;
    char mUnknown88[1];
    unsigned char mUnknown89;
    unsigned char mUnknown90;
    char mUnknown91[1];
};

/* 48-byte entry of Plan_80121264_800F0960; the array fills +0 to +1440. */
struct Entry_80120E98_800F0960 {
    char mUnknown0[12];
    float mUnknown12;
    char mUnknown16[20];
    int mUnknown36;
    char mUnknown40[8];
};

/* 32-byte entry of Plan_80121264_800F0960; the array fills +1444 to +2372. */
struct Entry_801230B8_800F0960 {
    char mUnknown0[16];
    int mUnknown16;
    char mUnknown20[8];
    float mUnknown28;
};

/* 2376-byte record cleared and filled by fn_80121264 (fn_801231E4 keeps one
   on its stack). */
struct Plan_80121264_800F0960 {
    Entry_80120E98_800F0960 mUnknown0[30];
    int mUnknown1440;
    Entry_801230B8_800F0960 mUnknown1444[29];
    unsigned int mUnknown2372;
};

extern "C" {
int fn_80178C9C(void);
}

extern "C" {
int fn_800BA6F8(void);
}

extern "C" {
int fn_800BAA24(void);
}

extern "C" float fn_802270A4(void *p);

extern "C" {
extern float lbl_803EAE28;
}

/* View of the block at player +336 that fn_800F4E14 and fn_800F6158
   address. */
struct Object_800F4E14_800F60BC {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    char mUnknown16[4];
    int mUnknown20;
    unsigned char mUnknown24;
};

extern "C" {
int fn_8009E9A4(void);
}

extern "C" {
extern float lbl_803EAE30;
}

extern "C" {
extern float lbl_803EAE34;
}

extern "C" {
extern float lbl_803EAE38;
}

extern "C" {
extern float lbl_803EAE3C;
}

/* View of the block at player +336 (same layout as Block_800F8A88 in
   src/game/cu_800F81C0.cpp). */
struct Block_800F7314 {
    int mRef;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
    unsigned char mUnknown23;
    unsigned char mUnknown24;
    unsigned char mUnknown25;
    unsigned char mUnknown26;
    unsigned char mUnknown27;
};

extern "C" {
float fn_801CFB18(int angle);
}

extern "C" {
float fn_80178A2C(void);
}

extern "C" {
int PlayerCutGetRunHeading(Object_80039F5C *p);
}

extern "C" {
extern float lbl_803EAE2C;
}

/* View of the block at player +336 used by fn_800F81C0, fn_800F846C,
   fn_800F8588, fn_800F8828, fn_800F8A88 and fn_800FA0DC. */
struct Block_800F8A88 {
    int mRef;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
    unsigned char mUnknown23;
    unsigned char mUnknown24;
    unsigned char mUnknown25;
    unsigned char mUnknown26;
    unsigned char mUnknown27;
};

extern "C" {
int PlayerCutGetAnimLength(unsigned char a);
}

extern "C" {
int PlayerCutGetAnimTime(Object_80039F5C *p);
}

extern "C" {
extern float lbl_803EAE40;
}

extern "C" {
extern float lbl_803EAE44;
}

extern "C" {
extern float lbl_803EAE48;
}

/* View of the block at player +336 used by fn_800F8D2C and fn_800F9024. */
struct Block_800F8D2C {
    int mRef;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
    unsigned char mUnknown23;
};

extern "C" {
extern float lbl_803EAE4C;
}

extern "C" {
extern float lbl_803EAE50;
}

extern "C" {
extern float lbl_803EAE54;
}

/* View of the block at player +336 used by fn_800F930C. */
struct Block_800F930C {
    int mRef;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned int mUnknown16;
};

/* View of the block whose address fn_8011F4EC returns. */
struct Block_800FAD2C {
    char mUnknown0[409];
    unsigned char mUnknown409[3];
    char mUnknown412[3];
    unsigned char mUnknown415[3];
};

extern "C" {
int PlayBookGetReceiver(int team, int index, unsigned char *pOut);
}

extern "C" {
extern float lbl_803EAE60;
}

/* View of the block at player +336 used by the state 22 handlers
   (as Block_800F8A88 in src/game/cu_800F930C.cpp). */
struct Block_800FA300 {
    int mRef;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
    unsigned char mUnknown23;
    unsigned char mUnknown24;
    unsigned char mUnknown25;
    unsigned char mUnknown26;
    unsigned char mUnknown27;
};

extern "C" {
int fn_800AC2C0(int team);
}

extern "C" {
Object_80039F5C *fn_8009BCE8(int *pRef);
}

extern "C" {
Object_80039F5C *PlyrGet(int team, unsigned short index);
}

extern "C" {
int fn_800A5C04(Object_80039F5C *p, int a, int b);
}

extern "C" {
int fn_8009E180(Object_80039F5C *p);
}

extern "C" {
int fn_800B65A0(int team);
}

extern "C" {
int fn_8009F258(Object_80039F5C *p);
}

extern float gPlyrMoveFwdSpeed;

extern "C" {
unsigned char fn_80164B78(void);
}

extern float lbl_803EAE64;

extern "C" {
unsigned char fn_800C0658(void);
}

extern "C" {
void DivotSkipNextSteps(Object_80039F5C *p);
}

extern "C" {
void fn_80051B88(Object_800B26B0 *pMotion, float value);
}

struct State_800FDAC8 {
    short mUnknown0;
    char mUnknown2[6];
    Point_8017886C mUnknown8;
    char mUnknown16[32];
    int mUnknown48;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
};

extern "C" {
int fn_800CB708(Object_80039F5C *p, int *pOut, Point_8017886C target, int angle, int flag);
}

extern "C" {
int fn_800CB580(Object_80039F5C *p, int *pOut, Point_8017886C target, int angle, int flag);
}

extern "C" {
int fn_80177F70(void);
}

extern float lbl_803EAE68;

extern float lbl_803EAE6C;

extern float lbl_803EAE70;

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

static inline void GetFormationPoint(PlayBookFormation_t *pTeam, int index, Point_8017886C *pOut)
{
    PlayBookPosition_t *pEntry = &pTeam->mUnknown8.mUnknown84[0][index];

    pOut->mX = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mX;
    pOut->mY = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mY;
}

static inline void AddPoint(Point_8017886C *pOut, Point_8017886C *pOffset)
{
    pOut->mX += pOffset->mX;
    pOut->mY += pOffset->mY;
}

extern "C" {
int fn_801CFE40(float,float);
}

extern "C" {
int MathAngleDiff(int,int);
}

extern "C" {
float fn_801CFB94(int);
}

extern "C" {
float fn_80260B1C(float);
}

extern "C" void fn_80227248(void *pOut, void *p, float scale);

extern "C" void fn_80227904(void *pOut, void *pA, void *pB, float t);

extern "C" {
float fn_80237260(int);
}

extern "C" {
Point_8017886C fn_80177FFC(int);
}

extern "C" {
Point_8017886C fn_80177FE0(void);
}

extern "C" {
int fn_801783AC(int);
}

extern "C" {
unsigned int fn_80178D18(int);
}

extern "C" {
float fn_80178A5C(void);
}

extern "C" {
float PlyrMoveGetRatedSpeed(Object_80039F5C *,float,float);
}

extern "C" {
int PlayerCutGetStartHeading(Object_80039F5C *);
}

extern "C" {
int PlayerCutGetTargetHeading(Object_80039F5C *);
}

extern "C" {
float PlayerCutGetRunSpeed(Object_80039F5C *,float);
}

extern "C" {
int PlayBookGetReceiver(int,int,unsigned char *);
}

extern "C" {
void fn_8009BD2C(Object_80039F5C *,int *);
}

extern "C" {
unsigned short fn_801BE648(void *p);
}

extern "C" {
int fn_801BE068(void *,void *,void *,unsigned short,float,void *);
}

extern "C" {
void fn_801BE67C(void *,void *,void *,void *);
}

extern "C" {
void fn_800C89F0(Object_80039F5C *,int,int,int,float);
}

extern "C" {
void fn_8009D284(Object_80039F5C *,Object_80039F5C *);
}

extern "C" {
extern float gPlyrMoveFwdSpeed,lbl_803EAE84;
}

extern "C" {
extern float lbl_803EAEA4,lbl_803EAEA8,lbl_803EAEAC,lbl_803EAEB0;
}

extern "C" {
extern float lbl_803EAEB4,lbl_803EAEB8,lbl_803EAEBC;
}

extern "C" {
extern unsigned short lbl_803EAE76;
}

extern "C" {
extern float lbl_803EAE78,lbl_803EAE7C;
}

extern "C" {
extern unsigned int lbl_803EAE80;
}

extern "C" {
extern unsigned char lbl_803EAEA0;
}

extern "C" {
static inline float MapRange(float v, float inLo, float inHi, float outLo, float outHi)
{
    return (v - inLo) * (outHi - outLo) / (inHi - inLo) + outLo;
}
}

extern unsigned char lbl_803EAE88;

extern "C" {
int fn_800CA5CC(Object_80039F5C *p, int kind, int apply);
}

extern "C" {
void TutorialSetMoveDone(int index, int value);
}

extern float gFrameTimeScale;

extern float lbl_803EC9E8;

extern float lbl_803EAEC0;

struct State_801021C0 {
    char mUnknown0[2];
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    int mUnknown4;
    char mUnknown8[3];
    unsigned char mUnknown11;
};

extern "C" {
void PenaltyRollRoughing(Object_80039F5C *p);
}

struct State_80102470 {
    char mUnknown0[2];
    unsigned char mUnknown2;
};

struct Entry_801018B4_80102A78 {
    char mUnknown0[4];
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    int mUnknown8;
    int mUnknown12;
    unsigned short mUnknown16;
    char mUnknown18[2];
    float mUnknown20;
    float mUnknown24;
};

/* 8-byte item of List_801018B4_80102A78: two halfwords for AnimChanStartAnim and the
   entry pointer. */
struct Item_801018B4_80102A78 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Entry_801018B4_80102A78 *mpEntry;
};

struct List_801018B4_80102A78 {
    unsigned short mCount;
    char mUnknown2[2];
    Item_801018B4_80102A78 mItems[1];
};

struct State_80102A78 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    float mUnknown20;
    float mUnknown24;
    float mUnknown28;
    float mUnknown32;
    unsigned char mUnknown36;
};

extern "C" {
float AnimSeqGetTime(AnimSeq_t *p);
}

extern float lbl_803EAEC4;

extern "C" {
void fn_800B260C(short value);
}

extern "C" {
void fn_800B1584(int a, const float *pPos);
}

extern "C" {
void fn_801783D0(int bit, int on);
}

extern "C" {
void fn_80099568(int kind);
}

extern "C" {
void fn_8013AD04(Ball_t *pBall, Vector_80039F5C *pVelocity, int mode, float spin, float rate);
}

struct Type_803EA368;

extern Type_803EA368 *lbl_803EA368;

extern "C" void ReplayEventAdd(Type_803EA368 *p, int id, Object_80039F5C *pObject, Vector_80039F5C *pPos, int *pFacing);

extern "C" {
void SpchIGSetPassTarget(int id);
}

extern "C" {
void BallLaunchToTarget(Ball_t *pBall, Vector_80039F5C *pTarget, int mode, float speed, float spin, float side);
}

extern "C" {
void fn_80152068(int index, Vector_80039F5C *pOut);
}

extern "C" {
int TutorialAreMovesDone(unsigned long long mask);
}

extern "C" {
float PlyrMoveGetRatedSpeed(Object_80039F5C *p, float a, float b);
}

extern "C" {
void PenaltyCheckGrounding(Object_80039F5C *p);
}

extern float lbl_803EAEC8;

extern float lbl_803EAECC;

extern float lbl_803EAED0;

extern float lbl_803EAED4;

static inline float AddRatingNoise_80102D78(float base, float random, int rating)
{
    return rating <= 255 ? random * (255 - rating) * (1.0f / 255.0f) + base : base;
}

extern float lbl_803EAE8C;

extern float lbl_803EAE90;

extern float lbl_803EAE94;

extern float lbl_803EAE98;

extern float lbl_803EAE9C;

extern float lbl_803EAEB8;

extern "C" float fn_800C49EC(float limit);

extern "C" float fn_800CAAFC(Object_80039F5C *p);

extern "C" float fn_801CFB18(int angle);

extern "C" int fn_801CFDD0(float);

extern "C" int PlayerCutGetTargetHeading(Object_80039F5C *p);

extern "C" int PlayerCutGetStartHeading(Object_80039F5C *p);

extern "C" int PlayerCutGetMessageTurn(Message_800F01CC *pMessage);

extern "C" void PlayerCutGetAnimOffset(int a, unsigned char b, int angle, Point_8017886C *pOut);

extern "C" int PlayerCutGetAnimLength(unsigned char a);

extern "C" int PlayerCutGetTimeLeft(Object_80039F5C *p);

struct State_80104328 {
    Point_8017886C mTarget;
};

extern "C" float fn_800B2618(int);

struct Block_800F4A74_80104C9C {
    unsigned short mUnknown0;
    char mUnknown2[2];
    Vector_80039F5C mUnknown4;
    unsigned int mUnknown16;
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
    unsigned char mUnknown64;
    unsigned char mUnknown65;
    unsigned char mUnknown66;
    char mUnknown67[21];
};

extern unsigned int lbl_803EAEE0;

extern unsigned int lbl_803EAEE4;

extern "C" void fn_801BE67C(void *pA, void *pB, void *pC, void *p);

extern "C" int MathRLerp(int a, int b, float factor);

extern "C" int CharSkelGetJointByName(void *p, const char *pName);

struct Reach_80105630 {
    unsigned int mEnd;
    unsigned char mHand;
    unsigned char mBall;
};

extern "C" int fn_8023790C(void);

extern "C" void fn_8009CE88(Object_80039F5C *p, int *pRecord, int a);

extern "C" int BallStateGetPrev(Ball_t *pBall, int *pOut);

extern "C" Reach_80105630 *fn_8009CD00(Object_80039F5C *p, void (*pCallback)(Object_80039F5C *, Vector_80039F5C *, Reach_80105630 *),
                                       int a, unsigned int delay, int b);

extern "C" void fn_8009CEE4(Object_80039F5C *p, int ref, int joint, int a, int b);

extern "C" float AnimSeqGetTimeToOpcode(AnimSeq_t *p, int key);

extern float lbl_803EAEEC;

extern float lbl_803EAEF0;

extern "C" void fn_80227350(void *pOut, void *p, float scale);

struct Turn_8010680C {
    int mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
};

extern "C" int fn_8009C4B0(Table_80089904 *pTable, Key_80110630 *pKey);

struct Block_800F4A74_801077D8 {
    unsigned short mUnknown0;
    char mUnknown2[2];
    Vector_80039F5C mUnknown4;
    unsigned int mUnknown16;
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
    unsigned char mUnknown64;
    unsigned char mUnknown65;
    unsigned char mUnknown66;
    char mUnknown67[21];
};

extern "C" {
float fn_8009F168(Vector_80039F5C *p, void *pVelocity, Vector_80039F5C *pOther, float speed);
}

struct Block_800F4A74_8010810C {
    unsigned short mUnknown0;
    char mUnknown2[2];
    Vector_80039F5C mUnknown4;
    unsigned int mUnknown16;
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
    unsigned char mUnknown64;
    unsigned char mUnknown65;
    unsigned char mUnknown66;
    char mUnknown67[21];
};

/* The 88-byte block at player +336 as fn_80109150 initialises it and
   fn_80108954 updates it. */
struct Block_80109150 {
    char mUnknown0[36];
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
    char mUnknown55[1];
    unsigned char mUnknown56;
    unsigned char mUnknown57;
    short mUnknown58;
    unsigned char mUnknown60;
    unsigned char mUnknown61;
    unsigned char mUnknown62;
    unsigned char mUnknown63;
    unsigned char mUnknown64;
    unsigned char mUnknown65;
    unsigned char mUnknown66;
    char mUnknown67[21];
};

/* The 88-byte block at player +336. +0 to +16 hold the pass view that
   fn_80108C34 and fn_80108DF8 read from the other player's block. */

struct Block_800F4A74_80108A94 {
    unsigned short mUnknown0;
    char mUnknown2[2];
    Vector_80039F5C mUnknown4;
    unsigned int mUnknown16;
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
    unsigned char mUnknown64;
    unsigned char mUnknown65;
    unsigned char mUnknown66;
    char mUnknown67[21];
};

struct Sphere_80108DF8 {
    Vector_80039F5C mCenter;
    float mRadius;
};

extern "C" {
int PlyrRollContestedCatch(Object_80039F5C *p);
}

extern "C" {
float fn_800ACB8C(int team);
}

extern "C" {
unsigned int fn_800ABDA4(int team);
}

/* The 88-byte block at player +336. +0 to +16 hold the pass view that
   fn_80108C34 and fn_80108DF8 read from the other player's block. */

struct Block_800F4A74_80109248 {
    unsigned short mUnknown0;
    char mUnknown2[2];
    Vector_80039F5C mUnknown4;
    unsigned int mUnknown16;
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
    unsigned char mUnknown64;
    unsigned char mUnknown65;
    unsigned char mUnknown66;
    char mUnknown67[21];
};

/* View of the block at player +336 with the mode in the top 3 bits and the
   state in the next 4 bits of the word at +52, and the point at +56. */
struct Block_801096D4 {
    char mUnknown0[52];
    unsigned int mUnknown52Mode : 3;
    unsigned int mUnknown52State : 4;
    unsigned int mUnknown52Rest : 25;
    Point_8017886C mUnknown56;
};

extern "C" {
int fn_800AC324(int team);
}

extern "C" {
extern float lbl_803EAEF8;
}

extern "C" {
extern float lbl_803EAF08;
}

extern "C" {
extern float lbl_803EAF0C;
}

/* View of the block at player +336 that holds the animation entry index at
   +50. */
struct Block_80109CA0 {
    char mUnknown0[50];
    short mUnknown50;
};

/* View of the block at player +336 with the packed word at +52 (player
   +388); fn_8010A07C reads the 4-bit field at bit 25. */
struct Block_80109E48 {
    char mUnknown0[52];
    unsigned int mUnknown52 : 3;
    unsigned int mUnknown52State : 4;
    unsigned int mUnknown52Count : 4;
    unsigned int mUnknown52Rest : 21;
};

/* View of the block at player +336 that fn_80109F34 updates: the mode in
   the top 3 bits and the state in the next 4 bits of the word at +52, and
   the point at +56. */
struct Block_80109F34 {
    char mUnknown0[2];
    unsigned char mUnknown2;
    char mUnknown3[17];
    float mUnknown20;
    char mUnknown24[4];
    float mUnknown28;
    char mUnknown32[20];
    unsigned int mUnknown52Mode : 3;
    unsigned int mUnknown52State : 4;
    unsigned int mUnknown52Rest : 25;
    Point_8017886C mUnknown56;
};

/* The two players fn_80109990 writes. */
struct Pair_80109990 {
    Object_80039F5C *mpUnknown0;
    Object_80039F5C *mpUnknown4;
};

extern "C" {
int fn_800CB580(Object_80039F5C *p, int *pIndex, Point_8017886C target, int angle, int check);
}

extern "C" {
int fn_8009274C(unsigned char index);
}

extern "C" {
Object_80039F5C *fn_800963EC(Character_80093BCC *pCharacter);
}

extern "C" {
Object_80039F5C *fn_800963F4(Character_80093BCC *pCharacter);
}

/* View of the block at player +336 that fn_8010A4E8 clears and seeds: two
   halfwords at +48 and +50 and the packed word at +52. */
struct Block_8010A4E8 {
    char mUnknown0[48];
    short mUnknown48;
    short mUnknown50;
    unsigned int mUnknown52Mode : 3;
    unsigned int mUnknown52State : 4;
    unsigned int mUnknown52Count : 4;
    unsigned int mUnknown52Kind : 6;
    unsigned int mUnknown52Rest : 15;
};

extern "C" {
int fn_800A5DD0(Object_80039F5C *p);
}

extern "C" {
int fn_800ABCC0(Class_80297B90 *p);
}

extern "C" {
int fn_800AD9B4(void);
}

extern "C" void fn_802276B4(void *pOut, void *pA, void *pB);

/* View of the block at player +336 driven by fn_8010A640: the packed word at
   +52 holds the mode (top 3 bits), the state, a queued state, a kind and a
   signed 15-bit timer. */
struct Block_8010A640 {
    short mUnknown0;
    char mUnknown2[6];
    Point_8017886C mUnknown8;
    char mUnknown16[8];
    float mUnknown24;
    char mUnknown28[20];
    short mUnknown48;
    unsigned short mUnknown50;
    unsigned int mUnknown52Mode : 3;
    unsigned int mUnknown52State : 4;
    unsigned int mUnknown52Count : 4;
    unsigned int mUnknown52Kind : 6;
    int mUnknown52Timer : 15;
    Point_8017886C mUnknown56;
};

extern "C" {
int fn_800CB708(Object_80039F5C *p, int *pIndex, Point_8017886C target, int angle, int beyond);
}

extern "C" {
void fn_800CC388(Object_80039F5C *p);
}

extern "C" {
int fn_800E1044(Object_80039F5C *p, Vector_80039F5C *pTarget);
}

extern "C" {
int fn_8009D1F4(Object_80039F5C *p);
}

extern "C" {
int PlyrMoveIsFacingHeading(Object_80039F5C *p);
}

extern "C" {
void fn_8016DBE4(Object_80039F5C *p);
}

extern "C" {
void PossReleaseBall(Object_80039F5C *p);
}

extern "C" {
extern int lbl_803EAF04;
}

extern "C" {
extern unsigned int lbl_803EAF14;
}

extern "C" {
extern float lbl_803EAF18;
}

/* View of the block at player +336 as fn_8010AF48 resets it. */
struct Block_8010AF48 {
    int mUnknown0;
    short mUnknown4;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    unsigned char mUnknown8;
};

/* View of the block at player +336 that fn_8010AFB8 reads: a request word
   and two flag bytes. */
struct Block_8010AFB8 {
    int mUnknown0;
    short mUnknown4;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
};

extern "C" {
int fn_800B0F98(void);
}

extern "C" {
int fn_8016E928(void);
}

/* View of the block at player +336 as the animation callbacks use it. */
struct Block_8010BC90 {
    unsigned char mUnknown0;
    signed char mUnknown1;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
    char mUnknown4[16];
    int mUnknown20;
    unsigned short mUnknown24;
};

extern "C" {
extern unsigned char lbl_802DABBC[];
}

extern "C" {
extern float lbl_802DAB74[];
}

/* View of the block at player +336 as fn_8010BED4 sets it up and fn_8010BF5C
   updates it. */
struct State_8010BF5C {
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
    int mUnknown12;
    float mUnknown16;
    float mUnknown20;
    float mUnknown24;
    float mUnknown28;
    float mUnknown32;
    int mUnknown36;
    Point_8017886C mUnknown40;
    short mUnknown48;
    char mUnknown50[2];
    unsigned int mUnknown52;
    unsigned short mUnknown56;
};

extern "C" {
float PlayTrackGetPlayIdRate(void);
}

extern "C" {
float PlayTrackGetResult5Rate(void);
}

extern "C" {
int fn_80177C38(void);
}

extern "C" {
int fn_800DC21C(Object_80039F5C *p);
}

extern "C" {
extern float lbl_803EAF24;
}

extern "C" {
extern float lbl_803EAF28;
}

extern "C" {
extern float lbl_803EAF2C;
}

extern "C" {
extern float lbl_803EAF34;
}

extern "C" {
extern unsigned int lbl_803EAF38;
}

extern "C" {
extern float lbl_803EAF3C;
}

extern "C" {
extern float lbl_803EAF40;
}

extern "C" {
extern float lbl_803EAF44;
}

#define MIN(a, b) ((a) > (b) ? (b) : (a))

/* View of the block at player +336 as fn_8010CB58 runs its states. */
struct Block_8010CB58 {
    char mUnknown0[12];
    float mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    char mUnknown21[3];
    int mUnknown24;
};

extern "C" {
extern float lbl_803EAF48;
}

extern "C" {
extern float lbl_803EAF4C;
}

extern "C" {
void StyleTrackerFinishRun(void);
}

/* View of the block at player +336 used by fn_8010D090: an output slot at
   +24 and a position at +44. */
struct Block_8010D090 {
    char mUnknown0[24];
    char mUnknown24[20];
    Vector_80039F5C mUnknown44;
};

/* View of the ball carrier's block at player +336: fn_8010D090 checks byte
   1 of the record at +20 or +32, chosen by the carrier's state. */
struct Carrier_8010D090 {
    char mUnknown0[20];
    unsigned char mUnknown20[12];
    unsigned char mUnknown32[4];
};

struct State_8010D80C_8010D434 {
    Vector_80039F5C mUnknown0;
    char mUnknown12[4];
    float mUnknown16;
    char mUnknown20[6];
    unsigned char mUnknown26;
    unsigned char mUnknown27;
};

/* View of the block at player +336 that fn_8010D508 fills: a position, a
   scale, an animation pair and two flag bytes. */
struct Block_8010D508 {
    Vector_80039F5C mUnknown0;
    char mUnknown12[4];
    float mUnknown16;
    int mUnknown20;
    unsigned short mUnknown24;
    unsigned char mUnknown26;
    unsigned char mUnknown27;
};

/* View of the record a Table_80089904 entry points to, as fn_8010D508 reads
   it: two positions at +8 and +20 and a scale at +32. */
struct Info_8010D508 {
    char mUnknown0[8];
    Vector_80039F5C mUnknown8;
    Vector_80039F5C mUnknown20;
    float mUnknown32;
};

extern "C" {
int fn_8009C4B0(Table_80089904 *pTable, Key_80110630 *pKey);
}

extern "C" void fn_80227384(void *pOut, void *p, int angle);

extern "C" {
AnimStateAnimList_t lbl_80319ED8;
}

/* View of the block at player +336 as the animation callbacks use it. */
struct Block_8010BC90_8010D834 {
    unsigned char mUnknown0;
    char mUnknown1[2];
    unsigned char mUnknown3;
    char mUnknown4[16];
    int mUnknown20;
    unsigned short mUnknown24;
};

extern "C" {
extern float lbl_803EAF54;
}

/* Steering state fn_8010E59C keeps per player: a speed scale, the heading
   to run on, the heading to face, a countdown to the next update and two
   flag bytes. fn_8010DAB4 and fn_8010E15C fill and adjust it. */
struct Steer_8010DAB4 {
    float mSpeed;
    int mHeading;
    int mFacing;
    int mTimer;
    char mUnknown16[5];
    unsigned char mUnknown21;
    unsigned char mUnknown22;
};

extern "C" {
int fn_801783AC(int flag);
}

static inline int InRange(int v, int lo, int hi) { return v <= hi && v >= lo; }

#define MAX(a, b) ((a) < (b) ? (b) : (a))

/* Record that fn_8010B738 and fn_8011067C read through each table entry.
   Partial layout. */
struct Record_8010B738_8010F43C {
    char mUnknown0[4];
    Key_80110630 mUnknown4;
    unsigned char mUnknown7;
    char mUnknown8[4];
    int mUnknown12;
    int mUnknown16;
    int mUnknown20;
    float mUnknown24;
    float mUnknown28;
    float mUnknown32;
};

struct Entry_8010B738_8010F43C {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    Record_8010B738_8010F43C *mpRecord;
};

/* Counted table of 8-byte entries starting at +4. */
struct Table_8010B738_8010F43C {
    unsigned short mCount;
    char mUnknown2[2];
    Entry_8010B738_8010F43C mEntries[1];
};

/* The 12 bytes at player +336 as the timer that fn_8010FD94 clears and
   fn_80113498 advances. */
struct Timer_8010FD94 {
    unsigned int mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
};

/* The bytes at player +336 as fn_801108D4 sets them up. */
struct State_801108D4 {
    float mUnknown0;
    int mUnknown4;
    short mUnknown8;
    char mUnknown10[2];
    unsigned char mUnknown12;
    unsigned char mUnknown13;
    unsigned char mUnknown14;
};

/* The bytes at player +336 as fn_8010F43C sets them up. */
struct State_8010F43C {
    float mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
};

/* View of player +336 while fn_801113DC's state runs. */
struct State_801113DC {
    int mUnknown0;
    float mUnknown4;
    char mUnknown8[4];
    unsigned char mUnknown12;
    char mUnknown13[3];
    Object_80039F5C *mpUnknown16;
    char mUnknown20[1];
};

extern "C" {
int fn_8009FB60(Object_80039F5C *p);
}

extern "C" {
void fn_800DB520(void *pBlock, Object_80039F5C *p, Object_80039F5C *pOther, float value);
}

extern "C" {
void PlyrCollideAddExempt(Object_80039F5C *p, Object_80039F5C *pOther);
}

extern "C" {
void TutorialSetMoveDone(int a, int b);
}

extern "C" {
Object_80039F5C *fn_8017876C(void);
}

extern "C" {
float AnimSeqGetTimeToOpcode(AnimSeq_t *p, int key);
}

extern "C" float fn_8022785C(void *pA, void *pB);

extern "C" {
extern unsigned char lbl_803EAF50;
}

extern "C" {
extern unsigned char lbl_803EAF51;
}

extern "C" {
int CharSkelGetJointByName(void *p, const char *pName);
}

/* Bytes at player +336 as fn_80113680 sets them up. */
struct State_80113680 {
    int mRef;
    int mUnknown4;
    float mUnknown8;
    unsigned char mUnknown12;
    unsigned char mUnknown13;
    unsigned char mUnknown14;
    unsigned char mUnknown15;
    char mUnknown16[2];
    short mUnknown18;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
};

/* Bytes at player +336 as fn_80113C20 sets them up. */
struct State_80113C20 {
    int mRef;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    int mUnknown20;
    unsigned char mUnknown24;
    unsigned char mUnknown25;
    short mUnknown26;
    unsigned char mUnknown28;
    unsigned char mUnknown29;
    unsigned char mUnknown30;
    unsigned char mUnknown31;
    Record_800DB60C mUnknown32;
    unsigned char mUnknown56;
    unsigned char mUnknown57;
    unsigned char mUnknown58;
    unsigned char mUnknown59;
    int mUnknown60;
    short mUnknown64;
    unsigned char mUnknown66;
    unsigned char mUnknown67;
    unsigned char mUnknown68;
};

/* The bytes at player +336 as fn_80113E74 updates them; +32 is the block
   passed to fn_800DB7A4 and fn_800DB8B4. */
struct State_80113E74 {
    int mRef;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    char mUnknown16[4];
    unsigned int mUnknown20;
    char mUnknown24[1];
    unsigned char mUnknown25;
    short mUnknown26;
    unsigned char mUnknown28;
    unsigned char mUnknown29;
    unsigned char mUnknown30;
    unsigned char mUnknown31;
    char mUnknown32[24];
    unsigned char mUnknown56;
    char mUnknown57[2];
    unsigned char mUnknown59;
    int mUnknown60;
    unsigned short mUnknown64;
    char mUnknown66[2];
    unsigned char mUnknown68;
};

/* The bytes at +336 of the player that fn_80113E74's reference names. */
struct Other_80113E74 {
    char mUnknown0[4];
    unsigned int mUnknown4;
    float mUnknown8;
};

/* Payload of fn_801BE60C as fn_80114F64 reads it. */
struct Block_80114F64 {
    char mUnknown0[4];
    Point_8017886C mUnknown4;
    char mUnknown12[16];
    unsigned char mUnknown28;
};

/* Bytes at player +336 as fn_80115248 reads them for states 40 and 92. */
struct State_80115248 {
    char mUnknown0[12];
    float mUnknown12;
    char mUnknown16[4];
    Object_80039F5C *mpUnknown20;
};

/* The bytes at player +336 as fn_8011569C drives them. */
struct State_8011569C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned char mUnknown16;
    unsigned char mUnknown17;
    char mUnknown18[2];
    unsigned char mUnknown20;
};

/* 16-byte zone records at +24 of the block fn_8011F4EC returns. */
struct Zone_8011569C {
    float mUnknown0;
    float mUnknown4;
    float mLow;
    float mHigh;
};

struct Field_8011569C {
    char mUnknown0[24];
    Zone_8011569C mZones[1];
};

extern "C" {
Object_80039F5C *fn_8009EC60(unsigned int index, Point_8017886C *pOut);
}

extern "C" {
int fn_8009EFDC(int side);
}

extern "C" {
void fn_800B2370(Object_80039F5C *, int, Object_80039F5C *, float);
}

extern "C" {
Object_80039F5C *fn_800B6544(int index);
}

extern "C" {
int fn_800CD35C(int mode, Object_80039F5C *p);
}

extern "C" {
int fn_800CE690(Object_800CE674 *p);
}

extern "C" {
float fn_800CE73C(Object_800CE674 *p);
}

extern "C" {
void fn_800D7A18(Object_80039F5C *p);
}

extern "C" {
void fn_800DB7A4(void *pBlock, Object_80039F5C *p);
}

extern "C" {
void fn_800DB8B4(void *pBlock, Object_80039F5C *p);
}

extern "C" {
void fn_800DF134(Object_80039F5C *p, Point_8017886C offset, int angle, int key);
}

extern "C" {
int fn_800E1554(Object_80039F5C *p);
}

extern "C" {
float BallGetHeightAtTime(Ball_t *pBall, float t);
}

extern "C" {
void fn_801410F4(int a);
}

extern "C" {
void fn_8016F6F4(Object_80039F5C *p, Object_80039F5C *pOther);
}

extern "C" {
void PossFumble(Object_80039F5C *p);
}

extern "C" {
void PossTryFumble(Object_80039F5C *p, Object_80039F5C *pOther);
}

extern "C" {
void PossStartFumble(void);
}

extern "C" {
void PossGrabBall(Object_80039F5C *p);
}

extern "C" {
int PossCheckDownedBall(Object_80039F5C *p);
}

extern "C" {
int PenaltyRollFacemask(void);
}

extern "C" {
int fn_801784C4(void);
}

extern "C" {
void RumbleStart(int a, int b, int c);
}

extern "C" float fn_80227890(void *pA, void *pB);

extern "C" {
void fn_80227970(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC, Vector_80039F5C *pOut, float *pValue,
                 float *pOther);
}

extern "C" {
extern float lbl_803EAF60;
}

extern "C" {
extern float lbl_803EAF64;
}

extern "C" {
extern float lbl_803EAF68;
}

extern "C" {
extern float lbl_803EAF6C;
}

extern "C" {
extern float lbl_803EAF70;
}

extern "C" {
extern float lbl_803EAF74;
}

extern "C" {
extern float lbl_803EAF78;
}

extern "C" {
extern unsigned char lbl_803EAF7C;
}

extern "C" {
extern unsigned char lbl_803EAF7D;
}

extern "C" {
extern float lbl_803EAF80;
}

extern "C" {
extern float lbl_803EAF84;
}

extern "C" {
extern float lbl_803EAF88;
}

extern "C" {
extern float lbl_803EAF8C;
}

extern "C" {
extern unsigned char lbl_803EAF90;
}

extern "C" {
extern unsigned char lbl_803EAF91;
}

extern "C" {
extern int lbl_803EAF94;
}

extern "C" {
extern unsigned char lbl_803EAF98;
}

extern "C" {
extern float lbl_803EAF9C;
}

extern "C" {
extern float lbl_803EAFA0;
}

extern "C" {
extern float lbl_803EAFA4;
}

extern "C" {
extern float lbl_803EAFA8;
}

extern "C" {
extern float lbl_803EAFAC;
}

extern "C" {
extern float lbl_803EAFB0;
}

extern "C" {
extern float lbl_803EAFB4;
}

extern "C" {
extern float lbl_803EAFB8;
}

extern "C" {
extern float lbl_803EAFBC;
}

extern "C" {
extern float lbl_803EAFCC;
}

extern "C" {
extern float gPlyrMoveBaseSpeed;
}

extern "C" float lbl_803EAFC0;

extern "C" float lbl_803EAFC4;

extern "C" float lbl_803EAFC8;

struct State_80116C34 {
    unsigned short mUnknown0;
    short mUnknown2;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned char mUnknown16;
    char mUnknown17;
    short mUnknown18;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    char mUnknown22[2];
    unsigned char mUnknown24;
};

/* View of the block at player +336 used by fn_80116B98. */
struct Block_80116B98 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned char mUnknown16;
    char mUnknown17[1];
    short mUnknown18;
    unsigned char mUnknown20;
};

extern "C" {
signed char fn_8009AF00(int team, signed char value);
}

extern "C" {
int fn_801783AC(int value);
}

extern "C" {
int fn_8009EFDC(int index);
}

extern "C" {
extern float lbl_803EAFE8;
}

extern "C" {
extern float lbl_803EAFEC;
}

extern "C" {
extern float lbl_803EAFF0;
}

extern "C" {
extern float lbl_803EAFF4;
}

extern "C" {
extern float lbl_803EAFF8;
}

extern "C" {
extern float lbl_803EAFFC;
}

extern "C" {
extern float lbl_803EB000;
}

extern "C" {
static inline int IsBallAway(const Vector_80039F5C &ball)
{
    int away = 0;
    if (ball.mY > fn_80177FE0().mY + 3.0f) {
        away = 1;
    } else if (!(fabsf(ball.mX - fn_80177FE0().mX) <= 3.0f)) {
        away = 1;
    }
    return away;
}
}

/* View of the record returned by fn_8011F4EC: a count at +408 and the
   player indices that follow it. */
struct Record_80117934 {
    char mUnknown0[408];
    unsigned char mUnknown408;
    unsigned char mUnknown409[3];
};

/* View of the block at player +336 used by fn_80117934. */
struct Block_80117934 {
    char mUnknown0[20];
    Object_80039F5C *mpUnknown20;
};

extern "C" float lbl_803EAFE4;

extern "C" int fn_8009EFDC(int index);

/* View of the block at player +336 used by fn_80117AA4. */
struct State_80117AA4 {
    char mUnknown0[17];
    unsigned char mUnknown17;
    char mUnknown18[2];
    Object_80039F5C *mpUnknown20;
};

extern "C" {
Object_80039F5C *fn_8009EDD4(unsigned int index, int side, Point_8017886C *pOut);
}

extern "C" {
extern unsigned char lbl_803EB010;
}

extern "C" {
extern float lbl_803EAFD0;
}

extern "C" {
extern float lbl_803EAFD4;
}

extern "C" {
extern float lbl_803EAFD8;
}

extern "C" {
extern float lbl_803EAFDC;
}

extern "C" {
extern unsigned short lbl_803EAFE0;
}

struct Record_8011F4E0;

/* View of the block at player +336 used by fn_801180FC. */
struct Block_801180FC {
    char mUnknown0[8];
    int mUnknown8;
    float mUnknown12;
};

/* View of the block at player +336 used by fn_80118210. */
struct Block_80118210 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned char mUnknown16;
    char mUnknown17[1];
    short mUnknown18;
    int mUnknown20;
    unsigned char mUnknown24;
    char mUnknown25[1];
    unsigned char mUnknown26;
};

extern "C" {
extern signed char lbl_803EB008;
}

extern "C" {
extern float lbl_803EB00C;
}

extern "C" {
extern float lbl_803EB004;
}

/* View of the block at player +1032 used by fn_80118B4C. */
struct Block_80118B4C {
    int mUnknown0;
    char mUnknown4[16];
    int mUnknown20;
    char mUnknown24[28];
    float mUnknown52;
};

/* View of the block at player +1032 used by fn_80119020. */
struct Block_80119020 {
    int mUnknown0;
    char mUnknown4[16];
    int mUnknown20;
    char mUnknown24[71];
    unsigned char mUnknown95;
    char mUnknown96[5];
    unsigned char mUnknown101;
    short mUnknown102;
    unsigned char mUnknown104;
    unsigned char mUnknown105;
};

/* View of the block at player +1032 used by fn_801194F0. */
struct Block_801194F0 {
    int mUnknown0;
    char mUnknown4[16];
    int mUnknown20;
    char mUnknown24[16];
    float mUnknown40;
    char mUnknown44[8];
    float mUnknown52;
    char mUnknown56[39];
    unsigned char mUnknown95;
};

extern "C" {
int fn_800A7F08(int team);
}

extern "C" {
int CharSkelGetJointByName(void *p, const char *name);
}

extern "C" void fn_80227930(void *pOut, void *pA, void *pB, float t);

extern "C" {
extern const char lbl_8029DB78[];
}

extern "C" {
int fn_800CE4A8(Query_800CE770 *p);
}

extern "C" {
int fn_800C8BAC(Object_80039F5C *p, int which);
}

extern "C" {
extern float lbl_803EB020;
}

extern "C" {
extern int lbl_802DAC38[];
}

extern "C" {
int fn_800A851C(int team, Object_80039F5C *p);
}

extern "C" {
int fn_800A8444(int team);
}

extern "C" {
extern int lbl_802DAC20[];
}

/* View of the block at player +1072 as fn_80119DB4 and fn_8011A2C4 use it:
   four values at +24..+36 (handed to fn_800ABF00) and three multipliers at
   +40..+48. */
struct Block_80119DB4 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    int mUnknown16;
    int mUnknown20;
    float mUnknown24;
    float mUnknown28;
    float mUnknown32;
    float mUnknown36;
    float mUnknown40;
    float mUnknown44;
    float mUnknown48;
    char mUnknown52[3];
    unsigned char mUnknown55;
    unsigned char mUnknown56;
};

extern "C" {
extern float lbl_803EB02C;
}

extern "C" {
extern float lbl_803EB030;
}

extern "C" {
extern float lbl_803EB034;
}

extern "C" {
extern float lbl_803EB038;
}

extern "C" {
extern float lbl_803EB03C;
}

extern "C" {
extern float lbl_803EB040;
}

extern "C" {
extern float lbl_803EB044;
}

extern "C" {
extern float lbl_803EB048;
}

extern "C" {
extern float lbl_803EB04C;
}

extern "C" {
extern float lbl_803EB050;
}

extern "C" {
extern float lbl_803EB054;
}

extern "C" {
extern float lbl_803EB058;
}

extern "C" {
extern float lbl_803EB05C;
}

extern "C" {
extern float lbl_803EB060;
}

extern "C" {
extern float lbl_803EB064;
}

extern "C" {
extern float lbl_803EB068;
}

extern "C" {
extern float lbl_803EB06C;
}

extern "C" {
extern float lbl_803EB070;
}

extern "C" {
extern float lbl_803EB074;
}

extern "C" {
extern float lbl_803EB078;
}

extern "C" {
extern float lbl_803EB07C;
}

extern "C" {
extern float lbl_803EB088;
}

extern "C" {
float fn_800AC004(int team, float value);
}

extern "C" {
float fn_800AD204(int team, int value);
}

extern "C" {
Object_80039F5C *BallGetCurrentHolder(void);
}

extern "C" {
void fn_800ABF00(int team, Block_80119DB4 *p);
}

extern "C" {
int fn_800CA5CC(Object_80039F5C *p, int kind, int value);
}

extern "C" {
extern float lbl_803EB080;
}

extern "C" {
extern float lbl_803EB084;
}

extern "C" {
extern float lbl_803EB08C;
}

extern "C" {
extern float lbl_803EB090;
}

extern "C" {
extern Move_8011AB38 *lbl_802DAF8C[2][3][5];
}

extern "C" {
int fn_800CD2B4(int mode, Object_80039F5C *p);
}

extern "C" {
int LooseBallIsIdle(Object_80039F5C *p);
}

/* View of the block at player +1072 used by fn_8011A608 and fn_8011A7B4. */
struct Block_8011A608 {
    float mUnknown0;
    char mUnknown4[4];
    float mUnknown8;
    char mUnknown12[4];
    int mUnknown16;
    char mUnknown20[8];
    float mUnknown28;
    char mUnknown32[23];
    unsigned char mUnknown55;
};

extern "C" {
int fn_800CE590(Query_800CE770 *pQuery, Record_800CE608 *pA, Record_800CE608 *pB);
}

extern "C" {
void fn_800CE608(Object_80039F5C *p, Record_800CE608 *pRecord);
}

extern "C" {
void AudmonEventPostArgs(int type, Vector_80039F5C *pPos, int a, int b, int c);
}

/* View of the 108 bytes at player +1032 as fn_8011AB38 uses them. */
struct Block_8011AB38 {
    int mUnknown0;
    int mUnknown4;
    char mUnknown8[16];
    Record_800CE608 mUnknown24;
    float mUnknown40;
    char mUnknown44[12];
    int mUnknown56;
    int mUnknown60;
    char mUnknown64[30];
    unsigned char mUnknown94;
};

static inline void SetMove_8011AB38(Object_80039F5C *p, Block_8011AB38 *pState)
{
    p->mUnknown512.mUnknown14 = 5;
    p->mUnknown512.mUnknown4 = pState->mUnknown56;
    p->mUnknown512.mUnknown8 = pState->mUnknown60;
    p->mUnknown512.mUnknown0 = pState->mUnknown40;
}

struct Entry_8011AFCC_8011B2A4 {
    int mUnknown0;
    char mUnknown4[56];
    Object_80039F5C *mpUnknown60;
    int mUnknown64;
    float mUnknown68;
    float mUnknown72;
    unsigned char mUnknown76;
    char mUnknown77[3];
};

struct Entry_8011AFCC_8011B4F8 {
    int mUnknown0;
    char mUnknown4[56];
    Object_80039F5C *mpUnknown60;
    int mUnknown64;
    float mUnknown68;
    float mUnknown72;
    unsigned char mUnknown76;
    char mUnknown77[3];
};

extern "C" {
int fn_800ACFFC(int team, int value);
}

struct Score_8011D0BC {
    float mValue;
    unsigned char mValid;
};

/* 80-byte entry of the two lists fn_8011D9B8 builds; terminated by a null
   player. +4 caches one score per opposing player index, with its valid byte. */
struct Entry_8011AFCC_8011BCDC {
    Entry_8011AFCC_8011BCDC *mpUnknown0;
    Score_8011D0BC mUnknown4[7];
    Object_80039F5C *mpUnknown60;
    int mUnknown64;
    float mUnknown68;
    float mUnknown72;
    unsigned char mUnknown76;
    char mUnknown77[3];
};

extern "C" {
extern float lbl_803EB014;
}

extern "C" {
extern float lbl_803EB018;
}

extern "C" {
extern float lbl_803EB01C;
}

extern "C" {
extern float lbl_803EB094;
}

extern "C" {
Object_80039F5C *PlyrFindByRole(int team, int a, unsigned char n);
}

extern "C" void fn_80227638(void *pOut, void *pA, void *pB);

extern "C" {
extern unsigned char lbl_803EB024;
}

extern "C" {
void fn_800A5A68(void *p);
}

extern "C" {
unsigned char BallsGetCount(void);
}

extern "C" {
extern int lbl_802DB03C[];
}

extern "C" {
int fn_801CFDD0(float value);
}

struct State_80125304 {
    Object_80039F5C *mpUnknown0;
    unsigned short mUnknown4;
};

struct State_80125594 {
    int mUnknown0;
    float mUnknown4;
    unsigned char mUnknown8;
};

extern "C" {
void fn_800B6D34(Object_80039F5C *p, Input_800B6D34 *pInput);
}

extern "C" float fn_8022781C(void *pA, void *pB);

extern "C" {
float fn_80260B1C(float x);
}

extern "C" {
int MathRLerp(int a, int b, float factor);
}

extern "C" {
extern float lbl_803EC9E8;
}

extern "C" {
typedef void (*Score_8012430C)(Directions_8012430C *, Object_80039F5C *, Object_80039F5C *);
}


extern "C" {
int fn_800E1584(Object_80039F5C *p);
}

extern "C" {
int fn_801783AC(int a);
}

extern "C" {
extern float lbl_803EB0A0, lbl_803EB0A4, lbl_803EB0A8, lbl_803EB0AC;
}


extern "C" {
float fn_80237260(int a);
}

extern "C" {
unsigned int fn_802372EC(int a, int b);
}

extern "C" {
int PursueGetTackleChance(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C target, unsigned int *pOut, float distance);
}

extern "C" int fn_80178D70(int team);
extern "C" void PlayerCutGetEndPoint(Object_80039F5C *p, Point_8017886C *pOut);
extern "C" Object_80039F5C *PlyrFindNearest(Vector_80039F5C *pPos, float *pOut, int team);
extern "C" int fn_800A7F1C(int team);
extern "C" const float lbl_803ED6CC;
extern "C" int fn_8009F0B8(Object_80039F5C *p, int angle);
extern "C" int fn_800CBB00(Object_80039F5C *p, int index, Point_8017886C target, int angle, int beyond);
extern "C" int BallStateGet(Ball_t *p, int *pArg);
extern "C" int fn_80099734(Object_80039F5C *p, Ball_t *pBall, int a, int mode, float range, void *pBlock, int b, int c, int d, int e);
extern "C" void fn_8009F928(Object_80039F5C *p, Point_8017886C *pOut, unsigned int distance, int predict);
extern "C" int fn_8009FD7C(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" void fn_8009E9EC(Object_80039F5C *p, int index, Point_8017886C *pOut);

/* Forward declarations of the functions this file defines, in address order. */
extern "C" void fn_800EFC68(int a, State_80039F5C *pQueue);
extern "C" void fn_800EFCD0(int a, State_80039F5C *pQueue, Object_80039F5C *p);
extern "C" void fn_800F00D4(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p);
extern "C" void fn_800F0490(int a, State_80039F5C *pQueue, int id);
extern "C" void fn_800F053C(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p);
extern "C" void fn_800F05E4(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p);
extern "C" void fn_800F0960(Object_80039F5C *p, Block_800F0C6C *pBlock);
extern "C" int fn_800F0B84(Object_80039F5C *p);
extern "C" int fn_800F0FA0(Input_800B6D34 *pBlock, unsigned int *pMasks, int index);
extern "C" void fn_800F0FD0(Input_800B6D34 *pBlock, int index);
extern "C" int fn_800F1FDC(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int fn_800F21E0(Object_80039F5C *p, Object_80039F5C *pOther, float distance);
extern "C" int fn_800F2920(Object_80039F5C *p);
extern "C" int fn_800F2A40(Object_80039F5C *p);
extern "C" int fn_800F2C1C(Object_80039F5C *p, int a);
extern "C" void fn_800F3A6C(Object_80039F5C *pA, Object_80039F5C *pB, Info_800F3A6C *pInfo, Points_800F3A6C *pPoints);
extern "C" int fn_800F4E14(Object_80039F5C *p, Object_800F4E14 *pInfo);
extern "C" int fn_800F4E88(Object_80039F5C *p, Record_800F4E88 *pRecord);
extern "C" void fn_800F4F08(Object_80039F5C *p, Record_800F4E88 *pRecord);
extern "C" int fn_800F5208(Object_80039F5C *p, Record_800F4E88 *pRecord);
extern "C" int fn_800F5AD4(Object_80039F5C *p);
extern "C" int fn_800F5CBC(Object_80039F5C *p, Record_800F4E88 *pRecord);
extern "C" void fn_800F60BC(Object_80039F5C *p);
extern "C" unsigned int fn_800F67E8(Object_80039F5C *pTarget);
extern "C" int fn_800F6878(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int fn_800F69C0(int angle, Object_80039F5C *p);
extern "C" void fn_800F6AD8(float *p);
extern "C" void fn_800F6B2C(Object_80039F5C *p, Vector_80039F5C *pDelta);
extern "C" void fn_800F6C90(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut);
extern "C" void fn_800F6D40(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut);
extern "C" void fn_800F6E30(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut);
extern "C" void fn_800F70D0(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut);
extern "C" void fn_800F722C(Object_80039F5C *p, Object_80039F5C *pOther, float *pX, float *pOut);
extern "C" void fn_800F7314(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut);
extern "C" void fn_800F7798(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut);
extern "C" void fn_800F7B64(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut);
extern "C" void fn_800F7F68(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut);
extern "C" void fn_800F8588(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" void fn_800F8A88(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int fn_800F8D24(Object_80039F5C *p);
extern "C" int fn_800F8D2C(Object_80039F5C *p);
extern "C" int fn_800F9024(Object_80039F5C *p);
extern "C" int fn_800F930C(Object_80039F5C *p);
extern "C" Object_80039F5C *fn_800F9480(Object_80039F5C *p);
extern "C" Object_80039F5C *fn_800F9688(Object_80039F5C *p);
extern "C" Point_8017886C AssignGetFormationPos(Object_80039F5C *p);
extern "C" int fn_800F9CB4(void);
extern "C" Object_80039F5C *fn_800F9E3C(Object_80039F5C *p, int flag);
extern "C" void fn_800FA014(Object_80039F5C *p, int *pRef);
extern "C" int fn_800FA098();
extern "C" Object_80039F5C *fn_800FB844(Object_80039F5C *p);
extern "C" Object_80039F5C *fn_800FB9D4(Object_80039F5C *p);
extern "C" void fn_800FBB70(void);
extern "C" Object_80039F5C *fn_800FBF74(Object_80039F5C *pTarget, Object_80039F5C *pOther);
extern "C" unsigned char fn_800FC014(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" unsigned char fn_800FC0C4(Object_80039F5C *p);
extern "C" unsigned char fn_800FC128(Object_80039F5C *p);
extern "C" unsigned char fn_800FC1DC(Object_80039F5C *p);
extern "C" void fn_800FC290(Object_80039F5C *p, Block_800FCC24 *pBlock, Point_8017886C target);
extern "C" int fn_800FC4A8(Object_80039F5C *p, Block_800FCC24 *pBlock, int mode);
extern "C" int fn_800FC648(Object_80039F5C *p, Block_800FCC24 *pBlock);
extern "C" int fn_800FC7A0(Object_80039F5C *p, Block_800FCC24 *pBlock);
extern "C" int fn_800FCE58(Object_80039F5C *p, Block_800FCC24 *pBlock);
extern "C" int fn_800FCFC0(Object_80039F5C *p);
extern "C" void fn_800FD178(Object_80039F5C *p, Block_800FD650 *pBlock);
extern "C" int fn_800FD2AC(Object_80039F5C *p);
extern "C" int fn_800FD580(Object_80039F5C *p);
extern "C" void fn_800FD724(Object_80039F5C *p);
extern "C" int fn_800FD7D0(Object_80039F5C *p);
extern "C" int fn_800FD828(Object_80039F5C *p);
extern "C" void fn_800FD978(Object_80039F5C *p);
extern "C" void fn_800FE03C(Object_80039F5C *p, Point_8017886C *pOut);
extern "C" void fn_800FE41C(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pOut);
extern "C" void fn_800FE430(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pOut);
extern "C" int fn_800FF094(Object_80039F5C *p);
extern "C" void fn_800FF598(State_800FDA58 *s, Object_80039F5C *p, Point_8017886C *point, int angle, float value);
extern "C" void fn_800FF6D8(Object_80039F5C *p);
extern "C" void fn_800FF868(Object_80039F5C *p,State_800FFDFC *,Object_80039F5C *other);
extern "C" void fn_800FF8FC(Object_80039F5C *p, float *out);
extern "C" int fn_800FFA10(Object_80039F5C *p, Object_80039F5C *other);
extern "C" void fn_800FFB4C(Object_80039F5C *p, Object_80039F5C *other, float *value, Point_8017886C *out);
extern "C" void fn_800FFD2C(Object_80039F5C *p, Point_8017886C *point);
extern "C" int fn_800FFFB0(Object_80039F5C *p);
extern "C" int fn_80100024(Object_80039F5C *p, int angle, int mode);
extern "C" void fn_8010016C(Object_80039F5C *p, Point_8017886C *point, Object_80039F5C *other, float speed);
extern "C" int fn_80100370(Ball_t *ball, Object_80039F5C *p, float value, Vector_80039F5C *out);
extern "C" void fn_80100AA0(Object_80039F5C *p,int,float *a,float *b);
extern "C" unsigned int fn_80100B0C(void);
extern "C" void fn_80100BF8(Object_80039F5C *p, float, Vector_80039F5C *point, Point_8017886C *offset, float factor, float skill);
extern "C" Object_80039F5C *fn_80100EA0(Object_80039F5C *p, int angle);
extern "C" void fn_80101064(Object_80039F5C *p);
extern "C" void fn_80101130(Object_80039F5C *p, Object_80039F5C *other, unsigned short *out);
extern "C" void fn_801016A4(Object_80039F5C *p, unsigned char *kind, Point_8017886C *point, int *angle);
extern "C" void fn_8010176C(Object_80039F5C *p, int mode, Point_8017886C *point);
extern "C" int fn_801018B4(Object_80039F5C *p, List_801018B4 *pList, int a, int b, int *pOut);
extern "C" void fn_80101AE0(Object_80039F5C *p, float *pOut);
extern "C" int fn_80101B7C(Object_80039F5C *p);
extern "C" int fn_80101C40(Object_80039F5C *p);
extern "C" void fn_80102D78(Object_80039F5C *p);
extern "C" void fn_801039D8(Object_80039F5C *p);
extern "C" int fn_80103CB0(Object_80039F5C *p);
extern "C" float AssignGetPassSpeed(Object_80039F5C *p, Object_80039F5C *pOther, float scale, short *pCount);
extern "C" void fn_80103F80(Ball_t *pBall, Vector_80039F5C pos, Vector_80039F5C velocity, float speed, int angle, float ballSpeed, Vector_80039F5C *pOut, Object_80039F5C *p);
extern "C" void fn_80104328(Object_80039F5C *p, unsigned int count, int *pTime, Vector_80039F5C *pPos, int *pAngle);
extern "C" int fn_80104610(Object_80039F5C *p);
extern "C" int fn_80104720(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int fn_801047C8(void);
extern "C" void fn_80104814(Object_80039F5C *p, Object_80039F5C *pOther, Ball_t *pBall, Vector_80039F5C *pTarget);
extern "C" void fn_801048B4(Object_80039F5C *p, Ball_t *pBall, Vector_80039F5C *pTarget);
extern "C" void fn_80104944(Object_80039F5C *p, Vector_80039F5C *pOut);
extern "C" void fn_80104A08(Object_80039F5C *p, float scale, int angle, Point_8017886C *pPoint, float *pValue);
extern "C" void fn_80104B24(Vector_80039F5C *p);
extern "C" void fn_80104B3C(Object_80039F5C *p, Vector_80039F5C *pOut);
extern "C" void fn_80104C3C(Object_80039F5C *p, Vector_80039F5C *pOut, float scale);
extern "C" void fn_80104D98(Object_80039F5C *p);
extern "C" void fn_80105168(int mode, Ball_t *pBall, Object_80039F5C *p, Object_80039F5C *pOther, float speed, Vector_80039F5C *pTarget, int unused);
extern "C" Object_80039F5C *fn_80105384(Object_80039F5C *p, int aggressive, Point_8017886C *pOut);
extern "C" int fn_80105E90(Object_80039F5C *p, Object_80039F5C *pTarget, int kind);
extern "C" void fn_801061E8(Object_80039F5C *p, Ball_t *pBall);
extern "C" int fn_80106618(Object_80039F5C *p);
extern "C" void fn_80106678(Record_8011F518 *pRecord, Object_80039F5C *p, int a, int b);
extern "C" void fn_80106A60(Object_80039F5C *p);
extern "C" void fn_80106C24(Object_80039F5C *p, Block_800F4A74_80104C9C *pBlock);
extern "C" void fn_801074B4(Object_80039F5C *p, Points_800F3A6C *pInfo);
extern "C" void fn_80107680(Points_800F3A6C *pInfo, int index);
extern "C" void fn_801076F0(Object_80039F5C *pA, Object_80039F5C *pB, Result_801076F0 *pOut, Input_801076F0 *pIn);
extern "C" void fn_801077D8(Object_80039F5C *p, Object_80039F5C *pOther, Block_800F4A74_801077D8 *pBlock, Info_800F3A6C *pInfo, Points_800F3A6C *pPoints);
extern "C" void fn_801079BC(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB, Points_800F3A6C *pInfo);
extern "C" void fn_80107A9C(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB, Info_800F3A6C *pResult, Points_800F3A6C *pInfo, float *pScale);
extern "C" void fn_80107D48(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB, Info_800F3A6C *pResult, Points_800F3A6C *pInfo, float *pScale);
extern "C" void fn_80108074(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB, Input_801076F0 *pIn);
extern "C" void fn_8010810C(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB, Points_800F3A6C *pInfo, Info_800F3A6C *pResult, float scale);
extern "C" void fn_80108954(Object_80039F5C *p, Object_80039F5C *pOther, Result_801076F0 *pInfo);
extern "C" void fn_80108A94(Object_80039F5C *p, Points_800F3A6C *pInfo);
extern "C" void fn_80108DF8(Object_80039F5C *p, Points_800F3A6C *pInfo, int quick);
extern "C" void fn_801096D4(Object_80039F5C *p);
extern "C" void fn_80109990(Pair_80109990 *pOut);
extern "C" int fn_80109A1C(Object_80039F5C *p, Point_8017886C *pOut);
extern "C" void fn_80109CA0(Object_80039F5C *p, int animation, unsigned char a, unsigned char b, unsigned char c);
extern "C" int fn_80109D70(Object_80039F5C *p, Point_8017886C *pOut);
extern "C" int fn_80109E48(Object_80039F5C *p, int kind, int *pOut);
extern "C" int fn_80109F34(Object_80039F5C *p);
extern "C" int fn_8010A07C(Object_80039F5C *p);
extern "C" int fn_8010A0A0(Object_80039F5C *p, int index);
extern "C" int fn_8010A2DC(Object_80039F5C *p, int a, short b);
extern "C" void fn_8010AECC(Object_80039F5C *p, unsigned char a, unsigned char b, unsigned char c);
extern "C" void fn_8010B1FC(Object_80039F5C *p, int a, short b);
extern "C" int fn_8010B224(Object_80039F5C *p);
extern "C" unsigned char fn_8010B738(Object_80039F5C *p, Table_8010B738 *pTable);
extern "C" unsigned char fn_8010B87C(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int fn_8010BD58(Object_80039F5C *p);
extern "C" void fn_8010BE54(Object_80039F5C *p);
extern "C" int fn_8010CE90(Object_80039F5C *p, Ball_t *pBall);
extern "C" void fn_8010CEB8(Object_80039F5C *p, int kind);
extern "C" void fn_8010CFD4(Object_80039F5C *p);
extern "C" void fn_8010D434(Object_80039F5C *p, State_8010D80C_8010D434 *pState);
extern "C" void fn_8010D508(Object_80039F5C *p);
extern "C" void fn_8010D80C(Object_80039F5C *p, Vector_80039F5C *pOut);
extern "C" float fn_8010D82C(Object_80039F5C *p);
extern "C" int fn_8010D8F4(Object_80039F5C *p);
extern "C" Object_80039F5C *fn_8010DA38(Object_80039F5C *p, Object_80039F5C *pExclude);
extern "C" void fn_8010DAB4(Object_80039F5C *p, Steer_8010DAB4 *pOut);
extern "C" void fn_8010E15C(Object_80039F5C *p, Steer_8010DAB4 *pOut);
extern "C" void fn_8010E59C(Object_80039F5C *p, Object_80039F5C *pTarget, Steer_8010DAB4 *pOut);
extern "C" void fn_8010EF40(Object_80039F5C *p);
extern "C" void fn_8010F058(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" void fn_8010F1F4(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int fn_8010FD94(Object_80039F5C *p);
extern "C" int fn_801101DC(Object_80039F5C *p);
extern "C" int fn_801102A4(Object_80039F5C *p);
extern "C" int fn_801105B0(Object_80039F5C *p);
extern "C" unsigned short fn_8011067C(Table_8010B738 *pTable, Object_80039F5C *p, Block_8011067C *pBlock, int angle);
extern "C" int fn_8011165C(Object_80039F5C *p);
extern "C" void CatchGetHandReach(Object_80039F5C *p, int angle, float length, Vector_80039F5C *pOut);
extern "C" int fn_80112C04(Object_80039F5C *p, Ball_t *pBall, int *pAngle, float *pValue);
extern "C" int fn_80113088(Object_80039F5C *p);
extern "C" int fn_80113498(Object_80039F5C *p);
extern "C" int fn_80113604(Object_80039F5C *p);
extern "C" int fn_80113BCC(Object_80039F5C *p);
extern "C" int fn_80113C18(Object_80039F5C *p, void *pState);
extern "C" int fn_80114D14(int a, unsigned char b, int c, unsigned char d);
extern "C" Object_80039F5C *fn_80114E7C(Object_80039F5C *p);
extern "C" void fn_80114F64(Object_80039F5C *p, int angle);
extern "C" void fn_8011569C(Object_80039F5C *p);
extern "C" int fn_801163B4(Object_80039F5C *p);
extern "C" int fn_80116410(Object_80039F5C *p, Object_80039F5C *pOther, State_8011569C *pState, Point_8017886C *pTarget);
extern "C" int fn_801167C4(void *pTarget, Object_80039F5C *p);
extern "C" void fn_80116880(Object_80039F5C *p, Object_80039F5C *pOther, float *pValue, float *pOut, float range);
extern "C" int fn_80116984(Object_80039F5C *p, Object_80039F5C *pOther, float *pOut);
extern "C" int fn_80116AB8(Object_80039F5C *p);
extern "C" int fn_801170E8(Object_80039F5C *p);
extern "C" int fn_80117494(Object_80039F5C *p, Point_8017886C *out);
extern "C" Object_80039F5C *fn_80117794(int index);
extern "C" Object_80039F5C *fn_80117934(void);
extern "C" void fn_80117AA4(Object_80039F5C *p, Point_8017886C *pOut, float *pSpeed);
extern "C" void fn_801180FC(Object_80039F5C *p);
extern "C" void fn_801187CC(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" void fn_80118894(Record_80118894 *pA, Record_80118894 *pB, int a, int b, Object_80039F5C *pPlayerA, Object_80039F5C *pPlayerB);
extern "C" int fn_80118B4C(Object_80039F5C *p, Pair_8011BAE0 *pPair);
extern "C" void fn_80119020(void);
extern "C" void fn_801194F0(void);
extern "C" void fn_80119B98(void);
extern "C" void fn_8011A2C4(Object_80039F5C *p, Object_80039F5C *pOther, Pair_8011BAE0 spot, int apply);
extern "C" int fn_8011A608(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" Move_8011AB38 *fn_8011A7B4(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int fn_8011A994(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" void fn_8011AB38(void);
extern "C" void fn_8011AFCC(Entry_8011AFCC *pEntries);
extern "C" void fn_8011B138(Entry_8011AFCC *pEntries);
extern "C" int fn_8011B2A4(Entry_8011AFCC_8011B2A4 *pEntry);
extern "C" void fn_8011B6E8(Entry_8011AFCC_8011B4F8 *pEntries, Pair_8011BAE0 target);
extern "C" void fn_8011B83C(Entry_8011AFCC_8011B4F8 *pEntries, Pair_8011BAE0 target);
extern "C" void fn_8011BAE0(Pair_8011BAE0 *pOut);
extern "C" void fn_8011D0BC(Entry_8011AFCC_8011BCDC *pA, Entry_8011AFCC_8011BCDC *pB, Pair_8011BAE0 pair);
extern "C" int fn_8011D558(Vector_80039F5C *p, Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC);
extern "C" void fn_8011D654(Entry_8011AFCC *pEntries);
extern "C" void fn_8011D8B4(Entry_8011AFCC *pEntries);
extern "C" void fn_8011D9B8(void);
extern "C" void fn_8011DBC0(Object_80039F5C *p);
extern "C" void fn_8011DBC4(Object_80039F5C *p);
extern "C" void fn_8011DBC8(Object_80039F5C *p, Block_8011DBC8 *pBlock);
extern "C" int fn_8011DBE0(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int fn_8011DC68(unsigned int id);
extern "C" int fn_8011DCA8(unsigned int id);
extern "C" void fn_8011DCDC(void);
extern "C" unsigned int fn_8011E188(void);
extern "C" void fn_8011E194(Object_80039F5C *p, unsigned char mask);
extern "C" void fn_8011E1A8(Object_80039F5C *p, unsigned char mask);
extern "C" void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value);
extern "C" void fn_8011E240(Object_80039F5C *p);
extern "C" void fn_8011E33C(Object_80039F5C *p, Object_80039F5C *pOther, int value);
extern "C" void fn_8011E3A4(Object_80039F5C *p);
extern "C" void fn_8011E3EC(Object_80039F5C *p, int a);
extern "C" int fn_8011E3F4(Object_80039F5C *p);
extern "C" int fn_8011E484(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" int fn_8011E8A4(Object_80039F5C *p);
extern "C" void fn_8011E8D8(Object_80039F5C *p);
extern "C" void fn_8011E938(Object_80039F5C *p);
extern "C" int fn_8011E95C(void);
extern "C" int fn_8011E9B4(Object_80039F5C *p);
extern "C" int fn_8011E9D8(State_80039F5C *pState);
extern "C" int fn_8011EAC0(Object_80039F5C *p, Object_80039F5C *pOther);
extern "C" unsigned char fn_8011EE18(Object_80039F5C *p, Object_80039F5C *pCarrier);
extern "C" int fn_8011EFD4(void *p, void *q);
extern "C" int fn_8011F1A4(void);
extern "C" int fn_8011F1CC(void);
extern "C" int fn_8011F228(void);
extern "C" int fn_8011F25C(void);
extern "C" int fn_8011F290(void);
extern "C" int fn_8011F2F8(void);
extern "C" int fn_8011F32C(void);
extern "C" unsigned char fn_8011F4C8(void);
extern "C" float fn_8011F4D4(void);
extern "C" Record_8011F4E0 *fn_8011F4E0(void);
extern "C" void *fn_8011F4EC(void);
extern "C" int fn_8011F524(void);
extern "C" Object_80039F5C *fn_8011F54C(void);
extern "C" void fn_8011F5AC(int index);
extern "C" int fn_8011FA78(void *pA, void *pB);
extern "C" int fn_8011FAFC(void *pA, void *pB);
extern "C" int fn_8011FB80(void *pA, void *pB);
extern "C" void fn_8011FCA4(void);
extern "C" int fn_8011FD64(unsigned short index);
extern "C" void fn_8011FE0C(void);
extern "C" void fn_80120384(void);
extern "C" int fn_80120794(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pDir, float speed, float dist, int, float range);
extern "C" int PursuitGetInterceptAngle(Vector_80039F5C *pA, Vector_80039F5C *pB, float speed, Vector_80039F5C *pDir);
extern "C" int fn_80120A50(Point_8017886C *p, Point_8017886C *pA, Point_8017886C *pB, Point_8017886C *pC);
extern "C" void fn_80120B4C(int value, int *pList, unsigned char i, unsigned char count);
extern "C" void fn_80120CDC(Object_80039F5C *p, Object_80039F5C *pOther, Entry_80120E98 *pEntry);
extern "C" void fn_80120D98(Object_80039F5C *p, Point_8017886C *pMin, Point_8017886C *pMax);
extern "C" void fn_80120EF8(Plan_80121264 *pPlan, Vector_80039F5C *pPos);
extern "C" void fn_80121264(Object_80039F5C *p, Plan_80121264 *pPlan);
extern "C" int fn_801218EC(Point_8017886C *pPos, Entry_80120E98 *pA, Entry_80120E98 *pB);
extern "C" int fn_80121918(Object_80039F5C *p, Plan_80121264 *pPlan, Entry_801230B8 *pEntry);
extern "C" int fn_80121BE8(Point_8017886C *pA, Point_8017886C *pB, Point_8017886C *pTarget, int angle, int heading, float distB, float distA);
extern "C" void fn_80121CB0(Object_80039F5C *p, Entry_801230B8 *pEntry, int angle);
extern "C" void fn_80122670(Object_80039F5C *p, Plan_80121264 *pPlan, int angle);
extern "C" void fn_801227DC(Object_80039F5C *p, Plan_80121264 *pPlan, Entry_801230B8 *pEntry);
extern "C" Entry_801230B8 *fn_801230B8(Plan_80121264 *pPlan);
extern "C" Entry_801230B8 *fn_80123174(Plan_80121264 *pPlan);
extern "C" int fn_80123254(void *pA, void *pB);
extern "C" void fn_8012327C(Directions_8012430C *pValues, Object_80039F5C *p);
extern "C" void fn_80123594(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *);
extern "C" void fn_8012368C(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *);
extern "C" void fn_801237F4(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *);
extern "C" void fn_80123C2C(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *pExclude);
extern "C" void fn_80123E2C(Directions_8012430C *, Object_80039F5C *, Object_80039F5C *);
extern "C" void fn_80123E30(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *);
extern "C" void fn_80123F48(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *);
extern "C" float fn_801242E0(Directions_8012430C *pValues, unsigned int index);
extern "C" void fn_8012430C(Directions_8012430C *pOut, int kind, Object_80039F5C *p);
extern "C" void fn_80124374(Directions_8012430C *pOut, int kind, Object_80039F5C *p, Object_80039F5C *a);
extern "C" unsigned char fn_801243E0(Directions_8012430C *pValues, int angle);
extern "C" Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, unsigned char a, unsigned char count, float *pOut, int b);
extern "C" Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, unsigned char a, unsigned char count, int angle, float *pOut, int b);
extern "C" int fn_80124714(Object_80039F5C *p, Object_80039F5C *pOther, Object_80039F5C **pOut);
extern "C" int fn_80124B1C(Object_80039F5C *p, Object_80039F5C *pOther, int angle, float length, float width);
extern "C" Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, float length, float width, int facing);
extern "C" Object_80039F5C *fn_80124CE4(Object_80039F5C *p, int team, float *pOut, int angle, float length, int facing, float width);
extern "C" Object_80039F5C *fn_80124E5C(Object_80039F5C *p, int team, float *pOut, int angle, float length, int facing, float width);
extern "C" float fn_80125004(Object_80039F5C *p, int kind, int index);
extern "C" float fn_8012506C(Object_80039F5C *p, int kind);
extern "C" float fn_801250B8(Object_80039F5C *p, Object_80039F5C *a, int kind);
extern "C" int fn_8012510C(Directions_8012430C *pValues);
extern "C" int fn_80125214(Object_80039F5C *p, Object_80039F5C *pTarget);
extern "C" int fn_80125304(Object_80039F5C *p);
extern "C" int fn_801253A8(Object_80039F5C *p);
extern "C" int fn_80125494(Object_80039F5C *p);
extern "C" int fn_801254C8(Object_80039F5C *p);
extern "C" int fn_80125510(Object_80039F5C *p, Message_800F01CC *pIn);
extern "C" void fn_80125594(Object_80039F5C *p, State_80125594 *pState);
extern "C" void fn_80125708(Object_80039F5C *p, State_80125594 *pState);
extern "C" void fn_80125B74(Object_80039F5C *p, State_80125594 *pState);
extern "C" int fn_80125C28(Object_80039F5C *p, State_80125594 *);
extern "C" int fn_80125D98(Object_80039F5C *p, State_80125594 *pState);
extern "C" int fn_80125DF0(Object_80039F5C *p);
extern "C" int fn_80125E20(Object_80039F5C *p);

extern "C" void fn_800EFC68(int a, State_80039F5C *pQueue) {
    Message_800F01CC *pEntries = (Message_800F01CC *)pQueue;

    memmove(pEntries, pEntries + 1, (lbl_803EAE14[a]->mCount - 1) * 4);
    pEntries[lbl_803EAE14[a]->mCount - 1].mId = 0;
}

/* The unit's own data, in target order. Neutral lbl_ names: no evidence names these objects yet. */
extern "C" {
char lbl_802DAAC4[] = "ASSIGN.C";
Input_800B6D34 lbl_802DAAD0 = {0};
}

static int (*lbl_802DAB38[4])(Object_80039F5C *p) = {
    fn_800F8D24, fn_800F8D2C, fn_800F9024, fn_800F930C,
};

extern "C" {
unsigned int lbl_802DAB48[3] = {0x14, 0x15, 0x16};
unsigned int lbl_802DAB54[3] = {0x17, 0x18, 0x19};
unsigned char lbl_802DAB60[20] = {4, 3, 2, 4, 4, 3, 0, 2, 1, 1, 2, 1, 2, 4, 1, 1, 1};
float lbl_802DAB74[18] = {1.0f, 0.5f, 0.5f, 0.75f, 0.9f, 0.5f, 0.0f, 0.5f, 0.8f, 0.9f, 0.75f, 1.0f, 0.25f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};
unsigned char lbl_802DABBC[100] = {0};
int lbl_802DAC20[6] = {0x92, 0x93, 0x97, 0x95, 0x96, 0x94};
int lbl_802DAC38[3] = {0xB6, 0xB7, 0xB8};
Move_8011AB38 lbl_802DAC44[] = {{0x31, 0.5f, 0x11C71C}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAC5C[] = {{0x31, 0.4f, 0x11C71C}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAC74[] = {{0x32, 0.4f, 0x11C71C}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAC8C[] = {{0x31, 0.4f, 0x11C71C}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DACA4[] = {{0x33, 0.4f, 0x11C71C}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DACBC[] = {{0x33, 0.4f, 0x11C71C}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DACD4[] = {{0x3C, 0.4f, 0x11C71C}, {0x31, 0.4f, 0x11C71C}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DACF8[] = {{0x3B, 0.4f, 0x11C71C}, {0x31, 0.4f, 0x11C71C}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAD1C[] = {{0x34, 0.5f, 0x18E38E}, {0x31, 0.4f, 0x18E38E}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAD40[] = {{0x34, 0.5f, 0x18E38E}, {0x31, 0.4f, 0x18E38E}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAD64[] = {{0x35, 0.5f, 0x18E38E}, {0x32, 0.4f, 0x18E38E}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAD88[] = {{0x35, 0.5f, 0x18E38E}, {0x6A, 0.5f, 0x271C71}, {0x31, 0.4f, 0x18E38E}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DADB8[] = {{0x6A, 0.5f, 0x271C71}, {0x33, 0.5f, 0x238E39}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DADDC[] = {{0x6A, 0.5f, 0x200000}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DADF4[] = {{0x3C, 0.4f, 0x18E38E}, {0x31, 0.5f, 0x200000}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAE18[] = {{0x6A, 0.4f, 0x271C71}, {0x3B, 0.4f, 0x11C71C}, {0x34, 0.4f, 0x11C71C}, {0x37, 0.4f, 0x11C71C}, {0x31, 0.5f, 0x200000}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAE60[] = {{0x37, 0.5f, 0x18E38E}, {0x31, 0.4f, 0x18E38E}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAE84[] = {{0x37, 0.5f, 0x18E38E}, {0x31, 0.4f, 0x18E38E}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAEA8[] = {{0x36, 0.5f, 0x18E38E}, {0x32, 0.4f, 0x18E38E}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAECC[] = {{0x36, 0.5f, 0x18E38E}, {0x6B, 0.4f, 0x271C71}, {0x31, 0.4f, 0x18E38E}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAEFC[] = {{0x6B, 0.5f, 0x271C71}, {0x33, 0.5f, 0x238E39}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAF20[] = {{0x6B, 0.5f, 0x271C71}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAF38[] = {{0x6B, 0.4f, 0x271C71}, {0x3C, 0.4f, 0x18E38E}, {0x31, 0.5f, 0x200000}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 lbl_802DAF68[] = {{0x3B, 0.4f, 0x11C71C}, {0x31, 0.5f, 0x200000}, {0xFFFF, 0.0f, 0x0}};
Move_8011AB38 *lbl_802DAF8C[2][3][5] = {
    {
        {lbl_802DAC44, lbl_802DAC74, lbl_802DACA4, lbl_802DACD4, lbl_802DACF8},
        {lbl_802DAD1C, lbl_802DAD64, lbl_802DADB8, lbl_802DADF4, lbl_802DAE18},
        {lbl_802DAE60, lbl_802DAEA8, lbl_802DAEFC, lbl_802DAF38, lbl_802DAF68}
    },
    {
        {lbl_802DAC5C, lbl_802DAC8C, lbl_802DACBC, lbl_802DACD4, lbl_802DACF8},
        {lbl_802DAD40, lbl_802DAD88, lbl_802DADDC, lbl_802DADF4, lbl_802DAE18},
        {lbl_802DAE84, lbl_802DAECC, lbl_802DAF20, lbl_802DAF38, lbl_802DAF68}
    }
};
float lbl_802DB004[14] = {0.833f, -0.833f, 2.5f, -2.5f, 4.166f, -4.166f, 6.0f, -6.0f, 8.0f, -8.0f, 1e1f, -1e1f, 12.0f, -12.0f};
int lbl_802DB03C[4] = {4, 8, 0xD, 0x1E};

Queue_800EFE0C **lbl_803EAE14 = 0;
Record_803EAE18 *lbl_803EAE18 = 0;
float lbl_803EAE1C = 9.0f;
unsigned char lbl_803EAE20[8] = {1, 2, 3, 3, 9, 6, 6, 7};
float lbl_803EAE28 = 3.0f;
float lbl_803EAE2C = 3.5f;
float lbl_803EAE30 = 4e1f;
float lbl_803EAE34 = 5.0f;
float lbl_803EAE38 = 3e1f;
float lbl_803EAE3C = 3.0f;
float lbl_803EAE40 = 2.0f;
float lbl_803EAE44 = 2.0f;
float lbl_803EAE48 = 3.0f;
float lbl_803EAE4C = 15.0f;
float lbl_803EAE50 = 1.0f;
float lbl_803EAE54 = 6e1f;
float lbl_803EAE58 = 5.0f;
float lbl_803EAE5C = 4.0f;
float lbl_803EAE60 = 15.0f;
float lbl_803EAE64 = 4.0f;
float lbl_803EAE68 = 1.0f;
float lbl_803EAE6C = 1.5f;
float lbl_803EAE70 = 3.0f;
unsigned short lbl_803EAE74 = 0;
unsigned short lbl_803EAE76 = 0;
float lbl_803EAE78 = 1.0f;
float lbl_803EAE7C = 1.5f;
unsigned int lbl_803EAE80 = 0x73;
float lbl_803EAE84 = 1.0f;
unsigned char lbl_803EAE88 = 0;
float lbl_803EAE8C = 0.6f;
float lbl_803EAE90 = 0.35f;
float lbl_803EAE94 = 0.31f;
float lbl_803EAE98 = 0.2f;
float lbl_803EAE9C = 45.0f;
unsigned char lbl_803EAEA0 = 1;
float lbl_803EAEA4 = 3.75f;
float lbl_803EAEA8 = 1.0f;
float lbl_803EAEAC = 1.0f;
float lbl_803EAEB0 = 0.5f;
float lbl_803EAEB4 = 22.0f;
float lbl_803EAEB8 = 55.0f;
float lbl_803EAEBC = 0.75f;
float lbl_803EAEC0 = 1.5f;
float lbl_803EAEC4 = 1.1f;
float lbl_803EAEC8 = 2.0f;
float lbl_803EAECC = 0.5f;
float lbl_803EAED0 = 76.0f;
float lbl_803EAED4 = 0.35f;
float lbl_803EAED8 = 3.0f;
unsigned int lbl_803EAEDC = 0x32;
unsigned int lbl_803EAEE0 = 0x37;
unsigned int lbl_803EAEE4 = 0x2D;
unsigned char lbl_803EAEE8 = 1;
float lbl_803EAEEC = 2.0f;
float lbl_803EAEF0 = 1.0f;
float lbl_803EAEF4 = 17.0f;
float lbl_803EAEF8 = 1e2f;
float lbl_803EAEFC = 8.0f;
float lbl_803EAF00 = 2e1f;
int lbl_803EAF04 = 180;
float lbl_803EAF08 = 15.0f;
float lbl_803EAF0C = 3.0f;
Object_80039F5C *lbl_803EAF10 = 0;
unsigned int lbl_803EAF14 = 0xA;
float lbl_803EAF18 = 0.182f;
float lbl_803EAF1C = 1.0f;
float lbl_803EAF20 = 4.0f;
float lbl_803EAF24 = 1.0f;
float lbl_803EAF28 = 2.0f;
float lbl_803EAF2C = 4.0f;
float lbl_803EAF30 = -1.0f;
float lbl_803EAF34 = 15.0f;
unsigned int lbl_803EAF38 = 0x96;
float lbl_803EAF3C = 2.0f;
float lbl_803EAF40 = 1.0f;
float lbl_803EAF44 = 2.0f;
float lbl_803EAF48 = 0.5f;
float lbl_803EAF4C = 0.8f;
unsigned char lbl_803EAF50 = 48;
unsigned char lbl_803EAF51 = 240;
float lbl_803EAF54 = 1.2f;
float lbl_803EAF58 = 9.0f;
unsigned short lbl_803EAF5C = 0;
unsigned short lbl_803EAF5E = 20;
float lbl_803EAF60 = 15.0f;
float lbl_803EAF64 = 25.0f;
float lbl_803EAF68 = 0.14f;
float lbl_803EAF6C = 1.0f;
float lbl_803EAF70 = 2.5f;
float lbl_803EAF74 = 0.25f;
float lbl_803EAF78 = 0.25f;
unsigned char lbl_803EAF7C = 1;
unsigned char lbl_803EAF7D = 0;
float lbl_803EAF80 = 17.0f;
float lbl_803EAF84 = 3.0f;
float lbl_803EAF88 = 135.0f;
float lbl_803EAF8C = 6.0f;
unsigned char lbl_803EAF90 = 127;
unsigned char lbl_803EAF91 = 0;
int lbl_803EAF94 = -10;
unsigned char lbl_803EAF98 = 127;
float lbl_803EAF9C = 1.1f;
float lbl_803EAFA0 = 0.4f;
float lbl_803EAFA4 = 0.75f;
float lbl_803EAFA8 = 4.0f;
float lbl_803EAFAC = 2.0f;
float lbl_803EAFB0 = 95.0f;
float lbl_803EAFB4 = 0.5f;
float lbl_803EAFB8 = 1.5f;
float lbl_803EAFBC = 8.0f;
float lbl_803EAFC0 = 0.2f;
float lbl_803EAFC4 = 5.0f;
float lbl_803EAFC8 = 4.0f;
float lbl_803EAFCC = 0.1f;
float lbl_803EAFD0 = 2.5f;
float lbl_803EAFD4 = 2.0f;
float lbl_803EAFD8 = 2.0f;
float lbl_803EAFDC = 16.0f;
unsigned short lbl_803EAFE0 = 90;
float lbl_803EAFE4 = 25.0f;
float lbl_803EAFE8 = 1e1f;
float lbl_803EAFEC = 6.0f;
float lbl_803EAFF0 = 5.0f;
float lbl_803EAFF4 = 3.0f;
float lbl_803EAFF8 = 3.0f;
float lbl_803EAFFC = 0.0f;
float lbl_803EB000 = 8.0f;
float lbl_803EB004 = 1.0f;
signed char lbl_803EB008 = 16;
float lbl_803EB00C = 2e1f;
unsigned char lbl_803EB010 = 1;
float lbl_803EB014 = 6.0f;
float lbl_803EB018 = 8.0f;
float lbl_803EB01C = 1e1f;
float lbl_803EB020 = 1.0f;
unsigned char lbl_803EB024 = 45;
Block_803EB028 *lbl_803EB028 = 0;
float lbl_803EB02C = 0.05f;
float lbl_803EB030 = 1.8e2f;
float lbl_803EB034 = 0.15f;
float lbl_803EB038 = 1e1f;
float lbl_803EB03C = 1e1f;
float lbl_803EB040 = 1e1f;
float lbl_803EB044 = 1e1f;
float lbl_803EB048 = 0.5f;
float lbl_803EB04C = 2.0f;
float lbl_803EB050 = 0.25f;
float lbl_803EB054 = 0.75f;
float lbl_803EB058 = 0.25f;
float lbl_803EB05C = 0.75f;
float lbl_803EB060 = 0.5f;
float lbl_803EB064 = 0.5f;
float lbl_803EB068 = 0.5f;
float lbl_803EB06C = 0.5f;
float lbl_803EB070 = 0.5f;
float lbl_803EB074 = 0.5f;
float lbl_803EB078 = 0.5f;
float lbl_803EB07C = 0.5f;
float lbl_803EB080 = 0.99f;
float lbl_803EB084 = 0.0f;
float lbl_803EB088 = 0.75f;
float lbl_803EB08C = 1.2e2f;
float lbl_803EB090 = 1e1f;
float lbl_803EB094 = 1.25f;
State_803EB098 *lbl_803EB098 = 0;
Lookup_8012078C *lbl_803EB09C = 0;
float lbl_803EB0A0 = 1e1f;
float lbl_803EB0A4 = 0.35f;
float lbl_803EB0A8 = 0.75f;
float lbl_803EB0AC = 0.75f;

}

/* End tables: static const, so they are emitted after the static initializer's pool. */
static Score_8012430C const lbl_8029F584[7] = {fn_80123594, fn_801237F4, fn_80123E2C, fn_80123E30, fn_80123F48, fn_8012368C, fn_80123C2C};
static const Directions_8012430C lbl_8029F5A0[6] = {
    {24.0f, -2.0f, -3.0f, -2.0f, 24.0f, 30.0f, 40.0f, 30.0f},
    {0.0f, 0.0f, 4.0f, 15.0f, 45.0f, 30.0f, 40.0f, 30.0f},
    {45.0f, 15.0f, 4.0f, 0.0f, 0.0f, 45.0f, 60.0f, 45.0f},
    {20.0f, 15.0f, -4.0f, -8.0f, -4.0f, 45.0f, 60.0f, 45.0f},
    {-4.0f, -8.0f, -4.0f, 15.0f, 20.0f, 45.0f, 60.0f, 45.0f},
    {0.0f, -5.0f, -6.0f, -5.0f, 0.0f, 85.0f, 200.0f, 85.0f}
};

extern "C" {
float lbl_803EC9E8 = 40.0f / (210.0f / gFrameTimeScale) * 0.25f;
int lbl_803EC9EC;
unsigned char *lbl_803EC9F0;
}

extern "C" void fn_800EFCD0(int a, State_80039F5C *pQueue, Object_80039F5C *p) {
    p->mUnknown3088 = 0;
    if (lbl_803EAE14[a]->mpHandlers[pQueue->mId].mpUnknown0(p) == 1 && p->mUnknown3088 == 0) {
        fn_800EFC68(a, pQueue);
        fn_800EFCD0(a, pQueue, p);
    }
    p->mUnknown3088 = 1;
    StyleTrackerEndDefensiveMove(p);
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
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, mode, 1.0f, p);
    p->mUnknown512.mUnknown14 = 0;
}

extern "C" int fn_800F0B84(Object_80039F5C *p) {
    int result = 0;

    if (fn_801BE648(p->mpUnknown792) == 47 || fn_801BE648(p->mpUnknown792) == 32
        || p->mMotion.mUnknown28 < gPlyrMoveFwdSpeed * 0.14f) {
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
    if (BallStateGet(BallGetCurrent(), 0) == 4 && p == BallGetTarget(BallGetCurrent())) {
        Message_800F01CC message;

        memset(&message, 0, 4);
        message.mId = 23;
        message.mUnknown1[0] = BallGetIndex(BallGetCurrent());
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
        p->mUnknown512.mUnknown0 = pMotion->mUnknown28 / gPlyrMoveFwdSpeed;
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
    Record_800B8694 *pRecord;
    unsigned int i;

    MemFill(pBlock, 104, 0, 4);
    if (fn_800B6644(index) == 255) {
        return;
    }
    pRecord = fn_800B8694(index);
    pBlock->mUnknown20 = pRecord->mUnknown48;
    pBlock->mUnknown4 = pRecord->mUnknown32;
    pBlock->mUnknown8 = pRecord->mUnknown36;
    pBlock->mUnknown12 = pRecord->mUnknown40;
    pBlock->mUnknown16 = pRecord->mUnknown44;
    pBlock->mUnknown24[0] = pRecord->mUnknown140;
    pBlock->mUnknown24[1] = pRecord->mUnknown144;
    pBlock->mUnknown24[2] = pRecord->mUnknown148;
    pBlock->mUnknown24[3] = pRecord->mUnknown152;
    pBlock->mUnknown24[4] = pRecord->mUnknown156;
    pBlock->mUnknown24[5] = pRecord->mUnknown160;
    pBlock->mUnknown24[6] = pRecord->mUnknown168;
    pBlock->mUnknown24[7] = pRecord->mUnknown164;
    pBlock->mUnknown24[8] = pRecord->mUnknown172;
    pBlock->mUnknown24[9] = pRecord->mUnknown176;
    pBlock->mUnknown24[10] = pRecord->mUnknown180;
    pBlock->mUnknown24[11] = pRecord->mUnknown184;
    if (pRecord->mUnknown0[0] != 0.0f || pBlock->mUnknown24[2] != 0.0f) {
        pBlock->mUnknown0 |= 0x1;
    }
    if (pRecord->mUnknown0[1] != 0.0f || pBlock->mUnknown24[3] != 0.0f) {
        pBlock->mUnknown0 |= 0x2;
    }
    if (pRecord->mUnknown0[2] != 0.0f || pBlock->mUnknown24[1] != 0.0f) {
        pBlock->mUnknown0 |= 0x4;
    }
    if (pRecord->mUnknown0[3] != 0.0f || pBlock->mUnknown24[0] != 0.0f) {
        pBlock->mUnknown0 |= 0x8;
    }
    if (pRecord->mUnknown0[4] != 0.0f) {
        pBlock->mUnknown0 |= 0x10;
    }
    if (pRecord->mUnknown0[5] != 0.0f) {
        pBlock->mUnknown0 |= 0x20;
    }
    if (pRecord->mUnknown0[6] != 0.0f) {
        pBlock->mUnknown0 |= 0x40;
    }
    if (pRecord->mUnknown0[7] != 0.0f) {
        pBlock->mUnknown0 |= 0x80;
    }
    if (pRecord->mUnknown52[0] != 0.0f) {
        pBlock->mUnknown0 |= 0x100;
    }
    if (pRecord->mUnknown52[1] != 0.0f) {
        pBlock->mUnknown0 |= 0x200;
    }
    if (pRecord->mUnknown52[2] != 0.0f) {
        pBlock->mUnknown0 |= 0x400;
    }
    if (pRecord->mUnknown52[3] != 0.0f) {
        pBlock->mUnknown0 |= 0x800;
    }
    if (pRecord->mUnknown52[4] != 0.0f) {
        pBlock->mUnknown0 |= 0x1000;
    }
    if (pRecord->mUnknown52[5] != 0.0f) {
        pBlock->mUnknown0 |= 0x2000;
    }
    if (pRecord->mUnknown52[6] != 0.0f) {
        pBlock->mUnknown0 |= 0x4000;
    }
    if (pRecord->mUnknown52[7] != 0.0f) {
        pBlock->mUnknown0 |= 0x8000;
    }
    if (pRecord->mUnknown52[8] != 0.0f) {
        pBlock->mUnknown0 |= 0x10000;
    }
    if (pRecord->mUnknown52[9] != 0.0f) {
        pBlock->mUnknown0 |= 0x20000;
    }
    if (pRecord->mUnknown52[10] != 0.0f) {
        pBlock->mUnknown0 |= 0x40000;
    }
    if (pRecord->mUnknown52[11] != 0.0f || pBlock->mUnknown24[6] != 0.0f) {
        pBlock->mUnknown0 |= 0x80000;
    }
    if (pRecord->mUnknown52[12] != 0.0f || pBlock->mUnknown24[7] != 0.0f) {
        pBlock->mUnknown0 |= 0x100000;
    }
    if (pRecord->mUnknown52[13] != 0.0f || pBlock->mUnknown24[5] != 0.0f) {
        pBlock->mUnknown0 |= 0x200000;
    }
    if (pRecord->mUnknown52[14] != 0.0f || pBlock->mUnknown24[4] != 0.0f) {
        pBlock->mUnknown0 |= 0x400000;
    }
    if (pRecord->mUnknown52[15] != 0.0f || pBlock->mUnknown24[8] != 0.0f) {
        pBlock->mUnknown0 |= 0x800000;
    }
    if (pRecord->mUnknown52[16] != 0.0f || pBlock->mUnknown24[9] != 0.0f) {
        pBlock->mUnknown0 |= 0x1000000;
    }
    if (pRecord->mUnknown52[17] != 0.0f || pBlock->mUnknown24[10] != 0.0f) {
        pBlock->mUnknown0 |= 0x2000000;
    }
    if (pRecord->mUnknown52[18] != 0.0f || pBlock->mUnknown24[11] != 0.0f) {
        pBlock->mUnknown0 |= 0x4000000;
    }
    if (pRecord->mUnknown52[19] != 0.0f) {
        pBlock->mUnknown0 |= 0x8000000;
    }
    if (pRecord->mUnknown52[20] != 0.0f) {
        pBlock->mUnknown0 |= 0x10000000;
    }
    if (pRecord->mUnknown52[21] != 0.0f) {
        pBlock->mUnknown0 |= 0x20000000;
    }
    if (pBlock->mUnknown12 != 0.0f || pBlock->mUnknown16 != 0.0f) {
        Vector_80039F5C pair;
        float length;
        int angle;

        pair.mX = pBlock->mUnknown12;
        pair.mY = pBlock->mUnknown16;
        length = fn_802270A4(&pair) > 1.0f ? 1.0f : fn_802270A4(&pair);
        angle = fn_801CFE40(pair.mY, pair.mX) & 0xFFFFFF;
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
            *(pBlock->mBytes92 + i / 8) |= 1 << (i % 8);
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
    found = PlayerMoveGetKind(p);
    if (fn_800B83F4(p) != 0) {
        PlayerMoveSetResult(p, 0);
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 240, 1.0f, p);
    } else if (found != 0) {
        if (fn_802372EC(0, 100) < 50) {
            p->mUnknown1008.mUnknown2 = 1;
        } else {
            p->mUnknown1008.mUnknown2 = 2;
        }
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 179, 1.0f, p);
        switch (p->mUnknown1008.mUnknown2) {
        case 1:
            if (side == 3) {
                PlayerMoveSetResult(p, 2);
            } else {
                PlayerMoveSetResult(p, 1);
            }
            break;
        case 2:
            if (side == 3) {
                PlayerMoveSetResult(p, 4);
            } else {
                PlayerMoveSetResult(p, 3);
            }
            break;
        }
    } else {
        PlayerMoveSetResult(p, 0);
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 22, 1.0f, p);
    }
    if (AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 22) != 0 || AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 179) != 0) {
        Entry_800EAC9C *pEntries = p->mpUnknown800;
        Entry_800EAC9C *pEntry;
        float speed;

        if (AnimChanGetNumActiveByState(p->mpUnknown796, pEntries, 179) != 0) {
            index = AnimChanGetStateChannelByIndex(p->mpUnknown796, pEntries, 179, 0);
        } else if (AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 22) != 0) {
            index = AnimChanGetStateChannelByIndex(p->mpUnknown796, pEntries, 22, 0);
        }
        if (p->mUnknown776 == 1) {
            AnimChanSetMirrored(&pEntries[index], AnimChanIsMirrored(&pEntries[index]) == 0);
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
        AnimSeqSetSpeed(&pEntry->mUnknown4C.mpUnknown0, MathInverse(speed));
        speed = 1.0f;
        if (pRatings[0] > 85) {
            short excess = pRatings[0] - 85;

            speed += excess / 170.0f * b;
        }
        pEntry->mUnknown2C = speed;
    } else if (AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 240) != 0) {
        Entry_800EAC9C *pEntries = p->mpUnknown800;

        index = AnimChanGetStateChannelByIndex(p->mpUnknown796, pEntries, 240, 0);
        if (p->mUnknown776 == 1) {
            AnimChanSetMirrored(&pEntries[index], AnimChanIsMirrored(&pEntries[index]) == 0);
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
        if (AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 229) != 0) {
            Entry_800EAC9C *pEntries = p->mpUnknown800;
            Entry_800EAC9C *pEntry;
            int entry = AnimChanGetStateChannelByIndex(p->mpUnknown796, pEntries, 229, 0);
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
            AnimSeqSetSpeed(&pEntry->mUnknown4C.mpUnknown0, MathInverse(speed));
            speed = 1.0f;
            if (pRatings[0] > 85) {
                short excess = pRatings[0] - 85;

                speed += excess / 170.0f * b;
            }
            pEntry->mUnknown2C = speed;
            PlayerMoveSetResult(p, 0);
        }
        AudmonEventPostId(48, &p->mMotion.mPos, p->mId, 0, 0, 0);
        p->mFlags |= 8;
    } else {
        PlayerMoveBegin(p, 1, 34);
        fn_800F1858(p);
    }
}

extern "C" int fn_800F1EE0(Object_80039F5C *p) {
    int result = 0;
    int mode = fn_800AD9B4();

    if (BallFindHeldBy(p) == 0) {
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
        if (!(p->mFlags & 0x4000) && MathAngleDiff(p->mMotion.mUnknown32, 0x400000) > 0x38E38E) {
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
        fn_8022732C(&ahead, &pOther->mMotion.mUnknown40, 15.0f / gFrameTimeScale);
        fn_80227690(&ahead, &ahead, &pMotion->mPos);
        distance = fn_802270A4(&ahead);
        if (!(pOther->mFlags & 0x800) && fn_8011E9B4(pOther) == 0) {
            if (distance < pOther->mMotion.mUnknown28 * (45.0f / gFrameTimeScale)) {
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
        float time = 15.0f / gFrameTimeScale;

        ahead.mX = pOther->mMotion.mPos.mX + pOther->mMotion.mUnknown40 * time;
        ahead.mY = pOther->mMotion.mPos.mY + pOther->mMotion.mUnknown44 * time;
        fn_80227690(&ahead, &ahead, &pMotion->mPos);
        fn_801CFE40(ahead.mY, ahead.mX);
        if (distance < 1.5f) {
            result = 2;
        } else {
            result = fn_802372EC(0, 2) + 2;
        }
    } else if (pMotion->mUnknown28 > gPlyrMoveFwdSpeed * 0.72f) {
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
        PlayerMoveBegin(p, c, 34);
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
        if (PlayerMoveGetKind(p) == 4) {
            fn_800F1C68(p);
        } else {
            fn_800F1858(p);
        }
        p->mUnknown512.mUnknown14 = 0;
        pBlock->mUnknown6 = 2;
        AudmonEventPostId(97, &pMotion->mPos, p->mId, p->mpState->mId, 0, 0);
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
            StyleTrackerFinishJuke(p);
            p->mFlags &= ~0x40000000;
        }
        if (!(p->mFlags & 4)) {
            if (p->mUnknown9[0] != 1) {
                Message_800F01CC message;

                p->mFlags &= ~0x80000;
                memset(&message, 0, 4);
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
        unsigned int bit;
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
            } else if ((*(input.mBytes92 + bit / 8) & (1 << bit)) != (1 << bit)) {
                if (time >= 0.5f) {
                    p->mpState->mUnknown1 = 3;
                }
                pBlock->mUnknown6 = 1;
            }
        }
    }
    return 0;
}

extern "C" int fn_800F2828(Object_80039F5C *a, Object_80039F5C *b) {
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
                float scaled;

                fn_8011E1BC(pTarget, p, 0, 5);
                fn_8011E33C(p, pTarget, 5);
                scaled = p->mRatings[0] / 255.0f;
                p->mUnknown772 = fn_800C49A4(p, scaled * 0.5f + 0.5f);
                return 1;
            }
        }
    }
    return 0;
}

extern "C" int fn_800F2A40(Object_80039F5C *p) {
    Object_80039F5C *pOther = BallGetCurrentHolder();

    if (pOther != 0) {
        Point_8017886C delta;

        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mFacing);
    }
    return 1;
}

extern "C" int fn_800F2AA0(Object_80039F5C *p) {
    Block_800F2AA0 *pBlock = (Block_800F2AA0 *)&p->mUnknown336;
    float scaled;

    if (p->mFlags & 0x4000) {
        pBlock->mUnknown0 = 1;
    } else {
        pBlock->mUnknown0 = 0;
    }
    fn_8009BD60(p);
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 68, 1.0f, p);
    p->mFlags &= ~4;
    scaled = p->mRatings[0] / 255.0f;
    scaled = scaled <= 1.0f ? scaled : 1.0f;
    p->mUnknown772 = fn_800C49A4(p, scaled * 0.7f + 0.3f);
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

        if (p->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.4f) {
            key.mUnknown0 = 2;
        } else {
            key.mUnknown0 = 1;
        }
        key.mUnknown2 = fn_800F2A40(p);
        BallGetPosition(BallGetCurrent(), &delta);
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
        AnimChanStartAnim(a, b, pTable->mEntries[best].mUnknown0, pTable->mEntries[best].mUnknown2, event, p, 1.0f);
    }
    return 0;
}

extern "C" Object_80039F5C *fn_800F2EC8(Object_80039F5C *pExclude, Points_800F3A6C *pInfo) {
    Object_80039F5C *pBest = 0;
    unsigned char index = 0;
    unsigned int i;

    for (i = 0; i < 4; i++) {
        Object_80039F5C *p = fn_8015286C(lbl_8031BDD4, i);

        if (p == pExclude || fn_801520C4(p, &index) == 0 || pInfo->mpUnknown0 != BallGet(index)) {
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

            BallGetPosition(BallGet(*pIndex), &ball);
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
    Vector_80039F5C *pDelta = &delta;
    int heading;
    int angle;
    int turn;
    int result;

    fn_80227690(pDelta, &origin, &target);
    heading = fn_801CFE40(pDelta->mY, pDelta->mX);
    if (pOther != 0) {
        fn_80227690(pDelta, &origin, &pOther->mMotion.mPos);
        if (fn_802270A4(pDelta) > 2.0f) {
            angle = fn_801CFE40(pDelta->mY, pDelta->mX);
            turn = MathAngleDiff(heading, angle);
            if (turn <= 0x1FFFFF) {
                result = 0;
            } else if (turn > 0x600000) {
                result = 1;
            } else if (((heading - angle) & 0xFFFFFF) > 0x7FFFFF) {
                result = 3;
            } else {
                result = 2;
            }
        } else {
            result = 4;
        }
    } else {
        result = 1;
    }
    pBlock->mUnknown24 = result;
    fn_80227690(pDelta, &origin, &p->mMotion.mPos);
    if (fn_802270A4(pDelta) > 2.0f) {
        angle = fn_801CFE40(pDelta->mY, pDelta->mX);
        turn = MathAngleDiff(heading, angle);
        if (turn <= 0x1FFFFF) {
            result = 0;
        } else if (turn > 0x600000) {
            result = 1;
        } else if (((heading - angle) & 0xFFFFFF) > 0x7FFFFF) {
            result = 3;
        } else {
            result = 2;
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
    Ball_t *pBall = BallGet(pBlock->mUnknown62);
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

        BallGetLandingPoint(pBall, &start);
        BallGetPosition(pBall, &target);
        BallGetVelocity(pBall, &velocity);
        fn_80227690(&delta, &start, &target);
        ballTime = fn_802270A4(&delta) / fn_802270A4(&velocity);
        fn_80227690(&delta, &start, &pOther->mMotion.mPos);
        otherTime = fn_802270A4(&delta)
            / (gPlyrMoveFwdSpeed * ((1.0f - lbl_803ED6CC) * (pOther->mRatings[4] / 255.0f) + lbl_803ED6CC));
        fn_80227690(&delta, &start, &p->mMotion.mPos);
        time = fn_802270A4(&delta) / (gPlyrMoveFwdSpeed * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        distance = fn_802270A4(&delta);
        fn_80227690(&apart, &p->mMotion.mPos, &pOther->mMotion.mPos);
        fn_80227690(&ahead, &target, &pOther->mMotion.mPos);
        if (pOther->mpState->mId == 28 && BallFindHeldBy(pOther) == pBall) {
            Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;

            if (pPass->mUnknown0 < pPass->mUnknown16) {
                otherTime = pPass->mUnknown16 - pPass->mUnknown0;
                fn_80227690(&delta, &pPass->mUnknown4, &target);
                ballTime = fn_802270A4(&delta) / fn_802270A4(&velocity);
                fn_80227690(&delta, &pPass->mUnknown4, &p->mMotion.mPos);
                time = fn_802270A4(&delta)
                    / (gPlyrMoveFwdSpeed * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
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

                    if ((MathAngleDiff(angle, pOther->mMotion.mUnknown32) <= 0x3FFFFF
                         && MathAngleDiff(angle, p->mMotion.mUnknown32) > 0x400000 && distance > 2.0f)
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
    if (MathAngleDiff(angle, pMotion->mFacing) > 0x555554 && distance >= 3.5f) {
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
        if (MathAngleDiff(pMotion->mFacing, 0x400000) <= 0x1FFFFF && BallStateGet(pInfo->mpUnknown0, 0) == 4) {
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
    pInfo->mpUnknown0 = BallGet(index);
    BallGetLandingPoint(pInfo->mpUnknown0, &pInfo->mUnknown4);
    BallSolveFallToHeight(pInfo->mpUnknown0, 1.5f, &pInfo->mUnknown48, (Vector_80039F5C *)&pInfo->mUnknown40);
    BallGetVelocity(pInfo->mpUnknown0, &pInfo->mUnknown28);
    BallGetPosition(pInfo->mpUnknown0, &pInfo->mUnknown16);
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
        turn = MathAngleDiff(heading, fn_801CFE40(toTarget.mY, toTarget.mX));
        if (turn <= 0x18E38D
            || (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.0f && passing && progress > 0.5f && turn <= 0x1FFFFF)) {
            pBlock->mUnknown54 = 1;
        }
    }
}

extern "C" void fn_800F3D38(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Point_8017886C *pAim,
                            Info_800F3A6C *pInfo, Points_800F3A6C *pPoints, float *pValue) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;
    Ball_t *pBall = BallGet(pBlock->mUnknown62);
    Point_8017886C delta;
    Point_8017886C lead;

    pTarget->mX = pPoints->mUnknown40.mX;
    delta.mY = 0.0f;
    pTarget->mY = pPoints->mUnknown40.mY;
    delta.mX = 0.0f;
    pAim->mX = pTarget->mX;
    pAim->mY = pTarget->mY;
    if (MathAngleDiff(pOther->mMotion.mUnknown32, 0) != 0) {
        fn_80227690(&delta, &pOther->mMotion.mPos, &pBall->mState.mPos);
    }
    if (pOther->mpState->mId == 28 && BallFindHeldBy(pOther) == pBall) {
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
        if (MathAngleDiff(fn_801CFE40(back.mY, back.mX), p->mMotion.mUnknown32) > 0x471C72) {
            int turn = MathAngleDiff(pOther->mMotion.mUnknown32, p->mMotion.mUnknown32);

            if ((float)MathAngleDiff(pOther->mMotion.mUnknown32, 0x400000) > 35.0f && pOther->mMotion.mUnknown28 > 0.0f) {
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
         / (gPlyrMoveFwdSpeed * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
    if (pOther != 0) {
        fn_80227690(&toOther, pTarget, &pOther->mMotion.mPos);
        fn_80227690(&apart, &pOther->mMotion.mPos, &p->mMotion.mPos);
        otherTime = fn_802270A4(&toOther)
                  / (gPlyrMoveFwdSpeed * ((1.0f - lbl_803ED6CC) * (pOther->mRatings[4] / 255.0f) + lbl_803ED6CC));
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
             / (gPlyrMoveFwdSpeed * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
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
        if (time < ballTime - 2.5f || (time < 12.0f && ballTime < 12.0f)
            || p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.5f) {
            if (fn_802270A4(&toAim) < 7.0f) {
                cut = 1;
            }
        }
        if (MathAngleDiff(p->mMotion.mUnknown32, 0x400000) <= 0x1C71C6 && scale > 0.9f && fn_802270A4(&apart) < 5.0f
            && p->mMotion.mPos.mY < pOther->mMotion.mPos.mY + 5.0f
            && MathAngleDiff(pBlock->mUnknown40, 0x400000) <= 0x1C71C6) {
            cut = 0;
        }
        if (cut != 0 && MathAngleDiff(p->mMotion.mUnknown32, 0x400000) <= 0x1C71C6) {
            if (fn_802270A4(&apart) > 10.0f
                || MathAngleDiff(pOther->mMotion.mUnknown32, fn_801CFE40(toOther.mY, toOther.mX)) > 0x155555) {
                cut = 0;
            }
        }
    }
    if (pOther != 0 && cut != 0) {
        fn_80227690(&ballDir, &pPoints->mUnknown16, &p->mMotion.mPos);
        fn_80227690(&otherDir, &pOther->mMotion.mPos, &p->mMotion.mPos);
        fn_802271A4(&ballDir, &ballDir);
        fn_802271A4(&otherDir, &otherDir);
        if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x18E38D && pBlock->mUnknown49 != 0) {
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
        turn = MathAngleDiff(pBlock->mUnknown40, p->mMotion.mFacing);
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
            && MathAngleDiff(p->mMotion.mFacing, pBlock->mUnknown36) <= 0xE38E2
            && MathAngleDiff(p->mMotion.mUnknown32, pBlock->mUnknown36) <= 0xE38E2) {
            pBlock->mUnknown48 = 1;
        }
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown36;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown40;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown44;
    }
    p->mUnknown512.mUnknown15 = pBlock->mUnknown48;
    if (pBlock->mUnknown40 == pBlock->mUnknown36 && p->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.05f
        && MathAngleDiff(p->mMotion.mUnknown32, pBlock->mUnknown40) > 0x2E38E3
        && MathAngleDiff(p->mMotion.mFacing, 0xC00000) <= 0x2AAAA9) {
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
    BallGetLandingTime(BallGet(pBlock->mUnknown62), &height);
    if (fn_8009A6EC(p) != 0) {
        choice = fn_800997F4(p, BallGet(pBlock->mUnknown62), range, pBlock, 3, 0, 0, &a, &b);
    }
    if (choice == 0x1FFFFFFF) {
        choice = fn_80099734(p, BallGet(pBlock->mUnknown62), 0, mode, range, pBlock, 1, 0, 0, 0);
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
    pBlock->mUnknown62 = BallGetIndex(BallGetCurrent());
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
            if (BallStateGet(points.mpUnknown0, 0) != 4) {
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
    Point_8017886C point;
    Object_80039F5C *pOther;

    point = fn_80177FE0();
    pOther = BallGetCurrentHolder();

    if (pMotion->mPos.mY > point.mY && fn_8011F1A4() != 0) {
        float x;

        if (pOther != 0 && fn_8011F4C8() > 3) {
            if (p->mMotion.mPos.mX > point.mX) {
                x = pOther->mMotion.mPos.mX - 1.0f;
            } else {
                x = pOther->mMotion.mPos.mX + 1.0f;
            }
        } else if (fn_801783AC(0) != 0 && pOther != 0) {
            x = pOther->mMotion.mPos.mX;
        } else {
            x = fn_8011F4D4();
        }
        x = x < 2.0f - fn_80178A08() ? 2.0f - fn_80178A08() : (x <= fn_80178A08() - 2.0f ? x : fn_80178A08() - 2.0f);
        if (fabsf(pMotion->mPos.mX - x) > 1.0f) {
            point.mX = x;
            point.mY = pMotion->mPos.mY + 2.0f;
            fn_80227690(&point, &point, &pMotion->mPos);
            pRecord->mUnknown20 = fn_801CFE40(point.mY, point.mX);
        } else {
            pRecord->mUnknown20 = 0x400000;
        }
        pRecord->mUnknown12 = 1.0f;
    } else if (fn_8011F1A4() != 0) {
        Point_8017886C origin;

        point.mX = fn_8011F4D4();
        origin = fn_80177FE0();
        if (fabsf(pMotion->mPos.mX) - fabsf(origin.mX) < fabsf(point.mX) - fabsf(origin.mX)) {
            if (fn_8011F4C8() > 3) {
                if (point.mX > fn_80177FE0().mX) {
                    point.mX -= 0.5f;
                } else {
                    point.mX += 0.5f;
                }
            }
            fn_80227690(&point, &point, &pMotion->mPos);
            pRecord->mUnknown20 = fn_801CFE40(point.mY, point.mX);
        } else {
            int turn = MathAngleDiff(pMotion->mFacing, 0x400000);

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

extern "C" int fn_800F5208(Object_80039F5C *p, Record_800F4E88 *pRecord) {
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_800B26B0 *pHolderMotion;
    Object_80039F5C *pTarget;
    Object_80039F5C *pHolder;
    Object_80039F5C *pTeamPlayer;
    Point_8017886C delta;
    float distance;
    float reach;
    int offense;
    int heading;
    int spread;
    int half;
    int flag;

    if (fn_8011F1CC()) {
        if (fn_801783AC(13) || BallStateGet(BallGetCurrent(), 0) == 4) {
            return 1;
        }
        delta = fn_80177FE0();
        if (fabsf(p->mMotion.mPos.mX - delta.mX) > 4.0f) {
            pTarget = fn_801245DC(p, fn_80178320(), 0, fn_80178D18(fn_80178320()), 0x18E38E, &distance, 1);
            delta.mY = delta.mY >= pMotion->mPos.mY ? delta.mY : pMotion->mPos.mY;
            if (pTarget && pTarget->mMotion.mPos.mY - delta.mY < lbl_803EAE28 && distance < 5.0f
                && MathAngleDiff(pTarget->mMotion.mUnknown32, 0xC00000) <= 0x3FFFFF && !fn_8011E9B4(pTarget)
                && fn_8011E188() > 30) {
                fn_8011E1BC(p, pTarget, 0, 3);
                return 1;
            }
        }
    }
    pHolder = BallGetCurrentHolder();
    if (!pHolder) {
        Vector_80039F5C velocity;
        Vector_80039F5C ballPos;

        if (BallStateGet(BallGetCurrent(), 0) == 3) {
            BallGetVelocity(BallGetCurrent(), &velocity);
            BallGetPosition(BallGetCurrent(), &ballPos);
            fn_80227690(&delta, &p->mMotion.mPos, &ballPos);
            if (MathAngleDiff(fn_801CFE40(velocity.mY, velocity.mX), delta.Heading()) <= 0x1FFFFF) {
                return 0;
            }
            pHolder = BallGetCurrentTarget();
        }
        if (!pHolder) {
            return 0;
        }
    }
    if (fn_8011F1CC() && !(pHolder->mFlags & 0x8000)) {
        if (p->mUnknown560.mFlags.mBytes[0] && (pTarget = fn_8009BCE8(&p->mUnknown560.mUnknown40)) != 0
            && fn_8011E9B4(pTarget) == 0) {
            return 1;
        }
        return 0;
    }
    pTeamPlayer = fn_8011F54C();
    pHolderMotion = &pHolder->mMotion;
    if (pHolder->mpState->mId >= 0x19 && pHolder->mpState->mId <= 0x1B) {
        return 0;
    }
    if (pHolder != pTeamPlayer && pHolder->mUnknown2914 != 7 && pHolder->mUnknown2914 != 0x18) {
        if (pMotion->mPos.mY < pHolderMotion->mPos.mY) {
            return 1;
        }
        if (MathAngleDiff(pMotion->mUnknown32, pHolderMotion->mUnknown32) > 0x671C72) {
            return 1;
        }
        if (pHolderMotion->mUnknown32 >= 0x98E38F && pHolderMotion->mUnknown32 <= 0xE71C71 && !fn_8011F228()) {
            return 1;
        }
        if (fn_8011F1A4() && fn_8011F4C8() > 3 && MathAngleDiff(pMotion->mFacing, 0x400000) <= 0x155554
            && fn_80177FE0().mY - pMotion->mPos.mY < 1.5f) {
            if (pRecord->mUnknown24) {
                return 1;
            }
        }
        if (p->mUnknown560.mFlags.mBytes[0] && (pTarget = fn_8009BCE8(&p->mUnknown560.mUnknown40)) != 0
            && (pTarget->mUnknown1032 < 4 || pTarget->mUnknown1032 > 5)) {
            return 1;
        }
    }
    if (fn_80178C9C() && (!fn_800BA6F8() || !fn_800BAA24())
        && pMotion->mPos.mY > PlyrGet(fn_80178320(), *fn_8012078C()->mpUnknown4)->mMotion.mPos.mY) {
        return 1;
    }
    if (fabsf(pMotion->mPos.mX - pHolderMotion->mPos.mX) > 10.0f
        || fabsf(pMotion->mPos.mY - pHolderMotion->mPos.mY) > 10.0f) {
        return 1;
    }
    flag = 0;
    if (fn_801783AC(0)) {
        flag = 1;
    } else if (fn_8011F1A4() && (fn_8011F4C8() & 1) && pMotion->mPos.mX < fn_80177FE0().mX) {
        flag = 1;
    } else if (fn_8011F1A4() && (fn_8011F4C8() & 1) == 0 && pMotion->mPos.mX > fn_80177FE0().mX) {
        flag = 1;
    }
    if (!flag) {
        return 0;
    }
    spread = 0x438E39;
    if (!pRecord->mUnknown24 && (!fn_8011F1A4() || fn_8011F4C8() <= 3)) {
        spread = 0x21C71C;
    }
    spread += MathAngleDiff(fn_800C8BAC(p, 0) + pMotion->mFacing, pMotion->mFacing);
    offense = fn_80178320();
    spread &= 0xFFFFFF;
    pTarget = fn_801245DC(p, offense, 0, fn_80178D18(fn_80178320()), spread, &distance, 1);
    if (!pTarget || (pTarget->mFlags & 0x800)) {
        return 0;
    }
    fn_80227690(&delta, &pTarget->mMotion.mPos, pMotion);
    heading = delta.Heading();
    if (fn_8011F1A4() && fn_8011F4C8() > 3) {
        switch (p->mUnknown2914) {
        case 1:
        case 2:
        case 5:
        case 6:
        case 8:
        case 9:
            if (pTarget->mMotion.mPos.mY > fn_80177FE0().mY) {
                if (fabsf(pMotion->mPos.mX - fn_80177FE0().mX) < 5.0f) {
                    return 0;
                }
            }
            break;
        }
        if (pTarget->mUnknown1032 == 8) {
            fn_80227690(&delta, &fn_8009BCE8(&pTarget->mUnknown1036)->mMotion.mPos, pMotion);
            if (MathAngleDiff(heading, delta.Heading()) <= 0x11C71B && fn_802270A4(&delta) < distance) {
                return 0;
            }
        }
    }
    reach = 3.5f;
    if (fn_8011F1A4() && (fn_8011F4C8() & 1)) {
        if (fn_8011F1A4() && fn_8011F4C8() > 3 && pMotion->mPos.mX < fn_8011F4D4()) {
            reach += (float)(fn_8011F4C8() - 1);
        } else {
            reach += (float)(fn_8011F4C8() - 1) / 3.0f;
        }
    } else if (fn_8011F1A4() && (fn_8011F4C8() & 1) == 0) {
        if (fn_8011F1A4() && fn_8011F4C8() > 3 && pMotion->mPos.mX > fn_8011F4D4()) {
            reach += fn_8011F4C8();
        } else {
            reach += fn_8011F4C8() / 3.0f;
        }
    }
    if (fn_8011F1A4() && fn_8011F4C8() > 3) {
        half = MathAngleDiff(pMotion->mFacing, heading) / 2;
    } else {
        half = MathAngleDiff(pMotion->mFacing, heading) / 4;
    }
    reach *= fn_801CFB94(half);
    if (pMotion->mPos.mY > fn_80177FE0().mY) {
        reach *= 2.0f;
    } else {
        if (pTarget->mMotion.mPos.mY > fn_80177FE0().mY && fn_8011E95C()) {
            reach /= 3.0f;
        }
    }
    if (distance < reach) {
        if (pTarget->mpState->mId == 0x20) {
            if (pTarget->mUnknown1032 == 6) {
                return 1;
            }
        } else if (pTarget->mUnknown1032 != 4) {
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_800F5AD4(Object_80039F5C *p) {
    Vector_80039F5C pos = p->mMotion.mPos;
    float distance;
    Object_80039F5C *pNear;
    Object_80039F5C *pOther;
    int flag;

    if (fn_8011F1A4() && (fn_8011F4C8() & 1)) {
        pos.mX -= 1.5f;
    } else {
        pos.mX += 1.5f;
    }
    pNear = fn_80124C28(p, &distance, 0x355555, 2.75f, 0.5f, p->mMotion.mFacing);
    flag = 0;
    if (fn_8011F1A4() && (fn_8011F4C8() & 1) && p->mMotion.mPos.mX > fn_80177FE0().mX) {
        flag = 1;
    } else if (fn_8011F1A4() && (fn_8011F4C8() & 1) == 0 && p->mMotion.mPos.mX < fn_80177FE0().mX) {
        flag = 1;
    }
    if (flag) {
        fn_8011E938(pNear);
        return 0;
    }
    pOther = PlyrFindNearest(&pos, &distance, p->mIdBytes[2]);
    if (!pOther || pOther == p || distance > 4.0f
        || fabsf(pOther->mMotion.mPos.mX - fn_80177FE0().mX) < fabsf(p->mMotion.mPos.mX - fn_80177FE0().mX)) {
        return 1;
    }
    if (pNear && pNear->mIdBytes[2] != p->mIdBytes[2]) {
        return 1;
    }
    return 0;
}

extern "C" int fn_800F5CBC(Object_80039F5C *p, Record_800F4E88 *pRecord) {
    Object_800B26B0 *pMotion;
    Object_80039F5C *pNear;
    Vector_80039F5C target;
    Point_8017886C delta;
    Point_8017886C point;
    float distance;
    float range;
    float scale;
    int result = pRecord->mUnknown20;
    int angle;
    int facing;
    int step;
    int onBall;
    int span;

    pNear = fn_80124C28(p, &distance, 0x2AAAAA, 3.5f, 0.5f, p->mMotion.mFacing);
    pMotion = &p->mMotion;
    onBall = 0;
    if (pNear) {
        range = 3.5f;
        if (pNear->mIdBytes[2] == p->mIdBytes[2]) {
            if (pRecord->mUnknown12 < 1e-7f) {
                return result;
            }
            if (pNear->mUnknown1032 != 4) {
                range *= 0.5f;
            }
        }
        if (distance < range) {
            if (pNear->mUnknown1032 != 4) {
                target = pNear->mMotion.mPos;
                target.mX += 2.0f * pNear->mMotion.mUnknown40;
                target.mY += 2.0f * pNear->mMotion.mUnknown44;
            } else {
                Object_80039F5C *pPartner = fn_8009BCE8(&pNear->mUnknown1036);

                target.mX = (pNear->mMotion.mPos.mX + pPartner->mMotion.mPos.mX) * 0.5f;
                target.mY = (pNear->mMotion.mPos.mY + pPartner->mMotion.mPos.mY) * 0.5f;
            }
            fn_80227690(&delta, &target, pMotion);
            angle = delta.Heading();
            facing = pMotion->mFacing;
            scale = distance / 3.5f;
            if (pNear->mpState->mId == 0x1A) {
                onBall = 1;
                point.mX = pNear->mMotion.mPos.mX;
                point.mY = fn_80177FE0().mY;
                fn_80227690(&point, &point, pMotion);
                facing = point.Heading();
            }
            step = (int)((1.0f - scale) * 2796202.0f);
            step = (int)(fn_801CFB94(MathAngleDiff(angle, pMotion->mFacing) / 2) * (float)step);
            if (!onBall && fn_8011F1A4() && MathAngleDiff(pMotion->mFacing, angle) <= 0xE38E2
                && pMotion->mPos.mY < fn_80177FE0().mY) {
                point.mX = fn_8011F4D4();
                point.mY = fn_80177FE0().mY;
                fn_80227690(&point, &point, pMotion);
                angle = point.Heading();
                if (((angle - facing) & 0xFFFFFF) > 0x800000) {
                    step = -step;
                }
            } else if (MathAngleDiff(pMotion->mFacing, angle) <= 0xE38E2
                       || MathAngleDiff(pMotion->mFacing, 0xC00000) <= 0x38E38D) {
                if (((angle - pRecord->mUnknown20) & 0xFFFFFF) <= 0x7FFFFF) {
                    step = -step;
                }
            } else if (((angle - facing) & 0xFFFFFF) <= 0x7FFFFF) {
                step = -step;
            }
            result = (pMotion->mFacing + step) & 0xFFFFFF;
            span = (result - pMotion->mFacing) & 0xFFFFFF;
            if ((span <= 0x7FFFFF && ((pRecord->mUnknown20 - pMotion->mFacing) & 0xFFFFFF) <= 0x7FFFFF)
                || (span > 0x800000 && ((pRecord->mUnknown20 - pMotion->mFacing) & 0xFFFFFF) > 0x800000)) {
                if (MathAngleDiff(pRecord->mUnknown20, angle) > MathAngleDiff(result, angle)) {
                    result = pRecord->mUnknown20 & 0xFFFFFF;
                }
            }
            p->mUnknown512.mUnknown15 = 0;
        }
    }
    return result;
}

extern "C" void fn_800F60BC(Object_80039F5C *p) {
    int facing = p->mMotion.mFacing & 0xFFFFFF;

    if ((facing >= 0x755556 && facing <= 0x8AAAAA) || facing < 0xAAAAA || facing > 0xF55556) {
        if (fn_8011F1A4() && fn_8011F4C8() > 3) {
            fn_800C89F0(p, 0x400000, 2, 0, 1.0f);
        }
    }
}

extern "C" int fn_800F6158(Object_80039F5C *p) {
    Object_800F4E14_800F60BC *pBlock = (Object_800F4E14_800F60BC *)&p->mUnknown336;
    Vector_80039F5C *pPos = &p->mMotion.mPos;
    int result;

    pBlock->mUnknown20 = (p->mpState->mUnknown2 << 17) & 0xFE0000;
    result = fn_800F4E14(p, (Object_800F4E14 *)pBlock);
    if (!result) {
        Point_8017886C offset;
        unsigned char distance = p->mpState->mUnknown1;

        pBlock->mUnknown8 = (distance >> 3) + (distance & 7) * 0.14285715f;
        pBlock->mUnknown12 = p->mpState->mUnknown3[0] * 0.003921569f;
        fn_80227538(&offset, pBlock->mUnknown20, pBlock->mUnknown8);
        pBlock->mUnknown0 = p->mMotion.mPos.mX + offset.mX;
        pBlock->mUnknown4 = pPos->mY + offset.mY;
        pBlock->mUnknown24 = result;
        fn_8011E3EC(p, 3);
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown20;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown20;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
    }
    return 0;
}

extern "C" int fn_800F62A4(Object_80039F5C *p) {
    Message_800F01CC message;

    if (fn_800F5AD4(p)) {
        memset(&message, 0, 4);
        if (fn_8011F1CC() && !fn_801783AC(0)) {
            message.mId = 31;
        } else {
            message.mId = 33;
        }
        fn_800F053C(0, p->mpState, &message, p);
        return 0;
    } else {
        memset(&message, 0, 4);
        message.mId = 47;
        message.mUnknown1[1] = p->mpState->mUnknown2;
        message.mUnknown1[0] = p->mpState->mUnknown1;
        message.mUnknown1[2] = p->mpState->mUnknown3[0];
        fn_800F053C(0, p->mpState, &message, p);
    }
    return 0;
}

extern "C" int fn_800F6370(Object_80039F5C *p) {
    int result = 0;
    Record_800F4E88 *pRecord = (Record_800F4E88 *)&p->mUnknown336;
    Message_800F01CC message;
    int direction;

    if (p == BallGetCurrentHolder()) {
        fn_8011E3EC(p, 0);
        fn_8011E240(p);
        memset(&message, 0, sizeof(message));
        message.mId = 1;
        fn_800F053C(0, p->mpState, &message, p);
        result = 1;
    } else {
        fn_8010A2DC(p, 0, -1);
        fn_800F60BC(p);
        if (!(p->mFlags & 0x4000)) {
            if (fn_800F5208(p, pRecord)) {
                fn_8011E3EC(p, 0);
                result = 1;
                fn_8011E240(p);
                p->mUnknown512.mUnknown15 = result;
                direction = fn_800F5CBC(p, pRecord);
                p->mUnknown512.mUnknown14 = result;
                p->mUnknown512.mUnknown4 = direction;
                p->mUnknown512.mUnknown8 = direction;
                p->mUnknown512.mUnknown0 = pRecord->mUnknown12;
                memset(&message, 0, sizeof(message));
                if (fn_801783AC(13) == 0 && BallStateGet(BallGetCurrent(), 0) != 4
                    && fn_801783AC(0) == 0 && fn_8011F1CC() != 0) {
                    message.mId = 31;
                    if (fn_8011F2F8() != 0) {
                        message.mUnknown1[1] = result;
                        if (fn_801783AC(0) == 0) {
                            fn_8011E194(p, 1);
                        }
                        int found = fn_800F06F4(0, p->mpState, 19, 0xFFFF) == 0xFFFF ? 0 : 1;

                        if (found) {
                            message.mUnknown1[0] = 32;
                            fn_800F05E4(0, p->mpState, &message, p);
                        } else {
                            fn_800F053C(0, p->mpState, &message, p);
                        }
                    } else {
                        fn_800F053C(0, p->mpState, &message, p);
                    }
                } else {
                    message.mId = 33;
                    fn_800F053C(0, p->mpState, &message, p);
                }
                result = 1;
            } else {
                if (pRecord->mUnknown24 == 0) {
                    if (fn_800F4E88(p, pRecord)) {
                        pRecord->mUnknown24 = 1;
                        if (fn_801783AC(13) == 0
                            && (p->mpState->mUnknown3[1] == 47 || p->mpState->mUnknown3[1] == 72)) {
                            result = 1;
                        }
                    }
                } else {
                    fn_800F4F08(p, pRecord);
                }
                if (MathAngleDiff(pRecord->mUnknown20, p->mMotion.mFacing) <= 0x155554) {
                    p->mUnknown512.mUnknown15 = 1;
                }
                direction = fn_800F5CBC(p, pRecord);
                if (p->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.05f
                    && MathAngleDiff(p->mMotion.mUnknown32, p->mMotion.mFacing) > 0x355555
                    && MathAngleDiff(p->mMotion.mUnknown32, pRecord->mUnknown20) > 0x400000) {
                    p->mUnknown512.mUnknown14 = 1;
                    p->mUnknown512.mUnknown8 = pRecord->mUnknown20;
                    p->mUnknown512.mUnknown0 = 0.0f;
                    p->mUnknown512.mUnknown4 = pRecord->mUnknown20;
                } else {
                    p->mUnknown512.mUnknown4 = direction;
                    p->mUnknown512.mUnknown14 = 1;
                    p->mUnknown512.mUnknown8 = direction;
                    p->mUnknown512.mUnknown0 = pRecord->mUnknown12;
                }
            }
        } else {
            fn_8011E3EC(p, 0);
            fn_8011E240(p);
            memset(&message, 0, sizeof(message));
            if (fn_801783AC(13) == 0 && BallStateGet(BallGetCurrent(), 0) != 4
                && fn_801783AC(0) == 0 && fn_8011F1CC() != 0) {
                message.mId = 31;
                if (fn_8011F2F8() != 0) {
                    message.mUnknown1[1] = 1;
                    if (fn_801783AC(0) == 0) {
                        fn_8011E194(p, 1);
                    }
                    int found = fn_800F06F4(0, p->mpState, 19, 0xFFFF) == 0xFFFF ? 0 : 1;

                    if (found) {
                        message.mUnknown1[0] = 32;
                        fn_800F05E4(0, p->mpState, &message, p);
                    } else {
                        fn_800F053C(0, p->mpState, &message, p);
                    }
                } else {
                    fn_800F053C(0, p->mpState, &message, p);
                }
            } else {
                message.mId = 33;
                fn_800F053C(0, p->mpState, &message, p);
            }
            result = 1;
        }
    }
    return result;
}

/* Discarded by SN's linker: only its pool (8.0f at 0x8029E1F0) survives in .rodata. */
// FAKEMATCH: invented body; only its pool constant(s) are target evidence
extern "C" {
static float _StrippedScaleByEight(float x)
{
    return x * 8.0f;
}
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
            Object_80039F5C *p = PlyrGet(fn_80178320(), i);
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

extern "C" int fn_800F6878(Object_80039F5C *p, Object_80039F5C *pOther) {
    int result = 0;

    if (p && pOther) {
        Point_8017886C delta;

        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        if (MathAngleDiff(pOther->mMotion.mUnknown32, 0x400000) < 0xAAAAA
            && (MathAngleDiff(p->mMotion.mFacing, 0xC00000) < 0x400000 || fn_802270A4(&delta) < 2.0f)) {
            result = 1;
        }
        if (result && MathAngleDiff(p->mMotion.mFacing, 0x400000) < 0x155555) {
            result = 0;
        }
        if (result && !(p->mMotion.mPos.mY < fn_80178A44() - 5.0f)) {
            result = 0;
        }
        if (result && (pOther->mpState->mId == 51 || pOther->mpState->mId == 52)) {
            result = 0;
        }
        if (result && !(pOther->mMotion.mUnknown28 >= gPlyrMoveFwdSpeed * 0.72f)) {
            result = 0;
        }
    }
    return result;
}

extern "C" int fn_800F69C0(int angle, Object_80039F5C *p) {
    int found = 0;
    int result = angle;
    unsigned char team;
    unsigned char i;
    int direction;

    for (team = 0; team <= 1; team++) {
        unsigned int n = fn_80178D18(team);

        for (i = 0; i < n; i++) {
            Object_80039F5C *pOther = PlyrGet(team, i);

            if (fn_8022781C(&p->mMotion.mPos, &pOther->mMotion.mPos) <= lbl_803EAE34) {
                Point_8017886C delta;

                fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
                direction = fn_801CFE40(delta.mY, delta.mX);
                if (MathAngleDiff(direction, result) < (int)(lbl_803EAE30 * 46603.38f)) {
                    found = 1;
                    result += (int)(lbl_803EAE38 * 46603.38f);
                }
            }
        }
    }
    return found ? result : angle;
}

extern "C" void fn_800F6AD8(float *p) {
    if (p) {
        if (fabsf(p[0]) < 0.3f) {
            p[0] = 0.0f;
        }
        if (fabsf(p[1]) < 0.3f) {
            p[1] = 0.0f;
        }
    }
}

extern "C" void fn_800F6B2C(Object_80039F5C *p, Vector_80039F5C *pDelta) {
    if (p && pDelta) {
        Point_8017886C origin;
        Point_8017886C target;
        float limit;

        origin = fn_80177FE0();
        // FAKEMATCH: mY goes through a pointer to target while mX is accessed directly, as the target's 4(r31) / 16(r1) accesses show
        Point_8017886C *pTarget = &target;
        fn_80227638(pTarget, &p->mMotion.mPos, pDelta);
        if (fabsf(target.mX) < 4.0f) {
            limit = origin.mY + lbl_803EAE3C;
            pTarget->mY = pTarget->mY < limit ? limit : pTarget->mY;
        } else {
            limit = origin.mY - 1.0f;
            pTarget->mY = pTarget->mY < limit ? limit : pTarget->mY;
        }
        pTarget->mY = pTarget->mY > fn_80178A44() - 5.0f ? fn_80178A44() - 5.0f : pTarget->mY;
        target.mX = target.mX < 2.5f - fn_80178A08() ? 2.5f - fn_80178A08()
                  : (target.mX > fn_80178A08() - 2.5f ? fn_80178A08() - 2.5f : target.mX);
        fn_80227690(pDelta, pTarget, &p->mMotion.mPos);
    }
}

extern "C" void fn_800F6C90(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut) {
    if (p && pOther && pOut) {
        Point_8017886C origin;

        origin = fn_80177FE0();
        if (pTarget->mY < origin.mY + 7.0f) {
            pOut->mY = 0.0f;
        } else {
            fn_800F6D40(p, pOther, pTarget, pOut);
        }
        fn_800F6AD8(&pOut->mX);
    }
}

extern "C" void fn_800F6D40(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut) {
    if (p && pOther && pOut) {
        Point_8017886C delta;

        fn_80227690(&delta, pTarget, &p->mMotion.mPos);
        if (!(p->mpState->mUnknown2 & 2)) {
            pOut->mY = pTarget->mY - p->mMotion.mPos.mY;
            if (fn_8009E9A4() == 1 && pOther->mUnknown2914 == 3) {
                pOut->mY = pOut->mY + 5.0f;
            }
        } else if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
            pOut->mY = pTarget->mY - p->mMotion.mPos.mY;
        } else {
            pOut->mY = pTarget->mY - p->mMotion.mPos.mY;
        }
        if (fn_800F6878(p, pOther)) {
            pOut->mY = pOut->mY + 2.5f;
        } else {
            fn_800F6AD8(&pOut->mX);
        }
    }
}

extern "C" void fn_800F6E30(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut) {
    if (p && pOther && pOut) {
        Point_8017886C origin = fn_80177FE0();
        Vector_80039F5C ball;
        Point_8017886C delta;
        int side;
        int flag;

        BallGetPosition(BallGetCurrent(), &ball);
        fn_80227690(&delta, pTarget, &p->mMotion.mPos);
        side = (p->mpState->mUnknown2 ^ 1) & 1;
        if (pTarget->mX > ball.mX ? side == 0 : side != 0) {
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag) {
            if (p->mMotion.mPos.mX > pTarget->mX) {
                float dx = pTarget->mX - p->mMotion.mPos.mX;

                pOut->mX = fabsf(dx) > 1.0f ? dx + 1.0f : 0.0f;
            } else if (fn_802270A4(&delta) > 2.0f) {
                pOut->mX = pTarget->mX - p->mMotion.mPos.mX + 1.0f;
            } else {
                pOut->mX = pTarget->mX - p->mMotion.mPos.mX - 1.0f;
            }
        } else if (p->mMotion.mPos.mX < pTarget->mX) {
            float dx = pTarget->mX - p->mMotion.mPos.mX;

            pOut->mX = fabsf(dx) > 1.0f ? dx - 1.0f : 0.0f;
        } else if (fn_802270A4(&delta) > 2.0f) {
            pOut->mX = pTarget->mX - p->mMotion.mPos.mX - 1.0f;
        } else {
            pOut->mX = pTarget->mX - p->mMotion.mPos.mX + 1.0f;
        }
        if (pOther->mMotion.mPos.mX > fn_80178A08() - 10.0f) {
            pOut->mX = fn_80178A08() - 1.0f - p->mMotion.mPos.mX;
        } else if (pOther->mMotion.mPos.mX < 10.0f - fn_80178A08()) {
            pOut->mX = 1.0f - fn_80178A08() - p->mMotion.mPos.mX;
        }
        if (fn_800F6878(p, pOther)) {
            if (ball.mX > pOther->mMotion.mPos.mX) {
                pOut->mX = 0.01f;
            } else if (ball.mX < pOther->mMotion.mPos.mX) {
                pOut->mX = -0.01f;
            }
        } else {
            fn_800F6AD8(&pOut->mX);
        }
    }
}

extern "C" void fn_800F70D0(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Vector_80039F5C *pOut) {
    if (p && pOther && pOut) {
        Point_8017886C origin;
        Point_8017886C delta;

        origin = fn_80177FE0();
        fn_80227690(&delta, pTarget, &p->mMotion.mPos);
        if (!(p->mpState->mUnknown2 & 2)) {
            if (pTarget->mY < origin.mY) {
                pOut->mY = pTarget->mY - p->mMotion.mPos.mY + 2.0f;
            } else if (p->mMotion.mPos.mY > pTarget->mY) {
                float dy = pTarget->mY - p->mMotion.mPos.mY;

                pOut->mY = fabsf(dy) > 1.0f ? dy + 1.0f : 0.0f;
            } else {
                pOut->mY = pTarget->mY - p->mMotion.mPos.mY - 1.0f;
            }
        } else if (p->mMotion.mPos.mY < pTarget->mY) {
            float dy = pTarget->mY - p->mMotion.mPos.mY;

            pOut->mY = fabsf(dy) > 1.0f ? dy - 1.0f : 0.0f;
        } else {
            pOut->mY = pTarget->mY - p->mMotion.mPos.mY + 1.0f;
        }
        fn_800F6AD8(&pOut->mX);
    }
}

extern "C" void fn_800F722C(Object_80039F5C *p, Object_80039F5C *pOther, float *pX, float *pOut) {
    if (p && pOther && pOut) {
        Vector_80039F5C pos;
        int side;
        int flag;
        float distance;

        BallGetPosition(BallGetCurrent(), &pos);
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

extern "C" void fn_800F7314(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut) {
    float speed = 0.0f;

    if (p && pOther && pOut) {
        Ball_t *pBall = BallGetCurrent();
        Point_8017886C toBall;
        Block_800F7314 *pBlock = (Block_800F7314 *)&p->mUnknown336;
        Point_8017886C spot;
        Point_8017886C toSpot;
        int heading;
        int direction;

        fn_80227690(&toBall, &pBall->mState.mPos, &p->mMotion.mPos);
        fn_8009F928(pOther, &spot, 5, pBlock->mUnknown21);
        fn_80227690(&toSpot, &spot, &p->mMotion.mPos);
        fn_800F6D40(p, pOther, &spot, pOut);
        fn_800F6E30(p, pOther, &spot, pOut);
        fn_800F6B2C(p, pOut);
        heading = fn_801CFE40(pOut->mY, pOut->mX);
        direction = heading & 0xFFFFFF;
        if (p->mMotion.mPos.mY >= fn_80178A44() - 5.0f && MathAngleDiff(p->mMotion.mUnknown32, 0x400000) > 0x1C71C7
            && fn_802270A4(&toSpot) < 2.0f) {
            pOut->mY = 0.0f;
            pBlock->mUnknown8 = fn_801CFE40(0.0f, pOut->mX);
            pBlock->mUnknown24 = 0;
            pBlock->mUnknown4 = 0xC00000;
            pBlock->mUnknown12 = 0.66f;
        } else if (pOther->mMotion.mUnknown28 < gPlyrMoveFwdSpeed * 0.14f) {
            if (MathAngleDiff(p->mMotion.mFacing, toBall.Heading()) > 0x11C71C) {
                pBlock->mUnknown8 = (toBall.Heading() + 0x400000) & 0xFFFFFF;
                pBlock->mUnknown12 = 0.25f;
            } else {
                pBlock->mUnknown8 = (toBall.Heading() + 0x400000) & 0xFFFFFF;
                pBlock->mUnknown12 = 0.0f;
            }
            pBlock->mUnknown4 = toBall.Heading();
            pBlock->mUnknown24 = 0;
        } else if (MathAngleDiff(direction, pOther->mMotion.mUnknown32) <= 0x3FFFFF) {
            int facing = pOther->mMotion.mUnknown32;
            Point_8017886C flat;

            if (MathAngleDiff(heading, facing) > 0x200000 && p->mMotion.mPos.mY < fn_80178A2C()) {
                int delta = (facing - direction) & 0xFFFFFF;
                direction = facing - 0x200000;
                if (delta > 0x800000) {
                    direction = facing + 0x200000;
                }
            }
            pBlock->mUnknown8 = direction;
            pBlock->mUnknown4 = direction;
            flat.mX = 0.0f;
            flat.mY = toSpot.mY;
            speed = pOther->mMotion.mUnknown28
                / (gPlyrMoveFwdSpeed * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
            if (fn_802270A4(&flat) > 1.5f) {
                speed = 1.0f;
            }
            pBlock->mUnknown12 = speed;
            pBlock->mUnknown12 = speed > 1.0f ? 1.0f : speed;
            if (MathAngleDiff(pBlock->mUnknown8, p->mMotion.mUnknown32) < 0xAAAAA) {
                pBlock->mUnknown24 = 1;
            } else {
                pBlock->mUnknown24 = 0;
            }
        } else {
            int near;

            pBlock->mUnknown8 = direction;
            pBlock->mUnknown4 = 0xC00000;
            near = fn_800F6878(p, pOther);
            if (near || MathAngleDiff(direction, pOther->mMotion.mUnknown32) <= 0x3FFFFF) {
                if (pBall->mState.mPos.mX > pOther->mMotion.mPos.mX) {
                    pBlock->mUnknown8 = 0x31C71C;
                    pBlock->mUnknown4 = 0x31C71C;
                } else if (pBall->mState.mPos.mX < pOther->mMotion.mPos.mX) {
                    pBlock->mUnknown8 = 0x4E38E3;
                    pBlock->mUnknown4 = 0x4E38E3;
                }
                pBlock->mUnknown24 = 1;
                pBlock->mUnknown12 = 1.0f;
            } else {
                if (MathAngleDiff(pOther->mMotion.mUnknown32, 0x400000) <= 0x11C71B
                    && fabsf(p->mMotion.mPos.mX - pOther->mMotion.mPos.mX) < lbl_803EAE2C
                    && p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 2.0f) {
                    pBlock->mUnknown23 = 1;
                    pBlock->mUnknown22 = 2;
                    pBlock->mUnknown20 = 0;
                }
                pBlock->mUnknown24 = 0;
                pBlock->mUnknown12 = 0.66f;
            }
        }
    }
}

extern "C" void fn_800F7798(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut) {
    if (p && pOther && pOut) {
        Point_8017886C toBall;
        Block_800F7314 *pBlock = (Block_800F7314 *)&p->mUnknown336;
        Point_8017886C spot;
        Point_8017886C toSpot;
        int heading;
        int direction;

        fn_80227690(&toBall, &BallGetCurrent()->mState.mPos, &p->mMotion.mPos);
        fn_8009F928(pOther, &spot, 5, pBlock->mUnknown21);
        fn_80227690(&toSpot, &spot, &p->mMotion.mPos);
        fn_800F70D0(p, pOther, &spot, pOut);
        fn_800F722C(p, pOther, &spot.mX, &pOut->mX);
        fn_800F6B2C(p, pOut);
        heading = fn_801CFE40(pOut->mY, pOut->mX);
        direction = heading & 0xFFFFFF;
        if (p->mMotion.mPos.mY >= fn_80178A44() - 5.0f && MathAngleDiff(p->mMotion.mUnknown32, 0x400000) > 0x1C71C7
            && fn_802270A4(&toSpot) < 2.0f) {
            pOut->mY = 0.0f;
            pBlock->mUnknown24 = 0;
            pBlock->mUnknown8 = fn_801CFE40(0.0f, pOut->mX);
            pBlock->mUnknown4 = 0xC00000;
            pBlock->mUnknown12 = 0.66f;
        } else if (pOther->mMotion.mUnknown28 < gPlyrMoveFwdSpeed * 0.14f) {
            if (MathAngleDiff(p->mMotion.mFacing, toBall.Heading()) > 0x11C71C) {
                pBlock->mUnknown8 = (toBall.Heading() + 0x800000) & 0xFFFFFF;
                pBlock->mUnknown12 = 0.25f;
            } else {
                pBlock->mUnknown8 = (toBall.Heading() + 0x800000) & 0xFFFFFF;
                pBlock->mUnknown12 = 0.0f;
            }
            pBlock->mUnknown4 = toBall.Heading();
            pBlock->mUnknown24 = 0;
        } else if (MathAngleDiff(direction, pOther->mMotion.mUnknown32) <= 0x3FFFFF) {
            int facing = pOther->mMotion.mUnknown32;
            Point_8017886C flat;
            float speed;

            if (MathAngleDiff(heading, facing) > 0x200000 && p->mMotion.mPos.mY < fn_80178A2C()) {
                int delta = (facing - direction) & 0xFFFFFF;
                direction = facing - 0x200000;
                if (delta > 0x800000) {
                    direction = facing + 0x200000;
                }
            }
            pBlock->mUnknown8 = direction;
            pBlock->mUnknown4 = direction;
            flat.mX = toSpot.mX;
            flat.mY = 0.0f;
            speed = pOther->mMotion.mUnknown28
                / (gPlyrMoveFwdSpeed * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
            if (fn_802270A4(&flat) > 1.5f) {
                speed = 1.0f;
            }
            pBlock->mUnknown12 = speed;
            pBlock->mUnknown12 = speed > 1.0f ? 1.0f : speed;
            if (MathAngleDiff(pBlock->mUnknown8, p->mMotion.mUnknown32) < 0xAAAAA) {
                pBlock->mUnknown24 = 1;
            } else {
                pBlock->mUnknown24 = 0;
            }
        } else {
            if (p->mMotion.mPos.mY - pOther->mMotion.mPos.mY < 7.0f) {
                int facing = pOther->mMotion.mUnknown32;

                if (facing < 0x800000) {
                    direction = facing;
                }
            }
            pBlock->mUnknown24 = 0;
            pBlock->mUnknown8 = direction;
            pBlock->mUnknown4 = 0xC00000;
            pBlock->mUnknown12 = 0.66f;
        }
    }
}

extern "C" void fn_800F7B64(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut) {
    float lift = 0.0f;
    float side = 0.0f;

    if (p && pOther && pOut) {
        Point_8017886C toOther;
        Block_800F7314 *pBlock;

        fn_80227690(&toOther, &pOther->mMotion.mPos, &p->mMotion.mPos);
        pBlock = (Block_800F7314 *)&p->mUnknown336;
        if (pOther->mpState->mId == 0x14 && pBlock->mUnknown21 != 0) {
            Point_8017886C spot;
            int angle;

            PlayerCutGetEndPoint(pOther, &spot);
            angle = PlayerCutGetRunHeading(pOther) & 0xFFFFFF;
            if (MathAngleDiff(angle, 0) < 0x200000) {
                side = 1.0f;
            } else if (MathAngleDiff(angle, 0x800000) < 0x200000) {
                side = -1.0f;
            } else {
                int diff = MathAngleDiff(angle, 0x400000);

                if (diff < 0x200000) {
                    if (p->mMotion.mPos.mX > pOther->mMotion.mPos.mX) {
                        side = 1.0f;
                    } else {
                        side = -1.0f;
                    }
                    side *= fn_801CFB18(0x400000 - diff);
                    if ((angle < 0x355555 && side > 0.0f) || (angle > 0x4AAAAB && side < 0.0f)) {
                        side *= 0.25f;
                    }
                    lift = 1.0f;
                } else {
                    diff = MathAngleDiff(angle, 0xC00000);
                    if (diff < 0x200000) {
                        if (p->mMotion.mPos.mX > pOther->mMotion.mPos.mX) {
                            side = 1.0f;
                        } else {
                            side = -1.0f;
                        }
                        side *= fn_801CFB18(0xC00000 - diff);
                        if ((angle > 0xCE38E4 && side > 0.0f) || (angle < 0xB55556 && side < 0.0f)) {
                            side *= 0.25f;
                        }
                    }
                }
            }
            if ((unsigned int)(pOther->mpState->mUnknown2 - 8) <= 1 && MathAngleDiff(angle, 0x400000) < 0x1C71C7) {
                side = 0.0f;
                lift = 2.0f;
            }
            if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
                pOut->mX = spot.mX - p->mMotion.mPos.mX + side;
                pOut->mY = pOther->mMotion.mPos.mY - p->mMotion.mPos.mY + 1.0f + lift;
                fn_800F6AD8(&pOut->mX);
                fn_800F6B2C(p, pOut);
                pBlock->mUnknown8 = fn_801CFE40(pOut->mY, pOut->mX);
                pBlock->mUnknown24 = 0;
                pBlock->mUnknown12 = 0.66f;
                if (MathAngleDiff(angle, 0xC00000) < 0x200000) {
                    pBlock->mUnknown4 = toOther.Heading();
                } else {
                    pBlock->mUnknown4 = pBlock->mUnknown8;
                }
            } else {
                pOut->mX = spot.mX - p->mMotion.mPos.mX + side;
                pOut->mY = pOther->mMotion.mPos.mY - p->mMotion.mPos.mY - 1.0f + lift;
                fn_800F6AD8(&pOut->mX);
                fn_800F6B2C(p, pOut);
                pBlock->mUnknown4 = pBlock->mUnknown8 = fn_801CFE40(pOut->mY, pOut->mX);
                pBlock->mUnknown12 = 0.66f;
                pBlock->mUnknown24 = 0;
            }
        } else if (MathAngleDiff(pOther->mMotion.mUnknown32, 0) < 0x1C71C7
                   || MathAngleDiff(pOther->mMotion.mUnknown32, 0x800000) < 0x1C71C7) {
            fn_800F7798(p, pOther, pOut);
        } else {
            fn_800F7314(p, pOther, pOut);
        }
    }
}

extern "C" void fn_800F7F68(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut) {
    if (p && pOther && pOut) {
        Point_8017886C toOther;
        Point_8017886C fromOther;
        Block_800F7314 *pBlock;
        Point_8017886C origin;
        Vector_80039F5C target;
        int angle;

        fn_80227690(&toOther, &pOther->mMotion.mPos, &p->mMotion.mPos);
        fn_80227690(&fromOther, &p->mMotion.mPos, &pOther->mMotion.mPos);
        pBlock = (Block_800F7314 *)&p->mUnknown336;
        origin = fn_80177FE0();
        if ((MathAngleDiff(pOther->mMotion.mUnknown32, fromOther.Heading()) < 0xE38E3 && fn_802270A4(&toOther) < 12.0f
             && (pOther->mMotion.mUnknown28 >= gPlyrMoveFwdSpeed * 0.14f
                 || fabsf(pOther->mMotion.mPos.mY - origin.mY) < 2.5f))
            || pOther->mpState->mId == 0x34) {
            pBlock->mUnknown8 = pOther->mMotion.mUnknown32;
            pBlock->mUnknown4 = toOther.Heading();
            pBlock->mUnknown12 = 0.5f;
            pBlock->mUnknown24 = 0;
            pOut->mX = pOut->mY = pOut->mZ = 0.0f;
            return;
        }
        fn_80227538(&target, (pOther->mMotion.mUnknown32 + 0x800000) & 0xFFFFFF, 1.0f);
        fn_800F6B2C(p, &target);
        target.mX += pOther->mMotion.mPos.mX;
        target.mZ = 0.0f;
        target.mY += pOther->mMotion.mPos.mY;
        fn_80227690(pOut, &target, &p->mMotion.mPos);
        angle = fn_80120794((Vector_80039F5C *)&p->mMotion, &target, (Vector_80039F5C *)&pOther->mMotion.mUnknown40,
                            p->mMotion.mUnknown28, pOther->mMotion.mUnknown28, pOther->mMotion.mUnknown32,
                            fn_802270A4(&toOther));
        pBlock->mUnknown8 = angle;
        pBlock->mUnknown12 = 1.0f;
        pBlock->mUnknown4 = angle;
        if (MathAngleDiff(p->mMotion.mFacing, angle) < 0xAAAAA) {
            pBlock->mUnknown24 = 1;
        } else {
            pBlock->mUnknown24 = 0;
        }
    }
}

extern "C" void fn_800F81C0(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut) {
    if (p && pOther && pOut) {
        Ball_t *pBall = BallGetCurrent();
        Vector_80039F5C *pPos = &p->mMotion.mPos;
        Block_800F8A88 *pBlock = (Block_800F8A88 *)&p->mUnknown336;
        Point_8017886C origin;
        Point_8017886C toBall;
        Point_8017886C spot;
        Point_8017886C toSpot;
        int direction;

        origin = fn_80177FE0();
        fn_80227690(&toBall, &pBall->mState.mPos, pPos);
        fn_8009F928(pOther, &spot, 5, pBlock->mUnknown21);
        fn_80227690(&toSpot, &spot, pPos);
        fn_800F6C90(p, pOther, &spot, pOut);
        fn_800F6E30(p, pOther, &spot, pOut);
        fn_800F6B2C(p, pOut);
        direction = fn_801CFE40(pOut->mY, pOut->mX) & 0xFFFFFF;
        if (pOther->mMotion.mUnknown28 < gPlyrMoveFwdSpeed * 0.14f) {
            if (MathAngleDiff(p->mMotion.mFacing, fn_801CFE40(toBall.mY, toBall.mX)) > 0x71C71) {
                pBlock->mUnknown8 = (fn_801CFE40(toBall.mY, toBall.mX) + 0x800000) & 0xFFFFFF;
                pBlock->mUnknown12 = 0.66f;
            } else {
                pBlock->mUnknown8 = (fn_801CFE40(toBall.mY, toBall.mX) + 0x800000) & 0xFFFFFF;
                pBlock->mUnknown12 = 0.0f;
            }
            pBlock->mUnknown4 = fn_801CFE40(toBall.mY, toBall.mX);
            pBlock->mUnknown24 = 0;
        } else if (MathAngleDiff(direction, pOther->mMotion.mUnknown32) < 0x400000) {
            pBlock->mUnknown8 = direction;
            pBlock->mUnknown4 = direction;
            pBlock->mUnknown12 = 1.0f;
            if (MathAngleDiff(p->mMotion.mFacing, direction) < 0xAAAAA) {
                pBlock->mUnknown24 = 1;
            } else {
                pBlock->mUnknown24 = 0;
            }
        } else if (pOther->mMotion.mPos.mY < origin.mY + 6.0f) {
            pBlock->mUnknown8 = direction;
            pBlock->mUnknown4 = fn_801CFE40(toSpot.mY, toSpot.mX);
            pBlock->mUnknown12 = 1.0f;
            pBlock->mUnknown24 = 0;
        } else {
            fn_80227690(&toSpot, &spot, pPos);
            pBlock->mUnknown8 = pOther->mMotion.mUnknown32;
            pBlock->mUnknown4 = fn_801CFE40(toSpot.mY, toSpot.mX);
            if (fn_800F6878(p, pOther)) {
                pBlock->mUnknown24 = 1;
                pBlock->mUnknown12 = 1.0f;
            } else {
                pBlock->mUnknown24 = 0;
                pBlock->mUnknown12 = 0.66f;
            }
        }
    }
}

extern "C" void fn_800F846C(Object_80039F5C *p, Object_80039F5C *pOther, Vector_80039F5C *pOut) {
    if (p && pOther && pOut) {
        Block_800F8A88 *pBlock = (Block_800F8A88 *)&p->mUnknown336;
        float offset;
        float distance;

        pOut->mY = lbl_803EAE40 + fn_80177FE0().mY - p->mMotion.mPos.mY;
        if (pOther->mMotion.mPos.mX > fn_80177FE0().mX) {
            offset = lbl_803EAE48;
        } else {
            offset = -lbl_803EAE48;
        }
        pOut->mX = pOther->mMotion.mPos.mX + offset - p->mMotion.mPos.mX;
        fn_800F6B2C(p, pOut);
        distance = fn_802270A4(pOut);
        pBlock->mUnknown8 = fn_801CFE40(pOut->mY, pOut->mX) & 0xFFFFFF;
        pBlock->mUnknown4 = 0xC00000;
        if (distance > lbl_803EAE44) {
            pBlock->mUnknown12 = 0.5f;
        } else {
            pBlock->mUnknown12 = 0.25f;
        }
        pBlock->mUnknown24 = 0;
    }
}

extern "C" void fn_800F8588(Object_80039F5C *p, Object_80039F5C *pOther) {
    if (p && pOther) {
        Block_800F8A88 *pBlock = (Block_800F8A88 *)&p->mUnknown336;
        Point_8017886C origin;
        Point_8017886C delta;

        origin = fn_80177FE0();
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        if (pBlock->mUnknown26 != 3 && pBlock->mUnknown26 != 7
            && pOther->mMotion.mUnknown28 <= gPlyrMoveFwdSpeed * 0.14f) {
            return;
        }
        if (fn_8011E9D8(pOther->mpState) && pBlock->mUnknown27) {
            pBlock->mUnknown26 = 6;
        } else if ((p->mUnknown2914 == 17 || p->mUnknown2914 == 18) && fn_800F67E8(pOther) > 1) {
            pBlock->mUnknown26 = 4;
        } else if (fabsf(delta.mX) > 4.0f && p->mMotion.mPos.mY < fn_80178A2C()
                   && (p->mMotion.mPos.mY > origin.mY + 4.0f || pOther->mMotion.mPos.mY < origin.mY - 1.0f)) {
            pBlock->mUnknown26 = 3;
        } else if (pOther->mpState->mId == 20) {
            float total = PlayerCutGetAnimLength(pOther->mpState->mUnknown2);
            float done = PlayerCutGetAnimTime(pOther);

            if (done / total > (1.0f - p->mRatings[8] * 0.003921569f) * 0.75f) {
                pBlock->mUnknown26 = 2;
            } else if (pBlock->mUnknown26 == 7) {
                pBlock->mUnknown26 = 0;
            } else {
                return;
            }
        } else {
            float limit = p->mMotion.mPos.mY < fn_80178A2C() ? 25.0f : 58.0f;

            if (MathAngleDiff(pOther->mMotion.mUnknown32, 0x400000) < (int)(limit * 46603.38f)
                || MathAngleDiff(pOther->mMotion.mUnknown32, 0xC00000) < (int)(limit * 46603.38f)) {
                pBlock->mUnknown26 = 0;
            } else {
                pBlock->mUnknown26 = 1;
            }
        }
    }
}

extern "C" void fn_800F8828(Object_80039F5C *p, Object_80039F5C *pOther, Block_800F8A88 *pBlock) {
    if (p && pOther) {
        Point_8017886C origin;

        origin = fn_80177FE0();
        p->mpState->mUnknown2 |= pBlock->mUnknown25;
        if (fabsf(p->mMotion.mPos.mY - origin.mY) <= 5.0f && fabsf(pOther->mMotion.mPos.mY - origin.mY) <= 5.0f
            && pBlock->mUnknown25 == 2) {
            p->mpState->mUnknown2 &= ~pBlock->mUnknown25;
        }
    }
}

extern "C" void fn_800F88E4(Object_80039F5C *p, Object_80039F5C *pTarget) {
    unsigned char *pMine = &p->mpState->mUnknown2;
    unsigned char *pTheirs = 0;
    Object_80039F5C *pFound = 0;
    unsigned short i;
    unsigned int n = fn_80178D18(fn_80178320());

    for (i = 0; i < n; i++) {
        Object_80039F5C *pOther = PlyrGet(fn_80178320(), i);

        if (pOther->mpState->mId == 22 && pTarget == fn_8009BCE8(&pOther->mUnknown336) && pOther != p) {
            pFound = pOther;
            pTheirs = &pFound->mpState->mUnknown2;
        }
    }
    if (pFound && fn_8022781C(&pFound->mMotion.mPos, &pTarget->mMotion.mPos) < 5.0f
        && fn_8022781C(&p->mMotion.mPos, &pTarget->mMotion.mPos) < 5.0f) {
        Vector_80039F5C ball;
        int right;

        BallGetPosition(BallGetCurrent(), &ball);
        right = pTarget->mMotion.mPos.mX > ball.mX;
        *pTheirs &= ~1;
        *pMine &= ~1;
        *pTheirs &= ~2;
        *pMine &= ~2;
        if ((right && pFound->mMotion.mPos.mX < p->mMotion.mPos.mX)
            || (!right && pFound->mMotion.mPos.mX > p->mMotion.mPos.mX)) {
            *pTheirs |= 2;
            *pMine |= 1;
        } else {
            *pTheirs |= 1;
            *pMine |= 2;
        }
    }
}

extern "C" void fn_800F8A88(Object_80039F5C *p, Object_80039F5C *pOther) {
    Block_800F8A88 *pBlock = (Block_800F8A88 *)&p->mUnknown336;
    Point_8017886C delta;

    pBlock->mUnknown24 = 0;
    fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
    if (pOther->mpState->mId == 56) {
        pBlock->mUnknown12 = 0.0f;
    } else {
        Vector_80039F5C out;
        int unknown32;

        fn_800F8828(p, pOther, pBlock);
        fn_800F88E4(p, pOther);
        out.mX = out.mY = out.mZ = 0.0f;
        switch (pBlock->mUnknown26) {
        case 0:
            fn_800F7314(p, pOther, &out);
            break;
        case 1:
            fn_800F7798(p, pOther, &out);
            break;
        case 2:
            fn_800F7B64(p, pOther, &out);
            break;
        case 3:
            fn_800F7F68(p, pOther, &out);
            break;
        case 4:
            fn_800F81C0(p, pOther, &out);
            break;
        case 5:
            break;
        case 6:
            fn_800F846C(p, pOther, &out);
            break;
        }
        unknown32 = p->mMotion.mUnknown32;
        if (MathAngleDiff(pBlock->mUnknown8, p->mMotion.mFacing) > 0x600000
            && pOther->mMotion.mUnknown28 >= gPlyrMoveFwdSpeed * 0.14f && pBlock->mUnknown12 >= gPlyrMoveFwdSpeed * 0.14f
            && fn_802270A4(&delta) < 5.0f) {
            int angle = ((pBlock->mUnknown8 + unknown32) / 2) & 0xFFFFFF;

            if (MathAngleDiff(angle, pBlock->mUnknown8) > 0x400000) {
                angle = (angle + 0x800000) & 0xFFFFFF;
            }
            pBlock->mUnknown8 = angle;
            pBlock->mUnknown12 = 0.66f;
            pBlock->mUnknown20 = 0;
        }
        pBlock->mUnknown8 &= 0xFFFFFF;
        pBlock->mUnknown4 &= 0xFFFFFF;
        if (pBlock->mUnknown16 <= 44 && p->mpState->mUnknown1 == 2 && pOther->mUnknown1052 != 0) {
            switch (p->mUnknown2914) {
            case 13:
            case 15:
                pBlock->mUnknown12 = 0.65f;
                break;
            case 17:
            case 18:
                pBlock->mUnknown12 = 0.45f;
                break;
            }
        }
        pBlock->mUnknown12 = pBlock->mUnknown12 < 0.0f ? 0.0f : pBlock->mUnknown12;
    }
}

extern "C" int fn_800F8D24(Object_80039F5C *p) {
    return 0;
}

extern "C" int fn_800F8D2C(Object_80039F5C *p) {
    Block_800F8D2C *pBlock = (Block_800F8D2C *)&p->mUnknown336;
    Object_80039F5C *pOther = fn_8009BCE8(&pBlock->mRef);

    if (pOther) {
        Vector_80039F5C delta;
        int angle;
        int side;
        int direction;

        fn_802276B4(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        if (delta.mY > -2.5f) {
            return 0;
        }
        pBlock->mUnknown12 = 0.5f;
        if (pOther->mpState->mId == 20) {
            angle = PlayerCutGetRunHeading(pOther);
        } else if ((unsigned char)(pOther->mpState->mId - 51) <= 1) {
            angle = pOther->mMotion.mFacing;
        } else {
            angle = pOther->mMotion.mUnknown32;
        }
        if (angle > 0x800000) {
            angle = 0x1000000 - angle;
        }
        if (delta.mX < -2.0f) {
            side = 0;
            direction = 0x700000;
        } else if (delta.mX > 2.0f) {
            side = 1;
            direction = 0x100000;
        } else {
            side = 2;
            if (MathAngleDiff(angle, 0x400000) <= 0xAAAAA) {
                direction = 0x400000;
                if (delta.mY < -6.0f) {
                    pBlock->mUnknown12 = 0.0f;
                }
            } else {
                direction = 0x700000;
                if (angle < 0x400000) {
                    direction = 0x100000;
                }
            }
        }
        if (p->mMotion.mPos.mY < fn_80177FE0().mY + 8.0f) {
            if (side == 2) {
                if (MathAngleDiff(angle, 0x400000) <= 0x11C71B) {
                    pBlock->mUnknown22 = side;
                    return 1;
                }
                if (pBlock->mUnknown16 > 60) {
                    return 0;
                }
            } else if (side == 1 ? angle < 0x400000 : angle > 0x400000) {
                if (pBlock->mUnknown16 > 30) {
                    return 0;
                }
            } else if (MathAngleDiff(angle, 0x400000) > 0x11C71B) {
                if (fabsf(delta.mX) < 2.0f) {
                    pBlock->mUnknown12 = 0.0f;
                }
                if (pBlock->mUnknown16 > 45) {
                    return 0;
                }
            } else {
                if (fabsf(delta.mX) < 1.0f) {
                    pBlock->mUnknown12 = 0.0f;
                }
                if (delta.mY > -5.0f) {
                    pBlock->mUnknown22 = 2;
                    return 1;
                }
            }
        } else {
            if (delta.mY < -9.0f) {
                return 0;
            }
            if ((MathAngleDiff(angle, 0x400000) > 0x200000 || side != 2) && pBlock->mUnknown16 > 30) {
                return 0;
            }
        }
        pBlock->mUnknown8 = direction;
        pBlock->mUnknown4 = 0xC00000;
        return 1;
    }
    return 0;
}

extern "C" int fn_800F9024(Object_80039F5C *p) {
    Block_800F8D2C *pBlock = (Block_800F8D2C *)&p->mUnknown336;
    Object_80039F5C *pOther = fn_8009BCE8(&pBlock->mRef);

    if (pOther) {
        Vector_80039F5C delta;
        Vector_80039F5C ball;
        int angle;
        float limit;
        float t;

        fn_802276B4(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        if (pOther->mpState->mId == 20) {
            angle = PlayerCutGetRunHeading(pOther);
            if (angle > 0x800000) {
                return 0;
            }
        } else {
            if ((unsigned char)(pOther->mpState->mId - 51) <= 1) {
                angle = pOther->mMotion.mFacing;
            } else {
                angle = pOther->mMotion.mUnknown32;
            }
            if (angle > 0x800000) {
                angle = 0x1000000 - angle;
            }
        }
        if (MathAngleDiff(angle, 0x400000) > 0x1C71C7) {
            return 0;
        }
        delta.mX = pOther->mMotion.mUnknown40 * lbl_803EAE54 + delta.mX;
        if (fabsf(delta.mX) > lbl_803EAE2C) {
            return 0;
        }
        if ((p->mpState->mUnknown2 & 2) == 0) {
            limit = -2.0f;
        } else {
            limit = -1.0f;
        }
        if (delta.mY > limit) {
            return 0;
        }
        if (delta.mY < -7.0f && fn_8009E9A4() != 1) {
            return 0;
        }
        BallGetPosition(BallGetCurrent(), &ball);
        if ((p->mpState->mUnknown2 & 1) == 0) {
            if (pOther->mMotion.mPos.mX > ball.mX) {
                float lo = pOther->mMotion.mPos.mX - lbl_803EAE50;

                if (p->mMotion.mPos.mX > lo) {
                    t = (p->mMotion.mPos.mX - lo) / (lbl_803EAE50 + lbl_803EAE2C);
                } else {
                    t = -((lo - p->mMotion.mPos.mX) / (lbl_803EAE2C - lbl_803EAE50));
                }
            } else {
                float hi = pOther->mMotion.mPos.mX + lbl_803EAE50;

                if (p->mMotion.mPos.mX < hi) {
                    t = -((hi - p->mMotion.mPos.mX) / (lbl_803EAE50 + lbl_803EAE2C));
                } else {
                    t = (p->mMotion.mPos.mX - hi) / (lbl_803EAE2C - lbl_803EAE50);
                }
            }
        } else {
            if (pOther->mMotion.mPos.mX > ball.mX) {
                float hi = pOther->mMotion.mPos.mX + lbl_803EAE50;

                if (p->mMotion.mPos.mX < hi) {
                    t = (hi - p->mMotion.mPos.mX) / (lbl_803EAE50 + lbl_803EAE2C);
                } else {
                    t = -((p->mMotion.mPos.mX - hi) / (lbl_803EAE2C - lbl_803EAE50));
                }
            } else {
                float lo = pOther->mMotion.mPos.mX - lbl_803EAE50;

                if (p->mMotion.mPos.mX > lo) {
                    t = (p->mMotion.mPos.mX - lo) / (lbl_803EAE50 + lbl_803EAE2C);
                } else {
                    t = -((lo - p->mMotion.mPos.mX) / (lbl_803EAE2C - lbl_803EAE50));
                }
            }
        }
        t = t < -1.0f ? -1.0f : (t > 1.0f ? 1.0f : t);
        if (t > 0.0f) {
            t = 1.0f - t;
        } else {
            t = -1.0f + t;
        }
        pBlock->mUnknown8 = (int)((t * lbl_803EAE4C + 90.0f) * 46603.38f);
        fn_80178A2C();
        pBlock->mUnknown4 = 0xC00000;
        pBlock->mUnknown12 = 0.5f;
        return 1;
    }
    return 0;
}

extern "C" int fn_800F930C(Object_80039F5C *p) {
    Block_800F930C *pBlock = (Block_800F930C *)&p->mUnknown336;
    Object_80039F5C *pOther = fn_8009BCE8(&pBlock->mRef);

    if (pOther) {
        Vector_80039F5C delta;

        fn_802276B4(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        if (fabsf(delta.mX) <= 4.0f && delta.mY <= -3.0f && pBlock->mUnknown16 <= 60) {
            if (delta.mX > 0.0f) {
                pBlock->mUnknown8 = 0x100000;
            } else {
                pBlock->mUnknown8 = 0x700000;
            }
            pBlock->mUnknown4 = 0xC00000;
            pBlock->mUnknown12 = 0.33f;
            return 1;
        }
    }
    return 0;
}

extern "C" Object_80039F5C *fn_800F93D0(Object_80039F5C *p) {
    Object_80039F5C *pResult = 0;
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char i;

    for (i = 0; i < 7; i++) {
        if (pRecord->mUnknown16[i] == p->mIdBytes[1]) {
            pResult = PlyrGet(fn_80178320(), i);
            break;
        }
    }
    return pResult;
}

extern "C" void fn_800F9440(Object_80039F5C *p, Object_80039F5C *pOther) {
    fn_8011F4E0()->mUnknown16[p->mIdBytes[1]] = pOther->mIdBytes[1];
}

extern "C" Object_80039F5C *fn_800F9480(Object_80039F5C *p) {
    int ref = 0;
    float best = -1000.0f;
    Object_80039F5C *pResult = 0;
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    Point_8017886C origin;
    Block_800FAD2C *pBlock;
    int n;
    int i;

    origin = fn_80177FE0();
    pBlock = (Block_800FAD2C *)fn_8011F4EC();
    n = fn_80178D18(p->mIdBytes[2]);
    for (i = 0; i <= 2; i++) {
        Object_80039F5C *pOther = PlyrGet(p->mIdBytes[2] ^ 1, pBlock->mUnknown415[i]);

        if (pOther->mUnknown1032 == 0 && fabsf(p->mMotion.mPos.mX - pOther->mMotion.mPos.mX) < 20.0f) {
            unsigned int count = 0;
            int j;

            for (j = 0; j < n; j++) {
                int valid = 1;
                Object_80039F5C *pMate = PlyrGet(p->mIdBytes[2], j);
                int slot = fn_800F06F4(0, pMate->mpState, 22, 0xFFFF);

                if (slot != 0xFFFF) {
                    if (pMate->mpState[slot].mId == 22) {
                        ref = pMate->mUnknown336;
                    } else {
                        State_80039F5C *pState = &pOther->mpState[slot];

                        if (pState->mUnknown1 >= 1 && pState->mUnknown1 <= 5) {
                            PlyrGet(p->mIdBytes[2] ^ 1, pRecord->mUnknown8[pState->mUnknown1 - 1]);
                            fn_8009BD2C(pOther, &ref);
                        } else {
                            valid = 0;
                        }
                    }
                    if (valid && pOther->mId == ref) {
                        count++;
                    }
                }
            }
            if (count <= 1) {
                float score = (pOther->mMotion.mPos.mY - origin.mY) * 1.5f
                            - fabsf(pOther->mMotion.mPos.mX - p->mMotion.mPos.mX);

                if (score > best) {
                    best = score;
                    pResult = pOther;
                }
            }
        }
    }
    return pResult;
}

extern "C" Object_80039F5C *fn_800F9688(Object_80039F5C *p) {
    Object_80039F5C *pResult = 0;
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    int n = fn_80178D18(p->mIdBytes[2]);
    int i;

    for (i = 0; i <= 2; i++) {
        Object_80039F5C *pOther = PlyrGet(p->mIdBytes[2] ^ 1, pRecord->mUnknown8[i]);

        if (pOther->mUnknown1032 == 0 && fabsf(p->mMotion.mPos.mX - pOther->mMotion.mPos.mX) < 10.0f) {
            int count = 0;
            int j;

            for (j = 0; j < n; j++) {
                Object_80039F5C *pMate = PlyrGet(p->mIdBytes[2], j);
                int index = fn_800F06F4(0, pMate->mpState, 22, 0xFFFF);

                if (index != 0xFFFF && pMate->mpState[index].mUnknown1 == i + 1) {
                    count++;
                }
            }
            if (count == 0) {
                pResult = pOther;
            }
        }
    }
    return pResult;
}

extern "C" Point_8017886C AssignGetFormationPos(Object_80039F5C *p) {
    Point_8017886C base;
    PlayBookFormation_t *pTeam;
    PlayBookPosition_t *pEntry;
    Point_8017886C point;

    base = fn_80177FFC(p->mIdBytes[2]);
    pTeam = PlayBookGetFormation(p->mIdBytes[2]);
    pEntry = &pTeam->mUnknown8.mUnknown84[0][p->mIdBytes[1]];
    point.mX = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mX;
    // FAKEMATCH: mY and the transform go through a pointer to point while mX is stored directly; this places &point after the first lfs as the target does
    Point_8017886C *pPoint = &point;
    pPoint->mY = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mY;
    fn_80227638(pPoint, pPoint, &base);
    return point;
}

extern "C" int fn_800F986C(Object_80039F5C *p) {
    unsigned char count = 0;
    unsigned char kind = fn_8009F6B4();
    int result = 16;
    unsigned char i = 0;
    Point_8017886C base;
    Point_8017886C pos;
    unsigned int n;
    unsigned char state;

    base = fn_80177FFC(p->mIdBytes[2]);
    n = fn_80178D18(fn_80178320());
    for (; i < n; i++) {
        if (PlyrGet(fn_80178320(), i)->mUnknown2914 == 14) {
            count++;
        }
    }
    state = p->mUnknown2914;
    pos = AssignGetFormationPos(p);
    switch (state) {
    case 16:
        if (fn_8009F778(p)) {
            if (kind == 1) {
                result = 4;
            } else if (kind == 2) {
                result = 6;
                if (pos.mX > base.mX) {
                    result = 5;
                }
            } else {
                result = 8;
                if (pos.mX > base.mX) {
                    result = 7;
                }
            }
        } else {
            result = 2;
            if (pos.mX > base.mX) {
                result = 3;
            }
        }
        break;
    case 17:
    case 18:
        if (fn_8009F778(p)) {
            result = 9;
        } else {
            result = pos.mX > base.mX;
        }
        break;
    case 14:
        if (count == 2) {
            result = 11;
            if (pos.mX > base.mX) {
                result = 13;
            }
        } else if (kind == 1) {
            result = 10;
            if (pos.mX > base.mX) {
                result = 14;
            }
        } else {
            result = 12;
        }
        break;
    case 13:
    case 15:
        if (kind == 2 || kind == 3) {
            result = 12;
        } else if (pos.mX > base.mX) {
            result = 14;
        } else {
            result = 10;
        }
        break;
    case 2:
    case 10:
    case 11:
    case 12:
        result = 15;
        break;
    }
    return result;
}

extern "C" Object_80039F5C *fn_800F9AF0(unsigned char slot) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char i = 0;
    unsigned char index = pRecord->mUnknown8[slot];
    Object_80039F5C *p = PlyrGet(fn_80178308(), index);

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
    int id = 0;
    int found = 0;
    unsigned char i;

    if (!p) {
        found = 1;
    } else {
        id = p->mIdBytes[1];
    }
    for (i = 0; i < 3; i++) {
        unsigned char slot;

        if (forward) {
            slot = i;
        } else {
            slot = 2 - i;
        }
        if (found) {
            Object_80039F5C *pSlot = fn_800F9AF0(slot);
            if (pSlot) {
                pResult = pSlot;
                break;
            }
        } else if (PlyrGet(fn_80178308(), pRecord->mUnknown8[slot])->mIdBytes[1] == (unsigned char)id) {
            found = 1;
        }
    }
    return pResult;
}

extern "C" int fn_800F9CAC(Entry_800FAECC *pEntries, unsigned char index, unsigned char count, Object_80039F5C *p) {
    return 1;
}

extern "C" int fn_800F9CB4(void) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char ahead = 0;
    unsigned char behind = 0;
    unsigned char aheadKind3 = 0;
    int team = fn_80178308();
    unsigned char behindKind3 = 0;
    Point_8017886C origin;
    int aheadKind4 = 0;
    int behindKind4 = 0;
    unsigned char i;

    origin = fn_80177FE0();
    for (i = 0; i <= 2; i++) {
        Object_80039F5C *pOther = PlyrGet(team, pRecord->mUnknown8[i]);
        float x = pOther->mMotion.mPos.mX;
        unsigned char kind = pOther->mUnknown2914;

        if (fabsf(x - origin.mX) > 1.0f) {
            if (x > origin.mX) {
                if (kind == 4) {
                    aheadKind4 = 1;
                } else if (kind == 3) {
                    aheadKind3++;
                }
                ahead++;
            } else {
                if (kind == 4) {
                    behindKind4 = 1;
                } else if (kind == 3) {
                    behindKind3++;
                }
                behind++;
            }
        }
    }
    if (behind > ahead) {
        return 0;
    }
    if (ahead > behind) {
        return 1;
    }
    if (behindKind3 > aheadKind3) {
        return 0;
    }
    if (aheadKind3 > behindKind3) {
        return 1;
    }
    if (aheadKind4 && !behindKind4) {
        return 1;
    }
    if (behindKind4 && !aheadKind4) {
        return 0;
    }
    return origin.mX >= 0.0f;
}

extern "C" Object_80039F5C *fn_800F9E3C(Object_80039F5C *p, int flag) {
    Object_80039F5C *pResult = 0;
    int team = fn_80178308();
    unsigned char i;
    unsigned int n = fn_80178D18(fn_80178320());

    for (i = 0; i <= 2; i++) {
        unsigned char valid;
        int index = PlayBookGetReceiver(team, i, &valid);

        if (valid && index != 0xFF) {
            Object_80039F5C *pTarget = PlyrGet(team, index);
            unsigned char kind = pTarget->mUnknown2914;

            if (((kind == 1 || kind == 2) && !flag) || kind == 4) {
                int count = 0;
                unsigned char j;

                for (j = 0; j < n; j++) {
                    Object_80039F5C *pOther = PlyrGet(fn_80178320(), j);
                    int slot = fn_800F06F4(0, pOther->mpState, 22, 0xFFFF);

                    if (slot != 0xFFFF && pOther->mpState[slot].mUnknown1 == fn_800FC0C4(pTarget)) {
                        count++;
                        if (fabsf(pOther->mMotion.mPos.mX - pTarget->mMotion.mPos.mX) > 5.5f
                            && fabsf(p->mMotion.mPos.mX - pTarget->mMotion.mPos.mX) < 5.0f) {
                            p->mpState->mUnknown1 = fn_800FC0C4(pTarget);
                            pResult = pTarget;
                            break;
                        }
                    }
                }
                if (count == 0 && fabsf(p->mMotion.mPos.mX - pTarget->mMotion.mPos.mX) < lbl_803EAE60) {
                    p->mpState->mUnknown1 = fn_800FC0C4(pTarget);
                    pResult = pTarget;
                }
            }
        }
    }
    return pResult;
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

extern "C" int fn_800FA098() {
    Point_8017886C goal;

    goal = fn_80177FE0();
    fn_801486A0();
    fn_8011E188();
    return 0;
}

extern "C" int fn_800FA0DC(Object_80039F5C *p) {
    unsigned char slot = 0;
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    Block_800F8A88 *pBlock = (Block_800F8A88 *)&p->mUnknown336;
    Object_80039F5C *pTarget;

    pBlock->mUnknown24 = slot;
    if (pRecord->mUnknown4) {
        slot = pRecord->mUnknown32[p->mIdBytes[1]];
        if (slot == 0xFF) {
            slot = 0xFD;
        }
    } else {
        slot = p->mpState->mUnknown1;
    }
    if (slot == 0xFE) {
        Message_800F01CC message;

        memset(&message, 0, 4);
        message.mId = 85;
        message.mUnknown1[0] = 48;
        fn_800F00D4(0, p->mpState, &message, p);
        return 1;
    }
    if (slot == 0xFD) {
        Message_800F01CC message;

        memset(&message, 0, 4);
        message.mId = 2;
        fn_800F00D4(0, p->mpState, &message, p);
        return 1;
    }
    if (slot) {
        pTarget = PlyrGet(fn_80178308(), pRecord->mUnknown8[slot - 1]);
        p->mpState->mUnknown1 = slot;
        if (pTarget->mUnknown2914 == 3 && p->mpState->mUnknown3[0] == 0) {
            float distance = fabsf(p->mMotion.mPos.mX - pTarget->mMotion.mPos.mX);

            if (distance < 3.5f) {
                p->mpState->mUnknown3[0] = 2;
            } else if (distance < 5.5f) {
                p->mpState->mUnknown3[0] = 1;
            }
        }
    } else {
        pTarget = 0;
    }
    fn_8009BD2C(pTarget, &pBlock->mRef);
    pBlock->mUnknown22 = p->mpState->mUnknown3[0];
    pBlock->mUnknown23 = 1;
    pBlock->mUnknown25 = p->mpState->mUnknown2 & 2;
    pBlock->mUnknown20 = 0;
    pBlock->mUnknown4 = p->mMotion.mFacing;
    pBlock->mUnknown8 = p->mMotion.mFacing;
    pBlock->mUnknown12 = 0.0f;
    pBlock->mUnknown26 = 7;
    pBlock->mUnknown27 = fn_802372EC(0, 20) + 20;
    pBlock->mUnknown21 = 0;
    pBlock->mUnknown16 = 0;
    if (fn_8011F4E0()->mUnknown0 < 0) {
        pBlock->mUnknown16 = 1;
    }
    if (p->mFlags & 0x4000) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.0f;
    }
    return 0;
}

extern "C" int fn_800FA300(Object_80039F5C *p)
{
    Block_800FA300 *pBlock;
    Object_80039F5C *pTarget;
    Object_80039F5C *pOther;
    Message_800F01CC message;
    int active = 0;

    fn_8010A2DC(p, 0, -1);
    pBlock = (Block_800FA300 *)&p->mUnknown336;
    if (--pBlock->mUnknown20 & 0x80) {
        int range = 255 - p->mRatings[8];
        int random;

        if (range < 0) {
            range = 0;
        }
        random = fn_802372EC(0, (unsigned int)range >> 5);
        active = 1;
        pBlock->mUnknown20 = pBlock->mUnknown20 + random + fn_800AC2C0(p->mIdBytes[2]);
    }
    pTarget = fn_8009BCE8(&pBlock->mRef);
    if (p->mUnknown560.mFlags.mBytes[0] != 0) {
        active = 1;
    }
    if (pTarget) {
        if (fn_800FA098(p, pTarget) && fn_80125510(p, (Message_800F01CC *)pTarget)) {
            return 0;
        }
        if (pTarget->mpState->mId != 20) {
            pBlock->mUnknown21 = 0;
        } else if (active && pBlock->mUnknown21 == 0) {
            pBlock->mUnknown21 = fn_8009FD7C(p, pTarget);
        }
    } else {
        pBlock->mUnknown21 = 0;
    }
    if (!(p->mFlags & 0x4000)) {
        if (active) {
            if (!pTarget) {
                Point_8017886C ball;
                Point_8017886C goal;
                Point_8017886C *pBall;
                Point_8017886C *pGoal;

                ball = fn_80177FE0();
                if (p->mMotion.mPos.mX > ball.mX) {
                    goal.mX = ball.mX + 4.0f;
                } else {
                    goal.mX = ball.mX - 4.0f;
                }
                pBall = &ball;
                pGoal = &goal;
                pGoal->mY = pBall->mY + 20.0f;
                fn_80227690(pGoal, pGoal, &p->mMotion.mPos);
                if (pGoal->mY < 0.0f) {
                    pGoal->mY = 2.0f;
                }
                if (p->mMotion.mPos.mY > fn_80178A44() - 2.0f) {
                    pGoal->mY = 0.0f;
                }
                pBlock->mUnknown8 = fn_801CFE40(pGoal->mY, goal.mX);
                pBlock->mUnknown4 = 0xC00000;
                pTarget = fn_800F9688(p);
                if (pTarget) {
                    pBlock->mUnknown23 = 1;
                    pBlock->mUnknown12 = 0.7f;
                    fn_8009BD2C(pTarget, &pBlock->mRef);
                } else {
                    pTarget = fn_800F9480(p);
                    if (pTarget) {
                        if (pTarget->mMotion.mPos.mY > p->mMotion.mPos.mY - 5.0f) {
                            pBlock->mUnknown12 = 1.0f;
                        } else {
                            pBlock->mUnknown12 = 0.7f;
                        }
                        pBlock->mUnknown23 = 1;
                        if (pTarget->mMotion.mPos.mY > pBall->mY + 7.0f) {
                            fn_8009BD2C(pTarget, &pBlock->mRef);
                        } else {
                            pTarget = 0;
                        }
                    } else {
                        pBlock->mUnknown12 = 0.7f;
                    }
                }
            } else if (fn_8011F4E0()->mUnknown0 < 0 && !(p->mFlags & 0x20000)
                       && (fn_8011F1CC() || fn_8011F1A4())) {
                if (pTarget->mUnknown1032 == 0) {
                    int id = fn_800F06F4(0, pTarget->mpState, 1, 0xFFFF);

                    if (id == 0xFFFF && fn_800F06F4(0, pTarget->mpState, 47, 0xFFFF) == id) {
                        unsigned char state = pTarget->mpState->mId;

                        if (state != 32 && state != 11 && state != 16) {
                            goto done;
                        }
                        if (fn_800F06F4(0, pTarget->mpState, 21, 0xFFFF) != 0xFFFF) {
                            goto done;
                        }
                    }
                }
                if (fn_8011E9D8(pTarget->mpState) && pBlock->mUnknown27 != 0) {
                    goto done;
                }
                switch (p->mUnknown2914) {
                case 14:
                    pOther = fn_800F9E3C(p, 0);
                    if (pOther) {
                        pTarget = pOther;
                        fn_8009BD2C(pTarget, &pBlock->mRef);
                        break;
                    }
                    p->mpState->mUnknown1 = fn_800FC0C4(pTarget);
                    memset(&message, 0, 4);
                    message.mId = 85;
                    message.mUnknown1[0] = 48;
                    fn_800F00D4(0, p->mpState, &message, p);
                    return 0;
                case 13:
                case 15:
                    pOther = fn_800F9E3C(p, 0);
                    if (pOther) {
                        pTarget = pOther;
                        fn_8009BD2C(pTarget, &pBlock->mRef);
                        break;
                    }
                    if ((unsigned int)(fn_8009F6B4() - 2) <= 1 || PlayTrackGetResult5Rate() > 0.25f) {
                        p->mpState->mUnknown1 = fn_800FC0C4(pTarget);
                        memset(&message, 0, 4);
                        message.mId = 85;
                        message.mUnknown1[0] = 48;
                        fn_800F00D4(0, p->mpState, &message, p);
                        return 0;
                    }
                    p->mpState->mUnknown1 = fn_800FC0C4(pTarget);
                    memset(&message, 0, 4);
                    message.mId = 2;
                    fn_800F00D4(0, p->mpState, &message, p);
                    return 0;
                case 16:
                    fn_8009BD2C(0, &pBlock->mRef);
                    pBlock->mUnknown23 = 0;
                    break;
                case 17:
                case 18: {
                    int alone;
                    unsigned char i;
                    unsigned int count;

                    pOther = fn_800F9E3C(p, 1);
                    if (pOther) {
                        pTarget = pOther;
                        fn_8009BD2C(pTarget, &pBlock->mRef);
                        break;
                    }
                    alone = 1;
                    count = fn_80178D18(fn_80178320());
                    for (i = 0; i < count; i++) {
                        Object_80039F5C *pMate = PlyrGet(fn_80178320(), i);

                        if (pMate != p) {
                            int blocking = 0;

                            if (pMate->mUnknown2914 <= 18) {
                                blocking = pMate->mUnknown2914 >= 17;
                            }

                            if (blocking) {
                                int id = fn_800F06F4(0, pMate->mpState, 2, 0xFFFF);

                                if (id != 0xFFFF || fn_800F06F4(0, pMate->mpState, 30, 0xFFFF) != id) {
                                    blocking = 0;
                                }
                            }
                            if (blocking) {
                                alone = 0;
                                break;
                            }
                        }
                    }
                    p->mpState->mUnknown1 = fn_800FC0C4(pTarget);
                    memset(&message, 0, 4);
                    message.mId = 40;
                    if (alone) {
                        message.mUnknown1[0] = 0;
                    } else if (p->mMotion.mPos.mX < 0.0f) {
                        message.mUnknown1[0] = 1;
                    } else {
                        message.mUnknown1[0] = 2;
                    }
                    fn_800F00D4(0, p->mpState, &message, p);
                    return 0;
                }
                }
            }
        done:
            if (pBlock->mUnknown23 == 1) {
                pBlock->mUnknown23 = lbl_802DAB38[pBlock->mUnknown22](p);
                if (pBlock->mUnknown23 == 0) {
                    pBlock->mUnknown20 = 0;
                }
            } else if (pTarget) {
                fn_800F8588(p, pTarget);
                fn_800F8A88(p, pTarget);
            }
        }
        if (pBlock->mUnknown12 != 0.0f) {
            Point_8017886C direction;
            Point_8017886C *pDirection = &direction;

            fn_80227538(pDirection, pBlock->mUnknown8, 1.0f);
            pBlock->mUnknown8 = fn_800F69C0(pBlock->mUnknown8, p);
            if (p->mMotion.mPos.mX > fn_80178A08() - 2.0f && direction.mX > 0.0f) {
                direction.mX = 0.0f;
            } else if (p->mMotion.mPos.mX < 2.0f - fn_80178A08() && direction.mX < 0.0f) {
                direction.mX = 0.0f;
            }
            pBlock->mUnknown8 = fn_801CFE40(pDirection->mY, direction.mX);
        }
    }
    if (fn_800A5C04(p, pBlock->mUnknown8, pBlock->mUnknown4)) {
        return 0;
    }
    if (p->mFlags & 0x4000) {
        return 0;
    }
    fn_8011F4E0();
    pBlock->mUnknown16++;
    if (active) {
        int count;

        fn_800FA014(p, (int *)pBlock);
        count = fn_8009E180(p);
        if (count > 2) {
            if (count == 4) {
                if (fn_8009F258(p)) {
                    memset(&message, 0, 4);
                    message.mId = 24;
                    message.mUnknown1[0] = 2;
                    fn_800F053C(0, p->mpState, &message, p);
                    return 1;
                }
            } else {
                unsigned short chance = p->mRatings[8];
                Vector_80039F5C pos;

                if (fn_800B65A0(p->mIdBytes[2]) == 255) {
                    chance = chance + (int)(chance * PlayTrackGetPlayIdRate());
                }
                BallGetPosition(BallGetCurrent(), &pos);
                if ((unsigned int)fn_802372EC(0, 255) < chance || pos.mY > fn_80177FE0().mY + 3.0f) {
                    memset(&message, 0, 4);
                    message.mId = 2;
                    fn_800F053C(0, p->mpState, &message, p);
                    return 1;
                }
            }
        }
    }
    if (pTarget && pTarget->mUnknown528.mUnknown15 == 1 && pBlock->mUnknown12 > 0.72f) {
        pBlock->mUnknown24 = 1;
    }
    if (pBlock->mUnknown12 != 0.0f) {
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown8;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
    }
    p->mUnknown512.mUnknown15 = pBlock->mUnknown24;
    if (pBlock->mUnknown4 == pBlock->mUnknown8 && p->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.14f
        && MathAngleDiff(p->mMotion.mUnknown32, pBlock->mUnknown4) > 0x2E38E3
        && MathAngleDiff(p->mMotion.mFacing, 0xC00000) < 0x2AAAAA) {
        pBlock->mUnknown12 = 0.0f;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown8;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown4;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
        pBlock->mUnknown20 = 2;
    }
    return 0;
}

extern "C" void fn_800FAD10(unsigned char *p) {
    unsigned char value = p[1];
    if (value != 0) {
        value = 6 - value;
    }
    p[1] = value;
}

extern "C" void fn_800FAD2C(void) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char i = 0;
    int team;
    int mode;
    int swapped;

    pRecord->mUnknown0 = 1;
    pRecord->mUnknown2 = 150;
    team = fn_80178308();
    PlayBookGetPlay(team);
    mode = fn_800AD9B4();
    for (; i <= 2; i++) {
        pRecord->mUnknown8[i] = ((Block_800FAD2C *)fn_8011F4EC())->mUnknown409[i];
        if (mode == 2 && PlyrGet(fn_80178308(), pRecord->mUnknown8[i])->mUnknown2914 == 0) {
            pRecord->mUnknown8[i] = fn_80164B78();
        }
    }
    do {
        swapped = 0;
        for (i = 0; i <= 1; i++) {
            float x0 = PlyrGet(team, pRecord->mUnknown8[i])->mMotion.mPos.mX;
            float x1 = PlyrGet(team, pRecord->mUnknown8[i + 1])->mMotion.mPos.mX;
            float y0 = PlyrGet(team, pRecord->mUnknown8[i])->mMotion.mPos.mY;
            float y1 = PlyrGet(team, pRecord->mUnknown8[i + 1])->mMotion.mPos.mY;

            if (x0 < x1 + 0.5f && (fabsf(x1 - x0) > 0.5f || y0 < y1)) {
                unsigned char slot = pRecord->mUnknown8[i];

                swapped = 1;
                pRecord->mUnknown8[i] = pRecord->mUnknown8[i + 1];
                pRecord->mUnknown8[i + 1] = slot;
            }
        }
    } while (swapped == 1);
    for (i = 0; i <= 2; i++) {
        pRecord->mUnknown12[i] = pRecord->mUnknown8[i];
    }
}

extern "C" void fn_800FAECC(void) {
    unsigned char taken[7];
    unsigned char counts[3] = {0};
    Entry_800FAECC entries[7];
    int useAlt = 0;
    int allowSingle = 1;
    Record_8011F4E0 *pRecord;
    int forward;
    int team;
    PlayBookPlay_t *pInfoTeam;
    PlayBookFormation_t *pTeam;
    unsigned char count;
    unsigned int n;

    pRecord = fn_8011F4E0();
    forward = fn_800F9CB4();
    pRecord->mUnknown4 = 1;
    if (pRecord->mUnknown5 == 0) {
        fn_800FBB70();
    }
    for (unsigned char i = 0; i < 7; i++) {
        pRecord->mUnknown32[i] = 0xFF;
        taken[i] = 0;
    }
    pRecord->mUnknown6 = 0;
    team = fn_80178320();
    pInfoTeam = PlayBookGetPlay(team);
    pTeam = PlayBookGetFormation(team);
    fn_8009F6B4();
    for (unsigned char i = 0; i < 8; i++) {
        pRecord->mUnknown40[i] = 0xFF;
    }
    if (pTeam->mUnknown8.mUnknownF == 1 && (pTeam->mUnknown8.mUnknown14 & 1) && (pInfoTeam->mUnknown18 & 1)) {
        useAlt = 1;
    }
    count = 0;
    n = fn_80178D18(team);
    for (unsigned char i = 0; i < n; i++) {
        Object_80039F5C *p = PlyrGet(team, i);
        unsigned short index;
        Message_800F01CC *pRoutes;
        int slot;

        if (!useAlt) {
            index = p->mIdBytes[1];
        } else {
            index = PlaySetGetEntry(pTeam, p->mIdBytes[1], 0)->mUnknownB;
        }
        pRoutes = (Message_800F01CC *)fn_800AEE20(PlyrGet(team, index));
        if (!pRoutes) {
            pRoutes = (Message_800F01CC *)fn_80164EC8(pInfoTeam, team, index);
        }
        slot = fn_800F06F4(0, pRoutes, 0x16, 0);
        if (slot != 0xFFFF) {
            unsigned char value = pRoutes[slot].mUnknown1[0];
            if (value == 0) {
                pRecord->mUnknown32[p->mIdBytes[1]] = value;
            } else {
                counts[value - 1]++;
            }
            entries[count].mpPlayer = p;
            entries[count].mKind = fn_800F986C(p);
            entries[count].mX = AssignGetFormationPos(p).mX;
            count++;
        } else {
            pRecord->mUnknown16[p->mIdBytes[1]] = 0xFF;
        }
    }
    for (unsigned char i = 0; i < count; i++) {
        unsigned char j;
        for (j = i + 1; j < count; j++) {
            if (entries[j].mX > entries[i].mX) {
                Entry_800FAECC t = entries[j];
                entries[j] = entries[i];
                entries[i] = t;
            }
        }
    }
    for (unsigned int i = 0; i < 3; i++) {
        Object_80039F5C *pReceiver = fn_800F93D0(PlyrGet(fn_80178308(), pRecord->mUnknown8[i]));
        if (pReceiver) {
            pRecord->mUnknown32[pReceiver->mIdBytes[1]] = i + 1;
            taken[pReceiver->mIdBytes[1]] = 1;
        }
    }
    unsigned char i;
    int next;

    for (i = 0; i < count; i = next) {
        unsigned char k;

        if (forward) {
            k = i;
            next = k + 1;
        } else {
            next = i + 1;
            k = count - next;
        }
        if (taken[entries[k].mpPlayer->mIdBytes[1]] == 0) {
            unsigned char tries = 0;
            if (entries[k].mKind > 1 || allowSingle) {
                Object_80039F5C *pSlot = 0;
                int done = 0;
                while (!done && tries <= 2) {
                    pSlot = fn_800F9BD8(forward, pSlot);
                    tries++;
                    if (!pSlot) {
                        done = 1;
                    } else if (fn_800F9CAC(entries, k, count, pSlot)) {
                        pRecord->mUnknown32[entries[k].mpPlayer->mIdBytes[1]] = fn_800FC0C4(pSlot);
                        taken[entries[k].mpPlayer->mIdBytes[1]] = 1;
                        done = 1;
                    }
                }
            }
        }
    }
}

extern "C" void fn_800FB314(void) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char count = 0;
    Object_80039F5C *pBlocked = 0;
    signed char blocked = -2;
    unsigned char order[3];
    unsigned char i;
    int team;

    if (!(pRecord->mUnknown0 & 0x8000)) {
        pRecord->mUnknown0--;
        if (pRecord->mUnknown0 & 0x8000) {
            unsigned int n;
            int swapped;
            int total;

            fn_80178320();
            team = fn_80178308();
            n = fn_80178D18(fn_80178320());
            for (i = 0; i < 3; i++) {
                if (!(PlyrGet(fn_80178308(), pRecord->mUnknown8[i])->mFlags & 0x20000000)) {
                    order[count++] = pRecord->mUnknown8[i];
                } else {
                    unsigned char j;

                    blocked = i + 1;
                    for (j = 0; j < n; j++) {
                        if (pRecord->mUnknown32[j] == blocked) {
                            pBlocked = PlyrGet(fn_80178320(), j);
                        }
                    }
                }
            }
            do {
                unsigned char last = count - 1;

                swapped = 0;
                for (i = 0; i <= last - 1; i++) {
                    Vector_80039F5C posA;
                    Vector_80039F5C posB;
                    Object_80039F5C *pA = PlyrGet(team, order[i]);
                    Object_80039F5C *pB = PlyrGet(team, order[i + 1]);
                    float xA;
                    float xB;

                    fn_800FBF74(pA, (Object_80039F5C *)pA->mpState);
                    fn_800FBF74(pB, (Object_80039F5C *)pB->mpState);
                    xA = pA->mMotion.mPos.mX;
                    xB = pB->mMotion.mPos.mX;
                    if (!BallGetCurrentHolder()) {
                        Point_8017886C goal = fn_80177FE0();
                    }
                    int time = 0;
                    int angle;
                    int routeA = fn_800F06F4(0, pA->mpState, 0x15, 0xFFFF);
                    int routeB = fn_800F06F4(0, pB->mpState, 0x15, 0xFFFF);
                    if (routeA != 0 && routeA != 0xFFFF && routeB != 0 && routeB != 0xFFFF) {
                        float a;
                        float b;

                        fn_80104328(pA, (unsigned char)(routeA - 1), &time, &posA, &angle);
                        fn_80104328(pB, (unsigned char)(routeB - 1), &time, &posB, &angle);
                        a = posA.mX < xA - 1.5f ? xA - 1.5f : (posA.mX > xA + 1.5f ? xA + 1.5f : posA.mX);
                        b = posB.mX < xB - 1.5f ? xB - 1.5f : (posB.mX > xB + 1.5f ? xB + 1.5f : posB.mX);
                        if (a < b) {
                            unsigned char t = order[i];
                            swapped = 1;
                            order[i] = order[i + 1];
                            order[i + 1] = t;
                        }
                    }
                }
            } while (swapped == 1);
            total = fn_80178D18(fn_80178320());
            for (i = 0; i < total; i++) {
                Object_80039F5C *p = PlyrGet(fn_80178320(), i);
                unsigned short route = fn_800F06F4(0, p->mpState, 0x16, 0xFFFF);

                if (route != 0xFFFF && pRecord->mUnknown32[p->mIdBytes[1]] != blocked) {
                    unsigned char ahead = fn_800FC128(p);
                    unsigned char behind = fn_800FC1DC(p);
                    unsigned char slot;
                    unsigned char j;

                    if (pBlocked) {
                        if (pBlocked->mMotion.mPos.mX > p->mMotion.mPos.mX) {
                            ahead--;
                        } else {
                            behind--;
                        }
                    }
                    if (ahead < behind || (ahead <= behind && p->mMotion.mPos.mX > fn_80177FE0().mX)) {
                        slot = ahead;
                    } else {
                        slot = count - behind - 1;
                    }
                    for (j = 0; j < 3; j++) {
                        if (pRecord->mUnknown8[j] == order[slot]) {
                            slot = j + 1;
                            break;
                        }
                    }
                    pRecord->mUnknown32[(p->mId >> 16) & 0xFF] = slot;
                    if (route == 0) {
                        fn_8009BD2C(PlyrGet(team, pRecord->mUnknown8[slot - 1]), &p->mUnknown336);
                    }
                }
            }
        }
    }
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

                    Object_80039F5C *pA = PlyrGet(team, pRecord->mUnknown12[i]);
                    Object_80039F5C *pB = PlyrGet(team, pRecord->mUnknown12[i + 1]);
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
        pos = AssignGetFormationPos(p);
        ahead = 1;
        behind = 1;
        n = fn_80178D18(fn_80178320());
        for (i = 0; i < n; i++) {
            Object_80039F5C *pOther = PlyrGet(fn_80178320(), i);
            if (pOther != p && fn_8009FE24(pOther)) {
                Point_8017886C otherPos = AssignGetFormationPos(pOther);
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
                    pResult = PlyrGet(fn_80178308(), pRecord->mUnknown24[i]);
                    break;
                }
            }
        } else {
            for (i = 7; i >= 0; i--) {
                if (pRecord->mUnknown24[i] != 255) {
                    behind--;
                }
                if (behind == 0) {
                    pResult = PlyrGet(fn_80178308(), pRecord->mUnknown24[i]);
                    break;
                }
            }
        }
    }
    return pResult;
}

extern "C" Object_80039F5C *fn_800FB9D4(Object_80039F5C *p)
{
    Object_80039F5C *pResult = 0;
    float best = 1000.0f;

    if (p) {
        unsigned int count = fn_80178D18(fn_80178320());
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *pOther = PlyrGet(fn_80178320(), i);

            if (pOther->mpState->mId == 22) {
                Object_80039F5C *pTarget = fn_8009BCE8(&pOther->mUnknown336);

                if (pTarget && pTarget == p) {
                    Point_8017886C delta;
                    float distance;

                    fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
                    distance = fn_802270A4(&delta);
                    if (distance < best) {
                        pResult = pOther;
                        best = distance;
                    }
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
        Object_80039F5C *p = PlyrGet(fn_80178320(), i);
        if (p->mpState->mId == 42) {
            Block_800FBAA8 *pBlock = (Block_800FBAA8 *)&p->mUnknown336;
            pBlock->mUnknown36 = 0;
        }
    }
}

extern "C" void fn_800FBB70(void) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    unsigned char i = 0;
    Object_80039F5C *list[4];
    Point_8017886C ball;
    Object_80039F5C **pp;
    int mode;
    unsigned int n;
    float x;
    float high1;
    float high2;
    float high3;
    float low1;
    float low2;
    float low3;
    Object_80039F5C *pHigh1;
    Object_80039F5C *pHigh2;
    Object_80039F5C *pHigh3;
    Object_80039F5C *pSlot3;
    Object_80039F5C *pSlot4;
    Object_80039F5C *pLow3;
    Object_80039F5C *pLow2;
    Object_80039F5C *pLow1;

    ball = fn_80177FE0();
    for (; i < 4; i++) {
        list[i] = 0;
    }
    mode = fn_800AD9B4();
    i = 0;
    pp = list;
    n = fn_80178D18(fn_80178308());
    for (; i < n; i++) {
        int state;

        *pp = PlyrGet(fn_80178308(), i);
        state = (*pp)->mUnknown2914;
        if (fn_8011F1CC() && mode != 2) {
            PlayBookFormation_t *pTeam = PlayBookGetFormation(fn_80178308());
            void *pInfo = fn_800AEE20(*pp);

            if (!pInfo) {
                if (pTeam->mUnknown8.mUnknownF == 0) {
                    pInfo = fn_80164EC8(PlayBookGetPlay((*pp)->mIdBytes[2]), ((*pp)->mId >> 8) & 0xFF, ((*pp)->mId >> 16) & 0xFF);
                } else {
                    unsigned char index = PlaySetGetEntry(pTeam, (*pp)->mIdBytes[1], 0)->mUnknownB;
                    pInfo = fn_80164EC8(PlayBookGetPlay((*pp)->mIdBytes[2]), (*pp)->mIdBytes[2], index);
                }
            }
            if (fn_800F06F4(0, pInfo, 21, 0xFFFF) != 0xFFFF) {
                pp++;
            }
        } else {
            switch (state) {
            case 1:
            case 2:
            case 3:
            case 4:
                pp++;
                break;
            }
        }
        *pp = 0;
    }
    pp = list;
    x = ball.mX;
    pHigh1 = 0;
    pHigh2 = 0;
    pHigh3 = 0;
    low1 = x;
    low2 = low1;
    pLow1 = 0;
    high1 = x - 0.01f;
    pLow2 = 0;
    high2 = high1;
    pLow3 = 0;
    high3 = high2;
    pSlot3 = 0;
    low3 = low2;
    pSlot4 = 0;
    while (*pp) {
        x = AssignGetFormationPos(*pp).mX;

        if (x > high1) {
            if (high1 > high2) {
                if (high2 > high3) {
                    high3 = high2;
                    pHigh3 = pHigh2;
                }
                high2 = high1;
                pHigh2 = pHigh1;
            }
            high1 = x;
            pHigh1 = *pp;
        } else if (x > high2) {
            if (high2 > high3) {
                high3 = high2;
                pHigh3 = pHigh2;
            }
            pHigh2 = *pp;
            high2 = x;
        } else if (x > high3) {
            pHigh3 = *pp;
            high3 = x;
        }
        if (x < low1) {
            if (x < low2) {
                if (low2 < low3) {
                    low3 = low2;
                    pLow3 = pLow2;
                }
                low2 = low1;
                pLow2 = pLow1;
            }
            low1 = x;
            pLow1 = *pp;
        } else if (x < low2) {
            if (low2 < low3) {
                low3 = low2;
                pLow3 = pLow2;
            }
            low2 = x;
            pLow2 = *pp;
        } else if (x < low3) {
            pLow3 = *pp;
            low3 = x;
        }
        pp++;
    }
    pRecord->mUnknown24[0] = pHigh1 ? pHigh1->mIdBytes[1] : 255;
    pRecord->mUnknown24[1] = pHigh2 ? pHigh2->mIdBytes[1] : 255;
    pRecord->mUnknown24[2] = pHigh3 ? pHigh3->mIdBytes[1] : 255;
    pRecord->mUnknown24[3] = pSlot3 ? pSlot3->mIdBytes[1] : 255;
    pRecord->mUnknown24[4] = pSlot4 ? pSlot4->mIdBytes[1] : 255;
    pRecord->mUnknown24[5] = pLow3 ? pLow3->mIdBytes[1] : 255;
    pRecord->mUnknown24[6] = pLow2 ? pLow2->mIdBytes[1] : 255;
    pRecord->mUnknown24[7] = pLow1 ? pLow1->mIdBytes[1] : 255;
    pRecord->mUnknown5 = 1;
}

extern "C" Object_80039F5C *fn_800FBF74(Object_80039F5C *pTarget, Object_80039F5C *pOther) {
    Record_8011F4E0 *pRecord = fn_8011F4E0();
    Object_80039F5C *pResult = 0;
    unsigned short i;
    unsigned int n = fn_80178D18(fn_80178320());

    for (i = 0; i < n; i++) {
        Object_80039F5C *p = PlyrGet(fn_80178320(), i);
        unsigned short kind = fn_800FC014(p, pOther);
        if (kind >= 1 && kind <= 5 && PlyrGet(fn_80178308(), pRecord->mUnknown8[kind - 1]) == pTarget) {
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
    return PlyrGet(fn_80178308(), pRecord->mUnknown8[slot - 1]);
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
        Object_80039F5C *pOther = PlyrGet(fn_80178320(), i);
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
        Object_80039F5C *pOther = PlyrGet(fn_80178320(), i);
        if (fn_800F06F4(0, pOther->mpState, 22, 0xFFFF) != 0xFFFF && pOther != p
            && pOther->mMotion.mPos.mX < p->mMotion.mPos.mX) {
            count++;
        }
    }
    return count;
}

extern "C" void fn_800FC290(Object_80039F5C *p, Block_800FCC24 *pBlock, Point_8017886C target) {
    Object_800B26B0 *pMotion = &p->mMotion;

    pBlock->mUnknown32 = 1;
    pBlock->mUnknown4[1].mX = target.mX;
    pBlock->mUnknown4[1].mY = target.mY;
    if (pMotion->mUnknown28 < gPlyrMoveFwdSpeed * 0.07f) {
        if (fn_80177FE0().mY - pMotion->mPos.mY > 1.5f) {
            if (fn_80177FE0().mY - target.mY > 1.5f) {
                if (target.mY - pMotion->mPos.mY > 0.05f) {
                    float distance;
                    int team = p->mIdBytes[2];

                    if (fn_801245DC(p, team, 0, fn_80178D18(team), 0x71C71, &distance, 0) && distance < 2.5f) {
                        if (target.mX > p->mMotion.mPos.mX) {
                            pBlock->mUnknown4[0].mX = p->mMotion.mPos.mX + 1.0f;
                        } else {
                            pBlock->mUnknown4[0].mX = p->mMotion.mPos.mX - 1.0f;
                        }
                    } else {
                        pBlock->mUnknown4[0].mX = pMotion->mPos.mX;
                    }
                    pBlock->mUnknown32 = 0;
                    pBlock->mUnknown4[0].mY = target.mY;
                }
            }
        } else if ((pBlock->mUnknown34 & 2) && (p->mFlags & 0x40000)) {
            if (fabsf(pMotion->mPos.mY - target.mY) < 0.5f) {
                pBlock->mUnknown32 = 0;
                pBlock->mUnknown4[0].mX = target.mX;
                pBlock->mUnknown4[0].mY = target.mY - 1.0f;
            }
        } else {
            pBlock->mUnknown34 &= ~2;
        }
    } else {
        pBlock->mUnknown34 &= ~2;
    }
}

extern "C" int fn_800FC4A8(Object_80039F5C *p, Block_800FCC24 *pBlock, int mode) {
    int animation;
    float speed;

    fn_80177FE0();
    animation = fn_801BE648(p->mpUnknown792);
    speed = 1.0f;
    if (mode == 2) {
        Point_8017886C ball;
        Point_8017886C delta;

        ball = fn_80177FE0();
        delta.mX = pBlock->mUnknown4[pBlock->mUnknown32].mX - ball.mX;
        delta.mY = pBlock->mUnknown4[pBlock->mUnknown32].mY - ball.mY;
        if (fn_802270A4(&delta) >= 4.0f) {
            delta.mX = pBlock->mUnknown4[1].mX - p->mMotion.mPos.mX;
            delta.mY = pBlock->mUnknown4[1].mY - p->mMotion.mPos.mY;
            if (fn_802270A4(&delta) < 3.0f && pBlock->mUnknown38) {
                if (p->mMotion.mPos.mX > pBlock->mUnknown4[pBlock->mUnknown32].mX) {
                    p->mUnknown1008.mUnknown0 = 6;
                } else {
                    p->mUnknown1008.mUnknown0 = 3;
                }
                animation = 190;
            }
        }
    }
    if (animation != fn_801BE648(p->mpUnknown792)) {
        int index;

        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, animation, 1.0f, p);
        index = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, animation, 0);
        p->mpUnknown800[index].mUnknown2C = speed;
        return 1;
    }
    return 0;
}

extern "C" int fn_800FC648(Object_80039F5C *p, Block_800FCC24 *pBlock) {
    Object_800B26B0 *pMotion = &p->mMotion;
    Vector_80039F5C point;
    Object_80039F5C *pOther;
    int result;

    point.mX = pBlock->mUnknown4[pBlock->mUnknown32].mX;
    point.mY = pBlock->mUnknown4[pBlock->mUnknown32].mY;
    point.mZ = 0.0f;
    result = 0;
    if (!fn_801248D4(p, 0, &point, &pOther, 0.0f, 0.5f, 0, 0)) {
        Point_8017886C delta;

        fn_80227690(&delta, &pOther->mMotion.mPos, pMotion);
        if (fn_802270A4(&delta) < 2.5f) {
            int toOther = fn_801CFE40(delta.mY, delta.mX);
            int toTarget;

            fn_80227690(&delta, &pBlock->mUnknown4[pBlock->mUnknown32], pMotion);
            toTarget = fn_801CFE40(delta.mY, delta.mX);
            if (MathAngleDiff(toTarget, toOther) <= 0x11C71B) {
                if (MathAngleDiff(toTarget, 0) <= 0x3FFFFF) {
                    result = MathAngleDiff(toOther, toTarget) - 0x200000;
                } else {
                    result = 0x200000 - MathAngleDiff(toOther, toTarget);
                }
            }
        }
    }
    return result;
}

extern "C" int fn_800FC7A0(Object_80039F5C *p, Block_800FCC24 *pBlock) {
    Point_8017886C delta;
    int direction;
    float distance;
    float speed;
    int turn;
    int limit;
    int offset = 0;

    delta.mX = pBlock->mUnknown4[pBlock->mUnknown32].mX - p->mMotion.mPos.mX;
    delta.mY = pBlock->mUnknown4[pBlock->mUnknown32].mY - p->mMotion.mPos.mY;
    direction = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    distance = fn_802270A4(&delta);
    speed = pBlock->mUnknown28;
    turn = MathAngleDiff(direction, p->mMotion.mFacing);
    limit = 0x200000;
    if (pBlock->mUnknown34 & 2) {
        limit = 0x5C71C7;
    }
    if (turn > limit) {
        speed = 0.14f;
        if (distance < 1.0f) {
            speed = distance * 0.14f;
        }
        if (fabsf(fn_80177FE0().mX - p->mMotion.mPos.mX) > 7.0f) {
            if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x38E37) {
                if (turn > 0x7C71C7) {
                    if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x38E37) {
                        pBlock->mUnknown36 = 1;
                        speed = 0.14f;
                        pBlock->mUnknown24 = p->mMotion.mFacing;
                    }
                }
            }
        }
    } else if (distance < 1.0f) {
        float minimum;

        speed *= distance;
        minimum = pBlock->mUnknown36 ? 0.5f : 0.14f;
        if (speed < minimum) {
            speed = minimum;
        }
    }
    if (fn_80177FE0().mY - p->mMotion.mPos.mY < 0.5f) {
        if (speed > 0.14f) {
            speed = 0.14f;
        }
    }
    if (distance > 0.05f) {
        int facing;

        if (pBlock->mUnknown32 == 1 && !pBlock->mUnknown36) {
            offset = fn_800FC648(p, pBlock);
        }
        direction += offset;
        facing = direction;
        if (pBlock->mUnknown36) {
            facing = pBlock->mUnknown24 + offset;
        }
        if (pBlock->mUnknown39 && delta.mY > 0.0f) {
            direction = facing = fn_800FCE58(p, pBlock);
            speed = 1.0f;
        }
        p->mUnknown512.mUnknown0 = speed;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = direction;
        p->mUnknown512.mUnknown8 = facing;
        return 0;
    }
    if (pBlock->mUnknown32 == 1) {
        p->mMotion.mUnknown28 = 0.0f;
        return 1;
    }
    pBlock->mUnknown32++;
    return 0;
}

extern "C" int fn_800FCA78(Object_80039F5C *p) {
    Block_800FCC24 *pBlock = (Block_800FCC24 *)&p->mUnknown336;
    Point_8017886C ball;
    PlayBookFormation_t *pTeam;
    PlayBookPosition_t *pEntry;
    Point_8017886C *pOffset;
    Point_8017886C target;

    ball = fn_80177FE0();
    pTeam = PlayBookGetFormation(p->mIdBytes[2]);
    pEntry = &pTeam->mUnknown8.mUnknown84[0][p->mIdBytes[1]];
    pOffset = pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10;
    target.mX = pOffset->mX + ball.mX;
    target.mY = pOffset->mY + ball.mY;
    pBlock->mUnknown39 = fn_801486A0() == 2;
    if (pBlock->mUnknown39) {
        pBlock->mUnknown38 = target.mY > p->mMotion.mPos.mY;
    } else if (fabsf(target.mX - p->mMotion.mPos.mX) < 4.0f) {
        pBlock->mUnknown38 = 0;
    } else {
        pBlock->mUnknown38 = 1;
    }
    pBlock->mUnknown20 = pTeam->mUnknown8.mUnknownF == 1 ? pEntry->mUnknown24 : pEntry->mUnknown20;
    pBlock->mUnknown33 = pTeam->mUnknown8.mUnknownF == 1 ? pEntry->mUnknownA : pEntry->mUnknown9;
    pBlock->mUnknown34 = pEntry->mUnknownE;
    pBlock->mUnknown28 = 0.72f;
    pBlock->mUnknown0 = 1;
    pBlock->mUnknown36 = 0;
    fn_800FC290(p, pBlock, target);
    p->mUnknown512.mUnknown14 = 0;
    AudmonEventPostId(120, &p->mMotion.mPos, p->mId, 0, 0, 0);
    p->mFlags &= ~0x40000;
    p->mFlags |= 0x10;
    p->mFlags |= 0x20000000;
    return 0;
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
        if (MathAngleDiff(p->mMotion.mFacing, pBlock->mUnknown20) > 0x200000) {
            memset(&message, 0, 4);
            message.mId = 6;
            message.mUnknown1[0] = pBlock->mUnknown20 >> 16;
            message.mUnknown1[1] = 1;
            fn_800F03D8(0, p->mpState, &message, p);
            memset(&message, 0, 4);
            message.mId = 9;
            message.mUnknown1[0] = pBlock->mUnknown33;
            message.mUnknown1[1] = 0;
            message.mUnknown1[2] = 255;
            fn_800F03D8(0, p->mpState, &message, p);
        } else {
            memset(&message, 0, 4);
            message.mId = 87;
            message.mUnknown1[0] = pBlock->mUnknown33;
            message.mUnknown1[1] = pBlock->mUnknown20 >> 16;
            fn_800F03D8(0, p->mpState, &message, p);
        }
        fn_8016DF34(p);
    }
    return result;
}

extern "C" int fn_800FCE58(Object_80039F5C *p, Block_800FCC24 *pBlock) {
    Point_8017886C ball = fn_80177FE0();
    Point_8017886C target;
    float t;
    int side;
    int up = 0x400000;

    target.mX = pBlock->mUnknown4[pBlock->mUnknown32].mX;
    target.mY = pBlock->mUnknown4[pBlock->mUnknown32].mY;
    t = (p->mMotion.mPos.mY - (ball.mY - 4.5f)) / 3.0f;
    side = p->mMotion.mPos.mX > target.mX ? 0x800000 : 0;
    t = t < 0.0f ? 0.0f : t > 1.0f ? 1.0f : t;
    return ((int)(t * (side * 2.1457672e-05f) * 46603.38f) + (int)((1.0f - t) * (up * 2.1457672e-05f) * 46603.38f)) & 0xFFFFFF;
}

extern "C" int fn_800FCFC0(Object_80039F5C *p) {
    int result = 0;

    if (p->mIdBytes[3] == 1 && p->mpState[1].mId == 18 && fn_8011F1CC()) {
        int team = fn_80178320();
        unsigned char i = 0;
        Vector_80039F5C *pPos = &p->mMotion.mPos;
        Point_8017886C ball;
        float limit;

        ball = fn_80177FE0();
        limit = ball.mY - 1.0f;
        for (; i < 7; i++) {
            Object_80039F5C *pOther = PlyrGet(team, i);
            if (pOther && pOther->mMotion.mPos.mY < limit
                && fabsf(pOther->mMotion.mPos.mX - ball.mX) < 6.0f) {
                if (pOther->mUnknown1032 == 0) {
                    result = 1;
                } else if (pOther->mUnknown1032 == 8) {
                    Point_8017886C toCarrier;
                    Point_8017886C toOther;
                    int angle;

                    fn_80227690(&toCarrier, &fn_8009BCE8(&pOther->mUnknown1036)->mMotion.mPos, pPos);
                    fn_80227690(&toOther, &pOther->mMotion.mPos, pPos);
                    angle = fn_801CFE40(toOther.mY, toOther.mX);
                    if (MathAngleDiff(angle, fn_801CFE40(toCarrier.mY, toCarrier.mX)) > 0x400000
                        || fn_8022710C(&toOther) < fn_8022710C(&toCarrier)) {
                        if (fn_80124714(p, pOther, 0) == 1) {
                            result = 1;
                        }
                    }
                }
            }
        }
    }
    return result;
}

extern "C" void fn_800FD178(Object_80039F5C *p, Block_800FD650 *pBlock) {
    float limit = fn_80178A08() - 1.0f;
    float x = fabsf(p->mMotion.mPos.mX);
    int clamped = 0;

    if (x > fn_80178A08() - 1.0f - 0.5f) {
        limit = fn_80178A08() - 1.0f - 0.5f;
    }
    pBlock->mUnknown4 = pBlock->mUnknown4 > fn_80178A44() - 1.0f ? fn_80178A44() - 1.0f : pBlock->mUnknown4;
    if (pBlock->mUnknown0 < -limit) {
        pBlock->mUnknown0 = -limit;
        clamped = 1;
    }
    if (pBlock->mUnknown0 > limit) {
        pBlock->mUnknown0 = limit;
        clamped = 1;
    }
    if (clamped) {
        Point_8017886C point;
        Point_8017886C delta;

        point.mX = pBlock->mUnknown0;
        point.mY = pBlock->mUnknown4;
        fn_80227690(&delta, &point, &p->mMotion.mPos);
        pBlock->mUnknown16 = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    }
}

extern "C" int fn_800FD2AC(Object_80039F5C *p) {
    Vector_80039F5C *pPos = &p->mMotion.mPos;
    Block_800FD650 *pBlock = (Block_800FD650 *)&p->mUnknown336;
    Point_8017886C offset;

    pBlock->mUnknown16 = (p->mpState->mUnknown2 << 17) & 0xFFFFFF;
    if (fn_801784E8()) {
        pBlock->mUnknown16 = (pBlock->mUnknown16 + 0x800000) & 0xFFFFFF;
    }
    pBlock->mUnknown8 = (p->mpState->mUnknown1 >> 3) + (p->mpState->mUnknown1 & 7) / 7.0f;
    pBlock->mUnknown12 = p->mpState->mUnknown3[0] / 255.0f;
    fn_80227538(&offset, pBlock->mUnknown16, pBlock->mUnknown8);
    pBlock->mUnknown0 = pPos->mX + offset.mX;
    pBlock->mUnknown4 = pPos->mY + offset.mY;
    if ((unsigned int)(fn_800AD9B4() - 2) <= 1) {
        fn_800FD178(p, pBlock);
    }
    return 0;
}

extern "C" int fn_800FD3F0(Object_80039F5C *p) {
    if (p) {
        fn_800FD724(p);
    }
    return 1;
}

extern "C" int fn_800FD41C(Object_80039F5C *p) {
    Block_800FD650 *pBlock;
    Vector_80039F5C *pPos;
    int result;

    fn_8010A2DC(p, 0, -1);
    pBlock = (Block_800FD650 *)&p->mUnknown336;
    pPos = &p->mMotion.mPos;
    result = 0;
    if (!(p->mFlags & 0x4000)) {
        Point_8017886C delta;
        Point_8017886C direction;

        fn_800FD178(p, pBlock);
        if (!PlayerActionAnimIsPassReady(p)) {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = pBlock->mUnknown16;
            p->mUnknown512.mUnknown4 = pBlock->mUnknown16;
            p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
        } else {
            PlayerActionAnimSteerPassReady(p, pBlock->mUnknown16, pBlock->mUnknown12);
            if (fn_800FCFC0(p)) {
                result = 1;
            }
        }
        delta.mX = pBlock->mUnknown0 - pPos->mX;
        delta.mY = pBlock->mUnknown4 - pPos->mY;
        fn_80227538(&direction, pBlock->mUnknown16, pBlock->mUnknown8);
        if (fn_802276E8(&delta, &direction) <= 0.0f) {
            result = 1;
        }
    } else {
        int found = 0;
        unsigned char i = 0;
        unsigned int n = fn_80178D18(fn_80178308());

        for (; i < n; i++) {
            if (PlyrGet(fn_80178308(), i)->mpState->mId == 56) {
                found = 1;
            }
        }
        if (!found) {
            result = 1;
        }
    }
    return result;
}

extern "C" int fn_800FD580(Object_80039F5C *p) {
    int result = 0;
    Block_800FD650 *pBlock = (Block_800FD650 *)&p->mUnknown336;
    Vector_80039F5C *pPos = &p->mMotion.mPos;

    if (!(p->mFlags & 0x4000) || p->mpState->mId == 68) {
        Point_8017886C delta;
        Point_8017886C direction;

        p->mUnknown512.mUnknown14 = 2;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown16;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown16;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
        delta.mX = pBlock->mUnknown0 - pPos->mX;
        delta.mY = pBlock->mUnknown4 - pPos->mY;
        fn_80227538(&direction, pBlock->mUnknown16, 1.0f);
        if (fn_802276E8(&delta, &direction) <= 0.0f) {
            result = 1;
        }
    }
    return result;
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

extern "C" void fn_800FD68C(Message_800F01CC *pMessage, Vector_80039F5C *pFrom, Point_8017886C *pTo) {
    Point_8017886C delta;

    fn_80227690(&delta, pTo, pFrom);
    pMessage->mUnknown1[0] = (int)(fn_802270A4(&delta) * 8.0f);
    pMessage->mUnknown1[1] = fn_801CFE40(delta.mY, delta.mX) >> 17;
}

extern "C" void fn_800FD708(State_80039F5C *pState)
{
    pState->mUnknown2 = ((0x800000 - (pState->mUnknown2 << 17)) & 0xFFFFFF) >> 17;
}

extern "C" void fn_800FD724(Object_80039F5C *p)
{
    if (p && (p->mpState->mId == 3 || p->mpState->mId == 19)) {
        Block_800FD650 *pBlock = (Block_800FD650 *)&p->mUnknown336;
        Point_8017886C delta;
        Point_8017886C target;

        target.mX = pBlock->mUnknown0;
        target.mY = pBlock->mUnknown4;
        fn_80227690(&delta, &target, &p->mMotion.mPos);
        p->mpState->mUnknown1 = (int)(fn_802270A4(&delta) * 8.0f);
        p->mpState->mUnknown2 = fn_801CFE40(delta.mY, delta.mX) >> 17;
    }
}

extern "C" int fn_800FD7D0(Object_80039F5C *p)
{
    PlayBookFormation_t *pTeam = PlayBookGetFormation(p->mIdBytes[2]);
    PlayBookPosition_t *pEntry = &pTeam->mUnknown8.mUnknown84[0][p->mIdBytes[1]];

    return pTeam->mUnknown8.mUnknownF == 1 ? pEntry->mUnknown24 : pEntry->mUnknown20;
}

extern "C" int fn_800FD828(Object_80039F5C *p)
{
    float speed = 0.0f;
    int changed = 0;
    int animation = fn_801BE648(p->mpUnknown792);
    Point_8017886C point;
    Point_8017886C base;

    fn_800FE03C(p, &point);
    base = fn_80177FFC(p->mIdBytes[2]);
    if (animation == 86) {
        fn_8009BD60(p);
    } else if (animation == 85) {
        fn_8009BD60(p);
        if (p->mUnknown2914 == 4) {
            p->mUnknown1008.mUnknown2 = 3;
        } else {
            p->mUnknown1008.mUnknown2 = 5;
        }
        if (fabsf(point.mY - base.mY) < 2.0f) {
            p->mUnknown1008.mUnknown1 = 9;
        }
    }
    if (animation != fn_801BE648(p->mpUnknown792)) {
        changed = 1;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, animation, 1.0f, p);
        p->mpUnknown800[AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, animation, 0)].mUnknown2C = speed;
        p->mFlags &= ~4;
    }
    return changed;
}

extern "C" void fn_800FD978(Object_80039F5C *p)
{
    State_800FDA58 *pState = (State_800FDA58 *)&p->mUnknown336;
    Point_8017886C point;
    int angle;
    unsigned char state;
    float value;

    fn_80177FFC(p->mIdBytes[2]);
    fn_800FE03C(p, &point);
    angle = fn_800FD7D0(p);
    state = p->mUnknown2914;
    if (fn_800AD9B4() == 2 && state == 0 && p->mMotion.mPos.mY < point.mY - 2.0f) {
        value = lbl_803EAE64;
    } else {
        value = 0.0f;
    }
    fn_800FF598(pState, p, &point, angle, value);
    if (fn_800C0658() == 0) {
        fn_800FF6D8(p);
    }
    DivotSkipNextSteps(p);
    fn_80051B88(&p->mMotion, 1.25f);
}

extern "C" int fn_800FDA58(Object_80039F5C *p)
{
    State_800FDA58 *pState = (State_800FDA58 *)&p->mUnknown336;

    pState->mUnknown48 = 0;
    pState->mUnknown52 = 0;
    pState->mUnknown53 = 0;
    fn_800FD978(p);
    if (fn_800FD828(p) != 0) {
        pState->mUnknown48 = 1;
    } else {
        pState->mUnknown48 = 2;
    }
    p->mFlags &= ~0x40000;
    p->mFlags &= ~0x20000000;
    return 0;
}

extern "C" int fn_800FDAC8(Object_80039F5C *p)
{
    unsigned char state = p->mUnknown2914;
    Point_8017886C target = {0.0f, 0.0f};
    State_800FDAC8 *pState = (State_800FDAC8 *)&p->mUnknown336;
    Point_8017886C base;
    int angle = 0;
    int result;

    base = fn_80177FFC(p->mIdBytes[2]);
    switch (pState->mUnknown48) {
    case 0:
        break;
    case 1:
        p->mFlags &= ~0x40000;
        if (p->mFlags & 4) {
            fn_800FD978(p);
            pState->mUnknown0 = 0;
            pState->mUnknown48 = 2;
        }
        break;
    case 2: {
        Point_8017886C *pBase;
        int index;
        float distance;
        int flag;

        target = pState->mUnknown8;
        index = fn_800F06F4(0, p->mpState, 6, 0xFFFF);
        distance = fn_8022781C(&target, &p->mMotion.mPos);
        if (index == 0xFFFF) {
            index = fn_800F06F4(0, p->mpState, 87, 0xFFFF);
            if (index != 0xFFFF) {
                angle = p->mpState[index].mUnknown2 << 16;
            } else {
                angle = 0x400000;
                if (p->mIdBytes[2] == fn_80178320()) {
                    angle = 0xC00000;
                }
            }
        } else {
            angle = p->mpState[index].mUnknown1 << 16;
        }
        pBase = &base;
        p->mFlags &= ~0x40000;
        if ((p->mIdBytes[2] == fn_80178320() && target.mY > pBase->mY + 2.0f)
            || ((state == 19 || state == 23) && fn_80177F70() == 0) || state == 20) {
            flag = 1;
        } else {
            flag = 0;
        }
        if (distance < 3.5f && fn_800CB708(p, &result, target, angle, flag)) {
            pState->mUnknown48 = 4;
            fn_800CBB00(p, result, target, angle, flag);
            break;
        }
        if (pState->mUnknown53 == 0 && lbl_803EABA4->fn_800C0414() == 3 && p->mIdBytes[2] == fn_80178308()) {
            pState->mUnknown53 = 1;
            pState->mUnknown0 = pState->mUnknown0 / 2;
        }
        if (pState->mUnknown52 == 0 && pState->mUnknown0 - 1 <= 0) {
            Point_8017886C delta;
            int run = 1;

            fn_80227690(&delta, &target, &p->mMotion.mPos);
            angle = fn_801CFE40(delta.mY, delta.mX);
            if (p->mMotion.mPos.mY < pBase->mY && pBase->mY - p->mMotion.mPos.mY < 1.5f
                && fabsf(p->mMotion.mPos.mX - base.mX) < 7.0f
                && ((p->mMotion.mPos.mX > base.mX && target.mX < p->mMotion.mPos.mX)
                    || (p->mMotion.mPos.mX < base.mX && target.mX > p->mMotion.mPos.mX))) {
                run = 0;
            }
            if (run && fn_800CB580(p, &result, target, angle, 0)) {
                fn_800CBB00(p, result, target, angle, 1);
                pState->mUnknown48 = 5;
            }
            pState->mUnknown52 = 1;
        }
        if (pState->mUnknown48 == 2) {
            if (p->mUnknown545 == 0 || fn_801783AC(21) == 0) {
                if (fn_800FF094(p) == 1) {
                    p->mFlags &= ~0x10;
                    p->mUnknown512.mUnknown14 = 1;
                    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown0 = 0.0f;
                    return 1;
                }
            } else {
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
                p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
                p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
            }
        }
        break;
    }
    case 5:
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            pState->mUnknown48 = 2;
        }
        break;
    case 3:
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            p->mFlags &= ~0x10;
            return 1;
        }
        p->mFlags &= ~0x40000;
        break;
    case 4:
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = 0.0f;
            return 1;
        }
        p->mFlags &= ~0x40000;
        break;
    }
    return 0;
}

extern "C" int fn_800FDFD8(Object_80039F5C *p)
{
    Input_800B6D34 input;

    if (p->mIdBytes[2] == fn_80178320()) {
        fn_800B6D34(p, &input);
        if (p->mFlags & 0x4000) {
            p->mFlags &= ~0x10;
            return 1;
        }
    }
    return 0;
}

extern "C" void fn_800FE03C(Object_80039F5C *p, Point_8017886C *pOut)
{
    Point_8017886C base;
    PlayBookFormation_t *pTeam;

    base = fn_80177FFC(p->mIdBytes[2]);
    pTeam = PlayBookGetFormation(p->mIdBytes[2]);
    GetFormationPoint(pTeam, p->mIdBytes[1], pOut);
    if (fn_8009FE24(p)) {
        Object_80039F5C *pOther = fn_800FB844(p);

        if (pOther) {
            PlayBookFormation_t *pOtherTeam = PlayBookGetFormation(pOther->mIdBytes[2]);
            Point_8017886C other;
            unsigned char i;
            unsigned int count;

            {
                PlayBookPosition_t *pEntry = &pOtherTeam->mUnknown8.mUnknown84[0][pOther->mIdBytes[1]];
                Point_8017886C *pPoint;

                // FAKEMATCH: mY is stored through a pointer to other while mX is stored directly; this places &other after the first lfs as the target does
                other.mX = (pOtherTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mX;
                pPoint = &other;
                pPoint->mY = (pOtherTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mY;
            }
            if (fabsf(other.mX) < lbl_803EAE70) {
                if (p->mUnknown2914 == 16) {
                    if (pOut->mX < -lbl_803EAE70) {
                        other.mX = other.mX > -lbl_803EAE70 ? -lbl_803EAE70 : other.mX;
                    } else if (pOut->mX > lbl_803EAE70) {
                        other.mX = other.mX < lbl_803EAE70 ? lbl_803EAE70 : other.mX;
                    } else {
                        other.mX = pOut->mX;
                    }
                } else if (p->mUnknown2914 != 17 && p->mUnknown2914 != 18) {
                    if (pOut->mX < -lbl_803EAE70 * 0.5f) {
                        other.mX = other.mX > -lbl_803EAE70 * 0.5f ? -lbl_803EAE70 * 0.5f : other.mX;
                    } else if (pOut->mX > lbl_803EAE70 * 0.5f) {
                        other.mX = other.mX < lbl_803EAE70 * 0.5f ? lbl_803EAE70 * 0.5f : other.mX;
                    } else {
                        pOut->mX = other.mX;
                    }
                }
            }
            if (p->mUnknown2914 != 17 && p->mUnknown2914 != 18) {
                pOut->mX = other.mX;
            } else if (pOtherTeam->mUnknown8.mUnknown4 == 11) {
                pOut->mX = other.mX;
            }
            count = fn_80178D18(fn_80178320());
            for (i = 0; i < count; i++) {
                PlayBookPosition_t *pEntry;
                Point_8017886C *pPoint;
                int carrier;
                int open;

                if (i == p->mIdBytes[1]) {
                    continue;
                }
                open = 0;
                carrier = 0;
                pEntry = &pTeam->mUnknown8.mUnknown84[0][i];
                pPoint = pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10;
                if (fn_8009FE24(PlyrGet(fn_80178320(), i))) {
                    carrier = 1;
                }
                if (!carrier) {
                    open = 1;
                }
                if (open && fn_8022781C(pPoint, pOut) < lbl_803EAE68) {
                    if (pOut->mX >= 0.0) {
                        pOut->mX = pOut->mX + lbl_803EAE6C;
                    } else {
                        pOut->mX = pOut->mX - lbl_803EAE6C;
                    }
                    break;
                }
            }
        }
    }
    AddPoint(pOut, &base);
    pOut->mX = CLAMP(pOut->mX, 1.0f - fn_80178A08(), fn_80178A08() - 1.0f);
    pOut->mY = CLAMP(pOut->mY, 1.0f - fn_80178A44(), fn_80178A44() - 1.0f);
}

extern "C" void fn_800FE41C(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pOut)
{
    pOut->mX = p->mMotion.mPos.mX;
    pOut->mY = p->mMotion.mPos.mY;
}

extern "C" void fn_800FE430(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pOut)
{
    pOut->mX = p->mMotion.mUnknown40;
    pOut->mY = p->mMotion.mUnknown44;
}

extern "C" {
void fn_800FE444(Object_80039F5C *p, int angle, Point_8017886C *point, float length)
{
    Point_8017886C delta;
    int to;
    int difference;

    fn_80227690(&delta, point, &p->mMotion.mPos);
    fn_802270A4(&delta);
    to = fn_801CFE40(delta.mY, delta.mX);
    difference = MathAngleDiff(to, angle);
    if (difference > 0x400000) {
        int limited = (angle - 0x400000) & 0xFFFFFF;

        if (MathAngleDiff(to, limited) <= 0x3FFFFF) {
            limited = (angle + 0x400000) & 0xFFFFFF;
        }
        fn_80227538(&delta, limited, length);
        fn_80227638(point, point, &delta);
    } else {
        fn_80227538(&delta, (angle - 0x800000) & 0xFFFFFF,
                    ((float)difference + (float)difference) * length * 0.0000002384185791015625f);
        fn_80227638(point, point, &delta);
    }
}
}

extern "C" {
void fn_800FE564(Object_80039F5C *p, Object_80039F5C *other, Object_80039F5C *target, float limit)
{
    Point_8017886C a;
    Point_8017886C b;
    Point_8017886C av;
    Point_8017886C bv;
    State_800FDA58 *state;
    float base;
    float radius;
    float dx;
    float dy;
    float px;
    float py;
    float aa;
    float bb;
    float disc;
    float first;
    float second;
    float t;
    float distance;

    fn_800FE41C(p, other, &a);
    fn_800FE41C(other, p, &b);
    state = (State_800FDA58 *)&p->mUnknown336;
    if (fn_8022781C(&a, &b) >= limit) {
        return;
    }
    fn_800FE430(p, target, &av);
    bv.mX = other->mMotion.mUnknown40;
    bv.mY = other->mMotion.mUnknown44;
    if (p->mpState->mId == 7) {
        base = 0.5f;
    } else {
        base = 2.0f;
    }
    if (base + fn_802270A4(&bv) / gPlyrMoveFwdSpeed <= 5.5f) {
        radius = base + fn_802270A4(&bv) / gPlyrMoveFwdSpeed;
    } else {
        radius = 5.5f;
    }
    if (p->mMotion.mUnknown28 != 0.0f && other->mMotion.mUnknown28 != 0.0f) {
        radius -= lbl_803EAE78 * fn_801CFB94(MathAngleDiff(p->mMotion.mUnknown32, other->mMotion.mUnknown32));
        if (radius < lbl_803EAE7C) {
            radius = lbl_803EAE7C;
        }
    }
    dx = bv.mX - av.mX;
    px = b.mX - a.mX;
    py = b.mY - a.mY;
    dy = bv.mY - av.mY;
    if (dx < 0.0000001f && dx > -0.0000001f) {
        dx = 0.0f;
    }
    if (dy < 0.0000001f && dy > -0.0000001f) {
        dy = 0.0f;
    }
    if (dx == 0.0f && dy == 0.0f) {
        return;
    }
    aa = dx * dx + dy * dy;
    bb = px * dx + py * dy;
    disc = bb * bb - 4.0f * aa * (px * px + py * py - radius * radius);
    if (disc < 0.0000001f) {
        return;
    }
    disc = fn_80260B1C(disc);
    if (aa < 0.0000001f) {
        aa = 0.0000001f;
    }
    first = (-bb - disc) / (aa + aa);
    second = (-bb + disc) / (aa + aa);
    if (first < 0.0f) {
        if (second >= 0.0f) {
            t = 0.0f;
        } else {
            t = first;
        }
    } else {
        t = first;
    }
    distance = fn_8022781C(&p->mMotion.mPos, &other->mMotion.mPos);
    if (t < 0.0f) {
        return;
    }
    if (t >= state->mUnknown40 && (t != state->mUnknown40 || distance >= state->mUnknown44)) {
        return;
    }
    fn_80227248(&av, &av, t);
    fn_80227638(&a, &a, &av);
    fn_80227248(&bv, &bv, t);
    fn_80227638(&b, &b, &bv);
    if (fn_8022781C(&a, &b) >= radius + 0.0000001f) {
        return;
    }
    fn_80227690(&av, &a, &b);
    state->mUnknown40 = t;
    state->mUnknown40 = state->mUnknown40 > 180.0f ? 180.0f : state->mUnknown40;
    state->mUnknown44 = distance;
    fn_802271A4(&state->mUnknown32, &av);
}
}

extern "C" {
void fn_800FE910(Object_80039F5C *p, Point_8017886C *point, float *value, float *distance, float *time)
{
    *distance = fn_8022781C(point, &p->mMotion.mPos);
    *distance = *distance > 15.0f ? 15.0f : *distance;
    if (*value > 0.0000001f) {
        float t = *distance / (gPlyrMoveFwdSpeed * *value);

        *time = t > 180.0f ? 180.0f : t;
    }
}
}

extern "C" {
void AssignRescanAvoidance(Object_80039F5C *p, Point_8017886C *point, float *speed)
{
    State_800FDA58 *s = (State_800FDA58 *)&p->mUnknown336;
    float distance;
    float time;
    Point_8017886C goal;
    Point_8017886C *direction;
    int team;

    if (--s->mUnknown0 > 0) {
        return;
    }
    direction = &s->mUnknown32;
    fn_800FE910(p, point, speed, &distance, &time);
    s->mUnknown0 = lbl_803EAE76;
    s->mUnknown40 = 180.0f;
    s->mUnknown44 = 1000.0f;
    // FAKEMATCH: x is cleared through the state block and y through direction (the same vector) for the target's two store bases
    s->mUnknown32.mX = direction->mY = 0.0f;
    if (*speed == 0.0f) {
        return;
    }
    if (p->mpState->mId == 7) {
        goal = fn_80177FFC(p->mIdBytes[2]);
        if (fabsf(p->mMotion.mPos.mY - goal.mY) < 1.5f) {
            s->mUnknown40 = 0.0f;
            if (p->mIdBytes[2] == fn_80178308()) {
                fn_80227538(direction, 0xC00000, 1.0f);
            } else {
                fn_80227538(direction, 0x400000, 1.0f);
            }
        }
    }
    if (s->mUnknown40 == 180.0f) {
        for (team = 0; team <= 1; team++) {
            int count = fn_80178D18((unsigned char)team);
            int i;

            for (i = 0; i < count; i++) {
                Object_80039F5C *other = PlyrGet((unsigned char)team, (unsigned short)i);

                if (other != p) {
                    fn_800FE564(p, other, (Object_80039F5C *)point, distance);
                }
            }
        }
    }
}
}

extern "C" {
void fn_800FEB60(Object_80039F5C *p, Point_8017886C *point, float *speed)
{
    float distance;
    float time;
    State_800FDA58 *s;
    Point_8017886C direction;
    Point_8017886C normal;
    Point_8017886C projected;
    Point_8017886C side;
    Point_8017886C delta;
    float parallel;
    float perpendicular;
    int target;
    int heading;
    int turn;
    float scale;

    fn_800FE910(p, point, speed, &distance, &time);
    s = (State_800FDA58 *)&p->mUnknown336;
    if (s->mUnknown40 >= time) {
        return;
    }
    fn_80227690(&direction, point, &p->mMotion.mPos);
    fn_802271A4(&direction, &direction);
    if (s->mUnknown40 < 4.5454545f) {
        parallel = 0.55f;
    } else {
        parallel = 2.5f / s->mUnknown40;
    }
    if (s->mUnknown40 < 6.1538463f) {
        perpendicular = 0.65f;
    } else {
        perpendicular = 4.0f / s->mUnknown40;
    }
    fn_802271A4(&normal, &s->mUnknown32);
    fn_80227248(&projected, &direction, fn_802276E8(&normal, &direction));
    fn_80227690(&side, &normal, &projected);
    fn_80227248(&projected, &projected, parallel);
    fn_802271A4(&side, &side);
    fn_80227248(&side, &side, perpendicular);
    fn_80227638(&direction, &direction, &projected);
    fn_80227638(&direction, &direction, &side);
    fn_80227690(&delta, point, &p->mMotion.mPos);
    target = fn_801CFE40(delta.mY, delta.mX);
    heading = fn_801CFE40(direction.mY, direction.mX);
    turn = MathAngleDiff(target, heading);
    MathAngleDiff(p->mMotion.mUnknown32, heading);
    scale = fn_802270A4(&direction) < 1.0f ? fn_802270A4(&direction) : 1.0f;
    if (s->mUnknown40 != 0.0f) {
        scale = fn_802270A4(&direction) < 1.0f ? fn_802270A4(&direction) : 1.0f;
    } else {
        if (turn != 0) {
            scale = fn_802270A4(&direction) < 1.0f ? fn_802270A4(&direction) : 1.0f;
        } else {
            scale = fn_802270A4(&direction) < 1.0f ? fn_802270A4(&direction) : 1.0f;
        }
    }
    *speed *= scale;
    fn_80227248(&direction, &direction, distance);
    fn_80227638(point, &p->mMotion.mPos, &direction);
}
}

extern "C" {
float fn_800FEDBC(State_800FDA58 *s, Object_80039F5C *p, float distance)
{
    Point_8017886C goal;
    int mode;
    unsigned int minimum;
    float desired;
    float result;

    goal = fn_80177FFC(p->mIdBytes[2]);
    mode = fn_800AD9B4();
    minimum = p->mRatings[4];
    if (minimum < lbl_803EAE80) {
        minimum = lbl_803EAE80;
    }
    result = s->mUnknown24;
    if ((unsigned int)(s->mUnknown2 - 1) < 2) {
        return result;
    }
    desired = s->mUnknown20Float;
    if (mode != 1 && mode != 9 && distance > 20.0f) {
        desired = 0.72f;
    }
    if (lbl_803EABA4->fn_800C0414() == 3 && p->mIdBytes[2] == fn_80178308()) {
        desired = 1.0f;
    }
    if (distance > 4.0f && mode == 2 && fn_801783AC(21) != 0) {
        desired = 0.72f;
    }
    if (mode == 2 && fabsf(s->mUnknown8 - goal.mX) > 8.0f) {
        desired = 1.0f;
    }
    if (mode == 1) {
        desired = 0.5f;
    }
    result = desired - s->mUnknown24;
    result = result < -0.01f ? -0.01f : (result > 0.05f ? 0.05f : result);
    s->mUnknown24 += result;
    result = s->mUnknown24;
    if (distance < 3.0f) {
        result = result * (distance * 0.33333334f);
        if (result < minimum * 0.00054901966f) {
            result = minimum * 0.00054901966f;
        }
    }
    return result;
}
}

extern "C" {
int fn_800FEFD4(Object_80039F5C *p)
{
    Point_8017886C point;
    point.mX=(float)(signed char)p->mpState->mUnknown1*0.25f;
    point.mY=(float)(signed char)p->mpState->mUnknown2*0.5f;
    fn_800FF598((State_800FDA58 *)&p->mUnknown336,p,&point,p->mpState->mUnknown3[0]<<16,-1.0f);
    return 0;
}
}

extern "C" {
int fn_800FF094(Object_80039F5C *p)
{
    int mode = fn_800AD9B4();
    int special = mode == 4;
    State_800FDA58 *s = (State_800FDA58 *)&p->mUnknown336;
    Point_8017886C point;
    Point_8017886C delta;
    float distance;
    float speed;
    float limit;
    int angle;

    point.mX = s->mUnknown8;
    point.mY = s->mUnknown12;
    fn_800FE444(p, s->mUnknown16, &point, s->mUnknown28);
    distance = fn_8022781C(&s->mUnknown8, &p->mMotion.mPos);
    speed = fn_800FEDBC(s, p, distance);
    switch (s->mUnknown2) {
    case 0:
        if (--s->mUnknown0 <= 0) {
            s->mUnknown0 = 0;
            AssignRescanAvoidance(p, &point, &s->mUnknown24);
            fn_800FEB60(p, &point, &s->mUnknown24);
            fn_80227690(&delta, &point, &p->mMotion.mPos);
            fn_801CFE40(delta.mY, delta.mX);
            s->mUnknown2 = 3;
        }
        break;
    case 1:
    case 2:
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            p->mMotion.mUnknown28 = 0.0f;
            s->mUnknown2 = s->mUnknown3Byte;
            s->mUnknown3Byte = 0;
        } else if (fn_801BE648(p->mpUnknown792) == 100) {
            if (s->mUnknown2 == 2) {
                p->mUnknown512.mUnknown14 = 7;
                p->mUnknown512.mUnknown4 = s->mUnknown4;
                p->mUnknown512.mUnknown8 = s->mUnknown4;
                p->mUnknown512.mUnknown0 = 1.5f;
            } else {
                p->mUnknown512.mUnknown14 = 6;
                p->mUnknown512.mUnknown4 = s->mUnknown4;
                p->mUnknown512.mUnknown8 = s->mUnknown4;
                p->mUnknown512.mUnknown0 = 1.0f;
            }
        } else {
            s->mUnknown2 = s->mUnknown3Byte;
            s->mUnknown3Byte = 0;
        }
        break;
    case 3:
        if (distance > 3.0f) {
            AssignRescanAvoidance(p, &point, &s->mUnknown24);
            fn_800FEB60(p, &point, &s->mUnknown24);
            speed = s->mUnknown24;
        } else if (special && p->mUnknown560.mFlags.mBytes[0] != 0) {
            s->mUnknown8 = p->mMotion.mPos.mX;
            s->mUnknown12 = p->mMotion.mPos.mY;
        }
        limit = special == 1 ? lbl_803EAE84 : 0.05f;
        if (distance < limit) {
            p->mMotion.mUnknown28 = 0.0f;
            s->mUnknown2 = 4;
        } else {
            fn_80227690(&delta, &point, &p->mMotion.mPos);
            angle = fn_801CFE40(delta.mY, delta.mX);
            if (speed == 1.0f) {
                p->mUnknown512.mUnknown15 = 1;
            }
            p->mUnknown512.mUnknown14 = BallFindHeldBy(p) ? 1 : 9;
            p->mUnknown512.mUnknown8 = angle;
            p->mUnknown512.mUnknown4 = angle;
            p->mUnknown512.mUnknown0 = speed;
        }
        break;
    case 4:
        if (special != 1 && MathAngleDiff(s->mUnknown16, p->mMotion.mFacing) > 0xB60B) {
            if (MathAngleDiff(p->mMotion.mFacing, s->mUnknown16) <= 0x155554) {
                if (p->mpState[1].mId != 87) {
                    p->mUnknown512.mUnknown14 = 3;
                    p->mUnknown512.mUnknown4 = s->mUnknown16;
                    p->mUnknown512.mUnknown8 = s->mUnknown16;
                    p->mUnknown512.mUnknown0 = 0.0f;
                    break;
                }
            } else {
                float limit = p->mIdBytes[2] == fn_80178308() ? 8.0f : 2.0f;
                float rate;

                s->mUnknown4 = s->mUnknown16;
                p->mFlags &= ~4;
                if (mode == 4 || !fn_80177F70()
                    || fabsf(fn_80177FFC(p->mIdBytes[2]).mY - p->mMotion.mPos.mY) > limit) {
                    s->mUnknown2 = 1;
                    p->mUnknown512.mUnknown14 = 6;
                    rate = 1.0f;
                } else {
                    s->mUnknown2 = 2;
                    p->mUnknown512.mUnknown14 = 7;
                    rate = 1.5f;
                }
                p->mUnknown512.mUnknown4 = s->mUnknown16;
                p->mUnknown512.mUnknown8 = s->mUnknown16;
                p->mUnknown512.mUnknown0 = rate;
                s->mUnknown3Byte = 6;
                break;
            }
        }
        s->mUnknown2 = 5;
        break;
    case 5:
        if (distance < 0.05f || special == 1) {
            p->mMotion.mUnknown28 = 0.0f;
            s->mUnknown2 = 6;
        } else {
            fn_80227690(&delta, &point, &p->mMotion.mPos);
            p->mUnknown512.mUnknown4 = fn_801CFE40(delta.mY, delta.mX);
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown8 = s->mUnknown16;
            p->mUnknown512.mUnknown0 = speed;
        }
        break;
    case 6:
        break;
    }
    return s->mUnknown2 == 6;
}
}

extern "C" int fn_800FF538(Object_80039F5C *p, int a)
{
    State_800FDA58 *pState = (State_800FDA58 *)&p->mUnknown336;

    if (a == 1) {
        pState->mUnknown4 = (pState->mUnknown4 + 0x800000) & 0xFFFFFF;
        pState->mUnknown16 = (pState->mUnknown16 + 0x800000) & 0xFFFFFF;
        pState->mUnknown8 = -pState->mUnknown8;
        pState->mUnknown12 = -pState->mUnknown12;
        if (pState->mUnknown2 != 0) {
            pState->mUnknown0 = 0;
        }
    }
    return 0;
}

extern "C" {
void fn_800FF598(State_800FDA58 *s, Object_80039F5C *p, Point_8017886C *point, int angle, float value)
{
    s->mUnknown0 = 0;
    s->mUnknown8 = point->mX;
    s->mUnknown12 = point->mY;
    s->mUnknown20Float = 0.56f;
    s->mUnknown16 = angle;
    s->mUnknown24 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
    if (value == -1.0f) {
        Point_8017886C delta;

        if (fn_8022781C(&p->mMotion.mPos, point) < 3.0f) {
            s->mUnknown28 = 0.0f;
        } else {
            fn_80227690(&delta, point, &p->mMotion.mPos);
            if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), angle) >= 0x3C71C8) {
                s->mUnknown28 = 0.0f;
            } else {
                float random = fn_80237260(0);

                s->mUnknown28 = random + random + 2.0f;
            }
        }
    } else {
        s->mUnknown28 = value;
    }
    s->mUnknown4 = 0;
    s->mUnknown2 = 0;
    s->mUnknown32.mY = 0.0f;
    s->mUnknown32.mX = 0.0f;
    s->mUnknown40 = 0.0f;
    s->mUnknown3Byte = 0;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown0 = s->mUnknown24;
}
}

extern "C" {
void fn_800FF6D8(Object_80039F5C *p)
{
    State_800FDA58 *s=(State_800FDA58 *)&p->mUnknown336;
    Object_800B26B0 *motion = &p->mMotion;

    motion->mPos.mX = s->mUnknown8;
    motion->mPos.mY = s->mUnknown12;
    motion->mFacing = s->mUnknown16;
    p->mpUnknown796->mUnknown8 = motion->mFacing;
    motion->mUnknown28 = 0.0f;
    s->mUnknown0 = 0;
    s->mUnknown4 = 0;
    s->mUnknown2 = 5;
    s->mUnknown3Byte = 0;
    s->mUnknown20Float = 0.0f;
    s->mUnknown24 = 0.0f;
    s->mUnknown28 = 0.0f;
    s->mUnknown32.mX = 0.0f;
    s->mUnknown32.mY = 0.0f;
    s->mUnknown40 = 0.0f;
    p->mUnknown512.mUnknown14=0;
    fn_801BE068(p->mpUnknown792,p->mpUnknown796,p->mpUnknown800,74,1.0f,p);
    fn_801BE67C(p->mpUnknown792,p->mpUnknown796,p->mpUnknown800,p);
    p->mUnknown9[0]=1;
}
}

extern "C" int fn_800FF7A8(Object_80039F5C *p)
{
    State_800FF7A8 *pState = (State_800FF7A8 *)&p->mUnknown336;

    pState->mUnknown0 = 0;
    pState->mUnknown4 = 0;
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~4;
    fn_800A3B58(p, 2, 0);
    return 0;
}

extern "C" {
int fn_800FF7F4(Object_80039F5C *p)
{
    fn_8010A2DC(p, 0, -1);
    if (p->mUnknown560.mUnknown53 != 0) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.0f;
        return 1;
    }
    return 0;
}
}

extern "C" int fn_800FF860() {
    return 1;
}

extern "C" {
void fn_800FF868(Object_80039F5C *p,State_800FFDFC *,Object_80039F5C *other)
{
    Point_8017886C delta;fn_80227690(&delta,&other->mMotion.mPos,&p->mMotion.mPos);
    fn_800C89F0(p,fn_801CFE40(delta.mY,delta.mX)&0xFFFFFF,1,0,0.5f);fn_8009D284(p,other);
}
}

extern "C" void fn_800FF8DC(Object_80039F5C *p, State_800FFDFC *pState)
{
    fn_8009D1AC(p);
}

extern "C" {
void fn_800FF8FC(Object_80039F5C *p, float *out)
{
    State_80039F5C *state = p->mpState;

    out[0] = (float)(signed char)state->mUnknown1 * 0.0625f;
    out[1] = (float)(signed char)state->mUnknown2 * 0.0625f;
    if (fn_801486A0() == 2) {
        Vector_80039F5C ball;

        BallGetPosition(BallGetCurrent(), &ball);
        if (p->mMotion.mPos.mX > ball.mX + 2.0f) {
            out[0] = fabsf(out[0]);
        } else if (p->mMotion.mPos.mX < ball.mX - 2.0f) {
            out[0] = -fabsf(out[0]);
        } else if (fn_802372EC(0, 100) < 50) {
            out[0] = fabsf(out[0]);
        } else {
            out[0] = -fabsf(out[0]);
        }
    }
}
}

extern "C" {
int fn_800FFA10(Object_80039F5C *p, Object_80039F5C *other)
{
    State_80039F5C *state = other->mpState;
    int result = 1;

    switch (state->mId) {
    case 18:
        result = 0;
        break;
    case 1:
        if (fn_8022781C(&p->mMotion.mPos, &other->mMotion.mPos) > 9.0f
            || p->mMotion.mPos.mY > other->mMotion.mPos.mY) {
            if (fn_801486A0() != 2 || fn_801783AC(20) != 0) {
                Message_800F01CC message;

                result = 0;
                memset(&message, 0, 4);
                message.mId = 33;
                fn_800F053C(0, p->mpState, &message, p);
            }
        }
        break;
    case 25:
        if (state->mUnknown2 == 9) {
            Message_800F01CC message;

            memset(&message, 0, 4);
            if (state->mUnknown1 == p->mIdBytes[1]) {
                fn_8010CEB8(p, 9);
            } else {
                message.mId = 33;
                fn_800F053C(0, p->mpState, &message, p);
            }
            result = 0;
        }
        break;
    }
    return result;
}
}

extern "C" {
void fn_800FFB4C(Object_80039F5C *p, Object_80039F5C *other, float *value, Point_8017886C *out)
{
    float factor;

    if (*value > 0.0f) {
        factor = MapRange(fn_80178A08() - p->mMotion.mPos.mX, 1.0f, 4.5f, -1.0f, 1.0f);
        factor = factor < -1.0f ? -1.0f : (factor > 1.0f ? 1.0f : factor);
    } else {
        factor = MapRange(fn_80178A08() + p->mMotion.mPos.mX, 1.0f, 4.5f, -1.0f, 1.0f);
        factor = factor < -1.0f ? -1.0f : (factor > 1.0f ? 1.0f : factor);
    }
    Point_8017886C delta;

    delta.mX = value[0];
    delta.mY = value[1];
    delta.mX *= factor;
    if (MathAngleDiff(other->mMotion.mUnknown32, 0x400000) > 0x200000) {
        if (delta.mY < 0.0f) {
            delta.mY *= 3.0f;
            delta.mY = delta.mY < -3.0f ? -3.0f : delta.mY;
        }
    } else {
        float d = 3.0f - fabsf(p->mMotion.mPos.mX - other->mMotion.mPos.mX);

        if (d < 0.0f) {
            d = 0.0f;
        }
        {
            float ratio = d / 3.0f;

            delta.mY *= ratio * 4.0f + 1.0f;
        }
    }
    fn_80227638(out, &other->mMotion.mPos, &delta);
}
}

extern "C" {
void fn_800FFD2C(Object_80039F5C *p, Point_8017886C *point)
{
    Point_8017886C delta;
    int angle;
    float speed;

    BallGetCurrentHolder();
    fn_80227690(&delta, point, &p->mMotion.mPos);
    angle = fn_801CFE40(delta.mY, delta.mX);
    speed = (fn_802270A4(&delta) - 0.3f) * 0.5f;
    speed = speed < 0.0f ? 0.0f : (speed > 1.0f ? 1.0f : speed);
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = angle;
    p->mUnknown512.mUnknown0 = speed;
    if (speed > 0.72f) {
        p->mUnknown512.mUnknown15 = 1;
    }
}
}

extern "C" int fn_800FFDFC(Object_80039F5C *p)
{
    State_800FFDFC *pState = (State_800FFDFC *)&p->mUnknown336;

    pState->mUnknown0 = 0;
    fn_800FF8FC(p, &pState->mUnknown4);
    return 0;
}

extern "C" int fn_800FFE30(Object_80039F5C *p)
{
    Object_80039F5C *pOther = BallGetCurrentHolder();
    State_800FFDFC *pState = (State_800FFDFC *)&p->mUnknown336;
    Message_800F01CC message;
    Point_8017886C point;

    if (fn_8010A2DC(p, 0, -1) != 0) {
        pState->mUnknown0 = 1;
    }
    if (*PlyrGetPendingMsg(p) == 57 && p->mUnknown3040 > 30) {
        p->mUnknown3040 = 30;
    }
    if (pOther != 0) {
        if (p == pOther) {
            memset(&message, 0, 4);
            message.mId = 1;
            fn_800F053C(0, p->mpState, &message, p);
            return 1;
        }
        if (fn_800FFA10(p, pOther) != 0) {
            if (!(p->mFlags & 0x4000)) {
                fn_800FFB4C(p, pOther, &pState->mUnknown4, &point);
                fn_800FFD2C(p, &point);
                fn_800FF868(p, pState, pOther);
            }
            return 0;
        }
        return 1;
    } else {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
        fn_8010CFD4(p);
    }
    return 0;
}

extern "C" int fn_800FFF78(Object_80039F5C *p)
{
    fn_800FF8DC(p, (State_800FFDFC *)&p->mUnknown336);
    return 1;
}

extern "C" void fn_800FFFA0(State_80039F5C *pState)
{
    pState->mUnknown1 = -pState->mUnknown1;
}

extern "C" int fn_800FFFB0(Object_80039F5C *p)
{
    if (fn_801486A0() == 1) {
        int result = 0;

        if (BallFindHeldBy(p) != 0) {
            result = fn_80178308() == p->mIdBytes[2];
        }
        return result;
    }
    return p == BallGetCurrentHolder();
}

extern "C" {
int fn_80100024(Object_80039F5C *p, int angle, int mode)
{
    Vector_80039F5C point;
    unsigned char filter[3] = {2, 10, 11};
    int result = 1;

    if (!(p->mFlags & 0x4000)) {
        point.mZ = 0.0f;
        if (mode == 2) {
            fn_80227538((Point_8017886C *)&point, angle, lbl_803EAEA4);
            fn_80227638(&point, &point, &p->mMotion.mPos);
            if (!fn_801248D4(p, &p->mMotion.mPos, &point, 0, 0.0f, 1.0f, (Filter_801248D4 *)filter, 0)) {
                result = 0;
            }
        }
    }
    return result;
}
}

extern "C" int fn_801000EC(Object_80039F5C *p)
{
    int result = 0;

    if (p != 0) {
        int id = p->mpState->mId;

        if (id == 33 || id == 31 || id == 47 || id == 32) {
            result = 1;
        }
        if (result == 0 && fn_8011E9D8(p->mpState) != 0) {
            result = 1;
        }
    }
    return result;
}

extern "C" {
void fn_8010016C(Object_80039F5C *p, Point_8017886C *point, Object_80039F5C *other, float speed)
{
    float chance = (float)other->mRatings[6] * 0.00392156886f;
    Point_8017886C middle;
    Point_8017886C delta;
    float time;
    float best;
    int replace;
    int team;
    unsigned int count;
    unsigned int i;

    if (lbl_803EAEA0 && fn_80237260(0) >= chance) {
        return;
    }
    fn_80227904(&middle, &p->mMotion.mPos, point, 0.5f);
    fn_80227690(&delta, point, &other->mMotion.mPos);
    time = fn_802270A4(&delta) / speed;
    best = 3.4028235e38f;
    replace = 0;
    team = fn_80178320();
    count = fn_80178D70(team);
    for (i = 0; i < count; i++) {
        Object_80039F5C *candidate = PlyrGet(team, (unsigned short)i);
        Point_8017886C pos;
        Point_8017886C offset;
        Point_8017886C future;
        float now;
        float later;

        if (fn_8011E9B4(candidate) || (candidate->mFlags & 0x800)) {
            continue;
        }
        pos.mX = candidate->mMotion.mPos.mX;
        pos.mY = candidate->mMotion.mPos.mY;
        fn_80227690(&offset, point, &pos);
        now = fn_802270A4(&offset);
        future.mX = candidate->mMotion.mPos.mX;
        future.mY = candidate->mMotion.mPos.mY;
        fn_8022732C(&future, &candidate->mMotion.mUnknown40, time);
        fn_80227690(&offset, point, &future);
        later = fn_802270A4(&offset);
        later = later > now ? now : later;
        if (later < best) {
            best = later;
            fn_80227690(&offset, &middle, &pos);
            replace = fn_802270A4(&offset) > now;
        }
    }
    if (replace) {
        point->mX = middle.mX;
        point->mY = middle.mY;
    }
}
}

extern "C" {
int fn_80100370(Ball_t *ball, Object_80039F5C *p, float value, Vector_80039F5C *out)
{
    Vector_80039F5C pos;
    Vector_80039F5C velocity = *(Vector_80039F5C *)&p->mMotion.mUnknown40;
    Vector_80039F5C ballPos;
    State_80039F5C *queue = p->mpState;
    State_80039F5C *state;
    Object_800B26B0 *motion = &p->mMotion;
    int angle = motion->mUnknown32;
    float speed = motion->mUnknown28;

    pos = motion->mPos;
    int result = 0;

    BallGetPosition(ball, &ballPos);
    state = p->mpState;
    switch (state->mId) {
    case 19:
        speed = PlyrMoveGetRatedSpeed(p, 1.0f, 1.0f);
        break;
    case 20:
        if ((unsigned int)(state->mUnknown2 - 8) < 2) {
            angle = PlayerCutGetStartHeading(p);
        } else {
            angle = PlayerCutGetTargetHeading(p);
        }
        PlayerCutGetEndPoint(p, (Point_8017886C *)&pos);
        speed = PlayerCutGetRunSpeed(p, 0.5f);
        fn_80227538((Point_8017886C *)&velocity, angle, speed);
        break;
    case 52:
        if ((unsigned int)(state->mUnknown1 - 4) < 2) {
            pos.mY += 3.0f;
            speed = PlyrMoveGetRatedSpeed(p, 1.0f, 0.72f);
            fn_80227538((Point_8017886C *)&velocity, angle, speed);
        }
        break;
    }
    fn_80103F80(ball, pos, velocity, speed, angle, value, out, p);
    switch (p->mpState->mId) {
    case 10:
    case 51:
    case 52:
    case 58:
        break;
    default:
        if (fn_800F06F4(0, queue, 19, 0xFFFF) != 0xFFFF || fn_800F06F4(0, queue, 20, 0xFFFF) != 0xFFFF) {
            unsigned int index = fn_800F06F4(0, queue, 21, 0xFFFF);

            if (index != 0xFFFF && index > 1) {
                while (queue[index].mId != 19 && queue[index].mId != 20 && queue[index].mId != 51) {
                    index--;
                }
                if (index != 0) {
                    float steps = fn_8022781C(out, &ballPos) / value;
                    int count;

                    steps = (float)(int)steps;
                    count = (int)steps;
                    float shortened;

                    fn_80104328(p, (unsigned char)(index - 1), &count, &pos, &angle);
                    shortened = (float)count;
                    if (shortened < steps) {
                        if (state->mId == 20) {
                            speed = PlayerCutGetRunSpeed(p, 1.0f - shortened / steps);
                        } else {
                            speed = PlyrMoveGetRatedSpeed(p, 1.0f - shortened / steps, 1.0f);
                        }
                        fn_80227538((Point_8017886C *)&velocity, angle, speed);
                        result = 1;
                        fn_80103F80(ball, pos, velocity, speed, angle, value, out, p);
                    }
                }
            }
        }
        break;
    }
    return result;
}
}

extern "C" {
void fn_801007A4(Ball_t *ball, Object_80039F5C *p, Object_80039F5C *other, float value,
                 Vector_80039F5C *out, unsigned char *kind)
{
    Object_800B26B0 *motion = &other->mMotion;

    switch (*kind) {
    case 1:
    case 7:
        if (!fn_80100370(ball, other, value, out)) {
            if (*kind == 1) {
                *kind = 0;
            } else {
                *kind = 6;
            }
        }
        break;
    case 0:
    case 4:
    case 6: {
        Vector_80039F5C velocity = *(Vector_80039F5C *)&motion->mUnknown40;
        Vector_80039F5C pos = motion->mPos;
        float speed = motion->mUnknown28;
        State_80039F5C *state = other->mpState;

        switch (state->mId) {
        case 52:
            if ((unsigned int)(state->mUnknown1 - 4) < 2) {
                pos.mY += 3.0f;
                speed = PlyrMoveGetRatedSpeed(other, 1.0f, 1.0f);
                fn_80227538((Point_8017886C *)&velocity, motion->mUnknown32, speed);
            }
            break;
        case 51:
            if (fn_800F06F4(0, state, 19, 0xFFFF) != 0xFFFF && other->mMotion.mPos.mY >= p->mMotion.mPos.mY) {
                pos.mY += 2.5f;
                speed = PlyrMoveGetRatedSpeed(other, 1.0f, 1.0f);
                fn_80227538((Point_8017886C *)&velocity, motion->mUnknown32, speed);
            }
            break;
        case 19: {
            int towardNegative = MathAngleDiff(motion->mUnknown32, 0x800000) <= 0x271C70;
            int towardPositive = MathAngleDiff(motion->mUnknown32, 0) <= 0x271C70;

            if (motion->mPos.mY < p->mMotion.mPos.mY - 2.0f && (towardNegative || towardPositive)) {
                speed = PlyrMoveGetRatedSpeed(other, 1.0f, 1.0f);
                fn_80227538((Point_8017886C *)&velocity, motion->mUnknown32, speed);
                if (towardNegative) {
                    pos.mX -= 3.0f;
                } else {
                    pos.mX += 3.0f;
                }
            }
            break;
        }
        }
        fn_80103F80(ball, pos, velocity, speed, motion->mUnknown32, value, out, other);
        break;
    }
    default:
        out->mX = out->mY = out->mZ = 0.0f;
        break;
    }
}
}

extern "C" {
void fn_80100AA0(Object_80039F5C *p,int,float *a,float *b)
{
    float rating=1.0f-(float)p->mRatings[6]*0.00392156886f;
    *a=1.0f-lbl_803EAEA8*rating;*b=1.0f-lbl_803EAEAC*rating;
}
}

extern "C" unsigned int fn_80100B0C(void)
{
    return fn_802372EC(0, 0x1000000);
}

extern "C" {
void fn_80100B34(Object_80039F5C *p,float *out,float *maximum,float a,float b,float c)
{
    if(out && maximum) {
        a += (1.0f - (float)p->mRatings[6] * 0.00392156886f) * 0.3f + 0.05f;
        a += (1.0f - b) * 0.2f;
        *maximum = c * a * lbl_803EAEB0;
        *out = fn_80237260(0) * *maximum;
    }
}
}

extern "C" {
void fn_80100BF8(Object_80039F5C *p, float, Vector_80039F5C *point, Point_8017886C *offset, float factor, float skill)
{
    float error = 0.0f;
    float amount = 0.0f;
    float maximum = 0.0f;
    Vector_80039F5C delta;
    Point_8017886C combined;
    Point_8017886C unused;
    Point_8017886C final;
    float distance;
    float length;
    float ratio;

    if (fn_800A7F1C(p->mIdBytes[2]) == 2) {
        return;
    }
    fn_802276B4(&delta, point, &p->mMotion.mPos);
    distance = fn_802270A4(&delta);
    length = factor * (lbl_803EAEB8 - lbl_803EAEB4) + lbl_803EAEB4;
    ratio = distance / length;
    length *= (float)fn_802372EC(0, 7) * 0.01f + 1.0f;
    if (ratio > 0.9f) {
        error = 0.05f;
        if (ratio > 1.0f) {
            error += 0.1f;
            length *= 1.0f - fn_80237260(0) * error * lbl_803EAEBC;
            distance = length;
            fn_80227538((Point_8017886C *)&delta, fn_801CFE40(delta.mY, delta.mX), length);
            fn_80227638(point, &delta, &p->mMotion.mPos);
        }
    }
    fn_80100B34(p, &amount, &maximum, error, skill, distance);
    fn_80227538((Point_8017886C *)&delta, fn_80100B0C(), amount);
    fn_80227638(&combined, &delta, offset);
    fn_80227690(&unused, point, offset);
    if (fn_802270A4(&combined) > maximum && amount > fn_802270A4(offset)) {
        fn_80227538((Point_8017886C *)&delta, fn_801CFE40(combined.mY, combined.mX), maximum);
        fn_80227690(&delta, &delta, offset);
    }
    fn_80227638(point, &delta, point);
    fn_80227690(&final, point, &p->mMotion.mPos);
    if (fn_802270A4(&final) > length || ratio > 1.0f) {
        fn_80227538((Point_8017886C *)point, fn_801CFE40(final.mY, final.mX), length);
        fn_80227638(point, point, &p->mMotion.mPos);
    }
}
}

extern "C" {
Object_80039F5C *fn_80100EA0(Object_80039F5C *p, int angle)
{
    Object_80039F5C *players[3];
    unsigned char active;
    Point_8017886C center;
    Point_8017886C delta;
    Point_8017886C minimum;
    Point_8017886C maximum;
    unsigned char i;
    int best;
    Object_80039F5C *result;

    minimum.mX = 100.0f;
    minimum.mY = 100.0f;
    maximum.mX = -100.0f;
    maximum.mY = -100.0f;
    for (i = 0; i < 3; i++) {
        unsigned int index = PlayBookGetReceiver(p->mIdBytes[2], i, &active);

        if (index != 255 && active) {
            Object_80039F5C *other = PlyrGet(p->mIdBytes[2], (unsigned short)index);
            Vector_80039F5C *pos = &other->mMotion.mPos;

            players[i] = other;
            if (pos->mX < minimum.mX) {
                minimum.mX = pos->mX;
            }
            if (pos->mY < minimum.mY) {
                minimum.mY = pos->mY;
            }
            if (pos->mX > maximum.mX) {
                maximum.mX = pos->mX;
            }
            if (pos->mY > maximum.mY) {
                maximum.mY = pos->mY;
            }
        } else {
            players[i] = 0;
        }
    }
    center.mX = (maximum.mX - minimum.mX) * 0.5f + minimum.mX;
    center.mY = (maximum.mY - minimum.mY) * 0.5f + minimum.mY;
    best = 0x800000;
    result = 0;
    for (i = 0; i < 3; i++) {
        if (players[i]) {
            int difference;

            fn_80227690(&delta, &players[i]->mMotion.mPos, &center);
            difference = MathAngleDiff(angle, fn_801CFE40(delta.mY, delta.mX));
            if (difference < best) {
                result = players[i];
                best = difference;
            }
        }
    }
    return result;
}
}

extern "C" {
void fn_80101064(Object_80039F5C *p)
{
    int team=fn_80178320(),n=fn_80178D18(team);
    for(unsigned int i=0;(int)i<n;++i) {
        Object_80039F5C *other=PlyrGet(team,(unsigned char)i);
        Point_8017886C delta;fn_80227690(&delta,&other->mMotion.mPos,&p->mMotion.mPos);
        if(!(fn_802270A4(&delta)>=2.5f)) {
            Record_800B15FC *record=fn_800B15FC();fn_8009BD2C(other,&record->mUnknown0);
            record->mUnknownC=p->mMotion.mPos.mX;record->mUnknown10=p->mMotion.mPos.mY;record->mUnknown14=33;
            fn_800B1508();return;
        }
    }
}
}

extern "C" {
void fn_80101130(Object_80039F5C *p, Object_80039F5C *other, unsigned short *out)
{
    Directions_8012430C values;
    unsigned char best;
    unsigned int facing;
    Lookup_8012078C *lookup;
    Object_80039F5C *receiver;
    Point_8017886C delta;
    unsigned int octant;
    int difference;
    float left = 0.0f;
    float right = 0.0f;
    int chosen = 0;
    int forward = 0;

    fn_8012430C(&values, 3, p);
    best = fn_801243E0(&values, -1);
    facing = ((unsigned int)p->mMotion.mUnknown32 + 0x100000) >> 21 & 7;
    lookup = fn_8012078C();
    receiver = PlyrGet(fn_80178320(), lookup->mpUnknown4[1]);
    fn_80227690(&delta, &other->mMotion.mPos, &p->mMotion.mPos);
    octant = ((unsigned int)fn_801CFE40(delta.mY, delta.mX) + 0x100000) >> 21 & 7;
    difference = MathAngleDiff(p->mMotion.mUnknown32, 0x400000);
    if ((values.mCost[best] == 0.0f || values.mCost[(best + 1) & 7] == 0.0f || values.mCost[(best + 7) & 7] == 0.0f)
        && (values.mCost[octant] >= 3.0f || values.mCost[(octant + 1) & 7] >= 4.0f || values.mCost[(octant + 7) & 7] >= 4.0f)
        && difference < 0x4AAAAB) {
        chosen = 1;
    }
    if (!chosen) {
        int pastRight = p->mMotion.mPos.mX > fn_80178A5C() + (fn_80178A08() - fn_80178A5C()) * 0.25f;
        int pastLeft = p->mMotion.mPos.mX < -(fn_80178A5C() + (fn_80178A08() - fn_80178A5C()) * 0.25f);
        left = fn_801242E0(&values, 0);
        right = fn_801242E0(&values, 4);

        if (((pastLeft && left > right * 1.45f) || (pastRight && right > left * 1.45f)) && difference < 0xE38E3) {
            chosen = 1;
        }
    }
    if (!chosen) {
        if (p->mMotion.mPos.mY < fn_80177FE0().mY) {
            forward = 1;
        }
    }
    if (chosen) {
        if (facing == 2 && p->mMotion.mPos.mY > receiver->mMotion.mPos.mY
            && p->mMotion.mPos.mY < fn_80178A2C() - 15.0f) {
            *out = 5;
        }
    } else if (forward) {
        *out = 12;
    }
}
}

extern "C" {
void fn_80101408(Object_80039F5C *p,Point_8017886C *point,int *angle)
{
    if(point && angle) {
        point->mX=fn_80178A08()+14.0f;
        point->mY=fn_80177FE0().mY+10.0f;
        if(!(p->mMotion.mPos.mX>=0.0f))point->mX=-point->mX;
        fn_80227690(point,point,&p->mMotion.mPos);
        *angle=(fn_801CFE40(point->mY,point->mX)-p->mMotion.mFacing)&0xFFFFFF;
    }
}
}

extern "C" {
void fn_801014C8(Object_80039F5C *p,Point_8017886C *point,int *angle)
{
    if(point && angle) {
        Point_8017886C target;target.mX=0.0f;
        target.mY=(fn_80178A2C()+fn_80178A44())*0.5f;
        fn_80227690(point,&target,&p->mMotion.mPos);
        *angle=(fn_801CFE40(point->mY,point->mX)-p->mMotion.mFacing)&0xFFFFFF;
    }
}
}

extern "C" {
void fn_80101568(Object_80039F5C *p, unsigned char *kind, Point_8017886C *point, int *angle)
{
    Vector_80039F5C target;

    target.mX = target.mY = target.mZ = 0.0f;
    if (point && angle && kind) {
        State_800FDA58 *state = (State_800FDA58 *)&p->mUnknown336;
        Ball_t *ball = BallFindHeldBy(p);
        Record_8011F4F8 *record = fn_8011F4F8(state->mUnknown3Byte);
        Object_80039F5C *other = PlyrGet(p->mIdBytes[2], (unsigned char)record->mUnknownA[0]);
        float speed;

        if (state->mUnknown0Bytes[0]) {
            speed = gFrameTimeScale * 0.3f;
        } else {
            speed = AssignGetPassSpeed(p, other, 0.9f, &record->mUnknown8);
        }
        if (ball) {
            fn_801007A4(ball, p, other, speed, &target, kind);
        } else {
            target.mX = other->mMotion.mPos.mX;
            target.mY = other->mMotion.mPos.mY;
        }
        fn_80227690(point, &target, &p->mMotion.mPos);
        fn_801CFE40(point->mY, point->mX);
        *angle = (fn_801CFE40(point->mY, point->mX) - p->mMotion.mFacing) & 0xFFFFFF;
        if (*angle > 0x1000000) {
            *angle -= 0x1000000;
        }
    }
}
}

extern "C" {
void fn_801016A4(Object_80039F5C *p, unsigned char *kind, Point_8017886C *point, int *angle)
{
    if (!p || !kind || !point || !angle) {
        return;
    }
    *angle = 0;
    point->mY = point->mX = 0.0f;
    switch (*kind) {
    case 2:
    case 5:
        *angle = 0;
        break;
    case 3:
        fn_80101408(p, point, angle);
        break;
    case 8:
        fn_801014C8(p, point, angle);
        break;
    case 0:
    case 1:
    case 4:
    case 6:
    case 7:
        fn_80101568(p, kind, point, angle);
        break;
    }
}
}

extern "C" {
void fn_8010176C(Object_80039F5C *p, int mode, Point_8017886C *point)
{
    if (!p) {
        return;
    }
    switch (mode) {
    case 4:
        if (fn_801BE648(p->mpUnknown792) == 69) {
            p->mUnknown1008.mUnknown1 = 10;
        } else {
            p->mUnknown1008.mUnknown1 = 1;
        }
        break;
    case 2:
        p->mUnknown1008.mUnknown1 = 3;
        break;
    case 5:
        p->mUnknown1008.mUnknown1 = 4;
        break;
    default: {
        State_800FDA58 *state = (State_800FDA58 *)&p->mUnknown336;
        Record_8011F4F8 *record = fn_8011F4F8(state->mUnknown3Byte);
        Object_80039F5C *other = 0;
        float distance;

        if (record && (unsigned char)record->mUnknownA[0] != 15) {
            other = PlyrGet(p->mIdBytes[2], (unsigned char)record->mUnknownA[0]);
        }
        if (other) {
            int near = other->mMotion.mPos.mY < fn_80177FE0().mY + 24.0f && fn_802270A4(point) < 32.0f;

            if (near) {
                distance = 24.0f;
            } else {
                distance = fn_802270A4(point);
            }
        } else {
            distance = fn_802270A4(point);
        }
        p->mUnknown1008.mUnknown1 = distance <= 24.0f ? 5 : 1;
        break;
    }
    }
}
}

extern "C" int fn_801018B4(Object_80039F5C *p, List_801018B4 *pList, int a, int b, int *pOut)
{
    int flag = p->mUnknown2913 == 0;
    int bestScore = -1;
    int bestValue = 0x800000;
    int bestIndex = -1;
    unsigned char bestByte = 1;
    int i;

    for (i = 0; i < pList->mCount; i++) {
        Entry_801018B4 *pEntry = pList->mItems[i].mpEntry;
        int score = 0;
        int value;
        unsigned char byte5;

        if (flag != pEntry->mUnknown16 || p->mUnknown1008.mUnknown0 != pEntry->mUnknown4) {
            continue;
        }
        value = MathAngleDiff(p->mMotion.mUnknown32 - ((p->mMotion.mFacing + fn_800C8BAC(p, 0)) & 0xFFFFFF),
                            pEntry->mUnknown8);
        *pOut = value;
        if (p->mUnknown1008.mUnknown0 == 1 || p->mUnknown1008.mUnknown0 == 2 || value <= 0x3FFFFF) {
            score = 6;
        }
        value = MathAngleDiff(b, pEntry->mUnknown12);
        *pOut = value;
        if (pEntry->mUnknown6 == 2 && value > 0x160B60 && value <= 0x7FFFFF) {
            *pOut = 0x160B60;
        }
        if (*pOut > bestValue && (bestByte != p->mUnknown1008.mUnknown1 || *pOut - bestValue > 0x155554)) {
            continue;
        }
        byte5 = pEntry->mUnknown5;
        if (p->mUnknown1008.mUnknown1 == byte5) {
            if (byte5 != 10
                || (p->mUnknown2913 == 0
                    && MathAngleDiff(p->mMotion.mFacing, 0) <= 0x3FFFFF)
                || (p->mUnknown2913 == 1
                    && MathAngleDiff(p->mMotion.mFacing, 0x800000) <= 0x3FFFFF)) {
                score += 3;
            }
        } else {
            switch (p->mUnknown1008.mUnknown1) {
            case 3:
            case 4:
                break;
            default:
                if (p->mUnknown1008.mUnknown1 == 10 || byte5 != 10) {
                    switch (byte5) {
                    case 8:
                    case 9:
                        score += 1;
                        break;
                    default:
                        score += 2;
                        break;
                    }
                } else {
                    score = -2;
                }
                break;
            }
        }
        if (score > bestScore || (score == bestScore && *pOut < bestValue)) {
            bestByte = pEntry->mUnknown5;
            bestScore = score;
            bestValue = *pOut;
            bestIndex = i;
        }
    }
    return bestIndex;
}

extern "C" void fn_80101AE0(Object_80039F5C *p, float *pOut)
{
    if (p && pOut) {
        short rating = p->mRatings[6];
        short value = rating < lbl_803EAE88 ? lbl_803EAE88 : (rating > 255 ? 255 : rating);

        *pOut = (float)(value - lbl_803EAE88) / (float)(255 - lbl_803EAE88);
    }
}

extern "C" int fn_80101B7C(Object_80039F5C *p)
{
    int flag = p->mUnknown776 == 1;
    unsigned char saved = p->mUnknown1008.mUnknown0;
    State_80101B7C *pState = (State_80101B7C *)&p->mUnknown336;
    Command_800CEE74 command;
    int value;
    int b;
    int index;
    int result;

    fn_800CEE74(&command, p, 0, 0, 0, 235, flag);
    result = 1;
    p->mUnknown1008.mUnknown0 = pState->mUnknown8 = fn_80101C40(p);
    index = fn_800C3BEC(p, &command, &value, &b);
    if (index == -1) {
        result = 0;
    }
    if (result != 0) {
        fn_800C39E0(p, 235, index, value, flag);
    } else {
        p->mUnknown1008.mUnknown0 = saved;
    }
    return result;
}

extern "C" int fn_80101C40(Object_80039F5C *p)
{
    int flag = p->mUnknown776 == 1;

    if ((p->mMotion.mPos.mX >= 0.0f && p->mMotion.mFacing <= 0x800000)
        || (p->mMotion.mPos.mX < 0.0f && p->mMotion.mFacing > 0x800000)) {
        return flag ? 1 : 3;
    }
    return flag ? 3 : 1;
}

extern "C" int fn_80101CB4(Object_80039F5C *p)
{
    Object_80039F5C *pOther = 0;
    State_800FDA58 *pState;
    Record_8011F4F8 *pRequest;
    AnimChannel_t *pChannels;
    unsigned char hasBall;
    int kind;
    unsigned char mode;
    int anim;

    if (fn_800AD9B4() != 3 || fn_800FFFB0(p) == 0) {
        return 1;
    }
    pState = (State_800FDA58 *)&p->mUnknown336;
    pState->mUnknown3Byte = BallGetIndex(BallFindHeldBy(p));
    pRequest = fn_8011F4F8(pState->mUnknown3Byte);
    p->mFlags &= ~0x1000;
    p->mFlags &= ~4;
    pRequest->mUnknown8 = p->mpState->mUnknown3[0];
    if (pRequest->mUnknown8 == 0) {
        pState->mUnknown0Bytes[0] = 1;
    } else {
        pState->mUnknown0Bytes[0] = 0;
    }
    pState->mUnknown2 = pState->mUnknown0Bytes[1] = 0;
    pState->mUnknown4 = 0;
    pRequest->mUnknownB = 1;
    pRequest->mUnknownAByte = p->mpState->mUnknown2;
    pRequest->mUnknown1D = p->mpState->mUnknown1;
    pRequest->mUnknownC = 0.0f;
    pRequest->mUnknown10 = 0;
    if (pRequest->mUnknownAByte != 15) {
        pOther = PlyrGet(p->mIdBytes[2], pRequest->mUnknownAByte);
        pRequest->mUnknown14 = pOther->mMotion.mUnknown40;
        pRequest->mUnknown18 = pOther->mMotion.mUnknown44;
        pRequest->mUnknown1C[0] = pOther->mpState->mId == 20;
        if (pOther->mpState->mId == 51) {
            pOther->mFlags |= 0x80000000;
        }
    } else {
        pRequest->mUnknown14 = pRequest->mUnknown18 = 0.0f;
        pRequest->mUnknown1C[0] = 0;
    }
    kind = PlayerMoveGetKind(p);
    hasBall = kind;
    fn_8009BD60(p);
    p->mFlags &= ~4;
    if (p->mpState->mUnknown1 != 2 && p->mpState->mUnknown1 != 5) {
        if (fn_801BE648(p->mpUnknown792) == 0xDE && PlayerMoveGetKind(p) == 0) {
            mode = 8;
        } else if (p->mMotion.mUnknown28 > lbl_803EC9E8) {
            switch (fn_801BE648(p->mpUnknown792)) {
            case 0x54:
                if (MathAngleDiff(p->mMotion.mFacing, p->mMotion.mUnknown32) <= 0x3FFFFF
                    && p->mMotion.mUnknown32 > 0x238E39 && p->mMotion.mUnknown32 <= 0x58E38D) {
                    mode = 2;
                } else {
                    mode = 3;
                }
                break;
            case 0x4A:
            default:
                if (p->mMotion.mUnknown28 > 40.0f / (210.0f / gFrameTimeScale) * 0.25f) {
                    if (fn_800CA5CC(p, 5, 1) != 0) {
                        mode = 5;
                    } else if (p->mUnknown2913 == 1
                               && MathAngleDiff(p->mMotion.mUnknown32, 0) <= 0x2AAAA9) {
                        mode = 5;
                    } else if (p->mUnknown2913 == 0
                               && MathAngleDiff(p->mMotion.mUnknown32, 0x800000) <= 0x2AAAA9) {
                        mode = 5;
                    } else {
                        mode = 2;
                    }
                } else {
                    mode = 2;
                }
                break;
            }
        } else {
            mode = 2;
        }
    } else {
        mode = 1;
    }
    p->mUnknown1008.mUnknown0 = mode;
    if (hasBall) {
        if (kind == 4) {
            if (fn_80101B7C(p) != 0) {
                anim = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, 0xEB, 0);
                p->mFlags |= 8;
                AudmonEventPostId(0x32, &p->mMotion.mPos, p->mId, 0, 0, 0);
                fn_800A2190(0);
            } else {
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 0xB2, 1.0f, p);
                anim = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, 0xB2, 0);
                TutorialSetMoveDone(0x19, 1);
            }
        } else {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 0xB2, 1.0f, p);
            anim = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, 0xB2, 0);
            TutorialSetMoveDone(0x19, 1);
        }
        if (anim == 0xFFFF) {
            anim = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, 0x45, 0);
        }
    } else {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 0x45, 1.0f, p);
        anim = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, 0x45, 0);
    }
    pChannels = p->mpUnknown800;
    if (pRequest->mUnknown1D != 4 && fn_801BE648(p->mpUnknown792) != 0xEB) {
        AnimSeqSetSpeed(&pChannels[anim].mUnknown4C, MathInverse(lbl_803EAEC0));
    }
    if (pRequest->mUnknownAByte != 15) {
        switch (p->mpState->mUnknown1) {
        case 0:
        case 1:
        case 6:
        case 7:
            fn_80100AA0(p, (int)&pOther->mMotion.mPos, &pRequest->mUnknown0, &pRequest->mUnknown4);
            break;
        }
    } else {
        pRequest->mUnknown0 = pRequest->mUnknown4 = 1.0f;
    }
    fn_800A3B58(p, 3, 0);
    return 0;
}

extern "C" int fn_801021C0(Object_80039F5C *p)
{
    State_801021C0 *pState = (State_801021C0 *)&p->mUnknown336;

    if (fn_800FFFB0(p)) {
        Record_8011F4F8 *pRecord;
        unsigned char kind;

        if (fn_800AD9B4() != 3) {
            return 1;
        }
        pRecord = fn_8011F4F8(pState->mUnknown3);
        kind = pRecord->mUnknown1D;
        if (p->mFlags & 0x1000) {
            fn_80103CB0(p);
            pState->mUnknown4 = 0;
            p->mFlags &= ~0x1000;
            pRecord->mUnknownB = 0;
        }
        if ((p->mFlags & 0x2000) && kind == 4) {
            fn_800A5A8C(2, p, PlyrGet(p->mIdBytes[2], (unsigned char)pRecord->mUnknownA[0]));
            StyleTrackerOnPumpFake(p);
            if (p->mFlags & 0x4000) {
                PassIconsShow(0);
            }
        }
        if (p->mFlags & 4) {
            if (fn_801BE648(p->mpUnknown792) == 235) {
                p->mFlags = (p->mFlags & ~4) | 8;
                p->mUnknown1008.mUnknown0 = pState->mUnknown11;
                p->mUnknown1008.mUnknown1 = 1;
                p->mUnknown1008.mUnknown2 = 1;
                p->mUnknown1011 = 6;
                fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 236, 1.0f, p);
            } else {
                if (kind == 4) {
                    p->mFlags &= ~0x2000;
                }
                p->mFlags &= ~4;
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                p->mUnknown512.mUnknown0 = 0.0f;
                return 1;
            }
        }
    } else {
        Object_80039F5C *pOther;

        pState->mUnknown4++;
        pOther = fn_8009BCE8(&p->mUnknown560.mUnknown40);
        if (pOther && (pOther->mpState->mId == 12 || p->mUnknown560.mUnknown32 > gPlyrMoveFwdSpeed * 50310.56f)) {
            switch (p->mUnknown560.mUnknown55) {
            case 0:
            case 5:
            case 7:
                if (pState->mUnknown4 > fn_80104610(p)) {
                    PenaltyRollRoughing(pOther);
                }
                pState->mUnknown2 = 1;
                if (fn_800E96EC(p, pOther) == 1) {
                    Record_800B15FC *pEvent = fn_800B15FC();

                    fn_8009BD2C(pOther, &pEvent->mUnknown0);
                    pEvent->mUnknownC = p->mMotion.mPos.mX;
                    pEvent->mUnknown10 = p->mMotion.mPos.mY;
                    pEvent->mUnknown14 = 34;
                    fn_800B1508();
                } else {
                    pState->mUnknown2 = 0;
                }
                break;
            }
        }
        p->mFlags &= ~0x3000;
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = 0.0f;
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_80102470(Object_80039F5C *p)
{
    State_80102470 *pState = (State_80102470 *)&p->mUnknown336;
    unsigned int flags;

    if (pState->mUnknown2 != 0 || fn_800FFFB0(p) == 0) {
        flags = p->mFlags;
        p->mFlags = flags & ~0x2000;
        if (flags & 0x4000) {
            int facing = p->mMotion.mFacing;

            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = facing;
            p->mUnknown512.mUnknown4 = facing;
            p->mUnknown512.mUnknown0 = 0.0f;
        }
        p->mFlags &= ~8;
        return 1;
    }
    return 0;
}

extern "C" void fn_801024FC(Object_80039F5C *p, int kind, int b, int c, int d)
{
    Message_800F01CC message;

    p->mUnknown512.mUnknown14 = 0;
    PlayerMoveBegin(p, d, 15);
    memset(&message, 0, 4);
    message.mId = 15;
    message.mUnknown1[0] = kind;
    message.mUnknown1[1] = b;
    message.mUnknown1[2] = c;
    if (fn_801486A0() == 1 && p->mpState->mId == 51) {
        fn_800F01CC(0, p->mpState, &message, p);
        return;
    }
    switch (kind) {
    case 4: {
        Record_800B15FC *pRecord;

        fn_800F00D4(0, p->mpState, &message, p);
        pRecord = fn_800B15FC();
        fn_8009BD2C(p, &pRecord->mUnknown0);
        pRecord->mUnknownC = p->mMotion.mPos.mX;
        pRecord->mUnknown10 = p->mMotion.mPos.mY;
        pRecord->mUnknown14 = 61;
        fn_800B1508();
        break;
    }
    case 5:
        fn_800F05E4(0, p->mpState, &message, p);
        break;
    default:
        StyleTrackerSetStylePassPending(PlayerMoveGetKind(p));
        CamGameSetModeAll(3);
        fn_800F053C(0, p->mpState, &message, p);
        memset(&message, 0, 4);
        message.mId = 33;
        fn_800F01CC(0, p->mpState, &message, p);
        break;
    }
}

extern "C" int fn_80102664(Object_80039F5C *p)
{
    State_80102664 *pState = (State_80102664 *)&p->mUnknown336;
    Record_8011F4F8 *pRecord = fn_8011F4F8(pState->mUnknown3);

    if (pState->mUnknown0 == 1 && pRecord->mUnknownAByte != 15) {
        Input_800B6D34 input;
        unsigned char i;
        unsigned int bit;

        fn_800B6D34(p, &input);
        for (i = 0; i <= 2; i++) {
            int index = PlayBookGetReceiver(p->mIdBytes[2], i, 0);

            if (pRecord->mUnknownAByte == index) {
                break;
            }
        }
        pRecord->mUnknown8++;
        bit = lbl_802DAB54[i];
        if (((&input.mUnknown92)[bit >> 3] & (1 << (bit & 7))) != (1 << (bit & 7))) {
            pState->mUnknown0 = 0;
            if (fn_800FFFB0(p) != 0 && (pRecord->mUnknown1D != 4 && pRecord->mUnknown1D != 5)) {
                TutorialSetMoveDone(29, 1);
            }
        }
    } else if (pRecord->mUnknown1D != 4 && pRecord->mUnknown1D != 5 && fn_800FFFB0(p) == 0) {
        fn_800B7F34(p);
    }
    return 0;
}

extern "C" int fn_8010279C(Object_80039F5C *p)
{
    Input_800B6D34 input;
    int d = 0;
    unsigned char i;

    fn_800B6D34(p, &input);
    if ((input.mUnknown96 & 1) || (input.mUnknown96 & 0x10)) {
        d = 4;
    }
    if (PassIconsAreShown() == 0) {
        if ((PassIconsWereShown() == 1 && (input.mUnknown94 & 1) && fn_800A61E0() == 0)
            || (PassIconsWereShown() == 0 && (input.mUnknown93 & 0x40) && fn_800A61E0() == 0)) {
            PassIconsShow(0);
            CamGameSetModeAll(2);
        } else if (PlayerActionAnimIsPassReady(p) == 0) {
            return fn_800B76E8(p);
        }
    } else if (fn_800FFFB0(p) != 0) {
        for (i = 0; i <= 2; i++) {
            unsigned int bit;

            if (input.mUnknown94 & 8) {
                Object_80039F5C *pTarget = fn_80100EA0(p, p->mMotion.mFacing);

                PassIconsHide();
                PassIconsClearReplayFlag();
                QbPassRestoreReceiverOptions(p);
                if (pTarget != 0) {
                    fn_801024FC(p, 4, pTarget->mIdBytes[1], 0, d);
                }
                return 0;
            }
            bit = lbl_802DAB48[i];
            if (((&input.mUnknown92)[bit >> 3] & (1 << (bit & 7))) == (1 << (bit & 7))) {
                unsigned char valid;
                int index = PlayBookGetReceiver(p->mIdBytes[2], i, &valid);

                if (valid != 0 && index != 255 && fn_801000EC(PlyrGet(fn_80178308(), index)) == 0) {
                    if (input.mUnknown94 & 4) {
                        fn_801024FC(p, 4, index, 0, d);
                    } else {
                        fn_801024FC(p, 0, index, 0, d);
                        if (PlayerMoveGetKind(p) == 0) {
                            switch (i) {
                            case 0:
                                TutorialSetMoveDone(26, 1);
                                break;
                            case 1:
                                TutorialSetMoveDone(27, 1);
                                break;
                            case 2:
                                TutorialSetMoveDone(28, 1);
                                break;
                            }
                        }
                    }
                    return 0;
                }
            }
        }
        if (input.mUnknown94 & 2) {
            fn_801024FC(p, 3, 15, 0, 0);
            return 0;
        }
        if (input.mUnknown93 & 0x80) {
            PassIconsHide();
            CamGameSetModeAll(1);
            TutorialSetMoveDone(19, 1);
        }
        if ((input.mUnknown95 & 8) && fn_800CA5CC(p, 0, 1) != 0) {
            p->mUnknown512.mUnknown15 = 1;
        }
    }
    fn_800B6E68(p, &input);
    return 0;
}

extern "C" int fn_80102A78(List_801018B4_80102A78 *pList, unsigned short animation, void *pData, AnimChannel_t *pEntries,
                           Object_80039F5C *p, unsigned int mode)
{
    int delta = 0;
    unsigned int angle = 0;
    int failed = 0;
    State_80102A78 *pState = (State_80102A78 *)fn_801BE60C(p->mpUnknown792, animation);

    switch (mode) {
    case 0: {
        Record_8011F4F8 *pRecord = fn_8011F4F8(((State_80102664 *)&p->mUnknown336)->mUnknown3);
        unsigned char kind = pRecord->mUnknown1D;
        Point_8017886C point;
        int index;
        Entry_801018B4_80102A78 *pEntry;

        fn_801016A4(p, &kind, &point, (int *)&angle);
        fn_8010176C(p, kind, &point);
        index = fn_801018B4(p, (List_801018B4 *)pList, 0, angle, &delta);
        if (index == -1) {
            index = 0;
        }
        pEntry = pList->mItems[index].mpEntry;
        if (animation == 178 && fn_80100024(p, angle, pEntry->mUnknown7) == 0) {
            failed = 1;
        }
        if (failed) {
            PlayerMoveBegin(p, 0, 0);
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 69, 1.0f, p);
        } else if (index != -1) {
            StyleTrackerSetPassSubtype(pEntry->mUnknown7);
            pState->mUnknown20 = pEntry->mUnknown20;
            pState->mUnknown24 = pEntry->mUnknown24;
            pState->mUnknown28 = pState->mUnknown24 - pState->mUnknown20;
            pState->mUnknown32 = 0.0f;
            pState->mUnknown8 = pEntry->mUnknown12;
            pState->mUnknown16 = p->mMotion.mFacing;
            pState->mUnknown12 = failed;
            pState->mUnknown36 = pRecord->mUnknown1D;
            if (pState->mUnknown28 != 0.0f) {
                delta = (angle - pState->mUnknown8) & 0xFFFFFF;
                if (delta > ((0x1000000 - delta) & 0xFFFFFF)) {
                    delta = -((0x1000000 - delta) & 0xFFFFFF);
                }
                pState->mUnknown4 = (int)(delta / pState->mUnknown28);
                fn_801BE760(p->mpUnknown792, animation, 1);
            } else {
                pState->mUnknown4 = failed;
            }
            pState->mUnknown0 = AnimChanStartAnim(pData, pEntries, pList->mItems[index].mUnknown0,
                                            pList->mItems[index].mUnknown2, animation, p, 1.0f);
            AnimSeqSetSpeed(&pEntries[pState->mUnknown0].mUnknown4C, MathInverse(lbl_803EAEC4));
        }
        break;
    }
    case 1:
        break;
    case 2:
        if (fn_801BE648(p->mpUnknown792) == animation) {
            float time = AnimSeqGetTime(&p->mpUnknown800[pState->mUnknown0].mUnknown4C);
            float previous = pState->mUnknown32;

            pState->mUnknown32 = time;
            if (time > pState->mUnknown20 && previous < pState->mUnknown24) {
                int step = pState->mUnknown4;

                p->mMotion.mFacing = (p->mMotion.mFacing + step) & 0xFFFFFF;
                p->mpUnknown800[pState->mUnknown0].mUnknownC = (p->mpUnknown800[pState->mUnknown0].mUnknownC + step) & 0xFFFFFF;
            }
        }
        break;
    }
    return 0;
}

extern "C" void fn_80102D78(Object_80039F5C *p)
{
    int result[2] = {0, 0};
    Object_80039F5C *pTarget = 0;
    Ball_t *pBall = BallFindHeldBy(p);
    Record_8011F4F8 *pRecord = fn_8011F4F8(BallGetIndex(pBall));
    Record_800B15FC *pEvent;
    Vector_80039F5C ball;
    Vector_80039F5C delta;
    Vector_80039F5C velocity;
    Vector_80039F5C target;
    float speed;
    float spin;
    float random;
    int side;

    fn_800A8954(5, p->mIdBytes[2], p);
    PassIconsHide();
    PassIconsClearReplayFlag();
    fn_800B260C(0);
    BallReleaseStill(pBall, 4, 0);
    pEvent = fn_800B15FC();
    if (TutorialAreMovesDone(0x20000000) == 0) {
        TutorialSetMoveDone(42, 1);
    }
    fn_8009BD2C(p, &pEvent->mUnknown0);
    pEvent->mUnknownC = p->mMotion.mPos.mX;
    pEvent->mUnknown10 = p->mMotion.mPos.mY;
    pEvent->mUnknown4 = pRecord->mUnknown1D;
    switch (pRecord->mUnknown1D) {
    case 0:
    case 1:
    case 6:
    case 7:
        pTarget = PlyrGet(p->mIdBytes[2], pRecord->mUnknownAByte);
        if (!(p->mFlags & 0x4000)) {
            fn_80101130(pTarget, p, (unsigned short *)&pRecord->mUnknown8);
        }
        speed = AssignGetPassSpeed(p, pTarget, pRecord->mUnknown0, &pRecord->mUnknown8);
        pEvent->mUnknown8 = (int)pTarget;
        if (PlayerMoveGetKind(p) != 0) {
            AudmonEventPostId(40, &p->mMotion.mPos, p->mId, 0, 0, 0);
        }
        break;
    case 8:
        speed = gFrameTimeScale * 0.27f;
        pEvent->mUnknown8 = (int)pTarget;
        break;
    default:
        speed = gFrameTimeScale * 0.37f;
        pEvent->mUnknown8 = 0;
        break;
    }
    pEvent->mUnknown14 = 5;
    pEvent->mUnknown16 = (int)(speed * 256.0f);
    fn_800B1508();
    spin = fn_80237260(0) * 0.2f;
    spin += p->mMotion.mUnknown28 * 0.1f / gPlyrMoveFwdSpeed;
    spin += p->mUnknown560.mUnknown32 * 0.15f / (gPlyrMoveFwdSpeed * 100621.1171875f);
    spin += (1.0f - pRecord->mUnknown4) * 0.2f * 2.0f;
    spin += pRecord->mUnknownC;
    random = fn_80237260(0);
    spin = AddRatingNoise_80102D78(spin, random, p->mRatings[6]);
    if (fn_800A7F1C(p->mIdBytes[2]) == 0) {
        spin = lbl_803EAEC8;
    }
    side = -4;
    if (p->mUnknown2913 == 1) {
        side = 4;
    }
    if (fn_800A7F1C(p->mIdBytes[2]) == 2) {
        spin = 0.0f;
        side = (int)(side * 3.0f);
    }
    if (pRecord->mUnknownC > 0.0f) {
        fn_800B1584(56, 0);
        fn_801783D0(23, 1);
    }
    switch (pRecord->mUnknown1D) {
    case 0:
    case 6:
        if (pTarget->mpState->mId == 20) {
            if (pRecord->mUnknown1D == 0) {
                pRecord->mUnknown1D = 1;
            } else {
                pRecord->mUnknown1D = 7;
            }
        }
        /* fall through */
    case 1:
    case 7: {
        Object_800B26B0 *pMotion = &pTarget->mMotion;
        Vector_80039F5C *pPos;
        float limit;
        float distance;
        float ratio;
        float maximum;

        if (pRecord->mUnknown1D == 1 || pRecord->mUnknown1D == 7) {
            fn_80100370(pBall, pTarget, speed, &target);
        } else {
            Vector_80039F5C offset;
            int angle;
            float length;

            if ((int)pTarget->mFlags >= 0) {
                if (pTarget->mpState->mId == 19) {
                    angle = (pTarget->mpState->mUnknown2 << 17) & 0xFE0000;
                } else {
                    angle = pMotion->mUnknown32;
                }
                if (pTarget->mpState->mId == 20) {
                    length = pTarget->mMotion.mUnknown28 >= PlyrMoveGetRatedSpeed(pTarget, 0.72f, 1.0f)
                        ? pTarget->mMotion.mUnknown28 : PlyrMoveGetRatedSpeed(pTarget, 0.72f, 1.0f);
                } else {
                    length = pTarget->mMotion.mUnknown28;
                }
            } else {
                angle = fn_801CFE40(pRecord->mUnknown18, pRecord->mUnknown14);
                length = fn_802270A4(&pRecord->mUnknown14);
            }
            fn_80227538((Point_8017886C *)&offset, angle, length);
            offset.mZ = 0.0f;
            fn_80103F80(pBall, pMotion->mPos, offset, length, angle, speed, &target, pTarget);
        }
        fn_8010016C(pTarget, (Point_8017886C *)&target, p, speed);
        limit = 1.0f - fn_80237260(0) * 2.5f;
        target.mX = target.mX > fn_80178A08() + limit ? fn_80178A08() + limit : target.mX;
        target.mX = target.mX < -(fn_80178A08() + limit) ? -(fn_80178A08() + limit) : target.mX;
        target.mY = target.mY > fn_80178A44() + limit ? fn_80178A44() + limit : target.mY;
        fn_80100BF8(p, speed, &target, (Point_8017886C *)result, pRecord->mUnknown0, pRecord->mUnknown4);
        target.mX = target.mX > fn_80178A08() + 3.0f ? fn_80178A08() + 3.0f : target.mX;
        target.mX = target.mX < -(fn_80178A08() + 3.0f) ? -(fn_80178A08() + 3.0f) : target.mX;
        target.mY = target.mY > fn_80178A44() + 2.5f ? fn_80178A44() + 2.5f : target.mY;
        pPos = &p->mMotion.mPos;
        BallGetPosition(pBall, &ball);
        if (fn_800A7F1C(p->mIdBytes[2]) != 2) {
            if (pRecord->mUnknown10 != 0) {
                Point_8017886C offset;

                fn_80227690(&offset, &target, &ball);
                fn_80227248(&offset, &offset, fn_801CFB94(pRecord->mUnknown10));
                fn_80227638(&target, &offset, &ball);
            }
            fn_80227690(&delta, &target, &ball);
            if (fn_802270A4(&delta) < 3.0f) {
                fn_80227690(&delta, &pTarget->mMotion.mPos, pPos);
                fn_80227538((Point_8017886C *)&target, fn_801CFE40(delta.mY, delta.mX), 4.0f);
                fn_80227638(&target, &target, pPos);
            }
        }
        {
            Object_80039F5C *pNearest = PlyrFindNearest(&pTarget->mMotion.mPos, 0, fn_80178320());

            ReplayEventAdd(lbl_803EA368, 5, pNearest, &pNearest->mMotion.mPos, &pNearest->mMotion.mFacing);
        }
        ReplayEventAdd(lbl_803EA368, 18, p, pPos, &p->mMotion.mFacing);
        ReplayEventAdd(lbl_803EA368, 17, pTarget, &pTarget->mMotion.mPos, &pTarget->mMotion.mFacing);
        fn_80099568(1);
        if (fn_800A7F1C(p->mIdBytes[2]) == 0) {
            speed *= lbl_803EAECC;
        }
        if (p->mRatings[6] <= lbl_803EAED0) {
            speed *= 1.0f - lbl_803EAED4 * ((lbl_803EAED0 - p->mRatings[6]) / lbl_803EAED0);
        }
        distance = fn_8022781C(&target, pPos);
        ratio = distance / speed;
        maximum = (pTarget->mFlags & 0x4000) ? 40.0f : 30.0f;
        if (ratio < maximum) {
            speed = distance / maximum;
            if (speed < 0.18f) {
                speed = 0.18f;
            }
        }
        target.mX = target.mX < 1.0f - fn_80178A08() ? 1.0f - fn_80178A08()
            : (target.mX > fn_80178A08() - 1.0f ? fn_80178A08() - 1.0f : target.mX);
        BallLaunchToTarget(pBall, &target, 1, speed, spin, side);
        BallSetTarget(pBall, pTarget);
        SpchIGSetPassTarget(pTarget->mId);
        BallGetVelocity(pBall, &velocity);
        if (velocity.mY < 0.0f) {
            fn_801783D0(1, 1);
        } else {
            fn_801783D0(13, 1);
            fn_801783D0(1, 0);
            StyleTrackerMarkCatchOpportunity(p->mIdBytes[2]);
        }
        fn_80101064(p);
        break;
    }
    case 3:
        speed = gFrameTimeScale * 0.37f;
        if (pRecord->mUnknownAByte != 15) {
            Object_80039F5C *pReceiver = PlyrGet(p->mIdBytes[2], pRecord->mUnknownAByte);

            if (pReceiver->mMotion.mPos.mX > fn_80178A08() - 8.0f) {
                target.mX = pReceiver->mMotion.mPos.mX + 14.0f;
                target.mY = pReceiver->mMotion.mPos.mY;
            } else if (pReceiver->mMotion.mPos.mX < 8.0f - fn_80178A08()) {
                target.mX = pReceiver->mMotion.mPos.mX - 14.0f;
                target.mY = pReceiver->mMotion.mPos.mY;
            } else if (pReceiver->mMotion.mPos.mY > fn_80178A2C()) {
                target.mX = pReceiver->mMotion.mPos.mX;
                target.mY = pReceiver->mMotion.mPos.mY + 10.0f;
            } else {
                target.mX = fn_80178A08() + 14.0f;
                target.mY = fn_80177FE0().mY + 10.0f;
            }
        } else {
            target.mX = fn_80178A08() + 14.0f;
            target.mY = fn_80177FE0().mY + 10.0f;
            if (MathAngleDiff(p->mMotion.mFacing, 0) > 0x400000) {
                target.mX = -target.mX;
            }
        }
        target.mZ = 0.0f;
        fn_80099568(1);
        BallLaunchToTarget(pBall, &target, 1, speed, spin, side);
        BallSetTarget(pBall, 0);
        fn_80101064(p);
        PenaltyCheckGrounding(p);
        fn_801783D0(13, 1);
        break;
    case 2:
        target.mX = 0.0f;
        target.mY = 0.02f;
        target.mZ = -0.2f;
        fn_8013AD04(pBall, &target, 1, spin, side);
        break;
    case 8:
        speed = gFrameTimeScale * 0.27f;
        if (fn_801486A0() == 1) {
            fn_80152068(BallGetIndex(pBall), &target);
        }
        BallLaunchToTarget(pBall, &target, 1, speed, spin, side);
        BallSetTarget(pBall, 0);
        fn_80101064(p);
        fn_801783D0(13, 1);
        break;
    }
    p->mFlags &= ~0x2000;
    pRecord->mUnknownB = 0;
}

extern "C" void fn_801039D8(Object_80039F5C *p)
{
    Object_80039F5C *pTarget = 0;
    Ball_t *pBall = BallFindHeldBy(p);
    Record_8011F4F8 *pRecord = fn_8011F4F8(BallGetIndex(pBall));
    Record_800B15FC *pEvent;
    Vector_80039F5C velocity;

    PassIconsHide();
    PassIconsClearReplayFlag();
    fn_800B260C(0);
    pEvent = fn_800B15FC();
    fn_8009BD2C(p, &pEvent->mUnknown0);
    pEvent->mUnknownC = p->mMotion.mPos.mX;
    pEvent->mUnknown10 = p->mMotion.mPos.mY;
    pEvent->mUnknown4 = pRecord->mUnknown1D;
    switch (pRecord->mUnknown1D) {
    case 0:
    case 1:
    case 6:
    case 7:
        pTarget = PlyrGet(p->mIdBytes[2], pRecord->mUnknownAByte);
        pEvent->mUnknown8 = (int)pTarget;
        if (PlayerMoveGetKind(p) != 0) {
            AudmonEventPostId(40, &p->mMotion.mPos, p->mId, 0, 0, 0);
        }
        break;
    case 8:
        if (PlayerMoveGetKind(p) != 0) {
            AudmonEventPostId(40, &p->mMotion.mPos, p->mId, 0, 0, 0);
        }
        pEvent->mUnknown8 = (int)pTarget;
        break;
    default:
        pEvent->mUnknown8 = 0;
        break;
    }
    pEvent->mUnknown16 = 0;
    pEvent->mUnknown14 = 5;
    fn_800B1508();
    StyleTrackerMarkCatchOpportunity(p->mIdBytes[2]);
    fn_800B1584(56, 0);
    fn_801783D0(23, 1);
    ReplayEventAdd(lbl_803EA368, 18, p, &p->mMotion.mPos, &p->mMotion.mFacing);
    BallGetVelocity(pBall, &velocity);
    velocity.mX = velocity.mX < -0.2f ? -0.2f : (velocity.mX > 0.2f ? 0.2f : velocity.mX);
    velocity.mY = velocity.mY < -0.1f ? -0.1f : (velocity.mY > 0.15f ? 0.15f : velocity.mY);
    velocity.mZ = velocity.mZ < -0.1f ? -0.1f : (velocity.mZ > 0.15f ? 0.15f : velocity.mZ);
    BallSetVelocity(pBall, &velocity);
    fn_80099568(1);
    BallRelease(pBall, 4, 0);
    fn_8013AD04(pBall, &velocity, 1, 2.0f, 1.0f);
    BallSetTarget(pBall, pTarget);
    if (velocity.mY < 0.0f) {
        fn_801783D0(1, 1);
    } else {
        fn_801783D0(13, 1);
    }
    fn_80101064(p);
    p->mFlags &= ~0x2000;
    pRecord->mUnknownB = 0;
}

extern "C" int fn_80103CB0(Object_80039F5C *p)
{
    Record_8011F4F8 *pRecord = fn_8011F4F8(BallGetIndex(BallFindHeldBy(p)));

    switch (pRecord->mUnknown1D) {
    case 4:
        fn_800A5A8C(2, p, PlyrGet(p->mIdBytes[2], pRecord->mUnknownAByte));
        if (fn_801BE648(p->mpUnknown792) == 69 || fn_801BE648(p->mpUnknown792) == 178) {
            p->mFlags |= 4;
        }
        break;
    case 5:
        fn_800A5A8C(3, p, p);
        break;
    case 3:
    default:
        fn_80102D78(p);
        break;
    }
    return 1;
}

extern "C" int fn_80103D6C(Object_80039F5C *p)
{
    int result = 0;
    Object_80039F5C *pOther = BallGetCurrentHolder();

    if (pOther != 0) {
        State_80039F5C *pState = pOther->mpState;

        if (pState->mId == 15 && pState->mUnknown1 != 4) {
            result = pState->mUnknown2 == p->mIdBytes[1];
        }
    }
    return result;
}

extern "C" float AssignGetPassSpeed(Object_80039F5C *p, Object_80039F5C *pOther, float scale, short *pCount)
{
    Vector_80039F5C delta;
    float factor = 0.0f;
    float distance;
    float spread;
    float base;
    float result;

    fn_8011F4F8(BallGetIndex(BallGetCurrent()));
    fn_802276B4(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
    distance = fn_802270A4(&delta);
    fn_801CFE40(delta.mY, delta.mX);
    *pCount = *pCount < 5 ? 5 : (*pCount > 20 ? 20 : *pCount);
    spread = (*pCount - 5.0f) * scale * (1.0f / 15.0f);
    fn_80101AE0(p, &factor);
    base = (lbl_803EAEB8 - distance) * (lbl_803EAEB8 - distance) / (lbl_803EAEB8 * lbl_803EAEB8)
        * (lbl_803EAE94 - lbl_803EAE98) + lbl_803EAE98;
    result = spread * (factor * (lbl_803EAE8C - base)) + base;
    result *= 1.1f;
    result *= gFrameTimeScale;
    if ((p->mFlags & 0x4000) && fn_8011E188() < lbl_803EAE9C && result > lbl_803EAE90) {
        result = lbl_803EAE90;
    }
    return result;
}

extern "C" void fn_80103F80(Ball_t *pBall, Vector_80039F5C pos, Vector_80039F5C velocity, float speed,
                            int angle, float ballSpeed, Vector_80039F5C *pOut, Object_80039F5C *p)
{
    Vector_80039F5C ball;
    Point_8017886C delta;
    int behind;
    int running;
    float runSpeed;
    float distance;
    float closing;
    float time;
    float reach;
    float slack;
    float burst;
    int turn;

    pOut->mX = pOut->mY = pOut->mZ = 0.0f;
    behind = pos.mY < fn_80177FE0().mY + 13.0f && MathAngleDiff(angle, 0xC00000) <= 0x271C70;
    if (behind) {
        pOut->mX = pos.mX;
        pOut->mY = pos.mY;
        pOut->mZ = 1.3f;
        return;
    }
    running = speed > PlyrMoveGetRatedSpeed(p, 0.14f, 1.0f) && angle <= 0x7FFFFF;
    if (speed > fn_800C49EC(gPlyrMoveFwdSpeed)) {
        speed = fn_800C49EC(gPlyrMoveFwdSpeed);
    }
    BallGetPosition(pBall, &ball);
    runSpeed = speed;
    fn_802276B4(&ball, &ball, &pos);
    distance = fn_802270A4(&ball);
    if (running) {
        runSpeed += (PlyrMoveGetRatedSpeed(p, 1.0f, 1.0f) - runSpeed) * fn_801CFB18(angle);
    }
    runSpeed /= gFrameTimeScale;
    if (runSpeed >= ballSpeed) {
        pOut->mX = pos.mX;
        pOut->mY = pos.mY;
        pOut->mZ = 1.3f;
        return;
    }
    turn = MathAngleDiff(angle, fn_801CFE40(ball.mY, ball.mX));
    if (turn > 0x400000) {
        turn = MathAngleDiff(0x800000, turn);
        closing = ballSpeed * fn_801CFB94(fn_801CFDD0(runSpeed * fn_801CFB18(turn) / ballSpeed)) - runSpeed * fn_801CFB94(turn);
    } else {
        closing = ballSpeed * fn_801CFB94(fn_801CFDD0(runSpeed * fn_801CFB18(turn) / ballSpeed)) + runSpeed * fn_801CFB94(turn);
    }
    time = distance / closing / gFrameTimeScale;
    pOut->mX = pos.mX;
    pOut->mY = pos.mY;
    fn_8022732C(pOut, &velocity, time);
    pOut->mZ = 1.3f;
    fn_80227690(&delta, pOut, &p->mMotion.mPos);
    distance = fn_802270A4(&delta);
    burst = fn_800CAAFC(p);
    slack = runSpeed - PlyrMoveGetRatedSpeed(p, 0.72f, 1.0f);
    if (slack < 0.0f) {
        slack = 0.0f;
    }
    reach = (slack * burst + PlyrMoveGetRatedSpeed(p, 0.72f, 1.0f) * time) * 0.75f;
    if (reach < distance) {
        float short_ = distance - reach;

        pOut->mX -= short_ * fn_801CFB94(angle);
        pOut->mY -= short_ * fn_801CFB18(angle);
    }
    pOut->mX = pOut->mX < 1.0f - fn_80178A08()
                   ? 1.0f - fn_80178A08()
                   : (pOut->mX > fn_80178A08() - 1.0f ? fn_80178A08() - 1.0f : pOut->mX);
}

extern "C" void fn_80104328(Object_80039F5C *p, unsigned int count, int *pTime, Vector_80039F5C *pPos, int *pAngle)
{
    State_80039F5C *pQueue = p->mpState;
    float speed = PlyrMoveGetRatedSpeed(p, 1.0f, 1.0f);
    State_80039F5C *pEntry;
    Point_8017886C offset;
    unsigned char i;

    pPos->mX = pPos->mY = pPos->mZ = 0.0f;
    pEntry = pQueue;
    switch (pEntry->mId) {
    case 19: {
        State_80104328 *pState = (State_80104328 *)&p->mUnknown336;

        offset.mX = pState->mTarget.mX;
        offset.mY = pState->mTarget.mY;
        *pTime = (int)(fn_8022781C(&offset, &p->mMotion.mPos) / speed);
        pPos->mX = pState->mTarget.mX;
        pPos->mY = pState->mTarget.mY;
        *pAngle = pEntry->mUnknown2 << 17 & 0xFE0000;
        break;
    }
    case 20:
        PlayerCutGetEndPoint(p, &offset);
        pPos->mX = offset.mX;
        pPos->mY = offset.mY;
        if ((unsigned int)(pEntry->mUnknown2 - 8) <= 1) {
            *pAngle = PlayerCutGetStartHeading(p);
        } else {
            *pAngle = PlayerCutGetTargetHeading(p);
        }
        *pTime = PlayerCutGetTimeLeft(p);
        break;
    default:
        *pTime = 0;
        break;
    }
    for (i = 1; i <= count; i++) {
        pEntry = &pQueue[i];
        if (pEntry->mId == 20) {
            State_80039F5C *pPrev = &pQueue[i - 1];
            int kind = pEntry->mUnknown2;
            int type = pEntry->mUnknown1;

            if (pPrev->mId == 19) {
                PlayerCutGetAnimOffset(kind, type, pPrev->mUnknown2 << 17 & 0xFE0000, &offset);
                *pTime += PlayerCutGetAnimLength(type);
                pPos->mX += offset.mX;
                pPos->mY += offset.mY;
                *pAngle += PlayerCutGetMessageTurn((Message_800F01CC *)pEntry);
            }
        } else if (pEntry->mId == 19) {
            float distance = (unsigned int)pEntry->mUnknown1 * 0.125f;

            *pTime += (int)(distance / speed);
            *pAngle = pEntry->mUnknown2 << 17 & 0xFE0000;
            fn_80227538(&offset, *pAngle, distance);
            pPos->mX += offset.mX;
            pPos->mY += offset.mY;
        }
    }
}

extern "C" int fn_801045BC(Object_80039F5C *p)
{
    int result = 0;

    if (p->mpState->mId == 15) {
        State_801045BC *pState = (State_801045BC *)&p->mUnknown336;

        if (fn_800FFFB0(p) == 0) {
            result = pState->mUnknown4;
        }
    }
    return result;
}

extern "C" int fn_80104610(Object_80039F5C *p)
{
    int result = 0;

    if (p->mpState->mId == 15) {
        result = (int)((float)((fn_800B2618(9) - 0.5) * -2.0) * 10.0f + 17.0f);
    }
    return result;
}

extern "C" int fn_80104688(Object_80039F5C *p)
{
    int result = 4;
    float value;
    int team = fn_80178320();

    if (fn_801244F0(p, team, 0, fn_80178D18(fn_80178320()), &value, 1) != 0) {
        result = value >= lbl_803EAED8 ? 4 : 0;
    }
    if (fn_802372EC(0, 100) < lbl_803EAEDC) {
        result = 0;
    }
    return result;
}

extern "C" int fn_80104720(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int result = 0;

    if (fn_8011F1A4() != 0 && p->mUnknown2914 == 0) {
        result = fn_8011F4D4() > p->mMotion.mPos.mX;
        if (fn_8011F228() != 0 || (p->mMotion.mFacing & 0xFFFFFF) > 0x800000) {
            result ^= 1;
        }
    } else if (((pOther->mMotion.mFacing - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
        result = 1;
    }
    return result;
}

extern "C" int fn_801047C8(void)
{
    int result = fn_801783AC(0) == 0;

    if (fn_801783AC(13) != 0) {
        result = 0;
    }
    return result;
}

extern "C" void fn_80104814(Object_80039F5C *p, Object_80039F5C *pOther, Ball_t *pBall, Vector_80039F5C *pTarget)
{
    Vector_80039F5C ball;
    int clamp;

    BallGetPosition(pBall, &ball);
    clamp = 0;
    if (pTarget->mY > ball.mY) {
        clamp = pOther->mMotion.mPos.mY < ball.mY;
    }
    if (fn_801047C8() == 0 && pTarget->mY > ball.mY) {
        clamp = 1;
    }
    if (clamp) {
        pTarget->mY = ball.mY - 0.25f;
    }
}

extern "C" void fn_801048B4(Object_80039F5C *p, Ball_t *pBall, Vector_80039F5C *pTarget)
{
    Vector_80039F5C ball;
    float over;

    BallGetPosition(pBall, &ball);
    over = fabsf(pTarget->mX) - (fn_80178A08() - 2.0f);
    if (over > 0.0f) {
        if (over > 2.0f) {
            over = 2.0f;
        }
        if (pTarget->mX > 0.0f) {
            pTarget->mX -= over;
        } else {
            pTarget->mX += over;
        }
    }
}

extern "C" void fn_80104944(Object_80039F5C *p, Vector_80039F5C *pOut) {
    float rating = p->mRatings[6] / 255.0f;
    float range = (1.0f - rating * 0.5f) * 2.0f;

    if (lbl_803EAEE8 == 0) {
        pOut->mX += fn_80237260(0) * 2.0f * range - range;
        pOut->mY += fn_80237260(0) * 2.0f * range - range;
    }
}

extern "C" void fn_80104A08(Object_80039F5C *p, float scale, int angle, Point_8017886C *pPoint, float *pValue) {
    if (scale == 0.0f) {
        scale = p->mUnknown560.mUnknown28 / (gPlyrMoveFwdSpeed * 100621.117f);
    }
    if (scale > 0.0f) {
        Point_8017886C offset;
        float t;

        fn_80227538(&offset, angle, scale * 2.0f * fn_80237260(0));
        offset.mX += fn_80237260(0) + -0.5f;
        offset.mY += fn_80237260(0) + -0.5f;
        fn_80227638(pPoint, pPoint, &offset);
        t = scale * 0.13000001f + 0.02f;
        t = t * 2.0f * fn_80237260(0) - t;
        *pValue *= t + 1.0f;
    }
}

extern "C" void fn_80104B24(Vector_80039F5C *p) {
    p->mY += 1.0f;
}

extern "C" void fn_80104B3C(Object_80039F5C *p, Vector_80039F5C *pOut) {
    State_80039F5C *pState = p->mpState;
    float speed;

    switch (pState->mId) {
    case 68:
    case 90:
        speed = pState->mUnknown3[0] / 255.0f;
        speed *= gPlyrMoveFwdSpeed;
        speed *= (1.0f - lbl_803ED6CC) * 0.75000006f + lbl_803ED6CC;
        fn_80227538((Point_8017886C *)pOut, (pState->mUnknown2 << 17) & 0xFFFFFF, speed);
        fn_8022765C(pOut, pOut, &p->mMotion.mUnknown40);
        fn_80227264(pOut, pOut, 0.5f);
        break;
    case 0:
    default:
        pOut->mX = p->mMotion.mUnknown40;
        pOut->mY = p->mMotion.mUnknown44;
        pOut->mZ = p->mMotion.mUnknown48;
        break;
    }
    pOut->mZ = 0.0f;
}

extern "C" void fn_80104C3C(Object_80039F5C *p, Vector_80039F5C *pOut, float scale) {
    Vector_80039F5C v;

    fn_80104B3C(p, &v);
    fn_80227264(pOut, &v, scale);
    fn_8022765C(pOut, pOut, &p->mMotion.mPos);
}

extern "C" float fn_80104C9C(Object_80039F5C *p, Object_80039F5C *pOther)
{
    unsigned int frames;
    Vector_80039F5C *pPos;
    Vector_80039F5C *pOtherPos;
    float count;
    float time;
    float gain;
    Vector_80039F5C ahead;

    if (fn_8011F518()->mUnknown4 == 12) {
        frames = lbl_803EAEE4;
    } else {
        frames = lbl_803EAEE0;
    }
    pPos = &p->mMotion.mPos;
    pOtherPos = &pOther->mMotion.mPos;
    time = fn_8022781C(pOtherPos, pPos);
    count = frames;
    time /= count;
    if (time < 0.06f) {
        time = 0.06f;
    }
    fn_80104C3C(pOther, &ahead, count);
    gain = (fn_8022781C(&ahead, pPos) - fn_8022781C(pOtherPos, pPos)) / count;
    return time < time + gain ? time + gain : time;
}

extern "C" void fn_80104D98(Object_80039F5C *p)
{
    Point_8017886C goal;
    Record_8011F518 *pRecord;
    Object_80039F5C *pOther;
    unsigned short animation;

    fn_8009BD60(p);
    goal = fn_80177FE0();
    pRecord = fn_8011F518();
    pOther = fn_8009BCE8(&pRecord->mUnknown0);
    if (pRecord->mUnknown4 == 8) {
        animation = 34;
        p->mUnknown1008.mUnknown0 = 2;
    } else if (pRecord->mUnknown4 == 11 || pRecord->mUnknown4 == 9 || pRecord->mUnknown4 == 10 ||
               pRecord->mUnknown4 == 2 || pRecord->mUnknown4 == 3 || pRecord->mUnknown4 == 4 ||
               pRecord->mUnknown4 == 5) {
        Vector_80039F5C target;
        Point_8017886C dir;

        animation = pRecord->mUnknown4 != 10 ? 135 : 177;
        if (animation == 135 && PlayerMoveGetKind(p) != 0) {
            animation = 191;
        }
        pRecord->mUnknown5 = 6;
        {
            Ball_t *pBall = BallGetCurrent();

            fn_80105168(6, pBall, p, pOther, fn_80104C9C(p, pOther), &target, 0);
        }
        if (p->mpState->mId == 91 && p->mMotion.mPos.mY < goal.mY) {
            fn_80104B24(&target);
        }
        fn_80104814(p, pOther, BallGetCurrent(), &target);
        fn_80227690(&dir, &target, &p->mMotion.mPos);
        p->mUnknown1008.mUnknown1 = (int)(dir.mX * 10.0f);
        p->mUnknown1008.mUnknown2 = (int)(dir.mY * 10.0f);
    } else {
        Point_8017886C delta;
        int side;
        int angle;
        int facing;
        float rate;

        switch (pRecord->mUnknown4) {
        case 2:
        case 3:
            animation = 201;
            break;
        case 4:
        case 5:
            animation = 82;
            break;
        case 6:
        case 7:
            animation = 204;
            break;
        case 0:
        default:
            animation = 116;
            break;
        }
        switch (p->mpState->mUnknown3[0]) {
        case 2:
            side = 0;
            break;
        case 1:
            side = 1;
            break;
        case 0:
        default:
            side = fn_80104720(p, pOther);
            break;
        }
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX);
        if (pRecord->mUnknown4 <= 1 || pRecord->mUnknown4 == 12 || pRecord->mUnknown4 == 13 ||
            pRecord->mUnknown4 == 6 || pRecord->mUnknown4 == 7) {
            rate = 0.25f;
        } else {
            rate = 0.5f;
        }
        if (side) {
            pRecord->mUnknown5 = 6;
            facing = 0;
        } else {
            pRecord->mUnknown5 = 3;
            facing = 0x800000;
        }
        facing = MathRLerp(facing, angle, rate);
        p->mUnknown512.mUnknown14 = 6;
        p->mUnknown512.mUnknown8 = facing;
        p->mUnknown512.mUnknown0 = 1.0f;
        p->mUnknown512.mUnknown4 = facing;
        p->mUnknown1008.mUnknown0 = pRecord->mUnknown5;
    }
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, animation, 1.0f, p);
    if (pRecord->mUnknown4 == 6 || pRecord->mUnknown4 == 7) {
        fn_801BE67C(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, p);
    }
    p->mUnknown512.mUnknown14 = 0;
    p->mUnknown778 = -1;
    p->mFlags &= ~0x1000;
    p->mFlags &= ~4;
}

extern "C" float fn_801050DC(Ball_t *pBall, Vector_80039F5C *pTarget, float speed)
{
    Vector_80039F5C delta;
    float time;
    float clamped;

    BallGetPosition(pBall, &delta);
    fn_802276B4(&delta, &delta, pTarget);
    time = fn_802270A4(&delta) / speed;
    if (time < 0.04074074f) {
        clamped = 0.04074074f;
    } else {
        clamped = time;
        if (clamped > 0.4074074f) {
            clamped = 0.4074074f;
        }
    }
    return clamped * gFrameTimeScale;
}

extern "C" void fn_80105168(int mode, Ball_t *pBall, Object_80039F5C *p, Object_80039F5C *pOther, float speed, Vector_80039F5C *pTarget, int unused)
{
    Vector_80039F5C delta;
    Vector_80039F5C ball;
    Vector_80039F5C hand;
    Vector_80039F5C handDir;
    Vector_80039F5C velocity;
    float distance;
    float runSpeed;
    int angle;
    float time;

    BallGetPosition(pBall, &ball);
    if (mode == 6) {
        fn_8009BF5C(pOther, CharSkelGetJointByName(pOther->mpUnknown4->mpUnknown100, "rwrist"), &hand, &handDir);
    } else {
        fn_8009BF5C(pOther, CharSkelGetJointByName(pOther->mpUnknown4->mpUnknown100, "lwrist"), &hand, &handDir);
    }
    fn_802276B4(&delta, &ball, &hand);
    distance = fn_802270A4(&delta);
    fn_80104B3C(pOther, &velocity);
    runSpeed = fn_802270D4(&velocity);
    angle = fn_801CFE40(velocity.mY, velocity.mX);
    angle = (angle - fn_801CFE40(delta.mY, delta.mX)) & 0xFFFFFF;
    time = distance / (speed * fn_801CFB94(fn_801CFDD0(runSpeed * fn_801CFB18(angle) / speed)) + runSpeed * fn_801CFB94(angle));
    if (time <= 0.0f || time > 120.0f) {
        time = 2.0f;
    }
    fn_80104C3C(pOther, pTarget, time);
    pTarget->mZ = hand.mZ;
    fn_801048B4(p, pBall, pTarget);
    pTarget->mY = pTarget->mY >= pOther->mMotion.mPos.mY ? pTarget->mY : pOther->mMotion.mPos.mY;
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

extern "C" Object_80039F5C *fn_80105384(Object_80039F5C *p, int aggressive, Point_8017886C *pOut)
{
    float bestScore = 0.0f;
    unsigned int count = fn_80178D18(p->mIdBytes[2]);
    Object_80039F5C *pBest = 0;
    int anyDepth = 0;
    unsigned char i;

    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther;
        float distance;
        float score;
        float stamina;
        Vector_80039F5C target;
        Point_8017886C spot;
        Ball_t *pBall;
        int side;

        if (((p->mId >> 16) & 0xFF) == i) {
            continue;
        }
        pOther = PlyrGet((p->mId >> 8) & 0xFF, i);
        if (!anyDepth && pOther->mMotion.mPos.mY >= p->mMotion.mPos.mY) {
            continue;
        }
        if (fn_8010531C(pOther) == 0 || fn_8011E9B4(pOther) != 0) {
            continue;
        }
        distance = fn_8022781C(&pOther->mMotion.mPos, &p->mMotion.mPos);
        if (distance >= 7.0f) {
            continue;
        }
        if (MathAngleDiff(pOther->mMotion.mFacing, 0xC00000) <= 0x200000) {
            continue;
        }
        if ((p->mpState[0].mId == 91 || p->mpState[1].mId == 91 || (p->mUnknown2914 == 0 && fn_8011F524() != 0)) &&
            pOther->mpState->mId == 90) {
            score = !aggressive ? 70.0f : 14.0f;
        } else {
            score = 7.0f - distance;
        }
        stamina = fn_8012506C(p, 3);
        if (stamina < 42.0f) {
            score += (42.0f - stamina) * 0.16666667f;
        }
        pBall = BallGetCurrent();
        fn_80105168(6, pBall, p, pOther, fn_80104C9C(p, pOther), &target, 0);
        spot.mX = target.mX;
        spot.mY = target.mY;
        fn_802276B4(&target, &target, &p->mMotion.mPos);
        side = ((fn_801CFE40(target.mY, target.mX) - p->mMotion.mFacing) & 0xFFFFFF) <= 0x7FFFFF ? 1 : 2;
        if (side != p->mUnknown776) {
            if (aggressive) {
                score *= 0.5f;
            } else {
                score = 0.0f;
            }
        }
        if (score > bestScore) {
            bestScore = score;
            pBest = pOther;
            if (pOut) {
                *pOut = spot;
            }
        }
    }
    return pBest;
}

extern "C" void fn_80105630(Object_80039F5C *p, Vector_80039F5C *pTarget, Reach_80105630 *pReach)
{
    int done = 0;
    Record_8011F518 *pRecord = fn_8011F518();
    Object_80039F5C *pOther = fn_8009BCE8(&pRecord->mUnknown0);

    if (pOther != 0) {
        Ball_t *pBall = BallGet(pReach->mBall);
        char name[10];
        Vector_80039F5C shoulder;
        Vector_80039F5C dir;
        unsigned int now;
        float t;
        int turn;

        if (pReach->mHand == 1) {
            strcpy(name, "rshoulder");
        } else {
            strcpy(name, "lshoulder");
        }
        fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, name), &shoulder, &dir);
        now = fn_8023790C() + 2;
        t = (pReach->mEnd - now) * 0.083333336f;
        t = t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t);
        fn_80105168(pRecord->mUnknown5, pBall, p, pOther, fn_80104C9C(p, pOther), pTarget, 0);
        fn_802276B4(pTarget, pTarget, &shoulder);
        turn = ((fn_801CFE40(pTarget->mY, pTarget->mX) - p->mMotion.mFacing) << 8) >> 8;
        turn = (int)(turn * (1.0f - t));
        fn_80227538((Point_8017886C *)pTarget, (turn + p->mMotion.mFacing) & 0xFFFFFF, 1.5f);
        pTarget->mZ = 0.4f;
        fn_8022765C(pTarget, pTarget, &shoulder);
    } else {
        done = 1;
    }
    if (pReach->mEnd <= fn_8023790C()) {
        done = 1;
    }
    if (done) {
        fn_8009CE88(p, pReach->mHand == 1 ? &p->mUnknown200 : &p->mUnknown108, 12);
        fn_8009CE88(p, &p->mUnknown16, 12);
    }
}

extern "C" int fn_80105898(Object_80039F5C *p) {
    Message_800F01CC message;
    Vector_80039F5C ball;
    Point_8017886C delta;
    State_80105898 *pState = (State_80105898 *)&p->mUnknown336;
    Record_8011F518 *pRecord = fn_8011F518();
    Object_80039F5C *pTarget = PlyrGet(p->mIdBytes[2], p->mpState->mUnknown1);
    int kind = 3;

    BallGetPosition(BallGetCurrent(), &ball);
    fn_80227690(&delta, &ball, &p->mMotion.mPos);
    if (((fn_801CFE40(delta.mY, delta.mX) - p->mMotion.mFacing) & 0xFFFFFF) <= 0x7FFFFF) {
        kind = 6;
    }
    if (p->mpState->mUnknown2 == 9 || p->mpState->mUnknown2 == 11) {
        StyleTrackerBeginPitch(PlayerMoveGetKind(p) != 0, p);
    }
    fn_80106678(pRecord, pTarget, kind, p->mpState->mUnknown2);
    pState->mUnknown0 = 2;
    pState->mUnknown1 = 0;
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~0x1000;
    p->mFlags &= ~4;
    if (pRecord->mUnknown4 != 8) {
        if (p == BallGetCurrentHolder()) {
            if (!(pRecord->mUnknown4 == 10 || pRecord->mUnknown4 == 1 || pRecord->mUnknown4 == 13 ||
                  pRecord->mUnknown4 == 3 || pRecord->mUnknown4 == 5 || pRecord->mUnknown4 == 7) &&
                (pRecord->mUnknown4 <= 1 || pRecord->mUnknown4 == 12 || pRecord->mUnknown4 == 13 ||
                 pRecord->mUnknown4 == 6 || pRecord->mUnknown4 == 7 ||
                 (pRecord->mUnknown4 >= 14 && pRecord->mUnknown4 <= 15))) {
                BallSetCurrentTarget(pTarget);
            }
            if (!fn_80105E90(p, pTarget, pRecord->mUnknown4)) {
                memset(&message, 0, 4);
                message.mId = 1;
                fn_800F053C(0, p->mpState, &message, p);
            }
        }
    } else if (p->mpState[1].mId == 31) {
        fn_8011E1BC(p, 0, 0, 1);
        fn_8011E3EC(p, 1);
    } else if (p->mpState[1].mId == 33) {
        fn_8011E1BC(p, 0, 0, 1);
        fn_8011E3EC(p, 2);
    }
    if (pRecord->mUnknown4 == 6 || pRecord->mUnknown4 == 7) {
        fn_80104D98(p);
        pState->mUnknown0 = 0;
    }
    return 0;
}

extern "C" int fn_80105AF4(Object_80039F5C *p) {
    int result = 0;
    Record_8011F518 *pRecord = fn_8011F518();
    State_80105898 *pState = (State_80105898 *)&p->mUnknown336;

    if (fn_8009BCE8(&pRecord->mUnknown0)->mpState->mId == 93) {
        return 1;
    }
    if (p->mFlags & 1) {
        Object_80039F5C *pOther;

        p->mFlags &= ~1;
        pState->mUnknown1 = 1;
        pOther = fn_8009BCE8(&pRecord->mUnknown0);
        if (pRecord->mUnknown4 == 10 || pRecord->mUnknown4 == 1 || pRecord->mUnknown4 == 13 ||
            pRecord->mUnknown4 == 3 || pRecord->mUnknown4 == 5 || pRecord->mUnknown4 == 7) {
            if (pRecord->mUnknown4 <= 1 || pRecord->mUnknown4 == 12 ||
                pRecord->mUnknown4 == 13 || pRecord->mUnknown4 == 6 || pRecord->mUnknown4 == 7) {
                fn_800A5A8C(0, p, pOther);
            } else {
                fn_800A5A8C(1, p, pOther);
            }
            fn_800A60D8(p, pOther);
        }
    }
    if (pRecord->mUnknown4 == 8 && BallFindHeldBy(p) == 0) {
        return 1;
    }
    if (pState->mUnknown0 != 0) {
        p->mFlags &= ~4;
        if (--pState->mUnknown0 == 0) {
            fn_80104D98(p);
        }
    }
    if (p->mFlags & 0x1000) {
        Ball_t *pBall = BallFindHeldBy(p);

        if (pBall != 0 && fn_801787A0() == 0) {
            fn_801061E8(p, pBall);
            if (pRecord->mUnknown4 != 8) {
                AudmonEventPostId(60, &p->mpUnknown4->mUnknown4, p->mId, 0, 0, 0);
                fn_800A2190(2);
            }
            fn_8011F5AC(0);
        }
        p->mFlags &= ~0x1000;
    }
    if (p->mFlags & 4) {
        p->mFlags &= ~4;
        result = 1;
    }
    if (result == 1) {
        if ((pRecord->mUnknown4 <= 1 || pRecord->mUnknown4 == 12 || pRecord->mUnknown4 == 13 ||
             pRecord->mUnknown4 == 6 || pRecord->mUnknown4 == 7 ||
             (pRecord->mUnknown4 >= 14 && pRecord->mUnknown4 <= 15)) &&
            (pRecord->mUnknown4 == 10 || pRecord->mUnknown4 == 1 || pRecord->mUnknown4 == 13 ||
             pRecord->mUnknown4 == 3 || pRecord->mUnknown4 == 5 || pRecord->mUnknown4 == 7)) {
            if (fn_800B65A0(p->mIdBytes[2]) != 255 && fn_8011F1A4() == 0 && PassIconsAreShown() == 0) {
                PassIconsShow(0);
                CamGameSetModeAll(2);
            }
            if (fn_800B65A0(p->mIdBytes[2]) == 255 && fn_8011F1A4() == 0) {
                CamGameSetModeAll(2);
            }
        }
        if (pRecord->mUnknown4 != 8) {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
        }
    }
    return result;
}

extern "C" void fn_80105DF0(Message_800F01CC *pMessage) {
    PlayBookFormation_t *pObject;
    unsigned int count;
    unsigned char i;

    if (pMessage->mUnknown1[2] == 1) {
        pMessage->mUnknown1[2] = 2;
    } else if (pMessage->mUnknown1[2] == 2) {
        pMessage->mUnknown1[2] = 1;
    }
    pObject = PlayBookGetFormation(fn_80178308());
    count = fn_80178D18(fn_80178308());
    for (i = 0; i < count; i++) {
        if (PlaySetGetEntry(pObject, i, 0)->mUnknownB == pMessage->mUnknown1[0]) {
            pMessage->mUnknown1[0] = i;
            break;
        }
    }
}

extern "C" int fn_80105E90(Object_80039F5C *p, Object_80039F5C *pTarget, int kind) {
    int result = 1;
    Ball_t *pBall = BallGetCurrent();
    unsigned char count = BallGetStateFrames(pBall);
    int state = BallStateGetPrev(pBall, 0);
    Vector_80039F5C target;

    if (count <= 21 && state == 4) {
        result = 0;
    } else if ((kind == 11 || kind == 9 || kind == 10 || kind == 2 || kind == 3 || kind == 4 || kind == 5) &&
               !(kind == 10 || kind == 1 || kind == 13 || kind == 3 || kind == 5 || kind == 7) &&
               !(kind >= 2 && kind <= 5)) {
        Ball_t *pLive = BallGetCurrent();

        fn_80105168(6, pLive, p, pTarget, fn_80104C9C(p, pTarget), &target, 0);
        if (fn_8022781C(&target, &p->mMotion.mPos) > 9.5f ||
            (!fn_801047C8() && pTarget->mMotion.mPos.mY > p->mMotion.mPos.mY)) {
            result = 0;
        }
    }
    if (fn_801BE648(p->mpUnknown792) == 234 || fn_801BE648(p->mpUnknown792) == 238) {
        result = 0;
    }
    return result;
}

extern "C" int fn_80105FF8(Object_80039F5C *p, Ball_t *pBall, float time) {
    int ready = 0;
    Reach_80105630 *pReach = 0;
    Record_8011F518 *pRecord = fn_8011F518();
    int joint = CharSkelGetJointByName(fn_8009BCE8(&pRecord->mUnknown0)->mpUnknown4->mpUnknown100, "rwrist");

    if (pRecord->mUnknown4 != 8) {
        int animation = fn_801BE648(p->mpUnknown792);
        unsigned char side = p->mUnknown776;

        if (p->mpState->mId == 10 || p->mpState->mId == 16) {
            int index = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, animation, 0);

            if (index != 0xFFFF && AnimSeqGetTimeToOpcode(&p->mpUnknown800[index].mUnknown4C, 0xC001) > time) {
                ready = 1;
            }
        } else {
            ready = 1;
        }
        if (ready) {
            int left;

            if (animation == 135 || animation == 191) {
                fn_8009CEE4(p, pRecord->mUnknown0, joint, 6, 0);
            }
            left = side == 2;
            pReach = fn_8009CD00(p, fn_80105630, left, (unsigned int)time, 2);
            if (pReach != 0) {
                pReach->mHand = left;
                pReach->mBall = BallGetIndex(pBall);
                pReach->mEnd = fn_8023790C() + (unsigned int)time + 2;
            }
        }
    }
    return pReach != 0;
}

extern "C" void fn_801061E8(Object_80039F5C *p, Ball_t *pBall) {
    Vector_80039F5C target;
    Vector_80039F5C velocity;
    float speed;
    Record_8011F518 *pRecord = fn_8011F518();
    Object_80039F5C *pTarget = fn_8009BCE8(&pRecord->mUnknown0);

    if (pRecord->mUnknown4 == 8) {
        BallReleaseStill(pBall, 2, 0);
        fn_8010D80C(pTarget, &target);
        speed = fn_8010D82C(pTarget);
        speed = fn_801050DC(pBall, &target, speed);
        if (fn_8011F32C()) {
            BallLaunchToTarget(pBall, &target, 2, speed, 0.0f, 1.0f);
        } else {
            BallLaunchToTarget(pBall, &target, 2, speed, 0.0f, 1.0f);
        }
        BallSetTarget(pBall, pTarget);
    } else if (!(pRecord->mUnknown4 == 10 || pRecord->mUnknown4 == 1 || pRecord->mUnknown4 == 13 ||
                 pRecord->mUnknown4 == 3 || pRecord->mUnknown4 == 5 || pRecord->mUnknown4 == 7)) {
        Record_800B15FC *pEvent;

        fn_80099568(2);
        BallRelease(pBall, 3, 0);
        speed = fn_80104C9C(p, pTarget);
        fn_80105168(pRecord->mUnknown5, pBall, p, pTarget, speed, &target, 0);
        if (pRecord->mUnknown4 == 9) {
            if (p->mUnknown2914 == 0) {
                fn_80104B24(&target);
            } else {
                fn_800A5A8C(6, p, p);
            }
        }
        if (pRecord->mUnknown4 == 9 || pRecord->mUnknown4 == 11) {
            fn_80104944(p, &target);
            fn_80104A08(p, pRecord->mUnknown8, pRecord->mUnknown12, (Point_8017886C *)&target, &speed);
        }
        fn_80104814(p, pTarget, pBall, &target);
        BallLaunchToTarget(pBall, &target, 3, speed, 1.0f, 4.0f);
        BallSetTarget(pBall, pTarget);
        BallGetVelocity(pBall, &velocity);
        pEvent = fn_800B15FC();
        fn_8009BD2C(p, &pEvent->mUnknown0);
        pEvent->mUnknownC = p->mMotion.mPos.mX;
        pEvent->mUnknown10 = p->mMotion.mPos.mY;
        if (velocity.mY < 0.0f) {
            pEvent->mUnknown4 = pTarget->mId;
            pEvent->mUnknown8 = pRecord->mUnknown4;
            pEvent->mUnknown14 = 7;
            fn_801783D0(1, 1);
        } else {
            pEvent->mUnknown14 = 5;
            pEvent->mUnknown4 = 0;
            pEvent->mUnknown16 = 0;
            pEvent->mUnknown8 = (int)pTarget;
            StyleTrackerMarkCatchOpportunity(p->mIdBytes[2]);
            fn_801783D0(13, 1);
            fn_801783D0(1, 0);
        }
        fn_800B1508();
    }
}

extern "C" int fn_801064A4(Object_80039F5C *p, int a) {
    int result = 0;
    Object_80039F5C *pTarget = fn_80105384(p, 1, 0);

    if (pTarget == 0) {
        if (fn_801486A0() == 0) {
            BallReleaseStill(BallGetCurrent(), 3, 1);
        }
    } else if (fn_80105E90(p, pTarget, 11)) {
        Message_800F01CC message;

        result = 1;
        memset(&message, 0, 4);
        message.mId = 25;
        PlayerMoveBegin(p, a, 25);
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
        fn_80106678(fn_8011F518(), pTarget, 6, 11);
        fn_8010CEB8(pTarget, 11);
        StyleTrackerBeginPitch(0, p);
        result = 1;
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

extern "C" void fn_80106678(Record_8011F518 *pRecord, Object_80039F5C *p, int a, int b) {
    fn_8009BD2C(p, &pRecord->mUnknown0);
    pRecord->mUnknown4 = b;
    pRecord->mUnknown5 = a;
    pRecord->mUnknown8 = 0.0f;
    pRecord->mUnknown12 = 0;
}

extern "C" int fn_801066D0(Object_80039F5C *p, Object_80039F5C *pTarget, int kind) {
    unsigned char filter[2] = {1, 0x11};
    int result = 1;

    if (kind == 9) {
        Ball_t *pBall = BallGetCurrent();
        Vector_80039F5C pos;
        Vector_80039F5C target;

        fn_80105168(6, pBall, p, pTarget, fn_80104C9C(p, pTarget), &target, 0);
        pos.mX = p->mMotion.mPos.mX;
        pos.mY = p->mMotion.mPos.mY;
        pos.mZ = p->mMotion.mPos.mZ;
        fn_80227350(&pos, (Vector_80039F5C *)&p->mMotion.mUnknown40, 40.0f);
        result = fn_801248D4(p, &pos, &target, 0, lbl_803EAEF0, lbl_803EAEEC, (Filter_801248D4 *)filter, pTarget);
    }
    return result;
}

extern "C" int fn_80106794(Object_80039F5C *p) {
    if (BallFindHeldBy(p) == BallGetCurrent()) {
        BallSetCurrentTarget(0);
    }
    return 1;
}

extern "C" int fn_801067D8(Object_80039F5C *p) {
    return fn_8012506C(p, 6) < lbl_803EAEF4;
}

extern "C" int fn_8010680C(Table_80089904 *pTable, unsigned short key, void *pRecord, AnimChannel_t *pEntries,
                           Object_80039F5C *p, unsigned int phase) {
    Turn_8010680C *pTurn = (Turn_8010680C *)fn_801BE60C(p->mpUnknown792, key);

    switch (phase) {
    case 0: {
        int index = fn_8009C4B0(pTable, &p->mUnknown1008);
        int facing;

        if (index >= 0) {
            p->mFlags &= ~4;
            pTurn->mUnknown8 = AnimChanStartAnim(pRecord, pEntries, pTable->mEntries[index].mUnknown0,
                                           pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        }
        facing = p->mUnknown512.mUnknown8;
        if (MathAngleDiff(facing, p->mMotion.mFacing) > 0xB60B) {
            fn_801BE760(p->mpUnknown792, key, 1);
            if (AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 204)) {
                int entry;

                pEntries = p->mpUnknown800;
                entry = AnimChanGetStateChannelByIndex(p->mpUnknown796, pEntries, 204, 0);

                pTurn->mUnknown4 = pEntries[entry].mUnknown48;
                if (pTurn->mUnknown4 != 0.0f ||
                    (pTurn->mUnknown4 = AnimSeqGetTimeToOpcode(&pEntries[entry].mUnknown4C, 0xC003)) != 0.0f) {
                    pTurn->mUnknown4 = pTurn->mUnknown4 > 50.0f ? 50.0f : pTurn->mUnknown4;
                    pTurn->mUnknown0 = (int)(MathAngleDiff(facing, p->mMotion.mFacing) / pTurn->mUnknown4);
                    if (((p->mMotion.mFacing - facing) & 0xFFFFFF) <= 0x7FFFFF) {
                        pTurn->mUnknown0 = -pTurn->mUnknown0;
                    }
                    /* The shipped code discards the rate it just computed. */
                    pTurn->mUnknown0 = 0;
                }
            }
        }
        break;
    }
    case 1:
        break;
    case 2:
        if (pTurn->mUnknown4 > 0.0f) {
            pTurn->mUnknown4 -= 1.0f;
            p->mMotion.mFacing += pTurn->mUnknown0;
            p->mpUnknown800[pTurn->mUnknown8].mUnknownC += pTurn->mUnknown0;
        }
        break;
    }
    return 0;
}

extern "C" void fn_80106A60(Object_80039F5C *p) {
    Block_800F4A74_80104C9C *pBlock = (Block_800F4A74_80104C9C *)&p->mUnknown336;
    Ball_t *pBall = BallGet(pBlock->mUnknown64);
    Object_80039F5C *pCarrier;
    Vector_80039F5C pos;
    Vector_80039F5C landing;
    Point_8017886C delta;
    int heading;
    int angle;
    int diff;

    BallGetPosition(pBall, &pos);
    BallGetLandingPoint(pBall, &landing);
    fn_80227690(&delta, &landing, &pos);
    heading = fn_801CFE40(delta.mY, delta.mX);
    pCarrier = BallGetTarget(pBall);
    if (pCarrier != 0) {
        fn_80227690(&delta, &landing, &pCarrier->mMotion.mPos);
        if (fn_802270A4(&delta) > 2.0f) {
            angle = fn_801CFE40(delta.mY, delta.mX);
            diff = MathAngleDiff(heading, angle);
            if (diff <= 0x1FFFFF) {
                pBlock->mUnknown24 = 0;
            } else if (diff > 0x600000) {
                pBlock->mUnknown24 = 1;
            } else if (((heading - angle) & 0xFFFFFF) <= 0x7FFFFF) {
                pBlock->mUnknown24 = 2;
            } else {
                pBlock->mUnknown24 = 3;
            }
        } else {
            pBlock->mUnknown24 = 4;
        }
    } else {
        pBlock->mUnknown24 = 1;
    }
    fn_80227690(&delta, &landing, &p->mMotion.mPos);
    if (fn_802270A4(&delta) > 2.0f) {
        angle = fn_801CFE40(delta.mY, delta.mX);
        diff = MathAngleDiff(heading, angle);
        if (diff <= 0x1FFFFF) {
            pBlock->mUnknown20 = 0;
        } else if (diff > 0x600000) {
            pBlock->mUnknown20 = 1;
        } else if (((heading - angle) & 0xFFFFFF) <= 0x7FFFFF) {
            pBlock->mUnknown20 = 2;
        } else {
            pBlock->mUnknown20 = 3;
        }
    } else {
        pBlock->mUnknown20 = 4;
    }
}

extern "C" void fn_80106C24(Object_80039F5C *p, Block_800F4A74_80104C9C *pBlock) {
    Ball_t *pBall = BallGet(pBlock->mUnknown64);
    Object_80039F5C *pOther = BallGetTarget(pBall);
    int result = pBlock->mUnknown49;
    Vector_80039F5C start;
    Vector_80039F5C target;
    Vector_80039F5C velocity;
    Point_8017886C delta;
    Point_8017886C apart;
    Point_8017886C ahead;
    float ballTime;
    float otherTime;
    float time;
    float distance = 0.0f;

    BallGetLandingPoint(pBall, &start);
    BallGetPosition(pBall, &target);
    BallGetVelocity(pBall, &velocity);
    fn_80227690(&delta, &start, &target);
    ballTime = fn_802270A4(&delta) / fn_802270A4(&velocity);
    if (pOther != 0) {
        fn_80227690(&delta, &start, &pOther->mMotion.mPos);
        otherTime = fn_802270A4(&delta)
            / (gPlyrMoveFwdSpeed * ((1.0f - lbl_803ED6CC) * (pOther->mRatings[4] / 255.0f) + lbl_803ED6CC));
        fn_80227690(&delta, &start, &p->mMotion.mPos);
        time = fn_802270A4(&delta) / (gPlyrMoveFwdSpeed * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        distance = fn_802270A4(&delta);
        fn_80227690(&apart, &p->mMotion.mPos, &pOther->mMotion.mPos);
        fn_80227690(&ahead, &target, &pOther->mMotion.mPos);
        if (pOther->mpState->mId == 28 && BallGetCurrentHolder() != pOther) {
            Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;

            if (pPass->mUnknown0 < pPass->mUnknown16) {
                otherTime = pPass->mUnknown16 - pPass->mUnknown0;
                fn_80227690(&delta, &pPass->mUnknown4, &target);
                ballTime = fn_802270A4(&delta) / fn_802270A4(&velocity);
                fn_80227690(&delta, &pPass->mUnknown4, &p->mMotion.mPos);
                time = fn_802270A4(&delta)
                    / (gPlyrMoveFwdSpeed * ((1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f) + lbl_803ED6CC));
            }
        }
        switch (pBlock->mUnknown20) {
        case 0:
            if (ballTime > time - 5.0f) {
                switch (pBlock->mUnknown24) {
                case 0:
                    if (time < otherTime) {
                        if ((time > 20.0f
                             && MathAngleDiff(fn_801CFE40(ahead.mY, ahead.mX), fn_801CFE40(apart.mY, apart.mX)) <= 0x71C71B)
                            || (MathAngleDiff(pOther->mMotion.mUnknown32, 0) <= 0x11C71B
                                && p->mMotion.mPos.mX > pOther->mMotion.mPos.mX)
                            || (MathAngleDiff(pOther->mMotion.mUnknown32, 0x800000) <= 0x11C71B
                                && p->mMotion.mPos.mX < pOther->mMotion.mPos.mX)
                            || p->mMotion.mPos.mY < pOther->mMotion.mPos.mY) {
                            result = 2;
                        } else {
                            result = 3;
                        }
                    } else if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.5f || pBlock->mUnknown49 == 3) {
                        result = 3;
                    } else {
                        result = 2;
                    }
                    break;
                case 2:
                case 3:
                    result = 0;
                    if (pBlock->mUnknown54 == 1) {
                        result = 3;
                    }
                    break;
                case 1:
                case 4:
                    result = 3;
                    if (pBlock->mUnknown56 <= 79) {
                        result = 0;
                    }
                    break;
                }
            } else {
                if (time < otherTime && pBlock->mUnknown51 != 1 && pOther->mpState->mId != 28) {
                    result = 0;
                } else if (pOther->mpState->mId == 28 && (pBlock->mUnknown50 == 3 || pBlock->mUnknown49 == 3)) {
                    result = 3;
                } else if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.5f || pBlock->mUnknown49 == 3) {
                    result = 3;
                } else {
                    result = 2;
                }
            }
            break;
        case 1:
            switch (pBlock->mUnknown24) {
            case 0:
                result = 3;
                break;
            case 2:
            case 3:
                result = 3;
                if (time < otherTime && pBlock->mUnknown54 == 0) {
                    result = 0;
                }
                break;
            case 1:
                result = 3;
                if (time < otherTime && pBlock->mUnknown54 == 0) {
                    result = 0;
                }
                break;
            case 4:
                result = 3;
                break;
            }
            break;
        case 4:
            switch (pBlock->mUnknown24) {
            case 0:
                result = 3;
                break;
            case 1:
                result = 0;
                break;
            case 2:
            case 3:
                result = 0;
                if (pBlock->mUnknown54 != 0) {
                    result = 3;
                }
                break;
            case 4:
                result = 2;
                break;
            }
            break;
        case 2:
        case 3:
            switch (pBlock->mUnknown24) {
            case 0:
                {
                    int angle = fn_801CFE40(velocity.mY, velocity.mX);

                    if ((MathAngleDiff(angle, pOther->mMotion.mUnknown32) <= 0x3FFFFF
                         && MathAngleDiff(angle, p->mMotion.mUnknown32) > 0x400000 && distance > 2.0f)
                        || (pBlock->mUnknown49 == 0 && velocity.mZ < 0.0f)) {
                        result = pOther->mMotion.mPos.mY >= p->mMotion.mPos.mY ? 2 : 0;
                    } else {
                        result = 3;
                        if (time < ballTime && pBlock->mUnknown56 <= 49) {
                            result = 2;
                        }
                    }
                }
                break;
            case 2:
            case 3:
                if (ballTime > time - 5.0f || distance < 5.0f) {
                    result = 3;
                    if (pBlock->mUnknown24 == pBlock->mUnknown20) {
                        if (pBlock->mUnknown54 == 0) {
                            result = 2;
                        }
                    } else if (time < otherTime) {
                        result = 2;
                    }
                } else {
                    result = 1;
                }
                break;
            case 4:
                result = 3;
                break;
            case 1:
                result = 3;
                if (time < otherTime) {
                    result = 0;
                }
                break;
            }
            break;
        }
    }
    if (pOther != 0 && result == 3) {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *pMate = PlyrGet(p->mIdBytes[2], i);

            if (pMate != p) {
                Point_8017886C gap;
                Block_800F4A74_80104C9C *pMateBlock = (Block_800F4A74_80104C9C *)&pMate->mUnknown336;

                fn_80227690(&gap, &pOther->mMotion.mPos, &pMate->mMotion.mPos);
                if (pMateBlock->mUnknown49 == 3
                    && pMate->mMotion.mPos.mY > p->mMotion.mPos.mY && fn_802270A4(&gap) < 4.5f) {
                    result = 2;
                    break;
                }
            }
        }
    }
    if (pOther != 0 && result == 2 && p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *pMate = PlyrGet(p->mIdBytes[2], i);
            Object_80039F5C *pMark = fn_800FB9D4(pOther);

            if (pMate != p) {
                Point_8017886C gap;
                Block_800F4A74_80104C9C *pMateBlock = (Block_800F4A74_80104C9C *)&pMate->mUnknown336;

                fn_80227690(&gap, &pOther->mMotion.mPos, &pMate->mMotion.mPos);
                if (pMateBlock->mUnknown49 == 2 && pMate->mMotion.mPos.mY < p->mMotion.mPos.mY
                    && fn_802270A4(&gap) < 3.5f) {
                    result = 3;
                    break;
                }
                if (pMark == pMate && pMate->mMotion.mPos.mY < p->mMotion.mPos.mY && fn_802270A4(&gap) < 3.5f) {
                    result = 3;
                    break;
                }
            }
        }
    }
    if (pOther != 0 && otherTime > ballTime + 5.0f) {
        result = 0;
    }
    if (result != pBlock->mUnknown49) {
        pBlock->mUnknown50 = pBlock->mUnknown49;
        pBlock->mUnknown49 = result;
    }
}

extern "C" void fn_801074B4(Object_80039F5C *p, Points_800F3A6C *pInfo) {
    Object_800B26B0 *pMotion;
    Point_8017886C delta;
    int angle;
    float distance;
    float strength;
    Object_80039F5C *pOther = BallGetTarget(pInfo->mpUnknown0);

    if (pOther == 0) {
        return;
    }
    pMotion = &p->mMotion;
    fn_80227690(&delta, &pOther->mMotion.mPos, &pMotion->mPos);
    angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    distance = fn_802270A4(&delta);
    if (MathAngleDiff(angle, pMotion->mFacing) > 0x555554 && distance >= 3.5f) {
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
        if (MathAngleDiff(pMotion->mFacing, 0x400000) <= 0x1FFFFF && BallStateGet(pInfo->mpUnknown0, 0) == 4) {
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

extern "C" void fn_80107680(Points_800F3A6C *pInfo, int index) {
    pInfo->mpUnknown0 = BallGet(index);
    BallGetLandingPoint(pInfo->mpUnknown0, &pInfo->mUnknown4);
    BallSolveFallToHeight(pInfo->mpUnknown0, 1.5f, &pInfo->mUnknown48, (Vector_80039F5C *)&pInfo->mUnknown40);
    BallGetVelocity(pInfo->mpUnknown0, &pInfo->mUnknown28);
    BallGetPosition(pInfo->mpUnknown0, &pInfo->mUnknown16);
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

extern "C" void fn_801077D8(Object_80039F5C *p, Object_80039F5C *pOther, Block_800F4A74_801077D8 *pBlock, Info_800F3A6C *pInfo,
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
        turn = MathAngleDiff(heading, fn_801CFE40(toTarget.mY, toTarget.mX));
        if (turn <= 0x18E38D
            || (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.0f && passing && progress > 0.5f && turn <= 0x1FFFFF)) {
            pBlock->mUnknown54 = 1;
        }
    }
}

extern "C" void fn_801079BC(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                            Points_800F3A6C *pInfo) {
    float x;
    float dx;

    x = pInfo->mUnknown4.mX;
    pA->mX = x;
    pA->mY = pInfo->mUnknown4.mY;
    pB->mX = x;
    pB->mY = pA->mY;
    dx = pInfo->mUnknown4.mX - p->mMotion.mPos.mX;
    if (dx > 0.0f) {
        dx *= 0.33333334f;
        if (dx > 2.0f) {
            dx = 2.0f;
        }
        pB->mX = x - dx;
    } else {
        dx *= 0.33333334f;
        if (dx < -2.0f) {
            dx = -2.0f;
        }
        pB->mX = x - dx;
    }
    if (pOther != 0) {
        float y = pOther->mMotion.mPos.mY + 4.0f;
        float low = pInfo->mUnknown4.mY - 1.0f;

        if (y < low) {
            y = low;
        } else {
            float high = pInfo->mUnknown4.mY + 2.0f;

            if (y > high) {
                y = high;
            }
        }
        pB->mY = y;
    }
}

extern "C" void fn_80107A9C(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                            Info_800F3A6C *pResult, Points_800F3A6C *pInfo, float *pScale) {
    Block_800F4A74_801077D8 *pBlock = (Block_800F4A74_801077D8 *)&p->mUnknown336;
    Ball_t *pBall = BallGet(pBlock->mUnknown64);
    Point_8017886C ballToOther;
    Point_8017886C offset;
    Point_8017886C delta;

    pA->mX = pInfo->mUnknown40.mX;
    ballToOther.mX = ballToOther.mY = 0.0f;
    pA->mY = pInfo->mUnknown40.mY;
    pB->mX = pA->mX;
    pB->mY = pA->mY;
    if (MathAngleDiff(pOther->mMotion.mUnknown32, 0) != 0) {
        fn_80227690(&ballToOther, &pOther->mMotion.mPos, &pBall->mState.mPos);
    }
    if (fn_80178A08() - fabsf(pA->mX) < 5.0f && !fn_801783AC(12) && !fn_801783AC(11)) {
        pA->mY -= 6.0f;
    }
    if (pOther->mpState->mId == 28 && BallGetCurrentHolder() != pOther) {
        Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;

        fn_80227538(&offset, ballToOther.Heading(), 0.5f);
        if (pPass->mUnknown0 < pPass->mUnknown16) {
            pB->mX = pPass->mUnknown4.mX;
            pB->mY = pPass->mUnknown4.mY;
            fn_80227690(pB, pB, &offset);
        }
    } else {
        pBlock->mUnknown55 = 1;
        pBlock->mUnknown58 = 0;
        fn_80227538(&offset, ballToOther.Heading(), 1.5f);
        fn_80227690(pB, pA, &offset);
        fn_80227690(&delta, pB, &p->mMotion.mPos);
        if (MathAngleDiff(delta.Heading(), p->mMotion.mUnknown32) > 0x471C72) {
            int turn = MathAngleDiff(pOther->mMotion.mUnknown32, p->mMotion.mUnknown32);

            if (MathAngleDiff(pOther->mMotion.mUnknown32, 0x400000) > 35.0f && pOther->mMotion.mUnknown28 > 0.0f) {
                if (turn <= 0x155554) {
                    fn_80227538(&delta, pOther->mMotion.mUnknown32, 0.5f);
                    fn_80227638(pB, &p->mMotion.mPos, &delta);
                }
            } else {
                pB->mX = pInfo->mUnknown40.mX;
                pB->mY = pInfo->mUnknown40.mY;
                pBlock->mUnknown55 = 0;
            }
        }
    }
}

extern "C" void fn_80107D48(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                            Info_800F3A6C *pResult, Points_800F3A6C *pInfo, float *pScale) {
    Block_800F4A74_801077D8 *pBlock = (Block_800F4A74_801077D8 *)&p->mUnknown336;
    Point_8017886C offset;

    pA->mX = pInfo->mUnknown4.mX;
    pA->mY = pInfo->mUnknown4.mY;
    if (pInfo->mUnknown16.mZ > 3.0f && MathAngleDiff(pResult->mUnknown24, 0x400000) <= 0x11C71B &&
        (p->mMotion.mPos.mY < pInfo->mUnknown40.mY || p->mMotion.mPos.mY > pInfo->mUnknown4.mY)) {
        pA->mX = pInfo->mUnknown40.mX;
        pA->mY = pInfo->mUnknown40.mY;
        fn_80227690(&offset, pA, &pOther->mMotion.mPos);
        fn_80227538(&offset, offset.Heading(), 2.5f);
        fn_80227638(pA, pA, &offset);
    }
    if (pOther->mpState->mId == 28 && BallGetCurrentHolder() != pOther) {
        Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;
        int angle;

        if (pPass->mUnknown0 < pPass->mUnknown16) {
            pA->mX = pPass->mUnknown4.mX;
            pA->mY = pPass->mUnknown4.mY;
            angle = pOther->mMotion.mUnknown32;
            if (angle <= 0x38E38D) {
                angle += 0x71C71;
            } else if (angle > 0x471C72) {
                angle -= 0x71C71;
            }
            fn_80227538(&offset, angle, 1.0f);
            fn_80227638(pA, pA, &offset);
        } else {
            pA->mX = pOther->mMotion.mPos.mX;
            pA->mY = pOther->mMotion.mPos.mY;
            angle = pOther->mMotion.mUnknown32;
            if (angle <= 0x38E38D) {
                angle += 0x71C71;
            } else if (angle > 0x471C72) {
                angle -= 0x71C71;
            }
            fn_80227538(&offset, angle, 1.0f);
            fn_80227638(pA, pA, &offset);
        }
    }
    pB->mX = pA->mX;
    pB->mY = pA->mY;
    if (pOther != 0) {
        if (MathAngleDiff(p->mMotion.mUnknown32, pOther->mMotion.mUnknown32) <= 0x155554) {
            pBlock->mUnknown61 = 1;
        } else if (pResult->mUnknown32 < 10.0f && pOther->mpState->mId != 28 && pResult->mUnknown36 < 5.0f) {
            float time = fn_8009F168(&pOther->mMotion.mPos, &pOther->mMotion.mUnknown40, &p->mMotion.mPos,
                                     gPlyrMoveFwdSpeed * (lbl_803ED6CC + (1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f))) -
                         0.25f;

            if (time < 0.1f) {
                time = 0.1f;
            }
            fn_80227248(pB, &pOther->mMotion.mUnknown40, time);
            fn_80227638(pB, pB, &pOther->mMotion.mPos);
        }
    }
}

extern "C" void fn_80108074(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                            Input_801076F0 *pIn) {
    if (p != 0 && pOther != 0 && pA != 0 && pB != 0 && pIn != 0) {
        if (pOther->mpState->mId == 28) {
            Block_80108074 *pBlock = (Block_80108074 *)&pOther->mUnknown336;

            if (pBlock != 0) {
                pA->mX = pBlock->mUnknown4.mX;
                pA->mY = pBlock->mUnknown4.mY;
            }
        } else {
            pA->mX = pIn->mUnknown40.mX;
            pA->mY = pIn->mUnknown40.mY;
        }
        pB->mX = pA->mX;
        pB->mY = pA->mY;
    } else if (pIn != 0 && pB != 0) {
        pB->mX = pIn->mUnknown40.mX;
        pB->mY = pIn->mUnknown40.mY;
    }
}

extern "C" void fn_8010810C(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pA, Point_8017886C *pB,
                            Points_800F3A6C *pInfo, Info_800F3A6C *pResult, float scale) {
    Block_800F4A74_8010810C *pBlock = (Block_800F4A74_8010810C *)&p->mUnknown336;
    Point_8017886C toTarget;
    Point_8017886C ballToSpot;
    Point_8017886C otherToSpot = {0.0f, 0.0f};
    Point_8017886C meToOther;
    float otherTime = 0.0f;
    float ballTime;
    float myTime;
    float time;
    float ratio;
    float factor;
    int blocked = 0;

    fn_80227690(&toTarget, pB, &p->mMotion.mPos);
    fn_80227690(&ballToSpot, pA, &pInfo->mUnknown16);
    ballTime = fn_802270A4(&ballToSpot) / fn_802270A4(&pInfo->mUnknown28);
    myTime = fn_802270A4(&toTarget) /
             (gPlyrMoveFwdSpeed * (lbl_803ED6CC + (1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f)));
    if (pOther != 0) {
        fn_80227690(&otherToSpot, pA, &pOther->mMotion.mPos);
        fn_80227690(&meToOther, &pOther->mMotion.mPos, &p->mMotion.mPos);
        otherTime = fn_802270A4(&otherToSpot) /
                    (gPlyrMoveFwdSpeed * (lbl_803ED6CC + (1.0f - lbl_803ED6CC) * (pOther->mRatings[4] / 255.0f)));
    } else {
        otherToSpot.mX = otherToSpot.mY = 0.0f;
        meToOther.mX = meToOther.mY = 0.0f;
    }
    if (pOther != 0 && pOther->mpState->mId == 28) {
        Block_800F3344 *pPass = (Block_800F3344 *)&pOther->mUnknown336;
        Point_8017886C toPass;

        ballTime = (float)(pPass->mUnknown16 - pPass->mUnknown0);
        fn_80227690(&toPass, &pPass->mUnknown4, &p->mMotion.mPos);
        myTime = fn_802270A4(&toPass) /
                 (gPlyrMoveFwdSpeed * (lbl_803ED6CC + (1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f)));
    }
    switch (pBlock->mUnknown49) {
    case 1:
        time = myTime;
        if (myTime < 4.0f) {
            time = myTime * 2.0f;
        }
        break;
    case 3:
        time = ballTime * scale;
        break;
    case 2:
        if (myTime < otherTime && fn_802270A4(&meToOther) < 2.0f && fn_802270A4(&toTarget) < fn_802270A4(&otherToSpot)) {
            time = myTime * (2.0f / 3.0f);
        } else {
            time = ballTime;
            if (pBlock->mUnknown55 != 0) {
                time = myTime;
            }
        }
        time *= scale;
        break;
    default:
        time = ballTime;
        break;
    }
    pBlock->mUnknown28 = pB->mX;
    pBlock->mUnknown32 = pB->mY;
    if (time > 0.0f) {
        ratio = fn_802270A4(&toTarget) / time;
    } else {
        ratio = 0.0f;
    }
    if (ratio > p->mMotion.mUnknown36) {
        factor = 1.0f;
    } else if (p->mMotion.mUnknown36 != 0.0f) {
        factor = ratio / p->mMotion.mUnknown36;
    } else {
        factor = 0.0f;
    }
    if (fn_801783AC(11) == 1 || fn_801783AC(12) == 1) {
        if (fn_80237260(0) > p->mRatings[3] / 255.0f && fn_8022781C(&pInfo->mUnknown16, &p->mMotion.mPos) > 6.0f) {
            factor /= 3.0f;
        }
    }
    pBlock->mUnknown36 = toTarget.Heading() & 0xFFFFFF;
    if (pBlock->mUnknown63 != 0) {
        pBlock->mUnknown40 = (pResult->mUnknown20 + 0x800000) & 0xFFFFFF;
        if (MathAngleDiff(pBlock->mUnknown40, p->mMotion.mFacing) > 0x5FFFFF) {
            int heading = p->mMotion.mFacing;

            if (MathAngleDiff(heading, 0x400000) <= 0x1FFFFF && pInfo->mUnknown16.mY < p->mMotion.mPos.mY &&
                BallStateGet(pInfo->mpUnknown0, 0) == 4) {
                Point_8017886C toBall;

                fn_80227690(&toBall, &pInfo->mUnknown16, &p->mMotion.mPos);
                heading = toBall.Heading();
            }
            if (((heading - pBlock->mUnknown40) & 0xFFFFFF) <= 0x7FFFFF) {
                pBlock->mUnknown40 = (p->mMotion.mFacing - 0x5F49F5) & 0xFFFFFF;
            } else {
                pBlock->mUnknown40 = (p->mMotion.mFacing + 0x5F49F5) & 0xFFFFFF;
            }
        }
    } else {
        if (pOther != 0) {
            if (myTime < ballTime - 2.5f || (myTime < 12.0f && ballTime < 12.0f) ||
                p->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 1.5f) {
                if (fn_802270A4(&toTarget) < 7.0f) {
                    blocked = 1;
                }
            }
            if (MathAngleDiff(p->mMotion.mUnknown32, 0x400000) <= 0x1C71C6 && factor > 0.9f &&
                fn_802270A4(&meToOther) < 5.0f && p->mMotion.mPos.mY < pOther->mMotion.mPos.mY + 5.0f &&
                MathAngleDiff(pBlock->mUnknown40, 0x400000) <= 0x1C71C6) {
                blocked = 0;
            }
            if (blocked != 0 && MathAngleDiff(p->mMotion.mUnknown32, 0x400000) <= 0x1C71C6 &&
                (fn_802270A4(&meToOther) > 10.0f ||
                 MathAngleDiff(pOther->mMotion.mUnknown32, otherToSpot.Heading()) > 0x155555)) {
                blocked = 0;
            }
        }
        if (pOther != 0 && blocked != 0) {
            Point_8017886C toBall;
            Point_8017886C toOtherPlayer;
            Point_8017886C sum;

            fn_80227690(&toBall, &pInfo->mUnknown16, &p->mMotion.mPos);
            fn_80227690(&toOtherPlayer, &pOther->mMotion.mPos, &p->mMotion.mPos);
            fn_802271A4(&toBall, &toBall);
            fn_802271A4(&toOtherPlayer, &toOtherPlayer);
            if (MathAngleDiff(p->mMotion.mFacing, 0x400000) <= 0x18E38D && pBlock->mUnknown49 != 0) {
                toBall.mX *= 0.35f;
                toBall.mY = 0.0f;
                toOtherPlayer.mX *= 0.65f;
                toOtherPlayer.mY *= 0.65f;
            } else {
                switch (pBlock->mUnknown49) {
                case 0:
                case 2:
                    toOtherPlayer.mX = 0.0f;
                    toOtherPlayer.mY = 0.0f;
                    break;
                case 1:
                case 3:
                    toBall.mX = 0.0f;
                    toBall.mY = 0.0f;
                    break;
                }
            }
            fn_80227638(&sum, &toBall, &toOtherPlayer);
            pBlock->mUnknown40 = sum.Heading();
        } else {
            int turn;

            pBlock->mUnknown40 = pBlock->mUnknown36;
            turn = MathAngleDiff(pBlock->mUnknown40, p->mMotion.mFacing);
            if (turn > 0x400000) {
                factor = fn_801CFB94(turn / 2) * 0.72f;
                pBlock->mUnknown60 = 0;
            }
        }
    }
    if (factor < 1e-7f) {
        factor = 0.0f;
    }
    pBlock->mUnknown44 = factor;
}

extern "C" void fn_80108954(Object_80039F5C *p, Object_80039F5C *pOther, Result_801076F0 *pInfo) {
    Block_80109150 *pBlock = (Block_80109150 *)&p->mUnknown336;

    if (pOther != 0 && pBlock->mUnknown49 == 3) {
        pBlock->mUnknown53 = 1;
        if (pBlock->mUnknown44 <= 0.7f && MathAngleDiff(pInfo->mUnknown20, p->mMotion.mUnknown32) > 0x78E38E) {
            pBlock->mUnknown52 = 1;
        }
        if (pBlock->mUnknown57 != 0 ||
            (pBlock->mUnknown61 != 0 && pBlock->mUnknown54 != 0 && pInfo->mUnknown40 < 2.0f)) {
            pBlock->mUnknown57 = 1;
            pBlock->mUnknown40 = (pInfo->mUnknown20 + 0x800000) & 0xFFFFFF;
            if (MathAngleDiff(p->mMotion.mFacing, pBlock->mUnknown40) > 0xAAAAA) {
                pBlock->mUnknown36 = pInfo->mUnknown20;
            } else {
                pBlock->mUnknown48 = 12;
            }
        }
    }
    if (pOther != 0 && pOther->mpState->mId == 28 &&
        MathAngleDiff(pInfo->mUnknown20 + 0x800000, p->mMotion.mFacing) <= 0x471C71) {
        pBlock->mUnknown53 = 1;
    }
}

extern "C" void fn_80108A94(Object_80039F5C *p, Points_800F3A6C *pInfo) {
    Block_800F4A74_80108A94 *pBlock = (Block_800F4A74_80108A94 *)&p->mUnknown336;

    if (pBlock->mUnknown44 != 0.0f) {
        if (pBlock->mUnknown52 == 1 && pBlock->mUnknown36 == pBlock->mUnknown40) {
            pBlock->mUnknown48 = 12;
        }
        if (pBlock->mUnknown60 == 1 && pBlock->mUnknown44 >= 0.72f && pBlock->mUnknown36 == pBlock->mUnknown40 &&
            MathAngleDiff(p->mMotion.mFacing, pBlock->mUnknown36) <= 0xE38E2 &&
            MathAngleDiff(p->mMotion.mUnknown32, pBlock->mUnknown36) <= 0xE38E2) {
            pBlock->mUnknown48 = 1;
        }
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown36;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown40;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown44;
    }
    p->mUnknown512.mUnknown15 = pBlock->mUnknown48;
    if (pBlock->mUnknown40 == pBlock->mUnknown36 && p->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.05f &&
        MathAngleDiff(p->mMotion.mUnknown32, pBlock->mUnknown40) > 0x2E38E3 &&
        MathAngleDiff(p->mMotion.mFacing, 0xC00000) <= 0x2AAAA9) {
        pBlock->mUnknown44 = 0.0f;
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown36;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown40;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown44;
        pBlock->mUnknown58 = 2;
    }
    if (pBlock->mUnknown53 == 1) {
        fn_801074B4(p, pInfo);
    }
}

extern "C" int fn_80108C34(Object_80039F5C *p, Block_800F4A74_80108A94 *pBlock, Points_800F3A6C *pInfo,
                           Object_80039F5C *pOther) {
    int result = 0;

    if (pBlock->mUnknown62 != 0 || p->mUnknown2914 == 17 || p->mUnknown2914 == 18 || p->mUnknown2914 == 16 ||
        fn_8009F0B8(p, 0x400000) == 1 || pBlock->mUnknown49 == 0) {
        result = 1;
    } else if (pOther != 0 && pOther->mpState->mId == 28 && BallGetCurrentHolder() != pOther) {
        Block_800F4A74_80108A94 *pOtherBlock = (Block_800F4A74_80108A94 *)&pOther->mUnknown336;

        if (fn_800ACB8C(p->mIdBytes[2]) < (float)pOtherBlock->mUnknown0 / (float)pOtherBlock->mUnknown16 &&
            fn_802372EC(0, 0xFF) < (unsigned short)(p->mRatings[8] / 3)) {
            result = 1;
        }
    } else if (pInfo->mUnknown28.mZ < 0.0f && fn_802372EC(0, 0xFF) < (unsigned short)(p->mRatings[8] / 5)) {
        result = 1;
    }
    if (pOther == 0) {
        return result;
    }
    switch (fn_801BE648(pOther->mpUnknown792)) {
    case 0xE0:
    case 0xE1:
        if (p->mMotion.mPos.mY > pOther->mMotion.mPos.mY) {
            result = 0;
        }
        break;
    }
    return result;
}

extern "C" void fn_80108DF8(Object_80039F5C *p, Points_800F3A6C *pInfo, int quick) {
    Block_800F4A74_80108A94 *pBlock = (Block_800F4A74_80108A94 *)&p->mUnknown336;
    int outA = -1;
    int outB = 0;
    int handle = 0x1FFFFFFF;
    int mode;
    float range;
    float height;
    Object_80039F5C *pOther; /* teammate in the loop, then the 0x80137B88 player */

    if (fn_80108C34(p, pBlock, pInfo, BallGetTarget(pInfo->mpUnknown0)) == 0) {
        return;
    }
    mode = 1;
    if (!(p->mFlags & 0x4000)) {
        mode = 3;
    }
    if (p->mUnknown8 == 0xFF) {
        range = 120.0f;
    } else {
        range = 17.0f;
    }
    if (quick == 0 && !fn_801783AC(11)) {
        unsigned char i;

        for (i = 0; i <= 2; i++) {
            int index = PlayBookGetReceiver(fn_80178308(), i, 0);

            if (index != 0xFF) {
                pOther = PlyrGet(fn_80178308(), index);
                float mateTime =
                    fn_8022781C(&pOther->mMotion.mPos, &pInfo->mUnknown40) / PlyrMoveGetRatedSpeed(pOther, 1.0f, 1.0f);
                float time = fn_8022781C(&p->mMotion.mPos, &pInfo->mUnknown40) / PlyrMoveGetRatedSpeed(p, 1.0f, 1.0f);

                if (time > mateTime - 45.0f || pInfo->mUnknown48 > mateTime - 45.0f) {
                    break;
                }
            }
        }
    }
    pOther = BallGetTarget(pInfo->mpUnknown0);
    if (pOther != 0 && pOther->mpState->mId == 28 && !fn_801783AC(11)) {
        Point_8017886C toTarget;
        Point_8017886C toPlayer;

        fn_80227690(&toTarget, &pInfo->mUnknown16, &pOther->mMotion.mPos);
        fn_80227690(&toPlayer, &p->mMotion.mPos, &pOther->mMotion.mPos);
        if (MathAngleDiff(toPlayer.Heading(), toTarget.Heading()) > 0x355555) {
            Block_800F4A74_80108A94 *pOtherBlock = (Block_800F4A74_80108A94 *)&pOther->mUnknown336;

            if (pOtherBlock->mUnknown0 < pOtherBlock->mUnknown16 && pBlock->mUnknown49 == 3) {
                
                Sphere_80108DF8 sphere;

                sphere.mCenter.mX = pOtherBlock->mUnknown4.mX;
                sphere.mCenter.mY = pOtherBlock->mUnknown4.mY;
                sphere.mCenter.mZ = pOtherBlock->mUnknown4.mZ;
                sphere.mRadius = 0.4f;
                fn_8009A8D4(pBlock);
            }
        }
    }
    BallGetLandingTime(BallGet(pBlock->mUnknown64), &height);
    if (fn_8009A6EC(p) != 0) {
        handle = fn_800997F4(p, BallGet(pBlock->mUnknown64), range, pBlock, 3, 0, 0, &outA, &outB);
    }
    if (handle == 0x1FFFFFFF) {
        handle = fn_80099734(p, BallGet(pBlock->mUnknown64), 0, mode, range, pBlock, 1, 0, 0, PlyrRollContestedCatch(p));
        if (handle == 0x1FFFFFFF) {
            return;
        }
    }
    if (((handle >> 29) & 3) == 1) {
        fn_8009A1A8(p, handle, outA, outB, pBlock->mUnknown64);
    } else {
        fn_80099F04(p, handle, pBlock->mUnknown64);
    }
}

extern "C" int fn_80109150(Object_80039F5C *p) {
    Block_80109150 *pBlock = (Block_80109150 *)&p->mUnknown336;

    memset(pBlock, 0, 88);
    pBlock->mUnknown51 = pBlock->mUnknown49 = p->mpState->mUnknown1;
    pBlock->mUnknown58 = 0;
    pBlock->mUnknown50 = 4;
    pBlock->mUnknown44 = 0.0f;
    pBlock->mUnknown56 = fn_802372EC(0, 100);
    pBlock->mUnknown52 = 0;
    pBlock->mUnknown53 = 0;
    pBlock->mUnknown54 = 0;
    pBlock->mUnknown48 = 0;
    pBlock->mUnknown57 = 0;
    pBlock->mUnknown61 = 0;
    pBlock->mUnknown60 = 1;
    pBlock->mUnknown63 = 0;
    pBlock->mUnknown62 = fn_8009F0B8(p, 0x38E38E);
    pBlock->mUnknown64 = BallGetCurrentIndex();
    pBlock->mUnknown65 = 1;
    pBlock->mUnknown66 = 0;
    fn_80106A60(p);
    fn_8009A8D4(pBlock);
    if (fn_800B65A0(p->mIdBytes[2]) == 255 && fn_800ABDA4(p->mIdBytes[2]) == 0) {
        pBlock->mUnknown58 = 0;
    }
    return 0;
}

extern "C" int fn_80109248(Object_80039F5C *p) {
    Block_800F4A74_80109248 *pBlock = (Block_800F4A74_80109248 *)&p->mUnknown336;
    Points_800F3A6C info;
    int result = 0;

    fn_80107680(&info, pBlock->mUnknown64);
    if (BallStateGet(info.mpUnknown0, 0) != 4) {
        Message_800F01CC message;

        pBlock->mUnknown65 = 0;
        memset(&message, 0, 4);
        message.mId = 2;
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (fn_800B65A0(fn_80178308()) != 0xFF && (float)fn_8011E188() < lbl_803EAEF8) {
        pBlock->mUnknown58 = 0;
    }
    if (!(p->mFlags & 0x4000)) {
        if ((info.mUnknown16.mX > fn_80178A08() + 3.0f && p->mMotion.mPos.mX > fn_80178A08() - 2.0f) ||
            (info.mUnknown16.mX < -fn_80178A08() - 3.0f && p->mMotion.mPos.mX < 2.0f - fn_80178A08())) {
            return 1;
        }
        int active = 0;

        if (--pBlock->mUnknown58 < 0) {
            float scale = 1.0f;
            Point_8017886C a;
            Point_8017886C b;
            Result_801076F0 res;
            Object_80039F5C *pOther;
            int rush;
            int delay;
            int rating;

            a.mX = a.mY = 0.0f;
            b.mX = b.mY = 0.0f;
            delay = fn_800AC324(p->mIdBytes[2]);
            rating = 0xFF - p->mRatings[8];
            if (rating < 0) {
                rating = 0;
            }
            rush = 0;
            pBlock->mUnknown58 = fn_802372EC(0, (rating >> 5) + delay);
            pBlock->mUnknown52 = 0;
            pBlock->mUnknown53 = 0;
            pBlock->mUnknown54 = 0;
            pBlock->mUnknown55 = 0;
            pBlock->mUnknown61 = 0;
            pBlock->mUnknown63 = 0;
            pBlock->mUnknown48 = 0;
            pBlock->mUnknown60 = 1;
            if (fn_801783AC(11) || fn_801783AC(12)) {
                rush = 1;
            }
            pOther = BallGetTarget(info.mpUnknown0);
            fn_80106A60(p);
            if (pOther != 0) {
                fn_801076F0(p, pOther, &res, (Input_801076F0 *)&info);
                fn_801077D8(p, pOther, (Block_800F4A74_801077D8 *)pBlock, (Info_800F3A6C *)&res, &info);
            }
            fn_80106C24(p, (Block_800F4A74_80104C9C *)pBlock);
            switch (pBlock->mUnknown49) {
            case 0:
                active = 1;
                fn_80108074(p, pOther, &a, &b, (Input_801076F0 *)&info);
                pBlock->mUnknown60 = 1;
                break;
            case 1:
                active = 1;
                fn_801079BC(p, pOther, &a, &b, &info);
                if (!rush) {
                    active = 0;
                }
                pBlock->mUnknown60 = 1;
                break;
            case 2:
                fn_80107A9C(p, pOther, &a, &b, (Info_800F3A6C *)&res, &info, &scale);
                pBlock->mUnknown60 = 1;
                active = 1;
                break;
            case 3:
                active = 1;
                fn_80107D48(p, pOther, &a, &b, (Info_800F3A6C *)&res, &info, &scale);
                pBlock->mUnknown60 = 1;
                break;
            }
            b.mX = CLAMP(b.mX, 1.0f - fn_80178A08(), fn_80178A08() - 1.0f);
            b.mY = CLAMP(b.mY, 1.0f - fn_80178A44(), fn_80178A44() - 1.0f);
            fn_8010810C(p, pOther, &a, &b, &info, (Info_800F3A6C *)&res, scale);
            fn_80108954(p, pOther, &res);
            if (pBlock->mUnknown54 == 1 && pBlock->mUnknown49 != 0 && !rush) {
                active = 0;
            }
            pBlock->mUnknown66 = active;
        }
        fn_80108A94(p, &info);
    } else {
        pBlock->mUnknown66 = 0;
    }
    if (pBlock->mUnknown66 == 1) {
        fn_80108DF8(p, &info, 0);
    }
    return result;
}

extern "C" void fn_801096D4(Object_80039F5C *p) {
    int turn = 0;
    float x = p->mMotion.mPos.mX;
    float y = p->mMotion.mPos.mY;
    int facing = p->mMotion.mFacing & 0xFFFFFF;

    if (x > fn_80178A08() - lbl_803EAF0C) {
        if (MathAngleDiff(facing, 0) <= 0x555554) {
            if (facing <= 0x7FFFFF) {
                turn = (int)(lbl_803EAF08 * 46603.38f);
            } else {
                turn = -(int)(lbl_803EAF08 * 46603.38f);
            }
        }
    } else if (x < lbl_803EAF0C - fn_80178A08()) {
        if (MathAngleDiff(facing, 0x800000) <= 0x555554) {
            if (facing <= 0x7FFFFF) {
                turn = -(int)(lbl_803EAF08 * 46603.38f);
            } else {
                turn = (int)(lbl_803EAF08 * 46603.38f);
            }
        }
    } else if (y > fn_80178A44() - lbl_803EAF0C) {
        if (MathAngleDiff(facing, 0x400000) <= 0x555554) {
            if (MathAngleDiff(facing, 0) <= 0x3FFFFF) {
                turn = -(int)(lbl_803EAF08 * 46603.38f);
            } else {
                turn = (int)(lbl_803EAF08 * 46603.38f);
            }
        }
    } else if (y < lbl_803EAF0C - fn_80178A44()) {
        if (MathAngleDiff(facing, 0xC00000) <= 0x555554) {
            if (MathAngleDiff(facing, 0) <= 0x3FFFFF) {
                turn = (int)(lbl_803EAF08 * 46603.38f);
            } else {
                turn = -(int)(lbl_803EAF08 * 46603.38f);
            }
        }
    }
    if (turn != 0 && p->mUnknown512.mUnknown0 > 0.0f) {
        Block_801096D4 *pBlock = (Block_801096D4 *)&p->mUnknown336;

        if (pBlock->mUnknown52Mode == 3) {
            int angle = facing + turn;

            p->mUnknown512.mUnknown8 = angle;
            p->mUnknown512.mUnknown0 = p->mUnknown528.mUnknown0;
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown4 = angle;
        } else {
            Point_8017886C target;
            Point_8017886C delta;
            int angle;

            target = fn_80177FFC(p->mIdBytes[2]);
            fn_80227690(&delta, &target, &p->mMotion.mPos);
            angle = delta.Heading();
            p->mUnknown512.mUnknown8 = angle;
            p->mUnknown512.mUnknown0 = p->mUnknown528.mUnknown0;
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown4 = angle;
            pBlock->mUnknown52Mode = 0;
            pBlock->mUnknown52State = 5;
            pBlock->mUnknown56 = target;
        }
    }
}

extern "C" int fn_80109968(Object_80039F5C *p, Point_8017886C *pOut) {
    return p->mMotion.mUnknown28 <= gPlyrMoveFwdSpeed * 0.07f;
}

extern "C" void fn_80109990(Pair_80109990 *pOut) {
    Object_80039F5C *pFirst = 0;
    Object_80039F5C *pSecond = 0;
    int i;

    for (i = 0; i <= 3 && pFirst == 0 && pSecond == 0; i++) {
        if (fn_8009274C(i) != 0) {
            Character_80093BCC *pCharacter = fn_80093BCC(i);

            pFirst = fn_800963EC(pCharacter);
            pSecond = fn_800963F4(pCharacter);
            break;
        }
    }
    pOut->mpUnknown0 = pFirst;
    pOut->mpUnknown4 = pSecond;
}

extern "C" int fn_80109A1C(Object_80039F5C *p, Point_8017886C *pOut) {
    int result = 0;
    Object_80039F5C *pTarget = BallGetCurrentHolder();
    float distance;

    if (pTarget != 0 && pTarget != p) {
        distance = fn_8022781C(&p->mMotion.mPos, &pTarget->mMotion.mPos);
        result = distance < 1.25f;
    }
    if (!result) {
        Pair_80109990 pair;
        Object_80039F5C *pOther;

        fn_80109990(&pair);
        pTarget = pair.mpUnknown0;
        if (pTarget != 0 && pTarget != p) {
            distance = fn_8022781C(&p->mMotion.mPos, &pTarget->mMotion.mPos);
            if (distance < 1.25f) {
                result = 1;
            }
        }
        pOther = pair.mpUnknown4;
        if (pOther != 0 && pOther != p) {
            distance = fn_8022781C(&p->mMotion.mPos, &pOther->mMotion.mPos);
            if (distance < 1.25f) {
                pTarget = pOther;
                result = 1;
            }
        }
        if (!result) {
            pTarget = fn_801244F0(p, p->mIdBytes[2], 0, fn_80178D18(p->mIdBytes[2]), &distance, 0);
            if (pTarget != 0 && pTarget != p) {
                if (distance < 0.75f) {
                    result = 1;
                } else {
                    pTarget = fn_801244F0(p, p->mIdBytes[2] ^ 1, 0, fn_80178D18(p->mIdBytes[2] ^ 1), &distance,
                                          0);
                    if (pTarget != 0 && pTarget != p && distance < 1.25f) {
                        result = 1;
                    }
                }
            }
        }
    }
    if (fabsf(p->mMotion.mPos.mX) > fn_80178A08() - lbl_803EAF0C ||
        fabsf(p->mMotion.mPos.mY) > fn_80178A44() - lbl_803EAF0C) {
        result = 0;
    }
    if (result) {
        fn_80227690(pOut, &p->mMotion.mPos, &pTarget->mMotion.mPos);
        if (fn_802270A4(pOut) != 0.0f) {
            fn_80227248(pOut, pOut, 6.0f / fn_802270A4(pOut));
            fn_80227638(pOut, pOut, &p->mMotion.mPos);
        } else {
            result = 0;
        }
    }
    return result;
}

extern "C" int fn_80109C7C(Object_80039F5C *p) {
    return p->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.4f;
}

extern "C" void fn_80109CA0(Object_80039F5C *p, int animation, unsigned char a, unsigned char b, unsigned char c) {
    Block_80109CA0 *pBlock = (Block_80109CA0 *)&p->mUnknown336;

    if (animation != 203) {
        fn_8009BD60(p);
        p->mUnknown1008.mUnknown0 = a;
        p->mUnknown1008.mUnknown1 = b;
        p->mUnknown1008.mUnknown2 = c;
    }
    if (animation != fn_801BE648(p->mpUnknown792)) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, animation, 1.0f, p);
        pBlock->mUnknown50 = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, animation, 0);
        p->mUnknown512.mUnknown14 = 0;
        p->mFlags &= ~4;
    } else {
        pBlock->mUnknown50 = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, animation, 0);
    }
}

extern "C" int fn_80109D70(Object_80039F5C *p, Point_8017886C *pOut) {
    int result = 6;

    if (BallFindHeldBy(p)) {
        result = 8;
    } else if (fn_80109C7C(p)) {
        result = 1;
    } else if (fn_80109A1C(p, pOut)) {
        result = 3;
    } else if (fn_80109968(p, pOut)) {
        result = 5;
    } else if (p->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.07f) {
        result = 2;
    } else if (fn_802372EC(0, 5) <= 3) {
        result = 4;
    }
    return result;
}

extern "C" int fn_80109E48(Object_80039F5C *p, int kind, int *pOut) {
    Block_80109E48 *pBlock = (Block_80109E48 *)&p->mUnknown336;
    int result;
    Message_800F01CC message;

    *pOut = 0;
    result = 0;
    switch (kind) {
    case 8:
        memset(&message, 0, 4);
        message.mId = 49;
        fn_800F00D4(0, p->mpState, &message, p);
        if (p->mpState->mId == 49) {
            result = 1;
            *pOut = 2;
        }
        break;
    case 9:
        if (p->mMotion.mUnknown28 <= gPlyrMoveFwdSpeed * 0.5f) {
            fn_80178308();
            pBlock->mUnknown52Count = 0;
        } else {
            pBlock->mUnknown52State = 1;
        }
        break;
    }
    return result;
}

extern "C" int fn_80109F34(Object_80039F5C *p) {
    Block_80109F34 *pBlock = (Block_80109F34 *)&p->mUnknown336;
    int result = 0;
    int state = pBlock->mUnknown52State;

    if (state == 3) {
        Point_8017886C delta;
        float rate;
        int angle;
        int index;

        fn_80227690(&delta, &pBlock->mUnknown56, &p->mMotion.mPos);
        fn_800FF598((State_800FDA58 *)pBlock, p, &pBlock->mUnknown56, delta.Heading() & 0xFFFFFF, -1.0f);
        pBlock->mUnknown28 = -1.0f;
        rate = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
        if (rate < 0.14f) {
            rate = 0.14f;
        }
        pBlock->mUnknown2 = state;
        pBlock->mUnknown20 = rate;
        pBlock->mUnknown52Mode = 2;
        result = 1;
        fn_800FF094(p);
        angle = p->mUnknown512.mUnknown4;
        if (fn_800CB580(p, &index, pBlock->mUnknown56, angle, 0) != 0) {
            fn_800CBB00(p, index, pBlock->mUnknown56, angle, 0);
            pBlock->mUnknown52Mode = 6;
        }
        fn_801096D4(p);
    }
    return result;
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

extern "C" int fn_8010A0A0(Object_80039F5C *p, int index) {
    if (index != 0xFFFF) {
        float distance;
        Object_80039F5C *pOther = fn_80124C28(p, &distance, 0x2AAAAA, 3.0f, 1.0f, p->mMotion.mFacing);

        if (pOther != 0) {
            Point_8017886C delta;
            int angle;

            fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
            angle = fn_801CFE40(delta.mY, delta.mX);
            if (((angle - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                p->mMotion.mFacing = (p->mMotion.mFacing + 0xB60B) & 0xFFFFFF;
                p->mpUnknown800[index].mUnknownC = (p->mpUnknown800[index].mUnknownC + 0xB60B) & 0xFFFFFF;
            } else {
                p->mMotion.mFacing = (p->mMotion.mFacing - 0xB60B) & 0xFFFFFF;
                p->mpUnknown800[index].mUnknownC = (p->mpUnknown800[index].mUnknownC - 0xB60B) & 0xFFFFFF;
            }
        }
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            return 1;
        }
    } else {
        return 1;
    }
    return 0;
}

extern "C" void fn_8010A1C4(int team) {
    int i;
    int count = fn_80178D18(team);

    for (i = 0; i < count; i++) {
        PlyrClearPendingMsg(PlyrGet(team, i), 62);
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

    if (BallFindHeldBy(p) == 0 && (kind == 5 || kind == 9)) {
        result = 1;
        memset(&message, 0, 4);
        message.mId = 62;
        message.mUnknown1[0] = 9;
        message.mUnknown1[2] = kind;
        PlyrSetPendingMsg(p, &message, 1);
    }
    return result;
}

extern "C" int fn_8010A2DC(Object_80039F5C *p, int a, short b) {
    int result = 0;
    int mode = fn_800AD9B4();

    

    if (fn_801486A0() != 0 && fn_801486A0() != 1 && (mode == 4 || (mode == 7 && (unsigned char)fn_800ABCC0(lbl_803EAA8C))) &&
        fn_801BE648(p->mpUnknown792) != 0xCB && p->mUnknown9[2] != 0) {
        if (*PlyrGetPendingMsg(p) != 62) {
            if (fn_8010BD58(p) != 0) {
                fn_8010BE54(p);
            } else {
                Message_800F01CC message;
                Vector_80039F5C toBall;

                memset(&message, 0, 4);
                message.mUnknown1[0] = a;
                message.mId = 62;
                BallGetPosition(BallGetCurrent(), &toBall);
                fn_802276B4(&toBall, &toBall, &p->mMotion.mPos);
                if (b == -1) {
                    if (fabsf(p->mMotion.mPos.mY) < fn_80178A2C() - 3.0f &&
                        fabsf(p->mMotion.mPos.mX) < fn_80178A08() - 5.0f && !(p->mFlags & 0x400)) {
                        b = (short)fn_802270A4(&toBall);
                        b += fn_802372EC(0, 100);
                    } else {
                        b = 0;
                    }
                }
                PlyrSetPendingMsg(p, &message, b);
            }
            result = 1;
        } else {
            if (p->mFlags & 0x4000) {
                p->mUnknown3040 = 0;
            }
            if (fabsf(p->mMotion.mPos.mY) > fn_80178A2C() - 3.0f || fabsf(p->mMotion.mPos.mX) > fn_80178A08() - 3.0f) {
                p->mUnknown3040 = 0;
            }
        }
    }
    return result;
}

extern "C" int fn_8010A4E8(Object_80039F5C *p) {
    Block_8010A4E8 *pBlock = (Block_8010A4E8 *)&p->mUnknown336;
    int mode = fn_800AD9B4();

    memset(pBlock, 0, 64);
    pBlock->mUnknown50 = -1;
    if (p->mpUnknown800 != (AnimChannel_t *)(p->mUnknown1244 + 12)) {
        p->mpUnknown800 = (AnimChannel_t *)(p->mUnknown1244 + 12);
    }
    if (fn_801486A0() == 0) {
        return 1;
    }
    if (mode == 4 || mode == 7 || mode == 8) {
        pBlock->mUnknown52State = p->mpState->mUnknown1;
        pBlock->mUnknown52Count = pBlock->mUnknown52State;
        pBlock->mUnknown52Kind = p->mpState->mUnknown3[0];
        pBlock->mUnknown52Mode = 0;
        pBlock->mUnknown52Rest = pBlock->mUnknown48 = 0;
        if (fn_801BE648(p->mpUnknown792) != 0x4A && fn_801BE648(p->mpUnknown792) != 0xCB && fn_800A5DD0(p) == 0) {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 0x4A, 1.0f, p);
        }
        p->mFlags &= ~0x10;
    } else {
        p->mUnknown1008Word = 30;
        fn_80109CA0(p, 0xCB, 0xFF, 0xFF, 0xFF);
        return 1;
    }
    return 0;
}

extern "C" int fn_8010A640(Object_80039F5C *p) {
    Block_8010A640 *pBlock = (Block_8010A640 *)&p->mUnknown336;
    int done = 0;

    if (fn_800A5C04(p, p->mMotion.mFacing, p->mMotion.mFacing) == 0) {
        int mode = fn_800AD9B4();

        pBlock->mUnknown52Timer--;
        if (mode == 4 || mode == 7) {
            switch (pBlock->mUnknown52Mode) {
            case 0:
                break;
            case 1:
                if (pBlock->mUnknown48 != -9999 && --pBlock->mUnknown48 <= 0 && (p->mFlags & 4)) {
                    pBlock->mUnknown52State = 0;
                    pBlock->mUnknown52Mode = 0;
                }
                break;
            case 3: {
                float limit = pBlock->mUnknown52State == 2 ? 0.0f : 0.14f;

                if (limit == 0.0f && p->mMotion.mUnknown28 < 0.04) {
                    p->mMotion.mUnknown28 = 0.0f;
                }
                if (p->mMotion.mUnknown28 > limit) {
                    if (PlyrMoveIsFacingHeading(p)) {
                        p->mUnknown512.mUnknown14 = 10;
                        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown0 = 0.08f;
                    } else {
                        p->mUnknown512.mUnknown14 = 1;
                        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown0 = 0.0f;
                    }
                } else {
                    pBlock->mUnknown52Mode = 0;
                    pBlock->mUnknown52State = 0;
                }
                break;
            }
            case 2: {
                int index;

                pBlock->mUnknown48--;
                fn_8009D1F4(p);
                if (fn_8022781C(&p->mMotion.mPos, &pBlock->mUnknown56) < 6.0f && p->mMotion.mUnknown28 > 0.006f &&
                    fn_800CB708(p, &index, pBlock->mUnknown56, p->mMotion.mFacing, 1)) {
                    pBlock->mUnknown52Mode = 5;
                    fn_800CBB00(p, index, pBlock->mUnknown56, p->mMotion.mFacing, 1);
                } else if (pBlock->mUnknown48 <= 0 || fn_800FF094(p) == 1) {
                    if (pBlock->mUnknown48 <= 0) {
                        if (pBlock->mUnknown48 + 1 > 0 &&
                            fn_800CB708(p, &index, pBlock->mUnknown56, p->mMotion.mFacing, 2)) {
                            fn_800CBB00(p, index, pBlock->mUnknown56, p->mMotion.mFacing, 2);
                            pBlock->mUnknown52Mode = 5;
                        }
                    }
                    if (pBlock->mUnknown52Mode != 5) {
                        pBlock->mUnknown52Mode = 0;
                        pBlock->mUnknown52State = 0;
                        p->mUnknown512.mUnknown14 = 1;
                        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown0 = 0.0f;
                        fn_8009D1AC(p);
                        switch (fn_802372EC(0, 5)) {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                            pBlock->mUnknown52Count = 5;
                            break;
                        case 4:
                            pBlock->mUnknown52Count = 4;
                            break;
                        default:
                            pBlock->mUnknown52Count = 6;
                            break;
                        }
                        pBlock->mUnknown52Count = 5;
                    }
                }
                break;
            }
            case 6:
                if (p->mFlags & 4) {
                    p->mUnknown512.mUnknown14 = 3;
                    p->mFlags &= ~4;
                    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown0 = lbl_803EAF18;
                    pBlock->mUnknown24 = lbl_803EAF18;
                    pBlock->mUnknown52Mode = 2;
                    pBlock->mUnknown0 = 0;
                }
                break;
            case 5:
                if (p->mFlags & 4) {
                    p->mFlags &= ~4;
                    p->mUnknown512.mUnknown0 = 0.0f;
                    p->mUnknown512.mUnknown14 = 3;
                    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                    pBlock->mUnknown52Mode = 2;
                    pBlock->mUnknown0 = 0;
                    pBlock->mUnknown8.mX = p->mMotion.mPos.mX;
                    pBlock->mUnknown8.mY = p->mMotion.mPos.mY;
                }
                break;
            case 4:
                fn_8009D1F4(p);
                if (fn_8010A0A0(p, pBlock->mUnknown50)) {
                    pBlock->mUnknown52Mode = 0;
                    fn_8009D1AC(p);
                    pBlock->mUnknown52Timer = lbl_803EAF04;
                    if (pBlock->mUnknown52State == 1) {
                        float length;

                        p->mUnknown512.mUnknown14 = 3;
                        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
                        length = fn_802372EC(0, lbl_803EAF14) + 2.0f;
                        fn_80227538(&pBlock->mUnknown56, p->mMotion.mFacing, length);
                        fn_80227638(&pBlock->mUnknown56, &pBlock->mUnknown56, &p->mMotion.mPos);
                        fn_800FF598((State_800FDA58 *)pBlock, p, &pBlock->mUnknown56, p->mMotion.mFacing & 0xFFFFFF, 0.0f);
                        pBlock->mUnknown24 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
                        pBlock->mUnknown52Mode = 2;
                        if (length > 4.0f && fn_802372EC(0, 3) == 0) {
                            pBlock->mUnknown52Mode = 3;
                        }
                        pBlock->mUnknown48 = 10000;
                    }
                    pBlock->mUnknown52State = 0;
                }
                break;
            default:
                pBlock->mUnknown52Mode = 0;
                break;
            }
            if (pBlock->mUnknown48 != -9999) {
                fn_801096D4(p);
                if (pBlock->mUnknown48 != -9999 && fn_800E1044(p, (Vector_80039F5C *)&pBlock->mUnknown56)) {
                    p->mUnknown1008Word = 30;
                    fn_80109CA0(p, 0xCB, 0xFF, 0xFF, 0xFF);
                    if (BallGetCurrentHolder() == p) {
                        PossReleaseBall(p);
                    }
                    pBlock->mUnknown52Mode = 1;
                    pBlock->mUnknown48 = -9999;
                    pBlock->mUnknown52State = 6;
                    done = 1;
                }
            }
            if (pBlock->mUnknown52Mode == 0 && done == 0) {
                if (pBlock->mUnknown52Count != 0) {
                    pBlock->mUnknown52State = pBlock->mUnknown52Count;
                } else {
                    pBlock->mUnknown52State = fn_80109D70(p, &pBlock->mUnknown56);
                }
                if (pBlock->mUnknown52State == 10) {
                    fn_800CC388(p);
                } else if (pBlock->mUnknown52State == 5) {
                    fn_80177F70();
                    fn_8016DBE4(p);
                } else {
                    int result;

                    if (fn_80109E48(p, pBlock->mUnknown52State, &result)) {
                        if (result == 1) {
                            pBlock->mUnknown52Mode = 4;
                        }
                    } else if (fn_80109F34(p)) {
                        pBlock->mUnknown48 = fn_802372EC(0, 120) + 10000;
                    } else if (fn_8010A07C(p)) {
                        pBlock->mUnknown52Mode = 3;
                    } else {
                        pBlock->mUnknown48 = fn_802372EC(0, 120) + 30;
                        p->mUnknown1008Word = 30;
                        fn_80109CA0(p, 0xCB, 0xFF, 0xFF, 0xFF);
                        pBlock->mUnknown52Mode = 1;
                    }
                }
            }
        } else {
            p->mUnknown1008Word = 30;
            fn_80109CA0(p, 0xCB, 0xFF, 0xFF, 0xFF);
            return 1;
        }
        pBlock->mUnknown56.mX =
            CLAMP(pBlock->mUnknown56.mX, lbl_803EAF0C - fn_80178A08(), fn_80178A08() - lbl_803EAF0C);
        pBlock->mUnknown56.mY =
            CLAMP(pBlock->mUnknown56.mY, lbl_803EAF0C - fn_80178A44(), fn_80178A44() - lbl_803EAF0C);
    }
    return 0;
}

/* Discarded by SN's linker: only its pool (0.0f at 0x8029EBB8) survives in .rodata. */
// FAKEMATCH: invented body; only its pool constant(s) are target evidence
extern "C" {
static float _StrippedClampNonNegative(float x)
{
    return x > 0.0f ? x : 0.0f;
}
}

extern "C" int fn_8010AEA0(Object_80039F5C *p) {
    fn_8009D1AC(p);
    return 1;
}

extern "C" void fn_8010AEC4(Object_80039F5C *p) {
    lbl_803EAF10 = p;
}

extern "C" void fn_8010AECC(Object_80039F5C *p, unsigned char a, unsigned char b, unsigned char c) {
    fn_8009BD60(p);
    p->mUnknown1008.mUnknown0 = a;
    p->mUnknown1008.mUnknown1 = b;
    p->mUnknown1008.mUnknown2 = c;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 83, 1.0f, p);
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~0x40000;
    p->mFlags &= ~4;
}

extern "C" int fn_8010AF48(Object_80039F5C *p) {
    Block_8010AF48 *pBlock;

    p->mUnknown336 = -1;
    pBlock = (Block_8010AF48 *)&p->mUnknown336;
    pBlock->mUnknown4 = 0;
    pBlock->mUnknown6 = 0;
    pBlock->mUnknown8 = 0;
    pBlock->mUnknown7 = 0;
    if (!(p->mFlags & 0x40000)) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 91, 1.0f, p);
    }
    return 0;
}

extern "C" int fn_8010AFB8(Object_80039F5C *p) {
    Block_8010AFB8 *pBlock = (Block_8010AFB8 *)&p->mUnknown336;
    int team;

    fn_8010A2DC(p, 0, 5);
    if (!(p->mFlags & 0x40000) && fn_801BE648(p->mpUnknown792) != 0x5B) {
        if (p->mFlags & 4) {
            p->mFlags |= 0x40000;
            p->mFlags &= ~4;
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 0x5B, 1.0f, p);
            if (pBlock->mUnknown6 != 0) {
                pBlock->mUnknown6 = 0;
                if (p->mpState[1].mId != 0) {
                    return 1;
                }
            }
        }
    } else {
        if (fn_800B65A0(p->mIdBytes[2]) == 0xFF && pBlock->mUnknown7 == 0 && fn_8016E928() && fn_801486A0() != 2) {
            if (fn_80237260(0) < 0.5f) {
                fn_8010B1FC(p, 2, 0);
            }
            pBlock->mUnknown7 = 1;
        }
        team = p->mIdBytes[2];
        switch (pBlock->mUnknown0) {
        case -1:
            break;
        case 1:
            if (fn_80177FFC(team).mY - p->mMotion.mPos.mY < 3.0f) {
                int id = fn_800B0F98();
                Object_80039F5C *pOther = fn_8009BCE8(&id);

                if (pOther != 0) {
                    fn_8010AECC(p, 6, p->mMotion.mPos.mX > pOther->mMotion.mPos.mX ? 3 : 6, 0xFF);
                }
            }
            break;
        case 2:
            if (fn_80177FFC(team).mY - p->mMotion.mPos.mY < 3.0f) {
                fn_8010AECC(p, 7, 0xFF, 0xFF);
            }
            break;
        }
        pBlock->mUnknown0 = -1;
    }
    return 0;
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

extern "C" int fn_8010B224(Object_80039F5C *p) {
    int result = 1;

    if (fn_801486A0() == 0) {
        result = 0;
    }
    if (p->mFlags & 0x800) {
        result = 0;
    }
    if (p->mpState->mId == 10 || p->mpState->mId == 50) {
        result = 0;
    }
    switch (fn_801BE648(p->mpUnknown792)) {
    case 155:
    case 185:
    case 206:
        result = 0;
        break;
    }
    if (BallGetCurrentHolder() != p) {
        int facing = p->mMotion.mFacing;
        Point_8017886C ahead;

        ahead.mX = fn_801CFB94(facing) * 5.0f + p->mMotion.mPos.mX;
        ahead.mY = fn_801CFB18(facing) * 5.0f + p->mMotion.mPos.mY;
        if (fabsf(ahead.mX) > fn_80178A08() || fabsf(ahead.mY) > fn_80178A44()) {
            result = 0;
        }
        if (result) {
            unsigned char team;

            for (team = 0; team <= 1; team++) {
                float distance;

                fn_801245DC(p, team, 0, fn_80178D18(team), 0x400000, &distance, 0);
                if (distance < 2.0f) {
                    result = 0;
                }
            }
        }
    }
    return result;
}

extern "C" unsigned char fn_8010B3A0(Object_80039F5C *p, int kind) {
    unsigned char result = 0;
    unsigned char i;
    Object_80039F5C *pOther;

    switch (kind) {
    case 5: {
        unsigned int count = fn_80178D18(0);
        for (i = 0; i < count; i++) {
            result |= fn_8010B87C(p, PlyrGet(0, i));
            if (result) {
                break;
            }
        }
        count = fn_80178D18(1);
        for (i = 0; i < count; i++) {
            result |= fn_8010B87C(p, PlyrGet(1, i));
            if (result) {
                break;
            }
        }
        break;
    }
    case 4: {
        pOther = BallGetCurrentHolder();
        if (pOther != 0) {
            result = fn_8010B87C(p, pOther);
        }
        break;
    }
    case 3: {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        for (i = 0; i < count; i++) {
            pOther = PlyrGet(p->mIdBytes[2] ^ 1, i);
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
            result = fn_8010B87C(p, PlyrGet(p->mIdBytes[2], i));
            if (result) {
                break;
            }
        }
        break;
    }
    case 2: {
        unsigned int count = fn_80178D18(p->mIdBytes[2]);
        for (i = 0; i < count; i++) {
            result = fn_8010B87C(p, PlyrGet(p->mIdBytes[2] ^ 1, i));
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

    if (BallGetCurrentHolder() != p) {
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
    } else if (!TutorialIsActive() || fn_801485D4()) {
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
    } else if (TutorialIsStepDone()) {
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
            if (pRecord->mUnknown4.mUnknown0 == kinds[j] && fn_8010B3A0(p, pRecord->mUnknown4.mUnknown1)) {
                if ((pRecord->mUnknown4.mUnknown2 == 1 && p->mUnknown776 == 2) ||
                    (pRecord->mUnknown4.mUnknown2 == 2 && p->mUnknown776 == 1) || BallGetCurrentHolder() != p) {
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

extern "C" unsigned char fn_8010B87C(Object_80039F5C *p, Object_80039F5C *pOther) {
    unsigned char result = 0;

    if (pOther != 0 && p != 0 && pOther != p) {
        Point_8017886C delta;
        int angle;

        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX);
        if (fn_802270A4(&delta) <= 5.0f) {
            result = MathAngleDiff(angle, p->mMotion.mFacing) <= 0xE38E2;
        }
    }
    return result;
}

extern "C" int fn_8010B924(Object_80039F5C *p) {
    int kind;

    if (!TutorialIsActive() || fn_801485D4()) {
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
    } else if (TutorialIsStepDone()) {
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
    if (pState->mUnknown2 == 0 && BallGetCurrentHolder() != p) {
        pState->mUnknown0 = 1;
    }
    return 0;
}

extern "C" int fn_8010BA90(Object_80039F5C *p) {
    Block_8010BC90 *pBlock = (Block_8010BC90 *)&p->mUnknown336;
    Message_800F01CC message;

    if (pBlock->mUnknown0) {
        p->mFlags &= ~4;
        memset(&message, 0, 4);
        message.mId = 62;
        message.mUnknown1[0] = 0;
        message.mUnknown1[1] = 0;
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (pBlock->mUnknown1 > 0) {
        pBlock->mUnknown1--;
    } else {
        if (fn_801BE648(p->mpUnknown792) != 206) {
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 206, 1.0f, p);
            if (fn_802372EC(0, 10) <= 4) {
                switch (pBlock->mUnknown2) {
                case 1:
                case 2:
                    fn_800A3B58(p, 9, 0);
                    break;
                case 3:
                case 4:
                    fn_800A3B58(p, 6, 0);
                    break;
                }
            }
        }
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            memset(&message, 0, 4);
            message.mId = 62;
            message.mUnknown1[0] = 0;
            message.mUnknown1[1] = 0;
            fn_800F053C(0, p->mpState, &message, p);
            if (pBlock->mUnknown3 != 255) {
                lbl_802DABBC[pBlock->mUnknown3] = 0;
            }
            return 1;
        }
        if (p->mFlags & 0x1000) {
            if (BallGetCurrentHolder() == p) {
                PossReleaseBall(p);
            }
            p->mFlags &= ~0x1000;
        }
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

extern "C" int fn_8010BC90(Table_8010B738 *pTable, unsigned short key, void *pData, AnimChannel_t *pEntries,
                           Object_80039F5C *p, unsigned int mode) {
    Block_801BE60C *pRecord = fn_801BE60C(p->mpUnknown792, key);
    Block_8010BC90 *pBlock = (Block_8010BC90 *)&p->mUnknown336;

    switch (mode) {
    case 0: {
        unsigned char index = fn_8010B738(p, pTable);

        if (index != 255) {
            pBlock->mUnknown3 = index;
            pRecord->mUnknown0Word = AnimChanStartAnim(pData, pEntries, pTable->mEntries[index].mUnknown0,
                                                 pTable->mEntries[index].mUnknown2, key, p, 1.0f);
            lbl_802DABBC[index] = 1;
        } else {
            pBlock->mUnknown0 = 1;
        }
        break;
    }
    case 1:
    case 3:
        break;
    }
    return 0;
}

extern "C" int fn_8010BD58(Object_80039F5C *p) {
    int result = 0;

    if (fn_8010B224(p)) {
        Vector_80039F5C toBall;
        float dist;
        float chance;
        float limit;
        int index;

        BallGetPosition(BallGetCurrent(), &toBall);
        fn_80227690(&toBall, &toBall, &p->mMotion.mPos);
        dist = fn_802270A4(&toBall);
        chance = 1.2f;
        chance -= dist * 0.15f;
        index = fn_800A2178();
        limit = lbl_802DAB74[index];
        if (TutorialIsActive() && !fn_801485D4()) {
            if (TutorialIsStepDone()) {
                limit = 1.0f;
            } else {
                limit = 0.75f;
            }
        }
        if (chance < limit) {
            chance = limit;
        }
        if (fn_80237260(0) < chance) {
            result = 1;
        }
    }
    return result;
}

extern "C" void fn_8010BE54(Object_80039F5C *p)
{
    Message_800F01CC message;

    memset(&message, 0, 4);
    message.mId = 93;
    PlyrSetPendingMsg(p, &message, 0);
}

extern "C" void fn_8010BEA4(void)
{
    memset(lbl_802DABBC, 0, 100);
}

extern "C" int fn_8010BED4(Object_80039F5C *p)
{
    State_8010BED4 *pState = (State_8010BED4 *)&p->mUnknown336;

    pState->mUnknown8 = p->mMotion.mUnknown32;
    pState->mUnknown12 = p->mMotion.mFacing;
    pState->mUnknown4 = p->mUnknown528.mUnknown0;
    pState->mUnknown48 = 0;
    pState->mUnknown0 = p->mMotion.mPos.mX - fn_80177FE0().mX;
    pState->mUnknown52 = 0;
    pState->mUnknown16 = lbl_803EAF30;
    pState->mUnknown56 = p->mpState->mUnknown2;
    return 0;
}

/* Update handler of the state fn_8010BED4 enters (player state table at
   0x802DBA78): counts frames, rerolls the +48 timer from rating 8 and, when it
   expires, picks a spot beside the ball carrier (offset away from a team-mate
   in state 85, clamped to the field) and the heading and speed towards it.
   Sends message 2 (give up) or 24 and returns 1, else posts the move. */
extern "C" int fn_8010BF5C(Object_80039F5C *p)
{
    Message_800F01CC message;
    State_8010BF5C *pState = (State_8010BF5C *)&p->mUnknown336;
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_80039F5C *pCarrier;
    Point_8017886C ball;
    Point_8017886C target;
    Point_8017886C delta;
    Vector_80039F5C ballPos;
    float side = 0.0f;
    float reach = pState->mUnknown16;
    int expired = 0;
    int result = 0;
    int deep = 0;

    ball = fn_80177FE0();
    PlayTrackGetResult5Rate();
    fn_8010A2DC(p, 0, -1);
    pState->mUnknown52++;
    pCarrier = BallGetCurrentHolder();
    BallGetPosition(BallGetCurrent(), &ballPos);
    pState->mUnknown48 = (signed char)(pState->mUnknown48 - 1);
    if (pState->mUnknown48 < 0) {
        int rating = 255 - p->mRatings[8];

        if (rating < 0) {
            rating = 0;
        }
        pState->mUnknown48 = (signed char)(pState->mUnknown48 + 2 + fn_802372EC(0, (unsigned int)rating >> 5));
        if (pCarrier && fn_800B65A0(p->mIdBytes[2]) != 255
            && fn_800B65A0(pCarrier->mIdBytes[2]) == 255 && !fn_80177C38()) {
            pState->mUnknown48 -= (short)MIN((float)pState->mUnknown48,
                                             (float)pState->mUnknown48 * PlayTrackGetPlayIdRate());
            if (fn_8011F1CC() && (pCarrier->mFlags & 0x8000)) {
                pState->mUnknown48 -= (short)MIN((float)pState->mUnknown48,
                                                 (float)pState->mUnknown48 * PlayTrackGetResult5Rate());
            }
        }
        expired = 1;
    }
    if (!(p->mFlags & 0x4000) && expired) {
        if (pCarrier == 0 && BallStateGet(BallGetCurrent(), 0) == 4) {
            pCarrier = BallGetCurrentLastHolder();
        }
        if (pCarrier != 0) {
            unsigned int i;
            unsigned int count = fn_80178D18(p->mIdBytes[2]);
            const float margin = 2.0f;

            for (i = 0; i < count; i++) {
                if (i != (p->mId >> 16 & 0xFF)) {
                    Object_80039F5C *pOther = PlyrGet(p->mId >> 8 & 0xFF, i);

                    if (pOther->mpState->mId == 85) {
                        if (pOther->mMotion.mPos.mX > p->mMotion.mPos.mX) {
                            side = -lbl_803EAF44;
                        } else {
                            side = lbl_803EAF44;
                        }
                        if ((pCarrier->mMotion.mPos.mX > ball.mX && p->mMotion.mPos.mX > pOther->mMotion.mPos.mX)
                            || (pCarrier->mMotion.mPos.mX < ball.mX
                                && p->mMotion.mPos.mX < pOther->mMotion.mPos.mX)) {
                            if (pCarrier->mFlags & 0x8000) {
                                memset(&message, 0, 4);
                                message.mId = 2;
                                message.mUnknown1[0] = 1;
                                fn_800F053C(0, p->mpState, &message, p);
                                return 1;
                            }
                        }
                    }
                }
            }
            if (pState->mUnknown52 > pState->mUnknown56 && pState->mUnknown56 != 0) {
                memset(&message, 0, 4);
                message.mId = 2;
                message.mUnknown1[0] = 1;
                fn_800F053C(0, p->mpState, &message, p);
                return 1;
            }
            if (((pCarrier->mFlags & 0x8000) && pState->mUnknown52 > lbl_803EAF38
                 && ball.mY - pCarrier->mMotion.mPos.mY < reach * lbl_803EAF3C)
                || ((float)pState->mUnknown52 > lbl_803EAF34 && (pCarrier->mFlags & 0x8000)
                    && ball.mY - pCarrier->mMotion.mPos.mY < reach)) {
                memset(&message, 0, 4);
                message.mId = 2;
                message.mUnknown1[0] = 1;
                fn_800F053C(0, p->mpState, &message, p);
                return 1;
            }
            target.mX = pCarrier->mMotion.mPos.mX + side;
            target.mX = target.mX < margin - fn_80178A08() ? margin - fn_80178A08()
                : (target.mX > fn_80178A08() - margin ? fn_80178A08() - margin : target.mX);
            target.mY = ball.mY + lbl_803EAF2C;
            target.mY = MIN(target.mY, fn_80178A2C() + margin);
            fn_80227690(&delta, &target, &pMotion->mPos);
            {
                float dist = fn_802270A4(&delta);
                float dx = fabsf(pMotion->mPos.mX - target.mX);
                float near = lbl_803EAF24;
                float wide = lbl_803EAF28;
                int angle;

                if (pMotion->mUnknown28 != 0.0f) {
                    near *= 0.5f;
                    wide *= 0.5f;
                }
                pState->mUnknown28 = dx;
                pState->mUnknown40 = target;
                pState->mUnknown32 = wide;
                pState->mUnknown20 = dist;
                pState->mUnknown24 = near;
                pState->mUnknown36 = pCarrier->mMotion.mUnknown32;
                angle = MathAngleDiff(pCarrier->mMotion.mUnknown32, 0x400000);
                if ((dx > wide && (angle > 0x200000 && angle < 0x600000) && fn_800DC21C(pCarrier))
                    || dx > wide + wide || (dx > 0.5f && pState->mUnknown4 == 1.0f)) {
                    pState->mUnknown8 = delta.Heading() & 0xFFFFFF;
                    pState->mUnknown12 = delta.Heading();
                    pState->mUnknown4 = 1.0f;
                } else if (dist > near || dx > wide) {
                    pState->mUnknown8 = delta.Heading() & 0xFFFFFF;
                    pState->mUnknown12 = 0xC00000;
                    pState->mUnknown4 = 0.9f;
                } else {
                    pState->mUnknown8 = 0xC00000;
                    pState->mUnknown4 = 0.0f;
                    pState->mUnknown12 = 0xC00000;
                }
            }
        }
    }
    if (fn_800A5C04(p, pState->mUnknown8, pState->mUnknown12)) {
        return 0;
    }
    if (!(p->mFlags & 0x4000)) {
        if (expired) {
            int kind;

            result = fn_8009F7A4(p, 0) == 1;
            kind = fn_8009E180(p);
            if (kind > 2) {
                switch (kind) {
                default:
                    if (fn_802372EC(0, 255) < (unsigned short)(p->mRatings[8] / 2)) {
                        memset(&message, 0, 4);
                        message.mId = 2;
                        message.mUnknown1[0] = 1;
                        fn_800F053C(0, p->mpState, &message, p);
                        return 1;
                    }
                    break;
                case 4: {
                    int go = 0;
                    Object_80039F5C *pTarget = BallGetCurrentTarget();

                    if (pTarget != 0) {
                        if (fabsf(pTarget->mMotion.mPos.mX - p->mMotion.mPos.mX) < 12.0f) {
                            Ball_t *pBall = BallGetCurrent();
                            Vector_80039F5C landing;

                            if (BallGetLandingPoint(pBall, &landing)) {
                                if (fabsf(landing.mX - fn_80177FE0().mX) > 8.0f) {
                                    go = fn_802372EC(0, 32) < (unsigned int)((p->mRatings[8] >> 5) + 8);
                                } else {
                                    Vector_80039F5C velocity;

                                    BallGetVelocity(pBall, &velocity);
                                    if ((landing.mY < p->mMotion.mPos.mY + 12.0f
                                         && fn_802372EC(0, 100) < (unsigned int)((p->mRatings[8] >> 5) + 8))
                                        || velocity.mZ < 0.0f) {
                                        go = 1;
                                    }
                                }
                            }
                        }
                        if (ballPos.mY > p->mMotion.mPos.mY + lbl_803EAF40) {
                            go = 1;
                            deep = 1;
                        }
                    } else {
                        go = 1;
                    }
                    if (go == 1 && (fn_8009F0B8(p, 0x2AAAAA) || deep)) {
                        memset(&message, 0, 4);
                        message.mId = 24;
                        message.mUnknown1[0] = 2;
                        fn_800F053C(0, p->mpState, &message, p);
                        return 1;
                    }
                    break;
                }
                case 6:
                    memset(&message, 0, 4);
                    message.mId = 2;
                    message.mUnknown1[0] = 1;
                    fn_800F053C(0, p->mpState, &message, p);
                    return 1;
                }
            }
        }
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pState->mUnknown8;
        p->mUnknown512.mUnknown8 = pState->mUnknown12;
        p->mUnknown512.mUnknown0 = pState->mUnknown4;
        if (pState->mUnknown4 == 1.0f) {
            p->mUnknown512.mUnknown15 = 1;
        }
    }
    return result;
}

extern "C" int fn_8010C864(Object_80039F5C *p)
{
    int found = 0;
    unsigned char i;
    unsigned int count = fn_80178D18(fn_80178308());

    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther = PlyrGet(fn_80178308(), i);

        if (pOther != p && fn_800F06F4(0, pOther->mpState, 26, 0xFFFF) != 0xFFFF) {
            found = 1;
            break;
        }
    }
    return found;
}

extern "C" int fn_8010C8F8(Object_80039F5C *p) {
    int result = 0;
    float range = 1.0f;
    Ball_t *pBall;
    Vector_80039F5C pos;
    Point_8017886C delta;

    BallGetCurrentHolder();
    pBall = BallFindTargeting(p);
    if (pBall == 0) {
        pBall = BallGetCurrent();
        range = 1.5f;
    }
    BallGetPosition(pBall, &pos);
    fn_80227690(&delta, &pos, &p->mMotion.mPos);
    if (fn_802270A4(&delta) < range) {
        result = 1;
    }
    return result;
}

extern "C" void fn_8010C98C(Object_80039F5C *p) {
    int pick = 1;
    Ball_t *pBall;
    Vector_80039F5C pos;
    int index;

    pBall = BallFindTargeting(p);
    if (pBall == 0) {
        pBall = BallGetCurrent();
    }
    BallGetPosition(pBall, &pos);
    fn_8009BD60(p);
    index = fn_800F06F4(0, p->mpState, 26, 0xFFFF);
    if (index != 0xFFFF) {
        switch (p->mpState[index].mUnknown2) {
        case 2:
        case 3:
            p->mUnknown1008.mUnknown0 = 1;
            pick = 0;
            break;
        case 4:
        case 5:
            p->mUnknown1008.mUnknown0 = 2;
            pick = 0;
            break;
        default:
            pick = 1;
            break;
        }
    }
    if (pick) {
        if (fn_8011F1A4()) {
            if (fn_8011F1A4() && (fn_8011F4C8() & 1)) {
                p->mUnknown1008.mUnknown0 = 1;
            } else {
                p->mUnknown1008.mUnknown0 = 2;
            }
        } else {
            Point_8017886C delta;

            fn_80227690(&delta, &pos, &p->mMotion.mPos);
            if (((fn_801CFE40(delta.mY, delta.mX) - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                p->mUnknown1008.mUnknown0 = 1;
            } else {
                p->mUnknown1008.mUnknown0 = 2;
            }
        }
    }
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 78, 1.0f, p);
    p->mUnknown512.mUnknown14 = 0;
}

extern "C" int fn_8010CAE8(Object_80039F5C *p)
{
    State_8010CAE8 *pState = (State_8010CAE8 *)&p->mUnknown336;

    fn_800FD2AC(p);
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = pState->mUnknown16;
    p->mUnknown512.mUnknown4 = pState->mUnknown16;
    p->mUnknown512.mUnknown0 = pState->mUnknown12;
    pState->mUnknown20 = 0;
    pState->mUnknown24 = 0;
    return fn_8010C864(p) == 0;
}

extern "C" int fn_8010CB58(Object_80039F5C *p) {
    int result = 0;
    Block_8010CB58 *pBlock = (Block_8010CB58 *)&p->mUnknown336;
    int animation;

    fn_800B8344(p);
    animation = fn_801BE648(p->mpUnknown792);
    switch (pBlock->mUnknown20) {
    case 0:
        if ((unsigned int)(animation - 30) <= 1 || animation == 202 || animation == 200) {
            p->mUnknown512.mUnknown14 = 0;
            pBlock->mUnknown20 = 1;
        } else {
            Object_80039F5C *pCarrier;

            result = fn_800FD580(p);
            pCarrier = BallGetCurrentHolder();
            if (pCarrier != 0 && pCarrier->mpState->mId == 18 && (p->mFlags & 0x4000)) {
                result = 1;
            }
            if (fn_8010C8F8(p)) {
                fn_8010C98C(p);
                pBlock->mUnknown20 = 1;
            }
        }
        break;
    case 1:
        if (BallGetCurrentHolder() == p && animation == 74) {
            pBlock->mUnknown20 = 2;
        }
        if (p->mFlags & 4) {
            p->mFlags &= ~4;
            pBlock->mUnknown24 = 20;
            pBlock->mUnknown20 = 2;
        } else if (!((unsigned int)(animation - 30) <= 1 || animation == 202 || animation == 200)) {
            if (animation == 78) {
                p->mUnknown512.mUnknown14 = 0;
            } else {
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = pBlock->mUnknown16;
                p->mUnknown512.mUnknown4 = pBlock->mUnknown16;
                p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
            }
        }
        break;
    case 2: {
        int has18 = fn_800F06F4(0, p->mpState, 18, 0xFFFF) != 0xFFFF;
        int has26 = fn_800F06F4(0, p->mpState, 26, 0xFFFF) != 0xFFFF;
        int has25 = fn_800F06F4(0, p->mpState, 25, 0xFFFF) != 0xFFFF;

        if (p == BallGetCurrentHolder() && !has18 && !has26 && !has25) {
            Message_800F01CC message;

            memset(&message, 0, 4);
            message.mId = 1;
            fn_800F053C(0, p->mpState, &message, p);
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
            p->mUnknown512.mUnknown0 = 0.72f;
        } else if (!has18) {
            if (--pBlock->mUnknown24 < 0) {
                result = 1;
            } else {
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown8 = pBlock->mUnknown16;
                p->mUnknown512.mUnknown4 = pBlock->mUnknown16;
                p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
            }
        } else {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = pBlock->mUnknown16;
            p->mUnknown512.mUnknown4 = pBlock->mUnknown16;
            p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
            result = 1;
        }
        break;
    }
    }
    return result;
}

extern "C" int fn_8010CE2C(Object_80039F5C *p)
{
    int result = 0;

    if (p->mpState->mId == 27 && ((State_8010CAE8 *)&p->mUnknown336)->mUnknown20 == 2) {
        if (fn_8011F25C() || fn_8011F290()) {
            result = 1;
        }
    }
    return result;
}

extern "C" int fn_8010CE90(Object_80039F5C *p, Ball_t *pBall)
{
    State_8010CAE8 *pState = (State_8010CAE8 *)&p->mUnknown336;

    return fn_80112C04(p, pBall, &pState->mUnknown16, &pState->mUnknown12);
}

/* Posts message 68 to the player's queue with the facing and a 0-255
   effort level taken from the move speed (scaled by rating 4 for a player
   whose id byte 3 is 1); kind 11 also finishes the running-style run. */
extern "C" void fn_8010CEB8(Object_80039F5C *p, int kind)
{
    Message_800F01CC message;
    float speed = p->mUnknown528.mUnknown0;
    float level;

    if (p->mIdBytes[3] == 1) {
        float scale = speed * 0.0052287583f;
        speed = scale * p->mRatings[4];
    }
    level = speed < lbl_803EAF48 ? lbl_803EAF48 : (speed > lbl_803EAF4C ? lbl_803EAF4C : speed);
    level *= 255.0f;
    message.mId = 68;
    message.mUnknown1[0] = 160;
    message.mUnknown1[1] = p->mMotion.mFacing >> 17;
    message.mUnknown1[2] = level < 0.0f ? 0 : (unsigned char)(level > 255.0f ? 255.0f : level);
    fn_800F00D4(0, p->mpState, &message, p);
    if (kind == 11) {
        StyleTrackerFinishRun();
    }
}

extern "C" void fn_8010CFD4(Object_80039F5C *p)
{
    if (((p->mMotion.mUnknown32 - 0x400000) & 0xFFFFFF) > 0x800000) {
        p->mUnknown512.mUnknown15 = 15;
    } else {
        p->mUnknown512.mUnknown15 = 16;
    }
}

extern "C" int fn_8010D004(Object_80039F5C *p)
{
    State_8010CAE8 *pState = (State_8010CAE8 *)&p->mUnknown336;
    int result;

    if (BallGetCurrentHolder() != p) {
        fn_800FD2AC(p);
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = pState->mUnknown16;
        p->mUnknown512.mUnknown4 = pState->mUnknown16;
        p->mUnknown512.mUnknown0 = pState->mUnknown12;
        fn_8010CFD4(p);
        fn_8009A8D4(&pState->mUnknown24);
        pState->mUnknown44 = p->mMotion.mPos.mX;
        pState->mUnknown48 = p->mMotion.mPos.mY;
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

extern "C" int fn_8010D090(Object_80039F5C *p) {
    Block_8010D090 *pBlock = (Block_8010D090 *)&p->mUnknown336;
    int result = 0;
    Object_80039F5C *pCarrier;
    Message_800F01CC message;
    Message_800F01CC message2;

    fn_800B8344(p);
    pCarrier = BallGetCurrentHolder();
    fn_8010A2DC(p, 0, 0);
    if (*PlyrGetPendingMsg(p) == 0x39) {
        p->mUnknown3040 = 0;
    }
    if (pCarrier == p) {
        int id = fn_800F06F4(0, p->mpState, 0x1A, 0xFFFF);

        if (id == 0xFFFF && fn_800F06F4(0, p->mpState, 0x12, 0xFFFF) == id) {

            memset(&message, 0, 4);
            message.mId = 1;
            fn_800F053C(0, p->mpState, &message, p);
        } else {
            result = 1;
        }
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
        p->mUnknown512.mUnknown15 = 0;
    } else {
        Ball_t *pBall = BallGetCurrent();

        if (BallStateGet(pBall, 0) == 3) {
            int angle = fn_80099734(p, pBall, 0, 1, 120.0f, pBlock->mUnknown24, 1, 0, 0, 0);

            if (angle != 0x1FFFFFFF && fn_80099F04(p, angle, BallGetIndex(pBall)) == 1) {
                return 0;
            }
            result = fn_8010CE90(p, pBall);
        } else {
            unsigned char *pRecord = 0;

            if (pCarrier != 0) {
                switch (pCarrier->mpState->mId) {
                case 10:
                case 0x3A:
                    pRecord = ((Carrier_8010D090 *)&pCarrier->mUnknown336)->mUnknown20;
                    break;
                case 16:
                    pRecord = ((Carrier_8010D090 *)&pCarrier->mUnknown336)->mUnknown32;
                    break;
                }
                if (pRecord != 0 && pRecord[1] == 0) {
                    switch (p->mpState[1].mId) {
                    case 0:
                    case 0x12:
                    case 0x1A:
                        memset(&message2, 0, 4);
                        message2.mId = 0x5A;
                        message2.mUnknown1[0] = 0;
                        message2.mUnknown1[1] = 0xE0;
                        fn_800F053C(0, p->mpState, &message2, p);
                        break;
                    }
                    result = 1;
                }
            }
            if (fn_8022781C(&pBlock->mUnknown44, &p->mMotion.mPos) > (float)p->mpState->mUnknown1 * 0.125f) {
                result = 1;
            }
        }
        if (result != 1) {
            fn_800FD580(p);
            fn_8010CFD4(p);
        }
    }
    return result;
}

extern "C" int fn_8010D36C(Object_80039F5C *p, Ball_t *pBall, State_8010D80C *pState)
{
    int result = 0;
    Vector_80039F5C pos;
    Vector_80039F5C velocity;
    float time;

    if (pState->mUnknown26 == 0) {
        BallGetPosition(pBall, &pos);
        BallGetVelocity(pBall, &velocity);
        time = fn_8022781C(&pos, pState) / fn_802270A4(&velocity);
        result = pState->mUnknown16 >= time;
    }
    if (result && (p->mUnknown1008.mUnknown0 == 2 || p->mUnknown1008.mUnknown0 == 3)) {
        if (BallStateGet(pBall, 0) != 2) {
            result = 0;
        }
    }
    return result;
}

extern "C" void fn_8010D434(Object_80039F5C *p, State_8010D80C_8010D434 *pState) {
    p->mFlags &= ~4;
    if (p->mUnknown1008.mUnknown0 == 2) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 176, 1.0f, p);
    } else {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 37, 1.0f, p);
    }
    if (pState->mUnknown27) {
        AnimChannel_t *pEntries = p->mpUnknown800;
        AnimChannel_t *pEntry = &pEntries[AnimChanGetStateChannelByIndex(p->mpUnknown796, pEntries, 37, 0)];

        AnimChanSetMirrored(pEntry, !AnimChanIsMirrored(pEntry));
    }
    pState->mUnknown26 = 1;
}

extern "C" void fn_8010D508(Object_80039F5C *p) {
    State_80039F5C *pState = p->mpState;
    Block_8010D508 *pBlock = (Block_8010D508 *)&p->mUnknown336;
    int close = 0;
    int flip = 0;
    int index;
    Object_80039F5C *pCarrier;
    Info_8010D508 *pInfo;
    Vector_80039F5C offset;
    Vector_80039F5C pivot;

    pBlock->mUnknown27 = 0;
    fn_8009BD60(p);
    pCarrier = BallGetHolder(BallGetCurrent());
    if (fn_8022781C(&p->mMotion.mPos, &pCarrier->mMotion.mPos) < 2.5f) {
        AnimFileGetStateAnimList(1, 0x25, (Table_80089904 *)&lbl_80319ED8);
        p->mUnknown1008.mUnknown0 = 1;
        close = 1;
    } else {
        AnimFileGetStateAnimList(1, 0xB0, (Table_80089904 *)&lbl_80319ED8);
        p->mUnknown1008.mUnknown0 = 2;
    }
    p->mUnknown1008.mUnknown1 = pState->mUnknown1;
    index = fn_8009C4B0((Table_80089904 *)&lbl_80319ED8, &p->mUnknown1008);
    pBlock->mUnknown24 = lbl_80319ED8.mEntries[index].mUnknown0;
    pBlock->mUnknown20 = lbl_80319ED8.mEntries[index].mUnknown2;
    pInfo = (Info_8010D508 *)lbl_80319ED8.mEntries[index].mpUnknown4;
    pBlock->mUnknown16 = pInfo->mUnknown32;
    offset = pInfo->mUnknown8;
    pivot = pInfo->mUnknown20;
    

    if (flip) {
        offset.mY = -offset.mY;
        pivot.mY = -pivot.mY;
    }
    pBlock->mUnknown0.mX = offset.mX;
    pBlock->mUnknown0.mY = offset.mY;
    pBlock->mUnknown0.mZ = offset.mZ;
    fn_80227690(pBlock, pBlock, &pivot);
    fn_80227264(pBlock, pBlock, p->mUnknown768);
    fn_80227638(pBlock, pBlock, &pivot);
    fn_80227384(pBlock, pBlock, p->mMotion.mFacing);
    fn_8022765C(pBlock, pBlock, &p->mMotion.mPos);
    if (close) {
        fn_8010D434(p, (State_8010D80C_8010D434 *)pBlock);
    } else {
        pBlock->mUnknown26 = close;
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

extern "C" int fn_8010D734(Object_80039F5C *p)
{
    int result = 0;
    State_8010D80C *pState = (State_8010D80C *)&p->mUnknown336;
    Ball_t *pBall;
    Record_800B15FC *pRecord;
    Vector_80039F5C pos;

    fn_800B8344(p);
    pBall = BallGetCurrent();
    BallGetPosition(pBall, &pos);
    if (fn_8010D36C(p, pBall, pState)) {
        fn_8010D434(p, (State_8010D80C_8010D434 *)pState);
    } else if ((p->mFlags & 4) && BallFindHeldBy(p)) {
        pRecord = fn_800B15FC();
        result = 1;
        pRecord->mUnknownC = pos.mX;
        pRecord->mUnknown10 = pos.mY;
        fn_8009BD2C(p, &pRecord->mUnknown0);
        pRecord->mUnknown14 = 4;
        fn_800B1508();
        BallSetTransferKind(pBall, 0);
        p->mFlags &= ~4;
    }
    return result;
}

extern "C" void fn_8010D80C(Object_80039F5C *p, Vector_80039F5C *pOut)
{
    State_8010D80C *pState = (State_8010D80C *)&p->mUnknown336;

    pOut->mX = pState->mUnknown0.mX;
    pOut->mY = pState->mUnknown0.mY;
    pOut->mZ = pState->mUnknown0.mZ;
}

extern "C" float fn_8010D82C(Object_80039F5C *p)
{
    return ((State_8010D80C *)&p->mUnknown336)->mUnknown16;
}

extern "C" int fn_8010D834(Table_80089904 *pTable, unsigned short key, void *pData, AnimChannel_t *pEntries,
                           Object_80039F5C *p, unsigned int mode) {
    if (mode == 0) {
        if (p->mpState->mId == 56) {
            Block_8010BC90_8010D834 *pBlock = (Block_8010BC90_8010D834 *)&p->mUnknown336;

            AnimChanStartAnim(pData, pEntries, pBlock->mUnknown24, pBlock->mUnknown20, key, p, 1.0f);
        } else {
            int index = fn_8009C4B0(pTable, &p->mUnknown1008);

            if (index >= 0) {
                AnimChanStartAnim(pData, pEntries, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2,
                            key, p, 1.0f);
            }
        }
    }
    return 0;
}

extern "C" int fn_8010D8F4(Object_80039F5C *p) {
    int result = 0;
    Object_80039F5C *pCarrier;

    if (fn_801486A0() != 2 || fn_801783AC(20)) {
        pCarrier = BallGetCurrentHolder();
        if (pCarrier != 0 && pCarrier->mpState->mId == 1 && pCarrier->mMotion.mPos.mY > p->mMotion.mPos.mY &&
            fn_8022781C(&pCarrier->mMotion.mPos, &p->mMotion.mPos) < 7.0f) {
            Object_80039F5C *pBlocker = fn_8010DA38(pCarrier, p);

            if (pBlocker == 0) {
                result = 1;
            } else if (p->mRatings[4] > pBlocker->mRatings[4] * lbl_803EAF54) {
                Message_800F01CC message;

                result = 1;
                memset(&message, 0, 4);
                message.mId = 33;
                fn_800F053C(0, pBlocker->mpState, &message, pBlocker);
            }
        }
    }
    return result;
}

extern "C" Object_80039F5C *fn_8010DA38(Object_80039F5C *p, Object_80039F5C *pExclude)
{
    unsigned char i;
    unsigned int count = fn_80178D18(p->mIdBytes[2]);

    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther = PlyrGet(p->mIdBytes[2], i);

        if (pOther != pExclude && pOther->mpState->mId == 90) {
            return pOther;
        }
    }
    return 0;
}

extern "C" void fn_8010DAB4(Object_80039F5C *p, Steer_8010DAB4 *pOut) {
    Object_80039F5C *pCarrier = BallGetCurrentHolder();
    Object_800B26B0 *pMotion = &p->mMotion;
    Ball_t *pBall = BallGetCurrent();
    int open = fn_80177F70() == 0;
    int ahead = open;
    int last;
    Object_80039F5C *pMate;
    Vector_80039F5C ballPos;
    Vector_80039F5C vel;
    Point_8017886C target;

    pOut->mUnknown22 = 0;
    if (!pCarrier && BallStateGet(pBall, 0) == 3) pCarrier = BallGetTarget(pBall);
    if (pCarrier) {
        Object_800B26B0 *pCarrierMotion = &pCarrier->mMotion;

        if (pCarrier->mpState->mId == 1) {
            BallGetPosition(BallGetCurrent(), &ballPos);
            if (pCarrier->mMotion.mPos.mX < pMotion->mPos.mX) {
                target.mX = pCarrier->mMotion.mPos.mX + 3.0f;
            } else {
                target.mX = pCarrier->mMotion.mPos.mX - 3.0f;
            }
            target.mX = CLAMP(target.mX, 2.0f - fn_80178A08(), fn_80178A08() - 2.0f);
            last = (unsigned int)fn_80178D70(fn_80178320()) / 2;
            last--;
            if (last < 0) last = 0;
            pMate = PlyrGet(fn_80178320(), fn_8012078C()->mpUnknown4[last]);
            if (pMate->mMotion.mPos.mY < pCarrierMotion->mPos.mY) {
                ahead = 0;
                target.mY = pCarrierMotion->mPos.mY - 2.0f;
            } else {
                float y = pMotion->mPos.mY;

                if (y < pCarrierMotion->mPos.mY) {
                    target.mY = pCarrierMotion->mPos.mY + 3.0f;
                    if (pCarrierMotion->mUnknown32 > 0x200000 && pCarrierMotion->mUnknown32 < 0x600000) {
                        target.mY += 3.0f;
                    }
                } else if (pCarrierMotion->mUnknown44 <= 0.0f && pCarrierMotion->mUnknown28 > 0.0f) {
                    target.mY = y - 3.0f;
                } else {
                    target.mY = y + 3.0f;
                }
            }
            fn_80227690(&target, &target, &pMotion->mPos);
            pOut->mHeading = target.Heading();
        } else {
            pOut->mHeading = pMotion->mFacing & 0xFFFFFF;
            pOut->mHeading = CLAMP(pOut->mHeading, 0x200000, 0x600000);
        }
        pOut->mHeading &= 0xFFFFFF;
        if (pMotion->mPos.mY < pCarrierMotion->mPos.mY || fabsf(pCarrierMotion->mPos.mX - pMotion->mPos.mX) > 8.0f) {
            if (pOut->mHeading <= 0x7FFFFF) {
                if (pOut->mHeading <= 0x3FFFFF) {
                    pOut->mHeading += MathAngleDiff(pOut->mHeading, 0x400000) / 3;
                } else {
                    pOut->mHeading -= MathAngleDiff(pOut->mHeading, 0x400000) / 3;
                }
            }
            pOut->mSpeed = 0.72f;
            if (fn_801783AC(0) && !open) pOut->mSpeed = 0.4f;
        } else {
            pOut->mSpeed = 0.72f;
        }
        pMate = PlyrGet(fn_80178320(), fn_8012078C()->mpUnknown4[0]);
        if (p->mMotion.mPos.mY > pMate->mMotion.mPos.mY && MathAngleDiff(pOut->mHeading, 0x400000) <= 0x3FFFFF) {
            target.mX = pCarrierMotion->mPos.mX;
            target.mX = CLAMP(target.mX, 2.0f - fn_80178A08(), fn_80178A08() - 2.0f);
            target.mY = pMate->mMotion.mPos.mY;
            fn_80227690(&target, &target, &p->mMotion.mPos);
            pOut->mHeading = target.Heading();
        }
        fn_8010E15C(p, pOut);
        pOut->mHeading &= 0xFFFFFF;
        if (open && ahead && pOut->mHeading > 0x800000 && pMotion->mPos.mY > pCarrierMotion->mPos.mY) {
            pOut->mFacing = 0x400000;
        } else {
            pOut->mFacing = pOut->mHeading;
        }
    } else {
        if (fn_801787A0()) {
            pOut->mHeading = pMotion->mFacing;
            pOut->mSpeed = pMotion->mUnknown28 / gPlyrMoveFwdSpeed;
        } else {
            pOut->mSpeed = 0.72f;
            if (!BallGetLandingPoint(pBall, &ballPos)) {
                BallGetPosition(pBall, &ballPos);
                vel.mX = vel.mY = vel.mZ = 0.0f;
            } else {
                BallGetVelocity(pBall, &vel);
                if (BallStateGet(pBall, 0) == 4) pOut->mSpeed = 0.4f;
            }
            if (open && vel.mZ < 0.0f) {
                ballPos.mX = (ballPos.mX + pMotion->mPos.mX) * 0.5f;
                ballPos.mY += 8.0f;
            } else if (BallStateGet(pBall, 0) == 4) {
                ballPos.mX = (ballPos.mX + pMotion->mPos.mX) * 0.5f;
                ballPos.mY += 4.0f;
            } else {
                fn_80227690(&target, &pMotion->mPos, &ballPos);
                fn_80227538(&target, target.Heading(), 5.0f);
                ballPos.mX += target.mX;
                ballPos.mY += target.mY;
            }
            fn_80227690(&target, &ballPos, &pMotion->mPos);
            pOut->mHeading = target.Heading();
            if (!fn_8011F1A4() && fn_802270A4(&target) < 1.0f) pOut->mSpeed = 0.0f;
        }
        fn_8010E15C(p, pOut);
        pOut->mFacing = pOut->mHeading;
    }
}

/* Steers the player around the nearest other player ahead of its heading. */
extern "C" void fn_8010E15C(Object_80039F5C *p, Steer_8010DAB4 *pOut) {
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_80039F5C *pMark = fn_8009BCE8(&p->mUnknown1036);
    Vector_80039F5C aim;
    Point_8017886C toward;
    Object_80039F5C *pOther;
    Object_80039F5C *pPartner;
    float distance;
    float limit;
    float scale;
    int second = 0;
    int first = 0;
    int turn = 0;
    int pair;
    int between;
    int heading;
    int off;

    aim.mX = aim.mY = aim.mZ = 0.0f;
    pOther = fn_80124C28(p, &distance, 0x38E38E, 3.0f, 0.5f, pOut->mHeading);
    if (pOther && distance < 3.0f && pOther != pMark && pOther != BallGetCurrentHolder()) {
        limit = 3.0f;
        between = 0;
        pair = InRange(pOther->mUnknown1032, 4, 7);
        if (pOther->mIdBytes[2] == p->mIdBytes[2] && !pair) limit *= 0.5f;
        /* The distance is computed and dropped (0x8010E254). */
        if (pMark) fn_8022781C(&pMark->mMotion.mPos, &pMotion->mPos);
        if (distance < limit) {
            if (pair) {
                pPartner = fn_8009BCE8(&pOther->mUnknown1036);
                aim.mX = (pOther->mMotion.mPos.mX + pPartner->mMotion.mPos.mX) * 0.5f;
                aim.mY = (pOther->mMotion.mPos.mY + pPartner->mMotion.mPos.mY) * 0.5f;
                fn_80227690(&toward, &pOther->mMotion.mPos, &pMotion->mPos);
                first = toward.Heading();
                fn_80227690(&toward, &pPartner->mMotion.mPos, &pMotion->mPos);
                second = toward.Heading();
                if ((((first - second) & 0xFFFFFF) <= 0x7FFFFF && ((pOut->mHeading - second) & 0xFFFFFF) <= 0x7FFFFF) ||
                    (((first - second) & 0xFFFFFF) > 0x800000 && ((pOut->mHeading - second) & 0xFFFFFF) > 0x800000)) {
                    if (MathAngleDiff(first - second, 0) > MathAngleDiff(pOut->mHeading - second, 0)) between = 1;
                }
            } else {
                aim.mX = pOther->mMotion.mPos.mX;
                aim.mY = pOther->mMotion.mPos.mY;
                aim.mZ = pOther->mMotion.mPos.mZ;
                aim.mX = pOther->mMotion.mUnknown40 * 10.0f + aim.mX;
                aim.mY = pOther->mMotion.mUnknown44 * 10.0f + aim.mY;
            }
            fn_80227690(&toward, &aim, &pMotion->mPos);
            heading = toward.Heading();
            scale = distance * 0.4f;
            if (scale > 1.0f) scale = 1.0f;
            if (MathAngleDiff(heading, pOut->mHeading) <= 0x271C70) {
                if (((heading - pOut->mHeading) & 0xFFFFFF) > 0x800000) {
                    turn = (int)((1.0f - scale) * 3728270.0f);
                    if (pair && between) {
                        if (((first - heading) & 0xFFFFFF) <= 0x7FFFFF) {
                            turn += MathAngleDiff(first, pOut->mHeading);
                        } else {
                            turn += MathAngleDiff(second, pOut->mHeading);
                        }
                    }
                } else {
                    turn = (int)-((1.0f - scale) * 3728270.0f);
                    if (pair && between) {
                        if (((first - heading) & 0xFFFFFF) > 0x800000) {
                            turn -= MathAngleDiff(first, pOut->mHeading);
                        } else {
                            turn -= MathAngleDiff(second, pOut->mHeading);
                        }
                    }
                }
                off = MathAngleDiff(pOut->mHeading + turn, pMotion->mFacing);
                if (off > 0x11C71C) {
                    pOut->mSpeed = fn_801CFB94(off / 2) * 0.72f;
                    pOut->mUnknown22 = 0;
                } else if (distance < 2.1f && MathAngleDiff(heading, pMotion->mFacing) <= 0x1FFFFF) {
                    pOut->mUnknown22 = 0;
                }
            }
            pOut->mHeading = (pOut->mHeading + turn) & 0xFFFFFF;
        }
    }
}

/* Updates the player's steering toward pTarget, or along the play when
   there is none, once its countdown runs out. */
extern "C" void fn_8010E59C(Object_80039F5C *p, Object_80039F5C *pTarget, Steer_8010DAB4 *pOut) {
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_80039F5C *pCarrier;
    Point_8017886C aim;
    Point_8017886C toward;
    float distance;
    float limit;
    int heading;
    int side;
    int off;
    int state;
    int rating;

    if (--pOut->mTimer < 0 || fn_801787A0()) {
        if (!fn_80178C9C() || (fn_800BA6F8() && fn_800BAA24() == 1)) {
            pOut->mUnknown21 = 1;
        } else {
            rating = p->mRatings[7] * 2;
            pOut->mTimer = rating / 2;
            pOut->mTimer = (255 - pOut->mTimer) / 32 + 2;
            if (pTarget) {
                /* The point is fetched and dropped (0x8010E65C). */
                fn_80177FE0();
                aim.mX = pTarget->mMotion.mUnknown40 * 10.0f + pTarget->mMotion.mPos.mX;
                aim.mY = pTarget->mMotion.mUnknown44 * 10.0f + pTarget->mMotion.mPos.mY;
                if (fn_801BE648(pTarget->mpUnknown792) == 0x56) aim.mY -= 0.75f;
                fn_80227690(&toward, &aim, pMotion);
                heading = toward.Heading();
                distance = fn_802270A4(&toward);
                if (distance < 2.5f) pOut->mTimer = 0;
                limit = 6.0f;
                pOut->mUnknown22 = 1;
                pOut->mSpeed = 1.0f;
                pOut->mHeading = heading;
                if (pTarget->mMotion.mUnknown28 != 0.0f &&
                    (fn_801BE648(pTarget->mpUnknown792) == 0x4A || fn_801BE648(pTarget->mpUnknown792) == 0x49 ||
                     fn_801BE648(pTarget->mpUnknown792) == 0xA0)) {
                    if (MathAngleDiff(heading, pTarget->mMotion.mUnknown32) > 0x6E38E3) {
                        if (distance < limit) pOut->mSpeed = distance / limit * 0.86f + 0.14f;
                    } else if (distance > 1.75f) {
                        if (fn_801BE648(pTarget->mpUnknown792) == 0xA0 && pTarget->mpState->mId != 2) {
                            pOut->mHeading = heading;
                        } else {
                            pOut->mHeading = fn_80120794((Vector_80039F5C *)pMotion, (Vector_80039F5C *)&pTarget->mMotion,
                                                         (Vector_80039F5C *)&pTarget->mMotion.mUnknown40,
                                                         pMotion->mUnknown28, pTarget->mMotion.mUnknown28,
                                                         pTarget->mMotion.mUnknown32, distance);
                        }
                        if (distance < 2.5f && fn_8011E188() <= 44) {
                            switch (p->mUnknown2914) {
                            case 4:
                            case 5:
                            case 6:
                            case 7:
                            case 8:
                            case 9:
                            case 24:
                                off = MathAngleDiff(heading, pOut->mHeading);
                                if (((heading - pOut->mHeading) & 0xFFFFFF) > 0x800000) {
                                    pOut->mHeading = pOut->mHeading - off / 2;
                                } else {
                                    pOut->mHeading = pOut->mHeading + off / 2;
                                }
                                break;
                            }
                        }
                        if (distance < limit) pOut->mSpeed = distance / limit * (1.0f - 0.72f) + 0.72f;
                        if (fn_8011E188() <= 59 && distance > 2.0f && fn_8011F1A4() && fn_8011F4C8() > 3 && !fn_801783AC(0) &&
                            MathAngleDiff(pMotion->mFacing, 0x400000) <= 0x3FFFFF) {
                            toward.mX = fn_8011F4D4();
                            toward.mY = fn_80177FE0().mY;
                            if (fabsf(toward.mX) > fabsf(pMotion->mPos.mX) && aim.mY - toward.mY > 3.0f &&
                                pMotion->mPos.mY - toward.mY < 1.5f) {
                                fn_80227690(&toward, &toward, pMotion);
                                side = toward.Heading();
                                off = MathAngleDiff(heading, side);
                                if (off <= 0x671C71 && off > MathAngleDiff(heading, pOut->mHeading)) {
                                    off = MAX(off, 0x18E38E);
                                    if (MathAngleDiff(side, heading) < MathAngleDiff(side, pOut->mHeading)) pOut->mHeading = heading;
                                    if (((side - heading) & 0xFFFFFF) > 0x800000) {
                                        pOut->mHeading -= off / 2;
                                    } else {
                                        pOut->mHeading += off / 2;
                                    }
                                }
                            }
                        }
                    } else {
                        if (pTarget == fn_8009BCE8(&p->mUnknown560.mUnknown40)) {
                            pOut->mSpeed = distance * 0.18285717f + 0.4f;
                        } else {
                            pOut->mSpeed = distance * 0.16f + 0.72f;
                        }
                        pOut->mUnknown22 = 0;
                    }
                    pCarrier = BallGetCurrentHolder();
                    if (pCarrier) {
                        state = pCarrier->mpState->mId;
                        if (state == 1 || state == 0x23 || state == 0x22 || state == 0x24) {
                            fn_80227690(&toward, &pCarrier->mMotion.mPos, pMotion);
                            distance = fn_802270A4(&toward);
                            if (distance < 10.0f) {
                                side = toward.Heading() & 0xFFFFFF;
                                if (distance < 5.0f && MathAngleDiff(heading, side) > 0x58E38E &&
                                    MathAngleDiff(pCarrier->mMotion.mFacing, side) > 0x755555) {
                                    off = MathAngleDiff(heading, pOut->mHeading);
                                    if (((pOut->mHeading - heading) & 0xFFFFFF) > 0x800000) {
                                        pOut->mHeading = (pOut->mHeading + off / 2) & 0xFFFFFF;
                                    } else {
                                        pOut->mHeading = (pOut->mHeading - off / 2) & 0xFFFFFF;
                                    }
                                } else if (MathAngleDiff(heading, side) <= 0x355554) {
                                    if (((pOut->mHeading - heading) & 0xFFFFFF) > 0x800000) {
                                        if (((side - heading) & 0xFFFFFF) > 0x800000 &&
                                            MathAngleDiff(pOut->mHeading, heading) > MathAngleDiff(side, heading)) {
                                            pOut->mHeading = heading;
                                            pOut->mHeading = (pOut->mHeading - MathAngleDiff(side, heading) / 2) & 0xFFFFFF;
                                        }
                                    } else if (((side - heading) & 0xFFFFFF) <= 0x7FFFFF &&
                                               MathAngleDiff(pOut->mHeading, heading) > MathAngleDiff(side, heading)) {
                                        pOut->mHeading = heading;
                                        pOut->mHeading = (pOut->mHeading + MathAngleDiff(side, heading) / 2) & 0xFFFFFF;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    pOut->mUnknown22 = 0;
                    if (distance < 1.75f) pOut->mSpeed = distance * 0.34285718f + 0.4f;
                    if (fn_8011F1A4() && fn_8011F4C8() > 3 && fn_8011E188() <= 59) {
                        toward.mX = fn_8011F4D4();
                        if (fabsf(pMotion->mPos.mX) < fabsf(toward.mX) && fabsf(pMotion->mPos.mX - toward.mX) < 3.0f) {
                            toward.mY = fn_80177FE0().mY;
                            fn_80227690(&toward, &toward, pMotion);
                            side = toward.Heading();
                            off = MathAngleDiff(heading, side);
                            if (off <= 0x3FFFFF) {
                                if (((pOut->mHeading - side) & 0xFFFFFF) <= 0x7FFFFF) {
                                    pOut->mHeading = pOut->mHeading - off / 2;
                                } else {
                                    pOut->mHeading = pOut->mHeading + off / 2;
                                }
                            }
                        }
                    }
                }
                fn_8010E15C(p, pOut);
                pOut->mHeading &= 0xFFFFFF;
                pOut->mFacing = pOut->mHeading;
                off = MathAngleDiff(pOut->mHeading, pMotion->mFacing);
                if (off > 0x18E38E) {
                    off /= 2;
                    pOut->mSpeed = MIN(pOut->mSpeed, fn_801CFB94(off) * 0.72f);
                    pOut->mUnknown22 = 0;
                }
            } else {
                fn_8010DAB4(p, pOut);
                heading = pMotion->mFacing;
            }
            if (pMotion->mUnknown28 > gPlyrMoveFwdSpeed * 0.05f && MathAngleDiff(pMotion->mUnknown32, pMotion->mFacing) > 0x400000 &&
                MathAngleDiff(pMotion->mUnknown32, pOut->mFacing) > 0x38E38E) {
                pOut->mFacing = heading;
                pOut->mSpeed = 0.0f;
                pOut->mTimer = 0;
            }
        }
    }
    if (fn_801787A0()) pOut->mSpeed = MIN(pOut->mSpeed, 0.4f);
}

extern "C" void fn_8010EF40(Object_80039F5C *p)
{
    int found = 0;
    Block_80170374 *pBlock = &p->mUnknown560;
    Object_80039F5C *pCarrier;
    Object_80039F5C *pOther;
    Point_8017886C delta;

    if (pBlock->mFlags.mBytes[0] == 1) {
        pCarrier = BallGetCurrentHolder();
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
                    if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), pOther->mMotion.mUnknown32) <= 0x3FFFFF) {
                        fn_800E96EC(p, pOther);
                    }
                }
                break;
            }
        }
    }
}

extern "C" void fn_8010F058(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Point_8017886C delta;
    int angle;
    float distance;
    float scale;
    int a;
    Object_800B26B0 *pMotion;

    if (p->mUnknown1032 == 4 || p->mUnknown1032 == 7 || pOther == 0) {
        return;
    }
    pMotion = &p->mMotion;
    fn_80227690(&delta, &pOther->mMotion.mPos, &pMotion->mPos);
    angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
    distance = fn_802270A4(&delta);
    if (MathAngleDiff(angle, pMotion->mFacing) > 0x4E38E2) {
        return;
    }
    scale = 0.0f;
    a = 0;
    if (pMotion->mPos.mY < pOther->mMotion.mPos.mY) {
        if (distance < 3.0f) {
            distance -= 1.0f;
            if (distance < 0.0f) {
                distance = 0.0f;
            }
            scale = 1.0f - distance * 0.33333334f;
        } else if (distance < 10.0f) {
            a = 1;
            distance -= 1.0f;
            if (distance < 0.0f) {
                distance = 0.0f;
            }
            scale = 1.0f - distance * 0.1f;
        }
    } else if (distance < 4.0f) {
        distance -= 1.0f;
        if (distance < 0.0f) {
            distance = 0.0f;
        }
        scale = 1.0f - distance * 0.25f;
    }
    if (scale != 0.0f) {
        fn_800C89F0(p, angle, 2, a, scale);
    }
}

extern "C" void fn_8010F1F4(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Point_8017886C delta;
    Object_80039F5C *pTarget;
    Object_80039F5C *pBlocker;
    int angle;

    if (pOther == 0 || p->mUnknown560.mFlags.mBytes[0] == 0) {
        return;
    }
    pTarget = fn_8009BCE8(&p->mUnknown560.mUnknown40);
    if (pTarget == 0) {
        pTarget = fn_8009BCE8(&p->mUnknown560.mUnknown44);
        if (pTarget == 0) {
            return;
        }
        pTarget = fn_8009BCE8(&pTarget->mUnknown1036);
        if (pTarget == 0) {
            return;
        }
    }
    if (pOther == pTarget || !fn_8011F1A4() || fn_8011F4C8() > 3 || fn_801783AC(0)) {
        return;
    }
    fn_80227690(&delta, &pTarget->mMotion.mPos, &p->mMotion.mPos);
    angle = fn_801CFE40(delta.mY, delta.mX);
    if (MathAngleDiff(angle, p->mMotion.mFacing) > 0x2AAAA9) {
        return;
    }
    delta.mX = pOther->mMotion.mPos.mX + pOther->mMotion.mUnknown40 * 5.0f;
    delta.mY = pOther->mMotion.mPos.mY + pOther->mMotion.mUnknown44 * 5.0f;
    fn_80227690(&delta, &delta, &p->mMotion.mPos);
    if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), angle) > 0x18E38D) {
        return;
    }
    pBlocker = fn_8009BCE8(&pTarget->mUnknown1036);
    if (pBlocker == 0) {
        return;
    }
    fn_80227690(&delta, &pTarget->mMotion.mPos, &pBlocker->mMotion.mPos);
    angle = fn_801CFE40(delta.mY, delta.mX);
    delta.mX = pOther->mMotion.mPos.mX + pOther->mMotion.mUnknown40 * 5.0f;
    delta.mY = pOther->mMotion.mPos.mY + pOther->mMotion.mUnknown44 * 5.0f;
    fn_80227690(&delta, &delta, &pBlocker->mMotion.mPos);
    if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), angle) <= 0x18E38E) {
        return;
    }
    switch (pBlocker->mUnknown1032) {
    case 2:
    case 4:
    case 7:
    case 8:
        fn_8011E240(pBlocker);
        fn_8011E1BC(pBlocker, 0, 0, 1);
        fn_8011E3EC(pBlocker, 2);
        fn_8011E240(p);
        fn_8011E1BC(p, 0, 0, 1);
        fn_8011E3EC(p, 2);
        break;
    }
}

extern "C" int fn_8010F43C(Object_80039F5C *p)
{
    State_8010F43C *pState = (State_8010F43C *)&p->mUnknown336;
    int time = p->mpState->mUnknown1;
    float fraction = (time & 0x1F) / 31.0f;

    pState->mUnknown16 = (time >> 5) * 60 + (int)(fraction * 60.0f);
    if (pState->mUnknown16 == 0) {
        pState->mUnknown20 = 0;
    } else {
        pState->mUnknown20 = 1;
    }
    pState->mUnknown21 = 0;
    fn_8010A2DC(p, 0, 0);
    if (!(p->mFlags & 0x4000)) {
        if (!fn_80178C9C() || (fn_800BA6F8() && fn_800BAA24() == 1)) {
            pState->mUnknown12 = fn_802372EC(0, 45) + 45;
        } else {
            pState->mUnknown12 = 0;
        }
        pState->mUnknown8 = p->mMotion.mFacing;
        pState->mUnknown0 = 0.4f;
        pState->mUnknown4 = p->mMotion.mFacing;
        pState->mUnknown21 = 0;
        pState->mUnknown22 = 0;
        if (fn_801787A0()) {
            pState->mUnknown12 = 99999;
        }
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = pState->mUnknown4;
        p->mUnknown512.mUnknown8 = pState->mUnknown8;
        p->mUnknown512.mUnknown0 = pState->mUnknown0;
    } else {
        pState->mUnknown0 = p->mUnknown528.mUnknown0;
        pState->mUnknown4 = p->mMotion.mFacing;
        pState->mUnknown8 = p->mMotion.mFacing;
        pState->mUnknown12 = 0;
        pState->mUnknown21 = 0;
        pState->mUnknown22 = p->mUnknown528.mUnknown15;
        p->mUnknown512.mUnknown0 = p->mUnknown528.mUnknown0;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown14 = 1;
    }
    if (p->mUnknown1052 != 2 ||
        (p->mUnknown1032 != 4 && p->mUnknown1032 != 7 && p->mUnknown1032 != 2 && p->mUnknown1032 != 3)) {
        fn_8011E1BC(p, 0, 0, 1);
        fn_8011E3EC(p, 2);
    }
    return 0;
}

extern "C" int fn_8010F654(Object_80039F5C *p)
{
    int result = 0;
    Ball_t *pBall = BallGetCurrent();
    State_8010F43C *pState = (State_8010F43C *)&p->mUnknown336;
    Block_8011E240 *pBlock = &p->mBlock1032;
    Object_80039F5C *pCarrier = BallGetCurrentHolder();
    Object_80039F5C *pOther;
    Message_800F01CC message;
    Vector_80039F5C ballPos;
    float minutes;

    if (p == BallGetCurrentHolder()) {
        fn_8011E3EC(p, 0);
        result = 1;
        fn_8011E240(p);
        memset(&message, 0, 4);
        message.mId = 1;
        fn_800F053C(0, p->mpState, &message, p);
    } else if (fn_8010D8F4(p)) {
        memset(&message, 0, 4);
        message.mId = 90;
        message.mUnknown1[0] = pCarrier->mMotion.mPos.mX > 0.0f ? lbl_803EAF50 : -lbl_803EAF50;
        message.mUnknown1[1] = lbl_803EAF51;
        result = 1;
        fn_800F053C(0, p->mpState, &message, p);
    } else if (fn_8009FB60(p)) {
        result = 1;
    } else {
        if (BallStateGet(pBall, 0) == 5 && fn_800AD9B4() == 3) {
            BallGetPosition(BallGetCurrent(), &ballPos);
            if (fn_8022785C(&ballPos, &p->mMotion.mPos) < 3.0f) {
                memset(&message, 0, 4);
                message.mId = 57;
                message.mUnknown1[0] = BallGetCurrentIndex();
                fn_800F053C(0, p->mpState, &message, p);
                return result;
            }
        }
        if (!fn_801783AC(13) && !fn_801783AC(0) && fn_8011F1CC() && !fn_801787A0() &&
            (pState->mUnknown20 == 0 || pState->mUnknown16 <= 0)) {
            fn_8011E3EC(p, 0);
            result = 0;
            fn_8011E240(p);
            memset(&message, 0, 4);
            message.mId = 31;
            fn_800F053C(0, p->mpState, &message, p);
        } else {
            fn_8010A2DC(p, 0, -1);
            if (fn_801787A0()) {
                if ((pBlock->mUnknown0 != 4 && pBlock->mUnknown0 != 7) || fn_802372EC(0, 100) <= 9) {
                    fn_8011E3EC(p, 0);
                    fn_8011E240(p);
                    pState->mUnknown21 = 1;
                }
            } else if (pBlock->mUnknown0 == 0) {
                fn_8011E240(p);
                fn_8011E1BC(p, 0, 0, 1);
                fn_8011E3EC(p, 2);
            }
            if (!(p->mFlags & 0x4000)) {
                if (p->mIdBytes[2] == fn_80178320()) {
                    if (fn_801783AC(0)) {
                        fn_8011E3EC(p, 0);
                        result = 1;
                        fn_8011E240(p);
                        memset(&message, 0, 4);
                        message.mId = 2;
                        fn_800F053C(0, p->mpState, &message, p);
                    } else {
                        pState->mUnknown4 = 0x400000;
                        pState->mUnknown8 = 0x400000;
                    }
                } else {
                    pOther = fn_8009BCE8(&pBlock->mUnknown4);
                    if (pBlock->mUnknown0 != 4 && pBlock->mUnknown0 != 7) {
                        fn_8010E59C(p, pOther, (Steer_8010DAB4 *)pState);
                        fn_8010F058(p, pOther);
                        fn_8010F1F4(p, pOther);
                    } else {
                        pState->mUnknown12 = 0;
                    }
                }
                if (pState->mUnknown21) {
                    p->mUnknown512.mUnknown14 = 10;
                    p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
                    p->mUnknown512.mUnknown0 = 0.5f;
                } else {
                    p->mUnknown512.mUnknown14 = 3;
                    p->mUnknown512.mUnknown4 = pState->mUnknown4 & 0xFFFFFF;
                    p->mUnknown512.mUnknown8 = pState->mUnknown8;
                    p->mUnknown512.mUnknown0 = pState->mUnknown0;
                    p->mUnknown512.mUnknown15 = pState->mUnknown22;
                }
                if (pState->mUnknown20) {
                    pState->mUnknown16--;
                    minutes = pState->mUnknown16 / 60.0f;
                    p->mpState->mUnknown1 = (int)(minutes * 32.0f);
                    if (pState->mUnknown16 > 0 && p->mpState->mUnknown1 == 0) {
                        p->mpState->mUnknown1 = 1;
                    }
                    if (pState->mUnknown16 <= 0) {
                        fn_8011E3EC(p, 0);
                        result = 1;
                        fn_8011E240(p);
                    }
                }
                fn_8010EF40(p);
            }
        }
    }
    return result;
}

extern "C" int fn_8010FB10(Object_80039F5C *p)
{
    fn_8011E3EC(p, 0);
    fn_8011E240(p);
    return 1;
}

extern "C" int fn_8010FB4C(Object_80039F5C *p)
{
    int result = 0;
    Input_800B6D34 input;
    Point_8017886C delta;
    Block_8010FB4C *pBlock;

    if (fn_8011E8A4(p)) {
        result = fn_800B7E60(p);
    } else {
        pBlock = (Block_8010FB4C *)&p->mUnknown1032;
        if (pBlock->mUnknown0 == 4 || pBlock->mUnknown0 == 7) {
            fn_800B6D34(p, &input);
            fn_800B6E68(p, &input);
            fn_80227690(&delta, &fn_8009BCE8(&p->mUnknown1036)->mMotion.mPos, &p->mMotion.mPos);
            if (MathAngleDiff(p->mUnknown512.mUnknown4, fn_801CFE40(delta.mY, delta.mX)) > 0x600000) {
                fn_8011E3EC(p, 0);
                fn_8011E240(p);
            } else {
                if (input.mUnknown92 & 1) {
                    pBlock->mUnknown105 = 1;
                }
                result = fn_800B7F34(p);
            }
        } else {
            result = fn_800B7F34(p);
        }
    }
    return result;
}

extern "C" int fn_8010FC40(Object_80039F5C *p)
{
    int mode = fn_800AD9B4();
    int restart = 1;
    unsigned char key;
    Object_80039F5C *pOther;

    if ((p->mFlags & 0x4000) && mode != 4) {
        return 1;
    }
    key = p->mpState->mUnknown1;
    if (p->mpState->mUnknown2 == 0 && key == fn_801BE648(p->mpUnknown792)) {
        restart = 0;
    }
    if (restart == 1) {
        p->mFlags &= ~4;
        p->mUnknown9[0] = 1;
        p->mUnknown512.mUnknown14 = 0;
        fn_8009BD60(p);
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, key, 1.0f, p);
        if (!(p->mpState->mUnknown3[0] & 0x80)) {
            p->mFlags |= 1 << (p->mpState->mUnknown3[0] & 0x7F);
        }
    } else {
        p->mFlags |= 1 << (p->mpState->mUnknown3[0] & ~0x80);
    }
    if (p->mIdBytes[2] == fn_80178308() && p->mUnknown2914 == 7) {
        pOther = PlaySetGetKeyPlayer(PlayBookGetFormation(fn_80178308()));
        PlyrCollideAddExempt(p, pOther);
        PlyrCollideAddExempt(pOther, p);
    }
    return 0;
}

extern "C" int fn_8010FD8C() {
    return 1;
}

extern "C" int fn_8010FD94(Object_80039F5C *p)
{
    int mode = fn_800AD9B4();
    Timer_8010FD94 *pTimer = (Timer_8010FD94 *)&p->mUnknown336;
    Object_80039F5C *pOther;

    if ((p->mFlags & 0x4000) && mode != 4) {
        return 1;
    }
    pTimer->mUnknown0 = 0;
    pTimer->mUnknown4 = 0.0f;
    pTimer->mUnknown8 = 0;
    if (p->mIdBytes[2] == fn_80178308() && p->mUnknown2914 == 7) {
        pOther = PlaySetGetKeyPlayer(PlayBookGetFormation(fn_80178308()));
        PlyrCollideAddExempt(p, pOther);
        PlyrCollideAddExempt(pOther, p);
    }
    return 0;
}

extern "C" int fn_8010FE40(Object_80039F5C *p)
{
    unsigned short key;
    Timer_8010FD94 *pTimer = (Timer_8010FD94 *)&p->mUnknown336;
    int target;
    AnimChannel_t *pEntries;
    int index;

    if ((p->mFlags & 0x4000) && pTimer->mUnknown8 != 0) {
        return 1;
    }
    if (pTimer->mUnknown8 != 0) {
        pTimer->mUnknown4 -= 1.0f;
        if (pTimer->mUnknown4 <= 0.0f) {
            return 1;
        }
        p->mMotion.mFacing += pTimer->mUnknown0;
        p->mpUnknown796->mUnknown8 += pTimer->mUnknown0;
    } else {
        pTimer->mUnknown8 = 1;
        p->mUnknown512.mUnknown14 = 0;
        p->mUnknown9[0] = 1;
        p->mFlags &= ~4;
        if (BallFindHeldBy(p) == 0) {
            fn_8009BD60(p);
            key = p->mpState->mUnknown1;
            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, key, 1.0f, p);
            target = p->mpState->mUnknown2 << 16;
            if (MathAngleDiff(target, p->mMotion.mFacing) > 0xB60B && AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, key)) {
                pEntries = p->mpUnknown800;
                index = AnimChanGetStateChannelByIndex(p->mpUnknown796, pEntries, key, 0);
                pTimer->mUnknown4 = pEntries[index].mUnknown48;
                if (pTimer->mUnknown4 == 0.0f) {
                    pTimer->mUnknown4 = AnimSeqGetTimeToOpcode(&pEntries[index].mUnknown4C, 0xC004);
                }
                if (pTimer->mUnknown4 != 0.0f) {
                    pTimer->mUnknown4 = pTimer->mUnknown4 > 75.0f ? 75.0f : pTimer->mUnknown4;
                    pTimer->mUnknown0 = (int)(MathAngleDiff(target, p->mMotion.mFacing) / pTimer->mUnknown4);
                    if (((p->mMotion.mFacing - target) & 0xFFFFFF) <= 0x7FFFFF) {
                        pTimer->mUnknown0 = -pTimer->mUnknown0;
                    }
                }
            }
        }
    }
    return 0;
}

extern "C" int fn_80110078(Object_80039F5C *p)
{
    Input_800B6D34 input;

    fn_800B6D34(p, &input);
    return 0;
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

extern "C" void fn_801100E8(Object_80039F5C *p)
{
    unsigned char side;

    fn_800A8954(1, p->mIdBytes[2], p);
    fn_8009BD60(p);
    switch (p->mpState->mUnknown2) {
    case 1:
    default:
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
    p->mUnknown1008.mUnknown0 = 4;
    p->mUnknown1008.mUnknown1 = side;
    if (PlayerMoveGetKind(p)) {
        p->mUnknown1008.mUnknown2 = 1;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 188, 1.0f, p);
        TutorialSetMoveDone(8, 1);
    } else {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 154, 1.0f, p);
    }
}

extern "C" int fn_801101DC(Object_80039F5C *p)
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
        case 25:
        case 26:
        case 27:
        case 34:
            result = 0;
            break;
        default:
            result = 1;
            break;
        }
        if (p != BallGetCurrentHolder()) {
            result = 0;
        }
        switch (p->mUnknown528.mUnknown15) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 10:
        case 11:
        case 20:
        case 21:
            result = 1;
            break;
        default:
            result = 0;
            break;
        }
    }
    return result;
}

extern "C" int fn_801102A4(Object_80039F5C *p)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    float range;
    Object_80039F5C *pOther = fn_801245DC(p, fn_80178320(), 0, fn_80178D18(fn_80178320()), 0x2E38E3, &range, 1);
    float margin = fn_80178A08() - fabsf(p->mMotion.mPos.mX);
    int result;

    if (pOther != 0 && margin > 3.0f) {
        Point_8017886C ahead;
        float distance;

        ahead.mX = pOther->mMotion.mPos.mX;
        ahead.mY = pOther->mMotion.mPos.mY;
        fn_8022732C(&ahead, &pOther->mMotion.mUnknown40, 15.0f / gFrameTimeScale);
        fn_80227690(&ahead, &ahead, &pMotion->mPos);
        distance = fn_802270A4(&ahead);
        if (!(pOther->mFlags & 0x800)) {
            if (distance < pOther->mMotion.mUnknown28 * (45.0f / gFrameTimeScale)) {
                Point_8017886C delta;
                int heading = fn_801CFE40(pOther->mMotion.mUnknown44, pOther->mMotion.mUnknown40);

                fn_80227690(&delta, &pMotion->mPos, &pOther->mMotion.mPos);
                if (((heading - fn_801CFE40(delta.mY, delta.mX)) & 0xFFFFFF) > 0x800000) {
                    result = 2;
                } else {
                    result = 1;
                }
            } else if (pMotion->mUnknown32 < 0x400000 || pMotion->mUnknown32 > 0xC00000) {
                result = 1;
            } else {
                result = 2;
            }
        } else {
            fn_80227690(&ahead, &pOther->mMotion.mPos, &pMotion->mPos);
            if (((pMotion->mUnknown32 - fn_801CFE40(ahead.mY, ahead.mX)) & 0xFFFFFF) > 0x800000) {
                result = 2;
            } else {
                result = 1;
            }
        }
    } else if (margin < 3.0f) {
        if (pMotion->mPos.mX > 0.0f) {
            if (pMotion->mUnknown32 <= 0x7FFFFF) {
                result = 1;
            } else {
                result = 2;
            }
        } else if (pMotion->mUnknown32 <= 0x7FFFFF) {
            result = 2;
        } else {
            result = 1;
        }
    } else if (pMotion->mUnknown32 < 0x400000 || pMotion->mUnknown32 > 0xC00000) {
        result = 1;
    } else {
        result = 2;
    }
    return result;
}

extern "C" void fn_801104BC(Object_80039F5C *p, Block_8011067C *pBlock)
{
    pBlock->mUnknown8 = -1;
    pBlock->mUnknown12 = 1.0f;
    pBlock->mUnknown16 = 1.0f;
    pBlock->mUnknown24 = 0;
    pBlock->mUnknown28 = 0;
}

extern "C" void fn_801104E4(Object_80039F5C *p, Block_8011067C *pBlock)
{
    float scale = 0.4f;
    short rating;

    if (fn_800CA5CC(p, 1, 1)) {
        scale *= fn_800CA9B4(3, p);
        fn_800CA9B4(2, p);
    }
    pBlock->mUnknown16 = 1.0f;
    pBlock->mUnknown20 = 1.0f;
    if (p->mRatings[0] > 127) {
        float bonus;
        float step;

        rating = p->mRatings[0] - 127;
        bonus = rating;
        step = scale / 128.0f;
        pBlock->mUnknown16 = 1.0f + bonus * step;
    }
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

extern "C" unsigned short fn_8011067C(Table_8010B738 *pTable, Object_80039F5C *p, Block_8011067C *pBlock, int angle)
{
    unsigned int index = 0;
    Record_8010B738 *pFound = 0;
    Record_8010B738 *pRecord;
    unsigned int i;
    int target;
    int delta;

    for (i = 0; i < pTable->mCount; i++) {
        pRecord = pTable->mEntries[i].mpRecord;
        if (fn_80110630(&pRecord->mUnknown4, &p->mUnknown1008) && angle >= pRecord->mUnknown16 &&
            angle <= pRecord->mUnknown20) {
            if (pFound == 0 || fn_802372EC(0, 100) <= 49) {
                pFound = pRecord;
                index = i;
            }
        }
    }
    if (pFound != 0 && index < pTable->mCount) {
        target = pFound->mUnknown12 & 0xFFFFFF;
        if (p->mUnknown1008.mUnknown1 == 6) {
            target = 0x1000000 - target;
        }
        delta = MathAngleDiff(target, angle);
        pBlock->mUnknown24 = delta;
        if (p->mUnknown1008.mUnknown1 == 6) {
            if (((target - angle) & 0xFFFFFF) > 0x800000) {
                pBlock->mUnknown24 = -delta;
            }
        } else if (((target - angle) & 0xFFFFFF) <= 0x7FFFFF) {
            pBlock->mUnknown24 = -delta;
        }
        if (p->mUnknown776 == 1) {
            pBlock->mUnknown24 = -pBlock->mUnknown24;
        }
        pBlock->mUnknown12 = pFound->mUnknown24 / pBlock->mUnknown16;
        if (PlayerMoveGetKind(p)) {
            pRecord = pTable->mEntries[index].mpRecord;
            PlayerMoveSetResult(p, pRecord->mUnknown7);
        } else {
            PlayerMoveSetResult(p, 0);
        }
    } else {
        index = 0;
    }
    return index;
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
        PlayerMoveBegin(p, c, 35);
        memset(&message, 0, 4);
        message.mId = 35;
        message.mUnknown1[0] = a;
        message.mUnknown1[1] = b;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int fn_801108D4(Object_80039F5C *p)
{
    State_801108D4 *pState = (State_801108D4 *)&p->mUnknown336;
    unsigned char kind = p->mpState->mUnknown1;
    Input_800B6D34 input;
    short value;

    if (kind == 0) {
        fn_800B6D34(p, &input);
        pState->mUnknown12 = kind;
        pState->mUnknown4 = 8;
        pState->mUnknown0 = 0.0f;
        pState->mUnknown13 = input.mUnknown72[0] != 0.0f;
    } else {
        pState->mUnknown12 = 1;
        pState->mUnknown4 = -1;
    }
    pState->mUnknown14 = 0;
    pState->mUnknown8 = p->mRatings[2];
    value = pState->mUnknown8 + 15;
    p->mRatings[2] = value > 255 ? 255 : value;
    p->mFlags &= ~4;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = p->mUnknown512.mUnknown4;
    return 0;
}

extern "C" int fn_801109A4(Object_80039F5C *p)
{
    int result = 0;
    State_801108D4 *pState = (State_801108D4 *)&p->mUnknown336;

    switch (pState->mUnknown12) {
    case 0:
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mUnknown512.mUnknown4;
        break;
    case 1:
        fn_801100E8(p);
        p->mUnknown512.mUnknown14 = 0;
        AudmonEventPostId(97, &p->mMotion.mPos, p->mId, p->mpState->mId, 0, 0);
        pState->mUnknown12 = 3;
        break;
    case 2:
        if (p->mFlags & 0x40000000) {
            p->mFlags &= ~0x40000000;
            StyleTrackerFinishSpin(p);
        }
        if (p->mFlags & 4) {
            p->mRatings[2] = pState->mUnknown8;
            p->mFlags &= ~4;
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = 0.72f;
            p->mUnknown512.mUnknown15 = 0;
            result = 1;
        } else if (p->mFlags & 1) {
            p->mFlags &= ~1;
            pState->mUnknown14 = 1;
            fn_800A5A8C(5, p, p);
        }
        break;
    case 3:
        if (fn_800C4B6C(p)) {
            result = 1;
        } else {
            pState->mUnknown12 = 2;
        }
        break;
    }
    return result;
}

extern "C" int fn_80110B00(Object_80039F5C *p)
{
    int done = 0;
    State_801108D4 *pState = (State_801108D4 *)&p->mUnknown336;
    Input_800B6D34 input;

    if (pState->mUnknown12 == 0) {
        pState->mUnknown4 = (short)(pState->mUnknown4 - 1);
        if (pState->mUnknown4 > 0) {
            fn_800B6D34(p, &input);
            if (input.mUnknown4 != 0.0f) {
                if (input.mUnknown4 < 0.0f) {
                    p->mpState->mUnknown2 = 1;
                } else {
                    p->mpState->mUnknown2 = 2;
                }
            } else if (input.mUnknown0 & 4) {
                p->mpState->mUnknown2 = 1;
            } else if (input.mUnknown0 & 8) {
                p->mpState->mUnknown2 = 2;
            }
            if (pState->mUnknown13) {
                if (input.mUnknown72[0] == 1.0f || input.mUnknown72[0] < pState->mUnknown0) {
                    done = 1;
                } else {
                    pState->mUnknown0 = input.mUnknown72[0];
                }
            } else if (!(input.mUnknown93 & 2)) {
                done = 1;
            }
        } else {
            done = 1;
        }
        if (done == 1) {
            p->mpState->mUnknown1 = 2;
            pState->mUnknown12 = done;
        }
    }
    return 0;
}

extern "C" int fn_80110C10(Object_80039F5C *p)
{
    unsigned short key = fn_801BE648(p->mpUnknown792);

    if (key == 154 || key == 188) {
        return ((Block_8011067C *)fn_801BE60C(p->mpUnknown792, key))->mUnknown32;
    }
    return p->mMotion.mFacing;
}

extern "C" int fn_80110C68(Object_80039F5C *p)
{
    return ((State_80113AAC *)&p->mUnknown336)->mUnknown14;
}

extern "C" int fn_80110C70(Table_8010B738_8010F43C *pTable, unsigned short key, void *pA, Entry_800EAC9C *pEntries,
                           Object_80039F5C *p, int mode)
{
    Block_8011067C *pBlock = (Block_8011067C *)fn_801BE60C(p->mpUnknown792, key);
    int angle;
    unsigned char side;
    unsigned int index;
    Entry_800EAC9C *pEntry;
    Record_8010B738_8010F43C *pRecord;

    switch (mode) {
    case 0:
        fn_801BE760(p->mpUnknown792, key, 1);
        angle = fn_801105B0(p);
        side = p->mUnknown1008.mUnknown1;
        fn_801104BC(p, pBlock);
        fn_801104E4(p, pBlock);
        index = fn_8011067C((Table_8010B738 *)pTable, p, pBlock, angle);
        pBlock->mUnknown8 = AnimChanStartAnim(pA, pEntries, pTable->mEntries[index].mUnknown0,
                                        pTable->mEntries[index].mUnknown2, key, p, 1.0f);
        if (p->mUnknown776 == 1) {
            pEntry = &pEntries[pBlock->mUnknown8];
            AnimChanSetMirrored(pEntry, AnimChanIsMirrored(pEntry) == 0);
            if (side == 6) {
                side = 3;
            } else {
                side = 6;
            }
        }
        if (side == 6) {
            pBlock->mUnknown32 = (p->mMotion.mFacing - angle) & 0xFFFFFF;
        } else {
            pBlock->mUnknown32 = (p->mMotion.mFacing + angle) & 0xFFFFFF;
        }
        AnimSeqSetSpeed(&pEntries[pBlock->mUnknown8].mUnknown4C, MathInverse(pBlock->mUnknown16));
        pEntries[pBlock->mUnknown8].mUnknown2C = pBlock->mUnknown20;
        pBlock->mUnknown28 = (int)(pBlock->mUnknown24 / pBlock->mUnknown12);
        pRecord = pTable->mEntries[index].mpRecord;
        pBlock->mUnknown0 = pRecord->mUnknown28;
        pBlock->mUnknown4 = pRecord->mUnknown32;
        p->mFlags &= ~4;
        break;
    case 2:
        if (fn_801BE648(p->mpUnknown792) == key) {
            p->mMotion.mFacing = (p->mMotion.mFacing + pBlock->mUnknown28) & 0xFFFFFF;
            pEntries[pBlock->mUnknown8].mUnknownC = (pEntries[pBlock->mUnknown8].mUnknownC + pBlock->mUnknown28) & 0xFFFFFF;
            if (p->mFlags & 4) {
                pBlock->mUnknown28 = 0;
            }
        }
        break;
    }
    return 0;
}

extern "C" int fn_80110EB0(Object_80039F5C *p, Object_80039F5C *a)
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
            MathAngleDiff(angle, p->mMotion.mFacing);
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
        if (p != BallGetCurrentHolder()) {
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
        memset(&message, 0, 4);
        message.mId = 43;
        message.mUnknown1[0] = a;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int fn_80111104(Object_80039F5C *p)
{
    State_80111104 *pState = (State_80111104 *)&p->mUnknown336;
    short value;

    pState->mUnknown4 = p->mRatings[2];
    if (p->mpState->mUnknown1 != 3) {
        pState->mUnknown0 = fn_80110EE4(p);
        if (pState->mUnknown0 != 22) {
            StyleTrackerBeginStiffArm(1);
            pState->mUnknown6 = lbl_803EAF5E + (pState->mUnknown4 >> 4);
            value = pState->mUnknown4 + 20;
            p->mRatings[2] = value > 255 ? 255 : value;
            if (fn_800CA5CC(p, 2, 1)) {
                pState->mUnknown0++;
            }
            p->mUnknown512.mUnknown15 = pState->mUnknown0Bytes[3];
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
            p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
        }
        return 0;
    }
    return 1;
}

extern "C" int fn_801111E8(Object_80039F5C *p)
{
    State_80111104 *pState = (State_80111104 *)&p->mUnknown336;

    pState->mUnknown6 = (signed char)(pState->mUnknown6 - 1);
    if ((short)pState->mUnknown6 < 0) {
        p->mRatings[2] = pState->mUnknown4;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.72f;
        p->mUnknown512.mUnknown15 = 0;
        StyleTrackerResolveStiffArm(p, 0);
        return 1;
    }
    p->mUnknown512.mUnknown15 = pState->mUnknown0Bytes[3];
    if (!(p->mFlags & 0x4000)) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 1.0f;
    } else if (p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed < 0.65f) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.65f;
    }
    return 0;
}

extern "C" int fn_801112D8(Object_80039F5C *p)
{
    p->mRatings[2] = p->mUnknown340;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown0 = 0.72f;
    p->mUnknown512.mUnknown15 = 0;
    return 1;
}

extern "C" int fn_80111314(Object_80039F5C *p)
{
    Input_800B6D34 input;

    fn_800B6D34(p, &input);
    fn_800B6E68(p, &input);
    return 0;
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

extern "C" int fn_801113DC(Object_80039F5C *p)
{
    State_801113DC *pState;
    State_80039F5C *pMessage;

    p->mUnknown9[0] = 1;
    StyleTrackerOnCarrierActionFive(p);
    pState = (State_801113DC *)&p->mUnknown336;
    pState->mUnknown0 = 255;
    pState->mUnknown4 = 0.0f;
    pState->mUnknown12 = BallFindHeldBy(p) != 0;
    pState->mpUnknown16 = fn_8009BCE8(&p->mUnknown560.mUnknown40);
    fn_800DB520(pState->mUnknown20, p, fn_8017876C(), pState->mUnknown4);
    fn_8009BD60(p);
    pMessage = p->mpState;
    if ((pMessage->mUnknown3[0] >> 4) > 1) {
        p->mUnknown1008.mUnknown0 = pMessage->mUnknown1;
        p->mUnknown1008.mUnknown1 = pMessage->mUnknown2;
        p->mUnknown1008.mUnknown2 = pMessage->mUnknown3[0] >> 4;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 193, 1.0f, p);
    } else {
        p->mUnknown1008.mUnknown2 = pMessage->mUnknown1 & 15;
        p->mUnknown1011 = pMessage->mUnknown1 >> 4;
        p->mUnknown1008.mUnknown1 = pMessage->mUnknown3[0];
        p->mUnknown1008.mUnknown0 = pMessage->mUnknown2;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 44, 1.0f, p);
    }
    p->mFlags &= ~4;
    p->mUnknown512.mUnknown14 = 0;
    return 0;
}

extern "C" int fn_80111528(Object_80039F5C *p)
{
    Input_800B6D34 input;

    fn_800B6D34(p, &input);
    if (input.mUnknown95 & 64) {
        fn_800DB60C((Record_800DB60C *)&((State_8010CAE8 *)&p->mUnknown336)->mUnknown20, p);
    } else {
        fn_800B7FE8(p);
    }
    return 0;
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

extern "C" int fn_801115C0(Object_80039F5C *p)
{
    int result = 0;
    float limit;
    float x;

    if (p->mpState->mId == 59) {
        limit = 0.5f;
    } else {
        limit = 0.4f;
    }
    x = fabsf(p->mMotion.mPos.mX);
    if (x > fn_80178A08()) {
        if (x - fn_80178A08() < limit) {
            result = 1;
        }
    } else if (fn_80178A08() - x < limit) {
        result = 1;
    }
    return result;
}

extern "C" int fn_8011165C(Object_80039F5C *p)
{
    float x = p->mMotion.mPos.mX;

    if (p->mUnknown776 == 1) {
        x = -x;
    }
    if (x > 0.0f) {
        return 13;
    }
    return 14;
}

extern "C" int fn_8011168C(Object_80039F5C *p)
{
    int result = 0;
    Object_800B26B0 *pMotion = &p->mMotion;
    int angle;
    Message_800F01CC message;

    if (pMotion->mUnknown28 > gPlyrMoveFwdSpeed * 0.4f && pMotion->mUnknown44 > 0.0f && fn_801115C0(p)) {
        if (p->mMotion.mPos.mX > 0.0f) {
            angle = (pMotion->mUnknown32 - 0x400000) & 0xFFFFFF;
            result = angle > 0xF8E38F;
        } else {
            angle = (pMotion->mUnknown32 - 0x400000) & 0xFFFFFF;
            if (angle <= 0x71C70) {
                result = 1;
            }
        }
    }
    if (result) {
        memset(&message, 0, 4);
        message.mId = 59;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int fn_80111794(Object_80039F5C *p)
{
    State_80111794 *pState = (State_80111794 *)&p->mUnknown336;

    pState->mUnknown0 = fn_8011165C(p);
    pState->mUnknown4 = 70 - p->mRatings[0] / 16;
    p->mUnknown512.mUnknown14 = 0;
    p->mUnknown512.mUnknown15 = pState->mUnknown0Bytes[3];
    return 0;
}

extern "C" int fn_801117F8(Object_80039F5C *p)
{
    State_80111794 *pState = (State_80111794 *)&p->mUnknown336;
    int angle;

    if (--pState->mUnknown4 < 0 || !fn_801115C0(p)) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.72f;
        p->mUnknown512.mUnknown15 = 0;
        return 1;
    }
    p->mUnknown512.mUnknown15 = pState->mUnknown0Bytes[3];
    if (!(p->mFlags & 0x4000)) {
        angle = p->mMotion.mFacing;
        if (pState->mUnknown4 <= 34) {
            if (pState->mUnknown0 == 14) {
                angle -= (int)(p->mRatings[0] * 913.78827f);
            } else {
                angle += (int)(p->mRatings[0] * 913.78827f);
            }
        }
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = angle & 0xFFFFFF;
        p->mUnknown512.mUnknown0 = 1.0f;
    }
    return 0;
}

extern "C" int fn_80111964(Object_80039F5C *p)
{
    p->mUnknown512.mUnknown15 = 0;
    return 1;
}

extern "C" int fn_80111974(Object_80039F5C *p)
{
    State_80111794 *pState = (State_80111794 *)&p->mUnknown336;
    Input_800B6D34 input;
    int b = 0;

    fn_800B6D34(p, &input);
    if ((input.mUnknown96 & 1) || (input.mUnknown96 & 0x10)) {
        b = 1;
    }
    if ((input.mUnknown92 & 1) && fn_800E815C(p, 0, b)) {
        return 0;
    }
    if (pState->mUnknown4 <= 34) {
        fn_800B6E68(p, &input);
    } else {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 1.0f;
    }
    return 0;
}

/* Where the player's hands reach after running length along angle: the
   step from his speed along angle (cut by 30 when angle differs from his
   facing, never below 0), plus the midpoint of his two wrists. */
extern "C" void CatchGetHandReach(Object_80039F5C *p, int angle, float length, Vector_80039F5C *pOut)
{
    Vector_80039F5C right;
    Vector_80039F5C left;
    int angles[4];
    Point_8017886C step;

    if (MathAngleDiff(angle, p->mMotion.mUnknown32) != 0) {
        length -= 30.0f;
        if (length < 0.0f) {
            length = 0.0f;
        }
    }
    fn_80227538(&step, angle, p->mMotion.mUnknown28);
    fn_80227248(pOut, &step, length);
    fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "rwrist"), &right, angles);
    fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, "lwrist"), &left, angles);
    fn_8022765C(&right, &right, &left);
    fn_80227264(&right, &right, 0.5f);
    fn_80227638(pOut, pOut, &right);
}

extern "C" int fn_80111B4C(Object_80039F5C *p)
{
    State_8010CAE8 *pState = (State_8010CAE8 *)&p->mUnknown336;
    Vector_80039F5C travel;
    Vector_80039F5C ahead;
    Vector_80039F5C fromTarget;
    Vector_80039F5C toBall;
    Vector_80039F5C closest;
    Vector_80039F5C velocity;
    Vector_80039F5C ball;
    Vector_80039F5C target;
    Vector_80039F5C offset;
    float distance;
    float along;
    float maxDistance;
    float maxHeight;
    float minHeight;
    float height;
    Ball_t *pBall;
    int travelAngle;
    int targetAngle;
    int result;

    travel.mZ = 0.0f;
    fromTarget.mZ = 0.0f;
    toBall.mZ = 0.0f;
    ahead.mZ = 0.0f;
    maxDistance = lbl_803EAF6C;
    result = 1;
    maxHeight = lbl_803EAF70;
    minHeight = lbl_803EAF74;
    pBall = BallGet(p->mpState->mUnknown1);
    BallGetLandingPoint(pBall, &ball);
    BallGetPosition(pBall, &target);
    fn_80227690(&travel, &ball, &target);
    fn_80227690(&fromTarget, &p->mMotion.mPos, &target);
    fn_80227690(&toBall, &ball, &p->mMotion.mPos);
    travelAngle = fn_801CFE40(travel.mY, travel.mX);
    targetAngle = fn_801CFE40(fromTarget.mY, fromTarget.mX);
    if (lbl_803EAF7C) {
        if (p->mUnknown528.mUnknown0 <= lbl_803EAF68 ||
            MathAngleDiff(p->mMotion.mFacing, (targetAngle + 0x800000) & 0xFFFFFF) < (int)(lbl_803EAF64 * 46603.379f)) {
            fn_80227248(&ahead, &travel, 4.0f);
            fn_80227638(&ahead, &ahead, &target);
            target.mZ = 0.0f;
            fn_80227970(&target, &ahead, &p->mMotion.mPos, &closest, &distance, &along);
            if (pState->mUnknown20) {
                maxDistance *= lbl_803EAF78 + 1.0f;
                maxHeight *= lbl_803EAF78 + 1.0f;
                minHeight *= 1.0f - lbl_803EAF78;
            }
            if (distance < maxDistance) {
                distance = fn_8022781C(&target, &closest);
                BallGetVelocity(pBall, &velocity);
                height = BallGetHeightAtTime(pBall, distance / fn_802270A4(&velocity));
                if (height < maxHeight * p->mUnknown768 && height > minHeight * p->mUnknown768) {
                    result = 0;
                    pState->mUnknown20 = 1;
                }
            }
        }
    } else {
        if (MathAngleDiff(travelAngle, targetAngle) < (int)(lbl_803EAF60 * 46603.379f) &&
            MathAngleDiff(p->mMotion.mFacing, (targetAngle + 0x800000) & 0xFFFFFF) < (int)(lbl_803EAF64 * 46603.379f) &&
            fn_802270A4(&fromTarget) < fn_802270A4(&travel) && fn_802270A4(&toBall) < 0.5f) {
            result = 0;
        }
        if (result) {
            fn_802276B4(&offset, &ball, &p->mMotion.mPos);
            if (fn_802270A4(&offset) < 0.5f) {
                result = 0;
            }
        }
    }
    if (result) {
        pState->mUnknown20 = 0;
    }
    return result;
}

extern "C" void fn_80111E80(Object_80039F5C *p)
{
    Vector_80039F5C ball;
    Point_8017886C delta;
    Ball_t *pBall = BallGetCurrent();
    int angle;
    float distance;

    BallGetLandingPoint(pBall, &ball);
    fn_80227690(&delta, &ball, &p->mMotion.mPos);
    if (fn_802270A4(&delta) < 10.0f) {
        BallGetPosition(pBall, &ball);
        fn_80227690(&delta, &ball, &p->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        if (MathAngleDiff(angle, p->mMotion.mFacing) <= 0x71C71B) {
            distance = fn_802270A4(&delta);
            if (distance < 35.0f) {
                fn_800C89F0(p, angle, 2, 0, 1.0f - distance / 35.0f);
            }
        }
    }
}

extern "C" int fn_80111F80(Object_80039F5C *p)
{
    State_80111F80 *state = (State_80111F80 *)&p->mUnknown336;

    fn_8009A8D4(state);
    state->mUnknown20 = 0;
    return 0;
}

extern "C" int fn_80111FBC(Object_80039F5C *p)
{
    State_80111F80 *state = (State_80111F80 *)&p->mUnknown336;
    Vector_80039F5C delta;
    Vector_80039F5C ball;
    Vector_80039F5C from;
    Vector_80039F5C velocity;
    Vector_80039F5C pos;
    Vector_80039F5C offset;
    Message_800F01CC message;
    Point_8017886C toBall;
    float height;
    int value;
    int extra;
    Ball_t *pBall;
    int target = 0x1FFFFFFF;
    int flag;
    int found;
    int a;
    int mode;
    float range;
    float t;
    float speed;

    pBall = BallGet(p->mpState->mUnknown1);
    BallGetLandingPoint(pBall, &ball);
    BallGetPosition(pBall, &from);
    BallGetVelocity(pBall, &velocity);
    fn_802276B4(&offset, &from, &p->mMotion.mPos);
    if (!(p->mFlags & 0x4000)) {
        if (ball.mX > fn_80178A08()) {
            ball.mX -= 2.0f * (ball.mX - fn_80178A08());
        } else if (ball.mX < -fn_80178A08()) {
            ball.mX -= 2.0f * (ball.mX + fn_80178A08());
        }
        if (lbl_803EAF7D != 0) {
            if (ball.mX > fn_80178A08() - 3.0f && p->mMotion.mPos.mX < ball.mX) {
                if (ball.mX > fn_80178A08() + 0.5f) {
                    if (fabsf(ball.mX - from.mX) < 1e-7f) {
                        t = 0.0f;
                    } else {
                        t = (fn_80178A08() + 0.5f - from.mX) / (ball.mX - from.mX);
                    }
                    ball.mX = fn_80178A08() + 0.5f;
                    ball.mY = (ball.mY - from.mY) * t + from.mY;
                }
                fn_80227690(&delta, &p->mMotion.mPos, &ball);
                fn_80227538((Point_8017886C *)&delta, fn_801CFE40(delta.mY, delta.mX), 1.25f);
                fn_80227638(&ball, &ball, &delta);
            }
            if (ball.mX < -(fn_80178A08() - 3.0f) && p->mMotion.mPos.mX > ball.mX) {
                if (ball.mX < -(fn_80178A08() + 0.5f)) {
                    if (ball.mX - from.mX != 0.0f) {
                        t = (-(fn_80178A08() + 0.5f) - from.mX) / (ball.mX - from.mX);
                    } else {
                        t = 0.0f;
                    }
                    ball.mX = -(fn_80178A08() + 0.5f);
                    ball.mY = (ball.mY - from.mY) * t + from.mY;
                }
                fn_80227690(&delta, &p->mMotion.mPos, &ball);
                fn_80227538((Point_8017886C *)&delta, fn_801CFE40(delta.mY, delta.mX), 1.25f);
                fn_80227638(&ball, &ball, &delta);
            }
        }
        ball.mY = ball.mY > fn_80178A44() - 0.75f ? fn_80178A44() - 0.75f : ball.mY;
    } else {
        BallGetLandingPoint(BallGetCurrent(), &pos);
        fn_80227690(&toBall, &pos, &p->mMotion.mPos);
        if (MathAngleDiff(p->mUnknown512.mUnknown4, fn_801CFE40(toBall.mY, toBall.mX)) > 0x200000) {
            Object_80039F5C *pOther = fn_800FB9D4(p);

            if (pOther != 0) {
                memset(&message, 0, 4);
                message.mId = 24;
                message.mUnknown1[0] = 2;
                fn_800F053C(0, pOther->mpState, &message, pOther);
            }
        }
    }
    flag = ball.mY >= fn_80177FE0().mY + 2.0f;
    if (MathAngleDiff(p->mMotion.mFacing, 0xC00000) < 0x2AAAAA) {
        flag = 0;
    }
    if (BallStateGet(pBall, 0) != 4) {
        memset(&message, 0, 4);
        if (BallGetHolder(pBall) == p) {
            message.mId = 1;
            fn_800F053C(0, p->mpState, &message, p);
            return 1;
        }
        return 1;
    }
    if (!(p->mFlags & 0x4000)) {
        if (flag == 1) {
            a = 0;
            mode = 3;
        } else {
            a = 0;
            mode = 2;
        }
    } else {
        a = 0;
        mode = 1;
    }
    if (p->mUnknown8 == 0xFF) {
        range = 120.0f;
    } else {
        range = 17.0f;
    }
    BallGetLandingTime(pBall, &height);
    value = -1;
    extra = 0;
    if (fn_8009A6EC(p)) {
        target = fn_800997F4(p, pBall, range, state, 3, 0, 0, &value, &extra);
    }
    if (target == 0x1FFFFFFF) {
        target = fn_80099734(p, pBall, 0, mode, range, state, 1, 0, 0, PlyrRollContestedCatch(p));
    }
    if (target != 0x1FFFFFFF) {
        int result;

        if (((target >> 29) & 3) == 1) {
            result = fn_8009A1A8(p, target, value, extra, p->mpState->mUnknown1);
        } else {
            result = fn_80099F04(p, target, p->mpState->mUnknown1);
        }
        if (result != 0) {
            return 0;
        }
    } else if (height <= lbl_803EAF80) {
        BallGetLandingPoint(pBall, &pos);
        flag = 0;
        if (fn_8022781C(&p->mMotion.mPos, &pos) < lbl_803EAF84) {
            if (BallGetTarget(pBall) == p && fn_801783AC(11) == 0) {
                if (MathAngleDiff(fn_801CFE40(offset.mY, offset.mX), p->mMotion.mFacing) >
                    (int)(lbl_803EAF88 * 46603.378f)) {
                    mode = 2;
                }
                flag = 1;
            } else if (fn_801783AC(11) == 1 && fn_8022781C(&p->mMotion.mPos, &pos) > lbl_803EAF8C) {
                a = 3;
                mode = 3;
                flag = 1;
            }
            if (flag) {
                found = 1;
                target = fn_80099734(p, pBall, a, mode, range, state, 1, 0, 1, PlyrRollContestedCatch(p));
                if (target == 0x1FFFFFFF) {
                    found = 0;
                }
            } else {
                found = 0;
            }
            if (found && fn_80099F04(p, target, p->mpState->mUnknown1) == 1) {
                return 0;
            }
        }
    }
    if (!(p->mFlags & 0x4000)) {
        fn_802276B4(&delta, &ball, &p->mMotion.mPos);
        if (fn_80111B4C(p)) {
            float ratio;
            float distance;

            speed = gPlyrMoveFwdSpeed * (lbl_803ED6CC + (1.0f - lbl_803ED6CC) * (p->mRatings[4] / 255.0f));
            fn_802276B4(&ball, &ball, &from);
            if (fn_802270A4(&velocity) != 0.0f) {
                ratio = fn_802270A4(&ball) / fn_802270A4(&velocity);
            } else {
                ratio = 0.0f;
            }
            distance = fn_802270A4(&delta);
            if (distance > 0.5f) {
                distance -= 0.5f;
            }
            if (ratio == 0.0f) {
                distance = 0.0f;
            } else {
                distance /= ratio;
            }
            if (distance > speed) {
                t = 1.0f;
            } else if (speed != 0.0f) {
                t = distance / speed;
            } else {
                t = 0.0f;
            }
            if (t < 0.4f) {
                t = 0.4f;
            }
            if (t != 0.0f) {
                int angle = fn_801CFE40(delta.mY, delta.mX);

                if (MathAngleDiff(angle, p->mMotion.mFacing) < 0xAAAAA) {
                    p->mUnknown512.mUnknown15 = 1;
                }
                if (MathAngleDiff(p->mMotion.mFacing, angle) > 0x600000) {
                    int turn = (p->mMotion.mFacing + 0x5F49F5) & 0xFFFFFF;

                    if (MathAngleDiff(turn, angle) > 0x400000) {
                        turn = (turn + 0x800000) & 0xFFFFFF;
                    }
                    angle = turn;
                }
                p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = angle;
                p->mUnknown512.mUnknown14 = 1;
                p->mUnknown512.mUnknown0 = t;
            }
        } else {
            fn_80227690(&offset, &from, &p->mMotion.mPos);
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = fn_801CFE40(offset.mY, offset.mX) & 0xFFFFFF;
            p->mUnknown512.mUnknown4 = fn_801CFE40(offset.mY, offset.mX) & 0xFFFFFF;
            p->mUnknown512.mUnknown0 = 0.0f;
        }
        fn_80111E80(p);
    }
    return 0;
}

extern "C" int fn_80112928(Object_80039F5C *p)
{
    int attempt = 0;
    Ball_t *pBall = BallGetCurrent();
    Object_80039F5C *pTarget;
    Message_800F01CC message;
    Vector_80039F5C ballPos;
    Vector_80039F5C pos;
    float time;
    Point_8017886C landing;
    Point_8017886C delta;

    if (fn_801783AC(11) == 1 || fn_801783AC(12) == 1) {
        attempt = 1;
    }
    pTarget = BallGetTarget(pBall);
    if (p == pTarget && BallStateGet(pBall, 0) == 4) {
        attempt = 1;
    } else if (BallGetLandingPoint(pBall, &ballPos) != 0 && pTarget != 0 && BallGetLandingTime(pBall, &time) != 0) {
        float targetDistance;
        float otherDistance;
        float distance;
        float targetSpeed;
        float speed;

        BallSolveFallToHeight(pBall, 2.0f, 0, (Vector_80039F5C *)&landing);
        fn_80227690(&delta, &pTarget->mMotion.mPos, &landing);
        targetDistance = fn_802270A4(&delta) - 2.0f;
        fn_80227690(&delta, &pTarget->mMotion.mPos, &ballPos);
        otherDistance = fn_802270A4(&delta) - 2.0f;
        if (otherDistance < targetDistance) {
            targetDistance = otherDistance;
        }
        fn_80227690(&delta, &p->mMotion.mPos, &ballPos);
        distance = fn_802270A4(&delta) + 0.5f;
        targetSpeed = PlyrMoveGetRatedSpeed(pTarget, 1.0f, 1.0f);
        speed = PlyrMoveGetRatedSpeed(p, 1.0f, 1.0f);
        if (targetDistance / targetSpeed > time && distance / speed < time) {
            attempt = 1;
        }
    }
    if (attempt != 0) {
        float chance;

        BallGetVelocity(pBall, &pos);
        if (pos.mZ < 0.0f && fn_801783AC(11) == 0 && fn_801783AC(12) == 0) {
            chance = 1.0f;
        } else {
            chance = p->mRatings[3] * 0.00078431377f;
            if (fn_8009F0B8(p, 0x400000) != 0) {
                chance += 0.15f;
            }
            if (p == pTarget) {
                chance = 1.0f;
            }
            if (fn_800A7F1C(p->mIdBytes[2]) == 0) {
                chance = 0.0f;
            }
        }
        if (fn_80237260(0) <= chance) {
            memset(&message, 0, sizeof(message));
            message.mId = 23;
            message.mUnknown1[0] = BallGetIndex(pBall);
            fn_800F053C(0, p->mpState, &message, p);
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_80112C04(Object_80039F5C *p, Ball_t *pBall, int *pAngle, float *pValue)
{
    Vector_80039F5C velocity;
    Vector_80039F5C playerVelocity;
    float lowTime;
    Point_8017886C lowLanding;
    float highTime;
    Point_8017886C highLanding;
    Point_8017886C lowReach;
    Point_8017886C highReach;
    Point_8017886C middle;
    int lowAngle;
    int highAngle;
    float value;

    BallGetVelocity(pBall, &velocity);
    playerVelocity.mX = p->mMotion.mUnknown40;
    playerVelocity.mY = p->mMotion.mUnknown44;
    playerVelocity.mZ = p->mMotion.mUnknown48;
    BallSolveFallToHeight(pBall, 0.8f, &lowTime, (Vector_80039F5C *)&lowLanding);
    BallSolveFallToHeight(pBall, 2.1f, &highTime, (Vector_80039F5C *)&highLanding);
    fn_80227690(&lowLanding, &lowLanding, &p->mMotion.mPos);
    lowAngle = fn_801CFE40(lowLanding.mY, lowLanding.mX);
    CatchGetHandReach(p, lowAngle, lowTime, (Vector_80039F5C *)&lowReach);
    fn_80227690(&lowReach, &lowReach, &p->mMotion.mPos);
    fn_80227690(&highLanding, &highLanding, &p->mMotion.mPos);
    highAngle = fn_801CFE40(highLanding.mY, highLanding.mX);
    CatchGetHandReach(p, highAngle, highTime, (Vector_80039F5C *)&highReach);
    fn_80227690(&highReach, &highReach, &p->mMotion.mPos);
    value = *pValue;
    if (fn_802270A4(&highLanding) > fn_802270A4(&highReach)) {
        if (value < 0.9f) {
            value += 0.1f;
        } else {
            value = 1.0f;
        }
        *pAngle = lowAngle;
    } else if (fn_802270A4(&lowLanding) < fn_802270A4(&lowReach)) {
        if (value > 0.24000001f) {
            value -= 0.1f;
        } else {
            value = 0.14f;
        }
        *pAngle = highAngle;
    } else {
        fn_80227638(&middle, &lowLanding, &highLanding);
        *pAngle = fn_801CFE40(middle.mY, middle.mX);
    }
    *pValue = value;
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
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
            break;
        }
    } else if (state->mUnknown13 == 1) {
        fn_800D7A0C(p, state->mUnknown4);
    }
    return result;
}

extern "C" int fn_80112F8C(Object_80039F5C *p)
{
    State_80112E10 *state = (State_80112E10 *)&p->mUnknown336;
    Input_800B6D34 input;
    int flag;

    fn_800B6D34(p, &input);
    flag = 0;
    if (state->mUnknown13 == 0) {
        p->mUnknown512.mUnknown15 = 22;
        if (input.mUnknown95 & 8) {
            p->mUnknown512.mUnknown15 = 23;
            p->mFlags |= 0x4000;
        }
        if ((input.mUnknown96 & 1) || (input.mUnknown96 & 0x10)) {
            flag = 1;
        }
        if (((input.mUnknown92 & 1) && fn_800E815C(p, 0, flag) != 0) ||
            ((input.mUnknown93 & 4) && CarrierMoveStart(p, flag) != 0)) {
            p->mFlags |= 0x4000;
            return 0;
        }
        fn_800B6E68(p, &input);
    } else {
        return fn_800B76E8(p);
    }
    return 0;
}

extern "C" int fn_80113088(Object_80039F5C *p)
{
    int result = 0;
    int ballState = BallStateGet(BallGetCurrent(), 0);
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
                Object_80039F5C *pCarrier = BallGetCurrentHolder();
                if (pCarrier != 0 && pCarrier->mpState->mId == 15) {
                    result = 1;
                }
            }
            if (result == 0 && fn_801486A0() == 1) {
                unsigned int count = BallsGetCount();
                unsigned int i;
                for (i = 1; i < count; i++) {
                    Ball_t *pBall = BallGet(i);
                    int state = BallStateGet(pBall, 0);
                    Object_80039F5C *pOther;
                    if (state == 3 || state == 4) {
                        result = 1;
                        break;
                    }
                    pOther = BallGetHolder(pBall);
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
    Ball_t *pBall;
    int target;

    index = 0;
    if (mode == 1 || mode == 3) {
        flag = 1;
    }
    if (fn_801486A0() == 1 && fn_801520C4(p, &index) != 0) {
        pBall = BallGet(index);
    } else {
        pBall = BallGetCurrent();
        index = BallGetIndex(pBall);
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
        memset(&message, 0, sizeof(message));
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

extern "C" int fn_80113498(Object_80039F5C *p)
{
    int result = 0;
    Timer_8010FD94 *pTimer = (Timer_8010FD94 *)&p->mUnknown336;

    if (p->mFlags & 0x4000) {
        pTimer->mUnknown0 += (unsigned int)gFrameTimeScale;
    } else {
        result = 1;
    }
    return result;
}

extern "C" int fn_80113510(Object_80039F5C *p)
{
    State_80113478 *state = (State_80113478 *)&p->mUnknown336;
    Input_800B6D34 input;
    int result;
    int c = 0;
    int a;
    int pressed;

    fn_800B6D34(p, &input);
    result = 0;
    a = 0;
    fn_800B6E68(p, &input);
    if (p->mpState->mUnknown2 != 0) {
        pressed = (input.mUnknown92 >> 1) & 1;
    } else {
        pressed = (input.mUnknown92 >> 3) & 1;
    }
    if (input.mUnknown96 & 1) {
        c = 1;
    }
    if (pressed) {
        int mode = state->mUnknown4;
        if (state->mUnknown0 > 15) {
            a = 1;
        }
        if (fn_80113208(p, a, mode, c) != 0) {
            result = 1;
        }
    } else {
        fn_80113208(p, 1, state->mUnknown4, c);
        result = 1;
    }
    return result;
}

extern "C" int fn_801135E4(Object_80039F5C *p)
{
    return fn_80113604(p);
}

extern "C" int fn_80113604(Object_80039F5C *p)
{
    State_80039F5C *pState = p->mpState;
    Object_80039F5C *pOther = PlyrGet(p->mIdBytes[2], pState->mUnknown1);
    unsigned int bit = 1 << pState->mUnknown2;

    if ((pOther->mFlags & bit) == bit) {
        return 1;
    }
    if (pState->mUnknown3[0] != 0) {
        fn_8010A2DC(p, 0, -1);
    }
    return 0;
}

extern "C" int fn_80113680(Object_80039F5C *p)
{
    State_80113680 *state = (State_80113680 *)&p->mUnknown336;
    Object_80039F5C *pOther;
    State_80039F5C *pState;

    if (p->mpState->mUnknown3[0] == 255) {
        return 1;
    }
    p->mUnknown9[0] = 1;
    state->mUnknown21 = 0;
    pOther = PlyrGet(p->mIdBytes[2] ^ 1, p->mpState->mUnknown3[0]);
    fn_8009BD2C(pOther, &state->mRef);
    p->mFlags |= 8;
    PlyrCollideAddExempt(p, pOther);
    state->mUnknown4 = 255;
    state->mUnknown8 = 0.0f;
    state->mUnknown12 = 0;
    state->mUnknown14 = 0;
    state->mUnknown15 = 0;
    state->mUnknown18 = 0;
    state->mUnknown20 = fn_800E1554(p);
    state->mUnknown13 = 0;
    p->mUnknown1218 = fn_800CD35C(1, p);
    if (fn_800B65A0(p->mIdBytes[2]) == 255 && fn_802372EC(0, 100) > 80.0f) {
        state->mUnknown13 = 1;
    }
    fn_800CE674(&p->mUnknown1240);
    fn_800CE684(&p->mUnknown1240);
    fn_8011E8D8(p);
    pState = p->mpState;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, (pState->mUnknown1 << 8) | pState->mUnknown2, 1.0f, p);
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~4;
    return 0;
}

extern "C" int fn_8011380C(Object_80039F5C *p)
{
    State_80113680 *state = (State_80113680 *)&p->mUnknown336;
    int result = 0;
    Object_800CE674 *pAnim = &p->mUnknown1240;
    Object_80039F5C *pOther = fn_8009BCE8(&state->mRef);

    if (state->mUnknown14 == 1) {
        if (!(p->mFlags & 0x4000)) {
            state->mUnknown18++;
        }
        if (state->mUnknown14 == 1 && p->mUnknown8 != 255) {
            RumbleStart(p->mUnknown8, lbl_803EAF90, 10);
        }
    }
    if (pAnim->mUnknown0 != -1) {
        state->mUnknown4 = fn_800CE690(pAnim);
        state->mUnknown8 = fn_800CE73C(pAnim);
        fn_800CE674(pAnim);
    }
    if (pAnim->mUnknown3 != -1) {
        if (pOther == BallGetCurrentHolder()) {
            switch (pAnim->mUnknown3) {
            case 2:
                fn_800B2370(p, 4, pOther, 1.0f);
                break;
            case 3:
                fn_800B2370(p, 5, pOther, 1.0f);
                break;
            case 1:
                if (PenaltyRollFacemask() != 0) {
                    if (fn_802372EC(0, 100) < 75) {
                        fn_800B2370(p, 4, pOther, 1.0f);
                    } else {
                        fn_800B2370(p, 5, pOther, 1.0f);
                    }
                } else if (fn_802372EC(0, 100) < 20) {
                    fn_800B2370(p, 5, pOther, 0.0f);
                }
                break;
            }
        }
        fn_800CE684(&p->mUnknown1240);
    }
    if (p->mUnknown9[0] != 1) {
        Message_800F01CC message;

        p->mFlags &= ~8;
        PlyrCollideRemoveExempt(p, fn_8009BCE8(&state->mRef));
        state->mUnknown21 = 1;
        if ((unsigned int)state->mUnknown4 <= 10) {
            memset(&message, 0, sizeof(message));
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F05E4(0, p->mpState, &message, p);
        } else {
            memset(&message, 0, sizeof(message));
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F05E4(0, p->mpState, &message, p);
        }
    }
    if ((p->mFlags & 4) && state->mUnknown14 != 1 && state->mUnknown14 != 4) {
        p->mFlags &= ~0xC;
        p->mFlags &= ~0x800;
        PlyrCollideRemoveExempt(p, fn_8009BCE8(&state->mRef));
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
        result = 1;
    }
    return result;
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

extern "C" int fn_80113B28(Object_80039F5C *p)
{
    State_80113AAC *state = (State_80113AAC *)&p->mUnknown336;
    Input_800B6D34 input;

    fn_8009BCE8(&state->mRef);
    fn_800B6D34(p, &input);
    if (state->mUnknown14 == 1 || state->mUnknown14 == 4 || state->mUnknown14 == 5 ||
        fn_801BE648(p->mpUnknown792) == 234) {
        if ((input.mUnknown95 & 0x10) && state->mUnknown14 == 1) {
            state->mUnknown12++;
        }
    } else {
        return fn_800B7F34(p);
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

extern "C" int fn_80113C18(Object_80039F5C *p, void *pState) {
    return 0;
}

extern "C" int fn_80113C20(Object_80039F5C *p)
{
    State_80113C20 *state = (State_80113C20 *)&p->mUnknown336;
    unsigned short key;
    Object_80039F5C *pOther;
    Ball_t *pBall;
    State_80039F5C *pState;

    p->mUnknown9[0] = 1;
    if (PlayerMoveGetKind(p) != 0 && PlayerMoveGetKind(p) != 4 && fn_801BE648(p->mpUnknown792) != 227) {
        state->mUnknown24 = 1;
    } else {
        state->mUnknown24 = 0;
    }
    pOther = PlyrGet(p->mIdBytes[2] ^ 1, p->mpState->mUnknown3[0]);
    fn_8009BD2C(pOther, &state->mRef);
    p->mFlags |= 8;
    PlyrCollideAddExempt(p, pOther);
    state->mUnknown4 = 0.0f;
    state->mUnknown20 = 255;
    state->mUnknown25 = 1;
    state->mUnknown56 = 0;
    state->mUnknown58 = 0;
    state->mUnknown60 = 0;
    state->mUnknown64 = 0;
    state->mUnknown57 = 0;
    state->mUnknown67 = 0;
    state->mUnknown68 = 0;
    state->mUnknown66 = p->mUnknown776;
    fn_800CE674(&p->mUnknown1240);
    fn_800CE684(&p->mUnknown1240);
    fn_800DB520(&state->mUnknown32, p, pOther, state->mUnknown4);
    state->mUnknown8 = 0.0f;
    state->mUnknown16 = 0.0f;
    state->mUnknown26 = -1;
    state->mUnknown59 = 0;
    state->mUnknown31 = 0;
    state->mUnknown30 = 0;
    state->mUnknown28 = 0;
    state->mUnknown29 = 0;
    if (p->mFlags & 0x1000) {
        state->mUnknown29 = 1;
    }
    pState = p->mpState;
    key = (pState->mUnknown1 << 8) | pState->mUnknown2;
    pBall = BallFindHeldBy(p);
    if (pBall != 0) {
        Record_8011F4F8 *pRecord = fn_8011F4F8(BallGetIndex(pBall));

        if ((fn_801BE648(p->mpUnknown792) == 69 || fn_801BE648(p->mpUnknown792) == 178) &&
            pRecord->mUnknownB == 1 && key != 234 &&
            (pRecord->mUnknown1D <= 1 || pRecord->mUnknown1D == 3 || pRecord->mUnknown1D == 6 ||
             pRecord->mUnknown1D == 7)) {
            Vector_80039F5C pos;

            state->mUnknown30 = 1;
            BallGetPosition(pBall, &pos);
            state->mUnknown12 = state->mUnknown8 = pos.mZ;
        }
    }
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, key, 1.0f, p);
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~0x1005;
    if (state->mUnknown30 == 1) {
        fn_800D7A18(p);
    }
    return 0;
}

extern "C" int fn_80113E74(Object_80039F5C *p)
{
    int result = 0;
    State_80113E74 *state = (State_80113E74 *)&p->mUnknown336;
    Object_800CE674 *pAnim = &p->mUnknown1240;
    Other_80113E74 *pOtherState = 0;
    Object_80039F5C *pOther = fn_8009BCE8(&state->mRef);
    Message_800F01CC message;
    Vector_80039F5C ball;
    Vector_80039F5C hand;
    Point_8017886C aim;
    Ball_t *pBall;
    int allowed;
    float speed;

    if (pOther != 0) {
        pOtherState = (Other_80113E74 *)&pOther->mUnknown336;
    }
    if (state->mUnknown68 == 0) {
        PossCheckDownedBall(p);
        state->mUnknown68 = 1;
    }
    fn_800DB7A4(state->mUnknown32, p);
    if (state->mUnknown56 == 1) {
        state->mUnknown60++;
        if (!(p->mFlags & 0x4000)) {
            state->mUnknown64++;
            if (!(p->mFlags & 0x4000)) {
                if (fn_801486A0() == 0) {
                    fn_80114F64(p, (fn_801CFE40(p->mMotion.mPos.mY, p->mMotion.mPos.mX) + 0x800000) & 0xFFFFFF);
                } else {
                    fn_80114F64(p, 0x400000);
                }
            }
        }
    }
    if (p == BallGetCurrentHolder() && fn_801787A0() == 0 && (p->mFlags & 1)) {
        p->mFlags &= ~1;
        if (fn_801787A0() == 0) {
            if (state->mUnknown56 == 5) {
                AudmonEventPostId(61, &p->mpUnknown4->mUnknown4, p->mId, 0, 0, 0);
                StyleTrackerAwardStrip(fn_80178320());
                PossStartFumble();
                PossGrabBall(pOther);
                fn_800A8954(26, p->mIdBytes[2], p);
            } else if (fn_801BE648(p->mpUnknown792) == 234 && fn_801BE648(pOther->mpUnknown792) == 234) {
                PossStartFumble();
                PossGrabBall(pOther);
                if (fn_801787A0() == 0) {
                    StyleTrackerAwardStrip(fn_80178308());
                    fn_800A8954(26, p->mIdBytes[2], p);
                    TutorialSetMoveDone(40, 1);
                }
            } else {
                PossFumble(p);
            }
        }
    }
    if (state->mUnknown25 != 0) {
        if (BallFindHeldBy(p) == 0) {
            p->mFlags |= 0x4000000;
            state->mUnknown25 = 0;
        } else {
            if (((p->mFlags & 0x10000) && state->mUnknown56 != 4 && state->mUnknown56 != 2) ||
                state->mUnknown56 == 3) {
                allowed = 1;
                if (state->mUnknown56 == 1) {
                    allowed = p->mRatings[2] - pOther->mRatings[5] <= lbl_803EAF94;
                }
                if (allowed) {
                    fn_800DB8B4(state->mUnknown32, p);
                }
            }
        }
    }
    if (state->mUnknown30 == 1) {
        if ((p->mFlags & 0x1000) || state->mUnknown29 != 0) {
            pBall = BallFindHeldBy(p);
            if (pBall != 0) {
                BallGetPosition(pBall, &ball);
                fn_8009BF5C(p, 12, &hand, 0);
                if (fn_800A7F1C(p->mIdBytes[2]) == 2 ||
                    (ball.mZ >= state->mUnknown8 - 0.3f && ball.mZ > hand.mZ - 0.15f)) {
                    Record_8011F4F8 *pRecord = fn_8011F4F8(BallGetIndex(pBall));

                    if (pRecord->mUnknownB == 1) {
                        int angle;
                        float scale;
                        Object_80039F5C *pTarget;

                        aim.mX = 0.2f;
                        aim.mY = state->mUnknown12 - ball.mZ;
                        aim.mY = aim.mY < 0.0f ? 0.0f : aim.mY;
                        angle = aim.Heading();
                        pRecord->mUnknown10 = angle + fn_802372EC(0, 0xE38E3);
                        pRecord->mUnknown8 = (pRecord->mUnknown8 - 5) / 3 + 5;
                        pRecord->mUnknownC = state->mUnknown4 / (gPlyrMoveFwdSpeed * 100621.12f);
                        if (pRecord->mUnknownC == 0.0f) {
                            float spread = pRecord->mUnknown10 / 4194304.0f;

                            pRecord->mUnknownC = spread * 0.5f + 0.5f;
                        }
                        scale = pRecord->mUnknownC / 3.0f;
                        pRecord->mUnknown0 -= pRecord->mUnknown0 * scale;
                        pRecord->mUnknown4 -= pRecord->mUnknown4 * scale;
                        fn_80102D78(p);
                        pTarget = fn_8009BCE8(&state->mRef);
                        if (pTarget != 0) {
                            Record_800B15FC *pEvent = fn_800B15FC();

                            fn_8009BD2C(pTarget, &pEvent->mUnknown0);
                            pEvent->mUnknownC = p->mMotion.mPos.mX;
                            pEvent->mUnknown10 = p->mMotion.mPos.mY;
                            pEvent->mUnknown14 = 34;
                            fn_800B1508();
                        }
                    }
                } else {
                    fn_801039D8(p);
                }
            }
            p->mUnknown778 = -1;
            p->mFlags &= ~0x1000;
            state->mUnknown30 = 0;
        } else if (AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 69) == 0 &&
                   AnimChanGetNumActiveByState(p->mpUnknown796, p->mpUnknown800, 178) == 0) {
            p->mUnknown778 = -1;
            state->mUnknown30 = 0;
        } else {
            pBall = BallFindHeldBy(p);
            if (pBall != 0) {
                BallGetPosition(pBall, &ball);
                if (state->mUnknown12 < ball.mZ) {
                    state->mUnknown12 = ball.mZ;
                }
            }
        }
    }
    if (pAnim->mUnknown0 != -1) {
        if (state->mUnknown26 < 0) {
            state->mUnknown26 = fn_80113C18(p, state);
            state->mUnknown28 = 1;
        }
        if (pAnim->mUnknown2 != 7) {
            state->mUnknown20 = fn_800CE690(pAnim);
            state->mUnknown4 = fn_800CE73C(pAnim);
            if (state->mUnknown28 == 1) {
                if (BallGetCurrentHolder() == p) {
                    if (state->mUnknown4 >= gPlyrMoveFwdSpeed * 80496.9f || lbl_803EAF91 != 0) {
                        fn_801410F4(2);
                    } else if (state->mUnknown4 >= gPlyrMoveFwdSpeed * 70434.78f) {
                        fn_801410F4(1);
                    } else if (state->mUnknown4 >= gPlyrMoveFwdSpeed * 60372.67f) {
                        fn_801410F4(0);
                    }
                }
                if (BallGetCurrentHolder() == p) {
                    fn_8016F6F4(p, fn_8009BCE8(&state->mRef));
                }
                state->mUnknown28 = 0;
            }
        } else {
            AudmonEventPostId(45, &pOther->mMotion.mPos, pOther->mId, 0, 0, 0);
        }
        if (state->mUnknown26 == 0) {
            Ball_t *pHeld = BallFindHeldBy(p);

            if (pHeld != 0 && pHeld == BallGetCurrent() && fn_801BE648(p->mpUnknown792) != 234 &&
                fn_801BE648(p->mpUnknown792) != 238) {
                PossTryFumble(p, pOther);
            }
        }
        state->mUnknown26--;
        if (state->mUnknown26 < 0) {
            fn_800CE674(pAnim);
        }
    }
    if (state->mUnknown59 == 0 && pOtherState != 0 && state->mUnknown20 != 0xFF && pOtherState->mUnknown4 != 0xFF) {
        speed = pOtherState->mUnknown8 < state->mUnknown4 ? state->mUnknown4 : pOtherState->mUnknown8;
        AudmonEventPostId(37, &p->mMotion.mPos, p->mId, (unsigned int)speed, state->mUnknown20, pOtherState->mUnknown4);
        state->mUnknown59 = 1;
        fn_800A3B58(p, 1, 1);
        speed = pOtherState->mUnknown8 < state->mUnknown4 ? state->mUnknown4 : pOtherState->mUnknown8;
        if (speed > gPlyrMoveFwdSpeed * 100621.12f * 0.75 && BallGetCurrentHolder() == p) {
            AudmonEventPost(100, 0);
        }
    }
    if (fn_801787A0() != 0 && p->mIdBytes[3] == 1 && (p->mFlags & 0x1000)) {
        p->mFlags &= ~0x1000;
        pBall = BallFindHeldBy(p);
        if (pBall != 0) {
            BallReleaseStill(pBall, 5, 0);
        }
    }
    if (p->mUnknown9[0] != 1) {
        p->mFlags &= ~0x82008;
        PlyrCollideRemoveExempt(p, fn_8009BCE8(&state->mRef));
        state->mUnknown31 = 1;
        if (state->mUnknown20 <= 10) {
            memset(&message, 0, 4);
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F05E4(0, p->mpState, &message, p);
        } else {
            memset(&message, 0, 4);
            message.mId = 11;
            message.mUnknown1[0] = p->mUnknown9[0];
            fn_800F05E4(0, p->mpState, &message, p);
        }
    }
    if ((p->mFlags & 4) && state->mUnknown56 != 1 && state->mUnknown56 != 4) {
        result = 1;
        p->mFlags &= ~0x0409280C;
        PlyrCollideRemoveExempt(p, fn_8009BCE8(&state->mRef));
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
        StyleTrackerFinishHurdle(p);
    }
    return result;
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

extern "C" int fn_80114838(Object_80039F5C *p)
{
    State_80113C20 *state = (State_80113C20 *)&p->mUnknown336;
    Input_800B6D34 input;
    Vector_80039F5C dir;
    int done = 0;
    int port = fn_800B65A0(p->mIdBytes[2]);

    fn_800B6D34(p, &input);
    if (BallGetCurrentHolder() == p && (input.mUnknown95 & 0x40)) {
        fn_800DB60C(&state->mUnknown32, p);
    } else {
        if (state->mUnknown56 == 1) {
            if (input.mUnknown95 & 0x10) {
                done = 1;
                state->mUnknown58++;
            } else {
                dir.mX = dir.mY = 0.0f;
                if (input.mUnknown4 != 0.0f || input.mUnknown8 != 0.0f) {
                    dir.mX = input.mUnknown4;
                    dir.mY = input.mUnknown8;
                } else {
                    if (input.mUnknown0 & 1) {
                        dir.mY = 1.0f;
                    }
                    if (input.mUnknown0 & 2) {
                        dir.mY = -1.0f;
                    }
                    if (input.mUnknown0 & 4) {
                        dir.mX = -1.0f;
                    }
                    if (input.mUnknown0 & 8) {
                        dir.mX = 1.0f;
                    }
                }
                if (fabsf(dir.mY) > 1e-7f || fabsf(dir.mX) > 1e-7f) {
                    int angle = fn_801CFE40(dir.mY, dir.mX) - input.mUnknown20;
                    if (fn_801784C4() != 0) {
                        angle -= 0x800000;
                    }
                    fn_80114F64(p, angle & 0xFFFFFF);
                }
            }
            if (p->mUnknown8 != 255) {
                RumbleStart(p->mUnknown8, lbl_803EAF98, 10);
            }
        }
        if (done == 0) {
            int mode = fn_800AD9B4();
            if (p->mIdBytes[2] == fn_80178320() || mode == 3 ||
                (mode == 2 && port != 255 && fn_800B6544(port) != p)) {
                return fn_800B7FE8(p);
            }
        }
    }
    return 0;
}

extern "C" int fn_80114A30(Object_80039F5C *p, int a)
{
    State_80114DF4 *state = (State_80114DF4 *)&p->mUnknown336;
    Object_80039F5C *pOther = PlyrGet((unsigned char)(1 - p->mIdBytes[2]), p->mpState->mUnknown3[0]);
    State_80113AAC *pOtherState = (State_80113AAC *)&pOther->mUnknown336;
    Input_800B6D34 input;
    int flag;
    int result;

    fn_800B6D34(pOther, &input);
    flag = (input.mUnknown96 >> 5) & 1;
    state->mUnknown67 = a;
    if (state->mUnknown56 != 4) {
        unsigned short otherRating = pOther->mRatings[5];
        unsigned short rating = p->mRatings[2];
        int low;
        int high;
        int diff;

        if (!(p->mFlags & 0x4000)) {
            unsigned char value = fn_800AD0E4(p->mIdBytes[2]);
            state->mUnknown58 += value;
        }
        if (!(pOther->mFlags & 0x4000)) {
            unsigned char value = fn_800AD0E4(pOther->mIdBytes[2]);
            pOtherState->mUnknown12 += value;
        }
        switch (state->mUnknown57) {
        case 0:
            if (!flag) {
                low = -2;
                high = 2;
            } else {
                low = -3;
                high = 0;
            }
            break;
        case 1:
            if (!flag) {
                low = -1;
                high = 1;
            } else {
                low = -3;
                high = -1;
            }
            break;
        default:
            if (!flag) {
                low = 0;
                high = 1;
            } else {
                low = -3;
                high = -2;
            }
            break;
        }
        diff = fn_80114D14(state->mUnknown58, rating, pOtherState->mUnknown12, otherRating);
        if (fn_800C53D8(p) != 0) {
            diff = high;
        }
        if (diff >= high) {
            Record_800B15FC *pRecord;

            p->mUnknown1219 = 1;
            p->mUnknown1160.mUnknown44++;
            result = 2;
            pRecord = fn_800B15FC();
            fn_8009BD2C(p, &pRecord->mUnknown0);
            pRecord->mUnknownC = p->mMotion.mPos.mX;
            pRecord->mUnknown10 = p->mMotion.mPos.mY;
            pRecord->mUnknown14 = 38;
            pRecord->mUnknown16 = 1;
            fn_800B1508();
        } else if (diff <= low) {
            if (flag || pOtherState->mUnknown13 != 0) {
                result = 5;
            } else {
                result = 3;
            }
            p->mUnknown1219 = 0;
            p->mFlags |= 0x10000;
            p->mFlags &= ~0x80000;
            fn_80178718(pOther);
        } else {
            result = 1;
        }
        if (result == 1) {
            state->mUnknown57++;
        }
    } else {
        result = 1;
        HudSetMashPlayers(p->mId, pOther->mId, 0);
    }
    if (fn_801787A0() != 0 || (BallGetCurrentHolder() != p && BallGetCurrentHolder() != pOther)) {
        result = 3;
        if (fn_802372EC(0, 100) < 50) {
            result = 2;
        }
    }
    pOtherState->mUnknown14 = result;
    state->mUnknown56 = result;
    if (result != 1) {
        AudmonEventPostArgs(102, &p->mMotion.mPos, result, 0, 0);
        HudClearMashPlayers(p->mId, pOther->mId);
        if (result == 2) {
            StyleTrackerOnTackleContest(0, p);
        }
        if (result == 3) {
            StyleTrackerOnTackleContest(1, p);
        }
    }
    return result;
}

extern "C" int fn_80114D14(int a, unsigned char b, int c, unsigned char d)
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
    StyleTrackerOnActionFour();
    AudmonEventPostArgs(101, &p->mMotion.mPos, p->mId, pOther->mId, 0);
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
        PlyrCollideRemoveExempt(p, pOther);
        AudmonEventPostArgs(102, &p->mMotion.mPos, 0, 0, 0);
        HudClearMashPlayers(p->mId, pOther->mId);
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

extern "C" float fn_80114EE4(Object_80039F5C *pA, Object_80039F5C *pB)
{
    float a = pA->mUnknown2904Float * lbl_803EAFA4 + pA->mRatings[2];
    float b = pB->mUnknown2904Float * lbl_803EAFA4 + pB->mRatings[5];
    float ratio = a / (a + b);

    return ratio * (lbl_803EAF9C - lbl_803EAFA0) + lbl_803EAFA0;
}

extern "C" void fn_80114F64(Object_80039F5C *p, int angle)
{
    State_80113C20 *state = (State_80113C20 *)&p->mUnknown336;
    float scale = lbl_803EAFA8;
    unsigned short key = fn_801BE648(p->mpUnknown792);
    Object_80039F5C *pOpponent = fn_80114E7C(p);
    float diff = p->mRatings[2] - pOpponent->mRatings[5];
    int delta;
    Object_80039F5C *pOther;
    int index;
    int otherIndex;

    float clamped = diff < -lbl_803EAFB0 ? -lbl_803EAFB0 : (diff > lbl_803EAFB0 ? lbl_803EAFB0 : diff);
    diff = (clamped + lbl_803EAFB0) / (lbl_803EAFB0 + lbl_803EAFB0);
    scale *= diff;
    if (scale < lbl_803EAFAC) {
        scale = lbl_803EAFAC;
    }
    switch (state->mUnknown67) {
    case 4:
    case 5:
    case 6:
        scale *= lbl_803EAFB4;
        if (scale > lbl_803EAFB8) {
            scale = lbl_803EAFB8;
        }
        break;
    }
    delta = MathAngleDiff(angle, p->mMotion.mFacing);
    if (((angle - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
        int limit = -(int)(scale * 46603.38f);

        delta = -delta;
        if (delta < limit) {
            delta = limit;
        }
    } else {
        int limit = (int)(scale * 46603.38f);

        if (delta > limit) {
            delta = limit;
        }
    }
    pOther = fn_8009BCE8(&state->mRef);
    index = AnimChanGetStateChannelByIndex(p->mpUnknown796, p->mpUnknown800, key, 0);
    otherIndex = AnimChanGetStateChannelByIndex(pOther->mpUnknown796, pOther->mpUnknown800, key, 0);
    if (otherIndex != 0xFFFF && index != 0xFFFF) {
        AnimChannel_t *pOtherRecord;
        Block_80114F64 *pBlock;
        Point_8017886C offset;
        Point_8017886C rotated;
        Point_8017886C target;
        Point_8017886C shift;

        p->mMotion.mFacing = (p->mMotion.mFacing + delta) & 0xFFFFFF;
        p->mpUnknown796->mUnknown8 = p->mMotion.mFacing;
        p->mpUnknown800[index].mUnknownC = (p->mpUnknown800[index].mUnknownC + delta) & 0xFFFFFF;
        pOtherRecord = &pOther->mpUnknown800[otherIndex];
        pBlock = (Block_80114F64 *)fn_801BE60C(pOther->mpUnknown792, key);
        if (pBlock->mUnknown28 == 0) {
            fn_80227690(&offset, &pOther->mMotion.mPos, &p->mMotion.mPos);
            fn_80227384(&rotated, &offset, delta);
            fn_80227638(&pOther->mMotion.mPos, &rotated, &p->mMotion.mPos);
            pOther->mMotion.mFacing = (pOther->mMotion.mFacing + delta) & 0xFFFFFF;
            pOtherRecord->mUnknownC = (pOtherRecord->mUnknownC + delta) & 0xFFFFFF;
        } else {
            fn_80227690(&target, &pBlock->mUnknown4, &p->mMotion.mPos);
            fn_80227384(&rotated, &target, delta);
            fn_80227690(&shift, &rotated, &target);
            fn_800DF134(pOther, shift, delta, key);
        }
    }
}

extern "C" float fn_80115248(Object_80039F5C *p, Object_80039F5C *pTarget, unsigned char kind)
{
    float score = 1.0f;
    float part = 0.0f;
    int found = 0;
    Object_80039F5C *pDefender = fn_800FB9D4(pTarget);
    Point_8017886C delta;
    Point_8017886C offset;
    unsigned char i;
    unsigned int count;
    int angle;

    if (pDefender != 0) {
        fn_80227690(&delta, &pDefender->mMotion.mPos, &pTarget->mMotion.mPos);
        if (fn_802270A4(&delta) < 5.0f && !(pDefender->mFlags & 0x20000)) {
            fn_80227690(&delta, &p->mMotion.mPos, &pTarget->mMotion.mPos);
            part = fn_802270A4(&delta) * 0.5f;
            if (part > 1.0f) {
                part = 1.0f;
            }
            found = 1;
            switch (pDefender->mUnknown2914) {
            case 13:
            case 14:
            case 15:
                part += part;
                break;
            }
        }
    }
    score += part;
    part = 0.0f;
    count = fn_80178D18(p->mIdBytes[2]);
    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther = PlyrGet(p->mIdBytes[2], i);
        float distance;

        fn_80227690(&delta, &pOther->mMotion.mPos, &pTarget->mMotion.mPos);
        distance = fn_802270A4(&delta);
        if (pOther != p) {
            fn_80227690(&delta, &pOther->mMotion.mPos, &pTarget->mMotion.mPos);
            switch (pOther->mpState->mId) {
            case 92:
                if (((State_80115248 *)&pOther->mUnknown336)->mpUnknown20 == pTarget &&
                    fn_80227890(&pOther->mMotion.mPos, &pTarget->mMotion.mPos) < 25.0f) {
                    found = 1;
                }
                break;
            case 40: {
                State_80115248 *pState = (State_80115248 *)&pOther->mUnknown336;

                fn_8009EAB0(pOther, fn_800C1180(pOther));
                if (fn_8009EF6C(pTarget) != 0) {
                    int side = pTarget->mMotion.mPos.mX - pOther->mMotion.mPos.mX >= 0.0f ? 0x800000 : 0;

                    if ((MathAngleDiff(pTarget->mMotion.mUnknown32, side) < 0x355555 &&
                         (MathAngleDiff(pOther->mMotion.mUnknown32, side) > 0x355555 ||
                          pState->mUnknown12 < 1.0f)) ||
                        distance < 7.0f) {
                        found = 1;
                    }
                }
                break;
            }
            case 85:
                if (distance < 2.5f) {
                    found = 1;
                }
                break;
            }
        } else if (fn_8009EF6C(pTarget) != 0) {
            int side = pTarget->mMotion.mPos.mX - p->mMotion.mPos.mX >= 0.0f ? 0x800000 : 0;

            if (MathAngleDiff(pTarget->mMotion.mUnknown32, side) < 0x355555) {
                found = 1;
            }
        }
    }
    if (found == 0) {
        part = 500.0f;
    }
    score += part;
    part = 0.0f;
    fn_8009EAB0(p, p->mpState->mUnknown1);
    if (fn_8009EC60(0, 0) == pTarget) {
        float dy = pTarget->mMotion.mPos.mY - fn_8009EC60(1, 0)->mMotion.mPos.mY;

        dy = dy < 4.0f ? 4.0f : (dy > part ? part : dy);
        part = dy;
    }
    score += part;
    part = 0.0f;
    angle = MathAngleDiff(pTarget->mMotion.mUnknown32, 0x400000);
    if (angle <= 0x1C71C6) {
        part = 40.0f - angle * 2.1457672e-05f;
        if (part > 4.0f) {
            part = 4.0f;
        }
    }
    if (part > 30.0f) {
        part = 30.0f;
    }
    score += part;
    if (pTarget->mMotion.mPos.mY > fn_80178A2C()) {
        fn_80227690(&offset, &pTarget->mMotion.mPos, &p->mMotion.mPos);
        score += fn_802270A4(&offset) * 4.0f;
    }
    return score;
}

extern "C" void fn_8011569C(Object_80039F5C *p)
{
    float bonus;
    Point_8017886C zone;
    Point_8017886C target;
    Point_8017886C ball;
    Point_8017886C spot;
    Vector_80039F5C ballPos;
    float xs[4];
    float weights[4];
    float total = 0.0f;
    float minX = 1000.0f;
    float maxX = -1000.0f;
    const float kAdvance = 4.0f;
    const float kCruise = 0.8f;
    const float kDepth = 10.0f;
    const float kSlow = 0.6f;
    const float kMargin = 2.0f;
    unsigned char numPlayers = 0;
    unsigned char numBelow = 0;
    unsigned char numAbove = 0;
    State_8011569C *pState = (State_8011569C *)&p->mUnknown336;
    signed char side;
    int count;

    bonus = 0.0f;
    zone.mX = 0.0f;
    zone.mY = 0.0f;
    target.mX = 0.0f;
    target.mY = 0.0f;
    ball.mX = 0.0f;
    ball.mY = 0.0f;
    spot.mX = 0.0f;
    spot.mY = 0.0f;
    ballPos.mX = 0.0f;
    ballPos.mY = 0.0f;
    ballPos.mZ = 0.0f;
    target.mX = 0.0f;
    target.mY = 0.0f;
    side = p->mpState->mUnknown1;
    count = fn_8009EAB0(p, side);
    fn_8009E9EC(p, side, &zone);
    Zone_8011569C *pZone = &((Field_8011569C *)fn_8011F4EC())->mZones[side];
    float low = pZone->mLow;
    float high = pZone->mHigh;
    ball = fn_80177FE0();
    BallGetPosition(BallGetCurrent(), &ballPos);
    if (count != 1) {
        pState->mUnknown17 = 0;
    }
    fn_80116AB8(p);

    if (count == 0) {
        unsigned char i;
        for (i = 0; i < 3; i++) {
            int index = PlayBookGetReceiver(fn_80178308(), i, 0);
            if (index != 0xFF) {
                numPlayers++;
                Object_80039F5C *pOther = PlyrGet(fn_80178308(), index);
                if (pOther->mMotion.mPos.mX > high) {
                    numAbove++;
                } else if (pOther->mMotion.mPos.mX < low) {
                    numBelow++;
                }
                if (pOther->mMotion.mPos.mX < minX) {
                    minX = pOther->mMotion.mPos.mX;
                }
                if (pOther->mMotion.mPos.mX > maxX) {
                    maxX = pOther->mMotion.mPos.mX;
                }
            }
        }
        if (numPlayers == 0) {
            minX = -7.0f;
            maxX = 7.0f;
        }
        if (numPlayers != 0 && numBelow == numPlayers) {
            target.mX = low;
        } else if (numPlayers != 0 && numAbove == numPlayers) {
            target.mX = high;
        } else {
            float x;
            if (fn_8009EFDC(side) != 0) {
                if (zone.mX < fn_80177FE0().mX) {
                    x = minX < zone.mX ? zone.mX : minX;
                } else {
                    x = maxX > zone.mX ? zone.mX : maxX;
                }
            } else {
                x = zone.mX;
            }
            target.mX = x;
        }
        target.mY = ball.mY + kDepth;
        pState->mUnknown12 = kSlow;
        fn_80116410(p, 0, pState, &target);
        if (ball.mY > fn_80178A2C() - 5.0f) {
            Object_80039F5C *pCarrier = BallGetCurrentHolder();
            if (pCarrier != 0 && (pCarrier->mFlags & 0x8000)
                && ((pCarrier->mMotion.mPos.mX < ball.mX && p->mMotion.mPos.mX < ball.mX)
                    || (pCarrier->mMotion.mPos.mX > ball.mX && p->mMotion.mPos.mX > ball.mX))) {
                float gap = ball.mY - pCarrier->mMotion.mPos.mY;
                int a = fn_800DC21C(pCarrier);
                int b = PlayerActionAnimIsPassReady(pCarrier);
                if ((a != 0 || b != 0 || fn_801783AC(0) != 0) && gap < 8.0f) {
                    pState->mUnknown20 = 1;
                }
            }
        }
    } else {
        if (count == 1) {
            Object_80039F5C *pOther = fn_8009EC60(0, &spot);
            int covered = 0;
            int handled = 0;

            if (pOther->mpState->mId != 20) {
                pState->mUnknown17 = 0;
            } else if (pState->mUnknown17 == 0) {
                pState->mUnknown17 = fn_8009FD7C(p, pOther);
            }
            fn_8009F928(pOther, &spot, 12, pState->mUnknown17);
            float range;
            if (MathAngleDiff(pOther->mMotion.mUnknown32, 0x400000) <= 0x155554
                || MathAngleDiff(pOther->mMotion.mUnknown32, 0xC00000) <= 0x155554) {
                range = 1.5f;
            } else {
                range = 6.0f;
            }
            fn_80116880(p, pOther, &spot.mX, &target.mX, range);
            Object_80039F5C *pMark = fn_800FB9D4(pOther);
            if (pMark != 0) {
                Point_8017886C delta;
                fn_80227690(&delta, &pMark->mMotion.mPos, &pOther->mMotion.mPos);
                if (fn_802270A4(&delta) < 5.0f && !(pMark->mFlags & 0x20000)) {
                    covered = 1;
                }
            }
            if (covered == 0 && fn_801167C4(pOther, p) != 0) {
                covered = 1;
            }
            if (covered != 0) {
                handled = fn_80116410(p, pOther, pState, &target);
                if (target.mY < pOther->mMotion.mPos.mY) {
                    handled = 0;
                }
            }
            if (handled == 0) {
                Point_8017886C delta;
                float dy = pOther->mMotion.mPos.mY - p->mMotion.mPos.mY;
                fn_80227690(&delta, &spot, &p->mMotion.mPos);
                float dist = fn_802270A4(&delta);
                float dx = fabsf(spot.mX - p->mMotion.mPos.mX);
                dx *= fn_801CFB18(pOther->mMotion.mUnknown32);
                if (dx < 0.0f) {
                    dx = 0.0f;
                }
                dx *= 0.75f;
                int ahead = fn_80116984(p, pOther, &bonus);
                dx += bonus;
                target.mY = pOther->mMotion.mUnknown44 * 60.0f * lbl_803EAFCC + spot.mY + kMargin + dx;
                if (target.mY < p->mMotion.mPos.mY
                    && MathAngleDiff(pOther->mMotion.mUnknown32, 0x400000) <= 0x155554
                    && spot.mY > p->mMotion.mPos.mY - lbl_803EAFBC) {
                    target.mY = p->mMotion.mPos.mY + kMargin;
                }
                if (ahead != 0) {
                    pState->mUnknown12 = 1.0f;
                } else if (dy > -2.0f) {
                    pState->mUnknown12 = p->mMotion.mPos.mY < spot.mY + 5.0f ? 1.0f : kCruise;
                } else if (dy > -5.0f && dist > 8.0f) {
                    pState->mUnknown12 = 1.0f;
                } else if (dy > -7.0f) {
                    pState->mUnknown12 = dist > 12.0f ? 1.0f : kSlow;
                } else {
                    int moving = 1;
                    if ((short)fn_8011F4E0()->mUnknown2 < 0
                        && (pOther->mMotion.mUnknown44 <= fabsf(pOther->mMotion.mUnknown40) * 2.0f / 3.0f
                            || pOther->mMotion.mUnknown44 <= gPlyrMoveBaseSpeed * 0.25f)) {
                        moving = 0;
                    }
                    if (moving == 1) {
                        target.mY = p->mMotion.mPos.mY;
                        pState->mUnknown12 = 0.4f;
                    } else {
                        pState->mUnknown12 = kSlow;
                    }
                }
            }
            if (p->mMotion.mPos.mY > fn_80178A2C()) {
                if (fabsf(target.mX - p->mMotion.mPos.mX) > 1.0f) {
                    pState->mUnknown12 = 1.0f;
                } else if (pState->mUnknown12 != 1.0f) {
                    pState->mUnknown12 = kCruise;
                }
            } else if (pState->mUnknown12 < kCruise && fabsf(target.mX - p->mMotion.mPos.mX) > kMargin) {
                pState->mUnknown12 = kCruise;
            }
        } else {
            Object_80039F5C *pOther = 0;
            unsigned int i;

            for (i = 0; i < count; i++) {
                Point_8017886C pos;
                weights[i] = fn_80115248(p, fn_8009EC60(i, &pos), count);
                xs[i] = pos.mX;
                if (xs[i] > maxX) {
                    maxX = xs[i];
                }
                if (xs[i] < minX) {
                    minX = xs[i];
                }
            }
            for (i = 0; i < count; i++) {
                total += weights[i];
            }
            for (i = 0; i < count; i++) {
                pOther = fn_8009EC60(i, &spot);
                if (weights[i] / total < kCruise || weights[i] < 500.0f) {
                    pOther = 0;
                } else {
                    break;
                }
            }
            Object_80039F5C *pLeader = pOther;
            if (pOther == 0) {
                pOther = fn_8009EC60(0, &spot);
            }
            if (pLeader == 0) {
                float halfSpread = (maxX - minX) * 0.5f;
                target.mX = halfSpread;
                for (i = 0; i < count; i++) {
                    target.mX += (xs[i] - halfSpread) * (weights[i] / total);
                }
            } else {
                fn_80116880(p, pOther, &spot.mX, &target.mX, 1.5f);
            }
            float dx = fabsf(spot.mX - p->mMotion.mPos.mX);
            dx *= fn_801CFB18(pOther->mMotion.mUnknown32);
            if (dx < 0.0f) {
                dx = 0.0f;
            }
            dx *= 0.75f;
            int ahead = fn_80116984(p, pOther, &bonus);
            dx += bonus;
            target.mY = pOther->mMotion.mUnknown44 * 60.0f * lbl_803EAFCC + spot.mY + kMargin + dx;
            int angle = MathAngleDiff(pOther->mMotion.mUnknown32, 0x400000);
            if (target.mY < p->mMotion.mPos.mY && angle <= 0x155554
                && spot.mY > p->mMotion.mPos.mY - lbl_803EAFBC) {
                target.mY = p->mMotion.mPos.mY + kMargin;
            }
            float dy = target.mY - p->mMotion.mPos.mY;
            if (ahead != 0) {
                pState->mUnknown12 = 1.0f;
            } else if (angle <= 0x2E38E2) {
                if (dy > kMargin) {
                    if (p->mMotion.mPos.mY < pOther->mMotion.mPos.mY + kMargin
                        && p->mMotion.mPos.mY < fn_80178A2C()) {
                        pState->mUnknown12 = 1.0f;
                    } else {
                        pState->mUnknown12 = kCruise;
                    }
                } else if (dy > -2.0f) {
                    if (pOther->mMotion.mUnknown44 > fabsf(pOther->mMotion.mUnknown40) * 2.0f / 3.0f
                        && pOther->mMotion.mUnknown44 > gPlyrMoveBaseSpeed * 0.25f) {
                        pState->mUnknown12 = kSlow;
                    } else {
                        pState->mUnknown12 = 0.4f;
                    }
                } else {
                    pState->mUnknown12 = 0.4f;
                }
            } else if (dy <= 0.0f && dy > -2.0f) {
                pState->mUnknown12 = 1.0f;
            } else {
                pState->mUnknown12 = kCruise;
            }
            if (p->mMotion.mPos.mY > fn_80178A2C()) {
                if (fabsf(target.mX - p->mMotion.mPos.mX) > 1.0f) {
                    pState->mUnknown12 = 1.0f;
                } else if (pState->mUnknown12 != 1.0f) {
                    pState->mUnknown12 = kCruise;
                }
            } else if (pState->mUnknown12 < kCruise && fabsf(target.mX - p->mMotion.mPos.mX) > kMargin) {
                pState->mUnknown12 = kCruise;
            }
        }
    }

    target.mX = target.mX < low + kMargin ? low + kMargin : (target.mX > high - kMargin ? high - kMargin : target.mX);
    if (p->mMotion.mPos.mY > fn_80178A44() - 6.0f - 1.0f) {
        pState->mUnknown12 = kCruise;
    }
    target.mY = target.mY > fn_80178A44() - 6.0f ? fn_80178A44() - 6.0f : target.mY;
    switch (fn_8009E9A4()) {
    case 1:
        target.mY += kAdvance;
        break;
    case 2:
        target.mY -= 1.0f;
        break;
    }
    fn_80227690(&target, &target, &p->mMotion.mPos);
    pState->mUnknown8 = fn_801CFE40(target.mY, target.mX);
    if (fn_802270A4(&target) < 1.0f) {
        pState->mUnknown4 = 0xC00000;
        pState->mUnknown12 = 0.0f;
    }
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

/* Picks a spot past a teammate in a neighbouring slot to run to. */




extern "C" int fn_80116410(Object_80039F5C *p, Object_80039F5C *pOther, State_8011569C *pState, Point_8017886C *pTarget) {
    float best = -1000.0f;
    float extra = 0.0f;
    Object_80039F5C *pBest = 0;
    int i = 0;
    int found = 0;
    int result = 0;
    int slots[24];
    unsigned int count;
    unsigned int j;
    unsigned int k;
    int ok;
    Object_80039F5C *pMate;
    Object_80039F5C *pGuard;
    Object_80039F5C *q;
    Record_8011F4E0 *pRecord;
    Object_80039F5C *pCover;
    Object_80039F5C *pMark;
    Point_8017886C spot;
    Point_8017886C apart;
    int near;

    if (p && pTarget) {
        switch (p->mpState->mUnknown1) {
        case 3:
        case 5:
            slots[0] = 4;
            slots[1] = 24;
            break;
        case 4:
            slots[0] = 3;
            slots[1] = 5;
            slots[2] = 24;
            break;
        case 6:
            slots[0] = 7;
            slots[1] = 24;
            break;
        case 7:
            slots[0] = 6;
            slots[1] = 8;
            slots[2] = 24;
            break;
        case 8:
            slots[0] = 7;
            slots[1] = 9;
            slots[2] = 24;
            break;
        case 9:
            slots[0] = 8;
            slots[1] = 24;
            break;
        case 1:
            slots[0] = 2;
            slots[1] = 24;
            break;
        case 2:
            slots[0] = 1;
            slots[1] = 24;
            break;
        case 0:
        default:
            slots[0] = 24;
            break;
        }
        count = fn_80178D18(p->mIdBytes[2]);
        for (; slots[i] != 24; i++) {
            for (j = 0; j < count; j++) {
                pMate = PlyrGet(p->mIdBytes[2], j);
                if (pMate != p && pMate->mpState->mId == 40 && pMate->mpState->mUnknown1 == slots[i]) {
                    fn_8009EAB0(pMate, pMate->mpState->mUnknown1);
                    pCover = fn_8009EC60(0, &spot);
                    if (pCover && spot.mY > best) {
                        ok = 0;
                        pGuard = fn_800FB9D4(pCover);
                        if (pGuard) {
                            fn_80227690(&apart, &pGuard->mMotion.mPos, &pCover->mMotion.mPos);
                            ok = fn_802270A4(&apart) < 5.0f;
                        } else if (pOther != pCover) {
                            if (!pOther) {
                                ok = 1;
                            } else if (pCover->mMotion.mPos.mY > pOther->mMotion.mPos.mY + 2.0f) {
                                ok = 1;
                            }
                        }
                        if (ok) {
                            pBest = pCover;
                            best = spot.mY;
                            found = 1;
                        }
                    }
                    break;
                }
            }
        }
        if (found) {
            near = fn_80116984(p, pBest, &extra);
            best += extra;
            if (best + 2.0f > p->mMotion.mPos.mY) {
                pTarget->mY = best + 2.0f;
                pState->mUnknown12 = near ? 1.0f : 0.8f;
                result = 1;
            } else {
                pTarget->mY = p->mMotion.mPos.mY;
                pState->mUnknown4 = 0xC00000;
                result = 1;
                pState->mUnknown12 = 0.0f;
            }
        } else {
            for (k = 0; k <= 2; k++) {
                pRecord = fn_8011F4E0();
                q = PlyrGet(fn_80178308(), pRecord->mUnknown8[k]);
                if (q) {
                    pMark = fn_800FB9D4(q);
                    if (pMark && (fn_8022781C(&pMark->mMotion.mPos, &q->mMotion.mPos) > 5.0f || (pMark->mFlags & 0x20000)) &&
                        pMark->mMotion.mPos.mY < q->mMotion.mPos.mY) {
                        pTarget->mX = q->mMotion.mPos.mX;
                        result = 1;
                        break;
                    }
                }
            }
        }
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
            Object_80039F5C *pOther = PlyrGet(p->mIdBytes[2], i);
            if (pOther != p) {
                unsigned char id = pOther->mpState->mId;
                if (id == 40 || id == 92) {
                    fn_8009EAB0(pOther, (unsigned char)fn_800C1180(pOther));
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
            MathAngleDiff(pOther->mMotion.mUnknown32, p->mMotion.mUnknown32);
            if (MathAngleDiff(pOther->mMotion.mUnknown32, 0) <= limit) {
                pending = 0;
                *pOut = *pValue + range;
            } else if (MathAngleDiff(pOther->mMotion.mUnknown32, 0x800000) <= limit) {
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

extern "C" int fn_80116984(Object_80039F5C *p, Object_80039F5C *pOther, float *pOut)
{
    int result = 0;

    if (p != 0 && pOther != 0 && pOut != 0) {
        *pOut = 0.0f;
        if (pOther->mRatings[4] > p->mRatings[4]) {
            unsigned int diff = (unsigned int)(pOther->mRatings[4] * 0.38823533f - p->mRatings[4] * 0.38823533f);
            float value = diff;

            *pOut = value * lbl_803EAFC0;
            if (value > lbl_803EAFC4 && fabsf(pOther->mMotion.mPos.mY - p->mMotion.mPos.mY) < lbl_803EAFC8) {
                result = 1;
            }
        }
    }
    return result;
}

/* Discarded by SN's linker: only its pool (10.0f and 5.0f at 0x8029F040) survives in .rodata. */
// FAKEMATCH: invented body; only its pool constant(s) are target evidence
extern "C" {
static float _StrippedScaleTenPlusFive(float x)
{
    return x * 10.0f + 5.0f;
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
                Object_80039F5C *pOther = PlyrGet(p->mIdBytes[2], i);
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

extern "C" {
int fn_80116B98(Object_80039F5C *p)
{
    Block_80116B98 *pBlock = (Block_80116B98 *)&p->mUnknown336;

    pBlock->mUnknown2 = 0;
    pBlock->mUnknown0 = 0;
    pBlock->mUnknown20 = 0;
    pBlock->mUnknown8 = 0;
    pBlock->mUnknown4 = 0xC00000;
    pBlock->mUnknown12 = 0.0f;
    if (fn_8011F1A4()) {
        pBlock->mUnknown16 = 1;
        pBlock->mUnknown18 = p->mRatings[5] <= 255 ? 255 - p->mRatings[5] : 0;
    } else {
        pBlock->mUnknown16 = 0;
        pBlock->mUnknown18 = 0;
    }
    return 0;
}
}

extern "C" {
int fn_80116C34(Object_80039F5C *p)
{
    fn_8010A2DC(p, 0, -1);
    State_80116C34 *state = (State_80116C34 *)&p->mUnknown336;
    int update = 0;
    state->mUnknown0++;
    state->mUnknown2 = (signed char)(state->mUnknown2 - 1);
    if (state->mUnknown2 < 0) {
        int limit = 255 - p->mRatings[8];
        if (limit < 0) limit = 0;
        update = 1;
        int base = fn_800AC2C0(p->mIdBytes[2]);
        state->mUnknown2 = (signed char)(state->mUnknown2 + base + fn_802372EC(0, (unsigned int)limit >> 5));
        state->mUnknown2 = fn_8009AF00(p->mIdBytes[2], (signed char)state->mUnknown2);
    }
    if (state->mUnknown16 && state->mUnknown0 >= state->mUnknown18) update = 1;
    if (!(p->mFlags & 0x4000) && update) {
        if (fn_801163B4(p)) return 1;
        if (!state->mUnknown16 || state->mUnknown0 < state->mUnknown18) {
            state->mUnknown21 = 0;
            fn_8011569C(p);
            if (state->mUnknown12 == 1.0f) {
                state->mUnknown4 = state->mUnknown8;
                if (MathAngleDiff(p->mMotion.mFacing, state->mUnknown8) <= 0xE38E2 &&
                    MathAngleDiff(p->mMotion.mUnknown32, state->mUnknown8) <= 0xE38E2) {
                    state->mUnknown21 = 1;
                }
            } else {
                state->mUnknown4 = 0xC00000;
            }
            if (state->mUnknown16) state->mUnknown12 *= 0.5f;
        } else {
            state->mUnknown4 = state->mUnknown8;
            state->mUnknown12 = 0.0f;
            state->mUnknown8 = p->mMotion.mFacing;
        }
    }
    if (!fn_800A5C04(p, state->mUnknown8, state->mUnknown4) && !(p->mFlags & 0x4000)) {
        if (update) {
            int kind = fn_8009E180(p);
            if (state->mUnknown20) kind = 5;
            if (kind > 2) {
                Message_800F01CC message;
                Vector_80039F5C target;
                if (kind != 4) {
                    unsigned short odds = p->mRatings[8] >> 1;
                    if (fn_800B65A0(p->mIdBytes[2]) == 255) {
                        odds += (int)(odds * PlayTrackGetPlayIdRate());
                    }
                    Vector_80039F5C ball;
                    BallGetPosition(BallGetCurrent(), &ball);
                    if (fn_802372EC(0, 255) < odds || IsBallAway(ball)) {
                        memset(&message, 0, 4);
                        message.mId = 2;
                        fn_800F053C(0, p->mpState, &message, p);
                        return 1;
                    }
                } else {
                    BallGetLandingPoint(BallGetCurrent(), &target);
                    if (fn_8009F258(p)) {
                        memset(&message, 0, 4);
                        message.mId = 24;
                        if (!BallGetTarget(BallGetCurrent())) {
                            message.mUnknown1[0] = 0;
                        } else if (fabsf(target.mX - p->mMotion.mPos.mX) < 10.0f || fn_802372EC(0, 100) <= 49) {
                            message.mUnknown1[0] = 2;
                        } else {
                            message.mUnknown1[0] = 1;
                        }
                        fn_800F053C(0, p->mpState, &message, p);
                        return 0;
                    }
                }
            }
        }
        if (state->mUnknown12 != 0.0f) {
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown4 = state->mUnknown8;
            p->mUnknown512.mUnknown8 = state->mUnknown4;
            p->mUnknown512.mUnknown0 = state->mUnknown12;
        } else if (MathAngleDiff(p->mMotion.mFacing, state->mUnknown4) > 0x71C71) {
            p->mUnknown512.mUnknown14 = 3;
            p->mUnknown512.mUnknown4 = (state->mUnknown4 + 0x800000) & 0xFFFFFF;
            p->mUnknown512.mUnknown8 = state->mUnknown4;
            p->mUnknown512.mUnknown0 = 0.5f;
        }
        p->mUnknown512.mUnknown15 = state->mUnknown21;
    }
    return 0;
}
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

extern "C" {
int fn_801170E8(Object_80039F5C *p)
{
    unsigned char side = p->mpState->mUnknown1 + 14;
    int found = 0;
    int result = 0;
    int beyond = 0;
    int blocked;
    unsigned int count = fn_80178D70(fn_80178320());
    for (unsigned char i = 0; i < count && !found; i++) {
        if (PlyrGet(fn_80178320(), i)->mpState->mId == 85) found = 1;
    }
    Point_8017886C origin;
    origin = fn_80177FE0();
    for (unsigned char i = 0; i <= 2; i++) {
        int index = PlayBookGetReceiver(fn_80178308(), i, 0);
        if (index == 255) continue;
        Object_80039F5C *other = PlyrGet(fn_80178308(), (unsigned short)index);
        if (!other) continue;
        switch (side) {
        case 15: case 17: case 20:
            if (!(other->mMotion.mPos.mX >= origin.mX)) {
                fn_8011E9D8(other->mpState);
                if (other->mMotion.mPos.mY < origin.mY + 4.0f && (other->mFlags & 0x800)) blocked = 1;
            }
            break;
        case 16: case 19: case 23:
            if (!(other->mMotion.mPos.mX <= origin.mX)) {
                fn_8011E9D8(other->mpState);
                if (other->mMotion.mPos.mY < origin.mY + 4.0f && (other->mFlags & 0x800)) blocked = 1;
            }
            break;
        }
    }
    Object_80039F5C *carrier = BallGetCurrentHolder();
    if (carrier) {
        switch (side) {
        case 15: case 17: case 20:
            if (!(carrier->mMotion.mPos.mX >= origin.mX)) beyond = 1;
            break;
        case 16: case 19: case 23:
            if (!(carrier->mMotion.mPos.mX <= origin.mX)) beyond = 1;
            break;
        }
    }
    if (carrier) {
        float ratio = carrier->mMotion.mUnknown28 / carrier->mMotion.mUnknown36;
        float speed = ratio < 0.0 ? 0.0f : (float)(ratio <= 1.0 ? ratio : 1.0);
        float proximity = 1.0f - fabsf(carrier->mMotion.mPos.mY - origin.mY) * 0.16666667f;
        float position = proximity < 0.0 ? 0.0f : (float)(proximity <= 1.0 ? proximity : 1.0);
        float score = speed * 0.6f + position * 0.4f;
        if (!(score <= 0.7f) && beyond) {
            blocked = 0;
            result = 1;
        } else blocked = 1;
    } else {
        blocked = 0;
        result = 1;
    }
    if (fn_801783AC(0) || fn_8009E180(p) == 5) result = 1;
    else if (found || blocked) result = 0;
    if (result) {
        Message_800F01CC message;
        memset(&message, 0, 4);
        message.mId = 2;
        fn_800F053C(0, p->mpState, &message, p);
        *lbl_803EC9F0 = 1;
    }
    return result;
}
}

extern "C" {
int fn_80117494(Object_80039F5C *p, Point_8017886C *out)
{
    State_80116C34 *state = (State_80116C34 *)&p->mUnknown336;
    int result = 0;
    unsigned char side = p->mpState->mUnknown1 + 14;
    float centerX = fn_80177FE0().mX;
    float centerY = fn_80177FE0().mY;
    out->mX = p->mMotion.mPos.mX;
    out->mY = p->mMotion.mPos.mY;
    Object_80039F5C *carrier = BallGetCurrentHolder();
    if (carrier && (carrier->mFlags & 0x8000) &&
        ((!(carrier->mMotion.mPos.mX >= centerX) && p->mMotion.mPos.mX < centerX) ||
         (!(carrier->mMotion.mPos.mX <= centerX) && !(p->mMotion.mPos.mX <= centerX)))) {
        float distance = centerY - carrier->mMotion.mPos.mY;
        if (!(distance >= lbl_803EAFE8) &&
            (carrier->mMotion.mUnknown32 & 0xFFFFFF) <= 0x7FFFFF) {
            int first = fn_800DC21C(carrier);
            int second = PlayerActionAnimIsPassReady(carrier);
            if (first || second || fn_801783AC(0)) {
                if (fn_801783AC(7) == 1 || fn_801783AC(8) == 1) state->mUnknown24 = 1;
                if (!(distance >= lbl_803EAFEC)) {
                    float half = lbl_803EAFF0 * 0.5f;
                    out->mY = half * (distance / lbl_803EAFEC) + centerY;
                    float threshold = PlayTrackGetResult5Rate() * lbl_803EAFF8 + lbl_803EAFF4;
                    if (!(distance >= threshold) && carrier->mUnknown8 != 255) state->mUnknown24 = 1;
                    result = 1;
                }
                if (!(fabsf(carrier->mMotion.mPos.mX) <= fabsf(p->mMotion.mPos.mX))) {
                    state->mUnknown12 = 0.8f;
                    distance = fabsf(carrier->mMotion.mPos.mX - p->mMotion.mPos.mX);
                    if (!(distance <= lbl_803EAFFC)) {
                        if (fn_8009EFDC(side) == -1) {
                            out->mX = carrier->mMotion.mPos.mX - 1.5f;
                            if (first && MathAngleDiff(carrier->mMotion.mUnknown32, 0x638E39) <= 0x1C71C6) state->mUnknown12 = 0.8f;
                        } else {
                            out->mX = carrier->mMotion.mPos.mX + 1.5f;
                            if (first && MathAngleDiff(carrier->mMotion.mUnknown32, 0x1C71C7) <= 0x1C71C6) state->mUnknown12 = 0.8f;
                        }
                        result = 1;
                    }
                }
                if (!(fabsf(p->mMotion.mPos.mX - centerX) <= 5.0f) &&
                    !(p->mMotion.mPos.mY <= fn_80178A2C()) &&
                    !(distance >= lbl_803EB000)) state->mUnknown24 = 1;
            }
        }
    }
    if (state->mUnknown24) result = 1;
    if (*lbl_803EC9F0) result = 0;
    return result;
}
}

extern "C" Object_80039F5C *fn_80117794(int index)
{
    Object_80039F5C *pBest = 0;
    float bestX = 0.0f;
    unsigned char i = 0;
    Record_80117934 *pRecord = (Record_80117934 *)fn_8011F4EC();

    for (; i < pRecord->mUnknown408; i++) {
        Object_80039F5C *p = PlyrGet(fn_80178308(), pRecord->mUnknown409[i]);
        int covered = 0;
        Object_80039F5C *pOther = fn_800FB9D4(p);

        if (pOther != 0) {
            covered = fn_80227890(&pOther->mMotion.mPos, &p->mMotion.mPos) < lbl_803EAFE4;
        }
        if (!covered) {
            unsigned char j = 0;
            unsigned int count = fn_80178D18(fn_80178320());

            for (; j < count; j++) {
                Object_80039F5C *pDefender = PlyrGet(fn_80178320(), j);
                State_80039F5C *pState = pDefender->mpState;

                if (pState->mId == 40) {
                    fn_8009EAB0(pDefender, pState->mUnknown1);
                    if (fn_8009EF6C(p) && fn_80227890(&p->mMotion.mPos, &pDefender->mMotion.mPos) < lbl_803EAFE4) {
                        covered = 1;
                    }
                } else if (pState->mId == 92 && ((Block_80117934 *)&pDefender->mUnknown336)->mpUnknown20 == p
                           && fn_80227890(&p->mMotion.mPos, &pDefender->mMotion.mPos) < lbl_803EAFE4) {
                    covered = 1;
                }
            }
            /* Both direction tests compare against -1 and keep the smaller x
               in the target (0x801178CC and 0x801178E8). */
            if (!covered
                && (pBest == 0 || (fn_8009EFDC(index) == -1 && p->mMotion.mPos.mX < bestX)
                    || (fn_8009EFDC(index) == -1 && p->mMotion.mPos.mX < bestX))) {
                pBest = p;
                bestX = pBest->mMotion.mPos.mX;
            }
        }
    }
    return pBest;
}

extern "C" Object_80039F5C *fn_80117934(void)
{
    Object_80039F5C *pBest = 0;
    float bestY = 0.0f;
    unsigned char i = 0;
    Record_80117934 *pRecord = (Record_80117934 *)fn_8011F4EC();

    for (; i < pRecord->mUnknown408; i++) {
        Object_80039F5C *p = PlyrGet(fn_80178308(), pRecord->mUnknown409[i]);
        int covered = 0;
        Object_80039F5C *pOther = fn_800FB9D4(p);

        if (pOther != 0) {
            covered = fn_80227890(&pOther->mMotion.mPos, &p->mMotion.mPos) < lbl_803EAFE4;
        }
        if (!covered) {
            unsigned char j = 0;
            unsigned int count = fn_80178D18(fn_80178320());

            for (; j < count; j++) {
                Object_80039F5C *pDefender = PlyrGet(fn_80178320(), j);
                State_80039F5C *pState = pDefender->mpState;

                if (pState->mId == 40) {
                    fn_8009EAB0(pDefender, pState->mUnknown1);
                    if (fn_8009EF6C(p) && fn_80227890(&p->mMotion.mPos, &pDefender->mMotion.mPos) < lbl_803EAFE4) {
                        covered = 1;
                    }
                } else if (pState->mId == 92 && ((Block_80117934 *)&pDefender->mUnknown336)->mpUnknown20 == p
                           && fn_80227890(&p->mMotion.mPos, &pDefender->mMotion.mPos) < lbl_803EAFE4) {
                    covered = 1;
                }
            }
            if (!covered && (pBest == 0 || p->mMotion.mPos.mY > bestY)) {
                pBest = p;
                bestY = pBest->mMotion.mPos.mY;
            }
        }
    }
    return pBest;
}

extern "C" void fn_80117AA4(Object_80039F5C *p, Point_8017886C *pOut, float *pSpeed)
{
    float high = 0.0f;
    float low = 0.0f;
    float top = 0.0f;
    float bottom = 0.0f;
    float speed = 0.6f;
    State_80117AA4 *pState = (State_80117AA4 *)&p->mUnknown336;
    Point_8017886C zone;
    unsigned char numPlayers = 0;
    unsigned char numBelow = 0;
    unsigned char numAbove = 0;
    Object_80039F5C *pOther = 0;
    Object_80039F5C *pMark;
    unsigned char side;
    int count;

    fn_80177FE0();
    side = p->mpState->mUnknown1 + 14;
    fn_8009E9EC(p, side, &zone);
    Zone_8011569C *pZone = &((Field_8011569C *)fn_8011F4EC())->mZones[side];
    high = pZone->mHigh;
    low = pZone->mLow;
    top = pZone->mUnknown0;
    bottom = pZone->mUnknown4;
    pOut->mX = p->mMotion.mPos.mX;
    pOut->mY = p->mMotion.mPos.mY;
    if (p == 0 || pOut == 0) return;

    count = fn_8009EAB0(p, side);
    if (count != 1) {
        pState->mUnknown17 = 0;
    }
    if (count == 0) {
        pState->mpUnknown20 = 0;
        if (!fn_80117494(p, pOut)) {
            if (fn_8009EFDC(side) || lbl_803EB010) {
                if (fn_8009EFDC(side)) {
                    pMark = fn_80117794(side);
                } else {
                    pMark = fn_80117934();
                }
                if (pMark) {
                    if (fn_8009EFDC(side)) {
                        pOut->mX = pMark->mMotion.mPos.mX;
                    } else {
                        pOut->mX = zone.mX;
                    }
                    pOut->mY = pMark->mMotion.mPos.mY >= zone.mY ? pMark->mMotion.mPos.mY : zone.mY;
                } else {
                    float minX = 100.0f;
                    float maxX = -100.0f;
                    unsigned char i;
                    for (i = 0; i <= 2; i++) {
                        int index = PlayBookGetReceiver(fn_80178308(), i, 0);
                        if (index != 0xFF) {
                            numPlayers++;
                            pMark = PlyrGet(fn_80178308(), index);
                            if (pMark->mMotion.mPos.mX > high) {
                                numAbove++;
                            } else if (pMark->mMotion.mPos.mX < low) {
                                numBelow++;
                            }
                            if (pMark->mMotion.mPos.mX < minX) {
                                minX = pMark->mMotion.mPos.mX;
                            }
                            if (pMark->mMotion.mPos.mX < maxX) {
                                maxX = pMark->mMotion.mPos.mX;
                            }
                        }
                    }
                    if (numPlayers == 0) {
                        minX = -7.0f;
                        maxX = 7.0f;
                    }
                    if (numPlayers != 0 && numBelow == numPlayers) {
                        pOut->mX = low + lbl_803EAFD8;
                    } else if (numPlayers != 0 && numAbove == numPlayers) {
                        pOut->mX = high - lbl_803EAFD8;
                    } else if (fn_8009EFDC(side)) {
                        if (zone.mX < fn_80177FE0().mX) {
                            pOut->mX = minX;
                        } else {
                            pOut->mX = maxX;
                        }
                    } else {
                        pOut->mX = zone.mX;
                    }
                    pOut->mY = zone.mY;
                }
            } else {
                pOut->mX = zone.mX;
                pOut->mY = zone.mY;
            }
            speed = 0.6f;
        }
        pOut->mX = pOut->mX < low + lbl_803EAFD8 ? low + lbl_803EAFD8
                 : (pOut->mX > high - lbl_803EAFD8 ? high - lbl_803EAFD8 : pOut->mX);
        pOut->mY = pOut->mY < bottom + lbl_803EAFD4 ? bottom + lbl_803EAFD4
                 : (pOut->mY > top - lbl_803EAFD4 ? top - lbl_803EAFD4 : pOut->mY);
    } else {
        if (!fn_8009EFDC(side)) {
            pOther = fn_8009EC60(0, pOut);
        } else {
            pOther = fn_8009EDD4(0, side, pOut);
        }
        if (pOther->mpState->mId != 20) {
            pState->mUnknown17 = 0;
        } else if (pState->mUnknown17 == 0) {
            pState->mUnknown17 = fn_8009FD7C(p, pOther);
        }
        fn_8009F928(pOther, pOut, 30, pState->mUnknown17);
        if (fn_8009EFDC(side)) {
            if (zone.mX < fn_80177FE0().mX) {
                pOut->mX += 1.0f;
            } else {
                pOut->mX -= 1.0f;
            }
        }
        Point_8017886C delta;
        fn_80227690(&delta, &p->mMotion.mPos, pOut);
        if (MathAngleDiff(delta.Heading(), pOther->mMotion.mUnknown32) <= (int)(lbl_803EAFE0 * 46603.38f)) {
            if (delta.mY > 0.0f) {
                pOut->mY = p->mMotion.mPos.mY;
                if (fn_80227890(&p->mMotion.mPos, pOut) < lbl_803EAFDC) {
                    pOut->mY += 2.0f;
                }
                speed = 0.8f;
            } else {
                pOut->mX = p->mMotion.mPos.mX;
                speed = 0.8f;
            }
        } else {
            speed = 0.8f;
        }
        pOut->mX = pOut->mX < low + lbl_803EAFD8 ? low + lbl_803EAFD8
                 : (pOut->mX > high - lbl_803EAFD8 ? high - lbl_803EAFD8 : pOut->mX);
        pOut->mY = pOut->mY < bottom + lbl_803EAFD4 ? bottom + lbl_803EAFD4
                 : (pOut->mY > top - lbl_803EAFD4 ? top - lbl_803EAFD4 : pOut->mY);
    }
    if (pOut->mY > fn_80178A2C() + lbl_803EAFD0) {
        pOut->mY = fn_80178A2C() + lbl_803EAFD0;
    }
    if (fabsf(p->mMotion.mPos.mX) < 4.0f) {
        pOut->mY = pOut->mY < zone.mY ? zone.mY : pOut->mY;
    }
    if (p->mMotion.mPos.mX <= low || p->mMotion.mPos.mX >= high
        || p->mMotion.mPos.mY <= bottom || p->mMotion.mPos.mY >= top) {
        speed = 1.0f;
    }
    if (pSpeed) {
        *pSpeed = speed;
    }
    pState->mpUnknown20 = pOther;
}

extern "C" void fn_801180FC(Object_80039F5C *p)
{
    Block_801180FC *pBlock;
    Point_8017886C origin;
    Point_8017886C spot;
    Point_8017886C target;
    float dx = 0.0f;
    float dy = 0.0f;

    fn_80178308();
    pBlock = (Block_801180FC *)&p->mUnknown336;
    origin = fn_80177FE0();
    fn_8011F4E0();
    fn_8009E9EC(p, (unsigned char)(p->mpState->mUnknown1 + 14), &spot);
    fn_8011F4EC();
    fn_80117AA4(p, &target, &pBlock->mUnknown12);
    fn_80227690(&target, &target, &p->mMotion.mPos);
    dx = target.mX;
    dy = target.mY;
    pBlock->mUnknown8 = fn_801CFE40(dy, dx);
    if ((p->mMotion.mUnknown28 != 0.0f && fn_802270A4(&target) < 0.5f)
        || (p->mMotion.mUnknown28 == 0.0f && fn_802270A4(&target) < 1.0f)) {
        pBlock->mUnknown12 = 0.0f;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = 0xC00000;
        p->mUnknown512.mUnknown4 = 0xC00000;
        p->mUnknown512.mUnknown0 = 0.0f;
    }
}

extern "C" int fn_80118210(Object_80039F5C *p)
{
    Block_80118210 *pBlock = (Block_80118210 *)&p->mUnknown336;

    pBlock->mUnknown2 = 0;
    pBlock->mUnknown0 = 0;
    pBlock->mUnknown24 = 0;
    pBlock->mUnknown26 = 0;
    pBlock->mUnknown4 = 0xC00000;
    pBlock->mUnknown12 = 0.0f;
    pBlock->mUnknown8 = 0;
    pBlock->mUnknown20 = 0;
    if (fn_8011F1A4()) {
        int range;

        pBlock->mUnknown16 = 1;
        range = 255 - p->mRatings[8];
        if (range < 0) {
            range = 0;
        }
        pBlock->mUnknown18 = fn_802372EC(0, range / 6);
    } else {
        pBlock->mUnknown16 = 0;
        pBlock->mUnknown18 = 0;
    }
    return 0;
}

extern "C" int fn_801182C8(Object_80039F5C *p)
{
    Message_800F01CC message;
    Vector_80039F5C ball;
    int update = 0;
    Object_80039F5C *pCarrier = BallGetCurrentHolder();
    State_80116C34 *state = (State_80116C34 *)&p->mUnknown336;
    fn_8010A2DC(p, 0, -1);
    state->mUnknown0++;
    state->mUnknown2 = (signed char)(state->mUnknown2 - 1);
    if (state->mUnknown2 < 0) {
        int limit = 255 - p->mRatings[8];
        if (limit < 0) limit = 0;
        update = 1;
        int base = fn_800AC2C0(p->mIdBytes[2]);
        state->mUnknown2 = (signed char)(state->mUnknown2 + base + fn_802372EC(0, (unsigned int)limit >> 5));
        state->mUnknown2 = fn_8009AF00(p->mIdBytes[2], (signed char)state->mUnknown2);
    }
    if (!(p->mFlags & 0x4000) && update) {
        if (!state->mUnknown16 || state->mUnknown0 < state->mUnknown18) {
            fn_801180FC(p);
            if (state->mUnknown12 == 1.0f) {
                state->mUnknown4 = state->mUnknown8;
            } else {
                state->mUnknown4 = 0xC00000;
            }
        } else {
            state->mUnknown12 = 0.1f;
            BallGetPosition(BallGetCurrent(), &ball);
            fn_80227690(&ball, &ball, &p->mMotion.mPos);
            state->mUnknown4 = fn_801CFE40(ball.mY, ball.mX);
            if (((fn_801CFE40(ball.mY, ball.mX) - p->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
                state->mUnknown8 = state->mUnknown4 - 0x400000;
            } else {
                state->mUnknown8 = state->mUnknown4 + 0x400000;
            }
        }
    }
    if (fn_800A5C04(p, state->mUnknown8, state->mUnknown4) || (p->mFlags & 0x4000)) return 0;
    if (update) {
        int kind = fn_8009E180(p);
        if (state->mUnknown24) kind = 5;
        if (kind > 1) {
            if (kind != 4) {
                unsigned short odds = p->mRatings[8];
                if (fn_800B65A0(p->mIdBytes[2]) == 255) {
                    odds += (int)(odds * PlayTrackGetPlayIdRate());
                }
                if ((kind == 5 || kind == 2) && pCarrier) {
                    if (fn_801783AC(7) == 1 || fn_801783AC(8) == 1) {
                        odds += pCarrier->mRatings[4] / lbl_803EB008;
                    }
                    odds += (int)(PlayTrackGetResult5Rate() * lbl_803EB00C);
                    if (fn_80177FE0().mY - pCarrier->mMotion.mPos.mY < lbl_803EB004) odds = 255;
                }
                if (kind == 6 || kind == 2 || fn_802372EC(0, 255) <= odds) {
                    if (fn_801170E8(p)) return 0;
                }
            } else if (fn_8009F258(p) == 1) {
                memset(&message, 0, 4);
                message.mId = 24;
                message.mUnknown1[0] = 2;
                fn_800F053C(0, p->mpState, &message, p);
                return 0;
            }
        }
    }
    if (state->mUnknown12 != 0.0f) {
        if (state->mUnknown12 == 1.0f &&
            MathAngleDiff(p->mMotion.mFacing, state->mUnknown8) <= 0xE38E2 &&
            MathAngleDiff(p->mMotion.mUnknown32, state->mUnknown8) <= 0xE38E2) {
            p->mUnknown512.mUnknown15 = 1;
        }
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = state->mUnknown8;
        p->mUnknown512.mUnknown8 = state->mUnknown4;
        p->mUnknown512.mUnknown0 = state->mUnknown12;
    } else if (MathAngleDiff(p->mMotion.mFacing, state->mUnknown4) > 0x71C71) {
        p->mUnknown512.mUnknown14 = 3;
        p->mUnknown512.mUnknown4 = (state->mUnknown4 + 0x800000) & 0xFFFFFF;
        p->mUnknown512.mUnknown8 = state->mUnknown4;
        p->mUnknown512.mUnknown0 = 0.5f;
    }
    return 0;
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

extern "C" void fn_801187CC(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Vector_80039F5C a;
    Vector_80039F5C b;
    Vector_80039F5C mid;

    if (fn_800A7F08(p->mIdBytes[2]) == 2) {
        fn_8009BF5C(p, CharSkelGetJointByName(p->mpUnknown4->mpUnknown100, lbl_8029DB78), &a, 0);
        fn_8009BF5C(pOther, CharSkelGetJointByName(pOther->mpUnknown4->mpUnknown100, lbl_8029DB78), &b, 0);
        fn_80227930(&mid, &b, &a, 0.75f);
        if (fn_801784C4() != 0) {
            mid.mX = -mid.mX;
            mid.mY = -mid.mY;
        }
    }
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
    unsigned short otherValue = 0;
    unsigned int count = fn_80178D70(team);

    for (; i < count; i++) {
        Object_80039F5C *p = PlyrGet(team, i);
        Object_80039F5C *pOther;
        unsigned short value;
        int mode;
        int otherMode;

        if (p->mUnknown1032 == 7) {
            pOther = fn_8009BCE8(&p->mUnknown1040);
        } else {
            pOther = fn_8009BCE8(&p->mUnknown1036);
        }
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
                PlyrCollideRemoveExempt(p, pOther);
                mode = 2;
                otherMode = 8;
                PlyrCollideRemoveExempt(pOther, p);
                break;
            case 3:
                if (pOther != 0) {
                    mode = 1;
                    if (MathAngleDiff(p->mMotion.mFacing, pOther->mMotion.mFacing) > 0x471C71) {
                        mode = p->mUnknown1032;
                    }
                    otherMode = pOther->mUnknown1032;
                } else {
                    otherMode = 0;
                    mode = 3;
                }
                break;
            case 2:
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
                p->mUnknown1072.mUnknown54 = 1;
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
            pOther->mUnknown1134 = otherValue;
            pOther->mUnknown1136 = 0;
            pOther->mUnknown1137 = 0;
        }
    }
}

extern "C" int fn_80118B4C(Object_80039F5C *p, Pair_8011BAE0 *pPair)
{
    Block_80118B4C *pBlock = (Block_80118B4C *)&p->mBlock1032;
    Query_800CE770 query;
    Object_80039F5C *pOther;
    Block_80118B4C *pOtherBlock;
    unsigned int count;
    float roll;
    int result;
    int close;
    float slow;
    Point_8017886C delta;
    int moves[2];

    fn_800CA5CC(p, 8, 0);
    result = 0;
    close = 0;
    if (!BallFindHeldBy(p) && (p->mUnknown1032 == 2 || p->mUnknown1032 == 3)) {
        pOther = fn_8009BCE8(&p->mUnknown1036);
        pOtherBlock = (Block_80118B4C *)&pOther->mBlock1032;
        if (fn_800CA5CC(pOther, 8, 0) && fn_800B65A0(pOther->mIdBytes[2]) == 255) {
            fn_8011F1CC();
        }
        if (fn_8011F1CC() && lbl_803EB028->mUnknown84 <= 45) goto done;
        if (MathAngleDiff(p->mMotion.mFacing, 0x400000) > 0x400000
            || pOther->mMotion.mPos.mY < fn_80177FE0().mY - lbl_803EB020) {
            close = 1;
        }
        if (lbl_803EB028->mUnknown84 <= 45 && !close) goto done;
        slow = gPlyrMoveFwdSpeed * 0.2f;
        if (p->mMotion.mUnknown28 <= slow || pOther->mMotion.mUnknown28 <= slow) goto done;
        if (!fn_8011A994(p, pOther)) goto done;
        fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        if (MathAngleDiff(pOther->mUnknown512.mUnknown4, angle) > 0x438E38
            && pOther->mUnknown512.mUnknown0 >= 0.4f
            && (p->mUnknown8 == 255 || p->mpState->mId != 96)) {
            goto done;
        }
        if (fn_80227890(&p->mMotion.mPos, &pOther->mMotion.mPos) >= 12.25f) goto done;
        if (!fn_80124714(p, pOther, 0)) goto done;
        count = 0;
        roll = fn_80237260(0);
        fn_8011A2C4(p, pOther, *pPair, 1);
        if (pBlock->mUnknown20 != 1 || close) {
            if (roll < pBlock->mUnknown52) {
                if (roll < pBlock->mUnknown52 * 0.5f) {
                    moves[count++] = lbl_802DAC38[0];
                } else {
                    moves[count++] = lbl_802DAC38[1];
                }
            } else if (roll < pOtherBlock->mUnknown52) {
                int blocked = 0;
                Object_80039F5C *pCarrier = BallGetCurrentHolder();
                if (pCarrier) {
                    Vector_80039F5C toCarrier;
                    fn_802276B4(&toCarrier, &pCarrier->mMotion.mPos, &pOther->mMotion.mPos);
                    int heading = fn_801CFE40(toCarrier.mY, toCarrier.mX);
                    if (fn_80124714(pOther, BallGetCurrentHolder(), 0) && fn_802270D4(&toCarrier) < 6.0f) {
                        blocked = MathAngleDiff(heading, pOther->mMotion.mFacing + fn_800C8BAC(pOther, 0)) <= 0x555554;
                    }
                }
                if (!blocked) {
                    moves[count++] = lbl_802DAC38[2];
                }
            }
        }

        fn_800CE770(&query);
        query.mpUnknown0 = p;
        query.mpUnknown4 = pOther;
        if (p->mpState->mId == 96) {
            query.mUnknown36 = 0x66666;
            query.mUnknown44 = 0.45f;
        } else {
            query.mUnknown36 = 0xE38E3;
            query.mUnknown44 = 0.4f;
        }
        for (unsigned char i = 0; i < count; i++) {
            query.mUnknown52 = moves[i];
            if (fn_800CE4A8(&query)) {
                result = 1;
                if (moves[i] == lbl_802DAC38[0] || moves[i] == lbl_802DAC38[2]) {
                    fn_8011E1BC(p, pOther, 0, 5);
                    fn_8011E33C(pOther, p, 5);
                    if (moves[i] == lbl_802DAC38[0]) {
                        fn_801187CC(p, pOther);
                    }
                } else {
                    fn_8011E1BC(p, pOther, 0, 6);
                    fn_8011E33C(pOther, p, 6);
                }
                fn_800CA5CC(p, 8, 1);
                if (fn_800B65A0(pOther->mIdBytes[2]) != 255 || !fn_8011F1CC()) {
                    fn_800CA5CC(pOther, 8, 1);
                }
                break;
            }
        }
    }
done:
    return result;
}

extern "C" void fn_80119020(void)
{
    Query_800CE770 query;
    Vector_80039F5C ball;

    if (fn_8011F32C() || fn_80177C38() || fn_801787A0()) return;

    unsigned char i = 0;
    BallGetPosition(BallGetCurrent(), &ball);
    int team = fn_80178308();
    unsigned int count = fn_80178D70(team);
    for (; i < count; i++) {
        Object_80039F5C *p = PlyrGet(team, i);
        Block_80119020 *pBlock = (Block_80119020 *)&p->mBlock1032;
        if (BallFindHeldBy(p)) continue;
        if (p->mUnknown1032 != 4 && p->mUnknown1032 != 2 && p->mUnknown1032 != 3) continue;
        Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown1036);
        Block_80119020 *pOtherBlock = (Block_80119020 *)&pOther->mBlock1032;
        if (pBlock->mUnknown105 || !pOtherBlock->mUnknown102) {
            int odds = p->mRatings[2] + p->mRatings[0];
            odds += (int)p->mUnknown2904Float;
            if (p->mUnknown1052 == 1) {
                odds += p->mRatings[7];
            } else {
                odds += p->mRatings[7];
            }
            odds /= 4;
            odds += fn_802372EC(0, 75);
            int diff = pOther->mRatings[2] + pOther->mRatings[4] + pOther->mRatings[5];
            diff += (int)pOther->mUnknown2904Float;
            diff /= 4;
            diff += fn_802372EC(0, 75);
            diff -= odds;
            if (p->mUnknown1052 == 1) {
                switch (p->mUnknown2914) {
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 24:
                    if (pBlock->mUnknown105 || fn_8011E188() > 179) {
                        diff /= 4;
                    } else {
                        diff = 0;
                    }
                    break;
                }
            } else {
                int late = 0;
                if (!fn_801783AC(0) && fn_80177FE0().mY - ball.mY > 2.0f) {
                    late = 1;
                } else if (fn_8011E188() <= 59) {
                    late = 1;
                }
                if (late) diff = 0;
            }
            if ((pBlock->mUnknown0 == 4 || pBlock->mUnknown0 == 7) && pBlock->mUnknown95) {
                diff /= 2;
            }
            if (pBlock->mUnknown105 || (diff > 0 && (int)fn_802372EC(0, 100) < diff)) {
                pBlock->mUnknown104 = 1;
            }
            if (pBlock->mUnknown104) {
                diff += p->mRatings[0] - pOther->mRatings[0];
                if ((int)fn_802372EC(0, 100) < diff) pBlock->mUnknown101 = 0; else pBlock->mUnknown101 = 1;
            }
            pBlock->mUnknown105 = 0;
        }
        if (!pBlock->mUnknown104) continue;

        int go = 1;
        if (pBlock->mUnknown0 == 2 || pBlock->mUnknown0 == 3) {
            Point_8017886C delta;
            go = 0;
            fn_80227690(&delta, &ball, &p->mMotion.mPos);
            int angle = fn_801CFE40(delta.mY, delta.mX);
            fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
            if (MathAngleDiff(angle, fn_801CFE40(delta.mY, delta.mX)) > 0x600000 || fn_802270A4(&delta) < 3.0f) {
                float dist;
                Object_80039F5C *pNear = fn_80124C28(p, &dist, 0x355555, 4.0f, 0.5f, p->mMotion.mFacing);
                if (pNear == pOther || !pNear) go = 1;
            }
        }
        if (!go) continue;
        if (!fn_8011A994(p, pOther)) continue;

        int done;
        fn_800CE770(&query);
        query.mUnknown36 = 0xE38E3;
        query.mUnknown44 = 0.4f;
        query.mpUnknown0 = p;
        query.mpUnknown4 = pOther;
        if (!pBlock->mUnknown101) {
            query.mUnknown52 = 79;
            done = fn_800CE4A8(&query);
        } else {
            query.mUnknown52 = 25;
            done = fn_800CE4A8(&query);
        }
        if (done) {
            fn_8011E1BC(p, pOther, 0, 5);
            fn_8011E33C(pOther, p, 5);
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
        fn_80118B4C(PlyrGet(team, i), &pair);
    }
}

extern "C" void fn_801194F0(void)
{
    Query_800CE770 query;
    int moves[4];
    Pair_8011BAE0 pair;

    unsigned char i = 0;
    int team = fn_80178308();
    fn_8011BAE0(&pair);
    unsigned int count = fn_80178D70(team);
    for (; i < count; i++) {
        Object_80039F5C *p = PlyrGet(team, i);
        fn_800CA5CC(p, 8, 0);
        Block_801194F0 *pBlock = (Block_801194F0 *)&p->mBlock1032;
        if (BallFindHeldBy(p)) continue;
        if (p->mUnknown1032 != 2 && p->mUnknown1032 != 3) continue;
        if (fn_80237260(0) >= 1.0f) continue;

        int covered = 0;
        Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown1036);
        if (fn_800A851C(fn_80178320(), pOther) && fn_800A8444(fn_80178320())) {
            covered = 1;
        }
        Block_801194F0 *pOtherBlock = (Block_801194F0 *)&pOther->mBlock1032;
        fn_800CA5CC(pOther, 8, 0);
        if (fn_8011F1CC() && lbl_803EB028->mUnknown84 <= 45) continue;
        if (covered) continue;
        float slow = gPlyrMoveFwdSpeed * 0.14f;
        if (p->mMotion.mUnknown28 <= slow && pOther->mMotion.mUnknown28 <= slow) continue;
        if (!fn_8011A994(p, pOther) && !fn_80113BCC(pOther)) continue;

        Point_8017886C delta;
        fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        if (MathAngleDiff(pOther->mUnknown512.mUnknown4, angle) > 0x51C71B
            && pOther->mUnknown512.mUnknown0 >= 0.4f) {
            continue;
        }
        angle = (angle + 0x800000) & 0xFFFFFF;
        if (MathAngleDiff(angle, p->mMotion.mFacing + fn_800C8BAC(p, 0)) > 0x555554) continue;
        if (fn_80227890(&p->mMotion.mPos, &pOther->mMotion.mPos) >= 12.25f) continue;
        if (!fn_80124714(p, pOther, 0)) continue;

        fn_8011A2C4(p, pOther, pair, 1);
        unsigned char num = 0;
        if (lbl_803EB028->mUnknown84 > 12) {
            int tryOther = 1;
            if (p->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.2f
                && MathAngleDiff(angle, p->mMotion.mFacing + fn_800C8BAC(p, 0)) <= 0x155554) {
                if (fn_80237260(0) < pBlock->mUnknown52) {
                    moves[num] = lbl_802DAC20[3];
                    num++;
                    tryOther = 0;
                }
            } else if (pOther->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.2f && !fn_80113BCC(pOther)) {
                if (fn_80237260(0) < pBlock->mUnknown52) {
                    moves[num] = lbl_802DAC20[2];
                    num++;
                    tryOther = 0;
                }
            }
            if (tryOther && !fn_80113BCC(pOther)) {
                int blocked = 0;
                Object_80039F5C *pCarrier = BallGetCurrentHolder();
                if (pCarrier) {
                    Vector_80039F5C toCarrier;
                    fn_802276B4(&toCarrier, &pCarrier->mMotion.mPos, &pOther->mMotion.mPos);
                    int heading = fn_801CFE40(toCarrier.mY, toCarrier.mX);
                    if (fn_80124714(pOther, BallGetCurrentHolder(), 0) && fn_802270D4(&toCarrier) < 6.0f) {
                        blocked = MathAngleDiff(heading, pOther->mMotion.mFacing + fn_800C8BAC(pOther, 0)) <= 0x555554;
                    }
                }
                if (!blocked) {
                    if (pOther->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.2f
                        && MathAngleDiff(angle + 0x800000, pOther->mMotion.mFacing + fn_800C8BAC(pOther, 0)) <= 0x155554) {
                        if (fn_80237260(0) < pOtherBlock->mUnknown52) {
                            moves[num] = lbl_802DAC20[0];
                            num++;
                        }
                    } else if (p->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.2f) {
                        if (fn_80237260(0) < pOtherBlock->mUnknown52) {
                            moves[num] = lbl_802DAC20[5];
                            num++;
                        }
                    }
                }
            }
        }
        if (!fn_80113BCC(pOther)) {
            if (pBlock->mUnknown95) {
                if (pBlock->mUnknown40 > 0.16f && pBlock->mUnknown20 != 1) {
                    moves[num] = lbl_802DAC20[4];
                    num++;
                }
            } else if (pOtherBlock->mUnknown40 > 0.16f) {
                moves[num] = lbl_802DAC20[1];
                num++;
            }
        }

        fn_800CE770(&query);
        query.mpUnknown0 = p;
        query.mpUnknown4 = pOther;
        query.mUnknown36 = 0xE38E3;
        query.mUnknown44 = 0.4f;
        for (unsigned char j = 0; j < num; j++) {
            query.mUnknown52 = moves[j];
            if (fn_800CE4A8(&query)) {
                if (moves[j] == lbl_802DAC20[3] || moves[j] == lbl_802DAC20[0]
                    || moves[j] == lbl_802DAC20[5] || moves[j] == lbl_802DAC20[2]) {
                    fn_8011E1BC(p, pOther, 0, 5);
                    fn_8011E33C(pOther, p, 5);
                    if (moves[j] == lbl_802DAC20[3] || moves[j] == lbl_802DAC20[2]) {
                        fn_801187CC(p, query.mpUnknown4);
                    }
                } else {
                    fn_8011E1BC(p, pOther, 0, 6);
                    fn_8011E33C(pOther, p, 6);
                }
                fn_800CA5CC(p, 8, 1);
                fn_800CA5CC(pOther, 8, 1);
                break;
            }
        }
    }
}

extern "C" void fn_80119B98(void)
{
    int team = fn_80178308();
    unsigned char i = 0;
    Pair_8011BAE0 pair;
    unsigned int count;

    fn_8011BAE0(&pair);
    count = fn_80178D70(team);
    for (; i < count; i++) {
        Object_80039F5C *p = PlyrGet(team, i);
        Ball_t *pBall;

        fn_800CA5CC(p, 8, 0);
        pBall = BallFindHeldBy(p);
        if (pBall == 0 && p->mUnknown1032 == 7) {
            Object_80039F5C *pA = fn_8009BCE8(&p->mUnknown1036);
            Object_80039F5C *pB = fn_8009BCE8(&p->mUnknown1040);

            fn_800CA5CC(pB, 8, 0);
            if (fn_8011A994(p, pB) && fn_80227890(&p->mMotion.mPos, &pB->mMotion.mPos) < 25.0f
                && fn_801248D4(p, 0, &pB->mMotion.mPos, 0, 0.0f, 0.5f, 0, pA)) {
                Query_800CE770 query;
                int done;

                fn_800CE770(&query);
                query.mUnknown52 = 243;
                query.mUnknown36 = 0x18E38E;
                query.mUnknown57 = 0;
                query.mpUnknown0 = p;
                query.mpUnknown4Entries[0] = pA;
                query.mpUnknown4Entries[1] = pB;
                query.mUnknown44 = 0.45f;
                done = 0;
                fn_8011E1A8(p, 2);
                if (fn_800CE4A8(&query)) {
                    done = 1;
                } else {
                    query.mUnknown57 = 1;
                    fn_8011E194(p, 2);
                    if (fn_800CE4A8(&query)) {
                        done = 1;
                    }
                }
                if (done) {
                    fn_8011E1BC(p, pA, pB, 5);
                    fn_8011E33C(pA, p, 6);
                    fn_8011E33C(pB, p, 6);
                    fn_800CA5CC(p, 8, 1);
                    fn_800CA5CC(pB, 8, 1);
                }
                fn_8011E1A8(p, 2);
            }
        }
    }
}

extern "C" void fn_80119DB4(Object_80039F5C *p, Object_80039F5C *pOther, int apply)
{
    Block_80119DB4 *pBlock = (Block_80119DB4 *)&p->mUnknown1072;
    Block_80119DB4 *pOtherBlock = (Block_80119DB4 *)&pOther->mUnknown1072;
    Record_80118894 *pRecord = (Record_80118894 *)&p->mUnknown1032;
    Record_80118894 *pOtherRecord = (Record_80118894 *)&pOther->mUnknown1032;
    short *pRatings = p->mRatings;
    short *pOtherRatings = pOther->mRatings;
    int first = p->mUnknown1052 == 1;
    Object_80039F5C *pCarrier;

    pBlock->mUnknown24 = pRatings[7] * lbl_803EB050 + p->mUnknown2904Float * lbl_803EB054;
    pBlock->mUnknown28 = pRatings[7];
    pBlock->mUnknown32 = pRatings[7] * lbl_803EB060 + p->mUnknown2904Float * lbl_803EB064;
    pBlock->mUnknown36 = pRatings[7] * lbl_803EB070 + p->mUnknown2904Float * lbl_803EB074;
    pOtherBlock->mUnknown24 = pOtherRatings[9] * lbl_803EB058 + pOther->mUnknown2904Float * lbl_803EB05C;
    pOtherBlock->mUnknown28 = pOtherRatings[9];
    pOtherBlock->mUnknown32 = pOtherRatings[9] * lbl_803EB068 + pOther->mUnknown2904Float * lbl_803EB06C;
    pOtherBlock->mUnknown36 = pOtherRatings[9] * lbl_803EB078 + pOther->mUnknown2904Float * lbl_803EB07C;
    if (first && fn_801783AC(0) == 0) {
        float scale;

        pOtherBlock->mUnknown32 += pOtherBlock->mUnknown32 * lbl_803EB02C;
        scale = lbl_803EB028->mUnknown84;
        if (scale > lbl_803EB030) {
            scale = lbl_803EB030;
        }
        scale = fn_800AC004(pOther->mIdBytes[2], scale / lbl_803EB030);
        pBlock->mUnknown24 -= pBlock->mUnknown24 * scale;
        pBlock->mUnknown28 -= pBlock->mUnknown28 * scale;
        pBlock->mUnknown32 -= pBlock->mUnknown32 * scale;
        pBlock->mUnknown36 -= pBlock->mUnknown36 * scale;
    } else if (p->mMotion.mUnknown28 > gPlyrMoveFwdSpeed * 0.4f) {
        pBlock->mUnknown24 += pBlock->mUnknown24 * lbl_803EB034;
        pBlock->mUnknown32 += pBlock->mUnknown32 * lbl_803EB034;
    }
    pCarrier = BallGetCurrentHolder();
    if (pCarrier != 0 && fn_800B65A0(pCarrier->mIdBytes[2]) != 0xFF && fn_800B65A0(pOther->mIdBytes[2]) == 0xFF) {
        float bonus = PlayTrackGetPlayIdRate();

        if (first && (pCarrier->mFlags & 0x8000)) {
            float other = PlayTrackGetResult5Rate();

            if (bonus < other) {
                bonus = other;
            }
        }
        pOtherBlock->mUnknown24 += pOtherBlock->mUnknown24 * (bonus * lbl_803EB038);
        pOtherBlock->mUnknown28 += pOtherBlock->mUnknown28 * (bonus * lbl_803EB03C);
        pOtherBlock->mUnknown32 += pOtherBlock->mUnknown32 * (bonus * lbl_803EB040);
        pOtherBlock->mUnknown36 += pOtherBlock->mUnknown36 * (bonus * lbl_803EB044);
    }
    if (first && pCarrier != 0 && (pCarrier->mFlags & 0x8000)) {
        pBlock->mUnknown24 *= lbl_803EB048;
        pBlock->mUnknown28 *= lbl_803EB048;
        pBlock->mUnknown32 *= lbl_803EB048;
        pBlock->mUnknown36 *= lbl_803EB048;
        pOtherBlock->mUnknown24 *= lbl_803EB04C;
        pOtherBlock->mUnknown28 *= lbl_803EB04C;
        pOtherBlock->mUnknown32 *= lbl_803EB04C;
        pOtherBlock->mUnknown36 *= lbl_803EB04C;
    }
    if (fabsf(p->mMotion.mPos.mX) > 4.0f) {
        pBlock->mUnknown36 *= fn_800AD204(p->mIdBytes[2], p->mRatings[7]);
    }
    pBlock->mUnknown24 *= pBlock->mUnknown40;
    pBlock->mUnknown28 *= pBlock->mUnknown44;
    pBlock->mUnknown32 *= pBlock->mUnknown48;
    pOtherBlock->mUnknown24 *= pOtherBlock->mUnknown40;
    pOtherBlock->mUnknown28 *= pOtherBlock->mUnknown44;
    pOtherBlock->mUnknown32 *= pOtherBlock->mUnknown48;
    fn_800ABF00(p->mIdBytes[2], pBlock);
    fn_800ABF00(pOther->mIdBytes[2], pOtherBlock);
    if (apply) {
        fn_80118894(pRecord, pOtherRecord, fn_800CA5CC(p, 8, 0), fn_800CA5CC(pOther, 8, 0), p, pOther);
    }
}

extern "C" void fn_8011A2C4(Object_80039F5C *p, Object_80039F5C *pOther, Pair_8011BAE0 spot, int apply)
{
    Point_8017886C delta;
    Block_80119DB4 *pBlock = (Block_80119DB4 *)&p->mUnknown1072;
    Block_80119DB4 *pOtherBlock;
    Block_8011E240 *pState;
    Object_800B26B0 *pMotion;
    int angle;
    float share;
    float chance;
    float first;
    float second;
    float one;

    fn_80227690(&delta, (Point_8017886C *)&spot, (Point_8017886C *)&pOther->mMotion.mPos);
    pOtherBlock = (Block_80119DB4 *)&pOther->mUnknown1072;
    pState = &p->mBlock1032;
    pMotion = &p->mMotion;
    angle = delta.Heading();
    fn_80119DB4(p, pOther, apply);

    share = pBlock->mUnknown28 / (pBlock->mUnknown28 + pOtherBlock->mUnknown28);
    pBlock->mUnknown56 = fn_80237260(0) < share;
    pOtherBlock->mUnknown56 = pBlock->mUnknown56 ^ 1;
    if (pOtherBlock->mUnknown56) {
        share = 1.0f - share;
    }
    if (fn_80237260(0) >= share) {
        second = share * fn_80237260(0);
    } else {
        second = share * share;
    }

    share = pBlock->mUnknown24 / (pBlock->mUnknown24 + pOtherBlock->mUnknown24);
    pBlock->mUnknown55 = fn_80237260(0) < share;
    pOtherBlock->mUnknown55 = pBlock->mUnknown55 ^ 1;
    if (pOtherBlock->mUnknown55) {
        share = 1.0f - share;
    }
    if (fn_80237260(0) >= share) {
        first = share * fn_80237260(0);
    } else {
        first = share * share;
    }

    share = pBlock->mUnknown32 / (pBlock->mUnknown32 + pOtherBlock->mUnknown32);
    if (fn_800E1554(pOther)) {
        share = 0.0f;
    }
    if (fn_80237260(0) >= share) {
        chance = share * fn_80237260(0);
    } else {
        chance = share * share;
    }
    pBlock->mUnknown8 = chance;
    pOtherBlock->mUnknown8 = 1.0f - chance;

    share = pBlock->mUnknown36 / (pBlock->mUnknown36 + pOtherBlock->mUnknown36);
    if (fn_800E1554(pOther)) {
        share = 0.0f;
    }
    pBlock->mUnknown12 = share * lbl_803EB088;
    pOtherBlock->mUnknown12 = 1.0f - share;

    if (pBlock->mUnknown56) {
        pBlock->mUnknown20 = (angle - 0x800000) & 0xFFFFFF;
        pOtherBlock->mUnknown20 = angle;
        if (pBlock->mUnknown55) {
            pOtherBlock->mUnknown16 = pBlock->mUnknown16 = pMotion->mFacing;
            if (pState->mUnknown20 == 1 && fn_80177FE0().mY - pMotion->mPos.mY < 1.5f) {
                first = 0.0f;
            }
        } else {
            pBlock->mUnknown16 = pOtherBlock->mUnknown16 = pOther->mUnknown512.mUnknown4;
            first *= 0.5f;
            second *= 0.5f;
        }
    } else {
        pOtherBlock->mUnknown20 = (angle - 0x800000) & 0xFFFFFF;
        pBlock->mUnknown20 = angle;
        if (pOtherBlock->mUnknown55) {
            pBlock->mUnknown16 = pOtherBlock->mUnknown16 = angle;
        } else {
            pOtherBlock->mUnknown16 = pBlock->mUnknown16 = pMotion->mFacing;
            first *= 0.5f;
            if (pState->mUnknown20 == 1 && fn_80177FE0().mY - pMotion->mPos.mY < 1.5f) {
                first = 0.0f;
            }
            second *= 0.5f;
        }
    }
    pBlock->mUnknown0 = first;
    pOtherBlock->mUnknown0 = first;
    pBlock->mUnknown4 = second;
    pOtherBlock->mUnknown4 = second;
}

extern "C" int fn_8011A608(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Block_8011A608 *pBlock = (Block_8011A608 *)&p->mUnknown1072;
    Block_8011A608 *pOtherBlock = (Block_8011A608 *)&pOther->mUnknown1072;
    int pass = 0;
    int result = 0;
    Query_800CE770 query;

    if (fn_800A851C(fn_80178320(), pOther)) {
        return 0;
    }
    if ((fn_8011F1CC() && fn_80237260(0) > lbl_803EB080) || (fn_8011F1A4() && fn_80237260(0) > lbl_803EB084)) {
        float chance = fn_80237260(0);

        if (chance < pBlock->mUnknown8) {
            fn_800CE770(&query);
            query.mUnknown36 = 0xE38E3;
            query.mUnknown44 = 0.4f;
            query.mpUnknown0 = p;
            query.mpUnknown4 = pOther;
            if (lbl_803EB028->mUnknown84 <= 24) {
                query.mUnknown52 = 150;
                result = fn_800CE4A8(&query);
            } else {
                query.mUnknown52 = 56;
                result = fn_800CE4A8(&query);
                if (result) {
                    pass = 1;
                }
            }
        } else if (chance < pOtherBlock->mUnknown8) {
            fn_800CE770(&query);
            query.mUnknown36 = 0xE38E3;
            query.mUnknown44 = 0.4f;
            query.mUnknown52 = 61;
            query.mpUnknown0 = p;
            query.mpUnknown4 = pOther;
            result = fn_800CE4A8(&query);
        }
    }
    if (result) {
        fn_8011E1BC(p, pOther, 0, 5);
        fn_8011E33C(pOther, p, 5);
        if (pass) {
            fn_801187CC(p, pOther);
        }
    }
    return result;
}

extern "C" Move_8011AB38 *fn_8011A7B4(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Block_8011A608 *pBlock = (Block_8011A608 *)&p->mUnknown1072;
    Block_8011A608 *pOtherBlock = (Block_8011A608 *)&pOther->mUnknown1072;
    int side;
    float limit;
    int dir;

    if (p->mUnknown1052 == 1) {
        side = 1;
        limit = 0.06f;
    } else {
        side = 0;
        limit = 0.175f;
    }
    if (MathAngleDiff(pOther->mMotion.mFacing, p->mMotion.mFacing) > 0x671C72) {
        dir = 0;
    } else if (((p->mMotion.mFacing - pOther->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
        dir = 1;
    } else {
        dir = 2;
    }
    if (pBlock->mUnknown55) {
        if (pBlock->mUnknown0 > limit) {
            return lbl_802DAF8C[side][dir][1];
        }
    } else if (pOtherBlock->mUnknown0 > limit) {
        if (pOtherBlock->mUnknown28 > pBlock->mUnknown28) {
            return lbl_802DAF8C[side][dir][2];
        }
        if (((pOtherBlock->mUnknown16 - pOther->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
            return lbl_802DAF8C[side][dir][4];
        }
        return lbl_802DAF8C[side][dir][3];
    } else if (pOtherBlock->mUnknown28 > pBlock->mUnknown28) {
        if (((pOtherBlock->mUnknown16 - pOther->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
            return lbl_802DAF8C[side][dir][4];
        }
        return lbl_802DAF8C[side][dir][3];
    }
    return lbl_802DAF8C[side][dir][0];
}

extern "C" int fn_8011A994(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Pair_8011BAE0 delta;

    fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
    if (MathAngleDiff(fn_801CFE40(delta.mUnknown4, delta.mUnknown0), pOther->mMotion.mFacing) > (int)(lbl_803EB08C * 46603.38f)) {
        Object_80039F5C *pCarrier = BallGetCurrentHolder();

        if (pCarrier != 0 && fn_8022781C(&pOther->mMotion.mPos, &pCarrier->mMotion.mPos) > lbl_803EB090) {
            return 0;
        }
    }
    if (fn_801787A0()) {
        return 0;
    }
    switch (pOther->mpState->mId) {
    case 22:
    case 92:
        return (pOther->mFlags >> 10) & 1;
    case 12:
    case 94:
        return p->mUnknown1040 == pOther->mId && fn_800CD2B4(1, pOther) == 0;
    case 1:
    case 5:
    case 10:
    case 15:
    case 16:
    case 17:
    case 28:
    case 50:
    case 58:
    case 91:
        return 0;
    case 57:
        return LooseBallIsIdle(pOther);
    }
    return 1;
}

extern "C" void fn_8011AB38(void)
{
    unsigned char i = 0;
    int team = fn_80178308();
    Pair_8011BAE0 spot;
    unsigned int count;

    fn_8011BAE0(&spot);
    count = fn_80178D70(team);
    for (; i < count; i++) {
        Object_80039F5C *p = PlyrGet(team, i);
        Block_8011AB38 *pState = (Block_8011AB38 *)&p->mUnknown1032;
        int done = 0;

        if (pState->mUnknown0 == 4 || pState->mUnknown0 == 7) {
            Object_80039F5C *pOther = fn_8009BCE8(&pState->mUnknown4);
            Block_8011AB38 *pOtherState = (Block_8011AB38 *)&pOther->mUnknown1032;
            Query_800CE770 query;
            Record_800CE608 result;
            Record_800CE608 otherResult;

            if (pState->mUnknown94) {
                pState->mUnknown94 = 0;
                fn_8011A2C4(p, pOther, spot, 0);
                if (fn_8011A994(p, pOther)) {
                    done = fn_8011A608(p, pOther);
                    if (!done) {
                        unsigned char j = 0;
                        Move_8011AB38 *pMoves = fn_8011A7B4(p, pOther);

                        fn_800CE770(&query);
                        query.mpUnknown0 = p;
                        query.mpUnknown4 = pOther;
                        while (pMoves[j].mKey != 0xFFFF) {
                            if (pMoves[j].mKey != pState->mUnknown24.mUnknown8) {
                                query.mUnknown52 = pMoves[j].mKey;
                                query.mUnknown36 = pMoves[j].mUnknown8;
                                query.mUnknown44 = pMoves[j].mUnknown4;
                                if (fn_800CE590(&query, &result, &otherResult)) {
                                    PlyrCollideAddExempt(p, pOther);
                                    PlyrCollideAddExempt(pOther, p);
                                    if (pState->mUnknown24.mUnknown8 != pMoves[j].mKey) {
                                        pState->mUnknown24 = result;
                                        pOtherState->mUnknown24 = otherResult;
                                        SetMove_8011AB38(p, pState);
                                        SetMove_8011AB38(pOther, pOtherState);
                                        fn_800CE608(p, &result);
                                        fn_800CE608(pOther, &otherResult);
                                        p->mFlags &= ~4;
                                        pOther->mFlags &= ~4;
                                        if (fn_8011DCA8(pMoves[j].mKey)) {
                                            AudmonEventPostArgs(103, &p->mMotion.mPos, p->mId, pOther->mId, 0);
                                        }
                                    }
                                    break;
                                }
                            }
                            j++;
                        }
                    }
                }
            }
            if (!done) {
                if ((p->mFlags & 4) || (pOther->mFlags & 4)) {
                    p->mFlags &= ~4;
                    pOther->mFlags &= ~4;
                    StyleTrackerEndDefensiveMove(pOther);
                    fn_800CE770(&query);
                    query.mpUnknown0 = p;
                    query.mpUnknown4 = pOther;
                    query.mUnknown52 = pState->mUnknown24.mUnknown8;
                    query.mUnknown36 = pState->mUnknown24.mUnknown0;
                    query.mUnknown44 = pState->mUnknown24.mUnknown4;
                    if (pState->mUnknown24.mUnknown8 != 0xFFFF && fn_8011A994(p, pOther)
                        && fn_800CE590(&query, &result, &otherResult)) {
                        pState->mUnknown24 = result;
                        pOtherState->mUnknown24 = otherResult;
                        SetMove_8011AB38(p, pState);
                        SetMove_8011AB38(pOther, pOtherState);
                        fn_800CE608(p, &result);
                        fn_800CE608(pOther, &otherResult);
                        PlyrCollideAddExempt(p, pOther);
                        PlyrCollideAddExempt(pOther, p);
                    } else {
                        if (fn_801BE648(p->mpUnknown792) != 74) {
                            fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 74, 1.0f, p);
                        }
                        if (fn_801BE648(pOther->mpUnknown792) != 74) {
                            fn_801BE068(pOther->mpUnknown792, pOther->mpUnknown796, pOther->mpUnknown800, 74, 1.0f, pOther);
                        }
                    }
                }
                SetMove_8011AB38(p, pState);
                SetMove_8011AB38(pOther, pOtherState);
            }
        }
    }
}

extern "C" void fn_8011AFCC(Entry_8011AFCC *pEntries)
{
    int swapped;

    do {
        Entry_8011AFCC *pPrev = pEntries;
        Entry_8011AFCC *pEntry;

        swapped = 0;
        for (pEntry = pEntries + 1; pEntry->mpUnknown60 != 0; pEntry++) {
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
        for (pEntry = pEntries + 1; pEntry->mpUnknown60 != 0; pEntry++) {
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

extern "C" int fn_8011B2A4(Entry_8011AFCC_8011B2A4 *pEntry)
{
    Object_800B26B0 *pMotion;
    Point_8017886C origin;
    Vector_80039F5C ball;

    if ((pEntry->mpUnknown60->mFlags & 0x800)
        || (pEntry->mpUnknown60->mUnknown1032 >= 4 && pEntry->mpUnknown60->mUnknown1032 <= 6)) {
        return 0;
    }
    pMotion = &pEntry->mpUnknown60->mMotion;
    origin = fn_80177FE0();
    if (fn_8011F1CC() && !fn_801783AC(0) && !fn_801783AC(13)) {
        State_80039F5C *pState;
        unsigned int id;

        if (pEntry->mUnknown76 == 1) {
            return 0;
        }
        pState = pEntry->mpUnknown60->mpState;
        id = pState->mId;
        if (id == 51) {
            id = pState[1].mId;
        }
        switch (id) {
        case 22:
        case 40:
        case 92:
            if (pEntry->mpUnknown60->mUnknown8 != 0xFF && (pEntry->mpUnknown60->mFlags & 0x4000)) {
                if (lbl_803EB028->mUnknown84 < 20) {
                    if (pMotion->mPos.mY <= origin.mY + 2.5f) {
                        break;
                    }
                } else if (pMotion->mPos.mY <= origin.mY + 3.5f) {
                    if (pMotion->mPos.mY <= origin.mY) {
                        break;
                    }
                    if (MathAngleDiff(pEntry->mpUnknown60->mMotion.mUnknown32, 0xC00000) <= 0x200000
                        && pEntry->mpUnknown60->mMotion.mUnknown28 >= gPlyrMoveFwdSpeed * 0.4f) {
                        break;
                    }
                }
            } else if (lbl_803EB028->mUnknown84 < 20) {
                if (pMotion->mPos.mY <= origin.mY + 2.5f) {
                    break;
                }
            } else {
                if (pMotion->mPos.mY <= origin.mY) {
                    break;
                }
                if (fn_8011F2F8() && fabsf(pMotion->mPos.mX - origin.mX) >= 5.0f
                    && pMotion->mPos.mY <= origin.mY + 5.0f) {
                    break;
                }
            }
            return 0;
        case 89:
            return 0;
        }
    }
    BallGetLandingPoint(BallGetCurrent(), &ball);
    return pMotion->mPos.mY - ball.mY >= -15.0f;
}

extern "C" void fn_8011B4F8(Entry_8011AFCC_8011B4F8 *pEntry)
{
    float score;

    if (fn_8011B2A4((Entry_8011AFCC_8011B2A4 *)pEntry) == 1) {
        Object_800B26B0 *pMotion = &pEntry->mpUnknown60->mMotion;
        Object_80039F5C *p;
        int near;

        if (pEntry->mUnknown72 < 80.0f) {
            score = 80.0f - pEntry->mUnknown72;
        } else {
            score = 5.0f;
        }
        if (pMotion->mUnknown28 > gPlyrMoveFwdSpeed * 0.5f && MathAngleDiff(pEntry->mUnknown64, pMotion->mUnknown32) > 0x4E38E3) {
            pEntry->mUnknown76 = 1;
            score *= 0.8f;
        }
        switch (pEntry->mpUnknown60->mQueue[0].mId) {
        case 10:
        case 11:
            score *= 0.33333334f;
            break;
        }
        if (fn_8011F1CC()) {
            score += fabsf(pMotion->mPos.mX - fn_80177FE0().mX) * 0.25f;
        } else {
            int angle = MathAngleDiff(pEntry->mUnknown64, pMotion->mFacing);

            if (angle > 0x600000) {
                score *= 0.083333336f;
            } else if (angle > 0x400000) {
                score *= 0.16666667f;
            }
        }
        p = pEntry->mpUnknown60;
        near = 0;
        if (p->mUnknown8 != 0xFF) {
            near = fabsf(p->mMotion.mPos.mY - fn_80177FE0().mY) <= 5.5f
                && fabsf(pEntry->mpUnknown60->mMotion.mPos.mX - fn_80177FE0().mX) <= 2.0f;
        }
        if (near) {
            score *= 10.0f;
        }
    } else {
        score = 5.0f;
    }
    pEntry->mUnknown68 = score;
}

extern "C" void fn_8011B6E8(Entry_8011AFCC_8011B4F8 *pEntries, Pair_8011BAE0 target)
{
    unsigned char count = 0;
    unsigned char i = 0;
    int team = fn_80178320();
    unsigned int n = fn_80178D70(team);

    for (; i < n; i++) {
        Object_80039F5C *p = PlyrGet(team, i);
        int skip = 0;

        switch (p->mQueue[0].mId) {
        case 16:
        case 32:
        case 89:
            skip = 1;
            break;
        case 17:
            if (!fn_80113BCC(p)) {
                skip = 1;
            }
            break;
        }
        if (!skip) {
            Pair_8011BAE0 delta;

            pEntries[count].mpUnknown60 = p;
            pEntries[count].mUnknown0 = 0;
            fn_80227690(&delta, &target, &p->mMotion.mPos);
            pEntries[count].mUnknown72 = fn_802270A4(&delta);
            pEntries[count].mUnknown64 = fn_801CFE40(delta.mUnknown4, delta.mUnknown0);
            pEntries[count].mUnknown76 = 0;
            fn_8011B4F8(&pEntries[count]);
            count++;
        }
    }
    pEntries[count].mpUnknown60 = 0;
    pEntries[count].mUnknown0 = 0;
    pEntries[count].mUnknown68 = 0.0f;
    if (lbl_803EB028->mUnknown88) {
        fn_8011B138((Entry_8011AFCC *)pEntries);
    }
}

extern "C" void fn_8011B83C(Entry_8011AFCC_8011B4F8 *pEntries, Pair_8011BAE0 target)
{
    unsigned char count = 0;
    unsigned char i = 0;
    int team = fn_80178308();
    unsigned int n = fn_80178D70(team);

    for (; i < n; i++) {
        Object_80039F5C *p = PlyrGet(team, i);
        int mode;

        switch (p->mUnknown1052) {
        case 1:
        case 2:
            break;
        default:
            continue;
        }
        mode = p->mUnknown1032;
        if (mode == 5 || mode == 6 || mode == 0) {
            continue;
        }
        if (mode == 4 || mode == 7) {
            short rating;
            int chance;

            if (!(fn_8011F1CC() && lbl_803EB028->mUnknown84 != 0)
                && (fn_8011F1CC() || lbl_803EB028->mUnknown84 <= 60)) {
                continue;
            }
            rating = p->mRatings[7];
            if (fn_800A2178() == 7 || fn_800A2178() == 8) {
                rating *= 3;
            }
            chance = fn_800ACFFC(p->mIdBytes[2], rating);
            if (chance <= 152 && fn_802372EC(0, 100) > chance * 0.6535948f) {
                continue;
            }
        }
        {
            Pair_8011BAE0 delta;

            pEntries[count].mpUnknown60 = p;
            pEntries[count].mUnknown0 = 0;
            fn_80227690(&delta, &target, &p->mMotion.mPos);
            pEntries[count].mUnknown72 = fn_802270A4(&delta);
            pEntries[count].mUnknown64 = fn_801CFE40(delta.mUnknown4, delta.mUnknown0);
            pEntries[count].mUnknown68 = pEntries[count].mUnknown72;
            switch (p->mUnknown2914) {
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                pEntries[count].mUnknown68 *= 0.5f;
                if (p->mRatings[7] > 152) {
                    pEntries[count].mUnknown68 *= 0.01f;
                }
                break;
            }
            if (p->mUnknown1052 == 1) {
                pEntries[count].mUnknown76 = 0;
            } else {
                pEntries[count].mUnknown76 = 1;
            }
            count++;
        }
    }
    pEntries[count].mpUnknown60 = 0;
    pEntries[count].mUnknown0 = 0;
    pEntries[count].mUnknown68 = 0.0f;
    fn_8011AFCC((Entry_8011AFCC *)pEntries);
}

extern "C" void fn_8011BAE0(Pair_8011BAE0 *pOut)
{
    Object_80039F5C *pCarrier = BallGetCurrentHolder();
    int kicking = fn_801783AC(0);
    int offense = fn_8011F1A4();
    Point_8017886C origin;

    origin = fn_80177FE0();
    if (!kicking && offense) {
        if (BallStateGet(BallGetCurrent(), 0) == 3) {
            pCarrier = BallGetCurrentTarget();
        }
        if (pCarrier != 0) {
            if (pCarrier->mpState->mId == 1 || pCarrier->mpState->mId == 68) {
                goto lead;
            }
            pOut->mUnknown0 = fn_8011F4D4();
            if (fn_8011F228()) {
                pOut->mUnknown0 = -pOut->mUnknown0;
            }
            pOut->mUnknown4 = fn_80177FE0().mY - 1.0f;
        } else {
            pOut->mUnknown0 = fn_8011F4D4();
            pOut->mUnknown4 = origin.mY - 1.0f;
        }
    } else if (pCarrier != 0) {
        if (offense || kicking) {
            Point_8017886C offset;

        lead:
            fn_80227248(&offset, &pCarrier->mMotion.mUnknown40, 5.0f);
            fn_80227638(pOut, &pCarrier->mMotion.mPos, &offset);
        } else if (BallGetCurrentHolder() != 0 && !(BallGetCurrentHolder()->mFlags & 0x8000)) {
            pOut->mUnknown0 = origin.mX;
            pOut->mUnknown4 = pCarrier->mMotion.mPos.mY;
            switch (lbl_803EB028->mUnknown90) {
            case 1:
                pOut->mUnknown0 = origin.mX + 0.33f;
                break;
            case 2:
                pOut->mUnknown0 = origin.mX - 0.33f;
                break;
            }
        } else {
            pOut->mUnknown0 = pCarrier->mMotion.mPos.mX;
            pOut->mUnknown4 = pCarrier->mMotion.mPos.mY;
        }
    } else {
        Vector_80039F5C spot;

        BallGetPosition(BallGetCurrent(), &spot);
        BallGetLandingPoint(BallGetCurrent(), &spot);
        pOut->mUnknown0 = spot.mX;
        pOut->mUnknown4 = spot.mY;
    }
}

extern "C" {
float fn_8011BCDC(Entry_8011AFCC_8011BCDC *pEntry, Entry_8011AFCC_8011BCDC *pTarget, Pair_8011BAE0 from, Point_8017886C ball,
                             int a, int b, float weight)
{
    Object_80039F5C *p = pEntry->mpUnknown60;
    Object_80039F5C *pOther = pTarget->mpUnknown60;
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_800B26B0 *pOtherMotion = &pOther->mMotion;
    Point_8017886C delta;
    float across;
    float length;

    fn_80227690(&delta, pMotion, pOtherMotion);
    across = fabsf(delta.mX);
    length = fn_802270A4(&delta);
    delta.Heading();
    if (pTarget->mpUnknown60->mFlags & 0x800) {
        weight *= 0.5f;
    }
    if (!a) {
        switch (pTarget->mpUnknown60->mUnknown2914) {
        case 10:
        case 11:
        case 12:
            if (lbl_803EB028->mUnknown84 < 180
                && ((pMotion->mPos.mX < ball.mX && pOtherMotion->mPos.mX > ball.mX)
                    || (pMotion->mPos.mX > ball.mX && pOtherMotion->mPos.mX < ball.mX))) {
                if (across > lbl_803EB014 * 0.5f) {
                    weight *= 0.5f;
                }
            } else if (across > lbl_803EB014) {
                weight *= 0.5f;
            }
            break;
        default: {
            float limit;

            if ((pOtherMotion->mUnknown32 & 0xFFFFFF) > 0x800000) {
                limit = ball.mY + 2.0f;
            } else {
                limit = ball.mY;
            }

            if (pOtherMotion->mPos.mY > limit) {
                switch (pTarget->mpUnknown60->mpState->mId) {
                case 22:
                case 40:
                case 92:
                    if (!b) {
                        if (pOtherMotion->mPos.mY > ball.mY + 5.0f) {
                            return 0.0f;
                        }
                        if (pOtherMotion->mPos.mY > ball.mY + 3.0f && (length > 5.0f || !fn_8011F2F8())) {
                            weight *= 0.5f;
                        }
                    }
                case 2:
                case 30:
                case 51:
                    if (across > lbl_803EB018) {
                        if (across < lbl_803EB018 * 1.5f && b) {
                            weight *= 0.5f;
                        } else {
                            return 0.0f;
                        }
                    }
                    break;
                case 85:
                    if (pOtherMotion->mPos.mY > ball.mY + 2.0f) {
                        return 0.0f;
                    }
                    if (pTarget->mpUnknown60->mUnknown8 == 0xFF) {
                        return 0.0f;
                    }
                    break;
                case 24:
                    break;
                default:
                    return 0.0f;
                }
            } else if (across > 8.0f) {
                return 0.0f;
            }
            if (BallGetCurrentHolder() != 0 && !(BallGetCurrentHolder()->mFlags & 0x8000)) {
                int close = fabsf(pTarget->mpUnknown60->mMotion.mPos.mY - fn_80177FE0().mY) <= 1.5f
                            && fabsf(pTarget->mpUnknown60->mMotion.mPos.mX - fn_80177FE0().mX) <= 3.0f;

                if (close) {
                    if (pOtherMotion->mUnknown28 > gPlyrMoveFwdSpeed * 0.5f) {
                        if (MathAngleDiff(pTarget->mUnknown64, pOtherMotion->mUnknown32) < 0x2AAAAA) {
                            weight *= 1.5f;
                        }
                    } else {
                        switch (pTarget->mpUnknown60->mpState->mId) {
                        case 2:
                        case 30:
                        case 51:
                            weight *= 1.5f;
                            break;
                        }
                    }
                }
            }
            break;
        }
        }
    }
    if (pEntry->mpUnknown60->mUnknown1048 != pTarget->mpUnknown60->mId) {
        switch (pEntry->mpUnknown60->mUnknown2914) {
        case 6:
        case 8:
            if (lbl_803EB028->mUnknown84 <= 30 || b) {
                break;
            }
            goto deep;
        case 4:
        case 5:
        case 9:
            if (lbl_803EB028->mUnknown84 < 15 && !b) {
                if ((pOtherMotion->mPos.mX > ball.mX && pMotion->mPos.mX < ball.mX)
                    || (pOtherMotion->mPos.mX < ball.mX && pMotion->mPos.mX > ball.mX)) {
                    weight *= 0.75f;
                }
                if (length > 2.0f) {
                    switch (pTarget->mpUnknown60->mUnknown2914) {
                    case 10:
                    case 11:
                    case 12:
                        if (fabsf(pMotion->mPos.mX - from.mUnknown0) > fabsf(pOtherMotion->mPos.mX - from.mUnknown0)) {
                            weight *= 0.95f;
                        }
                        break;
                    default:
                        weight *= 0.9f;
                        break;
                    }
                }
            }
            break;
        case 7:
        case 24:
            if (fabsf(from.mUnknown0 - ball.mX) < lbl_803EB01C && lbl_803EB028->mUnknown84 < 180) {
                switch (pTarget->mpUnknown60->mUnknown2914) {
                case 10:
                case 11:
                case 12:
                    if (across > lbl_803EB01C) {
                        return 0.0f;
                    }
                    if (lbl_803EB028->mUnknown89 && lbl_803EB028->mUnknown84 < 90
                        && pTarget->mpUnknown60->mId != pEntry->mpUnknown60->mUnknown560.mUnknown40) {
                        weight *= 0.75f;
                    }
                    break;
                case 14:
                    if (across > lbl_803EB01C) {
                        return 0.0f;
                    }
                    if (across > 2.5f && lbl_803EB028->mUnknown84 < 60) {
                        weight *= 0.5f;
                    }
                    break;
                default:
                    if (pTarget->mpUnknown60->mFlags & 0x4000) {
                        if (across > lbl_803EB01C) {
                            return 0.0f;
                        }
                    } else if (across > 2.5f) {
                        return 0.0f;
                    }
                    if (lbl_803EB028->mUnknown84 < 60 && across < 2.5f) {
                        weight *= 1.25f;
                    }
                    if (pOtherMotion->mPos.mY < fn_80177FE0().mY + 15.0f) {
                        weight *= 1.0f - (pOtherMotion->mPos.mY - fn_80177FE0().mY) * (1.0f / 15.0f);
                    } else {
                        return 0.0f;
                    }
                    break;
                }
            }
            break;
        case 1:
        case 2:
            if (length > 4.0f && fn_8011F1CC()) {
                Object_80039F5C *pBlocker;

                if (fn_80124714(pEntry->mpUnknown60, pTarget->mpUnknown60, &pBlocker) == 0) {
                    if (pBlocker->mIdBytes[2] == pEntry->mpUnknown60->mIdBytes[2] && pBlocker->mUnknown1032 == 1
                        && !(pBlocker->mFlags & 0x800)) {
                        Point_8017886C gap;

                        fn_80227690(&gap, pOtherMotion, &pBlocker->mMotion.mPos);
                        if (fn_802270A4(&gap) < 2.0f && MathAngleDiff(gap.Heading(), pBlocker->mMotion.mFacing) < 0x400000) {
                            weight *= 0.5f;
                        }
                    }
                } else if (fabsf(pOtherMotion->mPos.mX) > fabsf(pMotion->mPos.mX)) {
                    weight *= 1.5f;
                }
            }
            break;
        default:
        deep:
            if (pOtherMotion->mPos.mY > ball.mY + 2.0f) {
                weight *= 0.75f;
            }
            break;
        }
    }
    return weight;
}
}

extern "C" {
float fn_8011C4E0(Entry_8011AFCC_8011BCDC *pEntry, Entry_8011AFCC_8011BCDC *pTarget, Pair_8011BAE0 from, Point_8017886C ball,
                             float weight, int a)
{
    Object_80039F5C *pOther = pTarget->mpUnknown60;
    Object_80039F5C *p;
    Object_800B26B0 *pMotion;
    Object_800B26B0 *pOtherMotion;
    Point_8017886C delta;
    float across;
    float length;
    int angle;
    int deep;
    int turn;

    if (pOther->mFlags & 0x800) {
        return 0.0f;
    }
    p = pEntry->mpUnknown60;
    pMotion = &p->mMotion;
    pOtherMotion = &pOther->mMotion;
    deep = 0;
    fn_80227690(&delta, pMotion, pOtherMotion);
    across = fabsf(delta.mX);
    length = fn_802270A4(&delta);
    angle = delta.Heading();
    if (fn_8011F1A4()) {
        deep = fn_8011F4C8() > 3;
    }
    if (!a) {
        if (lbl_803EB028->mUnknown84 <= 64) {
            if (!deep && lbl_803EB028->mUnknown84 <= 1 && pOtherMotion->mPos.mY - ball.mY > 2.0f) {
                return 0.0f;
            }
            switch (pEntry->mpUnknown60->mUnknown2914) {
            case 5:
            case 9:
                if (pEntry->mpUnknown60->mUnknown2914 == 5 && deep && fn_8011F1A4() && (fn_8011F4C8() & 1)) {
                    if (pOtherMotion->mPos.mY - ball.mY > 2.0f && pMotion->mPos.mX > pOtherMotion->mPos.mX
                        && across > 2.0f) {
                        return 0.0f;
                    }
                } else if (pEntry->mpUnknown60->mUnknown2914 == 9 && deep && (!fn_8011F1A4() || !(fn_8011F4C8() & 1))) {
                    if (pOtherMotion->mPos.mY - ball.mY > 2.0f && pMotion->mPos.mX < pOtherMotion->mPos.mX
                        && across > 2.0f) {
                        return 0.0f;
                    }
                }
            case 6:
            case 7:
            case 8:
                if (pTarget->mpUnknown60->mId == pEntry->mpUnknown60->mUnknown560.mUnknown40) {
                    weight *= 1.1f;
                } else if (across > 0.85f) {
                    weight *= 0.95f;
                }
            case 4:
            case 24:
                if (length > 5.0f) {
                    return 0.0f;
                }
                if (pMotion->mPos.mY < ball.mY + 1.0f) {
                    if (across > 2.0f) {
                        weight -= length;
                        if (across > 3.5f) {
                            weight *= 0.5f;
                        }
                    } else {
                        if (length > 6.0f) {
                            weight *= 0.5f;
                        } else {
                            weight += 8.0f - length;
                        }
                        if (lbl_803EB028->mUnknown84 <= 3 && pEntry->mUnknown72 < 1.75f
                            && pEntry->mpUnknown60->mUnknown2914 != 7) {
                            weight *= 1.025f;
                        }
                    }
                }
                break;
            case 3:
                if (across > 4.0f) {
                    return 0.0f;
                }
                if (across > 0.5f) {
                    weight -= 16.0f;
                }
                break;
            case 1:
            case 2:
                if (deep && pEntry->mpUnknown60->mUnknown2914 == 2 && pOtherMotion->mPos.mY < ball.mY) {
                    if ((fn_8011F1A4() && (fn_8011F4C8() & 1) && pMotion->mPos.mX > pOtherMotion->mPos.mX)
                        || ((!fn_8011F1A4() || !(fn_8011F4C8() & 1)) && pMotion->mPos.mX < pOtherMotion->mPos.mX)) {
                        weight *= 1.1f;
                    }
                }
                break;
            default:
                weight -= 16.0f;
                break;
            }
        } else if (deep && pEntry->mpUnknown60->mUnknown2914 == 2 && pMotion->mPos.mY < ball.mY - 1.0f
                   && pOtherMotion->mPos.mY < ball.mY) {
            if (((fn_8011F1A4() && (fn_8011F4C8() & 1) && p->mMotion.mPos.mX > pOther->mMotion.mPos.mX)
                 || (fn_8011F1A4() && (fn_8011F4C8() & 1) == 0 && pMotion->mPos.mX < pOtherMotion->mPos.mX))
                && fn_8009BCE8(&pEntry->mpUnknown60->mUnknown1036) == 0 && length < 6.0f && length > 2.25f
                && fn_80124714(pEntry->mpUnknown60, pTarget->mpUnknown60, 0)) {
                weight *= 1.2f;
            }
        }
    } else if (pMotion->mPos.mY > from.mUnknown4) {
        if (length > pEntry->mUnknown72 * 2.5f) {
            weight *= 0.75f;
        }
        if (pOtherMotion->mPos.mY < from.mUnknown4) {
            weight *= 0.5f;
        }
    } else if (length > pEntry->mUnknown72) {
        return 0.0f;
    }
    if (lbl_803EB028->mUnknown84 != 0 && pTarget->mpUnknown60->mpState->mId != 51) {
        if (MathAngleDiff(pMotion->mFacing + fn_800C8BAC(pEntry->mpUnknown60, 0), (angle + 0x800000) & 0xFFFFFF) > 0x555555) {
            if (pMotion->mPos.mY < from.mUnknown4 || (pMotion->mPos.mY < ball.mY && !a)) {
                return 0.0f;
            }
        }
        if (length < 25.0f) {
            turn = MathAngleDiff(pMotion->mFacing, (angle - 0x800000) & 0xFFFFFF);

            if (a || pMotion->mPos.mY > ball.mY || (turn > 0x2E38E3 && lbl_803EB028->mUnknown84 > 30)) {
                turn = MathAngleDiff(pTarget->mUnknown64, pEntry->mUnknown64);
                weight *= fn_801CFB94(turn / 4);
                turn = MathAngleDiff(pEntry->mUnknown64, angle);
                weight *= fn_801CFB94(turn / 3);
            }
            weight *= fn_801CFB94(MathAngleDiff(pMotion->mFacing + fn_800C8BAC(pEntry->mpUnknown60, 0), (angle - 0x800000) & 0xFFFFFF) / 4);
        }
    }
    if (pEntry->mpUnknown60->mUnknown1139 == 1) {
        weight *= 0.75f;
    }
    return weight;
}
}

extern "C" {
float fn_8011CC10(Entry_8011AFCC_8011BCDC *pEntry, Entry_8011AFCC_8011BCDC *pOther, Pair_8011BAE0 pair, Point_8017886C ball, int bit,
                  int a, int c, int b)
{
    Vector_80039F5C *pPos = &pEntry->mpUnknown60->mMotion.mPos;
    Vector_80039F5C *pOtherPos = &pOther->mpUnknown60->mMotion.mPos;
    Point_8017886C delta;
    float distance;
    float score;
    int angle;

    if (!bit && (pEntry->mpUnknown60->mBlock1032.mUnknown100 & 1)
        && fabsf(pOther->mpUnknown60->mMotion.mPos.mX - ball.mX) < 4.0f && pOtherPos->mY < ball.mY + 3.0f) {
        return 0.0f;
    }
    score = 0.0f;
    if (!bit && pEntry->mpUnknown60->mUnknown8 == 255 && pEntry->mUnknown76 == 1 && pOther->mUnknown76 == 1
        && pPos->mY > pOtherPos->mY + 1.0f) {
        return score;
    }
    fn_80227690(&delta, pPos, pOtherPos);
    distance = fn_802270A4(&delta);
    angle = fn_801CFE40(delta.mY, delta.mX);
    score = distance;
    if (score > 88.0f) {
        score = 88.0f;
    }
    score = 88.0f - score;
    if (distance < 2.1f && fn_8011E484(pEntry->mpUnknown60, pOther->mpUnknown60)) {
        score *= 1.2f;
    }
    switch (pEntry->mpUnknown60->mUnknown1052) {
    case 0:
        break;
    case 1:
        score = fn_8011BCDC(pEntry, pOther, pair, ball, bit, c, score);
        break;
    case 2:
        score = fn_8011C4E0(pEntry, pOther, pair, ball, score, bit);
        break;
    }
    if (score == 0.0f) {
        return 0.0f;
    }
    if (bit && MathAngleDiff(pEntry->mUnknown64, (angle - 0x800000) & 0xFFFFFF) <= 0x38E38D && pPos->mY < pOtherPos->mY) {
        score *= 0.5f;
    }
    if (a && pEntry->mpUnknown60->mUnknown8 == 255 && pPos->mY > pOtherPos->mY) {
        return 0.0f;
    }
    if ((pEntry->mpUnknown60->mUnknown1032 == 7 && fn_8009BCE8(&pEntry->mpUnknown60->mUnknown1040) == pOther->mpUnknown60)
        || fn_8009BCE8(&pEntry->mpUnknown60->mUnknown1036) == pOther->mpUnknown60) {
        if ((a && distance < 4.5f && MathAngleDiff(angle, ((Object_800B26B0 *)pOtherPos)->mFacing) <= 0x3FFFFF)
            || (b && pOtherPos->mY < ball.mY + 2.0f)) {
            score *= lbl_803EB094;
        }
        if (!c && distance < 6.0f && distance > 2.25f) {
            if (fn_80124714(pEntry->mpUnknown60, pOther->mpUnknown60, 0)) {
                if (b || MathAngleDiff(angle, ((Object_800B26B0 *)pOtherPos)->mFacing) <= 0x3FFFFF) {
                    score *= 1.1f;
                }
            } else if (bit || (a && pPos->mY > ball.mY)) {
                score *= 0.9f;
            }
        }
    }
    if (pEntry->mpUnknown60->mUnknown1032 == 3) {
        if (pOther->mpUnknown60 == fn_8009BCE8(&pEntry->mpUnknown60->mUnknown1036)) {
            score *= 1.1f;
            if (pOther->mpUnknown60->mUnknown8 != 255) {
                score *= 2.0f;
            }
        } else {
            score *= 0.85f;
        }
    }
    if (pEntry->mpUnknown60->mUnknown8 != 255 && MathAngleDiff(angle, ((Object_800B26B0 *)pPos)->mUnknown32) > 0x6AAAAB) {
        score *= 20.0f;
    }
    return score;
}
}

extern "C" {
void fn_8011D0BC(Entry_8011AFCC_8011BCDC *pA, Entry_8011AFCC_8011BCDC *pB, Pair_8011BAE0 pair)
{
    int bit = fn_801783AC(0);
    Point_8017886C ball = fn_80177FE0();
    int a = fn_8011F1A4();
    int b = fn_8011F1CC();
    int changed;

    if (pB->mpUnknown60 == 0 || pA->mpUnknown60 == 0) {
        return;
    }
    do {
        Entry_8011AFCC_8011BCDC *pEntry;
        Entry_8011AFCC_8011BCDC *pOther;
        Entry_8011AFCC_8011BCDC *pScan;
        Entry_8011AFCC_8011BCDC *pBest;

        for (pEntry = pA; pEntry->mpUnknown60 != 0; pEntry++) {
            float best = 1.0f;

            pBest = 0;

            for (pOther = pB; pOther->mpUnknown60 != 0; pOther++) {
                if (pOther->mUnknown68 > 5.0f) {
                    int index = pOther->mpUnknown60->mIdBytes[1];
                    float value;

                    if (pEntry->mUnknown4[index].mValid) {
                        value = pEntry->mUnknown4[index].mValue;
                    } else {
                        value = fn_8011CC10(pEntry, pOther, pair, ball, bit, a, 0, b);
                        pEntry->mUnknown4[index].mValue = value;
                        pEntry->mUnknown4[index].mValid = 1;
                    }
                    if (value > best) {
                        best = value;
                        pBest = pOther;
                    }
                }
            }
            pEntry->mpUnknown0 = pBest;
            pEntry->mUnknown68 = best;
        }
        changed = 0;
        pEntry = pA;
        while (pEntry->mpUnknown60 != 0) {
            if (pEntry->mpUnknown0 != 0) {
                for (pBest = pScan = pEntry; pScan->mpUnknown60 != 0; pScan++) {
                    if (pScan[1].mpUnknown0 == pBest->mpUnknown0) {
                        changed = 1;
                        if (pScan[1].mUnknown68 > pBest->mUnknown68) {
                            pBest->mpUnknown0 = 0;
                            pBest->mUnknown68 = 0.0f;
                            pBest = &pScan[1];
                        } else {
                            pScan[1].mpUnknown0 = 0;
                            pScan[1].mUnknown68 = 0.0f;
                        }
                    }
                }
                if (pBest->mpUnknown60 != 0 && pBest->mpUnknown0 != 0) {
                    Object_80039F5C *pBlocker = 0;
                    Object_80039F5C *pMarked;

                    if (!fn_80124714(pBest->mpUnknown60, pBest->mpUnknown0->mpUnknown60, &pBlocker)) {
                        Point_8017886C delta;

                        fn_80227690(&delta, &pBest->mpUnknown60->mMotion.mPos, &pBlocker->mMotion.mPos);
                        if (fn_802270A4(&delta) < 1.5f) {
                            for (pOther = pB; pOther->mpUnknown60 != 0; pOther++) {
                                if (pOther->mpUnknown60 == pBlocker) {
                                    if (pOther->mUnknown68 > 5.0f) {
                                        pBest->mpUnknown0 = pOther;
                                        changed = 1;
                                        for (pScan = pEntry; pScan->mpUnknown60 != 0; pScan++) {
                                            if (pScan != pBest && pScan->mpUnknown0 == pOther) {
                                                pScan->mpUnknown0 = 0;
                                                pScan->mUnknown68 = 0.0f;
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    pMarked = fn_8009BCE8(&pBest->mpUnknown0->mpUnknown60->mUnknown1036);
                    if (pMarked != pBest->mpUnknown60) {
                        if (pMarked) {
                            if (pMarked->mUnknown1040 == pBest->mpUnknown0->mpUnknown60->mId) {
                                Object_80039F5C *pPartner = fn_8009BCE8(&pMarked->mUnknown1036);

                                fn_8011E1BC(pMarked, pPartner, 0, 4);
                                fn_8011E33C(pPartner, pMarked, 4);
                            } else {
                                fn_8011E1BC(pMarked, 0, 0, 1);
                            }
                        }
                        if (pBest->mpUnknown60->mUnknown1032 == 4 || pBest->mpUnknown60->mUnknown1032 == 7) {
                            Object_80039F5C *pPartner = fn_8009BCE8(&pBest->mpUnknown60->mUnknown1036);
                            short saved = pBest->mpUnknown60->mBlock1032.mUnknown102;

                            fn_8011E1BC(pBest->mpUnknown60, pPartner, pBest->mpUnknown0->mpUnknown60, 7);
                            pBest->mpUnknown60->mBlock1032.mUnknown102 = saved;
                            fn_8011E33C(pPartner, pBest->mpUnknown60, 4);
                            fn_8011E33C(pBest->mpUnknown0->mpUnknown60, pBest->mpUnknown60, 8);
                        } else {
                            if (pBest->mpUnknown0->mpUnknown60->mId == lbl_803EB028->mUnknown0) {
                                fn_8011E1BC(pBest->mpUnknown60, pBest->mpUnknown0->mpUnknown60, 0, 3);
                                fn_8011E938(0);
                            } else {
                                fn_8011E1BC(pBest->mpUnknown60, pBest->mpUnknown0->mpUnknown60, 0, 2);
                            }
                            fn_8011E33C(pBest->mpUnknown0->mpUnknown60, pBest->mpUnknown60, 8);
                        }
                    }
                    pBest->mpUnknown0->mUnknown68 = 0.0f;
                    fn_8011D8B4((Entry_8011AFCC *)pBest);
                }
                pEntry = pA;
            } else {
                pEntry++;
            }
        }
    } while (changed);
}
}

extern "C" {
int fn_8011D558(Vector_80039F5C *p, Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pC)
{
    float d0 = p->mX * (pC->mY - pB->mY) + pC->mX * (pB->mY - p->mY) + pB->mX * (p->mY - pC->mY);
    float d1 = pB->mX * (p->mY - pA->mY) + p->mX * (pA->mY - pB->mY) + pA->mX * (pB->mY - p->mY);
    float d2 = pA->mX * (pB->mY - pC->mY) + pB->mX * (pC->mY - pA->mY) + pC->mX * (pA->mY - pB->mY);
    float d3 = pC->mX * (pA->mY - p->mY) + pA->mX * (p->mY - pC->mY) + p->mX * (pC->mY - pA->mY);

    if ((d0 >= 0.0f && d1 >= 0.0f && d2 >= 0.0f && d3 >= 0.0f)
        || (d0 <= 0.0f && d1 <= 0.0f && d2 <= 0.0f && d3 <= 0.0f)) {
        return 1;
    }
    return 0;
}
}

extern "C" {
void fn_8011D654(Entry_8011AFCC *pEntries)
{
    Pair_8011BAE0 pair;

    pair.mUnknown0 = -fn_80178A08();
    pair.mUnknown4 = fn_80177FE0().mY;
    fn_8011B83C((Entry_8011AFCC_8011B4F8 *)pEntries, pair);
    for (; pEntries->mpUnknown60 != 0 && pEntries[1].mpUnknown60 != 0; pEntries++) {
        Object_80039F5C *pA = pEntries->mpUnknown60;
        Object_80039F5C *pB = pEntries[1].mpUnknown60;

        if ((pA->mUnknown1052 == 1 && pB->mUnknown1052 == 1) ||
            (pA->mUnknown1052 == 2 && pB->mUnknown1052 == 2 && lbl_803EB028->mUnknown84 < 20)) {
            int modeA = pA->mUnknown1032;
            int crossed = 0;
            int modeB = pB->mUnknown1032;
            Object_80039F5C *pOtherA;
            Object_80039F5C *pOtherB;

            if (modeA == 7) {
                pOtherA = fn_8009BCE8(&pA->mUnknown1040);
            } else {
                pOtherA = fn_8009BCE8(&pA->mUnknown1036);
            }
            if (modeB == 7) {
                pOtherB = fn_8009BCE8(&pB->mUnknown1040);
            } else {
                pOtherB = fn_8009BCE8(&pB->mUnknown1036);
            }
            switch (modeA) {
            case 2:
            case 3:
            case 7:
                switch (modeB) {
                case 2:
                case 3:
                case 7:
                    if (pA->mUnknown8 == 255 && pB->mUnknown8 == 255 &&
                        fn_8011D558(&pA->mMotion.mPos, &pOtherA->mMotion.mPos, &pB->mMotion.mPos,
                                    &pOtherB->mMotion.mPos)) {
                        crossed = 1;
                    }
                    break;
                }
                break;
            }
            if (crossed) {
                Object_80039F5C *pTargetA = fn_8009BCE8(&pA->mUnknown1036);
                Object_80039F5C *pTargetB = fn_8009BCE8(&pB->mUnknown1036);

                if (modeA == 7) {
                    fn_8011E1BC(pA, pTargetA, pOtherB, 7);
                } else {
                    fn_8011E1BC(pA, pOtherB, 0, modeA);
                }
                if (modeB == 7) {
                    fn_8011E1BC(pB, pTargetB, pOtherA, 7);
                } else {
                    fn_8011E1BC(pB, pOtherA, 0, modeB);
                }
                switch (modeA) {
                case 7:
                    fn_8011E33C(pTargetA, pA, 4);
                case 2:
                case 3:
                    fn_8011E33C(pOtherB, pA, 8);
                    break;
                }
                switch (modeB) {
                case 7:
                    fn_8011E33C(pTargetB, pB, 4);
                case 2:
                case 3:
                    fn_8011E33C(pOtherA, pB, 8);
                    break;
                }
            }
        }
    }
}
}

extern "C" {
void fn_8011D8B4(Entry_8011AFCC *pEntries)
{
    while (pEntries->mpUnknown60 != 0) {
        *pEntries = pEntries[1];
        pEntries++;
    }
}
}

extern "C" {
void fn_8011D930(Entry_8011AFCC *pA, Entry_8011AFCC *pB, Pair_8011BAE0 pairB, Pair_8011BAE0 pairA)
{
    MemFill(pA, 8 * sizeof(Entry_8011AFCC), 0, 4);
    MemFill(pB, 8 * sizeof(Entry_8011AFCC), 0, 4);
    fn_8011B83C((Entry_8011AFCC_8011B4F8 *)pA, pairA);
    fn_8011B6E8((Entry_8011AFCC_8011B4F8 *)pB, pairB);
}
}

extern "C" {
void fn_8011D9B8(void)
{
    Entry_8011AFCC listB[8];
    Entry_8011AFCC listA[8];
    Pair_8011BAE0 pair;

    fn_8011BAE0(&pair);
    fn_8011D930(listA, listB, pair, pair);
    fn_8011D0BC((Entry_8011AFCC_8011BCDC *)listA, (Entry_8011AFCC_8011BCDC *)listB, pair);
    fn_8011D654(listA);
}
}

extern "C" {
void fn_8011DA40(void)
{
    int team = fn_80178308();
    unsigned char side;

    lbl_803EB028->mUnknown84++;
    for (side = 0; side < 2; side++) {
        unsigned int count = fn_80178D70(side);
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *p = PlyrGet(side, i);
            Block_8011DBC8 *pBlock40 = &p->mUnknown1072;
            Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown1036);

            switch (p->mUnknown1032) {
            case 4:
            case 7:
                p->mUnknown1048 = p->mUnknown1036;
                if (side == team) {
                    if (--p->mBlock1032.mUnknown102 < 0) {
                        fn_8011E1BC(p, pOther, 0, 2);
                        fn_8011E33C(pOther, p, 8);
                    }
                } else {
                    p->mBlock1032.mUnknown102++;
                }
                break;
            case 3:
                if (p->mBlock1032.mUnknown102 > 20 && fn_8011F1CC()) {
                    p->mUnknown1032 = 2;
                }
            default:
                if (++p->mBlock1032.mUnknown102 > 10) {
                    p->mUnknown1048 = 0;
                }
                break;
            }
            if (--pBlock40->mUnknown52 <= 0) {
                pBlock40->mUnknown52 = 0;
                fn_8011DBC8(p, pBlock40);
            }
        }
    }
}
}

extern "C" {
void fn_8011DBC0(Object_80039F5C *p)
{
}
}

extern "C" {
void fn_8011DBC4(Object_80039F5C *p)
{
}
}

extern "C" {
void fn_8011DBC8(Object_80039F5C *p, Block_8011DBC8 *pBlock)
{
    pBlock->mUnknown40 = 1.0f;
    pBlock->mUnknown44 = 1.0f;
    pBlock->mUnknown48 = 1.0f;
}
}

extern "C" {
int fn_8011DBE0(Object_80039F5C *p, Object_80039F5C *pOther)
{
    unsigned int id = fn_801BE648(p->mpUnknown792);
    unsigned int otherId = fn_801BE648(pOther->mpUnknown792);

    if (otherId == id) {
        if (fn_8011DC68(id) && fn_8011DC68(otherId)) {
            return 1;
        }
        switch (otherId) {
        case 146:
        case 147:
        case 148:
        case 149:
        case 150:
        case 151:
        case 161:
            return 1;
        }
    }
    return 0;
}
}

extern "C" {
int fn_8011DC68(unsigned int id)
{
    switch (id) {
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 59:
    case 60:
    case 106:
    case 107:
        return 1;
    }
    return 0;
}
}

extern "C" {
int fn_8011DCA8(unsigned int id)
{
    switch (id) {
    case 49:
    case 52:
    case 55:
        return 1;
    }
    return 0;
}
}

extern "C" {
void fn_8011DCDC(void)
{
    if (fn_8011F1CC()) {
        Object_80039F5C *p = PlyrFindByRole(fn_80178308(), 1, 0);
        int index = 0xFFFF;
        Object_80039F5C *pOther = PlyrFindByRole(fn_80178308(), 2, 0);
        int otherIndex = 0xFFFF;
        int hasOther;

        if (p) {
            index = fn_800F06F4(0, p->mQueue, 31, 0xFFFF);
        }
        if (pOther) {
            otherIndex = fn_800F06F4(0, pOther->mQueue, 31, 0xFFFF);
        }
        hasOther = otherIndex != 0xFFFF;
        if ((index != 0xFFFF && !hasOther) || (index == 0xFFFF && hasOther)) {
            Point_8017886C ball;
            float x;

            if (otherIndex != 0xFFFF && index == 0xFFFF) {
                p = pOther;
            }
            ball = fn_80177FE0();
            if (fabsf(p->mMotion.mPos.mX - ball.mX) < 0.75f) {
                index = fn_800F06F4(0, p->mQueue, 3, 0xFFFF);
                if (index == 0xFFFF) {
                    index = fn_800F06F4(0, p->mQueue, 4, 0xFFFF);
                    if (index == 0xFFFF) {
                        index = fn_800F06F4(0, p->mQueue, 27, 0xFFFF);
                    }
                }
                if (index == 0xFFFF) {
                    x = p->mMotion.mPos.mX;
                } else {
                    int angle = p->mpState[index].mUnknown2 << 17;

                    if (angle > 0x400000 && angle < 0xC00000) {
                        x = p->mMotion.mPos.mX - 2.0f;
                    } else {
                        x = p->mMotion.mPos.mX + 2.0f;
                    }
                }
            } else {
                x = p->mMotion.mPos.mX;
            }
            if (x < ball.mX) {
                lbl_803EB028->mUnknown90 = 1;
            } else {
                lbl_803EB028->mUnknown90 = 2;
            }
        }
    } else {
        lbl_803EB028->mUnknown90 = 0;
    }
}
}

extern "C" {
void fn_8011DF3C(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EB028, sizeof(Block_803EB028), 0, 0x626C636B);

    fn_8023816C(pHandle);
    fn_802381E0(pHandle);
}
}

extern "C" {
void fn_8011DF8C(void)
{
}
}

extern "C" {
void fn_8011DF90(void)
{
    unsigned char side;
    int team;

    memset(lbl_803EB028->mUnknown4, 0, sizeof(lbl_803EB028->mUnknown4));
    lbl_803EB028->mUnknown84 = 0;
    lbl_803EB028->mUnknown90 = 0;
    fn_8011E938(0);
    team = fn_80178308();
    for (side = 0; side < 2; side++) {
        unsigned int count = fn_80178D18(side);
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *p = PlyrGet(team, i);

            memset(&p->mBlock1032, 0, sizeof(p->mBlock1032));
            fn_8011DBC8(p, &p->mUnknown1072);
            p->mUnknown1139 = 5;
            p->mUnknown1138 = 0;
        }
        team = fn_80178320();
    }
}
}

extern "C" {
void fn_8011E068(void)
{
    int team = fn_80178308();
    unsigned int count = fn_80178D70(team);
    unsigned char i;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = PlyrGet(team, i);

        if (p->mpState->mId == 51) {
            if (p->mpState[1].mId == 33) {
                fn_8011E1BC(p, 0, 0, 1);
                fn_8011E3EC(p, 2);
            } else if (p->mpState[1].mId == 31) {
                fn_8011E1BC(p, 0, 0, 1);
                fn_8011E3EC(p, 1);
            }
        }
    }
    fn_8011DCDC();
    lbl_803EB028->mUnknown89 = 1;
}
}

extern "C" {
void fn_8011E13C(void)
{
    int mode = fn_800AD9B4();

    if (mode == 3 || mode == 4) {
        fn_8011DA40();
        fn_8011D9B8();
        fn_8011893C();
        fn_80119020();
        fn_80119478();
        fn_801194F0();
        fn_80119B98();
        fn_8011AB38();
    }
}
}

extern "C" {
unsigned int fn_8011E188(void)
{
    return lbl_803EB028->mUnknown84;
}
}

extern "C" {
void fn_8011E194(Object_80039F5C *p, unsigned char mask)
{
    Block_8011E240 *pBlock = &p->mBlock1032;

    pBlock->mUnknown100 |= mask;
}
}

extern "C" {
void fn_8011E1A8(Object_80039F5C *p, unsigned char mask)
{
    Block_8011E240 *pBlock = &p->mBlock1032;

    pBlock->mUnknown100 &= ~mask;
}
}

extern "C" {
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value)
{
    Block_8011E240 *pBlock = &p->mBlock1032;

    fn_8011E240(p);
    pBlock->mUnknown0 = value;
    pBlock->mUnknown102 = 0;
    pBlock->mUnknown104 = 0;
    pBlock->mUnknown105 = 0;
    pBlock->mUnknown94 = 0;
    fn_8009BD2C(pA, &pBlock->mUnknown4);
    fn_8009BD2C(pB, &pBlock->mUnknown8);
    if (pBlock->mUnknown12 == 0) {
        fn_8009BD2C(pA, &pBlock->mUnknown12);
    }
}
}

extern "C" {
void fn_8011E240(Object_80039F5C *p)
{
    Block_8011E240 *pBlock = &p->mBlock1032;
    Object_80039F5C *pOther;
    int ref;

    pBlock->mUnknown0 = 0;
    pBlock->mUnknown102 = 0;
    pBlock->mUnknown104 = 0;
    pBlock->mUnknown105 = 0;
    pBlock->mUnknown94 = 0;
    pOther = fn_8009BCE8(&pBlock->mUnknown4);
    if (pOther) {
        PlyrCollideRemoveExempt(p, pOther);
        PlyrCollideRemoveExempt(pOther, p);
        fn_8009BD2C(p, &ref);
        if (pOther->mUnknown1036 == ref) {
            fn_8011E3A4(pOther);
        }
    }
    fn_8009BD2C(0, &pBlock->mUnknown4);
    pOther = fn_8009BCE8(&pBlock->mUnknown8);
    if (pOther) {
        PlyrCollideRemoveExempt(p, pOther);
        PlyrCollideRemoveExempt(pOther, p);
        fn_8009BD2C(p, &ref);
        if (pOther->mUnknown1036 == ref) {
            fn_8011E3A4(pOther);
        }
    }
    fn_8009BD2C(0, &pBlock->mUnknown8);
}
}

extern "C" {
void fn_8011E33C(Object_80039F5C *p, Object_80039F5C *pOther, int value)
{
    Block_8011E240 *pBlock = &p->mBlock1032;

    pBlock->mUnknown94 = 0;
    pBlock->mUnknown0 = value;
    pBlock->mUnknown102 = 0;
    fn_8009BD2C(pOther, &pBlock->mUnknown4);
    if (pBlock->mUnknown12 == 0) {
        fn_8009BD2C(pOther, &pBlock->mUnknown12);
    }
}
}

extern "C" {
void fn_8011E3A4(Object_80039F5C *p)
{
    Block_8011E240 *pBlock = &p->mBlock1032;

    pBlock->mUnknown0 = 0;
    pBlock->mUnknown102 = 0;
    pBlock->mUnknown104 = 0;
    pBlock->mUnknown105 = 0;
    pBlock->mUnknown94 = 0;
    fn_8009BD2C(0, &pBlock->mUnknown4);
}
}

extern "C" {
void fn_8011E3EC(Object_80039F5C *p, int a)
{
    p->mUnknown1052 = a;
}
}

extern "C" {
int fn_8011E3F4(Object_80039F5C *p)
{
    int result = 0;
    Object_80039F5C *pOther;

    if (p->mUnknown1032 == 7) {
        pOther = fn_8009BCE8(&p->mUnknown1040);
    } else {
        pOther = fn_8009BCE8(&p->mUnknown1036);
    }

    switch (p->mUnknown1032) {
    case 2:
    case 3:
    case 4:
        if (fn_8022781C(&p->mMotion.mPos, &pOther->mMotion.mPos) < 2.1f) {
            result = fn_8011E484(p, pOther);
        }
        break;
    }
    return result;
}
}

extern "C" {
int fn_8011E484(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int result = 0;
    Object_800B26B0 *pMotion;

    if (fn_801787A0()) {
        return 0;
    }
    pMotion = &p->mMotion;
    switch (fn_801BE648(pOther->mpUnknown792)) {
    case 0x30:
    case 0xD0:
    case 0xD1:
        return 0;
    }
    if (pOther) {
        switch (pOther->mpState->mId) {
        case 10:
        case 11:
        case 12:
        case 17:
        case 32:
        case 50:
        case 58:
        case 94:
            break;
        default:
            switch (p->mpState->mId) {
            case 25:
            case 26:
                break;
            default:
                if (!(pOther->mFlags & 0x800) && !BallFindHeldBy(p)) {
                    Point_8017886C delta;
                    int angle;
                    int both;
                    int limit;

                    fn_80227690(&delta, &pOther->mMotion.mPos, &pMotion->mPos);
                    angle = fn_801CFE40(delta.mY, delta.mX);
                    if ((p->mFlags & 0x4000) && MathAngleDiff(p->mUnknown512.mUnknown4, angle) > 0x600000) {
                        return 0;
                    }
                    both = 0;
                    if (pOther->mUnknown1032 == 4 && (p->mUnknown1032 == 4 || p->mUnknown1032 == 7)) {
                        both = 1;
                    }
                    limit = 0x1C71C7;
                    if (both) {
                        limit = 0x2E38E3;
                    }
                    if (MathAngleDiff(pMotion->mFacing + fn_800C8BAC(p, 0), angle) < limit) {
                        angle = (angle + 0x800000) & 0xFFFFFF;
                        if ((!pOther->mUnknown512.mUnknown14 || MathAngleDiff(pOther->mUnknown512.mUnknown4, angle) <= 0x5C71C6)
                            && fn_8022781C(&pMotion->mPos, &pOther->mMotion.mPos) < 2.1f) {
                            int difference = MathAngleDiff(pMotion->mFacing + fn_800C8BAC(p, 0),
                                                         pOther->mMotion.mFacing + fn_800C8BAC(pOther, 0));
                            Vector_80039F5C joint;
                            Vector_80039F5C otherJoint;
                            Vector_80039F5C angles;
                            float reach;

                            if (!both) {
                                fn_8009BF5C(p, 11, &joint, &angles);
                                fn_8009BF5C(pOther, 11, &otherJoint, &angles);
                                if (difference > 0x400000) {
                                    reach = fabsf(fn_801CFB94(difference) * 0.39999998f) + 0.85f;
                                } else {
                                    reach = 0.85f;
                                }
                                if (fn_8011DBE0(p, pOther)) {
                                    reach *= 1.2f;
                                } else if (fn_8011F228() && !fn_801783AC(0)) {
                                    reach = 1.25f;
                                }
                            }
                            if (both || fn_8022781C(&joint, &otherJoint) < reach) {
                                if (fn_8011DBE0(p, pOther) || difference > 0x3C71C7) {
                                    result = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}
}

extern "C" {
void fn_8011E7CC(Object_80039F5C *p, int which, float amount)
{
    Block_8011DBC8 *pBlock = &p->mUnknown1072;

    switch (which) {
    case 0:
        pBlock->mUnknown40 += amount;
        pBlock->mUnknown40 = pBlock->mUnknown40 < 0.0f ? 0.0f : pBlock->mUnknown40;
        break;
    case 1:
        pBlock->mUnknown44 += amount;
        pBlock->mUnknown44 = pBlock->mUnknown44 < 0.0f ? 0.0f : pBlock->mUnknown44;
        break;
    case 2:
        pBlock->mUnknown48 += amount;
        pBlock->mUnknown48 = pBlock->mUnknown48 < 0.0f ? 0.0f : pBlock->mUnknown48;
        break;
    }
}
}

extern "C" {
void fn_8011E884(Object_80039F5C *p, int a)
{
    p->mUnknown1072.mUnknown52 = a;
}
}

extern "C" {
int fn_8011E88C(Object_80039F5C *p)
{
    return p->mUnknown1072.mUnknown52 != 0;
}
}

extern "C" {
int fn_8011E8A4(Object_80039F5C *p)
{
    int result = 0;

    switch (p->mUnknown1032) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 8:
        result = 1;
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        break;
    }
    return result;
}
}

extern "C" {
void fn_8011E8D8(Object_80039F5C *p)
{
    fn_8011E3EC(p, 0);
    if (p->mIdBytes[2] == fn_80178308()) {
        fn_8011E240(p);
    } else {
        Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown1036);

        if (pOther) {
            fn_8011E240(pOther);
        }
    }
}
}

extern "C" {
void fn_8011E938(Object_80039F5C *p)
{
    fn_8009BD2C(p, &lbl_803EB028->mUnknown0);
}
}

extern "C" {
int fn_8011E95C(void)
{
    int result = 0;

    if (fn_8011F1A4() && fn_8011F4C8() <= 3) {
        result = lbl_803EB028->mUnknown84 < 60;
    }
    return result;
}
}

extern "C" {
int fn_8011E9B4(Object_80039F5C *p)
{
    int result = 0;

    switch (p->mUnknown1032) {
    case 4:
    case 5:
    case 6:
    case 7:
        result = 1;
        break;
    }
    return result;
}
}

extern "C" {
int fn_8011E9D8(State_80039F5C *pState)
{
    unsigned int c = 0xFFFF;
    int result = 0;

    if (pState) {
        unsigned int a = fn_800F06F4(0, pState, 31, 0xFFFF);
        unsigned int b = fn_800F06F4(0, pState, 47, 0xFFFF);

        if (a != 0xFFFF || b != 0xFFFF) {
            c = fn_800F06F4(0, pState, 19, 0xFFFF);
        }
        if (a != 0xFFFF && c != 0xFFFF && a < c) {
            result = 1;
        }
        if (b != 0xFFFF && c != 0xFFFF && b < c) {
            result = 1;
        }
    }
    return result;
}
}

extern "C" {
int fn_8011EAC0(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Block_8011E240 *pBlock = &p->mBlock1032;
    Block_8011E240 *pOtherBlock = &pOther->mBlock1032;
    Block_8011E240 saved;
    Block_8011E240 otherSaved;
    Point_8017886C point;
    unsigned char team;
    unsigned char i;

    saved.mUnknown0 = pBlock->mUnknown0;
    saved.mUnknown4 = pBlock->mUnknown4;
    otherSaved.mUnknown0 = pOtherBlock->mUnknown0;
    otherSaved.mUnknown4 = pOtherBlock->mUnknown4;
    p->mUnknown1032 = 2;
    fn_8009BD2C(pOther, &p->mUnknown1036);
    pOther->mUnknown1032 = 8;
    fn_8009BD2C(p, &pOther->mUnknown1036);
    fn_80227538(&point, (p->mMotion.mFacing + 0x800000) & 0xFFFFFF, 2.0f);
    fn_80227638(&point, &point, &p->mMotion.mPos);
    if (fn_80118B4C(p, (Pair_8011BAE0 *)&point)) {
        for (team = 0; team <= 1; team++) {
            unsigned int count = fn_80178D70(team);

            for (i = 0; i < count; i++) {
                Object_80039F5C *pPlayer = PlyrGet(team, i);

                if (pPlayer != p && pOther != pPlayer) {
                    Block_8011E240 *pPlayerBlock = &pPlayer->mBlock1032;
                    Object_80039F5C *pRef;

                    if (pPlayer->mUnknown1032 == 2) {
                        pRef = fn_8009BCE8(&pPlayer->mUnknown1036);
                        if (pRef == p || pRef == pOther) {
                            pPlayer->mUnknown1032 = 1;
                            pPlayerBlock->mUnknown4 = 0;
                        }
                    } else if (pPlayer->mUnknown1032 == 8) {
                        pRef = fn_8009BCE8(&pPlayer->mUnknown1036);
                        if (pRef == p || pRef == pOther) {
                            pPlayer->mUnknown1032 = 0;
                            pPlayerBlock->mUnknown4 = 0;
                        }
                    }
                }
            }
        }
        return 1;
    }
    p->mUnknown1032 = saved.mUnknown0;
    pBlock->mUnknown4 = saved.mUnknown4;
    pOther->mUnknown1032 = otherSaved.mUnknown0;
    pOtherBlock->mUnknown4 = otherSaved.mUnknown4;
    return 0;
}
}

extern "C" {
int fn_8011EC68(Object_80039F5C *p, Object_80039F5C *pOther)
{
    int result = 0;
    Object_80039F5C *pCarrier;

    if (fn_8011A994(p, pOther) && (pCarrier = BallGetCurrentHolder()) != 0) {
        Point_8017886C delta;
        int angle;

        fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX);
        if (MathAngleDiff(pOther->mUnknown512.mUnknown4, angle) >= (int)(lbl_803EB024 * (16777216.0f / 360.0f))) {
            Point_8017886C toBall;
            Point_8017886C ball;

            ball = fn_80177FE0();
            fn_80227690(&toBall, &ball, &pOther->mMotion.mPos);
            angle = fn_801CFE40(toBall.mY, toBall.mX);
            if (MathAngleDiff(pOther->mUnknown512.mUnknown4, angle) > 0x400000 || !fn_8011F1CC() ||
                (pCarrier->mFlags & 0x8000)) {
                Query_800CE770 query;

                fn_800CE770(&query);
                query.mUnknown52 = 161;
                query.mUnknown44 = 0.8f;
                query.mUnknown36 = 0xE38E3;
                query.mpUnknown0 = p;
                query.mpUnknown4 = pOther;
                query.mUnknown54 = fn_8011EE18(pOther, pCarrier);
                if (fn_800CE4A8(&query)) {
                    fn_8011E1BC(p, pOther, 0, 5);
                    result = 1;
                    fn_8011E33C(pOther, p, 5);
                }
            }
        }
    }
    return result;
}
}

extern "C" {
unsigned char fn_8011EE18(Object_80039F5C *p, Object_80039F5C *pCarrier)
{
    int degrees = (int)(((p->mUnknown512.mUnknown4 - p->mMotion.mFacing + 0x1000000) & 0xFFFFFF) * (360.0f / 16777216.0f));
    int rest = degrees % 45;
    int result;

    if (rest > 22) {
        degrees += 45 - rest;
    } else {
        degrees -= rest;
    }
    degrees = degrees < 90 ? 90 : degrees > 270 ? 270 : degrees;
    switch (degrees / 45 - 1) {
    case 0:
        result = 4;
        break;
    case 1:
        result = 7;
        break;
    case 2:
        result = 10;
        break;
    case 3: {
        Point_8017886C delta;
        int angle;

        fn_80227690(&delta, &pCarrier->mMotion.mPos, &p->mMotion.mPos);
        angle = fn_801CFE40(delta.mY, delta.mX);
        fn_80227384(&delta, &delta, p->mMotion.mFacing);
        angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        result = 17;
        if (angle <= 0x7FFFFF) {
            result = 18;
        }
        break;
    }
    case 4:
        result = 16;
        break;
    case 5:
        result = 14;
        break;
    default:
        result = 4;
        break;
    }
    return result;
}
}

extern "C" {
int fn_8011EFD4(void *p, void *q)
{
    State_803EB098 *pState = (State_803EB098 *)p;
    State_803EB098 *pOther = (State_803EB098 *)q;
    int result;

    if (pOther) {
        result = (pState->mUnknown4 != pOther->mUnknown4) | (pState->mUnknown0 != pOther->mUnknown0);
        result |= memcmp(&pState->mUnknown8, &pOther->mUnknown8, sizeof(pState->mUnknown8));
    } else {
        result = fn_80238278(pState, 576 + pState->mUnknown572 * sizeof(Record_8011F4F8), 0);
    }
    return result;
}
}

extern "C" {
void fn_8011F068(void)
{
    Point_8017886C point;

    point = fn_80177FE0();
    if (lbl_803EB098->mUnknown4 <= 13) {
        lbl_803EB098->mUnknown0 = point.mX + lbl_802DB004[lbl_803EB098->mUnknown4];
    } else {
        lbl_803EB098->mUnknown0 = point.mX;
    }
}
}

extern "C" {
void fn_8011F0D8(void)
{
    unsigned char count = BallsGetCount();
    void *pHandle = fn_80238174(0, (void **)&lbl_803EB098, 576 + count * sizeof(Record_8011F4F8), 0, 0x70696E66);
    State_803EB098 *pState;

    fn_80238234(pHandle, 0, 0, 0, fn_8011EFD4);
    pState = (State_803EB098 *)fn_8023816C(pHandle);
    pState->mUnknown4 = 0;
    pState->mUnknown0 = 0.0f;
    fn_800A5A68(pState->mUnknown528);
    pState->mUnknown572 = count;
    fn_802381E0(pHandle);
}
}

extern "C" {
void fn_8011F174(void)
{
    fn_800A5A88(lbl_803EB098->mUnknown528);
    lbl_803EB098 = 0;
}
}

extern "C" {
int fn_8011F1A4(void)
{
    return fn_801650BC(PlayBookGetPlay(fn_80178308()));
}
}

extern "C" {
int fn_8011F1CC(void)
{
    return fn_801650DC(PlayBookGetPlay(fn_80178308()));
}
}

extern "C" {
int fn_8011F1F4(void)
{
    return PlayBookGetPlay(fn_80178308())->mUnknown17 == 14;
}
}

extern "C" {
int fn_8011F228(void)
{
    return PlayBookGetPlay(fn_80178308())->mUnknown17 == 16;
}
}

extern "C" {
int fn_8011F25C(void)
{
    return PlayBookGetPlay(fn_80178308())->mUnknown14 == 4;
}
}

extern "C" {
int fn_8011F290(void)
{
    return PlayBookGetPlay(fn_80178308())->mUnknown14 == 18;
}
}

extern "C" {
int fn_8011F2C4(void)
{
    return PlayBookGetPlay(fn_80178308())->mUnknown17 == 2;
}
}

extern "C" {
int fn_8011F2F8(void)
{
    return PlayBookGetPlay(fn_80178308())->mUnknown17 == 5;
}
}

extern "C" {
int fn_8011F32C(void)
{
    return fn_801650FC(PlayBookGetPlay(fn_80178308()));
}
}

extern "C" {
int fn_8011F354(void)
{
    return fn_801650FC(PlayBookGetPlay(fn_80178348()));
}
}

extern "C" {
int fn_8011F37C(void)
{
    return (PlayBookGetPlay(fn_80178308())->mUnknown18 >> 16) & 1;
}
}

extern "C" {
void fn_8011F3A8(void)
{
    if (fn_8011F1A4()) {
        lbl_803EB098->mUnknown4 = PlayBookGetPlay(fn_80178308())->mUnknown1C[0][0];
        if (PlayBookGetFormation(fn_80178308())->mUnknown8.mUnknownF) {
            if (lbl_803EB098->mUnknown4 & 1) {
                lbl_803EB098->mUnknown4 = lbl_803EB098->mUnknown4 - 1;
            } else {
                lbl_803EB098->mUnknown4 = lbl_803EB098->mUnknown4 + 1;
            }
        }
        fn_8011F068();
        lbl_803EB098->mUnknown5 = 1;
    } else {
        lbl_803EB098->mUnknown5 = 0;
        lbl_803EB098->mUnknown4 = 0;
        lbl_803EB098->mUnknown0 = fn_80177FE0().mX;
    }
}
}

extern "C" {
void fn_8011F45C(int a)
{
    if (lbl_803EB098->mUnknown5) {
        lbl_803EB098->mUnknown4 = a;
    } else if (PlayBookGetPlay(fn_80178308())->mUnknown14 == 2) {
        lbl_803EB098->mUnknown4 = a;
        lbl_803EB098->mUnknown5 = 1;
    }
    fn_8011F068();
}
}

extern "C" {
unsigned char fn_8011F4C8(void)
{
    return lbl_803EB098->mUnknown4;
}
}

extern "C" {
float fn_8011F4D4(void)
{
    return lbl_803EB098->mUnknown0;
}
}

extern "C" {
Record_8011F4E0 *fn_8011F4E0(void)
{
    return &lbl_803EB098->mUnknown8;
}
}

extern "C" {
void *fn_8011F4EC(void)
{
    return lbl_803EB098->mUnknown56;
}
}

extern "C" {
Record_8011F4F8 *fn_8011F4F8(int index)
{
    return &lbl_803EB098->mUnknown576[index];
}
}

extern "C" {
void *fn_8011F50C(void)
{
    return lbl_803EB098->mUnknown528;
}
}

extern "C" {
Record_8011F518 *fn_8011F518(void)
{
    return &lbl_803EB098->mUnknown512;
}
}

extern "C" {
int fn_8011F524(void)
{
    return fn_80165098(PlayBookGetPlay(fn_80178348()));
}
}

extern "C" {
Object_80039F5C *fn_8011F54C(void)
{
    return PlaySetGetKeyPlayer(PlayBookGetFormation(fn_80178308()));
}
}

extern "C" {
void fn_8011F574(void)
{
    unsigned char i;

    for (i = 0; i < 2; i++) {
        lbl_803EB098->mUnknown6[i] = 0;
    }
}
}

extern "C" {
unsigned char fn_8011F59C(int index)
{
    return lbl_803EB098->mUnknown6[index];
}
}

extern "C" {
void fn_8011F5AC(int index)
{
    unsigned char *pCount = lbl_803EB098->mUnknown6;

    if (pCount[index] < 255) {
        pCount[index]++;
    }
}
}

extern "C" {
void fn_8011F5CC(Lookup_8012078C *pLookup)
{
    short count = pLookup->mUnknown16;

    pLookup->mpUnknown0 = (unsigned char *)fn_801D2B7C(count, 0, 0);
    memset(pLookup->mpUnknown0, 0, count);
    pLookup->mpUnknown4 = (unsigned char *)fn_801D2B7C(count, 0, 0);
    memset(pLookup->mpUnknown4, 0, count);
    pLookup->mpUnknown8 = (Entry_8011FBE0 *)fn_801D2B7C(pLookup->mUnknown16 * sizeof(Entry_8011FBE0), 0, 0);
    memset(pLookup->mpUnknown8, 0, pLookup->mUnknown16 * sizeof(Entry_8011FBE0));
    pLookup->mpUnknown12 = (int *)fn_801D2B7C(pLookup->mUnknown16 * sizeof(int), 0, 0);
    memset(pLookup->mpUnknown12, 0, pLookup->mUnknown16 * sizeof(int));
}
}

extern "C" {
int fn_8011F698(void *p, int value)
{
    fn_8011F5CC((Lookup_8012078C *)p);
    return 0;
}
}

extern "C" {
int fn_8011F6BC(void *p, int value)
{
    Lookup_8012078C *pLookup = (Lookup_8012078C *)p;

    fn_801D2BD0(pLookup->mpUnknown0);
    pLookup->mpUnknown0 = 0;
    fn_801D2BD0(pLookup->mpUnknown4);
    pLookup->mpUnknown4 = 0;
    fn_801D2BD0(pLookup->mpUnknown8);
    pLookup->mpUnknown8 = 0;
    fn_801D2BD0(pLookup->mpUnknown12);
    pLookup->mpUnknown12 = 0;
    return 0;
}
}

extern "C" {
int fn_8011F71C(void *p, void *q)
{
    Lookup_8012078C *pLookup = (Lookup_8012078C *)p;
    Lookup_8012078C *pOther = (Lookup_8012078C *)q;
    int result = 0;

    if (pOther) {
        result |= pLookup->mUnknown16 != pOther->mUnknown16;
        result |= pLookup->mUnknown18 != pOther->mUnknown18;
        result |= pLookup->mUnknown19 != pOther->mUnknown19;
        result |= pLookup->mUnknown20 != pOther->mUnknown20;
        result |= fn_80238258(pLookup->mpUnknown0 + ((char *)pLookup - (char *)lbl_803EB09C),
                              pOther->mpUnknown0 + ((char *)pOther - (char *)lbl_803EB09C),
                              pLookup->mUnknown16);
        result |= fn_80238258(pLookup->mpUnknown4 + ((char *)pLookup - (char *)lbl_803EB09C),
                              pOther->mpUnknown4 + ((char *)pOther - (char *)lbl_803EB09C),
                              pLookup->mUnknown16);
        result |= fn_80238258((char *)pLookup->mpUnknown8 + ((char *)pLookup - (char *)lbl_803EB09C),
                              (char *)pOther->mpUnknown8 + ((char *)pOther - (char *)lbl_803EB09C),
                              pLookup->mUnknown16 * sizeof(Entry_8011FBE0));
        result |= fn_80238258((char *)pLookup->mpUnknown12 + ((char *)pLookup - (char *)lbl_803EB09C),
                              (char *)pOther->mpUnknown12 + ((char *)pOther - (char *)lbl_803EB09C),
                              pLookup->mUnknown16 * sizeof(int));
    } else {
        result = fn_80238278(pLookup, sizeof(Lookup_8012078C), 0);
        result = fn_80238278(pLookup->mpUnknown0 + ((char *)pLookup - (char *)lbl_803EB09C),
                             pLookup->mUnknown16, result);
        result = fn_80238278(pLookup->mpUnknown4 + ((char *)pLookup - (char *)lbl_803EB09C),
                             pLookup->mUnknown16, result);
        result = fn_80238278((char *)pLookup->mpUnknown8 + ((char *)pLookup - (char *)lbl_803EB09C),
                             pLookup->mUnknown16 * sizeof(Entry_8011FBE0), result);
        result = fn_80238278((char *)pLookup->mpUnknown12 + ((char *)pLookup - (char *)lbl_803EB09C),
                             pLookup->mUnknown16 * sizeof(int), result);
    }
    return result;
}
}

extern "C" {
int fn_8011F904(void *p, void *pBuffer)
{
    Lookup_8012078C *pLookup = (Lookup_8012078C *)p;

    memcpy(pBuffer, pLookup, sizeof(Lookup_8012078C));
    pBuffer = (char *)pBuffer + sizeof(Lookup_8012078C);
    memcpy(pBuffer, pLookup->mpUnknown0, pLookup->mUnknown16);
    pBuffer = (char *)pBuffer + pLookup->mUnknown16;
    memcpy(pBuffer, pLookup->mpUnknown4, pLookup->mUnknown16);
    pBuffer = (char *)pBuffer + pLookup->mUnknown16;
    memcpy(pBuffer, pLookup->mpUnknown8, pLookup->mUnknown16 * sizeof(Entry_8011FBE0));
    pBuffer = (char *)pBuffer + pLookup->mUnknown16 * sizeof(Entry_8011FBE0);
    memcpy(pBuffer, pLookup->mpUnknown12, pLookup->mUnknown16 * sizeof(int));
    return 1;
}
}

extern "C" {
int fn_8011F99C(void *p, void *pBuffer)
{
    Lookup_8012078C *pLookup = (Lookup_8012078C *)p;
    void *pData;

    *pLookup = *(Lookup_8012078C *)pBuffer;
    pData = (char *)pBuffer + sizeof(Lookup_8012078C);
    memcpy(pLookup->mpUnknown0, pData, pLookup->mUnknown16);
    pBuffer = (char *)pData + pLookup->mUnknown16;
    memcpy(pLookup->mpUnknown4, pBuffer, pLookup->mUnknown16);
    pBuffer = (char *)pBuffer + pLookup->mUnknown16;
    memcpy(pLookup->mpUnknown8, pBuffer, pLookup->mUnknown16 * sizeof(Entry_8011FBE0));
    pBuffer = (char *)pBuffer + pLookup->mUnknown16 * sizeof(Entry_8011FBE0);
    memcpy(pLookup->mpUnknown12, pBuffer, pLookup->mUnknown16 * sizeof(int));
    return 1;
}
}

extern "C" {
int fn_8011FA54(void *p)
{
    short count = lbl_803EB09C->mUnknown16;

    return sizeof(Lookup_8012078C) + count + count + count * sizeof(Entry_8011FBE0) + count * sizeof(int);
}
}

extern "C" {
int fn_8011FA78(void *pA, void *pB)
{
    int team = fn_80178320();
    float a = PlyrGet(team, *(char *)pA)->mMotion.mPos.mX;
    float b = PlyrGet(team, *(char *)pB)->mMotion.mPos.mX;

    if (a - b < 0.0f) {
        return -1;
    }
    return 0;
}
}

extern "C" {
int fn_8011FAFC(void *pA, void *pB)
{
    int team = fn_80178320();
    float a = PlyrGet(team, *(char *)pA)->mMotion.mPos.mY;
    float b = PlyrGet(team, *(char *)pB)->mMotion.mPos.mY;

    if (a - b < 0.0f) {
        return -1;
    }
    return 0;
}
}

extern "C" {
int fn_8011FB80(void *pA, void *pB)
{
    if (((Entry_8011FBE0 *)pA)->mUnknown0 - ((Entry_8011FBE0 *)pB)->mUnknown0 < 0.0f) {
        return -1;
    }
    return 0;
}
}

extern "C" {
void fn_8011FBA8(void *pA, void *pB)
{
    unsigned char *pFirst = (unsigned char *)pA;
    unsigned char *pSecond = (unsigned char *)pB;
    unsigned char value = *pFirst;

    *pFirst = *pSecond;
    *pSecond = value;
}
}

extern "C" {
void fn_8011FBBC(void *pA, void *pB)
{
    Entry_8011FBE0 *pFirst = (Entry_8011FBE0 *)pA;
    Entry_8011FBE0 *pSecond = (Entry_8011FBE0 *)pB;
    Entry_8011FBE0 entry = *pFirst;

    *pFirst = *pSecond;
    *pSecond = entry;
}
}

extern "C" {
void fn_8011FBE0(void)
{
    int team = fn_80178320();
    Object_80039F5C *pPlayer = BallGetCurrentHolder();
    Vector_80039F5C pos;
    unsigned char count;
    unsigned char i;

    if (pPlayer) {
        pos.mX = pPlayer->mMotion.mPos.mX;
        pos.mY = pPlayer->mMotion.mPos.mY;
    } else if (!BallGetLandingPoint(BallGetCurrent(), &pos)) {
        BallGetPosition(BallGetCurrent(), &pos);
    }
    count = fn_80178D70(team);
    for (i = 0; i < count; i++) {
        Entry_8011FBE0 *pEntry = &lbl_803EB09C->mpUnknown8[i];

        pEntry->mUnknown0 = fn_8022781C(&PlyrGet(team, i)->mMotion.mPos, &pos);
        pEntry->mUnknown4 = i;
    }
}
}

extern "C" {
void fn_8011FCA4(void)
{
    int count = fn_80178D70(fn_80178320());

    SortArray(1, lbl_803EB09C->mpUnknown0, count, 1, fn_8011FA78, fn_8011FBA8, 0, 0);
    SortArray(1, lbl_803EB09C->mpUnknown4, count, 1, fn_8011FAFC, fn_8011FBA8, 0, 0);
    fn_8011FBE0();
    SortArray(1, lbl_803EB09C->mpUnknown8, count, sizeof(Entry_8011FBE0), fn_8011FB80, fn_8011FBBC, 0, 1);
}
}

extern "C" {
int fn_8011FD64(unsigned short index)
{
    int result;

    switch (PlyrGet(fn_80178320(), index)->mUnknown2914) {
    case 0:
    case 7:
    case 13:
    case 14:
    case 15:
        result = 1;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 16:
    case 17:
    case 18:
        result = 2;
        break;
    case 5:
    case 6:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    default:
        result = 0;
        break;
    }
    if (fn_801486A0() == 2) {
        result = 1;
    }
    return result;
}
}

extern "C" {
void fn_8011FE0C(void)
{
    Point_8017886C origin;
    int low = 255;
    int high = 255;
    int team;
    unsigned int count;
    Object_80039F5C *pCarrier;
    short i;

    origin = fn_80177FE0();
    team = fn_80178320();
    fn_8011FCA4();
    count = fn_80178D70(team);
    if (count > 7) count = 7;
    for (i = 0; i < (int)count; i++) {
        lbl_803EB09C->mpUnknown12[i] = 0;
    }
    pCarrier = BallGetCurrentHolder();
    if (count <= 1) return;
    for (i = 0; i < (int)count; i++) {
        if (fn_8011FD64(lbl_803EB09C->mpUnknown0[i]) == 2 || fn_801486A0() == 2) {
            Object_80039F5C *p = PlyrGet(team, lbl_803EB09C->mpUnknown0[i]);
            if (!(p->mFlags & 0x800) &&
                (!pCarrier || !(p->mMotion.mPos.mY <= pCarrier->mMotion.mPos.mY)) &&
                (p->mUnknown1032 == 0 || p->mUnknown1032 == 8)) {
                low = lbl_803EB09C->mpUnknown0[i];
                break;
            }
        }
    }
    for (i = count - 1; i >= 0; i--) {
        if (fn_8011FD64(lbl_803EB09C->mpUnknown0[i]) == 2 || fn_801486A0() == 2) {
            Object_80039F5C *p = PlyrGet(team, lbl_803EB09C->mpUnknown0[i]);
            if (!(p->mFlags & 0x800) &&
                (!pCarrier || !(p->mMotion.mPos.mY <= pCarrier->mMotion.mPos.mY)) &&
                (p->mUnknown1032 == 0 || p->mUnknown1032 == 8)) {
                high = lbl_803EB09C->mpUnknown0[i];
                break;
            }
        }
    }
    if (pCarrier) {
        Vector_80039F5C *pPos = &pCarrier->mMotion.mPos;
        Object_80039F5C *pMiddle;
        int middle;

        if (pPos->mX - origin.mX > 0.0f) {
            lbl_803EB09C->mUnknown19 = 0;
        } else {
            lbl_803EB09C->mUnknown19 = 1;
        }
        middle = ((count + 1) >> 1) - 1;
        pMiddle = PlyrGet(team, lbl_803EB09C->mpUnknown4[middle]);
        if (!(pPos->mY >= pMiddle->mMotion.mPos.mY)) {
            if (lbl_803EB09C->mUnknown19 == 0) {
                if (low != 255) {
                    if (count > 2) {
                        lbl_803EB09C->mpUnknown12[low] = 3;
                    } else {
                        lbl_803EB09C->mpUnknown12[low] = 0;
                    }
                }
                if (high != 255) {
                    if (count > 2) {
                        lbl_803EB09C->mpUnknown12[high] = 4;
                    } else {
                        lbl_803EB09C->mpUnknown12[high] = 2;
                    }
                }
            } else {
                if (high != 255) {
                    if (count > 2) {
                        lbl_803EB09C->mpUnknown12[high] = 3;
                    } else {
                        lbl_803EB09C->mpUnknown12[high] = 0;
                    }
                }
                if (low != 255) {
                    if (count > 2) {
                        lbl_803EB09C->mpUnknown12[low] = 4;
                    } else {
                        lbl_803EB09C->mpUnknown12[low] = 2;
                    }
                }
            }
            if (fn_8011F1A4() || fn_801783AC(0)) {
                for (i = 0; i < (int)count; i++) {
                    if (lbl_803EB09C->mpUnknown12[i] == 0 && fn_8011FD64(i)) {
                        lbl_803EB09C->mpUnknown12[i] = 2;
                    }
                }
                for (i = count - 1; i >= 0; i--) {
                    unsigned char index = lbl_803EB09C->mpUnknown8[i].mUnknown4;
                    if (lbl_803EB09C->mpUnknown12[index] == 0 && fn_8011FD64(index) == 0) {
                        lbl_803EB09C->mpUnknown12[index] = 4;
                        break;
                    }
                }
            }
        } else {
            for (i = 0; i < (int)count; i++) {
                lbl_803EB09C->mpUnknown12[i] = 5;
            }
            if (lbl_803EB09C->mUnknown19 == 0) {
                if (low != 255 && !(PlyrGet(team, low)->mMotion.mPos.mY <= pCarrier->mMotion.mPos.mY)) {
                    lbl_803EB09C->mpUnknown12[low] = 3;
                }
            } else {
                if (high != 255 && !(PlyrGet(team, high)->mMotion.mPos.mY <= pCarrier->mMotion.mPos.mY)) {
                    lbl_803EB09C->mpUnknown12[high] = 3;
                }
            }
        }
    } else {
        if (lbl_803EB09C->mUnknown19 == 0) {
            if (low != 255) lbl_803EB09C->mpUnknown12[low] = 3;
            if (high != 255) lbl_803EB09C->mpUnknown12[high] = 4;
        } else {
            if (high != 255) lbl_803EB09C->mpUnknown12[high] = 3;
            if (low != 255) lbl_803EB09C->mpUnknown12[low] = 4;
        }
        for (i = 0; i < (int)count; i++) {
            if (fn_8011FD64(i) == 1) lbl_803EB09C->mpUnknown12[i] = 2;
        }
    }
}
}

extern "C" {
void fn_80120384(void)
{
    short i;
    int count;
    Vector_80039F5C pos;
    Vector_80039F5C velocity;
    Point_8017886C delta;
    Object_80039F5C *pCarrier;
    int angle;

    fn_8011FCA4();
    count = fn_80178D70(fn_80178320());
    for (i = 0; i < count; i++) {
        lbl_803EB09C->mpUnknown12[i] = 3;
    }
    BallGetPosition(BallGetCurrent(), &pos);
    pCarrier = BallGetCurrentHolder();
    if (pCarrier) {
        velocity.mX = pCarrier->mMotion.mUnknown40;
        velocity.mY = pCarrier->mMotion.mUnknown44;
        velocity.mZ = pCarrier->mMotion.mUnknown48;
    } else {
        BallGetVelocity(BallGetCurrent(), &velocity);
    }
    angle = fn_801CFE40(velocity.mY, velocity.mX);
    for (i = 0; i < count; i++) {
        fn_80227690(&delta, &PlyrGet(fn_80178320(), i)->mMotion.mPos, &pos);
        if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), angle) <= 0x238E38) {
            lbl_803EB09C->mpUnknown12[i] = 0;
        }
    }
    for (i = 0; i < count && i <= 1; i++) {
        lbl_803EB09C->mpUnknown12[lbl_803EB09C->mpUnknown8[i].mUnknown4] = 0;
    }
    for (i = 0; i < count; i++) {
        if (lbl_803EB09C->mpUnknown8[i].mUnknown0 < 2.5f || lbl_803EB09C->mpUnknown8[i].mUnknown0 > 100.0f) {
            lbl_803EB09C->mpUnknown12[lbl_803EB09C->mpUnknown8[i].mUnknown4] = 0;
        }
    }
}
}

extern "C" {
void fn_8012055C(int count)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EB09C, sizeof(Lookup_8012078C), 0, 0x70757273);
    Lookup_8012078C *pLookup;

    fn_80238234(pHandle, fn_8011F698, fn_8011F6BC, 0, fn_8011F71C);
    fn_80238248(pHandle, fn_8011F904, fn_8011FA54, fn_8011F99C);
    pLookup = (Lookup_8012078C *)fn_8023816C(pHandle);
    pLookup->mUnknown16 = count;
    pLookup->mUnknown18 = 0;
    pLookup->mUnknown19 = 0;
    pLookup->mUnknown20 = 0;
    fn_802381E0(pHandle);
}
}

extern "C" {
void fn_8012060C(void)
{
    lbl_803EB09C = 0;
}
}

extern "C" {
void fn_80120618(void)
{
    Point_8017886C ball;
    unsigned char i;

    for (i = 0; i < lbl_803EB09C->mUnknown16; i++) {
        lbl_803EB09C->mpUnknown12[i] = 0;
        lbl_803EB09C->mpUnknown0[i] = lbl_803EB09C->mpUnknown4[i] = i;
        lbl_803EB09C->mpUnknown8[i].mUnknown4 = i;
        lbl_803EB09C->mpUnknown8[i].mUnknown0 = 0.0f;
    }
    if (fn_801486A0() == 0) {
        lbl_803EB09C->mUnknown18 = 3;
    } else {
        lbl_803EB09C->mUnknown18 = 0;
    }
    ball = fn_80177FE0();
    if (ball.mX > 0.0f) {
        lbl_803EB09C->mUnknown19 = 0;
    } else {
        lbl_803EB09C->mUnknown19 = 1;
    }
    lbl_803EB09C->mUnknown20 = 0;
}
}

extern "C" {
void fn_80120720(int value)
{
    lbl_803EB09C->mUnknown20 -= value;
    if (lbl_803EB09C->mUnknown20 & 0x80) {
        lbl_803EB09C->mUnknown20 = 5;
        switch (lbl_803EB09C->mUnknown18) {
        case 0:
            fn_8011FE0C();
            break;
        case 3:
            fn_80120384();
            break;
        }
    }
}
}

extern "C" {
Lookup_8012078C *fn_8012078C(void)
{
    return lbl_803EB09C;
}
}

extern "C" {
int fn_80120794(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pDir, float speed, float dist,
                int, float range)
{
    Point_8017886C delta;
    int angle;
    int result;

    fn_80227690(&delta, pB, pA);
    angle = fn_801CFE40(delta.mY, delta.mX);
    if (range > 10.0f && pA->mY < pB->mY) {
        return 0x400000;
    }
    if (dist < gPlyrMoveFwdSpeed * 0.1f) {
        return angle;
    }
    if (speed == 0.0f) {
        return angle;
    }
    result = PursuitGetInterceptAngle(pA, pB, speed, pDir);
    if (result <= 0x7FFFFF && pA->mY > pB->mY && pA->mY > fn_80178A2C()) {
        fn_80237260(0);
        result = result > 0x400000 ? 0x800000 : 0;
    }
    return result;
}
}

extern "C" {
int PursuitGetInterceptAngle(Vector_80039F5C *pA, Vector_80039F5C *pB, float speed, Vector_80039F5C *pDir)
{
    int dirAngle = fn_801CFE40(pDir->mY, pDir->mX);
    float dirLength = fn_802270A4(pDir);
    Point_8017886C delta;
    int toAngle;
    int backAngle;
    int diff;
    int opposite;
    int wide;
    float ratio;
    float minSpeed = speed;
    int turn;
    int result;

    fn_80227690(&delta, pA, pB);
    toAngle = fn_801CFE40(delta.mY, delta.mX);
    backAngle = (toAngle + 0x800000) & 0xFFFFFF;
    diff = MathAngleDiff(dirAngle, toAngle);
    opposite = MathAngleDiff(0x800000, diff);
    wide = diff > 0x400000;
    if (minSpeed < 1e-7f) {
        minSpeed = 1e-7f;
    }
    if (wide) {
        ratio = fn_801CFB18(opposite);
    } else {
        ratio = fn_801CFB18(diff);
    }
    ratio *= dirLength;
    ratio /= minSpeed;
    if (ratio > 1.0f) {
        Vector_80039F5C target;
        Point_8017886C toTarget;

        target.mX = pB->mX;
        target.mY = pB->mY;
        target.mZ = pB->mZ;
        fn_80227350(&target, pDir, 120.0f);
        fn_80227690(&toTarget, &target, pA);
        result = fn_801CFE40(toTarget.mY, toTarget.mX) & 0xFFFFFF;
    } else {
        turn = fn_801CFDD0(ratio);
        result = (((toAngle - dirAngle) & 0xFFFFFF) <= 0x7FFFFF ? backAngle + turn : backAngle - turn) & 0xFFFFFF;
    }
    return result;
}
}

extern "C" {
int fn_80120A50(Point_8017886C *p, Point_8017886C *pA, Point_8017886C *pB, Point_8017886C *pC)
{
    float d0 = p->mX * (pC->mY - pB->mY) + pC->mX * (pB->mY - p->mY) + pB->mX * (p->mY - pC->mY);
    float d1 = pB->mX * (p->mY - pA->mY) + p->mX * (pA->mY - pB->mY) + pA->mX * (pB->mY - p->mY);
    float d2 = pA->mX * (pB->mY - pC->mY) + pB->mX * (pC->mY - pA->mY) + pC->mX * (pA->mY - pB->mY);
    float d3 = pC->mX * (pA->mY - p->mY) + pA->mX * (p->mY - pC->mY) + p->mX * (pC->mY - pA->mY);

    if ((d0 >= 0.0f && d1 >= 0.0f && d2 >= 0.0f && d3 >= 0.0f)
        || (d0 <= 0.0f && d1 <= 0.0f && d2 <= 0.0f && d3 <= 0.0f)) {
        return 1;
    }
    return 0;
}
}

extern "C" {
void fn_80120B4C(int value, int *pList, unsigned char i, unsigned char count)
{
    for (; i < count; i++) {
        if (value == pList[i]) {
            pList[i] = 0;
            return;
        }
    }
}
}

extern "C" {
void fn_80120B84(Plan_80121264 *pPlan)
{
    int swapped;

    do {
        Entry_80120E98 *pPrev = pPlan->mUnknown0;
        Entry_80120E98 *pEntry = pPrev + 1;
        unsigned char i;

        swapped = 0;
        for (i = 0; i < pPlan->mUnknown1440 - 1; i++) {
            if (pEntry->mUnknown8.mX < pPrev->mUnknown8.mX) {
                Entry_80120E98 temp = *pEntry;

                *pEntry = *pPrev;
                *pPrev = temp;
                swapped = 1;
            }
            pPrev = pEntry;
            pEntry++;
        }
    } while (swapped);
}
}

extern "C" {
void fn_80120CDC(Object_80039F5C *p, Object_80039F5C *pOther, Entry_80120E98 *pEntry)
{
    if (pOther->mIdBytes[2] == p->mIdBytes[2]) {
        switch (pOther->mUnknown1032) {
        case 4:
        case 5:
        case 6:
        case 7:
            pEntry->mUnknown36 |= 1;
            break;
        case 1:
        case 2:
        case 3:
        default:
            pEntry->mUnknown36 |= 2;
            if (pOther->mQueue[0].mId == 47) {
                pEntry->mUnknown36 |= 4;
            }
            break;
        }
        if (pOther->mFlags & 0x800) {
            pEntry->mUnknown36 |= 32;
        }
    } else {
        switch (pOther->mUnknown1032) {
        case 4:
        case 5:
        case 6:
        case 7:
            pEntry->mUnknown36 |= 1;
            break;
        default:
            pEntry->mUnknown36 |= 8;
            break;
        }
        if (pOther->mFlags & 0x800) {
            pEntry->mUnknown36 |= 16;
        }
    }
}
}

extern "C" {
void fn_80120D98(Object_80039F5C *p, Point_8017886C *pMin, Point_8017886C *pMax)
{
    float x = p->mMotion.mPos.mX;
    pMin->mX = x;
    pMin->mY = p->mMotion.mPos.mY;
    pMax->mX = x;
    pMax->mY = pMin->mY;
    for (unsigned char i = 0; lbl_802DB03C[i] != 30; i++) {
        Vector_80039F5C point;
        int angles[3];
        fn_8009BF5C(p, lbl_802DB03C[i], &point, angles);
        float x = point.mX;
        pMax->mX = pMax->mX >= x ? pMax->mX : x;
        pMin->mX = pMin->mX <= x ? pMin->mX : x;
        float y = point.mY;
        pMax->mY = pMax->mY >= y ? pMax->mY : y;
        pMin->mY = pMin->mY <= y ? pMin->mY : y;
    }
}
}

extern "C" {
void fn_80120E98(Plan_80121264 *pPlan, int index)
{
    int last = pPlan->mUnknown1440 - 1;

    if (index != last) {
        memcpy(&pPlan->mUnknown0[index], &pPlan->mUnknown0[index + 1], (last - index) * sizeof(Entry_80120E98));
    }
    pPlan->mUnknown1440--;
}
}

extern "C" {
void fn_80120EF8(Plan_80121264 *pPlan, Vector_80039F5C *pPos)
{
    unsigned int i;
    int removed;

    fn_80120B84(pPlan);
    if (pPlan->mUnknown1440 > 4) {
        for (i = 1; i < pPlan->mUnknown1440 - 1; i++) {
            Entry_80120E98 *pEntry = &pPlan->mUnknown0[i];
            Entry_80120E98 *pNext = &pPlan->mUnknown0[i + 1];

            if (pEntry->mUnknown40 != pNext->mUnknown40 || pEntry->mUnknown44 != pNext->mUnknown44) {
                unsigned int j;

                for (j = i + 1; j < pPlan->mUnknown1440 - 1; j++) {
                    Entry_80120E98 *pMatch = &pPlan->mUnknown0[j];

                    if (pEntry->mUnknown40 == pMatch->mUnknown40 && pEntry->mUnknown44 == pMatch->mUnknown44
                        && (pMatch != pNext || pNext->mUnknown8.mX < pEntry->mUnknown8.mX)) {
                        Entry_80120E98 temp = *pNext;

                        *pNext = *pMatch;
                        *pMatch = temp;
                        break;
                    }
                }
            } else if (pEntry->mUnknown8.mX > pNext->mUnknown8.mX) {
                Entry_80120E98 temp = *pNext;

                *pNext = *pEntry;
                *pEntry = temp;
            }
        }
    }
    do {
        removed = 0;
        if (pPlan->mUnknown1440 > 4) {
            for (i = 3; i < pPlan->mUnknown1440 - 1; i += 2) {
                if (pPlan->mUnknown0[i].mUnknown8.mX < pPlan->mUnknown0[i - 1].mUnknown8.mX
                    && pPlan->mUnknown0[i].mUnknown8.mY > pPlan->mUnknown0[i - 1].mUnknown8.mY) {
                    fn_80120E98(pPlan, i);
                    fn_80120E98(pPlan, i);
                    removed = 1;
                    break;
                }
            }
        }
    } while (removed);
}
}

extern "C" {
void fn_80121264(Object_80039F5C *p, Plan_80121264 *pPlan)
{
    Vector_80039F5C *pPos = &p->mMotion.mPos;
    Object_80039F5C *players[14];
    unsigned char count = 0;
    unsigned char team;
    unsigned char i;
    float range;
    Object_80039F5C *pPlayer;
    Entry_80120E98 *pLast;

    memset(pPlan, 0, sizeof(Plan_80121264));
    memset(players, 0, sizeof(players));
    if (fn_8011F1A4() && fn_8011F1A4() && fn_8011F4C8() <= 3 && !fn_801783AC(0)) {
        range = 5.0f;
    } else {
        range = 8.0f;
    }
    for (team = 0; team <= 1; team++) {
        unsigned int n = fn_80178D70(team);

        for (i = 0; i < n; i++) {
            pPlayer = PlyrGet(team, i);

            if (pPlayer->mMotion.mPos.mY > pPos->mY && pPlayer->mMotion.mPos.mY - pPos->mY < range) {
                players[count] = pPlayer;
                count++;
            }
        }
    }
    pPlan->mUnknown1440 = 1;
    for (i = 0; i < count; i++) {
        Object_80039F5C *pPartner;
        Entry_80120E98 *pA;
        Entry_80120E98 *pB;
        Point_8017886C min;
        Point_8017886C max;
        Point_8017886C partnerMin;
        Point_8017886C partnerMax;

        pPlayer = players[i];
        if (!pPlayer) {
            continue;
        }
        pA = &pPlan->mUnknown0[pPlan->mUnknown1440];
        pB = &pPlan->mUnknown0[pPlan->mUnknown1440 + 1];
        pB->mUnknown36 = 0;
        pA->mUnknown36 = 0;
        fn_8009BD2C(0, &pA->mUnknown40);
        fn_8009BD2C(0, &pA->mUnknown44);
        pB->mUnknown40 = pA->mUnknown40;
        pB->mUnknown44 = pA->mUnknown44;
        switch (pPlayer->mUnknown1032) {
        case 4:
        case 5:
        case 6:
            pPartner = fn_8009BCE8(&pPlayer->mUnknown1036);
            fn_80120D98(pPlayer, &min, &max);
            fn_80120D98(pPartner, &partnerMin, &partnerMax);
            pA->mUnknown8.mX = max.mX >= partnerMax.mX ? max.mX : partnerMax.mX;
            pB->mUnknown8.mX = min.mX <= partnerMin.mX ? min.mX : partnerMin.mX;
            pA->mUnknown8.mY = min.mY <= partnerMin.mY ? min.mY : partnerMin.mY;
            if (pPos->mY > pA->mUnknown8.mY) {
                pA->mUnknown8.mY = max.mY >= partnerMax.mY ? max.mY : partnerMax.mY;
                if (pPos->mY < pA->mUnknown8.mY) {
                    pA->mUnknown8.mY = (pA->mUnknown8.mY + pPos->mY) * 0.5f;
                }
            }
            pB->mUnknown8.mY = pA->mUnknown8.mY;
            fn_80120CDC(p, pPartner, pA);
            fn_80120CDC(p, pPartner, pB);
            fn_80120CDC(p, pPlayer, pA);
            fn_80120CDC(p, pPlayer, pB);
            if (pPartner->mIdBytes[2] == p->mIdBytes[2]) {
                pA->mpUnknown0 = (Point_8017886C *)&pPartner->mMotion.mPos;
                pA->mpUnknown4 = (Point_8017886C *)&pPlayer->mMotion.mPos;
                pA->mUnknown16 = pPlayer->mMotion.mFacing;
            } else {
                pA->mpUnknown0 = (Point_8017886C *)&pPlayer->mMotion.mPos;
                pA->mpUnknown4 = (Point_8017886C *)&pPartner->mMotion.mPos;
                pA->mUnknown16 = pPartner->mMotion.mFacing;
            }
            pB->mpUnknown0 = pA->mpUnknown0;
            pB->mpUnknown4 = pA->mpUnknown4;
            pB->mUnknown16 = pA->mUnknown16;
            pA->mUnknown40 = pPlayer->mId;
            pA->mUnknown44 = pPartner->mId;
            pB->mUnknown40 = pA->mUnknown40;
            pB->mUnknown44 = pA->mUnknown44;
            fn_80120B4C((int)pPartner, (int *)players, i, count);
            break;
        default:
            fn_80120D98(pPlayer, &min, &max);
            pA->mUnknown8.mX = max.mX;
            pB->mUnknown8.mX = min.mX;
            pA->mUnknown8.mY = min.mY;
            if (pPos->mY > pA->mUnknown8.mY) {
                pA->mUnknown8.mY = max.mY;
                if (pPos->mY < pA->mUnknown8.mY) {
                    pA->mUnknown8.mY = (pA->mUnknown8.mY + pPos->mY) * 0.5f;
                }
            }
            pB->mUnknown8.mY = pA->mUnknown8.mY;
            pA->mUnknown40 = pPlayer->mId;
            pPartner = fn_8009BCE8(&pPlayer->mUnknown1036);
            if (pPartner) {
                if (pPartner->mIdBytes[2] == p->mIdBytes[2]) {
                    pA->mpUnknown0 = (Point_8017886C *)&pPartner->mMotion.mPos;
                    pA->mpUnknown4 = (Point_8017886C *)&pPlayer->mMotion.mPos;
                } else {
                    pA->mpUnknown0 = (Point_8017886C *)&pPlayer->mMotion.mPos;
                    pA->mpUnknown4 = (Point_8017886C *)&pPartner->mMotion.mPos;
                }
                pA->mUnknown44 = pPartner->mId;
            } else {
                pA->mpUnknown0 = 0;
                pA->mpUnknown4 = 0;
            }
            pB->mpUnknown0 = pA->mpUnknown0;
            pB->mpUnknown4 = pA->mpUnknown4;
            fn_80120CDC(p, pPlayer, pA);
            fn_80120CDC(p, pPlayer, pB);
            pA->mUnknown16 = pPlayer->mMotion.mFacing;
            pB->mUnknown16 = pPlayer->mMotion.mFacing;
            pB->mUnknown40 = pA->mUnknown40;
            pB->mUnknown44 = pA->mUnknown44;
            break;
        }
        if (pA->mUnknown8.mY < pPos->mY || pB->mUnknown8.mY < pPos->mY) {
            continue;
        }
        if (pA->mpUnknown0 && pA->mpUnknown4 && pB->mpUnknown0 && pB->mpUnknown4) {
            Point_8017886C delta;
            int heading;
            float distance;

            fn_80227690(&delta, pPos, pA->mpUnknown0);
            pA->mUnknown20 = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
            pA->mUnknown28 = fn_802270A4(&delta);
            pB->mUnknown20 = pA->mUnknown20;
            pB->mUnknown28 = pA->mUnknown28;
            fn_80227690(&delta, pA->mpUnknown4, pA->mpUnknown0);
            heading = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
            pA->mUnknown24 = heading;
            pB->mUnknown24 = heading;
            fn_80227690(&delta, pPos, pA->mpUnknown4);
            distance = fn_802270A4(&delta);
            pA->mUnknown32 = distance;
            pB->mUnknown32 = distance;
        }
        pPlan->mUnknown1440 += 2;
    }
    pPlan->mUnknown0[0].mUnknown36 = 0x40;
    pPlan->mUnknown0[0].mUnknown16 = 0;
    pPlan->mUnknown0[0].mpUnknown0 = 0;
    pPlan->mUnknown0[0].mpUnknown4 = 0;
    fn_8009BD2C(0, &pPlan->mUnknown0[0].mUnknown40);
    fn_8009BD2C(0, &pPlan->mUnknown0[0].mUnknown44);
    pPlan->mUnknown0[0].mUnknown8.mX = -fn_80178A08();
    if (pPlan->mUnknown1440 > 1) {
        pPlan->mUnknown0[0].mUnknown8.mY = pPlan->mUnknown0[1].mUnknown8.mY >= pPos->mY + 5.0f
                                               ? pPlan->mUnknown0[1].mUnknown8.mY
                                               : pPos->mY + 5.0f;
    } else {
        pPlan->mUnknown0[0].mUnknown8.mY = pPos->mY + 5.0f;
    }
    pLast = &pPlan->mUnknown0[pPlan->mUnknown1440];
    pLast->mUnknown36 = 0x40;
    pLast->mUnknown16 = 0;
    pLast->mpUnknown0 = 0;
    pLast->mpUnknown4 = 0;
    fn_8009BD2C(0, &pLast->mUnknown40);
    fn_8009BD2C(0, &pLast->mUnknown44);
    pLast->mUnknown8.mX = fn_80178A08();
    pLast->mUnknown8.mY = pPlan->mUnknown0[pPlan->mUnknown1440 - 1].mUnknown8.mY >= pPos->mY + 5.0f
                              ? pPlan->mUnknown0[pPlan->mUnknown1440 - 1].mUnknown8.mY
                              : pPos->mY + 5.0f;
    pPlan->mUnknown1440++;
    fn_80120EF8(pPlan, pPos);
}
}

extern "C" {
int fn_801218EC(Point_8017886C *pPos, Entry_80120E98 *pA, Entry_80120E98 *pB)
{
    return pPos->mX < pB->mUnknown8.mX && pPos->mX > pA->mUnknown8.mX;
}
}

extern "C" {
int fn_80121918(Object_80039F5C *p, Plan_80121264 *pPlan, Entry_801230B8 *pEntry)
{
    Point_8017886C *pPos;
    unsigned char i;
    unsigned char j;

    if (pEntry->mpUnknown4->mUnknown40 == pEntry->mpUnknown0->mUnknown40 &&
        pEntry->mpUnknown4->mUnknown44 == pEntry->mpUnknown0->mUnknown44) {
        return 0;
    }
    if (pEntry->mpUnknown4->mUnknown8.mX < pEntry->mpUnknown0->mUnknown8.mX) {
        return 0;
    }
    if (pEntry->mUnknown24 < 0.55f && !((pEntry->mpUnknown0->mUnknown36 | pEntry->mpUnknown4->mUnknown36) & 4)) {
        return 0;
    }
    if (MathAngleDiff(p->mMotion.mFacing, pEntry->mUnknown16) > 0x51C71C) {
        return 0;
    }
    pPos = (Point_8017886C *)&p->mMotion.mPos;
    if (!fn_801218EC(pPos, pEntry->mpUnknown0, pEntry->mpUnknown4)) {
        Entry_80120E98 *pNear = pEntry->mUnknown16 > 0x400000 ? pEntry->mpUnknown4 : pEntry->mpUnknown0;
        Point_8017886C delta;
        int angle;

        delta.mX = pNear->mUnknown8.mX;
        delta.mY = pNear->mUnknown8.mY;
        fn_80227690(&delta, &delta, pPos);
        angle = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        if (MathAngleDiff(pEntry->mUnknown16, 0x400000) < MathAngleDiff(angle, 0x400000)) {
            return 0;
        }
        if (MathAngleDiff(pEntry->mUnknown16, angle) <= 0x4FA4E) {
            return 0;
        }
    }
    for (i = 0; i < pPlan->mUnknown1440 - 1; i++) {
        Entry_80120E98 *pCur = &pPlan->mUnknown0[i];
        Entry_80120E98 *pNext = &pPlan->mUnknown0[i + 1];

        if (pCur != pEntry->mpUnknown0 && pNext != pEntry->mpUnknown4 &&
            fn_80120A50(&pCur->mUnknown8, &pNext->mUnknown8, pPos, &pEntry->mUnknown8)) {
            return 0;
        }
        if ((pCur->mUnknown36 & 1) && fn_80120A50(pCur->mpUnknown0, pCur->mpUnknown4, pPos, &pEntry->mUnknown8)) {
            return 0;
        }
    }
    for (i = 1; i < pPlan->mUnknown1440 - 2; i++) {
        Entry_80120E98 *pCur = &pPlan->mUnknown0[i];

        for (j = i + 1; j < pPlan->mUnknown1440 - 1; j++) {
            Entry_80120E98 *pOther = &pPlan->mUnknown0[j];

            if ((pCur != pEntry->mpUnknown0 || pOther != pEntry->mpUnknown4) &&
                pCur->mUnknown40 == pOther->mUnknown40 && pCur->mUnknown44 == pOther->mUnknown44 &&
                fn_80120A50(&pCur->mUnknown8, &pOther->mUnknown8, pPos, &pEntry->mUnknown8)) {
                return 0;
            }
        }
    }
    return 1;
}
}

extern "C" {
int fn_80121BE8(Point_8017886C *pA, Point_8017886C *pB, Point_8017886C *pTarget, int angle, int heading,
                float distB, float distA)
{
    if (pTarget) {
        Point_8017886C delta;

        fn_80227690(&delta, pTarget, pA);
        heading = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        distA = fn_802270A4(&delta);
        fn_80227690(&delta, pTarget, pB);
        distB = fn_802270A4(&delta);
    }
    if (MathAngleDiff(heading, angle) > 0x6E38E3 && distA < distB) {
        return 1;
    }
    return 0;
}
}

extern "C" {
void fn_80121CB0(Object_80039F5C *p, Entry_801230B8 *pEntry, int angle)
{
    Point_8017886C *pPos = (Point_8017886C *)&p->mMotion.mPos;
    int flagsB = pEntry->mpUnknown4->mUnknown36;
    int flagsA = pEntry->mpUnknown0->mUnknown36;
    int facing = p->mMotion.mFacing;
    float weight = 0.0f;
    int adjust = 0;
    int inside = fn_801218EC(pPos, pEntry->mpUnknown0, pEntry->mpUnknown4);
    Point_8017886C delta;
    int heading;

    if (!inside && !((flagsA | flagsB) & 0x40)) {
        if (pPos->mX > pEntry->mpUnknown4->mUnknown8.mX &&
            pEntry->mpUnknown4->mUnknown8.mY < pEntry->mpUnknown0->mUnknown8.mY) {
            fn_80227690(&delta, &pEntry->mpUnknown4->mUnknown8, &pEntry->mUnknown8);
            adjust = 1;
            weight = fn_801CFB94(MathAngleDiff(delta.Heading() & 0xFFFFFF, (pEntry->mUnknown16 + 0x800000) & 0xFFFFFF));
            delta = pEntry->mpUnknown0->mUnknown8;
        } else if (pPos->mX < pEntry->mpUnknown0->mUnknown8.mX &&
                   pEntry->mpUnknown4->mUnknown8.mY > pEntry->mpUnknown0->mUnknown8.mY) {
            fn_80227690(&delta, &pEntry->mpUnknown0->mUnknown8, &pEntry->mUnknown8);
            adjust = 1;
            weight = fn_801CFB94(MathAngleDiff(delta.Heading() & 0xFFFFFF, (pEntry->mUnknown16 + 0x800000) & 0xFFFFFF));
            delta = pEntry->mpUnknown4->mUnknown8;
        }
    } else if ((flagsA & 1) && (flagsB & 1)) {
        if (pEntry->mUnknown20 > 1.5f && pEntry->mUnknown24 < 4.0f) {
            if (pEntry->mpUnknown4->mUnknown8.mY > pEntry->mpUnknown0->mUnknown8.mY) {
                fn_80227690(&delta, &pEntry->mpUnknown4->mUnknown8, &pEntry->mpUnknown0->mUnknown8);
                heading = delta.Heading() & 0xFFFFFF;
                delta = pEntry->mpUnknown4->mUnknown8;
            } else {
                fn_80227690(&delta, &pEntry->mpUnknown0->mUnknown8, &pEntry->mpUnknown4->mUnknown8);
                heading = delta.Heading() & 0xFFFFFF;
                delta = pEntry->mpUnknown0->mUnknown8;
            }
            adjust = 1;
            weight = fn_801CFB94(MathAngleDiff(heading, 0x400000));
        } else if (pEntry->mUnknown24 > 8.0f && MathAngleDiff(pEntry->mUnknown16, angle) > 0x271C71 &&
                   MathAngleDiff(pEntry->mUnknown16, facing) > 0x271C71) {
            pEntry->mUnknown16 = angle;
        } else if (inside && pPos->mY > fn_80178A2C() - 5.0f && fn_801486A0()) {
            pEntry->mUnknown16 = angle;
        }
    } else if ((flagsA & 2) && (flagsB & 1) || (flagsA & 1) && (flagsB & 2)) {
        Entry_80120E98 *pOther;

        if (flagsA & 2) {
            delta = pEntry->mpUnknown4->mUnknown8;
            pOther = pEntry->mpUnknown0;
        } else {
            delta = pEntry->mpUnknown0->mUnknown8;
            pOther = pEntry->mpUnknown4;
        }
        if (delta.mY < pOther->mUnknown8.mY) {
            adjust = 1;
        }
        if (adjust) {
            fn_80227690(&delta, &delta, &pEntry->mUnknown8);
            weight = fn_801CFB94(MathAngleDiff(delta.Heading() & 0xFFFFFF, (pEntry->mUnknown16 + 0x800000) & 0xFFFFFF) / 2);
            if (flagsA & 2) {
                delta = pEntry->mpUnknown0->mUnknown8;
            } else {
                delta = pEntry->mpUnknown4->mUnknown8;
            }
        }
    } else if ((flagsA & 8) && (flagsB & 1) || (flagsA & 1) && (flagsB & 8) || (flagsA & 8) && (flagsB & 2) ||
               (flagsA & 2) && (flagsB & 8)) {
        if (pEntry->mUnknown20 > 1.5f && pEntry->mUnknown24 > 4.0f || !fn_801486A0()) {
            Entry_80120E98 *pEnd;

            if (flagsA & 3) {
                pEnd = pEntry->mpUnknown0;
            } else {
                pEnd = pEntry->mpUnknown4;
            }
            delta = pEnd->mUnknown8;
            heading = (pEnd->mUnknown20 + 0x800000) & 0xFFFFFF;
            if (MathAngleDiff(heading, pEntry->mUnknown16) > 0x400000 &&
                MathAngleDiff(pEntry->mUnknown16, facing) > 0x200000) {
                pEntry->mUnknown16 = angle;
            } else if (MathAngleDiff(heading, pEntry->mUnknown16) > 0x200000 &&
                       fabsf(pPos->mX - delta.mX) > 0.55f) {
                adjust = 1;
                weight = 0.35f;
            }
        } else {
            delta.mX = pPos->mX;
            adjust = 1;
            delta.mY = fn_80178A44();
            weight = 1.0f - pEntry->mUnknown20 / 1.5f;
        }
    } else if ((flagsA & 0x40) && (flagsB & 1) || (flagsA & 1) && (flagsB & 0x40) || (flagsA & 0x40) && (flagsB & 2) ||
               (flagsA & 2) && (flagsB & 0x40)) {
        if (fabsf(pPos->mX) > fabsf(pEntry->mUnknown8.mX)) {
            pEntry->mUnknown16 = angle;
        } else if (pEntry->mUnknown24 > 4.0f) {
            Entry_80120E98 *pEnd;

            if (flagsA & 3) {
                pEnd = pEntry->mpUnknown0;
            } else {
                pEnd = pEntry->mpUnknown4;
            }
            delta = pEnd->mUnknown8;
            weight = pEnd->mUnknown28;
            if (weight < 2.0f) {
                adjust = 1;
                weight *= 0.175f;
            }
        }
    } else if ((flagsA & 2) && (flagsB & 2)) {
        if (pEntry->mUnknown8.mY - pPos->mY < 2.0f) {
            adjust = 1;
            weight = 0.35f;
            if (fabsf(pEntry->mpUnknown4->mUnknown8.mX - pPos->mX) < fabsf(pEntry->mpUnknown0->mUnknown8.mX - pPos->mX)) {
                delta = pEntry->mpUnknown4->mUnknown8;
            } else {
                delta = pEntry->mpUnknown0->mUnknown8;
            }
        }
    } else if ((flagsA & 8) && (flagsB & 8)) {
        if (inside) {
            pEntry->mUnknown16 = angle;
        }
    } else if ((flagsA & 0x40) && (flagsB & 8) || (flagsA & 8) && (flagsB & 0x40)) {
        if (fabsf(pPos->mX) > fabsf(pEntry->mUnknown8.mX)) {
            pEntry->mUnknown16 = angle;
        } else if ((flagsA | flagsB) & 0x10) {
            if (pEntry->mUnknown24 > 4.0f) {
                adjust = 1;
                weight = 0.35f;
                if (flagsA & 0x10) {
                    delta = pEntry->mpUnknown0->mUnknown8;
                } else {
                    delta = pEntry->mpUnknown4->mUnknown8;
                }
            }
        } else if (inside && pEntry->mUnknown24 > fn_80178A08() * 0.5f) {
            if (angle < pEntry->mUnknown16) {
                fn_80227690(&delta, &pEntry->mpUnknown4->mUnknown8, pPos);
                heading = delta.Heading() & 0xFFFFFF;
                pEntry->mUnknown16 = angle < heading ? heading : angle;
            } else {
                fn_80227690(&delta, &pEntry->mpUnknown0->mUnknown8, pPos);
                heading = delta.Heading() & 0xFFFFFF;
                pEntry->mUnknown16 = angle > heading ? heading : angle;
            }
            delta = pEntry->mUnknown8;
            weight = 0.35f;
            adjust = 1;
        }
    } else if ((flagsA & 0x40) && (flagsB & 0x40)) {
        pEntry->mUnknown16 = angle;
    }

    if (inside && pEntry->mUnknown24 > 4.0f && MathAngleDiff(angle, 0x400000) <= 0x238E38) {
        fn_80227690(&delta, &pEntry->mpUnknown4->mUnknown8, pPos);
        heading = delta.Heading() & 0xFFFFFF;
        if (angle > heading) {
            fn_80227690(&delta, &pEntry->mpUnknown0->mUnknown8, pPos);
            heading = delta.Heading() & 0xFFFFFF;
            if (angle < heading) {
                pEntry->mUnknown16 = angle;
                adjust = 0;
            }
        }
    }
    if (adjust) {
        fn_80227690(&delta, &delta, pPos);
        heading = delta.Heading() & 0xFFFFFF;
        if (((heading - pEntry->mUnknown16) & 0xFFFFFF) > 0x800000) {
            pEntry->mUnknown16 = (pEntry->mUnknown16 - (int)(MathAngleDiff(heading, pEntry->mUnknown16) * weight)) & 0xFFFFFF;
        } else {
            pEntry->mUnknown16 = (pEntry->mUnknown16 + (int)(MathAngleDiff(heading, pEntry->mUnknown16) * weight)) & 0xFFFFFF;
        }
    }
}
}

extern "C" {
void fn_80122670(Object_80039F5C *p, Plan_80121264 *pPlan, int angle)
{
    Vector_80039F5C *pPos = &p->mMotion.mPos;
    unsigned char i;

    pPlan->mUnknown2372 = 0;
    for (i = 0; i < pPlan->mUnknown1440 - 1; i++) {
        Entry_801230B8 *pEntry = &pPlan->mUnknown1444[pPlan->mUnknown2372];
        Point_8017886C delta;

        pEntry->mpUnknown0 = &pPlan->mUnknown0[i];
        pEntry->mpUnknown4 = &pPlan->mUnknown0[i + 1];
        pEntry->mUnknown8.mX = (pEntry->mpUnknown0->mUnknown8.mX + pEntry->mpUnknown4->mUnknown8.mX) * 0.5f;
        pEntry->mUnknown8.mY = (pEntry->mpUnknown0->mUnknown8.mY + pEntry->mpUnknown4->mUnknown8.mY) * 0.5f;
        fn_80227690(&delta, &pEntry->mUnknown8, pPos);
        pEntry->mUnknown16 = fn_801CFE40(delta.mY, delta.mX) & 0xFFFFFF;
        pEntry->mUnknown20 = fn_802270A4(&delta);
        fn_80227690(&delta, &pEntry->mpUnknown0->mUnknown8, &pEntry->mpUnknown4->mUnknown8);
        pEntry->mUnknown24 = fn_802270A4(&delta);
        pEntry->mUnknown28 = 0.0f;
        fn_80121CB0(p, pEntry, angle);
        if (fn_80121918(p, pPlan, pEntry)) {
            pPlan->mUnknown2372++;
        }
    }
}
}

extern "C" {
void fn_801227DC(Object_80039F5C *p, Plan_80121264 *pPlan, Entry_801230B8 *pEntry)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Entry_80120E98 *pA = pEntry->mpUnknown0;
    Entry_80120E98 *pB = pEntry->mpUnknown4;
    int flagsA;
    int flagsB;
    int blocked = 0;
    int open = 0;
    int wide = 0;
    int inside = pMotion->mPos.mX < pB->mUnknown8.mX + 0.25f && pMotion->mPos.mX > pA->mUnknown8.mX - 0.25f;
    Point_8017886C delta;
    int angle;
    float value;

    flagsA = pA->mUnknown36;
    flagsB = pB->mUnknown36;
    if ((flagsA & 1) && (flagsB & 1)) {
        if (inside) {
            open = 1;
        }
    } else if ((flagsA & 2) && (flagsB & 1) || (flagsA & 1) && (flagsB & 2)) {
        open = 1;
        if ((flagsA | flagsB) & 4) {
            wide = 1;
        }
    } else if ((flagsA & 8) && (flagsB & 1) || (flagsA & 1) && (flagsB & 8)) {
        if (inside) {
            if (flagsA & 8) {
                fn_80227690(&delta, (Point_8017886C *)&pMotion->mPos, &pA->mUnknown8);
                angle = pA->mUnknown16;
            } else {
                fn_80227690(&delta, (Point_8017886C *)&pMotion->mPos, &pB->mUnknown8);
                angle = pB->mUnknown16;
            }
            if (MathAngleDiff(delta.Heading() & 0xFFFFFF, angle) > 0x400000) {
                open = 1;
            }
        }
    } else if ((flagsA & 0x40) && (flagsB & 1) || (flagsA & 1) && (flagsB & 0x40)) {
        if (inside || (!fn_8011F1A4() || fn_8011F4C8() > 3) && !fn_801783AC(0)) {
            open = 1;
        } else {
            blocked = 1;
        }
        if ((!fn_8011F1A4() || fn_8011F4C8() > 3) && !fn_801783AC(0) &&
            MathAngleDiff(pMotion->mFacing, pEntry->mUnknown16) <= 0x1FFFFF) {
            pEntry->mUnknown28 += 1.0f;
        }
    } else if ((flagsA & 2) && (flagsB & 2)) {
        if (inside) {
            open = 1;
        } else {
            blocked = 1;
        }
        if ((flagsA | flagsB) & 4) {
            wide = 1;
        }
    } else if ((flagsA & 8) && (flagsB & 2) || (flagsA & 2) && (flagsB & 8)) {
        if (!inside) {
            open = 1;
        }
    } else if ((flagsA & 0x40) && (flagsB & 2) || (flagsA & 2) && (flagsB & 0x40)) {
        open = 1;
        if ((flagsA | flagsB) & 4) {
            wide = 1;
        }
        if (flagsA & 2) {
            value = pA->mUnknown28;
        } else {
            value = pB->mUnknown28;
        }
        if (value > 5.0f && (!fn_8011F1A4() || fn_8011F4C8() > 3) && !fn_801783AC(0) &&
            MathAngleDiff(pMotion->mFacing, pEntry->mUnknown16) <= 0x1FFFFF) {
            pEntry->mUnknown28 += 1.0f;
        } else {
            blocked = 1;
        }
    } else if ((flagsA & 8) && (flagsB & 8)) {
    } else if ((flagsA & 0x40) && (flagsB & 8) || (flagsA & 8) && (flagsB & 0x40)) {
        if (inside && pPlan->mUnknown2372 <= 2) {
            fn_80227690(&delta, &pB->mUnknown8, (Point_8017886C *)&pMotion->mPos);
            angle = delta.Heading() & 0xFFFFFF;
            if ((pMotion->mFacing & 0xFFFFFF) > angle) {
                fn_80227690(&delta, &pA->mUnknown8, (Point_8017886C *)&pMotion->mPos);
                angle = delta.Heading() & 0xFFFFFF;
                if ((pMotion->mFacing & 0xFFFFFF) < angle) {
                    pEntry->mUnknown28 += 1.0f;
                }
            }
        }
    }

    if (((flagsA | flagsB) & 8) && pEntry->mUnknown24 < 5.0f) {
        value = 0.0f;

        if ((flagsA & 0x18) == 8 && pA->mUnknown8.mY - pMotion->mPos.mY > 1.0f) {
            value = fn_801CFB18(MathAngleDiff(pA->mUnknown16, pEntry->mUnknown16) / 2) * 0.5f;
        }
        if ((flagsB & 0x18) == 8 && pB->mUnknown8.mY - pMotion->mPos.mY > 1.0f) {
            value += fn_801CFB18(MathAngleDiff(pB->mUnknown16, pEntry->mUnknown16) / 2) * 0.5f;
            if (flagsA & 8) {
                value *= 0.5f;
            }
        }
        pEntry->mUnknown28 -= value;
    }
    if (open && pEntry->mUnknown24 > 3.0f && MathAngleDiff(pMotion->mFacing, pEntry->mUnknown16) <= 0x1FFFFF) {
        value = fn_801CFB94(MathAngleDiff(pEntry->mUnknown16, pMotion->mFacing));

        if (value < 0.0f) {
            value = 0.0f;
        }
        if (pA->mpUnknown0 && pA->mpUnknown4 &&
            (fn_80121BE8(pA->mpUnknown0, pA->mpUnknown4, 0, pA->mUnknown24, pA->mUnknown20, pA->mUnknown32, pA->mUnknown28) ||
             fn_80121BE8(pA->mpUnknown0, pA->mpUnknown4, &pEntry->mUnknown8, pA->mUnknown24, pA->mUnknown20,
                         pA->mUnknown32, pA->mUnknown28))) {
            pEntry->mUnknown28 += value;
        }
        if (pB->mpUnknown0 && pB->mpUnknown4 &&
            (fn_80121BE8(pB->mpUnknown0, pB->mpUnknown4, 0, pB->mUnknown24, pB->mUnknown20, pB->mUnknown32, pB->mUnknown28) ||
             fn_80121BE8(pB->mpUnknown0, pB->mpUnknown4, &pEntry->mUnknown8, pB->mUnknown24, pB->mUnknown20,
                         pB->mUnknown32, pB->mUnknown28))) {
            pEntry->mUnknown28 += value;
        }
    }
    if (wide) {
        if (fn_8011F1A4() && fn_8011F4C8() <= 3 ||
            fn_8011F1A4() && (fn_8011F4C8() & 1) == 0 && (flagsA & 4) ||
            fn_8011F1A4() && (fn_8011F4C8() & 1) && (flagsB & 4)) {
            pEntry->mUnknown28 += 1.0f;
        }
    }
    if (inside) {
        float width = pEntry->mUnknown24;
        unsigned int degrees;

        if (width > 12.0f) {
            width = 12.0f;
        }
        value = width / 12.0f;
        degrees = value * 90.0f;
        angle = degrees * 46603.38f;
        if (MathAngleDiff(pEntry->mUnknown16, pMotion->mFacing) < angle) {
            pEntry->mUnknown28 += value;
        }
    }
    if (blocked && MathAngleDiff(pMotion->mFacing, 0x400000) <= 0x1C71C6) {
        fn_80227690(&delta, &pB->mUnknown8, (Point_8017886C *)&pMotion->mPos);
        angle = delta.Heading() & 0xFFFFFF;
        if ((pMotion->mFacing & 0xFFFFFF) > angle) {
            fn_80227690(&delta, &pA->mUnknown8, (Point_8017886C *)&pMotion->mPos);
            angle = delta.Heading() & 0xFFFFFF;
            if ((pMotion->mFacing & 0xFFFFFF) < angle) {
                pEntry->mUnknown28 += 0.25f;
            }
        }
    }
}
}

extern "C" {
void fn_80123024(Object_80039F5C *p, Plan_80121264 *pPlan, int angle)
{
    unsigned char i;

    for (i = 0; i < pPlan->mUnknown2372; i++) {
        pPlan->mUnknown1444[i].mUnknown28 = fn_801CFB94(MathAngleDiff(pPlan->mUnknown1444[i].mUnknown16, angle) / 2);
        fn_801227DC(p, pPlan, &pPlan->mUnknown1444[i]);
    }
}
}

extern "C" {
Entry_801230B8 *fn_801230B8(Plan_80121264 *pPlan)
{
    unsigned char best = 0;
    float value = 0.0f;
    for (unsigned char i = 0; i < pPlan->mUnknown2372; i++) {
        if (!(pPlan->mUnknown1444[i].mUnknown28 <= value)) {
            value = pPlan->mUnknown1444[i].mUnknown28;
            best = i;
        }
    }
    return &pPlan->mUnknown1444[best];
}
}

extern "C" {
void fn_8012311C(Object_80039F5C *p, Plan_80121264 *pPlan, int angle)
{
    fn_80121264(p, pPlan);
    fn_80122670(p, pPlan, angle & 0xFFFFFF);
    fn_80123024(p, pPlan, angle & 0xFFFFFF);
}
}

extern "C" {
Entry_801230B8 *fn_80123174(Plan_80121264 *pPlan)
{
    Entry_801230B8 *pBest = 0;
    if (pPlan->mUnknown2372 != 0) {
        unsigned char best = 0;
        float value = 0.0f;
        for (unsigned char i = 0; i < pPlan->mUnknown2372; i++) {
            if (!(pPlan->mUnknown1444[i].mUnknown28 <= value)) {
                value = pPlan->mUnknown1444[i].mUnknown28;
                best = i;
            }
        }
        pBest = &pPlan->mUnknown1444[best];
    }
    return pBest;
}
}

extern "C" {
int fn_801231E4(Object_80039F5C *p, int angle)
{
    Plan_80121264 plan;

    fn_80121264(p, &plan);
    fn_80122670(p, &plan, angle);
    if (plan.mUnknown2372) {
        fn_80123024(p, &plan, angle);
        angle = fn_801230B8(&plan)->mUnknown16;
    }
    return angle;
}
}

extern "C" {
int fn_80123254(void *pA, void *pB)
{
    if (*(float *)pA - *(float *)pB > 0.0f) return 1;
    return -1;
}
}

extern "C" {
void fn_8012327C(Directions_8012430C *pValues, Object_80039F5C *p)
{
    Point_8017886C point;
    point.mY = fn_80177FE0().mY;
    Point_8017886C *pPos = (Point_8017886C *)&p->mMotion.mPos;
    unsigned char mode;
    if (pPos->mY > point.mY - 1.5f || fn_80177C38()) {
        if (!(pPos->mX >= 10.0f - fn_80178A08())) mode = 3;
        else if (!(pPos->mX <= fn_80178A08() - 10.0f)) mode = 4;
        else mode = 5;
    } else {
        mode = 0;
        if (fn_8011F1A4()) {
            point.mX = fn_8011F4D4();
            if (!(point.mY - pPos->mY <= 2.25f) && !fn_801783AC(0)) {
                Point_8017886C delta;
                fn_80227690(&delta, &point, pPos);
                unsigned int direction = (fn_801CFE40(delta.mY, delta.mX) + 0x100000) >> 21 & 7;
                switch (fn_8011F4C8()) {
                case 6: case 8: case 10: case 12:
                    if (!(point.mX <= pPos->mX)) mode = 1;
                    else pValues->mCost[1] -= 5.0f;
                    break;
                case 7: case 9: case 11: case 13:
                    if (!(point.mX >= pPos->mX)) mode = 2;
                    else pValues->mCost[3] -= 5.0f;
                    break;
                default:
                    if (!(fabsf(point.mX - pPos->mX) <= 1.5f)) {
                        if (!(point.mX <= pPos->mX)) {pValues->mCost[2] -= 1.0f; pValues->mCost[1] -= 2.0f;}
                        else {pValues->mCost[2] -= 1.0f; pValues->mCost[3] -= 2.0f;}
                    } else pValues->mCost[direction] -= 10.0f;
                    break;
                }
            }
        }
    }
    const Directions_8012430C *pRow = &lbl_8029F5A0[mode];
    if (fn_801485D4() && fn_80148A58()->vfn_09(1)) pRow = (Directions_8012430C *)fn_80148A58()->vfn_09(1);
    for (unsigned char i = 0; i < 8; i++) pValues->mCost[i] += pRow->mCost[i];
}
}

extern "C" {
void fn_80123594(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *)
{
    Point_8017886C pos;
    pos.mX = p->mMotion.mPos.mX;
    pos.mY = p->mMotion.mPos.mY;
    for (unsigned char team = 0; team < 2; team++) {
        unsigned int count = fn_80178D70(team);
        for (unsigned char i = 0; i < count; i++) {
            Object_80039F5C *pOther = PlyrGet(team, i);
            Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
            float distance = fn_8022781C(&pos, pOtherPos);
            if (!(distance >= 15.0f)) {
                Point_8017886C delta;
                fn_80227690(&delta, pOtherPos, &pos);
                unsigned int direction = (fn_801CFE40(delta.mY, delta.mX) + 0x100000) >> 21 & 7;
                pValues->mCost[direction] += 15.0f - distance;
            }
        }
    }
}
}

extern "C" {
void fn_8012368C(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *)
{
    Point_8017886C pos;
    pos.mX = p->mMotion.mPos.mX;
    pos.mY = p->mMotion.mPos.mY;
    int team = p->mIdBytes[2] ^ 1;
    unsigned int count = fn_80178D70(team);
    for (unsigned char i = 0; i < count; i++) {
        int valid = 1;
        Object_80039F5C *pOther = PlyrGet(team, i);
        switch (pOther->mpState->mId) {
        case 10:
        case 11:
        case 17:
            valid = 0;
            break;
        }
        if (pOther->mFlags & 0x800) valid = 0;
        if (valid) {
            Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
            float distance = fn_8022781C(&pos, pOtherPos);
            if (pOther->mUnknown1032 != 8 && pOther->mUnknown1032 != 0) distance *= 4.0f;
            if (!(distance >= 8.0f)) {
                Point_8017886C delta;
                fn_80227690(&delta, pOtherPos, &pos);
                unsigned int direction = (fn_801CFE40(delta.mY, delta.mX) + 0x100000) >> 21 & 7;
                pValues->mCost[direction] += 15.0f - distance;
            }
        }
    }
}
}

extern "C" {
void fn_801237F4(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *)
{
    Point_8017886C pos;
    pos.mX = p->mMotion.mPos.mX;
    pos.mY = p->mMotion.mPos.mY;
    int facing = p->mMotion.mFacing;
    int ownTeam = fn_80178320();
    float range, factor;
    if (!fn_80177C38() && !(pos.mY >= fn_80177FE0().mY + 5.0f)) {
        if (fn_8011F1A4() && fn_8011F4C8() <= 3) range = 10.0f;
        else range = 12.0f;
        factor = 0.0f;
    } else {range = 14.0f; factor = 0.6f;}
    for (unsigned char team = 0; team < 2; team++) {
        unsigned int count = fn_80178D70(team);
        for (unsigned char i = 0; i < count; i++) {
            Object_80039F5C *pOther = PlyrGet(team, i);
            if (pOther == p) continue;
            Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
            float distance = fn_8022781C(&pos, pOtherPos);
            Point_8017886C delta;
            fn_80227690(&delta, pOtherPos, &pos);
            int angle = fn_801CFE40(delta.mY, delta.mX);
            float limit = (1.0f - fn_801CFB18(MathAngleDiff(facing, angle) / 2) * factor) * range;
            if (!(distance >= limit)) {
                unsigned int direction = (angle + 0x100000) >> 21 & 7;
                float value = limit - distance;
                if (((unsigned int)pOther->mId >> 8 & 255) == ownTeam) {
                    if (!(pOther->mFlags & 0x800)) {
                        value *= 1.25f;
                        if (p->mUnknown560.mUnknown40 == pOther->mId) value += value;
                        if (pOther->mUnknown1032 == 5 || pOther->mUnknown1032 == 6) {
                            if (!(distance >= 1.5f)) value += value;
                        } else if (pOther->mUnknown1032 == 8 || pOther->mUnknown1032 == 0) {
                            if (!(distance >= 2.0f) && direction == ((p->mMotion.mFacing + 0x100000) >> 21 & 7)) value *= 5.0f;
                        }
                        if (!(pOtherPos->mY >= pos.mY)) value *= 0.5f;
                    }
                } else {
                    if (p->mUnknown560.mUnknown44 == pOther->mId) value += value;
                    if (pOther->mUnknown1032 == 4 || pOther->mUnknown1032 == 6 || pOther->mUnknown1032 == 5) {
                        if (!(distance >= 1.5f)) value += value;
                    } else {
                        if (!(pOther->mMotion.mUnknown28 <= gPlyrMoveFwdSpeed * 0.4f)
                            && MathAngleDiff(angle, pOther->mMotion.mUnknown32) <= 0x1FFFFF) value *= 0.25f;
                        if (pOther->mUnknown1052 == 3 && fn_8011F1A4() && fn_8011F4C8() <= 3
                            && MathAngleDiff(angle, facing) <= 0x1FFFFF) {
                            if (!fn_801783AC(0)) value -= 4.0f;
                            else value -= 2.0f;
                        }
                    }
                }
                pValues->mCost[direction] += value;
            }
        }
    }
    if (fn_801486A0()) fn_8012327C(pValues, p);
    else if (fn_800F06F4(0, PlyrGet(fn_80178320(), 0)->mpState, 51, 65535) != 65535) {
        pValues->mCost[(p->mMotion.mFacing + 0x100000) >> 21 & 7] = 0.0f;
    }
}
}

extern "C" {
void fn_80123C2C(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *pExclude)
{
    Point_8017886C pos;
    pos.mX = p->mMotion.mPos.mX;
    pos.mY = p->mMotion.mPos.mY;
    int facing = p->mMotion.mFacing;
    int team = fn_80178320();
    float range = lbl_803EB0A0;
    float factor = lbl_803EB0A4;
    unsigned int count = fn_80178D70(team);
    for (unsigned char i = 0; i < count; i++) {
        float value = 0.0f;
        Object_80039F5C *pOther = PlyrGet(team, i);
        if (pOther == pExclude) continue;
        Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
        float distance = fn_8022781C(&pos, pOtherPos);
        Point_8017886C delta;
        fn_80227690(&delta, pOtherPos, &pos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        int special = pOther->mpState->mId == 12 || pOther->mpState->mId == 94;
        float limit = (1.0f - fn_801CFB18(MathAngleDiff(facing, angle) / 2) * factor) * range;
        if (!(distance >= limit)) {
            unsigned int direction = (angle + 0x100000) >> 21 & 7;
            if (!(pOther->mFlags & 0x800)) {
                value = limit - distance;
                if (pOther->mUnknown1032 == 8 || pOther->mUnknown1032 == 0) value += value;
                if (special) value *= 1.25f;
                value *= 1.0f + (1.0f - fn_801CFB18(MathAngleDiff(pOther->mMotion.mFacing, (angle + 0x800000) & 0xFFFFFF))) * lbl_803EB0A8;
                if (!(pOtherPos->mY >= pos.mY)) value *= lbl_803EB0AC;
            }
            if (!(value <= pValues->mCost[direction])) pValues->mCost[direction] = value;
        }
    }
}
}

extern "C" {
void fn_80123E2C(Directions_8012430C *, Object_80039F5C *, Object_80039F5C *)
{
}
}

extern "C" {
void fn_80123E30(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *)
{
    Point_8017886C pos;
    pos.mX = p->mMotion.mPos.mX;
    pos.mY = p->mMotion.mPos.mY;
    int team = p->mIdBytes[2] ^ 1;
    for (unsigned char i = 0; i < 7; i++) {
        Object_80039F5C *pOther = PlyrGet(team, i);
        Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
        float distance = fn_8022781C(&pos, pOtherPos);
        if (!(distance >= 8.0f)) {
            Point_8017886C delta;
            fn_80227690(&delta, pOtherPos, &pos);
            unsigned int direction = (fn_801CFE40(delta.mY, delta.mX) + 0x100000) >> 21 & 7;
            float value = 8.0f - distance;
            pValues->mCost[direction] += value;
            pValues->mCost[(direction + 1) % 8] += value * 0.5f;
            pValues->mCost[(direction - 1) % 8] += value * 0.5f;
        }
    }
}
}

extern "C" {
void fn_80123F48(Directions_8012430C *pValues, Object_80039F5C *p, Object_80039F5C *)
{
    Point_8017886C pos;
    pos.mX = p->mMotion.mPos.mX;
    pos.mY = p->mMotion.mPos.mY;
    int team = fn_80178320();
    unsigned int count = fn_80178D70(team);
    for (unsigned char i = 0; i < count; i++) {
        float value = 0.0f;
        Object_80039F5C *pOther = PlyrGet(team, i);
        if (pOther == p) continue;
        Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
        float distance = fn_8022781C(&pos, pOtherPos);
        if (!(distance >= 8.5f)) {
            Point_8017886C delta;
            fn_80227690(&delta, pOtherPos, &pos);
            int angle = fn_801CFE40(delta.mY, delta.mX);
            unsigned int direction = (angle + 0x100000) >> 21 & 7;
            if (pOther->mIdBytes[2] == team) {
                Object_80039F5C *pBlocker = 0;
                value = 8.5f - distance;
                if (!(value <= 7.0f)) value = 7.0f;
                if (pOther->mFlags & 0x800) value -= 3.0f;
                int facing = p->mMotion.mFacing;
                if (!(p->mFlags & 0x200000)) {
                    if (!p->mUnknown2913) facing += 0x400000;
                    else facing -= 0x400000;
                    facing &= 0xFFFFFF;
                }
                if (MathAngleDiff(facing, angle) > 0x400000) {
                    float divisor = 0.25f + (1.0f - p->mRatings[6] * 0.003921568859368563f);
                    if (!(divisor >= 0.25f)) divisor = 0.25f;
                    value /= divisor * 4.0f;
                }
                if (!(distance >= 4.0f)) {
                    if ((pOther->mUnknown1032 >= 4 && pOther->mUnknown1032 <= 6)
                        || pOther->mpState->mId == 32 || pOther->mpState->mId == 11 || pOther->mpState->mId == 17) value -= 4.0f;
                    fn_80124714(p, pOther, &pBlocker);
                    if (pBlocker && pBlocker->mIdBytes[2] == fn_80178308()) value -= 4.0f;
                } else {
                    if ((pOther->mUnknown1032 >= 4 && pOther->mUnknown1032 <= 6)
                        || pOther->mpState->mId == 32 || pOther->mpState->mId == 11 || pOther->mpState->mId == 17) value -= 9.0f;
                    fn_80124714(p, pOther, &pBlocker);
                    if (pBlocker && pBlocker->mIdBytes[2] == fn_80178308()) value -= 9.0f;
                }
            }
            if (!(value >= 0.0f)) value = 0.0f;
            float side = value * 0.5f;
            pValues->mCost[direction] += value;
            pValues->mCost[(direction + 1) % 8] += side;
            pValues->mCost[(direction - 1) % 8] += side;
            pValues->mCost[(direction + 3) % 8] -= side;
            pValues->mCost[(direction - 3) % 8] -= side;
            pValues->mCost[(direction + 4) % 8] -= value;
        }
    }
}
}

extern "C" {
float fn_801242E0(Directions_8012430C *pValues, unsigned int index)
{
    return pValues->mCost[index] + pValues->mCost[(index + 7) % 8] + pValues->mCost[(index + 9) % 8];
}
}

extern "C" {
void fn_8012430C(Directions_8012430C *pOut, int kind, Object_80039F5C *p)
{
    memset(pOut, 0, 32);
    if (lbl_8029F584[kind]) lbl_8029F584[kind](pOut, p, 0);
}
}

extern "C" {
void fn_80124374(Directions_8012430C *pOut, int kind, Object_80039F5C *p, Object_80039F5C *a)
{
    memset(pOut, 0, 32);
    if (lbl_8029F584[kind]) lbl_8029F584[kind](pOut, p, a);
}
}

extern "C" {
unsigned char fn_801243E0(Directions_8012430C *pValues, int angle)
{
    float minimum = 32767.0f;
    unsigned char best = 0;
    for (unsigned char i = 0; i < 8; i++) {
        float value = pValues->mCost[i];
        if (!(value >= minimum)) {
            best = i;
            minimum = value;
        } else if (value == minimum) {
            float side = pValues->mCost[(i - 1) & 7] + pValues->mCost[(i + 1) & 7];
            float bestSide = pValues->mCost[(best - 1) & 7] + pValues->mCost[(best + 1) & 7];
            if (!(side >= bestSide)) {
                minimum = value;
                best = i;
            } else if (side == bestSide && angle != -1
                && MathAngleDiff(angle, i << 21) < MathAngleDiff(angle, best << 21)) {
                minimum = pValues->mCost[i];
                best = i;
            }
        }
    }
    return best;
}
}

extern "C" {
Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, unsigned char a, unsigned char count, float *pOut, int b)
{
    Point_8017886C *pPos = (Point_8017886C *)&p->mMotion.mPos;
    float minimum = 3.4028234663852886e38f;
    Object_80039F5C *pBest = 0;
    for (unsigned char i = a; i < count; i++) {
        Object_80039F5C *pOther = PlyrGet(team, i);
        if (pOther != p && (!b || !fn_8011E9B4(pOther))) {
            Point_8017886C delta;
            fn_80227690(&delta, (Point_8017886C *)&pOther->mMotion.mPos, pPos);
            float distance = delta.mX * delta.mX + delta.mY * delta.mY;
            if (!(distance >= minimum)) { minimum = distance; pBest = pOther; }
        }
    }
    *pOut = fn_80260B1C(minimum);
    return pBest;
}
}

extern "C" {
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, unsigned char a, unsigned char count, int angle, float *pOut, int b)
{
    Point_8017886C *pPos = (Point_8017886C *)&p->mMotion.mPos;
    int facing = p->mMotion.mUnknown28 != 0.0f ? p->mMotion.mUnknown32 : p->mMotion.mFacing;
    float minimum = 32767.0f;
    Object_80039F5C *pBest = 0;
    for (unsigned char i = a; i < count; i++) {
        Object_80039F5C *pOther = PlyrGet(team, i);
        if (pOther == p || (b && (pOther->mUnknown1032 >= 4 && pOther->mUnknown1032 <= 6))) continue;
        Point_8017886C delta;
        fn_80227690(&delta, (Point_8017886C *)&pOther->mMotion.mPos, pPos);
        if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), facing) < angle) {
            float distance = delta.mX * delta.mX + delta.mY * delta.mY;
            if (!(distance >= minimum)) { minimum = distance; pBest = pOther; }
        }
    }
    *pOut = fn_80260B1C(minimum);
    return pBest;
}
}

extern "C" {
int fn_80124714(Object_80039F5C *p, Object_80039F5C *pOther, Object_80039F5C **pOut)
{
    Point_8017886C delta;
    Object_800B26B0 *pMotion = &p->mMotion;
    fn_80227690(&delta, (Point_8017886C *)&pOther->mMotion.mPos, (Point_8017886C *)&pMotion->mPos);
    int angle = fn_801CFE40(delta.mY, delta.mX);
    float length = fn_802270A4(&delta);
    float minimum = 1000.0f;
    int result = 1;
    if (pOut) *pOut = 0;
    for (unsigned char team = 0; team < 2; team++) {
        unsigned int count = fn_80178D70(team);
        for (unsigned char i = 0; i < count; i++) {
            Object_80039F5C *pCandidate = PlyrGet(team, i);
            if (pCandidate == p || pCandidate == pOther) continue;
            Point_8017886C *pCandidatePos = (Point_8017886C *)&pCandidate->mMotion.mPos;
            fn_80227690(&delta, pCandidatePos, (Point_8017886C *)&pMotion->mPos);
            if (MathAngleDiff(angle, fn_801CFE40(delta.mY, delta.mX)) <= 0x355554) {
                float distance = fn_802270A4(&delta);
                if (!(distance >= length) && !(distance >= minimum)) {
                    Vector_80039F5C nearest;
                    float offset, unused;
                    fn_80227970(&pMotion->mPos, &pOther->mMotion.mPos, &pCandidate->mMotion.mPos, &nearest, &offset, &unused);
                    if (!(offset >= 0.5f)) {
                        minimum = distance;
                        result = 0;
                        if (pOut) *pOut = pCandidate;
                    }
                }
            }
        }
    }
    return result;
}
}

extern "C" {
int fn_801248D4(Object_80039F5C *p, Vector_80039F5C *pPos, Vector_80039F5C *pTarget, Object_80039F5C **pOut, float margin, float width, Filter_801248D4 *pFilter, Object_80039F5C *pExclude)
{
    int result = 1;
    if (!pPos) pPos = &p->mMotion.mPos;
    pTarget->mZ = 0.0f;
    Vector_80039F5C nearest;
    Vector_80039F5C delta;
    fn_802276B4(&delta, pTarget, pPos);
    int angle = fn_801CFE40(delta.mY, delta.mX);
    float length = fn_802270A4((Point_8017886C *)&delta);
    float minimum = 1000.0f;
    if (pOut) *pOut = 0;
    for (unsigned char team = 0; team < 2; team++) {
        unsigned int count = fn_80178D70(team);
        for (unsigned char i = 0; i < count; i++) {
            int valid = 1;
            Object_80039F5C *pOther = PlyrGet(team, i);
            if (pFilter) {
                for (unsigned char j = 0; j < pFilter->mCount; j++) {
                    if (pOther->mpState->mId == *(pFilter->mValues + j)) {valid = 0; break;}
                }
            }
            if (pOther == p || !valid || pExclude == pOther) continue;
            fn_802276B4(&delta, &pOther->mMotion.mPos, pPos);
            if (MathAngleDiff(angle, fn_801CFE40(delta.mY, delta.mX)) <= 0x355554) {
                float distance = fn_802270A4((Point_8017886C *)&delta);
                if (!(distance >= length + margin) && !(distance >= minimum)) {
                    float offset, unused;
                    fn_80227970(pPos, pTarget, &pOther->mMotion.mPos, &nearest, &offset, &unused);
                    if (!(offset >= width)) {
                        minimum = distance; result = 0;
                        if (pOut) *pOut = pOther;
                    }
                }
            }
        }
    }
    return result;
}
}

extern "C" {
int fn_80124B1C(Object_80039F5C *p, Object_80039F5C *pOther, int angle, float length, float width)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
    int facing = pMotion->mFacing;
    if (pOther != p) {
        Point_8017886C delta;
        fn_80227690(&delta, pOtherPos, (Point_8017886C *)&pMotion->mPos);
        if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), facing) < angle) {
            float distance = fn_802270A4(&delta);
            if (!(distance >= length)) {
                Vector_80039F5C target;
                fn_80227538((Point_8017886C *)&target, facing, length);
                target.mX += pMotion->mPos.mX;
                target.mY += pMotion->mPos.mY;
                target.mZ = pMotion->mPos.mZ;
                Vector_80039F5C nearest;
                float unused;
                fn_80227970(&pMotion->mPos, &target, &pOther->mMotion.mPos, &nearest, &distance, &unused);
                if (width + width > distance) return 1;
            }
        }
    }
    return 0;
}
}

extern "C" {
Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, float length, float width, int facing)
{
    *pOut = 32767.0f;
    Object_80039F5C *pBest = 0;
    for (unsigned char team = 0; team < 2; team++) {
        float distance;
        Object_80039F5C *pOther = fn_80124CE4(p, team, &distance, angle, length, facing, width);
        if (pOther && !(distance >= *pOut)) { *pOut = distance; pBest = pOther; }
    }
    return pBest;
}
}

extern "C" {
Object_80039F5C *fn_80124CE4(Object_80039F5C *p, int team, float *pOut, int angle, float length, int facing, float width)
{
    *pOut = 32767.0f;
    float limit = width + width;
    Object_80039F5C *pBest = 0;
    unsigned int count = fn_80178D70(team);
    Vector_80039F5C *pPos = &p->mMotion.mPos;
    for (unsigned char i = 0; i < count; i++) {
        Object_80039F5C *pOther = PlyrGet(team, i);
        if (pOther == p) continue;
        Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
        Point_8017886C delta;
        fn_80227690(&delta, pOtherPos, (Point_8017886C *)pPos);
        if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), facing) < angle) {
            float distance = fn_802270A4(&delta);
            if (!(distance >= length)) {
                Vector_80039F5C target;
                fn_80227538((Point_8017886C *)&target, facing, length);
                target.mX += pPos->mX;
                target.mY += pPos->mY;
                target.mZ = pPos->mZ;
                Vector_80039F5C nearest;
                float offset, unused;
                fn_80227970(pPos, &target, &pOther->mMotion.mPos, &nearest, &offset, &unused);
                if (!(limit <= offset) && !(distance >= *pOut)) { *pOut = distance; pBest = pOther; }
            }
        }
    }
    return pBest;
}
}

extern "C" {
Object_80039F5C *fn_80124E5C(Object_80039F5C *p, int team, float *pOut, int angle, float length, int facing, float width)
{
    *pOut = 32767.0f;
    float limit = width + width;
    Object_80039F5C *pBest = 0;
    unsigned int count = fn_80178D70(team);
    Vector_80039F5C *pPos = &p->mMotion.mPos;
    for (unsigned char i = 0; i < count; i++) {
        Object_80039F5C *pOther = PlyrGet(team, i);
        if (pOther == p || pOther->mUnknown1032 == 4) continue;
        Point_8017886C *pOtherPos = (Point_8017886C *)&pOther->mMotion.mPos;
        Point_8017886C delta;
        fn_80227690(&delta, pOtherPos, (Point_8017886C *)pPos);
        if (MathAngleDiff(fn_801CFE40(delta.mY, delta.mX), facing) < angle) {
            float distance = fn_802270A4(&delta);
            if (!(distance >= length)) {
                Vector_80039F5C target;
                fn_80227538((Point_8017886C *)&target, facing, length);
                target.mX += pPos->mX;
                target.mY += pPos->mY;
                target.mZ = pPos->mZ;
                Vector_80039F5C nearest;
                float offset, unused;
                fn_80227970(pPos, &target, &pOther->mMotion.mPos, &nearest, &offset, &unused);
                if (!(limit <= offset) && !(distance >= *pOut)) { *pOut = distance; pBest = pOther; }
            }
        }
    }
    return pBest;
}
}

extern "C" {
float fn_80124FE0(Object_80039F5C *p, int kind)
{
    return fn_80125004(p, kind, 0);
}
}

extern "C" {
float fn_80125004(Object_80039F5C *p, int kind, int index)
{
    Directions_8012430C values;

    fn_8012430C(&values, kind, p);
    SortArray(0, values.mCost, 8, sizeof(float), fn_80123254, 0, 0, -2);
    return values.mCost[index];
}
}

extern "C" {
float fn_8012506C(Object_80039F5C *p, int kind)
{
    Directions_8012430C values;
    fn_8012430C(&values, kind, p);
    float sum = 0.0f;
    for (int i = 0; i < 8; i++) sum += values.mCost[i];
    return sum;
}
}

extern "C" {
float fn_801250B8(Object_80039F5C *p, Object_80039F5C *a, int kind)
{
    Directions_8012430C values;
    fn_80124374(&values, kind, p, a);
    float sum = 0.0f;
    for (int i = 0; i < 8; i++) sum += values.mCost[i];
    return sum;
}
}

extern "C" {
int fn_8012510C(Directions_8012430C *pValues)
{
    unsigned int best = fn_801243E0(pValues, -1);
    int angle = best << 21;
    float next = pValues->mCost[(best + 1) % 8];
    float previous = pValues->mCost[(best - 1) % 8];
    float scale = pValues->mCost[best];
    float lower = next;
    int offset = 0x100000;
    if (!(next < previous)) {
        lower = previous;
        offset = -0x100000;
    }
    if (!(scale <= 0.0f)) scale /= lower;
    else if (!(scale >= 0.0f) && !(lower >= 0.0f)) scale = lower / scale;
    else scale = 0.0f;
    return (angle + (int)(offset * scale)) & 0xFFFFFF;
}
}

extern "C" {
int fn_801251FC(Object_80039F5C *p)
{
    return p->mUnknown1032 != 4;
}
}

extern "C" {
int fn_80125214(Object_80039F5C *p, Object_80039F5C *pTarget)
{
    int result = 0;
    Object_80039F5C *pOther;
    float distance;
    if (!pTarget) {
        int team;
        if (fn_801486A0() == 0 || fn_801486A0() == 1) team = p->mIdBytes[2];
        else {
            team = p->mIdBytes[2];
            team ^= 1;
        }
        pOther = fn_801245DC(p, team, 0, fn_80178D18(team), 0x400000, &distance, 1);
    } else {
        pOther = pTarget;
        Point_8017886C delta;
        fn_80227690(&delta, (Point_8017886C *)&p->mMotion.mPos, (Point_8017886C *)&pOther->mMotion.mPos);
        distance = fn_802270A4(&delta);
    }
    if (pOther && pOther != BallGetCurrentHolder() && !(distance >= 3.0f)) result = fn_8011EAC0(p, pOther);
    return result;
}
}

extern "C" {
int fn_80125304(Object_80039F5C *p)
{
    State_80125304 *pState = (State_80125304 *)&p->mUnknown336;
    if (p->mpState->mUnknown1 != 255) {
        int key = 1 | ((p->mIdBytes[2] ^ 1) << 8) | (p->mpState->mUnknown1 << 16);
        pState->mpUnknown0 = fn_8009BCE8(&key);
    } else pState->mpUnknown0 = 0;
    pState->mUnknown4 = 30;
    p->mUnknown512.mUnknown15 = 30;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / gPlyrMoveFwdSpeed;
    p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
    p->mUnknown512.mUnknown4 = p->mMotion.mUnknown32;
    return 0;
}
}

extern "C" {
int fn_801253A8(Object_80039F5C *p)
{
    State_80125304 *pState = (State_80125304 *)&p->mUnknown336;
    pState->mUnknown4--;
    if (pState->mUnknown4 & 0x8000) {
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
        p->mUnknown512.mUnknown0 = 0.72f;
        p->mUnknown512.mUnknown15 = 0;
        return 1;
    }
    p->mUnknown512.mUnknown15 = 30;
    if (!fn_80125214(p, pState->mpUnknown0) && p->mUnknown8 == 255) {
        if (!pState->mpUnknown0) return 1;
        Point_8017886C delta;
        fn_80227690(&delta, (Point_8017886C *)&pState->mpUnknown0->mMotion.mPos, (Point_8017886C *)&p->mMotion.mPos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = angle;
        p->mUnknown512.mUnknown4 = angle;
        p->mUnknown512.mUnknown0 = 1.0f;
    }
    return 0;
}
}

extern "C" {
int fn_80125494(Object_80039F5C *p)
{
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
    p->mUnknown512.mUnknown0 = 0.72f;
    p->mUnknown512.mUnknown15 = 0;
    return 1;
}
}

extern "C" {
int fn_801254C8(Object_80039F5C *p)
{
    Input_800B6D34 input;
    fn_800B6D34(p, &input);
    fn_800B6E68(p, &input);
    return 0;
}
}

extern "C" int fn_80125508() {
    return 0;
}

extern "C" {
int fn_80125510(Object_80039F5C *p, Message_800F01CC *pIn)
{
    int result = 0;
    unsigned char value;

    if (pIn) {
        value = pIn->mUnknown1[0];
    } else {
        value = 255;
    }
    if (fn_801251FC(p)) {
        Message_800F01CC message;

        result = 1;
        memset(&message, 0, sizeof(message));
        message.mId = 96;
        message.mUnknown1[0] = value;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}
}

extern "C" {
void fn_80125594(Object_80039F5C *p, State_80125594 *pState)
{
    Vector_80039F5C target, velocity;
    BallGetPosition(BallGetCurrent(), &target);
    Object_80039F5C *pOther = BallGetCurrentHolder();
    if (!pOther) BallGetVelocity(BallGetCurrent(), &velocity);
    else { velocity.mX = pOther->mMotion.mUnknown40; velocity.mY = pOther->mMotion.mUnknown44; velocity.mZ = pOther->mMotion.mUnknown48; }
    float speed;
    if (!(p->mMotion.mUnknown28 < PlyrMoveGetRatedSpeed(p, 0.14f, 1.0f))) speed = p->mMotion.mUnknown28;
    else speed = PlyrMoveGetRatedSpeed(p, 0.14f, 1.0f);
    Point_8017886C *pPos = (Point_8017886C *)&p->mMotion.mPos;
    int predicted = PursuitGetInterceptAngle((Vector_80039F5C *)pPos, &target, speed, &velocity);
    Point_8017886C delta;
    fn_80227690(&delta, (Point_8017886C *)&target, pPos);
    int toward = fn_801CFE40(delta.mY, delta.mX);
    if (fn_801486A0() == 0) {
        predicted = MathRLerp(predicted, toward, fn_80237260(0));
    }
    pState->mUnknown8 = 1;
    pState->mUnknown4 = 1.0f;
    pState->mUnknown4 -= MathAngleDiff(p->mMotion.mFacing, predicted) * 7.152557657263969e-8f;
    pState->mUnknown0 = predicted;
}
}

extern "C" {
void fn_80125708(Object_80039F5C *p, State_80125594 *pState)
{
    Vector_80039F5C target;
    BallGetPosition(BallGetCurrent(), &target);
    Object_80039F5C *pOther = BallGetCurrentHolder();
    int velocityAngle;
    if (!pOther) {
        Vector_80039F5C velocity;
        BallGetVelocity(BallGetCurrent(), &velocity);
        velocityAngle = fn_801CFE40(velocity.mY, velocity.mX);
    } else velocityAngle = pOther->mMotion.mUnknown32;
    Point_8017886C delta;
    fn_80227690(&delta, (Point_8017886C *)&target, (Point_8017886C *)&p->mMotion.mPos);
    float distance = fn_802270A4(&delta);
    int toward = fn_801CFE40(delta.mY, delta.mX);
    int opposite = (toward + 0x800000) & 0xFFFFFF;
    int blockedA = 0, blockedB = 0;
    if ((MathAngleDiff(velocityAngle, 0x400000) <= 0xFA4F9 && target.mX > fn_80178A08() - 4.0f)
        || (MathAngleDiff(velocityAngle, 0x800000) <= 0xFA4F9 && target.mY > fn_80178A44() - 4.0f)
        || (MathAngleDiff(velocityAngle, 0xC00000) <= 0xFA4F9 && target.mX < 4.0f - fn_80178A08())
        || (MathAngleDiff(velocityAngle, 0) <= 0xFA4F9 && !(target.mY >= 4.0f - fn_80178A44()))) blockedA = 1;
    else if ((MathAngleDiff(velocityAngle, 0xC00000) <= 0xFA4F9 && target.mX > fn_80178A08() - 4.0f)
        || (MathAngleDiff(velocityAngle, 0) <= 0xFA4F9 && target.mY > fn_80178A44() - 4.0f)
        || (MathAngleDiff(velocityAngle, 0x400000) <= 0xFA4F9 && target.mX < 4.0f - fn_80178A08())
        || (MathAngleDiff(velocityAngle, 0x800000) <= 0xFA4F9 && !(target.mY >= 4.0f - fn_80178A44()))) blockedB = 1;
    int difference = (opposite - velocityAngle) & 0xFFFFFF;
    float offset = 0.0f;
    int side = 0;
    if (difference <= 0x7FFFFF) {
        if (!blockedB) {
            side = 1;
            offset = distance * fn_801CFB18(0x800000 - difference);
            offset += (fn_80237260(0) - 0.5f) * 3.0f;
        }
    } else if (!blockedA) {
        offset = distance * fn_801CFB18(difference - 0x800000);
        offset += (fn_80237260(0) - 0.5f) * 3.0f;
    } else side = 1;
    int angle;
    if (!(offset >= distance * 0.25f)) {
        if (side) angle = (velocityAngle + 0x200000) & 0xFFFFFF;
        else angle = (velocityAngle - 0x200000) & 0xFFFFFF;
    } else angle = MathRLerp(velocityAngle, toward, 0.05f);
    if (MathAngleDiff(angle, 0) <= 0x3FFFFF && p->mMotion.mPos.mX > fn_80178A08() - 5.0f) angle = toward;
    else if (MathAngleDiff(angle, 0x400000) <= 0x3FFFFF && p->mMotion.mPos.mY > fn_80178A44() - 5.0f) angle = toward;
    else if (MathAngleDiff(angle, 0x800000) <= 0x3FFFFF && p->mMotion.mPos.mX < 5.0f - fn_80178A08()) angle = toward;
    else if (MathAngleDiff(angle, 0xC00000) <= 0x3FFFFF && !(p->mMotion.mPos.mY >= 5.0f - fn_80178A44())) angle = toward;
    pState->mUnknown8 = 1;
    pState->mUnknown4 = 1.0f;
    pState->mUnknown4 -= MathAngleDiff(p->mMotion.mFacing, angle) * 7.152557657263969e-8f;
    pState->mUnknown0 = angle;
}
}

extern "C" {
void fn_80125B74(Object_80039F5C *p, State_80125594 *pState)
{
    Lookup_8012078C *pLookup = fn_8012078C();
    if (!(p->mFlags & 0x400)) {
        switch (pLookup->mpUnknown12[p->mIdBytes[1]]) {
        case 0: fn_80125594(p, pState); break;
        case 3: fn_80125708(p, pState); break;
        default: fn_80125594(p, pState); break;
        }
        p->mUnknown512.mUnknown15 = pState->mUnknown8;
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = pState->mUnknown0;
        p->mUnknown512.mUnknown4 = pState->mUnknown0;
        p->mUnknown512.mUnknown0 = pState->mUnknown4;
    }
}
}

extern "C" {
int fn_80125C28(Object_80039F5C *p, State_80125594 *)
{
    Object_800B26B0 *pMotion = &p->mMotion;
    Vector_80039F5C target;
    BallGetPosition(BallGetCurrent(), &target);
    Point_8017886C delta;
    fn_80227690(&delta, (Point_8017886C *)&target, (Point_8017886C *)&pMotion->mPos);
    int angle = fn_801CFE40(delta.mY, delta.mX);
    int result = 0;
    unsigned int value = 0;
    if (MathAngleDiff(angle, pMotion->mFacing) <= 0x18E38D) {
        Object_80039F5C *pOther = BallGetCurrentHolder();
        float distance = fn_802270A4(&delta);
        result = PursueGetTackleChance(p, pOther, target, &value, distance);
    }
    if (result) {
        value = (unsigned int)(value * 0.1f);
        if (fn_802372EC(0, 100) < value && fn_800E815C(p, 0, 0)) return 1;
    }
    return 0;
}
}

extern "C" {
int fn_80125D98(Object_80039F5C *p, State_80125594 *pState)
{
    if (fn_800E1584(p)) return 1;
    if (fn_80125C28(p, pState)) return 1;
    return 0;
}
}

extern "C" {
int fn_80125DF0(Object_80039F5C *p)
{
    memset(&p->mUnknown336, 0, 12);
    return 0;
}
}

extern "C" {
int fn_80125E20(Object_80039F5C *p)
{
    State_80125594 *pState = (State_80125594 *)&p->mUnknown336;
    if (!BallGetCurrentHolder()) {
        Message_800F01CC message;
        memset(&message, 0, sizeof(message));
        message.mId = 57;
        message.mUnknown1[0] = BallGetCurrentIndex();
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (!(p->mFlags & 0x400)) {
        fn_80125B74(p, pState);
        if (fn_80125D98(p, pState)) return 0;
    }
    return 0;
}
}



