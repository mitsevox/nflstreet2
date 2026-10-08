#include "game/fn_8021D7B8.h"
#include "game/fn_801FCE10.h"
#include "game/Object_80039F5C.h"
#include "game/cu_8003AEA8.h"
#include "game/fn_8003B6BC.h"
#include "game/fn_8007F828.h"
#include "game/fn_8007F6F8.h"
#include "game/fn_801C1F94.h"
#include "game/fn_8017F584.h"
#include "game/fn_801801F0.h"
#include "game/ModuleGroup_8003450C.h"
#include "game/SndgCrowd.h"
#include "game/cu_80064864.h"
#include "game/Camera_8013F738.h"
#include "game/Class_80148A58.h"
#include "game/InGame.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80178D18.h"
#include "game/fn_80218FC4.h"
#include "game/cu_8017DD68.h"
#include "game/Class_80297AB8.h"
#include "game/Class_80297BF8.h"
#include "game/Class_80297C60.h"
#include "game/Class_80297CE8.h"
#include "game/Class_802A56E8.h"

/* One step of a tutorial lesson (32-byte records of the step tables). */
struct Step_802DEC08 {
    unsigned long long mMask;
    unsigned int mDuration;
    float mUnknown12;
    unsigned int mPrompts;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
};

/* Base of the five tutorial lessons; the vtable pointer follows the one word
   of data. */
class Lesson_802A3DC8 {
public:
    virtual void vfn_01() = 0;
    virtual int vfn_02() = 0;
    virtual int vfn_03();
    virtual int vfn_04();
    virtual int vfn_05();
    virtual int vfn_06();
    virtual Step_802DEC08 *vfn_07() = 0;
    virtual const char *vfn_08() = 0;
    virtual const char *vfn_09() = 0;

    int mUnknown0;
};

struct Game_80157558;
struct Game_801576F0;
struct Game_801582C4;

struct GamePtr_80157558 {
    GamePtr_80157558() : mp(0) {}
    Game_80157558 *mp;
};

struct GamePtr_801576F0 {
    GamePtr_801576F0() : mp(0) {}
    Game_801576F0 *mp;
};

struct GamePtr_801582C4 {
    GamePtr_801582C4() : mp(0) {}
    Game_801582C4 *mp;
};

class Lesson_802A3D68 : public Lesson_802A3DC8 {
public:
    virtual void vfn_01();
    virtual int vfn_02();
    virtual Step_802DEC08 *vfn_07();
    virtual const char *vfn_08();
    virtual const char *vfn_09();
    virtual ~Lesson_802A3D68() {}

    GamePtr_80157558 mpGame;
};

class Lesson_802A3D08 : public Lesson_802A3DC8 {
public:
    virtual void vfn_01();
    virtual int vfn_02();
    virtual Step_802DEC08 *vfn_07();
    virtual const char *vfn_08();
    virtual const char *vfn_09();
    virtual ~Lesson_802A3D08() {}

    int mUnknown8;
    GamePtr_801576F0 mpGame;
};

class Lesson_802A3CA8 : public Lesson_802A3DC8 {
public:
    virtual void vfn_01();
    virtual int vfn_02();
    virtual Step_802DEC08 *vfn_07();
    virtual const char *vfn_08();
    virtual const char *vfn_09();
    virtual ~Lesson_802A3CA8() {}

    GamePtr_80157558 mpGame;
};

class Lesson_802A3C48 : public Lesson_802A3DC8 {
public:
    virtual void vfn_01();
    virtual int vfn_02();
    virtual Step_802DEC08 *vfn_07();
    virtual const char *vfn_08();
    virtual const char *vfn_09();
    virtual ~Lesson_802A3C48() {}

    GamePtr_801582C4 mpGame;
};

class Lesson_802A3BE8 : public Lesson_802A3DC8 {
public:
    virtual void vfn_01();
    virtual int vfn_02();
    virtual Step_802DEC08 *vfn_07();
    virtual const char *vfn_08();
    virtual const char *vfn_09();
    virtual ~Lesson_802A3BE8() {}

    GamePtr_80157558 mpGame;
};

class Class_802A3B80 : public Class_80297BF8 {
public:
    virtual void vfn_03();
    virtual void vfn_04(float dt);
    virtual void vfn_06();
    virtual void vfn_07();
    virtual void vfn_11(float dt);

    int mUnknown4;
};

class Class_802A3B10 : public Class_80297CE8 {
public:
    virtual ~Class_802A3B10() {}
    virtual void vfn_04(float dt);
    virtual void vfn_05(float dt);
    virtual void vfn_06(float dt);
    virtual unsigned char vfn_08() { return mUnknown4; }
    virtual int vfn_12();

    unsigned char mUnknown4;
};

class Class_802A3AD8 : public Class_80297AB8 {
public:
    virtual void vfn_03();
    virtual void vfn_04(float dt);
};

/* Counter member of Class_802A3A48, cleared on construction. */
struct Count_802A3A48 {
    Count_802A3A48() : m(0) {}
    unsigned int m;
};

class Class_802A3A48 : public Class_80297C60 {
public:
    virtual void vfn_03(float dt);
    virtual void vfn_04(float dt);
    virtual void vfn_05();
    virtual void vfn_06();
    virtual void vfn_07();
    virtual void vfn_10();
    virtual int vfn_11();
    virtual int vfn_12();
    virtual void vfn_14(float dt);
    virtual ~Class_802A3A48() {}
    void fn_80158C04();

    unsigned char mUnknown4;
    unsigned char mUnknown5;
    signed char mUnknown6;
    Count_802A3A48 mUnknown8;
    int mUnknown12;
};

class Class_802A3990 : public Class_802A56E8 {
public:
    virtual int vfn_02();
    virtual int vfn_08();
    virtual void vfn_10();
    virtual void vfn_11(int a);
    virtual int vfn_12();
    virtual int vfn_14() { return 0; }
};

class Class_802A3958 : public Class_802A3AD8 {
public:
    virtual void vfn_04(float dt);
};

class Class_802A38C8 : public Class_802A3A48 {
public:
    virtual void vfn_03(float dt);
};

/* Flag member of Class_802A3858, cleared on construction. */
struct Flag_802A3858 {
    Flag_802A3858() : m(0) {}
    unsigned char m;
};

class Class_802A3858 : public Class_802A3B10 {
public:
    virtual void vfn_04(float dt);
    virtual void vfn_05(float dt);

    Flag_802A3858 mUnknown8;
};

class Class_802A3820 : public Class_802A3AD8 {
public:
    virtual void vfn_04(float dt);
};

/* The game objects a lesson creates in its first entry. */
struct Game_80157558 {
    Class_802A3B80 mObject0;
    Class_802A3B10 mObject8;
    Class_802A3AD8 mObject16;
    Class_802A3A48 mObject20;
    Class_802A3990 mObject36;
};

struct Game_801582C4 {
    Class_802A3B80 mObject0;
    Class_802A3B10 mObject8;
    Class_802A3820 mObject16;
    Class_802A3A48 mObject20;
    Class_802A3990 mObject36;
};

struct Game_801576F0 {
    Class_802A3B80 mObject0;
    Class_802A3858 mObject8;
    Class_802A3958 mObject20;
    Class_802A38C8 mObject24;
    Class_802A3990 mObject40;
};


/* Two floats returned in memory by fn_80177FE0. */
struct Pair_80177FE0 {
    float mX;
    float mY;
};

struct Team_80168EBC {
    char mUnknown0[0x40];
    int mUnknown40;
};

/* Text block posted with messages 0x80000080 and 0x80000081. */
struct Text_8031BEE4 {
    Text_8031BEE4() {}
    int mUnknown0;
    int mSize;
    char *mpText;
};

void *operator new(unsigned int size, int unknown);

