#include "game/Block_80307980.h"
#include "game/Class_8002373C.h"
#include "game/Class_802938C0.h"
#include "game/FMCAPPORT.h"
#include "game/Object_8003DEC4.h"
#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/cu_80047E28.h"
#include "game/cu_80181330.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801C3284.h"
#include "game/fn_801FCE10.h"

/* Range of one face feature: its values start at mOffset in the
   lbl_8036A170 slot mSlot, and the menu shows mCount of them. */
struct Range_800093E0 {
    int mOffset;
    int mCount;
    int mSlot;
};

/* Per-row record of the table at 0x80369E64: a key (mKey, -1 when the
   slot is free) and twelve values indexed by attribute (-1 when unset). */
struct Entry_80369E64 {
    int mKey;
    int mValues[12];
};

void *operator new(unsigned int size, int unknown);

extern "C" {
void fn_800225F4(int index, unsigned int value);
void fn_80022680(int index, int a, int b);
void fn_80022760(int index, unsigned int value);
void fn_80022D6C(void);
int fn_80022D78(void);
int fn_80022D80(void);
void fn_80022D88(void);
void fn_800230D8();
void fn_800230F8();
void fn_800232C8(Object_8007A334 *pObject);
void fn_8002333C(Object_8007A334 *pObject);
void fn_8002335C(Object_8007A334 *pCursor, int value, int *pResult);
void fn_80023394(Object_8007A334 *pCursor, char *pBuffer, int size);
int fn_800233C8(Object_8007A334 *pCursor);
void fn_800233F0(Object_8007A334 *pCursor, int type);
void fn_80023498(Object_8007A334 *pCursor);
void fn_800234B8(Object_8007A334 *pCursor, char *pBuffer, int size);
int fn_800234EC(Object_8007A334 *pCursor);
void fn_80048F6C(int index, const char *pName);
void fn_8007A098(int index, char *pBuffer, int size);
int fn_8007A43C(Object_8007A334 *pObject);
void fn_8007CC50(Object_8007A334 *pObject);
void fn_8007CCC4(Object_8007A334 *pObject);
void fn_8007CD1C(Object_8007A334 *pObject, char *pBuffer, int size);
int fn_8007CD50(Object_8007A334 *pObject);
int fn_800808F8(Object_8008044C *pObject);
int fn_80080920(Object_8008044C *pObject);
void fn_80080A34(Object_8008044C *pObject, char *pBuffer, int size);
void fn_80080A68(Object_8008044C *pObject, int a, int b);
void fn_80080A9C(Object_8008044C *pObject, char *pBuffer, int size);
int fn_80080CD8(Object_8008044C *pObject);
int fn_80080D10(Object_8008044C *pObject);
int fn_80080E48(Object_8008044C *pObject);
int fn_80080E70(Object_8008044C *pObject);
int fn_80080E98(Object_8008044C *pObject);
void fn_80080EF4(Object_8008044C *pObject, int value);
int fn_80080F20(void *pObject);
int fn_80080F48(void *pObject, int index);
void fn_80080F78(void *pObject, int value);
void fn_80080FA4(void *pObject, int index, int value);
void fn_80080FD4(Object_8008044C *pObject, int value);
void fn_80081000(Object_8008044C *pObject, int value);
void fn_8008105C(Object_8008044C *pObject, int value);
void fn_80081088(Object_8008044C *pObject, int value);
void fn_800810B4(Object_8008044C *pObject, int value);
int fn_800810E0(Object_8008044C *pObject);
void fn_80081108(Object_8008044C *pObject, int value);
int fn_80081134(Object_8008044C *pObject);
void fn_8008115C(Object_8008044C *pObject, int value);
int fn_80081188(Object_8008044C *pObject);
void fn_800811B4(Object_8008044C *pObject, int value);
int fn_80081208(Object_8008044C *pObject);
void fn_80081230(Object_8008044C *pObject, int value);
int fn_8008125C(Object_8008044C *pObject);
void fn_80081284(Object_8008044C *pObject, int value);
int fn_800812B0(Object_8008044C *pObject, int index);
void fn_8008135C(Object_8008044C *pObject, int index, int value);
void fn_8008199C(Object_8008044C *pObject, Info_80307908 *pInfo);
int fn_80081E3C(Object_8008044C *pObject);
void fn_80081E64(Object_8008044C *pObject, char *pBuffer, int size);
void fn_80081E98(Object_8008044C *pObject, char *pBuffer, int size);
int fn_80082280(Object_8008044C *pObject);
void fn_800822A8(Object_8008044C *pObject, int value);
int fn_800822D4(Object_8008044C *pObject);
void fn_80082308(Object_8008044C *pObject, int value);
int fn_80087938(int table, Object_8007A334 *pObject, int index, int *pResult);
int fn_800879E8(int table, Object_8007A334 *pObject);
void fn_80087A30(int table, Object_8007A334 *pObject);
int fn_80087A78(int table, Object_8007A334 *pObject, int value, int *pIndex);
int fn_80087B00(int table, Object_8007A334 *pObject);
int fn_80087B5C(int type);
void fn_8015D180(int a, int b);
void fn_8015D224(int index);
void fn_8015D38C(int a);
void fn_8015F638(int a, int b, int c, int *pResult);
int fn_8016128C(int a);
void fn_8016139C(int a, int *pId, int *pPalette);
void fn_80180FA4(const char *pText);
Object_8007A334 *fn_80182DBC(void);
Object_8008044C *fn_80182DC8(void);
void fn_80182DD4(const char *pText);
void fn_80182E04(const char *pText);
void fn_80182E34(char *pText);
void fn_80182E64(int a);
void fn_80182E70(int a);
void fn_80182E7C(int a);
void fn_80182ED0(void);
void fn_80182EFC(void);
void fn_80182F60(int index, int delta);
void fn_80182FD4(int a, unsigned char value);
void fn_8018300C(void);
void fn_801831F0(unsigned char a);
int fn_80183220(void);
int fn_80183228(void);
int fn_80183230(void);
int fn_80183238(int index);
void fn_801832B0(char *pText, int size);
void fn_801835C0(int a);
void fn_801835C8(void);
void fn_80183704(void);
int fn_80183948(void);
int fn_80183950(void);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);

int fn_80008914(void);
}

class Class_8000DBA0;

void fn_8000CEB4(int a);
void fn_8000CF24();
Class_8000DBA0 *fn_8000CF5C();

extern const Entry_80182CC8 lbl_80008F10[];
extern const Entry_80182CC8 lbl_80008FC0[];
extern const Entry_80182CC8 lbl_800090F4[];
extern const Entry_80182CC8 lbl_80009178[];
extern const Entry_80182CC8 lbl_80009254[];
extern const Range_800093E0 lbl_800093E0[];
extern const Entry_80182CC8 lbl_8000944C[];
extern const int lbl_800094FC[];
extern const Entry_80182CC8 lbl_8000950C[];
extern const Entry_80182CC8 lbl_800098D0[];

static unsigned short lbl_802F400C[21] = {
    0, 5, 5, 5, 10, 10, 15, 20, 25, 30, 35, 45, 60, 75, 100, 175, 300, 450, 650, 900, 1000,
};
static unsigned short lbl_802F4036[6] = { 15, 20, 25, 75, 150, 250 };
static unsigned short lbl_802F4042[11] = { 1, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5 };

/* Top level of the create-a-player menu. */
const Entry_80182CC8 lbl_80008F10[] = {
    { 0, 0, "Attributes", 1, 2 },
    { 1, 0, "Info", 1 },
    { 2, 0, "Appearance", 1 },
    { 3, 0, "Gear", 1, 14 },
};

const Entry_80182CC8 lbl_80008FC0[] = {
    { 0, 5, "First Name", 1, 12 },
    { 1, 5, "Last Name", 1, 24 },
    { 2, 0, "Position", 1, 29 },
    { 3, 0, "Jersey Number", 1, 23 },
    { 4, 0, "Handedness", 1 },
    { 5, 0, "Celebration", 1, 28 },
    { 6, 0, "Signature Style", 1, 37 },
};

const Entry_80182CC8 lbl_800090F4[] = {
    { 0, 0, "Hair", 1 },
    { 1, 0, "Face", 1 },
    { 2, 0, "Skin", 1 },
};

const Entry_80182CC8 lbl_80009178[] = {
    { 0, 0, "Hair Style", 1 },
    { 1, 0, "Hair Color", 1 },
    { 2, 0, "Facial Hair Style", 1 },
    { 3, 0, "Facial Hair Color", 1 },
    { 4, 0, "Eyebrows", 1 },
};

