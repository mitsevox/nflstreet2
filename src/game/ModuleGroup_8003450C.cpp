#include "game/ModuleGroup_8003450C.h"
#include "game/GameObjList.h"
#include "game/GameState.h"
#include "game/GameVpt.h"
#include "game/InGame.h"
#include "game/ModuleGroup_80033A5C.h"
#include "game/ModuleGroup_8008CC74.h"
#include "game/SndgCrowd.h"
#include "game/cu_8003EC04.h"
#include "game/cu_80041210.h"
#include "game/cu_80064864.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80178D18.h"
#include "game/fn_801FCE10.h"

extern "C" {
extern char lbl_8030A60C[];
extern char lbl_8030C070[];
extern void *lbl_803EA368;
extern void *lbl_803EA554;

void fn_8002B1E4(void);
void fn_8002B2D0(void);
void *fn_8002C8C0(void);
void fn_8002C964(void *p);
void fn_80030B30(void);
void fn_80030BC0(int a);
void fn_800397D0(int a);
void fn_80039890(void);
void fn_80039A1C(void);
int fn_8003DA94(unsigned short count, int a, int b);
int fn_8003DCC0(int a);
void fn_8003E118(void);
void fn_80040558(int a, int b);
void fn_800405F0(int a);
void fn_80040B88(int a);
void fn_80040C90(int a);
void fn_800410FC(void);
void fn_80043AE4(void);
void fn_80044378(void);
void fn_80044B2C(int a);
void fn_80044B50(void);
void fn_800463FC(int a);
void fn_8004787C(void);
void fn_8004A9FC(void);
void fn_8004FF8C(void);
void fn_800502C0(void);
int fn_800543B4(void);
void fn_8006E710(void);
void fn_8006E760(void);
void fn_8006E78C(void);
void fn_80073478(void);
void fn_80073528(void);
unsigned char fn_8007AFDC(int a);
void fn_8008FCB4(int a);
void fn_8008FD88(int a);
void fn_8008FDC0(void);
void fn_80094E80(void);
void fn_80094FE8(void);
void fn_80096954(void *p);
void fn_80096A24(void);
void fn_80099630(void);
void fn_800996D4(void);
void fn_8009AB34(void);
void fn_8009ABC0(void);
void fn_8009D474(int a, int b);
void fn_8009D8CC(int a);
void fn_800A2F48(void);
void fn_800A30B8(void);
void fn_800A70F4(void);
void fn_800A7274(void);
void fn_800ABD1C(void);
void fn_800ABD7C(void);
void fn_800AD634(float a);
void fn_800AD774(void);
void fn_800AEB1C(void);
void fn_800AEB9C(void);
void fn_800AF1BC(int a, int b);
void fn_800AF1FC(void);
void fn_800AFCB8(int a);
void fn_800AFD54(void);
void fn_800B0CFC(void);
void fn_800B0DA0(void);
void fn_800B1478(void);
void fn_800B14B8(void);
void fn_800B21D0(void);
void fn_800B22D4(void);
void fn_800B4A4C(void);
void fn_800B62D8(int a);
void fn_800B63A4(void);
void fn_800B8028(void);
void fn_800B8544(int a);
void fn_800B85C8(void);
void fn_800BA3F0(void);
void fn_800BA570(void);
void fn_800C310C(void);
void fn_800C46B0(int a);
void fn_800C471C(int a);
void fn_800C47EC(void *p);
int fn_800C8704(int *pA, int *pB);
void fn_800C9D6C(unsigned char a, unsigned char b);
void fn_800C9E40(void);
void fn_800C9E4C(unsigned char a, unsigned char b);
void fn_800D7438(void);
void fn_800D750C(void);
void fn_800D77F0(void);
void fn_800EFD70(int a);
void fn_800EFDD8(void);
void fn_800F164C(int a);
void fn_800F16F4(void);
void fn_80118704(void);
void fn_8011876C(void);
void fn_8011DF3C(void);
void fn_8011DF8C(void);
void fn_8011F0D8(void);
void fn_8011F174(void);
void fn_8012055C(int a);
void fn_8012060C(void);
void fn_8013F8D4(void *pObject);
void fn_80142B0C(void);
void fn_80142B68(void);
void fn_80144264(void);
void fn_80144B50(int a);
void fn_80144C6C(int a);
void fn_8014512C(void);
void fn_80145C88(void);
void fn_80145D0C(void);
void fn_80147AE4(int a);
void fn_80147BA8(int a);
void fn_80147EAC(void);
int fn_801485D4(void);
int fn_801485F4(void);
void fn_80148644(void);
int fn_801486A0(void);
int fn_80156704(void);
void fn_8015673C(void);
void fn_80156854(void);
void fn_8015C064(int a);
void fn_8015C0C0(void);
void fn_8015E654(int a);
void fn_8015E6C4(void);
void fn_8015E6C8(void);
void fn_8015E950(int a, int b);
void fn_8015E994(void);
void fn_80160874(int a);
void fn_80160A80(void);
void fn_80160B6C(void);
void fn_801615EC(void *pOwner);
void fn_801616C0(void *pOwner);
void fn_80162D78(void);
void fn_8016781C(void *p);
void fn_80167860(void);
void fn_801679B4(void);
void fn_801681A8(void);
void fn_80168210(void);
void fn_80168264(void);
void fn_80168324(int a, int b, int c, int d, int e, int f, int g, int h);
void fn_80168418(int a, int b, int c, int d, int e, int f, int g);
void fn_801684B8(int a);
void fn_8016B04C(void);
void fn_8016B0AC(void);
void fn_80178B5C(void);
int fn_80178C60(void);
void fn_8017CBD0(void);
void fn_8017CBD4(void);
void fn_8017CDD4(void);
void fn_8017CEB0(void);
void fn_8017EB94(void);
void fn_8017EBF0(void);
void fn_80188B78(int a, int b);
void fn_80188E14(void);
void fn_80188E8C(void);
void fn_8019B25C(int a);
void fn_8019B43C(void);
void fn_801A4650(Object_80228224 *pObject);
void fn_801A4E9C(void);
void fn_801A4FB0(void);
int fn_801F0F18(int a);
void fn_801F2798(const char *pText);
void fn_80228E18(void);
void fn_802363B0(Object_80228224 *pObject);
void fn_802363E0(Object_80228224 *pObject);
}

