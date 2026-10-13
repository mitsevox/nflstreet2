#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/fn_800670B4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80163E94.h"
#include "game/fn_800F06F4.h"
#include "game/Message_800F01CC.h"
#include "game/State_803EB098.h"
#include "game/State_80167094.h"
#include "game/Record_80167094.h"
#include "game/fn_801C1F94.h"
#include "game/Table_8007E020.h"
#include "game/fn_801FCE10.h"

extern "C" Point_80167094 lbl_8031D2B8[], lbl_8031D308[];

extern "C" {
void fn_802271A4(void *, void *);
float fn_80260B1C(float);

extern int lbl_802E9964[];
extern Point_80167094 lbl_802E98FC[];
extern unsigned char lbl_802E98E0[][4], lbl_802E98F0[][3];
extern unsigned char lbl_803EB3BB,lbl_803EB3BF,lbl_803EB3C3,lbl_803EB3C7,lbl_803EB3CB,lbl_803EB3CF;
extern unsigned char lbl_803EB3D3,lbl_803EB3D7,lbl_803EB3DB,lbl_803EB3DF,lbl_803EB3E3,lbl_803EB3E7;
extern unsigned char lbl_803EB3EB,lbl_803EB3EF,lbl_803EB3F3,lbl_803EB3F7,lbl_803EB3FB,lbl_803EB3FF,lbl_803EB403,lbl_803EB407,lbl_803EB40B;
int fn_80177F70(void);
int fn_8006560C(void);
void fn_80227638(void *, void *, void *);
float fn_8022781C(void *, void *);
int fn_801FA0BC(int, Table_8007E020 *, Object_80023BBC *, void *, int *, QueryResult *);
int fn_801C2E18(char *, const char *, ...);
int fn_8018AFF0(const char *);
int fn_80178308(void);
unsigned int fn_80178D18(int);
int fn_80178D70(int);
Object_800670B4 *fn_80168708(int);
Record_8011F4E0 *fn_8011F4E0(void);
Message_800F01CC *fn_800AEE20(Object_80039F5C *);
void fn_800AEF74(Object_80039F5C *, Message_800F01CC *);
void fn_800F0910(int, Message_800F01CC *);
int fn_800AD9B4(void);
int fn_801650DC(Record_80067338 *);
void fn_80164CE4(Record_80067338 *, Object_80039F5C *, int);

unsigned char fn_80164B78(void)
{
    Object_80039F5C *selected = fn_8016444C(fn_80168708(fn_80178308()));
    if (selected == fn_80039F5C(fn_80178308(), 0)) {
        unsigned int n = fn_80178D18(fn_80178308());
        for (unsigned char i = 0; i < n; ++i) {
            Object_80039F5C *p = fn_80039F5C(fn_80178308(), i);
            Record_80067338 *record = fn_8016871C(fn_80178308());
            void *queue = fn_80164EC8(record, fn_80178308(), p->mIdBytes[1]);
            if (fn_800F06F4(0, queue, 18, 0xFFFF) != 0xFFFF) {selected = p; break;}
        }
    }
    return selected->mIdBytes[1];
}

void fn_80164C4C(Object_800670B4 *object, Record_80067338 *record, int team, int)
{
    int remap = object->mUnknown8.mUnknownF == 1 && (object->mUnknown8.mUnknown14 & 1) && (record->mUnknown18 & 1);
    int count = fn_80178D70(team);
    for (int i = 0; i < count; ++i)
        fn_80164CE4(record, fn_80039F5C(team, (unsigned short)i), remap);
}

void fn_80164CE4(Record_80067338 *record, Object_80039F5C *p, int remap)
{
    if (fn_8011F4E0()->mUnknown6 && (unsigned int)(p->mUnknown2914 - 17) <= 1) remap = !remap;
    unsigned char index = p->mIdBytes[1];
    if (remap) index = fn_80163E94(fn_80168708(p->mIdBytes[2]), p->mIdBytes[1], 0)->mUnknownB;
    Message_800F01CC *other = fn_800AEE20(p);
    if (other) {fn_800AEF74(p, other); return;}
    Message_800F01CC *queue = (Message_800F01CC *)fn_80164EC8(record, p->mIdBytes[2], index);
    short count = 0;
    for (;;) {
        int end = queue->mId & 0x80;
        Message_800F01CC message = *queue;
        if (end) message.mId &= 0x7F;
        if (remap) fn_800F0910(0, &message);
        if (!message.mId) break;
        if (!count) fn_800F053C(0, p->mpState, &message, p);
        else fn_800F03D8(0, p->mpState, &message, p);
        ++count;
        ++queue;
        if (end) break;
    }
}

int fn_80164E30(Record_80067338 *record, Object_800670B4 *object, Object_80039F5C *p, int kind)
{
    unsigned char index = p->mIdBytes[1];
    if (object->mUnknown8.mUnknownF) index = fn_80163E94(object, p->mIdBytes[1], 0)->mUnknownB;
    Message_800F01CC *queue = (Message_800F01CC *)fn_80164EC8(record, p->mIdBytes[2], index);
    for (;;) {
        int end = queue->mId & 0x80;
        int id = queue->mId;
        if (end) id &= 0x7F;
        if (id == kind) return 1;
        ++queue;
        if (end) return 0;
    }
}

void *fn_80164EC8(void *record, int, unsigned short index)
{
    return (unsigned char *)record + 56 + index * 40;
}

unsigned char fn_80164ED8(Object_800670B4 *object, Record_80067338 *record, int slot, unsigned char *out, int remap)
{
    unsigned char index = 255;
    unsigned char (*slots)[4] = 0;
    int override = 0;
    if (fn_801650DC(record)) {
        int mode = fn_800AD9B4();
        slots = record->mUnknown1C;
        index = slots[slot][0];
        Object_80039F5C *p = fn_80039F5C(fn_80178308(), index);
        if (mode == 2 && !p->mUnknown2914) {index = fn_80164B78(); override = 1;}
    }
    if (out) {
        if (slots && !override) {
            if (!remap) *out = slots[slot][1];
            else {
                unsigned char n = fn_80163E94(object, index, 0)->mUnknownB;
                *out = 0;
                for (int i = 0; i <= 2; ++i) {
                    if (slots[i][0] == n) {*out = slots[i][1]; break;}
                }
            }
        } else *out = 0;
    }
    return index;
}

void fn_80165000(Object_800670B4 *object, Record_80067338 *record, unsigned int index, unsigned char value, int remap)
{
    if (fn_801650DC(record)) {
        if (remap == 1) index = fn_80163E94(object, index, 0)->mUnknownB;
        for (unsigned char i = 0; i <= 2; ++i)
            if (record->mUnknown1C[i][0] == index) {record->mUnknown1C[i][1] = value; break;}
    }
}

int fn_80165098(Record_80067338 *record) {return record->mUnknown14 == 2 || record->mUnknown14 == 17;}

int fn_801650BC(Record_80067338 *record) {unsigned int n = record->mUnknown14; return n >= 11 && n <= 18;}

int fn_801650DC(Record_80067338 *record) {unsigned int n = record->mUnknown14; return n >= 1 && n <= 5;}

int fn_801650FC(Record_80067338 *record) {return record->mUnknown14 == 21;}

void fn_80165110(Object_80167160 *record, int force)
{
    int swap = 0;
    if (record->mUnknown14 >= 1 && record->mUnknown14 <= 5) {
        Object_800670B4 *object = fn_80168708(fn_80178308());
        for (unsigned char i = 0; i <= 2; ++i) {
            unsigned char index = record->mUnknown1C[i][0];
            fn_80039F5C(fn_80178308(), index);
            if (object->mUnknown8.mUnknown84[0][index].mUnknownB == index && (i == 0 || i == 2)) {swap = 1; break;}
        }
        if (swap || force) {
            unsigned char first = record->mUnknown1C[0][0];
            unsigned char last = record->mUnknown1C[2][0];
            unsigned char a = record->mUnknown1C[0][1];
            unsigned char b = record->mUnknown1C[2][1];
            record->mUnknown1C[2][1] = a;
            record->mUnknown1C[0][0] = last;
            record->mUnknown1C[2][0] = first;
            record->mUnknown1C[0][1] = b;
        }
    }
}

int fn_801651E0(void *handle, int, signed char, int id, Record_80167094 *records)
{
    Object_80023BBC filter;
    filter.Set(6, 0x505445534C544553LL, 3, id);
    Table_8007E020 tables[2] = {{0x50544553, 0, &filter}, {-1, 0, 0}};
    ColumnValue_802D6424 columns[7] = {
        {0,0x50544553,0x6F736F70,0}, {0,0x50544553,0x69747261,0},
        {0,0x50544553,0x78747261,0}, {0,0x50544553,0x79747261,0},
        {0,0x50544553,0x736F5044,0}, {0,0x50544553,0x736F5045,0}, {0,-1,-1,0}
    };
    int cursor;
    int status = fn_801FA0BC((int)handle, tables, 0, 0, &cursor, 0);
    int opened = status == 0 || status == 23 || status == 21 || status == 20;
    if (!status) {
        status = fn_801FA228(cursor, 1, 0, columns);
        while (!status) {
            Record_80167094 *record = &records[columns[0].mValue];
            record->mUnknown18Word = columns[4].mValue;
            record->mUnknown8 = (float)columns[2].mValue;
            record->mUnknown10 = columns[1].mValue;
            record->mUnknownC = (float)columns[3].mValue;
            record->mUnknown14Word = columns[5].mValue;
            status = fn_801FA228(cursor, 0, 1, columns);
        }
    }
    if (opened) fn_801FA148(cursor);
    return 1;
}

int fn_80165464(void *handle, int, int id, Record_80167094 *records)
{
    Object_80023BBC play, route;
    play.Set(6, 0x53594C504C594C50LL, 3, id);
    route.Set(6, 0x4C5452414C545241LL, 3, id);
    Table_8007E020 plays[2] = {{0x53594C50,0,&play},{-1,0,0}};
    Table_8007E020 routes[2] = {{0x4C545241,0,&route},{-1,0,0}};
    ColumnValue_802D6424 counts[2] = {{0,0x53594C50,0x746E6361,0},{0,-1,-1,0}};
    ColumnValue_802D6424 ids[3] = {{0,0x4C545241,0x4C545241,0},{0,0x4C545241,0x6F736F70,0},{0,-1,-1,0}};
    int cursor;
    int status = fn_801FA0BC((int)handle, plays, 0, 0, &cursor, 0);
    int opened = status == 0 || status == 23 || status == 21 || status == 20;
    if (!status) {
        status = fn_801FA228(cursor, 1, 0, ids);
        route.mUnknown16.mValue.mInt = ids[0].mValue;
        while (!status) {
            Record_80167094 *record = &records[ids[1].mValue];
            route.mUnknown16.mKind = 3;
            record->mUnknown0Word = route.mUnknown16.mValue.mInt;
            fn_801FA290((int)handle, routes, 0, counts);
            record->mUnknown4Word = counts[0].mValue;
            status = fn_801FA228(cursor, 0, 1, ids);
            route.mUnknown16.mValue.mInt = ids[0].mValue;
        }
    }
    if (opened) fn_801FA148(cursor);
    return 1;
}

int fn_80165770(Object_80167160 *record, State_80167094 *state, Record_80167094 *)
{
    unsigned int kind = record->mUnknown14;
    state->mUnknown2160 = 0;
    if (!kind || (kind > 5 && kind != 38)) return 0;
    for (int i = 0; i < 3; ++i) {
        unsigned char index = record->mUnknown1C[i][0];
        int n = state->mUnknown2160;
        state->mUnknown2178[n][0] = state->mUnknown2084[index][0] - 4.0f;
        state->mUnknown2178[n][2] = state->mUnknown2084[index][2] + 4.0f;
        state->mUnknown2178[n][1] = state->mUnknown2084[index][1] - 4.0f;
        state->mUnknown2178[n][3] = state->mUnknown2084[index][3] + 4.0f;
        state->mUnknown2164[n] = i;
        ++state->mUnknown2160;
        if (!record->mUnknown1C[i][1]) state->mUnknown21C8[n] = index | 0x80;
        else {
            state->mUnknown2134[index] = 7;
            state->mUnknown21C8[n] = index & 0x7F;
        }
    }
    return 1;
}

int fn_80165890(void *handle, Record_80167094 *records, int first, unsigned char count)
{
    for (unsigned int i = first; i < count; ++i) {
        Record_80167094 *record = &records[i];
        int steps = record->mUnknown4Word;
        fn_801C1F94(record->mUnknown1C, 0, 0x1B0);
        for (int j = 0; j < steps; ++j) {
            char ax[8], ay[8], au[8], av[8], at[8], sp[8], ct[8], lt[8], ls[8];
            fn_801C2E18(ax, "ax%02d", j+1);
            fn_801C2E18(ay, "ay%02d", j+1);
            fn_801C2E18(au, "au%02d", j+1);
            fn_801C2E18(av, "av%02d", j+1);
            fn_801C2E18(at, "at%02d", j+1);
            fn_801C2E18(sp, "sp%02d", j+1);
            fn_801C2E18(ct, "ct%02d", j+1);
            fn_801C2E18(lt, "lt%02d", j+1);
            fn_801C2E18(ls, "ls%02d", j+1);
            int x, y, u, v, type, speed, link, arrow, color;
            int axTag = fn_8018AFF0(ax), ayTag = fn_8018AFF0(ay), atTag = fn_8018AFF0(at);
            int auTag = fn_8018AFF0(au), avTag = fn_8018AFF0(av), ctTag = fn_8018AFF0(ct);
            int spTag = fn_8018AFF0(sp), ltTag = fn_8018AFF0(lt), lsTag = fn_8018AFF0(ls);
            int status = fn_801FCE10(0, "use \x8c select \x8c into \x82 and \x8c into \x82 and \x8c into \x82 and \x8c into \x82 and \x8c into \x82 and \x8c into \x85 and \x8c into \x85 and \x8c into \x85 and \x8c into \x85 from 'LTRA' where 'LTRA' = \x85\n",
                (int)handle, axTag,&x,ayTag,&y,atTag,&type,auTag,&u,avTag,&v,ctTag,&link,spTag,&speed,ltTag,&arrow,lsTag,&color,record->mUnknown0Word);
            if (!status) {
                Route_80165890 *step = &record->mUnknown1C[j];
                step->mUnknown0 = (float)x;
                step->mUnknown4 = (float)y;
                step->mUnknown10 = type;
                step->mUnknown8 = (float)u;
                step->mUnknownC = (float)v;
                step->mUnknown14 = link;
                step->mUnknown18 = speed;
                step->mUnknown1C = arrow;
                step->mUnknown20 = color;
            }
        }
        record->mUnknown1C[steps].mUnknown10 = -1;
    }
    return 1;
}

void fn_80165C50(Point_80167094 *points, int count, Point_80167094 *out, float t)
{
    for (int i = 0; i < count; ++i) lbl_8031D2B8[i] = points[i];
    for (int i = 1; i < count; ++i)
        for (int j = 0; j < count - i; ++j) {
            lbl_8031D2B8[j].mX = (1.0f - t) * lbl_8031D2B8[j].mX + t * lbl_8031D2B8[j+1].mX;
            lbl_8031D2B8[j].mY = (1.0f - t) * lbl_8031D2B8[j].mY + t * lbl_8031D2B8[j+1].mY;
        }
    *out = lbl_8031D2B8[0];
}

void fn_80165D18(Point_80167094 *points, int count, Point_80167094 *out, int samples)
{
    float step = 1.0f / (float)(samples - 1);
    out[0] = points[0];
    float t = step;
    for (int i = 1; i < samples - 1; ++i) {
        fn_80165C50(points, count, &out[i], t);
        t += step;
    }
    out[samples-1] = points[count-1];
}

void fn_80165DF8(Point_80167094 *a, Point_80167094 *b, Point_80167094 *left, Point_80167094 *right,
                int width, Point_80167094 *prior, int average)
{
    Point_80167094 normal = {a->mY - b->mY, a->mX - b->mX};
    fn_802271A4(&normal, &normal);
    float half = (float)width * 0.25f;
    Point_80167094 offset;
    if (prior && average) {
        offset.mX = (normal.mX + prior->mX) * 0.5f;
        offset.mY = (normal.mY + prior->mY) * 0.5f;
        fn_802271A4(&offset, &offset);
    } else offset = normal;
    offset.mX *= half;
    offset.mY *= half;
    left->mX = a->mX - offset.mX;
    left->mY = a->mY + offset.mY;
    right->mX = a->mX + offset.mX;
    right->mY = a->mY - offset.mY;
    if (prior) *prior = normal;
}

void fn_80165F78(Point_80167094 *control, Point_80167094 *out, int samples, int width)
{
    fn_80165D18(control, 3, lbl_8031D308, samples);
    lbl_8031D308[samples] = lbl_8031D308[samples-2];
    Point_80167094 prior;
    fn_80165DF8(&lbl_8031D308[0], &lbl_8031D308[1], &out[0], &out[1], width, &prior, 0);
    int n = 2;
    for (int i = 1; i < samples - 1; ++i) {
        fn_80165DF8(&lbl_8031D308[i], &lbl_8031D308[i+1], &out[n], &out[n+1], width, &prior, 1);
        n += 2;
    }
    fn_80165DF8(&lbl_8031D308[samples-1], &lbl_8031D308[samples], &out[n], &out[n+1], width, 0, 0);
}

void fn_801660A0(Point_80167094 *points, Point_80167094 *out, int width)
{
    fn_80165DF8(&points[0], &points[1], &out[0], &out[1], width, 0, 0);
    fn_80165DF8(&points[1], &points[0], &out[2], &out[3], width, 0, 0);
}

void fn_80166110(Point_80167094 *points, Point_80167094 *out, int width, int length)
{
    Point_80167094 direction = {points[0].mX - points[1].mX, points[0].mY - points[1].mY};
    float magnitude = fn_80260B1C(direction.mX * direction.mX + direction.mY * direction.mY);
    if (magnitude != 0.0f) {direction.mX /= magnitude; direction.mY /= magnitude;}
    float x = -direction.mY * 0.5f * (float)width;
    float y = -direction.mX * 0.5f * (float)width;
    out[0].mX = points[0].mX + x;
    float forwardX = direction.mX * 0.5f * (float)length;
    out[0].mY = points[0].mY - y;
    float forwardY = direction.mY * 0.5f * (float)length;
    out[1].mX = points[0].mX - x;
    out[2].mX = out[0].mX + forwardX;
    out[2].mY = out[0].mY + forwardY;
    out[3].mX = out[1].mX + forwardX;
    out[1].mY = points[0].mY + y;
    out[3].mY = out[1].mY + forwardY;
}

int fn_801662A8(Point_80167094 *out, int count, int, Point_80167094 *quad)
{
    out[count] = quad[0];
    out[count+1] = quad[1];
    out[count+2] = quad[3];
    out[count+3] = quad[2];
    return count+4;
}

int fn_8016631C(Record_80167094 *record, int capacity, void *vertexBuffer, void *arrowBuffer,
                void *kindBuffer, void *colorBuffer, int extend)
{
    Point_80167094 *vertices = (Point_80167094 *)vertexBuffer;
    Point_80167094 (*arrows)[4] = (Point_80167094 (*)[4])arrowBuffer;
    int *kinds = (int *)kindBuffer, *colors = (int *)colorBuffer;
    Point_80167094 starts[12], ends[13], controls[3], strip[20];
    fn_801C1F94(controls, 0, 24);
    int drawn = 0;
    int count = 0;
    fn_801C1F94(strip, 0, 160);
    for (int i = 0; i <= 11; ++i) {
        Route_80165890 *step = &record->mUnknown1C[i];
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
        Point_80167094 zero = {0.0f, 0.0f};
        if (step->mUnknown10 == 1) {
            controls[0] = starts[i];
            fn_80227638(&controls[1], &step->mUnknown0, starts);
            fn_80227638(&controls[2], &step->mUnknown8, starts);
            if (controls[1].mX < 4.0f) controls[1].mX = 4.0f; else if (!(controls[1].mX <= 116.0f)) controls[1].mX = 116.0f;
            if (controls[1].mY < 4.0f) controls[1].mY = 4.0f; else if (!(controls[1].mY <= 96.0f)) controls[1].mY = 96.0f;
            if (controls[2].mX < 4.0f) controls[2].mX = 4.0f; else if (!(controls[2].mX <= 116.0f)) controls[2].mX = 116.0f;
            if (controls[2].mY < 4.0f) controls[2].mY = 4.0f; else if (!(controls[2].mY <= 96.0f)) controls[2].mY = 96.0f;
            ends[i+1] = controls[2];
            int samples = (int)(fn_8022781C(&controls[0], &controls[1]) * 0.175f + 2.0f);
            if (samples > 8) samples = 8;
            fn_80165F78(controls, strip, samples, width);
            for (int j = 0; j < samples; ++j) {
                vertices[count] = strip[j*2];
                vertices[count+1] = strip[j*2+1];
                count += 2;
            }
            drawn = 1;
        } else if (step->mUnknown10 == 0) {
            controls[0] = starts[i];
            fn_80227638(&controls[1], &step->mUnknown0, starts);
            if (controls[1].mX < 4.0f) controls[1].mX = 4.0f; else if (!(controls[1].mX <= 116.0f)) controls[1].mX = 116.0f;
            if (controls[1].mY < 4.0f) controls[1].mY = 4.0f; else if (!(controls[1].mY <= 96.0f)) controls[1].mY = 96.0f;
            ends[i+1] = controls[1];
            fn_801660A0(controls, strip, width);
            count = fn_801662A8(vertices, count, capacity, strip);
            if (fabsf(controls[0].mX - controls[1].mX) != zero.mX || fabsf(controls[0].mY - controls[1].mY) != zero.mY) drawn = 1;
        } else if (step->mUnknown10 == 2) {
            for (int j = 0; j < 2; ++j) {
                controls[0] = starts[i];
                if (!j) fn_80227638(&controls[1], &step->mUnknown0, starts);
                else fn_80227638(&controls[1], &step->mUnknown8, starts);
                if (controls[1].mX < 4.0f) controls[1].mX = 4.0f; else if (!(controls[1].mX <= 116.0f)) controls[1].mX = 116.0f;
                if (controls[1].mY < 4.0f) controls[1].mY = 4.0f; else if (!(controls[1].mY <= 96.0f)) controls[1].mY = 96.0f;
                ends[i+1] = controls[1];
                fn_801660A0(controls, strip, width);
                count = fn_801662A8(vertices, count, capacity, strip);
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
                fn_801660A0(controls, strip, width);
                count = fn_801662A8(vertices, count, capacity, strip);
            }
            Point_80167094 axis[2];
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

void fn_80166BE8(Object_80167160 *record, State_80167094 *state, Record_80167094 *entry, int team, int index, unsigned char)
{
    unsigned char r = 130, g = 130, b = 130;
    unsigned char secondaryR = 231, secondaryG = 217, secondaryB = 50;
    unsigned char primaryR, primaryG, primaryB;
    if (!fn_80177F70() && !fn_8006560C()) {
        primaryR = lbl_803EB3D3; primaryG = lbl_803EB3D7; primaryB = lbl_803EB3DB;
    } else {
        void *queue = fn_80164EC8(record, team, (unsigned short)index);
        int found = 0;
        for (unsigned char i = 0; i < 4; ++i) {
            if (fn_800F06F4(0, queue, lbl_802E98E0[i][3], 0xFFFF) != 0xFFFF) {
                secondaryR = lbl_802E98F0[i][0]; secondaryG = lbl_802E98F0[i][1]; secondaryB = lbl_802E98F0[i][2];
                found = 1;
                break;
            }
        }
        if (!found) secondaryR = secondaryG = secondaryB = 255;
        unsigned int kind = entry->mUnknown14Word;
        int inherited = 1;
        if (kind >= 5 && kind <= 9) {r = lbl_803EB3BB;g = lbl_803EB3C3;b = lbl_803EB3BF; inherited = 0;}
        else if (kind >= 10 && kind <= 15) {r = lbl_803EB3DF;g = lbl_803EB3E3;b = lbl_803EB3E7; inherited = 0;}
        else if (kind >= 16 && kind <= 18) {r = lbl_803EB3C7;g = lbl_803EB3CB;b = lbl_803EB3CF; inherited = 0;}
        primaryR = r; primaryG = g; primaryB = b;
        if (inherited) {
            unsigned int play = record->mUnknown14;
            int base = 0;
            int select = 0;
            if (play == 21) {
                if (kind >= 19 && kind <= 20) {primaryR = lbl_803EB3D3;primaryG = lbl_803EB3D7;primaryB = lbl_803EB3DB;}
                else base = 1;
            } else if (play == 11 || play == 37) {if (!kind) base = 1;}
            else if ((play >= 1 && play <= 5) || play == 38) select = 1;
            else if (play >= 12 && play <= 18) {
                primaryR = lbl_803EB3D3;primaryG = lbl_803EB3D7;primaryB = lbl_803EB3DB;
                if (record->mUnknownC != index) base = 1;
            }
            if (select) {
                int matched = 0;
                for (unsigned char i = 0; i < 3; ++i) {
                    if (record->mUnknown1C[i][0] == index) {
                        int highlight = !kind;
                        if (kind) highlight = fn_800F06F4(0, queue, 19, 0xFFFF) != 0xFFFF || fn_800F06F4(0, queue, 21, 0xFFFF) != 0xFFFF;
                        if (highlight) {
                            if (!i) {primaryR = lbl_803EB3EB;primaryG = lbl_803EB3EF;primaryB = lbl_803EB3F3;}
                            else if (i == 1) {primaryR = lbl_803EB3F7;primaryG = lbl_803EB3FB;primaryB = lbl_803EB3FF;}
                            else {primaryR = lbl_803EB403;primaryG = lbl_803EB407;primaryB = lbl_803EB40B;}
                        } else base = 1;
                        matched = 1;
                        break;
                    }
                }
                if (!matched) base = 1;
            }
            if (base) {primaryR = lbl_803EB3BB;primaryG = lbl_803EB3C3;primaryB = lbl_803EB3BF;}
        }
    }
    state->mUnknown2020[index].r = primaryR;
    state->mUnknown2020[index].g = primaryG;
    state->mUnknown2020[index].b = primaryB;
    state->mUnknown2020[index].a = 255;
    state->mUnknown204C[index].r = secondaryR;
    state->mUnknown204C[index].g = secondaryG;
    state->mUnknown204C[index].b = secondaryB;
    state->mUnknown204C[index].a = 255;
}

}
