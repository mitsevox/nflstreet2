#ifndef ENGINE_PERIPH_H
#define ENGINE_PERIPH_H

struct Device_801E12F8;

/* Low-level driver entry points (0x14 bytes). */
typedef struct Driver_801E11E8 {
    int (*mpInit)(struct Device_801E12F8 *pDevice, unsigned char *pPort);
    int (*mpRelease)(struct Device_801E12F8 *pDevice);
    int (*mpPoll)(struct Device_801E12F8 *pDevice, int arg);
    int (*mpGetData)(struct Device_801E12F8 *pDevice, void *pBuffer);
    int (*mpSendData)(struct Device_801E12F8 *pDevice, void *pBuffer);
} Driver_801E11E8;

/* Device slot (0x20 bytes). */
typedef struct Device_801E12F8 {
    unsigned int mIndex;
    Driver_801E11E8 *mpDriver;
    void *mpUnknown08;
    int mConnected;
    int mType;
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    char mPad18[4];
    void *mpData;
} Device_801E12F8;

extern unsigned int lbl_803ED648;
extern Driver_801E11E8 *lbl_803ED64C;
extern Device_801E12F8 *lbl_803ED658;
extern unsigned int lbl_803ED660;

#endif
