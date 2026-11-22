#ifndef GAME_TDBCOMPILEPERFORMOP_H
#define GAME_TDBCOMPILEPERFORMOP_H

struct QueryResult {
    unsigned short mUnknown0;
    short mUnknown2;
    int mUnknown4;
    int mUnknown8;
    unsigned char mUnknown12[4];
};

struct QueryCursor {
    int mUnknown0;
    unsigned short mUnknown4;
    int mUnknown8;
    void *mUnknown12;
};

#ifdef __cplusplus
extern "C" {
#endif

int TDbCompilePerformOp(void *pResult, const char *pQuery, ...);
int TDbSQLDestroyCursor(struct QueryCursor *pCursor);

#ifdef __cplusplus
}
#endif

#endif
