/* Game-event sounds: turns the in-game audio events (hits, footsteps, catches, whistles,
   crowd moments, pauses) into sound effects, music modes and crowd reactions, and streams
   the crowd and level sound banks during a game. */

#include "game/PlayBookGetPlay.h"
#include "game/SndgPathfinder.h"
#include "game/Block_800C9D6C.h"
#include "game/Object_8003DEC4.h"
#include "game/LevelSurface.h"
#include "game/ScrmGetBallSpot.h"
#include "game/Replay.h"
#include "game/SndgCrowd.h"
#include "game/Object_80039F5C.h"
#include "game/AudmonEvent.h"
#include "game/Ball.h"
#include "game/PlayBookDb.h"
#include "game/ScrmGetTeamPlayerCount.h"
#include "game/Vec3Magnitude.h"
#include "game/GameModeType.h"
#include "game/SyncRandGetRange.h"

struct SndgEventRecord_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    float mUnknownC;
    float mUnknown10;
    unsigned short mUnknown14;
};

extern "C" {

int GameOptionsGet(int id);
int fn_800A8444(int index);
void SndgSetVolumeOption(unsigned int index, unsigned int value);
void SndgAmbStopAllAndCue(void);
void SndgMusicSetMode(int mode);
void SndgMusicPause(void);
void SndgMusicResume(void);
void SndgAmbObjStop(int type, unsigned int index);
void SndgAmbPostCue(int type);
int SndgAmbObjExists(int type, unsigned int index);
unsigned int SndgAmbObjFindSlot(int type, int value);
void SndgSoundObjControl(int type, int mode, Vector_80039F5C *pPos, void *pObject, int index);
void SndgSoundObjUpdateFromEvent(int type, AudmonEvent_t *pRecord);
void SndgFadeOutChannelGroup(void);
void SndgSpchSetPlayFlags(int flags);
void SndgSituationReset(void);
unsigned char ReplayIsShowing(Type_803EA368 *p);
int fn_800A9680(void);
int SndgMusicGetMode(void);
int PlayAlignHasSlots(PlayBookPlay_t *pRecord);
int ScrmGetSnapOffense(void);
static const unsigned int _SndgEvent_aCrowdEvents[4] = {5, 10, 12, 15};
extern float gPlyrMoveFwdSpeed;
extern unsigned char lbl_803EA6EC;
extern unsigned char lbl_803EA6F8;
extern unsigned int lbl_803EA6E0;
void SndgEventCycleCrowdBanks(void);
void SndgEventCycleBanks145(void);
void SndgEventLoadFormationBank(void);
void SndgEventCycleBanks77(void);
void SndgEventLoadLevelBank(void);
void SndgEventLoadTeamBanks(void);
int SndgEventPlayVariant18(Vector_80039F5C *pPos);
int SndgEventPlayVariant24(Vector_80039F5C *pPos);
void SndgEventQueueDelayed(Vector_80039F5C *pPos);
int SndgEventPlayGroup(int id, Vector_80039F5C *pPos);
int SndgEventPlayGroupVolume(int id, Vector_80039F5C *pPos, unsigned int volume);
int SndgEventGetFootstepSfx(int unused, int value);


int ScrmGetDown(void);
int fn_801486A0(void);
int ScrmGetOffenseTeam(void);
int ScrmGetDefenseTeam(void);
PlayBookFormation_t *PlayBookGetFormation(int side);
int SndgSfxIsPlaying(int id);
void SndgSfxStop(int id);
int SndgRequestBank(unsigned int channel, int id, void (*callback)(int handle));
int SndgIsBankIndexLoaded(int channel, int id);
int SndgIsBankReady(unsigned int channel);
int SndgSfxPlayVolume(int id, Vector_80039F5C *pos, unsigned char volume);
unsigned char SndgSfxGetVolume(int id);
unsigned char SndgIsInit(void);
void SndgNullUpdate(void);
int fn_800A3444(void);
int FileHostCheckActive(void);
void FileDebugProcess(void);
void SndService(void);
int SndPatchOver(int handle);
unsigned int SysGetSystemTime(void);
void Vec2Sub(void *out, void *a, void *b);
int SyncRandBitPoolNew(int a, int b);
int SyncRandBitPoolDraw(int handle);
void SyncRandBitPoolDelete(int handle);
extern unsigned char lbl_802D63D0[];
static const unsigned char _SndgEvent_aSfxGroups[][2] = {
    {0x44, 4}, {0x66, 2}, {0x4C, 2}, {0x48, 4}, {0x50, 4}, {0x54, 4},
    {0x58, 4}, {0x5C, 4}, {0x60, 4}, {0x64, 2}, {0x4E, 2},
};
static Vector_80039F5C _SndgEvent_DelayedPos;
extern int lbl_803EA6C0;
extern unsigned char lbl_803EA6C4;
extern unsigned char lbl_803EA6C5;
extern unsigned char lbl_803EA6C6;
extern unsigned char lbl_803EA6C7;
extern unsigned char lbl_803EA6C8;
extern unsigned char lbl_803EA6C9;
extern unsigned char lbl_803EA6CA;
extern unsigned char lbl_803EA6CF;
extern unsigned char lbl_803EA6D0;
extern unsigned char lbl_803EA6D1;
extern unsigned char lbl_803EA6D2;
extern unsigned char lbl_803EA6D3;
extern unsigned char lbl_803EA6D4;
extern unsigned char lbl_803EA6D5;
extern unsigned char lbl_803EA6D6;
extern unsigned char lbl_803EA6D7;
extern unsigned char lbl_803EA6D8;
extern unsigned char lbl_803EA6DB;
extern unsigned char lbl_803EA6DC;
extern unsigned char lbl_803EA6E4;
extern unsigned char lbl_803EA6E5;
extern int lbl_803EA6E8;
extern unsigned int lbl_803EA6F0;
extern int lbl_803EA6F4;
extern unsigned char lbl_803EA6FA;
extern unsigned char lbl_803EA6FB;
static int _SndgEvent_iCrowdBankPool;
static int _SndgEvent_iRandomPool1;
static int _SndgEvent_iFormationPoolLarge;
static int _SndgEvent_iFormationPoolMedium;
static int _SndgEvent_iFormationPoolSmall;
static int _SndgEvent_iRandomPool5;
static int _SndgEvent_iRandomPool6;
static int _SndgEvent_iRandomPool7;
static int _SndgEvent_iRandomPool8;


void SndgSfxSetVolume(int index, int value, unsigned char volume);
int SndgSfxPlay(int index, Vector_80039F5C *p);

extern unsigned char lbl_803EA6CC;
extern unsigned char lbl_803EA6CD;
extern unsigned char lbl_803EA6CE;
extern unsigned char lbl_803EA6F9;
extern unsigned char lbl_803EA6D9;
extern unsigned char lbl_803EA6DA;

int SndgEventPlaySfx34(Vector_80039F5C *p);
int SndgEventPlaySfx35(Vector_80039F5C *p);
void SndgEventSetSfx34Volume(void);
int SndgEventGetSurfaceSfx(int value);
void SndgEventSetCrowdCycle(int value);

void SndgEventInit(void)
{
    lbl_803EA6CC = lbl_803EA6CD = 1;
}

void SndgEventShutdown(void)
{
}

void SndgEventSetSfx5Volume(int value)
{
    SndgSfxSetVolume(5, value, 0);
}

void SndgEventProcess(AudmonEvent_t *p)
{
    int value;
    Vector_80039F5C *pos;

    switch (p->mType) {
    case 53: SndgSfxPlay(48, &p->mPos); break;
    case 50: SndgSfxPlay(55, &p->mPos); break;
    case 51: SndgSfxPlay(56, &p->mPos); break;
    case 52: SndgSfxPlay(57, &p->mPos); break;
    case 48:
        SndgCrowdTriggerEvent(14, fn_8009BCE8(&p->mUnknown0)->mIdBytes[2]);
        SndgSfxPlay(54, &p->mPos);
        break;
    case 49:
        SndgCrowdTriggerEvent(15, fn_8009BCE8(&p->mUnknown0)->mIdBytes[2]);
        SndgSfxPlay(53, &p->mPos);
        break;
    case 132: SndgAmbStopAllAndCue(); SndgCrowdTriggerEvent(2, 0); break;
    case 126: SndgMusicSetMode(10); break;
    case 127: SndgMusicSetMode(11); break;
    case 107: case 128:
        if ((unsigned char)(GameOptionsGet(5) * 10) > 52 && !fn_800A8444(0) && !fn_800A8444(1)) SndgSetVolumeOption(2, 52);
        break;
    case 109: case 130: SndgSetVolumeOption(2, (unsigned char)(GameOptionsGet(5) * 10) & ~1U); break;
    case 88: {
        value = 15;
        Object_80039F5C *player = fn_8009BCE8(&p->mUnknown0);
        Object_8003DEC4 *pose = (Object_8003DEC4 *)player->mpUnknown4;
        if (pose && pose->mUnknown972) value = ((LevelSurface_t *)pose->mUnknown972)->mSurface;
        int id = SndgEventGetSurfaceSfx(value);
        if (BallGetCurrentHolder() == player) {
            SndgSfxPlayVolume(id, &p->mPos,
                (unsigned char)(SndgSfxGetVolume(id) * 2 <= 127 ? SndgSfxGetVolume(id) * 2 : 127));
        } else SndgSfxPlay(id, &p->mPos);
        break;
    }
    case 97: {
        Block_800C9D6C *table = fn_800CA8EC();
        value = 0;
        unsigned char index = 0;
        unsigned int side = ((unsigned int)p->mUnknown0 >> 8) & 255;
        while (index < 2) {
            if (table->mEntries[side][index].mRef == p->mUnknown0) { value = table->mEntries[side][index].mUnknown10 == 1; break; }
            index++;
        }
        int id;
        if (p->mUnknown10.mValue == 12) {
            SndgEventPlayVariant24(&p->mPos);
            break;
        }
        if (p->mUnknown10.mValue == 34) id = value ? 46 : 45;
        else if (p->mUnknown10.mValue == 35) id = value ? 48 : 47;
        else if (p->mUnknown10.mValue == 36) id = value ? 50 : 49;
        else if (p->mUnknown10.mValue == 43) id = value ? 52 : 51;
        else break;
        pos = &p->mPos;
        SndgSfxPlay(id, pos);
        SndgEventPlayVariant18(pos);
        break;
    }
    case 36: {
        value = 15;
        Object_80039F5C *player = fn_8009BCE8(&p->mUnknown0);
        Object_8003DEC4 *pose = (Object_8003DEC4 *)player->mpUnknown4;
        if (pose && pose->mUnknown972) value = ((LevelSurface_t *)pose->mUnknown972)->mSurface;
        int state = fn_800A3444();
        lbl_803EA6D1 = (lbl_803EA6D1 + 1) % 2;
        SndgSfxPlay(lbl_803EA6D1 + SndgEventGetFootstepSfx(state, value), &p->mPos);
        break;
    }
    case 101: SndgEventPlaySfx34(&p->mPos); break;
    case 102: SndgEventSetSfx34Volume(); break;
    case 103: SndgEventPlaySfx35(&p->mPos); break;
    case 62:
        if (p->mUnknown14 || !p->mUnknown0) {
            SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
            SndgSfxPlay(108, &p->mPos);
        } else { SndgEventPlayGroup(10, &p->mPos); SndgEventQueueDelayed(&p->mPos); }
        break;
    case 63:
        if (p->mUnknown14 || !p->mUnknown0) {
            SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
            SndgSfxPlay(104, &p->mPos);
        } else {
            unsigned char volume;
            if (lbl_803EA6EC) volume = 100;
            else {
                unsigned int scaled = p->mUnknown10.mValue * 4;
                if (scaled > 24) volume = (unsigned char)(scaled > 100 ? 100 : scaled);
                else volume = 25;
            }
            SndgEventPlayGroupVolume(0, &p->mPos, volume);
        }
        break;
    case 65:
        if (p->mUnknown14 || !p->mUnknown0) {
            SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
            SndgSfxPlay(106, &p->mPos);
        } else SndgEventPlayGroup(3, &p->mPos);
        break;
    case 66:
        if (p->mUnknown14) {
            SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
            SndgSfxPlay(105, &p->mPos);
        }
        break;
    case 67:
        if (p->mUnknown14 || !p->mUnknown0) {
            SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
            SndgSfxPlay(110, &p->mPos);
        } else {
            unsigned char volume;
            if (lbl_803EA6EC) volume = 100;
            else {
                unsigned int scaled = p->mUnknown10.mValue * 4;
                if (scaled > 24) volume = (unsigned char)(scaled > 100 ? 100 : scaled);
                else volume = 25;
            }
            SndgEventPlayGroupVolume(2, &p->mPos, volume);
        }
        break;
    case 68:
        if (p->mUnknown14 || !p->mUnknown0) {
            SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
            SndgSfxPlay(106, &p->mPos);
        } else { SndgEventPlayGroup(4, &p->mPos); SndgEventQueueDelayed(&p->mPos); }
        break;
    case 69:
        if (p->mUnknown14 || !p->mUnknown0) {
            SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
            SndgSfxPlay(108, &p->mPos);
        } else { SndgEventPlayGroup(5, &p->mPos); SndgEventQueueDelayed(&p->mPos); }
        break;
    case 70:
        if (p->mUnknown14 || !p->mUnknown0) {
            SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
            SndgSfxPlay(108, &p->mPos);
        } else { SndgEventPlayGroup(6, &p->mPos); SndgEventQueueDelayed(&p->mPos); }
        break;
    case 72:
        if (p->mUnknown14 || !p->mUnknown0) {
            SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
            SndgSfxPlay(105, &p->mPos);
        }
        break;
    case 73:
        if (p->mUnknown14 || !p->mUnknown0) {
            SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
            SndgSfxPlay(110, &p->mPos);
        } else {
            unsigned char volume;
            if (lbl_803EA6EC) volume = 100;
            else {
                unsigned int scaled = p->mUnknown10.mValue * 4;
                if (scaled > 24) volume = (unsigned char)(scaled > 100 ? 100 : scaled);
                else volume = 25;
            }
            SndgEventPlayGroupVolume(8, &p->mPos, volume);
        }
        break;
    case 64: case 74:
        if (p->mUnknown14 || !p->mUnknown0) SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
        SndgEventPlayGroup(9, &p->mPos);
        break;
    case 75:
        if (p->mUnknown14) {
            SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
            SndgSfxPlay(111, &p->mPos);
        } else SndgEventPlayGroup(8, &p->mPos);
        break;
    case 76:
        if (p->mUnknown14 || !p->mUnknown0) {
            SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
            SndgSfxPlay(112, &p->mPos);
        }
        break;
    case 77:
        if (p->mUnknown14 || !p->mUnknown0) {
            SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
            SndgSfxPlay(107, &p->mPos);
        } else { SndgEventPlayGroup(8, &p->mPos); SndgEventQueueDelayed(&p->mPos); }
        break;
    case 47: SndgAmbObjStop(4, (unsigned char)p->mUnknown18); break;
    case 78:
        SndgEventPlayGroup(1, &p->mPos);
        if (p->mUnknown14) SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
        else SndgEventQueueDelayed(&p->mPos);
        break;
    case 86: case 87:
        if (SndgAmbObjExists(7, 0)) SndgSoundObjControl(7, 2, &p->mPos, 0, 0);
        else SndgSoundObjControl(7, 1, &p->mPos, 0, 0);
        break;
    case 85: SndgSoundObjUpdateFromEvent(12, p); break;
    case 81: SndgSoundObjUpdateFromEvent(5, p); break;
    case 79: SndgSoundObjUpdateFromEvent(8, p); break;
    case 80: SndgSoundObjUpdateFromEvent(11, p); break;
    case 82: SndgSoundObjUpdateFromEvent(9, p); break;
    case 83: SndgSoundObjUpdateFromEvent(10, p); break;
    case 84:
        if (SndgAmbObjExists(6, (unsigned char)SndgAmbObjFindSlot(6, p->mUnknown18))) SndgSoundObjControl(6, 2, &p->mPos, 0, 0);
        else SndgSoundObjControl(6, 1, &p->mPos, 0, 0);
        break;
    case 44: lbl_803EA6EC = 1; break;
    case 46: SndgEventQueueDelayed(&p->mPos); break;
    case 96: if (p->mUnknown10.mValue <= 4) SndgEventPlayVariant18(&p->mPos); break;
    case 22: SndgSfxPlay(132, 0); break;
    case 23: SndgSfxPlay(133, 0); break;
    case 8: SndgMusicSetMode(3); break;
    case 9: SndgMusicSetMode(4); break;
    case 11: SndgMusicSetMode(14); break;
    case 10: SndgMusicSetMode(15); break;
    case 13: SndgMusicSetMode(16); break;
    case 12: SndgMusicSetMode(17); break;
    case 15:
        if (p->mUnknown10.mValue && !ReplayIsShowing(gpReplay) && !SndgSfxIsPlaying(62)) SndgSfxPlay(62, 0);
        break;
    case 17: if (!SndgSfxIsPlaying(60)) SndgSfxPlay(60, 0); break;
    case 20: SndgSfxPlay(61, 0); break;
    case 18: SndgSfxPlay(58, &p->mPos); break;
    case 125:
        if (fn_801486A0()) {
            lbl_803EA6E5 = (lbl_803EA6E5 + 1) % 4;
            switch (lbl_803EA6E5) {
            case 0: SndgEventCycleCrowdBanks(); break;
            case 1: SndgEventCycleBanks145(); SndgEventCycleBanks77(); break;
            case 2: SndgEventCycleCrowdBanks(); SndgEventLoadLevelBank(); break;
            case 3: SndgEventCycleBanks145(); break;
            }
        }
        break;
    case 115: if (fn_801486A0()) SndgEventLoadFormationBank(); break;
    case 112: if (fn_801486A0()) SndgEventLoadTeamBanks(); break;
    case 113:
        SndgSfxPlay(130, 0);
        SndgAmbPostCue(2);
        SndgMusicPause();
        SndgCrowdTriggerEvent(2, 0);
        break;
    case 114:
        SndgAmbPostCue(3);
        if (!p->mUnknown10.mValue) SndgMusicResume();
        SndgCrowdTriggerEvent(3, 0);
        break;
    case 95: if (fn_801486A0()) SndgSfxPlay(63, 0); break;
    case 89: SndgCrowdTriggerEvent(4, (unsigned char)p->mUnknown10.mValue); break;
    case 94: SndgCrowdTriggerEvent(11, (unsigned char)p->mUnknown10.mValue); break;
    case 92: SndgCrowdTriggerEvent(9, (unsigned char)p->mUnknown10.mValue); SndgSfxPlay(134, 0); break;
    case 90: SndgCrowdTriggerEvent(13, (unsigned char)p->mUnknown10.mValue); break;
    case 24: SndgSfxPlay(136, 0); break;
    case 25: SndgSfxPlay(137, 0); break;
    case 26: SndgSfxPlay(138, 0); break;
    case 35: {
        Object_80039F5C *a = (Object_80039F5C *)p->mUnknown10.mpObject;
        Object_80039F5C *b = (Object_80039F5C *)p->mUnknown14;
        int id;
        if (a->mUnknown560.mUnknown28 > gPlyrMoveFwdSpeed * 3144.409912109375f ||
            b->mUnknown560.mUnknown28 > gPlyrMoveFwdSpeed * 3144.409912109375f || fn_800A9680()) {
            lbl_803EA6D0 = (lbl_803EA6D0 + 1) % 3;
            id = lbl_803EA6D0 + 15;
        } else {
            lbl_803EA6CF = (lbl_803EA6CF + 1) % 3;
            id = lbl_803EA6CF + 12;
        }
        unsigned char volume;
        pos = &a->mMotion.mPos;
        if (fn_800A9680()) volume = SndgSfxGetVolume(id);
        else {
            volume = (unsigned char)((a->mUnknown560.mUnknown28 + a->mUnknown560.mUnknown28) * SndgSfxGetVolume(id) / (gPlyrMoveFwdSpeed * 100621.1171875f) > SndgSfxGetVolume(id)
                ? SndgSfxGetVolume(id)
                : (a->mUnknown560.mUnknown28 + a->mUnknown560.mUnknown28) * SndgSfxGetVolume(id) / (gPlyrMoveFwdSpeed * 100621.1171875f));
        }
        SndgSfxPlayVolume(id, pos, volume);
        break;
    }
    case 27:
        SndgSfxPlay(p->mUnknown10.mValue == 1, &p->mPos);
        SndgSfxPlay(5, &p->mPos);
        break;
    case 140:
        SndgSituationReset();
        lbl_803EA6E8 = -1;
        lbl_803EA6EC = lbl_803EA6F8 = 0;
        break;
    case 144: SndgSfxPlay(1, &p->mPos); break;
    case 157: {
        Object_80039F5C *player = fn_8009BCE8(&p->mUnknown0);
        if (fn_801486A0() != 1) {
            if (!lbl_803EA6F9) SndgMusicSetMode(9);
            else lbl_803EA6F9 = 0;
            SndgCrowdTriggerEvent(5, player->mIdBytes[2]);
        } else if (lbl_803EA6CE) {
            SndgEventSetCrowdCycle(0);
            lbl_803EA6E0 = (lbl_803EA6E0 + 1) % 4;
            SndgCrowdTriggerEvent(_SndgEvent_aCrowdEvents[lbl_803EA6E0], player->mIdBytes[2]);
        }
        break;
    }
    case 104:
        SndgSfxPlay(64, &p->mPos);
        if (fn_801486A0()) {
            Object_80039F5C *player = fn_8009BCE8(&p->mUnknown0);
            if (!lbl_803EA6F9) SndgMusicSetMode(7);
            SndgCrowdTriggerEvent(6, player->mIdBytes[2]);
            lbl_803EA6F8 = 1;
        }
        break;
    case 105:
        if (fn_801486A0()) {
            Object_80039F5C *player = fn_8009BCE8(&p->mUnknown0);
            // FAKEMATCH: the hold flag is cleared in both arms instead of once after the if; same stores
            if (!lbl_803EA6F9 || SndgMusicGetMode() == 7) {
                SndgMusicSetMode(8);
                lbl_803EA6F9 = 0;
            } else lbl_803EA6F9 = 0;
            SndgCrowdTriggerEvent(7, player->mIdBytes[2]);
            lbl_803EA6F8 = 0;
        }
        break;
    case 175:
        lbl_803EA6D4 = (lbl_803EA6D4 + 1) % 2;
        SndgSfxPlay(lbl_803EA6D4 + 10, &p->mPos);
        break;
    case 43: SndgEventPlayVariant24(&p->mPos); break;
    case 37: {
        unsigned int amount = p->mUnknown10.mValue;
        int state = p->mUnknown14;
        int previous = p->mUnknown18;
        SndgFadeOutChannelGroup();
        Object_80039F5C *player = fn_8009BCE8(&p->mUnknown0);
        int id;
        if (((unsigned int)state <= 1 || state == 3 || state == 5 || state == 7) &&
            ((unsigned int)previous <= 1 || previous == 3 || previous == 5 || previous == 7)) {
            if (!((float)amount <= gPlyrMoveFwdSpeed * 12577.6396484375f)) {
                lbl_803EA6D2 = (lbl_803EA6D2 + 1) % 2;
                id = lbl_803EA6D2 + 6;
            } else if ((float)amount > gPlyrMoveFwdSpeed * 3144.409912109375f) {
                lbl_803EA6D3 = (lbl_803EA6D3 + 1) % 2;
                id = lbl_803EA6D3 + 8;
            } else {
                lbl_803EA6D4 = (lbl_803EA6D4 + 1) % 2;
                id = lbl_803EA6D4 + 10;
            }
        } else {
            if (!((float)amount <= gPlyrMoveFwdSpeed * 12577.6396484375f)) {
                lbl_803EA6D3 = (lbl_803EA6D3 + 1) % 2;
                id = lbl_803EA6D3 + 8;
            } else {
                lbl_803EA6D4 = (lbl_803EA6D4 + 1) % 2;
                id = lbl_803EA6D4 + 10;
            }
        }
        SndgSfxPlay(id, &p->mPos);
        if ((unsigned int)(id - 6) <= 1) {
            SndgSpchSetPlayFlags(4);
            if (!SndgSfxIsPlaying(60)) SndgSfxPlay(60, &p->mPos);
            SndgEventQueueDelayed(&p->mPos);
        }
        if ((unsigned int)(id - 10) > 1) {
            int eligible = 0;
            if (player && (player->mFlags & 0x10000000)) {
                if (!(player->mMotion.mPos.mY >= ScrmGetBallSpot().mY)) {
                    if (PlayAlignHasSlots(PlayBookGetPlay(ScrmGetSnapOffense()))) eligible = BallGetCurrentHolder() == player;
                }
            }
            if (eligible) SndgCrowdTriggerEvent(8, player->mIdBytes[2]);
        }
        break;
    }
    case 124: ScrmGetPlayResult(); break;
    case 139:
        SndgEventSetSfx5Volume(50);
        SndgAmbObjStop(4, (unsigned char)p->mUnknown18);
        if (lbl_803EA6F8) {
            SndgMusicSetMode(8);
            lbl_803EA6F8 = 0;
        }
        break;
    case 14: case 21: case 38: case 71: case 91: case 93: case 99: case 111: case 121: case 122: break;
    // FAKEMATCH: the empty case labels 0, 1, 16 and 19 leave no compare in the target; they only
    // balance the compare tree like the target's (root 75, then 37 and 102) and change no result
    case 0: case 1: case 16: case 19: break;
    }
}

void SndgEventProcessInPlay(AudmonEvent_t *p)
{
    if (!ScrmGetDown()) return;
    switch (p->mType) {
    case 117: lbl_803EA6E4 = 1; break;
    case 118: SyncRandGetRange(1, 2); break;
    case 116: {
        unsigned char side = ((unsigned char *)&p->mUnknown10)[3];
        if (GameModeTypeGet() == 11 && fn_801486A0() == 15) break;
        if (side != ScrmGetOffenseTeam()) break;
        if (SndgSfxIsPlaying(66) || SndgSfxIsPlaying(67)) break;
        lbl_803EA6DB = (lbl_803EA6DB + 1) % 2;
        if (lbl_803EA6DB == 0) SndgSfxPlay(66, 0);
        else SndgSfxPlay(67, 0);
        break;
    }
    case 140:
        if (GameModeTypeGet() == 11 && fn_801486A0() == 15) break;
        SndgSfxStop(66);
        SndgSfxStop(67);
        SndgSfxPlay(65, &p->mPos);
        break;
    }
}

void SndgEventCycleCrowdBanks(void)
{
    if (!lbl_803EA6FA) return;
    if (lbl_803EA6FB) {
        unsigned char id;
        int busy;
        do {
            lbl_803EA6C4 = (lbl_803EA6C4 + 1) % 30;
            id = lbl_803EA6C4;
            busy = SndgIsBankIndexLoaded(4, id);
        } while (busy);
        SndgRequestBank(3, id, 0);
        lbl_803EA6FB = busy;
    } else {
        unsigned char id;
        do {
            lbl_803EA6C5 = (lbl_803EA6C5 + 1) % 30;
            id = lbl_803EA6C5;
        } while (SndgIsBankIndexLoaded(3, id));
        SndgRequestBank(4, id, 0);
        lbl_803EA6FB = 1;
    }
    lbl_803EA6C6 = (lbl_803EA6C6 + 1) % 10;
    SndgRequestBank(5, lbl_803EA6C6 + 30, 0);
}

void SndgEventCycleBanks145(void)
{
    if (!lbl_803EA6FA) return;
    if ((lbl_803EA6D6 + 1) % 6 <= 2) {
        int id;
        do {
            lbl_803EA6C9 = (lbl_803EA6C9 + 1) % 10;
            id = lbl_803EA6C9 + 145;
        } while (SndgIsBankIndexLoaded(14, id));
        SndgRequestBank(13, id, 0);
    } else {
        int id;
        do {
            lbl_803EA6CA = (lbl_803EA6CA + 1) % 10;
            id = lbl_803EA6CA + 145;
        } while (SndgIsBankIndexLoaded(13, id));
        SndgRequestBank(14, id, 0);
    }
}

void SndgEventLoadFormationBank(void)
{
    if (!lbl_803EA6FA) return;
    PlayBookFormation_t *p = PlayBookGetFormation(ScrmGetDefenseTeam());
    unsigned int count = 0;
    for (int i = 0; i < 7; ++i) {
        float x = p->mUnknown8.mUnknown84[0][i].mUnknown10.mX;
        float y = p->mUnknown8.mUnknown84[0][i].mUnknown10.mY;
        if (!(x <= -6.0f) && !(x >= 6.0f) && !(y >= 3.0f)) ++count;
    }
    int id;
    if (count > 2) id = SyncRandBitPoolDraw(_SndgEvent_iFormationPoolLarge) + 40;
    else if (count > 1) id = SyncRandBitPoolDraw(_SndgEvent_iFormationPoolMedium) + 56;
    else id = SyncRandBitPoolDraw(_SndgEvent_iFormationPoolSmall) + 72;
    SndgRequestBank(6, id, 0);
}

void SndgEventCycleBanks77(void)
{
    if (lbl_803EA6FA) {
        lbl_803EA6C7 = (lbl_803EA6C7 + 1) % 5;
        SndgRequestBank(7, lbl_803EA6C7 + 77, 0);
    }
}

void SndgEventLoadLevelBank(void)
{
    int base = 118;
    if (lbl_803EA6FA) {
        switch (fn_800A3444()) {
        case 3: base = 133; break;
        case 9: base = 121; break;
        case 4: base = 130; break;
        case 6: base = 139; break;
        case 7: base = 139; break;
        case 8: base = 139; break;
        case 10: base = 127; break;
        case 0: case 5: case 11: base = 136; break;
        case 2: break;
        // FAKEMATCH: case 1 repeats the initial base 118 and leaves no compare in the target; it only shapes the dispatch tree
        case 1: base = 118; break;
        }
        lbl_803EA6C8 = (lbl_803EA6C8 + 1) % 3;
        SndgRequestBank(8, base + lbl_803EA6C8, 0);
    }
}

void SndgEventSetReplayKind(int value)
{
}

void SndgEventReloadCrowdBanks(void)
{
    if (!SndgIsInit()) return;
    if (lbl_803EA6FA) {
        switch (lbl_803EA6F4) {
        case 0: {
            SndgNullUpdate();
            unsigned char id;
            lbl_803EA6C4 = SyncRandBitPoolDraw(_SndgEvent_iCrowdBankPool);
            id = lbl_803EA6C4;
            while (SndgIsBankIndexLoaded(3, id)) {
                lbl_803EA6C4 = SyncRandBitPoolDraw(_SndgEvent_iCrowdBankPool);
                id = lbl_803EA6C4;
            }
            if (fn_801486A0()) {
                while (!SndgIsBankReady(3)) {
                    if (FileHostCheckActive()) FileDebugProcess();
                    SndService();
                }
            }
            SndgRequestBank(3, id, 0);
            lbl_803EA6C5 = SyncRandBitPoolDraw(_SndgEvent_iCrowdBankPool);
            id = lbl_803EA6C5;
            while (SndgIsBankIndexLoaded(4, id)) {
                lbl_803EA6C5 = SyncRandBitPoolDraw(_SndgEvent_iCrowdBankPool);
                id = lbl_803EA6C5;
            }
            if (fn_801486A0()) {
                while (!SndgIsBankReady(4)) {
                    if (FileHostCheckActive()) FileDebugProcess();
                    SndService();
                }
            }
            SndgRequestBank(4, id, 0);
            break;
        }
        case 1: case 2: SndgNullUpdate(); break;
        }
    }
    lbl_803EA6F4 = 3;
}

void SndgEventOnReplayCase1(void)
{
}

void SndgEventOnReplayCase2(void)
{
}

void SndgEventLoadTeamBanks(void)
{
    int side = ScrmGetOffenseTeam();
    unsigned char value = 0;
    unsigned short index = 0;
    unsigned int count = ScrmGetTeamPlayerCount(side);
    for (; index < count; ++index) {
        Object_80039F5C *p = PlyrGet(side, index);
        if (!p->mUnknown2914) { value = p->mUnknown2912; break; }
    }
    lbl_803EA6DC = (lbl_803EA6DC + 1) % 3;
    int id, other;
    if (!ScrmGetOffenseTeam()) {
        if (value <= 2) { id = lbl_803EA6DC + 85; other = lbl_803EA6DC + 100; }
        else { id = lbl_803EA6DC + 82; other = lbl_803EA6DC + 94; }
    } else {
        if (value <= 2) { id = lbl_803EA6DC + 91; other = lbl_803EA6DC + 112; }
        else { id = lbl_803EA6DC + 88; other = lbl_803EA6DC + 106; }
    }
    SndgRequestBank(2, id, 0);
    SndgRequestBank(16, other, 0);
}

void SndgEventPostBallContact(Object_80039F5C *p, Ball_t *ball)
{
    Vector_80039F5C pos, velocity;
    FieldPoint_t delta;
    BallGetPosition(ball, &pos);
    int nearby = 0;
    BallGetVelocity(ball, &velocity);
    if (p->mIdBytes[3] == 1) {
        Vec2Sub(&delta, &pos, &p->mMotion);
        nearby = Vec2Magnitude(&delta) < 0.3f;
    }
    AudmonEventPostArgs(28, &pos, (unsigned int)(Vec3Magnitude(&velocity) * 65536.0f), nearby, ball->mState.mIndex);
}

void SndgEventPostBallValue(int *value, Ball_t *ball)
{
    Vector_80039F5C pos;
    BallGetPosition(ball, &pos);
    AudmonEventPostId(29, &pos, *value, 0, 0, ball->mState.mIndex);
}

void SndgEventPostRecord(void *record)
{
    SndgEventRecord_t *p = (SndgEventRecord_t *)record;
    Vector_80039F5C pos;
    pos.mX = p->mUnknownC;
    pos.mY = p->mUnknown10;
    pos.mZ = 0.0f;
    if (lbl_803EA6CD) AudmonEventPostId((unsigned short)(p->mUnknown14 + 137), &pos, p->mUnknown0, p->mUnknown4, p->mUnknown8, 0);
}

void SndgEventInitRandom(void)
{
    _SndgEvent_iCrowdBankPool = SyncRandBitPoolNew(1, 30);
    _SndgEvent_iRandomPool1 = SyncRandBitPoolNew(1, 10);
    _SndgEvent_iFormationPoolLarge = SyncRandBitPoolNew(1, 16);
    _SndgEvent_iFormationPoolMedium = SyncRandBitPoolNew(1, 16);
    _SndgEvent_iFormationPoolSmall = SyncRandBitPoolNew(1, 5);
    _SndgEvent_iRandomPool5 = SyncRandBitPoolNew(1, 5);
    _SndgEvent_iRandomPool6 = SyncRandBitPoolNew(1, 3);
    _SndgEvent_iRandomPool7 = SyncRandBitPoolNew(1, 10);
    _SndgEvent_iRandomPool8 = SyncRandBitPoolNew(1, 13);
    lbl_803EA6C5 = 1;
    lbl_803EA6CF = 0;
    lbl_803EA6D0 = 0;
    lbl_803EA6D1 = 0;
    lbl_803EA6D2 = 0;
    lbl_803EA6D3 = 0;
    lbl_803EA6D4 = 0;
    lbl_803EA6D5 = 0;
    lbl_803EA6E5 = 0;
    lbl_803EA6C4 = 0;
    lbl_803EA6DB = 0;
    lbl_803EA6DC = 0;
}

void SndgEventFreeRandom(void)
{
    SyncRandBitPoolDelete(_SndgEvent_iCrowdBankPool);
    SyncRandBitPoolDelete(_SndgEvent_iRandomPool1);
    SyncRandBitPoolDelete(_SndgEvent_iFormationPoolLarge);
    SyncRandBitPoolDelete(_SndgEvent_iFormationPoolMedium);
    SyncRandBitPoolDelete(_SndgEvent_iFormationPoolSmall);
    SyncRandBitPoolDelete(_SndgEvent_iRandomPool5);
    SyncRandBitPoolDelete(_SndgEvent_iRandomPool6);
    SyncRandBitPoolDelete(_SndgEvent_iRandomPool7);
    SyncRandBitPoolDelete(_SndgEvent_iRandomPool8);
}

void SndgEventUpdatePatch(void)
{
    if (lbl_803EA6C0 != 0x7FFFFFFF && SndPatchOver(lbl_803EA6C0)) lbl_803EA6C0 = 0x7FFFFFFF;
}

void SndgEventNull(void)
{
}

void SndgEventPlayReplaySfx(int id)
{
    SndgSfxPlayVolume(lbl_803EA6F0 + id, 0, 127);
    if (++lbl_803EA6F0 > 2) lbl_803EA6F0 = 2;
}

int SndgEventPlayVariant18(Vector_80039F5C *pos)
{
    unsigned int step = SyncRandGetRange(1, 2) + 1;
    lbl_803EA6D6 = (lbl_803EA6D6 + step) % 6;
    return SndgSfxPlay(lbl_803EA6D6 + 18, pos);
}

int SndgEventPlayVariant24(Vector_80039F5C *pos)
{
    unsigned int step = SyncRandGetRange(1, 2) + 1;
    lbl_803EA6D7 = (lbl_803EA6D7 + step) % 4;
    return SndgSfxPlay(lbl_803EA6D7 + 24, pos);
}

void SndgEventUpdateDelayed(void)
{
    if (lbl_803EA6E8 > 0 && SysGetSystemTime() >= (unsigned int)lbl_803EA6E8) {
        lbl_803EA6D8 = (lbl_803EA6D8 + 1) % 6;
        lbl_803EA6E8 = -1;
        SndgSfxPlay(lbl_803EA6D8 + 28, &_SndgEvent_DelayedPos);
    }
}

void SndgEventQueueDelayed(Vector_80039F5C *pos)
{
    if (lbl_803EA6E8 == -1) {
        lbl_803EA6E8 = SysGetSystemTime() + 6;
        _SndgEvent_DelayedPos.mX = pos->mX;
        _SndgEvent_DelayedPos.mY = pos->mY;
        _SndgEvent_DelayedPos.mZ = pos->mZ;
    }
}

int SndgEventPlaySfx34(Vector_80039F5C *p)
{
    lbl_803EA6D9 = 0;
    return SndgSfxPlay(34, p);
}

int SndgEventPlaySfx35(Vector_80039F5C *p)
{
    lbl_803EA6DA = 0;
    return SndgSfxPlay(35, p);
}

void SndgEventSetSfx34Volume(void)
{
    SndgSfxSetVolume(lbl_803EA6D9 + 34, 100, 0);
}

int SndgEventPlayGroup(int id, Vector_80039F5C *pos)
{
    if (++lbl_802D63D0[id] >= _SndgEvent_aSfxGroups[id][1]) lbl_802D63D0[id] = 0;
    return SndgSfxPlay(_SndgEvent_aSfxGroups[id][0] + lbl_802D63D0[id], pos);
}

int SndgEventPlayGroupVolume(int id, Vector_80039F5C *pos, unsigned int volume)
{
    if (++lbl_802D63D0[id] >= _SndgEvent_aSfxGroups[id][1]) lbl_802D63D0[id] = 0;
    int sound = _SndgEvent_aSfxGroups[id][0] + lbl_802D63D0[id];
    return SndgSfxPlayVolume(sound, pos, (unsigned char)((volume * SndgSfxGetVolume(sound)) / 100));
}

int SndgEventGetFootstepSfx(int unused, int value)
{
    int result = 36;
    int choice = SyncRandGetRange(1, 2);
    switch (value) {
    case 2: case 4: result = choice ? 36 : 38; break;
    case 1: case 10: result = 40; break;
    case 9: break;
    // FAKEMATCH: the empty surface labels 0 and 15 sit on the default arm; they only shape the
    // compare tree (the bounds checks after 1 and 10) and change no result
    case 0: case 15:
    default: result = 38; break;
    }
    return result;
}

int SndgEventGetSurfaceHitSfx(int a, int value)
{
    switch (value) {
    case 10:
        return 108;
    case 9:
        return 111;
    // FAKEMATCH: the empty surface labels 0, 1 and 15 sit on the default arm; they only shape the
    // compare tree (root 3, then 10, then 9) and change no result
    case 0:
    case 1:
    case 15:
    case 3:
    default:
        return 105;
    }
}

int SndgEventGetSurfaceSfx(int value)
{
    int result = 42;
    switch (value) {
    // FAKEMATCH: the empty case labels 5 and 7 (surface ids the target sends to the default 44)
    // leave no compare in the target; they only move the compare tree root to 4 and change no result
    case 0:
    case 1:
    case 5:
    case 7:
    case 8:
        result = 44;
        break;
    case 2:
    case 3:
        break;
    case 4:
    case 6:
        result = 43;
        break;
    default:
        result = 44;
        break;
    }
    return result;
}

void SndgEventSetCrowdCycle(int value)
{
    lbl_803EA6CE = value;
}

void SndgEventSetMusicHold(int value)
{
    lbl_803EA6F9 = value;
}

}
