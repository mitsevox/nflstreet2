/* Soundtrack music player (the FMSndgMusic module): keeps a shuffled play order of the
   soundtrack songs from the database, plays them on the music path-finder track, posts the
   game's music moods (mode changes) to that track, fades, pauses and resumes it, ramps its
   low-pass value and sends the current song's three text fields to the user interface. */
#include "engine/pathfinder.h"
#include "game/DbCursor.h"
#include "game/Query_8008352C.h"
#include "game/SndgPathfinder.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_8021D7B8.h"
#include "game/fn_802372EC.h"
#include "game/fn_800AD9B4.h"

#include <string.h>

struct SndgMusicText_t {
    int mUnknown0;
    unsigned int mUnknown4;
    char *mpUnknown8;
};

/* Allocation is 0x130 bytes; unaccessed words remain opaque. */
struct SndgMusicState_t {
    unsigned long long mUnknown0;
    unsigned long long mUnknown8;
    unsigned int mUnknown10;
    int mUnknown14;
    int mUnknown18;
    char mUnknown1C[4];
    void *mpUnknown20;
    int mUnknown24;
    int mUnknown28;
    int mUnknown2C;
    int mUnknown30;
    SndgMusicText_t mUnknown34[3];
    char mUnknown58[51];
    char mUnknown8B[51];
    char mUnknownBE[51];
    signed char mUnknownF1[40];
    char mUnknown119[3];
    int mUnknown11C;
    unsigned char mUnknown120;
    unsigned char mUnknown121;
    unsigned char mUnknown122;
    unsigned char mUnknown123;
    unsigned char mUnknown124;
    unsigned char mUnknown125;
    unsigned char mUnknown126;
    unsigned char mUnknown127;
    unsigned char mUnknown128;
    unsigned char mUnknown129;
    unsigned char mUnknown12A;
    char mUnknown12B[5];
};

/* The calendar helper writes all twelve bytes, including its final word. */
struct SndgMusicClock_t {
    char mUnknown0[12];
};

struct PathfinderStatus_t {
    int mUnknown0;
    char mUnknown4[44];
    int mUnknown30;
    char mUnknown34[4];
};

