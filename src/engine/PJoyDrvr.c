/* Low-level GameCube controller driver of the peripheral library: probes and initializes a pad
   port, polls the pad each frame into the device's button and axis data, and drives the rumble
   motor. */

#include "engine/periph.h"
#include "dolphin/pad.h"
#include "dolphin/si.h"

/* Per-port pad state kept in the low-level driver data block (16 bytes). */
typedef struct PerJoyData_t {
    short mPort;
    unsigned short mUnknown02;
    int mUnknown04;
    int mUnknown08;
    unsigned char mUnknown0C;
    unsigned char mUnknown0D[1];
    unsigned char mUnknown0E[1];
    char mPad0F;
} PerJoyData_t;

extern int _PerJoy_aiMotorCommand[4];
extern PADStatus _PerJoy_aPadStatus[4];

void *memset();
void *memcpy();
int MemFill(void *p, unsigned int size, int value, int flags);
void *PerSystemGetLLDriverData(unsigned int port);
unsigned long PerSizeofPerDataT(void);
unsigned long PerGetDataSize(void);
int GetState_GFLink(int port);
void GBAFanServiceLink(void);

int _PerJoyDriverInit(PerDevice_t *pDevice, unsigned char *pPort)
{
    PerJoyData_t *pJoy;
    unsigned char port;
    int status;
    int result = 0;
    unsigned int i;

    MemFill(_PerJoy_aiMotorCommand, sizeof(_PerJoy_aiMotorCommand), 0, 1);
    port = *pPort;
    status = SIProbe(port);
    if (status != 8 && status != 0x80 && status != 0x40) {
        pJoy = PerSystemGetLLDriverData(port);
        memset(pJoy, 0, sizeof(PerJoyData_t));
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
        pDevice->mUnknown14 = sizeof(PerJoyData_t);
        pDevice->mUnknown16 = 4;
        return 1;
    }
    pDevice->mStatus = 0;
    return result;
}

int _PerJoyDriverShutdown(PerDevice_t *pDevice)
{
    pDevice->mpUnknown08 = 0;
    pDevice->mStatus = 0;
    pDevice->mType = 0;
    return 1;
}

// FAKEMATCH: the fill routine gets its prototype only here, after the init driver's unprototyped
// call (crclr cr1eq at 0x801E1DB0) and before this one (none).
void *memset(void *pDst, int value, unsigned long size);

