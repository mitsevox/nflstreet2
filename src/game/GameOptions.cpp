/* Game options record: opens the options table, keeps one record of the
   23 option values (volumes and play settings) in memory, resets them to
   their defaults and writes changes back to the table. */
#include "game/DbQuery.h"
#include "game/FELoop.h"
#include "game/DbCursor.h"
#include "game/GameOptions.h"
#include "game/GameModeType.h"

/* One row of the option table: the column tag and the value to store when the
   options are reset. */
struct GameOptionsDefault_t {
    int mColumnTag;
    int mValue;
};

extern "C" {
extern void *gUISMainInfo;

int fn_801FA428(int file, DbTableRef *pTables, DbExpression *pExpression,
                DbColumnValue *pList, DbQueryResult *pResult, int a);
void SndgSetVolumeOption(int channel, unsigned char level);
void SndgApplyVolumeOptions(void);
int CamGetDisplayModeIndex(void);
void fn_80219650(void *p, unsigned short *pA, unsigned short *pB);

}

static GameOptionsDefault_t _GameOptions_aDefaults[23] = {
    { 0x454C534F, 0 },
    { 0x414C504F, 36 },
    { 0x544C504F, 200000 },
    { 0x4152544F, 10 },
    { 0x5658464F, 10 },
    { 0x5647494F, 10 },
    { 0x5349444F, 0 },
    { 0x4F52504F, 0 },
    { 0x5550434F, 1 },
    { 0x4249564F, 1 },
    { 0x4853434F, 1 },
    { 0x4554534F, 1 },
    { 0x4153414F, 1 },
    { 0x41434D4F, 0 },
    { 0x444D474F, 0 },
    { 0x5455544F, 0 },
    { 0x5249414F, 1 },
    { 0x4D4E534F, 1 },
    { 0x4D5A434F, 0 },
    { 0x4542474F, 1 },
    { 0x5041504F, 0 },
    { 0x5047504F, 1 },
    { 0x5447504F, 0 },
};

static DbCursor _GameOptions_sCursor;
static DbColumnValue _GameOptions_aRecord[24];

/* While set, GameOptionsSet updates only the record and skips the per-column
   store; GameOptionsSetDeferWrites writes the whole record back when it clears. */
static unsigned char _GameOptions_bDeferWrites = 0;

/* Columns 1, 2, 14, 8 and 19 keep a separate value that GameModeTypeGet() == 6
   selects instead of the record value. */
static int _GameOptions_iShadow1 = 36;
static int _GameOptions_iShadow2 = 100000;
static int _GameOptions_iShadow14 = 0;
static int _GameOptions_iShadow8 = 1;
static int _GameOptions_iShadow19 = 1;

