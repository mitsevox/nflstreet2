#include "game/cu_8008E978.h"
#include "game/fn_801C1F94.h"
#include "game/Frame_800DF7CC.h"

extern "C" {
void fn_80093348(int handle);
void fn_8009134C(int index);
void fn_800919F0(int index);
void fn_800917A4(int index);
void fn_80091E44(int index);
void fn_800921E8(int index, int active);
void fn_800941B8(void);
void fn_800941EC(void);
void fn_800A3B58(Object_80039F5C *p, int a, int b);
void fn_800A3B5C(Object_80039F5C *p);
int fn_801784C4(void);
int fn_801BBE5C(int objectType, int fileNum);
unsigned int fn_801BBEC0(unsigned int id, int flags);
void fn_801BB948(unsigned short id);
void fn_801383E4(int on);
int fn_80027DF0(void);
}

extern unsigned char lbl_803EA8BD;

/* Ends character handle's playback: puts each player back on its pose
   spot (actor flag 0x400; 0x800 takes the block's own spot and turn, and
   fn_801784C4 mirrors), restarts players whose state animation exists,
   runs the per-character clean-up and then releases the slot, freeing it
   once its table entry's use count drops to zero. */
extern "C" void fn_80093410(int handle)
{
    Character_80093BCC *pCharacter = fn_80093BCC(handle);

    if (pCharacter != 0) {
        Actor_801C009C *pActor;
        unsigned short i;

        lbl_803EA8BD = 0;
        pActor = fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4);
        (lbl_803EC924->mUnknown80.mCharacters + handle)->mUnknown38C = 8;
        lbl_803EC924->mUnknown80.mUnknownE4E = 0;
        fn_80093348(handle);
        for (i = 0; i < pActor->mUnknown4; i++) {
            Object_80039F5C *p = pCharacter->mUnknown14[i];

            if (p != 0) {
                if (pActor->mUnknown8 & 0x400) {
                    p->mpUnknown4->mUnknown20 &= ~0x2000;
                    if (pActor->mUnknown8 & 0x800) {
                        Block_80170E64 *pBlock = p->mpUnknown4;

                        p->mMotion.mFacing = (pBlock->mUnknown44.mUnknown32 + pBlock->mUnknown36) & 0xFFFFFF;
                        p->mMotion.mPos.mX = pBlock->mUnknown920;
                        p->mMotion.mPos.mY = pBlock->mUnknown936;
                        p->mMotion.mPos.mZ = 0.0f;
                    } else {
                        Block_80170E64 *pBlock = p->mpUnknown4;

                        p->mMotion.mFacing = pBlock->mUnknown44.mUnknown32;
                        p->mMotion.mPos.mX = pBlock->mUnknown44.mUnknown8[2];
                        p->mMotion.mPos.mY = -pBlock->mUnknown44.mUnknown8[0];
                        p->mMotion.mPos.mZ = 0.0f;
                    }
                    if (fn_801784C4()) {
                        p->mMotion.mFacing = (p->mMotion.mFacing + 0x800000) & 0xFFFFFF;
                        p->mMotion.mPos.mX = -p->mMotion.mPos.mX;
                        p->mMotion.mPos.mY = -p->mMotion.mPos.mY;
                    }
                }
                Frame_800DF7CC *pFrame = fn_801C029C(pActor, i);
                int id = fn_801BBE5C(pFrame->mUnknown42 | 0x4000, pFrame->mUnknown14);

                if (id != 0xFFFFFF && fn_801BBEC0(id, 0x400) != 0xFFFFFF) {
                    fn_800A3B5C(p);
                    fn_800A3B58(p, 2, 0);
                }
            }
        }
        fn_8009134C(handle);
        fn_800919F0(handle);
        fn_800917A4(handle);
        fn_80091E44(handle);
        fn_800921E8(handle, 0);
        if (pCharacter->mUnknownD8.mWord & 0x80000000) {
            fn_801BB948(pCharacter->mUnknownD8.mParts[1]);
            fn_801C1F94(&lbl_803EC924->mUnknown80.mCharacters[handle], 0, sizeof(Character_80093BCC));
            lbl_803EC924->mUnknown80.mCharacters[handle].mUnknown0 = -1;
        } else if (--lbl_8030C164[pCharacter->mUnknownD8.mWord].mUnknown4 == 0) {
            fn_801C1F94(&lbl_803EC924->mUnknown80.mCharacters[handle], 0, sizeof(Character_80093BCC));
            lbl_803EC924->mUnknown80.mCharacters[handle].mUnknown0 = -1;
        } else {
            (lbl_803EC924->mUnknown80.mCharacters + handle)->mUnknown38C = 0;
        }
        if (fn_80027DF0() == 0) {
            fn_801383E4(1);
        }
        fn_800941B8();
        fn_800941EC();
    }
}
