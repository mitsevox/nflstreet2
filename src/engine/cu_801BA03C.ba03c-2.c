#include <string.h>

typedef struct Script_801BD3BC {
    unsigned char mUnknown0;
    char mUnknown1[3];
    unsigned short mUnknown4[1];
} Script_801BD3BC;

typedef struct Frame_801BD3BC {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    float mUnknown4;
} Frame_801BD3BC;

typedef struct State_801BD3BC {
    Script_801BD3BC *mpUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    unsigned short mUnknown10;
    unsigned short mUnknown12;
    float mUnknown14;
    unsigned short mUnknown18;
    unsigned short mUnknown1A;
    unsigned short mUnknown1C;
    unsigned char mUnknown1E;
    unsigned char mUnknown1F;
    Frame_801BD3BC mUnknown20[2];
} State_801BD3BC;

typedef struct Triple_801BCA74 {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
} Triple_801BCA74;

typedef struct Pair_801BCCAC {
    float mUnknown0;
    float mUnknown4;
} Pair_801BCCAC;

typedef struct Record_801BCA74 {
    char mUnknown0[1];
    unsigned char mUnknown1;
    char mUnknown2[6];
    unsigned short mUnknown8;
    char mUnknownA[2];
    int mUnknownC;
    Triple_801BCA74 mUnknown10;
    int mUnknown1C;
    int mUnknown20;
    Pair_801BCCAC mUnknown24;
    float mUnknown2C;
    float mUnknown30;
    char mUnknown34[24];
    State_801BD3BC mUnknown4C;
} Record_801BCA74;

typedef struct Entry_801BCA74 {
    float mUnknown0;
    char mUnknown4[4];
    unsigned char mUnknown8;
    unsigned char mUnknown9;
    char mUnknownA[2];
    Triple_801BCA74 mUnknownC;
    Pair_801BCCAC mUnknown18;
    char mUnknown20[12];
} Entry_801BCA74;

typedef struct Anim_801BCA74 {
    unsigned short mUnknown0;
    char mUnknown2[2];
    Entry_801BCA74 mUnknown4[1];
} Anim_801BCA74;

typedef struct Object_801BA03C {
    char mUnknown0[2];
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    char mUnknown6[2];
    int mUnknown8;
} Object_801BA03C;

typedef struct Payload_801BE60C {
    char mUnknown0[64];
} Payload_801BE60C;

typedef union Value_801BF094 {
    unsigned int mUnknown0;
    float mUnknown0Float;
} Value_801BF094;

typedef struct Fade_801BF3C8 {
    float mUnknown0;
    float mUnknown4;
    char mUnknown8[4];
    float mUnknownC;
    Value_801BF094 mUnknown10;
    unsigned char mUnknown14;
    signed char mUnknown15;
    unsigned short mUnknown16;
} Fade_801BF3C8;

typedef struct Slot_801BE594 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    short mUnknown6;
    float mUnknown8;
    Payload_801BE60C mUnknownC;
    Fade_801BF3C8 mUnknown4C;
} Slot_801BE594;

typedef struct Collection_801BE594 {
    char mUnknown0[4];
    Slot_801BE594 mUnknown4[4];
} Collection_801BE594;

typedef int (*Handler_801BDA30)(void *pTable, unsigned short key, Object_801BA03C *pObject,
                                Record_801BCA74 *pRecords, void *pOwner, int event);

typedef struct Handlers_801BDA30 {
    unsigned short mUnknown0;
    Handler_801BDA30 *mpUnknown4;
} Handlers_801BDA30;

typedef struct Rule_801BEFA4 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    unsigned short mUnknown8;
    char mUnknownA[2];
    struct Transition_801BEFA4 *mpUnknownC;
} Rule_801BEFA4;

typedef struct Group_801BEFA4 {
    int mUnknown0;
    Rule_801BEFA4 mUnknown4[1];
} Group_801BEFA4;

typedef struct GroupRef_801BEFA4 {
    Group_801BEFA4 *mpUnknown0;
    char mUnknown4[4];
} GroupRef_801BEFA4;

typedef struct Transitions_801BEFA4 {
    unsigned short mUnknown0;
    char mUnknown2[10];
    GroupRef_801BEFA4 mUnknownC[1];
} Transitions_801BEFA4;

typedef struct Transition_801BEFA4 {
    char mUnknown0[4];
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    float mUnknown8;
    unsigned short mUnknownC;
    unsigned short mUnknownE;
} Transition_801BEFA4;

typedef void (*Update_801BF2B0)(Fade_801BF3C8 *p, float step);

extern State_801BD3BC *lbl_803ED610;
extern Handlers_801BDA30 **lbl_803EBB98;
extern int lbl_803ECEBC;
extern char lbl_8037EC7C[];
extern Transitions_801BEFA4 lbl_803D4F50;
extern Update_801BF2B0 *lbl_803EBB9C;
extern unsigned char *lbl_803EBBA0;
extern int lbl_803ED614;
extern Update_801BF2B0 lbl_802F484C[4];
extern unsigned char lbl_803EBBA4[4];

