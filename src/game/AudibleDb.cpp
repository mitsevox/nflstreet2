/* Audibles: the plays assigned to the four directions for a formation, and where each
   assigned play sits in the side's current playbook. */

#include <stdio.h>

#include "game/DbCursor.h"
#include "game/PlayBookDb.h"
#include "game/fn_801FCE10.h"

extern "C" {
int DbCursorGetValue(DbCursor *pObject, int key);
int PlayCallGetPlaybookId(int a);
int fn_801C302C(const char *s1, const char *s2, int n);

void AudibleDbOpen(DbCursor *pCursor);
void AudibleDbClose(DbCursor *pCursor);
int AudibleDbSeekFormation(DbCursor *pCursor, int key);
unsigned char AudibleDbGetSideFlag(DbCursor *pCursor);
int AudibleDbGetPlaybookId(DbCursor *pCursor);
unsigned char AudibleDbGetPlayIndex(DbCursor *pCursor, int column);
}

static int _AudibleDb_aDirectionColumns[4] = {
    0x55445541, 0x44445541, 0x4C445541, 0x52445541
};

extern "C" {

void AudibleDbOpen(DbCursor *pCursor)
{
    DbCursorOpen(pCursor, 0x49445541, 0x4F464C50, 0, 0, 0x54415453);
}

void AudibleDbClose(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

int AudibleDbSeekFormation(DbCursor *pCursor, int key)
{
    return DbCursorFindValue(pCursor, 0x4F464C50, key, 0, 0);
}

unsigned char AudibleDbGetSideFlag(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x4F494650);
}

int AudibleDbGetPlaybookId(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x44494250);
}

unsigned char AudibleDbGetPlayIndex(DbCursor *pCursor, int column)
{
    PlayBookFormation_t object;
    PlayBookPlay_t record;
    char text[8];
    int handle;
    int match = 0;
    int tag;
    int mode;
    int value;
    unsigned short count;
    unsigned char i;

    if (AudibleDbGetSideFlag(pCursor)) {
        value = AudibleDbGetPlaybookId(pCursor);
        tag = 0x31544250;
        mode = 1;
        match = value == PlayCallGetPlaybookId(1);
    } else {
        value = AudibleDbGetPlaybookId(pCursor);
        tag = 0x31444250;
        mode = 11;
        if (value == PlayCallGetPlaybookId(0)) {
            match = 1;
        }
    }
    if (match) {
        signed char number = DbCursorGetValue(pCursor, _AudibleDb_aDirectionColumns[column]);

        sprintf(text, "%02d", number);
        PlayBookDbLoadFormation(tag, mode, 0, &object);
        fn_801FCE10(0, "use \x8c select 'TSBP' into \x85 from 'TSBP' where '_dro' = \x85 and 'MFBP' = \x85\n",
                    tag, &handle, 1, object.mUnknown0);
        count = PlayBookDbCountPlays(tag, handle);
        for (i = 0; i < count; i++) {
            PlayBookDbLoadPlay(tag, handle, i, &record);
            if (fn_801C302C(record.mUnknown1F0, text, 2) == 0) {
                break;
            }
        }
    } else {
        i = 0;
    }
    return i;
}

}