const Entry_80182CC8 lbl_80009254[] = {
    { 0, 0, "Head Shape", 1 },
    { 1, 0, "Brow", 1 },
    { 2, 0, "Eyes", 1 },
    { 3, 0, "Ears", 1 },
    { 4, 0, "Nose", 1 },
    { 5, 0, "Lips", 1 },
    { 6, 0, "Mouth", 1 },
    { 7, 0, "Jaw & Chin", 1 },
    { 8, 0, "Expression", 1 },
};

const Range_800093E0 lbl_800093E0[] = {
    { 0, 7, 3 },
    { 0, 8, 1 },
    { 48, 24, 7 },
    { 8, 6, 2 },
    { 72, 33, 8 },
    { 30, 4, 5 },
    { 21, 9, 4 },
    { 34, 14, 6 },
    { -1, -1, -1 },
};

const Entry_80182CC8 lbl_8000944C[] = {
    { 0, 0, "Skin Tone", 1 },
    { 1, 0, "Back Tattoo", 1 },
    { 2, 0, "Left Arm Tattoo", 1 },
    { 3, 0, "Right Arm Tattoo", 1 },
};

/* fn_800233F0 table type of each Class_80009DC8 entry; 3 is the skin tone. */
const int lbl_800094FC[] = { 3, 2, 1, 0 };

const Entry_80182CC8 lbl_8000950C[] = {
    { 0, 2, "Passing", 1, 27 },
    { 1, 2, "Speed", 1, 44 },
    { 2, 2, "Blocking", 1, 4 },
    { 3, 2, "O-Moves", 1, 1 },
    { 4, 2, "Catching", 1, 7 },
    { 5, 2, "Run Power", 1, 32 },
    { 6, 2, "Jumping", 1, 6 },
    { 7, 2, "Tackling", 1, 45 },
    { 8, 2, "Coverage", 1, 8 },
    { 9, 2, "D-Moves", 1, 9 },
    { 10, 2, "Height", 1, 22 },
    { 11, 2, "Weight", 1, 54 },
};

/* Help line of each attribute. */
static const char *lbl_802F4058[] = {
    "Increases throwing power and accuracy.",
    "Makes player faster.",
    "Increases ability to block effectively.",
    "Improves ability to juke, spin and use the walls.",
    "Helps player catch the ball.",
    "Improves ability to break tackles.",
    "Improves ability to make jumping catches.",
    "Makes tackling more effective.",
    "Improves ability to cover receivers.",
    "Increases ability to shed blocks effectively.",
    "Makes player taller.",
    "Makes player heavier.",
};

const Entry_80182CC8 lbl_800098D0[] = {
    { 0, 0, "Style+Up", 1, 41 },
    { 1, 0, "Style+Right", 1, 40 },
    { 2, 0, "Style+Down", 1, 38 },
    { 3, 0, "Style+Left", 1, 39 },
};

static const char *lbl_802F4088[] = { "Athlete", "Rap", "Rock" };
static int lbl_802F4094[] = { 2, 1, 3 };
static const char *lbl_802F40A0[] = {
    "Lid", "Big Fathead", "Fathead", "Pill", "Big Pinhead", "Pinhead", "Meatball",
};
static const char *lbl_802F40BC[] = { "Crazed", "Determined", "Growl", "Pensive", "Smirk" };
static unsigned short lbl_803EB910[] = { 1, 10, 13 };
static const char *lbl_803EB918[] = { "Right", "Left" };
static const char *lbl_802F40D0[] = { "QB", "RB", "WR", "OL", "DL", "LB", "DB" };
static int lbl_802F40EC[7] = { 0, 1, 2, 4, 7, 9, 11 };

/* Value stored to lbl_803EB938 for each result of fn_80080ECC. */
static int lbl_802F4108[] = { 0, 1, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6 };

/* Top-level entry states while fn_80183950 reports set / clear. */
static const unsigned char lbl_803ED6D0[] = { 0, 0, 0, 1 };
static const unsigned char lbl_803ED6D4[] = { 0, 0, 0, 1 };

static const Layout_802EA9E0 lbl_8000A148[] = {
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 1 },
    { 23.0f, 975.0f, 0.0f, 338.0f, 3.1f, 15, 0 },
    { 23.0f, 975.0f, 0.0f, 338.0f, 3.1f, 15, 0 },
};

static const Layout_802EA9E0 lbl_8000A19C[] = {
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 1 },
    { 0.0f, 300.0f, 0.0f, 180.0f, 1.1f, 15, 0 },
    { 0.0f, 205.0f, 0.0f, 300.0f, 0.8f, 15, 0 },
    { 0.0f, 205.0f, 0.0f, 60.0f, 0.8f, 15, 0 },
};

/* Presets applied by fn_800089E0: one value for each of the twelve
   attributes. */
static const short lbl_8000A20C[7][12] = {
    { 50, 25, 1, 25, 1, 15, 15, 10, 5, 1, 65, 160 },
    { 10, 35, 1, 35, 25, 25, 5, 10, 1, 1, 65, 160 },
    { 1, 50, 1, 25, 35, 1, 25, 10, 1, 1, 65, 160 },
    { 1, 15, 50, 1, 1, 25, 1, 15, 1, 10, 65, 220 },
    { 1, 15, 10, 1, 1, 25, 1, 15, 1, 50, 65, 220 },
    { 1, 25, 1, 10, 10, 15, 10, 50, 10, 15, 65, 160 },
    { 1, 35, 1, 15, 15, 1, 15, 15, 50, 1, 65, 160 },
};

static int lbl_803EB920 = 0;
static int lbl_803EB924 = 0;
static int lbl_803EB928 = 0x7FFF;
static unsigned char lbl_803EB92C = 0;
static unsigned char lbl_803EB92D = 0;
static int lbl_803EB930 = 0;
static unsigned char lbl_803EB934 = 0;
static int lbl_803EB938 = 15;

/* Player list. */
class Class_8000A108 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pValue);
    virtual int vfn_02(int a, int b, void **ppResult);
    virtual void vfn_03(int index);
    virtual void vfn_04(int index, int *pId);
    virtual void vfn_05(int index, Entry_80182CC8 *pEntry);

    char mUnknown4[4];
};

/* Top-level menu of the selected player. */
class Class_8000A0B8 : public Class_802A6B60 {
public:
    virtual void vfn_01(int a, int *pCount, int *pValue);
    virtual int vfn_02(int a, int b, void **ppResult);
    virtual void vfn_03(int id);
    virtual void vfn_05(int index, Entry_80182CC8 *pEntry);
    virtual int vfn_07() { return 4; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_80008F10; }

    char mUnknown4[4];
};

class Class_8000A068 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **ppResult);
    virtual Class_802A6BB0 *vfn_06();
    virtual int vfn_07() { return 7; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_80008FC0; }

    char mUnknown4[4];
};

class Class_8000A018 : public Class_802A6B60 {
public:
    virtual void vfn_01(int a, int *pCount, int *pValue);
    virtual int vfn_02(int a, int b, void **ppResult);
    virtual void vfn_03(int id);
    virtual int vfn_07() { return 3; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_800090F4; }

    char mUnknown4[4];
};

class Class_80009FC8 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **ppResult);
    virtual int vfn_07() { return 5; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_80009178; }

    char mUnknown4[4];
};

class Class_80009F78 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **ppResult);
    virtual int vfn_07() { return 9; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_80009254; }

    const Range_800093E0 *GetRange(int feature) { return &lbl_800093E0[feature]; }

    char mUnknown4[4];
};

class Class_80009F28 : public Class_802A6B60 {
public:
    virtual void vfn_01(int a, int *pCount, int *pValue);
    virtual int vfn_02(int a, int b, void **ppResult);
    virtual int vfn_07() { return 4; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_8000944C; }

    char mUnknown4[4];
};

class Class_80009ED8 : public Class_802A6B60 {
public:
    virtual void vfn_01(int a, int *pCount, int *pValue);
    virtual int vfn_02(int a, int b, void **ppResult);
    virtual void vfn_03(int id);
    virtual Class_802A6BB0 *vfn_06();
    virtual int vfn_07() { return 12; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_8000950C; }

    char mUnknown4[4];
};

class Class_80009E88 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **ppResult);
    virtual int vfn_07() { return 4; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_800098D0; }

    char mUnknown4[4];
};

class Class_80009E48 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pOut);
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_03(int index);
    virtual void vfn_04(int index, int *pOut) { *pOut = index; }
    virtual void vfn_05(int index, Entry_80182CC8 *pOut);

    char mUnknown4[4];
    int mUnknown8;
};

