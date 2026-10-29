#include "engine/cu_801B9F00.h"

Block_801BD6D4 *lbl_803ED610;

int InitializeSequenceState(Block_801BD6D4 *p, Anim_801BAB34 *pScript, int flag);

int fn_801BCF40(Block_801BD6D4 *p)
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

unsigned short fn_801BCF98(Block_801BD6D4 *p, float step, int flag)
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

void fn_801BD26C(Block_801BD6D4 *p, Anim_801BAB34 *pScript, int key)
{
    int done;

    InitializeSequenceState(p, pScript, 1);
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

/* Reset playback state and read the first two sequence values. */
int InitializeSequenceState(Block_801BD6D4 *p, Anim_801BAB34 *pScript, int flag)
{
    int result = 0;

    p->mpUnknown0 = pScript;
    p->mUnknown4 = pScript->mUnknown0;
    p->mUnknown4 *= 0.0625f;
    if (p->mUnknown4 <= 0.0f) {
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

int fn_801BD4C0(Block_801BD6D4 *p, Anim_801BAB34 *pScript)
{
    return InitializeSequenceState(p, pScript, 0);
}

int fn_801BD4E4(Block_801BD6D4 *p, float step)
{
    float remaining = p->mUnknownC;
    int result = 0;

    p->mUnknownC = remaining - step;
    if (p->mUnknownC < 0.0f) {
        while (p->mUnknownC < 0.0f && !result) {
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

float fn_801BD60C(Anim_801BAB34 *pScript)
{
    Block_801BD6D4 state;

    fn_801BD26C(&state, pScript, 0xFFFF);
    return state.mUnknown8;
}

float fn_801BD660(Anim_801BAB34 *pScript, int key);

float fn_801BD640(Anim_801BAB34 *pScript, int key)
{
    return fn_801BD660(pScript, key);
}

float fn_801BD660(Anim_801BAB34 *pScript, int key)
{
    Block_801BD6D4 state;

    fn_801BD26C(&state, pScript, key);
    return state.mUnknown8;
}

float fn_801BD690(Block_801BD6D4 *p, int key)
{
    Block_801BD6D4 state;

    fn_801BD26C(&state, p->mpUnknown0, key);
    return state.mUnknown8 - p->mUnknown8;
}

float fn_801BD6D4(Block_801BD6D4 *p)
{
    return p->mUnknown8;
}

unsigned short fn_801BD6DC(Anim_801BAB34 *pScript)
{
    Block_801BD6D4 state;

    fn_801BD26C(&state, pScript, 0xFFFF);
    return state.mUnknown1A;
}

void fn_801BD710(Block_801BD6D4 *p, float rate)
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

void fn_801BD758(Block_801BD6D4 *p, float seconds)
{
    if (p->mUnknown1A == 0xFFFF) {
        p->mUnknown1A = fn_801BD6DC(p->mpUnknown0);
    }
    seconds *= 60.0f;
    fn_801BD710(p, p->mUnknown1A != 0.0f ? seconds / (float)p->mUnknown1A : 0.0f);
}

void fn_801BD81C(Block_801BD6D4 *p, float scale)
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

int fn_801BD934(Block_801BD6D4 *p, Anim_801BAB34 *pScript, unsigned short key)
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