extern "C" {
void fn_8003A450(void);
void fn_8003B1F4(int group);
void fn_8003B688(int group, int *values);
void fn_800406C0(int a);
void fn_8004730C(int a);
void fn_80047874(unsigned char enable);
void fn_800544A4(const char *pTitle, const char *pText, const char *pButtons);
int fn_80054568(void);
void fn_80057F28(void);
void fn_800582D0(void);
void fn_8005BF18(void);
int fn_8005BFD4(void);
void fn_80065814(void);
void fn_8006BCC8(int type);
void fn_8006EA04(int channel, unsigned int level);
void fn_8006EC24(void);
void fn_8006F824(int a);
void fn_80072C90(int a, int b);
int fn_80072E6C(void);
void fn_80072F04(void);
void fn_800731D0(int a);
void fn_800744C0(unsigned char value);
int fn_80074638(void);
int fn_80085A34(int formation, int team);
unsigned char fn_80087F10(void);
unsigned char fn_8008801C(void);
int fn_80088068(int id);
void fn_800880D0(unsigned int id, unsigned int count);
int fn_80088224(int id);
unsigned int fn_80088390(int a, int b, int flag);
unsigned int fn_8008849C(int a, int b, int flag);
int fn_800885A8(int a, int b);
float fn_800885E8(int a, int b);
void fn_8009B924(void);
void fn_8009D888(int index, int a);
void fn_8009D8CC(int index);
void fn_8009D944(int index);
void fn_8009D964(int index, int value);
void fn_8009D984(int a);
unsigned int fn_8009D990(int index);
void fn_8009E01C(void);
void fn_800A039C(Class_80297AB8 *pObject);
void fn_800A7A0C(int a);
void fn_800A7B5C(void);
void fn_800A8F08(void);
void fn_800AD910(int a, float b);
void fn_800AE988(void);
void fn_800B3EFC(int team);
void fn_800B63B0(void);
int fn_800B65A0(int unknown);
int fn_800B81A4(void);
void fn_800B847C(int a, int b);
void fn_800B9598(Class_80297C60 *pObject);
void fn_800BC51C(Class_80297BF8 *pObject);
void fn_800BF658(int a);
void fn_800BF6CC(int a);
void fn_800BFAB4(Class_80297CE8 *pObject);
void fn_800C1CA0(void);
void fn_800C1E50(void);
void fn_800C87CC(int a, int b);
void fn_800D4164(int a, float b, int c);
void fn_800D6F08(void);
void fn_800D7158(void);
void fn_800D7520(int a);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pObject);
void fn_8011DF90(void);
void fn_80138590(Object_80137ABC *pBall);
void fn_8013A910(Object_80137ABC *pBall, int *pAngles);
void fn_8013AD9C(Object_80137ABC *pBall, int a);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
void fn_8013C6F0(Camera_8013F738 *pCamera);
void fn_8013F97C(int a);
Camera_8013F738 *fn_8013FA04(int index);
void fn_8013FA58(int a, int b);
void fn_8013FA8C(int a);
void fn_801485B4(void);
void fn_801485EC(int mode);
int fn_801485F4(void);
void fn_80148644(void);
int fn_801486A0(void);
Class_80148A58 * fn_80148A58(void);
void fn_80149040(Object_80039F5C *pObject);
void fn_8014F3DC(int a);
void fn_8015C254(int a);
void fn_80167EA0(int team);
void fn_80168264(void);
void fn_80168640(int team, int kind);
void fn_80168744(int team, unsigned int a, unsigned int b, unsigned int c);
Team_80168EBC * fn_80168EBC(int team);
void fn_801735D8(unsigned int mask);
void fn_80177C50(int a);
void fn_80177E6C(int a, int b);
int fn_80177F70(void);
void fn_80177F88(int a);
Pair_80177FE0 fn_80177FE0(void);
void fn_801780A8(Pair_80177FE0 pos);
void fn_801782B0(void);
int fn_80178320(void);
void fn_8017833C(int value);
void fn_80178370(void);
int fn_801784E8(void);
void fn_801787FC(int which, short value);
float fn_80178A2C(void);
int fn_80178C60(void);
void fn_80178CD8(int a);
void fn_80178F20(Class_802A56E8 *pObject);
void fn_8017D6B8(int a, int b);
void fn_8017D9D8(int a);
void fn_8017DB44(void);
int fn_801801D0(void);
void fn_80194CBC(void);
void fn_80194F1C(unsigned char enabled);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
char * fn_801C2EF0(char *pDest, const char *pSource, int count);
unsigned int fn_801C3180(const char *pText);
void fn_802195E4(void *p, short a, short b);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
void fn_8022DA44(int a, int *pA, int b, int *pB, int tag);
void fn_801564DC(int index, int value);
void fn_8015651C(void);
void fn_801566DC(unsigned char value);
unsigned char fn_801566E4(void);
void fn_801566EC(void);
void fn_801566F8(void);
int fn_80156704(void);
void fn_80156724(unsigned int value);
void fn_8015672C(unsigned int value);
void fn_80156734(unsigned int value);
void fn_8015673C(void);
void fn_80156854(void);
unsigned int fn_801568E8(void);
unsigned int fn_801568F0(void);
Lesson_802A3DC8 * fn_801568F8(void);
void fn_80156900(unsigned int count, unsigned int total);
void fn_80156928(void);
unsigned char fn_80156960(void);
unsigned char fn_801569B4(void);
void fn_801569BC(void);
int fn_801569C8(unsigned int lesson);
void fn_80156AB0(void);
void fn_80156C48(void);
void fn_80156C78(int index, int value);
int fn_80156C8C(unsigned long long mask);
unsigned char fn_80156D14(void);
void fn_80156D1C(unsigned char value);
void fn_80156D24(unsigned int duration);
int fn_80156DC4(void);
void fn_80156E74(float *pX, float *pY, float *pZ);
void fn_80156E9C(unsigned int mask, int value, int flag);
void fn_80156F30(void);
float fn_80157000(void);
int fn_80157080(void);
short fn_80157448(int team, int unused, short value);
void fn_801574DC(int value);
void fn_80157514(void);
unsigned char fn_80157550(void);
void fn_8015844C(int show);
void fn_80158A4C(void);
void fn_80158AA8(void);
void fn_80158BB4(unsigned int mask);

extern void *lbl_803EB688;
extern const float lbl_803ED6A4;
extern const float lbl_803ED6A8;
}

#define TIME_HOURS(t) ((t) / 3600)
#define TIME_MINUTES(t) ((t) / 60 - TIME_HOURS(t) * 60)
#define TIME_SECONDS(t) ((t) - (TIME_HOURS(t) * 60 + TIME_MINUTES(t)) * 60)

