/* Replay camera and replay recorder of the in-game loop (Xbox data string
   "REPLAY.C" heads this file's .data; neutral file name). The data and the
   first four functions are linked from source; the remaining functions
   0x8002B960-0x80030D50 and the four discarded functions are draft
   reconstructions compiled only for comparison. */
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "engine/vptmanager.h"
#include "game/Camera_8013F738.h"
#include "game/GameVpt.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/RecordList_8002E7C0.h"
#include "game/cu_80136B1C.h"
#include "game/cu_8002B8F8.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80191804.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801C68FC.h"
#include "game/fn_80227638.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))

/* Camera description set up by fn_8002FDB4 (12 bytes cleared, +4 filled by
   fn_8009BD2C, +8 set to 1) and consumed by fn_8002C300, fn_8002F61C and
   fn_8002EA78 (+0 selects the camera mode, +8 attaches it). */
struct Type_8002FDB4 {
    int mUnknown00;
    int mUnknown04;
    unsigned char mUnknown08;
};

/* One {op, arg} word of a condition list read by fn_8002D4A0; op -1 ends
   the list. Ops 0 and 27 read only the low byte of the argument. */
struct Cond_8002D4A0 {
    short mOp;
    union {
        short mArg;
        struct {
            char mArgPad;
            unsigned char mArgLow;
        };
    };
};

/* One {op, arg} word of a replay camera script (fn_80030D14); op -1 ends it. */
struct Command_8002DC00 {
    short mOp;
    short mArg;
};

/* {id, script} row of the table fn_80030D14 searches; id -1 ends it. */
struct Script_802CC938 {
    int mId;
    Command_8002DC00 *mpCommands;
};

/* 12-byte row of the table fn_80030D08 returns: a script id and the
   condition list fn_8002E950 tests for it; id -1 ends the table. */
struct Entry_80030D08 {
    int mId;
    Cond_8002D4A0 *mpConds;
    int mUnknown08;
};

/* Argument of fn_801C3610 when it creates a camera (as in
   src/game/cu_8013F460.cpp). */
struct Desc_8013C340 {
    int mUnknown00;
    int mUnknown04;
    int mUnknown08;
    int mUnknown0C;
};

/* 0x14-byte focus block of the replay camera at 0x8030660C (cleared as a
   whole by fn_8002F61C); mPos is the focus point. */
struct Type_8030660C {
    int mUnknown00;
    Vector_80039F5C mPos;
    int mUnknown10;
};

/* 16-byte bit stream opened on a frame buffer by fn_80190ED4 (buffer, mode,
   bit position, 0x3F) and closed by fn_80190EF0. */
struct Type_80190ED4 {
    char *mpBuffer;
    int mMode;
    int mUnknown08;
    int mUnknown0C;
};

/* 12-byte replay channel record of the lbl_803EC648 pool, registered by
   fn_80030ACC: write and read callbacks and the record size in bits. */
struct Type_80030ACC {
    void (*mpWrite)(Type_80190ED4 *pStream);
    void (*mpRead)(Type_80190ED4 *pStream0, Type_80190ED4 *pStream1, Type_80190ED4 *pStream2,
                   Type_80190ED4 *pStream3, float t);
    unsigned int mSize;
};

extern "C" {
extern char lbl_802EC330[];
extern void *lbl_803EB688;

double fabs(double);

void fn_80026DD4(void);
void fn_800271D4(void **pHandlers);
void fn_80027230(void **pHandlers);
void fn_80027358(int slot);
void fn_8002885C(void);
void fn_800288B0(void);
unsigned char fn_8002892C(void);
void fn_80031018(const float *pValue, int a);
void fn_80031040(unsigned char value);
void fn_800310C0(void *p, int a, Object_80039F5C *pObject, Vector_80039F5C *pPos, int *pFacing);
int fn_800311E4(Type_803EA368 *p, int id);
int fn_8003122C(Type_803EA368 *p, int id, float *pOut);
Object_80039F5C *fn_80031294(Type_803EA368 *p, int id);
void fn_800312DC(Type_803EA368 *p);
int fn_800312FC(Type_803EA368 *p, int id);
int fn_80031328(Type_803EA368 *p, int id);
void fn_8003A5A8(void);
void fn_8003A5E8(void);
void fn_8003AC10(void);
Block_80170E64 *fn_8003DF7C(Vector_80039F5C *pPos, float *pDist);
void fn_8003E038(Block_80170E64 *pBlock, int *pOut);
Block_80170E64 *fn_80040F28(Vector_80039F5C *pPos, float *pDist);
void fn_80042F4C(int a);
void fn_800443B8(void);
void fn_80044460(void);
void fn_8004659C(void);
void fn_80047050(void);
void fn_800655B8(void);
void fn_800655D0(void);
int fn_8006560C(void);
void fn_800656E4(int value);
void fn_80067D4C(int type, Vector_80039F5C *pPos);
int fn_8006C854(int index, Vector_80039F5C *pPos);
void fn_8006E918(void);
void fn_800711DC(int a);
void fn_800711E0(void);
void fn_80071344(void);
void fn_80071348(void);
void fn_80071794(int a);
void fn_80072AEC(int a);
void fn_80072F04(void);
void fn_8009BB50(int a, int b);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_8009D818(int state);
int fn_8009D86C(void);
void fn_8009D964(int index, int value);
int fn_8009D990(int index);
void fn_800A3120(float a);
float fn_800A32B4(void);
int fn_800A3444(void);
void fn_800A8644(void);
void fn_800A866C(void);
void fn_800B50E8(int a);
int fn_800B81A4(void);
void fn_801383E4(int on);
void fn_8013C2B4(void *pCamera, int a, int b, int c);
void fn_8013C340(Desc_8013C340 *pDesc);
void fn_8013C384(void *pCamera, int a, int b, int c);
void fn_8013C540(Camera_8013F738 *pCamera, int angle);
void fn_8013C57C(Camera_8013F738 *pCamera, int angle);
void fn_8013C624(void *pCamera, int a, int b, int c);
void fn_8013C6F0(Camera_8013F738 *pCamera);
void fn_8013C868(void);
void fn_8013C90C(void);
void fn_8013C954(void);
void fn_8013E474(void);
void fn_8013FB44(void);
void fn_80144EDC(float a);
void fn_80145E64(float a);
void fn_80145FE4(void);
void fn_8014602C(void);
void fn_8014604C(void);
void fn_801478A8(void);
unsigned char fn_801478F0(unsigned char a);
void fn_8015A0D0(int value);
void fn_80162780(int a, int b);
void fn_80177E6C(int a, int b);
int fn_80177F70(void);
int fn_80177F7C(void);
void fn_80177F88(int a);
Point_8017886C fn_80177FE0(void);
void fn_801780A8(Point_8017886C pos);
float fn_80178298(void);
void fn_801782F4(float line);
int fn_80178308(void);
int fn_80178320(void);
int fn_80178348(void);
int fn_801784C4(void);
int fn_801787DC(int a);
void fn_801787FC(int which, short value);
float fn_80178A08(void);
float fn_80178A44(void);
unsigned int fn_80178D18(int team);
void fn_8017CFB4(int a);
void fn_8017DBCC(void);
void fn_8017DC44(void);
void fn_8017DC88(void);
void fn_8017DCCC(void);
void fn_8017DD1C(void);
unsigned char fn_8017DD60(void);
void fn_8017F814(void);
unsigned char fn_8017F2DC(unsigned char value);
unsigned char fn_8017F2EC(unsigned char value);
void fn_8018A4BC(int a, unsigned int id, float value);
void fn_80190ED4(Type_80190ED4 *pStream, char *pBuffer, int mode);
int fn_80190EF0(Type_80190ED4 *pStream);
unsigned long long fn_80190F18(void *pStream, int bits);
void fn_80191068(void *pStream, unsigned long long value, int bits);
void fn_80195EFC(int a, int b, int c, int d);
int fn_8019623C(int id);
void fn_80199C94(char *pSrc, int index, int size);
char *fn_80199CC4(int index, int size);
char *fn_80199CF0(int index, int size);
void fn_80199D58(int count, int size);
void fn_80199DB0(void);
void *fn_801C3610(int a, Desc_8013C340 *pDesc);
void fn_801C3640(void *pCamera);
void fn_801C39D0(Camera_8013F738 *pCamera, float value);
int fn_801C6280(int a, int b, int c);
int fn_801C6458(int a, int b);
void *fn_801C6A20(void *pool);
void *fn_801C6B4C(void *pool, void *item);
void *fn_801C6C84(void *pool, void *item);
void *fn_801D2B7C(int size, int a, int b);
int fn_801D2BD0(void *p);
void fn_801EC3B8(int a, int b);
int fn_801F7ABC(void);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
void fn_802196B4(void *p, int a, int b, int c, float *pD, unsigned char e);
void fn_80227384(Point_8017886C *pOut, Point_8017886C *pIn, int angle);
float fn_8022781C(Vector_80039F5C *pA, Vector_80039F5C *pB);
float fn_8022785C(Vector_80039F5C *pPos, Vector_80039F5C *pOther);
void fn_80227930(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB, float t);
int fn_8023790C(void);

/* Animation state and animation of each player ([team][index]), filled by
   fn_800D7708. */
extern unsigned short lbl_803192BC[2][7];
extern unsigned short lbl_803192D8[2][7];

Block_80170E64 *GetHighlightedObject(void);

void fn_8002B8F8(void);
void fn_8002B8FC(void);
unsigned char fn_8002B924(void);
void fn_8002B92C(void);
void fn_8002B960(Type_8002B960 *p);
void fn_8002BAF4(Type_8002B960 *p);
int fn_8002BC80(Type_803EA368 *p);
int fn_8002BCD4(Type_803EA368 *p);
int fn_8002BD44(Type_803EA368 *p);
int fn_8002BDBC(Type_803EA368 *p);
void fn_8002BDC4(Type_803EA368 *p);
int fn_8002BE28(Type_803EA368 *p, int event, int a);
void fn_8002BE68(Type_803EA368 *p);
void fn_8002BEF0(Type_803EA368 *p);
void fn_8002C13C(Type_803EA368 *p);
int fn_8002C300(Type_803EA368 *p, Type_8002FDB4 *pDesc);
int fn_8002C4B0(Type_803EA368 *p);
void fn_8002C630(Type_803EA368 *p);
void fn_8002C664(Type_803EA368 *p, int delta);
void fn_8002C6E0(Type_803EA368 *p, int delta);
void fn_8002C75C(Type_803EA368 *p);
void fn_8002C800(Type_803EA368 *p);
void fn_8002C848(int type);
void fn_8002C9A4(Type_803EA368 *p);
int fn_8002D1B8(Type_803EA368 *p, int value);
void fn_8002D128(Type_803EA368 *p, int value);
int fn_8002D158(Type_803EA368 *p);
void fn_8002D160(Type_803EA368 *p, int value);
int fn_8002D0D0(Type_803EA368 *p);
void fn_8002D250(Type_803EA368 *p);
void fn_8002D2D0(void);
void fn_8002D2D4(void);
int fn_8002D2D8(void);
void fn_8002D2E0(Type_803EA368 *p, int a, unsigned int id, float value);
void fn_8002D2E4(Type_8030660C *pFocus, Block_80170E64 **ppTarget);
void fn_8002D2E8(Type_803EA368 *p);
void fn_8002D2EC(void);
void fn_8002D2F0(Type_803EA368 *p, int id, int value, int index);
void fn_8002D338(Type_803EA368 *p, Timer_8002E7C0 *pTimer);
Record_8002E7C0 *fn_8002D3BC(RecordList_8002E7C0 *pList);
float fn_8002D414(int a, int b);
int fn_8002D4A0(Cond_8002D4A0 *pCond);
void fn_8002DC00(Type_803EA368 *p, RecordList_8002E7C0 *pList);
void fn_8002E75C(Type_803EA368 *p, Timer_8002E7C0 *pTimer);
void fn_8002E890(RecordList_8002E7C0 *pList);
void fn_8002E8B8(Type_803EA368 *p, RecordList_8002E7C0 *pList);
int fn_8002E950(int mode);
void fn_8002EA18(void);
void fn_8002EA38(void);
void fn_8002EA58(void);
Camera_8013F738 *fn_8002EA78(Type_8002FDB4 *pDesc);
void fn_8002EBBC(Object_80039F5C *p);
void fn_8002EC28(void);
void fn_8002ED48(Point_8017886C *pOut, unsigned int input, float amount);
Block_80170E64 *fn_8002EDE8(Camera_8013F738 *pCamera, float *pDist, unsigned char *pFound);
void fn_8002EED0(void);
void fn_8002F1E0(Camera_8013F738 *pCamera);
void fn_8002F26C(Camera_8013F738 *pCamera, unsigned int input, float amount);
Camera_8013F738 *fn_8002F61C(Type_8002FDB4 *pDesc);
void fn_8002F71C(Camera_8013F738 *pCamera);
void fn_8002F74C(Camera_8013F738 *pCamera);
void fn_8002F9D8(Camera_8013F738 *pCamera);
void fn_8002FA04(Camera_8013F738 *pCamera, int detach);
void fn_8002FA8C(Camera_8013F738 *pCamera, int unused, unsigned int input, float amount);
void fn_8002FC28(Camera_8013F738 *pCamera, int player, unsigned int input, float amount);
void fn_8002FDB4(Type_8002FDB4 *pDesc);
int fn_8002FDFC(void);
void fn_8002FE34(int index);
void fn_800300D0(void);
void fn_800307AC(void);
void fn_800307C0(Type_803EA368 *p);
void fn_80030828(Type_803EA368 *p);
void fn_800308A4(Type_803EA368 *p);
void fn_800308E8(Type_803EA368 *p);
void fn_80030940(Type_803EA368 *p);
void fn_80030C40(void);
Object_80039F5C *fn_80030C70(Object_80039F5C **ppA, Object_80039F5C **ppB);
void fn_80030CB0(int value);
unsigned char fn_80030CC0(Type_803EA368 *p);
void fn_80030CFC(void);
float fn_80030D00(void);
Entry_80030D08 *fn_80030D08(void);
Command_8002DC00 *fn_80030D14(int id);
}

