/* Team logos: copies the palette of a team's logo texture, recolors it
   with the team's three colors and writes it into one of two logo slots,
   holding a request until the texture is loaded. */

#include "game/FMCAPPORT.h"
#include "game/DbCursor.h"
#include "game/fn_801C1F94.h"

#include <string.h>
#include <dolphin/gx/GXManage.h>

/* Record returned by fn_80221BAC. */
struct TexPaletteInfo_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    void *mpUnknown20;
};

/* Local block passed to PlaDynClutApplyColors by TeamLogoTintPalette. */
struct PaletteDesc_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    int mUnknown4;
    char *mpUnknown8;
};

/* One pending entry, applied by TeamLogoUpdatePending once fn_80221BAC finds it. */
struct TeamLogoPending_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknown12[3];
};

extern "C" {
void fn_80083E1C(DbCursor *pObject, int a);
int fn_800841AC(DbCursor *pObject);
int fn_800841D8(DbCursor *pObject);
int fn_80084204(DbCursor *pObject);
void PlaDynClutApplyColors(PaletteDesc_t *pDesc, int id, FMCAPPORTText *pText);
void fn_801CE910(void);
void *fn_8021EA44(int index);
int fn_8021E2B4(void *pObject, int a, int b);
char *fn_80220BFC(int a, int b);
TexPaletteInfo_t *fn_80221BAC(void *pObject, int a, int b);
void DCStoreRange(char *p, int size);
}

static TeamLogoPending_t _TeamLogo_aPending[2];
static unsigned char _TeamLogo_bReady = 0;
static unsigned short _TeamLogo_aSlots[2] = {2, 3};

extern "C" {
int TeamLogoGetSlot(int index);

void TeamLogoFlushPalette(int id, char *p)
{
    DCStoreRange(p, 0x200);
    GXFlush();
}

void TeamLogoFirstInit(void)
{
}

void TeamLogoTintPalette(int id, int a, int b, int c, const unsigned char *pColor)
{
    FMCAPPORTText text;
    PaletteDesc_t desc;
    char buffer[1024];
    TexPaletteInfo_t *pRecord;
    char *pDst;
    int count;
    int bytes;

    pRecord = fn_80221BAC(fn_8021EA44(1), a, b);
    count = 256;
    bytes = 4;
    desc.mUnknown0 = pRecord->mUnknown8;
    desc.mUnknown2 = pRecord->mUnknown16;
    if (pRecord->mUnknown8 != 1 && pRecord->mUnknown8 != 9) {
        count = 16;
    }
    if (pRecord->mUnknown16 != 6) {
        bytes = 2;
    }
    desc.mUnknown4 = count * bytes;
    memcpy(buffer, pRecord->mpUnknown20, desc.mUnknown4);
    desc.mpUnknown8 = buffer;
    fn_801C1F94(&text, 0, sizeof(text));
    text.mChars[20] = pColor[0];
    text.mChars[21] = pColor[1];
    text.mChars[22] = pColor[2];
    PlaDynClutApplyColors(&desc, c, &text);
    pDst = fn_80220BFC(5, id);
    fn_801CE910();
    memcpy(pDst, buffer, desc.mUnknown4);
    TeamLogoFlushPalette(id, pDst);
}

void TeamLogoTintMatchup(int a, int b)
{
    DbCursor cursor;
    unsigned char color0[3];
    unsigned char color1[3];
    void *pObject;
    int id0;
    int id1;

    pObject = fn_8021EA44(1);
    fn_80083E1C(&cursor, 0);
    fn_80084034(&cursor, a, 0);
    id0 = fn_80084158(&cursor);
    color0[0] = fn_800841AC(&cursor);
    color0[1] = fn_800841D8(&cursor);
    color0[2] = fn_80084204(&cursor);
    fn_80084034(&cursor, b, 0);
    id1 = fn_80084158(&cursor);
    color1[0] = fn_800841AC(&cursor);
    color1[1] = fn_800841D8(&cursor);
    color1[2] = fn_80084204(&cursor);
    fn_80083F68(&cursor);
    fn_8021E2B4(pObject, 4, id0);
    fn_8021E2B4(pObject, 4, id1);
    TeamLogoTintPalette(TeamLogoGetSlot(0), 4, id0, 0xAC, color0);
    TeamLogoTintPalette(TeamLogoGetSlot(1), 4, id1, 0xAC, color1);
}

void TeamLogoUpdatePending(void);

void TeamLogoRequestTint(int index, int a, int b, int c, const unsigned char *pColor)
{
    int i;

    for (i = 0; i < 3; i++) {
        _TeamLogo_aPending[index].mUnknown12[i] = pColor[i];
    }
    _TeamLogo_aPending[index].mUnknown0 = a;
    _TeamLogo_aPending[index].mUnknown8 = c;
    _TeamLogo_aPending[index].mUnknown4 = b;
    TeamLogoUpdatePending();
}

void TeamLogoUpdatePending(void)
{
    int i;

    if (!_TeamLogo_bReady) {
        return;
    }
    for (i = 0; i < 2; i++) {
        if (_TeamLogo_aPending[i].mUnknown4 != -1) {
            if (fn_80221BAC(fn_8021EA44(1), _TeamLogo_aPending[i].mUnknown0, _TeamLogo_aPending[i].mUnknown4)) {
                TeamLogoTintPalette(TeamLogoGetSlot(i), _TeamLogo_aPending[i].mUnknown0, _TeamLogo_aPending[i].mUnknown4, _TeamLogo_aPending[i].mUnknown8,
                            _TeamLogo_aPending[i].mUnknown12);
                _TeamLogo_aPending[i].mUnknown4 = -1;
            }
        }
    }
}

int TeamLogoGetSlot(int index)
{
    int result;

    if (index == -1) {
        result = -1;
    } else {
        result = _TeamLogo_aSlots[index];
    }
    return result;
}

int TeamLogoGetHandle(int index)
{
    int result;

    if (index == -1) {
        result = -1;
    } else {
        result = _TeamLogo_aSlots[index] | 0x50000;
    }
    return result;
}

void TeamLogoInit(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        fn_801C1F94(&_TeamLogo_aPending[i], 0, sizeof(TeamLogoPending_t));
        _TeamLogo_aPending[i].mUnknown4 = -1;
    }
    if (!_TeamLogo_bReady) {
        TeamLogoFirstInit();
        _TeamLogo_bReady = 1;
    }
}

void TeamLogoShutdown(void)
{
    _TeamLogo_bReady = 0;
}
}
