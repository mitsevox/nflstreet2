#ifndef GAME_PENALTYSITUATION_H
#define GAME_PENALTYSITUATION_H

/* The play situation a penalty is enforced from and the outcome PenaltyEnforce writes back. */
struct PenaltySituation_t {
  float mUnknown0, mUnknown4, mUnknown8, mUnknownC;
  int mUnknown10, mUnknown14, mUnknown18, mUnknown1C;
  unsigned char mUnknown20, mUnknown21, mUnknown22, mUnknown23;
  signed char mUnknown24;
};
struct PenaltyOutcome_t {
  float mUnknown0, mUnknown4, mUnknown8, mUnknownC;
  int mUnknown10;
  signed char mUnknown14;
  unsigned char mUnknown15;
  unsigned char mUnknown16[2];
};

extern "C" void PenaltyEnforce(int type, PenaltySituation_t *in, PenaltyOutcome_t *out);

#endif
