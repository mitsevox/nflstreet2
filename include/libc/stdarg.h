#ifndef _STDARG_H_
#define _STDARG_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __MWERKS__
typedef struct {
  char gpr;
  char fpr;
  char reserved[2];
  char* input_arg_area;
  char* reg_save_area;
} __va_list[1];
typedef __va_list va_list;

#ifndef __MWERKS__
extern void __builtin_va_info(va_list*);
#endif

void* __va_arg(va_list v_list, unsigned char type);

#define va_start(ap, fmt) ((void)fmt, __builtin_va_info(&ap))
#define va_arg(ap, t) (*((t*)__va_arg(ap, _var_arg_typeof(t))))
#define va_end(ap) (void)0

#elif defined(__GNUC__) && __GNUC__ < 3
typedef struct __va_list_tag {
  unsigned char gpr;
  unsigned char fpr;
  char *overflow_arg_area;
  char *reg_save_area;
} __va_list[1], __gnuc_va_list[1];
typedef __gnuc_va_list va_list;

typedef struct {
  long   __gp_save[8];
  double __fp_save[8];
} __va_regsave_t;

#define __VA_FP_REGSAVE(AP,OFS,TYPE) \
  ((TYPE *) (void *) (&(((__va_regsave_t *) (AP)->reg_save_area)->__fp_save[OFS])))
#define __VA_GP_REGSAVE(AP,OFS,TYPE) \
  ((TYPE *) (void *) (&(((__va_regsave_t *) (AP)->reg_save_area)->__gp_save[OFS])))

#define va_start(AP,LASTARG) \
  (__builtin_next_arg (LASTARG), \
   __builtin_memcpy ((AP), __builtin_saveregs (), sizeof(__gnuc_va_list)))

#define __va_float_p(TYPE)	(__builtin_classify_type(*(TYPE *)0) == 8)
#define __va_aggregate_p(TYPE)	(__builtin_classify_type(*(TYPE *)0) >= 12)

#ifdef __OPTIMIZE__
extern void __va_arg_type_violation(void) __attribute__((__noreturn__));
#else
#define __va_arg_type_violation()
#endif

#define va_arg(AP,TYPE) \
__extension__ (*({ \
  register TYPE *__ptr; \
  if (__va_float_p (TYPE) && sizeof (TYPE) < 16) \
    { \
      unsigned char __fpr = (AP)->fpr; \
      if (__fpr < 8) \
        { \
          __ptr = __VA_FP_REGSAVE (AP, __fpr, TYPE); \
          (AP)->fpr = __fpr + 1; \
        } \
      else if (sizeof (TYPE) == 8) \
        { \
          unsigned long __addr = (unsigned long) ((AP)->overflow_arg_area); \
          __ptr = (TYPE *)((__addr + 7) & -8); \
          (AP)->overflow_arg_area = (char *)(__ptr + 1); \
        } \
      else \
        { \
          __va_arg_type_violation (); \
        } \
    } \
  else if (__va_aggregate_p (TYPE) || __va_float_p (TYPE)) \
    { \
      unsigned char __gpr = (AP)->gpr; \
      if (__gpr < 8) \
        { \
          __ptr = * __VA_GP_REGSAVE (AP, __gpr, TYPE *); \
          (AP)->gpr = __gpr + 1; \
        } \
      else \
        { \
          TYPE **__pptr = (TYPE **) ((AP)->overflow_arg_area); \
          __ptr = * __pptr; \
          (AP)->overflow_arg_area = (char *) (__pptr + 1); \
        } \
    } \
  else \
    { \
      if (sizeof (TYPE) == 8) \
        { \
          unsigned char __gpr = (AP)->gpr; \
          if (__gpr < 7) \
            { \
              __gpr += __gpr & 1; \
              __ptr = __VA_GP_REGSAVE (AP, __gpr, TYPE); \
              (AP)->gpr = __gpr + 2; \
            } \
          else \
            { \
              unsigned long __addr = (unsigned long) ((AP)->overflow_arg_area); \
              __ptr = (TYPE *)((__addr + 7) & -8); \
              (AP)->gpr = 8; \
              (AP)->overflow_arg_area = (char *)(__ptr + 1); \
            } \
        } \
      else if (sizeof (TYPE) == 4) \
        { \
          unsigned char __gpr = (AP)->gpr; \
          if (__gpr < 8) \
            { \
              __ptr = __VA_GP_REGSAVE (AP, __gpr, TYPE); \
              (AP)->gpr = __gpr + 1; \
            } \
          else \
            { \
              __ptr = (TYPE *) (AP)->overflow_arg_area; \
              (AP)->overflow_arg_area = (char *)(__ptr + 1); \
            } \
        } \
      else \
        { \
          __va_arg_type_violation (); \
        } \
    } \
  __ptr; \
}))

#define va_end(AP) ((void)0)
#else
typedef __builtin_va_list va_list;
#define va_start(v, l) __builtin_va_start(v, l)
#define va_end(v) __builtin_va_end(v)
#define va_arg(v, l) __builtin_va_arg(v, l)
#endif

#ifdef __cplusplus
}
#endif

#endif
