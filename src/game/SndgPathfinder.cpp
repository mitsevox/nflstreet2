#include <string.h>

#include "game/SndgPathfinder.h"
#include "game/Camera_8013F738.h"
#include "game/cu_80136B1C.h"
#include "game/fn_8016871C.h"
#include "game/fn_8017F584.h"
#include "game/fn_801C68FC.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801EF390.h"
#include "game/fn_802270D4.h"

void *operator new(unsigned int size, int unknown);

struct Vec2 {
    float x;
    float y;
};

struct AllocParams {
    AllocParams() : mUnknown0(0), mUnknown4(0), mUnknown8(0) {}

    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

class Allocator {
public:
    virtual void *Alloc(int size, const AllocParams &params);
    virtual void Free(void *p, int unknown);
};

struct Struct_803EB878 {
    const char *mName;
    unsigned int mHash;
};

class Class_801B8D9C {
public:
    char mUnknown0[8];
};

extern "C" {
int fn_801B90CC(Allocator **out);
int fn_801B9148(void);
int fn_801B9174(void);
int fn_801B95AC(Class_801B8D9C *list, void *params, int *handle);
int fn_801B8DA8(Class_801B8D9C *list, Struct_803EB878 *desc);
void fn_801B983C(int handle, void *params);
void fn_801B96E4(int handle);

extern Class_801B8D9C lbl_803ECC54;
extern Class_801B8D9C lbl_803ECC64;
extern Class_801B8D9C lbl_803ECC6C;
extern Class_801B8D9C lbl_803ECC74;
extern Class_801B8D9C lbl_803ECC7C;
extern Class_801B8D9C lbl_803ECC84;
extern Class_801B8D9C lbl_803ECC8C;
extern Class_801B8D9C lbl_803ECC94;
extern Class_801B8D9C lbl_803ECC9C;
extern Struct_803EB878 lbl_803EB878;
extern Struct_803EB878 lbl_803EB888;
extern Struct_803EB878 lbl_803EB890;
extern Struct_803EB878 lbl_803EB898;
extern Struct_803EB878 lbl_803EB8A0;
extern Struct_803EB878 lbl_803EB8A8;
extern Struct_803EB878 lbl_803EB8B0;
extern Struct_803EB878 lbl_803EB8B8;
extern Struct_803EB878 lbl_803EB8C0;
}

static inline int AddSound(Class_801B8D9C *list, Struct_803EB878 *desc, void *params, int *handle)
{
    int err = fn_801B95AC(list, params, handle);
    if (err < 0) {
        fn_801B8DA8(list, desc);
        err = fn_801B95AC(list, params, handle);
    }
    return err;
}

struct SoundObject {
    static void *operator new(unsigned int size)
    {
        Allocator *alloc;
        fn_801B90CC(&alloc);
        fn_801B9148();
        void *p = alloc->Alloc(size, AllocParams());
        fn_801B9174();
        return p;
    }

    static void operator delete(void *p)
    {
        Allocator *alloc;
        fn_801B90CC(&alloc);
        fn_801B9148();
        alloc->Free(p, 0);
        fn_801B9174();
    }

    int mHandle;
};

// The fields after mHandle form the parameter block that is registered with
// the per-type list and pushed to the playing handle by Commit().
struct Sound0 : SoundObject {
    void SetVolume(int volume)
    {
        if (volume < 0) {
            volume = 0;
        } else if (volume > 99) {
            volume = 99;
        }
        mVolume = volume;
    }

    void SetPan(int pan)
    {
        if (pan < 0) {
            pan = 0;
        } else if (pan > 0xfffe) {
            pan = 0xfffe;
        }
        mPan = pan;
    }

    Sound0(int volume, unsigned short pan)
    {
        mUnknown4 = 0;
        SetVolume(volume);
        mUnknownC = 0;
        mUnknown10 = 0;
        SetPan(pan);
        AddSound(&lbl_803ECC54, &lbl_803EB878, &mUnknown4, &mHandle);
    }

    ~Sound0()
    {
        if (mHandle != 0) {
            fn_801B96E4(mHandle);
        }
    }

    void Commit()
    {
        if (mHandle != 0) {
            fn_801B983C(mHandle, &mUnknown4);
        }
    }

    int mUnknown4;
    int mVolume;
    int mUnknownC;
    int mUnknown10;
    int mPan;
};

struct SoundVP : SoundObject {
    void SetVolume(int volume)
    {
        if (volume < 0) {
            volume = 0;
        } else if (volume > 99) {
            volume = 99;
        }
        mVolume = volume;
    }

    void SetPan(int pan)
    {
        if (pan < 0) {
            pan = 0;
        } else if (pan > 0xfffe) {
            pan = 0xfffe;
        }
        mPan = pan;
    }

    SoundVP(Class_801B8D9C *list, Struct_803EB878 *desc, int volume, unsigned short pan)
    {
        SetVolume(volume);
        SetPan(pan);
        AddSound(list, desc, &mVolume, &mHandle);
    }

    ~SoundVP()
    {
        if (mHandle != 0) {
            fn_801B96E4(mHandle);
        }
    }

    void Commit()
    {
        if (mHandle != 0) {
            fn_801B983C(mHandle, &mVolume);
        }
    }

    int mVolume;
    int mPan;
};

struct SoundVFP : SoundObject {
    void SetVolume(int volume)
    {
        if (volume < 0) {
            volume = 0;
        } else if (volume > 99) {
            volume = 99;
        }
        mVolume = volume;
    }

    void SetUnknown8(int value)
    {
        if (value < 0) {
            value = 0;
        } else if (value > 150) {
            value = 150;
        }
        mUnknown8 = value;
    }

    void SetPan(int pan)
    {
        if (pan < 0) {
            pan = 0;
        } else if (pan > 0xfffe) {
            pan = 0xfffe;
        }
        mPan = pan;
    }

    SoundVFP(Class_801B8D9C *list, Struct_803EB878 *desc, int volume, int f, unsigned short pan)
    {
        SetVolume(volume);
        SetUnknown8(f);
        SetPan(pan);
        AddSound(list, desc, &mVolume, &mHandle);
    }

    ~SoundVFP()
    {
        if (mHandle != 0) {
            fn_801B96E4(mHandle);
        }
    }

    void Commit()
    {
        if (mHandle != 0) {
            fn_801B983C(mHandle, &mVolume);
        }
    }

    int mVolume;
    int mUnknown8;
    int mPan;
};

struct Sound3 : SoundObject {
    void SetVolume(int volume)
    {
        if (volume < 0) {
            volume = 0;
        } else if (volume > 99) {
            volume = 99;
        }
        mVolume = volume;
    }

    void SetPan(int pan)
    {
        if (pan < 0) {
            pan = 0;
        } else if (pan > 0xfffe) {
            pan = 0xfffe;
        }
        mPan = pan;
    }

    void SetMode(int mode)
    {
        if (mode < 0) {
            mode = 0;
        } else if (mode > 3) {
            mode = 3;
        }
        mMode = mode;
    }

    Sound3(int volume, unsigned short pan, int mode)
    {
        SetVolume(volume);
        SetPan(pan);
        SetMode(mode);
        AddSound(&lbl_803ECC64, &lbl_803EB888, &mVolume, &mHandle);
    }

    ~Sound3()
    {
        if (mHandle != 0) {
            fn_801B96E4(mHandle);
        }
    }

    void Commit()
    {
        if (mHandle != 0) {
            fn_801B983C(mHandle, &mVolume);
        }
    }

