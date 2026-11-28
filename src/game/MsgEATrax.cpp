/* EA Trax playlist screen of the front-end options: loads the player's
   playlist into a 21-song table, lets the menu list the EA Trax songs with
   their title, artist and album, preview a song, add or remove songs (40
   slots), and writes the changes back to the playlist database when the
   screen is saved. */
#include "game/DbCursor.h"
#include "game/EditMenu.h"
#include <string.h>
#include "game/fn_801D2B7C.h"
#include "game/ResOpenDevice.h"
#include "game/SndgMusic.h"
#include "game/GameOptions.h"

/* One song of the playlist table: category and EA Trax row (-1 when the
   slot is free) and the edit state (0 in the playlist, 1 to remove, 2 to
   add, 3 free). */
struct MsgEATraxEntry_t {
    int mCategory;
    int mRow;
    int mState;
};

/* The playlist table MsgEATraxEnter allocates: free slots, then the songs. */
struct MsgEATraxPlaylist_t {
    int mCount;
    MsgEATraxEntry_t mEntries[21];
};

extern "C" {
extern char lbl_802EBFCC[];

void SndgPathResumeTrack(int a);
void SndgSetVolumeOption(unsigned int index, unsigned int value);
void SndgMusicSetHold(unsigned char a);
void SndgMusicPlaySong(int a, int b, int c);
int SndgMusicIsPaused(void);
void SndgMusicResume(void);
void SndgMusicStop(void);
void EATraxDbOpen(DbCursor *pObject);
void EATraxDbClose(DbCursor *pObject);
void EATraxDbFindSong(DbCursor *pObject, int key, int *pResult);
int EATraxDbGetSongId(DbCursor *pObject);
void EATraxDbGetArtist(DbCursor *pObject, char *pText, int length);
void EATraxDbGetTitle(DbCursor *pObject, char *pText, int length);
void EATraxDbGetAlbum(DbCursor *pObject, char *pText, int length);
void PlaylistDbOpen(DbCursor *pObject, void *pQuery);
void PlaylistDbRemoveStationEntries(DbCursor *pObject);
void PlaylistDbClose(DbCursor *pObject);
int PlaylistDbFirst(DbCursor *pObject);
int PlaylistDbNext(DbCursor *pObject);
void PlaylistDbFindEntry(DbCursor *pObject, int a, int b, int c);
int PlaylistDbGetIstx(DbCursor *pObject);
int PlaylistDbGetStationId(DbCursor *pObject);
int PlaylistDbGetSongId(DbCursor *pObject);
void PlaylistDbDeleteRow(DbCursor *pObject);
void PlaylistDbAddEntry(DbCursor *pObject, int a, int b, int c);
}

static void *_MsgEATrax_hSoundRes = (void *)-1;
static MsgEATraxPlaylist_t *_MsgEATrax_pPlaylist = 0;

