#ifndef ENGINE_RENDER_802353F8_H
#define ENGINE_RENDER_802353F8_H

/* Object of 0xC0 bytes shared by src/engine/cu_8022F428.c and src/engine/cu_802355E4.c;
   set up by fn_80235588 and released by fn_802355E4. */
typedef struct Render_802353F8 {
    int mUnknown0;
    int mUnknown4;
    float mUnknown8[4][4];
    float mUnknown72;
    char mUnknown76[8];
    void *mpUnknown84;
    void *mpUnknown88;
    char mUnknown92[8];
    char mUnknown100[8];
    struct Shader_80235630 *mpUnknown108;
    char mUnknown112[40];
    char mUnknown152[32];
    int mUnknown184;
    float mUnknown188;
} Render_802353F8;

#ifdef __cplusplus
extern "C" {
#endif

void fn_802353D4(Render_802353F8 *p, int flags);
void fn_802353D8(Render_802353F8 *p, int flags);
void fn_802353E8(Render_802353F8 *p, int flags);

#ifdef __cplusplus
}
#endif

#endif