int fn_801B9D00(int op);
int fn_801B9D50(int op);
int fn_801BD3BC(State_801BD3BC *p, Script_801BD3BC *pScript, int flag);
void fn_801BC67C(Triple_801BCA74 *pOut, Triple_801BCA74 *pA, Triple_801BCA74 *pB, float t);
void fn_801CF8A8(int *pOut, int a, int b, float t);

int fn_801BCA74(Object_801BA03C *pObject, Record_801BCA74 *pRecords, Anim_801BCA74 *pAnim, int *pOut, int key, int all)
{
    float total = 0.0f;
    int found = 0;
    int value = 0;
    Triple_801BCA74 target;
    int i;

    for (i = 0; i < pAnim->mUnknown0; i++) {
        Entry_801BCA74 *pEntry = &pAnim->mUnknown4[i];
        int index = pEntry->mUnknown9;

        if (i + 1 < pAnim->mUnknown0 && pAnim->mUnknown4[i + 1].mUnknown9 == index) {
            if (!(pRecords[index].mUnknown4C.mUnknown1E & 0x10)) {
                target = pAnim->mUnknown4[i + 1].mUnknownC;
            } else {
                target.mUnknown8 = 0;
                target.mUnknown4 = 0;
                target.mUnknown0 = 0;
            }
            fn_801BC67C(&pRecords[index].mUnknown10, &pEntry->mUnknownC, &target, pRecords[index].mUnknown4C.mUnknown14);
            i++;
        } else {
            pRecords[index].mUnknown10 = pEntry->mUnknownC;
        }
        if (pEntry->mUnknown8 & 2) {
            Record_801BCA74 *pRecord = &pRecords[index];
            int angle;
            int delta;
            int blend;
            float weight;

            if (pRecord->mUnknown4C.mUnknown1E & 8) {
                pRecord->mUnknown1C = 0;
                pRecord->mUnknownC = pObject->mUnknown8;
                pRecord->mUnknown4C.mUnknown1E = (pRecord->mUnknown4C.mUnknown1E & ~8) | 0x10;
            }
            if (pRecord->mUnknown4C.mUnknown1E & 0x20) {
                pRecord->mUnknown4C.mUnknown1E &= ~0x38;
            }
            angle = pRecord->mUnknown10.mUnknown4 << 8 >> 8;
            pRecord->mUnknown10.mUnknown4 = 0;
            delta = angle - pRecord->mUnknown1C;
            pRecord->mUnknown1C = angle;
            blend = (int)(((long long)pRecord->mUnknown20 * delta) >> 24);
            total += pEntry->mUnknown0;
            weight = total != 0.0f ? pEntry->mUnknown0 / total : 0.0f;
            {
                int apply = all;

                if (pRecord->mUnknown8 == key || pRecord->mUnknown8 == 0xFFFF || key == 0xFFFF) {
                    found = 1;
                    apply = 1;
                }
                if (apply) {
                    fn_801CF8A8(&value, blend, value, weight);
                }
            }
        }
    }
    if (found) {
        *pOut = value;
    }
    return found;
}

void fn_801BBC3C(unsigned short type, unsigned short key, void *pTable);
void fn_801BA398(Object_801BA03C *pObject, Record_801BCA74 *pRecords, unsigned short key);
void *fn_801D2B7C(int size, int a, int b);
int fn_801D2BD0(void *p);
int fn_801F7C88(void);
unsigned int fn_801BA568(Object_801BA03C *pObject, Record_801BCA74 *pRecords, unsigned short key);
unsigned int fn_801BA5A8(Object_801BA03C *pObject, Record_801BCA74 *pRecords, unsigned short key, unsigned short index);
void fn_801BF3C8(Fade_801BF3C8 *p, int a, int b, float from, float to);
void fn_801BF46C(Fade_801BF3C8 *p, float step);
void fn_801BF4A8(Fade_801BF3C8 *p, int frames, float from, float to);
void fn_801BBDCC(unsigned short type, unsigned short key, Transitions_801BEFA4 *pTable);
void fn_80227248(Pair_801BCCAC *pOut, Pair_801BCCAC *pIn, float scale);
void fn_80227384(Pair_801BCCAC *pOut, Pair_801BCCAC *pIn, int angle);
void fn_80227638(Pair_801BCCAC *pOut, Pair_801BCCAC *pA, Pair_801BCCAC *pB);
void fn_80227690(Pair_801BCCAC *pOut, Pair_801BCCAC *pA, Pair_801BCCAC *pB);
void fn_80227904(Pair_801BCCAC *pOut, Pair_801BCCAC *pA, Pair_801BCCAC *pB, float t);

