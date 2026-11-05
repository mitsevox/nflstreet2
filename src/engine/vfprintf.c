/* Partial source for vfprintf.c (C library): the formatted-output engine and its number
   conversion helpers. */

#include "engine/fn_80266AD8.h"
#include "engine/Reent_802622DC.h"
#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

extern char lbl_802FF4B0[];
extern char lbl_803A6ACC[];
extern int lbl_803EC548;
extern char *lbl_803EC54C;

extern int fn_80262C34 (void *data, File_80262B5C *fp, const char *fmt, va_list ap);
extern int fn_80264680 ();
extern double fn_80265D2C (double x);
extern double fn_80265EA0 (double x, double y);
extern char lbl_803A6A28[];

void fn_802624D8 (char *s);

int
fn_8026247C (char *s, int n)
{
  if (n > 0)
    {
      n--;
      if (s[n] > '4')
	{
	  do
	    s[n] = '0';
	  while (--n > 0 && s[n] == '9');
	  if (s[n] == '9')
	    return 0;
	  s[n]++;
	}
    }
  return 1;
}

void
fn_802624D8 (char *s)
{
  int i, j;
  char c;

  for (j = 0; s[j] != 0; j++);
  for (i = 0, j--; i < j; i++, j--)
    {
      c = s[i];
      s[i] = s[j];
      s[j] = c;
    }
}

void
fn_80262524 (unsigned int value, char *buf, int base)
{
  int i;
  int neg = value >> 31;

  if (neg && base == 10)
    value = -value;
  i = 0;
  do
    buf[i++] = lbl_802FF4B0[value % base];
  while ((value /= base) != 0);
  if (neg)
    buf[i++] = '-';
  buf[i] = 0;
  fn_802624D8 (buf);
}

char *
fn_802625A0 (double value, int prec, int conv, int strip, char *sign)
{
  union
  {
    double d;
    unsigned int w[2];
  } u;
  unsigned int lo, mant, e, neg;
  char *p;
  int n, i, j, k, d, exp10, end, width;
  double ip, eps;
  char c;

  u.d = value;
  lo = u.w[1];
  mant = u.w[0] & 0xfffff;
  e = u.w[0] >> 20;
  neg = e & 0x800;
  e &= 0x7ff;
  if (e == 0x7ff)
    {
      if (mant == 0 && lo == 0)
	{
	  if (neg)
	    strcpy (lbl_803A6A28, "-Inf");
	  else
	    strcpy (lbl_803A6A28, "Inf");
	}
      else
	strcpy (lbl_803A6A28, "NaN");
      return lbl_803A6A28;
    }

  width = prec;
  n = 0;
  if (value < 0.0)
    {
      if (sign)
	{
	  *sign = '-';
	  p = lbl_803A6A28;
	}
      else
	{
	  lbl_803A6A28[0] = '-';
	  p = lbl_803A6A28 + 1;
	}
      value = -value;
    }
  else
    p = lbl_803A6A28;

  if (value >= 1.0)
    {
      ip = fn_80265D2C (value);
      value -= ip;
      do
	{
	  if (n > 162)
	    break;
	  d = (int) fn_80265EA0 (ip, 10.0);
	  p[n++] = d + '0';
	  ip -= d;
	  ip /= 10.0;
	}
      while (ip >= 1.0);
      for (i = 0, j = n - 1; i < j; i++, j--)
	{
	  c = p[i];
	  p[i] = p[j];
	  p[j] = c;
	}
    }

  exp10 = n;
  if (exp10 == 0)
    {
      if (conv != 'f')
	{
	  if (value != 0.0)
	    {
	      value *= 10.0;
	      while (value < 1.0 && exp10 > -1021)
		{
		  value *= 10.0;
		  exp10--;
		}
	      exp10--;
	    }
	  if (value >= 1.0)
	    {
	      width = prec + 1;
	      value /= 10.0;
	    }
	}
      else
	p[n++] = '0';
    }

  if (exp10 < 0)
    end = width;
  else if (conv == 'f')
    end = width + (exp10 < 1 ? 1 : exp10);
  else
    end = width + 1;

  eps = 5.551115123125783e-17;
  for (;;)
    {
      value *= 10.0;
      d = (int) value;
      eps *= 10.0;
      value -= d;
      if (n < end && value >= eps && value <= 1.0 - eps)
	p[n++] = d + '0';
      else
	break;
    }
  if (value >= 0.5)
    d++;
  p[n++] = d + '0';
  while (n <= end)
    p[n++] = '0';

  if (fn_8026247C (p, end + 1) == 0)
    {
      p[0] = '1';
      end++;
      exp10++;
    }

  if (prec != 0)
    {
      if (conv == 'f')
	{
	  if (exp10 > 0)
	    k = exp10;
	  else
	    k = 1;
	}
      else
	k = 1;
      for (n = end; n > k; n--)
	p[n] = p[n - 1];
      p[k] = '.';
    }
  else
    end--;

  if (strip)
    {
      while (end != 0 && p[end] == '0')
	end--;
      if (p[end] == '.')
	end--;
    }

  if (conv != 'f')
    {
      p[++end] = conv;
      if (exp10 >= 0)
	{
	  p[++end] = '+';
	  if (exp10 != 0)
	    exp10--;
	  if (exp10 <= 9)
	    p[++end] = '0';
	}
      else
	{
	  p[++end] = '-';
	  if (exp10 > -10)
	    p[++end] = '0';
	  exp10 = -exp10;
	}
      fn_80262524 (exp10, &p[++end], 10);
    }
  else
    p[end + 1] = 0;

  return lbl_803A6A28;
}

