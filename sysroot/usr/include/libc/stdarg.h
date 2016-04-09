#ifndef __STDARG_H__
#define __STDARG_H__

#ifdef __cplusplus
extern "C" {
#endif

#if __GNUC__ >= 3
#define va_start(v,l)   __builtin_va_start(v,l)
#define va_end(v)       __builtin_va_end(v)
#define va_arg(v,l)     __builtin_va_arg(v,l)
#define va_copy(d,s)    __builtin_va_copy(d,s)
typedef __builtin_va_list va_list;
#else
#error You need a modern compiler.
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STDARG_H__ */
