#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/Row_8007BC34.h"
#include "game/cu_8015C25C.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"

/* One selectable gear row of the current category, built by fn_8000A620. */
struct Entry_8036A2C8 {
    int mUnknown0;
    int mId;
    int mOwner;
    unsigned char mUnknown12;
};

extern "C" {
void fn_800225F4(int index, unsigned int value);
void fn_80022680(int index, int a, int b);
void fn_80022D6C(void);
int fn_80022D78(void);
int fn_80022D80(void);
void fn_80022E40(int a, int b);
int fn_800238A0(int index);
int fn_80023914(int index);
void fn_80023988(int a, char *pBuffer, int size);
unsigned char fn_80023A3C(int index, int a);
void fn_80023B08(int index, int a);
int fn_80023BBC(int index, int a);
int fn_80023CA4(int index, int a);
int fn_800489F4(unsigned int type);
int fn_80048ACC(int type);
void fn_80048FA0(int index, int value);
void fn_80048FB8(int index, int value);
void fn_80049AD0(int index, unsigned char value);
void fn_80049AE8(int index, unsigned char value);
void fn_80049B00(int index, int value);
void fn_80049B18(int index, unsigned char value);
void fn_80049DD0(int index, unsigned char value);
void fn_80049DE8(int index, unsigned char value);
int fn_8007A43C(Object_8007A334 *pObject);
void fn_8007BA88(Object_8007A334 *pCursor, int value);
void fn_8007BB04(Object_8007A334 *pCursor);
int fn_8007BB24(Object_8007A334 *pCursor);
int fn_8007BBFC(Object_8007A334 *pCursor, int key, int *pResult);
void fn_8007BE20(Object_8007A334 *pCursor, char *pBuffer, int size);
int fn_8007BE54(Object_8007A334 *pCursor);
int fn_8007BE7C(Object_8007A334 *pCursor);
int fn_8007BEA4(Object_8007A334 *pCursor);
int fn_8007BF14(int index);
int fn_8007BF28(int index);
int fn_8007BF3C(Object_8007A334 *pCursor);
int fn_8007C690(Object_8007A334 *pCursor, short *pOut);
void fn_8007DDC8(Object_8007A334 *pObject, int a);
void fn_8007DE20(Object_8007A334 *pObject);
void fn_8007DE40(Object_8007A334 *pObject, int key, unsigned char *pA, unsigned char *pB);
void fn_8007DFC4(Object_8007A334 *pObject, int id);
int fn_8007E020(int type, int a, int b);
int fn_800808F8(Object_8008044C *pObject);
int fn_80080D10(Object_8008044C *pObject);
void fn_8008199C(Object_8008044C *pObject, Info_80307908 *pInfo);
Object_8007A334 *fn_80182DBC(void);
Object_8008044C *fn_80182DC8(void);
void fn_80182DD4(const char *pText);
void fn_80182E04(const char *pText);
void fn_80182E34(char *pText);
void fn_80182ED0(void);
void fn_80182F24(Info_80307908 *pInfo);
void fn_80182FD4(int a, unsigned char value);
void fn_8018300C(void);
void fn_80183130(int a);
void fn_801831A4(void);
void fn_801831E8(unsigned char a);
void fn_801832B0(char *pText, int size);
int fn_80183354(void);
void fn_801835C8(void);
void fn_80183704(void);
int fn_80183948(void);
int fn_80183950(void);
int fn_80183968(void);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801C302C(const char *s1, const char *s2, int n);
int fn_8022F384(int a);
int fn_8022F4BC(void);
}

extern const Entry_80182CC8 lbl_8000D2D0[];
extern const Entry_80182CC8 lbl_8000D380[];
extern const Entry_80182CC8 lbl_8000D430[];
extern const Entry_80182CC8 lbl_8000D488[];
extern const Entry_80182CC8 lbl_8000D564[];
extern const Entry_80182CC8 lbl_8000D640[];
extern const Entry_80182CC8 lbl_8000D6F0[];
extern const int lbl_8000D774[];
extern const int lbl_8000D784[];
extern const int lbl_8000D798[];
extern const int lbl_8000D7AC[];
extern const int lbl_8000D7BC[];

/* Entries of the body-area menu and its submenus. */
const Entry_80182CC8 lbl_8000D2D0[] = {
    { 0, 0, "Head", 1 },
    { 1, 0, "Arms", 1 },
    { 2, 0, "Torso", 1 },
    { 3, 0, "Legs", 1 },
};

const Entry_80182CC8 lbl_8000D380[] = {
    { 0, 0, "Headwear", 1, 20 },
    { 1, 0, "Headwear Style", 1, 21 },
    { 2, 0, "Headwear Decal", 1, 19 },
    { 3, 0, "Glasses", 1, 15 },
};

const Entry_80182CC8 lbl_8000D430[] = {
    { 0, 0, "Chain", 1 },
    { 1, 0, "Medallion", 1 },
};

const Entry_80182CC8 lbl_8000D488[] = {
    { 0, 0, "Shirt", 1, 34 },
    { 1, 0, "Front Decal", 1, 13 },
    { 2, 0, "Back Decal", 1, 3 },
    { 3, 0, "Shoulder Pads", 1, 36 },
    { 4, 0, "Jewelry", 1 },
};

const Entry_80182CC8 lbl_8000D564[] = {
    { 0, 0, "Long Sleeve", 1, 34 },
    { 1, 0, "Short Sleeve", 1, 34 },
    { 2, 0, "Jersey", 1, 34 },
    { 3, 0, "NFL Jersey", 1, 34 },
    { 4, 0, "Throwback Jersey", 1, 34 },
};

const Entry_80182CC8 lbl_8000D640[] = {
    { 0, 0, "Upper Arm", 1, 53 },
    { 1, 0, "Elbow", 1, 10 },
    { 2, 0, "Wrist", 1, 55 },
    { 3, 0, "Hands", 1, 18 },
};

const Entry_80182CC8 lbl_8000D6F0[] = {
    { 0, 0, "Pants", 1, 26 },
    { 1, 0, "Socks", 1, 43 },
    { 2, 0, "Shoes", 1, 35 },
};

/* Gear category of each menu entry; 14 marks an entry without one. */
const int lbl_8000D774[] = { 0, 14, 14, 1 };
const int lbl_8000D784[] = { 14, 14, 14, 2, 14 };
const int lbl_8000D798[] = { 10, 10, 10, 10, 10 };
const int lbl_8000D7AC[] = { 3, 4, 5, 6 };
const int lbl_8000D7BC[] = { 11, 8, 9 };
static const int lbl_803ED6D8[] = { 12, 13 };

