/* @HEADER@ */

#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"
#include "game/Class_80148A58.h"
#include "game/Ball.h"
#include "game/fn_80178D18.h"
#include "game/AutoDepth.h"
#include "game/AudmonEvent.h"
#include "game/fn_8009D990.h"
#include "game/fn_800B65A0.h"
#include "game/SyncRandGetRange.h"
#include "game/StyleTracker.h"
#include "game/TDbCompilePerformOp.h"
#include "game/GameModeType.h"
#include <string.h>
#include "game/fn_8021D7B8.h"
#include "game/PauseMenu.h"
#include "game/LivePlayPhase.h"
#include "game/Class_80297B50.h"
#include "game/Class_80297B90.h"
#include "game/PreGamePhase.h"
#include "game/PostPlayPhase.h"
#include "game/PreSnapPhase.h"
#include "game/ScrmRuleSet.h"
#include "game/Object_8008044C.h"
#include "game/GameOptions.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80218FC4.h"
#include "game/Object_8017886C.h"
#include "game/GameCamera.h"
#include "game/cammain.h"
#include "game/Record_800B15FC.h"
#include "game/fn_80177FE0.h"
#include "game/Vec2Distance.h"
#include "game/fn_801D2B7C.h"
#include "game/SyncStateRegister.h"
#include "game/DbTableCursorInline.h"

struct Vector_80039F5C;
struct Point_8017886C;
struct Block_80170E64;
class Record_8005CE10;

struct PlaybookTeamView {
    char mUnknown0[0x40];
    int mUnknown40;
};

struct Stats_8005C844 {
    Object_80039F5C *mpPlayers[3];
    int mValues[4];
};

struct Stats_8005CAE4 {
    Object_80039F5C *mpPlayers[4];
    int mValues[4];
};

struct TextChoices_802DDC20 {
    unsigned char mCount;
    char mUnknown1[3];
    const char *mpText[5];
};

struct Info_8014F3E4 {
    Object_80039F5C *mpUnknown0;
    unsigned int mUnknown4;
    unsigned int mUnknown8;
    unsigned int mUnknown12;
    unsigned char mUnknown16;
};

struct MiniGameSlotInfo_t {
    MiniGameSlotInfo_t() : mpObject(0), mUnknown4(0), mUnknown12(0), mUnknown16(0), mUnknown20(0xFF) {}
    Object_80039F5C *mpObject;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
};

struct Entry_8015005C {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknown10;
    unsigned char mUnknown12;
    char mUnknown13;
    unsigned short mUnknown14;
    unsigned short mUnknown16;
    char mUnknown18[2];
};

struct Table_8015005C {
    Entry_8015005C mEntries[4];
    Vector_80039F5C mUnknown80;
    Point_8017886C mUnknown92[3];
    unsigned char mUnknown116;
    unsigned char mUnknown117;
    unsigned char mCount;
    unsigned char mUnknown119;
    int mUnknown120;
    unsigned char mUnknown124;
    unsigned char mUnknown125;
    unsigned char mUnknown126;
};

struct Score_801531C4 {
    int mUnknown0[2];
    int mUnknown8;
    unsigned int mUnknown12;
    unsigned int mUnknown16;
    unsigned short mUnknown20[2];
    unsigned short mUnknown24[2];
    unsigned short mUnknown28[2];
    unsigned char mUnknown32;
};

class Record_8005CE10 {
public:
    Record_8005CE10() : mOrdinal(0), mEvent(11), mPlayer(32767), mConversion(11), mOther(32767), mFlag(0) {}
    virtual ~Record_8005CE10();
    unsigned int mOrdinal;
    unsigned int mEvent;
    int mPlayer;
    int mConversion;
    int mOther;
    unsigned char mFlag;
};

class Class_802A2DB8;
class Class_802A2C90;
class Class_802A2B68;
class Class_802A2A40;
class Class_802A2918;
class Class_802A27F0;
class Class_802A2788;
class Class_802A2748;
class Class_802A26D8;
class Class_802A26A0;
class Class_802A2618;
class Class_802A2560;
class Class_802A24F8;
struct States_802A2DB8;
class Class_802A2490;
class Class_802A2450;
class Class_802A23E0;
class Class_802A23A8;
class Class_802A2320;
class Class_802A2268;
class Class_802A2200;
class Block_802A21E8;
class Class_802A2130;
class Class_802A20C8;
class Class_802A2058;
class Class_802A2020;
class Class_802A1F90;
class Record_8014F104;
class Class_802A1F10;
class Block_8014F104;
class Class_802A1E38;
class Class_802A1DC8;
class Class_802A1D58;
class Class_802A1D20;
class Class_802A1C98;
class Class_802A1C30;
struct Object_8015005C;
class Class_802A1BC8;
class Class_802A1B58;
class Class_802A1B18;
class Class_802A1AE0;
class Class_802A1A58;
class Class_802A19F0;
class Class_802A1930;
struct Rules_801531C4;
class Class_802A18C8;
class Class_802A1860;
class Class_802A17A8;
class Block_80156400;

extern Class_802A2918 lbl_8031BDD4;

class Class_802A2DB8 : public Class_80148A58 {
public:
    Class_802A2DB8();
    virtual ~Class_802A2DB8();
    virtual void vfn_01();
    virtual void vfn_02();
    virtual int vfn_05(int team);
    virtual int vfn_08(int a);
    virtual void vfn_10(int value, int *pList, int *pIds);
    virtual void vfn_11(int value, int *pList, int *pIds, unsigned int count, int slot);
    virtual int vfn_21();
    virtual int vfn_32(int team, int kind);
    virtual int vfn_33(int kind, int team);

    States_802A2DB8 *mpUnknown1C;
};

class Class_802A2C90 : public Class_80148A58 {
public:
    Class_802A2C90();
    virtual ~Class_802A2C90() { }
    virtual void vfn_01();
    virtual void vfn_02();
    virtual int vfn_03();
    virtual unsigned int vfn_04(int team);
    virtual int vfn_05(int team);
    virtual unsigned int vfn_06();
    virtual void vfn_07(int a, int b);
    virtual int vfn_08(int a);
    virtual void vfn_10(int value, int *pList, int *pIds);
    virtual void vfn_11(int value, int * list, int * ids, unsigned int count, int b);
    virtual void vfn_14();
    virtual int vfn_32(int team, int kind);
    virtual int vfn_33(int kind, int team);

    Block_802A21E8 *mpUnknown1C;
    int mUnknown20;
};

class Class_802A2B68 : public Class_80148A58 {
public:
    Class_802A2B68();
    void fn_8014DA90();
    virtual ~Class_802A2B68() { }
    virtual void vfn_01();
    virtual void vfn_02();
    virtual int vfn_05(int team);
    virtual void vfn_10(int value, int *pList, int *pIds);
    virtual void vfn_11(int value, int *pList, int *pIds, unsigned int a, int b);
    virtual void vfn_12();
    virtual int vfn_13();
    virtual int vfn_21();
    virtual int vfn_26(int team, int index, Object_80039F5C *pPlayer, int kind);
    virtual int vfn_30(int kind, int team, int index, Object_80039F5C *pPlayer);
    virtual int vfn_31(int kind, int team, int index, Object_80039F5C *pPlayer, int threshold, int mode);

    Block_8014F104 *mpUnknown1C;
};

class Class_802A2A40 : public Class_80148A58 {
public:
    Class_802A2A40() : mpUnknown1C(0) {}
    virtual ~Class_802A2A40() { }
    virtual void vfn_01();
    virtual void vfn_02();
    virtual int vfn_08(int a);

    Block_80156400 *mpUnknown1C;
};

class Class_802A2918 : public Class_80148A58 {
public:
    Class_802A2918();
    virtual ~Class_802A2918() { }
    virtual void vfn_01();
    virtual void vfn_02();
    virtual int vfn_05(int team);
    virtual void vfn_10(int value, int *list, int *ids);
    virtual void vfn_11(int value, int *list, int *ids, unsigned int a, int b);
    virtual void vfn_12();
    virtual int vfn_13();
    virtual int vfn_21();
    virtual int vfn_22(int value);
    virtual int vfn_23(AutoDepthPlayer_t *pRecords, unsigned int count);
    virtual int vfn_26(int team, int index, Object_80039F5C * pPlayer, int kind);
    virtual int vfn_30(int kind, int team, int index, Object_80039F5C *pPlayer);

    Object_8015005C *mpUnknown1C;
    unsigned int mUnknown32;
    int mUnknown36;
    int mUnknown40;
    unsigned char mUnknown44[4];
};

class Class_802A27F0 : public Class_80148A58 {
public:
    Class_802A27F0();
    virtual void vfn_01();
    virtual void vfn_02();
    virtual int vfn_05(int team);
    virtual void vfn_07(int kind, int value);
    virtual const float * vfn_09(int index);
    virtual void vfn_10(int value, int *pList, int *pIds);
    virtual void vfn_11(int value, int *pList, int *pIds, unsigned int count, int b);
    virtual void vfn_14();
    virtual void vfn_20(int team, unsigned char index, int kind, char *pFirst, unsigned char firstLength, char *pSecond, unsigned char secondLength);
    virtual int vfn_21();
    virtual int vfn_26(int team, int index, Object_80039F5C *pPlayer, int kind);
    virtual int vfn_30(int kind, int team, int index, Object_80039F5C *pPlayer);
    virtual void vfn_35(int team, int showColors);

    Rules_801531C4 *mpUnknown1C;
    int mUnknown20;
    unsigned char mUnknown24;
    unsigned char mUnknown25;
};

class Class_802A2788 : public PreGamePhase {
public:
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void ShowIntroScreen();
};

class Class_802A2748 : public Class_80297B50 {
public:
    virtual void vfn_03(float dt);
    virtual void vfn_04(float dt);
    virtual void vfn_05(float dt);
    virtual int vfn_06();
};

class Class_802A26D8 : public PreSnapPhase {
public:
    virtual ~Class_802A26D8() { }
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
};

class Class_802A26A0 : public LivePlayPhase {
public:
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
};

class Class_802A2618 : public PostPlayPhase {
public:
    virtual void OnUpdate(float dt);
    virtual int GetResultText(char *pText);
    virtual void Finish(float dt);
};

class Class_802A2560 : public ScrmRuleSet {
public:
    virtual int GetScoreLimit();
    virtual int GetWinner();
    virtual void AwardWin(int team);
    virtual int IsTimed();
    virtual int GetGameTime();
    virtual void ResetPlaySpot();
    virtual void ResetGame(int team);
    virtual int AllowsAudibles() { return 0; }
    virtual int IsWinAwarded();
};

class Class_802A24F8 : public Class_80297B90 {
public:
    virtual void vfn_03(float dt);
    virtual void vfn_06() { }
    virtual void vfn_07() { }
    virtual void vfn_08();
    virtual void vfn_09();
    virtual int vfn_10() { return 1; }
    virtual int vfn_11() { return 1; }
};

struct States_802A2DB8 {
    Class_802A2788 mUnknown0;
    Class_802A2748 mUnknown4;
    Class_802A26D8 mUnknown8;
    Class_802A26A0 mUnknownC;
    Class_802A2618 mUnknown10;
    Class_802A24F8 mUnknown14;
    Class_802A2560 mUnknown18;
    int mUnknown1C;
    int mUnknown20[2][3];
    unsigned char mUnknown38;
};

class Class_802A2490 : public PreGamePhase {
public:
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void ShowIntroScreen();
    virtual void HideIntroScreen();
};

class Class_802A2450 : public Class_80297B50 {
public:
    virtual void vfn_03(float dt);
};

class Class_802A23E0 : public PreSnapPhase {
public:
    virtual ~Class_802A23E0() { }
    virtual void OnEnter(float dt);
};

class Class_802A23A8 : public LivePlayPhase {
public:
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);

    unsigned char mUnknown4;
};

class Class_802A2320 : public PostPlayPhase {
public:
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void ShowResultText();
};

class Class_802A2268 : public ScrmRuleSet {
public:
    virtual int GetTeamSize();
    virtual int AllowsPrediction();
};

class Class_802A2200 : public Class_80297B90 {
public:
    virtual void vfn_03(float dt);
    virtual void vfn_06() { }
    virtual void vfn_07() { }
    virtual void vfn_08();
    virtual void vfn_09();
    virtual int vfn_10() { return 1; }
    virtual int vfn_11() { return 1; }
};

class Block_802A21E8 {
public:
    Block_802A21E8() : mUnknown20(0), mUnknown24(0) {}
    virtual ~Block_802A21E8() {}

    Class_802A2490 mUnknown0;
    Class_802A2450 mUnknown4;
    Class_802A23E0 mUnknown8;
    Class_802A23A8 mUnknownC;
    Class_802A2320 mUnknown14;
    Class_802A2268 mUnknown18;
    Class_802A2200 mUnknown1C;
    int mUnknown20;
    int mUnknown24;
};

class Class_802A2130 : public ScrmRuleSet {
public:
    virtual int GetScoreLimit() { return 0x7FFFFFFF; }
    virtual int GetWinner();
    virtual void AwardWin(int team);
    virtual int IsNearWin(int team) { return 0; }
    virtual int GetScoreType() { return 1; }
    virtual int GetScore(int team) { return 0; }
    virtual int IsTimed() { return 1; }
    virtual int GetGameTime();
    virtual void ResetPlaySpot();
    virtual void ResetGame(int team);
    virtual int AllowsAudibles() { return 0; }
};

class Class_802A20C8 : public PreGamePhase {
public:
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void OnExit();
    virtual void ShowIntroScreen();
    virtual void HideIntroScreen() { }
    virtual void EnterFirstPhase(float dt);
    void fn_8014DA20();
};

class Class_802A2058 : public PreSnapPhase {
public:
    virtual ~Class_802A2058() {}
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void ReleaseHeldBalls() { }
    virtual void AssignControlledPlayers();

    unsigned char mUnknown4;
};

class Class_802A2020 : public LivePlayPhase {
public:
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);

    unsigned char mUnknown4;
};

class Class_802A1F90 : public PostPlayPhase {
public:
    Class_802A1F90() : mpUnknown4(0), mpUnknown8(0), mUnknown12(1) {}
    virtual ~Class_802A1F90() {}
    virtual void OnEnter(float dt);
    virtual void OnExit();
    virtual void ShowResultText() { }
    virtual void UpdateCue(float dt) { }
    virtual int IsHeld(float dt) { return 0; }
    virtual int GetBusy(float dt) { return 0; }
    virtual int IsFinished(int busy);
    virtual void Finish(float dt);

    Object_80039F5C *mpUnknown4;
    Object_80039F5C *mpUnknown8;
    unsigned char mUnknown12;
};

class Record_8014F104 {
public:
    Record_8014F104() : mUnknown0(0), mUnknown4(0), mUnknown8(255) { memset(mUnknown12, 0, sizeof(mUnknown12)); }
    virtual ~Record_8014F104() {}

    int mUnknown0;
    unsigned int mUnknown4;
    unsigned char mUnknown8;
    unsigned int mUnknown12[10];
};

class Class_802A1F10 : public Class_80297B90 {
public:
    virtual void vfn_03(float dt);
    virtual void vfn_06() { }
    virtual void vfn_07() { }
    virtual void vfn_08();
    virtual void vfn_09();
    virtual int vfn_10() { return 1; }
    virtual int vfn_11() { return 0; }
};

class Block_8014F104 {
public:
    Block_8014F104() : mUnknown2C(0), mUnknown30(1), mpUnknown34(0), mUnknown38(0), mpUnknown3C(0) { memset(mUnknown40, 0, sizeof(mUnknown40)); }
    virtual ~Block_8014F104() {}

    Class_802A2130 mUnknown0;
    Class_802A20C8 mUnknown4;
    Class_802A2058 mUnknown8;
    Class_802A2020 mUnknown10;
    Class_802A1F90 mUnknown18;
    Class_802A1F10 mUnknown28;
    int mUnknown2C;
    unsigned char mUnknown30;
    Record_8014F104 *mpUnknown34;
    unsigned int mUnknown38;
    Object_80039F5C *mpUnknown3C;
    int mUnknown40[2][7];
};

class Class_802A1E38 : public ScrmRuleSet {
public:
    virtual ~Class_802A1E38() { }
    virtual int GetScoreLimit() { return 0x7FFFFFFF; }
    virtual int GetWinner();
    virtual void AwardWin(int value);
    virtual int IsNearWin(int team) { return 0; }
    virtual int GetScore(int team) { return 0; }
    virtual int IsTimed()
    {
        if (lbl_8031BDD4.mUnknown36 != 0) {
            return 1;
        }
        return 0;
    }
    virtual int GetGameTime() { return lbl_8031BDD4.mUnknown36; }
    virtual void ResetGame(int team);
    virtual int AllowsAudibles() { return 0; }
    virtual void EndPlay();
};

class Class_802A1DC8 : public PreGamePhase {
public:
    Class_802A1DC8() : mUnknown4(1) {}
    virtual ~Class_802A1DC8() { }
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float value);
    virtual void OnExit();
    virtual void ShowIntroScreen();
    virtual void HideIntroScreen();
    virtual void EnterFirstPhase(float value);

    unsigned char mUnknown4;
};

class Class_802A1D58 : public PreSnapPhase {
public:
    virtual ~Class_802A1D58() { }
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void AssignControlledPlayers();
    virtual void SetupCamera();
};

class Class_802A1D20 : public LivePlayPhase {
public:
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void OnExit();

    unsigned char mUnknown4;
    char mUnknown5[3];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
};

class Class_802A1C98 : public PostPlayPhase {
public:
    virtual void OnExit();
    virtual void SetupCamera();
    virtual int GetBusy(float dt);
    virtual int IsFinished(int busy);
    virtual void Finish(float dt);
};

class Class_802A1C30 : public Class_80297B90 {
public:
    virtual void vfn_03(float dt);
    virtual void vfn_06() { }
    virtual void vfn_07() { }
    virtual void vfn_08();
    virtual void vfn_09();
    virtual int vfn_10() { return 1; }
    virtual int vfn_11() { return 0; }
};

struct Object_8015005C {
    Class_802A1DC8 mUnknown0;
    Class_802A1D58 mUnknown8;
    Class_802A1D20 mUnknown12;
    Class_802A1C98 mUnknown24;
    Class_802A1C30 mUnknown28;
    Class_802A1E38 mUnknown32;
    Table_8015005C *mpUnknown36;
};

class Class_802A1BC8 : public PreGamePhase {
public:
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void OnExit();
    virtual void ShowIntroScreen();
    virtual void HideIntroScreen();
};

class Class_802A1B58 : public PreSnapPhase {
public:
    virtual ~Class_802A1B58() {}
    virtual void OnEnter(float dt);
    virtual void AssignControlledPlayers();

    Block_80170E64 *mpUnknown4[2][2];
    signed char mUnknown20[2][2];
};

class Class_802A1B18 : public Class_80297B50 {
public:
    virtual void vfn_03(float dt);
    virtual void vfn_04(float dt);
    virtual void vfn_05(float dt);
};

class Class_802A1AE0 : public LivePlayPhase {
public:
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void OnExit();

    int mUnknown4;
};

class Class_802A1A58 : public PostPlayPhase {
public:
    virtual int GetResultText(char *pText);
};

class Class_802A19F0 : public Class_80297B90 {
public:
    virtual void vfn_03(float dt);
    virtual void vfn_06() { }
    virtual void vfn_07() { }
    virtual void vfn_08();
    virtual void vfn_09();
    virtual int vfn_10() { return 1; }
    virtual int vfn_11() { return 0; }
};

class Class_802A1930 : public ScrmRuleSet {
public:
    virtual int GetScoreLimit();
    virtual int GetWinner();
    virtual void AwardWin(int team);
    virtual int IsNearWin(int team);
    virtual int IsOpponentNearWin(int team);
    virtual int GetScoreType();
    virtual int GetScore(int team);
    virtual void ResetPlaySpot();
    virtual void ResetGame(int team);
    virtual int AllowsAudibles();
    virtual unsigned int GetGoalLimit();
    virtual int GetGoalTotal(int team);
    virtual int GetGoalCount(int team);
    virtual unsigned short vfn_22(int team);
};

struct Rules_801531C4 {
    Class_802A1BC8 mUnknown0;
    Class_802A1B58 mUnknown4;
    Class_802A1B18 mUnknown28;
    Class_802A1AE0 mUnknown32;
    Class_802A1A58 mUnknown40;
    Class_802A1930 mUnknown44;
    Class_802A19F0 mUnknown48;
    Score_801531C4 *mpUnknown52;
};

class Class_802A18C8 : public PreGamePhase {
public:
    virtual void OnEnter(float dt);
    virtual void OnUpdate(float dt);
    virtual void ShowIntroScreen();
    virtual void HideIntroScreen();
};

class Class_802A1860 : public Class_80297B90 {
public:
    virtual void vfn_03(float dt);
    virtual void vfn_06() { }
    virtual void vfn_07() { }
    virtual void vfn_08();
    virtual void vfn_09();
    virtual int vfn_10() { return 1; }
    virtual int vfn_11() { return 1; }
};

class Class_802A17A8 : public ScrmRuleSet {
public:
    virtual int GetScoreLimit();
    virtual int GetWinner();
    virtual void AwardWin(int team);
    virtual int IsNearWin(int team);
    virtual void ResetPlaySpot();
    virtual void ResetGame(int team);
    virtual void PlaceBallForDrive(int flip);

    unsigned char mUnknown4;
};

class Block_80156400 {
public:

    Class_802A18C8 mObject0;
    Class_802A17A8 mObject4;
    Class_802A1860 mObject12;
    int mUnknown16;
    Record_8005CE10 mRecords[2][3];
    unsigned char mUnknown188;
    unsigned char mUnknown189[2];
};

extern "C" const char *lbl_803EB2E4;
extern Record_80148C4C lbl_802DE130[];
void *operator new(unsigned int size, int unknown);
extern Record_80148C4C lbl_802DE41C[];
extern Record_80148C4C lbl_802DE99C[];
void *operator new[](unsigned int size, int unknown);
extern "C" Table_8015005C *fn_801530FC(void);
extern Record_80148C4C lbl_802DEA18[];
extern Record_80148C4C lbl_802DEAA8[];

