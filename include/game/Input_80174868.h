#ifndef GAME_INPUT_80174868_H
#define GAME_INPUT_80174868_H

/* Play-situation input and result blocks of fn_80174868 and fn_801764A0. */
struct Input_80174868 {
  float mUnknown0, mUnknown4, mUnknown8, mUnknownC;
  int mUnknown10, mUnknown14, mUnknown18, mUnknown1C;
  unsigned char mUnknown20, mUnknown21, mUnknown22, mUnknown23;
  signed char mUnknown24;
};
struct Output_80174868 {
  float mUnknown0, mUnknown4, mUnknown8, mUnknownC;
  int mUnknown10;
  signed char mUnknown14;
  unsigned char mUnknown15;
  unsigned char mUnknown16[2];
};

extern "C" void fn_801764A0(int type, Input_80174868 *in, Output_80174868 *out);

#endif
