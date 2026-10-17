#include "game/Class_80148A58.h"

struct Entry_80155C44 {
    int mUnknown0;
    unsigned int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    char mUnknown21[7];
};

struct Block_80155C44 {
    char mUnknown0[20];
    Entry_80155C44 mEntries[2][3];
    unsigned char mUnknown188;
    unsigned char mUnknown189[2];
};

class Class_802A2A40 : public Class_80148A58 {
public:
    Block_80155C44 *mpUnknown1C;
};

extern "C" {
int fn_800C8744(int team);
int fn_801787DC(int team);
unsigned char fn_80155D38(Class_80148A58 *p, int team);

void fn_80155A7C(Class_80148A58 *p, unsigned char team, int kind, int value)
{
    unsigned char i;

    if (static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][0].mUnknown4 <= 1
        && static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][0].mUnknown12 == 9
        && (kind == 6 || kind == 7)) {
        return;
    }
    if (static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown188 != team) {
        for (i = 2; i != 0; i--) {
            if (static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i - 1].mUnknown4 != 11) {
                static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i].mUnknown0 = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i - 1].mUnknown0;
                static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i].mUnknown4 = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i - 1].mUnknown4;
                static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i].mUnknown8 = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i - 1].mUnknown8;
                static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i].mUnknown12 = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i - 1].mUnknown12;
                static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i].mUnknown16 = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i - 1].mUnknown16;
                static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i].mUnknown20 = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i - 1].mUnknown20;
            }
        }
        static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown188 = team;
        static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown189[team]++;
    }
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][0].mUnknown0 = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown189[team];
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][0].mUnknown4 = kind;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][0].mUnknown8 = value;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][0].mUnknown12 = 9;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][0].mUnknown16 = 32767;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][0].mUnknown20 = 0;
}

void fn_80155BF4(Class_80148A58 *p, unsigned char team, int kind, int value, int flag)
{
    if (static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][0].mUnknown12 != 9 && kind == 2) {
        flag = 1;
    }
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][0].mUnknown12 = kind;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][0].mUnknown16 = value;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][0].mUnknown20 = flag;
}

void fn_80155C44(Class_80148A58 *p, int team, int index, Entry_80155C44 *pOut)
{
    unsigned char count = fn_80155D38(p, team);
    int depth = index + 1;
    int slot = count - depth;

    pOut->mUnknown0 = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][slot].mUnknown0;
    pOut->mUnknown4 = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][slot].mUnknown4;
    pOut->mUnknown8 = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][slot].mUnknown8;
    pOut->mUnknown12 = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][slot].mUnknown12;
    pOut->mUnknown16 = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][slot].mUnknown16;
    pOut->mUnknown20 = static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][slot].mUnknown20;
}

void fn_80155CF0(Class_80148A58 *p, int team, int *pFirst, int *pSecond)
{
    *pFirst = fn_800C8744(team);
    *pSecond = fn_801787DC(team);
}

unsigned char fn_80155D38(Class_80148A58 *p, int team)
{
    Block_80155C44 *pBlock = static_cast<Class_802A2A40 *>(p)->mpUnknown1C;
    unsigned char count = 0;
    unsigned char i;

    for (i = 0; i <= 2; i++) {
        if (pBlock->mEntries[team][i].mUnknown4 != 11) {
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
            static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i].mUnknown0 = 0;
            static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i].mUnknown4 = 11;
            static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i].mUnknown8 = 32767;
            static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i].mUnknown12 = 11;
            static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i].mUnknown16 = 32767;
            static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mEntries[team][i].mUnknown20 = 0;
        }
    }
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown188 = 2;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown189[0] = 0;
    static_cast<Class_802A2A40 *>(p)->mpUnknown1C->mUnknown189[1] = 0;
}
}