static ModuleDependency sAnimintfDependencies[] = { &gAnimData, &gGameState, 0 };
Animintf gAnimintf;

ModuleDependency *Animintf::GetDependencies() { return sAnimintfDependencies; }
ModuleDependency *Animintf::GetLinks() { return 0; }
const char *Animintf::GetName() { return "Animintf"; }

int Animintf::Init()
{
    fn_8008FCB4(1);
    fn_8008FDC0();
    return 1;
}

int Animintf::Shutdown()
{
    fn_8008FD88(0);
    return 1;
}

static ModuleDependency sAnimScriptManDependencies[] = { &gGameState, 0 };
AnimScriptMan gAnimScriptMan;

ModuleDependency *AnimScriptMan::GetDependencies() { return sAnimScriptManDependencies; }
ModuleDependency *AnimScriptMan::GetLinks() { return 0; }
const char *AnimScriptMan::GetName() { return "AnimScriptMan"; }

int AnimScriptMan::Init()
{
    fn_80094E80();
    return 1;
}

int AnimScriptMan::Shutdown()
{
    fn_80094FE8();
    return 1;
}

static ModuleDependency sArrowDependencies[] = { &gGameObjList, &gGameState, &gLight, 0 };
Arrow gArrow;

ModuleDependency *Arrow::GetDependencies() { return sArrowDependencies; }
ModuleDependency *Arrow::GetLinks() { return 0; }
const char *Arrow::GetName() { return "Arrow"; }

int Arrow::Init()
{
    fn_8015C064(GameObjList::fn_80028BB4());
    fn_80044B2C(GameObjList::fn_80028BB4());
    return 1;
}

int Arrow::Shutdown()
{
    fn_8015C0C0();
    fn_80044B50();
    return 1;
}

static ModuleDependency sAssDependencies[] = { &gGameState, &gAnimintf, &gAssJoy, 0 };
Ass gAss;

ModuleDependency *Ass::GetDependencies() { return sAssDependencies; }
ModuleDependency *Ass::GetLinks() { return 0; }
const char *Ass::GetName() { return "Ass"; }

int Ass::Init()
{
    fn_800EFD70(33);
    fn_80118704();
    return 1;
}

int Ass::Shutdown()
{
    fn_8011876C();
    fn_800EFDD8();
    return 1;
}

static ModuleDependency sAssJoyDependencies[] = { &gGameState, &gContext, 0 };
AssJoy gAssJoy;

ModuleDependency *AssJoy::GetDependencies() { return sAssJoyDependencies; }
ModuleDependency *AssJoy::GetLinks() { return 0; }
const char *AssJoy::GetName() { return "AssJoy"; }

int AssJoy::Init()
{
    fn_800F164C(10);
    return 1;
}

int AssJoy::Shutdown()
{
    fn_800F16F4();
    return 1;
}

static ModuleDependency sBallDependencies[] = { &gGameObjList, &gGameState, &gLight, &gShadows, &gStaData, &gPlyr, &gCld, &gEffects, &gSimpShadow, &gBigObj, 0 };
Ball gBall;

ModuleDependency *Ball::GetDependencies() { return sBallDependencies; }
ModuleDependency *Ball::GetLinks() { return 0; }
const char *Ball::GetName() { return "Ball"; }

int Ball::Init()
{
    int mode = 1;

    if (fn_801486A0() == 1) {
        mode = 3;
    }
    fn_80137F98(mode);
    fn_80137588(GameObjList::fn_80028BB4());
    fn_800502C0();
    fn_80040B88(GameObjList::fn_80028BB4());
    return 1;
}

int Ball::Shutdown()
{
    fn_8013764C(GameObjList::fn_80028BB4());
    return 1;
}

static ModuleDependency sBannerDependencies[] = { &gGameState, 0 };
Banner gBanner;

ModuleDependency *Banner::GetDependencies() { return sBannerDependencies; }
ModuleDependency *Banner::GetLinks() { return 0; }
const char *Banner::GetName() { return "Banner"; }

int Banner::Init()
{
    fn_8017CDD4();
    return 1;
}

int Banner::Shutdown()
{
    fn_8017CEB0();
    return 1;
}

static ModuleDependency sBigObjDependencies[] = { &gGameState, &gGameObjList, &gSimpShadow, &gEnv, 0 };
BigObj gBigObj;

ModuleDependency *BigObj::GetDependencies() { return sBigObjDependencies; }
ModuleDependency *BigObj::GetLinks() { return 0; }
const char *BigObj::GetName() { return "BigObj"; }

