/* Resource tracker: a debug log of every resource file opened and loaded (name, index, sizes, sync or
   async, time), with labels marking the start and finish of loading phases, kept in a memory buffer. */

#include "engine/Resource.h"
#include "engine/system.h"
#include "game/fn_801D2B7C.h"

extern int sprintf(char *s, const char *format, ...);

int ResTrackerSize = 0x32000;
static char *_ResTrackMemory = 0;
static char *_ResTrackBaseMemory = 0;
static int _ResCount = 0;
static unsigned char _bResTrackTideCompatible = 1;
static int _ResTrackPauseCount = 0;
unsigned char bResTrackResource = 0;
unsigned char bResTrackInit = 0;


static int _ResTrackIsPaused(void)
{
    if (_ResTrackPauseCount > 0) {
        return 1;
    }
    return 0;
}

void ResTrackInit(int heap)
{
    _ResCount = 0;
    _ResTrackMemory = fn_801D2BB0(heap, ResTrackerSize, 0, 0);
    _ResTrackBaseMemory = _ResTrackMemory;
    _ResTrackMemory += sprintf(_ResTrackMemory, "%s\t%s\t%s\t%s", "RESNAME", "Index", "Count", "Time");
    _ResTrackPauseCount = 0;
    bResTrackInit = 1;
}

void ResTrackInitSize(int heap, int size)
{
    ResTrackerSize = size;
    ResTrackInit(heap);
}

void ResTrackResource(unsigned int type, void *pData)
{
    ResTrackLoadInfo_t *pLoad;
    ResFile_t *pRes;
    char *pMem;
    char *pName;
    int index;

    if (bResTrackResource == 1 && bResTrackInit == 1) {
        pMem = _ResTrackMemory;
        if (pMem - _ResTrackBaseMemory < ResTrackerSize - 100) {
            if (_bResTrackTideCompatible != 0) {
                switch (type) {
                case 0:
                    pName = ((ResTrackOpenInfo_t *)pData)->pName;
                    index = -1;
                    break;
                case 2:
                    pRes = ((ResTrackLoadInfo_t *)pData)->pRes;
                    index = ((ResTrackLoadInfo_t *)pData)->mIndex;
                    pName = pRes->pName;
                    break;
                default:
                    pName = 0;
                    index = -1;
                    break;
                }
                if (pName != 0) {
                    _ResTrackMemory += sprintf(_ResTrackMemory, "%s\t%d\t%d\t%d\n", pName, index, _ResCount, SysGetSystemTime());
                }
            } else {
                pLoad = pData;
                switch (type) {
                case 0: {
                    char mode;
                    if (_ResTrackIsPaused() == 0) {
                        mode = ((ResTrackOpenInfo_t *)pData)->mMode;
                    } else {
                        mode = 'i';
                    }
                    _ResTrackMemory += sprintf(pMem, "OPEN\t%c\t%d\t%s\n", mode, SysGetSystemTime(), ((ResTrackOpenInfo_t *)pData)->pName);
                    break;
                }
                case 1:
                    pRes = pLoad->pRes;
                    _ResTrackMemory += sprintf(pMem, "OPENDONE\t\t%d\t%s\tN/A\t%d\t%d\n", SysGetSystemTime(), pRes->pName, pLoad->mIndex, pLoad->mIndex);
                    break;
                case 2: {
                    char mode;
                    pRes = pLoad->pRes;
                    if (_ResTrackIsPaused() == 0) {
                        mode = pLoad->mMode;
                    } else {
                        mode = 'i';
                    }
                    _ResTrackMemory += sprintf(pMem, "LOAD\t%c\t%d\t%s\t", mode, SysGetSystemTime(), pRes->pName);
                    if (pLoad->mIndex == -1) {
                        _ResTrackMemory += sprintf(_ResTrackMemory, "ALL\t");
                    } else {
                        _ResTrackMemory += sprintf(_ResTrackMemory, "%d\t", pLoad->mIndex);
                    }
                    _ResTrackMemory += sprintf(_ResTrackMemory, "%d\t%d\t%s\t%d\n", pLoad->mDiskSize, pLoad->mFullSize,
                                            pLoad->mAsync ? "ASYNC" : "SYNC", pLoad->mOffset);
                    break;
                }
                case 3:
                    pRes = pLoad->pRes;
                    _ResTrackMemory += sprintf(pMem, "LOADDONE\t\t%d\t%s\t", SysGetSystemTime(), pRes->pName);
                    if (pLoad->mIndex == -1) {
                        _ResTrackMemory += sprintf(_ResTrackMemory, "ALL\n");
                    } else {
                        _ResTrackMemory += sprintf(_ResTrackMemory, "%d\n", pLoad->mIndex);
                    }
                    break;
                }
            }
            _ResCount++;
        }
    }
}

void ResTrackEnable(int enable)
{
    bResTrackResource = enable;
    if (enable == 1) {
        _ResTrackMemory = _ResTrackBaseMemory;
        if (_bResTrackTideCompatible != 0) {
            _ResTrackMemory += sprintf(_ResTrackMemory, "TIDE_GROUPIMPORT_FILE\n");
            _ResTrackMemory += sprintf(_ResTrackMemory, "VERSION 0.1\n");
            _ResTrackMemory += sprintf(_ResTrackMemory, "\tADDITIONAL_COLUMNS:\t%s\t%s\n", "Count", "Time");
        } else {
            _ResTrackMemory += sprintf(_ResTrackMemory, "RESOURCE TRACKER\n");
            _ResTrackMemory += sprintf(_ResTrackMemory, "VERSION 0.2\n");
            _ResTrackMemory += sprintf(_ResTrackMemory, "Type\tQL\tTime\tDescription\tIndex\tDiskSize\tFullSize\tSync\tOffset\n");
        }
    }
}

void ResTrackSetTideCompatible(int tide)
{
    _bResTrackTideCompatible = tide;
}

void ResTrackLabel(char *pLabel)
{
    if (bResTrackResource == 1 && bResTrackInit == 1 &&
        _ResTrackMemory - _ResTrackBaseMemory < ResTrackerSize - 100 && _bResTrackTideCompatible == 0) {
        _ResTrackMemory += sprintf(_ResTrackMemory, "LABEL\t\t%d\t%s\n", SysGetSystemTime(), pLabel);
    }
}

void ResTrackPause(void)
{
    _ResTrackPauseCount++;
}

void ResTrackResume(void)
{
    _ResTrackPauseCount--;
}
