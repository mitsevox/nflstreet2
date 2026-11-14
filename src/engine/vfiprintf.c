/* Formats integer/string arguments and exposes the fixed C-locale conventions. */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */


/*
 * Copyright (c) 1994, 1997, 2001 Red Hat Incorporated.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * at Cygnus Solutions.  Cygnus Solutions may not be used to
 * endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "engine/vfiprintf.h"
#include "engine/mbtowc_r.h"
#include "engine/fn_80266AD8.h"
#include <stddef.h>
#include <string.h>

typedef unsigned long u_long;
typedef unsigned short u_short;
typedef unsigned int u_int;
extern int lbl_803EC558;
extern char *add_separators(char *dst, char *start, char *end, int *pLen);

static char _VFI_acBuffer[128];
static int _VFI_iBuffered = 0;
static char *_VFI_pWrite = _VFI_acBuffer;

/* Accumulates byte spans in a fixed staging buffer and drains it on request. */
static int
_vfwrite (int a, const char *s, unsigned int n, int flush)
{
  unsigned int i;
  int result;

  if (flush == 1)
    {
      result = fn_80266AD8 (a, _VFI_acBuffer, _VFI_iBuffered);
      _VFI_iBuffered = 0;
      _VFI_pWrite = _VFI_acBuffer;
      return result;
    }
  for (i = 0; i < n; i++)
    {
      *_VFI_pWrite = s[i];
      _VFI_pWrite++;
      if (++_VFI_iBuffered > 127)
	{
	  result = fn_80266AD8 (a, _VFI_acBuffer, _VFI_iBuffered);
	  _VFI_pWrite = _VFI_acBuffer;
	  _VFI_iBuffered = 0;
	  if (result == 0)
	    return 0;
	}
    }
  return i;
}

#define	to_digit(c)	((c) - '0')
#define is_digit(c)	((unsigned)to_digit(c) <= 9)
#define	to_char(n)	((n) + '0')

/*
 * Flags used during conversion.
 */
#define	ALT		0x001		/* alternate form */
#define	HEXPREFIX	0x002		/* add 0x or 0X prefix */
#define	LADJUST		0x004		/* left adjustment */
#define	LONGDBL		0x008		/* long double */
#define	LONGINT		0x010		/* long integer */
#define	QUADINT		0x020		/* quad integer */
#define	SHORTINT	0x040		/* short integer */
#define	ZEROPAD		0x080		/* zero (as opposed to blank) pad */
#define FPT		0x100		/* Floating point number */
#define GROUP 0x200
#define BUF 40