extern "C" {
Text_8031BEE4 lbl_8031BEE4;
Text_8031BEE4 lbl_8031BEF0;
Lesson_802A3D68 lbl_8031BEFC;
Lesson_802A3CA8 lbl_8031BF08;
Lesson_802A3C48 lbl_8031BF14;
Lesson_802A3BE8 lbl_8031BF20;
Lesson_802A3D08 lbl_8031BF2C;
int lbl_8031BF3C[45];
char lbl_8031BFF0[0x1C];
char lbl_8031C00C[0x20];

int lbl_802DEBD0[] = {
    0x8000005A, 0x8000005B, 0x8000005A, 0x80000060, 0x8000005E, 0x8000005C, 0x8000005D,
    0x8000005F, 0x80000066, 0x80000065, 0x80000061, 0x80000062, 0x80000063, 0x80000064,
};

Lesson_802A3DC8 *lbl_803EB300 = 0;
unsigned int lbl_803EB304 = 0xFFFF;
unsigned int lbl_803EB308 = 0xFFFF;
unsigned int lbl_803EB30C = 0xFFFF;
int lbl_803EB310 = 1;
int lbl_803EB314 = 0;
unsigned char lbl_803EB318 = 1;

Text_8031BEE4 *lbl_803ECA2C;
Text_8031BEE4 *lbl_803ECA30;
int lbl_803ECA34;
unsigned char lbl_803ECA38;
unsigned int lbl_803ECA3C;
unsigned int lbl_803ECA40;
unsigned int lbl_803ECA44;
unsigned int lbl_803ECA48;
unsigned char lbl_803ECA4C;
unsigned char lbl_803ECA4D;
unsigned int lbl_803ECA50;
unsigned int lbl_803ECA54;
unsigned char lbl_803ECA58;

Step_802DEC08 lbl_802DEC08[] = {
    { 0x1ULL, 3, 1.0f, 0x2, 5, 0, 0 },
    { 0x1000000000ULL, 3, 1.0f, 0x20, 15, 0, 0 },
    { 0x8000000000ULL, 3, 1.0f, 0x10, 5, 0, 0 },
    { 0x800000ULL, 3, 1.0f, 0x80, 5, 0, 0 },
    { 0x400000ULL, 3, 1.0f, 0x40, 5, 0, 0 },
    { 0x20000000000ULL, 3, 1.0f, 0x81, 5, 0, 0 },
};

Step_802DEC08 lbl_802DECC8[] = {
    { 0x40ULL, 3, 1.0f, 0x21, 5, 0, 0 },
    { 0x800ULL, 3, 1.0f, 0x81, 5, 0, 0 },
    { 0x4000ULL, 6, 1.0f, 0x81, 5, 0, 0 },
    { 0x80001000000ULL, 3, 1.0f, 0xB1, 5, 0, 0 },
    { 0x4000000000ULL, 3, 1.0f, 0x41, 5, 0, 0 },
    { 0x600000000ULL, 3, 1.0f, 0x80, 5, 1, 0 },
    { 0x10000000000ULL, 3, 1.0f, 0x80, 5, 1, 0 },
    { 0xA00000000ULL, 15, 1.0f, 0x80, 5, 1, 0 },
    { 0x100000000000ULL, 3, 1.0f, 0xA1, 5, 0, 0 },
};

Step_802DEC08 lbl_802DEDE8[] = {
    { 0x200000ULL, 3, 1.0f, 0x2, 0, 0, 0 },
    { 0x80024000000ULL, 3, 1.0f, 0x80, 15, 0, 0 },
    { 0x80030000000ULL, 3, 1.0f, 0x20, 15, 0, 0 },
    { 0x80028000000ULL, 3, 1.0f, 0x10, 15, 0, 0 },
    { 0xC0004000000ULL, 3, 1.0f, 0x80, 1, 0, 0 },
    { 0xC0010000000ULL, 3, 1.0f, 0x20, 1, 0, 0 },
    { 0xC0008000000ULL, 3, 1.0f, 0x10, 1, 0, 0 },
    { 0x8ULL, 3, 1.0f, 0x40, 5, 0, 0 },
    { 0x80000ULL, 3, 1.0f, 0x8, 5, 0, 0 },
};

Step_802DEC08 lbl_802DEF08[] = {
    { 0x1ULL, 3, 1.0f, 0x2, 0, 0, 0 },
    { 0x10000ULL, 3, 1.0f, 0x10, 5, 0, 0 },
    { 0x10ULL, 3, 1.0f, 0x20, 15, 0, 0 },
    { 0x80ULL, 3, 1.0f, 0x20, 0, 0, 0 },
    { 0x200ULL, 3, 1.0f, 0x80, 5, 0, 0 },
    { 0x1000ULL, 3, 1.0f, 0x80, 5, 0, 0 },
    { 0x20000ULL, 5, 1.0f, 0x40, 5, 0, 0 },
};

Step_802DEC08 lbl_802DEFE8[] = {
    { 0x8000ULL, 3, 1.0f, 0x1, 0, 0, 0 },
    { 0x100000ULL, 3, 1.0f, 0x201, 5, 0, 0 },
    { 0x20ULL, 3, 1.0f, 0x21, 15, 0, 0 },
    { 0x100ULL, 3, 1.0f, 0x21, 5, 0, 0 },
    { 0x400ULL, 3, 1.0f, 0x81, 5, 0, 0 },
    { 0x2000ULL, 3, 1.0f, 0x81, 5, 0, 0 },
    { 0x80002000000ULL, 3, 1.0f, 0xB1, 5, 0, 0 },
    { 0x2000000000ULL, 3, 1.0f, 0x41, 5, 0, 0 },
};
char lbl_802DF0E8[] = "You Passed.  Awesome!";
char lbl_802DF100[] = "You need more practice at this.";
char lbl_802DF120[] = "Are you sure you want to quit?";
char lbl_802DF140[] = "Congratulations! You have completed this tutorial category.";

}


extern "C" {

void fn_801564DC(int index, int value)
{
    fn_8021D7B8(lbl_803EB688, lbl_802DEBD0[index], 1, &value);
}

void fn_8015651C(void)
{
    Record_8003B6BC records[2];
    int list[8];
    int home;
    int away;
    unsigned int team;
    unsigned int i;

    fn_801FCE10(0, "select 'GTHG' into \x82 and 'GTAG' into \x82 from 'FNIG'\n", &home, &away);
    for (team = 0; team <= 1; team++) {
        for (i = 0; i <= 6; i++) {
            list[i] = fn_80039F5C((unsigned char)team, i)->mUnknown2908;
        }
        list[7] = 0x7FFF;
        fn_8003B3F8(team, list, 4);
        fn_8003B1F4(team);
    }
    fn_8003B6BC(0, &records[0]);
    fn_8003B6BC(1, &records[1]);
    fn_801FCE10(0, "delete from 'AGCD'\n");
    /* 0x41474344 is 'AGCD', the table cleared by the query above. */
    fn_8022DA44(home, records[0].mUnknown, away, records[1].mUnknown, 0x41474344);
    for (team = 0; team <= 1; team++) {
        for (i = 0; i <= 6; i++) {
            Object_80039F5C *pObject = fn_80039F5C((unsigned char)team, i);
            pObject->mUnknown2908 = records[team].mUnknown[i];
            fn_80149040(pObject);
        }
    }
    for (i = 0; i < 14; i++) {
        fn_801FCE10(0, "select 'DIOP' into \x85 from 'YALP' where 'DIGP' = \x85 and 'DIGT' = \x85\n",
                    &records[0].mUnknown[i], records[0].mUnknown[i], home);
        fn_801FCE10(0, "select 'DIOP' into \x85 from 'YALP' where 'DIGP' = \x85 and 'DIGT' = \x85\n",
                    &records[1].mUnknown[i], records[1].mUnknown[i], away);
    }
    fn_8003B688(0, records[0].mUnknown);
    fn_8003B688(1, records[1].mUnknown);
}

void fn_801566DC(unsigned char value)
{
    lbl_803EB318 = value;
}

unsigned char fn_801566E4(void)
{
    return lbl_803EB318;
}

void fn_801566EC(void)
{
    lbl_803ECA58 = 0;
}

void fn_801566F8(void)
{
    lbl_803ECA58 = 0;
}

int fn_80156704(void)
{
    return lbl_803EB30C != 0xFFFF;
}

void fn_80156724(unsigned int value)
{
    lbl_803EB304 = value;
}

void fn_8015672C(unsigned int value)
{
    lbl_803EB308 = value;
}

void fn_80156734(unsigned int value)
{
    lbl_803EB30C = value;
}

void fn_8015673C(void)
{
    unsigned int lesson = fn_801568F0();
    unsigned int step = fn_801568E8();

    lbl_803ECA3C = step;
    switch (lesson) {
    case 0:
        lbl_803EB300 = &lbl_8031BEFC;
        break;
    case 1:
        lbl_803EB300 = &lbl_8031BF08;
        break;
    case 2:
        lbl_803EB300 = &lbl_8031BF14;
        break;
    case 3:
        lbl_803EB300 = &lbl_8031BF20;
        break;
    case 4:
        lbl_803EB300 = &lbl_8031BF2C;
        break;
    }
    lbl_803EB314 = fn_8007F828(14);
    fn_8007F6F8(14, 0);
    fn_80178F20(0);
    lbl_803EB300->mUnknown0 = step;
    lbl_803EB300->vfn_01();
    lbl_803EB310 = fn_8007F828(0);
    fn_8007F6F8(0, 0);
    fn_80087F10();
    fn_80156734(step);
    fn_801566DC(1);
}

void fn_80156854(void)
{
    lbl_803EB300->vfn_02();
    lbl_803EB300 = 0;
    fn_8008801C();
    fn_8007F6F8(14, lbl_803EB314);
    lbl_803EB314 = 0;
    fn_80178F20(0);
    fn_8007F6F8(0, lbl_803EB310);
    lbl_803EB310 = 1;
    fn_8006EC24();
    lbl_803EB30C = 0xFFFF;
    lbl_803EB304 = 0xFFFF;
    fn_8015672C(5);
}

unsigned int fn_801568E8(void)
{
    return lbl_803EB304;
}

unsigned int fn_801568F0(void)
{
    return lbl_803EB308;
}

Lesson_802A3DC8 *fn_801568F8(void)
{
    return lbl_803EB300;
}

void fn_80156900(unsigned int count, unsigned int total)
{
    if (count != 0) {
        lbl_803ECA48 = total / count;
    } else {
        lbl_803ECA48 = 0;
    }
    lbl_803ECA4C = 0;
    lbl_803ECA4D = 0;
}

void fn_80156928(void)
{
    unsigned int time = fn_800289A8();

    lbl_803ECA40 = time;
    if (lbl_803ECA48 != 0) {
        lbl_803ECA44 = time + lbl_803ECA48;
    } else {
        lbl_803ECA44 = 0;
    }
}

unsigned char fn_80156960(void)
{
    if (lbl_803ECA44 != 0) {
        if (fn_800289A8() >= lbl_803ECA44) {
            fn_80156928();
            lbl_803ECA4C ^= 1;
        }
    } else {
        lbl_803ECA4C = 1;
    }
    return lbl_803ECA4C;
}

unsigned char fn_801569B4(void)
{
    return lbl_803ECA4D;
}

void fn_801569BC(void)
{
    lbl_803ECA4D = lbl_803ECA4C;
}

int fn_801569C8(unsigned int lesson)
{
    int done = 0;
    unsigned int step = fn_801568E8() + 1;
    unsigned int count = 0;

    fn_800880D0(lesson, step);
    step = fn_80088068(lesson);
    switch (lesson) {
    case 0:
        count = 7;
        break;
    case 2:
        count = 8;
        break;
    case 3:
        count = 6;
        break;
    case 1:
    case 4:
        count = 9;
        break;
    }
    if (step == 0 && fn_80088224(lesson) != 0) {
        if (fn_801568E8() + 1 >= count) {
            done = 1;
        } else {
            step = fn_801568E8() + 1;
        }
    }
    fn_80156724(step);
    return done;
}

void fn_80156AB0(void)
{
    unsigned int team;
    unsigned short i;
    int side;
    unsigned int a;
    unsigned int b;

    for (team = 0; team <= 1; team++) {
        for (i = 0; i <= 6; i++) {
            Object_80039F5C *pObject = fn_80039F5C((unsigned char)team, i);
            fn_800EFE60(0, &pObject->mUnknown3048, pObject);
        }
    }
    side = fn_800885A8(fn_801568F0(), fn_801568E8());
    b = fn_8008849C(fn_801568F0(), fn_801568E8(), side);
    a = fn_80088390(fn_801568F0(), fn_801568E8(), side);
    if (side == 1) {
        fn_8017833C(0);
        fn_80168640(0, 1);
        fn_80168744(0, 0, 0, (unsigned char)a);
        fn_80167EA0(0);
        fn_80168640(1, 11);
        fn_80168744(1, 0, 0, (unsigned char)b);
        fn_80167EA0(1);
    } else {
        fn_8017833C(1);
        fn_80168640(1, 1);
        fn_80168744(1, 0, 0, (unsigned char)b);
        fn_80167EA0(1);
        fn_80168640(0, 11);
        fn_80168744(0, 0, 0, (unsigned char)a);
        fn_80167EA0(0);
    }
    fn_800B3EFC(0);
    fn_800B3EFC(1);
}

void fn_80156C48(void)
{
    fn_801C1F94(lbl_8031BF3C, 0, sizeof(lbl_8031BF3C));
}

void fn_80156C78(int index, int value)
{
    lbl_8031BF3C[index] = value;
}

int fn_80156C8C(unsigned long long mask)
{
    int result = 1;
    unsigned char i;

    for (i = 0; i <= 44; i++) {
        if ((mask >> i & 1) && lbl_8031BF3C[i] == 0) {
            result = 0;
            break;
        }
    }
    return result;
}

unsigned char fn_80156D14(void)
{
    return lbl_803ECA38;
}

void fn_80156D1C(unsigned char value)
{
    lbl_803ECA38 = value;
}

void fn_80156D24(unsigned int duration)
{
    unsigned int seconds = TIME_SECONDS(fn_8009D990(2));

    lbl_803ECA50 = seconds;
    lbl_803ECA54 = seconds + duration;
}

int fn_80156DC4(void)
{
    unsigned int seconds = TIME_SECONDS(fn_8009D990(2));

    if (seconds < lbl_803ECA50) {
        seconds += 60;
    }
    return seconds >= lbl_803ECA54;
}

void fn_80156E74(float *pX, float *pY, float *pZ)
{
    *pX = 620.0f;
    *pY = 408.0f;
    *pZ = 1.0f;
}

void fn_80156E9C(unsigned int mask, int value, int flag)
{
    unsigned int i;

    fn_80156F30();
    for (i = 0; i <= 13; i++) {
        if (mask & 1 << i) {
            int arg;

            if (i < 3) {
                if (flag) {
                    arg = 1;
                } else {
                    arg = value;
                }
            } else {
                arg = value;
            }
            if (arg != 0) {
                fn_801564DC(i, arg);
            }
        }
    }
}

void fn_80156F30(void)
{
    fn_801564DC(1, 0);
    fn_801564DC(0, 0);
    fn_801564DC(3, 0);
    fn_801564DC(2, 0);
    fn_801564DC(5, 0);
    fn_801564DC(7, 0);
    fn_801564DC(7, 0);
    fn_801564DC(4, 0);
    fn_801564DC(6, 0);
    fn_801564DC(8, 0);
    fn_801564DC(9, 0);
    fn_801564DC(10, 0);
    fn_801564DC(11, 0);
    fn_801564DC(12, 0);
    fn_801564DC(13, 0);
}

float fn_80157000(void)
{
    float base = fn_80178A2C();
    float offset = fn_800885E8(fn_801568F0(), fn_801568E8());

    if (offset >= base + base) {
        offset = base + base;
    }
    return base - offset;
}

}