class Class_80009E08 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pOut);
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_03(int index);
    virtual void vfn_04(int index, int *pOut) { *pOut = index; }
    virtual void vfn_05(int index, Entry_80182CC8 *pOut);

    char mUnknown4[4];
    int mUnknown8;
    Class_8002373C *mUnknown12;
};

class Class_80009DC8 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pOut);
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_03(int index);
    virtual void vfn_04(int index, int *pOut) { *pOut = index; }
    virtual void vfn_05(int index, Entry_80182CC8 *pOut);

    char mUnknown4[4];
    int mUnknown8;
};

class Class_80009D88 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pOut);
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_03(int index);
    virtual void vfn_04(int index, int *pOut) { *pOut = index; }
    virtual void vfn_05(int index, Entry_80182CC8 *pOut);

    char mUnknown4[4];
    int mUnknown8;
};

class Class_80009D28 : public Class_802A6BB0 {
public:
    virtual void vfn_09(int a, int *pResult, Arg_8018399C text);
    virtual void vfn_10(int a, Arg_8018399C text);

    char mUnknown4[4];
};

class Class_80009CC8 : public Class_802A6BB0 {
public:
    virtual void vfn_06(int a, int b, int c, int *pD, int *pE, Arg_8018399C textF, Arg_8018399C textG,
                        Arg_8018399C textH);
    virtual int vfn_07(int a, int b, Arg_8018399C text);
    virtual void vfn_08(int a, int b, int c);

    char mUnknown4[4];
};

class Class_80009C88 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pOut);
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_03(int index);
    virtual void vfn_04(int index, int *pOut) { *pOut = index; }
    virtual void vfn_05(int index, Entry_80182CC8 *pOut);

    char mUnknown4[4];
    int mUnknown8;
};

static inline Class_80009CC8 *fn_80008C0C();
static inline Class_80009C88 *fn_80008C34();
static inline Class_8000A0B8 *fn_80008C64();
static inline Class_8000A068 *fn_80008C8C();
static inline Class_8000A018 *fn_80008CB4();
static inline Class_80009ED8 *fn_80008CDC();
static inline Class_80009E88 *fn_80008D04();
static inline Class_80009D88 *fn_80008D2C();
static inline Class_80009D28 *fn_80008D5C();
static inline Class_80009E48 *fn_80008D84();
static inline Class_80009E08 *fn_80008DB4();
static inline Class_80009DC8 *fn_80008DE4();
static inline Class_80009FC8 *fn_80008E14();
static inline Class_80009F78 *fn_80008E3C();
static inline Class_80009F28 *fn_80008E64();
static inline Class_8000A108 *fn_80008E8C();

static void fn_80008750(int key, int index, int value);
static void fn_800087BC();
static void fn_80008860();
static void fn_800088E8(int value);
static int fn_80008978(int key, int index);

static Object_8007A334 lbl_80369DDC;
static Object_8007A334 lbl_80369E08;
static Class_802938C0 lbl_80369E34;
static Entry_80369E64 lbl_80369E64[15];
static Block_80307980 lbl_8036A170;
static unsigned short lbl_8036A198[21];
static int lbl_803ECD5C;

static int fn_80005668()
{
    int mode = fn_80183948();

    return mode == 0 || mode == 3;
}

static void fn_800056A4(int position, int skill)
{
    int i;
    int loaded = 0;

    if (lbl_803EB934) {
        loaded = fn_801FCE10(0,
                       "select '10VL' into \x84 and '20VL' into \x84 and '30VL' into \x84 and '40VL' into \x84 and "
                       "'50VL' into \x84 and '60VL' into \x84 and '70VL' into \x84 and '80VL' into \x84 and "
                       "'90VL' into \x84 and '01VL' into \x84 and '11VL' into \x84 and '21VL' into \x84 and "
                       "'31VL' into \x84 and '41VL' into \x84 and '51VL' into \x84 and '61VL' into \x84 and "
                       "'71VL' into \x84 and '81VL' into \x84 and '91VL' into \x84 and '02VL' into \x84 "
                       "from 'CLKS' where 'SOPB' = \x85 and 'DIKS' = \x85\n",
                       &lbl_8036A198[1], &lbl_8036A198[2], &lbl_8036A198[3], &lbl_8036A198[4],
                       &lbl_8036A198[5], &lbl_8036A198[6], &lbl_8036A198[7], &lbl_8036A198[8],
                       &lbl_8036A198[9], &lbl_8036A198[10], &lbl_8036A198[11], &lbl_8036A198[12],
                       &lbl_8036A198[13], &lbl_8036A198[14], &lbl_8036A198[15], &lbl_8036A198[16],
                       &lbl_8036A198[17], &lbl_8036A198[18], &lbl_8036A198[19], &lbl_8036A198[20],
                       position, skill) == 0;
    }
    if (!loaded) {
        for (i = 0; i < 21; i++) {
            lbl_8036A198[i] = lbl_802F400C[i];
        }
    }
}

static int fn_800057C0(int value)
{
    int i;

    switch (value) {
    case 3:
        value = 2;
        break;
    case 5:
    case 6:
        value = 4;
        break;
    case 8:
        value = 7;
        break;
    case 10:
        value = 9;
        break;
    case 12:
    case 13:
        value = 11;
        break;
    }
    for (i = 0; i < 7; i++) {
        if (lbl_802F40EC[i] == value) {
            break;
        }
    }
    return i;
}

static int fn_80005868(int index)
{
    return lbl_802F40EC[index];
}

static unsigned short fn_8000587C(int index)
{
    return lbl_8036A198[index];
}

static int fn_80005890(int from, int to)
{
    int total = 0;
    int i = from / 5;
    int end = to / 5;

    while (i < end) {
        total += fn_8000587C(i + 1);
        i++;
    }
    return total;
}

static int fn_80005904(int from, int to)
{
    int sign = 1;
    int total = 0;
    int i;

    if (from > to) {
        sign = from;
        from = to;
        to = sign;
        sign = -1;
    }
    for (i = from; i < to; i++) {
        int index = (i - 65) * 6 / 19;
        total += lbl_802F4036[index];
    }
    return total * sign;
}

static int fn_80005980(int from, int to)
{
    int sign = 1;
    int total = 0;
    int i;

    if (from > to) {
        sign = from;
        from = to;
        to = sign;
        sign = -1;
    }
    for (i = from; i < to; i++) {
        int index = (i - 160) / 20;
        total += lbl_802F4042[index];
    }
    return total * sign;
}

static unsigned int fn_800059EC(int value, int *pTable, unsigned int count)
{
    unsigned int i;

    for (i = 0; i < count; i++) {
        if (pTable[i] == value) {
            break;
        }
    }
    return i;
}

static void fn_80005A24(int id)
{
    Object_8008044C object;
    Block_80307980 block;
    FMCAPPORTValues values;
    FMCAPPORTText text60;
    FMCAPPORTText text20;
    int ids[2];
    int unknown52;
    int unknown56;
    int entryId;
    int value6E;
    int value6C;
    int value72;
    int value73;
    int value74;
    int value76;
    int unknown8;
    int unknown12;
    unsigned int color18;
    unsigned int color19;

    fn_8008044C(&object, 0, 0x54415453);
    fn_800809C4(&object, id, 0);
    entryId = fn_80080D10(&object);
    value6E = fn_80080E98(&object);
    value6C = fn_80080E70(&object);
    value72 = fn_80081E3C(&object);
    value73 = fn_80082280(&object);
    value74 = fn_800822D4(&object);
    value76 = fn_80080E48(&object);
    color18 = fn_800810E0(&object);
    color19 = fn_80081134(&object);
    fn_80082138(&object, &block);
    fn_80046804(&block, &values);
    fn_8015F638(value6E, value6C, 0, ids);
    fn_8016139C(value6E, &unknown52, &unknown56);
    unknown8 = fn_8016128C(value72 + 1);
    unknown12 = value73 * 3 + value74 + 0x33BA;
    fn_801C1F94(&text60, 0, sizeof(text60));
    fn_801C1F94(&text20, 0, sizeof(text20));
    text60.mChars[18] = color18 + 0x80;
    text20.mChars[19] = color19 + 0x80;
    gFMCAPPORT.SetEntry(entryId, 0xFFFF, unknown8, unknown12, 0xA7, &text20, ids[0], unknown52, unknown56, &text60,
                        &values, value76);
    fn_8008056C(&object);
}

