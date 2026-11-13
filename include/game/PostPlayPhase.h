#ifndef GAME_POSTPLAYPHASE_H
#define GAME_POSTPLAYPHASE_H

/* The game phase after a play: it shows the play result ("1st Down",
   "Touchdown", ...), runs the result sequence and then picks the next phase.
   Mini-games and the tutorial install derived objects. */

class PostPlayPhase {
public:
    virtual void InitState();
    virtual void Shutdown();
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void OnExit();
    virtual void OnSequenceStart();
    virtual void ShowResultText();
    virtual void SetupCamera();
    virtual int GetResultText(char *pText);
    virtual void UpdateCue(float dt);
    virtual int IsHeld(float dt);
    virtual int GetBusy(float dt);
    virtual int IsFinished(int busy);
    virtual void Finish(float dt);
    virtual void ForceFinish();
};

/* .sdata word whose initial value is the object at 0x803EC90C, the .sbss word
   in which 0x800CF100 stores this vtable. */
extern PostPlayPhase *lbl_803EAB84;

#endif