/* Consumes the format and advances the supplied argument list. */
int
_vfiprintf_r(void *data, RuntimeFile_t *fp, const char *fmt0, va_list ap)
{
	char *fmt;	/* format string */
	int ch;	/* character from fmt */
	int n, m;	/* handy integers (short term usage) */
	char *cp;	/* handy char pointer (short term usage) */
	int flags;	/* flags as above */
	int ret;		/* return value accumulator */
	int width;		/* width from format (%8d), or 0 */
	int prec;		/* precision from format (%.3d), or -1 */
	char sign;		/* sign prefix (' ', '+', '-', or \0) */
	RuntimeWideChar_t wc;

#define	quad_t	  long long
#define	u_quad_t  unsigned long long

	u_quad_t _uquad;	/* integer arguments %[diouxX] */
	enum RuntimePrintfBase_t { OCT, DEC, HEX } base;/* base for [diouxX] conversion */
	int dprec;		/* a copy of prec if [diouxX], 0 otherwise */
	int realsz;		/* field size expanded by dprec */
	int size;		/* size of converted field or string */
	char *xdigs;	/* digits for [xX] conversion */

	char buf[BUF];		/* integer digits and single-character output */
	char ox[2];		/* space for 0x hex-prefix */
        int state = 0;          /* mbtowc calls from library must not change state */

	/*
	 * Choose PADSIZE to trade efficiency vs. size.  If larger printf
	 * fields occur frequently, increase PADSIZE and make the initialisers
	 * below longer.
	 */
#define	PADSIZE	16		/* pad chunk size */
	static const char _VFI_acBlanks[PADSIZE] =
	 {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	static const char _VFI_acZeroes[PADSIZE] =
	 {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};

	/* PAD uses n as the chunk counter. */
#define PRINT(ptr, len) { \
    if (fp->mFlags & 0x200) { \
        if (fp->mWriteRemaining > (len)) { \
            memcpy(fp->mCursor, (ptr), (len)); \
            fp->mCursor += (len); \
            fp->mWriteRemaining -= (len); \
        } else { \
            memcpy(fp->mCursor, (ptr), fp->mWriteRemaining); \
            fp->mCursor += fp->mWriteRemaining; \
            fp->mWriteRemaining = 0; \
        } \
    } else { \
        if (fp->mFlags == 0 && fp->mDescriptor == 0) \
            fp->mDescriptor = 1; \
        _vfwrite(fp->mDescriptor, (ptr), (len), 0); \
    } \
}
#define	PAD(howmany, with) { \
	if ((n = (howmany)) > 0) { \
		while (n > PADSIZE) { \
			PRINT(with, PADSIZE); \
			n -= PADSIZE; \
		} \
		PRINT(with, n); \
	} \
}
#define FLUSH() { \
    if (!(fp->mFlags & 0x200)) \
        _vfwrite(fp->mDescriptor, 0, 0, 1); \
}

	/*
	 * To extend shorts properly, we need both signed and unsigned
	 * argument extraction methods.
	 */
#define	SARG() \
	(flags&QUADINT ? va_arg(ap, quad_t) : \
	    flags&LONGINT ? va_arg(ap, long) : \
	    flags&SHORTINT ? (long)(short)va_arg(ap, int) : \
	    (long)va_arg(ap, int))
