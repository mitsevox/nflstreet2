/* Multibyte-to-wide-character conversion for the C runtime. */

/*
Copyright (c) 1994, 1997, 2001 Red Hat Incorporated.
All rights reserved.

Redistribution and use in source and binary forms are permitted
provided that the above copyright notice and this paragraph are
duplicated in all such forms and that any documentation,
advertising materials, and other materials related to such
distribution and use acknowledge that the software was developed
at Cygnus Solutions.  Cygnus Solutions may not be used to
endorse or promote products derived from this software without
specific prior written permission.
THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "engine/mbtowc_r.h"
#include <string.h>

#define ESC_CHAR 0x1b
#define _issjis1(c)    (((c) >= 0x81 && (c) <= 0x9f) || ((c) >= 0xe0 && (c) <= 0xef))
#define _issjis2(c)    (((c) >= 0x40 && (c) <= 0x7e) || ((c) >= 0x80 && (c) <= 0xfc))
#define _iseucjp(c)    ((c) >= 0xa1 && (c) <= 0xfe)
#define _isjis(c)      ((c) >= 0x21 && (c) <= 0x7e)

typedef enum { ESCAPE, DOLLAR, BRACKET, AT, B, J,
               NUL, JIS_CHAR, OTHER, JIS_C_NUM } JisCharType_t;
typedef enum { ASCII, A_ESC, A_ESC_DL, JIS, JIS_1, JIS_2, J_ESC, J_ESC_BR,
               J2_ESC, J2_ESC_BR, DONE, INV, JIS_S_NUM } JisState_t;
typedef enum { COPY_A, COPY_J, COPY_J2, MAKE_A, MAKE_J, NOOP, EMPTY, ERROR } JisAction_t;

static JisState_t _Mbtowc_aJisState[JIS_S_NUM][JIS_C_NUM] = {

   { A_ESC,   DONE,     DONE,     DONE,    DONE,   DONE,    DONE,    DONE,     DONE },
   { DONE,    A_ESC_DL, DONE,     DONE,    DONE,   DONE,    DONE,    DONE,     DONE },
{ DONE,    DONE,     DONE,     JIS,     JIS,    DONE,    DONE,    DONE,     DONE },
     { J_ESC,   JIS_1,    JIS_1,    JIS_1,   JIS_1,  JIS_1,   INV,     JIS_1,    INV },
   { INV,     JIS_2,    JIS_2,    JIS_2,   JIS_2,  JIS_2,   INV,     JIS_2,    INV },
   { J2_ESC,  DONE,     DONE,     DONE,    DONE,   DONE,    INV,     DONE,     DONE },
   { INV,     INV,      J_ESC_BR, INV,     INV,    INV,     INV,     INV,      INV },
{ INV,     INV,      INV,      INV,     ASCII,  ASCII,   INV,     INV,      INV },
  { INV,     INV,      J2_ESC_BR,INV,     INV,    INV,     INV,     INV,      INV },
{ INV,     INV,      INV,      INV,     DONE,   DONE,    INV,     INV,      INV },
};

static JisAction_t _Mbtowc_aJisAction[JIS_S_NUM][JIS_C_NUM] = {

   { NOOP,    COPY_A,   COPY_A,   COPY_A,  COPY_A,  COPY_A,  EMPTY,   COPY_A,  COPY_A},
   { COPY_A,  NOOP,     COPY_A,   COPY_A,  COPY_A,  COPY_A,  COPY_A,  COPY_A,  COPY_A},
{ COPY_A,  COPY_A,   COPY_A,   MAKE_J,  MAKE_J,  COPY_A,  COPY_A,  COPY_A,  COPY_A},
     { NOOP,    NOOP,     NOOP,     NOOP,    NOOP,    NOOP,    ERROR,   NOOP,    ERROR },
   { ERROR,   NOOP,     NOOP,     NOOP,    NOOP,    NOOP,    ERROR,   NOOP,    ERROR },
   { NOOP,    COPY_J2,  COPY_J2,  COPY_J2, COPY_J2, COPY_J2, ERROR,   COPY_J2, COPY_J2},
   { ERROR,   ERROR,    NOOP,     ERROR,   ERROR,   ERROR,   ERROR,   ERROR,   ERROR },
{ ERROR,   ERROR,    ERROR,    ERROR,   NOOP,    NOOP,    ERROR,   ERROR,   ERROR },
  { ERROR,   ERROR,    NOOP,     ERROR,   ERROR,   ERROR,   ERROR,   ERROR,   ERROR },
{ ERROR,   ERROR,    ERROR,    ERROR,   COPY_J,  COPY_J,  ERROR,   ERROR,   ERROR },
};

/* JIS shift sequences update conversion state retained between input characters. */
int _mbtowc_r(Reent_802622DC *r, RuntimeWideChar_t *pwc, const char *s, size_t n, int *state)
{
  RuntimeWideChar_t dummy;
  unsigned char *t = (unsigned char *)s;

  if (pwc == NULL)
    pwc = &dummy;

  if (s != NULL && n == 0)
    return -1;

  if (r->mLocaleName == NULL ||
      (strlen (r->mLocaleName) <= 1))
    {  }
  else if (!strcmp (r->mLocaleName, "C-SJIS"))
    {
      int char1 = *t;
      if (s == NULL)
        return 0;
      if (_issjis1 (char1))
        {
          int char2 = t[1];
          if (n <= 1)
            return -1;
          if (_issjis2 (char2))
            {
              *pwc = (((RuntimeWideChar_t)*t) << 8) + (RuntimeWideChar_t)(*(t+1));
              return 2;
            }
          else
            return -1;
        }
    }
  else if (!strcmp (r->mLocaleName, "C-EUCJP"))
    {
      int char1 = *t;
      if (s == NULL)
        return 0;
      if (_iseucjp (char1))
        {
          int char2 = t[1];
          if (n <= 1)
            return -1;
          if (_iseucjp (char2))
            {
              *pwc = (((RuntimeWideChar_t)*t) << 8) + (RuntimeWideChar_t)(*(t+1));
              return 2;
            }
          else
            return -1;
        }
    }
  else if (!strcmp (r->mLocaleName, "C-JIS"))
    {
      JisState_t curr_state;
      JisAction_t action;
      JisCharType_t ch;
      unsigned char *ptr;
      int i, curr_ch;

      if (s == NULL)
        {
          *state = 0;
          return 1;
        }

      curr_state = (*state == 0 ? ASCII : JIS);
      ptr = t;

      for (i = 0; i < n; ++i)
        {
          curr_ch = t[i];
          switch (curr_ch)
            {
            case ESC_CHAR:
              ch = ESCAPE;
              break;
            case '$':
              ch = DOLLAR;
              break;
            case '@':
              ch = AT;
              break;
            case '(':
              ch = BRACKET;
              break;
            case 'B':
              ch = B;
              break;
            case 'J':
              ch = J;
              break;
            case '\0':
              ch = NUL;
              break;
            default:
              if (_isjis (curr_ch))
                ch = JIS_CHAR;
              else
                ch = OTHER;
            }

          action = _Mbtowc_aJisAction[curr_state][ch];
          curr_state = _Mbtowc_aJisState[curr_state][ch];

          switch (action)
            {
            case NOOP:
              break;
            case EMPTY:
              *state = 0;
              *pwc = (RuntimeWideChar_t)0;
              return i;
            case COPY_A:
              *state = 0;
              *pwc = (RuntimeWideChar_t)*ptr;
              return (i + 1);
            case COPY_J:
              *state = 0;
              *pwc = (((RuntimeWideChar_t)*ptr) << 8) + (RuntimeWideChar_t)(*(ptr+1));
              return (i + 1);
            case COPY_J2:
              *state = 1;
              *pwc = (((RuntimeWideChar_t)*ptr) << 8) + (RuntimeWideChar_t)(*(ptr+1));
              return (ptr - t) + 2;
            case MAKE_A:
            case MAKE_J:
              ptr = t + i + 1;
              break;
            case ERROR:
            default:
              return -1;
            }

        }

      return -1;
    }

  if (s == NULL)
    return 0;

  *pwc = (RuntimeWideChar_t)*t;

  if (*t == '\0')
    return 0;

  return 1;
}
