/* Partial source for the C library range 0x802622DC-0x80264424 (neutral file name). */

#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <dolphin/os.h>

typedef struct File_80262B5C
{
  char mUnknown0[92];
  void *mUnknown5C;
} File_80262B5C;

typedef struct Exit_80262310
{
  struct Exit_80262310 *mUnknown0;
  int mUnknown4;
  void (*mUnknown8[32]) (void);
} Exit_80262310;

typedef struct Reent_802622DC
{
  char mUnknown0[8];
  File_80262B5C *mUnknown8;
  char mUnknownC[316];
  Exit_80262310 *mUnknown148;
  Exit_80262310 mUnknown14C;
} Reent_802622DC;

extern Reent_802622DC *lbl_803EC56C;
extern char lbl_802FF4B0[];
extern char lbl_803A6ACC[];
extern int lbl_803EC548;
extern char *lbl_803EC54C;

extern int fn_80262C34 (void *data, File_80262B5C *fp, const char *fmt, va_list ap);
extern int fn_80264680 ();
extern int fn_80266AD8 (int a, char *buf, int count);

int fn_80262B5C (File_80262B5C *fp, const char *fmt, va_list ap);
void *fn_80262440 (size_t size);
void fn_802624D8 (char *s);

int
vprintf (const char *fmt, va_list ap)
{
  return fn_80262B5C (lbl_803EC56C->mUnknown8, fmt, ap);
}

int
atexit (void (*fn) (void))
{
  Exit_80262310 *p;

  if ((p = lbl_803EC56C->mUnknown148) == NULL)
    lbl_803EC56C->mUnknown148 = p = &lbl_803EC56C->mUnknown14C;
  if (p->mUnknown4 >= 32)
    {
      if ((p = (Exit_80262310 *) fn_80262440 (sizeof *p)) == NULL)
	return -1;
      p->mUnknown4 = 0;
      p->mUnknown0 = lbl_803EC56C->mUnknown148;
      lbl_803EC56C->mUnknown148 = p;
    }
  p->mUnknown8[p->mUnknown4++] = fn;
  return 0;
}

void *
fn_802623A8 (const void *key, const void *base, size_t count, size_t size,
	     int (*compare) (const void *, const void *))
{
  void *p;
  size_t lo = 0;
  size_t hi = count;
  size_t mid;
  int cmp;

  if (count == 0 || size == 0)
    return NULL;
  while (lo < hi)
    {
      mid = (lo + hi) / 2;
      p = (void *) ((char *) base + mid * size);
      cmp = compare (key, p);
      if (cmp < 0)
	hi = mid;
      else if (cmp > 0)
	lo = mid + 1;
      else
	return p;
    }
  return NULL;
}

void *
fn_80262440 (size_t size)
{
  OSPanic (0, 0, "\n*** Library error ***\nAn external call has been made to 'malloc'\nCalling function address: 0x%X\nPlease See the ProDG manual\n",
	   (char *) __builtin_return_address (0) - 4);
}

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
