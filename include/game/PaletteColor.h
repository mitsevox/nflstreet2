#ifndef GAME_PALETTECOLOR_H
#define GAME_PALETTECOLOR_H

/* The fourth byte of each colour is never accessed. */
struct PaletteColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

extern "C" {
void fn_8007A068(unsigned char index, PaletteColor *pColor);
}

#endif
