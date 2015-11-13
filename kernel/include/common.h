#ifndef __COMMON_H__
#define __COMMON_H__

/* Simplyfing bit operations. */
#define BIT_SET(var, pos)       ((var) |=  (1 << (pos)))
#define BIT_CHECK(var, pos)     ((var) &   (1 << (pos)))
#define BIT_FLIP(var, pos)      ((var) ^=  (1 << (pos)))
#define BIT_CLEAR(var, pos)     ((var) &= ~(1 << (pos)))   

#define SECOND      1
#define MINUTE      (60 * SECOND)
#define HOUR        (60 * MINUTE)
#define DAY         (24 * HOUR)
#define YEAR        (365 * DAY)

#define HALT()      __asm__ __volatile__ ("hlt");

#endif /* __COMMON_H__ */