extern "C" {

static void _GameOptionsResetAll(void);

static inline int WriteRecord(DbCursor *pCursor,
                              DbColumnValue *pList)
{
    DbExpression expression;
    DbQueryResult result;
    DbTableRef tables[2];
    DbColumnValue key[2];

    key[0].Set(-1, pCursor->mUnknown12, 0);
    key[1].SetEnd();
    pCursor->Read(key);
    unsigned int table = pCursor->mUnknown8;
    unsigned int column = pCursor->mUnknown12;

    expression.Set(((unsigned long long)table << 32) | column,
                   0x00010003, key[0].mValue);
    tables[0].Set(table);
    tables[1].Set(-1);
    return fn_801FA428(pCursor->mUnknown4, tables, &expression, pList, &result, 0);
}

void GameOptionsOpenCursor(void);
int GameOptionsCloseCursor(void);
int GameOptionsWriteRecord(void);

#if defined(DECOMP_COMPARE)
void GameOptionsOpenCursor(void)
{
    DbCursorOpen(&_GameOptions_sCursor, 0x5354504F, 0x554E554F, 0, 0, 0x45564153);
}

int GameOptionsCloseCursor(void)
{
    return DbCursorClose(&_GameOptions_sCursor);
}

/* Writes the whole record back to the row the cursor's key column selects. */
int GameOptionsWriteRecord(void)
{
    return WriteRecord(&_GameOptions_sCursor, _GameOptions_aRecord);
}
#endif

/* Fills the record with the defaults and replaces them with the stored row. */
static int _GameOptionsReadRecord(void)
{
    DbColumnValue *pEnd;
    int i;

    for (i = 0; i < 23; i++) {
        _GameOptions_aRecord[i].mTableTag = 0x5354504F;
        _GameOptions_aRecord[i].mColumnTag = _GameOptions_aDefaults[i].mColumnTag;
        _GameOptions_aRecord[i].mValue = _GameOptions_aDefaults[i].mValue;
    }
    pEnd = &_GameOptions_aRecord[23];
    pEnd->mValue = 0;
    pEnd->mColumnTag = -1;
    pEnd->mTableTag = -1;
    return _GameOptions_sCursor.Read(_GameOptions_aRecord);
}

void GameOptionsInit(int reset)
{
    _GameOptions_bDeferWrites = 0;
    GameOptionsOpenCursor();
    if (reset != 0) {
        _GameOptionsResetAll();
    } else {
        _GameOptionsReadRecord();
    }
    SndgApplyVolumeOptions();
}

int GameOptionsShutdown(void)
{
    return GameOptionsCloseCursor();
}

void GameOptionsSetDeferWrites(int defer)
{
    if (_GameOptions_bDeferWrites != 0 && defer == 0) {
        GameOptionsWriteRecord();
    }
    _GameOptions_bDeferWrites = defer;
}

/* Resets every option to its default and stores the result. */
static void _GameOptionsResetAll(void)
{
    DbColumnValue *pEnd;
    int mode;
    int i;

    for (i = 0; i < 23; i++) {
        _GameOptions_aRecord[i].mTableTag = 0x5354504F;
        _GameOptions_aRecord[i].mColumnTag = _GameOptions_aDefaults[i].mColumnTag;
        _GameOptions_aRecord[i].mValue = _GameOptions_aDefaults[i].mValue;
    }
    pEnd = &_GameOptions_aRecord[23];
    pEnd->mValue = 0;
    pEnd->mColumnTag = -1;
    pEnd->mTableTag = -1;

    WriteRecord(&_GameOptions_sCursor, _GameOptions_aRecord);

    mode = CamGetDisplayModeIndex();
    if (mode == 1 || mode == 2) {
        GameOptionsSet(6, mode);
    }
}

/* Resets the marked options to their defaults and stores the result. */
int GameOptionsResetMarked(void)
{
    unsigned char reset[23] = {
        1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
    };
    DbColumnValue *pEnd;
    int i;

    for (i = 0; i < 23; i++) {
        _GameOptions_aRecord[i].mTableTag = 0x5354504F;
        _GameOptions_aRecord[i].mColumnTag = _GameOptions_aDefaults[i].mColumnTag;
        if (reset[i] != 0) {
            _GameOptions_aRecord[i].mValue = _GameOptions_aDefaults[i].mValue;
        }
    }
    pEnd = &_GameOptions_aRecord[23];
    pEnd->mValue = 0;
    pEnd->mColumnTag = -1;
    pEnd->mTableTag = -1;

    return WriteRecord(&_GameOptions_sCursor, _GameOptions_aRecord);
}

void GameOptionsSet(int id, int value)
{
    if (GameModeTypeGet() == 6) {
        switch (id) {
        case 1:
            _GameOptions_iShadow1 = value;
            return;
        case 2:
            _GameOptions_iShadow2 = value;
            return;
        case 14:
            _GameOptions_iShadow14 = value;
            return;
        case 8:
            _GameOptions_iShadow8 = value;
            return;
        case 19:
            _GameOptions_iShadow19 = value;
            return;
        }
    }
    if (_GameOptions_bDeferWrites == 0) {
        fn_8007AA90(&_GameOptions_sCursor, _GameOptions_aDefaults[id].mColumnTag, value);
    }
    _GameOptions_aRecord[id].mValue = value;
    if (id >= 3 && id <= 5) {
        switch (id) {
        case 3:
            SndgSetVolumeOption(3, value * 10);
            break;
        case 4:
            SndgSetVolumeOption(1, value * 10);
            break;
        case 5:
            SndgSetVolumeOption(2, value * 10);
            break;
        }
    }
}

int GameOptionsGet(int id)
{
    int allowed = 1;
    int result = 0;
    int override = 0;

    if ((unsigned int)id <= 22) {
        if (GameModeTypeGet() == 8) {
            override = 1;
            if (FELoopIsMainFEActive() != 0 && gUISMainInfo != 0) {
                unsigned short state;
                unsigned short other;

                fn_80219650(gUISMainInfo, &state, &other);
                if (state == 5 || state == 0) {
                    allowed = 0;
                }
            }
        }
        if (GameModeTypeGet() == 6) {
            switch (id) {
            case 1:
                return _GameOptions_iShadow1;
            case 2:
                return _GameOptions_iShadow2;
            case 14:
                return _GameOptions_iShadow14;
            case 8:
                return _GameOptions_iShadow8;
            case 19:
                return _GameOptions_iShadow19;
            }
        } else if (override != 0 && allowed != 0) {
            switch (id) {
            case 1:
                return 36;
            case 14:
                return 0;
            case 8:
                return 1;
            case 19:
                return 1;
            }
        }
        result = _GameOptions_aRecord[id].mValue;
    }
    return result;
}

void GameOptionsCopyShadow(void)
{
    _GameOptions_iShadow1 = _GameOptions_aRecord[1].mValue;
    _GameOptions_iShadow2 = _GameOptions_aRecord[2].mValue;
    _GameOptions_iShadow14 = _GameOptions_aRecord[14].mValue;
    _GameOptions_iShadow8 = _GameOptions_aRecord[8].mValue;
    _GameOptions_iShadow19 = _GameOptions_aRecord[19].mValue;
}
}
