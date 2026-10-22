#include "game/fn_801C68FC.h"

/* Playing stream (pool lbl_8039ADB8.mpPlaying, 0x10 bytes). */
struct Play_801E0A1C {
    int mHandle;
    void *mpData;
    int mUnknown8;
    int mUnknownC;
};

/* Loaded bank (pool lbl_8039ADB8.mpBanks, 0xC bytes). */
struct Bank_801E0A3C {
    int mId;
    void *mpUnknown4;
    unsigned char mUnknown8;
};

struct State_801E0A5C {
    void *mpPlaying;
    int mHandle;
    void *mpBanks;
};

struct Desc_801E0AEC {
    int mHeap;
    int mBankCount;
};

struct Config_801E0AEC {
    Config_801E0AEC() : mUnknown0(0), mUnknown4(0), mUnknown8(0) {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

struct Desc_801E0DF0 {
    int mId;
    int mUnknown04;
    int mUnknown08;
    float mUnknown0C;
    int mUnknown10;
    char mUnknown14[0xC];
    int mUnknown20;
    unsigned char mUnknown24;
};

struct Info_801E1084;

extern "C" {
void *fn_801D2BB0(int heap, unsigned int size, int a, int b);
int fn_801D2BD0(void *p);
void *fn_801C6A20(void *pool);
void *fn_801C6B4C(void *pool, void *item);
void fn_801C6C0C(void *pool, void *item);
void *fn_801C6C84(void *pool, void *item);
int fn_801C6DCC(void *pool, int a, int key, void *pResult, int (*match)(void *, int, void *));
void *memset(void *p, int c, unsigned int size);
}

/* Abstract allocator interface handed to the sound library. */
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
int fn_801B3AD0(int id, char *pName, int a);
int fn_801B3B7C(int id, int a, float b);
int fn_801B3D28(int id, char *pName, int a);
int fn_801B3DD8(int id);
void fn_801B45D0(int id, signed char value);
void fn_801B4728(int a, int b, int c, int d);
int fn_801B59B0(int id, int a);
void fn_801B5AB0(int a, unsigned char b);
int fn_801B5BCC(int id, Info_801E1084 *pInfo);
void fn_801B5CD0(int a);
int fn_801B5FC0(int id, int a);
unsigned int fn_801EF390(void *pData, int a, int b);
int fn_801F010C(void *pData, int a);
void *fn_801F44A4(void);
void fn_801F50C8(void *pEntries, int index);
void fn_8027D3AC(void);
void fn_8027ECD8(int a, int b);
void fn_8027ED6C(void);

static int fn_801E0A1C(Play_801E0A1C *pPlay, int handle, Play_801E0A1C **ppFound)
{
    if (pPlay->mHandle == handle) {
        *ppFound = pPlay;
        return 0;
    }
    return -1;
}

static int fn_801E0A3C(Bank_801E0A3C *pBank, int id, Bank_801E0A3C **ppFound)
{
    if (pBank->mId == id) {
        *ppFound = pBank;
        return 0;
    }
    return -1;
}

static int fn_801E0A5C(void)
{
    int handle = lbl_8039ADB8.mHandle;
    Play_801E0A1C *pFound;

    do {
        lbl_8039ADB8.mHandle++;
        pFound = 0;
        fn_801C6DCC(lbl_8039ADB8.mpPlaying, 0, lbl_8039ADB8.mHandle, &pFound,
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
    memset(&lbl_8039ADB8, 0, sizeof(lbl_8039ADB8));
    lbl_8039ADB8.mpPlaying = fn_801C68FC(pDesc->mHeap, 0, 4, sizeof(Play_801E0A1C), 0, 0);
    lbl_8039ADB8.mpBanks = fn_801C68FC(pDesc->mHeap, 0, pDesc->mBankCount, sizeof(Bank_801E0A3C), 0, 0);
    if (lbl_8039ADB8.mpPlaying && lbl_8039ADB8.mpBanks) {
        lbl_803EBD64 = 1;
    }
    return -1;
}

void fn_801E0BE4(void)
{
    Play_801E0A1C *pPlay;

    fn_801B2F28(-1);
    if (lbl_8039ADB8.mpBanks) {
        fn_801C69E4(lbl_8039ADB8.mpBanks);
    }
    if (lbl_8039ADB8.mpPlaying) {
        pPlay = (Play_801E0A1C *)fn_801C6B4C(lbl_8039ADB8.mpPlaying, 0);
        while (pPlay) {
            fn_801F010C(pPlay->mpData, pPlay->mUnknown8);
            pPlay = (Play_801E0A1C *)fn_801C6C84(lbl_8039ADB8.mpPlaying, pPlay);
        }
        fn_801C69E4(lbl_8039ADB8.mpPlaying);
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
    Play_801E0A1C *pPlay;
    int stream;
    int handle = -1;

    if (lbl_803EBD64) {
        pPlay = (Play_801E0A1C *)fn_801C6A20(lbl_8039ADB8.mpPlaying);
        if (pPlay) {
            stream = fn_801EF390(pData, a, b);
            if (stream) {
                if (fn_801B2CDC(stream) >= 0) {
                    pPlay->mHandle = fn_801E0A5C();
                    pPlay->mUnknownC = b;
                    pPlay->mpData = pData;
                    pPlay->mUnknown8 = a;
                    handle = pPlay->mHandle;
                    fn_801C6AA4(lbl_8039ADB8.mpPlaying, pPlay, 0);
                } else {
                    fn_801F010C(pData, a);
                    fn_801C6C0C(lbl_8039ADB8.mpPlaying, pPlay);
                }
            }
        }
    }
    return handle;
}

int fn_801E0D68(int handle)
{
    Play_801E0A1C *pPlay;
    int result = -1;

    if (lbl_803EBD64) {
        pPlay = 0;
        fn_801C6DCC(lbl_8039ADB8.mpPlaying, 0, handle, &pPlay,
                    (int (*)(void *, int, void *))fn_801E0A1C);
        if (pPlay) {
            result = 0;
            fn_801F010C(pPlay->mpData, pPlay->mUnknown8);
            fn_801C6C0C(lbl_8039ADB8.mpPlaying, pPlay);
        }
    }
    return result;
}

int fn_801E0DF0(Desc_801E0DF0 *pDesc)
{
    Bank_801E0A3C *pBank;
    int result = 0;

    pBank = (Bank_801E0A3C *)fn_801C6A20(lbl_8039ADB8.mpBanks);
    if (pBank) {
        memset(pBank, 0, sizeof(Bank_801E0A3C));
        pBank->mUnknown8 = pDesc->mUnknown24;
        fn_801F50C8(fn_801F44A4(), pDesc->mUnknown10);
        if (pDesc->mUnknown24) {
            result = fn_801B3D28(pDesc->mId, pDesc->mUnknown14, pDesc->mUnknown20);
            if (result >= 0) {
                pBank->mpUnknown4 = (void *)fn_801B3DD8(pDesc->mId);
                if (!pBank->mpUnknown4) {
                    result = -1;
                }
            }
        } else {
            result = fn_801B3AD0(pDesc->mId, pDesc->mUnknown14, pDesc->mUnknown04);
            if (result >= 0) {
                pBank->mpUnknown4 = (void *)fn_801B3B7C(pDesc->mId, pDesc->mUnknown08, pDesc->mUnknown0C);
                if (!pBank->mpUnknown4) {
                    result = -1;
                }
            }
        }
        if (result >= 0) {
            pBank->mId = pDesc->mId;
            fn_801C6AA4(lbl_8039ADB8.mpBanks, pBank, 0);
        } else {
            fn_801C6C0C(lbl_8039ADB8.mpBanks, pBank);
        }
    }
    return result;
}

int fn_801E0EF8(int id)
{
    Bank_801E0A3C *pBank = 0;
    int result = -1;

    fn_801C6DCC(lbl_8039ADB8.mpBanks, 0, id, &pBank, (int (*)(void *, int, void *))fn_801E0A3C);
    if (pBank) {
        fn_801C6C0C(lbl_8039ADB8.mpBanks, pBank);
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
