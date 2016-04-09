#include <stdint.h>

#include <filesystem/dev.h>
#include <filesystem/null.h>

/* Just fill buffer with zero. */
uint32_t DeviceNullRead(struct fs_node* node, uint32_t offset, uint8_t* buffer) {
    for(int i = 0; i < 512; i++) {
        buffer[i] = 0;
    }
    return 0;
}

void SetupVFSDeviceNull() {
    RegisterDevice("null", DeviceNullRead, NULL);
}
