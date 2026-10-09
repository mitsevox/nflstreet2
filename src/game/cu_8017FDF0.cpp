#include "game/fn_801EF390.h"
#include "game/fn_8022F478.h"
#include "game/Class_80148A58.h"
#include "game/FELoop.h"
#include "game/InGame.h"
#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/cu_80181330.h"
#include "game/cu_8007C9D4.h"
#include "game/fn_801801F0.h"
#include "game/fn_8007F828.h"
#include "game/fn_8017F584.h"
#include "game/fn_801C3284.h"
#include "game/cu_8017F90C.h"
#include "game/fn_800B65A0.h"

/* Filled by fn_80152940 for one index; the constructor leaves mUnknown8 unset. */
struct Info_80152940 {
    Info_80152940() : mUnknown0(0), mUnknown4(0), mUnknown12(0), mUnknown16(0), mUnknown20(0xFF) {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
};

/* One argument or result slot of the message handler fn_801801F8. */
union Arg_801801F8 {
    int i;
    float f;
    int *pi;
    float *pf;
    Params_80005284 *pParams;
};

extern "C" {
int fn_8022F4BC(void);
int fn_80186B38(int a);
int fn_8018F2F4(int a, int b);
int fn_8001194C(int a);
int fn_801869F0(void);
int fn_80186D64(int a);
void fn_80186F9C(int a, char *pText, int c);
int fn_801486A0(void);
void fn_80152940(Class_80148A58 *pObject, int index, Info_80152940 *pInfo);
int fn_80178AE0(void);
void fn_801E1BE8(void);
void fn_8007AEE8(Object_8007A334 *pObject);
void fn_8007AF14(Object_8007A334 *pObject);
int fn_8007AF34(Object_8007A334 *pObject);
int fn_8007AF5C(Object_8007A334 *pObject);
int fn_801C6458(int a, int b);
int fn_801E195C(int a);
int fn_800B81A4(void);
float fn_80237260(int stream);
int fn_80188030(int a);
int fn_80188044(int a);
void fn_80022680(int index, int a, int b);
int fn_80187F44(char *pText0, int length0, char *pText1, int length1, char *pText2, int length2, char *pText3, int length3);
int fn_801D6850(void);
void fn_801880B4(char *pText, int length);
void fn_801410F4(int a);
void fn_80186A44(signed char a);
int fn_8022F358(int index);
void fn_80186F30(signed char a, int b);
void fn_80186F8C(int a);
unsigned char fn_80062A60(void);
int fn_80063BE4(char *pDest, int count);
void fn_80063C2C(const char *pSource, int count);
int fn_80063C7C(int a, char *pText, int length);
int fn_801C2FE4(char *pText0, char *pText1);
int fn_801C31B0(char *pText0, char *pText1);
int fn_80025708(void);
int fn_80025718(void);
int fn_8017F60C(void);
void fn_80083E1C(Object_8007A334 *pObject, int a);
int fn_8008400C(Object_8007A334 *pObject);
int fn_80084360(Object_8007A334 *pObject);
int fn_80080D10(Object_8008044C *pObject);
void fn_80010150(int a);
int fn_8000FCDC(void);
void fn_80011600(int a, int b, int c);
void fn_8018A8C0(unsigned char value);
int fn_80065650(void);
int fn_8022F384(int a);
void *fn_8021EA44(int index);
int fn_8021E984(void *p, int a);
void fn_8000FCD4(int a);
int fn_8000FCCC(void);
unsigned char fn_80187C64(void);
void fn_80187C5C(unsigned char a);
void fn_80156E74(float *pX, float *pY, float *pZ);
int fn_8005902C(void);
int fn_8007B324(void);
int fn_80188DF0(int a);
int fn_8022E558(void);
int fn_8022E560(void);
}

static int lbl_803EB530 = 0;
static int lbl_803EB534 = -1;
static int lbl_803EB538 = -1;
static int lbl_803EB53C = -1;
static int lbl_803EB540 = 0;
static unsigned char lbl_803EB544 = 0;
static unsigned char lbl_803EB545 = 0;

extern "C" {
int fn_8017FDF0(void)
{
    return 2;
}

int fn_8017FDF8(void)
{
    return 0;
}

int fn_8017FE00(void)
{
    return 0;
}

float fn_8017FE08(float min, float max)
{
    return min + (max - min) * fn_80237260(1);
}

void fn_8017FE4C(int a, int b, int c)
{
    lbl_803EB530 = a;
    lbl_803EB534 = b;
    lbl_803EB538 = c;
    if (a == 0 && b == 0x69 && fn_8017F584() == 8) {
        fn_8018F2F4(fn_80186B38(fn_8022F4BC()), 0x3FF);
    }
}

int fn_8017FEA0(void)
{
    int value = fn_8007F828(6);

    return value == 1 || value == 2;
}

int fn_8017FED4(int a, int *pResult)
{
    int value = -1;

    if (a != -1) {
        value = fn_8001194C(a == 0);
    }
    *pResult = fn_801869F0();
    bool found = false;
    if (*pResult == 2) {
        *pResult = fn_80186D64(value);
        found = true;
    }
    return found;
}

void fn_8017FF40(int a)
{
    lbl_803EB53C = a;
}

int fn_8017FF48(int a, char *pText)
{
    int state;

    if (a == -1) {
        a = 1;
    }
    state = fn_801869F0();
    fn_80186F9C(state, pText, a);
    return state;
}

int fn_8017FF98(void)
{
    int result = 0;

    if (fn_80027DF0() == 0) {
        Info_80152940 info;

        switch (fn_801486A0()) {
        case 0:
            result = 1;
            break;
        case 1:
            for (unsigned int i = 0; i <= 3; i++) {
                fn_80152940(fn_80148A58(), i, &info);
                if (info.mUnknown20 == 0xFF) {
                    result = 1;
                    break;
                }
            }
            break;
        default: {
            unsigned char first = fn_800B65A0(0) != 0xFF;
            unsigned char second = fn_800B65A0(1) != 0xFF;

            result = first ^ second;
            break;
        }
        }
    }
    return result;
}

int fn_80180070(void)
{
    if (fn_801486A0() != 15) {
        return fn_80148A58()->vfn_13();
    }
    return fn_800B65A0(fn_80178AE0()) != 0xFF;
}

int fn_801800D0(void)
{
    int result = -1;

    if (fn_80027DF0() != 0) {
        Object_8007A334 cursor;
        int searching = 1;

        fn_801E1BE8();
        fn_8007AEE8(&cursor);
        for (int found = fn_8007A444(&cursor); found && searching; found = fn_8007A510(&cursor)) {
            result = fn_8007AF34(&cursor);
            fn_8007AF5C(&cursor);
            searching = fn_801E195C(fn_801C6458(result, 0)) == 2;
        }
        fn_8007AF14(&cursor);
        if (searching) {
            result = -1;
        }
    } else {
        int value = fn_800B81A4();

        if (value != 0xFF) {
            result = value;
        }
    }
    return result;
}

int fn_801801B4(void)
{
    return lbl_803EB530;
}

int fn_801801BC(void)
{
    return lbl_803EB538;
}

void fn_801801C4(int a)
{
}

void fn_801801C8(int a)
{
    lbl_803EB530 = a;
}

int fn_801801D0(void)
{
    int value = lbl_803EB53C;

    lbl_803EB53C = -1;
    return value;
}

unsigned char fn_801801E0(void)
{
    return lbl_803EB540;
}

void fn_801801E8(int a)
{
    lbl_803EB540 = a;
}

void fn_801801F0(unsigned char a)
{
    lbl_803EB545 = a;
}

void fn_80180AF8(int *pValues);
void fn_80180BE4(int id, int *pStatus, int *pTeam);
int fn_80180EF8(int id);

int fn_801801F8(unsigned int id, Arg_801801F8 *pArgs, int unused, Arg_801801F8 *pResult)
{
    switch (id) {
    case 1:
        pResult->i = fn_8017FDF0();
        break;
    case 0x136:
        pResult->i = fn_8017FDF8();
        break;
    case 7:
        pResult->i = fn_8017FE00();
        break;
    case 8:
        fn_80180BE4(pArgs[0].i, pArgs[1].pi, pArgs[2].pi);
        break;
    case 9:
        pResult->f = fn_8017FE08(pArgs[0].f, pArgs[1].f);
        break;
    case 0xA:
        *pArgs[0].pi = fn_80188030(*pArgs[0].pi);
        break;
    case 0x139:
        pResult->i = fn_80188044(pArgs[0].i);
        break;
    case 0xB:
        fn_8017FE4C(pArgs[0].i, pArgs[1].i, pArgs[2].i);
        break;
    case 0xC:
        pResult->i = fn_8017FEA0();
        break;
    case 0xF: {
        int index = pArgs[0].pi[0] + 1;

        fn_80180AF8(&pArgs[0].pi[index]);
        break;
    }

    case 0xD:
        pResult->i = fn_80180EF8(pArgs[0].i);
        break;
    case 0xE:
        fn_80022680(pArgs[1].i, pArgs[0].i, 0);
        break;
    case 0x5E:
        fn_801801F0(pArgs[0].i);
        break;
    case 0x5F:
        pResult->i = lbl_803EB545;
        break;
    case 0x114:
        pResult->i = fn_80187F44(pArgs[0].pParams->mpText, pArgs[0].pParams->mLength,
                                 pArgs[1].pParams->mpText, pArgs[1].pParams->mLength,
                                 pArgs[2].pParams->mpText, pArgs[2].pParams->mLength,
                                 pArgs[3].pParams->mpText, pArgs[3].pParams->mLength);
        break;
    case 0xDB:
        pResult->i = fn_801D6850();
        break;
    case 6:
        fn_801880B4(pArgs[0].pParams->mpText, pArgs[0].pParams->mLength);
        break;
    case 0x10:
        fn_801410F4(2);
        break;
    case 0x13:
        pResult->i = fn_801869F0();
        break;
    case 0x1F0:
        fn_80186A44(pArgs[0].i);
        break;
    case 0x1EF:
        if (pArgs[0].i == -1) {
            fn_8022F478(fn_8022F358((signed char)pArgs[1].i));
        } else {
            fn_80186F30(pArgs[1].i, pArgs[0].i != 0);
        }
        break;
    case 0x14:
        fn_80186D64(fn_8001194C(pArgs[0].i == 0));
        break;
    case 0x23:
        pResult->i = fn_8017FED4(pArgs[0].i, pArgs[1].pi);
        break;
    case 0x24:
        pResult->i = fn_8017FF48(pArgs[0].i, pArgs[1].pParams->mpText);
        break;
    case 0x25:
        fn_80186F8C(pArgs[0].i != 0);
        break;
    case 0x21: {
        int value = fn_8007F828(12);

        if (value == 1 && fn_80027DF0() != 0) {
            pResult->i = value;
        } else {
            pResult->i = 0;
        }
        break;
    }
    case 0x26:
        if (lbl_803EB544 != 0 || fn_8002892C() != 0 || (lbl_803EB540 != 0 && fn_80062A60() != 0)) {
            pResult->i = 1;
        } else {
            pResult->i = 0;
        }
        break;
    case 0x3A:
    case 0x3C:
        pResult->i = fn_80063BE4(pArgs[0].pParams->mpText, pArgs[0].pParams->mLength);
        break;
    case 0x3B:
        fn_80063C2C(pArgs[0].pParams->mpText, pArgs[0].pParams->mLength);
        break;
    case 0x3D:
        pResult->i = fn_80063C7C(pArgs[0].i, pArgs[1].pParams->mpText, pArgs[1].pParams->mLength);
        break;
    case 0x109:
        pResult->i = fn_801C2FE4(pArgs[0].pParams->mpText, pArgs[1].pParams->mpText);
        break;
    case 0x12A:
        pResult->i = fn_801C31B0(pArgs[0].pParams->mpText, pArgs[1].pParams->mpText);
        break;
    case 0x104:
        pResult->i = fn_80025708();
        break;
    case 0x105:
        pResult->i = fn_80025718();
        break;
    case 0xE0:
        pResult->i = fn_8017F60C();
        break;
    case 0xED: {
        Object_8007A334 cursor;
        char name[32];

        fn_80083E1C(&cursor, 0);
        if (fn_80084034(&cursor, pArgs[0].i, 0)) {
            fn_80083F88(&cursor, name, sizeof(name));
            fn_801C3284(pArgs[1].pParams->mpText, name, pArgs[1].pParams->mLength);
        } else {
            fn_801C3284(pArgs[1].pParams->mpText, "", pArgs[1].pParams->mLength);
        }
        fn_80083F68(&cursor);
        break;
    }
    case 0x103:
        fn_80010150(pArgs[0].i);
        break;
    case 0xFF: {
        int value = fn_8000FCDC();

        fn_80011600(pArgs[0].i, pArgs[1].i, value);
        break;
    }

    case 0x113:
        fn_8018A8C0(pArgs[0].i == 1);
        break;
    case 0x107:
        if (fn_80065650() == -1) {
            pResult->i = -1;
        } else {
            pResult->i = fn_80065650();
        }
        break;
    case 0x122:
        pResult->i = fn_801801E0();
        break;
    case 0x11F:
        fn_801801E8(pArgs[0].i == 1);
        break;
    case 0x108:
        pResult->i = fn_8022F384(fn_8022F4BC());
        break;
    case 0x111:
        pResult->i = fn_801800D0();
        break;
    case 0x13A:
        pResult->i = fn_801E195C(fn_801C6458(pArgs[0].i, 0)) == 2;
        break;
    case 0x19C:
        pResult->i = 0xFF;
        break;
    case 0xF5:
        fn_80028920();
        fn_80027AD8(0, -1, -1, -2, -2, -2);
        break;
    case 0x134:
        pResult->i = fn_8007F828(20) != 0;
        break;
    case 0x144: {
        void *pObject = fn_8021EA44(1);
        int high = pArgs[1].i >> 16;
        int low = pArgs[1].i & 0xFFFF;

        pResult->i = fn_801F0DB8((void *)fn_8021E984(pObject, high), low);

        break;
    }

    case 0x189:
        fn_8000FCD4(pArgs[0].i);
        break;
    case 0x172:
        pResult->i = fn_8017F584();
        break;
    case 0x17C:
        pResult->i = fn_8000FCCC();
        break;
    case 0x91: {
        int result = 0;

        if (fn_80187C64()) {
            result = fn_801869F0() == 0;
        }
        pResult->i = result;
        fn_80187C5C(0);
        break;
    }
    case 0x181: {
        float position[3];

        fn_80156E74(&position[0], &position[1], &position[2]);
        *pArgs[0].pf = position[0];
        *pArgs[1].pf = position[1];
        *pArgs[2].pf = position[2];
        break;
    }

    case 0x186:
        fn_8017FF40(pArgs[0].i);
        break;
    case 0x38:
        pResult->i = 1;
        break;
    case 0x190:
        pResult->i = fn_8017FF98();
        break;
    case 0x191:
        pResult->i = fn_80180070();
        break;
    case 0xCB:
        pResult->i = 0;
        break;
    case 0x195:
        pResult->i = 0;
        break;
    case 0x196:
        pResult->i = 0;
        break;
    case 0x19D:
        pResult->i = fn_8005902C();
        break;
    case 5:
    case 0xBB:
    case 0xBC:
    case 0x102:
    case 0x106:
    case 0x11E:
        break;
    default:
        return 0;
    }
    return 1;
}

void fn_80180AF8(int *pValues)
{
    Object_8007A334 cursor;

    if (fn_8007B324()) {
        for (int i = 3; i >= 0; i--) {
            pValues[i] = -1;
        }
        fn_8007AEE8(&cursor);
        if (fn_8007A444(&cursor)) {
            do {
                int key = fn_8007AF34(&cursor);
                int value = fn_8007AF5C(&cursor);
                int index = fn_80188030(key);

                if (index != -1) {
                    pValues[index] = value == 0 ? 0 : value == 1 ? 1 : -1;

                }
            } while (fn_8007A510(&cursor));
        }
        fn_8007AF14(&cursor);
    }
}

void fn_80180BE4(int id, int *pStatus, int *pTeam)
{
    Object_8007A334 cursor;
    int team = 2;
    int mode;
    int result;

    *pStatus = 0;
    *pTeam = fn_80188DF0(-1);
    mode = fn_8017F584();
    result = fn_80027DF0();
    if (mode == 7) {
        if (result) {
            fn_8007A334(&cursor, 0x4D414554, 0x44494754, 0, 0, 0x54415453);
        } else {
            fn_80083E1C(&cursor, 0);
        }
        if (fn_80084034(&cursor, id, 0)) {
            *pStatus = fn_80084158(&cursor);
            if (*pStatus == 0) {
                if (id == fn_8007CB6C(1)) {
                    *pStatus = 0x85;
                } else {
                    *pStatus = 0x86;
                }
            } else if (!fn_80084438(&cursor)) {
                if (result) {
                    team = fn_80084360(&cursor);
                    if (team != 0 && team != 1) {
                        team = 2;
                    }
                } else if (fn_8022E558() == id) {
                    team = 0;
                } else if (fn_8022E560() == id) {
                    team = 1;
                }
                switch (team) {
                case 0:
                    *pTeam = fn_80188DF0(0);
                    break;
                case 1:
                    *pTeam = fn_80188DF0(1);
                    break;
                }
            }
        }
        fn_80083F68(&cursor);
    } else if (mode == 2 || mode == 4 || mode == 13) {
        if (id == fn_8007CB6C(1)) {
            *pStatus = 0x85;
        } else {
            *pStatus = 0x86;
        }
    } else if (mode == 11) {
        if (id == fn_8007CB6C(1)) {
            fn_80083E1C(&cursor, 0);
            if (fn_80084034(&cursor, id, 0)) {
                *pStatus = fn_80084158(&cursor);
            } else {
                *pStatus = 0x85;
            }
            fn_80083F68(&cursor);
        } else {
            *pStatus = 0x86;
        }
    } else if (id == 10001) {
        *pStatus = 0x8E;
    } else {
        if (result) {
            fn_80083E40(&cursor, 0, 0x54415453);
        } else {
            fn_80083E1C(&cursor, 0);
        }
        if (fn_80084034(&cursor, id, 0)) {
            if (!result) {
                if (fn_8008400C(&cursor) != 5) {
                    team = 2;
                } else if (fn_8022E558() == id) {
                    team = 0;
                } else {
                    team = 1;
                }
            } else {
                team = fn_80084360(&cursor);
                if (team != 0 && team != 1) {
                    team = 2;
                }
            }

            if (!fn_80084438(&cursor)) {
                switch (team) {
                case 0:
                    *pTeam = fn_80188DF0(0);
                    break;
                case 1:
                    *pTeam = fn_80188DF0(1);
                    break;
                }
            }
            *pStatus = fn_80084158(&cursor);
        }
        fn_80083F68(&cursor);
    }
}

int fn_80180EF8(int id)
{
    Object_8008044C cursor;
    int result = 0;

    if (fn_80027DF0()) {
        fn_8008044C(&cursor, 0, 0x54415453);
    } else {
        fn_8008040C(&cursor, 0);
    }
    if (fn_800809C4(&cursor, id, 0)) {
        result = fn_80080D10(&cursor);
    }
    fn_8008056C(&cursor);
    return result;
}
}
