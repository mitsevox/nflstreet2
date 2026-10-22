#include "game/fn_801C68FC.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EF390.h"

/* Item of the first pool of lbl_8039ADB8 (0x10 bytes), keyed by a generated handle;
   holds the fn_801EF390 arguments. */
struct Item_801E0A1C {
    int mHandle;
    void *mpData;
    int mUnknown8;
    int mUnknownC;
};

/* Item of the second pool of lbl_8039ADB8 (0xC bytes), keyed by a caller id. */
struct Item_801E0A3C {
    int mId;
    void *mpUnknown4;
    unsigned char mUnknown8;
};

struct State_801E0A5C {
    void *mpPool0;
    int mHandle;
    void *mpPool8;
};

struct Desc_801E0AEC {
    int mHeap;
    int mCount;
};

struct Config_801E0AEC {
    Config_801E0AEC() : mUnknown0(0), mUnknown4(0), mUnknown8(0) {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

/* Three words at +0x14 of Desc_801E0DF0, passed by address (laid out as
   fn_8006DC98 fills them: a pointer and two words). */
struct Data_801E0DF0 {
    void *mpData;
    int mUnknown4;
    int mUnknown8;
};

struct Desc_801E0DF0 {
    int mId;
    int mUnknown04;
    int mUnknown08;
    float mUnknown0C;
    int mUnknown10;
    Data_801E0DF0 mUnknown14;
    int mUnknown20;
    unsigned char mUnknown24;
};

struct Info_801E1084;

extern "C" {
void *fn_801C6A20(void *pool);
void *fn_801C6B4C(void *pool, void *item);
void fn_801C6C0C(void *pool, void *item);
void *fn_801C6C84(void *pool, void *item);
int fn_801C6DCC(void *pool, int a, int key, void *pResult, int (*match)(void *, int, void *));
}

/* Abstract allocator interface handed to fn_801B2C18. */
class Class_801E119C {
public:
    virtual void *vfn_01(unsigned int size) = 0;
    virtual void vfn_02(void *p) = 0;
    virtual int vfn_03() = 0;
    virtual int vfn_04() = 0;
    virtual ~Class_801E119C() {}
};

/* Allocator on an engine heap, with an optional lock callback. */
class Class_801E10BC : public Class_801E119C {
public:
    Class_801E10BC(int heap) : mHeap(heap), mpLock(0) {}
    virtual void *vfn_01(unsigned int size)
    {
        void *p;

        if (mpLock) {
            mpLock(1);
        }
        p = fn_801D2BB0(mHeap, size, 0, 0);
        if (mpLock) {
            mpLock(0);
        }
        return p;
    }
    virtual void vfn_02(void *p) { fn_801D2BD0(p); }
    virtual int vfn_03() { return 0; }
    virtual int vfn_04() { return 0; }

    void *operator new(unsigned int size) { return fn_801D2BB0(1, size, 0, 0); }
    void operator delete(void *p) { fn_801D2BD0(p); }

    int mHeap;
    void (*mpLock)(int lock);
};

extern "C" {
extern State_801E0A5C lbl_8039ADB8;
extern Class_801E10BC *lbl_803EBD60;
extern unsigned char lbl_803EBD64;

void fn_801B2C18(Class_801E10BC *pAllocator, Config_801E0AEC *pConfig);
void fn_801B2B58(void);
int fn_801B2CDC(int a);
int fn_801B2F28(int id);
int fn_801B3234(int a);
int fn_801B3AD0(int id, Data_801E0DF0 *pData, int a);
int fn_801B3B7C(int id, int a, float b);
int fn_801B3D28(int id, Data_801E0DF0 *pData, int a);
int fn_801B3DD8(int id);
void fn_801B45D0(int id, signed char value);
void fn_801B4728(int a, int b, int c, int d);
int fn_801B59B0(int id, int a);
void fn_801B5AB0(int a, unsigned char b);
int fn_801B5BCC(int id, Info_801E1084 *pInfo);
void fn_801B5CD0(int a);
int fn_801B5FC0(int id, int a);
void *fn_801F44A4(void);
void fn_801F50C8(void *pEntries, int index);
void fn_8027D3AC(void);
void fn_8027ECD8(int a, int b);
void fn_8027ED6C(void);

static int fn_801E0A1C(Item_801E0A1C *pItem, int handle, Item_801E0A1C **ppFound)
{
    if (pItem->mHandle == handle) {
        *ppFound = pItem;
        return 0;
    }
    return -1;
}

static int fn_801E0A3C(Item_801E0A3C *pItem, int id, Item_801E0A3C **ppFound)
{
    if (pItem->mId == id) {
        *ppFound = pItem;
        return 0;
    }
    return -1;
}

static int fn_801E0A5C(void)
{
    int handle = lbl_8039ADB8.mHandle;
    Item_801E0A1C *pFound;

    do {
        lbl_8039ADB8.mHandle++;
        pFound = 0;
        fn_801C6DCC(lbl_8039ADB8.mpPool0, 0, lbl_8039ADB8.mHandle, &pFound,
                    (int (*)(void *, int, void *))fn_801E0A1C);
    } while (pFound || lbl_8039ADB8.mHandle == -1);
    return handle;
}

int fn_801E0AE4(void)
{
    return lbl_803EBD64;
}

int fn_801E0AEC(Desc_801E0AEC *pDesc)
{
    lbl_803EBD60 = new Class_801E10BC(pDesc->mHeap);
    Config_801E0AEC config;
    fn_801B2C18(lbl_803EBD60, &config);
    fn_8027ED6C();
    fn_8027D3AC();
    fn_801C1F94(&lbl_8039ADB8, 0, sizeof(lbl_8039ADB8));
    lbl_8039ADB8.mpPool0 = fn_801C68FC(pDesc->mHeap, 0, 4, sizeof(Item_801E0A1C), 0, 0);
    lbl_8039ADB8.mpPool8 = fn_801C68FC(pDesc->mHeap, 0, pDesc->mCount, sizeof(Item_801E0A3C), 0, 0);
    if (lbl_8039ADB8.mpPool0 && lbl_8039ADB8.mpPool8) {
        lbl_803EBD64 = 1;
    }
    return -1;
}

void fn_801E0BE4(void)
{
    Item_801E0A1C *pItem;

    fn_801B2F28(-1);
    if (lbl_8039ADB8.mpPool8) {
        fn_801C69E4(lbl_8039ADB8.mpPool8);
    }
    if (lbl_8039ADB8.mpPool0) {
        pItem = (Item_801E0A1C *)fn_801C6B4C(lbl_8039ADB8.mpPool0, 0);
        while (pItem) {
            fn_801F010C(pItem->mpData, pItem->mUnknown8);
            pItem = (Item_801E0A1C *)fn_801C6C84(lbl_8039ADB8.mpPool0, pItem);
        }
        fn_801C69E4(lbl_8039ADB8.mpPool0);
    }
    fn_801B2B58();
    if (lbl_803EBD60) {
        delete lbl_803EBD60;
    }
    lbl_803EBD60 = 0;
    lbl_803EBD64 = 0;
}

int fn_801E0CA8(void *pData, int a, int b)
{
    Item_801E0A1C *pItem;
    int id;
    int handle = -1;

    if (lbl_803EBD64) {
        pItem = (Item_801E0A1C *)fn_801C6A20(lbl_8039ADB8.mpPool0);
        if (pItem) {
            id = fn_801EF390(pData, a, b);
            if (id) {
                if (fn_801B2CDC(id) >= 0) {
                    pItem->mHandle = fn_801E0A5C();
                    pItem->mUnknownC = b;
                    pItem->mpData = pData;
                    pItem->mUnknown8 = a;
                    handle = pItem->mHandle;
                    fn_801C6AA4(lbl_8039ADB8.mpPool0, pItem, 0);
                } else {
                    fn_801F010C(pData, a);
                    fn_801C6C0C(lbl_8039ADB8.mpPool0, pItem);
                }
            }
        }
    }
    return handle;
}

int fn_801E0D68(int handle)
{
    Item_801E0A1C *pItem;
    int result = -1;

    if (lbl_803EBD64) {
        pItem = 0;
        fn_801C6DCC(lbl_8039ADB8.mpPool0, 0, handle, &pItem,
                    (int (*)(void *, int, void *))fn_801E0A1C);
        if (pItem) {
            result = 0;
            fn_801F010C(pItem->mpData, pItem->mUnknown8);
            fn_801C6C0C(lbl_8039ADB8.mpPool0, pItem);
        }
    }
    return result;
}

int fn_801E0DF0(Desc_801E0DF0 *pDesc)
{
    Item_801E0A3C *pItem;
    int result = 0;

    pItem = (Item_801E0A3C *)fn_801C6A20(lbl_8039ADB8.mpPool8);
    if (pItem) {
        fn_801C1F94(pItem, 0, sizeof(Item_801E0A3C));
        pItem->mUnknown8 = pDesc->mUnknown24;
        fn_801F50C8(fn_801F44A4(), pDesc->mUnknown10);
        if (pDesc->mUnknown24) {
            result = fn_801B3D28(pDesc->mId, &pDesc->mUnknown14, pDesc->mUnknown20);
            if (result >= 0) {
                pItem->mpUnknown4 = (void *)fn_801B3DD8(pDesc->mId);
                if (!pItem->mpUnknown4) {
                    result = -1;
                }
            }
        } else {
            result = fn_801B3AD0(pDesc->mId, &pDesc->mUnknown14, pDesc->mUnknown04);
            if (result >= 0) {
                pItem->mpUnknown4 = (void *)fn_801B3B7C(pDesc->mId, pDesc->mUnknown08, pDesc->mUnknown0C);
                if (!pItem->mpUnknown4) {
                    result = -1;
                }
            }
        }
        if (result >= 0) {
            pItem->mId = pDesc->mId;
            fn_801C6AA4(lbl_8039ADB8.mpPool8, pItem, 0);
        } else {
            fn_801C6C0C(lbl_8039ADB8.mpPool8, pItem);
        }
    }
    return result;
}

int fn_801E0EF8(int id)
{
    Item_801E0A3C *pItem = 0;
    int result = -1;

    fn_801C6DCC(lbl_8039ADB8.mpPool8, 0, id, &pItem, (int (*)(void *, int, void *))fn_801E0A3C);
    if (pItem) {
        fn_801C6C0C(lbl_8039ADB8.mpPool8, pItem);
        if (fn_801B2F28(id)) {
            result = 0;
        }
    }
    return result;
}

int fn_801E0F7C(int id, int a)
{
    return fn_801B59B0(id, a);
}

int fn_801E0F9C(int id, int a)
{
    return fn_801B5FC0(id, a);
}

void fn_801E0FBC(int id, int value)
{
    fn_801B45D0(id, value);
}

void fn_801E0FE0(int a, int b, int c)
{
    fn_801B4728(a, b, c, 1);
}

void fn_801E1004(int a, int b)
{
    fn_801B5AB0(a, b);
}

void fn_801E1028(int a)
{
    fn_801B5CD0(a);
}

void fn_801E1048(int a, int b)
{
    int p = fn_801B3234(a);

    if (p) {
        fn_8027ECD8(p, b);
    }
}

int fn_801E1084(int id, Info_801E1084 *pInfo)
{
    int result = -1;

    if (lbl_803EBD64) {
        result = fn_801B5BCC(id, pInfo);
    }
    return result;
}
}
