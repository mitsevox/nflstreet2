/* Play art: builds the route diagrams of the plays shown in the play-select slots from the
   playbook database (player spots, routes and receiver boxes) and draws them through the
   front-end draw callback; the PlayArtMem module loads and frees their textures. */

#include "game/PlayArtState.h"
#include <string.h>
#include "game/PlayBookTeam.h"
#include "game/fn_800B65A0.h"

#include "game/PlayArtPlayer.h"
#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/PlayBookDb.h"
#include "game/PlayBookGetPlay.h"
#include "game/PlaySet.h"
#include "game/fn_800F06F4.h"
#include "game/Message_800F01CC.h"
#include "game/State_803EB098.h"
#include "game/DbQueryTable.h"
#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"

static PlayArtPlayer_t _PlayArt_aPlayers[9][11];
static unsigned char _PlayArt_aFlip[3][9];
static PlayArtState_t _PlayArt_aStates[3][9];
extern "C" float lbl_802E992C[][2];

extern "C" {
int PlayAlignLoadSetPlayers(void *, int, signed char, int, PlayArtPlayer_t *);
int PlayAlignLoadPlayRoutes(void *, int, int, PlayArtPlayer_t *);
int PlayAlignLoadRouteSteps(void *, PlayArtPlayer_t *, int, unsigned char);
void PlayAlignSwapOuterSlots(PlayArtPlay_t *, int);
void fn_80166BE8(PlayArtPlay_t *, PlayArtState_t *, PlayArtPlayer_t *, int, int, unsigned char);
int fn_8016631C(PlayArtPlayer_t *, int, void *, void *, void *, void *, int);
int PlayAlignBuildSlotRects(PlayArtPlay_t *, PlayArtState_t *, PlayArtPlayer_t *);
PlayBookTeam_t *PlayBookGetTeam(int);
void UISGameSetDrawMode(int);
int GameModeTypeIsSpecial(void);
int fn_801486A0(void);
int fn_800BA6F8(void);
void PlyrIconQueueAdd(float, float, void *, unsigned char);
void UISViewObjSetDrawFunc(void (*)(int, float, float, float, float));
void PlyrIconShutdown(void);
int ResSetMemFlags(int);
void PlayArtRenderLoadTextures(int);
void PlayArtRenderUnloadTextures(void);

void PlayArtReadPositions(void *p, unsigned char *input, void *, int a, int b, signed char c, int group, int index)
{
    PlayAlignLoadSetPlayers(p, a, c, b, _PlayArt_aPlayers[index]);
    for (int i = 0; i < 11; ++i) {
        _PlayArt_aStates[group][index].mUnknown2078[i] = input[i * 0x28 + 0x8F];
    }
}

void PlayArtReadRoutes(void *p, void *, int a, int b, int, int index)
{
    PlayAlignLoadPlayRoutes(p, a, b, _PlayArt_aPlayers[index]);
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
    PlayAlignLoadRouteSteps(p, _PlayArt_aPlayers[index], first, count);
    int flag = 1;
    if (object->mUnknown14 <= 36)
        flag = object->mUnknown14 <= 30;
    state->mUnknown2083 = flag;
    if (_PlayArt_aFlip[group][index]) {
        PlayAlignSwapOuterSlots(object, 1);
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
        memset(state->mUnknown19F0[i], 0, 0x30);
        int size = fn_8016631C(record, remaining, state->mUnknown0 + used * 8,
            state->mUnknown970[i], state->mUnknown19F0[i], state->mUnknown1E10[i], flag);
        used += size;
        remaining -= size;
    }
    state->mUnknown940[i] = used;
    PlayAlignBuildSlotRects(object, state, _PlayArt_aPlayers[index]);
}

void PlayArtDraw(int code, float x, float y, float, float)
{
    UISGameSetDrawMode(5);
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
    memset(_PlayArt_aFlip[0], PlayBookGetTeam(0)->mUnknown20.mUnknown10, 9);
    memset(_PlayArt_aFlip[1], PlayBookGetTeam(1)->mUnknown20.mUnknown10, 9);
    memset(_PlayArt_aFlip[2], 0, 9);
    UISViewObjSetDrawFunc(PlayArtDraw);
}
void PlayArtSetFlip(signed char group, int value, int index)
{
    if (index == -1) {
        memset(_PlayArt_aFlip[group], value, 9);
    } else {
        _PlayArt_aFlip[group][index] = value;
    }
}
void PlayArtStop(void)
{
    UISViewObjSetDrawFunc(0);
    PlyrIconShutdown();
}
void PlayArtMemInit(int value)
{
    int saved = ResSetMemFlags(4);
    PlayArtRenderLoadTextures(value);
    ResSetMemFlags(saved);
}
void PlayArtMemShutdown(void)
{
    PlayArtRenderUnloadTextures();
}
void PlayArtResetAll(void)
{
    memset(_PlayArt_aPlayers, 0, sizeof(_PlayArt_aPlayers));
    memset(_PlayArt_aStates, 0, sizeof(_PlayArt_aStates));
}
void PlayArtResetTeam(int group)
{
    memset(_PlayArt_aStates[group], 0, sizeof(_PlayArt_aStates[group]));
}
}