int Lesson_802A3DC8::vfn_03()
{
    return 14;
}

int Lesson_802A3DC8::vfn_04()
{
    return 7;
}

int Lesson_802A3DC8::vfn_05()
{
    return 7;
}

int Lesson_802A3DC8::vfn_06()
{
    return 7;
}

extern "C" {

int fn_80157080(void)
{
    int done = 0;
    unsigned int lesson = fn_801568F0();
    int mode = fn_801486A0();

    if (lesson != 5) {
        int modes[5] = { 2, 3, 0, 4, 15 };
        mode = modes[lesson];
        fn_800AD910(0, 0.0f);
        fn_8017DB44();
        fn_800582D0();
        fn_80156854();
        fn_8015672C(5);
        fn_800C1CA0();
        fn_800C1E50();
        fn_8004730C(1);
        fn_8015C254(1);
        fn_80047874(1);
        if (mode != 15) {
            fn_801485B4();
            fn_801485EC(mode);
            switch (mode) {
            case 2:
                fn_800744C0(0);
                fn_80148A58()->vfn_07(0, 1);
                fn_80148A58()->vfn_07(1, 5);
                break;
            case 0:
                fn_801735D8(0x800);
                fn_8009D8CC(1);
                fn_8009D964(1, 0);
                fn_800744C0(0);
                fn_8014F3DC(180);
                break;
            case 4:
                if (fn_800B65A0(fn_80178320()) == 0xFF) {
                    fn_80177C50(0);
                }
                fn_80148A58()->vfn_07(0, 21);
                fn_80168640(1, 1);
                fn_80168744(1, 0, 0, 0);
                fn_80167EA0(1);
                fn_80085A34(fn_80168EBC(1)->mUnknown40, 1);
                fn_800B3EFC(1);
                fn_800B63B0();
                fn_800B847C(fn_800B65A0(1), 0);
                break;
            }
            fn_8015651C();
            fn_801485F4();
            fn_80072F04();
            fn_8006EC24();
            fn_80072F04();
            lbl_803ECA58 = 0;
        }
        done = 1;
    } else if (mode != 15) {
        unsigned int next = 5;
        switch (mode) {
        case 2:
            next = 1;
            break;
        case 3:
            next = 2;
            break;
        case 0:
            next = 3;
            break;
        case 4:
            next = 4;
            break;
        }
        fn_800744C0(1);
        if (next != 5) {
            done = 1;
            fn_800AD910(0, 0.0f);
            fn_8017DB44();
            fn_800582D0();
            fn_80148644();
            fn_800C1CA0();
            fn_800C1E50();
            fn_8004730C(1);
            fn_8015C254(1);
            fn_80047874(1);
            fn_8015672C(next);
            fn_80156734(0);
            fn_80156724(0);
            fn_8015651C();
            fn_8015673C();
            lbl_803ECA58 = done;
        }
    } else {
        fn_80072F04();
        fn_8006EC24();
        fn_80072F04();
    }

    if (done) {
        for (unsigned int team = 0; team <= 1; team++) {
            for (unsigned int i = 0; i <= 6; i++) {
                Object_80039F5C *pPlayer = fn_80039F5C((unsigned char)team, i);
                pPlayer->mUnknown9[2] = i < (unsigned int)fn_80178D70((unsigned char)team);
            }
        }
        gTurbo.fn_80035EE0();
        fn_8009D8CC(2);
        fn_8009D984(fn_80178C60());
        fn_800D7158();
        gPlayBook.fn_800355FC();
        fn_80057F28();
        fn_800AD910(1, 0.0f);
        fn_800655E8();
        fn_8006BCC8(3);
        fn_80072F04();
        fn_8006F394(3, 0);
        fn_80168264();
    }
    return done;
}

short fn_80157448(int team, int unused, short value)
{
    if (fn_8017F584() == 11 && fn_800B65A0(team) == 0xFF) {
        value = (short)(value * 0.75f);
    }
    return value;
}

void fn_801574DC(int value)
{
    fn_8021D7B8(lbl_803EB688, 0x80000072, 1, &value);
}

void fn_80157514(void)
{
    if (fn_8017F584() == 11) {
        fn_80065814();
        if (fn_800655F8() == 0) {
            fn_800655D0();
        }
    }
}

unsigned char fn_80157550(void)
{
    return lbl_803ECA58;
}

}

