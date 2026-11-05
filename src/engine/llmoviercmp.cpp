/* Low-level side of movie playback: centres the movie picture on the screen, hands each
   decoded frame's Y/U/V planes to the YUV renderer, and stops the movie stream when the
   disc drive reports an error. */

#include "engine/moviercmp.h"
#include "engine/render.h"
#include "engine/fn_801CEA08.h"

extern "C" {
int fn_801CEC84(void);
int DVDGetDriveStatus(void);
}

extern unsigned char lbl_803EBD4C;

void MovieRcmpRenderInit(Shape_t *pShape)
{
    int width = pShape->mWidth;
    int height = pShape->mHeight;
    int screenWidth = fn_801CEA08();
    int screenHeight = fn_801CEC84();
    int x = screenWidth / 2 - width / 2;
    if (height != 0x1C0) { height <<= 1; }
    yuvrenderinit(x, (screenHeight / 2 - height / 2) & ~1, width, height, 0, 0);
}

void MovieRcmpRenderShape(Shape_t *pShape, int type)
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
        yuvrenderDoubleYLines(pPlanes);
    } else if (type == 4 || type == 5) {
        yuvrenderVP6YLines(pPlanes);
    } else {
        yuvrenderDoubleYLines(pPlanes);
    }
}

int MovieRcmpHandleChunk(void *pInfo, void *pChunk)
{
    if (pChunk == 0) {
        int status = DVDGetDriveStatus();

        if ((status >= 4 && status <= 6) || status == 11 || status == -1) {
            return 0;
        }
    }
    return 1;
}
