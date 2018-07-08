/**
 * common.h - Universial C macros.
 *
 * This file is part of Zylix.
 *
 * Zylix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Zylix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Zylix.  If not, see <http://www.gnu.org/licenses/>.
 */

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
