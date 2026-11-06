#ifndef GAME_ANIMDEQUANTIZE_H
#define GAME_ANIMDEQUANTIZE_H

struct AnimQuantTables {
    short *mUnknown0;
    short *mUnknown4;
};

#ifdef __cplusplus
extern "C" {
#endif
int AnimDequantize(int value, int index, int component, void *pContext, struct AnimQuantTables *pPair);
#ifdef __cplusplus
}
#endif

#endif