static const char *lbl_802F4140[] = { "L", "R", "B" };
static const char *lbl_802F414C[] = {
    "Front", "Back", "Side", "Upside Down Front", "Upside Down Back", "Upside Down Side",
};
static const char *lbl_802F4164[] = {
    "None", "Number", "Team Name", "Team Logo & Name", "Team Logo & Name", "Team Logo",
};
static int lbl_802F417C[] = { 0, 1, 5 };
static int lbl_802F4188[] = { 0, 1, 5, 2, 3 };
static int lbl_802F419C[] = { 0, 1, 2 };
static int lbl_802F41A8[] = { 0, 2, 3, 5, 1 };

static const Layout_802EA9E0 lbl_8000DC30[] = {
    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15, 1 },
    { 23.0f, 975.0f, 0.0f, 338.0f, 3.1f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, 255.0f, 0.0f, 348.0f, 0.9f, 15, 0 },
    { 0.0f, -15.0f, 0.0f, 335.0f, 0.25f, 15, 0 },
};

static const unsigned short lbl_8000DCBC[] = { 2, 2, 14, 11, 11, 12, 8, 12, 15, 15, 2, 9, 2, 2 };

static inline bool AnyDecalFlagged()
{
    return fn_80023914(fn_80183354()) != 0;
}

class Class_8000DBF0 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pOut);
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_03(int index);
    virtual void vfn_04(int index, int *pOut);
    virtual void vfn_05(int index, Entry_80182CC8 *pOut);

    char mUnknown4[4];
};

class Class_8000DBA0 : public Class_802A6B60 {
public:
    virtual void vfn_01(int a, int *pCount, int *pOut);
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_03(int id);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);
    virtual int vfn_07() { return 4; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_8000D2D0; }

    char mUnknown4[4];
};

class Class_8000DB50 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);
    virtual int vfn_07() { return 4; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_8000D380; }
    int fn_8000B600();

    char mUnknown4[4];
};

class Class_8000DB00 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);
    virtual int vfn_07() { return 2; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_8000D430; }
    int fn_8000B760();

    char mUnknown4[4];
};

class Class_8000DAB0 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);
    virtual int vfn_07() { return 5; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_8000D488; }
    int fn_8000B984();

    char mUnknown4[4];
};

class Class_8000DA60 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);
    virtual int vfn_07() { return 5; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_8000D564; }
    int fn_8000BADC();

    char mUnknown4[4];
};

class Class_8000DA10 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);
    virtual int vfn_07() { return 4; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_8000D640; }
    int fn_8000BBD0();

    char mUnknown4[4];
};

class Class_8000D9C0 : public Class_802A6B60 {
public:
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_05(int id, Entry_80182CC8 *pOut);
    virtual int vfn_07() { return 3; }
    virtual Entry_80182CC8 *vfn_08() { return (Entry_80182CC8 *)lbl_8000D6F0; }
    int fn_8000BCE0();

    char mUnknown4[4];
};

class Class_8000D980 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pOut);
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_03(int index);
    virtual void vfn_04(int index, int *pOut) { *pOut = index; }
    virtual void vfn_05(int index, Entry_80182CC8 *pOut);

    char mUnknown4[4];
    int mUnknown8;
    int mUnknown12;
};

class Class_8000D940 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pOut);
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_03(int index);
    virtual void vfn_04(int index, int *pOut) { *pOut = index; }
    virtual void vfn_05(int index, Entry_80182CC8 *pOut);

    char mUnknown4[4];
    int mUnknown8;
    int mUnknown12;
};

class Class_8000D900 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pOut);
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_03(int index);
    virtual void vfn_04(int index, int *pOut) { *pOut = index; }
    virtual void vfn_05(int index, Entry_80182CC8 *pOut);

    char mUnknown4[4];
    int mUnknown8;
};

class Class_8000D8C0 : public Class_80184190 {
public:
    virtual void vfn_01(int a, int *pCount, int *pOut);
    virtual int vfn_02(int a, int b, void **pOut);
    virtual void vfn_03(int index);
    virtual void vfn_04(int index, int *pOut) { *pOut = index; }
    virtual void vfn_05(int index, Entry_80182CC8 *pOut);

    char mUnknown4[4];
    int mUnknown8;
};

static inline Class_8000DB50 *fn_8000D0A0();
static inline Class_8000DAB0 *fn_8000D0C8();
static inline Class_8000DA10 *fn_8000D0F0();
static inline Class_8000D9C0 *fn_8000D118();
static inline Class_8000DBA0 *fn_8000D140();
static inline Class_8000D980 *fn_8000D168();
static inline Class_8000D900 *fn_8000D198();
static inline Class_8000DA60 *fn_8000D1C8();
static inline Class_8000D8C0 *fn_8000D1F0();
static inline Class_8000DB00 *fn_8000D220();
static inline Class_8000D940 *fn_8000D248();

static Object_8007A334 lbl_8036A1FC;
static Object_8007A334 lbl_8036A228;
static Object_8007A334 lbl_8036A254;
static Info_80307908 lbl_8036A280;
static Entry_8036A2C8 lbl_8036A2C8[166];
static unsigned char lbl_803EB940 = 0;
static int lbl_803ECDD0;
static int lbl_803ECDD4;
static int lbl_803ECDD8;
static int lbl_803ECDDC;

static void fn_8000A360(int id, int index)
{
    if (lbl_803ECDD0 != 14) {
        int type = fn_8007BF14(lbl_803ECDD0);
        int row = fn_8007A43C((Object_8007A334 *)fn_80182DC8());
        Info_80307908 info;

        fn_800809C4(fn_80182DC8(), id, 0);
        fn_800817CC(fn_80182DC8(), &info);
        fn_8007BBFC(&lbl_8036A1FC, 0, 0);
        if (fn_8007BF28(type) != 14) {
            info.mValues[fn_8007BF28(type)] = 0;
        } else if (type == 6) {
            info.mValues[7] = 0;
            info.mValues[6] = 0;
        }
        fn_8008199C(fn_80182DC8(), &info);
        fn_8007A600((Object_8007A334 *)fn_80182DC8(), row);
    }
}

static int fn_8000A434(int type, int value)
{
    int result = -1;

    if (lbl_803ECDD0 != 14) {
        int row = fn_8007A43C((Object_8007A334 *)fn_80182DC8());
        Info_80307908 info;
        int found;

        for (found = fn_8007A444((Object_8007A334 *)fn_80182DC8()); found && result == -1; found = fn_8007A510((Object_8007A334 *)fn_80182DC8())) {
            int id;

            fn_800817CC(fn_80182DC8(), &info);
            id = fn_800808F8(fn_80182DC8());
            if (fn_8007BF28(type) != 14) {
                if (info.mValues[fn_8007BF28(type)] == value) {
                    result = id;
                }
            } else if (type == 6) {
                if (info.mValues[7] == value || info.mValues[6] == value) {
                    result = id;
                }
            }
        }
        fn_8007A600((Object_8007A334 *)fn_80182DC8(), row);
    }
    return result;
}

