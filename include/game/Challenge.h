#ifndef GAME_CHALLENGE_H
#define GAME_CHALLENGE_H

/* Eight-byte entry of the two-entry list at +500 of Challenge_t:
   ChalHasReward compares mId, and ChalFormatRewards passes mUnknown4 on to
   ChalFormatReward. */
struct ChalReward_t {
    int mId;
    unsigned short mUnknown4;
    char mUnknown6[2];
};

/* 12-byte entry of the four-entry list at +452 of Challenge_t:
   ChallengeEvaluateGoal dispatches on mType and passes mValue to the selected test,
   and ChallengeGetGoalTexts skips entries whose mUnknown8 is zero. */
struct ChalGoal_t {
    int mType;
    unsigned int mValue;
    unsigned char mUnknown8;
    char mUnknown9[3];
};

/* 40-byte block at +524 of Challenge_t; ChalHasMedalGoal tests mUnknown0. */
struct ChalMedalGoal_t {
    int mUnknown0;
    unsigned int mUnknown4[3];
    char *mUnknown10[3];
    int mUnknown1C;
    unsigned short mUnknown20[3];
    char mUnknown26[2];
};

/* Record that ChalReadRecord clears and fills; ChalGetCurrent returns the challenge
   being played (_Chal_sCurrent). Only the accessed fields are declared. */
struct Challenge_t {
    unsigned char mUnknown0;
    char mUnknown1[202];
    char mUnknownCB[203];
    unsigned short mUnknown196;
    unsigned char mUnknown198;
    char mUnknown199[3];
    int mUnknown19C;
    int mUnknown1A0;
    unsigned short mUnknown1A4;
    unsigned char mUnknown1A6;
    unsigned char mUnknown1A7;
    int mUnknown1A8;
    int mUnknown1AC;
    int mUnknown1B0;
    int mUnknown1B4;
    int mUnknown1B8;
    int mUnknown1BC;
    signed char mUnknown1C0;
    unsigned char mUnknown1C1;
    char mUnknown1C2;
    unsigned char mUnknown1C3;
    ChalGoal_t mUnknown1C4[4];
    ChalReward_t mUnknown1F4[2];
    unsigned char mUnknown204;
    char mUnknown205[3];
    int mUnknown208;
    ChalMedalGoal_t mUnknown20C;
};

extern "C" {
Challenge_t *ChalGetCurrent(void);
}

#endif
