/* User profiles: which saved profile each controller pad has selected, how
   recently each profile was used, creating and deleting profiles, adding a
   finished game's stats to the selected profiles and writing their record
   rows (high scores, style, streak and venue bests) to the save database,
   and the profile name shown for each pad. */

#include "game/fn_801FCE10.h"
#include "game/StyleTracker.h"
#include <string.h>
#include "game/fn_8022F478.h"
#include "game/GameModeType.h"
#include "game/Cheat.h"
#include "libc/string.h"

extern "C" {
int UserRecGetCount(void);
int UserRecGetName(int, char *);
int fn_8022F358(int);
void ChalCloseCursors(void);
void fn_8022F1BC(int);
void MemCardFilesRemoveSlot(int, int);
void MemCardFilesCopySlot(int, int, int, int);
void fn_80011894(int);
int UserRecGetGameStat(int, int, int, int, int);
void UserRecAddStat(int, int, int);
void UserRecUpdateStreak(int, int, int);
void RecordsPrune(void);
void fn_8022F294(int);
int fn_8022F0D4(int);
int fn_8022F794(int, char *);
int fn_8022F3D4(int);
void MemCardFilesResetSlot(int, int, int);
void MemCardFilesRenameSlot(int, int, char *);
int CheatIsNoneEnabled(void);
int fn_801485D4(void);
int fn_800A7E40(int);
int fn_800A7E54(int);
int fn_800A3444(void);
void UserRecAddRecent(int);
int UserProfileGetSelected(unsigned char);
void UserProfileTouch(int);
int UserProfileSaveRecords(unsigned char, int);
int UserProfileGetFreeKey(int, int, int, int);
void UserProfileSetVenueRecord(int, int, int);
void UserProfileAddBGSHRecord(int, int);
void UserProfileAddTGSHRecord(int, int);
void UserProfileUpdateStreakRecord(int, int, int);
void UserProfileAddStyleRecord(int, int);
}

struct UserProfileStat_t { int mKind; int mTable; int mColumn; int mProfileColumn; };
static UserProfileStat_t _UserProfile_aGameStats[] = {
    { 0x00000002, 0x00000000, 0x00000000, 0x776E5355 },
    { 0x00000003, 0x00000000, 0x00000000, 0x6C6E5355 },
    { 0x00000001, 0x00000000, 0x00000000, 0x46505250 },
    { 0x00000000, 0x41475354, 0x74727374, 0x74725355 },
    { 0x00000000, 0x41475354, 0x74507374, 0x74705355 },
    { 0x00000000, 0x41475354, 0x6B737374, 0x73645355 },
    { 0x00000000, 0x41475354, 0x74737374, 0x46535355 },
    { 0x00000000, 0x41475354, 0x69447374, 0x69645355 },
    { 0x00000000, 0x41475354, 0x66667374, 0x72665355 },
    { 0x00000000, 0x41475354, 0x64647374, 0x54445455 },
    { 0x00000004, 0x00000000, 0x00000000, 0x54505455 },
    { 0x00000005, 0x00000000, 0x00000000, 0x42475355 },
    { 0x00000006, 0x00000000, 0x00000000, 0x57535155 },
    { 0x00000007, 0x00000000, 0x00000000, 0x50505455 },
    { 0x00000008, 0x00000000, 0x00000000, 0x574F5355 },
    { 0x00000009, 0x00000000, 0x00000000, 0x4C4F5355 },
    { 0x0000000A, 0x00000000, 0x00000000, 0x534F5355 },
    { 0x0000000B, 0x00000000, 0x00000000, 0x414F5355 },
    { 0x0000000C, 0x00000000, 0x00000000, 0x54424755 },
    { 0x0000000D, 0x00000000, 0x00000000, 0x00000000 },
};
static signed char _UserProfile_aSelected[2];
static unsigned int _UserProfile_aRecency[2];
static unsigned int _UserProfile_uUseCounter = 0;
static char _UserProfile_aPadNames[4][13];

