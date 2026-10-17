#include "game/Object_8017886C.h"
#include "game/fn_800670B4.h"

/* Four-byte entry of the stream read by fn_800B9F50. */
struct Event_800B9F50 {
    unsigned char mType;
    unsigned char mIndex;
    unsigned short mTime;
};

/* Block allocated by fn_800BA3F0 through fn_80238174 under the id 'prac'
   (392 bytes); only the accessed fields are declared. */
struct Block_800BA3F0 {
    Object_800670B4 *mpUnknown0;
    Object_800670B4 *mpUnknown4;
    Record_80067338 *mpUnknown8;
    Record_80067338 *mpUnknownC;
    int mUnknown10;
    unsigned char mUnknown14;
    unsigned char mUnknown15[3];
    Point_8017886C mUnknown18;
    int mUnknown20;
    unsigned char mUnknown24[0x9C];
    int mUnknownC0;
    unsigned char mUnknownC4[0x1C];
    unsigned char mUnknownE0;
    unsigned char mUnknownE1[3];
    int mUnknownE4[37];
    Event_800B9F50 *mpUnknown178;
    int mUnknown17C;
    unsigned char mUnknown180;
    unsigned char mUnknown181[1];
    unsigned char mUnknown182;
    unsigned char mUnknown183;
    unsigned char mUnknown184;
    unsigned char mUnknown185;
    unsigned char mUnknown186[2];
};


extern "C" {
int fn_800BA870(void);
void fn_800AD910(int a, float b);

extern Block_800BA3F0 *lbl_803EAB88;
}

extern "C" Point_8017886C fn_800BA7A0(void)
{
    if (lbl_803EAB88->mUnknown20 == 0) {
        lbl_803EAB88->mUnknown18.mX = 0.0f;
        lbl_803EAB88->mUnknown18.mY = -20.0f;
    }
    return lbl_803EAB88->mUnknown18;
}

extern "C" void fn_800BA804(int value)
{
    if (fn_800BA870() != 0) {
        lbl_803EAB88->mUnknown183 = value;
        if (value != 0) {
            fn_800AD910(8, 0.0f);
        }
    } else {
        lbl_803EAB88->mUnknown183 = 0;
    }
}
