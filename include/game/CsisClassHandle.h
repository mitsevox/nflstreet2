#ifndef GAME_CSISCLASSHANDLE_H
#define GAME_CSISCLASSHANDLE_H

struct Entry_801B8DF0;

/* Constructed by 0x801B8D9C; src/game/SndgHandles.cpp defines ten objects of it. */
class CsisClassHandle {
public:
    CsisClassHandle();

    Entry_801B8DF0 *mEntry;
    int mValue;
};

extern CsisClassHandle gSndgBallThrow;
extern CsisClassHandle gSndgPauseEvent;
extern CsisClassHandle gSndgFan;
extern CsisClassHandle gSndgIdleBus;
extern CsisClassHandle gSndgIdleTrain;
extern CsisClassHandle gSndgIdleTruck;
extern CsisClassHandle gSndgIdlePolice;
extern CsisClassHandle gSndgIdleGolfCart;
extern CsisClassHandle gSndgIdleIdleTruck;
extern CsisClassHandle gSndgIdleVehicle;

#endif