int BigObj::Init()
{
    unsigned short count = fn_800543B4() + 1;

    fn_801F2798("BigObjSetupBigObjectsStart");
    fn_80040558(count, GameObjList::fn_80028BB4());
    fn_801F2798("BigObjSetupBigObjectsFinish");
    fn_801F2798("BObjInfoStateInitStart");
    fn_800413F0(104, 10);
    fn_801F2798("BObjInfoStateInitFinish");
    fn_801F2798("GenObjSetupAnimationsStart");
    fn_8004A9FC();
    fn_801F2798("GenObjSetupAnimationsFinish");
    fn_801F2798("BigObjAddAllObjectsStart");
    fn_80040C90(GameObjList::fn_80028BB4());
    fn_801F2798("BigObjAddAllObjectsFinish");
    return 1;
}

int BigObj::Shutdown()
{
    fn_80041490();
    fn_80228E18();
    fn_800405F0(GameObjList::fn_80028BB4());
    return 1;
}

static ModuleDependency sBlockDependencies[] = { &gGameState, 0 };
Block gBlock;

ModuleDependency *Block::GetDependencies() { return sBlockDependencies; }
ModuleDependency *Block::GetLinks() { return 0; }
const char *Block::GetName() { return "Block"; }

int Block::Init()
{
    fn_8011DF3C();
    return 1;
}

int Block::Shutdown()
{
    fn_8011DF8C();
    return 1;
}

static ModuleDependency sCamGameDependencies[] = { &gGameState, &gGameVpt, &gVptMgr, 0 };
CamGame gCamGame;

ModuleDependency *CamGame::GetDependencies() { return sCamGameDependencies; }
ModuleDependency *CamGame::GetLinks() { return 0; }
const char *CamGame::GetName() { return "CamGame"; }

int CamGame::Init()
{
    fn_8013F8D4(GameVpt::fn_800293A8());
    return 1;
}

int CamGame::Shutdown()
{
    return 1;
}

static ModuleDependency sCamScriptDependencies[] = { &gAnimData, 0 };
CamScript gCamScript;

ModuleDependency *CamScript::GetDependencies() { return sCamScriptDependencies; }
ModuleDependency *CamScript::GetLinks() { return 0; }
const char *CamScript::GetName() { return "CamScript"; }

int CamScript::Init()
{
    fn_80096954(gAnimData.fn_80033AF8());
    return 1;
}

int CamScript::Shutdown()
{
    fn_80096A24();
    return 1;
}

static ModuleDependency sCatchDependencies[] = { &gGameState, &gAnimintf, 0 };
Catch gCatch;

ModuleDependency *Catch::GetDependencies() { return sCatchDependencies; }
ModuleDependency *Catch::GetLinks() { return 0; }
const char *Catch::GetName() { return "Catch"; }

int Catch::Init()
{
    fn_80099630();
    return 1;
}

int Catch::Shutdown()
{
    fn_800996D4();
    return 1;
}

static ModuleDependency sCatchUpDependencies[] = { &gGameState, 0 };
CatchUp gCatchUp;

ModuleDependency *CatchUp::GetDependencies() { return sCatchUpDependencies; }
ModuleDependency *CatchUp::GetLinks() { return 0; }
const char *CatchUp::GetName() { return "CatchUp"; }

int CatchUp::Init()
{
    fn_8009AB34();
    return 1;
}

int CatchUp::Shutdown()
{
    fn_8009ABC0();
    return 1;
}

static void *sCldDependencies[] = { 0 };
Cld gCld;

ModuleDependency *Cld::GetDependencies() { return (ModuleDependency *)sCldDependencies; }
ModuleDependency *Cld::GetLinks() { return 0; }
const char *Cld::GetName() { return "Cld"; }

int Cld::Init()
{
    fn_8003ED30(100);
    fn_80142B0C();
    return 1;
}

int Cld::Shutdown()
{
    fn_8003EDB8();
    fn_80142B68();
    return 1;
}

static ModuleDependency sClockDependencies[] = { &gScrmRule, &gMiniGame, &gTutorialGame, &gGameState, 0 };
Clock gClock;

ModuleDependency *Clock::GetDependencies() { return sClockDependencies; }
ModuleDependency *Clock::GetLinks() { return 0; }
const char *Clock::GetName() { return "Clock"; }

int Clock::Init()
{
    fn_8009D474(fn_80178C60(), 60);
    return 1;
}

int Clock::Shutdown()
{
    fn_8009D8CC(2);
    return 1;
}

static ModuleDependency sCoinTossDependencies[] = { &gGameState, 0 };
CoinToss gCoinToss;

ModuleDependency *CoinToss::GetDependencies() { return sCoinTossDependencies; }
ModuleDependency *CoinToss::GetLinks() { return 0; }
const char *CoinToss::GetName() { return "CoinToss"; }

int CoinToss::Init()
{
    fn_8017EB94();
    return 1;
}

int CoinToss::Shutdown()
{
    fn_8017EBF0();
    return 1;
}

static ModuleDependency sEffectsDependencies[] = { &gParticles, 0 };
Effects gEffects;

ModuleDependency *Effects::GetDependencies() { return sEffectsDependencies; }
ModuleDependency *Effects::GetLinks() { return 0; }
const char *Effects::GetName() { return "Effects"; }

int Effects::Init()
{
    fn_80145C88();
    return 1;
}

int Effects::Shutdown()
{
    fn_80145D0C();
    return 1;
}

