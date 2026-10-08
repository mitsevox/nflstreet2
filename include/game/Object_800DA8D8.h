#ifndef GAME_OBJECT_800DA8D8_H
#define GAME_OBJECT_800DA8D8_H

struct Entry_800DA8D8
{
    float mUnknown0;
    float mUnknown4;
    int mUnknown8;
};

/* Object at payload +0xC that fn_800DA8D8 and fn_800DAA68 index. Only the
   12-byte entries from +24 are declared. */
struct Object_800DA8D8
{
    char mUnknown0[24];
    Entry_800DA8D8 mUnknown24[1];
};

#endif
