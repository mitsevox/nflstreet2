/* Banner module: six timed on-screen banners with two 64-character text lines each, held in the 'bnnr' block; cleared, timed out per tick and given text by the game. */
#include <string.h>
#include "game/fn_80238174.h"

/* One of the six 0x90-byte entries of BannerSet_t. */
struct Banner_t {
    unsigned char mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    float mUnknown8;
    float mUnknownC;
    char mText[2][64];
};

/* The six banners, allocated under the id 'bnnr'. */
struct BannerSet_t {
    Banner_t mEntries[6];
};

extern "C" {
void *fn_8023816C(void *pHandle);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
}

static BannerSet_t *_Banner_pSet;
static unsigned int _Banner_uTickMs = 1;

extern "C" {

void BannerClear(int index);

int BannerCompare(void *p, void *q)
{
    BannerSet_t *pA = (BannerSet_t *)p;
    BannerSet_t *pB = (BannerSet_t *)q;
    int result = 0;
    unsigned int i;

    if (pB != 0) {
        /* Only the fields before the text are compared. */
        for (i = 0; i <= 5; i++) {
            result |= fn_80238258(&pA->mEntries[i], &pB->mEntries[i], 16);
        }
    } else {
        return 0;
    }
    return result;
}

void BannerAlloc(void)
{
    void *pHandle = fn_80238174(0, (void **)&_Banner_pSet, sizeof(BannerSet_t), 0, 0x626E6E72);
    BannerSet_t *pSet;
    unsigned int i;
    unsigned int j;

    fn_80238234(pHandle, 0, 0, 0, BannerCompare);
    pSet = (BannerSet_t *)fn_8023816C(pHandle);
    for (i = 0; i <= 5; i++) {
        pSet->mEntries[i].mUnknown0 = 0;
        pSet->mEntries[i].mUnknown2 = 0;
        pSet->mEntries[i].mUnknown4 = 0;
        pSet->mEntries[i].mUnknown8 = 0.0f;
        pSet->mEntries[i].mUnknownC = 0.0f;
        for (j = 0; j <= 1; j++) {
            strcpy(pSet->mEntries[i].mText[j], "");
        }
    }
    fn_802381E0(pHandle);
}

void BannerClearAll(void)
{
    BannerClear(7);
}

void BannerSetTickMs(unsigned int value)
{
    _Banner_uTickMs = value;
}

int BannerUpdate(float step)
{
    int i;

    for (i = 0; i <= 5; i++) {
        if (_Banner_pSet->mEntries[i].mUnknown0 && _Banner_pSet->mEntries[i].mUnknown8 != 0.0f) {
            _Banner_pSet->mEntries[i].mUnknownC += step;
            if (_Banner_pSet->mEntries[i].mUnknownC > _Banner_pSet->mEntries[i].mUnknown8) {
                BannerClear(i);
                if (i == 3 && _Banner_pSet->mEntries[5].mUnknown8 != 0.0f) {
                    BannerClear(5);
                    _Banner_pSet->mEntries[5].mUnknown0 = 1;
                }
            }
        }
    }
    return 0;
}

void BannerEnd(void)
{
}

void BannerShow(unsigned short, unsigned short, int, int)
{
}

void BannerClear(int index)
{
    int i;
    int j;

    if (index == 7) {
        for (i = 0; i <= 5; i++) {
            BannerClear(i);
        }
    } else if (_Banner_pSet->mEntries[index].mUnknown0) {
        for (j = 0; j < 2; j++) {
            strcpy(_Banner_pSet->mEntries[index].mText[j], "");
        }
        _Banner_pSet->mEntries[index].mUnknown0 = 0;
        _Banner_pSet->mEntries[index].mUnknown8 = 0.0f;
    }
}

int BannerIsActive(int index)
{
    int result = 0;
    int i;

    if (index == 7) {
        for (i = 0; i < 6; i++) {
            result |= _Banner_pSet->mEntries[i].mUnknown0;
        }
    } else {
        result = _Banner_pSet->mEntries[index].mUnknown0;
    }
    return result;
}

void BannerSetText(int index, int line, const char *pText)
{
    strcpy(_Banner_pSet->mEntries[index].mText[line], pText);
}

}
