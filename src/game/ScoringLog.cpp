/* Keeps the game's scoring summary: up to 40 scoring plays (type, yards, scorer ids, clock and both scores), each later completed with its conversion result, published under the tag 'MSSG'. */
#include "game/fn_8009D990.h"
struct ScoringPlay_t {
    short mUnknown00;
    short mUnknown02;
    short mUnknown04;
    short mUnknown06;
    short mUnknown08;
    short mUnknown0A;
    short mUnknown0C;
    char mUnknown0E;
    char mUnknown0F;
    char mUnknown10;
    char mUnknown11;
    char mUnknown12;
};

struct ScoringLog_t {
    unsigned int mCount;
    ScoringPlay_t mRecords[40];
};

extern "C" {
int fn_8009D86C(void);
int DriveLogHasLongPlay(void);
void DriveLogSetHold(int value);
int DriveLogGetPlayerNum(int id);
int fn_801787DC(int a);
void fn_8017C344(unsigned short team, int play);
int fn_8022DDB4(int tag, void *data);
}

ScoringLog_t gScoringLog;

extern "C" void ScoringLogInit(void)
{
    gScoringLog.mCount = 0;
    fn_8022DDB4(0x4D535347, &gScoringLog);
}

extern "C" void ScoringLogReset(void)
{
    gScoringLog.mCount = 0;
    fn_8022DDB4(0x4D535347, &gScoringLog);
}

extern "C" void ScoringLogAddScore(int a, short b, int c, int d)
{
    if (a != 9) {
        DriveLogSetHold(1);
    }
    if (gScoringLog.mCount < 40) {
        int hi = (c >> 8) & 0xFF;
        gScoringLog.mRecords[gScoringLog.mCount].mUnknown10 = fn_8009D86C();
        gScoringLog.mRecords[gScoringLog.mCount].mUnknown00 = fn_8009D990(1);
        gScoringLog.mRecords[gScoringLog.mCount].mUnknown0E = a;
        gScoringLog.mRecords[gScoringLog.mCount].mUnknown02 = b;
        gScoringLog.mRecords[gScoringLog.mCount].mUnknown06 = DriveLogGetPlayerNum(c);
        gScoringLog.mRecords[gScoringLog.mCount].mUnknown0A = DriveLogGetPlayerNum(d);
        gScoringLog.mRecords[gScoringLog.mCount].mUnknown11 = fn_801787DC(1);
        gScoringLog.mRecords[gScoringLog.mCount].mUnknown12 = fn_801787DC(0);
        if ((a == 0 || a == 1 || a == 5) && DriveLogHasLongPlay()) {
            fn_8017C344(hi, a);
        }
        gScoringLog.mRecords[gScoringLog.mCount].mUnknown0F = 13;
        gScoringLog.mCount++;
        fn_8022DDB4(0x4D535347, &gScoringLog);
    }
}

extern "C" void ScoringLogSetConversion(int a, int b, int c, int d)
{
    if (gScoringLog.mCount - 1 < 39) {
        gScoringLog.mRecords[gScoringLog.mCount - 1].mUnknown0F = a;
        gScoringLog.mRecords[gScoringLog.mCount - 1].mUnknown04 = b;
        gScoringLog.mRecords[gScoringLog.mCount - 1].mUnknown08 = DriveLogGetPlayerNum(c);
        gScoringLog.mRecords[gScoringLog.mCount - 1].mUnknown0C = DriveLogGetPlayerNum(d);
        gScoringLog.mRecords[gScoringLog.mCount - 1].mUnknown11 = fn_801787DC(1);
        gScoringLog.mRecords[gScoringLog.mCount - 1].mUnknown12 = fn_801787DC(0);
        fn_8022DDB4(0x4D535347, &gScoringLog);
    }
}
