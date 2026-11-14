#ifndef ENGINE_CU_802714A8_H
#define ENGINE_CU_802714A8_H

typedef struct Params_803A6C40 {
    unsigned char mUnknown0[8];
    unsigned short m8;
    unsigned short mA;
    unsigned char mUnknownC[2];
    unsigned char mE;
    unsigned char mUnknownF[3];
    unsigned char m12;
    unsigned char mUnknown13;
    float m14;
    unsigned char mUnknown18[9];
    unsigned char m21;
    unsigned char m22;
    unsigned char m23;
    unsigned char mUnknown24;
    unsigned char m25;
    unsigned char mUnknown26[2];
    unsigned char m28;
    unsigned char mUnknown29;
    unsigned short m2A[2];
    unsigned char mUnknown2E[0xA];
    unsigned int m38;
    unsigned int m3C;
    unsigned char mUnknown40[0x5C];
} Params_803A6C40;

typedef struct Record_803A6DF0 {
    int m0;
    short m4[8];
    int m14;
    int m18;
    unsigned short m1C;
    short m1E;
    unsigned short m20;
    unsigned char m22;
    unsigned char m23;
    unsigned short m24;
    unsigned char m26;
    unsigned char mUnknown27;
    short m28;
    unsigned char m2A;
    unsigned char mUnknown2B[5];
    float m30;
    float m34;
    float m38;
    int m3C;
    int m40;
    int m44;
    float m48;
    unsigned short m4C;
    unsigned char m4E;
    unsigned char mUnknown4F;
    unsigned short m50;
    unsigned char mUnknown52[0xA];
    signed char m5C;
    signed char m5D;
    signed char m5E;
    signed char m5F;
    unsigned char mUnknown60[4];
    float *m64;
    signed char m68;
    unsigned char m69;
    unsigned char m6A;
    unsigned char m6B;
    unsigned char m6C;
    unsigned char m6D;
    unsigned short m6E;
    struct SndEnvStage_t *m70;
    unsigned char mUnknown74[4];
    signed char *m78;
    int m7C;
    signed char *m80;
    short m84;
    short m86;
    short m88;
    unsigned short m8A;
    unsigned short m8C;
    unsigned short m8E;
} Record_803A6DF0;

typedef struct Struct_803A6C24 {
    unsigned short m0;
    unsigned short m2;
    unsigned char m4;
    unsigned char m5;
    unsigned char m6;
    unsigned char mUnknown7[3];
    unsigned char mA;
    unsigned char mUnknownB;
    unsigned char mC;
    unsigned char mUnknownD;
    unsigned short mE;
    unsigned short m10;
    unsigned char mUnknown12[0xA];
    Params_803A6C40 m1C;
    void *(*mB8)(int size);
    // FAKEMATCH: volatile only for the target's reload of the release callback in fn_80275194
    void (*volatile mBC)(void *p);
    unsigned char mUnknownC0[0xC];
    Params_803A6C40 mCC;
    unsigned char m168;
    unsigned char m169;
    signed char m16A;
    unsigned char mUnknown16B;
    short m16C;
    unsigned char mUnknown16E;
    unsigned char m16F;
    volatile unsigned int m170;
    void (*m174[12])(void);
    unsigned char mUnknown1A4[0x1C];
    int (*m1C0)(int bank);
    unsigned char mUnknown1C4[8];
    Record_803A6DF0 *m1CC;
    struct SndBankSlot_t *m1D0;
    struct Struct_80278894 *m1D4;
    unsigned char mUnknown1D8[0x48];
    void (*m220)(void);
    void (*m224)(void);
} Struct_803A6C24;

typedef struct Setup_80272EC4 {
    int m0;
    void (*m4)(int);
    unsigned char m8;
    unsigned char m9;
    unsigned char mA;
} Setup_80272EC4;

typedef struct Node_80279D90 Node_80279D90;

