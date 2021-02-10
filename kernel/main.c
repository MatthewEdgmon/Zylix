/**
 * main.c - Kernel entry point.
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

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <arch/cpu_info.h>
#include <arch/cpu.h>
#include <arch/interrupts.h>
#include <arch/io.h>
#include <arch/syscalls.h>

#include <devices/acpi/acpi.h>
#include <devices/net/Am79C970A.h>
#include <devices/storage/ata.h>
#include <devices/storage/ata_pio.h>
#include <devices/storage/ata_dma.h>
#include <devices/storage/atapi.h>
#include <devices/storage/floppy.h>
#include <devices/video/bga.h>
#include <devices/video/bitmap_font.h>
#include <devices/video/lfb_terminal.h>
#include <devices/video/vesa.h>
#include <devices/video/vga.h>
#include <devices/video/voodoo3.h>
#include <devices/cmos.h>
#include <devices/pci.h>
#include <devices/ps2.h>
#include <devices/ps2keyboard.h>
#include <devices/ps2mouse.h>
#include <devices/smbios.h>
#include <devices/vbox_guest.h>

#include <filesystem/vfs.h>

#include <memory/liballoc.h>
#include <memory/manager.h>

#include <shell/shell.h>

#include <structures/double_list.h>
#include <structures/tree.h>

#include <tasking/multitask.h>

#include <shell/shell.h>

#include <common.h>
#include <lock.h>
#include <logging.h>
#include <multiboot.h>
#include <panic.h>
#include <terminal.h>

uintptr_t initial_esp;

int main(multiboot_info_t* multiboot_info, uint32_t multiboot_magic, uintptr_t esp) {

    initial_esp = esp;

    SetupTerminal();
    TerminalSetColor(TerminalMakeColor(COLOR_WHITE, COLOR_BLACK));

    SetupCPU();
    SetupSyscalls();

    if(multiboot_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("Didn't receive right multiboot magic: 0x%X\n", multiboot_magic);
        return 1;
    }

    VGASetTextMode(90, 30);

    MultibootDumpInfo(multiboot_info);

    SetupMemoryManager(multiboot_info);
    SetupLocks();

    DumpCPUInformation();

    /* TODO: Modularize system setup. */

    SetupSMBIOS();

    SetupA20();
    SetupPS2();
    SetupPS2Keyboard();
    //SetupPS2Mouse();

    SetupACPI();

    SetupRTC();
    CMOSReadRTC();
    printf("Current date and time: %d/%d/%d %d:%02d:%02d \n", CMOSGetMonth(), CMOSGetDay(), CMOSGetYear(),
                                                              CMOSGetHours(), CMOSGetMinutes(), CMOSGetSeconds());

    SetupPCI();

    /* Video devices. */
    uint32_t video_size_x = 1024;
    uint32_t video_size_y = 768;
    uint32_t video_bpp = 32;

    if(SetupBGA() == 0) {
        BGASetVideoMode(video_size_x, video_size_y, video_bpp, 1, 1);
        SetupLFBTerminal(BGAGetLFBAddress(), BGAGetLFBWidth(), BGAGetLFBHeight());
    } else {
        printf("Bochs Graphics Adapter failed to initialize.\n");
    }

    //SetupVoodoo3();

    /* Storage devices. */
    //SetupATA_DMA();
    SetupATA_PIO();
    //SetupATAPI();
    //SetupFloppy();

    /* Network devices. */
    SetupAm79C970A();

    /* VM devices. */
    SetupVBoxGuest();

    /* Begin multi-tasking. */
    //SetupMultitask();

    SetupShell();

    int exit_status = 0;

    while(!exit_status) {

    }

    return 0;
}