void Lesson_802A3BE8::vfn_01()
{
    mpGame.mp = new (0) Game_80157558;
    fn_800BC51C(&mpGame.mp->mObject0);
    fn_800BFAB4(&mpGame.mp->mObject8);
    fn_800A039C(&mpGame.mp->mObject16);
    fn_800B9598(&mpGame.mp->mObject20);
    mpGame.mp->mObject36.vfn_11(2);
    fn_80178F20(&mpGame.mp->mObject36);
    fn_801568E8();
}

int Lesson_802A3BE8::vfn_02()
{
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_80178F20(0);
    delete mpGame.mp;
    mpGame.mp = 0;
    return 0;
}

Step_802DEC08 *Lesson_802A3BE8::vfn_07()
{
    return &lbl_802DEC08[fn_801568E8()];
}

const char *Lesson_802A3BE8::vfn_08()
{
    return "Defense, defense, defense.  You need to stop the other team to win.";
}

const char *Lesson_802A3BE8::vfn_09()
{
    return "You now have the skills to make the big stop!  Try them out in the 4 on 4 Street Event to 21 points.";
}

void Lesson_802A3D08::vfn_01()
{
    mpGame.mp = new (0) Game_801576F0;
    fn_800BC51C(&mpGame.mp->mObject0);
    fn_800BFAB4(&mpGame.mp->mObject8);
    fn_800A039C(&mpGame.mp->mObject20);
    fn_800B9598(&mpGame.mp->mObject24);
    fn_80178F20(&mpGame.mp->mObject40);
}

int Lesson_802A3D08::vfn_02()
{
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_80178F20(0);
    delete mpGame.mp;
    mpGame.mp = 0;
    return 0;
}

Step_802DEC08 *Lesson_802A3D08::vfn_07()
{
    return &lbl_802DECC8[fn_801568E8()];
}

const char *Lesson_802A3D08::vfn_08()
{
    return "There are a lot of new skills to learn in NFL STREET 2, and you are going to need to master them all.";
}

const char *Lesson_802A3D08::vfn_09()
{
    return "Now that you know how to use the walls and GameBreakers, you are ready for a full game of 7-on-7 to 36 points.";
}

void Class_802A3858::vfn_04(float dt)
{
    Class_802A3B10::vfn_04(dt);
    mUnknown8.m = 0;
    unsigned int step = fn_801568E8();
    if (step >= 5 && step <= 7) {
        fn_800A7A0C(1);
        fn_800A8F08();
        if (step == 7) {
            fn_800D4164(1, lbl_803ED6A8, 0);
        } else {
            fn_800D4164(1, lbl_803ED6A4 + 0.2f, 0);
        }
        fn_800A7B5C();
    } else {
        fn_800A7A0C(1);
        if (step == 8) {
            fn_800406C0(0xC0);
        }
    }
}

void Class_802A3858::vfn_05(float dt)
{
    unsigned int step = fn_801568E8();
    if (step >= 5 && step <= 7 && mUnknown4 && !mUnknown8.m) {
        fn_8017D9D8(1);
        mUnknown8.m = 1;
    }
    Class_802A3B10::vfn_05(dt);
}

void Class_802A3958::vfn_04(float dt)
{
    static unsigned int lbl_803EB31C = 0;
    unsigned int step = fn_801568E8();
    Step_802DEC08 *pStep;

    if (step == 3) {
        Class_80297AB8::vfn_04(dt);
        unsigned char done = fn_80156D14();
        if (done == 0) {
            unsigned char button = fn_80156960();
            pStep = fn_801568F8()->vfn_07();
            unsigned int prompts = pStep->mPrompts;
            if (fn_8013BA58(fn_801374BC(), 0) != 4) {
                if (button != fn_801569B4()) {
                    fn_80156E9C(pStep->mPrompts, 0, 1);
                    if (++lbl_803EB31C > 2) {
                        lbl_803EB31C = done;
                    }
                    switch (lbl_803EB31C) {
                    case 0:
                        prompts = 0x20;
                        break;
                    case 1:
                        prompts = 0x10;
                        break;
                    case 2:
                        prompts = 0x80;
                        break;
                    }
                    fn_80156E9C(prompts | 1, 1, 1);
                    fn_801569BC();
                }
            } else {
                fn_80156F30();
                pStep->mPrompts = 1;
                fn_80156E9C(1, 1, 1);
            }
            if (fn_80156C8C(pStep->mMask)) {
                fn_80156E9C(pStep->mPrompts, 1, 1);
                fn_80156D1C(1);
                fn_80156D24(pStep->mDuration);
            }
        } else {
            if (fn_80156DC4()) {
                fn_80178370();
            }
            return;
        }
    } else if (step == 4) {
        Class_80297AB8::vfn_04(dt);
        unsigned char done = fn_80156D14();
        if (done != 0) {
            return;
        }
        unsigned char button = fn_80156960();
        pStep = fn_801568F8()->vfn_07();
        unsigned int prompts = pStep->mPrompts;
        if (fn_8013BA58(fn_801374BC(), 0) != 4) {
            if (button != fn_801569B4()) {
                fn_80156E9C(pStep->mPrompts, 0, 0);
                if (++lbl_803EB31C > 1) {
                    lbl_803EB31C = done;
                }
                switch (lbl_803EB31C) {
                case 0:
                    prompts = 0x20;
                    break;
                case 1:
                    prompts = 0x80;
                    break;
                }
                fn_80156E9C(prompts, 1, 0);
                fn_801569BC();
            }
        } else {
            Object_80039F5C *pPlayer = fn_80137B88(fn_801374BC());
            int on = 0;
            if (pPlayer) {
                if (pPlayer->mUnknown8 == 0xFF) {
                    prompts = 0x20;
                } else {
                    on = 1;
                    prompts = 0x41;
                }
                if (button != fn_801569B4()) {
                    fn_80156E9C(prompts, button, on);
                    fn_801569BC();
                }
            } else {
                fn_80156F30();
            }
        }
        if (fn_80156C8C(pStep->mMask)) {
            fn_80156E9C(pStep->mPrompts, 1, 1);
            fn_80156D1C(1);
            fn_80156D24(pStep->mDuration);
        }
    } else {
        Class_802A3AD8::vfn_04(dt);
    }
}

void Class_802A38C8::vfn_03(float dt)
{
    if (fn_801568E8() == 3) {
        fn_801568F8()->vfn_07()->mPrompts = 0xB1;
    } else if (fn_801568E8() == 8) {
        Step_802DEC08 *pStep = fn_801568F8()->vfn_07();
        if (fn_80156C8C(pStep->mMask)) {
            fn_800406C0(0xC0);
        }
    }
    Class_802A3A48::vfn_03(dt);
}

void Lesson_802A3CA8::vfn_01()
{
    mpGame.mp = new (0) Game_80157558;
    fn_800BC51C(&mpGame.mp->mObject0);
    fn_800BFAB4(&mpGame.mp->mObject8);
    fn_800A039C(&mpGame.mp->mObject16);
    fn_800B9598(&mpGame.mp->mObject20);
    fn_80178F20(&mpGame.mp->mObject36);
    fn_801568E8();
}

int Lesson_802A3CA8::vfn_02()
{
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_80178F20(0);
    delete mpGame.mp;
    mpGame.mp = 0;
    return 0;
}

Step_802DEC08 *Lesson_802A3CA8::vfn_07()
{
    return &lbl_802DEDE8[fn_801568E8()];
}

const char *Lesson_802A3CA8::vfn_08()
{
    return "Learn how to be the quarterback and lead your team to victory.";
}

const char *Lesson_802A3CA8::vfn_09()
{
    return "Now that you know how to pass the ball, see how you do in a game of 2 Minute Challenge.";
}

