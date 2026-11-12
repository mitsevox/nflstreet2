/* Penalty rules: deciding when a foul is called (offside at the snap, intentional grounding, pass
   interference, face mask and roughing rolls scaled by the penalty frequency settings) and
   enforcing it from the penalty kind table: marching off 5, 10 or 15 yards with the
   half-the-distance rule, picking the next down, the new line to gain and the team in possession. */
#include "game/Entry_800B206C.h"
#include "game/fn_80177FE0.h"
#include "game/Object_80039F5C.h"
#include "game/Point2.h"
#include "game/Ball.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_802372EC.h"
#include <math.h>
#include "game/fn_8009D990.h"
#include "game/fn_8013AD94.h"
#include "game/PenaltySituation.h"
struct PenaltyKindInfo_t {
  unsigned short mUnknown0, mUnknown2;
  unsigned int mUnknown4;
  void (*mUnknown8)(PenaltySituation_t *, PenaltyOutcome_t *);
};
struct PenaltyRouteView_t {
  unsigned short mUnknown0;
  unsigned char mUnknown2[2];
  Point2_t mUnknown4;
  unsigned char mUnknownC[4];
  unsigned int mUnknown10;
};
struct PenaltyContactView_t {
  unsigned char mUnknown0;
  unsigned char mUnknown1[31];
  float mUnknown20;
  unsigned char mUnknown24[17];
  unsigned char mUnknown35, mUnknown36;
};
template <class T>
static inline T _PenaltyClamp(T value, T low, T high) {
  return !(value < low) ? (value <= high ? value : high) : low;
}
extern "C" {
void PenaltyEnforceKind0(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind15(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind1(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind2(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind4(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind5(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind7(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind6(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind8(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind9(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind10(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind11(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind12(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind13(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind14(PenaltySituation_t *, PenaltyOutcome_t *);
void PenaltyEnforceKind17(PenaltySituation_t *, PenaltyOutcome_t *);
PenaltyKindInfo_t _Penalty_aKindInfo[18] = {
    {15, 15, 0xFE000008, PenaltyEnforceKind0}, {5, 0, 0xFE000006, PenaltyEnforceKind1},
    {0, 5, 0xFE000000, PenaltyEnforceKind2},   {0, 5, 0xFE000006, PenaltyEnforceKind2},
    {5, 5, 0xFE000018, PenaltyEnforceKind4},   {15, 15, 0xFE000018, PenaltyEnforceKind5},
    {15, 15, 0xFE000008, PenaltyEnforceKind6}, {0, 15, 0xFE000008, PenaltyEnforceKind7},
    {5, 0, 0xFE000006, PenaltyEnforceKind8},   {10, 15, 0xFE000008, PenaltyEnforceKind9},
    {10, 0, 0xFE000008, PenaltyEnforceKind10},  {10, 0, 0xFE000004, PenaltyEnforceKind11},
    {0, 15, 0xFE000028, PenaltyEnforceKind12},  {0, 5, 0xFE000008, PenaltyEnforceKind13},
    {0, 15, 0xFE000008, PenaltyEnforceKind14},  {15, 15, 0xFE000004, PenaltyEnforceKind15},
    {15, 15, 0xFE00000C, PenaltyEnforceKind15}, {15, 15, 0xFE000004, PenaltyEnforceKind17},
};
extern float gPlyrMoveFwdSpeed;
unsigned char fn_80178308(void);
unsigned char fn_80178320(void);
unsigned char fn_80178348(void);
int fn_801783AC(int);
void fn_801783D0(int, int);
float fn_80178A2C(void);
float fn_80178A08(void);
int fn_80177F70(void);
int fn_801784E8(void);
void PenaltyResolveOutcome(PenaltySituation_t *, PenaltyOutcome_t *, float, int);
void fn_800B2640(int, int);
int fn_800B2600(void);
void fn_800B260C(short);
float fn_800B2618(int);
int fn_801CFE40(float, float);
int MathAngleDiff(int, int);
void fn_80227690(void *, void *, void *);
int BallStateGet(void *, int *);
int fn_80177C38(void);
void PenaltyApplyDiscipline(float *, Object_80039F5C *, int);
void fn_800B2370(Object_80039F5C *, int, Object_80039F5C *, float);
int fn_8009D86C(void);
void ClockRuleSetFlags(unsigned int);
void SortArray(int, void *, int, int,
                 int (*)(Entry_800B206C *, Entry_800B206C *), int, int, int);
int PenaltyIsPlayingBall(Object_80039F5C *, Object_80039F5C *, void *);
void PenaltyCallInterference(int, Object_80039F5C *, Object_80039F5C *);
extern const char *gPossJointNames[];
unsigned int fn_80178D18(int team);
void fn_80178370(void);
int fn_800BA6F8(void);
int fn_801787A0(void);
int PlayBookGetReceiver(int team, int index, unsigned char *pOut);
int CharSkelGetJointByName(void *p, const char *pName);
float fn_802270A4(void *);
void PenaltyApplyDiscipline(float *value, Object_80039F5C *, int) {
  unsigned int factor = 127;
  float normalized = (float)factor * 0.003921568859368563f;
  *value *= (float)(1.2000000476837158 - (double)normalized * 0.4);
}
float PenaltyMarchOff(float, float, int);
void PenaltyResolveOutcome(PenaltySituation_t *in, PenaltyOutcome_t *out, float value,
                 int type) {
  if (!in || !out)
    return;
  int team = fn_80178348();
  if (in->mUnknown22)
    team = (unsigned char)(team ^ 1);
  if (team == fn_80178308() && in->mUnknown20 == team && !in->mUnknown21) {
    if (in->mUnknown14 == 6) {
      out->mUnknown10 = 3;
      return;
    }
    out->mUnknown10 = 2;
    out->mUnknown14 = 0;
    out->mUnknown15 ^= 1;
    out->mUnknown8 = in->mUnknown8;
    out->mUnknown0 = -PenaltyMarchOff(out->mUnknown8, value, 0);
    return;
  }
  if (team != fn_80178308() && !in->mUnknown21 &&
      in->mUnknown20 == fn_80178320()) {
    if (in->mUnknown14 == 6) {
      out->mUnknown10 = 3;
      return;
    }
    out->mUnknown10 = 2;
    if (in->mUnknown24 > 0) {
      out->mUnknown14 = in->mUnknown24;
      if (out->mUnknown14 == 6 || out->mUnknown14 == 9) {
        out->mUnknown8 = fn_80178A2C() - 5.0f;
        out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, value, 0);
      }
    }
    return;
  }
  if (team != fn_80178308() && !in->mUnknown21 &&
      in->mUnknown20 != fn_80178320()) {
    out->mUnknown8 = -out->mUnknown8;
    out->mUnknown14 = 0;
    if (in->mUnknown22)
      out->mUnknown0 = -out->mUnknown0;
    if (in->mUnknown14 == 6) {
      if (in->mUnknown24 > 0) {
        out->mUnknown14 = in->mUnknown24;
        out->mUnknownC = value;
        out->mUnknown10 = 3;
      } else {
        out->mUnknown14 = 0;
        out->mUnknown10 = 1;
      }
    } else if (type || !(out->mUnknown0 < in->mUnknownC)) {
      out->mUnknown10 = 2;
    } else
      out->mUnknown10 = type;
    return;
  }
  if (team != fn_80178308() && in->mUnknown21 == 1 &&
      in->mUnknown20 != fn_80178308()) {
    out->mUnknown14 = 0;
    out->mUnknown10 = 0;
    out->mUnknown15 ^= 1;
    return;
  }
  if (in->mUnknown14 != 6) {
    if (!(out->mUnknown0 < in->mUnknownC)) {
      if (in->mUnknown24 > 0)
        out->mUnknown14 = in->mUnknown24;
      out->mUnknown10 = 2;
      return;
    }
  } else {
    if (in->mUnknown24 > 0) {
      out->mUnknown14 = in->mUnknown24;
      out->mUnknownC = value;
      out->mUnknown10 = 3;
    } else {
      out->mUnknown10 = 1;
      out->mUnknown14 = 0;
    }
    return;
  }
  if (in->mUnknown24 > 0)
    out->mUnknown14 = in->mUnknown24;
  if (type)
    out->mUnknown10 = 2;
  else
    out->mUnknown10 = type;
}

int PenaltyResolvePair(Entry_800B206C *events, int, unsigned char *result) {
  int handled = 0;
  *result = 0;
  int team = events[0].mUnknown4Bytes[2], other = events[1].mUnknown4Bytes[2];
  unsigned short a = team == fn_80178308()
                         ? _Penalty_aKindInfo[events[0].mUnknown0].mUnknown0
                         : _Penalty_aKindInfo[events[0].mUnknown0].mUnknown2;
  unsigned short b = other == fn_80178308()
                         ? _Penalty_aKindInfo[events[1].mUnknown0].mUnknown0
                         : _Penalty_aKindInfo[events[1].mUnknown0].mUnknown2;
  if (team == other) {
    if (a == 15 && b == 5) {
      handled = 1;
      *result = 1;
    } else if (a == 5 && b == 15) {
      handled = 1;
      *result = 1;
      Entry_800B206C temp = events[0];
      events[0] = events[1];
      events[1] = temp;
    }
  } else {
    *result = 2;
    handled = 1;
  }
  return handled;
}
int PenaltyResolvePairOther(Entry_800B206C *, int, unsigned char *result) {
  *result = 0;
  return -1;
}
int PenaltyResolvePairKind1First(Entry_800B206C *, int, unsigned char *result) {
  *result = 0;
  return -1;
}
int PenaltyCompareEvents(Entry_800B206C *a, Entry_800B206C *b) {
  return a->mUnknown14 - b->mUnknown14;
}
float PenaltyMarchOff(float value, float amount, int direction) {
  if (!(value >= -fn_80178A2C()))
    value = -fn_80178A2C();
  else if (!(value <= fn_80178A2C()))
    value = fn_80178A2C();
  float out;
  if (direction) {
    out = value - amount;
    float limit = value - fabsf(value + fn_80178A2C()) * 0.5f;
    if (!(out >= limit))
      out = limit;
  } else {
    out = value + amount;
    float limit = fabsf(value - fn_80178A2C()) * 0.5f + value;
    if (!(out <= limit))
      out = limit;
  }
  if (!(out >= -fn_80178A2C()))
    return -fn_80178A2C();
  if (out <= fn_80178A2C())
    return out;
  return fn_80178A2C();
}
void PenaltySetupOutcome(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  unsigned char side = fn_80178348();
  if (in->mUnknown22)
    side ^= 1;
  int other = side != fn_80178308();
  unsigned char direction = in->mUnknown21;
  out->mUnknown0 = in->mUnknown0;
  out->mUnknown14 = 0;
  out->mUnknown15 = fn_80178308();
  if (direction) {
    out->mUnknown10 = 1;
    if (in->mUnknown22)
      out->mUnknown10 = 2;
  } else
    out->mUnknown10 = 2;
  out->mUnknown8 = in->mUnknown8;
  if (in->mUnknown10 != 3) {
    out->mUnknown8 = in->mUnknown4;
    return;
  }
  if (!other) {
    out->mUnknown8 = in->mUnknown4;
    if (direction) {
      if (!(in->mUnknown8 >= in->mUnknown4))
        out->mUnknown8 = in->mUnknown8;
      if (in->mUnknown22)
        return;
      if (!(in->mUnknown8 >= in->mUnknown0)) {
        if (!(in->mUnknown8 <= -fn_80178A2C()))
          out->mUnknown8 = in->mUnknown0;
        else {
          out->mUnknown8 = in->mUnknown8;
          out->mUnknown14 = -2;
        }
      }
      if (!(in->mUnknown8 <= in->mUnknown0) &&
          !(in->mUnknown4 >= in->mUnknown0)) {
        if (!(in->mUnknown4 <= -fn_80178A2C()))
          out->mUnknown8 = in->mUnknown0;
        else {
          out->mUnknown8 = in->mUnknown8;
          out->mUnknown14 = -2;
        }
      }
      return;
    }
    if (in->mUnknown22)
      return;
    if (!(in->mUnknown8 < in->mUnknown0)) {
      if (!(in->mUnknown4 >= in->mUnknown0))
        out->mUnknown8 = in->mUnknown0;
      if (in->mUnknown8 >= in->mUnknown0)
        goto clampLow;
    }
    if (!(in->mUnknown4 >= in->mUnknown0)) {
      if (!(in->mUnknown8 <= in->mUnknown4))
        out->mUnknown8 = in->mUnknown8;
      else
        out->mUnknown8 = in->mUnknown4;
    }
    goto clampLow;
  }
  if (!direction) {
    if (in->mUnknown20 == fn_80178308()) {
      out->mUnknown8 = in->mUnknown8;
      out->mUnknown15 ^= 1;
      goto clampLow;
    }
    if (!(in->mUnknown4 >= out->mUnknown8))
      out->mUnknown8 = in->mUnknown4;
    if (!fn_801783AC(2)) {
      if (!(in->mUnknown8 <= -fn_80178A2C()) &&
          !(in->mUnknown8 >= in->mUnknown4))
        out->mUnknown8 = in->mUnknown8;
      else
        out->mUnknown8 = in->mUnknown4;
    }
  clampLow:
    if (!(out->mUnknown8 >= -fn_80178A2C()))
      out->mUnknown8 = -fn_80178A2C();
    return;
  }
  if (fn_801783AC(15) && !in->mUnknown23) {
    out->mUnknown8 = in->mUnknown0;
    out->mUnknown15 ^= 1;
    return;
  }
  if (in->mUnknown20 == fn_80178308()) {
    if (!(out->mUnknown8 <= in->mUnknown4))
      out->mUnknown8 = in->mUnknown4;
  } else {
    if (!in->mUnknown22 && !(in->mUnknown8 >= in->mUnknown0)) {
      if (!(in->mUnknown8 <= -fn_80178A2C()))
        out->mUnknown8 = in->mUnknown0;
      else {
        out->mUnknown8 = in->mUnknown8;
        out->mUnknown14 = -2;
      }
    }
    if (!(out->mUnknown8 <= fn_80178A2C()))
      out->mUnknown8 = fn_80178A2C();
  }
  if (in->mUnknown20 == fn_80178320())
    out->mUnknown15 ^= 1;
  else
    out->mUnknown10 = 2;
}
void PenaltyEnforceKind0(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 15.0f, in->mUnknown21);
}
void PenaltyEnforceKind15(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 15.0f, in->mUnknown21);
  if (in->mUnknown14 == 6) {
    if (in->mUnknown24 > 0) {
      out->mUnknown10 = 3;
      out->mUnknownC = 15.0f;
      out->mUnknown14 = in->mUnknown24;
      return;
    }
  } else if (in->mUnknown24 > 0) {
    out->mUnknown14 = in->mUnknown24;
    out->mUnknown10 = 2;
  }
  if (in->mUnknown14 == 6)
    out->mUnknown10 = 1;
}
void PenaltyEnforceKind1(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  out->mUnknown10 = 1;
  out->mUnknown14 = 0;
  out->mUnknown8 = in->mUnknown0;
  out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 5.0f, in->mUnknown21);
}
void PenaltyEnforceKind2(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  out->mUnknown10 = 1;
  out->mUnknown8 = in->mUnknown0;
  out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 5.0f, in->mUnknown21);
  out->mUnknown14 = 0;
}
void PenaltyEnforceKind4(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  if (!(in->mUnknown4 <= out->mUnknown8) && in->mUnknown20 == fn_80178320())
    out->mUnknown8 = in->mUnknown4;
  out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 5.0f, in->mUnknown21);
  PenaltyResolveOutcome(in, out, 5.0f, 0);
}
void PenaltyEnforceKind5(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 15.0f, in->mUnknown21);
  PenaltyResolveOutcome(in, out, 15.0f, 1);
}
void PenaltyEnforceKind7(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  out->mUnknown8 = in->mUnknown8;
  if (!(out->mUnknown8 >= -fn_80178A2C()))
    out->mUnknown8 = -30.0f;
  out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 15.0f, in->mUnknown21);
  out->mUnknown10 = 2;
  out->mUnknown14 = 0;
  if (out->mUnknown15 == in->mUnknown20)
    out->mUnknown15 ^= 1;
  int team = fn_80178308();
  if (team == fn_80178348())
    out->mUnknown0 = -out->mUnknown0;
}
void PenaltyEnforceKind6(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  out->mUnknown8 = in->mUnknown8;
  if (!(out->mUnknown8 >= -fn_80178A2C()))
    out->mUnknown8 = -30.0f;
  out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 15.0f, in->mUnknown21);
  out->mUnknown10 = 2;
  out->mUnknown14 = 0;
  if (out->mUnknown15 == in->mUnknown20)
    out->mUnknown15 ^= 1;
}
void PenaltyEnforceKind8(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  out->mUnknown8 = in->mUnknown0;
  out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 5.0f, in->mUnknown21);
  out->mUnknown10 = 1;
  out->mUnknown14 = 0;
}
void PenaltyEnforceKind9(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  if (in->mUnknown20 == fn_80178348()) {
    if (in->mUnknown14 == 6) {
      out->mUnknown14 = 0;
      out->mUnknown10 = 3;
    } else {
      out->mUnknown8 = in->mUnknown0;
      out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 10.0f, in->mUnknown21);
      out->mUnknown10 = 1;
      out->mUnknown14 = 0;
    }
    return;
  }
  if (in->mUnknown14 == 6) {
    if (in->mUnknown24 > 0) {
      out->mUnknown14 = in->mUnknown24;
      out->mUnknown10 = 3;
      return;
    }
    out->mUnknown10 = 1;
    out->mUnknown14 = 0;
    if (!(in->mUnknown0 <= fn_80178A2C() - 2.0f))
      out->mUnknown0 = (fn_80178A2C() - in->mUnknown0) * 0.5f + in->mUnknown0;
    else
      out->mUnknown0 = fn_80178A2C() - 1.0f;
    return;
  }
  out->mUnknown10 = 2;
  out->mUnknown8 = in->mUnknown0;
  out->mUnknown14 = 0;
  if (!(in->mUnknown8 >= fn_80178A2C())) {
    out->mUnknown0 = in->mUnknown8;
    return;
  }
  if (!(in->mUnknown0 <= fn_80178A2C() - 2.0f))
    out->mUnknown0 = (fn_80178A2C() - in->mUnknown0) * 0.5f + in->mUnknown0;
  else
    out->mUnknown0 = fn_80178A2C() - 1.0f;
}
void PenaltyEnforceKind10(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 10.0f, in->mUnknown21);
}
void PenaltyEnforceKind11(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  if (in->mUnknown14 == 6)
    out->mUnknown10 = 3;
  else
    out->mUnknown10 = 0;
  out->mUnknown8 = in->mUnknown0;
  if (!(in->mUnknown0 <= in->mUnknown8 + 10.0f))
    out->mUnknown0 = in->mUnknown8;
  else
    out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 10.0f, in->mUnknown21);
  if (in->mUnknown14 != 6) {
    if (!(in->mUnknown8 >= -fn_80178A2C())) {
      out->mUnknown10 = 1;
      out->mUnknown14 = -2;
    } else
      out->mUnknown14 = 0;
  }
}
void PenaltyEnforceKind12(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  if (in->mUnknown14 == 6 && in->mUnknown24 > 0) {
    out->mUnknown10 = 3;
    out->mUnknownC = 15.0f;
    out->mUnknown14 = in->mUnknown24;
    return;
  }
  if (!(in->mUnknown4 <= in->mUnknown0) && fn_80178308() == fn_80178348())
    out->mUnknown8 = in->mUnknown4;
  else
    out->mUnknown8 = in->mUnknown0;
  out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 15.0f, in->mUnknown21);
  out->mUnknown10 = 2;
  out->mUnknown14 = 0;
  if (in->mUnknown14 == 6)
    out->mUnknown10 = 1;
  out->mUnknown15 = fn_80178348();
}
void PenaltyEnforceKind13(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  out->mUnknown8 = in->mUnknown0;
  out->mUnknown0 = PenaltyMarchOff(in->mUnknown0, 5.0f, in->mUnknown21);
  if (in->mUnknown14 != 6) {
    if (out->mUnknown0 < in->mUnknownC)
      out->mUnknown10 = 1;
    else
      out->mUnknown10 = 2;
  } else if (in->mUnknown24 > 0) {
    out->mUnknown10 = 3;
    out->mUnknownC = 5.0f;
    out->mUnknown14 = in->mUnknown24;
  } else
    out->mUnknown10 = 1;
  out->mUnknown15 = fn_80178348();
  if (fn_80177F70() == 6)
    fn_800B2640(4, 1);
}
void PenaltyEnforceKind14(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  if (in->mUnknown14 == 6 && in->mUnknown24 > 0) {
    out->mUnknown10 = 3;
    out->mUnknownC = 15.0f;
    out->mUnknown14 = in->mUnknown24;
  } else {
    out->mUnknown8 = in->mUnknown0;
    out->mUnknown0 = PenaltyMarchOff(out->mUnknown8, 15.0f, in->mUnknown21);
    if (in->mUnknown14 == 6)
      out->mUnknown10 = 1;
    else
      out->mUnknown10 = 2;
    out->mUnknown14 = 0;
  }
  out->mUnknown15 = fn_80178348();
  if (fn_80177F70() == 6)
    fn_800B2640(4, 1);
}
void PenaltyEnforceKind17(PenaltySituation_t *in, PenaltyOutcome_t *out) {
  if (fn_801784E8())
    in->mUnknown0 = -in->mUnknown0;
  int special = fn_801783AC(3);
  if (special)
    in->mUnknown8 = fn_8017827C().mY;
  else if (in->mUnknown20 == fn_80178308() && out->mUnknown15 != in->mUnknown20)
    in->mUnknown8 = -in->mUnknown8;
  float distance = fabsf(in->mUnknown0 - in->mUnknown8);
  if (!(distance >= 20.0f)) {
    if ((special || !(distance >= 10.0f)) && !fn_801783AC(17)) {
      out->mUnknown8 = in->mUnknown0;
      out->mUnknown10 = 3;
      out->mUnknown15 ^= 1;
      if (special)
        out->mUnknown0 = -(in->mUnknown0 + 5.0f);
      else {
        if (fn_801784E8())
          in->mUnknown0 = -in->mUnknown0;
        out->mUnknown0 = in->mUnknown0 - 5.0f;
      }
      fn_801783D0(17, 1);
    } else {
      out->mUnknown0 = in->mUnknown8;
      out->mUnknown10 = 2;
    }
  } else {
    out->mUnknown10 = 2;
    float spot = in->mUnknown0 - 30.0f;
    out->mUnknown0 = spot;
    if (!(in->mUnknown8 <= spot))
      out->mUnknown0 = in->mUnknown8;
    if (in->mUnknown20 == fn_80178308() && out->mUnknown15 != in->mUnknown20)
      out->mUnknown0 = -out->mUnknown0;
  }
}
int PenaltyCanFoulInState(Object_80039F5C *player) {
  int result = 0;
  switch (player->mpState->mId) {
  case 24:
    if ((unsigned char)player->mUnknown361[24] == 3)
      result = 1;
    else if (fn_802372EC(0, 15) < (unsigned int)fn_800B2600())
      result = 1;
    break;
  case 2:
  case 22:
  case 40:
  case 92:
    if (player->mFlags & 0x400)
      result = 1;
    break;
  case 67:
    result = 1;
    break;
  }
  return result;
}
void PenaltyPickInterferenceByFacing(Object_80039F5C *a, float valueA, int angleA,
                 Object_80039F5C *b, float valueB, int angleB, void *context) {
  int selected = 0;
  float normalized = 0.0f;
  int limit;
  int flag;
  if (a->mUnknown8 != 255 && (a->mFlags & 0x4000)) {
    normalized = (valueA - 4.0f) * 0.16666667f;
    unsigned int span = 30;
    unsigned int base = 35;
    unsigned int count = _PenaltyClamp<unsigned int>(
        (unsigned int)(normalized * (float)span + (float)base), 35, 65);
    limit = (int)((float)count * 46603.379f);
    flag = 0;
  } else {
    limit = 0x38E38E;
    flag = 1;
  }
  if ((a->mUnknown512.mUnknown0 == 0.0f && !flag) ||
      MathAngleDiff(a->mUnknown512.mUnknown4, angleA) > limit) {
    if (!(valueA > valueB) && !PenaltyIsPlayingBall(a, b, context) &&
        a->mpState->mId != 28) {
      PenaltyCallInterference(3, a, b);
      selected = 1;
    }
  }
  if (!selected) {
    if (b->mUnknown8 != 255 && (b->mFlags & 0x4000)) {
      limit = 0x18E38E;
      flag = 0;
    } else {
      limit = 0x38E38E;
      flag = 1;
    }
    if (b->mUnknown512.mUnknown0 == 0.0f ||
        (!(b->mUnknown512.mUnknown0 >= 0.5f) && !flag) ||
        MathAngleDiff(b->mUnknown512.mUnknown4, angleB) > limit) {
      if (!(valueB > valueA) && !PenaltyIsPlayingBall(b, a, context) &&
          b->mpState->mId != 28)
        PenaltyCallInterference(4, b, a);
    }
  }
}
void PenaltyApplyFrequency(float *value, int type, float target) {
  float scale = fn_800B2618(type), factor = scale * 1.9800001f;
  if (scale == 0.0f)
    *value = 0.0f;
  else if (!(scale >= 0.5050505f))
    *value *= factor;
  else if (!(scale <= 0.5050505f) && !(*value >= target)) {
    if (type == 1) {
      float amount = (factor - 1.0f) * 0.4f;
      *value = (target - *value) * amount + *value;
    } else
      *value = (target - *value) * (factor - 1.0f) + *value;
  }
}
float PenaltyGetBaseRate(unsigned char type) {
  float value = 1.0f;
  switch (type) {
  case 2:
  case 4:
  case 6:
  case 8:
  case 9:
  case 10:
    value = 0.1f;
    break;
  case 0:
  case 1:
  case 3:
  case 5:
  case 7:
    value = 0.25f;
    break;
  default:
    value = 1.0f;
    break;
  }
  return value;
}
float PenaltyApplyCallCount(float value) {
  int count = fn_800B2600();
  if (count > 0) {
    float decrease = value * 0.1f;
    value -= decrease * (float)count;
  }
  return value;
}
float PenaltyApplyAngleFactor(float value, Object_80039F5C *a, Object_80039F5C *b) {
  float adjusted = value;
  if (MathAngleDiff(a->mMotion.mUnknown32, b->mMotion.mUnknown32) <= 0x200000)
    adjusted *= 0.8f;
  if (MathAngleDiff(a->mMotion.mUnknown32, b->mMotion.mUnknown32) > 0x5FFFFF)
    adjusted = value * 1.25f;
  return adjusted;
}
int PenaltySkipInterference(Ball_t *ball, Object_80039F5C *player) {
  int reject = 0;
  if (fn_800AD9B4() != 3)
    reject = 1;
  if (!reject && ball && BallStateGet(ball, 0) != 4)
    reject = 1;
  if (!reject && !player)
    reject = 1;
  if (!reject && !(player->mMotion.mPos.mY > fn_80177FE0().mY + 5.0f))
    reject = 1;
  if (!reject && fn_801783AC(11) == 1)
    reject = 1;
  if (!reject && fn_801783AC(12) == 1)
    reject = 1;
  if (!reject && fn_8013AD94(ball) != 1)
    reject = 1;
  if (!reject && fn_80177C38())
    reject = 1;
  return reject;
}
int PenaltySkipInterferenceAt(Object_80039F5C *a, Object_80039F5C *b, Vector_80039F5C point) {
  int reject = 0;
  if (!a || !b)
    reject = 1;
  if (!reject && a->mIdBytes[2] == b->mIdBytes[2])
    reject = 1;
  if (!reject && !(fabsf(point.mX) < fn_80178A08() + 2.0f))
    reject = 1;
  return reject;
}
int PenaltyIsPlayingBall(Object_80039F5C *a, Object_80039F5C *b, void *) {
  Point2_t toPlayer, fromPlayer, toBall;
  fn_80227690(&toPlayer, &b->mMotion.mPos, &a->mMotion.mPos);
  int toward = fn_801CFE40(toPlayer.mY, toPlayer.mX);
  fn_80227690(&fromPlayer, &a->mMotion.mPos, &b->mMotion.mPos);
  int away = fn_801CFE40(fromPlayer.mY, fromPlayer.mX);
  Vector_80039F5C point;
  BallGetLandingPoint(BallGetCurrent(), &point);
  point.mZ = 0.0f;
  int reject = 0;
  if (MathAngleDiff(toward, a->mMotion.mUnknown32) <= 0x2AAAA9)
    reject = MathAngleDiff(toward, a->mMotion.mFacing) <= 0x2AAAA9;
  if (!reject) {
    float speed = b->mUnknown504;
    if (!(speed >= gPlyrMoveFwdSpeed * 0.14f) && b->mUnknown512.mUnknown0 == 0.0f)
      reject = 1;
    if (!reject) {
      if (b->mpState->mId == 28) {
        PenaltyRouteView_t *state = (PenaltyRouteView_t *)&b->mUnknown336;
        if (state->mUnknown0 < state->mUnknown10) {
          point.mX = state->mUnknown4.mX;
          point.mY = state->mUnknown4.mY;
        }
      }
      fn_80227690(&toBall, &point, &b->mMotion.mPos);
      int direction = fn_801CFE40(toBall.mY, toBall.mX);
      if (MathAngleDiff(away, direction) > 0x200000)
        reject = 1;
    }
  }
  return reject;
}
int PenaltyHasInterferenceContact(Object_80039F5C *a, Object_80039F5C *b) {
  int result = 0;
  float value = 1.0f;
  if (a && b) {
    PenaltyContactView_t *block = (PenaltyContactView_t *)&a->mUnknown560;
    if (block && block->mUnknown0 && block->mUnknown35) {
      value = PenaltyApplyCallCount(PenaltyApplyAngleFactor(PenaltyGetBaseRate(block->mUnknown36), a, b));
      value = !(value < 0.00001f) ? (value <= 1.0f ? value : 1.0f) : 0.00001f;
      fn_800B260C((short)(fn_800B2600() + 1));
      float limit = value * 100621.12f;
      if (!(block->mUnknown20 <= gPlyrMoveFwdSpeed * limit))
        result = 1;
    }
  }
  return result;
}
void PenaltyCallInterference(int type, Object_80039F5C *a, Object_80039F5C *b) {
  float value = 0.0f;
  if (a && b) {
    value = 0.25f;
    PenaltyApplyFrequency(&value, type, 1.0f);
    PenaltyApplyDiscipline(&value, a, 9);
    fn_800B2370(a, 9, b, value);
  }
}
void PenaltyPickInterferenceNear(Object_80039F5C *a, Object_80039F5C *b, float valueB,
                 Vector_80039F5C *point, float valueA) {
  if (!(point->mY >= a->mMotion.mPos.mY)) {
    if (!(valueB >= valueA) && PenaltyCanFoulInState(b)) {
      if (!PenaltyIsPlayingBall(b, a, point))
        PenaltyCallInterference(4, b, a);
    } else if (!(valueA >= valueB) && PenaltyCanFoulInState(a)) {
      if (!PenaltyIsPlayingBall(a, b, point))
        PenaltyCallInterference(3, a, b);
    }
  }
}
void PenaltyPickInterferenceFar(Object_80039F5C *a, Object_80039F5C *b, float valueA,
                 Vector_80039F5C *point, float valueB, int angleA, int angleB) {
  if (!(valueA >= valueB) && PenaltyCanFoulInState(b)) {
    if (!PenaltyIsPlayingBall(b, a, point))
      PenaltyCallInterference(4, b, a);
    return;
  }
  if (!(valueB >= valueA) && PenaltyCanFoulInState(a)) {
    if (!PenaltyIsPlayingBall(a, b, point))
      PenaltyCallInterference(3, a, b);
    return;
  }
  PenaltyPickInterferenceByFacing(a, valueA, angleA, b, valueB, angleB, point);
}
float PenaltyCalcLineToGain(float value) {
  if (value >= fn_80178A2C() - 10.0f)
    return fn_80178A2C();
  return value + 10.0f;
}
int PenaltyNextDown(int value) {
  switch (value) {
  case 0:
    return 1;
  case 6:
    return 0;
  case 1:
  case 2:
  case 3:
  case 4:
    return value + 1;
  case 5:
    return 7;
  }
  return 1;
}
int PenaltyResolveEvents(Entry_800B206C *events, unsigned char count, unsigned char *result) {
  int ret;
  *result = 0;
  switch (count) {
  case 1:
    ret = 1;
    *result = ret;
    break;
  case 2:
    SortArray(0, events, 2, 36, PenaltyCompareEvents, 0, 0, 1);
    if (events[1].mUnknown1C == 0)
      PenaltyResolvePair(events, 2, result);
    else if (events[0].mUnknown1C == 1)
      PenaltyResolvePairKind1First(events, 2, result);
    else
      PenaltyResolvePairOther(events, 2, result);
  default:
    ret = -1;
    break;
  }
  return ret;
}
void PenaltyEnforce(int type, PenaltySituation_t *in, PenaltyOutcome_t *out) {
  PenaltySetupOutcome(in, out);
  _Penalty_aKindInfo[type].mUnknown8(in, out);
  int mode = fn_8009D86C(), option = fn_8009D990(1);
  if ((mode == 2 || mode == 4 || mode == 5) && !option &&
      !(out->mUnknownC <= 0.0f)) {
    out->mUnknownC = 0.0f;
    ClockRuleSetFlags(256);
  }
  if (_Penalty_aKindInfo[type].mUnknown4 & 16)
    fn_800B2640(4, 1);
  if ((_Penalty_aKindInfo[type].mUnknown4 & 32) && fn_80178308() == fn_80178348())
    fn_800B2640(4, 1);
}
unsigned int PenaltyGetKindFlags(int type) { return _Penalty_aKindInfo[type].mUnknown4; }
void PenaltyCheckDefenderContact(Object_80039F5C *player);
void PenaltyCheckAllPlayers(void) {
  for (unsigned char team = 0; team <= 1; team++) {
    unsigned int count = fn_80178D18(team);
    for (unsigned short i = 0; i < count; i++)
      PenaltyCheckDefenderContact(fn_80039F5C(team, i));
  }
}
void PenaltyCheckOffside(void) {
  Point_8017886C line;
  line = fn_80177FE0();
  unsigned int count = fn_80178D18(fn_80178320());
  for (unsigned short i = 0; i < count; i++) {
    Object_80039F5C *player = fn_80039F5C(fn_80178320(), i);
    if (!(player->mMotion.mPos.mY >= line.mY + 3.0f)) {
      if (!(player->mMotion.mPos.mY >= line.mY + 0.15625f)) {
        fn_800B2370(player, 2, 0, 1.0f);
        return;
      }
      for (unsigned short j = 0; j <= 4; j++) {
        Vector_80039F5C pos, dir;
        int joint =
            CharSkelGetJointByName(player->mpUnknown4->mpUnknown100, gPossJointNames[j]);
        fn_8009BF5C(player, joint, &pos, &dir);
        if (!(pos.mY >= line.mY + 0.15625f)) {
          fn_800B2370(player, 2, 0, 1.0f);
          return;
        }
      }
    }
  }
}
void PenaltyCheckDefenderContact(Object_80039F5C *player) {
  int mode = fn_800AD9B4();
  int live = fn_80177F70();
  if (mode != 2 || !live || BallStateGet(BallGetCurrent(), 0) != 6)
    return;
  int team = fn_80178320();
  if (player->mIdBytes[2] == team && player->mUnknown560.mFlags.mBytes[0] &&
      player->mUnknown560.mUnknown53) {
    if (fn_800BA6F8())
      fn_80178370();
    else
      fn_800B2370(player, 3, 0, 1.0f);
  }
}
void PenaltyCheckOffenseKind1(void) {
  Ball_t *ball = BallGetCurrent();
  int state = 0;
  if (ball)
    state = BallStateGet(ball, 0);
  if (fn_80177F70() && state != 6)
    fn_800B2370(fn_80039F5C(fn_80178308(), 0), 1, 0, 1.0f);
}
void PenaltyCheckGrounding(Object_80039F5C *player) {
  if (fn_800B2618(8) <= 0.0f)
    return;
  Point_8017886C line;
  line = fn_80177FE0();
  Vector_80039F5C ball;
  if (!BallGetLandingPoint(BallGetCurrent(), &ball))
    return;
  if (player->mFlags & 0x8000) {
    if (!(ball.mY >= line.mY - 4.0f))
      fn_800B2370(player, 11, 0, 1.0f);
    return;
  }
  int near = 0;
  for (unsigned char i = 0; i <= 2; i++) {
    Point2_t delta;
    unsigned short index = PlayBookGetReceiver(player->mIdBytes[2], i, 0);
    fn_80227690(&delta,
                &fn_80039F5C(player->mIdBytes[2], index)->mMotion.mPos,
                &ball);
    if (fn_802270A4(&delta) < 4.0f) {
      near = 1;
      break;
    }
  }
  if (!near)
    fn_800B2370(player, 11, 0, 1.0f);
}
void PenaltyCheckPassInterference(void) {
  Ball_t *ball = BallGetCurrent();
  Object_80039F5C *carrier = 0;
  if (ball)
    carrier = BallGetTarget(ball);
  if (PenaltySkipInterference(ball, carrier))
    return;
  Object_80039F5C *tackler = fn_8009BCE8(&carrier->mUnknown560.mUnknown40);
  if (!PenaltyHasInterferenceContact(carrier, tackler))
    return;
  Vector_80039F5C pos, ballPos;
  BallGetLandingPoint(ball, &pos);
  BallGetPosition(ball, &ballPos);
  if (PenaltySkipInterferenceAt(carrier, tackler, pos))
    return;
  Point2_t delta;
  fn_80227690(&delta, &pos, &carrier->mMotion.mPos);
  float carrierDistance = fn_802270A4(&delta);
  int carrierAngle = fn_801CFE40(delta.mY, delta.mX);
  fn_80227690(&delta, &pos, &tackler->mMotion.mPos);
  float tacklerDistance = fn_802270A4(&delta);
  int tacklerAngle = fn_801CFE40(delta.mY, delta.mX);
  if (!(carrierDistance >= 4.0f))
    PenaltyPickInterferenceNear(carrier, tackler, carrierDistance, &ballPos,
                tacklerDistance);
  else
    PenaltyPickInterferenceFar(carrier, tackler, carrierDistance, &ballPos,
                tacklerDistance, carrierAngle, tacklerAngle);
}
void PenaltyRollPassPlayFoul(Object_80039F5C *player) {
  if (fn_800AD9B4() != 3)
    return;
  float chance = 450.0f;
  PenaltyApplyFrequency(&chance, 0, 10000.0f);
  if (fn_802372EC(0, 10000) < (unsigned int)chance)
    fn_800B2370(player, 0, 0, 1.0f);
}
int PenaltyRollFacemask(void) {
  float chance = 2000.0f;
  PenaltyApplyFrequency(&chance, 2, 10000.0f);
  if (!fn_801787A0() && (float)fn_802372EC(0, 10000) < chance)
    return 1;
  return 0;
}
void PenaltyRollRoughing(Object_80039F5C *player) {
  if (fn_800AD9B4() != 3 || BallFindHeldBy(player))
    return;
  float chance = 75.0f;
  PenaltyApplyFrequency(&chance, 9, 100.0f);
  PenaltyApplyDiscipline(&chance, player, 9);
  if (!((float)fn_802372EC(0, 100) >= chance))
    fn_800B2370(player, 12, 0, 1.0f);
}
int PenaltyRollTackleFoul(void) {
  float chance = 2300.0f;
  PenaltyApplyFrequency(&chance, 0, 10000.0f);
  if (fn_800AD9B4() == 3 && (float)fn_802372EC(0, 10000) < chance)
    return 1;
  return 0;
}
}