int fn_801BCCAC(Object_801BA03C *pObject, Record_801BCA74 *pRecords, Anim_801BCA74 *pAnim, Pair_801BCCAC *pOut, int key, int all)
{
    Pair_801BCCAC sum;
    Pair_801BCCAC offset;
    Pair_801BCCAC delta;
    float total;
    int found = 0;
    int i;

    sum.mUnknown4 = 0.0f;
    total = 0.0f;
    sum.mUnknown0 = 0.0f;
    for (i = 0; i < pAnim->mUnknown0; i++) {
        Entry_801BCA74 *pEntry = &pAnim->mUnknown4[i];

        if (pEntry->mUnknown8 & 4) {
            int index = pEntry->mUnknown9;
            int apply = all;

            if (pRecords[index].mUnknown8 == key || pRecords[index].mUnknown8 == 0xFFFF || key == 0xFFFF) {
                found = 1;
                apply = 1;
            }
            if (apply == 1) {
                Record_801BCA74 *pRecord = &pRecords[index];
                Pair_801BCCAC *pOffset;

                if (pRecord->mUnknown4C.mUnknown1E & 1) {
                    pRecord->mUnknown24.mUnknown0 = 0.0f;
                    pRecord->mUnknown4C.mUnknown1E = (pRecord->mUnknown4C.mUnknown1E & ~1) | 2;
                    pRecord->mUnknown24.mUnknown4 = 0.0f;
                }
                if (pRecord->mUnknown4C.mUnknown1E & 4) {
                    pRecord->mUnknown4C.mUnknown1E &= ~7;
                }
                if (i + 1 < pAnim->mUnknown0 && pAnim->mUnknown4[i + 1].mUnknown9 == index) {
                    if (!(pRecord->mUnknown4C.mUnknown1E & 2)) {
                        fn_80227904(&offset, &pEntry->mUnknown18, &pAnim->mUnknown4[i + 1].mUnknown18, pRecord->mUnknown4C.mUnknown14);
                    } else {
                        fn_80227248(&offset, &pEntry->mUnknown18, pRecord->mUnknown4C.mUnknown14);
                    }
                    pOffset = &offset;
                    i++;
                } else {
                    offset.mUnknown0 = pEntry->mUnknown18.mUnknown0;
                    offset.mUnknown4 = pEntry->mUnknown18.mUnknown4;
                    pOffset = &offset;
                }
                fn_80227690(&delta, pOffset, &pRecord->mUnknown24);
                fn_80227638(&pRecord->mUnknown24, &pRecord->mUnknown24, &delta);
                fn_80227248(&delta, &delta, pRecord->mUnknown2C);
                fn_80227384(&delta, &delta, pRecord->mUnknownC);
                total += pEntry->mUnknown0;
                fn_80227904(&sum, &delta, &sum, total != 0.0f ? pEntry->mUnknown0 / total : 0.0f);
            }
        }
    }
    if (found) {
        pOut->mUnknown4 = sum.mUnknown4;
        pOut->mUnknown0 = sum.mUnknown0;
    }
    return found;
}

void fn_801BCEEC(Object_801BA03C *p, Record_801BCA74 *pRecords)
{
    int i;

    p->mUnknown8 = (p->mUnknown8 + 0x800000) & 0xFFFFFF;
    for (i = 0; i < p->mUnknown4; i++, pRecords++) {
        if (pRecords->mUnknown1 != 0) {
            pRecords->mUnknownC = (pRecords->mUnknownC + 0x800000) & 0xFFFFFF;
        }
    }
}

int fn_801BCF40(State_801BD3BC *p)
{
    unsigned short word = p->mpUnknown0->mUnknown4[p->mUnknown18];
    int value;

    p->mUnknown18++;
    value = word & 0xFFF;
    if (word & 0x800) {
        value |= 0xF000;
    }
    if (word & 0x1000) {
        value <<= 16;
        value += p->mpUnknown0->mUnknown4[p->mUnknown18];
        p->mUnknown18++;
    }
    return value;
}

unsigned short fn_801BCF98(State_801BD3BC *p, float step, int flag)
{
    unsigned short result = 0xFFFF;
    int done = 0;

    do {
        unsigned short op = p->mpUnknown0->mUnknown4[p->mUnknown18];

        p->mUnknown18++;
        if (op & 0x8000) {
            if (!(op & 0x4000)) {
                switch (op) {
                case 0x8000:
                    if (p->mUnknown1A == 0xFFFF) {
                        p->mUnknown1A = p->mUnknown1C;
                    }
                    done = 1;
                    break;
                case 0x8001:
                    p->mUnknown18 = 0;
                    if (p->mUnknown1A == 0xFFFF) {
                        p->mUnknown1A = p->mUnknown1C;
                    }
                    break;
                case 0x8002:
                    p->mUnknown1F++;
                    p->mUnknown20[p->mUnknown1F - 1].mUnknown0 = p->mUnknown18;
                    p->mUnknown20[p->mUnknown1F - 1].mUnknown2 = 0;
                    p->mUnknown20[p->mUnknown1F - 1].mUnknown4 = p->mUnknown8 + step;
                    break;
                case 0x8003: {
                    unsigned short count = fn_801BCF40(p);

                    if (p->mUnknown20[p->mUnknown1F - 1].mUnknown2 == 0) {
                        p->mUnknown20[p->mUnknown1F - 1].mUnknown2 = count;
                    } else {
                        p->mUnknown20[p->mUnknown1F - 1].mUnknown2--;
                    }
                    if (p->mUnknown20[p->mUnknown1F - 1].mUnknown2 != 0) {
                        p->mUnknown18 = p->mUnknown20[p->mUnknown1F - 1].mUnknown0;
                        step = 0.0f;
                        p->mUnknown8 = p->mUnknown20[p->mUnknown1F - 1].mUnknown4;
                    } else {
                        p->mUnknown1F--;
                    }
                    break;
                }
                case 0x8004:
                    p->mUnknownC += fn_801BCF40(p) * 0.0625f;
                    break;
                case 0x8005:
                    p->mUnknown1E |= 9;
                    break;
                case 0x8006:
                    p->mUnknown1E |= 0x24;
                    break;
                default:
                    if ((op & 0xE000) == 0xA000) {
                        if (op & 0x1000) {
                            p->mUnknown18++;
                        }
                    }
                    break;
                }
            } else {
                int handled;

                lbl_803ED610 = p;
                if (flag == 0) {
                    handled = fn_801B9D00(op);
                } else {
                    handled = fn_801B9D50(op);
                }
                if (!handled) {
                    if (op & 0x1000) {
                        p->mUnknown18++;
                    }
                }
            }
        } else {
            result = op & 0x7FFF;
            done = 1;
            p->mUnknown1C++;
        }
    } while (!done);

    p->mUnknown8 += step;
    return result;
}

