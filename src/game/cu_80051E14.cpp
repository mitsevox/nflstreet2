/* Object handlers that start the object's animation on placement, restore its
   saved state and pass a hit on to the entries of its node list whose names
   match, and a chain of "RIGHT"/"LEFT" linked objects that start their
   animations in turn. */
#include "game/Object_80040818.h"

/* The two linked objects at Object_80041904 +420 of a chained object. */
struct Pair_80052130 {
    Object_80040818 *mpLeft;
    Object_80040818 *mpRight;
};

extern "C" {
void fn_8004AF84(Extra_8004149C *pExtra);
void fn_8004CBEC(void *p, float value, Object_80041904 *pObject, Object_80040818 *pItem);
void fn_8004E090(Object_80040818 *pItem, int a, int b);
Object_80040818 *fn_8004117C(int key);
void fn_800411C8(Object_80040818 *pItem);
void fn_800411EC(Object_80040818 *pItem);
void fn_80067E3C(int type, Vector_80039F5C *pPos, int id, int a, int b, int c);
int fn_801784C4(void);
int fn_801BE068(void *pA, void *pB, void *pC, unsigned short key, float value, void *p);
int fn_801BE648(void *p);
void fn_801BE67C(void *pA, void *pB, void *pC, void *p);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int fn_801C2FE4(const char *pText0, const char *pText1);
char *fn_801C310C(char *pText, const char *pPattern);
unsigned int fn_801C3180(const char *pText);
char *fn_801C32CC(char *pText);
}

static inline void StartAnim(Object_80041904 *pObject, unsigned short key, float value)
{
    fn_8004AF84(pObject->mUnknown428);
    Extra_8004149C *pExtra = pObject->mUnknown428;
    fn_801BE068(pExtra->mUnknown1300, pExtra->mUnknown48, pExtra->mUnknown60, key, value, pObject);
}

