/* Menu message routing: the callback the menu system calls for every screen
   message, which passes it to the handler of the screen's group; the handlers
   of the tutorial popup screens; and the character set a text entry box
   offers. */

#include "game/PauseMenu.h"
#include "game/cu_80181330.h"
#include "game/fn_801C3284.h"

extern "C" {
int fn_8000F870(int module, unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int MsgStreetEventDispatch(int group, unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int fn_8001D0F4(int group, unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int fn_8001D180(int group, unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int MsgMemCardDispatch(int group, unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int MsgTeamDispatch(int group, unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int MsgOptionsDispatch(int group, unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int fn_80059664(int group, unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int PopupScreenMsg(int kind, int id, void *pArgs, int c, int *pResult);
int fn_8017F6A8(int group, unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
int fn_8017F90C(unsigned int id, Arg_8018399C *pArgs, int count, int *pResult);
void fn_800AE65C(void);
void fn_800AE988(void);
int TutorialScreen13Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen12Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen2Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen1Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen8Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen5Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen15Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen10Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen11Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen7Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen9Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen14Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen6Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen4Msg(int id, void *pArgs, int count, int *pResult);
int TutorialScreen0Msg(int id, void *pArgs, int count, int *pResult);
}

/* Copies the character list for the given type into pText and returns the
   list's length, limited to length. */
extern "C" int TextEntryGetCharSet(int type, char *pText, int length)
{
    unsigned int count;

    fn_801C3284(pText, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ", length);
    count = 63;
    switch (type) {
    case 0:
    case 0x204:
        fn_801C3284(pText, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ", length);
        count = 63;
        break;
    case 0x201:
        fn_801C3284(pText, "1234567890", length);
        count = 10;
        break;
    case 1:
    case 2:
        fn_801C3284(pText, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789. ", length);
        count = 64;
        break;
    }
    if (count > length) {
        count = length;
    }
    return count;
}

extern "C" int PopupScreen20Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        break;
    case 0x80000002:
        PauseRequestClose();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" int TutorialScreenMsg(int kind, int id, void *pArgs, int count, int *pResult)
{
    switch (kind) {
    case 0:
        return TutorialScreen0Msg(id, pArgs, count, pResult);
    case 1:
        return TutorialScreen1Msg(id, pArgs, count, pResult);
    case 2:
        return TutorialScreen2Msg(id, pArgs, count, pResult);
    case 11:
        return TutorialScreen11Msg(id, pArgs, count, pResult);
    case 10:
        return TutorialScreen10Msg(id, pArgs, count, pResult);
    case 13:
        return TutorialScreen13Msg(id, pArgs, count, pResult);
    case 12:
        return TutorialScreen12Msg(id, pArgs, count, pResult);
    case 7:
        return TutorialScreen7Msg(id, pArgs, count, pResult);
    case 9:
        return TutorialScreen9Msg(id, pArgs, count, pResult);
    case 8:
        return TutorialScreen8Msg(id, pArgs, count, pResult);
    case 6:
        return TutorialScreen6Msg(id, pArgs, count, pResult);
    case 5:
        return TutorialScreen5Msg(id, pArgs, count, pResult);
    case 4:
        return TutorialScreen4Msg(id, pArgs, count, pResult);
    case 14:
        return TutorialScreen14Msg(id, pArgs, count, pResult);
    case 15:
        return TutorialScreen15Msg(id, pArgs, count, pResult);
    }
    return 0;
}

extern "C" void TutorialScreen13Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" void TutorialScreen13Enter(void)
{
    fn_800AE65C();
}

extern "C" int TutorialScreen13Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        TutorialScreen13Enter();
        break;
    case 0x80000002:
        TutorialScreen13Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen12Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" int TutorialScreen12Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        TutorialScreen12Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen2Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" int TutorialScreen2Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        TutorialScreen2Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen1Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" int TutorialScreen1Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        TutorialScreen1Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen8Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" int TutorialScreen8Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        TutorialScreen8Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen5Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" int TutorialScreen5Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        TutorialScreen5Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen15Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" int TutorialScreen15Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        break;
    case 0x80000002:
        TutorialScreen15Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen10Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" void TutorialScreen10Enter(void)
{
    fn_800AE65C();
}

extern "C" int TutorialScreen10Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        TutorialScreen10Enter();
        break;
    case 0x80000002:
        TutorialScreen10Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen11Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" void TutorialScreen11Enter(void)
{
    fn_800AE65C();
}

extern "C" int TutorialScreen11Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        TutorialScreen11Enter();
        break;
    case 0x80000002:
        TutorialScreen11Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen7Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" int TutorialScreen7Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        TutorialScreen7Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen9Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" int TutorialScreen9Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        TutorialScreen9Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen14Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" int TutorialScreen14Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        TutorialScreen14Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen6Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" int TutorialScreen6Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        TutorialScreen6Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen4Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" int TutorialScreen4Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        TutorialScreen4Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void TutorialScreen0Exit(void)
{
    PauseRequestClose();
    fn_800AE988();
}

extern "C" int TutorialScreen0Msg(int id, void *pArgs, int count, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_800AE65C();
        break;
    case 0x80000002:
        TutorialScreen0Exit();
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" void ScreenMsgDispatch(unsigned int id, int group, int screen, int count, Arg_8018399C *pArgs,
                            int *pResult)
{
    int handled = 0;

    switch (group) {
    case 0:
        handled = fn_8000F870(screen, id, pArgs, count, pResult);
        break;
    case 13:
        handled = MsgStreetEventDispatch(screen, id, pArgs, count, pResult);
        break;
    case 11:
        handled = fn_8001D180(screen, id, pArgs, count, pResult);
        break;
    case 6:
        handled = MsgMemCardDispatch(screen, id, pArgs, count, pResult);
        break;
    case 3:
        handled = fn_80059664(screen, id, pArgs, count, pResult);
        break;
    case 1:
        handled = PopupScreenMsg(screen, id, pArgs, count, pResult);
        break;
    case 5:
        handled = MsgOptionsDispatch(screen, id, pArgs, count, pResult);
        break;
    case 2:
        handled = fn_8017F6A8(screen, id, pArgs, count, pResult);
        break;
    case 7:
        handled = TutorialScreenMsg(screen, id, pArgs, count, pResult);
        break;
    case 12:
        handled = fn_8001D0F4(screen, id, pArgs, count, pResult);
        break;
    case 8:
        handled = MsgTeamDispatch(screen, id, pArgs, count, pResult);
        break;
    }
    if (handled == 0) {
        fn_8017F90C(id, pArgs, count, pResult);
    }
}
