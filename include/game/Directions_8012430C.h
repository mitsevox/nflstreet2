#ifndef GAME_DIRECTIONS_8012430C_H
#define GAME_DIRECTIONS_8012430C_H

/* Eight per-direction costs, one per 45-degree sector, cleared and filled by
   AssignDirEvaluate/AssignDirEvaluateVs through the callback table _Assign_aDirScorers. */
struct Directions_8012430C {
    float mCost[8];
};

#endif
