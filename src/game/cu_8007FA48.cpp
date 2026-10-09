#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/Record_80082B18.h"
#include "game/Query_8007F19C.h"
#include "game/fn_801FCE10.h"

extern "C" {
extern int lbl_802D68D0[];
extern int lbl_802D6950[];
extern int lbl_802D6990[];
int fn_801F95C8(void);
int fn_801FA0BC(int, void *, void *, void *, void *, int *, void *);
int fn_801FA148(int);
int fn_8022EF8C(int, int);
int fn_8022EFBC(int, int);
int fn_8022F358(int);
int fn_8022F3D4(int);
void fn_80082B18(Record_80082B18 *);
void fn_80082C64(Record_80082B18 *);
void fn_80082D30(Record_80082B18 *);
void fn_80082E48(Record_80082B18 *);
void fn_80083070(Record_80082B18 *);
void fn_8008318C(int, Record_80082B18 *, int, int);
void fn_800731D0(int);
}

/* These fast cursors are also accessed by the selector, fetch and close
   functions below. The halfword at +4 can be overwritten independently. */
extern "C" {
QueryCursor lbl_8030BC58;
QueryCursor lbl_8030BC68;
QueryCursor lbl_8030BC78;
}

extern "C" int fn_8007FA48(int table, int column, int *out, unsigned short *count, int start)
{
    QueryCursor cursor;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    int row;
    int result;
    if (start < 0)
        result = fn_801FCE10(0, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from \x8c order by 'DIGP' asc\n", table, &cursor, &row, column);
    else
        result = fn_801FCE10(0, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from \x8c where 'DIGP' >= \x82 order by 'DIGP' asc\n", table, &cursor, &row, column, start);
    int previous = start;
    int high = 0x7FFF;
    int next = -1;
    unsigned short filled = 0;
    while (result == 0 && filled < *count) {
        result = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        if (result != 0) break;
        if (row > previous + 1) {
            next = previous + 1;
            while (result == 0 && next < row && filled < *count && next <= 0x7F14) {
                out[filled++] = next++;
            }
        }
        high = next > row ? next : row;
        previous = row;
    }
    int valid = 0;
    if (result == 0 || result == 23 || result == 21 || result == 20) valid = 1;
    if (valid == 1) {
        if (cursor.mUnknown0 != 0) result = fn_801FCFA0(&cursor);
        else result = 0;
    } else if (cursor.mUnknown0 != 0) fn_801FCFA0(&cursor);
    if (result == 0 && filled < *count) {
        next = high == 0x7FFF ? 0 : high + 1;
        while (filled < *count && next <= 0x7F14) out[filled++] = next++;
    }
    *count = filled;
    return result;
}

extern "C" int fn_8007FC70(int source, int value, int reset, int start)
{
    char first[16], last[16], other[16];
    Record_80082B18 record;
    first[0] = 0;
    last[0] = 0;
    fn_80082B18(&record);
    record.mUnknown04 = first;
    record.mUnknown08 = last;
    record.mUnknown0C = other;
    unsigned short count = 1;
    fn_8007FA48(0x54415453, 0x59414C50, &record.mUnknown00, &count, start);
    record.mUnknown14 = value;
    record.mUnknown10 = value;
    fn_80082C64(&record);
    fn_800731D0(0);
    fn_80082D30(&record);
    fn_800731D0(0);
    fn_80082E48(&record);
    fn_800731D0(0);
    fn_80083070(&record);
    fn_800731D0(0);
    if (reset) {
        record.mUnknown10C = 0x41;
        record.mUnknown118 = 2;
        record.mUnknown1C = 1;
        record.mUnknown18 = 0;
        record.mUnknown110 = 0;
        record.mUnknownC8 = 0;
        record.mUnknownC4 = 0;
        record.mUnknownCC = 0;
        record.mUnknownD0 = 0;
        record.mUnknownD4 = 0;
        record.mUnknownD8 = 0;
        record.mUnknownDC = 0;
        record.mUnknownE0 = 0;
        record.mUnknownE4 = 0;
        record.mUnknownE8 = 0;
        record.mUnknownB8 = 0;
        record.mUnknownBC = 0;
        record.mUnknownC0 = 0;
        record.mUnknownA8 = 0;
        record.mUnknownAC = 0;
        record.mUnknownB0 = 0;
        record.mUnknownB4 = 0;
        record.mUnknown6C = 0;
        record.mUnknown70 = 0;
        record.mUnknown74 = 0;
        record.mUnknown84 = 0;
        record.mUnknown88 = 0;
        record.mUnknown8C = 0;
        record.mUnknown90 = 0;
        record.mUnknown94 = 0;
        record.mUnknown98 = 0;
        record.mUnknown9C = 0;
    }
    fn_800731D0(0);
    fn_8008318C(0x59414C50, &record, source, 0x1AD);
    fn_800731D0(0);
    return record.mUnknown00;
}

/* The query cursor identities are distinct in adjacent source. These
   wrappers use the common query entry point with this caller's object. */
extern "C" void fn_8007FE04(Object_8008044C *p, void *arg, int flags)
{
    fn_8007A334(reinterpret_cast<Object_8007A334 *>(p), 0x59414C50, 0x44494750, arg, 0, flags);
}
extern "C" void fn_8007FE40(Object_8008044C *p, void *arg, int selector, int flags)
{
    Object_80023BBC node;
    node.Set(6, 0x59414C5044494754LL, 3, selector);
    fn_8007A334(reinterpret_cast<Object_8007A334 *>(p), 0x59414C50, 0x44494750, arg, &node, flags);
}
extern "C" void fn_8007FEB8(Object_8008044C *p, void *arg, int flags)
{
    Object_80023BBC node;
    node.Set(6, 0x59414C5047494C50LL, 3, 1);
    fn_8007A334(reinterpret_cast<Object_8007A334 *>(p), 0x59414C50, 0x44494750, arg, &node, flags);
}
extern "C" void fn_8007FF30(Object_8008044C *p, void *arg, int selector, int flags)
{
    Object_80023BBC node;
    node.Set(6, 0x59414C5059545250LL, 3, selector);
    fn_8007A334(reinterpret_cast<Object_8007A334 *>(p), 0x59414C50, 0x44494750, arg, &node, flags);
}
extern "C" void fn_8007FFA8(Object_8008044C *p, void *arg, int selector, int value, int flags)
{
    Object_80023BBC root, left, right;
    root.Set(11, &left, &right);
    left.Set(6, 0x59414C5044494754LL, 3, selector);
    right.SetUnknown32(6, 0x59414C5044494750LL, 3, 0x10006);
    right.mUnknown16.mValue.mInt = value;
    fn_8007A334(reinterpret_cast<Object_8007A334 *>(p), 0x59414C50, 0x44494750, arg, &root, flags);
}
extern "C" void fn_80080084(int value, int handle, int table, ColumnValue_802D6424 *columns)
{
    Result_8007F19C result;
    Table_8007F19C tables[2];
    Expression_8007F19C node;
    tables[0].Set(table, 2, &node);
    tables[1].Set(-1);
    node.Set((static_cast<unsigned long long>(static_cast<unsigned int>(table)) << 32) | 0x44494750, 0x10003, value);
    fn_801FA428(handle, tables, 0, columns, &result, 0);
}

extern "C" void fn_80080138(int selector, int index, int mode)
{
    if (index == -1 && mode == 0) return;
    int cursor = 0;
    int source, destination, from, to;
    int created = 0;
    if (mode) {
        from = 0x52475250;
        if (index == -1) {
            destination = 0x54415453;
            fn_8022EF8C(destination, from);
            created = 1;
        } else destination = fn_8022F3D4(fn_8022F358(index));
        source = 0x54415453;
        to = 0x59414C50;
    } else {
        source = fn_8022F3D4(fn_8022F358(index));
        destination = 0x54415453;
        from = 0x59414C50;
        to = 0x52475250;
    }
    Table_8007F19C tables[2];
    Expression_8007F19C node;
    ColumnValue_802D6424 columns[24];
    for (int i = 0; i < 22; ++i) columns[i].Set(from, lbl_802D68D0[i], 0);
    columns[22].Set(from, 0x44494750, 0);
    columns[23].SetEnd();
    if (selector == 0x3FF) tables[0].Set(from);
    else {
        node.Set((static_cast<unsigned long long>(static_cast<unsigned int>(from)) << 32) | 0x44494754, 0x10003, selector);
        tables[0].mTag = from;
        tables[0].mUnknown4 = 2;
        tables[0].mFilter = &node;
    }
    tables[1].Set(-1);
    char unknown[16];
    int result = fn_801FA0BC(source, tables, 0, 0, 0, &cursor, unknown);
    if (result != 23) {
        if (fn_801FA228(cursor, 1, 0, columns) == 0) {
            do {
                for (int i = 21; i >= 0; --i) columns[i].mTableTag = to;
                columns[22].mTableTag = -1;
                columns[22].mColumnTag = -1;
                fn_80080084(columns[22].mValue, destination, to, columns);
                for (int i = 21; i >= 0; --i) columns[i].mTableTag = from;
                columns[22].mColumnTag = 0x44494750;
                columns[22].mTableTag = from;
            } while (fn_801FA228(cursor, 0, 1, columns) == 0);
        }
    }
    fn_801FA148(cursor);
    if (created) fn_8022EFBC(0x54415453, from);
}

extern "C" void fn_8008040C(Object_8008044C *p, Desc_8008044C *desc)
{
    int tag = fn_801F95C8();
    fn_8008044C(p, desc, tag);
}
extern "C" void fn_8008044C(Object_8008044C *p, Desc_8008044C *desc, int tag)
{
    Desc_8008044C local;
    if (desc) {
        local.mUnknown0 = desc->mUnknown0;
        local.mUnknown4 = desc->mUnknown4;
        local.mUnknown8 = desc->mUnknown8;
        local.mUnknown12 = desc->mUnknown12;
    }
    void *arg = 0;
    switch (local.mUnknown0) {
    case 1: arg = lbl_802D6950; break;
    case 2: arg = lbl_802D6990; break;
    }
    switch (local.mUnknown4) {
    case 0: fn_8007FE04(p, arg, tag); break;
    case 1: fn_8007FE40(p, arg, local.mUnknown8, tag); break;
    case 2: fn_8007FEB8(p, arg, tag); break;
    case 3: fn_8007FF30(p, arg, local.mUnknown8, tag); break;
    case 4: fn_8007FFA8(p, arg, local.mUnknown8, local.mUnknown12, tag); break;
    }
}
extern "C" void fn_8008056C(Object_8008044C *p)
{
    fn_8007A3C4(reinterpret_cast<Object_8007A334 *>(p));
}

extern "C" int fn_8008058C(int *id, int *pos, int *value, int a, int b, int c, int mode)
{
    unsigned short result = 0;
    if (static_cast<unsigned int>(b) > 15) b = a;
    if (static_cast<unsigned int>(c) > 15) c = a;
    switch (mode) {
    case 0:
        lbl_8030BC58.mUnknown0 = 0;
        lbl_8030BC58.mUnknown8 = -1;
        lbl_8030BC58.mUnknown12 = 0;
        lbl_8030BC58.mUnknown4 = 0;
        if (a != 255 && a != -1)
            fn_801FCE10(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 and 'OPBP' into \x82 and 'PXSP' into \x82 from 'YALP' where (('OPBP' = \x82) or ('OPBP' = \x82) or ('OPBP' = \x82)) and ('DIGT' >= 1 && 'DIGT' <= 32) order by 'DIGP' asc\n", &lbl_8030BC58, id, pos, value, a, b, c);
        else
            fn_801FCE10(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 and 'OPBP' into \x82 and 'PXSP' into \x82 from 'YALP' where ('DIGT' >= 1 && 'DIGT' <= 32) order by 'DIGP' asc\n", &lbl_8030BC58, id, pos, value);
        break;
    case 1:
        lbl_8030BC68.mUnknown0 = 0;
        lbl_8030BC68.mUnknown8 = -1;
        lbl_8030BC68.mUnknown12 = 0;
        lbl_8030BC68.mUnknown4 = 0;
        if (a != 255 && a != -1)
            fn_801FCE10(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 and 'OPBP' into \x82 and 'PXSP' into \x82 from 'YALP' where (('OPBP' = \x82) or ('OPBP' = \x82) or ('OPBP' = \x82)) and ('DIGT' = \x82) order by 'DIGP' asc\n", &lbl_8030BC68, id, pos, value, a, b, c, 34);
        else
            fn_801FCE10(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 and 'OPBP' into \x82 and 'PXSP' into \x82 from 'YALP' where ('DIGT' = \x82) order by 'DIGP' asc\n", &lbl_8030BC68, id, pos, value, 34);
        break;
    case 2:
        lbl_8030BC78.mUnknown0 = 0;
        lbl_8030BC78.mUnknown8 = -1;
        lbl_8030BC78.mUnknown12 = 0;
        lbl_8030BC78.mUnknown4 = 0;
        if (a != 255 && a != -1)
            fn_801FCE10(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 and 'OPBP' into \x82 and 'PXSP' into \x82 from 'YALP' where (('OPBP' = \x82) or ('OPBP' = \x82) or ('OPBP' = \x82)) and ('YTRP' = \x82) order by 'DIGP' asc\n", &lbl_8030BC78, id, pos, value, a, b, c, 1);
        else
            fn_801FCE10(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 and 'OPBP' into \x82 and 'PXSP' into \x82 from 'YALP' where ('YTRP' = \x82) order by 'DIGP' asc\n", &lbl_8030BC78, id, pos, value, 1);
        break;
    }
    return result;
}
extern "C" void fn_8008079C(int which)
{
    switch (which) {
    case 0: fn_801FCE10(0, "fetch from \x8a\n", &lbl_8030BC58); break;
    case 1: fn_801FCE10(0, "fetch from \x8a\n", &lbl_8030BC68); break;
    case 2: fn_801FCE10(0, "fetch from \x8a\n", &lbl_8030BC78); break;
    }
}
extern "C" void fn_8008082C(unsigned short value, int which)
{
    switch (which) {
    case 0: lbl_8030BC58.mUnknown4 = value; break;
    case 1: lbl_8030BC68.mUnknown4 = value; break;
    case 2: lbl_8030BC78.mUnknown4 = value; break;
    }
}
extern "C" void fn_80080874(int which)
{
    switch (which) {
    case 0: if (lbl_8030BC58.mUnknown0) fn_801FCFA0(&lbl_8030BC58); break;
    case 1: if (lbl_8030BC68.mUnknown0) fn_801FCFA0(&lbl_8030BC68); break;
    case 2: if (lbl_8030BC78.mUnknown0) fn_801FCFA0(&lbl_8030BC78); break;
    }
}
