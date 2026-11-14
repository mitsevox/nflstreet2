#ifndef ENGINE_VFIPRINTF_H
#define ENGINE_VFIPRINTF_H

#include "engine/Reent_802622DC.h"
#include <stdarg.h>

struct RuntimeLocaleConv_t {
    char *decimal_point;
    char *thousands_sep;
    char *grouping;
    char *int_curr_symbol;
    char *currency_symbol;
    char *mon_decimal_point;
    char *mon_thousands_sep;
    char *mon_grouping;
    char *positive_sign;
    char *negative_sign;
    char int_frac_digits;
    char frac_digits;
    char p_cs_precedes;
    char p_sep_by_space;
    char n_cs_precedes;
    char n_sep_by_space;
    char p_sign_posn;
    char n_sign_posn;
};

#ifdef __cplusplus
extern "C" {
int _vfiprintf_r(void *data, RuntimeFile_t *fp, const char *fmt, va_list ap);
#else
int _vfiprintf_r();
#endif
struct RuntimeLocaleConv_t *_localeconv_r(void *data);
struct RuntimeLocaleConv_t *localeconv(void);
#ifdef __cplusplus
}
#endif

#endif
