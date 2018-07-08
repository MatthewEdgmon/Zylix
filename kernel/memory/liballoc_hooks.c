/**
 * liballoc_hooks.c - Glue layer from Zylix to liballoc.
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

#include <stdint.h>
#include <stdio.h>

#include <memory/manager.h>

int liballoc_lock() {
    //lock();
    return 0;
}

int liballoc_unlock() {
    //unlock();
    return 0;
}

void* liballoc_alloc(int pages) {
    return ManagerPageAllocate(pages);
}

int liballoc_free(void* ptr, int pages) {
    return ManagerPageFree(ptr, pages);
}
