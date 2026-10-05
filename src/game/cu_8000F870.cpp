#include <string.h>

#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/Object_800785C0.h"
#include "game/cu_8003AEA8.h"
#include "game/cu_8003E214.h"
#include "game/cu_80181330.h"
#include "game/fn_8003B6BC.h"
#include "game/fn_80072AA8.h"
#include "game/fn_8007F6F8.h"
#include "game/fn_8007F828.h"
#include "game/fn_80178D18.h"
#include "game/fn_8017F584.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801C3284.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801FCE10.h"
#include "game/fn_802372EC.h"

/* Argument block passed to fn_802329F0 when saving the roster file (template.dat). */
struct Request_802329F0 {
    int mMode;
    int mSize;
    const char *mpName;
    int mCount;
};

/* Controller index of each of the two teams. */
struct Pair_803ECE48 {
    signed char mIndex[2];
};

/* One roster row of a team: the player id, the pick slot it fills (-1 when
   not picked), its position in the list and an auto-pick key (0xFF unset). */
struct Entry_8036AE60 {
    int mId;
    int mSlot;
    int mIndex;
    int mKey;
};

/* Roster of one team, followed by one more player id. */
struct Roster_8036AE60 {
    Entry_8036AE60 mEntries[20];
    int mUnknown140;
};

/* Scroll state of one team's roster list: the top row and the cursor row. */
struct Scroll_8036B0E8 {
    int mTop;
    int mRow;
};

/* Pair of bytes saved by fn_80014430 from the two fn_80011C1C results. */
struct Pair_803EB9D0 {
    unsigned char mUnknown0;
    unsigned char mUnknown1;
};

/* Two seven-entry position lists of one team, filled by fn_8003B5AC. */
struct Slots_8036B0F8 {
    int mUnknown0[7];
    int mUnknown1C[7];
};

/* One of the twelve 0xB8-byte records of the table at lbl_803EB9DC, filled by fn_800156B4. */
struct Entry_803EB9DC {
    char mText0[0x21];
    char mText21[0x21];
    char mText42[0x66];
    int mUnknownA8;
    int mUnknownAC;
    int mUnknownB0;
    unsigned char mUnknownB4;
    unsigned char mValid;
};

/* Block allocated by fn_80016248: thirteen column values, three more
   values (the third a signed win/loss streak) and a name. */
struct Stats_803EB9E8 {
    int mValues[13];
    int mUnknown34;
    int mUnknown38;
    int mStreak;
    char mName[16];
};

/* Record filled by fn_80088CE0. */
struct Record_80088CE0 {
    signed char mIndex;
    char mName[147];
    int mUnknown94;
};

/* Pointer list read by fn_8003B234 (src/game/cu_8003AEA8.cpp). */
struct Pair_8003AEA8;

void *operator new(unsigned int size, int unknown);