void Lesson_802A3D68::vfn_01()
{
    mpGame.mp = new (0) Game_80157558;
    fn_800BC51C(&mpGame.mp->mObject0);
    fn_800BFAB4(&mpGame.mp->mObject8);
    fn_800A039C(&mpGame.mp->mObject16);
    fn_800B9598(&mpGame.mp->mObject20);
    fn_80178F20(&mpGame.mp->mObject36);
    fn_801568E8();
}

int Lesson_802A3D68::vfn_02()
{
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_80178F20(0);
    delete mpGame.mp;
    mpGame.mp = 0;
    return 0;
}

Step_802DEC08 *Lesson_802A3D68::vfn_07()
{
    return &lbl_802DEF08[fn_801568E8()];
}

const char *Lesson_802A3D68::vfn_08()
{
    return "It's time to learn how to run with the rock.";
}

const char *Lesson_802A3D68::vfn_09()
{
    return "Now that you have some running skills, try a 5 round game of Open Field Showdown.";
}

void Class_802A3820::vfn_04(float dt)
{
    static unsigned int lbl_803EB320 = 0;
    Step_802DEC08 *pStep;

    if (fn_801568E8() == 6) {
        Class_80297AB8::vfn_04(dt);
        unsigned char done = fn_80156D14();
        if (done != 0) {
            return;
        }
        unsigned char button = fn_80156960();
        pStep = fn_801568F8()->vfn_07();
        unsigned int prompts = pStep->mPrompts;
        if (fn_8013BA58(fn_801374BC(), 0) != 4) {
            if (button != fn_801569B4()) {
                fn_80156E9C(pStep->mPrompts, 0, 1);
                if (++lbl_803EB320 > 2) {
                    lbl_803EB320 = done;
                }
                switch (lbl_803EB320) {
                case 0:
                    prompts = 0x20;
                    break;
                case 1:
                    prompts = 0x10;
                    break;
                case 2:
                    prompts = 0x80;
                    break;
                }
                fn_80156E9C(prompts | 1, 1, 1);
                fn_801569BC();
            }
        } else {
            fn_80156F30();
            fn_80156E9C(pStep->mPrompts, 1, 1);
        }
        if (fn_80156C8C(pStep->mMask)) {
            fn_80156E9C(pStep->mPrompts, 1, 1);
            fn_80156D1C(1);
            fn_80156D24(pStep->mDuration);
        }
    } else if (fn_801568E8() == 7) {
        Class_80297AB8::vfn_04(dt);
        unsigned char done = fn_80156D14();
        if (done == 0) {
            unsigned char button = fn_80156960();
            pStep = fn_801568F8()->vfn_07();
            unsigned int prompts = pStep->mPrompts;
            if (fn_8013BA58(fn_801374BC(), 0) != 4) {
                if (button != fn_801569B4()) {
                    fn_80156E9C(pStep->mPrompts, 0, 0);
                    if (++lbl_803EB320 > 2) {
                        lbl_803EB320 = done;
                    }
                    switch (lbl_803EB320) {
                    case 0:
                        prompts = 0x20;
                        break;
                    case 1:
                        prompts = 0x10;
                        break;
                    case 2:
                        prompts = 0x80;
                        break;
                    }
                    fn_80156E9C(prompts, 1, 0);
                    fn_801569BC();
                }
            } else {
                Object_80039F5C *pPlayer = fn_80137B88(fn_801374BC());
                int on = 0;
                if (pPlayer) {
                    if (pPlayer->mUnknown8 == 0xFF) {
                        prompts = 0x20;
                    } else {
                        on = 1;
                        prompts = 0x41;
                    }
                    if (button != fn_801569B4()) {
                        fn_80156E9C(prompts, button, on);
                        fn_801569BC();
                    }
                } else {
                    fn_80156F30();
                }
            }
            if (fn_80156C8C(pStep->mMask)) {
                fn_80156E9C(pStep->mPrompts, 1, 1);
                fn_80156D1C(1);
                fn_80156D24(pStep->mDuration);
            }
        } else {
            if (fn_80156DC4()) {
                fn_80178370();
            }
            return;
        }
    } else {
        Class_802A3AD8::vfn_04(dt);
    }
}

void Lesson_802A3C48::vfn_01()
{
    mpGame.mp = new (0) Game_801582C4;
    fn_800BC51C(&mpGame.mp->mObject0);
    fn_800BFAB4(&mpGame.mp->mObject8);
    fn_800A039C(&mpGame.mp->mObject16);
    fn_800B9598(&mpGame.mp->mObject20);
    fn_80178F20(&mpGame.mp->mObject36);
    fn_801568E8();
}

int Lesson_802A3C48::vfn_02()
{
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_80178F20(0);
    delete mpGame.mp;
    mpGame.mp = 0;
    return 0;
}

Step_802DEC08 *Lesson_802A3C48::vfn_07()
{
    return &lbl_802DEFE8[fn_801568E8()];
}

const char *Lesson_802A3C48::vfn_08()
{
    return "You are going to need to learn to show your Style and earn GameBreakers in order to be great.";
}

const char *Lesson_802A3C48::vfn_09()
{
    return "Showcase your Style in a game of Crush the Carrier. To get the big points, stop Styling before you get tackled.";
}

