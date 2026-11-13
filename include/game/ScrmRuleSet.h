#ifndef GAME_SCRMRULESET_H
#define GAME_SCRMRULESET_H

/* Scoring and game-end rules of a scrimmage, defined in cu_80176F18: the score
   limit, the winner, the game clock and where the ball is placed. The current
   rule object is held in the scrimmage state block and called through the
   fn_80178xxx wrappers. Arguments named team are 0 or 1. */
class ScrmRuleSet {
public:
    virtual int GetScoreLimit();
    virtual int GetWinner();
    virtual void AwardWin(int team);
    virtual int IsNearWin(int team);
    virtual int IsOpponentNearWin(int team);
    virtual int GetScoreType();
    virtual int GetScore(int team);
    virtual int IsTimed();
    virtual int GetGameTime();
    virtual void ResetPlaySpot();
    virtual void ResetGame(int team);
    virtual int UsesBothTeams();
    virtual int GetTeamSize();
    virtual int AllowsAudibles();
    virtual int AllowsPrediction();
    virtual int GetGoalLimit() { return 0; }
    virtual int GetGoalTotal(int team) { return 0; }
    virtual int GetGoalCount(int team) { return 0; }
    virtual void EndPlay();
    virtual void PlaceBallForDrive(int flip);
    virtual int IsWinAwarded();
};

#endif
