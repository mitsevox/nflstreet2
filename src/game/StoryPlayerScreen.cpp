/* Story mode player screen: shows the story player's 3D preview model in the
   team's colours and handles the screen's messages for accepting, reverting
   and saving the player's edits in the profile database. */

#include "game/Object_8007A334.h"
#include "game/cu_8002ACB4.h"
#include "game/StoryPlayerScreen.h"
#include "game/fn_8018BE68.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801FCE10.h"

struct StoryModelLayout_t {
    float mPosition[3];
    float mScale;
    int mUnknown16;
};

struct StoryPlayerMsgExtra_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

union StoryPlayerMsgWord_t {
    int *mpId;
    int mValue;
};

struct StoryPlayerMsgArgs_t {
    StoryPlayerMsgWord_t mUnknown0;
    StoryPlayerMsgExtra_t *mpUnknown4;
};

extern "C" {
void fn_80022398(void);
void fn_800223C0(void);
void fn_800223E4(int index, float x, float y, float z);
void fn_8002248C(int index, unsigned char value);
void fn_800224A4(int index, float angle);
void fn_8002251C(int index, unsigned char value);
void fn_80022534(int index, float scale);
void fn_80022580(int index, int a, int b);
void fn_80022680(int index, int a, int b);
void fn_80022730(int index, int value);
void fn_80061DDC(void);
int fn_800841AC(Object_8007A334 *pObject);
int fn_800841D8(Object_8007A334 *pObject);
int fn_80084204(Object_8007A334 *pObject);
int fn_80183950(void);
void fn_80185264(unsigned char value);
unsigned char fn_8018526C(void);
unsigned char fn_8018527C(void);
void fn_80188CBC(int index, int a, int b, int c, const unsigned char *pColor);
void fn_8018BF3C(void);
int fn_8018C0E8(int a, int *p);
void fn_8018C48C(int tag);
int fn_8018D780(int a);
int fn_8018D890(int a, int b);
void fn_8018D8EC(int a, int b);
void fn_8018DCBC(int a);
int fn_8018DD04(int a);
void fn_8018DD4C(int a, int b, int c);
int fn_8018E874(int a, int b);
void fn_8018E8B0(int a, int b, int c);
int fn_8022F358(int index);
int fn_8022F384(int a);
int fn_8022F3D4(int a);
int fn_8022F4BC(void);

static StoryModelLayout_t _StoryPlayerScreen_ModelLayout = {{330.0f, 290.0f, 7.0f}, 1.0f, 14};
static unsigned char _StoryPlayerScreen_bActive = 0;
static int _StoryPlayerScreen_iLoadResult;
static int _StoryPlayerScreen_iPlayerId;
static signed char _StoryPlayerScreen_iProfile;
static unsigned char _StoryPlayerScreen_bSavedFlag;

void StoryPlayerScreenCopyToSlot8(void)
{
    int a;
    int b;
    int handle = fn_8022F3D4(fn_8022F358(_StoryPlayerScreen_iProfile));
    void *p1;
    void *p2;

    fn_801FCE10(0, "use \x8c select 'PXSP' into \x85 and 'DIGP' into \x85 from 'YPRC' where 'DIOP' = \x82\n",
                handle, &a, &b, 0x7FF4);
    fn_801FCE10(0, "use \x8c update 'YPRC' set 'PXSP' = \x85 where 'DIGP' = \x82\n", handle, 8, b);
    p1 = fn_801D2B7C(0x20000, 0, 0);
    p2 = fn_801D2B7C(0x400, 0, 0);
    fn_801FCE10(0, "use \x8c select 'XTPP' into \x89 and 'LPPP' into \x89 from 'PPRC' where 'PXSP' = \x85\n",
                handle, p1, p2, a);
    fn_801FCE10(0, "use \x8c update 'PPRC' set 'XTPP' = \x89 and 'LPPP' = \x89 where 'PXSP' = \x85\n", handle,
                p1, p2, 8);
    fn_801D2BD0(p2);
    fn_801D2BD0(p1);
}

void StoryPlayerScreenLoadModel(void)
{
    Result_8018BE68 result;

    _StoryPlayerScreen_iLoadResult = fn_8018BE68(_StoryPlayerScreen_iProfile, 1, &result);
    _StoryPlayerScreen_iPlayerId = result.mUnknown0;
    fn_80022680(0, result.mUnknown0, 1);
}

void StoryPlayerScreenAccept(void)
{
    fn_80185264(1);
    fn_8002ADE0(_StoryPlayerScreen_iProfile, _StoryPlayerScreen_iPlayerId);
}

void StoryPlayerScreenMarkChanged(int enable)
{
    if (enable && fn_8018527C()) {
        fn_8018E8B0(_StoryPlayerScreen_iProfile, 0, 1);
    }
}

void StoryPlayerScreenRevert(void)
{
    Result_8018BE68 result;
    int handle;

    fn_80185264(_StoryPlayerScreen_bSavedFlag);
    handle = fn_8018D890(_StoryPlayerScreen_iProfile, 0);
    if (fn_8018DD04(handle) > 0) {
        fn_8018DCBC(handle);
    }
    fn_8018BECC(_StoryPlayerScreen_iProfile, 0, &result);
    fn_8018DD4C(handle, result.mUnknown0, 1);
    fn_8018D8EC(_StoryPlayerScreen_iProfile, handle);
    fn_8018C48C(0x54415453);
    StoryPlayerScreenCopyToSlot8();
    StoryPlayerScreenLoadModel();
}

void StoryPlayerScreenEnter(int *pId)
{
    fn_80061DDC();
    if (_StoryPlayerScreen_bActive == 0) {
        _StoryPlayerScreen_bActive = 1;
        _StoryPlayerScreen_iProfile = fn_8022F384(fn_8022F4BC());
        fn_80022398();
        fn_800223E4(0, _StoryPlayerScreen_ModelLayout.mPosition[0], _StoryPlayerScreen_ModelLayout.mPosition[1], _StoryPlayerScreen_ModelLayout.mPosition[2]);
        fn_800224A4(0, 0.0f);
        fn_80022534(0, _StoryPlayerScreen_ModelLayout.mScale);
        fn_8002248C(0, 0);
        fn_8002251C(0, 0);
        fn_80022730(0, _StoryPlayerScreen_ModelLayout.mUnknown16);
        fn_80022580(0, 82, 0);
        StoryPlayerScreenLoadModel();
        _StoryPlayerScreen_bSavedFlag = fn_8018526C();
        if (fn_8018C0E8(_StoryPlayerScreen_iProfile, pId)) {
            Object_8007A334 cursor;
            fn_80083E40(&cursor, 0, 0x54415453);
            fn_80084034(&cursor, *pId, 0);
            if (!fn_80084438(&cursor)) {
                unsigned char values[3];
                values[0] = fn_800841AC(&cursor);
                values[1] = fn_800841D8(&cursor);
                values[2] = fn_80084204(&cursor);
                fn_80188CBC(0, 4, fn_80084158(&cursor), 172, values);
                fn_80188CBC(1, 4, fn_80084158(&cursor), 172, values);
            }
            fn_80083F68(&cursor);
        } else {
            *pId = 0;
        }
    }
}

void StoryPlayerScreenExit(void)
{
    if (_StoryPlayerScreen_bActive) {
        fn_8002ADAC();
        fn_800223C0();
        if (fn_80183950() == 0) {
            fn_8018C48C(0x54415453);
        }
        fn_80185264(_StoryPlayerScreen_bSavedFlag);
        _StoryPlayerScreen_bActive = 0;
    }
}

int StoryPlayerScreenCheckFlags(int which)
{
    int result = 1;

    switch (which) {
    case 0:
        if (fn_8018E874(_StoryPlayerScreen_iProfile, 0) == 0) {
            result = 0;
        }
        break;
    case 1:
        if (fn_8018E874(_StoryPlayerScreen_iProfile, 1) == 0 && fn_8018D780(_StoryPlayerScreen_iProfile) != 0) {
            result = 0;
        }
        break;
    }
    return result;
}

void StoryPlayerScreenIgnore(int a, int b, int c) {}

void StoryPlayerScreenSave(void)
{
    int active = fn_8018E874(_StoryPlayerScreen_iProfile, 1);

    fn_8018BF3C();
    if (active) {
        fn_8018E8B0(_StoryPlayerScreen_iProfile, 1, 1);
    }
}

void StoryPlayerScreenConfirm(int which)
{
    switch (which) {
    case 0:
        StoryPlayerScreenAccept();
        break;
    case 1:
        if (fn_8018E874(_StoryPlayerScreen_iProfile, 1) == 0) {
            StoryPlayerScreenRevert();
            fn_8018E8B0(_StoryPlayerScreen_iProfile, 1, 1);
        }
        break;
    }
}

unsigned char StoryPlayerScreenIsActive(void)
{
    return _StoryPlayerScreen_bActive;
}

int StoryPlayerScreenMsg(unsigned int id, StoryPlayerMsgArgs_t *pBlock, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        StoryPlayerScreenEnter(pBlock->mUnknown0.mpId);
        break;
    case 0x80000002:
        StoryPlayerScreenExit();
        break;
    case 0x80000003:
        if (StoryPlayerScreenCheckFlags(pBlock->mUnknown0.mValue)) {
            *pResult = 1;
        } else {
            *pResult = 0;
        }
        break;
    case 0x80000004:
        StoryPlayerScreenIgnore(pBlock->mUnknown0.mValue, pBlock->mpUnknown4->mUnknown8, pBlock->mpUnknown4->mUnknown4);
        break;
    case 0x80000005:
        StoryPlayerScreenSave();
        break;
    case 0x80000006:
        StoryPlayerScreenConfirm(pBlock->mUnknown0.mValue);
        break;
    case 0x80000007: {
        int enable = 0;
        if (pBlock->mUnknown0.mValue) {
            enable = 1;
        }
        StoryPlayerScreenMarkChanged(enable);
        break;
    }
    default:
        return 0;
    }
    return 1;
}
}
