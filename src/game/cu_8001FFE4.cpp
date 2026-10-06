#include "game/Object_8007A334.h"
#include "game/fn_8021D7B8.h"

struct Buffer_80020170 {
    char mUnknown0[4];
    int mUnknown4;
    char *mUnknown8;
};

struct BufferRef_80020170 {
    Buffer_80020170 *mUnknown0;
};

struct Params_80020170 {
    int mUnknown0;
    BufferRef_80020170 mUnknown4;
    BufferRef_80020170 mUnknown8;
    int *mUnknown12;
    int *mUnknown16;
};

extern "C" {
extern void *lbl_803EB688;

void fn_80010200(int value);
void fn_80011600(int a, int b, int c);
void fn_80014294(int a, int b);
void fn_80015D28(int a);
void fn_80027E18(unsigned char value);
int fn_800231B0(Object_8007A334 *pObject, int a, int *pResult);
int fn_800231E8(Object_8007A334 *pObject);
int fn_80023210(Object_8007A334 *pObject);
int fn_80023238(Object_8007A334 *pObject);
void fn_80023260(Object_8007A334 *pObject, char *pData, int size);
void fn_80023294(Object_8007A334 *pObject, char *pData, int size);
void fn_8007EBDC(Object_8007A334 *pObject, int db);
void fn_8007EC34(Object_8007A334 *pObject);
int fn_8007EC54(Object_8007A334 *pObject, int a);
void fn_8007ECBC(int db, int a);
unsigned char fn_80087F70(void);
unsigned char fn_80087FD0(void);
int fn_80088068(int id);
int fn_800881B8(void);
int fn_80088224(int id);
void fn_80088338(int id, char *pDest, int count);
unsigned char fn_80088628(void);
void fn_80088638(int db);
int fn_80088640(void);
void fn_801566EC(void);
void fn_801566F8(void);
void fn_80156724(int value);
void fn_8015672C(int value);
void fn_80156734(int value);
unsigned int fn_801568F0(void);
int fn_801801B4(void);
void fn_801801C4(int a);
void fn_80186F30(signed char a, int b);
signed char fn_8022F384(int a);
int fn_8022F478(int a);
int fn_8022F4BC(void);
int fn_8000FCCC(void);
int fn_8000FCDC(void);

void fn_80020328(void);
void fn_80020410(void);
}

static Object_8007A334 lbl_8036B334;
static unsigned char lbl_803EBA98 = 0;
static unsigned char lbl_803EBA99 = 0;

extern "C" {
void fn_8001FFE4(void)
{
    fn_801566EC();
    fn_80087F70();
    if (!lbl_803EBA99) {
        if (fn_8022F4BC() != -1) {
            fn_80088638(fn_8022F4BC());
            lbl_803EBA99 = 1;
        }
    } else {
        fn_8022F478(fn_80088640());
    }
}

void fn_8002003C(void)
{
    fn_801566F8();
    fn_80087FD0();
}

int fn_80020060(int index)
{
    fn_800231B0(&lbl_8036B334, index + lbl_803EBA98, 0);
    return fn_80023210(&lbl_8036B334);
}

void fn_800200A4(int index, BufferRef_80020170 first, BufferRef_80020170 second, int *pResult0, int *pResult1)
{
    fn_800231B0(&lbl_8036B334, index + lbl_803EBA98, 0);
    fn_80023260(&lbl_8036B334, first.mUnknown0->mUnknown8, first.mUnknown0->mUnknown4 + 1);
    fn_80023294(&lbl_8036B334, second.mUnknown0->mUnknown8, second.mUnknown0->mUnknown4 + 1);
    *pResult0 = fn_800231E8(&lbl_8036B334);
    *pResult1 = fn_80023238(&lbl_8036B334);
}

void fn_80020130(int value)
{
    if (value != -1) {
        fn_801801C4(value);
    }
    fn_8021D7B8(lbl_803EB688, 0x80000036, 0, 0);
}

int fn_80020170(unsigned int id, Params_80020170 *pParams, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_8001FFE4();
        break;
    case 0x80000002:
        fn_8002003C();
        fn_80020328();
        break;
    case 0x80000003:
        *pResult = fn_80020060(pParams->mUnknown0);
        break;
    case 0x80000004:
        fn_800200A4(pParams->mUnknown0, pParams->mUnknown4, pParams->mUnknown8, pParams->mUnknown12,
                    pParams->mUnknown16);
        break;
    case 0x80000005:
        fn_80020130(pParams->mUnknown0);
        break;
    case 0x80000007:
        fn_8015672C(pParams->mUnknown0);
        break;
    case 0x80000006:
        fn_80088338(pParams->mUnknown0, pParams->mUnknown4.mUnknown0->mUnknown8, pParams->mUnknown4.mUnknown0->mUnknown4);
        *pParams->mUnknown16 = fn_80088224(pParams->mUnknown0);
        break;
    case 0x80000008:
        *pResult = fn_800881B8();
        fn_80020410();
        break;
    case 0x80000009:
        *pResult = fn_80088628();
        break;
    case 0x8000000A:
        fn_80010200(600);
        break;
    default:
        return 0;
    }
    return 1;
}

void fn_80020328(void)
{
    int state = fn_801801B4();

    if (state == 1) {
        int value = fn_8000FCDC();
        if (!lbl_803EBA99) {
            fn_80088638(fn_8022F4BC());
            lbl_803EBA99 = state;
        }
        fn_80011600(-1, fn_8000FCCC(), value);
        fn_80186F30(fn_8022F384(fn_80088640()), 1);
        fn_80014294(0x36, 0x21);
        fn_80027E18(1);
        unsigned int id = fn_801568F0();
        if (fn_80088224(id)) {
            fn_80156734(0);
            fn_80156724(0);
        } else {
            fn_80156734(fn_80088068(id));
            fn_80156724(fn_80088068(id));
        }
        fn_80015D28(4);
    } else {
        fn_80088638(-1);
        lbl_803EBA99 = 0;
    }
}

void fn_80020410(void)
{
    Object_8007A334 object;

    int db = fn_8022F384(fn_8022F4BC());
    fn_8007EBDC(&object, db);
    int found = fn_8007EC54(&object, 0x21);
    fn_8007EC34(&object);
    if (fn_800881B8() && found) {
        fn_8007ECBC(db, 0x21);
    }
}
}
