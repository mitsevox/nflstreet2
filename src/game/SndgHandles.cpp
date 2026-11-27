/* Sound class handles of the in-game sound effects (ball throw, pause, fans,
   vehicle idles) that the in-game sound code binds by name to the loaded
   sound banks. */
#include "game/SndgHandles.h"

Csis::ClassHandle gSndgBallThrow;
Csis::ClassHandle gSndgPauseEvent;
Csis::ClassHandle gSndgFan;
Csis::ClassHandle gSndgIdleBus;
Csis::ClassHandle gSndgIdleTrain;
Csis::ClassHandle gSndgIdleTruck;
Csis::ClassHandle gSndgIdlePolice;
Csis::ClassHandle gSndgIdleGolfCart;
Csis::ClassHandle gSndgIdleIdleTruck;
Csis::ClassHandle gSndgIdleVehicle;

/* The class names and hashes the handles are bound with, in the same order. */
Csis::InterfaceId gSndgBallThrowId = { "Ball_Throw", 0x1B322E75 };
Csis::InterfaceId gSndgPauseEventId = { "PauseEvent", 0x1B3254F3 };
Csis::InterfaceId gSndgFanId = { "Fan", 0x1B327E8D };
Csis::InterfaceId gSndgIdleBusId = { "Idle_Bus", 0x1B326A30 };
Csis::InterfaceId gSndgIdleTrainId = { "Idle_Train", 0x1B323242 };
Csis::InterfaceId gSndgIdleTruckId = { "Idle_Truck", 0x1B3234BA };
Csis::InterfaceId gSndgIdlePoliceId = { "Idle_Police", 0x1B32539E };
Csis::InterfaceId gSndgIdleGolfCartId = { "Idle_GolfCart", 0x1B327D7A };
Csis::InterfaceId gSndgIdleIdleTruckId = { "Idle_IdleTruck", 0x1B3222F9 };
Csis::InterfaceId gSndgIdleVehicleId = { "Idle_Vehicle", 0x1B327B4D };
