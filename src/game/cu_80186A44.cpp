#include "game/fn_801FCE10.h"
#include "game/fn_801C1F94.h"
#include "game/fn_8022F478.h"
#include "game/fn_8017F584.h"
#include "game/cu_80190208.h"
#include "libc/string.h"

extern "C" {
int fn_801869F0(void);
int fn_80186A10(int, char *);
int fn_8022F358(int);
void fn_80077F24(void);
void fn_8022F1BC(int);
void fn_80029DCC(int, int);
void fn_80029E90(int, int, int, int);
void fn_80011894(int);
int fn_80186518(int, int, int, int, int);
void fn_80186808(int, int, int);
void fn_80186714(int, int, int);
void fn_8007D654(void);
void fn_8022F294(int);
int fn_8022F0D4(int);
void fn_8022F794(int, char *);
int fn_8022F3D4(int);
void fn_80029C2C(int, int, int);
void fn_8002A1D4(int, int, char *);
int fn_80190394(void);
int fn_801485D4(void);
int fn_800D41F8(int);
int fn_800A7E40(int);
int fn_800A7E54(int);
int fn_800A3444(void);
void fn_8018689C(int);
int fn_80186F7C(unsigned char);
void fn_80186ED8(int);
int fn_80187038(unsigned char, int);
int fn_80187400(int, int, int, int);
void fn_80187500(int, int, int);
void fn_80187580(int, int);
void fn_80187614(int, int);
void fn_801876A8(int, int, int);
void fn_801877E8(int, int);
}

