#include "game/cu_8008E978.h"
#include "game/cu_8002B8F8.h"
#include "game/Object_8003DEC4.h"
#include "game/cu_80064864.h"
#include "game/fn_800AD9B4.h"

struct Class_80297C60;
struct Sample_801C009C;

extern "C" {
void fn_80028DD0(float value);
int fn_8002C9A8(Type_803EA368 *p, int msg, int value);
Object_8003DEC4 *fn_8003DEC4(int index);
Object_80039F5C *fn_8003E0C8(Block_80170E64 *object);
int fn_8005BE5C(int value);
void fn_8005BF18(void);
void fn_8005BF5C(void);
void fn_8005BF98(void);
int fn_8005BFD4(void);
void fn_80067E3C(int type, Vector_80039F5C *pPos, int id, int a, int b, int c);
int fn_800737B8(void);
Object_80039F5C *fn_8008FF28(Params_80092E54 *pRequest, Actor_801C009C *pActor);
void fn_80090BDC(void);
int fn_80090E4C(int index);
void fn_80091144(int index);
Actor_801C009C *fn_80091240(int index);
void fn_8009126C(int index);
int fn_800916E0(int index);
int fn_80091864(int index);
int fn_80091AD0(Character_80093BCC *pCharacter, Actor_801C009C *pActor);
int fn_80091C84(int index, float *pOut);
int fn_80091D34(void);
void fn_80091DAC(int index, int force);
void fn_80092380(Character_80093BCC *pCharacter, int enable);
int fn_800927BC(unsigned char index);
void fn_800941B8(void);
void fn_800941EC(void);
int fn_80096304(int index);
int fn_8009637C(int index);
void fn_8009BA10(int value);
int fn_800B65A0(int team);
void fn_800B9B64(Class_80297C60 *p, int enable, int value);
void fn_8015A0D0(int value);
void fn_8015C254(int a);
void fn_8017DC08(void);
Sample_801C009C *fn_801C009C(Actor_801C009C *bank, unsigned short id, unsigned short subId, unsigned short index);
Sample_801C009C *fn_801C00F8(Actor_801C009C *);
}

extern unsigned char lbl_803EA8BD;
extern unsigned char lbl_803EA8BE;
extern unsigned char lbl_803EA8BF;
extern unsigned char lbl_803EA8C0;
extern unsigned char lbl_803EA8C8;
extern unsigned int lbl_803EA8D0;
extern unsigned char lbl_803EA8D4;
extern Class_80297C60 *lbl_803EAB84;
extern Type_803EA368 *lbl_803EA368;

/* Steps character index's state machine (+0x38C) once and returns 0 when the
   sequence ends or cannot start. 0: wait until fn_800927BC(index) reports
   ready, clear the frame counter 0x803EA8D0. 1: count frames, start
   fn_800655B8 once, then wait for fn_80096304 (kind 1 counts as ready) and,
   when fn_800AD9B4 was 4 on entry, until the frame counter exceeds 120; when
   fn_801C009C finds no sample for the +0xE0 selection, clear its two ids and
   keep +0xE0 set only if fn_801C00F8 returns a fallback sample; then go to 2
   (flag 1, via fn_80091240), 3 (kind other than 1 with fn_800AD9B4 4, or
   fn_800AD9B4 2; starts fn_8005BE5C) or 4. 2: wait for fn_8009637C, then 3 or
   4 the same way; like 1, kind 1 counts as ready. 3: in those modes wait for
   fn_8005BFD4 to report 1, then go to 4. 4: set up the players and objects
   (fn_80091864, fn_80091AD0, fn_800916E0, fn_80090E4C, fn_80090BDC and the
   rest), pass the team of the character's first player (fn_8008FF28) to
   fn_800B9B64 when the block's +0xECF byte is set, and go to 5. 5: once
   fn_80091D34 is set or fn_80091C84 reports nothing left, hand over to 6 in
   those modes, else set 8 and return 0; until then, while fn_80091C84 reports
   a value under 15 it calls fn_8005BF98 and sets 0x803EA8C8. 6: wait for
   fn_8005BFD4 to report 1, then set 8 and return 0. States 5 and 6 return at
   once; 8's body runs on a later call. 8: for kinds up to 2 set bit 0 of the
   +0x14 word of the block at +4 of each of the 14 objects whose +0xB byte is
   set, clear 0x803EA8BD and 0x803EA8C0, and end. On an end it calls
   fn_80067E3C(0x82, ...) when fn_800737B8 is set, runs fn_800941B8 and
   fn_800941EC, calls fn_80092380(character, 0) unless fn_800AD9B4 is 7, and
   calls fn_80028DD0(1.0f). */
