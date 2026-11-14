/* Player save: prepares a player's record for a memory-card slot and writes it through the card stream table. */

#include "game/PlayerSave.h"
#include <string.h>
#include "game/fn_801D2B7C.h"

extern "C" {
void MemCardFilesResetSlot(int a, int b, int c);
void MemCardFilesRenameSlot(int a, int b, char *pBuf);
void MemCardFilesGetSlotName(int a, int b, char *pBuf, int size);
int PlayerRecordRead(int a, void *pBuffer);

static void *_PlayerSave_pBuffer = 0;
static void *_PlayerSave_pRecord = 0;

int PlayerSaveWrite(int target, SaveStreamOps_t *pOps)
{
    char stream[0x80];
    unsigned int done;
    int result;

    pOps->mpUnknown14(0x100);
    result = pOps->mpOpen(stream, 0x100, target, 0);
    if (result == 0) {
        result = pOps->mpWrite(stream, _PlayerSave_pBuffer, 0x100, &done);
    }
    if (result == 0) {
        result = pOps->mpClose(stream);
    } else {
        pOps->mpClose(stream);
    }
    return result;
}

int PlayerSaveOnSave(SaveRequest_t *pRequest, SaveStreamOps_t *pOps)
{
    int result;

    if (pRequest->mUnknown10) {
        result = PlayerSaveWrite(pRequest->mTarget, pOps);
    } else {
        result = PlayerSaveWrite(pRequest->mTarget, pOps);
    }
    return result;
}

int PlayerSaveOnLoad(SaveRequest_t *pRequest, SaveStreamOps_t *pOps)
{
    return 0xFFFF;
}

void PlayerSaveFree(void)
{
    if (_PlayerSave_pBuffer != 0) {
        fn_801D2BD0(_PlayerSave_pBuffer);
        _PlayerSave_pBuffer = 0;
    }
}

int PlayerSavePrepare(int a, int b)
{
    char name[32];
    int result;

    PlayerSaveFree();
    result = 0;
    _PlayerSave_pBuffer = fn_801D2B7C(0x100, 0, 0);
    if (_PlayerSave_pBuffer != 0) {
        memset(_PlayerSave_pBuffer, 0, 0x100);
        _PlayerSave_pRecord = _PlayerSave_pBuffer;
        result = PlayerRecordRead(b, _PlayerSave_pBuffer);
        if (result != 0) {
            MemCardFilesResetSlot(3, a, 0);
            MemCardFilesGetSlotName(2, a, name, 32);
            MemCardFilesRenameSlot(3, a, name);
        }
    }
    return result;
}
}
