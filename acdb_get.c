#include <stdlib.h>
#include <dlfcn.h>

#include "acdb_data.h"

typedef int (*platform_get_snd_device_acdb_id_t)(int);

int main() {
    void *handle;
    const char *error;
    platform_get_snd_device_acdb_id_t platform_get_snd_device_acdb_id;

    handle = dlopen(LIB_AUDIO_HAL, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror(); /* Clear any existing error */

    platform_get_snd_device_acdb_id = (platform_get_snd_device_acdb_id_t)dlsym(handle, "platform_get_snd_device_acdb_id");

    error = dlerror();
    if (error != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    printf("    <acdb_ids>\n");
    for (int dev = 1; dev < SND_DEVICE_MAX; dev++)
        printf("        <device name=\"%s\" acdb_id=\"%i\"/>\n", device_table[dev], platform_get_snd_device_acdb_id(dev));
    printf("    </acdb_ids>\n");

    dlclose(handle);
    exit(EXIT_SUCCESS);
}
