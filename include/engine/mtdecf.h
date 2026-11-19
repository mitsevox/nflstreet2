#ifndef ENGINE_MTDECF_H
#define ENGINE_MTDECF_H

namespace Snd {

/* The MT (MicroTalk) decode state: the bit reader (+0x0 byte pointer, +0x4 bit buffer, +0x8 bit
   count), the stream header (+0xC reduced-bandwidth flag, +0x10 multi-pulse threshold, +0x14 the 64
   fixed gains), the 12 reflection coefficients +0x114, the 12-sample synthesis history +0x144, the
   324-sample adaptive codebook +0x174 and the 432-sample decoded frame +0x684 that follows it. */
struct UTALKSTATE_CODA {
    unsigned char *m0;
    unsigned int m4;
    int m8;
    int mC;
    int m10;
    float m14[64];
    float m114[12];
    float m144[12];
    float m174[324];
    float m684[432];
};

/* The decoder state the MT unpack filters save and restore around a loop jump: the bit buffer +0x4,
   the samples left in the current frame +0xD44 and the header word +0xD5C. */
struct MTFSTATE {
    int m0;
    int m4;
    int m8;
};

/* 3432-byte MT block decoder used by the MT unpack filters in src/engine/supmutf.c,
   src/engine/supmutlf.c and src/engine/supmutpf.c: the decode state, then the delivery fields
   +0xD44-+0xD67. */
class CMTBLKDecf : public UTALKSTATE_CODA {
public:
    static void *operator new(unsigned int size);
    static void operator delete(void *p);
    CMTBLKDecf();
    int Feed(void *data, int size, int count);
    int Decode(float **dst, int count);
    MTFSTATE GetState();
    void SetState(MTFSTATE *state, int flags);
    void SetCodecVersion(int version);
    void initmut(unsigned char *data, UTALKSTATE_CODA *state, int header);

    int mD44;
    unsigned char *mD48;
    float *mD4C;
    short mD50;
    short mD52;
    int mD54;
    int mD58;
    int mD5C;
    int mD60;
    int mD64;
};

}

#endif