/* .sdata */
static int lbl_803EA358 = 0;
static unsigned char lbl_803EA35C = 0;
static unsigned char lbl_803EA35D = 0;
static unsigned int lbl_803EA360 = 0;
static unsigned char lbl_803EA364 = 0;
static unsigned char lbl_803EA365 = 0;
static unsigned char lbl_803EA366 = 0;
Type_803EA368 *lbl_803EA368 = 0;
static unsigned char lbl_803EA36C = 0;
static int lbl_803EA370 = -1;
static unsigned char lbl_803EA374 = 0;
static unsigned char lbl_803EA375 = 1;
static unsigned char lbl_803EA376 = 0;
static int lbl_803EA378 = 0;
static int lbl_803EA37C = 0;
static float lbl_803EA380 = 1.2f;
static unsigned char lbl_803EA384 = 0;
static int lbl_803EA388 = 0;

/* .sbss */
static int lbl_803EC614;
static int lbl_803EC618;
static int lbl_803EC61C;
static Block_80170E64 *lbl_803EC620;
static int lbl_803EC624;
static unsigned char lbl_803EC628;
static float lbl_803EC62C;
static float lbl_803EC630;
static unsigned char lbl_803EC634;
static float lbl_803EC638;
static float lbl_803EC63C;
static float lbl_803EC640;
static float lbl_803EC644;
static void *lbl_803EC648;
static unsigned int lbl_803EC64C;
static unsigned int lbl_803EC650;
static unsigned char lbl_803EC654;
static int lbl_803EC658;
static int lbl_803EC65C;
static int lbl_803EC660;
static Object_80039F5C *lbl_803EC664;
static Object_80039F5C *lbl_803EC668;
static float lbl_803EC66C;

/* .bss */
static Type_8030660C lbl_8030660C;

/* .data */
static char lbl_802CC830[] = "REPLAY.C";

/* The replay camera's callbacks; 0x802DBDA0 points to this table. */
static void (*lbl_802CC83C[])(void) = { fn_8002EA18, fn_8002EA38, fn_8002EA58 };

static Command_8002DC00 lbl_802CC848[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 14 }, { 0x1A, 0 }, { 0x1B, -6 }, { 0x1C, 4 }, { -1, 0 },
};
static Command_8002DC00 lbl_802CC868[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 14 }, { 0x1A, 0 }, { 0x1B, 6 }, { 0x1C, 4 }, { -1, 0 },
};
static Command_8002DC00 lbl_802CC888[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 14 }, { 0x1A, 1 }, { 0x1B, 6 }, { 0x1C, 3 }, { -1, 0 },
};
static Command_8002DC00 lbl_802CC8A8[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 7 }, { 2, 7 }, { 0x1A, -1 }, { 0x1B, 5 }, { 0x1C, 4 }, { -1, 0 },
};
static Command_8002DC00 lbl_802CC8CC[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 7 }, { 2, 4 }, { 0x1A, 0 }, { 0x1B, -5 }, { 0x1C, 4 }, { -1, 0 },
};
static Command_8002DC00 lbl_802CC8F0[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 7 }, { 2, 3 }, { 0x1A, -1 }, { 0x1B, -6 }, { 0x1C, 4 }, { -1, 0 },
};
static Command_8002DC00 lbl_802CC914[] = {
    { 1, 0 }, { 0x26, 0x2D }, { 0x28, 10000 }, { 5, 7 }, { 2, 0x35 }, { 0x1A, 0 }, { 0x1B, 6 }, { 0x1C, 4 }, { -1, 0 },
};

static Script_802CC938 lbl_802CC938[] = {
    { 0, lbl_802CC848 }, { 1, lbl_802CC868 }, { 3, lbl_802CC888 }, { 2, lbl_802CC8A8 },
    { 4, lbl_802CC8F0 }, { 5, lbl_802CC8CC }, { 6, lbl_802CC914 }, { -1, 0 },
};

static Cond_8002D4A0 lbl_803EA38C[] = { { 0x19, 100 }, { -1, 0 } };
static Cond_8002D4A0 lbl_802CC978[] = { { 3, 7 }, { 0x19, 100 }, { -1, 0 } };
static Cond_8002D4A0 lbl_802CC984[] = { { 3, 0xB }, { 0x19, 100 }, { -1, 0 } };
static Cond_8002D4A0 lbl_802CC990[] = { { 3, 4 }, { 0x19, 100 }, { -1, 0 } };
static Cond_8002D4A0 lbl_802CC99C[] = { { 3, 3 }, { 0x19, 100 }, { -1, 0 } };
static Cond_8002D4A0 lbl_802CC9A8[] = { { 3, 0x35 }, { 0x19, 100 }, { -1, 0 } };

static Entry_80030D08 lbl_802CC9B4[] = {
    { 0, lbl_803EA38C, -1 }, { 1, lbl_803EA38C, -1 }, { 2, lbl_802CC978, -1 }, { 3, lbl_802CC984, -1 },
    { 4, lbl_802CC99C, -1 }, { 5, lbl_802CC990, -1 }, { 6, lbl_802CC9A8, -1 }, { -1, 0, 0 },
};

/* Unreferenced on GameCube. The Xbox build has the same eight floats right
   after its copy of lbl_802CC9B4 (0x5012E0), stored into every player
   (+0xEEC) by a function next to the fn_80030D14 counterpart that the
   GameCube link discarded. */
static float lbl_802CCA14[8] = { -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 3.0f, 1.0f, 0.0f };

extern "C" void fn_8002B8F8(void) {}

extern "C" void fn_8002B8FC(void)
{
    fn_8017F814();
    lbl_803EA36C = 0;
}

extern "C" unsigned char fn_8002B924(void) { return lbl_803EA36C; }

extern "C" void fn_8002B92C(void)
{
    if (fn_8002B924()) {
        fn_8002B8FC();
    } else {
        fn_8002B8F8();
    }
}

#if defined(DECOMP_COMPARE)


extern "C" void fn_8002B960(Type_8002B960 *p)
{
    unsigned char team;
    unsigned int i;
    unsigned int count;
    Object_80039F5C *pObject;

    for (team = 0; team <= 1; team++) {
        count = fn_80178D18(team);
        for (i = 0; i < count; i++) {
            pObject = fn_80039F5C(team, i);
            p->mUnknown000[team][i] = *(Block_80039F5C_B54 *)((char *)pObject + 0xB54);
            p->mUnknown578[team][i] = *(Block_80039F5C_BB8 *)pObject->mRatings;
        }
    }
    p->mUnknown690 = fn_8009D86C();
    p->mUnknown694 = fn_80177F70();
    p->mUnknown6A4[0] = fn_8009D990(0);
    p->mUnknown6A4[1] = fn_8009D990(1);
    p->mUnknown6A4[2] = fn_8009D990(2);
    p->mUnknown6B0[0] = fn_801787DC(0);
    p->mUnknown6B0[1] = fn_801787DC(1);
    p->mUnknown6B4 = fn_801374D4();
    p->mUnknown698 = fn_80177FE0();
    p->mUnknown6A0 = fn_80178298();
    p->mUnknown6B6 = 0;
}

extern "C" void fn_8002BAF4(Type_8002B960 *p)
{
    unsigned char team;
    unsigned int i;
    unsigned int count;
    Object_80039F5C *pObject;

    for (team = 0; team <= 1; team++) {
        count = fn_80178D18(team);
        for (i = 0; i < count; i++) {
            pObject = fn_80039F5C(team, i);
            fn_8006560C();
            *(Block_80039F5C_B54 *)((char *)pObject + 0xB54) = p->mUnknown000[team][i];
            *(Block_80039F5C_BB8 *)pObject->mRatings = p->mUnknown578[team][i];
        }
    }
    fn_8009D818(p->mUnknown690);
    fn_80177F88(p->mUnknown694);
    fn_8009D964(0, p->mUnknown6A4[0]);
    fn_8009D964(1, p->mUnknown6A4[1]);
    fn_8009D964(2, p->mUnknown6A4[2]);
    fn_801787FC(0, p->mUnknown6B0[0]);
    fn_801787FC(1, p->mUnknown6B0[1]);
    fn_8013745C(p->mUnknown6B4);
    fn_801780A8(p->mUnknown698);
    fn_801782F4(p->mUnknown6A0);
}

extern "C" int fn_8002BC80(Type_803EA368 *p)
{
    if (p->mUnknownD90 == 2) {
        fn_800312DC(p);
        p->mUnknownD90 = 0;
        memset(p->mUnknown148C, 0, sizeof(p->mUnknown148C));
    }
    return 0;
}

extern "C" int fn_8002BCD4(Type_803EA368 *p)
{
    if (p->mUnknownD90 == 0) {
        fn_8002B960(&p->mUnknown000);
        p->mUnknownD8C = -1;
        p->mUnknownD74 = p->mUnknownD70 = fn_8023790C();
        p->mUnknownD90 = 1;
        p->mUnknown14B4 = fn_801784C4();
        fn_80030CB0(fn_801374D4());
    }
    fn_8002C9A4(p);
    return 0;
}

extern "C" int fn_8002BD44(Type_803EA368 *p)
{
    if (p->mUnknownD90 == 1) {
        fn_800310C0(p, 0x34, 0, 0, 0);
        p->mUnknownD80 = p->mUnknownD7C = fn_8023790C();
        fn_80030828(p);
        p->mUnknownD90 = 2;
        p->mUnknownD94 &= ~0x10;
    }
    return 0;
}

extern "C" int fn_8002BDBC(Type_803EA368 *p)
{
    return 0;
}

extern "C" void fn_8002BDC4(Type_803EA368 *p)
{
    if (p->mUnknownD94 & 0x10) {
        fn_8002BDBC(p);
    } else if (p->mUnknownD90 == 1) {
        fn_800307C0(p);
    }
    if (p->mUnknownD94 & 0x20) {
        p->mUnknownD94 &= ~0x10;
    }
}

extern "C" int fn_8002BE28(Type_803EA368 *p, int event, int a)
{
    int result = 3;

    switch (event) {
    case 6:
        result = 1;
        break;
    case 7:
        result = 4;
        break;
    case 0x16:
        result = 5;
        break;
    }
    return result;
}

extern "C" void fn_8002BE68(Type_803EA368 *p)
{
    Type_8002FDB4 args;

    fn_8002FDB4(&args);
    if (p->mUnknownD94 & 0x80) {
        args.mUnknown00 = fn_8002BE28(p, 7, 0);
        fn_8002C300(p, &args);
    } else if (p->mUnknownD94 & 0x400000) {
        args.mUnknown00 = fn_8002BE28(p, 0x16, 0);
        fn_8002C300(p, &args);
    }
}

extern "C" void fn_8002BEF0(Type_803EA368 *p)
{
    unsigned int i;

    p->mUnknownD80 = p->mUnknownD80 > p->mUnknownD7C ? p->mUnknownD7C : p->mUnknownD80;
    if (fn_800B81A4() != 0xFF && lbl_803EA360 > 0x1D) {
        p->mUnknownD94 |= 0x200;
    }
    fn_801383E4(1);
    for (i = 0; i <= 4; i++) {
        if (p->mUnknown148C[i].mUnknown0 == p->mUnknownD74 && p->mUnknownD78 == 0) {
            fn_8002C848(p->mUnknown148C[i].mUnknown4);
        }
    }
    if (p->mUnknownD74 >= p->mUnknownD80 && p->mUnknownD88 != 0) {
        fn_80030940(p);
        p->mUnknownD88 = 0;
        fn_8013E474();
    }
    lbl_803EA358 += p->mUnknownD88;
    if (lbl_803EA358 > 60) {
        fn_8004659C();
        fn_801478A8();
        lbl_803EA358 = 0;
    }
    if (p->mUnknownD88 < 60) {
        fn_80144EDC(p->mUnknownD88 / 60.0f);
        fn_80145E64(1.0f);
        fn_800A3120(p->mUnknownD88 / 60.0f);
    } else {
        fn_80144EDC(1.0f);
        fn_80145E64(1.0f);
        fn_800A3120(p->mUnknownD88 / 60.0f);
    }
    fn_80047050();
    if (p->mUnknownD94 & 0x200) {
        if (lbl_803EA360 > 0x1D) {
            fn_8002C4B0(p);
            fn_80067D4C(0x7F, 0);
            fn_800656E4(4);
        }
    } else if (p->mUnknownD88 > 0) {
        fn_8002C6E0(p, p->mUnknownD88);
    } else if (p->mUnknownD88 < 0) {
        fn_8002C664(p, p->mUnknownD88);
    }
    if (p->mpUnknownDA0) {
        fn_8002F9D8(p->mpUnknownDA0);
    }
}

