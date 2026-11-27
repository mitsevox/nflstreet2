#ifndef GAME_MINIGAMEC_H
#define GAME_MINIGAMEC_H

/* MiniGameC, the base class of the six mini-game modes, and its depth-chart state. */
struct Object_80039F5C;
struct AutoDepthPlayer_t;

extern "C" void GameStatsUpdateRecords(void);

struct MiniGameDepthRecord_t {
    int mUnknown0;
    int mUnknown4[10];
    unsigned char mUnknown2C;
    char mUnknown2D[3];
};

struct MiniGameDepthState_t {
    unsigned int mCount;
    int mCachedValue;
    MiniGameDepthRecord_t *mpRecords;
    unsigned char mUnknownC;
    char mUnknownD[3];
};

class MiniGameC {
public:
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual int GetTotalPlayerCount();
    virtual unsigned int vfn_04(int team);
    virtual int vfn_05(int team);
    virtual unsigned int vfn_06();
    virtual void SetOption(int a, int b) {}
    virtual int GetPlayType(int a);
    virtual const float *GetAssignDirections(int a) { return 0; }
    virtual void FillDepthChart(int value, int *list, int *ids);
    virtual void AutoFillDepthChart(int value, int *list, int *ids, unsigned int count, int b);
    virtual void UpdateRecords() { GameStatsUpdateRecords(); }
    virtual int IsWinnerUserTeam();
    virtual void vfn_14() {}
    virtual void UpdateCountdown();
    virtual void AssignPlayerAwards(const int *pKinds);
    virtual void AssignTeamAwards(const int *pKinds);
    virtual void GetPlayerAwardsText(int a, unsigned char index, char *pText, unsigned char length);
    virtual void GetTeamAwardText(int team, int column, char *pText, int length);
    virtual void GetPlayerStatText(int team, unsigned char index, int kind, char *pFirst, unsigned char firstLength,
                        char *pSecond, unsigned char secondLength)
    {
        pSecond[0] = 0;
        pFirst[0] = 0;
    }
    virtual int vfn_21() { return 1; }
    virtual int AllowsPause(int a) { return 1; }

    virtual int SelectDepthRecord(AutoDepthPlayer_t *pRecords, unsigned int count);
    virtual int SumPlayerColumn(int team, unsigned int tag);
    virtual unsigned char GetAwardCount(int team, int index);
    virtual int CheckAward(int team, int index, Object_80039F5C *pPlayer, int kind);
    virtual int PlayerHasAward(int team, int index, int value);
    virtual unsigned char GetAwardWinnerCount(int index);
    virtual const char *GetAwardTitle(int kind);
    virtual int GetPlayerStat(int kind, int team, int index, Object_80039F5C *pPlayer);
    virtual int IsBestPlayerStat(int kind, int team, int index, Object_80039F5C *pPlayer,
                       int threshold, int mode);
    virtual int CheckTeamAward(int team, int kind);
    virtual int GetTeamStat(int kind, int team);
    virtual int IsBetterTeamStat(int kind, int team, int threshold, int mode);

    MiniGameC();
    int IsTutorial();

    int mUnknown0;
    int mUnknown4;
    union {
        char mUnknown8[16];
        MiniGameDepthState_t mState;
    };
};

extern "C" MiniGameC *MiniGameGetCurrent(void);

#endif
