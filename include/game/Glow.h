#ifndef GAME_GLOW_H
#define GAME_GLOW_H

#include "game/Vector_80039F5C.h"

/* One sprite of a glow: texture index, size, then red, green, blue and alpha. */
struct GlowElement_t { int mUnknown0; float mUnknown4, mUnknown8, mUnknownC, mUnknown10, mUnknown14; };

/* A ghost sprite of a glow and its position on the line through the screen centre. */
struct GlowGhost_t { GlowElement_t *mUnknown0; float mUnknown4; };

/* One glow: its main sprite, mode words, visibility and fade, position and direction, flicker
   and the ghost sprites that follow it across the screen. */
struct Glow_t {
    GlowElement_t *mUnknown0;
    int mUnknown4, mUnknown8, mUnknownC;
    unsigned char mUnknown10, mUnknown11;
    char mUnknown12[2];
    float mUnknown14;
    Vector_80039F5C mUnknown18, mUnknown24;
    float mUnknown30;
    unsigned char mUnknown34, mUnknown35, mUnknown36;
    char mUnknown37;
    float mUnknown38;
    char mUnknown3C[136]; /* Indexed as 8-byte slots; original capacity unknown. */
};

/* One glow texture: the resource it is loaded from and its GX texture and palette. */
struct GlowTexture_t {
    void *mUnknown0;
    int mUnknown4, mUnknown8;
    unsigned char mUnknownC;
    char mUnknownD[3];
    unsigned char mUnknown10[44];
    unsigned char mUnknown3C[40];
    unsigned char mUnknown64;
    char mUnknown65[3];
};

/* On/off flicker state of one level glow (0x24 bytes). */
struct GlowFlicker_t {
    int mUnknown0;
    int mUnknown4;
    unsigned short mUnknown8;
    char mUnknownA[2];
    float mUnknownC, mUnknown10, mUnknown14, mUnknown18, mUnknown1C;
    float mUnknown20;
};

extern "C" int GlowIsOnScreen(Vector_80039F5C *);

#endif