extern "C" void fn_8002C13C(Type_803EA368 *p)
{
    unsigned short a;
    unsigned short b;

    lbl_803EA366 = 0;
    if (p->mUnknownD74 >= p->mUnknownD7C && p->mUnknownD8C == -1) {
        p->mUnknownD94 |= 0x200;
    }
    if (lbl_803EA364 == 0) {
        fn_80219650(lbl_803EB688, &a, &b);
        if (fn_800B81A4() != 0xFF) {
            p->mUnknownD94 |= 0x200;
        }
        fn_80047050();
        if (p->mUnknownD94 & 0x1000200) {
            if (lbl_803EA360 > 0x1D) {
                fn_8002C4B0(p);
            }
        } else if (!(p->mUnknownD94 & 0x100) && (p->mUnknownD94 & 0xF000)) {
            if (p->mUnknownD88 > 0) {
                fn_8002C6E0(p, p->mUnknownD88);
                lbl_803EA358 += p->mUnknownD88;
            } else if (p->mUnknownD88 < 0) {
                fn_8002C664(p, p->mUnknownD88);
                lbl_803EA358 -= p->mUnknownD88;
            }
            if (lbl_803EA358 > 60) {
                fn_8004659C();
                fn_801478A8();
                lbl_803EA358 = 0;
            }
            fn_80144EDC(p->mUnknownD88 / 60.0f);
            fn_8014602C();
            fn_800A3120(p->mUnknownD88 / 60.0f);
            lbl_803EA366 = 1;
        }
        if (p->mUnknownD94 & 0x2000000) {
            fn_8002D2E8(p);
        }
        if (p->mpUnknownDA0) {
            fn_8002F74C(p->mpUnknownDA0);
        }
    }
}

extern "C" int fn_8002C300(Type_803EA368 *p, Type_8002FDB4 *pDesc)
{
    int result = -1;

    lbl_803EA360 = 0;
    if (p->mUnknownD90 == 2 || (p->mUnknownD94 & 0x400000)) {
        if (p->mUnknownD94 & 0x400000) {
            p->mUnknownD94 |= 0x800000;
        } else {
            fn_8006C854(0x77, 0);
            fn_8002885C();
            fn_800655B8();
            fn_8002B960(&p->mUnknown6B8);
            fn_8002BAF4(&p->mUnknown000);
            if ((p->mUnknownD94 & 0x2000000) && fn_801784C4()) {
                fn_80177E6C(0, 0);
            }
            fn_800B50E8(0);
            fn_800B50E8(1);
            fn_8003A5A8();
            fn_800443B8();
            p->mUnknownD78 = 0;
            p->mUnknownD74 = p->mUnknownD70;
            fn_800308A4(p);
            if (!(p->mUnknownD94 & 0x10000)) {
                fn_80030940(p);
                fn_80072F04();
                fn_80072AEC(0xC);
            }
            fn_8017DC44();
            p->mUnknownD90 = 4;
        }
        if (p->mUnknownD94 & 0x2000000) {
            fn_8002D2D0();
        }
        fn_8002C75C(p);
        p->mpUnknownDA0 = fn_8002F61C(pDesc);
        fn_8002F74C(p->mpUnknownDA0);
        if (p->mUnknown14B4 && !(p->mUnknownD94 & 0x400000)) {
            fn_8013C540(p->mpUnknownDA0, 0x800000);
            fn_8013C2B4(p->mpUnknownDA0, 0, 0, 0);
            fn_8013C6F0(p->mpUnknownDA0);
        }
        lbl_803EA35C = fn_8017F2EC(0);
        lbl_803EA35D = fn_8017F2DC(2);
        fn_800A8644();
        fn_80145FE4();
        result = 0;
    }
    lbl_803EA365 = fn_801478F0(0);
    fn_8002B8F8();
    return result;
}

extern "C" int fn_8002C4B0(Type_803EA368 *p)
{
    int result = -1;
    Camera_8013F738 *pCamera;

    fn_801478F0(lbl_803EA365);
    if (p->mUnknownD90 == 4 || (p->mUnknownD94 & 0x1000000)) {
        if (p->mUnknownD94 & 0x1000000) {
            p->mUnknownD94 &= ~0x800000;
        } else {
            fn_8002BAF4(&p->mUnknown6B8);
            fn_8017DC88();
            if ((p->mUnknownD94 & 0x2000000) && fn_801784C4()) {
                fn_8013FB44();
            }
            if (!(p->mUnknownD94 & 0x10000)) {
                fn_8006C854(0x78, 0);
                fn_80072AEC(0xD);
                fn_800656E4(4);
            }
            if (fn_8006560C() == 0) {
                fn_800B50E8(0);
                fn_800B50E8(1);
            }
            fn_8003A5E8();
            fn_8003AC10();
            fn_80044460();
            p->mUnknownD94 &= ~0x1000;
            p->mUnknownD94 &= ~0x10000;
            fn_800308E8(p);
            p->mUnknownD8C = -1;
            p->mUnknownD90 = 2;
            fn_800288B0();
            fn_800655D0();
        }
        if (p->mUnknownD94 & 0x2000000) {
            p->mUnknownD94 &= ~0x2000000;
            fn_8002D2D4();
        }
        fn_8002C800(p);
        pCamera = p->mpUnknownDA0;
        fn_8002FA04(pCamera, fn_8002B550(GameVpt::fn_800293A8()) == p->mpUnknownDA0);
        p->mpUnknownDA0 = 0;
        fn_8017F2EC(lbl_803EA35C);
        fn_8017F2DC(lbl_803EA35D);
        fn_800A866C();
        fn_8014604C();
        fn_800711E0();
        result = 0;
    }
    fn_8002B8FC();
    return result;
}

extern "C" void fn_8002C630(Type_803EA368 *p)
{
    fn_8023790C();
    fn_80030940(p);
}

extern "C" void fn_8002C664(Type_803EA368 *p, int delta)
{
    p->mUnknownD78 += delta;
    while (p->mUnknownD78 <= -60) {
        p->mUnknownD78 += 60;
        if (p->mUnknownD74 > p->mUnknownD70) {
            p->mUnknownD74--;
        }
    }
    if (p->mUnknownD74 == p->mUnknownD70) {
        p->mUnknownD78 = 0;
    }
    fn_8002C630(p);
}

extern "C" void fn_8002C6E0(Type_803EA368 *p, int delta)
{
    p->mUnknownD78 += delta;
    while (p->mUnknownD78 >= 60) {
        p->mUnknownD78 -= 60;
        if (p->mUnknownD74 < p->mUnknownD7C) {
            p->mUnknownD74++;
        }
    }
    if (p->mUnknownD74 == p->mUnknownD7C) {
        p->mUnknownD78 = 0;
    }
    fn_8002C630(p);
}

extern "C" void fn_8002C75C(Type_803EA368 *p)
{
    fn_800271D4(p->mUnknownDA8);
    if (!fn_8002892C() && p->mUnknownD8C != -1) {
        fn_801C6280(9, 0, fn_801C6458(p->mUnknownD8C, 0));
        fn_801C6280(9, 2, (int)fn_80026DD4);
        fn_801C6280(9, 4, 1);
        fn_801C6280(-1, 3, (int)lbl_802EC330);
        fn_801EC3B8(9, p->mUnknownD8C);
    }
}

extern "C" void fn_8002C800(Type_803EA368 *p)
{
    fn_80027230(p->mUnknownDA8);
    fn_80027358(-1);
    if (!fn_8002892C()) {
        fn_801C6280(9, 4, 0);
    }
}

extern "C" void fn_8002C848(int type)
{
    switch (type) {
    case 0:
        break;
    case 1:
        fn_80071344();
        break;
    case 2:
        fn_80071348();
        break;
    case 3:
        break;
    case 4:
        fn_80071794(8);
        break;
    case 5:
        fn_80071794(9);
        break;
    }
}

extern "C" Type_803EA368 *fn_8002C8C0(void)
{
    Type_803EA368 *p;

    p = (Type_803EA368 *)fn_801D2B7C(sizeof(Type_803EA368), 0, 0);
    memset(p, 0, sizeof(Type_803EA368));
    p->mUnknownD7C = 0;
    p->mUnknownD70 = 0;
    p->mUnknownD78 = 0;
    p->mUnknownD74 = 0;
    p->mUnknownD94 = 0;
    p->mpUnknownDA0 = 0;
    p->mUnknownD90 = 2;
    fn_8002BC80(p);
    p->mUnknown14B5 = 0;
    p->mUnknownD98 = -1;
    lbl_803EC614 = 0;
    memset(p->mUnknown148C, 0, sizeof(p->mUnknown148C));
    fn_801C6280(9, 4, 0);
    return p;
}

extern "C" void fn_8002C964(Type_803EA368 *p)
{
    fn_8002BD44(p);
    fn_8002C4B0(p);
    fn_80030C40();
    fn_801D2BD0(p);
}

extern "C" void fn_8002C9A4(Type_803EA368 *p)
{
}


extern "C" int fn_8002C9A8(Type_803EA368 *p, int msg, int value)
{
    int result = -1;

    if (p == 0) {
        return -2;
    }
    if (p->mUnknownD90 != 4) {
        switch (msg) {
        case 3:
            result = 0;
            fn_8002BD44(p);
            break;
        case 1:
            p->mUnknownD94 |= 2;
            result = 0;
            fn_8002BC80(p);
            break;
        case 2:
            p->mUnknownD94 |= 4;
            result = 0;
            fn_8002BCD4(p);
            fn_800307AC();
            break;
        default:
            p->mUnknownD94 |= 1 << msg;
            result = 0;
            break;
        }
    }
    return result;
}

extern "C" int fn_8002CA74(Type_803EA368 *p, int msg, int value)
{
    int result = -1;

    switch (msg) {
    case 10:
        p->mUnknownD8C = value;
        break;
    case 11:
        p->mUnknownD94 |= 0x800;
        result = 0;
        break;
    case 7:
        if (p->mUnknownD90 == 2) {
            result = 0;
            p->mUnknownD94 &= ~0x800;
            p->mUnknownD94 &= ~0x100;
            p->mUnknownD94 |= 0x80;
            lbl_803EA358 = 0;
        }
        break;
    case 25:
        p->mUnknownD94 |= 0x2000000;
        result = 0;
        break;
    case 8:
        if (p->mUnknownD90 == 4) {
            if (p->mUnknownD94 & 0x100) {
                p->mUnknownD94 &= ~0x100;
            } else {
                p->mUnknownD94 |= 0x100;
            }
            result = 0;
        }
        break;
    case 9:
        if (p->mUnknownD90 == 4) {
            p->mUnknownD94 = (p->mUnknownD94 | 1 << msg) & ~0x100;
            result = 0;
            if (p->mUnknown14B5) {
                p->mUnknown14B5 = 0;
            }
        }
        break;
    case 22:
    case 24:
        p->mUnknownD94 |= 1 << msg;
        result = 0;
        break;
    }
    return result;
}

