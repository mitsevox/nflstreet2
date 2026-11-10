#ifndef GAME_STYLE_AWARD_RULE_H
#define GAME_STYLE_AWARD_RULE_H

struct StyleAwardRule_t {
    unsigned char mEnabled;
    unsigned char mApply;
    unsigned char mAllowZero;
    int mPoints;
    int unk_0x8;
    int mMeterSteal;
    int mScoreDelta;
    int mTableIndex;
    float mOpponentDistance;
    int mOpponentAngle;
    int mComboWeight;
    unsigned char mAllowBehindLine;
    int mCategory;
    int mComboLabel;
    int mMessage;
};

#endif
