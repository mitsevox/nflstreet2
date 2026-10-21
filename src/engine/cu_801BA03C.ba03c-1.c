typedef struct Block_801BF3C8 {
    float mWeight;
    unsigned char mUnknown4[4];
    int mUnknown8;
    unsigned char mUnknownC[12];
} Block_801BF3C8;

typedef struct Block_801BD6D4 {
    void *mpUnknown0;
    float mUnknown4;
    float mUnknown8;
} Block_801BD6D4;

/* 124-byte channel record; the list header's mCount records follow each other. */
typedef struct Record_800D81C8 {
    unsigned char mUnknown0;
    unsigned char mStatus;
    short mUnknown2;
    unsigned short mUnknown4;
    unsigned char mUnknown6;
    unsigned char mFlags;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
    int mUnknownC;
    unsigned char mUnknown10[12];
    int mUnknown1C;
    int mUnknown20;
    float mUnknown24;
    float mUnknown28;
    float mUnknown2C;
    Block_801BF3C8 mUnknown30;
    float mUnknown48;
    Block_801BD6D4 mUnknown4C;
    unsigned char mUnknown58[8];
    float mUnknown60;
    unsigned short mUnknown64;
    unsigned short mUnknown66;
    unsigned char mUnknown68[2];
    unsigned char mUnknown6A;
    unsigned char mUnknown6B[17];
} Record_800D81C8;

typedef struct Object_801BA03C {
    unsigned short mUnknown0;
    unsigned char mUnknown2[2];
    unsigned short mCount;
    unsigned char mUnknown6[2];
    int mUnknown8;
} Object_801BA03C;

typedef struct Anim_801BAB34 {
    unsigned char mUnknown0[2];
    unsigned char mUnknown2;
} Anim_801BAB34;

int fn_801B9F00(Object_801BA03C *pList, Record_800D81C8 *pChannels);
void fn_801B9D84(int state);
void fn_801B9DA8(void *pUser);
void fn_801B9DCC(void);
void fn_801B9DDC(void);
void *fn_801BC084(int slot);
unsigned short fn_801BAB2C(void *pFile);
Anim_801BAB34 *fn_801BAB34(void *pFile, int anim);
unsigned short fn_801BAB48(void *pFile, int state);
int fn_801BD4C0(Block_801BD6D4 *pSeq, Anim_801BAB34 *pAnim);
int fn_801BD4E4(Block_801BD6D4 *pSeq, float time);
unsigned short fn_801BD6DC(void *pSeq);
void fn_801BD710(Block_801BD6D4 *pSeq, float rate);
void fn_801BF3C8(Block_801BF3C8 *pWeight, int a, int b, float x, float y);
void fn_801BF46C(Block_801BF3C8 *pWeight, float time);
float fn_80260260(float x, float y);

void fn_801BA360(Record_800D81C8 *pChannel, int a, int b, float x, float y);
void fn_801BA384(Object_801BA03C *pList, Record_800D81C8 *pChannels, int index);
int fn_801BA650(Record_800D81C8 *pChannel, float time, void *pUser);
int fn_801BA720(Record_800D81C8 *pChannel, Anim_801BAB34 *pAnim, void *pUser);

void fn_801BA03C(Object_801BA03C *pList, Record_800D81C8 *pChannels, float time, void *pUser)
{
    int i;
    int active;

    for (i = 0; i < pList->mCount; i++) {
        if (pChannels[i].mStatus == 1)
            pChannels[i].mStatus = 0;
        if (pChannels[i].mStatus != 0) {
            pChannels[i].mUnknown48 -= time;
            if (!(pChannels[i].mUnknown48 >= 0.0f)) {
                pChannels[i].mUnknown48 = 0.0f;
                active = pChannels[i].mUnknown30.mUnknown8;
                fn_801BF46C(&pChannels[i].mUnknown30, time);
                if (!(pChannels[i].mUnknown30.mWeight >= 1e-7f) && active != 0)
                    pChannels[i].mStatus = 1;
                if (pChannels[i].mStatus != 0 && fn_801BA650(&pChannels[i], time, pUser) == 1)
                    pChannels[i].mStatus = 1;
            }
        }
    }
}

int fn_801BA154(Object_801BA03C *pList, Record_800D81C8 *pChannels, int slot, int anim, float weight, int state,
                void *pUser, unsigned short stateRef)
{
    int index = fn_801B9F00(pList, pChannels);

    if (index != -1) {
        fn_801BA360(&pChannels[index], 0, 0, weight, weight);
        pChannels[index].mUnknown4 = fn_801BAB2C(fn_801BC084(slot));
        pChannels[index].mUnknown6 = slot;
        pChannels[index].mUnknown2 = anim;
        pChannels[index].mUnknown8 = state;
        if (stateRef != 0xFFFF)
            pChannels[index].mUnknownA = fn_801BAB48(fn_801BC084(pChannels[index].mUnknown6), stateRef);
        else if (!(state & 0x8000))
            pChannels[index].mUnknownA = fn_801BAB48(fn_801BC084(pChannels[index].mUnknown6), state);
        else
            pChannels[index].mUnknownA = stateRef;
        pChannels[index].mUnknownC = pList->mUnknown8;
        pChannels[index].mUnknown1C = 0;
        pChannels[index].mUnknown2C = 1.0f;
        pChannels[index].mUnknown20 = 0x1000000;
        pChannels[index].mUnknown24 = 0.0f;
        pChannels[index].mUnknown28 = 0.0f;
        pChannels[index].mUnknown48 = 0.0f;
        if (fn_801BA720(&pChannels[index], fn_801BAB34(fn_801BC084(slot), anim), pUser) == 0)
            pChannels[index].mStatus = 2;
    }
    return index;
}