extern "C" void fn_8002CBB0(Type_803EA368 *p, int a, unsigned int id, float value)
{
    if (a == 9) {
        fn_80191804(9, id, value);
        if (p->mUnknownD94 & 0x10000) {
            if (p->mUnknownD90 == 4) {
                switch (id) {
                case 0: /* 0 and 1: the cmplwi 1 test at 0x8002CC10 */
                case 1:
                    break;
                case 6:
                    if (value == 1.0f) {
                        if (p->mUnknownD88 == 15) {
                            p->mUnknownD88 = 45;
                        } else {
                            p->mUnknownD88 = 15;
                        }
                    }
                    break;
                case 8:
                    if (value == 1.0f) {
                        fn_8002D250(p);
                    }
                    break;
                case 9:
                    if (value == 1.0f && fn_8002E950(1)) {
                        RecordList_8002E7C0 *pList = &p->mpUnknownDA0->mUnknown128;

                        fn_8002E890(pList);
                        fn_8002DC00(p, pList);
                        fn_8002E8B8(p, pList);
                        p->mUnknownD74 = p->mUnknownD70;
                        p->mUnknownD78 = 0;
                        fn_8013C624(p->mpUnknownDA0, 8, 0, 0);
                    }
                    break;
                case 10: /* placeholder values: the compare tree needs two */
                case 11: /* empty labels above 9; values not recovered */
                    break;
                }
            }
            return;
        }
        if (p->mUnknownD94 & 0x100) {
            fn_8018A4BC(9, id, value);
            return;
        }
        if (p->mUnknownD94 & 0x800000) {
            fn_8002FC28(p->mpUnknownDA0, 9, id, value);
            fn_8018A4BC(9, id, value);
            return;
        }
        if ((p->mUnknownD94 & 0x2000000) && fn_8002D2D8()) {
            fn_8002D2E0(p, 9, id, value);
            return;
        }
        if (p->mUnknownD94 & 0x200) {
            return;
        }
        {
            unsigned short s0;
            unsigned short s1;

            fn_8002FA8C(p->mpUnknownDA0, a, id, value);
            fn_80219650(lbl_803EB688, &s0, &s1);
            fn_8018A4BC(a, id, value);
        }
        if (id == 0 && lbl_803EA360 > 29) {
            p->mUnknownD94 |= 0x200;
            fn_8017DBCC();
        }
        switch (id) {
        case 0x50:
            if (value == 1.0f) {
                if (fn_8017DD60()) {
                    fn_8017DD1C();
                } else {
                    fn_8017DCCC();
                }
            }
            break;
        case 0x4B:
            if (p->mUnknownD94 & 0x1000) {
                p->mUnknownD94 &= ~0x1000;
                p->mUnknownD88 = 0;
            } else {
                p->mUnknownD94 |= 0x1000;
                p->mUnknownD88 = 60;
            }
            break;
        case 0x3B:
        case 0x4C:
            p->mUnknownD94 = (p->mUnknownD94 & ~0x1000) | 0x2000;
            if (value < 1.0f) {
                p->mUnknownD88 = (int)(-value * 90.0f);
            } else {
                p->mUnknownD88 = (int)(-value * 180.0f);
            }
            break;
        case 0x3C:
        case 0x4E:
            p->mUnknownD94 = (p->mUnknownD94 & ~0x1000) | 0x4000;
            p->mUnknownD88 = (int)(value * (value < 1.0f ? 90.0f : 180.0f));
            break;
        case 0x15:
            if (value == 1.0f) {
                fn_8002B92C();
            }
            break;
        }
    }
}

extern "C" void fn_8002CF34(Type_803EA368 *p)
{
    int state = p->mUnknownD90;

    if (state == 4 || (p->mUnknownD94 & 0x800000)) {
        lbl_803EA360++;
        if (p->mUnknownD94 & 0x10000) {
            fn_8002BEF0(p);
        } else {
            fn_8002C13C(p);
        }
    } else {
        if (state == 1 && fn_800AD9B4() != 3 && fn_80030CC0(p)) {
            fn_8002BD44(p);
        }
        fn_8002BDC4(p);
        fn_8002BE68(p);
    }
    p->mUnknownD94 &= 0x2811950;
}

extern "C" void fn_8002CFF4(Type_803EA368 *p)
{
    Type_8002FDB4 args;

    args.mUnknown00 = 1;
    args.mUnknown04 = 1;
    args.mUnknown08 = 1;
    p->mUnknownD84 = fn_801F7ABC();
    p->mUnknownD94 = (p->mUnknownD94 | 0x10000) & ~0x40;
    fn_80031040(0);
    fn_8002C300(p, &args);
}

extern "C" unsigned char fn_8002D058(void) { return lbl_803EA366; }

extern "C" unsigned char fn_8002D060(Type_803EA368 *p)
{
    unsigned char result = 0;

    if (p != 0) {
        result = ((p->mUnknownD94 & 0x800000) != 0) | ((p->mUnknownD94 & 0x400000) != 0) |
                 ((p->mUnknownD94 & 0x800) != 0) | ((p->mUnknownD94 & 0x80) != 0) |
                 (p->mUnknownD90 == 4);
    }
    return result;
}

extern "C" int fn_8002D0AC(Type_803EA368 *p)
{
    int result = 0;

    if (p != 0) {
        result = p->mUnknownD90 == 1;
    }
    return result;
}

extern "C" int fn_8002D0D0(Type_803EA368 *p)
{
    int result = 0;

    if (p->mUnknownD90 == 2 || p->mUnknownD90 == 4) {
        result = p->mUnknownD7C - p->mUnknownD70;
    }
    return result;
}

extern "C" int fn_8002D0FC(Type_803EA368 *p)
{
    int result = 0;

    if (p->mUnknownD90 == 2 || p->mUnknownD90 == 4) {
        result = p->mUnknownD74 - p->mUnknownD70;
    }
    return result;
}

extern "C" void fn_8002D128(Type_803EA368 *p, int value)
{
    p->mUnknownD88 = value;
    p->mUnknownD88 = CLAMP(p->mUnknownD88, -120, 120);
}

extern "C" int fn_8002D150(Type_803EA368 *p) { return p->mUnknownD88; }

extern "C" int fn_8002D158(Type_803EA368 *p) { return p->mUnknownD70; }

extern "C" void fn_8002D160(Type_803EA368 *p, int value)
{
    p->mUnknownD80 = p->mUnknownD74 + value;
    p->mUnknownD80 = CLAMP(p->mUnknownD80, p->mUnknownD70, p->mUnknownD7C);
}

extern "C" int fn_8002D198(Type_803EA368 *p)
{
    if (lbl_803EA360 > 29) {
        p->mUnknownD94 |= 0x200;
    }
    return 0;
}

extern "C" int fn_8002D1B8(Type_803EA368 *p, int value)
{
    if (value < p->mUnknownD70) {
        value = p->mUnknownD70;
    } else if (value > p->mUnknownD7C - 1) {
        value = p->mUnknownD7C - 1;
    }
    p->mUnknownD74 = value;
    fn_80042F4C(0);
    fn_80030940(p);
    fn_80042F4C(1);
    return 0;
}

extern "C" int fn_8002D228(Type_803EA368 *p)
{
    return ((p->mUnknownD94 >> 8) & 1) | (((p->mUnknownD94 >> 9) & 1) | (p->mUnknownD90 == 2));
}

extern "C" void fn_8002D250(Type_803EA368 *p)
{
    if (p->mUnknownD74 - p->mUnknownD70 > 2) {
        p->mUnknownD80 = p->mUnknownD74;
        p->mUnknownD88 = 60;
    }
}

extern "C" void fn_8002D274(Type_803EA368 *p)
{
    fn_8002C9A8(p, 3, 0);
    fn_8002C9A8(p, 1, 0);
    fn_8002CF34(p);
}

extern "C" unsigned char fn_8002D2C0(void) { return lbl_803EA364; }

extern "C" void fn_8002D2C8(Type_803EA368 *p, unsigned char value) { p->mUnknown14B5 = value; }

/* Debug-window callbacks for the highlighted player (Xbox 0x20830 and
   0x209F0, PS2 0x1B4F30). Nothing on GameCube installs them, so the linker
   drops both; only their strings remain (0x8028A9F0-0x8028AB28). The PS2
   build reads the two animation tables through out-of-line getters of the
   fn_800D77F0 file (0x271490, 0x2714C0) that GameCube also discards; with
   no GameCube address for them, the tables are read directly here, as the
   Xbox build does after inlining. State is taken from the lower table as on
   PS2 (Xbox reads the two the other way round). Xbox and PS2 take only
   (line, buf) here; the GameCube caller fn_8017F7B0 forwards r3-r5 without
   setting them, so it gives no parameter count. This code is not measured. */
extern "C" void PrintPlayerDebugLine(int line, char *pBuf)
{
    int id;
    Object_80039F5C *p;

    fn_8003E038(GetHighlightedObject(), &id);
    p = fn_8009BCE8(&id);
    if (p != 0) {
        switch (line) {
        case 0:
            sprintf(pBuf, "O-Moves: %d     Jumping: %d", p->mRatings[0], p->mRatings[1]);
            break;
        case 1:
            sprintf(pBuf, "Run Power: %d   Catching: %d", p->mRatings[2], p->mRatings[3]);
            break;
        case 2:
            sprintf(pBuf, "Speed: %d       Tackling: %d", p->mRatings[4], p->mRatings[5]);
            break;
        case 3:
            sprintf(pBuf, "Passing: %d     Blocking: %d", p->mRatings[6], p->mRatings[7]);
            break;
        case 4:
            sprintf(pBuf, "Coverage: %d    D-Moves: %d", p->mRatings[8], p->mRatings[9]);
            break;
        case 5:
            sprintf(pBuf, "State: 0x%04X    Anim: %d",
                    lbl_803192BC[(p->mId >> 8) & 0xFF][(p->mId >> 16) & 0xFF],
                    lbl_803192D8[(p->mId >> 8) & 0xFF][(p->mId >> 16) & 0xFF]);
            break;
        default:
            pBuf[0] = 0;
            break;
        }
    } else {
        switch (line) {
        case 0:
            sprintf(pBuf, "Highlight a player for debug info.");
            break;
        case 2:
            sprintf(pBuf, "Press Z to toggle this window.");
            break;
        default:
            pBuf[0] = 0;
            break;
        }
    }
}

extern "C" void PrintDebugHelpLine(int line, char *pBuf, int, int *pCount)
{
    *pCount = 4;
    switch (line) {
    case 0:
        sprintf(pBuf, "Highlight a player for debug info");
        break;
    case 2:
        sprintf(pBuf, "Press Z to toggle this window.");
        break;
    case 4:
        sprintf(pBuf, "(Nothing else to see here)");
        break;
    default:
        pBuf[0] = 0;
        break;
    }
}

extern "C" void fn_8002D2D0(void) {}

extern "C" void fn_8002D2D4(void) {}

extern "C" int fn_8002D2D8(void) { return 0; }

extern "C" void fn_8002D2E0(Type_803EA368 *p, int a, unsigned int id, float value) {}

extern "C" void fn_8002D2E4(Type_8030660C *p, Block_80170E64 **ppTarget) {}

extern "C" void fn_8002D2E8(Type_803EA368 *p) {}

extern "C" void fn_8002D2EC(void) {}

extern "C" void fn_8002D2F0(Type_803EA368 *p, int id, int value, int index)
{
    p->mUnknown148C[index].mUnknown0 = fn_800311E4(p, id);
    p->mUnknown148C[index].mUnknown4 = value;
}

extern "C" void fn_8002D338(Type_803EA368 *p, Timer_8002E7C0 *pTimer)
{
    pTimer->mUnknown00 = fn_8002D158(p);
    pTimer->mUnknown08 = fn_8002D0D0(p);
    pTimer->mUnknown0C = 45;
    pTimer->mUnknown04 = 0;
    if (fn_800312FC(p, 0x25)) {
        int end = fn_800311E4(p, 0x25) + 150;

        pTimer->mUnknown08 = end - fn_8002D158(p);
    }
}

extern "C" Record_8002E7C0 *fn_8002D3BC(RecordList_8002E7C0 *pList)
{
    Record_8002E7C0 *pRecord = 0;

    if (pList->mUnknown57C <= 8) {
        pRecord = &pList->mUnknown000[pList->mUnknown57C++];
        memset(pRecord, 0, sizeof(Record_8002E7C0));
    }
    return pRecord;
}

extern "C" float fn_8002D414(int a, int b)
{
    float va[3];
    float vb[3];
    float result;

    if (fn_80031328(lbl_803EA368, a) && fn_80031328(lbl_803EA368, b)) {
        fn_8003122C(lbl_803EA368, a, va);
        fn_8003122C(lbl_803EA368, b, vb);
        result = vb[1] - va[1];
    } else {
        result = 0.0f;
    }
    return result;
}

