#include "game/Object_80039F5C.h"

extern "C" {

void fn_8011E7CC(Object_80039F5C *p, int which, float amount)
{
    Block_8011DBC8 *pBlock = &p->mUnknown1072;

    switch (which) {
    case 0:
        pBlock->mUnknown40 += amount;
        pBlock->mUnknown40 = pBlock->mUnknown40 < 0.0f ? 0.0f : pBlock->mUnknown40;
        break;
    case 1:
        pBlock->mUnknown44 += amount;
        pBlock->mUnknown44 = pBlock->mUnknown44 < 0.0f ? 0.0f : pBlock->mUnknown44;
        break;
    case 2:
        pBlock->mUnknown48 += amount;
        pBlock->mUnknown48 = pBlock->mUnknown48 < 0.0f ? 0.0f : pBlock->mUnknown48;
        break;
    }
}

}
