#ifndef ENGINE_SPCHEVNT_H
#define ENGINE_SPCHEVNT_H

/* Declarations of src/engine/spchevnt.c used by several game units. */
struct SpchEventKey_t {
    unsigned short mId;
    unsigned char mUnknown2;
    unsigned char mUnknown3;
};
extern "C" {
extern int (*gSPCH_AddEvent)(int, int, ...);

int SPCH_MakeEventSpec(int a, int b, int c);
void SPCH_PlayLastEvent(unsigned int channel);
int SPCH_Play(unsigned int channel);
}

#endif