extern "C" {
void fn_801D31F0(void *pDst, const void *pSrc, int size);
extern int lbl_803EB2A8;
extern int lbl_803EB2AC;
extern Class_80148A58 *lbl_8031BDBC[];
void fn_800EFE1C(int a, State_80039F5C *pQueue);
void PlyrSwapStateData(Object_80039F5C *pA, Object_80039F5C *pB);
void fn_80149040(Object_80039F5C *p);
void fn_800B6474(int index, unsigned char team);
void fn_800B6658(Object_80039F5C *p);
void fn_800B6714(Object_80039F5C *p, int index);
void fn_80148814(Object_80039F5C *p);
int fn_80178AE0(void);
int fn_8022B414(int handle, unsigned int tag, int *pValue);
void fn_80148D20(AutoDepthPlayer_t *pRecords, int *pValues,
                 DbCursor *pQuery);
void fn_80148DFC(AutoDepthPlayer_t *pRecords, int count, int *pExcluded,
                 int *pId, int *pCategory);
int fn_801486A0(void);
int EditMenuIsStoryTeam(void);
void *memmove(void *dst, const void *src, unsigned int n);
extern int lbl_8031BE04[14][3];
extern unsigned char lbl_8031BEAC[54];
extern int lbl_803ECA24[2];
extern unsigned char lbl_803EB2B4;
extern TextChoices_802DDC20 lbl_802DDC20[];
void PlyrLoadDbRecord(QueryCursor cursor, int index, void *pOut);
void fn_800B4900(QueryCursor cursor, int index, short *pRatings, void *pOut);
void fn_800B4798(short *pRatings, int team, unsigned char index, void *pContext);
void fn_800B5150(Object_80039F5C *p);
void PlyrAttachModel(Object_80039F5C *p);
int fn_800C8704(int *pFirst, int *pSecond);
int fn_800C8744(int team);
int fn_8022B7A4(int handle, unsigned int tag, int *pValue);
int fn_801C2D88(char *pText, int capacity, const char *pFormat, ...);
void fn_80177F88(int value);
int fn_800A2178(void);
void fn_80178CD8(int value);
int fn_80178308(void);
int fn_80178348(void);
void fn_8017833C(int team);
extern unsigned char lbl_803EB2B5;
extern char *lbl_803EB2B0;
extern void *gUISMainInfo;
extern int lbl_802DE3D0[];
int fn_801787DC(int team);
void fn_801787FC(int team, short value);
void fn_800C87CC(int team, int value);
void ClockRuleClearFlags(unsigned int mask);
void ClockRuleSetFlags(unsigned int mask);
void fn_8009D8CC(int index);
void fn_8009D964(int index, int value);
void fn_8009D888(int index, int value);
void fn_8009D944(int index);
float fn_80178A2C(void);
void fn_80178A20(float value);
void fn_80178E88(float v);
int fn_80178320(void);
int fn_80178360(void);
void fn_80178370(void);
int fn_801783AC(int bit);
void fn_801790D0(int team, float a, float b);
void HudClearEvent71(void);
void TutorialReleasePause(void);
int MsgBoxIsClosed(void);
int fn_800C1E40(void);
void MsgBoxShow(const char *pTitle, const char *pText, const char *pButtons);
void fn_8021956C(void *p, int a, int b, int c);
void fn_801486A8(void);
void fn_801487C0(int team, int begin);
void BallResetToSpot(void);
void PlayBookSetFormationType(int team, int kind);
int PlayCallScriptRunOffense(int mode);
void PlayBookLoadCurrentPlay(int team);
void PlayBookSetIndices(int team, unsigned int a, unsigned int b, unsigned int c);
PlaybookTeamView *PlayBookGetTeam(int team);
int FormationLineupApplyUser(int formation, int team);
void fn_800B3EFC(int team);
void fn_800AD910(int a, float b);
void CamGameResumeAll(void);
void ScrmTeamPlaceInHuddle(int team);
Object_80039F5C *PlyrFindNearest(Vector_80039F5C *pPos, float *pOut, int team);
int fn_8011F1CC(void);
void HudShowAlert(const char *pText);
void PlyrMgrClearStates(void);
int InGameOverlayGetState(void);
void InGameOverlayReset(void);
void ClockRuleEndPeriod(void);
void fn_800BC51C(PreGamePhase *pObject);
void fn_800B3644(Class_80297B50 *pObject);
void fn_800BFAB4(PreSnapPhase *pObject);
void fn_800A039C(LivePlayPhase *pObject);
void fn_800B9598(PostPlayPhase *pObject);
void fn_800AACB8(Class_80297B90 *pObject);
void fn_80178F20(ScrmRuleSet *pObject);
unsigned char DepthChartGetEntry(int group, int index, int *pValue);
int PlayerDbSeekOriginalId(Object_8008044C *pObject, int a, int *pResult);
int PlayerDbGetId(Object_8008044C *pObject);
Object_80039F5C *PlyrFindById(int id);
void fn_8014A6A0(const int *pValues, int *pOrder, unsigned int count);
void fn_8014A8D8(const int *pValues, int *pOrder, unsigned int count);
extern unsigned char lbl_803EB2D0;
extern unsigned char lbl_803EB2D1;
extern char *lbl_803EB2BC;
extern char *lbl_803EB2C0;
extern char *lbl_803EB2C4;
extern char *lbl_803EB2C8;
extern char *lbl_803EB2CC;
int fn_800A937C(void);
int fn_800A8444(int team);
int fn_800A8EA4(int team);
int fn_8014BC90(void);
int fn_800B9A90(PostPlayPhase *p);
void fn_800B925C(void *p, char *pText);
extern char *lbl_803EB2B8;
extern int lbl_802DE95C[];
void fn_8014BC98(const int *pValues, int *pOrder, unsigned int count);
void fn_8014BED8(const int *pValues, int *pOrder, unsigned int count);
Block_8014F104 *fn_8014F104(Class_80148A58 *p);
void fn_8014D024(unsigned short index);
void fn_8014F4D8(Class_80148A58 *p, Object_80039F5C *pPlayer, int kind, int value);
void HudShowPlayerPopup(Object_80039F5C *p, int team, const char *pText, int value, int d);
int fn_801C2E18(char *pBuffer, const char *pFormat, ...);
void HudSetScoreTableRow(int slot, const char *pText0, const char *pText1, const char *pText2, int key);
void fn_800EFE60(int a, State_80039F5C *pQueue, Object_80039F5C *pPlayer);
void PlyrClearPendingMsg(Object_80039F5C *pPlayer, int value);
void Vec2FromAngle(float *pOut, int angle, float length);
float fn_80178A08(void);
extern int lbl_803EB2DC;
extern Object_80039F5C *lbl_803EB2E0;
extern int lbl_802DE9CC[];
void fn_801488D4(Object_80039F5C *p, Object_80039F5C *pOther);
int fn_8014EDBC(void);
extern char *lbl_803EB2D4;
void CamGameSetModeAll(int a);
void CamGameSelectCamera(int a);
GameCamera_t *CamGameGetCamera(int index);
void CamPlaySetYOffset(float value);
void fn_8014D67C(void);
void PlyrStarSetShown(int a, int b);
float fn_80178A44(void);
void fn_801780A8(Point_8017886C pos);
void CamGameSetFocusAll(int a, int b);
void PlayerMoveResetAll(void);
void fn_800B14E4(void);
void DivotRestartRecords(void);
void AudmonEventClear(void);
void ClockRuleSnap(void);
void fn_800C9FC0(void);
void PauseUnblock(void);
extern int lbl_803EB2D8;
void HudShowCallout(const char *pText);
void ParticleTrailStartAfterimage(Block_80170E64 *p);
void fn_800F0490(int a, State_80039F5C *pQueue, int id);
void fn_800F0278(int a, State_80039F5C *pQueue, Message_800F01CC *pMessage, Object_80039F5C *p,
                 unsigned char position);
void fn_80120618(void);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_801787A0(void);
int fn_80178508(void *pPos, float *pOut, int a);
void fn_801783D0(int bit, int on);
void PossFumble(Object_80039F5C *p);
void fn_8014D210(Object_80039F5C *p, int a, int b);
void fn_80177C44(int value);
void fn_8014D948(void *p);
int BallStateGet(Ball_t *pBall, int *pOut);
float Vec3Distance(Vector_80039F5C *pPos, Vector_80039F5C *pOther);
void PauseBlock(void);
int InGameOverlayOpen(int value);
void InGameOverlayShow(void);
void fn_800A8738(int value);
int StoryEventsGetCurrentEvent(void);
void StoryEventsSetRewardPenalty(int value);
int fn_8014FF34(Class_802A2B68 *p);
int GameTextGetPadPlayer(int index);
int UserProfileGetPadName(unsigned char index, char *pText, int count);
int UserProfileGetFreeKey(int kind, int key, int first, int last);
unsigned int fn_8014F474(Class_80148A58 *p, Object_80039F5C *pPlayer);
int RecordsGetValue(int a);
float fn_800A32B4(void);
float SyncRandGetFloatRange(int selector, float first, float last);
extern Class_802A2918 lbl_8031BDD4;
void fn_80151CCC(Class_802A2918 *p, unsigned int index, unsigned char value);
void fn_801526EC(Class_802A2918 *p);
void fn_801502B4(void *p);
int fn_80151B20(Class_802A2918 *p);
int fn_8009D9A8(int index);
void PlyrMgrResetAll(void);
void fn_801527E0(Class_802A2918 *p, int value);
void fn_80151010(Class_802A1D20 *p);
void ResetBallsAndFieldPositions(Class_802A1D20 *p);
void fn_801024FC(Object_80039F5C *p, int kind, int b, int c, int d);
void SndgEventSetCrowdCycle(int value);
void OSReport(const char *pMessage, ...);
void RefreshFourPlayerScoreRows(Class_802A1D20 *p);
void fn_80151BCC(Class_802A2918 *p);
void fn_80151D9C(Class_802A2918 *p);
void fn_80153168(Class_802A2918 *p, int index, unsigned char value);
int BallStateGetPrev(Ball_t *p, int *pOut);
void fn_8015013C(Object_8015005C *p, int id, int flag);
void BallRestAtAngles(Ball_t *pBall, int *pAngles);
void BallSetSpinMode(Ball_t *pBall, int value);
void BallPrimeKickUp(Ball_t *pBall);
void fn_8014FFC4(Point_8017886C *pPoint);
extern int lbl_802DEA78[];
int fn_80177C38(void);
void fn_80177C50(int a);
void fn_8011DF90(void);
void PlayBookRestoreSelection(int team);
void fn_8009B924(void);
int fn_801529C0(Class_802A2918 *p);
void *SyncStateGetData(void *pHandle);
void PlyrStarSetBallRingEnabled(unsigned char value);
Point_8017886C fn_80177FFC(int team);
void HudSetScoreTableRows(int a);
void Vec2Sub(void *pOut, void *pA, void *pB);
int MathAngleDiff(int a, int b);
int fn_8015228C(Object_80039F5C *p, unsigned char *pIndex);
void fn_80152940(Class_802A2918 *p, int index, MiniGameSlotInfo_t *pInfo);
Rules_801531C4 *fn_80155128(Class_80148A58 *p);
int fn_800948E4(Object_8017886C *p);
void fn_80177E6C(int a, int b);
int FormationLineupSwapAllUser(int a, int b, int c, int d);
void HudPost3AOff(void);
void HudSetScoreTableHeaders(const char *pText0, const char *pText1);
int GameTextFindPlayerPad(int index);
int PortDbGetControlledPlayer(int key);
void PortDbSetControlledPlayer(int key, int value);
Object_80039F5C *PlyrFindByRole(int team, int a, unsigned char n);
void FieldLinesEnable(unsigned char enabled);
extern char *lbl_803EB2F0;
unsigned char PortDbCountSidePlayers(int team);
unsigned char fn_800B65D0(int team);
void fn_800B65C0(int team, unsigned char index);
extern int lbl_803EB2F4;
void PlayBookLoadAudibles(int team);
extern int lbl_802DEB78[];
char *strcpy(char *pDest, const char *pSource);
extern int lbl_802DEB08[];
extern int lbl_802DEB40[];
int fn_80178EA0(int team);
int fn_80178EE0(int team);
int fn_80155130(Class_80148A58 *p, int team, unsigned char index);
Object_80039F5C *fn_80154FC0(Class_802A27F0 *p, int team, int index);
extern unsigned char lbl_803EB2FC;
extern unsigned char lbl_803EB2FD;
int fn_80177F70(void);
float SyncRandGetFloat(int stream);
unsigned short fn_80178E94(void);
void fn_80155D7C(Class_80148A58 *p);
extern char *lbl_803EB2F8;
void fn_80155A7C(Class_80148A58 *p, unsigned char team, int kind, int value);
void fn_80155BF4(Class_80148A58 *p, unsigned char team, int kind, int value, int flag);
void fn_8017CAC0(void (*pCallback)(unsigned int, int, int));
void fn_801556D0(unsigned int kind, int value, int flag);
unsigned char fn_80155D38(Class_80148A58 *p, int team);
}

extern "C" {

void PlyrSwapStateData(Object_80039F5C *pA, Object_80039F5C *pB)
{
    Message_800F01CC message;
    State_80039F5C queue[10];
    unsigned char state[88];
    unsigned char block1244[12];
    unsigned char block1256[1240];
    unsigned char block2496[404];
    unsigned char *pBytesA = (unsigned char *)pA;
    unsigned char *pBytesB = (unsigned char *)pB;

    fn_801D31F0(&message, pA->mUnknown3044, sizeof(message));
    fn_801D31F0(pA->mUnknown3044, pB->mUnknown3044, sizeof(message));
    fn_801D31F0(pB->mUnknown3044, &message, sizeof(message));
    fn_801D31F0(queue, pA->mQueue, sizeof(queue));
    fn_801D31F0(pA->mQueue, pB->mQueue, sizeof(queue));
    fn_801D31F0(pB->mQueue, queue, sizeof(queue));
    fn_801D31F0(state, pBytesA + 336, sizeof(state));
    fn_801D31F0(pBytesA + 336, pBytesB + 336, sizeof(state));
    fn_801D31F0(pBytesB + 336, state, sizeof(state));
    fn_801D31F0(block1244, pBytesA + 1244, sizeof(block1244));
    fn_801D31F0(pBytesA + 1244, pBytesB + 1244, sizeof(block1244));
    fn_801D31F0(pBytesB + 1244, block1244, sizeof(block1244));
    fn_801D31F0(block1256, pBytesA + 1256, sizeof(block1256));
    fn_801D31F0(pBytesA + 1256, pBytesB + 1256, sizeof(block1256));
    fn_801D31F0(pBytesB + 1256, block1256, sizeof(block1256));
    fn_801D31F0(block2496, pBytesA + 2496, sizeof(block2496));
    fn_801D31F0(pBytesA + 2496, pBytesB + 2496, sizeof(block2496));
    fn_801D31F0(pBytesB + 2496, block2496, sizeof(block2496));
}

void fn_801485B4(void)
{
    lbl_803EB2A8 = 1;
}

void fn_801485C0(void)
{
    lbl_803EB2A8 = 0;
    lbl_803EB2AC = 15;
}

int fn_801485D4(void)
{
    return lbl_803EB2A8 != 0;
}

void fn_801485EC(int value)
{
    lbl_803EB2AC = value;
}

void fn_801485F4(void)
{
    lbl_803EB2A8 = 2;
    lbl_8031BDBC[lbl_803EB2AC]->vfn_01();
}

void fn_80148644(void)
{
    lbl_8031BDBC[lbl_803EB2AC]->vfn_02();
    lbl_803EB2A8 = 1;
    fn_801485C0();
}

int fn_80148698(short *pRatings, Object_80039F5C *p, int value)
{
    return value;
}

int fn_801486A0(void)
{
    return lbl_803EB2AC;
}

void fn_801486A8(void)
{
    for (unsigned short team = 0; team < 2; ++team) {
        for (unsigned short index = 0; index < 7; ++index) {
            Object_80039F5C *p = PlyrGet((unsigned char)team, index);
            p->mMotion.mPos.mX = 0.0f;
            p->mMotion.mPos.mY = -((float)(int)index * 3.0f);
            p->mpUnknown4->mUnknown20 |= 1;
            p->mUnknown512.mUnknown14 = 1;
            p->mUnknown512.mUnknown8 = 0x800000;
            p->mUnknown512.mUnknown4 = 0x800000;
            p->mUnknown512.mUnknown0 = 0.14f;
            p->mFlags &= ~0x40000U;
            p->mUnknown9[2] = (unsigned int)index < (unsigned int)fn_80178D70((unsigned char)team);
        }
    }
}

void fn_801487C0(int team, int begin)
{
    for (unsigned char index = begin; index < 7; ++index) {
        fn_80148814(PlyrGet(team, index));
    }
}

void fn_80148814(Object_80039F5C *p)
{
    Ball_t *pBall = BallFindHeldBy(p);
    if (pBall) {
        Vector_80039F5C velocity;
        velocity.mX = velocity.mY = velocity.mZ = 0.0f;
        BallSetVelocity(pBall, &velocity);
        BallReleaseStill(pBall, 5, 0);
    }
    p->mMotion.mPos.mY = p->mMotion.mPos.mX = -100.0f;
    p->mpUnknown4->mUnknown20 &= ~1U;
    fn_800EFE1C(0, p->mpState);
    p->mFlags |= 0x40000;
    p->mUnknown512.mUnknown14 = 1;
    p->mUnknown512.mUnknown0 = 0.0f;
    p->mUnknown512.mUnknown8 = 0;
    p->mUnknown512.mUnknown4 = 0;
    p->mUnknown9[2] = 0;
}

void fn_801488D4(Object_80039F5C *pA, Object_80039F5C *pB)
{
    unsigned char motion[88];
    unsigned char control[16];
    unsigned char *pBytesA = (unsigned char *)pA;
    unsigned char *pBytesB = (unsigned char *)pB;
    unsigned short id = pA->mUnknown2908;
    pA->mUnknown2908 = pB->mUnknown2908;
    pB->mUnknown2908 = id;

    fn_801D31F0(motion, pBytesA + 424, sizeof(motion));
    fn_801D31F0(pBytesA + 424, pBytesB + 424, sizeof(motion));
    fn_801D31F0(pBytesB + 424, motion, sizeof(motion));
    fn_801D31F0(control, &pA->mUnknown512, sizeof(control));
    fn_801D31F0(&pA->mUnknown512, &pB->mUnknown512, sizeof(control));
    fn_801D31F0(&pB->mUnknown512, control, sizeof(control));
    fn_801D31F0(control, &pA->mUnknown528, sizeof(control));
    fn_801D31F0(&pA->mUnknown528, &pB->mUnknown528, sizeof(control));
    fn_801D31F0(&pB->mUnknown528, control, sizeof(control));

    unsigned char byte = pA->mUnknown9[0];
    pA->mUnknown9[0] = pB->mUnknown9[0];
    pB->mUnknown9[0] = byte;
    unsigned int flags = pA->mFlags;
    pA->mFlags = pB->mFlags;
    pB->mFlags = flags;
    PlyrSwapStateData(pA, pB);
    fn_80149040(pA);
    fn_80149040(pB);

    unsigned char indexA = pA->mUnknown8;
    unsigned char indexB = pB->mUnknown8;
    if (indexA != 0xFF) {
        fn_800B6474(indexA, pB->mIdBytes[2]);
        fn_800B6714(pB, indexA);
    } else {
        fn_800B6658(pB);
    }
    if (indexB != 0xFF) {
        fn_800B6474(indexB, pA->mIdBytes[2]);
        fn_800B6714(pA, indexB);
    } else {
        fn_800B6658(pA);
    }
}

Class_80148A58 *fn_80148A58(void)
{
    int index = fn_801486A0();
    if (index != 15) {
        return lbl_8031BDBC[index];
    }
    return 0;
}

} /* extern "C" */

 /* extern "C" */

Class_80148A58::Class_80148A58()
{
    mUnknown0 = 2;
    mUnknown4 = 1;
    mState.mCount = 0;
    mState.mCachedValue = 0;
    mState.mpRecords = 0;
    mState.mUnknownC = 1;
}

int Class_80148A58::vfn_03()
{
    return 14;
}

unsigned int Class_80148A58::vfn_04(int team)
{
    return 7;
}

int Class_80148A58::vfn_05(int team)
{
    return 7;
}

unsigned int Class_80148A58::vfn_06()
{
    return 7;
}

int Class_80148A58::vfn_08(int a)
{
    return 0;
}

extern "C" {

void fn_80148AF8(Class_80148A58 *p)
{
    if (p->mState.mCount && p->mState.mpRecords) {
        AutoDepthSetRateCallback(fn_80148D20);
        AutoDepthSetSelectCallback(fn_80148DFC);
    }
}

} /* extern "C" */

void Class_80148A58::vfn_10(int value, int *pList, int *pIds)
{
    AutoDepthFillChart(value, pList, pIds);
}

void Class_80148A58::vfn_11(int value, int *pList, int *pIds, unsigned int count, int b)
{
    AutoDepthFillChart(value, pList, pIds);
}

int Class_80148A58::vfn_13()
{
    unsigned char result = 0;
    unsigned char team = (unsigned char)fn_80178AE0();
    if (team != 2) {
        result = fn_800B65A0(team) != 255;
    }
    return result;
}

void Class_80148A58::vfn_15()
{
    int value = (int)fn_8009D990(1);
    if (value != mState.mCachedValue && value >= 0) {
        mState.mCachedValue = value;
        if (value <= 10) {
            AudmonEventPost(20, 0);
        }
    }
}

int Class_80148A58::vfn_23(AutoDepthPlayer_t *pRecords, unsigned int count)
{
    unsigned int index = 0;
    while (index < mState.mCount && mState.mpRecords[index].mUnknown2C) {
        ++index;
    }
    return index == mState.mCount ? 0 : index;
}

int Class_80148A58::vfn_24(int team, unsigned int tag)
{
    int value = 0;
    int result = 0;
    for (unsigned char index = 0; index <= 6; ++index) {
        Object_80039F5C *p = PlyrGet((unsigned char)team, index);
        if (p->mUnknown9[2]) {
            fn_8022B414(p->mUnknown2908, tag, &value);
            result += value;
        }
    }
    return result;
}

extern "C" {

void fn_80148D20(AutoDepthPlayer_t *pRecord, int *pValues, DbCursor *)
{
    Class_80148A58 *p = fn_80148A58();
    unsigned int i;
    unsigned int j;

    for (j = 0; j < 14; j++) {
        pRecord->values[j] = 0;
    }
    for (i = 0; i < p->mState.mCount; i++) {
        pRecord->values[p->mState.mpRecords[i].mUnknown0] = 0;
        for (j = 0; j < 10; j++) {
            pRecord->values[p->mState.mpRecords[i].mUnknown0] +=
                p->mState.mpRecords[i].mUnknown4[j] * pValues[j];
            p->mState.mpRecords[i].mUnknown2C = 0;
        }
    }
}

void fn_80148DFC(AutoDepthPlayer_t *pRecords, int count, int *, int *pId, int *pCategory)
{
    Class_80148A58 *p = fn_80148A58();
    int index = p->vfn_23(pRecords, count);
    unsigned int values[4];
    int ids[4];
    int categories[4];
    unsigned int found;
    unsigned int i;
    unsigned char k;

    for (unsigned char m = 0; m <= 3; m++) {
        ids[m] = 32767;
        values[m] = 0;
        categories[m] = 0;
    }
    found = 0;
    for (i = 0; i < count; i++) {
        if (!pRecords[i].excluded) {
            for (k = 0; k <= 3; k++) {
                if (pRecords[i].values[p->mState.mpRecords[index].mUnknown0] > values[k]) {
                    found++;
                    memmove(&values[k] + 1, &values[k], (3 - k) * 4);
                    memmove(&ids[k] + 1, &ids[k], (3 - k) * 4);
                    memmove(&categories[k] + 1, &categories[k], (3 - k) * 4);
                    ids[k] = pRecords[i].id;
                    values[k] = pRecords[i].values[p->mState.mpRecords[index].mUnknown0];
                    categories[k] = p->mState.mpRecords[index].mUnknown0;
                    *pCategory = categories[k];
                    p->mState.mpRecords[index].mUnknown2C = 1;
                    break;
                }
            }
        }
    }
    *pId = ids[0];
    *pCategory = categories[0];
    if (!EditMenuIsStoryTeam() && *pCategory) {
        switch (fn_801486A0()) {
        case 0:
        case 1:
        case 2: {
            unsigned int n = found;
            if (n > 4) {
                n = 4;
            }
            unsigned int pick = SyncRandGetRange(0, n);
            *pId = ids[pick];
            *pCategory = categories[pick];
            break;
        }
        }
    }
}

} /* extern "C" */

int Class_80148A58::fn_80149014()
{
    return GameModeTypeGet() == 11;
}

extern "C" {

void fn_80149040(Object_80039F5C *p)
{
    QueryCursor cursor;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    TDbCompilePerformOp(0,"declare \x8A cursor for select * from 'AGLP' where ('DIGP' = \x84)\n",&cursor,p->mUnknown2908);
    PlyrLoadDbRecord(cursor,0,&p->mUnknown2900);
    p->mUnknown508 = p->mUnknown2904Float;
    fn_800B4900(cursor,0,p->mRatings,p->mUnknown3020);
    fn_800B4798(p->mRatings,(p->mId >> 8) & 0xFF,(p->mId >> 16) & 0xFF,&p->mUnknown2900);
    if(cursor.mUnknown0)TDbSQLDestroyCursor(&cursor);
    PlyrAttachModel(p);
    fn_800B5150(p);
}

TextChoices_802DDC20 lbl_802DDC20[54] = {
    {1, {0}, {""}},
    {3, {0}, {"Tackling Machine", "Bruiser", "Trampler"}},
    {2, {0}, {"Scoring Machine", "Scoreboard"}},
    {2, {0}, {"Tank", "Powerhouse"}},
    {2, {0}, {"Hoppy", "Spring-Loaded", "Got Hops", "High Flyer"}},
    {2, {0}, {"Slippery", "Shifty"}},
    {2, {0}, {"Grabby", "Scoops"}},
    {2, {0}, {"Superfly", "Zero Gravity"}},
    {3, {0}, {"Completely Useless", "Worthless", "Should've Stayed Home"}},
    {1, {0}, {"Weak Tackler"}},
    {5, {0}, {"Unimpressive", "Boring", "Forgettable", "Bench Warmer", "Uninspired"}},
    {2, {0}, {"Butterfingers", "Dropsy"}},
    {2, {0}, {"Showstopper", "Show-Off"}},
    {1, {0}, {"D-Fensive"}},
    {2, {0}, {"QBs Fear Him", "Sack Master"}},
    {2, {0}, {"Interceptor", "Pick Machine"}},
    {4, {0}, {"So Close!", "Not Quite", "Maybe Next Time", "Almost"}},
    {2, {0}, {"High Score!", "Top Scorer"}},
    {1, {0}, {"Champion"}},
    {3, {0}, {"Top Dawg", "Street Legend", "MVP"}},
    {1, {0}, {"Centurion"}},
    {1, {0}, {"Stay Home"}},
    {1, {0}, {"Opportunist"}},
    {1, {0}, {"Marathon Man"}},
    {1, {0}, {"Minute Man"}},
    {2, {0}, {"Keeper", "Kung-Fu Grip"}},
    {1, {0}, {"Waxed!"}},
    {1, {0}, {"E for Effort"}},
    {3, {0}, {"Ka-Ching!", "Street Ball Magnet", "Money"}},
    {2, {0}, {"Bankrupt", "Penniless"}},
    {1, {0}, {"Jackpot!"}},
    {1, {0}, {"Owned the Walls"}},
    {3, {0}, {"Dropsy", "Butterfingers", "You're No Receiver"}},
    {4, {0}, {"Eeked It Out", "Barely Won", "Ya Got Lucky", "Pure Luck"}},
    {1, {0}, {"Clutch Victory"}},
    {1, {0}, {"Unstoppable Force"}},
    {1, {0}, {"Brick Wall"}},
    {1, {0}, {"Gold Star for Teamwork"}},
    {1, {0}, {"Ball Hog"}},
    {1, {0}, {"Completely Dominating"}},
    {1, {0}, {"Favorite Player:"}},
    {1, {0}, {"Safety Dancer"}},
    {1, {0}, {"Expert Marksman"}},
    {1, {0}, {"Brick Hands"}},
    {1, {0}, {"Likes the Long Ball"}},
    {1, {0}, {"Runs the West Coast"}},
    {1, {0}, {"Can't find the Bull's Eye!"}},
    {1, {0}, {"Didn't Try Hard Enough"}},
    {1, {0}, {"Afraid to Pass?"}},
    {1, {0}, {"Gatling Gunner"}},
    {1, {0}, {"Can't Convert"}},
    {1, {0}, {"Coast to Coast"}},
    {1, {0}, {"Perfect Execution"}},
    {1, {0}, {"Beyond Perfect Execution"}},
};

int lbl_803EB2A8 = 0;
int lbl_803EB2AC = 15;
char *lbl_803EB2B0 = "2 Minute Challenge\n\nUsing only passing plays, score as many times as you can in two minutes. Interceptions, fumble recoveries and safeties by the defense will cause you to lose points.";
unsigned char lbl_803EB2B4 = 0;
unsigned char lbl_803EB2B5 = 0;

} /* extern "C" */

void Class_80148A58::vfn_16(const int *pKinds)
{
    memset(lbl_8031BE04,0,168);
    memset(lbl_8031BEAC,0,54);
    fn_800C8704(&lbl_803ECA24[0],&lbl_803ECA24[1]);
    for(unsigned char k=0;pKinds[k]!=0;k++) {
        for(unsigned char i=0;i<14;i++) {
            unsigned char team=i/7,index=i%7;
            Object_80039F5C *player=PlyrGet(team,index);
            if(player->mUnknown9[2]) {
                unsigned int count=vfn_25(team,index);
                if(count<=2 && vfn_26(team,index,player,pKinds[k])) {
                    lbl_8031BEAC[k]++;
                    lbl_8031BE04[i][count]=pKinds[k];
                }
            }
        }
    }
}

void Class_80148A58::vfn_17(const int *pKinds)
{
    memset(lbl_8031BE04,0,168);
    memset(lbl_8031BEAC,0,54);
    fn_800C8704(&lbl_803ECA24[0],&lbl_803ECA24[1]);
    for(unsigned char k=0;pKinds[k]!=0;k++) {
        for(unsigned char team=0;team<2;team++) {
            unsigned int count=vfn_25(0,team);
            if(count<=2 && vfn_32(team,pKinds[k])) {
                lbl_8031BEAC[k]++;
                lbl_8031BE04[team][count]=pKinds[k];
            }
        }
    }
}

void Class_80148A58::vfn_18(int team, unsigned char index, char *text, unsigned char capacity)
{
    *text=0;
    for(unsigned char i=0;i<3 && lbl_8031BE04[team*7+index][i];i++) {
        const char *name=vfn_29(lbl_8031BE04[team*7+index][i]);
        unsigned char length=strlen(name);
        if(i)length+=2;
        if(capacity>length) {
            if(i) {
                text[0]=',';text[1]=' ';text+=2;capacity-=2;length-=2;
            }
            strncpy(text,name,capacity);
            text+=length;
            capacity-=length;
        }
    }
}

void Class_80148A58::vfn_19(int team, int column, char *text, int capacity)
{
    fn_801C2D88(text,capacity,vfn_29(lbl_8031BE04[team][column]));
}

unsigned char Class_80148A58::vfn_25(int team, int index)
{
    unsigned char row=team*7+index,count=0;
    while(count<3 && lbl_8031BE04[row][count])count++;
    return count;
}

int Class_80148A58::vfn_26(int team, int index, Object_80039F5C *player, int kind)
{
    int result=0;
    switch(kind) {
    case 1:result=vfn_31(1,team,index,player,1,0);break;
    case 2:result=vfn_31(2,team,index,player,0,0);break;
    case 3:result=vfn_31(3,team,index,player,10,0);break;
    case 4:result=vfn_31(4,team,index,player,2,0);break;
    case 5:result=vfn_31(5,team,index,player,2,0);break;
    case 6:result=vfn_31(6,team,index,player,1,0);break;
    case 7:result=vfn_31(7,team,index,player,3,0);break;
    case 8:result=vfn_31(8,team,index,player,1,1);break;
    case 9:
        result=vfn_31(9,team,index,player,2,1);
        if(result && vfn_28(8))result=0;
        break;
    case 10:result=vfn_25(team,index)==0;break;
    case 11:result=vfn_31(11,team,index,player,3,0);break;
    case 12:result=vfn_31(12,team,index,player,0,0);break;
    case 13:result=vfn_31(13,team,index,player,1,0);break;
    case 14:result=vfn_31(14,team,index,player,1,0);break;
    case 15:result=vfn_31(15,team,index,player,1,0);break;
    }
    return result;
}

int Class_80148A58::vfn_27(int team, int index, int value)
{
    unsigned char row=team*7+index;
    int found=0;
    for(unsigned char i=0;i<3;i++)if(lbl_8031BE04[row][i]==value)found=1;
    return found;
}

const char * Class_80148A58::vfn_29(int kind)
{
    unsigned char index=0;
    if(lbl_802DDC20[kind].mCount>1)index=SyncRandGetRange(0,lbl_802DDC20[kind].mCount);
    return lbl_802DDC20[kind].mpText[index];
}

unsigned char Class_80148A58::vfn_28(int index)
{
    return lbl_8031BEAC[index];
}

