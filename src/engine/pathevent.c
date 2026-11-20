/* PATH events (pathevent.c): queues music events from the game, filters and releases them and
   services the event queue each tick. */

#include "engine/pathlib.h"

extern "C" int fn_801B5E5C(int flags, Sequence_801B84E4 *sequence)
{
    int result = -8;
    Event_801B845C *entry = sequence->mUnknown14;
    int depth = 0;
    unsigned int high = flags & 0xFF000000;
    for (unsigned int i = 0; i < sequence->mUnknownF; ++i, ++entry) {
        if ((entry->mUnknown4 & 0x00FE0000) == 0x00020000) {
            switch ((entry->mUnknown4 >> 9) & 7) {
            case 0:
            case 1:
                entry->mBits4.depth = depth++;
                break;
            case 2:
            case 3:
                entry->mBits4.depth = depth - 1;
                break;
            case 4:
                entry->mBits4.depth = --depth;
                break;
            default:
                break;
            }
        } else {
            entry->mBits4.depth = depth;
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (lbl_802F47D0[i] && (lbl_802F47D0[i]->mUnknown14 & high) == lbl_802F47D0[i]->mUnknown14) {
            int count = lbl_802F47D0[i]->mUnknown1100;
            if (count > 15)
                return -13;
            result = 0;
            unsigned int now = lbl_803EBB60->vfn_05();
            sequence->mUnknown8 = now;
            sequence->mUnknown0 = now;
            lbl_802F47D0[i]->mUnknownC0[count++] = sequence;
            lbl_802F47D0[i]->mUnknown1100 = count;
        }
    }
    return result;
}

extern "C" void fn_801B6334(Sequence_801B84E4 *p)
{
    for (int i = 0; i < 4; ++i) {
        Bank_801B3480 *bank = lbl_802F47D0[i];
        if (bank) {
            for (int j = 0; j <= 16; ++j) {
                if (bank->mUnknownC0[j] == p) {
                    bank->mUnknownC0[j] = 0;
                    --bank->mUnknown1100;
                    for (++j; j < 16; ++j)
                        bank->mUnknownC0[j - 1] = bank->mUnknownC0[j];
                }
            }
        }
    }
}

extern "C" void fn_801B63F0(Entry_801B63F0 *p, int value)
{
    Header_801B2CDC *base = lbl_803EBB28->mUnknown18;
    unsigned int key = p->mUnknownC >> 8;
    short *offsets = lbl_803EBB28->mUnknown24;
    Entry_801B63F0 *found = 0;
    for (int i = base->mUnknownF - 1; i >= 0; --i) {
        Entry_801B63F0 *entry = (Entry_801B63F0 *)((unsigned char *)base + offsets[i] * 4);
        if ((entry->mUnknownC >> 8) == key) {
            found = entry;
            break;
        }
    }
    if (found)
        found->mUnknown10.bits.flag4000 = value;
}

extern "C" void fn_801B6460(void)
{
    for (int i = 0; i < lbl_803EBB28->mUnknown18->mUnknownF; ++i) {
        Entry_801B63F0 *entry = (Entry_801B63F0 *)((unsigned char *)lbl_803EBB28->mUnknown18 + lbl_803EBB28->mUnknown24[i] * 4);
        if (entry)
            entry->mUnknown10.bits.flag4000 = 0;
    }
}

extern "C" int fn_801B64C0(int index)
{
    Sequence_801B84E4 *p = lbl_803EBB28->mUnknownC0[index];
    int count = 0;
    if (p->mUnknown8 > lbl_803EBB3C)
        return 0;
    unsigned int i = p->mUnknown10;
    Event_801B845C *entry = &p->mUnknown14[i];
    for (; i < p->mUnknownF; ++i, ++entry) {
        if (!(entry->mUnknown4 & 0x10000) && !fn_801B7880(p, entry))
            break;
        ++count;
        ++p->mUnknown10;
        p->mUnknown8 = lbl_803EBB3C;
    }
    return count;
}
