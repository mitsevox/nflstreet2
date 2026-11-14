/* GameCube side of the UI graphics movies: allocates a 320x240 movie node,
   streams the movie file and its sound through the MovieRcmp player, decodes
   each frame into the node's texture and swizzles it into GX tiles, and
   moves a playing movie to another menu slot. Functions without a body here
   keep their original bytes. */

#include <string.h>

#include <dolphin/os/OSCache.h>
#include "engine/MovieRcmpInfo.h"
#include "engine/sound.h"
#include "engine/UIGLibraries.h"
#include "engine/UIGFmv.h"
#include "engine/LLUIGFmv.h"
#include "game/fn_801D2B7C.h"

extern void *memset();
extern void *memcpy();

extern void *lbl_803EBF80;
extern Uint8 lbl_803EBF84;
extern Uint8 lbl_803EBF85;

struct StreamTap_801F5DA4 *fn_801F687C(int numRequests, int numFilters, int numTaps, void *pMem,
                                       int memSize);
void fn_801F6AC8(struct StreamTap_801F5DA4 *h, int index, unsigned int mask, unsigned int value,
                 int tap);
void fn_801F6B84(struct StreamTap_801F5DA4 *h);
struct StreamTap_801F5DA4 *fn_801F6CE8(struct StreamTap_801F5DA4 *h, int tap);
int fn_801F6D54(struct StreamTap_801F5DA4 *h, SndFileDesc_t *pFile, int offset,
                unsigned int endMarker);
int fn_801DC86C(Uint8 *pY, Uint8 *pU, Uint8 *pV, Int32 a, Int32 b, Int32 c, void *pDst,
                 Int32 Stride, Int32 d);

void LLUIGFmvProcess(UIGLibrary_t *pObject, LLUIGFmvMovie_t *pMovie)
{
    pMovie->unk_44 = 1;
}

void LLUIGDumpImage(LLUIGFmvStream_t *pSub)
{
    if (pSub->pFrame != NULL) {
        MovieRcmpReleaseFrame(&pSub->Info, pSub->pFrame);
        pSub->pFrame = NULL;
    }
}

void LLUIGFmvDecompressFrame(LLUIGFmvStream_t *pSub, Int32 a)
{
    Uint8 *pY;
    Uint8 *pU;
    Uint8 *pV;

    if (pSub->pFrame != NULL) {
        MovieRcmpGetDataFromFrame(pSub->pFrame, &pY, &pU, &pV);
        fn_801DC86C(pY, pU, pV, pSub->unk_30, pSub->unk_30, pSub->unk_34, pSub->unk_1C,
                    pSub->unk_00 * 4, a);
        MovieRcmpReleaseFrame(&pSub->Info, pSub->pFrame);
        pSub->pFrame = NULL;
    }
}

Int32 LLUIGFmvNextFrame(UIGLibrary_t *pObject, LLUIGFmvMovie_t *pMovie, LLUIGFmvStream_t *pSub)
{
    struct RcmpFrame_t *pFrame = NULL;

    if (pSub->pStream != NULL) {
        if (pSub->pFrame != NULL) {
            MovieRcmpReleaseFrame(&pSub->Info, pSub->pFrame);
            pSub->pFrame = NULL;
        }
        pFrame = MovieRcmpGetFrame(&pSub->Info, MovieRcmpGetGoalFrame(&pSub->Info));
        pSub->pFrame = pFrame;
        if (pFrame != NULL && pSub->unk_34 == 0 && pSub->unk_30 == 0) {
            MovieRcmpGetSizeFromFrame(pFrame, &pSub->unk_30, &pSub->unk_34);
        }
    }
    if (pFrame == NULL) {
        pMovie->Flags |= 2;
        if (pMovie->Flags & 1) {
            LLUIGFmvStopInstance(pObject, pMovie);
            LLUIGFmvStartInstance(pObject, pMovie);
        } else {
            lbl_803EBF85 = 1;
            lbl_803EBF84 = 1;
        }
    }
    return pFrame != NULL;
}