extern "C" {

void fn_8015844C(int show)
{
    if (show) {
        if (fn_801568F0() == 0) {
            fn_801C2EF0(lbl_8031BFF0, "Running the Ball", 25);
            switch (fn_801568E8()) {
            case 0:
                fn_801C2EF0(lbl_8031C00C, "Turbo", 30);
                break;
            case 1:
                fn_801C2EF0(lbl_8031C00C, "Stiff Arm", 30);
                break;
            case 2:
                fn_801C2EF0(lbl_8031C00C, "Juke", 30);
                break;
            case 3:
                fn_801C2EF0(lbl_8031C00C, "Spin", 30);
                break;
            case 4:
                fn_801C2EF0(lbl_8031C00C, "Hurdle", 30);
                break;
            case 5:
                fn_801C2EF0(lbl_8031C00C, "Dive", 30);
                break;
            case 6:
                fn_801C2EF0(lbl_8031C00C, "Pitch", 30);
                break;
            }
        } else if (fn_801568F0() == 1) {
            fn_801C2EF0(lbl_8031BFF0, "Passing", 25);
            switch (fn_801568E8()) {
            case 0:
                fn_801C2EF0(lbl_8031C00C, "Turbo Roll Out", 30);
                break;
            case 1:
                fn_801C2EF0(lbl_8031C00C, "Touch Pass to B Button", 30);
                break;
            case 2:
                fn_801C2EF0(lbl_8031C00C, "Touch Pass to X Button", 30);
                break;
            case 3:
                fn_801C2EF0(lbl_8031C00C, "Touch Pass to A Button", 30);
                break;
            case 4:
                fn_801C2EF0(lbl_8031C00C, "Bullet Pass to B Button", 30);
                break;
            case 5:
                fn_801C2EF0(lbl_8031C00C, "Bullet Pass to X Button", 30);
                break;
            case 6:
                fn_801C2EF0(lbl_8031C00C, "Bullet Pass to A Button", 30);
                break;
            case 7:
                fn_801C2EF0(lbl_8031C00C, "Pump Fake", 30);
                break;
            case 8:
                fn_801C2EF0(lbl_8031C00C, "Drop Passing Icons", 30);
                break;
            }
        } else if (fn_801568F0() == 2) {
            fn_801C2EF0(lbl_8031BFF0, "Styling", 25);
            switch (fn_801568E8()) {
            case 0:
                fn_801C2EF0(lbl_8031C00C, "Styling", 30);
                break;
            case 1:
                fn_801C2EF0(lbl_8031C00C, "Signature Style", 30);
                break;
            case 2:
                fn_801C2EF0(lbl_8031C00C, "Juke", 30);
                break;
            case 3:
                fn_801C2EF0(lbl_8031C00C, "Spin", 30);
                break;
            case 4:
                fn_801C2EF0(lbl_8031C00C, "Hurdle", 30);
                break;
            case 5:
                fn_801C2EF0(lbl_8031C00C, "Dive", 30);
                break;
            case 6:
                fn_801C2EF0(lbl_8031C00C, "Pass", 30);
                break;
            case 7:
                fn_801C2EF0(lbl_8031C00C, "Catch", 30);
                break;
            }
        } else if (fn_801568F0() == 3) {
            fn_801C2EF0(lbl_8031BFF0, "Defense", 25);
            switch (fn_801568E8()) {
            case 0:
                fn_801C2EF0(lbl_8031C00C, "Turbo", 30);
                break;
            case 1:
                fn_801C2EF0(lbl_8031C00C, "Switch Players", 30);
                break;
            case 2:
                fn_801C2EF0(lbl_8031C00C, "Line Moves", 30);
                break;
            case 3:
                fn_801C2EF0(lbl_8031C00C, "Dive Tackle", 30);
                break;
            case 4:
                fn_801C2EF0(lbl_8031C00C, "Interception", 30);
                break;
            case 5:
                fn_801C2EF0(lbl_8031C00C, "Power Tackle", 30);
                break;
            }
        } else if (fn_801568F0() == 4) {
            fn_801C2EF0(lbl_8031BFF0, "New Stuff", 25);
            switch (fn_801568E8()) {
            case 0:
                fn_801C2EF0(lbl_8031C00C, "Wall Juke", 30);
                break;
            case 1:
                fn_801C2EF0(lbl_8031C00C, "Wall Hurdle", 30);
                break;
            case 2:
                fn_801C2EF0(lbl_8031C00C, "Wall Dive", 30);
                break;
            case 3:
                fn_801C2EF0(lbl_8031C00C, "Wall Pass", 30);
                break;
            case 4:
                fn_801C2EF0(lbl_8031C00C, "Wall Catch", 30);
                break;
            case 5:
                fn_801C2EF0(lbl_8031C00C, "GameBreaker on Offense", 30);
                break;
            case 6:
                fn_801C2EF0(lbl_8031C00C, "GameBreaker on Defense", 30);
                break;
            case 7:
                fn_801C2EF0(lbl_8031C00C, "GameBreaker 2", 30);
                break;
            case 8:
                fn_801C2EF0(lbl_8031C00C, "Hot Spots", 30);
                break;
            }
        }
        lbl_8031BEE4.mUnknown0 = 0;
        lbl_8031BEE4.mpText = lbl_8031BFF0;
        lbl_8031BEE4.mSize = fn_801C3180(lbl_8031BFF0) + 1;
        lbl_803ECA2C = &lbl_8031BEE4;
        lbl_8031BEF0.mUnknown0 = 0;
        lbl_8031BEF0.mpText = lbl_8031C00C;
        lbl_8031BEF0.mSize = fn_801C3180(lbl_8031C00C) + 1;
        lbl_803ECA30 = &lbl_8031BEF0;
        fn_8021D7B8(lbl_803EB688, 0x80000080, 1, &lbl_803ECA2C);
        fn_8021D7B8(lbl_803EB688, 0x80000081, 1, &lbl_803ECA30);
    }
    lbl_803ECA34 = show;
    fn_8021D7B8(lbl_803EB688, 0x8000007F, 1, &lbl_803ECA34);
}

void fn_80158A4C(void)
{
    for (unsigned char team = 0; team <= 1; team++) {
        for (unsigned short i = 0; i <= 6; i++) {
            fn_80149040(fn_80039F5C(team, i));
        }
    }
}

void fn_80158AA8(void)
{
    unsigned char volume;

    if (fn_80072E6C()) {
        fn_80072F04();
    }
    fn_8006EA04(3, 100);
    fn_8006F344(0);
    volume = fn_8007F828(5) * 10;
    fn_8006EA04(2, volume * 40u / 100);
    for (unsigned char team = 0; team <= 1; team++) {
        QueryCursor cursor;
        int a;
        int b;
        cursor.mUnknown0 = 0;
        cursor.mUnknown4 = 0;
        cursor.mUnknown8 = -1;
        cursor.mUnknown12 = 0;
        fn_801FCE10(0, "declare \x8a cursor for select * from 'YALP' where ('DIGT' = \x83) order by 'DIGP'\n", &cursor, team);
        for (unsigned short i = 0; i <= 6; i++) {
            fn_801FCE10(0, "fetch from \x8a 'DIGP' into \x82 and 'DIOP' into \x82\n", &cursor, &a, &b);
        }
        if (cursor.mUnknown0) fn_801FCFA0(&cursor);
    }
}

void fn_80158BB4(unsigned int mask)
{
    unsigned char state = fn_80156960();
    if (state != fn_801569B4()) {
        fn_80156E9C(mask, state, 1);
        fn_801569BC();
    }
}

}

void Class_802A3A48::fn_80158C04()
{
    fn_800655B8();
    Step_802DEC08 *pRecord = fn_801568F8()->vfn_07();
    fn_801801F0(1);
    if (fn_80156C8C(pRecord->mMask)) {
        fn_80156E9C(pRecord->mPrompts, 1, 1);
        fn_80156D1C(1);
    }
    if (fn_80156D14()) {
        if (fn_801569C8(fn_801568F0()) == 0) {
            fn_800544A4("Tutorial Results", lbl_802DF0E8, "|^Done");
            mUnknown12 = 0;
        } else {
            char text[256];
            const char *pName;
            mUnknown4 = 1;
            mUnknown12 = 0;
            pName = fn_801568F8()->vfn_09();
            if (pName == 0) pName = "";
            fn_801C2D88(text, 255, "%s\n\n%s", lbl_802DF140, pName);
            fn_800544A4("Tutorial Results", text, "|^Done");
        }
        mUnknown8.m = 0;
        fn_801566DC(1);
    } else {
        mUnknown12 = 1;
        if (mUnknown8.m > 2) {
            fn_800544A4("Tutorial Results", lbl_802DF100, "|^Retry|Quit|Skip to Next Section");
        } else {
            fn_800544A4("Tutorial Results", lbl_802DF100, "|^Retry|Quit");
        }
    }
}

static unsigned char lbl_803EB324 = 0;
static unsigned char lbl_803EB325 = 0;

void Class_802A3B80::vfn_03()
{
    Class_80297BF8::vfn_03();
    fn_800D7520(1);
    mUnknown4 = 1;
    fn_80158AA8();
    fn_800655B8();
}

void Class_802A3B80::vfn_04(float dt)
{
    unsigned short id;
    unsigned short other;
    int busy;

    fn_80219650(lbl_803EB688, &id, &other);
    busy = 0;
    if (id == 1) {
        busy = other == 2;
    }
    if (!busy && fn_80054568()) {
        int choice = fn_801801D0();

        if (choice == 2) {
            if (mUnknown4 == 2) {
                fn_80194F1C(1);
                fn_80072C90(0xFA, 0);
                fn_800282DC();
            } else {
                mUnknown4 = choice;
                fn_800544A4("Tutorial Results", lbl_802DF120, "|^No|Yes");
            }
        } else {
            Class_80297BF8::vfn_04(dt);
        }
    }
}

void Class_802A3B80::vfn_11(float dt)
{
    fn_800AD910(2, dt);
}

void Class_802A3B80::vfn_06()
{
    char text[256];

    if (fn_801568E8() == 0) {
        const char *pInfo = fn_801568F8()->vfn_08();

        if (pInfo != 0) {
            fn_801574DC(0);
            if (fn_80157550()) {
                fn_801C2E18(text, "%s\n\nDo you want to continue?", pInfo);
                fn_800544A4("Tutorial Information", text, "|^Continue|Quit");
            } else {
                fn_800544A4("Tutorial Information", pInfo, "|^Done");
            }
        }
    } else {
        fn_801574DC(0);
        fn_800544A4("Tutorial Information", "Back for more?", "|^Done");
    }
}

void Class_802A3B80::vfn_07()
{
    fn_801574DC(1);
}

void Class_802A3B10::vfn_04(float dt)
{
    Pair_80177FE0 start;
    Pair_80177FE0 point;
    Vector_80039F5C pos;
    int angles[3];
    int args[2];
    Object_80137ABC *pBall;

    fn_80156C48();
    fn_80156AB0();
    fn_80158A4C();
    fn_8009D8CC(1);
    mUnknown4 = 0;
    fn_80156D24(3);
    lbl_803EB324 = 1;
    start.mX = 0.0f;
    start.mY = fn_80157000();
    if (fn_801566E4()) {
        fn_80067DB8(0x85, 0, fn_801568F0(), fn_801568E8(), 0);
        fn_800731D0(1);
    }
    fn_801780A8(start);
    fn_801782B0();
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
    Class_80297CE8::vfn_04(dt);
    fn_8009E01C();
    fn_800BF658(1);
    fn_800D4164(1, 0.0f, 0);
    fn_800D4164(0, 0.0f, 0);
    fn_8017DE54(1, 0.0f, 0, 0);
    fn_8017DE54(0, 0.0f, 0, 0);
    args[0] = 1;
    args[1] = 0;
    fn_8021D7B8(lbl_803EB688, 0x8000001A, 2, args);
    args[0] = 0;
    fn_8021D7B8(lbl_803EB688, 0x8000001A, 2, args);
    fn_80156E9C(fn_801568F8()->vfn_07()->mPrompts, 1, 0);
    fn_80065814();
    if (!fn_800655F8()) {
        fn_800655D0();
    }
    fn_8015844C(1);
}

