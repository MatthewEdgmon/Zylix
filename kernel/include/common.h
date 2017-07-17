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

inline void pokeb(uint16_t* address, uint8_t value) { *((uint8_t*) address) = value; }
inline void pokew(uint16_t* address, uint16_t value) { *((uint16_t*) address) = value; }
inline void pokel(uint16_t* address, uint32_t value) { *((uint32_t*) address) = value; }

inline uint8_t peekb(uint8_t* address) { return *((uint8_t*) address); }
inline uint16_t peekw(uint16_t* address) { return *((uint16_t*) address); }
inline uint32_t peekl(uint32_t* address) { return *((uint32_t*) address); }

#endif /* __COMMON_H__ */
