#ifndef GAME_PALETTECOLOR_H
#define GAME_PALETTECOLOR_H

/* The fourth byte of each colour is never accessed. */
struct PaletteColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct ColorPalette {
    PaletteColor mColors[4];
};

extern "C" {
void DbColPalGetPalette(int index, ColorPalette *pPalette);
void DbColPalGetPrimaryColor(unsigned char index, PaletteColor *pColor);
}

#endif