void Class_802A3B10::vfn_06(float dt)
{
    fn_8015844C(0);
    Class_80297CE8::vfn_06(dt);
}

void Class_802A3B10::vfn_05(float dt)
{
    if (fn_80156DC4()) {
        Camera_8013F738 *pCamera = fn_8013FA04(5);
        Step_802DEC08 *pEntry = fn_801568F8()->vfn_07();

        if (pCamera->mUnknownA0 == 5 && lbl_803EB324 != 0) {
            fn_800BF6CC(1);
            if (pEntry->mUnknown24 != 1) {
                fn_80156F30();
            } else {
                fn_80156900(pEntry->mUnknown20, 60);
                fn_80156928();
            }
            lbl_803EB324 = 0;
        }
        if (lbl_803EB324 == 0 && pEntry->mUnknown24 == 1) {
            if (fn_80156C8C(0x400000000ULL)) {
                fn_80156F30();
            } else {
                fn_80158BB4(pEntry->mPrompts);
            }
        }
        if (mUnknown4 == 0 && fn_80074638()) {
            fn_8009D888(0, 5);
            fn_8009D944(0);
            mUnknown4 = 1;
        }
        Class_80297CE8::vfn_05(dt);
    }
}

int Class_802A3B10::vfn_12()
{
    int result = 0;

    if (mUnknown4 != 0 && (unsigned int)fn_8009D990(0) <= 2) {
        result = Class_80297CE8::vfn_12();
    }
    return result;
}

void Class_802A3AD8::vfn_03()
{
    Step_802DEC08 *pEntry;

    Class_80297AB8::vfn_03();
    fn_80156D1C(0);
    fn_8013C6F0(fn_8013FA04(5));
    pEntry = fn_801568F8()->vfn_07();
    if (pEntry->mUnknown24 != 1) {
        fn_80156900(pEntry->mUnknown20, 60);
        fn_80156928();
    } else {
        fn_80156F30();
    }
}

void Class_802A3AD8::vfn_04(float dt)
{
    Class_80297AB8::vfn_04(dt);
    if (fn_80156D14() == 0) {
        Step_802DEC08 *pEntry = fn_801568F8()->vfn_07();

        if (pEntry->mUnknown24 != 1) {
            fn_80158BB4(pEntry->mPrompts);
        }
        if (fn_80156C8C(pEntry->mMask)) {
            fn_80156E9C(pEntry->mPrompts, 1, 1);
            fn_80156D1C(1);
            fn_80156D24(pEntry->mDuration);
        }
    } else if (fn_80156DC4()) {
        fn_80178370();
    }
}

void Class_802A3A48::vfn_03(float dt)
{
    Step_802DEC08 *pEntry = fn_801568F8()->vfn_07();

    mUnknown5 = 0;
    mUnknown6 = pEntry->mUnknown12 * 60.0f;
    mUnknown4 = 0;
    mUnknown12 = 0;
    Class_80297C60::vfn_03(dt);
    fn_80156F30();
}

void Class_802A3A48::vfn_04(float dt)
{
    unsigned short id;
    unsigned short other;

    if (mUnknown5 == 0) {
        if (mUnknown6 > 0) {
            if (mUnknown6 == 2) {
                if (fn_80156D14()) {
                    fn_80067DB8(0x86, 0, 0, 0, 0);
                } else {
                    fn_80067DB8(0x87, 0, 0, 0, 0);
                }
                mUnknown6--;
            } else if (mUnknown6 == 1) {
                if (fn_80074638() || !fn_80156D14()) {
                    mUnknown6--;
                    lbl_803EB325 = 0;
                }
            } else {
                mUnknown6--;
            }
        } else {
            fn_80194F1C(0);
            fn_80194CBC();
            fn_8006F824(1);
            fn_80158C04();
            mUnknown5 = 1;
        }
    } else {
        int key = fn_800B81A4();

        if (key != 0xFF || lbl_803EB325 != 0) {
            if (lbl_803EB325 == 0) {
                int args[2];

                args[0] = key;
                args[1] = 1;
                lbl_803EB325 = 1;
                fn_80218FC4(lbl_803EB688, 1, 2, 2, args);
                fn_802195E4(lbl_803EB688, 1, 2);
            } else {
                int busy = 0;

                fn_80219650(lbl_803EB688, &id, &other);
                if (id == 1) {
                    busy = other == 2;
                }
                if (!busy) {
                    fn_802195E4(lbl_803EB688, 1, 3);
                    lbl_803EB325 = 0;
                }
            }
        } else if (fn_80054568()) {
            if (mUnknown12 != 0) {
                switch (fn_801801D0()) {
                case 1:
                    mUnknown8.m++;
                    fn_801566DC(0);
                    mUnknown12 = 0;
                    fn_80194F1C(1);
                    vfn_15();
                    break;
                case 2:
                    if (mUnknown12 == 1) {
                        mUnknown12 = 2;
                        fn_800544A4("Tutorial Results", lbl_802DF120, "|^No|Yes");
                    } else {
                        fn_80194F1C(1);
                        fn_80072C90(0xFA, 0);
                        fn_80047874(0);
                        fn_8004730C(0);
                        fn_800282DC();
                        mUnknown12 = 0;
                    }
                    break;
                case 3:
                    fn_80067DB8(0x88, 0, 0, 0, 0);
                    mUnknown8.m = 0;
                    fn_801566DC(1);
                    if (!fn_801569C8(fn_801568F0())) {
                        mUnknown12 = 0;
                    } else {
                        char text[256];
                        const char *pInfo;

                        mUnknown12 = 0;
                        mUnknown4 = 1;
                        pInfo = fn_801568F8()->vfn_09();
                        if (pInfo == 0) {
                            pInfo = "";
                        }
                        fn_801C2D88(text, 0xFF, "%s\n\n%s", lbl_802DF140, pInfo);
                        fn_800544A4("Tutorial Results", text, "|^Done");
                    }
                    break;
                }
                fn_800D6F08();
            }
            Class_80297C60::vfn_04(dt);
        }
    }
}

void Class_802A3A48::vfn_06()
{
}

void Class_802A3A48::vfn_05()
{
    Object_80137ABC *pBall;
    Pair_80177FE0 point;
    Vector_80039F5C pos;
    int angles[3];

    Class_80297C60::vfn_05();
    fn_8011DF90();
    if (fn_80137B40()) {
        fn_8013791C(fn_801374BC(), 5, 0);
    }
    if (fn_801784E8()) {
        fn_80177E6C(1, 1);
    }
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
    fn_8013F97C(0);
    fn_8013FA58(1, fn_801374D4());
}

void Class_802A3A48::vfn_07()
{
}

void Class_802A3A48::vfn_10()
{
}

int Class_802A3A48::vfn_11()
{
    fn_800AE988();
    return 0;
}

int Class_802A3A48::vfn_12()
{
    fn_8009B924();
    return 0;
}

void Class_802A3A48::vfn_14(float dt)
{
    fn_8003A450();
    if (fn_8005BFD4() != 4) {
        fn_8005BF18();
    }
    if (mUnknown4 != 0) {
        if (!fn_80157080()) {
            fn_80072C90(0xFA, 0);
            fn_800282DC();
        }
    } else {
        fn_800AD910(2, dt);
    }
}

void Class_802A3990::vfn_11(int a)
{
    Class_802A56E8::vfn_11(a);
}

int Class_802A3990::vfn_12()
{
    return 1;
}

void Class_802A3990::vfn_10()
{
    fn_80177F88(1);
    Class_802A56E8::vfn_10();
    if (fn_80177F70() == 6) {
        fn_801787FC(1, 0);
        fn_801787FC(0, 0);
        fn_800C87CC(1, 0);
        fn_800C87CC(0, 0);
        fn_80177F88(1);
        fn_8017D6B8(1, 0);
        fn_8017D6B8(0, 0);
    }
    fn_80178CD8(0);
}

int Class_802A3990::vfn_02()
{
    return 2;
}

int Class_802A3990::vfn_08()
{
    return 0;
}
