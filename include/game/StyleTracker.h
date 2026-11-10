#ifndef GAME_STYLE_TRACKER_H
#define GAME_STYLE_TRACKER_H

/* Style awards, combinations and Gamebreaker meter events. */
struct Object_80039F5C;
struct Record_800B15FC;
struct AudmonEvent_t;

extern "C" {
typedef void (*StyleAwardCallback)(int, int, const char *, int, int, int, int);
unsigned short StyleTrackerGetEventCount(int side, int index);
float StyleTrackerGetMeterFraction(int side);
void StyleTrackerSetMeter(int side, int value, int arg);
void StyleTrackerSetMeterFraction(int side, float t, int arg);
int StyleTrackerGetTotal(int side);
void StyleTrackerSetTotal(int side, int value);
int StyleTrackerGetWinner();
void StyleTrackerOnTouchdown(void);
void StyleTrackerOnCarrierStopped(float a);
void StyleTrackerOnSafety(void);
void StyleTrackerOnTackle(Object_80039F5C *p, float a);
void StyleTrackerOnBrokenTackle(Object_80039F5C *p);
void StyleTrackerOnTackleContest(int flag, Object_80039F5C *p);
void StyleTrackerOnTurnoverOnDowns(void);
void StyleTrackerOnTouchback(int flag);
void StyleTrackerOnFirstDown(void);
void StyleTrackerOnStyleFirstDown(void);
void StyleTrackerOnConversion(void);
void StyleTrackerOnDefensiveConversion(void);
void StyleTrackerOnFailedConversion(void);
void StyleTrackerOnFumbleRecovery(Object_80039F5C *p);
void StyleTrackerOnFumble(Object_80039F5C *p, int team);
void StyleTrackerRefreshUserPlayers(void);
void StyleTrackerOnPumpFake(Object_80039F5C *p);
void StyleTrackerSetStylePassPending(unsigned char flag);
void StyleTrackerSetPassSubtype(int value);
void StyleTrackerBeginStiffArm(int flag);
void StyleTrackerResolveStiffArm(Object_80039F5C *p, int flag);
void StyleTrackerBeginJuke(Object_80039F5C *p, int kind);
void StyleTrackerFinishJuke(Object_80039F5C *p);
void StyleTrackerBeginSpin(Object_80039F5C *p, int kind, unsigned char flag);
void StyleTrackerFinishSpin(Object_80039F5C *p);
void StyleTrackerOnMoveResult(int value);
void StyleTrackerBeginPumpInteraction(void);
int StyleTrackerUpdateRun(int active, int a, int b);
void StyleTrackerAwardDive(Object_80039F5C *p, int kind, unsigned char flag);
void StyleTrackerBeginHurdle(Object_80039F5C *p, int kind, unsigned char flag);
void StyleTrackerFinishHurdle(Object_80039F5C *p);
void StyleTrackerSetCatchFlags(int a, int b, unsigned char c);
void StyleTrackerAwardCatch(Object_80039F5C *p);
void StyleTrackerOnCarrierContact(Object_80039F5C *p);
void StyleTrackerOnInterception(int a, Object_80039F5C *p);
void StyleTrackerBeginPitch(int flag, Object_80039F5C *p);
void StyleTrackerFinishPitch(int team, int a, int b);
void StyleTrackerEndDefensiveMove(Object_80039F5C *p);
void StyleTrackerOnCarrierActionTwo(Object_80039F5C *p);
void StyleTrackerOnCarrierActionFive(Object_80039F5C *p);
void StyleTrackerOnActionThree(void);
void StyleTrackerAwardHotspot(Object_80039F5C *p, unsigned int count, int changed);
void StyleTrackerAwardStrip(int team);
void StyleTrackerOnActionFour(void);
void StyleTrackerEndPlay(void);
void StyleTrackerHandleGameEvent(Record_800B15FC *pRecord);
void StyleTrackerHandleAudioEvent(AudmonEvent_t *pRecord);
void StyleTrackerReset(void);
void StyleTrackerInit(void);
void StyleTrackerResetDefaults();
void StyleTrackerSetEnabled(int a);
unsigned char StyleTrackerGetCatchStreak(int team);
void StyleTrackerMarkCatchOpportunity(int team);
unsigned char StyleTrackerGetStyleCatchStreak(int team);
unsigned int StyleTrackerAddProfilePoints(int side, unsigned int value);
void StyleTrackerSetAwardCallback(StyleAwardCallback a);
}

#endif
