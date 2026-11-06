#ifndef ENGINE_TEXFILE_H
#define ENGINE_TEXFILE_H

/* Result of TexGetMaterialByIndex, a 12-byte entry of the table at +0x14 of the
   data; the halfwords +2, +4 and +8 are read by its callers. */
typedef struct TexFileMaterial_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    char mUnknown6[2];
    unsigned short mUnknown8;
    char mUnknownA[2];
} TexFileMaterial_t;

/* Result of TexGetTextureByIndex, a 16-byte entry of the table at +0x18 of the data:
   +8 is the byte size of the block at +0xC. */
typedef struct TexFileImage_t {
    unsigned short mWidth;
    unsigned short mHeight;
    unsigned short mFormat;
    unsigned short mType;
    unsigned int mUnknown8;
    unsigned char *mpUnknownC;
} TexFileImage_t;

/* Result of TexGetPaletteByIndex, a 12-byte entry of the table at +0x1C of the data:
   +4 is the byte size of the block at +8. */
typedef struct TexFilePalette_t {
    unsigned short mFormat;
    unsigned short mUnknown2;
    unsigned int mUnknown4;
    unsigned char *mpUnknown8;
} TexFilePalette_t;

#ifdef __cplusplus
extern "C" {
#endif
void TexMipmapRelocate(void *p);
TexFileMaterial_t *TexGetMaterialByIndex(void *p, unsigned short index);
TexFileImage_t *TexGetTextureByIndex(void *p, unsigned short index);
TexFilePalette_t *TexGetPaletteByIndex(void *p, unsigned short index);
#ifdef __cplusplus
}
#endif

#endif