static void fn_8000A528()
{
    int type = fn_8007BE7C(&lbl_8036A1FC);
    int id = fn_8007BE54(&lbl_8036A1FC);
    int unique = fn_8007BF3C(&lbl_8036A1FC);
    int current = fn_800808F8(fn_80182DC8());
    int owner = fn_8000A434(type, id);

    if (unique && owner != -1 && owner != current) {
        fn_80183130(owner);
    } else {
        fn_801831A4();
    }
}

static void fn_8000A5B0()
{
    short flags[10];

    fn_8018300C();
    if (fn_8007C690(&lbl_8036A1FC, flags)) {
        int i;

        for (i = 0; i <= 9; i++) {
            if (flags[i]) {
                fn_80182FD4(i, 1);
            }
        }
    }
}

static int fn_8000A620()
{
    int type = fn_8007BF14(lbl_803ECDD0);
    int showUnique = 1;
    int count;
    int i;

    if (fn_80183950() || fn_80183948() == 5) {
        showUnique = 0;
    }
    fn_8007BA88(&lbl_8036A1FC, type);
    count = fn_8007A410(&lbl_8036A1FC);
    lbl_803ECDD8 = 0;
    fn_8007A444(&lbl_8036A1FC);
    for (i = 0; i < count; i++) {
        int id = fn_8007BE54(&lbl_8036A1FC);
        int set = fn_8007BEA4(&lbl_8036A1FC);

        if (id == 0 || lbl_803ECDD4 == set) {
            int key = fn_8007BB24(&lbl_8036A1FC);
            int unique = fn_8007BF3C(&lbl_8036A1FC);
            unsigned char locked;
            unsigned char flag;

            fn_8007DE40(&lbl_8036A228, key, &locked, &flag);
            if (!locked && (showUnique || !unique)) {
                lbl_8036A2C8[lbl_803ECDD8].mUnknown12 = flag;
                if (unique) {
                    lbl_8036A2C8[lbl_803ECDD8].mOwner = fn_8000A434(type, id);
                } else {
                    lbl_8036A2C8[lbl_803ECDD8].mOwner = -1;
                }
                lbl_8036A2C8[lbl_803ECDD8].mUnknown0 = key;
                lbl_8036A2C8[lbl_803ECDD8].mId = id;
                lbl_803ECDD8++;
            }
        }
        fn_8007A510(&lbl_8036A1FC);
    }
    return lbl_803ECDD8;
}

static void fn_8000A7B0()
{
    fn_8007BB04(&lbl_8036A1FC);
}

static int fn_8000A7D8(int id)
{
    int i;

    for (i = 0; i < lbl_803ECDD8; i++) {
        if (lbl_8036A2C8[i].mId == id) {
            break;
        }
    }
    if (i >= lbl_803ECDD8) {
        i = 0;
    }
    return i;
}

static int fn_8000A838(int index, int a)
{
    int result = 0;

    if (index != 14) {
        int type = fn_8007BF14(index);

        result = fn_8007E020(type, a, fn_80183968());
    }
    return result;
}

static int fn_8000A890(int index)
{
    return fn_8000A838(index, -1);
}

static int fn_8000A8B4(int type)
{
    switch (type) {
    case 3:
    case 5:
    case 6:
        return 1;
    }
    return 0;
}

static int fn_8000A8E0(int type)
{
    int result = 0;

    switch (type) {
    case 3:
        result = lbl_8036A280.mUnknown00 - 1;
        break;
    case 5:
        result = lbl_8036A280.mUnknown01 - 1;
        break;
    case 6:
        if (lbl_8036A280.mValues[6] && lbl_8036A280.mValues[7] &&
            lbl_8036A280.mValues[6] == lbl_8036A280.mValues[7]) {
            result = 2;
        } else {
            result = lbl_8036A280.mValues[6] == 0;
        }
        break;
    }
    return result;
}

static void fn_8000A970(int type, int value, int item)
{
    switch (type) {
    case 3:
        lbl_8036A280.mUnknown00 = value + 1;
        break;
    case 5:
        lbl_8036A280.mUnknown01 = value + 1;
        break;
    case 6:
        if (item == 0) {
            lbl_8036A280.mValues[6] = 0;
            lbl_8036A280.mValues[7] = 0;
        } else {
            switch (value) {
            case 0:
                lbl_8036A280.mValues[6] = item;
                lbl_8036A280.mValues[7] = 0;
                break;
            case 1:
                lbl_8036A280.mValues[6] = 0;
                lbl_8036A280.mValues[7] = item;
                break;
            case 2:
                lbl_8036A280.mValues[6] = item;
                lbl_8036A280.mValues[7] = item;
                break;
            default:
                lbl_8036A280.mValues[6] = 0;
                lbl_8036A280.mValues[7] = 0;
                break;
            }
        }
        break;
    }
}

static unsigned int fn_8000AA38(int value, int *pTable, unsigned int count)
{
    unsigned int i;

    for (i = 0; i < count; i++) {
        if (pTable[i] == value) {
            break;
        }
    }
    if (i >= count) {
        i = 0;
    }
    return i;
}

static int fn_8000AA7C(unsigned char *pFlag, unsigned char *pSkullcap)
{
    Row_8007BC34 row;
    Object_8007A334 cursor;
    int type;

    fn_8007BA88(&cursor, 0);
    fn_8007BBFC(&cursor, lbl_8036A280.mValues[0], 0);
    fn_8007BC34(&cursor, &row);
    type = fn_800489F4(row.mUnknown64);
    fn_8007BB04(&cursor);
    if (pFlag) {
        *pFlag = row.mUnknown76;
    }
    if (pSkullcap) {
        if (fn_801C302C(row.mName, "SKULLCAP_BLACK_L", 16) == 0 || fn_801C302C(row.mName, "SKULLCAP_WHITE_L", 16) == 0) {
            *pSkullcap = 1;
        } else {
            *pSkullcap = 0;
        }
    }
    return type;
}

static int fn_8000AB70()
{
    Object_8007A334 cursor;
    Row_8007BC34 row;

    fn_8007BA88(&cursor, 9);
    fn_8007BBFC(&cursor, lbl_8036A280.mValues[10], 0);
    fn_8007BC34(&cursor, &row);
    fn_8007BB04(&cursor);
    return row.mUnknown71 && !row.mUnknown76;
}

static int fn_8000AC04()
{
    Object_8007A334 cursor;
    Row_8007BC34 row;

    fn_8007BA88(&cursor, 9);
    fn_8007BBFC(&cursor, lbl_8036A280.mValues[10], 0);
    fn_8007BC34(&cursor, &row);
    fn_8007BB04(&cursor);
    return row.mUnknown70 && !row.mUnknown76;
}