extern "C" {
void UserProfileDelete(signed char index)
{
    int count = UserRecGetCount();
    int db = fn_8022F358(index);
    ChalCloseCursors();
    fn_8022F1BC(db);
    for (int i = index; i < count; i = (signed char)(i + 1)) {
        MemCardFilesRemoveSlot(2, i);
        int next = i + 1;
        if (next < count) {
            MemCardFilesCopySlot(2, i, 2, next);
            _UserProfile_aRecency[i] = _UserProfile_aRecency[next];
        }
    }
    for (unsigned char pad = 0; pad < 2; pad++) {
        if (_UserProfile_aSelected[pad] >= 0) {
            if (_UserProfile_aSelected[pad] > index) _UserProfile_aSelected[pad]--;
            else if (_UserProfile_aSelected[pad] == index) _UserProfile_aSelected[pad] = -1;
        }
    }
    fn_80011894(index);
}
int UserProfileFindIndex(int db)
{
    int count = UserRecGetCount();
    signed char i = 0;
    int searching = 1;
    while (searching && i < count) {
        if (fn_8022F358((int)i) == db) searching = 0;
        else i++;
    }
    return i;
}
void UserProfileAddGameStats(void)
{
    if (UserProfileGetSelected(0) == -1 && UserProfileGetSelected(1) == -1) return;
    for (UserProfileStat_t *p = _UserProfile_aGameStats; p->mKind != 13; p++) {
        int value;
        if (UserProfileGetSelected(0) != -1) {
            value = UserRecGetGameStat(p->mKind, p->mTable, p->mColumn, 0, 1);
            UserRecAddStat(fn_8022F358(UserProfileGetSelected(0)), p->mProfileColumn, value);
        }
        if (UserProfileGetSelected(1) != -1) {
            value = UserRecGetGameStat(p->mKind, p->mTable, p->mColumn, 1, 0);
            UserRecAddStat(fn_8022F358(UserProfileGetSelected(1)), p->mProfileColumn, value);
        }
    }
    if (UserProfileGetSelected(0) != -1) UserRecUpdateStreak(fn_8022F358(UserProfileGetSelected(0)), 0, 1);
    if (UserProfileGetSelected(1) != -1) UserRecUpdateStreak(fn_8022F358(UserProfileGetSelected(1)), 1, 0);
}
void UserProfileSaveAllRecords(unsigned char *pFlags)
{
    unsigned char changed = 0;
    if (UserProfileGetSelected(0) != -1) changed = UserProfileSaveRecords(0, pFlags[0]);
    if (UserProfileGetSelected(1) != -1) changed |= UserProfileSaveRecords(1, pFlags[1]);
    if (changed) RecordsPrune();
}
int UserProfileGetOldest(int excluded)
{
    signed char best = -1;
    unsigned int value = 0;
    for (signed char i = 0; i < UserRecGetCount(); i++) {
        if (i != excluded) {
            if (best == -1) { best = i; value = _UserProfile_aRecency[best]; }
            else if (_UserProfile_aRecency[i] < value) { value = _UserProfile_aRecency[i]; best = i; }
        }
    }
    return best;
}
int UserProfileSortByRecent(signed char *pOrder, int capacity)
{
    signed char i;
    int count = UserRecGetCount();
    for (i = 0; i < capacity; i++) pOrder[i] = -1;
    for (i = 0; i < count; i++) pOrder[i] = i;
    for (signed char pass = count - 1; pass > 0; pass--) {
        for (i = 0; i < pass; i++) {
            if (_UserProfile_aRecency[pOrder[i]] < _UserProfile_aRecency[pOrder[i + 1]]) {
                signed char t = pOrder[i];
                pOrder[i] = pOrder[i + 1];
                pOrder[i + 1] = t;
            }
        }
    }
    return count;
}
void UserProfileTouch(int index) { _UserProfile_aRecency[index] = ++_UserProfile_uUseCounter; }
void UserProfileInit(void)
{
    _UserProfile_aSelected[0] = -1;
    _UserProfile_aSelected[1] = -1;
    memset(_UserProfile_aPadNames, 0, sizeof(_UserProfile_aPadNames));
}
void UserProfileSelect(signed char index, unsigned char pad)
{
    _UserProfile_aSelected[pad] = index;
    if (index != -1 && index < UserRecGetCount()) UserProfileTouch(index);
}
int UserProfileGetSelected(unsigned char pad) { return _UserProfile_aSelected[pad]; }
void UserProfileDeselect(int pad) { _UserProfile_aSelected[pad] = -1; }
void UserProfileCreate(int index, char *pName, int)
{
    int count = UserRecGetCount();
    int db;
    if (index <= count - 1) { db = fn_8022F358(index); fn_8022F294(db); }
    else { index = count; db = fn_8022F0D4(count); }
    fn_8022F794(db, pName);
    UserProfileTouch(index);
    fn_8022F478(fn_8022F358(index));
    MemCardFilesResetSlot(2, index, 0);
    MemCardFilesRenameSlot(2, index, pName);
}
int UserProfileSaveRecords(unsigned char pad, int allowCreate)
{
    char name[32]; QueryResult result;
    int v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18; int id = 0;
    int changed = 0; int code = 0; unsigned char busy = 0; // FAKEMATCH: code is a dead store target
    int selected = UserProfileGetSelected(pad);
    UserRecGetName(selected, name);
    int db = fn_8022F358(selected);
    fn_8022F478(db);
    int token = fn_8022F3D4(db);
    int status = fn_801FCE10(0, "use \x8C select 'wnSU' into \x82 and 'swSU' into \x82 and 'FPRP' into \x82 and 'tpSU' into \x82 and 'trSU' into \x82 and 'TDTU' into \x82 and 'FSSU' into \x82 and 'idSU' into \x82 and 'rfSU' into \x82 and 'BGSU' into \x82 and 'TBGU' into \x82 and 'TPTU' into \x82 and 'sdSU' into \x82 and 'FNWU' into \x82 and 'WSQU' into \x82 and 'WOSU' into \x82 and 'LOSU' into \x82 and 'SOSU' into \x82 and 'AOSU' into \x82 from 'TSPU'\n", token, &v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15, &v16, &v17, &v18);
    if (v1 < 0) v1 = 0;
    if (GameModeTypeGet() == 0) {
        if (UserProfileGetSelected(0) != -1) {
            CheatSelectSlot(UserProfileGetSelected(0)); busy |= CheatIsNoneEnabled() == 0; CheatClearSlot();
        }
        if (UserProfileGetSelected(1) != -1) {
            CheatSelectSlot(UserProfileGetSelected(1)); busy |= CheatIsNoneEnabled() == 0; CheatClearSlot();
        }
    }
    if (status == 0 && !busy) {
        status = fn_801FCE10(&result, "use 'EVAS' select 'KPSH' into \x82 from 'RCSH' where 'KUSH' = \x88\n", &id, name);
        if (status != 0 && status != 23) code = status; // FAKEMATCH: dead store of the error status
        if (status == 23) {
            if (allowCreate) {
                id = UserProfileGetFreeKey(0x52435348, 0x4B505348, 0, 255);
                if (id != -1) {
                fn_801FCE10(&result, "use 'EVAS' insert into 'RCSH' set 'KPSH' = \x82 and 'KUSH' = \x88 and 'WGSH' = \x82 and 'LGSH' = \x82 and 'PTSH' = \x82 and 'TPSH' = \x82 and 'TRSH' = \x82 and 'TDSH' = \x82 and 'TSSH' = \x82 and 'CISH' = \x82 and 'RFSH' = \x82 and 'GTSH' = \x82 and '2TSH' = \x82 and 'TTSH' = \x82 and 'KSSH' = \x82 and 'WQSH' = \x82 and 'WOSH' = \x82 and 'LOSH' = \x82 and 'SOSH' = \x82 and 'AOSH' = \x82\n", id, name, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v14, v15, v16, v17, v18);
                changed = 1; // FAKEMATCH: set after the insert call (order found by search; same result)
                }
            } else id = -1;
        } else {
            changed = 1;
            fn_801FCE10(&result, "use 'EVAS' update 'RCSH' set 'KUSH' = \x88 and 'WGSH' = \x82 and 'LGSH' = \x82 and 'PTSH' = \x82 and 'TPSH' = \x82 and 'TRSH' = \x82 and 'TDSH' = \x82 and 'TSSH' = \x82 and 'CISH' = \x82 and 'RFSH' = \x82 and 'GTSH' = \x82 and '2TSH' = \x82 and 'TTSH' = \x82 and 'KSSH' = \x82 and 'WQSH' = \x82 and 'WOSH' = \x82 and 'LOSH' = \x82 and 'SOSH' = \x82 and 'AOSH' = \x82 where 'KUSH' = \x88\n", name, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v14, v15, v16, v17, v18, name);
        }
    } else id = -1;
    if (id != -1 && !fn_801485D4()) {
        int side = StyleTrackerGetTotal(pad);
        UserProfileAddStyleRecord(id, side);
        int a = fn_800A7E40(pad);
        UserProfileAddBGSHRecord(id, a);
        int b = fn_800A7E54(pad);
        UserProfileAddTGSHRecord(id, b);
        UserProfileUpdateStreakRecord(id, v1, 0);
        UserProfileSetVenueRecord(fn_800A3444(), id, side);
    }
    return changed;
}
int UserProfileGetFreeKey(int kind, int key, int first, int last)
{
    QueryResult result; int found = -1; int value = -1; int scratch; int code = 0; // FAKEMATCH: code is a dead store target
    fn_801FCE10(&result, "use 'EVAS' select max(\x8C) into \x82 from \x8C\n", key, &value, kind);
    if (value < last) found = value + 1;
    else {
        fn_801FCE10(&result, "use 'EVAS' select count(*) into \x82 from \x8C\n", &value, kind);
        if (value < last) {
            for (value = first; value <= last; value++) {
                int status = fn_801FCE10(&result, "use 'EVAS' select \x8C into \x82 from \x8C where \x8C = \x82\n", key, &scratch, kind, key, value);
                if (status != 0 && status != 23) code = status; // FAKEMATCH: dead store of the error status
                if (status == 23) { found = value; break; }
            }
        }
    }
    return found;
}
void UserProfileSetVenueRecord(int event, int id, int value)
{
    QueryResult result; int previous;
    if (fn_801FCE10(&result, "use 'EVAS' select 'KTFH' into \x82 from 'DFSH' where 'DIVE' = \x82\n", &previous, event) == 0 && value > previous)
        fn_801FCE10(&result, "use 'EVAS' update 'DFSH' set 'KUFH' = \x82 and 'KTFH' = \x82 where 'DIVE' = \x82\n", id, value, event);
}
void UserProfileAddBGSHRecord(int id, int value)
{
    QueryResult result; int previous;
    if (fn_801FCE10(&result, "use 'EVAS' select min('TPGH') into \x82 from 'BGSH'\n", &previous) == 0 && value > previous) {
        int key = UserProfileGetFreeKey(0x42475348, 0x4B504748, 0, 15);
        fn_801FCE10(&result, "use 'EVAS' insert into 'BGSH' set 'KPGH' = \x82 and 'KUGH' = \x82 and 'TPGH' = \x82\n", key, id, value);
    }
}
void UserProfileAddTGSHRecord(int id, int value)
{
    QueryResult result; int previous;
    if (fn_801FCE10(&result, "use 'EVAS' select min('TPGH') into \x82 from 'TGSH'\n", &previous) == 0 && value > previous) {
        int key = UserProfileGetFreeKey(0x54475348, 0x4B504748, 0, 15);
        fn_801FCE10(&result, "use 'EVAS' insert into 'TGSH' set 'KPGH' = \x82 and 'KPSH' = \x82 and 'TPGH' = \x82\n", key, id, value);
    }
}
void UserProfileUpdateStreakRecord(int id, int value, int retry)
{
    QueryResult result; int minimum, previous;
    if (fn_801FCE10(&result, "use 'EVAS' select min('SWWH') into \x82 from 'SWSH'\n", &minimum) != 0) return;
    if (fn_801FCE10(&result, "use 'EVAS' select 'SWWH' into \x82 from 'SWSH' where 'KUWH' = \x82 and 'CIWH' = 1\n", &previous, id) == 23) {
        if (value > minimum) {
            int key = UserProfileGetFreeKey(0x53575348, 0x4B505748, 0, 15);
            fn_801FCE10(&result, "use 'EVAS' insert into 'SWSH' set 'KPWH' = \x82 and 'KUWH' = \x82 and 'SWWH' = \x82 and 'CIWH' = 1\n", key, id, value);
        }
    } else if (value <= 0) {
        fn_801FCE10(&result, "use 'EVAS' update 'SWSH' set 'CIWH' = 0 where 'KUWH' = \x82 and 'CIWH' = 1\n", id);
    } else if (value >= previous) {
        fn_801FCE10(&result, "use 'EVAS' update 'SWSH' set 'SWWH' = \x82 where 'KUWH' = \x82 and 'CIWH' = 1\n", value, id);
    } else {
        fn_801FCE10(&result, "use 'EVAS' update 'SWSH' set 'CIWH' = 0 where 'KUWH' = \x82 and 'CIWH' = 1\n", id);
        if (!retry) UserProfileUpdateStreakRecord(id, value, 1);
    }
}
void UserProfileAddStyleRecord(int id, int value)
{
    QueryResult result; int previous;
    if (fn_801FCE10(&result, "use 'EVAS' select min('TPTH') into \x82 from 'KTSH'\n", &previous) == 0 && value > previous) {
        int key = UserProfileGetFreeKey(0x4B545348, 0x4B505448, 0, 15);
        fn_801FCE10(&result, "use 'EVAS' insert into 'KTSH' set 'KPTH' = \x82 and 'KUTH' = \x82 and 'TPTH' = \x82\n", key, id, value);
    }
}
void UserProfileAddRecordRow(int index)
{
    // FAKEMATCH: code only receives a dead store of the error status below
    char name[32]; int id = 0; int code = 0; int v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12 = 0;
    UserRecGetName(index, name);
    int db = fn_8022F358(index);
    fn_8022F478(db);
    int token = fn_8022F3D4(db);
    int status = fn_801FCE10(0, "use 'EVAS' select 'KPSH' into \x82 from 'RCSH' where 'KUSH' = \x88\n", &id, name);
    if (status != 0 && status != 23) code = status; // FAKEMATCH: dead store of the error status
    if (status == 23) {
        id = UserProfileGetFreeKey(0x52435348, 0x4B505348, 0, 255);
        if (id == -1) return;
        if (fn_801FCE10(0, "use \x8C select 'wnSU' into \x82 and 'swSU' into \x82 and 'FPRP' into \x82 and 'tpSU' into \x82 and 'trSU' into \x82 and 'TDTU' into \x82 and 'FSSU' into \x82 and 'idSU' into \x82 and 'rfSU' into \x82 and 'BGSU' into \x82 and 'TBGU' into \x82 and 'TPTU' into \x82 and 'FNWU' into \x82 from 'TSPU'\n", token, &v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12) == 0)
            fn_801FCE10(0, "use 'EVAS' insert into 'RCSH' set 'KPSH' = \x82 and 'KUSH' = \x88 and 'WGSH' = \x82 and 'LGSH' = \x82 and 'PTSH' = \x82 and 'TPSH' = \x82 and 'TRSH' = \x82 and 'TDSH' = \x82 and 'TSSH' = \x82 and 'CISH' = \x82 and 'RFSH' = \x82 and 'GTSH' = \x82 and '2TSH' = \x82 and 'TTSH' = \x82 and 'CNWH' = \x82\n", id, name, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
    }
    if (id != -1) UserRecAddRecent(id);
}
void UserProfileSetPadName(unsigned char index, char *pText)
{
    if (pText) strncpy(_UserProfile_aPadNames[index], pText, 13);
    else _UserProfile_aPadNames[index][0] = 0;
}
int UserProfileGetPadName(unsigned char index, char *pText, int count)
{
    int present = 0;
    if (_UserProfile_aPadNames[index][0]) {
        present = 1;
        if (pText) strncpy(pText, _UserProfile_aPadNames[index], count);
    }
    return present;
}
}
