#include "game/cu_80136B1C.h"
#include "game/fn_801C1F94.h"
#include "game/Block_801BE60C.h"
#include "game/Item_80097440.h"

extern "C" float fn_80097A88(Object_80039F5C *p, int handle, Object_80137ABC *pBall, float *pOut, short *pValue);
extern "C" int fn_801BE068(void *, void *, void *, unsigned short, void *, float);
extern "C" unsigned short fn_801BA5A8(Object_8016D9B8 *p, Record_800D81C8 *records, unsigned short key, unsigned short index);
extern "C" int fn_801BA6B0(Record_800D81C8 *entry);
extern "C" void fn_801BA6BC(Record_800D81C8 *entry, int value);
extern "C" void fn_801BD81C(void *p, float value);
extern "C" void fn_800F05E4(int, State_80039F5C *, Message_800F01CC *, Object_80039F5C *);

extern "C" {
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
extern Record_80097518 lbl_8030C2B8[];
extern Block_80099630 *lbl_803EC92C;
void fn_800975A4(unsigned char kind, int handle, unsigned char *pHigh, unsigned char *pLow);
}

extern "C" int fn_80099F04(Object_80039F5C *p, int handle, int kind)
{
    Message_800F01CC message;
    unsigned char high;
    unsigned char low;
    int result;

    if (!(p->mFlags & 0x800)) {
        float blend;
        short value;
        Record_800D81C8 *pRecords;
        float duration;
        int index;
        unsigned short key;
        unsigned short group;
        unsigned short entry;

        p->mUnknown512.mUnknown14 = 0;
        lbl_803EC92C->mUnknown4.mUnknown0 = p->mpUnknown796->mUnknown8;
        lbl_803EC92C->mUnknown4.mUnknown14 = 0;
        lbl_803EC92C->mUnknown4.mUnknown10 = 0.0f;
        lbl_803EC92C->mUnknown4.mUnknown4 = 0.0f;
        lbl_803EC92C->mUnknown4.mUnknown8 = 0.0f;
        lbl_803EC92C->mUnknown4.mUnknownC = 0.0f;
        duration = fn_80097A88(p, handle, fn_80137ABC(kind), &blend, &value);
        index = (handle >> 29) & 3;
        key = lbl_8030C2B8[index].mUnknown8[handle & 0x1FFFFFFF].mUnknown0;
        group = lbl_8030C2B8[index].mUnknown8[handle & 0x1FFFFFFF].mUnknown2;
        p->mFlags &= ~4;
        p->mUnknown1011 = key >> 8;
        p->mUnknown1008.mUnknown1 = group >> 8;
        p->mUnknown1008.mUnknown0 = group;
        p->mUnknown1008.mUnknown2 = key;
        if (lbl_8030C2B8[index].mUnknown8[handle & 0x1FFFFFFF].mpUnknown4->mUnknown14.mZ > 1.159353f) {
            unsigned char type = lbl_8030C2B8[index].mUnknown8[handle & 0x1FFFFFFF].mpUnknown4->mUnknown4;

            if (type == 3 || type == 4 || type == 7) {
                float scale = p->mRatings[1] * (1.0f / 255.0f);

                if (scale > 1.0f) {
                    scale = 1.0f;
                }
                p->mUnknown772 = scale * 1.1f;
            }
        }
        p->mUnknown9[0] = 1;
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, lbl_8030C2B8[index].mUnknown0, p, 1.0f);
        pRecords = p->mpUnknown800;
        entry = fn_801BA5A8(p->mpUnknown796, pRecords, lbl_8030C2B8[index].mUnknown0, 0);
        if (handle < 0) {
            fn_801BA6BC(&pRecords[entry], fn_801BA6B0(&pRecords[entry]) == 0);
        }
        pRecords[entry].mUnknown44 = duration;
        fn_801BD81C(&pRecords[entry].mUnknown4C, blend);
        p->mpUnknown800[entry].mUnknownC = lbl_803EC92C->mUnknown4.mUnknown0;
        fn_801C1F94(&message, 0, sizeof(Message_800F01CC));
        message.mId = 28;
        fn_800975A4(kind, handle, &high, &low);
        message.mUnknown1[0] = high;
        message.mUnknown1[1] = low;
        message.mUnknown1[2] = value;
        if (p->mpState->mId == 28) {
            fn_800F05E4(0, p->mpState, &message, p);
        } else {
            fn_800F00D4(0, p->mpState, &message, p);
        }
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
