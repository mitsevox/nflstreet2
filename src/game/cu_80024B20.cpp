#include "game/Entry_80219044.h"
#include "game/Object_800785C0.h"
#include "game/cu_80067C10.h"
#include "game/fn_8007F828.h"
#include "game/fn_801C1F94.h"
#include "game/fn_8021D7B8.h"

/* Result list sent with message 0x80000083: a two-word header followed by
   the four results copied by fn_80025C88. */
struct Results_8037E088 {
    int mUnknown0;
    int mUnknown4;
    int mResults[4];
};

extern "C" {
extern void *lbl_803EB688;

int fn_800254E8(Object_800785C0 *pRecord, int a, int b);
int fn_80025708(void);
int fn_800257B4(int side, Object_800785C0 *pRecord, int index);
unsigned char fn_800254B4(Object_800785C0 *pRecord);

void fn_80078C50(int type, int value, char *pText, int size);
int fn_800796B8(int side, Object_800785C0 *pRecord, int index, int *pResult);
int fn_80079758(int side, Info_8007984C *pInfo);
int fn_800797F4(Object_800785C0 *pRecord, int a, int b);
int fn_8007984C(Object_800785C0 *pRecord);
int fn_8009D990(int index);
int fn_800A7E40(unsigned char side);
int fn_800B65A0(int side);
int fn_800D41F8(int side);
unsigned char fn_80174160(void);
int fn_80177F70(void);
int fn_80178308(void);
int fn_80178348(void);
int fn_801787DC(unsigned char side);
int fn_801788D8(int *pValue);
int fn_80178AE0(void);
int fn_8022B7A4(int handle, int tag, void *pValue);

static int lbl_803EBAF0 = 3;
static Entry_80219044 lbl_8037DF58[4];
static char lbl_8037DF88[4][64];
static Results_8037E088 lbl_8037E088;

int fn_80024C24(int side);

int fn_80024B20(int side, int limit, int flag)
{
    int value;
    int result;
    int own;
    int other;

    result = 2;
    switch (fn_801788D8(&value)) {
    case 0:
        own = fn_801787DC(side);
        other = fn_801787DC((side + 1) & 1);
        break;
    case 1:
        own = fn_800D41F8(side);
        other = fn_800D41F8((side + 1) & 1);
        break;
    default:
        return 2;
    }
    if (flag) {
        result = fn_80024C24(side);
        if (result == 0) {
            if (own - other < limit) {
                result = 1;
            }
        } else if (result == 2) {
            if (fn_8007F828(14) == 0 && value + 5 - limit < other) {
                result = 1;
            }
        }
    } else if (own - other >= limit) {
        result = 0;
    }
    return result;
}

int fn_80024C24(int side)
{
    int result = fn_80178AE0();

    if (result == 2) {
        return 2;
    }
    if (result == side) {
        return 0;
    }
    return 1;
}

int fn_80024C70(int side, int value)
{
    return fn_800D41F8(side) < value ? 2 : 0;
}

int fn_80024CA8(int side, unsigned int value)
{
    unsigned int stat;

    fn_8022B7A4(side, 0x73707374, &stat);
    if (stat >= value) {
        int current = fn_80174160();

        if (current != side || fn_80178308() != current) {
            return 3;
        }
    }
    return 0;
}

int fn_80024D18(int side, int other, unsigned int value)
{
    unsigned int a;
    unsigned int b;
    unsigned int total;

    fn_8022B7A4(side, 0x6E737374, &a);
    fn_8022B7A4(other, 0x6E737374, &b);
    total = a + b;
    if (total > value) {
        return 1;
    }
    if (total == value) {
        return 3;
    }
    return 0;
}

int fn_80024D94(int side)
{
    if (fn_800A7E40((side + 1) & 1)) {
        return 1;
    }
    return 0;
}

int fn_80024DCC(int side, unsigned int value)
{
    return fn_800A7E40(side) < value ? 2 : 0;
}

int fn_80024E08(int side, unsigned int value)
{
    unsigned int a;
    unsigned int b;
    unsigned int c;

    fn_8022B7A4(side, 0x74727374, &a);
    fn_8022B7A4(side, 0x74507374, &b);
    fn_8022B7A4(side, 0x64647374, &c);
    if (fn_800B65A0(side) == 0xFF) {
        return a + b + c > value;
    }
    return a + b + c < value ? 2 : 0;
}

int fn_80024EC0(int side, unsigned int value)
{
    return fn_801787DC(side) < value ? 2 : 0;
}

int fn_80024EFC(int side, unsigned int value)
{
    int mode;
    unsigned int own;

    switch (fn_801788D8(&mode)) {
    case 0:
        own = fn_801787DC(side);
        break;
    case 1:
        own = fn_800D41F8(side);
        break;
    default:
        return 2;
    }
    if (own > value) {
        return 1;
    }
    if (fn_800785C0()->mUnknown1A4 != 0 && fn_800254B4(fn_800785C0()) == 1) {
        if (fn_8009D990(4) == 0) {
            return 0;
        }
        return 2;
    }
    return 0;
}

int fn_80024FA8(int side, unsigned int value, int flag)
{
    unsigned int stat;

    fn_8022B7A4(side, 0x73707374, &stat);
    if (stat >= value) {
        int current = fn_80174160();

        if (current != side || fn_80178308() != current ||
            (flag && fn_80177F70() == 6)) {
            return 3;
        }
    }
    return 2;
}

int fn_80025030(int side, int other, unsigned int value)
{
    unsigned int a;
    unsigned int b;

    fn_8022B7A4(side, 0x6E737374, &a);
    fn_8022B7A4(other, 0x6E737374, &b);
    if (a + b >= value) {
        return 3;
    }
    return 2;
}

int fn_8002509C(int side, int value)
{
    int mode;
    int own;
    int other;

    switch (fn_801788D8(&mode)) {
    case 0:
        own = fn_801787DC(side);
        other = fn_801787DC((side + 1) & 1);
        break;
    case 1:
        own = fn_800D41F8(side);
        other = fn_800D41F8((side + 1) & 1);
        break;
    default:
        return 2;
    }
    if (own > other) {
        if (fn_800785C0()->mUnknown1A4 != 0) {
            if (fn_8009D990(4) == 0) {
                return 0;
            }
            return 2;
        }
        return 0;
    }
    return 2;
}

int fn_80025148(int side, unsigned int value)
{
    int a;
    int b;
    unsigned int scaled;

    fn_8022B7A4(side, 0x61707374, &a);
    fn_8022B7A4(side, 0x6E737374, &b);
    scaled = (float)a / (float)b * 100.0f;
    return scaled < value ? 2 : 0;
}

int fn_80025238(int side, int value)
{
    unsigned int a;
    unsigned int b;

    fn_8022B7A4(side, 0x74507374, &a);
    fn_8022B7A4(side, 0x74727374, &b);
    if (b != 0 || a != 0) {
        return 1;
    }
    return 0;
}

int fn_800252A8(int side, int value)
{
    int a;
    int b;
    int c;
    int total;

    fn_8022B7A4(side, 0x73707374, &a);
    fn_8022B7A4(side, 0x74507374, &b);
    fn_8022B7A4(side, 0x74727374, &c);
    total = b + c;
    if (total >= a) {
        return 0;
    }
    if (total == a - 1 && fn_80174160() == side && fn_80178308() == side) {
        return 2;
    }
    return 1;
}

int fn_80025354(int side)
{
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;

    fn_8022B7A4(side, 0x74727374, &a);
    fn_8022B7A4(side, 0x74507374, &b);
    fn_8022B7A4(side, 0x64647374, &c);
    fn_8022B7A4(side, 0x64317374, &d);
    if (fn_800B65A0(side) != 0xFF) {
        if (a == 0 && b == 0 && c == 0 && d == 0) {
            return 2;
        }
    } else if (a != 0 || b != 0 || c != 0 || d != 0) {
        return 1;
    }
    return 0;
}

int fn_8002544C(int side, unsigned int value)
{
    unsigned int a;
    unsigned int b;

    fn_8022B7A4(side, 0x61707374, &a);
    fn_8022B7A4(side, 0x63707374, &b);
    return a - b > value;
}

unsigned char fn_800254B4(Object_800785C0 *pRecord)
{
    unsigned char count = 0;
    int i;

    for (i = 0; i < 4; i++) {
        if (pRecord->mUnknown1C4[i].mType != 0) {
            count++;
        }
    }
    return count;
}

int fn_800254E8(Object_800785C0 *pRecord, int a, int b)
{
    return fn_800797F4(pRecord, a, b);
}

int fn_80025508(void)
{
    int counts[4];

    if (fn_80025708()) {
        Object_800785C0 *pRecord = fn_800785C0();
        int result = 7;
        int active = fn_8007984C(pRecord);
        int side = fn_800B65A0(0) == 0xFF;
        int i;

        fn_801C1F94(counts, 0, sizeof(counts));
        for (i = 0; i < 4; i++) {
            counts[fn_800257B4(side, pRecord, i)]++;
        }
        if (active) {
            result = fn_80079758(side, &pRecord->mUnknown20C);
        }
        if (counts[1] > 0) {
            return 1;
        }
        if (counts[0] + counts[3] == 4) {
            int ret = 0;

            if (active && result != 0) {
                ret = counts[3] == 0 ? 2 : 0;
            }
            return ret;
        }
        if (counts[3] <= 0) {
            return 2;
        }
        return 1;
    }
    switch (fn_80178AE0()) {
    case 0:
        return 1;
    case 1:
        return 0;
    }
    return 2;
}

int fn_80025640(int *pResult)
{
    int result = fn_80025508();
    int done = 1;

    if (result == 2) {
        done = 0;
    }
    if (pResult) {
        *pResult = result;
    }
    return done;
}

int fn_8002568C(void)
{
    int result = 7;

    if (fn_80025708()) {
        Object_800785C0 *pRecord = fn_800785C0();

        if (fn_8007984C(pRecord)) {
            result = fn_80079758(fn_800B65A0(0) == 0xFF, &pRecord->mUnknown20C);
        }
    }
    return result;
}

void fn_800256F8(int mode)
{
    lbl_803EBAF0 = mode;
}

int fn_80025700(void)
{
    return lbl_803EBAF0;
}

int fn_80025708(void)
{
    return lbl_803EBAF0 == 0;
}

int fn_80025718(void)
{
    return lbl_803EBAF0 == 1;
}

void fn_8002572C(void)
{
    int result;

    if (fn_80025640(&result)) {
        if (result == 0) {
            fn_80067DB8(0x5E, 0, fn_800B65A0(0) == 0xFF, 0, 0);
        } else if (result == 1) {
            fn_80067DB8(0x5D, 0, fn_80178348(), 0, 0);
        }
    }
}

int fn_800257B4(int side, Object_800785C0 *pRecord, int index)
{
    int result = 2;
    int type = pRecord->mUnknown1C4[index].mType;
    int value = pRecord->mUnknown1C4[index].mValue;
    int opposite = side == 0;

    if (fn_800796B8(side, pRecord, index, &result) == 0) {
        switch (type) {
        case 1:
            if (fn_800254E8(pRecord, 2, 0)) {
                result = fn_80024B20(side, value, 1);
            } else {
                result = fn_80024B20(side, value, 0);
            }
            break;
        case 2:
            result = fn_80024C24(side);
            break;
        case 3:
            result = fn_80024C70(side, value);
            break;
        case 7:
            result = fn_80024CA8(side, value);
            break;
        case 6:
            result = fn_80024D18(side, opposite, value);
            break;
        case 20:
            result = fn_80024D94(side);
            break;
        case 31:
            result = fn_80024DCC(side, value);
            break;
        case 41:
            result = fn_80024E08(side, value);
            break;
        case 42:
            result = fn_80024EC0(side, value);
            break;
        case 45:
            result = fn_80024E08(opposite, value);
            break;
        case 46:
            result = fn_80024EFC(opposite, value);
            break;
        case 47:
        case 48:
            break;
        case 50:
            result = fn_80024CA8(opposite, value);
            break;
        case 52:
            result = fn_80024FA8(opposite, value, 0);
            break;
        case 53:
            result = fn_80025030(side, opposite, value);
            break;
        case 56:
            if (fn_800254E8(pRecord, 68, 0)) {
                result = fn_80024FA8(side, value, 1);
            } else {
                result = fn_80024FA8(side, value, 0);
            }
            break;
        case 55:
            result = fn_8002509C(side, value);
            break;
        case 58:
            result = fn_80025148(side, value);
            break;
        case 60:
            result = fn_80025238(side, value);
            break;
        case 68:
            result = fn_800252A8(side, value);
            break;
        case 71:
            result = fn_80025354(opposite);
            break;
        case 72:
            result = fn_80025354(side);
            break;
        case 74:
            result = fn_8002544C(side, value);
            break;
        }
    }
    return result;
}

int fn_80025ACC(void)
{
    int result = 0;

    if (fn_80025708() && fn_800785C0()->mUnknown1C3 != 0) {
        result = 1;
    }
    return result;
}

int fn_80025B18(int *pResults, char (*pText)[64])
{
    unsigned char i;
    Object_800785C0 *pRecord;
    int count;

    for (i = 0; i <= 3; i++) {
        pText[i][0] = 0;
        pResults[i] = -1;
    }
    pRecord = fn_800785C0();
    count = 0;
    for (i = 0; i <= 3; i++) {
        Entry_800257B4 *pEntry = &pRecord->mUnknown1C4[i];

        if (pEntry->mType != 0 && pEntry->mUnknown8 != 0) {
            fn_80078C50(pEntry->mType, pEntry->mValue, pText[count], 64);
            switch (pEntry->mType) {
            case 6:
            case 7:
            case 21:
            case 38:
            case 39:
            case 40:
            case 46:
            case 50:
            case 52:
            case 53:
            case 56:
            case 57:
            case 58:
            case 59:
            case 73:
            case 74:
                pResults[count] = -1;
                break;
            default:
                switch (fn_800257B4(1, pRecord, i)) {
                case 0:
                case 3:
                    pResults[count] = 1;
                    break;
                default:
                    pResults[count] = 0;
                    break;
                }
                break;
            }
            count++;
        }
    }
    return count;
}

void fn_80025C88(int flag)
{
    if (fn_80025708()) {
        int results[4];
        Arg_8021D7B8 args[7];
        unsigned char i;
        int count;

        for (i = 0; i <= 3; i++) {
            lbl_8037DF88[i][0] = 0;
            results[i] = -1;
        }
        count = 0;
        if (flag) {
            count = fn_80025B18(results, lbl_8037DF88);
        }
        args[0].i = flag;
        args[1].i = count;
        for (i = 0; i <= 3; i++) {
            lbl_8037DF58[i].mUnknown0 = 0;
            lbl_8037DF58[i].mpText = lbl_8037DF88[i];
            lbl_8037DF58[i].mLength = 63;
            args[i + 2].p = &lbl_8037DF58[i];
            lbl_8037E088.mResults[i] = results[i];
        }
        lbl_8037E088.mUnknown0 = 1;
        lbl_8037E088.mUnknown4 = 4;
        args[6].p = &lbl_8037E088;
        if (count > 0 || !flag) {
            fn_8021D7B8(lbl_803EB688, 0x80000083, 7, args);
        }
    }
}

}
