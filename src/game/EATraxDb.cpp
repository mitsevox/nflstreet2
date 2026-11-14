/* Static-database access for the EA Trax song list (table 'XTAE'): opens the song cursor,
   finds a song by id and reads its id and its three display strings, which the music player
   (SndgMusic.cpp) shows for the playing song. */
#include "game/DbCursor.h"
#include "game/DbSortKey.h"
#include "game/Query_8008352C.h"

static DbSortKey _EATraxDb_aSortKeys[2] = {
    {0x58544145, 0x58494E53, 0, 0},
    {-1, -1, 3, 0}
};

extern "C" {

void EATraxDbOpen(DbCursor *pCursor)
{
    Query_8008352C query;

    query.mUnknown0 = 0;
    query.mUnknown4 = 0;
    query.mUnknown8 = 0;
    DbCursorOpen(pCursor, 0x58544145, 0x58494E53, _EATraxDb_aSortKeys, 0, 0x54415453);
}

void EATraxDbClose(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

void EATraxDbFindSong(DbCursor *pCursor, int key, int *pRow)
{
    DbCursorFindInt(pCursor, 0x44494E53, key, 0, pRow);
}

int EATraxDbGetSongId(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x44494E53);
}

void EATraxDbGetArtist(DbCursor *pCursor, char *pText, int length)
{
    DbCursorGetString(pCursor, 0x52414E53, (int)pText, length);
}

void EATraxDbGetTitle(DbCursor *pCursor, char *pText, int length)
{
    DbCursorGetString(pCursor, 0x49544E53, (int)pText, length);
}

void EATraxDbGetAlbum(DbCursor *pCursor, char *pText, int length)
{
    DbCursorGetString(pCursor, 0x4C414E53, (int)pText, length);
}

}
