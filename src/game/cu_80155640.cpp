#include "game/PreGamePhase.h"

class Class_802A18C8 : public PreGamePhase {
};

extern "C" {
extern char *lbl_803EB2F8;
extern const char lbl_802A0B74[];

int fn_800C1E40(void);
void MsgBoxShow(const char *pTitle, const char *pText, const char *pButtons);
int MsgBoxIsClosed(void);

void fn_80155640(Class_802A18C8 *p, float dt)
{
    if (MsgBoxIsClosed()) {
        p->PreGamePhase::OnUpdate(dt);
    }
}

void fn_801556CC(Class_802A18C8 *p)
{
}

void fn_8015568C(Class_802A18C8 *p)
{
    if (fn_800C1E40() == 0) {
        MsgBoxShow("Quick Strike", lbl_803EB2F8, lbl_802A0B74);
    }
}
}
