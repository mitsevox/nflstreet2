#ifndef GAME_PLAYERSAVE_H
#define GAME_PLAYERSAVE_H

/* Seven-word stream operation table, the shape of the CardStream table at 0x802F46C4. */
struct SaveStreamOps_t {
    int (*mpOpen)(void *pStream, int a, int target, unsigned char reading);
    int (*mpClose)(void *pStream);
    int (*mpRead)(void *pStream, void *pData, unsigned int size, unsigned int *pDone);
    int (*mpWrite)(void *pStream, void *pData, unsigned int size, unsigned int *pDone);
    void (*mpUnknown10)(void *pStream, unsigned int count);
    int (*mpUnknown14)(unsigned int size);
    unsigned int mUnknown18;
};

struct SaveRequest_t {
    char mUnknown0[12];
    int mTarget;
    unsigned char mUnknown10;
};

/* src/game/PlayerSave.cpp */
extern "C" {
int PlayerSaveOnSave(SaveRequest_t *pRequest, SaveStreamOps_t *pOps);
void PlayerSaveFree(void);
int PlayerSavePrepare(int a, int b);
}

#endif
