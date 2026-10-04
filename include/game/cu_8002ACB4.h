#ifndef GAME_CU_8002ACB4_H
#define GAME_CU_8002ACB4_H

/* Seven-word stream operation table, the shape of the CardStream table at 0x802F46C4. */
struct StreamOps_8002ACB4 {
    int (*mpOpen)(void *pStream, int a, int target, unsigned char reading);
    int (*mpClose)(void *pStream);
    int (*mpRead)(void *pStream, void *pData, unsigned int size, unsigned int *pDone);
    int (*mpWrite)(void *pStream, void *pData, unsigned int size, unsigned int *pDone);
    void (*mpUnknown10)(void *pStream, unsigned int count);
    int (*mpUnknown14)(unsigned int size);
    unsigned int mUnknown18;
};

struct Request_8002AD64 {
    char mUnknown0[12];
    int mTarget;
    unsigned char mUnknown10;
};

/* src/game/cu_8002ACB4.cpp */
extern "C" {
int fn_8002AD64(Request_8002AD64 *pRequest, StreamOps_8002ACB4 *pOps);
void fn_8002ADAC(void);
int fn_8002ADE0(int a, int b);
}

#endif