void fn_801BD26C(State_801BD3BC *p, Script_801BD3BC *pScript, int key)
{
    int done;

    fn_801BD3BC(p, pScript, 1);
    done = 0;
    p->mUnknown8 += p->mUnknownC + p->mUnknownC;
    do {
        unsigned short op = p->mpUnknown0->mUnknown4[p->mUnknown18];

        p->mUnknown18++;
        if (op & 0x8000) {
            if (op == key) {
                done = 1;
            }
            if (!(op & 0x4000)) {
                switch (op) {
                case 0x8000:
                    p->mUnknown8 -= p->mUnknownC;
                case 0x8001:
                    if (p->mUnknown1A == 0xFFFF) {
                        p->mUnknown1A = p->mUnknown1C;
                    }
                    done = 1;
                    break;
                case 0x8002:
                case 0x8003:
                case 0x8004:
                case 0x8005:
                case 0x8006:
                    break;
                default:
                    if ((op & 0xE000) == 0xA000) {
                        if (op & 0x1000) {
                            p->mUnknown18++;
                        }
                    }
                    break;
                }
            } else {
                lbl_803ED610 = p;
                fn_801B9D50(op);
            }
        } else {
            p->mUnknown8 += p->mUnknownC;
            p->mUnknown1C++;
        }
    } while (!done);
}

int fn_801BD3BC(State_801BD3BC *p, Script_801BD3BC *pScript, int flag)
{
    int result = 0;
    float rate;

    p->mpUnknown0 = pScript;
    rate = (float)pScript->mUnknown0 * 0.0625f;
    p->mUnknown4 = rate;
    if (!(rate > 0.0f)) {
        p->mUnknown4 = 1.0f;
    }
    p->mUnknownC = p->mUnknown4;
    p->mUnknown1C = 0;
    p->mUnknown8 = 0.0f;
    p->mUnknown18 = 0;
    p->mUnknown1A = 0xFFFF;
    p->mUnknown1F = 0;
    p->mUnknown1E = 0;
    p->mUnknown10 = fn_801BCF98(p, 0.0f, flag);
    p->mUnknown12 = fn_801BCF98(p, 0.0f, flag);
    p->mUnknown14 = 0.0f;
    if (p->mUnknown12 == 0xFFFF) {
        p->mUnknown12 = p->mUnknown10;
        result = 1;
    }
    return result;
}

int fn_801BD4C0(State_801BD3BC *p, Script_801BD3BC *pScript)
{
    return fn_801BD3BC(p, pScript, 0);
}

int fn_801BD4E4(State_801BD3BC *p, float step)
{
    float remaining = p->mUnknownC;
    int result = 0;

    p->mUnknownC = remaining - step;
    if (!(p->mUnknownC >= 0.0f)) {
        while (!(p->mUnknownC >= 0.0f) && !result) {
            p->mUnknown10 = p->mUnknown12;
            p->mUnknown12 = fn_801BCF98(p, remaining, 0);
            if (p->mUnknown12 == 0xFFFF) {
                p->mUnknown12 = p->mUnknown10;
                result = 1;
            }
            p->mUnknownC += p->mUnknown4;
            remaining = p->mUnknown4;
        }
        p->mUnknown8 += p->mUnknown4 - p->mUnknownC;
    } else {
        p->mUnknown8 += step;
    }
    if (!result) {
        p->mUnknown14 = p->mUnknown4 != 0.0f ? (p->mUnknown4 - p->mUnknownC) / p->mUnknown4 : 0.0f;
    } else {
        p->mUnknown14 = 1.0f;
    }
    return result;
}

float fn_801BD60C(Script_801BD3BC *pScript)
{
    State_801BD3BC state;

    fn_801BD26C(&state, pScript, 0xFFFF);
    return state.mUnknown8;
}

float fn_801BD660(Script_801BD3BC *pScript, int key);

float fn_801BD640(Script_801BD3BC *pScript, int key)
{
    return fn_801BD660(pScript, key);
}

float fn_801BD660(Script_801BD3BC *pScript, int key)
{
    State_801BD3BC state;

    fn_801BD26C(&state, pScript, key);
    return state.mUnknown8;
}

float fn_801BD690(State_801BD3BC *p, int key)
{
    State_801BD3BC state;

    fn_801BD26C(&state, p->mpUnknown0, key);
    return state.mUnknown8 - p->mUnknown8;
}

