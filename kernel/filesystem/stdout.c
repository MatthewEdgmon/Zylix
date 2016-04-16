#include <filesystem/vfs.h>
#include <filesystem/dev.h>
#include <filesystem/stdout.h>

#include <terminal.h>
/*
uint32_t stdout_write(fs_node_t* node, uint32_t offset, uint8_t* buffer) {
    TerminalPrintCharacter(*buffer);
    return 0;
}

void SetupVFSDeviceStdout() {
    RegisterDevice("stdout", NULL, stdout_write);
    fs_node_t* node;
    //node->dev->block_size = 0;
}
*/
