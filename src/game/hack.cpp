/* Development hacks: loading a file from the host by name, saving the frame buffer to a numbered
   bitmap and dumping a masked range of memory. On the GameCube no code calls them: the linker
   discarded the functions, and only their settings and literals remain. */

extern "C" {
int printf(const char *pFormat, ...);
int sprintf(char *pOut, const char *pFormat, ...);
}

/* Header of the 640 x 448, 32-bit screen dump bitmap. */
static unsigned char _Hack_BMPHeader[54] = {
    'B', 'M', 0x36, 0x80, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00,
    0x28, 0x00, 0x00, 0x00, 0x80, 0x02, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x01, 0x00,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x11, 0x00, 0x12, 0x0B, 0x00, 0x00,
    0x12, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
static int _Hack_ScreenDumpNum = 0;

unsigned char Hack_ScreenShotEnabled = 1;
int Hack_fptodp_cnt = 0;
int Hack_ProfileFrames = 1;

static unsigned int _Hack_MemMask[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
static unsigned int _Hack_MemCompare[4] = { 0, 0, 0, 0 };
static int _Hack_nWords = 1;
static unsigned int _Hack_MemStart = 0x00100000;
static unsigned int _Hack_MemEnd = 0x04000000;

// FAKEMATCH: discarded stand-ins (static inline, so ProDG emits their literals and the statics
// they read without their code); the target keeps only this file's data and .rodata literals
static inline int HackLoadFile(char *pName, void *pFile)
{
    if (pFile == 0) {
        printf("Error: Cannot open %s\n", pName);
        return 0;
    }
    printf("HackLoad: %s\n", pName);
    return 1;
}

static inline void _HackScreenDump(char *pName)
{
    if (Hack_ScreenShotEnabled) {
        sprintf(pName, "screen%02d.bmp", _Hack_ScreenDumpNum++);
        pName[0] = _Hack_BMPHeader[0];
    }
}

static inline void _HackMemDump(void)
{
    unsigned int *p;

    for (p = (unsigned int *)_Hack_MemStart; p < (unsigned int *)_Hack_MemEnd; p += _Hack_nWords) {
        if ((p[0] & _Hack_MemMask[0]) == _Hack_MemCompare[0]) {
            printf("%08X: %08X %08X %08X %08X\n", p, p[0], p[1], p[2], p[3]);
        }
    }
}
