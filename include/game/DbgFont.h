#ifndef GAME_DBGFONT_H
#define GAME_DBGFONT_H

extern "C" {
void DbgFontLoadTexture(void);
void DbgFontInit(void);
void DbgFontShutdown(void);
void DbgFontSetEnabled(unsigned short value);
void DbgFontSetColor(unsigned char r, unsigned char g, unsigned char b);
int DbgFontPrint(int x, unsigned short y, int c, char *pText, int e);
}

#endif