static void fn_80005BE4(int index, int value)
{
    int flag;

    lbl_8036A170.mUnknown0[index] = value;
    if (index == 3) {
        fn_80049B78(0, lbl_8036A170.mUnknown0[index]);
        fn_80049B78(1, lbl_8036A170.mUnknown0[index]);
    }
    fn_80046804(&lbl_8036A170, &fn_8003DEC4(0)->mUnknown4976);
    fn_80046804(&lbl_8036A170, &fn_8003DEC4(1)->mUnknown4976);
    fn_80049F10(0, &lbl_8036A170);
    fn_80049F10(1, &lbl_8036A170);
    flag = fn_80046898(&lbl_8036A170);
    fn_80049BD8(0, flag);
    fn_80049BD8(1, flag);
    fn_8015D180(fn_80022D78(), 15);
    fn_80022D6C();
}

static void fn_80005CAC(int value)
{
    int flag;

    fn_80049B48(0, value);
    fn_80049B48(1, value);
    lbl_80369E34.fn_801900D4(value, 0);
    lbl_8036A170.mUnknown0[0] = lbl_80369E34.fn_801901A4();
    fn_80046804(&lbl_8036A170, &fn_8003DEC4(0)->mUnknown4976);
    fn_80046804(&lbl_8036A170, &fn_8003DEC4(1)->mUnknown4976);
    fn_80049F10(0, &lbl_8036A170);
    fn_80049F10(1, &lbl_8036A170);
    flag = fn_80046898(&lbl_8036A170);
    fn_80049BD8(0, flag);
    fn_80049BD8(1, flag);
    fn_8015D180(fn_80022D78(), 15);
    fn_80022D6C();
}

static int fn_80005D88(unsigned int value)
{
    int mode = 2;

    if (value > 294) {
        mode = 0;
    } else if (value > 229) {
        mode = 1;
    } else if (value > 199) {
        mode = 3;
    }
    if (lbl_803ECD5C != mode) {
        lbl_803ECD5C = mode;
        lbl_8036A170.mUnknown0[9] = mode;
        fn_80049BA8(1, mode);
        fn_80049BA8(0, mode);
        fn_80046804(&lbl_8036A170, &fn_8003DEC4(0)->mUnknown4976);
        fn_80046804(&lbl_8036A170, &fn_8003DEC4(1)->mUnknown4976);
        fn_80049F10(0, &lbl_8036A170);
        fn_80049F10(1, &lbl_8036A170);
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
    }
    return mode;
}

static void fn_80005E64(int value)
{
    fn_80049B90(0, value);
    fn_80049B90(1, value);
    fn_8015D180(fn_80022D78(), 15);
    fn_80022D6C();
}

static unsigned char fn_80005EB4(Info_80307908 *pInfo, int part)
{
    switch (part) {
    case 1:
        return pInfo->mUnknown05;
    case 0:
        return pInfo->mUnknown04;
    case 2:
        return pInfo->mUnknown08;
    }
    return pInfo->mUnknown05;
}

static void fn_80005EF8(Info_80307908 *pInfo, int part, unsigned char value)
{
    switch (part) {
    case 1:
        pInfo->mUnknown05 = value;
        break;
    case 0:
        pInfo->mUnknown04 = value;
        break;
    case 2:
        pInfo->mUnknown08 = value;
        break;
    }
}

void Class_80009ED8::vfn_01(int a, int *pCount, int *pValue)
{
    Class_802A6B60::vfn_01(a, pCount, pValue);
    fn_801831F0(1);
}

int Class_80009ED8::vfn_02(int a, int b, void **ppResult)
{
    int result = Class_802A6B60::vfn_02(a, b, ppResult);

    fn_801831F0(0);
    fn_80180FA4("");
    return result;
}

void Class_80009ED8::vfn_03(int id)
{
    Class_802A6B60::vfn_03(id);
    fn_80180FA4(lbl_802F4058[id]);
    if (id >= 0 && id <= 9) {
        fn_800056A4(lbl_803EB938, id);
    }
}

Class_802A6BB0 *Class_80009ED8::vfn_06()
{
    return fn_80008C0C();
}

int Class_80009E88::vfn_02(int a, int b, void **ppResult)
{
    int result = Class_802A6B60::vfn_02(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 0:
        case 1:
        case 2:
        case 3:
            fn_80008C34()->mUnknown8 = a;
            result = 1;
            *ppResult = fn_80008C34();
            break;
        }
    }
    return result;
}

void Class_8000A108::vfn_01(int a, int *pCount, int *pValue)
{
    char buffer[18];
    int index;

    if (a == 1) {
        fn_800087BC();
    }
    fn_80083F88(fn_80182DBC(), buffer, 18);
    fn_80182E34(buffer);
    fn_80182DD4("");
    fn_80182E04("");
    *pCount = fn_8007A410((Object_8007A334 *)fn_80182DC8());
    if (fn_80005668()) {
        (*pCount)++;
    }
    index = *pValue;
    if (fn_80005668()) {
        index--;
    }
    if (index >= 0) {
        fn_8007A600((Object_8007A334 *)fn_80182DC8(), index);
        int id = fn_800808F8(fn_80182DC8());

        if (lbl_803EB928 != id || a == 1) {
            if (lbl_803EB928 != 0x7FFF) {
                fn_800809C4(fn_80182DC8(), lbl_803EB928, pValue);
            } else {
                lbl_803EB928 = id;
            }
            fn_80022680(fn_80022D80(), lbl_803EB928, 1);
        }
    } else {
        lbl_803EB928 = 0x7FFF;
    }
}

int Class_8000A108::vfn_02(int a, int b, void **ppResult)
{
    int result = 1;

    if (b != 0) {
        result = -1;
        fn_80008860();
    } else {
        char buffer[27];

        *ppResult = fn_80008C64();
        fn_800809C4(fn_80182DC8(), a, 0);
        fn_801832B0(buffer, 27);
        fn_80182E34(buffer);
    }
    return result;
}

void Class_8000A108::vfn_03(int index)
{
    if (index != 0x7FFF) {
        char buffer[27];
        int position;

        fn_800809C4(fn_80182DC8(), index, 0);
        fn_80022680(fn_80022D80(), index, 0);
        lbl_803EB928 = index;
        position = fn_80080ECC(fn_80182DC8());
        lbl_803EB938 = lbl_802F4108[position];
        fn_80182E64(position);
        fn_80182E70(fn_800811E0(fn_80182DC8()));
        fn_80182E7C(fn_80081188(fn_80182DC8()));
        fn_801832B0(buffer, 27);
        fn_80182DD4(buffer);
        fn_80182ED0();
        fn_80082138(fn_80182DC8(), &lbl_8036A170);
    } else {
        lbl_803EB928 = index;
        if (fn_80005668()) {
            fn_80182DD4("Continue");
        }
        fn_80182EFC();
        fn_80182E64(0xFF);
        fn_80182E70(-1);
        fn_80182E7C(-1);
        fn_8015D224(fn_80022D80());
    }
    fn_80183740(0);
}

void Class_8000A108::vfn_04(int index, int *pId)
{
    if (fn_80005668()) {
        index--;
    }
    if (index >= 0) {
        fn_8007A600((Object_8007A334 *)fn_80182DC8(), index);
        *pId = fn_800808F8(fn_80182DC8());
    } else {
        *pId = 0x7FFF;
    }
}

void Class_8000A108::vfn_05(int index, Entry_80182CC8 *pEntry)
{
    char buffer[27] = { 0 };

    pEntry->mUnknown40 = 0;
    if (index != 0x7FFF) {
        int value;

        fn_800809C4(fn_80182DC8(), index, 0);
        if (fn_80183950() && index == 0) {
            pEntry->mUnknown41 = 1;
        }
        value = fn_80080D10(fn_80182DC8());
        pEntry->mUnknown36 = fn_8007A43C((Object_8007A334 *)fn_80182DC8());
        if (fn_80005668()) {
            pEntry->mUnknown36++;
        }
        pEntry->mId = index;
        pEntry->mUnknown30 = fn_80080CD8(fn_80182DC8()) == 0;
        pEntry->mUnknown4 = 0;
        pEntry->mUnknown32 = value | 0xA0000;
        fn_801832B0(buffer, 27);
        fn_801C3284(pEntry->mName, buffer, 22);
    } else {
        pEntry->mId = index;
        pEntry->mUnknown36 = 0;
        pEntry->mUnknown30 = 1;
        pEntry->mUnknown32 = 0xC0000;
        if (fn_80005668()) {
            pEntry->mUnknown4 = 8;
            fn_801C3284(pEntry->mName, "Continue", 22);
        }
    }
    fn_80022D88();
}

void Class_8000A0B8::vfn_01(int a, int *pCount, int *pValue)
{
    Class_802A6B60::vfn_01(a, pCount, pValue);
    if (fn_80080920(fn_80182DC8()) != 0x7FFF) {
        *pValue = 3;
    }
    fn_80022680(fn_80022D78(), lbl_803EB928, 1);
    fn_8015D38C(0);
    if (lbl_803EB92C) {
        fn_8000CF24();
        lbl_803EB92C = 0;
    }
}

