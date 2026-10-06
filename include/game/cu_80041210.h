#ifndef GAME_CU_80041210_H
#define GAME_CU_80041210_H

struct Extra_8004149C {
    char mUnknown0[32];
    unsigned char mUnknown32;
    unsigned char mUnknown33;
    char mUnknown34[2];
    char mUnknown36[4];
    char mUnknown40[8];
    char mUnknown48[4];
    unsigned short mUnknown52;
    char mUnknown54[2];
    int mUnknown56;
    char mUnknown60[1240];
    char mUnknown1300[408];
    int mUnknown1708;
};

struct Object_80041904;
typedef void (*Callback_80041904)(Object_80041904 *pObject, int entry, int mode);

struct Object_80041904 {
    int mUnknown0;
    char mUnknown4[4];
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    char mUnknown20[12];
    int mUnknown32;
    char mUnknown36[60];
    float mUnknown96;
    float mUnknown100;
    float mUnknown104;
    float mUnknown108;
    float mUnknown112;
    float mUnknown116;
    float mUnknown120;
    float mUnknown124;
    float mUnknown128;
    float mUnknown132;
    float mUnknown136;
    int mUnknown140;
    char mUnknown144[40];
    Callback_80041904 mUnknown184;
    int mUnknown188;
    char mUnknown192[228];
    void *mUnknown420;
    char mUnknown424[4];
    Extra_8004149C *mUnknown428;
};

struct Desc_8004149C {
    int mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    float mUnknown16;
    float mUnknown20;
    float mUnknown24;
};

extern "C" {
void fn_800413F0(int maxObjects, int maxExtras);
void fn_80041490(void);
Object_80041904 *fn_8004149C(void *pOwner, Desc_8004149C *pDesc);
int fn_80041664(void);
int fn_800416CC(float dt);
int fn_8004183C(void);
Object_80041904 *fn_80041904(int index);
int fn_80041928(void);
}

#endif
