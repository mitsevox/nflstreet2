#include "engine/cu_801D86B4.h"
#include "engine/cu_801DB7D4.h"

extern "C" {
int fn_801CEA08(void);
int fn_801CEC84(void);
int DVDGetDriveStatus(void);
}

extern unsigned char lbl_803EBD4C;

void fn_801D94A0(Shape_801D94A0 *pShape)
{
    int width = pShape->mWidth;
    int height = pShape->mHeight;
    int screenWidth = fn_801CEA08();
    int screenHeight = fn_801CEC84();
    int x = screenWidth / 2 - width / 2;
    if (height != 0x1C0) { height <<= 1; }
    fn_801DB7D8(x, (screenHeight / 2 - height / 2) & ~1, width, height, 0, 0);
}

void fn_801D9538(Shape_801D94A0 *pShape, int type)
{
    unsigned char *pPlanes[3];
    unsigned char *pData;

    if (pShape->mFlags & 0x10000000) {
        pData = (unsigned char *)pShape + pShape->mOffset;
    } else {
        pData = (unsigned char *)&pShape->mOffset;
    }
    pPlanes[0] = pData;
    pPlanes[1] = pData + pShape->mWidth * pShape->mHeight;
    pPlanes[2] = pPlanes[1] + (pShape->mWidth / 2) * (pShape->mHeight / 2);
    if (lbl_803EBD4C != 0) {
        fn_801DB838(pPlanes);
    } else if (type == 4 || type == 5) {
        fn_801DB89C(pPlanes);
    } else {
        fn_801DB838(pPlanes);
    }
}

int fn_801D95E4(void *pInfo, void *pChunk)
{
    if (pChunk == 0) {
        int status = DVDGetDriveStatus();

        if ((status >= 4 && status <= 6) || status == 11 || status == -1) {
            return 0;
        }
    }
    return 1;
}
