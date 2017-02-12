#include <stdlib.h>
#include <dlfcn.h>

#include "acdb_data.h"

typedef int (*platform_get_snd_device_acdb_id_t)(int);

int main() {
    void *handle;
    platform_get_snd_device_acdb_id_t platform_get_snd_device_acdb_id;

    handle = dlopen(LIB_AUDIO_HAL, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    platform_get_snd_device_acdb_id = (platform_get_snd_device_acdb_id_t) dlsym(handle, "platform_get_snd_device_acdb_id");

    if (!platform_get_snd_device_acdb_id)  {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    printf("    <acdb_ids>\n");
    int dev;
    for (dev = 1; dev < SND_DEVICE_MAX; dev++)
        printf("        <device name=\"%s\" acdb_id=\"%i\"/>\n", device_table[dev], platform_get_snd_device_acdb_id(dev));
    printf("    </acdb_ids>\n");

    dlclose(handle);
    return 0;
}