int
fn_80262A88 (int a, const char *s, unsigned int n, int flush)
{
  unsigned int i;
  int result;

  if (flush == 1)
    {
      result = fn_80266AD8 (a, lbl_803A6ACC, lbl_803EC548);
      lbl_803EC548 = 0;
      lbl_803EC54C = lbl_803A6ACC;
      return result;
    }
  for (i = 0; i < n; i++)
    {
      *lbl_803EC54C = s[i];
      lbl_803EC54C++;
      if (++lbl_803EC548 > 127)
	{
	  result = fn_80266AD8 (a, lbl_803A6ACC, lbl_803EC548);
	  lbl_803EC54C = lbl_803A6ACC;
	  lbl_803EC548 = 0;
	  if (result == 0)
	    return 0;
	}
    }
  return i;
}

int
fn_80262B5C (File_80262B5C *fp, const char *fmt, va_list ap)
{
  const char *p;

  for (p = fmt; *p != 0; p++)
    {
      if (*p == '%' && p[1] != 0)
	{
	  p++;
	  while (*p <= '@' && p[1] != 0)
	    p++;
	  switch (*p)
	    {
	    case 'L':
	    case 'E':
	    case 'G':
	    case 'e':
	    case 'f':
	    case 'g':
	      return fn_80262C34 (fp->mUnknown5C, fp, fmt, ap);
	    }
	}
    }
  return fn_80264680 (fp->mUnknown5C, fp, fmt, ap);
}

char *fn_80264424(char *dst, char *start, char *end, int *pLen)
{
    int len = end - start + 10;
    char *buf = __builtin_alloca(len);
    char *q = buf + len - 1;
    char *dot;
    char *p;
    int state;
    int count = 0;

    if (dst == 0 || start == 0 || end == 0)
        return 0;

    state = 0;
    p = start;
    dot = end;
    while (p <= end && state != 2) {
        switch (*p) {
        case '.':
            dot = p;
            if (state == 0)
                state = 1;
            break;
        case 'E':
        case 'e':
            state = 2;
            break;
        }
        p++;
    }
    if (state == 2)
        return start;

    for (p = end; p > start; p--) {
        *q-- = *p;
        if (p <= dot) {
            if (count % 3 == 0 && count != 0) {
                *q-- = ',';
                len++;
            }
            count++;
        }
    }
    *q = *p;
    len -= 10;
    memcpy(dst, q, len);
    *pLen = len;
    return dst;
}
