#ifndef GAME_PRESNAPPHASE_H
#define GAME_PRESNAPPHASE_H

/* The game phase before the snap: play selection, the pre-snap speech and the
   play clock, until the offense snaps the ball. Mini-games and the tutorial
   install derived objects. */

class PreSnapPhase {
public:
    virtual ~PreSnapPhase() {}
    virtual void InitState();
    virtual void Shutdown();
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void OnExit(float dt);
    virtual void UnusedHook();
    virtual unsigned char AllowsPressPrompts() { return 1; }
    virtual void ReleaseHeldBalls();
    virtual void AssignControlledPlayers();
    virtual void SetupCamera();
    virtual int CanSnap();

    int fn_800C02C8();
    void fn_800C02D4(short value);
    short fn_800C02E0();
    void fn_800C02EC(short value);
    void fn_800C02F8(int value);
    int fn_800C0414();
    unsigned char fn_800C0420(int index);
    unsigned char fn_800C043C(int index);
    unsigned char fn_800C0458();
};

/* .sdata word whose initial value is the object at 0x803EC914, the .sbss word
   in which 0x800CF100 stores this vtable. */
extern PreSnapPhase *lbl_803EABA4;

#endif
