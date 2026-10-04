#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/cu_80181330.h"
#include "game/fn_8007F6F8.h"
#include "game/fn_8007F828.h"
#include "game/fn_801FCE10.h"
#include "game/FELoop.h"

/* Record filled by fn_8018EDF0. */
struct Record_8030A340 {
    char mUnknown0[72];
    int mUnknown72;
    int mUnknown76;
    char mUnknown80[3];
    signed char mUnknown83;
    char mUnknown84[16];
};

/* Teams and round of the current match, set by fn_80061520. */
struct Match_8030A3A4 {
    int mDit1;
    int mDit2;
    int mLvlt;
};

/* Values saved by fn_800611C0 and restored by fn_80061154. */
struct Saved_802D4E28 {
    int mValue0;
    int mValue1;
    int mValue14;
    unsigned char mSaved;
};

/* Index returned by fn_8022F384, and whether fn_80060B0C opened the 'PDFN'
   database; while it is open, queries skip their own open and close. */
struct State_803EA5F8 {
    signed char mIndex;
    signed char mUnknown1;
    short mUnknown2;
    short mOpen;
};

struct Block_800619FC {
    int *mpGame;
    int *mpDit2;
    int *mpDit1;
    Params_80005284 *mpName2;
    Params_80005284 *mpName1;
    int *mpUnknown20;
    int *mpUnknown24;
    int *mpWinner;
};

extern "C" {
int fn_8000FCCC(void);
int fn_8000FCDC(void);
void fn_80010150(int a);
void fn_80011600(int a, int b, int c);
void fn_80015D28(int a);
void fn_8001B260(int a, int b);
void fn_8001B330(int a);
void fn_8003B3F8(int a, int *pList, int b);
void fn_8003B6F0(int a);
void fn_8003B8BC(void);
void fn_8005BE54(unsigned char value);
int fn_80060354(Record_8030A340 *pRecord, int *pList);
void fn_80060410(int index, int *pList);
void fn_8007CAEC(int index, int value);
void fn_80084A8C(int a, int *pList, int b, int c);
int fn_80085620(int a, int b);
int *fn_80085744(int a, int b);
int fn_80085C94(int a, int *pList);
int fn_80086154(void);
int fn_80086174(void);
int fn_800868E8(int *pDigp, int count, int munt, int digt);
int fn_80086960(int digt, int *pList);
int fn_80086994(void);
int fn_800869C8(int lvlt);
int fn_800869FC(int lvlt, int row, int *pDit1, int *pDit2, int *pTniw);
int fn_80086A30(int lvlt, int dit1, int dit2, int tniw);
int fn_80086A64(void);
int fn_80086A98(void);
int fn_80086ACC(int *pList);
int fn_80086AEC(int size);
int fn_80086B50(void);
int fn_80086BA4(int index);
void fn_80087BE4(Object_8007A334 *pObject, int index);
void fn_80087C3C(Object_8007A334 *pObject);
int fn_80178AE0(void);
int fn_801801B4(void);
void fn_80186F30(signed char a, int b);
int fn_8018BE68(int a, int b, int *pList);
void fn_8018C48C(int tag);
int fn_8018E7CC(int a);
int fn_8018EDF0(int a, int b, Record_8030A340 *pRecord);
int fn_8018EE44(int a);
int fn_8018EEAC(void);
int fn_8018EEF0(void);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int fn_8022C8F0(unsigned int low, unsigned int high);
int fn_8022F358(int index);
int fn_8022F384(int a);
int fn_8022F3D4(int a);
int fn_8022F4BC(void);
}

Object_8008044C lbl_8030A2BC;
Object_8007A334 lbl_8030A2E8;
Object_8007A334 lbl_8030A314;
Record_8030A340 lbl_8030A340;
Match_8030A3A4 lbl_8030A3A4;

static unsigned char lbl_803EA5E8 = 0;
static Record_8030A340 *lbl_803EA5EC = 0;
static Object_8008044C *lbl_803EA5F0 = 0;
static Object_8007A334 *lbl_803EA5F4 = 0;
static State_803EA5F8 lbl_803EA5F8 = {0, -1, 0, 0};

static Saved_802D4E28 lbl_802D4E28 = {-1, 0, 0, 0};

/* Round ('LVLT') and row of each of the 15 bracket games. */
static int lbl_802D4E38[15] = {1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4};
static int lbl_802D4E74[15] = {0, 0, 1, 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7};

