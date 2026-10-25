#ifndef GAME_REQUEST_802329F0_H
#define GAME_REQUEST_802329F0_H

/* Argument block passed to fn_802329F0 with the file name template.dat. */
struct Request_802329F0 {
    int mMode;
    int mSize;
    const char *mpName;
    int mCount;
};

#ifdef __cplusplus
extern "C" {
#endif
int fn_802329F0(struct Request_802329F0 *pRequest);
#ifdef __cplusplus
}
#endif

#endif