int Class_80148A58::vfn_30(int kind, int team, int index, Object_80039F5C *pPlayer)
{
    int result=0;
    unsigned short id=pPlayer->mUnknown2908;
    int value;
    switch(kind) {
    case 1:case 9:fn_8022B414(id,0x61746467,&result);break;
    case 2:
        fn_8022B414(id,0x64747567,&result);
        fn_8022B414(id,0x64746167,&value);result+=value;break;
    case 3:
        fn_8022B414(id,0x74627567,&result);
        fn_8022B7A4(lbl_803ECA24[team],0x61737374,&value);
        result+=value*10;break;
    case 4:
        fn_8022B7A4(lbl_803ECA24[team],0x68647374,&result);
        fn_8022B7A4(lbl_803ECA24[team],0x68777374,&value);result+=value;
        fn_8022B7A4(lbl_803ECA24[team],0x68737374,&value);result+=value;
        fn_8022B7A4(lbl_803ECA24[team],0x68327374,&value);result+=value;break;
    case 5:
        fn_8022B7A4(lbl_803ECA24[team],0x6A737374,&result);
        fn_8022B7A4(lbl_803ECA24[team],0x6A777374,&value);result+=value;
        fn_8022B7A4(lbl_803ECA24[team],0x73737374,&value);result+=value;
        fn_8022B7A4(lbl_803ECA24[team],0x73327374,&value);result+=value;break;
    case 6:fn_8022B414(id,0x72666C67,&result);break;
    case 7:
        fn_8022B7A4(lbl_803ECA24[team],0x68777374,&result);
        fn_8022B7A4(lbl_803ECA24[team],0x6A777374,&value);result+=value;
        fn_8022B7A4(lbl_803ECA24[team],0x70777374,&value);result+=value;
        fn_8022B7A4(lbl_803ECA24[team],0x63777374,&value);result+=value;break;
    case 8:
        fn_8022B414(id,0x64747567,&result);
        fn_8022B414(id,0x64746167,&value);result+=value;
        fn_8022B414(id,0x61746467,&value);result+=value;
        fn_8022B414(id,0x66666C67,&value);result+=value;
        fn_8022B414(id,0x6E696167,&value);result+=value;break;
    case 10:break;
    case 11:fn_8022B414(id,0x75667567,&result);break;
    case 12:result=StyleTrackerGetTotal(team);break;
    case 13:
        fn_8022B414(id,0x72666C67,&result);
        fn_8022B414(id,0x6E696167,&value);result+=value;break;
    case 14:fn_8022B414(id,0x6B736C67,&result);break;
    case 15:fn_8022B414(id,0x6E696167,&result);break;
    }
    return result;
}

int Class_80148A58::vfn_31(int kind, int team, int index, Object_80039F5C *player, int threshold, int mode)
{
    int value=vfn_30(kind,team,index,player);
    int count;
    switch(fn_801486A0()) {
    case 1:count=4;break;
    case 0:count=6;break;
    default:count=7;break;
    }
    int best=0,found=0,result=0;
    for(unsigned char t=0;t<2;t++) {
        for(unsigned char i=0;i<(unsigned int)count;i++) {
            Object_80039F5C *other=PlyrGet(t,i);
            if(other->mUnknown9[2]) {
                if(!found) {
                    best=vfn_30(kind,t,i,other);found=1;
                } else {
                    int next=vfn_30(kind,t,i,other);
                    if((mode==0 && next>best) || (mode==1 && next<best))best=next;
                }
            }
        }
    }
    if((mode==0 && best>threshold) || (mode==1 && best<threshold))result=value==best;
    return result;
}

int Class_80148A58::vfn_32(int team, int kind)
{
    int result=0;
    if(kind!=21 && vfn_27(0,team,8))return 0;
    switch(kind) {
    case 1:result=vfn_34(1,team,1,0);break;
    case 2:result=vfn_34(2,team,1,0);break;
    case 3:result=vfn_34(3,team,10,0);break;
    case 4:result=vfn_34(4,team,4,0);break;
    case 5:result=vfn_34(5,team,2,0);break;
    case 6:result=vfn_34(6,team,1,0);break;
    case 7:result=vfn_34(7,team,3,0);break;
    case 8:result=vfn_33(8,team)==0;break;
    case 9:
        if(!vfn_28(8) && vfn_34(9,team,100,1))result=1;
        break;
    case 10:result=vfn_25(0,team)==0;break;
    case 11:result=vfn_34(11,team,3,0);break;
    case 12:result=vfn_34(12,team,1,0);break;
    case 13:result=vfn_34(13,team,1,0);break;
    case 14:result=vfn_34(14,team,1,0);break;
    case 15:result=vfn_34(15,team,1,0);break;
    }
    return result;
}

int Class_80148A58::vfn_33(int kind, int team)
{
    int result=0,value;
    int handle=fn_800C8744(team);
    switch(kind) {
    case 1:case 9:result=vfn_24(team,0x61746467);break;
    case 2:
        fn_8022B7A4(handle,0x74727374,&result);
        fn_8022B7A4(handle,0x74507374,&value);result+=value;
        fn_8022B7A4(handle,0x64647374,&value);result+=value;break;
    case 3: {
        int a=StyleTrackerGetEventCount(team,30),b=StyleTrackerGetEventCount(team,31);
        int c=StyleTrackerGetEventCount(team,29);result=a+b+c;break;
    }
    case 4: {
        int a=StyleTrackerGetEventCount(team,57),b=StyleTrackerGetEventCount(team,63);result=a+b;break;
    }
    case 5: {
        int a=StyleTrackerGetEventCount(team,34),b=StyleTrackerGetEventCount(team,46);
        int c=StyleTrackerGetEventCount(team,42);result=a+b+c;break;
    }
    case 6:fn_8022B7A4(handle,0x72667374,&result);break;
    case 7: {
        int a=StyleTrackerGetEventCount(team,63),b=StyleTrackerGetEventCount(team,11);
        int c=StyleTrackerGetEventCount(team,42),d=StyleTrackerGetEventCount(team,113);
        int e=StyleTrackerGetEventCount(team,110);result=a+b+c+d+e;break;
    }
    case 8:
        fn_8022B7A4(handle,0x74727374,&value);result+=value;
        fn_8022B7A4(handle,0x74507374,&value);result+=value;
        fn_8022B7A4(handle,0x64647374,&value);result+=value;
        fn_8022B7A4(handle,0x69707374,&value);result+=value;
        result+=vfn_24(team,0x61746467);
        result+=vfn_24(team,0x72666C67);break;
    case 10:break;
    case 11:
        fn_8022B7A4(handle,0x75667374,&value);result+=value*5;
        fn_8022B7A4(handle,0x70447374,&value);result+=value;break;
    case 12:result=StyleTrackerGetTotal(team);break;
    case 13:
        fn_8022B7A4(handle,0x69447374,&result);
        result+=vfn_24(team,0x72666C67);break;
    case 14: {
        int a=StyleTrackerGetEventCount(team,77),b=StyleTrackerGetEventCount(team,103);result=a+b;break;
    }
    case 15: {
        int a=StyleTrackerGetEventCount(team,74),b=StyleTrackerGetEventCount(team,75);
        int c=StyleTrackerGetEventCount(team,105);result=a+b+c;break;
    }
    }
    return result;
}

int Class_80148A58::vfn_34(int kind, int team, int threshold, int mode)
{
    int value=vfn_33(kind,team);
    int other=(team+1)&1;
    int result=1;
    if((mode==0 && value<vfn_33(kind,other)) || (mode==1 && value>vfn_33(kind,other)))result=0;
    if((mode==0 && value<threshold) || (mode==1 && value>threshold))result=0;
    return result;
}

extern "C" {

void fn_8014A6A0(const int *pValues,int *pOrder,unsigned int count)
{
    int has0=0,has2=0,has3=0,has1=0,has4=0,has5=0,has6=0;
    for(unsigned char i=0;i<count;i++) {
        if(pOrder[0]==pValues[i])has0=1;
        else if(pOrder[2]==pValues[i])has2=1;
        else if(pOrder[3]==pValues[i])has3=1;
        else if(pOrder[1]==pValues[i])has1=1;
        else if(pOrder[4]==pValues[i])has4=1;
        else if(pOrder[5]==pValues[i])has5=1;
        else if(pOrder[6]==pValues[i])has6=1;
    }
    int temp;
    if(!has0) {
        if(has1) {temp=pOrder[0];pOrder[0]=pOrder[1];pOrder[1]=temp;has1=0;}
        else if(has4) {temp=pOrder[0];pOrder[0]=pOrder[4];pOrder[4]=temp;has4=0;}
        else if(has5) {temp=pOrder[0];pOrder[0]=pOrder[5];pOrder[5]=temp;has5=0;}
        else if(has6) {temp=pOrder[0];pOrder[0]=pOrder[6];pOrder[6]=temp;has6=0;}
    }
    if(!has2) {
        if(has1) {temp=pOrder[2];pOrder[2]=pOrder[1];pOrder[1]=temp;has1=0;}
        else if(has6) {temp=pOrder[2];pOrder[2]=pOrder[6];pOrder[6]=temp;has6=0;}
        else if(has4) {temp=pOrder[2];pOrder[2]=pOrder[4];pOrder[4]=temp;has4=0;}
        else if(has5) {temp=pOrder[2];pOrder[2]=pOrder[5];pOrder[5]=temp;has5=0;}
    }
    if(!has3) {
        if(has1) {temp=pOrder[3];pOrder[3]=pOrder[1];pOrder[1]=temp;}
        else if(has6) {temp=pOrder[3];pOrder[3]=pOrder[6];pOrder[6]=temp;}
        else if(has4) {temp=pOrder[3];pOrder[3]=pOrder[4];pOrder[4]=temp;}
        else if(has5) {temp=pOrder[3];pOrder[3]=pOrder[5];pOrder[5]=temp;}
    }
}

void fn_8014A8D8(const int *pValues,int *pOrder,unsigned int count)
{
    int has11=0,has9=0,has13=0,has10=0,has7=0,has12=0,has8=0;
    for(unsigned char i=0;i<count;i++) {
        if(pOrder[11]==pValues[i])has11=1;
        else if(pOrder[13]==pValues[i])has13=1;
        else if(pOrder[9]==pValues[i])has9=1;
        else if(pOrder[10]==pValues[i])has10=1;
        else if(pOrder[7]==pValues[i])has7=1;
        else if(pOrder[12]==pValues[i])has12=1;
        else if(pOrder[8]==pValues[i])has8=1;
    }
    int temp;
    if(!has11) {
        if(has12) {temp=pOrder[11];pOrder[11]=pOrder[12];pOrder[12]=temp;has12=0;}
        else if(has9) {temp=pOrder[11];pOrder[11]=pOrder[9];pOrder[9]=temp;has9=0;}
        else if(has10) {temp=pOrder[11];pOrder[11]=pOrder[10];pOrder[10]=temp;has10=0;}
        else if(has7) {temp=pOrder[11];pOrder[11]=pOrder[7];pOrder[7]=temp;has7=0;}
        else if(has8) {temp=pOrder[11];pOrder[11]=pOrder[8];pOrder[8]=temp;has8=0;}
    }
    if(!has13) {
        if(has12) {temp=pOrder[13];pOrder[13]=pOrder[12];pOrder[12]=temp;}
        else if(has9) {temp=pOrder[13];pOrder[13]=pOrder[9];pOrder[9]=temp;}
        else if(has10) {temp=pOrder[13];pOrder[13]=pOrder[10];pOrder[10]=temp;}
        else if(has7) {temp=pOrder[13];pOrder[13]=pOrder[7];pOrder[7]=temp;}
        else if(has8) {temp=pOrder[13];pOrder[13]=pOrder[8];pOrder[8]=temp;}
    }
}

} /* extern "C" */

int Class_802A2560::IsTimed()
{return 1;}

int Class_802A2560::IsWinAwarded()
{return lbl_803EB2B4;}

int Class_802A2560::GetGameTime()
{return 120;}

void Class_802A2560::ResetPlaySpot()
{
    ScrmRuleSet::ResetPlaySpot();
    fn_80177F88(1);
    if(fn_800A2178()==0 || fn_800A2178()==11)fn_80178CD8(1);
    int team=fn_80178308();
    if(team!=fn_80178348()) {
        fn_8017833C(fn_80178348());
        fn_80178CD8(1);
    }
}

int Class_802A2560::GetScoreLimit()
{return 0x7FFFFFFF;}

int Class_802A2560::GetWinner()
{
    int result = 2;
    int first = fn_801787DC(0);
    int second = fn_801787DC(1);
    if (lbl_803EB2B4 && fn_8009D990(1) == 0) {
        if (first > second) {
            result = 0;
        } else if (first < second) {
            result = 1;
        }
    } else {
        result = 2;
    }
    return result;
}

void Class_802A2560::ResetGame(int team)
{
    ScrmRuleSet::ResetGame(team);
    lbl_803EB2B4 = 0;
}

void Class_802A2560::AwardWin(int team)
{
    lbl_803EB2B4 = 1;
    unsigned short points;
    if (team == 0) {
        points = fn_801787DC(1);
    } else {
        points = fn_801787DC(0);
    }
    int score = points + 1;
    fn_801787FC(team, score);
    fn_800C87CC(team, score);
    ClockRuleClearFlags(2048);
    fn_8009D8CC(1);
    fn_8009D964(1, 0);
}

void Class_802A2788::OnEnter(float dt)
{
    PreGamePhase::OnEnter(dt);
    fn_80178E88(fn_80178A2C() * 2.0f - 20.0f);
    fn_801790D0(fn_80178308(), 0.0f, 0.0f);
    fn_801790D0(fn_80178320(), 5.0f, 3.0f);
    fn_80178A20(fn_80178A2C() * 2.0f);
    ClockRuleSetFlags(2048);
    lbl_803EB2B4 = 0;
    fn_8017833C(1);
    lbl_803EB2B5 = 0;
    HudClearEvent71();
    TutorialReleasePause();
}

void Class_802A2788::OnUpdate(float dt)
{
    if (MsgBoxIsClosed()) {
        PreGamePhase::OnUpdate(dt);
    }
}

void Class_802A2788::ShowIntroScreen()
{
    if (fn_800C1E40() == 0) {
        MsgBoxShow("2 Minute Challenge", lbl_803EB2B0, "|^Done");
    }
}

Record_80148C4C lbl_802DE130[14] = {
    {0, {0, 0, 0, 0, 0, 0, 10, 0, 0, 0}, 0},
    {1, {8, 8, 5, 10, 10, 5, 0, 0, 10, 0}, 0},
    {2, {8, 8, 5, 10, 10, 5, 0, 0, 10, 0}, 0},
    {3, {8, 8, 5, 10, 10, 5, 0, 0, 10, 0}, 0},
    {4, {8, 8, 5, 10, 10, 5, 0, 0, 10, 0}, 0},
    {5, {8, 8, 5, 10, 10, 5, 0, 0, 10, 0}, 0},
    {6, {8, 8, 5, 10, 10, 5, 0, 0, 10, 0}, 0},
    {7, {8, 8, 5, 10, 10, 5, 0, 0, 10, 0}, 0},
    {8, {8, 8, 5, 10, 10, 5, 0, 0, 10, 0}, 0},
    {9, {8, 8, 5, 10, 10, 5, 0, 0, 10, 0}, 0},
    {10, {8, 8, 5, 10, 10, 5, 0, 0, 10, 0}, 0},
    {11, {8, 8, 5, 10, 10, 5, 0, 0, 10, 0}, 0},
    {12, {8, 8, 5, 10, 10, 5, 0, 0, 10, 0}, 0},
    {13, {8, 8, 5, 10, 10, 5, 0, 0, 10, 0}, 0},
};

int lbl_802DE3D0[19] = {21, 20, 16, 15, 14, 13, 2, 1, 9, 11, 3, 7, 4, 5, 6, 8, 12, 10, 0};

void Class_802A24F8::vfn_03(float dt)
{
    ClockRuleClearFlags(2048);
    fn_8009D8CC(1);
    fn_80148A58()->vfn_12();
    fn_80148A58()->vfn_17(lbl_802DE3D0);
    fn_8021D7B8(gUISMainInfo, 0x8000003A, 0, 0);
    Class_80297B90::vfn_03(dt);
}

void Class_802A24F8::vfn_08()
{
    PauseOpenScreen(3, 17, -1);
}

void Class_802A24F8::vfn_09()
{
    fn_8021956C(gUISMainInfo, 3, 17, 1);
}

void Class_802A2748::vfn_03(float dt)
{
    fn_801487C0(fn_80178308(), 3);
    fn_801487C0(fn_80178320(), 2);
    if (fn_800B65A0(fn_80178308()) != 255) {
        Class_80297B50::vfn_03(dt);
    } else {
        BallResetToSpot();
    }
}

void Class_802A2748::vfn_04(float dt)
{
    if (fn_800B65A0(fn_80178308()) != 255) {
        Class_80297B50::vfn_04(dt);
    } else {
        int team = fn_80178308();
        int other = team == 0;
        PlayBookSetFormationType(team, 1);
        PlayBookSetFormationType(other, 11);
        PlayCallScriptRunOffense(0);
        PlayBookLoadCurrentPlay(team);
        PlayBookSetIndices(other, 0, 0, 0);
        PlayBookLoadCurrentPlay(other);
        FormationLineupApplyUser(PlayBookGetTeam(0)->mUnknown40, 0);
        FormationLineupApplyUser(PlayBookGetTeam(1)->mUnknown40, 1);
        fn_800B3EFC(team);
        fn_800B3EFC(other);
        fn_800AD910(2, dt);
    }
    fn_80148A58()->vfn_15();
}

void Class_802A2748::vfn_05(float dt)
{
    if (fn_800B65A0(fn_80178308()) != 255) {
        Class_80297B50::vfn_05(dt);
    } else {
        fn_8009D888(0, 10);
        CamGameResumeAll();
        ScrmTeamPlaceInHuddle(fn_80178308());
        ScrmTeamPlaceInHuddle(fn_80178320());
        fn_8009D944(1);
        fn_8009D944(0);
        short value = 9 - SyncRandGetRange(0, 5);
        lbl_803EABA4->fn_800C02EC(value);
    }
}

int Class_802A2748::vfn_06()
{
    return 10;
}

void Class_802A26D8::OnEnter(float dt)
{
    fn_801486A8();
    PreSnapPhase::OnEnter(dt);
    fn_801487C0(fn_80178308(), 3);
    fn_801487C0(fn_80178320(), 2);
    short value = 9 - SyncRandGetRange(0, 5);
    lbl_803EABA4->fn_800C02EC(value);
    Ball_t *pBall = BallGetCurrent();
    Vector_80039F5C pos;
    BallGetPosition(pBall, &pos);
    BallGiveToPlayer(pBall, PlyrFindNearest(&pos, 0, fn_80178308()));
}

void Class_802A26D8::OnUpdate(float dt)
{
    PreSnapPhase::OnUpdate(dt);
    fn_80148A58()->vfn_15();
    if (fn_8009D990(1) == 0) {
        fn_80178370();
    }
}

void Class_802A26A0::OnEnter(float dt)
{
    ClockRuleSetFlags(2048);
    LivePlayPhase::OnEnter(dt);
}

void Class_802A26A0::OnUpdate(float dt)
{
    LivePlayPhase::OnUpdate(dt);
    fn_80148A58()->vfn_15();
    if (fn_8011F1CC() && fn_801783AC(0) && !fn_801783AC(13) && !fn_801783AC(1) &&
        !fn_801783AC(20)) {
        fn_80178370();
        HudShowAlert("Passer Cannot Run!");
    } else if (fn_80178308() != fn_80178348()) {
        fn_80178370();
    }
}

int Class_802A2618::GetResultText(char *pText)
{
    if (fn_8009D990(1) != 0 || lbl_803EB2B4 != 0) {
        return PostPlayPhase::GetResultText(pText);
    }
    strcpy(pText, "Switch Sides!");
    return 1;
}

void Class_802A2618::OnUpdate(float dt)
{
    PostPlayPhase::OnUpdate(dt);
    fn_80148A58()->vfn_15();
}

void Class_802A2618::Finish(float dt)
{
    PlyrMgrClearStates();
    if (InGameOverlayGetState() != 4) {
        InGameOverlayReset();
    }
    if (fn_8009D990(1)) {
        fn_800AD910(5, dt);
    } else {
        int pending = 0;
        ClockRuleClearFlags(2048);
        fn_8009D8CC(1);
        ClockRuleClearFlags(16);
        if (fn_80178AE0() == 2) {
            if (lbl_803EB2B4) {
                lbl_803EB2B5 = 1;
            }
            if (lbl_803EB2B5) {
                fn_8009D964(1, 30);
            } else {
                fn_8009D964(1, 120);
            }
            fn_8017833C(fn_80178360());
            fn_80178CD8(1);
            lbl_803EB2B4 = !lbl_803EB2B4;
            fn_800AD910(5, 0.0f);
        } else {
            pending = 1;
        }
        if (pending) {
            ClockRuleEndPeriod();
        }
    }
}

char *lbl_803EB2B8 = "4 on 4\n\nThe game rules are a little different than the normal game.  First team to %d points wins this game.  Touchdowns are worth 6 points, and turnovers are worth 3 points each.  The QB only has 5 seconds to pass and cannot run with the ball.";
char *lbl_803EB2BC = "Passer Cannot Run!";
char *lbl_803EB2C0 = "Pass Clock Expired";
char *lbl_803EB2C4 = "Inside the Five!";
char *lbl_803EB2C8 = "3 Pt. Turnover";
char *lbl_803EB2CC = "Turnover TD";
unsigned char lbl_803EB2D0 = 0;
unsigned char lbl_803EB2D1 = 0;

 /* extern "C" */

Class_802A2DB8::Class_802A2DB8()
{
    mState.mCount = 14;
    mState.mpRecords = lbl_802DE130;
}

Class_802A2DB8::~Class_802A2DB8()
{
    mState.mCount = 0;
    mState.mpRecords = 0;
}

void Class_802A2DB8::vfn_01()
{
    unsigned int i;
    int id;

    mUnknown0 = 13;
    mUnknown4 = 12;
    mState.mUnknownC = 0;
    mpUnknown1C = new (0) States_802A2DB8;
    mpUnknown1C->mUnknown1C = GameOptionsGet(14);
    if (mpUnknown1C->mUnknown1C != 0) {
        GameOptionsSet(14, 0);
    }
    fn_800BC51C(&mpUnknown1C->mUnknown0);
    fn_800B3644(&mpUnknown1C->mUnknown4);
    fn_800BFAB4(&mpUnknown1C->mUnknown8);
    fn_800A039C(&mpUnknown1C->mUnknownC);
    fn_800B9598(&mpUnknown1C->mUnknown10);
    fn_800AACB8(&mpUnknown1C->mUnknown14);
    mpUnknown1C->mUnknown18.ResetGame(2);
    fn_80178F20(&mpUnknown1C->mUnknown18);
    mpUnknown1C->mUnknown38 = GameOptionsGet(19);
    if (mpUnknown1C->mUnknown38 != 0) {
        GameOptionsSet(19, 0);
    }
    id = 0;
    for (i = 0; i < 2; i++) {
        Object_8008044C cursor;
        Desc_8008044C desc;
        desc.mUnknown0 = 0;
        desc.mUnknown4 = 1;
        desc.mUnknown12 = 0;
        desc.mUnknown8 = i;
        PlayerCursorOpenDefault(&cursor, &desc);
        if (DepthChartGetEntry(i, 0, &id)) {
            PlayerDbSeekOriginalId(&cursor, id, 0);
            id = PlayerDbGetId(&cursor);
        }
        mpUnknown1C->mUnknown20[i][0] = id;
        if (DepthChartGetEntry(i, 2, &id)) {
            PlayerDbSeekOriginalId(&cursor, id, 0);
            id = PlayerDbGetId(&cursor);
        }
        mpUnknown1C->mUnknown20[i][1] = id;
        if (DepthChartGetEntry(i, 3, &id)) {
            PlayerDbSeekOriginalId(&cursor, id, 0);
            id = PlayerDbGetId(&cursor);
        }
        mpUnknown1C->mUnknown20[i][2] = id;
        PlayerCursorClose(&cursor);
    }
}