extern "C" int fn_8002D4A0(Cond_8002D4A0 *pCond)
{
    int last = -1;
    int sum = 0;
    int minGap = -3600;
    int maxGap = 7200;
    unsigned char ordered = 0;
    int minDy = -150;
    int maxDy = 150;
    int ok = 1;
    int needMatch = 0;
    int matched = 0;
    int hasCall = 0;
    int flag = 0;
    int callA = 0;
    int callB = 0;
    unsigned char value374 = 0;

    for (; pCond->mOp != -1; pCond++) {
        if (!ok) {
            return 0;
        }
        switch (pCond->mOp) {
        case 0:
            ordered = pCond->mArgLow;
            break;
        case 1:
            minGap = pCond->mArg;
            break;
        case 2:
            maxGap = pCond->mArg;
            break;
        case 3:
            if (needMatch && !matched) {
                ok = 0;
            }
            needMatch = 0;
            matched = 0;
            if (!fn_80031328(lbl_803EA368, pCond->mArg)) {
                ok = 0;
                break;
            }
            if (last != -1) {
                if (ordered && fn_800311E4(lbl_803EA368, last) > fn_800311E4(lbl_803EA368, pCond->mArg)) {
                    ok = 0;
                }
                if (minDy > fn_8002D414(last, pCond->mArg)) {
                    ok = 0;
                }
                if (maxDy < fn_8002D414(last, pCond->mArg)) {
                    ok = 0;
                }
                if (minGap > ABS(fn_800311E4(lbl_803EA368, last) - fn_800311E4(lbl_803EA368, pCond->mArg))) {
                    ok = 0;
                }
                if (maxGap < ABS(fn_800311E4(lbl_803EA368, last) - fn_800311E4(lbl_803EA368, pCond->mArg))) {
                    ok = 0;
                }
            }
            last = pCond->mArg;
            break;
        case 4:
            if (fn_80031328(lbl_803EA368, pCond->mArg)) {
                ok = 0;
            }
            break;
        case 5:
            if (last == -1) {
                ok = 0;
            } else {
                Object_80039F5C *pObject;

                needMatch = 1;
                pObject = fn_80031294(lbl_803EA368, last);
                if (pObject == 0) {
                    ok = 0;
                } else if (pObject->mUnknown2914 == pCond->mArg) {
                    matched = 1;
                }
            }
            break;
        case 6:
            if (last == -1) {
                ok = 0;
            } else {
                float pos[3] = { 0.0f };

                if (fn_8003122C(lbl_803EA368, last, pos) == -1 || pos[0] < pCond->mArg) {
                    ok = 0;
                }
            }
            break;
        case 8:
            if (last == -1) {
                ok = 0;
            } else {
                float pos[3] = { 0.0f };

                if (fn_8003122C(lbl_803EA368, last, pos) == -1 || pos[0] > pCond->mArg) {
                    ok = 0;
                }
            }
            break;
        case 7:
            if (last == -1) {
                ok = 0;
            } else {
                float pos[3] = { 0.0f };

                if (fn_8003122C(lbl_803EA368, last, pos) == -1 || pos[1] < pCond->mArg) {
                    ok = 0;
                }
            }
            break;
        case 9:
            if (last == -1) {
                ok = 0;
            } else {
                float pos[3] = { 0.0f };

                if (fn_8003122C(lbl_803EA368, last, pos) == -1 || pos[1] > pCond->mArg) {
                    ok = 0;
                }
            }
            break;
        case 11:
            minDy = pCond->mArg;
            break;
        case 10:
            maxDy = pCond->mArg;
            break;
        case 12: /* placeholder values; see the source-form row */
        case 13:
            break;
        case 14:
            if (fn_80177F7C() < pCond->mArg) {
                ok = 0;
            }
            break;
        case 15:
            if (fn_80177F7C() > pCond->mArg) {
                ok = 0;
            }
            break;
        case 16:
        case 17:
            break;
        case 18:
            if (fn_8009D86C() < pCond->mArg) {
                ok = 0;
            }
            break;
        case 19:
            if (fn_8009D990(1) > pCond->mArg) {
                ok = 0;
            }
            break;
        case 20:
        case 21:
            break;
        case 22: {
            int gap = pCond->mArg;

            if (ABS(fn_801787DC(0) - fn_801787DC(1)) < gap) {
                ok = 0;
            }
            break;
        }
        case 23: {
            int gap = pCond->mArg;

            if (ABS(fn_801787DC(0) - fn_801787DC(1)) > gap) {
                ok = 0;
            }
            break;
        }
        case 25:
            sum += pCond->mArg;
            break;
        case 26:
            break;
        case 27:
            value374 = pCond->mArgLow;
            break;
        case 30:
            flag = 1;
            break;
        case 24:
            if (pCond->mArg) {
                if (fn_801787DC(fn_80178308()) <= fn_801787DC(fn_80178320())) {
                    ok = 0;
                }
            } else {
                if (fn_801787DC(fn_80178308()) >= fn_801787DC(fn_80178320())) {
                    ok = 0;
                }
            }
            break;
        case 31:
            if (fn_8016871C(fn_80178348())->mUnknown14 != pCond->mArg) {
                ok = 0;
            }
            break;
        case 32:
            needMatch = 1;
            if (fn_80031294(lbl_803EA368, pCond->mArg)) {
                ok = 0;
            }
            break;
        case 28:
            hasCall = 1;
            callA = pCond->mArg;
            break;
        case 29:
            callB = pCond->mArg;
            break;
        }
    }
    if (needMatch && !matched) {
        ok = 0;
    }
    if (ok) {
        lbl_803EA378 = sum;
        lbl_803EA374 = value374;
        lbl_803EA376 = flag;
        if (hasCall) {
            fn_8009BB50(callA, callB);
        }
    } else {
        lbl_803EA378 = 0;
    }
    return ok;
}

extern "C" void fn_8002DC00(Type_803EA368 *p, RecordList_8002E7C0 *pList)
{
    Record_8002E7C0 *pRecord = 0;
    Timer_8002E7C0 *pTimer = 0;
    int last = -1;
    int count = 0;
    Command_8002DC00 *pCmd;
    Vector_80039F5C origin;
    Point_8017886C pt;
    float range[3];

    pt = fn_80177FE0();
    origin.mX = pt.mX;
    origin.mY = pt.mY;
    origin.mZ = 0.0f;

    pCmd = fn_80030D14(lbl_803EA370);
    if (pCmd == 0) {
        return;
    }
    while (pCmd->mOp != -1) {
        switch (pCmd->mOp) {
        case 1:
            pRecord = fn_8002D3BC(pList);
            pTimer = &pRecord->mUnknown04;
            pRecord->mUnknown00 = 0;
            fn_8002D338(p, pTimer);
            pTimer->mUnknown08 = 0;
            pRecord->mUnknown1C.mUnknown34 = 0;
            pRecord->mUnknown1C.mUnknown00[0] = 0.0f;
            pRecord->mUnknown1C.mUnknown00[1] = 55.0f;
            pRecord->mUnknown1C.mUnknown00[2] = 30.0f;
            pRecord->mUnknown1C.mUnknown18 = 45.0f;
            pRecord->mUnknown1C.mUnknown1C[0] = origin.mX;
            pRecord->mUnknown1C.mUnknown1C[1] = origin.mY;
            pRecord->mUnknown1C.mUnknown1C[2] = origin.mZ;
            pRecord->mUnknown5C.mUnknown34 = 0;
            pRecord->mUnknown5C.mUnknown00[0] = 0.0f;
            pRecord->mUnknown5C.mUnknown00[1] = 55.0f;
            pRecord->mUnknown5C.mUnknown00[2] = 30.0f;
            pRecord->mUnknown5C.mUnknown18 = 45.0f;
            pRecord->mUnknown5C.mUnknown1C[0] = origin.mX;
            pRecord->mUnknown5C.mUnknown1C[1] = origin.mY;
            pRecord->mUnknown5C.mUnknown1C[2] = origin.mZ;
            break;
        case 2:
            pRecord->mUnknown1C.mUnknown38 = fn_80031294(p, pCmd->mArg);
            break;
        case 3:
            if (pCmd->mArg <= 4) {
                pList->mUnknown584 |= 1 << pCmd->mArg;
            } else {
                pRecord->mUnknown18 |= 1 << pCmd->mArg;
            }
            break;
        case 4:
            pRecord->mUnknown00 = pCmd->mArg;
            lbl_803EA375 = 0;
            break;
        case 9:
            fn_8003122C(p, pCmd->mArg, pRecord->mUnknown1C.mUnknown1C);
            break;
        case 0xA:
            *(Vector_80039F5C *)pRecord->mUnknown1C.mUnknown1C = origin;
            break;
        case 0xB:
            pRecord->mUnknown1C.mUnknown1C[0] = pCmd->mArg;
            break;
        case 0xC:
            pRecord->mUnknown1C.mUnknown1C[1] = pCmd->mArg;
            break;
        case 0xD:
            pRecord->mUnknown1C.mUnknown1C[2] = pCmd->mArg;
            break;
        case 0xE:
            pRecord->mUnknown1C.mUnknown1C[0] += pCmd->mArg;
            break;
        case 0xF:
            pRecord->mUnknown1C.mUnknown1C[1] += pCmd->mArg;
            break;
        case 0x10:
            pRecord->mUnknown1C.mUnknown1C[2] += pCmd->mArg;
            break;
        case 0x11:
            fn_8003122C(p, pCmd->mArg, pRecord->mUnknown1C.mUnknown28);
            break;
        case 0x12:
            pRecord->mUnknown1C.mUnknown28[0] = pCmd->mArg;
            break;
        case 0x13:
            pRecord->mUnknown1C.mUnknown28[1] = pCmd->mArg;
            break;
        case 0x14:
            pRecord->mUnknown1C.mUnknown28[2] = pCmd->mArg;
            break;
        case 0x15:
            pRecord->mUnknown1C.mUnknown28[0] += pCmd->mArg;
            break;
        case 0x16:
            pRecord->mUnknown1C.mUnknown28[1] += pCmd->mArg;
            break;
        case 0x17:
            pRecord->mUnknown1C.mUnknown28[2] += pCmd->mArg;
            break;
        case 5:
            pRecord->mUnknown1C.mUnknown34 = pCmd->mArg;
            break;
        case 6:
            lbl_803EA375 = 0;
        case 0x29:
            pRecord->mUnknown1C.mUnknown3C = pCmd->mArg;
            break;
        case 0x18:
            fn_8003122C(p, pCmd->mArg, pRecord->mUnknown1C.mUnknown00);
            break;
        case 0x19:
            *(Vector_80039F5C *)pRecord->mUnknown1C.mUnknown00 = origin;
            break;
        case 0x1A:
            pRecord->mUnknown1C.mUnknown00[0] = pCmd->mArg;
            break;
        case 0x1D:
            pRecord->mUnknown1C.mUnknown00[0] += pCmd->mArg;
            break;
        case 0x1B:
            pRecord->mUnknown1C.mUnknown00[1] = pCmd->mArg;
            break;
        case 0x1E:
            pRecord->mUnknown1C.mUnknown00[1] += pCmd->mArg;
            break;
        case 0x1C:
            pRecord->mUnknown1C.mUnknown00[2] = pCmd->mArg;
            break;
        case 0x1F:
            pRecord->mUnknown1C.mUnknown00[2] += pCmd->mArg;
            break;
        case 7: {
            float limit;
            fn_8003122C(p, pCmd->mArg, range);
            limit = lbl_803EA37C;
            if (limit > fn_800A32B4() - (float)fabs(range[0])) {
                switch (pRecord->mUnknown1C.mUnknown34) {
                case 0:
                case 1:
                case 2:
                case 3: {
                    float d = pRecord->mUnknown1C.mUnknown00[0] - range[0];

                    if ((range[0] > 0.0f && d > 0.0f) || (range[1] < 0.0f && d < 0.0f)) {
                        pRecord->mUnknown1C.mUnknown00[0] -= d + d;
                    }
                    break;
                }
                case 7:
                case 8:
                case 9:
                case 10:
                    if ((range[0] > 0.0f && pRecord->mUnknown1C.mUnknown00[0] > 0.0f)
                        || (range[0] < 0.0f && pRecord->mUnknown1C.mUnknown00[0] < 0.0f)) {
                        pRecord->mUnknown1C.mUnknown00[0] = -pRecord->mUnknown1C.mUnknown00[0];
                    }
                    break;
                }
            }
            break;
        }
        case 8:
            lbl_803EA37C = pCmd->mArg;
            break;
        /* Placeholder label values: the compare tree needs empty labels
           at 0, 0x20-0x23 and one value above 0x3F; 0x40 is not recovered. */
        case 0:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x40:
            break;
        case 0x24:
            pTimer->mUnknown00 = fn_800311E4(p, pCmd->mArg);
            break;
        case 0x25:
            pTimer->mUnknown00 += pCmd->mArg;
            pTimer->mUnknown00 = pTimer->mUnknown00 < p->mUnknownD70 ? p->mUnknownD70 : pTimer->mUnknown00;
            pTimer->mUnknown00 = pTimer->mUnknown00 > p->mUnknownD7C - 1 ? p->mUnknownD7C - 1 : pTimer->mUnknown00;
            break;
        case 0x26:
            pTimer->mUnknown0C = pCmd->mArg;
            break;
        case 0x27:
            pTimer->mUnknown08 = fn_800311E4(p, pCmd->mArg) - pTimer->mUnknown00;
            break;
        case 0x28:
            pTimer->mUnknown08 += pCmd->mArg;
            break;
        case 0x2A:
            fn_8002D2F0(p, last, pCmd->mArg, count);
            count++;
            lbl_803EA375 = 0;
            break;
        case 0x2B:
            p->mUnknown148C[count - 1].mUnknown0 += pCmd->mArg;
            break;
        case 0x2C:
            last = pCmd->mArg;
            break;
        case 0x2D:
            pRecord->mUnknown5C.mUnknown38 = fn_80031294(p, pCmd->mArg);
            break;
        case 0x2E:
            fn_8003122C(p, pCmd->mArg, pRecord->mUnknown5C.mUnknown1C);
            break;
        case 0x2F:
            *(Vector_80039F5C *)pRecord->mUnknown5C.mUnknown1C = origin;
            break;
        case 0x30:
            pRecord->mUnknown5C.mUnknown1C[0] = pCmd->mArg;
            break;
        case 0x31:
            pRecord->mUnknown5C.mUnknown1C[0] += pCmd->mArg;
            break;
        case 0x32:
            pRecord->mUnknown5C.mUnknown1C[1] = pCmd->mArg;
            break;
        case 0x33:
            pRecord->mUnknown5C.mUnknown1C[1] += pCmd->mArg;
            break;
        case 0x34:
            pRecord->mUnknown5C.mUnknown1C[2] = pCmd->mArg;
            break;
        case 0x35:
            pRecord->mUnknown5C.mUnknown1C[2] += pCmd->mArg;
            break;
        case 0x36:
            pRecord->mUnknown5C.mUnknown34 = pCmd->mArg;
            pList->mUnknown584 |= 0x10;
            break;
        case 0x37:
            pRecord->mUnknown5C.mUnknown3C = pCmd->mArg;
            lbl_803EA375 = 0;
            break;
        case 0x38:
            fn_8003122C(p, pCmd->mArg, pRecord->mUnknown5C.mUnknown00);
            break;
        case 0x39:
            *(Vector_80039F5C *)pRecord->mUnknown5C.mUnknown00 = origin;
            break;
        case 0x3A:
            pRecord->mUnknown5C.mUnknown00[0] = pCmd->mArg;
            break;
        case 0x3B:
            pRecord->mUnknown5C.mUnknown00[0] += pCmd->mArg;
            break;
        case 0x3C:
            pRecord->mUnknown5C.mUnknown00[1] = pCmd->mArg;
            break;
        case 0x3D:
            pRecord->mUnknown5C.mUnknown00[1] += pCmd->mArg;
            break;
        case 0x3E:
            pRecord->mUnknown5C.mUnknown00[2] = pCmd->mArg;
            break;
        case 0x3F:
            pRecord->mUnknown5C.mUnknown00[2] += pCmd->mArg;
            break;
        }
        pCmd++;
    }
}

