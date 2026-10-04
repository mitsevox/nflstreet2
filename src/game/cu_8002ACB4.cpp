#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"

/* Seven-word stream operation table, the shape of the CardStream table at 0x802F46C4. */
struct StreamOps_8002ACB4 {
    int (*mpOpen)(void *pStream, int a, int target, unsigned char reading);
    int (*mpClose)(void *pStream);
    int (*mpRead)(void *pStream, void *pData, unsigned int size, unsigned int *pDone);
    int (*mpWrite)(void *pStream, void *pData, unsigned int size, unsigned int *pDone);
    void (*mpUnknown10)(void *pStream, unsigned int count);
    int (*mpUnknown14)(unsigned int size);
    unsigned int mUnknown18;
};

struct Request_8002AD64 {
    char mUnknown0[12];
    int mTarget;
    unsigned char mUnknown10;
};

extern "C" {
void fn_80029C2C(int a, int b, int c);
void fn_8002A1D4(int a, int b, char *pBuf);
void fn_8002A260(int a, int b, char *pBuf, int size);
int fn_8002A9B8(int a, void *pBuffer);

static void *lbl_803EA340 = 0;
static void *lbl_803EA344 = 0;

int fn_8002ACB4(int target, StreamOps_8002ACB4 *pOps)
{
    char stream[0x80];
    unsigned int done;
    int result;

    pOps->mpUnknown14(0x100);
    result = pOps->mpOpen(stream, 0x100, target, 0);
    if (result == 0) {
        result = pOps->mpWrite(stream, lbl_803EA340, 0x100, &done);
    }
    if (result == 0) {
        result = pOps->mpClose(stream);
    } else {
        pOps->mpClose(stream);
    }
    return result;
}

int fn_8002AD64(Request_8002AD64 *pRequest, StreamOps_8002ACB4 *pOps)
{
    int result;

    if (pRequest->mUnknown10) {
        result = fn_8002ACB4(pRequest->mTarget, pOps);
    } else {
        result = fn_8002ACB4(pRequest->mTarget, pOps);
    }
    return result;
}

int fn_8002ADA0(Request_8002AD64 *pRequest, StreamOps_8002ACB4 *pOps)
{
    return 0xFFFF;
}

void fn_8002ADAC(void)
{
    if (lbl_803EA340 != 0) {
        fn_801D2BD0(lbl_803EA340);
        lbl_803EA340 = 0;
    }
}

int fn_8002ADE0(int a, int b)
{
    char name[32];
    int result;

    fn_8002ADAC();
    result = 0;
    lbl_803EA340 = fn_801D2B7C(0x100, 0, 0);
    if (lbl_803EA340 != 0) {
        fn_801C1F94(lbl_803EA340, 0, 0x100);
        lbl_803EA344 = lbl_803EA340;
        result = fn_8002A9B8(b, lbl_803EA340);
        if (result != 0) {
            fn_80029C2C(3, a, 0);
            fn_8002A260(2, a, name, 32);
            fn_8002A1D4(3, a, name);
        }
    }
    return result;
}
}
