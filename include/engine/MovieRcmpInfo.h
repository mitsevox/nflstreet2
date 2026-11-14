#ifndef ENGINE_MOVIERCMPINFO_H
#define ENGINE_MOVIERCMPINFO_H

/* Movie player record of src/engine/moviercmp.cpp, shared with C callers. */
typedef struct MovieRcmpInfo_t {
    struct MovieRcmpVideoInfo_t *mpVideo;
    struct MovieRcmpAudioInfo_t *mpAudio;
    int mCodec;
} MovieRcmpInfo_t;

struct RcmpFrame_t;

#ifdef __cplusplus
extern "C" {
#endif

/* src/engine/moviercmp.cpp */
void MovieRcmpInitVideo(MovieRcmpInfo_t *pInfo, void *pStream);
void MovieRcmpShutdownVideo(MovieRcmpInfo_t *pInfo);
int MovieRcmpInitAudio(MovieRcmpInfo_t *pInfo, void *pStream, int volume);
void MovieRcmpShutdownAudio(MovieRcmpInfo_t *pInfo);
int MovieRcmpIsDecodeTime(MovieRcmpInfo_t *pInfo);
unsigned int MovieRcmpGetGoalFrame(MovieRcmpInfo_t *pInfo);
unsigned int MovieRcmpGetCurFrame(MovieRcmpInfo_t *pInfo);
struct RcmpFrame_t *MovieRcmpGetFrame(MovieRcmpInfo_t *pInfo, unsigned int frame);
void MovieRcmpReleaseFrame(MovieRcmpInfo_t *pInfo, struct RcmpFrame_t *pFrame);
void MovieRcmpGetDataFromFrame(struct RcmpFrame_t *pFrame, unsigned char **ppY, unsigned char **ppU,
                               unsigned char **ppV);
void MovieRcmpGetSizeFromFrame(struct RcmpFrame_t *pFrame, int *pWidth, int *pHeight);

#ifdef __cplusplus
}
#endif

#endif
