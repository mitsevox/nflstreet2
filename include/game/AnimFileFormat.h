#ifndef GAME_ANIMFILEFORMAT_H
#define GAME_ANIMFILEFORMAT_H

struct AnimCompressTableView {
    unsigned char unknown0[4];
    char *array4;
    char *array8;
    char *arrayC;
    char *array10;
    char *array14;
};

struct AnimMotionGroupView {
    unsigned int count;
    char **motion;
    AnimCompressTableView *compress;
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
    AnimCompressTableView *compress;
    AnimGroupHeaderView *groups;
    AnimMotionGroupView *groupMotion;
};

void AnimExtnRelocateFile(AnimFileFormat_t *file);

#endif
