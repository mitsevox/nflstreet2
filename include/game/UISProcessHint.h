#ifndef GAME_FN_8021D7B8_H
#define GAME_FN_8021D7B8_H

/* One word of the argument block posted through UISProcessHint. */
union Arg_8021D7B8 {
    int i;
    float f;
    void *p;
};

/* count is the number of argument words at pArgs. */
extern "C" void UISProcessHint(void *p, int id, int count, void *pArgs);

#endif