extern "C" {
void fn_80004440(int *pId);
int fn_8000485C(void);
int fn_8001B354(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
void fn_8001B228(void);
void fn_8001B260(int a, int b);
void fn_8001B330(int a);
void fn_8001B828(void);
void fn_8001ED90(unsigned char value);
int fn_80023514(void);
void fn_80023560(void);
void fn_800235DC(void);
void fn_80023634(int *pCount);
void fn_80023684(char *pDest, int count);
void fn_800236B0(int *pValue);
int fn_80025708(void);
int fn_80025718(void);
unsigned char fn_8002892C(void);
void fn_8003B0F8(int group, int kind, int slot, int code, int a, int b);
void fn_8003B1F4(int group);
void fn_8003B234(int group, int kind, Pair_8003AEA8 **pPairs);
void fn_8003B2D0(int group, int kind, int slot);
void fn_8003B584(int group, int value, int index0, int index1);
int fn_8003B5AC(int group, int value, int *pFirst, int *pSecond);
void fn_8003DE74(int team, int *pList);
void fn_80054CA8(int a);
void fn_80054CFC(void);
int fn_800551D8(unsigned char a);
void fn_800551E0(unsigned char a, int b, char *pText, int length);
void fn_80055230(unsigned char a, int b, int c, int *pList0, int *pList1, char *pText, int length);
int fn_8006270C(void);
void fn_80062A58(unsigned char a);
void fn_8006CA18(int index, int a, unsigned char volume);
void fn_80073094(void);
void fn_800731D0(int a);
int fn_8007A43C(Object_8007A334 *pObject);
void fn_8007A4A4(Object_8007A334 *pObject);
int fn_8007A588(Object_8007A334 *pObject);
int fn_8007A934(Object_8007A334 *pObject, int key);
int fn_8007AF84(int team);
int fn_8007B518(int index, int id);
void fn_8007B684(int id);
void fn_8007B6D4(void);
void fn_8007B6FC(int *pA, int *pB);
void fn_8007B8A4(char *pDest, int count);
void fn_8007B904(int a, int b);
void fn_8007B93C(int a, int b);
void fn_8007C9D4(void);
void fn_8007CAB4(void);
unsigned char fn_8007CAE4(void);
void fn_8007CAEC(int index, int value);
int fn_8007CB6C(int index);
void fn_8007D4E8(void);
void fn_8007D52C(void);
int fn_8007D5A0(int type, int value, int column, char *pText, int size);
void fn_8007DB74(int a, int b);
int fn_8007DBB4(int a);
void fn_8007DDC0(int a);
void fn_8007EBDC(Object_8007A334 *pObject, int db);
void fn_8007EC34(Object_8007A334 *pObject);
int fn_8007EC54(Object_8007A334 *pObject, int id);
int fn_800808F8(Object_8008044C *pObject);
void fn_80080B08(Object_8008044C *pObject, char *pBuffer, int size);
void fn_80080BEC(Object_8008044C *pObject, char *pBuffer, int size);
int fn_80080D10(Object_8008044C *pObject);
int fn_80081188(Object_8008044C *pObject);
int fn_800812E0(Object_8008044C *pObject, int index);
void fn_80081F50(Object_8008044C *pObject, int team, int a);
void fn_80082558(int a, int b);
void fn_80083E1C(Object_8007A334 *pObject, Query_80083E40 *pQuery);
int fn_80083FBC(Object_8007A334 *pObject);
int fn_8008406C(Object_8007A334 *pObject, int id, int *pResult);
int fn_800841AC(Object_8007A334 *pObject);
int fn_800841D8(Object_8007A334 *pObject);
int fn_80084204(Object_8007A334 *pObject);
int fn_800842E8(Object_8007A334 *pObject);
int fn_80084310(Object_8007A334 *pObject);
int fn_80084338(Object_8007A334 *pObject);
void fn_80087BE4(Object_8007A334 *pObject, int index);
void fn_80087C3C(Object_8007A334 *pObject);
int fn_80087C8C(Object_8007A334 *pObject, unsigned int index);
unsigned int fn_800886BC(int a);
int fn_8008872C(int a);
void fn_80088950(Object_8007A334 *pObject, int index);
void fn_80088A1C(Object_8007A334 *pObject);
int fn_80088A74(Object_8007A334 *pObject, int index);
void fn_80088B24(Object_8007A334 *pObject, int a, unsigned char b);
void fn_80088C8C(Object_8007A334 *pObject);
void fn_80088CE0(Object_8007A334 *pObject, Record_80088CE0 *pRecord);
void fn_800A2F3C(int a);
int fn_800A3444(void);
int fn_801485D4(void);
int fn_801486A0(void);
void fn_80148AF8(Class_80148A58 *pObject);
int fn_8017F60C(void);
void fn_8017F670(int a, char *pText);
int fn_80178308(void);
int fn_80178320(void);
int fn_801801B4(void);
void fn_801801C4(int a);
void fn_801801C8(int a);
void fn_80183368(int mode, int value);
void fn_801834DC(void);
int fn_801835A0(void);
void fn_80183934(void);
int fn_801869F0(void);
int fn_80186A10(int index, char *pText);
signed char fn_80186B38(int a);
int fn_80186DF0(signed char *pIndices, int length);
void fn_80186F30(signed char a, unsigned char b);
int fn_80186F7C(unsigned char index);
void fn_80186F8C(int a);
void fn_80187A28(unsigned char index, char *pText);
int fn_80187A78(unsigned char index, char *pText, int length);
unsigned char fn_80187C64(void);
void fn_8018801C(int index, int value);
int fn_80188030(int a);
int fn_80188044(int index);
void fn_8018807C(unsigned char a);
void fn_80188CBC(int index, int a, int b, int c, const unsigned char *pColor);
int fn_8018BD9C(int a);
void fn_8018C230(int a, int b);
void fn_8018C48C(int tag);
int fn_8018D720(int a);
void fn_8018D7E0(void);
int fn_8018F228(int a);
int fn_8018F2F4(int a, int b);
int fn_8018F3D8(int a);
int fn_801C2D88(char *pBuffer, int size, const char *pFormat, ...);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
char *fn_801C3084(const char *pString, int c);
unsigned int fn_801C3180(const char *pText);
int fn_801C6458(int a, int b);
int fn_801E15D0(int a);
unsigned int fn_801E1954(void);
int fn_801E195C(int a);
void fn_801E1BE8(void);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);
int fn_8021E2B4(void *pObject, int a, int b);
void fn_8021E72C(void *pObject, int a, int b);
void *fn_8021EA44(int index);
void fn_802293B4(int a, int b);
void fn_802293FC(void);
void fn_80229438(int tag, int a);
int fn_802294F4(void);
int fn_80229554(void);
void fn_8022A490(int a);
int fn_8022A508(int a, int b, int c, int d, int e);
int fn_8022C8F0(unsigned int low, unsigned int high);
void fn_8022DC7C(int a);
void fn_8022DCB0(int a);
void fn_8022DCE4(int a);
void fn_8022DD18(int a);
int fn_8022F358(int index);
int fn_8022F384(int a);
int fn_8022F4BC(void);
void fn_802329F0(Request_802329F0 *pRequest);

extern char lbl_802EBE24[];
extern void *lbl_803EB688;

int fn_8000FE60(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
void fn_80010150(int mode);
void fn_800102D8(void);
int fn_800103A4(int force);
void fn_80010B78(void);
int fn_80011344(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int fn_80011AA8(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
void fn_80011D9C(Object_8007A334 *pObject, int side);
int fn_80011FA0(int side, int id);
int fn_80012244(int side);
int fn_80014260(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int fn_80014430(int *pCount1, int *pCount0, int *pMode, int *pFlag);
void fn_80014AA8(int team, int id);
void fn_80014B98(void);
void fn_80014FD8(int team);
void fn_80015000(int team, int *pList);
void fn_800150FC(int team, int index, char *pBuffer, int size);
int fn_800151C0(int team, int *pNext, int id);
void fn_800153A0(int team, int *pIndex, int id);
void fn_80015420(int team, int *pIndex);
void fn_800155CC(int team);
void fn_80015654(unsigned char value);
void fn_8001565C(int team, int slot, int *pId);
int fn_80015B68(int *pIndex, int any);
int fn_80015BF8(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
void fn_80015D28(int id);
int fn_80015E24(unsigned int index);
int fn_80015EB8(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int fn_8001642C(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int fn_80016730(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int fn_80016950(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int fn_80016DF4(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);

extern const char *lbl_802F41BC[];
extern int lbl_802F41C8[][5];
extern int lbl_802F43A8[];
extern unsigned char lbl_802F43D8[];
extern const char *lbl_802F43E4[];

unsigned char lbl_803EB950 = 0;
unsigned char lbl_803EB951 = 0;
int lbl_803EB954 = 0;
unsigned char lbl_803EB958 = 0;
int lbl_803EB95C = 0;
int lbl_803EB960 = 0;
int lbl_803EB964 = -1;
unsigned char lbl_803EB968 = 1;
unsigned char lbl_803EB969 = 4;
unsigned char lbl_803EB96A = 1;
unsigned char lbl_803EB96C[4] = { 3, 3, 3, 3 };
unsigned char lbl_803EB970 = 0;
unsigned char lbl_803EB971 = 0;
int lbl_803EB974 = 7;
unsigned char lbl_803EB978[2] = { 0, 0 };
int lbl_803EB97C[2] = { -1, -1 };
int lbl_803EB984[2] = { -1, -1 };
int lbl_803EB98C[2] = { -1, -1 };
int *lbl_803EB994[2] = { 0, 0 };
unsigned char lbl_803EB99C = 0;
int lbl_803EB9A0[2] = { -1, -1 };
int lbl_803EB9A8 = -1;
unsigned char lbl_803EB9AC[2] = { 1, 1 };
unsigned char lbl_803EB9B0[2] = { 1, 1 };
int lbl_803EB9B4[2] = { -1, -1 };
unsigned char lbl_803EB9BC[2] = { 1, 1 };
unsigned char lbl_803EB9C0[2] = { 1, 1 };
int lbl_803EB9C4[2] = { 0, 0 };
unsigned char lbl_803EB9CC = 1;
unsigned char lbl_803EB9D0[2] = { 0, 0 };
unsigned char lbl_803EB9D2 = 1;
int lbl_803EB9D4[2] = { -1, -1 };
Entry_803EB9DC *lbl_803EB9DC = 0;
int lbl_803EB9E0 = -1;
unsigned char lbl_803EB9E4 = 1;
unsigned char lbl_803EB9E5 = 1;
unsigned char lbl_803EB9E6 = 0;
signed char lbl_803EB9E7 = -1;
Stats_803EB9E8 *lbl_803EB9E8 = 0;
signed char lbl_803EB9EC = -1;
unsigned char lbl_803EB9ED = 2;
int lbl_803EB9F0 = 0;
int lbl_803EB9F4 = 0;
unsigned char lbl_803EB9F8 = 1;
unsigned char lbl_803EB9F9 = 0;
unsigned char lbl_803EB9FA = 0;
unsigned char lbl_803EB9FB = 0;
signed char lbl_803EB9FC = -1;
signed char lbl_803EB9FD = 0;
signed char lbl_803EB9FE = 0;
Object_8007A334 *lbl_803EBA00 = 0;
Object_8007A334 *lbl_803EBA04 = 0;

unsigned char lbl_803ECE38[8];
unsigned char lbl_803ECE40[4];
unsigned char lbl_803ECE44[4];
Pair_803ECE48 lbl_803ECE48;
int **lbl_803ECE4C;
int lbl_803ECE50[2];

Object_8007A334 lbl_8036ADB0[2];
Object_8008044C lbl_8036AE08[2];
Roster_8036AE60 lbl_8036AE60[2];
Scroll_8036B0E8 lbl_8036B0E8[2];
Slots_8036B0F8 lbl_8036B0F8[2];

int fn_8000F870(int module, unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    switch (module) {
    case 1:
        return fn_8000FE60(id, pArgs, count, pResult);
    case 3:
        return fn_80015EB8(id, pArgs, count, pResult);
    case 17:
        return fn_80011344(id, pArgs, count, pResult);
    case 7:
        return fn_80014260(id, pArgs, count, pResult);
    case 8:
        return fn_80015BF8(id, pArgs, count, pResult);
    case 9:
        return fn_8001B354(id, pArgs, count, pResult);
    case 12:
        return fn_80011AA8(id, pArgs, count, pResult);
    case 11:
        return fn_8001642C(id, pArgs, count, pResult);
    case 4:
        return fn_80016730(id, pArgs, count, pResult);
    case 15:
        return fn_80016950(id, pArgs, count, pResult);
    case 16:
        return fn_80016DF4(id, pArgs, count, pResult);
    }
    return 0;
}

void fn_8000FA0C(void)
{
    fn_80054CFC();
    if (!lbl_803EB951) {
        lbl_803EB951 = 1;
        if (fn_801835A0()) {
            fn_801834DC();
        }
        fn_80183934();
        if (!fn_80027E90()) {
            fn_80027E88(1);
        }
        fn_8018C48C(0x54415453);
        fn_8018C48C(0x454D4147);
        fn_80027EA0();
        if (fn_8007CAE4()) {
            fn_8007CAB4();
        }
        if (fn_802294F4()) {
            fn_80229554();
        }
        if (fn_80187C64() && !fn_801869F0() && !fn_80027EAC()) {
            fn_80010150(11);
        }
    }
}

void fn_8000FAD0(int mode)
{
    int save = 1;
    Request_802329F0 request;

    if (lbl_803EB951) {
        fn_80015654(0);
        switch (mode) {
        case 0:
            if (lbl_803EB958) {
                request.mMode = 1;
            } else {
                request.mMode = mode;
            }
            break;
        case 8:
            fn_80186F30(fn_80186B38(fn_8022F4BC()), 1);
            fn_80186F30(-1, 0);
            /* fall through */
        case 2:
        case 6:
        case 7:
        case 9:
        case 10:
        case 11:
        case 12:
            request.mMode = mode;
            lbl_803EB958 = 0;
            break;
        case 3:
        case 4:
        case 5:
        case 13:
            save = 0;
            break;
        default:
            save = 0;
            break;
        }
        if (save) {
            request.mSize = 0x96000;
            request.mpName = lbl_802EBE24;
            request.mCount = 1;
            if (fn_802294F4()) {
                fn_800731D0(0);
                fn_80229554();
            }
            switch (mode) {
            case 0:
            case 2:
            case 6:
                fn_802329F0(&request);
                fn_8007C9D4();
                if (lbl_803EB958) {
                    fn_801FCE10(0, "update 'FNIG' set 'YTPG' = \x82\n", lbl_803EB95C);
                }
                fn_80229438(0x544E464F, 2);
                fn_8022A490(2);
                break;
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
                fn_800731D0(1);
                fn_800731D0(0);
                fn_802329F0(&request);
                fn_800731D0(1);
                fn_800731D0(0);
                fn_8007C9D4();
                fn_800731D0(0);
                fn_80229438(0x544E464F, 2);
                fn_800731D0(0);
                fn_8022A490(2);
                break;
            }
        } else if (lbl_803EB950) {
            fn_80015654(1);
        }
        lbl_803EB951 = 0;
    }
    lbl_803EB964 = -1;
}

int fn_8000FCCC(void)
{
    return lbl_803EB954;
}

void fn_8000FCD4(int a)
{
    lbl_803EB954 = a;
}

int fn_8000FCDC(void)
{
    int current = fn_8000FCCC();
    int count = 0;
    int first = 8;
    int found = 0;
    int assigned = fn_80188030(current);
    int limit;
    int i;

    fn_801E1BE8();
    if (fn_801E1954() < 8) {
        limit = fn_801E1954();
    } else {
        limit = 8;
    }
    for (i = 0; i < limit; i++) {
        if (fn_801E195C(i)) {
            fn_801E15D0(i);
        }
    }
    for (i = 0; i <= 7; i++) {
        if (fn_801E195C(fn_801C6458(i, 0)) == 2) {
            fn_8018801C(i, count);
            count++;
            found = 1;
            if (first == 8) {
                first = i;
            }
        } else {
            fn_8018801C(i, -1);
        }
    }
    int connected = fn_801E195C(fn_801C6458(current, 0)) == 2;
    if (!found) {
        int value = 0;
        if (assigned != -1 && assigned <= 3) {
            value = assigned;
        }
        fn_8018801C(current, value);
    } else if (assigned == -1 && connected) {
        found = 0;
    } else if (assigned == -1 || assigned > 3) {
        found = 0;
        fn_8000FCD4(first);
    } else if (!connected) {
        fn_8018801C(current, assigned);
        found = 0;
    }
    return found;
}

int fn_8000FE60(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        if (lbl_803EB950) {
            fn_801834DC();
            fn_80027EA0();
            lbl_803EB950 = 0;
        }
        fn_8000FA0C();
        break;
    case 0x80000002:
        fn_8000FAD0(pArgs[0].i);
        break;
    case 0x80000003:
        fn_8000FCD4(pArgs[0].i);
        break;
    case 0x80000004:
        lbl_803EB958 = 1;
        lbl_803EB95C = 0;
        break;
    case 0x80000006:
        lbl_803EB958 = 1;
        lbl_803EB95C = 1;
        break;
    case 0x80000005:
        lbl_803EB958 = 0;
        break;
    case 0x80000007:
        switch (pArgs[0].i) {
        case 900:
            lbl_803EB950 = 1;
            fn_80183368(2, 0x3FF);
            break;
        case 750:
            lbl_803EB950 = 1;
            break;
        case 751:
            lbl_803EB950 = 1;
            fn_80183368(4, 0x3FF);
            break;
        case 752:
            lbl_803EB950 = 1;
            fn_80183368(1, 0x3FF);
            break;
        }
        *pResult = 1;
        break;
    case 0x80000008:
        break;
    case 0x8000000A:
        fn_801801C4(pArgs[0].i);
        break;
    case 0x8000000B:
        lbl_803EB960 = pArgs[0].i;
        break;
    case 0x8000000C:
        fn_800731D0(1);
        fn_800731D0(0);
        break;
    case 0x8000000D:
        *pResult = 0;
        break;
    case 0x80000000:
        fn_801C2EF0(pArgs[0].pParams->mpText, "", pArgs[0].pParams->mLength);
        break;
    case 0x8000000F:
        fn_80027EB4(0);
        break;
    case 0x80000010:
        *pResult = lbl_803EB964;
        lbl_803EB964 = -1;
        break;
    case 0x80000011:
        *pResult = 1;
        switch (pArgs[0].i) {
        case 751:
            *pResult = fn_8018BD9C(fn_8022F384(fn_8022F4BC()));
            break;
        case 752:
            *pResult = fn_8018D720(fn_8022F384(fn_8022F4BC()));
            break;
        }
        break;
    case 0x80000009:
        *pResult = fn_8018D720(fn_8022F384(fn_8022F4BC()));
        break;
    default:
        return 0;
    }
    return 1;
}

void fn_80010150(int mode)
{
    unsigned char saved = fn_80027E90();
    fn_8000FA0C();
    fn_8000FAD0(mode);
    fn_80027E88(saved);
}

int fn_80010194(void)
{
    unsigned short a = 0;
    unsigned short b = 0;
    int result;

    fn_80219650(lbl_803EB688, &a, &b);
    result = 0;
    if (a == 0 && b == 1 && lbl_803EB951) {
        result = lbl_803EB960 == 0;
    }
    return result;
}

void fn_80010200(int value)
{
    lbl_803EB964 = value;
}

void fn_80010208(void)
{
    fn_8018807C(0);
    switch (fn_801486A0()) {
    case 0:
    case 1:
        lbl_803EB968 = 0;
        break;
    default:
        unsigned int type = fn_8017F584();
        if (type == 6 || type == 8) {
            lbl_803EB968 = 0;
        } else {
            lbl_803EB968 = 1;
        }
        break;
    }
    switch (fn_801486A0()) {
    case 2:
    case 3:
        lbl_803EB969 = 2;
        break;
    default:
        lbl_803EB969 = 4;
        break;
    }
    fn_800102D8();
    int state = fn_801801B4();
    if (state == 1) {
        fn_800103A4(1);
        lbl_803EB96A = state;
    }
    if (fn_80025708() || fn_80025718()) {
        lbl_803EB96A = fn_8007CB6C(2);
    }
}

void fn_800102D8(void)
{
    Pair_803ECE48 previous = lbl_803ECE48;

    fn_80186DF0(lbl_803ECE48.mIndex, 2);
    for (unsigned char i = 0; i <= 3; i++) {
        if (lbl_803EB96C[i] <= 1) {
            unsigned char j;
            for (j = 0; j <= 1; j++) {
                if (previous.mIndex[lbl_803EB96C[i]] == lbl_803ECE48.mIndex[j]) {
                    lbl_803EB96C[i] = j;
                    break;
                }
            }
            if (j == 2 || lbl_803ECE48.mIndex[lbl_803EB96C[i]] == -1) {
                lbl_803EB96C[i] = 3;
            }
        }
    }
}

int fn_800103A4(int force)
{
    unsigned char changed = 0;
    int i;
    int j;
    unsigned char k;
    int start;
    unsigned int count;
    unsigned char used[2];

    fn_801E1BE8();
    count = 0;
    for (i = 0; i <= 7; i++) {
        unsigned char present = fn_801E195C(fn_801C6458(i, 0)) == 2;
        if (present && count <= 3) {
            count++;
        } else {
            present = 0;
        }
        if (!changed) {
            changed = lbl_803ECE38[i] != present;
        }
        lbl_803ECE38[i] = present;
    }
    for (j = 0; j <= 9; j++) {
        fn_8018801C(j, -1);
    }
    j = 0;
    for (i = 0; i <= 7; i++) {
        if (lbl_803ECE38[i] && j <= 3) {
            fn_8018801C(i, j);
            j++;
        }
    }
    if (changed || force) {
        for (j = 0; j < 4; j++) {
            if (!lbl_803ECE38[j]) {
                lbl_803EB96C[j] = 3;
            }
        }
        for (k = 0; k <= 1; k++) {
            used[k] = 0;
        }
        for (j = 0; j < 4; j++) {
            if (lbl_803EB96C[j] <= 1) {
                used[lbl_803EB96C[j]] = 1;
            }
        }
        k = 0;
        start = fn_80188030(fn_8000FCCC());
        if (start == -1) {
            start = 0;
        }
        for (i = 0; i <= 3; i++) {
            j = (i + start) % 4;
            int pad = fn_80188044(j);
            if (pad != -1 && lbl_803ECE38[pad] && lbl_803EB96C[j] > 2) {
                do {
                    if (k < fn_801869F0() && lbl_803ECE48.mIndex[k] != -1) {
                        lbl_803EB96C[j] = k++;
                    } else {
                        lbl_803EB96C[j] = 3;
                    }
                } while (used[lbl_803EB96C[j]] && lbl_803EB96C[j] != 3);
            }
        }
        for (j = 0; j <= 3; j++) {
            lbl_803ECE40[j] = 1;
            lbl_803ECE44[j] = 0;
            fn_80187A28(j, 0);
        }
        if (force) {
            for (j = 0; j < 4; j++) {
                if (lbl_803EB96C[j] == 2) {
                    lbl_803EB96C[j] = 3;
                }
            }
            j = fn_80188030(fn_8000FCCC());
            if (j != -1) {
                if (lbl_803EB968) {
                    lbl_803ECE40[j] = 0;
                } else {
                    lbl_803ECE40[j] = 2;
                }
            }
            fn_80010B78();
        }
    }
    return changed || force;
}

void fn_800106B8(int *pA, int *pB)
{
    if (lbl_803EB968) {
        *pA = 1;
    } else {
        *pA = 2;
    }
    switch (fn_8017F584()) {
    case 2:
        *pB = 1;
        break;
    case 9:
        if (fn_801486A0() == 2) {
            *pB = 1;
        } else {
            *pB = 0;
        }
        break;
    default:
        *pB = 0;
        break;
    }
}

int fn_80010730(int index, int dir)
{
    int result = 0;
    unsigned char count = 0;

    for (unsigned char i = 0; i <= 3; i++) {
        switch (dir) {
        case 1:
            if (lbl_803ECE40[i] == 2) {
                count++;
            }
            break;
        case 3:
            if (lbl_803ECE40[i] == 0) {
                count++;
            }
            break;
        }
    }
    int isLeft = lbl_803ECE40[index] == 0;
    int isRight = lbl_803ECE40[index] == 2;
    switch (dir) {
    case 3:
        if (!isLeft && (isRight || (lbl_803EB968 && count < lbl_803EB969))) {
            result = 1;
        }
        break;
    case 1:
        if (!isRight) {
            if (!isLeft) {
                if (count < lbl_803EB969) {
                    result = 1;
                }
            } else {
                result = 1;
            }
        }
        break;
    }
    return result;
}

int fn_800107FC(int index, int dir)
{
    int moved = fn_80010730(index, dir);

    if (moved) {
        switch (dir) {
        case 3:
            switch (lbl_803ECE40[index]) {
            case 1:
                lbl_803ECE40[index] = 0;
                break;
            case 2:
                lbl_803ECE40[index] = 1;
                break;
            }
            break;
        case 1:
            switch (lbl_803ECE40[index]) {
            case 1:
                lbl_803ECE40[index] = 2;
                break;
            case 0:
                lbl_803ECE40[index] = 1;
                break;
            }
            break;
        }
    }
    fn_80010B78();
    return moved;
}

int fn_800108A8(int index)
{
    int result = 3;

    switch (lbl_803EB96C[index]) {
    case 3:
        break;
    case 4:
        if (lbl_803ECE44[index] == 1) {
            result = 2;
        }
        break;
    case 5:
        switch (lbl_803ECE44[index]) {
        case 1:
            result = 0;
            break;
        case 2:
            result = 1;
            break;
        }
        break;
    }
    return result;
}

void fn_80010914(void)
{
    char text[16];
    int i;

    fn_802293FC();
    for (i = 0; i <= 3; i++) {
        int pad = fn_80188044(i);
        if (pad != -1) {
            if (lbl_803ECE40[i] == 2) {
                if (lbl_803EB968) {
                    fn_802293B4(0, pad);
                } else {
                    fn_802293B4(1, pad);
                }
            } else if (lbl_803ECE40[i] == 0) {
                fn_802293B4(1, pad);
            }
        }
    }
    fn_80186F8C(0);
    if (fn_8017F584() != 6 && fn_8017F584() != 8 && fn_8017F584() != 7 && fn_8017F584() != 11) {
        fn_80186F8C(1);
        if (fn_801486A0() != 0 && fn_801486A0() != 1) {
            for (i = 0; i <= 3; i++) {
                if (lbl_803ECE44[i] == 1 && lbl_803EB96C[i] <= 1) {
                    if (lbl_803ECE40[i] == 0) {
                        fn_80186F30(lbl_803ECE48.mIndex[lbl_803EB96C[i]], 1);
                    } else {
                        fn_80186F30(lbl_803ECE48.mIndex[lbl_803EB96C[i]], 0);
                    }
                    fn_80054CA8(lbl_803ECE48.mIndex[lbl_803EB96C[i]]);
                }
            }
        } else {
            int team = 0;
            for (i = 0; i <= 3; i++) {
                switch (lbl_803ECE44[i]) {
                case 1:
                    if (lbl_803EB96C[i] <= 1) {
                        fn_80186A10(lbl_803ECE48.mIndex[lbl_803EB96C[i]], text);
                        fn_80187A28(i, text);
                    } else {
                        fn_80187A28(i, 0);
                    }
                    if (lbl_803EB96C[i] != 3 && team <= 1) {
                        fn_80186F30(lbl_803ECE48.mIndex[lbl_803EB96C[i]], team);
                        team++;
                    }
                    break;
                case 2:
                    if (lbl_803EB96C[i] != 2) {
                        fn_80187A28(i, 0);
                    }
                    break;
                default:
                    fn_80187A28(i, 0);
                    break;
                }
            }
        }
    }
    fn_8007CAEC(2, lbl_803EB96A);
    fn_8006CA18(0x8F, 0x32, 0);
    if (fn_801801B4() == 1) {
        fn_8018807C(1);
    }
}

void fn_80010B78(void)
{
    unsigned char i;
    unsigned char j;
    unsigned char n;

    switch (fn_801486A0()) {
    case 0:
    case 1:
        for (i = 0; i <= 3; i++) {
            if (lbl_803ECE40[i] == 2) {
                if (lbl_803ECE44[i] == 0) {
                    n = 0;
                    for (j = 0; j <= 3; j++) {
                        if (lbl_803ECE44[j] == 1) {
                            n++;
                        }
                    }
                    if (n <= 1) {
                        lbl_803ECE44[i] = 1;
                        if (lbl_803EB96C[i] == 2) {
                            lbl_803EB96C[i] = 3;
                        }
                    } else {
                        lbl_803ECE44[i] = 2;
                        if (lbl_803EB96C[i] <= 1 || lbl_803EB96C[i] == 4) {
                            lbl_803EB96C[i] = 3;
                        }
                    }
                }
            } else {
                lbl_803ECE44[i] = 0;
            }
        }
        break;
    default:
        for (i = 0; i <= 3; i++) {
            lbl_803ECE44[i] = 0;
            if (lbl_803ECE40[i] != 1) {
                int unique = 1;
                for (j = 0; j < i; j++) {
                    if (lbl_803ECE40[j] == lbl_803ECE40[i]) {
                        unique = 0;
                        break;
                    }
                }
                if (unique) {
                    lbl_803ECE44[i] = 1;
                }
            }
        }
        break;
    }
}

int fn_80010CF4(int index)
{
    int result = -1;

    switch (lbl_803ECE40[index]) {
    case 0:
        result = 1;
        break;
    case 1:
        break;
    case 2:
        if (lbl_803EB968) {
            result = 0;
            break;
        }
        switch (fn_801486A0()) {
        case 0:
        case 1:
            if (lbl_803ECE44[index] == 1) {
                for (unsigned char j = 0; j <= 3; j++) {
                    if (j == index) {
                        result = 1;
                        break;
                    }
                    if (lbl_803ECE44[j] == 1) {
                        result = 0;
                        break;
                    }
                }
            }
            break;
        default:
            result = 1;
            break;
        }
        break;
    }
    return result;
}

void fn_80010DC4(int index, int pad)
{
    fn_800102D8();
    if (pad >= 0 && pad < fn_801869F0()) {
        switch (lbl_803ECE44[index]) {
        case 1:
            for (unsigned char j = 0; j <= 1; j++) {
                if (lbl_803ECE48.mIndex[j] == pad) {
                    lbl_803EB96C[index] = j;
                    break;
                }
            }
            break;
        case 2:
            lbl_803EB96C[index] = 2;
            break;
        }
    }
}

const char *lbl_802F41BC[] = { "None", "Load", "Create" };

void fn_80010E68(int index, int dir, Arg_8018399C arg)
{
    Params_80005284 *pParams = arg.pParams;

    fn_800102D8();
    switch (lbl_803ECE44[index]) {
    case 1: {
        switch (dir) {
        case 2:
            if (lbl_803EB96C[index] == 5) {
                lbl_803EB96C[index] = 0;
            } else {
                lbl_803EB96C[index]++;
            }
            while (lbl_803EB96C[index] <= 2 && lbl_803EB96C[index] >= fn_801869F0()) {
                lbl_803EB96C[index]++;
            }
            break;
        case 0:
            if (lbl_803EB96C[index] == 0) {
                lbl_803EB96C[index] = 5;
            } else {
                lbl_803EB96C[index]--;
            }
            while (lbl_803EB96C[index] <= 2 && lbl_803EB96C[index] >= fn_801869F0()) {
                if (lbl_803EB96C[index] == 0) {
                    lbl_803EB96C[index] = 5;
                } else {
                    lbl_803EB96C[index]--;
                }
            }
            break;
        case -1:
            break;
        default:
            lbl_803EB96C[index] = 3;
            dir = -1;
            break;
        }
        int again = 1;
        while (dir != -1 && lbl_803EB96C[index] <= 1 && again) {
            int j;
            for (j = 0; j <= 3; j++) {
                if (j != index && lbl_803EB96C[j] == lbl_803EB96C[index]) {
                    if (lbl_803ECE44[j] == 1) {
                        if (dir == 0) {
                            if (lbl_803EB96C[index] == 0) {
                                lbl_803EB96C[index] = 5;
                            } else {
                                lbl_803EB96C[index]--;
                            }
                        } else {
                            lbl_803EB96C[index]++;
                            if (lbl_803EB96C[index] >= fn_801869F0()) {
                                lbl_803EB96C[index] = 3;
                            }
                        }
                        break;
                    }
                    if (lbl_803ECE44[j] == 0) {
                        lbl_803EB96C[j] = 3;
                    }
                }
            }
            if (j == 4) {
                again = 0;
            }
        }
        if (lbl_803EB96C[index] <= 1) {
            fn_80186A10(lbl_803ECE48.mIndex[lbl_803EB96C[index]], pParams->mpText);
        } else {
            fn_801C2EF0(pParams->mpText, lbl_802F41BC[lbl_803EB96C[index] - 3], pParams->mLength);
        }
        break;
    }
    case 2:
        switch (dir) {
        case 0:
            switch (lbl_803EB96C[index]) {
            case 3:
                if (fn_80187A78(index, 0, 0)) {
                    lbl_803EB96C[index] = 2;
                } else {
                    lbl_803EB96C[index] = 5;
                }
                break;
            case 2:
                lbl_803EB96C[index] = 5;
                break;
            case 5:
                lbl_803EB96C[index] = 3;
                break;
            default:
                lbl_803EB96C[index] = 3;
                break;
            }
            break;
        case 2:
            switch (lbl_803EB96C[index]) {
            case 3:
                lbl_803EB96C[index] = 5;
                break;
            case 5:
                if (fn_80187A78(index, 0, 0)) {
                    lbl_803EB96C[index] = 2;
                } else {
                    lbl_803EB96C[index] = 3;
                }
                break;
            case 2:
                lbl_803EB96C[index] = 3;
                break;
            default:
                lbl_803EB96C[index] = 3;
                break;
            }
            break;
        case -1:
            break;
        default:
            lbl_803EB96C[index] = 3;
            break;
        }
        if (lbl_803EB96C[index] == 2) {
            fn_80187A78(index, pParams->mpText, pParams->mLength);
        } else {
            fn_801C2EF0(pParams->mpText, lbl_802F41BC[lbl_803EB96C[index] - 3], pParams->mLength);
        }
        break;
    default:
        pParams->mpText[0] = 0;
        break;
    }
}

int fn_80011224(int *pA, int *pB, int *pC, int *pD)
{
    int result = fn_800103A4(0);
    int index;

    index = fn_80188044(0);
    *pA = index != -1 ? lbl_803ECE38[index] : 0;
    index = fn_80188044(1);
    *pB = index != -1 ? lbl_803ECE38[index] : 0;
    index = fn_80188044(2);
    *pC = index != -1 ? lbl_803ECE38[index] : 0;
    index = fn_80188044(3);
    *pD = index != -1 ? lbl_803ECE38[index] : 0;
    return result;
}

void fn_800112F8(int a, int *pB, int *pC)
{
    *pB = fn_80010730(a, 3);
    *pC = fn_80010730(a, 1);
}

int fn_80011344(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80010208();
        break;
    case 0x80000003:
        fn_800106B8(pArgs[0].pi, pArgs[1].pi);
        break;
    case 0x80000002:
        fn_80010914();
        break;
    case 0x80000004:
        *pResult = fn_800107FC(pArgs[0].i, pArgs[1].i);
        break;
    case 0x8000000C:
        *pResult = fn_80010CF4(pArgs[0].i);
        break;
    case 0x8000000D:
        *pResult = fn_800108A8(pArgs[0].i);
        break;
    case 0x8000000A:
        fn_80187A28(pArgs[0].i, pArgs[1].pParams->mpText);
        break;
    case 0x80000007:
        if (pArgs[0].i == 2) {
            lbl_803EB96A = 0;
        } else {
            lbl_803EB96A = 1;
        }
        break;
    case 0x80000010:
        if (lbl_803EB96A == 0) {
            *pResult = 2;
        } else {
            *pResult = 0;
        }
        break;
    case 0x8000000F:
        fn_80010DC4(pArgs[0].i, pArgs[1].i);
        break;
    case 0x80000008:
        fn_80010E68(pArgs[0].i, pArgs[1].i, pArgs[2]);
        break;
    case 0x80000005:
        *pArgs[0].pi = lbl_803ECE40[0];
        *pArgs[1].pi = lbl_803ECE40[1];
        *pArgs[2].pi = lbl_803ECE40[2];
        *pArgs[3].pi = lbl_803ECE40[3];
        break;
    case 0x80000009: {
        unsigned int state = fn_8017F584();
        if (state == 6 || state == 8) {
            *pResult = 0;
        } else if (lbl_803ECE44[pArgs[0].i]) {
            *pResult = 1;
        } else {
            *pResult = 0;
        }
        break;
    }
    case 0x80000006:
        *pResult = fn_80011224(pArgs[0].pi, pArgs[1].pi, pArgs[2].pi, pArgs[3].pi);
        break;
    case 0x8000000E:
        fn_800112F8(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x80000011:
        fn_8018807C(pArgs[0].i);
        break;
    case 0x8000000B:
        break;
    default:
        return 0;
    }
    return 1;
}

void fn_80011600(int pad0, int pad1, int keep)
{
    fn_801801C8(1);
    if (keep) {
        fn_80010208();
    } else {
        fn_800102D8();
        for (int i = 0; i < 4; i++) {
            lbl_803ECE40[i] = 1;
            lbl_803ECE44[i] = 0;
            lbl_803EB96C[i] = 3;
        }
        if (pad0 != -1) {
            if (fn_80188030(pad0) == -1 || fn_80188030(pad0) > 3) {
                pad0 = fn_8000FCCC();
            }
            lbl_803ECE40[fn_80188030(pad0)] = 2;
            lbl_803ECE44[fn_80188030(pad0)] = 1;
        }
        if (pad1 != -1) {
            if (fn_80188030(pad1) == -1 || fn_80188030(pad1) > 3) {
                pad1 = fn_8000FCCC();
            }
            lbl_803ECE40[fn_80188030(pad1)] = 0;
            lbl_803ECE44[fn_80188030(pad1)] = 1;
        }
        lbl_803EB96A = 1;
    }
    char name[13] = {0};
    int db = fn_8022F384(fn_8022F4BC());
    if (pad0 != -1 && fn_80188030(pad0) != -1) {
        lbl_803ECE40[fn_80188030(pad0)] = 2;
        fn_8017F60C();
        lbl_803ECE44[fn_80188030(pad0)] = 1;
        lbl_803EB96C[fn_80188030(pad0)] = db;
        if (db != -1) {
            fn_80186A10(db, name);
            fn_80187A28(fn_80188030(pad0), name);
        }
    }
    if (pad1 != -1 && fn_80188030(pad1) != -1) {
        if (lbl_803EB968) {
            lbl_803ECE40[fn_80188030(pad1)] = 0;
        } else {
            lbl_803ECE40[fn_80188030(pad1)] = 2;
        }
        lbl_803ECE44[fn_80188030(pad1)] = 1;
        lbl_803EB96C[fn_80188030(pad1)] = db;
        if (db != -1) {
            fn_80186A10(db, name);
            fn_80187A28(fn_80188030(pad1), name);
        }
    }
    fn_80010914();
}

void fn_80011894(int removed)
{
    for (unsigned char i = 0; i <= 3; i++) {
        unsigned char team = lbl_803EB96C[i];
        if (team > 1) {
            continue;
        }
        if (lbl_803ECE48.mIndex[team] > removed) {
            unsigned char want = lbl_803ECE48.mIndex[team] - 1;
            for (unsigned char j = 0; j <= 1; j++) {
                if (lbl_803ECE48.mIndex[j] == want) {
                    lbl_803EB96C[i] = j;
                    break;
                }
            }
        } else if (lbl_803ECE48.mIndex[team] == removed) {
            lbl_803EB96C[i] = 3;
        }
    }
    fn_800102D8();
}

int fn_8001194C(int side)
{
    int result = -1;

    for (unsigned char i = 0; i <= 3; i++) {
        if ((side == 0 && lbl_803ECE40[i] == 2) || (side == 1 && lbl_803ECE40[i] == 0)) {
            if (lbl_803ECE44[i] == 1) {
                if (lbl_803EB96C[i] <= 1) {
                    result = lbl_803ECE48.mIndex[lbl_803EB96C[i]];
                }
                break;
            }
        }
    }
    return result;
}

int lbl_802F41C8[][5] = {
    { 1, 24, 24, 24, 24 },
    { 0, 1, 2, 24, 24 },
    { 0, 1, 3, 24, 24 },
    { 0, 1, 4, 24, 24 },
    { 0, 1, 5, 24, 24 },
    { 0, 1, 6, 24, 24 },
    { 16, 1, 5, 24, 24 },
    { 0, 1, 7, 8, 9 },
    { 0, 1, 7, 24, 24 },
    { 0, 1, 8, 24, 24 },
    { 0, 1, 10, 24, 24 },
    { 0, 1, 11, 24, 24 },
    { 0, 1, 12, 24, 24 },
    { 0, 1, 13, 24, 24 },
    { 0, 1, 14, 24, 24 },
    { 0, 1, 15, 24, 24 },
    { 0, 1, 17, 24, 24 },
    { 0, 1, 18, 24, 24 },
    { 0, 1, 22, 24, 24 },
    { 0, 1, 22, 24, 24 },
    { 0, 1, 22, 24, 24 },
    { 0, 1, 22, 24, 24 },
    { 0, 1, 23, 24, 24 },
    { 0, 1, 19, 20, 21 },
};

void fn_800119CC(int type, int value, int column, char *pOut, int size, int *pFound)
{
    char text[32] = " ";

    if (type != 6) {
        if (value > 9) {
            *pOut = 0;
            return;
        }
    } else {
        value = fn_80015E24(value);
    }
    if (fn_8007D5A0(type, value, lbl_802F41C8[type][column], text, 32)) {
        *pFound = 1;
    } else {
        *pFound = 0;
    }
    memcpy(pOut, text, size);
}

int fn_80011AA8(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_8007D4E8();
        fn_8007DDC0(1);
        lbl_803EB970 = 1;
        break;
    case 0x80000002:
        fn_8007D52C();
        lbl_803EB970 = 0;
        break;
    case 0x80000003:
        fn_800119CC(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[3].pParams->mpText, pArgs[3].pParams->mLength,
                    pArgs[4].pi);
        break;
    default:
        return 0;
    }
    return 1;
}

void fn_80011B60(Object_8007A334 *pObject, int index, int saved)
{
    int found = 0;

    if (saved) {
        found = fn_8008406C(pObject, index, 0);
        if (found) {
            lbl_803EB97C[index] = fn_80083FBC(pObject);
        }
    }
    if (!found) {
        if (lbl_803EB97C[index] != -1) {
            found = fn_80084034(pObject, lbl_803EB97C[index], 0);
        }
        if (!found) {
            if (!fn_8008406C(pObject, index, 0)) {
                fn_8007A444(pObject);
                fn_80011D9C(pObject, index);
            }
        }
    }
}

unsigned char fn_80011C1C(unsigned char pad)
{
    int db = fn_80186F7C(pad);

    if (db != -1) {
        if (fn_8022F358(fn_80186F7C(pad)) != lbl_803EB9B4[pad]) {
            lbl_803EB9B4[pad] = fn_8022F358(fn_80186F7C(pad));
            return 1;
        }
    } else if (lbl_803EB9B4[pad] != -1) {
        lbl_803EB9B4[pad] = db;
        return 1;
    }
    return 0;
}

void fn_80011CB0(Object_8007A334 *pObject)
{
    if (!fn_8007A588(pObject)) {
        fn_8007A4A4(pObject);
    }
}

void fn_80011CEC(Object_8007A334 *pObject)
{
    if (!fn_8007A510(pObject)) {
        fn_8007A444(pObject);
    }
}

unsigned char fn_80011D28(Object_8007A334 *pObject, int side)
{
    unsigned char count = 0;

    if (fn_8007A444(pObject)) {
        do {
            if (!fn_80011FA0(side, fn_80083FBC(pObject))) {
                count++;
            }
        } while (fn_8007A510(pObject));
    }
    return count;
}

void fn_80011D9C(Object_8007A334 *pObject, int side)
{
    do {
        unsigned int i = 0;
        unsigned int count = fn_8022C8F0(0, lbl_803EB978[side]);
        while (i < count) {
            fn_80011CEC(pObject);
            if (!fn_80011FA0(side, fn_80083FBC(pObject))) {
                i++;
            }
        }
    } while (lbl_803ECE4C[side][1] == fn_80083FBC(pObject));
}

void fn_80011E34(int side)
{
    fn_80011D9C(&lbl_8036ADB0[side], side);
    fn_80011CB0(&lbl_8036ADB0[side]);
    for (unsigned int i = 0; i <= 2; i++) {
        lbl_803ECE4C[side][i] = fn_80083FBC(&lbl_8036ADB0[side]);
        fn_80011CEC(&lbl_8036ADB0[side]);
    }
}

void fn_80011EBC(int side, int id, char *pName, int size, int *pA, int *pB, int *pC, int *pFree)
{
    Object_8007A334 cursor;

    fn_80083E1C(&cursor, 0);
    fn_80084034(&cursor, id, 0);
    if (pName) {
        fn_80083F88(&cursor, pName, size);
    }
    *pA = fn_800842E8(&cursor);
    *pB = fn_80084310(&cursor);
    *pC = fn_80084338(&cursor);
    if (pFree) {
        *pFree = !fn_80011FA0(side, id);
    }
    fn_80083F68(&cursor);
}

int fn_80011FA0(int side, int id)
{
    int result = 0;
    int db = fn_80186F7C(side);
    int otherDb = fn_80186F7C(!side);

    if (db != -1) {
        Object_8007A334 cursor;
        fn_8007EBDC(&cursor, db);
        result = fn_8007EC54(&cursor, id);
        fn_8007EC34(&cursor);
    } else if (otherDb != -1 && !fn_8007AF84(side)) {
        Object_8007A334 cursor;
        fn_8007EBDC(&cursor, otherDb);
        result = fn_8007EC54(&cursor, id);
        fn_8007EC34(&cursor);
    } else {
        Object_8007A334 *pObject = &lbl_8036ADB0[side];
        int position = fn_8007A43C(pObject);
        fn_80084034(pObject, id, 0);
        result = !fn_8007A934(pObject, 0x53495654);
        fn_8007A600(pObject, position);
    }
    return result;
}

void fn_800120C8(int side, int *pIndex)
{
    int i;
    int count = fn_80012244(side);

    for (i = 0; i < count; i++) {
        if (fn_8017F584() == 8 && fn_8018F228(fn_80186B38(fn_8022F4BC())) != 0x3FF) {
            if (side == 1) {
                if (lbl_803EB994[1][i] == fn_8018F228(fn_80186B38(fn_8022F4BC()))) {
                    *pIndex = i;
                    return;
                }
            } else if (lbl_803EB994[0][i] == fn_8006270C()) {
                *pIndex = i;
                return;
            }
        } else if (lbl_803EB994[side][i] == lbl_803ECE4C[side][1]) {
            *pIndex = i;
            return;
        }
    }
    *pIndex = i;
}

void fn_800121BC(int side, int *pIds, int count)
{
    int i = 0;

    if (fn_8007A444(&lbl_8036ADB0[side])) {
        do {
            pIds[i++] = fn_80083FBC(&lbl_8036ADB0[side]);
        } while (fn_8007A510(&lbl_8036ADB0[side]));
    }
    fn_8007A444(&lbl_8036ADB0[side]);
}

int fn_80012244(int side)
{
    return fn_8007A410(&lbl_8036ADB0[side]);
}

void fn_80012274(int side, int index, int *pId, char *pName, int size)
{
    Object_8007A334 cursor;

    *pId = lbl_803EB994[side][index];
    fn_80083E1C(&cursor, 0);
    fn_80084034(&cursor, *pId, 0);
    fn_80083F88(&cursor, pName, size);
    fn_80083F68(&cursor);
}

void fn_80012310(int side, int direction, int *pId, char *pName, int nameSize, int *pPosition, char *pRole,
                 int roleSize, int *pFlag, int *pStats, char *pHeight, int heightSize, char *pWeight,
                 int weightSize)
{
    int found = -1;
    int result;

    if (direction == 3) {
        lbl_803EB9A0[side] =
            lbl_803EB9A0[side] - 1 < -1 ? lbl_803ECE50[side] - 1 : lbl_803EB9A0[side] - 1;
    } else if (direction == 1) {
        int current = lbl_803EB9A0[side] + 1;
        if (current == lbl_803ECE50[side]) {
            lbl_803EB9A0[side] = -1;
        } else {
            lbl_803EB9A0[side] = current;
        }
    }
    if (lbl_803EB9A0[side] != -1) {
        for (int i = 0; i < lbl_803ECE50[side]; i++) {
            if (lbl_8036AE60[side].mEntries[i].mIndex == lbl_803EB9A0[side]) {
                found = i;
                break;
            }
        }
        Object_8008044C *pObject = &lbl_8036AE08[side];
        *pId = lbl_8036AE60[side].mEntries[found].mId;
        pPosition[0] = lbl_803EB9A0[side] + 1;
        pPosition[1] = lbl_803ECE50[side];
        fn_800809C4(pObject, *pId, &result);
        fn_80080B08(pObject, pName, nameSize);
        fn_8017F670(fn_80080ECC(pObject), pRole);
        if (pStats) {
            pStats[0] = fn_800812E0(pObject, 6);
            pStats[1] = fn_800812E0(pObject, 4);
            pStats[2] = fn_800812E0(pObject, 7);
            pStats[3] = fn_800812E0(pObject, 0);
            pStats[4] = fn_800812E0(pObject, 3);
            pStats[5] = fn_800812E0(pObject, 2);
            pStats[6] = fn_800812E0(pObject, 1);
            pStats[7] = fn_800812E0(pObject, 5);
            pStats[8] = fn_800812E0(pObject, 8);
            pStats[9] = fn_800812E0(pObject, 9);
        }
        unsigned int height = fn_800811E0(pObject);
        int weight = fn_80081188(pObject);
        fn_801C2D88(pHeight, heightSize, "%d ft %d in", height / 12, height % 12);
        fn_801C2D88(pWeight, weightSize, "%d lbs", weight);
        if (lbl_8036AE60[side].mEntries[found].mSlot >= 0) {
            *pFlag = 1;
        } else {
            *pFlag = 0;
        }
    } else {
        *pId = -1;
        *pFlag = 0;
        fn_801C3284(pName, "Auto Pick Players", nameSize);
        fn_801C3284(pRole, "", roleSize);
        pPosition[0] = -1;
        pPosition[1] = -1;
        for (int i = 0; i < 10; i++) {
            pStats[i] = 0;
        }
    }
}

void fn_80012634(int side)
{
    Object_8008044C list;
    Desc_8008044C desc;

    if (lbl_803EB97C[side] != -1) {
        void *pList = fn_8021EA44(1);
        desc.mUnknown4 = 1;
        desc.mUnknown8 = lbl_803EB97C[side];
        fn_8008044C(&list, &desc, 0x54415453);
        if (fn_8007A444((Object_8007A334 *)&list)) {
            do {
                fn_8021E72C(pList, 10, fn_80080D10(&list));
            } while (fn_8007A510((Object_8007A334 *)&list));
        }
        fn_8008056C(&list);
    }
}

void fn_80012710(int side)
{
    Object_8008044C list;
    Desc_8008044C desc;
    void *pList = fn_8021EA44(1);

    desc.mUnknown4 = 1;
    desc.mUnknown8 = lbl_803EB97C[side];
    fn_8008044C(&list, &desc, 0x54415453);
    if (fn_8007A444((Object_8007A334 *)&list)) {
        do {
            fn_8021E2B4(pList, 10, fn_80080D10(&list));
        } while (fn_8007A510((Object_8007A334 *)&list));
    }
    fn_8008056C(&list);
}

void fn_800127E4(int side, char *pBuffer, int size, int full)
{
    if (full) {
        fn_80080B08(&lbl_8036AE08[side], pBuffer, size);
    } else {
        fn_80080BEC(&lbl_8036AE08[side], pBuffer, size);
    }
}

void fn_80012834(unsigned char side)
{
    Desc_8008044C desc;
    Object_8008044C *pObject = &lbl_8036AE08[side];

    if (pObject->mUnknown0 != 0) {
        fn_8008056C(pObject);
    }
    desc.mUnknown0 = 1;
    desc.mUnknown4 = 1;
    desc.mUnknown8 = lbl_803EB97C[side];
    fn_8008044C(pObject, &desc, fn_80027DF0() ? 0x54415453 : 0x454D4147);
    lbl_803EB9A0[side] = -1;
}

/* Row -1 stands for the row under the cursor. */
static inline int ResolveRow(int list, int row)
{
    if (row == -1) {
        row = lbl_8036B0E8[list].mTop + lbl_8036B0E8[list].mRow;
        if (row >= lbl_803ECE50[list]) {
            row = row - lbl_803ECE50[list] - 1;
        }
    }
    return row;
}

static inline int NextRow(int list, int row)
{
    int next = -1;

    if (row != lbl_803ECE50[list] - 1) {
        next = row + 1;
    }
    return next;
}

static inline void GetRow(int team, int list, int row, int *pOut)
{
    if (row != -1) {
        fn_8007A600((Object_8007A334 *)&lbl_8036AE08[list], row);
        int id = fn_800808F8(&lbl_8036AE08[list]);
        int i;

        pOut[0] = id;
        pOut[1] = -1;
        for (i = 0; i < lbl_803ECE50[team]; i++) {
            if (lbl_8036AE60[list].mEntries[i].mId == id && lbl_8036AE60[list].mEntries[i].mSlot >= 0) {
                pOut[1] = lbl_8036AE60[list].mEntries[i].mSlot;
                break;
            }
        }
    } else {
        pOut[1] = row;
        pOut[0] = row;
    }
}

void fn_800128E8(unsigned char team)
{
    if (fn_80027DF0()) {
        if (lbl_803EB9AC[team]) {
            unsigned char i;

            for (i = 0; i <= 19; i++) {
                lbl_8036AE60[team].mEntries[i].mSlot = -1;
                lbl_8036AE60[team].mEntries[i].mIndex = 0x7FFF;
                lbl_8036AE60[team].mEntries[i].mId = 0x7FFF;
                lbl_8036AE60[team].mEntries[i].mKey = 0xFF;
            }
            lbl_8036AE60[team].mUnknown140 = 0x7FFF;
        }
        if (fn_8007A444((Object_8007A334 *)&lbl_8036AE08[team])) {
            do {
                fn_80081F50(&lbl_8036AE08[team], team, 0);
            } while (fn_8007A510((Object_8007A334 *)&lbl_8036AE08[team]));
        }
        lbl_803EB9CC = 1;
    } else {
        lbl_803EB9CC = 0;
    }
}

void fn_800129E4(unsigned char team)
{
    lbl_8036B0E8[team].mTop = lbl_803ECE50[team] - 1;
    lbl_8036B0E8[team].mRow = 1;
}

void fn_80012A14(unsigned char team)
{
    int i;

    lbl_803ECE50[team] = fn_8007A410((Object_8007A334 *)&lbl_8036AE08[team]);
    fn_8007A444((Object_8007A334 *)&lbl_8036AE08[team]);
    for (i = 0; i < lbl_803ECE50[team]; i++) {
        lbl_8036AE60[team].mEntries[i].mId = fn_800808F8(&lbl_8036AE08[team]);
        lbl_8036AE60[team].mEntries[i].mIndex = i;
        fn_8007A510((Object_8007A334 *)&lbl_8036AE08[team]);
    }
}

void fn_80012ABC(int team, int *pRow0, int *pRow1, int *pRow2, int *pCursor)
{
    int list = 1;
    int row;

    if (team == 0) {
        list = 0;
    }
    row = lbl_8036B0E8[list].mTop;
    GetRow(team, list, row, pRow0);
    row = NextRow(list, row);
    GetRow(team, list, row, pRow1);
    row = NextRow(list, row);
    GetRow(team, list, row, pRow2);
    *pCursor = lbl_8036B0E8[list].mRow;
}

void fn_80012D50(int team, int unused, int delta, int *pOut)
{
    int list = 1;
    int row;

    if (team == 0) {
        list = 0;
    }
    row = lbl_8036B0E8[list].mTop + lbl_8036B0E8[list].mRow;
    if (row < lbl_803ECE50[list]) {
        row += delta;
    } else {
        row = row - lbl_803ECE50[list] - 1 + delta;
    }
    if (row < -1) {
        row = lbl_803ECE50[list] - 1;
    } else if (row >= lbl_803ECE50[list]) {
        row = -1;
    }
    if (lbl_8036B0E8[list].mRow == 0 && delta < 0) {
        lbl_8036B0E8[list].mTop = row;
    } else if (lbl_8036B0E8[list].mRow == 2 && delta > 0) {
        if (lbl_8036B0E8[list].mTop == lbl_803ECE50[list] - 1) {
            lbl_8036B0E8[list].mTop = -1;
        } else {
            lbl_8036B0E8[list].mTop++;
        }
    } else {
        lbl_8036B0E8[list].mRow += delta;
    }
    GetRow(team, list, row, pOut);
}

void fn_80012F3C(int team, int row, char *pName, int nameLength, char *pPosition, int positionLength,
                 int *pValues)
{
    int list = 1;

    if (team == 0) {
        list = 0;
    }
    row = ResolveRow(list, row);
    if (row != -1) {
        fn_8007A600((Object_8007A334 *)&lbl_8036AE08[list], row);
        fn_800127E4(list, pName, nameLength, 0);
        fn_8017F670(fn_80080ECC(&lbl_8036AE08[list]), pPosition);
        if (pValues) {
            int values[10];

            fn_80081788(&lbl_8036AE08[list], values);
            pValues[0] = values[6];
            pValues[1] = values[4];
            pValues[2] = values[7];
            pValues[3] = values[0];
            pValues[4] = values[3];
            pValues[5] = values[2];
            pValues[6] = values[1];
            pValues[7] = values[5];
            pValues[8] = values[8];
            pValues[9] = values[9];
        }
    } else {
        fn_801C2E18(pName, " ");
        fn_801C2E18(pPosition, " ");
        if (pValues) {
            unsigned char i;

            for (i = 0; i <= 9; i++) {
                pValues[i] = 1;
            }
        }
    }
}

void fn_800130B8(int group, int kind, int slot)
{
    fn_8003B2D0(group, kind, slot);
}

void fn_800130D8(int group, int kind, Pair_8003AEA8 **pPairs)
{
    fn_8003B234(group, kind, pPairs);
}

void fn_800130F8(int group, int kind, int slot, int code, int a, int b)
{
    fn_8003B0F8(group, kind, slot, code, a, b);
}

int fn_80013118(int team)
{
    unsigned int picked = 0;
    int result = 1;
    int i;

    for (i = 0; i < lbl_803ECE50[team]; i++) {
        if (lbl_8036AE60[team].mEntries[i].mSlot >= 0) {
            picked++;
        }
    }
    if (picked < lbl_803EB974) {
        result = 0;
    }
    return result;
}

void fn_8001317C(int team, int *pIds)
{
    int count = 0;
    int i;

    for (i = 0; i < lbl_803ECE50[team]; i++) {
        if (lbl_8036AE60[team].mEntries[i].mSlot >= 0) {
            pIds[count] = lbl_8036AE60[team].mEntries[i].mId;
            count++;
        }
    }
    pIds[count] = 0x7FFF;
}

Entry_8036AE60 *fn_800131F4(int team, int id, int *pIndex)
{
    Entry_8036AE60 *pSlot = 0;
    int i;

    for (i = 0; i < lbl_803ECE50[team]; i++) {
        if (lbl_8036AE60[team].mEntries[i].mId == id) {
            pSlot = &lbl_8036AE60[team].mEntries[i];
            break;
        }
    }
    if (pIndex) {
        *pIndex = i;
    }
    return pSlot;
}

void fn_80013254(int team, int *pIndex)
{
    int ids[22];
    int keys[16];
    int id = 0;
    int key = 0;
    Entry_8036AE60 *pSlot;
    unsigned int picked;
    unsigned int keyed;

    do {
        Entry_8036AE60 *pOpen = 0;
        int count = 0;
        int i;

        picked = 0;
        keyed = 0;
        for (i = 0; i < lbl_803ECE50[team]; i++) {
            pSlot = &lbl_8036AE60[team].mEntries[i];
            if (pSlot->mSlot >= 0) {
                if (pSlot->mKey != 0xFF) {
                    keys[keyed] = pSlot->mKey;
                    keyed++;
                    picked++;
                    continue;
                }
                if (!pOpen) {
                    pOpen = pSlot;
                }
                picked++;
            }
            ids[count] = lbl_8036AE60[team].mEntries[i].mId;
            count++;
        }
        keys[keyed] = 0xFF;
        ids[count] = 0x7FFF;
        if (pOpen) {
            pOpen->mKey = fn_8003EA28(0, keys, pOpen->mId);
        }
    } while (picked > keyed);
    if (picked < lbl_803EB974) {
        fn_8003EB2C(0, ids, keys, &id, &key);
        pSlot = fn_800131F4(team, id, pIndex);
        pSlot->mKey = key;
    }
}

void fn_800133B0(int team, int a, int b)
{
    if (a != b) {
        Entry_8036AE60 slot = lbl_8036AE60[team].mEntries[a];

        lbl_8036AE60[team].mEntries[a] = lbl_8036AE60[team].mEntries[b];
        lbl_8036AE60[team].mEntries[b] = slot;
    }
}

void fn_80013438(int team)
{
    int ids[22];
    int index;
    int count = 0;
    int open = -1;
    int picked = 0;
    int i;

    for (i = 0; i < lbl_803ECE50[team]; i++) {
        if (lbl_8036AE60[team].mEntries[i].mSlot < 0) {
            if (open == -1) {
                open = i;
            }
        } else {
            picked++;
        }
        ids[count] = lbl_8036AE60[team].mEntries[i].mId;
        count++;
    }
    ids[count] = 0x7FFF;
    fn_8003E710(lbl_803EB9C4[team], ids, 0);
    for (i = picked; i < lbl_803EB974; i++) {
        fn_80013254(team, &index);
        if (lbl_8036AE60[team].mEntries[index].mSlot < 0) {
            fn_800133B0(team, open, index);
            lbl_8036AE60[team].mEntries[open].mSlot = open;
            open++;
            while (open <= 6 && lbl_8036AE60[team].mEntries[open].mSlot >= 0) {
                open++;
            }
        }
    }
    fn_8003E8B8(0);
    lbl_8036AE60[team].mUnknown140 = lbl_8036AE60[team].mEntries[lbl_803EB974 - 1].mId;
    for (i = 0; i < lbl_803ECE50[team]; i++) {
        lbl_8036AE60[team].mEntries[i].mKey = 0xFF;
    }
}

/* An array argument points at a header of pArray[0] + 1 words; its data follows the header. */
int fn_80013614(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        lbl_803EB9A8 = pArgs[4].i;
        *pResult = fn_80014430(pArgs[0].pi, pArgs[1].pi, pArgs[2].pi, pArgs[3].pi);
        break;
    case 0x80000002:
        fn_80014B98();
        break;
    case 0x80000003:
        fn_80011EBC(pArgs[0].i, pArgs[1].i, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength, pArgs[3].pi,
                    pArgs[4].pi, pArgs[5].pi, pArgs[6].pi);
        break;
    case 0x80000019:
        fn_80012274(pArgs[0].i, pArgs[1].i, pArgs[2].pi, pArgs[3].pParams->mpText, pArgs[3].pParams->mLength);
        break;
    case 0x80000018:
        fn_800120C8(pArgs[0].i, pArgs[1].pi);
        break;
    case 0x80000005:
        fn_80011E34(pArgs[0].i);
        break;
    case 0x80000006:
        if (fn_8017F584() == 8 && pArgs[0].i == 0) {
            fn_80014AA8(0, fn_8006270C());
            break;
        }
        if (fn_8017F584() == 8 && fn_801801B4() == 1) {
            if (fn_8018F228(fn_80186B38(fn_8022F4BC())) == 0x3FF) {
                fn_8018F2F4(fn_80186B38(fn_8022F4BC()), pArgs[1].i);
            } else {
                pArgs[1].i = fn_8018F228(fn_80186B38(fn_8022F4BC()));
            }
        }
        if (fn_8017F584() == 6 && fn_80025708()) {
            Object_8007A334 query;
            int team;

            fn_80083E40(&query, 0, 0x54415453);
            fn_8008406C(&query, 1, 0);
            team = fn_80083FBC(&query);
            fn_80083F68(&query);
            if (pArgs[0].i == 1 && pArgs[1].i != team) {
                fn_80014AA8(1, team);
                pArgs[0].i = 0;
            }
        }
        fn_80014AA8(pArgs[0].i, pArgs[1].i);
        break;
    case 0x80000016:
        *pResult = fn_8006270C();
        break;
    case 0x80000017:
        *pResult = fn_8018F228(fn_80186B38(fn_8022F4BC()));
        break;
    case 0x8000000F:
        if (count == 5) {
            int *pRow0 = pArgs[1].pi;
            int *pRow1 = pArgs[2].pi;
            int *pRow2 = pArgs[3].pi;
            int row0 = pRow0[0] + 1;
            int row1 = pRow1[0] + 1;
            int row2 = pRow2[0] + 1;

            fn_80012ABC(pArgs[0].i, pRow0 + row0, pRow1 + row1, pRow2 + row2, pArgs[4].pi);
        }
        break;
    case 0x80000010:
        if (count == 4) {
            int *pRow = pArgs[3].pi;
            int row = pRow[0] + 1;

            fn_80012D50(pArgs[0].i, pArgs[1].i, pArgs[2].i, pRow + row);
        } else {
            int *pPosition = pArgs[4].pi;
            int *pStats = pArgs[7].pi;
            int position = pPosition[0] + 1;
            int stats = pStats[0] + 1;

            fn_80012310(pArgs[0].i, pArgs[1].i, pArgs[2].pi, pArgs[3].pParams->mpText, pArgs[3].pParams->mLength,
                        pPosition + position, pArgs[5].pParams->mpText, pArgs[5].pParams->mLength,
                        pArgs[6].pi, pStats + stats, pArgs[8].pParams->mpText,
                        pArgs[8].pParams->mLength, pArgs[9].pParams->mpText, pArgs[9].pParams->mLength);
        }
        break;
    case 0x80000011:
    {
        int *pValues = pArgs[5].pi;
        int values = pValues[0] + 1;

        fn_80012F3C(pArgs[0].i, -1, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength, pArgs[3].pParams->mpText,
                    pArgs[3].pParams->mLength, pValues + values);
        break;
    }
    case 0x80000014:
        fn_800150FC(pArgs[0].i, -1, pArgs[1].pParams->mpText, pArgs[1].pParams->mLength);
        break;
    case 0x8000000C:
        fn_800130B8(pArgs[0].i, pArgs[1].i, pArgs[2].i);
        break;
    case 0x8000000A:
    {
        int *pPairs = pArgs[2].pi;
        int pairs = pPairs[0] + 1;

        fn_800130D8(pArgs[0].i, pArgs[1].i, (Pair_8003AEA8 **)(pPairs + pairs));
        break;
    }
    case 0x8000000B:
        fn_800155CC(pArgs[0].i);
        break;
    case 0x8000000E:
        fn_800130F8(pArgs[0].i, pArgs[1].i, pArgs[2].i, pArgs[3].i, (int)pArgs[4].pParams->mpText,
                    pArgs[4].pParams->mLength);
        break;
    case 0x80000008:
        *pResult = fn_800151C0(pArgs[0].i, pArgs[1].pi, pArgs[2].i);
        break;
    case 0x80000009:
        fn_800153A0(pArgs[0].i, pArgs[1].pi, pArgs[2].i);
        break;
    case 0x8000000D:
        fn_80015420(pArgs[0].i, pArgs[1].pi);
        break;
    case 0x80000012:
    {
        int *pList = pArgs[1].pi;
        int list = pList[0] + 1;

        fn_80015000(pArgs[0].i, pList + list);
        lbl_803EB99C = 1;
        break;
    }
    case 0x80000007:
        fn_80014FD8(pArgs[0].i);
        break;
    case 0x80000013:
        fn_8017F584();
        break;
    case 0xD:
        if (pArgs[0].i == -1) {
            *pResult = 1;
            break;
        }
        return 0;
    case 0x8000001A:
        fn_8001565C(pArgs[0].i, pArgs[1].i, pArgs[2].pi);
        break;
    case 0x147:
        *pResult = fn_800551D8(pArgs[0].i);
        break;
    case 0x149:
        fn_800551E0(pArgs[0].i, pArgs[1].i, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength);
        *pArgs[3].pi = fn_80178D70(pArgs[0].i ? fn_80178308() : fn_80178320());
        break;
    case 0x14A: {
        int *pList = pArgs[1].pi;
        int list = pList[0] + 1;

        pList += list;
        fn_80055230(pArgs[0].i, pArgs[4].i, pArgs[3].i, pList, pList + 1, pArgs[2].pParams->mpText,
                    pArgs[2].pParams->mLength);
        break;
    }
    case 0xE:
    case 0x80000015:
        break;
    default:
        return 0;
    }
    return 1;
}

int fn_80013CCC(int *pCount, int *pA, int *pB, int *pC)
{
    *pC = 0;
    if (fn_802294F4()) {
        fn_80229554();
    }
    *pB = 0;
    if (fn_801835A0()) {
        fn_801834DC();
    }
    Query_80083E40 query;
    query.mUnknown0 = 1;
    query.mUnknown4 = 3;
    fn_80083E40(&lbl_8036ADB0[1], &query, 0x54415453);
    *pA = 0;
    *pCount = fn_8007A410(&lbl_8036ADB0[1]);
    return 0;
}

void fn_80013D74(void)
{
    Object_8007A334 *pQuery = &lbl_8036ADB0[1];

    if (pQuery->mUnknown0) {
        fn_80083F68(pQuery);
    }
    if (fn_801801B4() == 1) {
        fn_80183368(5, lbl_803EB9D4[1]);
    } else {
        lbl_803EB9D4[1] = 0x3FF;
    }
}

void fn_80013DCC(int mode, int id, char *pName, int nameLength, int *pA, int *pB, int *pC, int *pMode)
{
    if (mode == 1) {
        Object_8007A334 query;

        fn_80083E40(&query, 0, 0x54415453);
        fn_80084034(&query, id, 0);
        if (pName) {
            fn_80083F88(&query, pName, nameLength);
        }
        *pA = fn_800842E8(&query);
        *pB = fn_80084310(&query);
        *pC = fn_80084338(&query);
        if (pMode) {
            *pMode = mode;
        }
        fn_80083F68(&query);
    }
}

void fn_80013EAC(int mode, int row, int *pId, char *pName, int nameLength)
{
    Object_8007A334 query;

    if (mode == 1) {
        int current = fn_8007A43C(&lbl_8036ADB0[1]);

        fn_8007A600(&lbl_8036ADB0[1], row);
        *pId = fn_80083FBC(&lbl_8036ADB0[1]);
        fn_80083F88(&lbl_8036ADB0[1], pName, nameLength);
        if (current != -1) {
            fn_8007A600(&lbl_8036ADB0[1], current);
        }
    }
}

void fn_80013F54(int mode, int *pResult)
{
    int found = 0;

    if (mode == 1) {
        found = fn_80084034(&lbl_8036ADB0[1], lbl_803EB9D4[1], pResult);
    }
    if (!found) {
        *pResult = found;
    }
}

void fn_80013FA8(int index, int value)
{
    lbl_803EB9D4[index] = value;
}

int fn_80013FB8(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        *pResult = fn_80013CCC(pArgs[0].pi, pArgs[1].pi, pArgs[2].pi, pArgs[3].pi);
        break;
    case 0x80000002:
        fn_80013D74();
        break;
    case 0x80000003:
        fn_80013DCC(pArgs[0].i, pArgs[1].i, pArgs[2].pParams->mpText, pArgs[2].pParams->mLength, pArgs[3].pi,
                    pArgs[4].pi, pArgs[5].pi, pArgs[6].pi);
        break;
    case 0x80000019:
        fn_80013EAC(pArgs[0].i, pArgs[1].i, pArgs[2].pi, pArgs[3].pParams->mpText, pArgs[3].pParams->mLength);
        break;
    case 0x80000018:
        fn_80013F54(pArgs[0].i, pArgs[1].pi);
        break;
    case 0x80000006:
        fn_80013FA8(pArgs[0].i, pArgs[1].i);
        break;
    case 0xF: {
        int *pList = pArgs[0].pi;
        int offset = pList[0] + 1;
        int i;

        pList += offset;

        for (i = 3; i >= 0; i--) {
            pList[i] = 1;
        }
        break;
    }
    case 0xA:
        *pArgs[0].pi = 0;
        break;
    case 0x111:
        *pResult = -1;
        break;
    case 0x80000004:
    case 0x80000005:
        break;
    default:
        return 0;
    }
    return 1;
}


void fn_8001416C(int team)
{
    int count = 0;
    int i;

    for (i = 0; i < lbl_803ECE50[team]; i++) {
        Entry_8036AE60 *pPlayer = &lbl_8036AE60[team].mEntries[i];
        if (pPlayer->mSlot >= 0) {
            count++;
        }
    }
    for (i = 0; i < lbl_803ECE50[team] && count <= 6; i++) {
        Entry_8036AE60 *pPlayer = &lbl_8036AE60[team].mEntries[i];
        if (pPlayer->mSlot < 0) {
            pPlayer->mSlot = count;
            count++;
        }
    }
}
void fn_80014214(int team)
{
    for (int i = 0; i < lbl_803ECE50[team]; i++) {
        Entry_8036AE60 *pPlayer = &lbl_8036AE60[team].mEntries[i];
        if (pPlayer->mSlot >= lbl_803EB974) {
            pPlayer->mSlot = -1;
        }
    }
}

int fn_80014260(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    int result;

    if (lbl_803EB971 == 0) {
        result = fn_80013614(id, pArgs, count, pResult);
    } else {
        result = fn_80013FB8(id, pArgs, count, pResult);
    }
    return result;
}

void fn_80014294(int id0, int id1)
{
    int saved1 = lbl_803EB97C[1];
    int saved0 = lbl_803EB97C[0];

    fn_801801C8(1);
    fn_80014430(0, 0, 0, 0);

    if (id0 == -2) {
        fn_80011E34(0);
        lbl_803EB97C[0] = lbl_803ECE4C[0][1];
    } else if (id0 == -1) {
        lbl_803EB97C[0] = 31;
    } else if (id0 == -3) {
        fn_8008406C(&lbl_8036ADB0[0], 0, 0);
        lbl_803EB97C[0] = fn_80083FBC(&lbl_8036ADB0[0]);
    } else {
        lbl_803EB97C[0] = id0;
    }

    if (id1 == -2) {
        do {
            fn_80011E34(1);
            lbl_803EB97C[1] = lbl_803ECE4C[1][1];
        } while (lbl_803EB97C[0] == lbl_803EB97C[1]);
    } else if (id1 == -1) {
        lbl_803EB97C[1] = 20;
    } else if (id1 == -3) {
        fn_8008406C(&lbl_8036ADB0[1], 1, 0);
        lbl_803EB97C[1] = fn_80083FBC(&lbl_8036ADB0[1]);
    } else {
        lbl_803EB97C[1] = id1;
    }

    fn_80014AA8(0, lbl_803EB97C[0]);
    fn_80014AA8(1, lbl_803EB97C[1]);
    fn_80014FD8(0);
    fn_80014FD8(1);
    fn_80015000(0, 0);
    fn_80015000(1, 0);
    fn_80014B98();

    lbl_803EB97C[1] = saved1;
    lbl_803EB97C[0] = saved0;
}

void fn_8001441C(int team, int id)
{
    lbl_803EB98C[team] = id;
}

void fn_8001442C(void)
{
}

int fn_80014430(int *pCount1, int *pCount0, int *pMode, int *pFlag)
{
    Query_80083E40 query;
    Pair_803EB9D0 pair = { 0, 0 };
    unsigned char color[3];
    int mode;
    unsigned int i;
    unsigned int j;

    mode = fn_801486A0();
    if (fn_8017F584() == 6) {
        lbl_803EB984[0] = lbl_803EB97C[0];
        lbl_803EB984[1] = lbl_803EB97C[1];
        lbl_803EB97C[0] = lbl_803EB98C[0];
        lbl_803EB97C[1] = lbl_803EB98C[1];
    }
    if (pFlag) {
        *pFlag = 1;
    }
    if (fn_801485D4()) {
        fn_80148AF8(fn_80148A58());
    }

    switch (mode) {
    case 3:
        lbl_803EB974 = 3;
        break;
    case 4:
        lbl_803EB974 = 4;
        break;
    case 5:
        lbl_803EB974 = 7;
        break;
    default:
        lbl_803EB974 = 7;
        break;
    }
    if (pMode) {
        *pMode = lbl_803EB974;
    }

    lbl_803EB9D2 = 0;
    lbl_803EB9A0[0] = -1;
    lbl_803EB9A0[1] = -1;
    pair.mUnknown0 = fn_80011C1C(0);
    pair.mUnknown1 = fn_80011C1C(1);
    lbl_803EB9D0[0] = pair.mUnknown0;
    lbl_803EB9D0[1] = pair.mUnknown1;

    if (fn_801801B4() == 1) {
        if (fn_8017F584() == 6) {
            if (!fn_8000485C() || lbl_803EB9A8 != 0x6B) {
                fn_8018D7E0();
            }
        } else {
            fn_8018D7E0();
        }
    }

    query.mUnknown0 = 1;
    query.mUnknown4 = 0;
    if (fn_8017F584() == 3) {
        query.mUnknown4 = 3;
    } else if (fn_8017F584() == 6) {
        if (lbl_803EB9A8 == 0x6B) {
            if (lbl_803EB97C[0] == 63) {
                int id;
                fn_80004440(&id);
                lbl_803EB97C[0] = id;
            }
            query.mUnknown4 = 0;
        } else {
            query.mUnknown4 = 3;
        }
    } else if (fn_8007AF84(0) == 0 && fn_80186F7C(1) != -1) {
        query.mUnknown4 = 1;
        query.mUnknown8 = 1;
    } else {
        query.mUnknown4 = 1;
        query.mUnknown8 = 0;
    }
    fn_80083E1C(&lbl_8036ADB0[0], &query);
    if (fn_801801B4() == 1) {
        lbl_803EB978[0] = fn_80011D28(&lbl_8036ADB0[0], 0);
    }

    query.mUnknown4 = 0;
    query.mUnknown0 = 1;
    if (fn_8017F584() == 3) {
        query.mUnknown4 = 3;
    } else if (fn_8017F584() == 6) {
        if (lbl_803EB9A8 == 0x6B) {
            query.mUnknown4 = 1;
            query.mUnknown8 = 1;
        } else {
            query.mUnknown4 = 3;
        }
    } else {
        int ai = fn_8007AF84(1);
        if (ai == 0 && fn_80186F7C(0) != -1) {
            query.mUnknown4 = 1;
            query.mUnknown8 = ai;
        } else {
            query.mUnknown4 = 1;
            query.mUnknown8 = 1;
        }
    }
    fn_80083E1C(&lbl_8036ADB0[1], &query);
    if (fn_801801B4() == 1) {
        lbl_803EB978[1] = fn_80011D28(&lbl_8036ADB0[1], 1);
    }

    if (fn_8008406C(&lbl_8036ADB0[0], 0, 0)) {
        color[0] = fn_800841AC(&lbl_8036ADB0[0]);
        color[1] = fn_800841D8(&lbl_8036ADB0[0]);
        color[2] = fn_80084204(&lbl_8036ADB0[0]);
        fn_80188CBC(0, 4, fn_80084158(&lbl_8036ADB0[0]), 172, color);
    }
    if (fn_8008406C(&lbl_8036ADB0[1], 1, 0)) {
        color[0] = fn_800841AC(&lbl_8036ADB0[1]);
        color[1] = fn_800841D8(&lbl_8036ADB0[1]);
        color[2] = fn_80084204(&lbl_8036ADB0[1]);
        fn_80188CBC(1, 4, fn_80084158(&lbl_8036ADB0[1]), 172, color);
    }

    lbl_803ECE4C = (int **)fn_801D2B7C(8, 0, 0);
    for (i = 0; i < 2; i++) {
        lbl_803ECE4C[i] = (int *)fn_801D2B7C(12, 0, 0);
    }

    if (fn_8017F584() == 6) {
        if (lbl_803EB9A8 == 0x6B) {
            fn_80084034(&lbl_8036ADB0[0], lbl_803EB97C[0], 0);
        } else {
            fn_8007A444(&lbl_8036ADB0[0]);
        }
    } else {
        fn_80011B60(&lbl_8036ADB0[0], 0, pair.mUnknown0);
    }
    for (i = 0; i < 1; i++) {
        fn_80011CB0(&lbl_8036ADB0[0]);
    }
    for (j = 0; j < 3; j++) {
        lbl_803ECE4C[0][j] = fn_80083FBC(&lbl_8036ADB0[0]);
        fn_80011CEC(&lbl_8036ADB0[0]);
    }

    if (fn_8017F584() == 6) {
        if (lbl_803EB9A8 == 0x6B) {
            fn_80084034(&lbl_8036ADB0[1], lbl_803EB97C[1], 0);
        } else if (lbl_803EB97C[0] != 0) {
            lbl_803EB97C[1] = lbl_803EB97C[0];
            fn_80084034(&lbl_8036ADB0[1], lbl_803EB97C[0], 0);
        } else {
            fn_8007A444(&lbl_8036ADB0[1]);
            lbl_803EB97C[1] = fn_80083FBC(&lbl_8036ADB0[1]);
        }
    } else {
        fn_80011B60(&lbl_8036ADB0[1], 1, pair.mUnknown1);
    }
    for (i = 0; i < 1; i++) {
        fn_80011CB0(&lbl_8036ADB0[1]);
    }
    for (j = 0; j < 3; j++) {
        lbl_803ECE4C[1][j] = fn_80083FBC(&lbl_8036ADB0[1]);
        fn_80011CEC(&lbl_8036ADB0[1]);
    }

    void *pFont = fn_8021EA44(1);
    fn_8021E2B4(pFont, 10, 1);
    fn_8021E2B4(pFont, 10, 1);
    fn_8003B6F0(fn_801801B4() == 1);
    lbl_803EB9AC[0] = lbl_803EB9AC[1] = fn_801801B4() == 1;
    if (fn_801801B4() == 1) {
        lbl_803EB9BC[0] = 1;
        lbl_803EB9BC[1] = 1;
        lbl_803EB9C0[0] = 1;
        lbl_803EB9C0[1] = 1;
        lbl_803EB9B0[0] = 1;
        lbl_803EB9B0[1] = 1;
    }

    if (pCount0 && pCount1) {
        *pCount0 = fn_80012244(0);
        *pCount1 = fn_80012244(1);
        lbl_803EB994[0] = (int *)fn_801D2B7C(*pCount0 * 4, 0, 0);
        lbl_803EB994[1] = (int *)fn_801D2B7C(*pCount1 * 4, 0, 0);
        fn_800121BC(0, lbl_803EB994[0], *pCount0);
        fn_800121BC(1, lbl_803EB994[1], *pCount1);
    }
    return 0;
}

void fn_80014AA8(int team, int id)
{
    fn_80012634(team);
    lbl_803EB97C[team] = id;
    fn_80012710(team);
    fn_80012834(team);
    if (fn_80027DF0()) {
        if (lbl_803EB9AC[team]) {
            int index = fn_80186F7C(team);
            if (index == -1) {
                index = fn_80186F7C(team == 0);
            }
            fn_80082558(id, index);
            fn_800128E8(team);
            fn_80012A14(team);
            fn_800129E4(team);
            lbl_803EB9C4[team] = fn_802372EC(0, 5);
            lbl_803EB9C0[team] = 1;
            lbl_803EB9B0[team] = 0;
            lbl_803EB9BC[team] = lbl_803EB9BC[team] = 1;
        }
        lbl_803EB9AC[team] = 1;
    }
}

void fn_80014B98(void)
{
    Record_8003B6BC records[2];
    int ids[2][7];
    int texture0 = 0;
    int texture1 = 0;
    int id0 = 0;
    int id1 = 0;

    lbl_803EB9D2 = 1;
    fn_80012634(0);
    fn_80012634(1);
    void *pFont = fn_8021EA44(1);
    fn_8021E72C(pFont, 10, 1);
    fn_8021E72C(pFont, 10, 1);

    if (fn_801801B4() == 1) {
        id0 = lbl_803EB97C[0];
        fn_80084034(&lbl_8036ADB0[0], id0, 0);
        texture0 = fn_8007A98C(&lbl_8036ADB0[0], 0x49524454);
        id1 = lbl_803EB97C[1];
        fn_80084034(&lbl_8036ADB0[1], id1, 0);
        texture1 = fn_8007A98C(&lbl_8036ADB0[1], 0x49524454);
    }
    if (lbl_8036ADB0[0].mUnknown0) {
        fn_80083F68(&lbl_8036ADB0[0]);
    }
    Object_8007A334 *pCursor = &lbl_8036ADB0[1];
    if (pCursor->mUnknown0) {
        fn_80083F68(pCursor);
    }
    if (fn_801801B4() == 1) {
        fn_8007CAEC(0, id0);
        fn_8007CAEC(1, id1);
        fn_8022A508(0, id0, id0, 0, texture0);
        fn_8022A508(1, id1, id1, 0, texture1);
        fn_8022DC7C(0);
        fn_8022DCB0(0);
        fn_8022DCE4(0);
        fn_8022DD18(0);
    }

    for (unsigned int i = 0; i < 2; i++) {
        fn_801D2BD0(lbl_803ECE4C[i]);
    }
    fn_801D2BD0(lbl_803ECE4C);
    if (lbl_803EB994[0]) {
        fn_801D2BD0(lbl_803EB994[0]);
        fn_801D2BD0(lbl_803EB994[1]);
        lbl_803EB994[0] = 0;
        lbl_803EB994[1] = 0;
    }

    if (fn_801801B4() == 1 && ((fn_8017F584() == 8 && lbl_803EB99C) || fn_8017F584() != 8) &&
        ((fn_8017F584() == 6 && lbl_803EB99C) || fn_8017F584() != 6)) {
        fn_8003B6BC(0, &records[0]);
        fn_8003B6BC(1, &records[1]);
        for (unsigned char i = 0; i <= 6; i++) {
            fn_800809C4(&lbl_8036AE08[0], records[0].mUnknown[i], 0);
            fn_80081F50(&lbl_8036AE08[0], 0, 1);
            ids[0][i] = lbl_8036AE60[0].mEntries[i].mId;
            fn_800809C4(&lbl_8036AE08[1], records[1].mUnknown[i], 0);
            fn_80081F50(&lbl_8036AE08[1], 1, 1);
            ids[1][i] = lbl_8036AE60[1].mEntries[i].mId;
        }
        fn_8003DE74(0, ids[0]);
        fn_8003DE74(1, ids[1]);
    }

    if (lbl_8036AE08[0].mUnknown0) {
        fn_8008056C(&lbl_8036AE08[0]);
    }
    Object_8008044C *pPlayer = &lbl_8036AE08[1];
    if (pPlayer->mUnknown0) {
        fn_8008056C(pPlayer);
    }
    fn_8003B8BC();

    if (fn_801801B4() == 1) {
        if (fn_8017F584() == 6 && lbl_803EB99C) {
            if (fn_80025708()) {
                fn_80015D28(fn_800785C0()->mUnknown1BC);
            } else {
                fn_80015D28(fn_800A3444());
            }
            fn_8001ED90(1);
        }
        fn_80027E18(1);
    }
    if (fn_801801B4() == 0) {
        fn_8018807C(0);
        if (fn_8017F584() == 6) {
            if (!fn_8000485C() || lbl_803EB9A8 != 0x6B) {
                fn_8018C48C(0x454D4147);
                fn_8018C48C(0x54415453);
            }
        } else {
            fn_8018C48C(0x454D4147);
            fn_8018C48C(0x54415453);
        }
    }

    fn_8003EBC4(0);
    fn_8003EBE4(0);
    if (fn_8017F584() == 6) {
        if (fn_8000485C() && fn_801801B4() == 1 && lbl_803EB9A8 != 0x6B) {
            lbl_803EB98C[0] = lbl_803EB97C[0];
        }
        lbl_803EB97C[0] = lbl_803EB984[0];
        lbl_803EB97C[1] = lbl_803EB984[1];
    }
    lbl_803EB99C = 0;
}

void fn_80014FD8(int team)
{
    int side = team ? 1 : 0;

    lbl_803EB9BC[side] = 1;
    lbl_803EB9C0[side] = 1;
}

void fn_80015000(int team, int *pList)
{
    int list[8];
    int side = team ? 1 : 0;

    if (lbl_803EB9BC[side]) {
        if (lbl_803EB9C0[side]) {
            fn_80013438(side);
            lbl_803EB9C0[side] = 0;
        }
        fn_8001416C(team);
        fn_8001317C(team, list);
        fn_8003B3F8(team, list, lbl_803EB9C4[side]);
    }
    fn_8003B1F4(team);

    if (pList) {
        unsigned char count = 0;
        for (unsigned char i = 0; count <= 6 && i < 20; i++) {
            if (lbl_8036AE60[team].mEntries[i].mSlot >= 0) {
                pList[count] = lbl_8036AE60[team].mEntries[i].mId;
                count++;
            }
        }
    }
}

void fn_800150FC(int team, int index, char *pBuffer, int size)
{
    int side = team ? 1 : 0;

    index = ResolveRow(side, index);
    if (index != -1) {
        fn_8007A600((Object_8007A334 *)&lbl_8036AE08[side], index);
        fn_800127E4(side, pBuffer, size, 1);
    } else {
        fn_801C3284(pBuffer, " ", size + 1);
    }
}

int fn_800151C0(int team, int *pNext, int id)
{
    int result = 0;

    if (id != -1) {
        int side;
        int slot;
        int i;

        result = 1;
        side = team ? 1 : 0;
        for (slot = 0; slot < lbl_803ECE50[team]; slot++) {
            if (lbl_8036AE60[side].mEntries[slot].mSlot < 0) {
                break;
            }
        }
        for (i = 0; i < lbl_803ECE50[team]; i++) {
            if (lbl_8036AE60[side].mEntries[i].mId == id) {
                lbl_8036AE60[side].mEntries[i].mSlot = slot;
                break;
            }
        }
        if (!lbl_803EB9BC[side]) {
            fn_8003B584(team, id, lbl_8036B0F8[side].mUnknown1C[slot], lbl_8036B0F8[side].mUnknown0[slot]);
        }
        if (i != slot) {
            fn_800133B0(team, i, slot);
        }
        for (slot++; slot < lbl_803ECE50[team]; slot++) {
            if (lbl_8036AE60[side].mEntries[slot].mSlot < 0) {
                break;
            }
        }
        *pNext = slot;
        if (fn_80013118(side)) {
            lbl_8036AE60[side].mUnknown140 = id;
        }
        lbl_803EB9C0[side] = 0;
    }
    return result;
}

void fn_800153A0(int team, int *pIndex, int id)
{
    int side = team ? 1 : 0;

    for (*pIndex = 0; *pIndex < lbl_803ECE50[team]; (*pIndex)++) {
        if (lbl_8036AE60[side].mEntries[*pIndex].mId == id) {
            lbl_8036AE60[side].mEntries[*pIndex].mSlot = -1;
            break;
        }
    }
    lbl_8036AE60[side].mUnknown140 = 0x7FFF;
}

void fn_80015420(int team, int *pIndex)
{
    int side = team ? 1 : 0;

    fn_80014214(team);
    for (int i = 0; i < lbl_803ECE50[side]; i++) {
        if (lbl_8036AE60[side].mEntries[i].mId == lbl_8036AE60[side].mUnknown140) {
            lbl_803EB9A0[side] = lbl_8036AE60[side].mEntries[i].mIndex;
            break;
        }
    }
    fn_800809C4(&lbl_8036AE08[side], lbl_8036AE60[side].mUnknown140, &lbl_8036B0E8[side].mTop);
    if (lbl_8036B0E8[side].mTop == 0) {
        lbl_8036B0E8[side].mTop = -1;
    } else {
        lbl_8036B0E8[side].mTop--;
    }
    lbl_8036B0E8[side].mRow = 1;
    for (*pIndex = 0; *pIndex < lbl_803ECE50[side]; (*pIndex)++) {
        if (lbl_8036AE60[side].mEntries[*pIndex].mId == lbl_8036AE60[side].mUnknown140) {
            lbl_8036AE60[side].mEntries[*pIndex].mSlot = -1;
            break;
        }
    }
    lbl_8036AE60[side].mUnknown140 = 0x7FFF;
    lbl_803EB9BC[team] = 1;
}

void fn_800155CC(int team)
{
    lbl_803EB9BC[team] = 0;
    for (int i = 0; i < 7; i++) {
        fn_8003B5AC(team, lbl_8036AE60[team].mEntries[i].mId, &lbl_8036B0F8[team].mUnknown1C[i],
                    &lbl_8036B0F8[team].mUnknown0[i]);
    }
}

void fn_80015654(unsigned char value)
{
    lbl_803EB971 = value;
}

void fn_8001565C(int team, int slot, int *pId)
{
    *pId = -1;
    for (int i = 0; i < lbl_803ECE50[team]; i++) {
        if (lbl_8036AE60[team].mEntries[i].mSlot == slot) {
            *pId = lbl_8036AE60[team].mEntries[i].mId;
            break;
        }
    }
}

int lbl_802F43A8[] = { 9, 2, 0, 1, 5, 3, 4, 6, 7, 8, 10, 11 };
unsigned char lbl_802F43D8[12] = { 0 };

void fn_800156B4(int index, char *pName, int nameSize, char *pTeam, int teamSize, int *pValue, char *pText,
                 int textSize, int *pA, int *pB, int *pFlag)
{
    if (!lbl_803EB9DC[index].mValid) {
        fn_8007B684(lbl_802F43A8[index]);
        fn_8007B8A4(pName, nameSize);
        fn_8007B904((int)pTeam, teamSize);
        fn_8007B93C((int)pText, textSize);
        fn_8007B6FC(&lbl_803EB9DC[index].mUnknownAC, &lbl_803EB9DC[index].mUnknownB0);
        fn_8007B6D4();
        fn_8007D4E8();
        fn_8007DB74(6, lbl_802F43A8[index]);
        lbl_803EB9DC[index].mUnknownA8 = fn_8007DBB4(5);
        fn_8007D52C();
        if (lbl_803EB9E5) {
            int index0 = fn_80186F7C(0);
            int index1 = fn_80186F7C(1);
            *pFlag = 1;
            fn_8022F4BC();
            if (index0 != -1) {
                *pFlag = fn_8007B518(index0, lbl_802F43A8[index]);
            }
            if (index1 != -1 && *pFlag == 1) {
                *pFlag = fn_8007B518(index1, lbl_802F43A8[index]);
            }
            if (index0 == -1 && index1 == -1) {
                if (lbl_802F43A8[index] == 10 || lbl_802F43A8[index] == 11) {
                    *pFlag = 1;
                } else {
                    *pFlag = 0;
                }
            }
            if (fn_8017F584() == 8) {
                int value = fn_8018F3D8(fn_80186F7C(1));
                if (value == 0 && lbl_802F43A8[index] == 11) {
                    *pFlag = value;
                }
            }
        } else {
            *pFlag = lbl_802F43D8[index];
        }
        fn_801C3284(lbl_803EB9DC[index].mText0, pName, sizeof(lbl_803EB9DC[index].mText0));
        fn_801C3284(lbl_803EB9DC[index].mText21, pTeam, sizeof(lbl_803EB9DC[index].mText21));
        *pValue = lbl_803EB9DC[index].mUnknownA8;
        fn_801C3284(lbl_803EB9DC[index].mText42, pText, sizeof(lbl_803EB9DC[index].mText42));
        lbl_803EB9DC[index].mUnknownB4 = *pFlag;
        *pA = lbl_803EB9DC[index].mUnknownAC;
        *pB = lbl_803EB9DC[index].mUnknownB0;
        lbl_803EB9DC[index].mValid = 1;
    } else {
        fn_801C3284(pName, lbl_803EB9DC[index].mText0, nameSize + 1);
        fn_801C3284(pTeam, lbl_803EB9DC[index].mText21, teamSize + 1);
        *pValue = lbl_803EB9DC[index].mUnknownA8;
        fn_801C3284(pText, lbl_803EB9DC[index].mText42, textSize + 1);
        *pFlag = lbl_803EB9DC[index].mUnknownB4;
        *pA = lbl_803EB9DC[index].mUnknownAC;
        *pB = lbl_803EB9DC[index].mUnknownB0;
    }
    lbl_803EB9E0 = index;
}

void fn_800159A4(int *pCount, int *pCurrent, int *pResult)
{
    int current = lbl_803EB9E0;
    int flag;
    lbl_803EB9DC = (Entry_803EB9DC *)fn_801D2B7C(12 * sizeof(Entry_803EB9DC), 0, 0);
    fn_801C1F94(lbl_803EB9DC, 0, 12 * sizeof(Entry_803EB9DC));
    for (unsigned char i = 0; i <= 11; i++) {
        Entry_803EB9DC *pEntry = &lbl_803EB9DC[i];
        fn_800156B4(i, pEntry->mText0, 32, pEntry->mText21, 32, &pEntry->mUnknownA8, pEntry->mText42,
                    101, &pEntry->mUnknownAC, &pEntry->mUnknownB0, &flag);
    }
    if (lbl_803EB9E4) {
        lbl_803EB9E4 = 0;
        fn_80015B68(&lbl_803EB9E0, 0);
    } else {
        if (lbl_803EB9DC[current].mUnknownB4) {
            fn_80015B68(&current, 0);
        }
        lbl_803EB9E0 = current;
    }
    *pCount = 12;
    *pCurrent = lbl_803EB9E0;
    if (fn_8017F584() == 8 && fn_8018F3D8(fn_80186F7C(1)) == 0) {
        *pCurrent = 11;
        lbl_803EB9E0 = 11;
    }
    switch (fn_801486A0()) {
    case 0:
    case 1:
    case 2:
        *pResult = 1;
        break;
    default:
        *pResult = 0;
        break;
    }
}

void fn_80015B0C(int id, int unused)
{
    if (fn_801801B4() == 1) {
        fn_800A2F3C(id);
        fn_80027A20();
    } else if (fn_801486A0() != 15) {
        fn_8001B228();
    }
    fn_801D2BD0(lbl_803EB9DC);
}

int fn_80015B68(int *pIndex, int any)
{
    int index;
    do {
        index = fn_802372EC(0, 12);
    } while ((!any && lbl_803EB9DC[index].mUnknownB4) || index == lbl_803EB9E0);
    int id = lbl_802F43A8[index];
    *pIndex = index;
    return id;
}

void fn_80015BF0(int index)
{
    lbl_803EB9E0 = index;
}

int fn_80015BF8(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800159A4(pArgs[0].pi, pArgs[1].pi, pArgs[2].pi);
        break;
    case 0x80000002:
        fn_80015B0C(lbl_802F43A8[lbl_803EB9E0], pArgs[0].i);
        break;
    case 0x80000003:
        fn_800156B4(pArgs[0].i, pArgs[1].pParams->mpText, pArgs[1].pParams->mLength,
                    pArgs[2].pParams->mpText, pArgs[2].pParams->mLength, pArgs[3].pi,
                    pArgs[4].pParams->mpText, pArgs[4].pParams->mLength, pArgs[5].pi,
                    pArgs[6].pi, pArgs[7].pi);
        break;
    case 0x80000004:
        fn_80015B68(pArgs[0].pi, 0);
        break;
    case 0x80000005:
        fn_80015BF0(pArgs[0].i);
        break;
    default:
        return 0;
    }
    return 1;
}

void fn_80015D28(int id)
{
    int count;
    int current;
    int flag;
    fn_801801C8(1);
    fn_800159A4(&count, &current, &flag);
    int saved = lbl_803EB9E0;
    if (id == -1) {
        lbl_803EB9E0 = 0;
    } else if (id == -2) {
        fn_80015B68(&lbl_803EB9E0, 1);
    } else {
        for (lbl_803EB9E0 = 0; lbl_803EB9E0 <= 11; lbl_803EB9E0++) {
            if (lbl_802F43A8[lbl_803EB9E0] == id) {
                break;
            }
        }
    }
    if (lbl_803EB9E0 > 11) {
        if (id > 11) {
            id = lbl_802F43A8[0];
        }
        fn_80015B0C(id, 0);
    } else {
        fn_80015B0C(lbl_802F43A8[lbl_803EB9E0], 0);
    }
    lbl_803EB9E0 = saved;
}

int fn_80015E24(unsigned int index)
{
    int id = 12;
    if (index <= 11) {
        id = lbl_802F43A8[index];
    }
    return id;
}

void fn_80015E48(Arg_8018399C *pArgs, int count, int *pResult)
{
    lbl_803EB9E6 = 1;
    fn_80027E88(0);
    fn_80073094();
    fn_80062A58(0);
}

void fn_80015E80(Arg_8018399C *pArgs, int count, int *pResult)
{
    lbl_803EB9E6 = 0;
    if (!fn_8002892C()) {
        fn_80072AA8();
        fn_80072F90();
    }
}

int fn_80015EB8(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80015E48(pArgs, count, pResult);
        break;
    case 0x80000002:
        fn_80015E80(pArgs, count, pResult);
        break;
    default:
        return 0;
    }
    return 1;
}

int fn_80015F2C(void)
{
    unsigned short a = 0;
    unsigned short b = 0;
    fn_80219650(lbl_803EB688, &a, &b);
    return a == 0 && b == 3 && lbl_803EB9E6;
}

int fn_80015F90(int control)
{
    int index = lbl_803EB9E7;
    if (index != -1) {
        switch (control) {
        case -1:
            if (index == 0) {
                lbl_803EB9E7 = fn_801869F0() - 1;
            } else {
                lbl_803EB9E7--;
            }
            break;
        case 0:
            break;
        case 1:
            if (index == fn_801869F0() - 1) {
                lbl_803EB9E7 = 0;
            } else {
                lbl_803EB9E7++;
            }
            break;
        }
    }
    return index;
}

void fn_80016038(void)
{
    Object_8007A334 query;
    if (lbl_803EB9E7 != -1) {
        fn_80087BE4(&query, lbl_803EB9E7);
        lbl_803EB9E8->mValues[0] = fn_80087C8C(&query, 10);
        lbl_803EB9E8->mValues[1] = fn_80087C8C(&query, 11);
        lbl_803EB9E8->mValues[4] = fn_80087C8C(&query, 3);
        lbl_803EB9E8->mValues[3] = fn_80087C8C(&query, 4);
        lbl_803EB9E8->mValues[5] = fn_80087C8C(&query, 5);
        lbl_803EB9E8->mValues[2] = lbl_803EB9E8->mValues[3] + lbl_803EB9E8->mValues[4] + lbl_803EB9E8->mValues[5];
        lbl_803EB9E8->mValues[6] = fn_80087C8C(&query, 8);
        lbl_803EB9E8->mValues[7] = fn_80087C8C(&query, 9);
        lbl_803EB9E8->mValues[8] = fn_80087C8C(&query, 6);
        lbl_803EB9E8->mValues[9] = fn_80087C8C(&query, 7);
        lbl_803EB9E8->mValues[10] = fn_80087C8C(&query, 12);
        lbl_803EB9E8->mValues[11] = fn_80087C8C(&query, 13);
        lbl_803EB9E8->mValues[12] = fn_8008872C(fn_8022F358(lbl_803EB9E7));
        lbl_803EB9E8->mUnknown34 = fn_80087C8C(&query, 0);
        lbl_803EB9E8->mUnknown38 = fn_80087C8C(&query, 1);
        lbl_803EB9E8->mStreak = fn_80087C8C(&query, 2);
        fn_80087C3C(&query);
        fn_80186A10(lbl_803EB9E7, lbl_803EB9E8->mName);
    } else {
        for (unsigned char i = 0; i <= 12; i++) {
            lbl_803EB9E8->mValues[i] = 0;
        }
        lbl_803EB9E8->mUnknown34 = 0;
        lbl_803EB9E8->mUnknown38 = 0;
        lbl_803EB9E8->mStreak = 0;
        fn_801C3284(lbl_803EB9E8->mName, "None", 14);
    }
}

void fn_80016248(int *pCount)
{
    signed char indices[4];
    lbl_803EB9E8 = (Stats_803EB9E8 *)fn_801D2B7C(sizeof(Stats_803EB9E8), 0, 0);
    *pCount = fn_801869F0();
    fn_80186DF0(indices, 4);
    if (*pCount > 0) {
        lbl_803EB9E7 = indices[0];
    } else {
        lbl_803EB9E7 = -1;
    }
    fn_80016038();
}

void fn_800162B4(void)
{
    fn_801D2BD0(lbl_803EB9E8);
    lbl_803EB9E8 = 0;
    lbl_803EB9E7 = -1;
}

void fn_800162E8(int control, Params_80005284 *pName, int *pUnknown34, int *pUnknown38,
                 Params_80005284 *pStreak, int *pValues, int *pClear)
{
    if (fn_80015F90(control) != lbl_803EB9E7) {
        fn_80016038();
    }
    fn_801C3284(pName->mpText, lbl_803EB9E8->mName, pName->mLength);
    *pUnknown34 = lbl_803EB9E8->mUnknown34;
    *pUnknown38 = lbl_803EB9E8->mUnknown38;
    int streak = lbl_803EB9E8->mStreak;
    if (streak >= 0) {
        if (streak == 1) {
            fn_801C3284(pStreak->mpText, "1 Win", pStreak->mLength);
        } else {
            fn_801C2E18(pStreak->mpText, "%d Wins", streak);
        }
    } else if (streak == -1) {
        fn_801C3284(pStreak->mpText, "1 Loss", pStreak->mLength);
    } else {
        fn_801C2E18(pStreak->mpText, "%d Losses", -streak);
    }
    unsigned char i;
    for (i = 0; i <= 12; i++) {
        pValues[i] = lbl_803EB9E8->mValues[i];
    }
    for (i = 0; i <= 15; i++) {
        pClear[i] = 0;
    }
}

int fn_8001642C(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80016248(pArgs[0].pi);
        break;
    case 0x80000002:
        fn_800162B4();
        break;
    case 0x80000003:
    {
        int *pValues = pArgs[5].pi;
        int *pClear = pArgs[6].pi;
        int valuesOffset = pValues[0] + 1;
        int clearOffset = pClear[0] + 1;
        fn_800162E8(pArgs[0].i, pArgs[1].pParams, pArgs[2].pi, pArgs[3].pi,
                    pArgs[4].pParams, pValues + valuesOffset, pClear + clearOffset);
        break;
    }
    default:
        return 0;
    }
    return 1;
}

/* Replaces Windows-1252 symbols and curly quotes with their plain forms. */
void fn_800164F0(char *pText)
{
    signed char length = fn_801C3180(pText);
    for (signed char i = 0; i < length; i++) {
        switch (pText[i]) {
        case '\x99':
            pText[i] = '\xb0';
            break;
        case '\xae':
            pText[i] = '\xb1';
            break;
        case '\xa9':
            pText[i] = '\xb2';
            break;
        case '\x93':
        case '\x94':
            pText[i] = '"';
            break;
        case '\x91':
        case '\x92':
            pText[i] = '\'';
            break;
        }
    }
}

void fn_800165BC(void)
{
    fn_80023560();
    lbl_803EB9EC = -1;
    lbl_803EB9ED = 2;
}

void fn_800165EC(void)
{
    fn_800235DC();
}

void fn_8001660C(int *pCount, int *pValue, Params_80005284 *pRecord)
{
    int ok = 1;
    if (lbl_803EB9EC < 0) {
        ok = fn_80023514();
    }
    if (ok) {
        fn_800236B0(pValue);
        if (lbl_803EB9EC == -1 && *pValue == 2 && lbl_803EB9ED != 2) {
            lbl_803EB9EC = 2;
        } else if (lbl_803EB9EC == -1 && *pValue == 1 && lbl_803EB9ED != 1) {
            lbl_803EB9EC = 1;
        }
        if (lbl_803EB9EC > 0) {
            lbl_803EB9EC--;
            strcpy(pRecord->mpText, " ");
            *pValue = 0;
            (*pCount)--;
        } else {
            fn_80023684(pRecord->mpText, pRecord->mLength);
            lbl_803EB9EC = -1;
            lbl_803EB9ED = *pValue;
        }
    } else {
        strcpy(pRecord->mpText, " ");
        *pValue = 0;
    }
    fn_800164F0(pRecord->mpText);
}

int fn_80016730(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800165BC();
        fn_80023634(pArgs[0].pi);
        break;
    case 0x80000002:
        fn_800165EC();
        break;
    case 0x80000003:
        fn_8001660C(pArgs[0].pi, pArgs[1].pi, pArgs[2].pParams);
        break;
    default:
        return 0;
    }
    return 1;
}

void fn_800167D0(void)
{
    lbl_803EB9F4 = fn_8007F828(1);
    fn_8018D7E0();
    fn_8018C230(0, 1);
}

void fn_80016808(void)
{
    fn_8007F6F8(1, lbl_803EB9F4);
    fn_8001B330(lbl_803EB9F8 + lbl_803EB9F9 * 2 + lbl_803EB9FA * 4 + lbl_803EB9FB * 8);
    if (fn_801801B4() == 1) {
        fn_8001B260(lbl_803EB9F0, 14);
        fn_8001B828();
    }
}

int fn_80016878(int key)
{
    switch (key) {
    case 1:
        return lbl_803EB9F0;
    case 2:
        return lbl_803EB9F8;
    case 3:
        return lbl_803EB9F9;
    case 4:
        return lbl_803EB9FA;
    case 5:
        return lbl_803EB9FB;
    case 6:
        return lbl_803EB9F4;
    }
    return 0;
}

void fn_800168E8(int key, int value)
{
    switch (key) {
    case 1:
        lbl_803EB9F0 = value;
        break;
    case 2:
        lbl_803EB9F8 = value;
        break;
    case 3:
        lbl_803EB9F9 = value;
        break;
    case 4:
        lbl_803EB9FA = value;
        break;
    case 5:
        lbl_803EB9FB = value;
        break;
    case 6:
        lbl_803EB9F4 = value;
        break;
    }
}

int fn_80016950(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000007:
        fn_800167D0();
        break;
    case 0x80000008:
        fn_80016808();
        break;
    case 0x80000001:
        *pResult = fn_80016878(pArgs[0].i);
        break;
    case 0x80000002:
        fn_800168E8(pArgs[0].i, pArgs[1].i);
        break;
    default:
        return 0;
    }
    return 1;
}

void fn_80016A08(int *pCount)
{
    lbl_803EB9FE = fn_801869F0();
    *pCount = lbl_803EB9FE;
    lbl_803EBA00 = new (0) Object_8007A334;
    if (lbl_803EB9FE > 0) {
        signed char indices[2];
        unsigned char auxiliary[2];
        fn_80186DF0(indices, 2);
        for (int i = 0; i < 2; ++i) {
            if (indices[i] != -1) {
                auxiliary[i] = 1;
            }
        }
        lbl_803EB9FC = indices[0];
        lbl_803EBA04 = new (0) Object_8007A334;
    } else {
        lbl_803EB9FC = -1;
    }
}

void fn_80016AF4(void)
{
    if (lbl_803EBA00) {
        fn_80088C8C(lbl_803EBA00);
        delete lbl_803EBA00;
        lbl_803EBA00 = 0;
    }
    if (lbl_803EBA04) {
        fn_80088A1C(lbl_803EBA04);
        delete lbl_803EBA04;
        lbl_803EBA04 = 0;
    }
}

void fn_80016B60(int control, char *pText, int *pResult)
{
    if (lbl_803EB9FC == -1) {
        fn_801C2E18(pText, "None");
        *pResult = 0;
        return;
    }
    if (control != -1 && lbl_803EB9FE > 1) {
        if (control == 3) {
            if (lbl_803EB9FC - 1 >= 0) {
                lbl_803EB9FC--;
            } else {
                lbl_803EB9FC = lbl_803EB9FE - 1;
            }
        } else if (control == 1) {
            lbl_803EB9FC = (lbl_803EB9FC + 1) % lbl_803EB9FE;
        }
    }
    if (lbl_803EBA04->mUnknown0) {
        fn_80088A1C(lbl_803EBA04);
    }
    fn_80088950(lbl_803EBA04, lbl_803EB9FC);
    fn_80186A10(lbl_803EB9FC, pText);
    *pResult = fn_800886BC(fn_8022F358(lbl_803EB9FC));
}

void fn_80016C60(int index, char *pText, int *pUnknown94, int *pFlag)
{
    Record_80088CE0 record;
    fn_8007A600(lbl_803EBA00, index);
    fn_80088CE0(lbl_803EBA00, &record);
    fn_801C2E18(pText, record.mName);
    char *pDot = fn_801C3084(pText, '.');
    if (pDot) {
        pDot[1] = 0;
    }
    *pUnknown94 = record.mUnknown94;
    if (lbl_803EB9FC != -1 && fn_80088A74(lbl_803EBA04, record.mIndex) != 0) {
        *pFlag = 1;
    } else {
        *pFlag = 0;
    }
}

const char *lbl_802F43E4[] = { "User Stats", "Game Modes", "Save Files", "Miscellaneous" };

void fn_80016D14(int control, char *pText, int size, int *pResult)
{
    switch (control) {
    case -1:
        break;
    case 1:
        lbl_803EB9FD = (lbl_803EB9FD + 1) % 4;
        break;
    case 3:
        if (--lbl_803EB9FD < 0) {
            lbl_803EB9FD = 3;
        }
        break;
    }
    if (lbl_803EBA00->mUnknown0) {
        fn_80088C8C(lbl_803EBA00);
    }
    fn_80088B24(lbl_803EBA00, 1, lbl_803EB9FD);
    fn_801C3284(pText, lbl_802F43E4[lbl_803EB9FD], size);
    *pResult = fn_8007A410(lbl_803EBA00);
}

int fn_80016DF4(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_80016A08(pArgs[0].pi);
        break;
    case 0x80000002:
        fn_80016AF4();
        break;
    case 0x80000003:
        fn_80016B60(pArgs[0].i, pArgs[1].pParams->mpText, pArgs[2].pi);
        break;
    case 0x80000004:
        fn_80016C60(pArgs[0].i, pArgs[1].pParams->mpText, pArgs[2].pi,
                    pArgs[3].pi);
        break;
    case 0x80000005:
        fn_80016D14(pArgs[0].i, pArgs[1].pParams->mpText, pArgs[1].pParams->mLength,
                    pArgs[2].pi);
        break;
    default:
        return 0;
    }
    return 1;
}
}