int Class_8000A0B8::vfn_02(int a, int b, void **ppResult)
{
    int result = Class_802A6B60::vfn_02(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 1:
            *ppResult = fn_80008C8C();
            result = 1;
            break;
        case 2:
            *ppResult = fn_80008CB4();
            result = 1;
            break;
        case 0:
            *ppResult = fn_80008CDC();
            result = 1;
            break;
        case 3:
            fn_8000CEB4(1);
            lbl_803EB92C = 1;
            result = 1;
            *ppResult = fn_8000CF5C();
            break;
        }
    } else {
        fn_8015D38C(1);
    }
    return result;
}

void Class_8000A0B8::vfn_03(int id)
{
    fn_80182DD4(lbl_80008F10[id].mName);
}

void Class_8000A0B8::vfn_05(int index, Entry_80182CC8 *pEntry)
{
    Class_802A6B60::vfn_05(index, pEntry);
    if (fn_80183950()) {
        if (fn_800808F8(fn_80182DC8()) != 0) {
            pEntry->mUnknown30 = lbl_803ED6D4[index];
            return;
        }
    } else if (fn_80080920(fn_80182DC8()) != 0x7FFF) {
        pEntry->mUnknown30 = lbl_803ED6D0[index];
        return;
    }
    pEntry->mUnknown30 = lbl_80008F10[index].mUnknown30;
}

int Class_8000A068::vfn_02(int a, int b, void **ppResult)
{
    int result = Class_802A6B60::vfn_02(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 6:
            *ppResult = fn_80008D04();
            result = 1;
            break;
        case 2:
        case 3:
        case 4:
        case 5:
            fn_80008D2C()->mUnknown8 = a;
            result = 1;
            *ppResult = fn_80008D2C();
            break;
        }
    }
    return result;
}

Class_802A6BB0 *Class_8000A068::vfn_06()
{
    return fn_80008D5C();
}

int Class_80009FC8::vfn_02(int a, int b, void **ppResult)
{
    int result = Class_802A6B60::vfn_02(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            fn_80008D84()->mUnknown8 = a;
            result = 1;
            *ppResult = fn_80008D84();
            break;
        }
    }
    return result;
}

int Class_80009F78::vfn_02(int a, int b, void **ppResult)
{
    int result = Class_802A6B60::vfn_02(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            fn_80008DB4()->mUnknown8 = a;
            result = 1;
            *ppResult = fn_80008DB4();
            break;
        }
    }
    return result;
}

void Class_80009F28::vfn_01(int a, int *pCount, int *pValue)
{
    Class_802A6B60::vfn_01(a, pCount, pValue);
    fn_80183740(0);
}

int Class_80009F28::vfn_02(int a, int b, void **ppResult)
{
    int result = Class_802A6B60::vfn_02(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 0:
        case 1:
        case 2:
        case 3:
            fn_80008DE4()->mUnknown8 = a;
            result = 1;
            *ppResult = fn_80008DE4();
            break;
        }
        switch (a) {
        case 0:
            fn_80183740(&lbl_8000A19C[0]);
            break;
        case 1:
            fn_80183740(&lbl_8000A19C[1]);
            break;
        case 2:
            fn_80183740(&lbl_8000A19C[2]);
            break;
        case 3:
            fn_80183740(&lbl_8000A19C[3]);
            break;
        }
    }
    return result;
}

void Class_8000A018::vfn_01(int a, int *pCount, int *pValue)
{
    Class_802A6B60::vfn_01(a, pCount, pValue);
    fn_80183740(0);
}

int Class_8000A018::vfn_02(int a, int b, void **ppResult)
{
    int result = Class_802A6B60::vfn_02(a, b, ppResult);

    if (b == 0) {
        switch (a) {
        case 0:
            result = 1;
            fn_80183740(&lbl_8000A148[1]);
            *ppResult = fn_80008E14();
            break;
        case 1:
            result = 1;
            fn_80183740(&lbl_8000A148[2]);
            *ppResult = fn_80008E3C();
            break;
        case 2:
            *ppResult = fn_80008E64();
            result = 1;
            break;
        }
    } else {
        fn_80005A24(lbl_803EB928);
    }
    return result;
}

void Class_8000A018::vfn_03(int id)
{
    Class_802A6B60::vfn_03(id);
}

void Class_80009D88::vfn_01(int a, int *pCount, int *pOut)
{
    switch (mUnknown8) {
    case 2:
        *pOut = fn_800057C0(fn_80080ECC(fn_80182DC8()));
        *pCount = 7;
        break;
    case 5:
        *pOut = fn_800059EC(fn_80080F20(fn_80182DC8()), lbl_802F4094, 3);
        *pCount = 3;
        break;
    case 3:
        *pOut = fn_8008125C(fn_80182DC8());
        *pCount = 100;
        break;
    case 4:
        *pOut = fn_80081208(fn_80182DC8());
        *pCount = 2;
        break;
    }
}

int Class_80009D88::vfn_02(int a, int b, void **pOut)
{
    fn_80183740(0);
    if (b == 0) {
        switch (mUnknown8) {
        case 2:
            fn_80080EF4(fn_80182DC8(), fn_80005868(a));
            fn_80182E64(fn_80005868(a));
            break;
        case 3:
            fn_80081284(fn_80182DC8(), a);
            break;
        case 5:
            fn_80080F78(fn_80182DC8(), lbl_802F4094[a]);
            break;
        case 4:
            fn_80081230(fn_80182DC8(), a);
            break;
        }
    } else if (mUnknown8 == 3) {
        fn_80049BF0(0, fn_8008125C(fn_80182DC8()));
        fn_80049BF0(1, fn_8008125C(fn_80182DC8()));
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
    }
    return -1;
}

void Class_80009D88::vfn_03(int index)
{
    switch (mUnknown8) {
    case 2:
        break;
    case 3:
        fn_80049BF0(0, index);
        fn_80049BF0(1, index);
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
        break;
    case 4:
        break;
    case 5:
        fn_800225F4(0, lbl_803EB910[index]);
        fn_800225F4(1, lbl_803EB910[index]);
        break;
    }
}

void Class_80009D88::vfn_05(int index, Entry_80182CC8 *pOut)
{
    switch (mUnknown8) {
    case 2:
        fn_801C3284(pOut->mName, lbl_802F40D0[index], 22);
        break;
    case 3:
        fn_801C2D88(pOut->mName, 22, "%02d", index);
        break;
    case 5:
        fn_801C3284(pOut->mName, lbl_802F4088[index], 22);
        break;
    case 4:
        fn_801C3284(pOut->mName, lbl_803EB918[index], 22);
        break;
    }
}

void Class_80009D28::vfn_09(int a, int *pResult, Arg_8018399C text)
{
    Params_80005284 *pParams = text.pParams;
    char buffer[16];
    char buffer2[16];

    switch (a) {
    case 0:
        *pResult = 1;
        fn_80080A34(fn_80182DC8(), buffer, 12);
        fn_801C3284(pParams->mpText, buffer, pParams->mLength + 1);
        break;
    case 1:
        *pResult = 2;
        fn_80080A68(fn_80182DC8(), (int)buffer2, 15);
        fn_801C3284(pParams->mpText, buffer2, pParams->mLength + 1);
        break;
    }
}

void Class_80009D28::vfn_10(int a, Arg_8018399C text)
{
    Params_80005284 *pParams = text.pParams;
    char buffer[16];
    char label[27];
    char label2[27];
    char name[32];

    switch (a) {
    case 0:
        fn_801C3284(buffer, pParams->mpText, 12);
        fn_80081E64(fn_80182DC8(), buffer, 12);
        fn_801832B0(label, 27);
        fn_80182E34(label);
        fn_800809C4(fn_80182DC8(), lbl_803EB928, 0);
        break;
    case 1:
        fn_801C3284(buffer, pParams->mpText, 15);
        fn_80081E98(fn_80182DC8(), buffer, 15);
        fn_801832B0(label2, 27);
        fn_80182E34(label2);
        fn_800809C4(fn_80182DC8(), lbl_803EB928, 0);
        fn_80080A9C(fn_80182DC8(), name, 31);
        fn_80048F6C(0, name);
        fn_80048F6C(1, name);
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
        break;
    }
    fn_800225F4(0, 24);
    fn_800225F4(1, 24);
}