extern "C" {
void fn_80060948(int id, char *pName, int size);
int fn_800609EC(int team, int lvlt);
void fn_80060A9C(void);
void fn_80060B0C(void);
void fn_80060BB4(void);
void fn_80060BE0(void);
int fn_80060C14(int game, int *pLvlt, int *pRow);
int fn_80060C94(void);
void fn_80060CD4(void);
int fn_80060E7C(void);
int fn_8006102C(void);
void fn_80061088(int *pDit1, int *pDit2, int *pLvlt);
void fn_80061154(void);
void fn_800611C0(int value14, int value1);
int fn_80061390(int digt);
int fn_80061408(int digt);

void fn_80061520(int dit1, int dit2, int lvlt)
{
    fn_8003B6F0(1);
    dit2 = fn_80061408(dit2);
    lbl_8030A3A4.mDit1 = fn_80061390(dit1);
    lbl_8030A3A4.mDit2 = dit2;
    lbl_8030A3A4.mLvlt = lvlt;
    fn_8003B8BC();
}

void fn_80061584(void)
{
    int dit1;
    int dit2;
    int lvlt;
    int saved = fn_8000FCDC();

    fn_800611C0(0, 0x24);
    if (fn_800869C8(1) == 0) {
        lbl_803EA5EC->mUnknown83 = -1;
    }
    fn_80061088(&dit1, &dit2, &lvlt);
    fn_80061520(dit1, dit2, lvlt);
    if (lbl_803EA5EC->mUnknown72) {
        lbl_803EA5EC->mUnknown72 = 0;
    }
    fn_80011600(-1, fn_8000FCCC(), saved);
    fn_80186F30(lbl_803EA5F8.mIndex, 1);
    fn_8007CAEC(2, 1);
    fn_80015D28(lbl_803EA5EC->mUnknown72);
}

int fn_8006164C(void)
{
    return fn_80086A98() > 0;
}

int fn_8006167C(void)
{
    int result = 100;

    if (fn_8018EDF0(0, fn_8018EE44(0) - 1, &lbl_8030A340)) {
        result = 123;
        lbl_803EA5EC = &lbl_8030A340;
    }
    return result;
}

void fn_800616D8(void)
{
    switch (lbl_803EA5EC->mUnknown76) {
    case 0:
    case 1:
    case 2:
    case 3:
        break;
    case 4:
        fn_8006164C();
        fn_80061584();
        break;
    }
}

void fn_8006171C(int game, int *pDit1, int *pUnknown5, int *pDit2, int *pUnknown7, int *pWinner)
{
    int lvlt;
    int row;
    int dit1 = -1;
    int dit2 = -1;
    int tniw;
    int found;

    *pUnknown5 = -1;
    *pUnknown7 = -1;
    *pWinner = -1;
    *pDit1 = -1;
    *pDit2 = -1;
    if (fn_80060C14(game, &lvlt, &row)) {
        found = fn_800869FC(lvlt, row, &dit1, &dit2, &tniw);
        if (found) {
            *pDit1 = dit1;
            *pDit2 = dit2;
            switch ((unsigned int)tniw) {
            case 0:
                break;
            case 1:
                *pWinner = 0;
                break;
            case 2:
                *pWinner = 1;
                break;
            }
        }
        if (found && lvlt < lbl_802D4E38[14]) {
            if (fn_800609EC(dit1, lvlt) < fn_800609EC(dit2, lvlt)) {
                *pDit2 = dit1;
                *pDit1 = dit2;
            }
        }
    }
}

/* Starts the tournament on first use and returns the player's open game. */
void fn_8006182C(int *pGame)
{
    int lvlt;
    int row;
    int dit1;
    int dit2;
    int tniw;
    int game;

    *pGame = 0;
    if (!lbl_803EA5E8) {
        fn_80010150(10);
        fn_80060BE0();
        fn_80060B0C();
        fn_80061154();
        fn_80060BB4();
        if (!fn_8006164C()) {
            fn_80060CD4();
        }
        lbl_803EA5EC = 0;
        lbl_803EA5E8 = 1;
        fn_80027EA0();
    }
    for (game = 0; game <= 14; game++) {
        if (fn_80060C14(game, &lvlt, &row) && fn_800869FC(lvlt, row, &dit1, &dit2, &tniw) && tniw == 0 &&
            (dit1 == 0x2E || dit2 == 0x2E)) {
            *pGame = game;
        }
    }
}

void fn_80061918(void)
{
    if (lbl_803EA5E8) {
        if (!fn_8006102C()) {
            if (fn_801801B4() == 0) {
                fn_80060BE0();
                lbl_803EA5EC = 0;
            } else if (fn_801801B4() == 1) {
                fn_80027E18(1);
                fn_8006167C();
                fn_800616D8();
            }
        }
        fn_80060A9C();
        lbl_803EA5E8 = 0;
    }
    fn_8005BE54(0);
}

int fn_8006199C(void)
{
    int done = 0;

    if (lbl_803EA5EC) {
        fn_80060B0C();
        if (!fn_8006102C()) {
            fn_80060E7C();
        }
        if (fn_8006102C()) {
            done = 1;
        }
        fn_80060A9C();
    }
    return done;
}

int fn_800619FC(unsigned int id, Block_800619FC *pBlock, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_8006182C(pBlock->mpGame);
        break;
    case 0x80000002:
        fn_80061918();
        break;
    case 0x80000003: {
        int *pDit2 = pBlock->mpDit2;
        int *pDit1 = pBlock->mpDit1;

        fn_8006171C((int)pBlock->mpGame, pDit1, pBlock->mpUnknown24, pDit2, pBlock->mpUnknown20, pBlock->mpWinner);
        fn_80060948(*pDit1, pBlock->mpName1->mpText, pBlock->mpName1->mLength);
        fn_80060948(*pDit2, pBlock->mpName2->mpText, pBlock->mpName2->mLength);
        break;
    }
    default:
        return 0;
    }
    return 1;
}

