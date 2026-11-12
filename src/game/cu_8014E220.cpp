#include "game/Class_80148A58.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/GameCamera.h"
#include "game/cammain.h"
#include "game/Ball.h"

struct State_802A2058 {
    char mUnknown0[4];
    unsigned char mUnknown4;
};

struct Record_8014F104 {
    int mUnknown0;
    int mUnknown4;
    unsigned char mUnknown8;
    char mUnknown9[3];
    char mUnknown12[40];
    char mUnknown52[4];
};

struct Block_8014F104 {
    char mUnknown0[0x34];
    Record_8014F104 *mpUnknown34;
};

extern "C" {
extern char *lbl_803EB2D4;
extern const char lbl_802A0B74[];

int fn_800C1E40(void);
void MsgBoxShow(const char *pTitle, const char *pText, const char *pButtons);

Block_8014F104 *fn_8014F104(Class_80148A58 *p);
Object_80039F5C *fn_8003AC84(int id);
void fn_800AD910(int a, float b);
void fn_800BCC30(void *p);
void CamGameSetModeAll(int a);
void CamGameSelectCamera(int a);
GameCamera_t *CamGameGetCamera(int index);
void fn_80141164(float value);
void fn_8014D67C(void);
int MsgBoxIsClosed(void);
void fn_800BCB18(void *p, float dt);
void fn_800B6474(int index, unsigned char team);
void fn_800B6714(Object_80039F5C *p, int port);
void fn_800B6658(Object_80039F5C *p);
void fn_800BFB88(void *p, float dt);
void fn_80162780(int a, int b);
void fn_801487C0(int team, unsigned char begin);
float fn_80178A44(void);
void fn_801780A8(Point_8017886C pos);
void fn_8017833C(int value);
void CamGameSetFocusAll(int a, int b);
void PlayerMoveResetAll(void);
void fn_800B14E4(void);
void DivotRestartRecords(void);
void AudmonEventClear(void);
void ClockRuleSnap(void);
void fn_800C9FC0(void);
int fn_8005BFD4(void);
void fn_8005BF18(void);
void PauseUnblock(void);

void fn_8014E220(void *p, float dt)
{
    fn_800AD910(2, dt);
}

void fn_8014E244(void *p)
{
    fn_800BCC30(p);
    CamGameSetModeAll(1);
    CamGameSelectCamera(0);
    CamMainWarpToDest(CamGameGetCamera(5));
    fn_80141164(2.5f);
    fn_8014D67C();
}

void fn_8014E290(void *p, float dt)
{
    if (MsgBoxIsClosed()) {
        fn_800BCB18(p, dt);
    }
}

void fn_8014E31C(void)
{
    for (unsigned char i = 0; i <= 5; i++) {
        Object_80039F5C *pPlayer = fn_8003AC84(fn_8014F104(fn_80148A58())->mpUnknown34[i].mUnknown0);
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

void fn_8014E3B4(State_802A2058 *p, float dt)
{
    fn_800BFB88(p, dt);
    fn_80162780(1, 1);
    fn_801487C0(1, 1);
    fn_801487C0(0, 5);
    Point_8017886C pos = {0.0f, 0.0f};
    pos.mY = -fn_80178A44();
    fn_801780A8(pos);
    fn_8017833C(1);
    Object_80039F5C *pPlayer = fn_80039F5C(1, 0);
    if (pPlayer != BallGetCurrentHolder()) {
        BallGiveToPlayer(BallGetCurrent(), pPlayer);
        BallSetTransferKind(BallGetCurrent(), 0);
    }
    CamGameSetFocusAll(1, BallGetCurrentIndex());
    p->mUnknown4 = 1;
}

void fn_8014E48C(State_802A2058 *p, float dt)
{
    if (p->mUnknown4) {
        p->mUnknown4 = 0;
        PlayerMoveResetAll();
        fn_800B14E4();
        DivotRestartRecords();
        AudmonEventClear();
        ClockRuleSnap();
        fn_800C9FC0();
        fn_80148A58()->vfn_15();
    }
    if (fn_8005BFD4() == 3 || fn_8005BFD4() == 4) {
        if (fn_8005BFD4() != 4) {
            fn_8005BF18();
            PauseUnblock();
        }
        fn_800AD910(3, dt);
    }
}

void fn_8014E2DC(void *p)
{
    if (fn_800C1E40() == 0) {
        MsgBoxShow("Crush the Carrier", lbl_803EB2D4, lbl_802A0B74);
    }
}
}