static ModuleDependency sEnvDependencies[] = { &gGameObjList, &gGRand, &gStaData, &gGameVpt, &gScrmRule, &gScreenTint, 0 };
Env gEnv;

ModuleDependency *Env::GetDependencies() { return sEnvDependencies; }
ModuleDependency *Env::GetLinks() { return 0; }
const char *Env::GetName() { return "Env"; }

int Env::Init()
{
    fn_801F2798("EnvMgrInitStart");
    fn_800A2F48();
    fn_801F2798("EnvMgrInitFinish");
    fn_801615EC((void *)GameObjList::fn_80028BB4());
    fn_801F2798("EnvObjAddObjTypeStart");
    fn_800463FC(GameObjList::fn_80028BB4());
    fn_801F2798("EnvObjAddObjTypeFinish");
    fn_801F2798("FldObjAddObjTypeStart");
    fn_8019B25C(GameObjList::fn_80028BB4());
    fn_801F2798("FldObjAddObjTypeFinish");
    fn_80043AE4();
    fn_800C47EC(lbl_803EA554);
    fn_8004787C();
    fn_80178B5C();
    return 1;
}

int Env::Shutdown()
{
    fn_800A30B8();
    fn_801616C0((void *)GameObjList::fn_80028BB4());
    return 1;
}

static ModuleDependency sGameBrkDependencies[] = { &gGameState, &gEffects, 0 };
GameBrk gGameBrk;

ModuleDependency *GameBrk::GetDependencies() { return sGameBrkDependencies; }
ModuleDependency *GameBrk::GetLinks() { return 0; }
const char *GameBrk::GetName() { return "GameBrk"; }

int GameBrk::Init()
{
    fn_800A70F4();
    return 1;
}

int GameBrk::Shutdown()
{
    fn_800A7274();
    return 1;
}

static ModuleDependency sGameIntfDependencies[] = { &gGameState, 0 };
GameIntf gGameIntf;

ModuleDependency *GameIntf::GetDependencies() { return sGameIntfDependencies; }
ModuleDependency *GameIntf::GetLinks() { return 0; }
const char *GameIntf::GetName() { return "GameIntf"; }

int GameIntf::Init()
{
    fn_80147EAC();
    return 1;
}

int GameIntf::Shutdown()
{
    return 1;
}

static ModuleDependency sGamePlayDependencies[] = { &gGameState, &gGameObjList, &gIGMisc, &gUIS, &gCamScript, &gPenalty, &gScrmRule, &gJoyMsg, &gGRand, &gStatics, &gClock, &gGameBrk, &gPlyr, &gBall, &gPlyrCtrl, &gSndgIG, &gPursuit, &gPlayInfo, &gAudmon, &gAnimintf, &gAss, &gVptMgr, lbl_8030C070, 0 };
GamePlay gGamePlay;

ModuleDependency *GamePlay::GetDependencies() { return sGamePlayDependencies; }
ModuleDependency *GamePlay::GetLinks() { return 0; }
const char *GamePlay::GetName() { return "GamePlay"; }

int GamePlay::Init()
{
    fn_800AD634(0.0f);
    return 1;
}

int GamePlay::Shutdown()
{
    fn_800AD774();
    return 1;
}

static ModuleDependency sGameSkillDependencies[] = { &gGameState, &gTutorialGame, 0 };
GameSkill gGameSkill;

ModuleDependency *GameSkill::GetDependencies() { return sGameSkillDependencies; }
ModuleDependency *GameSkill::GetLinks() { return 0; }
const char *GameSkill::GetName() { return "GameSkill"; }

int GameSkill::Init()
{
    fn_800ABD1C();
    return 1;
}

int GameSkill::Shutdown()
{
    fn_800ABD7C();
    return 1;
}

static ModuleDependency sHotRtDependencies[] = { &gGameState, 0 };
HotRt gHotRt;

ModuleDependency *HotRt::GetDependencies() { return sHotRtDependencies; }
ModuleDependency *HotRt::GetLinks() { return 0; }
const char *HotRt::GetName() { return "HotRt"; }

int HotRt::Init()
{
    fn_800AEB1C();
    return 1;
}

int HotRt::Shutdown()
{
    fn_800AEB9C();
    return 1;
}

static void *sID3ReadDependencies[] = { 0 };
ID3Read gID3Read;

ModuleDependency *ID3Read::GetDependencies() { return (ModuleDependency *)sID3ReadDependencies; }
ModuleDependency *ID3Read::GetLinks() { return 0; }
const char *ID3Read::GetName() { return "ID3Read"; }

int ID3Read::Init()
{
    fn_800AF1BC(1, 2);
    return 1;
}

int ID3Read::Shutdown()
{
    fn_800AF1FC();
    return 1;
}

static ModuleDependency sIGNetEventDependencies[] = { &gGameState, &gGRand, &gDbgPrint, 0 };
IGNetEvent gIGNetEvent;

ModuleDependency *IGNetEvent::GetDependencies() { return sIGNetEventDependencies; }
ModuleDependency *IGNetEvent::GetLinks() { return 0; }
const char *IGNetEvent::GetName() { return "IGNetEvent"; }

int IGNetEvent::Init()
{
    return 1;
}

int IGNetEvent::Shutdown()
{
    return 1;
}

static void *sIGOnlineDependencies[] = { 0 };
IGOnline gIGOnline;

ModuleDependency *IGOnline::GetDependencies() { return (ModuleDependency *)sIGOnlineDependencies; }
ModuleDependency *IGOnline::GetLinks() { return 0; }
const char *IGOnline::GetName() { return "IGOnline"; }

