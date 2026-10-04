#ifndef GAME_ENTRY_80219044_H
#define GAME_ENTRY_80219044_H

/* 12-byte text argument passed by address in message argument lists and in
   the list given to fn_80219044: a length word at +4 and a string pointer at
   +8. */
struct Entry_80219044 {
    int mUnknown0;
    int mLength;
    char *mpText;
};

#endif