extern "C" {
int fn_80051E14(Object_80041904 *pObject, Object_80040818 *pItem, int mode)
{
    Extra_8004149C *pExtra = pObject->mUnknown428;

    if (mode == 0) {
        if (pObject->mUnknown196.mValue != -1) {
            StartAnim(pObject, pObject->mUnknown196.mParts.mKey, 1.0f);
        }
    } else if (mode == 2) {
        pObject->mUnknown8 = pObject->mUnknown112;
        pObject->mUnknown12 = pObject->mUnknown116;
        pObject->mUnknown16 = pObject->mUnknown120;
        pObject->mUnknown96 = pObject->mUnknown124;
        pObject->mUnknown100 = pObject->mUnknown128;
        pObject->mUnknown104 = pObject->mUnknown132;
        pObject->mUnknown108 = pObject->mUnknown136;
        pObject->mUnknown32 = pObject->mUnknown140;
        pExtra->mUnknown56 = pObject->mUnknown140;
        if (pObject->mUnknown196.mValue != -1 &&
            fn_801BE648(pObject->mUnknown428->mUnknown1300) != pObject->mUnknown196.mValue) {
            StartAnim(pObject, pObject->mUnknown196.mParts.mKey, 1.0f);
        }
        fn_8004E090(pItem, 0, 0);
        pItem->mUnknown232_31 = 1;
        if (pObject->mUnknown144 != -1) {
            fn_800411EC(fn_8004117C(pObject->mUnknown144));
        } else {
            fn_800411EC(pItem);
        }
        pObject->mUnknown380 = 0;
    } else {
        if (pExtra->mUnknown1708 & 1) {
            pItem->mUnknown232_31 = 0;
            pExtra->mUnknown1708 &= ~1;
        }
        if (pObject->mUnknown380 &&
            fn_801BE648(pObject->mUnknown428->mUnknown1300) == pObject->mUnknown196.mValue) {
            if (pObject->mUnknown144 != -1) {
                fn_800411C8(fn_8004117C(pObject->mUnknown144));
            } else {
                fn_800411C8(pItem);
            }
            Vector_80039F5C pos;
            pos.mX = pObject->mUnknown360;
            pos.mY = pObject->mUnknown364;
            pos.mZ = pObject->mUnknown368;
            if (fn_801784C4()) {
                pos.mX = -pos.mX;
                pos.mY = -pos.mY;
            }
            Node_80041904 *pNode = pObject->mUnknown312;
            pObject->mUnknown380 = 0;
            float value = pObject->mUnknown372;
            for (; pNode; pNode = pNode->mpNext) {
                if (fn_801C2FE4(pNode->mName, pObject->mUnknown316) == 0) {
                    if (pNode->mUnknown64.mValue != -1) {
                        StartAnim(pObject, pNode->mUnknown64.mParts.mKey, 1.0f);
                    }
                    if (pNode->mUnknown104 != -1 && pNode->mUnknown108 != -1) {
                        fn_8004E090(pItem, pNode->mUnknown104, pNode->mUnknown108);
                    }
                    if (pNode->mUnknown92) {
                        fn_80067E3C(pNode->mUnknown92, &pos, pObject->mUnknown376, (unsigned int)value,
                                    pObject->mUnknown381, 0);
                    }
                    fn_8004CBEC(pNode->mUnknown128, value, pObject, pItem);
                    break;
                }
            }
        }
    }
    return 1;
}

void fn_80052130(Object_80040818 *pItem, Node_80041904 *pNode)
{
    Extra_8004149C *pExtra = pItem->mUnknown472->mUnknown428;
    Pair_80052130 *pPair = (Pair_80052130 *)pItem->mUnknown472->mUnknown420;
    char name[64];

    fn_801C2EF0(name, pNode->mName, 64);
    fn_801C32CC(name);
    if (fn_801C310C(name, "RIGHT")) {
        if (pPair->mpRight) {
            pExtra->mUnknown1704 = pItem->mUnknown472->mUnknown427;
            StartAnim(pItem->mUnknown472, pNode->mUnknown64.mParts.mKey, 1.0f);
            if (pPair->mpRight) {
                for (Node_80041904 *pOther = pPair->mpRight->mUnknown472->mUnknown312; pOther;
                     pOther = pOther->mpNext) {
                    fn_801C2EF0(name, pOther->mName, 64);
                    fn_801C32CC(name);
                    if (fn_801C310C(name, "LEFT")) {
                        if (pOther->mUnknown64.mValue != -1 &&
                            fn_801BE648(pPair->mpRight->mUnknown472->mUnknown428->mUnknown1300) !=
                                pOther->mUnknown64.mValue) {
                            Object_80041904 *pObject = pPair->mpRight->mUnknown472;
                            pObject->mUnknown428->mUnknown1704 = pObject->mUnknown427;
                            StartAnim(pPair->mpRight->mUnknown472, pOther->mUnknown64.mParts.mKey, 1.0f);
                            fn_80052130(pPair->mpRight, pOther);
                        }
                        break;
                    }
                }
            }
            if (pPair->mpLeft) {
                pPair->mpLeft->mUnknown472->mUnknown428->mUnknown1708 |= 1;
            }
        }
    } else if (pPair->mpLeft) {
        pExtra->mUnknown1704 = pItem->mUnknown472->mUnknown427;
        StartAnim(pItem->mUnknown472, pNode->mUnknown64.mParts.mKey, 1.0f);
        if (pPair->mpRight) {
            pPair->mpRight->mUnknown472->mUnknown428->mUnknown1708 |= 1;
        }
        if (pPair->mpLeft) {
            for (Node_80041904 *pOther = pPair->mpLeft->mUnknown472->mUnknown312; pOther;
                 pOther = pOther->mpNext) {
                fn_801C2EF0(name, pOther->mName, 64);
                fn_801C32CC(name);
                if (fn_801C310C(name, "RIGHT")) {
                    if (pOther->mUnknown64.mValue != -1 &&
                        fn_801BE648(pPair->mpLeft->mUnknown472->mUnknown428->mUnknown1300) !=
                            pOther->mUnknown64.mValue) {
                        Object_80041904 *pObject = pPair->mpLeft->mUnknown472;
                        pObject->mUnknown428->mUnknown1704 = pObject->mUnknown427;
                        StartAnim(pPair->mpLeft->mUnknown472, pOther->mUnknown64.mParts.mKey, 1.0f);
                        fn_80052130(pPair->mpLeft, pOther);
                    }
                    break;
                }
            }
        }
    }
}

int fn_80052440(Object_80041904 *pObject, Object_80040818 *pItem, int mode)
{
    Extra_8004149C *pExtra = pObject->mUnknown428;

    if (mode == 0) {
        if (pObject->mUnknown196.mValue != -1) {
            pExtra->mUnknown1704 = 1;
            StartAnim(pObject, pObject->mUnknown196.mParts.mKey, 1.0f);
        }
    } else {
        if (pExtra->mUnknown1708 & 1) {
            if (pObject->mUnknown196.mValue != -1) {
                pExtra->mUnknown1704 = 1;
                StartAnim(pObject, pObject->mUnknown196.mParts.mKey, 1.0f);
                Extra_8004149C *pAnim = pObject->mUnknown428;
                fn_801BE67C(pAnim->mUnknown1300, pAnim->mUnknown48, pAnim->mUnknown60, pObject);
            }
            pExtra->mUnknown1708 &= ~1;
        }
        if (pObject->mUnknown380) {
            float x = pObject->mUnknown360;
            float y = pObject->mUnknown364;
            float z = pObject->mUnknown368;
            pObject->mUnknown380 = 0;
            Vector_80039F5C pos;
            pos.mX = x;
            pos.mY = y;
            pos.mZ = z;
            float value = pObject->mUnknown372;
            if (fn_801784C4()) {
                pos.mX = -pos.mX;
                pos.mY = -pos.mY;
            }
            for (Node_80041904 *pNode = pObject->mUnknown312; pNode; pNode = pNode->mpNext) {
                if (fn_801C2FE4(pNode->mName, pObject->mUnknown316) == 0) {
                    if (pObject->mUnknown381 == 0) {
                        if (pNode->mUnknown64.mValue != -1 &&
                            fn_801BE648(pObject->mUnknown428->mUnknown1300) == pObject->mUnknown196.mValue) {
                            fn_80052130(pItem, pNode);
                        }
                        fn_8004CBEC(pNode->mUnknown128, pObject->mUnknown372, pObject, pItem);
                    }
                    if (pNode->mUnknown92) {
                        fn_80067E3C(pNode->mUnknown92, &pos, pObject->mUnknown376, (unsigned int)value,
                                    pObject->mUnknown381, 0);
                    }
                    break;
                }
            }
        }
    }
    return 1;
}

int fn_80052678(Object_80040818 *pItem)
{
    int value = 0;
    unsigned int i = 0;

    if (pItem) {
        unsigned int length = fn_801C3180(pItem->mName);

        while (i < length && (unsigned char)pItem->mName[i] - '0' > 9u) {
            i++;
        }
        while (i < length && (unsigned char)pItem->mName[i] - '0' <= 9u) {
            int digit = pItem->mName[i] - '0';
            value = value * 10 + digit;
            i++;
        }
    }
    return value;
}
}
