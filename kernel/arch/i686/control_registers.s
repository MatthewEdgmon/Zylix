/**
 * control_registers.s - Functions to load CR0 - CR15.
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

.code32
.section .text
.align 4

.macro LoadCR register
    .global LoadCR\register
    .type LoadCR\register, @function
    LoadCR\register:
        mov 4(%esp), %eax
        mov %eax, %cr\register
        ret

    .global SaveCR\register
    .type SaveCR\register, @function
    SaveCR\register:
        mov %cr\register, %eax
        ret
.endm

LoadSaveCR 0
LoadSaveCR 1
LoadSaveCR 2
LoadSaveCR 3
LoadSaveCR 4
LoadSaveCR 5
LoadSaveCR 6
LoadSaveCR 7
LoadSaveCR 8
LoadSaveCR 9
LoadSaveCR 10
LoadSaveCR 11
LoadSaveCR 12
LoadSaveCR 13
LoadSaveCR 14
LoadSaveCR 15

.global GetFlagRegister
.type GetFlagRegister, @function
GetFlagRegister:
    pushfd
    pop %eax
    ret
