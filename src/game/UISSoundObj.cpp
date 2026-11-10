/* UI Studio sound object: the front-end screen object that plays a menu sound effect,
   picked from a table by sound group and index, when the screen sends it a message. */
#include "game/Object_80039F5C.h"

struct UISSoundArgs_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
};

extern "C" {
int SndgSfxPlay(int index, Vector_80039F5C *pPos);

void UISSoundObjCreate(void *p);
void UISSoundObjDraw(void *p);
void UISSoundObjPlay(int group, unsigned int index);
void UISSoundObjDestroy(void *p);
void UISSoundObjAction(void *p, unsigned int message, int a, UISSoundArgs_t *pArgs);
}

static int _UISSoundObj_aiGroup0Sounds[23] = {
    0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x91,
    0x91, 0x91, 0x91, 0x91, 0x79, 0x7A, 0x7B, 0x7C,
    0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83
};

static int _UISSoundObj_aiGroup13Sounds[9] = {
    0x91, 0x91, 0x91, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90
};

extern "C" void UISSoundObjCreate(void *p)
{
}

extern "C" void UISSoundObjDraw(void *p)
{
}

extern "C" void UISSoundObjPlay(int group, unsigned int index)
{
    int id;

    if (group == 0 || group == 13) {
        if ((group == 0 && index <= 22) || (group == 13 && index <= 8)) {
            if (group == 0) {
                id = _UISSoundObj_aiGroup0Sounds[index];
            } else {
                id = _UISSoundObj_aiGroup13Sounds[index];
            }
            SndgSfxPlay(id, 0);
        }
    }
}

extern "C" void UISSoundObjDestroy(void *p)
{
}

extern "C" void UISSoundObjAction(void *p, unsigned int message, int a, UISSoundArgs_t *pArgs)
{
    if (p != 0) {
        switch (message) {
        case -1:
            UISSoundObjCreate(p);
            break;
        case -2:
            UISSoundObjDraw(p);
            break;
        case -3:
            UISSoundObjDestroy(p);
            break;
        case 0:
            UISSoundObjPlay(pArgs->mUnknown0, pArgs->mUnknown2);
            break;
        }
    }
}
