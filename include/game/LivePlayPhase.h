#ifndef GAME_LIVEPLAYPHASE_H
#define GAME_LIVEPLAYPHASE_H

/* The game phase that runs while the ball is live. The game calls the
   current phase object's OnEnter, OnUpdate and OnExit from its phase table;
   mini-games and the tutorial install derived objects. */

class LivePlayPhase {
public:
    virtual void InitState();
    virtual void Shutdown();
    virtual void OnEnter();
    virtual void OnUpdate(float dt);
    virtual void OnExit();
};

/* .sdata word whose initial value is the object at 0x803EC900, the .sbss word
   in which 0x800CF100 stores this vtable. */
extern LivePlayPhase *lbl_803EA9E4;

#endif
