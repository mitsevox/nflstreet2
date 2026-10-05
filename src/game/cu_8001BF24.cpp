#include "game/Class_80148A58.h"
#include "game/Object_8007A334.h"
#include "game/cu_80181330.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"

struct Toggle_8001BF24 {
    int mValue;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mUnknown6;
    int mUnknown8;
};

struct Option_8001BF24 {
    char **mppItems;
    unsigned char mUnknown4;
    unsigned char mUnknown5;
    unsigned char mCount;
    unsigned char mSelection;
    char mName[13];
    char mDescription[71];
};

struct State_8001BF24 {
    Toggle_8001BF24 mToggles[4];
    Option_8001BF24 mOptions[3];
    unsigned char mUnknown324;
    unsigned char mUnknown325;
};

struct Settings_8031BDD4 {
    char mUnknown0[32];
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
};

extern "C" {
void fn_8001B260(int a, int b);
void fn_8001B330(int a);
void fn_8001B828(void);
void fn_8007AEE8(Object_8007A334 *pObject);
void fn_8007AF14(Object_8007A334 *pObject);
unsigned char fn_8007AFDC(int a);
int fn_80082414(int index);
int fn_801486A0(void);
void fn_8014F3DC(int ticks);
int fn_801801B4(void);
void fn_8018C230(int a, int b);
void fn_8018C48C(int handle);
void fn_8018D7E0(void);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
char *fn_801C3084(const char *pString, int c);

extern Settings_8031BDD4 lbl_8031BDD4;
extern int lbl_802A11F4[];
extern char *lbl_803EB2E8;

void fn_8001C138(State_8001BF24 *pState);
void fn_8001CA3C(Option_8001BF24 *pOption, const char *pName, const char *pItems, const char *pDescription,
                 unsigned char flag);
}

static State_8001BF24 *lbl_803EBA58 = 0;
static int lbl_803EBA5C = 14;