void Class_80009E48::vfn_01(int a, int *pCount, int *pOut)
{
    lbl_80369E34.fn_80190098();
    switch (mUnknown8) {
    case 0:
        fn_80087A78(0x12, &lbl_80369DDC, fn_80080E98(fn_80182DC8()), pOut);
        *pCount = fn_80087B00(0x12, &lbl_80369DDC);
        break;
    case 1:
        *pOut = fn_800810E0(fn_80182DC8());
        *pCount = 12;
        break;
    case 2:
        lbl_80369E34.fn_801900D4(fn_80082280(fn_80182DC8()), pOut);
        *pCount = lbl_80369E34.fn_8018FE34();
        break;
    case 3:
        *pOut = fn_80081134(fn_80182DC8());
        *pCount = 12;
        break;
    case 4:
        *pOut = fn_800822D4(fn_80182DC8());
        *pCount = 3;
        break;
    }
}

int Class_80009E48::vfn_02(int a, int b, void **pOut)
{
    if (b == 0) {
        switch (mUnknown8) {
        case 0:
            fn_80087938(0x12, &lbl_80369DDC, a, 0);
            fn_80087A30(0x12, &lbl_80369DDC);
            fn_80080FD4(fn_80182DC8(), fn_8007CD50(&lbl_80369DDC));
            break;
        case 1:
            fn_800810B4(fn_80182DC8(), a);
            break;
        case 2:
            lbl_80369E34.fn_8018FF0C(a);
            fn_800822A8(fn_80182DC8(), lbl_80369E34.fn_80190120());
            fn_800225F4(0, 26);
            fn_800225F4(1, 26);
            break;
        case 3:
            fn_80081108(fn_80182DC8(), a);
            fn_800225F4(0, 26);
            fn_800225F4(1, 26);
            break;
        case 4:
            fn_80082308(fn_80182DC8(), a);
            break;
        }
    } else {
        switch (mUnknown8) {
        case 0:
            fn_80005E64(fn_80080E98(fn_80182DC8()));
            break;
        case 1:
            fn_80049D34(0, fn_800810E0(fn_80182DC8()));
            fn_80049D34(1, fn_800810E0(fn_80182DC8()));
            fn_8015D180(fn_80022D78(), 15);
            fn_80022D6C();
            break;
        case 2:
            fn_80005CAC(fn_80082280(fn_80182DC8()));
            break;
        case 3:
            fn_80049D50(0, fn_80081134(fn_80182DC8()));
            fn_80049D50(1, fn_80081134(fn_80182DC8()));
            fn_8015D180(fn_80022D78(), 15);
            fn_80022D6C();
            break;
        case 4:
            fn_80049B60(0, fn_800822D4(fn_80182DC8()));
            fn_80049B60(1, fn_800822D4(fn_80182DC8()));
            fn_8015D180(fn_80022D78(), 15);
            fn_80022D6C();
            break;
        }
    }
    lbl_80369E34.fn_8018FE10();
    return -1;
}

void Class_80009E48::vfn_03(int index)
{
    switch (mUnknown8) {
    case 0:
        fn_80087938(0x12, &lbl_80369DDC, index, 0);
        fn_80005E64(fn_8007CD50(&lbl_80369DDC));
        break;
    case 1:
        fn_80049D34(0, index);
        fn_80049D34(1, index);
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
        break;
    case 2:
        lbl_80369E34.fn_8018FF0C(index);
        fn_80005CAC(lbl_80369E34.fn_80190120());
        break;
    case 3:
        fn_80049D50(0, index);
        fn_80049D50(1, index);
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
        break;
    case 4:
        fn_80049B60(0, index);
        fn_80049B60(1, index);
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
        break;
    }
}

void Class_80009E48::vfn_05(int index, Entry_80182CC8 *pOut)
{
    char name[32];

    switch (mUnknown8) {
    case 0:
        fn_80087938(0x12, &lbl_80369DDC, index, 0);
        pOut->mUnknown40 = fn_800879E8(0x12, &lbl_80369DDC);
        fn_8007CD1C(&lbl_80369DDC, name, 26);
        fn_801C3284(pOut->mName, name, 22);
        break;
    case 1:
    case 3:
        fn_8007A098(index, name, 21);
        fn_801C3284(pOut->mName, name, 22);
        break;
    case 2:
        lbl_80369E34.fn_8018FF0C(index);
        lbl_80369E34.fn_8019015C(name, 21);
        fn_801C3284(pOut->mName, name, 22);
        break;
    case 4:
        fn_801C2D88(pOut->mName, 22, "EyeBrow %d", index + 1);
        break;
    }
}

void Class_80009E08::vfn_01(int a, int *pCount, int *pOut)
{
    mUnknown12 = new (0) Class_8002373C;
    if (mUnknown8 == 8) {
        *pOut = fn_80080E48(fn_80182DC8());
        *pCount = 5;
    } else {
        const Range_800093E0 *pRange = fn_80008E3C()->GetRange(mUnknown8);

        *pOut = lbl_8036A170.mUnknown0[pRange->mSlot] - pRange->mOffset;
        *pCount = pRange->mCount;
    }
}

int Class_80009E08::vfn_02(int a, int b, void **pOut)
{
    if (b == 0) {
        if (mUnknown8 == 8) {
            fn_80081088(fn_80182DC8(), a);
        } else {
            const Range_800093E0 *pRange = fn_80008E3C()->GetRange(mUnknown8);

            lbl_8036A170.mUnknown0[pRange->mSlot] = a + pRange->mOffset;
            fn_80082334(fn_80182DC8(), &lbl_8036A170);
            fn_80049F10(0, &lbl_8036A170);
            fn_80049F10(1, &lbl_8036A170);
        }
    } else {
        if (mUnknown8 == 8) {
            fn_80049C20(0, fn_80080E48(fn_80182DC8()));
            fn_80049C20(1, fn_80080E48(fn_80182DC8()));
            fn_8015D180(fn_80022D78(), 15);
            fn_80022D6C();
        } else {
            fn_80082138(fn_80182DC8(), &lbl_8036A170);
            fn_80049F10(0, &lbl_8036A170);
            fn_80049F10(1, &lbl_8036A170);
            int slot = fn_80008E3C()->GetRange(mUnknown8)->mSlot;

            fn_80005BE4(slot, lbl_8036A170.mUnknown0[slot]);
        }
    }
    delete mUnknown12;
    return -1;
}

void Class_80009E08::vfn_03(int index)
{
    if (mUnknown8 == 8) {
        fn_80049C20(0, index);
        fn_80049C20(1, index);
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
    } else {
        const Range_800093E0 *pRange = fn_80008E3C()->GetRange(mUnknown8);

        fn_80005BE4(pRange->mSlot, index + pRange->mOffset);
    }
}

void Class_80009E08::vfn_05(int index, Entry_80182CC8 *pOut)
{
    char name[32];

    if (mUnknown8 == 8) {
        fn_801C3284(pOut->mName, lbl_802F40BC[index], 22);
    } else {
        const Range_800093E0 *pRange = fn_80008E3C()->GetRange(mUnknown8);

        if (mUnknown8 == 0) {
            fn_801C3284(pOut->mName, lbl_802F40A0[index + pRange->mOffset], 22);
        } else {
            mUnknown12->fn_80023820(index + pRange->mOffset, (int)name, 31);
            fn_801C3284(pOut->mName, name, 22);
        }
    }
}

void Class_80009DC8::vfn_01(int a, int *pCount, int *pOut)
{
    int type = lbl_800094FC[mUnknown8];

    if (type == 3) {
        *pCount = 12;
        *pOut = fn_80081E3C(fn_80182DC8());
    } else {
        Object_8007A334 cursor;
        Info_80307908 info;
        int key;

        fn_800817CC(fn_80182DC8(), &info);
        fn_800233F0(&cursor, type);
        key = fn_80087B5C(type);
        fn_80087A78(key, &cursor, fn_80005EB4(&info, type), pOut);
        *pCount = fn_80087B00(fn_80087B5C(type), &cursor);
        fn_80023498(&cursor);
    }
}

int Class_80009DC8::vfn_02(int a, int b, void **pOut)
{
    Info_80307908 info;

    fn_800817CC(fn_80182DC8(), &info);
    int type = lbl_800094FC[mUnknown8];

    if (b == 0) {
        if (type == 3) {
            fn_8008105C(fn_80182DC8(), a);
        } else {
            Object_8007A334 cursor;

            fn_800233F0(&cursor, type);
            fn_80087938(fn_80087B5C(type), &cursor, a, 0);
            fn_80087A30(fn_80087B5C(type), &cursor);
            fn_80005EF8(&info, type, fn_800234EC(&cursor));
            fn_80023498(&cursor);
            fn_8008199C(fn_80182DC8(), &info);
        }
    } else {
        if (type == 3) {
            fn_80049B30(0, fn_80081E3C(fn_80182DC8()) + 1);
            fn_80049B30(1, fn_80081E3C(fn_80182DC8()) + 1);
            fn_8015D180(fn_80022D78(), 15);
            fn_80022D6C();
        } else {
            fn_80049D6C(0, type, fn_80005EB4(&info, type));
            fn_80049D6C(1, type, fn_80005EB4(&info, type));
            fn_8015D180(fn_80022D78(), 15);
            fn_80022D6C();
        }
    }
    return -1;
}