void Class_802A2DB8::vfn_02()
{
    if (mpUnknown1C->mUnknown38 != 0) {
        GameOptionsSet(19, 1);
    }
    fn_800BC51C(0);
    fn_800B3644(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_800AACB8(0);
    if (mpUnknown1C->mUnknown1C != 0) {
        GameOptionsSet(14, mpUnknown1C->mUnknown1C);
    }
    fn_80178F20(0);
    delete mpUnknown1C;
    mpUnknown1C = 0;
}

int Class_802A2DB8::vfn_08(int a)
{
    return 2;
}

int Class_802A2DB8::vfn_05(int team)
{
    if (team == fn_80178308()) {
        return 3;
    }
    return 2;
}

void Class_802A2DB8::vfn_10(int value, int *pList, int *pIds)
{
    AutoDepthFillChart(value, pList, pIds);
    fn_8014A6A0(pList, pIds, 3);
    fn_8014A8D8(pList, pIds, 3);
}

void Class_802A2DB8::vfn_11(int value, int *pList, int *pIds, unsigned int count, int slot)
{
    AutoDepthFillChart(value, pList, pIds);
    int first = pList[0];
    switch (slot) {
    case 0:
    case 2:
    case 3:
        break;
    default:
        slot = 3;
        break;
    }
    for (unsigned char i = 0; i < 7; i++) {
        if (pIds[i] == first) {
            pIds[i] = pIds[slot];
            pIds[slot] = first;
            break;
        }
    }
    fn_8014A6A0(pList, pIds, count);
    int values[3];
    values[0] = pIds[0];
    values[1] = pIds[2];
    values[2] = pIds[3];
    fn_8014A8D8(values, pIds, 3);
}

extern "C" {

void fn_8014BA20(Class_802A2DB8 *p, int team, Stats_8005C844 *pStats)
{
    int value = 0;
    int handle = fn_800C8744(team);
    for (unsigned char i = 0; i < 3; i++) {
        pStats->mpPlayers[i] = PlyrFindById(p->mpUnknown1C->mUnknown20[team][i]);
    }
    pStats->mValues[0] = fn_801787DC((unsigned char)team);
    fn_8022B7A4(handle, 0x74727374, &value);
    pStats->mValues[1] += value;
    fn_8022B7A4(handle, 0x74507374, &value);
    pStats->mValues[1] += value;
    fn_8022B7A4(handle, 0x64647374, &value);
    pStats->mValues[1] += value;
    fn_8022B7A4(handle, 0x69447374, &value);
    pStats->mValues[3] = value;
    fn_8022B7A4(handle, 0x72667374, &value);
    pStats->mValues[2] = value;
}

} /* extern "C" */

int Class_802A2DB8::vfn_32(int team, int kind)
{
    int result = 0;
    switch (kind) {
    case 16:
        if (fn_801787DC(team) >= fn_801787DC((team + 1) & 1) - 3 && vfn_34(2, team, 100, 1)) {
            result = 1;
        }
        break;
    case 20:
        if (fn_801787DC(team) > 99) {
            result = 1;
        }
        break;
    case 21:
        if (fn_801787DC(team) < 0) {
            result = 1;
        }
        break;
    default:
        result = Class_80148A58::vfn_32(team, kind);
        break;
    }
    return result;
}

int Class_802A2DB8::vfn_33(int kind, int team)
{
    switch (kind) {
    case 16:
    case 20:
    case 21:
        return fn_801787DC(team);
    default:
        return Class_80148A58::vfn_33(kind, team);
    }
}

int Class_802A2DB8::vfn_21()
{
    return 0;
}

extern "C" {

int fn_8014BC90(void)
{
    return 0;
}

void fn_8014BC98(const int *pValues, int *pOrder, unsigned int count)
{
    int has0 = 0, has2 = 0, has3 = 0, has1 = 0, has4 = 0, has5 = 0, has6 = 0;
    for (unsigned char i = 0; i < count; i++) {
        if (pOrder[0] == pValues[i]) {
            has0 = 1;
        } else if (pOrder[2] == pValues[i]) {
            has2 = 1;
        } else if (pOrder[3] == pValues[i]) {
            has3 = 1;
        } else if (pOrder[1] == pValues[i]) {
            has1 = 1;
        } else if (pOrder[4] == pValues[i]) {
            has4 = 1;
        } else if (pOrder[5] == pValues[i]) {
            has5 = 1;
        } else if (pOrder[6] == pValues[i]) {
            has6 = 1;
        }
    }
    int temp;
    if (!has0) {
        if (has4) {
            temp = pOrder[0];
            pOrder[0] = pOrder[4];
            pOrder[4] = temp;
            has4 = 0;
        } else if (has5) {
            temp = pOrder[0];
            pOrder[0] = pOrder[5];
            pOrder[5] = temp;
            has5 = 0;
        } else if (has6) {
            temp = pOrder[0];
            pOrder[0] = pOrder[6];
            pOrder[6] = temp;
            has6 = 0;
        }
    }
    if (!has2) {
        if (has4) {
            temp = pOrder[2];
            pOrder[2] = pOrder[4];
            pOrder[4] = temp;
            has4 = 0;
        } else if (has5) {
            temp = pOrder[2];
            pOrder[2] = pOrder[5];
            pOrder[5] = temp;
            has5 = 0;
        } else if (has6) {
            temp = pOrder[2];
            pOrder[2] = pOrder[6];
            pOrder[6] = temp;
            has6 = 0;
        }
    }
    if (!has3) {
        if (has4) {
            temp = pOrder[3];
            pOrder[3] = pOrder[4];
            pOrder[4] = temp;
            has4 = 0;
        } else if (has5) {
            temp = pOrder[3];
            pOrder[3] = pOrder[5];
            pOrder[5] = temp;
            has5 = 0;
        } else if (has6) {
            temp = pOrder[3];
            pOrder[3] = pOrder[6];
            pOrder[6] = temp;
            has6 = 0;
        }
    }
    if (!has1) {
        if (has4) {
            temp = pOrder[1];
            pOrder[1] = pOrder[4];
            pOrder[4] = temp;
        } else if (has5) {
            temp = pOrder[1];
            pOrder[1] = pOrder[5];
            pOrder[5] = temp;
        } else if (has6) {
            temp = pOrder[1];
            pOrder[1] = pOrder[6];
            pOrder[6] = temp;
        }
    }
}

void fn_8014BED8(const int *pValues, int *pOrder, unsigned int count)
{
    int has11 = 0, has9 = 0, has13 = 0, has10 = 0, has7 = 0, has12 = 0, has8 = 0;
    for (unsigned char i = 0; i < count; i++) {
        if (pOrder[11] == pValues[i]) {
            has11 = 1;
        } else if (pOrder[9] == pValues[i]) {
            has9 = 1;
        } else if (pOrder[13] == pValues[i]) {
            has13 = 1;
        } else if (pOrder[10] == pValues[i]) {
            has10 = 1;
        } else if (pOrder[7] == pValues[i]) {
            has7 = 1;
        } else if (pOrder[12] == pValues[i]) {
            has12 = 1;
        } else if (pOrder[8] == pValues[i]) {
            has8 = 1;
        }
    }
    int temp;
    if (!has11) {
        if (has7) {
            temp = pOrder[11];
            pOrder[11] = pOrder[7];
            pOrder[7] = temp;
            has7 = 0;
        } else if (has12) {
            temp = pOrder[11];
            pOrder[11] = pOrder[12];
            pOrder[12] = temp;
            has12 = 0;
        } else if (has8) {
            temp = pOrder[11];
            pOrder[11] = pOrder[8];
            pOrder[8] = temp;
            has8 = 0;
        }
    }
    if (!has9) {
        if (has7) {
            temp = pOrder[9];
            pOrder[9] = pOrder[7];
            pOrder[7] = temp;
            has7 = 0;
        } else if (has12) {
            temp = pOrder[9];
            pOrder[9] = pOrder[12];
            pOrder[12] = temp;
            has12 = 0;
        } else if (has8) {
            temp = pOrder[9];
            pOrder[9] = pOrder[8];
            pOrder[8] = temp;
            has8 = 0;
        }
    }
    if (!has13) {
        if (has7) {
            temp = pOrder[13];
            pOrder[13] = pOrder[7];
            pOrder[7] = temp;
            has7 = 0;
        } else if (has12) {
            temp = pOrder[13];
            pOrder[13] = pOrder[12];
            pOrder[12] = temp;
            has12 = 0;
        } else if (has8) {
            temp = pOrder[13];
            pOrder[13] = pOrder[8];
            pOrder[8] = temp;
            has8 = 0;
        }
    }
    if (!has10) {
        if (has7) {
            temp = pOrder[10];
            pOrder[10] = pOrder[7];
            pOrder[7] = temp;
        } else if (has12) {
            temp = pOrder[10];
            pOrder[10] = pOrder[12];
            pOrder[12] = temp;
        } else if (has8) {
            temp = pOrder[10];
            pOrder[10] = pOrder[8];
            pOrder[8] = temp;
        }
    }
}

} /* extern "C" */

void Class_802A2450::vfn_03(float dt)
{
    Class_80297B50::vfn_03(dt);
    fn_801487C0(0, 4);
    fn_801487C0(1, 4);
}

int Class_802A2268::GetTeamSize()
{
    return 4;
}

int Class_802A2268::AllowsPrediction()
{
    return 1;
}

void Class_802A2320::OnEnter(float dt)
{
    PostPlayPhase::OnEnter(dt);
    fn_8009D8CC(5);
}

void Class_802A2320::ShowResultText()
{
    char text[32];
    int changed = PostPlayPhase::GetResultText(text);
    if (fn_800A2178() == 14) {
        changed = 1;
        strcpy(text, lbl_803EB2CC);
    } else if (fn_80178308() != fn_80178348()) {
        changed = 1;
        strcpy(text, lbl_803EB2C8);
    }
    if (changed) {
        fn_800B925C(this, text);
    }
}

void Class_802A2320::OnUpdate(float dt)
{
    PostPlayPhase::OnUpdate(dt);
    if ((unsigned char)fn_800B9A90(lbl_803EAB84)) {
        if (fn_8014BC90()) {
            if (!lbl_803EB2D0) {
                HudShowAlert(lbl_803EB2C4);
                lbl_803EB2D0 = 1;
            }
        } else {
            lbl_803EB2D0 = 0;
        }
    }
}

void Class_802A23A8::OnEnter(float dt)
{
    LivePlayPhase::OnEnter(dt);
    if (fn_800A937C() == 0) {
        fn_8009D888(5, 0);
    }
    unsigned char blocked = 0;
    if ((fn_800A8444(0) && fn_800A8EA4(0) == 2) || (fn_800A8444(1) && fn_800A8EA4(1) == 2)) {
        blocked = 1;
    }
    mUnknown4 = blocked;
}

void Class_802A23A8::OnUpdate(float dt)
{
    int clear = 1;
    LivePlayPhase::OnUpdate(dt);
    if (fn_800A937C() == 0) {
        unsigned char i;
        for (i = 0; i <= 6; i++) {
            Object_80039F5C *pPlayer = PlyrGet(fn_80178308(), i);
            if (fn_800F06F4(0, pPlayer->mpState, 18, 0xFFFF) != 0xFFFF) {
                clear = 0;
            }
            if (fn_800F06F4(0, pPlayer->mpState, 26, 0xFFFF) != 0xFFFF) {
                clear = 0;
            }
        }
        if (clear || fn_801783AC(13) || fn_801783AC(1)) {
            fn_8009D8CC(5);
        }
        Object_80039F5C *pCarrier = BallGetCurrentHolder();
        int special = 0;
        if (pCarrier) {
            special = pCarrier->mpState->mId == 16;
        }
        if (fn_8011F1CC() && fn_801783AC(0) && !fn_801783AC(13) && !fn_801783AC(1) &&
            !fn_801783AC(20) && !mUnknown4 && !special) {
            fn_80178370();
            HudShowAlert(lbl_803EB2BC);
        } else if (fn_80178308() != fn_80178348()) {
            fn_80178370();
        } else if (fn_8009D990(5) == 0 && !mUnknown4) {
            fn_80178370();
            HudShowAlert(lbl_803EB2C0);
        }
    }
}

void Class_802A23E0::OnEnter(float dt)
{
    fn_801486A8();
    PreSnapPhase::OnEnter(dt);
    fn_801487C0(0, 4);
    fn_801487C0(1, 4);
    fn_8009D964(5, 5);
}

void Class_802A2490::OnEnter(float dt)
{
    PreGamePhase::OnEnter(dt);
    fn_80178E88(5.0f);
    fn_801790D0(fn_80178308(), 0.0f, 0.0f);
    fn_801790D0(fn_80178320(), 3.0f, 0.0f);
    fn_80178A20(fn_80178A2C());
    fn_8009D964(5, 5);
    lbl_803EB2D0 = 1;
    lbl_803EB2D1 = 0;
    TutorialReleasePause();
}

void Class_802A2490::OnUpdate(float dt)
{
    if (MsgBoxIsClosed()) {
        if (!lbl_803EB2D1 && fn_800C1E40() == 0) {
            fn_80218FC4(gUISMainInfo, 3, 8, 0, 0);
            lbl_803EB2D1 = 1;
        }
        PreGamePhase::OnUpdate(dt);
    }
}

 /* extern "C" */

Record_80148C4C lbl_802DE41C[14] = {
    {0, {0, 0, 6, 0, 2, 0, 10, 0, 0, 0}, 0},
    {4, {6, 0, 9, 3, 7, 4, 0, 3, 4, 3}, 0},
    {5, {8, 6, 6, 8, 10, 6, 0, 0, 6, 0}, 0},
    {6, {6, 6, 6, 6, 10, 6, 0, 0, 8, 0}, 0},
    {1, {6, 0, 10, 6, 6, 0, 0, 0, 0, 0}, 0},
    {2, {6, 8, 4, 8, 10, 6, 0, 0, 0, 0}, 0},
    {3, {4, 4, 6, 8, 8, 0, 0, 6, 0, 0}, 0},
    {7, {4, 0, 6, 8, 10, 6, 0, 0, 8, 0}, 0},
    {8, {4, 0, 0, 0, 10, 6, 0, 0, 8, 0}, 0},
    {9, {0, 0, 0, 0, 2, 2, 10, 0, 0, 0}, 0},
    {10, {0, 2, 0, 0, 8, 10, 0, 0, 6, 0}, 0},
    {11, {0, 8, 0, 0, 10, 6, 0, 0, 8, 0}, 0},
    {12, {4, 0, 0, 0, 10, 6, 0, 0, 8, 0}, 0},
    {13, {0, 6, 0, 0, 10, 6, 0, 0, 8, 0}, 0},
};

Record_80148C4C lbl_802DE6BC[14] = {
    {0, {0, 0, 0, 0, 0, 0, 10, 0, 0, 0}, 0},
    {4, {6, 0, 9, 3, 7, 4, 0, 3, 4, 3}, 0},
    {5, {8, 6, 6, 8, 10, 6, 0, 0, 6, 0}, 0},
    {6, {6, 6, 6, 6, 10, 6, 0, 0, 8, 0}, 0},
    {1, {6, 0, 10, 6, 6, 0, 0, 0, 0, 0}, 0},
    {2, {6, 8, 4, 8, 10, 6, 0, 0, 0, 0}, 0},
    {3, {4, 4, 6, 8, 8, 0, 0, 6, 0, 0}, 0},
    {7, {4, 0, 6, 8, 10, 6, 0, 0, 8, 0}, 0},
    {8, {4, 0, 0, 0, 10, 6, 0, 0, 8, 0}, 0},
    {9, {0, 0, 0, 0, 2, 2, 10, 0, 0, 0}, 0},
    {10, {0, 2, 0, 0, 8, 10, 0, 0, 6, 0}, 0},
    {11, {0, 8, 0, 0, 10, 6, 0, 0, 8, 0}, 0},
    {12, {4, 0, 0, 0, 10, 6, 0, 0, 8, 0}, 0},
    {13, {0, 6, 0, 0, 10, 6, 0, 0, 8, 0}, 0},
};

Class_802A2C90::Class_802A2C90()
{
    mpUnknown1C = 0;
    mUnknown20 = -1;
    mState.mCount = 14;
    mState.mpRecords = lbl_802DE41C;
}

void Class_802A2C90::vfn_01()
{
    mUnknown0 = 10;
    mUnknown4 = 9;
    mpUnknown1C = new (0) Block_802A21E8;
    mpUnknown1C->mUnknown20 = GameOptionsGet(14);
    if (mpUnknown1C->mUnknown20 != 0) {
        GameOptionsSet(14, 0);
    }
    if (mUnknown20 != -1) {
        mpUnknown1C->mUnknown24 = GameOptionsGet(1);
        GameOptionsSet(1, mUnknown20);
    } else {
        mpUnknown1C->mUnknown24 = -1;
    }
    fn_800BC51C(&mpUnknown1C->mUnknown0);
    fn_800B3644(&mpUnknown1C->mUnknown4);
    fn_800BFAB4(&mpUnknown1C->mUnknown8);
    fn_800A039C(&mpUnknown1C->mUnknownC);
    fn_800B9598(&mpUnknown1C->mUnknown14);
    fn_800AACB8(&mpUnknown1C->mUnknown1C);
    mpUnknown1C->mUnknown18.ResetGame(2);
    fn_80178F20(&mpUnknown1C->mUnknown18);
}

void Class_802A2490::ShowIntroScreen()
{
    char text[300];

    if (fn_800C1E40() == 0) {
        int value = GameOptionsGet(1);
        fn_801C2D88(text, sizeof(text), lbl_803EB2B8, value);
        MsgBoxShow("4 on 4", text, "|^Done");
    }
}

char *lbl_803EB2D4 = "Crush the Carrier\n\nScore more points than your opponents to win the game.  You'll earn the most points by Stylin' and holding onto the ball.  Keep in mind that tackles are worth big points too.";
int lbl_803EB2D8 = 0;
int lbl_803EB2DC = 0;
Object_80039F5C *lbl_803EB2E0 = 0;

void Class_802A2490::HideIntroScreen()
{
    if (lbl_803EB2D1) {
        fn_8021956C(gUISMainInfo, 3, 8, 1);
        lbl_803EB2D1 = 0;
    }
}

int lbl_802DE95C[16] = {41, 15, 14, 13, 12, 11, 9, 7, 6, 5, 4, 3, 2, 1, 10, 0};

void Class_802A2200::vfn_03(float dt)
{
    ClockRuleClearFlags(2048);
    fn_8009D8CC(1);
    fn_80148A58()->vfn_12();
    fn_80148A58()->vfn_17(lbl_802DE95C);
    fn_8021D7B8(gUISMainInfo, 0x8000003A, 0, 0);
    Class_80297B90::vfn_03(dt);
}

void Class_802A2200::vfn_08()
{
    PauseOpenScreen(3, 24, -1);
}

void Class_802A2200::vfn_09()
{
    fn_8021956C(gUISMainInfo, 3, 24, 1);
}

void Class_802A2C90::vfn_02()
{
    fn_800BC51C(0);
    fn_800B3644(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_800AACB8(0);
    if (mpUnknown1C->mUnknown20 != 0) {
        GameOptionsSet(14, mpUnknown1C->mUnknown20);
    }
    if (mpUnknown1C->mUnknown24 != -1) {
        GameOptionsSet(1, mpUnknown1C->mUnknown24);
    }
    mUnknown20 = -1;
    fn_80178F20(0);
    delete mpUnknown1C;
    mpUnknown1C = 0;
}

unsigned int Class_802A2C90::vfn_06()
{
    return 7;
}

unsigned int Class_802A2C90::vfn_04(int team)
{
    return 7;
}

int Class_802A2C90::vfn_05(int team)
{
    return 4;
}

int Class_802A2C90::vfn_03()
{
    return 14;
}

int Class_802A2C90::vfn_08(int a)
{
    int result = 0;
    if (fn_8014BC90()) {
        result = 2;
    }
    return result;
}

void Class_802A2C90::vfn_10(int value, int *pList, int *pIds)
{
    AutoDepthFillChart(value, pList, pIds);
    fn_8014BC98(pList, pIds, 4);
    fn_8014BED8(pList, pIds, 4);
}

void Class_802A2C90::vfn_11(int value, int *list, int *ids, unsigned int count, int b)
{
    mState.mpRecords = lbl_802DE6BC;
    AutoDepthFillChart(value, list, ids);
    mState.mpRecords = lbl_802DE41C;
    int first = list[0];
    int offense;
    switch (b) {
    case 0:
    case 1:
    case 2:
    case 3:
        offense = 1;
        break;
    case 9:
    case 10:
    case 11:
    case 13:
        offense = 0;
        break;
    default:
        b = 3;
        offense = 1;
        break;
    }
    unsigned char i;
    int values[4];
    if (offense) {
        for (i = 0; i <= 6; i++) {
            if (ids[i] == first) {
                switch (i) {
                case 0:
                case 1:
                case 2:
                case 3:
                    break;
                default:
                    ids[i] = ids[b];
                    ids[b] = first;
                    break;
                }
            }
        }
        fn_8014BC98(list, ids, count);
        values[0] = ids[0];
        values[1] = ids[2];
        values[2] = ids[3];
        values[3] = ids[1];
        fn_8014BED8(values, ids, 4);
    } else {
        for (i = 7; i <= 13; i++) {
            if (ids[i] == first) {
                switch (i) {
                case 9:
                case 10:
                case 11:
                case 13:
                    break;
                default:
                    ids[i] = ids[b];
                    ids[b] = first;
                    break;
                }
            }
        }
        fn_8014BED8(list, ids, count);
        values[0] = ids[11];
        values[1] = ids[9];
        values[2] = ids[13];
        values[3] = ids[10];
        fn_8014BC98(values, ids, 4);
    }
}

extern "C" {

void fn_8014CCE8(Class_80148A58 *p, int team, Stats_8005CAE4 *pStats)
{
    int ids[4];
    Object_8008044C cursor;
    int id = 0;
    int handle = fn_800C8744(team);
    int value = 0;
    PlayerCursorOpenDefault(&cursor, 0);
    if (DepthChartGetEntry(team, 0, &id)) {
        PlayerDbSeekOriginalId(&cursor, id, 0);
        id = PlayerDbGetId(&cursor);
    }
    ids[0] = id;
    if (DepthChartGetEntry(team, 2, &id)) {
        PlayerDbSeekOriginalId(&cursor, id, 0);
        id = PlayerDbGetId(&cursor);
    }
    ids[1] = id;
    if (DepthChartGetEntry(team, 3, &id)) {
        PlayerDbSeekOriginalId(&cursor, id, 0);
        id = PlayerDbGetId(&cursor);
    }
    ids[2] = id;
    if (DepthChartGetEntry(team, 1, &id)) {
        PlayerDbSeekOriginalId(&cursor, id, 0);
        id = PlayerDbGetId(&cursor);
    }
    ids[3] = id;
    PlayerCursorClose(&cursor);
    for (unsigned char i = 0; i < 4; i++) {
        pStats->mpPlayers[i] = PlyrFindById(ids[i]);
    }
    pStats->mValues[0] = fn_801787DC((unsigned char)team);
    fn_8022B7A4(handle, 0x74727374, &value);
    pStats->mValues[1] += value;
    fn_8022B7A4(handle, 0x74507374, &value);
    pStats->mValues[1] += value;
    fn_8022B7A4(handle, 0x64647374, &value);
    pStats->mValues[1] += value;
    fn_8022B7A4(handle, 0x69447374, &value);
    pStats->mValues[3] = value;
    pStats->mValues[2] = p->vfn_24(team, 0x61746467);
}

} /* extern "C" */

void Class_802A2C90::vfn_14()
{
    if (fn_801486A0() == 4) {
        fn_8009D8CC(5);
        fn_8009D964(5, 5);
    }
}

int Class_802A2C90::vfn_32(int team, int kind)
{
    int result;
    if (kind == 41) {
        result = vfn_34(41, team, 1, 0);
    } else {
        result = Class_80148A58::vfn_32(team, kind);
    }
    return result;
}

int Class_802A2C90::vfn_33(int kind, int team)
{
    int result;
    if (kind == 41) {
        result = StyleTrackerGetEventCount(team, 101);
    } else {
        result = Class_80148A58::vfn_33(kind, team);
    }
    return result;
}

void Class_802A2C90::vfn_07(int a, int b)
{
    if (a == 0) {
        mUnknown20 = b;
    }
}

extern "C" {

void fn_8014D024(unsigned short index)
{
    for (; index != 0; index--) {
        if (fn_8014F104(fn_80148A58())->mpUnknown34[index].mUnknown4 >
            fn_8014F104(fn_80148A58())->mpUnknown34[index - 1].mUnknown4) {
            Record_8014F104 temp = fn_8014F104(fn_80148A58())->mpUnknown34[index];
            fn_8014F104(fn_80148A58())->mpUnknown34[index] = fn_8014F104(fn_80148A58())->mpUnknown34[index - 1];
            fn_8014F104(fn_80148A58())->mpUnknown34[index - 1] = temp;
        } else {
            break;
        }
    }
}

void fn_8014D210(Object_80039F5C *p, int kind, int value)
{
    unsigned short i;
    for (i = 0; i <= 5; i++) {
        if (fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown0 == p->mUnknown2908) {
            fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown4 += value;
            break;
        }
    }
    fn_8014D024(i);
}

void fn_8014D298(int kind, int unused, const char *pText, int value, int addValue, int d, int addText)
{
    int credit = 0;
    Object_80039F5C *pFirst = 0;
    Object_80039F5C *pSecond = 0;
    int statA = 11;
    int statB = 11;
    switch (kind) {
    case 29:
        statA = 3;
        credit = 1;
        break;
    case 27:
    case 28:
    case 32:
    case 33:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 44:
    case 45:
    case 48:
    case 49:
    case 55:
    case 56:
    case 58:
    case 59:
    case 61:
    case 62:
    case 64:
    case 65:
    case 66:
    case 108:
        credit = 1;
        break;
    case 30:
    case 31:
        statA = 2;
        credit = 1;
        break;
    case 34:
    case 35:
    case 46:
    case 47:
    case 50:
    case 51:
    case 109:
    case 111:
        statA = 5;
        credit = 1;
        break;
    case 42:
    case 43:
    case 110:
        statA = 5;
        statB = 6;
        credit = 1;
        break;
    case 57:
    case 60:
    case 112:
        statA = 4;
        credit = 1;
        break;
    case 63:
    case 113:
        statA = 4;
        statB = 6;
        credit = 1;
        break;
    case 86:
    case 87:
    case 88:
    case 89:
        statA = 1;
        credit = 1;
        break;
    case 78:
    case 84:
    case 85:
    case 96:
    case 98:
    case 120: {
        Object_80039F5C *pBallPlayer = BallGetCurrentLastHolder();
        if (pBallPlayer) {
            if (pBallPlayer->mpState->mId == 16) {
                for (unsigned short i = 0; i <= 4; i++) {
                    if (!pFirst) {
                        pFirst = PlyrGet(0, i);
                        if (pBallPlayer->mpState->mUnknown3[0] != i && pFirst->mpState->mId != 17) {
                            pFirst = 0;
                        } else {
                            fn_8014F4D8(fn_80148A58(), pFirst, 0, 1);
                        }
                    } else if (!pSecond) {
                        pSecond = PlyrGet(0, i);
                        if (pBallPlayer->mpState->mUnknown3[0] != i && pSecond->mpState->mId != 17) {
                            pSecond = 0;
                        } else {
                            fn_8014F4D8(fn_80148A58(), pSecond, 0, 1);
                        }
                    } else {
                        break;
                    }
                }
            } else if (pBallPlayer->mUnknown560.mUnknown48) {
                pFirst = fn_8009BCE8(&pBallPlayer->mUnknown560.mUnknown48);
                fn_8014F4D8(fn_80148A58(), pFirst, 0, 1);
            }
        }
        fn_8014F104(fn_80148A58())->mUnknown18.mpUnknown8 = pFirst;
        break;
    }
    }
    if (credit == 1) {
        pFirst = BallGetCurrentHolder();
        if (!pFirst) {
            pFirst = BallGetCurrentLastHolder();
        }
        if (statA != 11) {
            fn_8014F4D8(fn_80148A58(), pFirst, statA, 1);
        }
        if (statB != 11) {
            fn_8014F4D8(fn_80148A58(), pFirst, statB, 1);
        }
    }
    if (pFirst) {
        if (pSecond) {
            value /= 2;
        }
        if (addValue) {
            fn_8014D210(pFirst, kind, value);
        }
        if (addText) {
            HudShowPlayerPopup(pFirst, pFirst->mIdBytes[2], pText, value, d);
        }
        if (pSecond) {
            if (addValue) {
                fn_8014D210(pSecond, kind, value);
            }
            if (addText) {
                HudShowPlayerPopup(pSecond, pSecond->mIdBytes[2], pText, value, d);
            }
        }
    }
}

// Place one player at the center and the other five within the field bounds.
void PlaceSixPlayerFormation(void)
{
    unsigned int first = SyncRandGetRange(0, 6);
    float sectorWidth = 60.0f;
    Object_80039F5C *pPlayer = PlyrGet(1, 0);
    fn_800EFE60(0, pPlayer->mpState, pPlayer);
    PlyrClearPendingMsg(pPlayer, 0);
    pPlayer->mMotion.mPos.mX = 0.0f;
    pPlayer->mMotion.mPos.mY = 0.0f;
    int sectorAngle = (int)(sectorWidth * 46603.378f);
    pPlayer->mUnknown512.mUnknown4 = (first * sectorAngle - sectorAngle / 2) & 0xFFFFFF;
    pPlayer->mUnknown512.mUnknown0 = 1.0f;
    pPlayer->mMotion.mFacing = pPlayer->mUnknown512.mUnknown4;
    pPlayer->mUnknown512.mUnknown8 = pPlayer->mUnknown512.mUnknown4;
    pPlayer->mUnknown512.mUnknown14 = 1;

    for (unsigned char i = 0; i <= 4; i++) {
        pPlayer = PlyrGet(0, i);
        fn_800EFE60(0, pPlayer->mpState, pPlayer);
        PlyrClearPendingMsg(pPlayer, 0);
        unsigned int sector = (i + first) % 6;
        unsigned int spread = SyncRandGetRange(0, 2);
        float degrees = sector * sectorWidth + SyncRandGetRange(0, (unsigned int)sectorWidth);
        float radius = spread + 8.0f;
        Vec2FromAngle(&pPlayer->mMotion.mPos.mX, (int)(degrees * 46603.378f), radius);
        pPlayer->mMotion.mPos.mX = pPlayer->mMotion.mPos.mX < -fn_80178A08() ? -fn_80178A08() :
            (pPlayer->mMotion.mPos.mX > fn_80178A08() ? fn_80178A08() : pPlayer->mMotion.mPos.mX);
        pPlayer->mMotion.mPos.mY = pPlayer->mMotion.mPos.mY < -fn_80178A2C() ? -fn_80178A2C() :
            (pPlayer->mMotion.mPos.mY > fn_80178A2C() ? fn_80178A2C() : pPlayer->mMotion.mPos.mY);
        pPlayer->mUnknown512.mUnknown0 = 1.0f;
        pPlayer->mUnknown512.mUnknown4 = ((int)(degrees * 46603.378f) + 0x800000) & 0xFFFFFF;
        pPlayer->mMotion.mFacing = pPlayer->mUnknown512.mUnknown4;
        pPlayer->mUnknown512.mUnknown8 = pPlayer->mUnknown512.mUnknown4;
        pPlayer->mUnknown512.mUnknown14 = 1;
    }
}

// Display the six records in their current score order.
void RefreshSixPlayerScoreRows(void *p)
{
    for (unsigned char i = 0; i <= 5; i++) {
        char name[24];
        char score[16];
        strcpy(name, PlyrFindById(fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown0)->mUnknown2927 + 21);
        fn_801C2E18(score, "%d", fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown4);
        if (fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown8 != 255) {
            fn_8014F104(fn_80148A58());
        }
        HudSetScoreTableRow(i + 1, name, score, "",
                    fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown8);
    }
}

} /* extern "C" */

void Class_802A20C8::fn_8014DA20()
{
    for (unsigned char team = 0; team <= 1; team++) {
        for (unsigned short i = 0; i <= 6; i++) {
            Object_80039F5C *pPlayer = PlyrGet(team, i);
            fn_80149040(pPlayer);
            fn_800EFE60(0, pPlayer->mpState, pPlayer);
        }
    }
}

void Class_802A2B68::fn_8014DA90()
{
    Block_8014F104 *pBlock = fn_8014F104(fn_80148A58());
    for (unsigned int team = 0; team <= 1; team++) {
        for (unsigned int i = 0; i <= 6; i++) {
            Object_80039F5C *pPlayer = PlyrGet((unsigned char)team, i);
            int id = pBlock->mUnknown40[team][i];
            if (id != pPlayer->mUnknown2908) {
                fn_801488D4(pPlayer, PlyrFindById(id));
            }
        }
    }
}

Record_80148C4C lbl_802DE99C[1] = {
    {1, {8, 8, 10, 0, 10, 10, 0, 0, 0, 0}, 0},
};

int lbl_802DE9CC[19] = {26, 19, 16, 17, 18, 22, 23, 24, 25, 1, 3, 4, 5, 6, 7, 8, 9, 10, 0};

void Class_802A1F10::vfn_03(float dt)
{
    ClockRuleClearFlags(2048);
    fn_8009D8CC(1);
    fn_8021D7B8(gUISMainInfo, 0x8000003A, 0, 0);
    fn_80148A58()->vfn_12();
    fn_80148A58()->vfn_16(lbl_802DE9CC);
    Class_80297B90::vfn_03(dt);
}

void Class_802A1F10::vfn_08()
{
    PauseOpenScreen(3, 18, -1);
}

void Class_802A1F10::vfn_09()
{
    fn_8021956C(gUISMainInfo, 3, 18, 1);
}

int Class_802A2130::GetWinner()
{
    if (fn_8009D990(1) == 0) {
        return 1;
    }
    return 2;
}

int Class_802A2130::GetGameTime()
{
    return fn_8014EDBC();
}

void Class_802A2130::ResetGame(int team)
{
    ScrmRuleSet::ResetGame(2);
    for (unsigned char i = 0; i <= 5; i++) {
        fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown4 = 0;
        memset(fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown12, 0, 40);
    }
    lbl_803EB2DC = 0;
    lbl_803EB2E0 = 0;
}

void Class_802A2130::ResetPlaySpot()
{
    ScrmRuleSet::ResetPlaySpot();
    fn_80178CD8(0);
}

void Class_802A2130::AwardWin(int team)
{
    int pad = PauseGetValue();
    unsigned short i;
    int value = fn_8014F104(fn_80148A58())->mpUnknown34[0].mUnknown4 + 1;
    for (i = 0; i <= 5; i++) {
        if (fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown8 == pad) {
            fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown4 = value;
            break;
        }
    }
    fn_8014D024(i);
    fn_8009D964(1, 0);
}

void Class_802A20C8::OnEnter(float dt)
{
    Block_8014F104 *pBlock = fn_8014F104(fn_80148A58());
    int keepIds = fn_80148A58()->fn_80149014();
    if (pBlock->mUnknown30) {
        pBlock->mUnknown30 = 0;
        StyleTrackerSetAwardCallback(fn_8014D298);
        int ids[2][7];
        int others[2][7];
        for (unsigned char team = 0; team <= 1; team++) {
            QueryCursor cursor = {0, 0, -1, 0};
            TDbCompilePerformOp(0, "declare \212 cursor for select * from 'YALP' where ('DIGT' = \203) order by 'DIGP'\n",
                                &cursor, team);
            for (unsigned short i = 0; i <= 6; i++) {
                TDbCompilePerformOp(0, "fetch from \212 'DIGP' into \202 and 'DIOP' into \202\n", &cursor,
                                    &ids[team][i], &others[team][i]);
                Object_80039F5C *pPlayer = PlyrGet(team, i);
                if (!keepIds) {
                    pPlayer->mUnknown2908 = ids[team][i];
                }
                pBlock->mUnknown40[team][i] = pPlayer->mUnknown2908;
            }
            if (cursor.mUnknown0) {
                TDbSQLDestroyCursor(&cursor);
            }
        }
        if (!keepIds) {
            for (unsigned short i = 0; i <= 2; i++) {
                Object_80039F5C *pFirst = PlyrGet(1, i);
                Object_80039F5C *pSecond = PlyrGet(0, i + 2);
                unsigned short id = pSecond->mUnknown2908;
                pSecond->mUnknown2908 = pFirst->mUnknown2908;
                pFirst->mUnknown2908 = id;
            }
        } else {
            DbTableCursor table;
            table.OpenTable('YALP', 'DIGP', 0, 0, 'EMAG');
            Object_80039F5C *pCarrier = PlyrFindByRole(1, 0, 0);
            table.FindColumnInt('DIGP', pCarrier->mUnknown2908, 0, 0);
            int other = table.GetColumnInt('DIOP');
            PortDbSetControlledPlayer(fn_800B65A0(1), other);
            Object_80039F5C *pFirst = PlyrGet(1, 0);
            if (pCarrier != pFirst) {
                fn_801488D4(pCarrier, pFirst);
            }
            others[1][0] = other;
            ids[1][0] = pCarrier->mUnknown2908;
        }
        pBlock->mpUnknown34[0].mUnknown0 = PlyrGet(1, 0)->mUnknown2908;
        pBlock->mpUnknown34[0].mUnknown8 = 255;
        for (unsigned short i = 1; i <= 5; i++) {
            pBlock->mpUnknown34[i].mUnknown0 = PlyrGet(0, i - 1)->mUnknown2908;
            pBlock->mpUnknown34[i].mUnknown8 = 255;
        }
        for (int pad = 0; pad <= 3; pad++) {
            int port = GameTextFindPlayerPad(pad);
            int id = PortDbGetControlledPlayer(port);
            if (id >= 0) {
                int found = 0;
                for (unsigned char team = 0; team <= 1 && !found; team++) {
                    for (unsigned short i = 0; i <= 6; i++) {
                        if (others[team][i] == id) {
                            id = ids[team][i];
                            found = 1;
                            break;
                        }
                    }
                }
                for (unsigned short i = 0; i <= 5; i++) {
                    if (pBlock->mpUnknown34[i].mUnknown0 == id) {
                        pBlock->mpUnknown34[i].mUnknown8 = port;
                        break;
                    }
                }
            }
        }
        TutorialReleasePause();
    }
    fn_8014DA20();
    PreGamePhase::OnEnter(dt);
    HudSetScoreTableRows(6);
    HudSetScoreTableHeaders("Player", "Points");
    HudPost3AOff();
    FieldLinesEnable(0);
    fn_800A8738(1);
}

void Class_802A20C8::EnterFirstPhase(float dt)
{
    fn_800AD910(2, dt);
}

void Class_802A20C8::OnExit()
{
    PreGamePhase::OnExit();
    CamGameSetModeAll(1);
    CamGameSelectCamera(0);
    CamMainWarpToDest(CamGameGetCamera(5));
    CamPlaySetYOffset(2.5f);
    fn_8014D67C();
}

void Class_802A20C8::OnUpdate(float dt)
{
    if (MsgBoxIsClosed()) {
        PreGamePhase::OnUpdate(dt);
    }
}

void Class_802A20C8::ShowIntroScreen()
{
    if (fn_800C1E40() == 0) {
        MsgBoxShow("Crush the Carrier", lbl_803EB2D4, "|^Done");
    }
}

void Class_802A2058::AssignControlledPlayers()
{
    for (unsigned char i = 0; i <= 5; i++) {
        Object_80039F5C *pPlayer = PlyrFindById(fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown0);
        if (pPlayer) {
            unsigned char port = fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown8;
            if (port != 255) {
                fn_800B6474(port, pPlayer->mIdBytes[2]);
                fn_800B6714(pPlayer, port);
            } else {
                fn_800B6658(pPlayer);
            }
        }
    }
}

void Class_802A2058::OnEnter(float dt)
{
    PreSnapPhase::OnEnter(dt);
    PlyrStarSetShown(1, 1);
    fn_801487C0(1, 1);
    fn_801487C0(0, 5);
    Point_8017886C pos = {0.0f, 0.0f};
    pos.mY = -fn_80178A44();
    fn_801780A8(pos);
    fn_8017833C(1);
    Object_80039F5C *pPlayer = PlyrGet(1, 0);
    if (pPlayer != BallGetCurrentHolder()) {
        BallGiveToPlayer(BallGetCurrent(), pPlayer);
        BallSetTransferKind(BallGetCurrent(), 0);
    }
    CamGameSetFocusAll(1, BallGetCurrentIndex());
    mUnknown4 = 1;
}

void Class_802A2058::OnUpdate(float dt)
{
    if (mUnknown4) {
        mUnknown4 = 0;
        PlayerMoveResetAll();
        fn_800B14E4();
        DivotRestartRecords();
        AudmonEventClear();
        ClockRuleSnap();
        fn_800C9FC0();
        fn_80148A58()->vfn_15();
    }
    if (InGameOverlayGetState() == 3 || InGameOverlayGetState() == 4) {
        if (InGameOverlayGetState() != 4) {
            InGameOverlayReset();
            PauseUnblock();
        }
        fn_800AD910(3, dt);
    }
}

void Class_802A2020::OnEnter(float dt)
{
    mUnknown4 = 0;
    LivePlayPhase::OnEnter(dt);
    Object_80039F5C *pPlayer = PlyrGet(1, 0);
    PlyrClearPendingMsg(pPlayer, 0);
    if (fn_800F06F4(0, pPlayer->mpState, 1, 0xFFFF) == 0xFFFF) {
        Message_800F01CC message;
        if (fn_8014F104(fn_80148A58())->mUnknown18.mUnknown12) {
            memset(&message, 0, 4);
            message.mId = 51;
            message.mUnknown1[0] = 16;
            fn_800F053C(0, pPlayer->mpState, &message, pPlayer);
            memset(&message, 0, 4);
            message.mId = 1;
            fn_800F01CC(0, pPlayer->mpState, &message, pPlayer);
        } else {
            memset(&message, 0, 4);
            message.mId = 1;
            fn_800F03D8(0, pPlayer->mpState, &message, pPlayer);
        }
    }
    char text[64];
    fn_801C2D88(text, 64, "Catch %s %s", pPlayer->mUnknown2927, pPlayer->mUnknown2927 + 21);
    HudShowCallout(text);
    ParticleTrailStartAfterimage(pPlayer->mpUnknown4);
    for (unsigned char i = 0; i <= 4; i++) {
        Object_80039F5C *pOther = PlyrGet(0, i);
        int position = fn_800F06F4(0, pOther->mpState, 97, 0xFFFF);
        PlyrClearPendingMsg(pOther, 0);
        fn_800F0490(0, pOther->mpState, 51);
        fn_800F0490(0, pOther->mpState, 2);
        fn_800F0490(0, pOther->mpState, 97);
        Message_800F01CC message;
        memset(&message, 0, 4);
        message.mId = 51;
        if (fn_8014F104(fn_80148A58())->mUnknown18.mUnknown12) {
            message.mUnknown1[0] = 48;
        } else {
            message.mUnknown1[0] = 32;
        }
        if (position == 0xFFFF) {
            fn_800F03D8(0, pOther->mpState, &message, pOther);
            memset(&message, 0, 4);
            message.mId = 97;
            fn_800F03D8(0, pOther->mpState, &message, pOther);
        } else {
            fn_800F0278(0, pOther->mpState, &message, pOther, position);
            memset(&message, 0, 4);
            message.mId = 97;
            fn_800F0278(0, pOther->mpState, &message, pOther, position + 1);
        }
    }
    fn_80120618();
}

void Class_802A2020::OnUpdate(float dt)
{
    Vector_80039F5C pos;
    Object_80039F5C *pCarrier = BallGetCurrentHolder();
    if (pCarrier) {
        if (!mUnknown4) {
            mUnknown4 = 1;
            BallGetPosition(BallGetCurrent(), &pos);
            Record_800B15FC *pRecord = fn_800B15FC();
            pRecord->mUnknown14 = 3;
            pRecord->mUnknownC = pos.mX;
            pRecord->mUnknown10 = pos.mY;
            pRecord->mUnknown4 = 1;
            fn_800B1508();
            pRecord = fn_800B15FC();
            pRecord->mUnknownC = pos.mX;
            pRecord->mUnknown10 = pos.mY;
            fn_8009BD2C(pCarrier, &pRecord->mUnknown0);
            pRecord->mUnknown14 = 4;
            fn_800B1508();
        }
    } else if (mUnknown4) {
        mUnknown4 = 0;
        StyleTrackerEndPlay();
    }
    LivePlayPhase::OnUpdate(dt);
    fn_800B14E4();
    if (fn_801787A0() == 0) {
        BallGetPosition(BallGetCurrent(), &pos);
        if (pCarrier) {
            if (fn_80178508(&pCarrier->mMotion, 0, 0) > 2) {
                fn_801783D0(3, 1);
                fn_80178370();
                StyleTrackerEndPlay();
            } else if ((pCarrier->mFlags & 0x800) &&
                       (pCarrier->mpState->mId == 10 || pCarrier->mpState->mId == 16 ||
                        pCarrier->mpState->mId == 25)) {
                PossFumble(pCarrier);
            } else {
                fn_8014D210(pCarrier, 130, 10);
            }
        } else if (fn_80178508(&pos, 0, 0) > 2) {
            fn_801783D0(3, 1);
            fn_80178370();
        }
        if (!fn_8009D990(1)) {
            fn_80177C44(1);
            fn_80178370();
            StyleTrackerEndPlay();
        }
    }
    fn_80148A58()->vfn_15();
    fn_8014D948(this);
    if (BallStateGet(BallGetCurrent(), 0) == 1 && !lbl_803EB2E0) {
        int time = fn_8009D990(1);
        lbl_803EB2E0 = BallGetCurrentHolder();
        lbl_803EB2DC = time;
    } else if (BallStateGet(BallGetCurrent(), 0) != 1 && lbl_803EB2E0) {
        unsigned int time = lbl_803EB2DC - fn_8009D990(1);
        Object_80039F5C *pPlayer = lbl_803EB2E0;
        fn_8014F4D8(fn_80148A58(), pPlayer, 8, time);
        fn_8014F4D8(fn_80148A58(), pPlayer, 7, 1);
        if (time > fn_8014F104(fn_80148A58())->mUnknown38) {
            fn_8014F104(fn_80148A58())->mUnknown38 = time;
            fn_8014F104(fn_80148A58())->mpUnknown3C = pPlayer;
        }
        lbl_803EB2DC = 0;
        lbl_803EB2E0 = 0;
    }
}

void Class_802A1F90::OnEnter(float dt)
{
    Object_80039F5C *pPlayer = PlyrGet(1, 0);
    mpUnknown4 = BallGetCurrentHolder();
    mUnknown12 = 0;
    fn_8009D8CC(1);
    if (fn_8009D990(1)) {
        if (fn_801783AC(3)) {
            unsigned int best = 0xFFFFFFFF;
            mUnknown12 = 1;
            for (unsigned short i = 0; i <= 5; i++) {
                Object_80039F5C *pOther = PlyrFindById(fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown0);
                unsigned int value = fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown4;
                if (pOther != pPlayer && (value < best || (value == best && SyncRandGetRange(0, 100) > 50))) {
                    mpUnknown4 = pOther;
                    best = value;
                }
            }
        } else if (!mpUnknown4 || pPlayer == mpUnknown4) {
            mUnknown12 = 1;
            mpUnknown4 = mpUnknown8;
            if (!mpUnknown8) {
                Vector_80039F5C pos;
                BallGetPosition(BallGetCurrent(), &pos);
                float best = 3.4028235e38f;
                for (unsigned short i = 0; i <= 4; i++) {
                    Object_80039F5C *pOther = PlyrGet(0, i);
                    float distance = Vec3Distance(&pOther->mMotion.mPos, &pos);
                    if (distance < best) {
                        mpUnknown4 = pOther;
                        best = distance;
                    }
                }
            }
        } else if (fn_801783AC(3)) {
            mUnknown12 = 1;
        }
        if (!fn_8009D990(1)) {
            mUnknown12 = 0;
        }
        if (mUnknown12) {
            PauseBlock();
            InGameOverlayOpen(2);
        }
    }
    PostPlayPhase::OnEnter(dt);
}

void Class_802A1F90::OnExit()
{
    PostPlayPhase::OnExit();
    if (fn_8009D990(1)) {
        fn_801488D4(PlyrGet(1, 0), mpUnknown4);
        if (mUnknown12) {
            PlyrMgrClearStates();
            fn_8014D67C();
            InGameOverlayShow();
        }
    } else {
        PlyrMgrClearStates();
        for (unsigned int team = 0; team <= 1; team++) {
            for (unsigned int i = 0; i <= 6; i++) {
                Object_80039F5C *pPlayer = PlyrGet((unsigned char)team, i);
                fn_800EFE60(0, pPlayer->mpState, pPlayer);
            }
        }
    }
    mpUnknown8 = 0;
}

int Class_802A1F90::IsFinished(int busy)
{
    if (!mUnknown12 || InGameOverlayGetState() == 1) {
        return 1;
    }
    return 0;
}

void Class_802A1F90::Finish(float dt)
{
    if (fn_8009D990(1)) {
        fn_800AD910(2, dt);
    } else {
        ClockRuleEndPeriod();
    }
}

extern "C" {

int fn_8014EDBC(void)
{
    return lbl_803EB2D8;
}

} /* extern "C" */

 /* extern "C" */

Class_802A2B68::Class_802A2B68()
{
    mState.mCount = 1;
    mState.mpRecords = lbl_802DE99C;
    mpUnknown1C = 0;
}

void Class_802A2B68::vfn_01()
{
    Block_8014F104 *pBlock = new (0) Block_8014F104;
    mpUnknown1C = pBlock;
    lbl_803EB2E0 = 0;
    pBlock->mpUnknown34 = new (0) Record_8014F104[6];
    fn_80178F20(&mpUnknown1C->mUnknown0);
    fn_800BC51C(&mpUnknown1C->mUnknown4);
    fn_800BFAB4(&mpUnknown1C->mUnknown8);
    fn_800A039C(&mpUnknown1C->mUnknown10);
    fn_800B9598(&mpUnknown1C->mUnknown18);
    fn_800AACB8(&mpUnknown1C->mUnknown28);
    mpUnknown1C->mUnknown2C = GameOptionsGet(14);
    if (mpUnknown1C->mUnknown2C != 1) {
        GameOptionsSet(14, 1);
    }
}

void Class_802A2B68::vfn_02()
{
    fn_800A8738(0);
    if (mpUnknown1C->mUnknown2C != 1) {
        GameOptionsSet(14, mpUnknown1C->mUnknown2C);
    }
    if (StoryEventsGetCurrentEvent()) {
        StoryEventsSetRewardPenalty(fn_8014FF34(this));
    }
    if (fn_80149014()) {
        fn_8014DA90();
    }
    StyleTrackerSetAwardCallback(0);
    fn_80178F20(0);
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_800AACB8(0);
    delete[] mpUnknown1C->mpUnknown34;
    delete mpUnknown1C;
    mpUnknown1C = 0;
}

extern "C" {

Block_8014F104 *fn_8014F104(Class_80148A58 *p)
{
    return static_cast<Class_802A2B68 *>(p)->mpUnknown1C;
}

} /* extern "C" */

int Class_802A2B68::vfn_05(int team)
{
    if (team == 0) {
        return 5;
    }
    return 1;
}

void Class_802A2B68::vfn_10(int value, int *pList, int *pIds)
{
    for (unsigned char i = 0; i <= 6 && pList[i] != 32767; i++) {
        pIds[i] = pIds[i + 7] = pList[i];
    }
}

void Class_802A2B68::vfn_11(int value, int *pList, int *pIds, unsigned int a, int b)
{
    vfn_10(value, pList, pIds);
}

void Class_802A2B68::vfn_12()
{
    for (unsigned short i = 0; i <= 5; i++) {
        if (mpUnknown1C->mpUnknown34[i].mUnknown8 == 255) {
            continue;
        }
        char name[32];
        if (!UserProfileGetPadName(GameTextGetPadPlayer(mpUnknown1C->mpUnknown34[i].mUnknown8), name, 31)) {
            continue;
        }
        QueryResult result;
        QueryCursor cursor;
        unsigned int score = 0;
        int key = 0;
        cursor.mUnknown0 = 0;
        cursor.mUnknown4 = 0;
        cursor.mUnknown8 = -1;
        cursor.mUnknown12 = 0;
        TDbCompilePerformOp(&result, "use 'EVAS' declare \212 fastcursor for select 'SRCH' into \205 and 'KPSH' into \202 from 'CCSH' where 'TRCH' = \203 order by 'SRCH' asc and 'KPSH' asc\n", &cursor, &score, &key,
                    (unsigned char)((unsigned int)lbl_803EB2D8 / 60));
        cursor.mUnknown4 = 0;
        TDbCompilePerformOp(0, "fetch from \212\n", &cursor);
        if (cursor.mUnknown0) {
            TDbSQLDestroyCursor(&cursor);
        }
        if (score < mpUnknown1C->mpUnknown34[i].mUnknown4) {
            int id = 0;
            int status = TDbCompilePerformOp(0, "use 'EVAS' select 'KPSH' into \202 from 'RCSH' where 'KUSH' = \210\n", &id, name);
            if (status == 23) {
                id = UserProfileGetFreeKey(0x52435348, 0x4B505348, 0, 255);
                if (id == -1) {
                    continue;
                }
                TDbCompilePerformOp(0, "use 'EVAS' insert into 'RCSH' set 'KPSH' = \202 and 'KUSH' = \210 and 'WGSH' = 0 and 'LGSH' = 0 and 'PTSH' = 0 and 'TPSH' = 0 and 'TRSH' = 0 and 'TDSH' = 0 and 'TSSH' = 0 and 'CISH' = 0 and 'RFSH' = 0 and 'GTSH' = 0 and '2TSH' = 0 and 'TTSH' = 0 and 'CNWH' = 0\n", id, name);
            }
            if (id != -1) {
                TDbCompilePerformOp(&result, "use 'EVAS' update 'CCSH' set 'SRCH' = \205 and 'UCCH' = \202 where 'KPSH' = \202\n",
                            mpUnknown1C->mpUnknown34[i].mUnknown4, id, key);
            }
        }
    }
}

const char *lbl_803EB2E4 = "Jump Ball Battle\n\nCatch as many passes as possible. The NFL STREET ball is worth double points.";
const char *lbl_803EB2E8 = "5 Points|10 Points|15 Points|20 Points|25 Points|30 Points|35 Points|40 Points|45 Points|50 Points|60 Points|70 Points|80 Points|90 Points|100 Points|^60 Seconds|90 Seconds|120 Seconds|150 Seconds|180 Seconds";
extern const int lbl_802A11F4[20] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100, 60, 90, 120, 150, 180};
extern const char *const lbl_802A1280[15] = {"5", "10", "15", "20", "25", "30", "35", "40", "45", "50", "60", "70", "80", "90", "100"};
int lbl_803EB2EC = 0;

int Class_802A2B68::vfn_13()
{
    if (GameModeTypeGet() == 7) {
        return fn_8014FF34(this) <= 4;
    }
    return fn_8014F104(fn_80148A58())->mpUnknown34[0].mUnknown8 != 255;
}

extern "C" {

void fn_8014F3DC(int value)
{
    lbl_803EB2D8 = value;
}

void fn_8014F3E4(Class_80148A58 *p, int index, Info_8014F3E4 *pInfo)
{
    Record_8014F104 *pRecord = &static_cast<Class_802A2B68 *>(p)->mpUnknown1C->mpUnknown34[index];
    pInfo->mUnknown4 = pRecord->mUnknown4;
    pInfo->mUnknown8 = pRecord->mUnknown12[8];
    pInfo->mUnknown12 = pRecord->mUnknown12[0];
    pInfo->mpUnknown0 = PlyrFindById(pRecord->mUnknown0);
    pInfo->mUnknown16 = pRecord->mUnknown8;
}

Object_80039F5C *fn_8014F448(Class_80148A58 *p)
{
    return PlyrFindById(static_cast<Class_802A2B68 *>(p)->mpUnknown1C->mpUnknown34[0].mUnknown0);
}

unsigned int fn_8014F474(Class_80148A58 *p, Object_80039F5C *pPlayer)
{
    unsigned int i;
    for (i = 0; i <= 5; i++) {
        if (fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown0 == pPlayer->mUnknown2908) {
            break;
        }
    }
    return i;
}

void fn_8014F4D8(Class_80148A58 *p, Object_80039F5C *pPlayer, int kind, int value)
{
    unsigned int index = fn_8014F474(fn_80148A58(), pPlayer);
    if (kind == 8 && value > fn_8014F104(fn_80148A58())->mpUnknown34[index].mUnknown12[9]) {
        fn_8014F104(fn_80148A58())->mpUnknown34[index].mUnknown12[9] = value;
    }
    fn_8014F104(fn_80148A58())->mpUnknown34[index].mUnknown12[kind] += value;
}

} /* extern "C" */

int Class_802A2B68::vfn_26(int team, int index, Object_80039F5C *pPlayer, int kind)
{
    int result = 0;
    unsigned int i = fn_8014F474(this, pPlayer);
    Record_8014F104 *pRecord = &mpUnknown1C->mpUnknown34[i];
    switch (kind) {
    case 26:
        if (vfn_31(26, team, index, pPlayer, 1, 0)) {
            unsigned int j;
            result = 1;
            for (j = 0; j <= 5; j++) {
                if (i != j && pRecord->mUnknown4 < mpUnknown1C->mpUnknown34[j].mUnknown4 * 2) {
                    result = 0;
                    break;
                }
            }
            if (pRecord->mUnknown8 != 255) {
                result = 0;
            }
        }
        break;
    case 19:
        if (vfn_31(26, team, index, pPlayer, 1, 0)) {
            unsigned int j;
            result = 1;
            for (j = 0; j <= 5; j++) {
                if (i != j && pRecord->mUnknown4 < mpUnknown1C->mpUnknown34[j].mUnknown4 * 2) {
                    result = 0;
                    break;
                }
            }
        }
        break;
    case 16: {
        unsigned int max = 0;
        unsigned int j;
        for (j = 0; j < 4; j++) {
            if (mpUnknown1C->mpUnknown34[j].mUnknown4 >= max) {
                max = mpUnknown1C->mpUnknown34[j].mUnknown4;
            }
        }
        if (pRecord->mUnknown4 >= max - 2 && pRecord->mUnknown4 < max) {
            result = 1;
        }
        break;
    }
    case 17:
        {
            int ok = vfn_31(17, team, index, pPlayer, 1, 0) && pRecord->mUnknown4 >= RecordsGetValue(22);
            result = ok;
        }
        break;
    case 18:
        result = vfn_31(18, team, index, pPlayer, 1, 0);
        break;
    case 22:
        result = vfn_31(22, team, index, pPlayer, 1, 0);
        break;
    case 23:
        result = vfn_31(23, team, index, pPlayer, 1, 0);
        break;
    case 24:
        result = vfn_31(24, team, index, pPlayer, 100, 1);
        break;
    case 25:
        result = vfn_31(25, team, index, pPlayer, 1, 0);
        break;
    case 1:
        result = vfn_31(1, team, index, pPlayer, 1, 0);
        break;
    case 3:
        result = vfn_31(3, team, index, pPlayer, 1, 0);
        break;
    case 4:
        result = vfn_31(4, team, index, pPlayer, 3, 0);
        break;
    case 5:
        result = vfn_31(5, team, index, pPlayer, 3, 0);
        break;
    case 6:
        result = vfn_31(6, team, index, pPlayer, 1, 0);
        break;
    case 7:
        result = vfn_31(7, team, index, pPlayer, 3, 0);
        break;
    case 8:
        {
            int ok = vfn_31(6, team, index, pPlayer, 100, 1) && vfn_31(1, team, index, pPlayer, 100, 1);
            result = ok;
        }
        break;
    case 9:
        {
            int ok = vfn_31(9, team, index, pPlayer, 100, 1) && !vfn_28(8);
            result = ok;
        }
        break;
    case 10:
    default:
        result = Class_80148A58::vfn_26(team, index, pPlayer, kind);
        break;
    }
    return result;
}

int Class_802A2B68::vfn_30(int kind, int team, int index, Object_80039F5C *pPlayer)
{
    int result = 0;
    unsigned int i = fn_8014F474(this, pPlayer);
    switch (kind) {
    case 16:
    case 17:
    case 18:
    case 19:
    case 26:
        result = mpUnknown1C->mpUnknown34[i].mUnknown4;
        break;
    case 22:
        result = mpUnknown1C->mpUnknown34[i].mUnknown12[1] - mpUnknown1C->mpUnknown34[i].mUnknown12[0];
        break;
    case 23:
        result = mpUnknown1C->mpUnknown34[i].mUnknown12[9];
        break;
    case 24:
        if (mpUnknown1C->mpUnknown34[i].mUnknown12[7] != 0) {
            result = mpUnknown1C->mpUnknown34[i].mUnknown12[8] / mpUnknown1C->mpUnknown34[i].mUnknown12[7];
        } else {
            result = 10000;
        }
        break;
    case 25:
        result = mpUnknown1C->mpUnknown34[i].mUnknown12[8];
        break;
    case 1:
    case 9:
        result = mpUnknown1C->mpUnknown34[i].mUnknown12[0];
        break;
    case 3:
        result = mpUnknown1C->mpUnknown34[i].mUnknown12[2] + mpUnknown1C->mpUnknown34[i].mUnknown12[3] * 10;
        break;
    case 4:
        result = mpUnknown1C->mpUnknown34[i].mUnknown12[4];
        break;
    case 5:
        result = mpUnknown1C->mpUnknown34[i].mUnknown12[5];
        break;
    case 6:
        result = mpUnknown1C->mpUnknown34[i].mUnknown12[7];
        break;
    case 7:
        result = mpUnknown1C->mpUnknown34[i].mUnknown12[6];
        break;
    case 8:
        break;
    case 10:
    default:
        result = Class_80148A58::vfn_30(kind, team, index, pPlayer);
        break;
    }
    return result;
}

int Class_802A2B68::vfn_31(int kind, int team, int index, Object_80039F5C *pPlayer, int threshold, int mode)
{
    int answer = 0;
    int original = vfn_30(kind, team, index, pPlayer);
    int result = 0;
    bool found = false;
    for (unsigned char t = 0; t <= 1; t++) {
        for (unsigned char i = 0; i < 6; i++) {
            Object_80039F5C *pCandidate = PlyrGet(t, i);
            if (pCandidate->mUnknown9[2] != 0) {
                if (!found) {
                    result = vfn_30(kind, t, i, pCandidate);
                    found = true;
                } else {
                    int value = vfn_30(kind, t, i, pCandidate);
                    if ((mode == 0 && value > result) || (mode == 1 && value < result)) {
                        result = value;
                    }
                }
            }
        }
    }
    if ((mode == 0 && result > threshold) || (mode == 1 && result < threshold)) {
        answer = original == result;
    }
    return answer;
}

int Class_802A2B68::vfn_21()
{
    return 0;
}

extern "C" {

int fn_8014FF34(Class_802A2B68 *p)
{
    int result = 0;
    for (unsigned int i = 0; i <= 5; i++) {
        if (fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown8 != 255) {
            result = fn_8014F474(p, PlyrFindById(fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown0));
            break;
        }
    }
    return result;
}

void fn_8014FFC4(Point_8017886C *p)
{
    float width = fn_800A32B4();
    float originY = fn_80177FE0().mY;
    if (!(width <= 6.0f)) {
        width = 6.0f;
    }
    p->mY = SyncRandGetFloatRange(0, originY + 20.0f, originY + 40.0f);
    p->mX = SyncRandGetFloatRange(0, -width, width);
}

void fn_8015005C(Object_8015005C *p, int index)
{
    for (; index != 0; index--) {
        Entry_8015005C *pEntries = p->mpUnknown36->mEntries;
        unsigned int score = pEntries[index].mUnknown10 + pEntries[index].mUnknown8 * 2;
        unsigned int prevScore = pEntries[index - 1].mUnknown10 + pEntries[index - 1].mUnknown8 * 2;
        if (score > prevScore) {
            Entry_8015005C temp = pEntries[index];
            pEntries[index] = pEntries[index - 1];
            p->mpUnknown36->mEntries[index - 1] = temp;
        } else {
            break;
        }
    }
}

void fn_8015013C(Object_8015005C *p, int id, int flag)
{
    unsigned short i;
    for (i = 0; i < p->mpUnknown36->mCount; i++) {
        if (p->mpUnknown36->mEntries[i].mUnknown0 == id) {
            if (flag) {
                p->mpUnknown36->mEntries[i].mUnknown8++;
            } else {
                p->mpUnknown36->mEntries[i].mUnknown10++;
            }
            break;
        }
    }
    fn_8015005C(p, i);
}

} /* extern "C" */

int Class_802A1E38::GetWinner()
{
    return fn_801530FC()->mUnknown125;
}

void Class_802A1E38::AwardWin(int value)
{
    fn_801530FC()->mUnknown125 = value;
    int count = lbl_8031BDD4.mUnknown32;
    if (count != 0) {
        fn_801530FC()->mEntries[0].mUnknown8 += count;
    } else {
        fn_801530FC()->mEntries[0].mUnknown8++;
        fn_8009D964(1, 0);
    }
    if (lbl_8031BDD4.mUnknown40 == 1) {
        unsigned int n = fn_801530FC()->mCount;
        unsigned int i;
        for (i = 1; i < n; i++) {
            fn_80151CCC(&lbl_8031BDD4, i, 0);
        }
    }
    fn_801502B4(this);
}

 /* extern "C" */

extern "C" void fn_801502B4(void *p)
{
    for (unsigned int i = 0; i <= 3; i++) {
        Entry_8015005C *pEntry = &fn_801530FC()->mEntries[i];
        unsigned int score = pEntry->mUnknown10 + pEntry->mUnknown8 * 2;
        if (score > pEntry->mUnknown4) {
            pEntry->mUnknown4 = score;
        }
        pEntry->mUnknown14 += pEntry->mUnknown8;
        pEntry->mUnknown16 += pEntry->mUnknown10;
        pEntry->mUnknown10 = 0;
        pEntry->mUnknown8 = 0;
    }
    fn_801530FC()->mUnknown125 = 1;
}

void Class_802A1E38::ResetGame(int team)
{
    ScrmRuleSet::ResetGame(2);
    fn_801526EC(&lbl_8031BDD4);
}

void Class_802A1E38::EndPlay()
{
    if (fn_801530FC()->mUnknown117) {
        ScrmRuleSet::EndPlay();
    }
}

void Class_802A1DC8::OnEnter(float dt)
{
    fn_800A8738(1);
    fn_8017833C(0);
    PreGamePhase::OnEnter(dt);
    HudSetScoreTableRows(4);
    HudSetScoreTableHeaders("Player", "Points");
    HudPost3AOff();
    StyleTrackerSetEnabled(0);
    if (mUnknown4) {
        Table_8015005C *pTable = fn_801530FC();
        int ids[2][7];
        int others[2][7];
        for (unsigned char team = 0; team <= 1; team++) {
            QueryCursor cursor = {0, 0, -1, 0};
            TDbCompilePerformOp(0, "declare \212 cursor for select * from 'YALP' where ('DIGT' = \203)\n", &cursor, team);
            for (unsigned short i = 0; i <= 6; i++) {
                TDbCompilePerformOp(0, "fetch from \212 'DIGP' into \202 and 'DIOP' into \202\n", &cursor,
                                    &ids[team][i], &others[team][i]);
                PlyrGet(team, i)->mUnknown2908 = ids[team][i];
            }
            if (cursor.mUnknown0) {
                TDbSQLDestroyCursor(&cursor);
            }
        }
        for (unsigned short i = 0; i <= 1; i++) {
            Object_80039F5C *pFirst = PlyrGet(0, i);
            Object_80039F5C *pSecond = PlyrGet(1, i + 2);
            unsigned short id = pSecond->mUnknown2908;
            pSecond->mUnknown2908 = pFirst->mUnknown2908;
            pFirst->mUnknown2908 = id;
        }
        for (unsigned short i = 0; i <= 3; i++) {
            pTable->mEntries[i].mUnknown0 = PlyrGet(1, i)->mUnknown2908;
            pTable->mEntries[i].mUnknown4 = 0;
            pTable->mEntries[i].mUnknown8 = 0;
            pTable->mEntries[i].mUnknown10 = 0;
            pTable->mEntries[i].mUnknown14 = 0;
            pTable->mEntries[i].mUnknown16 = 0;
            pTable->mEntries[i].mUnknown12 = 255;
            pTable->mEntries[i].mUnknown13 = 0;
        }
        for (int pad = 0; pad <= 3; pad++) {
            int port = GameTextFindPlayerPad(pad);
            int id = PortDbGetControlledPlayer(port);
            if (id >= 0) {
                int found = 0;
                for (unsigned char team = 0; team <= 1 && !found; team++) {
                    for (unsigned short i = 0; i <= 6; i++) {
                        if (others[team][i] == id) {
                            id = ids[team][i];
                            found = 1;
                            break;
                        }
                    }
                }
                for (unsigned short i = 0; i <= 3; i++) {
                    if (pTable->mEntries[i].mUnknown0 == id) {
                        pTable->mEntries[i].mUnknown12 = port;
                        break;
                    }
                }
            }
        }
        TutorialReleasePause();
        mUnknown4 = 0;
    }
    fn_80178E88(fn_80178A2C() + -15.0f);
    fn_80178CD8(0);
    for (unsigned char team = 0; team <= 1; team++) {
        for (unsigned short i = 0; i <= 6; i++) {
            PlyrGet(team, i)->mpUnknown4->mUnknown20 &= ~1U;
        }
    }
    FieldLinesEnable(0);
}

void Class_802A1DC8::OnUpdate(float value)
{
    if (MsgBoxIsClosed()) {
        EnterFirstPhase(value);
    }
}

void Class_802A1DC8::OnExit()
{
    PreGamePhase::OnExit();
    for (unsigned char team = 0; team <= 1; team++) {
        for (unsigned short i = 0; i <= 6; i++) {
            Object_80039F5C *pPlayer = PlyrGet(team, i);
            fn_80149040(pPlayer);
            fn_800EFE60(0, pPlayer->mpState, pPlayer);
        }
    }
}

 /* extern "C" */
void Class_802A1DC8::ShowIntroScreen()
{
    if (fn_800C1E40() == 0) {
        MsgBoxShow("Jump Ball Battle", lbl_803EB2E4, "|^Done");
    }
}

void Class_802A1DC8::HideIntroScreen()
{
}

void Class_802A1DC8::EnterFirstPhase(float value)
{
    fn_800AD910(2, value);
}

void Class_802A1D58::OnEnter(float dt)
{
    unsigned int i;
    unsigned int count;
    Point_8017886C point;

    PlyrMgrResetAll();
    count = fn_801530FC()->mCount;
    fn_801486A8();
    PreSnapPhase::OnEnter(dt);
    fn_801530FC()->mUnknown117 = 0;
    fn_801527E0(&lbl_8031BDD4, 1);
    point = fn_80177FE0();
    for (i = 0; i < count; i++) {
        Object_80039F5C *pPlayer = PlyrFindById(fn_801530FC()->mEntries[i].mUnknown0);
        pPlayer->mMotion.mPos.mX = -(float)count * 1.125f + (float)i * 2.25f;
        pPlayer->mMotion.mPos.mY = point.mY + 30.0f;
    }
}

void Class_802A1D58::OnUpdate(float dt)
{
    fn_800AD910(3, dt);
    if (lbl_8031BDD4.mUnknown36 != 0) {
        fn_80148A58()->vfn_15();
    }
}

void Class_802A1D58::AssignControlledPlayers()
{
    unsigned char i;

    for (i = 0; i <= 3; i++) {
        Object_80039F5C *pPlayer = PlyrFindById(fn_801530FC()->mEntries[i].mUnknown0);
        if (pPlayer) {
            unsigned char value = fn_801530FC()->mEntries[i].mUnknown12;
            if (value != 255 && fn_801530FC()->mEntries[i].mUnknown13 == 0) {
                fn_800B6474(value, pPlayer->mIdBytes[2]);
                fn_800B6714(pPlayer, value);
            } else {
                fn_800B6658(pPlayer);
            }
        }
    }
}

void Class_802A1D58::SetupCamera()
{
}

void Class_802A1D20::OnEnter(float dt)
{
    LivePlayPhase::OnEnter(dt);
    PlyrStarSetShown(1, 1);
    mUnknown8 = 0;
    mUnknown9 = 0;
    mUnknown4 = 0;
    fn_80151010(this);
}

void Class_802A1D20::OnUpdate(float dt)
{
    unsigned char i;
    for (i = 0; i < BallsGetCount(); i++) {
        if (BallStateGet(BallGet(i), 0) == 4) {
            if (!mUnknown8) {
                mUnknown8 = 1;
                ClockRuleSetFlags(0x800);
                ClockRuleSnap();
            }
            fn_80153168(&lbl_8031BDD4, i, 1);
        }
    }
    if (lbl_8031BDD4.mUnknown36) {
        int time = fn_8009D990(1);
        if (time != lbl_803EB2EC && (unsigned int)time <= 5) {
            lbl_803EB2EC = time;
            AudmonEventPost(20, 0);
        }
    }
    LivePlayPhase::OnUpdate(dt);
    if (lbl_8031BDD4.mUnknown36) {
        fn_80148A58()->vfn_15();
    }
    unsigned int count = BallsGetCount();
    int noneFree = 1;
    fn_800B14E4();
    for (unsigned int k = 0; k <= 3; k++) {
        Object_80039F5C *pPlayer = PlyrGet(1, k);
        Ball_t *pHeld = BallFindHeldBy(pPlayer);
        if (pHeld) {
            i = BallGetIndex(pHeld);
            if (!mUnknown5[i]) {
                mUnknown5[i] = 1;
                fn_8015013C(lbl_8031BDD4.mpUnknown1C, pPlayer->mUnknown2908, BallGetCurrent() == pHeld);
            }
        }
    }
    float minX = 3.4028235e38f;
    float maxX = 1.17549435e-38f;
    Vector_80039F5C pos = {0.0f, 0.0f, 0.0f};
    Vector_80039F5C *pTarget = &fn_801530FC()->mUnknown80;
    unsigned char b = 0;
    pTarget->mY = minX;
    for (; b < count; b++) {
        Ball_t *pBall = BallGet(b);
        if (BallIsVisible(pBall)) {
            int prev = BallStateGetPrev(pBall, 0);
            int state = BallStateGet(pBall, 0);
            if (state != 5 && !(prev == 4 && state == 1)) {
                BallGetPosition(pBall, &pos);
                noneFree = 0;
                if (pos.mX < minX) {
                    minX = pos.mX;
                }
                if (pos.mX > maxX) {
                    maxX = pos.mX;
                }
            }
            if (pos.mY < pTarget->mY) {
                *pTarget = pos;
            }
        }
    }
    if (!noneFree) {
        pTarget->mX = (maxX - minX) * 0.5f + minX;
    } else {
        pTarget->mX = 0.0f;
        pTarget->mY = -15.0f;
        pTarget->mZ = 2.0f;
    }
    RefreshFourPlayerScoreRows(this);
    Class_802A2918 *pRules = &lbl_8031BDD4;
    fn_80151BCC(pRules);
    if (noneFree) {
        fn_80151D9C(pRules);
        if (fn_80178AE0() == 2) {
            fn_80151010(this);
        } else {
            fn_801530FC()->mUnknown117 = 1;
            fn_80178370();
        }
    }
}

void Class_802A1D20::OnExit()
{
    LivePlayPhase::OnExit();
}

extern "C" {

// Reset the balls and keep the three random field positions at least four units apart.
void ResetBallsAndFieldPositions(Class_802A1D20 *p)
{
    unsigned int count = BallsGetCount();
    Table_8015005C *pTable = fn_801530FC();
    Vector_80039F5C position;
    int angles[3];
    Point_8017886C origin;
    origin.mX = 0.0f;
    origin.mY = -15.0f;
    fn_801780A8(origin);
    Ball_t *pCurrent = BallGetCurrent();
    unsigned char i;
    for (i = 0; i < count; i++) {
        Ball_t *pBall = BallGet(i);
        if (BallGetHolder(pBall)) {
            BallReleaseStill(pBall, 5, 0);
        }
        if (pBall == pCurrent) {
            BallReleaseStill(pBall, 6, 0);
        }
        position.mX = origin.mX + i * 0.33f;
        position.mY = origin.mY;
        position.mZ = 0.3f;
        BallSetPosition(pBall, &position);
        angles[0] = 0;
        angles[1] = 0xFFC00000;
        angles[2] = 0xFFC00000;
        BallRestAtAngles(pBall, angles);
        BallSetSpinMode(pBall, 0);
        BallPrimeKickUp(pBall);
    }
    for (i = 0; i <= 2; i++) {
        fn_8014FFC4(&pTable->mUnknown92[i]);
        unsigned int j = 0;
        while (j < i) {
            if (Vec2Distance(&pTable->mUnknown92[i], &pTable->mUnknown92[j]) < 4.0f) {
                fn_8014FFC4(&pTable->mUnknown92[i]);
                j = 0;
            } else {
                j++;
            }
        }
    }
}

void fn_80151010(Class_802A1D20 *p)
{
    fn_801527E0(&lbl_8031BDD4, 1);
    ResetBallsAndFieldPositions(p);
    Point_8017886C origin = fn_80177FE0();
    unsigned int count = BallsGetCount();
    memset(p->mUnknown5, 0, 3);
    unsigned char first = SyncRandGetRange(0, 3);
    unsigned int players = fn_801530FC()->mUnknown119;
    unsigned int i;
    unsigned char ball;
    Message_800F01CC message;
    for (i = 0; i < players; i++) {
        Object_80039F5C *pPlayer = PlyrGet(0, i);
        if (i == first) {
            ball = 0;
        } else if (i == 0) {
            ball = first;
        } else {
            ball = i;
        }
        Ball_t *pBall = BallGet(ball);
        BallSetVisible(pBall, 1);
        BallGiveToPlayer(pBall, pPlayer);
        fn_80153168(&lbl_8031BDD4, ball, 0);
        pPlayer->mMotion.mPos.mX = -((float)players * 0.5f * 2.0f) + (float)i * 2.0f;
        pPlayer->mMotion.mPos.mY = origin.mY;
        if (pPlayer->mUnknown2913 == 0) {
            pPlayer->mMotion.mFacing = 0;
        } else {
            pPlayer->mMotion.mFacing = 0x800000;
            pPlayer->mMotion.mPos.mX = pPlayer->mMotion.mPos.mX + 0.5f;
        }
        fn_800EFE60(0, pPlayer->mpState, pPlayer);
        memset(&message, 0, 4);
        message.mId = 51;
        float delay = (signed char)SyncRandGetRange(0, 15) * (1.0f / 60.0f);
        if (p->mUnknown8 == 1) {
            if (p->mUnknown9 == 1) {
                message.mUnknown1[0] = (int)((delay + 1.5f) * 32.0f);
            } else {
                message.mUnknown1[0] = (int)((delay + 0.4f) * 32.0f);
            }
        } else {
            message.mUnknown1[0] = (int)((delay + 2.0f) * 32.0f);
        }
        fn_800F053C(0, pPlayer->mpState, &message, pPlayer);
        fn_801024FC(pPlayer, 8, 15, 5, 0);
        memset(&message, 0, 4);
        message.mId = 62;
        message.mUnknown1[0] = 0;
        message.mUnknown1[1] = 0;
        fn_800F03D8(0, pPlayer->mpState, &message, pPlayer);
        if (pPlayer->mUnknown2913 == 0) {
            pPlayer->mUnknown512.mUnknown0 = 1.0f;
            pPlayer->mUnknown512.mUnknown14 = 3;
            pPlayer->mUnknown512.mUnknown8 = 0;
            pPlayer->mUnknown512.mUnknown4 = 0xC38E39;
        } else {
            pPlayer->mUnknown512.mUnknown0 = 1.0f;
            pPlayer->mUnknown512.mUnknown14 = 3;
            pPlayer->mUnknown512.mUnknown8 = 0x800000;
            pPlayer->mUnknown512.mUnknown4 = 0xBC71C7;
        }
    }
    p->mUnknown4 += players;
    if (p->mUnknown4 > 2) {
        p->mUnknown4 = 0;
        SndgEventSetCrowdCycle(1);
    }
    Vector_80039F5C offField = {2048.0f, 2048.0f, 0.0f};
    for (; i < count; i++) {
        if (i == first) {
            ball = 0;
        } else {
            ball = i;
        }
        Ball_t *pBall = BallGet(ball);
        BallSetVisible(pBall, 0);
        BallSetPosition(pBall, &offField);
        fn_80153168(&lbl_8031BDD4, ball, 1);
    }
    unsigned int total = fn_801530FC()->mCount;
    for (i = 0; i < total; i++) {
        Object_80039F5C *pPlayer = PlyrFindById(fn_801530FC()->mEntries[i].mUnknown0);
        if (fn_801530FC()->mEntries[i].mUnknown12 == 0xFF &&
            fn_800F06F4(0, pPlayer->mpState, 95, 0xFFFF) == 0xFFFF) {
            memset(&message, 0, 4);
            message.mId = 95;
            fn_800F03D8(0, pPlayer->mpState, &message, pPlayer);
        }
    }
    CamGameSetModeAll(12);
    CamGameSelectCamera(0);
    CamGameSetFocusAll(7, BallGetCurrentIndex());
    p->mUnknown9 = 0;
}

// Clear eliminated players' rows; show each remaining player's current round total.
void RefreshFourPlayerScoreRows(Class_802A1D20 *p)
{
    for (unsigned char i = 0; i <= 3; i++) {
        if (fn_801530FC()->mEntries[i].mUnknown13 == 0) {
            char score[16];
            char name[20];
            strncpy(name, PlyrFindById(fn_801530FC()->mEntries[i].mUnknown0)->mUnknown2927 + 21, sizeof(name));
            Entry_8015005C *pEntries = fn_801530FC()->mEntries;
            fn_801C2D88(score, sizeof(score), "%d",
                        pEntries[i].mUnknown10 + pEntries[i].mUnknown8 * 2);
            HudSetScoreTableRow(i + 1, name, score, "", fn_801530FC()->mEntries[i].mUnknown12);
        } else {
            HudSetScoreTableRow(i + 1, "", "", "", 255);
        }
    }
}

} /* extern "C" */

int Class_802A1C98::IsFinished(int busy)
{
    ForceFinish();
    return 1;
}

void Class_802A1C98::OnExit()
{
    unsigned char team;

    PostPlayPhase::OnExit();
    if (fn_80177C38() == 1 || fn_80177C38() == 3) {
        fn_80177C50(1);
        fn_80177C44(0);
    }
    fn_8011DF90();
    team = fn_80178308();
    PlayBookRestoreSelection(team);
}

void Class_802A1C98::Finish(float dt)
{
    if (InGameOverlayGetState() != 4) {
        InGameOverlayReset();
    }
    if (fn_80178AE0() == 2) {
        fn_800AD910(2, dt);
    } else {
        ClockRuleEndPeriod();
    }
}

void Class_802A1C98::SetupCamera()
{
}

int Class_802A1C98::GetBusy(float dt)
{
    fn_8009B924();
    return 0;
}

Record_80148C4C lbl_802DEA18[2] = {
    {2, {8, 5, 0, 10, 8, 0, 0, 0, 5, 0}, 0},
    {0, {0, 0, 0, 0, 0, 0, 10, 0, 0, 0}, 0},
};

int lbl_802DEA78[12] = {17, 33, 19, 18, 30, 27, 28, 29, 31, 32, 10, 0};

void Class_802A1C30::vfn_03(float dt)
{
    unsigned int i;

    ClockRuleClearFlags(2048);
    fn_8009D8CC(1);
    for (i = 0; i < 4; i++) {
        PlyrFindById(fn_801530FC()->mEntries[i].mUnknown0)->mUnknown9[2] = 1;
    }
    fn_80148A58()->vfn_12();
    fn_80148A58()->vfn_16(lbl_802DEA78);
    fn_8021D7B8(gUISMainInfo, 0x8000003A, 0, 0);
    if (StoryEventsGetCurrentEvent()) {
        StoryEventsSetRewardPenalty(fn_801529C0(&lbl_8031BDD4));
    }
    Class_80297B90::vfn_03(dt);
}

void Class_802A1C30::vfn_08()
{
    PauseOpenScreen(3, 19, -1);
}

void Class_802A1C30::vfn_09()
{
    fn_8021956C(gUISMainInfo, 3, 19, 1);
}

 /* extern "C" */

Class_802A2918::Class_802A2918()
{
    mpUnknown1C = 0;
    mUnknown32 = 0;
    mUnknown36 = 0;
    mUnknown40 = 0;
    mState.mCount = 2;
    mState.mpRecords = lbl_802DEA18;
}

void Class_802A2918::vfn_01()
{
    void *pHandle = 0;
    int allocate = fn_80149014() == 0;
    Table_8015005C *pTable;

    mpUnknown1C = new (0) Object_8015005C;
    if (allocate) {
        pHandle = SyncStateRegister(0, (void **)&mpUnknown1C->mpUnknown36, sizeof(Table_8015005C), 0, 0x4D474A42);
        pTable = (Table_8015005C *)SyncStateGetData(pHandle);
    } else {
        mpUnknown1C->mpUnknown36 = (Table_8015005C *)fn_801D2B7C(sizeof(Table_8015005C), 0, 0);
        pTable = mpUnknown1C->mpUnknown36;
    }
    memset(pTable, 0, sizeof(Table_8015005C));
    pTable->mCount = 4;
    pTable->mUnknown119 = 3;
    pTable->mUnknown125 = 2;
    pTable->mUnknown124 = 0;
    pTable->mUnknown126 = 0;
    pTable->mUnknown120 = GameOptionsGet(14);
    if (pTable->mUnknown120 != 0) {
        GameOptionsSet(14, 0);
    }
    if (allocate) {
        SyncStateCommit(pHandle);
    }
    fn_80178F20(&mpUnknown1C->mUnknown32);
    fn_800BC51C(&mpUnknown1C->mUnknown0);
    fn_800BFAB4(&mpUnknown1C->mUnknown8);
    fn_800A039C(&mpUnknown1C->mUnknown12);
    fn_800B9598(&mpUnknown1C->mUnknown24);
    fn_800AACB8(&mpUnknown1C->mUnknown28);
    mpUnknown1C->mpUnknown36->mUnknown116 = GameOptionsGet(19);
    if (mpUnknown1C->mpUnknown36->mUnknown116 != 0) {
        GameOptionsSet(19, 0);
    }
    PlyrStarSetBallRingEnabled(0);
}

void Class_802A2918::vfn_02()
{
    PlyrStarSetBallRingEnabled(1);
    if (mpUnknown1C->mpUnknown36->mUnknown116 != 0) {
        GameOptionsSet(19, 1);
    }
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_800AACB8(0);
    if (mpUnknown1C->mpUnknown36->mUnknown120 != 0) {
        GameOptionsSet(14, mpUnknown1C->mpUnknown36->mUnknown120);
    }
    fn_80178F20(0);
    if (fn_80149014()) {
        fn_801D2BD0(mpUnknown1C->mpUnknown36);
    }
    delete mpUnknown1C;
    mpUnknown1C = 0;
}

extern "C" {

int fn_80151B20(Class_802A2918 *p)
{
    if (p->mUnknown40 == 0) {
        Entry_8015005C *pFirst = &p->mpUnknown1C->mpUnknown36->mEntries[0];
        Entry_8015005C *pSecond = pFirst + 1;

        return pFirst->mUnknown10 + pFirst->mUnknown8 * 2 ==
               pSecond->mUnknown10 + pSecond->mUnknown8 * 2;
    } else {
        Table_8015005C *pTable = p->mpUnknown1C->mpUnknown36;
        int lower = 0;
        unsigned int score = pTable->mEntries[0].mUnknown10 + pTable->mEntries[0].mUnknown8 * 2;
        unsigned int i;

        for (i = 1; i < pTable->mCount; i++) {
            if (pTable->mEntries[i].mUnknown10 + pTable->mEntries[i].mUnknown8 * 2 < score) {
                lower = 1;
            }
        }
        return !lower;
    }
}

void fn_80151BCC(Class_802A2918 *p)
{
    unsigned int i;
    unsigned int count;
    Object_80039F5C *pPlayer;

    count = p->mpUnknown1C->mpUnknown36->mUnknown119;
    for (i = 0; i < count; i++) {
        pPlayer = PlyrGet(0, i);
        float limit = fn_80177FFC(0).mY;
        if (pPlayer->mMotion.mPos.mY > limit) {
            pPlayer->mMotion.mPos.mY = limit;
        }
    }
    count = p->mpUnknown1C->mpUnknown36->mCount;
    for (i = 0; i < count; i++) {
        pPlayer = PlyrFindById(p->mpUnknown1C->mpUnknown36->mEntries[i].mUnknown0);
        float limit = fn_80177FFC(1).mY + 5.0f;
        if (pPlayer->mMotion.mPos.mY < limit) {
            pPlayer->mMotion.mPos.mY = limit;
        }
    }
}

void fn_80151CCC(Class_802A2918 *p, unsigned int index, unsigned char value)
{
    Object_80039F5C *pPlayer;
    Object_80039F5C *pOther;

    p->mpUnknown1C->mpUnknown36->mEntries[index].mUnknown13 = 1;
    p->mpUnknown1C->mpUnknown36->mCount--;
    p->mpUnknown1C->mpUnknown36->mUnknown119--;
    pPlayer = PlyrFindById(p->mpUnknown1C->mpUnknown36->mEntries[index].mUnknown0);
    fn_800B6658(pPlayer);
    if (value) {
        pOther = PlyrGet(1, p->mpUnknown1C->mpUnknown36->mCount);
        if (pOther != pPlayer) {
            fn_801488D4(pPlayer, pOther);
        }
        fn_80148814(pOther);
        HudSetScoreTableRows(p->mpUnknown1C->mpUnknown36->mCount);
    }
}

void fn_80151D9C(Class_802A2918 *p)
{
    char text[83];
    char line[83];
    int over = 0;
    unsigned char sudden = 0;
    Table_8015005C *pTable;
    Object_80039F5C *pPlayer;
    unsigned int i;
    bool last;
    Class_802A1D20 *pState;
    Entry_8015005C *pEntries;
    Entry_8015005C *pRows;

    if ((p->mUnknown36 != 0 && fn_8009D990(1) == 0) ||
        (p->mUnknown32 != 0 &&
         p->mpUnknown1C->mpUnknown36->mEntries[0].mUnknown10 +
                 p->mpUnknown1C->mpUnknown36->mEntries[0].mUnknown8 * 2 >= p->mUnknown32)) {
        if (fn_80151B20(p)) {
            pTable = p->mpUnknown1C->mpUnknown36;
            if (pTable->mUnknown124 == 0) {
                pTable->mUnknown124 = 1;
                HudShowCallout("Sudden Death!");
            }
        } else {
            over = 1;
            pTable = p->mpUnknown1C->mpUnknown36;
            if (pTable->mUnknown124 != 0) {
                sudden = 1;
            }
            pTable->mUnknown124 = 0;
        }
    }
    if (!over) {
        return;
    }
    if (p->mUnknown40 == 0) {
        p->mpUnknown1C->mpUnknown36->mUnknown126 = sudden;
        fn_801502B4(&p->mpUnknown1C->mUnknown32);
        return;
    }
    strncpy(text, "Starting next round.\n", sizeof(text));
    for (i = 3; i != 0; i--) {
        if (p->mpUnknown1C->mpUnknown36->mEntries[i].mUnknown13 == 0) {
            pPlayer = PlyrFindById(p->mpUnknown1C->mpUnknown36->mEntries[i].mUnknown0);
            fn_801C2D88(line, sizeof(line), "Eliminated %s %s.\n", pPlayer->mUnknown2927,
                        pPlayer->mUnknown2927 + 21);
            strncat(text, line, sizeof(text) - strlen(text));
            pEntries = p->mpUnknown1C->mpUnknown36->mEntries;
            if (pEntries[i].mUnknown10 + pEntries[i].mUnknown8 * 2 !=
                pEntries[i - 1].mUnknown10 + pEntries[i - 1].mUnknown8 * 2) {
                break;
            }
        }
    }
    last = i == 1;
    for (; i <= 3; i++) {
        if (p->mpUnknown1C->mpUnknown36->mEntries[i].mUnknown13 == 0) {
            fn_80151CCC(p, i, !last);
        }
    }
    if (last) {
        p->mpUnknown1C->mpUnknown36->mUnknown126 = sudden;
        fn_801502B4(&p->mpUnknown1C->mUnknown32);
        return;
    }
    HudShowCallout(text);
    for (i = 0; i < 4; i++) {
        pRows = p->mpUnknown1C->mpUnknown36->mEntries;
        if (pRows[i].mUnknown10 + pRows[i].mUnknown8 * 2 > pRows[i].mUnknown4) {
            pRows[i].mUnknown4 = pRows[i].mUnknown10 + pRows[i].mUnknown8 * 2;
        }
        pRows[i].mUnknown14 += pRows[i].mUnknown8;
        pRows[i].mUnknown16 += pRows[i].mUnknown10;
        pRows[i].mUnknown8 = 0;
        pRows[i].mUnknown10 = 0;
    }
    ClockRuleClearFlags(0x800);
    fn_8009D8CC(1);
    fn_8009D964(1, fn_8009D9A8(1));
    pState = &p->mpUnknown1C->mUnknown12;
    pState->mUnknown9 = 1;
    pState->mUnknown8 = 0;
}

void fn_80152068(int index, Vector_80039F5C *pOut)
{
    pOut->mX = (fn_801530FC()->mUnknown92 + index)->mX;
    pOut->mY = (fn_801530FC()->mUnknown92 + index)->mY;
    pOut->mZ = 0.0f;
}

int fn_801520C4(Object_80039F5C *p, unsigned char *pIndex)
{
    unsigned int count = BallsGetCount();
    int result = 0;
    float best = -3.4028234663852886e38f;

    if (p->mUnknown8 != 255) {
        return fn_8015228C(p, pIndex);
    }
    *pIndex = 0;
    unsigned int players = fn_801530FC()->mCount;
    unsigned char i;

    for (i = 0; i < count; i++) {
        Ball_t *pBall = BallGet(i);
        float score = 0.0f;

        if (BallIsVisible(pBall) && BallStateGet(pBall, 0) == 4) {
            Vector_80039F5C position;
            BallGetLandingPoint(pBall, &position);
            float distance = Vec2Distance(&position, &p->mMotion.mPos);
            score = SyncRandGetFloatRange(0, score, 0.75f);
            if (i == 0) {
                score += 0.5f;
            }
            unsigned char closer = 0;
            unsigned char j;
            for (j = 0; j < players; j++) {
                Object_80039F5C *pOther = PlyrGet(1, j);
                if (pOther != p && !(Vec2Distance(&position, &pOther->mMotion.mPos) >= distance)) {
                    closer++;
                }
            }
            score -= closer * closer * 1.5f;
            if (!(score <= best)) {
                *pIndex = i;
                best = score;
                result = 1;
            }
        }
    }
    return result;
}

int fn_8015228C(Object_80039F5C *p, unsigned char *pIndex)
{
    unsigned int count = BallsGetCount();
    int result = 0;
    *pIndex = 0;
    float best = -3.4028234663852886e38f;
    fn_801530FC();
    unsigned char i;

    for (i = 0; i < count; i++) {
        Ball_t *pBall = BallGet(i);
        if (BallIsVisible(pBall) && BallStateGet(pBall, 0) == 4) {
            Vector_80039F5C position;
            Point_8017886C delta;
            BallGetLandingPoint(pBall, &position);
            Vec2Sub(&delta, &position, &p->mMotion.mPos);
            int direction = delta.Heading();
            float score = MathAngleDiff(direction, p->mUnknown512.mUnknown4);
            score *= 0.00000011920928955078125f;
            score = 1.0f - score;
            score *= 5.0f;
            score *= p->mUnknown512.mUnknown0;
            score -= Vec2Distance(&position, &p->mMotion.mPos);
            if (!(score <= best)) {
                *pIndex = i;
                best = score;
                result = 1;
            }
        }
    }
    return result;
}

} /* extern "C" */

void Class_802A2918::vfn_10(int value, int *list, int *ids)
{
    unsigned char i;

    for (i = 0; i < 7 && list[i] != 32767; i++) {
        ids[i] = ids[i + 7] = list[i];
    }
}

void Class_802A2918::vfn_11(int value, int *list, int *ids, unsigned int a, int b)
{
    vfn_10(value, list, ids);
}

void Class_802A2918::vfn_12()
{
    for (unsigned short i = 0; i <= 3; i++) {
        if (mpUnknown1C->mpUnknown36->mEntries[i].mUnknown12 == 255) {
            continue;
        }
        char name[32];
        if (!UserProfileGetPadName(GameTextGetPadPlayer(mpUnknown1C->mpUnknown36->mEntries[i].mUnknown12), name, 31)) {
            continue;
        }
        QueryResult result;
        QueryCursor cursor;
        unsigned int score = 0;
        int key = 0;
        cursor.mUnknown0 = 0;
        cursor.mUnknown4 = 0;
        cursor.mUnknown8 = -1;
        cursor.mUnknown12 = 0;
        TDbCompilePerformOp(&result, "use 'EVAS' declare \x8a fastcursor for select 'SJSH' into \x85 and 'KPSH' into \x82 from 'BJSH' order by 'SJSH' asc and 'KPSH' asc\n",
                    &cursor, &score, &key);
        cursor.mUnknown4 = 0;
        TDbCompilePerformOp(0, "fetch from \212\n", &cursor);
        if (cursor.mUnknown0) {
            TDbSQLDestroyCursor(&cursor);
        }
        MiniGameSlotInfo_t info;
        fn_80152940(this, i, &info);
        if (score < (unsigned int)info.mUnknown8) {
            int id = 0;
            int status = TDbCompilePerformOp(0, "use 'EVAS' select 'KPSH' into \202 from 'RCSH' where 'KUSH' = \210\n", &id, name);
            if (status == 23) {
                id = UserProfileGetFreeKey(0x52435348, 0x4B505348, 0, 255);
                if (id == -1) {
                    continue;
                }
                TDbCompilePerformOp(0, "use 'EVAS' insert into 'RCSH' set 'KPSH' = \202 and 'KUSH' = \210 and 'WGSH' = 0 and 'LGSH' = 0 and 'PTSH' = 0 and 'TPSH' = 0 and 'TRSH' = 0 and 'TDSH' = 0 and 'TSSH' = 0 and 'CISH' = 0 and 'RFSH' = 0 and 'GTSH' = 0 and '2TSH' = 0 and 'TTSH' = 0 and 'CNWH' = 0\n", id, name);
            }
            if (id != -1) {
                TDbCompilePerformOp(&result, "use 'EVAS' update 'BJSH' set 'SJSH' = \x85 and 'UBJH' = \x82 where 'KPSH' = \x82\n",
                            info.mUnknown8, id, key);
            }
        }
    }
}

extern "C" {

Object_80039F5C *fn_8015264C(Class_802A2918 *p)
{
    return PlyrFindById(lbl_8031BDD4.mpUnknown1C->mpUnknown36->mEntries[0].mUnknown0);
}

} /* extern "C" */

int Class_802A2918::vfn_13()
{
    if (GameModeTypeGet() == 7) {
        return fn_801529C0(this) <= 2;
    }
    return lbl_8031BDD4.mpUnknown1C->mpUnknown36->mEntries[0].mUnknown12 != 255;
}

extern "C" {

void fn_801526EC(Class_802A2918 *p)
{
    unsigned char i;

    p->mpUnknown1C->mpUnknown36->mCount = 4;
    p->mpUnknown1C->mpUnknown36->mUnknown119 = 3;
    p->mpUnknown1C->mpUnknown36->mUnknown124 = 0;
    p->mpUnknown1C->mpUnknown36->mUnknown125 = 2;
    for (i = 0; i <= 3; i++) {
        Entry_8015005C *pEntries = p->mpUnknown1C->mpUnknown36->mEntries;

        pEntries[i].mUnknown4 = pEntries[i].mUnknown8 = pEntries[i].mUnknown10 =
            pEntries[i].mUnknown14 = pEntries[i].mUnknown16 = 0;
        p->mpUnknown1C->mpUnknown36->mEntries[i].mUnknown13 = 0;
        PlyrGet(1, i)->mUnknown9[2] = 1;
    }
}

void fn_801527B8(Class_802A2918 *p, Vector_80039F5C *pOut)
{
    *pOut = p->mpUnknown1C->mpUnknown36->mUnknown80;
}

void fn_801527E0(Class_802A2918 *p, int value)
{
    unsigned char begin = fn_801530FC()->mUnknown119;

    fn_801487C0(1, 4);
    if (value) {
        unsigned int i;

        for (i = 0; i < 4; i++) {
            if (fn_801530FC()->mEntries[i].mUnknown13) {
                fn_80148814(PlyrFindById(fn_801530FC()->mEntries[i].mUnknown0));
            }
        }
    }
    fn_801487C0(0, begin);
}

Object_80039F5C *fn_8015286C(Class_802A2918 *p, int index)
{
    return PlyrFindById(p->mpUnknown1C->mpUnknown36->mEntries[index].mUnknown0);
}

} /* extern "C" */

int Class_802A2918::vfn_23(AutoDepthPlayer_t *pRecords, unsigned int count)
{
    unsigned int n = 0;
    unsigned int i;

    for (i = 0; i < count; i++) {
        if (pRecords[i].excluded) {
            n++;
        }
    }
    return n > 3;
}

extern "C" {

void fn_801528E0(Class_802A2918 *p, Point_8017886C *pOut)
{
    pOut->mX = 0.0f;
    pOut->mY = fn_80177FE0().mY + 20.0f + 10.0f;
}

char *lbl_803EB2F0 = "Open Field Showdown\n\nScore against your opponent in an open field situation, then stop your opponent from scoring in the very same situation.";
int lbl_803EB2F4 = 0;

void fn_80152940(Class_802A2918 *p, int index, MiniGameSlotInfo_t *pInfo)
{
    Entry_8015005C *pEntry = &p->mpUnknown1C->mpUnknown36->mEntries[index];

    pInfo->mUnknown4 = pEntry->mUnknown16 + pEntry->mUnknown14 * 2;
    pInfo->mUnknown8 = pEntry->mUnknown4;
    pInfo->mUnknown12 = pEntry->mUnknown14;
    pInfo->mUnknown16 = pEntry->mUnknown16;
    pInfo->mpObject = PlyrFindById(pEntry->mUnknown0);
    pInfo->mUnknown20 = pEntry->mUnknown12;
    pInfo->mUnknown21 = index;
}

int fn_801529C0(Class_802A2918 *p)
{
    MiniGameSlotInfo_t info;
    unsigned char result = 0;
    int i;

    for (i = 0; i <= 3; i++) {
        if (fn_801530FC()->mEntries[i].mUnknown12 != 255) {
            fn_80152940(p, i, &info);
            result = info.mUnknown21;
            break;
        }
    }
    return result;
}

} /* extern "C" */

int Class_802A2918::vfn_30(int kind, int team, int index, Object_80039F5C *pPlayer)
{
    MiniGameSlotInfo_t info;
    int result = 0;

    fn_80152940(this, index, &info);
    if (info.mpObject != 0) {
        switch (kind) {
        case 27:
            result = info.mUnknown16 + info.mUnknown12;
            break;
        case 28:
        case 29:
            result = info.mUnknown12;
            break;
        case 31:
            result = 0;
            break;
        case 32:
            fn_8022B414(pPlayer->mUnknown2908, 0x64706467, &result);
            break;
        case 18:
            result = 4 - info.mUnknown21;
            break;
        case 17:
        case 19:
            result = info.mUnknown4;
            break;
        default:
            result = Class_80148A58::vfn_30(kind, team, index, pPlayer);
            break;
        }
    }
    return result;
}

int Class_802A2918::vfn_26(int team, int index, Object_80039F5C *pPlayer, int kind)
{
    int result = 0;
    MiniGameSlotInfo_t info;

    if (team == 1 && (unsigned int)index <= 3) {
        fn_80152940(this, index, &info);
        Object_80039F5C *pSlotPlayer = info.mpObject;
        if (pSlotPlayer != 0) {
            switch (kind) {
            case 27:
                {
                    int ok = pSlotPlayer != fn_8015264C(this) && vfn_31(27, 1, index, pSlotPlayer, 1, 0);
                    result = ok;
                }
                break;
            case 28:
                {
                    int ok = !vfn_27(1, index, 30) && vfn_31(28, 1, index, pSlotPlayer, 3, 0);
                    result = ok;
                }
                break;
            case 29:
                result = vfn_30(29, 1, index, pSlotPlayer) == 0;
                break;
            case 30:
                {
                    int ok = info.mUnknown16 == 0 && (unsigned int)info.mUnknown12 > 2;
                    result = ok;
                }
                break;
            case 31:
                result = vfn_31(31, 1, index, pSlotPlayer, 1, 0);
                break;
            case 32:
                result = vfn_31(32, 1, index, pSlotPlayer, 1, 0);
                break;
            case 17:
                {
                    int ok = vfn_31(17, 1, index, pSlotPlayer, 1, 0) &&
                             (unsigned int)info.mUnknown4 >= (unsigned int)RecordsGetValue(23);
                    result = ok;
                }
                break;
            case 18:
                {
                    int ok = !vfn_27(1, index, 33) && !vfn_27(1, index, 19) &&
                             vfn_31(18, 1, index, pSlotPlayer, 1, 0);
                    result = ok;
                }
                break;
            case 33:
                {
                    int ok = vfn_31(18, 1, index, pSlotPlayer, 1, 0) && mpUnknown1C->mpUnknown36->mUnknown126;
                    result = ok;
                }
                break;
            case 19:
                if (vfn_31(19, 1, index, pSlotPlayer, 1, 0)) {
                    MiniGameSlotInfo_t other;
                    unsigned int i;
                    result = 1;
                    for (i = 0; i <= 3; i++) {
                        if (index == i) {
                            continue;
                        }
                        fn_80152940(this, i, &other);
                        if ((unsigned int)info.mUnknown4 < (unsigned int)(other.mUnknown4 * 2)) {
                            result = 0;
                            break;
                        }
                    }
                }
                break;
            default:
                result = Class_80148A58::vfn_26(team, index, pSlotPlayer, kind);
                break;
            }
        }
    }
    return result;
}

int Class_802A2918::vfn_05(int team)
{
    if (team == 0) {
        return mpUnknown1C ? mpUnknown1C->mpUnknown36->mUnknown119 : 3;
    }
    return mpUnknown1C ? mpUnknown1C->mpUnknown36->mCount : 4;
}

int Class_802A2918::vfn_21()
{
    return 0;
}

int Class_802A2918::vfn_22(int value)
{
    int result = 0;

    if (value != 255) {
        Entry_8015005C *pEntry = fn_801530FC()->mEntries;
        Entry_8015005C *pEnd = pEntry + 3;
        int count = 0;

        for (; pEntry <= pEnd; pEntry++) {
            unsigned char kind = pEntry->mUnknown12;

            if (kind != 255 && pEntry->mUnknown13 == 0) {
                count++;
                if (kind == value) {
                    result = 1;
                    break;
                }
            }
        }
        if (count == 0) {
            result = 1;
        }
    }
    return result;
}

extern "C" {

Table_8015005C *fn_801530FC(void)
{
    return lbl_8031BDD4.mpUnknown1C->mpUnknown36;
}

int fn_8015310C(Class_802A2918 *p)
{
    int result = 1;
    unsigned char i;

    for (i = 0; i < BallsGetCount(); i++) {
        if (p->mUnknown44[i] == 0) {
            result = 0;
            break;
        }
    }
    return result;
}

void fn_80153168(Class_802A2918 *p, int index, unsigned char value)
{
    p->mUnknown44[index] = value;
}

} /* extern "C" */

int Class_802A1930::GetScoreLimit()
{
    unsigned short score0 = fn_801787DC(0);
    unsigned short score1 = fn_801787DC(1);

    unsigned short high;

    if (score0 > score1) {
        high = score0;
    } else {
        high = score1;
    }
    return high + 8;
}

int Class_802A1930::GetWinner()
{
    return fn_80155128(fn_80148A58())->mpUnknown52->mUnknown32;
}

int Class_802A1930::IsNearWin(int team)
{
    Score_801531C4 *pScore = fn_80155128(fn_80148A58())->mpUnknown52;
    int other = !team;
    unsigned int score = pScore->mUnknown24[team];
    unsigned int otherScore = pScore->mUnknown24[other];

    if (pScore->mUnknown20[team] < pScore->mUnknown16) {
        score++;
    }
    otherScore += pScore->mUnknown16 - pScore->mUnknown20[other];
    return score > otherScore;
}

int Class_802A1930::IsOpponentNearWin(int team)
{
    Score_801531C4 *pScore = fn_80155128(fn_80148A58())->mpUnknown52;
    int other = !team;
    unsigned int score = pScore->mUnknown24[team];
    unsigned int otherScore = pScore->mUnknown24[other];

    score += pScore->mUnknown16 - pScore->mUnknown20[team];
    return score <= otherScore;
}

int Class_802A1930::GetScoreType()
{
    return 2;
}

int Class_802A1930::GetScore(int team)
{
    return fn_80155128(fn_80148A58())->mpUnknown52->mUnknown24[team];
}

unsigned int Class_802A1930::GetGoalLimit()
{
    return fn_80155128(fn_80148A58())->mpUnknown52->mUnknown16;
}

int Class_802A1930::GetGoalTotal(int team)
{
    return fn_80155128(fn_80148A58())->mpUnknown52->mUnknown20[team];
}

int Class_802A1930::GetGoalCount(int team)
{
    return fn_80155128(fn_80148A58())->mpUnknown52->mUnknown24[team];
}

unsigned short Class_802A1930::vfn_22(int team)
{
    return fn_80155128(fn_80148A58())->mpUnknown52->mUnknown28[team];
}

int Class_802A1930::AllowsAudibles()
{
    unsigned int count0 = 0;
    unsigned int count1 = 0;
    int mode = fn_80148A58()->vfn_05(0);
    int i;

    for (i = 0; i <= 6; i++) {
        if (PlyrGet(0, i)->mUnknown8 != 255) {
            count0++;
        } else if (PlyrGet(1, i)->mUnknown8 != 255) {
            count1++;
        }
    }
    if (mode == 2 && count0 <= 1 && count1 <= 1) {
        return 1;
    }
    return 0;
}

void Class_802A1930::ResetPlaySpot()
{
    int a = 1;
    Rules_801531C4 *pRules = fn_80155128(fn_80148A58());
    Object_8017886C *o = fn_8017886C();
    if (fn_80178348() == fn_80178308()) {
        a = 0;
    }
    int kind = fn_800948E4(o);
    ScrmRuleSet::ResetPlaySpot();
    if (pRules->mpUnknown52->mUnknown32 == 2) {
        pRules->mpUnknown52->mUnknown20[fn_80178348()]++;
        if (kind == 2) {
            if (a == 0) {
                pRules->mpUnknown52->mUnknown24[fn_80178348()]++;
            } else {
                pRules->mpUnknown52->mUnknown28[fn_80178360()]++;
                if (pRules->mpUnknown52->mUnknown24[fn_80178348()] != 0) {
                    pRules->mpUnknown52->mUnknown24[fn_80178348()]--;
                }
            }
        } else {
            pRules->mpUnknown52->mUnknown28[fn_80178360()]++;
        }
        Score_801531C4 *pScore = pRules->mpUnknown52;
        if (pScore->mUnknown20[0] >= pScore->mUnknown16 && pScore->mUnknown20[1] >= pScore->mUnknown16) {
            if (pScore->mUnknown24[0] > pScore->mUnknown24[1]) {
                pScore->mUnknown32 = 0;
            } else if (pScore->mUnknown24[1] > pScore->mUnknown24[0]) {
                pScore->mUnknown32 = 1;
            } else {
                pScore->mUnknown16++;
            }
        }
        if (a == 0 ? kind != 8 : kind == 8) {
            fn_8017833C(fn_80178320());
        } else if (kind != 8) {
            fn_80177E6C(0, 1);
        }

        int team = fn_80178308();
        if (fn_80178D70(team) == 2) {
            FormationLineupSwapAllUser(1, team, 0, 2);
        }
        fn_80178CD8(1);
    }
    ((Class_802A27F0 *)fn_80148A58())->vfn_35(fn_80178348(), 0);
}

void Class_802A1930::ResetGame(int team)
{
    Rules_801531C4 *pRules = fn_80155128(fn_80148A58());

    ScrmRuleSet::ResetGame(team);
    memset(pRules->mpUnknown52->mUnknown20, 0, sizeof(pRules->mpUnknown52->mUnknown20));
    memset(pRules->mpUnknown52->mUnknown24, 0, sizeof(pRules->mpUnknown52->mUnknown24));
    memset(pRules->mpUnknown52->mUnknown28, 0, sizeof(pRules->mpUnknown52->mUnknown28));
    pRules->mpUnknown52->mUnknown32 = 2;
    pRules->mpUnknown52->mUnknown16 = pRules->mpUnknown52->mUnknown12;
    StyleTrackerSetEnabled(0);
}

void Class_802A1BC8::OnEnter(float dt)
{
    PreGamePhase::OnEnter(dt);
    fn_80148A58()->vfn_14();
    HudSetScoreTableRows(fn_80178D70(0) * 2);
    ((Class_802A27F0 *)fn_80148A58())->vfn_35(0, 0);
    ((Class_802A27F0 *)fn_80148A58())->vfn_35(1, 0);
    HudPost3AOff();
    fn_800A8738(1);
    TutorialReleasePause();
}

void Class_802A1930::AwardWin(int team)
{
    Rules_801531C4 *pRules = fn_80155128(fn_80148A58());
    int other = !team;

    pRules->mpUnknown52->mUnknown24[team] = pRules->mpUnknown52->mUnknown20[team] = pRules->mpUnknown52->mUnknown20[other] = pRules->mpUnknown52->mUnknown16;
    if (pRules->mpUnknown52->mUnknown24[other] >= pRules->mpUnknown52->mUnknown24[team]) {
        pRules->mpUnknown52->mUnknown24[other] = pRules->mpUnknown52->mUnknown24[team] - 1;
    }
    pRules->mpUnknown52->mUnknown32 = team;
}

void Class_802A1BC8::OnExit()
{
    PreGamePhase::OnExit();
    CamGameSetModeAll(1);
    CamGameSelectCamera(0);
    CamMainWarpToDest(CamGameGetCamera(5));
    CamPlaySetYOffset(2.5f);
}

void Class_802A1BC8::OnUpdate(float dt)
{
    if (MsgBoxIsClosed()) {
        PreGamePhase::OnUpdate(dt);
    }
}

void Class_802A1BC8::ShowIntroScreen()
{
    if (fn_800C1E40() == 0) {
        MsgBoxShow("Open Field Showdown", lbl_803EB2F0, "|^Done");
    }
}

void Class_802A1BC8::HideIntroScreen()
{
}

void Class_802A1B58::OnEnter(float dt)
{
    Rules_801531C4 *pRules = fn_80155128(fn_80148A58());
    int team = fn_80178308();

    fn_801486A8();
    PreSnapPhase::OnEnter(dt);
    fn_801487C0(0, fn_80148A58()->vfn_05(0));
    fn_801487C0(1, fn_80148A58()->vfn_05(1));
    do {
        pRules->mpUnknown52->mUnknown8 = SyncRandGetRange(0, 3);
    } while (pRules->mpUnknown52->mUnknown8 == pRules->mpUnknown52->mUnknown0[team] && SyncRandGetRange(0, 100) > 20);
    pRules->mpUnknown52->mUnknown0[team] = pRules->mpUnknown52->mUnknown8;
    ((Class_802A27F0 *)fn_80148A58())->vfn_35(fn_80178308(), 1);
    ((Class_802A27F0 *)fn_80148A58())->vfn_35(fn_80178320(), 0);

    unsigned int limit = pRules->mpUnknown52->mUnknown12;
    if (pRules->mUnknown44.GetGoalLimit() > limit && pRules->mpUnknown52->mUnknown20[0] == pRules->mpUnknown52->mUnknown20[1]) {
        HudShowAlert("Playoff Round!");
    }
    if ((unsigned int)fn_80178D70(0) > 1) {
        unsigned int value = fn_8009D990(0);
        lbl_803EABA4->fn_800C02D4(value - 2);
        value = fn_8009D990(0);
        lbl_803EABA4->fn_800C02EC(value - 4);
    } else {
        lbl_803EABA4->fn_800C02EC(39);
    }
    BallResetToSpot();
    Ball_t *pBall = BallGetCurrent();
    Vector_80039F5C pos;
    BallGetPosition(pBall, &pos);
    BallGiveToPlayer(pBall, PlyrFindNearest(&pos, 0, fn_80178308()));
}

void Class_802A1B58::AssignControlledPlayers()
{
    PreSnapPhase::AssignControlledPlayers();
    int team = fn_80178308();
    unsigned char kind = PortDbCountSidePlayers(team);
    unsigned char first = fn_800B65A0(team);
    unsigned char second = fn_800B65D0(team);
    Object_80039F5C *p0 = PlyrGet(team, 0);
    Object_80039F5C *p1 = PlyrGet(team, 1);

    if (kind == 2) {
        if (!mpUnknown4[team][0]) {
            mpUnknown4[team][0] = p0->mpUnknown4;
            mUnknown20[team][0] = first;
        }
        if (!mpUnknown4[team][1]) {
            mpUnknown4[team][1] = p1->mpUnknown4;
            mUnknown20[team][1] = second;
        }
        if (mpUnknown4[team][0] == p0->mpUnknown4 || mUnknown20[team][0] != first) {
            fn_800B6714(p0, first);
            fn_800B6714(p1, second);
            fn_800B65C0(team, first);
        } else {
            fn_800B6714(p1, first);
            fn_800B6714(p0, second);
            fn_800B65C0(team, second);
        }
    }
    team = fn_80178320();
    kind = PortDbCountSidePlayers(team);
    first = fn_800B65A0(team);
    second = fn_800B65D0(team);
    p0 = PlyrGet(team, 0);
    p1 = PlyrGet(team, 1);
    if (kind == 2) {
        if (!mpUnknown4[team][0]) {
            mpUnknown4[team][0] = p0->mpUnknown4;
            mUnknown20[team][0] = first;
        }
        if (!mpUnknown4[team][1]) {
            mpUnknown4[team][1] = p1->mpUnknown4;
            mUnknown20[team][1] = second;
        }
        fn_800B6714(p0, first);
        fn_800B6714(p1, second);
        fn_800B65C0(team, first);
    }
    if (0) {
        OSReport("%s, %s", p0->mUnknown2927, p1->mUnknown2927);
        OSReport("%s-%s, %s", p0->mUnknown2927, p1->mUnknown2927, p0->mUnknown2927);
    }
}

void Class_802A1B18::vfn_03(float dt)
{
}

void Class_802A1B18::vfn_04(float dt)
{
    int team = fn_80178308();
    int other = !team;
    unsigned int flag = SyncRandGetRange(0, 100) & 1;

    PlayBookSetFormationType(team, 1);
    PlayBookSetFormationType(other, 11);
    PlayBookSetIndices(team, 0, 0, fn_800B65A0(team) == 255 ? flag : 0);
    PlayBookLoadCurrentPlay(team);
    FormationLineupApplyUser(PlayBookGetTeam(team)->mUnknown40, team);
    PlayBookSetIndices(other, 0, 0, 0);
    PlayBookLoadCurrentPlay(other);
    fn_800B3EFC(team);
    fn_800B3EFC(other);
    PlayBookLoadAudibles(fn_80178308());
    fn_800AD910(2, dt);
}

void Class_802A1B18::vfn_05(float dt)
{
    fn_8009D888(0, 10);
    CamGameResumeAll();
    ScrmTeamPlaceInHuddle(fn_80178308());
    ScrmTeamPlaceInHuddle(fn_80178320());
    fn_801790D0(fn_80178308(), 0.0f, 0.0f);
    fn_801790D0(fn_80178320(), 18.0f, 0.0f);
}

void Class_802A1AE0::OnEnter(float dt)
{
    LivePlayPhase::OnEnter(dt);
    mUnknown4 = 0;
    fn_8009D888(5, 0);
}

void Class_802A1AE0::OnUpdate(float dt)
{
    LivePlayPhase::OnUpdate(dt);
    if (fn_801787A0() == 0) {
        if (fn_8009D990(5) == 0) {
            HudShowAlert("Time Expired");
            fn_80178370();
        } else {
            unsigned int value;

            if (fn_80177C38() % 2 != (mUnknown4 & 1)) {
                mUnknown4++;
                fn_8009D8CC(5);
                fn_8009D964(5, 20);
                fn_8009D888(5, 0);
            }
            value = fn_8009D990(5);
            if (value != lbl_803EB2F4) {
                lbl_803EB2F4 = value;
                if (value <= 5) {
                    AudmonEventPost(20, 0);
                }
            }
        }
    }
}

void Class_802A1AE0::OnExit()
{
    LivePlayPhase::OnExit();
    fn_8009D8CC(5);
}

int Class_802A1A58::GetResultText(char *pText)
{
    char touchdown[10] = "Touchdown";
    char defensive[13] = "Defensive TD";
    int result = 0;
    int kind = fn_800A2178();

    if (kind == 0) {
        StyleTrackerOnTouchdown();
        result = 1;
        strcpy(pText, touchdown);
    } else if (kind == 14) {
        StyleTrackerOnTouchdown();
        result = 1;
        strcpy(pText, defensive);
    }
    return result;
}

Record_80148C4C lbl_802DEAA8[2] = {
    {0, {6, 0, 6, 0, 10, 8, 0, 2, 1, 1}, 0},
    {1, {6, 0, 6, 0, 10, 8, 0, 2, 1, 1}, 0},
};

int lbl_802DEB08[14] = {0, 2, 1, 3, 4, 5, 6, 9, 10, 7, 8, 11, 12, 13};

int lbl_802DEB40[14] = {1, 11, 12, 13, 9, 10, 2, 3, 0, 7, 8, 4, 5, 6};

int lbl_802DEB78[22] = {37, 39, 35, 16, 34, 36, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 0, 0};

void Class_802A19F0::vfn_03(float dt)
{
    ClockRuleClearFlags(2048);
    fn_8009D8CC(1);
    fn_80148A58()->vfn_12();
    fn_80148A58()->vfn_16(lbl_802DEB78);
    fn_8021D7B8(gUISMainInfo, 0x8000003A, 0, 0);
    Class_80297B90::vfn_03(dt);
}

void Class_802A19F0::vfn_08()
{
    PauseOpenScreen(3, 20, -1);
}

void Class_802A19F0::vfn_09()
{
    fn_8021956C(gUISMainInfo, 3, 20, 1);
}

 /* extern "C" */

Class_802A27F0::Class_802A27F0()
{
    mState.mUnknownC = 0;
    mState.mCount = 2;
    mState.mpRecords = lbl_802DEAA8;
}

void Class_802A27F0::vfn_01()
{
    void *pHandle = 0;
    int allocate = fn_80149014() == 0;
    Score_801531C4 *pScore;

    mpUnknown1C = new (0) Rules_801531C4;
    if (allocate) {
        pHandle = SyncStateRegister(0, (void **)&mpUnknown1C->mpUnknown52, sizeof(Score_801531C4), 0, 0x4D474F46);
        pScore = (Score_801531C4 *)SyncStateGetData(pHandle);
    } else {
        mpUnknown1C->mpUnknown52 = (Score_801531C4 *)fn_801D2B7C(sizeof(Score_801531C4), 0, 0);
        pScore = mpUnknown1C->mpUnknown52;
    }
    memset(pScore, 0, sizeof(Score_801531C4));
    pScore->mUnknown8 = 3;
    pScore->mUnknown0[0] = 3;
    pScore->mUnknown0[1] = 3;
    pScore->mUnknown16 = pScore->mUnknown12 = mUnknown25;
    pScore->mUnknown32 = 2;
    mpUnknown1C->mUnknown4.mpUnknown4[0][0] = 0;
    mpUnknown1C->mUnknown4.mpUnknown4[0][1] = 0;
    mpUnknown1C->mUnknown4.mpUnknown4[1][0] = 0;
    mpUnknown1C->mUnknown4.mpUnknown4[1][1] = 0;
    mpUnknown1C->mUnknown4.mUnknown20[0][0] = -1;
    mpUnknown1C->mUnknown4.mUnknown20[0][1] = -1;
    mpUnknown1C->mUnknown4.mUnknown20[1][0] = -1;
    mpUnknown1C->mUnknown4.mUnknown20[1][1] = -1;
    if (allocate) {
        SyncStateCommit(pHandle);
    }
    fn_800BC51C(&mpUnknown1C->mUnknown0);
    fn_800BFAB4(&mpUnknown1C->mUnknown4);
    fn_800B3644(&mpUnknown1C->mUnknown28);
    fn_800A039C(&mpUnknown1C->mUnknown32);
    fn_800B9598(&mpUnknown1C->mUnknown40);
    fn_800AACB8(&mpUnknown1C->mUnknown48);
    fn_80178F20(&mpUnknown1C->mUnknown44);
    fn_80178E88(fn_80178A2C() * 2.0f - 18.0f);
    mUnknown20 = GameOptionsGet(14);
    GameOptionsSet(14, 2);
}

void Class_802A27F0::vfn_02()
{
    fn_800BC51C(0);
    fn_800BFAB4(0);
    fn_800B3644(0);
    fn_800A039C(0);
    fn_800B9598(0);
    fn_800AACB8(0);
    GameOptionsSet(14, mUnknown20);
    fn_80178F20(0);
    if (fn_80149014()) {
        fn_801D2BD0(mpUnknown1C->mpUnknown52);
    }
    delete mpUnknown1C;
    mpUnknown1C = 0;
    fn_800A8738(0);
}

int Class_802A27F0::vfn_05(int team)
{
    return mUnknown24;
}

void Class_802A27F0::vfn_07(int kind, int value)
{
    switch (kind) {
    case 0:
        switch (value) {
        case 0:
            mUnknown0 = 8;
            mUnknown4 = 7;
            mUnknown24 = 2;
            break;
        case 1:
            mUnknown0 = 6;
            mUnknown4 = 5;
            mUnknown24 = 1;
            break;
        }
        break;
    case 1:
        mUnknown25 = value;
        break;
    }
}

static const float lbl_802A3000[3][8] = {
    {10.0f, 10.0f, 0.0f, -10.0f, -5.0f, 85.0f, 200.0f, 85.0f},
    {-5.0f, -10.0f, 0.0f, 10.0f, 10.0f, 85.0f, 200.0f, 85.0f},
    {-5.0f, -6.0f, -8.0f, -6.0f, -5.0f, 85.0f, 200.0f, 85.0f},
};

const float * Class_802A27F0::vfn_09(int index)
{
    if (index == 1) {
        return lbl_802A3000[fn_80155128(fn_80148A58())->mpUnknown52->mUnknown8];
    }
    return 0;
}

void Class_802A27F0::vfn_10(int value, int *pList, int *pIds)
{
    unsigned char i;

    for (i = 0; i < 7 && pList[i] != 32767; i++) {
        pIds[lbl_802DEB08[i]] = pIds[lbl_802DEB08[i + 7]] = pList[i];
    }
}

void Class_802A27F0::vfn_11(int value, int *pList, int *pIds, unsigned int count, int b)
{
    int second = pList[1];
    int found = 0;
    int first;
    unsigned char i;

    AutoDepthFillChart(value, pList, pIds);
    first = pList[0];
    if (fn_80178D70(0) == 1) {
        for (i = 0; i <= 6; i++) {
            if (pIds[i] == first) {
                pIds[i] = pIds[lbl_802DEB08[0]];
                pIds[lbl_802DEB08[0]] = first;
                break;
            }
        }
        for (i = 7; i <= 13; i++) {
            if (pIds[i] == first) {
                pIds[i] = pIds[lbl_802DEB08[7]];
                pIds[lbl_802DEB08[7]] = first;
                break;
            }
        }
    } else {
        unsigned char j;

        for (j = 0; j <= 13; j++) {
            unsigned char k;

            for (k = 1; k < count; k++) {
                if (pIds[lbl_802DEB40[j]] == pList[k]) {
                    second = pIds[lbl_802DEB40[j]];
                    found = 1;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        for (i = 0; i <= 6; i++) {
            if (pIds[i] == first) {
                pIds[i] = pIds[lbl_802DEB08[0]];
                pIds[lbl_802DEB08[0]] = first;
            }
        }
        for (i = 0; i <= 6; i++) {
            if (pIds[i] == second) {
                pIds[i] = pIds[lbl_802DEB08[1]];
                pIds[lbl_802DEB08[1]] = second;
            }
        }
        for (i = 7; i <= 13; i++) {
            if (pIds[i] == first) {
                pIds[i] = pIds[lbl_802DEB08[7]];
                pIds[lbl_802DEB08[7]] = first;
            }
        }
        for (i = 7; i <= 13; i++) {
            if (pIds[i] == second) {
                pIds[i] = pIds[lbl_802DEB08[8]];
                pIds[lbl_802DEB08[8]] = second;
            }
        }
    }
}

void Class_802A27F0::vfn_35(int team, int showColors)
{
    char text[16];
    int first = fn_80178EE0(team);
    int color = 255;
    int second = fn_80178EA0(team);

    fn_801C2E18(text, "%d / %d", first, second);
    if (mUnknown24 == 1) {
        int slot = team == 1 ? 1 : 2;
        Object_80039F5C *pPlayer = PlyrGet(team, 0);

        if (showColors) {
            color = fn_80155130(this, team, 0);
            if (color == 255) {
                color = 254;
            }
        }
        HudSetScoreTableRow(slot, pPlayer->mUnknown2927 + 21, text, "", color);
    } else {
        int slot = team == 1 ? 1 : 3;
        Object_80039F5C *pPlayer = PlyrGet(team, 0);

        if (showColors) {
            color = fn_80155130(this, team, 0);
            if (color == 255) {
                color = 254;
            }
        }
        HudSetScoreTableRow(slot, pPlayer->mUnknown2927 + 21, text, "", color);
        pPlayer = PlyrGet(team, 1);
        if (showColors) {
            color = fn_80155130(this, team, 1);
            if (color == 255) {
                color = 254;
            }
        }
        HudSetScoreTableRow(slot + 1, pPlayer->mUnknown2927 + 21, "",
                   "", color);
    }
}

void Class_802A27F0::vfn_14()
{
    fn_8009D8CC(5);
    fn_8009D964(5, 20);
}

int Class_802A27F0::vfn_26(int team, int index, Object_80039F5C *pPlayer, int kind)
{
    int other = !team;
    int result = 0;

    switch (kind) {
    case 1:
        if (vfn_27(team, index, 36) == 0 && vfn_27(team, index, 39) == 0) {
            result = Class_80148A58::vfn_26(team, index, pPlayer, kind);
        }
        break;
    case 9:
        result = Class_80148A58::vfn_26(team, index, pPlayer, kind);
        break;
    case 2:
        if (mUnknown24 > 1 && vfn_27(team, index, 35) == 0) {
            result = Class_80148A58::vfn_26(team, index, pPlayer, kind);
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 10:
    case 11:
    case 13:
    case 14:
    case 15:
        result = Class_80148A58::vfn_26(team, index, pPlayer, kind);
        break;
    case 16: {
        int value = 0;
        if (mpUnknown1C->mUnknown44.GetWinner() != team &&
            mpUnknown1C->mUnknown44.GetGoalLimit() > 10) {
            Class_802A1930 *pRules = &mpUnknown1C->mUnknown44;
            unsigned char selected = pRules->Class_802A1930::GetWinner();
            value = pRules->Class_802A1930::GetGoalCount(selected);
            value = value - mpUnknown1C->mUnknown44.GetGoalCount(team) == 1;
        }
        result = value;
        break;
    }
    case 34: {
        int value = 0;
        if (mpUnknown1C->mUnknown44.GetWinner() == team &&
            mpUnknown1C->mUnknown44.GetGoalLimit() > 10) {
            Class_802A1930 *pRules = &mpUnknown1C->mUnknown44;
            unsigned char selected = pRules->Class_802A1930::GetWinner();
            value = pRules->Class_802A1930::GetGoalCount(selected);
            value = value - mpUnknown1C->mUnknown44.GetGoalCount(other) == 1;
        }
        result = value;
        break;
    }
    case 35: {
        int value = 0;
        if (vfn_27(team, index, 39) == 0) {
            value = mpUnknown1C->mUnknown44.GetGoalCount(team);
            value = value == mpUnknown1C->mUnknown44.GetGoalTotal(team);
        }
        result = value;
        break;
    }
    case 36: {
        int value = 0;
        if (vfn_27(team, index, 39) == 0) {
            value = fn_80178EE0(other) == 0;
        }
        result = value;
        break;
    }
    case 37:
        if (mUnknown24 > 1) {
            int value = 0;
            Object_80039F5C *pOther = fn_80154FC0(this, team, index);
            if (vfn_30(1, team, index, pPlayer) > 2 && vfn_30(1, team, index, pOther) > 2 &&
                vfn_30(2, team, index, pPlayer) > 2 && vfn_30(2, team, index, pOther) > 2) {
                value = vfn_30(37, team, index, pPlayer) > 3;
            }
            result = value;
        }
        break;
    case 38:
        break;
    case 39: {
        int value = 0;
        if (vfn_26(team, index, pPlayer, 35) && vfn_26(team, index, pPlayer, 36)) {
            value = 1;
        }
        result = value;
        break;
    }
    }
    return result;
}

int Class_802A27F0::vfn_30(int kind, int team, int index, Object_80039F5C *pPlayer)
{
    int value;

    if (kind == 37) {
        fn_8022B7A4(lbl_803ECA24[team], 0x7A707374, &value);
    } else {
        value = Class_80148A58::vfn_30(kind, team, index, pPlayer);
    }
    return value;
}

extern "C" {

Object_80039F5C *fn_80154FC0(Class_802A27F0 *p, int team, int index)
{
    Object_80039F5C *result = 0;

    if (p->mUnknown24 > 1) {
        result = PlyrGet(team, index == 0);
    }
    return result;
}

} /* extern "C" */

void Class_802A27F0::vfn_20(int team, unsigned char index, int kind, char *pFirst, unsigned char firstLength, char *pSecond, unsigned char secondLength)
{
    Object_80039F5C *pPlayer = PlyrGet(team, index);
    switch (kind) {
    case 0:
        fn_801C2D88(pFirst, firstLength, "TDs");
        fn_801C2D88(pSecond, secondLength, "%d",
                    vfn_30(2, team, index, pPlayer));
        break;
    case 1:
        fn_801C2D88(pFirst, firstLength, "Tackles");
        fn_801C2D88(pSecond, secondLength, "%d",
                    vfn_30(1, team, index, pPlayer));
        break;
    }
}

char *lbl_803EB2F8 = "Quick Strike\n\nThe game consists of two series with each team putting the ball in play from their opponent's end of the field. Each team retains the ball until they score or run out of downs. The game continues until the tie is broken. If the game results in a tie the spot of the ball will be moved back a little further until someone finally wins.";
unsigned char lbl_803EB2FC = 0;
unsigned char lbl_803EB2FD = 0;

extern "C" {

Rules_801531C4 *fn_80155128(Class_80148A58 *p)
{
    return static_cast<Class_802A27F0 *>(p)->mpUnknown1C;
}

int fn_80155130(Class_80148A58 *p, int team, unsigned char index)
{
    int color = 255;

    if (fn_800B65A0(team) != 255) {
        if (PortDbCountSidePlayers(team) == 2) {
            Object_80039F5C *pPlayer = PlyrGet(team, index);
            Rules_801531C4 *pRules = static_cast<Class_802A27F0 *>(p)->mpUnknown1C;

            if (pRules->mUnknown4.mpUnknown4[team][index] != pPlayer->mpUnknown4) {
                color = pRules->mUnknown4.mUnknown20[team][index ^ 1];
            } else {
                color = pRules->mUnknown4.mUnknown20[team][index];
            }
        } else {
            color = fn_800B65A0(team);
        }
    }
    return color;
}

} /* extern "C" */

int Class_802A27F0::vfn_21()
{
    return 0;
}

int Class_802A17A8::GetScoreLimit()
{
    int mode = fn_80177F70();
    int team = fn_80178308();
    int other = !team;
    unsigned short score = fn_801787DC(team);
    unsigned short otherScore = fn_801787DC(other);

    int result;

    if (mode == 6) {
        if (fn_800A8444(team)) {
            result = score + 2;
        } else if (score == otherScore + 6) {
            result = SyncRandGetFloat(0) < 0.5f ? otherScore + 7 : otherScore + 8;
        } else {
            result = score == otherScore ? score + 1 : score + 2;
        }
    } else {
        result = (otherScore < score ? score : otherScore) + 8;
    }
    return result;
}

void Class_802A17A8::PlaceBallForDrive(int flip)
{
    if (!lbl_803EB2FC) {
        float distance = fn_80178A2C() * 2.0f -
                         ((lbl_803EB2FD / 2) * 10.0f + 18.0f);
        if (!(distance >= 1.0f)) {
            distance = 1.0f;
        }
        fn_80178E88(distance);
        lbl_803EB2FC = 1;
        ++lbl_803EB2FD;
    }
    ScrmRuleSet::PlaceBallForDrive(flip);
}

int Class_802A17A8::GetWinner()
{
    return mUnknown4;
}

void Class_802A17A8::AwardWin(int team)
{
    mUnknown4 = team;
}

int Class_802A17A8::IsNearWin(int team)
{
    return 1;
}

void Class_802A17A8::ResetPlaySpot()
{
    int a = 1;
    Object_8017886C *o = fn_8017886C();
    if (fn_80178348() == fn_80178308()) {
        a = 0;
    }
    unsigned int score0 = fn_801787DC(0);
    unsigned int score1 = fn_801787DC(1);
    unsigned short flags = fn_80178E94();
    lbl_803EB2FC = 0;
    ScrmRuleSet::ResetPlaySpot();
    if (mUnknown4 == 2) {
        if (o->mUnknown1D == -2) {
            int team = fn_80178320();
            if ((team == 0 && score0 > score1) || (team == 1 && score0 < score1)) {
                mUnknown4 = team;
            }
        } else if (o->mUnknown1D > 0) {
            int team = fn_80178308();
            if (a) {
                if ((team == 0 && score0 > score1) || (team == 1 && score0 < score1)) {
                    mUnknown4 = team;
                }
            } else if (flags & 1) {
                if (team == 0) {
                    if (score0 > score1) {
                        mUnknown4 = 0;
                    } else if (o->mUnknown1D != 6 && score0 < score1) {
                        mUnknown4 = 1;
                    }
                } else {
                    if (score0 < score1) {
                        mUnknown4 = 1;
                    } else if (o->mUnknown1D != 6 && score0 > score1) {
                        mUnknown4 = 0;
                    }
                }
            }
        } else if ((a && (flags & 1) == 0) || ((o->mUnknown18 & 4) && (flags & 1))) {
            if (score0 > score1) {
                mUnknown4 = 0;
            } else if (score0 < score1) {
                mUnknown4 = 1;
            }
        }
        if (mUnknown4 != 2 && fn_80177F70() == 6) {
            fn_80177F88(1);
        }
    }
    if (a && fn_80177F70() == 1) {
        fn_80178CD8(1);
    } else if (o->mUnknown18 & 0x900) {
        fn_80178CD8(0);
    }
}

void Class_802A17A8::ResetGame(int team)
{
    ScrmRuleSet::ResetGame(team);
    mUnknown4 = 2;
    fn_80155D7C(fn_80148A58());
}

void Class_802A18C8::OnEnter(float dt)
{
    fn_80178E88(fn_80178A2C() * 2.0f - 18.0f);
    PreGamePhase::OnEnter(dt);
    fn_80178A20(fn_80178A2C() * 2.0f);
    fn_80155D7C(fn_80148A58());
    lbl_803EB2FC = lbl_803EB2FD = 0;
    TutorialReleasePause();
}

void Class_802A18C8::OnUpdate(float dt)
{
    if (MsgBoxIsClosed()) {
        PreGamePhase::OnUpdate(dt);
    }
}

void Class_802A18C8::ShowIntroScreen()
{
    if (fn_800C1E40() == 0) {
        MsgBoxShow("Quick Strike", lbl_803EB2F8, "|^Done");
    }
}

void Class_802A18C8::HideIntroScreen()
{
}

extern "C" {

void fn_801556D0(unsigned int kind, int value, int flag)
{
    int team = fn_80178348();

    if (kind <= 1 || kind == 6 || kind == 7 || kind == 5 || kind == 8) {
        fn_80155A7C(fn_80148A58(), team, kind, value);
    } else if (kind >= 2 && kind <= 4) {
        fn_80155BF4(fn_80148A58(), team, kind, value, flag);
    }
}

} /* extern "C" */

void Class_802A1860::vfn_03(float dt)
{
    fn_8021D7B8(gUISMainInfo, 0x8000003A, 0, 0);
    fn_80148A58()->vfn_12();
    Class_80297B90::vfn_03(dt);
}

void Class_802A1860::vfn_08()
{
    PauseOpenScreen(3, 25, -1);
}

void Class_802A1860::vfn_09()
{
    fn_8021956C(gUISMainInfo, 3, 25, 1);
}

void Class_802A2A40::vfn_01()
{
    mpUnknown1C = new (0) Block_80156400;
    mpUnknown1C->mUnknown188 = 2;
    mpUnknown1C->mUnknown189[0] = 0;
    mpUnknown1C->mUnknown189[1] = 0;
    mpUnknown1C->mUnknown16 = GameOptionsGet(14);
    if (mpUnknown1C->mUnknown16 != 0) {
        GameOptionsSet(14, 0);
    }
    fn_800BC51C(&mpUnknown1C->mObject0);
    fn_800AACB8(&mpUnknown1C->mObject12);
    fn_8017CAC0(fn_801556D0);
    mpUnknown1C->mObject4.ResetGame(2);
    fn_80178F20(&mpUnknown1C->mObject4);
}

void Class_802A2A40::vfn_02()
{
    fn_800BC51C(0);
    fn_800AACB8(0);
    if (mpUnknown1C->mUnknown16 != 0) {
        GameOptionsSet(14, mpUnknown1C->mUnknown16);
    }
    fn_80178F20(0);
    fn_8017CAC0(0);
    delete mpUnknown1C;
    mpUnknown1C = 0;
}

int Class_802A2A40::vfn_08(int a)
{
    int result = 0;

    if (a && fn_80177F70() == 6) {
        unsigned int first = fn_801787DC(fn_80178308());
        unsigned int second = fn_801787DC(fn_80178320());

        if (first < second) {
            if (second - first > 1) {
                result = 2;
            } else {
                result = SyncRandGetFloat(0) <= 0.5f ? 1 : 2;
            }
        } else if (first > second) {
            result = SyncRandGetFloat(0) <= 0.5f ? 1 : 2;
        } else {
            result = SyncRandGetFloat(0) <= 0.7f ? 1 : 2;
        }
    }
    return result;
}

extern "C" {

void fn_80155A7C(Class_80148A58 *p, unsigned char team, int kind, int value)
{
    unsigned char i;

    if (static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][0].mEvent <= 1
        && static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][0].mConversion == 9
        && (kind == 6 || kind == 7)) {
        return;
    }
    if (static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown188 != team) {
        for (i = 2; i != 0; i--) {
            if (static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i - 1].mEvent != 11) {
                static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i].mOrdinal = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i - 1].mOrdinal;
                static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i].mEvent = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i - 1].mEvent;
                static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i].mPlayer = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i - 1].mPlayer;
                static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i].mConversion = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i - 1].mConversion;
                static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i].mOther = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i - 1].mOther;
                static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i].mFlag = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i - 1].mFlag;
            }
        }
        static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown188 = team;
        static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown189[team]++;
    }
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][0].mOrdinal = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown189[team];
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][0].mEvent = kind;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][0].mPlayer = value;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][0].mConversion = 9;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][0].mOther = 32767;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][0].mFlag = 0;
}