int IGOnline::Init()
{
    return 1;
}

int IGOnline::Shutdown()
{
    return 1;
}

static ModuleDependency sJoyMsgDependencies[] = { &gGameState, 0 };
JoyMsg gJoyMsg;

ModuleDependency *JoyMsg::GetDependencies() { return sJoyMsgDependencies; }
ModuleDependency *JoyMsg::GetLinks() { return 0; }
const char *JoyMsg::GetName() { return "JoyMsg"; }

int JoyMsg::Init()
{
    fn_800AFCB8(3);
    return 1;
}

int JoyMsg::Shutdown()
{
    fn_800AFD54();
    return 1;
}

static ModuleDependency sLightDependencies[] = { &gGameVpt, &gGameState, &gEnv, 0 };
Light gLight;

ModuleDependency *Light::GetDependencies() { return sLightDependencies; }
ModuleDependency *Light::GetLinks() { return 0; }
const char *Light::GetName() { return "Light"; }

int Light::Init()
{
    fn_802363B0(GameVpt::fn_800293A8());
    fn_8019B43C();
    return 1;
}

int Light::Shutdown()
{
    fn_802363E0(GameVpt::fn_800293A8());
    return 1;
}

static ModuleDependency sMiMDependencies[] = { &gGameState, 0 };
MiM gMiM;

ModuleDependency *MiM::GetDependencies() { return sMiMDependencies; }
ModuleDependency *MiM::GetLinks() { return 0; }
const char *MiM::GetName() { return "MiM"; }

int MiM::Init()
{
    fn_800B0CFC();
    return 1;
}

int MiM::Shutdown()
{
    fn_800B0DA0();
    return 1;
}

static ModuleDependency sMonitorDependencies[] = { &gGameState, 0 };
Monitor gMonitor;

ModuleDependency *Monitor::GetDependencies() { return sMonitorDependencies; }
ModuleDependency *Monitor::GetLinks() { return 0; }
const char *Monitor::GetName() { return "Monitor"; }

int Monitor::Init()
{
    fn_800B1478();
    return 1;
}

int Monitor::Shutdown()
{
    fn_800B14B8();
    return 1;
}

static ModuleDependency sParticlesDependencies[] = { &gGameState, &gGameObjList, &gGameVpt, &gEnv, &gStaData, &gBigObj, 0 };
Particles gParticles;

ModuleDependency *Particles::GetDependencies() { return sParticlesDependencies; }
ModuleDependency *Particles::GetLinks() { return 0; }
const char *Particles::GetName() { return "Particles"; }

int Particles::Init()
{
    fn_80144B50(GameObjList::fn_80028BB4());
    return 1;
}

int Particles::Shutdown()
{
    fn_80144C6C(GameObjList::fn_80028BB4());
    return 1;
}

static ModuleDependency sPauseDependencies[] = { &gRumble, &gPractice, &gReplay, &gClock, &gPenalty, &gScrmRule, &gGamePlay, &gCelebration, 0 };
Pause gPause;

ModuleDependency *Pause::GetDependencies() { return sPauseDependencies; }
ModuleDependency *Pause::GetLinks() { return 0; }
const char *Pause::GetName() { return "Pause"; }

int Pause::Init()
{
    fn_80064E18();
    return 1;
}

int Pause::Shutdown()
{
    fn_80064EA4();
    return 1;
}

static ModuleDependency sPenaltyDependencies[] = { &gGameState, 0 };
Penalty gPenalty;

ModuleDependency *Penalty::GetDependencies() { return sPenaltyDependencies; }
ModuleDependency *Penalty::GetLinks() { return 0; }
const char *Penalty::GetName() { return "Penalty"; }

int Penalty::Init()
{
    fn_800B21D0();
    return 1;
}

int Penalty::Shutdown()
{
    fn_800B22D4();
    return 1;
}

static ModuleDependency sPlayArtMemDependencies[] = { &gGameState, &gIGMisc, &gGLIB, 0 };
PlayArtMem gPlayArtMem;

ModuleDependency *PlayArtMem::GetDependencies() { return sPlayArtMemDependencies; }
ModuleDependency *PlayArtMem::GetLinks() { return 0; }
const char *PlayArtMem::GetName() { return "PlayArtMem"; }

int PlayArtMem::Init()
{
    fn_8016781C(gIGMisc.mData.mp);
    return 1;
}

int PlayArtMem::Shutdown()
{
    fn_80167860();
    return 1;
}

static ModuleDependency sPlayInfoDependencies[] = { &gGameState, &gBall, 0 };
PlayInfo gPlayInfo;

ModuleDependency *PlayInfo::GetDependencies() { return sPlayInfoDependencies; }
ModuleDependency *PlayInfo::GetLinks() { return 0; }
const char *PlayInfo::GetName() { return "PlayInfo"; }

int PlayInfo::Init()
{
    fn_8011F0D8();
    return 1;
}

int PlayInfo::Shutdown()
{
    fn_8011F174();
    return 1;
}

static ModuleDependency sPlayTrackDependencies[] = { &gGameState, 0 };
PlayTrack gPlayTrack;

ModuleDependency *PlayTrack::GetDependencies() { return sPlayTrackDependencies; }
ModuleDependency *PlayTrack::GetLinks() { return 0; }
const char *PlayTrack::GetName() { return "PlayTrack"; }

int PlayTrack::Init()
{
    fn_8016B04C();
    return 1;
}

