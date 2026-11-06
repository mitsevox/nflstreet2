/* Tutorial menu: lists the tutorial lessons with their titles, descriptions and the
   current profile's progress, starts the chosen lesson and records when every
   lesson has been completed. */

#include "game/DbCursor.h"
#include "game/fn_8021D7B8.h"

struct TutorialText_t {
    char mUnknown0[4];
    int mUnknown4;
    char *mUnknown8;
};

struct TutorialTextRef_t {
    TutorialText_t *mUnknown0;
};

struct TutorialArgs_t {
    int mUnknown0;
    TutorialTextRef_t mUnknown4;
    TutorialTextRef_t mUnknown8;
    int *mUnknown12;
    int *mUnknown16;
};

extern "C" {
extern void *lbl_803EB688;

void fn_80010200(int value);
void fn_80011600(int a, int b, int c);
void fn_80014294(int a, int b);
void fn_80015D28(int a);
void FELoopSetResume(unsigned char value);
int LessonTableSeek(DbCursor *pObject, int a, int *pResult);
int LessonTableGetCILM(DbCursor *pObject);
int LessonTableGetCISM(DbCursor *pObject);
int LessonTableGetDIRM(DbCursor *pObject);
void LessonTableGetTitle(DbCursor *pObject, char *pData, int size);
void LessonTableGetDescription(DbCursor *pObject, char *pData, int size);
void TeamLockOpen(DbCursor *pObject, int db);
void TeamLockClose(DbCursor *pObject);
int TeamLockIsHidden(DbCursor *pObject, int a);
void TeamUnlock(int db, int a);
unsigned char TutorialDbOpenInfo(void);
unsigned char TutorialDbCloseInfo(void);
int TutorialGetStepCount(int id);
int TutorialAllComplete(void);
int TutorialIsComplete(int id);
void TutorialGetDescription(int id, char *pDest, int count);
unsigned char TutorialTakeAllCompleteFlag(void);
void TutorialSetProfileDb(int db);
int TutorialGetProfileDb(void);
void fn_801566EC(void);
void fn_801566F8(void);
void fn_80156724(int value);
void fn_8015672C(int value);
void fn_80156734(int value);
unsigned int fn_801568F0(void);
int fn_801801B4(void);
void fn_801801C4(int a);
void fn_80186F30(signed char a, int b);
signed char fn_8022F384(int a);
int fn_8022F478(int a);
int fn_8022F4BC(void);
int fn_8000FCCC(void);
int fn_8000FCDC(void);

void MsgTutorialBeginLesson(void);
void MsgTutorialCheckCompletion(void);
}

static DbCursor _MsgTutorial_LessonCursor;
static unsigned char _MsgTutorial_cFirstLesson = 0;
static unsigned char _MsgTutorial_bDatabaseSet = 0;

extern "C" {
void MsgTutorialInit(void)
{
    fn_801566EC();
    TutorialDbOpenInfo();
    if (!_MsgTutorial_bDatabaseSet) {
        if (fn_8022F4BC() != -1) {
            TutorialSetProfileDb(fn_8022F4BC());
            _MsgTutorial_bDatabaseSet = 1;
        }
    } else {
        fn_8022F478(TutorialGetProfileDb());
    }
}

void MsgTutorialShutdown(void)
{
    fn_801566F8();
    TutorialDbCloseInfo();
}

int MsgTutorialGetLessonStatus(int index)
{
    LessonTableSeek(&_MsgTutorial_LessonCursor, index + _MsgTutorial_cFirstLesson, 0);
    return LessonTableGetCISM(&_MsgTutorial_LessonCursor);
}

void MsgTutorialGetLessonInfo(int index, TutorialTextRef_t first, TutorialTextRef_t second, int *pResult0, int *pResult1)
{
    LessonTableSeek(&_MsgTutorial_LessonCursor, index + _MsgTutorial_cFirstLesson, 0);
    LessonTableGetTitle(&_MsgTutorial_LessonCursor, first.mUnknown0->mUnknown8, first.mUnknown0->mUnknown4 + 1);
    LessonTableGetDescription(&_MsgTutorial_LessonCursor, second.mUnknown0->mUnknown8, second.mUnknown0->mUnknown4 + 1);
    *pResult0 = LessonTableGetCILM(&_MsgTutorial_LessonCursor);
    *pResult1 = LessonTableGetDIRM(&_MsgTutorial_LessonCursor);
}

void MsgTutorialPostLessonEvent(int value)
{
    if (value != -1) {
        fn_801801C4(value);
    }
    fn_8021D7B8(lbl_803EB688, 0x80000036, 0, 0);
}

int MsgTutorialHandleMessage(unsigned int id, TutorialArgs_t *pParams, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        MsgTutorialInit();
        break;
    case 0x80000002:
        MsgTutorialShutdown();
        MsgTutorialBeginLesson();
        break;
    case 0x80000003:
        *pResult = MsgTutorialGetLessonStatus(pParams->mUnknown0);
        break;
    case 0x80000004:
        MsgTutorialGetLessonInfo(pParams->mUnknown0, pParams->mUnknown4, pParams->mUnknown8, pParams->mUnknown12,
                    pParams->mUnknown16);
        break;
    case 0x80000005:
        MsgTutorialPostLessonEvent(pParams->mUnknown0);
        break;
    case 0x80000007:
        fn_8015672C(pParams->mUnknown0);
        break;
    case 0x80000006:
        TutorialGetDescription(pParams->mUnknown0, pParams->mUnknown4.mUnknown0->mUnknown8, pParams->mUnknown4.mUnknown0->mUnknown4);
        *pParams->mUnknown16 = TutorialIsComplete(pParams->mUnknown0);
        break;
    case 0x80000008:
        *pResult = TutorialAllComplete();
        MsgTutorialCheckCompletion();
        break;
    case 0x80000009:
        *pResult = TutorialTakeAllCompleteFlag();
        break;
    case 0x8000000A:
        fn_80010200(600);
        break;
    default:
        return 0;
    }
    return 1;
}

void MsgTutorialBeginLesson(void)
{
    int state = fn_801801B4();

    if (state == 1) {
        int value = fn_8000FCDC();
        if (!_MsgTutorial_bDatabaseSet) {
            TutorialSetProfileDb(fn_8022F4BC());
            _MsgTutorial_bDatabaseSet = state;
        }
        fn_80011600(-1, fn_8000FCCC(), value);
        fn_80186F30(fn_8022F384(TutorialGetProfileDb()), 1);
        fn_80014294(0x36, 0x21);
        FELoopSetResume(1);
        unsigned int id = fn_801568F0();
        if (TutorialIsComplete(id)) {
            fn_80156734(0);
            fn_80156724(0);
        } else {
            fn_80156734(TutorialGetStepCount(id));
            fn_80156724(TutorialGetStepCount(id));
        }
        fn_80015D28(4);
    } else {
        TutorialSetProfileDb(-1);
        _MsgTutorial_bDatabaseSet = 0;
    }
}

void MsgTutorialCheckCompletion(void)
{
    DbCursor object;

    int db = fn_8022F384(fn_8022F4BC());
    TeamLockOpen(&object, db);
    int found = TeamLockIsHidden(&object, 0x21);
    TeamLockClose(&object);
    if (TutorialAllComplete() && found) {
        TeamUnlock(db, 0x21);
    }
}
}