    int mVolume;
    int mPan;
    int mMode;
};

/* Ambient sound bank state (0x8C bytes), allocated by fn_8006B664. */
struct Struct_803EA67C {
    void *mpUnknown0;
    void *mpUnknown4;
    int mUnknown8;
    int mUnknownC;
    void *mpUnknown10;
    int mHandles[9];
    Sound0 **mSound0;
    SoundVFP **mSound1;
    SoundVP **mSound2;
    Sound3 **mSound3;
    SoundVFP **mSound4;
    SoundVFP **mSound5;
    SoundVFP **mSound6;
    SoundVFP **mSound7;
    SoundVP **mSound8;
    float mScales[9];
    unsigned char mCounts[9];
};

struct Struct_80290788 {
    unsigned int mCount;
    float mScale;
};

/* Per sound slot: create, update and stop functions. */
struct Struct_802D5104 {
    void (*mCreate)(int index, Vector_80039F5C *pPos, void *pObject);
    void (*mUpdate)(int index, Vector_80039F5C *pPos, void *pObject);
    void (*mStop)(int index);
};

struct Struct_8006BBC4 {
    int mUnknown0;
    int mUnknown4;
    char mUnknown8[1];
};

typedef void (*Callback_8006C548)(int handle);
typedef void (*Handler_8030A668)(int unknown);

/* 0x1C-byte table entry; the table ends with an entry whose m10 is 3. */
struct Entry_8030A664 {
    int m0;
    const char *m4;
    void *m8;
    int mC;
    int m10;
    int m14;
    int m18;
};

struct Entry_8030A660 {
    int m0;
    int m4;
    int m8;
    unsigned char mC;
    unsigned char mD;
    unsigned char mE[2];
    unsigned int m10;
    int m14;
};

struct Struct_802D611C {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
};

struct Struct_8006C2C8 {
    unsigned int m0;
    unsigned int m4;
    Entry_8030A660 *m8;
    Struct_802D611C *mC;
    Entry_8030A664 *m10;
    Handler_8030A668 *m14;
};

struct Struct_8030A654 {
    int m0;
    unsigned int m4;
    unsigned int m8;
    Entry_8030A660 *mC;
    Entry_8030A664 *m10;
    Handler_8030A668 *m14;
    int m18;
    void *m1C;
    unsigned char m20;
    int *m24;
    int *m28;
};

/* Pool node queued by fn_8006BF4C. */
struct Node_8006BF4C {
    unsigned int m0;
    void *m4;
    int m8;
    Callback_8006C548 mC;
};

/* Filled in by fn_801F40F4. */
struct Struct_801F40F4 {
    signed char mVolume;
    unsigned char mUnknown1[7];
    unsigned short mPan;
    short mSpan;
    short mUnknownC;
    short mUnknownE;
    short mUnknown10;
    short mUnknown12;
    short mUnknown14;
    short mUnknown16;
};

/* Game event passed to fn_8006CE84 and its handlers. */
struct Struct_8006CCD0 {
    int mUnknown0;
    Vector_80039F5C mPosition;
    union {
        unsigned int mValue;
        void *mpObject;
    } mUnknown10;
    int mUnknown14;
    int mUnknown18;
    int mUnknown1C;
    unsigned short mType;
};

/* Record whose address Block_80170E64 keeps in its word at +0x294. */
struct Record_80170E64_294 {
    int m0;
    int m4;
    int m8;
};

struct Struct_802D62B8 {
    float mDistance;
    float mFactor;
    float mScaleNoPos;
    float mScalePositional;
};

struct Struct_8030A688;
typedef void (*Callback_8030A688)(Struct_8030A688 *);

struct Struct_8030A688 {
    Struct_802D62B8 *mParams;
    Callback_8030A688 mUpdate;
    Vector_80039F5C mOrigin;
    int mAngle;
};

struct Struct_8030A680 {
    int mHandle;
    int m04;
    Struct_8030A688 mSource;
    Vector_80039F5C mPosition;
    unsigned char m2C;
    unsigned char mScale;
    unsigned char m2E[2];
};

struct Struct_802D62D8 {
    unsigned char mScale;
    Struct_802D62B8 *mParams;
    Callback_8030A688 mUpdate;
};

struct Struct_801F4834 {
    int mStatus;
    int m04;
    int m08;
};

struct Struct_803EA698Entry {
    void (*mFunc)(int, int);
};

struct Item_8006DA6C {
    int mKey;
};

/* A sound request queued for replication through the "Sounds" stream (0x14 bytes). */
struct Struct_8030A518Entry {
    unsigned int mId;
    Vector_80039F5C mPos;
    unsigned short mFlags;
    unsigned char mUnknown12;
};

struct Struct_8030A518 {
    Struct_8030A518Entry mEntries[12];
    unsigned char mCount;
};

struct Struct_8030A830 {
    char mUnknown0[0xA];
    short mUnknownA;
    unsigned char mUnknownC;
    unsigned char mUnknownD;
    char mUnknownE[0x18 - 0xE];
    int mFlags;
    float mUnknown1C;
    float mUnknown20;
    Vector_80039F5C mUnknown24;
    int mUnknown30;
    unsigned char mUnknown34;
};

struct Struct_803EA368 {
    char mUnknown0[0xD70];
    int mUnknownD70;
    int mUnknownD74;
    char mUnknownD78[0xD88 - 0xD78];
    int mUnknownD88;
    char mUnknownD8C[0xD94 - 0xD8C];
    int mUnknownD94;
};

struct Struct_801E0AEC {
    int mUnknown0;
    int mUnknown4;
};

struct Struct_801E0DF0 {
    int mId;
    int mUnknown4;
    int mUnknown8;
    float mValue;
    int mUnknown10;
    void *mpData;
    int mUnknown18;
    int mUnknown1C;
    int mUnknown20;
    unsigned char mUnknown24;
};

struct SndgPathfinderState {
    void *mpPool[3];
};

extern "C" {
extern char lbl_802EBFCC[];
extern char lbl_802EBFE4[];
extern char lbl_802EBFF4[];
extern char lbl_802EC000[];
extern char lbl_802EC00C[];
extern Struct_803EA368 *lbl_803EA368;

int abs(int value);
int fn_8002D060(void *p);
int fn_8002D0AC(void *p);
void fn_800300D4(void *pStream, float *pValues, int bits, float scale);
void fn_80030490(void *pStream, float *pValues, int bits, float scale);
void fn_80030ACC(void (*write)(void *), void (*read)(void *, void *, void *, void *, float), int size,
                 const char *pName);
int fn_80031054(Vector_80039F5C *pPos);
void fn_8006F344(unsigned char value);
void fn_8006F850(Struct_8006CCD0 *pEvent);
void fn_80070C40(Struct_8006CCD0 *pEvent);
void fn_800717E0(Vector_80039F5C *pPos);
int fn_80071BA0(int a, int b);
void fn_800728F8(void);
void fn_80072C54(int value);
void fn_80073144(int a, int b);
void fn_80073620(int a, int b, int c);
void fn_8007371C(void);
void fn_80073764(void);
void fn_80074358(int a);
int fn_800744A8(void);
int fn_800744B8(void);
void fn_80074684(int a, int b);
void fn_800746E0(void);
void fn_80074734(void);
void fn_80074788(void);
void fn_800747DC(int a);
void fn_80074864(int a);
void fn_800748EC(int a);
void fn_80074974(int a);
void fn_80074A14(int a);
void fn_80074AB4(int a);
void fn_80074B54(int a);
void fn_80074C08(int a);
void fn_80074CBC(void);
void fn_80074D70(void);
void fn_80074DF8(int a);
void fn_80074E08(void);
void fn_80074E90(int a);
void fn_80074EA0(void);
void fn_80074F28(int a);
void fn_80074F38(Vector_80039F5C *pPos);
void fn_80075058(int a);
void fn_80075068(void);
void fn_800750F0(int a);
void fn_80075100(void);
void fn_80075188(int a);
void fn_80076228(void);
void fn_80076D9C(int a);
void fn_80076DAC(int a);
void fn_80076DB4(int a, int b, int c, int d);
void fn_80076EA4(int a);
void fn_80076EE8(int a);
void fn_80077258(void);
void fn_8007732C(int a);
void fn_80077488(void);
void fn_8007753C(void);
int fn_8007F828(int a);
int fn_8009D86C(void);
int fn_8009D990(int a);
int fn_800A3444(void);
int fn_800A8444(int a);
int fn_800AD9B4(void);
int fn_800BA6F8(void);
int fn_8013F9F8(void);
Camera_8013F738 *fn_8013FA04(int index);
int fn_8013FD0C(int index);
unsigned int fn_801568F0(void);
Vec2 fn_80177FE0(void);
int fn_80178308(void);
int fn_80178348(void);
int fn_801784C4(void);
unsigned long long fn_80190F18(void *pStream, int bits);
void fn_80191068(void *pStream, unsigned long long value, int bits);
void fn_801B2F18(void (*a)(int, int), void (*b)(int, int), void (*c)(int, int));
void fn_801B3084(int flags, const char *pName, int value);
void *fn_801C6A20(void *pool);
void *fn_801C6B4C(void *pool, void *item);
void fn_801C6C0C(void *pool, void *item);
void *fn_801C6C84(void *pool, void *item);
void fn_801C6DCC(void *pool, int a, int key, void *pResult, int (*match)(Item_8006DA6C *, int, Item_8006DA6C **));
void fn_801CE7D0(int a);
int fn_801CFE40(float y, float x);
unsigned int fn_801D27F4(int a);
void fn_801D34D0(void *p, int size, int value, int align);
int fn_801E0AE4(void);
void fn_801E0AEC(Struct_801E0AEC *pDesc);
void fn_801E0BE4(void);
int fn_801E0CA8(void *pData, int unknown, int c);
int fn_801E0D68(int handle);
int fn_801E0DF0(Struct_801E0DF0 *pDesc);
int fn_801E0EF8(int id);
int fn_801E0F7C(int id, int unknown);
int fn_801E0F9C(int id, int unknown);
void fn_801E0FBC(int id, unsigned int value);
void fn_801E0FE0(int a, int b, int c);
void fn_801E1004(int a, int b);
void fn_801E1028(int a);
void fn_801E1048(int a, int b);
int fn_801F0C50(void *a, int b);
void fn_801F11AC(void *pData, int a);
void fn_801F3C14(void);
int fn_801F3E28(void);
int fn_801F3E34(void);
int fn_801F3E40(void *pData, int b, int c);
void fn_801F3ED8(void *pData, int *pSlot, int b, int c, Callback_8006C548 cb);
void fn_801F3F74(int handle);
int fn_801F4024(int handle);
int fn_801F4050(int a, int b, Struct_801F40F4 *pParams);
void fn_801F40F4(Struct_801F40F4 *pParams);
void fn_801F4130(int handle);
int fn_801F41A0(int handle);
void fn_801F421C(int handle, int value);
void fn_801F4294(int handle, int a, int value);
void fn_801F4314(int handle, int value);
int fn_801F438C(void *pData, int b);
int fn_801F44B0(int a, int b, int c, int d);
void fn_801F45D4(int handle);
void fn_801F4638(int handle);
void fn_801F4678(int handle, int a, int volume);
void fn_801F4770(int handle, int pan, int c);
void fn_801F4834(int handle, Struct_801F4834 *pStatus);
int fn_801F48B8(int handle);
void fn_801F49B8(int handle, int a, int b);
void fn_801F4A38(int handle, int a);
void fn_801F4AEC(int a, int b);
void fn_801F4B20(void);
void fn_801F4B88(void *pData, int a, int b);
void fn_801F4C5C(void);
int fn_801F4DAC(void *pData, int b, int c);
void fn_801F4F28(int handle);
unsigned int fn_801F7ABC(void);
int fn_80227040(Vector_80039F5C *a, Vector_80039F5C *b);
int fn_802275D8(Vector_80039F5C *a, Vector_80039F5C *b, float eps);
void fn_80227690(Vec2 *pOut, Vector_80039F5C *a, Vector_80039F5C *b);
float fn_8022785C(Vector_80039F5C *pPos, Vector_80039F5C *pOther);
unsigned int fn_802372EC(int a, int b);
void fn_8006E3F0(Struct_8030A518Entry *pEntry, void *pStream0, void *pStream1, void *pStream2, void *pStream3,
                 float unknown);
void fn_80068154(void);
void fn_80068418(void);
void fn_80068A04(void);
void fn_80068C1C(void);
void fn_80068E00(void);
void fn_80068ED0(Vector_80039F5C *pPos, unsigned short *pPan, short *pSpan);
float fn_80068F70(Vector_80039F5C *pPos);
int fn_80068FE8(Sound0 *pEntry, void *pObject, int index, int init);
void fn_800691E8(int index, Vector_80039F5C *pPos, void *pObject);
void fn_80069398(int index, Vector_80039F5C *pPos, void *pObject);
void fn_800695F0(int index);
void fn_800696A4(int index, Vector_80039F5C *pPos, void *pObject);
void fn_80069858(int index, Vector_80039F5C *pPos, void *pObject);
void fn_800699C8(int index, Vector_80039F5C *pPos, void *pObject);
void fn_80069B4C(int index, Vector_80039F5C *pPos, void *pObject);
void fn_80069D00(int index, Vector_80039F5C *pPos, void *pObject);
void fn_80069EB4(int index, Vector_80039F5C *pPos, void *pObject);
void fn_8006A068(int index, Vector_80039F5C *pPos, void *pObject);
void fn_8006A21C(int index, Vector_80039F5C *pPos, void *pObject);
void fn_8006A38C(int index, Vector_80039F5C *pPos, void *pObject);
void fn_8006A4D8(int index, Vector_80039F5C *pPos, void *pObject);
void fn_8006A5C8(int index, Vector_80039F5C *pPos, void *pObject);
void fn_8006A6B8(int index, Vector_80039F5C *pPos, void *pObject);
void fn_8006A804(int index, Vector_80039F5C *pPos, void *pObject);
void fn_8006A950(int index, Vector_80039F5C *pPos, void *pObject);
void fn_8006AA9C(int index, Vector_80039F5C *pPos, void *pObject);
void fn_8006ABE8(int index, Vector_80039F5C *pPos, void *pObject);
void fn_8006ACD8(void);
void fn_8006B1CC(int index);
void fn_8006B25C(int index);
void fn_8006B2EC(int index);
void fn_8006B37C(int index);
void fn_8006B40C(int index);
void fn_8006B49C(int index);
void fn_8006B52C(int index);
void fn_8006B5BC(int index);
int fn_8006B64C(void);
void fn_8006B664(void);
void fn_8006B790(void);
int fn_8006B810(int type, unsigned int index);
void fn_8006B91C(int type, unsigned int index, Vector_80039F5C *pPos, void *pObject);
void fn_8006B9AC(int type, unsigned int index, Vector_80039F5C *pPos, void *pObject);
unsigned int fn_8006BA54(int type, int value);
int fn_8006BB44(int type);
int fn_8006BBC4(Struct_8006BBC4 *p);
void fn_8006BC30(int type, unsigned int index);
void fn_8006BCC8(int type);
void fn_8006BD24(void);
void fn_8006BD4C(void);
void fn_8006BDD8(unsigned int volume);
float fn_8006BE3C(int type);
Entry_8030A664 *fn_8006BE68(int type, int id);
int fn_8006BEBC(void *a, void *b);
void fn_8006BEC4(void);
void fn_8006BF08(void);
int fn_8006BF4C(unsigned int index, void *a, int b, Callback_8006C548 cb);
void fn_8006C040(void *item);
void fn_8006C074(Node_8006BF4C *pNode);
void fn_8006C120(int a);
void fn_8006C1E8(void);
void fn_8006C22C(Entry_8030A664 *pEntry);
void fn_8006C284(Entry_8030A664 *pEntry);
void fn_8006C2C8(Struct_8006C2C8 *pInit);
void fn_8006C3C4(Entry_8030A664 *pEntry);
void fn_8006C454(void);
void fn_8006C4D4(unsigned int index);
int fn_8006C548(unsigned int index, int a, Callback_8006C548 cb);
int fn_8006C674(int index, int a);
void fn_8006C6EC(unsigned int index);
int fn_8006C74C(unsigned int index);
int fn_8006C78C(unsigned int index);
int fn_8006C7F4(unsigned int index);
int fn_8006C854(int index, Vector_80039F5C *pPos);
int fn_8006C8A4(int index, Vector_80039F5C *pPos, unsigned char c);
void fn_8006C9D4(int index);
void fn_8006CA18(int index, int a, unsigned char volume);
void fn_8006CA84(int a);
void fn_8006CAEC(void);
void fn_8006CAF0(int index);
void fn_8006CB40(Vector_80039F5C *a, Vector_80039F5C *b, int angle, unsigned short *pOut0, short *pOut1);
unsigned char fn_8006CC48(void);
int fn_8006CC54(int index);
unsigned char fn_8006CC90(int index);
void fn_8006CCA8(float value);
void fn_8006CCD0(Struct_8006CCD0 *p);
void fn_8006CE84(Struct_8006CCD0 *p);
void fn_8006CEC8(Struct_8030A688 *src);
void fn_8006CF9C(Vector_80039F5C *origin, Vector_80039F5C *pos, unsigned short *pan, short *span);
void fn_8006D0F8(void);
void fn_8006D188(int withThird);
void fn_8006D268(void);
void fn_8006D2B4(void);
void fn_8006D2EC(void);
void fn_8006D314(void);
void fn_8006D338(void);
void fn_8006D358(int unknown);
unsigned char fn_8006D408(Struct_8030A688 *src, Vector_80039F5C *pos, unsigned char volume);
void fn_8006D540(int idx, Vector_80039F5C *pos, Struct_801F40F4 *out);
unsigned char fn_8006D5FC(int idx, unsigned char volume);
int fn_8006D65C(int idx);
void fn_8006D670(int idx, int handle);
void fn_8006D684(int idx, unsigned char percent);
void fn_8006D6F4(int idx, int a, int volume);
void fn_8006D758(int idx, Vector_80039F5C *pos);
void fn_8006D7CC(int idx);
int fn_8006D884(int idx);
void fn_8006D8DC(int idx);
void fn_8006D91C(int a, int b);
void fn_8006D98C(int a, int b);
void fn_8006D9FC(int a, int b);
int fn_8006DA6C(Item_8006DA6C *pItem, int key, Item_8006DA6C **ppResult);
void fn_8006DDB4(int a, int b, int c);
void fn_8006DEA8(int a, int b);
void fn_8006DEEC(int a);
void fn_8006DF2C(int a);
void fn_8006DF6C(int a);
void fn_8006DFA8(int value);
void fn_8006E010(int value);
void fn_8006E08C(void);
void fn_8006E0DC(int unknown);
void fn_8006E134(int flags);
void fn_8006E148(Struct_8006CCD0 *pEvent);
int fn_8006E25C(void);
void fn_8006E2A8(void);
void fn_8006E308(Struct_8030A518Entry *pEntry);
void fn_8006E370(Struct_8030A518Entry *pEntry, void *pStream);
void fn_8006E548(void *pStream);
void fn_8006E5B4(void *pStream0, void *pStream1, void *pStream2, void *pStream3, float unknown);
void fn_8006E6CC(Struct_8030A518 *pList);
void fn_8006E710(void);
void fn_8006E760(void);
void fn_8006E78C(void);
int fn_8006E7CC(void);
void fn_8006E7D4(Struct_8030A518Entry *pEntry);
void fn_8006E89C(int id, Vector_80039F5C *pPos, unsigned char unknown);
void fn_8006E918(void);
void fn_8006E924(int unknown);
void fn_8006EA04(unsigned int index, unsigned int value);
void fn_8006EC24(void);
void fn_8006ECB4(Struct_8006CCD0 *pEvent);
void fn_8006F0B8(int flags);
void fn_8006F0C8(int flags);
int fn_8006F0D8(void);

void fn_80071748(int unknown);
void fn_80073F5C(int unknown);
void fn_8007418C(int unknown);
void fn_801860E4(int unknown);

}

extern "C" {
const char *lbl_802D50A4[] = {
    "REC_Car_PathNode09",
    "REC_Car_PathNode11",
    "REC_Car_PathNode14",
    "EAR_GolfCart_pathnode06",
    "CAG_Car_PathNode03",
    "CAG_Car_PathNode06",
    "CAG_Car_PathNode16",
    "AQA_Cars_Pathnode01",
    "AQA_Cars_Pathnode04",
    "AQA_Cars_Pathnode07",
    "AQA_Cars_Pathnode10",
    "AQA_Cars_Pathnode13",
    "AQA_Cars_Pathnode16",
    "STR_Car_PathNode05",
    "STR_Car_PathNode01",
    "ALL_Car_PathNode02",
    "ALL_Car_PathNode09",
    "Leg_Car_PathNode12",
    "Leg_Car_PathNode15",
    0,
};

unsigned char lbl_802D50F4[13] = { 70, 70, 0, 0, 80, 99, 99, 8, 99, 99, 99, 99, 30 };

Struct_802D5104 lbl_802D5104[9] = {
    { fn_800691E8, fn_80069398, fn_800695F0 },
    { fn_800696A4, fn_8006A38C, fn_8006B1CC },
    { fn_80069858, fn_8006A4D8, fn_8006B25C },
    { fn_800699C8, fn_8006A5C8, fn_8006B2EC },
    { fn_80069B4C, fn_8006A6B8, fn_8006B37C },
    { fn_80069D00, fn_8006A804, fn_8006B40C },
    { fn_80069EB4, fn_8006A950, fn_8006B49C },
    { fn_8006A068, fn_8006AA9C, fn_8006B52C },
    { fn_8006A21C, fn_8006ABE8, fn_8006B5BC },
};

int lbl_802D5170[4] = { 0x02D2BB24, 0x028C7A9A, 0x02EDEB7B, 0x02F323C1 };
float lbl_802D5180[3] = { 0.0f };

Entry_8030A660 lbl_802D518C[145] = {
    { 0, 7, 0, 0x51, 1 },
    { 1, 7, 1, 0x51, 1 },
    { 2, 7, 2, 0x61, 1 },
    { 3, 7, 3, 0x6B, 1 },
    { 4, 7, 4, 0x6B, 1 },
    { 5, 6, 0, 0x5B, 1 },
    { 6, 3, 0, 0x6B, 1 },
    { 7, 4, 0, 0x6B, 1 },
    { 8, 3, 1, 0x5B, 1 },
    { 9, 4, 1, 0x5B, 1 },
    { 10, 3, 2, 0x66, 1 },
    { 11, 4, 2, 0x66, 1 },
    { 12, 5, 0, 0x5B, 1 },
    { 13, 5, 1, 0x5B, 1 },
    { 14, 5, 2, 0x5B, 1 },
    { 15, 5, 3, 0x5B, 1 },
    { 16, 5, 4, 0x5B, 1 },
    { 17, 5, 5, 0x5B, 1 },
    { 18, 13, 0, 0x51, 1 },
    { 19, 13, 1, 0x51, 1 },
    { 20, 13, 2, 0x51, 1 },
    { 21, 14, 0, 0x51, 1 },
    { 22, 14, 1, 0x51, 1 },
    { 23, 14, 2, 0x51, 1 },
    { 24, 13, 3, 0x5B, 1 },
    { 25, 13, 4, 0x5B, 1 },
    { 26, 14, 3, 0x5B, 1 },
    { 27, 14, 4, 0x5B, 1 },
    { 28, 13, 5, 0x5B, 1 },
    { 29, 13, 6, 0x5B, 1 },
    { 30, 13, 7, 0x5B, 1 },
    { 31, 14, 5, 0x5B, 1 },
    { 32, 14, 6, 0x5B, 1 },
    { 33, 14, 7, 0x5B, 1 },
    { 34, 15, 0, 0x5B, 1 },
    { 35, 15, 1, 0x5B, 1 },
    { 36, 8, 0, 0x6B, 1 },
    { 37, 8, 1, 0x6B, 1 },
    { 38, 8, 2, 0x6B, 1 },
    { 39, 8, 3, 0x6B, 1 },
    { 40, 8, 4, 0x6B, 1 },
    { 41, 8, 5, 0x6B, 1 },
    { 42, 17, 0, 0x1F, 1 },
    { 43, 17, 1, 0x1F, 1 },
    { 44, 17, 2, 0x1F, 1 },
    { 45, 11, 0, 0x7F, 1 },
    { 46, 11, 4, 0x7F, 1 },
    { 47, 11, 1, 0x7F, 1 },
    { 48, 11, 5, 0x7F, 1 },
    { 49, 11, 2, 0x7F, 1 },
    { 50, 11, 6, 0x7F, 1 },
    { 51, 11, 3, 0x7F, 1 },
    { 52, 11, 7, 0x7F, 1 },
    { 53, 11, 8, 0x7F, 1 },
    { 54, 11, 9, 0x7F, 1 },
    { 55, 11, 10, 0x7F, 1 },
    { 56, 11, 11, 0x7F, 1 },
    { 57, 11, 12, 0x7F, 1 },
    { 58, 10, 0, 0x51, 1 },
    { 59, 10, 3, 0x51, 1 },
    { 60, 10, 4, 0x5B, 1 },
    { 61, 10, 5, 0x51, 1 },
    { 62, 10, 10, 0x5B, 1 },
    { 63, 10, 15, 0x6B, 1 },
    { 64, 12, 4, 0x39, 1 },
    { 65, 2, 4, 0x52, 5 },
    { 66, 16, 0, 0x52, 5 },
    { 67, 16, 1, 0x52, 5 },
    { 68, 9, 0, 0x6B, 1 },
    { 69, 9, 1, 0x6B, 1 },
    { 70, 9, 2, 0x6B, 1 },
    { 71, 9, 3, 0x6B, 1 },
    { 72, 9, 4, 0x5B, 1 },
    { 73, 9, 5, 0x5B, 1 },
    { 74, 9, 6, 0x5B, 1 },
    { 75, 9, 7, 0x5B, 1 },
    { 76, 9, 8, 0x5B, 1 },
    { 77, 9, 9, 0x5B, 1 },
    { 78, 9, 10, 0x45, 1 },
    { 79, 9, 11, 0x45, 1 },
    { 80, 9, 12, 0x5B, 1 },
    { 81, 9, 13, 0x5B, 1 },
    { 82, 9, 14, 0x5B, 1 },
    { 83, 9, 15, 0x5B, 1 },
    { 84, 9, 16, 0x5B, 1 },
    { 85, 9, 17, 0x5B, 1 },
    { 86, 9, 18, 0x5B, 1 },
    { 87, 9, 19, 0x5B, 1 },
    { 88, 9, 20, 0x5B, 1 },
    { 89, 9, 21, 0x5B, 1 },
    { 90, 9, 22, 0x5B, 1 },
    { 91, 9, 23, 0x5B, 1 },
    { 92, 9, 24, 0x5B, 1 },
    { 93, 9, 25, 0x5B, 1 },
    { 94, 9, 26, 0x5B, 1 },
    { 95, 9, 27, 0x5B, 1 },
    { 96, 9, 28, 0x5B, 1 },
    { 97, 9, 29, 0x5B, 1 },
    { 98, 9, 30, 0x5B, 1 },
    { 99, 9, 31, 0x5B, 1 },
    { 100, 9, 32, 0x5B, 1 },
    { 101, 9, 33, 0x5B, 1 },
    { 102, 9, 34, 0x5B, 1 },
    { 103, 9, 35, 0x5B, 1 },
    { 104, 9, 36, 0x5B, 1 },
    { 105, 9, 37, 0x7F, 1 },
    { 106, 9, 38, 0x5B, 1 },
    { 107, 9, 39, 0x5B, 1 },
    { 108, 9, 40, 0x5B, 1 },
    { 109, 9, 41, 0x5B, 1 },
    { 110, 9, 42, 0x5B, 1 },
    { 111, 9, 43, 0x5B, 1 },
    { 112, 9, 44, 0x5B, 1 },
    { 113, 6, 0, 0x61, 1 },
    { 114, 0, 0, 0x6B, 1 },
    { 115, 0, 1, 0x6B, 1 },
    { 116, 0, 2, 0x6B, 1 },
    { 117, 0, 3, 0x6B, 1 },
    { 118, 0, 4, 0x6B, 1 },
    { 119, 0, 5, 0x6B, 1 },
    { 120, 0, 6, 0x6B, 1 },
    { 121, 0, 12, 0x6B, 1 },
    { 122, 0, 13, 0x6B, 1 },
    { 123, 0, 14, 0x6B, 1 },
    { 124, 0, 15, 0x6B, 1 },
    { 125, 0, 16, 0x6B, 1 },
    { 126, 0, 17, 0x5B, 1 },
    { 127, 0, 18, 0x5B, 1 },
    { 128, 0, 19, 0x6B, 1 },
    { 129, 0, 20, 0x6B, 1 },
    { 130, 0, 21, 0x6B, 1 },
    { 131, 0, 22, 0x5B, 1 },
    { 132, 0, 32, 0x6B, 1 },
    { 133, 0, 33, 0x6B, 1 },
    { 134, 0, 34, 0x7F, 1 },
    { 135, 0, 36, 0x6B, 1 },
    { 136, 0, 37, 0x5B, 1 },
    { 137, 0, 38, 0x6B, 1 },
    { 138, 0, 39, 0x6B, 1 },
    { 139, 1, 3, 0x6B, 1 },
    { 140, 1, 4, 0x6B, 1 },
    { 141, 1, 5, 0x6B, 1 },
    { 142, 1, 6, 0x6B, 1 },
    { 143, 1, 7, 0x6B, 1 },
    { 144, 1, 8, 0x6B, 1 },
};

Entry_8030A664 lbl_802D5F24[18] = {
    { 0, lbl_802EBFCC, 0, 0, 0, 1, 0 },
    { 2, lbl_802EBFE4, 0, -1, 0, 2, 2 },
    { 3, lbl_802EBFE4, 0, 0, 0, 3, 2 },
    { 4, lbl_802EBFE4, 0, 15, 0, 4, 2 },
    { 5, lbl_802EBFE4, 0, 30, 0, 5, 2 },
    { 6, lbl_802EBFE4, 0, 72, 0, 6, 2 },
    { 7, lbl_802EBFE4, 0, 77, 0, 7, 2 },
    { 8, lbl_802EBFE4, 0, -1, 0, 8, 2 },
    { 9, lbl_802EBFE4, 0, 193, 0, 9, 2 },
    { 10, lbl_802EBFE4, 0, 143, 0, 11, 2 },
    { 11, lbl_802EBFE4, 0, 142, 0, 12, 2 },
    { 12, lbl_802EBFE4, 0, 144, 0, 13, 2 },
    { 13, lbl_802EBFE4, 0, 145, 0, 14, 2 },
    { 14, lbl_802EBFE4, 0, 146, 0, 15, 2 },
    { 15, lbl_802EBFE4, 0, 155, 0, 16, 2 },
    { 16, lbl_802EBFE4, 0, -1, 0, 17, 2 },
    { 17, lbl_802EBFE4, 0, 191, 0, 18, 2 },
    { 0, 0, 0, 0, 3, 0, 0 },
};
Struct_802D611C lbl_802D611C[20] = {
    { 0, 0xC00000, 0xe4b800 },
    { 1, 0xe4b800, 0xe89c00 },
    { 2, 0xe89c00, 0xe8c400 },
    { 3, 0xe8c400, 0xe9e400 },
    { 4, 0xe9e400, 0xeb0400 },
    { 5, 0xeb0400, 0xec3000 },
    { 6, 0xec3000, 0xede000 },
    { 7, 0xede000, 0xee4000 },
    { 8, 0xee4000, 0xf00400 },
    { 9, 0xf00400, 0xf81000 },
    { 10, 0xf81000, 0xf81400 },
    { 11, 0xf81400, 0xf93000 },
    { 12, 0xf93000, 0xfb0800 },
    { 13, 0xfb0800, 0xfb1400 },
    { 14, 0xfb1400, 0xfc3800 },
    { 15, 0xfc3800, 0xfd5c00 },
    { 16, 0xfd5c00, 0xfea400 },
    { 17, 0xfea400, 0xffd800 },
    { 18, 0xffd800, 0x1000000 },
    { -1, 0xFFFFFFFF, 0xFFFFFFFF },
};
Handler_8030A668 lbl_802D620C[] = { fn_8006D358, fn_8006E0DC, fn_80073F5C, fn_80071748, fn_8006E924, fn_801860E4, 0 };

Struct_8006C2C8 lbl_802D6228 = { 18, 1, lbl_802D518C, lbl_802D611C, lbl_802D5F24, lbl_802D620C };

Entry_8030A664 lbl_802D6240[3] = {
    { 0, lbl_802EBFCC, 0, 0, 0, 1, 0 },
    { 1, lbl_802EBFCC, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 0, 3, 0, 0 },
};
Handler_8030A668 lbl_802D6294[] = { fn_8007418C, fn_801860E4, 0 };

Struct_8006C2C8 lbl_802D62A0 = { 18, 1, lbl_802D518C, lbl_802D611C, lbl_802D6240, lbl_802D6294 };

Struct_802D62B8 lbl_802D62B8 = { 10.0f, 0.3f, 1.0f, 1.0f };
Struct_802D62B8 lbl_802D62C8 = { 10.0f, 0.1f, 1.0f, 1.0f };

Struct_802D62D8 lbl_802D62D8[9] = {
    { 0xFF, &lbl_802D62B8, fn_8006CEC8 },
    { 0xFF, &lbl_802D62B8, fn_8006CEC8 },
    { 0xFF, &lbl_802D62B8, fn_8006CEC8 },
    { 0xFF, 0, 0 },
    { 0xFF, &lbl_802D62C8, fn_8006CEC8 },
    { 0xFF, &lbl_802D62C8, fn_8006CEC8 },
    { 0xFF, &lbl_802D62B8, fn_8006CEC8 },
    { 0xFF, 0, 0 },
    { 0xFF, 0, 0 },
};

Vector_80039F5C lbl_802D6344 = { 3.4028235e38f, 3.4028235e38f, 3.4028235e38f };

}

static ModuleDependency sDependencies[] = { &gSnd, 0 };

SndgPathfinder gSndgPathfinder;

extern "C" {
unsigned char lbl_8030A61C[9][6];
Struct_8030A654 lbl_8030A654;
Struct_8030A680 lbl_8030A680[9];
Struct_8030A830 lbl_8030A830;
int lbl_8030A868[128];

Struct_803EA67C *lbl_803EA67C = 0;
unsigned int lbl_803EA680 = 99;
int lbl_803EA684 = -1;
unsigned int lbl_803EA688 = 0xFFFFFFFF;
unsigned int lbl_803EA68C = 100;
int lbl_803EA690 = 0x1000;
}

static void *sLinks[] = { 0 };

extern "C" {
SndgPathfinderState *lbl_803EA698 = 0;
Struct_8030A830 *lbl_803EA69C = &lbl_8030A830;
Struct_8030A518 *lbl_803EA6A0 = 0;
int lbl_803EA6A4 = -1;
unsigned char lbl_803EA6A8[4] = { 1, 50, 50, 50 };
int lbl_803EA6AC = 0;
unsigned char lbl_803EA6B0 = 0;
unsigned char lbl_803EA6B1 = 0;
int lbl_803EA6B4 = 0;
int lbl_803EC814;
}

static const int lbl_80290758[12] = { 70, 70, 61, 70, 70, 70, 55, 70, 60, 67, 70, 70 };

static const Struct_80290788 lbl_80290788[12][9] = {
    { { 3, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 1, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 1, 0.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 2, 9.0f } },
    { { 3, 0.0f }, { 3, 2.0f }, { 0, 0.0f }, { 1, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 3, 2.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 4, 5.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 2, 2.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 4, 2.0f }, { 1, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 1, 0.2f } },
    { { 3, 0.0f }, { 3, 0.5f }, { 0, 0.0f }, { 0, 0.0f }, { 1, 0.5f }, { 1, 0.5f }, { 1, 0.5f }, { 1, 0.5f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 0, 2.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 1, 2.0f }, { 0, 0.0f }, { 0, 0.0f }, { 1, 2.0f }, { 0, 0.0f }, { 0, 0.0f }, { 6, 2.0f }, { 1, 0.2f } },
    { { 3, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 1, 0.5f }, { 0, 0.0f }, { 0, 0.0f } },
    { { 3, 0.0f }, { 6, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f }, { 0, 0.0f } },
};

#define ALLOC_LIST(list, Type, slot)                                                      \
    if (lbl_803EA67C->mCounts[slot] != 0) {                                               \
        lbl_803EA67C->list = (Type **)fn_801D2B7C(lbl_803EA67C->mCounts[slot] * 4, 0, 0); \
        memset(lbl_803EA67C->list, 0, lbl_803EA67C->mCounts[slot] * 4);                   \
    }

extern "C" void fn_80068154(void)
{
    int level = fn_800A3444();
    int i;
    int j;

    for (i = 0; i < 9; i++) {
        lbl_803EA67C->mCounts[i] = lbl_80290788[level][i].mCount;
        lbl_803EA67C->mScales[i] = lbl_80290788[level][i].mScale;
        for (j = 0; j < 6; j++) {
            lbl_8030A61C[i][j] = 0xFF;
        }
    }
    ALLOC_LIST(mSound0, Sound0, 0);
    ALLOC_LIST(mSound3, Sound3, 3);
    ALLOC_LIST(mSound1, SoundVFP, 1);
    ALLOC_LIST(mSound2, SoundVP, 2);
    ALLOC_LIST(mSound4, SoundVFP, 4);
    ALLOC_LIST(mSound5, SoundVFP, 5);
    ALLOC_LIST(mSound6, SoundVFP, 6);
    ALLOC_LIST(mSound7, SoundVFP, 7);
    ALLOC_LIST(mSound8, SoundVP, 8);
}

#define FREE_LIST(list, Type, slot)                         \
    if (lbl_803EA67C->mCounts[slot] != 0) {                 \
        unsigned int i;                                     \
        for (i = 0; i < lbl_803EA67C->mCounts[slot]; i++) { \
            Type *s = lbl_803EA67C->list[i];                \
            if (s != 0) {                                   \
                delete s;                                   \
            }                                               \
        }                                                   \
        fn_801D2BD0(lbl_803EA67C->list);                    \
        lbl_803EA67C->list = 0;                             \
    }

extern "C" void fn_80068418(void)
{
    FREE_LIST(mSound8, SoundVP, 8);
    FREE_LIST(mSound7, SoundVFP, 7);
    FREE_LIST(mSound6, SoundVFP, 6);
    FREE_LIST(mSound5, SoundVFP, 5);
    FREE_LIST(mSound4, SoundVFP, 4);
    FREE_LIST(mSound2, SoundVP, 2);
    FREE_LIST(mSound1, SoundVFP, 1);
    FREE_LIST(mSound3, Sound3, 3);
    FREE_LIST(mSound0, Sound0, 0);
}

extern "C" void fn_80068A04(void)
{
    int level = fn_800A3444();

    switch (level) {
    case 0:
        fn_801B3084(0x2000000, "Ambnum", 2);
        break;
    case 1:
        fn_801B3084(0x2000000, "Ambnum", 4);
        break;
    case 3:
        fn_801B3084(0x2000000, "Ambnum", 6);
        break;
    case 2:
        fn_801B3084(0x2000000, "Ambnum", 1);
        break;
    case 4:
        fn_801B3084(0x2000000, "Ambnum", 7);
        break;
    case 9:
        fn_801B3084(0x2000000, "Ambnum", 3);
        break;
    case 5:
        fn_801B3084(0x2000000, "Ambnum", 5);
        break;
    case 6:
        fn_801B3084(0x2000000, "Ambnum", 8);
        break;
    case 7:
        fn_801B3084(0x2000000, "Ambnum", 9);
        break;
    case 8:
        fn_801B3084(0x2000000, "Ambnum", 10);
        break;
    case 11:
        fn_801B3084(0x2000000, "Ambnum", 11);
        break;
    case 10:
        fn_801B3084(0x2000000, "Ambnum", 12);
        break;
    default:
        fn_801B3084(0x2000000, "Ambnum", 1);
        break;
    }
    lbl_803EA68C = lbl_80290758[level];
    lbl_803EA67C->mUnknownC = 0x12000001;
    fn_8006DC98(lbl_803EA67C->mpUnknown4, 2, 0x12000001, 1.0f);
}

extern "C" void fn_80068C1C(void)
{
    int level = fn_800A3444();

    lbl_803EA67C->mHandles[0] = 0;
    lbl_803EA67C->mHandles[1] = 0;
    lbl_803EA67C->mHandles[2] = 0;
    lbl_803EA67C->mHandles[3] = 0;
    lbl_803EA67C->mHandles[4] = 0;
    lbl_803EA67C->mHandles[5] = 0;
    lbl_803EA67C->mHandles[8] = 0;
    lbl_803EA67C->mHandles[7] = 0;
    lbl_803EA67C->mHandles[6] = 0;
    if (lbl_80290788[level][0].mCount != 0) {
        lbl_803EA67C->mHandles[0] = fn_801F4DAC(lbl_803EA67C->mpUnknown10, 0, 0);
    }
    if (lbl_80290788[level][1].mCount != 0) {
        lbl_803EA67C->mHandles[1] = fn_801F4DAC(lbl_803EA67C->mpUnknown10, 3, 0);
    }
    if (lbl_80290788[level][2].mCount != 0) {
        lbl_803EA67C->mHandles[2] = fn_801F4DAC(lbl_803EA67C->mpUnknown10, 6, 0);
    }
    if (lbl_80290788[level][3].mCount != 0) {
        lbl_803EA67C->mHandles[3] = fn_801F4DAC(lbl_803EA67C->mpUnknown10, 1, 0);
    }
    if (lbl_80290788[level][8].mCount != 0) {
        lbl_803EA67C->mHandles[4] = fn_801F4DAC(lbl_803EA67C->mpUnknown10, 7, 0);
    }
    if (lbl_80290788[level][4].mCount != 0) {
        lbl_803EA67C->mHandles[5] = fn_801F4DAC(lbl_803EA67C->mpUnknown10, 2, 0);
    }
    if (lbl_80290788[level][5].mCount != 0) {
        lbl_803EA67C->mHandles[6] = fn_801F4DAC(lbl_803EA67C->mpUnknown10, 4, 0);
    }
    if (lbl_80290788[level][6].mCount != 0) {
        lbl_803EA67C->mHandles[7] = fn_801F4DAC(lbl_803EA67C->mpUnknown10, 5, 0);
    }
    if (lbl_80290788[level][7].mCount != 0) {
        lbl_803EA67C->mHandles[8] = fn_801F4DAC(lbl_803EA67C->mpUnknown10, 8, 0);
    }
}

extern "C" void fn_80068E00(void)
{
    if (lbl_803EA67C->mHandles[0] != 0) {
        fn_801F4F28(lbl_803EA67C->mHandles[0]);
    }
    if (lbl_803EA67C->mHandles[1] != 0) {
        fn_801F4F28(lbl_803EA67C->mHandles[1]);
    }
    if (lbl_803EA67C->mHandles[2] != 0) {
        fn_801F4F28(lbl_803EA67C->mHandles[2]);
    }
    if (lbl_803EA67C->mHandles[3] != 0) {
        fn_801F4F28(lbl_803EA67C->mHandles[3]);
    }
    if (lbl_803EA67C->mHandles[4] != 0) {
        fn_801F4F28(lbl_803EA67C->mHandles[4]);
    }
    if (lbl_803EA67C->mHandles[5] != 0) {
        fn_801F4F28(lbl_803EA67C->mHandles[5]);
    }
    if (lbl_803EA67C->mHandles[8] != 0) {
        fn_801F4F28(lbl_803EA67C->mHandles[8]);
    }
    if (lbl_803EA67C->mHandles[7] != 0) {
        fn_801F4F28(lbl_803EA67C->mHandles[7]);
    }
    if (lbl_803EA67C->mHandles[6] != 0) {
        fn_801F4F28(lbl_803EA67C->mHandles[6]);
    }
}

extern "C" void fn_80068ED0(Vector_80039F5C *pPos, unsigned short *pPan, short *pSpan)
{
    Vector_80039F5C position;
    Camera_8013F738 *pCamera;
    int angle;

    pCamera = fn_8013FA04(fn_8013F9F8());
    position.mX = pCamera->mHeader.mUnknown04[0];
    position.mY = pCamera->mHeader.mUnknown04[1];
    position.mZ = pCamera->mHeader.mUnknown04[2];
    angle = fn_8013FD0C(fn_8013F9F8());
    if (fn_801784C4()) {
        angle = (angle + 0x800000) & 0xFFFFFF;
        position.mX = -position.mX;
        position.mY = -position.mY;
    }
    fn_8006CB40(&position, pPos, angle, pPan, pSpan);
}

extern "C" float fn_80068F70(Vector_80039F5C *pPos)
{
    Vector_80039F5C position;
    Camera_8013F738 *pCamera;

    pCamera = fn_8013FA04(fn_8013F9F8());
    position.mX = pCamera->mHeader.mUnknown04[0];
    position.mY = pCamera->mHeader.mUnknown04[1];
    position.mZ = pCamera->mHeader.mUnknown04[2];
    if (fn_801784C4()) {
        position.mX = -position.mX;
        position.mY = -position.mY;
    }
    return fn_8022785C(&position, pPos);
}

#define MIN(a, b) ((a) <= (b) ? (a) : (b))

static inline int ClampVolume(int volume)
{
    if (volume < 0) {
        volume = 0;
    } else if (volume > 127) {
        volume = 127;
    }
    return volume;
}

extern "C" int fn_80068FE8(Sound0 *pEntry, void *pObject, int index, int init)
{
    Vector_80039F5C position;
    Vector_80039F5C other;
    float height;
    float distance;
    int result;

    fn_80137D58((Object_80137ABC *)pObject, &position);
    height = position.mZ;
    fn_80138064((Object_80137ABC *)pObject, &other);
    result = 1;
    distance = fn_8022785C(&position, &other);
    if (init) {
        lbl_802D5180[index] = distance;
        if (fn_800A8444(fn_80178308()) == 0) {
            pEntry->mUnknown4 = ClampVolume(MIN((int)(MIN(distance, 50.0f) * (127.0f / 50.0f)), 124));
        } else {
            pEntry->mUnknown4 = 127;
        }
    }
    pEntry->mUnknown10 = ClampVolume(height >= 1.5f ? (int)((MIN(height, 15.0f) - 1.5f) * (127.0f / (15.0f - 1.5f))) : 0);
    if (!init) {
        if (pEntry->mUnknownC < (int)(distance * 127.0f / lbl_802D5180[index])) {
            result = 0;
        }
    }
    pEntry->mUnknownC = ClampVolume((int)(distance * 127.0f / lbl_802D5180[index]));
    return result;
}

static inline unsigned int SoundVolume(int type)
{
    unsigned int volume = lbl_803EA688 * lbl_802D50F4[type] / 100;
    if (volume > 99) {
        volume = 99;
    }
    return volume;
}

extern "C" void fn_800691E8(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (lbl_803EA67C->mSound0[index] == 0) {
        unsigned short pan;
        short unk;
        fn_80068ED0(pPos, &pan, &unk);
        lbl_803EA684 = SoundVolume(4);
        if (lbl_803EA684 != 0) {
            lbl_803EA67C->mSound0[index] = new Sound0(lbl_803EA684, pan);
            fn_80068FE8(lbl_803EA67C->mSound0[index], pObject, index, 1);
            lbl_803EA67C->mSound0[index]->Commit();
        }
    }
}

extern "C" void fn_80069398(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (lbl_803EA67C->mSound0[index] != 0) {
        int volume = lbl_803EA684;
        unsigned short pan;
        short unk;
        fn_80068ED0(pPos, &pan, &unk);
        lbl_803EA67C->mSound0[index]->SetPan(pan);
        lbl_803EA67C->mSound0[index]->SetVolume(volume);
        if (fn_80068FE8(lbl_803EA67C->mSound0[index], pObject, index, 0)) {
            lbl_803EA67C->mSound0[index]->Commit();
            int v = lbl_803EA67C->mSound0[index]->mUnknown10;
            int cutoff;
            if (v >= 0) {
                if (v <= 127) {
                    cutoff = (int)((127.0f - v) * (17500.0f / 127.0f) + 2500.0f);
                } else {
                    cutoff = 2500;
                }
            } else {
                cutoff = 20000;
            }
            fn_80073144(cutoff, 0);
            float level = fn_8007F828(4);
            int w = lbl_803EA67C->mSound0[index]->mUnknown10;
            fn_8006D684(1, (w >= 0 ? (w <= 127 ? (int)(level / (w * 2.0f * (1.0f / 127.0f) + 1.0f))
                                                : (int)(level * (1.0f / 3.0f)))
                                    : (int)level) * 10);
        } else {
            fn_8006BC30(4, index);
        }
    }
}

extern "C" void fn_800695F0(int index)
{
    Sound0 *s = lbl_803EA67C->mSound0[index];
    if (s != 0) {
        delete s;
        lbl_803EA67C->mSound0[index] = 0;
        fn_80073144(20000, 0);
        fn_8006D684(1, fn_8007F828(4) * 10);
    }
}

extern "C" void fn_800696A4(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (lbl_803EA67C->mSound1[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(5);
        float f = fn_80068F70(pPos);
        fn_80068ED0(pPos, &pan, &unk);
        lbl_803EA67C->mSound1[index] = new SoundVFP(&lbl_803ECC9C, &lbl_803EB8C0, volume, (int)f, pan);
        lbl_803EA67C->mSound1[index]->Commit();
    }
}

extern "C" void fn_80069858(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (lbl_803EA67C->mSound2[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(6);
        fn_80068ED0(pPos, &pan, &unk);
        lbl_803EA67C->mSound2[index] = new SoundVP(&lbl_803ECC94, &lbl_803EB8B8, volume, pan);
        lbl_803EA67C->mSound2[index]->Commit();
    }
}

extern "C" void fn_800699C8(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (lbl_803EA67C->mSound3[index] == 0) {
        unsigned int volume = SoundVolume(7);
        unsigned short pan = 0;
        short unk = 0;
        int mode = 2;
        fn_80068ED0(pPos, &pan, &unk);
        lbl_803EA67C->mSound3[index] = new Sound3(volume, pan, mode);
        lbl_803EA67C->mSound3[index]->Commit();
    }
}

extern "C" void fn_80069B4C(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (lbl_803EA67C->mSound4[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(8);
        float f = fn_80068F70(pPos);
        fn_80068ED0(pPos, &pan, &unk);
        lbl_803EA67C->mSound4[index] = new SoundVFP(&lbl_803ECC6C, &lbl_803EB890, volume, (int)f, pan);
        lbl_803EA67C->mSound4[index]->Commit();
    }
}

extern "C" void fn_80069D00(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (lbl_803EA67C->mSound5[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(9);
        float f = fn_80068F70(pPos);
        fn_80068ED0(pPos, &pan, &unk);
        lbl_803EA67C->mSound5[index] = new SoundVFP(&lbl_803ECC84, &lbl_803EB8A8, volume, (int)f, pan);
        lbl_803EA67C->mSound5[index]->Commit();
    }
}

extern "C" void fn_80069EB4(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (lbl_803EA67C->mSound6[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(10);
        float f = fn_80068F70(pPos);
        fn_80068ED0(pPos, &pan, &unk);
        lbl_803EA67C->mSound6[index] = new SoundVFP(&lbl_803ECC8C, &lbl_803EB8B0, volume, (int)f, pan);
        lbl_803EA67C->mSound6[index]->Commit();
    }
}

extern "C" void fn_8006A068(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (lbl_803EA67C->mSound7[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(11);
        float f = fn_80068F70(pPos);
        fn_80068ED0(pPos, &pan, &unk);
        lbl_803EA67C->mSound7[index] = new SoundVFP(&lbl_803ECC7C, &lbl_803EB8A0, volume, (int)f, pan);
        lbl_803EA67C->mSound7[index]->Commit();
    }
}

extern "C" void fn_8006A21C(int index, Vector_80039F5C *pPos, void *pObject)
{
    if (lbl_803EA67C->mSound8[index] == 0) {
        unsigned short pan = 0;
        short unk = 0;
        unsigned int volume = SoundVolume(12);
        fn_80068ED0(pPos, &pan, &unk);
        lbl_803EA67C->mSound8[index] = new SoundVP(&lbl_803ECC74, &lbl_803EB898, volume, pan);
        lbl_803EA67C->mSound8[index]->Commit();
    }
}

#define UPDATE_VFP(name, list, type)                                      \
    extern "C" void name(int index, Vector_80039F5C *pPos, void *pObject) \
    {                                                                     \
        if (lbl_803EA67C->list[index] != 0) {                             \
            unsigned short pan = 0;                                       \
            short unk = 0;                                                \
            unsigned int volume = SoundVolume(type);                      \
            float f = fn_80068F70(pPos);                                  \
            fn_80068ED0(pPos, &pan, &unk);                                \
            lbl_803EA67C->list[index]->SetUnknown8((int)f);               \
            lbl_803EA67C->list[index]->SetPan(pan);                       \
            lbl_803EA67C->list[index]->SetVolume(volume);                 \
            lbl_803EA67C->list[index]->Commit();                          \
        }                                                                 \
    }

#define UPDATE_VP(name, list, type)                                       \
    extern "C" void name(int index, Vector_80039F5C *pPos, void *pObject) \
    {                                                                     \
        if (lbl_803EA67C->list[index] != 0) {                             \
            unsigned short pan;                                           \
            short unk;                                                    \
            unsigned int volume = SoundVolume(type);                      \
            fn_80068ED0(pPos, &pan, &unk);                                \
            lbl_803EA67C->list[index]->SetPan(pan);                       \
            lbl_803EA67C->list[index]->SetVolume(volume);                 \
            lbl_803EA67C->list[index]->Commit();                          \
        }                                                                 \
    }

UPDATE_VFP(fn_8006A38C, mSound1, 5)
UPDATE_VP(fn_8006A4D8, mSound2, 6)
UPDATE_VP(fn_8006A5C8, mSound3, 7)
UPDATE_VFP(fn_8006A6B8, mSound4, 8)
UPDATE_VFP(fn_8006A804, mSound5, 9)
UPDATE_VFP(fn_8006A950, mSound6, 10)
UPDATE_VFP(fn_8006AA9C, mSound7, 11)
UPDATE_VP(fn_8006ABE8, mSound8, 12)

#define SILENCE(list, type)                                                   \
    if (lbl_803EA67C->list != 0) {                                            \
        for (unsigned int i = 0; i < lbl_80290788[level][type].mCount; i++) { \
            if (lbl_803EA67C->list[i] != 0) {                                 \
                lbl_803EA67C->list[i]->SetVolume(0);                          \
                lbl_803EA67C->list[i]->Commit();                              \
            }                                                                 \
        }                                                                     \
    }

extern "C" void fn_8006ACD8(void)
{
    int level = fn_800A3444();
    SILENCE(mSound0, 0)
    SILENCE(mSound1, 1)
    SILENCE(mSound2, 2)
    SILENCE(mSound3, 3)
    SILENCE(mSound4, 4)
    SILENCE(mSound5, 5)
    SILENCE(mSound6, 6)
    SILENCE(mSound7, 7)
    SILENCE(mSound8, 8)
}

#define STOP(name, list, Type)               \
    extern "C" void name(int index)          \
    {                                        \
        Type *s = lbl_803EA67C->list[index]; \
        if (s != 0) {                        \
            delete s;                        \
            lbl_803EA67C->list[index] = 0;   \
        }                                    \
    }

STOP(fn_8006B1CC, mSound1, SoundVFP)
STOP(fn_8006B25C, mSound2, SoundVP)
STOP(fn_8006B2EC, mSound3, Sound3)
STOP(fn_8006B37C, mSound4, SoundVFP)
STOP(fn_8006B40C, mSound5, SoundVFP)
STOP(fn_8006B49C, mSound6, SoundVFP)
STOP(fn_8006B52C, mSound7, SoundVFP)
STOP(fn_8006B5BC, mSound8, SoundVP)

extern "C" int fn_8006B64C(void)
{
    return lbl_803EA67C != 0;
}

extern "C" void fn_8006B664(void)
{
    if (fn_801F3E28()) {
        lbl_803EA67C = (Struct_803EA67C *)fn_801D2B7C(sizeof(Struct_803EA67C), 0, 0);
        memset(lbl_803EA67C, 0, sizeof(Struct_803EA67C));
        lbl_803EA67C->mpUnknown0 = (void *)-1;
        lbl_803EA67C->mpUnknown4 = (void *)-1;
        lbl_803EA67C->mpUnknown10 = (void *)-1;
        lbl_803EA67C->mpUnknown0 = fn_801EEB44(lbl_802EBFF4, 44);
        lbl_803EA67C->mpUnknown4 = fn_801EEB44(lbl_802EC00C, 44);
        lbl_803EA67C->mpUnknown10 = fn_801EEB44(lbl_802EC000, 44);
        fn_801F4B88(lbl_803EA67C->mpUnknown0, 1, 0);
        lbl_803EA67C->mUnknown8 = fn_8006DBF8(lbl_803EA67C->mpUnknown4, 1);
        fn_80068A04();
        fn_80068C1C();
        fn_80068154();
        fn_8006DD70(lbl_803EA67C->mUnknownC, lbl_803EA680 * lbl_803EA68C / 100);
        lbl_803EA684 = (unsigned char)(fn_8007F828(4) * 10);
        lbl_803EA688 = (unsigned char)(fn_8007F828(4) * 10);
    }
}

extern "C" void fn_8006B790(void)
{
    if (fn_8006B64C()) {
        fn_80068418();
        fn_8006DD24(lbl_803EA67C->mUnknownC);
        fn_8006DC4C(lbl_803EA67C->mUnknown8);
        fn_80068E00();
        fn_801F4C5C();
        fn_801EEFAC(lbl_803EA67C->mpUnknown0);
        fn_801EEFAC(lbl_803EA67C->mpUnknown4);
        fn_801EEFAC(lbl_803EA67C->mpUnknown10);
        fn_801D2BD0(lbl_803EA67C);
        lbl_803EA67C = 0;
    }
}

static inline int IsActive(SoundObject *pSound) { return pSound != 0; }

extern "C" int fn_8006B810(int type, unsigned int index)
{
    int result = 0;
    if (fn_8006B64C() && index < lbl_803EA67C->mCounts[type - 4]) {
        switch (type) {
        case 4:
            result = IsActive(lbl_803EA67C->mSound0[index]);
            break;
        case 5:
            result = IsActive(lbl_803EA67C->mSound1[index]);
            break;
        case 6:
            result = IsActive(lbl_803EA67C->mSound2[index]);
            break;
        case 7:
            result = IsActive(lbl_803EA67C->mSound3[index]);
            break;
        case 8:
            result = IsActive(lbl_803EA67C->mSound4[index]);
            break;
        case 9:
            result = IsActive(lbl_803EA67C->mSound5[index]);
            break;
        case 10:
            result = IsActive(lbl_803EA67C->mSound6[index]);
            break;
        case 11:
            result = IsActive(lbl_803EA67C->mSound7[index]);
            break;
        case 12:
            result = IsActive(lbl_803EA67C->mSound8[index]);
            break;
        }
    }
    return result;
}

extern "C" void fn_8006B91C(int type, unsigned int index, Vector_80039F5C *pPos, void *pObject)
{
    if (fn_8006B64C() && lbl_802D5104[type - 4].mCreate && index < lbl_803EA67C->mCounts[type - 4]) {
        lbl_802D5104[type - 4].mCreate(index, pPos, pObject);
    }
}

extern "C" void fn_8006B9AC(int type, unsigned int index, Vector_80039F5C *pPos, void *pObject)
{
    if (fn_8006B64C() && fn_8006B810(type, index) && lbl_802D5104[type - 4].mUpdate &&
        index < lbl_803EA67C->mCounts[type - 4]) {
        lbl_802D5104[type - 4].mUpdate(index, pPos, pObject);
    }
}

extern "C" unsigned int fn_8006BA54(int type, int value)
{
    unsigned int result = 0;
    if (fn_8006B64C() && lbl_803EA67C->mCounts[type - 4] != 0) {
        int found = 0;
        unsigned int i;
        for (i = 0; i <= 5 && !found; i++) {
            if (lbl_8030A61C[type - 4][i] == value) {
                result = i;
                found = 1;
            }
        }
        if (!found) {
            for (i = 0; i <= 5; i++) {
                if (lbl_8030A61C[type - 4][i] == 0xFF) {
                    lbl_8030A61C[type - 4][i] = value;
                    result = i;
                    break;
                }
            }
        }
    }
    return result;
}

extern "C" int fn_8006BB44(int type)
{
    int result = 0;
    int level = fn_800A3444();
    if (type != 12) {
        switch (level) {
        case 2:
        case 4:
        case 5:
        case 7:
        case 9:
        case 10:
        case 11:
            result = 1;
            break;
        default:
            result = 0;
            break;
        }
    }
    return result;
}

extern "C" int fn_8006BBC4(Struct_8006BBC4 *p)
{
    const char *str = p->mUnknown8;
    int i;
    for (i = 0; lbl_802D50A4[i]; i++) {
        if (!strcmp(str, lbl_802D50A4[i])) {
            return 1;
        }
    }
    return 0;
}

extern "C" void fn_8006BC30(int type, unsigned int index)
{
    if (fn_8006B64C() && fn_8006B810(type, index) && lbl_802D5104[type - 4].mStop &&
        index < lbl_803EA67C->mCounts[type - 4]) {
        lbl_802D5104[type - 4].mStop(index);
    }
}

extern "C" void fn_8006BCC8(int type)
{
    if (fn_8006B64C()) {
        if (type == 2) {
            fn_8006ACD8();
        }
        fn_8006DE00(lbl_803EA67C->mUnknownC, lbl_802D5170[type]);
    }
}

extern "C" void fn_8006BD24(void)
{
    fn_8006BD4C();
    fn_8006BCC8(2);
}

extern "C" void fn_8006BD4C(void)
{
    if (fn_8006B64C()) {
        unsigned char type;
        for (type = 4; type <= 12; type++) {
            unsigned char i;
            for (i = 0; i < lbl_803EA67C->mCounts[type - 4]; i++) {
                fn_8006BC30(type, i);
            }
        }
    }
}

extern "C" void fn_8006BDD8(unsigned int volume)
{
    lbl_803EA680 = volume;
    if (fn_8006B64C()) {
        fn_8006DD70(lbl_803EA67C->mUnknownC, volume * lbl_803EA68C / 100);
        lbl_803EA684 = lbl_803EA688 = volume;
    }
}

extern "C" float fn_8006BE3C(int type)
{
    if (lbl_803EA67C) {
        return lbl_803EA67C->mScales[type - 4];
    }
    return 0.5f;
}

extern "C" Entry_8030A664 *fn_8006BE68(int type, int id)
{
    Entry_8030A664 *pEntry = lbl_8030A654.m10;

    while (pEntry->m10 != 3) {
        if (pEntry->m10 == type && pEntry->m0 == id) {
            break;
        }
        pEntry++;
    }
    return pEntry;
}

extern "C" int fn_8006BEBC(void *a, void *b)
{
    return -1;
}

extern "C" void fn_8006BEC4(void)
{
    lbl_8030A654.m1C = fn_801C68FC(1, 0, 20, sizeof(Node_8006BF4C), fn_8006BEBC, 0);
}

extern "C" void fn_8006BF08(void)
{
    if (lbl_8030A654.m1C != 0) {
        fn_801C69E4(lbl_8030A654.m1C);
        lbl_8030A654.m1C = 0;
    }
}

extern "C" int fn_8006BF4C(unsigned int index, void *a, int b, Callback_8006C548 cb)
{
    int result = 0;
    int isNew = 1;
    Node_8006BF4C *pNode;

    if (index >= lbl_8030A654.m4) {
        return 0;
    }
    if (lbl_8030A654.m1C == 0) {
        return 0;
    }
    for (pNode = (Node_8006BF4C *)fn_801C6B4C(lbl_8030A654.m1C, 0); pNode != 0;
         pNode = (Node_8006BF4C *)fn_801C6C84(lbl_8030A654.m1C, pNode)) {
        if (pNode->m4 == a && pNode->m8 == b) {
            isNew = 0;
        }
    }
    if (isNew) {
        pNode = (Node_8006BF4C *)fn_801C6A20(lbl_8030A654.m1C);
        if (pNode != 0) {
            pNode->m0 = index;
            pNode->m4 = a;
            pNode->m8 = b;
            pNode->mC = cb;
            fn_801C6AA4(lbl_8030A654.m1C, pNode, 0);
            result = 1;
        }
    }
    return result;
}

extern "C" void fn_8006C040(void *item)
{
    if (lbl_8030A654.m1C != 0) {
        fn_801C6C0C(lbl_8030A654.m1C, item);
    }
}

extern "C" void fn_8006C074(Node_8006BF4C *pNode)
{
    if (lbl_8030A654.m1C != 0) {
        if (fn_801F0C50(pNode->m4, pNode->m8) < fn_801D27F4(1)) {
            int *pSlot;
            Entry_8030A664 *pEntry;

            if (fn_8006C74C(pNode->m0)) {
                fn_8006C6EC(pNode->m0);
            }
            pSlot = &lbl_8030A654.m24[pNode->m0];
            pEntry = fn_8006BE68(0, pNode->m0);
            fn_801F3ED8(pNode->m4, pSlot, pNode->m8, pEntry->m14, pNode->mC);
            lbl_8030A654.m18 = pNode->m0;
        }
    }
}

extern "C" void fn_8006C120(int a)
{
    Node_8006BF4C *pNode;

    if (lbl_8030A654.m1C == 0) {
        return;
    }
    if (lbl_8030A654.m18 != 0x7FFFFFFF) {
        pNode = (Node_8006BF4C *)fn_801C6B4C(lbl_8030A654.m1C, 0);
        if (fn_8006C78C(pNode->m0)) {
            lbl_8030A654.m18 = 0x7FFFFFFF;
            fn_8006C040(pNode);
        }
        if (lbl_8030A654.m18 != 0x7FFFFFFF) {
            return;
        }
    }
    pNode = (Node_8006BF4C *)fn_801C6B4C(lbl_8030A654.m1C, 0);
    if (pNode != 0) {
        int start = 1;
        if (a && fn_800AD9B4() == 3) {
            start = 0;
        }
        if (start) {
            fn_8006C074(pNode);
        }
    }
}

extern "C" void fn_8006C1E8(void)
{
    while (fn_801C6B4C(lbl_8030A654.m1C, 0) != 0) {
        fn_8006C120(0);
        fn_801F4B20();
    }
}

extern "C" void fn_8006C22C(Entry_8030A664 *pEntry)
{
    while (pEntry->m10 != 3) {
        pEntry->m8 = fn_801EEB44(pEntry->m4, 44);
        fn_801F11AC(pEntry->m8, 1);
        pEntry++;
    }
}

extern "C" void fn_8006C284(Entry_8030A664 *pEntry)
{
    while (pEntry->m10 != 3) {
        fn_801EEFAC(pEntry->m8);
        pEntry++;
    }
}

extern "C" void fn_8006C2C8(Struct_8006C2C8 *pInit)
{
    lbl_8030A654.m4 = pInit->m0;
    lbl_8030A654.m8 = pInit->m4;
    lbl_8030A654.mC = pInit->m8;
    lbl_8030A654.m10 = pInit->m10;
    lbl_8030A654.m14 = pInit->m14;
    lbl_8030A654.m24 = (int *)fn_801D2B7C(pInit->m0 * 4, 0, 0);
    lbl_8030A654.m28 = (int *)fn_801D2B7C(pInit->m4 * 4, 0, 0);
    fn_801D34D0(lbl_8030A654.m24, pInit->m0 * 4, 0, 4);
    fn_801D34D0(lbl_8030A654.m28, pInit->m4 * 4, 0, 4);
    fn_8006BEC4();
    lbl_8030A654.m0 = 0;
    lbl_8030A654.m18 = 0x7FFFFFFF;
    lbl_8030A654.m20 = 1;
    fn_8006C22C(lbl_8030A654.m10);
    fn_8006C3C4(lbl_8030A654.m10);
    lbl_8030A654.m0 = -1;
    lbl_803EA690 = 0x1000;
    fn_8006C1E8();
}

extern "C" void fn_8006C3C4(Entry_8030A664 *pEntry)
{
    while (pEntry->m10 != 3) {
        switch (pEntry->m10) {
        case 0:
            if (pEntry->mC != -1) {
                if (pEntry->m18 & 2) {
                    fn_8006C548(pEntry->m0, pEntry->mC, 0);
                } else {
                    fn_8006C4D4(pEntry->m0);
                }
            }
            break;
        case 2:
            fn_8006CAF0(pEntry->m0);
            break;
        }
        pEntry++;
    }
}

extern "C" void fn_8006C454(void)
{
    int i;

    if (lbl_8030A654.m20) {
        for (i = 0; i < 20; i++) {
            fn_801CE7D0(1);
            fn_801F4B20();
        }
        fn_801F3C14();
        fn_8006BF08();
        fn_801D2BD0(lbl_8030A654.m24);
        fn_801D2BD0(lbl_8030A654.m28);
        lbl_8030A654.m24 = 0;
        lbl_8030A654.m28 = 0;
        lbl_8030A654.m20 = 0;
        fn_8006C284(lbl_8030A654.m10);
    }
}

extern "C" void fn_8006C4D4(unsigned int index)
{
    if (lbl_8030A654.m20 && index < lbl_8030A654.m4) {
        Entry_8030A664 *pEntry = fn_8006BE68(0, index);
        lbl_8030A654.m24[index] = fn_801F3E40(pEntry->m8, pEntry->mC, pEntry->m14);
    }
}

extern "C" int fn_8006C548(unsigned int index, int a, Callback_8006C548 cb)
{
    Entry_8030A664 *pEntry;
    int *pSlot;
    int queue;
    int result;
    int canQueue;

    if (!fn_801F3E28() || !lbl_8030A654.m20 || index >= lbl_8030A654.m4) {
        return 0;
    }
    pEntry = fn_8006BE68(0, index);
    pSlot = &lbl_8030A654.m24[index];
    queue = 0;
    result = 0;
    canQueue = fn_801F0C50(pEntry->m8, a) < fn_801D27F4(1);
    if (*pSlot != 0) {
        if (fn_801F0DB8(pEntry->m8, a)) {
            result = 1;
            if (cb != 0) {
                cb(*pSlot);
            }
        } else if (canQueue) {
            queue = 1;
            result = 1;
        }
    } else if (canQueue) {
        result = 1;
        queue = 1;
    }
    if (queue) {
        result = fn_8006BF4C(index, pEntry->m8, a, cb);
    }
    return result;
}

extern "C" int fn_8006C674(int index, int a)
{
    if (fn_801F3E28()) {
        int *pSlot = &lbl_8030A654.m24[index];
        if (*pSlot != 0 && fn_801F0DB8(fn_8006BE68(0, index)->m8, a)) {
            return 1;
        }
    }
    return 0;
}

extern "C" void fn_8006C6EC(unsigned int index)
{
    if (lbl_8030A654.m20 && index < lbl_8030A654.m4) {
        fn_801F3F74(lbl_8030A654.m24[index]);
        lbl_8030A654.m24[index] = 0;
    }
}

extern "C" int fn_8006C74C(unsigned int index)
{
    if (!lbl_8030A654.m20) {
        return 0;
    }
    if (index >= lbl_8030A654.m4) {
        return 0;
    }
    return lbl_8030A654.m24[index];
}

extern "C" int fn_8006C78C(unsigned int index)
{
    int result;
    int handle;

    if (!lbl_8030A654.m20 || index >= lbl_8030A654.m4) {
        return 0;
    }
    result = 0;
    handle = fn_8006C74C(index);
    if (handle != 0) {
        result = fn_801F4024(handle);
    }
    return result;
}

extern "C" int fn_8006C7F4(unsigned int index)
{
    if (!lbl_8030A654.m20 || !fn_801F3E28() || !fn_801F3E34()) {
        return 1;
    }
    return fn_8006C78C(index);
}

extern "C" int fn_8006C854(int index, Vector_80039F5C *pPos)
{
    int result;

    if (lbl_8030A654.m20) {
        Entry_8030A660 *pEntry = &lbl_8030A654.mC[index];
        result = fn_8006C8A4(index, pPos, pEntry->mC);
    } else {
        result = 0x7FFFFFFF;
    }
    return result;
}

extern "C" int fn_8006C8A4(int index, Vector_80039F5C *pPos, unsigned char c)
{
    int result = 0x7FFFFFFF;
    Entry_8030A660 *pEntry;
    unsigned int now;
    Struct_801F40F4 params;

    if (!lbl_8030A654.m20) {
        return 0x7FFFFFFF;
    }
    pEntry = &lbl_8030A654.mC[index];
    now = fn_801F7ABC();
    if (fn_801F41A0(pEntry->m14) != 0 || (unsigned int)(index - 0x72) <= 30 ||
        now - pEntry->m10 > fn_802372EC(1, 15) + 10) {
        fn_801F40F4(&params);
        params.mVolume = c;
        fn_8006D540(pEntry->mD, pPos, &params);
        if (params.mVolume != 0 && lbl_8030A654.m24[pEntry->m4] != 0) {
            result = pEntry->m14 = fn_801F4050(lbl_8030A654.m24[pEntry->m4], pEntry->m8, &params);
            pEntry->m10 = now;
            fn_8006E89C(index, pPos, c);
            if (lbl_803EA690 != 0x1000) {
                fn_801F4314(result, lbl_803EA690);
            }
        }
    }
    return result;
}

extern "C" void fn_8006C9D4(int index)
{
    if (lbl_8030A654.m20) {
        Entry_8030A660 *pEntry = &lbl_8030A654.mC[index];
        fn_801F4130(pEntry->m14);
    }
}

extern "C" void fn_8006CA18(int index, int a, unsigned char volume)
{
    Entry_8030A660 *pEntry = &lbl_8030A654.mC[index];
    int value = fn_8006D5FC(pEntry->mD, volume);

    if (a == 0) {
        fn_801F421C(pEntry->m14, value);
    } else {
        fn_801F4294(pEntry->m14, a, value);
    }
}

extern "C" void fn_8006CA84(int a)
{
    Handler_8030A668 *pHandler;

    for (pHandler = lbl_8030A654.m14; *pHandler != 0; pHandler++) {
        (*pHandler)(a);
    }
    fn_800728F8();
    fn_8006C120(1);
    fn_801F4B20();
}

extern "C" void fn_8006CAEC(void)
{
}

extern "C" void fn_8006CAF0(int index)
{
    Entry_8030A664 *pEntry = fn_8006BE68(2, index);
    lbl_8030A654.m28[index] = fn_801F438C(pEntry->m8, pEntry->mC);
}

extern "C" void fn_8006CB40(Vector_80039F5C *a, Vector_80039F5C *b, int angle, unsigned short *pOut0, short *pOut1)
{
    Vector_80039F5C dir;
    Vector_80039F5C flat;
    Vec2 delta;
    int rot;

    fn_80227690(&delta, b, a);
    rot = (fn_801CFE40(delta.y, delta.x) - angle + 0x400000) & 0xFFFFFF;
    *pOut0 = -(((rot - 0x400000) & 0xFFFFFF) / 256);

    fn_802276B4(&dir, b, a);
    flat.mX = dir.mX;
    flat.mY = dir.mY;
    flat.mZ = 0.0f;
    rot = fn_80227040(&flat, &dir);
    if (rot > 0x800000) {
        rot = 0x1000000 - rot;
    }
    if (dir.mZ < 0.0f) {
        *pOut1 = -(rot / 256);
    } else {
        *pOut1 = rot / 256;
    }
}

extern "C" unsigned char fn_8006CC48(void)
{
    return lbl_8030A654.m20;
}

extern "C" int fn_8006CC54(int index)
{
    Entry_8030A660 *pEntry = &lbl_8030A654.mC[index];
    return fn_801F41A0(pEntry->m14) == 0;
}

extern "C" unsigned char fn_8006CC90(int index)
{
    return lbl_8030A654.mC[index].mC;
}

extern "C" void fn_8006CCA8(float value)
{
    lbl_803EA690 = (int)(value * 4096.0f);
}

extern "C" void fn_8006CCD0(Struct_8006CCD0 *p)
{
    switch (p->mType) {
    case 0x1F:
        if (p->mUnknown10.mValue > 0x50000) {
            if (p->mUnknown10.mValue > 0x200000) {
                int id = 15;
                Object_80137ABC *pBall = fn_801374BC();
                if (pBall != 0 && pBall->mpUnknown00 != 0 && pBall->mpUnknown00->mUnknown660 != 0) {
                    id = ((Record_80170E64_294 *)pBall->mpUnknown00->mUnknown660)->m8;
                }
                fn_8006C854(fn_80071BA0(fn_800A3444(), id), &p->mPosition);
            } else {
                fn_8006C854(0x69, &p->mPosition);
            }
        }
        break;
    case 0x20: {
        Vector_80039F5C vec;
        fn_80137EC4((Object_80137ABC *)p->mUnknown10.mpObject, &vec);
        if (fn_802270D4(&vec) > 0.42f) {
            fn_800717E0(&p->mPosition);
        }
        fn_8006B91C(4, (unsigned char)p->mUnknown18, &p->mPosition, p->mUnknown10.mpObject);
        break;
    }
    case 0x21:
        fn_8006B9AC(4, (unsigned char)p->mUnknown18, &p->mPosition, p->mUnknown10.mpObject);
        break;
    case 0x22:
        fn_8006BC30(4, (unsigned char)p->mUnknown18);
        break;
    case 0x1D:
        fn_8006BC30(4, (unsigned char)p->mUnknown18);
        fn_8006C854(4, &p->mPosition);
        break;
    case 0x1C:
        fn_8006BC30(4, (unsigned char)p->mUnknown18);
        fn_8006C854(3, &p->mPosition);
        break;
    case 0x1E:
        fn_8009BCE8(&p->mUnknown0);
        if (p->mUnknown10.mValue != 0) {
            fn_8006C854(2, &p->mPosition);
        } else {
            fn_8006C854(3, &p->mPosition);
        }
        break;
    }
}

extern "C" void fn_8006CE84(Struct_8006CCD0 *p)
{
    fn_8006CCD0(p);
    fn_8006F850(p);
    fn_80070C40(p);
    fn_8006E148(p);
}

extern "C" void fn_8006CEC8(Struct_8030A688 *src)
{
    if (fn_8002D060(lbl_803EA368) == 0) {
        Camera_8013F738 *obj = fn_8013FA04(fn_8013F9F8());
        int angle;

        src->mOrigin.mX = obj->mHeader.mUnknown04[0];
        src->mOrigin.mY = obj->mHeader.mUnknown04[1];
        src->mOrigin.mZ = obj->mHeader.mUnknown04[2];
        if (fn_801784C4()) {
            src->mOrigin.mX = -src->mOrigin.mX;
            src->mOrigin.mY = -src->mOrigin.mY;
        }
        angle = fn_8013FD0C(fn_8013F9F8());
        if (fn_801784C4()) {
            angle = (angle + 0x800000) & 0xFFFFFF;
        }
        src->mAngle = angle;
    } else if (fn_80031054(&src->mOrigin) == 0) {
        Block_80170E64 *pBlock = fn_8013825C(fn_801374BC());

        src->mOrigin.mX = pBlock->mUnknown4.mX;
        src->mOrigin.mY = pBlock->mUnknown4.mY;
        src->mOrigin.mZ = pBlock->mUnknown4.mZ;
    }
}

extern "C" void fn_8006CF9C(Vector_80039F5C *origin, Vector_80039F5C *pos, unsigned short *pan, short *span)
{
    Vector_80039F5C delta;
    float dist;
    short scale;

    fn_802276B4(&delta, pos, origin);
    dist = fn_802270D4(&delta);
    if (dist < 5.0f) {
        scale = (short)(dist * 51.0f);
        *span = (*span * scale) / 255;
        switch (*pan >> 14) {
        case 0:
            *pan = (*pan * scale) / 255;
            break;
        case 1:
            *pan = 0x7FFF - ((0x7FFF - *pan) * scale) / 255;
            break;
        case 2:
            *pan = ((*pan - 0x8000) * scale) / 255 + 0x8000;
            break;
        case 3:
            *pan = 0xFFFF - ((0xFFFF - *pan) * scale) / 255;
            break;
        }
    }
}

extern "C" void fn_8006D0F8(void)
{
    int i;

    for (i = 0; i < 9; i++) {
        Struct_802D62D8 *rec = &lbl_802D62D8[i];
        Struct_8030A680 *e = &lbl_8030A680[i];
        Vector_80039F5C *origin = &e->mSource.mOrigin;

        e->mHandle = 0;
        e->m04 = 0;
        e->mScale = rec->mScale;
        e->m2C = rec->mScale;
        e->mSource.mUpdate = rec->mUpdate;
        e->mSource.mParams = rec->mParams;
        e->mSource.mAngle = 0x400000;
        origin->mX = origin->mY = origin->mZ = 0.0f;
        e->mPosition.mX = lbl_802D6344.mX;
        e->mPosition.mY = lbl_802D6344.mY;
        e->mPosition.mZ = lbl_802D6344.mZ;
    }
}

extern "C" void fn_8006D188(int withThird)
{
    int handle;

    fn_8006D0F8();

    handle = fn_801F44B0(0x10000, 20, 150, 0);
    lbl_8030A680[4].mHandle = handle;
    fn_801F49B8(handle, 0, 15);
    fn_801F4A38(handle, 0x55);

    handle = fn_801F44B0(0x10000, 20, 150, 0);
    lbl_8030A680[5].mHandle = handle;
    fn_801F49B8(handle, 0, 15);
    fn_801F4A38(handle, 0x55);

    if (withThird) {
        handle = fn_801F44B0(0x10000, 20, 150, 0);
        lbl_8030A680[6].mHandle = handle;
        fn_801F49B8(handle, 0, 15);
        fn_801F4A38(handle, 0x55);
    } else {
        lbl_8030A680[6].mHandle = 0;
    }
}

extern "C" void fn_8006D268(void)
{
    if (lbl_8030A680[6].mHandle) {
        fn_801F45D4(lbl_8030A680[6].mHandle);
    }
    fn_801F45D4(lbl_8030A680[4].mHandle);
    fn_801F45D4(lbl_8030A680[5].mHandle);
}

extern "C" void fn_8006D2B4(void)
{
    lbl_8030A680[4].mHandle = fn_801F44B0(0x10000, 20, 150, 0);
}

extern "C" void fn_8006D2EC(void)
{
    fn_801F45D4(lbl_8030A680[4].mHandle);
}

extern "C" void fn_8006D314(void)
{
    fn_8006D0F8();
    fn_8006D2B4();
}

extern "C" void fn_8006D338(void)
{
    fn_8006D2EC();
}

extern "C" void fn_8006D358(int unknown)
{
    unsigned int i;

    for (i = 0; i < 9; i++) {
        if (i == 6 && fn_8006D65C(6) && fn_8006D884(6) && !fn_801F48B8(fn_8006D65C(6))) {
            fn_801F4638(fn_8006D65C(6));
        }

        Struct_8030A688 *src = &lbl_8030A680[i].mSource;
        if (src->mParams && src->mUpdate) {
            src->mUpdate(src);
        }
    }
}

extern "C" unsigned char fn_8006D408(Struct_8030A688 *src, Vector_80039F5C *pos, unsigned char volume)
{
    if (src->mParams) {
        float level = volume;

        if (pos && !fn_802275D8(pos, &lbl_802D6344, 1e-7f)) {
            Vector_80039F5C delta;
            float dist;
            Struct_802D62B8 *params;

            fn_802276B4(&delta, pos, &src->mOrigin);
            dist = fn_802270D4(&delta);
            params = src->mParams;
            if (dist > params->mDistance && params->mFactor > 0.0f) {
                float t = (dist + (1.0f - params->mFactor) * (params->mDistance - dist)) / params->mDistance;
                level /= t * t;
            }
            level *= src->mParams->mScalePositional;
        } else {
            level *= src->mParams->mScaleNoPos;
        }
        volume = (int)(level > 127.0f ? 127.0f : level);
    }
    return volume;
}

extern "C" void fn_8006D540(int idx, Vector_80039F5C *pos, Struct_801F40F4 *out)
{
    Struct_8030A680 *e = &lbl_8030A680[idx];

    out->mVolume = (out->mVolume * e->mScale) / 255;
    out->mVolume = fn_8006D408(&e->mSource, pos, out->mVolume);
    if (pos) {
        fn_8006CB40(&e->mSource.mOrigin, pos, e->mSource.mAngle, &out->mPan, &out->mSpan);
        fn_8006CF9C(&e->mSource.mOrigin, pos, &out->mPan, &out->mSpan);
    }
}

extern "C" unsigned char fn_8006D5FC(int idx, unsigned char volume)
{
    Struct_8030A680 *e = &lbl_8030A680[idx];

    return fn_8006D408(&e->mSource, &e->mPosition, (volume * e->mScale) / 255);
}

extern "C" int fn_8006D65C(int idx)
{
    return lbl_8030A680[idx].mHandle;
}

extern "C" void fn_8006D670(int idx, int handle)
{
    lbl_8030A680[idx].mHandle = handle;
}

extern "C" void fn_8006D684(int idx, unsigned char percent)
{
    lbl_8030A680[idx].mScale = percent * 255U / 100;
    if (fn_8006D65C(idx)) {
        fn_8006D6F4(idx, 0, 127);
    }
}

extern "C" void fn_8006D6F4(int idx, int a, int volume)
{
    int handle = fn_8006D65C(idx);

    if (handle) {
        if (volume) {
            volume = fn_8006D5FC(idx, volume);
        }
        fn_801F4678(handle, a, volume);
    }
}

extern "C" void fn_8006D758(int idx, Vector_80039F5C *pos)
{
    Struct_8030A680 *e = &lbl_8030A680[idx];

    if (pos) {
        e->mPosition.mX = pos->mX;
        e->mPosition.mY = pos->mY;
        e->mPosition.mZ = pos->mZ;
    } else {
        e->mPosition.mX = lbl_802D6344.mX;
        e->mPosition.mY = lbl_802D6344.mY;
        e->mPosition.mZ = lbl_802D6344.mZ;
    }
    fn_8006D7CC(idx);
}

extern "C" void fn_8006D7CC(int idx)
{
    Struct_8030A680 *e = &lbl_8030A680[idx];

    if (e->mHandle) {
        unsigned short pan;
        short span;

        if (!fn_802275D8(&e->mPosition, &lbl_802D6344, 1e-7f)) {
            fn_8006CB40(&e->mSource.mOrigin, &e->mPosition, e->mSource.mAngle, &pan, &span);
            fn_8006CF9C(&e->mSource.mOrigin, &e->mPosition, &pan, &span);
        } else {
            span = pan = 0;
        }
        fn_801F4770(e->mHandle, pan, 0);
    }
}

extern "C" int fn_8006D884(int idx)
{
    if (fn_8006D65C(idx)) {
        Struct_801F4834 status;

        fn_801F4834(fn_8006D65C(idx), &status);
        if (status.mStatus == 0) {
            return 0;
        }
    }
    return 1;
}

extern "C" void fn_8006D8DC(int idx)
{
    if (fn_8006D65C(idx)) {
        fn_801F4638(fn_8006D65C(idx));
    }
}

extern "C" void fn_8006D91C(int a, int b)
{
    Struct_803EA698Entry *entry;

    for (entry = (Struct_803EA698Entry *)fn_801C6B4C(lbl_803EA698->mpPool[0], 0); entry;
         entry = (Struct_803EA698Entry *)fn_801C6C84(lbl_803EA698->mpPool[0], entry)) {
        entry->mFunc(a, b);
    }
}

extern "C" void fn_8006D98C(int a, int b)
{
    Struct_803EA698Entry *entry;

    for (entry = (Struct_803EA698Entry *)fn_801C6B4C(lbl_803EA698->mpPool[1], 0); entry;
         entry = (Struct_803EA698Entry *)fn_801C6C84(lbl_803EA698->mpPool[1], entry)) {
        entry->mFunc(a, b);
    }
}

extern "C" void fn_8006D9FC(int a, int b)
{
    Struct_803EA698Entry *entry;

    for (entry = (Struct_803EA698Entry *)fn_801C6B4C(lbl_803EA698->mpPool[2], 0); entry;
         entry = (Struct_803EA698Entry *)fn_801C6C84(lbl_803EA698->mpPool[2], entry)) {
        entry->mFunc(a, b);
    }
}

extern "C" int fn_8006DA6C(Item_8006DA6C *pItem, int key, Item_8006DA6C **ppResult)
{
    if (pItem->mKey == key) {
        *ppResult = pItem;
        return 0;
    }
    return -1;
}

ModuleDependency *SndgPathfinder::GetDependencies() { return sDependencies; }
ModuleDependency *SndgPathfinder::GetLinks() { return (ModuleDependency *)sLinks; }
const char *SndgPathfinder::GetName() { return "SndgPathfinder"; }

int SndgPathfinder::Init()
{
    lbl_803EA698 = new (0) SndgPathfinderState;
    memset(lbl_803EA698, 0, sizeof(SndgPathfinderState));
    lbl_803EA698->mpPool[0] = fn_801C68FC(1, 0, 4, 4, 0, 0);
    lbl_803EA698->mpPool[1] = fn_801C68FC(1, 0, 4, 4, 0, 0);
    lbl_803EA698->mpPool[2] = fn_801C68FC(1, 0, 4, 4, 0, 0);
    if (fn_801F3E28()) {
        Struct_801E0AEC desc;
        desc.mUnknown0 = 1;
        desc.mUnknown4 = 3;
        fn_801E0AEC(&desc);
        fn_801B2F18(fn_8006D91C, fn_8006D98C, fn_8006D9FC);
    }
    return 1;
}

int SndgPathfinder::Shutdown()
{
    if (fn_801F3E28()) {
        fn_801E0BE4();
    }
    fn_801C69E4(lbl_803EA698->mpPool[0]);
    fn_801C69E4(lbl_803EA698->mpPool[1]);
    fn_801C69E4(lbl_803EA698->mpPool[2]);
    delete lbl_803EA698;
    lbl_803EA698 = 0;
    return 1;
}

extern "C" int fn_8006DBF8(void *pData, int unknown)
{
    int result = -1;
    if (fn_801E0AE4()) {
        result = fn_801E0CA8(pData, unknown, 1);
    }
    return result;
}

extern "C" int fn_8006DC4C(int handle)
{
    int result = 0;
    if (fn_801E0AE4()) {
        result = fn_801E0D68(handle) >= 0;
    }
    return result;
}

extern "C" int fn_8006DC98(void *pData, int unknown, int id, float value)
{
    int result = 0;
    if (fn_801E0AE4()) {
        Struct_801E0DF0 desc;
        desc.mUnknown24 = 0;
        desc.mUnknown10 = 0;
        desc.mUnknown1C = 0;
        desc.mpData = pData;
        desc.mUnknown18 = unknown;
        desc.mId = id;
        desc.mValue = value;
        desc.mUnknown4 = 1000;
        desc.mUnknown8 = 2;
        result = fn_801E0DF0(&desc) >= 0;
    }
    return result;
}

extern "C" int fn_8006DD24(int id)
{
    int result = 0;
    if (fn_801E0AE4()) {
        result = fn_801E0EF8(id) >= 0;
    }
    return result;
}

extern "C" void fn_8006DD70(int id, unsigned int value)
{
    if (fn_801E0AE4()) {
        fn_801E0FBC(id, value);
    }
}

extern "C" void fn_8006DDB4(int a, int b, int c)
{
    if (fn_801E0AE4()) {
        fn_801E0FE0(a, b, c);
    }
}

extern "C" int fn_8006DE00(int id, int unknown)
{
    int result = 1;
    if (fn_801E0AE4()) {
        result = fn_801E0F9C(id, unknown) >= 0;
    }
    return result;
}

extern "C" int fn_8006DE54(int id, int unknown)
{
    int result = 1;
    if (fn_801E0AE4()) {
        result = fn_801E0F7C(id, unknown) >= 0;
    }
    return result;
}

extern "C" void fn_8006DEA8(int a, int b)
{
    if (fn_801E0AE4()) {
        fn_801E1048(a, b);
    }
}

extern "C" void fn_8006DEEC(int a)
{
    if (fn_801E0AE4()) {
        fn_801E1004(a, 1);
    }
}

extern "C" void fn_8006DF2C(int a)
{
    if (fn_801E0AE4()) {
        fn_801E1004(a, 0);
    }
}

extern "C" void fn_8006DF6C(int a)
{
    if (fn_801E0AE4()) {
        fn_801E1028(a);
    }
}

extern "C" void fn_8006DFA8(int value)
{
    if (gSndgPathfinder.fn_801CC96C()) {
        Item_8006DA6C *pItem = (Item_8006DA6C *)fn_801C6A20(lbl_803EA698->mpPool[0]);
        if (pItem) {
            pItem->mKey = value;
            fn_801C6AA4(lbl_803EA698->mpPool[0], pItem, 0);
        }
    }
}

extern "C" void fn_8006E010(int value)
{
    if (gSndgPathfinder.fn_801CC96C()) {
        Item_8006DA6C *pFound = 0;
        fn_801C6DCC(lbl_803EA698->mpPool[0], 0, value, &pFound, fn_8006DA6C);
        if (pFound) {
            fn_801C6C0C(lbl_803EA698->mpPool[0], pFound);
        }
    }
}

extern "C" void fn_8006E08C(void)
{
    lbl_803EA69C->mUnknown34 = fn_8016871C(fn_80178308())->mUnknown17;
    lbl_803EA69C->mUnknown30 = 0;
    lbl_803EA69C->mFlags = 0;
    lbl_803EA69C->mUnknown24.mX = 0.0f;
    lbl_803EA69C->mUnknown24.mY = 0.0f;
}

extern "C" void fn_8006E0DC(int unknown)
{
    unsigned char value;

    lbl_803EA69C->mUnknownA = fn_8009D990(1);
    lbl_803EA69C->mUnknownD = fn_8009D86C();
    value = fn_8009D990(0);
    if (value != lbl_803EA69C->mUnknownC) {
        lbl_803EA69C->mUnknownC = value;
    }
}

extern "C" void fn_8006E134(int flags)
{
    lbl_803EA69C->mFlags |= flags;
}

extern "C" void fn_8006E148(Struct_8006CCD0 *pEvent)
{
    switch (pEvent->mType) {
    case 0x1F:
        fn_80137D58(fn_801374BC(), &lbl_803EA69C->mUnknown24);
        break;
    case 0x8E:
        lbl_803EA69C->mFlags |= 1;
        break;
    case 0x8F:
        lbl_803EA69C->mUnknown1C = pEvent->mPosition.mX;
        lbl_803EA69C->mUnknown20 = pEvent->mPosition.mY;
        break;
    case 0x8C: {
        Vec2 v;
        v = fn_80177FE0();
        lbl_803EA69C->mUnknown1C = v.x;
        lbl_803EA69C->mUnknown20 = v.y;
        lbl_803EA69C->mFlags = 0;
        break;
    }
    case 0x92:
    case 0x95:
    case 0x97:
        lbl_803EA69C->mFlags |= 2;
        break;
    case 0xA2:
        lbl_803EA69C->mFlags |= 0x10;
        break;
    }
}

extern "C" int fn_8006E25C(void)
{
    unsigned int i;

    if (lbl_803EA368->mUnknownD94 & 0x10000) {
        return 0;
    }
    for (i = 0; i < 128; i++) {
        if (lbl_8030A868[i] == -1) {
            return i;
        }
    }
    return 0;
}

extern "C" void fn_8006E2A8(void)
{
    unsigned int i;

    for (i = 0; i < 128; i++) {
        if (lbl_8030A868[i] != -1) {
            fn_801F4130(lbl_8030A868[i]);
            lbl_8030A868[i] = -1;
        }
    }
}

extern "C" void fn_8006E308(Struct_8030A518Entry *pEntry)
{
    int slot = fn_8006E25C();

    if (pEntry->mFlags & 1) {
        lbl_8030A868[slot] = fn_8006C8A4(pEntry->mId, 0, pEntry->mUnknown12);
    } else {
        lbl_8030A868[slot] = fn_8006C8A4(pEntry->mId, &pEntry->mPos, pEntry->mUnknown12);
    }
}

extern "C" void fn_8006E370(Struct_8030A518Entry *pEntry, void *pStream)
{
    fn_80191068(pStream, pEntry->mId, 8);
    fn_80030490(pStream, &pEntry->mPos.mX, 8, 1.0f);
    fn_80191068(pStream, pEntry->mUnknown12, 8);
    fn_80191068(pStream, pEntry->mFlags, 1);
}

extern "C" void fn_8006E3F0(Struct_8030A518Entry *pEntry, void *pStream0, void *pStream1, void *pStream2,
                            void *pStream3, float unknown)
{
    float pos[2];
    Vector_80039F5C *pPos;

    pEntry->mId = fn_80190F18(pStream1, 8);
    pPos = &pEntry->mPos;
    pPos->mX = pPos->mY = pPos->mZ = 0.0f;
    fn_800300D4(pStream1, &pPos->mX, 8, 1.0f);
    pEntry->mUnknown12 = fn_80190F18(pStream1, 8);
    pEntry->mFlags = (unsigned char)fn_80190F18(pStream1, 1);

    fn_80190F18(pStream0, 8);
    fn_800300D4(pStream0, pos, 8, 1.0f);
    fn_80190F18(pStream0, 8);
    fn_80190F18(pStream0, 1);
    if (pStream2) {
        fn_80190F18(pStream2, 8);
        fn_800300D4(pStream2, pos, 8, 1.0f);
        fn_80190F18(pStream2, 8);
        fn_80190F18(pStream2, 1);
    }
    if (pStream3) {
        fn_80190F18(pStream3, 8);
        fn_800300D4(pStream3, pos, 8, 1.0f);
        fn_80190F18(pStream3, 8);
        fn_80190F18(pStream3, 1);
    }
}

extern "C" void fn_8006E548(void *pStream)
{
    unsigned int i;

    fn_80191068(pStream, lbl_803EA6A0->mCount, 4);
    for (i = 0; i < 12; i++) {
        fn_8006E370(&lbl_803EA6A0->mEntries[i], pStream);
    }
    fn_8006E6CC(lbl_803EA6A0);
}

extern "C" void fn_8006E5B4(void *pStream0, void *pStream1, void *pStream2, void *pStream3, float unknown)
{
    unsigned int count;
    unsigned int i;
    int frames;
    int half;
    int parity;
    Struct_8030A518Entry entry;

    count = (unsigned char)fn_80190F18(pStream1, 4);
    fn_80190F18(pStream0, 4);
    if (pStream2) {
        fn_80190F18(pStream2, 4);
    }
    if (pStream3) {
        fn_80190F18(pStream3, 4);
    }
    frames = lbl_803EA368->mUnknownD74 - lbl_803EA368->mUnknownD70;
    half = frames / 2;
    parity = frames % 2;
    for (i = 0; i < 12; i++) {
        fn_8006E3F0(&entry, pStream0, pStream1, pStream2, pStream3, unknown);
        if ((parity != lbl_803EC814 || half != lbl_803EA6A4) && i < count && fn_8002D060(lbl_803EA368)) {
            fn_8006E308(&entry);
        }
    }
    lbl_803EA6A4 = half;
    lbl_803EC814 = parity;
}

extern "C" void fn_8006E6CC(Struct_8030A518 *pList)
{
    if (pList) {
        memset(pList, 0, sizeof(pList->mEntries));
        pList->mCount = 0;
    }
}

extern "C" void fn_8006E710(void)
{
    static Struct_8030A518 sQueue;
    unsigned int i;

    lbl_803EA6A0 = &sQueue;
    for (i = 0; i < 128; i++) {
        lbl_8030A868[i] = -1;
    }
    fn_8006E6CC(lbl_803EA6A0);
}

extern "C" void fn_8006E760(void)
{
    fn_8006E6CC(lbl_803EA6A0);
    lbl_803EA6A0 = 0;
}

extern "C" void fn_8006E78C(void)
{
    fn_80030ACC(fn_8006E548, fn_8006E5B4, fn_8006E7CC(), "Sounds");
}

extern "C" int fn_8006E7CC(void)
{
    return 400;
}

extern "C" void fn_8006E7D4(Struct_8030A518Entry *pEntry)
{
    if (fn_8002D0AC(lbl_803EA368) && lbl_803EA6A0->mCount < 12) {
        lbl_803EA6A0->mEntries[lbl_803EA6A0->mCount] = *pEntry;
        if (fn_801784C4()) {
            lbl_803EA6A0->mEntries[lbl_803EA6A0->mCount].mPos.mX = -lbl_803EA6A0->mEntries[lbl_803EA6A0->mCount].mPos.mX;
            lbl_803EA6A0->mEntries[lbl_803EA6A0->mCount].mPos.mY = -lbl_803EA6A0->mEntries[lbl_803EA6A0->mCount].mPos.mY;
        }
        lbl_803EA6A0->mCount++;
    }
}

extern "C" void fn_8006E89C(int id, Vector_80039F5C *pPos, unsigned char unknown)
{
    Struct_8030A518Entry entry;

    if (id == 5 || id == 0x3E || (id >= 0x72 && id <= 0x90)) {
        return;
    }
    entry.mId = id;
    entry.mUnknown12 = unknown;
    entry.mFlags = 0;
    if (pPos) {
        entry.mPos.mX = pPos->mX;
        entry.mPos.mY = pPos->mY;
        entry.mPos.mZ = pPos->mZ;
    } else {
        entry.mFlags = 1;
    }
    fn_8006E7D4(&entry);
}

extern "C" void fn_8006E918(void)
{
    lbl_803EA6A4 = -1;
}

extern "C" void fn_8006E924(int unknown)
{
    Struct_803EA368 *p = lbl_803EA368;
    int rate;
    unsigned int i;

    if (!fn_8002D060(p)) {
        fn_8006E2A8();
        return;
    }
    if (p->mUnknownD94 & 0x10000) {
        return;
    }
    rate = abs(p->mUnknownD88);
    if (rate != 0) {
        if (rate < 10) {
            rate = 10;
        }
        rate *= 4096;
        rate /= 60;
    }
    for (i = 0; i < 128; i++) {
        if (lbl_8030A868[i] != -1) {
            if (fn_801F41A0(lbl_8030A868[i])) {
                lbl_8030A868[i] = -1;
            } else {
                fn_801F4314(lbl_8030A868[i], rate);
            }
        }
    }
}

extern "C" void fn_8006EA04(unsigned int index, unsigned int value)
{
    switch (index) {
    case 0:
        fn_801F4AEC(value ? 2 : 1, 0);
        break;
    case 1:
        if (value > 100) {
            value = 100;
        }
        value = value > 50 ? (value - 50) * (100 - lbl_803EA6A8[index]) / 50 + lbl_803EA6A8[index]
                           : value * lbl_803EA6A8[index] / 50;
        fn_8006D684(0, value);
        fn_8006D684(1, value);
        fn_8006BDD8(value * 99 / 100);
        fn_8006F344(value * 83 / 100);
        break;
    case 2:
        if (value > 100) {
            value = 100;
        }
        value = value > 50 ? (value - 50) * (100 - lbl_803EA6A8[index]) / 50 + lbl_803EA6A8[index]
                           : value * lbl_803EA6A8[index] / 50;
        value = value * 75 / 100;
        fn_80072C54(value);
        fn_8006D684(8, value);
        break;
    case 3:
        if (value > 100) {
            value = 100;
        }
        value = value > 50 ? (value - 50) * (100 - lbl_803EA6A8[index]) / 50 + lbl_803EA6A8[index]
                           : value * lbl_803EA6A8[index] / 50;
        value = value * 95 / 100;
        fn_8006D684(4, value);
        fn_8006D684(5, value);
        break;
    }
}

extern "C" void fn_8006EC24(void)
{
    unsigned int values[4];
    unsigned int i;

    values[0] = fn_8007F828(11);
    values[1] = (unsigned char)(fn_8007F828(4) * 10);
    values[2] = (unsigned char)(fn_8007F828(5) * 10);
    values[3] = (unsigned char)(fn_8007F828(3) * 10);
    for (i = 0; i < 4; i++) {
        fn_8006EA04(i, values[i]);
    }
}

extern "C" void fn_8006ECB4(Struct_8006CCD0 *pEvent)
{
    if (!fn_800BA6F8() && fn_800744A8()) {
        if (fn_8017F584() == 11 && fn_801568F0() <= 4) {
            switch (pEvent->mType) {
            case 0x85:
                fn_80074684(pEvent->mUnknown10.mValue, pEvent->mUnknown14);
                break;
            case 0x86:
                fn_800746E0();
                break;
            case 0x88:
                fn_80074788();
                break;
            case 0x87:
                fn_80074734();
                break;
            case 0x80:
                fn_80073620(pEvent->mUnknown10.mValue, pEvent->mUnknown0, pEvent->mUnknown18);
                break;
            case 0x81:
                fn_8007371C();
                break;
            case 0x82:
                fn_80073764();
                break;
            }
        } else {
            if (fn_800744B8()) {
                switch (pEvent->mType) {
                case 0x73:
                    lbl_803EA6B0 = 0;
                    lbl_803EA6B1 = 0;
                    fn_80077258();
                    break;
                case 0x75:
                    fn_8007732C(fn_80178348());
                    break;
                case 0x78:
                    if (!lbl_803EA6B1) {
                        fn_80077488();
                        lbl_803EA6B1 = 1;
                    }
                    break;
                case 0x77:
                    if (!lbl_803EA6B0) {
                        fn_8007753C();
                        lbl_803EA6B0 = 1;
                    }
                    break;
                case 0x2A: {
                    unsigned char kind = fn_8009BCE8(&pEvent->mUnknown0)->mpState->mId;
                    if (kind != 0x3A && kind != 0x10 && !(fn_8006F0D8() & 8)) {
                        fn_80076DAC(pEvent->mUnknown0);
                        fn_8006F0B8(0x40);
                    }
                    break;
                }
                case 0x68:
                    fn_80074CBC();
                    break;
                case 0x62:
                    fn_80074E90(pEvent->mUnknown0);
                    fn_80074E08();
                    break;
                case 0x27:
                    fn_80074F28(pEvent->mUnknown0);
                    fn_80074EA0();
                    break;
                case 0x2D:
                    fn_80074DF8(pEvent->mUnknown0);
                    fn_80074D70();
                    break;
                case 0x36:
                    fn_800747DC(pEvent->mUnknown0);
                    break;
                case 0x37:
                    fn_80074864(pEvent->mUnknown0);
                    break;
                case 0x38:
                    fn_800748EC(pEvent->mUnknown0);
                    break;
                case 0x39:
                    fn_80074974(pEvent->mUnknown0);
                    break;
                case 0x3A:
                    fn_80074A14(pEvent->mUnknown0);
                    break;
                case 0x3B:
                    fn_80074AB4(pEvent->mUnknown0);
                    break;
                case 0x3C:
                    fn_80074B54(pEvent->mUnknown0);
                    break;
                case 0x3D:
                    fn_80074C08(pEvent->mUnknown0);
                    break;
                case 0x61:
                    if (pEvent->mUnknown10.mValue == 0x22) {
                        fn_80074A14(pEvent->mUnknown0);
                    } else if (pEvent->mUnknown10.mValue == 0x23) {
                        fn_80074A14(pEvent->mUnknown0);
                    } else if (pEvent->mUnknown10.mValue == 0x2B) {
                        fn_80074974(pEvent->mUnknown0);
                    }
                    break;
                case 0x2F:
                    fn_80075058(pEvent->mUnknown0);
                    fn_80074F38(&pEvent->mPosition);
                    break;
                case 0x65:
                    fn_800750F0(pEvent->mUnknown10.mValue);
                    fn_80075188(pEvent->mUnknown14);
                    if (fn_802372EC(1, 2)) {
                        fn_80075068();
                    } else {
                        fn_80075100();
                    }
                    break;
                case 0x5F:
                    fn_80076D9C(pEvent->mUnknown0);
                    break;
                case 0x7C:
                    fn_80076228();
                    break;
                }
            }
            switch (pEvent->mType) {
            case 0x80:
                fn_80073620(pEvent->mUnknown10.mValue, pEvent->mUnknown0, pEvent->mUnknown18);
                break;
            case 0x81:
                fn_8007371C();
                break;
            case 0x82:
                fn_80073764();
                break;
            case 0x6B:
                fn_80076DB4(pEvent->mUnknown10.mValue, pEvent->mUnknown0, pEvent->mUnknown18, pEvent->mUnknown14);
                break;
            case 0x6C:
                fn_80076EA4(pEvent->mUnknown10.mValue);
                break;
            case 0x6D:
                fn_80076EE8(pEvent->mUnknown10.mValue);
                break;
            }
        }
    }
    if (pEvent->mType == 0x84) {
        fn_80074358(0);
        fn_80074358(1);
        fn_80074358(2);
    }
}

extern "C" void fn_8006F0B8(int flags)
{
    lbl_803EA6AC |= flags;
}

extern "C" void fn_8006F0C8(int flags)
{
    lbl_803EA6AC &= ~flags;
}

extern "C" int fn_8006F0D8(void)
{
    return lbl_803EA6AC;
}