int PlayTrack::Shutdown()
{
    fn_8016B0AC();
    return 1;
}

void PlayBook::fn_8003549C(int flag)
{
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;

    fn_800C8704(&a, &b);
    if (fn_8002892C()) {
        c = 59;
        d = 59;
        e = 59;
        f = 59;
    } else {
        fn_801FCE10(0, "select 'IPHG' into \x85 and 'IPAG' into \x85 and 'PDHG' into \x85 and 'PDAG' into \x85 from 'FNIG'\n", &c, &d, &e, &f);
    }
    if (flag) {
        fn_80168324((int)gIGMisc.mData.mp, a, b, c, d, e, f, 1);
    } else {
        fn_80168418(a, b, c, d, e, f, 1);
    }
}

static ModuleDependency sPlayBookDependencies[] = { &gGameState, &gPlyr, &gIGMisc, 0 };
static ModuleDependency sPlayBookLinks[] = { &gFEPlyBk, 0 };
PlayBook gPlayBook;

ModuleDependency *PlayBook::GetDependencies() { return sPlayBookDependencies; }
ModuleDependency *PlayBook::GetLinks() { return sPlayBookLinks; }
const char *PlayBook::GetName() { return "PlayBook"; }

int PlayBook::Init()
{
    fn_801681A8();
    fn_80168210();
    fn_8003549C(1);
    fn_801679B4();
    fn_80168264();
    return 1;
}

int PlayBook::Shutdown()
{
    fn_801684B8(1);
    return 1;
}

void PlayBook::fn_800355FC()
{
    fn_8003549C(0);
}

static ModuleDependency sPlyrDependencies[] = { &gGRender, &gAnimData, &gGameObjList, &gGameVpt, &gGameState, &gCld, &gEffects, &gLight, &gShadows, &gSimpShadow, &gParticles, &gAss, &gBlock, &gCatch, &gAudmon, &gBigObj, &gUIS, 0 };
Plyr gPlyr;

ModuleDependency *Plyr::GetDependencies() { return sPlyrDependencies; }
ModuleDependency *Plyr::GetLinks() { return 0; }
const char *Plyr::GetName() { return "Plyr"; }

int Plyr::Init()
{
    fn_801F2798("PlyrObjsInitStart");
    fn_80160874(14);
    fn_80160A80();
    fn_8015E654(1);
    fn_8015E6C4();
    fn_8015E950(1, 1);
    fn_8003DA94(14, GameObjList::fn_80028BB4(), 0);
    fn_8015E994();
    fn_801F2798("PlyrObjsInitFinish");
    fn_801F2798("PlaStateInitStart");
    fn_800397D0(14);
    fn_801F2798("PlaStateInitFinish");
    fn_80039A1C();
    fn_801A4650(GameVpt::fn_800293A8());
    fn_8004FF8C();
    return 1;
}

int Plyr::Shutdown()
{
    fn_80039890();
    fn_8003DCC0(GameObjList::fn_80028BB4());
    fn_8015E6C8();
    fn_80160B6C();
    return 1;
}

static ModuleDependency sPlyrCtrlDependencies[] = { &gAssJoy, 0 };
PlyrCtrl gPlyrCtrl;

ModuleDependency *PlyrCtrl::GetDependencies() { return sPlyrCtrlDependencies; }
ModuleDependency *PlyrCtrl::GetLinks() { return 0; }
const char *PlyrCtrl::GetName() { return "PlyrCtrl"; }

int PlyrCtrl::Init()
{
    fn_800B62D8(10);
    fn_800B8028();
    return 1;
}

int PlyrCtrl::Shutdown()
{
    fn_800B63A4();
    return 1;
}

static void *sPlyrMsgDependencies[] = { 0 };
PlyrMsg gPlyrMsg;

ModuleDependency *PlyrMsg::GetDependencies() { return (ModuleDependency *)sPlyrMsgDependencies; }
ModuleDependency *PlyrMsg::GetLinks() { return 0; }
const char *PlyrMsg::GetName() { return "PlyrMsg"; }

int PlyrMsg::Init()
{
    fn_800B8544(10);
    return 1;
}

int PlyrMsg::Shutdown()
{
    fn_800B85C8();
    return 1;
}

static ModuleDependency sPracticeDependencies[] = { &gGameState, &gBall, 0 };
Practice gPractice;

ModuleDependency *Practice::GetDependencies() { return sPracticeDependencies; }
ModuleDependency *Practice::GetLinks() { return 0; }
const char *Practice::GetName() { return "Practice"; }

int Practice::Init()
{
    fn_800BA3F0();
    return 1;
}

int Practice::Shutdown()
{
    fn_800BA570();
    return 1;
}

static ModuleDependency sPursuitDependencies[] = { &gGameState, 0 };
Pursuit gPursuit;

ModuleDependency *Pursuit::GetDependencies() { return sPursuitDependencies; }
ModuleDependency *Pursuit::GetLinks() { return 0; }
const char *Pursuit::GetName() { return "Pursuit"; }

int Pursuit::Init()
{
    fn_8012055C(7);
    return 1;
}

int Pursuit::Shutdown()
{
    fn_8012060C();
    return 1;
}

static ModuleDependency sRenderBinDependencies[] = { &gGameObjList, &gGameState, 0 };
RenderBin gRenderBin;

ModuleDependency *RenderBin::GetDependencies() { return sRenderBinDependencies; }
ModuleDependency *RenderBin::GetLinks() { return 0; }
const char *RenderBin::GetName() { return "RenderBin"; }