Record_8030A340 *fn_80061AD4(void)
{
    return lbl_803EA5EC;
}

void fn_80061ADC(void)
{
    lbl_803EA5EC = 0;
}

void fn_80061AE8(void)
{
    int saved = fn_8000FCDC();

    fn_8006167C();
    fn_80011600(-1, fn_8000FCCC(), saved);
    fn_80186F30(lbl_803EA5F8.mIndex, 1);
    if (lbl_803EA5F8.mOpen == 0) {
        lbl_803EA5F8.mIndex = fn_8022F384(fn_8022F4BC());
        fn_80086BA4(lbl_803EA5F8.mIndex);
    }
    fn_80086A64();
    fn_80086994();
    if (lbl_803EA5F8.mOpen == 0) {
        fn_80086B50();
    }
    fn_8001B260(2, 0);
    fn_8001B330(1);
}

void fn_80061B90(int team, int *pDigp)
{
    int teams[8];
    int munt = 0;
    int i;

    fn_80060B0C();
    fn_80086ACC(teams);
    for (munt = 0; munt <= 7 && teams[munt] != team; munt++) {
    }
    if (team == fn_80060C94()) {
        for (i = 0; i <= 6 && pDigp[i] != 0; i++) {
        }
    }
    fn_800868E8(pDigp, 7, munt, team);
    fn_80060A9C();
}

int fn_80061C44(void)
{
    int result;

    if (lbl_803EA5F8.mOpen == 0) {
        fn_80086BA4(lbl_803EA5F8.mIndex = fn_8022F384(fn_8022F4BC()));
    }
    result = fn_8006164C();
    if (lbl_803EA5F8.mOpen == 0) {
        fn_80086B50();
    }
    return result;
}

int fn_80061CAC(void)
{
    int result;

    if (lbl_803EA5F8.mOpen == 0) {
        fn_80086BA4(lbl_803EA5F8.mIndex = fn_8022F384(fn_8022F4BC()));
    }
    result = fn_8006102C();
    if (lbl_803EA5F8.mOpen == 0) {
        fn_80086B50();
    }
    return result;
}

int fn_80061D14(void)
{
    int result;

    if (lbl_803EA5EC == 0) {
        result = 0;
    } else {
        int state = fn_80178AE0();
        result = 1;
        if (state == 1) {
            fn_8006199C();
        }
    }
    return result;
}

void fn_80061D64(int index)
{
    fn_801FCE10(0,
                "use \x8c insert into 'LTFN' set 'TNIW' = 2 and 'LVLT' = 0 and '1DIT' = 1 and '2DIT' = 2\n",
                fn_8022F3D4(fn_8022F358(index)));
}

void fn_80061DA0(int index)
{
    fn_801FCE10(0, "use \x8c delete from 'LTFN' where ('TNIW' = 2)\n", fn_8022F3D4(fn_8022F358(index)));
}

void fn_80061DDC(void)
{
    lbl_803EA5EC = 0;
}

int fn_80061DE8(void)
{
    int count = 0;

    fn_801FCE10(0, "use \x8c select count(*) into \x85 from 'LTFN'\n", fn_8022F3D4(fn_8022F4BC()), &count);
    return count;
}
}