void Class_80009DC8::vfn_03(int index)
{
    int type = lbl_800094FC[mUnknown8];

    if (type == 3) {
        fn_80049B30(0, index + 1);
        fn_80049B30(1, index + 1);
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
    } else {
        Object_8007A334 cursor;
        int value;

        fn_800233F0(&cursor, type);
        fn_80087938(fn_80087B5C(type), &cursor, index, 0);
        value = fn_800234EC(&cursor);
        fn_80023498(&cursor);
        fn_80049D6C(0, type, value);
        fn_80049D6C(1, type, value);
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
    }
}

void Class_80009DC8::vfn_05(int index, Entry_80182CC8 *pOut)
{
    int type = lbl_800094FC[mUnknown8];

    if (type == 3) {
        fn_801C2D88(pOut->mName, 22, "Skin Tone %d", index + 1);
    } else {
        Object_8007A334 cursor;

        fn_800233F0(&cursor, type);
        fn_80087938(fn_80087B5C(type), &cursor, index, 0);
        pOut->mUnknown40 = fn_800879E8(fn_80087B5C(type), &cursor);
        fn_800234B8(&cursor, pOut->mName, 22);
        fn_800234EC(&cursor);
        fn_80023498(&cursor);
    }
}

void Class_80009C88::vfn_01(int a, int *pCount, int *pOut)
{
    fn_8002335C(&lbl_80369E08, fn_80080F48(fn_80182DC8(), mUnknown8), pOut);
    *pCount = fn_8007A410(&lbl_80369E08);
}

int Class_80009C88::vfn_02(int a, int b, void **pOut)
{
    fn_80183740(0);
    if (b == 0) {
        fn_8007A600(&lbl_80369E08, a);
        fn_80080FA4(fn_80182DC8(), mUnknown8, fn_800233C8(&lbl_80369E08));
    }
    return -1;
}

void Class_80009C88::vfn_03(int index)
{
    fn_8007A600(&lbl_80369E08, index);
    fn_800225F4(0, (unsigned short)(fn_800233C8(&lbl_80369E08) + 31));
    fn_800225F4(1, (unsigned short)(fn_800233C8(&lbl_80369E08) + 31));
}

void Class_80009C88::vfn_05(int index, Entry_80182CC8 *pOut)
{
    fn_8007A600(&lbl_80369E08, index);
    fn_80023394(&lbl_80369E08, pOut->mName, 22);
}

void Class_80009CC8::vfn_06(int a, int b, int c, int *pD, int *pE, Arg_8018399C textF, Arg_8018399C textG,
                            Arg_8018399C textH)
{
    Params_80005284 *pLeft = textF.pParams;
    Params_80005284 *pRight = textG.pParams;
    Params_80005284 *pValue = textH.pParams;
    int *pMin = (int *)b;
    int *pMax = (int *)c;

    lbl_803EB924 = 0;
    fn_801C2D88(pValue->mpText, pValue->mLength, "");
    fn_80183740(0);
    lbl_803EB92D = 1;
    switch (a) {
    case 10:
        *pMin = 65;
        *pMax = 84;
        *pE = fn_800811E0(fn_80182DC8());
        fn_80008750(fn_800808F8(fn_80182DC8()), 10, *pE);
        *pD = fn_80008978(fn_800808F8(fn_80182DC8()), 10);
        fn_801C2D88(pLeft->mpText, pLeft->mLength, "Shorter");
        fn_801C2D88(pRight->mpText, pRight->mLength, "Taller");
        fn_801C2D88(pValue->mpText, pValue->mLength, "%d ft %d in", *pE / 12, *pE % 12);
        if (*pE < 84) {
            lbl_803EB930 = fn_80005904(*pE, *pE + 1);
        } else {
            lbl_803EB930 = 0;
        }
        break;
    case 11:
        *pMin = 160;
        *pMax = 380;
        *pE = fn_80081188(fn_80182DC8());
        fn_80008750(fn_800808F8(fn_80182DC8()), 11, *pE);
        *pD = fn_80008978(fn_800808F8(fn_80182DC8()), 11);
        lbl_803ECD5C = fn_80080E20(fn_80182DC8());
        fn_801C2D88(pLeft->mpText, pLeft->mLength, "Lighter");
        fn_801C2D88(pRight->mpText, pRight->mLength, "Heavier");
        fn_801C2D88(pValue->mpText, pValue->mLength, "%d lbs", *pE);
        if (*pE < 380) {
            lbl_803EB930 = fn_80005980(*pE, *pE + 1);
        } else {
            lbl_803EB930 = 0;
        }
        break;
    default: {
        int level;

        *pMin = 0;
        *pMax = 20;
        level = fn_800812B0(fn_80182DC8(), fn_80183238(a));
        *pE = level / 5;
        if (level < 100) {
            if (level == 1) {
                lbl_803EB930 = fn_80005890(1, 5);
            } else {
                lbl_803EB930 = fn_80005890(level, level + 5);
            }
        } else {
            lbl_803EB930 = 0;
        }
        fn_80008750(fn_800808F8(fn_80182DC8()), a, *pE);
        *pD = fn_80008978(fn_800808F8(fn_80182DC8()), a);
        fn_801C2D88(pLeft->mpText, pLeft->mLength, "Worse");
        fn_801C2D88(pRight->mpText, pRight->mLength, "Better");
        fn_801C2D88(pValue->mpText, pValue->mLength, "Level %d", *pE);
        fn_80182FD4(fn_80183238(a), 1);
        break;
    }
    }
}

int Class_80009CC8::vfn_07(int a, int b, Arg_8018399C text)
{
    Params_80005284 *pParams = text.pParams;
    int result = 0;
    int cost;

    fn_801C2D88(pParams->mpText, pParams->mLength, "");
    switch (a) {
    case 10:
        if (b >= 65 && b <= 84 && b >= fn_80183230()) {
            cost = fn_80005904(fn_80183228(), b);

            if (cost <= fn_80008914()) {
                if (b > fn_80183220()) {
                    fn_800225F4(0, 6);
                    fn_800225F4(1, 6);
                } else if (b < fn_80183220()) {
                    fn_800225F4(0, 5);
                    fn_800225F4(1, 5);
                }
                fn_80022760(0, b);
                result = 1;
                fn_80022760(1, b);
                lbl_803EB924 = cost;
                if (b < 84) {
                    lbl_803EB930 = fn_80005904(b, b + 1);
                } else {
                    lbl_803EB930 = 0;
                }
            }
        }
        if (!result) {
            b = fn_80183220();
        }
        fn_801C2D88(pParams->mpText, pParams->mLength, "%d ft %d in", b / 12, b % 12);
        fn_80182E70(b);
        break;
    case 11:
        if (b >= 160 && b <= 380 && b >= fn_80183230()) {
            cost = fn_80005980(fn_80183228(), b);

            if (cost <= fn_80008914()) {
                fn_800225F4(0, 3);
                result = 1;
                fn_800225F4(1, 3);
                fn_80005D88(b);
                lbl_803EB924 = cost;
                if (b < 380) {
                    lbl_803EB930 = fn_80005980(b, b + 1);
                } else {
                    lbl_803EB930 = 0;
                }
            }
        }
        if (!result) {
            b = fn_80183220();
        }
        fn_801C2D88(pParams->mpText, pParams->mLength, "%d lbs", b);
        fn_80182E7C(b);
        break;
    default: {
        int level = b * 5;
        int previous;

        if (level == 0) {
            level = 1;
        }
        previous = fn_80183228() * 5;
        if (previous == 0) {
            previous = 1;
        }
        if (level >= 1 && level <= 100 && b >= fn_80183230()) {
            if (b > fn_80183228()) {
                cost = fn_80005890(previous, level);
            } else {
                cost = -fn_80005890(level, previous);
            }
            if (cost <= fn_80008914()) {
                result = 1;
                fn_80182F60(fn_80183238(a), level);
                lbl_803EB924 = cost;
                if (level < 100) {
                    if (level == 1) {
                        lbl_803EB930 = fn_80005890(1, 5);
                    } else {
                        lbl_803EB930 = fn_80005890(level, level + 5);
                    }
                } else {
                    lbl_803EB930 = 0;
                }
            }
        }
        if (!result) {
            b = fn_80183220();
        }
        fn_801C2D88(pParams->mpText, pParams->mLength, "Level %d", b);
        break;
    }
    }
    return result;
}