float fn_801BD6D4(State_801BD3BC *p)
{
    return p->mUnknown8;
}

unsigned short fn_801BD6DC(Script_801BD3BC *pScript)
{
    State_801BD3BC state;

    fn_801BD26C(&state, pScript, 0xFFFF);
    return state.mUnknown1A;
}

void fn_801BD710(State_801BD3BC *p, float rate)
{
    if (p->mUnknown4 != 0.0f) {
        p->mUnknownC = p->mUnknownC * rate / p->mUnknown4;
        p->mUnknown8 = p->mUnknown8 * rate / p->mUnknown4;
    } else {
        p->mUnknownC = 0.0f;
        p->mUnknown8 = 0.0f;
    }
    p->mUnknown4 = rate;
}

void fn_801BD758(State_801BD3BC *p, float seconds)
{
    if (p->mUnknown1A == 0xFFFF) {
        p->mUnknown1A = fn_801BD6DC(p->mpUnknown0);
    }
    seconds *= 60.0f;
    fn_801BD710(p, p->mUnknown1A != 0.0f ? seconds / (float)p->mUnknown1A : 0.0f);
}

void fn_801BD81C(State_801BD3BC *p, float scale)
{
    float rate;

    if (p->mUnknown1A == 0xFFFF) {
        p->mUnknown1A = fn_801BD6DC(p->mpUnknown0);
    }
    rate = p->mUnknown1A * (float)p->mpUnknown0->mUnknown0 * 0.0625f;
    rate *= scale;
    fn_801BD710(p, p->mUnknown1A != 0.0f ? rate / (float)p->mUnknown1A : 0.0f);
}

int fn_801BD910(void)
{
    return fn_801BCF40(lbl_803ED610);
}

int fn_801BD934(State_801BD3BC *p, Script_801BD3BC *pScript, unsigned short key)
{
    int found = 0;
    int done = 0;

    p->mpUnknown0 = pScript;
    p->mUnknown18 = 0;
    do {
        unsigned short op = p->mpUnknown0->mUnknown4[p->mUnknown18];

        p->mUnknown18++;
        if (op & 0x8000) {
            if (op == key) {
                found = 1;
                done = 1;
            }
            if (!(op & 0x4000)) {
                switch (op) {
                case 0x8000:
                case 0x8001:
                    done = 1;
                    break;
                case 0x8002:
                case 0x8003:
                case 0x8004:
                case 0x8005:
                case 0x8006:
                    break;
                default:
                    if ((op & 0xE000) == 0xA000) {
                        if (op & 0x1000) {
                            p->mUnknown18++;
                        }
                    }
                    break;
                }
            } else {
                lbl_803ED610 = p;
                if (!found) {
                    fn_801B9D50(op);
                }
            }
        }
    } while (!done);
    return found;
}

int fn_801BDA30(unsigned short type, unsigned short key, void *pOwner, int event, Object_801BA03C *pObject,
                Record_801BCA74 *pRecords)
{
    if (key & 0x8000) {
        return 0;
    }
    fn_801BBC3C(type, key, lbl_8037EC7C);
    return lbl_803EBB98[type]->mpUnknown4[key](lbl_8037EC7C, key, pObject, pRecords, pOwner, event);
}

void fn_801BDAC0(Collection_801BE594 *p)
{
    int count;
    int i;
    int j;

    for (count = 3; count >= 0; count--) {
        if (p->mUnknown4[count].mUnknown2 != 0) {
            break;
        }
    }
    if (count > 0) {
        i = 0;
        while (i < count) {
            if (p->mUnknown4[i].mUnknown2 == 0) {
                for (j = i; j < count; j++) {
                    p->mUnknown4[j] = p->mUnknown4[j + 1];
                    p->mUnknown4[j + 1].mUnknown2 = 0;
                    p->mUnknown4[j + 1].mUnknown8 = 0.0f;
                }
                count--;
            } else {
                i++;
            }
        }
    }
}

void fn_801BDBD4(Collection_801BE594 *p, Object_801BA03C *pObject, Record_801BCA74 *pRecords, int index,
                 void *pOwner)
{
    fn_801BDA30(pObject->mUnknown2, p->mUnknown4[index].mUnknown0, pOwner, 3, pObject, pRecords);
    fn_801BA398(pObject, pRecords, p->mUnknown4[index].mUnknown0);
    p->mUnknown4[index].mUnknown2 = 0;
}