int fn_801BA2A8(Object_801BA03C *pList, Record_800D81C8 *pChannels, int slot, int anim, float weight, int state,
                void *pUser)
{
    return fn_801BA154(pList, pChannels, slot, anim, weight, state, pUser, 0xFFFF);
}

int fn_801BA2D0(Object_801BA03C *pList, Record_800D81C8 *pChannels, Record_800D81C8 *pSource)
{
    int index = fn_801B9F00(pList, pChannels);

    if (index != -1)
        pChannels[index] = *pSource;
    return index;
}

void fn_801BA360(Record_800D81C8 *pChannel, int a, int b, float x, float y)
{
    fn_801BF3C8(&pChannel->mUnknown30, a, b, x, y);
}

void fn_801BA384(Object_801BA03C *pList, Record_800D81C8 *pChannels, int index)
{
    pChannels[index].mStatus = 0;
}

void fn_801BA398(Object_801BA03C *pList, Record_800D81C8 *pChannels, int state)
{
    int i;

    for (i = 0; i < pList->mCount; i++) {
        if (pChannels[i].mStatus != 0 && pChannels[i].mUnknown8 == state)
            fn_801BA384(pList, pChannels, i);
    }
}

void fn_801BA418(Object_801BA03C *pList, Record_800D81C8 *pChannels, int index, int slot, int anim, int state,
                 void *pUser)
{
    float length;
    float time;
    int result;

    if (pChannels[index].mStatus == 2) {
        pChannels[index].mUnknown4 = fn_801BAB2C(fn_801BC084(slot));
        pChannels[index].mUnknown8 = state;
        pChannels[index].mUnknown6 = slot;
        pChannels[index].mUnknown2 = anim;
        if (pChannels[index].mUnknown66 == 0xFFFF)
            pChannels[index].mUnknown66 = fn_801BD6DC(pChannels[index].mUnknown4C.mpUnknown0);
        length = pChannels[index].mUnknown4C.mUnknown4 * (unsigned int)pChannels[index].mUnknown66;
        time = fn_80260260(pChannels[index].mUnknown4C.mUnknown8, length);
        result = fn_801BA720(&pChannels[index], fn_801BAB34(fn_801BC084(slot), anim), pUser);
        if (result != 1) {
            pChannels[index].mUnknown66 = fn_801BD6DC(pChannels[index].mUnknown4C.mpUnknown0);
            fn_801BD710(&pChannels[index].mUnknown4C, length / (unsigned int)pChannels[index].mUnknown66);
            result = fn_801BA650(&pChannels[index], time, pUser);
        }
        if (result == 1)
            pChannels[index].mStatus = result;
    }
}

unsigned short fn_801BA568(Object_801BA03C *pList, Record_800D81C8 *pChannels, int state)
{
    unsigned short count = 0;
    int i;

    for (i = 0; i < pList->mCount; i++) {
        if (pChannels[i].mStatus == 2 && pChannels[i].mUnknown8 == state)
            count++;
    }
    return count;
}

unsigned short fn_801BA5A8(Object_801BA03C *pList, Record_800D81C8 *pChannels, int state, int index)
{
    unsigned short count = 0;
    int i;

    for (i = 0; i < pList->mCount; i++) {
        if (pChannels[i].mStatus == 2 && pChannels[i].mUnknown8 == state) {
            if (count == index)
                return i;
            count++;
        }
    }
    return 0xFFFF;
}

void fn_801BA60C(Object_801BA03C *pList, Record_800D81C8 *pChannels, int state, float delay)
{
    int i;

    for (i = 0; i < pList->mCount; i++) {
        if (pChannels[i].mStatus == 2 && pChannels[i].mUnknown8 == state)
            pChannels[i].mUnknown48 = delay;
    }
}

int fn_801BA650(Record_800D81C8 *pChannel, float time, void *pUser)
{
    int result;

    fn_801B9DA8(pUser);
    fn_801B9D84(pChannel->mUnknown8);
    result = fn_801BD4E4(&pChannel->mUnknown4C, time);
    fn_801B9DCC();
    fn_801B9DDC();
    return result;
}

int fn_801BA6B0(Record_800D81C8 *pChannel)
{
    return pChannel->mFlags & 1;
}

void fn_801BA6BC(Record_800D81C8 *pChannel, int enable)
{
    int changed;

    if (enable == 1) {
        changed = !(pChannel->mFlags & 1);
        pChannel->mFlags |= 1;
    } else {
        changed = pChannel->mFlags & 1;
        pChannel->mFlags &= ~1;
    }
    if (changed) {
        if (pChannel->mFlags & 0x10)
            pChannel->mFlags = (pChannel->mFlags & ~0x10) | 0x20;
        else if (pChannel->mFlags & 0x20)
            pChannel->mFlags = (pChannel->mFlags & ~0x20) | 0x10;
    }
}

int fn_801BA720(Record_800D81C8 *pChannel, Anim_801BAB34 *pAnim, void *pUser)
{
    int result;

    fn_801B9D84(pChannel->mUnknown8);
    fn_801B9DA8(pUser);
    result = fn_801BD4C0(&pChannel->mUnknown4C, pAnim);
    fn_801B9DCC();
    fn_801B9DDC();
    pChannel->mFlags = pAnim->mUnknown2;
    return result;
}

void fn_801BA784(Record_800D81C8 *pDest, Record_800D81C8 *pSource)
{
    *pDest = *pSource;
    pDest->mUnknown4C.mpUnknown0 = fn_801BAB34(fn_801BC084(pSource->mUnknown6), pSource->mUnknown2);
}