void Class_80009CC8::vfn_08(int a, int b, int c)
{
    int played = 0;

    lbl_803EB92D = 0;
    if (b == 0) {
        switch (a) {
        case 10:
            fn_80008914();
            fn_800088E8(lbl_803EB924);
            fn_80022760(0, c);
            fn_80022760(1, c);
            fn_800811B4(fn_80182DC8(), c);
            if (c == 84) {
                fn_800225F4(0, 22);
                played = 1;
                fn_800225F4(1, 22);
            } else if (c >= 79 && c <= 83) {
                fn_800225F4(0, 23);
                played = 1;
                fn_800225F4(1, 23);
            }
            break;
        case 11: {
            int build;

            fn_80008914();
            fn_800088E8(lbl_803EB924);
            build = fn_80005D88(c);
            fn_80081000(fn_80182DC8(), build);
            fn_8008115C(fn_80182DC8(), c);
            if (c > 379) {
                fn_800225F4(0, 21);
                played = 1;
                fn_800225F4(1, 21);
            } else if (c > 294) {
                fn_800225F4(0, 28);
                played = 1;
                fn_800225F4(1, 28);
            } else if (c > 229) {
                fn_800225F4(0, 27);
                played = 1;
                fn_800225F4(1, 27);
            }
            break;
        }
        default: {
            float fraction = c * 0.05f;
            unsigned int value = fn_800812B0(fn_80182DC8(), fn_80183238(a));
            int level;

            if (fraction > value * 0.01f) {
                if (fraction >= 0.5 && fraction < 0.75) {
                    fn_800225F4(0, 17);
                    played = 1;
                    fn_800225F4(1, 17);
                } else if (fraction >= 0.75 && fraction <= 0.99) {
                    fn_800225F4(0, 18);
                    played = 1;
                    fn_800225F4(1, 18);
                } else if (fraction == 1.0) {
                    fn_800225F4(0, 19);
                    played = 1;
                    fn_800225F4(1, 19);
                }
            }
            fn_80008914();
            fn_800088E8(lbl_803EB924);
            level = c * 5;
            if (level == 0) {
                level = 1;
            }
            fn_8008135C(fn_80182DC8(), fn_80183238(a), level);
            break;
        }
        }
    } else {
        switch (a) {
        case 10:
            fn_80022760(0, fn_800811E0(fn_80182DC8()));
            fn_80022760(1, fn_800811E0(fn_80182DC8()));
            break;
        case 11:
            fn_80005D88(fn_80081188(fn_80182DC8()));
            break;
        default: {
            int index = fn_80183238(a);

            fn_80182F60(index, fn_800812B0(fn_80182DC8(), index));
            break;
        }
        }
        fn_800225F4(0, 20);
        played = 1;
        fn_800225F4(1, 20);
    }
    fn_80182E70(fn_800811E0(fn_80182DC8()));
    fn_80182E7C(fn_80081188(fn_80182DC8()));
    fn_8018300C();
    lbl_803EB924 = 0;
    if (!played) {
        fn_80183740(0);
    }
}

static void fn_80008750(int key, int index, int value)
{
    signed char i;

    for (i = 0; i <= 14; i++) {
        if (lbl_80369E64[i].mKey != -1) {
            if (lbl_80369E64[i].mKey == key) {
                if (lbl_80369E64[i].mValues[index] == -1) {
                    lbl_80369E64[i].mValues[index] = value;
                }
                return;
            }
        } else {
            lbl_80369E64[i].mKey = key;
            lbl_80369E64[i].mValues[index] = value;
            return;
        }
    }
}

static void fn_800087BC()
{
    fn_801835C0(0x71);
    lbl_803EB928 = 0x7FFF;
    fn_801835C8();
    fn_800230D8();
    fn_8007CC50(&lbl_80369DDC);
    fn_800232C8(&lbl_80369E08);
    fn_8007A444((Object_8007A334 *)fn_80182DC8());
    if (fn_80183950()) {
        if (fn_80183948() != 3) {
            lbl_803EB928 = 0;
        }
        if (fn_8022EF8C(0, 0x434C4B53) == 0) {
            lbl_803EB934 = 1;
            lbl_8036A198[0] = 0;
            lbl_803EB938 = 15;
        }
    }
}

static void fn_80008860()
{
    fn_80183704();
    fn_800230F8();
    fn_8007CCC4(&lbl_80369DDC);
    fn_8002333C(&lbl_80369E08);
    if (lbl_803EB934) {
        fn_8022EFBC(0, 0x434C4B53);
        lbl_803EB934 = 0;
    }
    lbl_803EB928 = 0x7FFF;
}

extern "C" Class_80184190 *fn_800088C8(void)
{
    return fn_80008E8C();
}

static void fn_800088E8(int value)
{
    if (lbl_803EB920 >= value) {
        lbl_803EB920 -= value;
    } else {
        lbl_803EB920 = 0;
    }
}

extern "C" void fn_8000890C(int value)
{
    lbl_803EB920 = value;
}

extern "C" int fn_80008914(void)
{
    return lbl_803EB920;
}

extern "C" int fn_8000891C(void)
{
    return lbl_803EB924;
}

extern "C" void fn_80008924(void)
{
    unsigned char i;
    unsigned char j;

    for (i = 0; i <= 14; i++) {
        lbl_80369E64[i].mKey = -1;
        for (j = 0; j <= 11; j++) {
            lbl_80369E64[i].mValues[j] = -1;
        }
    }
}

static int fn_80008978(int key, int index)
{
    signed char i;

    for (i = 0; i <= 14; i++) {
        if (lbl_80369E64[i].mKey == key) {
            return lbl_80369E64[i].mValues[index];
        }
    }
    return -1;
}

extern "C" int fn_800089C0(void)
{
    if (!lbl_803EB92D) {
        return 0;
    }
    return lbl_803EB930;
}

extern "C" int fn_800089D8(void)
{
    return lbl_803EB928;
}

extern "C" void fn_800089E0(int a)
{
    int i;
    int value = fn_80005868(a);

    fn_80080EF4(fn_80182DC8(), value);
    for (i = 0; i <= 11; i++) {
        switch (i) {
        case 10:
            fn_800811B4(fn_80182DC8(), lbl_8000A20C[a][i]);
            break;
        case 11:
            fn_8008115C(fn_80182DC8(), lbl_8000A20C[a][i]);
            break;
        default:
            fn_8008135C(fn_80182DC8(), fn_80183238(i), lbl_8000A20C[a][i]);
            break;
        }
    }
}

static inline Class_80009CC8 *fn_80008C0C()
{
    static Class_80009CC8 sInstance;
    return &sInstance;
}

static inline Class_80009C88 *fn_80008C34()
{
    static Class_80009C88 sInstance;
    return &sInstance;
}

static inline Class_8000A0B8 *fn_80008C64()
{
    static Class_8000A0B8 sInstance;
    return &sInstance;
}

static inline Class_8000A068 *fn_80008C8C()
{
    static Class_8000A068 sInstance;
    return &sInstance;
}

static inline Class_8000A018 *fn_80008CB4()
{
    static Class_8000A018 sInstance;
    return &sInstance;
}

static inline Class_80009ED8 *fn_80008CDC()
{
    static Class_80009ED8 sInstance;
    return &sInstance;
}

static inline Class_80009E88 *fn_80008D04()
{
    static Class_80009E88 sInstance;
    return &sInstance;
}

static inline Class_80009D88 *fn_80008D2C()
{
    static Class_80009D88 sInstance;
    return &sInstance;
}

static inline Class_80009D28 *fn_80008D5C()
{
    static Class_80009D28 sInstance;
    return &sInstance;
}

static inline Class_80009E48 *fn_80008D84()
{
    static Class_80009E48 sInstance;
    return &sInstance;
}

static inline Class_80009E08 *fn_80008DB4()
{
    static Class_80009E08 sInstance;
    return &sInstance;
}

static inline Class_80009DC8 *fn_80008DE4()
{
    static Class_80009DC8 sInstance;
    return &sInstance;
}

static inline Class_80009FC8 *fn_80008E14()
{
    static Class_80009FC8 sInstance;
    return &sInstance;
}

static inline Class_80009F78 *fn_80008E3C()
{
    static Class_80009F78 sInstance;
    return &sInstance;
}

static inline Class_80009F28 *fn_80008E64()
{
    static Class_80009F28 sInstance;
    return &sInstance;
}

static inline Class_8000A108 *fn_80008E8C()
{
    static Class_8000A108 sInstance;
    return &sInstance;
}
