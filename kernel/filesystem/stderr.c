#include <filesystem/vfs.h>
#include <filesystem/dev.h>
#include <filesystem/stderr.h>

#include <terminal.h>

uint32_t stderr_write(fs_node_t* node, uint32_t offset, uint8_t* buffer) {
    TerminalPrintCharacter(*buffer);
    return 0;
}

void SetupVFSDeviceStderr() {
    RegisterDevice("stderr", NULL, stderr_write);
    fs_node_t* node;
    node->dev->block_size = 0;
}
