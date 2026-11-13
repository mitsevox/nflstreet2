/* Exchanges the pending message, the message queue and four state blocks of
   two players; part of swapping two players on the field. */
#include "game/Object_80039F5C.h"
#include "game/Message_800F01CC.h"

extern "C" {
void fn_801D31F0(void *pDst, const void *pSrc, int size);

void PlyrSwapStateData(Object_80039F5C *pA, Object_80039F5C *pB)
{
    Message_800F01CC message;
    State_80039F5C queue[10];
    unsigned char state[88];
    unsigned char block1244[12];
    unsigned char block1256[1240];
    unsigned char block2496[404];
    unsigned char *pBytesA = (unsigned char *)pA;
    unsigned char *pBytesB = (unsigned char *)pB;

    fn_801D31F0(&message, pA->mUnknown3044, sizeof(message));
    fn_801D31F0(pA->mUnknown3044, pB->mUnknown3044, sizeof(message));
    fn_801D31F0(pB->mUnknown3044, &message, sizeof(message));
    fn_801D31F0(queue, pA->mQueue, sizeof(queue));
    fn_801D31F0(pA->mQueue, pB->mQueue, sizeof(queue));
    fn_801D31F0(pB->mQueue, queue, sizeof(queue));
    fn_801D31F0(state, pBytesA + 336, sizeof(state));
    fn_801D31F0(pBytesA + 336, pBytesB + 336, sizeof(state));
    fn_801D31F0(pBytesB + 336, state, sizeof(state));
    fn_801D31F0(block1244, pBytesA + 1244, sizeof(block1244));
    fn_801D31F0(pBytesA + 1244, pBytesB + 1244, sizeof(block1244));
    fn_801D31F0(pBytesB + 1244, block1244, sizeof(block1244));
    fn_801D31F0(block1256, pBytesA + 1256, sizeof(block1256));
    fn_801D31F0(pBytesA + 1256, pBytesB + 1256, sizeof(block1256));
    fn_801D31F0(pBytesB + 1256, block1256, sizeof(block1256));
    fn_801D31F0(block2496, pBytesA + 2496, sizeof(block2496));
    fn_801D31F0(pBytesA + 2496, pBytesB + 2496, sizeof(block2496));
    fn_801D31F0(pBytesB + 2496, block2496, sizeof(block2496));
}
}
