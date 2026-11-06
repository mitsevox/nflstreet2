#ifndef ENGINE_VIEWPORTTYPES_H
#define ENGINE_VIEWPORTTYPES_H

typedef struct Viewport_t Viewport_t;
typedef struct ViewportDesc_t ViewportDesc_t;

/* Callback stored at +60 and called with the object and the pointer at +64. */
typedef void (*VptCameraFuncT)(Viewport_t *pObject, void *arg);

/* Object returned by VptOpen: a 248-byte element of the pool created by VptInit. */
struct Viewport_t {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    float mUnknown20;
    float mUnknown24;
    unsigned int mUnknown28;
    float mUnknown32;
    float mUnknown36;
    float mUnknown40;
    char mUnknown44[2];
    unsigned char mUnknown46;
    unsigned char mUnknown47;
    int mUnknown48[3];
    VptCameraFuncT mUnknown60;
    void *mUnknown64;
    unsigned char mUnknown68;
    unsigned char mUnknown69;
    int mUnknown72;
    float mUnknown76[4][4];
    char mUnknown140[64];
    float mUnknown204;
    float mUnknown208;
    char mUnknown212[4];
    float mUnknown216;
    float mUnknown220;
    float mUnknown224;
    float mUnknown228;
    float mUnknown232;
    float mUnknown236;
    float mUnknown240;
    char mUnknown244[4];
};

/* Argument of VptOpen. */
struct ViewportDesc_t {
    unsigned short mUnknown0;
    char mUnknown2;
    unsigned char mUnknown3;
    int mUnknown4[3];
    unsigned short mUnknown16;
    unsigned short mUnknown18;
};

#endif