extern "C" int fn_80092830(int index)
{
    Character_80093BCC *pCharacter = &lbl_803EC924->mUnknown80.mCharacters[index];
    int result = 1;
    Actor_801C009C *pActor = fn_80093BAC(pCharacter->mUnknown0, pCharacter->mUnknown4);
    int single = pCharacter->mUnknown4 == 1;
    float remaining;

    switch (pCharacter->mUnknown38C) {
    case 0:
        lbl_803EA8C8 = 0;
        if (fn_800927BC(index) == 0) {
            break;
        }
        lbl_803EA8D0 = 0;
        pCharacter->mUnknown38C = 1;
    case 1: {
        int mode = fn_800AD9B4();
        int ready;

        lbl_803EA8D0++;
        if (fn_80091D34() != 0 && pCharacter->mUnknown4 != 0) {
            result = 0;
            break;
        }
        if (lbl_803EA8BE == 0 && pCharacter->mUnknown4 != 4 &&
            (pCharacter->mUnknown4 != 2 || pCharacter->mUnknown0 != 1)) {
            fn_800655B8();
            lbl_803EA8BE = 1;
        }
        ready = fn_80096304(index);
        if (single) {
            ready = 1;
        }
        if (ready == 0 || (mode == 4 && lbl_803EA8D0 <= 120)) {
            break;
        }
        fn_8009BA10(0);
        if (pCharacter->mUnknownE0.mUnknown0 != 0 &&
            fn_801C009C(pActor, 1, pCharacter->mUnknownE0.mUnknown4.mParts[1], pCharacter->mUnknownE0.mUnknown8.mParts[1]) == 0) {
            Sample_801C009C *pSample = fn_801C00F8(pActor);

            pCharacter->mUnknownE0.mUnknown4.mWord = -1;
            pCharacter->mUnknownE0.mUnknown8.mWord = -1;
            if (pSample != 0) {
                pCharacter->mUnknownE0.mUnknown0 = 1;
            } else {
                pCharacter->mUnknownE0.mUnknown0 = 0;
            }
        }
        if (pCharacter->mUnknown8 & 1) {
            fn_80091240(index);
            pCharacter->mUnknown38C = 2;
        } else if ((pCharacter->mUnknown4 != 1 && fn_800AD9B4() == 4) || fn_800AD9B4() == 2) {
            fn_8005BE5C(pCharacter->mUnknown4 == 0);
            pCharacter->mUnknown38C = 3;
            lbl_803EA8BD = 1;
        } else {
            pCharacter->mUnknown38C = 4;
        }
    }
    case 2:
        if (pCharacter->mUnknown38C == 2) {
            int done = 0;
            int ready;

            if (fn_8009637C(index) != 0 && result != 0) {
                done = 1;
            }
            ready = done;
            if (single) {
                ready = 1;
            }
            if (ready != 0) {
                if ((pCharacter->mUnknown4 != 1 && fn_800AD9B4() == 4) || fn_800AD9B4() == 2) {
                    fn_8005BE5C(pCharacter->mUnknown4 == 0);
                    pCharacter->mUnknown38C = 3;
                    lbl_803EA8BD = 1;
                } else {
                    pCharacter->mUnknown38C = 4;
                }
            } else {
                if (fn_80091D34() != 0 && pCharacter->mUnknown4 != 0) {
                    result = 0;
                }
                break;
            }
        }
    case 3:
        if ((pCharacter->mUnknown4 != 1 && fn_800AD9B4() == 4) || fn_800AD9B4() == 2) {
            if (fn_8005BFD4() == 1) {
                fn_8017DC08();
                fn_8005BF5C();
                pCharacter->mUnknown38C = 4;
                lbl_803EA8BD = 0;
            }
            break;
        }
    case 4:
        fn_8015C254(0);
        fn_8015A0D0(0);
        lbl_803EA8BF = 1;
        if (lbl_803EC924->mUnknown80.mUnknownE4F[0] != 0) {
            int team = 2;
            Character_80093BCC *pOther = fn_80093BCC(index);
            Object_80039F5C *pPlayer = fn_8008FF28(pOther, fn_80093BAC(pOther->mUnknown0, pOther->mUnknown4));

            if (pPlayer != 0 && fn_800B65A0(pPlayer->mIdBytes[2]) != 0xFF) {
                team = pPlayer->mIdBytes[2];
            }
            fn_800B9B64(lbl_803EAB84, 1, team);
            lbl_803EC924->mUnknown80.mUnknownE4F[0] = 0;
        }
        if (fn_80091864(index) == 0 || fn_80091AD0(pCharacter, pActor) == 0 || fn_800916E0(index) == 0 ||
            fn_80090E4C(index) == 0) {
            result = 0;
            break;
        }
        fn_80090BDC();
        fn_80091144(index);
        fn_80091DAC(index, lbl_803EA8D4);
        pCharacter->mUnknown38C = 5;
        fn_80092380(pCharacter, 1);
        fn_8009126C(index);
        fn_8002C9A8(lbl_803EA368, 3, 0);
    case 5:
        if (fn_80091D34() != 0 || fn_80091C84(index, &remaining) == 0) {
            if ((pCharacter->mUnknown4 != 1 && fn_800AD9B4() == 4) || fn_800AD9B4() == 2) {
                if (lbl_803EA8C8 == 0 && fn_80091D34() != 0 && fn_8005BFD4() != 3) {
                    break;
                }
                if (fn_8005BFD4() != 0) {
                    fn_8005BF98();
                }
                if (fn_800737B8() != 0) {
                    fn_80067E3C(0x82, 0, 0, 0, 0, 0);
                }
                pCharacter->mUnknown38C = 6;
                lbl_803EA8BD = 1;
            } else {
                pCharacter->mUnknown38C = 8;
                result = 0;
            }
        } else if (((pCharacter->mUnknown4 != 1 && fn_800AD9B4() == 4) || fn_800AD9B4() == 2) &&
                   fn_8005BFD4() != 0 && remaining < 15.0f) {
            fn_8005BF98();
            lbl_803EA8C8 = 1;
        }
        break;
    case 6:
        if (fn_8005BFD4() == 1) {
            fn_8005BF18();
            pCharacter->mUnknown38C = 8;
            lbl_803EA8BD = 0;
            result = 0;
        }
        break;
    case 7:
        break;
    case 8:
        if ((unsigned int)pCharacter->mUnknown4 <= 2) {
            unsigned short i;

            for (i = 0; i < 14; i++) {
                Object_80039F5C *p = fn_8003E0C8((Block_80170E64 *)fn_8003DEC4(i));

                if (p->mUnknown9[2] != 0) {
                    p->mpUnknown4->mUnknown20 |= 1;
                }
            }
        }
        result = 0;
        lbl_803EA8BD = 0;
        lbl_803EA8C0 = 0;
        break;
    }
    if (result == 0) {
        if (fn_800737B8() != 0) {
            fn_80067E3C(0x82, 0, 0, 0, 0, 0);
        }
        fn_800941B8();
        fn_800941EC();
        if (fn_800AD9B4() != 7) {
            fn_80092380(pCharacter, 0);
        }
        fn_80028DD0(1.0f);
    }
    return result;
}
