#ifndef GAME_PREGAMEPHASE_H
#define GAME_PREGAMEPHASE_H

/* The game phase before the first play: it plays the intro sequence and then
   hands over to the first play's phase. Mini-games and the tutorial install
   derived objects. */

class PreGamePhase {
public:
    virtual void InitState();
    virtual void Shutdown();
    virtual void OnEnter();
    virtual void OnUpdate(float dt);
    virtual void OnExit();
    virtual void ShowIntroScreen();
    virtual void HideIntroScreen();
    virtual void UpdateIntroStart(float dt);
    virtual void UpdateIntro(float dt);
    virtual void UpdateIntroEnd(float dt);
    virtual void EnterFirstPhase(float dt);
};

/* .sdata word whose initial value is the object at 0x803EC910, the .sbss word
   in which 0x800CF100 stores this vtable. */
extern PreGamePhase *lbl_803EAB90;

#endif
