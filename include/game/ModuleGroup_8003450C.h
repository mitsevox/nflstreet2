#ifndef GAME_MODULEGROUP_8003450C_H
#define GAME_MODULEGROUP_8003450C_H

#include "game/Module.h"

DECLARE_MODULE(Animintf);
DECLARE_MODULE(AnimScriptMan);
DECLARE_MODULE(Arrow);
DECLARE_MODULE(Ass);
DECLARE_MODULE(AssJoy);
DECLARE_MODULE(Ball);
DECLARE_MODULE(Banner);
DECLARE_MODULE(BigObj);
DECLARE_MODULE(Block);
DECLARE_MODULE(CamGame);
DECLARE_MODULE(CamScript);
DECLARE_MODULE(Catch);
DECLARE_MODULE(CatchUp);
DECLARE_MODULE(Cld);
DECLARE_MODULE(Clock);
DECLARE_MODULE(CoinToss);
DECLARE_MODULE(Effects);
DECLARE_MODULE(Env);
DECLARE_MODULE(GameBrk);
DECLARE_MODULE(GameIntf);
DECLARE_MODULE(GamePlay);
DECLARE_MODULE(GameSkill);
DECLARE_MODULE(HotRt);
DECLARE_MODULE(ID3Read);
DECLARE_MODULE(IGNetEvent);
DECLARE_MODULE(JoyMsg);
DECLARE_MODULE(Light);
DECLARE_MODULE(MiM);
DECLARE_MODULE(Monitor);
DECLARE_MODULE(Particles);
DECLARE_MODULE(Pause);
DECLARE_MODULE(Penalty);
DECLARE_MODULE(PlayArtMem);
DECLARE_MODULE(PlayInfo);
DECLARE_MODULE(PlayTrack);
DECLARE_MODULE(Plyr);
DECLARE_MODULE(PlyrCtrl);
DECLARE_MODULE(PlyrMsg);
DECLARE_MODULE(Practice);
DECLARE_MODULE(Pursuit);
DECLARE_MODULE(RenderBin);
DECLARE_MODULE(Replay);
DECLARE_MODULE(ReplayFrame);
DECLARE_MODULE(ScreenTint);
DECLARE_MODULE(Shadows);
DECLARE_MODULE(SideAvoid);
DECLARE_MODULE(SimpShadow);
DECLARE_MODULE(SndgIG);
DECLARE_MODULE(SndgReplay);
DECLARE_MODULE(Statcoll);
DECLARE_MODULE(Statics);
DECLARE_MODULE(Sub);
DECLARE_MODULE(Trk);
DECLARE_MODULE(ColorStyle);
DECLARE_MODULE(VptMgr);
DECLARE_MODULE(MiniGame);
DECLARE_MODULE(TutorialGame);
DECLARE_MODULE(IGOnline);

class PlayBook : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

    void fn_8003549C(int flag);
    void fn_800355FC();
};

class Turbo : public Module {
public:
    virtual int Init();
    virtual int Shutdown();
    virtual ModuleDependency *GetDependencies();
    virtual ModuleDependency *GetLinks();
    virtual const char *GetName();

    void fn_80035EE0();
};

extern Animintf gAnimintf;
extern AnimScriptMan gAnimScriptMan;
extern Arrow gArrow;
extern Ass gAss;
extern AssJoy gAssJoy;
extern Ball gBall;
extern Banner gBanner;
extern BigObj gBigObj;
extern Block gBlock;
extern CamGame gCamGame;
extern CamScript gCamScript;
extern Catch gCatch;
extern CatchUp gCatchUp;
extern Cld gCld;
extern Clock gClock;
extern CoinToss gCoinToss;
extern Effects gEffects;
extern Env gEnv;
extern GameBrk gGameBrk;
extern GameIntf gGameIntf;
extern GamePlay gGamePlay;
extern GameSkill gGameSkill;
extern HotRt gHotRt;
extern ID3Read gID3Read;
extern IGNetEvent gIGNetEvent;
extern IGOnline gIGOnline;
extern JoyMsg gJoyMsg;
extern Light gLight;
extern MiM gMiM;
extern Monitor gMonitor;
extern Particles gParticles;
extern Pause gPause;
extern Penalty gPenalty;
extern PlayArtMem gPlayArtMem;
extern PlayInfo gPlayInfo;
extern PlayTrack gPlayTrack;
extern PlayBook gPlayBook;
extern Plyr gPlyr;
extern PlyrCtrl gPlyrCtrl;
extern PlyrMsg gPlyrMsg;
extern Practice gPractice;
extern Pursuit gPursuit;
extern RenderBin gRenderBin;
extern Replay gReplay;
extern ReplayFrame gReplayFrame;
extern ScreenTint gScreenTint;
extern Shadows gShadows;
extern SideAvoid gSideAvoid;
extern SimpShadow gSimpShadow;
extern SndgIG gSndgIG;
extern SndgReplay gSndgReplay;
extern Statcoll gStatcoll;
extern Statics gStatics;
extern Sub gSub;
extern Trk gTrk;
extern Turbo gTurbo;
extern ColorStyle gColorStyle;
extern VptMgr gVptMgr;
extern MiniGame gMiniGame;
extern TutorialGame gTutorialGame;

#endif