struct Entry_80186BAC { int mKind; int mArg4; int mArg8; int mKey; };
static Entry_80186BAC lbl_802EAA40[] = {
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
static signed char lbl_803ECB88[2];
extern unsigned int lbl_803ECB8C[];
static unsigned int lbl_803EB5E0 = 0;
static char lbl_80362B7C[4][13];

extern "C" {
void fn_80186A44(signed char index)
{
    int count = fn_801869F0();
    int db = fn_8022F358(index);
    fn_80077F24();
    fn_8022F1BC(db);
    for (int i = index; i < count; i = (signed char)(i + 1)) {
        fn_80029DCC(2, i);
        int next = i + 1;
        if (next < count) {
            fn_80029E90(2, i, 2, next);
            lbl_803ECB8C[i] = lbl_803ECB8C[next];
        }
    }
    for (unsigned char pad = 0; pad < 2; pad++) {
        if (lbl_803ECB88[pad] >= 0) {
            if (lbl_803ECB88[pad] > index) lbl_803ECB88[pad]--;
            else if (lbl_803ECB88[pad] == index) lbl_803ECB88[pad] = -1;
        }
    }
    fn_80011894(index);
}
int fn_80186B38(int db)
{
    int count = fn_801869F0();
    signed char i = 0;
    int searching = 1;
    while (i < count && searching) {
        if (fn_8022F358((int)i) == db) searching = 0;
        else i++;
    }
    return i;
}
void fn_80186BAC(void)
{
    if (fn_80186F7C(0) == -1 && fn_80186F7C(1) == -1) return;
    for (Entry_80186BAC *p = lbl_802EAA40; p->mKind != 13; p++) {
        if (fn_80186F7C(0) != -1) {
            int value = fn_80186518(p->mKind, p->mArg4, p->mArg8, 0, 1);
            fn_80186808(fn_8022F358(fn_80186F7C(0)), p->mKey, value);
        }
        if (fn_80186F7C(1) != -1) {
            int value = fn_80186518(p->mKind, p->mArg4, p->mArg8, 1, 0);
            fn_80186808(fn_8022F358(fn_80186F7C(1)), p->mKey, value);
        }
    }
    if (fn_80186F7C(0) != -1) fn_80186714(fn_8022F358(fn_80186F7C(0)), 0, 1);
    if (fn_80186F7C(1) != -1) fn_80186714(fn_8022F358(fn_80186F7C(1)), 1, 0);
}
void fn_80186CE8(unsigned char *pFlags)
{
    unsigned char changed = 0;
    if (fn_80186F7C(0) != -1) changed = fn_80187038(0, pFlags[0]);
    if (fn_80186F7C(1) != -1) changed |= fn_80187038(1, pFlags[1]);
    if (changed) fn_8007D654();
}
int fn_80186D64(int excluded)
{
    signed char best = -1;
    unsigned int value = 0;
    for (signed char i = 0; i < fn_801869F0(); i++) {
        if (i != excluded) {
            if (best == -1) { best = i; value = lbl_803ECB8C[best]; }
            else if (lbl_803ECB8C[i] < value) { value = lbl_803ECB8C[i]; best = i; }
        }
    }
    return best;
}
int fn_80186DF0(signed char *pOrder, int capacity)
{
    int count = fn_801869F0();
    for (signed char i = 0; i < capacity; i++) pOrder[i] = -1;
    for (signed char i = 0; i < count; i++) pOrder[i] = i;
    for (signed char pass = count - 1; pass > 0; pass--) {
        for (signed char i = 0; i < pass; i++) {
            signed char a = pOrder[i], b = pOrder[i + 1];
            if (lbl_803ECB8C[a] < lbl_803ECB8C[b]) {
                pOrder[i] = b; pOrder[i + 1] = a;
            }
        }
    }
    return count;
}
void fn_80186ED8(int index) { lbl_803ECB8C[index] = ++lbl_803EB5E0; }
void fn_80186EF4(void)
{
    lbl_803ECB88[1] = -1;
    lbl_803ECB88[0] = -1;
    fn_801C1F94(lbl_80362B7C, 0, sizeof(lbl_80362B7C));
}
void fn_80186F30(signed char index, unsigned char pad)
{
    lbl_803ECB88[pad] = index;
    if (index != -1 && index < fn_801869F0()) fn_80186ED8(index);
}
int fn_80186F7C(unsigned char pad) { return lbl_803ECB88[pad]; }
void fn_80186F8C(int pad) { lbl_803ECB88[pad] = -1; }
void fn_80186F9C(int index, char *pName, int)
{
    int count = fn_801869F0();
    int db;
    if (index <= count - 1) { db = fn_8022F358(index); fn_8022F294(db); }
    else { index = count; db = fn_8022F0D4(count); }
    fn_8022F794(db, pName);
    fn_80186ED8(index);
    fn_8022F478(fn_8022F358(index));
    fn_80029C2C(2, index, 0);
    fn_8002A1D4(2, index, pName);
}
int fn_80187038(unsigned char pad, int allowCreate)
{
    char name[32]; QueryResult result;
    int v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16, v17, v18; int id = 0;
    int changed = 0;
    int selected = fn_80186F7C(pad);
    fn_80186A10(selected, name);
    int db = fn_8022F358(selected);
    fn_8022F478(db);
    int token = fn_8022F3D4(db);
    int status = fn_801FCE10(0, "use \x8C select 'wnSU' into \x82 and 'swSU' into \x82 and 'FPRP' into \x82 and 'tpSU' into \x82 and 'trSU' into \x82 and 'TDTU' into \x82 and 'FSSU' into \x82 and 'idSU' into \x82 and 'rfSU' into \x82 and 'BGSU' into \x82 and 'TBGU' into \x82 and 'TPTU' into \x82 and 'sdSU' into \x82 and 'FNWU' into \x82 and 'WSQU' into \x82 and 'WOSU' into \x82 and 'LOSU' into \x82 and 'SOSU' into \x82 and 'AOSU' into \x82 from 'TSPU'\n", token, &v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9, &v10, &v11, &v12, &v13, &v14, &v15, &v16, &v17, &v18);
    if (v1 < 0) v1 = 0;
    int busy = 0;
    if (fn_8017F584() == 0) {
        if (fn_80186F7C(0) != -1) {
            fn_80190280(fn_80186F7C(0)); busy = !fn_80190394(); fn_80190288();
        }
        if (fn_80186F7C(1) != -1) {
            fn_80190280(fn_80186F7C(1)); busy |= !fn_80190394(); fn_80190288();
        }
    }
    if (status != 0 || busy) id = -1;
    else {
        status = fn_801FCE10(&result, "use 'EVAS' select 'KPSH' into \x82 from 'RCSH' where 'KUSH' = \x88\n", &id, name);
        if (status == 23) {
            if (allowCreate) {
                id = fn_80187400(0x52435348, 0x4B505348, 0, 255);
                if (id == -1) return changed;
                changed = 1;
                fn_801FCE10(&result, "use 'EVAS' insert into 'RCSH' set 'KPSH' = \x82 and 'KUSH' = \x88 and 'WGSH' = \x82 and 'LGSH' = \x82 and 'PTSH' = \x82 and 'TPSH' = \x82 and 'TRSH' = \x82 and 'TDSH' = \x82 and 'TSSH' = \x82 and 'CISH' = \x82 and 'RFSH' = \x82 and 'GTSH' = \x82 and '2TSH' = \x82 and 'TTSH' = \x82 and 'KSSH' = \x82 and 'WQSH' = \x82 and 'WOSH' = \x82 and 'LOSH' = \x82 and 'SOSH' = \x82 and 'AOSH' = \x82\n", id, name, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v14, v15, v16, v17, v18);
            } else id = -1;
        } else {
            changed = 1;
            fn_801FCE10(&result, "use 'EVAS' update 'RCSH' set 'KUSH' = \x88 and 'WGSH' = \x82 and 'LGSH' = \x82 and 'PTSH' = \x82 and 'TPSH' = \x82 and 'TRSH' = \x82 and 'TDSH' = \x82 and 'TSSH' = \x82 and 'CISH' = \x82 and 'RFSH' = \x82 and 'GTSH' = \x82 and '2TSH' = \x82 and 'TTSH' = \x82 and 'KSSH' = \x82 and 'WQSH' = \x82 and 'WOSH' = \x82 and 'LOSH' = \x82 and 'SOSH' = \x82 and 'AOSH' = \x82 where 'KUSH' = \x88\n", name, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v14, v15, v16, v17, v18, name);
        }
    }
    if (id != -1 && !fn_801485D4()) {
        int side = fn_800D41F8(pad);
        fn_801877E8(id, side);
        fn_80187580(id, fn_800A7E40(pad));
        fn_80187614(id, fn_800A7E54(pad));
        fn_801876A8(id, v1, 0);
        fn_80187500(fn_800A3444(), id, side);
    }
    return changed;
}
int fn_80187400(int kind, int key, int first, int last)
{
    QueryResult result; int value = -1; int found = -1; int scratch;
    fn_801FCE10(&result, "use 'EVAS' select max(\x8C) into \x82 from \x8C\n", key, &value, kind);
    if (value < last) found = value + 1;
    else {
        fn_801FCE10(&result, "use 'EVAS' select count(*) into \x82 from \x8C\n", &value, kind);
        if (value < last) {
            for (value = first; value <= last; value++) {
                int status = fn_801FCE10(&result, "use 'EVAS' select \x8C into \x82 from \x8C where \x8C = \x82\n", key, &scratch, kind, key, value);
                if (status == 23) { found = value; break; }
            }
        }
    }
    return found;
}
void fn_80187500(int event, int id, int value)
{
    QueryResult result; int previous;
    if (fn_801FCE10(&result, "use 'EVAS' select 'KTFH' into \x82 from 'DFSH' where 'DIVE' = \x82\n", &previous, event) == 0 && value > previous)
        fn_801FCE10(&result, "use 'EVAS' update 'DFSH' set 'KUFH' = \x82 and 'KTFH' = \x82 where 'DIVE' = \x82\n", id, value, event);
}
void fn_80187580(int id, int value)
{
    QueryResult result; int previous;
    if (fn_801FCE10(&result, "use 'EVAS' select min('TPGH') into \x82 from 'BGSH'\n", &previous) == 0 && value > previous) {
        int key = fn_80187400(0x42475348, 0x4B504748, 0, 15);
        fn_801FCE10(&result, "use 'EVAS' insert into 'BGSH' set 'KPGH' = \x82 and 'KUGH' = \x82 and 'TPGH' = \x82\n", key, id, value);
    }
}
void fn_80187614(int id, int value)
{
    QueryResult result; int previous;
    if (fn_801FCE10(&result, "use 'EVAS' select min('TPGH') into \x82 from 'TGSH'\n", &previous) == 0 && value > previous) {
        int key = fn_80187400(0x54475348, 0x4B504748, 0, 15);
        fn_801FCE10(&result, "use 'EVAS' insert into 'TGSH' set 'KPGH' = \x82 and 'KPSH' = \x82 and 'TPGH' = \x82\n", key, id, value);
    }
}
void fn_801876A8(int id, int value, int retry)
{
    QueryResult result; int minimum, previous;
    if (fn_801FCE10(&result, "use 'EVAS' select min('SWWH') into \x82 from 'SWSH'\n", &minimum) != 0) return;
    if (fn_801FCE10(&result, "use 'EVAS' select 'SWWH' into \x82 from 'SWSH' where 'KUWH' = \x82 and 'CIWH' = 1\n", &previous, id) == 23) {
        if (value > minimum) {
            int key = fn_80187400(0x53575348, 0x4B505748, 0, 15);
            fn_801FCE10(&result, "use 'EVAS' insert into 'SWSH' set 'KPWH' = \x82 and 'KUWH' = \x82 and 'SWWH' = \x82 and 'CIWH' = 1\n", key, id, value);
        }
    } else if (value <= 0) {
        fn_801FCE10(&result, "use 'EVAS' update 'SWSH' set 'CIWH' = 0 where 'KUWH' = \x82 and 'CIWH' = 1\n", id);
    } else if (value >= previous) {
        fn_801FCE10(&result, "use 'EVAS' update 'SWSH' set 'SWWH' = \x82 where 'KUWH' = \x82 and 'CIWH' = 1\n", value, id);
    } else {
        fn_801FCE10(&result, "use 'EVAS' update 'SWSH' set 'CIWH' = 0 where 'KUWH' = \x82 and 'CIWH' = 1\n", id);
        if (!retry) fn_801876A8(id, value, 1);
    }
}
void fn_801877E8(int id, int value)
{
    QueryResult result; int previous;
    if (fn_801FCE10(&result, "use 'EVAS' select min('TPTH') into \x82 from 'KTSH'\n", &previous) == 0 && value > previous) {
        int key = fn_80187400(0x4B545348, 0x4B505448, 0, 15);
        fn_801FCE10(&result, "use 'EVAS' insert into 'KTSH' set 'KPTH' = \x82 and 'KUTH' = \x82 and 'TPTH' = \x82\n", key, id, value);
    }
}
void fn_8018787C(int index)
{
    char name[32]; int v[13]; int id = 0;
    v[12] = 0;
    fn_80186A10(index, name);
    int db = fn_8022F358(index);
    fn_8022F478(db);
    int token = fn_8022F3D4(db);
    if (fn_801FCE10(0, "use 'EVAS' select 'KPSH' into \x82 from 'RCSH' where 'KUSH' = \x88\n", &id, name) == 23) {
        id = fn_80187400(0x52435348, 0x4B505348, 0, 255);
        if (id == -1) return;
        if (fn_801FCE10(0, "use \x8C select 'wnSU' into \x82 and 'swSU' into \x82 and 'FPRP' into \x82 and 'tpSU' into \x82 and 'trSU' into \x82 and 'TDTU' into \x82 and 'FSSU' into \x82 and 'idSU' into \x82 and 'rfSU' into \x82 and 'BGSU' into \x82 and 'TBGU' into \x82 and 'TPTU' into \x82 and 'FNWU' into \x82 from 'TSPU'\n", token, &v[0], &v[1], &v[2], &v[3], &v[4], &v[5], &v[6], &v[7], &v[8], &v[9], &v[10], &v[11], &v[12]) == 0)
            fn_801FCE10(0, "use 'EVAS' insert into 'RCSH' set 'KPSH' = \x82 and 'KUSH' = \x88 and 'WGSH' = \x82 and 'LGSH' = \x82 and 'PTSH' = \x82 and 'TPSH' = \x82 and 'TRSH' = \x82 and 'TDSH' = \x82 and 'TSSH' = \x82 and 'CISH' = \x82 and 'RFSH' = \x82 and 'GTSH' = \x82 and '2TSH' = \x82 and 'TTSH' = \x82 and 'CNWH' = \x82\n", id, name, v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9], v[10], v[11], v[12]);
    }
    if (id != -1) fn_8018689C(id);
}
void fn_80187A28(unsigned char index, char *pText)
{
    if (pText) strncpy(lbl_80362B7C[index], pText, 13);
    else lbl_80362B7C[index][0] = 0;
}
int fn_80187A78(unsigned char index, char *pText, int count)
{
    int present = 0;
    if (lbl_80362B7C[index][0]) {
        present = 1;
        if (pText) strncpy(pText, lbl_80362B7C[index], count);
    }
    return present;
}
}
