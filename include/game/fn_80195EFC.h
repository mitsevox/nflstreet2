#ifndef GAME_FN_80195EFC_H
#define GAME_FN_80195EFC_H

typedef void (*Callback_80195EFC)(int, float);
extern "C" void fn_80195EFC(int mode, unsigned int duration, unsigned int color, Callback_80195EFC notify);

#endif
