#ifndef GAME_FEATAWARDS_H
#define GAME_FEATAWARDS_H

/* 168-byte entry allocated through fn_801D2B7C and kept in _Feat_apAwarded. */
struct FeatAward_t {
    char mName[132];
    char mText[32];
    int mCredits;
};

extern "C" {
void FeatAwardEAGameSaveFeats(void);
void FeatAwardNewUserFeats(void);
void FeatAwardAllUsersFeat(void);
unsigned int FeatGetAwardedCount(void);
void FeatGetAwarded(int index, FeatAward_t *pEntry);
void FeatClearAwarded(void);
int FeatAwardCurrentUserModeFeat(FeatAward_t *pEntry);
}

#endif