#if defined(DECOMP_COMPARE)
extern "C" PlayArtVertex_t _PlayAlign_aCurveWork[], _PlayAlign_aCurveSamples[];

extern "C" {
void Vec2Normalize(void *, void *);
void PlayAlignBuildCurveStrip(PlayArtVertex_t *, PlayArtVertex_t *, int, int);
void PlayAlignBuildSegmentStrip(PlayArtVertex_t *, PlayArtVertex_t *, int);

extern int lbl_802E9964[];
extern PlayArtVertex_t lbl_802E98FC[];
extern unsigned char lbl_802E98E0[][4], lbl_802E98F0[][3];
extern unsigned char lbl_803EB3BB,lbl_803EB3BF,lbl_803EB3C3,lbl_803EB3C7,lbl_803EB3CB,lbl_803EB3CF;
extern unsigned char lbl_803EB3D3,lbl_803EB3D7,lbl_803EB3DB,lbl_803EB3DF,lbl_803EB3E3,lbl_803EB3E7;
extern unsigned char lbl_803EB3EB,lbl_803EB3EF,lbl_803EB3F3,lbl_803EB3F7,lbl_803EB3FB,lbl_803EB3FF,lbl_803EB403,lbl_803EB407,lbl_803EB40B;
int fn_80177F70(void);
int PauseIsOpen(void);
void Vec2Add(void *, void *, void *);
float Vec2Distance(void *, void *);
int _TDbQrySelect(int, DbQueryTable *, DbFilter *, void *, int *, QueryResult *);
int fn_801C2E18(char *, const char *, ...);
int DbTextToTag(const char *);
int fn_80178308(void);
unsigned int fn_80178D18(int);
int fn_80178D70(int);
PlayBookFormation_t *PlayBookGetFormation(int);
Record_8011F4E0 *fn_8011F4E0(void);
Message_800F01CC *fn_800AEE20(Object_80039F5C *);
void fn_800AEF74(Object_80039F5C *, Message_800F01CC *);
void fn_800F0910(int, Message_800F01CC *);
int fn_800AD9B4(void);
int PlayAlignHasSlots(PlayBookPlay_t *);
void PlayAlignIssuePlayerRoute(PlayBookPlay_t *, Object_80039F5C *, int);

void fn_80166110(PlayArtVertex_t *points, PlayArtVertex_t *out, int width, int length)
{
    PlayArtVertex_t direction;
    direction.mY = points[0].mY - points[1].mY;
    direction.mX = points[0].mX - points[1].mX;
    float magnitude = sqrtf(direction.mX * direction.mX + direction.mY * direction.mY);
    if (magnitude != 0.0f) {direction.mX /= magnitude; direction.mY /= magnitude;}
    PlayArtVertex_t side;
    side.mX = -direction.mY;
    side.mY = -direction.mX;
    side.mX = side.mX * 0.5f * (float)width;
    side.mY = side.mY * 0.5f * (float)width;
    out[0].mX = points[0].mX + side.mX;
    direction.mX = direction.mX * 0.5f * (float)length;
    out[0].mY = points[0].mY - side.mY;
    direction.mY = direction.mY * 0.5f * (float)length;
    out[1].mX = points[0].mX - side.mX;
    out[2].mX = out[0].mX + direction.mX;
    out[2].mY = out[0].mY + direction.mY;
    out[3].mX = out[1].mX + direction.mX;
    out[1].mY = points[0].mY + side.mY;
    out[3].mY = out[1].mY + direction.mY;
}

int PlayArtAddQuad(PlayArtVertex_t *out, int count, int, PlayArtVertex_t *quad)
{
    out[count++] = quad[0];
    out[count++] = quad[1];
    out[count++] = quad[3];
    out[count++] = quad[2];
    return count;
}

int fn_8016631C(PlayArtPlayer_t *record, int capacity, void *vertexBuffer, void *arrowBuffer,
                void *kindBuffer, void *colorBuffer, int extend)
{
    PlayArtVertex_t *vertices = (PlayArtVertex_t *)vertexBuffer;
    PlayArtVertex_t (*arrows)[4] = (PlayArtVertex_t (*)[4])arrowBuffer;
    int *kinds = (int *)kindBuffer, *colors = (int *)colorBuffer;
    PlayArtVertex_t starts[12], ends[13], controls[3], strip[20];
    memset(controls, 0, 24);
    int drawn = 0;
    int count = 0;
    memset(strip, 0, 160);
    for (int i = 0; i <= 11; ++i) {
        PlayArtStep_t *step = &record->mUnknown1C[i];
        int arrowKind = step->mUnknown14;
        kinds[i] = arrowKind;
        colors[i] = step->mUnknown20;
        int width = lbl_802E9964[step->mUnknown1C];
        if (record->mUnknown4Word) {
            int link = step->mUnknown18 == 15 ? i : step->mUnknown18;
            if (!i) {starts[0].mX = record->mUnknown8; starts[0].mY = record->mUnknownC;}
            else if (link == i) starts[i] = ends[i];
            else starts[i] = ends[link+1];
        }
        int stop = 0;
        PlayArtVertex_t zero = {0.0f, 0.0f};
        if (step->mUnknown10 == 1) {
            controls[0] = starts[i];
            Vec2Add(&controls[1], &step->mUnknown0, starts);
            Vec2Add(&controls[2], &step->mUnknown8, starts);
            if (controls[1].mX < 4.0f) controls[1].mX = 4.0f; else if (!(controls[1].mX <= 116.0f)) controls[1].mX = 116.0f;
            if (controls[1].mY < 4.0f) controls[1].mY = 4.0f; else if (!(controls[1].mY <= 96.0f)) controls[1].mY = 96.0f;
            if (controls[2].mX < 4.0f) controls[2].mX = 4.0f; else if (!(controls[2].mX <= 116.0f)) controls[2].mX = 116.0f;
            if (controls[2].mY < 4.0f) controls[2].mY = 4.0f; else if (!(controls[2].mY <= 96.0f)) controls[2].mY = 96.0f;
            ends[i+1] = controls[2];
            int samples = (int)(Vec2Distance(&controls[0], &controls[1]) * 0.175f + 2.0f);
            if (samples > 8) samples = 8;
            PlayAlignBuildCurveStrip(controls, strip, samples, width);
            for (int j = 0; j < samples; ++j) {
                vertices[count] = strip[j*2];
                vertices[count+1] = strip[j*2+1];
                count += 2;
            }
            drawn = 1;
        } else if (step->mUnknown10 == 0) {
            controls[0] = starts[i];
            Vec2Add(&controls[1], &step->mUnknown0, starts);
            if (controls[1].mX < 4.0f) controls[1].mX = 4.0f; else if (!(controls[1].mX <= 116.0f)) controls[1].mX = 116.0f;
            if (controls[1].mY < 4.0f) controls[1].mY = 4.0f; else if (!(controls[1].mY <= 96.0f)) controls[1].mY = 96.0f;
            ends[i+1] = controls[1];
            PlayAlignBuildSegmentStrip(controls, strip, width);
            count = PlayArtAddQuad(vertices, count, capacity, strip);
            if (fabsf(controls[0].mX - controls[1].mX) != zero.mX || fabsf(controls[0].mY - controls[1].mY) != zero.mY) drawn = 1;
        } else if (step->mUnknown10 == 2) {
            for (int j = 0; j < 2; ++j) {
                controls[0] = starts[i];
                if (!j) Vec2Add(&controls[1], &step->mUnknown0, starts);
                else Vec2Add(&controls[1], &step->mUnknown8, starts);
                if (controls[1].mX < 4.0f) controls[1].mX = 4.0f; else if (!(controls[1].mX <= 116.0f)) controls[1].mX = 116.0f;
                if (controls[1].mY < 4.0f) controls[1].mY = 4.0f; else if (!(controls[1].mY <= 96.0f)) controls[1].mY = 96.0f;
                ends[i+1] = controls[1];
                PlayAlignBuildSegmentStrip(controls, strip, width);
                count = PlayArtAddQuad(vertices, count, capacity, strip);
                if (fabsf(controls[0].mX - controls[1].mX) != zero.mX || fabsf(controls[0].mY - controls[1].mY) != zero.mY) drawn = 1;
            }
        } else if (step->mUnknown10 == -1) stop = 1;
        if (arrowKind) {
            if (!drawn && extend) {
                controls[1] = starts[i];
                starts[i].mY -= 8.0f;
                controls[0] = starts[i];
                if (controls[1].mX < 4.0f) controls[1].mX = 4.0f; else if (!(controls[1].mX <= 116.0f)) controls[1].mX = 116.0f;
                if (controls[1].mY < 4.0f) controls[1].mY = 4.0f; else if (!(controls[1].mY <= 96.0f)) controls[1].mY = 96.0f;
                ends[i+1] = controls[1];
                PlayAlignBuildSegmentStrip(controls, strip, width);
                count = PlayArtAddQuad(vertices, count, capacity, strip);
            }
            PlayArtVertex_t axis[2];
            if (step->mUnknown10 == 1) {axis[0] = controls[2]; axis[1] = controls[1];}
            else {axis[0] = ends[i+1]; axis[1] = starts[i];}
            if (fabsf(axis[0].mX - axis[1].mX) == 0.0f && fabsf(axis[0].mY - axis[1].mY) == 0.0f) {
                axis[1].mX += 1.0f;
                axis[1].mY += 1.0f;
            }
            if ((unsigned int)(step->mUnknown14 - 3) < 3) {
                float x = lbl_802E98FC[kinds[i]].mX * 0.5f;
                float y = lbl_802E98FC[kinds[i]].mY * 0.5f;
                arrows[i][0].mX = axis[0].mX - x;
                arrows[i][2].mX = axis[0].mX - x;
                arrows[i][3].mY = axis[0].mY - y;
                arrows[i][1].mY = axis[0].mY + y;
                arrows[i][3].mX = axis[0].mX + x;
                arrows[i][0].mY = axis[0].mY + y;
                arrows[i][1].mX = axis[0].mX + x;
                arrows[i][2].mY = axis[0].mY - y;
            } else {
                fn_80166110(axis, strip, (int)lbl_802E98FC[kinds[i]].mX, (int)lbl_802E98FC[kinds[i]].mY);
                for (int j = 0; j < 4; ++j) arrows[i][j] = strip[j];
            }
        }
        if (stop) break;
    }
    return count;
}

void fn_80166BE8(PlayArtPlay_t *record, PlayArtState_t *state, PlayArtPlayer_t *entry, int team, int index, unsigned char)
{
    unsigned char r = 130, g = 130, b = 130;
    unsigned char secondaryR = 231, secondaryG = 217, secondaryB = 50;
    int found = 0;

    if (!fn_80177F70() && !PauseIsOpen()) {
        r = lbl_803EB3D3; g = lbl_803EB3D7; b = lbl_803EB3DB;
    } else {
        int inherited = 1;
        void *queue = PlayAlignGetRoute(record, (unsigned char)team, (unsigned short)index);
        for (unsigned char i = 0; i <= 3; ++i) {
            if (fn_800F06F4(0, queue, lbl_802E98E0[i][3], 0xFFFF) != 0xFFFF) {
                secondaryR = lbl_802E98F0[i][0];
                secondaryG = lbl_802E98F0[i][1];
                secondaryB = lbl_802E98F0[i][2];
                found = 1;
                break;
            }
        }
        if (!found) secondaryR = secondaryG = secondaryB = 255;
        if (inherited) {
            switch (entry->mUnknown14Word) {
            case 5: case 6: case 7: case 8: case 9:
                r = lbl_803EB3BB; g = lbl_803EB3C3; b = lbl_803EB3BF;
                inherited = 0;
                break;
            case 10: case 11: case 12: case 13: case 14: case 15:
                r = lbl_803EB3DF; g = lbl_803EB3E3; b = lbl_803EB3E7;
                inherited = 0;
                break;
            case 16: case 17: case 18:
                r = lbl_803EB3C7; g = lbl_803EB3CB; b = lbl_803EB3CF;
                inherited = 0;
                break;
            }
        }
        if (inherited) {
            unsigned int kind = entry->mUnknown14Word;
            switch (record->mUnknown14) {
            case 21:
                if (kind >= 19 && kind <= 20) {
                    r = lbl_803EB3D3; g = lbl_803EB3D7; b = lbl_803EB3DB;
                } else {
                    r = lbl_803EB3BB; g = lbl_803EB3C3; b = lbl_803EB3BF;
                }
                break;
            case 11: case 37:
                if (!kind) {
                    r = lbl_803EB3BB; g = lbl_803EB3C3; b = lbl_803EB3BF;
                }
                break;
            case 12: case 13: case 14: case 15: case 16: case 17: case 18:
                if (record->mUnknownC == index) {
                    r = lbl_803EB3D3; g = lbl_803EB3D7; b = lbl_803EB3DB;
                } else {
                    r = lbl_803EB3BB; g = lbl_803EB3C3; b = lbl_803EB3BF;
                }
                break;
            case 1: case 2: case 3: case 4: case 5: case 38:
                if (!kind) {
                    int matched = 0;
                    for (unsigned char i = 0; i <= 2; ++i) {
                        if (record->mUnknown1C[i][0] == index) {
                            switch (i) {
                            case 0: r = lbl_803EB3EB; g = lbl_803EB3EF; b = lbl_803EB3F3; break;
                            case 1: r = lbl_803EB3F7; g = lbl_803EB3FB; b = lbl_803EB3FF; break;
                            case 2: r = lbl_803EB403; g = lbl_803EB407; b = lbl_803EB40B; break;
                            }
                            matched = 1;
                            break;
                        }
                    }
                    if (!matched) {
                        r = lbl_803EB3BB; g = lbl_803EB3C3; b = lbl_803EB3BF;
                    }
                } else {
                    r = lbl_803EB3BB; g = lbl_803EB3C3; b = lbl_803EB3BF;
                    for (unsigned char i = 0; i <= 2; ++i) {
                        if (record->mUnknown1C[i][0] == index) {
                            if (fn_800F06F4(0, queue, 19, 0xFFFF) != 0xFFFF || fn_800F06F4(0, queue, 21, 0xFFFF) != 0xFFFF) {
                                switch (i) {
                                case 0: r = lbl_803EB3EB; g = lbl_803EB3EF; b = lbl_803EB3F3; break;
                                case 1: r = lbl_803EB3F7; g = lbl_803EB3FB; b = lbl_803EB3FF; break;
                                case 2: r = lbl_803EB403; g = lbl_803EB407; b = lbl_803EB40B; break;
                                }
                            }
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
    state->mUnknown2020[index].r = r;
    state->mUnknown2020[index].g = g;
    state->mUnknown2020[index].b = b;
    state->mUnknown2020[index].a = 255;
    state->mUnknown204C[index].r = secondaryR;
    state->mUnknown204C[index].g = secondaryG;
    state->mUnknown204C[index].b = secondaryB;
    state->mUnknown204C[index].a = 255;
}

}
#endif
