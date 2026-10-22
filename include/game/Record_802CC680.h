#ifndef GAME_RECORD_802CC680_H
#define GAME_RECORD_802CC680_H

typedef struct Record_802CC680 {
    char mName[8];
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    int mUnknown14;
} Record_802CC680;

#ifdef __cplusplus
extern "C" {
#endif
Record_802CC680 *fn_80025E50(unsigned int id);
#ifdef __cplusplus
}
#endif

#endif
