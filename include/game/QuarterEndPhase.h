#ifndef GAME_QUARTERENDPHASE_H
#define GAME_QUARTERENDPHASE_H

/* The game phase that runs between quarters: it waits on the quarter-end
   screen, plays the list of quarter-end clips and then hands over to the
   next phase. Its single object is defined in src/game/QuarterEndPhase.cpp. */
class QuarterEndPhase {
public:
    virtual void OnEnter();
    virtual void OnUpdate(float f);
    virtual void OnExit();
    void InitState();
    int IsWaiting();
};

extern QuarterEndPhase *gQuarterEndPhase;

#endif