extern "C" {
void fn_8001BF24(void)
{
    lbl_803EBA58->mToggles[0].mUnknown8 = fn_80082414(0);
    lbl_803EBA58->mToggles[1].mUnknown8 = fn_80082414(1);
    lbl_803EBA58->mToggles[2].mUnknown8 = fn_80082414(3);
    lbl_803EBA58->mToggles[3].mUnknown8 = fn_80082414(2);
}

void fn_8001BF80(State_8001BF24 *pState)
{
    int count;

    fn_8001CA3C(&pState->mOptions[0], 0, 0, 0, 0);
    fn_8001CA3C(&pState->mOptions[1], 0, 0, 0, 0);
    fn_8001CA3C(&pState->mOptions[2], 0, 0, 0, 0);
    count = 3;
    switch (fn_801486A0()) {
    case 1:
        fn_8001CA3C(&pState->mOptions[0], "Game Type", "Single Round|^Elimination",
                    "Play a single round or multiple rounds with Elimination.", 0);
        fn_8001CA3C(&pState->mOptions[1], "Play To", lbl_803EB2E8,
                    "Select the length of the Street Event, or play to score.", 0);
        lbl_803EBA5C = 7;
        break;
    case 0:
        fn_8001CA3C(&pState->mOptions[0], "Timer", "3 Minutes|^5 Minutes|8 Minutes|10 Minutes",
                    "Select the Length of the Street Event.", 0);
        count = 2;
        lbl_803EBA5C = 6;
        break;
    case 2:
        fn_8001CA3C(&pState->mOptions[0], "Game Type",
                    (pState->mUnknown324 <= 1 && pState->mUnknown325 <= 1) ? "2 on 2|^1 on 1" : "2 on 2",
                    "Select the Game Type for the Street Event.", 0);
        fn_8001CA3C(&pState->mOptions[1], "Rounds", "5 Rounds|^10 Rounds|15 Rounds|20 Rounds",
                    "Select the Number of Rounds for the Street Event.", 0);
        lbl_803EBA5C = 2;
        break;
    case 3:
    case 4:
        break;
    }
    fn_8001CA3C(&pState->mOptions[count - 1], "Player Count", "^40 Random|All Players",
                "Choose the number of players to put in the pool.", 0);
}

void fn_8001C138(State_8001BF24 *pState)
{
    unsigned char i;
    unsigned char j;

    for (i = 0; i <= 2; i++) {
        if (pState->mOptions[i].mCount != 0) {
            for (j = 0; j < pState->mOptions[i].mCount; j++) {
                fn_801D2BD0(pState->mOptions[i].mppItems[j]);
            }
            fn_801D2BD0(pState->mOptions[i].mppItems);
        }
    }
}

void fn_8001C1D0(State_8001BF24 *pState)
{
    pState->mToggles[0].mValue = 1;
    pState->mToggles[1].mValue = 2;
    pState->mToggles[2].mValue = 8;
    pState->mToggles[3].mValue = 4;
    pState->mToggles[0].mUnknown5 = 1;
    pState->mToggles[1].mUnknown5 = 1;
    pState->mToggles[2].mUnknown5 = 1;
    pState->mToggles[3].mUnknown5 = 0;
    pState->mToggles[0].mUnknown4 = 1;
    pState->mToggles[1].mUnknown4 = 0;
    pState->mToggles[2].mUnknown4 = 0;
    pState->mToggles[3].mUnknown4 = 0;
    if (lbl_803EBA58->mToggles[0].mUnknown8 != 0) {
        lbl_803EBA58->mToggles[0].mUnknown6 = 0;
    } else {
        lbl_803EBA58->mToggles[0].mUnknown6 = 1;
        lbl_803EBA58->mToggles[0].mUnknown4 = 0;
    }
    if (lbl_803EBA58->mToggles[1].mUnknown8 != 0) {
        lbl_803EBA58->mToggles[1].mUnknown6 = 0;
    } else {
        lbl_803EBA58->mToggles[1].mUnknown6 = 1;
        lbl_803EBA58->mToggles[1].mUnknown4 = 0;
    }
    if (lbl_803EBA58->mToggles[2].mUnknown8 != 0) {
        lbl_803EBA58->mToggles[2].mUnknown6 = 0;
    } else {
        lbl_803EBA58->mToggles[2].mUnknown6 = 1;
        lbl_803EBA58->mToggles[2].mUnknown4 = 0;
    }
}

void fn_8001C294(State_8001BF24 *pState)
{
    switch (fn_801486A0()) {
    case 1:
    {
        unsigned char index;

        switch (pState->mOptions[0].mSelection) {
        case 0:
            lbl_8031BDD4.mUnknown40 = 0;
            break;
        case 1:
            lbl_8031BDD4.mUnknown40 = 1;
            break;
        }
        index = pState->mOptions[1].mSelection;
        if (index <= 14) {
            lbl_8031BDD4.mUnknown32 = lbl_802A11F4[index];
            lbl_8031BDD4.mUnknown36 = 0;
        } else {
            lbl_8031BDD4.mUnknown36 = lbl_802A11F4[index];
            lbl_8031BDD4.mUnknown32 = 0;
        }
        break;
    }
    case 0:
    {
        int minutes = 0;

        switch (pState->mOptions[0].mSelection) {
        case 0:
            minutes = 3;
            break;
        case 1:
            minutes = 5;
            break;
        case 2:
            minutes = 8;
            break;
        case 3:
            minutes = 10;
            break;
        }
        fn_8014F3DC(minutes * 60);
        break;
    }
    case 2:
    {
        int rounds = 5;
        int type = pState->mOptions[0].mSelection;

        switch (pState->mOptions[1].mSelection) {
        case 0:
            break;
        case 1:
            rounds = 10;
            break;
        case 2:
            rounds = 15;
            break;
        case 3:
            rounds = 20;
            break;
        }
        fn_80148A58()->vfn_07(0, type);
        fn_80148A58()->vfn_07(1, rounds);
        break;
    }
    case 3:
    case 4:
        break;
    }
    fn_8001C138(pState);
}

void fn_8001C440(void)
{
    lbl_803EBA58 = (State_8001BF24 *)fn_801D2B7C(sizeof(State_8001BF24), 0, 0);
    fn_801C1F94(lbl_803EBA58, 0, sizeof(State_8001BF24));
    fn_8018D7E0();
    fn_8018C230(0, 1);
    {
        Object_8007A334 object;

        fn_8007AEE8(&object);
        lbl_803EBA58->mUnknown324 = fn_8007AFDC(0);
        lbl_803EBA58->mUnknown325 = fn_8007AFDC(1);
        fn_8007AF14(&object);
    }
    lbl_803EBA5C = 14;
    fn_8001BF24();
    fn_8001C1D0(lbl_803EBA58);
    fn_8001BF80(lbl_803EBA58);
}

void fn_8001C504(void)
{
    int mask = 0;
    int count = 3;
    int mode;
    int i;

    for (i = 0; i < 4; i++) {
        if (lbl_803EBA58->mToggles[i].mUnknown4 != 0) {
            mask |= lbl_803EBA58->mToggles[i].mValue;
        }
    }
    if (fn_801486A0() == 0) {
        count = 2;
    }
    mode = 0;
    if (lbl_803EBA58->mOptions[count - 1].mSelection != 0) {
        mode = lbl_803EBA58->mOptions[count - 1].mSelection == 1 ? 2 : 0;
    }
    fn_8001B330(mask);
    fn_8001B260(mode, lbl_803EBA5C);
    fn_8001B828();
    fn_8001C294(lbl_803EBA58);
    if (fn_801801B4() == 0) {
        fn_8018C48C(0x54415453);
    }
    fn_801D2BD0(lbl_803EBA58);
    lbl_803EBA58 = 0;
}

void fn_8001C5EC(int index, int *pEnabled, Arg_8018399C text, int *pState)
{
    int selectable = 1;

    if (index >= 1 && index <= 3) {
        *pEnabled = lbl_803EBA58->mOptions[index - 1].mUnknown5;
        if (lbl_803EBA58->mOptions[index - 1].mUnknown5 != 0) {
            fn_801C2EF0(text.pParams->mpText, lbl_803EBA58->mOptions[index - 1].mName, text.pParams->mLength);
        }
        selectable = lbl_803EBA58->mOptions[index - 1].mCount > 1;
    } else if (index >= 4 && index <= 7) {
        *pEnabled = lbl_803EBA58->mToggles[index - 4].mUnknown5;
        if (lbl_803EBA58->mToggles[index - 4].mUnknown5 != 0) {
            const char *pName = index == 4   ? "NFL Players"
                                : index == 5 ? "NFL Legends"
                                : index == 6 ? "Created"
                                : index == 7 ? "Randomized"
                                             : "Unknown";

            fn_801C2EF0(text.pParams->mpText, pName, text.pParams->mLength);
        }
    }
    *pState = 0;
    if (!selectable || (index >= 4 && index <= 7 && lbl_803EBA58->mToggles[index - 4].mUnknown6 != 0)) {
        *pState = 2;
    }
}

int fn_8001C75C(int index, int direction, Arg_8018399C text)
{
    int changed = 0;
    Params_80005284 *pText = text.pParams;

    if (index >= 1 && index <= 3 ? lbl_803EBA58->mOptions[index - 1].mUnknown5 != 0
                                 : index >= 4 && index <= 7 && lbl_803EBA58->mToggles[index - 4].mUnknown5 != 0) {
        switch (direction) {
        case 0:
            break;
        case 3:
            if (index >= 1 && index <= 3) {
                if (lbl_803EBA58->mOptions[index - 1].mSelection == 0) {
                    lbl_803EBA58->mOptions[index - 1].mSelection = lbl_803EBA58->mOptions[index - 1].mCount - 1;
                } else {
                    lbl_803EBA58->mOptions[index - 1].mSelection--;
                }
            } else if (index >= 4 && index <= 7) {
                lbl_803EBA58->mToggles[index - 4].mUnknown4 = !lbl_803EBA58->mToggles[index - 4].mUnknown4;
            }
            break;
        case 1:
            if (index >= 1 && index <= 3) {
                if (lbl_803EBA58->mOptions[index - 1].mSelection == lbl_803EBA58->mOptions[index - 1].mCount - 1) {
                    lbl_803EBA58->mOptions[index - 1].mSelection = 0;
                } else {
                    lbl_803EBA58->mOptions[index - 1].mSelection++;
                }
            } else if (index >= 4 && index <= 7) {
                lbl_803EBA58->mToggles[index - 4].mUnknown4 = !lbl_803EBA58->mToggles[index - 4].mUnknown4;
            }
            break;
        }
        if (index >= 1 && index <= 3) {
            if (lbl_803EBA58->mOptions[index - 1].mUnknown4 != 0) {
                fn_8001C138(lbl_803EBA58);
                changed = 1;
                fn_8001BF80(lbl_803EBA58);
            }
            fn_801C2EF0(pText->mpText, lbl_803EBA58->mOptions[index - 1].mppItems[lbl_803EBA58->mOptions[index - 1].mSelection],
                        pText->mLength);
            if (fn_801486A0() == 2 && index == 1) {
                switch (lbl_803EBA58->mOptions[0].mSelection) {
                case 0:
                    lbl_803EBA5C = 4;
                    break;
                case 1:
                    lbl_803EBA5C = 2;
                    break;
                }
            }
        } else if (index >= 4 && index <= 7) {
            const char *pValue = lbl_803EBA58->mToggles[index - 4].mUnknown4 ? "On" : "Off";

            fn_801C2EF0(pText->mpText, pValue, pText->mLength);
        }
    }
    return changed;
}

void fn_8001C980(int index, Arg_8018399C text)
{
    if (index >= 1 && index <= 3) {
        fn_801C2EF0(text.pParams->mpText, lbl_803EBA58->mOptions[index - 1].mDescription, text.pParams->mLength);
    } else if (index >= 4 && index <= 7) {
        const char *pDescription = index == 4   ? "Allow/Disallow NFL Players in the Selection Pool."
                                   : index == 5 ? "Allow/Disallow NFL Legends in the Selection Pool."
                                   : index == 6 ? "Allow/Disallow Created Players in the Selection Pool."
                                   : index == 7 ? "Allow/Disallow Randomly Generated Characters in the Selection Pool."
                                                : "";

        fn_801C2EF0(text.pParams->mpText, pDescription, text.pParams->mLength);
    }
}

void fn_8001CA3C(Option_8001BF24 *pOption, const char *pName, const char *pItems, const char *pDescription,
                 unsigned char flag)
{
    if (pName != 0) {
        fn_801C2EF0(pOption->mName, pName, 12);
    } else {
        pOption->mName[0] = 0;
    }
    if (pName != 0) {
        fn_801C2EF0(pOption->mDescription, pDescription, 70);
    } else {
        pOption->mDescription[0] = 0;
    }
    pOption->mCount = 0;
    if (pItems != 0 && *pItems != 0) {
        const char *p;
        unsigned char i;

        pOption->mSelection = 0;
        pOption->mCount = 1;
        for (p = pItems; *p != 0; p++) {
            if (*p == '|') {
                pOption->mCount++;
            }
        }
        pOption->mppItems = (char **)fn_801D2B7C(pOption->mCount * 4, 0, 0);
        p = pItems;
        for (i = 0; i < pOption->mCount; i++) {
            char *pBar;

            pOption->mppItems[i] = (char *)fn_801D2B7C(14, 0, 0);
            if (*p == '^') {
                pOption->mSelection = i;
                p++;
            }
            fn_801C2EF0(pOption->mppItems[i], p, 13);
            pBar = fn_801C3084(pOption->mppItems[i], '|');
            if (pBar != 0) {
                *pBar = 0;
            }
            p = fn_801C3084(p + 1, '|') + 1;
        }
    } else {
        pOption->mUnknown5 = 0;
        pOption->mSelection = 0;
    }
    pOption->mUnknown5 = pOption->mCount != 0;
    pOption->mUnknown4 = flag;
}

int fn_8001CBE8(void)
{
    unsigned int total;
    int count = 3;

    if (fn_801486A0() == 0) {
        count = 2;
    }
    total = 0;
    if (lbl_803EBA58->mToggles[0].mUnknown4 != 0) {
        total = lbl_803EBA58->mToggles[0].mUnknown8;
    }
    if (lbl_803EBA58->mToggles[1].mUnknown4 != 0) {
        total += lbl_803EBA58->mToggles[1].mUnknown8;
    }
    if (lbl_803EBA58->mToggles[2].mUnknown4 != 0) {
        total += lbl_803EBA58->mToggles[2].mUnknown8;
    }
    if (lbl_803EBA58->mToggles[3].mUnknown4 != 0) {
        total += lbl_803EBA58->mToggles[3].mUnknown8;
    }
    switch (lbl_803EBA58->mOptions[count - 1].mSelection) {
    case 1:
        total = total >= lbl_803EBA5C;
        break;
    case 0:
    default:
        total = total >= 40;
        break;
    }
    return total;
}

int fn_8001CCB4(unsigned int id, Arg_8018399C *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        fn_8001C440();
        break;
    case 0x80000002:
        fn_8001C504();
        break;
    case 0x80000003:
        fn_8001C5EC(pArgs[0].i, pArgs[1].pi, pArgs[2], pArgs[3].pi);
        break;
    case 0x80000004:
        *pResult = fn_8001C75C(pArgs[0].i, pArgs[1].i, pArgs[2]);
        break;
    case 0x80000005:
        fn_8001C980(pArgs[0].i, pArgs[1]);
        break;
    case 0x80000006:
        *pResult = fn_8001CBE8();
        break;
    default:
        return 0;
    }
    return 1;
}
}
