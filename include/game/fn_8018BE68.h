#ifndef GAME_FN_8018BE68_H
#define GAME_FN_8018BE68_H

/* 32-byte output block of fn_8018BE68 and fn_8018BECC; both fall back to a
   local block of their own when the pointer is null. */
struct Result_8018BE68 {
    int mUnknown0;
    char mUnknown4[28];
};

extern "C" {
int fn_8018BE68(int a, int b, Result_8018BE68 *pOut);
int fn_8018BECC(int a, int b, Result_8018BE68 *pOut);
}

#endif