unsigned short fn_801BDC3C(Collection_801BE594 *p, Object_801BA03C *pObject, Record_801BCA74 *pRecords, void *pOwner,
                           unsigned short key)
{
    int slot = -1;
    int freed = 0;
    int i;

    fn_801BDAC0(p);
    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 == 0) {
            slot = i;
            break;
        }
    }
    if (i == 4) {
        for (i = 0; i < 4; i++) {
            if (p->mUnknown4[i].mUnknown8 != 0.0f) {
                fn_801BDBD4(p, pObject, pRecords, i, pOwner);
                freed = 1;
                fn_801BDAC0(p);
                break;
            }
        }
        if (!freed) {
            for (i = 0; i < 4; i++) {
                if (p->mUnknown4[i].mUnknown2 == 1 && !(p->mUnknown4[i].mUnknown4C.mUnknown0 > 1e-07f) && (p->mUnknown4[i].mUnknown0 & 0x8000) &&
                    p->mUnknown4[i].mUnknown0 != 0xFFFF && fn_801BA568(pObject, pRecords, p->mUnknown4[i].mUnknown0) == 0) {
                    fn_801BDBD4(p, pObject, pRecords, i, pOwner);
                    freed = 1;
                    fn_801BDAC0(p);
                    break;
                }
            }
        }
        if (!freed) {
            for (i = 0; i < 4; i++) {
                if (p->mUnknown4[i].mUnknown2 == 1 && p->mUnknown4[i].mUnknown0 != 0xFFFF &&
                    fn_801BA568(pObject, pRecords, p->mUnknown4[i].mUnknown0) == 0) {
                    fn_801BDBD4(p, pObject, pRecords, i, pOwner);
                    freed = 1;
                    fn_801BDAC0(p);
                    break;
                }
            }
        }
        if (!freed) {
            float lowest = 1.1f;
            int index = -1;

            for (i = 0; i < 4; i++) {
                if (p->mUnknown4[i].mUnknown2 == 1 && p->mUnknown4[i].mUnknown0 != 0xFFFF &&
                    !(p->mUnknown4[i].mUnknown4C.mUnknown0 >= lowest)) {
                    lowest = p->mUnknown4[i].mUnknown4C.mUnknown0;
                    index = i;
                }
            }
            if (index != -1) {
                fn_801BDBD4(p, pObject, pRecords, index, pOwner);
                freed = 1;
                fn_801BDAC0(p);
            }
        }
        if (freed == 1) {
            for (i = 0; i < 4; i++) {
                if (p->mUnknown4[i].mUnknown2 == 0) {
                    slot = i;
                    break;
                }
            }
        }
    }
    if (slot == -1) {
        slot = 3;
        fn_801BDBD4(p, pObject, pRecords, 0, pOwner);
        fn_801BDAC0(p);
    }
    return slot;
}

unsigned short fn_801BDF38(Collection_801BE594 *p)
{
    unsigned short key = 0xFFFE;
    int unique;
    int i;

    do {
        unique = 1;
        for (i = 0; i < 4; i++) {
            if (p->mUnknown4[i].mUnknown0 == key) {
                key--;
                unique = 0;
                break;
            }
        }
    } while (!unique);
    return key;
}

int fn_801BDF90(int count)
{
    int result;

    lbl_803EBB98 = fn_801D2B7C(count * 4, 0, 0);
    result = fn_801F7C88();
    lbl_803ECEBC = count;
    if (lbl_803EBB98 != 0) {
        memset(lbl_803EBB98, 0, count * 4);
    }
    return result;
}

int fn_801BDFF8(void)
{
    if (lbl_803EBB98 != 0) {
        fn_801D2BD0(lbl_803EBB98);
        lbl_803EBB98 = 0;
    }
    return 0;
}

void fn_801BE030(int type, Handlers_801BDA30 *pHandlers)
{
    lbl_803EBB98[type] = pHandlers;
}

void fn_801BE040(Collection_801BE594 *p)
{
    int i;

    for (i = 0; i < 4; i++) {
        p->mUnknown4[i].mUnknown0 = 0;
        p->mUnknown4[i].mUnknown6 = -16;
        p->mUnknown4[i].mUnknown2 = 0;
    }
}

unsigned short fn_801BE648(Collection_801BE594 *p);
int fn_801BE82C(unsigned short type, unsigned short key);
void fn_801BE99C(Collection_801BE594 *p, Object_801BA03C *pObject, Record_801BCA74 *pRecords, unsigned short key,
                 unsigned short previous, int state, void *pOwner);

