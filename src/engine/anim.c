/* Animation library core: starts and stops the animation module, keeps the
   stacks of game data that animation scripts hand to the game when they reach a
   game-defined opcode, and records which sequence file version is in use. */

#include "engine/cu_801B9F00.h"
#include "engine/animemot.h"
#include "engine/fn_801F7BD4.h"

typedef int (*AnimUserOpcodeCallback_t)(void *pUser, int op, unsigned int state);

extern unsigned char _Anim_ModuleActive;
extern AnimUserOpcodeCallback_t _Anim_pUserOpcodeCallback;
extern AnimUserOpcodeCallback_t _Anim_pUserOpcodeSkipCallback;
extern int _Anim_SeqVersion;
extern signed char _Anim_UserDataStackPosition;
extern signed char _Anim_UserStateStackPosition;
extern void *_Anim_pCurrentUserData[];
extern unsigned int _Anim_UserCallbackState[];

int _AnimDoUserOpcodeCallback(int op)
{
    return _Anim_pUserOpcodeCallback(_Anim_pCurrentUserData[_Anim_UserDataStackPosition], op, _Anim_UserCallbackState[_Anim_UserDataStackPosition]);
}

int _AnimDoUserOpcodeSkipCallback(int op)
{
    return _Anim_pUserOpcodeSkipCallback(0, op, 0);
}

void _AnimUserCallbackPushState(unsigned int state)
{
    _Anim_UserCallbackState[++_Anim_UserStateStackPosition] = state;
}

void _AnimUserCallbackPushInfo(void *pUser)
{
    _Anim_pCurrentUserData[++_Anim_UserDataStackPosition] = pUser;
}

void _AnimUserCallbackPopState(void)
{
    _Anim_UserStateStackPosition--;
}

void _AnimUserCallbackPopInfo(void)
{
    _Anim_UserDataStackPosition--;
}

int AnimInit(unsigned int mode)
{
    int err = 0;

    if (_Anim_ModuleActive == 0)
        _Anim_ModuleActive = 1;
    else
        err = 0x140001;
    _Anim_UserDataStackPosition = -1;
    _Anim_UserStateStackPosition = -1;
    AnimFileSetCustomRelocateFunc(0);
    switch (mode) {
    case 0:
        AnimFileSetRelocateBigFileFunc(AnimFileProcessBigFile);
        break;
    case 1:
    case 2:
        AnimFileSetRelocateBigFileFunc(AnimFileNewProcessBigFile);
        break;
    }
    _Anim_SeqVersion = mode;
    fn_801F7BD4(err);
    return err;
}

int AnimShutdown(void)
{
    int err = 0;

    if (_Anim_ModuleActive) {
        _Anim_pUserOpcodeCallback = 0;
        _Anim_ModuleActive = 0;
    } else {
        err = 0x140002;
    }
    fn_801F7BD4(err);
    return err;
}

void AnimInitHeader(AnimHeader_t *pList, unsigned short a, unsigned short b, unsigned short count)
{
    pList->mUnknown0 = a;
    pList->mUnknown2 = b;
    pList->mUnknown4 = count;
}

void AnimSetUserOpcodeCallbacks(AnimUserOpcodeCallback_t callback, AnimUserOpcodeCallback_t fallback)
{
    _Anim_pUserOpcodeCallback = callback;
    _Anim_pUserOpcodeSkipCallback = fallback;
}

int AnimGetSeqVersion(void)
{
    return _Anim_SeqVersion;
}
