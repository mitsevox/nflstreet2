#ifndef GAME_REQUEST_802329F0_H
#define GAME_REQUEST_802329F0_H

/* Argument block passed to fn_802329F0 with the file name template.dat. */
struct Request_802329F0 {
    int mMode;
    int mSize;
    const char *mpName;
    int mCount;
};

extern "C" void fn_802329F0(Request_802329F0 *pRequest);

#endif
