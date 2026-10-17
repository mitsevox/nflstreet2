#include "game/Block_8030E6E8.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80163E94.h"

/* One of the 24 four-float boxes fn_8009E674 lays out at +0x18 of
   State_8011F4EC. */
struct Box_8009E674 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
};

/* Object whose address fn_8011F4EC returns. Only the accessed bytes are
   declared; the size is not established. */
struct State_8011F4EC {
    int mUnknown0;
    int mUnknown4[2];
    int mUnknownC;
    unsigned char mUnknown10;
    unsigned char mUnknown11;
    unsigned char mUnknown12[2];
    unsigned short mUnknown14;
    unsigned char mUnknown16[2];
    Box_8009E674 mUnknown18[24];
    unsigned char mUnknown198;
    unsigned char mUnknown199[3];
    unsigned char mUnknown19C[3];
    unsigned char mUnknown19F[3];
    unsigned char mUnknown1A2;
    unsigned char mUnknown1A3[5];
    unsigned char mUnknown1A8;
    unsigned char mUnknown1A9;
    unsigned char mUnknown1AA[2];
    float mUnknown1AC[3];
    unsigned char mUnknown1B8[3];
    unsigned char mUnknown1BB[3];
    unsigned char mUnknown1BE[3];
    unsigned char mUnknown1C1[3];
    unsigned char mUnknown1C4;
    unsigned char mUnknown1C5;
};

extern "C" {
int fn_80178308(void);
Object_800670B4 *fn_80168708(int team);
int fn_800B0F98(void);
int fn_8009DBB4(State_8011F4EC *p);
}

extern "C" int fn_8009DBB4(State_8011F4EC *p)
{
    int result = 0;
    int team = fn_80178308();
    unsigned char behind = 0;
    unsigned char ahead = 0;
    Object_800670B4 *pTeam = fn_80168708(team);
    unsigned char i = 0;
    float ballX = fn_80177FE0().mX;
    int carrierId = fn_800B0F98();

    do {
        Object_80039F5C *pObject = fn_80039F5C(team, p->mUnknown199[i]);
        Point_8017886C pos;

        if ((pObject->mFlags & 0x40000) || carrierId == pObject->mId) {
            pos.mX = pObject->mMotion.mPos.mX;
        } else {
            Entry_8006719C *pEntry = fn_80163E94(pTeam, p->mUnknown199[i], 0);

            pos.mX = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mX;
            pos.mY = (pTeam->mUnknown8.mUnknownF == 1 ? &pEntry->mUnknown18 : &pEntry->mUnknown10)->mY;
            pos.mX += ballX;
        }
        p->mUnknown1AC[i] = pos.mX;
        if (!(__builtin_fabsf(pos.mX - ballX) <= 0.5f)) {
            if (!(pos.mX < ballX)) {
                ahead++;
            } else {
                behind++;
            }
        }
        i++;
    } while (i <= 2);
    if (ahead >= behind) {
        result = 1;
    }
    return result;
}