extern "C" void fn_8002E75C(Type_803EA368 *p, Timer_8002E7C0 *pTimer)
{
    fn_8006E918();
    fn_8002D1B8(p, pTimer->mUnknown00 - pTimer->mUnknown04);
    fn_8002D128(p, pTimer->mUnknown0C);
    fn_8002D160(p, pTimer->mUnknown08);
    pTimer->mUnknown10 = 0;
}

extern "C" Record_8002E7C0 *fn_8002E7C0(RecordList_8002E7C0 *pList)
{
    return &pList->mUnknown000[pList->mUnknown580];
}

extern "C" int fn_8002E7D0(RecordList_8002E7C0 *pList)
{
    return pList->mUnknown580 + 1 < pList->mUnknown57C;
}

extern "C" void fn_8002E7EC(Type_803EA368 *p, RecordList_8002E7C0 *pList)
{
    Record_8002E7C0 *pCur = &pList->mUnknown000[pList->mUnknown580];
    Record_8002E7C0 *pNext = &pList->mUnknown000[pList->mUnknown580 + 1];

    if (pNext->mUnknown18 & 0x40) {
        pNext->mUnknown1C.mUnknown1C[0] = pCur->mUnknown1C.mUnknown0C[0];
        pNext->mUnknown1C.mUnknown1C[1] = pCur->mUnknown1C.mUnknown0C[1];
        pNext->mUnknown1C.mUnknown1C[2] = pCur->mUnknown1C.mUnknown0C[2];
    }
    if (pNext->mUnknown18 & 0x80) {
        pNext->mUnknown1C.mUnknown00[0] = p->mpUnknownDA0->mHeader.mUnknown04[0];
        pNext->mUnknown1C.mUnknown00[1] = p->mpUnknownDA0->mHeader.mUnknown04[1];
        pNext->mUnknown1C.mUnknown00[2] = p->mpUnknownDA0->mHeader.mUnknown04[2];
    }
    pList->mUnknown580++;
    fn_8002E75C(p, &pList->mUnknown000[pList->mUnknown580].mUnknown04);
}

extern "C" void fn_8002E890(RecordList_8002E7C0 *pList)
{
    fn_801C1F94(pList, 0, sizeof(RecordList_8002E7C0));
}

extern "C" void fn_8002E8B8(Type_803EA368 *p, RecordList_8002E7C0 *pList)
{
    fn_8017CFB4(7);
    if (pList->mUnknown584 & 1) {
        fn_8002D2EC();
    }
    fn_8002E75C(p, &pList->mUnknown000[0].mUnknown04);
    if (pList->mUnknown584 & 2) {
        fn_800711DC(0);
    } else if (pList->mUnknown584 & 4) {
        fn_800711DC(1);
    } else if (pList->mUnknown584 & 8) {
        fn_800711DC(2);
    } else {
        fn_800711DC(3);
    }
}

extern "C" int fn_8002E950(int mode)
{
    int searching = 1;
    Entry_80030D08 *pEntry = fn_80030D08();
    Entry_80030D08 *pStart;

    switch (mode) {
    case 0:
        lbl_803EA370 = mode;
        break;
    case 1:
        lbl_803EA370++;
        pEntry += lbl_803EA370;
        if (pEntry->mId == -1) {
            pEntry = fn_80030D08();
        }
        break;
    }
    pStart = pEntry;
    while (searching) {
        if (fn_8002D4A0(pEntry->mpConds)) {
            lbl_803EA370 = pEntry->mId;
            return 1;
        }
        pEntry++;
        if (pEntry->mId == -1) {
            pEntry = fn_80030D08();
        }
        if (pEntry == pStart) {
            searching = 0;
        }
    }
    return 0;
}

extern "C" void fn_8002EA18(void)
{
    fn_8013C868();
}

extern "C" void fn_8002EA38(void)
{
    fn_8013C90C();
}

extern "C" void fn_8002EA58(void)
{
    fn_8013C954();
}

extern "C" Camera_8013F738 *fn_8002EA78(Type_8002FDB4 *pDesc)
{
    Desc_8013C340 desc;
    Object_80039F5C *pObject;
    Camera_8013F738 *pCamera;

    fn_8013C340(&desc);
    pObject = fn_8009BCE8(&pDesc->mUnknown04);
    if (pObject) {
        desc.mUnknown08 = pDesc->mUnknown04;
    }
    switch (pDesc->mUnknown00) {
    case 1:
    case 2:
        desc.mUnknown00 = 4;
        desc.mUnknown04 = 15;
        break;
    case 3:
    default:
        desc.mUnknown00 = 1;
        desc.mUnknown04 = 13;
        break;
    }
    pCamera = (Camera_8013F738 *)fn_801C3610(3, &desc);
    pCamera->mUnknownF5C = 0;
    if (fn_8002D2D8()) {
        lbl_803EC634 = 1;
    } else {
        lbl_803EC634 = 0;
    }
    if (pDesc->mUnknown00 == 1) {
        RecordList_8002E7C0 *pList = &pCamera->mUnknown128;
        Type_803EA368 *p = lbl_803EA368;

        fn_8002E890(pList);
        fn_8002DC00(p, pList);
        fn_8002E8B8(p, pList);
    }
    fn_8013C624(pCamera, 8, 0, 0);
    if (pObject == 0) {
        if (fn_801383B0()) {
            lbl_803EC620 = fn_8013825C(fn_801374BC());
        } else {
            lbl_803EC620 = 0;
        }
    } else {
        lbl_803EC620 = pObject->mpUnknown4;
    }
    fn_8013C384(pCamera, 5, (int)&lbl_8030660C, 0);
    return pCamera;
}

extern "C" void fn_8002EBBC(Object_80039F5C *p)
{
    int on = 0;
    Block_80170E64 *pBlock;

    if (p && (p->mpUnknown4->mUnknown20 & 0x200)) {
        on = 1;
    }
    pBlock = fn_8013825C(fn_801374BC());
    if (on == 1) {
        pBlock->mUnknown20 |= 8;
    } else {
        pBlock->mUnknown20 &= ~8;
    }
}

extern "C" void fn_8002EC28(void)
{
    Object_80039F5C *pA;
    Object_80039F5C *pB;
    Object_80039F5C *p = fn_80030C70(&pA, &pB);

    if (lbl_803EC620) {
        if (lbl_803EC628 == 1 && p) {
            if (pA != pB) {
                float t = fn_80030D00();

                if (pA == 0) {
                    fn_80227930(&lbl_8030660C.mPos, &p->mpUnknown4->mUnknown4, &lbl_803EC620->mUnknown4, t);
                } else if (pB == 0) {
                    fn_80227930(&lbl_8030660C.mPos, &lbl_803EC620->mUnknown4, &p->mpUnknown4->mUnknown4, t);
                } else {
                    fn_80227930(&lbl_8030660C.mPos, &pB->mpUnknown4->mUnknown4, &pA->mpUnknown4->mUnknown4, t);
                }
            } else {
                Vector_80039F5C *pFocus = &lbl_8030660C.mPos;

                pFocus->mX = p->mpUnknown4->mUnknown4.mX;
                pFocus->mY = p->mpUnknown4->mUnknown4.mY;
                pFocus->mZ = p->mpUnknown4->mUnknown4.mZ;
            }
        } else {
            Block_80170E64 *pBlock = lbl_803EC620;
            Vector_80039F5C *pFocus = &lbl_8030660C.mPos;

            pFocus->mX = pBlock->mUnknown4.mX;
            pFocus->mY = pBlock->mUnknown4.mY;
            pFocus->mZ = pBlock->mUnknown4.mZ;
        }
    }
    if (fn_801383B0()) {
        fn_8002EBBC(p);
    }
}

extern "C" void fn_8002ED48(Point_8017886C *pOut, unsigned int dir, float speed)
{
    pOut->mY = 0.0f;
    pOut->mX = 0.0f;
    switch (dir) {
    case 0x35:
        pOut->mX = -speed;
        break;
    case 0x10:
    case 0x36:
        pOut->mX = speed;
        break;
    case 0x34:
        pOut->mY = -speed;
        break;
    case 0x11:
    case 0x33:
        pOut->mY = speed;
        break;
    }
    fn_80227384(pOut, pOut, -lbl_803EC61C);
}

extern "C" Block_80170E64 *fn_8002EDE8(Camera_8013F738 *pCamera, float *pDist, unsigned char *pFound)
{
    Block_80170E64 *pBest = fn_8003DF7C(&lbl_8030660C.mPos, pDist);
    Block_80170E64 *p;
    float dist;

    if (lbl_803EC634) {
        p = fn_80040F28(&lbl_8030660C.mPos, &dist);
        if (p && dist < *pDist) {
            *pDist = dist;
            pBest = p;
        }
    }
    if (fn_801383B0()) {
        *pFound = 0;
        if (fn_80030C70(0, 0) == 0) {
            p = fn_8013825C(fn_801374BC());
            dist = fn_8022781C(&p->mUnknown4, &lbl_8030660C.mPos);
            if (dist < *pDist) {
                *pDist = dist;
                *pFound = 1;
                pBest = p;
            }
        }
    }
    return pBest;
}

extern "C" void fn_8002EED0(void)
{
    switch (fn_800A3444()) {
    case 9:
        lbl_803EC638 = -1.5f;
        lbl_803EC63C = -0.5f;
        lbl_803EC644 = 3.5f;
        lbl_803EC640 = 2.5f;
        break;
    case 2:
        lbl_803EC638 = -4.0f;
        lbl_803EC63C = -0.5f;
        lbl_803EC644 = 6.0f;
        lbl_803EC640 = 2.5f;
        break;
    case 7:
        lbl_803EC638 = -8.5f;
        lbl_803EC63C = -0.5f;
        lbl_803EC644 = 10.5f;
        lbl_803EC640 = 2.5f;
        break;
    case 1:
        lbl_803EC638 = -1.0f;
        lbl_803EC63C = -0.5f;
        lbl_803EC644 = 3.0f;
        lbl_803EC640 = 2.5f;
        break;
    case 5:
        lbl_803EC638 = -0.5f;
        lbl_803EC63C = -0.75f;
        lbl_803EC644 = 2.5f;
        lbl_803EC640 = 2.75f;
        break;
    case 3:
        lbl_803EC638 = -1.0f;
        lbl_803EC63C = -0.5f;
        lbl_803EC644 = 3.0f;
        lbl_803EC640 = 2.5f;
        break;
    case 11:
        lbl_803EC638 = -1.0f;
        lbl_803EC63C = -0.5f;
        lbl_803EC644 = 3.0f;
        lbl_803EC640 = 2.5f;
        break;
    default:
        lbl_803EC638 = -0.5f;
        lbl_803EC63C = -0.5f;
        lbl_803EC644 = 2.5f;
        lbl_803EC640 = 2.5f;
        break;
    }
}

