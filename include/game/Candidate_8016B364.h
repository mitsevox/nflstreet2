#ifndef GAME_CANDIDATE_8016B364_H
#define GAME_CANDIDATE_8016B364_H

/* One 12-byte candidate passed with its count to fn_8016B364; the
   halfword at +4 is the weight these functions rescale or clear.
   fn_80067690 fills the list from a query, sorts it by that weight and
   picks one entry at random in proportion to it. */
struct Candidate_8016B364 {
    unsigned int mUnknown0;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    unsigned char mUnknown8;
};

#endif
