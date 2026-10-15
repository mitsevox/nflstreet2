/* Partial source for the runtime range 0x8025E148-0x8025FBD4 (neutral file name). */

#include <string.h>

typedef int SItype __attribute__ ((mode (SI)));
typedef unsigned int USItype __attribute__ ((mode (SI)));
typedef int DItype __attribute__ ((mode (DI)));
typedef unsigned int UDItype __attribute__ ((mode (DI)));
typedef float SFtype __attribute__ ((mode (SF)));
typedef float DFtype __attribute__ ((mode (DF)));
typedef int word_type __attribute__ ((mode (__word__)));

#define BITS_PER_UNIT 8
#define WORD_SIZE (sizeof (SItype) * BITS_PER_UNIT)
#define HIGH_HALFWORD_COEFF (((UDItype) 1) << (WORD_SIZE / 2))
#define HIGH_WORD_COEFF (((UDItype) 1) << WORD_SIZE)

struct DIstruct {SItype high, low;};

typedef union
{
  struct DIstruct s;
  DItype ll;
} DIunion;

typedef void (*func_ptr) (void);

typedef struct Context_8025FB68
{
  char mUnknown0[4];
  void **mUnknown4;
  char mUnknown8[8];
} Context_8025FB68;

extern func_ptr lbl_80289A20[];
extern void fn_8023E88C (void) __attribute__ ((__noreturn__));

void fn_8025FB08 (void);

void
fn_8025E148 (void)
{
  unsigned long nptrs = (unsigned long) lbl_80289A20[0];
  unsigned i;

  if (nptrs == (unsigned long) -1)
    for (nptrs = 0; lbl_80289A20[nptrs + 1] != 0; nptrs++);

  for (i = nptrs; i >= 1; i--)
    lbl_80289A20[i] ();
}

void
__main (void)
{
  static int initialized;
  if (! initialized)
    {
      initialized = 1;
      fn_8025E148 ();
    }
}

DItype
__ashldi3 (DItype u, word_type b)
{
  DIunion w;
  word_type bm;
  DIunion uu;

  if (b == 0)
    return u;

  uu.ll = u;

  bm = (sizeof (SItype) * BITS_PER_UNIT) - b;
  if (bm <= 0)
    {
      w.s.low = 0;
      w.s.high = (USItype) uu.s.low << -bm;
    }
  else
    {
      USItype carries = (USItype) uu.s.low >> bm;
      w.s.low = (USItype) uu.s.low << b;
      w.s.high = ((USItype) uu.s.high << b) | carries;
    }

  return w.ll;
}

DItype
__ashrdi3 (DItype u, word_type b)
{
  DIunion w;
  word_type bm;
  DIunion uu;

  if (b == 0)
    return u;

  uu.ll = u;

  bm = (sizeof (SItype) * BITS_PER_UNIT) - b;
  if (bm <= 0)
    {
      w.s.high = uu.s.high >> (sizeof (SItype) * BITS_PER_UNIT - 1);
      w.s.low = uu.s.high >> -bm;
    }
  else
    {
      USItype carries = (USItype) uu.s.high << bm;
      w.s.high = uu.s.high >> b;
      w.s.low = ((USItype) uu.s.low >> b) | carries;
    }

  return w.ll;
}

UDItype
__fixunssfdi (SFtype original_a)
{
  DFtype a = original_a;
  DFtype b;
  UDItype v;

  if (a < 0)
    return 0;

  b = (a / HIGH_WORD_COEFF);
  v = (USItype) b;
  v <<= WORD_SIZE;
  a -= (DFtype) v;
  if (a < 0)
    v -= (USItype) (- a);
  else
    v += (USItype) a;
  return v;
}

DFtype
__floatdidf (DItype u)
{
  DFtype d;

  d = (SItype) (u >> WORD_SIZE);
  d *= HIGH_HALFWORD_COEFF;
  d *= HIGH_HALFWORD_COEFF;
  d += (USItype) (u & (HIGH_WORD_COEFF - 1));

  return d;
}

#define DI_SIZE (sizeof (DItype) * BITS_PER_UNIT)
#define DF_SIZE 53
#define SF_SIZE 24

SFtype
__floatdisf (DItype u)
{
  DFtype f;

  if (DF_SIZE < DI_SIZE
      && DF_SIZE > (DI_SIZE - DF_SIZE + SF_SIZE))
    {
#define REP_BIT ((USItype) 1 << (DI_SIZE - DF_SIZE))
      if (! (- ((DItype) 1 << DF_SIZE) < u
	     && u < ((DItype) 1 << DF_SIZE)))
	{
	  if ((USItype) u & (REP_BIT - 1))
	    u |= REP_BIT;
	}
    }
  f = (SItype) (u >> WORD_SIZE);
  f *= HIGH_HALFWORD_COEFF;
  f *= HIGH_HALFWORD_COEFF;
  f += (USItype) (u & (HIGH_WORD_COEFF - 1));

  return (SFtype) f;
}

DItype
__lshrdi3 (DItype u, word_type b)
{
  DIunion w;
  word_type bm;
  DIunion uu;

  if (b == 0)
    return u;

  uu.ll = u;

  bm = (sizeof (SItype) * BITS_PER_UNIT) - b;
  if (bm <= 0)
    {
      w.s.high = 0;
      w.s.low = (USItype) uu.s.high >> -bm;
    }
  else
    {
      USItype carries = (USItype) uu.s.high << bm;
      w.s.high = (USItype) uu.s.high >> b;
      w.s.low = ((USItype) uu.s.low >> b) | carries;
    }

  return w.ll;
}

void
__pure_virtual (void)
{
  fn_8025FB08 ();
}

word_type
__cmpdi2 (DItype a, DItype b)
{
  DIunion au, bu;

  au.ll = a, bu.ll = b;

  if (au.s.high < bu.s.high)
    return 0;
  else if (au.s.high > bu.s.high)
    return 2;
  if ((USItype) au.s.low < (USItype) bu.s.low)
    return 0;
  else if ((USItype) au.s.low > (USItype) bu.s.low)
    return 2;
  return 1;
}

void
fn_8025FAF8 (void)
{
  fn_8023E88C ();
}

void (*lbl_802FF4A8) (void) = fn_8025FAF8;

void
fn_8025FB08 (void)
{
  (*lbl_802FF4A8) ();
}

static Context_8025FB68 *fn_8025FB34 (void);
static Context_8025FB68 *fn_8025FB68 (void);

static Context_8025FB68 *(*lbl_802FF4AC) (void) = fn_8025FB34;

static Context_8025FB68 *
fn_8025FB34 (void)
{
  lbl_802FF4AC = fn_8025FB68;
  return (*lbl_802FF4AC) ();
}

static Context_8025FB68 *
fn_8025FB68 (void)
{
  static Context_8025FB68 eh;
  static int initialized;
  static void *top_elt[2];

  if (! initialized)
    {
      initialized = 1;
      memset (&eh, 0, sizeof eh);
      eh.mUnknown4 = top_elt;
    }
  return &eh;
}
