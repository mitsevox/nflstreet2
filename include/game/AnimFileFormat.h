#ifndef GAME_ANIMFILEFORMAT_H
#define GAME_ANIMFILEFORMAT_H

#include "game/Record_8019D8AC.h"

struct AnimMotionGroupView {
    unsigned int count;
    char **motion;
    Record_8019D8AC *compress;
};

struct AnimGroupHeaderView {
    unsigned int count;
};

struct AnimFileFormat_t {
    unsigned char unknown0[4];
    unsigned short motionCount;
    unsigned short flags;
    unsigned char unknown8[8];
    char **motion;
    Record_8019D8AC *compress;
    AnimGroupHeaderView *groups;
    AnimMotionGroupView *groupMotion;
};

void AnimExtnRelocateFile(AnimFileFormat_t *file);

#endif
