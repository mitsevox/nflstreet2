/* Checks a player's face-feature choices against a list of disallowed values (empty in this game). */
#include "game/FaceFeatures.h"

/* Ints that must not appear among the ten block words, ended by 0xFFFF; the list holds only
   the terminator, so the result is always 1. */
static const int _FaceMorph_aExcluded[] = { 0xFFFF };

int FaceMorphIsAllowed(FaceFeatures_t *pBlock) {
    int result = 1;
    int i;
    int j;
    int *pWords = pBlock->mUnknown0;

    for (i = 0; _FaceMorph_aExcluded[i] != 0xFFFF; i++) {
        for (j = 0; j < 10; j++) {
            if (_FaceMorph_aExcluded[i] == pWords[j]) {
                result = 0;
                break;
            }
        }
    }
    return result;
}
