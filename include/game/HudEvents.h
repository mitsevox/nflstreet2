#ifndef GAME_HUDEVENTS_H
#define GAME_HUDEVENTS_H

/* src/game/HudEvents.cpp */
extern "C" {
void HudSetGameBreakerMeter(int a, float t, int b, int direct);
void HudSetGameBreakerLevel(int a, int b);
void HudResetGameBreaker(int a);
void HudSetEvent1A(int a, int b);
}

#endif
