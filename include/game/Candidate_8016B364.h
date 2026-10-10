#ifndef GAME_CANDIDATE_8016B364_H
#define GAME_CANDIDATE_8016B364_H

/* One 12-byte candidate passed with its count to fn_8016B364; the
   halfword at +4 is the weight that fn_8016A7DC, fn_8016A9B4, fn_8016AC24
   and fn_8016ACD8 rescale or clear. fn_80067690 fills the list from a query, sorts it by that weight
   and draws an entry with fn_802372EC weighted by it. */
struct Candidate_8016B364 {
    unsigned int mUnknown0;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    unsigned char mUnknown8;
};

#endif
