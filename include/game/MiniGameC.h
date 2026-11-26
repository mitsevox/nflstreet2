#ifndef GAME_MINIGAMEC_H
#define GAME_MINIGAMEC_H

/* MiniGameC, the base class of the six mini-game modes, and its depth-chart state. */
struct Object_80039F5C;
struct AutoDepthPlayer_t;

extern "C" void GameStatsUpdateRecords(void);

struct Record_80148C4C {
    int mUnknown0;
    int mUnknown4[10];
    unsigned char mUnknown2C;
    char mUnknown2D[3];
};

struct State_80148A58 {
    unsigned int mCount;
    int mCachedValue;
    Record_80148C4C *mpRecords;
    unsigned char mUnknownC;
    char mUnknownD[3];
};

class MiniGameC {
public:
    virtual void vfn_01() = 0;
    virtual void vfn_02() = 0;
    virtual int vfn_03();
    virtual unsigned int vfn_04(int team);
    virtual int vfn_05(int team);
    virtual unsigned int vfn_06();
    virtual void vfn_07(int a, int b) {}
    virtual int vfn_08(int a);
    virtual const float *vfn_09(int a) { return 0; }
    virtual void vfn_10(int value, int *list, int *ids);
    virtual void AutoFillDepthChart(int value, int *list, int *ids, unsigned int count, int b);
    virtual void vfn_12() { GameStatsUpdateRecords(); }
    virtual int IsWinnerUserTeam();
    virtual void vfn_14() {}
    virtual void vfn_15();
    virtual void vfn_16(const int *pKinds);
    virtual void vfn_17(const int *pKinds);
    virtual void GetPlayerAwardsText(int a, unsigned char index, char *pText, unsigned char length);
    virtual void vfn_19(int team, int column, char *pText, int length);
    virtual void GetPlayerStatText(int team, unsigned char index, int kind, char *pFirst, unsigned char firstLength,
                        char *pSecond, unsigned char secondLength)
    {
        pSecond[0] = 0;
        pFirst[0] = 0;
    }
    virtual int vfn_21() { return 1; }
    virtual int vfn_22(int a) { return 1; }

    virtual int vfn_23(AutoDepthPlayer_t *pRecords, unsigned int count);
    virtual int vfn_24(int team, unsigned int tag);
    virtual unsigned char vfn_25(int team, int index);
    virtual int CheckAward(int team, int index, Object_80039F5C *pPlayer, int kind);
    virtual int PlayerHasAward(int team, int index, int value);
    virtual unsigned char vfn_28(int index);
    virtual const char *vfn_29(int kind);
    virtual int vfn_30(int kind, int team, int index, Object_80039F5C *pPlayer);
    virtual int vfn_31(int kind, int team, int index, Object_80039F5C *pPlayer,
                       int threshold, int mode);
    virtual int vfn_32(int team, int kind);
    virtual int vfn_33(int kind, int team);
    virtual int vfn_34(int kind, int team, int threshold, int mode);

    MiniGameC();
    int fn_80149014();

    int mUnknown0;
    int mUnknown4;
    union {
        char mUnknown8[16];
        State_80148A58 mState;
    };
};

extern "C" MiniGameC *MiniGameGetCurrent(void);

#endif
