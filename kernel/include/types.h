#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>

#undef NULL
#define NULL ((void *)0UL)

typedef signed char			int8_t;
typedef signed short		int16_t;
// typedef signed int		int32_t;
typedef signed long long	int64_t;
typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
//typedef unsigned int		uint32_t;
typedef unsigned long long	uint64_t;

typedef unsigned long		size_t;

typedef enum {false, true}	bool;

#define FALSE				(unsigned int)0
#define TRUE				(unsigned int)1


#endif /* __TYPES_H__ */