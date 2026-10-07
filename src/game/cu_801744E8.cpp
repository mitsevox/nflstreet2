#include "game/Object_80039F5C.h"
#include "game/Pair_8017055C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_802372EC.h"
#include <math.h>
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
struct Event_801744E8 {
  int mUnknown0;
  unsigned short mUnknown4;
  unsigned char mUnknown6, mUnknown7;
  unsigned int mUnknown8, mUnknownC, mUnknown10;
  int mUnknown14;
  unsigned int mUnknown18, mUnknown1C, mUnknown20;
};
struct Table_801744E8 {
  unsigned short mUnknown0, mUnknown2;
  unsigned int mUnknown4;
  void (*mUnknown8)(Input_80174868 *, Output_80174868 *);
};
struct State_80175E3C {
  unsigned short mUnknown0;
  unsigned char mUnknown2[2];
  Pair_8017055C mUnknown4;
  unsigned char mUnknownC[4];
  unsigned int mUnknown10;
};
struct Block_80175FC8 {
  unsigned char mUnknown0;
  unsigned char mUnknown1[31];
  float mUnknown20;
  unsigned char mUnknown24[17];
  unsigned char mUnknown35, mUnknown36;
};
extern "C" {
extern Table_801744E8 lbl_802E9A04[];
extern float lbl_803ECB08;
int fn_80178308(void);
int fn_80178320(void);
int fn_80178348(void);
int fn_801783AC(int);
void fn_801783D0(int, int);
float fn_80178A2C(void);
float fn_80178A08(void);
int fn_80177F70(void);
int fn_801784E8(void);
Pair_8017055C fn_80177FE0(void);
Pair_8017055C fn_8017827C(void);
void fn_80174204(Input_80174868 *, Output_80174868 *, int, float);
void fn_800B2640(int, int);
int fn_800B2600(void);
void fn_800B260C(short);
float fn_800B2618(int);
int fn_801CFE40(float, float);
int fn_801CFFD0(int, int);
void fn_80227690(void *, void *, void *);
int fn_8013BA58(void *, int *);
int fn_8013AD94(void *);
int fn_80177C38(void);
void fn_8017419C(float *, Object_80039F5C *, int);
void fn_800B2370(Object_80039F5C *, int, Object_80039F5C *, float);
int fn_8009D86C(void);
int fn_8009D990(int);
void fn_801735B4(unsigned int);
void fn_801F51DC(int, void *, int, int,
                 int (*)(Event_801744E8 *, Event_801744E8 *), int, int, int);
int fn_80175E3C(Object_80039F5C *, Object_80039F5C *, void *);
void fn_801760B4(int, Object_80039F5C *, Object_80039F5C *);
void fn_8017419C(float *value, Object_80039F5C *, int) {
  unsigned int factor = 127;
  float normalized = (float)factor * 0.003921568859368563f;
  *value *= (float)(1.2000000476837158 - (double)normalized * 0.4);
}
float fn_80174750(int, float, float);
void fn_80174204(Input_80174868 *in, Output_80174868 *out, int type,
                 float value) {
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
    out->mUnknown0 = -fn_80174750(0, in->mUnknown8, value);
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
      if (in->mUnknown24 == 6 || in->mUnknown24 == 9) {
        out->mUnknown8 = fn_80178A2C() - 5.0f;
        out->mUnknown0 = fn_80174750(0, out->mUnknown8, value);
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
        out->mUnknown10 = 3;
        out->mUnknownC = value;
      } else {
        out->mUnknown14 = 0;
        out->mUnknown10 = 1;
      }
    } else if (!type && !(out->mUnknown0 >= in->mUnknownC)) {
      out->mUnknown10 = type;
    } else
      out->mUnknown10 = 2;
    return;
  }
  if (team != fn_80178308() && in->mUnknown21 == 1 &&
      in->mUnknown20 == fn_80178308()) {
    out->mUnknown14 = 0;
    out->mUnknown10 = 0;
    out->mUnknown15 ^= 1;
    return;
  }
  if (in->mUnknown14 == 6) {
    if (in->mUnknown24 > 0) {
      out->mUnknown14 = in->mUnknown24;
      out->mUnknown10 = 3;
      out->mUnknownC = value;
    } else {
      out->mUnknown14 = 0;
      out->mUnknown10 = 1;
    }
    return;
  }
  if (!(out->mUnknown0 < in->mUnknownC)) {
    if (in->mUnknown24 > 0)
      out->mUnknown14 = in->mUnknown24;
    out->mUnknown10 = 2;
    return;
  }
  if (in->mUnknown24 > 0)
    out->mUnknown14 = in->mUnknown24;
  out->mUnknown10 = type ? 2 : type;
}

