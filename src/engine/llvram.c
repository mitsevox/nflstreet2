/* Low-level VRAM layout tables: the code-less data file of the VRAM library. For each GS pixel
   storage format it gives the block size, the page's block grid and the order of the 32 blocks
   in a page, and a table maps a format slot to its layout. No retained code reads them. */

/* One storage format's page layout. */
typedef struct VramMap_t {
    int mUnknown00;
    int mPixelShift;        /* log2(32 / bits per pixel) */
    int mBlockWidth;        /* pixels */
    int mBlockHeight;       /* pixels */
    int mBlocksPerRow;
    int mBlocksPerColumn;
    unsigned char mBlockOrder[32];
} VramMap_t;

static VramMap_t _Vram_Map_PSMT4 = {
    0, 3, 32, 16, 4, 8,
    { 0, 2, 8, 10, 1, 3, 9, 11, 4, 6, 12, 14, 5, 7, 13, 15,
      16, 18, 24, 26, 17, 19, 25, 27, 20, 22, 28, 30, 21, 23, 29, 31 },
};

static VramMap_t _Vram_Map_PSMT8 = {
    0, 2, 16, 16, 8, 4,
    { 0, 1, 4, 5, 16, 17, 20, 21, 2, 3, 6, 7, 18, 19, 22, 23,
      8, 9, 12, 13, 24, 25, 28, 29, 10, 11, 14, 15, 26, 27, 30, 31 },
};

static VramMap_t _Vram_Map_PSMCT16 = {
    0, 1, 16, 8, 4, 8,
    { 0, 2, 8, 10, 1, 3, 9, 11, 4, 6, 12, 14, 5, 7, 13, 15,
      16, 18, 24, 26, 17, 19, 25, 27, 20, 22, 28, 30, 21, 23, 29, 31 },
};

static VramMap_t _Vram_Map_PSMCT24 = {
    0, 0, 8, 8, 8, 4,
    { 0, 1, 4, 5, 16, 17, 20, 21, 2, 3, 6, 7, 18, 19, 22, 23,
      8, 9, 12, 13, 24, 25, 28, 29, 10, 11, 14, 15, 26, 27, 30, 31 },
};

static VramMap_t _Vram_Map_PSMCT32 = {
    0, 0, 8, 8, 8, 4,
    { 0, 1, 4, 5, 16, 17, 20, 21, 2, 3, 6, 7, 18, 19, 22, 23,
      8, 9, 12, 13, 24, 25, 28, 29, 10, 11, 14, 15, 26, 27, 30, 31 },
};

static VramMap_t *_Vram_pGSVramMapping[15] = {
    &_Vram_Map_PSMT4, &_Vram_Map_PSMT8, &_Vram_Map_PSMCT16, &_Vram_Map_PSMCT24, &_Vram_Map_PSMCT32,
};

/* 32 bytes of uninitialized storage; no retained code reads or writes it. */
unsigned int _Vram_GSTexFlush[8];