void LLUIGFmvUpdate(UIGLibrary_t *pObject, LLUIGFmvMovie_t *pMovie)
{
    LLUIGFmvStream_t *pSub;

    if (pMovie->unk_44 != 0) {
        pSub = &pMovie->Sub;
        if (pSub->Info.mpAudio != NULL && pSub->Info.mpVideo != NULL) {
            pMovie->unk_44 = 0;
            pSub->unk_14++;
            if (MovieRcmpIsDecodeTime(&pSub->Info)) {
                if (pSub->unk_16 != 0) {
                    if (!(MovieRcmpGetCurFrame(&pSub->Info) & 1)) {
                        LLUIGDumpImage(pSub);
                        LLUIGFmvNextFrame(pObject, pMovie, pSub);
                    } else {
                        LLUIGFmvDecompressFrame(pSub, 2);
                        if (LLUIGFmvNextFrame(pObject, pMovie, pSub)) {
                            LLUIGFmvDecompressFrame(pSub, 1);
                            LLUIGFmvNextFrame(pObject, pMovie, pSub);
                            LLUIGFMVSizzle32to32(pSub->unk_00, pSub->unk_04, pSub->unk_1C);
                            DCStoreRange(pSub->unk_1C, pSub->unk_00 * pSub->unk_04 * 4);
                        }
                    }
                } else {
                    LLUIGFmvDecompressFrame(pSub, 0);
                    LLUIGFmvNextFrame(pObject, pMovie, pSub);
                    LLUIGFMVSizzle32to32(pSub->unk_00, pSub->unk_04, pSub->unk_1C);
                    DCStoreRange(pSub->unk_1C, pSub->unk_00 * pSub->unk_04 * 4);
                }
            }
        }
    }
}

void LLUIGFmvInit(void)
{
}

void LLUIGFmvShutdown(void)
{
}

LLUIGFmvMovie_t *LLUIGFmvAddInstance(UIGLibrary_t *pObject, Int16 a, Int16 b)
{
    Int32 Heap = UIGFmvGetHeap();
    LLUIGFmvMovie_t *pMovie;
    LLUIGFmvStream_t *pSub;

    UIGLibrarySetMemInfo(a, b);
    pMovie = fn_801D2B7C(sizeof(LLUIGFmvMovie_t), 0, 0);
    memset(pMovie, 0, sizeof(LLUIGFmvMovie_t));
    pSub = &pMovie->Sub;
    UIGLibraryClearMemInfo();
    pMovie->Flags = 0;
    pSub->unk_04 = 240;
    pSub->unk_00 = 320;
    pSub->unk_1C = fn_801D2BB0(Heap, 0x4B000, 0, 0);
    memset(pSub->unk_1C, 0, 0x4B000);
    DCStoreRange(pSub->unk_1C, pSub->unk_00 * pSub->unk_04 * 4);
    LLUIGFmvInitTexture(pMovie, 320, 240);
    pMovie->unk_40 = b;
    pMovie->unk_3C = a;
    lbl_803EBF84 = 1;
    return pMovie;
}

void LLUIGFmvDeleteInstance(UIGLibrary_t *pObject, LLUIGFmvMovie_t *pMovie)
{
    LLUIGFmvStream_t *pSub = &pMovie->Sub;

    LLUIGFmvStopInstance(pObject, pMovie);
    if (lbl_803EBF80 != NULL) {
        fn_801D2BD0(lbl_803EBF80);
        lbl_803EBF80 = NULL;
    }
    if (pSub->unk_08 != NULL) {
        fn_801D2BD0(pSub->unk_08);
        pSub->unk_08 = NULL;
    }
    if (pSub->unk_1C != NULL) {
        fn_801D2BD0(pSub->unk_1C);
        pSub->unk_1C = NULL;
    }
    if (pSub->unk_18 != NULL) {
        fn_801D2BD0(pSub->unk_18);
        pSub->unk_18 = NULL;
    }
    fn_801D2BD0(pMovie);
    lbl_803EBF85 = 1;
}

void LLUIGFmvStartInstance(UIGLibrary_t *pObject, LLUIGFmvMovie_t *pMovie)
{
    Int32 Heap = UIGFmvGetHeap();
    LLUIGFmvStream_t *pSub = &pMovie->Sub;
    SndFileDesc_t File;
    Int32 Queued;

    if (pSub->unk_1C == NULL) {
        pSub->unk_1C = fn_801D2BB0(Heap, 0x4B000, 0, 0);
        memset(pSub->unk_1C, 0, 0x4B000);
        DCStoreRange(pSub->unk_1C, pSub->unk_00 * pSub->unk_04 * 4);
    }
    pSub->unk_08 = fn_801D2BB0(Heap, 0x4B000, 0, 0);
    pSub->pStream = fn_801F687C(2, 2, 2, pSub->unk_08, 0x4B000);
    if (UIGFmvHaveSound()) {
        pSub->pTap = fn_801F6CE8(pSub->pStream, 2);
        fn_801F6AC8(pSub->pStream, 1, 0xFFFF, 17235, 2);
    } else {
        pSub->pTap = (struct StreamTap_801F5DA4 *)-1;
        fn_801F6AC8(pSub->pStream, 1, 0xFFFF, 17235, -1);
    }
    File.pRes = UIGLibraryGetResFile(pObject, pMovie->unk_3C);
    File.mIndex = pMovie->unk_40;
    Queued = fn_801F6D54(pSub->pStream, &File, 0, 0);
    MovieRcmpInitVideo(&pSub->Info, pSub->pStream);
    pSub->unk_30 = 0;
    pSub->unk_34 = 0;
    pSub->pFrame = MovieRcmpGetFrame(&pSub->Info, 0);
    if (pSub->pFrame != NULL) {
        MovieRcmpGetSizeFromFrame(pSub->pFrame, &pSub->unk_30, &pSub->unk_34);
    }
    if (UIGFmvHaveSound()) {
        MovieRcmpInitAudio(&pSub->Info, pSub->pTap, Queued);
    }
    pMovie->unk_44 = 1;
    pSub->unk_14 = 0;
    pSub->unk_16 = UIGFmvHaveAlphaMap();
    lbl_803EBF85 = 0;
    lbl_803EBF84 = 0;
}