#define	UARG() \
	(flags&QUADINT ? va_arg(ap, u_quad_t) : \
	    flags&LONGINT ? va_arg(ap, u_long) : \
	    flags&SHORTINT ? (u_long)(u_short)va_arg(ap, int) : \
	    (u_long)va_arg(ap, u_int))

	fmt = (char *)fmt0;
	ret = 0;

	/*
	 * Scan the format for conversions (`%' character).
	 */
	for (;;) {
	        cp = fmt;
	        while ((n = _mbtowc_r(lbl_803EC56C, &wc, fmt, lbl_803EC558, &state)) > 0) {
			fmt += n;
			if (wc == '%') {
				fmt--;
				break;
			}
		}
		if ((m = fmt - cp) != 0) {
			PRINT(cp, m);
			ret += m;
		}
		if (n <= 0)
			goto done;
		if (fp->mWriteRemaining <= 0 && (fp->mFlags & 0x200))
			goto error;
		fmt++;		/* skip over '%' */

		flags = 0;
		dprec = 0;
		width = 0;
		prec = -1;
		sign = '\0';

rflag:		ch = *fmt++;
reswitch:	switch (ch) {
		case ' ':
			/*
			 * ``If the space and + flags both appear, the space
			 * flag will be ignored.''
			 *	-- ANSI X3J11
			 */
			if (!sign)
				sign = ' ';
			goto rflag;
		case '#':
			flags |= ALT;
			goto rflag;
		case '\'':
			flags |= GROUP;
			goto rflag;
		case '*':
			/*
			 * ``A negative field width argument is taken as a
			 * - flag followed by a positive field width.''
			 *	-- ANSI X3J11
			 * They don't exclude field widths read from args.
			 */
			if ((width = va_arg(ap, int)) >= 0)
				goto rflag;
			width = -width;
			/* FALLTHROUGH */
		case '-':
			flags |= LADJUST;
			goto rflag;
		case '+':
			sign = '+';
			goto rflag;
		case '.':
			if ((ch = *fmt++) == '*') {
				n = va_arg(ap, int);
				prec = n < 0 ? -1 : n;
				goto rflag;
			}
			n = 0;
			while (is_digit(ch)) {
				n = 10 * n + to_digit(ch);
				ch = *fmt++;
			}
			prec = n < 0 ? -1 : n;
			goto reswitch;
		case '0':
			/*
			 * ``Note that 0 is taken as a flag, not as the
			 * beginning of a field width.''
			 *	-- ANSI X3J11
			 */
			flags |= ZEROPAD;
			goto rflag;
		case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			n = 0;
			do {
				n = 10 * n + to_digit(ch);
				ch = *fmt++;
			} while (is_digit(ch));
			width = n;
			goto reswitch;
		case 'h':
			flags |= SHORTINT;
			goto rflag;
		case 'l':
			if (*fmt == 'l') {
				fmt++;
				flags |= QUADINT;
			} else {
				flags |= LONGINT;
			}
			goto rflag;
		case 'q':
			flags |= QUADINT;
			goto rflag;
		case 'c':
			*(cp = buf) = va_arg(ap, int);
			size = 1;
			sign = '\0';
			break;
		case 'D':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'd':
		case 'i':
			_uquad = SARG();
			if ((quad_t)_uquad < 0)
			{

				_uquad = -_uquad;
				sign = '-';
			}
			base = DEC;
			goto number;
		case 'n':
			if (flags & QUADINT)
				*va_arg(ap, quad_t *) = ret;
			else
			if (flags & LONGINT)
				*va_arg(ap, long *) = ret;
			else if (flags & SHORTINT)
				*va_arg(ap, short *) = ret;
			else
				*va_arg(ap, int *) = ret;
			continue;	/* no output */
		case 'O':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'o':
			_uquad = UARG();
			base = OCT;
			goto nosign;
		case 'p':
			/*
			 * ``The argument shall be a pointer to void.  The
			 * value of the pointer is converted to a sequence
			 * of printable characters, in an implementation-
			 * defined manner.''
			 *	-- ANSI X3J11
			 */
			/* NOSTRICT */
			_uquad = (u_long)va_arg(ap, void *);
			base = HEX;
			xdigs = "0123456789abcdef";
			flags |= HEXPREFIX;
			ch = 'x';
			goto nosign;
		case 's':
			if ((cp = va_arg(ap, char *)) == NULL)
				cp = "(null)";
			if (prec >= 0) {
				/*
				 * can't use strlen; can only look for the
				 * NUL in the first `prec' characters, and
				 * strlen() will go further.
				 */
				char *p = memchr(cp, 0, prec);

				if (p != NULL) {
					size = p - cp;
					if (size > prec)
						size = prec;
				} else
					size = prec;
			} else
				size = strlen(cp);
			sign = '\0';
			break;
		case 'U':
			flags |= LONGINT;
			/*FALLTHROUGH*/
		case 'u':
			_uquad = UARG();
			base = DEC;
			goto nosign;
		case 'X':
			xdigs = "0123456789ABCDEF";
			goto hex;
		case 'x':
			xdigs = "0123456789abcdef";
hex:			_uquad = UARG();
			base = HEX;
			/* leading 0x/X only if non-zero */
			if (flags & ALT && _uquad != 0)
				flags |= HEXPREFIX;

			/* unsigned conversions */
nosign:			sign = '\0';
			/*
			 * ``... diouXx conversions ... if a precision is
			 * specified, the 0 flag will be ignored.''
			 *	-- ANSI X3J11
			 */
number:			if ((dprec = prec) >= 0)
				flags &= ~ZEROPAD;

			/*
			 * ``The result of converting a zero value with an
			 * explicit precision of zero is no characters.''
			 *	-- ANSI X3J11
			 */
			cp = buf + BUF;
			if (_uquad != 0 || prec != 0) {
				/*
				 * Unsigned mod is hard, and unsigned mod
				 * by a constant is easier than that by
				 * a variable; hence this switch.
				 */
				switch (base) {
				case OCT:
					do {
						*--cp = to_char(_uquad & 7);
						_uquad >>= 3;
					} while (_uquad);
					/* handle octal leading 0 */
					if (flags & ALT && *cp != '0')
						*--cp = '0';
					break;

				case DEC:
					/* many numbers are 1 digit */
					while (_uquad >= 10) {
						*--cp = to_char(_uquad % 10);
						_uquad /= 10;
					}
					*--cp = to_char(_uquad);
					break;

				case HEX:
					do {
						*--cp = xdigs[_uquad & 15];
						_uquad >>= 4;
					} while (_uquad);
					break;

				default:
					cp = "bug in vfprintf: bad base";
					size = strlen(cp);
					goto skipsize;
				}
			}

			if (base == DEC && (flags & GROUP))
				cp = add_separators(buf, cp, buf + BUF, &size);
			else
				size = buf + BUF - cp;
		skipsize:
			break;
		default:	/* "%?" prints ?, unless ? is NUL */
			if (ch == '\0')
				goto done;
			/* pretend it was %c with argument ch */
			cp = buf;
			*cp = ch;
			size = 1;
			sign = '\0';
			break;
		}

		/*
		 * All reasonable formats wind up here.  At this point, `cp'
		 * points to a string which (if not flags&LADJUST) should be
		 * padded out to `width' places.  If flags&ZEROPAD, it should
		 * first be prefixed by any sign or other prefix; otherwise,
		 * it should be blank padded before the prefix is emitted.
		 * After any left-hand padding and prefixing, emit zeroes
		 * required by a decimal [diouxX] precision, then print the
		 * string proper; finally, if LADJUST, pad with blanks.
		 *
		 * Compute actual size, so we know how much to pad.
		 * size excludes decimal prec; realsz includes it.
		 */
		realsz = dprec > size ? dprec : size;
		if (sign)
			realsz++;
		else if (flags & HEXPREFIX)
			realsz+= 2;

		/* right-adjusting blank padding */
		if ((flags & (LADJUST|ZEROPAD)) == 0)
			PAD(width - realsz, _VFI_acBlanks);

		/* prefix */
		if (sign) {
			PRINT(&sign, 1);
		} else if (flags & HEXPREFIX) {
			ox[0] = '0';
			ox[1] = ch;
			PRINT(ox, 2);
		}

		/* right-adjusting zero padding */
		if ((flags & (LADJUST|ZEROPAD)) == ZEROPAD)
			PAD(width - realsz, _VFI_acZeroes);

		/* leading _VFI_acZeroes from decimal precision */
		PAD(dprec - size, _VFI_acZeroes);

		/* the string or number proper */
		PRINT(cp, size);
		/* left-adjusting padding (always blank) */
		if (flags & LADJUST)
			PAD(width - realsz, _VFI_acBlanks);

		/* finally, adjust ret */
		ret += width > realsz ? width : realsz;


	}
done:
	FLUSH();
error:
	return ret;
	/* NOTREACHED */
}

/* Numeric and monetary defaults for the C locale. */
static const struct RuntimeLocaleConv_t _VFI_sLocale = {
    ".", "", "", "", "", "", "", "", "", "",
    255, 255, 255, 255, 255, 255, 255, 255
};

/* Returns the fixed numeric and monetary convention record. */
struct RuntimeLocaleConv_t *_localeconv_r(void *data)
{
    return (struct RuntimeLocaleConv_t *)&_VFI_sLocale;
}

/* Uses the shared runtime context for the conventional locale accessor. */
struct RuntimeLocaleConv_t *localeconv(void)
{
    return _localeconv_r(lbl_803EC56C);
}