int fn_801BE068(Collection_801BE594 *p, Object_801BA03C *pObject, Record_801BCA74 *pRecords, unsigned short key,
                void *pOwner, float frames)
{
    unsigned short previous = fn_801BE648(p);
    unsigned short slot;
    int add;
    int i;

    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown2 == 3) {
            p->mUnknown4[i].mUnknown2 = 2;
            fn_801BDA30(pObject->mUnknown2, previous, pOwner, 4, pObject, pRecords);
            if (p->mUnknown4[i].mUnknown8 != 0.0f && i > 0) {
                fn_801BDBD4(p, pObject, pRecords, i, pOwner);
                if (p->mUnknown4[i - 1].mUnknown0 == 0xFFFF) {
                    p->mUnknown4[i - 1].mUnknown0 = fn_801BDF38(p);
                    fn_801BF4A8(&p->mUnknown4[i - 1].mUnknown4C, 10, -1.0f, 0.0f);
                    while (fn_801BA568(pObject, pRecords, 0xFFFF)) {
                        pRecords[fn_801BA5A8(pObject, pRecords, 0xFFFF, 0)].mUnknown8 = p->mUnknown4[i - 1].mUnknown0;
                    }
                }
            }
            break;
        }
    }
    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0) {
            unsigned short old = p->mUnknown4[i].mUnknown0;

            if (old == key || old == 0xFFFF) {
                p->mUnknown4[i].mUnknown0 = fn_801BDF38(p);
                p->mUnknown4[i].mUnknown4 &= ~1;
                while (fn_801BA568(pObject, pRecords, old)) {
                    pRecords[fn_801BA5A8(pObject, pRecords, old, 0)].mUnknown8 = p->mUnknown4[i].mUnknown0;
                }
            }
        }
    }
    add = 0;
    if (fn_801BE82C(pObject->mUnknown2, previous)) {
        add = 1;
    }
    if (add == 1) {
        slot = fn_801BDC3C(p, pObject, pRecords, pOwner, 0xFFFF);
        memset(&p->mUnknown4[slot], 0, sizeof(Slot_801BE594));
        p->mUnknown4[slot].mUnknown2 = add;
        p->mUnknown4[slot].mUnknown0 = 0xFFFF;
        p->mUnknown4[slot].mUnknown8 = 0.0f;
        fn_801BF3C8(&p->mUnknown4[slot].mUnknown4C, 0, 0, 0.0f, 0.0f);
    }
    slot = fn_801BDC3C(p, pObject, pRecords, pOwner, key);
    memset(&p->mUnknown4[slot], 0, sizeof(Slot_801BE594));
    p->mUnknown4[slot].mUnknown2 = 3;
    p->mUnknown4[slot].mUnknown0 = key;
    p->mUnknown4[slot].mUnknown8 = 0.0f;
    fn_801BF4A8(&p->mUnknown4[slot].mUnknown4C, 10, 0.0f, frames);
    fn_801BDA30(pObject->mUnknown2, key, pOwner, 0, pObject, pRecords);
    fn_801BE99C(p, pObject, pRecords, key, previous, 2, pOwner);
    return 0;
}

void fn_801BE3C0(Collection_801BE594 *p, unsigned short key, int a, int b, float from, float to)
{
    int i;

    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown0 == key && p->mUnknown4[i].mUnknown2 == 3) {
            fn_801BF3C8(&p->mUnknown4[i].mUnknown4C, a, b, from, to);
            return;
        }
    }
}

void fn_801BE420(Collection_801BE594 *p, Object_801BA03C *pObject, Record_801BCA74 *pRecords, void *pOwner, float step)
{
    int i;

    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown2 == 0) {
            break;
        }
        p->mUnknown4[i].mUnknown8 -= step;
        if (!(p->mUnknown4[i].mUnknown8 >= 0.0f)) {
            p->mUnknown4[i].mUnknown8 = 0.0f;
            fn_801BF46C(&p->mUnknown4[i].mUnknown4C, step);
            if (!(p->mUnknown4[i].mUnknown4C.mUnknown0 <= 1e-07f)) {
                if (p->mUnknown4[i].mUnknown4 & 1) {
                    fn_801BDA30(pObject->mUnknown2, p->mUnknown4[i].mUnknown0, pOwner, 2, pObject, pRecords);
                }
                if (fn_801BA568(pObject, pRecords, p->mUnknown4[i].mUnknown0) == 0) {
                    if (p->mUnknown4[i].mUnknown2 == 3) {
                        fn_801BDA30(pObject->mUnknown2, p->mUnknown4[i].mUnknown0, pOwner, 1, pObject, pRecords);
                    } else {
                        fn_801BDBD4(p, pObject, pRecords, i, pOwner);
                    }
                }
            } else {
                fn_801BDBD4(p, pObject, pRecords, i, pOwner);
            }
        }
    }
    fn_801BDAC0(p);
}

Slot_801BE594 *fn_801BE594(Collection_801BE594 *p, unsigned short key)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            return &p->mUnknown4[i];
        }
    }
    return 0;
}

float fn_801BE5D0(Collection_801BE594 *p, unsigned short key)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            return p->mUnknown4[i].mUnknown4C.mUnknown0;
        }
    }
    return 0.0f;
}

Payload_801BE60C *fn_801BE60C(Collection_801BE594 *p, unsigned short key)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            return &p->mUnknown4[i].mUnknownC;
        }
    }
    return 0;
}

unsigned short fn_801BE648(Collection_801BE594 *p)
{
    unsigned short key = 0xFFFF;
    int i;

    for (i = 3; i >= 0; i--) {
        if (p->mUnknown4[i].mUnknown2 == 3) {
            key = p->mUnknown4[i].mUnknown0;
        }
    }
    return key;
}

void fn_801BE67C(Collection_801BE594 *p, Object_801BA03C *pObject, Record_801BCA74 *pRecords, void *pOwner)
{
    int i;

    for (i = 3; i >= 0; i--) {
        if (p->mUnknown4[i].mUnknown2 != 3 && p->mUnknown4[i].mUnknown2 != 0) {
            fn_801BDBD4(p, pObject, pRecords, i, pOwner);
        }
    }
    fn_801BDAC0(p);
    if (p->mUnknown4[0].mUnknown2 == 3) {
        p->mUnknown4[0].mUnknown8 = 0.0f;
        fn_801BF3C8(&p->mUnknown4[0].mUnknown4C, 0, 0, 1.0f, 1.0f);
    }
}

void *fn_801BE72C(unsigned short type, unsigned short key)
{
    fn_801BBC3C(type, key, lbl_8037EC7C);
    return lbl_8037EC7C;
}

