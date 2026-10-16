struct Entry_8015005C {
    int mUnknown0;
    int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknown10;
    int mUnknown12;
    int mUnknown16;
};

struct Table_8015005C {
    Entry_8015005C mEntries[5];
    char mUnknown100[18];
    unsigned char mCount;
};

struct Object_8015005C {
    char mUnknown0[36];
    Table_8015005C *mpUnknown36;
};

extern "C" {

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
}
