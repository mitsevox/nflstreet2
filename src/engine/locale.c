/* C library locale: the "C" locale's numeric and monetary conventions that localeconv returns
   to the formatters, the multibyte length limit the converters read, and the locale selection
   whose character-set names the game never switches (the linker discards setlocale). */

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

#include "engine/vfiprintf.h"
#include <string.h>

#define LC_ALL 0
#define LC_CTYPE 2

int __mb_cur_max = 1;

static const struct RuntimeLocaleConv_t lconv = {
    ".", "", "", "", "", "", "", "", "", "",
    255, 255, 255, 255, 255, 255, 255, 255
};

char *_setlocale_r(Reent_802622DC *p, int category, const char *locale)
{
    static char lc_ctype[8] = "C";
    static char last_lc_ctype[8] = "C";

    if (locale) {
        if (category != LC_CTYPE) {
            if (strcmp(locale, "C") && strcmp(locale, ""))
                return 0;
            if (category == LC_ALL) {
                strcpy(last_lc_ctype, lc_ctype);
                strcpy(lc_ctype, locale);
                __mb_cur_max = 1;
            }
        } else {
            if (strcmp(locale, "C") && strcmp(locale, "") && strcmp(locale, "C-JIS")
                && strcmp(locale, "C-EUCJP") && strcmp(locale, "C-SJIS"))
                return 0;

            strcpy(last_lc_ctype, lc_ctype);
            strcpy(lc_ctype, locale);

            if (!strcmp(locale, "C-JIS"))
                __mb_cur_max = 8;
            else if (strlen(locale) > 1)
                __mb_cur_max = 2;
            else
                __mb_cur_max = 1;
        }
        p->mCurrentCategory = category;
        p->mLocaleName = locale;

        if (category == LC_CTYPE)
            return last_lc_ctype;
    } else {
        if (category == LC_CTYPE)
            return lc_ctype;
    }

    return "C";
}

struct RuntimeLocaleConv_t *_localeconv_r(void *data)
{
    return (struct RuntimeLocaleConv_t *)&lconv;
}

char *setlocale(int category, const char *locale)
{
    return _setlocale_r(_impure_ptr, category, locale);
}

struct RuntimeLocaleConv_t *localeconv(void)
{
    return _localeconv_r(_impure_ptr);
}
