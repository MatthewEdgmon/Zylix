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

#define FP_NAN       0
#define FP_INFINITE  1
#define FP_ZERO      2
#define FP_SUBNORMAL 3
#define FP_NORMAL    4

double      acos(double);
float       acosf(float);
long double acosl(long double);

double      acosh(double);
float       acoshf(float);
long double acoshl(long double);

double      asin(double);
float       asinf(float);
long double asinl(long double);

double      asinh(double);
float       asinhf(float);
long double asinhl(long double);

double      cos(double);
float       cosf(float);
long double cosl(long double);

double      tan(double);
float       tanf(float);
long double tanl(long double);

double      tanh(double);
float       tanhf(float);
long double tanhl(long double);

double      tgamma(double);
float       tgammaf(float);
long double tgammal(long double);

double      trunc(double);
float       truncf(float);
long double truncl(long double);

#if defined(_XOPEN_SOURCE) || defined(_BSD_SOURCE)
#undef  MAXFLOAT
#define MAXFLOAT        3.40282346638528859812e+38F
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __MATH_H__ */
