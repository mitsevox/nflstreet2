#ifndef GAME_TIMESCALE_H
#define GAME_TIMESCALE_H

void TimeScaleReset();
void TimeScaleUpdate();
void TimeScaleSet(float target);
void TimeScaleRamp(float target, float divisor);

#endif