extern "C" {

void MsgEATraxLoadPlaylist(void)
{
    DbCursor cursor;
    DbCursor table;
    unsigned char i;

    for (i = 0; i <= 20; i++) {
        _MsgEATrax_pPlaylist->mEntries[i].mCategory = -1;
        _MsgEATrax_pPlaylist->mEntries[i].mRow = -1;
        _MsgEATrax_pPlaylist->mEntries[i].mState = 3;
    }
    PlaylistDbOpen(&cursor, 0);
    i = 0;
    PlaylistDbRemoveStationEntries(&cursor);
    EATraxDbOpen(&table);
    _MsgEATrax_pPlaylist->mCount = 40;
    if (PlaylistDbFirst(&cursor)) {
        do {
            _MsgEATrax_pPlaylist->mEntries[i].mState = 0;
            if (PlaylistDbGetIstx(&cursor) == 0) {
                PlaylistDbGetStationId(&cursor);
                PlaylistDbGetSongId(&cursor);
                _MsgEATrax_pPlaylist->mEntries[i].mCategory = 1;
                _MsgEATrax_pPlaylist->mEntries[i].mRow = 0;
            } else {
                _MsgEATrax_pPlaylist->mEntries[i].mCategory = 0;
                EATraxDbFindSong(&table, PlaylistDbGetSongId(&cursor), &_MsgEATrax_pPlaylist->mEntries[i].mRow);
            }
            i++;
            _MsgEATrax_pPlaylist->mCount--;
        } while (PlaylistDbNext(&cursor));
    }
    EATraxDbClose(&table);
    PlaylistDbClose(&cursor);
}

void MsgEATraxSavePlaylist(void)
{
    DbCursor cursor;
    DbCursor table;
    int changed = 0;
    unsigned char i;

    PlaylistDbOpen(&cursor, 0);
    EATraxDbOpen(&table);
    for (i = 0; i <= 20; i++) {
        int state = _MsgEATrax_pPlaylist->mEntries[i].mState;

        if (state == 1 || state == 2) {
            int isEATrax;
            int value;

            if (_MsgEATrax_pPlaylist->mEntries[i].mCategory == 0) {
                isEATrax = 1;
                DbCursorSeek(&table, _MsgEATrax_pPlaylist->mEntries[i].mRow);
                value = EATraxDbGetSongId(&table);
            } else {
                isEATrax = 0;
                value = 0;
            }
            if (_MsgEATrax_pPlaylist->mEntries[i].mState == 1) {
                PlaylistDbFindEntry(&cursor, isEATrax, 0, value);
                PlaylistDbDeleteRow(&cursor);
            } else {
                PlaylistDbAddEntry(&cursor, isEATrax, 0, value);
            }
            changed = 1;
        }
    }
    EATraxDbClose(&table);
    PlaylistDbClose(&cursor);
    if (changed) {
        SndgMusicReshuffle();
    }
}

void MsgEATraxGetCategory(int mode, int *pResult, MenuText_t *pText)
{
    int count = 0;

    if (mode == 0) {
        DbCursor table;

        EATraxDbOpen(&table);
        count = DbCursorGetRowCount(&table);
        *pResult = count;
        EATraxDbClose(&table);
        strnzcpy(pText->mpText, "EA TRAX", pText->mLength);
    } else if (mode - 1 < 0) {
        *pResult = count;
    } else {
        *pResult = count;
        strnzcpy(pText->mpText, " ", pText->mLength);
    }
}

int MsgEATraxGetFreeSlots(void)
{
    return _MsgEATrax_pPlaylist->mCount;
}

int MsgEATraxGetSongInfo(int mode, int key, MenuText_t **ppTexts)
{
    int result = 0;
    unsigned char i;

    if (mode == 0) {
        DbCursor table;

        EATraxDbOpen(&table);
        if (DbCursorSeek(&table, key)) {
            EATraxDbGetTitle(&table, ppTexts[0]->mpText, ppTexts[0]->mLength);
            EATraxDbGetArtist(&table, ppTexts[1]->mpText, ppTexts[1]->mLength);
            EATraxDbGetAlbum(&table, ppTexts[2]->mpText, ppTexts[2]->mLength);
            EATraxDbGetSongId(&table);
            for (i = 0; i <= 20; i++) {
                if (_MsgEATrax_pPlaylist->mEntries[i].mCategory == mode && _MsgEATrax_pPlaylist->mEntries[i].mRow == key) {
                    int state = _MsgEATrax_pPlaylist->mEntries[i].mState;

                    if (state == 0 || state == 2) {
                        result = 1;
                    }
                    break;
                }
            }
        }
        EATraxDbClose(&table);
    } else if (mode - 1 < 0) {
        for (i = 0; i <= 20; i++) {
            if (_MsgEATrax_pPlaylist->mEntries[i].mCategory == mode && _MsgEATrax_pPlaylist->mEntries[i].mRow == key) {
                int state = _MsgEATrax_pPlaylist->mEntries[i].mState;

                if (state == 0 || state == 2) {
                    result = 1;
                }
                break;
            }
        }
    }
    return result;
}

void MsgEATraxGetSongNames(int mode, int key, MenuText_t *pText1, MenuText_t *pText2, MenuText_t *pText3)
{
    if (mode == 0) {
        DbCursor table;

        EATraxDbOpen(&table);
        if (DbCursorSeek(&table, key)) {
            EATraxDbGetArtist(&table, pText1->mpText, pText1->mLength);
            EATraxDbGetTitle(&table, pText2->mpText, pText2->mLength);
            EATraxDbGetAlbum(&table, pText3->mpText, pText3->mLength);
        }
        EATraxDbClose(&table);
    }
}

void MsgEATraxPlaySong(int mode, int key)
{
    if (mode == 0) {
        DbCursor table;
        int value;

        EATraxDbOpen(&table);
        DbCursorSeek(&table, key);
        value = EATraxDbGetSongId(&table);
        EATraxDbClose(&table);
        SndgPathResumeTrack(0x11000001);
        SndgMusicPlaySong(1, 0, value);
    } else if (mode - 1 < 0) {
        SndgMusicPlaySong(0, 0, 0);
    }
}

void MsgEATraxStopSong(void)
{
    SndgMusicStop();
}

int MsgEATraxToggleSong(int a, int b)
{
    MsgEATraxPlaylist_t *pTable = _MsgEATrax_pPlaylist;
    int result = 0;
    int free = 21;
    unsigned char i;

    for (i = 0; i <= 20; i++) {
        if (pTable->mEntries[i].mCategory == a && pTable->mEntries[i].mRow == b) {
            int state = pTable->mEntries[i].mState;

            if (state == 0) {
                pTable->mEntries[i].mState = 1;
                result = 1;
            } else if (state == 1) {
                pTable->mEntries[i].mState = 0;
                result = 1;
                pTable->mCount--;
                break;
            } else if (state == 2) {
                if (b != 0) state++; // FAKEMATCH: dead increment (state is not read again); the extra block gives the target's r10 for pTable
                pTable->mEntries[i].mCategory = -1;
                result = 1;
                pTable->mEntries[i].mRow = -1;
                pTable->mEntries[i].mState = 3;
            } else {
                continue;
            }
            pTable->mCount++;
            break;
        } else if (pTable->mEntries[i].mCategory == -1 && pTable->mEntries[i].mRow == -1 && free == 21) {
            free = i;
        }
    }
    if (result == 0 && free != 21) {
        result = 1;
        _MsgEATrax_pPlaylist->mEntries[free].mState = 2;
        _MsgEATrax_pPlaylist->mEntries[free].mCategory = a;
        _MsgEATrax_pPlaylist->mEntries[free].mRow = b;
        _MsgEATrax_pPlaylist->mCount--;
    }
    return result;
}

void MsgEATraxEnter(void)
{
    _MsgEATrax_hSoundRes = ResOpenDevice(lbl_802EBFCC, 44);
    SndgSetVolumeOption(2, 100);
    if (SndgMusicIsPaused()) {
        SndgMusicResume();
    }
    SndgMusicStop();
    SndgMusicSetHold(1);
    _MsgEATrax_pPlaylist = (MsgEATraxPlaylist_t *)fn_801D2B7C(256, 0, 0);
    MsgEATraxLoadPlaylist();
}

void MsgEATraxExit(void)
{
    SndgSetVolumeOption(2, (unsigned char)(GameOptionsGet(5) * 10));
    SndgMusicSetHold(0);
    ResClose(_MsgEATrax_hSoundRes);
    fn_801D2BD0(_MsgEATrax_pPlaylist);
    _MsgEATrax_pPlaylist = 0;
    SndgMusicContinue();
}

int MsgEATraxHandleMessage(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult)
{
    switch (id) {
    case 0x80000001:
        *pResult = 0;
        break;
    case 0x80000002:
        MsgEATraxGetCategory(pArgs[0].i, pArgs[1].pi, pArgs[2].pParams);
        break;
    case 0x80000003:
        *pResult = MsgEATraxGetFreeSlots();
        break;
    case 0x80000004:
        *pResult = MsgEATraxGetSongInfo(pArgs[0].i, pArgs[1].i,
                               (MenuText_t **)(pArgs[2].i + (*pArgs[2].pi + 1) * 4));
        break;
    case 0x80000005:
        MsgEATraxGetSongNames(pArgs[0].i, pArgs[1].i, pArgs[2].pParams, pArgs[3].pParams, pArgs[4].pParams);
        break;
    case 0x80000006:
        MsgEATraxPlaySong(pArgs[0].i, pArgs[1].i);
        break;
    case 0x80000007:
        MsgEATraxStopSong();
        break;
    case 0x80000008:
        *pResult = MsgEATraxToggleSong(pArgs[0].i, pArgs[1].i);
        break;
    case 0x80000009:
        MsgEATraxEnter();
        break;
    case 0x8000000A:
        MsgEATraxExit();
        break;
    case 0x8000000B:
        MsgEATraxSavePlaylist();
        MsgEATraxLoadPlaylist();
        break;
    default:
        return 0;
    }
    return 1;
}

}
