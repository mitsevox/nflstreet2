#include "game/Block_8030E6E8.h"
#include "game/fn_80177FE0.h"
#include "game/PlaySet.h"
#include "game/Item_80097440.h"

extern "C" {
int fn_80178308(void);
PlayBookFormation_t *PlayBookGetFormation(int team);
int fn_800B0F98(void);
int fn_8009DBB4(State_8011F4EC *p);
}

extern "C" int fn_8009DBB4(State_8011F4EC *p)
{
    int result = 0;
    int team = fn_80178308();
    unsigned char behind = 0;
    unsigned char ahead = 0;
    PlayBookFormation_t *pTeam = PlayBookGetFormation(team);
    unsigned char i = 0;
    float ballX = fn_80177FE0().mX;
    int carrierId = fn_800B0F98();

    do {
        Object_80039F5C *pObject = PlyrGet(team, p->mUnknown199[i]);
        Point_8017886C pos;

        if ((pObject->mFlags & 0x40000) || carrierId == pObject->mId) {
            pos.mX = pObject->mMotion.mPos.mX;
        } else {
            PlayBookPosition_t *pEntry = PlaySetGetEntry(pTeam, p->mUnknown199[i], 0);

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
