#ifndef GAME_FN_801FCE10_H
#define GAME_FN_801FCE10_H

struct QueryResult {
    unsigned short mUnknown0;
    short mUnknown2;
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknown12[4];
};

struct QueryCursor {
    int mUnknown0;
    short mUnknown4;
    int mUnknown8;
    void *mUnknown12;
};

#ifdef __cplusplus
extern "C" {
#endif

int fn_801FCE10(void *pResult, const char *pQuery, ...);
int fn_801FCFA0(struct QueryCursor *pCursor);

#ifdef __cplusplus
}
#endif

#endif
