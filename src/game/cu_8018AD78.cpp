#include <string.h>

struct Entry_8018AD78 {
    unsigned char mUnknown[4];
};

struct Group_8018AD78 {
    unsigned short mCount;
    unsigned short mStart;
};

struct Item_8018AD78 {
    int mUnknown0;
    int mUnknown4;
    char *mpUnknown8;
};

struct Header_8018AD78 {
    unsigned char mRelocated;
    unsigned char mItemCount;
    unsigned char mUnknown2;
    unsigned char mGroupCount;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    int mUnknown8;
    Entry_8018AD78 *mpEntries;
    Group_8018AD78 *mpGroups;
    Item_8018AD78 **mppItems;
};

struct Result_8018AD78 {
    int mUnknown0;
    int mUnknown4;
    char *mpUnknown8;
};

struct Args_8018AD78 {
    int mUnknown0;
    int mUnknown4;
    Result_8018AD78 *mpResult;
};

extern "C" {
void fn_8018AD78(Header_8018AD78 *pHeader, unsigned int message, int a, Args_8018AD78 *pArgs, int *pOut);
}

extern "C" void fn_8018AD78(Header_8018AD78 *pHeader, unsigned int message, int a, Args_8018AD78 *pArgs, int *pOut)
{
    int count;

    if (pHeader != 0) {
        switch (message) {
        case -1:
            if (pHeader->mRelocated == 0) {
                int i;

                pHeader->mRelocated = 1;
                pHeader->mUnknown8 += (int)pHeader;
                pHeader->mpEntries = (Entry_8018AD78 *)((int)pHeader->mpEntries + (int)pHeader);
                pHeader->mpGroups = (Group_8018AD78 *)((int)pHeader->mpGroups + (int)pHeader);
                pHeader->mppItems = (Item_8018AD78 **)((int)pHeader->mppItems + (int)pHeader);
                i = pHeader->mItemCount;
                while (i-- != 0) {
                    pHeader->mppItems[i] = (Item_8018AD78 *)((int)pHeader->mppItems[i] + (int)pHeader);
                }
            }
            break;
        case 0:
            *pOut = pHeader->mpGroups[pArgs->mUnknown0].mCount;
            break;
        case 1:
            if (pArgs->mUnknown4 == 2) {
                *pOut = pHeader->mpEntries[pArgs->mUnknown0].mUnknown[2];
            } else {
                *pOut = pHeader->mpEntries[pArgs->mUnknown0].mUnknown[pArgs->mUnknown4];
            }
            break;
        case 2:
            if (pArgs->mUnknown0 < pHeader->mGroupCount) {
                count = pHeader->mpGroups[pArgs->mUnknown0].mCount;
                if (pArgs->mUnknown4 < count) {
                    strcpy(pArgs->mpResult->mpUnknown8,
                           pHeader->mppItems[pHeader->mpEntries[pArgs->mUnknown4].mUnknown[3]]->mpUnknown8);
                    break;
                }
            }
            pArgs->mpResult->mpUnknown8 = 0;
            pArgs->mpResult->mUnknown4 = 0;
            break;
        case 3:
            {
                if (pArgs->mUnknown0 < pHeader->mGroupCount) {
                    unsigned int start;
                    unsigned int i;

                    count = pHeader->mpGroups[pArgs->mUnknown0].mCount;
                    start = pHeader->mpGroups[pArgs->mUnknown0].mStart;

                    for (i = 0; i < count; i++) {
                        Entry_8018AD78 *pEntry = &pHeader->mpEntries[start + i];

                        if (pEntry->mUnknown[0] == pArgs->mUnknown4) {
                            strcpy(pArgs->mpResult->mpUnknown8, pHeader->mppItems[pEntry->mUnknown[3]]->mpUnknown8);
                            return;
                        }
                    }
                }
                pArgs->mpResult->mpUnknown8 = 0;
                pArgs->mpResult->mUnknown4 = 0;
            }
            break;
        case 4:
            if (pArgs->mUnknown0 < pHeader->mUnknown4) {
                pHeader->mUnknown6 = pArgs->mUnknown0;
            } else {
                pHeader->mUnknown6 = 0;
            }
            break;
        }
    }
}