static int fn_8000AC98()
{
    Object_8007A334 cursor;
    Row_8007BC34 row;

    fn_8007BA88(&cursor, 9);
    fn_8007BBFC(&cursor, lbl_8036A280.mValues[10], 0);
    fn_8007BC34(&cursor, &row);
    fn_8007BB04(&cursor);
    return fn_80048ACC(row.mUnknown64);
}

static int fn_8000AD18()
{
    unsigned char flag = 0;
    unsigned char skullcap = 0;
    int allowed;

    switch (fn_8000AA7C(&flag, &skullcap)) {
    case 1:
    case 4:
    case 5:
    case 7:
    case 12:
    case 13:
    case 14:
        allowed = 1;
        break;
    default:
        allowed = 0;
        break;
    }
    return allowed && !flag && !skullcap;
}

static int fn_8000ADB4()
{
    int count = 0;

    switch (fn_8000AA7C(0, 0)) {
    case 1:
        count = 3;
        break;
    case 7:
        count = 5;
        break;
    }
    return count;
}

static int fn_8000AE0C(int index)
{
    int value = 0;

    switch (fn_8000AA7C(0, 0)) {
    case 1:
        value = lbl_802F419C[index];
        break;
    case 7:
        value = lbl_802F41A8[index];
        break;
    }
    return value;
}

static int fn_8000AE7C(int value)
{
    int result = 0;
    unsigned int i;

    switch (fn_8000AA7C(0, 0)) {
    case 1:
        for (i = 0; i < 3; i++) {
            if (lbl_802F419C[i] == value) {
                break;
            }
        }
        if (i < 3) {
            result = value;
        }
        break;
    case 7:
        for (i = 0; i < 5; i++) {
            if (lbl_802F41A8[i] == value) {
                break;
            }
        }
        if (i < 5) {
            result = value;
        }
        break;
    }
    return result;
}

static unsigned int fn_8000AF48(int value)
{
    unsigned int i = 0;

    switch (fn_8000AA7C(0, 0)) {
    case 1:
        for (i = 0; i < 3; i++) {
            if (lbl_802F419C[i] == value) {
                break;
            }
        }
        break;
    case 7:
        for (i = 0; i < 5; i++) {
            if (lbl_802F41A8[i] == value) {
                break;
            }
        }
        break;
    }
    return i;
}

void Class_8000DBA0::vfn_01(int a, int *pCount, int *pOut)
{
    Class_802A6B60::vfn_01(a, pCount, pOut);
    fn_80183740(0);
    if (!lbl_803EB940) {
        fn_80022680(fn_80022D78(), lbl_803ECDDC, 1);
        fn_8015D38C(0);
    }
}

int Class_8000DBA0::vfn_02(int a, int b, void **pOut)
{
    int result = Class_802A6B60::vfn_02(a, b, pOut);

    if (b == 0) {
        switch (a) {
        case 0:
            result = 1;
            fn_80183740(&lbl_8000DC30[1]);
            *pOut = fn_8000D0A0();
            break;
        case 2:
            result = 1;
            fn_80183740(&lbl_8000DC30[2]);
            *pOut = fn_8000D0C8();
            break;
        case 1:
            result = 1;
            fn_80183740(&lbl_8000DC30[3]);
            *pOut = fn_8000D0F0();
            break;
        case 3:
            result = 1;
            fn_80183740(&lbl_8000DC30[4]);
            *pOut = fn_8000D118();
            break;
        }
    }
    if (!lbl_803EB940) {
        fn_8015D38C(1);
    }
    return result;
}

void Class_8000DBA0::vfn_03(int id)
{
    fn_80182DD4("Gear");
}

void Class_8000DBA0::vfn_05(int id, Entry_80182CC8 *pOut)
{
    Class_802A6B60::vfn_05(id, pOut);
    switch (id) {
    case 0:
        pOut->mUnknown40 = fn_8000D0A0()->fn_8000B600();
        break;
    case 2:
        pOut->mUnknown40 = fn_8000D0C8()->fn_8000B984();
        break;
    case 1:
        pOut->mUnknown40 = fn_8000D0F0()->fn_8000BBD0();
        break;
    case 3:
        pOut->mUnknown40 = fn_8000D118()->fn_8000BCE0();
        break;
    }
}

void Class_8000DBF0::vfn_01(int a, int *pCount, int *pOut)
{
    char buffer[18];

    fn_80083F88(fn_80182DBC(), buffer, 18);
    fn_80182E34(buffer);
    fn_80182DD4("");
    fn_80182E04("");
    *pCount = fn_8007A410((Object_8007A334 *)fn_80182DC8()) + 1;
    fn_8007A444((Object_8007A334 *)fn_80182DC8());
    lbl_803ECDDC = fn_800808F8(fn_80182DC8());
    fn_80022680(fn_80022D80(), lbl_803ECDDC, 1);
}

int Class_8000DBF0::vfn_02(int a, int b, void **pOut)
{
    char buffer[27];

    *pOut = fn_8000D140();
    fn_800809C4(fn_80182DC8(), a, 0);
    fn_801832B0(buffer, 27);
    fn_80182E34(buffer);
    fn_800817CC(fn_80182DC8(), &lbl_8036A280);
    return 1;
}

void Class_8000DBF0::vfn_03(int index)
{
    if (index != 0x7FFF) {
        char buffer[27];

        fn_800809C4(fn_80182DC8(), index, 0);
        lbl_803ECDDC = index;
        fn_80022680(fn_80022D80(), index, 0);
        fn_801832B0(buffer, 27);
        fn_80182DD4(buffer);
        fn_80182ED0();
    } else {
        fn_80182DD4("Save And Exit");
    }
}

void Class_8000DBF0::vfn_04(int index, int *pOut)
{
    if (index >= fn_8007A410((Object_8007A334 *)fn_80182DC8())) {
        *pOut = 0x7FFF;
    } else {
        fn_8007A600((Object_8007A334 *)fn_80182DC8(), index);
        *pOut = fn_800808F8(fn_80182DC8());
    }
}

void Class_8000DBF0::vfn_05(int index, Entry_80182CC8 *pOut)
{
    char buffer[27] = { 0 };

    pOut->mUnknown40 = 0;
    if (index != 0x7FFF) {
        int value;

        fn_800809C4(fn_80182DC8(), index, 0);
        value = fn_80080D10(fn_80182DC8());
        pOut->mUnknown36 = fn_8007A43C((Object_8007A334 *)fn_80182DC8());
        pOut->mId = index;
        pOut->mUnknown30 = 1;
        pOut->mUnknown4 = 0;
        pOut->mUnknown32 = value | 0xA0000;
        fn_801832B0(buffer, 27);
        fn_801C3284(pOut->mName, buffer, 22);
    } else {
        pOut->mUnknown36 = fn_8007A410((Object_8007A334 *)fn_80182DC8());
        pOut->mId = index;
        pOut->mUnknown30 = 1;
        pOut->mUnknown4 = 4;
        pOut->mUnknown32 = 0xC0034;
        fn_801C3284(pOut->mName, "Undo Changes", 22);
    }
}

