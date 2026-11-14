/* Formation sets of a loaded play: finds each player's entry (start spot, facing and
   order) for a named set such as "Norm", and steps through the players in order. */

#include <string.h>
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include <string.h>
#include "game/PlaySet.h"
#include "game/PlayBookGetPlay.h"
#include "game/fn_80178D18.h"

extern "C" {

int fn_80178308(void);
int fn_80178320(void);

int PlaySetFindRow(PlayBookFormation_t *pObject, int index, const char **ppNames);

/* Returns a pointer to entry index of row 0, first swapping into row 0 the
   entry of the row that ppNames selects. */
PlayBookPosition_t *PlaySetGetEntry(PlayBookFormation_t *pObject, unsigned int index, const char **ppNames)
{
    if (index > 6) {
        index = 0;
    }
    if (ppNames) {
        int row = PlaySetFindRow(pObject, index, ppNames);

        if (row != -1 && row != 0) {
            PlayBookPosition_t entry = pObject->mUnknown8.mUnknown84[row][index];

            pObject->mUnknown8.mUnknown84[row][index] = pObject->mUnknown8.mUnknown84[0][index];
            pObject->mUnknown8.mUnknown84[0][index] = entry;
        }
    }
    return &pObject->mUnknown8.mUnknown84[0][index];
}

void PlaySetSwapRow(PlayBookFormation_t *pObject, int row, int index)
{
    PlayBookPosition_t entry = pObject->mUnknown8.mUnknown84[row][index];

    pObject->mUnknown8.mUnknown84[row][index] = pObject->mUnknown8.mUnknown84[0][index];
    pObject->mUnknown8.mUnknown84[0][index] = entry;
}

/* Looks the names of the null-terminated list ppNames up in the name table
   and returns the first row whose entry index carries the id of a name found
   there, or -1. */
int PlaySetFindRow(PlayBookFormation_t *pObject, int index, const char **ppNames)
{
    int row = 0;
    int i = 0;
    int found = 0;
    int j;

    if (ppNames && ppNames[0]) {
        do {
            for (j = 0; j <= 12; j++) {
                if (strcmp(pObject->mUnknown8.mUnknown1C[j].mName, ppNames[i]) == 0) {
                    unsigned short id = pObject->mUnknown8.mUnknown1C[j].mId;

                    for (row = 0; row <= 10; row++) {
                        if (pObject->mUnknown8.mUnknown84[row][index].mUnknown6 == id) {
                            found = 1;
                            break;
                        }
                    }
                    break;
                }
            }
            i++;
        } while (ppNames[i] && found != 1);
    }
    return found == 1 ? row : -1;
}

/* Returns the index of the entry whose mUnknown8 follows that of entry
   index, wrapping to 1 after the team's player count. */
int PlaySetGetNextOrder(PlayBookFormation_t *pObject, unsigned char index)
{
    unsigned int count;
    unsigned char next;
    unsigned char i;
    PlayBookPosition_t *pEntry;

    if (pObject->mUnknown4) {
        count = fn_80178D70(fn_80178308());
    } else {
        count = fn_80178D70(fn_80178320());
    }
    pEntry = &pObject->mUnknown8.mUnknown84[0][index];
    next = pEntry->mUnknown8 + 1;
    if (next > count) {
        next = 1;
    }
    for (i = 0; i < count; i++) {
        pEntry = &pObject->mUnknown8.mUnknown84[0][i];
        if (pEntry->mUnknown8 == next) {
            break;
        }
    }
    return i;
}

/* As PlaySetGetNextOrder, stepping back and wrapping to the player count. */
int PlaySetGetPrevOrder(PlayBookFormation_t *pObject, unsigned char index)
{
    unsigned int count;
    unsigned char previous;
    unsigned char i;
    PlayBookPosition_t *pEntry;

    if (pObject->mUnknown4) {
        count = fn_80178D70(fn_80178308());
    } else {
        count = fn_80178D70(fn_80178320());
    }
    pEntry = &pObject->mUnknown8.mUnknown84[0][index];
    if (pEntry->mUnknown8 > 1) {
        previous = pEntry->mUnknown8 - 1;
    } else {
        previous = count;
    }
    for (i = 0; i < count; i++) {
        pEntry = &pObject->mUnknown8.mUnknown84[0][i];
        if (pEntry->mUnknown8 == previous) {
            break;
        }
    }
    return i;
}

void PlaySetGetEntryRoles(PlayBookFormation_t *pObject, unsigned char index, unsigned char *pA, unsigned char *pB)
{
    *pA = pObject->mUnknown8.mUnknown84[0][index].mUnknown0;
    *pB = pObject->mUnknown8.mUnknown84[0][index].mUnknown3;
}

Object_80039F5C *PlaySetGetKeyPlayer(PlayBookFormation_t *pObject)
{
    if (PlayBookGetPlay(fn_80178308())->mUnknown18 & 0x20000) {
        return PlyrGet(fn_80178308(), 1);
    }
    return PlyrGet(fn_80178308(), pObject->mUnknown8.mUnknownE);
}

void PlaySetPointToRoleMate(Object_80039F5C *p)
{
    Message_800F01CC msg;
    int post = 0;

    memset(&msg, 0, 4);
    msg.mId = 84;
    if (p->mUnknown2914 == 0) {
        int i;
        int count = fn_80178D70(p->mIdBytes[2]);

        for (i = 0; i < count; i++) {
            Object_80039F5C *pOther = PlyrGet(p->mIdBytes[2], i);

            if (pOther->mUnknown2914 == 7 || pOther->mUnknown2914 == 24) {
                msg.mUnknown1[0] = i;
                msg.mUnknown1[1] = 18;
                msg.mUnknown1[2] = 1;
                post = 1;
            }
        }
    }
    if (post) {
        fn_800F03D8(0, p->mpState, &msg, p);
    }
}
}
