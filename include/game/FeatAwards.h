#ifndef GAME_FEATAWARDS_H
#define GAME_FEATAWARDS_H

/* 168-byte entry allocated through fn_801D2B7C and kept in _Feat_apAwarded. */
struct FeatAward {
    char mName[132];
    char mText[32];
    int mUnknown164;
};

extern "C" {
void FeatAwardEAGameSaveFeats(void);
void FeatAwardNewUserFeats(void);
void FeatAwardAllUsersFeat(void);
unsigned int FeatGetAwardedCount(void);
void FeatGetAwarded(int index, FeatAward *pEntry);
void FeatClearAwarded(void);
int FeatAwardCurrentUserModeFeat(FeatAward *pEntry);
}

#endif