extern "C" void fn_8002F01C(Camera_8013F738 *pCamera, Type_8030660C *pTarget)
{
    float dist = fn_8022785C(&pTarget->mPos, (Vector_80039F5C *)pCamera->mHeader.mUnknown04);
    float overX = fabsf(pCamera->mHeader.mUnknown04[0]) - (fn_80178A08() + lbl_803EC640 + lbl_803EC63C);
    float overY = fabsf(pCamera->mHeader.mUnknown04[1]) - (fn_80178A44() + lbl_803EC644 + lbl_803EC638);
    float overZ = fabsf(pCamera->mHeader.mUnknown04[2]) - 9.2f;
    float limitX = 16.0f;
    float limitY = 16.0f;
    float limitZ = 16.0f;

    if (overX > 0.0f) {
        limitX = dist * ((fn_80178A08() + lbl_803EC640 + lbl_803EC63C - fabsf(pTarget->mPos.mX))
                         / (fabsf(pCamera->mHeader.mUnknown04[0]) - fabsf(pTarget->mPos.mX)));
    }
    if (overY > 0.0f) {
        limitY = dist * ((fn_80178A44() + lbl_803EC644 + lbl_803EC638 - fabsf(pTarget->mPos.mY))
                         / (fabsf(pCamera->mHeader.mUnknown04[1]) - fabsf(pTarget->mPos.mY)));
    }
    if (overZ > 0.0f) {
        limitZ = dist * ((9.2f - fabsf(pTarget->mPos.mZ))
                         / (fabsf(pCamera->mHeader.mUnknown04[2]) - fabsf(pTarget->mPos.mZ)));
    }
    lbl_803EC62C = limitY <= limitX ? limitY : limitX;
    lbl_803EC62C = limitZ <= lbl_803EC62C ? limitZ : lbl_803EC62C;
}

extern "C" void fn_8002F1E0(Camera_8013F738 *pCamera)
{
    if (lbl_803EC630 > lbl_803EC62C) {
        pCamera->mUnknown30 = lbl_803EC62C;
    } else {
        pCamera->mUnknown30 = lbl_803EC630;
    }
}

extern "C" void fn_8002F204(Camera_8013F738 *pCamera, float amount)
{
    float v = amount * 0.2f + lbl_803EC630;

    if (lbl_803EC634) {
        lbl_803EC630 = v < 0.0f ? 0.0f : v;
    } else {
        lbl_803EC630 = CLAMP(v, 2.0f, lbl_803EC62C);
    }
}

extern "C" void fn_8002F26C(Camera_8013F738 *pCamera, unsigned int input, float amount)
{
    Point_8017886C offset;

    if ((unsigned int)(fn_801F7ABC() - lbl_803EC624) > 29) {
        if (lbl_803EC620 == 0) {
            float dist;
            unsigned char flag;
            Block_80170E64 *pTarget = fn_8002EDE8(pCamera, &dist, &flag);

            if (pTarget != 0) {
                Point_8017886C clamped;
                clamped.mX = CLAMP(pTarget->mUnknown4.mX, -fn_80178A08(), fn_80178A08());
                clamped.mY = CLAMP(pTarget->mUnknown4.mY, -fn_80178A44(), fn_80178A44());
                if (dist >= 0.25f || clamped.mX != pTarget->mUnknown4.mX
                    || clamped.mY != pTarget->mUnknown4.mY) {
                    fn_8002ED48(&offset, input, amount * 0.15f);
                    fn_80227638(&lbl_8030660C.mPos, &lbl_8030660C.mPos, &offset);
                } else {
                    lbl_803EC620 = pTarget;
                    lbl_803EC624 = fn_801F7ABC();
                    lbl_803EC628 = flag;
                    fn_80031040(0);
                }
            } else {
                fn_8002ED48(&offset, input, amount * 0.15f);
                fn_80227638(&lbl_8030660C.mPos, &lbl_8030660C.mPos, &offset);
                lbl_8030660C.mPos.mX = CLAMP(lbl_8030660C.mPos.mX, -fn_80178A08(), fn_80178A08());
                lbl_8030660C.mPos.mY = CLAMP(lbl_8030660C.mPos.mY, -fn_80178A44(), fn_80178A44());
            }
        } else {
            float step = 0.275f;
            if (amount < 0.0f) {
                step = -step;
            }
            fn_8002ED48(&offset, input, step);
            fn_80227638(&lbl_8030660C.mPos, &lbl_8030660C.mPos, &offset);
            lbl_803EC620 = 0;
            fn_80031040(1);
        }
    }
}

extern "C" void fn_8002F510(Camera_8013F738 *pCamera, float amount)
{
    fn_8013C540(pCamera, -(int)((amount + amount) * 46603.37890625f));
}

extern "C" void fn_8002F550(Camera_8013F738 *pCamera, float amount)
{
    int base = pCamera->mUnknownD0 & 0xFFFFFF;
    int angle = base + (int)(amount * 37282.703125f);

    if (!lbl_803EC634) {
        angle = CLAMP(angle, 0xC00000, 0xFF49F5);
    }
    fn_8013C57C(pCamera, angle - base);
}

extern "C" void fn_8002F5D4(Camera_8013F738 *pCamera, float amount)
{
    float v = amount * 0.2f + pCamera->mUnknownCC;

    v = CLAMP(v, 1.0f, 9.2f);
    pCamera->mUnknownCC = v;
}

extern "C" Camera_8013F738 *fn_8002F61C(Type_8002FDB4 *pDesc)
{
    Camera_8013F738 *pCamera;

    memset(&lbl_8030660C, 0, sizeof(Type_8030660C));
    lbl_803EC620 = 0;
    lbl_803EC61C = 0;
    lbl_803EC624 = fn_801F7ABC();
    lbl_803EC628 = 1;
    lbl_803EC62C = 16.0f;
    pCamera = fn_8002EA78(pDesc);
    if (pDesc->mUnknown08) {
        fn_8002F71C(pCamera);
    }
    lbl_803EC630 = pCamera->mUnknown30;
    fn_80031040(0);
    pCamera->mUnknown90 = 0x200000;
    pCamera->mUnknown88 = 0x400000;
    pCamera->mUnknown64 = 0.3f;
    pCamera->mUnknown68 = 0.3f;
    pCamera->mUnknown6C = 0.3f;
    pCamera->mUnknown70 = 0.2f;
    pCamera->mUnknown74 = 0.3f;
    pCamera->mUnknown78 = 0.3f;
    pCamera->mUnknown8C = 0x200000;
    pCamera->mUnknown84 = 0x400000;
    pCamera->mUnknown7C = 0.3f;
    pCamera->mUnknown80 = 0.2f;
    fn_801C39D0(pCamera, 0.1f);
    pCamera->mUnknown94 |= 4;
    lbl_803EA384 = 1;
    fn_8002EED0();
    return pCamera;
}

extern "C" void fn_8002F71C(Camera_8013F738 *pCamera)
{
    fn_8002B2D4(0, pCamera, 0, 0);
}

extern "C" void fn_8002F74C(Camera_8013F738 *pCamera)
{
    fn_80030CFC();
    if (!lbl_803EC634) {
        Point_8017886C clamped;
        clamped.mX = CLAMP(lbl_8030660C.mPos.mX, -fn_80178A08(), fn_80178A08());
        clamped.mY = CLAMP(lbl_8030660C.mPos.mY, -fn_80178A44(), fn_80178A44());
        if (clamped.mX != lbl_8030660C.mPos.mX || clamped.mY != lbl_8030660C.mPos.mY) {
            lbl_8030660C.mPos.mX = clamped.mX;
            lbl_8030660C.mPos.mY = clamped.mY;
            lbl_803EC620 = 0;
            lbl_803EC628 = 0;
            fn_80031040(1);
        }
    }
    fn_8002EC28();
    lbl_8030660C.mPos.mZ = lbl_803EA380;
    if (!lbl_803EC634) {
        lbl_803EC62C = 16.0f;
        fn_8002F1E0(pCamera);
        pCamera->mUnknown94 |= 4;
        fn_8013C2B4(pCamera, 0, 0, 0);
        fn_8002F01C(pCamera, &lbl_8030660C);
        pCamera->mUnknown94 |= 4;
    }
    fn_8002F1E0(pCamera);
    fn_8002D2E4(&lbl_8030660C, &lbl_803EC620);
    fn_80031018(&lbl_8030660C.mPos.mX, 0);
    fn_8013C2B4(pCamera, 0, 0, 0);
    lbl_803EC61C = pCamera->mUnknown38;
    if (!lbl_803EC634) {
        pCamera->mHeader.mUnknown04[0] = CLAMP(pCamera->mHeader.mUnknown04[0], -fn_80178A08() - lbl_803EC63C, fn_80178A08() + lbl_803EC63C);
        pCamera->mHeader.mUnknown04[1] = CLAMP(pCamera->mHeader.mUnknown04[1], -fn_80178A44() - lbl_803EC638, fn_80178A44() + lbl_803EC638);
    }
}

extern "C" void fn_8002F9D8(Camera_8013F738 *pCamera)
{
    fn_8013C2B4(pCamera, 0, 0, 0);
}

extern "C" void fn_8002FA04(Camera_8013F738 *pCamera, int detach)
{
    if (detach) {
        fn_8002B3DC(0, pCamera);
    }
    fn_801C3640(pCamera);
    fn_80031040(0);
    if (fn_8019623C(0x23000)) {
        fn_80195EFC(1, 15, 0x808080, 0);
    }
    lbl_803EA384 = 0;
}

extern "C" unsigned char fn_8002FA84(void)
{
    return lbl_803EA384;
}

extern "C" void fn_8002FA8C(Camera_8013F738 *pCamera, int unused, unsigned int input, float amount)
{
    switch (input) {
    case 0x12:
        fn_8002F510(pCamera, amount);
        break;
    case 0x13:
        fn_8002F550(pCamera, amount);
        break;
    case 0x3A:
        fn_8002F204(pCamera, 1.0f);
        break;
    case 0x37:
        fn_8002F204(pCamera, -1.0f);
        break;
    case 8:
        break;
    }
    if (pCamera->mUnknownF5C & 1) {
        switch (input) {
        case 0x36:
            fn_8002F510(pCamera, 1.0f);
            break;
        case 0x35:
            fn_8002F510(pCamera, -1.0f);
            break;
        case 0x33:
            fn_8002F550(pCamera, 1.0f);
            break;
        case 0x34:
            fn_8002F550(pCamera, -1.0f);
            break;
        case 0x10:
            fn_8002F510(pCamera, amount);
            break;
        case 0x11:
            fn_8002F550(pCamera, amount);
            break;
        }
    } else {
        switch (input) {
        case 0x10:
        case 0x11:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
            fn_8002F26C(pCamera, input, amount);
            break;
        }
    }
}

extern "C" void fn_8002FC28(Camera_8013F738 *pCamera, int player, unsigned int input, float amount)
{
    unsigned int action;

    switch (input) {
    case 0x37:
        action = 0;
        break;
    case 0x3A:
        action = 1;
        break;
    case 0x33:
        action = 2;
        break;
    case 0x34:
        action = 3;
        break;
    case 0x11:
        action = 4;
        break;
    case 0x12:
        action = 5;
        break;
    case 0x13:
        action = 6;
        break;
    default:
        action = 7;
        break;
    }
    switch (action) {
    case 0:
        fn_8002F204(pCamera, -1.0f);
        fn_802196B4(lbl_803EB688, player, 20, 0, 0, 1);
        break;
    case 1:
        fn_8002F204(pCamera, 1.0f);
        fn_802196B4(lbl_803EB688, player, 20, 0, 0, 1);
        break;
    case 2:
        fn_8002F5D4(pCamera, 1.0f);
        fn_802196B4(lbl_803EB688, player, 20, 0, 0, 1);
        break;
    case 3:
        fn_8002F5D4(pCamera, -1.0f);
        fn_802196B4(lbl_803EB688, player, 20, 0, 0, 1);
        break;
    case 4:
        fn_8002F5D4(pCamera, amount);
        fn_802196B4(lbl_803EB688, player, 20, 0, 0, 1);
        break;
    case 5:
        fn_8002F510(pCamera, amount);
        fn_802196B4(lbl_803EB688, player, 20, 0, 0, 1);
        break;
    case 6:
        fn_8002F550(pCamera, amount);
        fn_802196B4(lbl_803EB688, player, 20, 0, 0, 1);
        break;
    }
}

extern "C" void fn_8002FDB4(Type_8002FDB4 *pDesc)
{
    memset(pDesc, 0, sizeof(Type_8002FDB4));
    fn_8009BD2C(0, &pDesc->mUnknown04);
    pDesc->mUnknown08 = 1;
}


/* Accessors that nothing on GameCube calls; the linker drops them. */
extern "C" Block_80170E64 *GetHighlightedObject(void) { return lbl_803EC620; }