extern "C" {
extern void *gUISMainInfo;
extern void *gUISSubInfo;
extern char lbl_802EBF88[];
int FELoopIsMainFEActive(void);
int fn_801486A0(void);
void SndgUpdate(int a);
void SndgPathFadeTrack(int a, int b, unsigned int c);
void SndgPathSetStreamValue(int a, int b);
void SndgPathPauseTrack(int a);
void SndgPathResumeTrack(int a);
void SndgPathStopTrack(int a);
void SndgPathAddCallback(void (*callback)(int, int));
void SndgPathRemoveCallback(void (*callback)(int, int));
void fn_8007B358(DbCursor *p);
void fn_8007B3AC(DbCursor *p);
void fn_8007B3CC(DbCursor *p, int id, int *pResult);
void fn_8007B42C(DbCursor *p, char *pBuffer, int size);
void fn_8007B460(DbCursor *p, char *pBuffer, int size);
void fn_8007B494(DbCursor *p, char *pBuffer, int size);
void fn_8008352C(DbCursor *p, Query_8008352C *pQuery);
void fn_800835D0(DbCursor *p);
void fn_80083644(DbCursor *p);
int fn_800836A4(DbCursor *p, int a, int b, int c);
int fn_800837B8(DbCursor *p);
unsigned char fn_800837D8(DbCursor *p);
int fn_80083804(DbCursor *p);
int fn_8008382C(DbCursor *p);
int fn_801B3084(int flags, const char *pName, int value);
void fn_801CE7D0(int a);
void *ResOpenDevice(const char *pName, int flags);
void ResClose(void *p);
int fn_801F3E28(void);
unsigned long long fn_801F7D34(SndgMusicClock_t *p);
void fn_801F81F4(SndgMusicClock_t *p);
void fn_80219650(void *p, unsigned short *a, unsigned short *b);

static unsigned int _SndgMusic_uVolume = 100;
static SndgMusicState_t *_SndgMusic_pState = 0;
static unsigned char _SndgMusic_bRestart = 0;
static unsigned char _SndgMusic_bTextPending = 0;

void SndgMusicTrackCallback(int flags, int event);
void SndgMusicSetSongNum(int a, int b, int c);
int SndgMusicPostMode(int mode);
int SndgMusicApplyCutoff(int value);
void SndgMusicShufflePlaylist(void);
int SndgMusicNextPlaylistIndex(void);
void SndgMusicSelectNextSong(void);
void SndgMusicPublishSongText(void);
void SndgMusicFlushSongText(void);
void SndgMusicInit(void);
void SndgMusicShutdown(void);
void SndgMusicUpdate(void);
void SndgMusicReshuffle(void);
unsigned char SndgMusicGetSongCount(void);
void SndgMusicSetHold(unsigned char value);
void SndgMusicSetMode(int mode);
void SndgMusicPlaySong(int a, int b, int c);
void SndgMusicSetVolume(unsigned int value);
void SndgMusicFadeOut(unsigned int delay, int wait);
void SndgMusicFadeIn(unsigned int delay);
unsigned char SndgMusicIsPaused(void);
void SndgMusicPause(void);
void SndgMusicResume(void);
unsigned char SndgMusicIsPlaying(void);
void SndgMusicContinue(void);
void SndgMusicStop(void);
void SndgMusicRampCutoff(int value, unsigned int duration);
void SndgMusicPumpFrame(int draw);
void SndgMusicWaitForStart(int frames);
int SndgMusicGetMode(void);
void SndgMusicExitMode(int pauseAfter);

void SndgMusicTrackCallback(int flags, int event)
{
    if (flags & 0x1000000) {
        switch (event) {
        case 0x0: {
        case 0x7C:
        case 0xF8:
        case 0x174:
        case 0x1F0:
        case 0x26C:
        case 0x2E8:
        case 0x364:
        case 0x3E0:
        case 0x45C:
        case 0x4D8:
        case 0x554:
        case 0x5D0:
        case 0x64C:
        case 0x6C8:
        case 0x744:
        case 0x7C0:
        case 0x83C:
        case 0x8B8:
        case 0x934:
        case 0x9B0:
            SndgMusicState_t *p = _SndgMusic_pState;
            p->mUnknown127 = 1;
            p->mUnknown30 = p->mUnknown2C;
            SndgMusicPublishSongText();
            break;
        }
        case 0x75:
        case 0xF1:
        case 0x16D:
        case 0x1E9:
        case 0x265:
        case 0x2E1:
        case 0x35D:
        case 0x3D9:
        case 0x455:
        case 0x4D1:
        case 0x54D:
        case 0x5C9:
        case 0x645:
        case 0x6C1:
        case 0x73D:
        case 0x7B9:
        case 0x835:
        case 0x8B1:
        case 0x92D:
        case 0x9A9:
        case 0xA25:
            if (_SndgMusic_pState->mUnknown12A > 1 &&
                _SndgMusic_pState->mUnknown30 == _SndgMusic_pState->mUnknown2C) {
                SndgMusicSelectNextSong();
            }
            break;
        case -1:
            if (!_SndgMusic_pState->mUnknown129 && !_SndgMusic_pState->mUnknown122 && _SndgMusic_pState->mUnknown127) {
                _SndgMusic_bRestart = 1;
            }
            break;
        }
    }
}

void SndgMusicSetSongNum(int a, int b, int c)
{
    if (a) {
        fn_801B3084(0x1000000, "SongNum", c);
    }
}

int SndgMusicPostMode(int mode)
{
    int result = 0;
    if (_SndgMusic_pState->mUnknown121 || _SndgMusic_pState->mUnknown125) {
        int id = 0x1679406;
        int blocked = 0;
        int stop = 0;
        int start = 0;
        int same = 0;
        if (!_SndgMusic_pState->mUnknown122) {
            same = _SndgMusic_pState->mUnknown30 == _SndgMusic_pState->mUnknown2C;
        }
        switch (mode) {
        case 0: id = 0x1AC89E8; break;
        case 1: break;
        case 2: id = 0x18B0457; break;
        case 5: id = 0x199B6D8; break;
        case 6: id = 0x136E6A7; break;
        case 9:
            if (_SndgMusic_pState->mUnknown11C == 3 || _SndgMusic_pState->mUnknown11C == 15 ||
                _SndgMusic_pState->mUnknown11C == 14 || _SndgMusic_pState->mUnknown11C == 16 ||
                _SndgMusic_pState->mUnknown30 != _SndgMusic_pState->mUnknown2C) {
                blocked = 1;
            } else {
                id = 0x1262E0A;
            }
            break;
        case 7:
            if (_SndgMusic_pState->mUnknown30 != _SndgMusic_pState->mUnknown2C) {
                blocked = 1;
            } else {
                _SndgMusic_pState->mUnknown129 = 1;
                id = 0x19BE6DB;
            }
            break;
        case 8:
            if (_SndgMusic_pState->mUnknown11C != 7) {
                blocked = 1;
            } else {
                _SndgMusic_pState->mUnknown129 = 0;
                id = 0x1FDFBA7;
            }
            break;
        case 10:
            _SndgMusic_pState->mUnknown129 = 1;
            start = same;
            id = 0x1C739C4;
            break;
        case 11:
            _SndgMusic_pState->mUnknown129 = 0;
            stop = same;
            id = 0x1E045E4;
            break;
        case 3:
            start = same;
            _SndgMusic_pState->mUnknown129 = 1;
            id = 0x189CE52;
            _SndgMusic_pState->mUnknown128 = 1;
            break;
        case 4:
            _SndgMusic_pState->mUnknown129 = 0;
            stop = same;
            id = 0x156195E;
            _SndgMusic_pState->mUnknown128 = 0;
            break;
        case 14:
            _SndgMusic_pState->mUnknown128 = 1;
            id = 0x1BEFEF2;
            break;
        case 15:
            start = same;
            _SndgMusic_pState->mUnknown129 = 1;
            id = 0x1AA9D96;
            _SndgMusic_pState->mUnknown128 = 1;
            break;
        case 16: id = 0x1F322AD; break;
        case 17:
            _SndgMusic_pState->mUnknown129 = 0;
            stop = same;
            id = 0x18ABBB7;
            _SndgMusic_pState->mUnknown128 = 0;
            break;
        case 12:
            _SndgMusic_pState->mUnknown129 = 1;
            start = same;
            id = 0x11E6027;
            break;
        case 13:
            stop = same;
            _SndgMusic_pState->mUnknown129 = 0;
            id = 0x10DE592;
            break;
        default: blocked = 1; break;
        }
        if (!blocked && mode != 5 && mode != 6) {
            _SndgMusic_pState->mUnknown11C = mode;
        }
        if (stop) {
            fn_801B3084(0x1000000, "SongNum", 0);
            SndgPathPauseTrack(0x11000001);
        } else if (start) {
            fn_801B3084(0x1000000, "SongNum", 1);
            SndgPathResumeTrack(0x11000001);
        }
        if (!blocked) {
            result = SndgPathPostEvent(0x11000001, id);
        } else if ((unsigned int)(mode - 7) <= 2) {
            result = 1;
        }
    }
    return result;
}

int SndgMusicApplyCutoff(int value)
{
    if (_SndgMusic_pState->mUnknown121 || _SndgMusic_pState->mUnknown125) {
        SndgPathSetStreamValue(0x11000001, value);
    }
    return 1;
}

void SndgMusicShufflePlaylist(void)
{
    DbCursor cursor;
    unsigned int i;
    _SndgMusic_pState->mUnknown120 = 0;
    fn_8008352C(&cursor, 0);
    fn_800835D0(&cursor);
    unsigned int count = fn_800837B8(&cursor);
    for (i = 0; i < 40; ++i) {
        if (i < count) {
            _SndgMusic_pState->mUnknownF1[i] = i;
        } else {
            _SndgMusic_pState->mUnknownF1[i] = -1;
        }
    }
    if (count) {
        for (int round = 0; round <= 7; ++round) {
            for (i = 0; i < count - 1; ++i) {
                int k = i + fn_802372EC(1, count - i);
                signed char first = _SndgMusic_pState->mUnknownF1[i];
                signed char second = _SndgMusic_pState->mUnknownF1[k];
                _SndgMusic_pState->mUnknownF1[k] = first;
                _SndgMusic_pState->mUnknownF1[i] = second;
            }
        }
        _SndgMusic_pState->mUnknown121 = 1;
    } else {
        _SndgMusic_pState->mUnknown121 = 0;
        SndgMusicStop();
    }
    fn_80083644(&cursor);
    _SndgMusic_pState->mUnknown12A = count;
}

int SndgMusicNextPlaylistIndex(void)
{
    unsigned char index = _SndgMusic_pState->mUnknown120;
    int result = _SndgMusic_pState->mUnknownF1[index];
    if (index == 39 || (_SndgMusic_pState->mUnknownF1[index + 1] & 0x80)) {
        _SndgMusic_pState->mUnknown120 = 0;
    } else {
        ++_SndgMusic_pState->mUnknown120;
    }
    return result;
}

void SndgMusicSelectNextSong(void)
{
    if (!_SndgMusic_pState->mUnknown126) {
        DbCursor cursor;
        Query_8008352C query;
        query.mUnknown4 = 0;
        query.mUnknown8 = 0;
        query.mUnknown0 = 1;
        fn_8008352C(&cursor, &query);
        if (fn_800837B8(&cursor)) {
            DbCursorSeek(&cursor, SndgMusicNextPlaylistIndex());
            _SndgMusic_pState->mUnknown122 = fn_800837D8(&cursor);
            _SndgMusic_pState->mUnknown28 = fn_80083804(&cursor);
            _SndgMusic_pState->mUnknown2C = fn_8008382C(&cursor);
        } else {
            _SndgMusic_pState->mUnknown121 = 0;
        }
        fn_80083644(&cursor);
    }
}

void SndgMusicPublishSongText(void)
{
    DbCursor cursor;
    if ((!FELoopIsMainFEActive() && !_SndgMusic_bTextPending) || !_SndgMusic_uVolume || _SndgMusic_pState->mUnknown124) {
        _SndgMusic_bTextPending = 1;
    } else {
        unsigned short a, b;
        if (gUISMainInfo) {
            fn_80219650(gUISMainInfo, &a, &b);
            if (a == 5 && b == 1) {
                return;
            }
        }
        if (_SndgMusic_pState->mUnknown122) {
            fn_8007B358(&cursor);
            fn_8007B3CC(&cursor, _SndgMusic_pState->mUnknown2C, 0);
            fn_8007B42C(&cursor, _SndgMusic_pState->mUnknown58, 51);
            fn_8007B460(&cursor, _SndgMusic_pState->mUnknown8B, 51);
            fn_8007B494(&cursor, _SndgMusic_pState->mUnknownBE, 51);
            fn_8007B3AC(&cursor);
        }
        struct {
            int count;
            SndgMusicText_t *records[3];
        } args;
        args.count = 3;
        args.records[0] = &_SndgMusic_pState->mUnknown34[0];
        args.records[0]->mpUnknown8 = _SndgMusic_pState->mUnknown58;
        args.records[0]->mUnknown4 = strlen(_SndgMusic_pState->mUnknown58);
        args.records[1] = &_SndgMusic_pState->mUnknown34[1];
        args.records[1]->mpUnknown8 = _SndgMusic_pState->mUnknown8B;
        args.records[1]->mUnknown4 = strlen(_SndgMusic_pState->mUnknown8B);
        args.records[2] = &_SndgMusic_pState->mUnknown34[2];
        args.records[2]->mpUnknown8 = _SndgMusic_pState->mUnknownBE;
        args.records[2]->mUnknown4 = strlen(_SndgMusic_pState->mUnknownBE);
        if (gUISSubInfo) {
            _SndgMusic_bTextPending = 0;
            fn_8021D7B8(gUISSubInfo, 0x80000004, 4, &args);
        }
    }
}

void SndgMusicFlushSongText(void)
{
    if (_SndgMusic_bTextPending) {
        int ready = 0;
        if (FELoopIsMainFEActive() || !fn_801486A0() || fn_801486A0() == 1 || fn_800AD9B4() != 3) {
            ready = 1;
        }
        if (ready) {
            SndgMusicPublishSongText();
        }
    }
}

void SndgMusicInit(void)
{
    _SndgMusic_pState = (SndgMusicState_t *)fn_801D2B7C(0x130, 0, 0);
    fn_801C1F94(_SndgMusic_pState, 0, 0x130);
    _SndgMusic_pState->mUnknown18 = 20000;
    _SndgMusic_pState->mpUnknown20 = (void *)-1;
    _SndgMusic_pState->mUnknown24 = -1;
    _SndgMusic_pState->mUnknown14 = 20000;
    _SndgMusic_pState->mUnknown128 = 0;
    _SndgMusic_pState->mUnknown129 = 0;
    _SndgMusic_pState->mUnknown11C = 19;
    _SndgMusic_pState->mUnknown122 = 1;
    _SndgMusic_pState->mUnknown127 = 1;
    DbCursor cursor;
    fn_8008352C(&cursor, 0);
    _SndgMusic_pState->mUnknown12A = fn_800837B8(&cursor);
    if (_SndgMusic_pState->mUnknown12A) {
        _SndgMusic_pState->mUnknown121 = 1;
    }
    fn_80083644(&cursor);
    if (fn_801F3E28()) {
        _SndgMusic_pState->mpUnknown20 = ResOpenDevice(lbl_802EBF88, 44);
        _SndgMusic_pState->mUnknown24 = SndgPathLoadMap(_SndgMusic_pState->mpUnknown20, 1);
        SndgPathCreateTrack(_SndgMusic_pState->mpUnknown20, 2, 0x11000001, 2.0f);
        SndgPathAddCallback(SndgMusicTrackCallback);
        SndgMusicSetVolume(_SndgMusic_uVolume);
        SndgMusicSelectNextSong();
        SndgMusicSetSongNum(_SndgMusic_pState->mUnknown122, _SndgMusic_pState->mUnknown28, _SndgMusic_pState->mUnknown2C);
    }
}

void SndgMusicShutdown(void)
{
    if (fn_801F3E28()) {
        SndgPathRemoveCallback(SndgMusicTrackCallback);
        SndgPathDestroyTrack(0x11000001);
        SndgPathUnloadMap(_SndgMusic_pState->mUnknown24);
        ResClose(_SndgMusic_pState->mpUnknown20);
    }
    fn_801D2BD0(_SndgMusic_pState);
    _SndgMusic_pState = 0;
}

void SndgMusicUpdate(void)
{
    if (fn_801F3E28()) {
        SndgMusicClock_t calendar;
        fn_801F81F4(&calendar);
        unsigned long long now = fn_801F7D34(&calendar);
        if (_SndgMusic_pState->mUnknown0 && now > _SndgMusic_pState->mUnknown0) {
            SndgMusicState_t *p = _SndgMusic_pState;
            if (p->mUnknown18 < p->mUnknown14) {
                int value = p->mUnknown18 + (now - p->mUnknown0) * p->mUnknown10;
                if (value > p->mUnknown14) {
                    value = p->mUnknown14;
                }
                p->mUnknown18 = value;
                SndgMusicApplyCutoff(value);
            } else if (p->mUnknown18 > p->mUnknown14) {
                int value = p->mUnknown18 - (now - p->mUnknown0) * p->mUnknown10;
                if (value < p->mUnknown14) {
                    value = p->mUnknown14;
                }
                _SndgMusic_pState->mUnknown18 = value;
                SndgMusicApplyCutoff(value);
            }
            _SndgMusic_pState->mUnknown0 = _SndgMusic_pState->mUnknown18 == _SndgMusic_pState->mUnknown14 ? 0 : now;
        }
        if (_SndgMusic_pState->mUnknown8 && now > _SndgMusic_pState->mUnknown8) {
            _SndgMusic_pState->mUnknown8 = 0;
            SndgMusicPause();
        }
        if (_SndgMusic_bRestart) {
            _SndgMusic_bRestart = 0;
            SndgPathStopTrack(0x11000001);
            SndgMusicPlaySong(_SndgMusic_pState->mUnknown122, _SndgMusic_pState->mUnknown28, _SndgMusic_pState->mUnknown2C);
        } else {
            SndgMusicSetSongNum(_SndgMusic_pState->mUnknown122, _SndgMusic_pState->mUnknown28, _SndgMusic_pState->mUnknown2C);
        }
    }
}

void SndgMusicReshuffle(void)
{
    SndgMusicStop();
    SndgMusicShufflePlaylist();
}

unsigned char SndgMusicGetSongCount(void) { return _SndgMusic_pState->mUnknown12A; }
void SndgMusicSetHold(unsigned char value)
{
    if (_SndgMusic_pState) {
        _SndgMusic_pState->mUnknown126 = value;
    }
}

void SndgMusicSetMode(int mode)
{
    if ((unsigned int)mode <= 17) {
        SndgMusicPostMode(mode);
        switch (mode) {
        case 0: _SndgMusic_pState->mUnknown123 = 1; break;
        case 1: _SndgMusic_pState->mUnknown123 = 0; break;
        case 5: _SndgMusic_pState->mUnknown124 = 1; break;
        case 6: _SndgMusic_pState->mUnknown124 = 0; break;
        }
    }
}

void SndgMusicPlaySong(int a, int b, int c)
{
    SndgMusicStop();
    _SndgMusic_pState->mUnknown125 = 1;
    if (a) {
        _SndgMusic_pState->mUnknown122 = 1;
        _SndgMusic_pState->mUnknown28 = b;
        _SndgMusic_pState->mUnknown2C = c;
        SndgMusicSetSongNum(a, b, c);
        SndgMusicPostMode(0);
    } else {
        _SndgMusic_pState->mUnknown122 = 0;
        _SndgMusic_pState->mUnknown127 = 0;
        _SndgMusic_pState->mUnknown2C = c;
        _SndgMusic_pState->mUnknown28 = b;
        _SndgMusic_pState->mUnknown30 = c;
        fn_801B3084(0x1000000, "SongNum", 0);
        SndgMusicPublishSongText();
    }
    _SndgMusic_pState->mUnknown123 = 1;
    _SndgMusic_pState->mUnknown128 = 0;
    _SndgMusic_pState->mUnknown129 = 0;
}

void SndgMusicSetVolume(unsigned int value)
{
    _SndgMusic_uVolume = value;
    if (_SndgMusic_pState) {
        SndgPathSetTrackVolume(0x11000001, value);
    }
}

void SndgMusicFadeOut(unsigned int delay, int wait)
{
    if (fn_801F3E28() && _SndgMusic_pState->mUnknown123 && !_SndgMusic_pState->mUnknown124) {
        SndgMusicExitMode(0);
        SndgMusicClock_t calendar;
        fn_801F81F4(&calendar);
        _SndgMusic_pState->mUnknown8 = fn_801F7D34(&calendar) + delay;
        if (_SndgMusic_pState->mUnknown122 || _SndgMusic_pState->mUnknown128) {
            SndgPathFadeTrack(0x11000001, 0, delay);
        }
        if (FELoopIsMainFEActive() && gUISSubInfo) {
            fn_8021D7B8(gUISSubInfo, 0x80000003, 0, 0);
        }
        if (wait) {
            while (_SndgMusic_pState->mUnknown8) {
                SndgMusicPumpFrame(1);
            }
        }
    }
}

void SndgMusicFadeIn(unsigned int delay)
{
    if (fn_801F3E28()) {
        SndgMusicExitMode(1);
        SndgMusicPumpFrame(1);
        if (_SndgMusic_pState->mUnknown123 &&
            (_SndgMusic_pState->mUnknown124 || _SndgMusic_pState->mUnknown8 || _SndgMusic_uVolume)) {
            SndgMusicResume();
            if (_SndgMusic_pState->mUnknown122 || _SndgMusic_pState->mUnknown128) {
                SndgPathFadeTrack(0x11000001, 100, delay);
            }
            _SndgMusic_pState->mUnknown8 = 0;
            SndgMusicPumpFrame(1);
            SndgMusicWaitForStart(90);
        }
    }
}

unsigned char SndgMusicIsPaused(void)
{
    unsigned char result = 0;
    if (_SndgMusic_pState) {
        result = _SndgMusic_pState->mUnknown124;
    }
    return result;
}

void SndgMusicPause(void)
{
    if ((_SndgMusic_pState->mUnknown121 || _SndgMusic_pState->mUnknown125) &&
        _SndgMusic_pState->mUnknown123 && !_SndgMusic_pState->mUnknown124) {
        if (_SndgMusic_pState->mUnknown122 || _SndgMusic_pState->mUnknown128) {
            SndgPathPauseTrack(0x11000001);
        }
        _SndgMusic_pState->mUnknown124 = 1;
    }
}

void SndgMusicResume(void)
{
    if ((_SndgMusic_pState->mUnknown121 || _SndgMusic_pState->mUnknown125) && _SndgMusic_uVolume &&
        _SndgMusic_pState->mUnknown124) {
        if (_SndgMusic_pState->mUnknown122 || _SndgMusic_pState->mUnknown128) {
            SndgPathResumeTrack(0x11000001);
        }
        _SndgMusic_pState->mUnknown124 = 0;
    }
}

unsigned char SndgMusicIsPlaying(void) { return _SndgMusic_pState->mUnknown123; }

void SndgMusicContinue(void)
{
    if (fn_801F3E28() && _SndgMusic_pState) {
        _SndgMusic_pState->mUnknown125 = 0;
        if (_SndgMusic_pState->mUnknown121 && _SndgMusic_uVolume) {
            SndgMusicResume();
            int next = 1;
            if (_SndgMusic_pState->mUnknown123) {
                DbCursor cursor;
                fn_8008352C(&cursor, 0);
                if (fn_800836A4(&cursor, _SndgMusic_pState->mUnknown122, _SndgMusic_pState->mUnknown28,
                               _SndgMusic_pState->mUnknown2C)) {
                    next = 0;
                    SndgMusicPublishSongText();
                } else {
                    SndgMusicStop();
                }
                fn_80083644(&cursor);
            }
            if (next) {
                SndgMusicSelectNextSong();
                SndgMusicPlaySong(_SndgMusic_pState->mUnknown122, _SndgMusic_pState->mUnknown28, _SndgMusic_pState->mUnknown2C);
            }
        } else {
            SndgMusicStop();
        }
    }
}

void SndgMusicStop(void)
{
    if (_SndgMusic_pState) {
        if (_SndgMusic_pState->mUnknown123) {
            if (_SndgMusic_pState->mUnknown122 || _SndgMusic_pState->mUnknown127) {
                SndgPathResumeTrack(0x11000001);
                SndgPathStopTrack(0x11000001);
            }
            _SndgMusic_pState->mUnknown124 = 0;
            _SndgMusic_pState->mUnknown123 = 0;
            if (FELoopIsMainFEActive() && gUISSubInfo) {
                fn_8021D7B8(gUISSubInfo, 0x80000003, 0, 0);
            }
        }
        _SndgMusic_pState->mUnknown125 = 0;
    }
}

void SndgMusicRampCutoff(int value, unsigned int duration)
{
    SndgMusicState_t *p = _SndgMusic_pState;
    if (p->mUnknown122) {
        p->mUnknown14 = value;
        if (!duration) {
            if (p->mUnknown18 != value) {
                p->mUnknown18 = value;
                SndgMusicApplyCutoff(value);
            }
        } else {
            p->mUnknown10 = (value < p->mUnknown18 ? p->mUnknown18 - value : value - p->mUnknown18) / duration;
            SndgMusicClock_t calendar;
            fn_801F81F4(&calendar);
            _SndgMusic_pState->mUnknown0 = fn_801F7D34(&calendar);
        }
    }
}

void SndgMusicPumpFrame(int draw)
{
    SndgUpdate(1);
    if (draw) {
        fn_801CE7D0(1);
    }
}

void SndgMusicWaitForStart(int frames)
{
    PathfinderStatus_t info;
    PathfinderGetStatus(0x11000001, &info);
    if (_SndgMusic_pState && fn_801F3E28() && info.mUnknown0 >= 0 && _SndgMusic_pState->mUnknown122) {
        int count = 0;
        int previous = info.mUnknown30;
        if (frames <= 0) {
            frames = 90;
        }
        int limit = frames * 1000 / 60;
        if (!_SndgMusic_pState->mUnknown124) {
            while (info.mUnknown30 < limit && count < frames) {
                ++count;
                SndgMusicPumpFrame(1);
                previous = info.mUnknown30;
                PathfinderGetStatus(0x11000001, &info);
                if (_SndgMusic_pState->mUnknown124 || info.mUnknown30 > previous) {
                    return;
                }
            }
        }
    }
}

int SndgMusicGetMode(void)
{
    if (!_SndgMusic_pState) {
        return 19;
    }
    return _SndgMusic_pState->mUnknown11C;
}

void SndgMusicExitMode(int pauseAfter)
{
    int handled = 1;
    switch (_SndgMusic_pState->mUnknown11C) {
    case 7: SndgMusicSetMode(8); break;
    case 10: SndgMusicSetMode(11); break;
    case 12: SndgMusicSetMode(13); break;
    case 3: SndgMusicSetMode(4); break;
    case 15:
        SndgMusicSetMode(16);
        for (int i = 20; i; --i) {
            SndgMusicPumpFrame(1);
        }
    case 14:
        SndgMusicSetMode(17);
        for (int i = 20; i; --i) {
            SndgMusicPumpFrame(1);
        }
        break;
    default: handled = 0; break;
    }
    if (handled && pauseAfter) {
        SndgMusicPumpFrame(1);
        SndgMusicPause();
    }
}
}
