#ifndef GAME_OBJECT_80193F84_H
#define GAME_OBJECT_80193F84_H

struct Object_80193F84 {
    int mUnknown0;
    int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
    char mUnknownC[4];
    int mUnknown10;
    void *mpUnknown14;
    char mUnknown18[16];
    unsigned char mUnknown28;
    int mUnknown2C;
    int mUnknown30;
    char mUnknown34[4];
    long long mUnknown38;
};

extern "C" {
void fn_80193E7C(Object_80193F84 *p);
void fn_80193EF0(Object_80193F84 *p, int a, int b, int c, const char *pName);
void fn_80193F2C(Object_80193F84 *p);
void fn_80193F84(Object_80193F84 *p);
}

#endif