extern "C" void SetFocusHeight(unsigned char reset, float height)
{
    if (reset) {
        lbl_803EA380 = 1.2f;
    } else {
        lbl_803EA380 = height;
    }
}

extern "C" int fn_8002FDFC(void)
{
    if (lbl_803EC660 >= lbl_803EC658) {
        lbl_803EC654 = 1;
        lbl_803EC660 = 0;
    }
    return lbl_803EC660++;
}

extern "C" void fn_8002FE34(int index)
{
    char *pBuffer = fn_80199CC4(index, lbl_803EC650);

    if (pBuffer != 0) {
        Type_80190ED4 stream;
        Type_80030ACC *pEntry;

        fn_80190ED4(&stream, pBuffer, 1);
        for (pEntry = (Type_80030ACC *)fn_801C6B4C(lbl_803EC648, 0); pEntry != 0;
             pEntry = (Type_80030ACC *)fn_801C6C84(lbl_803EC648, pEntry)) {
            pEntry->mpWrite(&stream);
        }
        fn_80190EF0(&stream);
        fn_80199C94(pBuffer, index, lbl_803EC650);
    }
}


extern "C" void fn_8002FECC(Type_803EA368 *pGame, char **ppCur, char **ppNext, char **ppPrev, char **ppNext2,
                            float *pT)
{
    int ticks;
    int frame;
    int cur;
    int next;
    int next2 = -1;
    int prev = -1;

    *ppPrev = *ppNext2 = 0;
    ticks = (pGame->mUnknownD74 - pGame->mUnknownD70) * 60 + pGame->mUnknownD78;
    frame = ticks / 120;
    *pT = (float)(ticks % 120) * (1.0f / 120.0f);
    cur = (frame + lbl_803EC65C) % lbl_803EC658;
    if (lbl_803EC654) {
        if (cur != lbl_803EC65C) {
            if (cur == 0) {
                prev = lbl_803EC658 - 1;
            } else {
                prev = cur - 1;
            }
        }
        if (cur == lbl_803EC660) {
            next = cur;
        } else {
            next = (cur + 1) % lbl_803EC658;
            if (next != lbl_803EC660) {
                next2 = (next + 1) % lbl_803EC658;
            }
        }
    } else {
        if (cur > 0 && cur <= lbl_803EC660) {
            prev = cur - 1;
        }
        if (cur != lbl_803EC660) {
            next = (cur + 1) % lbl_803EC658;
            next2 = next + 1;
        } else {
            next = cur;
        }
        if (next2 > lbl_803EC660) {
            next2 = -1;
        }
    }
    *ppCur = fn_80199CF0(cur, lbl_803EC650);
    *ppNext = fn_80199CF0(next, lbl_803EC650);
    if (prev >= 0) {
        *ppPrev = fn_80199CF0(prev, lbl_803EC650);
    } else {
        fn_80199CF0(cur, lbl_803EC650);
        *ppPrev = 0;
    }
    if (next2 >= 0) {
        *ppNext2 = fn_80199CF0(next2, lbl_803EC650);
    } else {
        fn_80199CF0(next, lbl_803EC650);
        *ppNext2 = 0;
    }
}

extern "C" void fn_800300D0(void) {}

extern "C" void fn_800300D4(void *pStream, float *pValues, int bits, float scale)
{
    long long value = fn_80190F18(pStream, bits * 2);
    float x = (int)((value << (64 - bits * 2)) >> (64 - bits));
    float y = (int)((value << (64 - bits)) >> (64 - bits));

    scale = 1.0f / scale;
    pValues[0] = x * scale;
    pValues[1] = y * scale;
}

extern "C" void fn_800301C4(void *pStream, float *pValues, int bits, float scale)
{
    long long value = fn_80190F18(pStream, bits * 3);
    float x = (int)((value << (64 - bits * 3)) >> (64 - bits));
    float y = (int)((value << (64 - bits * 2)) >> (64 - bits));
    float z = (int)((value << (64 - bits)) >> (64 - bits));

    scale = 1.0f / scale;
    pValues[0] = x * scale;
    pValues[1] = y * scale;
    pValues[2] = z * scale;
}

extern "C" void fn_80030304(void *pStream, float *pValues, int bits, float scale)
{
    long long value = fn_80190F18(pStream, bits * 4);
    float x = (int)((value << (64 - bits * 4)) >> (64 - bits));
    float y = (int)((value << (64 - bits * 3)) >> (64 - bits));
    float z = (int)((value << (64 - bits * 2)) >> (64 - bits));
    float w = (int)((value << (64 - bits)) >> (64 - bits));

    scale = 1.0f / scale;
    pValues[0] = x * scale;
    pValues[1] = y * scale;
    pValues[2] = z * scale;
    pValues[3] = w * scale;
}

extern "C" void fn_80030490(void *pStream, float *pValues, int bits, float scale)
{
    unsigned long long mask = (1ULL << bits) - 1;
    unsigned long long x = ((long long)(int)(pValues[0] * scale) & mask) << bits;
    unsigned long long y = (long long)(int)(pValues[1] * scale) & mask;

    fn_80191068(pStream, x | y, bits * 2);
}

extern "C" void fn_80030554(void *pStream, float *pValues, int bits, float scale)
{
    unsigned long long mask = (1ULL << bits) - 1;
    unsigned long long x = ((long long)(int)(pValues[0] * scale) & mask) << bits * 2;
    unsigned long long y = ((long long)(int)(pValues[1] * scale) & mask) << bits;
    unsigned long long z = (long long)(int)(pValues[2] * scale) & mask;

    fn_80191068(pStream, x | y | z, bits * 3);
}

extern "C" void fn_8003065C(void *pStream, float *pValues, int bits, float scale)
{
    unsigned long long mask = (1ULL << bits) - 1;
    unsigned long long x = ((long long)(int)(pValues[0] * scale) & mask) << bits * 3;
    unsigned long long y = ((long long)(int)(pValues[1] * scale) & mask) << bits * 2;
    unsigned long long z = ((long long)(int)(pValues[2] * scale) & mask) << bits;
    unsigned long long w = (long long)(int)(pValues[3] * scale) & mask;

    fn_80191068(pStream, x | y | z | w, bits * 4);
}

extern "C" void fn_800307AC(void)
{
    lbl_803EC654 = lbl_803EC660 = lbl_803EC65C = 0;
}

extern "C" void fn_800307C0(Type_803EA368 *pGame)
{
    if (((pGame->mUnknownD74 - pGame->mUnknownD70) & 1) == 0) {
        fn_8002FE34(fn_8002FDFC());
        if (lbl_803EC654) {
            pGame->mUnknownD70 += 2;
        }
    }
    pGame->mUnknownD74++;
}

extern "C" void fn_80030828(Type_803EA368 *pGame)
{
    int count = lbl_803EC660 - 1;

    lbl_803EC660 = count;
    if (lbl_803EC658 == 0) {
        lbl_803EC660 = lbl_803EC65C = 0;
        count = 1;
    } else if (lbl_803EC654 == 1) {
        if (count < 0) {
            lbl_803EC660 = lbl_803EC658 - 1;
            lbl_803EC65C = 0;
        } else {
            lbl_803EC65C = (count + 1) % lbl_803EC658;
        }
        count = lbl_803EC658;
    }
    pGame->mUnknownD7C = pGame->mUnknownD70 + (count - 1) * 2;
}

extern "C" void fn_800308A4(Type_803EA368 *pGame)
{
    lbl_803EC668 = 0;
    lbl_803EC664 = 0;
    fn_80162780(!(pGame->mUnknownD94 & 0x10000), 0);
    fn_8015A0D0(0);
}

extern "C" void fn_800308E8(Type_803EA368 *p)
{
    if (fn_800AD9B4() == 4 || fn_8006560C()) {
        fn_80162780(0, 0);
    } else {
        fn_80162780(1, 1);
    }
    fn_8015A0D0(1);
}

extern "C" void fn_80030940(Type_803EA368 *pGame)
{
    char *pCur;
    char *pNext;
    char *pPrev;
    char *pNext2;
    Type_80190ED4 streams[4];
    Type_80030ACC *pRecord;

    fn_8002FECC(pGame, &pCur, &pNext, &pPrev, &pNext2, &lbl_803EC66C);
    fn_80190ED4(&streams[0], pCur, 0);
    fn_80190ED4(&streams[1], pNext, 0);
    if (pPrev) {
        fn_80190ED4(&streams[2], pPrev, 0);
    }
    if (pNext2) {
        fn_80190ED4(&streams[3], pNext2, 0);
    }
    for (pRecord = (Type_80030ACC *)fn_801C6B4C(lbl_803EC648, 0); pRecord;
         pRecord = (Type_80030ACC *)fn_801C6C84(lbl_803EC648, pRecord)) {
        if (pPrev == 0) {
            if (pNext2 == 0) {
                pRecord->mpRead(&streams[1], &streams[0], 0, 0, lbl_803EC66C);
            } else {
                pRecord->mpRead(&streams[1], &streams[0], 0, &streams[3], lbl_803EC66C);
            }
        } else if (pNext2 == 0) {
            pRecord->mpRead(&streams[1], &streams[0], &streams[2], 0, lbl_803EC66C);
        } else {
            pRecord->mpRead(&streams[1], &streams[0], &streams[2], &streams[3], lbl_803EC66C);
        }
    }
    fn_80190EF0(&streams[0]);
    fn_80190EF0(&streams[1]);
    if (pPrev) {
        fn_80190EF0(&streams[2]);
    }
    if (pNext2) {
        fn_80190EF0(&streams[3]);
    }
    fn_800300D0();
}

extern "C" void fn_80030ACC(void (*pWrite)(Type_80190ED4 *),
                            void (*pRead)(Type_80190ED4 *, Type_80190ED4 *, Type_80190ED4 *, Type_80190ED4 *, float),
                            unsigned int size, const char *pName)
{
    Type_80030ACC *pRecord = (Type_80030ACC *)fn_801C6A20(lbl_803EC648);

    pRecord->mpWrite = pWrite;
    pRecord->mpRead = pRead;
    pRecord->mSize = size;
    fn_801C6AA4(lbl_803EC648, pRecord, 0);
    lbl_803EC650 += size;
}

extern "C" void fn_80030B30(void)
{
    Type_80030ACC *pRecord;

    for (pRecord = (Type_80030ACC *)fn_801C6B4C(lbl_803EC648, 0); pRecord;
         pRecord = (Type_80030ACC *)fn_801C6C84(lbl_803EC648, pRecord)) {
        lbl_803EC650 += pRecord->mSize;
    }
    lbl_803EC650 = ((((lbl_803EC650 / 2 + 7) / 8 + 7) & ~7) + 31) & ~31;
    lbl_803EC658 = lbl_803EC64C / lbl_803EC650;
    fn_80199D58(lbl_803EC658, lbl_803EC650);
}

extern "C" void fn_80030BC0(int size)
{
    lbl_803EC648 = fn_801C68FC(1, 0, 11, 12, 0, 0);
    lbl_803EC650 = 0;
    lbl_803EC64C = 0x400000 - size;
    if (size > 0x400000 || lbl_803EC64C < 0x3C000) {
        lbl_803EC64C = 0x3C000;
    }
}

extern "C" void fn_80030C40(void)
{
    fn_801C69E4(lbl_803EC648);
    lbl_803EC648 = 0;
    fn_80199DB0();
}

extern "C" Object_80039F5C *fn_80030C70(Object_80039F5C **ppA, Object_80039F5C **ppB)
{
    if (ppA && ppB) {
        *ppA = lbl_803EC664;
        *ppB = lbl_803EC668;
    }
    if (lbl_803EC664) {
        return lbl_803EC664;
    }
    return lbl_803EC668;
}

extern "C" void fn_80030CA4(Object_80039F5C *pA, Object_80039F5C *pB)
{
    lbl_803EC664 = pA;
    lbl_803EC668 = pB;
}

extern "C" void fn_80030CB0(int value) { lbl_803EA388 = value; }

extern "C" int fn_80030CB8(void) { return lbl_803EA388; }

extern "C" unsigned char fn_80030CC0(Type_803EA368 *pGame)
{
    unsigned char result = lbl_803EC654;

    if (!result && ((pGame->mUnknownD74 - pGame->mUnknownD70) & 1) == 0 && lbl_803EC660 >= lbl_803EC658) {
        result = 1;
    }
    return result;
}

extern "C" void fn_80030CFC(void) {}

extern "C" float fn_80030D00(void) { return lbl_803EC66C; }

extern "C" Entry_80030D08 *fn_80030D08(void) { return lbl_802CC9B4; }

extern "C" Command_8002DC00 *fn_80030D14(int id)
{
    Script_802CC938 *pEntry;

    for (pEntry = lbl_802CC938; pEntry->mId != -1; pEntry++) {
        if (pEntry->mId == id) {
            return pEntry->mpCommands;
        }
    }
    return 0;
}
#endif
