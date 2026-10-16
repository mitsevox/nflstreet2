#include "game/Command_800CEE74.h"
#include "game/cu_80136B1C.h"

/* Block at player +336 passed to fn_80099734, fn_800997F4 and fn_8009817C.
   Only the accessed fields are declared. */
struct Block_800997F4 {
    char mUnknown0[8];
    int mUnknown8;
    int mUnknown12;
};

extern "C" int fn_8009817C(Object_80039F5C *p, Vector_80039F5C *pPos, int facing, unsigned char a, Object_80137ABC *pBall,
                           int b, int mode, float range, Block_800997F4 *pBlock, int c, int d, int e, int f, int g);
extern "C" void fn_800CEED8(int, int, Command_800CEE74 *, Object_80039F5C *, Vector_80039F5C *, int, Vector_80039F5C *,
                            int *, unsigned char *);
extern "C" float fn_80178A2C(void);
extern unsigned char lbl_803EA944;
extern "C" int fn_80098EAC(Object_80039F5C *p, Vector_80039F5C *pPos, int facing, unsigned char a, Object_80137ABC *pBall,
                           int b, int mode, int c, int d, unsigned char flags, int e);
extern "C" int fn_80138064(Object_80137ABC *pBall, Vector_80039F5C *pOut);

extern "C" {
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_80178320(void);
int fn_80099510(Object_80039F5C *p);
int fn_80099734(Object_80039F5C *p, Object_80137ABC *pBall, int a, int mode, float range, Block_800997F4 *pBlock, int b, int c, int d, unsigned char e);
void fn_800CEE74(Command_800CEE74 *pOut, Object_80039F5C *pA, Object_80039F5C *pB, void *pData, int angle, int key, int mirror);
void fn_800CEED8(int key, int index, Command_800CEE74 *pRecord, Object_80039F5C *pPlayer, Vector_80039F5C *pPoint, int angle, Vector_80039F5C *pOut, int *pAngle, unsigned char *pValue);
}

extern "C" int fn_800997F4(Object_80039F5C *p, Object_80137ABC *pBall, float range, Block_800997F4 *pBlock, int a,
                           int b, int c, int *pOutA, int *pOutB)
{
    Command_800CEE74 command;
    unsigned char order[3] = { 1, 2, 3 };
    Vector_80039F5C end;
    unsigned char key;
    int extra = 0;
    int index;
    int angle;
    int value = -1;
    int result = 0x1FFFFFFF;
    int last = 0x1FFFFFFF;
    unsigned char i;
    unsigned char j;

    if (fn_80099510(p) != 0) {
        *pOutA = value;
        if (__builtin_fabsf(p->mMotion.mPos.mY) < fn_80178A2C() - 5.0f) {
            order[0] = 2;
            order[1] = 1;
            order[2] = 3;
        } else if (p->mIdBytes[2] == fn_80178320()) {
            order[0] = 3;
            order[1] = 2;
            order[2] = 1;
        }
        if (pBlock != 0) {
            last = pBlock->mUnknown8;
        }
        for (i = 0; i <= 2; i++) {
            for (j = 0; j <= 1; j++) {
                unsigned char flags;
                int kind;

                p->mUnknown1008.mUnknown0 = order[i];
                if (j == 1) {
                    fn_800CEE74(&command, p, 0, 0, 0, 0xE0, 1);
                } else {
                    fn_800CEE74(&command, p, 0, 0, 0, 0xE0, 0);
                }
                value = fn_800C3BEC(p, &command, &extra, &index);
                if (value == -1) {
                    continue;
                }
                fn_800CEED8(0xE0, index, &command, p, (Vector_80039F5C *)&p->mUnknown1160.mUnknown16,
                            p->mUnknown1160.mUnknown12Word, &end, &angle, &key);
                flags = 1;
                if (command.mUnknown62 != 0) {
                    flags = 2;
                }
                switch (p->mUnknown1008.mUnknown0) {
                case 2:
                    kind = 5;
                    break;
                case 3:
                    kind = 6;
                    break;
                case 1:
                    kind = 4;
                    break;
                default:
                    kind = 4;
                    break;
                }
                result = fn_8009817C(p, &end, angle, key + lbl_803EA944, pBall, kind, kind, range, pBlock, a, b, c, 1,
                                     flags);
                if (pBlock != 0) {
                    if (pBlock->mUnknown8 == last) {
                        value = pBlock->mUnknown12;
                    } else {
                        pBlock->mUnknown12 = value;
                        last = pBlock->mUnknown8;
                    }
                }
                if (result != 0x1FFFFFFF) {
                    break;
                }
            }
            if (result != 0x1FFFFFFF) {
                break;
            }
        }
        if (result != 0x1FFFFFFF) {
            *pOutB = extra;
            *pOutA = value;
        }
    }
    return result;
}