struct Node_80279D90 {
    int (*m0)(Node_80279D90 *node, int count, float *a, float *b, int flag);
    void (*m4)(Node_80279D90 *node);
    Node_80279D90 *m8;
    int mC;
    Node_80279D90 *m10;
    int m14;
    unsigned short m18;
    unsigned char m1A;
    unsigned char m1B;
};

typedef struct Desc_80276798 {
    int m0;
    int m4;
    unsigned char mUnknown8[2];
    unsigned short mA;
    void (*mC)(Node_80279D90 *node, int a, int slot);
    int (*m10)(Node_80279D90 *node, int count, float *a, float *b, int flag);
    void (*m14)(Node_80279D90 *node);
} Desc_80276798;

typedef struct Record_803B5010 {
    unsigned char m0;
    unsigned char m1;
    unsigned char mUnknown2[2];
    float m4[6];
    float m1C[6];
    float *m34;
    float *m38;
    float m3C;
    Node_80279D90 *m40;
    int (*m44)(Node_80279D90 *node);
    Node_80279D90 *m48;
    Node_80279D90 *m4C;
    Node_80279D90 *m50;
    Node_80279D90 *m54;
    Node_80279D90 *m58;
} Record_803B5010;

typedef struct Params_80275F80 {
    int m0;
    int m4;
    int m8;
    int mC;
    int m10;
    int m14;
    int m18;
    int m1C;
    int m20;
    int m24;
    int (*m28)(Node_80279D90 *node);
} Params_80275F80;

typedef struct Struct_803B4E34 {
    Setup_80272EC4 m0;
    unsigned short mC;
    unsigned char mE;
    unsigned char mUnknownF[5];
    int *m14;
    void (*m18[6][3])(Node_80279D90 *node, Params_80275F80 *params);
    int m60[6][3];
    void *mA8[2];
    int *mB0[2];
    void *mB8[6];
    int *mD0[6];
    float mE8[6];
    float *m100;
    Node_80279D90 *m104[6];
    unsigned char mUnknown11C[0x18];
    Node_80279D90 m134[6];
    Record_803B5010 *m1DC;
    void (*m1E0)(int count, float *src, float *dst, float gain);
    void (*m1E4)(int count, short *src, float *dst);
} Struct_803B4E34;

#ifdef __cplusplus
extern "C" {
#endif

extern void *(*lbl_803B53E4)(int size);
extern void (*lbl_803B53E8)(void *p);
extern int (*lbl_80301000)(void *dst, void *src, int size);
extern Struct_803A6C24 lbl_803A6C24;
extern Struct_803B4E34 lbl_803B4E34;

int SNDI_memcpy(void *dst, void *src, int size);

int fn_80274304(int index);
int fn_80274334(int index);
int fn_80274398(void);
void fn_80274960(int index);
int fn_80274B50(int index);
void fn_80274D34(int index, int value);
void fn_80274E24(int index, int value);
int fn_8027474C(int index);
int fn_802750B8(int index, Desc_80276798 *desc);

void fn_802774C8(int count, short *src, float *dst);
unsigned char *fn_802792F0(int index, int channel, int *length, int *b);
void fn_8027952C(int index, int channel, int value);
void fn_802797F4(void *(*alloc)(int size));
void fn_80279800(void (*release)(void *p));
int fn_8027980C(int (*copy)(void *dst, void *src, int size));
void fn_8027986C(unsigned int start, unsigned int length);
void fn_802798C0(void);
void fn_80279C20(Node_80279D90 *node);
int fn_80279CB8(Node_80279D90 *node);
void fn_80279D90(Node_80279D90 **list, Node_80279D90 *node);
void fn_8027A4C0(Node_80279D90 *node, int value);
void fn_8027A7FC(void);
void fn_8027A844(void);
void fn_8027A8A4(void);
void fn_8027A8EC(int count, float *src, float *dst, float gain);

#ifdef __cplusplus
}
#endif

#endif
