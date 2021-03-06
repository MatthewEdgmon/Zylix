/**
 * version.h - Kernel versioning information.
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

#ifndef __VERSION_H__
#define __VERSION_H__

extern char* __kernel_version_format;

extern char* __kernel_name;
extern char* __kernel_code_name;

extern int   __kernel_version_major;
extern int   __kernel_version_minor;
extern int   __kernel_version_lower;

extern char* __kernel_build_date;
extern char* __kernel_build_time;

extern char* __kernel_compiler_version;

#endif /* __VERSION_H__ */
