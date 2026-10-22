#ifndef ENGINE_PERIPH_H
#define ENGINE_PERIPH_H

struct Device_801E12F8;

/* Low-level driver entry points (0x14 bytes). */
typedef struct Driver_801E11E8 {
    int (*mpInit)(struct Device_801E12F8 *pDevice, unsigned char *pPort);
    int (*mpRelease)(struct Device_801E12F8 *pDevice);
    int (*mpPoll)(struct Device_801E12F8 *pDevice, int (*pCounter)());
    int (*mpGetData)(struct Device_801E12F8 *pDevice, void *pBuffer);
    int (*mpSendData)(struct Device_801E12F8 *pDevice, void *pBuffer);
} Driver_801E11E8;

/* Device slot (0x20 bytes). */
typedef struct Device_801E12F8 {
    unsigned int mIndex;
    Driver_801E11E8 *mpDriver;
    void *mpUnknown08;
    int mStatus;
    int mType;
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    char mPad18[4];
    void *mpData;
} Device_801E12F8;

/* Descriptor passed to fn_801E1478 (sPeriphDesc, 0x18 bytes). */
typedef struct Desc_801E1478 {
    unsigned int mNumDevices;
    unsigned int mUnknown04;
    unsigned int mUnknown08;
    int (*mpUnknown0C)();
    Driver_801E11E8 **mppDrivers;
    int *mpUnknown14;
} Desc_801E1478;

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned int lbl_803ED648;
extern Driver_801E11E8 *lbl_803ED64C;
extern Device_801E12F8 *lbl_803ED658;
extern unsigned int lbl_803ED660;

int fn_801E1478(Desc_801E1478 *pDesc);
int fn_801E153C(void);
int fn_801E1688(unsigned int index);
int fn_801E19B4(unsigned int index);
int fn_801E1A20(void *pData);
int fn_801E1A80(void);
int fn_801E1AB4(void);
void fn_801E26FC(void);

#ifdef __cplusplus
}
#endif

#endif
