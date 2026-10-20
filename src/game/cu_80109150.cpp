#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/Team_80167A8C.h"
#include "game/State_803EB098.h"
#include "game/cu_80067C10.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/Record_800DB60C.h"
#include "game/fn_801BE60C.h"
#include "game/Block_801BE60C.h"

/* The 88-byte block at player +336 as fn_80109150 initialises it and
   fn_80108954 updates it. */
struct Block_80109150 {
    char mUnknown0[36];
    int mUnknown36;
    int mUnknown40;
    float mUnknown44;
    unsigned char mUnknown48;
    unsigned char mUnknown49;
    unsigned char mUnknown50;
    unsigned char mUnknown51;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
    unsigned char mUnknown54;
    char mUnknown55[1];
    unsigned char mUnknown56;
    unsigned char mUnknown57;
    short mUnknown58;
    unsigned char mUnknown60;
    unsigned char mUnknown61;
    unsigned char mUnknown62;
    unsigned char mUnknown63;
    unsigned char mUnknown64;
    unsigned char mUnknown65;
    unsigned char mUnknown66;
    char mUnknown67[21];
};

extern "C" {
void fn_8009A8D4(void *p);
unsigned char fn_8009F0B8(Object_80039F5C *p, int angle);
unsigned int fn_800ABDA4(int team);
void fn_80106A60(Object_80039F5C *p);
}

extern "C" int fn_80109150(Object_80039F5C *p) {
    Block_80109150 *pBlock = (Block_80109150 *)&p->mUnknown336;

    fn_801C1F94(pBlock, 0, 88);
    pBlock->mUnknown51 = pBlock->mUnknown49 = p->mpState->mUnknown1;
    pBlock->mUnknown58 = 0;
    pBlock->mUnknown50 = 4;
    pBlock->mUnknown44 = 0.0f;
    pBlock->mUnknown56 = fn_802372EC(0, 100);
    pBlock->mUnknown52 = 0;
    pBlock->mUnknown53 = 0;
    pBlock->mUnknown54 = 0;
    pBlock->mUnknown48 = 0;
    pBlock->mUnknown57 = 0;
    pBlock->mUnknown61 = 0;
    pBlock->mUnknown60 = 1;
    pBlock->mUnknown63 = 0;
    pBlock->mUnknown62 = fn_8009F0B8(p, 0x38E38E);
    pBlock->mUnknown64 = fn_801374D4();
    pBlock->mUnknown65 = 1;
    pBlock->mUnknown66 = 0;
    fn_80106A60(p);
    fn_8009A8D4(pBlock);
    if (fn_800B65A0(p->mIdBytes[2]) == 255 && fn_800ABDA4(p->mIdBytes[2]) == 0) {
        pBlock->mUnknown58 = 0;
    }
    return 0;
}
