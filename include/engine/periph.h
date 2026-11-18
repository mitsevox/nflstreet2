#ifndef ENGINE_PERIPH_H
#define ENGINE_PERIPH_H

struct PerDevice_t;

/* Low-level driver entry points (0x14 bytes). */
typedef struct PerDriver_t {
    int (*mpInit)(struct PerDevice_t *pDevice, unsigned char *pPort);
    int (*mpRelease)(struct PerDevice_t *pDevice);
    int (*mpPoll)(struct PerDevice_t *pDevice, int (*pCounter)());
    int (*mpGetData)(struct PerDevice_t *pDevice, void *pBuffer);
    int (*mpSendData)(struct PerDevice_t *pDevice, void *pBuffer);
} PerDriver_t;

/* Device slot (0x20 bytes). */
typedef struct PerDevice_t {
    unsigned int mIndex;
    PerDriver_t *mpDriver;
    void *mpUnknown08;
    int mStatus;
    int mType;
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    char mPad18[4];
    void *mpData;
} PerDevice_t;

/* Start of a device's data record (PerSizeofPerDataT bytes): the slot index, then the
   axis bytes and button bits from +8. */
typedef struct PerData_t {
    unsigned int mIndex;
    int mUnknown04;
    unsigned char mUnknown08[1];
} PerData_t;

/* Descriptor passed to PerInit (sPeriphDesc, 0x18 bytes). */
typedef struct PerInitParms_t {
    unsigned int mNumDevices;
    unsigned int mUnknown04;
    unsigned int mUnknown08;
    int (*mpUnknown0C)();
    PerDriver_t **mppDrivers;
    int *mpUnknown14;
} PerInitParms_t;

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char Per_ModuleActive;
extern unsigned char Per_BtnMask[8];
extern unsigned int Per_MaxAxis;
extern unsigned int Per_NumDrivers;
extern PerDriver_t *Per_DriverArray;
extern unsigned int Per_MaxButtons;
extern unsigned int Per_MaxDevices;
extern PerDevice_t *Per_DeviceArray;
extern unsigned char *Per_DeviceDataBuffer;
extern unsigned int Per_NumDevices;

int PerInit(PerInitParms_t *pDesc);
int PerShutdown(void);
int PerReleaseSingleDevice(unsigned int index);
unsigned int PerGetDeviceTypeT(unsigned int index);
int PerSystemInit(void *pData);
int PerSystemShutdown(void);
int PerRegisterDevices(void);
void PerJoyDriverPollPADs(void);

#ifdef __cplusplus
}
#endif

#endif
