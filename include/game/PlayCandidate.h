#ifndef GAME_PLAYCANDIDATE_H
#define GAME_PLAYCANDIDATE_H

/* One 12-byte candidate passed with its count to PlayTrackWeightCandidates; the
   halfword at +4 is the weight that PlayTrackWeightOffense, PlayTrackWeightDefense, PlayTrackFilterByMode
   and PlayTrackFilterByChallenge rescale or clear. PlayBookDbPickAIPlay fills the list from a query, sorts it by that weight
   and draws an entry with fn_802372EC weighted by it. */
struct PlayCandidate_t {
    unsigned int mUnknown0;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    unsigned char mUnknown8;
};

#endif