int Class_8000DB50::vfn_02(int a, int b, void **pOut)
{
    int result = Class_802A6B60::vfn_02(a, b, pOut);

    if (b == 0) {
        int type = lbl_8000D774[a];

        if (type != 14) {
            Class_8000D980 *pItems = fn_8000D168();

            result = 1;
            pItems->mUnknown8 = type;
            pItems->mUnknown12 = 0;
            *pOut = fn_8000D168();
        } else {
            switch (a) {
            case 1:
            case 2:
                fn_8000D198()->mUnknown8 = a;
                result = 1;
                *pOut = fn_8000D198();
                break;
            }
        }
    }
    return result;
}

void Class_8000DB50::vfn_05(int id, Entry_80182CC8 *pOut)
{
    Class_802A6B60::vfn_05(id, pOut);
    if (id == 2) {
        pOut->mUnknown40 = AnyDecalFlagged();
    } else {
        pOut->mUnknown40 = fn_8000A890(lbl_8000D774[id]);
    }
    switch (id) {
    case 1:
        pOut->mUnknown30 = fn_8000ADB4() != 0;
        break;
    case 2:
        pOut->mUnknown30 = fn_8000AD18();
        break;
    default:
        pOut->mUnknown30 = lbl_8000D380[id].mUnknown30;
        break;
    }
}

int Class_8000DB50::fn_8000B600()
{
    int result = 0;
    int i;

    for (i = 0; i <= 3; i++) {
        if (fn_8000A890(lbl_8000D774[i])) {
            result = 1;
            break;
        }
    }
    if (!result) {
        result = AnyDecalFlagged();
    }
    return result;
}

int Class_8000DB00::vfn_02(int a, int b, void **pOut)
{
    int result = Class_802A6B60::vfn_02(a, b, pOut);

    if (b == 0) {
        int value = lbl_803ED6D8[a];
        Class_8000D980 *pItems = fn_8000D168();

        result = 1;
        pItems->mUnknown8 = value;
        pItems->mUnknown12 = b;
        *pOut = fn_8000D168();
    }
    return result;
}

void Class_8000DB00::vfn_05(int id, Entry_80182CC8 *pOut)
{
    Class_802A6B60::vfn_05(id, pOut);
    pOut->mUnknown40 = fn_8000A890(lbl_803ED6D8[id]);
    if (lbl_8000D430[id].mId == 1) {
        pOut->mUnknown30 = lbl_8036A280.mValues[12] != 0;
    }
}

int Class_8000DB00::fn_8000B760()
{
    int result = 0;
    int i;

    for (i = 0; i < 2; i++) {
        if (fn_8000A890(lbl_803ED6D8[i])) {
            result = 1;
            break;
        }
    }
    return result;
}

int Class_8000DAB0::vfn_02(int a, int b, void **pOut)
{
    int result = Class_802A6B60::vfn_02(a, b, pOut);

    if (b == 0) {
        int value = lbl_8000D784[a];

        if (value != 14) {
            Class_8000D980 *pItems = fn_8000D168();

            result = 1;
            pItems->mUnknown8 = value;
            pItems->mUnknown12 = b;
            *pOut = fn_8000D168();
        } else {
            switch (a) {
            case 0:
                *pOut = fn_8000D1C8();
                result = 1;
                break;
            case 1:
            case 2:
                fn_8000D1F0()->mUnknown8 = a;
                result = 1;
                *pOut = fn_8000D1F0();
                break;
            case 4:
                *pOut = fn_8000D220();
                result = 1;
                break;
            }
        }
    }
    return result;
}

void Class_8000DAB0::vfn_05(int id, Entry_80182CC8 *pOut)
{
    Class_802A6B60::vfn_05(id, pOut);
    switch (id) {
    case 0:
        pOut->mUnknown40 = fn_8000D1C8()->fn_8000BADC();
        break;
    case 4:
        pOut->mUnknown40 = fn_8000D220()->fn_8000B760();
        break;
    case 1:
    case 2:
        pOut->mUnknown40 = AnyDecalFlagged();
        break;
    default:
        pOut->mUnknown40 = fn_8000A890(lbl_8000D784[id]);
        break;
    }
    switch (id) {
    case 2:
        pOut->mUnknown30 = fn_8000AC04();
        break;
    case 1:
        pOut->mUnknown30 = fn_8000AB70();
        break;
    case 3:
        pOut->mUnknown30 = fn_8000AC98();
        break;
    default:
        pOut->mUnknown30 = lbl_8000D488[id].mUnknown30;
        break;
    }
}

int Class_8000DAB0::fn_8000B984()
{
    int result = 0;
    int i;

    for (i = 0; i < 5; i++) {
        if (fn_8000A890(lbl_8000D784[i])) {
            result = 1;
            break;
        }
    }
    if (!result) {
        result = fn_8000D1C8()->fn_8000BADC();
        if (!result) {
            result = fn_8000D220()->fn_8000B760();
            if (!result) {
                result = AnyDecalFlagged();
            }
        }
    }
    return result;
}

int Class_8000DA60::vfn_02(int a, int b, void **pOut)
{
    int result = Class_802A6B60::vfn_02(a, b, pOut);

    if (b == 0) {
        int value = lbl_8000D798[a];
        Class_8000D980 *pItems = fn_8000D168();

        result = 1;
        pItems->mUnknown8 = value;
        pItems->mUnknown12 = a;
        *pOut = fn_8000D168();
    }
    return result;
}

void Class_8000DA60::vfn_05(int id, Entry_80182CC8 *pOut)
{
    Class_802A6B60::vfn_05(id, pOut);
    pOut->mUnknown40 = fn_8000A838(lbl_8000D798[id], id);
}

int Class_8000DA60::fn_8000BADC()
{
    int result = 0;

    if (fn_8000A890(10)) {
        result = 1;
    }
    return result;
}

int Class_8000DA10::vfn_02(int a, int b, void **pOut)
{
    int result = Class_802A6B60::vfn_02(a, b, pOut);

    if (b == 0) {
        int value = lbl_8000D7AC[a];
        Class_8000D980 *pItems = fn_8000D168();

        result = 1;
        pItems->mUnknown8 = value;
        pItems->mUnknown12 = b;
        *pOut = fn_8000D168();
    }
    return result;
}

void Class_8000DA10::vfn_05(int id, Entry_80182CC8 *pOut)
{
    Class_802A6B60::vfn_05(id, pOut);
    pOut->mUnknown40 = fn_8000A890(lbl_8000D7AC[id]);
}