extern "C" void fn_80099AD0(Object_80039F5C *p, Object_80137ABC *pBall, int a, int mode, int b, int d, unsigned char e)
{
    unsigned char flags = 0;
    int facing;
    int angle;
    Vector_80039F5C delta;

    if (e != 0) {
        flags = 2;
    }
    if (fn_80098EAC(p, &p->mMotion.mPos, p->mMotion.mFacing, 0, pBall, a, mode, b, d, flags, 0) != 0x1FFFFFFF) {
        return;
    }
    facing = p->mMotion.mFacing;
    fn_80138064(pBall, &delta);
    fn_80227690(&delta, &delta, &p->mMotion.mPos);
    angle = fn_801CFE40(delta.mY, delta.mX);
    if (fn_801CFFD0(p->mMotion.mFacing, angle) <= 0xAAAA9) {
        p->mMotion.mFacing = angle & 0xFFFFFF;
    } else {
        angle = (angle - p->mMotion.mFacing) & 0xFFFFFF;
        if (angle <= 0x7FFFFF) {
            p->mMotion.mFacing = (p->mMotion.mFacing + 0xAAAAA) & 0xFFFFFF;
        } else {
            p->mMotion.mFacing = (p->mMotion.mFacing - 0xAAAAA) & 0xFFFFFF;
        }
    }
    p->mpUnknown796->mUnknown8 = p->mMotion.mFacing;
    if (fn_80098EAC(p, &p->mMotion.mPos, p->mMotion.mFacing, 0, pBall, a, mode, b, d, flags, 0) == 0x1FFFFFFF) {
        p->mMotion.mFacing = facing;
        p->mpUnknown796->mUnknown8 = facing;
        fn_80099734(p, pBall, a, mode, 120.0f, 0, b, 0, d, e);
    }
}

extern "C" int fn_80099C80(Object_80039F5C *p, Object_80137ABC *pBall, int b, int *pOutA, int *pOutB)
{
    Command_800CEE74 command;
    unsigned char order[3] = { 1, 2, 3 };
    Vector_80039F5C end;
    unsigned char key;
    int extra = 0;
    int index;
    int angle;
    int value = -1;
    int result = 0x1FFFFFFF;
    unsigned char i;
    unsigned char j;

    *pOutA = value;
    if (__builtin_fabsf(p->mMotion.mPos.mY) < fn_80178A2C() - 5.0f) {
        order[0] = 2;
        order[1] = 1;
        order[2] = 3;
    } else if (p->mIdBytes[2] == fn_80178320()) {
        order[0] = 3;
        order[1] = 2;
        order[2] = 1;
    }
    for (i = 0; i <= 2; i++) {
        for (j = 0; j <= 1; j++) {
            unsigned char flags;
            int kind;

            fn_800CEE74(&command, p, 0, 0, 0, 0xE0, j == 1);
            p->mUnknown1008.mUnknown0 = order[i];
            value = fn_800C3BEC(p, &command, &extra, &index);
            if (value == -1) {
                continue;
            }
            fn_800CEED8(0xE0, index, &command, p, (Vector_80039F5C *)&p->mUnknown1160.mUnknown16,
                        p->mUnknown1160.mUnknown12Word, &end, &angle, &key);
            flags = 1;
            if (command.mUnknown62 != 0) {
                flags = 2;
            }
            switch (p->mUnknown1008.mUnknown0) {
            case 2:
                kind = 5;
                break;
            case 3:
                kind = 6;
                break;
            case 1:
                kind = 4;
                break;
            default:
                kind = 4;
                break;
            }
            result = fn_80098EAC(p, &end, angle, key + lbl_803EA944, pBall, kind, kind, 3, b, 1, flags);
            if (result != 0x1FFFFFFF) {
                break;
            }
        }
        if (result != 0x1FFFFFFF) {
            break;
        }
    }
    if (result == 0x1FFFFFFF) {
        result = fn_800997F4(p, pBall, 120.0f, 0, 3, 0, b, &value, &extra);
    }
    if (result != 0x1FFFFFFF) {
        *pOutA = value;
        *pOutB = extra;
    }
    return result;
}
