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
    char mUnknown1300[404];
    unsigned char mUnknown1704;
    char mUnknown1705[3];
    int mUnknown1708;
};

struct Object_80040818;
struct Object_80041904;

/* Animation word: -1 for none; its low halfword is the key passed to
   fn_801BE068 and the word is compared with fn_801BE648's result. */
union AnimId_80041904 {
    int mValue;
    struct {
        short mUnknown0;
        unsigned short mKey;
    } mParts;
};

/* Entry of the list at Object_80041904 +312, matched by its name. */
struct Node_80041904 {
    char mName[64];
    AnimId_80041904 mUnknown64;
    char mUnknown68[24];
    unsigned short mUnknown92;
    char mUnknown94[10];
    int mUnknown104;
    int mUnknown108;
    char mUnknown112[16];
    void *mUnknown128;
    Node_80041904 *mpNext;
};
typedef void (*Callback_80041904)(Object_80041904 *pObject, int entry, int mode);

struct Object_80041904 {
    int mUnknown0;
    int mUnknown4;
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
    int mUnknown144;
    unsigned short mUnknown148;
    char mUnknown150[2];
    Object_80040818 *mUnknown152[8];
    Callback_80041904 mUnknown184;
    int mUnknown188;
    char mUnknown192[4];
    AnimId_80041904 mUnknown196;
    char mUnknown200[112];
    Node_80041904 *mUnknown312;
    char mUnknown316[44];
    float mUnknown360;
    float mUnknown364;
    float mUnknown368;
    float mUnknown372;
    int mUnknown376;
    unsigned char mUnknown380;
    unsigned char mUnknown381;
    char mUnknown382[38];
    void *mUnknown420;
    char mUnknown424[3];
    unsigned char mUnknown427;
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
