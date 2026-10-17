struct Entry_8015005C {
    int mUnknown0;
    unsigned int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknown10;
    char mUnknown12[8];
};

struct Table_8015005C {
    Entry_8015005C mEntries[5];
    char mUnknown100[17];
    unsigned char mUnknown117;
    unsigned char mCount;
    char mUnknown119[6];
    unsigned char mUnknown125;
};

struct Object_8015005C {
    char mUnknown0[36];
    Table_8015005C *mpUnknown36;
};

struct Settings_8031BDD4 {
    char mUnknown0[32];
    int mUnknown32;
    int mUnknown36;
    int mUnknown40;
};

extern "C" {
extern Settings_8031BDD4 lbl_8031BDD4;

Table_8015005C *fn_801530FC(void);
void fn_8009D964(int index, int value);
void fn_80151CCC(Settings_8031BDD4 *p, unsigned int index, int value);
void fn_801526EC(Settings_8031BDD4 *p);
void fn_80177768(void *p, int team);
void fn_801777FC(void *p);
void fn_801502B4(void *p);

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

unsigned char fn_801501CC(void *p)
{
    return fn_801530FC()->mUnknown125;
}

void fn_801501F0(void *p, unsigned char value)
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
    fn_801502B4(p);
}

void fn_8015034C(void *p)
{
    fn_80177768(p, 2);
    fn_801526EC(&lbl_8031BDD4);
}

void fn_8015037C(void *p)
{
    if (fn_801530FC()->mUnknown117) {
        fn_801777FC(p);
    }
}
}