int Class_8000DA10::fn_8000BBD0()
{
    int result = 0;
    int i;

    for (i = 0; i < 4; i++) {
        if (fn_8000A890(lbl_8000D7AC[i])) {
            result = 1;
            break;
        }
    }
    return result;
}

int Class_8000D9C0::vfn_02(int a, int b, void **pOut)
{
    int result = Class_802A6B60::vfn_02(a, b, pOut);

    if (b == 0) {
        int value = lbl_8000D7BC[a];
        Class_8000D980 *pItems = fn_8000D168();

        result = 1;
        pItems->mUnknown8 = value;
        pItems->mUnknown12 = b;
        *pOut = fn_8000D168();
    }
    return result;
}

void Class_8000D9C0::vfn_05(int id, Entry_80182CC8 *pOut)
{
    Class_802A6B60::vfn_05(id, pOut);
    pOut->mUnknown40 = fn_8000A890(lbl_8000D7BC[id]);
}

int Class_8000D9C0::fn_8000BCE0()
{
    int result = 0;
    int i;

    for (i = 0; i < 3; i++) {
        if (fn_8000A890(lbl_8000D7BC[i])) {
            result = 1;
            break;
        }
    }
    return result;
}

void Class_8000D980::vfn_01(int a, int *pCount, int *pOut)
{
    int type;
    int id;

    lbl_803ECDD0 = mUnknown8;
    lbl_803ECDD4 = mUnknown12;
    type = fn_8007BF14(lbl_803ECDD0);
    *pCount = fn_8000A620();
    if (type == 6) {
        id = lbl_8036A280.mValues[6];
        if (id == 0) {
            id = lbl_8036A280.mValues[7];
        }
    } else {
        int index = lbl_803ECDD0;

        id = lbl_8036A280.mValues[index];
    }
    *pOut = fn_8000A7D8(id);
    if (fn_8000A8B4(type)) {
        *pCount = (*pCount - 1) * 3 + 1;
        if (*pOut != 0) {
            *pOut = (*pOut - 1) * 3 + 1;
            *pOut += fn_8000A8E0(type);
        }
    }
}

int Class_8000D980::vfn_02(int a, int b, void **pOut)
{
    int result = -1;

    if (b == 0) {
        Row_8007BC34 row;
        int index = a;
        int type = fn_8007BF14(lbl_803ECDD0);

        if (fn_8000A8B4(type) && index != 0) {
            index = (index - 1) / 3 + 1;
        }
        fn_8007A600(&lbl_8036A1FC, lbl_8036A2C8[index].mId);
        fn_8007BC34(&lbl_8036A1FC, &row);
        if (row.mUnknown76) {
            fn_8000D248()->mUnknown8 = type;
            result = 1;
            fn_8000D248()->mUnknown12 = lbl_8036A2C8[index].mUnknown0;
            *pOut = fn_8000D248();
        } else {
            if (lbl_8036A2C8[index].mUnknown12) {
                fn_8007DFC4(&lbl_8036A228, lbl_8036A2C8[index].mUnknown0);
            }
            if (lbl_8036A2C8[index].mOwner != -1 && lbl_8036A2C8[index].mOwner != lbl_803ECDDC) {
                fn_8000A360(lbl_8036A2C8[index].mOwner, index);
            }
            if (lbl_803ECDD0 == 0) {
                lbl_8036A280.mUnknown02 = fn_8000AE7C(lbl_8036A280.mUnknown02);
            }
            fn_8008199C(fn_80182DC8(), &lbl_8036A280);
        }
    } else {
        fn_800817CC(fn_80182DC8(), &lbl_8036A280);
        if (fn_8007BF14(lbl_803ECDD0) == 6) {
            fn_80022E40(6, lbl_8036A280.mValues[6]);
            fn_80022E40(7, lbl_8036A280.mValues[7]);
        } else {
            fn_80022E40(lbl_803ECDD0, lbl_8036A280.mValues[lbl_803ECDD0]);
        }
        if (lbl_803ECDD0 == 0) {
            fn_80049AD0(0, lbl_8036A280.mUnknown02);
            fn_80049AD0(1, lbl_8036A280.mUnknown02);
        }
        fn_80049DD0(0, lbl_8036A280.mUnknown00);
        fn_80049DD0(1, lbl_8036A280.mUnknown00);
        fn_80049DE8(0, lbl_8036A280.mUnknown01);
        fn_80049DE8(1, lbl_8036A280.mUnknown01);
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
    }
    fn_801831A4();
    fn_8018300C();
    fn_801831E8(0);
    fn_80182ED0();
    fn_8000A7B0();
    fn_800225F4(0, 2);
    fn_800225F4(1, 2);
    return result;
}

void Class_8000D980::vfn_03(int index)
{
    int side = -1;
    int item;
    int type;

    fn_800225F4(0, lbl_8000DCBC[lbl_803ECDD0]);
    fn_800225F4(1, lbl_8000DCBC[lbl_803ECDD0]);
    item = index;
    type = fn_8007BF14(lbl_803ECDD0);
    if (fn_8000A8B4(type) && item != 0) {
        side = (item - 1) % 3;
        item = (item - 1) / 3 + 1;
    }
    fn_8007A600(&lbl_8036A1FC, lbl_8036A2C8[item].mId);
    lbl_8036A280.mValues[lbl_803ECDD0] = lbl_8036A2C8[item].mId;
    fn_8000A528();
    fn_8000A5B0();
    if (fn_8000A8B4(type)) {
        fn_8000A970(type, side, lbl_8036A2C8[item].mId);
    }
    if (type == 6) {
        fn_80022E40(6, lbl_8036A280.mValues[6]);
        fn_80022E40(7, lbl_8036A280.mValues[7]);
    } else {
        fn_80022E40(lbl_803ECDD0, lbl_8036A280.mValues[lbl_803ECDD0]);
    }
    if (lbl_803ECDD0 == 0) {
        unsigned char value = fn_8000AE7C(lbl_8036A280.mUnknown02);

        fn_80049AD0(0, value);
        fn_80049AD0(1, value);
    }
    fn_80182F24(&lbl_8036A280);
    fn_80049DD0(0, lbl_8036A280.mUnknown00);
    fn_80049DD0(1, lbl_8036A280.mUnknown00);
    fn_80049DE8(0, lbl_8036A280.mUnknown01);
    fn_80049DE8(1, lbl_8036A280.mUnknown01);
    fn_8015D180(fn_80022D78(), 15);
    fn_80022D6C();
}

