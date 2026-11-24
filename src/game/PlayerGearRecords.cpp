/* Reads and writes a player's gear columns and look bytes through the database cursor. */
#include "game/Object_8008044C.h"
#include "game/DbCursor.h"
#include "game/DbQuery.h"

/* Fourteen column tags read in this order by both functions. The source
   grouping and original declaration remain provisional. */
static int _PlayerGear_aColumnTags[14] = {
    0x54414850, 0x52574550, 0x41505350, 0x52415550,
    0x57424550, 0x54525750, 0x444E4850, 0x44485250,
    0x434F5350, 0x4F485350, 0x54525350, 0x544E5050,
    0x54434A50, 0x44454D50
};

extern "C" int PlayerDbReadGear(Object_8008044C *object, PlayerGear_t *info)
{
    DbColumnValue columns[15];
    DbColumnValue *list = columns;
    for (int i = 0; i < 14; ++i) list[i].Set(object->mUnknown8, _PlayerGear_aColumnTags[i], 0);
    columns[14].SetEnd();
    TDbQryRetrieve(object->mUnknown0, 0, 0, list);
    for (int i = 0; i < 14; ++i) info->mValues[i] = list[i].mValue;
    info->mUnknown00 = DbCursorGetInt(object, 0x4C554C50);
    info->mUnknown01 = DbCursorGetInt(object, 0x4C574C50);
    info->mUnknown02 = DbCursorGetInt(object, 0x524F4850);
    info->mUnknown03 = DbCursorGetInt(object, 0x50544550);
    info->mUnknown09 = DbCursorGetInt(object, 0x44465450);
    info->mUnknown0A = DbCursorGetInt(object, 0x44425450);
    info->mUnknown0B = DbCursorGetInt(object, 0x43444850);
    info->mUnknown04 = DbCursorGetInt(object, 0x54415250);
    info->mUnknown05 = DbCursorGetInt(object, 0x4F544150);
    info->mUnknown06[0] = DbCursorGetInt(object, 0x544C5250);
    info->mUnknown06[1] = DbCursorGetInt(object, 0x4F544C50);
    info->mUnknown08 = DbCursorGetInt(object, 0x4F544250);
    info->mUnknown0C = DbCursorGetInt(object, 0x4D545350);
    int result = DbCursorGetInt(object, 0x4D544850);
    info->mUnknown0D = result;
    return result;
}

extern "C" void PlayerDbWriteGear(Object_8008044C *object, PlayerGear_t *info)
{
    DbColumnValue columns[15];
    DbColumnValue *list = columns;
    for (int i = 0; i < 14; ++i) {
        columns[i].mValue = info->mValues[i];
        columns[i].Set(0x59414C50, _PlayerGear_aColumnTags[i]);
    }
    columns[14].SetEnd();
    {
        DbExpression expression;
        DbColumnValue key[2];
        key[0].Set(-1, object->mUnknown12, 0);
        key[1].SetEnd();
        TDbQryRetrieve(object->mUnknown0, 0, 0, key);
        unsigned int table = object->mUnknown8;
        unsigned int keyColumn = object->mUnknown12;
        expression.Set(((unsigned long long)table << 32) | keyColumn, 0x10003, key[0].mValue);
        DbTableRef tables[2];
        tables[0].Set(object->mUnknown8);
        tables[1].Set(-1);
        DbQueryResult result;
        TDbQrySetFirstRow(object->mUnknown4, tables, &expression, list, &result, 0);
    }
    DbCursorSetInt(object, 0x4C554C50, info->mUnknown00);
    DbCursorSetInt(object, 0x4C574C50, info->mUnknown01);
    DbCursorSetInt(object, 0x524F4850, info->mUnknown02);
    DbCursorSetInt(object, 0x50544550, info->mUnknown03);
    DbCursorSetInt(object, 0x44465450, info->mUnknown09);
    DbCursorSetInt(object, 0x44425450, info->mUnknown0A);
    DbCursorSetInt(object, 0x43444850, info->mUnknown0B);
    DbCursorSetInt(object, 0x54415250, info->mUnknown04);
    DbCursorSetInt(object, 0x4F544150, info->mUnknown05);
    DbCursorSetInt(object, 0x544C5250, static_cast<unsigned char>(info->mUnknown06[0]));
    DbCursorSetInt(object, 0x4F544C50, static_cast<unsigned char>(info->mUnknown06[1]));
    DbCursorSetInt(object, 0x4F544250, info->mUnknown08);
    DbCursorSetInt(object, 0x4D545350, info->mUnknown0C);
    DbCursorSetInt(object, 0x4D544850, info->mUnknown0D);
}
