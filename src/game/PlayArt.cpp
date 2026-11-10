/* Play art: builds the route diagrams of the plays shown in the play-select slots from the
   playbook database (player spots, routes and receiver boxes) and draws them through the
   front-end draw callback; the PlayArtMem module loads and frees their textures. */

#include "game/PlayArtState.h"
#include "game/fn_801C1F94.h"
#include "game/PlayBookTeam.h"
#include "game/fn_800B65A0.h"

#include "game/PlayArtPlayer.h"

static PlayArtPlayer_t _PlayArt_aPlayers[9][11];
static unsigned char _PlayArt_aFlip[3][9];
static PlayArtState_t _PlayArt_aStates[3][9];
extern "C" float lbl_802E992C[][2];

extern "C" {
int fn_801651E0(void *, int, signed char, int, PlayArtPlayer_t *);
int fn_80165464(void *, int, int, PlayArtPlayer_t *);
int fn_80165890(void *, PlayArtPlayer_t *, int, unsigned char);
void fn_80165110(PlayArtPlay_t *, int);
void fn_80166BE8(PlayArtPlay_t *, PlayArtState_t *, PlayArtPlayer_t *, int, int, unsigned char);
int fn_8016631C(PlayArtPlayer_t *, int, void *, void *, void *, void *, int);
int fn_80165770(PlayArtPlay_t *, PlayArtState_t *, PlayArtPlayer_t *);
PlayBookTeam_t *PlayBookGetTeam(int);
void fn_8018A8C8(int);
int GameModeTypeIsSpecial(void);
int fn_801486A0(void);
int fn_800BA6F8(void);
void PlyrIconQueueAdd(float, float, void *, unsigned char);
void fn_8018A908(void (*)(int, float, float, float, float));
void PlyrIconShutdown(void);
int ResSetMemFlags(int);
void fn_801A1240(int);
void fn_801A12E8(void);

void PlayArtReadPositions(void *p, unsigned char *input, void *, int a, int b, signed char c, int group, int index)
{
    fn_801651E0(p, a, c, b, _PlayArt_aPlayers[index]);
    for (int i = 0; i < 11; ++i) {
        _PlayArt_aStates[group][index].mUnknown2078[i] = input[i * 0x28 + 0x8F];
    }
}

void PlayArtReadRoutes(void *p, void *, int a, int b, int, int index)
{
    fn_80165464(p, a, b, _PlayArt_aPlayers[index]);
}

void PlayArtBuild(void *p, PlayArtPlay_t *object, int, int, int, int group, int index, int first, unsigned char count, void *)
{
    PlayArtState_t *state = &_PlayArt_aStates[group][index];
    int remaining = 0x128;
    int used;
    if (first == 0)
        used = 0;
    else
        used = state->mUnknown940[first];
    fn_80165890(p, _PlayArt_aPlayers[index], first, count);
    int flag = 1;
    if (object->mUnknown14 <= 36)
        flag = object->mUnknown14 <= 30;
    state->mUnknown2083 = flag;
    if (_PlayArt_aFlip[group][index]) {
        fn_80165110(object, 1);
    }
    int i;
    for (i = first; i < count; ++i) {
        PlayArtPlayer_t *record = &_PlayArt_aPlayers[index][i];
        state->mUnknown940[i] = used;
        float x = record->mUnknown8;
        float y = record->mUnknownC;
        float dx = lbl_802E992C[record->mUnknown10][0];
        float dy = lbl_802E992C[record->mUnknown10][1];
        state->mUnknown2084[i][0] = x - dx;
        state->mUnknown2084[i][1] = y - dy;
        state->mUnknown2084[i][2] = x + dx;
        state->mUnknown2084[i][3] = y + dy;
        unsigned char value = PlayBookGetTeam((unsigned char)group)->mUnknown20.mUnknown10;
        fn_80166BE8(object, state, record, group, i, value);
        state->mUnknown2134[i] = record->mUnknown10;
        fn_801C1F94(state->mUnknown19F0[i], 0, 0x30);
        int size = fn_8016631C(record, remaining, state->mUnknown0 + used * 8,
            state->mUnknown970[i], state->mUnknown19F0[i], state->mUnknown1E10[i], flag);
        used += size;
        remaining -= size;
    }
    state->mUnknown940[i] = used;
    fn_80165770(object, state, _PlayArt_aPlayers[index]);
}

void PlayArtDraw(int code, float x, float y, float, float)
{
    fn_8018A8C8(5);
    int flag = 1;
    if ((!GameModeTypeIsSpecial() && fn_801486A0() != 3 && fn_800B65A0(0) != 0xFF && fn_800B65A0(1) != 0xFF) || fn_800BA6F8()) {
        flag = 0;
    }
    switch ((unsigned int)code) {
    case 0: PlyrIconQueueAdd(x, y, &_PlayArt_aStates[1][0], _PlayArt_aFlip[1][0]); break;
    case 1: PlyrIconQueueAdd(x, y, &_PlayArt_aStates[1][1], _PlayArt_aFlip[1][1]); break;
    case 4:
        if (flag) { PlyrIconQueueAdd(x, y, &_PlayArt_aStates[1][4], _PlayArt_aFlip[1][4]); break; }
    case 2: PlyrIconQueueAdd(x, y, &_PlayArt_aStates[1][2], _PlayArt_aFlip[1][2]); break;
    case 5:
        if (flag) { PlyrIconQueueAdd(x, y, &_PlayArt_aStates[1][5], _PlayArt_aFlip[1][5]); break; }
    case 3: PlyrIconQueueAdd(x, y, &_PlayArt_aStates[1][3], _PlayArt_aFlip[1][3]); break;
    case 6: PlyrIconQueueAdd(x, y, &_PlayArt_aStates[1][6], _PlayArt_aFlip[1][6]); break;
    case 7: PlyrIconQueueAdd(x, y, &_PlayArt_aStates[1][7], _PlayArt_aFlip[1][7]); break;
    case 10: if (flag) goto case14;
    case 8: PlyrIconQueueAdd(x, y, &_PlayArt_aStates[0][0], _PlayArt_aFlip[0][0]); break;
    case 11: if (flag) goto case15;
    case 9: PlyrIconQueueAdd(x, y, &_PlayArt_aStates[0][1], _PlayArt_aFlip[0][1]); break;
    case 12: PlyrIconQueueAdd(x, y, &_PlayArt_aStates[0][4], _PlayArt_aFlip[0][4]); break;
    case 13: PlyrIconQueueAdd(x, y, &_PlayArt_aStates[0][5], _PlayArt_aFlip[0][5]); break;
    case 14:
        if (flag) { PlyrIconQueueAdd(x, y, &_PlayArt_aStates[0][6], _PlayArt_aFlip[0][6]); break; }
    case14: PlyrIconQueueAdd(x, y, &_PlayArt_aStates[0][2], _PlayArt_aFlip[0][2]); break;
    case 15:
        if (flag) { PlyrIconQueueAdd(x, y, &_PlayArt_aStates[0][7], _PlayArt_aFlip[0][7]); break; }
    case15: PlyrIconQueueAdd(x, y, &_PlayArt_aStates[0][3], _PlayArt_aFlip[0][3]); break;
    default: PlyrIconQueueAdd(x, y, &_PlayArt_aStates[2][code - 16], _PlayArt_aFlip[2][code - 16]); break;
    }
}

void PlayArtStart(void)
{
    fn_801C1F94(_PlayArt_aFlip[0], PlayBookGetTeam(0)->mUnknown20.mUnknown10, 9);
    fn_801C1F94(_PlayArt_aFlip[1], PlayBookGetTeam(1)->mUnknown20.mUnknown10, 9);
    fn_801C1F94(_PlayArt_aFlip[2], 0, 9);
    fn_8018A908(PlayArtDraw);
}
void PlayArtSetFlip(signed char group, int value, int index)
{
    if (index == -1) {
        fn_801C1F94(_PlayArt_aFlip[group], value, 9);
    } else {
        _PlayArt_aFlip[group][index] = value;
    }
}
void PlayArtStop(void)
{
    fn_8018A908(0);
    PlyrIconShutdown();
}
void PlayArtMemInit(int value)
{
    int saved = ResSetMemFlags(4);
    fn_801A1240(value);
    ResSetMemFlags(saved);
}
void PlayArtMemShutdown(void)
{
    fn_801A12E8();
}
void PlayArtResetAll(void)
{
    fn_801C1F94(_PlayArt_aPlayers, 0, sizeof(_PlayArt_aPlayers));
    fn_801C1F94(_PlayArt_aStates, 0, sizeof(_PlayArt_aStates));
}
void PlayArtResetTeam(int group)
{
    fn_801C1F94(_PlayArt_aStates[group], 0, sizeof(_PlayArt_aStates[group]));
}
}
