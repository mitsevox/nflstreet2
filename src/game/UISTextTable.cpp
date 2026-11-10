/* UI Studio text table object: a front-end screen object backed by a table of
   strings grouped into lists. Its action function fixes up the table's offsets
   once, reports list sizes, copies the string an entry selects into the
   caller's text buffer and keeps the current selection. */
#include <string.h>

struct UISTextTableEntry_t {
    unsigned char mUnknown[4];
};

struct UISTextTableGroup_t {
    unsigned short mCount;
    unsigned short mStart;
};

struct UISTextTableItem_t {
    int mUnknown0;
    int mUnknown4;
    char *mpUnknown8;
};

struct UISTextTableHdr_t {
    unsigned char mRelocated;
    unsigned char mItemCount;
    unsigned char mUnknown2;
    unsigned char mGroupCount;
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    int mUnknown8;
    UISTextTableEntry_t *mpEntries;
    UISTextTableGroup_t *mpGroups;
    UISTextTableItem_t **mppItems;
};

struct UISTextResult_t {
    int mUnknown0;
    int mUnknown4;
    char *mpUnknown8;
};

struct UISTextTableArgs_t {
    int mUnknown0;
    int mUnknown4;
    UISTextResult_t *mpResult;
};

extern "C" {
void UISTextTableAction(UISTextTableHdr_t *pHeader, unsigned int message, int a, UISTextTableArgs_t *pArgs, int *pOut);
}

extern "C" void UISTextTableAction(UISTextTableHdr_t *pHeader, unsigned int message, int a, UISTextTableArgs_t *pArgs, int *pOut)
{
    int count;

    if (pHeader != 0) {
        switch (message) {
        case -1:
            if (pHeader->mRelocated == 0) {
                int i;

                pHeader->mRelocated = 1;
                pHeader->mUnknown8 += (int)pHeader;
                pHeader->mpEntries = (UISTextTableEntry_t *)((int)pHeader->mpEntries + (int)pHeader);
                pHeader->mpGroups = (UISTextTableGroup_t *)((int)pHeader->mpGroups + (int)pHeader);
                pHeader->mppItems = (UISTextTableItem_t **)((int)pHeader->mppItems + (int)pHeader);
                i = pHeader->mItemCount;
                while (i-- != 0) {
                    pHeader->mppItems[i] = (UISTextTableItem_t *)((int)pHeader->mppItems[i] + (int)pHeader);
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
                        UISTextTableEntry_t *pEntry = &pHeader->mpEntries[start + i];

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
