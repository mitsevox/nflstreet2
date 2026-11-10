#ifndef GAME_STORY_TEAM_H
#define GAME_STORY_TEAM_H

/* 32-byte output block of StoryTeamLoadOneToStats and StoryTeamAddOneToStats; both fall back to a
   local block of their own when the pointer is null. */
struct StoryTeamIdBlock_t {
    int mUnknown0;
    char mUnknown4[28];
};

extern "C" {
int StoryTeamLoadOneToStats(int a, int b, StoryTeamIdBlock_t *pOut);
int StoryTeamAddOneToStats(int a, int b, StoryTeamIdBlock_t *pOut);
}

#endif