void fn_801BE760(Collection_801BE594 *p, unsigned short key, unsigned short flags)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            p->mUnknown4[i].mUnknown4 |= flags;
        }
    }
}

void fn_801BE798(Collection_801BE594 *p, unsigned short key, float value)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            p->mUnknown4[i].mUnknown8 = value;
        }
    }
}

float fn_801BE7C8(Collection_801BE594 *p, unsigned short key)
{
    float value = 0.0f;
    int i;

    for (i = 0; i <= 3; i++) {
        if (p->mUnknown4[i].mUnknown2 != 0 && p->mUnknown4[i].mUnknown0 == key) {
            value = p->mUnknown4[i].mUnknown8;
            break;
        }
    }
    return value;
}

int fn_801BE82C(unsigned short type, unsigned short key)
{
    fn_801BBDCC(type, key, &lbl_803D4F50);
    return lbl_803D4F50.mUnknown0;
}

unsigned int fn_801BE860(Collection_801BE594 *p, Object_801BA03C *pObject, Record_801BCA74 *pRecords, unsigned short key)
{
    float highest = 0.0f;
    unsigned int best = 0xFFFF;
    unsigned int count = fn_801BA568(pObject, pRecords, key);
    unsigned short i;

    for (i = 0; i < count; i++) {
        unsigned int index = fn_801BA5A8(pObject, pRecords, key, i);

        if (!(highest >= pRecords[index].mUnknown30)) {
            highest = pRecords[index].mUnknown30;
            best = index;
        }
    }
    return best;
}

void fn_801BE910(Collection_801BE594 *p, unsigned short key, int frames)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (p->mUnknown4[i].mUnknown0 == key
            || ((p->mUnknown4[i].mUnknown0 & 0x8000) && p->mUnknown4[i].mUnknown0 != 0xFFFF)) {
            fn_801BF4A8(&p->mUnknown4[i].mUnknown4C, frames, -1.0f, 0.0f);
        }
    }
}

Transition_801BEFA4 *fn_801BEFA4(Transitions_801BEFA4 *pTable, Object_801BA03C *pObject, Record_801BCA74 *pRecords,
                                 unsigned short fromType, unsigned short fromFrame, unsigned short fromKey,
                                 unsigned short toType, unsigned short toKey, unsigned short toFrame)
{
    Transition_801BEFA4 *pResult = 0;
    unsigned short key;
    int i;

    if (toKey != 0xFFFF) {
        key = toFrame | 0x8000;
    } else {
        key = 0xFFFF;
        toKey = toType;
    }
    for (i = 0; i < pTable->mUnknown0; i++) {
        Group_801BEFA4 *pGroup = pTable->mUnknownC[i].mpUnknown0;
        int j;

        for (j = 0; j < pGroup->mUnknown0; j++) {
            if ((pGroup->mUnknown4[j].mUnknown0 == key || (key == 0xFFFF && !(pGroup->mUnknown4[j].mUnknown0 & 0x8000))) &&
                pGroup->mUnknown4[j].mUnknown2 == toKey && pGroup->mUnknown4[j].mUnknown4 == fromType &&
                (fromType == 0xFFFF ||
                 (fromKey >= pGroup->mUnknown4[j].mUnknown6 && fromKey <= pGroup->mUnknown4[j].mUnknown8))) {
                pResult = pGroup->mUnknown4[j].mpUnknownC;
            }
        }
    }
    return pResult;
}

void fn_801BF090(Fade_801BF3C8 *p, float step)
{
}

void fn_801BF094(Fade_801BF3C8 *p, float step)
{
    float value = p->mUnknown0;
    float target = p->mUnknown4;

    if (value != target) {
        p->mUnknown0 = (target - p->mUnknownC) / (float)p->mUnknown10.mUnknown0 * step + value;
        if (!(p->mUnknownC >= target)) {
            if (!(p->mUnknown0 <= target)) {
                p->mUnknown0 = target;
            }
        } else if (!(p->mUnknown0 >= target)) {
            p->mUnknown0 = target;
        }
    }
}

void fn_801BF11C(Fade_801BF3C8 *p, float step)
{
    p->mUnknownC -= step;
    if (!(p->mUnknownC > 0.0f)) {
        p->mUnknown0 = 0.0f;
    }
}

void fn_801BF2B0(int count)
{
    int i;

    lbl_803EBB9C = fn_801D2B7C(count * 4, 0, 0);
    lbl_803EBBA0 = fn_801D2B7C(count, 0, 0);
    fn_801F7C88();
    lbl_803ED614 = count;
    if (lbl_803EBB9C != 0) {
        for (i = 0; i < 4; i++) {
            lbl_803EBB9C[i] = lbl_802F484C[i];
            lbl_803EBBA0[i] = lbl_803EBBA4[i];
        }
        for (; i < count; i++) {
            lbl_803EBB9C[i] = 0;
            lbl_803EBBA0[i] = 0;
        }
    }
}

int fn_801BF384(void)
{
    if (lbl_803EBB9C != 0) {
        fn_801D2BD0(lbl_803EBB9C);
        fn_801D2BD0(lbl_803EBBA0);
        lbl_803EBB9C = 0;
        lbl_803EBBA0 = 0;
    }
    return 0;
}