int _PerJoyDriverPoll(PerDevice_t *pDevice, int (*pCounter)(unsigned int))
{
    PerJoyData_t *pJoy;
    PerData_t *pData;
    float stickX = 0.0f;
    float stickY = stickX;
    unsigned int type;
    unsigned int typeHi;
    unsigned int typeLo;
    short port;
    int state;
    unsigned int i;
    int j;

    type = PerGetDeviceTypeT(pDevice->mIndex);
    pJoy = pDevice->mpUnknown08;
    port = pJoy->mPort;
    typeHi = type >> 16;
    typeLo = type & 0xFFFF;
    state = pJoy->mUnknown04;
    if (_PerJoy_aPadStatus[port].err != PAD_ERR_NONE && _PerJoy_aPadStatus[port].err != PAD_ERR_TRANSFER) {
        state = 0;
        pJoy->mUnknown0C = 0;
    }
    memset((unsigned char *)pDevice->mpData + 8, 0, PerGetDataSize());
    for (j = 4; j < 8; j++) {
        ((signed char *)pDevice->mpData)[j + 8] = -0x80;
    }

    switch (state) {
    case 0:
        if (pJoy->mUnknown0C == 0) {
            int probe = SIProbe(port);
            if (probe != 0x80 && probe != 8 && probe != 0x40) {
                pJoy->mUnknown08 = probe;
                pJoy->mUnknown0C = 1;
            }
        }
        if (_PerJoy_aPadStatus[port].err == PAD_ERR_NO_CONTROLLER) {
            if (pJoy->mUnknown08 == RES_WIRELESS_LITE && GetState_GFLink(port) != 0) {
                pDevice->mStatus = 1;
                typeLo |= 0x800;
                state = 2;
                typeHi = 1;
                typeLo &= ~0x700;
            }
            if (state != 2) {
                PADReset(0x80000000 >> port);
                pJoy->mUnknown0C = 0;
                pDevice->mStatus = 0;
                typeHi = 0;
                typeLo = 0;
            }
        } else if (_PerJoy_aPadStatus[port].err == PAD_ERR_NONE) {
            pJoy->mUnknown0D[0] = 0;
            state = 1;
            pDevice->mStatus = 2;
            typeLo |= 0x200;
            typeHi = 1;
        } else {
            pDevice->mStatus = 0;
        }
        break;
    case 2:
        pData = pDevice->mpData;
        if (pCounter) {
            pData->mUnknown04 = pCounter(pDevice->mIndex);
        } else {
            pData->mUnknown04 = 0;
        }
        break;
    case 1:
        if (_PerJoy_aPadStatus[port].err == PAD_ERR_NONE) {
            unsigned short buttons = _PerJoy_aPadStatus[port].button;
            float x;
            float y;
            float sum;
            int xPositive;
            int yNegative;
            int axis;
            int value;
            signed char out;

            for (i = 0; i < Per_MaxButtons; i++) {
                if (i < pDevice->mUnknown14) {
                    unsigned int byte = Per_MaxAxis + (i >> 3);
                    unsigned int bit = i & 7;
                    unsigned int mask = 1 << i;
                    if ((buttons & mask) == 0) {
                        ((PerData_t *)pDevice->mpData)->mUnknown08[byte] &= ~Per_BtnMask[bit];
                    } else {
                        ((PerData_t *)pDevice->mpData)->mUnknown08[byte] |= Per_BtnMask[bit];
                    }
                } else {
                    unsigned int byte = Per_MaxAxis + (i >> 3);
                    unsigned int bit = i & 7;
                    ((PerData_t *)pDevice->mpData)->mUnknown08[byte] &= ~Per_BtnMask[bit];
                }
            }

            if (_PerJoy_aPadStatus[port].stickX < 0) {
                x = -_PerJoy_aPadStatus[port].stickX;
                xPositive = 0;
            } else {
                x = _PerJoy_aPadStatus[port].stickX;
                xPositive = 1;
            }
            if (_PerJoy_aPadStatus[port].stickY > 0) {
                y = _PerJoy_aPadStatus[port].stickY;
                yNegative = 0;
            } else {
                y = -_PerJoy_aPadStatus[port].stickY;
                yNegative = 1;
            }
            sum = x + y;
            if (sum > 0.0f) {
                if (x > y) {
                    float ratio = y / x;
                    stickX = sum * (1.0f / 70.0f);
                    stickY = ratio * stickX;
                } else {
                    float ratio = x / y;
                    stickY = sum * (1.0f / 70.0f);
                    stickX = ratio * stickY;
                }
            }
            if (stickX > 1.0f) {
                stickX = 1.0f;
            }
            if (stickY > 1.0f) {
                stickY = 1.0f;
            }
            out = (signed char)(stickX * (xPositive == 1 ? 127.0f : -127.0f));
            ((signed char *)pDevice->mpData)[8] = out;
            out = (signed char)(stickY * (yNegative == 1 ? 127.0f : -127.0f));
            ((signed char *)pDevice->mpData)[9] = out;

            axis = 2;
            value = (float)_PerJoy_aPadStatus[port].substickX * (127.0 / 29.0);
            out = (signed char)(value < -127 ? -127 : (value > 127 ? 127 : value));
            ((signed char *)pDevice->mpData)[axis + 8] = out;
            axis++;
            value = (float)-_PerJoy_aPadStatus[port].substickY * (127.0 / 29.0);
            out = (signed char)(value < -127 ? -127 : (value > 127 ? 127 : value));
            ((signed char *)pDevice->mpData)[axis + 8] = out;
            axis++;
            value = ((float)_PerJoy_aPadStatus[port].triggerLeft - 76.0f) * (127.0 / 70.0);
            out = (signed char)(value < -128 ? -128 : (value > 127 ? 127 : value));
            ((signed char *)pDevice->mpData)[axis + 8] = out;
            if (out > -120) {
                ((PerData_t *)pDevice->mpData)->mUnknown08[Per_MaxAxis] |= Per_BtnMask[6];
            }
            axis++;
            value = ((float)_PerJoy_aPadStatus[port].triggerRight - 76.0f) * (127.0 / 70.0);
            out = (signed char)(value < -128 ? -128 : (value > 127 ? 127 : value));
            ((signed char *)pDevice->mpData)[axis + 8] = out;
            if (out > -120) {
                ((PerData_t *)pDevice->mpData)->mUnknown08[Per_MaxAxis] |= Per_BtnMask[5];
            }
            axis++;
            out = 127;
            if (_PerJoy_aPadStatus[port].analogA == 0) {
                out = -128;
            }
            ((signed char *)pDevice->mpData)[axis + 8] = out;
            axis++;
            out = 127;
            if (_PerJoy_aPadStatus[port].analogB == 0) {
                out = -128;
            }
            ((signed char *)pDevice->mpData)[axis + 8] = out;
            pData = pDevice->mpData;
            if (pCounter) {
                pData->mUnknown04 = pCounter(pDevice->mIndex);
            } else {
                pData->mUnknown04 = 0;
            }
        }
        break;
    }
    pDevice->mType = (typeHi << 16) + (typeLo & 0xFFFF);
    pJoy->mUnknown04 = state;
    return 1;
}

int _PerJoyDriverGetData(PerDevice_t *pDevice, void *pBuffer)
{
    int result = 0;

    if ((unsigned int)pDevice->mStatus <= 1) {
        MemFill(pDevice->mpData, PerSizeofPerDataT(), 0, 4);
    } else {
        result = 1;
        memcpy(pBuffer, pDevice->mpData, PerSizeofPerDataT());
    }
    return result;
}

int _PerJoyDriverSendData(PerDevice_t *pDevice, unsigned char *pBuffer)
{
    PerJoyData_t *pJoy = pDevice->mpUnknown08;
    int result = 0;
    short port = pJoy->mPort;

    if (pDevice->mStatus != 0) {
        if (pDevice->mType & 0x200) {
            pJoy->mUnknown0E[0] = pBuffer[9] != 0 ? pBuffer[9] : pBuffer[8];
            if (pJoy->mUnknown0E[0] != 0) {
                _PerJoy_aiMotorCommand[port] = 1;
            } else {
                _PerJoy_aiMotorCommand[port] = 0;
            }
            PADControlMotor(port, _PerJoy_aiMotorCommand[port]);
        }
        result = 1;
    }
    return result;
}

void PerJoyDriverPollPADs(void)
{
    MemFill(_PerJoy_aPadStatus, sizeof(_PerJoy_aPadStatus), 0, 1);
    PADRead(_PerJoy_aPadStatus);
    PADClamp(_PerJoy_aPadStatus);
    GBAFanServiceLink();
}