int RenderBin::Init()
{
    return 1;
}

int RenderBin::Shutdown()
{
    return 1;
}

static ModuleDependency sReplayDependencies[] = { &gGameStateActivate, &gReplayFrame, 0 };
Replay gReplay;

ModuleDependency *Replay::GetDependencies() { return sReplayDependencies; }
ModuleDependency *Replay::GetLinks() { return 0; }
const char *Replay::GetName() { return "Replay"; }

int Replay::Init()
{
    GameState::fn_8002900C();
    lbl_803EA368 = fn_8002C8C0();
    return 1;
}

int Replay::Shutdown()
{
    fn_801F0F18(0);
    fn_8002C964(lbl_803EA368);
    lbl_803EA368 = 0;
    return 1;
}

static void *sReplayFrameDependencies[] = { 0 };
ReplayFrame gReplayFrame;

ModuleDependency *ReplayFrame::GetDependencies() { return (ModuleDependency *)sReplayFrameDependencies; }
ModuleDependency *ReplayFrame::GetLinks() { return 0; }
const char *ReplayFrame::GetName() { return "ReplayFrame"; }

int ReplayFrame::Init()
{
    fn_80030BC0(0);
    fn_8013740C();
    fn_80162D78();
    fn_8003E118();
    fn_800410FC();
    fn_80044378();
    fn_8006E78C();
    fn_8014512C();
    fn_800B4A4C();
    fn_800D77F0();
    fn_80030B30();
    return 1;
}

int ReplayFrame::Shutdown()
{
    return 1;
}

static ModuleDependency sScreenTintDependencies[] = { &gGameState, &gGameObjList, &gGameVpt, &gStaData, 0 };
ScreenTint gScreenTint;

ModuleDependency *ScreenTint::GetDependencies() { return sScreenTintDependencies; }
ModuleDependency *ScreenTint::GetLinks() { return 0; }
const char *ScreenTint::GetName() { return "ScreenTint"; }

int ScreenTint::Init()
{
    fn_80147AE4(GameObjList::fn_80028BB4());
    return 1;
}

int ScreenTint::Shutdown()
{
    fn_80147BA8(GameObjList::fn_80028BB4());
    return 1;
}

static ModuleDependency sShadowsDependencies[] = { &gGameObjList, &gGameState, &gLight, 0 };
Shadows gShadows;

ModuleDependency *Shadows::GetDependencies() { return sShadowsDependencies; }
ModuleDependency *Shadows::GetLinks() { return 0; }
const char *Shadows::GetName() { return "Shadows"; }

int Shadows::Init()
{
    return 1;
}

int Shadows::Shutdown()
{
    return 1;
}

static ModuleDependency sSideAvoidDependencies[] = { &gGameState, 0 };
SideAvoid gSideAvoid;

ModuleDependency *SideAvoid::GetDependencies() { return sSideAvoidDependencies; }
ModuleDependency *SideAvoid::GetLinks() { return 0; }
const char *SideAvoid::GetName() { return "SideAvoid"; }

int SideAvoid::Init()
{
    fn_800C310C();
    return 1;
}

int SideAvoid::Shutdown()
{
    return 1;
}

static ModuleDependency sSimpShadowDependencies[] = { &gGameState, &gGRender, &gStaData, 0 };
SimpShadow gSimpShadow;

ModuleDependency *SimpShadow::GetDependencies() { return sSimpShadowDependencies; }
ModuleDependency *SimpShadow::GetLinks() { return 0; }
const char *SimpShadow::GetName() { return "SimpShadow"; }

int SimpShadow::Init()
{
    fn_801A4E9C();
    return 1;
}

int SimpShadow::Shutdown()
{
    fn_801A4FB0();
    return 1;
}

static ModuleDependency sSndgIGDependencies[] = { &gPractice, &gUIS, &gMonitor, lbl_8030A60C, &gSndgCrowd, &gMiniGame, 0 };
SndgIG gSndgIG;

ModuleDependency *SndgIG::GetDependencies() { return sSndgIGDependencies; }
ModuleDependency *SndgIG::GetLinks() { return 0; }
const char *SndgIG::GetName() { return "SndgIG"; }

int SndgIG::Init()
{
    fn_80073478();
    return 1;
}

int SndgIG::Shutdown()
{
    fn_80073528();
    return 1;
}

static ModuleDependency sSndgReplayDependencies[] = { &gGameState, 0 };
SndgReplay gSndgReplay;

ModuleDependency *SndgReplay::GetDependencies() { return sSndgReplayDependencies; }
ModuleDependency *SndgReplay::GetLinks() { return 0; }
const char *SndgReplay::GetName() { return "SndgReplay"; }

int SndgReplay::Init()
{
    fn_8006E710();
    return 1;
}

int SndgReplay::Shutdown()
{
    fn_8006E760();
    return 1;
}

static ModuleDependency sStatcollDependencies[] = { &gGameState, 0 };
Statcoll gStatcoll;

ModuleDependency *Statcoll::GetDependencies() { return sStatcollDependencies; }
ModuleDependency *Statcoll::GetLinks() { return 0; }
const char *Statcoll::GetName() { return "Statcoll"; }

int Statcoll::Init()
{
    fn_80144264();
    return 1;
}

int Statcoll::Shutdown()
{
    return 1;
}