int fn_801744E8(Event_801744E8 *events, int, unsigned char *result) {
  *result = 0;
  int team = events[0].mUnknown6, other = events[1].mUnknown6;
  unsigned short a = team == fn_80178308()
                         ? lbl_802E9A04[events[0].mUnknown0].mUnknown0
                         : lbl_802E9A04[events[0].mUnknown0].mUnknown2;
  unsigned short b = other == fn_80178308()
                         ? lbl_802E9A04[events[1].mUnknown0].mUnknown0
                         : lbl_802E9A04[events[1].mUnknown0].mUnknown2;
  if (team == other) {
    if (a == 15 && b == 5) {
      *result = 1;
      return 1;
    }
    if (a == 5 && b == 15) {
      *result = 1;
      Event_801744E8 temp = events[0];
      events[0] = events[1];
      events[1] = temp;
      return 1;
    }
    return 0;
  }
  *result = 2;
  return 1;
}
int fn_80174720(Event_801744E8 *, int, unsigned char *result) {
  *result = 0;
  return -1;
}
int fn_80174730(Event_801744E8 *, int, unsigned char *result) {
  *result = 0;
  return -1;
}
int fn_80174740(Event_801744E8 *a, Event_801744E8 *b) {
  return a->mUnknown14 - b->mUnknown14;
}
float fn_80174750(int direction, float value, float amount) {
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
  if (!(out <= fn_80178A2C()))
    return fn_80178A2C();
  return out;
}
void fn_80174868(Input_80174868 *in, Output_80174868 *out) {
  unsigned char side = fn_80178348();
  if (in->mUnknown22)
    side ^= 1;
  int other = side != fn_80178308();
  unsigned char direction = in->mUnknown21;
  out->mUnknown0 = in->mUnknown0;
  out->mUnknown14 = 0;
  out->mUnknown15 = fn_80178308();
  out->mUnknown10 = (direction && !in->mUnknown22) ? 1 : 2;
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
          out->mUnknown8 = in->mUnknown0;
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
    if (!(in->mUnknown4 >= in->mUnknown0))
      out->mUnknown8 =
          !(in->mUnknown8 <= in->mUnknown4) ? in->mUnknown8 : in->mUnknown4;
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
    out->mUnknown15 ^= 1;
    out->mUnknown8 = in->mUnknown0;
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
        out->mUnknown8 = in->mUnknown0;
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
void fn_80174C24(Input_80174868 *in, Output_80174868 *out) {
  out->mUnknown0 = fn_80174750(in->mUnknown21, out->mUnknown8, 15.0f);
}
void fn_80174C64(Input_80174868 *in, Output_80174868 *out) {
  out->mUnknown0 = fn_80174750(in->mUnknown21, out->mUnknown8, 15.0f);
  if (in->mUnknown14 == 6 && in->mUnknown24 > 0) {
    out->mUnknown10 = 3;
    out->mUnknownC = 15.0f;
    out->mUnknown14 = in->mUnknown24;
    return;
  }
  if (in->mUnknown14 != 6 && in->mUnknown24 > 0) {
    out->mUnknown14 = in->mUnknown24;
    out->mUnknown10 = 2;
  }
  if (in->mUnknown14 == 6)
    out->mUnknown10 = 1;
}
void fn_80174D10(Input_80174868 *in, Output_80174868 *out) {
  out->mUnknown10 = 1;
  out->mUnknown14 = 0;
  out->mUnknown8 = in->mUnknown0;
  out->mUnknown0 = fn_80174750(in->mUnknown21, in->mUnknown0, 5.0f);
}
void fn_80174D64(Input_80174868 *in, Output_80174868 *out) {
  out->mUnknown10 = 1;
  out->mUnknown8 = in->mUnknown0;
  out->mUnknown0 = fn_80174750(in->mUnknown21, in->mUnknown0, 5.0f);
  out->mUnknown14 = 0;
}
void fn_80174DB8(Input_80174868 *in, Output_80174868 *out) {
  if (!(in->mUnknown4 <= out->mUnknown8) && in->mUnknown20 == fn_80178320())
    out->mUnknown8 = in->mUnknown4;
  out->mUnknown0 = fn_80174750(in->mUnknown21, out->mUnknown8, 5.0f);
  fn_80174204(in, out, 0, 5.0f);
}
void fn_80174E3C(Input_80174868 *in, Output_80174868 *out) {
  out->mUnknown0 = fn_80174750(in->mUnknown21, out->mUnknown8, 15.0f);
  fn_80174204(in, out, 1, 15.0f);
}
void fn_80174E94(Input_80174868 *in, Output_80174868 *out) {
  out->mUnknown8 = in->mUnknown8;
  if (!(out->mUnknown8 >= -fn_80178A2C()))
    out->mUnknown8 = -30.0f;
  out->mUnknown0 = fn_80174750(in->mUnknown21, out->mUnknown8, 15.0f);
  out->mUnknown10 = 2;
  out->mUnknown14 = 0;
  if (out->mUnknown15 == in->mUnknown20)
    out->mUnknown15 ^= 1;
  int team = fn_80178308();
  if (team == fn_80178348())
    out->mUnknown0 = -out->mUnknown0;
}
void fn_80174F4C(Input_80174868 *in, Output_80174868 *out) {
  out->mUnknown8 = in->mUnknown8;
  if (!(out->mUnknown8 >= -fn_80178A2C()))
    out->mUnknown8 = -30.0f;
  out->mUnknown0 = fn_80174750(in->mUnknown21, out->mUnknown8, 15.0f);
  out->mUnknown10 = 2;
  out->mUnknown14 = 0;
  if (out->mUnknown15 == in->mUnknown20)
    out->mUnknown15 ^= 1;
}
void fn_80174FE4(Input_80174868 *in, Output_80174868 *out) {
  out->mUnknown8 = in->mUnknown0;
  out->mUnknown0 = fn_80174750(in->mUnknown21, in->mUnknown0, 5.0f);
  out->mUnknown14 = 0;
  out->mUnknown10 = 1;
}
void fn_80175038(Input_80174868 *in, Output_80174868 *out) {
  if (in->mUnknown20 == fn_80178348()) {
    if (in->mUnknown14 == 6) {
      out->mUnknown10 = 3;
      out->mUnknown14 = 0;
    } else {
      out->mUnknown8 = in->mUnknown0;
      out->mUnknown0 = fn_80174750(in->mUnknown21, in->mUnknown0, 10.0f);
      out->mUnknown14 = 0;
      out->mUnknown10 = 1;
    }
    return;
  }
  if (in->mUnknown14 == 6) {
    if (in->mUnknown24 > 0) {
      out->mUnknown14 = in->mUnknown24;
      out->mUnknown10 = 3;
      return;
    }
    out->mUnknown14 = 0;
    out->mUnknown10 = 1;
  } else {
    out->mUnknown10 = 2;
    out->mUnknown8 = in->mUnknown0;
    out->mUnknown14 = 0;
    if (!(in->mUnknown8 >= fn_80178A2C())) {
      out->mUnknown0 = in->mUnknown8;
      return;
    }
  }
  if (!(in->mUnknown0 <= fn_80178A2C() - 2.0f))
    out->mUnknown0 = (fn_80178A2C() - in->mUnknown0) * 0.5f + in->mUnknown0;
  else
    out->mUnknown0 = fn_80178A2C() - 1.0f;
}
void fn_801751C0(Input_80174868 *in, Output_80174868 *out) {
  out->mUnknown0 = fn_80174750(in->mUnknown21, out->mUnknown8, 10.0f);
}
void fn_80175200(Input_80174868 *in, Output_80174868 *out) {
  out->mUnknown10 = in->mUnknown14 == 6 ? 3 : 0;
  out->mUnknown8 = in->mUnknown0;
  if (!(in->mUnknown0 <= in->mUnknown8 + 10.0f))
    out->mUnknown0 = in->mUnknown8;
  else
    out->mUnknown0 = fn_80174750(in->mUnknown21, in->mUnknown0, 10.0f);
  if (in->mUnknown14 != 6) {
    if (!(in->mUnknown8 >= -fn_80178A2C())) {
      out->mUnknown14 = -2;
      out->mUnknown10 = 1;
    } else
      out->mUnknown14 = 0;
  }
}
void fn_801752C0(Input_80174868 *in, Output_80174868 *out) {
  if (in->mUnknown14 == 6 && in->mUnknown24 > 0) {
    out->mUnknown10 = 3;
    out->mUnknownC = 15.0f;
    out->mUnknown14 = in->mUnknown24;
    return;
  }
  out->mUnknown8 =
      (!(in->mUnknown4 <= in->mUnknown0) && fn_80178308() == fn_80178348())
          ? in->mUnknown4
          : in->mUnknown0;
  out->mUnknown0 = fn_80174750(in->mUnknown21, out->mUnknown8, 15.0f);
  out->mUnknown10 = 2;
  out->mUnknown14 = 0;
  if (in->mUnknown14 == 6)
    out->mUnknown10 = 1;
  out->mUnknown15 = fn_80178348();
}
void fn_801753A4(Input_80174868 *in, Output_80174868 *out) {
  out->mUnknown8 = in->mUnknown0;
  out->mUnknown0 = fn_80174750(in->mUnknown21, in->mUnknown0, 5.0f);
  if (in->mUnknown14 != 6)
    out->mUnknown10 = out->mUnknown0 < in->mUnknownC ? 1 : 2;
  else if (in->mUnknown24 > 0) {
    out->mUnknown10 = 3;
    out->mUnknownC = 5.0f;
    out->mUnknown14 = in->mUnknown24;
  } else
    out->mUnknown10 = 1;
  out->mUnknown15 = fn_80178348();
  if (fn_80177F70() == 6)
    fn_800B2640(4, 1);
}
void fn_80175464(Input_80174868 *in, Output_80174868 *out) {
  if (in->mUnknown14 == 6 && in->mUnknown24 > 0) {
    out->mUnknown10 = 3;
    out->mUnknownC = 15.0f;
    out->mUnknown14 = in->mUnknown24;
  } else {
    out->mUnknown8 = in->mUnknown0;
    out->mUnknown0 = fn_80174750(in->mUnknown21, in->mUnknown0, 15.0f);
    out->mUnknown10 = in->mUnknown14 == 6 ? 1 : 2;
    out->mUnknown14 = 0;
  }
  out->mUnknown15 = fn_80178348();
  if (fn_80177F70() == 6)
    fn_800B2640(4, 1);
}
void fn_80175524(Input_80174868 *in, Output_80174868 *out) {
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
      out->mUnknown10 = 3;
      out->mUnknown8 = in->mUnknown0;
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
      out->mUnknown10 = 2;
      out->mUnknown0 = in->mUnknown8;
    }
  } else {
    out->mUnknown10 = 2;
    out->mUnknown0 = in->mUnknown0 - 30.0f;
    if (!(in->mUnknown8 <= in->mUnknown0 - 30.0f))
      out->mUnknown0 = in->mUnknown8;
    if (in->mUnknown20 == fn_80178308() && out->mUnknown15 != in->mUnknown20)
      out->mUnknown0 = -out->mUnknown0;
  }
}
int fn_801756F0(Object_80039F5C *player) {
  switch (player->mpState->mId) {
  case 24:
    if ((unsigned char)player->mUnknown361[24] == 3)
      return 1;
    {
      unsigned int value = fn_802372EC(0, 15);
      return value < (unsigned int)fn_800B2600();
    }
  case 67:
    return 1;
  case 2:
  case 22:
  case 40:
  case 92:
    return (player->mFlags & 0x400) != 0;
  }
  return 0;
}
void fn_801757A4(Object_80039F5C *a, int angleA, Object_80039F5C *b, int angleB,
                 void *context, float valueA, float valueB) {
  int selected = 0;
  int zeroState = a->mUnknown512.mUnknown0 == 0.0f;
  int limit;
  int flag;
  if (a->mUnknown8 != 255 && (a->mFlags & 0x4000)) {
    float normalized = (valueA - 4.0f) * 0.16666667f;
    unsigned int span = 30;
    unsigned int base = 35;
    unsigned int count = (unsigned int)(normalized * (float)span + (float)base);
    if (count < 35)
      count = 35;
    else if (count > 65)
      count = 65;
    limit = (int)((float)count * 46603.379f);
    flag = 0;
  } else {
    limit = 0x38E38E;
    flag = 1;
  }
  if ((zeroState && !flag) ||
      fn_801CFFD0(a->mUnknown512.mUnknown4, angleA) > limit) {
    if (!(valueA > valueB) && !fn_80175E3C(a, b, context) &&
        a->mpState->mId != 28) {
      selected = 1;
      fn_801760B4(3, a, b);
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
        fn_801CFFD0(b->mUnknown512.mUnknown4, angleB) > limit) {
      if (!(valueB > valueA) && !fn_80175E3C(b, a, context) &&
          b->mpState->mId != 28)
        fn_801760B4(4, b, a);
    }
  }
}
void fn_80175A40(float *value, int type, float target) {
  float scale = fn_800B2618(type), factor = scale * 1.9800001f;
  if (scale == 0.0f)
    *value = 0.0f;
  else if (!(scale >= 0.5050505f))
    *value *= factor;
  else if (!(scale <= 0.5050505f) && !(*value >= target)) {
    float amount = factor - 1.0f;
    if (type == 1)
      amount *= 0.4f;
    *value = (target - *value) * amount + *value;
  }
}
float fn_80175B18(int type) {
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
  }
  return value;
}
float fn_80175B88(float value) {
  int count = fn_800B2600();
  if (count > 0) {
    float decrease = value * 0.1f;
    value -= decrease * (float)count;
  }
  return value;
}
float fn_80175BF8(Object_80039F5C *a, Object_80039F5C *b, float value) {
  float adjusted = value;
  if (fn_801CFFD0(a->mMotion.mUnknown32, b->mMotion.mUnknown32) <= 0x200000)
    adjusted *= 0.8f;
  if (fn_801CFFD0(a->mMotion.mUnknown32, b->mMotion.mUnknown32) > 0x5FFFFF)
    adjusted = value * 1.25f;
  return adjusted;
}
int fn_80175C8C(void *ball, Object_80039F5C *player) {
  if (fn_800AD9B4() != 3)
    return 1;
  if (ball && fn_8013BA58(ball, 0) != 4)
    return 1;
  if (!player)
    return 1;
  if (!(player->mMotion.mPos.mY > fn_80177FE0().mY + 5.0f))
    return 1;
  if (fn_801783AC(11) == 1)
    return 1;
  if (fn_801783AC(12) == 1)
    return 1;
  if (fn_8013AD94(ball) != 1)
    return 1;
  if (fn_80177C38())
    return 1;
  return 0;
}
int fn_80175DAC(Object_80039F5C *a, Object_80039F5C *b, Pair_8017055C *point) {
  if (!a || !b)
    return 1;
  if (a->mIdBytes[2] == b->mIdBytes[2])
    return 1;
  float value = fabsf(point->mX);
  return !(value < fn_80178A08() + 2.0f);
}
int fn_80175E3C(Object_80039F5C *a, Object_80039F5C *b, void *) {
  Pair_8017055C delta;
  fn_80227690(&delta, &b->mMotion.mPos, &a->mMotion.mPos);
  int toward = fn_801CFE40(delta.mY, delta.mX);
  fn_80227690(&delta, &a->mMotion.mPos, &b->mMotion.mPos);
  int away = fn_801CFE40(delta.mY, delta.mX);
  Vector_80039F5C point;
  fn_80138064(fn_801374BC(), &point);
  point.mZ = 0.0f;
  int reject = 0;
  if (fn_801CFFD0(toward, a->mMotion.mUnknown32) <= 0x2AAAA9)
    reject = fn_801CFFD0(toward, a->mMotion.mFacing) <= 0x2AAAA9;
  if (!reject) {
    struct View {
      unsigned char pad[16];
      float value;
    };
    float speed = ((View *)b->mUnknown488)->value;
    if (!(speed >= lbl_803ECB08 * 0.14f) && b->mUnknown512.mUnknown0 == 0.0f)
      reject = 1;
    if (!reject) {
      if (b->mpState->mId == 28) {
        State_80175E3C *state = (State_80175E3C *)&b->mUnknown336;
        if (state->mUnknown0 < state->mUnknown10) {
          point.mX = state->mUnknown4.mX;
          point.mY = state->mUnknown4.mY;
        }
      }
      fn_80227690(&delta, &point, &b->mMotion.mPos);
      int direction = fn_801CFE40(delta.mY, delta.mX);
      if (fn_801CFFD0(away, direction) > 0x200000)
        reject = 1;
    }
  }
  return reject;
}
int fn_80175FC8(Object_80039F5C *a, Object_80039F5C *b) {
  if (!a || !b)
    return 0;
  Block_80175FC8 *block = (Block_80175FC8 *)&a->mUnknown560;
  if (!block || !block->mUnknown0 || !block->mUnknown35)
    return 0;
  float value = fn_80175B88(fn_80175BF8(a, b, fn_80175B18(block->mUnknown36)));
  if (value < 0.00001f)
    value = 0.00001f;
  else if (!(value <= 1.0f))
    value = 1.0f;
  fn_800B260C((short)(fn_800B2600() + 1));
  return !(block->mUnknown20 <= lbl_803ECB08 * (value * 100621.12f));
}
void fn_801760B4(int type, Object_80039F5C *a, Object_80039F5C *b) {
  float value = 0.0f;
  if (a && b) {
    value = 0.25f;
    fn_80175A40(&value, type, 1.0f);
    fn_8017419C(&value, a, 9);
    fn_800B2370(a, 9, b, value);
  }
}
void fn_80176140(Object_80039F5C *a, Object_80039F5C *b, Pair_8017055C *point,
                 float valueB, float valueA) {
  if (!(point->mY >= a->mMotion.mPos.mY)) {
    if (!(valueB >= valueA) && fn_801756F0(b)) {
      if (!fn_80175E3C(b, a, point))
        fn_801760B4(4, b, a);
    } else if (!(valueA >= valueB) && fn_801756F0(a)) {
      if (!fn_80175E3C(a, b, point))
        fn_801760B4(3, a, b);
    }
  }
}
void fn_80176228(Object_80039F5C *a, Object_80039F5C *b, Pair_8017055C *point,
                 int angleA, int angleB, float valueA, float valueB) {
  if (!(valueA >= valueB) && fn_801756F0(b)) {
    if (!fn_80175E3C(b, a, point))
      fn_801760B4(4, b, a);
    return;
  }
  if (!(valueB >= valueA) && fn_801756F0(a)) {
    if (!fn_80175E3C(a, b, point))
      fn_801760B4(3, a, b);
    return;
  }
  fn_801757A4(a, angleA, b, angleB, point, valueA, valueB);
}
float fn_80176328(float value) {
  float limit = fn_80178A2C();
  if (!(value >= limit - 10.0f))
    return value + 10.0f;
  return fn_80178A2C();
}
int fn_80176378(int value) {
  switch (value) {
  case 0:
    return 1;
  case 1:
  case 2:
  case 3:
  case 4:
    return value + 1;
  case 5:
    return 7;
  case 6:
    return 0;
  }
  return 1;
}
int fn_801763D0(Event_801744E8 *events, int count, unsigned char *result) {
  *result = 0;
  switch (count) {
  case 1:
    *result = 1;
    return 1;
  case 2:
    fn_801F51DC(0, events, 2, 36, fn_80174740, 0, 0, 1);
    if (events[1].mUnknown1C == 0)
      fn_801744E8(events, 2, result);
    else if (events[0].mUnknown1C == 1)
      fn_80174730(events, 2, result);
    else
      fn_80174720(events, 2, result);
  }
  return -1;
}
void fn_801764A0(int type, Input_80174868 *in, Output_80174868 *out) {
  fn_80174868(in, out);
  lbl_802E9A04[type].mUnknown8(in, out);
  int mode = fn_8009D86C(), option = fn_8009D990(1);
  if ((mode == 2 || mode == 4 || mode == 5) && !option &&
      !(out->mUnknownC <= 0.0f)) {
    out->mUnknownC = 0.0f;
    fn_801735B4(256);
  }
  if (lbl_802E9A04[type].mUnknown4 & 16)
    fn_800B2640(4, 1);
  if ((lbl_802E9A04[type].mUnknown4 & 32) && fn_80178308() == fn_80178348())
    fn_800B2640(4, 1);
}
unsigned int fn_801765A8(int type) { return lbl_802E9A04[type].mUnknown4; }
}
