#ifndef __MATH_H__
#define __MATH_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Use GCC built in types, if GCC's version is greater than 3.03. */
#if 100*__GNUC__+__GNUC_MINOR__ >= 303
#define NAN        __builtin_nanf("")
#define INFINITY   __builtin_inff()
#else
#define NAN        (0.0f/0.0f)
#define INFINITY   1e5000f
#endif

#define HUGE_VALF INFINITY
#define HUGE_VAL  ((double) INFINITY)
#define HUGE_VALL ((long double) INFINITY)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __MATH_H__ */