static ModuleDependency sStaticsDependencies[] = { &gGRender, &gGameObjList, &gGameState, &gLight, &gStaData, &gShadows, &gSimpShadow, &gPractice, &gEnv, &gPlyrCtrl, 0 };
Statics gStatics;

ModuleDependency *Statics::GetDependencies() { return sStaticsDependencies; }
ModuleDependency *Statics::GetLinks() { return 0; }
const char *Statics::GetName() { return "Statics"; }

int Statics::Init()
{
    fn_801F2798("StaticModelInitStart");
    fn_800C46B0(GameObjList::fn_80028BB4());
    fn_801F2798("StaticModelInitFinish");
    return 1;
}

int Statics::Shutdown()
{
    fn_80228E18();
    fn_800C471C(GameObjList::fn_80028BB4());
    return 1;
}

static void *sSubDependencies[] = { 0 };
Sub gSub;

ModuleDependency *Sub::GetDependencies() { return (ModuleDependency *)sSubDependencies; }
ModuleDependency *Sub::GetLinks() { return 0; }
const char *Sub::GetName() { return "Sub"; }

int Sub::Init()
{
    fn_8017CBD0();
    return 1;
}

int Sub::Shutdown()
{
    fn_8017CBD4();
    return 1;
}

static ModuleDependency sTrkDependencies[] = { &gGameState, &gGameBrk, &gMiniGame, 0 };
Trk gTrk;

ModuleDependency *Trk::GetDependencies() { return sTrkDependencies; }
ModuleDependency *Trk::GetLinks() { return 0; }
const char *Trk::GetName() { return "Trk"; }

int Trk::Init()
{
    fn_800D7438();
    return 1;
}

int Trk::Shutdown()
{
    fn_800D750C();
    return 1;
}

static void fn_80035DA0(unsigned char *pA, unsigned char *pB)
{
    unsigned char a;
    unsigned char b;

    switch (fn_801486A0()) {
    case 0:
    case 1:
        a = fn_80178D70(0);
        b = fn_80178D70(1);
        break;
    case 2:
        a = b = fn_80178D70(0);
        break;
    default:
        b = fn_8007AFDC(0) > fn_8007AFDC(1) ? fn_8007AFDC(0) : fn_8007AFDC(1);
        if (b <= 2) {
            a = b = 2;
        } else {
            a = b;
        }
        break;
    }
    *pA = a;
    *pB = b;
}

static ModuleDependency sTurboDependencies[] = { &gGameState, 0 };
Turbo gTurbo;

ModuleDependency *Turbo::GetDependencies() { return sTurboDependencies; }
ModuleDependency *Turbo::GetLinks() { return 0; }
const char *Turbo::GetName() { return "Turbo"; }

int Turbo::Init()
{
    unsigned char a;
    unsigned char b;

    fn_80035DA0(&a, &b);
    fn_800C9D6C(a, b);
    return 1;
}

int Turbo::Shutdown()
{
    fn_800C9E40();
    return 1;
}

void Turbo::fn_80035EE0()
{
    unsigned char a;
    unsigned char b;

    fn_80035DA0(&a, &b);
    fn_800C9E4C(a, b);
}

static void *sColorStyleDependencies[] = { 0 };
ColorStyle gColorStyle;

ModuleDependency *ColorStyle::GetDependencies() { return (ModuleDependency *)sColorStyleDependencies; }
ModuleDependency *ColorStyle::GetLinks() { return 0; }
const char *ColorStyle::GetName() { return "ColorStyle"; }

int ColorStyle::Init()
{
    int a;
    int b;

    fn_800C8704(&a, &b);
    fn_80188E14();
    fn_80188B78(a, b);
    return 1;
}

int ColorStyle::Shutdown()
{
    fn_80228E18();
    fn_80188E8C();
    return 1;
}

static ModuleDependency sVptMgrDependencies[] = { &gGameState, 0 };
VptMgr gVptMgr;

ModuleDependency *VptMgr::GetDependencies() { return sVptMgrDependencies; }
ModuleDependency *VptMgr::GetLinks() { return 0; }
const char *VptMgr::GetName() { return "VptMgr"; }

int VptMgr::Init()
{
    fn_8002B1E4();
    return 1;
}

int VptMgr::Shutdown()
{
    fn_8002B2D0();
    return 1;
}

static ModuleDependency sMiniGameDependencies[] = { &gGameState, &gEnv, &gPlyrCtrl, 0 };
MiniGame gMiniGame;

ModuleDependency *MiniGame::GetDependencies() { return sMiniGameDependencies; }
ModuleDependency *MiniGame::GetLinks() { return 0; }
const char *MiniGame::GetName() { return "MiniGame"; }

int MiniGame::Init()
{
    if (fn_801485D4()) {
        fn_801485F4();
    }
    return 1;
}

int MiniGame::Shutdown()
{
    if (fn_801485D4()) {
        fn_80148644();
    }
    return 1;
}

static ModuleDependency sTutorialGameDependencies[] = { &gGameState, &gEnv, &gTrk, 0 };
TutorialGame gTutorialGame;

ModuleDependency *TutorialGame::GetDependencies() { return sTutorialGameDependencies; }
ModuleDependency *TutorialGame::GetLinks() { return 0; }
const char *TutorialGame::GetName() { return "TutorialGame"; }

int TutorialGame::Init()
{
    if (fn_80156704()) {
        fn_8015673C();
    }
    return 1;
}

int TutorialGame::Shutdown()
{
    if (fn_80156704()) {
        fn_80156854();
    }
    return 1;
}
