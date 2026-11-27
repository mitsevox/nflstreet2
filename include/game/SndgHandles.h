#ifndef GAME_SNDGHANDLES_H
#define GAME_SNDGHANDLES_H

#include "engine/csis.h"

/* CSIS class handles defined by src/game/SndgHandles.cpp. */
extern Csis::ClassHandle gSndgBallThrow;
extern Csis::ClassHandle gSndgPauseEvent;
extern Csis::ClassHandle gSndgFan;
extern Csis::ClassHandle gSndgIdleBus;
extern Csis::ClassHandle gSndgIdleTrain;
extern Csis::ClassHandle gSndgIdleTruck;
extern Csis::ClassHandle gSndgIdlePolice;
extern Csis::ClassHandle gSndgIdleGolfCart;
extern Csis::ClassHandle gSndgIdleIdleTruck;
extern Csis::ClassHandle gSndgIdleVehicle;

/* Their class ids, also defined by src/game/SndgHandles.cpp. */
extern Csis::InterfaceId gSndgBallThrowId;
extern Csis::InterfaceId gSndgPauseEventId;
extern Csis::InterfaceId gSndgFanId;
extern Csis::InterfaceId gSndgIdleBusId;
extern Csis::InterfaceId gSndgIdleTrainId;
extern Csis::InterfaceId gSndgIdleTruckId;
extern Csis::InterfaceId gSndgIdlePoliceId;
extern Csis::InterfaceId gSndgIdleGolfCartId;
extern Csis::InterfaceId gSndgIdleIdleTruckId;
extern Csis::InterfaceId gSndgIdleVehicleId;

#endif
