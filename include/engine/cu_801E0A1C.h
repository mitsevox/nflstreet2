#ifndef ENGINE_CU_801E0A1C_H
#define ENGINE_CU_801E0A1C_H

struct Desc_801E0AEC {
    int mHeap;
    int mCount;
};

struct Data_801E0DF0 {
    void *mpData;
    int mUnknown4;
    int mUnknown8;
};

struct Desc_801E0DF0 {
    int mId;
    int mUnknown04;
    int mUnknown08;
    float mUnknown0C;
    int mUnknown10;
    Data_801E0DF0 mUnknown14;
    int mUnknown20;
    unsigned char mUnknown24;
};

struct Info_801E1084;

extern "C" {
int fn_801E0AE4(void);
int fn_801E0AEC(Desc_801E0AEC *pDesc);
void fn_801E0BE4(void);
int fn_801E0CA8(void *pData, int a, int b);
int fn_801E0D68(int handle);
int fn_801E0DF0(Desc_801E0DF0 *pDesc);
int fn_801E0EF8(int id);
int fn_801E0F7C(int id, int a);
int fn_801E0F9C(int id, int a);
void fn_801E0FBC(int id, int value);
void fn_801E0FE0(int a, int b, int c);
void fn_801E1004(int a, int b);
void fn_801E1028(int a);
void fn_801E1048(int a, int b);
int fn_801E1084(int id, Info_801E1084 *pInfo);
}

#endif
