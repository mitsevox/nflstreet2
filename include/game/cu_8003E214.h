#ifndef GAME_CU_8003E214_H
#define GAME_CU_8003E214_H

#include "game/Object_8007A334.h"

struct Record_8003E214 {
    int id;
    unsigned int values[14];
    unsigned char excluded;
    unsigned char mUnknown61[3];
    int category;
};

typedef void (*Update_8003E214)(Record_8003E214 *, int *, Object_8007A334 *);
typedef void (*Select_8003E214)(Record_8003E214 *, int, int *, int *, int *);

extern "C" {
int fn_8003E214(int *list, int value);
void fn_8003E24C(int category, int *id, unsigned int *value);
void fn_8003E294(int category, int *ids, unsigned int *values);
void fn_8003E3FC(int id, unsigned char excluded);
void fn_8003E454(unsigned char excluded);
void fn_8003E48C(int *list);
void fn_8003E4E0(Record_8003E214 *record, int *values, Object_8007A334 *query);
void fn_8003E5E0(Record_8003E214 *records, int count, int *excluded, int *id, int *category);
void fn_8003E710(int value, int *list, Record_8003E214 **pRecords);
void fn_8003E8B8(Record_8003E214 **pRecords);
void fn_8003E8FC(int value, int *list, int *ids);
unsigned int fn_8003EA28(Record_8003E214 *records, int *excluded, int id);
void fn_8003EB2C(Record_8003E214 *records, int *allowed, int *excluded, int *id, int *category);
void fn_8003EBC4(Update_8003E214 callback);
void fn_8003EBE4(Select_8003E214 callback);
}

#endif
