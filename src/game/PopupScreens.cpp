/* Popup screens: routes the popup group's messages to their screen handlers,
   and handles the progressive-scan popup that switches the video mode. */

extern "C" {
int fn_80020C44(unsigned int id, void *pArgs, int c, int *pResult);
int fn_80020DC0(unsigned int id, void *pArgs, int c, int *pResult);
int fn_800211B4(unsigned int id, void *pArgs, int c, int *pResult);
int fn_800212C8(int id, void *pArgs, int c, int *pResult);
int fn_800217AC(unsigned int id, void *pArgs, int c, int *pResult);
int ProgressivePopupMsg(int id, int *pArgs, int c, int *pResult);
int PopupScreen20Msg(int id, void *pArgs, int c, int *pResult);
int fn_80186324(unsigned int id, void *pArgs, int c, int *pResult);
void fn_801CEB58(int a);
void fn_8023CFD0(int a);
}

static int _ProgressivePopup_bOn = 0;

extern "C" int ProgressivePopupMsg(int id, int *pArgs, int c, int *pResult)
{
    switch (id) {
    case 0x80000001:
        if (*pArgs == 1) {
            _ProgressivePopup_bOn = *pArgs;
            fn_8023CFD0(1);
            fn_801CEB58(1);
        } else {
            _ProgressivePopup_bOn = 0;
            fn_8023CFD0(0);
        }
        break;
    default:
        return 0;
    }
    return 1;
}

extern "C" int ProgressivePopupIsOn(void)
{
    return (unsigned char)_ProgressivePopup_bOn;
}

extern "C" int PopupScreenMsg(int kind, int id, void *pArgs, int c, int *pResult)
{
    switch (kind) {
    case 2:
        return fn_80186324(id, pArgs, c, pResult);
    case 4:
        return fn_800217AC(id, pArgs, c, pResult);
    case 1:
        return fn_800212C8(id, pArgs, c, pResult);
    case 6:
        return fn_800211B4(id, pArgs, c, pResult);
    case 11:
        return fn_80020DC0(id, pArgs, c, pResult);
    case 13:
        return fn_80020C44(id, pArgs, c, pResult);
    case 14:
        return ProgressivePopupMsg(id, (int *)pArgs, c, pResult);
    case 20:
        return PopupScreen20Msg(id, pArgs, c, pResult);
    }
    return 0;
}
