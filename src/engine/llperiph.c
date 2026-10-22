#include "engine/periph.h"
#include "game/fn_801D2B7C.h"

extern void *lbl_803ED664;

void fn_801CE234(void (*pCallback)(void));
void fn_80247134(void);
void fn_802856D8(void);
int fn_8025D574(unsigned int port);
int fn_801E1B08(unsigned char port);
int fn_801E1B94(void);
void fn_801E1C38(unsigned char port);
unsigned int fn_801E1D3C(void);

int fn_801E1A20(void *pData)
{
    fn_80247134();
    fn_802856D8();
    lbl_803ED664 = fn_801D2BB0(1, fn_801E1D3C() * 4, 0, 0);
    lbl_803ED660 = 4;
    fn_801E1AB4();
    fn_801E26FC();
    fn_801CE234(fn_801E26FC);
    return 0;
}

int fn_801E1A80(void)
{
    fn_801E1B94();
    fn_801D2BD0(lbl_803ED664);
    lbl_803ED664 = 0;
    return 0;
}

int fn_801E1AB4(void)
{
    unsigned char port;

    for (port = 0; port < lbl_803ED660; port++) {
        fn_801E1B08(port);
    }
    return 0;
}

int fn_801E1B08(unsigned char port)
{
    unsigned char i;
    unsigned char arg;

    for (i = 0; i < lbl_803ED648; i++) {
        arg = port;
        if (lbl_803ED64C[i].mpInit(&lbl_803ED658[port], &arg) == 1) {
            lbl_803ED658[port].mpDriver = &lbl_803ED64C[i];
            break;
        }
    }
    return 0;
}

int fn_801E1B94(void)
{
    unsigned char port;

    for (port = 0; port < lbl_803ED660; port++) {
        fn_801E1B08(port);
    }
    return 0;
}

void fn_801E1BE8(void)
{
    unsigned char port;

    for (port = 0; port < lbl_803ED660; port++) {
        fn_801E1C38(port);
    }
}

void fn_801E1C38(unsigned char port)
{
    int status;
    int type;

    status = fn_8025D574(port);
    if (status == 0x80) {
        return;
    }
    type = fn_801E19B4(port);
    if (status == 8) {
        if (lbl_803ED658[port].mStatus != 0 && !(type & 0x800)) {
            fn_801E1688(port);
            lbl_803ED658[port].mpDriver = 0;
            lbl_803ED658[port].mStatus = 0;
            lbl_803ED658[port].mType = 0;
        }
    } else if (lbl_803ED658[port].mStatus == 0) {
        fn_801E1B08(port);
    }
}

int fn_801E1CE0(unsigned int port)
{
    if (lbl_803ED658[port].mStatus == 0) {
        return 0;
    }
    return 1;
}

void *fn_801E1D04(unsigned int port)
{
    return (char *)lbl_803ED664 + fn_801E1D3C() * port;
}

unsigned int fn_801E1D3C(void)
{
    return 16;
}
