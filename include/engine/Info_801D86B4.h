#ifndef ENGINE_INFO_801D86B4_H
#define ENGINE_INFO_801D86B4_H

/* Movie player record of src/engine/cu_801D86B4.cpp, shared with C callers. */
typedef struct Info_801D86B4 {
    struct Video_801D86B4 *mpVideo;
    struct Audio_801D86B4 *mpAudio;
    int mCodec;
} Info_801D86B4;

struct Frame_801D86B4;

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/cu_801D86B4.cpp */
void fn_801D8A2C(Info_801D86B4 *pInfo, void *pStream);
void fn_801D8B54(Info_801D86B4 *pInfo);
int fn_801D8BC8(Info_801D86B4 *pInfo, void *pStream, int volume);
void fn_801D8C84(Info_801D86B4 *pInfo);
int fn_801D900C(Info_801D86B4 *pInfo);
unsigned int fn_801D9224(Info_801D86B4 *pInfo);
unsigned int fn_801D9230(Info_801D86B4 *pInfo);
struct Frame_801D86B4 *fn_801D923C(Info_801D86B4 *pInfo, unsigned int frame);
void fn_801D9290(Info_801D86B4 *pInfo, struct Frame_801D86B4 *pFrame);
void fn_801D92B8(struct Frame_801D86B4 *pFrame, unsigned char **ppY, unsigned char **ppU,
                 unsigned char **ppV);
void fn_801D9320(struct Frame_801D86B4 *pFrame, int *pWidth, int *pHeight);

#ifdef __cplusplus
}
#endif

#endif