void fn_80155BF4(Class_80148A58 *p, unsigned char team, int kind, int value, int flag)
{
    if (static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][0].mConversion != 9 && kind == 2) {
        flag = 1;
    }
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][0].mConversion = kind;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][0].mOther = value;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][0].mFlag = flag;
}

void fn_80155C44(Class_80148A58 *p, int team, int index, Record_8005CE10 *pOut)
{
    unsigned char count = fn_80155D38(p, team);
    int depth = index + 1;
    int slot = count - depth;

    pOut->mOrdinal = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][slot].mOrdinal;
    pOut->mEvent = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][slot].mEvent;
    pOut->mPlayer = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][slot].mPlayer;
    pOut->mConversion = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][slot].mConversion;
    pOut->mOther = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][slot].mOther;
    pOut->mFlag = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][slot].mFlag;
}

void fn_80155CF0(Class_80148A58 *p, int team, int *pFirst, int *pSecond)
{
    *pFirst = fn_800C8744(team);
    *pSecond = fn_801787DC(team);
}

unsigned char fn_80155D38(Class_80148A58 *p, int team)
{
    Block_80156400 *pBlock = static_cast<Class_802A2A40 *>(p)->mpUnknown1C;
    unsigned char count = 0;
    unsigned char i;

    for (i = 0; i <= 2; i++) {
        if (pBlock->mRecords[team][i].mEvent != 11) {
            count++;
        }
    }
    return count;
}