void LLUIGFmvStopInstance(UIGLibrary_t *pObject, LLUIGFmvMovie_t *pMovie)
{
    LLUIGFmvStream_t *pSub;

    if (pMovie->unk_40 == -1) {
        lbl_803EBF85 = 1;
        return;
    }
    pSub = &pMovie->Sub;
    if (pSub->pStream != NULL) {
        if (UIGFmvHaveSound() && pSub->pTap != (struct StreamTap_801F5DA4 *)-1) {
            MovieRcmpShutdownAudio(&pSub->Info);
        }
        MovieRcmpShutdownVideo(&pSub->Info);
        fn_801F6B84(pSub->pStream);
        pSub->pStream = NULL;
        pSub->Info.mpAudio = NULL;
        pSub->Info.mpVideo = NULL;
    }
    if (pSub->unk_08 != NULL) {
        fn_801D2BD0(pSub->unk_08);
        pSub->unk_08 = NULL;
    }
    if (pSub->unk_1C != NULL) {
        fn_801D2BD0(pSub->unk_1C);
        pSub->unk_1C = NULL;
    }
    if (pSub->unk_18 != NULL) {
        fn_801D2BD0(pSub->unk_18);
        pSub->unk_18 = NULL;
    }
    lbl_803EBF84 = 1;
}

void LLUIGFMVSizzle32to32(Int32 Width, Int32 Height, Uint8 *pData)
{
    Int32 Heap = UIGFmvGetHeap();
    Int32 TilesX = (Width + 3) >> 2;
    Int32 TilesY = (Height + 3) >> 2;
    Uint32 x;
    Uint32 y;
    Uint8 *pTile;

    if (lbl_803EBF80 == NULL) {
        lbl_803EBF80 = fn_801D2BB0(Heap, TilesX * TilesY * 64, 0, 0);
    }
    pTile = lbl_803EBF80;
    for (y = 0; y < TilesY; y++) {
        for (x = 0; x < TilesX; x++) {
            _PackTile_RGBA8(pData, x * 4, y * 4, pTile, Width, Height);
            pTile += 64;
        }
    }
    memcpy(pData, lbl_803EBF80, TilesX * TilesY * 64);
}

void _GetLayerValue(Uint8 *pSrc, Int32 Width, Int32 x, Int32 y, Uint8 *pA, Uint8 *pB, Uint8 *pC)
{
    Uint8 *p = &pSrc[(y * Width + x) * 4];
    Uint8 First = p[3];
    Uint8 Second = p[2];

    pA[1] = First;
    pA[0] = Second;
    if (pB != NULL) {
        *pB = p[1];
    }
    if (pC != NULL) {
        *pC = p[0];
    }
}

void _PackTile_RGBA8(Uint8 *pSrc, Int32 x, Int32 y, Uint8 *pTile, Int32 Width, Int32 Height)
{
    Uint32 Rows = Height - y;
    Uint32 Cols = Width - x;
    Uint32 i;
    Uint32 j;
    Uint8 *pAR;
    Uint8 *pGB;
    Uint8 Texel[4];

    if (Rows > 4) {
        Rows = 4;
    }
    if (Cols > 4) {
        Cols = 4;
    }
    for (j = 0; j < Rows; j++) {
        pAR = &pTile[j * 8];
        pGB = &pTile[j * 8 + 32];
        for (i = 0; i < Cols; i++) {
            _GetLayerValue(pSrc, Width, x + i, y + j, &Texel[0], &Texel[2], &Texel[3]);
            pAR[0] = Texel[1];
            pAR[1] = Texel[0];
            pGB[0] = Texel[2];
            pGB[1] = Texel[3];
            pAR += 2;
            pGB += 2;
        }
    }
}

void LLUIGFmvSwapInstance(UIGLibrary_t *pObject, Int16 a, Int16 b, LLUIGFmvMovie_t *pMovie)
{
    UIGLibraryMoveItem(pObject, a, b, pMovie->unk_3C, pMovie->unk_40);
    LLUIGFmvStopInstance(pObject, pMovie);
    pMovie->unk_3C = a;
    pMovie->unk_40 = b;
    lbl_803EBF84 = 0;
    pMovie->Flags &= ~2;
}
