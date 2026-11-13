#ifndef GAME_SCREENTRANSITION_H
#define GAME_SCREENTRANSITION_H

typedef void (*ScreenTransNotifyFn)(int, float);
extern "C" void ScreenTransStart(int mode, unsigned int duration, unsigned int color, ScreenTransNotifyFn notify);

#endif
