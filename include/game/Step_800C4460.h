#ifndef GAME_STEP_800C4460_H
#define GAME_STEP_800C4460_H

/* One of the eight 32-byte steps of Sequence_800C4460. */
struct Step_800C4460 {
    int (*mpCallback0)(void *p);
    int (*mpCallback4)(void *p);
    void (*mpCallback8)(void *p);
    float mUnknownC;
    union { unsigned char mUnknown10[16]; int mWords10[4]; };
};

#endif
