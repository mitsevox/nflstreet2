#include <math.h>
#include <string.h>

#include "game/Command_800CEE74.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/State_803EB098.h"
#include "game/cu_80067C10.h"
#include "game/Input_800B6D34.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
#include "game/fn_801BE60C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/Input_800B6D34.h"
#include "game/fn_80177FE0.h"
#include "game/Record_800DB60C.h"
#include "game/fn_8022781C.h"
#include "game/fn_800670B4.h"
#include "game/fn_80227638.h"
#include "game/fn_8016871C.h"
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

struct Block_80114A30 {
    char mUnknown0[44];
    int mUnknown44;
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
    char mUnknown0[12];
    float mUnknown12;
    float mUnknown16;
    char mUnknown20[4];
    int mUnknown24;
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
int fn_8011F25C(void);
int fn_8011F290(void);
int fn_800FD2AC(Object_80039F5C *p);
int fn_80112C04(Object_80039F5C *p, Object_80137ABC *pBall, int *pAngle, float *pValue);
void fn_800B6E68(Object_80039F5C *p, Input_800B6D34 *pInput);
int fn_800B7FE8(Object_80039F5C *p);
int fn_8011165C(Object_80039F5C *p);
void fn_800D4F34(int a);
int fn_800CA5CC(Object_80039F5C *p, int a, int b);
void fn_800B8344(Object_80039F5C *p);
void fn_8010D434(Object_80039F5C *p, State_8010D80C *pState);
int fn_8011E8A4(Object_80039F5C *p);
int fn_800B7E60(Object_80039F5C *p);
int fn_800B7F34(Object_80039F5C *p);
int fn_800D0B90(Object_80039F5C *p);
void fn_800D0C0C(Object_80039F5C *p, int a);
extern float lbl_803EAF30;
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

/* Object pointer, three positions, a pair and a float filled by fn_800F39FC
   and passed to fn_800F2EC8, fn_800F30AC, fn_800F3284, fn_800F3838,
   fn_800F3A6C, fn_800F3B54, fn_800F3D38, fn_800F3F90 and fn_800F4038. Only
   the accessed prefix is declared; the size is unknown. */
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

/* View of the player +336 storage shared by fn_800FDA58 and fn_800FF538. */
struct State_800FDA58 {
    short mUnknown0;
    unsigned char mUnknown2;
    char mUnknown3[1];
    int mUnknown4;
    float mUnknown8;
    float mUnknown12;
    int mUnknown16;
    char mUnknown20[28];
    int mUnknown48;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
};

/* View of the player +336 storage used by fn_800FF7A8. */
struct State_800FF7A8 {
    int mUnknown0;
    unsigned char mUnknown4;
};

/* View of the player +336 storage used by fn_800FFDFC, fn_800FFF78 and
   fn_800FFE30. */
struct State_800FFDFC {
    unsigned char mUnknown0;
    char mUnknown1[3];
    float mUnknown4;
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

/* 8-byte item of List_801018B4; only the leading pointer is read. */
struct Item_801018B4 {
    Entry_801018B4 *mpEntry;
    char mUnknown4[4];
};

/* Halfword count followed by items from +8. */
struct List_801018B4 {
    unsigned short mCount;
    char mUnknown2[6];
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

/* 92-byte state allocated through fn_80238174 under the id 'blck'
   (fn_8011DF3C). */
struct Block_803EB028 {
    int mUnknown0;
    char mUnknown4[80];
    unsigned int mUnknown84;
    char mUnknown88[1];
    unsigned char mUnknown89;
    unsigned char mUnknown90;
    char mUnknown91[1];
};

/* 48-byte entry of Plan_80121264; the array fills +0 to +1440. */
struct Entry_80120E98 {
    char mUnknown0[12];
    float mUnknown12;
    char mUnknown16[20];
    int mUnknown36;
    char mUnknown40[8];
};

/* 32-byte entry of Plan_80121264; the array fills +1444 to +2372. */
struct Entry_801230B8 {
    char mUnknown0[16];
    int mUnknown16;
    char mUnknown20[8];
    float mUnknown28;
};

/* 2376-byte record cleared and filled by fn_80121264 (fn_801231E4 keeps one
   on its stack). */
struct Plan_80121264 {
    Entry_80120E98 mUnknown0[30];
    int mUnknown1440;
    Entry_801230B8 mUnknown1444[29];
    unsigned int mUnknown2372;
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
int fn_8009A1A8(Object_80039F5C *p, int a, int b, int c, int index);
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
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value);
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
int fn_800B76E8(Object_80039F5C *p);
int fn_800B7F34(Object_80039F5C *p);
void fn_800B6E68(Object_80039F5C *p, Input_800B6D34 *pInput);
int fn_800EF8E8(Object_80039F5C *p, int a);
int fn_800AD0E4(int team);
int fn_80114D14(int a, unsigned char b, int c, unsigned char d);
int fn_800C53D8(Object_80039F5C *p);
void fn_800D47D4(int a, Object_80039F5C *p);
void fn_8017D8C4(int a, int b, unsigned char c);
void fn_80178718(Object_80039F5C *p);
int fn_801787A0(void);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
int fn_80238278(const void *p, int size, int seed);
int fn_800C8BAC(Object_80039F5C *p, int a);
int fn_800D0B90(Object_80039F5C *p);
void fn_800D4E68(unsigned char a);
unsigned char *fn_8003AB38(Object_80039F5C *p);
int fn_800FD828(Object_80039F5C *p);
void fn_800FD978(Object_80039F5C *p);
void fn_800FF868(Object_80039F5C *p, State_800FFDFC *pState, Object_80039F5C *pOther);
void fn_800FF8FC(Object_80039F5C *p, float *pValue);
int fn_800FFA10(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_800FFB4C(Object_80039F5C *p, Object_80039F5C *pOther, float *pValue, Point_8017886C *pOut);
void fn_800FFD2C(Object_80039F5C *p, Point_8017886C *pPoint);
int fn_80101C40(Object_80039F5C *p);
void fn_8010CFD4(Object_80039F5C *p);
int fn_8011E9D8(State_80039F5C *pState);
int fn_8011F1A4(void);
int fn_8011F228(void);
float fn_8011F4D4(void);
void fn_8013FA8C(int a);
extern float lbl_803EAED8;
extern unsigned int lbl_803EAEDC;
void fn_800A2190(int bit);
void fn_800A60D8(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_80104D98(Object_80039F5C *p);
void fn_801061E8(Object_80039F5C *p, Object_80137ABC *pBall);
void fn_8011F5AC(int index);
void fn_80148108(int mode);
int fn_801481B0(void);
Object_800670B4 *fn_80168708(int team);
int fn_801787A0(void);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
float fn_802276E8(Point_8017886C *pA, Point_8017886C *pB);
float fn_80178A08(void);
float fn_80178A44(void);
int fn_801784E8(void);
int fn_800DC080(Object_80039F5C *p);
void fn_800DBC4C(Object_80039F5C *p, int angle, float value);
int fn_80124714(Object_80039F5C *p, Object_80039F5C *pOther, int a);
float fn_8022710C(void *pV);
Object_800670B4 *fn_80168708(int team);
int fn_801248D4(Object_80039F5C *p, int a, Vector_80039F5C *pPos, Object_80039F5C **ppOut, int b, int c, float x, float y);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, void *pRecord, float e);
int fn_801BA5A8(void *pA, void *pB, unsigned short id, int index);
void fn_800FC290(Object_80039F5C *p, Block_800FCC24 *pBlock, Point_8017886C target);
int fn_800FC648(Object_80039F5C *p, Block_800FCC24 *pBlock);
int fn_800FCE58(Object_80039F5C *p, Block_800FCC24 *pBlock);
int fn_800FCFC0(Object_80039F5C *p);
void fn_800FD178(Object_80039F5C *p, Block_800FD650 *pBlock);
Point_8017886C fn_80177FFC(int team);
unsigned char fn_8009F6B4(void);
int fn_8009F778(Object_80039F5C *p);
void *fn_800AEE20(Object_80039F5C *p);
void fn_8009BD60(Object_80039F5C *p);
int fn_8011F1A4(void);
unsigned char fn_8011F4C8(void);
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
void fn_8013AA00(Object_80137ABC *pBall, float height, float *pTime, Vector_80039F5C *pLanding);
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



extern "C" int fn_800F0FA0(Input_800B6D34 *pBlock, unsigned int *pMasks, int index);
extern "C" void fn_800F05E4(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p);
extern "C" int fn_800F2A40(Object_80039F5C *p);
extern "C" void fn_800F3A6C(Object_80039F5C *pA, Object_80039F5C *pB, Info_800F3A6C *pInfo, Points_800F3A6C *pPoints);

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

extern "C" void fn_800F0FD0(Input_800B6D34 *pBlock, int index) {
    Record_800B8694 *pRecord;
    unsigned int i;

    fn_801D34D0(pBlock, 104, 0, 4);
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
        Point_8017886C pair;
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
            pBlock->mBytes92[i / 8] |= 1 << (i % 8);
        }
    }
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
        fn_801BD81C(&pEntry->mUnknown4C.mpUnknown0, fn_801CFFA0(speed));
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
            fn_801BD81C(&pEntry->mUnknown4C.mpUnknown0, fn_801CFFA0(speed));
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
            } else if ((input.mBytes92[bit / 8] & (1 << bit)) != (1 << bit)) {
                if (time >= 0.5f) {
                    p->mpState->mUnknown1 = 3;
                }
                pBlock->mUnknown6 = 1;
            }
        }
    }
    return 0;
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

extern "C" int fn_800F2AA0(Object_80039F5C *p) {
    Block_800F2AA0 *pBlock = (Block_800F2AA0 *)&p->mUnknown336;
    float scaled;

    if (p->mFlags & 0x4000) {
        pBlock->mUnknown0 = 1;
    } else {
        pBlock->mUnknown0 = 0;
    }
    fn_8009BD60(p);
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 68, p, 1.0f);
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
    fn_8013AA00(pInfo->mpUnknown0, 1.5f, &pInfo->mUnknown48, (Vector_80039F5C *)&pInfo->mUnknown40);
    fn_80137EC4(pInfo->mpUnknown0, &pInfo->mUnknown28);
    fn_80137D58(pInfo->mpUnknown0, &pInfo->mUnknown16);
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
    pOther = fn_80137B40();

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