void Class_8000D980::vfn_05(int index, Entry_80182CC8 *pOut)
{
    int item = index;
    int side = -1;
    char name[32];

    if (fn_8000A8B4(fn_8007BF14(lbl_803ECDD0)) && item != 0) {
        side = (item - 1) % 3;
        item = (item - 1) / 3 + 1;
    }
    fn_8007A600(&lbl_8036A1FC, lbl_8036A2C8[item].mId);
    pOut->mUnknown40 = lbl_8036A2C8[item].mUnknown12;
    fn_8007BE20(&lbl_8036A1FC, name, 32);
    if (side != -1) {
        fn_801C2D88(pOut->mName, 22, "%s-%s", lbl_802F4140[side], name);
    } else {
        fn_801C3284(pOut->mName, name, 22);
    }
}

void Class_8000D940::vfn_01(int a, int *pCount, int *pOut)
{
    Query_80083E40 query;
    int selected;

    query.mUnknown4 = 3;
    query.mUnknown0 = 1;
    selected = 0;
    fn_80083E40(&lbl_8036A254, &query, 0x54415453);
    *pCount = fn_8007A410(&lbl_8036A254);
    switch (mUnknown8) {
    case 0:
        selected = lbl_8036A280.mUnknown0D;
        break;
    case 9:
        selected = lbl_8036A280.mUnknown0C;
        break;
    }
    *pOut = 0;
    for (int more = fn_8007A444(&lbl_8036A254); more; more = fn_8007A510(&lbl_8036A254)) {
        if (fn_80084158(&lbl_8036A254) - 1 == selected) {
            *pOut = fn_8007A43C(&lbl_8036A254);
            break;
        }
    }
}

int Class_8000D940::vfn_02(int a, int b, void **pOut)
{
    int result;
    int value;

    fn_8007A600(&lbl_8036A254, a);
    result = -1;
    value = fn_80084158(&lbl_8036A254) - 1;
    if (b == 0) {
        switch (mUnknown8) {
        case 0:
            lbl_8036A280.mUnknown0D = value;
            break;
        case 9:
            lbl_8036A280.mUnknown0C = value;
            break;
        }
        result = -2;
        fn_8007DFC4(&lbl_8036A228, mUnknown12);
        fn_8008199C(fn_80182DC8(), &lbl_8036A280);
    } else {
        fn_800817CC(fn_80182DC8(), &lbl_8036A280);
        switch (mUnknown8) {
        case 0:
            fn_80048FA0(0, lbl_8036A280.mUnknown0D);
            fn_80048FA0(1, lbl_8036A280.mUnknown0D);
            break;
        case 9:
            fn_80048FB8(0, lbl_8036A280.mUnknown0C);
            fn_80048FB8(1, lbl_8036A280.mUnknown0C);
            break;
        }
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
    }
    fn_80083F68(&lbl_8036A254);
    return result;
}

void Class_8000D940::vfn_03(int index)
{
    int value;

    fn_8007A600(&lbl_8036A254, index);
    value = fn_80084158(&lbl_8036A254) - 1;
    switch (mUnknown8) {
    case 0:
        fn_80048FA0(0, value);
        fn_80048FA0(1, value);
        break;
    case 9:
        fn_80048FB8(0, value);
        fn_80048FB8(1, value);
        break;
    }
    fn_8015D180(fn_80022D78(), 15);
    fn_80022D6C();
}

void Class_8000D940::vfn_05(int index, Entry_80182CC8 *pOut)
{
    char name[18];

    fn_8007A600(&lbl_8036A254, index);
    fn_80083F88(&lbl_8036A254, name, 18);
    fn_801C3284(pOut->mName, name, 22);
}

static int fn_8000C648()
{
    return fn_80183948() != 5 ? 3 : 5;
}

static int fn_8000C678(int index)
{
    if (fn_80183948() == 5) {
        return lbl_802F4188[index];
    }
    return lbl_802F417C[index];
}

static int *fn_8000C6CC()
{
    if (fn_80183948() == 5) {
        return lbl_802F4188;
    }
    return lbl_802F417C;
}

void Class_8000D900::vfn_01(int a, int *pCount, int *pOut)
{
    *pCount = 0;
    *pOut = 0;
    switch (mUnknown8) {
    case 1:
        *pOut = fn_8000AF48(lbl_8036A280.mUnknown02);
        *pCount = fn_8000ADB4();
        break;
    case 2: {
        unsigned char value = lbl_8036A280.mUnknown0B;

        if (value <= 5) {
            *pOut = fn_8000AA38(value, fn_8000C6CC(), fn_8000C648());
        } else {
            *pOut = fn_80023BBC(fn_80183354(), lbl_8036A280.mUnknown0B - 6) + fn_8000C648();
        }
        *pCount = fn_8000C648() + fn_800238A0(fn_80183354());
        break;
    }
    }
}

int Class_8000D900::vfn_02(int a, int b, void **pOut)
{
    if (b == 0) {
        fn_8008199C(fn_80182DC8(), &lbl_8036A280);
        if (mUnknown8 == 2 && lbl_8036A280.mUnknown0B > 5) {
            fn_80023B08(fn_80183354(), lbl_8036A280.mUnknown0B - 6);
        }
    } else {
        fn_800817CC(fn_80182DC8(), &lbl_8036A280);
        switch (mUnknown8) {
        case 1:
            fn_80049AD0(0, lbl_8036A280.mUnknown02);
            fn_80049AD0(1, lbl_8036A280.mUnknown02);
            break;
        case 2:
            fn_80049AE8(0, lbl_8036A280.mUnknown0B);
            fn_80049AE8(1, lbl_8036A280.mUnknown0B);
            break;
        }
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
    }
    return -1;
}

void Class_8000D900::vfn_03(int index)
{
    switch (mUnknown8) {
    case 1:
        if (fn_8000ADB4()) {
            lbl_8036A280.mUnknown02 = fn_8000AE0C(index);
            fn_80049AD0(0, lbl_8036A280.mUnknown02);
            fn_80049AD0(1, lbl_8036A280.mUnknown02);
            fn_8015D180(fn_80022D78(), 15);
            fn_80022D6C();
        }
        break;
    case 2:
        if (index < fn_8000C648()) {
            lbl_8036A280.mUnknown0B = fn_8000C678(index);
        } else {
            lbl_8036A280.mUnknown0B = fn_80023CA4(fn_80183354(), index - fn_8000C648()) + 6;
        }
        fn_80049AE8(0, lbl_8036A280.mUnknown0B);
        fn_80049AE8(1, lbl_8036A280.mUnknown0B);
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
        break;
    }
}

