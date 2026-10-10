#include <math.h>
#include <string.h>

#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/Team_80167A8C.h"
#include "game/State_803EB098.h"
#include "game/cu_80067C10.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
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
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/Record_800DB60C.h"
#include "game/fn_801BE60C.h"
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
float fn_80237260(int stream);
extern unsigned char lbl_803EAEE8;
extern const float lbl_803ED6CC;
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



extern "C" int fn_800F2A40(Object_80039F5C *p) {
    Object_80039F5C *pOther = fn_80137B40();

    if (pOther != 0) {
        Point_8017886C delta;

        fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        fn_801CFFD0(fn_801CFE40(delta.mY, delta.mX), p->mMotion.mFacing);
    }
    return 1;
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















extern "C" int fn_800F4A74(Object_80039F5C *p) {
    Block_800F4A74 *pBlock = (Block_800F4A74 *)&p->mUnknown336;

    memset(pBlock, 0, 88);
    pBlock->mUnknown62 = fn_801374E0(fn_801374BC());
    pBlock->mUnknown63 = 0;
    pBlock->mUnknown36 = 0;
    pBlock->mUnknown40 = 0xC00000;
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

extern "C" Point_8017886C fn_800F97A8(Object_80039F5C *p) {
    Point_8017886C base;
    Object_800670B4 *pTeam;
    Entry_8006719C *pEntry;
    Point_8017886C point;

    base = fn_80177FFC(p->mIdBytes[2]);
    pTeam = fn_80168708(p->mIdBytes[2]);
    pEntry = &pTeam->mUnknown8.mUnknown84[0][p->mIdBytes[1]];
    point.mX = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mX;
    point.mY = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mY;
    fn_80227638(&point, &point, &base);
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
        if (fn_80039F5C(fn_80178320(), i)->mUnknown2914 == 14) {
            count++;
        }
    }
    state = p->mUnknown2914;
    pos = fn_800F97A8(p);
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
        } else {
            result = 10;
            if (pos.mX > base.mX) {
                result = 14;
            }
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

        *pp = fn_80039F5C(fn_80178308(), i);
        state = (*pp)->mUnknown2914;
        if (fn_8011F1CC() && mode != 2) {
            Object_800670B4 *pTeam = fn_80168708(fn_80178308());
            void *pInfo = fn_800AEE20(*pp);

            if (!pInfo) {
                if (pTeam->mUnknown8.mUnknownF == 0) {
                    pInfo = fn_80164EC8(fn_8016871C((*pp)->mIdBytes[2]), ((*pp)->mId >> 8) & 0xFF, ((*pp)->mId >> 16) & 0xFF);
                } else {
                    unsigned char index = fn_80163E94(pTeam, (*pp)->mIdBytes[1], 0)->mUnknownB;
                    pInfo = fn_80164EC8(fn_8016871C((*pp)->mIdBytes[2]), (*pp)->mIdBytes[2], index);
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
        x = fn_800F97A8(*pp).mX;

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

extern "C" void fn_800FC290(Object_80039F5C *p, Block_800FCC24 *pBlock, Point_8017886C target) {
    Object_800B26B0 *pMotion = &p->mMotion;

    pBlock->mUnknown32 = 1;
    pBlock->mUnknown4[1].mX = target.mX;
    pBlock->mUnknown4[1].mY = target.mY;
    if (pMotion->mUnknown28 < lbl_803ECB08 * 0.07f) {
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

        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, animation, p, 1.0f);
        index = fn_801BA5A8(p->mpUnknown796, p->mpUnknown800, animation, 0);
        p->mpUnknown800[index].mUnknown44 = speed;
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
    if (!fn_801248D4(p, 0, &point, &pOther, 0, 0, 0.0f, 0.5f)) {
        Point_8017886C delta;

        fn_80227690(&delta, &pOther->mMotion.mPos, pMotion);
        if (fn_802270A4(&delta) < 2.5f) {
            int toOther = fn_801CFE40(delta.mY, delta.mX);
            int toTarget;

            fn_80227690(&delta, &pBlock->mUnknown4[pBlock->mUnknown32], pMotion);
            toTarget = fn_801CFE40(delta.mY, delta.mX);
            if (fn_801CFFD0(toTarget, toOther) <= 0x11C71B) {
                if (fn_801CFFD0(toTarget, 0) <= 0x3FFFFF) {
                    result = fn_801CFFD0(toOther, toTarget) - 0x200000;
                } else {
                    result = 0x200000 - fn_801CFFD0(toOther, toTarget);
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
    turn = fn_801CFFD0(direction, p->mMotion.mFacing);
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
            if (fn_801CFFD0(p->mMotion.mFacing, 0x400000) <= 0x38E37) {
                if (turn > 0x7C71C7) {
                    if (fn_801CFFD0(p->mMotion.mFacing, 0x400000) <= 0x38E37) {
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
    Object_800670B4 *pTeam;
    Entry_8006719C *pEntry;
    Point_8017886C *pOffset;
    Point_8017886C target;

    ball = fn_80177FE0();
    pTeam = fn_80168708(p->mIdBytes[2]);
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
    fn_80067E3C(120, &p->mMotion.mPos, p->mId, 0, 0, 0);
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

    if (p->mIdBytes[3] == 1 && p->mpState->mUnknown4 == 18 && fn_8011F1CC()) {
        int team = fn_80178320();
        unsigned char i = 0;
        Vector_80039F5C *pPos = &p->mMotion.mPos;
        Point_8017886C ball;
        float limit;

        ball = fn_80177FE0();
        limit = ball.mY - 1.0f;
        for (; i < 7; i++) {
            Object_80039F5C *pOther = fn_80039F5C(team, i);
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
                    if (fn_801CFFD0(angle, fn_801CFE40(toCarrier.mY, toCarrier.mX)) > 0x400000
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
        if (!fn_800DC080(p)) {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = pBlock->mUnknown16;
            p->mUnknown512.mUnknown4 = pBlock->mUnknown16;
            p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
        } else {
            fn_800DBC4C(p, pBlock->mUnknown16, pBlock->mUnknown12);
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
            if (fn_80039F5C(fn_80178308(), i)->mpState->mId == 56) {
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

extern "C" int fn_800FD7D0(Object_80039F5C *p)
{
    Object_800670B4 *pTeam = fn_80168708(p->mIdBytes[2]);
    Entry_8006719C *pEntry = &pTeam->mUnknown8.mUnknown84[0][p->mIdBytes[1]];

    return pTeam->mUnknown8.mUnknownF == 1 ? pEntry->mUnknown24 : pEntry->mUnknown20;
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

extern "C" int fn_800FF860() {
    return 1;
}

extern "C" void fn_800FF8DC(Object_80039F5C *p, State_800FFDFC *pState)
{
    fn_8009D1AC(p);
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
    Object_80039F5C *pOther = fn_80137B40();
    State_800FFDFC *pState = (State_800FFDFC *)&p->mUnknown336;
    Message_800F01CC message;
    Point_8017886C point;

    if (fn_8010A2DC(p, 0, -1) != 0) {
        pState->mUnknown0 = 1;
    }
    if (*fn_8003AB38(p) == 57 && p->mUnknown3040 > 30) {
        p->mUnknown3040 = 30;
    }
    if (pOther != 0) {
        if (p == pOther) {
            fn_801C1F94(&message, 0, 4);
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
        p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
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

        if (fn_80137C48(p) != 0) {
            result = fn_80178308() == p->mIdBytes[2];
        }
        return result;
    }
    return p == fn_80137B40();
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

extern "C" unsigned int fn_80100B0C(void)
{
    return fn_802372EC(0, 0x1000000);
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
        value = fn_801CFFD0(p->mMotion.mUnknown32 - ((p->mMotion.mFacing + fn_800C8BAC(p, 0)) & 0xFFFFFF),
                            pEntry->mUnknown8);
        *pOut = value;
        if (p->mUnknown1008.mUnknown0 == 1 || p->mUnknown1008.mUnknown0 == 2 || value <= 0x3FFFFF) {
            score = 6;
        }
        value = fn_801CFFD0(b, pEntry->mUnknown12);
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
                    && fn_801CFFD0(p->mMotion.mFacing, 0) <= 0x3FFFFF)
                || (p->mUnknown2913 == 1
                    && fn_801CFFD0(p->mMotion.mFacing, 0x800000) <= 0x3FFFFF)) {
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

extern "C" void fn_801024FC(Object_80039F5C *p, int kind, int b, int c, int d)
{
    Message_800F01CC message;

    p->mUnknown512.mUnknown14 = 0;
    fn_800D0BF4(p, d, 15);
    fn_801C1F94(&message, 0, 4);
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
        fn_800D4E68(fn_800D0B90(p));
        fn_8013FA8C(3);
        fn_800F053C(0, p->mpState, &message, p);
        fn_801C1F94(&message, 0, 4);
        message.mId = 33;
        fn_800F01CC(0, p->mpState, &message, p);
        break;
    }
}

extern "C" int fn_80103D6C(Object_80039F5C *p)
{
    int result = 0;
    Object_80039F5C *pOther = fn_80137B40();

    if (pOther != 0) {
        State_80039F5C *pState = pOther->mpState;

        if (pState->mId == 15 && pState->mUnknown1 != 4) {
            result = pState->mUnknown2 == p->mIdBytes[1];
        }
    }
    return result;
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

extern "C" int fn_80105898(Object_80039F5C *p) {
    Message_800F01CC message;
    Vector_80039F5C ball;
    Point_8017886C delta;
    State_80105898 *pState = (State_80105898 *)&p->mUnknown336;
    Record_8011F518 *pRecord = fn_8011F518();
    Object_80039F5C *pTarget = fn_80039F5C(p->mIdBytes[2], p->mpState->mUnknown1);
    int kind = 3;

    fn_80137D58(fn_801374BC(), &ball);
    fn_80227690(&delta, &ball, &p->mMotion.mPos);
    if (((fn_801CFE40(delta.mY, delta.mX) - p->mMotion.mFacing) & 0xFFFFFF) <= 0x7FFFFF) {
        kind = 6;
    }
    if (p->mpState->mUnknown2 == 9 || p->mpState->mUnknown2 == 11) {
        fn_800D6914(fn_800D0B90(p) != 0, p);
    }
    fn_80106678(pRecord, pTarget, kind, p->mpState->mUnknown2);
    pState->mUnknown0 = 2;
    pState->mUnknown1 = 0;
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~0x1000;
    p->mFlags &= ~4;
    if (pRecord->mUnknown4 != 8) {
        if (p == fn_80137B40()) {
            if (!(pRecord->mUnknown4 == 10 || pRecord->mUnknown4 == 1 || pRecord->mUnknown4 == 13 ||
                  pRecord->mUnknown4 == 3 || pRecord->mUnknown4 == 5 || pRecord->mUnknown4 == 7) &&
                (pRecord->mUnknown4 <= 1 || pRecord->mUnknown4 == 12 || pRecord->mUnknown4 == 13 ||
                 pRecord->mUnknown4 == 6 || pRecord->mUnknown4 == 7 ||
                 (pRecord->mUnknown4 >= 14 && pRecord->mUnknown4 <= 15))) {
                fn_80137C10(pTarget);
            }
            if (!fn_80105E90(p, pTarget, pRecord->mUnknown4)) {
                fn_801C1F94(&message, 0, 4);
                message.mId = 1;
                fn_800F053C(0, p->mpState, &message, p);
            }
        }
    } else if (p->mpState->mUnknown4 == 31) {
        fn_8011E1BC(p, 0, 0, 1);
        fn_8011E3EC(p, 1);
    } else if (p->mpState->mUnknown4 == 33) {
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
    if (pRecord->mUnknown4 == 8 && fn_80137C48(p) == 0) {
        return 1;
    }
    if (pState->mUnknown0 != 0) {
        p->mFlags &= ~4;
        if (--pState->mUnknown0 == 0) {
            fn_80104D98(p);
        }
    }
    if (p->mFlags & 0x1000) {
        Object_80137ABC *pBall = fn_80137C48(p);

        if (pBall != 0 && fn_801787A0() == 0) {
            fn_801061E8(p, pBall);
            if (pRecord->mUnknown4 != 8) {
                fn_80067E3C(60, &p->mpUnknown4->mUnknown4, p->mId, 0, 0, 0);
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
            if (fn_800B65A0(p->mIdBytes[2]) != 255 && fn_8011F1A4() == 0 && fn_801481B0() == 0) {
                fn_80148108(0);
                fn_8013FA8C(2);
            }
            if (fn_800B65A0(p->mIdBytes[2]) == 255 && fn_8011F1A4() == 0) {
                fn_8013FA8C(2);
            }
        }
        if (pRecord->mUnknown4 != 8) {
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown4 = p->mMotion.mFacing;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
        }
    }
    return result;
}

extern "C" void fn_80105DF0(Message_800F01CC *pMessage) {
    Object_800670B4 *pObject;
    unsigned int count;
    unsigned char i;

    if (pMessage->mUnknown1[2] == 1) {
        pMessage->mUnknown1[2] = 2;
    } else if (pMessage->mUnknown1[2] == 2) {
        pMessage->mUnknown1[2] = 1;
    }
    pObject = fn_80168708(fn_80178308());
    count = fn_80178D18(fn_80178308());
    for (i = 0; i < count; i++) {
        if (fn_80163E94(pObject, i, 0)->mUnknownB == pMessage->mUnknown1[0]) {
            pMessage->mUnknown1[0] = i;
            break;
        }
    }
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
            if (pRecord->mUnknown4.mUnknown0 == kinds[j] && fn_8010B3A0(p, pRecord->mUnknown4.mUnknown1)) {
                if ((pRecord->mUnknown4.mUnknown2 == 1 && p->mUnknown776 == 2) ||
                    (pRecord->mUnknown4.mUnknown2 == 2 && p->mUnknown776 == 1) || fn_80137B40() != p) {
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

extern "C" int fn_8010CE90(Object_80039F5C *p, Object_80137ABC *pBall)
{
    State_8010CAE8 *pState = (State_8010CAE8 *)&p->mUnknown336;

    return fn_80112C04(p, pBall, &pState->mUnknown16, &pState->mUnknown12);
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

    if (fn_80137B40() != p) {
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

extern "C" int fn_8010D36C(Object_80039F5C *p, Object_80137ABC *pBall, State_8010D80C *pState)
{
    int result = 0;
    Vector_80039F5C pos;
    Vector_80039F5C velocity;
    float time;

    if (pState->mUnknown26 == 0) {
        fn_80137D58(pBall, &pos);
        fn_80137EC4(pBall, &velocity);
        time = fn_8022781C(&pos, pState) / fn_802270A4(&velocity);
        result = pState->mUnknown16 >= time;
    }
    if (result && (p->mUnknown1008.mUnknown0 == 2 || p->mUnknown1008.mUnknown0 == 3)) {
        if (fn_8013BA58(pBall, 0) != 2) {
            result = 0;
        }
    }
    return result;
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
    Object_80137ABC *pBall;
    Record_800B15FC *pRecord;
    Vector_80039F5C pos;

    fn_800B8344(p);
    pBall = fn_801374BC();
    fn_80137D58(pBall, &pos);
    if (fn_8010D36C(p, pBall, pState)) {
        fn_8010D434(p, pState);
    } else if ((p->mFlags & 4) && fn_80137C48(p)) {
        pRecord = fn_800B15FC();
        result = 1;
        pRecord->mUnknownC = pos.mX;
        pRecord->mUnknown10 = pos.mY;
        fn_8009BD2C(p, &pRecord->mUnknown0);
        pRecord->mUnknown14 = 4;
        fn_800B1508();
        fn_80138398(pBall, 0);
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
            if (fn_801CFFD0(p->mUnknown512.mUnknown4, fn_801CFE40(delta.mY, delta.mX)) > 0x600000) {
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

extern "C" int fn_8010FD8C() {
    return 1;
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
        if (p != fn_80137B40()) {
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
        delta = fn_801CFFD0(target, angle);
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
        if (fn_800D0B90(p)) {
            pRecord = pTable->mEntries[index].mpRecord;
            fn_800D0C0C(p, pRecord->mUnknown7);
        } else {
            fn_800D0C0C(p, 0);
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
        fn_800D0BF4(p, c, 35);
        fn_801C1F94(&message, 0, 4);
        message.mId = 35;
        message.mUnknown1[0] = a;
        message.mUnknown1[1] = b;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

extern "C" int fn_80110C68(Object_80039F5C *p)
{
    return ((State_80113AAC *)&p->mUnknown336)->mUnknown14;
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

extern "C" int fn_80111104(Object_80039F5C *p)
{
    State_80111104 *pState = (State_80111104 *)&p->mUnknown336;
    short value;

    pState->mUnknown4 = p->mRatings[2];
    if (p->mpState->mUnknown1 != 3) {
        pState->mUnknown0 = fn_80110EE4(p);
        if (pState->mUnknown0 != 22) {
            fn_800D4F34(1);
            pState->mUnknown6 = lbl_803EAF5E + (pState->mUnknown4 >> 4);
            value = pState->mUnknown4 + 20;
            p->mRatings[2] = value > 255 ? 255 : value;
            if (fn_800CA5CC(p, 2, 1)) {
                pState->mUnknown0++;
            }
            p->mUnknown512.mUnknown15 = pState->mUnknown0Bytes[3];
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown0 = p->mMotion.mUnknown28 / lbl_803ECB08;
            p->mUnknown512.mUnknown4 = p->mUnknown512.mUnknown8 = p->mMotion.mUnknown32;
        }
        return 0;
    }
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

extern "C" int fn_80111794(Object_80039F5C *p)
{
    State_80111794 *pState = (State_80111794 *)&p->mUnknown336;

    pState->mUnknown0 = fn_8011165C(p);
    pState->mUnknown4 = 70 - p->mRatings[0] / 16;
    p->mUnknown512.mUnknown14 = 0;
    p->mUnknown512.mUnknown15 = pState->mUnknown0Bytes[3];
    return 0;
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
            ((input.mUnknown93 & 4) && fn_800EF8E8(p, flag) != 0)) {
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

extern "C" int fn_80114A30(Object_80039F5C *p, int a)
{
    State_80114DF4 *state = (State_80114DF4 *)&p->mUnknown336;
    Object_80039F5C *pOther = fn_80039F5C((unsigned char)(1 - p->mIdBytes[2]), p->mpState->mUnknown3[0]);
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
            ((Block_80114A30 *)&p->mUnknown1160)->mUnknown44++;
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
        fn_8017D8C4(p->mId, pOther->mId, 0);
    }
    if (fn_801787A0() != 0 || (fn_80137B40() != p && fn_80137B40() != pOther)) {
        result = 3;
        if (fn_802372EC(0, 100) < 50) {
            result = 2;
        }
    }
    pOtherState->mUnknown14 = result;
    state->mUnknown56 = result;
    if (result != 1) {
        fn_80067DB8(102, &p->mMotion.mPos, result, 0, 0);
        fn_8017D9B0(p->mId, pOther->mId);
        if (result == 2) {
            fn_800D47D4(0, p);
        }
        if (result == 3) {
            fn_800D47D4(1, p);
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

extern "C" {

extern Block_803EB028 *lbl_803EB028;
extern State_803EB098 *lbl_803EB098;
extern Lookup_8012078C *lbl_803EB09C;
extern float lbl_802DB004[];

int fn_80165098(Record_80067338 *pRecord);
int fn_801650BC(Record_80067338 *pRecord);
int fn_801650DC(Record_80067338 *pRecord);
int fn_801650FC(Record_80067338 *pRecord);
void fn_8016444C(Object_800670B4 *p);
void fn_800A5A88(void *p);
void fn_801F51DC(int a, void *pBase, int count, int size, int (*pCompare)(void *, void *),
                 void (*pSwap)(void *, void *), int b, int c);

void fn_80119020(void);
void fn_801194F0(void);
void fn_80119B98(void);
void fn_8011AB38(void);
void fn_8011D9B8(void);
void fn_8011DBC8(Object_80039F5C *p, Block_8011DBC8 *pBlock);
void fn_8011DCDC(void);
void fn_8011E33C(Object_80039F5C *p, Object_80039F5C *pOther, int value);
int fn_8011FA78(void *pA, void *pB);
int fn_8011FAFC(void *pA, void *pB);
int fn_8011FB80(void *pA, void *pB);
void fn_8011FE0C(void);
void fn_80120384(void);
void fn_80121264(Object_80039F5C *p, Plan_80121264 *pPlan);
void fn_80122670(Object_80039F5C *p, Plan_80121264 *pPlan, int angle);
void fn_801227DC(Object_80039F5C *p, Plan_80121264 *pPlan, Entry_801230B8 *pEntry);
Entry_801230B8 *fn_801230B8(Plan_80121264 *pPlan);
int fn_80123254(void *pA, void *pB);
void fn_8012430C(float *pOut, int kind, Object_80039F5C *p);
float fn_801CFB94(int angle);

void fn_8011DA40(void)
{
    int team = fn_80178308();
    unsigned char side;

    lbl_803EB028->mUnknown84++;
    for (side = 0; side < 2; side++) {
        unsigned int count = fn_80178D70(side);
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *p = fn_80039F5C(side, i);
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

void fn_8011DBC0(Object_80039F5C *p)
{
}

void fn_8011DBC4(Object_80039F5C *p)
{
}

int fn_8011DC68(unsigned int id);

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

void fn_8011DF3C(void)
{
    void *pHandle = fn_80238174(0, (void **)&lbl_803EB028, sizeof(Block_803EB028), 0, 0x626C636B);

    fn_8023816C(pHandle);
    fn_802381E0(pHandle);
}

void fn_8011DF8C(void)
{
}

void fn_8011E938(Object_80039F5C *p);

void fn_8011DF90(void)
{
    unsigned char side;
    int team;

    fn_801C1F94(lbl_803EB028->mUnknown4, 0, sizeof(lbl_803EB028->mUnknown4));
    lbl_803EB028->mUnknown84 = 0;
    lbl_803EB028->mUnknown90 = 0;
    fn_8011E938(0);
    team = fn_80178308();
    for (side = 0; side < 2; side++) {
        unsigned int count = fn_80178D18(side);
        unsigned char i;

        for (i = 0; i < count; i++) {
            Object_80039F5C *p = fn_80039F5C(team, i);

            fn_801C1F94(&p->mBlock1032, 0, sizeof(p->mBlock1032));
            fn_8011DBC8(p, &p->mUnknown1072);
            p->mUnknown1139 = 5;
            p->mUnknown1138 = 0;
        }
        team = fn_80178320();
    }
}

void fn_8011E3EC(Object_80039F5C *p, int a);

void fn_8011E068(void)
{
    int team = fn_80178308();
    unsigned int count = fn_80178D70(team);
    unsigned char i;

    for (i = 0; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);

        if (p->mpState->mId == 51) {
            if (p->mpState->mUnknown4 == 33) {
                fn_8011E1BC(p, 0, 0, 1);
                fn_8011E3EC(p, 2);
            } else if (p->mpState->mUnknown4 == 31) {
                fn_8011E1BC(p, 0, 0, 1);
                fn_8011E3EC(p, 1);
            }
        }
    }
    fn_8011DCDC();
    lbl_803EB028->mUnknown89 = 1;
}

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

unsigned int fn_8011E188(void)
{
    return lbl_803EB028->mUnknown84;
}

void fn_8011E194(Object_80039F5C *p, unsigned char mask)
{
    Block_8011E240 *pBlock = &p->mBlock1032;

    pBlock->mUnknown100 |= mask;
}

void fn_8011E1A8(Object_80039F5C *p, unsigned char mask)
{
    Block_8011E240 *pBlock = &p->mBlock1032;

    pBlock->mUnknown100 &= ~mask;
}

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

void fn_8011E3A4(Object_80039F5C *p);

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
        fn_80143EBC(p, pOther);
        fn_80143EBC(pOther, p);
        fn_8009BD2C(p, &ref);
        if (pOther->mUnknown1036 == ref) {
            fn_8011E3A4(pOther);
        }
    }
    fn_8009BD2C(0, &pBlock->mUnknown4);
    pOther = fn_8009BCE8(&pBlock->mUnknown8);
    if (pOther) {
        fn_80143EBC(p, pOther);
        fn_80143EBC(pOther, p);
        fn_8009BD2C(p, &ref);
        if (pOther->mUnknown1036 == ref) {
            fn_8011E3A4(pOther);
        }
    }
    fn_8009BD2C(0, &pBlock->mUnknown8);
}

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

void fn_8011E3EC(Object_80039F5C *p, int a)
{
    p->mUnknown1052 = a;
}

void fn_8011E884(Object_80039F5C *p, int a)
{
    p->mUnknown1072.mUnknown52 = a;
}

int fn_8011E88C(Object_80039F5C *p)
{
    return p->mUnknown1072.mUnknown52 != 0;
}

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

void fn_8011E938(Object_80039F5C *p)
{
    fn_8009BD2C(p, &lbl_803EB028->mUnknown0);
}

int fn_8011F1A4(void);
unsigned char fn_8011F4C8(void);

int fn_8011E95C(void)
{
    int result = 0;

    if (fn_8011F1A4() && fn_8011F4C8() <= 3) {
        result = lbl_803EB028->mUnknown84 < 60;
    }
    return result;
}

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

void fn_8011F174(void)
{
    fn_800A5A88(lbl_803EB098->mUnknown528);
    lbl_803EB098 = 0;
}

int fn_8011F1A4(void)
{
    return fn_801650BC(fn_8016871C(fn_80178308()));
}

int fn_8011F1CC(void)
{
    return fn_801650DC(fn_8016871C(fn_80178308()));
}

int fn_8011F1F4(void)
{
    return fn_8016871C(fn_80178308())->mUnknown17 == 14;
}

int fn_8011F228(void)
{
    return fn_8016871C(fn_80178308())->mUnknown17 == 16;
}

int fn_8011F25C(void)
{
    return fn_8016871C(fn_80178308())->mUnknown14 == 4;
}

int fn_8011F290(void)
{
    return fn_8016871C(fn_80178308())->mUnknown14 == 18;
}

int fn_8011F2C4(void)
{
    return fn_8016871C(fn_80178308())->mUnknown17 == 2;
}

int fn_8011F2F8(void)
{
    return fn_8016871C(fn_80178308())->mUnknown17 == 5;
}

int fn_8011F32C(void)
{
    return fn_801650FC(fn_8016871C(fn_80178308()));
}

int fn_8011F354(void)
{
    return fn_801650FC(fn_8016871C(fn_80178348()));
}

void fn_8011F3A8(void)
{
    if (fn_8011F1A4()) {
        lbl_803EB098->mUnknown4 = fn_8016871C(fn_80178308())->mUnknown1C[0][0];
        if (fn_80168708(fn_80178308())->mUnknown8.mUnknownF) {
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

void fn_8011F45C(int a)
{
    if (lbl_803EB098->mUnknown5) {
        lbl_803EB098->mUnknown4 = a;
    } else if (fn_8016871C(fn_80178308())->mUnknown14 == 2) {
        lbl_803EB098->mUnknown4 = a;
        lbl_803EB098->mUnknown5 = 1;
    }
    fn_8011F068();
}

unsigned char fn_8011F4C8(void)
{
    return lbl_803EB098->mUnknown4;
}

float fn_8011F4D4(void)
{
    return lbl_803EB098->mUnknown0;
}

Record_8011F4E0 *fn_8011F4E0(void)
{
    return &lbl_803EB098->mUnknown8;
}

void *fn_8011F4EC(void)
{
    return lbl_803EB098->mUnknown56;
}

Record_8011F4F8 *fn_8011F4F8(int index)
{
    return &lbl_803EB098->mUnknown576[index];
}

void *fn_8011F50C(void)
{
    return lbl_803EB098->mUnknown528;
}

Record_8011F518 *fn_8011F518(void)
{
    return &lbl_803EB098->mUnknown512;
}

int fn_8011F524(void)
{
    return fn_80165098(fn_8016871C(fn_80178348()));
}

void fn_8011F54C(void)
{
    fn_8016444C(fn_80168708(fn_80178308()));
}

void fn_8011F574(void)
{
    unsigned char i;

    for (i = 0; i < 2; i++) {
        lbl_803EB098->mUnknown6[i] = 0;
    }
}

unsigned char fn_8011F59C(int index)
{
    return lbl_803EB098->mUnknown6[index];
}

void fn_8011F5AC(int index)
{
    unsigned char *pCount = lbl_803EB098->mUnknown6;

    if (pCount[index] < 255) {
        pCount[index]++;
    }
}

void fn_8011F5CC(Lookup_8012078C *pLookup)
{
    short count = pLookup->mUnknown16;

    pLookup->mpUnknown0 = (unsigned char *)fn_801D2B7C(count, 0, 0);
    fn_801C1F94(pLookup->mpUnknown0, 0, count);
    pLookup->mpUnknown4 = (unsigned char *)fn_801D2B7C(count, 0, 0);
    fn_801C1F94(pLookup->mpUnknown4, 0, count);
    pLookup->mpUnknown8 = (Entry_8011FBE0 *)fn_801D2B7C(pLookup->mUnknown16 * sizeof(Entry_8011FBE0), 0, 0);
    fn_801C1F94(pLookup->mpUnknown8, 0, pLookup->mUnknown16 * sizeof(Entry_8011FBE0));
    pLookup->mpUnknown12 = (int *)fn_801D2B7C(pLookup->mUnknown16 * sizeof(int), 0, 0);
    fn_801C1F94(pLookup->mpUnknown12, 0, pLookup->mUnknown16 * sizeof(int));
}

int fn_8011F698(void *p, int value)
{
    fn_8011F5CC((Lookup_8012078C *)p);
    return 0;
}

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

int fn_8011F99C(void *p, void *pBuffer)
{
    Lookup_8012078C *pLookup = (Lookup_8012078C *)p;

    *pLookup = *(Lookup_8012078C *)pBuffer;
    pBuffer = (char *)pBuffer + sizeof(Lookup_8012078C);
    memcpy(pLookup->mpUnknown0, pBuffer, pLookup->mUnknown16);
    pBuffer = (char *)pBuffer + pLookup->mUnknown16;
    memcpy(pLookup->mpUnknown4, pBuffer, pLookup->mUnknown16);
    pBuffer = (char *)pBuffer + pLookup->mUnknown16;
    memcpy(pLookup->mpUnknown8, pBuffer, pLookup->mUnknown16 * sizeof(Entry_8011FBE0));
    pBuffer = (char *)pBuffer + pLookup->mUnknown16 * sizeof(Entry_8011FBE0);
    memcpy(pLookup->mpUnknown12, pBuffer, pLookup->mUnknown16 * sizeof(int));
    return 1;
}

int fn_8011FA54(void *p)
{
    short count = lbl_803EB09C->mUnknown16;

    return sizeof(Lookup_8012078C) + count + count + count * sizeof(Entry_8011FBE0) + count * sizeof(int);
}

void fn_8011FBA8(void *pA, void *pB)
{
    unsigned char *pFirst = (unsigned char *)pA;
    unsigned char *pSecond = (unsigned char *)pB;
    unsigned char value = *pFirst;

    *pFirst = *pSecond;
    *pSecond = value;
}

void fn_8011FBBC(void *pA, void *pB)
{
    Entry_8011FBE0 *pFirst = (Entry_8011FBE0 *)pA;
    Entry_8011FBE0 *pSecond = (Entry_8011FBE0 *)pB;
    Entry_8011FBE0 entry = *pFirst;

    *pFirst = *pSecond;
    *pSecond = entry;
}

void fn_8011FBE0(void)
{
    int team = fn_80178320();
    Object_80039F5C *pPlayer = fn_80137B40();
    Vector_80039F5C pos;
    unsigned char count;
    unsigned char i;

    if (pPlayer) {
        pos.mX = pPlayer->mMotion.mPos.mX;
        pos.mY = pPlayer->mMotion.mPos.mY;
    } else if (!fn_80138064(fn_801374BC(), &pos)) {
        fn_80137D58(fn_801374BC(), &pos);
    }
    count = fn_80178D70(team);
    for (i = 0; i < count; i++) {
        Entry_8011FBE0 *pEntry = &lbl_803EB09C->mpUnknown8[i];

        pEntry->mUnknown0 = fn_8022781C(&fn_80039F5C(team, i)->mMotion.mPos, &pos);
        pEntry->mUnknown4 = i;
    }
}

void fn_8011FCA4(void)
{
    int count = fn_80178D70(fn_80178320());

    fn_801F51DC(1, lbl_803EB09C->mpUnknown0, count, 1, fn_8011FA78, fn_8011FBA8, 0, 0);
    fn_801F51DC(1, lbl_803EB09C->mpUnknown4, count, 1, fn_8011FAFC, fn_8011FBA8, 0, 0);
    fn_8011FBE0();
    fn_801F51DC(1, lbl_803EB09C->mpUnknown8, count, sizeof(Entry_8011FBE0), fn_8011FB80, fn_8011FBBC, 0, 1);
}

int fn_8011FD64(unsigned char index)
{
    int result;

    switch (fn_80039F5C(fn_80178320(), index)->mUnknown2914) {
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

void fn_8012060C(void)
{
    lbl_803EB09C = 0;
}

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

Lookup_8012078C *fn_8012078C(void)
{
    return lbl_803EB09C;
}

void fn_80120B4C(int value, int *pList, unsigned char i, unsigned char count)
{
    for (; i < count; i++) {
        if (value == pList[i]) {
            pList[i] = 0;
            return;
        }
    }
}

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
            if (pOther->mUnknown3048.mId == 47) {
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

void fn_80120E98(Plan_80121264 *pPlan, int index)
{
    int last = pPlan->mUnknown1440 - 1;

    if (index != last) {
        memcpy(&pPlan->mUnknown0[index], &pPlan->mUnknown0[index + 1], (last - index) * sizeof(Entry_80120E98));
    }
    pPlan->mUnknown1440--;
}

void fn_80123024(Object_80039F5C *p, Plan_80121264 *pPlan, int angle)
{
    unsigned char i;

    for (i = 0; i < pPlan->mUnknown2372; i++) {
        pPlan->mUnknown1444[i].mUnknown28 = fn_801CFB94(fn_801CFFD0(pPlan->mUnknown1444[i].mUnknown16, angle) / 2);
        fn_801227DC(p, pPlan, &pPlan->mUnknown1444[i]);
    }
}

void fn_8012311C(Object_80039F5C *p, Plan_80121264 *pPlan, int angle)
{
    fn_80121264(p, pPlan);
    fn_80122670(p, pPlan, angle & 0xFFFFFF);
    fn_80123024(p, pPlan, angle & 0xFFFFFF);
}

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

void fn_80123E2C(void)
{
}

float fn_801242E0(float *pValues, unsigned int index)
{
    return pValues[index] + pValues[(index + 7) % 8] + pValues[(index + 9) % 8];
}

float fn_80125004(Object_80039F5C *p, int kind, int index);

float fn_80124FE0(Object_80039F5C *p, int kind)
{
    return fn_80125004(p, kind, 0);
}

float fn_80125004(Object_80039F5C *p, int kind, int index)
{
    float values[8];

    fn_8012430C(values, kind, p);
    fn_801F51DC(0, values, 8, sizeof(float), fn_80123254, 0, 0, -2);
    return values[index];
}

int fn_801251FC(Object_80039F5C *p)
{
    return p->mUnknown1032 != 4;
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
        fn_801C1F94(&message, 0, sizeof(message));
        message.mId = 96;
        message.mUnknown1[0] = value;
        fn_800F00D4(0, p->mpState, &message, p);
    }
    return result;
}

int fn_80125DF0(Object_80039F5C *p)
{
    fn_801C1F94(&p->mUnknown336, 0, 12);
    return 0;
}

}
