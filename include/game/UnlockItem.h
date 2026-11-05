#ifndef GAME_UNLOCKITEM_H
#define GAME_UNLOCKITEM_H

/* Record filled by UnlockListReadItem. */
struct UnlockItem {
    signed char mIndex;
    char mName[132];
    int mUnknown136;
    int mUnknown140;
    unsigned int mUnknown144;
    int mUnknown148;
};

#endif
