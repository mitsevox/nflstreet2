#include "game/Object_8008044C.h"
#include "game/Object_8007A334.h"
#include "game/Query_8007F19C.h"

/* Fourteen column tags read in this order by both functions. The source
   grouping and original declaration remain provisional. */
static int lbl_802D6898[14] = {
    0x54414850, 0x52574550, 0x41505350, 0x52415550,
    0x57424550, 0x54525750, 0x444E4850, 0x44485250,
    0x434F5350, 0x4F485350, 0x54525350, 0x544E5050,
    0x54434A50, 0x44454D50
};

extern "C" void fn_800817CC(Object_8008044C *object, Info_80307908 *info)
{
    ColumnValue_802D6424 columns[15];
    ColumnValue_802D6424 *list = columns;
    for (int i = 0; i < 14; ++i) list[i].Set(object->mUnknown8, lbl_802D6898[i], 0);
    columns[14].SetEnd();
    fn_801FA228(object->mUnknown0, 0, 0, list);
    for (int i = 0; i < 14; ++i) info->mValues[i] = list[i].mValue;
    info->mUnknown00 = fn_8007A98C(object, 0x4C554C50);
    info->mUnknown01 = fn_8007A98C(object, 0x4C574C50);
    info->mUnknown02 = fn_8007A98C(object, 0x524F4850);
    info->mUnknown03 = fn_8007A98C(object, 0x50544550);
    info->mUnknown09 = fn_8007A98C(object, 0x44465450);
    info->mUnknown0A = fn_8007A98C(object, 0x44425450);
    info->mUnknown0B = fn_8007A98C(object, 0x43444850);
    info->mUnknown04 = fn_8007A98C(object, 0x54415250);
    info->mUnknown05 = fn_8007A98C(object, 0x4F544150);
    info->mUnknown06[0] = fn_8007A98C(object, 0x544C5250);
    info->mUnknown06[1] = fn_8007A98C(object, 0x4F544C50);
    info->mUnknown08 = fn_8007A98C(object, 0x4F544250);
    info->mUnknown0C = fn_8007A98C(object, 0x4D545350);
    info->mUnknown0D = fn_8007A98C(object, 0x4D544850);
}

extern "C" void fn_8008199C(Object_8008044C *object, Info_80307908 *info)
{
    ColumnValue_802D6424 columns[15];
    ColumnValue_802D6424 *list = columns;
    Expression_8007F19C expression;
    Result_8007F19C result;
    Table_8007F19C tables[2];
    ColumnValue_802D6424 key[2];
    for (int i = 0; i < 14; ++i) list[i].Set(0x59414C50, lbl_802D6898[i], info->mValues[i]);
    columns[14].SetEnd();
    key[0].Set(-1, object->mUnknown12, 0);
    key[1].SetEnd();
    fn_801FA228(object->mUnknown0, 0, 0, key);
    expression.Set((static_cast<unsigned long long>(static_cast<unsigned int>(object->mUnknown8)) << 32) |
                   static_cast<unsigned int>(object->mUnknown12), 0x10003, key[0].mValue);
    tables[0].Set(object->mUnknown8);
    tables[1].Set(-1);
    fn_801FA428(object->mUnknown4, tables, &expression, list, &result, 0);
    fn_8007ABA4(object, 0x4C554C50, info->mUnknown00);
    fn_8007ABA4(object, 0x4C574C50, info->mUnknown01);
    fn_8007ABA4(object, 0x524F4850, info->mUnknown02);
    fn_8007ABA4(object, 0x50544550, info->mUnknown03);
    fn_8007ABA4(object, 0x44465450, info->mUnknown09);
    fn_8007ABA4(object, 0x44425450, info->mUnknown0A);
    fn_8007ABA4(object, 0x43444850, info->mUnknown0B);
    fn_8007ABA4(object, 0x54415250, info->mUnknown04);
    fn_8007ABA4(object, 0x4F544150, info->mUnknown05);
    fn_8007ABA4(object, 0x544C5250, static_cast<unsigned char>(info->mUnknown06[0]));
    fn_8007ABA4(object, 0x4F544C50, static_cast<unsigned char>(info->mUnknown06[1]));
    fn_8007ABA4(object, 0x4F544250, info->mUnknown08);
    fn_8007ABA4(object, 0x4D545350, info->mUnknown0C);
    fn_8007ABA4(object, 0x4D544850, info->mUnknown0D);
}
