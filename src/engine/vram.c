/*
 * VRAM block table: at start-up the VRAM module allocates a table with one 28-byte entry per block
 * of video memory the game may hand out, marks every entry free, and frees the table at shutdown.
 */
#include "engine/vram.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"

/* 28-byte pool entry; only the byte at +8 is written here. */
typedef struct VramBlock_t {
    unsigned char mUnknown0[8];
    unsigned char mUnknown8;
    unsigned char mUnknown9[19];
} VramBlock_t;

static unsigned short _Vram_MaxBlocks = 0;
static VramBlock_t *_Vram_Blocks = 0;
static int _Vram_NextHandle = -1;
static unsigned char _Vram_ModuleActive = 0;

int VramInit(VramInitBlock_t *pDesc)
{
    int err = 0;
    unsigned int i;

    if (_Vram_ModuleActive == 0) {
        _Vram_MaxBlocks = pDesc->mUnknown0;
        _Vram_NextHandle = err;
        _Vram_Blocks = fn_801D2BB0(1, _Vram_MaxBlocks * sizeof(VramBlock_t), 0, 0);
        if (_Vram_Blocks == 0) {
            err = fn_801F7C88();
        } else {
            for (i = 0; i < _Vram_MaxBlocks; i++) {
                _Vram_Blocks[i].mUnknown8 = 0xFF;
            }
            _Vram_ModuleActive = 1;
        }
    } else {
        err = 0x80001;
    }
    fn_801F7BD4(err);
    return err;
}

int VramShutdown(void)
{
    int err = 0;

    if (_Vram_ModuleActive) {
        _Vram_NextHandle = -1;
        _Vram_MaxBlocks = 0;
        fn_801D2BD0(_Vram_Blocks);
        _Vram_ModuleActive = 0;
        _Vram_Blocks = 0;
    } else {
        err = 0x80002;
    }
    fn_801F7BD4(err);
    return err;
}