void Class_8000D900::vfn_05(int index, Entry_80182CC8 *pOut)
{
    switch (mUnknown8) {
    case 1:
        if (fn_8000ADB4()) {
            fn_801C3284(pOut->mName, lbl_802F414C[fn_8000AE0C(index)], 22);
        }
        break;
    case 2:
        if (index < fn_8000C648()) {
            fn_801C3284(pOut->mName, lbl_802F4164[fn_8000C678(index)], 22);
        } else {
            int id = fn_80023CA4(fn_80183354(), index - fn_8000C648());

            pOut->mUnknown40 = fn_80023A3C(fn_80183354(), id);
            fn_80023988(id, pOut->mName, 22);
        }
        break;
    }
}

void Class_8000D8C0::vfn_01(int a, int *pCount, int *pOut)
{
    *pCount = 0;
    *pOut = 0;
    switch (mUnknown8) {
    case 1: {
        unsigned char value = lbl_8036A280.mUnknown09;

        if (value <= 5) {
            *pOut = fn_8000AA38(value, fn_8000C6CC(), fn_8000C648());
        } else {
            *pOut = fn_80023BBC(fn_80183354(), lbl_8036A280.mUnknown09 - 6) + fn_8000C648();
        }
        *pCount = fn_8000C648() + fn_800238A0(fn_80183354());
        break;
    }
    case 2: {
        unsigned char value = lbl_8036A280.mUnknown0A;

        if (value <= 5) {
            *pOut = fn_8000AA38(value, fn_8000C6CC(), fn_8000C648());
        } else {
            *pOut = fn_80023BBC(fn_80183354(), lbl_8036A280.mUnknown0A - 6) + fn_8000C648();
        }
        *pCount = fn_8000C648() + fn_800238A0(fn_80183354());
        break;
    }
    }
}

int Class_8000D8C0::vfn_02(int a, int b, void **pOut)
{
    if (b == 0) {
        fn_8008199C(fn_80182DC8(), &lbl_8036A280);
        switch (mUnknown8) {
        case 1:
            if (lbl_8036A280.mUnknown09 > 5) {
                fn_80023B08(fn_80183354(), lbl_8036A280.mUnknown09 - 6);
            }
            break;
        case 2:
            if (lbl_8036A280.mUnknown0A > 5) {
                fn_80023B08(fn_80183354(), lbl_8036A280.mUnknown0A - 6);
            }
            break;
        }
    } else {
        fn_800817CC(fn_80182DC8(), &lbl_8036A280);
        switch (mUnknown8) {
        case 1:
            fn_80049B00(0, lbl_8036A280.mUnknown09);
            fn_80049B00(1, lbl_8036A280.mUnknown09);
            break;
        case 2:
            fn_80049B18(0, lbl_8036A280.mUnknown0A);
            fn_80049B18(1, lbl_8036A280.mUnknown0A);
            break;
        }
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
    }
    return -1;
}

void Class_8000D8C0::vfn_03(int index)
{
    switch (mUnknown8) {
    case 1:
        if (index < fn_8000C648()) {
            lbl_8036A280.mUnknown09 = fn_8000C678(index);
        } else {
            lbl_8036A280.mUnknown09 = fn_80023CA4(fn_80183354(), index - fn_8000C648()) + 6;
        }
        fn_80049B00(0, lbl_8036A280.mUnknown09);
        fn_80049B00(1, lbl_8036A280.mUnknown09);
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
        break;
    case 2:
        if (index < fn_8000C648()) {
            lbl_8036A280.mUnknown0A = fn_8000C678(index);
        } else {
            lbl_8036A280.mUnknown0A = fn_80023CA4(fn_80183354(), index - fn_8000C648()) + 6;
        }
        fn_80049B18(0, lbl_8036A280.mUnknown0A);
        fn_80049B18(1, lbl_8036A280.mUnknown0A);
        fn_8015D180(fn_80022D78(), 15);
        fn_80022D6C();
        break;
    }
}

void Class_8000D8C0::vfn_05(int index, Entry_80182CC8 *pOut)
{
    switch (mUnknown8) {
    case 1:
        if (index < fn_8000C648()) {
            fn_801C3284(pOut->mName, lbl_802F4164[fn_8000C678(index)], 22);
        } else {
            int id = fn_80023CA4(fn_80183354(), index - fn_8000C648());

            pOut->mUnknown40 = fn_80023A3C(fn_80183354(), id);
            fn_80023988(id, pOut->mName, 22);
        }
        break;
    case 2:
        if (index < fn_8000C648()) {
            fn_801C3284(pOut->mName, lbl_802F4164[fn_8000C678(index)], 22);
        } else {
            int id = fn_80023CA4(fn_80183354(), index - fn_8000C648());

            pOut->mUnknown40 = fn_80023A3C(fn_80183354(), id);
            fn_80023988(id, pOut->mName, 22);
        }
        break;
    }
}

void fn_8000CEB4(int a)
{
    fn_8007DDC8(&lbl_8036A228, fn_8022F384(fn_8022F4BC()));
    lbl_803EB940 = a;
    if (a == 0) {
        fn_801835C8();
    } else {
        lbl_803ECDDC = fn_800808F8(fn_80182DC8());
        fn_800817CC(fn_80182DC8(), &lbl_8036A280);
    }
}

void fn_8000CF24()
{
    if (lbl_803EB940 == 0) {
        fn_80183704();
    }
    fn_8007DE20(&lbl_8036A228);
}

Class_8000DBA0 *fn_8000CF5C()
{
    return fn_8000D140();
}

static inline Class_8000DB50 *fn_8000D0A0()
{
    static Class_8000DB50 sInstance;
    return &sInstance;
}

static inline Class_8000DAB0 *fn_8000D0C8()
{
    static Class_8000DAB0 sInstance;
    return &sInstance;
}

static inline Class_8000DA10 *fn_8000D0F0()
{
    static Class_8000DA10 sInstance;
    return &sInstance;
}

static inline Class_8000D9C0 *fn_8000D118()
{
    static Class_8000D9C0 sInstance;
    return &sInstance;
}

static inline Class_8000DBA0 *fn_8000D140()
{
    static Class_8000DBA0 sInstance;
    return &sInstance;
}

static inline Class_8000D980 *fn_8000D168()
{
    static Class_8000D980 sInstance;
    return &sInstance;
}

static inline Class_8000D900 *fn_8000D198()
{
    static Class_8000D900 sInstance;
    return &sInstance;
}

static inline Class_8000DA60 *fn_8000D1C8()
{
    static Class_8000DA60 sInstance;
    return &sInstance;
}

static inline Class_8000D8C0 *fn_8000D1F0()
{
    static Class_8000D8C0 sInstance;
    return &sInstance;
}

static inline Class_8000DB00 *fn_8000D220()
{
    static Class_8000DB00 sInstance;
    return &sInstance;
}

static inline Class_8000D940 *fn_8000D248()
{
    static Class_8000D940 sInstance;
    return &sInstance;
}

static inline Class_8000DBF0 *GetClass_8000DBF0()
{
    static Class_8000DBF0 sInstance;
    return &sInstance;
}
