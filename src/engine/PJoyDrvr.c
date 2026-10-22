#include "engine/periph.h"

/* Per-port pad state kept in the low-level driver data block (16 bytes). */
typedef struct JoyData_801E1D44 {
    short mPort;
    unsigned short mUnknown02;
    int mUnknown04;
    char mPad08[5];
    unsigned char mUnknown0D[1];
    unsigned char mUnknown0E[1];
    char mPad0F;
} JoyData_801E1D44;

extern int lbl_8039ADE4[4];
extern char lbl_803E92CC[0x30];

void *fn_801C1F94();
void *fn_801C1FBC();
int fn_801D34D0(void *p, unsigned int size, int value, int flags);
int fn_8025D574(unsigned int port);
void *fn_801E1D04(unsigned int port);
unsigned long fn_801E194C(void);
void fn_8024734C(void *pStatus);
void fn_802465BC(void *pStatus);
void fn_802476F8(int port, int command);
void fn_802857D8(void);

int fn_801E1D44(Device_801E12F8 *pDevice, unsigned char *pPort)
{
    JoyData_801E1D44 *pJoy;
    unsigned char port;
    int status;
    int result = 0;
    unsigned int i;

    fn_801D34D0(lbl_8039ADE4, sizeof(lbl_8039ADE4), 0, 1);
    port = *pPort;
    status = fn_8025D574(port);
    if (status != 8 && status != 0x80 && status != 0x40) {
        pJoy = fn_801E1D04(port);
        fn_801C1F94(pJoy, 0, sizeof(JoyData_801E1D44));
        pJoy->mPort = port;
        pJoy->mUnknown02 = 0;
        pJoy->mUnknown04 = 0;
        for (i = 0; i < 1; i++) {
            pJoy->mUnknown0D[i] = 0xFF;
            pJoy->mUnknown0E[i] = 0;
        }
        pDevice->mpUnknown08 = pJoy;
        pDevice->mStatus = 1;
        pDevice->mType = 0;
        pDevice->mUnknown14 = sizeof(JoyData_801E1D44);
        pDevice->mUnknown16 = 4;
        return 1;
    }
    pDevice->mStatus = 0;
    return result;
}

int fn_801E1E34(Device_801E12F8 *pDevice)
{
    pDevice->mpUnknown08 = 0;
    pDevice->mStatus = 0;
    pDevice->mType = 0;
    return 1;
}

int fn_801E25DC(Device_801E12F8 *pDevice, void *pBuffer)
{
    int result = 0;

    if ((unsigned int)pDevice->mStatus <= 1) {
        fn_801D34D0(pDevice->mpData, fn_801E194C(), 0, 4);
    } else {
        result = 1;
        fn_801C1FBC(pBuffer, pDevice->mpData, fn_801E194C());
    }
    return result;
}

int fn_801E2658(Device_801E12F8 *pDevice, unsigned char *pBuffer)
{
    JoyData_801E1D44 *pJoy = pDevice->mpUnknown08;
    int result = 0;
    short port = pJoy->mPort;

    if (pDevice->mStatus != 0) {
        if (pDevice->mType & 0x200) {
            pJoy->mUnknown0E[0] = pBuffer[9] != 0 ? pBuffer[9] : pBuffer[8];
            if (pJoy->mUnknown0E[0] != 0) {
                lbl_8039ADE4[port] = 1;
            } else {
                lbl_8039ADE4[port] = 0;
            }
            fn_802476F8(port, lbl_8039ADE4[port]);
        }
        result = 1;
    }
    return result;
}

void fn_801E26FC(void)
{
    fn_801D34D0(lbl_803E92CC, sizeof(lbl_803E92CC), 0, 1);
    fn_8024734C(lbl_803E92CC);
    fn_802465BC(lbl_803E92CC);
    fn_802857D8();
}