void fn_80155D7C(Class_80148A58 *p)
{
    unsigned char team;
    unsigned char i;

    for (team = 0; team <= 1; team++) {
        for (i = 0; i <= 2; i++) {
            static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i].mOrdinal = 0;
            static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i].mEvent = 11;
            static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i].mPlayer = 32767;
            static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i].mConversion = 11;
            static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i].mOther = 32767;
            static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mRecords[team][i].mFlag = 0;
        }
    }
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown188 = 2;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown189[0] = 0;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown189[1] = 0;
}

} /* extern "C" */

Class_802A2C90 lbl_8031BD10;
Class_802A2DB8 lbl_8031BD34;
Class_802A2B68 lbl_8031BD54;
Class_802A2A40 lbl_8031BD74;
Class_802A27F0 lbl_8031BD94;
Class_80148A58 *lbl_8031BDBC[6] = {&(Class_80148A58 &)lbl_8031BD54, &(Class_80148A58 &)lbl_8031BDD4, &(Class_80148A58 &)lbl_8031BD94, &(Class_80148A58 &)lbl_8031BD34, &(Class_80148A58 &)lbl_8031BD10, &(Class_80148A58 &)lbl_8031BD74};
Class_802A2918 lbl_8031BDD4;
int lbl_8031BE04[14][3];
unsigned char lbl_8031BEAC[54];
int lbl_803ECA24[2];
